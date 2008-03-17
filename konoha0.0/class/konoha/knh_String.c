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
/* [macros] */

#define _new_String(ctx,t)              new_String__fast(ctx,CLASS_String,B(t))
#define _new_String__STEXT(ctx,cid,s)   new_String__fast(ctx, cid, STEXT(s))

#define _knh_String_value(o)   (o)->value

/* ======================================================================== */
/* [structs] */

void
knh_String_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	String *b = (String*)s;
	b->value = (knh_uchar_t*)"";
	b->strlen = 0;
	b->hcode = 0;
	b->orig = NULL;
}

/* ------------------------------------------------------------------------ */

#define _knh_String_struct_copy  NULL

/* ------------------------------------------------------------------------ */

knh_int_t
knh_String_struct_compare(Ctx *ctx, Struct *s1, Struct *s2) 
{
	String *b =  (String*)s1;
	String *b2 = (String*)s2;

	knh_class_t cid = knh_struct_cid(s1);  /* use String as default */
	Vocabulary *spec = knh_tclass_getVocabulary(ctx, cid);
	return knh_Vocabulary_compare(spec, knh_String_tobytes(b), knh_String_tobytes(b2));
}

/* ------------------------------------------------------------------------ */

void
knh_String_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	String *b = (String*)s;
	if(IS_SWEEP(gc)) {
		if(b->orig == NULL) {
			knh_free(b->value, KNH_SIZE(b->strlen + 1));
		}
		else{
			gc(ctx, (Object*)b->orig);	
		}
	}
}

/* ======================================================================== */
/* [hcode] */

knh_hcode_t knh_string_hash(knh_uchar_t *buf, knh_size_t len)
{
	knh_hcode_t h = len;
	knh_int_t i; 
	for(i = 0; i < len; i++) {
		h = buf[i] + 31 * h;
	}
	return h;
}

#define _knh_bytes_hcode(t)     knh_string_hash((t).buf, (t).len)

/* ======================================================================== */
/* [constructors] */


String *new_String__fast(Ctx *ctx, knh_class_t cid, knh_bytes_t t)
{
	String *b = (String*)knh_Object_malloc0(ctx, KNH_FLAG_String, cid, sizeof(String));
	b->strlen = t.len;
	b->value = (knh_uchar_t*)knh_malloc(ctx, KNH_SIZE(b->strlen+1));
	knh_memcpy(b->value, t.buf, t.len); b->value[b->strlen] = '\0';
	b->hcode = knh_string_hash(b->value, b->strlen);
	b->orig = NULL;
	return b;
}

/* ------------------------------------------------------------------------ */

INLINE
String *new_String__subfast(Ctx *ctx, knh_class_t cid, String *sub, knh_size_t offset, knh_size_t len)
{
	String *b = (String*)knh_Object_malloc0(ctx, KNH_FLAG_String, cid, sizeof(String));
	b->value = sub->value + offset;
	b->strlen = len;
	b->hcode = knh_string_hash(b->value, b->strlen);
	KNH_INITv(b->orig, sub);
	return b;
}

/* ------------------------------------------------------------------------ */

INLINE
String *new_String__checked(Ctx *ctx, knh_class_t cid, knh_bytes_t value)
{
	return knh_Vocabulary_value(ctx, knh_tclass_getVocabulary(ctx, cid), value, NULL, 0, 0);
}

/* ------------------------------------------------------------------------ */

INLINE
String *new_String__sub(Ctx *ctx, knh_class_t cid, String *sub, knh_size_t offset, knh_size_t len)
{
	return knh_Vocabulary_value(ctx, knh_tclass_getVocabulary(ctx, cid), knh_String_tobytes(sub), sub, offset, len);
}

/* ======================================================================== */
/* [methods] */

INLINE
knh_hcode_t knh_String_hcode(String *b) 
{
	return b->hcode;
}

/* ------------------------------------------------------------------------ */

INLINE 
char *knh_String_tochar(String *b)
{
	return (char*)b->value;
}

