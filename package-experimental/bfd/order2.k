using bfd.*;
//String file = "/home/nok/workspace/elf/funccpy"
String file = "/usr/local/lib/libkonoha-0.so.5";
String func = "knh_Stmt_add";
Bfd bfd =  new Bfd(file, "");
boolean ret= bfd.checkformat(Bfd.BFD_OBJECT);
assert(ret);
bfd.print_all_symbols(0);
int size = bfd.get_symbol_size(0,func);
OUT << func + "   " + size + "size"<< EOL;