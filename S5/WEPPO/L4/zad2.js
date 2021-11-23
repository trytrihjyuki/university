function Foo() {
    console.log("foo obj");
}

Foo.prototype.Bar = function() {
        var Qux = function() {
            console.log('private Qux');
        }
        Qux();
}

var o = new Foo();
o.Bar();
// o.Qux(); // error
