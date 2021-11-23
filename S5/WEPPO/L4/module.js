// simple module for zad3
console.log('[+] module');
exports.x = 0;
let zad3 = require('./zad3.js');
console.log('zad3.x = ', zad3.x);
exports.x = 1;
console.log('[-] module');
let tmp  = require("./module.js"); // odwolanie sie do siebie
