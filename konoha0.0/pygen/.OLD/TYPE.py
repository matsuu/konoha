import sys, os

###################################################################################

NEW_DEFVAL = {
	'Writer': 'Context_writer(ctx)' 
}


TYPE_DEFVAL = {


}

DEFVAL = {
	'stdout': 'knh_Context_out(ctx)',
	'stderr': 'knh_Context_err(ctx)',
	'stdin':  'knh_Context_in(ctx)',
	'true':   'KNH_TRUE',
	'false':  'KNH_FALSE'
}

TYPEMAP = {
	'Bool/knh_bool_t':    'IS_TRUE(%s)',
	'Int/knh_int_t':      'knh_Int_value((Int*)%s)',
	'Int/knh_uint_t':     '(knh_uint_t)knh_Int_value((Int*)%s)',
	'Int/knh_size_t':     '(knh_size_t)knh_Int_value((Int*)%s)',
    'Int/size_t':        '(size_t)knh_Int_value((Int*)%s)',
	'Float/knh_float_t':  'knh_Float_value((Float*)%s)',
	'Float/float':    '(float)knh_Float_value((Float*)%s)',

	'String/char*':   'knh_String_tochar(%s)',
	'String/knh_bytes_t' : 'knh_Object_tobytes(ctx, %s)', # in case of Null
	'String/knh_methodn_t' : 
		'knh_tmethodn_forname(ctx, knh_String_tobytes(%s), METHODN_NONAME)', 

	'Bytes/knh_size_t' : 'knh_Bytes_size(%s)',
	'Bytes/knh_bytes_t' : 'knh_Bytes_tobytes(%s)',

	'Class/knh_class_t' : 'knh_Class_class((Class*)%s)',
	'Class/knh_type_t':   'knh_Class_type((Class*)%s)',
	'Any/knh_hcode_t':    'knh_Object_hcode(ctx,%s)',

	'Object/knh_bytes_t':  'knh_Object_tobytes(ctx, %s)',
	'Object/f_map':   'knh_mapping_util_func(ctx,%s)', 

	'void/void':       '%s',
	'Object*/Object1': '%s',
	'Object*/Object2': '%s',

	'knh_bool_t/Bool':     'new_Bool(ctx, %s)',
	'knh_int_t/Int':       'new_Int(ctx, %s)',
	'knh_size_t/Int':      'new_Int(ctx, %s)',
    'size_t/Int':         'new_Int(ctx, %s)',
	'int/Int':            'new_Int(ctx, %s)',
	'knh_uint_t/Int':      'new_Int(ctx, %s)',
	'knh_index_t/Int':     'new_Int(ctx, %s)',

	'knh_float_t/Float':   'new_Float(ctx, %s)',
	'float/Float':        'new_Float(ctx, %s)',

	'char*/String':       'new_String__fast(ctx, B(%s))',
	'knh_class_t/Class':   'new_Class__type(ctx, %s)', 
	'knh_type_t/Class':    'new_Class__type(ctx, %s)',
}

SKIP = {
	'String/knh_bytes_t*': 0,
	'Any/knh_hcode_t': 0,
	'Any1/knh_hcode_t': 0,
	'Object/f_mapmap' : 0,
}

STATIC = {
	'Context':  '((Context*)ctx)',
}

###################################################################################

def nz_ctype(ctype):
	pf = ''
	if ctype.endswith('**'): pf = '**'
	elif ctype.endswith('*'): pf = '*'
	if ctype.startswith('Object'): ctype = 'Any'
	if ctype.startswith('Any'): ctype = 'Any'
	return ctype.replace('*', '') + pf

def nz_cname(cname):
	return cname

def nz_mtype(mtype):
	if mtype.startswith('Object'): mtype = 'Object'
	if mtype.startswith('Any'): mtype = 'Any'
	if mtype.endswith('..'): return 'Iterator'
	if mtype.endswith('[]'): return 'Array'
	if mtype.find(':') > 0: return mtype[mtype.find(':'):]
	return mtype.replace('!','')

def isObjectType(ctype, mtype):
	return ctype[0].isupper() and ctype.endswith('*')

def defaultValue(mtype, mvalue):
	if mvalue == 'new': 
		if NEW_DEFVAL.has_key(mtype):
			return NEW_DEFVAL[mtype]
		return 'new_%s(ctx)' % mtype
	if TYPE_DEFVAL.has_key(mtype):
		return TYPE_DEFVAL[mtype] % mvalue
	if DEFVAL.has_key(mvalue): return DEFVAL[defvalue]
	return 'TO_SET_DEFVAL(%s, %s)' % (mtype, mvalue);

def nz_cast(ctype, nc, sfv):
	if ctype.endswith('**'): return '(%s)%s' % (ctype, sfv)
	ctype = ctype.replace('*', '')
	if ctype.startswith("Any") : ctype = 'Object'
	return 'KNH_CAST_%s%s(ctx, %s)' % (ctype, nc, sfv)

def convToC(ctype, mtype, mvalue, sfv):
	if ctype == 'knh_vargc_t': return 'knh_stackf_argc(ctx, &(%s))' % sfv
	if ctype.endswith('**'): sfv = '&(%s)' % sfv
	if isObjectType(ctype, mtype):
		if mvalue is None:
			nc = ''
			if not mtype.endswith('!'): nc = 'OrNull'
			return nz_cast(ctype, nc, sfv)
		return 'IS_NULL(%s) ? %s : %s' % (sfv, defaultValue(mtype, mvalue), nz_cast(ctype, '', sfv))

	key = '%s/%s' % (nz_mtype(mtype), ctype)
	if TYPEMAP.has_key(key): 
		value = TYPEMAP[key] % sfv
	else:
		print 'Cast!!: %s' % key
		value = 'TO_SET_TYPEMAP("%s", %s)' % (key, sfv);
	if mvalue is not None:
		return 'IS_NULL(%s) ? (%s)%s : %s' % (sfv, ctype, mvalue, value)
	return value

###################################################################################

def cskip(ctype, mtype):
	if ctype == 'knh_vargc_t': return 0
	mtype = nz_mtype(mtype)
	key = '%s/%s' % (mtype, ctype)
	if SKIP.has_key(key): return SKIP[key]
	return 1

###################################################################################

def convTokonoha(ctype, mtype, rval):
	if isObjectType(ctype, mtype):
		nc = ''
		if not mtype.endswith('!'): nc = 'OrNull'
		return nz_cast(ctype, nc, rval)
	mtype = nz_mtype(mtype)
	key = '%s/%s' % (ctype, mtype)
	if TYPEMAP.has_key(key): return TYPEMAP[key] % rval
	print 'Cast!!: %s' % key
	return 'TO_SET_TYPEMAP("%s", %s); ' % (key, rval)

###################################################################################

