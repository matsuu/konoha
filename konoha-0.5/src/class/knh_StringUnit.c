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
/* [macro] */

//static
//int knh_fvcabcmp__default(StringUnit *b, knh_bytes_t v1, knh_bytes_t v2);

/* ======================================================================== */
/* [structs] */


/* ======================================================================== */
/* [constructors] */

StringUnit *new_StringUnit(Ctx *ctx, knh_flag_t flag, knh_class_t cid, String *tag)
{
	StringUnit* o = (StringUnit*)new_Object_bcid(ctx, CLASS_StringUnit, 0);
	DP(o)->spec.flag = flag;
	DP(o)->spec.cid  = cid;
	KNH_SETv(ctx, DP(o)->spec.tag, tag);
	return o;
}


/* ======================================================================== */
/* [methods] */
//
//size_t knh_fvcabbconv__toupper(Ctx *ctx, BytesConv *o, knh_bytes_t t, Bytes *ba)
//{
//	size_t i;
//	for(i = 0; i < t.len; i++) {
//		knh_Bytes_putc(ctx, ba, toupper(t.buf[i]));
//	}
//	return i;
//}
//
///* ------------------------------------------------------------------------ */
//
//size_t knh_fvcabbconv__tolower(Ctx *ctx, BytesConv *o, knh_bytes_t t, Bytes *ba)
//{
//	size_t i;
//	for(i = 0; i < t.len; i++) {
//		knh_Bytes_putc(ctx, ba, tolower(t.buf[i]));
//	}
//	return i;
//}


/* ======================================================================== */
/* [Dict] */

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
String *knh_fvcabnew__dict(Ctx *ctx, knh_class_t cid, knh_bytes_t t, String *orign)
{
	StringUnit *u = (StringUnit*)ctx->share->ClassTable[cid].cspec;
	KNH_ASSERT(IS_StringUnit(u));
	knh_index_t n = knh_DictIdx_index(ctx, DP(u)->vocabDictIdx, t);
	if(n == -1) return new_StringX__FormatException(ctx, cid, t, orign);
	return knh_DictIdx_get__fast(DP(u)->vocabDictIdx, n);
}

/* ------------------------------------------------------------------------ */

static
int knh_fvcabcmp__dict(StringUnit *o, knh_bytes_t v1, knh_bytes_t v2)
{
	return knh_DictIdx_index(NULL, DP(o)->vocabDictIdx, v1) - knh_DictIdx_index(NULL, DP(o)->vocabDictIdx, v2);
}

///* ------------------------------------------------------------------------ */
//
//static
//void knh_StringUnit_initDict2(Ctx *ctx, StringUnit *o, ObjectNULL *dict, f_bconv fbconv, f_sunit_new fnew, f_sunit_cmp fcmp)
//{
//	DP(o)->fbconv = fbconv;
//	DP(o)->fnew = (fnew == NULL) ? knh_fvcabnew__dict : fnew;
//	DP(o)->fcmp = (fcmp == NULL) ? knh_fvcabcmp__dict : fcmp;
//
//	if(dict == NULL || IS_NULL(dict)) {
//		KNH_SETv(ctx, DP(o)->vocabDictIdx, new_DictIdx(ctx, 12, 0));
//	}
//	else if(IS_DictIdx(dict)) {
//		KNH_SETv(ctx, DP(o)->vocabDictIdx, dict);
//	}
//	else {
//		TODO();
//		KNH_SETv(ctx, DP(o)->vocabDictIdx, new_DictIdx(ctx, 12, 0));
//	}
//}

/* ------------------------------------------------------------------------ */

