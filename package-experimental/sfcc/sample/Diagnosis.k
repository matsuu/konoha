class Diagnosis{
    String symptom;
    String part;

    public Diagnosis(String s, String p){
        this.symptom = s;
        this.part = p;
    }

    void report(String host){
        cc = new CIMClient(host); 
        op = new CIMObjectPath("root/cimv2","DEOS_DCare");
        op.addKey("CLASS","Diagnosis");
        //s = 
        cc.invokeMethod(op, "recieve", this.symptom + "," + this.part);
        //os.system(s);
    }

}


