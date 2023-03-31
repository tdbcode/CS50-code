select ROUND(AVG(rating),0) from ratings where movie_id IN (
    select id from movies);