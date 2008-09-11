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

//#define _new_String__STEXT(ctx,cid,s)   new_StringX0(ctx, cid, s)

#define _knh_String_value(o)   ((o)->str)
#define _knh_String_tochar(o)  (char*)((o)->str)
#define _knh_String_strlen(o)  (o)->size

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

String *new_String(Ctx *ctx, knh_bytes_t t, String *orign)
{
	knh_String_t *o = (String*)new_PObject__NNctx(ctx, FLAG_String, CLASS_String, CLASS_String);
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

String *new_String0(Ctx *ctx, knh_bytes_t t, String *orign)
{
	knh_String_t *o = (String*)new_PObject0(ctx, FLAG_String, CLASS_String, CLASS_String);
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

String *new_StringX__fast(Ctx *ctx, knh_class_t cid, knh_bytes_t t, String *orign)
{
	knh_String_t *o = (String*)new_PObject0(ctx, FLAG_String, CLASS_String, cid);
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

String *new_StringX__FormatException(Ctx *ctx, knh_class_t cid, knh_bytes_t t, String *orign)
{
	Bytes *ba = knh_Context_openBConvBuf(ctx);
	knh_Bytes_write(ctx, ba, STEXT("Format!!: "));
	knh_Bytes_write(ctx, ba, B(CLASSN(cid)));
	knh_Bytes_write(ctx, ba, STEXT("('"));
	knh_Bytes_write(ctx, ba, t);
	knh_Bytes_write(ctx, ba, STEXT(")'"));
	{
		String *s = (String*)new_Nue__b(ctx, knh_Bytes_tobytes(ba));
		knh_Bytes_clear(ba);
		return s;
	}
}

/* ------------------------------------------------------------------------ */

String *new_StringX(Ctx *ctx, knh_class_t cid, knh_bytes_t t, String *orign)
{
	DEBUG_ASSERT_cid(cid);
	{
		StringUnit *u = (StringUnit*)knh_tClass[cid].cspec;
		KNH_ASSERT(IS_StringUnit(u));
		if(DP(u)->fbconv != NULL) {
			Bytes *ba = knh_Context_openBConvBuf(ctx);
			size_t n = DP(u)->fbconv(ctx, DP(u)->bconv, t, ba);
			if(n == ((size_t)-1)) {
				knh_Bytes_clear(ba);
				return new_StringX__FormatException(ctx, cid, t, orign);
			}
			else {
				knh_bytes_t newt = knh_Bytes_tobytes(ba);
				if(knh_bytes_strcmp(t, newt) != 0) {
					String *s = DP(u)->fnew(ctx, cid, newt, NULL);
					knh_Bytes_clear(ba);
					return s;
				}
			}
		}
		return DP(u)->fnew(ctx, cid, t, orign);
	}
}

/* ------------------------------------------------------------------------ */

Object *knh_String_fdefault(Ctx *ctx, knh_class_t cid)
{
	return (Object*)TS_EMPTY;
}

/* ======================================================================== */
/* [commons] */

knh_hcode_t knh_String_hashCode(String *o)
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

int knh_String_compareTo(String *o, String *o2)
{
	if(o->h.cid == CLASS_String || o2->h.cid == CLASS_String) {
		size_t i, max = knh_uint_min(o->size, o2->size);
		for(i = 0; i < max; i++) {
			int res = o->str[i] - o2->str[i];
			if(res != 0) return res;
		}
		return o->size - o2->size;
	}
	else {
		if(o->h.cid == o2->h.cid) {
			StringUnit *u = (StringUnit*)knh_tClass[o->h.cid].cspec;
			KNH_ASSERT(IS_StringUnit(u));
			return DP(u)->fcmp(u, knh_String_tobytes(o), knh_String_tobytes(o2));
		}
		return (int)(o - o2);
	}
}

/* ======================================================================== */
/* [misc] */

char *knh_StringNULL_tochar(String *o)
{
	if(IS_NULL(o)) {
		return "";
	}else {
		return (char*)o->str;
	}
}

/* ------------------------------------------------------------------------ */

knh_bytes_t knh_String_tobytes(String *o)
{
	knh_bytes_t bt = {o->str, o->size};
	return bt;
}

/* ------------------------------------------------------------------------ */

knh_bytes_t knh_StringNULL_tobytes(String *o)
{
	if(IS_NULL(o)) {
		knh_bytes_t bt = {(knh_uchar_t*)"", 0};
		return bt;
	}else {
		knh_bytes_t bt = {o->str, o->size};
		return bt;
	}
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
