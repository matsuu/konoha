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
		ins = new InputStream(LATEST,"r");
		ous = new OutputStream(LATEST + "~","a");
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
		os.rename(LATEST + "~",LATEST);
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
		print("!WARN: FileController.latastMod : NOT FOUND Last-Modified");
		return ""; 
	}


	/*----------------------
	  methods for KLIPDATA
	----------------------*/

	//*-----get klip_data from server -----*/
	boolean getKlipData()
	{
		if ( latestMod(LATEST) != latestMod(KLIPURL) ) {
			os.unlink(KLIPDATA);
		} else {
			print("INFO : non need to update KLIPDATA");
			return true;
		}
		boolean write = false;
		ins = new InputStream(KLIPURL,"r");
		ous = new OutputStream(KLIPDATA,"a");
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
		os.unlink(KLIPDATA);
		updateLatest("modified"," None");
	}

	/*--------------------------------
	  methods for curdata & prevdata
	--------------------------------*/
	void mkBufCurData()	{
		copyText(CURDATA,CURDATA + "~");
	}

	void rmBufCurData() {
		os.unlink(CURDATA + "~");
	}

	void cpBufCur2Prev() {
		copyText(CURDATA + "~",PREVDATA);
	}

	void resetCurPrev() {
		resetText2Js(CURDATA);
		resetText2Js(PREVDATA);
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

	//*-----for undo-----*/
	String[] changeDiff(String opr)
	{
		String[] ret =[];
		String f0;
		String f1;
		if(opr == "u_install"){
			f0 = PREVDATA;
			f1 = CURDATA;
		} else if( opr == "u_remove" ) {
			f0 = CURDATA;
			f1 = PREVDATA;
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
