#!/usr/local/bin/konoha

void readfile(String filename)
{
	OUT << "opening.. " << filename << EOL;
	foreach(String line from new InputStream(filename)) {
		OUT << line << EOL;
	}
}

void main(String[] argv) {
	foreach(String a from argv) {
		readfile(a);
	}
}

