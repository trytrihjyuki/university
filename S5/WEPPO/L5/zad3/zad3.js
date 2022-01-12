var http = require('http');
var express = require('express');

var app = express();
app.use( (req, res) => {
        res.header('Content-disposition', 'attachment; filename = "data.txt"');
        res.end('przykladowy plik');
});
http.createServer(app).listen(4000)
