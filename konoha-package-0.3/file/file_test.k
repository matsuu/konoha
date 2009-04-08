using file.*;
File f = new File("hoge.txt","w");
for(i=0;i<100;i++){
    f.putc(3);
}
f.close();

