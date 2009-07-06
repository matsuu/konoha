//
//define functions in main
//
/*-----functions for dependency-----*/
boolean searchList(String dpackage,String[] list,int mode)
{
	String name = dpackage / "=";
	String version = dpackage % "=";
	foreach ( String pic from list ) {
		String listname = pic / "=";
		String listver = pic % "=";
		if( listname == name ) {
			if ( listver >= version ) { dispError("depend_ver",HIDE); return false; }
			else if ( mode == ADD ) { pic = dpackage; return true; }
		}
	}
	if( mode == ADD ) { list << dpackage; }
	return true;
}

/*-----resolve dependency & make list of install-----*/
boolean resolveDepend ( Package target, String[] list )
{
	foreach( String cell from target.depend ) {
		if( !searchList(cell,list,CHECK) ) { continue; }
		String dname = cell / "=";
		String dver = cell % "=";
		Package pac = new Package(dname,dver,"");
		OUT << "KLIP : depend package : " + dname + "ver=" + dver << EOL;
		if( !pac.setMember(KLIPDATA)) { dispError("dpac->klip",HIDE); return false; }
		String instpac = %("%s{0}=%s{1}",pac.name,pac.version);
		searchList(instpac,list,ADD);
		if( !resolveDepend(pac,list) ) { return false; }
	}
	return true;
}

/*-----get list & install from list-----*/
boolean installwithDepend ( Package target )
{
	OUT << "KLIP : resolve dependency..." << EOL;
	String[] instList = [%("%s{0}=%s{1}",target.name,target.version)];
	if( !resolveDepend(target,instList) ) { return false; }
	int i = |instList|;
	while( i > 0 ) {
		String name = instList[i - 1] / "=";
		String version = instList[i - 1] % "=";
		Package p = new Package(name,version,"");
		OUT << "KLIP : install [" + name + "] ver==" + version << EOL;
		if ( !p.setMember(KLIPDATA) ) { break; }
		updateLatest("Last-Installed-Package",%("[%s{0}] ver=%{1}",p.name,p.version));
		if ( !p.install() ) { break; }
		i--;
	}
	OUT << %("KLIP : %d{0} packages are installed",|instList| - i) << EOL;
	if ( i != 0 ) {	dispError("instDepend",HIDE); return false;	}
	return true;
}

/*-----for undo-----*/
String[] searchChanged(String opr )
{
	String[] ret =[];
	if(opr == "undo_inst"){ ins = new InputStream(CURDATA,"r"); }
	else if( opr == "undo_rmv" ) { ins = new InputStream(PREVDATA,"r"); }
	foreach( String txt from ins ) {
		boolean chk = true;
		if(opr == "undo_inst"){ inr = new InputStream(PREVDATA,"r"); }
		else if( opr == "undo_rmv" ) { inr = new InputStream(CURDATA,"r");	}
		foreach( String txt2 from inr ) { if( txt == txt2 ) { chk = false;} }
		inr.close();
		if (chk == true) { ret << txt; }
	}
	ins.close();
	return ret;
}

String filter(String cell,String member)
{
	String bef = %('"%s{0}":"',member);
	String aft = '"';
	return cell % bef / aft;
}

boolean inUndo(String opr)
{
	String[] list = searchChanged(opr);
	boolean ret = true;
	foreach( String cell from list ) {
		String name = filter(cell,"name");
		String version = filter(cell,"version");
		String url = filter(cell,"url");
		Package pick = new Package( name,version,url );
		if( opr == "undo_inst") { ret = pick.remove(); }
		else if ( opr == "undo_rmv" ) { ret =  pick.install(); }
		if ( ret == false ) { break; }
	}
	return ret;
}


