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
/* [Int] */

static
int knh_fichk__range(ClassSpec *u, knh_int_t v)
{
	return (DP(u)->imin <= v && v <= DP(u)->imax);
}

/* ------------------------------------------------------------------------ */

static
int knh_fichk__umax(ClassSpec *u, knh_uint_t v)
{
	return (v <= DP(u)->umax);
}

/* ------------------------------------------------------------------------ */

static
int knh_fichk__urange(ClassSpec *u, knh_uint_t v)
{
	return (DP(u)->umin <= v && v <= DP(u)->umax);
}

/* ------------------------------------------------------------------------ */

static
int knh_ficmp__unsigned(ClassSpec *u, knh_uint_t v1, knh_uint_t v2)
{
	if(v1 == v2) return 0;
	return (v1 > v2) ? 1 : -1;
}

/* ------------------------------------------------------------------------ */
/* [Float] */

static
int knh_ffchk__range(ClassSpec *u, knh_float_t v)
{
	return (DP(u)->fmin <= v && v <= DP(u)->fmax);
}

/* ------------------------------------------------------------------------ */

static
int knh_ffcmp__step(ClassSpec *u, knh_float_t v1, knh_float_t v2)
{
	knh_float_t v = v1 - v2;
	if(v >= DP(u)->fstep) return 1;
	if(v <= -(DP(u)->fstep)) return -1;
	return 0;
}

/* ------------------------------------------------------------------------ */

static
void knh_ClassSpec_initIntRange(Ctx *ctx, ClassSpec *u, knh_int_t min, knh_int_t max)
{
	DP(u)->imin = min;
	DP(u)->fmin = (knh_float_t)min;
	DP(u)->imax = max;
	DP(u)->fmax = (knh_float_t)max;
	DP(u)->fstep = 1.0;

	if(min >= 0) {
		DP(u)->ficmp = (knh_ficmp)knh_ficmp__unsigned;
		if(min == 0) {
			DP(u)->fichk = (knh_fichk)knh_fichk__umax;
		}
		else {
			DP(u)->fichk = (knh_fichk)knh_fichk__urange;
		}
		DP(u)->ffchk = knh_ffchk__range;
	}
	else {
		if(min != KNH_INT_MIN || max != KNH_INT_MAX) {
			DP(u)->fichk = knh_fichk__range;
			DP(u)->ffchk = knh_ffchk__range;
		}
	}
	DP(u)->ffcmp = knh_ffcmp__step;
}

/* ------------------------------------------------------------------------ */

