#!/usr/bin/python

def fib(n):
	if n == 1 or n == 2: return n
	return fib(n - 1) + fib(n - 2)

fib(36)
