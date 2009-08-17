/*
 * Konoha Document generator
 * kindofbrown@users.sourceforge.jp
 * kindofbrown(c)2009
 */

MAJ_VERSION = 1;
MIN_VERSION = 1;

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

class PackageParser {
	String[] clsdefined;
	String[] mtddefined;
	MethodInfo[] methods;
	Boolean javadocflag;
	String annotation;
	
	PackageParser () {
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
			/* do nothing */
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
		os << "import java.util.Iterator;" << EOL;
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
					line = line.replace("Int", "Integer");

					// find nullable
					reg = @'re:([a-zA-Z]+)[?]';
					if (line =~ reg) {
						m = line.match(reg);
						line = line.replace(%("%s{0}?", m[0]), %("Nullable<%s{0}>", m[0]));
					}

					// find iterator 
					reg = 're:([a-zA-Z]+)..';
					if (line =~ reg) {
						m = line.match(reg);
						line = line.replace(%("%s{0}..", m[0]), %("Iterator<%s{0}>", m[0]));
					}
					
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
	OUT << %("JavaDoc Generator 0.%d{0}.%d{1}", MAJ_VERSION, MIN_VERSION) << EOL;
	
	PackageParser p = new PackageParser();
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
	System.system(%("javadoc -nodeprecatedlist -d %s{0} %s{0}.java", packagename));

	System.system(%("konoha javadoc2konoha.k %s{0}", packagename));
	
}
