///
/// define class Package 
///
/*-----Package's class-----*/
class Package
{
	/*-----package-----*/
	String name;
	String version;
	String url;
	String[] depend;

	/*-----constructor-----*/
	Package(String name,String version,String url)
	{
		this.name = name;
		this.version = version;
		this.url = url;
	}

	//*-----methods for set member variables-----*/
	void setMember(String file)
	{
		Parser pars = getParser(file);
		parsver = pars.version;
		if( version == "" || version == parsver ) { 
		} else if ( version < parsver) {
			String detected = %("%s{0} ver=%s{1}",name,parsver);
			OUT.println("KLIP : install " + detected);
		} else {
			print("!WARN: detected lower version only");
		}
		this.version = parsver;
		this.url = pars.url;
		this.depend = pars.depend;
	}

	//*-----get version from CURDATA-----*/
	String getCurVer()
	{
		Parser pars = getParser(CURDATA);
		return pars.version;
	}

	//*-----check before install [installed or not]-----*/
	boolean selectYorN(String message)
	{
		boolean ret;
		OUT.print(%("!ASK : %s{0} [y/n] : ",message));
		while( true ){
			input = IN.readLine();
			if ( input == "y" ) {
				ret = true;
				break;
			} else if ( input == "n" ) {
				ret = false;
				break;
			} else {
				OUT.print("!ASK : please input [y/n] : "); 
			}
		}
		return ret;
	}

	/*-----remove dir to tmp-----*/
	String rmtmp(String name)
	{
		String tmpdir = "/tmp/" + name;
		while ( os.hasDir(tmpdir) ) {
			tmpdir = "/tmp/" + (String)Int.random(1024) + "." + name;
		}
		return tmpdir;
	}


	/*
	  operations
	 */
	
	//*-----do real operation-----*/
	int do_install()
	{
		String filename = this.url.split("/",0).pop();
		if ( !getPackage() ) {
			print("!ERR : Package.do_install : getPackage");
			return EXIT_ERROR;
		}
		boolean ret = decompPackage();
		os.unlink(filename);
		if ( !ret ) {
			print("!ERR : Package.do_install : decompPackage");
			return EXIT_ERROR;
		}
		OUT.println("KLIP : done!");
		return EXIT_SUCCESS;
	}

	int do_remove()
	{
		String ptmp = rmtmp(name);
		if ( !os.rename(__path + "/" + name,ptmp) ) {
			print("!ERR : Package.do_remove : rename");
			return EXIT_ERROR;
		}
		OUT.println("KLIP : done!");
		return EXIT_SUCCESS;
	}

	//*-----methods of operations-----*/
	int install()
	{
		OUT.print("KLIP : install ...  ");
		OUT.println(%("%s{0} ver=%s{1}",name,version));
		String getver = getCurVer();
		if ( getver != "" ) {
			OUT.println(%("KLIP : %s{0} ver=%s{1} is already installed!",name,getver));
			if ( version >= getver ) {
				return EXIT_NORMAL; 
			} else {
				OUT.println("KLIP : you can update this package");
				return EXIT_NORMAL;
			}
		} else if ( os.hasDir( __path + "/" + name) ) {
			OUT.println("KLIP : can't touch this exsited package!");
			return EXIT_NORMAL;
		}
		if( !selectYorN("install it?") ) { 
			OUT.println("KLIP : denyed to install");
			return EXIT_NORMAL;
		} else {
			OUT.println("KLIP : install this package");
		}
		return do_install();
	}
		
	int update()
	{
		OUT.print("KLIP : update  ...  ");
		OUT.println(%("%s{0} ver=%s{1}",name,version));
		String getver = getCurVer();
		if ( getver == "" ) {
			if ( os.hasDir( __path + "/" + name ) ) {
				OUT.println("KLIP : can't touch this exsited package!");
			} else {
				OUT.println("KLIP : this package isn't installed.");
			}
			return EXIT_NORMAL;
		} else if ( getver >= version ) {
			OUT.println(%("KLIP : %s{0} ver=%s{1} is already installed!",name,getver));
			OUT.println("KLIP : no need to update");
			return EXIT_NORMAL;
		}
		if( !selectYorN("update it?") ) { 
			OUT.println("KLIP : denyed to update");
			return EXIT_NORMAL;
		} else {
			OUT.println("KLIP : update this package");
		} 
		if ( do_remove() == EXIT_ERROR ) {
			return EXIT_ERROR;
		}
		return do_install();
	}

	int remove()
	{
		OUT.println("KLIP : remove  ...  " + name);
		String getver = getCurVer();
		if ( os.hasDir( __path + "/" + name) ) {
			if ( getver != "" ) {
				OUT.println("KLIP : " + %("%s{0} ver=%s{1} ",name,getver) + " is found!");
				if( !selectYorN("remove it?") ) {
					OUT.println("KLIP : denyed to remove");
					return EXIT_NORMAL;
				} else {
					OUT.println("KLIP : remove this package");
				}
			} else {
				OUT.println("!ERR : can't touch this existed package!");
				return EXIT_NORMAL;
			}
		} else {
			OUT.println("KLIP : " + name + " isn't found...");
			return EXIT_NORMAL;
		}
		return do_remove();
	}


	/*
	  methods of depend with system flag
	 */

	Parser getParser(String file)
	{
		String type = file.split(".",0).pop();
		Parser pars;
		if ( type == "json" ) {
			pars = (Parser) new ParserJson(name,file);
			//		} else if ( type == "xml" ) {
			//			if ( use_libxml ) {
			//				pars = (Parser) new ParserXml(name,file);
			//			} else {
			//				OUT.println("!ERR : Package.setMember : cannot using libxml2 ");
			//				return false;
			//			}
		} else {
			print ("!ERR : Package.setMember : filetype == " + type );
		}
		pars.setMember();
		return pars;
	}

	//*-----get package-----*/
	boolean getPackage()
	{
		Getter g;
		if ( __use_curl ) {
			g = (Getter) new GetterCurl(url);
		} else {
			g = (Getter) new GetterStream(url);
		}
		return g.getPackage();
	}
	
	//*-----decompress archieves-----*/
	boolean decompPackage()
	{
		Decomp d;
		if ( __use_zllt ) {
			d = (Decomp) new DecompZllT(name,version);
		} else if ( __use_posix ) {
			d = (Decomp) new DecompSystem(name,version);
		} else {
			print("!ERR : Package.decompPackage : no way to decompPackage");
			return false;
		}
		return d.decompPackage();
	}
}

