//
//define functions for using stream
//
class GetterStream extends Getter {

	/*-----getPackage by stream-----*/
	boolean getPackage()
	{
		String pkgurl = %(url,__sites[Int.random(|sites|)]) + "@@" - "@@";
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
		if ( !os.hasFile(filename) ) {
			print("!ERR : GetterStream.getPackage : stream");
			return false;
		}
		return true;
	}

}
