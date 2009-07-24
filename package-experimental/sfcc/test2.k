using sfcc.*;

String s;

enm = new CIMEnumeration();

op = new CIMObjectPath("root/cimv2","Linux_Hello");

op.addKey("CreationClassName","Linux_Hello");

op.addKey("Name","libxml2");

cc = new CIMClient("192.168.59.202");

s = cc.invokeMethod(op, "cal", "src", "/usr/local/share/konoha/sample/fib.k", "", "");

s;

ins = new CIMInstance(cc,op);

op1 = ins.getObjectPath();

op1.toString();

