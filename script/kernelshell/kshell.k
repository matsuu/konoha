#!/usr/local/bin/konoha

void main(String[] args)
{

    InputStream in;
    OutputStream out;
    String str;
    while (1) {
        in = new InputStream("/dev/konoha", "r");
        out = new OutputStream("/dev/konoha", "w");
        OUT << ">>";
        str = IN.readLine();
        out << str;
        s = in.readLine();
        OUT <<  s << EOL;
        in.close();
        out.close();
    }
    in.close();
    out.close();
}

