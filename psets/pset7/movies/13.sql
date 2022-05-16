SELECT DISTINCT name FROM people 
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.id IN (SELECT movie_id from stars WHERE person_id = (SELECT id from people where name LIKE 'Kevin Bacon' AND people.birth = 1958)) AND NOT people.name = 'Kevin Bacon'
