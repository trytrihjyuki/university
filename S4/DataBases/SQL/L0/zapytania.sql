SELECT imie, nazwisko
FROM uzytkownik JOIN wybor using (kod_uz)
    JOIN grupa USING (kod_grupy)
    JOIN przedmiot_semestr using (kod_przed_sem)
    JOIN przedmiot using (kod_przed)
    JOIN semestr USING (semestr_id)
    WHERE semestr>0
    AND przedmiot.nazwa='Matematyka dyskretna (M)'
    AND rodzaj_zajec='w'
    AND semestr.nazwa='Semestr zimowy 2017/2018'
ORDER BY data
LIMIT 1;

SELECT kod_grupy
FROM grupa JOIN przedmiot_semestr USING (kod_przed_sem)
    JOIN przedmiot USING (kod_przed)
    JOIN semestr USING (semestr_id)
    WHERE semestr.nazwa='Semestr zimowy 2017/2018'
    AND przedmiot.nazwa='Matematyka dyskretna (M)'
    AND rodzaj_zajec='w';

SELECT w1.data-w2.data
FROM wybor w1 JOIN grupa USING (kod_grupy) 
    JOIN wybor w2 USING (kod_grupy) 
WHERE grupa.kod_grupy=5649
ORDER BY 1 desc;
SELECT w1.data-w2.data

SELECT COUNT(DISTINCT przedmiot.nazwa)
FROM przedmiot JOIN przedmiot_semestr USING (kod_przed)
JOIN grupa USING (kod_przed_sem)
WHERE przedmiot.rodzaj='o' AND grupa.rodzaj_zajec='e';

SELECT COUNT(DISTINCT uzytkownik.kod_uz)
FROM uzytkownik JOIN grupa USING (kod_uz)
JOIN przedmiot_semestr USING (kod_przed_sem)
JOIN przedmiot USING (kod_przed)
JOIN semestr USING (semestr_id)
WHERE semestr.nazwa LIKE 'Semestr zimowy%'
AND grupa.rodzaj_zajec IN ('c', 'C')
AND przedmiot.rodzaj='o';

SELECT DISTINCT nazwa
FROM przedmiot JOIN przedmiot_semestr USING (kod_przed)
JOIN grupa USING (kod_przed_sem)
JOIN uzytkownik USING (kod_uz)
WHERE uzytkownik.nazwisko='Urban'
ORDER BY nazwa;

SELECT COUNT(*)
FROM uzytkownik
WHERE uzytkownik.nazwisko LIKE 'Kabacki%';

SELECT COUNT(DISTINCT u.kod_uz)
FROM uzytkownik u
JOIN wybor w1 USING (kod_uz)
JOIN grupa g1 USING (kod_grupy)
JOIN przedmiot_semestr ps1 USING (kod_przed_sem)
JOIN przedmiot p1 USING (kod_przed)
JOIN wybor w2 ON (u.kod_uz=w2.kod_uz)
JOIN grupa g2 ON (g2.kod_grupy=w2.kod_grupy)
JOIN przedmiot_semestr ps2 ON (g2.kod_przed_sem=ps2.kod_przed_sem)
JOIN przedmiot p2 ON (p2.kod_przed=ps2.kod_przed)
WHERE p1.nazwa='Algorytmy i struktury danych (M)'
AND p2.nazwa=p1.nazwa
AND ps1.kod_przed_sem<>ps2.kod_przed_sem;

SELECT COUNT(nazwa)
FROM przedmiot
JOIN przedmiot_semestr USING (kod_przed)
WHERE przedmiot.rodzaj='o'
AND semestr_id=27;

SELECT COUNT(DISTINCT kod_grupy)
FROM grupa
JOIN przedmiot_semestr USING (kod_przed_sem)
JOIN przedmiot USING (kod_przed)
JOIN semestr USING (semestr_id)
WHERE semestr.nazwa='Semestr zimowy 2017/2018'
AND przedmiot.nazwa='Logika dla informatyków'
AND grupa.rodzaj_zajec in ('c', 'C');