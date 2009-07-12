
sub prime{
    $sqrt = sqrt($i);
    foreach(@primes){
        last if $sqrt < $_;
        return 0 if $i % $_ == 0;
    }
    return 1;
}

$i = 2;
$lim = @ARGV[0] * 1;
@primes = ();

while($i < $lim){
    push(@primes, $i) if &prime;
    $i += 1;
}

