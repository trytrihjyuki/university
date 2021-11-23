function fibit() {
    var fib_num = [0,1];

    return  {
        next : function() {
            var new_num = fib_num[1] + fib_num[0];
            fib_num[0] = fib_num[1];
            fib_num[1] = new_num;
            return {
                value: fib_num[0],
                done : false
            }
        }
    }
}

function* fibg() {
    var fib_num = [1,1];
    while (true) {
        var new_num = fib_num[1] + fib_num[0];
        fib_num[0] = fib_num[1];
        fib_num[1] = new_num;
        yield fib_num[0];
    }
}

var itek = fibit();
for (var i; i = itek.next(), !itek.done;) {
    if (i.value > 30) break;
    console.log(i.value);
}

// po generatorze mozemy sie iterowac for_of
for (var i of fibg()) {
    if (i > 30) break;
    console.log(i);
}
