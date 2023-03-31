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


    # Iterate over CSV file, counting favorites
    for student in students:
        house = student["house"]
        head = student["head"]

        if house not in houses:
            houses[house] = head
            db.execute("INSERT INTO houses (id, house_name, head) VALUES (?, ?, ?);", hid, house, head)
            hid += 1

        sid = student["id"]
        name = student["student_name"]

        db.execute("INSERT INTO studentsnew (id, student_name, head) VALUES (?, ?, ?);", hid, house, head)

    print(houses)
