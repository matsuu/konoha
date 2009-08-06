using sfcc.*;

class Diagnosis{
    String Case;
    String Part;
    
    void new(String Case, String Part){
	this.Case = Case;
	this.Part = Part;
    }

    void report(String host){
	cc = new CIMClient(host);	
	op = new CIMObjectPath("root/cimv2","DEOS_DCare");
	op.addKey("CLASS","Diagnosis");
	OUT << cc.invokeMethod(op, "recieve", this.Case + "," + this.Part) << EOL;	
    }

}


Diagnosis d = new Dignosis("SoftwareAging", "OS");
d.report();
