//
//define functions in main
//
/*-----operations in main-----*/
int undoInMain()
{
	copyText(CURDATA,CURDATA + "~");
	boolean ret;
	ret = do_undo();
	copyText(CURDATA + "~",PREVDATA);
	os.unlink(CURDATA + "~");
	if ( !ret ) {
		OUT.println("!ERR : some was failed in undo...");
		return EXIT_NORMAL;
	}
	return EXIT_SUCCESS;
}

int searchInMain(Package target)
{
	if ( !getKlipData(KLIPDATA) ) {
		return errorExit("serach");
	}
	String ret;
	if ( !target.setMember(KLIPDATA) ) {
		ret = "KLIP : package is NOT FOUND...";
	} else {
	    ret = "KLIP : package is FOUND!" + "\n";
	    ret += %("KLIP : %s{0} ver=%s{1}",target.name,target.version);
	}
	OUT.println(ret);
	return EXIT_SUCCESS;
}

int installInMain(Package target)
{
	int ret;
	if ( !getKlipData(KLIPDATA) ) {
		return errorExit("getdata");
	}
	if ( !target.setMember(KLIPDATA) ) {
		OUT.println("KLIP : package is NOT FOUND...");
		return EXIT_NORMAL;
	}
	copyText(CURDATA,CURDATA + "~");
	updateLatest("Last-Installed-Package:",%("[%s{0}] ver=%s{1}",target.name,target.version));
	if( target.depend[0] != "" ) {
		OUT.println("KLIP : this package has dependency");
		ret = dinstall(target)
	} else {
		OUT.println("KLIP : package has no dependency");
		ret = target.install();
		String[] data = [target.name,target.version,target.url];
		endofOpration(ret,"install",data);
	}
	os.unlink(CURDATA + "~");
	return ret;
}

int updateInMain(Package target)
{
	int ret;
	if ( !getKlipData(KLIPDATA) ) {
		return errorExit("getdata");
	}
	if ( !target.setMember(KLIPDATA) ) {
		return errorExit("setmember"); 
	}
	copyText(CURDATA,CURDATA + "~");
	updateLatest("Last-Installed-Package:",%("[%s{0}] ver=%s{1}",target.name,target.version));
	ret = target.update();
	String[] data = [target.name,target.version,target.url];
	endofOpration(ret,"update",data);
	os.unlink(CURDATA + "~");
	return ret;
}

int removeInMain(Package target)
{
	int ret;
	copyText(CURDATA,CURDATA + "~");
	ret = target.remove();
	String[] data = [target.name,target.version,target.url];
	endofOpration(ret,"remove",data);
	os.unlink(CURDATA + "~");
	return ret;
}

int cleanInMain()
{
	if ( os.hasFile(KLIPDATA) ) { 
		if( !os.unlink(KLIPDATA) ) {
			return errorExit("cleanDATA"); 
		} 
	}
	resetText2Js(CURDATA);
	resetText2Js(PREVDATA);
	updateLatest("Last-Modified:"," None");
	updateLatest("Last-Installed-Package:"," None");
	return EXIT_SUCCESS;
}

int switchOperation(Package target, String operation)
{
	int ret;
	if ( operation == "search" ) {
		ret = searchInMain(target);
	} else if(operation == "install") {
		ret = installInMain(target);
	} else if(operation == "update") {
		ret = updateInMain(target);
	} else if (operation == "remove") {
		ret = removeInMain(target);
	} else if (operation == "undo") {
		ret = undoInMain(); 
	} else if (operation == "clean") {
		ret = cleanInMain(); 
	} else {
		return errorExit("operation");
	}
	if ( ret == EXIT_ERROR ) {
		return errorExit(operation);
	}
	return ret;
}

int Script.klipMain(String[] args)
{
    int ret;
    if ( |args| == 2 ) {
		Package n = new Package("","","");
		ret = switchOperation(n,args[1]);
	}  else if ( |args| == 3 ){
		Package p = new Package(args[2],"","");
		ret = switchOperation(p,args[1]);
	} else {
		return errorExit("usage"); 
	}
    return ret;
}

