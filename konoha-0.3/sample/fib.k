#!/usr/local/bin/konoha

int fib(int n) {
	if(n<3) return 1;
	return fib(n-1)+fib(n-2);
}

void test() {
	n = fib(36);
	print "fib(36)=", n;
	if(n == 14930352) {
		print "fib(36)..ok";
	}
}

void main(String[] argv) {
	test()
}

