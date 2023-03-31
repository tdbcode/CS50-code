select name from songs
WHERE artist_id IN (
    select id from artists
    where name like "%feat%");