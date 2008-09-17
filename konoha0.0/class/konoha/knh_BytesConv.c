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

static
size_t f_bconv__NOP(Ctx *ctx, BytesConv *b, knh_bytes_t t, knh_Bytes_t *ba);

static
size_t f_bconv__iconv(Ctx *ctx, BytesConv *o, knh_bytes_t t, knh_Bytes_t *ba);

/* ======================================================================== */
/* [structs] */

void
knh_BytesConv_struct_init(Ctx *ctx, knh_BytesConv_struct *b, int init, Object *cs)
{
	KNH_INITv(b->name, TS_EMPTY);
	b->fbconv = f_bconv__NOP;
#ifdef KNH_USING_ICONV
	b->iconv_d = ((iconv_t)-1);
#endif
}

/* ------------------------------------------------------------------------ */

#define _knh_BytesConv_struct_copy NULL

/* ------------------------------------------------------------------------ */

#define _knh_BytesConv_struct_compare NULL

/* ------------------------------------------------------------------------ */

void
knh_BytesConv_struct_traverse(Ctx *ctx, knh_BytesConv_struct *b, f_traverse ftr)
{
	if(ftr == NULL || IS_SWEEP(ftr)) {
#ifdef KNH_USING_ICONV
		if(b->fbconv == f_bconv__iconv) {
			iconv_close(b->iconv_d);
			b->fbconv = f_bconv__NOP;
		}
#endif
	}
	ftr(ctx, UP(b->name));
}

/* ======================================================================== */
/* [fbconv] */

size_t knh_BytesConv_conv(Ctx *ctx, BytesConv *o, knh_bytes_t t, knh_Bytes_t *ba)
{
	return DP(o)->fbconv(ctx, o, t, ba);
}

/* ------------------------------------------------------------------------ */

static
size_t f_bconv__NOP(Ctx *ctx, BytesConv *b, knh_bytes_t t, knh_Bytes_t *ba)
{
	knh_Bytes_write(ctx, ba, t);
	return t.len;
}

/* ------------------------------------------------------------------------ */

BytesConv* new_BytesConv(Ctx *ctx, String *name, f_bconv fbconv)
{
	BytesConv *o = (BytesConv*)new_Object_malloc(ctx, FLAG_BytesConv, CLASS_BytesConv, sizeof(knh_BytesConv_struct));
	knh_BytesConv_struct_init(ctx, DP(o), 0, NULL);
	KNH_SETv(ctx, DP(o)->name, name);
	DP(o)->fbconv = (fbconv == NULL) ? f_bconv__NOP : fbconv;
	return o;
}

/* ------------------------------------------------------------------------ */
/* [iconv] */

static
size_t f_bconv__iconv(Ctx *ctx, BytesConv *o, knh_bytes_t t, knh_Bytes_t *ba)
{
#if defined(KNH_USING_ICONV)
	char buffer[4096], *ibuf = (char*)t.buf;
	size_t ilen = t.len, rsize = 0, ilen_prev = ilen;
	iconv_t cd = DP(o)->iconv_d;
	KNH_ASSERT(cd != (iconv_t)-1);

	while(ilen > 0) {
		char *obuf = buffer;
		size_t olen = sizeof(buffer);
//		DBG2_P("S in=%p,%d out=%p,%d", ibuf, ilen, obuf, olen);
#if defined(KONOHA_OS__MACOSX)
		size_t rc = iconv(cd, &ibuf, &ilen, &obuf, &olen);
#else
		size_t rc = iconv(cd, (const char**)&ibuf, &ilen, &obuf, &olen);
#endif
		//		DBG2_P("E in=%p,%d out=%p,%d", ibuf, ilen, obuf, olen);
		olen = sizeof(buffer) - olen;
//		DBG2_P("E2 in=%p,%d out=%p,%d", ibuf, ilen, obuf, olen);
		if(rc == (size_t)-1) {
			KNH_WARNING(ctx, "iconv: misplaced..");
			return rsize;
 		}
 		rsize += olen;
 		knh_Bytes_write(ctx, ba, B2(buffer, olen));
 		if(ilen == ilen_prev) {
 			DBG2_P("infinite loop!!: ilen = %d", (int)ilen); return rsize;
 		}
 		ilen_prev = ilen;
	}
	return rsize;
#else
	return 0;
#endif
}

