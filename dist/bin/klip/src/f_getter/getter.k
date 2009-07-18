//
//define glue class for get package
//
class Getter {

	String url;

	/*-----constructor-----*/
	Getter(String url){
		this.url = url;
	}

	/*-----get package data-----*/
	@virtual boolean getPackage();

}