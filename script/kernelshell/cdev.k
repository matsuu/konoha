cdev = new Chardev("hi");

String r() { return "konoha"; }

Closure cc = delegate(r);
cdev.addFunc("read", cc);
cdev.regist();
