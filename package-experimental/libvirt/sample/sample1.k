using libvirt.*;

Virt.init()
Connection c = new Connection("qemu:///system");
c.close();
