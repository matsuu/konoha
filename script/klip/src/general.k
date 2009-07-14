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
	if( level == 0 ) {
		print txt;
	} else if ( level == 1 ) {
		OUT.println(txt);
	}
}

/*-----exit process-----*/
int errorExit(String opr)
{
	dispError(opr,1);
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

/*-----copy txt file-----*/
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

/*-----reset txt to empty-----*/
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

/*-----touch install list-----*/
boolean touchList(String pack,String[] list,int mode)
{
	String name = pack / "=";
	String version = pack % "=";
	foreach ( String pic from list ) {
		if( name == (pic / "=") ) {
			if ( version <= (pic % "=") ) {
				dispError("depend_ver",0);
				return false; 
			} else if ( mode == 1 ) {
				pic = pack;
				return true;
			}
		}
	}
	if( mode == 1 ) {
		list << pack;
	}
	return true;
}

/*-----update latest install------*/
void updateLatest(String section, String diff)
{
	boolean flag = false;
	ins = new InputStream(LATEST,"r");
	ous = new OutputStream(LATEST + "~","a");
	foreach( String txt from ins ) {
		if ( txt.startsWith(section) ) {
			flag = true;
			txt = section + diff;
		}
		ous.println(txt);
	}
	if ( !flag ) {
		ous.println(section + diff);
	}
	ous.close();
	ins.close();
	os.rename(LATEST + "~",LATEST);
}

/*-----check Modified section of latest.klip-----*/
boolean checkLatest(String seciton, String input)
{
	boolean flag = false;
	g_ins = new InputStream(input,"r");
	foreach ( String gettxt from g_ins ) {
		if ( gettxt.startsWith(seciton) ) {
			break; 
		}
	}
	g_ins.close();
	ins = new InputStream(LATEST,"r");
	foreach( String txt from ins ) {
		if ( txt.startsWith(seciton) ) { 
			if ( txt == gettxt ) {
				return true; 
			}	
			flag = true;
		}
	}
	ins.close();
	if ( !flag ) {
		return false; 
	}
	updateLatest(seciton,gettxt % seciton); 
	return true; 
}

/*-----get klip_data from server -----*/
boolean getKlipData(String filename)
{
	if ( checkLatest("Last-Modified:",%(KLIPURL,filename.split("/",0).pop() ) ) ) {
		if ( os.hasFile(filename) ) {
			os.unlink(filename); 
		}
	} else {
		return true;
	}
	boolean write = false;
	ins = new InputStream(%(KLIPURL,filename.split("/",0).pop() ),"r");
	ous = new OutputStream(filename,"a");
	foreach ( String txt from ins ) {
		if ( "{" == txt || write ) {
			write = true;
			ous.println(txt);
			if ( txt == "}" ) { break;}
		}
	}
	ins.close();
	ous.close();
	if ( !os.hasFile(filename) ) {
		return false;
	} else {
		return true;
	}
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

//*-----modification of current [use TMPDATA]-----*/
void modCurData(String[] data,int mode)
{
	InputStream ins = new InputStream(CURDATA,"r");
	OutputStream ous = new OutputStream(CURDATA + "#","a");
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
	os.rename(CURDATA + "#",CURDATA);
}

void endofOpration(int code,String opr,String[] data)
{
	int mode;
	if ( code == EXIT_SUCCESS ) {
		if ( "install" in? opr ) {
			mode = ADD;
		} else if ( opr == "update" ) {
			mode = REPLACE;
		} else if ( "remove" in? opr ) {
			mode = DELETE;
		}
        modCurData(data,mode);
		if ( !("_" in? opr) ) {
			copyText(CURDATA + "~",PREVDATA);
		}
	}
}
