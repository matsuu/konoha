#!/usr/local/bin/konoha

import "utest.k";

Float r;
Float a=0.6;
b=0.7;
c=-1.3;
Float d=12.34;

utest("float+float",a+b+c==0);

utest("float-float",a-b-c==1.2);

utest("float*float",a*b*c==-0.546);

utest("float/float",b/(-2)==-0.35);

utest("float/float(2)",c/2==-0.65);

//utest("float%float",c % b==?);

//utest("float mod float",c mod b==?);

utest("float+float*float",a+b*c==-0.31);

r=c/a*b;
utest("float/float*float",r*a==-0.91);
print r;

r=1.26/a/b;
utest("float/float/float",r==3.0);

utest("float<float",c<b);

utest("float>float",b>c);

utest("float>=float",b>=0.6 && b>=0.7);

utest("float<=float",c<=-1.2 && c<=-1.3);

utest("float!=float",b!=c);

utest("float++",(a++)==1.6);

utest("float--",(b--)==-0.3);

utest("float.getSize()",d.getSize()==12);

print "random(5)";
for(i=0;i<5;i++){
print Float.random(5);
}
