#!/usr/bin/python
import os, sys
from pygenlib  import *
from CLASS import *
from CFILE import *


API_LEVEL = 2

# ---------------------------------------------------------------------------

def gen_class_h(bdir):
	fname = '%s/include/konoha/konoha_class_.h' % bdir
	f = open_h(fname, ['<konoha/konoha_config.h>', '<konoha/konoha_t.h>'])
	
	write_define(f, 'KONOHA_SERIAL_NUMBER', '%d' % get_serial_number())
	
	sn = 1
	for cname in TSTRUCT[1:]:
		c = CLASSTBL[cname]
		if c.isUNUSE():
			c.write_define(f, 0)
		else:
			c.write_define(f, sn)
			sn += 1
		################	
		write_line(f)
	
	write_dline(f)

	cn = 0
	for cname in TCLASS:
		c = CLASSTBL[cname]
		if c.isUNUSE():
			c.write_define(f, 0)
		else:
			c.write_define(f, cn)
			cn += 1
		################	
		write_line(f)

	write_dline(f)
	write_comment(f, "@STRUCT/CLASS %d %d" % (sn, cn))
	write_dline(f)
	
	write_TFIELDN(f)

	close_h(f, fname)

def gen_alias_h(bdir):
	fname = '%s/include/konoha/konoha_alias_.h' % bdir
	f = open_h(fname, ['<konoha/konoha_config.h>'])
	
	for cname in TSTRUCT[1:]:
#		c = CLASSTBL[cname]
		lname = alias_lname(cname)
		f.write('''
#ifndef  UNALIAS_%s
''' % (lname))
		write_define(f, lname, cname, 40)
		write_define(f, '%sNULL' % lname, cname, 40)
		f.write('''#endif/*UNALIAS_%s*/
''' % (lname))

	for cname in TCLASS:
#		c = CLASSTBL[cname]
		lname = alias_lname(cname)
		f.write('''
#ifndef  UNALIAS_%s
''' % (lname))
		write_define(f, lname, cname, 40)
		write_define(f, '%sNULL' % lname, cname, 40)
		f.write('''#endif/*UNALIAS_%s*/
''' % (lname))

	write_dline(f)
	close_h(f, fname)


# ---------------------------------------------------------------------------
def gen_class(bdir):
	PM = {}
	for cname in TCLASSALL:
		c = CLASSTBL[cname]
		pkgn = c.pkgn
		if not PM.has_key(pkgn):
			PM[pkgn] = []
		PM[pkgn].append(c)
					
	for pkgn in PM.keys():
		gen = FileGen(bdir, 'class/%s' % pkgn)
		
		for c in PM[pkgn]:
			c.write_typedef(gen.fh)
			write_line(gen.fh)
		write_dline(gen.fh)

		for c in PM[pkgn]:
			c.write_prototype(gen.fh)
			c.write_CAST(gen.fc)
			c.write_flag(gen)
			write_line(gen.fh)
		
		read_CFILE(gen, '%s/class/%s' % (bdir, pkgn))
		read_CFILE(gen, '%s/api/%s' % (bdir, pkgn), API_LEVEL)
		#read_CFILE(gen, '%s/gen/class/%s' % (bdir, pkgn))
		if pkgn == 'konoha': 
			read_CFILE(gen, '%s/class/konoha/vm' % bdir)
		gen.close()
	#

# ---------------------------------------------------------------------------

def gen_class_c(bdir):
	fname = '%s/gen/konoha_class_.c' % bdir
	f = open_c(fname, ['<konoha/konoha_dev.h>'])
	write_init_struct(f)
	write_init_class(f)
	close_c(f, fname)

# ---------------------------------------------------------------------------

bdir = '..'
read_PACKAGETBL(bdir)

gen_class(bdir)
gen_class_h(bdir)
gen_alias_h(bdir)
gen_class_c(bdir)
