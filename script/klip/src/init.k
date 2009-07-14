//
//define system_init script for klip
//
/*-----abstruct class method-----*/
eval ("class Curl {void easySetOpt(); boolean easyPerform();}");
eval ("class Zlib {boolean decompGZ();}");
eval ("class Tar  {boolean extractTar();}");

//*-----for Script.getPackage() @gengeral.k-----*/
if ( use_curl ) {
	eval( "using curl.*;" );
}

//*-----for Package.decompPackage() @package.k-----*/
if ( use_zl_lt ) {
	eval("using zlib.*;");
	eval("using libtar.*;");
} else if ( use_posix ) {
	OUT << use_posix << EOL;
	eval("using posix.*;");
}
