-- 13. Names of all people who starred in a movie in which Kevin Bacon also starred
SELECT name FROM people WHERE id IN (
    SELECT person_id FROM stars WHERE movie_id IN (
        SELECT id FROM movies WHERE id IN (
            SELECT movie_id FROM stars WHERE person_id IN (
                SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958
            )
        )
    )
) AND name != 'Kevin Bacon';
--WITH n AS (SELECT title, name, birth FROM stars
--JOIN movies ON stars.movie_id = movies.id
--JOIN people ON stars.person_id = people.id)
--SELECT name FROM n
--WHERE title IN
--(SELECT title FROM n WHERE name = 'Kevin Bacon' AND birth = 1958)
--AND name != 'Kevin Bacon';
