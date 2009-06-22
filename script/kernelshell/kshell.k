#!/usr/local/bin/konoha

using posix.*;

int main(String[] args)
{

    InputStream in;
    OutputStream out;
    String str;
    while (1) {
	in = new InputStream("/dev/konoha", "r");
	out = new OutputStream("/dev/konoha", "w");
	OUT << ">>";
	str = IN.readLine()
	out << str;
	s = in.readLine();	
	System.sleep(1);
	OUT <<  s << EOL;
	in.close();
	out.close();
    }
    in.close();
    out.close();
}