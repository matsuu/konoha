//
//define functions for using curl
//
/*-----getPackage by curl-----*/
boolean Package.getPackage()
{
	String pkgurl = %(this.url,sites[Int.random(|sites|)]);
	String filename = pkgurl.split("/",0).pop();
	ous = new OutputStream(filename,"wb");
	Curl c = new Curl();
	c.easySetOpt(Curl.OPT_URL,pkgurl);
	c.easySetOpt(Curl.OPT_FILE,ous);
	c.easyPerform();
	ous.close();
	if ( !os.hasFile(filename) ) { return false; }
	return true;
}