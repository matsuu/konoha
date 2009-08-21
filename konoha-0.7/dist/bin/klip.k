#!/usr/local/bin/konoha


/*----------------------------------------------------------*/

///
/// define const data
///
/*-----system info message-----*/
usage="""
*************************************
*  klip ( Konoha LIbrary Provider ) *
*          version 0.1.5 (09/07/18) *
*************************************

usage:
  klip option [pkg]

options:

  list        : list of package on server

  installed   : list of packages already installed

  search  pkg : search package from list on server

  install pkg : install package

  update  pkg : update package

  remove  pkg : remove package

  undo        : undo previous operation
""";

/*-----system const integer-----*/
EXIT_SUCCESS = 1;
EXIT_NORMAL  = 0;
EXIT_ERROR   = -1;

ADD = 1;
REPLACE = 2;
DELETE = 3;

/*-----already installed list & format to write -----*/
klipdir = $env.home + "/.konoha/klip/";
curdata = klipdir + "current.json";
CURFORM = '{"name":"%s{0}","version":"%s{1}","url":"%s{2}"},';

/*-----other files(for undo)-----*/
prevdata = klipdir + "previous.json";
latest = klipdir + "latest.log";

/*-----server's klip_data url(klip.xml or etc)-----*/
KLIPFILE = "klip.json";
KLIPURL = "http://konoha.sourceforge.jp/klip/" + KLIPFILE;
//KLIPURL = "http://localhost/klip/" +  KLIPFILE;

/*-----sourceforge's mirror server-----*/
sites = ["keihanna" ,"jaist" ,"globalbase", "osdn", "iij"];

/*-----KLIPDATA-----*/
klipdata = klipdir + KLIPFILE;

/*-----system flag-----*/
boolean root;
boolean fail = false;
boolean use_curl = false;
boolean use_zlib = false;
boolean use_libtar = false;
boolean use_posix = false;
boolean use_zllt = false;

/*----------------------------------------------------------*/

//
//getting system environment
//

if ( !os.hasDir(klipdir) ) {
	os.mkdir(klipdir);
}

/*
  user check
*/
String path = $konoha.path.package;
if ( !os.hasDir( path ) ) {
	root = os.mkdir( path );
} else {
	String home = $env.HOME;
	if ( "/home/" in? home ) {
		root = false;
	} else {
		root = true;
	}
}
if ( !root ) { 
	path = $konoha.path.user.package;
	if ( !os.hasDir( path ) ) {
		os.mkdir( path );
	}
}
path += "/";

/*
  library check
*/
//*-----curl-----*/
String libcurl = path + "curl";
class Curl {
	@abstract boolean easyPerform();
	@abstract void easySetOpt(int type, Any? data);
}
if ( os.hasDir( libcurl ) ) {
	if ( os.hasLib("libcurl") ) {
		eval ( "using curl.*;");
		use_curl = true;
	}
}
		
//*-----zlib-----*/
String libzlib = path + "zlib";
class Zlib {
	@abstract boolean decompGZ(String gzfile);
}
if ( os.hasDir( libzlib ) ) {
	if ( os.hasLib("libz") ) {
		eval ( "using zlib.*;" );
		use_zlib = true;
	}
}

//*-----libtar-----*/
String liblibtar = path + "libtar";
class Tar {
	@abstract boolean extractTar(String tarfile);
}
if ( os.hasDir( liblibtar ) ) {
	if ( os.hasLib("libtar") ) {
		eval ( "using libtar.*;" );
		use_libtar = true;
	}
}
		
//*-----posix-----*/
String libposix = path + "posix";
String shared = $konoha.platform + ".so";
if ( os.hasDir( libposix ) ) {
	if ( os.hasLib( libposix + "/posix_" + shared ) ) {
		eval ( "using posix.*;" );
		use_posix = true;
	}
}

/*----------------------------------------------------------*/

//
//define glue class for decompress
//
class Decomp {

	String name;
	String version;

