var z1 = true;
var z2 = 'test';
var z3 = new Boolean(true);

console.log(typeof z1); //"boolean"
console.log(typeof z2); //"string"
console.log(typeof z3); //"object"
console.log(z1 instanceof Boolean); //false
console.log(z2 instanceof String); //false
console.log(z3 instanceof Boolean); //true

// instance of zwraca true lub false - odpowiada na pytanie czy dany obiekt jest instancja okreslonego typu


// typeof zwraca typ obiektu - prymitywny lub inny (obiekt)
// typy prymitywne: boolean, null, string, number, undefined
