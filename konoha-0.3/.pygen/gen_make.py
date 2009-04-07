#!/usr/bin/python
import os, os.path, sys

#########################################################

LDLIBS_MAP = {
	'macosx' : '-lm -lreadline -liconv',
	'unix' : '-lm -lreadline -liconv',
	'mingw' : 'lib/iconv.a -lm',
	'cygwin': '-lm -lreadline -liconv',
}


HASMAKERULES = ''

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
%s	$(CC) $(CFLAGS) %s -I"../include" -o%s -c "../%s" 
''' % (fb, fn, HASMAKERULES, c_options, fb, fn))


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

	LDLIBS = ''
	for l in data.OPTIONS:
		if l.startswith("-l"): LDLIBS += " " + l

	if OS == 'windows':
		write_nmakeobjs(f, data)
		f.write('''
$(program): $(library) konoha.obj
	$(CC) -o $(program) konoha.obj -L"." -lkonoha
''') 
	else:
		write_makeobjs(f, data)
		f.write('''
$(program): $(library) konoha.o
	$(CC) -o $(program) konoha.o -L"." -lkonoha
''') 
	
	if DLL.endswith('.dylib'):
		f.write('''
$(library) : $(objs)
	$(CC) -dynamiclib -o $(library) -L"./lib" -L"." $(objs) $(LDLIBS) %s
''' % (LDLIBS))
	elif DLL.endswith('.dll'):
		if OS == 'windows':
			f.write('''
$(library) : $(objs)
	$(CC) -shared -Wl -o $(library) -L"./lib" -L"." $(objs) $(LDLIBS) %s
''' % (LDLIBS))
		else:
			f.write('''
$(library) : $(objs)
	$(CC) -shared -Wl -o $(library) -L"./lib" -L"." $(objs) $(LDLIBS) %s
''' % (LDLIBS))
	else:
		f.write('''
$(library) : $(objs)
	$(CC) -shared -Wl,-soname,libkonoha.so -o $(library) -L"./lib" -L"." $(objs) $(LDLIBS) %s
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
	if OS == 'tb':
		EXTRA = '''
include ../../etc/makerules
VPATH = "./ $(shell find ../ -type d) ./"
'''
		global HASMAKERULES
		HASMAKERULES = '#'
	else:
		EXTRA = ''

	f.write('''#Makefiile by gen_konoha.py
%sCC = %s
%s
CFLAGS += %s
%sLDLIBS = %s

program = %s
library =

.PHONY: all
all: $(program)

''' % (HASMAKERULES, CC, EXTRA, CFLAGS, HASMAKERULES, osldlibs(data,OS), PROG))
	
	write_makeobjs(f, data)
	
	LDLIBS = ''
	for l in data.OPTIONS:
		if l.startswith("-l"): LDLIBS += " " + l
	
	f.write('''
$(program): $(objs) konoha.o
%s	$(CC) -o $(program) $^ -L"./lib" -L"./libexec" $(LDLIBS) %s
%s	strip $(program)
''' % (HASMAKERULES, LDLIBS, HASMAKERULES))

### nmake ##################################################################

def write_nmakeobjs(f, data, c_options = ''):
	fbl = []
	for fn in data.CFILES:
		fb = filebase(fn)
		if fb == 'konoha': continue
		fbl.append(fb)
	
	f.write('''
LINK32DLL_OBJS = ''')
	for fb in fbl:
		f.write('''\\
\t$(OUTDIR)\\%s''' % (fb + '.obj'))

	for fn in data.CFILES:
		fb = filebase(fn) + '.obj'
		f.write('''

$(OUTDIR)\\%s : "..\\%s" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\\%s" "..\\%s" 
''' % (fb, fn.replace('/', '\\'), fb, fn.replace('/', '\\')))

