///
/// define class Package 
///
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


	//*-----methods for operation-----*/
	boolean install()
	{
		path = instDIR + this.name;
		boolean res = false;
		Parser cur = new Parser(this.name,CURDATA);
		String getver = cur.version;
		if( os.hasDir(path) ){
			if ( getver == "" ) { OUT << "!ERR : klip can't touch this existed package!" << EOL; }
			else {
				res = selectYorN( this.name + " ver=" + getver + " is found! overwrite it?" );
				if( res == false ) { OUT << "KLIP : denyed to update" << EOL; return false; }
				else { OUT << "KLIP : update this package" << EOL; }
			}
		} else { OUT << "KLIP : install this package" << EOL; }
		String filename = this.url.split("/",0).pop();
		if ( !getPackage(this.url) ) { return false; }
        if ( System.system("tar -xzf " + filename + " -C " + instDIR) != 0 ) { return false; }
		if ( !os.unlink(filename) ) { return false; }
		if ( res == true ) { modCurData(this.name,this.version,this.url,REPLACE);}
		else { modCurData(this.name,this.version,this.url,ADD); }
		return true;
	}

	boolean remove()
	{
		path = instDIR + "/"+ this.name;
		Parser cur = new Parser(this.name,CURDATA);
		if ( cur.version != "" && os.hasDir(path) ) {
			String message = "target package is detected! remove it?";
			res = selectYorN(message);
			if( res == false ) { 
				OUT << "KLIP : denyed to remove" << EOL;
				return false;
			} else { OUT << "KLIP : remove this package" << EOL; }
		} else {
			OUT << "!ERR : " + this.name + " isn't existed" << EOL;
			return false;
		}
		String ptmp = "/tmp/" + this.name;
		while ( os.hasDir(ptmp) ) {
			ptmp = "/tmp/" + (String)Int.random(1024) + "." + this.name;
		}
		if ( !os.rename(path,ptmp) ) { return false; }
		modCurData(this.name,"","",DELETE);
		return true;
	}
 
}
