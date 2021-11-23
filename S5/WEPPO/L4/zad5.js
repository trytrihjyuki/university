var fs = require('fs');
var txt = fs.readFileSync("plik.txt").toString();
console.log(txt);
