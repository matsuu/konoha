using math.*;

boolean isprime(Int n, Int[] primes)
{
    int sqrt = (int) Math.sqrt(n);
    foreach (int i in primes) {
        if (sqrt < i) {
            break;
        } else if ( n % i == 0) {
            return false;
        }

    }
    return true;
}

void main (String[] args)
{
    limit = (int)args[1];
    primes = new Int[](limit);
    for (i=2; i < limit; i++) {
        if (isprime(i, primes)) {
            primes.add(i);
        }
    }
}
