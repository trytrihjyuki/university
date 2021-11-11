
def is_palindrom(w):
    w = w.lower()                             # lowercase
    w = w.replace(' ', '')                    # no space
    w = ''.join(l for l in w if l.isalnum())  # no punctation
    return w == w[::-1]

print(is_palindrom('Ala, ma kotka.'))
print(is_palindrom("Eine güldne, gute Tugend: Lüge nie!"))


const a = 1; const b = 2; const c = 3;
(function firstFunction () {
    const b = 5; const c = 6;

    (function secondFunction () {
      const b = 8;
      console.log(`a: ${a}, b: ${b}, c: ${c}`);

      (function thirdFunction () {
        const a = 7; const c = 9;

        (function fourthFunction () {
          const a = 1; const c = 8;
        })()
      })()
    })()
  })()