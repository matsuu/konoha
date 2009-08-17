using posix.*


int main (String[] args) {

	if (|args| < 3) {
		OUT << """
usage : konoha javadoc2konoha.k dir
""";
	}
	dirs = System.listdir(args[1]);
	foreach (String file in dirs) {
		if (System.hasDir(args[1] + "/"+file) == true) {
			OUT << "dir:" << file << EOL;
		} else {
			// its file.
			if (".html" in? file) {
				OUT << "html:" << file << EOL;
				htmlFormat(args[1] + "/" + file);
			}else if (".css" in? file) {
				OUT << "css:" << file << EOL;
				cssFormat(args[1] + "/" + file);
			} else {
				OUT << file << EOL;
			}
		}
	}
}


void htmlFormat (String path) {
	file = [];
	foreach (String line from new InputStream(path, "r")) {
		buf = line;
		if ("java.lang." in? buf){
			buf = buf.replace("java.lang.", "");
		}
		if ("java.util." in? buf) {
			buf = buf.replace("java.util.","");
		}
		file << buf << EOL;
	}
	os = new OutputStream(path, "w");
	foreach (String line in file) {
		os << line;
	}
	os.close();
}



void cssFormat (String path) {
	file = [];
	foreach (String line from new InputStream(path, "r")) {
		if ("CCCCFF" in? line) {
			file << line.replace("CCCCFF", "66CC66") << EOL;
		} else if ("EEEEFF" in? line) {
			file << line.replace("EEEEFF", "CCFFCC") << EOL;
		} else if ("00008B" in? line) {
			file << line.replace("00008B", "008B00") << EOL;
		} else {
			file << line << EOL;
		}
	}
	os = new OutputStream(path, "w");
	foreach (String line in file) {
		os << line;
	}
	os.close();
}
