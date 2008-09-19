#!/usr/bin/python
import os, sys
from pygenlib2  import *
from source import parse_params
from source import parse_funcname

TYPES = {
	'Boolean/knh_bool_t':	'IS_TRUE(%s)',
	'Boolean/int':		   'IS_TRUE(%s)',
	'Boolean!/knh_bool_t':	'IS_TRUE(%s)',
	'Boolean!/int':		   'IS_TRUE(%s)',
	'knh_bool_t/Boolean':	'new_Boolean(ctx, %s)',
	'int/Boolean':		   'new_Boolean(ctx, %s)',
#	
	'Int!/knh_int_t':	  'knh_Int_toint((Int*)%s)',
	'Int!/knh_uint_t':	 '(knh_uint_t)knh_Int_toint((Int*)%s)',
	'Int!/size_t':		 '(size_t)knh_Int_toint((Int*)%s)',
	'Int!/int':			'(int)knh_Int_toint((Int*)%s)',
	
	'Int/knh_int_t':	  'knh_IntNULL_toint((Int*)%s)',
	'Int/knh_uint_t':	 '(knh_uint_t)knh_IntNULL_toint((Int*)%s)',
	'Int/size_t':		 '(size_t)knh_IntNULL_toint((Int*)%s)',
	'Int/int':			'(int)knh_IntNULL_toint((Int*)%s)',

	'knh_int_t/Int':	  'new_Int(ctx, %s)',
	'size_t/Int':		 'new_Int(ctx, (knh_int_t)%s)',
	'knh_uint_t/Int':	 'new_Int(ctx, %s)',
	'knh_index_t/Int':	'new_Int(ctx, %s)',
	'int/Int':			'new_Int(ctx, (knh_int_t)%s)',
#
	'Float!/knh_float_t':  'knh_Float_tofloat((Float*)%s)',
	'Float!/float':		'(float)knh_Float_tofloat((Float*)%s)',
	'Float!/double':	   '(double)knh_Float_tofloat((Float*)%s)',
	'Float/knh_float_t':  'knh_FloatNULL_tofloat((Float*)%s)',
	'Float/float':		'(float)knh_FloatNULL_tofloat((Float*)%s)',
	'Float/double':	   '(double)knh_FloatNULL_tofloat((Float*)%s)',
	
	'knh_float_t/Float':  'new_Float(ctx, %s)',
	'float/Float':		'new_Float(ctx, (knh_float_t)%s)',
	'double/Float':	   'new_Float(ctx, (knh_float_t)%s)',

	'String!/char*':	   'knh_String_tochar((String*)%s)',
	'String!/knh_bytes_t': 'knh_String_tobytes((String*)%s)', 
	'String/char*':	   'knh_StringNULL_tochar((String*)%s)',
	'String/knh_bytes_t': 'knh_StringNULL_tobytes((String*)%s)', 
	'String!/knh_methodn_t' : 
		'knh_tmethodn_forname(ctx, knh_String_tobytes((String*)%s), METHODN_NONAME)', 

	'char*/String':	   'new_String(ctx, %s)',
	'knh_bytes_t/String': 'new_String(ctx, CLASS_String, %s)', 

	'Bytes!/knh_bytes_t' : 'knh_Bytes_tobytes((Bytes*)%s)',
	'Bytes/knh_bytes_t' :  'knh_BytesNULL_tobytes((Bytes*)%s)',

	'Class/knh_class_t' : 'knh_Class_cid((Class*)%s)',
	'Class/knh_type_t':   'knh_Class_cid((Class*)%s)',
	'knh_class_t/Class':  'knh_tClass_class(ctx, %s)', 
	'knh_type_t/Class':   'knh_tClass_class(ctx, %s)',

	'void/void':	   '%s',
}

# ---------------------------------------------------------------------------

#############

def mapfunc(t1, n1, t2, n2, data):
	t2 = t2.replace('!', '')
	key = '%s/%s' % (t1, t2)
	comment = '/* %s %s => %s %s */' % (t1, n1, t2, n2)
	if TYPES.has_key(key):
		return '%s %s' % (TYPES[key] % ('%s' % (n1)), comment)
	if t2.find('_') != 0: 
		if data.CLASS_MAP.has_key(t2):
			t2 = data.CLASS_MAP[t2]
	return '(%s)%s %s' % (t2, n1, comment)

#############

##############################################################################

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
	

###############################################################################

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
	if(c.struct_name.endswith('_t')):
		write_define(f, STRUCT_cname(c.cname), c.struct_name.replace('knh_', 'STRUCT_').replace('_t', ''), 32)
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

