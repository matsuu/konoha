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
	'knh_class_t/Class':  'knh_ClassTable_class(ctx, %s)', 
	'knh_type_t/Class':   'knh_ClassTable_class(ctx, %s)',

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
		write_define(f, fb.KNH_FLAG, 'KNH_FLAG_T%d' % n, 40)
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
	write_define(f, CLASS_cname(c.cname), '((knh_class_t)KNH_TCLASS_SIZE-(%d+1))' % n, 32)
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

	write_define(f, 'KONOHA_BUILDID', '%d' % data.serial_number)
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
	
	write_define(f, 'ACLASS_Int', 'CLASS_IArray', 32)
	write_define(f, 'ATYPE_Int', 'CLASS_IArray', 32)
	write_define(f, 'NNATYPE_Int', 'NNTYPE_cidOLD(CLASS_IArray)', 32)
	
	write_define(f, 'ACLASS_Float', 'CLASS_FArray', 32)
	write_define(f, 'ATYPE_Float', 'CLASS_FArray', 32)
	write_define(f, 'NNATYPE_Float', 'NNTYPE_cidOLD(CLASS_FArray)', 32)
	
	write_chapter(f, '[Array<X>]')
	for cname in data.ACLASS_LIST:
		cname = cname.replace(":", "__")
		if cname == 'Int' or cname == 'Float': continue
		write_define(f, 'ACLASS_%s' % cname, '((knh_class_t)(KNH_TCLASS_SIZE-(%d+1)))' % cn, 32)
		write_define(f, 'ATYPE_%s' % cname, 'ACLASS_%s' % cname, 32)
		write_define(f, 'NNATYPE_%s' % cname, 'NNTYPE_cidOLD(ACLASS_%s)' % cname, 32)
		cn += 1
	
	write_chapter(f, '[Iterator<X>]')
	for cname in data.ICLASS_LIST:
		cname = cname.replace(":", "__")
		write_define(f, 'ICLASS_%s' % cname, '((knh_class_t)(KNH_TCLASS_SIZE-(%d+1)))' % cn, 32)
		write_define(f, 'ITYPE_%s' % cname, 'NNTYPE_cidOLD(ICLASS_%s)' % cname, 32)
		write_define(f, 'NNITYPE_%s' % cname, 'NNTYPE_cidOLD(ICLASS_%s)' % cname, 32)
		cn += 1
	
	write_chapter(f, '[Generics]')
	for c in data.GENERICS_LIST:
		write_define(f, 'CLASS_%s' % c.cname, '((knh_class_t)(KNH_TCLASS_SIZE-(%d+1)))' % cn, 32)
		write_define(f, 'TYPE_%s' % c.cname, 'CLASS_%s' % c.cname, 32)
		write_define(f, 'NNTYPE_%s' % c.cname, 'NNTYPE_cidOLD(CLASS_%s)' % cname, 32)
		cn += 1
		
	write_chapter(f, '[Object:X]')
	for cname in data.XCLASS_LIST:
		cname = cname.replace(":", "__")
		write_define(f, 'CLASS_%s' % cname, '((knh_class_t)(KNH_TCLASS_SIZE-(%d+1)))' % cn, 32)
		write_define(f, 'TYPE_%s' % cname, 'CLASS_%s' % cname, 32)
		write_define(f, 'NNTYPE_%s' % cname, 'NNTYPE_cidOLD(CLASS_%s)' % cname, 32)
		cn += 1
	
	write_chapter(f, '[tString]')
	cn = 0
	for t in data.STEXT_LIST:
		nm = data.STEXT_MAP[t]
		write_define(f, 'TSN_%s' % nm, '%d' % cn, 32)
		write_define(f, 'TS_%s' % nm, '((ctx)->share->tString[TSN_%s])' % nm)
		cn += 1
	write_define(f, 'KNH_TSTRING_SIZE', '%d' % cn, 32)
	
	write_chapter(f, '[field]')
	write_fieldn_h(f, data)

	write_chapter(f, '[MFN]')

	cn = 0
	for n in data.MF_LIST:
		write_define(f, n, '%d' % cn, 32)
		write_define(f, n.replace('MFN_', 'MF_'), 'knh_tMethodField(ctx, %s)' % n)
		cn += 1
	write_define(f, 'KNH_TMETHODFIELD_SIZE', '%d' % cn, 32)
	
	cn = 1
	for n in data.EXPT_LIST:
		write_define(f, 'EXPT_%s' % n, '%d' % cn, 32)
		cn += 1
	
	write_chapter(f, '[KNH_CLASS_T]')
	
	for c in data.CLASS_LIST:
		if not c.struct_name.endswith("_t"):
			op = ''
			if c.cname == 'Method':   op = '\tknh_fmethod fcall_1;\n\tknh_code_t *pc_start;\n'
			if c.cname == 'Mapper':   op = '\tknh_fmapper fmap_1;\n'
			if c.cname == 'Iterator': op = '\tknh_fitrnext fnext_1;\n'
			if c.cname == 'Closure': op = '\tknh_fmethod finvoke_1;\n\tknh_fmethod fcallcc_2;\n'
			if c.cname == 'Token':    op = '\tknh_uri_t uri;\n\tknh_ushort_t line;\n\tknh_flag_t flag;\n\tknh_token_t  tt;\n'
			if c.cname == 'Stmt':     op = '\tknh_uri_t uri;\n\tknh_ushort_t line;\n\tknh_flag_t flag;\n\tknh_stmt_t  stt;\n'
			if c.cname == 'Asm':    op = '\tknh_uri_t uri;\n\tknh_ushort_t line;\n'
			if c.cname == 'KLRCode':     op = '\tknh_uri_t uri;\n\tknh_ushort_t line;\n'
			#if c.cname == 'Asm': op = '\tknh_uri_t uri;\n\tknh_ushort_t line;\n\tknh_flag_t flag;\n\tknh_ushort_t dummy;\n'
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
\t%s_%s(%s, p_bool(sfp[1]));
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
\t%s_%s(%s, p_bool(sfp[1]));
\tKNH_RETURN_void(ctx, sfp);
}
''' % (methodbase, ffn, funcbase, ffn, a1))

def write_ctable_c(f, c, data):
	return

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
\tKNH_TCLASS_PARAM(ctx, %s, CLASS_Any, CLASS_unknown);''' % (CLASS_cname(c.cname)))
	if '@Param2' in c.options:
		f.write('''
\tKNH_TCLASS_PARAM(ctx, %s, CLASS_Any, CLASS_unknown);''' % (CLASS_cname(c.cname)))
		

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
	if t.endswith("..") or t.endswith("..!") : return "Iterator"
	if t.endswith("[]") or t.endswith("[]!"): return "Array"
	return t.replace("!", "")

