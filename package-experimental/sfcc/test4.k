using sfcc.*;

String s;

enm = new CIMEnumeration();

op = new CIMObjectPath("root/cimv2","Linux_Hello");

op.addKey("CreationClassName","Linux_Hello");

op.addKey("Name","hello");

cc = new CIMClient("192.168.59.202");

s = cc.invokeMethod(op, "fib.k", "");

OUT << s << EOL;

ins = new CIMInstance(cc,op);

OUT << op.toString() << EOL;

