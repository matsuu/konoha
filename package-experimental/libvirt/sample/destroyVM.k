using libvirt.*;

Virt.init()
Connection c = new Connection("qemu:///system");

Domain d = c.getDomainByName("fedora11");
//d.shutdown();
d.destroy();
c.close();
