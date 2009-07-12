function isprime(n, primes)
    nsqrt = n ^ 0.5
    for i = 1, #primes do
    if nsqrt < primes[i] then break end
    if n % primes[i] == 0 then return false end
    end
    return true
end

primes = {}

for i = 2, arg[1] * 1 do
if isprime(i, primes) then primes[#primes + 1] = i end
end