	Decomp(String name,String version){
		this.name = name;
		this.version = version;
	}

	@virtual boolean decompPackage();

}

/*----------------------------------------------------------*/

//
//define functions for using posix
//
/*-----decompPackage by posix-----*/
class DecompSystem extends Decomp {

	/*-----Decomp.decompPackage-----*/
	boolean decompPackage(){
		String filename = %("%s{0}-%s{1}.tar.gz",name,version);
		int ret;
		ret = System.system("tar -xzf " + filename);
		if ( ret != 0 || !os.hasDir(name) ) {
			print("!ERR : DecompSystem.decompPackage : System.system");
			return false;
		}
		os.rename(name,__path + name);
		return true;
	}
}

/*----------------------------------------------------------*/

//
//define functions for using zlib & libtar
//
/*-----decompPackage by using zlib & libtar-----*/
class DecompZllT extends Decomp {

	/*-----Decomp.decompPackage-----*/
	boolean decompPackage(){
		String filename = %("%s{0}-%s{1}.tar.gz",name,version);
		if ( !Zlib.decompGZ(filename) ) {
			print("!ERR : DecompZllT.decompPackage : Zlib.decompGZ");
			return false;
		}
		String tarfile = filename - ".gz";
		boolean res = Tar.extractTar(tarfile);
		os.unlink(tarfile);
		if ( !res || !os.hasDir(name) ) {
			print("!ERR : DecompZllT.decompPackage : Tar.extractTar == " + res );
			return false;
		}
		os.rename(name,__path + name);
		return true;
	}
	
}

/*----------------------------------------------------------*/

//
//define glue class for get package
//
class Getter {

	String url;

	/*-----constructor-----*/
	Getter(String url){
		this.url = url;
	}

	/*-----get package data-----*/
	@virtual boolean getPackage();

}

/*----------------------------------------------------------*/

//
//define functions for using curl
//
class GetterCurl extends Getter
{

	/*-----getPackage by curl-----*/
	boolean getPackage()
	{
		String pkgurl = %(url,__sites[Int.random(|sites|)]) + "@@" - "@@";
		String filename = pkgurl.split("/",0).pop();
		ous = new OutputStream(filename,"wb");
		Curl c = new Curl();
		c.easySetOpt(10002,pkgurl);  //Curl.OPT_URL
		c.easySetOpt(10001,ous);     //Curl.OPT_FILE
		c.easyPerform();
		ous.close();
		if ( !os.hasFile(filename) ) {
			print("!ERR : GetterCurl.getPackage : Curl.easyPerform");
			return false;
		}
		return true;
	}
	
}

/*----------------------------------------------------------*/

//
//define functions for using stream
//
class GetterStream extends Getter {

	/*-----getPackage by stream-----*/
	boolean getPackage()
	{
		String pkgurl = %(url,__sites[Int.random(|sites|)]) + "@@" - "@@";
		String filename = pkgurl.split("/",0).pop();
		ous = new OutputStream(filename,"wb");
		ins = new InputStream(pkgurl);
		int count = 0;
		int buf;
		while(true){
			buf = ins.getChar();
			if ( count >= 3 ) {
				if ( buf == -1 ){ break; }
				else {
					ous.putChar(buf);
				}
			} else if ( buf == 10 ) {
				if ( count == 2 || count == 0 ) {
					count++;
				}
			} else if ( buf == 13 && count == 1 ) {
				count++;
			} else {
				count = 0;
			}
		}
		ous.close();
		ins.close();
		if ( !os.hasFile(filename) ) {
			print("!ERR : GetterStream.getPackage : stream");
			return false;
		}
		return true;
	}

}

/*----------------------------------------------------------*/

//
//registing parsers
//
/*-----class Parser Form-----*/
class Parser
{
	String name;
	String version;
	String url;
	String[] depend;
	String file;

	/*-----constructor-----*/
	Parser(String name, String file)
	{
		this.name = name;
		this.depend = [];
		this.file = file;
 	}

