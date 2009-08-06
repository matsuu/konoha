using sfcc.*;

//String.. s;

op = new CIMObjectPath("root/cimv2","Linux_Hello");

op.addKey("CreationClassName","Linux_Hello");

//op.addKey("Name","linux");

cc = new CIMClient("192.168.59.202");

s = cc.enumInstanceNames(op);

typeof(s);