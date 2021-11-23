var readline = require('readline');
var fs = require('fs');

var file = readline.createInterface({
    input: fs.createReadStream('access.log.2')
});

var ips = {};
file.on('line', function (line) {
    s = line.split(' ')[0];
    if (ips[s] == undefined) {
        ips[s] = 1;
    }
    else {
        ips[s] += 1;
    }
});

file.on('close', function() {
    var items = Object.keys(ips).map(function(ip) {
        return [ip, ips[ip]];
    });
    items.sort(function(a, b) {
        return b[1] - a[1];
    });
    for(let a in items.slice(0,3)) {
        console.log("IP: ", items[a][0], " logs: ", items[a][1]);
    }
});

