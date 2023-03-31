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
    counts = {}

    INSERT INTO table_name (column1, column2, column3, ...)
    VALUES (value1, value2, value3, ...);

    # Iterate over CSV file, counting favorites
    for student in students:
        id = student["id"]
        name = student["name"]
        house = student["house"]
        if house == "Slytherin":
            houseID = 1
        elif house == "Ravenclaw":
            houseID = 2
        elif house == "Hufflepuff":
            houseID = 3
        elif house == "Gryffindor:
            houseID = 4

        head = student["head"]
        db.execute("INSERT INTO houses (id, house_name, head) VALUES (houseID, house, );)
        db.execute("INSERT INTO student (id, student_name, houseID) VALUES (id, name, );)

# Prompt user for favorite
favorite = input("Favorite: ")

# Search for title
rows = db.execute("SELECT COUNT(*) FROM favorites WHERE problem LIKE ?", "%" + favorite + "%")

# Get first (and only) row
row = rows[0]

# Print popularity
print(row["COUNT(*)"])