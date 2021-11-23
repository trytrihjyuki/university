function createGenerator(n) {
    
    return function() {
        var _state = 0;

        return {
            next: function() {
                return {
                    value: _state,
                    done : _state++ >= n
                }
            }
        }
    }
}

var foo = {
    [Symbol.iterator] : createGenerator(2)
};

var bar = {
    [Symbol.iterator] : createGenerator(4)
};

for (var f of foo)
    console.log(f);

for (var f of bar)
    console.log(f);


