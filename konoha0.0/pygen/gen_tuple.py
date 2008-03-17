#!/usr/bin/python
import os, sys
from pygenlib  import *
from CONFIG import *

def write_tuple_h(f, n):
	f.write('''
void knh_Tuple%d_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Tuple%d_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Tuple%d_struct_compare(Ctx *ctx, Struct *s, Struct *s2); 
void knh_Tuple%d_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);'''.replace('%d', '%d' % n))

def write_tuple_c(f, n):
	f.write('''
void knh_Tuple%d_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
\tTuple%d *b  = (Tuple%d*)s;
\tif(cs == NULL) {''' % (n, n, n))
	for i in range(n):
		f.write('''
\t\tKNH_INITv(b->v[%d], KNH_NULL);''' % (i))
	f.write('''
\t}else {''')
	for i in range(n):
		f.write('''
\t\tKNH_INITv(b->v[%d], knh_ClassStruct_safevalue(ctx, cs, %d));''' % (i, i))
	f.write('''
\t}
}

/* ------------------------------------------------------------------------ */
void knh_Tuple%d_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
\tTuple%d *b  = (Tuple%d*)s;
\tTuple%d *b2 = (Tuple%d*)s2;''' % (n, n, n, n, n))
	for i in range(n):
		f.write('''
\tKNH_SETv(ctx, b2->v[%d], b->v[%d]);''' % (i, i))
	f.write('''
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Tuple%d_struct_compare(Ctx *ctx, Struct *s, Struct *s2)
{
\tTuple%d *b  = (Tuple%d*)s;
\tTuple%d *b2 = (Tuple%d*)s2;
\tknh_int_t res;''' % (n, n, n, n, n))
	for i in range(n):
		f.write('''
\tres = knh_Object_compare(ctx, b->v[%d], b2->v[%d]);
\tif(res != 0) return res;''' % (i, i))
	f.write('''
\treturn res;
}

/* ------------------------------------------------------------------------ */

void knh_Tuple%d_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
\tTuple%d *b  = (Tuple%d*)s;''' % (n, n, n))
	for i in range(n):
		f.write('''
\tgc(ctx, b->v[%d]);''' % (i))
	f.write('''
}
''')

# ---------------------------------------------------------------------------

def gen_tuple(bdir):
	fname = '%s/include/konoha/konoha_tuple_.h' % bdir
	f = open_h(fname, ['<konoha/konoha_t.h>'])
	for n in range(1, 16):
		write_tuple_h(f, n)
	close_h(f, fname)

	fname = '%s/gen/konoha_tuple_.c' % bdir
	f = open_c(fname, ['<konoha/konoha_dev.h>'])
	for n in range(1, 16):
		write_tuple_c(f, n)
	close_c(f, fname)

# ---------------------------------------------------------------------------

if __name__ == '__main__':
	bdir = '..'
	gen_tuple(bdir)
