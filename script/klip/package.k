///
/// define class Package 
///
using posix.*;

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
	

	/*-----methods for set member variables-----*/
	boolean setMember(String file)
	{
		String check = file;
		String filetype;
		while ( check != "" ) { filetype = check; check %= "." }
		if( filetype == "xml" ) { return xml2Package(file); }
		else if ( filetype == "json" ) { return json2Package(file); }
		return false;
	}


	boolean json2Package(String jsonfile)
	{
		ParserJson p = new ParserJson(this.name,jsonfile);
		jsonversion = p.getVersion();
		if( this.version == "" || this.version == jsonversion) { 
		} else if ( this.version < jsonversion) {
			String detected = %("%s{0} ver=%s{1}",this.name,jsonversion);
			print "!WARN: upper version is found!";
			OUT << "KLIP : install " + detected << EOL;
		} else {
			OUT << "!ERR : selected version is incorrect!" << EOL;
			return false;
		}
		this.version = jsonversion;
		this.url = p.getUrl();
		this.depend = p.getDepend();
		if ( this.url == "" ) { return false; }
		return true;
	}


	boolean xml2Package(String xmlfile)
	{
		ParserXml p = new ParserXml(this.name,xmlfile);
		xmlversion = p.getVersion();
		if( this.version == "" || this.version == xmlversion) { 
		} else if ( this.version < xmlversion) {
			String detected = %("%s{0} ver=%s{1}",this.name,xmlversion);
			print "!WARN: upper version is found!";
			OUT << "KLIP : install " + detected << EOL;
		} else {
			OUT << "!ERR : selected version is incorrect!" << EOL;
			return false;
		}
		this.version = xmlversion;
		this.url = p.getUrl();
		this.depend = p.getDepend();
		if ( this.url == "" ) { return false; }
		return true;
	}


	/*-----getting package from server-----*/
	boolean getPackage()
	{
		String mirror = sites[Int.random(|sites|)];
		String baseurl = this.url;
		String pkgurl = %(this.url,mirror);
		String filename;
		while ( baseurl != "" ) { filename = baseurl; baseurl %= "/"; }
		System.system("wget -q -N " + pkgurl);
		//another way
		if ( !System.hasFile(filename) ) { return false; }
		return true;
	}

	
	/*-----methods for operation-----*/
	boolean install()
	{
		path = instDIR + this.name;
		boolean res = false;
		String pkgurl = this.url;
		ParserXml cur = new ParserXml(this.name,CURXML);
		String getver = cur.getVersion();
		if( getver != "" && System.hasDir(path) ){
			String message = this.name + " ver=" + getver + " is found! overwrite it?";
			res = selectYorN(message);
			if( res == false ) { 
				OUT << "KLIP : denyed to update" << EOL;
				return false;
			} else {
				OUT << "KLIP : update this package" << EOL;
			}
		} else { OUT << "KLIP : install this package" << EOL; }
		String filename;
		while ( pkgurl != "" ) { filename = pkgurl; pkgurl %= "/"; }
		if ( !getPackage() ) { return false; }
		if ( System.system("tar -xzf " + filename + " -C " + instDIR) != 0 ) { return false; }
		if ( System.unlink(filename) != 0 ) { return false; }
		if ( res == true ) { modCurXml(this.name,this.version,this.url,"r");
		} else if ( res == false ) { modCurXml(this.name,this.version,this.url,"a"); }
		return true;
	}


	boolean remove()
	{
		path = instDIR + this.name;
		ParserXml cur = new ParserXml(this.name,CURXML);
		if ( cur.getVersion() != "" && System.hasDir(path) ) {
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
		if ( System.system("rm -rf " + path) != 0 ) { return false; }
		modCurXml(this.name,"","","d");
		return true;
	}


	/*-----check before install [installed or not]-----*/
	boolean selectYorN(String message)
	{
		boolean ret;
		OUT << %("!ASK : %s{0} [y/n] : ",message);
		while( true ){
			input = IN.readLine();
			if ( input == "y" ) { ret = true; break; }
			else if ( input == "n" ) { ret = false; break; }
			else { OUT << "!ASK : please input [y/n] : " ; }
		}
		return ret;
	} 


	/*-----modification of current.xml [use TMPXML]-----*/
	void modCurXml(String name,String version,String url,String mode)
	{
		InputStream ins = new InputStream(CURXML,"r");
		OutputStream ous = new OutputStream(TMPXML,"a");
		if (mode == "a" ){
			String base = %(CURFORM,name,version,url);
			foreach( String txt from ins ) {
				if (txt == "</packages>") { break; }
				String txtname = txt % "<name>" / "</name>";
				if ( txtname > name && base != "" ) {
					ous << base << EOL;
					base = "";
				}
				ous << txt << EOL;
			}
			if ( base != "" ) { ous << base << EOL; }
			ous << "</packages>" << EOL;
		} else if (mode == "d" || mode == "r") {
			String base =  %("<package><name>%s{0}</name>",name );
			foreach ( String txt from ins ) {
				if ( txt.startsWith(base) ) {
					if( mode == "r" ) {
						ous << %(CURFORM,name,version,url) << EOL;
					} else if ( mode == "d" ) {	}
				} else { ous << txt << EOL;	}
			}
		}
		System.rename( TMPXML, CURXML );
		ins.close();
		ous.close();
	}

}
