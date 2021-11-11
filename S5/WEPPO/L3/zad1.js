/* Definiujemy obiekt */
var obj = {
    n :  4,

    f : function(x) {
        return 2*this.n
    },

    get nnn() {
        return this.n;
    },

    set nnn(x) {
        this.n = x;
    }
};



Object.defineProperty(obj , 'a' , {
    value : 2,
    writable : true,
    enumerable: true
});


Object.defineProperty(obj , 'g' , {
    value : function(x) {
        return this.a + x;
    },
    enumerable: true
});


Object.defineProperty(obj , 'c' , {
    get : function() {
        return this.a;
    },
    set : function(x) {
        this.a = x;
    },
    enumerable: true
});

obj.c = 3;
console.log(obj);
obj.c = obj.g(2);
console.log(obj);

/*
Pole, metoda i właściwość może być dodane przez Object.defineProperty lub przez przypisanie np. obj.a = 2;
Właściwość z akcesoriami musi być dodana przez Object.defineProperty.
*/