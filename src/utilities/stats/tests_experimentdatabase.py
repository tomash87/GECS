import os, sys
import tempfile
import time
import unittest
from sqlite3 import ProgrammingError

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from experimentdatabase import DataSet
from experimentdatabase import Database
from experimentdatabase import DatabaseException

__author__ = 'Tomasz Pawlak'


class TestBase(unittest.TestCase):
    def _get_temp_file(self) -> str:
        file = tempfile.mkstemp(prefix="ExperimentDatabase", suffix=".sqlite", dir=tempfile.gettempdir())
        os.close(file[0])
        os.remove(file[1])
        return file[1]


class DatabaseTests(TestBase):
    def test_database(self):
        # Test #1: file does not exist
        file = self._get_temp_file()
        self.assertFalse(os.access(file, os.F_OK))

        with Database(file) as db:
            self.assertTrue(os.access(file, os.F_OK))
            self.__check_tables_exist(db)
            self.assertIn("experiments", db._columns)
            self.assertIn("id", db._columns["experiments"])

        self.assertTrue(os.access(file, os.F_OK))

        # Test #2: file exits, but is empty
        os.remove(file)
        open(file, "w").close()
        self.assertTrue(os.access(file, os.F_OK))

        with Database(file) as db:
            self.assertTrue(os.access(file, os.F_OK))
            self.__check_tables_exist(db)

        self.assertTrue(os.access(file, os.F_OK))

        # Test #3: a file contains database
        self.assertTrue(os.access(file, os.F_OK))

        with Database(file) as db:
            self.assertTrue(os.access(file, os.F_OK))
            self.__check_tables_exist(db)

        self.assertTrue(os.access(file, os.F_OK))

        # clean up
        os.remove(file)

    def test_close(self):
        file = self._get_temp_file()
        self.assertFalse(os.access(file, os.F_OK))

        db = Database(file)
        self.assertTrue(os.access(file, os.F_OK))

        # test if connection is open
        self.assertEqual(1, len(db.engine.execute("SELECT 1 FROM sqlite_master LIMIT 1").fetchall()))

        db.__exit__(None, None, None)
        # test if connection is closed
        with self.assertRaises(ProgrammingError):
            db.engine.execute("SELECT 1 FROM sqlite_master LIMIT 1")

        with self.assertRaises(DatabaseException):
            db.write_data(None)

        os.remove(file)

    def test_write_data(self):
        file = self._get_temp_file()
        self.assertFalse(os.access(file, os.F_OK))

        with Database(file) as db:
            # Test #1: first insert
            parameters = DataSet("test_set", None, db)
            parameters["String"] = "This is string parameter"
            parameters["Float"] = 1.1
            parameters["Int"] = 2
            parameters["Boolean"] = True
            parameters["Null"] = None

            db.write_data(parameters)

            rows = db.engine.execute("SELECT `String`, `Float`, `Int`, `Boolean`, `Null` FROM test_set ORDER BY id ASC").fetchall()
            self.assertEqual(1, len(rows))
            self.assertEqual(parameters["String"], rows[0]["String"])
            self.assertEqual(parameters["Float"], rows[0]["Float"])
            self.assertEqual(parameters["Int"], rows[0]["Int"])
            self.assertEqual(parameters["Boolean"], rows[0]["Boolean"])
            self.assertEqual(parameters["Null"], rows[0]["Null"])

            # Test #2: two tuples in DB
            # Note that we changed the case of letters!
            parameters2 = DataSet("test_set", None, db)
            parameters2["string"] = "2: This is string parameter"
            parameters2["Float"] = 21.1
            parameters2["Int"] = (1 << 63) - 1
            parameters2["Boolean"] = False
            parameters2["Null"] = None

            db.write_data(parameters2)

            rows = db.engine.execute("SELECT `String`, `Float`, `Int`, `Boolean`, `Null` FROM test_set ORDER BY id ASC").fetchall()
            self.assertEqual(2, len(rows))
            self.assertEqual(parameters["String"], rows[0]["String"])
            self.assertEqual(parameters["Float"], rows[0]["Float"])
            self.assertEqual(parameters["Int"], rows[0]["Int"])
            self.assertEqual(parameters["Boolean"], rows[0]["Boolean"])
            self.assertEqual(parameters["Null"], rows[0]["Null"])

            self.assertEqual(parameters2["String"], rows[1]["String"])
            self.assertEqual(parameters2["Float"], rows[1]["Float"])
            self.assertEqual(parameters2["Int"], rows[1]["Int"])
            self.assertEqual(parameters2["Boolean"], rows[1]["Boolean"])
            self.assertEqual(parameters2["Null"], rows[1]["Null"])

        os.remove(file)

    def test_new_experiment(self):
        file = self._get_temp_file()

        with Database(file) as db:
            experiment = db.new_experiment()

            self.assertIsNotNone(experiment)
            self.assertEqual(-1, experiment.id)

        os.remove(file)

    def __check_tables_exist(self, db: Database, table_name="experiments"):
        rows = db.engine.execute("SELECT count(*) FROM sqlite_master WHERE type='table' and name=:name", {"name": table_name}).fetchall()
        self.assertEqual(1, int(rows[0][0]))


