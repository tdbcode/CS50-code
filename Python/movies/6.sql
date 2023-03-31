select AVG(rating) from ratings where movie_id IN (
    select id from movies);