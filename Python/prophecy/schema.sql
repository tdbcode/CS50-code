CREATE TABLE students (
    id INTEGER,
    student_name TEXT,
    houseID INTEGER,
    PRIMARY KEY(id)
);

CREATE TABLE houses (
    id INTEGER,
    house_name TEXT,
    head TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE housesreferences (
    studentid INTEGER,
    houseid INTEGER,
    FOREIGN KEY (studentid) REFERENCES students(id)
    FOREIGN KEY (houseid) REFERENCES houses(id)
);