-- Maurycy Borkowski, PGA

-- Zadanie 1
CREATE VIEW SeaAirports
    (iatacode, name, city, province, country, sea)
AS
SELECT
    airport.iatacode, airport.name, airport.city, airport.province, airport.country, located.sea
FROM
airport
JOIN city ON (city.name=airport.city)
JOIN located ON (city.name=located.city)
WHERE city.elevation>200
AND located.sea IS NOT NULL
AND airport.country=city.country
AND located.country=city.country
AND airport.province=city.province
AND located.province=city.province;

-- Zadanie 2
ALTER TABLE city DROP CONSTRAINT citykey;

ALTER TABLE city ADD COLUMN id SERIAL;
ALTER TABLE city ADD CONSTRAINT PKcity
    PRIMARY KEY(id);

ALTER TABLE airport ADD COLUMN CityId int;

UPDATE airport SET CityId = c.id
FROM city c JOIN airport a ON(c.name = a.city) WHERE a.city = airport.city;

ALTER TABLE airport ADD CONSTRAINT  airport
    FOREIGN KEY (CityId) REFERENCES city(id) DEFERRABLE;

INSERT INTO airport
    (iatacode,name,country,city,province,latitude,longitude, elevation, CityId)
SELECT 'IEG', 'Babimost', city.country, city.name, city.province,
 city.latitude, city.longitude, city.elevation, city.id
FROM city WHERE name = 'Zielona Góra';

-- Zadanie 3
INSERT INTO countrypops
    (country, year, population)
SELECT country.code, extract(year FROM current_date), country.population
FROM country;

-- Zadanie 4
ALTER TABLE country ADD COLUMN poppeakcount numeric;
ALTER TABLE country ADD COLUMN poppeakyear numeric;
UPDATE country
SET (poppeakcount, poppeakyear) = 
    (SELECT MAX(countrypops.population) as maksik, countrypops.year
     FROM countrypops
     WHERE countrypops.country=country.code
     GROUP BY countrypops.country, countrypops.year
     ORDER BY maksik DESC
     LIMIT 1
    );
