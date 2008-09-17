#!/usr/bin/python
import os, sys
from pygenlib2  import *
from knhsettings import *

# ---------------------------------------------------------------------------

def write_flag_h(f, c, fb, n):
	if c == None: return
	if fb.index == None:
		write_define(f, fb.KNH_FLAG, 'KNH_FLAG%d' % n, 40)
	else:
		write_define(f, fb.KNH_FLAG, 'KNH_FLAG_OF_LOCAL%s' % fb.index, 40)

	args = 'o'
	if fb.fmt.find('[n]') > 0: args = 'o,n'
	funcbase = c.funcbase
	if c.cname == 'Class': 
		funcbase = funcbase.replace('Class', 'class')
	ff = fb.options[0]
	if ff != '*':  
		f.write('''
#define %s_%s%s(%s)  \\
\t((%s & %s) == %s)
''' % (funcbase, ff, fb.pname, args, fb.fmt % 'o', fb.KNH_FLAG, fb.KNH_FLAG))
		if fb.nname != None:
			f.write('''
#define %s_%s%s(%s)   \\
\t((%s & %s) != %s)
''' % (funcbase, ff, fb.nname, args, fb.fmt % 'o', fb.KNH_FLAG, fb.KNH_FLAG))
	ff = fb.options[1]
	if ff != '*':  
		f.write('''
#define %s_%s%s(%s,b)  \\
\tif(b) %s |= %s; else %s &= ~(%s);

''' % (funcbase, ff, fb.pname, args, fb.fmt % 'o', fb.KNH_FLAG, fb.fmt % 'o', fb.KNH_FLAG))
		if fb.nname != None:
			f.write('''
#define %s_%s%s(%s,b)  \\
\tif(b) %s &= ~(%s); else %s |= %s;

''' % (funcbase, ff, fb.nname, args, fb.fmt % 'o', fb.KNH_FLAG, fb.fmt % 'o', fb.KNH_FLAG))
	
####################################################################################################################

def write_class0_h(f, c, n):
	if(c.struct_name != '0'):
		write_ifndefine(f, c.cname.replace(':', '_'), 'knh_%s_t' % c.cname, 32)
	write_define(f, 'IS_%s(o)' % c.cname, '((o)->h.cid == %s)' % CLASS_cname(c.cname), 32)
	write_define(f, 'ASSERT_%s(o)' % c.cname, 'DEBUG_ASSERT(((o)->h.cid == %s))' % CLASS_cname(c.cname), 32)
	write_define(f, TYPE_cname(c.cname), '%s' % CLASS_cname(c.cname), 32)
	write_define(f, 'NN' + TYPE_cname(c.cname), 'TYPE_TONNTYPE(%s)' % CLASS_cname(c.cname), 32)
	write_define(f, 'CFLAG_%s' % c.cname, '((knh_flag_t)%s)' % c.flag, 32)
	write_define(f, 'FLAG_%s' % c.cname, 'KNH_FLAG_CF2OF(CFLAG_%s)' % c.cname, 32)

def write_struct_h(f, c, n):
	write_section(f, c.cname)
	write_define(f, STRUCT_cname(c.cname), '((knh_struct_t)%d)' % n, 32)
	write_define(f, CLASS_cname(c.cname), '((knh_class_t)%d)' % n, 32)
	write_define(f, 'IS_b%s(o)' % c.cname, '((o)->h.bcid == %s)' % CLASS_cname(c.cname), 32)
	write_class0_h(f, c, n)

def write_class_h(f, c, n):
	write_section(f, c.cname)
	if(c.struct_name == '0'):
		write_define(f, STRUCT_cname(c.cname), '((knh_struct_t)0)', 32)
	else:
		write_define(f, STRUCT_cname(c.cname), 'BSIZE_TOSID(sizeof(%s)/sizeof(Object*))' % c.struct_name, 32)
	write_define(f, CLASS_cname(c.cname), '((knh_class_t)KNH_TSTRUCT_SIZE+%d)' % n, 32)
	write_class0_h(f, c, n)

