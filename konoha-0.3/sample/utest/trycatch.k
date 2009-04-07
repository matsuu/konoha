#!/usr/local/bin/konoha

import "utest.k";

try {
	throw new IO!!();
	print "hello";
}
catch(IO!! e) {
	print "IO!!";
}
catch(Exception e) {
	print "Exception!!";
}
finally {
	print "finally";
}

