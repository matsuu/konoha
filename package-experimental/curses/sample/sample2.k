#!/usr/local/bin/konoha
using curses.*;

OUT << "curses start" << EOL;
String message = "this is test of curses";
int ret;

lines = Curses.getLINES();
cols = Curses.getCOLS();
p1 = Curses.newpad(1,|message|);
ret = p1.keypad(true);
ret = p1.mvwaddstr(0,0,message);

int x = (cols - |message|) / 2;
int y = lines / 2 -1;
int code;
while( true ){
	ret = p1.prefresh(0,0,y,x,y,x + |message|);
	p1.wtimeout(0);
	code = p1.wgetch();
	if(code == " ".getChar()){
		x = Int.random(cols - |message| ); 
		y = Int.random(lines);
	}
	else if (code == "q".getChar()){ break; }
}

p1.endwin();
OUT << "curses end" << EOL;
