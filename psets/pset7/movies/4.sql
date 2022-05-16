SELECT count(title) from movies 
JOIN ratings ON id = ratings.movie_id
WHERE rating = 10.0;