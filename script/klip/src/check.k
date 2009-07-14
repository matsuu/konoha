//
//define system_check script for klip
//
//*-----system flag-----*/
boolean system_fail = true;
boolean root;
boolean use_curl = false;
boolean use_zl_lt = false;
boolean use_posix = false;

//*-----system fail switch-----*/
void sys_fail(String msg)
{
	print("!ERR : fatal error : " + msg);
	system_fail = false;
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
			sys_fail("instDir");
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
	if ( true ) {//os.hasLib("libcurl") ) {
		use_curl = true;
	} else {
		OUT.println("INFO : you need to install libcurl(-devel)");
	}
}

//*-----zlib & libtar-----*/
if ( os.hasDir( pkgpath + "/zlib") && os.hasDir( pkgpath + "/libtar") ) {
	boolean zl = true;//os.hasLib("libz");
	boolean lt = true;//os.hasLib("libtar");
	if ( !zl ) {
		OUT.println("INFO : you need to install zlib(-devel)");
	}
	if ( !lt ) {
		OUT.println("INFO : you need to install libtar(-devel)");
	}
	if ( zl && lt ) {
		use_zl_lt = true;
	}
} else 

//*-----posix-----*/
if ( os.hasDir( pkgpath + "/posix" ) ) {
	use_posix = true;
}

//*-----result-----*/
if ( !use_zl_lt || !use_posix ) {
	sys_fail("library not found");
}
