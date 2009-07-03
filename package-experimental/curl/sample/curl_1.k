/*
 * package curl sample file
 *
 */
using curl.*;

Curl c = new Curl();
c.easySetOpt(Curl.CURLOPT_URL,"http://sourceforge.jp/projects/konoha/");
c.easyPerform();


