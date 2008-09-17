class Person {
  String name;
  Int age;
}

Connection c = new Connection("test");
ResultSet rs = c.query("");
print %dump(rs.next());


