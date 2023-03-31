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

        sid = student["id"]
        name = student["student_name"]

    print(houses)
    db.execute("INSERT INTO houses (id, house_name, head) VALUES (hid, name, );)