	/*-----Data2Package-----*/
	@virtual void setMember();

	/*-----generate formed txt-----*/
	@virtual String generate();

	/*-----generate package name list-----*/
	@virtual String[] nameList();

}

/*----------------------------------------------------------*/

//
// parsing data to json
//
/*-----class Parser for Json-----*/
class ParserJson extends Parser
{

	/*-----Override Parser.setMember-----*/
	void setMember()
	{
		this.version = getElement("version");
		this.url = getElement("url");
		this.depend = getElement("depend").split("&",0);
	}

	/*-----Override Parser.generate-----*/
	String generate()
	{
		String ret;
		if ( this.url == "" ) { return ret; }
		ret += "{\n";
		ret += setNode("name",this.name) + ",\n";
		ret += setNode("version",this.version) + ",\n";
		ret += setNode("url",this.url);
		if ( this.depend[0] != "" ) { ret += ",\n" + arrayNode("depend",this.depend); }
		return ret + "\n}\n";
	}

	/*-----for setMemberJson-----*/ 
	String getElement(String elemname)
	{
		String ret;
		String raw = rawjs();
		String check = %('"name":"%s{0}"',this.name);
		while( true ) {
			if ( raw == "" ) { break; }
			else if ( check in? ( raw / "," ) ) {
				ret = parseThisTree(raw,elemname); 
				break;
			}
			raw = succRaw(raw);
		}
		return ret;
	}

	String parseThisTree(String raw,String elemname)
	{
		String ret;
		String key = %('"%s{0}":',elemname);
		while(true) {
			if ( raw == "" ) { break; }
			String pic = raw / ",";
			if ( key in? pic ) { 
				if ( elemname != "depend" ) {
					ret = pic.split('":"',0).pop();
					ret = ret.split('"',0)[0];
					return ret;
				}
				else { return getDependencies(raw); }
			} else if ( "}" in? pic && !("{0}" in? pic) ) { break; }			
			raw = succRaw(raw);
		}
		return ret;
	}

	String getDependencies(String raw)
	{
		String ret;
		String base = ( raw - "]" ) % '"depend":["';
		while( base != "") {
			ret += base.split('"',0)[0] + "&";
 			base %= '","';
		}
		return ret;
	}

	String[] nameList()
	{
		String[] ret = [];
		String[] box;
		String raw = rawjs();
		String check = '"name":"';
		box = raw.split(check,0);
		foreach(String txt from box) {
			ret << txt / '"';
		}
		ret.remove(0);
		return ret;
	}

	String rawjs()
	{
		String ret;
		ins = new InputStream(this.file,"r");
		foreach( String txt from ins ) {
			ret += txt;
		}
		ins.close();
		return ret - "\t";
	}

	String succRaw (String raw)	{ return raw % ","; }

	/*-----for generateJson-----*/
	String setNode(String name,String data)
	{
		return %('"%s{0}":"%s{1}"',name,data );
	}

	String arrayNode(String name,String[] data)
	{
		String ret;
		ret += %('"%s{0}":[',name);
		foreach ( String cell from data) {
			ret += %('"%s{0}",',cell);
		}
		return ret[..|ret|-2] + "]";
	}

}

/*----------------------------------------------------------*/

//
//define general function
//
class FileHandler {

	/*------------------------
	  methods for latest.log
	------------------------*/

	//*-----update latest install------*/
	void updateLatest(String section, String diff)
	{
		if ( section == "install" ) {
			str = "Last-Installed-Package:";
		} else if ( section == "modified" ) {
			str = "Last-Modified:";
		}
		boolean flag = false;
		ins = new InputStream(__latest,"r");
		ous = new OutputStream(__latest + "~","a");
		foreach( String txt from ins ) {
			if ( txt.startsWith(str) ) {
				flag = true;
				txt = str + diff;
			}
			ous.println(txt);
		}
		if ( !flag ) {
			ous.println(str + diff);
		}
		ous.close();
		ins.close();
		os.rename(__latest + "~",__latest);
	}
	
