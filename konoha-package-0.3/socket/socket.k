# socket.k by Kimio Kuramitsu

class Socket ;
class ServerSocket;


// These methods came from Java 1.2

Socket Socket.new(String host, int port);

InputStream Socket.getInputStream();
OutputStream Socket.getOutputStream();
int Socket.getPort();
void Socket.close();
boolean Socket.isClosed();

ServerSocket ServerSocket.new(int port);
Socket ServerSocket.accept();
void ServerSocket.close();