def write_fieldn_h(f, data):
    c = 0
    data.FIELDN_LIST.sort()
    for n in data.FIELDN_LIST:
        write_define(f, FIELDN_name(n.replace('::', '__').replace(':', '__')), '((knh_fieldn_t)%d)' % c)
        write_define(f, METHODN_mname(n), '((knh_methodn_t)%d)' % c)
        write_define(f, METHODN_mname('%' + n), '((knh_methodn_t)%d|KNH_FLAG_MN_MOVTEXT)' % c)
        if n.find(':') < 1:
	        if(len(n) > 0):
	            n = n[0].upper() + n[1:]
	        write_define(f, METHODN_mname('get' + n), '((knh_methodn_t)%d|KNH_FLAG_MN_GETTER)' % c)
	        write_define(f, METHODN_mname('set' + n), '((knh_methodn_t)%d|KNH_FLAG_MN_SETTER)' % c)
        c += 1
    write_define(f, 'KNH_TFIELDN_SIZE', '%d' % (c * 2))

def gen_name_h(bdir, data):
	fname = '%s/include/konoha/gen/konoha_name_.h' % bdir
	f = open_h(fname, ['<konoha/konoha_config.h>', '<konoha/konoha_t.h>'])
	#write_define(f, 'KONOHA_SERIAL_NUMBER', '%d' % get_serial_number())

	write_chapter(f, '[flag]')
	fc = ''
	fn = 0
	c = None
	for flag in data.FLAG_LIST:
		if flag.cname != fc:
			fc = flag.cname
			fn = 0
			if data.CLASS_MAP.has_key(fc):
				c = data.CLASS_MAP[fc]
			write_section(f, fc)
		write_flag_h(f, c, flag, fn)
		fn += 1

	write_chapter(f, '[class]')
	sn = 0
	cn = 0
	for p in data.PACKAGE_LIST:
		p = data.package(p)
		write_section(f, p.package)
		for c in p.CLASS_LIST:
			#if c.cname == 'Object': continue
			c.make_flag(data)
			if c.isTuple() :
				write_class_h(f, c, cn)
				write_line(f)
				cn += 1
			else:
				write_struct_h(f, c, sn)
				write_line(f)
				sn += 1
	
	write_chapter(f, '[array, iterator, X]')
	
	for cname in data.ACLASS_LIST:
		cname = cname.replace(":", "__")
		write_define(f, 'ACLASS_%s' % cname, '((knh_class_t)(KNH_TSTRUCT_SIZE+%d))' % cn, 32)
		write_define(f, 'ATYPE_%s' % cname, 'CLASS_TONNTYPE(ACLASS_%s)' % cname, 32)
		cn += 1
	
	for cname in data.ICLASS_LIST:
		cname = cname.replace(":", "__")
		write_define(f, 'ICLASS_%s' % cname, '((knh_class_t)(KNH_TSTRUCT_SIZE+%d))' % cn, 32)
		write_define(f, 'ITYPE_%s' % cname, 'CLASS_TONNTYPE(ICLASS_%s)' % cname, 32)
		cn += 1
	
	for cname in data.XCLASS_LIST:
		cname = cname.replace(":", "__")
		write_define(f, 'CLASS_%s' % cname, '((knh_class_t)(KNH_TSTRUCT_SIZE+%d))' % cn, 32)
		write_define(f, 'TYPE_%s' % cname, 'CLASS_%s' % cname, 32)
		write_define(f, 'NNTYPE_%s' % cname, 'CLASS_TONNTYPE(CLASS_%s)' % cname, 32)
		cn += 1
	
	write_chapter(f, '[tString]')
	cn = 0
	for t in data.STEXT_LIST:
		nm = data.STEXT_MAP[t]
		write_define(f, 'TSN_%s' % nm, '%d' % cn, 32)
		write_define(f, 'TS_%s' % nm, 'knh_tString[TSN_%s]' % nm)
		cn += 1
	write_define(f, 'KNH_TSTRING_SIZE', '%d' % cn, 32)
	
	write_chapter(f, '[field]')
	write_fieldn_h(f, data)

	write_chapter(f, '[MFN]')

	cn = 0
	for n in data.FUNCTYPE_LIST:
		write_define(f, n, '%d' % cn, 32)
		write_define(f, n.replace('MFN_', 'MF_'), 'knh_tMethodField(%s)' % n)
		cn += 1
	write_define(f, 'KNH_TMETHODFIELD_SIZE', '%d' % cn, 32)

	write_chapter(f, '[macros]')
	for m in data.MACROS:
		write_println(f, m)
	close_h(f, fname)

	fname = '%s/include/konoha/gen/konoha_t_.h' % bdir
	l = ['<konoha/konoha_t.h>', '<konoha/gen/konoha_name_.h>']
	f = open_h(fname, l)
	for p in data.PACKAGE_LIST:
		if p[0] == '+' or p[0] == '#': continue
		write_chapter(f, '[%s]' % p)
		f.write('''
#include<konoha/class/%s.h>
''' % p)
		p = data.package(p)
		for c in p.CLASS_LIST:
			if c.hasStruct():
				op = ''
				if c.cname == 'Method':   op = '\tf_method fcall_1;\n\tvoid *code_2;\n'
				if c.cname == 'Mapper':   op = '\tf_mapper fmap_1;\n'
				if c.cname == 'Iterator': op = '\tf_next fnext_1;\n'
				#if c.cname == 'Token':    op = '\tknh_fileid_t fileid;\n\tknh_ushort_t line;\n\tknh_flag_t flag;\n\tknh_token_t  tt;\n'
				#if c.cname == 'Stmt':     op = '\tknh_fileid_t fileid;\n\tknh_ushort_t line;\n\tknh_flag_t flag;\n\tknh_stmt_t  stt;\n'
				#if c.cname == 'Compiler': op = '\tknh_fileid_t fileid;\n\tknh_ushort_t line;\n\tknh_flag_t flag;\n\tknh_ushort_t dummy;\n'
				f.write('''
typedef struct knh_%s_t {
\tknh_hObject_t h;
\t%s *b;
%s} knh_%s_t; 
''' % (c.cname, c.struct_name, op, c.cname))

	write_dline(f)
	close_h(f, fname)