	//*-----check Modified section of latest.klip-----*/
	String latestMod(String file)
	{
		ins = new InputStream(file,"r");
		foreach( String txt from ins ) {
			if ( "Last-Modified:" in? txt ) {
				ins.close();
				return txt; 
			}
		}
		ins.close();
		print("!WARN: FileHandler.latastMod : NOT FOUND Last-Modified");
		return ""; 
	}


	/*----------------------
	  methods for KLIPDATA
	----------------------*/

	//*-----get klip_data from server -----*/
	boolean getKlipData()
	{
		if ( latestMod(__latest) != latestMod(KLIPURL) ) {
			os.unlink(__klipdata);
		} else {
			print("INFO : non need to update KLIPDATA");
			return true;
		}
		boolean write = false;
		ins = new InputStream(KLIPURL,"r");
		ous = new OutputStream(__klipdata,"a");
		foreach ( String txt from ins ) {
			if ( "{" == txt || write ) {
				write = true;
				ous.println(txt);
				if ( txt == "}" ) { break;}
			} else if ( "Last-Modified:" in? txt ) {
				updateLatest("modified",
							 txt.split("Last-Modified:",0).pop());
            }
		}
		ins.close();
		ous.close();
		return true;
	}

	//*-----remove klipdata-----*/
	void rmKlipData()
	{
		os.unlink(__klipdata);
		updateLatest("modified"," None");
	}

	/*--------------------------------
	  methods for curdata & prevdata
	--------------------------------*/
	void mkBufCurData()	{
		copyText(__curdata,__curdata + "~");
	}

	void rmBufCurData() {
		os.unlink(__curdata + "~");
	}

	void cpBufCur2Prev() {
		copyText(__curdata + "~",__prevdata);
	}

	void resetCurPrev() {
		resetText2Js(__curdata);
		resetText2Js(__prevdata);
	}

	void resetLatest() {
		os.unlink(__latest);
		ous = new OutputStream(__latest,"a");
		ous.close();
		updateLatest("install"," None");
		updateLatest("modified"," None");
	}

	//*-----modification of current [use TMPDATA]-----*/
	void modCurData(String[] data,int mode)
	{
		InputStream ins = new InputStream(__curdata,"r");
		OutputStream ous = new OutputStream(__curdata + "#","a");
		if (mode == ADD ){
			String base = %(CURFORM,data[0],data[1],data[2]);
			foreach( String txt from ins ) {
				if (txt == "}") {
					break;
				}
				String txtname = txt % '"name":' / '"';
				if ( txtname > data[0] && base != "" ) {
					ous.println(base);
					base = "";
				}
				ous.println(txt);
			}
			if ( base != "" ) {
				ous.println(base);
			}
			ous.println("}");
		} else if (mode == DELETE || mode == REPLACE) {
			String base =  %('"name":"%s{0}"',data[0] );
			foreach ( String txt from ins ) {
				if ( base in? txt ) {
					if( mode == REPLACE ) {
						txt = %(CURFORM,data[0],data[1],data[2]);
						ous.println(txt);
					}
				} else {
					ous.println(txt);
				}
			}
		}
		ins.close();
		ous.close();
		os.rename(__curdata + "#",__curdata);
	}

	//*-----for undo-----*/
	String[] changeDiff(String opr)
	{
		String[] ret =[];
		String f0;
		String f1;
		if(opr == "u_install"){
			f0 = __prevdata;
			f1 = __curdata;
		} else if( opr == "u_remove" ) {
			f0 = __curdata;
			f1 = __prevdata;
		}
		ins0 = new InputStream(f0,"r"); 
		boolean chk;
		foreach( String txt from ins0 ) {
			chk = true;
			ins1 = new InputStream(f1,"r");	
			foreach( String txt2 from ins1 ) {
				if( txt == txt2 ) {
					chk = false;
				} 
			}
			ins1.close();
			if (chk == true) ret << txt;
		}
		ins0.close();
		return ret;
	}


