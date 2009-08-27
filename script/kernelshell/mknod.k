#!/usr/local/bin/konoha
using posix.*;
void main (String[] args)
{
    if(|args| != 2){
        OUT << %("usage : %s{0} devicename",args[0]) << EOL;
        os.exit(1);
    }

    device = args[1];

    ins = new InputStream("/proc/devices","r");
    int major = 0;
    foreach(String s in ins) {
        tmp = s.split(" ",0);
        major = (int) tmp.get(0);
        name  = tmp.get(1);
        if(name == device) {
            OUT << major << EOL;
            break;
        }
    }
    in.close();

    os.system(%("rm -rf /dev/%s{0}",device));
    os.system(%("mknod /dev/%s{0} c %d{1} 0",device,major));
    os.system(%("chgrp wheel /dev/%s{0}",device));
    os.system(%("chmod 666   /dev/%s{0}",device));
}
