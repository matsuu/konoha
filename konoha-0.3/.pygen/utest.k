#!/usr/local/bin/konoha

void utest(String! name, Boolean! test) {
	if(test) {
		OUT << "[" << name << "]: PASS" << EOL;
	}
	else {
		OUT << "[" << name << "]: ** FAILED **" << EOL;
	}
}




