function is_prime(n)
{
    for (let i=2; i*i <= n; i++)
        if (!(n % i)) return false
    return true
}

primes = []
for (let i=2; i <= 100000; i++)
{
    if (is_prime(i)) primes.push(i)
}

for (let i = 0; i <= 10; i++)
        console.log(primes[i]);

console.log(primes.length);
