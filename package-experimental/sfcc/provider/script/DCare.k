
String receive(String s){
    a = s.split(",");
    symptom = a[0];
    part = a[1];
    if(symptom == "SoftwareAging" && part == "OS"){
        OUT << "check" << part << EOL;
        return "reboot";
    }
    return "";
}