def gen_class_h(bdir, data):
	fname = '%s/include/konoha/gen/konoha_class_.h' % bdir
	f = open_h(fname, ['<konoha/konoha_t.h>'] + data.INCLUDE_H)

	write_define(f, 'KONOHA_SERIAL_NUMBER', '%d' % data.serial_number)
	write_dline(f)
	for u in data.USING_MAP:
		write_ifndefine(f, 'KONOHA_USING_%s' % u.upper(), '1')
	
	write_chapter(f, '[FLAG]')
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

	write_chapter(f, '[CLASS]')
		
	cn = 0
	sn = 0
	for c in data.CLASS_LIST:
		c.make_flag(data)
		if c.struct_name.startswith('knh_%s_' % c.cname) and not '@Field' in c.options:
			write_struct_h(f, c, sn)
			write_line(f)
			sn += 1
		else:
			write_class_h(f, c, cn)
			write_line(f)
			cn += 1
	
	write_chapter(f, '[Array<X>]')
	for cname in data.ACLASS_LIST:
		cname = cname.replace(":", "__")
		write_define(f, 'ACLASS_%s' % cname, '((knh_class_t)(KNH_TSTRUCT_SIZE+%d))' % cn, 32)
		write_define(f, 'ATYPE_%s' % cname, 'CLASS_TONNTYPE(ACLASS_%s)' % cname, 32)
		cn += 1
	
	write_chapter(f, '[Iterator<X>]')
	for cname in data.ICLASS_LIST:
		cname = cname.replace(":", "__")
		write_define(f, 'ICLASS_%s' % cname, '((knh_class_t)(KNH_TSTRUCT_SIZE+%d))' % cn, 32)
		write_define(f, 'ITYPE_%s' % cname, 'CLASS_TONNTYPE(ICLASS_%s)' % cname, 32)
		cn += 1
	
	write_chapter(f, '[Object:X]')
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
	for n in data.MF_LIST:
		write_define(f, n, '%d' % cn, 32)
		write_define(f, n.replace('MFN_', 'MF_'), 'knh_tMethodField(%s)' % n)
		cn += 1
	write_define(f, 'KNH_TMETHODFIELD_SIZE', '%d' % cn, 32)
	
	write_chapter(f, '[KNH_CLASS_T]')
	
	for c in data.CLASS_LIST:
		if not c.struct_name.endswith("_t"):
			op = ''
			if c.cname == 'Method':   op = '\tf_method fcall_1;\n\tvoid *code_2;\n'
			if c.cname == 'Mapper':   op = '\tf_mapper fmap_1;\n'
			if c.cname == 'Iterator': op = '\tf_next fnext_1;\n'
			if c.cname == 'Token':    op = '\tknh_fileid_t fileid;\n\tknh_ushort_t line;\n\tknh_flag_t flag;\n\tknh_token_t  tt;\n'
			if c.cname == 'Stmt':     op = '\tknh_fileid_t fileid;\n\tknh_ushort_t line;\n\tknh_flag_t flag;\n\tknh_stmt_t  stt;\n'
			#if c.cname == 'Compiler': op = '\tknh_fileid_t fileid;\n\tknh_ushort_t line;\n\tknh_flag_t flag;\n\tknh_ushort_t dummy;\n'
			f.write('''
typedef struct knh_%s_t {
\tknh_hObject_t h;
\t%s *b;
%s} knh_%s_t; 
''' % (c.cname, c.struct_name, op, c.cname))

	write_dline(f)
	close_h(f, fname)

	fname = '%s/include/konoha/gen/konoha_proto_.h' % bdir
	f = open_h(fname, ['<konoha/gen/konoha_class_.h>'])
	
	write_chapter(f, '[PROTOTYPE]')
	for p in data.PROTOTYPE_LIST:
		if not 'KNHAPI' in p : write_println(f, p)
	
	close_h(f, fname)

	fname = '%s/include/konoha/gen/konoha_knhapi_.h' % bdir
	f = open_h(fname, ['<konoha/gen/konoha_class_.h>'])
	
	write_chapter(f, '[MACROS]')
	for m in data.MACROS:
		write_println(f, m)

	write_chapter(f, '[PROTOTYPE]')
	for p in data.PROTOTYPE_LIST:
		if 'KNHAPI' in p : write_println(f, p)
	close_h(f, fname)



##############################################################################
##############################################################################
##############################################################################

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
		data.add_method('@method Boolean! %s.%s()' % (c.cname, ffn), functype)
		f.write('''
static 
METHOD %s_%s(Ctx *ctx, knh_sfp_t *sfp)
{
\tKNH_RETURN_Boolean(ctx, sfp, %s_%s(%s));
}
''' % (methodbase, ffn, funcbase, ffn, a1))
		if fb.nname != None:
			ffn = ff + fb.nname
			functype = 'METHOD %s_%s(Ctx *ctx, knh_sfp_t *sfp)' % (methodbase, ffn)
			data.add_method('@method Boolean! %s.%s()' % (c.cname, ffn), functype)
			f.write('''
static
METHOD %s_%s(Ctx *ctx, knh_sfp_t *sfp)
{
\tKNH_RETURN_Boolean(ctx, sfp, !(%s_%s(%s)));
}
''' % (methodbase, ffn, funcbase, ffn, a1))
	#
	ff = fb.options[3]
	if ff != '*':
		ffn = ff + fb.pname
		functype = 'METHOD %s_%s(Ctx *ctx, knh_sfp_t *sfp)' % (methodbase, ffn)
		data.add_method('@method void %s.%s(Boolean b)' % (c.cname, ffn), functype)
		f.write('''
static
METHOD %s_%s(Ctx *ctx, knh_sfp_t *sfp)
{
\t%s_%s(%s, IS_TRUE(sfp[1].o));
\tKNH_RETURN_void(ctx, sfp);
}
''' % (methodbase, ffn, funcbase, ffn, a1))
		if fb.nname != None:
			ffn = ff + fb.nname
			functype = 'METHOD %s_%s(Ctx *ctx, knh_sfp_t *sfp)' % (methodbase, ffn)
			data.add_method('@method void %s.%s(Boolean b)' % (c.cname, ffn), functype)
			f.write('''
static
METHOD %s_%s(Ctx *ctx, knh_sfp_t *sfp)
{
\t%s_%s(%s, IS_TRUE(sfp[1].o));
\tKNH_RETURN_void(ctx, sfp);
}
''' % (methodbase, ffn, funcbase, ffn, a1))

