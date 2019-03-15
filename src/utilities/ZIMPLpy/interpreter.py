import runpy
from collections import defaultdict
from subprocess import PIPE

from psutil import Popen
import pandas as pd
import numpy as np
from gurobipy import *


class Interpreter:
    feasible_status = frozenset({GRB.OPTIMAL, GRB.UNBOUNDED, GRB.SOLUTION_LIMIT, GRB.SUBOPTIMAL})
    infeasible_status = frozenset({GRB.INFEASIBLE, GRB.INF_OR_UNBD})
    base_dir = os.path.dirname(__file__)
    zimpl_path = "%s/../ZIMPL/bin/zimpl" % os.path.dirname(__file__)
    zpl_regex = re.compile(r'\.zpl$', re.I)
    empty_rule_regex = re.compile(r'\s*<\S+>\s*::=\s*(?=\n\s*<\S+>\s*::=|$)')
    code_regex = re.compile(r'\(\*(?P<code>(?!\*\)).*)\*\)')
    enumerator_regex = re.compile(r'\(=(?P<code>(?!=\)).*)=\)')
    comment_regex = re.compile(r'#.*$')

    def __init__(self, zpl_filename, unlink_files=True):
        working_dir = os.path.dirname(zpl_filename)
        name_noext = Interpreter.zpl_regex.sub(r"", zpl_filename)
        self.py_filename = name_noext + ".py"
        self.lp_filename = name_noext + ".lp"
        zpl_mtime = os.path.getmtime(zpl_filename)

        py_process = Popen([Interpreter.zimpl_path, "-v0", "-tpy", zpl_filename], cwd=working_dir, stderr=PIPE) if not os.path.exists(self.py_filename) or zpl_mtime > os.path.getmtime(self.py_filename) else None
        lp_process = Popen([Interpreter.zimpl_path, "-v0", "-l99", "-tlp", zpl_filename], cwd=working_dir, stderr=PIPE) if not os.path.exists(self.lp_filename) or zpl_mtime > os.path.getmtime(self.lp_filename) else None

        self.unlink_files = unlink_files

        if py_process is not None:
            py_exit_code = py_process.wait()
            py_stderr = str(py_process.stderr.read().decode("utf-8"))
            if py_exit_code != 0 or len(py_stderr) > 0:
                raise ValueError("Error in ZIMPL program. Exit code: %d.\n%s" % (py_exit_code, py_stderr))

        try:
            module = runpy.run_path(self.py_filename, run_name=__name__)
            self.program = module[os.path.basename(name_noext)]()
        except RecursionError as e:
            print(self.py_filename)
            self.unlink_files = False
            raise e

        self.vars = [v for v in self.program.variables.keys() if not v.startswith("__")]  # omit auxiliary variables

        if lp_process is not None:
            lp_exit_code = lp_process.wait()
            lp_stderr = str(lp_process.stderr.read().decode("utf-8"))
            if lp_exit_code != 0 or len(lp_stderr) > 0:
                # print(lp_stderr)
                raise ValueError("Error in ZIMPL program. Exit code: %d.\n%s" % (lp_exit_code, lp_stderr))

        self.lp_interpreter = LP_interpreter(self.lp_filename, self.vars)

    def sample(self, n: int, positive_only: bool = True, class_column: bool = False) -> pd.DataFrame:
        vars = self.vars
        X = pd.DataFrame(columns=vars)

        while X.shape[0] < n:
            new_X = pd.DataFrame()
            for v in vars:
                (domain, _min, _max) = self.program.variables[v]
                if domain == 'Z':
                    r = np.random.randint(_min, _max + 1, n)
                elif domain == 'R':
                    r = np.random.uniform(_min, _max, n)
                else:
                    raise NotImplementedError("Sampling for domain %s is not implemented." % domain)
                r = pd.DataFrame(r.reshape((n, 1)), columns=[v])
                new_X = pd.concat([new_X, r], axis=1)

            if class_column or positive_only:
                classes = self.program.constraints(new_X)
                if class_column:
                    new_X["class"] = classes
                if positive_only:
                    positive = new_X[classes]
                    if positive.shape[0] > 0:
                        X = X.append(positive[:min(n - X.shape[0], positive.shape[0])], ignore_index=True)
                        print("Found %d positives so far..." % X.shape[0])
            else:
                return new_X
        assert X.shape[0] == n
        return X

    def optimize(self):
        return self.lp_interpreter.optimize()

    def sample_positive(self, n: int):
        '''Samples positive examples using solver. Distribution of examples is unknown except that all are positive.
        This method does not work unless model contains integer variables.'''
        return self.lp_interpreter.sample_positive(n)

    def is_satisfied(self, X: pd.DataFrame):
        return self.lp_interpreter.is_satisfied(X, self.program)

    def generate_grammar(self):
        with open(os.path.dirname(__file__) + "/../../../grammars/ZIMPL-dedicated.bnf", "rt") as f:
            grammar = f.read()
        grammar = self.filter_grammar(grammar)
        return grammar

    def filter_grammar(self, grammar: str) -> str:
        output = defaultdict(lambda: [])
        output_grammar = ""

        globals = __import__("itertools", {}, {}, "*").__dict__
        globals["sprod"] = lambda s, r=1: ("".join(p) for p in globals["product"](s, repeat=r))
        globals["spermut"] = lambda s, r=None: ("".join(p) for p in globals["permutations"](s, r=r))
        globals["rule_exists"] = lambda nonterm: nonterm in output
        globals.update({"sets": self.program.sets, "vardefs": self.program.vardefs, "params": self.program.params})

        lines = grammar.split("\n")
        for lineno, line in enumerate(lines):
            try:
                code = Interpreter.code_regex.search(line)
                if code is not None:
                    exec(code["code"], globals)
                    line = Interpreter.comment_regex.sub("", line)

                enumerator = Interpreter.enumerator_regex.search(line)
                if enumerator is not None:
                    # print(enumerator["code"])
                    options = eval(enumerator["code"], globals)
                    candidates = (Interpreter.comment_regex.sub("", line) % option for option in options)

                    last_rule = ""
                    for candidate in candidates:
                        parts = candidate.split("::=")
                        if len(parts) > 0:
                            last_rule = parts[0].strip()
                        output[last_rule].append(parts[-1].strip())
                else:
                    output_grammar += line + "\n"
            except Exception as e:
                print(e, "in grammar line %d" % (lineno+1))
                raise e

        output_grammar = self.remove_singular_rules(output_grammar, output)
        grammar = "\n".join("%-24s::=%s" % (k, ("|\n" + " " * 27).join(v)) for k, v in output.items() if k != "")
        return Interpreter.empty_rule_regex.sub("", output_grammar + grammar)

    def remove_singular_rules(self, output_grammar: str, rules: dict):
        singular = {k: v for k, v in rules.items() if len(v) == 1 and "|" not in v[0]}
        for s_name, s_production in singular.items():
            del rules[s_name]
            assert len(s_production) == 1
            for productions in rules.values():
                for i in range(len(productions)):
                    productions[i] = productions[i].replace(s_name, s_production[0])
                    output_grammar = output_grammar.replace(s_name, s_production[0])
        return output_grammar

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        if self.unlink_files:
            for file in [self.py_filename, self.lp_filename, re.sub(r'\.lp$', '.tbl', self.lp_filename)]:
                try:
                    os.unlink(file)
                except:
                    pass


