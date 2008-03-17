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

void
knh_Vocabulary_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	Vocabulary *b =  (Vocabulary*)s1;
	b->spec.flag = 0;
	b->spec.cid  = CLASS_Float;
	KNH_INITv(b->spec.urn,  knh_String_EMPTY());
	KNH_INITv(b->spec.tag,  knh_String_EMPTY());
	KNH_INITv(b->spec.defvalue, knh_String_EMPTY());
	//
	b->fnmz = NULL;
	b->fval = knh_Vocabulary_fval__default;
	b->fcmp = knh_Vocabulary_fcmp__default;
	b->charlen = 0;
	b->bytelen = 0;
	KNH_INITv(b->pattern, KNH_NULL);
	KNH_INITv(b->vocabDictIdx, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

#define _knh_Vocabulary_struct_copy   NULL

/* ------------------------------------------------------------------------ */

#define _knh_Vocabulary_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void
knh_Vocabulary_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Vocabulary *b = (Vocabulary*)s;
	gc(ctx, b->spec.urn);
	gc(ctx, b->spec.tag);
	gc(ctx, b->spec.defvalue);

	gc(ctx, b->pattern);
	gc(ctx, b->vocabDictIdx);
}

/* ======================================================================== */
/* [constructors] */

Vocabulary *new_Vocabulary__STEXT(Ctx *ctx, knh_flag_t flag, knh_class_t cid, char *urn, char *tag, ...)
{
	Vocabulary* b = (Vocabulary*)knh_Object_malloc0(ctx, KNH_FLAG_Vocabulary, CLASS_Vocabulary, sizeof(Vocabulary));
	knh_Vocabulary_struct_init(ctx, (Struct*)b, 0, NULL);

	b->spec.flag = flag;
	b->spec.cid  = cid;
	if(urn != NULL) {
		KNH_SETv(ctx, b->spec.urn,  new_String__fast(ctx, CLASS_String__urn, B(urn)));
	}
	if(tag != NULL) {
		KNH_SETv(ctx, b->spec.tag,  new_String__fast(ctx, CLASS_String, B(tag)));
	}
	
	char *vocab = NULL;
	va_list args; 

	va_start(args , tag);
	if((vocab = va_arg(args, char*)) != NULL) {
		knh_Vocabulary_initDict(ctx, b, NULL, NULL, NULL, NULL);
		knh_Vocabulary_addDict__STEXT(ctx, b, vocab);
		while((vocab = va_arg(args, char*)) != NULL) {
			knh_Vocabulary_addDict__STEXT(ctx, b, vocab);
		}
	}
	va_end(args);
	return b;
}

/* ======================================================================== */
/* [tclass] */


Vocabulary* knh_tclass_getVocabulary(Ctx *ctx, knh_class_t cid)
{
	KNH_ASSERT(IS_Vocabulary(knh_tclass_spec(cid)));
	return (Vocabulary*)knh_tclass_spec(cid);
}

/* ------------------------------------------------------------------------ */

Vocabulary *knh_String_spec(Ctx *ctx)
{
	return new_Vocabulary__STEXT(ctx, 0, CLASS_String, NULL, NULL, NULL);
}


/* ------------------------------------------------------------------------ */

knh_class_t
KNH_TVOCAB(Ctx *ctx, char *urn, char *tag, ...)
{
	knh_class_t cid = knh_tclass_newId(ctx);

	Vocabulary* b = (Vocabulary*)knh_Object_malloc0(ctx, KNH_FLAG_Vocabulary, CLASS_Vocabulary, sizeof(Vocabulary));
	knh_Vocabulary_struct_init(ctx, (Struct*)b, 0, NULL);

	b->spec.flag = 0;
	b->spec.cid  = cid;
	DEBUG_ASSERT(urn != NULL);
	KNH_SETv(ctx, b->spec.urn,  new_String__fast(ctx, CLASS_String__urn, B(urn)));
	DEBUG_ASSERT(tag != NULL);
	
	char *vocab = NULL;
	va_list args; 

	va_start(args , tag);
	if((vocab = va_arg(args, char*)) != NULL) {
		knh_Vocabulary_initDict(ctx, b, NULL, NULL, NULL, NULL);
		knh_Vocabulary_addDict__STEXT(ctx, b, vocab);
		while((vocab = va_arg(args, char*)) != NULL) {
			knh_Vocabulary_addDict__STEXT(ctx, b, vocab);
		}
	}
	va_end(args);
	
	KNH_TCLASS_SPEC(ctx, CLASS_String, b);
	return cid;
}

/* ======================================================================== */
/* [methods] */

