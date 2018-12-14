import re
from os import getcwd
from tempfile import mkstemp

import pandas as pd
import os

from algorithm.parameters import params
from fitness.base_ff_classes.base_ff import base_ff
from stats.stats import stats
from utilities.ZIMPLpy.interpreter import Interpreter


class ZIMPL(base_ff):
    debug = params["DEBUG"]
    maximise = True
    var_regex = re.compile(r'VAR(?P<n>\d+)')
    set_regex = re.compile(r'SET(?P<n>\d+)')
    param_regex = re.compile(r'PARAM(?P<n>\d+)')

    def __init__(self):
        # Initialise base fitness function class.
        super().__init__()
        problem_name = params["PROBLEM"]
        base_dir = os.path.dirname(__file__)
        dataset_dir = base_dir + "/../../datasets/ZIMPL"
        self.zimpl_ground_truth_filename = "%s/%s.zpl" % (dataset_dir, problem_name)
        self.zimpl_template = self.load_template()
        with Interpreter(self.zimpl_ground_truth_filename, not ZIMPL.debug, False) as interpreter:
            self.ground_truth_program = interpreter.program

        training_size = cast_int(params.get("TRAINING_SIZE"))
        test_size = cast_int(params.get("TEST_SIZE"))
        validation_size = cast_int(params.get("VALIDATION_SIZE"))

        self.training_set = pd.read_csv("%s/%s_training.csv.bz2" % (dataset_dir, problem_name), index_col=False, nrows=training_size)
        self.test_set = pd.read_csv("%s/%s_test.csv.bz2" % (dataset_dir, problem_name), index_col=False, nrows=test_size)
        self.validation_set = pd.read_csv("%s/%s_validation.csv.bz2" % (dataset_dir, problem_name), index_col=False, nrows=validation_size)

        assert len(self.training_set) == training_size or len(self.training_set) > 0 and training_size is None
        assert len(self.test_set) == test_size or len(self.test_set) > 0 and test_size is None
        assert len(self.validation_set) == validation_size or len(self.validation_set) > 0 and validation_size is None

        self.training_test = True
        self.vardefs = list(self.ground_truth_program.vardefs.keys())
        self.sets = list(self.ground_truth_program.sets.keys())
        self.params = list(self.ground_truth_program.params.keys())

        self.default_fitness = 0.0
        # self.n_vars = len(self.vardefs)
        # self.n_is = len(self.sets)
        # self.n_os = len(self.params)

        self.tmp_file_handle, self.tmp_filename = mkstemp(".zpl")

        stats["GROUND_TRUTH_TRAINING_FITNESS"] = self.fitness(self.training_set, self.ground_truth_program)
        stats["GROUND_TRUTH_TEST_FITNESS"] = self.fitness(self.test_set, self.ground_truth_program)

    def load_template(self):
        with open(self.zimpl_ground_truth_filename) as f:
            tpl = f.read()
        return re.sub(r'#+\sEND\sOF\sTEMPLATE\s#+.*$', "", tpl, flags=re.I | re.S)

    def evaluate(self, ind, **kwargs):
        if ind.phenotype is None:
            return self.default_fitness

        dist = kwargs.get('dist', 'training')
        if dist == "training":
            data = self.training_set
        elif dist == "test":
            data = self.test_set
        else:
            raise ValueError("Unknown dist: " + dist)

        if not ind.phenotype.startswith(self.zimpl_template):
            ind.phenotype = self.set_names(ind.phenotype)
            # ind.phenotype = self.set_symbols(phenotype, self.var_regex, self.vardefs)
            # ind.phenotype = self.set_symbols(phenotype, self.set_regex, self.sets)
            # ind.phenotype = self.set_symbols(phenotype, self.param_regex, self.params)
            ind.phenotype = self.zimpl_template + ind.phenotype

        try:
            os.write(self.tmp_file_handle, ind.phenotype.encode("utf-8"))
            # os.fsync(self.tmp_file_handle) # no buffering

            with Interpreter(self.tmp_filename, not ZIMPL.debug, False) as interpreter:
                return self.fitness(data, interpreter.program)

        except ValueError as e:
            print(e)
            return self.default_fitness
        finally:
            os.lseek(self.tmp_file_handle, 0, 0)
            os.ftruncate(self.tmp_file_handle, 0)

    def fitness(self, data, program):
        recall = self.recall(data, program)
        probability = self.probability(self.validation_set, program)
        # return recall - probability
        # return 2 * recall / (recall * probability + 1)  # 2pr/(p+r) = 2r/Pr(f(x)=1)/(1/Pr(f(x)=1)+r) = 2r/(1+r*Pr(f(x)=1))
        return recall / (recall * probability + 0.5)  # 2pr/(p+r) = 2rc/Pr(f(x)=1)/(c/Pr(f(x)=1)+r) = 2rc/(c+r*Pr(f(x)=1)) # c = 0.5

    def set_names(self, phenotype):
        name_pos = 0
        name_len = len("name_seq")
        for i in range(999999):
            name_pos = phenotype.find("name_seq", name_pos)
            if name_pos < 0:
                break
            new_name = "constraint%d" % i
            phenotype = phenotype[:name_pos] + new_name + phenotype[name_pos + name_len:]
            name_pos += len(new_name)
        return phenotype

    def set_symbols(self, phenotype, regex, symbols):
        return regex.sub(lambda match: symbols[int(match.group('n'))], phenotype)

    def recall(self, data, program):
        outcomes: pd.DataFrame = program.constraints(data)
        tp = outcomes.sum()
        fn = outcomes.shape[0] - tp
        assert 0 <= tp <= outcomes.shape[0]
        assert 0 <= fn <= outcomes.shape[0]
        return tp / (tp + fn)

    def probability(self, data, program):
        outcomes: pd.DataFrame = program.constraints(data)
        p = outcomes.sum()
        assert 0 <= p <= outcomes.shape[0]
        return p / data.shape[0]

    def confusion_matrix(self, data, program):
        tp = fp = tn = fn = 0
        for i, row in data.iterrows():
            outcome = program.constraints(**row.to_dict())
            if row.get("class", True):
                if outcome:
                    tp += 1
                else:
                    fn += 1
            else:
                if outcome:
                    fp += 1
                else:
                    tn += 1
        return tp, fp, tn, fn


def cast_int(x):
    if x is None:
        return None
    return int(x)
