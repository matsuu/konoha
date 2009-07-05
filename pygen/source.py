#!/usr/bin/python
import os, os.path, sys
from pygenlib2  import *
#from gen_hfile import *

##############################################################################

__FILE__ = ''
__LINE__ = 1

def warning(msg):
	print '[%s:%d] %s' % (__FILE__, __LINE__, msg)

##############################################################################

STEXT = [
 ("EMPTY", ""), ("TAB", "\\t"), ("LF","\\n"), ("SPC", " "),
 ("EOL", "EOL"), ("BEGIN", "BEGIN"), ("END", "END"),
 ("void", "void"), ("true", "true"), ("false","false"), ("null", "null"),
 ("main", "main"), ("ENCODING", '"KONOHA_ENCODING"'),
 ("DEVNULL", "/dev/null"), ("DEVSTDIN", "/dev/stdin"),("DEVSTDERR", "/dev/stderr"), ("DEVSTDOUT", "/dev/stdout"),
 ("ATlabel", "@label"),
# ("TYPEERR", "Type!!"), ("NULLERR", "Null!!"),("SYNTAXERR", "Syntax!!"),
 ("SecurityException", "Security!!"), ("AssertionException", "Assertion!!"), 
 ("LP", "("), ("RP", ")"),  ("LB", "{"), ("RB", "}"),  ("LS", "["), ("RS", "]"), 
]

##############################################################################

class Source :
	def __init__(self, bdir):
		self.bdir = bdir
		self.lastfpath = ''
		self.TARGET = 'unix'
		self.OPTIONS = []
		self.MACROS = []
		#self.MANIFESTO = {}
		self.USING_MAP = {}  # @gen_class_h
		self.HFILES = []
		self.CFILES = []
		self.FUNC_MAP = {}
		self.INITFUNC_LIST = []
		self.PROTOTYPE_LIST = []
		#self.C = []
		self.FLAG_LIST = []
		self.FLAG_MAP = {}
		self.FIELDN_LIST = []
		self.FIELDN_MAP = {}
		self.CLASS_LIST = []
		self.CLASS_MAP = {}
		self.MF_LIST = []
		self.MF_MAP = {}
		self.METHOD_LIST = []
		self.METHOD_MAP = {}
		self.MAPPER_LIST = []
		self.MAPPER_MAP = {}
		self.EXPT_MAP = {}
		self.EXPT_LIST = []
		self.STEXT_LIST = []
		self.STEXT_MAP = {}
		self.ACLASS_LIST = ['String']
		self.ICLASS_LIST = ['String']
		self.XCLASS_LIST = ['String:urn']
		self.GENERICS_LIST = []
		self.XPACKAGE_LIST = []
		self.INCLUDE_H = ['<konoha/konoha_class.h>']
		self.STATICLIB_MAP = {}
		self.MODULES_MAP = {}
		self.add_fieldn('this')
		self.add_fieldn('vargs')
		self.add_fieldn('lambda')
		self.add_fieldn('main')
		self.add_fieldn('default')
		self.add_fieldn('typeof')
		self.add_fieldn('defined')
		self.add_fieldn('super')
		self.add_fieldn('proceed')
		self.add_fieldn('delegate')
		self.add_fieldn('copy')
		self.add_fieldn('format')
		self.add_fieldn('likely')
		self.add_fieldn('unlikely')
		self.add_fieldn('GLOBAL')  ## GLOBALINDEX
		self.add_fieldn('register')  ## register
		for v in "abcdefghijklmnopqrstuvwxyz": self.add_fieldn(v)
