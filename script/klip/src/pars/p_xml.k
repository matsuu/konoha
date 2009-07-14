///
/// parsing data to Xml
///
using libxml2.*;
import "form.k";

/*-----class Parser for Xml-----*/
class ParserXml extends Form
{
	String file;

	/*-----constructor-----*/
	ParserXml(String name,String xmlfile)
	{
		this.name = name;
		this.file = xmlfile;
	}

	/*-----parsing Xml-----*/
	String getElement(String elemname)
	{ 
		XmlReader reader = new XmlReader (this.file);
		String ans;
		while (reader.read()) {
			type = reader.nodeType();
			if (type == XmlReader.TYPE_ELEMENT && reader.constName() == 'name') {
				reader.read();
				if (type == XmlReader.TYPE_ELEMENT && reader.constValue() == this.name) {
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
		if ( this.url == "" ) { return ret; }
		ret += setAttr("package",0) + "\n";
		ret += setNode("name",this.name) + "\n";
		ret += setNode("version",this.version) + "\n";
		ret += setNode("url",this.url) + "\n";
		int i = 0;
		ret += setAttr("depend",0) + "\n";
		foreach( String cell from this.depend ) {
			if ( cell == "") { break; }
			ret += setAttr("dpackage",0) + setNode("dname",cell / "=");
			ret += setNode("dversion",cell % "=") + setAttr("dpackage",1) + "\n";
		}
		ret += setAttr("depend",1) + "\n";
		return  ret + setAttr("package",1) + "\n";
	}

	String setNode(String attr,String data)
	{
		return setAttr(attr,0) + data + setAttr(attr,1);
	}

	String setAttr(String name,int sw)
	{
		String ret;
		if( sw == 1 ) { ret = "/" + name; }
		else { ret = name; }
		return "<" + ret + ">";
	}
}

/*-----Xml2Package-----*/
void Parser.setMember()
{
	String buf = "xml";
	ParserXml pars = new ParserXml(this.name,this.file);
	this.name = pars.name;
	this.version = pars.getElement("version") + buf - buf;
	this.url = pars.getElement("url") + buf - buf;
	this.depend = pars.getElement("depend").split("&",0);
}
