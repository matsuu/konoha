#!/usr/local/bin/konoha

CGIURL = "http://konoha.sourceforge.jp/cgi-bin/knhgetpkg.cgi"

String getPackageURL(String pkgname) {
  url = "%s{0}?package=%s{1}&type=%s{2}" %% (CGIURL, pkgname, $konoha.platform)
  //print url;
  in = new InputStream(url);
  foreach(String line from in) {
    print line;
    if(line.startsWith("Location: ")) {
	s = line.split();
        return s[1];
    }
  }
  //return "NONE";
  return url;
}

void main(String[] args) {
    print |args|;
    if(|args| < 1) {
	OUT << "USAGE: konohaget.k package_name" << EOL;
    }
    url = getPackageURL(args[1]);
    print url;
}