#		self.add_mf('MFN_Any_Any_', 'new_MethodField__1(ctx, KNH_FLAG_MF_VARARGS, TYPE_Any, TYPE_Any, FIELDN_o)')
#		self.add_mf('MFN_void_OutputStream_Any', 'new_MethodField__2(ctx, 0, TYPE_void, TYPE_OutputStream, FIELDN_w, TYPE_Any, FIELDN_o)')
#		self.add_mf('MFN_Any', 'new_MethodField__0(ctx, 0, TYPE_Any)')
	###
	
	def kpath2(self, fpath):
		if fpath.startswith(self.bdir+'/'):
			return fpath[len(bdir)+1:]
		return fpath
	###
	
	def add_file(self, fpath):
		if fpath.startswith(self.bdir+'/'):
			fpath = fpath[len(self.bdir)+1:]
		self.CFILES.append(fpath) 
		self.MODULES = []
		self.MODULES_MAP[fpath] = self.MODULES
	
	def add_STEXT(self, t, n = None):
		if self.STEXT_MAP.has_key(t): return
		if n == None: n = t
		self.STEXT_MAP[t] = n
		self.STEXT_LIST.append(t)
	
	def add_flag(self, anno):
		f = Flag(anno, self)
		self.FLAG_LIST.append(f)
		self.FLAG_MAP[f.id] = f
	
	def add_class(self, anno):
		c = Class(anno, self)
		if self.CLASS_MAP.has_key(c.id):
			warning("DEBUG duplicated class name: %s" % c.id)
			return
		self.CLASS_MAP[c.id] = c
		self.CLASS_LIST.append(c) 
	
	def add_generics(self, anno):
		c = Generics(anno, self)
		self.GENERICS_LIST.append(c) 
	
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

	def add_field(self, anno):
		f = Field(self, anno)
		self.FIELD_LIST.append(f)
		self.FIELD_MAP[f.id] = f

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
		
	def add_mf(self, mfn, newmf):
		if not self.MF_MAP.has_key(mfn):
			self.MF_LIST.append(mfn)
			self.MF_MAP[mfn] = newmf
			
	def add_method(self, mtd, func, text = ""):
		mtd = Method(mtd, func, self)
		if self.METHOD_MAP.has_key(mtd.id):
			warning("DEBUG duplicated method name: %s" % mtd.id)
			return
		self.METHOD_MAP[mtd.id] = mtd
		self.METHOD_LIST.append(mtd)
		self.add_fieldn(mtd.mn)
		t = mtd.rtype
		if t.endswith("]") or t.endswith("."):
			self.add_xclass(t)
		for p in mtd.params:
			self.add_fieldn(p.name)
			t = p.type
			if t.endswith("]") or t.endswith("."):
				self.add_xclass(t)
		self.MODULES.append(mtd)
			
	def add_mapper(self, mm, func, text = ""):
		mm = Mapper(mm, func, self)
		if self.MAPPER_MAP.has_key(mm.id):
			warning("DEBUG duplicated mapmap name: %s" % mm.id)
			return
		self.MAPPER_MAP[mm.id] = mm
		self.MAPPER_LIST.append(mm)
		self.MODULES.append(mm)
	
	def add_expt(self, anno):
		e = Expt(anno, self)
		if self.EXPT_MAP.has_key(e.id):
			warning("DEBUG duplicated expt name: %s!!" % e.id)
			return
		self.EXPT_MAP[e.id] = e
		self.EXPT_LIST.append(e.id)
	

##############################################################################

def parse_options(t, n):
	if len(t) <= n: return []
	return t[n:]

# /* @field TYPE Class.name ctype.cname @Options */

class Field :
	def __init__(self, anno, data):
		self.anno = anno
		
		t = anno.split()
		self.type =  t[1]
		self.id = t[2]
		self.cname, self.fn = t[2].split('.')
		if t[3].find(".") > 0 : 
			self.ctype, self.cname = t[3].split('.')
		else:
			self.ctype = 'Object*'
			self.cname = t[3]
		self.options = parse_options(t, 4)
		data.add_fieldn(self.fn)
		###
###

# /* @flag Nue.Release!Debug NUE:1 knh_Object_head(%s)->flag 'is:set:*:*' */

class Flag:
	def __init__(self, anno, data):
		#print anno
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
###

# /* @class "package.Class" Object knh_Class_struct @Option */

