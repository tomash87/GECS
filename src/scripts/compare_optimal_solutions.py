import os
import sqlite3
import tempfile
from gurobipy import *
import pandas as pd

from fitness.ZIMPL import Evaluator
from utilities.ZIMPLpy.interpreter import Interpreter, LP_interpreter


def zpl_get_optimal_solution(zimpl: str):
    fd, zpl_filename = tempfile.mkstemp(".zpl")
    try:
        os.write(fd, zimpl.encode("utf-8"))  # no buffering
        interpreter = Interpreter(zpl_filename)

        return interpreter.optimize()
    except ValueError:
        return None
    finally:
        os.close(fd)
        os.unlink(zpl_filename)


def lp_get_optimal_solution(lp_format: str, problem):
    fd, lp_filename = tempfile.mkstemp(".lp")
    try:
        evaluator = Evaluator("../../datasets/ZIMPL/%s_test.csv" % problem, 2000)

        os.write(fd, lp_format.encode("utf-8"))  # no buffering
        interpreter = LP_interpreter(lp_filename, list(evaluator.data.columns))

        return interpreter.optimize()
    except ValueError:
        return None
    finally:
        os.close(fd)
        os.unlink(lp_filename)


def get_optimal_solution(model, problem):
    if "Subject To" in model:
        return lp_get_optimal_solution(model, problem)
    else:
        return zpl_get_optimal_solution(model)


def compare_optimal_solutions(opt: dict, ground_truth: dict, ground_truth_interpreter: Interpreter) -> bool:
    if opt is None:
        return False, False

    val_match = abs(opt[""] - ground_truth[""]) < 1e-6
    if len(opt) != len(ground_truth):
        return val_match, False

    if val_match:
        var_match = bool(ground_truth_interpreter.is_satisfied(pd.DataFrame(opt, [0], [k for k in opt.keys() if k != ""]))[0])
    else:
        var_match = False

    # var_match = True
    # for k, v in opt.items():
    #     if k == "":
    #         continue
    #     if abs(ground_truth[k] - v) >= 1e-6:
    #         var_match = False
    #         break

    return val_match, var_match


def main():
    LP_interpreter.gurobi_env.setParam(GRB.Param.Threads, 2)
    problems = ["chvatal_diet", "facility_location", "queens1", "queens2", "queens3", "queens4", "queens5", "steinerbaum", "tsp"]
    training_size = {p: 400 for p in problems}
    training_size["queens1"] = 92
    training_size["steinerbaum"] = 53

    ground_truth_interpreters = {p: Interpreter("../../datasets/ZIMPL/%s.zpl" % p) for p in problems}
    ground_truth_optimums = {p: i.optimize() for p, i in ground_truth_interpreters.items()}

    db_filename = "../../results/results.sqlite"

    experiment_name = "OCCALS"

    db_conn = sqlite3.connect(db_filename)
    cursor = db_conn.cursor()
    for stmt in ["ALTER TABLE generations ADD COLUMN optimal_value_match NUMERIC NULL",
                 "ALTER TABLE generations ADD COLUMN optimal_solution_match NUMERIC NULL"]:
        try:
            cursor.execute(stmt)
        except:
            pass

    cursor.execute(r'''SELECT g.id, problem, best_phenotype 
                    FROM experiments e JOIN parameters p on e.id = p.parent JOIN generations g on e.id = g.parent 
                    WHERE p.EXPERIMENT_NAME=? --AND p.TRAINING_SIZE IN (53, 92, 400) 
                    AND g.end=1 --AND best_phenotype NOT LIKE "Subject To%"''', (experiment_name, ))

    for row in cursor.fetchall():
        opt = get_optimal_solution(row[2], row[1])
        val_match, var_match = compare_optimal_solutions(opt, ground_truth_optimums[row[1]], ground_truth_interpreters[row[1]])

        cursor.execute("UPDATE generations SET optimal_value_match=?, optimal_solution_match=? WHERE id=?", (val_match, var_match, row[0]))

    db_conn.commit()


if __name__ == '__main__':
    main()
