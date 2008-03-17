#!/usr/bin/konoha

class Person {
  String name;
  int age;
}

class Student extends Person {
  String id;
}

Student s = new Student(); // default
s.name = "kobayashi";
s.age = 23;
s.id = "XXXXXX";

print %dump(s);