# ---------------------------------------------------------------------------

def gen_class_h(bdir, p, data):
	fname = '%s/include/konoha/gen/%s_.h' % (bdir, p.pname)
	f = open_h(fname, ['<konoha/konoha_config.h>', '<konoha/konoha_t.h>', '<konoha/gen/konoha_t_.h>'])
	
	write_chapter(f, '[prototype]')
	for fn in p.H:
		f.write('''
%s''' % fn)
	write_dline(f)

	close_h(f, fname)

# ---------------------------------------------------------------------------
# ---------------------------------------------------------------------------
# ---------------------------------------------------------------------------

def write_flag_c(f, c, fb, data):
	if c == None: return
	funcbase = c.funcbase
	a1 = '(knh_%s_t*)sfp[0].o' % c.cname
	if c.cname == 'Class': 
		funcbase = funcbase.replace('Class', 'class')
		a1 = 'knh_Class_cid(sfp[0].c)'
	methodbase = c.methodbase

	ff = fb.options[2]
	if ff != '*':
		ffn = ff + fb.pname
		functype = 'METHOD %s_%s(Ctx *ctx, knh_sfp_t *sfp)' % (methodbase, ffn)
		Method(c.package, '@method Boolean! %s.%s()' % (c.cname, ffn), functype, data)
		f.write('''
static 
METHOD %s_%s(Ctx *ctx, knh_sfp_t *sfp)
{
\tMETHOD_RETURN_BOOLEAN(ctx, sfp, %s_%s(%s));
}
''' % (methodbase, ffn, funcbase, ffn, a1))
		if fb.nname != None:
			ffn = ff + fb.nname
			functype = 'METHOD %s_%s(Ctx *ctx, knh_sfp_t *sfp)' % (methodbase, ffn)
			Method(c.package, '@method Boolean! %s.%s()' % (c.cname, ffn), functype, data)
			f.write('''
static
METHOD %s_%s(Ctx *ctx, knh_sfp_t *sfp)
{
\tMETHOD_RETURN_BOOLEAN(ctx, sfp, !(%s_%s(%s)));
}
''' % (methodbase, ffn, funcbase, ffn, a1))
	#
	ff = fb.options[3]
	if ff != '*':
		ffn = ff + fb.pname
		functype = 'METHOD %s_%s(Ctx *ctx, knh_sfp_t *sfp)' % (methodbase, ffn)
		Method(c.package, '@method void %s.%s(Boolean b)' % (c.cname, ffn), functype, data)
		f.write('''
static
METHOD %s_%s(Ctx *ctx, knh_sfp_t *sfp)
{
\t%s_%s(%s, IS_TRUE(sfp[1].o));
\tMETHOD_RETURN(ctx, sfp, KNH_VOID);
}
''' % (methodbase, ffn, funcbase, ffn, a1))
		if fb.nname != None:
			ffn = ff + fb.nname
			functype = 'METHOD %s_%s(Ctx *ctx, knh_sfp_t *sfp)' % (methodbase, ffn)
			Method(c.package, '@method void %s.%s(Boolean b)' % (c.cname, ffn), functype, data)
			f.write('''
static
METHOD %s_%s(Ctx *ctx, knh_sfp_t *sfp)
{
\t%s_%s(%s, IS_TRUE(sfp[1].o));
\tMETHOD_RETURN(ctx, sfp, KNH_VOID);
}
''' % (methodbase, ffn, funcbase, ffn, a1))

