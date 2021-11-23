const readline = require('readline');
let rl = readline.createInterface({
      input: process.stdin,
      output: process.stdout,
});


rl.question('Jak masz na imię?\n', (ans) => {
    console.log(`Witaj ${ans}!`);
    rl.close();
});
