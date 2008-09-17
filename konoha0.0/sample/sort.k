#!/usr/local/bin/konoha


a = [];

for(i = 0; i < 10000; i++) {
	a.add(Int.random(1000));
}

print a
//size = |a|;

for(i = 0; i < |a| - 1; i++) {
	for(j = i+1; j < |a|; j++) {
		if(a[i] > a[j]) {
			n = a[i];
			a[i] = a[j];
			a[j] = n;
		}
	}
}

print "sorted ", |a|;


	