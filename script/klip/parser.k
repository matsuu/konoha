///
/// parsing data
///
using libxml2.*;

/*-----class Basic Form of Package*/
class Form
{
	String name;
	String version;
	String url;
	String[] depend;
}


/*-----class Parser for Json-----*/
class ParserJson extends Form
{

	/*-----constructor-----*/
	ParserJson(String name,String jsonfile)
	{
		this.name = name;
		this.version = getElement(name,"version",jsonfile);
		this.url =  getElement(name,"url",jsonfile);
		depend_str =  getElement(name,"depend",jsonfile);
		this.depend = depend_str.split("&",0);
	}


	String getElement(String pkgname,String elemname,String jsonfile)
	{
		String ret;
		String check = %('"name":"%s{0}"',pkgname);
		ins = new InputStream(jsonfile);
		while( true ) {
			t = ins.readLine();
			if ( t == null ) { break; }
			if( check in? t ) {
				ret = parseThisTree(ins,elemname); 
				break;
			}
		}
		ins.close();
		return ret;
	}


	String parseThisTree(InputStream ins,String elemname)
	{
		String ret;
		String check = %('"%s{0}":"',elemname);
		while(true) {
			t = ins.readLine();
			if ( "}" in? t && !("{0}" in? t) ) { break; }			
			if ( check in? t ) { 
				if ( elemname != "depend" ) { return t % check / '"'; }
				else { return getDependencies(t); }
			}
		}
		return ret;
	}


	String getDependencies(String txt)
	{
		String ret;
		String base = txt % '"depend":["';
		while( base != "}") {
			if  ( base == "" ) { break; }
			ret += base / '"';
			ret += "&";
			base %= '","'; 
		}
		return ret;
	}


	/*-----Generate Json-----*/
	String generateJson()
	{
		String ret;
		if ( this.url == "" ) { return ret; }
		ret += "{\n";
		ret += setNode("name",this.name) + ",\n";
		ret += setNode("version",this.version) + ",\n";
		ret += setNode("url",this.url);
		int i = 0;
		if ( this.depend[0] != "" ) { ret += ",\n" + setArrayNode("depend",this.depend); }
		return ret + "\n}\n";
	}


	String setNode(String name,String data)
	{
		return %('"%s{0}":"%s{1}"',name,data );
	}


	String setArrayNode(String name,String[] data)
	{
		String ret;
		ret += %('"%s{0}":[',name);
		int i = 0;
		while( i < |data| ) {
			if ( i != 0 ) { ret += ","; }
			ret += %('"%s{0}"',data[i]);
			i++;
		}
		return ret + "]";
	}

}


/*-----class Parser for Xml-----*/
class ParserXml extends Form
{

	/*-----constructor-----*/
	ParserXml(String name,String xmlfile)
	{
		this.name = name;
		this.version = getElement(name,"version",xmlfile);
		this.url = getElement(name,"url",xmlfile);
		depend_str = getElement(name,"depend",xmlfile);
		this.depend = depend_str.split("&",0);
	}


	/*-----parsing Xml-----*/
	String getElement(String pkgname, String elemname,String xmlfile)
	{ 
		XmlReader reader = new XmlReader (xmlfile);
		String ans;
		while (reader.read()) {
			type = reader.nodeType();
			if (type == XmlReader.TYPE_ELEMENT && reader.constName() == 'name') {
				reader.read();
				if (type == XmlReader.TYPE_ELEMENT && reader.constValue() == pkgname) {
					ret = parseThisTree(reader, elemname);
					reader.close();
					return ret;
				}
			}
		}
		reader.close();
		return ans;
	}
	

	String parseThisTree(XmlReader reader, String elemname)
	{
		String ans;
		while (reader.read()) {
			type = reader.nodeType();
			if (type == XmlReader.TYPE_ELEMENT) {
				curelem = reader.constName();
				if ( curelem == elemname ){
					if ( elemname == "depend" ) {
						return getDependencies(reader);
					} else if (reader.read() && type == XmlReader.TYPE_ELEMENT) {
						return reader.constValue();
					}
				}
			}
		}
		return ans;
	}
	

	String getDependencies(XmlReader reader)
	{
		String ans;
		while (reader.read()) {
			type = reader.nodeType();
			if (type == XmlReader.TYPE_ELEMENT) {
				curelem = reader.constName();
				if (curelem == 'dname') {
					if (reader.read() && type == XmlReader.TYPE_ELEMENT) {
						ans += reader.constValue() + '=';
					}
				} else if (curelem == 'dversion') {
					if (reader.read() && type == XmlReader.TYPE_ELEMENT) {
						ans += reader.constValue() + '&';
					}
				} else if (curelem == 'depend') {
					return ans;
				}
			}
		}
		return ans;
	}


	/*-----Generate Xml-----*/
	String generateXml()
	{
		String ret;
		if ( this.version == "" || this.url == "" ) { return ret; }
		ret += "<package>\n";
		ret += setNode("name",this.name) + "\n";
		ret += setNode("version",this.version) + "\n";
		ret += setNode("url",this.url) + "\n";
		int i = 0;
		ret += "<depend>\n";
		while( i < |this.depend| ) {
			if ( this.depend[i] == "") { break; }
			ret += "<dpackage>";
			dname = this.depend[i] / "=";
			ret += setNode("dname",dname);
			dversion = this.depend[i] % "=";
			ret += setNode("dversion",dversion);
			ret += "</dpackage>\n";
			i++;
		}
		ret += "</depend>\n";
		ret += "</package>\n";
		return ret;
	}


	String setNode(String attr,String data)
	{
		String ret;
		ret += setAttr(attr,0);
		ret += data;
		ret += setAttr(attr,1);
		return ret;
	}


	String setAttr(String name,int sw)
	{
		String attr;
		if( sw == 1 ) { attr = "/" + name; }
		else { attr = name; }
		attr = "<" + attr + ">";
		return attr;
	}

}
