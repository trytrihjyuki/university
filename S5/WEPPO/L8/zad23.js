const { Client } = require('pg');

const db = new Client({
        user: 'maurykdell',
        host: 'localhost',
        database: 'maurykdell',
        password: 'password',
        port: 5432,
});

db.connect();
// ZAD 2
async function getAllPeople() {
      let response;
      response = await db.query('SELECT * FROM osoba;');
      return response.rows;
}

async function printAllPeople() {
      const people = await getAllPeople();
      console.log(people);
};
// przykładowy select asynchroniczny
printAllPeople();

async function addNew() {
      const response = await db.query(`select nextval('osoba_id_seq')`);
      const new_id = response.rows[0].nextval;
      console.log('NEW ADDED ID: ', new_id);
      db.query(`INSERT INTO osoba VALUES (`+new_id+`, 'Marta', 'Lewandowska', 'marta927@wp.pl', 'female', 12)`)
};
addNew();

// ZAD 3
db.query(`UPDATE osoba SET imie='Jakub' WHERE id=1`);
printAllPeople();
db.query(`DELETE FROM osoba WHERE imie='Jakub'`);
printAllPeople();
