/*
 * package curl sample file
 *
 */
using curl.*;
boolean ret;
Curl c = new Curl();
OutputStream o = new OutputStream("a.png","w");
c.easySetOpt(Curl.OPT_URL,"http://www.google.co.jp/images/nav_logo4.png");
c.easySetOpt(Curl.OPT_FILE,o);
ret = c.easyPerform();
if ( ret ) {
	OUT.println("[CURLINFO]");
	OUT.println("  REQUEST_SIZE   : " + c.easyGetInfo(Curl.INFO_REQUEST_SIZE));
	OUT.println("  SIZE_DOWNLOAD  : " + c.easyGetInfo(Curl.INFO_SIZE_DOWNLOAD));
	OUT.println("  SPEED_DOWNLOAD : " + c.easyGetInfo(Curl.INFO_SPEED_DOWNLOAD));
	OUT.println("  CONTENT_TYPE   : " + c.easyGetInfo(Curl.INFO_CONTENT_TYPE));
}
o.close();

