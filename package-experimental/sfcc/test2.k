using sfcc.*;

String s;

enm = new CIMEnumeration();

op = new CIMObjectPath("root/cimv2","Linux_OperatingSystem");

op.addKey("CreationClassName","Linux_OperatingSystem");

op.addKey("Name","linux");

cc = new CIMClient("192.168.59.202");

s = cc.invokeMethod(op, "execCmd", "cmd", "ls", "", "");

OUT << s << EOL;

ins = new CIMInstance(cc,op);

OUT << op.toString() << EOL;

