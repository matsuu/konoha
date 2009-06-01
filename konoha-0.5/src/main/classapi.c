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
/* Data */
/* ======================================================================== */

/* ------------------------------------------------------------------------ */
/* @data*/
typedef struct {
	char                  *name;
	int                    index;
} knh_StringData_t ;

typedef struct {
	char                  *name;
	knh_struct_t           sid;
	knh_flag_t             flag;
	size_t                 size;
	knh_fstruct_init       finit;
	knh_fstruct_copy       fcopy;
	knh_fstruct_traverse   ftraverse;
	knh_fstruct_compareTo  fcompareTo;
	knh_fstruct_hashCode   fhashCode;
	knh_fstruct_newClass   fnewClass;
	knh_fstruct_getkey     fgetkey;
} knh_StructData_t ;

typedef struct {
	char *name;
	knh_class_t cid;
	knh_flag_t flag;
	knh_struct_t bcid;
	knh_class_t supcid;
	int field_size;
	int method_size; /* copy supcid if 0 */
	int mapper_size; /* copy Any if 0 */
	knh_fdefault fdefault;
} knh_ClassData_t ;

typedef struct {
	char *name;
	knh_class_t cid;
	knh_class_t bcid;
	knh_class_t p1;
	knh_class_t p2;
} knh_GenericsData_t ;

typedef struct {
	char *name;
	knh_class_t cid;
	knh_type_t r0;
	knh_type_t p1;
	knh_type_t p2;
	knh_type_t p3;
} knh_ClosureData_t ;

typedef struct {
	char *name;
	knh_flag_t flag;
	knh_expt_t eid;
	char *parent;
} knh_ExptData_t ;

typedef struct {
	char *name;
	void *func;
} knh_FuncData_t ;

typedef struct {
	char *name;
	knh_fieldn_t fn;
} knh_FieldNameData_t ;

typedef struct {
	int mfindex;
	knh_ushort_t psize;
	knh_type_t rtype;
	knh_type_t t1;
	knh_fieldn_t f1;
	knh_type_t t2;
	knh_fieldn_t f2;
	knh_type_t t3;
	knh_fieldn_t f3;
	knh_type_t t4;
	knh_fieldn_t f4;
} knh_MethodFieldData_t ;

typedef struct {
	knh_fmethod func;
	knh_flag_t flag;
	knh_class_t cid;
	knh_methodn_t mn;
	knh_ushort_t delta;
	int mfindex;
	void *optfunc;
} knh_MethodData_t ;

typedef struct {
	knh_fmapper func;
	knh_flag_t flag;
	knh_class_t scid;
	knh_class_t tcid;
} knh_MapperData_t ;

/* ======================================================================== */
/* Object */

#define knh_ObjectField_init_ NULL
#define knh_ObjectField_copy NULL
#define knh_ObjectField_traverse_ NULL
#define knh_ObjectField_compareTo NULL
#define knh_ObjectField_hashCode NULL
#define knh_ObjectField_newClass NULL
#define knh_ObjectField_getkey  NULL

/* ------------------------------------------------------------------------ */

