#!/usr/bin/python
import os, os.path, sys
#from template import *
#from pygenlib  import *

CC='gcc'
CFLAGS='-O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP'

bdir = '..'


def add_clists(dir, fn, clists):
	cpath = dir + '/' + fn
	if cpath.startswith('../'):
		cpath = cpath.replace('../', '')
	oname = cpath.split('/')[-1].replace('.c', '.o')
	clists.append((cpath, oname))

def find_c(dir, clists):
	fl = os.listdir(dir)
	for fn in fl:
		if fn.startswith('.'): continue
		if fn.startswith('_'): continue
		if fn.endswith('.c'): 
			add_clists(dir, fn, clists)
		if os.path.isdir(dir + '/' + fn):
			find_c(dir + '/' + fn, clists)

############################################################################

def read_dllibs(bdir, clists):
	for cf in clists:
		f = open('../%s' % cf[0])
		for ln in f:
			loc = ln.find('@LD')
			if loc > 0:
				dllibs = ln[loc+3:].replace('*/', '').replace('\n', '').replace('\r', '')
				f.close()
				return dllibs
		f.close()
	return '-lnotfound'

osname = os.uname()[0].lower()

pkgobjs = ''
pkglist = ''
pkgcc = []

############################################################################

def gen_package(f, bdir):
	global pkglist, pkgobjs
	pdir = '%s/package' % bdir
	dl = os.listdir(pdir)
	for dn in dl:
		if dn.startswith('_'): continue
		pkgso = dn
		clists = []
		find_c(pdir, clists)
		dllibs = read_dllibs(bdir, clists)
		objs = ''
		for cf in clists:
			objs += '%s ' % cf[1]
		pkgobjs += objs		
		if osname == 'darwin':
			pkglist += 'lib%s.dylib ' % pkgso
			pkgcc.append('''
lib%s.dylib : %s
	$(CC) -dynamiclib -o lib%s.dylib -L"./lib" %s%s -lkonoha
	mkdir -p package/%s
	cp lib%s.dylib package/%s
''' % (pkgso, objs, pkgso, objs, dllibs, pkgso, pkgso, pkgso))
		else:
			pkglist += 'lib%s.so ' % pkgso
			pkgcc.append('''
lib%s.so : %s
	$(CC) -shared -Wl,-soname,lib%s.so -o lib%s.so %s%s
	mkdir -p package/%s
	cp lib%s.so package/%s
''' % (pkgso, objs, pkgso, pkgso, objs, dllibs, pkgso, pkgso, pkgso))
		
############################################################################

def gen_make(f, bdir):
	clists = []
	find_c(bdir, clists)
	objs = ''
	for cf in clists:
		if not cf[0].startswith('package/'):
			objs += '%s ' % cf[1]

	f.write('''# makefile for konoha

CC = gcc
CFLAGS = -g -Wall -O2
#LDLIBS = -lm -ldl

program = konoha
objs = %s
packages = %s
pkgobjs = %s

.PHONY: all
all: $(program) $(packages)

$(program): $(objs)
	$(CC) -dynamiclib -o libkonoha.dylib $^ $(LDLIBS)
	$(CC) -o $(program) $^ $(LDLIBS)
	mkdir -p bin
	mkdir -p lib
	cp $(program) bin
	cp libkonoha.dylib lib

.PHONY: clean
clean:
	$(RM) $(program) $(objs) $(packages) $(pkgobjs)

''' % (objs, pkglist, pkgobjs))

	for cf in clists:
		if cf[0].startswith('package/')  :
			f.write('''
%s : ../%s
	$(CC) -fPIC $(CFLAGS) -fno-common -DKONOHA_PACKAGE -I"../include" -c "../%s"
''' % (cf[1], cf[0], cf[0]))
		else: 			
			f.write('''
%s : ../%s
	$(CC) $(CFLAGS) -fno-common -I"../include" -c "../%s"
''' % (cf[1], cf[0], cf[0]))

	for cc in pkgcc:
		f.write(cc)
	
############################################################################

f = open('makefile', 'w')
gen_package(f, '..')
gen_make(f, '..')
f.close()
