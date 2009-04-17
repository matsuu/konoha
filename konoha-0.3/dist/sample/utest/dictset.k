//クラス
//	konoha.DictSet
//演算子
//	    x << y*         x..    x[m..+n]*    x[m..<n]*     x[m..n]*  
//	      x[n]*      x[n]=y*     y in? x*         |x|*  
//メソッド
//	void add(String! k)*
//	void clear()*
//	Boolean! isIgnoreCase()*
//	DictSet! new(Int i)*
//	void remove(String! k)*
//フォーマッタ
//	%dump %k* 
//マッピング
//	DictSet
//		==> Iterator
//		==> String..

#!/usr/local/bin/konoha

import "utest.k";

DictSet d = new DictSet();
d["key1"]=11;
d["key0"]=0;
d["key3"]=3;
d["key2"]=22;
DictSet e = new DictSet();
e["key5"]=12;
e["key4"]=2;

print "%k";
%k(d);
print "%dump";
%dump(d);

utest("|x|",|d| == 4);

utest("isIgnoreCase()", d.isIgnoreCase() == false);

d.add("key4");
utest("void add(String! k)",|d| == 5);

utest("x[n]",d["key1"] == 11);

d << "newkey";
utest("<<",|d| == 6);

d.remove("key0");
utest("void remove(String! k)",|d| == 5);

d["key0"] = 100;
utest("x[n] = y",d["key0"] == 100);

utest("in?","key2" in? d == true);

utest("[m..+n]",d["key0"..+2] == "{key0, key1}");
print d["key0"..+2];

utest("[m..n]",d["key0".."key1"] == "{key0, key1}");
print d["key0".."key1"];

utest("[m..<n]",d["key0"..<"key2"] == "{key0, key1}");
print d["key0"..<"key2"];

print d;
d.clear();
utest("void clear()",|d| == 0);
