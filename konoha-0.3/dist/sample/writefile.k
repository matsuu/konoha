#!/usr/local/bin/konoha

void readfile(String filename)
{
	foreach(String line from new InputStream(filename)) {
		OUT << line << EOL;
	}
}

void main(String[] argv) {
	if(|argv| == 0) {
		ERR << "needs filename" << EOL;
	}
	else {
		print "opening ..", argv[0];
		out = new OutputStream(argv[0], "a");
		out << "I love you." << EOL;
		out.close();
	}
}

