//クラス
//	konoha.DictMap
//演算子
//	    x << y*         x..    x[m..+n]*    x[m..<n]*     x[m..n]*  
//	      x[n]*      x[n]=y*     y in? x*         |x|*  
//メソッド
//	void clear()*
//	Boolean! isIgnoreCase()*
//	DictMap! new(Int i)
//	DictMap! new:init(Any v, ...)
//	void remove(String! k)*
//フォーマッタ
//	%k* 
//マッピング
//	DictMap
//		==> Iterator
//		==> String..

#!/usr/local/bin/konoha
import "utest.k";

DictMap d = new DictMap();
d["key2"] = 2;
d["key1"] = 1;
d["key3"] = "three";
d["key0"] = "zero";
DictMap z = DictMap.new:init("key4",4,"key5","five");

print "%k";
%k(d);

utest("|x|", |d| == 4);

utest("isIgnoreCase()", d.isIgnoreCase() == false);

utest("x[n]",d["key0"] == "zero");

d.remove("key3");
utest("void remove(String! k)",|d| == 3);

d["key3"] = "three";
utest("x[n] = y",d.get("key3") == "three");

utest("in?","key1" in? d == true);

utest("d[m..n]",d["key0".."key2"] == "{key0: \"zero\", key1: 1, key2: 2}");
print d["key0".."key2"];

utest("d[m..<n]",d["key0"..<"key2"] == "{key0: \"zero\", key1: 1}");
print d["key0"..<"key2"];

utest("d[m..+n]",d["key0"..+1] == "{key0: \"zero\", key1: 1}");
print d["key0"..+1];

d << "newKey";
utest("<<",|d| == 5);

print |d|, d;
print |z|, z;

z.clear();
utest("clear()",|z| == 0);
