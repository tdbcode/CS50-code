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
        sid = student["id"]
        name = student["student_name"]
        house = student["house"]
        head = student["head"]

        if house not in houses:
            houses[id] = hid
            houses[name] = house
            houses[head] = head
            hid += 1

    print(houses[name])



       # db.execute("INSERT INTO student (id, student_name, houseID) VALUES (id, name, );)