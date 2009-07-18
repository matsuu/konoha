///
/// parsing data to json
///
/*-----class Parser for Json-----*/
class ParserJson extends Parser
{

	/*-----Override Parser.setMember-----*/
	void setMember()
	{
		this.version = getElement("version");
		this.url = getElement("url");
		this.depend = getElement("depend").split("&",0);
	}

	/*-----Override Parser.generate-----*/
	String generate()
	{
		String ret;
		if ( this.url == "" ) { return ret; }
		ret += "{\n";
		ret += setNode("name",this.name) + ",\n";
		ret += setNode("version",this.version) + ",\n";
		ret += setNode("url",this.url);
		if ( this.depend[0] != "" ) { ret += ",\n" + arrayNode("depend",this.depend); }
		return ret + "\n}\n";
	}

	/*-----for setMemberJson-----*/ 
	String getElement(String elemname)
	{
		String ret;
		String raw = rawjs();
		String check = %('"name":"%s{0}"',this.name);
		while( true ) {
			if ( raw == "" ) { break; }
			else if ( check in? ( raw / "," ) ) {
				ret = parseThisTree(raw,elemname); 
				break;
			}
			raw = succRaw(raw);
		}
		return ret;
	}

	String parseThisTree(String raw,String elemname)
	{
		String ret;
		String key = %('"%s{0}":',elemname);
		while(true) {
			if ( raw == "" ) { break; }
			String pic = raw / ",";
			if ( key in? pic ) { 
				if ( elemname != "depend" ) {
					ret = pic.split('":"',0).pop();
					ret = ret.split('"',0)[0];
					return ret;
				}
				else { return getDependencies(raw); }
			} else if ( "}" in? pic && !("{0}" in? pic) ) { break; }			
			raw = succRaw(raw);
		}
		return ret;
	}

	String getDependencies(String raw)
	{
		String ret;
		String base = ( raw - "]" ) % '"depend":["';
		while( base != "") {
			ret += base.split('"',0)[0] + "&";
 			base %= '","';
		}
		return ret;
	}

	String rawjs()
	{
		String ret;
		ins = new InputStream(this.file,"r");
		foreach( String txt from ins ) {
			ret += txt;
		}
		ins.close();
		return ret - "\t";
	}

	String succRaw (String raw)	{ return raw % ","; }

	/*-----for generateJson-----*/
	String setNode(String name,String data)
	{
		return %('"%s{0}":"%s{1}"',name,data );
	}

	String arrayNode(String name,String[] data)
	{
		String ret;
		ret += %('"%s{0}":[',name);
		foreach ( String cell from data) {
			ret += %('"%s{0}",',cell);
		}
		return ret[..|ret|-2] + "]";
	}

}

