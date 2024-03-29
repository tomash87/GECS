﻿import os
import re
import sqlite3
import subprocess
import time
import psutil
import sys
import pyximport
import db

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
pyximport.install(language_level=3, inplace=True)
import fitness.helper  # implicitly compiles helper script; needed due to race conditions when compiled concurrently


class ProcessPool:
    def __init__(self, max_processes=psutil.cpu_count(logical=False)):
        self.queue = []
        self.max_processes = max_processes

    def execute(self, cmd, arguments, log_filename):
        self.wait_until_less_than(self.max_processes)
        log = open(log_filename + ".log", "w")
        self.queue.append(dict(process=subprocess.Popen([cmd] + arguments.split(" "), stdout=log, stderr=log), log=log))

    def wait_until_less_than(self, x):
        while True:
            for p in self.queue:
                p["process"].poll()
                if p["process"].returncode is not None:
                    p["log"].close()
                    self.queue.remove(p)

            if len(self.queue) < x:
                break

            time.sleep(0.1)

    def close(self):
        self.wait_until_less_than(1)


class SlurmPool:
    def __init__(self):
        try:
            os.makedirs("./slurm")
        except:
            None
        self.run = open("./run.sh", "w")
        self.run.write("#!/bin/bash\n")
        self.run.write("export LD_LIBRARY_PATH=./gurobi810/linux64/lib/\n")

    def execute(self, cmd, arguments, script_filename):
        sbatch = open("./slurm/%s.sh" % script_filename, "w")
        sbatch.write("#!/bin/bash\n")
        sbatch.write("#SBATCH -p lab-ci,lab-43,lab-44,lab-45\n")
        sbatch.write("#SBATCH -c 1 --mem=2600\n")
        sbatch.write("#SBATCH -t 3-23:55:00\n")
        sbatch.write("export GRB_LICENSE_FILE=~/gurobi-$(hostname).lic\n")
        sbatch.write("date\n")
        sbatch.write("hostname\n")
        sbatch.write("echo LD_LIBRARY_PATH=$LD_LIBRARY_PATH\n")
        sbatch.write("echo GRB_LICENSE_FILE=$GRB_LICENSE_FILE\n")
        sbatch.write("echo %s %s\n" % (cmd, arguments))
        sbatch.write("srun %s %s && srun rm \"./slurm/%s.sh\"\n" % (cmd, arguments.replace("'", r"\'"), script_filename))
        sbatch.close()

        self.run.write("sbatch \"./slurm/%s.sh\"\n" % script_filename)

    def close(self):
        self.run.close()

        ps = subprocess.Popen(["/bin/sh", "./run.sh"])
        ps.wait()


class CompleteDetector:
    def __init__(self, filename="../results/results.sqlite"):
        self.db = db.prepare_connection(filename)
        self.no_db = False

        cursor = self.db.cursor()
        try:
            cursor.execute("CREATE INDEX IF NOT EXISTS parametersExperimentNameProblemRandomSeedTrainingSize ON parameters(EXPERIMENT_NAME, PROBLEM, RANDOM_SEED, TRAINING_SIZE)")

        except sqlite3.OperationalError as e:
            self.no_db = True
            print(e)

    def is_completed(self, params):
        if self.no_db:
            return False
        cursor = self.db.cursor()
        cursor.execute("SELECT 1 FROM experiments e JOIN parameters p ON e.id=p.parent "
                       "WHERE p.EXPERIMENT_NAME=:EXPERIMENT_NAME "
                       "AND p.PROBLEM=:PROBLEM "
                       "AND p.RANDOM_SEED=:RANDOM_SEED "
                       "AND p.TRAINING_SIZE=:TRAINING_SIZE "
                       "AND e.error_exctype IS NULL "
                       "LIMIT 1", params)
        data = cursor.fetchall()
        # print(data[0][0])
        # return data[0][0] > 0
        return len(data) > 0


