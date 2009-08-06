using sfcc.*;

String.. s1; 

op = new CIMObjectPath("root/cimv2","");

cc = new CIMClient("192.168.59.202");

s1 = cc.enumClassNames(op,0);

foreach(String s in s1){

    OUT << s << EOL;

}

