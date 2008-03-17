/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER  
 * 
 * Copyright (c) 2005-2008, Kimio Kuramitsu <kimio at ynu.ac.jp>
 *           (c) 2008-      Konoha Software Foundation  
 * All rights reserved.
 * 
 * You may choose one of the following two licenses when you use konoha. 
 * See www.konohaware.org/license.html for further information.
 * 
 * (1) GNU General Public License 2.0      (with    KONOHA_UNDER_GPL2)
 * (2) Konoha Software Foundation License 1.0
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER 
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  
 ****************************************************************************/

/* ************************************************************************ */

#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */
/* [nop] */

knh_bool_t knh_ResultSet_next__nop(Ctx *ctx, knh_rsptr_t *rsptr, ResultSet *b)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

void knh_ResultSet_free__nop(knh_rsptr_t *rsptr)
{

}

/* ======================================================================== */
/* [structs] */

void knh_ResultSet_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	ResultSet *b =  (ResultSet*)s1;
	
	b->rsptr = NULL;
	b->tcid = CLASS_ResultSet;
	b->column_size = init;
	b->column = knh_malloc(ctx, sizeof(knh_rscolumn_t) * b->column_size);
	int i = 0;
	for(i = 0; i < b->column_size; i++) {
		b->column[i].type = CLASS_Object;
		KNH_INITv(b->column[i].name, knh_String_EMPTY());
		b->column[i].start = 0;
		b->column[i].len = 0;
	}
	KNH_INITv(b->databuf, new_Bytes(ctx, 256));
	
//	b->drv.fnext = knh_ResultSet_next__nop;
//	b->drv.ffree = knh_ResultSet_free__nop;
}

/* ------------------------------------------------------------------------ */

#define _knh_ResultSet_struct_copy NULL

/* ------------------------------------------------------------------------ */

#define _knh_ResultSet_struct_compare NULL

/* ------------------------------------------------------------------------ */

void knh_ResultSet_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	ResultSet *b = (ResultSet*)s;
	gc(ctx, b->databuf);
	int i = 0;
	for(i = 0; i < b->column_size; i++) {
		gc(ctx, b->column[i].name);
	}
	if(IS_SWEEP(gc)) {
		knh_free(b->column, sizeof(knh_rscolumn_t) * b->column_size);
		b->column = NULL;
		b->drv.ffree(b->rsptr);
		b->rsptr = NULL;			
	}
}

/* ======================================================================== */
/* [constructors] */


ResultSet* new_ResultSet(Ctx *ctx, size_t column_size, knh_rsptr_t *rsptr, f_rsptr_next fnext, f_rsptr_free ffree)
{
	ResultSet *b = (ResultSet*)knh_Object_malloc0(ctx, KNH_FLAG_ResultSet, CLASS_ResultSet, sizeof(knh_ResultSet));	
	knh_ResultSet_struct_init(ctx, (Struct*)b, column_size, NULL);
	b->rsptr = rsptr;
	b->drv.fnext = fnext;
	b->drv.ffree = ffree;
	return b;
}


/* ======================================================================== */
/* [next] */

/* ------------------------------------------------------------------------ */
/* @method ResultSet ResultSet.next() */

ResultSet *knh_ResultSet_next(Ctx *ctx, ResultSet *b)
{
	if(b->drv.fnext(ctx, b->rsptr, b)) {
		return b;
	}
	return KNH_NULL;
}

/* ======================================================================== */
/* [iterators] */

