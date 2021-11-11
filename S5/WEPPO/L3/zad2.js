function fib(n) {
    if (n >= 2) return fib( n - 1 ) + fib( n - 2 );
    return 1;
}

function memoize (f) {

    var cache = {};

    return function (n) {

        if ( n in cache ) {
            return cache[n]
        } else {
            var res = f(n);
            cache[n] = res;
            return res;
        }
    }
}

var memofib = memoize(fib);

var t1 = performance.now()
console.log(memofib(40));
var t2 = performance.now()
console.log('wolniej: ' + (t2-t1))

var fib = memoize(fib);

var t3 = performance.now()
console.log(memofib(4000));
var t4 = performance.now()
console.log('szybciej: ' + (t4-t3))