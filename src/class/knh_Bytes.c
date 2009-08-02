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

#define _knh_Bytes_size(o)      (o)->size
#define _knh_Bytes_value(o)     (o)->buf
#define _knh_Bytes_last(o)      ((o)->buf + (o)->size)

/* ======================================================================== */
/* [barray] */


size_t knh_bytes_newsize(size_t s)
{
	if(s <= KONOHA_SMALLPAGESIZE) return KONOHA_SMALLPAGESIZE;
	if(s <= KONOHA_PAGESIZE) {
		if(s <= 1024) return 1024;
		return KONOHA_PAGESIZE;
	}
	if((s % KONOHA_PAGESIZE) == 0) return s;
	return ((s / KONOHA_PAGESIZE)+1) * KONOHA_PAGESIZE;
}

/* ------------------------------------------------------------------------ */

static
void knh_Bytes_expands(Ctx *ctx, knh_Bytes_t *o, size_t newsize)
{
	if(o->capacity == 0) {
		newsize = knh_bytes_newsize(newsize);
		o->buf = (knh_uchar_t*)KNH_MALLOC(ctx, newsize);
		o->capacity = newsize;
	}
	else {
		knh_uchar_t *newa = (knh_uchar_t*)KNH_MALLOC(ctx, newsize);
		knh_memcpy(newa, o->buf, o->capacity);
		knh_bzero(&newa[o->capacity], newsize - o->capacity);
		KNH_FREE(ctx, o->buf, o->capacity);
		o->buf = newa;
		o->capacity = newsize;
	}
}

/* ======================================================================== */
/* [constructors] */

KNHAPI(Bytes*) new_Bytes(Ctx *ctx, size_t capacity)
{
	return (Bytes*)new_Object_bcid(ctx, CLASS_Bytes, capacity);
}

/* ======================================================================== */
/* [methods] */

KNHAPI(knh_bytes_t) knh_Bytes_tobytes(Bytes *o)
{
	knh_bytes_t v = {o->buf, o->size};
	return v;
}

