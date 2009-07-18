//
//getting system environment
//

/*
  user check
*/

path = $konoha.path.package + "/";
if ( !os.hasDir( path ) ) {
	root = os.mkdir( path );
} else {
	int i = 0;
	while ( !os.hasDir( path + "./klip" * i ) ) { i++; }
	root = os.mkdir( path + "klip" * i );
	os.rename( path + "klip","/tmp/klip");
}
if ( !root ) { 
	path = $konoha.path.user.package + "/";
	if ( !os.hasDir( path ) ) {
		os.mkdir( path );
	}
}


/*
  library check
 */

//*-----curl-----*/
class Curl {
	@abstract boolean easyPerform();
	@abstract void easySetOpt(int type, Any? data);
}
if ( os.hasDir( path + "curl") ) {
	if ( os.hasLib("libcurl") ) {
		eval ( "using curl.*;");
		use_curl = true;
	}
}
		
//*-----zlib-----*/
class Zlib {
	@abstract boolean decompGZ(String gzfile);
}
if ( os.hasDir( path + "zlib") ) {
	if ( os.hasLib("libz") ) {
		eval ( "using zlib.*;" );
		use_zlib = true;
	}
}

//*-----libtar-----*/
class Tar {
	@abstract boolean extractTar(String tarfile)
}
if ( os.hasDir( path + "libtar") ) {
	if ( os.hasLib("libtar") ) {
		eval ( "using libtar.*;" );
		use_libtar = true;
	}
}
		
//*-----posix-----*/
if ( os.hasDir( path + "posix" ) ) {
	eval ( "using posix.*;" );
	use_posix = true;
}

