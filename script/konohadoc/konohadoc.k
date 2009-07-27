/*
 * Konoha Document generator
 */


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

	void gen() {
		foreach(String line in defaultclasses) {
			OUT << typeof(line) << EOL;
			line.indexOf("hi");

		}
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
	KonohaDocGenerator kdg = new KonohaDocGenerator();

	kdg.importing(args[1]);
	kdg.showdiff();
//	kdg.showClasses();
	kdg.showMethods();
	kdg.showModSigs();
}
