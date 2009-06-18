///
/// define class Package 
///
using posix.*;
using libxml2.*;



/*-----Package's class-----*/
class Package
{
	String name;
	String version;
	String url;
	String[] depend;
	
	/*---constructor---*/
	Package(String name,String version,String url)
	{
		this.name = name;
		this.version = version;
		this.url = url;
	}

	
	/*-----for klip_c.k ERROR message-----*/
	void dispErrorClass(String code)
	{
		String txt = "";
		if (code == "break"){
			txt = "BREAK:";
		} else if (code == "not existed"){
			txt = "!ERR : can't find this package @ INSTDIR";
		} else if (code == "version"){
			txt = "!ERR : can't find this package of such version";
		} else{
			txt = "!ERR : " + code + " failed";
		}
		OUT << txt << EOL;
	}	
	

	/*---methods for set member variables---*/
	String setMember(String xmlfile)
	{
		xmlversion = getElementFromXml(this.name,"version",xmlfile);
		if(this.version != "" && this.version != xmlversion) {
			if( (Float)this.version < (Float)xmlversion ){
				String detected = %("%s{0} ver=%s{1}",this.name,xmlversion);
				OUT << "!WARN: upper version is found : " + detected << EOL;
				//need to select [y/n]?
			} else {
				dispErrorClass("version");
				return "";
			}
		} 
		this.version = xmlversion;
		this.url = getElementFromXml(this.name,"url",xmlfile);
		depend_str = getElementFromXml(this.name,"depend",xmlfile);
		this.depend = depend_str.split("&",0);
		return this.url;
	}


	String getElementFromXml(String pkgname, String elemname, String xmlfile)
	{ 
		XmlReader reader = new XmlReader (xmlfile);
		String ans = "";
		while (reader.read()) {
			type = reader.nodeType();
			if (type == XmlReader.TYPE_ELEMENT && reader.constName() == 'name') {
				reader.read();
				if (type == XmlReader.TYPE_ELEMENT && reader.constValue() == pkgname) {
					ret = parseThisTree(reader, elemname);
					reader.close();
					return ret;
				}
			}
		}
		reader.close();
		return ans;
	}
	

	String parseThisTree(XmlReader reader, String elemname)
	{
		String ans = "";
		while (reader.read()) {
			type = reader.nodeType();
			if (type == XmlReader.TYPE_ELEMENT) {
				curelem = reader.constName();
				if ( curelem == elemname ){
					if ( elemname == "depend" ) {
						return getDependencies(reader);
					} else if (reader.read() && type == XmlReader.TYPE_ELEMENT) {
						return reader.constValue();
					}
				}
			}
		}
		return ans;
	}
	
	String getDependencies(XmlReader reader)
	{
		String ans = "";
		while (reader.read()) {
			type = reader.nodeType();
			if (type == XmlReader.TYPE_ELEMENT) {
				curelem = reader.constName();
				if (curelem == 'dname') {
					if (reader.read() && type == XmlReader.TYPE_ELEMENT) {
						ans += reader.constValue() + '=';
					}
				} else if (curelem == 'dversion') {
					if (reader.read() && type == XmlReader.TYPE_ELEMENT) {
						ans += reader.constValue() + '&';
					}
				} else if (curelem == 'depend') {
					return ans;
				}
			}
		}
		return ans;
	}
	
	
	/*---methods for operation---*/
	boolean install()
	{
		String filename = %("%s{0}-%s{1}.tar.gz",this.name,this.version);
		path = INSTDIR + this.name;
		boolean res = false;
		OUT << "SEEK : " + path << EOL;
		if( System.hasDir(path) ){
			String message = %("%s{0} is found! overwrite it?",this.name );
			res = selectYorN(message);
			if( res == false ) { 
				OUT << "KLIP : denyed to update" << EOL;
				return false;
			} else {
				OUT << "KLIP : update this package" << EOL;
			}
		} else { OUT << "KLIP : install this package" << EOL; }
		String mirror = sites[Int.random(|sites|)];
		String pkgurl = %(this.url,mirror);
		OUT << "GET  : " + pkgurl << EOL;
		System.system("wget -q -N " + pkgurl);
		OUT << "DECOM: " + filename + " @ " + INSTDIR << EOL;
		System.system(%("tar -xzf %s{0} -C %s{1}",filename,INSTDIR));
		OUT << "REMOV: " + filename << EOL;
		System.unlink(filename);
		if(System.hasDir(path) == false) { dispErrorClass("decomp"); return false; }
		if ( res == true ) { modCurXml(this.name,this.version,this.url,"r");
		} else if ( res == false ) { modCurXml(this.name,this.version,this.url,"a"); }
		return true;
	}


	boolean remove()
	{
		path = INSTDIR + this.name;
		OUT << "SEEK : " + path << EOL;
		if ( System.hasDir(path) ) {
			String message = "target package is detected! remove it?";
			res = selectYorN(message);
			if( res == false ) { 
				OUT << "KLIP : denyed to remove" << EOL;
				return false;
			} else { OUT << "KLIP : remove this package" << EOL; }
		} else {
			dispErrorClass("not existed");
			return false;
		}
		OUT << "REMOV: " + path << EOL;
		System.system("rm -rf " + path);
		if( System.hasDir(path) ) { dispErrorClass("remove"); return false; }
		modCurXml(this.name,"","","d");
		return true;
	}


	/*---check before install [installed or not]---*/
	boolean selectYorN(String message)
	{
		OUT << %("!ASK : %s{0} [y/n] : ",message);
		while(true){
			input = IN.readLine();
			if ( input == "y" ) { return true; }
			else if ( input == "n" ) { return false; }
			else { OUT << "!ASK : please input [y/n] : " ; }
		}
	} 


	/*---modification of current.xml [use TMPXML]---*/
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