Object* knh_ResultSet_it_next(Ctx *ctx, Iterator *it)
{
	ResultSet *b = (ResultSet*)knh_Iterator_source(it);
	if(b->drv.fnext(ctx, b->rsptr, b)) {
		if(b->tcid == CLASS_ResultSet) {
			return b;
		}
		TODO();
	}
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */
/* @map ResultSet Iterator */

Object* knh_ResultSet_Iterator(Ctx *ctx, Object *self, MapMap *map)
{
	return new_Iterator(ctx, ((ResultSet*)self)->tcid, self, knh_ResultSet_it_next);
}


/* ======================================================================== */
/* [meta] */

void knh_ResultSet_initTargetClass(ResultSet *b, knh_class_t tcid)
{
	b->tcid = tcid;
}

/* ------------------------------------------------------------------------ */

void knh_ResultSet_initMetaInfo(Ctx *ctx, ResultSet *b, size_t n, knh_type_t type, String *name)
{
	DEBUG_ASSERT(n < b->column_size);
	b->column[n].type = type;
	KNH_SETv(ctx, b->column[n].name, name);
}

/* ------------------------------------------------------------------------ */

knh_index_t knh_ResultSet_index(Ctx *ctx, ResultSet *b, knh_bytes_t name)
{
	knh_index_t i = 0;
	for(i = 0; i < b->column_size; i++) {
		if(knh_String_equals(b->column[i].name, name)) return i;
	}
	return -1;
}

/* ------------------------------------------------------------------------ */

String *knh_ResultSet_getName(Ctx *ctx, ResultSet *b, size_t n)
{
	DEBUG_ASSERT(n < b->column_size);
	return b->column[n].name;
}

/* ------------------------------------------------------------------------ */

knh_type_t knh_ResultSet_get_type(Ctx *ctx, ResultSet *b, size_t n)
{
	DEBUG_ASSERT(n < b->column_size);
	return b->column[n].type;
}

/* ======================================================================== */
/* [set] */

void knh_ResultSet_initData(Ctx *ctx, ResultSet *b)
{
	int i = 0;
	for(i = 0; i < b->column_size; i++) {
		b->column[i].ctype = 0;
		b->column[i].start = 0;
		b->column[i].len = 0;
	}
	knh_Bytes_clear(b->databuf);
}

/* ------------------------------------------------------------------------ */

void knh_ResultSet_set__int(Ctx *ctx, ResultSet *b, size_t n, knh_int_t value)
{
	DEBUG_ASSERT(n < b->column_size);
	knh_bytes_t t = {(knh_uchar_t*)(&value), sizeof(knh_int_t)};
	b->column[n].ctype = knh_ResultSet_CTYPE__int;
	b->column[n].start = knh_Bytes_size(b->databuf);
	b->column[n].len = sizeof(knh_int_t);
	knh_Bytes_write(ctx, b->databuf, t);
}

/* ------------------------------------------------------------------------ */

void knh_ResultSet_set__float(Ctx *ctx, ResultSet *b, size_t n, knh_float_t value)
{
	DEBUG_ASSERT(n < b->column_size);
	knh_bytes_t t = {(knh_uchar_t*)(&value), sizeof(knh_float_t)};
	b->column[n].ctype = knh_ResultSet_CTYPE__float;
	b->column[n].start = knh_Bytes_size(b->databuf);
	b->column[n].len = sizeof(knh_float_t);
	knh_Bytes_write(ctx, b->databuf, t);
	int i, c = t.len % sizeof(void*);
	for(i = 0; i < c; i++) knh_Bytes_putc(ctx, b->databuf, 0);    /* zero */
}

/* ------------------------------------------------------------------------ */

void knh_ResultSet_set__int64(Ctx *ctx, ResultSet *b, size_t n, knh_int64_t value)
{
	DEBUG_ASSERT(n < b->column_size);
	knh_bytes_t t = {(knh_uchar_t*)(&value), sizeof(knh_int64_t)};
	b->column[n].ctype = knh_ResultSet_CTYPE__int64;	
	b->column[n].start = knh_Bytes_size(b->databuf);
	b->column[n].len = sizeof(knh_int64_t);
	knh_Bytes_write(ctx, b->databuf, t);
}

/* ------------------------------------------------------------------------ */

void knh_ResultSet_set__bytes(Ctx *ctx, ResultSet *b, size_t n, knh_bytes_t t)
{
	DEBUG_ASSERT(n < b->column_size);
	b->column[n].ctype = knh_ResultSet_CTYPE__bytes;
	b->column[n].start = knh_Bytes_size(b->databuf);
	b->column[n].len = t.len;
	knh_Bytes_write(ctx, b->databuf, t);
	int i, c = t.len % sizeof(void*);
	for(i = 0; i < c; i++) knh_Bytes_putc(ctx, b->databuf, 0);    /* zero */
}

/* ------------------------------------------------------------------------ */

void knh_ResultSet_set__null(Ctx *ctx, ResultSet *b, size_t n)
{
	DEBUG_ASSERT(n < b->column_size);
	b->column[n].ctype = knh_ResultSet_CTYPE__null;
	b->column[n].start = knh_Bytes_size(b->databuf);
	b->column[n].len = 0;
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_ResultSet_get__int(Ctx *ctx, ResultSet *b, size_t n)
{
	DEBUG_ASSERT(n < b->column_size);
	char *p = knh_Bytes_tochar(b->databuf) + b->column[n].start;
	switch(b->column[n].ctype) {
	case knh_ResultSet_CTYPE__null :
		return 0;
	case knh_ResultSet_CTYPE__int :
		return (knh_int_t)(*((knh_int_t*)p));
	case knh_ResultSet_CTYPE__float :
		return (knh_int_t)(*((knh_float_t*)p));
	case knh_ResultSet_CTYPE__int64 :
		return (knh_int_t)(*((knh_int64_t*)p));
	case knh_ResultSet_CTYPE__bytes :
		return knh_bytes_toint(B2(p, b->column[n].len));
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

knh_float_t knh_ResultSet_get__float(Ctx *ctx, ResultSet *b, size_t n)
{
	DEBUG_ASSERT(n < b->column_size);
	char *p = knh_Bytes_tochar(b->databuf) + b->column[n].start;
	switch(b->column[n].ctype) {
	case knh_ResultSet_CTYPE__null :
		return 0.0;
	case knh_ResultSet_CTYPE__int :
		return (knh_float_t)(*((knh_int_t*)p));
	case knh_ResultSet_CTYPE__float :
		return (knh_float_t)(*((knh_float_t*)p));
	case knh_ResultSet_CTYPE__int64 :
		return (knh_float_t)(*((knh_int64_t*)p));
	case knh_ResultSet_CTYPE__bytes :
		return knh_bytes_tofloat(B2(p, b->column[n].len));
	}
	return 0.0;
}

/* ------------------------------------------------------------------------ */

knh_int64_t knh_ResultSet_get__int64(Ctx *ctx, ResultSet *b, size_t n)
{
	char *p = knh_Bytes_tochar(b->databuf) + b->column[n].start;
	switch(b->column[n].ctype) {
	case knh_ResultSet_CTYPE__null :
		return 0L;
	case knh_ResultSet_CTYPE__int :
		return (knh_int64_t)(*((knh_int_t*)p));
	case knh_ResultSet_CTYPE__float :
		return (knh_int64_t)(*((knh_float_t*)p));
	case knh_ResultSet_CTYPE__int64 :
		return (knh_int64_t)(*((knh_int64_t*)p));
	case knh_ResultSet_CTYPE__bytes :
		return knh_bytes_toint64(B2(p, b->column[n].len));
	}
	return 0L;
}

/* ------------------------------------------------------------------------ */
/* @method Any ResultSet.get(Int! n) */

Object *knh_ResultSet_get(Ctx *ctx, ResultSet *b, size_t n)
{
	Object *v;
	knh_class_t cid = TYPE_UNMASK(b->column[n].type);
	knh_class_t bcid = knh_tclass_bcid(cid);
	switch(bcid) {
	case CLASS_Int :
		v = new_Int__checked(ctx, cid, knh_ResultSet_get__int(ctx, b, n));
		if(IS_NULL(v) && TYPE_ISNOTNULL(b->column[n].type)) {
			KNH_SAFEFREE(ctx, v);
			TODO();
			return knh_tclass_value(ctx, cid, NULL);
		}
		return v;
	case CLASS_Float :
		v = new_Float__checked(ctx, cid, knh_ResultSet_get__float(ctx, b, n));
		if(IS_NULL(v) && TYPE_ISNOTNULL(b->column[n].type)) {
			KNH_SAFEFREE(ctx, v);
			TODO();
			return knh_tclass_value(ctx, cid, NULL);
		}
		return v;
	case CLASS_Int64 :
		v = new_Int64__checked(ctx, cid, knh_ResultSet_get__int64(ctx, b, n));
		if(IS_NULL(v) && TYPE_ISNOTNULL(b->column[n].type)) {
			KNH_SAFEFREE(ctx, v);
			TODO();
			return knh_tclass_value(ctx, cid, NULL);
		}
		return v;
#ifdef CLASS_Decimal
	case CLASS_Decimal :
		TODO();
		return KNH_NULL;
#endif
	case CLASS_String :
		v = new_String__checked(ctx, cid, B2(knh_Bytes_tochar(b->databuf) + b->column[n].start, b->column[n].len));
		if(IS_NULL(v) && TYPE_ISNOTNULL(b->column[n].type)) {
			KNH_SAFEFREE(ctx, v);
			TODO();
			return knh_tclass_value(ctx, cid, NULL);
		}
		return v;
	}
	DEBUG("unsupported type cid=%s, bcid=%s", CLASSN(cid), CLASSN(bcid));
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */
/* @method void ResultSet.%dump(OutputStream w, Any m) */

void knh_ResultSet__dump(Ctx *ctx, ResultSet *b, OutputStream *w, Any *m)
{
	knh_putc(ctx, w, '[');
	size_t n;
	for(n = 0; n < b->column_size; n++) {
		if(n > 0) {
			knh_write_delim(ctx,w);
		}
		char *p = knh_Bytes_tochar(b->databuf) + b->column[n].start;
		switch(b->column[n].ctype) {
			case knh_ResultSet_CTYPE__null :
				knh_write(ctx, w, STEXT("null"));
				break;
			case knh_ResultSet_CTYPE__int :
				knh_write__i(ctx, w, (knh_int_t)(*((knh_int_t*)p)));
				break;
			case knh_ResultSet_CTYPE__float :
				knh_write__f(ctx, w, (knh_float_t)(*((knh_float_t*)p)));
				break;
			case knh_ResultSet_CTYPE__int64 :
				TODO();
				/*knh_write__l(ctx, w, (knh_int64_t)(*((knh_int64_t*)p))); */
				break;
			case knh_ResultSet_CTYPE__bytes :
				knh_write(ctx, w, B2(p, b->column[n].len));
				break;
		}
	}
	knh_putc(ctx, w, ']');
}

/* ======================================================================== */
/* [TFUNC] */

void
KNH_TFUNC_RESULTSET_NEXT(Ctx *ctx, char *n, f_rsptr_next f)
{
	if(f == NULL) f = knh_ResultSet_next__nop;
	KNH_TFUNC(ctx, n, (void*)f);
}

/* ------------------------------------------------------------------------ */

void
KNH_TFUNC_RESULTSET_FREE(Ctx *ctx, char *n, f_rsptr_free f)
{
	if(f == NULL) f = knh_ResultSet_free__nop;
	KNH_TFUNC(ctx, n, (void*)f);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