	/*--------------------------------------
	  methods for other method in this class
	--------------------------------------*/

	//*-----reset txt to empty-----*/
	void resetText2Js(String filename)
	{
		os.unlink(filename);
		ous = new OutputStream(filename,"w");
		String[] form = ["{","}"];
		foreach( String txt from form) {
			ous.println(txt);
		}
		ous.close();
	}
	
	//*-----copy txt file-----*/
	void copyText(String infile ,String outfile)
	{
		os.unlink(outfile);
		ins = new InputStream(infile,"r");
		ous = new OutputStream(outfile,"w");
		foreach(String txt from ins) {
			ous.println(txt);
		}
		ous.close();
		ins.close();
	}
	
}

/*----------------------------------------------------------*/

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
		Parser pars = getParser(__curdata);
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
		String[] files;
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
	String[] getList(String filename)
	{
		p = getParser(filename);
		return p.nameList();
	}

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

/*----------------------------------------------------------*/

//
//define controller of operations
//
class Operater {

	String opr;
	Package pkg;
	FileHandler fh;
	
	Operater(String[] args)
	{
		int ret;
		String name = "";
		if ( |args| >= 2 && |args| <= 3 ) {
			this.opr = args[1];
			if ( |args| == 3 ) {
				name = args[2];
			}
		}
		this.pkg = new Package(name,"","");
		this.fh = new FileHandler();
	}

	/*-----opr in? operations-----*/
	boolean checkOpr()
	{
		String[] ops = ["search",
						"install",
						"update",
						"remove",
						"undo",
						"list",
						"installed",
						"clean"];
		return ( opr in? ops );
	}

	/*-----init-----*/
	void init()
	{
		if ( !os.hasFile(__latest) ) {
			fh.resetLatest();
		}
		if ( !os.hasFile(__curdata) ) {
			fh.resetCurPrev();
		}
	}

	/*-----do operation-----*/
	int exec()
	{
		int ret;
		boolean flag;
		String filename;
		String[] need_search = ["search",
								"install",
								"update"];
		String[] need_list = ["list",
							  "installed"];
		if ( opr == "undo" ) {
			ret = undoMain(); 
		} else if ( opr == "clean" ) {
			ret = cleanMain(); 
		} else if ( opr == "remove" ) {
			ret = removeMain();
		} else if ( opr in? need_list ) {
			if ( opr == "list" ) {
				filename = __klipdata;
			} else if ( opr == "installed" ) {
				filename = __curdata;
			}
			listKlip(filename);
			ret = EXIT_SUCCESS;
		} else if ( opr in? need_search ){
			flag = searchKlip();
			if ( opr == "search" ) {
				ret = EXIT_SUCCESS;
			} else if (flag) {
				if( opr == "install" ) {
					if ( |pkg.depend| > 1 ) {
						ret = dinstallMain();
					} else {
						ret = installMain();
					}
				} else if ( opr == "update" ) {
					ret = updateMain();
				}
			}
		}
		if ( ret == EXIT_ERROR ) {
			OUT.println("!ERR : " + opr + " faild");
		}
		return ret;
	}

	/*-----update KLIPDATA & search pkg from it-----*/
	boolean searchKlip()
	{
		fh.getklipdata();
		String ret;
		pkg.setMember(__klipdata);
		if ( |pkg.url| == 0 ) {
			OUT.println("KLIP : package is NOT FOUND...");
			return false;
		} else {
			OUT.println(%("PACK : %s{0}\tver=%s{1} is FOUND", pkg.name, pkg.version));
			return true;
		}
	}

