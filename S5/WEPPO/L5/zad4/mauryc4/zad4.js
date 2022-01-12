const express = require('express');
const app = express();

app.set('view engine', 'ejs');
app.set('views', './views');
app.use(express.urlencoded({ extended:true }));

let data = {};

app.get('/', (req, res) => {
    res.render('index');
});

app.get('/print', (req, res) => {
    res.render('print', data);
});

app.post('/', (req, res) => {
    first_name =  req.body.first_name;
    last_name = req.body.last_name;
    class_name = req.body.class_name;
    for (let i = 1; i <= 10; i ++) {
        req.body[`zad${i}`] = req.body[`zad${i}`] || '0';
    }
    // console.log(req.body[`zad1`]);
    if (!first_name || !last_name || !class_name) {
        res.render('index', req.body );
    }
    else {
        data = req.body;
        res.redirect('/print');
    }
});

app.listen(5000);