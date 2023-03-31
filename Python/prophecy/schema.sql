CREATE TABLE students (
    id INTEGER,
    student_name TEXT,
    house TEXT,
    head INTEGER,
    PRIMARY KEY(id)
    FOREIGN KEY (houseID) REFERENCES Persons(PersonID)
);