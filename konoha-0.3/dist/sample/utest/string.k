#!/usr/local/bin/konoha

import "utest.k";

String a = "aaaaa";
String b = "aaa";
String c = "a";
String d = "aabbb";
String e = "aabbcc";
String f = "aaaabbbb";
String g = "b";

print "English check:\n";
print "------operator test------\n";

utest("String +",a+b=="aaaaaaaa");

utest("String - String",f-b == "abbbb");

utest("String * int",c*3==b);

utest("String + + *3",c+c+g*3==d);

utest("String /", e/"bb"=="aa");

utest("String / size <",b/d==b);

utest("String %", e % "b" =="bcc");

utest("String % size <",b % d == "");

utest("String in?","cd"in?"aaabcddd");

utest("String in? size >","abcde"in?"cd" == false);

utest("String [m..+n]",f[2..+5]=="aabbb");

print "[f[2..+9](over)] : ";
print f[2..+9];

print "[f[-3..5](over) == ] : ";
print f[-3..+5];

print "[f[2..+(-1)] == ] : ", f[2..+(-1)];

#add by kimio kuramitsu
String s5 = "%s{0} %s{1}" %% (3, 5);
utest("String %%",  s5 == "3 5");

print "\n-------Method test-------\n"

utest("String.endsWith",e.endsWith("c") && c.endsWith("a"));

utest("String.equals", e.equals(c+"abbcc"));

utest("String.get",e.get(4)=="c");

print "[String.get size over] : "
e.get(9);

utest("String.getSize",e.getSize()==6);

utest("String.indexOf",e.indexOf("cc")==4);

utest("String.replace",e.replace("bb","dd")=="aaddcc");

utest("String.replace(2)",d.replace(g,"c") == "aaccc");

//utest("String.split" Unsupported!)

utest("String.startsWith",e.startsWith("a") && e.startsWith("aab"));
utest("String.startsWith (long arg)", !e.startsWith("aabbccd"));

utest("String.toLower","HeLlO!".toLower() == "hello!");

utest("String.toUpper","HeLlO!".toUpper() == "HELLO!");

utest("String.trim"," s1s3   ".trim() == "s1s3");
utest("String.trim space only","                ".trim() == "");

print "\nJapanese Check:\n";

String jaiu = "あいうえお";
String jaaa = "あああああ";
String ja = "あ";
String jp = "あaいaaあacいcc";
String jaiu2 = "あいうあいう";
String jk = "よろしくお願いします！";

print "------operator test------\n";

utest("String[]",jk[5] == "願");

utest("String +", jaiu+ja == "あいうえおあ");

utest("String - String", jaiu2 - "いう" == "ああ");

utest("String * int",jaiu*2=="あいうえおあいうえお");

utest("String + + *3", ja + jaiu2 + "を" * 3 == "ああいうあいうををを");

utest("String /", jp/"aあa"=="あaいa");

utest("String / size <",jaiu/jk==jaiu);

utest("String %",jp % "aあa" == "cいcc");
print jp % "aあa";

utest("String % size <",jaiu % jk=="");

utest("String in?","お願い" in? jk);

utest("String in? size >", jk in? "お願い" == false);

utest("String [m..+n]",jk[2..+4]=="しくお願");
//UnsupportedOperation!!


print "\n-------Method test-------\n"

utest("String.endsWith",jk.endsWith("！") && jp.endsWith("c"));

utest("String.equals", jp.equals("あaいaaあacいc"+"c"));

utest("String.get",jk.get(8)=="ま");

print "[String.get size over] : "
jk.get(13);

utest("String.getSize",jp.getSize()==11);

utest("String.indexOf",jp.indexOf("いc")==8); //14??
jp.indexOf("いc");

utest("String.replace",jp.replace("あ","a")=="aaいaaaacいcc");

utest("String.replace(2)",jaaa.replace(ja,"い") == "いいいいい");

//utest("String.split" Unsupported!)

utest("String.startsWith",ja.startsWith("あ") && jp.startsWith("あaい"));
utest("String.startsWith (long arg)", !ja.startsWith("sあえせ"));

utest("String.toLower",jp.toLower() == jp);

utest("String.toUpper",jp.toUpper() == "あAいAAあACいCC");

utest("String.trim","　あ　".trim() == "　あ　");
utest("String.trim(2)","　あ い う ".trim() == "　あ い う");

print "\nutest String finished!";
