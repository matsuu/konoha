OUT << "class inheritance" << EOL;
OUT << "super()" << EOL;

class Test{
 Test(){
  OUT << "Test constructor" << EOL;
 }
}
class Hoge extends Test{
 Hoge(){
  OUT << "Hoge constructor" << EOL;
  super();
 }
}

Hoge h = new Hoge(); //infinite loop
