//
//define extra operation ( dinstall & undo )
//
/*-----resolve dependency & make list of install-----*/
boolean resolveDepend (Package cur,String[] list )
{
	foreach( String cell from cur.depend ) {
		if( !touchList(cell,list,0) ) {
			continue;
		}
		String name = cell.split("=",0)[0];
		String version = cell.split("=",0).pop();
		Package pac = new Package(name,version,"");
		if( !pac.setMember(KLIPDATA) ) {
			return false; 
		}
		touchList(pac.name + "=" + pac.version,list,1);
		if( !resolveDepend(pac,list) ) {
			return false;
		}
	}
	return true;
}

//*-----install with dependency-----*/
int dinstall(Package pack)
{
	OUT.println("KLIP : resolve dependency...");
	String[] list = [%("%s{0}=%s{1}",pack.name,pack.version)];
	if( !resolveDepend(pack,list) ) {
		return EXIT_ERROR;
	}
	int i = |list|;
	while( i > 0 ) {
		String name = list[i - 1].split("=",0)[0];
		if ( pack.name == "all" && i == 1 ) {
			break;
		}
		String version = list[i - 1].split("=",0).pop();
		Package p = new Package(name,version,"");
		if ( !p.setMember(KLIPDATA) ) {
			OUT.println("!ERR : this depend package isn't found in KLIPDATA");
			OUT.println(%("!ERR : %s{0} ver=%s{1}",name,version));
			i--;
			continue;
		}
		int ret = p.install();
		updateLatest("Last-Installed-Package",%("[%s{0}] ver=%{1}",p.name,p.version));
		if ( ret == EXIT_ERROR ) {
			break;
		}
		String[] data = [p.name,p.version,p.url];
		endofOpration(ret,"d_install",data);
		i--;
	}
	OUT.println(%("KLIP : %d{0} packages are installed",|list| - i));
	if ( pack.name == "all" ) {
		i--;
	}
	if ( i != 0 ) {
		OUT.println("!ERR : failed to install some depended packages");
		if ( !selectYorN("undo operation?") ) {
			OUT.println("KLIP : denyed to undo");
			return EXIT_ERROR;
		}
		OUT.println("KLIP : undo!");
		copyText(PREVDATA,PREVDATA + "~");
		copyText(CURDATA + "~",PREVDATA);
		boolean res = do_undo();
		copyText(PREVDATA + "~",PREVDATA);
		os.unlink(PREVDATA + "~");
		if ( !res ) {
			copyText(CURDATA + "~",PREVDATA);
			return EXIT_ERROR;
		}
	}
	return EXIT_SUCCESS;
}

/*-----for undo-----*/
String[] searchChanged(String opr)
{
	String[] ret =[];
	if(opr == "u_install"){
		ins = new InputStream(PREVDATA,"r"); 
	} else if( opr == "u_remove" ) {
		ins = new InputStream(CURDATA,"r"); 
	}
	boolean chk;
	foreach( String txt from ins ) {
		chk = true;
		if(opr == "u_install"){
			inr = new InputStream(CURDATA,"r"); 
		} else if( opr == "u_remove" ) {
			inr = new InputStream(PREVDATA,"r");	
		}
		foreach( String txt2 from inr ) {
			if( txt == txt2 ) {
				chk = false;
			} 
		}
		inr.close();
		if (chk == true) {
			ret << txt; 
		}
	}
	ins.close();
	return ret;
}

String filter(String cell,String member)
{
	String bef = %('"%s{0}":"',member);
	String aft = '"';
	String ret = cell.split(bef,0).pop();
	return ret.split(aft,0)[0];
}

boolean undo(String opr,String[] list)
{
	boolean res = true;
	int ret;
	foreach( String cell from list ) {
		String name = filter(cell,"name");
		String version = filter(cell,"version");
		String url = filter(cell,"url");
		Package pick = new Package( name,version,url );
		if( opr == "u_install") {
			ret = pick.install();
		} else if ( opr == "u_remove" ) {
			ret = pick.remove();
		}
		String[] data = [pick.name,pick.version,pick.url];
		endofOpration(ret,opr,data);
		if ( ret == EXIT_ERROR ) {
			res == false;
		}
	}
	return res;
}

boolean do_undo()
{
	boolean ret;
	boolean flag = true;
	String[] u_opr = ["u_remove","u_install"];
	foreach ( String opr from u_opr ) {
		String[] list = searchChanged(opr);
		if ( |list| == 0 ) {
			ret = true;
		} else {
			ret = undo(opr,list);
		}
		if (!ret) {
			flag = false;
		}
	}
	return flag;
}
