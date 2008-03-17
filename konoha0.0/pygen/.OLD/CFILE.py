#!/usr/bin/python
import os, sys
from pygenlib  import *
from CLASS import *

#------------------------------------------------------------------------------------


class FileGen:
	def __init__(self, bdir, pkgn):
		self.fhname = '%s/include/konoha/%s_.h' % (bdir, pkgn)
		self.fcname = '%s/gen/%s_.c' % (bdir, pkgn)
		self.fh = open_h(self.fhname, ['<konoha/konoha_t.h>', '<konoha/%s.h>' % pkgn])
		self.fc = open_c(self.fcname, ['<konoha/konoha_dev.h>'])

	def close(self):
		close_h(self.fh, self.fhname)
		close_c(self.fc, self.fcname)

#------------------------------------------------------------------------------------

class CFile:
	def __init__(self, dirname, filename):
		self.dirname = dirname
		self.filename = filename
		self.cline = None
		self.zone_map = {}
		self.zone_order = []
		self.defines = None
		
	def pathname(self):
		if self.dirname is None or self.dirname == '':
			return self.filename
		else:
			return '%s/%s' % (self.dirname, self.filename)

	def read_file(self, f, gen = None):
		#print 'reading %s ..' % self.filename
		pp = 0
		for ln in f:
			if ln.startswith('/* @c '):
				self.cline = ln
				break
			if ln.startswith('#endif') and pp == 1:
				break
			if ln.startswith('#ifdef __cplusplus'):
				self.cline = ''
				pp = 1
				continue

		if self.cline is None:
			print 'DEBUG: no @c in %s/%s' % (self.dirname, self.filename)
			return None
		
		zone = '[config]'
		text = ''
		pp = 0
		for ln in f: 
			if ln.startswith('#endif') and pp == 1: break
			if ln.startswith('#ifdef __cplusplus'): 
				pp = 1
				continue
			if ln.startswith('/* ['):
				zone = ln.split()[1]
				continue

			if ln.startswith('/* ===') or ln.startswith('/* ---'):
				if len(text) > 0 :
					self.add_block(zone, text, gen)
					text = ''
				continue
			
			if ln.startswith("#define _") :
				ln = ln.replace('#define _', '#define ').replace('\r','').replace('\n', '')
				if self.defines is None: self.defines = []
				if not ln.endswith('\\') :
					self.defines.append(ln)
					continue
				p = ln + '\n'	
				for ln in f:
					ln = ln.replace('\r','').replace('\n', '')
					p += (ln + '\n')
					if not ln.endswith('\\'): break
				#
				self.defines.append(p)
				continue
			if pp == 0: text += ln
		#
		if len(text) > 0 :
			self.add_block(zone, text, gen)
		f.close()
		return self

	def add_block(self, zone, text, gen = None):
		if not self.zone_map.has_key(zone):
			self.zone_map[zone] = []
			self.zone_order.append(zone)
		self.zone_map[zone].append(text)
		
		functype = parse_functype(text)
		if gen is None or functype is None: return
		
		funcname = parse_funcname(functype)
		FUNCMAP_found(funcname)

		if text.find('@map') > 0:
			m = new_Map(text)
			if m != None and m.cfunc != funcname:
				m.cfunc = None

		if text.find('@method') > 0:
			m = new_Method(text)
			if m is None: return
			if m.cfunc == funcname:
				m.write_methodfunc(gen.fc, functype)
			elif funcname != m.methodfunc:
				m.methodfunc = None

	def write_h(self, f):
		write_chapter(f, self.filename)
		if self.defines is not None:
			for d in self.defines:
				write_println(f, d)
			write_println(f)
			write_println(f)

		for zone in self.zone_order:
			blocks = self.zone_map[zone]
			for text in blocks:
				func = parse_functype(text)
				if func is not None:
					if(text.find('INLINE') > 0) : func = 'INLINE ' + func
					write_println(f, func + ';')
			write_println(f)
		write_println(f)
		
	def write_cfile(self, f):
		write_license(f)
		f.write('#include"commons.h"\n')
		self.write_h(f)
		write_comment(f, '@bof')
		for zone in self.zone_order:
			write_chapter(f, zone)
			blocks = self.zone_map[zone]
			c = 0
			for text in blocks:
				if c > 0 : write_line(f)
				f.write(text)
				c += 1
		write_comment(f, '@eof')

	def funcs(self):
		funcs = []
		for zone in self.zone_order:
			blocks = self.zone_map[zone]
			for text in blocks:
				func = parse_functype(text)
				if func is not None: funcs.append(text)
		return funcs

#------------------------------------------------------------------------------------

def new_CFile(drn, fn, gen = None):
	cf = CFile(drn, fn)
	f = open(cf.pathname())
	cf = cf.read_file(f, gen)
	f.close()
	return cf

#------------------------------------------------------------------------------------

def rewrite_CFILE(path):
	#print 'Rewriting %s' % (path)
	cf = new_CFile('', path)
	if cf is None: return
	#f = open(path, 'w')
	#cf.write_cfile(f)
	#f.close()

if __name__ == '__main__':
	for path in sys.argv[1:]:
		rewrite_CFILE(path)

#------------------------------------------------------------------------------------

def read_CFILE(gen, drn, level = 3):
	try:
		fl = os.listdir(drn)
		for fn in fl:
			if not fn.endswith('.c') : continue
			if level < 3 :
				if fn.endswith('_api2.c') and level < 2: continue
				if fn.endswith('_api1.c') and level < 1: continue
			cf = new_CFile(drn, fn, gen)
			if cf is None: continue
			cf.write_h(gen.fh)
	except OSError, e:
		print e
		pass
	