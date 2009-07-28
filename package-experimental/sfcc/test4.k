using sfcc.*;

String s;

enm = new CIMEnumeration();

op = new CIMObjectPath("root/cimv2","Linux_Hello");

op.addKey("CreationClassName","Linux_Hello");

op.addKey("CLASS","Test");

cc = new CIMClient("192.168.59.202");

s = cc.invokeMethod(op, "func1", ["1","1"]);

OUT << s << EOL;

