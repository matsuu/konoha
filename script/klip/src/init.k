//
//define system_init script for klip
//
/*-----abstruct class method-----*/
class Curl {void easySetOpt(); boolean easyPerform();}
class Zlib {boolean decompGZ();}
class Tar  {boolean extractTar();}

//*-----for Script.getPackage() @gengeral.k-----*/
if ( use_curl ) {
	eval( "using curl.*;" );
}

//*-----for Package.decompPackage() @package.k-----*/
if ( use_zl_lt ) {
	eval("using zlib.*;");
	eval("using libtar.*;");
} else if ( use_posix ) {
	eval("using posix.*;");
}
