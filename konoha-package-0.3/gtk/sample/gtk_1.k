using gtk.*;
g=new Gtk();
g.init(new Array());
Window w = g.createWindow();
w.setTitle("hello konoha!");
w.setSize(200,100);
Button b = g.createButton("hoge");
b.setAction();
b.setVisible(true);
w.addButton(b);
w.setVisible(true);

g.main();
