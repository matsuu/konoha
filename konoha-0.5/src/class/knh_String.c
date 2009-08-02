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
/* [macros] */

#define _knh_String_value(o)   ((o)->str)
#define _knh_String_tochar(o)  (char*)((o)->str)
#define _knh_String_strlen(o)  (o)->size

/* ======================================================================== */
/* [hcode] */

knh_hcode_t knh_uchar_hcode(knh_hcode_t h, knh_uchar_t *buf, size_t len)
{
	size_t i;
	for(i = 0; i < len; i++) {
		h = buf[i] + 31 * h;
	}
	return h;
}

/* ------------------------------------------------------------------------ */

void knh_String_checkASCII(String *o)
{
	knh_uchar_t *p = o->str;
	size_t i;
	for(i = 0; i < o->size; i++) {
		if(p[i] > 127) return;
	}
	knh_String_setASCII(o, 1);
}

/* ======================================================================== */
/* [constructors] */

KNHAPI(String*) new_String(Ctx *ctx, knh_bytes_t t, String *orign)
{
	knh_String_t *o = (String*)new_hObject(ctx, FLAG_String, CLASS_String, CLASS_String);
	if(orign == NULL) {
		o->size = t.len;
		o->str = (knh_uchar_t*)KNH_MALLOC(ctx, KNH_SIZE(o->size+1));
		knh_memcpy(o->str, t.buf, t.len);
		o->str[o->size] = '\0';
		o->orign = NULL;
		knh_String_checkASCII(o);
	}else {
		KNH_ASSERT(IS_bString(orign));
		o->size = t.len;
		o->str = (knh_uchar_t*)t.buf;
		if(orign->orign == NULL) {
			KNH_INITv(o->orign, orign);
		}
		else {
			KNH_ASSERT(IS_bString(orign->orign));
			KNH_INITv(o->orign, orign->orign);
		}
		if(knh_String_isASCII(orign)) {
			knh_String_setASCII(o, 1);
		}
		else {
			knh_String_checkASCII(o);
		}
	}
	return o;
}

/* ------------------------------------------------------------------------ */

knh_String_t *new_StringX__T(Ctx *ctx, knh_class_t cid, const char *text)
{
	knh_String_t *o = (knh_String_t*)new_hObject(ctx, FLAG_String, CLASS_String, cid);
	o->str = (knh_uchar_t*)text;
	o->size = knh_strlen(text);
	o->orign = NULL;
	knh_String_setTextSgm(o, 1);
	knh_String_checkASCII(o);
	return o;
}

/* ------------------------------------------------------------------------ */

String *new_StringX__fast(Ctx *ctx, knh_class_t cid, knh_bytes_t t, String *orign)
{
	knh_String_t *o = (String*)new_hObject(ctx, FLAG_String, CLASS_String, cid);
	if(orign == NULL) {
		o->size = t.len;
		o->str = (knh_uchar_t*)KNH_MALLOC(ctx, KNH_SIZE(o->size+1));
		knh_memcpy(o->str, t.buf, t.len);
		o->str[o->size] = '\0';
		o->orign = NULL;
	}
	else {
		KNH_ASSERT(IS_bString(orign));
		o->size = t.len;
		o->str = (knh_uchar_t*)t.buf;
		if(orign->orign == NULL) {
			KNH_INITv(o->orign, orign);
		}
		else {
			KNH_ASSERT(IS_bString(orign->orign));
			KNH_INITv(o->orign, orign->orign);
		}
	}
	knh_String_checkASCII(o);
	return o;
}


/* ------------------------------------------------------------------------ */

String *new_StringX(Ctx *ctx, knh_class_t cid, knh_bytes_t t, String *orign)
{
	if(cid == CLASS_String) {
		return new_String(ctx, t, orign);
	}
	else {
		KNH_ASSERT_cid(cid);
		TODO();
		return new_String(ctx, t, orign);
	}
//	ClassSpec *u = knh_getClassSpec(ctx, cid].cspec;
//	KNH_ASSERT(IS_ClassSpec(u));
//		if(DP(u)->fbconv != NULL) {
//		return new_String__fcnv(ctx, DP(u)->)
//		Bytes *ba = knh_Context_openBConvBuf(ctx);
//			size_t n = DP(u)->fbconv(ctx, DP(u)->bconv, t, ba);
//			if(n == ((size_t)-1)) {
//				knh_Bytes_clear(ba, 0);
//				return new_StringX__FormatException(ctx, cid, t, orign);
//			}
//			else {
//				knh_bytes_t newt = knh_Bytes_tobytes(ba);
//				if(knh_bytes_strcmp(t, newt) != 0) {
//					String *s = DP(u)->fnew(ctx, cid, newt, NULL);
//					knh_Bytes_clear(ba, 0);
//					return s;
//				}
//			}
//		}
//		return DP(u)->fnew(ctx, cid, t, orign);
//	}
}

