//
//define system_check script for klip
//
//*-----system flag-----*/
String do_klip = "";
boolean root;
boolean use_curl = false;
boolean use_zl_lt = false;
boolean use_posix = false;

//*-----fatal problem switch-----*/
void klipInfo(String code) {
	do_klip += code; 
}

//*-----user check-----*/
String pkgpath = $konoha.path.package;

if ( os.hasDir(pkgpath) ) {
	pkgpath += "/klip";
}
if ( !os.mkdir(pkgpath) ){
	pkgpath = $konoha.path.user.package;
	if ( !os.hasDir(pkgpath)  ) {
		if ( !os.mkdir(pkgpath) ) {
			klipInfo("1#");
		}
	} else {
		root = false; //user
		pkgpath = $konoha.path.user.package;
	}
} else {
	root = true; //root
	pkgpath = $konoha.path.package;
}

//*-----curl-----*/
if ( os.hasDir( pkgpath + "/curl") ) {
	if ( os.hasLib("libcurl") ) {
		use_curl = true;
	} else {
		klipInfo("c");
	}
}

//*-----zlib & libtar-----*/
if ( os.hasDir( pkgpath + "/zlib") && os.hasDir( pkgpath + "/libtar") ) {
	boolean zl = os.hasLib("libz");
	boolean lt = os.hasLib("libtar");
	if ( !zl ) {
		klipInfo("z");
	}
	if ( !lt ) {
		klipInfo("t");
	}
	if ( zl && lt ) {
		use_zl_lt = true;
	}
}
if ( !use_zl_lt && os.hasDir( pkgpath + "/posix" ) ) {
	use_posix = true;
}

//*-----result-----*/
if ( !use_zl_lt && !use_posix ) {
	klipInfo("2#");
}
