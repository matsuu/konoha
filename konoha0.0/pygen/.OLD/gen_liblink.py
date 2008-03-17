#!/usr/bin/python
import os, os.path, sys
from pygenlib  import *

bdir = '..'

def write_liblink_h(f, settings):
	libname  = getdict(settings, 'libname', None)
	funclist = getdict(settings, 'funclist', []) 

	write_ifdef(f, 'KONOHA_USING_%s' % libname)

	for ft in funclist:
		fn = parse_funcname(ft)
		f.write('''
typedef %s;''' % (ft.replace(fn, '(*f_lib_%s)' % fn)))

	write_line(f)

	f.write('''
#ifndef KNH_UNEXPORTED''')
	for ft in funclist:
		fn = parse_funcname(ft)
		f.write('''
extern f_lib_%s lib_%s;''' % (fn, fn))
	f.write('''
#endif/*KNH_UNEXPORTED*/''')

	write_line(f)

	f.write('''
knh_bool_t konoha_using_%s(void);
''' % libname)

	write_endif(f, 'KONOHA_USING_%s' % libname)

def write_liblink_c(f, settings):
	libname  = getdict(settings, 'libname', None)
	funclist = getdict(settings, 'funclist', []) 
	fname = []
	for fn in funclist:
		fname.append(parse_funcname(fn))


	f.write('''
#ifdef __cplusplus
}
#endif

#define KONOHA_UNEXPORTED
#include<konoha/lib/%s.h>

#ifdef __cplusplus 
extern "C" {
#endif

''' % libname)

	write_ifdef(f, 'KONOHA_USING_%s' % libname)
	write_ifdef(f, 'KONOHA_PRELINK_%s' % libname)
	f.write('''
//static int konohab_%s = 1;
//static int konohab_%s_loaded = 1;''' % (libname, libname))
	for fn in fname:
		f.write('''
f_lib_%s lib_%s = %s;''' % (fn, fn, fn))
	write_line(f)
	f.write('''
knh_bool_t konoha_using_%s(void)
{
	return 1;
}
''' % libname)
	write_else(f, 'KONOHA_PRELINK_%s' % libname)
	f.write('''
void *knh_system_loadFunc(Ctx*, char*, char*, char*, void*);

static int konohab_%s = 0;
static int konohab_%s_loaded = 0;''' % (libname, libname))
	for fn in fname:
		f.write('''
f_lib_%s lib_%s = NULL;''' % (fn, fn))

	write_line(f)
	
	f.write('''
#ifndef F_PREFIX
#define F_PREFIX  ""
#endif

#ifndef F_POSTFIX
#define F_POSTFIX  ""
#endif

knh_bool_t konoha_using_%s(void)
{
	if(konohab_%s_loaded) return konohab_%s;
	konohab_%s_loaded = 1;''' % (libname, libname, libname, libname))
	for fn in fname:
		f.write('''
	lib_%s = knh_system_loadFunc(NULL, NULL, "%s", F_PREFIX "%s" F_POSTFIX, NULL);
	if(lib_%s == NULL) {
		return 0;
	}''' % (fn, libname, fn, fn))
	
	f.write('''
	konohab_%s = 1;
	return 1;
}
''' % libname)

	write_endif(f, 'KONOHA_PRELINK_%s' % libname)

	write_else(f, 'KONOHA_USING_%s' % libname)

	f.write('''
knh_bool_t konoha_using_%s(void)
{
	return 0;
}
''' % libname)

	write_endif(f, 'KONOHA_USING_%s' % libname)

def make_liblink(bdir, settings):
	libname  = getdict(settings, 'libname', None)
	if libname is None : return 
	print 'generating ..', libname
	fname = '%s/include/konoha/lib/%s.h' % (bdir, libname)
	f = open_h2(fname, ['<konoha/konoha_t.h>'])

	f.write('''
#ifdef KONOHA_USING_%s''' % libname.upper())
	for i in getdict(settings, 'include', []):
		f.write('''
	#include%s''' % i)
	f.write('''
#endif
''')
	write_begin_c(f)
	write_dline(f)
	write_liblink_h(f, settings)
	close_h(f, fname)
	
	fname = '%s/gen/lib/%s_.c' % (bdir, libname)
	f = open_c(fname, ['<konoha/konoha_t.h>'])
	write_liblink_c(f, settings)
	close_c(f, fname)

if __name__ == '__main__':
	for path in sys.argv[1:]:
		settings = read_settings(path)
		make_liblink(bdir, settings)
