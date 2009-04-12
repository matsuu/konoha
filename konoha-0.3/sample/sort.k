#!/usr/local/bin/konoha

a = new int[10000];

for(i = 0; i < 10000; i++) {
	a[i] = Int.random(10000);
}

//print a
//size = |a|;

{
register a.opSize(), a.opSize()-1;
for(i = 0; i <  a.opSize() - 1; i++) {
	for(j = i+1; j < a.opSize(); j++) {
		register a[i], a[j];
		if(a[i] > a[j]) {
			n = a[i];
			a[i] = a[j];
			a[j] = n;
		}
	}
}
}

print "sorted ", |a|;


	