def write_ctable_c(f, c, data):
	if c.isTuple() : return
	if not c.hasStruct():
		f.write('''
static INLINE
knh_struct_t
KNH_TSTRUCT_$1(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void *finit, void *fcopy, void *fgc,
	knh_hcode_t (*fhashCode)($1*),
	int (*fcompareTo)($1*, $1*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, finit, fcopy, fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}
'''.replace('$1', c.cname))
		return
	
	f.write('''
static INLINE
knh_struct_t
KNH_TSTRUCT_$1(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_$1*, int, Object*),
	void (*fcopy)(Ctx*, knh_$1*, knh_$1*),
	void (*fgc)(Ctx*, knh_$1*, f_traverse),
	knh_hcode_t (*fhashCode)($1*),
	int (*fcompareTo)($1*, $1*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}
'''.replace('$1', c.cname))

def write_struct_c(f, c, data):
	if c.isTuple() : return
	fh = '%s_hashCode' % (c.funcbase)
	if not data.FUNC_MAP.has_key(fh) : fh = 'NULL'
	fc = '%s_compareTo' % (c.funcbase)
	if not data.FUNC_MAP.has_key(fc) : fc = 'NULL'
	
	if not c.hasStruct():
		f.write('''
\tKNH_TSTRUCT_%s(ctx, %s, 0, "%s", NULL, NULL, NULL, %s, %s); ''' % (c.cname, STRUCT_cname(c.cname), c.cname, fh, fc))
		return
	f.write('''
\tKNH_TSTRUCT_%s(ctx, %s, sizeof(%s),
\t\t"%s",
\t\t%s_struct_init,
\t\t%s_struct_copy, 
//\t\t%s_struct_compare, 
\t\t%s_struct_traverse,
\t\t%s,
\t\t%s);''' % (c.cname, STRUCT_cname(c.cname), c.struct_name, c.cname, c.funcbase, c.funcbase, c.funcbase, c.funcbase, fh, fc))

def write_class_c(f, c, data):
	f.write('''
\tKNH_TCLASS__T(ctx, CFLAG_%s, "%s",
\t\t%s, %s, %s,''' % (c.cname, c.fullname, CLASS_cname(c.cname), STRUCT_cname(c.cname), CLASS_cname(c.super_cname)))
	spec = '%s_cspec' % (c.funcbase)
	if not data.FUNC_MAP.has_key(spec):
		spec = 'KNH_NULL'
	else:
		spec += '(ctx)'
	fvalue = '%s_fdefault' % (c.funcbase)
	if not data.FUNC_MAP.has_key(fvalue) : fvalue = 'NULL'
	#print c.cname, fvalue
	f.write('''
\t\t%s, %s, %d); ''' % (spec, fvalue, c.method_size))
	#print c.options
	if '@Param1' in c.options:
		f.write('''
\tKNH_TCLASS_PARAM(ctx, %s, CLASS_Any, CLASS_Nue);''' % (CLASS_cname(c.cname)))
	if '@Param2' in c.options:
		f.write('''
\tKNH_TCLASS_PARAM(ctx, %s, CLASS_Any, CLASS_Any);''' % (CLASS_cname(c.cname)))
		

def write_method_c(f, mtd, data):
	if mtd.methodfunc == None: return
	f.write('''
\tKNH_TMETHOD(ctx, 
\t\t%s, 
\t\t%s, %s, /*delta*/0, 
\t\t%s, %s,
\t\t%s
\t);
''' % (mtd.make_flag(data), mtd.methodfunc, mtd.optfunc, CLASS_cname(mtd.cname), METHODN_mname(mtd.mn), mtd.MF()))

def C(t):
	if t[0] == 'p': t = t[1:]
	if t.endswith(".."): return "Iterator"
	if t.endswith("[]"): return "Array"
	return t.replace("!", "")