class DataSetTests(TestBase):
    __db_file = None
    __db = None
    __experiment = None

    def setUp(self):
        self.__db_file = self._get_temp_file()
        self.__db = Database(self.__db_file)
        self.__experiment = self.__db.new_experiment()

    def test_get_id(self):
        iteration = self.__experiment.new_child_data_set("iterations")
        self.assertEqual(-1, iteration.id)

        iteration.save()
        self.assertGreaterEqual(iteration.id, 0)

        previous_id = iteration.id
        iteration.save()
        self.assertEqual(previous_id, iteration.id)

    def test_save(self):
        with self.__db.new_experiment() as experiment:
            self.assertEqual(-1, experiment.id)

            experiment["in_Problem"] = "Keijzer04";
            experiment["in_ProblemType"] = "Regression";
            experiment["in_CrossoverProbability"] = 0.666666666667;
            experiment["in_MutationProbability"] = 0.33333333;
            experiment["in_AvgNodeCount"] = "35345.40";
            experiment["out_TotalTime"] = 2222;

            self.assertEqual(-1, experiment.id)

            experiment.save()

            self.assertGreaterEqual(experiment.id, 0)

            # check data stored in database
            rows = self.__db.engine.execute("SELECT * FROM experiments").fetchall()
            self.assertEqual(1, len(rows))

            self.assertEqual(experiment["in_Problem"], rows[0]["in_Problem"])
            self.assertEqual(experiment["in_ProblemType"], rows[0]["in_ProblemType"])
            self.assertEqual(experiment["in_CrossoverProbability"], rows[0]["in_CrossoverProbability"])
            self.assertEqual(experiment["in_MutationProbability"], rows[0]["in_MutationProbability"])
            self.assertEqual(float(experiment["in_AvgNodeCount"]), rows[0]["in_AvgNodeCount"])
            self.assertEqual(experiment["out_TotalTime"], rows[0]["out_TotalTime"])

            # change the value of a single parameter and add a parameter, then check if the database was updated
            previous_id = experiment.id

            experiment["in_AvgNodeCount"] = "222222.2222"
            experiment["in_newParam"] = 123
            experiment.save()

            # make sure the experiment id did not change
            self.assertEqual(previous_id, experiment.id)
            rows = self.__db.engine.execute("SELECT * FROM experiments").fetchall()
            self.assertEqual(1, len(rows))

            self.assertEqual(experiment["in_Problem"], rows[0]["in_Problem"])
            self.assertEqual(experiment["in_ProblemType"], rows[0]["in_ProblemType"])
            self.assertEqual(experiment["in_CrossoverProbability"], rows[0]["in_CrossoverProbability"])
            self.assertEqual(experiment["in_MutationProbability"], rows[0]["in_MutationProbability"])
            self.assertEqual(float(experiment["in_AvgNodeCount"]), rows[0]["in_AvgNodeCount"])
            self.assertEqual(experiment["out_TotalTime"], rows[0]["out_TotalTime"])
            self.assertEqual(experiment["in_newParam"], rows[0]["in_newParam"])

    def test_save_of_child(self):
        with self.__experiment.new_child_data_set("iterations") as iteration:
            iteration["generation"] = 1
            iteration["bestFitness"] = 444
            iteration["avgFitness"] = 1434.3

            self.assertEqual(-1, iteration.id)

            iteration.save()

            self.assertGreaterEqual(iteration.id, 0)

            # check contents of database

            rows = self.__db.engine.execute("SELECT * FROM iterations").fetchall()
            self.assertEqual(1, len(rows))

            self.assertEqual(iteration["generation"], rows[0]["generation"])
            self.assertEqual(iteration["bestFitness"], rows[0]["bestFitness"])
            self.assertEqual(iteration["avgFitness"], rows[0]["avgFitness"])

            # change a single value and add a value
            iteration["bestFitness"] = 400.1
            iteration["newValue"] = 234
            # save the parent (and the child in effect)
            self.__experiment.save()

            rows = self.__db.engine.execute("SELECT * FROM iterations").fetchall()
            self.assertEqual(1, len(rows))

            self.assertEqual(iteration["generation"], rows[0]["generation"])
            self.assertEqual(iteration["bestFitness"], rows[0]["bestFitness"])
            self.assertEqual(iteration["avgFitness"], rows[0]["avgFitness"])
            self.assertEqual(iteration["newValue"], rows[0]["newValue"])

    def test___exit__(self):
        iteration = self.__experiment.new_child_data_set("iterations")
        iteration["generation"] = 1
        iteration.__exit__(None, None, None)

        with self.assertRaises(DatabaseException):
            iteration.id

        # check if databa is written to database
        rows = self.__db.engine.execute("SELECT * FROM iterations").fetchall()
        self.assertEqual(1, len(rows))

        self.assertEqual(1, rows[0]["generation"])
        self.assertEqual(self.__experiment.id, rows[0]["parent"])

    def tearDown(self):
        self.__experiment.__exit__(None, None, None)
        self.__db.__exit__(None, None, None)

        os.remove(self.__db_file)


