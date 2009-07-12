n = 9000;
x = new Int[n];
y = new Int[n];

for (i=0; i < n; i++) {
    x[i] = i + 1;
}

for (i=0; i < 999; i++) {
    for (j=n-1; j >= 0; j--) {
        y[i] = y[i] + x[j];
    }
}

print y;