def CI(t):
	if t[0] == 'p': t = t[1:]
	return t.replace("!", "").replace("..", "").replace("[]", "")

def write_tmapper_c(f, mm, data):
	if mm.mapfunc == None: return
	f.write('''
INLINE static
void KNH_TMAPPER_%s_%s(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_%s_t* (*fmapfunc)(Ctx *, knh_%s_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}
''' %(CI(mm.fcname), CI(mm.tcname), C(mm.tcname), C(mm.fcname)))

def write_mapmap_c(f, mm, data):
	if mm.mapfunc == None: return
	f.write('''
\tKNH_TMAPPER_%s_%s(ctx, 
\t\t%s, 
\t\t%s, %s,  
\t\t%s, %s
\t);
''' % (CI(mm.fcname), CI(mm.tcname), mm.make_flag(data), CLASS_cname(mm.fcname), CLASS_cname(mm.tcname), mm.mapfunc, mm.mapopt))

def write_method_func_c(f, mtd, data):
	if mtd.methodfunc != None: return
	if not data.CLASS_MAP.has_key(mtd.cname):
		print 'DEBUG %s' % mtd.anno
		return
	c = data.CLASS_MAP[mtd.cname]
	rtype = mtd.functype.split()[0]
	params = parse_params(mtd.functype)
	if rtype == 'void':
		rcval = ''
		rmap = ''
		rval = 'KNH_VOID'
	elif data.isClass(rtype):
		rcval = 'Object *rv = (Object*)'
		rmap = ''
		if rtype.endswith('!'):
			rmap = 'KNH_ASSERT(IS_NOTNULL(rv));\n\t';
		rval = 'rv'
	else:
		rcval = '%s v = ' % rtype
		rmap = 'Object* rv = (Object*)%s;\n\t' % mapfunc(rtype, 'v', mtd.rtype, 'rv', data)
		rval = 'rv'
	mtd.methodfunc = '%s_%s' % (c.methodbase, mtd.mn.replace('::', '__').replace(':', '__'))
	f.write('''
static
METHOD %s(Ctx *ctx, knh_sfp_t *sfp)
{
\t/* %s */''' % (mtd.methodfunc, mtd.anno.replace('@', '')))
	f.write('''
\t%s%s(''' % (rcval, parse_funcname(mtd.functype)))
	if c.struct_name == 'knh_Object_t' :
		cc = 'knh_%s_t' % c.cname
	else :
		cc = c.struct_name + '_t'
	if cc == '0': cc = c.cname
	if params[0].type == 'Ctx*':
		ci = 2
		f.write('''
\t\tctx,
\t\t(%s*)sfp[0].o''' % cc)
	else:
		ci = 1
		f.write('''
\t\t(%s*)sfp[0].o''' % cc)
	ki = 0
	for p in params[ci:]:
		n = 'sfp[%d].o' % (ki + 1)
		if p.type == 'knh_vargc_t':
			f.write(''',
\t\tknh_sfp_argc(ctx, sfp + %d),
\t\tsfp + %d''' % ((ki + 1), (ki + 1)))
			break
		if p.type == 'knh_hcode_t':
			f.write(''',
\t\tknh_Object_hashCode(%s)''' % n)
			continue
		if ki < len(mtd.params):
			f.write(''',
\t\t%s''' % (mapfunc(mtd.params[ki].type, n, p.type, p.name, data)))
			ki += 1
		else:
			break
	f.write('''
\t);
\t%sMETHOD_RETURN(ctx, sfp, %s);
}
''' % (rmap, rval))

def gen_class_c(bdir, p, data):
	fname = '%s/konoha/gen/package/%s_.c' % (bdir, p.pname)
	f = open_c(fname, ['<konoha/konoha_dev.h>'])
	write_chapter(f, '[flag]')
	for c in p.CLASS_LIST:
		for fb in data.FLAG_LIST:
			if fb.cname == c.cname:
				write_flag_c(f, c, fb, data)

	write_chapter(f, '[method]')
	for mtd in p.METHOD_LIST:
		write_method_func_c(f, mtd, data)
	
	write_chapter(f, '[TABLE]')
	for mm in p.MAPMAP_LIST:
		write_tmapper_c(f, mm, data)
		
	write_chapter(f, '[package]')
	f.write('''
void knh_%s_initapis(Ctx *ctx)
{
''' % p.pname)
#	for c in p.CLASS_LIST:
#		write_struct_c(f, c, data)
#	for c in p.CLASS_LIST:
#		write_class_c(f, c, data)
	for mtd in p.METHOD_LIST:
		write_method_c(f, mtd, data)
	for mm in p.MAPMAP_LIST:
		write_mapmap_c(f, mm, data)
	
	f.write('''
}
''')
	close_c(f, fname)

