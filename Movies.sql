-- titles of all movies released in 2008
SELECT title FROM movies WHERE year = 2008;

-- birth year of Emma Stone
SELECT birth FROM people WHERE name = 'Emma Stone';

-- titles movies release date on/ after 2018, alphabetical order
SELECT title FROM movies WHERE year >= 2018 ORDER BY title asc;

-- determine the number of movies with an IMDb rating of 10.0.
SELECT COUNT(title) FROM movies JOIN ratings ON movies.id = ratings.movie_id WHERE rating = 10

--  list the titles and release years of all Harry Potter movies, in chronological order.
SELECT title, year FROM movies WHERE title LIKE '%Harry Potter%' ORDER BY year;

-- determine the average rating of all movies released in 2012.
SELECT AVG(rating) FROM ratings JOIN movies ON ratings.movie_id = movies.id WHERE year = 2012;

--list all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title.
SELECT movies.title, ratings.rating 
FROM movies 
JOIN ratings ON ratings.movie_id = movies.id 
WHERE movies.year = 2010 
ORDER BY ratings.rating DESC, movies.title ASC;

-- list the names of all people who starred in Toy Story.
SELECT name FROM people 
JOIN stars ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.title = 'Toy Story';

-- list the names of all people who starred in a movie released in 2004, ordered by birth year.
SELECT DISTINCT(people.name) FROM stars
JOIN people ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.year = 2004
ORDER BY birth;

--  list the names of all people who have directed a movie that received a rating of at least 9.0.
SELECT name FROM people
JOIN directors ON people.id = directors.person_id
JOIN movies ON directors.movie_id = movies.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE rating >= 9

-- list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
SELECT movies.title FROM people
Join stars ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;

--  list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.

SELECT title FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE people.name = "Johnny Depp" AND movies.title IN (SELECT title FROM movies
JOIN stars  ON stars.movie_id = movies.id
Join people ON stars.person_id = people.id
WHERE people.name = 'Helena Bonham Carter');

--  list the names of all people who starred in a movie in which Kevin Bacon also starred.
SELECT name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies on stars.movie_id = movies.id
WHERE movies.id IN (SELECT movies.id FROM movies
JOIN people ON stars.person_id = people.id
Join stars ON stars.movie_id = movies.id
WHERE people.name = 'Kevin Bacon'
AND people.birth = 1958)
AND people.name != 'Kevin Bacon';
