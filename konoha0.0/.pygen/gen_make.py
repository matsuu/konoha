#!/usr/bin/python
import os, os.path, sys

#########################################################

LDLIBS_MAP = {
	'macosx' : '-lm -lreadline -liconv',
	'unix' : '-lm -lreadline -liconv',
	'mingw' : '-lm -liconv',
	'cygwin': '-lm -lreadline -liconv',
}

def osldlibs(data, OS):
	LDLIBS = '-m'
	if LDLIBS_MAP.has_key(OS):
		LDLIBS = LDLIBS_MAP[OS]
	return LDLIBS

#########################################################

def filebase(cpath):
	return cpath.split('/')[-1].replace('.c', '')

def write_makeobjs(f, data, c_options = ''):
	fbl = []
	for fn in data.CFILES:
		fb = filebase(fn)
		if fb == 'konoha': continue
		fbl.append(fb)
	
	f.write('''
objs = ''')
	for fb in fbl:
		f.write('''\\
\t%s''' % (fb + '.o'))

	for fn in data.CFILES:
		fb = filebase(fn) + '.o'
		f.write('''

%s : ../%s ../include/konoha/gen/konoha_class_.h
	$(CC) $(CFLAGS) %s -I"../include" -o%s -c "../%s" 
''' % (fb, fn, c_options, fb, fn))


def write_dll(f, data, CC, CFLAGS, OS):
	PROG = 'konoha'
	DLL = 'libkonoha.so'
	if OS == 'macosx':
		DLL = DLL.replace('.so', '.dylib')
	if OS == 'mingw' or OS == 'cygwin' or OS == 'windows':
		PROG += '.exe'
		DLL = DLL.replace('.so', '.dll')

	f.write('''#Makefiile by gen_konoha.py
CC = %s
CFLAGS = %s
LDLIBS = %s

program = %s
library = %s

.PHONY: all
all: $(program) 

''' % (CC, CFLAGS, osldlibs(data, OS), PROG, DLL))

	write_makeobjs(f, data)

	LDLIBS = ''
	for l in data.OPTIONS:
		if l.startswith("-l"): LDLIBS += " " + l

	f.write('''
$(program): $(library) konoha.o
	$(CC) -o $(program) konoha.o -L"." -lkonoha
''') 
	
	if DLL.endswith('.dylib'):
		f.write('''
$(library) : $(objs)
	$(CC) -dynamiclib -o $(library) -L"./lib" -L"./libexec" $(objs) $(LDLIBS) %s
''' % (LDLIBS))
	elif DLL.endswith('.dll'):
		f.write('''
$(library) : $(objs)
	$(CC) -shared -Wl -o $(library) -L"./lib" -L"./libexec" $(objs) $(LDLIBS) %s
''' % (LDLIBS))
	else:
		f.write('''
$(library) : $(objs)
	$(CC) -shared -Wl,-soname,libkonoha.so -o $(library) -L"./lib" -L"./libexec" $(objs) $(LDLIBS) %s
''' % (LDLIBS))

def add_package(bdir, data):
	dir = bdir + '/package'
	fl = os.listdir(dir)
	for fn in fl:
		fpath =  dir + '/' + fn
		if not os.path.isdir(fpath): continue
		fl2 = os.listdir(fpath)
		for fn2 in fl2:
			if fn2.endswith('.c'):
				data.CFILES.append('package/' + fn + '/' + fn2)


def write_mono(f, data, CC, CFLAGS, OS):
	PROG = 'konoha'
	if OS == 'mingw' or OS == 'cygwin' or OS == 'windows':
		PROG += '.exe'
	
	f.write('''#Makefiile by gen_konoha.py
CC = %s
CFLAGS = %s
LDLIBS = %s

program = %s
library =

.PHONY: all
all: $(program)

''' % (CC, CFLAGS, osldlibs(data,OS), PROG))
	
	write_makeobjs(f, data)
	
	LDLIBS = ''
	for l in data.OPTIONS:
		if l.startswith("-l"): LDLIBS += " " + l
	
	f.write('''
$(program): $(objs) konoha.o
	$(CC) -o $(program) $^ -L"./lib" -L"./libexec" $(LDLIBS) %s
	strip $(program)
''' % (LDLIBS))

def gen_makefile(bdir, data):
	f = open(bdir + '/build/makefile', 'w')
	CC = "gcc"
	CFLAGS = '-O2 -Wall -fmessage-length=0 -fPIC'
	OS = 'unix'
	
	for l in data.OPTIONS:
		if l.startswith("-O"): 
			CFLAGS = CFLAGS.replace('-O2', l)
		elif l.startswith("CC="):
			CC = l.replace("CC=", "")
		elif l == '-g':
			CFLAGS += ' -g -DKNH_DBGMODE'
		elif l.startswith('-mtune') or l.startswith('-mcpu'):
			CFLAGS += ' %s' % l
		elif l == 'macosx':
			OS = 'macosx'
			CFLAGS = CFLAGS.replace(" -fPIC", "")
			CFLAGS += ' -DKONOHA_OS__MACOSX'
		elif l == 'mingw':
			OS = 'mingw'
			CFLAGS = CFLAGS.replace(" -fPIC", "")
			CFLAGS += ' -DKONOHA_OS__MINGW'
		elif l == 'cygwin':
			OS = 'cygwin'
			CFLAGS = CFLAGS.replace(" -fPIC", "")
			CFLAGS += ' -DKONOHA_OS__CYGWIN'

	if '-mono' in data.OPTIONS:
		CFLAGS = CFLAGS.replace(" -fPIC", "")
		CFLAGS += ' -DKONOHA_MONOLITHIC'
		add_package(bdir, data)
		write_mono(f, data, CC, CFLAGS, OS)
	else:
		write_dll(f, data, CC, CFLAGS, OS)
		
	f.write('''
.PHONY: clean
clean:
	$(RM) -rf $(objs) $(program) $(library) konoha.o 

''')
	f.close()

def gen_automake(dir):
    return 

def gen_automake2(dir):
	fl = os.listdir(dir)
	clist = []
	for fn in fl:
		if fn.startswith('.'): continue
		if fn.startswith('_'): continue
		fpath = dir + '/' + fn
		if os.path.isdir(fpath):
			gen_automake(fpath)
		if fn.endswith('.c') :
			clist.append(fn)
	
	if len(clist) == 0: return
	
	f = open(dir+'/Makefile.am', 'w')
	f.write('''### Process this file with automake to generate Makefile.in
''')
	lname = 'lib'+ dir.replace('../', '').replace('/','')
	f.write('''
libkonoha_la_SOURCES +=''')
	for fn in clist:
		f.write('''  %s \\
''' % fn)
	f.close()


#############

if __name__ == '__main__':
	bdir = '..'
	from source import *
	data = read_data(bdir)
	gen_makefile(bdir, data)
	gen_automake(bdir)
