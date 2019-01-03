import sys
import sqlite3


class Descriptor:
    def __init__(self, path):
        self.tree = {'experiments': None # {
        #     'generations': None,
        #     'constraints': None,
		#     'variables': None
        # }
        }
        self.max_ids = {}

        self.db = sqlite3.connect(path)
        self.cursor = self.db.cursor()
        self.cursor.execute("PRAGMA foreign_keys=ON")
        self.cursor.execute("PRAGMA synchronous=OFF")
        self.cursor.execute("PRAGMA temp_store=MEMORY")
        self.cursor.execute("PRAGMA journal_mode=TRUNCATE")
        self.cursor.execute("PRAGMA page_size=" + str(1 << 15))
        self.cursor.execute("PRAGMA threads=3")
        self.prepare_indexes()
        self.cursor.execute("BEGIN IMMEDIATE TRANSACTION")
        self.cursor.execute("PRAGMA defer_foreign_keys=ON")
        self.load_data()

    def prepare_indexes(self):
        #  self.cursor.execute("CREATE INDEX IF NOT EXISTS fitnessParent ON fitness(parent)")
        #  self.cursor.execute("CREATE INDEX IF NOT EXISTS generationsParent ON generations(parent)")
        #  self.cursor.execute("CREATE INDEX IF NOT EXISTS constraintsParent ON constraints(parent)")
        #  self.cursor.execute("CREATE INDEX IF NOT EXISTS variablesParent ON variables(parent)")
        pass

    def load_data(self):
        self.cursor.execute("SELECT name, seq FROM sqlite_sequence")
        rows = self.cursor.fetchall()
        self.max_ids = [(table, int(seq)) for (table, seq) in rows]
        self.tables = [table for (table, seq) in rows]

    def increase_ids(self, other):
        '''other is max_ids collection of the other database'''
        for (table, max_id) in other:
            if table not in self.tables:
                print("Warning! No table %s in database" % table)
                continue

            self.cursor.execute("SELECT id FROM %s ORDER BY id DESC" % table)
            my_rows = self.cursor.fetchall()
            for id in my_rows:
                self.cursor.execute("UPDATE %s SET id=%d WHERE id=%d" % (table, int(id[0]) + max_id + 1, id[0]))

        self.cursor.execute("PRAGMA foreign_key_check")
        violations = self.cursor.fetchall()
        if len(violations) > 0:
            raise Exception("\n".join([" ".join(v) for v in violations]))

    def copy_data(self, other):
        '''other is Descriptor of other database'''
        for (table, seq) in self.max_ids:
            if table not in other.tables:
                print("Warning! No table %s in database" % table)
                continue

            other.cursor.execute("SELECT * FROM " + table)
            other_rows = other.cursor.fetchall()

            # create insert statement
            insert = "INSERT INTO " + table + "("
            insert += ",".join(["`" + column[0] + "`" for column in other.cursor.description])
            insert += ") VALUES ("
            insert += "?," * len(other.cursor.description)
            insert = insert[:-1]
            insert += ")"

            for row in other_rows:
                self.cursor.execute(insert, [x for x in row])

    def rollback(self):
        self.db.rollback()

    def commit(self):
        self.db.commit()


def main():
    basePath = sys.argv[1]
    otherPath = sys.argv[2]

    baseDB = Descriptor(basePath)
    otherDB = Descriptor(otherPath)
    print("Connections opened")

    otherDB.increase_ids(baseDB.max_ids)
    print("Ids increased in the other db")

    baseDB.copy_data(otherDB)
    print("Data copied from the other db to base db")

    otherDB.rollback()
    baseDB.commit()
    print("Connections closed")


if __name__ == "__main__":
    main()
