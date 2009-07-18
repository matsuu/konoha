//
//define klip mainline
//
class Klip {
	
	String[] args;
	String[] ecode;

	Klip(String[] args)
	{
		this.args  = args;
		this.ecode = [];
	}

	//*-----start klip-----*/
	int start()
	{
		if ( |ecode| != 0 ) {
			info();
		}
		if ( !__fail ) {
			/*-----oparation exec-----*/
			Operater op = new Operater(args);
			if ( !op.checkOpr() ) {
				showUsage();
				return EXIT_NORMAL;
			}
			return op.exec();
		} 
		return EXIT_ERROR;
	}
	
	//*-----check package for klip-----*/
	void check()
	{
		ecode = [];

		//*-----curl-----*/
		if ( !os.hasLib("libcurl") && !__use_curl ) ecode << "curl";
		
		//*-----zlib & libtar-----*/
		if ( !os.hasLib("libz") && !__use_zlib) ecode << "zlib";

		if ( !os.hasLib("libtar") && !__use_libtar) ecode << "libtar";
		
		if ( __use_zlib && __use_libtar ) {
			__use_zllt = true;
		} else {
			__use_zllt=false;
		}

		//*-----result-----*/
		if ( !__use_zllt && !__use_posix ) {
			ecode << "e_decomp";
			__fail = true;
		}
	}

	//*-----show infomation-----*/
	void info()
	{
		String[] ret = [];
		if ( "e_user" in? ecode ) {
			ret << "!ERR : unknown_user_mode";
		}
		if ( "e_decomp" in? ecode ) {
			ret << "!ERR : need to set [zlib + libtar / posix]";
		}
		if ( "libtar" in? ecode ) {
			ret << "INFO : you need to install libtar(-devel)";
		}
		if ( "zlib" in? ecode ) {
			ret << "INFO : you need to install zlib(-devel)";
		}
		if ( "curl" in? ecode ) {
			ret << "INFO : you need to install libcurl(-devel)";
		}
		foreach( String txt from ret ) {
			OUT.println(txt);
		}
	}

	void showUsage()
	{
		OUT << """
**********************************
* klip (konoha library provider) *
*       version 0.1.5 (09/07/18) *
**********************************

usage:
  klip option [pkg]

options:

  search  pkg : search package from list

  install pkg : install package

  update  pkg : update package

  remove  pkg : remove package

  undo        : undo previous operation

""" << EOL;
	}

}
