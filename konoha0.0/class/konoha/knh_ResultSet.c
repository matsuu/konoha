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
/* [structs] */

void knh_ResultSet_struct_init(Ctx *ctx, knh_ResultSet_struct *b, int init, Object *cs)
{
	b->rsetptr = NULL;
	b->tcid = CLASS_ResultSet;
	b->column_size = init;
	b->column = (knh_rscolumn_t*)KNH_MALLOC(ctx, sizeof(knh_rscolumn_t) * b->column_size);
	int i = 0;
	for(i = 0; i < b->column_size; i++) {
		b->column[i].type = CLASS_Object;
		KNH_INITv(b->column[i].name, TS_EMPTY);
		b->column[i].start = 0;
		b->column[i].len = 0;
	}
	KNH_INITv(b->databuf, new_Bytes(ctx, 256));
	KNH_INITv(b->conn, KNH_NULL);
	b->count = 0;
}

/* ------------------------------------------------------------------------ */

#define _knh_ResultSet_struct_copy NULL

/* ------------------------------------------------------------------------ */

#define _knh_ResultSet_struct_compare NULL

/* ------------------------------------------------------------------------ */

void knh_ResultSet_struct_traverse(Ctx *ctx, knh_ResultSet_struct *b, f_traverse ftr)
{
	ftr(ctx, UP(b->databuf));
	int i = 0;
	for(i = 0; i < b->column_size; i++) {
		ftr(ctx, UP(b->column[i].name));
	}
	if(IS_SWEEP(ftr)) {
		KNH_FREE(b->column, sizeof(knh_rscolumn_t) * b->column_size);
		b->column = NULL;
		b->free_rset(b->rsetptr);
		b->rsetptr = NULL;
	}
	ftr(ctx, UP(b->conn));
}

/* ======================================================================== */
/* [constructors] */

KNHAPI(ResultSet*) new_ResultSet(Ctx *ctx, Connection *conn, size_t column_size, knh_rshdlr_t *rsptr)
{
	ResultSet *o = (ResultSet*)new_Object_malloc(ctx, FLAG_ResultSet, CLASS_ResultSet, sizeof(knh_ResultSet_struct));
	knh_ResultSet_struct_init(ctx, DP(o), column_size, NULL);
	KNH_SETv(ctx, DP(o)->conn, conn);
	DP(o)->rsetptr = rsptr;
	DP(o)->free_rset = DP(conn)->df->free_rset;
	return o;
}

/* ======================================================================== */
/* [next] */

/* ------------------------------------------------------------------------ */
/* @method ResultSet ResultSet.next() */

ResultSet *knh_ResultSet_next(Ctx *ctx, ResultSet *o)
{
	if(DP(DP(o)->conn)->df->next_rset(ctx, DP(o)->rsetptr, o)) {
		DP(o)->count += 1;
		return o;
	}
	return (ResultSet*)KNH_NULL;
}

///* ======================================================================== */
///* [iterators] */
//
//static
//Object* knh_ResultSet_it_next(Ctx *ctx, Iterator *it)
//{
//	ResultSet *o = (ResultSet*)knh_Iterator_source(it);
//	if(DP(o)->api.fnext(ctx, DP(o)->rsetptr, o)) {
//		return (Object*)o;
//	}
//	return (Object*)KNH_NULL;
//}
//
///* ------------------------------------------------------------------------ */
///* @map ResultSet ResultSet.. */
//
//Object* knh_ResultSet_Iterator(Ctx *ctx, Object *o, Mapper *mpr)
//{
//	return new_Iterator(ctx, CLASS_ResultSet, o, knh_ResultSet_it_next);
//}

/* ======================================================================== */
/* [meta] */

