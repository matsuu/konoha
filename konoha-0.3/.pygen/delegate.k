class C {
  int succ(int n) {
    return n+1;
  }
}

c = new C();
c.succ(1)

f = delegate(c, succ);
f(1)

