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

#ifdef KONOHA_ON_WINDOWS
#pragma comment(lib, "iconv.lib")
#endif

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [fbconv] */

size_t knh_BytesConv_conv(Ctx *ctx, BytesConv *o, knh_bytes_t t, knh_Bytes_t *ba)
{
	return o->fbconv(ctx, o, t, ba);
}


///* ------------------------------------------------------------------------ */
//
//BytesConv* new_BytesConv(Ctx *ctx, knh_fbyteconv fbconv)
//{
//	knh_BytesConv_t *o = (BytesConv*)new_Object_bcid(ctx, CLASS_BytesConv, 0);
//	DP(o)->fbconv = (fbconv == NULL) ? knh_fbyteconv_nop : fbconv;
//	return o;
//}

/* ------------------------------------------------------------------------ */

static
size_t knh_fbyteconv_noconv(Ctx *ctx, BytesConv *bc, knh_bytes_t t, knh_Bytes_t *ba)
{
	knh_Bytes_write(ctx, ba, t);
	return t.len;
}

/* ------------------------------------------------------------------------ */
/* [iconv] */

iconv_t knh_iconv_open(Ctx *ctx, char *to, char *from)
{
#if defined(KNH_USING_ICONV)
	return iconv_open(to, from);
#else
	return ((iconv_t)-1);
#endif
}

/* ------------------------------------------------------------------------ */

void knh_iconv_close(Ctx *ctx, iconv_t cd)
{
#if defined(KNH_USING_ICONV)
	iconv_close(cd);
#endif
}

/* ------------------------------------------------------------------------ */

static
size_t knh_fbyteconv_iconv(Ctx *ctx, BytesConv *bc, knh_bytes_t t, knh_Bytes_t *ba)
{
#if defined(KNH_USING_ICONV)
	char buffer[4096], *ibuf = (char*)t.buf;
	size_t ilen = t.len, rsize = 0, ilen_prev = ilen;
	iconv_t cd = bc->iconv_d;
	KNH_ASSERT(cd != (iconv_t)-1);

	while(ilen > 0) {
		char *obuf = buffer;
		size_t olen = sizeof(buffer);
//		DBG2_P("S in=%p,%d out=%p,%d", ibuf, ilen, obuf, olen);
#if defined(KONOHA_ON_MACOSX)
		size_t rc = iconv(cd, &ibuf, &ilen, &obuf, &olen);
#else
		size_t rc = iconv(cd, &ibuf, &ilen, &obuf, &olen);
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
	knh_Bytes_write(ctx, ba, t);
	return t.len;
#endif
}

/* ------------------------------------------------------------------------ */

static
void knh_fbyteconvfree_iconv(Ctx *ctx, BytesConv *bc)
{
	if(bc->iconv_d != (iconv_t)-1) {
		knh_iconv_close(ctx, bc->iconv_d);
	}
}

/* ------------------------------------------------------------------------ */

BytesConv* new_BytesConv__iconv(Ctx *ctx, char *from, char *to)
{
	iconv_t cd = knh_iconv_open(ctx, to, from);
	if(cd == (iconv_t)-1) {
		KNH_WARNING(ctx, _("unsupported iconv(from=%s, to=%s)"), from, to);
	}

	BytesConv* o = (BytesConv*)new_Object_bcid(ctx, CLASS_BytesConv, 0);
	if(cd != (iconv_t)-1) {
		o->iconv_d = cd;
		o->fbconv = knh_fbyteconv_iconv;
		o->fbconvfree = knh_fbyteconvfree_iconv;
	}
	else {
		o->fbconv = knh_fbyteconv_noconv;
	}
	return o;
}

/* ------------------------------------------------------------------------ */

BytesConv* new_BytesConv__in(Ctx *ctx, char *from)
{
	return new_BytesConv__iconv(ctx, from, KONOHA_ENCODING);
}

/* ------------------------------------------------------------------------ */

BytesConv* new_BytesConv__out(Ctx *ctx, char *to)
{
	return new_BytesConv__iconv(ctx, KONOHA_ENCODING, to);
}


/* ======================================================================== */
/* [bconvbuf] */

static Bytes *knh_Context_openBConvBuf(Ctx* ctx)
{
	KNH_ASSERT(knh_Bytes_size(ctx->bconvbuf) == 0);
	return ctx->bconvbuf;
}

/* ------------------------------------------------------------------------ */

static void knh_Context_closeBConvBuf(Ctx* ctx, Bytes *ba)
{
	KNH_ASSERT(ba == ctx->bconvbuf);
	knh_Bytes_clear(ba, 0);
}

/* ======================================================================== */
/* [String] */

String *new_String__bconv(Ctx *ctx, knh_bytes_t t, BytesConv *bc)
{
	KNH_ASSERT(IS_BytesConv(bc));
	if(t.len == 0) return TS_EMPTY;
	Bytes *ba = knh_Context_openBConvBuf(ctx);
	String *s;
	bc->fbconv(ctx, bc, t, ba);
	s = new_String(ctx, knh_Bytes_tobytes(ba), NULL);
	knh_Context_closeBConvBuf(ctx, ba);
	return s;
}

/* ------------------------------------------------------------------------ */

String *new_String__cwbconv(Ctx *ctx, knh_cwb_t *cwb, BytesConv *bc)
{
	if(knh_cwb_size(cwb) == 0) {
		return TS_EMPTY;
	}
	else if(IS_NULL(bc)) {
		String *s = new_String(ctx, knh_cwb_tobytes(cwb), NULL);
		knh_cwb_close(cwb);
		return s;
	}else {
		Bytes *ba = knh_Context_openBConvBuf(ctx);
		bc->fbconv(ctx, bc, knh_cwb_tobytes(cwb), ba);
		String *s = new_String(ctx, knh_Bytes_tobytes(ba), NULL);
		knh_Context_closeBConvBuf(ctx, ba);
		knh_cwb_close(cwb);
		return s;
	}
}

/* ------------------------------------------------------------------------ */

KNHAPI(String*) new_String__fbcnv(Ctx *ctx, String *s, knh_fbyteconv fbcnv, BytesConv *bc)
{
	knh_bytes_t base = knh_String_tobytes(s);
	Bytes *ba = knh_Context_openBConvBuf(ctx);
	fbcnv(ctx, bc, base, ba);
	if(knh_strncmp((char*)(base.buf), (char*)(ba->buf), base.len) != 0) {
		s = new_String(ctx, knh_Bytes_tobytes(ba), NULL);
	}
	knh_Context_closeBConvBuf(ctx, ba);
	return s;
}


/* ------------------------------------------------------------------------ */

void knh_OutputStream_write__bconv(Ctx *ctx, OutputStream *w, knh_bytes_t t)
{
	Bytes *ba = knh_Context_openBConvBuf(ctx);
	knh_BytesConv_conv(ctx, DP(w)->bconv, t, ba);
	knh_OutputStream_write(ctx, w, knh_Bytes_tobytes(ba));
	knh_Context_closeBConvBuf(ctx, ba);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