class ConcurrentTests(TestBase):
    RUNNER_COUNT = 100
    ITERATION_COUNT = 100

    __db_file = None

    def setUp(self):
        self.__db_file = self._get_temp_file()

    def test(self):
        for r in range(0, self.RUNNER_COUNT):
            self.do_work(r)
        # Parallel(n_jobs=10, backend="threading")(delayed(self.do_work)(r) for r in range(0, self.RUNNER_COUNT))

        self.validate_database()

    def do_work(self, id: int):
        s_time = time.clock()
        db = Database(self.__db_file)
        with db.new_experiment() as experiment:
            experiment["in_runnerId"] = id

            for i in range(0, self.ITERATION_COUNT):
                iter = experiment.new_child_data_set("iterations")
                iter["generation"] = i
                iter["bestFitness"] = 1.0 / (1.0 + i)
                iter["timeElapsed"] = (time.clock() - s_time)
                # data is saved on exit from "with" statement

                # db.__exit__(None, None, None) # DO NOT uncomment, simulate that process still uses the file

    def validate_database(self):
        db = Database(self.__db_file)

        expected_runner_id = 0
        expected_generation = 0
        count = 0

        for row in db.engine.execute(
                "SELECT e.id AS expId, i.id AS iterId, e.in_runnerId AS in_runnerId, i.generation AS generation FROM experiments e JOIN iterations i ON e.id = i.parent ORDER BY in_runnerId, generation ASC"):
            self.assertEqual(expected_runner_id, row["in_runnerId"])
            self.assertEqual(expected_generation, row["generation"])

            expected_generation += 1
            if expected_generation >= self.ITERATION_COUNT:
                expected_generation = 0
                expected_runner_id += 1

            count += 1

        self.assertEqual(self.RUNNER_COUNT * self.ITERATION_COUNT, count)

    def tearDown(self):
        os.remove(self.__db_file)


if __name__ == '__main__':
    unittest.main()
