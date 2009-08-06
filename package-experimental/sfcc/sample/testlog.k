using sfcc.*;

String s;

op = new CIMObjectPath("root/cimv2","Linux_Hello");

op.addKey("CreationClassName","Linux_Hello");

op.addKey("CLASS","Test");

cc = new CIMClient("192.168.59.202");

s = cc.invokeMethod(op, "write", ["failed","kernel"]);

OUT << s << EOL;

