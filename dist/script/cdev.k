int fib(int n) { if(n < 3){ return 1;} return fib(n-1) + fib(n-2);}
cdev = new Chardev("hi");

String r() { return (String) fib(36) + "\n"; }

Closure cc = delegate(r);
cdev.addFunc("read", cc);
cdev.regist();
