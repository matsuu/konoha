#!/usr/bin/python
import os, sys
from pygenlib2  import *

# ---------------------------------------------------------------------------

OS = {
'linux': ['unux', 'readline', 'dl', 'socket'],
'macosx': ['unix'],
'windows': ['winsock'],
'tk': ['tk'],
}

DRVAPIS = [
'f_inptr_open', 'f_inptr_getc', 'f_inptr_read', 'f_inptr_close',
'f_outptr_open', 'f_outptr_putc', 'f_outptr_write', 'f_outptr_flush', 'f_outptr_close',
'f_rsptr_free', 'f_rsptr_next',
'f_connptr_open', 'f_connptr_query', 'f_connptr_close',
]

DRIVERS2 = {
'InputStream': ['open', 'getc', 'read', 'close'],
'OutputStream': ['open', 'putc', 'write', 'flush', 'close'],
'Connection': ['open', 'query', 'close'],
'ResultSet': ['next', 'free'],
}



class Source :
	def __init__(self, bdir):
		self.bdir = bdir
		self.lastfpath = ''
		self.TARGET = 'unix'
		self.OPTIONS = []
		self.MACROS = []
		self.MANIFESTO = {}
		self.USING_MAP = {}
		
		self.CFILES = []
		self.FUNC_MAP = {}
		self.FLAG_LIST = []
		self.FLAG_MAP = {}
		self.FIELDN_LIST = []
		self.FIELDN_MAP = {}
		self.LDLIBS = []
		self.DRIVERS = []
		self.H = []
		self.C = []
		self.CLASS_LIST = []
		self.CLASS_MAP = {}
		self.FUNCTYPE_LIST = []
		self.FUNCTYPE_MAP = {}
		self.METHOD_LIST = []
		self.METHOD_MAP = {}
		self.MAPMAP_LIST = []
		self.MAPMAP_MAP = {}
		self.STEXT_LIST = []
		self.STEXT_MAP = {}
		self.ACLASS_LIST = ['String']
		self.ICLASS_LIST = ['String']
		self.XCLASS_LIST = ['String:urn']
		self.TFUNC_MAP = {}
		self.XPACKAGE_LIST = []
		self.KNHINIT = []
		self.KNHAPI = []
		self.add_fieldn('this')
		self.add_fieldn('vargs')
		self.add_fieldn('lambda')
		self.add_fieldn('main')
		for v in "abcdefghijklmnopqrstuvwxyz": self.add_fieldn(v)
		self.add_functype('MFN_Any_Any_', 'new_MethodField__1(ctx, KNH_FLAG_MF_VARARGS, TYPE_Any, TYPE_Any, FIELDN_o)')
		self.add_functype('MFN_void_OutputStream_Any', 'new_MethodField__2(ctx, 0, TYPE_void, TYPE_OutputStream, FIELDN_w, TYPE_Any, FIELDN_o)')
		self.add_functype('MFN_Any', 'new_MethodField__0(ctx, 0, TYPE_Any)')
		for t,n in STEXT: self.add_STEXT(n, t)
	###
	
	def kpath(self, fpath):
		if fpath.startswith(self.bdir+'/'):
			return fpath[len(bdir)+1:]
		return fpath
	###
	def add_file(self, package, fpath):
		if fpath.startswith(self.bdir+'/'):
			fpath = fpath[len(self.bdir)+1:]
		self.CFILES.append(fpath) 
	
	def add_STEXT(self, t, n = None):
		if self.STEXT_MAP.has_key(t): return
		if n == None: n = t
		self.STEXT_MAP[t] = n
		self.STEXT_LIST.append(t)
		
	def add_driver(self, drv):
		self.package(drv.package).DRIVERS.append(drv)
	
	def add_flag(self, f):
		self.FLAG_LIST.append(f)
		self.FLAG_MAP[f.id] = f
	
	def add_class(self, c):
		if self.CLASS_MAP.has_key(c.id):
			print "DEBUG duplicated class name: %s" % c.id
			return
		self.CLASS_MAP[c.id] = c
		self.package(c.package).CLASS_LIST.append(c) 

	def add_xclass(self, c):
		if c.endswith("[]"):
			c = c.replace("[]", "")
			if not c in self.ACLASS_LIST: self.ACLASS_LIST.append(c)
			return
		if c.endswith(".."):
			c = c.replace("..", "")
			if not c in self.ICLASS_LIST: self.ICLASS_LIST.append(c)
			return
		if c.find(":") > 0:
			if not c in self.XCLASS_LIST: self.XCLASS_LIST.append(c)
			return

	def isClass(self, type):
		if type.endswith('..'): type = type[:-2]
		if type.endswith('!'): type = type[:-1]
		type = type.replace('*', '')
		if type == "Any" or type == "any": return True
		return self.CLASS_MAP.has_key(type)
		
	def add_fieldn(self, fn):
		fn = fn.replace('::', ':')
		if fn.startswith('%'): 
			fn = fn[1:]
		elif fn.startswith('get') or fn.startswith("set") :
			fn = fn[3:]
			if len(fn) > 0 : fn = fn[0].lower() + fn[1:]
		if self.FIELDN_MAP.has_key(fn):
			return
		self.FIELDN_MAP[fn] = True
		self.FIELDN_LIST.append(fn)

	def add_field(self, f):
		self.FIELD_LIST.append(f)
		self.FIELD_MAP[f.id] = f

	def add_functype(self, mfn, newmf):
		if not self.FUNCTYPE_MAP.has_key(mfn):
			#print '@', mfn, newmf
			self.FUNCTYPE_LIST.append(mfn)
			self.FUNCTYPE_MAP[mfn] = newmf
			
	def add_method(self, mtd):
		if self.METHOD_MAP.has_key(mtd.id):
			print "DEBUG duplicated method name: %s" % mtd.id
			return
		self.METHOD_MAP[mtd.id] = mtd
		self.package(mtd.package).METHOD_LIST.append(mtd)
		self.add_fieldn(mtd.mn)
		t = mtd.rtype
		if t.endswith("]") or t.endswith("."):
			self.add_xclass(t)
		for p in mtd.params:
			self.add_fieldn(p.name)
			t = p.type
			if t.endswith("]") or t.endswith("."):
				self.add_xclass(t)
			
	def add_mapmap(self, mm):
		if self.MAPMAP_MAP.has_key(mm.id):
			print "DEBUG duplicated mapmap name: %s" % mm.id
			return
		self.MAPMAP_MAP[mm.id] = mm
		self.package(mm.package).MAPMAP_LIST.append(mm)

	def add_func(self, anno, funcname):
		key = anno.split()[1]
		if key.endswith("+") and funcname.find('__') > 0:
			dummy, fn = funcname.split('__')
			key = key.replace('+', fn)
		print 'key=', key
		if self.TFUNC_MAP.has_key(key):
			print "DEBUG duplicated func name: %s" % key
			return
		self.TFUNC_MAP[key] = funcname

	def add_xpackage(self, pname):
		pname = pname.replace('.', '_')
		self.XPACKAGE_LIST.append(pname)
		func = '%s_load' % pname
		#self.TFUNC_MAP[func] = func
		func = '%s_traverse' % pname
		#self.TFUNC_MAP[func] = func

	def add_manifesto(self, key, values):
		print 'add_manifesto', key, values
		vl = values.split()
		if key.endswith('+'):
			if self.MANIFESTO.has_key(key):
				options = self.MANIFESTO[key]
			else:
				options = []
			for v in vl:
				if not v.startswith('*'): continue
 				vv = v[1:]
				options.append(vv)
				if key == 'using+': self.USING_MAP[vv] = vv
			self.MANIFESTO[key] = options
		else:
			for v in vl: 
				if v.startswith('*'): 
					v = v[1:]
					self.MANIFESTO[key] = v
					if key == 'os': 
						if OS.has_key(v):
							for n in OS[v]: self.USING_MAP[n] = n
					break
######


# /* @driver mysql Connection ResultSet */

class Driver:
	def __init__(self, package, anno, data):
		self.package = package
		self.anno = anno
		
		t = anno.split()
		self.scheme = t[1]
		self.classes = parse_options(t, 2)
		#
		data.add_driver(self)
		#
###	


def write_TFUNC_c(f, drv, data):
	for c in drv.classes:
		if not DRIVERS.has_key(c) : continue
		fb = data.CLASS_MAP[c].funcbase
		for cf in DRIVERS[c]:
			fn = fb + '_' + cf + '__' + drv.scheme
			f.write('''
\tKNH_TFUNC_%s_%s(ctx, "%s", %s);''' % (c.upper(), cf.upper(), fn, fn))
