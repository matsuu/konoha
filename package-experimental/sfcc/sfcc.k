class Sfcc;
class CIMCEnv; //
class CIMCStatus{
    int rc;
    String msg;
}; //
class CIMCClient; //
class CIMCObjectPath; //
class CIMCEnumeration; //
class CIMCString; //
class CIMCData; //
    




//-------------Sfcc----------------
int Sfcc.mkCIMCEnvrc(String s, int i); 
String Sfcc.mkCIMCEnvmsg(String s, int i); 
CIMCEnv Sfcc.mkCIMCEnvce(String s, int i); 
CIMCEnv Sfcc.mkCIMCEnv(String s, int i, CIMCStatus status){
    status.rc = this.mkCIMCEnvrc(s,i); 
    status.msg = this.mkCIMCEnvmsg(s,i);
    return this.mkCIMCEnvce(s,i); 
}; 
//void Sfcc.CMRelease(String msg);

//-------------------CIMCEnv-----------------
CIMCClient CIMCEnv.connectcl(String cim_host, String http, String cim_host_port, String cim_host_userid, String cim_host_passwd);
int CIMCEnv.connectrc(String cim_host, String http, String cim_host_port, String cim_host_userid, String cim_host_passwd);
String CIMCEnv.connectmsg(String cim_host, String http, String cim_host_port, String cim_host_userid, String cim_host_passwd);

CIMCClient CIMCEnv.connect(String cim_host, String http, String cim_host_port, String cim_host_userid, String cim_host_passwd, CIMCStatus status){
    status.rc = this.connectrc(cim_host,http,cim_host_port,cim_host_userid,cim_host_passwd);
    status.msg = this.connectmsg(cim_host,http,cim_host_port,cim_host_userid,cim_host_passwd);
    return this.connectcl(cim_host,http,cim_host_port,cim_host_userid,cim_host_passwd);
};

int CIMCEnv.newObjectPathrc(String path);
String CIMCEnv.newObjectPathmsg(String path);
CIMCObjectPath CIMCEnv.newObjectPathop(String path);

CIMCObjectPath CIMCEnv.newObjectPath(String path, CIMCStatus status){
    status.rc = this.newObjectPathrc(path);
    status.msg = this.newObjectPathmsg(path);
    return this.newObjectPathop(path);
};
void CIMCEnv.release();







//-------------------CIMCStatus-----------------

// 特になし?


//-------------------CIMCClient-----------------
int CIMCClient.enumClassNamesrc(CIMCObjectPath op, int flag);
String CIMCClient.enumClassNamesmsg(CIMCObjectPath op, int flag);
CIMCEnumeration CIMCClient.enumClassNamesenm(CIMCObjectPath op, int flag);
CIMCEnumeration CIMCClient.enumClassNames(CIMCObjectPath op, int flag, CIMCStatus status){
    status.rc = this.enumClassNamesrc(op,flag);
    status.msg = this.enumClassNamesmsg(op,flag);
    return this.enumClassNamesenm(op,flag);
};
void CIMCClient.release();






//-------------------CIMCObjectPath-----------------
String CIMCObjectPath.toString();
void CIMCObjectPath.release();







//-------------------CIMCEnumeration-----------------
boolean CIMCEnumeration.hasNext();
CIMCObjectPath CIMCEnumeration.getNext();
void CIMCEnumeration.release();








//-------------------CIMCString-----------------
String CIMCString.getCharPtr();


//-------------------CIMCData-----------------
