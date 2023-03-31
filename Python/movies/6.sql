select ROUND(AVG(rating),2) from ratings where movie_id IN (
    select id from movies);