#define _knh_Bytes_tochar(b)  (char*)knh_Bytes_value(b)

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_Bytes_clear(Bytes *o, size_t pos)
{
	if(pos < o->size) {
		knh_bzero(o->buf + pos, o->size - pos);
		o->size = pos;
	}
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_Bytes_ensureSize(Ctx *ctx, Bytes *o, size_t len)
{
	if(o->capacity < len) {
		knh_Bytes_expands(ctx, o, len);
	}
	o->size = len;
}

/* ------------------------------------------------------------------------ */

void knh_Bytes_ensureZero(Ctx *ctx, Bytes *o)
{
	if(o->size == o->capacity) {
		knh_Bytes_expands(ctx, o, o->capacity * 2);
	}
	if(o->buf[o->size] != 0) {
		o->buf[o->size] = 0;
	}
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_Bytes_putc(Ctx *ctx, Bytes *o, int ch)
{
	if(o->size == o->capacity) {
		knh_Bytes_expands(ctx, o, o->capacity * 2);
	}
	o->buf[o->size] = ch;
	o->size += 1;
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_Bytes_write(Ctx *ctx, Bytes *o, knh_bytes_t v)
{
	if(v.len == 0) return ;
	if(o->size + v.len >= o->capacity) {
		size_t newsize = o->capacity * 2;
		if(newsize < o->size + v.len) newsize = knh_bytes_newsize(o->size + v.len);
		knh_Bytes_expands(ctx, o, newsize);
	}
	knh_memcpy(&o->buf[o->size], v.buf, v.len);
	o->size += v.len;
}

/* ------------------------------------------------------------------------ */

void knh_Bytes_remove(Ctx *ctx, Bytes *o, size_t offset, size_t len)
{
	KNH_ASSERT(offset + len < o->size);
	memmove(o->buf + offset + len, o->buf + offset, len);
	knh_bzero(o->buf + (o->size - len), len);
	o->size = o->size - len;
}

/* ------------------------------------------------------------------------ */

void knh_Bytes_unputc(Bytes *o)
{
	if(o->size > 0) {
		o->size -= 1;
		o->buf[o->size] = '\0';
	}
}

/* ------------------------------------------------------------------------ */

void knh_Bytes_update(Ctx *ctx, Bytes *o, size_t pos, knh_bytes_t t)
{
	if(pos + t.len + 1 > o->size) {
		if(o->size < o->capacity && o->buf[o->size] != 0) {
			DBG2_P("extending buffer %p", o->buf);
			knh_Bytes_clear(o, pos);
			knh_Bytes_write(ctx, o, t);
			return;
		}
		DBG2_P("buffer overflow %p", o->buf);
		KNH_ABORT();
	}
	else {
		DBG2_P("rewrite buffer %p", o->buf);
		knh_memcpy(&o->buf[pos], t.buf, t.len);
		knh_bzero(&(o->buf[pos+t.len]), o->size - pos - t.len);
	}
}

/* ======================================================================== */
/* [cwb] */

knh_cwb_t *knh_cwb_open(Ctx* ctx, knh_cwb_t *cwb)
{
	cwb->ba = ((Context*)ctx)->bufa;
	cwb->w  = ((Context*)ctx)->bufw;
	cwb->pos = knh_Bytes_size(((Context*)ctx)->bufa);
	return cwb;
}

/* ------------------------------------------------------------------------ */

knh_cwb_t *knh_cwb_openinit(Ctx* ctx, knh_cwb_t *cwb, knh_bytes_t t)
{
	cwb->ba = ctx->bufa;
	cwb->w  = ctx->bufw;
	cwb->pos = knh_Bytes_size(ctx->bufa);
	KNH_ASSERT(!(cwb->ba->buf <= t.buf && t.buf < (cwb->ba->buf + cwb->pos)));
	knh_Bytes_write(ctx, (cwb->ba), t);
	return cwb;
}

/* ------------------------------------------------------------------------ */

void knh_cwb_putc(Ctx *ctx, knh_cwb_t *cwb, int ch)
{
	knh_Bytes_putc(ctx, (cwb->ba), ch);
}

/* ------------------------------------------------------------------------ */

void knh_cwb_write(Ctx *ctx, knh_cwb_t *cwb, knh_bytes_t t)
{
	KNH_ASSERT(!(cwb->ba->buf <= t.buf && t.buf < (cwb->ba->buf + cwb->pos)));
	knh_Bytes_write(ctx, (cwb->ba), t);
}

/* ------------------------------------------------------------------------ */

size_t knh_cwb_size(knh_cwb_t *cwb)
{
	return (cwb->ba)->size - cwb->pos;
}

/* ------------------------------------------------------------------------ */

knh_bytes_t knh_cwb_tobytes(knh_cwb_t *cwb)
{
	knh_bytes_t t = {(cwb->ba)->buf + cwb->pos, (cwb->ba)->size - cwb->pos};
	return t;
}

/* ------------------------------------------------------------------------ */

char *knh_cwb_tochar(Ctx *ctx, knh_cwb_t *cwb)
{
	knh_bytes_t t = {(cwb->ba)->buf + cwb->pos, (cwb->ba)->size - cwb->pos};
	knh_Bytes_ensureZero(ctx, cwb->ba);
	return (char*)t.buf;
}

/* ------------------------------------------------------------------------ */

void knh_cwb_close(knh_cwb_t *cwb)
{
	knh_Bytes_clear(cwb->ba, cwb->pos);
}

/* ------------------------------------------------------------------------ */

void knh_cwb_subclear(knh_cwb_t *cwb, size_t len)
{
	knh_Bytes_clear(cwb->ba, cwb->pos + len);
}

/* ------------------------------------------------------------------------ */
/* [String] */

String *new_String__cwb(Ctx *ctx, knh_cwb_t *cwb)
{
	if(cwb->pos == (cwb->ba)->size) {
		return TS_EMPTY;
	}
	else {
		knh_bytes_t t = knh_cwb_tobytes(cwb);
		String *s = new_String(ctx, t, NULL);
		knh_cwb_close(cwb);
		return s;
	}
}

/* ------------------------------------------------------------------------ */

String *new_StringX__cwb(Ctx *ctx, knh_class_t cid, knh_cwb_t *cwb)
{
	knh_bytes_t t = knh_cwb_tobytes(cwb);
	String *s = new_StringX(ctx, cid, t, NULL);
	knh_cwb_close(cwb);
	return s;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