def write_nmake(f, data, CC, CFLAGS, OS):
	f.write('''#Makefiile by gen_konoha.py
KONOHA=konoha
OUTDIR=.
LINK32=link.exe
DISTDIR="\\Konoha"
BINDIR="\\Konoha\\bin"

ALL : $(OUTDIR)\\$(KONOHA).dll $(OUTDIR)\\$(KONOHA).exe

CLEAN :
	-@erase /Q $(OUTDIR)\\*.OBJ

$(OUTDIR) :
	if not exist $(OUTDIR)/$(NULL) mkdir $(OUTDIR)

$(DISTDIR) :
	if not exist $(DISTDIR)/$(NULL) mkdir $(DISTDIR)

INSTALL : $(DISTDIR)
	-@erace /Q $(DISTDIR)\\*
	if not exist $(DISTDIR)\\bin\\$(NULL) mkdir $(DISTDIR)\\bin
	if not exist $(DISTDIR)\\lib\\$(NULL) mkdir $(DISTDIR)\\lib
	if not exist $(DISTDIR)\\package\\$(NULL) mkdir $(DISTDIR)\\package
	copy "$(OUTDIR)\\konoha.exe" "$(DISTDIR)\\bin\\konoha.exe"
	copy "$(OUTDIR)\\konoha.dll" "$(DISTDIR)\\bin\\konoha.dll"
	copy "$(OUTDIR)\\ext\\*.dll" "$(DISTDIR)\\bin\\"
	copy "$(OUTDIR)\\konoha.lib" "$(DISTDIR)\\lib\\konoha.lib"
	copy "$(OUTDIR)\\ext\\iconv.lib" "$(DISTDIR)\\lib\\iconv.lib"
	if not exist $(DISTDIR)\\package\\math mkdir $(DISTDIR)\\package\\math
	if exist $(OUTDIR)\\libknhmath.dll copy $(OUTDIR)\\libknhmath.dll $(DISTDIR)\\package\\math\\libknhmath.dll
	
CFLAGS=\\
	/nologo\\
	/c /TP /O2 /GL /W3\\
	/DKNH_USING_ICONV\\
	/I"..\\include" /I".\\include"

CFLAGSD=\\
	/nologo\\
	/c /O2 /W3 /MD\\
	/Fd"$(OUTDIR)\\$(KONOHA).pdb"\\
	/TP\\
	/Zi\\
	/D_WINDOWS /DLIBICONV_PLUG /DKNH_USING_ICONV\\
	/I"..\\include" /I".\\include"

LINK32DLL_FLAGS=\\
 /nologo /dll /LTCG /incremental:no /DEFAULTLIB:"ext\\iconv.lib"\\
 /pdb:"$(OUTDIR)\\$(KONOHA).pdb" /machine:I386 /out:"$(OUTDIR)\\$(KONOHA).dll"\\
 /implib:"$(OUTDIR)\\$(KONOHA).lib"

LINK32_FLAGS=konoha.lib\\
 /nologo /LTCG /subsystem:console /incremental:no\\
 /out:"$(OUTDIR)\\$(KONOHA).exe"

''')
	
	write_nmakeobjs(f, data)
	
	f.write('''

$(OUTDIR)\\$(KONOHA).dll : $(OUTDIR) $(LINK32DLL_OBJS)
	$(LINK32) $(LINK32DLL_FLAGS)  "$(OUTDIR)\\ext\\iconv.lib" $(LINK32DLL_OBJS)

$(OUTDIR)\\$(KONOHA).exe : $(OUTDIR) $(OUTDIR)\\$(KONOHA).dll "$(OUTDIR)\\konoha.obj"
	$(LINK32) $(LINK32_FLAGS) "$(OUTDIR)\\$(KONOHA).lib" "$(OUTDIR)\\$(KONOHA).obj"

''') 

	f.write('''

LINK32DLL_MATHFLAGS=\\
 /nologo /dll /LTCG /incremental:no\\
 /pdb:"$(OUTDIR)\\$(KONOHA).pdb" /machine:I386 /out:"$(OUTDIR)\\libknhmath.dll"\\
 /implib:"$(OUTDIR)\\libknhmath.lib"

$(OUTDIR)\\knh_Math.obj : "..\\package\\math\\knh_Math.c" 
	cl $(CFLAGS) /Fo"$(OUTDIR)\\knh_Math.obj" "..\\package\\math\\knh_Math.c" 

$(OUTDIR)\\libknhmath.dll : $(OUTDIR)\\knh_Math.obj
	$(LINK32) $(LINK32DLL_MATHFLAGS) $(OUTDIR)\\konoha.lib $(OUTDIR)\\knh_Math.obj

PACKAGE : $(OUTDIR)\\libknhmath.dll
	
''')

def convert_BOM(bdir):
	f = open(bdir + '/src/gen/konoha_message_.c')
	data = f.read()
	f.close()
	f = open(bdir + '/src/gen/konoha_message_.c', 'w')
	f.write('%c%c%c' % (0xef, 0xbb, 0xbf))
	f.write(data)
	f.close()

def gen_makefile(bdir, data):
	if 'tb' in data.OPTIONS:
		f = open(bdir + '/tbmx1/makefile', 'w')
	elif 'mingw' in data.OPTIONS:
		f = open(bdir + '/mingw/makefile', 'w')
	elif 'windows' in data.OPTIONS:
		f = open(bdir + '/windows/makefile', 'w')
	else:
		f = open(bdir + '/build/Makefile', 'w')
	
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
			CFLAGS = CFLAGS.replace(" -fPIC", '')
			CFLAGS += ' -I"include" -DKONOHA_OS__MINGW'
		elif l == 'cygwin':
			OS = 'cygwin'
			CFLAGS = CFLAGS.replace(" -fPIC", "")
			CFLAGS += ' -DKONOHA_OS__CYGWIN'
		elif l == 'windows':
			OS = 'windows'
			CFLAGS = '/O2'
			convert_BOM(bdir)
		elif l == 'tb':
			OS = 'tb'
			HASMAKERULES = '#'
			CFLAGS += ' -I/usr/local/te/include -I"../include" -DKONOHA_OS__TB'
			data.OPTIONS.append("-mono")
	
	if '-liconv' in data.OPTIONS:
		CFLAGS += ' -DKNH_USING_ICONV'

	if '-mono' in data.OPTIONS :
		CFLAGS = CFLAGS.replace(" -fPIC", "")
		CFLAGS += ' -DKONOHA_MONOLITHIC'
		add_package(bdir, data)
		write_mono(f, data, CC, CFLAGS, OS)
	elif OS == 'windows':
		write_nmake(f, data, 'cl', CFLAGS, OS)
		f.close()
		return
	else:
		write_dll(f, data, CC, CFLAGS, OS)
		
	f.write('''

.PHONY: dist
dist:
	$(RM) -rf $(objs) konoha.o

.PHONY: clean
clean:
	$(RM) -rf $(objs) $(program) $(library) konoha.o 

''')
	f.close()

#############

if __name__ == '__main__':
	bdir = '..'
	from source import *
	data = read_data(bdir)
	gen_makefile(bdir, data)
