DROP TABLE studentsnew;
DROP TABLE houses;
DROP TABLE housesreferences;

CREATE TABLE studentsnew (
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

CREATE TABLE houseref (
    studentid INTEGER,
    houseid INTEGER,
    FOREIGN KEY (studentid) REFERENCES studentsnew(id)
    FOREIGN KEY (houseid) REFERENCES houses(id)
);