OUT << "int" << EOL;
class A{
    int i;
}
A a=new A();
print a.i;
print a;
OUT << "a.i is 0?" << (a.i == 0) << EOL << EOL;


OUT << "float" << EOL;
class B{
    float f;
}

B b=new B();
zero = 0.0;
print b.f;
print b;
OUT << "b.f is 0.0?" << (b.f == zero) << EOL << EOL;

OUT << "string" << EOL;
class C{
    String s;
}
C c=new C();
print c.s;
print c;
OUT << "c.s is ''?" << (c.s == "") << EOL;


