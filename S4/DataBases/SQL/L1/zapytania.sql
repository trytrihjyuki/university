(SELECT uzytkownik.kod_uz, imie,nazwisko
FROM grupa JOIN uzytkownik USING(kod_uz)
WHERE rodzaj_zajec='w')
EXCEPT
(SELECT uzytkownik.kod_uz, imie,nazwisko
FROM grupa JOIN uzytkownik USING(kod_uz)
WHERE rodzaj_zajec='s');

-- zad 2
SELECT COUNT(DISTINCT wybor.kod_uz), przedmiot.nazwa
FROM przedmiot
LEFT JOIN przedmiot_semestr ON (przedmiot.kod_przed=przedmiot_semestr.kod_przed)
LEFT JOIN grupa ON (przedmiot_semestr.kod_przed_sem=grupa.kod_przed_sem)
LEFT JOIN wybor ON (grupa.kod_grupy=wybor.kod_grupy)
WHERE przedmiot.rodzaj='k'
GROUP BY przedmiot.kod_przed, przedmiot.nazwa;

-- zad 3
SELECT DISTINCT uzytkownik.kod_uz, uzytkownik.imie, uzytkownik.nazwisko
FROM wybor
JOIN grupa ON (grupa.kod_grupy=wybor.kod_grupy)
JOIN uzytkownik ON (uzytkownik.kod_uz=grupa.kod_uz)
GROUP BY grupa.kod_grupy, uzytkownik.kod_uz, uzytkownik.imie,
uzytkownik.nazwisko, grupa.max_osoby
HAVING max_osoby < COUNT(*);

-- zad 4
SELECT DISTINCT uzytkownik.kod_uz, uzytkownik.imie, uzytkownik.nazwisko
FROM wybor
JOIN uzytkownik ON (uzytkownik.kod_uz=wybor.kod_uz)
JOIN grupa ON (grupa.kod_grupy=wybor.kod_grupy)
JOIN przedmiot_semestr ON (grupa.kod_przed_sem=przedmiot_semestr.kod_przed_sem)
JOIN przedmiot ON (przedmiot_semestr.kod_przed=przedmiot.kod_przed)
WHERE przedmiot.nazwa LIKE 'Algorytmy i struktury danych%'
AND uzytkownik.kod_uz IN
(SELECT uzytkownik.kod_uz
FROM wybor w2
JOIN uzytkownik u2 ON (u2.kod_uz=w2.kod_uz)
JOIN grupa g2 ON (g2.kod_grupy=w2.kod_grupy)
JOIN przedmiot_semestr ps2 ON (g2.kod_przed_sem=ps2.kod_przed_sem)
JOIN przedmiot p2 ON (ps2.kod_przed=p2.kod_przed)
WHERE p2.nazwa LIKE 'Matematyka dyskretna%'
AND ps2.semestr_id > przedmiot_semestr.semestr_id
);

-- 5
SELECT przedmiot.nazwa
FROM przedmiot
JOIN przedmiot_semestr USING (kod_przed)
JOIN grupa USING (kod_przed_sem)
JOIN wybor USING (kod_grupy)
WHERE rodzaj='p' AND rodzaj_zajec='w'
GROUP BY przedmiot.nazwa, przedmiot.kod_przed
HAVING COUNT(DISTINCT wybor.kod_uz)>=ALL(
SELECT COUNT(DISTINCT wybor.kod_uz)
 FROM przedmiot
 JOIN przedmiot_semestr USING(kod_przed)
 JOIN grupa USING(kod_przed_sem)
 JOIN wybor USING(kod_grupy)
 WHERE rodzaj='p' AND rodzaj_zajec='w'
 GROUP BY przedmiot.kod_przed);

-- 6
SELECT POM.semestr_id,nazwisko FROM
(SELECT semestr.semestr_id AS "semestr_id",
 MIN(data) AS "data"
 FROM semestr
 JOIN przedmiot_semestr USING(semestr_id)
 JOIN grupa USING(kod_przed_sem)
 JOIN wybor USING(kod_grupy)
 WHERE nazwa LIKE '%letni%'
 GROUP BY semestr.semestr_id) POM 
 JOIN wybor USING(data)
 JOIN grupa USING(kod_grupy)
 JOIN przedmiot_semestr USING(kod_przed_sem,semestr_id)
 JOIN uzytkownik ON wybor.kod_uz=uzytkownik.kod_uz
 ORDER BY 1,2 ;

 -- 9
WITH BD AS (
SELECT DISTINCT wybor.kod_uz
FROM wybor
JOIN grupa USING (kod_grupy)
JOIN przedmiot_semestr USING (kod_przed_sem)
JOIN przedmiot USING (kod_przed)
JOIN semestr USING (semestr_id)
WHERE semestr.nazwa='Semestr letni 2016/2017'
AND przedmiot.nazwa='Bazy danych'
AND grupa.rodzaj_zajec='w'),
SK AS (
SELECT DISTINCT wybor.kod_uz
FROM wybor
JOIN grupa USING (kod_grupy)
JOIN przedmiot_semestr USING (kod_przed_sem)
JOIN przedmiot USING (kod_przed)
JOIN semestr USING (semestr_id)
WHERE semestr.nazwa='Semestr letni 2016/2017'
AND przedmiot.nazwa='Sieci komputerowe'
AND grupa.rodzaj_zajec='w')
((SELECT * FROM BD) EXCEPT (SELECT * FROM SK)) UNION
((SELECT * FROM SK) EXCEPT (SELECT * FROM BD));