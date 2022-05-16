SELECT DISTINCT people.name FROM people
Join stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.title LIKE 'Toy Story';