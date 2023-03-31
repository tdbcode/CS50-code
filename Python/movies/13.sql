select distinct(name) from people
JOIN stars ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.id IN
(
    select movies.id FROM movies
    JOIN stars ON movie.id = stars.movie_id
    JOIN people ON stars.person_id = people.id
    WHERE people.name = "Kevin Bacon" AND people.birth = 1958
);