def gen_package_c(bdir, data):
	for p in data.PACKAGE_LIST:
		p = data.package(p)
		if p.isDriver:
			pass
		elif p.isLoadable:
			pass
		else:
			gen_class_h(bdir, p, data)
			gen_class_c(bdir, p, data)

def gen_package_h(bdir, data):
	fname = '%s/include/konoha/gen/package_.h' % (bdir)
	l = ['<konoha/gen/konoha_t_.h>']
	for p in data.PACKAGE_LIST:
		p = data.package(p)
		if p.isDriver:
			pass
		elif p.isLoadable:
			pass
		else:
			l.append('<konoha/gen/%s_.h>' % p.pname)
	f = open_h(fname, l)
	write_dline(f)
	close_h(f, fname)

def gen_load_c(bdir, data):
	fname = '%s/konoha/gen/konoha_load_.c' % (bdir)
	f = open_c(fname, ['<konoha/konoha_dev.h>'])
	write_chapter(f, '[prototype]')
	for p in data.PACKAGE_LIST:
		p = data.package(p)
		if p.isDriver:
			pass
		elif p.isLoadable:
			pass
		else:
			f.write('''
void knh_%s_initapis(Ctx *ctx);''' % p.pname)

	write_chapter(f, '[init]')
	
	f.write('''

void knh_tString_init0(void)
{
	DEBUG_ASSERT(knh_tString != NULL);
''')

	for t in data.STEXT_LIST:
		nm = data.STEXT_MAP[t]
		f.write('''
\tKNH_INITv(knh_tString[TSN_%s], new_String__T(NULL, "%s"));''' % (nm, t))
		
	f.write('''
}''')
	for p in data.PACKAGE_LIST:
		p = data.package(p)
		for c in p.CLASS_LIST:
			write_ctable_c(f, c, data)
	f.write('''
void konoha_class_init0(Ctx *ctx)
{''')
	for p in data.PACKAGE_LIST:
		p = data.package(p)
		write_section(f, p.package)
		for c in p.CLASS_LIST:
			write_struct_c(f, c, data)
		for c in p.CLASS_LIST:
			write_class_c(f, c, data)
	
	for cname in data.ACLASS_LIST:
		cname = cname.replace(":", "__")
		f.write('''
	KNH_ACLASS(ctx, ACLASS_%s, CLASS_%s);''' % (cname, cname))
	
	for cname in data.ICLASS_LIST:
		cname = cname.replace(":", "__")
		f.write('''
	KNH_ICLASS(ctx, ICLASS_%s, CLASS_%s);''' % (cname, cname))
	
	for cname in data.XCLASS_LIST:
		bcname, tag = cname.split(':')
		cname = cname.replace(":", "__")
		func = 'knh_cspec_' + cname
		if not data.FUNC_MAP.has_key(func):
			func = 'NULL'
		f.write('''
	KNH_XCLASS(ctx, CLASS_%s, CLASS_%s, %s);''' % (cname, bcname, func))
	
	for key in data.TFUNC_MAP.keys():
		f.write('''
	KNH_TFUNC__T(ctx, "%s", %s);''' % (key, data.TFUNC_MAP[key]))

	l = data.FIELDN_LIST
	l.sort()
	for n in l:
		f.write('''
\tKNH_TFIELDN__T(ctx, %s, "%s");''' % (FIELDN_name(n.replace(':','__')), n))

	write_line(f)
	
	for n in data.FUNCTYPE_LIST:
#		f.write('''
#\tKNH_INITv(knh_tMethodField[%s], %s);''' % (n, data.FUNCTYPE_MAP[n]))
		f.write('''
\tknh_tMethodField_add(ctx, %s); //%s''' % (data.FUNCTYPE_MAP[n], n))
#//\tKNH_TMETHODFIELD(ctx, %s, %s);''' % (n, ))
	
	for p in data.PACKAGE_LIST:
		p = data.package(p)
		if p.isDriver:
			pass
		elif p.isLoadable:
			pass
		else:
			f.write('''
\tknh_%s_initapis(ctx);''' % p.pname)
	
	f.write('''
}
''')
	close_c(f, fname)
	
