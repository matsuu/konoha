#!/usr/local/bin/konoha
using curses.*;

OUT << "curses start" << EOL;

String[] msg =[
"This is test of curses!", 
"Hello,world!",
"This is a pen.",
"This is written by konoha.",
"What's up?",
"How are you?",
"Have a nice day!",
"Good night...",
"umm..."
];


String message = msg[0];
int ret;

lines = Curses.getLINES();
cols = Curses.getCOLS();
p1 = Curses.newpad(1,cols);
ret = p1.keypad(true);
ret = p1.mvwaddstr(0,0,message);

int x = (cols - |message|) / 2;
int y = lines / 2 -1;
int code;
while( true ){
	ret = p1.prefresh(0,0,y,x,y,x + |message|-1);
	p1.wtimeout(0);
	code = p1.wgetch();
	if( code == Curses.KEY_ENTER || code == " ".getChar() ){
		message = msg[Int.random(|msg|)];	  
		ret = p1.mvwaddstr(0,0,message);
		x = Int.random(cols - |message| ); 
		y = Int.random(lines);
	}
	else if (code == "q".getChar()){ break; }
}

p1.endwin();
OUT << "curses end" << EOL;
