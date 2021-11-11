
function forEach(a, f) {
    for (const i of a) {
        f(i);
    }
}

function map( a, f ) {
    var ans = [];
    for (const i of a) {
        ans.push( f(i) );
    }
    // mozna tez return ans, ale w poleceniu filter ma wypisac [1,2]
    console.log(ans);
}

function filter( a, f ) {
    var ans = [];
    for (const i of a) {
        if ( f(i) )
            ans.push(i);
    }
    // mozna tez return ans, ale w poleceniu filter ma wypisac [1,2]
    console.log(ans);
}
var a = [1,2,3,4];
forEach( a, _ => { console.log( _ ); } );
// [1,2,3,4]

filter( a, _ => _ < 3 );
// [1,2]

map( a, _ => _ * 2 );
// [2,4,6,8]