def gen_manifesto_h(bdir, data):
	fname = '%s/include/konoha/gen/manifesto.h' % (bdir)
	f = open_h(fname, ['<stdio.h>'])
	write_define(f, 'KONOHA_SERIAL_NUMBER', '%d' % data.serial_number)
	write_dline(f)
	for u in data.USING_MAP:
		write_ifndefine(f, 'KONOHA_USING_%s' % u.upper(), '1')
	close_h(f, fname)

#########################################################

def filebase(cpath):
	return cpath.split('/')[-1].replace('.c', '')

def write_makefile_objs(f, data):
	l = []
	ll = []
	u = []
	uu = []
	pkg = ['libkonoha']
	for p in data.PACKAGE_LIST:
		p = data.package(p)
		for fn in p.CFILES:
			l.append(filebase(fn))
			p.make_libs(u, data)
			if p.isDriver:
				pkg.append('drv_%s' % p.pname)
			elif p.isLoadable:
				pkg.append('pkg_%s' % p.pname)
			else:
				ll.append(filebase(fn))
				p.make_libs(uu, data)

	f.write('''

objs_M = ''')
	for fb in l:
		f.write('''\\
\t%s''' % (fb + 'M.o'))

	f.write('''

objs_D = ''')
	for fb in l:
		f.write('''\\
\t%s''' % (fb + 'D.o'))

	f.write('''

LDLIBS_M = ''')
	for t in u:
		f.write('''\\
\t%s''' % (t))

	f.write('''

objs_L = ''')
	for fb in ll:
		f.write('''\\
\t%s''' % (fb + 'L.o'))

	f.write('''

LDLIBS_L = ''')
	for t in uu:
		f.write('''\\
\t%s''' % (t))

	f.write('''

packages_dylib = ''')
	for fb in pkg:
		f.write('''\\
\t%s.dylib''' % (fb))

	f.write('''

packages_so = ''')
	for fb in pkg:
		f.write('''\\
\t%s.so''' % (fb))

	f.write('''

packages_dll = ''')
	for fb in pkg:
		f.write('''\\
\t%s.dll''' % (fb))
	
def write_makefile_cc(f, p, data):
	l = []
	for fn in p.CFILES:
		l.append(filebase(fn))
	
	u = []
	p.make_libs(u, data)

	f.write('''

objs_%sL = ''' % p.pname)
	for fb in l:
		f.write('''\\
\t%s''' % (fb + 'L.o'))

	f.write('''
LDLIBS_%sL = ''' % p.pname)
	for t in u:
		f.write('''\\
\t%s''' % (t))

	for fn in p.CFILES:
		fb = filebase(fn) + 'M.o'
		f.write('''

%s : ../%s ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../%s" -o%s
''' % (fb, fn, fn, fb))
		fb = filebase(fn) + 'D.o'
		f.write('''
%s : ../%s ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../%s" -o%s
''' % (fb, fn, fn, fb))
		fb = filebase(fn) + 'L.o'
		f.write('''
%s : ../%s ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../%s" -o%s
''' % (fb, fn, fn, fb))

		if p.isDriver:
			f.write('''

drv_%s.dylib : $(objs_%sL)
	$(CC) -dynamiclib -o drv_%s.dylib -L"./lib" -L"./libexec" $(objs_%sL) $(LDLIBS_%sL) -lkonoha
	mkdir -p driver
	mv drv_%s.dylib driver/

drv_%s.so : $(objs_%sL)
	$(CC) -shared -Wl,-soname,drv_%s.so -o drv_%s.so -L"./lib" -L"./libexec" $(objs_%sL) $(LDLIBS_%sL) -lkonoha
	mkdir -p driver
	mv drv_%s.so driver/

drv_%s.dll : $(objs_%sL)
	$(CC) -shared -Wl -o drv_%s.dll -L"./lib" -L"./libexec" $(objs_%sL) $(LDLIBS_%sL) -lkonoha
	mkdir -p driver
	mv drv_%s.dll driver/

'''.replace('%s', p.pname));
		elif p.isLoadable:
			f.write('''

pkg_%s.dylib : $(objs_%sL)
	$(CC) -dynamiclib -o pkg_%s.dylib -L"./lib" -L"./libexec" $(objs_%sL) $(LDLIBS_%sL) -lkonoha
	mkdir -p package/%s
	mv pkg_%s.dylib package/%s

pkg_%s.so : $(objs_%sL)
	$(CC) -shared -Wl,-soname,drv_%s.so -o pkg_%s.so -L"./lib" -L"./libexec" $(objs_%sL) $(LDLIBS_%sL) -lkonoha
	mkdir -p package/%s
	mv pkg_%s.so package/%s

pkg_%s.dll : $(objs_%sL)
	$(CC) -shared -Wl -o pkg_%s.dll -L"./lib" -L"./libexec" $(objs_%sL) $(LDLIBS_%sL) -lkonoha
	mkdir -p package/%s
	mv pkg_%s.dll package/%s

'''.replace("%s", p.pname))