def write_ctable_c(f, c, data):
	if not c.struct_name.startswith("knh_%s_" % c.cname) or '@Field' in c.options: return
	if not c.struct_name.startswith("knh_%s_struct" % c.cname):
		return
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
static INLINE knh_struct_t KNH_TSTRUCT_$1(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_$1_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_$1_struct*, knh_$1_struct*),
	void (*fgc)(Ctx*, knh_$1_struct*, f_traverse),
	knh_hcode_t (*fhashCode)($1*),
	int (*fcompareTo)($1*, $1*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}
'''.replace('$1', c.cname))

def write_struct_c(f, c, data):
	if not c.struct_name.startswith("knh_%s_" % c.cname) or '@Field' in c.options: return
	fh = '%s_hashCode' % (c.funcbase)
	if not data.FUNC_MAP.has_key(fh) : fh = 'NULL'
	fc = '%s_compareTo' % (c.funcbase)
	if not data.FUNC_MAP.has_key(fc) : fc = 'NULL'
	
	if not c.struct_name.startswith("knh_%s_struct" % c.cname):
		f.write('''
\tKNH_TSTRUCT(ctx, %s, 0, "%s", NULL, NULL, NULL, (f_hashCode)%s, (f_compareTo)%s); ''' % (STRUCT_cname(c.cname), c.cname, fh, fc))
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
\t\t%s, (void*)%s, /*delta*/0, 
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
	cc = 'knh_%s_t' % c.cname
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
\t%sKNH_RETURN(ctx, sfp, %s);
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

def gen_konoha_init_c(bdir, data):
	fname = '%s/konoha/gen/konoha_init_.c' % (bdir)
	f = open_c(fname, ['<konoha/konoha_dev.h>'])
	
	write_chapter(f, '[prototype]')
	
	for key in data.STATICLIB_MAP.keys():
		f.write('''
int %s(Ctx *ctx);''' % (key))
	
	write_chapter(f, '[flag]')
	
	for c in data.CLASS_LIST:
		for fb in data.FLAG_LIST:
			if fb.cname == c.cname: write_flag_c(f, c, fb, data)
	
	write_chapter(f, '[method]')
	for mtd in data.METHOD_LIST: write_method_func_c(f, mtd, data)
	write_chapter(f, '[tmapper]')
	for mm in data.MAPPER_LIST: write_tmapper_c(f, mm, data)
	
	write_chapter(f, '[INIT]')
	
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
	for c in data.CLASS_LIST:
			write_ctable_c(f, c, data)
	
	f.write('''
void konoha_class_init0(Ctx *ctx)
{''')
	for c in data.CLASS_LIST:
		write_struct_c(f, c, data)
	for c in data.CLASS_LIST:
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
		if data.FUNC_MAP.has_key(func):
			f.write('''
	KNH_XCLASS(ctx, CLASS_%s, CLASS_%s, %s(ctx, CLASS_%s, CLASS_%s, NULL));''' % (cname, bcname, func, bcname, cname))
	
	f.write('''
#ifdef KONOHA_MONOLITHIC
''')
	for key in data.STATICLIB_MAP.keys():
		f.write('''
	KNH_TSTATICLIB__T(ctx, "%s", (void*)%s);''' % (key, data.STATICLIB_MAP[key]))

	f.write('''
#endif/*KONOHA_MONOLITHIC*/
''')

	l = data.FIELDN_LIST
	l.sort()
	for n in l:
		f.write('''
\tKNH_TFIELDN__T(ctx, %s, "%s");''' % (FIELDN_name(n.replace(':','__')), n))

	write_line(f)
	
	for n in data.MF_LIST:
		f.write('''
\tknh_tMethodField_add(ctx, %s); //%s''' % (data.MF_MAP[n], n))
	
	for mtd in data.METHOD_LIST: write_method_c(f, mtd, data)
	for mm in data.MAPPER_LIST: write_mapmap_c(f, mm, data)

	for p in data.INITFUNC_LIST:
		f.write('''
\t%s(ctx);''' % p)
	
	f.write('''
}
''')
	close_c(f, fname)