class Class :
	def __init__(self, anno, data):
		self.anno = anno
		t = anno.split()
		if t[1].startswith('"'):
			self.fullname = t[1].replace('"')
			self.cname = self.fullname[self.fullname.rfind(".")+1]
			self.id = self.cname
		else:
			self.cname = t[1]
			self.id = t[1]
			self.fullname = "konoha." + t[1]
		self.super_cname = t[2]
		self.struct_name = t[3]
		self.options = parse_options(t, 4)
		self.funcbase = 'knh_' + self.cname
		self.methodbase = self.funcbase.replace('_', '__')
		self.method_size = 0
		###	
	def make_flag(self, data):
		flag = ''
		for o in self.options:
			if o == '@Field' or o.startswith('@Param') : continue
			flag += ('|' + 'KNH_FLAG_CF_%s' % o[1:].upper())
		if len(flag) == 0:
			self.flag = '0'
		else:
			self.flag = flag[1:]
		return self.flag
	###
######

###


# /* @generics HashMapSS HashMap<String,String> String String */
# /* @generics ArrayCmp int(Any1!,Any1!) Int! Any1! Any1! void */

class Generics :
	def __init__(self, anno, data):
		self.anno = anno
		t = anno.split()
		self.cname = t[1]
		self.fullname = t[2]
		self.params = t[3:]
		if self.fullname.find('(') > 0:
			self.bname = 'Closure'
		else: 
			self.bname, dummy = self.fullname.split('<')
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
			params.append(Param('Any', t[0]))
	return params

MT_PARAMS = [Param('OutputStream', 'w'), Param('Any', 'm')]

class Method :
	def __init__(self, anno, functype, data):
		self.anno = anno
		self.functype = functype
		pre, args = anno.split('(')
		t = pre.replace('..', ',,').replace('.',' ').split()
		self.rtype = t[1].replace(',,', '..')
		self.cname = t[2]
		self.mn = t[3].replace(',,', '..')
		self.id = '%s.%s' % (self.cname, self.mn)
		self.options = parse_options(t, 4)
		parse_flag(pre.replace('[]', '@@'), self.options)
		self.methodfunc = None
		self.optfunc = 'NULL'
		if self.mn.startswith('%'):
			self.params = MT_PARAMS
			self.optfunc = parse_funcname(self.functype)
			self.methodfunc = 'knh_fmethod_movableText'
			if self.optfunc.startswith("knh__"):
				self.methodfunc = self.optfunc
				self.optfunc = 'NULL'
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
		data.CLASS_MAP[self.cname].method_size += 1
		self.mfn = self.MFN()
		self.newmf = self.new_MethodField()
		data.add_mf(self.mfn, self.newmf)
		###
			
	def ntype(self, type):
		if type.endswith('[]!'): return 'na%s' % type.replace('[]!', '')
		if type.endswith('!'): return 'n%s' % type.replace('!', '')
		if type.endswith('[]'): return 'a%s' % type.replace('[]','')
		if type.endswith('..'): return 'i%s' % type.replace('..','')
		return type

	def make_mfflag(self):
		flag = ''
		for o in self.options:
			o = o[1:].upper()
			if o.find('VARARGS') == -1:continue
			return 'KNH_FLAG_MF_%s' % o
		return '0'

	def MFN(self):
		t = 'MFN_%s' % self.ntype(self.rtype)
		for p in self.params:
			t += '_%s' % self.ntype(p.type)
		flag = self.make_mfflag()
		if flag != '0': t += '_'
		return t

	def MF(self):
		t = 'MF_%s' % self.ntype(self.rtype)
		for p in self.params:
			t += '_%s' % self.ntype(p.type)
		flag = self.make_mfflag()
		if flag != '0': t += '_'
		return t
	
	def new_MethodField(self):
		args = ''
		for p in self.params:
			args += ', %s, %s' % (TYPE_cname(p.type), FIELDN_name(p.name[0]))
		return 'new_MethodField__%d(NULL, %s, %s%s)' % (len(self.params), self.make_mfflag(), TYPE_cname(self.rtype), args) 
	
	def make_flag(self, data):
		flag = ''
		for o in self.options:
			flag += ('|' + 'KNH_FLAG_MF_%s' % o[1:].upper())
		if len(flag) == 0:
			self.flag = '0'
		else:
			self.flag = flag[1:]
		return self.flag
	###

