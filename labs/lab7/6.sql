SELECT name FROM songs Where artist_id=(SELECT id FROM artists where name = 'Post Malone');