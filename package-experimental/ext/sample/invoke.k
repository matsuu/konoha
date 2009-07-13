using ext.*;
using posix.*;

String System.invokeEditor(String data){
    String tmpname = System.tmpfile();
    OutputStream os = new OutputStream(tmpname,"w");
    os.print(data);
    os.close();
    editor = $env.EDITOR;
    if(editor == null){
        editor = "vi";
    }
    int ret = System.system(editor+" "+tmpname);
    if(ret != 0){
        OUT << "err";
    }

    InputStream is = new InputStream(tmpname,"r");
    String val = "";
    foreach(String s from is){
        val += s;
    }
    System.unlink(tmpname);
    return val;
}

int main(String[] args){
    s = System.invokeEditor("");
    OUT << s << EOL;
    return 0;
}
