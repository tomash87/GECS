import runpy, os, re, platform
from collections import defaultdict
from subprocess import PIPE, TimeoutExpired

from numpy.random.mtrand import RandomState
from psutil import Popen
import pandas as pd
import numpy as np
from gurobipy import *


class Interpreter:
    feasible_status = frozenset({GRB.OPTIMAL, GRB.UNBOUNDED, GRB.SOLUTION_LIMIT, GRB.SUBOPTIMAL})
    infeasible_status = frozenset({GRB.INFEASIBLE, GRB.INF_OR_UNBD})
    base_dir = os.path.dirname(__file__)
    zimpl_path = os.path.abspath("%s/../ZIMPL/bin/zimpl" % os.path.dirname(__file__) + (".exe" if platform.system() == "Windows" else ""))
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

        py_process = Popen([Interpreter.zimpl_path, "-v0", "-tpy", zpl_filename], cwd=working_dir, stderr=PIPE) if not os.path.exists(self.py_filename) or zpl_mtime > os.path.getmtime(
            self.py_filename) else None
        lp_process = Popen([Interpreter.zimpl_path, "-v0", "-l99", "-tlp", zpl_filename], cwd=working_dir, stderr=PIPE) if not os.path.exists(self.lp_filename) or zpl_mtime > os.path.getmtime(
            self.lp_filename) else None

        self.unlink_files = unlink_files

        if py_process is not None:
            try:
                py_exit_code = py_process.wait(timeout=30)
                py_stderr = str(py_process.stderr.read().decode("utf-8"))
            except TimeoutExpired:
                py_process.kill()
                py_exit_code = -1
                py_stderr = ""
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
            try:
                lp_exit_code = lp_process.wait(timeout=30)
                lp_stderr = str(lp_process.stderr.read().decode("utf-8"))
            except TimeoutExpired:
                lp_process.kill()
                lp_exit_code = -1
                lp_stderr = ""
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

    def sample_positive(self, n: int, method: str, budget: int = 1000, convert_to_int: bool = False, seed: int = None):
        '''Samples positive examples using solver. Distribution of examples is unknown except that all are positive.
        This method does not work unless model contains integer variables.'''
        return self.lp_interpreter.sample_positive(n, method, budget, convert_to_int, seed)

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
        globals["rule_exists"] = lambda nonterm, min_count=1: nonterm in output and len(output[nonterm]) >= min_count
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
                elif "::=" in line:
                    parts = line.split("::=")
                    if len(parts) > 0:
                        output[parts[0].strip()].append(parts[-1].strip())
                else:
                    output_grammar += line + "\n"
            except Exception as e:
                print(e, "in grammar line %d" % (lineno + 1))
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
    pinf = float("inf")
    ninf = float("-inf")
    max_fails = 5
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

    def sample_positive(self, n: int, method: str, budget: int, convert_to_int: bool, seed: int = None):
        if method == 'bc':
            return self.sample_positive_branch_and_cut(n, convert_to_int)
        elif method == 'har':
            return self.sample_positive_hit_and_run(n, budget, seed)
        raise Exception("Unrecognized method: %s" % method)

    def sample_positive_branch_and_cut(self, n: int, convert_to_int: bool):
        """Samples positive examples using solver. Distribution of examples is unknown except that all are positive.
        This method does not work unless model contains integer variables."""
        model = read(self.lp_filename, LP_interpreter.gurobi_env)
        model.Params.PoolSearchMode = 2
        model.Params.PoolSolutions = n  # we want at least n feasible solutions
        model.Params.SolutionLimit = n  # we want no more than n feasible solutions

        gurobi_vars = [model.getVarByName(v) for v in self.vars if model.getVarByName(v) is not None]
        continuous_vars = set()
        if convert_to_int:
            for v in gurobi_vars:
                if v.VType == GRB.CONTINUOUS:
                    continuous_vars.add(v)
                    v.VType = GRB.INTEGER
            model.update()

        vars = [v.varName for v in gurobi_vars]
        milp = any(v.VType in "BI" for v in gurobi_vars)

        model.optimize()

        if model.Status in Interpreter.feasible_status:
            sol_count = model.SolCount
            X = pd.DataFrame(columns=vars, index=pd.RangeIndex(start=0, stop=sol_count), dtype=np.double)
            Xv = X.values
            for i in range(sol_count):
                model.Params.SolutionNumber = i
                for j in range(Xv.shape[1]):
                    v = gurobi_vars[j]
                    assert X.columns[j] == gurobi_vars[j]
                    val = v.Xn if milp else v.X
                    Xv[i, j] = round(val) if v.VType in "BI" else val

            if X.shape[0] < n:
                print("Warning: feasible region consists of %d unique solutions; %d requested." % (X.shape[0], n), file=sys.stderr)
        else:
            X = pd.DataFrame(columns=vars, index=pd.RangeIndex(start=0, stop=0), dtype=np.double)
        assert X.shape[0] <= n, X.shape

        if convert_to_int:
            for v in continuous_vars:
                v.VType = GRB.CONTINUOUS
            model.update()

        return X

    def sample_positive_hit_and_run(self, n: int, budget: int, seed: int = None):
        """Samples uniformly distributed positive examples from feasible region using Hit-and-Run algorithm."""
        if seed is not None:
            random_state = np.random.get_state()
            np.random.set_state(RandomState(seed))

        fails = 0

        model: Model = read(self.lp_filename, LP_interpreter.gurobi_env)
        model.Params.PoolSolutions = 1  # do not use solution pool

        gurobi_vars = [model.getVarByName(v) for v in self.vars if model.getVarByName(v) is not None]
        vars = [v.varName for v in gurobi_vars]
        int_vars = {v: v.VType for v in gurobi_vars if v.VType != GRB.CONTINUOUS}
        assert len(vars) == len(gurobi_vars)
        # optimization: call once/allocate memory once
        len_vars = len(vars)
        len_vars_tuple = (len_vars,)
        len_int_vars = len(int_vars)

        def relax_ints():
            for v in int_vars.keys():
                v.VType = GRB.CONTINUOUS

        def restore_ints():
            for v, t in int_vars.items():
                v.VType = t

        source_point = np.empty(len_vars_tuple, dtype=np.double)
        source_point = LP_interpreter.find_extreme_point(model, gurobi_vars, source_point)

        if source_point is None:
            return pd.DataFrame(columns=vars, index=pd.RangeIndex(start=0, stop=0), dtype=np.double)

        def handle_new_fail():
            nonlocal fails, source_point
            fails += 1
            if fails >= LP_interpreter.max_fails:
                # start over with new random point
                fails = 0
                source_point = LP_interpreter.find_extreme_point(model, gurobi_vars, source_point)
                assert source_point is not None

        X = pd.DataFrame(columns=vars, index=pd.RangeIndex(start=0, stop=n), dtype=np.double)
        Xv = X.values

        # create auxiliary delta and diff variables
        _lambda = model.addVar(LP_interpreter.ninf, LP_interpreter.pinf, 0.0, GRB.CONTINUOUS, "_lambda")
        delta_variables = [model.addVar(LP_interpreter.ninf, LP_interpreter.pinf, 0.0, GRB.CONTINUOUS, v.VarName + "_DELTA") for v in gurobi_vars]
        diff_variables = [model.addVar(LP_interpreter.ninf, LP_interpreter.pinf, 0.0, GRB.CONTINUOUS, v.VarName + "_DIFF") for v in gurobi_vars]

        random_point = np.empty(len_vars_tuple, dtype=np.double)

        # optimization: allocate memory once
        on_line_constraints = [None] * len_vars
        distance_diff_constraints = [None] * len_vars
        distance_delta_constraints = [None] * len_vars
        sum_delta_variables = quicksum(delta_variables)
        dup_matrix = np.empty((n, len_vars), dtype=np.bool)
        dup_vector = np.empty(n, dtype=np.bool)

        i = 0
        while i < n and budget > 0:
            budget -= 1

            random_direction = np.random.uniform(-1.0, 1.0, len_vars_tuple)
            for j, v in enumerate(gurobi_vars):
                on_line_constraints[j] = model.addConstr(v, GRB.EQUAL, source_point[j] + random_direction[j] * _lambda)

            # get bounds by maximizing and minimizing
            relax_ints()

            # maximize
            model.setObjective(_lambda, GRB.MAXIMIZE)
            model.optimize()
            if model.Status not in Interpreter.feasible_status:
                lambda_max = 0.0
            elif model.Status == GRB.UNBOUNDED:
                lambda_max = 1e6
            else:
                assert model.Status in Interpreter.feasible_status
                assert np.all([(abs(source_point[j] + random_direction[j] * _lambda.X - v.X) < 1e-6 for j, v in enumerate(gurobi_vars))])
                lambda_max = _lambda.X

            # minimize
            model.ModelSense = GRB.MINIMIZE
            model.optimize()
            if model.Status not in Interpreter.feasible_status:
                lambda_min = 0.0
            elif model.Status == GRB.UNBOUNDED:
                lambda_min = -1e6
            else:
                assert model.Status in Interpreter.feasible_status
                assert np.all([(abs(source_point[j] + random_direction[j] * _lambda.X - v.X) < 1e-6 for j, v in enumerate(gurobi_vars))])
                lambda_min = _lambda.X

            restore_ints()

            # drop extra constraints
            model.remove(on_line_constraints)

            # the first time lambda_min == lambda_max may be the case where source_point is brand new
            if fails > 0 and lambda_min == lambda_max:
                handle_new_fail()
                continue
            # elif lambda_min != lambda_max:
            #     print("lambda_min: %f, lambda_max: %f" % (lambda_min, lambda_max))

            # draw a random point on this line
            r = np.random.uniform(lambda_min, lambda_max)
            np.multiply(r, random_direction, out=random_point)
            np.add(source_point, random_point, out=random_point)

            if len_int_vars > 0:
                # find the closest feasible point
                # use delta variables to measure distance of a feasible solution to random_point
                for j, v in enumerate(gurobi_vars):
                    distance_diff_constraints[j] = model.addConstr(diff_variables[j], GRB.EQUAL, v - random_point[j])
                    distance_delta_constraints[j] = model.addGenConstrAbs(delta_variables[j], diff_variables[j])

                # minimize distance
                model.setObjective(sum_delta_variables, GRB.MINIMIZE)
                model.optimize()
                assert model.Status in Interpreter.feasible_status
                assert np.all(dv.X >= -1e-6 for dv in delta_variables)

                # solution to this model is our example
                for j, v in enumerate(gurobi_vars):
                    random_point[j] = round(v.X) if v.VType in "BI" else v.X

                # clean up
                model.remove(distance_diff_constraints)
                model.remove(distance_delta_constraints)

            if np.equal(Xv, random_point, out=dup_matrix).all(1, out=dup_vector).any():
                handle_new_fail()
            else:
                fails = 0
                Xv[i] = random_point
                source_point[:] = random_point
                print("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bProgress: %d/%d" % (i, n), end="")
                i += 1

        if i < n:
            # budget exceeded; shrink X
            print("budget exceeded")
            X = X[:i]

        if seed is not None:
            np.random.set_state(random_state) # return previous state of the random generator

        print("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", end="")
        return X

    @staticmethod
    def find_extreme_point(model: Model, gurobi_vars: list, source_point: np.ndarray):
        # random objective
        obj = quicksum(np.random.uniform(-1.0, 1.0) * v for v in gurobi_vars)

        model.setObjective(obj, GRB.MINIMIZE)
        model.optimize()
        if model.Status in Interpreter.infeasible_status:
            return None

        for i, v in enumerate(gurobi_vars):
            source_point[i] = round(v.X) if v.VType in "BI" else v.X

        return source_point

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
