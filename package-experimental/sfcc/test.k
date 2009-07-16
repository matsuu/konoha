using sfcc.*;

int rc;
String msg;
CIMCString str = new CIMCString();
String host = "localhost";
String userid = "Kato";
String passwd = "konoha";
String port = "5988";

CIMCStatus status = new CIMCStatus();
CIMCClient client = new CIMCClient();
CIMCObjectPath op = new CIMCObjectPath();
CIMCEnumeration enm = new CIMCEnumeration();

ce = Sfcc.mkCIMCEnv("XML",0,status);

client = ce.connect(host, "http", port, userid, passwd, status);

op = ce.newObjectPath("root/cimv2",status);

enm = client.enumClassNames(op,0,status);


if(status.rc == 0){   
    while (enm.hasNext()) {
	op = enm.getNext();
	str = op.toString();
    }
}