	/*-----update KLIPDATA & list pkg from it-----*/
	void listKlip(String filename)
	{
		OUT.println("KLIP : show package list...");
		String[] names = [];
		String[] ret = [];
		String form = "PACK : %s{0}\tver=%s{1}";
		fh.getklipdata();
		names = pkg.getList(filename);
		foreach (String nm from names) {
			pac = new Package(nm,"","");
			pac.setMember(filename);
			if ( pac.version == "" ) continue;
			OUT.println(%(form,pac.name,pac.version));
		}
		OUT.println("KLIP : theere are [" + |names| + "] packages");
	}
	
	/*-----main of install-----*/
	int installMain()
	{
		int ret;
		fh.mkBufCurData();
		fh.updateLatest("install", pkg.name + "=" + pkg.version );
		ret = pkg.install();
		if ( ret == EXIT_SUCCESS ) {
			fh.modCurData([pkg.name,pkg.version,pkg.url],ADD);
			fh.cpBufCur2Prev();
		}
		fh.rmBufCurData();
		return ret;
	}
	
	/*-----main of update-----*/
	int updateMain()
	{
		int ret;
		fh.mkBufCurData();
		fh.updateLatest("install", pkg.name + "=" + pkg.version);
		ret = pkg.update();
		if ( ret == EXIT_SUCCESS ) {
			fh.modCurData([pkg.name,pkg.version,pkg.url],REPLACE);
			fh.cpBufCur2Prev();
		}
		fh.rmBufCurData();
		return ret;
	}
	
	/*-----main of remove-----*/
	int removeMain()
	{
		int ret;
		fh.mkBufCurData();
		ret = pkg.remove();
		if ( ret == EXIT_SUCCESS ) {
			fh.modCurData([pkg.name,pkg.version,pkg.url],DELETE);
			fh.cpBufCur2Prev();
		}
		fh.rmBufCurData();
		return ret;
	}
	
	/*-----main of clean-----*/
	int cleanMain()
	{
		fh.rmKlipData();
		fh.resetCurPrev();
		fh.updateLatest("install"," None");
		return EXIT_SUCCESS;
	}


	/*-------------------------------------------------
	  define methods of dinstall (not only 1 package)
	-------------------------------------------------*/

	/*-----main of install with depenency(dinstall)------*/
	int dinstallMain()
	{
		int ret;
		fh.mkBufCurData();
		ret = dinstall();
		if ( ret == 0 ) {
			print("!ERR : OperationController.dinstallMain : dinstall");
			fh.rmBufCurData();
			return EXIT_ERROR;
		}
		fh.cpBufCur2Prev();
		fh.rmBufCurData();
		OUT.println(%("KLIP : %d{0} packages are installed",ret));
		return EXIT_SUCCESS;
	}

	/*-----dinstall------*/
	int dinstall()
	{
		String[] list = [pkg.name + "=" + pkg.version];
		resolveDepend(pkg,list);
		int num = |list|;
		int ret = 0;
		while( num > 0 ) {
			Package pac = new Package(
									list[num - 1].split("=",0)[0],
									list[num - 1].split("=",0).pop(),
									"");
			pac.setMember(__klipdata);
			if ( |pac.url| == 0 ) {
				OUT.println(%("!ERR : %s{0} ver=%s{1} is NOT FOUND",
							  pac.name,
							  pac.version));
				num--;
				continue;
			}
			fh.updateLatest("install", pac.name + "=" + pac.version);
			if ( pac.install() == EXIT_ERROR ) {
				print("!ERR : OperationController.dinstall : install " + pac.name + "=" + pac.version);
				num--;
				continue;
			}
			fh.modCurData([pac.name,pac.version,pac.url],ADD);
			ret++;
			num--;
		}
		return ret;
	}

	/*-----resolve dependency & make list for dinstall-----*/
	void resolveDepend (Package cur,String[] list)
	{
		print("KLIP : resolve dependency...");
		foreach( String ce from cur.depend ) {
			if( !searchList(ce,list,0) ) continue;
			Package pac = new Package(ce.split("=",0)[0],
									  ce.split("=",0).pop(),
									  "");
			pac.setMember(__klipdata);
			if( |pac.url| == 0 ) {
				print("!ERR : OperationController.resolveDepend : setMember :" + pac.name);
				continue;
			}
			searchList(pac.name + "=" + pac.version,list,1);
			resolveDepend(pac,list);
		}
	}
	
