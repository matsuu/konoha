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

DRIVERS = {
 'InputStream': ['open', 'getc', 'read', 'close'],
 'OutputStream': ['open', 'putc', 'write', 'flush', 'close'],
 'Connection': ['open', 'query', 'close'],
 'ResultSet': ['next', 'free'],
}

TYPES = {
	'Bool/knh_bool_t':    'IS_TRUE(%s)',
	'Bool/int':           'IS_TRUE(%s)',
	'Bool!/knh_bool_t':    'IS_TRUE(%s)',
	'Bool!/int':           'IS_TRUE(%s)',
	'knh_bool_t/Bool':    'new_Bool(ctx, %s)',
	'int/Bool':           'new_Bool(ctx, %s)',
#	
	'Int!/knh_int_t':      'knh_Int_toint(%s)',
	'Int!/knh_uint_t':     '(knh_uint_t)knh_Int_toint(%s)',
    'Int!/size_t':         '(size_t)knh_Int_toint(%s)',
    'Int!/int':            '(int)knh_Int_toint(%s)',
	
	'Int/knh_int_t':      'knh_IntNULL_toint(%s)',
	'Int/knh_uint_t':     '(knh_uint_t)knh_IntNULL_toint(%s)',
    'Int/size_t':         '(size_t)knh_IntNULL_toint(%s)',
    'Int/int':            '(int)knh_IntNULL_toint(%s)',

	'knh_int_t/Int':      'new_Int(ctx, %s)',
    'size_t/Int':         'new_Int(ctx, (knh_int_t)%s)',
	'knh_uint_t/Int':     'new_Int(ctx, %s)',
	'knh_index_t/Int':    'new_Int(ctx, %s)',
	'int/Int':            'new_Int(ctx, (knh_int_t)%s)',
#
	'Float!/knh_float_t':  'knh_Float_tofloat(%s)',
	'Float!/float':        '(float)knh_Float_tofloat(%s)',
	'Float!/double':       '(double)knh_Float_tofloat(%s)',
	'Float/knh_float_t':  'knh_FloatNULL_tofloat(%s)',
	'Float/float':        '(float)knh_FloatNULL_tofloat(%s)',
	'Float/double':       '(double)knh_FloatNULL_tofloat(%s)',
	
	'knh_float_t/Float':  'new_Float(ctx, %s)',
	'float/Float':        'new_Float(ctx, (knh_float_t)%s)',
	'double/Float':       'new_Float(ctx, (knh_float_t)%s)',

	'String!/char*':       'knh_String_tochar(%s)',
	'String!/knh_bytes_t': 'knh_String_tobytes(%s)', 
	'String/char*':       'knh_StringNULL_tochar(%s)',
	'String/knh_bytes_t': 'knh_StringNULL_tobytes(%s)', 
	'String!/knh_methodn_t' : 
		'knh_tmethodn_forname(ctx, knh_String_tobytes(%s), METHODN_NONAME)', 

	'char*/String':       'new_String(ctx, %s)',
	'knh_bytes_t/String': 'new_String(ctx, CLASS_String, %s)', 

	'Bytes!/knh_bytes_t' : 'knh_Bytes_tobytes(%s)',
	'Bytes/knh_bytes_t' :  'knh_BytesNULL_tobytes(%s)',

	'Class/knh_class_t' : 'knh_Class_class((Class*)%s)',
	'Class/knh_type_t':   'knh_Class_type((Class*)%s)',
	'knh_class_t/Class':  'new_Class__type(ctx, %s)', 
	'knh_type_t/Class':   'new_Class__type(ctx, %s)',

	'void/void':       '%s',
}

# ---------------------------------------------------------------------------

#############

def mapfunc(t1, n1, t2, n2, data):
	t2 = t2.replace('!', '')
	key = '%s/%s' % (t1, t2)
	comment = '/* %s %s => %s %s */' % (t1, n1, t2, n2)
	if TYPES.has_key(key):
		return '%s %s' % (TYPES[key] % n1, comment)
	if t2.find('_') != 0: 
		if data.CLASS_MAP.has_key(t2):
			t2 = data.CLASS_MAP[t2]
	return '(%s)%s %s' % (t2, n1, comment)

#############

class Package :
	def __init__(self, package):
		self.package = package
		self.pname = package.replace('+', '').replace('#', '')
		self.isDriver = False
		if package.startswith('#'): self.isDriver = True
		self.isLoadable = False
		if package.startswith('+'): self.isLoadable = True
		self.LDLIBS = []
		self.CFILES = []
		self.DRIVERS = []
		self.H = []
		self.C = []
		self.CLASS_LIST = []
		self.METHOD_LIST = []
		self.MAPMAP_LIST = []
	
	def make_libs(self, libs, data):
		for l in self.LDLIBS:
			l.append_libs(libs, data)
		