/* ------------------------------------------------------------------------ */

char *knh_StringNULL_tochar(String *b)
{
	if(IS_NULL(b)) {
		return "";
	}else {
		return (char*)b->value;
	}
}

/* ------------------------------------------------------------------------ */

knh_bytes_t knh_String_tobytes(String *b)
{
	knh_bytes_t bt = {b->value, b->strlen};
	return bt;
}

/* ------------------------------------------------------------------------ */

knh_bytes_t knh_StringNULL_tobytes(String *b)
{
	if(IS_NULL(b)) {
		knh_bytes_t bt = {(knh_uchar_t*)"", 0};
		return bt;
	}else {
		knh_bytes_t bt = {b->value, b->strlen};
		return bt;
	}
}

/* ======================================================================== */
/* [method] */

/* @method Bool! String.equals(String! s) */

INLINE
knh_bool_t knh_String_equals(String *b, knh_bytes_t s)
{
	return (b->strlen == s.len && knh_strncmp((char*)b->value, (char*)s.buf, s.len) == 0);
}

/* ------------------------------------------------------------------------ */

/* @method Bool! String.startsWith(String! s) */

INLINE
knh_bool_t knh_String_startsWith(String *b, knh_bytes_t s)
{
	return knh_bytes_startsWith(knh_String_tobytes(b), s);
}

/* ------------------------------------------------------------------------ */
/* @method Bool! String.endsWith(String! s) */

INLINE
knh_bool_t knh_String_endsWith(String *b, knh_bytes_t s)
{
	return knh_bytes_endsWith(knh_String_tobytes(b), s);
}

/* ------------------------------------------------------------------------ */
/* @method Int! String.getSize() */

INLINE
size_t knh_String_getSize(String *b)
{
	return knh_string_size(knh_String_tobytes(b));
}

/* ======================================================================== */
/* [operators] */

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* @method[STATIC] String! String.opMul(Int! n) */

String* knh_String_opMul(Ctx *ctx, String *b, knh_int_t n)
{
	if(n <= 0) {
		return knh_String_EMPTY();
	}else if(n == 1) {
		return b;
	}
	
	String *s = (String*)knh_Object_malloc0(ctx, KNH_FLAG_String, CLASS_String, sizeof(String));
	s->strlen = b->strlen * n;
	s->value = (knh_uchar_t*)knh_malloc(ctx, KNH_SIZE(s->strlen+1));
	
	knh_int_t i;
	for(i = 0; i < n; i++) {
		knh_memcpy(s->value + (b->strlen*i), b->value, b->strlen); 
	}
	s->value[s->strlen] = '\0';
	s->hcode = knh_string_hash(s->value, s->strlen);
	s->orig = NULL;
	return s;
}

/* ======================================================================== */
/* [movabletext] */

/* @method void String.%s(OutputStream w, Any m) */

INLINE
void knh_String__s(Ctx *ctx, String *b, OutputStream *w, Any *m)
{
	knh_write(ctx, w, knh_String_tobytes(b));
}

/* ------------------------------------------------------------------------ */

/* @method void String.%dump(OutputStream w, Any m) */

void knh_String__dump(Ctx *ctx, String *b, OutputStream *w, Any *m)
{
	int_byte_t quote = '\'';
	if(knh_Object_cid(b) == CLASS_String) quote = '"';
	knh_putc(ctx, w, quote);
	char *p = knh_String_tochar(b);
	knh_int_t i;
	for(i = 0; i < b->strlen; i++) {
		switch(p[i]) {
			case '\t' :
				knh_putc(ctx, w, '\\'); knh_putc(ctx, w, 't'); break ;
			case '\n' :
				knh_putc(ctx, w, '\\'); knh_putc(ctx, w, 'n'); break ;
			case '\r' :
				knh_putc(ctx, w, '\\'); knh_putc(ctx, w, 'r'); break ;
			case '\\' : case '\"' : case '\'' :
				knh_putc(ctx, w, '\\'); knh_putc(ctx, w, p[i]); break ;
			default :
				knh_putc(ctx, w, p[i]);
		}
	}
	knh_putc(ctx, w, quote);
}

