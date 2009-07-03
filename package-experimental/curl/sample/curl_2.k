/*
 * package curl sample file
 *
 */
using curl.*;

Curl c = new Curl();
OutputStream o = new OutputStream("a.png","w");
c.easySetOpt(Curl.CURLOPT_URL,"http://www.google.co.jp/images/nav_logo4.png");
c.easySetOpt(Curl.CURLOPT_FILE,o);
c.easyPerform();

o.close();

