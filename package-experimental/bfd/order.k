using bfd.*;
//String file = "/home/nok/workspace/elf/funccpy"
String file = "/usr/local/lib/libkonoha-0.so.5";
String funcname = "knh_Stmt_add";
Bfd bfd =  new Bfd(file, "");
Minisyms minisyms = new Minisyms();
Size size = new Size();
boolean ret= bfd.checkformat(Bfd.BFD_OBJECT);
//assert(ret);
Asymbol store = bfd.make_empty_symbol(bfd);
int symnum = bfd.read_minisymbols(0,minisyms);
OUT<<symnum<<EOL;
Minisyms p = new Minisyms();
p.copy_pointer(minisyms);
for(int i = 0 ; i<symnum ; i++){
  Asymbol sym = bfd.minisymbol_to_symbol(0,p,store);
  String name = sym.get_name();
  int value = sym.get_value();
  OUT << %08x(value) + " " + name << EOL;
  p.next_symbol();
}
p.copy_pointer(minisyms);
int funcsize=0;
for(i = 0 ; i < symnum ; i++){
  Asymbol sym = bfd.minisymbol_to_symbol(0,p,store);
  String name = sym.get_name();
  if(name == funcname){
    int value = sym.get_value();
    int minimum = 0;
    Minisyms q = new Minisyms();
    q.copy_pointer(minisyms);
    for(int j = 0; j < symnum; j++){
      Asymbol sym2 = bfd.minisymbol_to_symbol(0,q,store);
      int value2 = sym2.get_value();
      if(value < value2){
        if( minimum > value2){
          minimum = value2;
        }else if ( minimum == 0 ){
          minimum = value2;
        }
      }
      q.next_symbol();
    }
    funcsize = minimum - value;
  }
  p.next_symbol();
}
OUT << funcname + " size of "+ funcsize << EOL;