#####

class Mapper :
	def __init__(self, anno, funcname, data) :
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
		
	def make_flag(self, data):
		flag = ''
		for o in self.options:
			flag += ('|' + 'KNH_FLAG_MMF_%s' % o[1:].upper())
		if len(flag) == 0:
			self.flag = '0'
		else:
			self.flag = flag[1:]
		return self.flag
###

#####

# /* @expt IO!! "Exception!!" @Option */

class Expt :
	def __init__(self, anno, data) :
		self.anno = anno
		t = anno.split()
		self.name = t[1].replace("!!", "").replace("'", "").replace('"', '')
		self.parent = t[2].replace("'", '"')
		if self.parent == "-": self.parent = 'NULL'
		elif not self.parent.startswith('"'): self.parent = '"' + self.parent + '"'
		self.id = self.name
		self.options = parse_options(t, 3)
		#
		
	def make_flag(self, data):
		flag = ''
		for o in self.options:
			flag += ('|' + 'KNH_FLAG_EF_%s' % o[1:].upper())
		if len(flag) == 0:
			self.flag = '0'
		else:
			self.flag = flag[1:]
		return self.flag
###

##############################################################################

# ---------------------------------------------------------------------------
## parser

def functype_filter(text):
	text = text.replace('', '').replace('_SS_', '').replace('','')
	prev = ' '
	text2 = ''
	for c in text:
		if c == ' ' and prev == ' ':
			continue
		text2 += c
		prev = c
	if text2.endswith(' '): text2 = text2[:len(text2)-1]
	if text2.endswith('\t'): text2 = text2[:len(text2)-1]
	if text2.find('=') > 0 : return None
	if not text2.endswith(')'):
		print text2.find('=')
		debug_print('Invalid functype: %s' % text2)
		return None
	return text2
###

def parse_functype(text):
	func = ''
	for ln in text.split('\n'):
		if ln.startswith('/') or ln.startswith('#'):
			continue
		if ln.find('{') >= 0:
			func += ' ' + ln.replace('{', '')
			return functype_filter(func)
		func += ' ' + ln
	return None
###

# ---------------------------------------------------------------------------


def nz_cparam(tn, vn):
	if vn.startswith('*'): return nz_cparam(tn+'*', vn[1:])
	return tn, vn
###

def parse_funcname(functype):
	t = functype.replace('static', '').replace('(', ' ').split()
	tn, funcname = nz_cparam(t[0], t[1])
	return funcname
###

# ---------------------------------------------------------------------------

def parse_anno(text, anno):
	text = text[text.find(anno):]
	text = text[:text.find('*/')]
	return text
###

# ---------------------------------------------------------------------------

def parse_flag(anno, oplist):
	loc = anno.find(']')
	if loc == -1: return
	s,t = anno[:loc].split('[')
	for op in t.split('|'):
		oplist.append('@'+op)


##############################################################################

def read_source_cblock(fpath, zone, text, data):
	if text.find('@data') > 0 : return
	functype = parse_functype(text)
	if functype == None : 
		if functype != None and functype.find('_fdefault') > 0 :
			funcname = parse_funcname(functype)
			data.FUNC_MAP[funcname] = functype
		return
	
	if 'KNHINIT' in functype:
		functype = functype.replace('KNHINIT', '')
		funcname = parse_funcname(functype)
		data.INITFUNC_LIST.append(funcname)
	else:
		funcname = parse_funcname(functype)

	for ln in text.split('\n'):
		if ln.find('/* @map') != -1: data.add_mapper(parse_anno(ln, '@map'), funcname, text)
		if ln.find('/* @method') != -1: data.add_method(parse_anno(ln, '@method'), functype, text)
	
	if functype.find('static') >= 0: 
		if functype != None and functype.find('_fdefault') > 0 :
			funcname = parse_funcname(functype)
			data.FUNC_MAP[funcname] = functype
		return
	
	if(data.lastfpath != fpath):
		data.lastfpath = fpath;
		data.PROTOTYPE_LIST.append('/* %s */' % fpath)
	
	data.PROTOTYPE_LIST.append(functype + ';')
	data.FUNC_MAP[funcname] = functype
	
	
