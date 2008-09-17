#!/usr/bin/python
import os, sys
from pygenlib2  import *
from knhsettings import *

#########################################################

def filebase(cpath):
	return cpath.split('/')[-1].replace('.c', '')

def EXTOBJ(data):
	if data.TARGET == 'windows': return '.obj'
	return '.o'

def EXTEXE(data):
	if data.TARGET == 'windows' or data.TARGET =='cygwin' : return '.exe'
	if data.TARGET == 'mingw': return '.exe'
	return ''

def EXTDLL(data):
	if data.TARGET == 'macos': return '.dylib'
	if data.TARGET == 'windows': return '.obj'
	return '.so'

def write_MONO(f, data):
	for p in data.PACKAGE_LIST:
		p = data.package(p)
		for fn in p.CFILES:
			l.append(filebase(fn))
			p.make_libs(u, data)

	f.write('''

LDLIBS = ''')
	for t in u + CC_LIBS(data):
		f.write('''\\
\t%s''' % (t))

	f.write('''
objs = ''')
	for fb in l:
		f.write('''\\
\t%s''' % (fb + EXTOBJ(data)))

	for fn in l:
		fb = filebase(fn) + EXTOBJ(data)
		f.write('''

%s : ../%s ../include/konoha/gen/manifesto.h
\t$(CC) $(CFLAGS) -I"../include" -c "../%s" -o%s
''' % (fb, fn, fn, fb))
	
	ext = EXTEXE(data)
	f.write('''

konoha.o: ../konoha/konoha.c ../include/konoha/gen/manifesto.h
\t$(CC) $(CFLAGS) -I"../include" -c "../konoha/konoha.c" -okonoha.o


.PHONY: $(program)
$(program): konoha%s $(objs)
\t$(CC) -o $(program) $^ -L"./lib" $(LDLIBS)
\tstrip $(program)
\tmkdir -p bin
\tmv $(program) bin

''' % (EXTOBJ(data))

def write_LIB__each(f, p, data):
	l = []
	for fn in p.CFILES:
		l.append(filebase(fn))
	
	u = []
	p.make_libs(u, data)
	if(p.pname == 'konoha')
		u = u + CC_LIBS(data)

	f.write('''
LDLIBS_%s = ''' % p.pname)
	for t in u:
		f.write('''\\
\t%s''' % (t))
		
	f.write('''

OBJ_%s = ''' % p.pname)
	for fb in l:
		f.write('''\\
\t%s''' % (fb + EXTOBJ(data)))
	
	for fn in p.CFILES:
		fb = filebase(fn) + EXTOBJ(DLL)
		f.write('''

%s : ../%s ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS) -I"../include" -c "../%s" -o%s
''' % (fb, fn, fn, fb))

def write_OLD(f, p, data):
		if p.isDriver:
			f.write('''

drv_%s.dylib : $(objs_%sL)
	$(CC) -dynamiclib -o drv_%s.dylib -L"./lib" -L"./libexec" $(objs_%sL) $(LDLIBS_%sL) -lkonoha
	mkdir -p driver
	mv drv_%s.dylib driver/

drv_%s.so : $(objs_%sL)
	$(CC) -shared -Wl,-soname,drv_%s.so -o drv_%s.so -L"./lib" -L"./libexec" $(objs_%sL) $(LDLIBS_%sL) -lkonoha
	mkdir -p driver
	mv drv_%s.so driver/

drv_%s.dll : $(objs_%sL)
	$(CC) -shared -Wl -o drv_%s.dll -L"./lib" -L"./libexec" $(objs_%sL) $(LDLIBS_%sL) -lkonoha
	mkdir -p driver
	mv drv_%s.dll driver/

'''.replace('%s', p.pname));
		elif p.isLoadable:
			f.write('''

pkg_%s.dylib : $(objs_%sL)
	$(CC) -dynamiclib -o pkg_%s.dylib -L"./lib" -L"./libexec" $(objs_%sL) $(LDLIBS_%sL) -lkonoha
	mkdir -p package/%s
	mv pkg_%s.dylib package/%s

pkg_%s.so : $(objs_%sL)
	$(CC) -shared -Wl,-soname,drv_%s.so -o pkg_%s.so -L"./lib" -L"./libexec" $(objs_%sL) $(LDLIBS_%sL) -lkonoha
	mkdir -p package/%s
	mv pkg_%s.so package/%s

pkg_%s.dll : $(objs_%sL)
	$(CC) -shared -Wl -o pkg_%s.dll -L"./lib" -L"./libexec" $(objs_%sL) $(LDLIBS_%sL) -lkonoha
	mkdir -p package/%s
	mv pkg_%s.dll package/%s

'''.replace("%s", p.pname))

def CC_isMONO(data):
	for a in data.OPTIONS:
		if a == '-mono' : return True
	return False

def CC_CFLAGS(data):
	cflag = '-O2 -Wall -g -fno-common -fPIC' 
	for a in data.OPTIONS:
		if a == '-debug': cflag = cflag.replace('-O2', '-O0').replace('-g', '-g3 -fmessage-length=0 -DKNH_DBGMODE')
		if a == '-fast':  cflag = cflag.replace('-O2', '-O3 -DKNH_FASTMODE')
		if a == '-mono':  cflag = cflag.replace('-fPIC', '-DKNH_MONOLITHIC')
	return cflag

def gen_makefile(bdir, data):
	f = open(bdir + '/build/makefile', 'w')
	f.write('''#Makefiile by gen_konoha.py for %s

CC = gcc
CFLAGS = %s

program = konoha%s

.PHONY: all
all: $(program)

''' % (data.TARGET, CC_CFLAGS(data), EXTEXE(data))

	if CC_isMONO(data) :
		write_MONO(f, data)
	else:
		write_LIB(f, data)

	write_makefile_objs(f, data)

	for p in data.PACKAGE_LIST:
		p = data.package(p)
		write_makefile_cc(f, p, data)

	f.write('''

konohaM.o: ../konoha.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../konoha.c" -okonohaM.o

konohaD.o: ../konoha.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../konoha.c" -okonohaD.o

konohaL.o: ../konoha.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -I"../include" -c "../konoha.c" -okonohaL.o

.PHONY: $(program)
$(program): konohaM.o $(objs_M)
	$(CC) -o $(program) $^ -L"./lib" $(LDLIBS_M) $(LDLIBS)
	strip $(program)
	mkdir -p bin
	mv $(program) bin

.PHONY: $(program).exe
$(program).exe: konohaM.o $(objs_M)
	$(CC) -o $(program).exe $^ -L"./lib" $(LDLIBS_M) $(LDLIBS)
	strip $(program).exe
	mkdir -p bin
	mv $(program).exe bin

.PHONY: safe_$(program)
safe_$(program): konohaD.o $(objs_D)
	$(CC) -o safe_$(program) $^ -L"./lib" $(LDLIBS_M) $(LDLIBS)
	mkdir -p bin
	mv safe_$(program) bin

.PHONY: safe_$(program).exe
safe_$(program).exe: konohaD.o $(objs_D)
	$(CC) -o safe_$(program).exe $^ -L"./lib" $(LDLIBS_M) $(LDLIBS)
	mkdir -p bin
	mv safe_$(program).exe bin

.PHONY: lib$(program).dylib
lib$(program).dylib: konohaL.o $(objs_L)
	$(CC) -dynamiclib -o libkonoha.dylib $^ -L"./lib" $(LDLIBS_L) $(LDLIBS)
	mkdir -p libexec
	mv libkonoha.dylib libexec
	$(CC) -o $(program) konohaL.o -L"./libexec" -lkonoha
	mv $(program) libexec

.PHONY: lib$(program).so
lib$(program).so: konohaL.o $(objs_L)
	$(CC) -shared -Wl,-soname,libkonoha.so -o libkonoha.so $^ -L"./lib" $(LDLIBS_L) $(LDLIBS)
	mkdir -p libexec
	mv libkonoha.so libexec
	$(CC) -o $(program) konohaL.o -L"./libexec" -lkonoha
	mv $(program) libexec

.PHONY: lib$(program).dll
lib$(program).dll: konohaL.o $(objs_L)
	$(CC) -shared -Wl,--output-def,libkonoha.def,--out-implib,libkonohadll.a -o libkonoha.dll $^ -L"./lib" $(LDLIBS_L) $(LDLIBS)
	mkdir -p libexec
	mv libkonoha.dll libexec
	$(CC) -o $(program) konohaL.o -L"./libexec" -lkonoha
	mv $(program) libexec

.PHONY: lib$(program)
lib$(program): 
	echo "choose one: dylib, so, cll"

.PHONY: dylib
dylib: lib$(program).dylib $(packages_dylib)

.PHONY: so
so: lib$(program).so $(packages_so)

.PHONY: dll
dll: lib$(program).dll $(packages_dll)

.PHONY: clean
clean:
	$(RM) -rf bin libexec package driver $(objs_M) $(objs_L) $(objs_D) *.o 

''')
	
	f.close()
	
