#include <stdlib.h>
#include <math.h>
/*
 *  prime.c
 *  gcc -pipe -Wall -O3 -fomit-frame-pointer -lm prime.c -o prime
 */

__attribute__((fastcall)) int isprime(int n, const int *primes, int len)
{
    int nsqrt = (int) sqrt((double) n);
    int i = 0;
    while(i < len){
        if(nsqrt < primes[i]){ break; }
        if(n % primes[i] == 0){ return 0; }
        i++;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    int lim = atoi(argv[1]);
    int *primes = (int *) alloca(sizeof(int) * (lim / (log((double)lim) - 2)));
    int len = 0;
    int i;

    for (i = 2; i < lim; i++) {
        if(isprime(i, primes, len)){
            primes[len++] = i;
        }
    }
    return 0;
}

