#!/usr/local/bin/konoha
using curses.*;

c = new Curses(20,20,0,0);
c.keypad(true);
c.wmove(1,2);
c.waddstr("curses sample\n");
c.waddstr("0 to move left\n");
c.waddstr("1 to move right");
pos = 5;
while(1){
    c.wtimeout(0);
    code = c.wgetch();
    c.mvwaddstr(,10,4,"key code:["+code+"]");
    if((code == '1'.getChar() ) && pos > 1){
        pos--;
    }
    if((code == '0'.getChar()) && pos < 20){
        pos++;
    }
    c.wmove(4,pos);
    c.waddstr(" @ ");

    if(code == 'q'.getChar()) break;
    c.wrefresh();
}

c.endwin();