def main():
    seeds = range(0, 25)
    prob = ["acube32", "acube52", "asimplex32", "asimplex52",
            "gdiet", "gfacility", "gnetflow", "gsudoku", "gworkforce1",
            "zdiet", "zfacility", "zqueens1", "zqueens2", "zqueens3", "zqueens4", "zqueens5", "zsteinerbaum", "ztsp"]
    training_sizes = {p: [100, 200, 300, 400, 500, 600, 700, 800] for p in prob}
    training_sizes["queens1"] = [92]
    training_sizes["steinerbaum"] = [53]

    cx = {"S": "--crossover subtree", "F2": "--crossover fixed_twopoint", "V1": "--crossover variable_onepoint"}
    mt = {"S": "--mutation subtree", "C": "--mutation int_flip_per_codon", "I": "--mutation int_flip_per_ind"}
    ps = {"250_120": "--population_size 250 --generations 120", "750_40": "--population_size 750 --generations 40"}
    # ts = {"3": "--tournament_size 3", "5": "--tournament_size 5", "7": "--tournament_size 7"}
    # td = {"13": "--max_tree_depth 13", "14": "--max_tree_depth 14", "15": "--max_tree_depth 15"}
    # id = {"7": "--max_init_tree_depth 7", "8": "--max_init_tree_depth 8", "9": "--max_init_tree_depth 9"}

    settings = {'tuning': {}, 'scaling': {}}
    problems = {'tuning': {}, 'scaling': {}}
    # tuning pass 1 & 2: cx * mt
    # if c+m in {"SS", "F2S", "V1S", "SI", "SC"}
    settings['tuning'].update(
        {c + m: r"%s %s --population_size 500 --generations 60 --tournament_size 5" % (cc, mc) for c, cc in cx.items() for m, mc in mt.items() if c + m in {"SS", "F2S", "V1S", "V1I", "V1C"}})
    problems['tuning'].update({p: "--grammar ZIMPL-dedicated-%s.bnf --extra_parameters PROBLEM='%s', TRAINING_SIZE=%d" % (p, p, min(400, max(training_sizes[p]))) for p in prob})

    # tuning pass 2: ps
    settings['tuning'].update({"%s" % pop: r"%s --crossover variable_onepoint --mutation int_flip_per_ind --tournament_size 5" % pc for pop, pc in ps.items()})

    # scaling
    settings['scaling'].update({"V1I": r"--population_size 500 --generations 60 --tournament_size 5 --crossover variable_onepoint --mutation int_flip_per_ind"})
    problems['scaling'].update(
       {p + "_" + str(t): "--grammar ZIMPL-dedicated-%s.bnf --extra_parameters PROBLEM='%s', TRAINING_SIZE=%d" % (p, p, t) for p in prob for t in training_sizes[p] if t != min(400, max(training_sizes[p]))})

    # pool = ProcessPool()
    pool = SlurmPool()
    detector = CompleteDetector()

    settings_parser1 = re.compile(r'--(?P<param>\S+)\s+(?P<value>\S+)')
    settings_parser2 = re.compile(r"(?P<param>[a-zA-Z0-9_]+)='?(?P<value>[a-zA-Z0-9_]+)'?")

    total_runs = 0
    executed_runs = 0

    for seed in seeds:
        for type in ["scaling", "tuning"]:
            for problem, cmd_problem in problems[type].items():
                for name, cmd_setting in settings[type].items():
                    total_runs += 1

                    params = dict(settings_parser2.findall(cmd_problem))
                    params = {"EXPERIMENT_NAME": name, "PROBLEM": params["PROBLEM"], "RANDOM_SEED": seed, "TRAINING_SIZE": params["TRAINING_SIZE"]}
                    if detector.is_completed(params):
                        continue

                    executed_runs += 1
                    # ZIMPL-experiment-lookup_bad_fitness.txt
                    cmd = "-O ponyge.py --parameters ZIMPL-experiment.txt --random_seed %d --experiment_name %s %s %s" % (seed, name, cmd_setting, cmd_problem)
                    log = "%s_%s%s_%d" % (name, params["PROBLEM"], params["TRAINING_SIZE"], seed)
                    pool.execute("python3", cmd, log)

    print("Executing runs: %d Completed runs: %d Total runs: %d" % (executed_runs, total_runs - executed_runs, total_runs))
    pool.close()


if __name__ == '__main__':
    main()
