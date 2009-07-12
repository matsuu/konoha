
import sys

def isprime(n, primes):
    sqrt = n ** 0.5
    for i in primes:
        if sqrt < i: break
        if n % i == 0: return False
    return True

def main():
    primes = []

    for i in range(2, int(sys.argv[1])):
        if isprime(i, primes):
            primes.append(i)
main()

