var express = require('express');

var app = express();
app.set('view engine', 'ejs');
app.set('views', './views');
app.disable('etag');

app.get('/', (req, res) => {
    const phone = {
        name: "Phone",
        boxes: [
            {value: 1, text: "Samsung"},
            {value: 2, text: "Apple"},
            {value: 3, text: "Huawei"},
            {value: 4, text: "Xiaiomi"},
            {value: 5, text: "LG"},
            {value: 6, text: "Oppo"}
        ]
    }

    res.render("index.ejs", {
        phone: phone
    });
});

app.listen(3000);
