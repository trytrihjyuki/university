-- Maurycy Borkowski, PGA

-- zadanie 1
CREATE VIEW tmp AS
SELECT country1,country2,i1,i2 FROM
(SELECT country1, country2, p1.independence AS i1, p2.independence AS i2 FROM borders JOIN Politics p1 ON (p1.country = country1) JOIN Politics p2 ON(p2.country = country2) 
WHERE p1.independence IS NOT NULL AND p2.independence IS NOT NULL) AS neighbours 
WHERE ABS(extract(year FROM neighbours.i1) - extract(year FROM neighbours.i2)) > 580;


SELECT DISTINCT m.organization FROM isMember m JOIN tmp ON(m.country = tmp.country1)
WHERE tmp.country2 IN (SELECT country FROM isMember WHERE isMember.organization = m.organization);

-- zadanie 2
CREATE TABLE city_log (
    id serial PRIMARY KEY,
    user_id text,
    type char(6),
    data timestamp,
    accept boolean  default true
);

-- zadanie 3 & 4
-- INSERT TRIGGER
CREATE OR REPLACE FUNCTION insert_trigger_fnc()
RETURNS TRIGGER AS
$$
BEGIN
    IF ((SELECT count(*) FROM (SELECT * FROM city_log ORDER BY id DESC LIMIT 10) sub WHERE user_id=current_user) < 10) THEN
        INSERT INTO city_log(user_id,type,data,accept)
        VALUES (current_user,'INSERT',current_timestamp,true);
        RETURN NEW;
    ELSE
        INSERT INTO city_log(user_id,type,data,accept)
        VALUES (current_user,'INSERT',current_timestamp,false);
        RETURN NULL;
    END IF;
END;
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER citylog_insert_trigger
  BEFORE INSERT
  ON city
  FOR EACH ROW
  EXECUTE PROCEDURE insert_trigger_fnc();

-- UPDATE TRIGGER
CREATE OR REPLACE FUNCTION update_trigger_fnc()
RETURNS TRIGGER AS
$$
BEGIN
    IF ((SELECT count(*) FROM (SELECT * FROM city_log ORDER BY id DESC LIMIT 10) sub WHERE user_id=current_user) < 10) THEN
        INSERT INTO city_log(user_id,type,data,accept)
        VALUES (current_user,'UPDATE',current_timestamp,true);
        RETURN NEW;
    ELSE
        INSERT INTO city_log(user_id,type,data,accept)
        VALUES (current_user,'UPDATE',current_timestamp,false);
        RETURN NULL;
    END IF;
END;
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER citylog_update_trigger
  BEFORE UPDATE
  ON city
  FOR EACH ROW
  EXECUTE PROCEDURE update_trigger_fnc();

-- DELETE TRIGGER
CREATE OR REPLACE FUNCTION delete_trigger_fnc()
RETURNS TRIGGER AS
$$
BEGIN
    IF ((SELECT count(*) FROM (SELECT * FROM city_log ORDER BY id DESC LIMIT 10) sub WHERE user_id=current_user) < 10) THEN
        INSERT INTO city_log(user_id,type,data,accept)
        VALUES (current_user,'DELETE',current_timestamp,true);
        RETURN OLD;
    ELSE
        INSERT INTO city_log(user_id,type,data,accept)
        VALUES (current_user,'DELETE',current_timestamp,false);
        RETURN NULL;
    END IF;
END;
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER citylog_delete_trigger
  BEFORE DELETE
  ON city
  FOR EACH ROW
  EXECUTE PROCEDURE delete_trigger_fnc();


-- INSERT INTO city VALUES('test', 'test', 'test', 1, 2, 3, 4);
-- UPDATE city SET name = 'test2' WHERE name = 'test';
-- DELETE FROM city WHERE name='test2';

-- SELECT * FROM city_log;

-- DROP TRIGGER citylog_update_trigger ON city;
-- DROP TRIGGER citylog_insert_trigger ON city;
-- DROP TRIGGER citylog_delete_trigger ON city;