class Source :
	def __init__(self, bdir):
		self.bdir = bdir
		self.lastfpath = ''
		self.MACROS = []
		self.MANIFESTO = {}
		self.USING_MAP = {}
		self.PACKAGE_LIST = ['konoha']
		self.PACKAGE_MAP = {}
		self.FUNC_MAP = {}
		self.FLAG_LIST = []
		self.FLAG_MAP = {}
		self.FIELDN_LIST = []
		self.FIELDN_MAP = {}
		self.CLASS_MAP = {}
		self.METHOD_MAP = {}
		self.MAPMAP_MAP = {}
		self.add_fieldn('this')
		self.add_fieldn('vargs')
		self.add_fieldn('run')
	###
	
	def kpath(self, fpath):
		if fpath.startswith(self.bdir+'/'):
			return fpath[len(bdir)+1:]
		return fpath
	###

	def package(self, package):
		if not self.PACKAGE_MAP.has_key(package):
			verbose_print("reading package %s .." % package)
			self.PACKAGE_MAP[package] = Package(package)
			if not package in self.PACKAGE_LIST:
				self.PACKAGE_LIST.append(package)
		return self.PACKAGE_MAP[package]

	def add_file(self, package, fpath):
		if fpath.startswith(self.bdir+'/'):
			fpath = fpath[len(self.bdir)+1:]
		self.package(package).CFILES.append(fpath) 
		
	def add_library(self, lib):
		self.package(lib.package).LDLIBS.append(lib) 
	
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

	def isClass(self, type):
		if type.endswith('..'): type = type[:-2]
		if type.endswith('!'): type = type[:-1]
		type = type.replace('*', '')
		if type == "Any" or type == "any": return True
		return self.CLASS_MAP.has_key(type)
		
	def add_fieldn(self, fn):
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

	def add_method(self, mtd):
		if self.METHOD_MAP.has_key(mtd.id):
			print "DEBUG duplicated method name: %s" % mtd.id
			return
		self.METHOD_MAP[mtd.id] = mtd
		self.package(mtd.package).METHOD_LIST.append(mtd)
		self.add_fieldn(mtd.mn)
		for p in mtd.params:
			self.add_fieldn(p.name)
			
	def add_mapmap(self, mm):
		if self.MAPMAP_MAP.has_key(mm.id):
			print "DEBUG duplicated mapmap name: %s" % mm.id
			return
		self.MAPMAP_MAP[mm.id] = mm
		self.package(mm.package).MAPMAP_LIST.append(mm)

	def add_manifesto(self, key, values):
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

def parse_options(t, n):
	if len(t) <= n: return []
	return t[n:]

######

# /* @using socket -lsocket */

class Library:
	def __init__(self, package, anno, data):
		self.package = package
		self.anno = anno
		t = anno.split()
		self.name = t[1]
		self.options = parse_options(t, 2)
		data.add_library(self)
	
	def append_libs(self, libs, data):
		if not data.USING_MAP.has_key(self.name): return
		for l in self.options:
			if not l in libs: libs.append(l)
		
# /* @field TYPE Class.name ctype.cname @Options */

class Field :
	def __init__(self, package, anno, data):
		self.package = package
		self.anno = anno
		
		t = anno.split()
		self.type =  t[1]
		self.id = t[2]
		self.cname, self.fn = t[2].split('.')
		if t[3].find(".") > 0 : 
			self.ctype, self.cname = t[3].split('.')
		else:
			self.ctype = t[1]
			self.cname = t[3]
		self.options = parse_options(t, 4)
		###
		data.add_field(self)
		###
###

# /* @flag Nue.Release!Debug NUE:1 knh_Object_head(%s)->flag 'is:set:*:*' */

class Flag:
	def __init__(self, package, anno, data):
		#print anno
		self.package = package
		self.anno = anno

		t = anno.split()
		p = t[1].replace('!', '.').split('.')
		self.cname = p[0]
		self.pname = p[1]
		self.id = '%s.%s' % (p[0], p[1])
		if len(p) == 2:
			self.nname = None
		else:
			self.nname = p[2]
		if t[2].find(':') > 0:
			t[2], self.index = t[2].split(':')
		else:
			self.index = None
		self.KNH_FLAG = 'KNH_FLAG_%s_%s' % (t[2], self.pname.upper())
		self.fmt = t[3]
		self.options = t[4].replace('\'', '').split(':')
		###
		data.add_flag(self)
		###
