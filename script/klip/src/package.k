///
/// define class Package 
///
import "form.k";

/*-----Package's class-----*/
class Package extends Form
{

	/*-----constructor-----*/
	Package(String name,String version,String url)
	{
		this.name = name;
		this.version = version;
		this.url = url;
	}
	
	//*-----methods for set member variables-----*/
	boolean setMember(String file)
	{
		String filetype = file.split(".",0).pop();
		Parser pars = new Parser(this.name,file);
		pars.setMember();
		return transMembers(pars);
	}

	boolean transMembers(Parser pars)
	{
		parsver = pars.version;
		packver = this.version;
		if( packver == "" || packver == parsver) { 
		} else if ( packver < parsver) {
			String detected = %("%s{0} ver=%s{1}",this.name,parsver);
			OUT.println("KLIP : install " + detected);
		} else {
			OUT.println("!ERR : selected version is incorrect!");
			return false;
		}
		this.version = parsver;
		this.url = pars.url;
		this.depend = pars.depend;
		if ( this.url == "" ) {
			return false; 
		} else {
			return true;
		}
	}

	//*-----get package data-----*/
	boolean getPackage(){
		OUT.println("!ERR : no way to get package data [curl / stream]");
		return false; 
	}

	//*-----decompress archieves-----*/
	boolean decomPackage(){
		OUT.println("!ERR : no way to decompress package data [zlib + libtar / posix]");
		return false; 
	}

	//*-----do real operation-----*/
	int do_install()
	{
		String filename = this.url.split("/",0).pop();
		if ( !getPackage() ) {
			return EXIT_ERROR;
		}
		boolean ret = decomPackage();
		if ( !os.unlink(filename) ) {
			return EXIT_ERROR;
		}
		if ( !ret ) {
			return EXIT_ERROR;
		}
		OUT.println("KLIP : done!");
		return EXIT_SUCCESS;
	}

	int do_remove()
	{
		String path = klip_INST + "/" + this.name;
		String ptmp = rmtmp(this.name);
		if ( !os.rename(path,ptmp) ) {
			return EXIT_ERROR;
		}
		OUT.println("KLIP : done!");
		return EXIT_SUCCESS;
	}

	//*-----methods for guidance of operation-----*/
	int install()
	{
		OUT.print("KLIP : install ...  ");
		OUT.println(%("%s{0} ver=%s{1}",this.name,this.version));
		path = klip_INST + "/" + this.name;
		String getver = getCurVer(this.name);
		if ( getver != "" ) {
			OUT.println(%("KLIP : %s{0} ver=%s{1} is already installed!",this.name,getver));
			if ( this.version >= getver ) {
				return EXIT_NORMAL; 
			} else {
				OUT.println("KLIP : you can update this package");
				return EXIT_NORMAL;
			}
		} else if ( os.hasDir(path) ) {
			OUT.println("KLIP : can't touch this exsited package!");
			OUT.println("KLIP : denyed to install");
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
		OUT.println(%("%s{0} ver=%s{1}",this.name,this.version));
		String path = klip_INST + "/" + this.name;
		String getver = getCurVer(this.name);
		if ( getver == "" ) {
			OUT.println("KLIP : this package isn't installed.");
			OUT.println("KLIP : denyed to update");
			return EXIT_NORMAL;
		} else if ( getver >= this.version ) {
			OUT.println(%("KLIP : %s{0} ver=%s{1} is already installed!",this.name,getver));
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
		OUT.print("KLIP : remove  ...  ");
		OUT.println(%("%s{0} ver=??",this.name));
		String path = klip_INST + "/"+ this.name;
		String getver = getCurVer(this.name);
		if ( os.hasDir(path) ) {
			if ( getver != "" ) {
				OUT.println("KLIP : " + %("%s{0} ver=%s{1} ",this.name,getver) + " is found!");
				if( !selectYorN("remove it?") ) { 
					OUT.println("KLIP : denyed to remove");
					return EXIT_NORMAL;
				} else {
					OUT.println("KLIP : remove this package");
				}
			} else {
				OUT.println("!ERR : klip can't touch this existed package!");
				return EXIT_NORMAL;
			}
		} else {
			OUT.println("KLIP : " + this.name + " isn't found...");
			return EXIT_NORMAL;
		}
		return do_remove();
	}
}
