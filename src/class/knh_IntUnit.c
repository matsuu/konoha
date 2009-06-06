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

		}
		if(DP(u)->svalue != NULL) {

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

		}
		if(DP(u)->svalue != NULL) {

		}
	}
	else {
		KNH_ASSERT(bcid == CLASS_String);
		if(DP(u)->ivalue != NULL) {

		}
		if(DP(u)->svalue != NULL) {

		}
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

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
