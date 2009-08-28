#!/usr/local/bin/konoha

import "utest.k";

n = 0;
if(n < 10 && n == 0) {
	n = 1;
}
else {
	n = -1;
}

if(n == -1) {
	n = 3;
}
else {
	n = 2;
}

utest("if statement", n == 2);

n = 1;
if(n == 0) {
	n = 1;
}
else if(n == 1) {
	n = 2;
}
else {
	n = 3;
}

utest("if-else if", n == 2);

n = 0;
while(n < 10) {
	n++;
}

utest("while loop", n == 10);

n = 0;
do {
	n++;
} while (n < 10);

utest("do-while loop", n == 10);

n = 0;
for(i = 0; i < 10; i++) {
	n = i;
}

utest("for loop", n == 9);

n = 0;
for(i = 0; i < 10; i++) {
	for(j = i + 1; j < 10; j++) {
		if(i + j == 10) n = i + j;
	}
}

utest("nested loop", n == 10);

n = 0;
for(;;) {
	n = Int.random(10);
	if(n == 5) break;
}

utest("break", n == 5);

n = 0;
for(i = 0; i < 10; i++)  {
	if(i > 4) continue;
	n += i;
}

utest("continue", n == 10);

try {
	print "hello";
}
catch(IO!! e) {
	print "IO!!";
}
catch(Exception e) {
	print "Exception!!";
}
finally {
	print "finally";
}