/* ======================================================================== */
/* [global] */

static Object *knh_String_gEMPTY    = NULL;
static Object *knh_String_gNL       = NULL;
//static Object *knh_String_gSPC      = NULL;
static Object *knh_String_gTAB      = NULL;
//static Object *knh_String_gVOID     = NULL;
static Object *knh_String_gNULL     = NULL;
static Object *knh_String_gTRUE     = NULL;
static Object *knh_String_gFALSE    = NULL;

/* ------------------------------------------------------------------------ */


String *knh_String_EMPTY(void)
{
	if(knh_String_gEMPTY == NULL) {
		knh_String_gEMPTY = new_String__fast(CTX_NULL, CLASS_String, STEXT(""));
		KNH_TGLOBAL(knh_String_gEMPTY);
	}
	return (String*)knh_String_gEMPTY;
}

/* ------------------------------------------------------------------------ */


String *knh_String_NL(void)
{
	if(knh_String_gNL == NULL) {
		knh_String_gNL = new_String__fast(CTX_NULL, CLASS_String, STEXT(KONOHA_OS_LINEFEED));
		KNH_TGLOBAL(knh_String_gNL);
	}
	return (String*)knh_String_gNL;
}

/* ------------------------------------------------------------------------ */

String *knh_String_TAB(void)
{
	if(knh_String_gTAB == NULL) {
		knh_String_gTAB = new_String__fast(CTX_NULL, CLASS_String, STEXT("\t"));
		KNH_TGLOBAL(knh_String_gTAB);
	}
	return (String*)knh_String_gTAB;
}

///* ------------------------------------------------------------------------ */
//
//
//String *const_StringSPC(void)
//{
//	if(knh_String_gSPC == NULL) {
//		knh_String_gSPC = new_String__fast(CTX_NULL, CLASS_String, STEXT(" "));
//		KNH_TGLOBAL(knh_String_gSPC);
//	}
//	return knh_String_gSPC;
//}
//


///* ------------------------------------------------------------------------ */
//
//
//String *const_String_void(void)
//{
//	if(knh_String_gVOID == NULL) {
//		knh_String_gVOID = new_String__fast(CTX_NULL, CLASS_String, STEXT("void"));
//		KNH_TGLOBAL(knh_String_gVOID);
//	}
//	return knh_String_gVOID;
//}
//
//#define _VOID              const_String_void()
//
///* ------------------------------------------------------------------------ */
//
//INLINE
//knh_bool_t knh_Object_is_void(Object *b)
//{
//	return (knh_String_gVOID == b);
//}
//
//#define _IS_VOID(o)        knh_Object_is_void(o)

/* ------------------------------------------------------------------------ */

String *knh_String_NULL(void)
{
	if(knh_String_gNULL == NULL) {
		knh_String_gNULL = new_String__fast(CTX_NULL, CLASS_String, STEXT("null"));
		KNH_TGLOBAL(knh_String_gNULL);
	}
	return (String*)knh_String_gNULL;
}

/* ------------------------------------------------------------------------ */


String *knh_String_cTRUE(void)
{
	if(knh_String_gTRUE == NULL) {
		knh_String_gTRUE = new_String__fast(CTX_NULL, CLASS_String, STEXT("true"));
		KNH_TGLOBAL(knh_String_gTRUE);
	}
	return (String*)knh_String_gTRUE;
}

/* ------------------------------------------------------------------------ */

String *knh_String_cFALSE(void)
{
	if(knh_String_gFALSE == NULL) {
		knh_String_gFALSE = new_String__fast(CTX_NULL, CLASS_String, STEXT("false"));
		KNH_TGLOBAL(knh_String_gNULL);
	}
	return (String*)knh_String_gFALSE;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
