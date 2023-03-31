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


    # Iterate over CSV file, counting favorites
    for student in students:
        id = student["id"]
        name = student["student_name"]
        house = student["house"]
        head = student["head"]

        if house not in houses:
            houses[house] = head

        if house == "Slytherin":
            houseID = 1
        elif house == "Ravenclaw":
            houseID = 2
        elif house == "Hufflepuff":
            houseID = 3
        elif house == "Gryffindor":
            houseID = 4

    print(houses)

    for house in houses:
        db.execute("INSERT INTO houses (id, house_name, houseID) VALUES (id, name, );)
id INTEGER,
    house_name TEXT,
    head TEXT,
    PRIMARY KEY(id)

       # db.execute("INSERT INTO student (id, student_name, houseID) VALUES (id, name, );)