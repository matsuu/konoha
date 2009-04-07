
c = new Connection("sqlite3:test.sqlite");
rs = c.query("select * from tbl");
while(rs.next()) {
  print %dump(rs);
}
rs.close();

