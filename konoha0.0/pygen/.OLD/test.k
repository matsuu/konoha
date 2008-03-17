#!/usr/bin/konoha

print "hello,world";

boolean err = false;

int fact(int n) {
   if(n == 1) return 1;
   return n * fact(n - 1);
}

if(fact(10) != 3628800) {
   print "factorial failed";
   err = true;
}

int test_loop() {
   int c = 0;
   while(c < 20) {
     c += 1;
     if(c % 2 == 1) continue;
     if(c == 16) break;
   }
   return c;
}

if(test_loop() != 16) {
  print "loop failed";
  err = true;
}

class Person {
  String name = "naruto";
  int age = 16;
}

class Student extends Person {
  String univ = "YNU";
}

Student s = new Student();
if(s.univ != "YNU") {
  print "class failed";
  err = true;
}

if(err) {
  print "Dont' release this package";
}


