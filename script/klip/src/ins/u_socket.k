//
//define functions for using socket
//
/*-----getPackage by socket-----*/
boolean Script.getPackage(String url)
{
	String pkgurl = %(url,sites[Int.random(|sites|)]);
	String filename = pkgurl.split("/",0).pop();
	ous = new OutputStream(filename,"wb");
	//Socket s = new Socket();
	ous.close();
	//s.close();
	if ( !os.hasFile(filename) ) { return false; }
	return true;
}