def CI(t):
	if t[0] == 'p': t = t[1:]
	return t.replace("!", "").replace("..", "__").replace("[]", "__A")

def write_tmapper_c(f, mm, data):
	return

def CLASS_cname2(cname):
	cname = cname.replace("!", "")
	if cname.endswith("[]") :
		return 'ACLASS_%s' % cname.replace("[]", "")
	if cname.endswith("..") :
		return 'ICLASS_%s' % cname.replace("..", "")
	return 'CLASS_%s' % cname
	
def write_mapmap_c(f, mm, data):
	if mm.mapfunc == None: return
	f.write('''
\tKNH_TMAPPER(ctx, 
\t\t%s, 
\t\t%s, %s,  
\t\t%s, %s
\t);
''' % (mm.make_flag(data), CLASS_cname2(mm.fcname), CLASS_cname2(mm.tcname), mm.mapfunc, mm.mapopt))

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
		rval = 'KNH_NULL'
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
		if p.type == 'int':
			f.write(''',
\t\tknh_stack_argc(ctx, sfp + %d),
\t\tsfp + %d''' % ((ki + 1), (ki + 1)))
			break
		if p.type == 'knh_hcode_t':
			f.write(''',
\t\tknh_Object_hashCode(Ctx *ctx, %s)''' % n)
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

def gen_class2_c(bdir, p, data):
	fname = '%s/src/gen/package/%s_.c' % (bdir, p.pname)
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
	fname = '%s/src/gen/method_.c' % (bdir)
	f = open_c(fname, ['<konoha/konoha_dev.h>'])
	
	f.write('''
#ifdef KNH_CC_METHODAPI
''')
	write_chapter(f, '[flag]')
	for c in data.CLASS_LIST:
		for fb in data.FLAG_LIST:
			if fb.cname == c.cname: write_flag_c(f, c, fb, data)
	
	write_chapter(f, '[method]')
	for mtd in data.METHOD_LIST: write_method_func_c(f, mtd, data)
	
	f.write('''
#endif/*KNH_CC_METHODAPI*/
''')
	
	close_c(f, fname)

