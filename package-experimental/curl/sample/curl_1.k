/*
 * package curl sample file
 *
 */
using curl.*;

Curl c = new Curl();
c.easySetOpt(Curl.OPT_URL,"http://sourceforge.jp/projects/konoha/");
c.easyPerform();


