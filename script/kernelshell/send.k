#!/usr/local/bin/konoha

void main(String[] args)
{
    if(|args| != 2){
        OUT << %("usage : %s{0} devicefile",args[0]) << EOL;
        os.exit(1);
    }

    
    InputStream  in  = new InputStream(args[1], "r");
    OutputStream out = new OutputStream("/dev/konoha", "w");
    foreach(String line in in) {
        out << line;
    }
    in.close();
    out.close();
}

