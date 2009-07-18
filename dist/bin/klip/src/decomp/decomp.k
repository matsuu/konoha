//
//define glue class for decompress
//
class Decomp {

	String name;
	String version;

	Decomp(String name,String version){
		this.name = name;
		this.version = version;
	}

	@virtual boolean decompPackage();

}