###################

def write_structdef_h(f, c, data):
	if not c.struct_name.startswith("knh_%s_" % c.cname) or '@Field' in c.options: return
	write_chapter(f, c.cname)
	fmt = '''
#define _$CF_init NULL
#define _$CF_copy NULL 
#define _$CF_traverse NULL
#define _$CF_compareTo NULL
#define _$CF_hashCode NULL
#define _$CF_newClass NULL

'''.replace('$CF', c.funcbase).replace('_Object_', '_ObjectField_')
	f.write(fmt)

def write_structdata_c(f, c, data):
	if not c.struct_name.startswith("knh_%s_" % c.cname) or '@Field' in c.options: return
	size = '0'
	if c.struct_name.startswith("knh_%s_struct" % c.cname): size = 'sizeof(%s)' % c.struct_name
	fmt = '''
\t{
\t\t"%s", STRUCT_$C, FLAG_$C, %s,
\t\t(knh_fstruct_init)$CF_init,
\t\t(knh_fstruct_copy)$CF_copy, 
\t\t(knh_fstruct_traverse)$CF_traverse,
\t\t(knh_fstruct_compareTo)$CF_compareTo,
\t\t(knh_fstruct_hashCode)$CF_hashCode,
\t\t(knh_fstruct_newClass)$CF_newClass,
\t\t$CF_getkey
\t},'''.replace('$CF', c.funcbase).replace('$C', c.cname).replace('_Object_', '_ObjectField_')
	f.write(fmt % (c.cname, size))

def write_classdata_c(f, c, data):
	fullname = c.fullname
	if c.cname == 'IArray': fullname = 'Int[]'
	if c.cname == 'FArray': fullname = 'Float[]'
	fmt = '''
\t{"%s", CLASS_$C, CFLAG_$C, %s, %s, 0, %d, 0, knh_$C_fdefault},'''.replace('$C', c.cname)
	f.write(fmt % (fullname, STRUCT_cname(c.cname), CLASS_cname(c.super_cname), c.method_size))
	

def write_methoddata_c(f, mtd, data):
	if mtd.methodfunc == None: return
	mfindex = mtd.MF().replace('MF_', 'MFN_')
	fmt = '''
\t{%s, %s, %s, %s, 0, %s, (void*)%s},'''
	f.write(fmt % (mtd.methodfunc, mtd.make_flag(data), CLASS_cname(mtd.cname), METHODN_mname(mtd.mn), mfindex, mtd.optfunc))


def write_mapmapdata_c(f, mm, data) :
	if mm.mapfunc == None: return
	fmt = '''
\t{%s, %s, %s, %s},'''
	fmt = fmt % (mm.mapfunc, mm.make_flag(data), CLASS_cname2(mm.fcname), CLASS_cname2(mm.tcname))
	f.write(fmt)

def gen_struct_hc(bdir, data):
	fname = '%s/include/konoha/gen/struct_.h' % (bdir)
	f = open_h(fname, ['<konoha/konoha_t.h>'])

	f.write('''
static knh_StringData_t StringData[] = {''')
	for t in data.STEXT_LIST:
		nm = data.STEXT_MAP[t]
		f.write('''
\t{"%s", TSN_%s}, ''' % (t, nm))
	f.write('''
	{NULL}
};
''')
	
	f.write('''
static char* StructName[] =  {''')
	for c in data.CLASS_LIST:
		if not c.struct_name.startswith("knh_%s_" % c.cname) or '@Field' in c.options: continue
		f.write('''
	"%s",''' % c.cname);
	f.write('''
};
''')
	f.write('''
static knh_StructData_t StructData[] = {''')
	for c in data.CLASS_LIST:
		write_structdata_c(f, c, data)
	f.write('''
	{NULL}
};
''')

