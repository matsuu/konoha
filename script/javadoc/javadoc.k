/*
 * Konoha Document generator
 * kindofbrown@users.sourceforge.jp
 * kindofbrown(c)2009
 */

using posix.*;

class MethodInfo {
	String name;
	String classname;
	String retval;
	String args;
	String defs;
	String annotation;

	MethodInfo() {
		name = '';
		classname = '';
		defs= '';
		retval = '';
		args = '';
		annotation = '';
	}
}

class ScriptParser {
	String[] clsdefined;
	String[] mtddefined;
	MethodInfo[] methods;
	Boolean javadocflag;
	String annotation;
	Parser () {
		clsdefined = [];
		mtddefined = [];
		methods = [];
		javadocflag = false;
		annotation = "";
	}
	
	/**
	 * One line parser and checks if it has a 
	 * style of class definition, or
	 * method definition.
	 */
	void parseOneLine(String line) {
		re = @'re:[A-Za-z0-9.[]+[] \n]+[A-Za-z0-9]+[.][A-Za-z0-9]+[(]';
		classn = '';
		if (javadocflag == true) {
			if (annotation == "") annotation = "/**" + EOL;
			if ("*/" in? line) {
				javadocflag = false;
			}
			annotation = annotation + line + EOL;
		}
		
		if ("/**" in? line) {
			annotation = "";
			javadocflag = true;
		}else if (line =~ /class/ ) {
			classn = line;
			classn = classn.trim();
			classn = classn.replace("class ", "");
			classn = classn.replace(";","");
			clsdefined << classn;

		} else if (line =~ re) {
			/* here we parse methods */
			tmp = line.trim();
			tmp = tmp.replace("..", "");
			didx = tmp.indexOf(".");
			sidx = tmp.indexOf(" ");
			pidx = tmp.indexOf("(");
			mname = tmp[(didx+1)..(pidx-1)];

			tmp = tmp[sidx..didx];
			belonging = '';
			foreach(String s in clsdefined) {
				if (s in? tmp) {
					belonging = s;
					break;
				}
			}
			MethodInfo mi = new MethodInfo();
			mi.name = mname;
			mi.classname = belonging;
			mi.defs = line;
			mi.annotation = annotation;
			methods.add(mi);
			annotation = "";
		} else {
			/* it is out */
		}
	}
	
	void showclasses() {
		foreach(String s in clsdefined) {
			OUT << s << EOL;
		}
	}

	void showmethods () {
		foreach (MethodInfo mi in methods) {
			OUT << %("class:%s{0} methods:%s{1}", mi.name, mi.classname) << EOL;
			OUT << mi.defs << EOL;
		}
	}

	void genJava (String filename) {
		os = new OutputStream(filename, "w");
		foreach(String cls in clsdefined) {
			os << %("public class %s{0} {", cls) << EOL;
			
			  foreach (MethodInfo mi in methods) {
				if (mi.classname == cls) {
					/* replace Method new with Constructor */
					os << mi.annotation << EOL;
					if (mi.name == 'new') {
						line = mi.defs.replace("new", "");
					} else {
						line = mi.defs;
					}
					line = line.replace(%("%s{0}.", cls), "");
					line = line.replace(";", "");
					line = line.replace("?", "<Nullable>");
					//TODO iterator transform
					line = line.replace("..", "");
					os << %("\tpublic %s{0} { }", line) << EOL;
				}
			}
			
			os << "}" << EOL;
		}
		os.close();
	}
	
}

int main (String[] args)
{
	if (|args| < 2) {
		OUT << "usage:" << EOL;
		return 0;
	}

	ScriptParser p = new ScriptParser();
	lines = [];
	/* Cutout comments from script */
	foreach(String line from new InputStream(args[1], "r")) {	
		line = line.trim();
		if (line.startsWith(@"//")) {
			continue;
		}
		lines << line;
	}

	foreach(String line from lines) {
		p.parseOneLine(line);
	}
//	p.showclasses();
//	p.showmethods();
	packagename = args[1].replace(".k", "");
	filename = args[1].replace(".k", ".java");
	p.genJava(filename);
	System.system(%("javadoc -d %s{0} %s{0}.java", packagename));

	System.system(%("konoha javadoc2konoha.k %s{0}", packagename));
	
}
