console.log(([![]]+[][[]])) // false + undefined jako jeden string;
//undefined - z [] chcemy wziac 0 element
console.log(![] + []) // []  z ! - daje false , po dodaniu kolejnej [] mamy dalej bool false

console.log(+[]) // +[], konwertuje pusta tablice do liczby - 0

console.log(+!+[]);
//// !+[]  zero do true, dalej +!+[] konwertuje true do 1
console.log(!+[]+!+[]) // true + 1 = 2 

console.log(+!+[]+[+[]]) // 1 + tablica, ktora konwertuje sie do stringa '0' stad wynikiem jest string '10'

console.log((![]+[])[+[]] + (![]+[])[+!+[]] + ([![]]+[][[]])[+!+[]+[+[]]] + (![]+[])[!+[]+!+[]]);
