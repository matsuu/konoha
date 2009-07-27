using sfcc.*;

String.. s1;

String[] s2;

enm = new CIMEnumeration();

op = new CIMObjectPath("root/cimv2","Linux_RpmPackage");

op.addKey("CreationClassName","Linux_RpmPackage");

op.addKey("Name","libxml2");

cc = new CIMClient("192.168.59.202");

ins = new CIMInstance(cc,op);

s1 = cc.enumClassNames(op,0);

foreach(String s in s1){

    OUT << "s1:" << s << EOL;

}

s2 = ins.getProperty();

foreach(s in s2..){

 OUT << s << EOL;

}
