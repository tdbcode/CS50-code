select AVG(energy) from songs
WHERE artist_id IN (
    select id from artists
    where name = "Drake");