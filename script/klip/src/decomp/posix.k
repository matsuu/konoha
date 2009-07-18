//
//define functions for using posix
//
/*-----decompPackage by posix-----*/
class DecompSystem extends Decomp {

	/*-----Decomp.decompPackage-----*/
	boolean decompPackage(){
		String filename = %("%s{0}-%s{1}.tar.gz",name,version);
		int ret;
		ret = System.system("tar -xzf " + filename);
		if ( ret != 0 || !os.hasDir(name) ) {
			print("!ERR : DecompSystem.decompPackage : System.system");
			return false;
		}
		os.rename(name,__path + name);
		return true;
	}
}