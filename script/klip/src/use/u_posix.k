//
//define functions for using posix
//
/*-----decomPackage by posix-----*/
boolean Package.decomPackage(){
	String filename = %("%s{0}-%s{1}.tar.gz",this.name,this.version);
	int ret;
	String path = klip_INST + "/" + this.name;
	ret = System.system("tar -xzf " + filename);
	if ( ret != 0 || !os.hasDir(this.name) ) { return false; }
	if ( os.hasDir(path) ) {
		String trash = rmtmp(this.name);
		os.rename(path,trash);
	}
	if ( !os.rename(this.name,path) ) {
		return false;
	}
	return true;
}