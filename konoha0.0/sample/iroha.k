#!/usr/local/bin/konoha
String! line=IN.readLine();
int a=line.indexOf("&");
print a;
cmd=cmd[0..+a];
print cmd;

cmd=cmd.replace("%20"," ").replace("%22",'"').replace("%0A","").replace("%3D","=").replace("cmd=","");
//print line;
String ll="";

in=new InputStream("file");
foreach(String l from in){
ll+=l;
}


eval(ll);
print "Content-type:text/html;charset=utf8\n\n";
eval(cmd);

out=new OutputStream("file","a");
cmd=cmd.replace('"','\\"').replace(" ","\\ ");
out << cmd+";"<< EOL;
out.close();

