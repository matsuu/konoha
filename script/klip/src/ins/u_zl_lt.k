//
//define functions for using zlib & libtar
//
/*-----decomPackage by zlib & libtar-----*/
boolean Package.decomPackage(){
	String filename = %("%s{0}-%s{1}.tar.gz",this.name,this.version);
	if ( !Zlib.decompGZ(filename) ) { return false; }
	String tarfile = filename - ".gz";
	boolean res = Tar.extractTar(tarfile);
	os.unlink(tarfile);
	if ( !res ) { return false; }
	if ( !os.hasDir(this.name) ) { return false; }
	String path = klip_INST + "/" + this.name;
	if ( !os.rename(this.name,path) ) {
		String trash = rmtmp(this.name);
		os.rename(this.name,trash);
		return false;
	}
	return true;
}