void knh_ResultSet_initTargetClass(ResultSet *o, knh_class_t tcid)
{
	DP(o)->tcid = tcid;
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_ResultSet_initMetaInfo(Ctx *ctx, ResultSet *o, size_t n, knh_type_t type, String *name)
{
	KNH_ASSERT(n < DP(o)->column_size);
	DP(o)->column[n].type = type;
	KNH_SETv(ctx, DP(o)->column[n].name, name);
}

/* ------------------------------------------------------------------------ */

knh_index_t knh_ResultSet_index(Ctx *ctx, ResultSet *o, knh_bytes_t name)
{
	knh_index_t i = 0;
	for(i = 0; i < DP(o)->column_size; i++) {
		if(knh_String_equals(DP(o)->column[i].name, name)) return i;
	}
	return -1;
}

/* ------------------------------------------------------------------------ */

String *knh_ResultSet_getName(Ctx *ctx, ResultSet *o, size_t n)
{
	KNH_ASSERT(n < DP(o)->column_size);
	return DP(o)->column[n].name;
}

/* ------------------------------------------------------------------------ */

knh_type_t knh_ResultSet_get_type(Ctx *ctx, ResultSet *o, size_t n)
{
	KNH_ASSERT(n < DP(o)->column_size);
	return DP(o)->column[n].type;
}

/* ======================================================================== */
/* [set] */

KNHAPI(void) knh_ResultSet_initData(Ctx *ctx, ResultSet *o)
{
	int i = 0;
	for(i = 0; i < DP(o)->column_size; i++) {
		DP(o)->column[i].ctype = 0;
		DP(o)->column[i].start = 0;
		DP(o)->column[i].len = 0;
	}
	knh_Bytes_clear(DP(o)->databuf);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_ResultSet_setInt(Ctx *ctx, ResultSet *o, size_t n, knh_int_t value)
{
	KNH_ASSERT(n < DP(o)->column_size);
	knh_bytes_t t = {(knh_uchar_t*)(&value), sizeof(knh_int_t)};
	DP(o)->column[n].ctype = knh_ResultSet_CTYPE__int;
	DP(o)->column[n].start = knh_Bytes_size(DP(o)->databuf);
	DP(o)->column[n].len = sizeof(knh_int_t);
	knh_Bytes_write(ctx, DP(o)->databuf, t);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_ResultSet_setFloat(Ctx *ctx, ResultSet *o, size_t n, knh_float_t value)
{
	KNH_ASSERT(n < DP(o)->column_size);
	knh_bytes_t t = {(knh_uchar_t*)(&value), sizeof(knh_float_t)};
	DP(o)->column[n].ctype = knh_ResultSet_CTYPE__float;
	DP(o)->column[n].start = knh_Bytes_size(DP(o)->databuf);
	DP(o)->column[n].len = sizeof(knh_float_t);
	knh_Bytes_write(ctx, DP(o)->databuf, t);
	int i, c = t.len % sizeof(void*);
	for(i = 0; i < c; i++) knh_Bytes_putc(ctx, DP(o)->databuf, 0);    /* zero */
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_ResultSet_setInt64(Ctx *ctx, ResultSet *o, size_t n, knh_int64_t value)
{
	KNH_ASSERT(n < DP(o)->column_size);
	knh_bytes_t t = {(knh_uchar_t*)(&value), sizeof(knh_int64_t)};
	DP(o)->column[n].ctype = knh_ResultSet_CTYPE__int64;
	DP(o)->column[n].start = knh_Bytes_size(DP(o)->databuf);
	DP(o)->column[n].len = sizeof(knh_int64_t);
	knh_Bytes_write(ctx, DP(o)->databuf, t);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_ResultSet_setBytes(Ctx *ctx, ResultSet *o, size_t n, knh_bytes_t t)
{
	KNH_ASSERT(n < DP(o)->column_size);
	DP(o)->column[n].ctype = knh_ResultSet_CTYPE__bytes;
	DP(o)->column[n].start = knh_Bytes_size(DP(o)->databuf);
	DP(o)->column[n].len = t.len;
	knh_Bytes_write(ctx, DP(o)->databuf, t);
	int i, c = t.len % sizeof(void*);
	for(i = 0; i < c; i++) knh_Bytes_putc(ctx, DP(o)->databuf, 0);    /* zero */
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_ResultSet_setNULL(Ctx *ctx, ResultSet *o, size_t n)
{
	KNH_ASSERT(n < DP(o)->column_size);
	DP(o)->column[n].ctype = knh_ResultSet_CTYPE__null;
	DP(o)->column[n].start = knh_Bytes_size(DP(o)->databuf);
	DP(o)->column[n].len = 0;
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_ResultSet_getInt(Ctx *ctx, ResultSet *o, size_t n)
{
	KNH_ASSERT(n < DP(o)->column_size);
	char *p = knh_Bytes_tochar(DP(o)->databuf) + DP(o)->column[n].start;
	switch(DP(o)->column[n].ctype) {
	case knh_ResultSet_CTYPE__null :
		return 0;
	case knh_ResultSet_CTYPE__int :
		return (knh_int_t)(*((knh_int_t*)p));
	case knh_ResultSet_CTYPE__float :
		return (knh_int_t)(*((knh_float_t*)p));
	case knh_ResultSet_CTYPE__int64 :
		return (knh_int_t)(*((knh_int64_t*)p));
	case knh_ResultSet_CTYPE__bytes :
		TODO();
//		return knh_bytes_toint(B2(p, DP(o)->column[n].len));
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

knh_float_t knh_ResultSet_getFloat(Ctx *ctx, ResultSet *o, size_t n)
{
	KNH_ASSERT(n < DP(o)->column_size);
	char *p = knh_Bytes_tochar(DP(o)->databuf) + DP(o)->column[n].start;
	switch(DP(o)->column[n].ctype) {
	case knh_ResultSet_CTYPE__null :
		return 0.0;
	case knh_ResultSet_CTYPE__int :
		return (knh_float_t)(*((knh_int_t*)p));
	case knh_ResultSet_CTYPE__float :
		return (knh_float_t)(*((knh_float_t*)p));
	case knh_ResultSet_CTYPE__int64 :
		return (knh_float_t)(*((knh_int64_t*)p));
	case knh_ResultSet_CTYPE__bytes :
		TODO();
//		return knh_bytes_tofloat(B2(p, DP(o)->column[n].len));
	}
	return 0.0;
}

/* ------------------------------------------------------------------------ */

knh_int64_t knh_ResultSet_getInt64(Ctx *ctx, ResultSet *o, size_t n)
{
	char *p = knh_Bytes_tochar(DP(o)->databuf) + DP(o)->column[n].start;
	switch(DP(o)->column[n].ctype) {
	case knh_ResultSet_CTYPE__null :
		return 0L;
	case knh_ResultSet_CTYPE__int :
		return (knh_int64_t)(*((knh_int_t*)p));
	case knh_ResultSet_CTYPE__float :
		return (knh_int64_t)(*((knh_float_t*)p));
	case knh_ResultSet_CTYPE__int64 :
		return (knh_int64_t)(*((knh_int64_t*)p));
	case knh_ResultSet_CTYPE__bytes :
		TODO();
//		return knh_bytes_toint64(B2(p, DP(o)->column[n].len));
	}
	return 0L;
}

///* ------------------------------------------------------------------------ */
///* @method Any ResultSet.get(Int! n) */
//
//Object *knh_ResultSet_get(Ctx *ctx, ResultSet *o, size_t n)
//{
//	Object *v;
//	knh_class_t cid = TYPE_UNMASK(DP(o)->column[n].type);
//	knh_class_t bcid = knh_tClass[cid].bcid;
//	switch(bcid) {
//	case CLASS_Int :
//		v = new_IntX(ctx, cid, knh_ResultSet_get__int(ctx, b, n));
//		if(IS_NULL(v) && TYPE_ISNOTNULL(DP(o)->column[n].type)) {
//			KNH_SAFEFREE(ctx, v);
//			TODO();
//			return knh_tclass_value(ctx, cid, NULL);
//		}
//		return v;
//	case CLASS_Float :
//		v = new_FloatX(ctx, cid, knh_ResultSet_get__float(ctx, b, n));
//		if(IS_NULL(v) && TYPE_ISNOTNULL(DP(o)->column[n].type)) {
//			KNH_SAFEFREE(ctx, v);
//			TODO();
//			return knh_tclass_value(ctx, cid, NULL);
//		}
//		return v;
//	case CLASS_Int64 :
//		v = new_Int64X(ctx, cid, knh_ResultSet_get__int64(ctx, b, n));
//		if(IS_NULL(v) && TYPE_ISNOTNULL(DP(o)->column[n].type)) {
//			KNH_SAFEFREE(ctx, v);
//			TODO();
//			return knh_tclass_value(ctx, cid, NULL);
//		}
//		return v;
//#ifdef CLASS_Decimal
//	case CLASS_Decimal :
//		TODO();
//		return KNH_NULL;
//#endif
//	case CLASS_String :
//		v = new_String__checked(ctx, cid, B2(knh_Bytes_tochar(DP(o)->databuf) + DP(o)->column[n].start, DP(o)->column[n].len));
//		if(IS_NULL(v) && TYPE_ISNOTNULL(DP(o)->column[n].type)) {
//			KNH_SAFEFREE(ctx, v);
//			TODO();
//			return knh_tclass_value(ctx, cid, NULL);
//		}
//		return v;
//	case CLASS_Object :
//		{
//			char *p = knh_Bytes_tochar(DP(o)->databuf) + DP(o)->column[n].start;
//			switch(DP(o)->column[n].ctype) {
//				case knh_ResultSet_CTYPE__int :
//					return new_Int(ctx, (knh_int_t)(*((knh_int_t*)p)));
//				case knh_ResultSet_CTYPE__float :
//					return new_Float(ctx, (knh_float_t)(*((knh_float_t*)p)));
//				case knh_ResultSet_CTYPE__int64 :
//					TODO();
//					return KNH_NULL;
//				case knh_ResultSet_CTYPE__bytes :
//					return new_StringX__fast(ctx, CLASS_String, B2(p, DP(o)->column[n].len));
//			}
//			return KNH_NULL;
//		}
//	}
//	DBG2_P("unsupported type cid=%s, bcid=%s", CLASSN(cid), CLASSN(bcid));
//	return KNH_NULL;
//}

/* ------------------------------------------------------------------------ */
/* @method void ResultSet.%dump(OutputStream w, Any m) */

void knh_ResultSet__dump(Ctx *ctx, ResultSet *o, OutputStream *w, Any *m)
{
	knh_putc(ctx, w, '[');
	size_t n;
	for(n = 0; n < DP(o)->column_size; n++) {
		if(n > 0) {
			knh_write_delim(ctx,w);
		}
		char *p = knh_Bytes_tochar(DP(o)->databuf) + DP(o)->column[n].start;
		switch(DP(o)->column[n].ctype) {
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
				knh_write(ctx, w, B2(p, DP(o)->column[n].len));
				break;
		}
	}
	knh_putc(ctx, w, ']');
}

///* ======================================================================== */
///* [SequenceMapper] */
//
//int knh_resultset_index(Ctx *ctx, Tuple *t, Object **index[], int j, int e)
//{
//	int i;
//	knh_class_t cid = knh_Object_cid(t);
//	for(i = 0; i <knh_tclass_bsize(cid); i++) {
//		knh_cfield_t *cf = knh_Class_fieldAt(cid, i);
//		knh_struct_t topsid = knh_tclass_topsid(TYPE_UNMASK(cf->type));
//		if(0 < topsid && topsid < CLASS_Prototype ) {
//			KNH_SETv(ctx, t->v[i], (Tuple*)new_Object__cid(ctx, 0, TYPE_UNMASK(cf->type)));
//			j = knh_resultset_index(ctx, t->v[i], index, j, e);
//		}
//		else {
//			index[j] = &(t->v[i]); j++;
//		}
//		if(!(j < e)) return e;
//	}
//	return j;
//}
//
//
///* ------------------------------------------------------------------------ */
//
//Object *knh_ResultSet_toObject(Ctx *ctx, ResultSet *rs, knh_class_t tcid)
//{
//	int i;
//	DBG2_P("tcid=%s", CLASSN(tcid));
//
//	Tuple *t = (Tuple*)new_Object__cid(ctx, 0, tcid);
//	Object **index[256] = {0};
//	knh_resultset_index(ctx, t, index, 0, sizeof(index)/sizeof(Object**));
//
//	for(i = 0; i < knh_tclass_bsize(tcid); i++) {
//		knh_cfield_t *cf = knh_Class_fieldAt(tcid, i);
//		Object *o = knh_ResultSet_get(ctx, rs, i);
//		if(knh_Object_opInstanceof(ctx, o, cf->type)) {
//			KNH_SETv(ctx, index[i], o);
//		}
//		else {
//			TODO();
//		}
//		if(i == rs->column_size) break;
//	}
//	return (Object*)t;
//}
//
///* ------------------------------------------------------------------------ */
//
//Object *knh_ResultSet_Object(Ctx *ctx, Object *self, Mapper *mpr)
//{
//	return knh_ResultSet_toObject(ctx, (ResultSet*)self, TYPE_UNMASK(mpr->tcid));
//}
//
///* ------------------------------------------------------------------------ */
//
//Object *
//knh_ResultSet_seq_next(Ctx *ctx, Iterator *it)
//{
//	ResultSet *rs = (ResultSet*)it->source;
//	if(rs->api.fnext(ctx, rs->rsetptr, rs)) {
//		return knh_ResultSet_toObject(ctx, rs, it->cid);
//	}
//	return KNH_NULL;
//}
//
///* ------------------------------------------------------------------------ */
//
//Object *knh_ResultSet_Object__(Ctx *ctx, Object *self, Mapper *mpr)
//{
//	return new_Iterator(ctx, TYPE_UNMASK(mpr->tcid), self, knh_ResultSet_seq_next);
//}
//
///* ------------------------------------------------------------------------ */
//
//Mapper*
//new_Mapper__ResultSet(Ctx *ctx, knh_class_t tcid)
//{
//	if(TYPE_ISPLURAL(tcid)) {
//		return new_Mapper(ctx, 0, CLASS_ResultSet, tcid, knh_ResultSet_Object__, KNH_NULL);
//	}
//	else {
//		return new_Mapper(ctx, 0, CLASS_ResultSet, TYPE_UNMASK(tcid), knh_ResultSet_Object, KNH_NULL);
//	}
//}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
