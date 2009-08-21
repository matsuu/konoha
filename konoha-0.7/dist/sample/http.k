#!/usr/local/bin/konoha

foreach(String line 
        from new InputStream("http://konoha.sourceforge.jp/script/fibo.k")) {
	OUT << line << EOL;
}

