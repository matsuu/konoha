//
//define functions in main
//
/*-----for undo-----*/
String[] searchChanged(String opr)
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
	int ret;
	foreach( String cell from list ) {
		String name = filter(cell,"name");
		String version = filter(cell,"version");
		String url = filter(cell,"url");
		Package pick = new Package( name,version,url );
		if( opr == "undo_inst") { ret = pick.remove(); }
		else if ( opr == "undo_rmv" ) { ret =  pick.install(); }
		if ( ret == EXIT_ERROR ) { return false; }
	}
	return true;
}

/*-----operation in main-----*/
int undoInMain()
{
	boolean ret = true;
	touchText(CURDATA,BUFDATA,COPY);
	if ( !inUndo("undo_inst") ) { dispError("undo_inst",HIDE); ret =  false; }
	if ( !inUndo("undo_rmv") ) { dispError("undo_rmv",HIDE); ret = false; }
	if ( ret == false ) { return errorExit("undo"); }
	touchText(PREVDATA,CURDATA,COPY);
	return EXIT_SUCCESS;
}

int searchInMain(Package target)
{
	if ( !getKlipData(KLIPDATA) ) { return errorExit("serach"); }
	String ret;
	if ( !target.setMember(KLIPDATA) ) {
		ret = "KLIP : package is NOT FOUND...";
	} else {
	    ret = "KLIP : package is FOUND!" + "\n";
	    ret += %("KLIP : %s{0} ver=%s{1}",target.name,target.version);
	}
	OUT << ret << EOL;
	return EXIT_SUCCESS;
}

int installInMain(Package target)
{
	int ret;
	if ( !getKlipData(KLIPDATA) ) { return errorExit("getdata"); }
	if ( !target.setMember(KLIPDATA) ) { return errorExit("setmember"); }
	touchText(CURDATA,BUFDATA,COPY);
	updateLatest("Last-Installed-Package:",%("[%s{0}] ver=%s{1}",target.name,target.version));
	if( target.depend[0] != "" ) {
		OUT << "KLIP : this package has dependency" << EOL;
		ret = target.dinstall()
	} else {
		OUT << "KLIP : package has no dependency" << EOL;
		ret = target.install();
	}
	if( ret == EXIT_ERROR ) { return errorExit("install"); }
	return ret;
}

int removeInMain(Package target)
{
	int ret;
	touchText(CURDATA,BUFDATA,COPY);
	ret = target.remove();
	if( ret == EXIT_ERROR ) { return errorExit("remove"); }
	return ret;
}

int cleanInMain()
{
	if ( os.hasFile(KLIPDATA) ) { 
		if( !os.unlink(KLIPDATA) ) { return errorExit("cleanDATA"); } 
	}
	touchText(EMPTY,CURDATA,COPY);
	touchText(EMPTY,PREVDATA,COPY);
	updateLatest("Last-Modified:"," None");
	updateLatest("Last-Installed-Package:"," None");
	return EXIT_SUCCESS;
}

int switchOperation(Package target, String operation)
{
	if ( operation == "search" ) { return searchInMain(target);	}
	else if(operation == "install"){ return installInMain(target); }
	else if (operation == "remove"){ return removeInMain(target); }
	else if (operation == "undo") {	return undoInMain(); }
	else if (operation == "clean"){ return cleanInMain(); }
	else { dispError("operation",SHOW); return EXIT_ERROR; }
}

int klipOperation(String[] args)
{
	if( |args| == 2 ) { return switchOperation(new Package("","",""),args[1]); }
	String operation = args[1];
	String name = args[2];
	String version;
	if ( |args| == 4) {
		version = args[3];
		if ( (Float)version == 0.0) { return errorExit("arg_ver"); }
	}
	return switchOperation(new Package(name,version,""),operation);
}

int endofKlip(int ret)
{
	if ( ret == EXIT_ERROR ) {
		OUT << "KLIP : some error occured!" << EOL;
	} else if ( ret == EXIT_NORMAL ) {
		OUT << "KLIP : something missed (not error)" << EOL;
	} else {
		OUT << "KLIP : success all" << EOL;
		touchText( BUFDATA, PREVDATA, RENAME );
	}
	return ret;
}
