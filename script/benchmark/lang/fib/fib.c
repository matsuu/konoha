#include <stdio.h>
/*
 * gcc-mp-4.4 -pipe -Wall -O3 -fomit-frame-pointer fib.c
 */
__attribute__((fastcall)) int fib(int n)
{
    if (n < 2) {
        return n;
    } else {
        return fib(n-1) + fib(n-2);
    }
}
int main(void)
{
    printf("%d\n",fib(36));
    return 0;
}
