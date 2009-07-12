def isprime(n, primes)
    sqrt = n ** 0.5
    for i in primes
        break if sqrt < i
        return false if n % i == 0
    end
    return true
end

primes = []

for i in 2..ARGV[0].to_i
    primes.push(i) if isprime(i, primes)
end

