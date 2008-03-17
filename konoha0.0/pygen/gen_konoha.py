#!/usr/bin/python
import os, os.path, sys
from pygenlib2  import *
from gen_hfile import *
from knhsettings import *


def read_source_cblock(fpath, package, zone, text, data):
	functype = parse_functype(text)
	if functype == None: return
	
	if(data.lastfpath != fpath):
		data.lastfpath = fpath;
		data.package(package).H.append('/* %s */' % fpath)
	data.package(package).H.append(functype + ';')
	
	funcname = parse_funcname(functype)
	data.FUNC_MAP[funcname] = text

	if text.find('/* @map') != -1: MapMap(package, parse_anno(text, '@map'), funcname, data)
	if text.find('/* @method') != -1: Method(package, parse_anno(text, '@method'), functype, data)
###

def read_lineanno(package, line, data):
	if line.find('/* @using') != -1:
		Library(package, parse_anno(line, '@using'), data)
		return line
	if line.find('/* @flag') != -1:
		Flag(package, parse_anno(line, '@flag'), data)
		return line
	if line.find('/* @field') != -1:
		Field(package, parse_anno(line, '@field'), data)
		return line
	if line.find('/* @driver') != -1:
		Driver(package, parse_anno(line, '@driver'), data)
		return line
	if line.find('/* @class') != -1:
		Class(package, parse_anno(line, '@class'), data)
		return line
	return line


def read_source_h(fpath, package, data):
	f = open(fpath)
	if package == None: package = parse_package(fpath)
	for ln in f:
		ln = read_lineanno(package, ln, data)
	f.close()

def read_source_c(fpath, data):
	f = open(fpath)
	package = parse_package(fpath)
	data.add_file(package, fpath)
	# header part
	pp = 0
	cline = None
	for ln in f:
		ln = read_lineanno(package, ln, data)
		if ln.startswith('#endif') and pp == 1:
			break
		if ln.startswith('#ifdef __cplusplus'):
			cline = ''
			pp = 1
			continue
	
	# body part
	zone = '[config]'
	text = ''

	pp = 0
	for ln in f: 
		if ln.startswith('//'): continue
		ln = read_lineanno(package, ln, data)
		if ln.startswith('#endif') and pp == 1: break
		if ln.startswith('#ifdef __cplusplus'): 
			pp = 1
			continue
		
		if ln.startswith('/* ['):
			zone = ln.split()[1]
			continue

		if ln.startswith('/* ===') or ln.startswith('/* ---'):
			if len(text) > 0 :
				read_source_cblock(fpath, package, zone, text, data)
				text = ''
				continue
			
		if ln.startswith("#define _") :
			ln = linetrim(ln.replace('#define _', '#define '))
			if not ln.endswith('\\') :
				data.MACROS.append(ln)
				continue
			p = ln + '\n'	
			for ln in f:
				ln = linetrim(ln)
				p += (ln + '\n')
				if not ln.endswith('\\'): break
			###
			data.MACROS.append(p)
			continue
		if pp == 0: text += ln
	###
	if len(text) > 0 :
		read_source_cblock(fpath, package, zone, text, data)
	f.close()
###

def read_source_k(fpath, data):
	f = open(fpath)
	settings = {}
	exec(f)
	data.settings[data.kpath(fpath)] = settings
###

def read_include_class(dir, data):
	dir = dir + '/include/konoha/class'
	fl = os.listdir(dir)
	for fn in fl:
		if fn.endswith('_.h'): continue
		if fn.endswith('.h'): 
			read_source_h(dir + '/' + fn, fn.replace('.h', ''), data)

def read_source(dir, data):
	fl = os.listdir(dir)
	for fn in fl:
		if fn.startswith('.'): continue
		if fn.startswith('_'): continue
		fpath = dir + '/' + fn
		if os.path.isdir(fpath):
			read_source(fpath, data)
		if dir == data.bdir: continue
		if fn.endswith('.c') :
			if fpath.find('/gen/') == -1: 
				read_source_c(fpath, data)
			else:
				data.add_file("konoha", fpath)
		if fn.endswith('.h') and dir.find('/include/konoha') == -1: 
			read_source_h(fpath, None, data)

def read_manifesto(fname, data):
	f = open(fname)
	key = ''
	for line in f:
		if line.startswith("#"): continue
		if line.startswith("\t"):
			values = line
			data.add_manifesto(key, values)
		elif line.find(':') > 0:
			key, values = line.split(':')
			data.add_manifesto(key, values)
	print data.MANIFESTO
	f.close()

#############

if __name__ == '__main__':
	bdir = '..'
	data = Source(bdir)
	read_manifesto("%s/.build/manifesto" % bdir, data)
	f = open('%s/pygen/SERIAL_NUMBER' % bdir)
	data.serial_number = int(f.readline())
	f.close()
	if len(sys.argv) > 1 and sys.argv[1] == '-c':
		data.serial_number += 1
		f = open('%s/pygen/SERIAL_NUMBER' % bdir, 'w')
		f.write('%d' % data.serial_number)
		f.close()
	read_include_class(bdir, data)
	read_source(bdir, data)
	gen_package_c(bdir, data)
	gen_load_c(bdir, data)
	gen_package_h(bdir, data)
	gen_name_h(bdir, data)
	gen_manifesto_h(bdir, data)
	gen_makefile(bdir, data)

