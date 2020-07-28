SELECT title FROM movies WHERE id IN (
SELECT movie_id
FROM stars
WHERE (
    SELECT id
    FROM people
    WHERE name = "Helena Bonham Carter") = person_id
INTERSECT
SELECT movie_id
FROM stars
WHERE (
    SELECT id
    FROM people
    WHERE name = "Johnny Depp") = person_id
)