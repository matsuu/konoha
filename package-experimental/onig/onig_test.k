using onig.*;
Onig.compile("^[^0-9][a-zA-Z0-9_]+([.][a-zA-Z0-9_]+)*[@][a-zA-Z0-9_]+([.][a-zA-Z0-9_]+)*[.][a-zA-Z]{2,4}$");


Onig.match("hoge@gmail.com");

Onig.compile("[a-z]+");
Onig.match("12hogehoge");
