using libvirt.*;
import "Diagnosis.k";

class DCare {
    void receive(Diagnosis dig){
        symptom = dig.symptom;
        part    = dig.part;
        if(symptom == "SoftwareAging" && part == "OS"){
            OUT << symptom + ":" + part<< EOL;
            Virt.init();
            Connection c = new Connection("qemu:///system");
            Domain d = c.getDomainByName("fedora11");
            OUT << "destory :" + d.destroy() << EOL;
            c.close();
        }
    }
}

void receive(String s){
    String[] a = s.split(",");
    symptom = a[0];
    part    = a[1];
    Diagnosis d = new Diagnosis(symptom, part); 
    DCare.receive(d);
}
