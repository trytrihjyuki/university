
function* fibg() {
    var fib_num = [1,1];
    while (true) {
        var new_num = fib_num[1] + fib_num[0];
        fib_num[0] = fib_num[1];
        fib_num[1] = new_num;
        yield fib_num[0];
    }
}

function* take(it, top) {
    for (var i = 0; i < top; i++)
        yield it.next().value;
}



// zwróć dokładnie 10 wartości z potencjalnie
// "nieskończonego" iteratora/generatora
for (let num of take( fibg(), 10 ) ) {
    console.log(num);
}
