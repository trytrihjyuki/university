function fib_iter(n)
{
    if (n <= 2) return 1
    last = 1
    pre_last = 1
    for (let i = 3; i <= n; i++)
    {
        curr = last + pre_last;
        last = pre_last;
        pre_last = curr;
    }

    return curr;
}

function fib_rec(n)
{
    if (n <= 2) return 1;
    
    return fib_rec(n-1) + fib_rec(n-2);
}

// przy n > 40 już widać znaczącą różnicę między algorytmiami
// na przeglądarkach działa szybciej niż w node, chrome najszybszy
for (let i = 10; i < 45; i++)
{
    console.log('\nN = ', i)
    console.time('Iteracyjnie')
    fib_iter(i)
    console.timeEnd('Iteracyjnie')
    
    console.time('Rekurencyjnie')
    fib_rec(i)
    console.timeEnd('Rekurencyjnie')
}