KNHAPI(ClassSpec*) new_Vocabulary(Ctx *ctx, char *lang, char *defval, ...)
{
	knh_class_t cid = knh_ClassTable_newId(ctx);
	StringUnit* o = new_StringUnit(ctx, 0, cid, TS_EMPTY);

	DP(o)->fbconv = NULL;
	DP(o)->fnew = knh_fvcabnew__dict;
	DP(o)->fcmp = knh_fvcabcmp__dict;
	KNH_SETv(ctx, DP(o)->vocabDictIdx, new_DictIdx0(ctx, 16, 0));

	char *vocab = NULL;
	va_list args;

	va_start(args , defval);
	while((vocab = va_arg(args, char*)) != NULL) {
		String *s = new_String__T(ctx, vocab);
		knh_DictIdx_add__fast(ctx, DP(o)->vocabDictIdx, s);
		if(knh_String_equals(s, B(defval))) {
			KNH_SETv(ctx, DP(o)->spec.defvalue, s);
		}
		s->h.cid = cid;
	}
	va_end(args);

	return (ClassSpec*)o;
}

/* ------------------------------------------------------------------------ */

static
MAPPER knh_Mapper_fvocab(Ctx *ctx, knh_sfp_t *sfp)
{
	String *s = sfp[0].s;
	StringUnit *u = (StringUnit*)ctx->share->ClassTable[knh_Object_cid(sfp[0].o)].cspec;
	KNH_ASSERT(IS_StringUnit(u));
	KNH_ASSERT(IS_DictIdx(DP(u)->vocabDictIdx));

	StringUnit *u2 = (StringUnit*)ctx->share->ClassTable[DP(sfp[1].mpr)->tcid].cspec;
	KNH_ASSERT(IS_StringUnit(u2));
	KNH_ASSERT(IS_DictIdx(DP(u2)->vocabDictIdx));

	size_t n = (size_t)knh_DictIdx_index(ctx, DP(u)->vocabDictIdx, knh_String_tobytes(s));
	KNH_ASSERT(n < knh_DictIdx_size(DP(u2)->vocabDictIdx));
	KNH_MAPPED(ctx, sfp, knh_DictIdx_get__fast(DP(u2)->vocabDictIdx, n));
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_addVocabularyMapper(Ctx *ctx, knh_class_t scid, char *text)
{
	KNH_ASSERT_cid(scid);
	knh_class_t tcid = konoha_findcid(ctx, B(text));

	if(tcid != CLASS_unknown || ctx->share->ClassTable[tcid].bcid != tcid) {
//		StringUnit *u = (StringUnit*)ctx->share->ClassTable[scid].cspec;
//		if(!IS_StringUnit(u) || !IS_DictIdx(DP(u)->vocabDictIdx)) {
//			TODO();
//			return;
//		}
		StringUnit *u2 = (StringUnit*)ctx->share->ClassTable[tcid].cspec;
		if(!IS_StringUnit(u2) || !IS_DictIdx(DP(u2)->vocabDictIdx)) {
			TODO();
			return;
		}
//		if(knh_DictIdx_size(DP(u)->vocabDictIdx) != knh_DictIdx_size(DP(u2)->vocabDictIdx)) {
//			TODO();
//			return;
//		}
		Mapper *mpr = new_Mapper(ctx, KNH_FLAG_MMF_AFFINE, scid, tcid,
				knh_Mapper_fvocab, (Object*)KNH_NULL);
		if(ctx->share->ClassTable[scid].cmap == NULL) {
			knh_ClassTable_t *TC = (knh_ClassTable_t*)(&ctx->share->ClassTable[scid]);
			KNH_INITv(TC->cmap, new_ClassMap0(ctx, 4));
		}
		knh_ClassMap_add(ctx, ctx->share->ClassTable[scid].cmap, mpr);

		mpr = new_Mapper(ctx, KNH_FLAG_MMF_AFFINE, tcid, scid,
				knh_Mapper_fvocab, (Object*)KNH_NULL);
		if(ctx->share->ClassTable[tcid].cmap == NULL) {
			knh_ClassTable_t *TC = (knh_ClassTable_t*)(&ctx->share->ClassTable[tcid]);
			KNH_INITv(TC->cmap, new_ClassMap0(ctx, 4));
		}
		knh_ClassMap_add(ctx, ctx->share->ClassTable[tcid].cmap, mpr);
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
