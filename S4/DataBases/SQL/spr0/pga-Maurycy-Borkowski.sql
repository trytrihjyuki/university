-- Maurycy Borkowski, PGA
-- Zadanie 1
SELECT DISTINCT city.*
FROM city
JOIN airport ON (airport.city=city.name)
WHERE city.elevation<100
AND city.country='PL'
ORDER BY city.name;
-- Zadanie 2
SELECT DISTINCT sea.name, sea.area
FROM sea
JOIN river ON (sea.name=river.sea)
JOIN geo_river ON (river.name=geo_river.river)
WHERE geo_river.country='F'
AND river.length>800
ORDER BY sea.area DESC;
