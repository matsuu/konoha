#!/usr/local/bin/konoha

import "utest.k";

int r;
int a=1;
b=0b00010;
c=-3;

utest("int+int",a+b+c==0);

utest("int-int",a-b-c==2);

utest("int*int",a*b*c==-6);

utest("int/int",b/-2==-1);

utest("int/int(2)",c/2==-1);

utest("int%int",c % b==-1);

utest("int mod int",c mod b==-1);

utest("int+int*int",a+b*c==-5);

r=c/a*b;
utest("int/int*int",r==-6);

r=18/c/b;
utest("int/int/int",r==-3);

r=c&5;
utest("int&int",r==5);

r=c^b;
utest("int^int",r==-1);

r=c<<1;
utest("int<<int",r==-6);

r=7 >> 1;
utest("int>>int",r==3);

r=b|c;
utest("int|int",r==-1);

r= ~b;
utest("~int",r==-3);

utest("int<int",c<b);

utest("int>int",b>c);

utest("int>=int",b>=-1 && b>=2);

utest("int<=int",c<=1 && c<=-3);

utest("int!=int",b!=c);

utest("int==string", a != "1");

utest("int++",(a++)==2);
utest("++int",(++a)==3);//

utest("int--",(b--)==1);
utest("--int",(--b)==0);//

print "random(10) & %bits"; 
int n = 0;
for(i=0;i<5;i++){
n = Int.random(10);
print n + " = " + %bits(n);
}

print "==FORMATTERS==";

int i = 10;

utest("%d(n)",%d(i)=="10");
utest("%05d(n)",%05d(i)=="00010");

utest("%f(n)",%f(i)==(String)(float)10);
utest("%2.2f(n)",%2.2f(i)=="10.00");

utest("%s(n)",%s(i)=="10");

utest("%u(n)",%u(i)=="10");

utest("%x(n)",%x(i)=="a");