/* ------------------------------------------------------------------------ */

String *new_String__int(Ctx *ctx, knh_int_t n)
{
	char buf[KNH_INTUNIT_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), KNH_INT_FMT, n);
	return new_String(ctx, B(buf), NULL);
}

/* ------------------------------------------------------------------------ */

String *new_String__float(Ctx *ctx, knh_float_t n)
{
	char buf[KNH_INTUNIT_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), KNH_FLOAT_FMT, n);
	return new_String(ctx, B(buf), NULL);
}


/* ======================================================================== */
/* [misc] */

KNHAPI(knh_bytes_t) knh_String_tobytes(String *o)
{
	knh_bytes_t bt = {o->str, o->size};
	return bt;
}


/* ======================================================================== */
/* [constructors] */

KNHAPI(char*) knh_String_text(Ctx *ctx, String *s)
{
	if(s->str[s->size] != '\0') {
		knh_uchar_t *newstr = (knh_uchar_t*)KNH_MALLOC(ctx, KNH_SIZE(s->size+1));
		knh_memcpy(newstr, s->str, s->size);
		newstr[s->size] = '\0';
		s->str = newstr;
		KNH_ASSERT(s->orign != NULL);
		KNH_FINALv(ctx, s->orign);
		s->orign = NULL;
	}
	return (char*)s->str;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_String_equals(String *o, knh_bytes_t s)
{
//	knh_bytes_t t = knh_String_tobytes(o);
	return (o->size == s.len && knh_strncmp((char*)o->str, (char*)s.buf, s.len) == 0);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_String_startsWith(String *b, knh_bytes_t s)
{
	return knh_bytes_startsWith(knh_String_tobytes(b), s);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_String_endsWith(String *b, knh_bytes_t s)
{
	return knh_bytes_endsWith(knh_String_tobytes(b), s);
}

/* ======================================================================== */
/* [StringParser] */

Object* new_String_parseOf(Ctx *ctx, String *p)
{
	return UP(p);
}

/* ------------------------------------------------------------------------ */

static knh_parser_drvapi_t PARSER__String = {
	KNH_DRVAPI_TYPE__PARSER, "_",
	TYPE_String,
	new_String_parseOf
};

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_addParserDriver(Ctx *ctx, char *alias, knh_parser_drvapi_t *d)
{
	if(alias != NULL) {
		knh_addDriverAPI(ctx, alias, (knh_drvapi_t*)d);
	}
	else {
		knh_addDriverAPI(ctx, d->name, (knh_drvapi_t*)d);
	}
}

/* ------------------------------------------------------------------------ */

static
knh_parser_drvapi_t *knh_System_getParserDriver(Ctx *ctx, knh_bytes_t name)
{
	knh_drvapi_t *d = knh_getDriverAPI(ctx, KNH_DRVAPI_TYPE__PARSER, name);
	if(d == NULL) {
		return &(PARSER__String);
	}
	KNH_ASSERT(d->type == KNH_DRVAPI_TYPE__PARSER);
	return (knh_parser_drvapi_t*)d;
}

/* ------------------------------------------------------------------------ */

int knh_bytes_splitTag(knh_bytes_t t, knh_bytes_t *tag, knh_bytes_t *body)
{
	size_t i;
	for(i = 1; i < t.len; i++) {
		if(t.buf[i] == ':' && t.buf[i-1] != '\\') {
			tag->buf = t.buf;
			tag->len = i;
			body->buf = t.buf + i + 1;
			body->len = t.len - (i+1);
			return 1;
		}
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

Object *new_Object_parseOf(Ctx *ctx, String *s)
{
	knh_bytes_t t = knh_String_tobytes(s);
	knh_index_t loc = knh_bytes_index(t, ':');
	if(loc <= 0) {
		return UP(s);
	}
	if(loc > 2 && t.buf[loc-2] == '!' && t.buf[loc-1] == '!') {
		return UP(new_Exception(ctx, s));
	}
	knh_class_t tagcid = knh_NameSpace_tagcid(ctx, ctx->share->mainns, CLASS_String, knh_bytes_first(t, loc));
	if(tagcid != CLASS_unknown) {
		DBG2_P("cid=%s", CLASSN(tagcid));

	}
	knh_parser_drvapi_t *d = knh_System_getParserDriver(ctx, knh_bytes_first(t, loc));
	return d->parser(ctx, s);
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
