SELECT avg(rating) FROM ratings 
JOIN movies ON movie_id = movies.id
WHERE year = 2012;