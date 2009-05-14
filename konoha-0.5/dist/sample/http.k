#!/usr/local/bin/konoha

foreach(String line 
        from new InputStream("http://www.ubicg.ynu.ac.jp")) {
	OUT << line << EOL;
}

