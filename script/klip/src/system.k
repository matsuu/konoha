//
//define system function
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
	} else if ( code == "klipd" ) {
		txt = "!ERR : failed to get klipDATA";
	} else if ( code == "klip" ) {
		txt = "!ERR : can't find this package @ klipdata";
	} else{
		txt = "!ERR : " + code + " failed";
	}
	if( level == HIDE ) { print txt; }
	else if ( level == SHOW ) { OUT << txt << EOL; }
}

/*-----Text------*/
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
	boolean check = false;
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
		String base =  %('"{"name":"%s{0}"',name );
		foreach ( String txt from ins ) {
			if ( txt.startsWith(base) ) {
				if( mode == REPLACE ) {
					ous << %(CURFORM,name,version,url) << EOL;
				} else if ( mode == DELETE ) {	}
			} else { ous << txt << EOL;	}
		}
	}
	touchText( TMPDATA, CURDATA, RENAME );
	ins.close();
	ous.close();
}


//*-----getting package from server-----*/
boolean getPackage(String url)
{
	String pkgurl = %(url,sites[Int.random(|sites|)]);
	String filename = pkgurl.split("/",0).pop();
	ous = new OutputStream(filename,"wb");
	Curl c = new Curl();
	c.easySetOpt(Curl.CURLOPT_URL,pkgurl);
	c.easySetOpt(Curl.CURLOPT_FILE,ous);
	c.easyPerform();
	ous.close();
	if ( !os.hasFile(filename) ) { return false; }
	return true;
}

/*-----class Basic Form of Package------*/
class Form
{
	String name;
	String version;
	String url;
	String[] depend;
}


