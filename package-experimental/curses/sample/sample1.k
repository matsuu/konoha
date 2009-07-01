#!/usr/local/bin/konoha
using curses.*;

OUT << "curses start" << EOL;

String chmod()
{ 
	while(true)	{
		i = Int.random(127); 
		if ( i > 32 ) { return %c(i); }
	}
}

void rlc(Curses c,int code)
{
	c.mvwaddstr(10,i," " * 18);
	str = "key code:[" + code + "]";
	c.mvwaddstr(10,3,str);
}

c = new Curses(20,20,0,0);
c.keypad(true);
c.mvwaddstr(0,3,"curses sample");

int i;
c.mvwaddstr(1,0,"*" * 19);
for(i=2;i<9;i++){ c.mvwaddstr(i,0,"*"); c.mvwaddstr(i,18,"*");}
c.mvwaddstr(9,0,"*" * 19);

int line = 5;
int pos = 9;
String str;
String ch = "0";

while(1){
    c.wtimeout(0);
    code = c.wgetch();
	if( code != -1 ) { rlc(c,code); }
	c.mvwaddstr(line,pos," ");
    if((code == Curses.KEY_LEFT) && pos > 1){ pos--; }
	else if((code == Curses.KEY_RIGHT) && pos < 17){ pos++; }
	else if((code == Curses.KEY_DOWN) && line < 8){ line++; }
	else if((code == Curses.KEY_UP) && line > 2){ line--; }
	else if(code == Curses.KEY_ENTER){ ch = chmod(); }
	else if(code == ' '.getChar()){ ch = chmod(); }
	else if(code == 'q'.getChar()) { break; }
    c.mvwaddstr(line,pos,ch);
    c.wmove(line,pos);
    c.wrefresh();
}

c.endwin();
OUT << "curses end" << EOL;
