using libvirt.*;
class DCare;
void DCare.receive(String s){
    String[] a = s.split(",");
    symptom = a[0];
    part    = a[1];
    if(symptom == "SoftwareAging" && part == "OS"){
        OUT << s << EOL;
        Virt.init();
        Connection c = new Connection("qemu:///system");
        Domain d = c.getDomainByName("fedora11");
        d.destroy();
        c.close();
    }
}
