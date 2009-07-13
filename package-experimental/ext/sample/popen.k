using ext.*;
s = "svn info http://konoha-utils.googlecode.com/svn/trunk";
String[] o = os.popen(s);
foreach (String s in o) {
    OUT << s << EOL;
}
