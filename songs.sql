-- 1.sql
SELECT name FROM songs;

-- 2.sql
SELECT name FROM songs ORDER BY tempo;

-- 3.sql
SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;

-- 4.sql
SELECT name FROM songs WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75;

-- 5.sql
SELECT avg(energy) FROM songs;

-- 6.sql
SELECT name FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name == "Post Malone");

-- 7.sql
SELECT avg(energy) FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name == "Drake");

-- 8.sql
SELECT name FROM songs WHERE name LIKE "%feat.%";
