CREATE SEQUENCE numer_przedmiot_semestr;
SELECT setval('numer_przedmiot_semestr',max(kod_przed_sem))
FROM przedmiot_semestr;

ALTER TABLE przedmiot_semestr
    ALTER COLUMN kod_przed_sem
    SET DEFAULT nextval('numer_przedmiot_semestr');
ALTER SEQUENCE numer_przedmiot_semestr

   OWNED BY przedmiot_semestr.kod_przed_sem;