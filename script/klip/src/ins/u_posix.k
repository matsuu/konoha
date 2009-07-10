//
//define functions for using posix
//
/*-----decomPackage by posix-----*/
boolean Package.decomPackage(){
	String filename = %("%s{0}-%s{1}.tar.gz",this.name,this.version);
	int ret;
	ret = System.system("tar -xzf " + filename + " -C " + klip_INST);
	if ( ret != 0 ) { return false; }
	return true;
}