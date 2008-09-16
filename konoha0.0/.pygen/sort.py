import random

a = []
i = 0
while i < 10000:
	a.append(random.randint(0, 1000))
	i += 1

print len(a)

i = 0
while i < len(a) - 1:
	j = i + 1
	while j < len(a):
		if a[i] > a[j]:
			n = a[i]
			a[i] = a[j]
			a[j] = n
		j += 1
	i += 1

print len(a)

