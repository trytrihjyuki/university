function sum(...args) {
    var s = 0;
    for (const i of args)
        s += i;
    return s;
}

console.log(sum(1,2,3,4,5))
