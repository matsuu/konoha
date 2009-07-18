//
//define functions for using zlib & libtar
//
/*-----decompPackage by using zlib & libtar-----*/
class DecompZllT extends Decomp {

	/*-----Decomp.decompPackage-----*/
	boolean decompPackage(){
		String filename = %("%s{0}-%s{1}.tar.gz",name,version);
		if ( !Zlib.decompGZ(filename) ) {
			print("!ERR : DecompZllT.decompPackage : Zlib.decompGZ");
			return false;
		}
		String tarfile = filename - ".gz";
		boolean res = Tar.extractTar(tarfile);
		os.unlink(tarfile);
		if ( !res || !os.hasDir(name) ) {
			print("!ERR : DecompZllT.decompPackage : Tar.extractTar == " + res );
			return false;
		}
		os.rename(name,__path + name);
		return true;
	}
	
}