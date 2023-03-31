# Favorite problem instead of favorite language

import csv
from cs50 import SQL

# Open database
db = SQL("sqlite:///roster.db")

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
        print(temphouse)

        db.execute("INSERT INTO houseref (studentid, houseid) VALUES (?, ?, ?);", studentid, temphouse)
        db.execute("INSERT INTO studentsnew (id, student_name, houseID) VALUES (?, ?, ?);", studentid, temphouse)

    print(houses)
