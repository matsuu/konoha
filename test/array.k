/* unit test for Array */
import "utest.k";

print "\n------operator test------\n";
a = [0, 1, 2, 3, 4, 5];
c = [0, 0, 0, 0, 0, 0];
utest("array size", |a| == 6);
utest("a[n]",a[5] == 5);

//utest("y in? x",a in? 5 ==true);

b = a[2..4];
try{
utest("x[s..e]",b[0]==2 && b[1] ==3 && b[2]==4);
}catch(Exception e){
print"[x[s..e]]: ** FAILED **";
}

c = a[2..<4];
try{
utest("x[s..<e]",c[0]==2 && c[1] ==3 && |c| == 2);
}catch(Exception e){
print"[x[s..<e]]: ** FAILED **";
}

c = a[2..+2];
try{
utest("a[s..+e]",c[0]==2 && c[1]==3 && |c| == 2);
}catch(Exception e){
print"[a[s..+e]]: ** FAILED **";
}

c << 4;
try{
utest("x << y",c[2] == 4);
}catch(Exception e){
print"[x << y]: ** FAILED **"; 
}

print "\n-------Method test-------\n";
c.add(5);
utest("void add(Any v)",c[3]==5);

c.clear();
utest("void clear()",|c| == 0);

c = [0,1,2,3,4,5];
utest("Any pop()",c.pop() == 5 && c[-1] == 4);

c = [0,1,2,3,4,5];
c.remove(3);
utest("void remove(Int! n)",c[3]==4 && |c| == 5); 

c = [0,1,2,3,4,5];
c.swap(2,4);
utest("void swap(Int! m, Int! n)",c[2] == 4 && c[4] == 2);
utest("Int! indexOf(Any v)",c.indexOf(3) == 3);

c = [0,1,0,1,0,1];
utest("Int! lastIndexOf(Any v)",c.lastIndexOf(0) == 4);

c = [0,1,2,3,4,5]; 
c.insert(2,10);
utest("void insert(Int! n, Any v)",c[2] == 10 && c[1] == 1 && c[3] == 2);


//c = [0,1,2,3,4];
//c.reverse();
//utest("void reverse()",c[0] == 4 && c[1] == 3 && c[2] == 2 && c[3] == 1 $$ c[4] == 0);

c = [0,1,2,3,4,5];
print"\n";
print(c) ;
print"c.shuffle()";
for(i=0;i<5;i++){
	c.shuffle();
	print(c);
	}
print"\n";

n = a[0];
utest("array type", typeof(n) == Int);
utest("array first", a[0] == 0);
utest("array last", a[-1] == 5);

a[] = 0;
n = 0;
for(i = 0; i < |a|; i++) {
  n += a[i];
}
utest("array allset", n == 0);

/* Two dimension */

a2 = new int[10, 10];
utest("array 2D", |a2| == 10 * 10);

a2[2,3] = 1;
utest("array 2D(get)", a2[2,3] == 1);

print "\nutest Array finished!";
