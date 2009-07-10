//
//define functions for using curl
//
/*-----getPackage by curl-----*/
boolean Script.getPackage(String url)
{
	String pkgurl = %(url,sites[Int.random(|sites|)]);
	String filename = pkgurl.split("/",0).pop();
	ous = new OutputStream(filename,"wb");
	Curl c = new Curl();
	c.easySetOpt(Curl.CURLOPT_URL,pkgurl);
	c.easySetOpt(Curl.CURLOPT_FILE,ous);
	c.easyPerform();
	ous.close();
	if ( !os.hasFile(filename) ) { return false; }
	return true;
}