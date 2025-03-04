import sqlite3 as sq

conn = sq.connect('database.db')

#create a cursor
cur = conn.cursor()

#create a table
#cur.execute("""INSERT INTO customers VALUES('itsjusta','semicolon','itsjustasemicolon@gmail.com')
#        """)

cur.execute("""SELECT rowid, * FROM customers""")
items = (cur.fetchall())
for item in items:
    print(item)




#DATATYPES - NULL, INTEGER, REAL, TEXT, BLOB (images)

#print("Successful")

conn.commit()
conn.close()

