-- Maurycy Borkowski, PGA
-- Zadanie 1
SELECT name, COUNT(DISTINCT island)
FROM country
JOIN geo_sea ON (country.code=geo_sea.country)
LEFT JOIN islandIn USING (sea)
GROUP BY name
ORDER BY count(DISTINCT island) DESC, name ASC;

-- Zadanie 2
WITH PL AS (
SELECT country.name as cn, percentage as pp
FROM country
JOIN ethnicgroup ON (country.code=ethnicgroup.country)
WHERE ethnicgroup.name='Polish')
SELECT DISTINCT country.name, pp
FROM country
JOIN ethnicgroup ON (country.code=ethnicgroup.country)
JOIN PL ON (country.name=cn)
GROUP BY country.name, pp
HAVING COUNT(DISTINCT ethnicgroup.name)>=10;

-- zadanie 3
CREATE TEMP TABLE KARTEZ AS (
(SELECT country2 AS a,country1 AS b FROM borders) UNION
(SELECT country1 AS a,country2 AS b FROM borders));

WITH RECURSIVE Path(a,b) AS (
(SELECT a, b FROM KARTEZ)
UNION (SELECT KARTEZ.a, p.b FROM KARTEZ JOIN Path p ON (KARTEZ.b=p.a)))

SELECT DISTINCT country.*
FROM Path p
JOIN Country ON (p.a=country.code)
WHERE p.b = 'PL'
ORDER BY country.name;

-- zadanie 4
SELECT country.name, ROUND((SUM(city.population)/country.population*100)) as pr
FROM country
JOIN city ON (country.code=city.country)
GROUP BY country.name, country.population
HAVING ROUND((SUM(city.population)/country.population*100))>=75
ORDER BY pr DESC;