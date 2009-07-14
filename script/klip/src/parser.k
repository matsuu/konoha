//
//registing parsers
//
/*-----class Parser Form-----*/
class Parser extends Form
{
	String file;
	/*-----constructor-----*/
	Parser(String name, String file)
	{
		this.name = name;
		this.file = file;
 	}

	/*-----Data2Package-----*/
	void setMember(){}
}

//*-----get current version from curdata-----*/
String getCurVer(String name)
{
	Parser p = new Parser(name,CURDATA);
	p.setMember();
	return p.version;
}