###

def read_lineanno(line, data):
	if line.find('/* @flag') != -1:
		data.add_flag(parse_anno(line, '@flag'))
		return line
	if line.find('/* @field') != -1:
		data.add_field(parse_anno(line, '@field'))
		return line
	if line.find('/* @class') != -1:
		data.add_class(parse_anno(line, '@class'))
		return line
	if line.find('/* @expt') != -1: 
		data.add_expt(parse_anno(line, '@expt'))
		return line
	if line.find('/* @generics') != -1: 
		data.add_generics(parse_anno(line, '@generics'))
		return line
	return line

def read_source_h(fpath, data):
	print fpath
	f = open(fpath)
	__FILE__ = fpath
	__LINE__ = 1
	for ln in f:
		__LINE__ += 1
		ln = read_lineanno(ln, data)
	f.close()

def read_source_c(fpath, data):
	f = open(fpath)
	data.add_file(fpath)
	__FILE__ = fpath
	__LINE__ = 1
	# header part
	pp = 0
	cline = None
	for ln in f:
		__LINE__ =+ 1
		ln = read_lineanno(ln, data)
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
		__LINE__ =+ 1
		if ln.startswith('//'): continue
		ln = read_lineanno(ln, data)
		if ln.startswith('#endif') and pp == 1: break
		if ln.startswith('#ifdef __cplusplus'): 
			pp = 1
			continue
		
		if ln.startswith('/* ['):
			zone = ln.split()[1]
			continue

		if ln.startswith('/* ===') or ln.startswith('/* ---'):
			if len(text) > 0 :
				read_source_cblock(fpath, zone, text, data)
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
		read_source_cblock(fpath, zone, text, data)
	f.close()
###

def read_include_class(dir, data):
	read_source_h(dir + '/include/konoha/konoha_class.h', data)

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
				data.add_file(fpath)
		if fn.endswith('.h') and dir.find('/include/konoha') == -1: 
			read_source_h(fpath, data)

def read_xpackage_OLD(dir, data):
	fl = os.listdir(dir)
	for fn in fl:
		if fn.startswith('.'): continue
		if fn.startswith('_'): continue
		if not os.path.isdir(dir +'/' + fn): continue
		data.XPACKAGE_LIST.append(fn)
		f = 'knh%s_load' % fn
		data.STATICLIB_MAP[f] = f
	
def read_xpackage(dir, data):
	pass

#############

def read_data(bdir):
	data = Source(bdir)
	for t,n in STEXT: data.add_STEXT(n, t)
	f = open('%s/src/BUILDID' % bdir)
	data.serial_number = int(f.readline())
	f.close()
	if len(sys.argv) > 1: data.OPTIONS = sys.argv[1:]
	if '-c' in data.OPTIONS: 
		data.serial_number += 1
		print 'build=%d' % data.serial_number
		f = open('%s/src/BUILDID' % bdir, 'w')
		f.write('%d' % data.serial_number)
		f.close()
	read_include_class(bdir, data)
	read_source(bdir + '/include/konoha', data)
	#read_source(bdir + '/class', data)
	read_source(bdir + '/src', data)
	read_xpackage(bdir + '/package', data)
	return data

if __name__ == '__main__':
	bdir = '..'
	data = read_data(bdir)
	print data.CFILES
	#gen_package_c(bdir, data)
	#gen_load_c(bdir, data)
	#gen_package_h(bdir, data)
	#gen_name_h(bdir, data)
	#gen_manifesto_h(bdir, data)
	#gen_makefile(bdir, data)

