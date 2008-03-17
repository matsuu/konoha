#!/usr/bin/konoha

any fib(any n) {
	if(n == 1 or n == 2) return n;
	return fib(n - 1) + fib(n - 2);
}

print fib(16);

