#!/usr/local/bin/konoha
import "walk.k"

MAKEFILE = "../build/Makefile.am";

int main(String[] args)
{
    OutputStream o = new OutputStream(MAKEFILE,"w");
    o.print("""# this Makefile is generated from ../gensrc/gen_automake.k
# masahiro@ynu(c)2009
# shinpei@ynu(c)2008

# make target for libtool.
CFLAGS = -g3 -O3 -pipe
lib_LTLIBRARIES = libkonoha.la

libkonoha_la_LDFLAGS = -no-undefined -release 0 -version-info 5:0:0
#if LDL
#libkonoha_la_LDFLAGS += -ldl
#endif

AM_CPPFLAGS = -I../include
#if MINGW
#AM_CPPFLAGS += -DKONOHA_ON_MINGW
#endif
libkonoha_la_SOURCES = 
""");

    foreach (String p in System.walk("../src")) {
		OUT << p << EOL;
		if(p.indexOf(".svn") >= 0) continue;
        if(p.endsWith(".c") == false ) continue;
        if(p.endsWith("konoha.c")) continue;

        o.println(%("libkonoha_la_SOURCES += %s{0}",p));
    }

    o.println("libkonoha_la_includedir = $(includedir)");
    o.println("libkonoha_la_include_HEADERS = ../include/konoha.h");

    o.println("libkonoha_la_includekonohadir = $(includedir)/../include/konoha");
    o.println("libkonoha_la_includekonoha_HEADERS =");

    foreach (String p in System.walk("../include/konoha")) {
        if(p.indexOf(".svn") >= 0) continue;
		if(p.indexOf("gen") >= 0) continue;
        if(p.endsWith(".h") == false ) continue;
        if(p.endsWith("konoha.h")) continue;

        o.println(%("libkonoha_la_includekonoha_HEADERS += %s{0}",p));
    }

    o.println("libkonoha_la_includegendir = $(includedir)/../include/konoha/gen");
    o.println("libkonoha_la_includegen_HEADERS =");

    foreach (String p in System.walk("../include/konoha/gen")) {
        if(p.indexOf(".svn") >= 0) continue;
        if(p.endsWith(".h") == false ) continue;

        o.println(%("libkonoha_la_includegen_HEADERS += %s{0}",p));
    }

    o.println("sampledir = /usr/local/konoha/sample");
    o.println("dist_sample_SCRIPTS =");

    foreach (String p in System.walk("../dist/sample")) {
        if(p.indexOf(".svn") >= 0) continue;
        if(p.endsWith(".k") == false ) continue;
        if(p.endsWith("konoha.h")) continue;

        o.println(%("dist_sample_SCRIPTS += %s{0}",p));
    }

    o.println("""
scriptdir = /usr/local/konoha/script
scriptklipdir = /usr/local/konoha/script/klip
dist_scriptklip_SCRIPTS =
dist_scriptklip_SCRIPTS += ../dist/bin/klip""");

    o.println("""
bin_PROGRAMS = konoha
konoha_SOURCES = ../src/konoha.c
konoha_INCLUDES = ../include
konoha_LDADD = libkonoha.la
""");

    o.close();

    return 0;
}