	/*-----search install list-----*/
	boolean searchList(String pack,String[] list,int mode)
	{
		foreach ( String ce from list ) {
			if( pack.split("=",0)[0] == ce.split("=",0)[0] ) {
				if ( pack.split("=",0).pop() <= ce.split("=",0).pop() ) {
					return false;
				} else if ( mode == 1 ) {
					list[list.indexOf(ce)] = pack;
					return true;
				}
			}
		}
		if( mode == 1 ) {
			list << pack;
		}
		return true;
	}


	/*------------------------
	  define methods of undo
	------------------------*/

	/*-----undo main-----*/
	int undoMain()
	{
		String[] u_fail = [];
		fh.mkBufCurData();
		if ( undo("u_remove") != EXIT_SUCCESS ) { u_fail << "u_rm"; }
		if ( undo("u_install") != EXIT_SUCCESS ) { u_fail << "u_in"; }
		if ( |u_fail| != 0 ) {
			fh.rmBufCurData();
			if ( "u_in" in? u_fail ) {
				OUT.println("!ERR : undo :install failed");
			}
			if ( "u_rm" in? u_fail ) {
				OUT.println("!ERR : undo :remove failed");
			}
			return EXIT_NORMAL;
		}
		fh.cpBufCur2Prev();
		fh.rmBufCurData();
		return EXIT_SUCCESS;
	}

	/*-----undo(install/remove)-----*/
	int undo(String u_opr)
	{
		int ret;
		String[] list = fh.changeDiff(u_opr);
		if ( |list| == 0 ) {
			return EXIT_SUCCESS;
		}
		foreach( String ce from list ) {
			Package pac = new Package( 
									   filter(ce,"name"),
									   filter(ce,"version"),
									   filter(ce,"url"));
			if( u_opr == "u_install") {
				ret = pac.install();
				if ( ret == EXIT_SUCCESS ) {
					fh.modCurData([pac.name,pac.version,pac.url],ADD);
				}
			} else if ( u_opr == "u_remove" ) {
				ret = pac.remove();
				if ( ret == EXIT_SUCCESS ) {
					fh.modCurData([pac.name,pac.version,pac.url],DELETE);
				}
			}
		}
		return ret;
	}

	/*-----filter for undo-----*/
	String filter(String cell,String member)
	{
		String bef = %('"%s{0}":"',member);
		String aft = '"';
		String ret = cell.split(bef,0).pop();
		return ret.split(aft,0)[0];
	}

}

/*----------------------------------------------------------*/

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
		if ( !__fail ) {
			/*-----oparation exec-----*/
			Operater op = new Operater(args);
			op.init();
			if ( op.checkOpr() ) {
				return op.exec();
			}
			showUsage();
		} 
		info();
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
			__use_zllt = false;
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
			ret << '     : please set "property variable HOME" correctry';
		}
		if ( "e_decomp" in? ecode ) {
			ret << '!ERR : cannot both "using [zlib+libtar/posix]"';
			ret << "     : please install either of them by another way";
		}
		if ( "libtar" in? ecode ) {
			ret << "INFO : you should install libtar(-devel)";
		}
		if ( "zlib" in? ecode ) {
			ret << "INFO : you should install zlib(-devel)";
		}
		if ( "curl" in? ecode ) {
			ret << "INFO : you should install libcurl(-devel)";
		}
		if ( |ecode| != 0 ) {
			foreach( String txt from ret ) {
				OUT.println(txt);
			}
		}
	}

	void showUsage() {
		OUT << __usage << EOL;
	}

}


//
//Script.main
//
int main (String[] args)
{
	Klip klip = new Klip(args);
	klip.check();
	return klip.start();
}