knh_bool_t knh_Vocabulary_fnmz__toupper(Ctx *ctx, knh_bytes_t t, Bytes *ba)
{
	size_t i;
	for(i = 0; i < t.len; i++) {
		knh_Bytes_putc(ctx, ba, toupper(t.buf[i]));
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_Vocabulary_fnmz__tolower(Ctx *ctx, knh_bytes_t t, Bytes *ba)
{
	size_t i;
	for(i = 0; i < t.len; i++) {
		knh_Bytes_putc(ctx, ba, toupper(t.buf[i]));
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

String *knh_Vocabulary_newString(Ctx *ctx, Vocabulary *b, knh_bytes_t t, void *orig, size_t off, size_t len)
{
	if(orig == NULL) {
		return new_String__fast(ctx, b->spec.cid, t);
	}
	DEBUG_ASSERT(knh_Object_topsid(orig) == STRUCT_String);
	return new_String__subfast(ctx, b->spec.cid, (String*)orig, off, len);
}

#define _knh_Vocabulary_fval__default knh_Vocabulary_newString

/* ------------------------------------------------------------------------ */

String *new_Nue__asIllegalString(Ctx *ctx, Vocabulary *b, knh_bytes_t t)
{
	knh_buffer_t ctxbuf = knh_Context_buffer(ctx);
	knh_write__s(ctx, ctxbuf.w, "Type!!: '");
	knh_write(ctx, ctxbuf.w, t);
	knh_write__s(ctx, ctxbuf.w, "' is not in ");
	knh_write__s(ctx, ctxbuf.w, CLASSN(b->spec.cid));
	String *s = new_String__fast(ctx, CLASS_String, knh_buffer_tobytes(ctxbuf));
	knh_buffer_clear(ctxbuf);
	return (String*)new_Nue(ctx, s); 
}

/* ------------------------------------------------------------------------ */

String *knh_Vocabulary_value(Ctx *ctx, Vocabulary *b, knh_bytes_t t, void *orig, size_t off, size_t len)
{
	if(b->fnmz != NULL) {
		knh_buffer_t ctxbuf = knh_Context_buffer(ctx);
		knh_bool_t isgo = b->fnmz(ctx, t, ctxbuf.ba);
		String *s;
		if(!isgo) {
			s = new_Nue__asIllegalString(ctx, b, t);
		}
		else {
			s = b->fval(ctx, b, knh_buffer_tobytes(ctxbuf), NULL, 0, 0);
		}
		knh_buffer_clear(ctxbuf);
		return s;
	}
	return b->fval(ctx, b, t, orig, off, len);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Vocabulary_fcmp__default(Vocabulary *b, knh_bytes_t v1, knh_bytes_t v2)
{
	return knh_bytes_strcmp(v1, v2);
}

/* ------------------------------------------------------------------------ */

INLINE
knh_int_t knh_Vocabulary_compare(Vocabulary *b, knh_bytes_t v1, knh_bytes_t v2)
{
	return b->fcmp(b, v1, v2);
}

/* ======================================================================== */
/* [Dict] */

void knh_Vocabulary_initDict(Ctx *ctx, Vocabulary *b, ObjectNULL *dict, f_vocab_nmz fnmz, f_vocab_val fval, f_vocab_cmp fcmp)
{

	b->fnmz = fnmz;
	b->fval = (fval == NULL) ? knh_Vocabulary_fval__dict : fval;
	b->fcmp = (fcmp == NULL) ? knh_Vocabulary_fcmp__dict : fcmp;
	
	if(dict == NULL || IS_NULL(dict)) {
		KNH_SETv(ctx, b->vocabDictIdx, new_DictIdx(ctx, 12, 0));
	}
	else if(IS_DictIdx(dict)) {
		KNH_SETv(ctx, b->vocabDictIdx, dict);
	}
	else {
		TODO();
		KNH_SETv(ctx, b->vocabDictIdx, new_DictIdx(ctx, 12, 0));
	}
}

/* ------------------------------------------------------------------------ */

String* knh_Vocabulary_fval__dict(Ctx *ctx, Vocabulary *b, knh_bytes_t t, void *orig, size_t off, size_t len)
{
	knh_index_t n = knh_DictIdx_index(ctx, b->vocabDictIdx, t);
	if(n != -1) return  new_Nue__asIllegalString(ctx, b, t);
	return knh_DictIdx_get__fast(b->vocabDictIdx, n);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Vocabulary_fcmp__dict(Vocabulary *b, knh_bytes_t v1, knh_bytes_t v2)
{
	return knh_DictIdx_index(NULL, b->vocabDictIdx, v1) - knh_DictIdx_index(NULL, b->vocabDictIdx, v2);
}

/* ------------------------------------------------------------------------ */

void knh_Vocabulary_addDict__STEXT(Ctx *ctx, Vocabulary *b, char *vocab)
{
	DEBUG_ASSERT(vocab != NULL);
	knh_DictIdx_add__fast(ctx, b->vocabDictIdx, new_String__STEXT(ctx, b->spec.cid, vocab));
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
