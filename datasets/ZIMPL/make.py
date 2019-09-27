import os
import re

from utilities.ZIMPLpy.interpreter import Interpreter


def main():
    base_dir = os.path.dirname(__file__)

    for file in os.scandir(base_dir):
        if file.is_file() and re.search(r"\.zpl$", file.name, re.I) is not None:
            print("%s:" % file.name)
            with Interpreter(file.path, False) as interpreter:
                name_noext = re.sub(r"\.zpl$", r"", file.path)

                print("Calculating training set...")
                generate(interpreter, name_noext + "_training.csv.bz2", 5000, True)
                print("Calculating test set...")
                generate(interpreter, name_noext + "_test.csv.bz2", 5000, True)
                print("Calculating validation set...")
                generate(interpreter, name_noext + "_validation.csv.bz2", 5000, True)
                # print("Calculating validation set 2...")
                # generate(interpreter, name_noext + "_validation2.csv.bz2", 500000, False)
                print("Generating grammar...")
                with open("%s/../../grammars/ZIMPL-dedicated-%s.bnf" % (base_dir, os.path.basename(name_noext)), "wt") as f:
                    f.write(interpreter.generate_grammar())


def generate(interpreter, filename, n, positive_only=True, class_column=False):
    if not os.path.exists(filename):
        if positive_only and not class_column:
            if "zsteinerbaum" in filename or "zqueens1" in filename:
                data = interpreter.sample_positive(n, method="bc")
            else:
                data = interpreter.sample_positive(n, method="har", budget=1000000)
        else:
            data = interpreter.sample(n, positive_only, class_column)
        data.to_csv(filename, index=False, compression="bz2")


if __name__ == '__main__':
    main()