class LP_interpreter:
    gurobi_env = Env("")

    def __init__(self, lp_filename, vars):
        self.lp_filename = lp_filename
        self.vars = vars

    def optimize(self) -> dict:
        model = read(self.lp_filename, LP_interpreter.gurobi_env)
        model.optimize()

        if model.Status in Interpreter.feasible_status:
            gurobi_vars = [model.getVarByName(v) for v in self.vars if model.getVarByName(v) is not None]
            solution = {"": model.ObjVal}
            for j in range(len(gurobi_vars)):
                v = gurobi_vars[j]
                solution[v.varName] = v.Xn
            return solution
        else:
            return None


    def sample_positive(self, n: int):
        '''Samples positive examples using solver. Distribution of examples is unknown except that all are positive.
        This method does not work unless model contains integer variables.'''
        model = read(self.lp_filename, LP_interpreter.gurobi_env)
        model.Params.PoolSearchMode = 2
        model.Params.PoolSolutions = n  # we want at least n feasible solutions
        model.Params.SolutionLimit = n  # we want no more than n feasible solutions

        model.optimize()

        gurobi_vars = [model.getVarByName(v) for v in self.vars if model.getVarByName(v) is not None]
        vars = [v.varName for v in gurobi_vars]

        if model.Status in Interpreter.feasible_status:
            sol_count = model.SolCount
            X = pd.DataFrame(columns=vars, index=pd.RangeIndex(start=0, stop=sol_count), dtype=np.double)
            Xv = X.values
            for i in range(sol_count):
                model.Params.SolutionNumber = i
                for j in range(Xv.shape[1]):
                    v = gurobi_vars[j]
                    assert X.columns[j] == gurobi_vars[j]
                    Xv[i, j] = round(v.Xn) if v.VType in "BI" else v.Xn

            if X.shape[0] < n:
                print("Warning: feasible region consists of %d unique solutions; %d requested." % (X.shape[0], n), file=sys.stderr)
        else:
            X = pd.DataFrame(columns=vars, index=pd.RangeIndex(start=0, stop=0), dtype=np.double)
        assert X.shape[0] <= n, X.shape
        return X

    def is_satisfied(self, X: pd.DataFrame, py_program=None):
        if list(X.columns) == len(self.vars) and py_program is not None:  # if no auxiliary variables
            return py_program.constraints(X)

        # use solver
        model = read(self.lp_filename, LP_interpreter.gurobi_env)
        model.Params.PoolSolutions = 1
        model.Params.SolutionLimit = 1

        out = np.empty((X.shape[0]), dtype=np.uint16)

        gurobi_vars = [model.getVarByName(v) for v in X.columns] if len(model.getVars()) > 0 else [None for v in X.columns]

        Xv = X.values
        for i in range(Xv.shape[0]):
            for j in range(Xv.shape[1]):
                _var = gurobi_vars[j]
                if _var is None:
                    continue
                _var.LB = _var.UB = Xv[i, j]

            model.optimize()
            assert model.Status in {GRB.OPTIMAL, GRB.UNBOUNDED, GRB.SOLUTION_LIMIT, GRB.SUBOPTIMAL, GRB.INFEASIBLE, GRB.INF_OR_UNBD}, model.Status
            out[i] = model.Status in Interpreter.feasible_status  # does feasible solution exist?
            assert not out[i] or model.SolCount > 0

        return out

LP_interpreter.gurobi_env.setParam(GRB.Param.LogToConsole, 0)
LP_interpreter.gurobi_env.setParam(GRB.Param.Threads, 1)
LP_interpreter.gurobi_env.setParam(GRB.Param.TimeLimit, 600)  # 10 minutes - protection from hanging in model solving
