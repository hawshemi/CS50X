SELECT name FROM people
JOIN stars ON people.id = person_id
JOIN movies ON movie_id = movies.id
WHERE movies.title = "Toy Story"
