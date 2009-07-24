using sfcc.*;

String.. s1; 

String.. s2;

enm = new CIMEnumeration();

op = new CIMObjectPath("root/cimv2","");

cc = new CIMClient("192.168.59.202");

s1 = cc.enumClassNames(op,0);

print s1;