static
void knh_ClassStruct_initField(Ctx *ctx, ClassStruct *cs, knh_class_t self_cid, Object **v)
{
	size_t i;
	knh_cfield_t *cf = cs->fields;
	for(i = 0; i < cs->fsize; i++) {
#ifdef KNH_USING_UNBOXFIELD
		if(cf[i].type == TYPE_void) {
			continue;
		}
		else if(cf[i].type == NNTYPE_Int) {
			knh_int_t *data = (knh_int_t*)(v + i);
			data[0] = IS_NULL(cf[i].value) ? 0 : ((Int*)cf[i].value)->n.ivalue;
			continue;
		}
		else if(cf[i].type == NNTYPE_Float) {
			knh_float_t *data = (knh_float_t*)(v + i);
			data[0] = IS_NULL(cf[i].value) ? 0.0 : ((Int*)cf[i].value)->n.fvalue;
			continue;
		}
		else if(cf[i].type == NNTYPE_Boolean) {
			knh_bool_t *data = (knh_bool_t*)(v + i);
			data[0] = IS_NULL(cf[i].value) ? 0 : ((Int*)cf[i].value)->n.bvalue;
			continue;
		}
		else
#endif/*KNH_USING_UNBOXFIELD*/
		if(IS_NULL(cf[i].value) && IS_NNTYPE(cf[i].type)) {
			knh_class_t cid = knh_pmztype_toclass(ctx, cf[i].type, self_cid);
			KNH_INITv(v[i], new_Object_init(ctx, 0, cid, 0));
		}
		else {
			KNH_INITv(v[i], cf[i].value);
		}
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_ObjectField_init(Ctx *ctx, knh_ObjectField_t *of, int init)
{
	knh_class_t cid = of->h.cid;
	if(ctx->share->ClassTable[cid].size > 0) {
		Object **v = (Object**)of->fields;
		size_t offset;
		while((offset = ctx->share->ClassTable[cid].offset) != 0) {
			knh_ClassStruct_initField(ctx, ctx->share->ClassTable[cid].cstruct, of->h.cid, v + offset);
			cid = ctx->share->ClassTable[cid].supcid;
			KNH_ASSERT_cid(cid);
		}
		knh_ClassStruct_initField(ctx, ctx->share->ClassTable[cid].cstruct, of->h.cid, v + offset);
		of->fields = v;
		of->bsize = ctx->share->ClassTable[of->h.cid].bsize;
	}
	else {
		of->fields = NULL;
		of->bsize = 0;
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_ObjectField_traverse(Ctx *ctx, knh_ObjectField_t *of, knh_ftraverse ftr)
{
	knh_class_t cid = knh_Object_cid(of);
	while(cid != CLASS_Object) {
		knh_ClassStruct_t *cs = ctx->share->ClassTable[cid].cstruct;
		size_t i, offset = ctx->share->ClassTable[cid].offset;
		for(i = 0; i < cs->fsize; i++) {
			knh_type_t type = cs->fields[i].type;
			//DBG2_P("i=%d, fn=%s, type=%s%s", i, FIELDN(cs->fields[i].fn), TYPEQN(type));
			if(type == NNTYPE_Int || type == NNTYPE_Float ||
					type == NNTYPE_Boolean || type == TYPE_void) {
				continue;
			}
			if(of->fields[i + offset] == NULL) return; /* for Script */
			if(cs->fields[i].fn == FIELDN_register) continue;
			ftr(ctx, of->fields[i + offset]);
		}
		cid = ctx->share->ClassTable[cid].supcid;
	}
}

/* ======================================================================== */
/* Any */

#define knh_Any_init_ NULL
#define knh_Any_copy NULL
#define knh_Any_traverse_ NULL
#define knh_Any_compareTo NULL
#define knh_Any_hashCode NULL
#define knh_Any_newClass NULL
#define knh_Any_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_Any_init(Ctx *ctx, knh_Glue_t *g, int init)
{
	knh_Glue_init(ctx, g, NULL, NULL);
}

/* ------------------------------------------------------------------------ */

static
void knh_Any_traverse(Ctx *ctx, knh_Glue_t *g, knh_ftraverse ftr)
{
	if(IS_SWEEP(ftr)) {
		g->gfree(ctx, g);
		knh_Glue_init(ctx, g, NULL, NULL);
	}
}

/* ======================================================================== */
/* Nue */

#define knh_Nue_init_ NULL
#define knh_Nue_copy NULL
#define knh_Nue_traverse_ NULL
#define knh_Nue_compareTo_ NULL
#define knh_Nue_hashCode_ NULL
#define knh_Nue_newClass NULL
#define knh_Nue_getkey_ NULL

/* ------------------------------------------------------------------------ */

static
void knh_Nue_init(Ctx *ctx, knh_Nue_t *n, int init)
{
	n->orign = NULL;
}

/* ------------------------------------------------------------------------ */

static
void knh_Nue_traverse(Ctx *ctx, knh_Nue_t *n, knh_ftraverse ftr)
{
	if(n->orign != NULL) {
		KNH_ASSERT(IS_bString(n->orign));
		ftr(ctx, UP(n->orign));
		n->orign = NULL;
	}
}

/* ------------------------------------------------------------------------ */

static
int knh_Nue_compareTo(Nue *o, Nue *o1)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

static
knh_hcode_t knh_Nue_hashCode(Ctx *ctx, Nue *o)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

static
String *knh_Nue_getkey(Ctx *ctx, knh_sfp_t *lsfp)
{
	return TS_null;
}

/* ======================================================================== */
/* Boolean */

#define knh_Boolean_init_ NULL
#define knh_Boolean_copy NULL
#define knh_Boolean_traverse NULL
#define knh_Boolean_compareTo NULL
#define knh_Boolean_hashCode NULL
#define knh_Boolean_newClass NULL

/* ------------------------------------------------------------------------ */

static
void knh_Boolean_init(Ctx *ctx, Boolean *o, int init)
{
	o->n.bvalue = init;
}

/* ------------------------------------------------------------------------ */

static
String *knh_Boolean_getkey(Ctx *ctx, knh_sfp_t *lsfp)
{
	if(lsfp[0].bvalue) {
		return TS_true;
	}
	else {
		return TS_false;
	}
}

/* ======================================================================== */
/* Number */

#define knh_Number_init NULL
#define knh_Number_copy NULL
#define knh_Number_traverse NULL
#define knh_Number_compareTo NULL
#define knh_Number_hashCode NULL
#define knh_Number_newClass NULL
#define knh_Number_getkey NULL

/* ======================================================================== */
/* Int */

#define knh_Int_init_ NULL
#define knh_Int_copy NULL
#define knh_Int_traverse NULL
#define knh_Int_compareTo_ NULL
#define knh_Int_hashCode_ NULL
#define knh_Int_newClass NULL

/* ------------------------------------------------------------------------ */

static
void knh_Int_init(Ctx *ctx, Int *n, int init)
{
	n->n.ivalue = (knh_int_t)init;
}

/* ------------------------------------------------------------------------ */

static
knh_hcode_t knh_Int_hashCode(Ctx *ctx, Int *o)
{
	return (knh_hcode_t)o->n.ivalue;
}

/* ------------------------------------------------------------------------ */

static
int knh_Int_compareTo(Int *o, Int *o2)
{
	if(o->h.cid == CLASS_Int || o2->h.cid == CLASS_Int) {
		return (int)(o->n.ivalue - o2->n.ivalue);
	}
	else {
		Ctx *ctx = konoha_getCurrentContext();
		IntUnit *u = (IntUnit*)ctx->share->ClassTable[o->h.cid].cspec;
		KNH_ASSERT(IS_IntUnit(u));
		return DP(u)->fcmp(u, o->n.ivalue, o2->n.ivalue);
	}
}

/* ------------------------------------------------------------------------ */

static
String *knh_Int_getkey(Ctx *ctx, knh_sfp_t *lsfp)
{
	char buf[40];
#ifdef KNH_USING_INT32
	knh_snprintf(buf, sizeof(buf), "%016lu", lsfp[0].ivalue);
#else
	//18446744073709551615ULL
	knh_snprintf(buf, sizeof(buf), "%020llu", lsfp[0].ivalue);
#endif
	return new_String(ctx, B(buf), NULL);
}

/* ======================================================================== */
/* Float */

#define knh_Float_init_ NULL
#define knh_Float_copy NULL
#define knh_Float_traverse NULL
#define knh_Float_compareTo_ NULL
#define knh_Float_hashCode_ NULL
#define knh_Float_newClass NULL
#define knh_Float_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_Float_init(Ctx *ctx, Float *f, int init)
{
	f->n.fvalue = (knh_float_t)init;
}

/* ------------------------------------------------------------------------ */

static
knh_hcode_t knh_Float_hashCode(Ctx *ctx, Int *f)
{
	return (knh_hcode_t)f->n.ivalue;
}

/* ------------------------------------------------------------------------ */

static
int knh_Float_compareTo(Float *o, Float *o2)
{
	if(o->h.cid == CLASS_Float || o2->h.cid == CLASS_Float) {
		return (int)(o->n.fvalue - o2->n.fvalue);
	}
	else {
		Ctx *ctx = konoha_getCurrentContext();
		FloatUnit *fu = (FloatUnit*)ctx->share->ClassTable[o->h.cid].cspec;
		KNH_ASSERT(IS_FloatUnit(fu));
		return DP(fu)->fcmp(fu, o->n.fvalue, o2->n.fvalue);
	}
}

/* ------------------------------------------------------------------------ */

//static
//String *knh_Float_getkey(Ctx *ctx, knh_sfp_t *lsfp)
//{
//	char buf[40]; // formating as int64
//	knh_snprintf(buf, sizeof(buf), "%020llu", lsfp[0].ivalue);
//	return new_String(ctx, B(buf), NULL);
//}

/* ======================================================================== */
/* String */

#define knh_String_init_ NULL
#define knh_String_copy NULL
#define knh_String_traverse_ NULL
#define knh_String_compareTo_ NULL
#define knh_String_hashCode_ NULL
#define knh_String_newClass NULL

/* ------------------------------------------------------------------------ */

static
void knh_String_init(Ctx *ctx, knh_String_t *s, int init)
{
	s->str = (knh_uchar_t*)""; // for safety
	s->size = 0;
	s->orign = NULL;
}

/* ------------------------------------------------------------------------ */

static
void knh_String_traverse(Ctx *ctx, knh_String_t *s, knh_ftraverse ftr)
{
	if(s->orign != NULL) {
		ftr(ctx, UP(s->orign));
	}
	else if(!knh_String_isTextSgm(s)) {
		if(IS_SWEEP(ftr)) {
			KNH_FREE(ctx, s->str, KNH_SIZE(s->size + 1));
			s->str = NULL;
		}
	}
}

/* ------------------------------------------------------------------------ */

static
knh_hcode_t knh_String_hashCode(Ctx *ctx, String *o)
{
	KNH_ASSERT(IS_bString(o));
	knh_hcode_t h = o->size;
	size_t i;
	for(i = 0; i < o->size; i++) {
		h = o->str[i] + 31 * h;
	}
	return h;
}

/* ------------------------------------------------------------------------ */

static
int knh_String_compareTo(String *o, String *o2)
{
	if(o->h.cid == CLASS_String || o2->h.cid == CLASS_String) {
		size_t i, max = (o->size< o2->size) ? o->size : o2->size;
		for(i = 0; i < max; i++) {
			int res = o->str[i] - o2->str[i];
			if(res != 0) return res;
		}
		return o->size - o2->size;
	}
	else {
		if(o->h.cid == o2->h.cid) {
			Ctx *ctx = konoha_getCurrentContext();
			StringUnit *u = (StringUnit*)ctx->share->ClassTable[o->h.cid].cspec;
			KNH_ASSERT(IS_StringUnit(u));
			return DP(u)->fcmp(u, knh_String_tobytes(o), knh_String_tobytes(o2));
		}
		return (int)(o - o2);
	}
}

/* ------------------------------------------------------------------------ */

static
String *knh_String_getkey(Ctx *ctx, knh_sfp_t *lsfp)
{
	return lsfp[0].s;
}

/* ======================================================================== */
/* Bytes */

#define knh_Bytes_init_ NULL
#define knh_Bytes_copy NULL
#define knh_Bytes_traverse_ NULL
#define knh_Bytes_compareTo NULL
#define knh_Bytes_hashCode NULL
#define knh_Bytes_newClass NULL
#define knh_Bytes_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_Bytes_init(Ctx *ctx, knh_Bytes_t *b, int init)
{
	b->size = 0;
	if(init <= 0) {
		b->buf = (knh_uchar_t*)"";
		b->capacity = 0;
	}
	else {
		b->capacity = knh_bytes_newsize(init);
		b->buf = (knh_uchar_t*)KNH_MALLOC(ctx, b->capacity);
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_Bytes_traverse(Ctx *ctx, knh_Bytes_t *b, knh_ftraverse ftr)
{
	if(IS_SWEEP(ftr)) {
		KNH_FREE(ctx, b->buf, b->capacity);
		b->buf = NULL;
		b->capacity = 0;
		b->size = 0;
	}
}

/* ======================================================================== */
/* Tuple2 */

#define knh_Tuple2_init_ NULL
#define knh_Tuple2_copy NULL
#define knh_Tuple2_traverse_ NULL
#define knh_Tuple2_compareTo NULL
#define knh_Tuple2_hashCode NULL
#define knh_Tuple2_newClass NULL
#define knh_Tuple2_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_Tuple2_init(Ctx *ctx, knh_Tuple2_t *t, int init)
{
	KNH_INITv(t->first, KNH_NULL);
	KNH_INITv(t->second, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

static
void knh_Tuple2_traverse(Ctx *ctx, knh_Tuple2_t *t, knh_ftraverse ftr)
{
	ftr(ctx, t->first);
	ftr(ctx, t->second);
}

/* ======================================================================== */
/* Range */

#define knh_Range_init knh_Tuple2_init
#define knh_Range_copy NULL
#define knh_Range_traverse knh_Tuple2_traverse
#define knh_Range_compareTo NULL
#define knh_Range_hashCode NULL
#define knh_Range_newClass NULL
#define knh_Range_getkey NULL

/* ======================================================================== */
/* Array */

#define knh_Array_init_ NULL
#define knh_Array_copy NULL
#define knh_Array_traverse_ NULL
#define knh_Array_compareTo NULL
#define knh_Array_hashCode NULL
#define knh_Array_newClass NULL
#define knh_Array_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_Array_init(Ctx *ctx, knh_Array_t *a, int init)
{
	a->list = NULL;
	a->capacity = 0;
	a->size = 0;
	if(init > 0) {
		knh_Array_grow(ctx, a, init, KNH_NULL);
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_Array_traverse(Ctx *ctx, knh_Array_t *a, knh_ftraverse ftr)
{
	size_t i;
	for(i = 0; i < a->capacity; i++) {
		ftr(ctx, a->list[i]);
	}
	if(a->capacity > 0 && IS_SWEEP(ftr)) {
		if(knh_Array_isDim(a)) {
			knh_array_dfree(ctx, a->list, a->capacity, sizeof(Object*));
		}
		else {
			KNH_FREE(ctx, a->list, a->capacity * sizeof(Object*));
		}
		a->list = NULL;
		a->size = 0;
		a->capacity = 0;
	}
}

/* ======================================================================== */
/* IArray */

#define knh_IArray_init_ NULL
#define knh_IArray_copy NULL
#define knh_IArray_traverse_ NULL
#define knh_IArray_compareTo NULL
#define knh_IArray_hashCode NULL
#define knh_IArray_newClass NULL
#define knh_IArray_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_IArray_init(Ctx *ctx, knh_IArray_t *a, int init)
{
	a->ilist = NULL;
	a->capacity = 0;
	a->size = 0;
	KNH_ASSERT(init == 0);
//	if(init > 0) {
//		knh_IArray_grow(ctx, a, init, 0);
//	}
}

/* ------------------------------------------------------------------------ */

static
void knh_IArray_traverse(Ctx *ctx, knh_IArray_t *a, knh_ftraverse ftr)
{
	if(a->capacity > 0 && IS_SWEEP(ftr)) {
		if(knh_IArray_isDim(a)) {
			knh_array_dfree(ctx, a->ilist, a->capacity, sizeof(knh_int_t));
		}
		else {
			KNH_FREE(ctx, a->ilist, a->capacity * sizeof(knh_int_t));
		}
		a->size = 0;
		a->capacity = 0;
	}
}

/* ======================================================================== */
/* FArray */

#define knh_FArray_init_ NULL
#define knh_FArray_copy NULL
#define knh_FArray_traverse_ NULL
#define knh_FArray_compareTo NULL
#define knh_FArray_hashCode NULL
#define knh_FArray_newClass NULL
#define knh_FArray_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_FArray_init(Ctx *ctx, knh_FArray_t *a, int init)
{
	a->flist = NULL;
	a->capacity = 0;
	a->size = 0;
	KNH_ASSERT(init == 0);
//	if(init > 0) {
//		knh_FArray_grow(ctx, a, init, 0.0);
//	}
}

/* ------------------------------------------------------------------------ */

static
void knh_FArray_traverse(Ctx *ctx, knh_FArray_t *a, knh_ftraverse ftr)
{
	if(a->capacity > 0 && IS_SWEEP(ftr)) {
		if(knh_FArray_isDim(a)) {
			knh_array_dfree(ctx, a->flist, a->capacity, sizeof(knh_float_t));
		}
		else {
			KNH_FREE(ctx, a->flist, a->capacity * sizeof(knh_float_t));
		}
		a->size = 0;
		a->capacity = 0;
	}
}

/* ======================================================================== */
/* Iterator */

#define knh_Iterator_init_ NULL
#define knh_Iterator_copy NULL
#define knh_Iterator_traverse_ NULL
#define knh_Iterator_compareTo NULL
#define knh_Iterator_hashCode NULL
#define knh_Iterator_newClass NULL
#define knh_Iterator_getkey NULL

/* ------------------------------------------------------------------------ */

static
ITRNEXT knh_fitrnext_single(Ctx *ctx, knh_sfp_t *sfp, int n)
{
	Iterator *it = sfp[0].it;
	if(DP(it)->pos == 0) {
		DP(it)->pos = 1;
		KNH_ITRNEXT(ctx, sfp, n, DP(it)->source);
	}
	KNH_ITREND(ctx, sfp, n);
}
/* ------------------------------------------------------------------------ */

static
void knh_Iterator_init(Ctx *ctx, Iterator *it, int init)
{
	knh_Iterator_struct *b = DP(it);
	b->fnext  =  knh_fitrnext_single;
	KNH_INITv(b->source, KNH_VOID);
	KNH_INITv(b->prefetch, KNH_NULL);
	b->pos    =  0;
	b->ref    =  NULL;
	b->count = 0;
	b->start = 0;
	b->end   = (size_t)-1;
}

/* ------------------------------------------------------------------------ */

static
void knh_Iterator_traverse(Ctx *ctx, Iterator *it, knh_ftraverse ftr)
{
	knh_Iterator_struct *b = DP(it);
	ftr(ctx, b->source);
	ftr(ctx, b->prefetch);
}

/* ======================================================================== */
/* DictMap */

#define knh_DictMap_init_ NULL
#define knh_DictMap_copy NULL
#define knh_DictMap_traverse_ NULL
#define knh_DictMap_compareTo NULL
#define knh_DictMap_hashCode NULL
#define knh_DictMap_newClass NULL
#define knh_DictMap_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_DictMap_init(Ctx *ctx, knh_DictMap_t *d, int init)
{
	d->_list = knh_dictmap_malloc(ctx, (size_t)init);
	d->size = 0;
	d->fcmp = knh_bytes_strcmp;
}

/* ------------------------------------------------------------------------ */

static
void knh_DictMap_traverse(Ctx *ctx, knh_DictMap_t *d, knh_ftraverse ftr)
{
	knh_dict_traverse(ctx, d->_list, ftr);
}

/* ======================================================================== */
/* DictSet */

#define knh_DictSet_init_ NULL
#define knh_DictSet_copy NULL
#define knh_DictSet_traverse knh_DictMap_traverse
#define knh_DictSet_compareTo NULL
#define knh_DictSet_hashCode NULL
#define knh_DictSet_newClass NULL
#define knh_DictSet_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_DictSet_init(Ctx *ctx, knh_DictSet_t *d, int init)
{
	d->_list = knh_dictset_malloc(ctx, (size_t)init);
	d->size = 0;
	d->fcmp = knh_bytes_strcmp;
}

/* ======================================================================== */
/* HashMap */

#define knh_HashMap_init_ NULL
#define knh_HashMap_copy NULL
#define knh_HashMap_traverse knh_Hash_traverse
#define knh_HashMap_compareTo NULL
#define knh_HashMap_hashCode NULL
#define knh_HashMap_newClass NULL
#define knh_HashMap_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_Hash_init(Ctx *ctx, knh_Hash_t *hash, int init)
{
	knh_Hash_struct *b = DP(hash);
	b->DBG_name = "HashMap";
	if(init > 0) {
		b->hmax = init;
		b->capacity = knh_bytes_newsize(init);
		b->array = (knh_hashentry_t**)KNH_MALLOC(ctx, sizeof(knh_hashentry_t*) * b->capacity);
		knh_bzero(b->array, sizeof(knh_hashentry_t*) * b->capacity);
	}
	else {
		b->hmax = 0;
		b->capacity = 0;
		b->array = NULL;
	}
	b->size = 0;
	b->tables = NULL;
	b->tables_size = 0;
	b->tables_capacity = 0;
	b->tables_first = NULL;
	b->unused_first = NULL;
	//
	hash->fcmp = knh_Object_cmp;
}

/* ------------------------------------------------------------------------ */

static
void knh_hashmapentry_traverse(Ctx *ctx, knh_hashentry_t *e, knh_ftraverse ftr)
{
	DBG2_ASSERT(e->key != NULL);
	ftr(ctx, e->key);
	ftr(ctx, e->value);
}

/* ------------------------------------------------------------------------ */
/* @data */

static knh_hash_op knh_hashmap_op = {
	sizeof(knh_hashentry_t),
	NULL,
	knh_hashmapentry_traverse,
};

/* ------------------------------------------------------------------------ */

static
void knh_HashMap_init(Ctx *ctx, knh_HashMap_t *o, int init)
{
	knh_Hash_t *hash = (knh_Hash_t*)o;
	knh_Hash_init(ctx, hash, init);
	DP(hash)->DBG_name = "HashMap";
	hash->fcmp = knh_Object_cmp;
	hash->hashop = &knh_hashmap_op;
}

/* ------------------------------------------------------------------------ */

static
void knh_Hash_traverse(Ctx *ctx, knh_Hash_t *hash, knh_ftraverse ftr)
{
	knh_Hash_struct *b = DP(hash);
	size_t i, j, esize = hash->hashop->size, tsize = KNH_HASH_TABLESIZE / esize;
	for(j = 0; j < b->tables_size; j++) {
		for(i = 0; i < tsize; i++) {
			knh_hashentry_t *e = KNH_HASHENTRY(b->tables[j], esize, i);
			if(e->key != NULL) {
				hash->hashop->ftraverse(ctx, e, ftr);
			}
		}
	}
	if(IS_SWEEP(ftr)) {
		if(b->array != NULL) {
			KNH_FREE(ctx, b->array, sizeof(knh_hashentry_t*) * b->capacity);
			b->array = NULL;
			b->size = 0;
			b->capacity = 0;
		}
		if(b->tables_size > 0) {
			for(i = 0; i < b->tables_size; i++) {
				KNH_FREE(ctx, b->tables[i], KNH_HASH_TABLESIZE);
			}
			if(b->tables_capacity > 1) {
				KNH_FREE(ctx, b->tables, sizeof(knh_hashentry_t*) * b->capacity);
			}
			b->tables = NULL;
			b->tables_capacity = 0;
			b->tables_size = 0;
		}
	}
}

/* ======================================================================== */
/* HashSet */

#define knh_HashSet_init_ NULL
#define knh_HashSet_copy NULL
#define knh_HashSet_traverse knh_Hash_traverse
#define knh_HashSet_compareTo NULL
#define knh_HashSet_hashCode NULL
#define knh_HashSet_newClass NULL
#define knh_HashSet_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_hashsetentry_traverse(Ctx *ctx, knh_hashentry_t *e, knh_ftraverse ftr)
{
	DBG2_ASSERT(e->key != NULL);
	ftr(ctx, e->key);
}

/* ------------------------------------------------------------------------ */
/* @data */

static knh_hash_op knh_hashset_op = {
	sizeof(knh_hashentry_t),
	NULL,
	knh_hashsetentry_traverse,
};

/* ------------------------------------------------------------------------ */

static
void knh_HashSet_init(Ctx *ctx, knh_HashSet_t *o, int init)
{
	knh_Hash_t *hash = (knh_Hash_t*)o;
	knh_Hash_init(ctx, hash, init);
	DP(hash)->DBG_name = "HashSet";
	hash->fcmp = knh_Object_cmp;
	hash->hashop = &knh_hashset_op;
}


/* ======================================================================== */
/* DictIdx */

#define knh_DictIdx_init_ NULL
#define knh_DictIdx_copy NULL
#define knh_DictIdx_traverse_ NULL
#define knh_DictIdx_compareTo NULL
#define knh_DictIdx_hashCode NULL
#define knh_DictIdx_newClass NULL
#define knh_DictIdx_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_DictIdx_init(Ctx *ctx, knh_DictIdx_t *d, int init)
{
	KNH_INITv(d->terms, new_Array(ctx, CLASS_String, init));
	KNH_INITv(d->termsDictSet, new_DictSet(ctx, init));
	d->offset = 0;
}

/* ------------------------------------------------------------------------ */

static
void knh_DictIdx_traverse(Ctx *ctx, knh_DictIdx_t *d, knh_ftraverse ftr)
{
	ftr(ctx, UP(d->terms));
	ftr(ctx, UP(d->termsDictSet));
}

/* ======================================================================== */
/* Class */

#define knh_Class_init_ NULL
#define knh_Class_copy NULL
#define knh_Class_traverse NULL
#define knh_Class_compareTo_ NULL
#define knh_Class_hashCode_ NULL
#define knh_Class_newClass NULL

/* ------------------------------------------------------------------------ */

static
void knh_Class_init(Ctx *ctx, knh_Class_t *c, int init)
{
	c->cid = (knh_class_t)init;
	c->type = (knh_type_t)init;
}

/* ------------------------------------------------------------------------ */

static
knh_hcode_t knh_Class_hashCode(Ctx *ctx, Class *o)
{
	return (knh_hcode_t)o->cid;
}

/* ------------------------------------------------------------------------ */

static
int knh_Class_compareTo(Class *o, Class *o2)
{
	Ctx *ctx = konoha_getCurrentContext();
	return knh_strcmp(CLASSN(o->cid), CLASSN(o2->cid));
}

/* ------------------------------------------------------------------------ */

static
String *knh_Class_getkey(Ctx *ctx,knh_sfp_t *lsfp)
{
	knh_Class_t *c = (knh_Class_t*)lsfp[0].o;
	KNH_ASSERT_cid(c->cid);
	return ctx->share->ClassTable[c->cid].lname;
}

/* ======================================================================== */
/* ClassStruct */

#define knh_ClassStruct_init_ NULL
#define knh_ClassStruct_copy NULL
#define knh_ClassStruct_traverse_ NULL
#define knh_ClassStruct_compareTo NULL
#define knh_ClassStruct_hashCode NULL
#define knh_ClassStruct_newClass NULL
#define knh_ClassStruct_getkey NULL

static
void knh_ClassStruct_init(Ctx *ctx, ClassStruct *b, int init)
{
	b->fsize = init;
	if(b->fsize == 0) {
		b->fields = NULL;
	}else {
		b->fields = (knh_cfield_t*)KNH_MALLOC(ctx, b->fsize * sizeof(knh_cfield_t));
		knh_intptr_t i;
		for(i = 0; i < b->fsize; i++) {
			b->fields[i].flag = 0;
			b->fields[i].type = TYPE_Any;
			b->fields[i].fn   = FIELDN_NONAME;
			KNH_INITv(b->fields[i].value, KNH_NULL);
		}
	}
	KNH_INITv(b->methods, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

static
void knh_ClassStruct_traverse(Ctx *ctx, ClassStruct *b, knh_ftraverse ftr)
{
	ftr(ctx, UP(b->methods));
	if(b->fields != NULL) {
		knh_intptr_t i;
		for(i = 0; i < b->fsize; i++) {
			ftr(ctx, b->fields[i].value);
		}
		if(IS_SWEEP(ftr)) {
			//DBG2_P("freeing b->fields=%p", b->fields);
			KNH_FREE(ctx, b->fields, b->fsize * sizeof(knh_cfield_t));
			b->fields = NULL;
		}
	}
}

/* ======================================================================== */
/* MethodField */

#define knh_MethodField_init_ NULL
#define knh_MethodField_copy NULL
#define knh_MethodField_traverse_ NULL
#define knh_MethodField_compareTo NULL
#define knh_MethodField_hashCode NULL
#define knh_MethodField_newClass NULL
#define knh_MethodField_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_MethodField_init(Ctx *ctx, knh_MethodField_t *o, int init)
{
	o->psize = (size_t)init;
	if(o->psize > KNH_METHODFIELD_2) {
		o->mparams = (knh_mparam_t*)KNH_MALLOC(ctx, init * sizeof(knh_mparam_t));
		size_t i;
		for(i = 0; i < o->psize; i++) {
			o->mparams[i].type = TYPE_void;
			o->mparams[i].fn   = FIELDN_NONAME;
		}
	}
	else {
		o->p0.type = TYPE_void;
		o->p0.fn = FIELDN_NONAME;
		o->p1.type = TYPE_void;
		o->p1.fn = FIELDN_NONAME;
	}
	o->rtype = TYPE_Any;
}

/* ------------------------------------------------------------------------ */

knh_hcode_t knh_MethodField_hachCode(Ctx *ctx, MethodField *o)
{
	knh_hcode_t h = o->rtype;
	if(o->psize == 1) {
		return knh_mparam_hcode(h, o->p0.type, o->p0.fn);
	}
	else if(o->psize == 2) {
		h = knh_mparam_hcode(h, o->p0.type, o->p0.fn);
		return knh_mparam_hcode(h, o->p1.type, o->p1.fn);
	}
	else {
		size_t i;
		for(i = 0; i < o->psize; i++) {
			h = knh_mparam_hcode(h, o->mparams[i].type, o->mparams[i].fn);
		}
	}
	return h;
}

/* ------------------------------------------------------------------------ */

static
void knh_MethodField_traverse(Ctx *ctx, knh_MethodField_t *o, knh_ftraverse ftr)
{
	if(IS_SWEEP(ftr) && o->psize > KNH_METHODFIELD_2) {
		KNH_FREE(ctx, o->mparams, o->psize * sizeof(knh_mparam_t));
	}
}

/* ======================================================================== */
/* Method */

#define knh_Method_init_ NULL
#define knh_Method_copy NULL
#define knh_Method_traverse_ NULL
#define knh_Method_compareTo NULL
#define knh_Method_hashCode NULL
#define knh_Method_newClass NULL

/* ------------------------------------------------------------------------ */

static
void knh_Method_init(Ctx *ctx, Method *mtd, int init)
{
	knh_Method_struct *b = DP(mtd);
	b->flag   = 0;
	b->delta  = 0;
	b->cid    = CLASS_Object;
	b->mn     = METHODN_NONAME;
	b->fproceed  = knh_fmethod_abstract;
	KNH_INITv(b->mf, konoha_findMethodField0(ctx, TYPE_Any));
	b->code  = NULL;
}

/* ------------------------------------------------------------------------ */

static
void knh_Method_traverse(Ctx *ctx, Method *mtd, knh_ftraverse gc)
{
	knh_Method_struct *b = DP(mtd);
	gc(ctx, UP(b->mf));
	if((b->flag & KNH_FLAG_MF_OBJECTCODE) == KNH_FLAG_MF_OBJECTCODE) {
		gc(ctx, (Object*)b->code);
		if(IS_SWEEP(gc)) {
			b->code = NULL;
		}
	}
}

/* ------------------------------------------------------------------------ */

static
String *knh_Method_getkey(Ctx *ctx, knh_sfp_t *lsfp)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_format_cmethodn(ctx, buf, sizeof(buf), DP(lsfp[0].mtd)->cid, DP(lsfp[0].mtd)->mn);
	return new_String(ctx, B(buf), NULL);
}

/* ======================================================================== */
/* Mapper */

#define knh_Mapper_init_ NULL
#define knh_Mapper_copy NULL
#define knh_Mapper_traverse_ NULL
#define knh_Mapper_compareTo NULL
#define knh_Mapper_hashCode NULL
#define knh_Mapper_newClass NULL

/* ------------------------------------------------------------------------ */

static
void knh_Mapper_init(Ctx *ctx, Mapper *mpr, int init)
{
	knh_Mapper_struct *b = DP(mpr);
	b->size = 0;
	b->flag = 0;
	b->scid = CLASS_Object;
	b->tcid = CLASS_Object;
	//b->fmap = NULL;
	KNH_INITv(b->mapdata, KNH_NULL);
	KNH_INITv(b->m2, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

static
void knh_Mapper_traverse(Ctx *ctx, Mapper *mpr, knh_ftraverse ftr)
{
	knh_Mapper_struct *b = DP(mpr);
	ftr(ctx, b->mapdata);
	ftr(ctx, UP(b->m2));
}

/* ------------------------------------------------------------------------ */

static
String *knh_Mapper_getkey(Ctx *ctx, knh_sfp_t *lsfp)
{
	char buf[CLASSNAME_BUFSIZ*2];
	knh_snprintf(buf, sizeof(buf), "%s => %s", CLASSN(DP(lsfp[0].mpr)->scid), CLASSN(DP(lsfp[0].mpr)->tcid));
	return new_String(ctx, B(buf), NULL);
}

/* ======================================================================== */
/* ClassMap */

#define knh_ClassMap_init_ NULL
#define knh_ClassMap_copy NULL
#define knh_ClassMap_traverse_ NULL
#define knh_ClassMap_compareTo NULL
#define knh_ClassMap_hashCode NULL
#define knh_ClassMap_newClass NULL
#define knh_ClassMap_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_ClassMap_init(Ctx *ctx, ClassMap *cm, int init)
{
	knh_ClassMap_struct *b = DP(cm);
	b->size   = 0;
	b->capacity = (init <= 3) ? 4 : init;
	b->maplist   = (Mapper**)KNH_MALLOC(ctx, b->capacity * sizeof(Mapper*));
	knh_bzero(b->maplist, b->capacity * sizeof(Mapper*));
}

/* ------------------------------------------------------------------------ */

static
void knh_ClassMap_traverse(Ctx *ctx, ClassMap *cm, knh_ftraverse gc)
{
	knh_ClassMap_struct *b = DP(cm);
	int i;
	for(i = 0; i < b->size; i++) {
		gc(ctx, UP(b->maplist[i]));
	}
	if(IS_SWEEP(gc)) {
		KNH_FREE(ctx, b->maplist, b->capacity * sizeof(Mapper*));
	}
}

/* ======================================================================== */
/* Closure */

#define knh_Closure_init_ NULL
#define knh_Closure_copy NULL
#define knh_Closure_traverse_ NULL
#define knh_Closure_compareTo NULL
#define knh_Closure_hashCode NULL
#define knh_Closure_newClass NULL
#define knh_Closure_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_Closure_init(Ctx *ctx, Closure *c, int init)
{
	knh_Closure_struct *b = DP(c);
	KNH_INITv(b->base, KNH_NULL);
	KNH_INITv(b->mtd, KNH_NULL);
	b->stack = NULL;
	b->stacksize = 0;
}

/* ------------------------------------------------------------------------ */

static
void knh_Closure_traverse(Ctx *ctx, Closure *c, knh_ftraverse ftr)
{
	knh_Closure_struct *b = DP(c);
	ftr(ctx, UP(b->base));
	ftr(ctx, UP(b->mtd));
	if(b->stacksize > 0 && knh_Closure_isCopiedStack(c)) {
		size_t i;
		for(i = 0; i < b->stacksize; i++) {
			ftr(ctx, b->stack[i].o);
		}
		if(IS_SWEEP(ftr)) {
			KNH_FREE(ctx, b->stack, sizeof(knh_sfp_t) * b->stacksize);
			b->stack = NULL;
			b->stacksize = 0;
		}
	}
}

/* ======================================================================== */
/* AffineConv */

#define knh_AffineConv_init_ NULL
#define knh_AffineConv_copy NULL
#define knh_AffineConv_traverse NULL
#define knh_AffineConv_compareTo NULL
#define knh_AffineConv_hashCode NULL
#define knh_AffineConv_newClass NULL
#define knh_AffineConv_getkey NULL

static
void knh_AffineConv_init(Ctx *ctx, AffineConv *o, int init)
{
	o->scale = 1.0;
	o->shift = 0.0;
}

/* ======================================================================== */
/* IntUnit */

#define knh_IntUnit_init_ NULL
#define knh_IntUnit_copy NULL
#define knh_IntUnit_traverse_ NULL
#define knh_IntUnit_compareTo NULL
#define knh_IntUnit_hashCode NULL
#define knh_IntUnit_newClass NULL

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_fenumchk__nop(IntUnit *b, knh_int_t v)
{
	return 1;
}

/* ------------------------------------------------------------------------ */

static
int knh_fenumcmp__signed(IntUnit *b, knh_int_t v1, knh_int_t v2)
{
	return (int)(v1 - v2);
}

/* ------------------------------------------------------------------------ */

static
void knh_fenumfmt__signed(IntUnit *b, char *buf, size_t bufsiz, knh_int_t v)
{
	knh_snprintf(buf, bufsiz, KNH_INT_FMT, v);
}

/* ------------------------------------------------------------------------ */

static
void knh_IntUnit_init(Ctx *ctx, IntUnit *u, int init)
{
	knh_IntUnit_struct *b = DP(u);
	b->spec.flag = 0;
	b->spec.cid  = CLASS_Int;
	KNH_INITv(b->spec.urn,  TS_EMPTY);
	KNH_INITv(b->spec.tag,  TS_EMPTY);
	KNH_INITv(b->spec.defvalue, ctx->share->tInt[0-(KNH_TINT_MIN)]);
	//
	b->step = 1;
	b->max  = KNH_INT_MAX;
	b->min  = KNH_INT_MIN;
	b->fchk = knh_fenumchk__nop;
	b->fcmp = knh_fenumcmp__signed;
	b->ffmt = knh_fenumfmt__signed;
}

/* ------------------------------------------------------------------------ */

static
void knh_IntUnit_traverse(Ctx *ctx, IntUnit *u, knh_ftraverse ftr)
{
	knh_IntUnit_struct *b = DP(u);
	ftr(ctx, UP(b->spec.urn));
	ftr(ctx, UP(b->spec.tag));
	ftr(ctx, b->spec.defvalue);
}

/* ------------------------------------------------------------------------ */

static
String* knh_IntUnit_getkey(Ctx *ctx, knh_sfp_t *lsfp)
{
	return DP((IntUnit*)lsfp[0].o)->spec.urn;
}

/* ======================================================================== */
/* FloatUnit */

#define knh_FloatUnit_init_ NULL
#define knh_FloatUnit_copy NULL
#define knh_FloatUnit_traverse_ NULL
#define knh_FloatUnit_compareTo NULL
#define knh_FloatUnit_hashCode NULL
#define knh_FloatUnit_newClass NULL

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_funitchk__default(FloatUnit *b, knh_float_t v)
{
	return 1;
}

/* ------------------------------------------------------------------------ */

static
int knh_funitcmp__default(FloatUnit *b, knh_float_t v1, knh_float_t v2)
{
	knh_float_t delta = v1 - v2;
	if(delta == 0.0) return 0;
	return delta < 0 ? -1 : 1;
}

/* ------------------------------------------------------------------------ */

static
void knh_funitfmt__default(FloatUnit *b, char *buf, size_t bufsiz, knh_float_t v)
{
	knh_snprintf(buf, bufsiz, KNH_FLOAT_FMT, v);
}

/* ------------------------------------------------------------------------ */

static
void knh_FloatUnit_init(Ctx *ctx, FloatUnit *u, int init)
{
	knh_FloatUnit_struct *b = DP(u);
	b->spec.flag = 0;
	b->spec.cid  = CLASS_Float;
	KNH_INITv(b->spec.urn,  TS_EMPTY);
	KNH_INITv(b->spec.tag,  TS_EMPTY);
	KNH_INITv(b->spec.defvalue, KNH_FLOAT0);
	//
	b->step = 0.0;
	b->max  = KNH_FLOAT_MAX;
	b->min  = KNH_FLOAT_MIN;
	b->fchk = knh_funitchk__default;
	b->fcmp = knh_funitcmp__default;
	b->ffmt = knh_funitfmt__default;
	b->FMT  = KNH_FLOAT_FMT;
}

/* ------------------------------------------------------------------------ */

static
void knh_FloatUnit_traverse(Ctx *ctx, FloatUnit *u, knh_ftraverse gc)
{
	knh_FloatUnit_struct *b = DP(u);
	gc(ctx, UP(b->spec.urn));
	gc(ctx, UP(b->spec.tag));
	gc(ctx, b->spec.defvalue);
}

/* ------------------------------------------------------------------------ */

static
String* knh_FloatUnit_getkey(Ctx *ctx, knh_sfp_t *lsfp)
{
	return DP((FloatUnit*)lsfp[0].o)->spec.urn;
}

/* ======================================================================== */
/* Regex */

#define knh_Regex_init_ NULL
#define knh_Regex_copy NULL
#define knh_Regex_traverse_ NULL
#define knh_Regex_compareTo NULL
#define knh_Regex_hashCode NULL
#define knh_Regex_newClass NULL
#define knh_Regex_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_Regex_init(Ctx *ctx, Regex *o, int init)
{
	KNH_INITv(o->pattern, TS_EMPTY);
	o->df = knh_System_getRegexDriver(ctx, STEXT("NOP"));
	o->reg = NULL;
}

/* ------------------------------------------------------------------------ */

static
void knh_Regex_traverse(Ctx *ctx, Regex *o, knh_ftraverse ftr)
{
	ftr(ctx, UP(o->pattern));
	if(IS_SWEEP(ftr)) {
		if(o->reg != NULL) {
			o->df->regfree(ctx, o->reg);
			o->df = NULL;
			o->reg = NULL;
		}
	}
}

/* ======================================================================== */
/* BytesConv */

#define knh_BytesConv_init_ NULL
#define knh_BytesConv_copy NULL
#define knh_BytesConv_traverse_ NULL
#define knh_BytesConv_compareTo NULL
#define knh_BytesConv_hashCode NULL
#define knh_BytesConv_newClass NULL
#define knh_BytesConv_getkey NULL

size_t knh_fbyteconv_nop(Ctx *ctx, BytesConv *bc, knh_bytes_t t, knh_Bytes_t *ba)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

void knh_fbyteconvfree_nop(Ctx *ctx, BytesConv *bc)
{
}

/* ------------------------------------------------------------------------ */

static
void knh_BytesConv_init(Ctx *ctx, BytesConv *bc, int init)
{
	bc->fbconv  = knh_fbyteconv_nop;
	bc->fbconvfree = knh_fbyteconvfree_nop;
	bc->convp = NULL;
}

/* ------------------------------------------------------------------------ */

static
void knh_BytesConv_traverse(Ctx *ctx, BytesConv *bc, knh_ftraverse ftr)
{
	if(IS_SWEEP(ftr)) {
		bc->fbconvfree(ctx, bc);
		bc->fbconv = knh_fbyteconv_nop;
		bc->fbconvfree = knh_fbyteconvfree_nop;
	}
}

/* ======================================================================== */
/* StringUnit */

#define knh_StringUnit_init_ NULL
#define knh_StringUnit_copy NULL
#define knh_StringUnit_traverse_ NULL
#define knh_StringUnit_compareTo NULL
#define knh_StringUnit_hashCode NULL
#define knh_StringUnit_newClass NULL

/* ------------------------------------------------------------------------ */

static
int knh_fvcabcmp__default(StringUnit *o, knh_bytes_t v1, knh_bytes_t v2)
{
	return knh_bytes_strcmp(v1, v2);
}

/* ------------------------------------------------------------------------ */

static
void knh_StringUnit_init(Ctx *ctx, StringUnit *u, int init)
{
	knh_StringUnit_struct *b = DP(u);

	b->spec.flag = 0;
	b->spec.cid  = CLASS_newid;
	KNH_INITv(b->spec.urn, TS_EMPTY);
	KNH_INITv(b->spec.tag,  TS_EMPTY);
	KNH_INITv(b->spec.defvalue, TS_EMPTY);
	//
	b->fnew = new_StringX__fast;
	b->fcmp = knh_fvcabcmp__default;
	b->fbconv = NULL;
	KNH_INITv(b->bconv, KNH_NULL);
	b->charlen = 0;
	b->bytelen = 0;
	KNH_INITv(b->pattern, KNH_NULL);
	KNH_INITv(b->vocabDictIdx, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

static
void knh_StringUnit_traverse(Ctx *ctx, StringUnit *u, knh_ftraverse gc)
{
	knh_StringUnit_struct *b = DP(u);
	gc(ctx, UP(b->spec.urn));
	gc(ctx, UP(b->spec.tag));
	gc(ctx, b->spec.defvalue);

	gc(ctx, UP(b->bconv));
	gc(ctx, UP(b->pattern));
	gc(ctx, UP(b->vocabDictIdx));
}

/* ------------------------------------------------------------------------ */

static
String* knh_StringUnit_getkey(Ctx *ctx, knh_sfp_t *lsfp)
{
	return DP((StringUnit*)lsfp[0].o)->spec.urn;
}

/* ======================================================================== */
/* InputStream */

#define knh_InputStream_init_ NULL
#define knh_InputStream_copy NULL
#define knh_InputStream_traverse_ NULL
#define knh_InputStream_compareTo NULL
#define knh_InputStream_hashCode NULL
#define knh_InputStream_newClass NULL

static
void knh_InputStream_init(Ctx *ctx, InputStream *in, int init)
{
	knh_InputStream_struct *b = DP(in);
	b->fd = -1;
	KNH_INITv(b->ba, KNH_NULL);
	b->buf = "";
	b->bufpos = 0;
	b->bufend = 0;
	b->bufsiz = 0;
	b->driver = konoha_getDefaultIODriver();
	KNH_INITv(b->bconv, KNH_NULL);
	KNH_INITv(b->enc, TS_ENCODING);
	KNH_INITv(b->urn, TS_DEVNULL);
	b->size    = 0;
	b->line    = 1;
	b->prev    = '\n';
	b->fileid   = 0;
}

/* ------------------------------------------------------------------------ */

static
void knh_InputStream_traverse(Ctx *ctx, InputStream *in, knh_ftraverse ftr)
{
	knh_InputStream_struct *b = DP(in);
	if(IS_SWEEP(ftr) && b->fd != -1) {
		b->driver->fclose(ctx, b->fd);
		b->fd = -1;
	}
	ftr(ctx, UP(b->ba));
	ftr(ctx, UP(b->enc));
	ftr(ctx, UP(b->bconv));
	ftr(ctx, UP(b->urn));
}

/* ------------------------------------------------------------------------ */

static
String* knh_InputStream_getkey(Ctx *ctx, knh_sfp_t *lsfp)
{
	return DP((InputStream*)lsfp[0].o)->urn;
}

/* ======================================================================== */
/* OutputStream */

#define knh_OutputStream_init_ NULL
#define knh_OutputStream_copy NULL
#define knh_OutputStream_traverse_ NULL
#define knh_OutputStream_compareTo NULL
#define knh_OutputStream_hashCode NULL
#define knh_OutputStream_newClass NULL

void
knh_OutputStream_init(Ctx *ctx, OutputStream *out, int init)
{
	knh_OutputStream_struct *b = DP(out);
	b->fd = -1;
	b->driver = konoha_getDefaultIODriver();
	if(init == -1) {
		KNH_INITv(b->ba, KNH_NULL);
	}
	else {
		KNH_INITv(b->ba, new_Bytes(ctx, 4096));
	}
	KNH_INITv(b->bconv, KNH_NULL);
	KNH_INITv(b->enc, TS_ENCODING);
	KNH_INITv(b->urn, TS_DEVNULL);
	b->size = 0;
	b->line = 0;
	KNH_INITv(b->NEWLINE, TS_LF);
	KNH_INITv(b->TAB, TS_TAB);
	b->indent = 0;
	b->flag = 0;
}

/* ------------------------------------------------------------------------ */

static
void knh_OutputStream_traverse(Ctx *ctx, OutputStream *out, knh_ftraverse ftr)
{
	knh_OutputStream_struct *b = DP(out);
	if(IS_SWEEP(ftr) && b->fd != -1) {
		b->driver->fclose(ctx, b->fd);
		b->fd = -1;
	}
	ftr(ctx, UP(b->ba));
	ftr(ctx, UP(b->enc));
	ftr(ctx, UP(b->bconv));
	ftr(ctx, UP(b->urn));
	ftr(ctx, UP(b->NEWLINE));
	ftr(ctx, UP(b->TAB));
}

/* ------------------------------------------------------------------------ */

static
String* knh_OutputStream_getkey(Ctx *ctx, knh_sfp_t *lsfp)
{
	return DP((OutputStream*)lsfp[0].o)->urn;
}

/* ======================================================================== */
/* Socket */

#define knh_Socket_init_ NULL
#define knh_Socket_copy NULL
#define knh_Socket_traverse_ NULL
#define knh_Socket_compareTo NULL
#define knh_Socket_hashCode NULL
#define knh_Socket_newClass NULL

static
void knh_Socket_init(Ctx *ctx, Socket *o, int init)
{
	knh_Socket_struct *so = DP(o);
	so->sd = -1;
	so->port = init;
	KNH_INITv(so->urn, TS_EMPTY);
	KNH_INITv(so->in, konoha_getDefaultValue(ctx, CLASS_InputStream));
	KNH_INITv(so->out, konoha_getDefaultValue(ctx, CLASS_OutputStream));
}

/* ------------------------------------------------------------------------ */

static
void knh_Socket_traverse(Ctx *ctx, Socket *o, knh_ftraverse ftr)
{
	knh_Socket_struct *so = DP(o);
	if(IS_SWEEP(ftr)) {
		if(so->sd != -1) {
			knh_InputStream_close(ctx, so->in);
			knh_OutputStream_close(ctx, so->out);
			knh_socket_close(ctx, so->sd);
			so->sd = -1;
		}
	}
	ftr(ctx, UP(so->urn));
	ftr(ctx, UP(so->in));
	ftr(ctx, UP(so->out));
}

/* ------------------------------------------------------------------------ */

static
String* knh_Socket_getkey(Ctx *ctx, knh_sfp_t *lsfp)
{
	return DP((Socket*)lsfp[0].o)->urn;
}

/* ======================================================================== */
/* Connection */

#define knh_Connection_init_ NULL
#define knh_Connection_copy NULL
#define knh_Connection_traverse_ NULL
#define knh_Connection_compareTo NULL
#define knh_Connection_hashCode NULL
#define knh_Connection_newClass NULL
#define knh_Connection_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_Connection_init(Ctx *ctx, Connection *c, int init)
{
	knh_Connection_struct *b = DP(c);
	b->conn = NULL;
	KNH_INITv(b->urn, TS_EMPTY);
	b->df = knh_System_getDefaultDBDriver();
}

/* ------------------------------------------------------------------------ */

static
void knh_Connection_traverse(Ctx *ctx, Connection *c, knh_ftraverse ftr)
{
	knh_Connection_struct *b = DP(c);
	ftr(ctx, UP(b->urn));
	if(IS_SWEEP(ftr) && b->conn != NULL) {
		b->df->dbclose(ctx, b->conn);
		b->conn = NULL;
		b->df = NULL;
	}
}

/* ======================================================================== */
/* ResultSet */

#define knh_ResultSet_init_ NULL
#define knh_ResultSet_copy NULL
#define knh_ResultSet_traverse_ NULL
#define knh_ResultSet_compareTo NULL
#define knh_ResultSet_hashCode NULL
#define knh_ResultSet_newClass NULL
#define knh_ResultSet_getkey NULL


static
void knh_ResultSet_init(Ctx *ctx, ResultSet *rs, int init)
{
	knh_ResultSet_struct *b = DP(rs);
	b->dbcur = NULL;
	b->tcid = CLASS_ResultSet;
	b->column_size = 0;
	b->column = NULL;
	KNH_INITv(b->databuf, new_Bytes(ctx, 256));
	KNH_INITv(b->conn, KNH_NULL);
	b->dbcur_free = knh_dbcurfree__NOP;
	b->count = 0;
}

/* ------------------------------------------------------------------------ */

static
void knh_ResultSet_traverse(Ctx *ctx, ResultSet *rs, knh_ftraverse ftr)
{
	knh_ResultSet_struct *b = DP(rs);
	ftr(ctx, UP(b->databuf));
	int i = 0;
	for(i = 0; i < b->column_size; i++) {
		ftr(ctx, UP(b->column[i].name));
	}
	if(IS_SWEEP(ftr)) {
		if(b->column != NULL) {
			KNH_FREE(ctx, b->column, sizeof(knh_dbschema_t) * b->column_size);
			b->column = NULL;
		}
		if(b->dbcur != NULL) {
			b->dbcur_free(b->dbcur);
			b->dbcur = NULL;
		}
	}
	ftr(ctx, UP(b->conn));
}

/* ======================================================================== */
/* Exception */

#define knh_Exception_init_ NULL
#define knh_Exception_copy NULL
#define knh_Exception_traverse_ NULL
#define knh_Exception_compareTo NULL
#define knh_Exception_hashCode NULL
#define knh_Exception_newClass NULL
#define knh_Exception_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_Exception_init(Ctx *ctx, Exception *e, int init)
{
	knh_Exception_struct *b = DP(e);
	b->eid  = 1;
	b->flag = 0;
	KNH_INITv(b->message, TS_EMPTY);
	KNH_INITv(b->bag, KNH_NULL);
	KNH_INITv(b->traces, KNH_NULL);
	b->file = "";
	b->line = 0;
}

/* ------------------------------------------------------------------------ */

static
void knh_Exception_traverse(Ctx *ctx, Exception *e, knh_ftraverse ftr)
{
	knh_Exception_struct *b = DP(e);
	ftr(ctx, UP(b->message));
	ftr(ctx, b->bag);
	ftr(ctx, UP(b->traces));
}


/* ======================================================================== */
/* ExceptionHandler */

#define knh_ExceptionHandler_init_ NULL
#define knh_ExceptionHandler_copy NULL
#define knh_ExceptionHandler_traverse_ NULL
#define knh_ExceptionHandler_compareTo NULL
#define knh_ExceptionHandler_hashCode NULL
#define knh_ExceptionHandler_newClass NULL
#define knh_ExceptionHandler_getkey NULL

static
void knh_ExceptionHandler_init(Ctx *ctx, ExceptionHandler *hdr, int init)
{
	knh_ExceptionHandler_struct *b = DP(hdr);
	b->esp = ctx->esp;
	KNH_INITv(b->caught, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

void
knh_ExceptionHandler_traverse(Ctx *ctx, ExceptionHandler *hdr, knh_ftraverse gc)
{
	knh_ExceptionHandler_struct *b = DP(hdr);
	gc(ctx, UP(b->caught));
}

/* ======================================================================== */
/* Script */

#define knh_Script_init_ NULL
#define knh_Script_copy NULL
#define knh_Script_traverse knh_ObjectField_traverse
#define knh_Script_compareTo NULL
#define knh_Script_hashCode NULL
#define knh_Script_newClass NULL
#define knh_Script_getkey NULL

static
void knh_Script_init(Ctx *ctx, Script *s, int init)
{
	s->fields = (Object**)KNH_MALLOC(ctx, sizeof(Object*) * KNH_SCRIPT_FIELDSIZE);
	knh_bzero(s->fields, sizeof(Object*) * KNH_SCRIPT_FIELDSIZE);
}

/* ======================================================================== */
/* NameSpace */

#define knh_NameSpace_init_ NULL
#define knh_NameSpace_copy NULL
#define knh_NameSpace_traverse_ NULL
#define knh_NameSpace_compareTo NULL
#define knh_NameSpace_hashCode NULL
#define knh_NameSpace_newClass NULL

/* ------------------------------------------------------------------------ */

static
void knh_NameSpace_init(Ctx *ctx, NameSpace *ns, int init)
{
	knh_NameSpace_struct *b = DP(ns);
	if(init != KNH_OBJECT_RAWINIT) { /* @see(new_NameSpace) */
		KNH_INITv(b->nsname, KNH_NULL);
	}
	KNH_INITv(b->name2cidDictSet, new_DictSet(ctx, 64));
	KNH_INITv(b->script, KNH_NULL);
	KNH_INITv(b->importedNameSpaces, KNH_NULL);
	KNH_INITv(b->lconstDictMap, KNH_NULL);
	KNH_INITv(b->tag2urnDictMap, KNH_NULL);
	KNH_INITv(b->func2cidDictSet, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

static
void knh_NameSpace_traverse(Ctx *ctx, NameSpace *ns, knh_ftraverse ftr)
{
	knh_NameSpace_struct *b = DP(ns);
	ftr(ctx, UP(b->nsname));
	ftr(ctx, UP(b->script));
	ftr(ctx, UP(b->importedNameSpaces));
	ftr(ctx, UP(b->lconstDictMap));
	ftr(ctx, UP(b->name2cidDictSet));
	ftr(ctx, UP(b->tag2urnDictMap));
	ftr(ctx, UP(b->func2cidDictSet));
}

/* ------------------------------------------------------------------------ */

static
String *knh_NameSpace_getkey(Ctx *ctx, knh_sfp_t *lsfp)
{
	return DP((NameSpace*)lsfp[0].o)->nsname;
}

/* ======================================================================== */
/* System */

#define knh_System_init_ NULL
#define knh_System_copy NULL
#define knh_System_traverse_ NULL
#define knh_System_compareTo NULL
#define knh_System_hashCode NULL
#define knh_System_newClass NULL
#define knh_System_getkey NULL


static knh_uintptr_t knh_autoSystemId = 0;

/* ------------------------------------------------------------------------ */

static
void knh_System_init(Ctx *ctx, System *o, int init)
{
	knh_System_struct *sys = DP(o);
	char buf[FILENAME_BUFSIZ];
	sys->sysid = knh_autoSystemId++;
	sys->ctxcount = 0;

	KNH_INITv(sys->ClassNameDictSet, new_DictSet(ctx, KNH_TCLASS_SIZE/2));
	KNH_INITv(sys->ExptNameDictSet, new_DictSet(ctx, KNH_TEXPT_SIZE/2));

	KNH_INITv(sys->enc,   new_String__T(ctx, konoha_encoding()));
	KNH_INITv(sys->in,    new_InputStream__stdio(ctx, stdin, sys->enc));
	KNH_INITv(sys->out,   new_OutputStream__stdio(ctx, stdout, sys->enc));
	KNH_INITv(sys->err,   new_OutputStream__stdio(ctx, stderr, sys->enc));

	KNH_INITv(sys->props, new_DictMap0(ctx, 64));

	KNH_INITv(sys->FieldNameDictIdx, new_DictIdx0__ignoreCase(ctx, KNH_TFIELDN_SIZE * 2, 0));
	KNH_INITv(sys->FileNameDictIdx, new_DictIdx0(ctx, 32, 0));
	knh_DictIdx_add__fast(ctx, sys->FileNameDictIdx, new_String__T(ctx, "(unknown)"));
	KNH_INITv(sys->MethodFieldHashMap, new_HashMap(ctx, "System.MethodField", (KNH_TCLASS_SIZE * 2) + 31 ));

	KNH_INITv(sys->homeDir, new_String(ctx, B(knh_format_homepath(buf,sizeof(buf))), NULL));
	KNH_INITv(sys->DriversTableDictSet, new_DictSet(ctx, 32));
	KNH_INITv(sys->SpecFuncDictSet, new_DictSet(ctx, 32));

	KNH_INITv(sys->NameSpaceTableDictMap, new_DictMap0(ctx, 8));
	KNH_INITv(sys->URNAliasDictMap, new_DictMap0(ctx, 8));

	knh_DictMap_set(ctx, sys->props, new_String__T(ctx, "konoha.encoding"), UP(sys->enc));
	knh_DictMap_set(ctx, sys->props, new_String__T(ctx, "konoha.home"), UP(sys->homeDir));
	knh_DictMap_set(ctx, sys->props, new_String__T(ctx, "konoha.lang"),
			UP(new_String(ctx, B(knh_format_lang(buf, sizeof(buf))), NULL)));
	//knh_Asm_setLang(buf);

	KNH_INITv(sys->UsingResources, new_Array0(ctx, 0));
	//KNH_INITv(sys->sysnsDictMap_UNUSED, new_DictMap0(ctx, 16));
	//KNH_INITv(sys->funcDictSet_UNUSED, new_DictSet(ctx, 16));

}

/* ------------------------------------------------------------------------ */

static void knh_System_traverse(Ctx *ctx, System *o, knh_ftraverse ftr)
{
	knh_System_struct *sys = DP(o);

	ftr(ctx, UP(sys->enc));
	ftr(ctx, UP(sys->in));
	ftr(ctx, UP(sys->out));
	ftr(ctx, UP(sys->err));

	ftr(ctx, UP(sys->props));
	ftr(ctx, UP(sys->ExptNameDictSet));
	ftr(ctx, UP(sys->ClassNameDictSet));

	ftr(ctx, UP(sys->FieldNameDictIdx));
	ftr(ctx, UP(sys->FileNameDictIdx));

	ftr(ctx, UP(sys->MethodFieldHashMap));
	ftr(ctx, UP(sys->NameSpaceTableDictMap));
	ftr(ctx, UP(sys->URNAliasDictMap));

	ftr(ctx, UP(sys->homeDir));
	ftr(ctx, UP(sys->DriversTableDictSet));
	ftr(ctx, UP(sys->SpecFuncDictSet));
	ftr(ctx, UP(sys->UsingResources));
	//ftr(ctx, UP(sys->sysnsDictMap_UNUSED));
	//ftr(ctx, UP(sys->funcDictSet_UNUSED));
}

/* ======================================================================== */
/* Context */

#define knh_Context_init_ NULL
#define knh_Context_copy NULL
#define knh_Context_traverse_ NULL
#define knh_Context_compareTo NULL
#define knh_Context_hashCode NULL
#define knh_Context_newClass NULL
#define knh_Context_getkey NULL

/* ------------------------------------------------------------------------ */

void knh_Context_init(Ctx *ctx, knh_Context_t *o, int init)
{
	/* Context can be only instatiated in new_Context() */
	KNH_THROWs(ctx, "Abort!!");
}

/* ======================================================================== */
/* Token */

#define knh_Token_init_ NULL
#define knh_Token_copy NULL
#define knh_Token_traverse_ NULL
#define knh_Token_compareTo NULL
#define knh_Token_hashCode NULL
#define knh_Token_newClass NULL
#define knh_Token_getkey NULL


static
void knh_Token_init(Ctx *ctx, Token *tk, int init)
{
	knh_Token_struct *b = DP(tk);
	b->tt_next = TT_EOT;
	b->type    =  CLASS_Any;
	KNH_INITv(b->data, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

static
void knh_Token_traverse(Ctx *ctx, Token *tk, knh_ftraverse gc)
{
	knh_Token_struct *b = DP(tk);
	gc(ctx, b->data);
}

/* ======================================================================== */
/* Stmt */

#define knh_Stmt_init_ NULL
#define knh_Stmt_copy NULL
#define knh_Stmt_traverse_ NULL
#define knh_Stmt_compareTo NULL
#define knh_Stmt_hashCode NULL
#define knh_Stmt_newClass NULL
#define knh_Stmt_getkey NULL

static
void knh_Stmt_init(Ctx *ctx, Stmt *stmt, int init)
{
	knh_Stmt_struct *b = DP(stmt);
	b->size = 0;
	b->capacity = init;
	b->type = TYPE_void;
	b->line_end = 0;
	if(b->capacity > 0) {
		b->terms = (Object**)KNH_MALLOC(ctx, sizeof(Term*) * b->capacity);
		size_t i;
		for(i = 0; i < b->capacity; i++) {
			KNH_INITv(b->terms[i], KNH_NULL);
		}
	}else {
		b->terms = NULL;
	}
	KNH_INITv(b->metaDictMap,  KNH_NULL);
	KNH_INITv(b->next,  KNH_NULL);
}

/* ------------------------------------------------------------------------ */

static
void knh_Stmt_terms_traverse(Ctx *ctx, knh_Stmt_struct *b, knh_ftraverse ftr)
{
	size_t i;
	for(i = 0; i < b->capacity; i++) {
		ftr(ctx, b->terms[i]);
	}
	if(IS_SWEEP(ftr)) {
		KNH_FREE(ctx, b->terms, sizeof(Term*) * b->capacity);
		b->terms = NULL;
		b->capacity = 0;
		b->size = 0;
	}
}

/* ------------------------------------------------------------------------ */

void knh_Stmt_done(Ctx *ctx, Stmt *o)
{
	SP(o)->stt = STT_DONE;
	if(DP(o)->terms != NULL) {
		knh_Stmt_terms_traverse(ctx, DP(o), knh_Object_sweep);
	}
	KNH_SETv(ctx, DP(o)->metaDictMap, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

static
void knh_Stmt_traverse(Ctx *ctx, Stmt *stmt, knh_ftraverse ftr)
{
	knh_Stmt_struct *b = DP(stmt);
	if(b->terms != NULL) {
		knh_Stmt_terms_traverse(ctx, b, ftr);
	}
	ftr(ctx, UP(b->metaDictMap));
	ftr(ctx, UP(b->next));
}

/* ======================================================================== */
/* Asm */

#define knh_Asm_init_ NULL
#define knh_Asm_copy NULL
#define knh_Asm_traverse_ NULL
#define knh_Asm_compareTo NULL
#define knh_Asm_hashCode NULL
#define knh_Asm_newClass NULL
#define knh_Asm_getkey NULL

static
void knh_Asm_init(Ctx *ctx, Asm *abr, int init)
{
	knh_Asm_struct *b = DP(abr);
	b->flag = 0;
	b->this_cid = CLASS_Object;

	KNH_INITv(b->ns, knh_System_getNameSpace(ctx, STEXT("main")));
	KNH_INITv(b->mtd,   KNH_NULL);
	b->level = 0;

	knh_intptr_t i;
	b->vars = (knh_cfield_t*)KNH_MALLOC(ctx, KONOHA_LOCALSIZE * sizeof(knh_cfield_t));
	b->vars_size = 0;
	for(i = 0; i < KONOHA_LOCALSIZE; i++) {
		b->vars[i].flag  = 0;
		b->vars[i].type  = TYPE_Any;
		b->vars[i].fn    = FIELDN_NONAME;
//		b->vars[i].count = 0;
		KNH_INITv(b->vars[i].value, KNH_NULL);
	}
	b->stack = 0;
	b->globalidx = -1;

	b->regs = (knh_asmreg_t*)KNH_MALLOC(ctx, KNH_ASM_REGMAX * sizeof(knh_asmreg_t));
	b->regs_size = 0;

	b->labels = NULL;
	b->labelmax = 0;
	b->labelcapacity = 0;
	KNH_INITv(b->name2labelIdDictSet, new_DictSet(ctx, 256));

	KNH_INITv(b->lstacks, new_Array(ctx, CLASS_String, 8));
	KNH_INITv(b->finallyStmt, KNH_NULL);

	b->fileid = 0;
	b->line = 0;
	KNH_INITv(b->elf, new_Bytes(ctx, 4096));
	KNH_INITv(b->dwarf, new_Bytes(ctx, 1024));

	b->dlhdr = NULL;
	KNH_INITv(b->constPools, KNH_NULL);
	KNH_INITv(b->exportsMethods, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

static
void knh_Asm_traverse(Ctx *ctx, Asm *abr, knh_ftraverse ftr)
{
	knh_Asm_struct *b = DP(abr);
	size_t i;
	for(i = 0; i < KONOHA_LOCALSIZE; i++) {
		ftr(ctx, b->vars[i].value);
	}
	for(i = 0; i < b->labelcapacity; i++) {
		ftr(ctx, UP(b->labels[i].tklabel));
	}
	if(IS_SWEEP(ftr)) {
		KNH_FREE(ctx, b->vars, KONOHA_LOCALSIZE * sizeof(knh_cfield_t));
		if(b->labels != NULL) {
			KNH_FREE(ctx, b->labels, b->labelcapacity * sizeof(knh_labeltbl_t));
		}
		KNH_FREE(ctx, b->regs, KNH_ASM_REGMAX * sizeof(knh_asmreg_t));
		b->regs_size = 0;
	}

	ftr(ctx, UP(b->ns));
	ftr(ctx, UP(b->mtd));
	ftr(ctx, UP(b->elf));
	ftr(ctx, UP(b->dwarf));

	ftr(ctx, UP(b->name2labelIdDictSet));
	ftr(ctx, UP(b->lstacks));
	ftr(ctx, UP(b->finallyStmt));

	if(IS_SWEEP(ftr) && b->dlhdr != NULL) {
		b->dlhdr = NULL;
	}
	ftr(ctx, UP(b->exportsMethods));
	ftr(ctx, UP(b->constPools));
}

/* ======================================================================== */
/* KLRCode */

#define knh_KLRCode_init_ NULL
#define knh_KLRCode_copy NULL
#define knh_KLRCode_traverse_ NULL
#define knh_KLRCode_compareTo NULL
#define knh_KLRCode_hashCode NULL
#define knh_KLRCode_newClass NULL
#define knh_KLRCode_getkey NULL

/* ------------------------------------------------------------------------ */

static
void knh_KLRCode_init(Ctx *ctx, KLRCode *o, int init)
{
	knh_KLRCode_struct *b = DP(o);
	b->size = 0;
	b->code = (knh_code_t*)"";
	b->fileid = 0;
//	b->nsid = 0;
	b->dwarf = NULL;
	b->dsize = 0;
}

/* ------------------------------------------------------------------------ */

void knh_code_traverse(Ctx *ctx, knh_code_t *pc, knh_ftraverse ftr);

/* ------------------------------------------------------------------------ */

static
void knh_KLRCode_traverse(Ctx *ctx, KLRCode *o, knh_ftraverse ftr)
{
	knh_KLRCode_struct *b = DP(o);
	knh_code_traverse(ctx, b->code, ftr);
	if(IS_SWEEP(ftr)) {
		KNH_FREE(ctx, b->code, KNH_SIZE(b->size));
		if(b->dwarf != NULL) {
			KNH_FREE(ctx, b->dwarf, b->dsize * sizeof(knh_dwarf_t));
		}
	}
}

/* ======================================================================== */
/* [default] */

#define knh_Object_fdefault NULL
#define knh_Any_fdefault NULL
#define knh_This_fdefault NULL
#define knh_Any0_fdefault NULL
#define knh_Any1_fdefault NULL
#define knh_Any2_fdefault NULL
#define knh_Any3_fdefault NULL
#define knh_Nue_fdefault NULL
#define knh_Boolean_fdefault_ NULL
#define knh_Number_fdefault NULL
#define knh_Int_fdefault_ NULL
#define knh_IntX_fdefault_ NULL
#define knh_Float_fdefault_ NULL
#define knh_FloatX_fdefault_ NULL
#define knh_String_fdefault_ NULL
#define knh_StringX_fdefault_ NULL
#define knh_Bytes_fdefault NULL
#define knh_Tuple2_fdefault NULL
#define knh_Range_fdefault NULL
#define knh_Array_fdefault NULL
#define knh_IArray_fdefault NULL
#define knh_FArray_fdefault NULL
#define knh_Iterator_fdefault NULL
#define knh_DictMap_fdefault NULL
#define knh_DictSet_fdefault NULL
#define knh_HashMap_fdefault NULL
#define knh_HashSet_fdefault NULL
#define knh_LRUHashMap_fdefault NULL
#define knh_DictIdx_fdefault NULL
#define knh_Class_fdefault_ NULL
#define knh_ClassStruct_fdefault NULL
#define knh_MethodField_fdefault NULL
#define knh_Method_fdefault NULL
#define knh_Mapper_fdefault NULL
#define knh_ClassMap_fdefault NULL
#define knh_Closure_fdefault NULL
#define knh_AffineConv_fdefault NULL
#define knh_IntUnit_fdefault NULL
#define knh_FloatUnit_fdefault NULL
#define knh_Regex_fdefault NULL
#define knh_BytesConv_fdefault NULL
#define knh_StringUnit_fdefault NULL
#define knh_InputStream_fdefault NULL
#define knh_OutputStream_fdefault NULL
#define knh_Socket_fdefault NULL
#define knh_Connection_fdefault NULL
#define knh_ResultSet_fdefault NULL
#define knh_Exception_fdefault NULL
#define knh_ExceptionHandler_fdefault_ NULL
#define knh_Script_fdefault NULL
#define knh_NameSpace_fdefault_ NULL
#define knh_System_fdefault_ NULL
#define knh_Context_fdefault_ NULL
#define knh_Token_fdefault NULL
#define knh_Stmt_fdefault NULL
#define knh_Asm_fdefault NULL
#define knh_KLRCode_fdefault NULL

/* ------------------------------------------------------------------------ */

static
Object *knh_Boolean_fdefault(Ctx *ctx, knh_class_t cid)
{
	return KNH_FALSE;
}

/* ------------------------------------------------------------------------ */

static
Object *knh_Class_fdefault(Ctx *ctx, knh_class_t cid)
{
	return (Object*)ctx->share->ClassTable[CLASS_Class].class_cid;
}

/* ------------------------------------------------------------------------ */

static
Object *knh_Context_fdefault(Ctx *ctx, knh_class_t cid)
{
	return (Object*)ctx;
}

/* ------------------------------------------------------------------------ */

static
Object *knh_ExceptionHandler_fdefault(Ctx *ctx, knh_class_t cid)
{
	return (Object*)new_Object_bcid(ctx, CLASS_ExceptionHandler, 0);
}


/* ------------------------------------------------------------------------ */

static
Object *knh_Float_fdefault(Ctx *ctx, knh_class_t cid)
{
	return (Object*)KNH_FLOAT0;
}

/* ------------------------------------------------------------------------ */

static
Object *knh_FloatX_fdefault(Ctx *ctx, knh_class_t cid)
{
	FloatUnit *o = (FloatUnit*)ctx->share->ClassTable[cid].cspec;
	KNH_ASSERT(IS_FloatUnit(o));
	return DP(o)->spec.defvalue;
}

/* ------------------------------------------------------------------------ */

static
Object *knh_Int_fdefault(Ctx *ctx, knh_class_t cid)
{
	return (Object*)KNH_INT0;
}

/* ------------------------------------------------------------------------ */

static
Object *knh_IntX_fdefault(Ctx *ctx, knh_class_t cid)
{
	IntUnit *o = (IntUnit*)ctx->share->ClassTable[cid].cspec;
	KNH_ASSERT(IS_IntUnit(o));
	return DP(o)->spec.defvalue;
}

/* ------------------------------------------------------------------------ */

static
Object *knh_String_fdefault(Ctx *ctx, knh_class_t cid)
{
	return (Object*)TS_EMPTY;
}

/* ------------------------------------------------------------------------ */

static
Object *knh_StringX_fdefault(Ctx *ctx, knh_class_t cid)
{
	StringUnit *u = (StringUnit*)ctx->share->ClassTable[cid].cspec;
	KNH_ASSERT(IS_StringUnit(u));
	return DP(u)->spec.defvalue;
}

/* ------------------------------------------------------------------------ */

static
Object *knh_NameSpace_fdefault(Ctx *ctx, knh_class_t cid)
{
	return UP(ctx->ns);
}

/* ------------------------------------------------------------------------ */

static
Object *knh_System_fdefault(Ctx *ctx, knh_class_t cid)
{
	return (Object*)ctx->sys;
}

/* ======================================================================== */
/* [commons] */

#ifdef __cplusplus
}
#endif

#define KNH_CC_METHODAPI
#include"../gen/method_.c"
#include"../api/objectapi.c"
#include"../api/numberapi.c"
#include"../api/stringapi.c"

#include"../api/bytesapi.c"
#include"../api/arrayapi.c"
#include"../api/dictapi.c"
#include"../api/hashapi.c"

#include"../api/systemapi.c"
#include"../api/streamapi.c"
#include"../api/dbapi.c"

#include<konoha/gen/struct_.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [load] */

char *konoha_geStructTableName(Ctx *ctx, knh_struct_t sid)
{
	if(sid < (sizeof(StructName) / sizeof(char*))) {
		return StructName[sid];
	}
	DBG2_P("unknown sid=%d", sid);
	return "STRUCT_unknown";
}

/* ------------------------------------------------------------------------ */

static
void konoha_loadStringData(Ctx *ctx, knh_StringData_t *data)
{
	while(data->name != NULL) {
		KNH_ASSERT(ctx->share->tString[data->index] == NULL);
		KNH_ASSERT(data->index < (SIZEOF_TSTRING / sizeof(String*)));
		KNH_INITv(ctx->share->tString[data->index], new_String__T(ctx, data->name));
		data++;
	}
}

/* ------------------------------------------------------------------------ */

void konoha_loadSystemString(Ctx *ctx)
{
	konoha_loadStringData(ctx, StringData);
}

/* ------------------------------------------------------------------------ */
/* StructData */

/* ------------------------------------------------------------------------ */

static void knh_finit__default(Ctx *ctx, Object *o, int init)
{
}

/* ------------------------------------------------------------------------ */

static void knh_ftraverse__default(Ctx *ctx, Object *o, knh_ftraverse f)
{
}

/* ------------------------------------------------------------------------ */

static int knh_fcompareTo__default(Object *o1, Object *o2)
{
	return (int)((knh_intptr_t)o1 - (knh_intptr_t)o2);
}

/* ------------------------------------------------------------------------ */

static Object *knh_fcopy__default(Ctx *ctx, Object *o)
{
	return o;
}

/* ------------------------------------------------------------------------ */

static knh_hcode_t knh_fhashCode__default(Ctx *ctx, Object* o1)
{
	return ((knh_hcode_t)o1) / sizeof(Object*);
}

/* ------------------------------------------------------------------------ */

static void knh_fnewClass__default(Ctx *ctx, knh_class_t cid)
{
}

/* ------------------------------------------------------------------------ */

static String* knh_fgetkey__default(Ctx *ctx, knh_sfp_t *lsfp)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), "%s.%p", CLASSN(knh_Object_cid(lsfp[0].o)), lsfp[0].o);
	return new_String(ctx, B(buf), NULL);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_loadStructData(Ctx *ctx, knh_StructData_t *data)
{
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	knh_StructData_t *d = data;
	while(d->name != NULL) {
		if(!(ctx->share->StructTableSize < KNH_TSTRUCT_SIZE)) {
			KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
			KNH_EXIT("enlarge KNH_TSTRUCT_SIZE %d", KNH_TSTRUCT_SIZE);
			return;
		}
		KNH_ASSERT(d->size % sizeof(Object*) == 0);
		int sid = d->sid;
		if(sid == STRUCT_newid) sid = ctx->share->StructTableSize;
		KNH_ASSERT(sid == ctx->share->StructTableSize);
		ctx->share->StructTableSize++;
		ctx->share->StructTable[sid].name = d->name;
		ctx->share->StructTable[sid].size = d->size;
		ctx->share->StructTable[sid].flag = KNH_FLAG_CF2OF(d->flag);
		ctx->share->StructTable[sid].sid  = (knh_struct_t)sid;
		ctx->share->StructTable[sid].finit = (d->finit != NULL) ? d->finit : knh_finit__default;
		ctx->share->StructTable[sid].ftraverse = (d->ftraverse != NULL) ? d->ftraverse : knh_ftraverse__default;
		ctx->share->StructTable[sid].fcopy = (d->fcopy != NULL) ? d->fcopy : knh_fcopy__default;
		ctx->share->StructTable[sid].fcompareTo = (d->fcompareTo != NULL) ? d->fcompareTo : knh_fcompareTo__default;
		ctx->share->StructTable[sid].fhashCode = (d->fhashCode != NULL) ? d->fhashCode : knh_fhashCode__default;
		ctx->share->StructTable[sid].fnewClass = (d->fnewClass != NULL) ? d->fnewClass : knh_fnewClass__default;
		ctx->share->StructTable[sid].fgetkey = (d->fgetkey != NULL) ? d->fgetkey : knh_fgetkey__default;
		d++;
	}
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
}

/* ------------------------------------------------------------------------ */

static
void konoha_loadClassData(Ctx *ctx, knh_ClassData_t *data)
{
	while(data->name != NULL) {
		knh_class_t cid = data->cid;
		if(cid + 1 == ctx->share->ClassTableSize) {
			ctx->share->ClassTableSize = cid;
		}

		konoha_setClassName(ctx, cid, new_String__T(ctx, data->name));

		ctx->share->ClassTable[cid].cflag  = data->flag;
		ctx->share->ClassTable[cid].oflag  = KNH_FLAG_CF2OF(data->flag);

		ctx->share->ClassTable[cid].bcid   = data->bcid;
		ctx->share->ClassTable[cid].supcid = data->supcid;
		if(data->bcid == CLASS_Object && data->supcid != CLASS_Object) {
			ctx->share->ClassTable[cid].offset = ctx->share->ClassTable[data->supcid].bsize;
		}else {
			ctx->share->ClassTable[cid].offset = 0;
		}

		if(data->bcid == CLASS_Object) {
			ctx->share->ClassTable[cid].sid = STRUCT_FIELD(data->field_size);
			ctx->share->ClassTable[cid].bsize = (ctx->share->ClassTable[cid].offset + data->field_size);

		}else if(data->bcid == CLASS_Script ) {
			ctx->share->ClassTable[cid].sid = STRUCT_Script;
			ctx->share->ClassTable[cid].bsize = data->field_size;
			ctx->share->ClassTable[cid].size = ctx->share->ClassTable[cid].bsize * sizeof(knh_Object_t*);
		}
		else {
			KNH_ASSERT(ctx->share->ClassTable[cid].offset == 0);
			ctx->share->ClassTable[cid].sid    = (knh_struct_t)data->bcid;
			ctx->share->ClassTable[cid].size =   ctx->share->StructTable[data->bcid].size;
			ctx->share->ClassTable[cid].bsize  = ctx->share->ClassTable[cid].size / sizeof(knh_Object_t*);
		}

		KNH_ASSERT(ctx->share->ClassTable[cid].cstruct == NULL);
		if(data->method_size > 0) {
			KNH_INITv(ctx->share->ClassTable[cid].cstruct, new_ClassStruct0(ctx, data->field_size, data->method_size));
		}
		else {
			KNH_INITv(ctx->share->ClassTable[cid].cstruct, ctx->share->ClassTable[data->supcid].cstruct);
		}
		KNH_ASSERT(ctx->share->ClassTable[cid].cmap == NULL);
		ClassMap *cm = ctx->share->ClassTable[CLASS_Any].cmap;
		if((data->flag & KNH_FLAG_CF_PRIVATE) == 0 || cid == CLASS_Any) {
			cm = new_ClassMap0(ctx, data->mapper_size);
		}
		KNH_INITv(ctx->share->ClassTable[cid].cmap, cm);
		konoha_setClassDefaultValue(ctx, cid, KNH_NULL, data->fdefault);
		data++;
	}
}

/* ------------------------------------------------------------------------ */

static
void konoha_loadGenericsData(Ctx *ctx, knh_GenericsData_t *data)
{
	while(data->name != NULL) {
		konoha_addGenericsClass(ctx, data->cid, new_String__T(ctx, data->name), data->bcid, data->p1, data->p2);
		data++;
	}
}

/* ------------------------------------------------------------------------ */

static
void konoha_loadClosureData(Ctx *ctx, knh_ClosureData_t *data)
{
	while(data->name != NULL) {
		konoha_addClosureClass(ctx, data->cid, new_String__T(ctx, data->name), data->r0, data->p1, data->p2, data->p3);
		data++;
	}
}

/* ------------------------------------------------------------------------ */

static
void konoha_loadExptData(Ctx *ctx, knh_ExptData_t *data)
{
	while(data->name != NULL) {
		konoha_addException(ctx, data->flag, data->eid, new_String__T(ctx, data->name), data->parent);
		data++;
	}
}

/* ------------------------------------------------------------------------ */

static
void konoha_loadFuncData(Ctx *ctx, knh_FuncData_t *data)
{
	while(data->name != NULL) {
		knh_DictSet_set(ctx, DP(ctx->sys)->funcDictSet_UNUSED, new_String__T(ctx, data->name), (knh_uintptr_t)data->func);
		data++;
	}
}

/* ------------------------------------------------------------------------ */

static
void konoha_loadFieldNameData(Ctx *ctx, knh_FieldNameData_t *data)
{
	while(data->name != NULL) {
		String *name = new_String__T(ctx, data->name);
#if defined(KNH_DBGMODE2)
		knh_fieldn_t fn = (knh_fieldn_t)knh_DictIdx_add__fast(ctx, DP(ctx->sys)->FieldNameDictIdx, name);
			//DEBUG("'%s' %d %d", knh_String_tochar(name), fn, fn2);
		KNH_ASSERT(fn == data->fn);
#else
		knh_DictIdx_add__fast(ctx, DP(ctx->sys)->FieldNameDictIdx, name);
#endif
		data++;
	}
}

/* ------------------------------------------------------------------------ */

static
void konoha_loadMethodFieldData(Ctx *ctx, knh_MethodFieldData_t *data, MethodField **pools)
{
	int chk = -1;
	while(data->mfindex != -1) {
		DBG2_ASSERT(data->mfindex < KNH_TMETHODFIELD_SIZE);
		DBG2_ASSERT(data->mfindex > chk); chk = data->mfindex;
		MethodField *mf = new_MethodField(ctx, data->rtype, data->psize);
		if(mf->psize == 1) {
			mf->p0.type = data->t1; mf->p0.fn = data->f1;
		}
		else if(mf->psize == 2) {
			mf->p0.type = data->t1; mf->p0.fn = data->f1;
			mf->p1.type = data->t2; mf->p1.fn = data->f2;
		}
		else if(mf->psize > KNH_METHODFIELD_2) {
			if(data->psize >= 1) {
				mf->mparams[0].type = data->t1;
				mf->mparams[0].fn = data->f1;
			}
			if(data->psize >= 2) {
				mf->mparams[1].type = data->t2;
				mf->mparams[1].fn = data->f2;
			}
			if(data->psize >= 3) {
				mf->mparams[2].type = data->t3;
				mf->mparams[2].fn = data->f3;
			}
			if(data->psize >= 4) {
				mf->mparams[3].type = data->t4;
				mf->mparams[3].fn = data->f4;
			}
		}
		pools[data->mfindex] = mf;
		data++;
	}
}

/* ------------------------------------------------------------------------ */

static
void konoha_loadMethodData(Ctx *ctx, knh_MethodData_t *data, MethodField **pools)
{
	while(data->func != NULL) {
		KNH_ASSERT_cid(data->cid);
		Method *mtd = new_Method(ctx, data->flag, data->cid, data->mn, data->func);
		DP(mtd)->code  = data->optfunc;
		DP(mtd)->delta = data->delta;
		DBG2_ASSERT(data->mfindex < KNH_TMETHODFIELD_SIZE);
		MethodField *mf = pools[data->mfindex];
		KNH_ASSERT(IS_MethodField(mf));
		KNH_SETv(ctx, DP(mtd)->mf, mf);

		ClassStruct *cs = ctx->share->ClassTable[data->cid].cstruct;
		if(knh_class_isSingleton(data->cid)) {
			DP(mtd)->flag = DP(mtd)->flag | KNH_FLAG_MF_STATIC;
		}
		knh_Array_add(ctx, cs->methods, UP(mtd));
		data++;
	}
}

/* ------------------------------------------------------------------------ */

static
void konoha_loadMapperData(Ctx *ctx, knh_MapperData_t *data)
{
	while(data->func != NULL) {
		konoha_addMapperFunc(ctx, data->flag, data->scid, data->tcid, data->func, KNH_NULL);
		data++;
	}
}

/* ------------------------------------------------------------------------ */

static void konoha_loadStringPropertyData(Ctx *ctx, knh_StringConstData_t *data)
{
	DictMap *pmap = DP(ctx->sys)->props;
	while(data->name != NULL) {
		String *n = new_String__T(ctx, data->name);
		knh_DictMap_append(ctx, pmap, n, UP(new_String__T(ctx, data->value)));
		data++;
	}
}

/* ------------------------------------------------------------------------ */
/* @data */

static knh_IntConstData_t IntConstData[] = {
	{"Int.MAX", KNH_INT_MAX},
	{"Int.MIN", KNH_INT_MIN},
	{NULL, 0}
};

static knh_FloatConstData_t FloatConstData[] = {
	{"Float.MAX", KNH_FLOAT_MAX},
	{"Float.MIN", KNH_FLOAT_MIN},
	{NULL, 0.0}
};

static knh_StringConstData_t StringConstData[] = {
	{NULL, NULL}
};

static knh_StringConstData_t StringPropertyData[] = {
	{"konoha.version", KONOHA_VERSION},
	{"konoha.os", KONOHA_OS},
	{"konoha.platform", KONOHA_PLATFORM},
	{NULL, NULL}
};

/* ------------------------------------------------------------------------ */

static void konoha_loadClassProperties(Ctx *ctx)
{
	KNH_SETv(ctx, ctx->share->ClassTable[CLASS_Int].cspec,
		new_IntUnit(ctx, 0, CLASS_Int, TS_EMPTY, TS_EMPTY, KNH_INT_MIN, KNH_INT_MAX, 0));
	KNH_SETv(ctx, ctx->share->ClassTable[CLASS_Float].cspec,
			new_FloatUnit(ctx, 0, CLASS_Float, TS_EMPTY, KNH_FLOAT_MIN, KNH_FLOAT_MAX, 0.0, 0.0));
	KNH_SETv(ctx, ctx->share->ClassTable[CLASS_String].cspec,
			new_StringUnit(ctx, 0, CLASS_String, TS_EMPTY));

	konoha_setClassParam(ctx, CLASS_Array, CLASS_Any, CLASS_Nue);
	konoha_setClassParam(ctx, CLASS_Iterator, CLASS_Any, CLASS_Nue);
	konoha_setClassParam(ctx, CLASS_DictMap, CLASS_Any, CLASS_Nue);
	konoha_setClassParam(ctx, CLASS_DictSet, CLASS_Any, CLASS_Nue);
	konoha_setClassParam(ctx, CLASS_HashMap, CLASS_Any, CLASS_Any);
	konoha_setClassParam(ctx, CLASS_HashSet, CLASS_Any, CLASS_Any);
	ctx->share->ClassTable[CLASS_Closure].r0 = CLASS_Any;
	ctx->share->ClassTable[CLASS_Closure].p1 = CLASS_Any;
	ctx->share->ClassTable[CLASS_Closure].p2 = CLASS_Any;
	ctx->share->ClassTable[CLASS_Closure].p3 = CLASS_Any;

	konoha_loadIntConstData(ctx, IntConstData);
	konoha_loadFloatConstData(ctx, FloatConstData);
	konoha_loadStringConstData(ctx, StringConstData);
	konoha_loadStringPropertyData(ctx, StringPropertyData);
}

/* ------------------------------------------------------------------------ */

void konoha_loadSystemStructData(Ctx *ctx)
{
	konoha_loadStructData(ctx, StructData);
}

/* ------------------------------------------------------------------------ */

void konoha_loadSystemData(Ctx *ctx)
{
	konoha_loadClassData(ctx, ClassData);

	konoha_loadClassProperties(ctx);
	konoha_loadGenericsData(ctx, GenericsData);
	konoha_loadClosureData(ctx, ClosureData);
	konoha_loadExptData(ctx, ExptData);
	konoha_loadFuncData(ctx, FuncData);

	konoha_loadFieldNameData(ctx, FieldNameData);
	{
		MethodField *pools[KNH_TMETHODFIELD_SIZE];
		konoha_loadMethodFieldData(ctx, MethodFieldData, pools);
		konoha_loadMethodData(ctx, MethodData, pools);
		int i;
		for(i = 0; i < KNH_TMETHODFIELD_SIZE; i++) {
			konoha_addMethodFieldTable(ctx, pools[i]);
		}
	}
	konoha_loadMapperData(ctx, MapperData);

	knh_finit_ *f = InitFuncData;
	while(f[0] != NULL) {
		f[0](ctx);
		f++;
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
