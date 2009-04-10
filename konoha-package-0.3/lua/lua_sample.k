using lua.*;
l=new Lua();
/*
l.doString("function fib(n) if n < 2 then return n else return fib(n-1)+fib(n-2) end end" );
l.doString("print(fib(10))");
*/
l.doFile("fib.lua");
