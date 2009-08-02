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
 * (1) GNU Lesser General Public License 3.0 (with KONOHA_UNDER_LGPL3)
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
/* [constructors] */

ResultSet* new_ResultSet(Ctx *ctx)
{
	return (ResultSet*)new_Object_bcid(ctx, CLASS_ResultSet, 0);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_ResultSet_next(Ctx *ctx, ResultSet *o)
{
	if(DP(o)->dbcur != NULL) {
		if(DP(DP(o)->conn)->df->dbcurnext(ctx, DP(o)->dbcur, o)) {
			DP(o)->count += 1;
			return 1;
		}
		else {
			DP(o)->dbcur_free(DP(o)->dbcur);
			DP(o)->dbcur = NULL;
			DP(o)->dbcur_free = knh_dbcurfree__NOP;
		}
	}
	return 0;
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! ResultSet.next() */

METHOD knh__ResultSet_next(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_ResultSet_next(ctx, (ResultSet*)sfp[0].o))
}

/* ------------------------------------------------------------------------ */
/* @method void ResultSet.close() */

void knh_ResultSet_close(Ctx *ctx, ResultSet *o)
{
	if(DP(o)->dbcur != NULL) {
		DP(o)->dbcur_free(DP(o)->dbcur);
		DP(o)->dbcur = NULL;
		DP(o)->dbcur_free = knh_dbcurfree__NOP;
	}
	KNH_SETv(ctx, DP(o)->conn, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_ResultSet_initColumn(Ctx *ctx, ResultSet *o, size_t column_size)
{
	size_t i;
	if(DP(o)->column_size != 0) {
		for(i = 0; i < DP(o)->column_size; i++) {
			KNH_FINALv(ctx, DP(o)->column[i].name);
		}
		KNH_FREE(ctx, DP(o)->column, sizeof(knh_dbschema_t) * DP(o)->column_size);
		DP(o)->column = NULL;
		if(DP(o)->dbcur != NULL) {
			DP(o)->dbcur_free(DP(o)->dbcur);
			DP(o)->dbcur = NULL;
		}
	}
	DP(o)->column_size = column_size;
	if(column_size > 0) {
		DP(o)->column = (knh_dbschema_t*)KNH_MALLOC(ctx, sizeof(knh_dbschema_t) * DP(o)->column_size);
		for(i = 0; i < DP(o)->column_size; i++) {
			DP(o)->column[i].type = CLASS_Object;
			KNH_INITv(DP(o)->column[i].name, TS_EMPTY);
			DP(o)->column[i].start = 0;
			DP(o)->column[i].len = 0;
		}
	}
	DP(o)->count = 0;
}

///* ======================================================================== */
///* [iterators] */
//
//static
//Object* knh_ResultSet_it_next(Ctx *ctx, Iterator *it)
//{
//	ResultSet *o = (ResultSet*)DP(it)->source;
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

KNHAPI(void) knh_ResultSet_setName(Ctx *ctx, ResultSet *o, size_t n, String *name)
{
	KNH_ASSERT(n < DP(o)->column_size);
	KNH_SETv(ctx, DP(o)->column[n].name, name);
}

/* ------------------------------------------------------------------------ */

String *knh_ResultSet_getName(Ctx *ctx, ResultSet *o, size_t n)
{
	KNH_ASSERT(n < DP(o)->column_size);
	return DP(o)->column[n].name;
}

/* ------------------------------------------------------------------------ */

int knh_ResultSet_findColumn(Ctx *ctx, ResultSet *o, knh_bytes_t name)
{
	int i = 0;
	for(i = 0; i < DP(o)->column_size; i++) {
		if(knh_bytes_strcasecmp(knh_String_tobytes(DP(o)->column[i].name), name) == 0) return i;
	}
	return -1;
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
	knh_Bytes_clear(DP(o)->databuf, 0);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_ResultSet_setInt(Ctx *ctx, ResultSet *o, size_t n, knh_int_t value)
{
	KNH_ASSERT(n < DP(o)->column_size);
	knh_bytes_t t = {(knh_uchar_t*)(&value), sizeof(knh_int_t)};
	DP(o)->column[n].ctype = knh_ResultSet_CTYPE__integer;
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

KNHAPI(void) knh_ResultSet_setText(Ctx *ctx, ResultSet *o, size_t n, knh_bytes_t t)
{
	KNH_ASSERT(n < DP(o)->column_size);
	DP(o)->column[n].ctype = knh_ResultSet_CTYPE__text;
	DP(o)->column[n].start = knh_Bytes_size(DP(o)->databuf);
	DP(o)->column[n].len = t.len;
	knh_Bytes_write(ctx, DP(o)->databuf, t);
	int i, c = t.len % sizeof(void*);
	for(i = 0; i < c; i++) knh_Bytes_putc(ctx, DP(o)->databuf, 0);    /* zero */
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_ResultSet_setBlob(Ctx *ctx, ResultSet *o, size_t n, knh_bytes_t t)
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
	case knh_ResultSet_CTYPE__integer :
		return (knh_int_t)(*((knh_int_t*)p));
	case knh_ResultSet_CTYPE__float :
		return (knh_int_t)(*((knh_float_t*)p));
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
	case knh_ResultSet_CTYPE__integer :
		return (knh_float_t)(*((knh_int_t*)p));
	case knh_ResultSet_CTYPE__float :
		return (knh_float_t)(*((knh_float_t*)p));
	case knh_ResultSet_CTYPE__bytes :
		TODO();
//		return knh_bytes_tofloat(B2(p, DP(o)->column[n].len));
	}
	return 0.0;
}

/* ------------------------------------------------------------------------ */

String* knh_ResultSet_getString(Ctx *ctx, ResultSet *o, size_t n)
{
	KNH_ASSERT(n < DP(o)->column_size);
	char *p = knh_Bytes_tochar(DP(o)->databuf) + DP(o)->column[n].start;
	switch(DP(o)->column[n].ctype) {
	case knh_ResultSet_CTYPE__null :
		return (String*)KNH_NULL;
	case knh_ResultSet_CTYPE__integer :
		return new_String__int(ctx, (knh_int_t)(*((knh_int_t*)p)));
	case knh_ResultSet_CTYPE__float :
		return new_String__float(ctx, (knh_float_t)(*((knh_float_t*)p)));
	case knh_ResultSet_CTYPE__text :
		return new_String(ctx, B2(p, DP(o)->column[n].len), NULL);
	}
	return (String*)KNH_NULL;
}

///* ======================================================================== */
///* [SequenceMapper] */
//
//int knh_resultset_index(Ctx *ctx, Tuple *t, Object **index[], int j, int e)
//{
//	int i;
//	knh_class_t cid = knh_Object_cid(t);
//	for(i = 0; i <knh_tclass_bsize(cid); i++) {
//		knh_cfield_t *cf = knh_Class_fieldAt(ctx, cid, i);
//		knh_struct_t topsid = knh_tclass_topsid(CLASS_type(cf->type));
//		if(0 < topsid && topsid < CLASS_Prototype ) {
//			KNH_SETv(ctx, t->v[i], (Tuple*)new_Object__cid(ctx, 0, CLASS_type(cf->type)));
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
//		knh_cfield_t *cf = knh_Class_fieldAt(ctx, tcid, i);
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
//	return knh_ResultSet_toObject(ctx, (ResultSet*)self, CLASS_type(mpr->tcid));
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
//	return new_Iterator(ctx, CLASS_type(mpr->tcid), self, knh_ResultSet_seq_next);
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
//		return new_Mapper(ctx, 0, CLASS_ResultSet, CLASS_type(tcid), knh_ResultSet_Object, KNH_NULL);
//	}
//}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
