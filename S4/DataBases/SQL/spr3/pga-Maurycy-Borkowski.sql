-- zadanie 0
CREATE TABLE sunken_city (LIKE city);
ALTER TABLE sunken_city ADD COLUMN sinking_date date;

-- zadanie 1
CREATE OR REPLACE FUNCTION sea_level(level int)
RETURNS VOID
AS $X$
DECLARE ct city;
BEGIN
    DROP TABLE IF EXISTS last_level;
    CREATE TABLE last_level(level int);
    INSERT INTO last_level(level) VALUES(level);

    DELETE FROM airport WHERE airport.elevation < $1;

    FOR ct IN
        SELECT *
        FROM city c
        WHERE c.elevation < $1
    LOOP
        INSERT INTO sunken_city(name, country, province, population, latitude, longitude, elevation, sinking_date)
        VALUES (ct.name, ct.country, ct.province, ct.population, ct.latitude, ct.longitude, ct.elevation, CURRENT_DATE);

        UPDATE airport SET city=NULL 
        WHERE city=ct.name AND country=ct.country;

        DELETE FROM city WHERE city.name = ct.name AND city.country = ct.country;

    END LOOP;
END
$X$ LANGUAGE plpgsql;

-- zadanie 2
CREATE TABLE last_level(level INT);
INSERT INTO last_level(level) VALUES(10);

CREATE OR REPLACE FUNCTION check_ins_city()
    RETURNS TRIGGER AS $X$
    DECLARE l INT;
    BEGIN
        SELECT level INTO l FROM last_level;
        IF (NEW.elevation >= l) THEN RETURN NEW;
        ELSE
            INSERT INTO sunken_city(name, country, province, population, latitude, longitude, elevation, sinking_date)
            VALUES(NEW.name, NEW.country, NEW.province, NEW.population, NEW.latitude, NEW.longitude, NEW.elevation, CURRENT_DATE); 
        END IF;
    RETURN NULL;
    END
    $X$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION check_upd_city()
    RETURNS TRIGGER AS $X$
    DECLARE l INT;
    BEGIN
        SELECT level INTO l FROM last_level;
        IF (NEW.elevation >= l) THEN RETURN NEW;
        ELSE 
            DELETE FROM city WHERE name = OLD.name AND country = OLD.country;
            INSERT INTO sunken_city(name, country, province, population, latitude, longitude, elevation, sinking_date)
            VALUES(NEW.name, NEW.country, NEW.province, NEW.population, NEW.latitude, NEW.longitude, NEW.elevation, CURRENT_DATE); 
        END IF;
    RETURN NULL;
    END
    $X$ LANGUAGE plpgsql;

CREATE TRIGGER on_insert_to_city BEFORE INSERT ON city
FOR EACH ROW EXECUTE PROCEDURE check_ins_city();

CREATE TRIGGER on_update_to_city BEFORE UPDATE ON city
FOR EACH ROW EXECUTE PROCEDURE check_upd_city();


-- ################## TESTOWANIE ################## 

-- FUNKCJA SEA_LEVEL

-- Sprawdziłem jakie miasta są poniżej 1m
SELECT * FROM city WHERE city.elevation < 1;
-- Zalewamy te miasta
SELECT sea_level(1);
-- Sprawdzamy czy dobrze się przeniosły
SELECT * FROM city WHERE city.elevation < 1;
SELECT * FROM sunken_city;


-- szukamy lotniska, które się nie usunie z miastem
SELECT airport.iatacode, airport.name, airport.city, city.elevation, airport.elevation
FROM city JOIN airport ON (city.name=airport.name)
WHERE (city.elevation < airport.elevation)
LIMIT 1;
-- miasto.elevation=920, lotnisko.elevation=977
-- zalewamy miasto ale NIE lotnisko
SELECT sea_level(921);
-- sprawdzamy krotki lotniska i miasta
SELECT * FROM city
WHERE city.name='Herat';
SELECT * FROM sunken_city
WHERE sunken_city.name='Herat';
SELECT * FROM airport
WHERE airport.iatacode='HEA';


-- TRIGGERY

-- INSERT
-- Sprawdzamy wartość ostatniego zalania (dodaliśmy 10 przy tworzeniu)
SELECT * FROM last_level;
-- Dodajemy miast poniżej last_level i sprawdzamy gdzi jest (sunken czy zwykle city)
INSERT INTO city(name,country,province,population,latitude,longitude,elevation)
VALUES('Pcim','PL','nuda',100,20,30,9);

SELECT * FROM city
WHERE city.name='Pcim';

SELECT * FROM sunken_city
WHERE sunken_city.name='Pcim';
-- analogicznie sprawdzamy czy zostawi w spokoju miasto jak będzie elevation>10

-- UPDATE
INSERT INTO city(name,country,province,population,latitude,longitude,elevation)
VALUES('Pcimek','PL','nuda',100,20,30,11);

UPDATE city SET elevation = 9 WHERE name = 'Pcimek';

SELECT * FROM city
WHERE city.name='Pcimek';

SELECT * FROM sunken_city
WHERE sunken_city.name='Pcimek';
-- analogicznie sprawdzamy czy zostawi w spokoju miasto jak będzie elevation>10