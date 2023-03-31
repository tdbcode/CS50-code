select DISTINCT(name) from people JOIN stars ON people.id = stars.person_id JOIN movies ON stars.movie_id = movies.id
WHERE people.name = "Kevin Bacon" AND people.birth = 1958;