/*-----operation in main-----*/
int undoInMain()
{
	boolean ret = true;
	touchText(CURDATA,BUFDATA,COPY);
	if ( !inUndo("undo_inst") ) { dispError("undo_inst",HIDE); ret =  false; }
	if ( !inUndo("undo_rmv") ) { dispError("undo_rmv",HIDE); ret = false; }
	if ( ret == false ) { dispError("undo",SHOW); return EXIT_ERROR; }
	touchText(PREVDATA,CURDATA,COPY);
	return EXIT_SUCCESS;
}

int searchInMain(Package target)
{
	if ( !getKlipData(KLIPDATA) ) { dispError("klipd",SHOW); return EXIT_ERROR; }
	if ( !target.setMember(KLIPDATA) ) {
		OUT << "KLIP : package is NOT FOUND..." << EOL;
		return EXIT_SUCCESS;
	}
	OUT << "KLIP : package is FOUND!" << EOL;
	OUT << %("KLIP : %s{0} ver=%s{1}",target.name,target.version) << EOL;
	return EXIT_SUCCESS;
}

int installInMain(Package target)
{
	if ( !getKlipData(KLIPDATA) ) { dispError("klipd",SHOW); return EXIT_ERROR; }
	if ( !target.setMember(KLIPDATA) ) { dispError("klip",SHOW); return EXIT_ERROR; }
	touchText(CURDATA,BUFDATA,COPY);
	updateLatest("Last-Installed-Package:",%("[%s{0}] ver=%{1}",target.name,target.version));
	if( target.depend[0] != "" ) {
		OUT << "KLIP : this package has dependency" << EOL;
		if( !installwithDepend(target) ) {
			dispError("dinstall",SHOW);
			touchText( BUFDATA, CURDATA, RENAME);
			return EXIT_ERROR;
		}
	} else {
		OUT << "KLIP : package has no dependency" << EOL;
		if( !target.install() ) {
			dispError("install",SHOW); 
			touchText( BUFDATA, CURDATA, RENAME );
			return EXIT_ERROR;
		}
	}
	return EXIT_SUCCESS;
}

int removeInMain(Package target)
{
	touchText(CURDATA,BUFDATA,COPY);
	if( !target.remove() ) {
		dispError("remove",SHOW);
		touchText( BUFDATA, CURDATA, RENAME );
		return EXIT_ERROR; 
	}
	return EXIT_SUCCESS;
}


int cleanInMain()
{
	boolean ret;
	if ( os.hasFile(KLIPDATA) ) { ret = os.unlink(KLIPDATA); }
	else { ret = true; }
	touchText(EMPTY,CURDATA,COPY);
	touchText(EMPTY,PREVDATA,COPY);
	updateLatest("Last-Modified:"," None");
	updateLatest("Last-Installed-Package:"," None");
    int t = 0;
    if(ret == true) t = 0;
    else t = -1;
	return t;
}

int switchOperation(Package target, String operation)
{
	int ret;
	if ( operation == "search" ) {
		ret = searchInMain(target);
	} else if(operation == "install"){ 
		ret = installInMain(target);
	} else if (operation == "remove"){
		ret = removeInMain(target);
	} else if (operation == "undo") {
		ret = undoInMain();
	} else if (operation == "clean"){ 
		ret = cleanInMain();
	} else { dispError("operation",SHOW); return EXIT_ERROR; }
	return ret;
}

int klipOperation(String[] args)
{
	if( |args| == 2 ) { return switchOperation(new Package("","",""),args[1]); }
	String operation = args[1];
	String name = args[2];
	if ( |args| == 4 ) {
		String version = args[3];
		if ( (Float)version == 0.0) { dispError("arg_ver",SHOW); return EXIT_ERROR; }
	} else { version = ""; }
	Package target = new Package(name,version,"");
	ret = switchOperation(target,operation);
	return ret;
}

int endOfKlip(int ret)
{
	if ( ret != EXIT_SUCCESS ) {
		OUT << "KLIP : some error occured!" << EOL;
		return EXIT_ERROR; 
	}
	touchText( BUFDATA, PREVDATA, RENAME );
	OUT << "KLIP : success all" << EOL;
	return EXIT_SUCCESS;
}

