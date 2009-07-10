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
			OUT << "KLIP : install " + detected << EOL;
		} else {
			OUT << "!ERR : selected version is incorrect!" << EOL;
			return false;
		}
		this.version = parsver;
		this.url = pars.url;
		this.depend = pars.depend;
		if ( this.url == "" ) { return false; }
		return true;
	}

	//*-----decompress archieves-----*/
	boolean decomPackage(){ return false; }

	//*-----methods for operation-----*/
	int install()
	{
		OUT << "KLIP : install ...  ";
		OUT << %("%s{0} ver=%s{1}",this.name,this.version) << EOL;
		path = klip_INST + "/" + this.name;
		boolean res = false;
		Parser cur = new Parser(this.name,CURDATA);
		cur.setMember();
		String getver = cur.version;
		if( os.hasDir(path) ){
			if ( getver == "" ) {
				OUT << "!ERR : klip can't touch this existed package!" << EOL;
				return EXIT_ERROR;
			}
			else {
				OUT << %("KLIP : %s{0} ver=%s{1} is already existed!",this.name,getver) << EOL;
				res = selectYorN( "really overwrite it?" );
				if( res == false ) { OUT << "KLIP : denyed to update" << EOL; return EXIT_NORMAL; }
				else { OUT << "KLIP : update this package" << EOL;
					String ptmp = rmtmp(this.name);
					if ( !os.rename(path,ptmp) ) { return EXIT_ERROR; }
				}
			}
		}
		String filename = this.url.split("/",0).pop();
		if ( !getPackage(this.url) ) { return EXIT_ERROR; }
		boolean ret = decomPackage();
		if ( !os.unlink(filename) ) { return EXIT_ERROR; }
		if ( !ret ) { return EXIT_ERROR; }
		if ( res == true ) { modCurData(this.name,this.version,this.url,REPLACE);}
		else { modCurData(this.name,this.version,this.url,ADD); }
		return EXIT_SUCCESS;
	}

	int remove()
	{
		OUT << "KLIP : remove  ...  ";
		OUT << %("%s{0} ver=??",this.name) << EOL;
		path = klip_INST + "/"+ this.name;
		Parser cur = new Parser(this.name,CURDATA);
		cur.setMember();
		if ( os.hasDir(path) ) {
			if ( cur.version != "" ) {
				OUT << "KLIP : " + %("%s{0} ver=%s{1} ",this.name,cur.version) + " is found!" << EOL;
				String message = "really remove it?";
				res = selectYorN(message);
				if( res == false ) { 
					OUT << "KLIP : denyed to remove" << EOL;
					return EXIT_NORMAL;
				} else { OUT << "KLIP : remove this package" << EOL; }
			} else {
				OUT << "!ERR : klip can't touch this existed package!" << EOL;
				return EXIT_NORMAL;
			}
		} else {
			OUT << "KLIP : " + this.name + " isn't found..." << EOL;
			return EXIT_NORMAL;
		}
		String ptmp = rmtmp(this.name);
		if ( !os.rename(path,ptmp) ) { return EXIT_ERROR; }
		modCurData(this.name,cur.version,"",DELETE);
		return EXIT_SUCCESS;
	}

	int dinstall()
	{
		OUT << "KLIP : resolve dependency..." << EOL;
		String[] list = [%("%s{0}=%s{1}",this.name,this.version)];
		if( !resolveDepend(this,list) ) { return EXIT_ERROR; }
		int i = |list|;
		while( i > 0 ) {
			String name = list[i - 1] / "=";
			String version = list[i - 1] % "=";
			Package p = new Package(name,version,"");
			OUT << "KLIP : install [" + name + "] ver==" + version << EOL;
			if ( !p.setMember(KLIPDATA) ) { return EXIT_ERROR; }
			updateLatest("Last-Installed-Package",%("[%s{0}] ver=%{1}",p.name,p.version));
			if ( p.install() == EXIT_ERROR ) { break; }
			i--;
		}
		OUT << %("KLIP : %d{0} packages are installed",|list| - i) << EOL;
		if ( i != 0 ) {	return EXIT_ERROR; }
		return EXIT_SUCCESS;
	}

	/*-----resolve dependency & make list of install-----*/
	boolean resolveDepend (Package cur,String[] list )
	{
		foreach( String cell from cur.depend ) {
			if( !touchList(cell,list,CHECK) ) { continue; }
			Package pac = new Package(cell / "=",cell % "=","");
			if( !pac.setMember(KLIPDATA) ) { dispError("set_of_dpac",HIDE); return false; }
			touchList(pac.name + "=" + pac.version,list,ADD);
			if( !resolveDepend(pac,list) ) { return false; }
		}
		return true;
	}

}
