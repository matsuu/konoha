sub fib {
    my $n = shift;
    if ($n < 2) {
        return $n;
    } else {
        return &fib($n-1) + &fib($n-2);
    }
}
print &fib(36);
