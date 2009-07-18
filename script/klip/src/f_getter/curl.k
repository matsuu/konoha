//
//define functions for using curl
//
class GetterCurl extends Getter
{

	/*-----getPackage by curl-----*/
	boolean getPackage()
	{
		String pkgurl = %(url,__sites[Int.random(|sites|)]) + "@@" - "@@";
		String filename = pkgurl.split("/",0).pop();
		ous = new OutputStream(filename,"wb");
		Curl c = new Curl();
		c.easySetOpt(10002,pkgurl);  //Curl.OPT_URL
		c.easySetOpt(10001,ous);     //Curl.OPT_FILE
		c.easyPerform();
		ous.close();
		if ( !os.hasFile(filename) ) {
			print("!ERR : GetterCurl.getPackage : Curl.easyPerform");
			return false;
		}
		return true;
	}
	
}