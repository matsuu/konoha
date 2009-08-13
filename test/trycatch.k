#!/usr/local/bin/konoha

import "utest.k";

try {
    throw new IO!!();
    os.OUT.println "hello";
}
catch(IO!! e) {
    os.OUT.println "IO!!";
}
catch(Exception e) {
    os.OUT.println "Exception!!";
}
finally {
    os.OUT.println"finally";
}

