class Virt;
class Connection;
class Domain;

void Virt.init()
Connection! Connection.new(String name);
void Connection.close();
String Connection.getType();
String Connection.getHostname();
String Connection.getURI();
Int Connection.getFreeMemory();
Domain Connection.getDomainByName(String name);

Connection Domain.getConnection();
String Domain.getName();
Int Domain.getID();
String Domain.getOSType();
Boolean Domain.create();
Boolean Domain.reboot();
Boolean Domain.shutdown();
Boolean Domain.destroy();