def gen_makefile(bdir, data):
	f = open(bdir + '/build/makefile', 'w')
	f.write('''#Makefiile by gen_konoha.py

CC = gcc
CFLAGS_MONO = -O2 -g -Wall
CFLAGS_DEBUG = -O0 -g3 -Wall -fmessage-length=0
CFLAGS_LIB = -O2 -g -Wall

program = konoha
library = libkonoha

.PHONY: all
all: $(program)

''')

	write_makefile_objs(f, data)

	for p in data.PACKAGE_LIST:
		p = data.package(p)
		write_makefile_cc(f, p, data)

	f.write('''

konohaM.o: ../konoha.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../konoha.c" -okonohaM.o

konohaD.o: ../konoha.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../konoha.c" -okonohaD.o

konohaL.o: ../konoha.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -I"../include" -c "../konoha.c" -okonohaL.o

.PHONY: $(program)
$(program): konohaM.o $(objs_M)
	$(CC) -o $(program) $^ -L"./lib" $(LDLIBS_M) $(LDLIBS)
	strip $(program)
	mkdir -p bin
	mv $(program) bin

.PHONY: $(program).exe
$(program).exe: konohaM.o $(objs_M)
	$(CC) -o $(program).exe $^ -L"./lib" $(LDLIBS_M) $(LDLIBS)
	strip $(program).exe
	mkdir -p bin
	mv $(program).exe bin

.PHONY: safe_$(program)
safe_$(program): konohaD.o $(objs_D)
	$(CC) -o safe_$(program) $^ -L"./lib" $(LDLIBS_M) $(LDLIBS)
	mkdir -p bin
	mv safe_$(program) bin

.PHONY: safe_$(program).exe
safe_$(program).exe: konohaD.o $(objs_D)
	$(CC) -o safe_$(program).exe $^ -L"./lib" $(LDLIBS_M) $(LDLIBS)
	mkdir -p bin
	mv safe_$(program).exe bin

.PHONY: lib$(program).dylib
lib$(program).dylib: konohaL.o $(objs_L)
	$(CC) -dynamiclib -o libkonoha.dylib $^ -L"./lib" $(LDLIBS_L) $(LDLIBS)
	mkdir -p libexec
	mv libkonoha.dylib libexec
	$(CC) -o $(program) konohaL.o -L"./libexec" -lkonoha
	mv $(program) libexec

.PHONY: lib$(program).so
lib$(program).so: konohaL.o $(objs_L)
	$(CC) -shared -Wl,-soname,libkonoha.so -o libkonoha.so $^ -L"./lib" $(LDLIBS_L) $(LDLIBS)
	mkdir -p libexec
	mv libkonoha.so libexec
	$(CC) -o $(program) konohaL.o -L"./libexec" -lkonoha
	mv $(program) libexec

.PHONY: lib$(program).dll
lib$(program).dll: konohaL.o $(objs_L)
	$(CC) -shared -Wl,--output-def,libkonoha.def,--out-implib,libkonohadll.a -o libkonoha.dll $^ -L"./lib" $(LDLIBS_L) $(LDLIBS)
	mkdir -p libexec
	mv libkonoha.dll libexec
	$(CC) -o $(program) konohaL.o -L"./libexec" -lkonoha
	mv $(program) libexec

.PHONY: lib$(program)
lib$(program): 
	echo "choose one: dylib, so, cll"

.PHONY: dylib
dylib: lib$(program).dylib $(packages_dylib)

.PHONY: so
so: lib$(program).so $(packages_so)

.PHONY: dll
dll: lib$(program).dll $(packages_dll)

.PHONY: clean
clean:
	$(RM) -rf bin libexec package driver $(objs_M) $(objs_L) $(objs_D) *.o 

''')
	
	f.close()
	
