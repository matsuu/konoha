#!/usr/local/bin/konoha

class Counter {
	int count;
	Counter(int count) {
		_count = count;
	}
	
	void count() {
		_count++;
	}
	
	void reset() {
		_count = 0;
	}
}

void main(String[] argv) {
	Counter c = new Counter(0);
	for(i = 0; i < 10000; i++) {
		c.count();
	}
	print c.count;
	if(c.count == 10000) {
		print "ok";
	}
}

