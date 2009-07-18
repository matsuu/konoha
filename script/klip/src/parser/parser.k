//
//registing parsers
//
/*-----class Parser Form-----*/
class Parser
{
	String name;
	String version;
	String url;
	String[] depend;
	String file;

	/*-----constructor-----*/
	Parser(String name, String file)
	{
		this.name = name;
		this.depend = [];
		this.file = file;
 	}

	/*-----Data2Package-----*/
	@virtual void setMember();

	/*-----generate formed txt-----*/
	@virtual String generate();

}
