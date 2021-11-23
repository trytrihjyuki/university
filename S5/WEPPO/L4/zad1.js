class Tree {
    constructor(val, left, right) {
        this.left = left;
        this.right = right;
        this.val = val;
    }
    [Symbol.iterator] = function* (){
        var q = [];
        q.push(this);
        while (q.length) {
            var node = q.shift();
            if (node.right) q.push(node.right);
            if (node.left) q.push(node.left);
            yield node.val;
        }
    }
}


var root = new Tree( 1,
    new Tree( 2, new Tree( 3 ) ), new Tree( 4 ));

for ( var e of root ) {
    console.log( e );
}
