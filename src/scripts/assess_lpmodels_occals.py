import re
import sqlite3
import os
import tempfile

from fitness.ZIMPL import Evaluator
from utilities.ZIMPLpy.interpreter import LP_interpreter, Interpreter
from utilities.stats.experimentdatabase import Database

def get_problem(filename):
    match = re.search(r'([a-zA-Z0-9_]+)_training', filename)
    if match is not None:
        return match[1]

def get_fitness(lp_format, problem):
    fd, lp_filename = tempfile.mkstemp(".lp")
    try:
        evaluator = Evaluator("../../datasets/ZIMPL/%s_test.csv" % problem, 2000)

        os.write(fd, lp_format.encode("utf-8"))  # no buffering
        lp_interpreter = LP_interpreter(lp_filename, list(evaluator.data.columns))

        return evaluator.fitness(lp_interpreter, lp_format)
    finally:
        os.close(fd)
        os.unlink(lp_filename)


def get_phenotype(problem, lp_format: str):
    benchmark = Interpreter("../../datasets/ZIMPL/%s.zpl" % problem, False)
    bounds = ""
    generals = ""
    for name, (domain, _min, _max) in benchmark.program.variables.items():
        bounds += "%f <= %s <= %f\n" % (_min, name, _max)
        if domain == 'Z':
            generals += "%s\n" % name

    if lp_format.find("Bounds") >= 0:
        lp_format = lp_format.replace("Bounds", "Bounds\n" + bounds)
    elif lp_format.find("Binary") >= 0:
        lp_format = lp_format.replace("Binary", "Bounds\n" + bounds + "Binary")
    else:
        lp_format = lp_format.replace("End", "Bounds\n" + bounds + "End")

    if lp_format.find("Generals") >= 0:
        lp_format = lp_format.replace("Generals", "Generals\n" + generals)
    else:
        lp_format = lp_format.replace("End", "Generals\n" + generals + "End")
    return lp_format


def main():
    problems = ["chvatal_diet", "facility_location", "queens1", "queens2", "queens3", "queens4", "queens5", "steinerbaum", "tsp"]
    training_size = {p: 400 for p in problems}
    training_size["queens1"] = 92
    training_size["steinerbaum"] = 53

    source_db_filename = "../../results/stats.sqlite"
    destination_db_filename = "../../results/results.sqlite"

    experiment_name = "OCCALS"

    source_db_conn = sqlite3.connect(source_db_filename)
    source_cursor = source_db_conn.cursor()
    source_cursor.execute("SELECT inputFile, trainingDataSize, seed, LPFormat FROM experiments")

    destination_db = Database(destination_db_filename)

    for row in source_cursor:
        problem = get_problem(row[0])
        phenotype = get_phenotype(problem, row[3])
        assert row[1] == training_size[problem] or row[1] == 400

        exp = destination_db.new_experiment()
        params = exp.new_child_data_set("parameters")
        params["EXPERIMENT_NAME"] = experiment_name
        params["PROBLEM"] = problem
        params["TRAINING_SIZE"] = training_size[problem]
        params["RANDOM_SEED"] = row[2]
        gen = exp.new_child_data_set("generations")
        gen["end"] = 1
        gen["best_phenotype"] = phenotype
        gen["test_fitness"] = get_fitness(phenotype, problem)

        exp.save()


if __name__ == '__main__':
    main()