###

# /* @class[OPT] Class Object knh_ @Option */

class Class :
	def __init__(self, package, anno, data):
		self.package = package
		self.anno = anno

		t = anno.split()
		self.cname = t[1]
		self.id = t[1]
		self.super_cname = t[2]
		self.fullname = package.replace('+', '') + '.' + t[1]
		self.struct_name = t[3]
		self.options = parse_options(t, 4)
		if self.struct_name.endswith('_'):
			self.struct_name += self.cname
		self.funcbase = self.struct_name
		if self.struct_name == '0':
			self.funcbase = 'knh_%s' % self.cname
		self.methodbase = self.funcbase.replace('_', '__')
		###
		data.add_class(self)
		###

	def isTuple(self):
		if self.struct_name == '0' or '@Tuple' in self.options:
			return True
		return False
	
	def make_flag(self, data):
		flag = ''
		for o in self.options:
			key = self.cname + '.' + o[1:]
			if data.FLAG_MAP.has_key(key):
				flag += ('|' + data.FLAG_MAP[key].KNH_FLAG)
		if len(flag) == 0:
			self.flag = '0'
		else:
			self.flag = flag[1:]
	###
######

class Param :
	def __init__(self, type, name, value = None):
		self.set(type, name)
		self.value = value
	
	def set(self, type, name):
		if name.startswith('*'):
			self.set(type+'*', name[1:])
		else:
			self.type = type
			self.name = name

def parse_params(ptext):
	params = []
	ptext = ptext[ptext.find('(')+1:]
	ptext = ptext[:ptext.find(')')]
	if len(ptext) == 0: return params
	for a in ptext.split(','):
		a = a.replace('=', ' ')
		t = a.split()
		if len(t) == 3:
			params.append(Param(t[0], t[1], t[2]))
		elif len(t) == 2:
			params.append(Param(t[0], t[1]))
		else:
			params.append(Param('any', t[0]))
	return params

MT_PARAMS = [Param('OutputStream', 'w'), Param('Any', 'm')]

class Method :
	def __init__(self, package, anno, functype, data):
		self.package = package
		self.anno = anno
		self.functype = functype
		
		pre, args = anno.split('(')
		t = pre.replace('.',' ').split()
		self.rtype = t[1]
		self.cname = t[2]
		self.mn = t[3]
		self.id = '%s.%s' % (self.cname, self.mn)
		self.options = parse_options(t, 4)
		self.methodfunc = None
		self.optfunc = 'NULL'
		if self.mn.startswith('%'):
			self.params = MT_PARAMS
			self.optfunc = parse_funcname(self.functype)
			self.methodfunc = 'knh_fmethod_movableText'
		else:
			self.params = parse_params(anno)
			funcname = parse_funcname(self.functype)
			loc = funcname.find('_')
			if funcname[loc+1] == '_':
				self.methodfunc = funcname
				self.optfunc = 'NULL'
			else:
				if len(self.options) > 0 and not self.options[0].startswith('@'):
					self.methodfunc = self.options[0]
					self.optfunc = funcname
		###
		data.add_method(self)
		###

	def make_flag(self, data):
		flag = ''
		for o in self.options:
			key = 'Method.' + o[1:]
			if data.FLAG_MAP.has_key(key):
				flag += ('|' + data.FLAG_MAP[key].KNH_FLAG)
		if len(flag) == 0:
			self.flag = '0'
		else:
			self.flag = flag[1:]
		return self.flag
	###

#####

class MapMap :
	def __init__(self, package, anno, funcname, data) :
		self.package = package
		self.anno = anno
		self.funcname = funcname
		
		t = anno.split()
		self.fcname = t[1]
		self.tcname = t[2]
		self.id = '%s->%s' % (self.fcname, self.tcname)
		self.options = parse_options(t, 3)
		self.mapfunc = funcname
		self.mapopt = 'KNH_NULL'
		if self.tcname.endswith('!') or self.tcname.endswith('..') or self.tcname == 'Bool':
			self.options.append('@Total')
		#
		data.add_mapmap(self)
		#
		
	def make_flag(self, data):
		flag = ''
		for o in self.options:
			key = 'MapMap.' + o[1:]
			if data.FLAG_MAP.has_key(key):
				flag += ('|' + data.FLAG_MAP[key].KNH_FLAG)
		if len(flag) == 0:
			self.flag = '0'
		else:
			self.flag = flag[1:]
		return self.flag
###

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

