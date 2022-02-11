-- Tworzymy tabele
DROP TABLE osoba;
DROP SEQUENCE osoba_id_seq;

CREATE SEQUENCE osoba_id_seq;

CREATE TABLE osoba (
    -- id serial PRIMARY KEY, --wariant 2
    id int PRIMARY KEY DEFAULT nextval('osoba_id_seq'), -- wariant 1
    imie text,
    nazwisko text,
    email text,
    gender text,
    age int
);

ALTER SEQUENCE osoba_id_seq
OWNED BY osoba.id;


-- Dodawanie wartosci
INSERT INTO osoba VALUES (DEFAULT, 'Kuba', 'Kowalski', 'kuba.kuba@wp.pl', 'male', 10);
INSERT INTO osoba VALUES (DEFAULT, 'Kuba', 'Złotopolski', 'kuba420@wp.pl', 'male', 21);
INSERT INTO osoba VALUES (DEFAULT, 'Marek', 'Kowalski', 'marek@onet.pl', 'male', 30);
INSERT INTO osoba VALUES (DEFAULT, 'Hania', 'Nowak', 'hania.nowak@wp.pl', 'female', 10);
INSERT INTO osoba VALUES (DEFAULT, 'Anna', 'Lewandowska', 'ania997@wp.pl', 'female', 32);

-- przykład
SELECT * FROM osoba;