/* ------------------------------------------------------------------------ */

BytesConv* new_BytesConv__iconv(Ctx *ctx, char *from, char *to)
{
#ifdef KNH_USING_ICONV
	iconv_t cd = iconv_open(to, from);
	if(cd == (iconv_t)-1) {
		return (BytesConv*)KNH_NULL;
	}
	else {
		BytesConv* o = (BytesConv*)new_Object_malloc(ctx, FLAG_BytesConv, CLASS_BytesConv, sizeof(knh_BytesConv_struct));
		char buf[FILENAME_BUFSIZ];
		knh_snprintf(buf, sizeof(buf), "iconv:%s=>%s", from, to);
		knh_BytesConv_struct_init(ctx, DP(o), 0, NULL);
		KNH_SETv(ctx, DP(o)->name, new_String0(ctx, B(buf), NULL));
		DP(o)->iconv_d = cd;
		DP(o)->fbconv = f_bconv__iconv;
		return o;
	}
#else
	DBG2_P("uninstalled iconv!!");
	return (BytesConv*)KNH_NULL;
#endif
}

/* ------------------------------------------------------------------------ */

BytesConv* new_BytesConv__in(Ctx *ctx, char *from)
{
#ifdef KNH_USING_ICONV
	return new_BytesConv__iconv(ctx, from, KONOHA_ENCODING);
#else
	return KNH_NULL;
#endif
}

/* ------------------------------------------------------------------------ */

BytesConv* new_BytesConv__out(Ctx *ctx, char *to)
{
#ifdef KNH_USING_ICONV
	return new_BytesConv__iconv(ctx, KONOHA_ENCODING, to);
#else
	return KNH_NULL;
#endif
}

/* ======================================================================== */
/* [String] */

String *new_String__bconv(Ctx *ctx, knh_bytes_t t, BytesConv *bconv)
{
	KNH_ASSERT(IS_BytesConv(bconv));
	Bytes *ba = knh_Context_openBConvBuf(ctx);
	String *s;
	DP(bconv)->fbconv(ctx, bconv, t, ba);
	s = new_String(ctx, knh_Bytes_tobytes(ba), NULL);
	knh_Context_closeBConvBuf(ctx, ba);
	return s;
}

/* ------------------------------------------------------------------------ */

String *new_String__wbufconv(Ctx *ctx, knh_wbuf_t cb, BytesConv *bconv)
{
	if(cb.pos == cb.ba->size) {
		return TS_EMPTY;
	}
	else {
		if(IS_NULL(bconv)) {
			String *s = new_String(ctx, knh_Bytes_lastbyte(cb.ba, cb.pos), NULL);
			knh_Bytes_subclear(cb.ba, cb.pos);
			return s;
		}else {
			Bytes *ba = knh_Context_openBConvBuf(ctx);
			String *s;
			DP(bconv)->fbconv(ctx, bconv, knh_Bytes_lastbyte(cb.ba, cb.pos), ba);
			s = new_String(ctx, knh_Bytes_tobytes(ba), NULL);
			knh_Bytes_subclear(cb.ba, cb.pos);
			knh_Context_closeBConvBuf(ctx, ba);
			return s;
		}
	}
}

/* ======================================================================== */
/* [movabletext] */

/* @method void BytesConv.%k(OutputStream w, Any m) */

void knh_BytesConv__k(Ctx *ctx, BytesConv *o, OutputStream *w, Any *m)
{
	knh_write(ctx, w, knh_String_tobytes(DP(o)->name));
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