#	for c in data.CLASS_LIST:
#		f.write('''
#define knh_%s_fdefault NULL''' % c.cname)
	
	f.write('''
static knh_ClassData_t ClassData[] = {''')
	for c in data.CLASS_LIST:
		#if c.struct_name.startswith("knh_%s_" % c.cname) or '@Field' in c.options: continue
		write_classdata_c(f, c, data)
	f.write('''
	{NULL}
};
''')

	f.write('''
static knh_GenericsData_t GenericsData[] = {''')
	for cname in data.ICLASS_LIST:
		cname = cname.replace(":", "__")
		f.write('''
\t{"%s..", ICLASS_%s, CLASS_Iterator, CLASS_%s, CLASS_unknown},''' % (cname, cname, cname))
	for cname in data.ACLASS_LIST:
		cname = cname.replace(":", "__")
		f.write('''
\t{"%s[]", ACLASS_%s, CLASS_Array, CLASS_%s, CLASS_unknown},''' % (cname, cname, cname))
	for c in data.GENERICS_LIST:
		if c.bname == 'Closure': continue
		f.write('''
\t{"%s", CLASS_%s, CLASS_%s, CLASS_%s, CLASS_%s},''' % (c.fullname, c.cname, c.bname, c.params[0], c.params[1]))
	f.write('''
	{NULL}
};
''')

	f.write('''
static knh_ClosureData_t ClosureData[] = {''')
	for c in data.GENERICS_LIST:
		if c.bname != 'Closure': continue
		f.write('''
\t{"%s", CLASS_%s, %s, %s, %s, %s},''' % (c.fullname, c.cname, TYPE_cname(c.params[0]), TYPE_cname(c.params[1]), TYPE_cname(c.params[2]), TYPE_cname(c.params[3])))
	f.write('''
	{NULL}
};
''')
	
	f.write('''
static knh_ExptData_t ExptData[] = {''')
	for cname in data.EXPT_LIST:
		e = data.EXPT_MAP[cname]
		f.write('''
	{"%s", %s, EXPT_%s, %s},''' % (cname, e.make_flag(data), cname, e.parent.replace("!!", "")))
	f.write('''
	{NULL, 0}
};
''')

	for key in data.STATICLIB_MAP.keys():
		f.write('''
int %s(Ctx *ctx);''' % (key))

	f.write('''
static knh_FuncData_t FuncData[] = {''')
	for key in data.STATICLIB_MAP.keys():
		if key.endswith("_load"): continue
		f.write('''
	{""%s", (void*)%s},''' % (key, data.STATICLIB_MAP[key]))
	f.write('''
#ifdef KONOHA_MONOLITHIC''')
	for key in data.STATICLIB_MAP.keys():
		if not key.endswith("_load"): continue
		f.write('''
	{"%s", (void*)%s},''' % (key, data.STATICLIB_MAP[key]))
	f.write('''
#endif/*KONOHA_MONOLITHIC*/
	{NULL}
};
''')

	f.write('''
static knh_FieldNameData_t FieldNameData[] = {''')
	l = data.FIELDN_LIST
	l.sort()
	for n in l:
		f.write('''
\t{"%s", %s},''' % (n, FIELDN_name(n.replace(':','__'))))
	f.write('''
	{NULL, 0}
};
''')

	write_line(f)
	f.write('''
static knh_MethodFieldData_t MethodFieldData[] = {''')
	for n in data.MF_LIST:
		func = data.MF_MAP[n].replace("new_MethodField__", "\n\t{%s, " % n)
		func = func.replace('KNH_FLAG_MF_VARARGS', '0').replace('(', '+')
		func = func.replace(')', '},').replace('NULL,', '').replace('ctx,', '')
		f.write(func)
	f.write('''
	{-1, 0}
};
''')

	f.write('''
static knh_MethodData_t MethodData[] = {''')
	for mtd in data.METHOD_LIST: write_methoddata_c(f, mtd, data)
	f.write('''
	{NULL, 0}
};
''')

	f.write('''
static knh_MapperData_t MapperData[] = {''')
	for mm in data.MAPPER_LIST: write_mapmapdata_c(f, mm, data)
	f.write('''
	{NULL, 0}
};
''')

	f.write('''
typedef void (*knh_finit_)(Ctx *);

static knh_finit_ InitFuncData[] = {''')
	for p in data.INITFUNC_LIST:
		f.write('''
\t%s,''' % p)
	f.write('''
	NULL
};
''')
	close_h(f, fname)

