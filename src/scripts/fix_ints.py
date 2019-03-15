import sqlite3

db_file = "../../results/results.sqlite"

db_conn = sqlite3.connect(db_file)
cursor = db_conn.cursor()

select = "SELECT max_genome_length, max_used_codons, max_tree_depth, max_tree_nodes, id FROM generations"
update = "UPDATE generations SET max_genome_length=?, max_used_codons=?, max_tree_depth=?, max_tree_nodes=? WHERE id=?"

cursor.execute("BEGIN DEFERRED TRANSACTION")
for row in cursor.execute(select).fetchall():
    cursor.execute(update, [int.from_bytes(r, byteorder='little') if isinstance(r, bytes) else r for r in row])

db_conn.commit()