void knh_write_intx(Ctx *ctx, OutputStream *w, ClassSpec *u, knh_int_t v)
{
	char *FMT = KNH_INT_FMT;
	if(DP(u)->imin >= 0) {
		FMT = KNH_UINT_FMT;
	}
	knh_write__ffmt(ctx, w, FMT, v);
	knh_bytes_t tag = knh_String_tobytes(DP(u)->tag);
	if(tag.len > 0) {
		knh_putc(ctx, w, '[');
		knh_write(ctx, w, tag);
		knh_putc(ctx, w, ']');
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_ClassSpec_initFloatRange(Ctx *ctx, ClassSpec *u, knh_float_t min, knh_float_t max, knh_float_t step)
{
	DP(u)->fmin = min;
	DP(u)->fmax = max;
	DP(u)->fstep = step;
	DP(u)->imax = (knh_int_t)max;
	DP(u)->imin = (knh_int_t)min;

	if(min >= 0.0) {
		DP(u)->ficmp = (knh_ficmp)knh_ficmp__unsigned;
		if(min == 0) {
			DP(u)->fichk = (knh_fichk)knh_fichk__umax;
		}
		else {
			DP(u)->fichk = (knh_fichk)knh_fichk__urange;
		}
		DP(u)->ffchk = knh_ffchk__range;
	}
	else {
		if(min != KNH_FLOAT_MIN || max != KNH_FLOAT_MAX) {
			DP(u)->fichk = knh_fichk__range;
			DP(u)->ffchk = knh_ffchk__range;
		}
	}
	if(step != 0.0) {
		DP(u)->ffcmp = knh_ffcmp__step;
	}
}

/* ------------------------------------------------------------------------ */

void knh_write_floatx(Ctx *ctx, OutputStream *w, ClassSpec *u, knh_float_t v)
{
	char *FMT = KNH_FLOAT_FMT;
	knh_float_t step = DP(u)->fstep;
	if(0.1 <= step && step < 1.0) {
		FMT = KNH_FLOAT_FMT1;
	}
	else if(0.01 <= step && step < 0.1) {
		FMT = KNH_FLOAT_FMT2;
	}
	else if(0.001 <= step && step < 0.01) {
		FMT = KNH_FLOAT_FMT3;
	}
	else if(0.0001 <= step && step < 0.001) {
		FMT = KNH_FLOAT_FMT4;
	}
	knh_write__ffmt(ctx, w, FMT, v);
	knh_bytes_t tag = knh_String_tobytes(DP(u)->tag);
	if(tag.len > 0) {
		knh_putc(ctx, w, '[');
		knh_write(ctx, w, tag);
		knh_putc(ctx, w, ']');
	}
}

/* ------------------------------------------------------------------------ */

static MAPPER knh_IntX_FloatX(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_float_t v = (knh_float_t)sfp[0].ivalue;
	KNH_MAPPED_Float(ctx, sfp, v);
}

/* ------------------------------------------------------------------------ */

static MAPPER knh_FloatX_IntX(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_int_t v = (knh_int_t)sfp[0].fvalue;
	KNH_MAPPED_Int(ctx, sfp, v);
}

/* ------------------------------------------------------------------------ */

static
int knh_ClassSpec_isVocab(ClassSpec *u)
{
	return IS_DictIdx(DP(u)->vocabDictIdx);
}

/* ------------------------------------------------------------------------ */

static
String *knh_ClassSpec_getVocabAt(Ctx *ctx, ClassSpec *u, size_t n)
{
	return knh_DictIdx_get__fast(DP(u)->vocabDictIdx, n - DP(u)->imin);
}

/* ------------------------------------------------------------------------ */

static
knh_int_t knh_ClassSpec_getVocabIdx(Ctx *ctx, ClassSpec *u, String *s)
{
	return knh_DictIdx_index(ctx, DP(u)->vocabDictIdx, knh_String_tobytes(s)) + DP(u)->imin;
}

/* ------------------------------------------------------------------------ */

static MAPPER knh_IntX_Vocab(Ctx *ctx, knh_sfp_t *sfp)
{
	ClassSpec *u = (ClassSpec*)sfp[1].o;
	KNH_ASSERT(IS_ClassSpec(u));
	KNH_MAPPED(ctx, sfp, knh_ClassSpec_getVocabAt(ctx, u, sfp[0].ivalue));
}

/* ------------------------------------------------------------------------ */

static MAPPER knh_Vocab_IntX(Ctx *ctx, knh_sfp_t *sfp)
{
	ClassSpec *u = (ClassSpec*)sfp[1].o;
	KNH_ASSERT(IS_ClassSpec(u));
	KNH_MAPPED_Int(ctx, sfp, knh_ClassSpec_getVocabIdx(ctx, u, sfp[0].s));
}

/* ------------------------------------------------------------------------ */

void knh_ClassSpec_reuse(Ctx *ctx, ClassSpec *u, knh_class_t cid)
{
	knh_class_t bcid = ctx->share->ClassTable[cid].bcid;
	if(bcid == CLASS_Int) {
		knh_int_t v = 0;
		if(!DP(u)->fichk(u, v)) {
			v = DP(u)->imin;
		}
		KNH_ASSERT(DP(u)->ivalue == NULL);
		KNH_INITv(DP(u)->ivalue, new_IntX__fast(ctx, cid, v));
		if(DP(u)->fvalue != NULL) {
			Mapper *mpr = new_Mapper(ctx, KNH_FLAG_MMF_AFFINE, DP(u)->ucid, cid, knh_FloatX_IntX, (Object*)u);
			konoha_addMapper(ctx, mpr);
			mpr = new_Mapper(ctx, KNH_FLAG_MMF_AFFINE, cid, DP(u)->ucid, knh_IntX_FloatX, (Object*)u);
			konoha_addMapper(ctx, mpr);
		}
		if(DP(u)->svalue != NULL) {
			if(knh_ClassSpec_isVocab(u)) {
				Mapper *mpr = new_Mapper(ctx, KNH_FLAG_MMF_AFFINE, cid, DP(u)->ucid, knh_IntX_Vocab, (Object*)u);
				konoha_addMapper(ctx, mpr);
				mpr = new_Mapper(ctx, KNH_FLAG_MMF_AFFINE, DP(u)->ucid, cid, knh_Vocab_IntX, (Object*)u);
				konoha_addMapper(ctx, mpr);
			}
		}
	}
	else if(bcid == CLASS_Float) {
		knh_float_t v = 0;
		if(!DP(u)->ffchk(u, v)) {
			v = DP(u)->fmin;
		}
		KNH_ASSERT(DP(u)->fvalue == NULL);
		KNH_INITv(DP(u)->fvalue, new_FloatX__fast(ctx, cid, v));
		if(DP(u)->ivalue != NULL) {
			Mapper *mpr = new_Mapper(ctx, KNH_FLAG_MMF_AFFINE, cid, DP(u)->ucid, knh_FloatX_IntX, (Object*)u);
			konoha_addMapper(ctx, mpr);
			mpr = new_Mapper(ctx, KNH_FLAG_MMF_AFFINE, DP(u)->ucid, cid, knh_IntX_FloatX, (Object*)u);
			konoha_addMapper(ctx, mpr);
		}
	}
	else {
		KNH_ASSERT(bcid == CLASS_String);

	}
}

/* ------------------------------------------------------------------------ */

KNHAPI(ClassSpec*) new_Enum(Ctx *ctx, char *tag, knh_int_t min, knh_int_t max)
{
	knh_class_t cid = knh_ClassTable_newId(ctx);
	ClassSpec* u = (ClassSpec*)new_Object_bcid(ctx, CLASS_ClassSpec, (int)cid);
	if(tag != NULL || tag[0] != 0) {
		KNH_SETv(ctx, DP(u)->urn, new_String__T(ctx, tag));
	}
	knh_ClassSpec_initIntRange(ctx, u, min, max);
	return u;
}

/* ------------------------------------------------------------------------ */

KNHAPI(ClassSpec*) new_Unit(Ctx *ctx, char *tag, knh_float_t min, knh_float_t max, knh_float_t step)
{
	knh_class_t cid = knh_ClassTable_newId(ctx);
	ClassSpec* u = (ClassSpec*)new_Object_bcid(ctx, CLASS_ClassSpec, (int)cid);
	if(tag != NULL || tag[0] != 0) {
		KNH_SETv(ctx, DP(u)->urn, new_String__T(ctx, tag));
	}
	knh_ClassSpec_initFloatRange(ctx, u, min, max, step);
	return u;
}

/* ======================================================================== */
/* [String] */

static
String *new_StringX__FormatException(Ctx *ctx, knh_class_t cid, knh_bytes_t t, String *orign)
{
	TODO();
//	Bytes *ba = knh_Context_openBConvBuf(ctx);
//	knh_Bytes_write(ctx, ba, STEXT("Format!!: "));
//	knh_Bytes_write(ctx, ba, B(CLASSN(cid)));
//	knh_Bytes_write(ctx, ba, STEXT("('"));
//	knh_Bytes_write(ctx, ba, t);
//	knh_Bytes_write(ctx, ba, STEXT(")'"));
//	{
//		String *s = (String*)new_Nue__b(ctx, knh_Bytes_tobytes(ba));
//		knh_Bytes_clear(ba, 0);
//		return s;
//	}
	return TS_EMPTY;
}

/* ------------------------------------------------------------------------ */

static
String *knh_fsnew__dict(Ctx *ctx, knh_class_t cid, knh_bytes_t t, String *orign)
{
	ClassSpec *u = (ClassSpec*)ctx->share->ClassTable[cid].cspec;
	KNH_ASSERT(IS_ClassSpec(u));
	knh_index_t n = knh_DictIdx_index(ctx, DP(u)->vocabDictIdx, t);
	if(n == -1) return new_StringX__FormatException(ctx, cid, t, orign);
	return knh_DictIdx_get__fast(DP(u)->vocabDictIdx, n);
}

/* ------------------------------------------------------------------------ */

static
int knh_fscmp__dict(ClassSpec *o, knh_bytes_t v1, knh_bytes_t v2)
{
	return knh_DictIdx_index(NULL, DP(o)->vocabDictIdx, v1) - knh_DictIdx_index(NULL, DP(o)->vocabDictIdx, v2);
}

/* ------------------------------------------------------------------------ */

static
DictIdx* new_DictIdx__Array(Ctx *ctx, Array *a)
{
	knh_DictIdx_t *o = (knh_DictIdx_t*)new_hObject(ctx, FLAG_DictIdx, CLASS_DictIdx, CLASS_DictIdx);
	KNH_INITv(o->terms, a);
	KNH_INITv(o->termsDictSet, new_DictSet(ctx, knh_Array_size(a)));
	o->offset = 0;
	{
		knh_uintptr_t i = 0;
		for(i = 0; i < knh_Array_size(a); i++) {
			String *s = (String*)knh_Array_n(a, i);
			knh_DictSet_append(ctx, o->termsDictSet, s, i);
		}
	}
	knh_DictSet_toIgnoreCase(o->termsDictSet);
	return o;
}

/* ------------------------------------------------------------------------ */

KNHAPI(ClassSpec*) new_Vocabulary(Ctx *ctx, char *tag, int base, char *terms, ...)
{
	knh_class_t cid = knh_ClassTable_newId(ctx);
	ClassSpec* u = (ClassSpec*)new_Object_bcid(ctx, CLASS_ClassSpec, (int)cid);
	if(tag != NULL || tag[0] != 0) {
		KNH_SETv(ctx, DP(u)->urn, new_String__T(ctx, tag));
	}

	DP(u)->fsnew = knh_fsnew__dict;
	DP(u)->fscmp = knh_fscmp__dict;
	{
		va_list args;
		va_start(args , terms);
		Array *a = new_Array0(ctx, 0);
		char *vocab = NULL;
		while((vocab = va_arg(args, char*)) != NULL) {
			String *s = new_String__T(ctx, vocab);
			knh_Array_add(ctx, a, UP(s));
			s->h.cid = cid;
		}
		va_end(args);
		KNH_SETv(ctx, DP(u)->vocabDictIdx, new_DictIdx__Array(ctx, a));
		knh_ClassSpec_initIntRange(ctx, u, base, base + knh_Array_size(a) - 1);
		KNH_ASSERT(knh_Array_size(a) > 0);
		KNH_INITv(DP(u)->svalue, knh_Array_n(a, 0));
	}
	return u;
}

///* ------------------------------------------------------------------------ */
//
//static
//MAPPER knh_Mapper__fdict(Ctx *ctx, knh_sfp_t *sfp)
//{
//	String *s = sfp[0].s;
//	ClassSpec *u = (ClassSpec*)ctx->share->ClassTable[knh_Object_cid(sfp[0].o)].cspec;
//	KNH_ASSERT(IS_ClassSpec(u));
//	KNH_ASSERT(IS_DictIdx(DP(u)->vocabDictIdx));
//
//	ClassSpec *u2 = (ClassSpec*)ctx->share->ClassTable[DP(sfp[1].mpr)->tcid].cspec;
//	KNH_ASSERT(IS_ClassSpec(u2));
//	KNH_ASSERT(IS_DictIdx(DP(u2)->vocabDictIdx));
//
//	size_t n = (size_t)knh_DictIdx_index(ctx, DP(u)->vocabDictIdx, knh_String_tobytes(s));
//	KNH_ASSERT(n < knh_DictIdx_size(DP(u2)->vocabDictIdx));
//	KNH_MAPPED(ctx, sfp, knh_DictIdx_get__fast(DP(u2)->vocabDictIdx, n));
//}
//
///* ------------------------------------------------------------------------ */
//
//KNHAPI(void) konoha_addVocabularyMapper(Ctx *ctx, knh_class_t scid, char *text)
//{
//	KNH_ASSERT_cid(scid);
//	knh_class_t tcid = konoha_findcid(ctx, B(text));
//
//	if(tcid != CLASS_unknown || ctx->share->ClassTable[tcid].bcid != tcid) {
////		ClassSpec *u = (ClassSpec*)ctx->share->ClassTable[scid].cspec;
////		if(!IS_ClassSpec(u) || !IS_DictIdx(DP(u)->vocabDictIdx)) {
////			TODO();
////			return;
////		}
//		ClassSpec *u2 = (ClassSpec*)ctx->share->ClassTable[tcid].cspec;
//		if(!IS_ClassSpec(u2) || !IS_DictIdx(DP(u2)->vocabDictIdx)) {
//			TODO();
//			return;
//		}
////		if(knh_DictIdx_size(DP(u)->vocabDictIdx) != knh_DictIdx_size(DP(u2)->vocabDictIdx)) {
////			TODO();
////			return;
////		}
//		Mapper *mpr = new_Mapper(ctx, KNH_FLAG_MMF_AFFINE, scid, tcid,
//				knh_Mapper_fvocab, (Object*)KNH_NULL);
//		if(ctx->share->ClassTable[scid].cmap == NULL) {
//			knh_ClassTable_t *TC = (knh_ClassTable_t*)(&ctx->share->ClassTable[scid]);
//			KNH_INITv(TC->cmap, new_ClassMap0(ctx, 4));
//		}
//		knh_ClassMap_add(ctx, ctx->share->ClassTable[scid].cmap, mpr);
//
//		mpr = new_Mapper(ctx, KNH_FLAG_MMF_AFFINE, tcid, scid,
//				knh_Mapper_fvocab, (Object*)KNH_NULL);
//		if(ctx->share->ClassTable[tcid].cmap == NULL) {
//			knh_ClassTable_t *TC = (knh_ClassTable_t*)(&ctx->share->ClassTable[tcid]);
//			KNH_INITv(TC->cmap, new_ClassMap0(ctx, 4));
//		}
//		knh_ClassMap_add(ctx, ctx->share->ClassTable[tcid].cmap, mpr);
//	}
//}

/* ======================================================================== */
/* [urnalias] */

knh_bytes_t konoha_getAliasURN(Ctx *ctx, knh_bytes_t aurn)
{
	String *s = (String*)knh_DictMap_get__b(ctx,  DP(ctx->sys)->URNAliasDictMap, aurn);
	if(IS_NOTNULL(s)) {
		return knh_String_tobytes(s);
	}
	return aurn;
}

///* ------------------------------------------------------------------------ */
//
//void konoha_setAliasURN(Ctx *ctx, String *alias, String *urn)
//{
//	if(knh_Context_isVerbose(ctx)) {
//		String *s =(String*)knh_DictMap_get__b(ctx,  DP(ctx->sys)->URNAliasDictMap, knh_String_tobytes(urn));
//		if(IS_NOTNULL(s)) {
//			KNH_WARNING(ctx, "Overriding %s %s", knh_String_tochar(alias), knh_String_tochar(s));
//		}
//	}
//	knh_DictMap_set(ctx, DP(ctx->sys)->URNAliasDictMap, alias, UP(urn));
//}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_loadURNAlias(Ctx *ctx, knh_StringConstData_t *data)
{
	DictMap *map = DP(ctx->sys)->URNAliasDictMap;
	knh_StringConstData_t *d = data;
	while(d->name != NULL) {
		String *s =(String*)knh_DictMap_get__b(ctx,  map, B(d->name));
		if(IS_NOTNULL(s)) {
			KNH_WARNING(ctx, _("Overriding %s %s"), data->value, knh_String_tochar(s));
		}
		d++;
	}
	d = data;
	while(d->name != NULL) {
		String *n = new_String__T(ctx, d->name);
		knh_DictMap_append(ctx, map, n, UP(new_String__T(ctx, d->value)));
		d++;
	}
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_loadClassSpecFunc(Ctx *ctx, knh_NamedPointerData_t *data)
{
	DictSet *ds = DP(ctx->sys)->SpecFuncDictSet;
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	while(data->name != NULL) {
		DBG2_P("adding.. '%s'", data->name);
		String *n = new_String__T(ctx, data->name);
		knh_DictSet_set(ctx, ds, n, (knh_uintptr_t)data->ptr);
		data++;
	}
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
}

/* ------------------------------------------------------------------------ */

static
ClassSpec *new_ClassSpecNULL(Ctx *ctx, knh_bytes_t urn)
{
	DBG2_P("finding.. '%s'", urn.buf);
	ClassSpec *u = (ClassSpec*)(KNH_NULL);
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	knh_index_t loc = 0;
	while(loc != -1) {
		knh_fspec func = (knh_fspec)knh_DictSet_get__b(DP(ctx->sys)->SpecFuncDictSet, urn);
		if(func != NULL) {
			u = func(ctx, urn);
			break;
		}
		loc = knh_bytes_rindex(urn, '/');
		if(loc != -1) {
			urn = knh_bytes_first(urn, loc);
		}
	}
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	return u;
}

/* ======================================================================== */
/* [SPEC] */

static
Object *knh_ClassTable_fdefault__ISPEC(Ctx *ctx, knh_class_t cid)
{
	ClassSpec *u = (ClassSpec*)ctx->share->ClassTable[cid].cspec;
	KNH_ASSERT(IS_ClassSpec(u));
	return UP(DP(u)->ivalue);
}

/* ------------------------------------------------------------------------ */

static
Object *knh_ClassTable_fdefault__FSPEC(Ctx *ctx, knh_class_t cid)
{
	ClassSpec *u = (ClassSpec*)ctx->share->ClassTable[cid].cspec;
	KNH_ASSERT(IS_ClassSpec(u));
	return UP(DP(u)->fvalue);
}

/* ------------------------------------------------------------------------ */

static
Object *knh_ClassTable_fdefault__SSPEC(Ctx *ctx, knh_class_t cid)
{
	ClassSpec *u = (ClassSpec*)ctx->share->ClassTable[cid].cspec;
	KNH_ASSERT(IS_ClassSpec(u));
	return UP(DP(u)->svalue);
}

/* ------------------------------------------------------------------------ */

static
knh_class_t konoha_addSpecializedType(Ctx *ctx, knh_class_t cid, knh_class_t bcid, ClassSpec *u)
{
	if(cid == CLASS_newid) {
		cid = knh_ClassTable_newId(ctx);
	}else {
		KNH_ASSERT(cid + 1 == ctx->share->ClassTableSize);
		ctx->share->ClassTableSize = cid;
	}

	char bufcn[CLASSNAME_BUFSIZ];
	knh_snprintf(bufcn, sizeof(bufcn), KNH_CLASSSPEC_FMT, CLASSN(bcid), knh_String_tochar(DP(u)->urn));
	konoha_setClassName(ctx, cid, new_String(ctx, B(bufcn), NULL));

	ctx->share->ClassTable[cid].bcid   = bcid;
	ctx->share->ClassTable[cid].supcid = bcid;

//	if(bcid == CLASS_Int) bcid = CLASS_IntX;
//	else if(bcid == CLASS_Float) bcid = CLASS_FloatX;
//	else if(bcid == CLASS_String) bcid = CLASS_StringX;

	DBG2_P("%s\n\tcopying from %s", bufcn, CLASSN(bcid));
	ctx->share->ClassTable[cid].cflag  = ctx->share->ClassTable[bcid].cflag;
	ctx->share->ClassTable[cid].oflag  = ctx->share->ClassTable[bcid].oflag;
	ctx->share->ClassTable[cid].offset = ctx->share->ClassTable[bcid].offset;

	ctx->share->ClassTable[cid].sid  = ctx->share->ClassTable[bcid].sid;
	ctx->share->ClassTable[cid].size = ctx->share->ClassTable[bcid].size;
	ctx->share->ClassTable[cid].bsize  = ctx->share->ClassTable[bcid].bsize;

	KNH_ASSERT(ctx->share->ClassTable[cid].cstruct == NULL);
	KNH_INITv(ctx->share->ClassTable[cid].cstruct, ctx->share->ClassTable[bcid].cstruct);

	if(ctx->share->ClassTable[cid].cmap == NULL) {
		KNH_INITv(ctx->share->ClassTable[cid].cmap, new_ClassMap0(ctx, 4));
	}
	else {
		KNH_ASSERT(IS_ClassMap(ctx->share->ClassTable[cid].cmap));
	}

	KNH_ASSERT(ctx->share->ClassTable[cid].cspec == NULL);
	KNH_INITv(ctx->share->ClassTable[cid].cspec, u);

	if(DP(u)->ucid != cid) {
		knh_ClassSpec_reuse(ctx, u, cid);
	}
	if(bcid == CLASS_Int) {
		KNH_ASSERT(DP(u)->ivalue != NULL);
		ctx->share->ClassTable[cid].fdefault = knh_ClassTable_fdefault__ISPEC;
	}
	else if(bcid == CLASS_Float) {
		KNH_ASSERT(DP(u)->fvalue != NULL);
		ctx->share->ClassTable[cid].fdefault = knh_ClassTable_fdefault__FSPEC;
	}
	else {
		KNH_ASSERT(DP(u)->svalue != NULL);
		ctx->share->ClassTable[cid].fdefault = knh_ClassTable_fdefault__SSPEC;
	}
	return cid;
}

/* ------------------------------------------------------------------------ */

static
ClassSpec* konoha_findClassSpecNULL(Ctx *ctx, knh_bytes_t lname)
{
	knh_index_t loc = knh_bytes_index(lname, '{');
	if(loc != -1) {
		char *postfix = (char*)lname.buf + loc;
		char cname[CLASSNAME_BUFSIZ];
		knh_snprintf(cname, sizeof(cname), "Int%s", postfix);
		knh_class_t cid = konoha_getcid(ctx, B(cname));
		if(cid != CLASS_unknown) {
			return (ClassSpec*)ctx->share->ClassTable[cid].cspec;
		}
		knh_snprintf(cname, sizeof(cname), "Float%s", postfix);
		cid = konoha_getcid(ctx, B(cname));
		if(cid != CLASS_unknown) {
			return (ClassSpec*)ctx->share->ClassTable[cid].cspec;
		}
		knh_snprintf(cname, sizeof(cname), "String%s", postfix);
		cid = konoha_getcid(ctx, B(cname));
		if(cid != CLASS_unknown) {
			return (ClassSpec*)ctx->share->ClassTable[cid].cspec;
		}
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

knh_class_t konoha_findcidx(Ctx *ctx, knh_bytes_t lname)
{
	ClassSpec *u = 	konoha_findClassSpecNULL(ctx, lname);
	if(u != NULL) {
		knh_index_t loc = knh_bytes_index(lname, '{');
		knh_class_t bcid = konoha_getcid(ctx, knh_bytes_first(lname, loc));
		return konoha_addSpecializedType(ctx, CLASS_newid, bcid, u);
	}
	else {
		knh_index_t loc = knh_bytes_index(lname, '{');
		knh_bytes_t urn = knh_bytes_last(lname, loc+1); urn.len -= 1;
		knh_class_t bcid = konoha_getcid(ctx, knh_bytes_first(lname, loc));
		DBG2_P("cid=%d,%s", bcid, CLASSN(bcid));
		u = new_ClassSpecNULL(ctx, urn);
		if(u != NULL) {
			knh_class_t ucid = DP(u)->ucid;
			knh_class_t ubcid = ctx->share->ClassTable[ucid].bcid;
			DBG2_P("cid=%d,%s", ubcid, CLASSN(ubcid));
			konoha_addSpecializedType(ctx, ucid, ubcid, u);
			if(ubcid != bcid) {
				return konoha_addSpecializedType(ctx, CLASS_newid, bcid, u);
			}
			return ucid;
		}
		return bcid;
	}
}

/* ------------------------------------------------------------------------ */



#ifdef __cplusplus
}
#endif