import datetime
import os
import re
import sys
from tempfile import mkstemp
from traceback import format_tb
import inspect

import pandas as pd
import numpy as np

import stats
from algorithm.parameters import params
from fitness.base_ff_classes.base_ff import base_ff
from representation.individual import Individual
from stats.stats import stats as statistics
from utilities.ZIMPLpy.interpreter import Interpreter
from utilities.stats import file_io, trackers
import pyximport

from utilities.stats.experimentdatabase import *

os.environ["CFLAGS"] = "-O3 -march=native"
pyximport.install(language_level=3, inplace=True)

import fitness.helper as helper


class ZIMPL(base_ff):
    debug = params["DEBUG"]
    maximise = True
    database: Database = None
    experiment: Experiment = None
    prev_get_soo_stats = None

    def __init__(self):
        # Initialise base fitness function class.
        super().__init__()
        problem_name = params["PROBLEM"]
        base_dir = os.path.dirname(__file__)
        dataset_dir = base_dir + "/../../datasets/ZIMPL"
        self.zimpl_ground_truth_filename = "%s/%s.zpl" % (dataset_dir, problem_name)
        self.zimpl_template = self.load_template()
        with open(self.zimpl_ground_truth_filename, "rt") as f:
            self.ground_truth_phenotype = f.read()
        self.ground_truth_interpreter = Interpreter(self.zimpl_ground_truth_filename, not ZIMPL.debug)
        self.ground_truth_program = self.ground_truth_interpreter.program

        training_size = cast_int(params.get("TRAINING_SIZE"))
        test_size = cast_int(params.get("TEST_SIZE"))

        self.training_set = Evaluator("%s/%s_training.csv.bz2" % (dataset_dir, problem_name), training_size)
        self.test_set = Evaluator("%s/%s_test.csv.bz2" % (dataset_dir, problem_name), test_size)

        self.training_test = True
        self.vardefs = list(self.ground_truth_program.vardefs.keys())
        self.sets = list(self.ground_truth_program.sets.keys())
        self.params = list(self.ground_truth_program.params.keys())

        self.default_fitness = 0.0
        self.tmp_file_handle, self.tmp_filename = mkstemp(".zpl")

        statistics["GROUND_TRUTH_TRAINING_FITNESS"] = self.training_set.fitness(self.ground_truth_interpreter, self.ground_truth_phenotype)
        statistics["GROUND_TRUTH_TEST_FITNESS"] = self.test_set.fitness(self.ground_truth_interpreter, self.ground_truth_phenotype)

    def load_template(self):
        with open(self.zimpl_ground_truth_filename) as f:
            tpl = f.read()
        return re.sub(r'#+\sEND\sOF\sTEMPLATE\s#+.*$', "", tpl, flags=re.I | re.S)

    def evaluate(self, ind: Individual, **kwargs):
        if ind.phenotype is None:
            ind.invalid = True
            return self.default_fitness

        dist = kwargs.get('dist', 'training')
        if dist == "training":
            data = self.training_set
        elif dist == "test":
            data = self.test_set
        else:
            raise ValueError("Unknown dist: " + dist)

        program = self.format_program(ind.phenotype)

        try:
            os.write(self.tmp_file_handle, program.encode("utf-8"))
            # os.fsync(self.tmp_file_handle) # no buffering

            with Interpreter(self.tmp_filename, not ZIMPL.debug) as interpreter:
                return data.fitness(interpreter, program)

        except ValueError as e:
            # if "Error 168" in str(e):
            #     print("program=%s\nerror=%s" % (program, str(e)))
            #     breakpoint()
            if "Error 142" not in str(e):
                print(e, file=sys.stderr)
            ind.runtime_error = True
            return self.default_fitness
        finally:
            os.lseek(self.tmp_file_handle, 0, 0)
            os.ftruncate(self.tmp_file_handle, 0)

    def format_program(self, phenotype):
        return self.zimpl_template + ZIMPL.set_names(phenotype)

    @staticmethod
    def set_names(phenotype):
        name_pos = 0
        name_len = len("name_seq")
        for i in range(1, 999999):
            name_pos = phenotype.find("name_seq", name_pos)
            if name_pos < 0:
                break
            new_name = "constraint%d" % i
            phenotype = phenotype[:name_pos] + new_name + phenotype[name_pos + name_len:]
            name_pos += len(new_name)
        return phenotype

    @staticmethod
    def confusion_matrix(data, program):
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

    @staticmethod
    def save_best_ind_to_file(_stats, ind, end=False, name="best"):
        prev_phenotype = ind.phenotype
        ind.phenotype = params["FITNESS_FUNCTION"].format_program(prev_phenotype)
        file_io.save_best_ind_to_file(_stats, ind, end, name)
        ind.phenotype = prev_phenotype

    @staticmethod
    def init_experimentdatabase():
        if ZIMPL.database is not None:
            return
        ZIMPL.database = Database(params["EXPERIMENT_DATABASE"])
        ZIMPL.experiment = ZIMPL.database.new_experiment()
        ZIMPL.experiment["timestamp"] = str(datetime.datetime.now())
        ZIMPL.experiment["commandline"] = " ".join(sys.argv)
        for k, v in statistics.items():
            if k.startswith("GROUND"):
                ZIMPL.experiment[k] = v
        parameters = ZIMPL.experiment.new_child_data_set("parameters")
        parameters.update({str(k): str(v) for k, v in params.items()})

    @staticmethod
    def get_soo_stats(individuals, end):
        ZIMPL.prev_get_soo_stats(individuals, end)  # calculate statistics

        generation = ZIMPL.experiment.new_child_data_set("generations")
        generation.update({k: v for k, v in statistics.items() if not k.startswith("GROUND")})
        generation["best_phenotype"] = params["FITNESS_FUNCTION"].format_program(trackers.best_ever.phenotype)
        generation["test_fitness"] = params["FITNESS_FUNCTION"].evaluate(trackers.best_ever, dist="test")
        generation["end"] = end
        if end:
            ZIMPL.experiment.save(True)
            ZIMPL.experiment = None
            ZIMPL.database.__exit__(None, None, None)

    @staticmethod
    def except_hook(exctype, value, tb):
        if ZIMPL.experiment is not None:
            ZIMPL.experiment["error_exctype"] = exctype.__name__
            ZIMPL.experiment["error_value"] = str(value)
            ZIMPL.experiment["error_tb"] = "".join(format_tb(tb))
            ZIMPL.experiment.save()
        ZIMPL.prev_excepthook(exctype, value, tb)


