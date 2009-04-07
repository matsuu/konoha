//クラス
//	konoha.HashMap
//演算子
//	       x..        x[n]*      x[n]=y*     y in? x*  
//メソッド
//	void clear()*
//	HashMap! new(Int i)*
//	void remove(Any! k)*
//フォーマッタ
//	%dump* %k* 
//マッピング
//	HashMap
//		==> Iterator

#!/usr/local/bin/konoha

import "utest.k";

HashMap h = new HashMap();
h["key2"] = 2;
h["key1"] = 1;
h["key3"] = "three";
h["key0"] = "zero";
HashMap z = new HashMap();
z["key4"] = 4;
z["key5"] = 5;

print "%k";
%k(h);
print "%dump";
%dump(h);

utest("x[n]=y",h["key0"] == "zero");

h.remove("key3");
utest("void remove(String! k)",h["key3"] != true);
print h;

h["key4"] = 4;
utest("void set(String! k, Any v)",h["key4"] == 4);

utest("in?","key1" in? h == true);
utest("opHas(String! k)",h.opHas("key1") == true);

z.clear();
utest("clear()",(h["key4"] != true) && (h["key5"] != true));
print h,z;
//print |h|, h;
//print |z|, z;

