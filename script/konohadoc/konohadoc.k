/*
 * Konoha Document generator
 * kindofbrown@users.sourceforge.jp
 * kindofbrown(c)2009
 */

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
		classn = ''
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

	void genJava () {
		foreach(String cls in clsdefined) {
			OUT << %("public class %s{0} {", cls) << EOL;
			
			  foreach (MethodInfo mi in methods) {
				if (mi.classname == cls) {
					/* replace Method new with Constructor */
					OUT << mi.annotation << EOL;
					if (mi.name == 'new') {
						line = mi.defs.replace("new", "");
					} else {
						line = mi.defs;
					}
					line = line.replace(%("%s{0}.", cls), "");
					line = line.replace(";", "");
					line = line.replace("?", "");
					//TODO iterator transform
					line = line.replace("..", "");
					OUT << %("\tpublic %s{0} { }", line) << EOL;
				}
			}
			
			OUT << "}" << EOL;
		}
	}
	
}

class KonohaDocGenerator {
	Class[] defaultclasses;
	Class[] afterclasses;
	Class[] newclasses;
	Method[] newmethods;

	KonohaDocGenerator() {
		defaultclasses = domain(Class);
		afterclasses = [];
		newclasses = [];
		newmethods = [];
	}

	void importing(String file) {
		eval('import "' + file + '";');
		afterclasses = domain(Class);
	}

	void showdiff () {
		int index = 0;
		foreach (Class c in afterclasses) {
			index++;
		}
		int def_idx = 0;
		int aft_idx = 0;
		while(aft_idx<index) {
			if (defaultclasses[def_idx] == afterclasses[aft_idx]) {
				def_idx++; aft_idx++;
			} else {
			    newclasses << afterclasses[aft_idx];
				aft_idx++;
			}
		}
	}

	void showClasses() {
		foreach(Class x in newclasses) {
			OUT << x << EOL; 
		}
	}

	void showMethods() {
		foreach (Method m in domain(Method)) {
			line = %("%s{0}", m);
			foreach (Class c in newclasses) {
				clsname = %("%s{0}", c);
				if (clsname in? line) {
					newmethods << m;
//					OUT << line << EOL;
				}
			}
		}
	}

	void showSigs() {
		foreach (Method m in newmethods) {
			OUT << %k(m) << EOL;
//			c = delegate(m);
//			OUT << typeof(c) << EOL;
		}
	}

	void showModSigs() {
		/* constructors */
		preclsname = ''
		foreach(Method m in newmethods) {
			line = %k(m);
			i = line.indexOf(" ")+1;
			j = line.indexOf(".") - 1;
			clsname = line[i..j];
			if (preclsname != clsname) {
				if (preclsname != '') {
					OUT << "}" << EOL;
				}
				OUT << %("public class %s{0} {", clsname) << EOL;
				preclsname = clsname;
			} 
			i = i - 1;
			if ('.new(' in? line) {
				r = line.indexOf('.new(');

				OUT << '\tpublic ' << line[..i]  << line[r+4..] << "{ }" << EOL;
			} else {
				r = line.indexOf(@".");
				OUT << '\tpublic ' << line[..i] << line[r+1..] << "{ }" << EOL;
			}
		}

		OUT << "}" << EOL;
	}

	void generate(String filename) {
		OutputStream os = new OutputStream(filename, "w");


		os.close();
	}
}

int main (String[] args)
{
	if (|args| < 2) {
		OUT << "usage:" << EOL;
		return 0;
	}

/*
	KonohaDocGenerator kdg = new KonohaDocGenerator();

	kdg.importing(args[1]);
	kdg.showdiff();
//	kdg.showClasses();
	kdg.showMethods();
	kdg.showModSigs();
	*/

	ScriptParser p = new ScriptParser();
	lines = [];
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
	p.genJava();
	
}
