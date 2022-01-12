var express = require('express');
var multer = require('multer');

var app = express();
app.set('view engine', 'ejs');
app.set('views', './views');
app.disable('etag');

app.get('/', (req, res) => {
     res.render('index');
});

const srg = multer.diskStorage({
    destination: './uploads/',
    filename: function (req, file, cb) {
        cb(null, file.originalname);
      }
})

var upload = multer({ storage: srg });
app.post('/', upload.single('file'), (req, res) => {
    res.render('index');
});

app.listen(3000);