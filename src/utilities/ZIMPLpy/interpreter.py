import runpy
from collections import defaultdict

from psutil import Popen
import pandas as pd
import numpy as np
from gurobipy import *


class Interpreter:
    rule_regex = re.compile(r'^\s*<\S+>\s*::=')
    empty_rule_regex = re.compile(r'\s*<\S+>\s*::=\s*(?=\n\s*<\S+>\s*::=|$)')
    enumerator_regex = re.compile(r'\(=(?P<code>(?!\*\)).*)=\)')
    comment_regex = re.compile(r'#.*$')

    def __init__(self, zpl_filename, unlink_files=True, solver_based_sampling=True):
        base_dir = os.path.dirname(__file__)
        name_noext = re.sub(r"\.zpl$", r"", zpl_filename)

        py_process = Popen(["%s/../ZIMPL/bin/zimpl" % base_dir, "-v0", "-tpy", zpl_filename], cwd=os.path.dirname(name_noext))

        if solver_based_sampling:
            lp_process = Popen(["%s/../ZIMPL/bin/zimpl" % base_dir, "-v0", "-l99", "-tlp", zpl_filename], cwd=os.path.dirname(name_noext))

        self.py_filename = name_noext + ".py"
        self.lp_filename = name_noext + ".lp"
        self.unlink_files = unlink_files

        py_exit_code = py_process.wait()
        if py_exit_code != 0:
            raise ValueError("Error in ZIMPL program. Exit code: %d." % py_exit_code)

        module = runpy.run_path(self.py_filename)
        self.program = module[os.path.basename(name_noext)]()

        if solver_based_sampling:
            lp_exit_code = lp_process.wait()
            if lp_exit_code != 0:
                raise ValueError("Error in ZIMPL program. Exit code: %d." % lp_exit_code)

    def sample(self, n: int, positive_only: bool = True, class_column: bool = False) -> pd.DataFrame:
        vars = list(self.program.variables.keys())
        X = pd.DataFrame(columns=vars, dtype=np.double)

        while X.shape[0] < n:
            new_X = pd.DataFrame(dtype=np.double)
            for v, (domain, _min, _max) in self.program.variables.items():
                if domain == 'Z':
                    r = np.random.randint(_min, _max + 1, n)
                elif domain == 'R':
                    r = np.random.uniform(_min, _max, n)
                else:
                    raise NotImplementedError("Sampling for domain %s is not implemented." % domain)
                r = pd.DataFrame(r.reshape((n, 1)), columns=[v])
                new_X = pd.concat([new_X, r], axis=1)

            classes = self.program.constraints(new_X)
            # classes = new_X.apply(lambda row: self.program.constraints(**row.to_dict()), axis=1, reduce=True)
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
        model = read(self.lp_filename)
        # model.Params.LogToConsole = 0
        model.Params.PoolSearchMode = 2
        model.Params.MIPGap = 0
        model.Params.MIPGapAbs = 0

        model._vars = model.getVars()
        model._n = n
        model._X = []

        model.optimize(mycallback)
        assert model.Status in (GRB.OPTIMAL, GRB.UNBOUNDED, GRB.INTERRUPTED, GRB.SUBOPTIMAL)

        vars = list(self.program.variables.keys())
        X = pd.DataFrame(model._X, columns=vars, dtype=np.double)

        # it sometimes happens that solver does not terminate immediately after call to .terminate()
        if X.shape[0] > n:
            X = X.sample(n)

        assert X.shape[0] <= n, X.shape
        return X

    def generate_grammar(self):
        with open(os.path.dirname(__file__) + "/../../../grammars/ZIMPL-dedicated.bnf", "rt") as f:
            grammar = f.read()
        grammar = self.filter_grammar(grammar)
        # productions = self.generate_productions_for_symbol("variable", self.program.vardefs)
        # grammar += "".join(productions)
        # productions = self.generate_productions_for_set("set", self.program.sets, 2)
        # grammar += "".join(productions)
        # productions = self.generate_productions_for_symbol("param", self.program.params)
        # grammar += "".join(productions)

        return grammar

    def filter_grammar(self, grammar: str) -> str:
        globals = __import__("itertools", {}, {}, "*").__dict__
        globals["sprod"] = lambda s, r = 1: ("".join(p) for p in globals["product"](s, repeat=r))
        globals["spermut"] = lambda s, r = None: ("".join(p) for p in globals["permutations"](s, r=r))
        globals.update({"sets": self.program.sets, "vardefs": self.program.vardefs, "params": self.program.params})

        lines = grammar.split("\n")
        output = defaultdict(lambda: [])
        output_grammar = ""
        for line in lines:
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

        grammar = "\n".join("%-24s::=%s" % (k, ("|\n" + " "*27).join(v)) for k, v in output.items() if k != "")
        return Interpreter.empty_rule_regex.sub("", output_grammar + grammar)

    def generate_productions_for_symbol(self, name: str, collection: dict, max_index=3) -> dict:
        indexes = "ijklmno"[:max_index]
        productions = ["<%s_%s> ::=" % (name, indexes[:i]) for i in range(max_index + 1)]

        for symbol, properties in collection.items():
            for a in range(properties["arity"], max_index + 1):
                productions[a] += "'%s" % symbol
                if properties["arity"] > 0:
                    productions[a] += "['<index_%s_%d>']" % (indexes[:a], properties["arity"])
                productions[a] += "'|"
        for i in range(max_index + 1):
            if productions[i].endswith("::="):
                #productions[i] += "'%s'" % default_value
                productions[i] = ""
                # swapped = self.swap_keys(collection)
                # for a in range(i + 1, max_index + 1):
                #     if len(swapped[a]) > 0:
                #         productions[i] += "|".join("'%s['<index_%s_%d>']'" % (v, indexes[:i], arity) for v in swapped[a])
                #         break
            else:
                productions[i] = productions[i][:-1] + "\n"
        return productions

    def generate_productions_for_set(self, name: str, collection: dict, max_index=3) -> dict:
        indexes = "ijklmno"[:max_index]
        productions = ["<%s_%s_%d> ::=" % (name, indexes[:i], j) for i in range(max_index + 1) for j in range(1, max_index - i + 2)]

        for symbol, properties in collection.items():
            for i in range(properties["arity"], max_index - properties["value_arity"] + 2):
                # index = base_i + j
                # i  j    index  base_i
                # 0  1    0
                # 0  2    1
                # 0  mi+1 mi     -1
                # 1  1    mi+1
                # 1  2    mi+2
                # 1  mi   2mi    mi
                # 2  1    2mi+1
                # 2  2    2mi+2
                # 2  mi-1 3mi-1  2mi
                # 3  1    3mi
                # 3  2    3mi-1
                # 3  mi-2 4mi-3  3mi-1
                #                i*mi-0.5i^2-0.5i
                # index = i*mi-0.5i^2+1.5i-1 + j
                index = int(i * max_index - 0.5 * (i * i) + 1.5 * i - 1 + properties["value_arity"])
                assert properties["value_arity"] <= max_index - i + 1
                assert productions[index].startswith("<%s_%s_%d> ::=" % (name, indexes[:i], properties["value_arity"])), productions[index]

                productions[index] += "'%s" % symbol
                if properties["arity"] > 0:
                    productions[index] += "['<index_%s_%d>']" % (indexes[:index], properties["arity"])
                productions[index] += "'|"
        assert (max_index + 1) * max_index - 0.5 * (max_index + 1) ** 2 + 1.5 * (max_index + 1) == len(productions)
        for i, production in enumerate(productions):
            if production.endswith("::="):
                #productions[i] += "'%s'" % default_value
                productions[i] = ""
            else:
                productions[i] = production[:-1] + "\n"
        return productions

    def swap_keys(self, d: dict) -> defaultdict:
        d2 = defaultdict(lambda: [])
        for k, v in d.items():
            d2[v].append(k)
        return d2

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        if self.unlink_files:
            for file in [self.py_filename, self.lp_filename, re.sub(r'\.lp$', '.tbl', self.lp_filename)]:
                try:
                    os.unlink(file)
                except:
                    pass


def mycallback(model, where):
    if where == GRB.Callback.MIPSOL:
        x = model.cbGetSolution(model._vars)
        model._X.append({model._vars[i].varName: x[i] for i in range(len(x))})
        if len(model._X) >= 100 * model._n:
            model.terminate()