class Evaluator:
    def __init__(self, dataset_filename, size):
        self.data = self.load_dataset(dataset_filename, size)

    def load_dataset(self, filename, size):
        set = pd.read_csv(filename, index_col=False, engine='c', na_filter=False, dtype=np.double)
        if size is not None and set.shape[0] > size:
            set = set.sample(size)
            set.reset_index(inplace=True, drop=True)
        return set

    def fitness(self, interpreter, phenotype):
        recall = self.recall(interpreter)
        if recall < 1e-6:
            return 0.0
        precision = self.precision(interpreter)
        return 2 * recall * precision / (recall + precision) - 1e-6 * len(phenotype)

    def recall(self, interpreter):
        assert "class" not in self.data.columns or self.data["class"].all(), self.data
        tp = interpreter.is_satisfied(self.data).sum()
        fn = self.data.shape[0] - tp
        assert 0 <= tp <= self.data.shape[0]
        assert 0 <= fn <= self.data.shape[0]
        return tp / (tp + fn)

    def precision(self, interpreter):
        assert "class" not in self.data.columns or self.data["class"].all(), self.data
        P: pd.DataFrame = interpreter.sample_positive(self.data.shape[0])
        if P.shape[1] < self.data.shape[1]:
            for c in self.data.columns:
                if c not in P.columns:
                    P[c] = 0.0
            P = P[self.data.columns]
        assert P.shape[1] == self.data.shape[1]
        assert all(a == b for a, b in zip(P.columns, self.data.columns))
        return helper.precision(self.data.values, P.values)


def cast_int(x):
    if x is None:
        return None
    return int(x)


# patching extra parameters
# we assume --extra_parameters is a comma-separated kv sequence, eg:
# "alpha=0.5, beta=0.5, gamma=0.5"
# which we can pass to the dict() constructor
if 'EXTRA_PARAMETERS' in params:
    extra_params = eval("dict(" + "".join(params['EXTRA_PARAMETERS']) + ")")
    params.update(extra_params)


# monkey patching statistics to write formatted programs
if any("ponyge.py" in frame.filename for frame in inspect.stack()):
    stats.stats.save_best_ind_to_file = ZIMPL.save_best_ind_to_file
    # monkey patching statistics to write experiment database
    if ZIMPL.prev_get_soo_stats is None:
        ZIMPL.prev_get_soo_stats = stats.stats.get_soo_stats
        stats.stats.get_soo_stats = ZIMPL.get_soo_stats
    ZIMPL.init_experimentdatabase()
    ZIMPL.prev_excepthook = sys.excepthook
    sys.excepthook = ZIMPL.except_hook

