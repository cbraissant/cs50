SELECT title, rating FROM movies
JOIN ratings ON ratings.movie_id = movies.id
WHERE year = 2010 AND ratings.rating >= 0
ORDER BY ratings.rating DESC, title;