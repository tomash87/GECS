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
    gurobi_env = Env("")

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

    def sample_positive(self, n: int):
        '''Samples positive examples using solver. Distribution of examples is unknown except that all are positive.
        This method does not work unless model contains integer variables.'''
        model = read(self.lp_filename, Interpreter.gurobi_env)
        model.Params.PoolSearchMode = 2
        model.Params.PoolSolutions = n  # we want at least n feasible solutions
        model.Params.SolutionLimit = n  # we want no more than n feasible solutions

        vars = self.vars

        model.optimize()
        if model.Status in Interpreter.feasible_status:
            sol_count = model.SolCount
            gurobi_vars = [model.getVarByName(v) for v in vars]
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

    def is_satisfied(self, X: pd.DataFrame):
        if list(X.columns) == self.program.variables:  # if no auxiliary variables
            return self.program.constraints(X)

        # use solver
        model = read(self.lp_filename, Interpreter.gurobi_env)
        model.Params.PoolSolutions = 1
        model.Params.SolutionLimit = 1

        out = np.empty((X.shape[0]), dtype=np.uint16)

        gurobi_vars = [model.getVarByName(v) for v in X.columns] if len(self.vars) > 0 else [None for v in X.columns]

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

    def estimate_volume_precise(self):
        vars = self.vars
        if len(vars) == 0:
            return 1

        model: Model = read(self.lp_filename, Interpreter.gurobi_env)
        total_integer_solutions = 1
        for v in vars:
            var = model.getVarByName(v)
            if var.VType not in "BI":
                var.VType = "I"     # convert all variables to integer
            domain, _min, _max = self.program.variables[v]
            total_integer_solutions *= _max - _min + 1

        model.Params.PoolSearchMode = 2
        model.Params.PoolSolutions = 100000
        model.Params.SolutionLimit = 100000
        model.optimize()

        return model.SolCount / total_integer_solutions

    def estimate_volume(self):
        vars = self.vars
        if len(vars) == 0:
            return 1

        model: Model = read(self.lp_filename, Interpreter.gurobi_env)

        model.Params.PoolSolutions = 1
        model.setObjective(quicksum(model.getVarByName(v) for v in vars))
        model.optimize()
        if model.Status in Interpreter.infeasible_status:
            return 0
        solutions = [[model.getVarByName(v).x for v in vars]]
        model.ModelSense *= -1
        model.optimize()
        solutions.append([model.getVarByName(v).x for v in vars])
        model.setObjective(quicksum((-1) ** i * model.getVarByName(v) for i, v in enumerate(vars)))
        model.optimize()
        solutions.append([model.getVarByName(v).x for v in vars])
        model.ModelSense *= -1
        model.optimize()
        solutions.append([model.getVarByName(v).x for v in vars])

        # monte carlo estimation
        n = 2000
        X = pd.DataFrame()
        sample_box_volume = 1
        bbox_volume = 1
        for i, v in enumerate(vars):
            domain, d_min, d_max = self.program.variables[v]
            _min = min(solution[i] for solution in solutions)
            _max = max(solution[i] for solution in solutions)
            sample_box_volume *= max(_max - _min, 1)
            bbox_volume *= max(d_max - d_min, 1)
            if domain == 'Z':
                X[v] = np.random.randint(_min, _max + 1, n)
            elif domain == 'R':
                X[v] = np.random.uniform(_min, _max, n)
            else:
                raise NotImplementedError("Sampling for domain %s is not implemented." % domain)
        X.drop_duplicates(inplace=True)
        X.reset_index(inplace=True, drop=True)
        out = self.is_satisfied(X)

        p = out.sum() / X.shape[0] * sample_box_volume / bbox_volume
        assert 0 <= p <= 1, p
        return p

    def estimate_volume_hypercube(self):
        vars = self.vars
        if len(vars) == 0:
            return 1

        model: Model = read(self.lp_filename, Interpreter.gurobi_env)

        model.Params.PoolSolutions = 1
        if model.getObjective().size() == 0:  # no objective
            model.setObjective(quicksum(model.getVarByName(v) for v in vars))
        model.optimize()
        if model.Status in Interpreter.infeasible_status:
            return 0
        solution = [model.getVarByName(v).x for v in vars]
        model.ModelSense *= -1
        model.optimize()
        solution2 = [model.getVarByName(v).x for v in vars]

        # add auxiliary variables
        length = model.addVar()
        divergence = model.addVars(len(vars), lb=-GRB.INFINITY)
        abs_divergence = model.addVars(len(vars))
        model.update()
        # add auxiliary constraints that resemble hypercube with one vertex in the optimal solution
        div_constr = model.addConstrs(divergence[i] == model.getVarByName(v) - solution[i] for i, v in enumerate(vars))
        model.addConstrs(abs_d == abs_(d) for abs_d, d in zip(abs_divergence.values(), divergence.values()))
        model.addConstr(quicksum(abs_d for abs_d in abs_divergence.values()) >= len(vars) * length)
        # set new objective to maximize edge length
        model.setObjective(length, sense=GRB.MAXIMIZE)
        model.optimize()
        avg_length = length.x
        # L1_distance = sum(abs_d.x for abs_d in abs_divergence.values())

        model.remove(div_constr)
        model.addConstrs(divergence[i] == model.getVarByName(v) - solution2[i] for i, v in enumerate(vars))
        model.optimize()
        avg_length2 = length.x
        # L1_distance2 = sum(abs_d.x for abs_d in abs_divergence.values())

        bbox_volume = 1
        # max_L1_distance = 0
        for v in vars:
            domain, _min, _max = self.program.variables[v]
            maxmin = _max - _min
            bbox_volume *= maxmin
            # max_L1_distance += maxmin

        assert avg_length ** len(vars) <= bbox_volume + 1e-6, (avg_length ** len(vars), bbox_volume)
        assert avg_length2 ** len(vars) <= bbox_volume + 1e-6, (avg_length2 ** len(vars), bbox_volume)
        # assert L1_distance <= max_L1_distance, (L1_distance, max_L1_distance)
        p = (avg_length ** len(vars) + avg_length2 ** len(vars)) / (2 * bbox_volume)
        # return (L1_distance + L1_distance2) / (2 * max_L1_distance)
        # p = 0.25 * ((avg_length ** len(vars) + avg_length2 ** len(vars)) / bbox_volume + (L1_distance + L1_distance2) / max_L1_distance)

        if p < 0.001:
            p2 = self.estimate_volume_precise()
            return min(0.001, p2)  # guarantee monotonicity
        return p

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


Interpreter.gurobi_env.setParam(GRB.Param.LogToConsole, 0)
Interpreter.gurobi_env.setParam(GRB.Param.Threads, 1)
