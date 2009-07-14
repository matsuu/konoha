//
//define functions for using stream
//
/*-----getPackage by stream-----*/
boolean Package.getPackage()
{
	String pkgurl = %(this.url,sites[Int.random(|sites|)]) + "@@" - "@@";
	String filename = pkgurl.split("/",0).pop();
	ous = new OutputStream(filename,"wb");
	ins = new InputStream(pkgurl);
	int count = 0;
	int buf;
    while(true){
        buf = ins.getChar();
        if ( count >= 3 ) {
            if ( buf == -1 ){ break; }
            else {
                ous.putChar(buf);
            }
        } else if ( buf == 10 ) {
            if ( count == 2 || count == 0 ) {
                count++;
			}
        } else if ( buf == 13 && count == 1 ) {
            count++;
        } else {
            count = 0;
        }
    }
	ous.close();
	ins.close();
	if ( !os.hasFile(filename) ) { return false; }
	return true;
}