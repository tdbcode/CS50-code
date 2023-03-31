select title, ratings.rating from movies JOIN movies ON movies.id = ratings.movie_id where movies.year = 2010) ORDER BY ratings.rating DESC;

SELECT student_name, houses.house_name FROM houseref JOIN studentsnew ON houseref.studentid = studentsnew.id JOIN houses ON houseref.houseid = houses.id;