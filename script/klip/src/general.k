//
//define general function
//
/*-----for ERROR message-----*/
void dispError(String code,int level)
{
	String txt = "";
	if (code == "usage"){
		txt = "USAGE: ./klip [operation] [package_name]\n";
		txt += "USAGE: operation = [ search , install , remove , undo ]";
	} else if (code == "operation"){
		txt = "!ERR : undefined such operation\n";
		txt += "USAGE: operation = [ search , install , remove , undo ]";
	} else if ( code == "arg_ver" ){
		txt = "!ERR : please set Float value @ args.version ";
	} else {
		txt = "!ERR : " + code + " failed";
	}
	if( level == HIDE ) { print txt; }
	else if ( level == SHOW ) { OUT << txt << EOL; }
}

/*-----exit process-----*/
int errorExit(String opr)
{
	String[] touched = ["install","dinstall","remove"]
	dispError(opr,SHOW);
	if ( opr in? touched) { touchText( BUFDATA, CURDATA, RENAME); }
	return EXIT_ERROR;
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

/*-----touch install list-----*/
boolean touchList(String pack,String[] list,int mode)
{
	String name = pack / "=";
	String version = pack % "=";
	foreach ( String pic from list ) {
		if( name == (pic / "=") ) {
			if ( version <= (pic % "=") ) { dispError("depend_ver",HIDE); return false; }
			else if ( mode == ADD ) { pic = pack; return true; }
		}
	}
	if( mode == ADD ) { list << pack; }
	return true;
}

/*-----touch general text------*/
void touchText(String fromfile,String tofile,int mode)
{
	if ( mode != 0 ) {
		if( os.hasFile(tofile) ) { os.unlink(tofile); }
		ins = new InputStream(fromfile,"r");
		ous = new OutputStream(tofile,"a");
		foreach( String txt from ins ) { ous << txt << EOL; }
		ins.close();
		ous.close();
		if ( mode == RENAME ) { os.unlink(fromfile); }
	}
}

/*-----update latest install------*/
void updateLatest(String section, String diff)
{
	boolean flag = false;
	ins = new InputStream(LATEST,"r");
	ous = new OutputStream(LATEST + "~","a");
	foreach( String txt from ins ) {
		if ( txt.startsWith(section) ) { flag = true; ous << section + diff << EOL; }
		else { ous << txt << EOL; }
	}
	if ( !flag ) { ous << section + diff << EOL; }
	ous.close();
	ins.close();	
	touchText(LATEST + "~",LATEST,RENAME);
}

/*-----check Modified section of latest.klip-----*/
boolean checkLatest(String seciton, String input)
{
	boolean flag = false;
	g_ins = new InputStream(input,"r");
	foreach ( String gettxt from g_ins ) {
		if ( gettxt.startsWith(seciton) ) { break; }
	}
	g_ins.close();
	ins = new InputStream(LATEST,"r");
	foreach( String txt from ins ) {
		if ( txt.startsWith(seciton) ) { 
			if ( txt == gettxt ) { return true; }	
			flag = true;
		}
	}
	ins.close();
	if ( !flag ) { return false; }
	updateLatest(seciton,gettxt % seciton); 
	return true; 
}

/*-----get klip_data from server -----*/
boolean getKlipData(String filename)
{
	if ( checkLatest("Last-Modified:",%(KLIPURL,filename.split("/",0).pop() ) ) ) {
		if ( os.hasFile(filename) ) { os.unlink(filename); }
	} else { return true; }
	boolean write = false;
	ins = new InputStream(%(KLIPURL,filename.split("/",0).pop() ),"r");
	ous = new OutputStream(filename,"a");
	foreach ( String txt from ins ) {
		if ( write == false && txt == "" ) { write = true; }
		else if ( write == true ) { ous << txt << EOL; }
	}
	ins.close();
	ous.close();
	if ( !os.hasFile(filename) ) { return false; }
	return true;
}

//*-----check before install [installed or not]-----*/
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

//*-----modification of current [use TMPDATA]-----*/
void modCurData(String name,String version,String url,int mode)
{
	String endw = "}";  //for json
	InputStream ins = new InputStream(CURDATA,"r");
	OutputStream ous = new OutputStream(TMPDATA,"a");
	if (mode == ADD ){
		String base = %(CURFORM,name,version,url);
		foreach( String txt from ins ) {
			if (txt == endw) { break; }
			String txtname = txt % '"name":' / '"';
			if ( txtname > name && base != "" ) {
				ous << base << EOL;
				base = "";
			}
			ous << txt << EOL;
		}
		if ( base != "" ) { ous << base << EOL; }
		ous << endw << EOL;
	} else if (mode == DELETE || mode == REPLACE) {
		String base =  %('"name":"%s{0}"',name );
		foreach ( String txt from ins ) {
			if ( base in? txt ) {
				if( mode == REPLACE ) {
					ous << %(CURFORM,name,version,url) << EOL;
				}
			} else { ous << txt << EOL;	}
		}
	}
	touchText( TMPDATA, CURDATA, RENAME );
	ins.close();
	ous.close();
}

//*-----getting package from server-----*/
boolean getPackage(String url){ }
