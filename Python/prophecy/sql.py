# Favorite problem instead of favorite language

import csv
from cs50 import SQL

# Open database
db = SQL("sqlite:///roster.db")

db.execute("DROP TABLE studentsnew;")
db.execute("DROP TABLE houses;")
db.execute("DROP TABLE houseref;")
db.execute("CREATE TABLE studentsnew (id INTEGER, student_name TEXT, PRIMARY KEY(id));")
db.execute("CREATE TABLE houses (id INTEGER, house_name TEXT, head TEXT, PRIMARY KEY(id));")
db.execute("CREATE TABLE houses (id INTEGER, house_name TEXT, head TEXT, PRIMARY KEY(id));")
db.execute("CREATE TABLE houseref (studentid INTEGER, houseid INTEGER, FOREIGN KEY (studentid) REFERENCES studentsnew(id) FOREIGN KEY (houseid) REFERENCES houses(id));")

# Open CSV file
with open("students.csv", "r") as file:

    # Create DictReader
    students = csv.DictReader(file)

    # Counts
    houses = {}
    hid = 1
    temphouse = 0


    # Iterate over CSV file, counting favorites
    for student in students:
        house = student["house"]
        head = student["head"]

        if house not in houses:
            houses[house] = head
            db.execute("INSERT INTO houses (id, house_name, head) VALUES (?, ?, ?);", hid, house, head)
            hid += 1

        studentid = student["id"]
        name = student["student_name"]

        temphouse = db.execute("SELECT id FROM houses WHERE house_name = ?;", house)
        for house in temphouse:
            temphouse1 = house["id"]
        db.execute("INSERT INTO studentsnew (id, student_name) VALUES (?, ?);", studentid, name)
        db.execute("INSERT INTO houseref (studentid, houseid) VALUES (?, ?);", studentid, temphouse1)

SELECT
t1.*,
t2.staff_name
FROM Clients t1
LEFT JOIN Staff t2
ON (t2.id = t1.staff);

newstudents = db.execute("SELECT t1.id, t2.house_name FROM studentsnew t1 LEFT JOIN houses t2 ON (t2.id = );")
for students in newstudents:
    print(students["name"])


