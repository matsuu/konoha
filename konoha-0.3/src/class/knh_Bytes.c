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

knh_bytes_t knh_BytesNULL_tobytes(Bytes *o)
{
	if(IS_NULL(o)) {
		knh_bytes_t v = {(knh_uchar_t*)"", 0};
		return v;
	}
	else {
		knh_bytes_t v = {o->buf, o->size};
		return v;
	}
}

/* ------------------------------------------------------------------------ */

char *knh_BytesNULL_tochar(Bytes *o)
{
	if(IS_NULL(o)) {
		return "";
	}
	else {
		return (char*)o->buf;
	}
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_Bytes_clear(Bytes *o, size_t pos)
{
	if(pos < o->size) {
		knh_bzero(o->buf + pos, o->size - pos);
		o->size = pos;
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

void knh_Bytes_unputc(Bytes *o)
{
	if(o->size > 0) {
		o->size -= 1;
		o->buf[o->size] = '\0';
	}
}

///* ======================================================================== */
///* [malloc] */
//
//void *knh_Context_mallocOnce(Ctx* ctx, size_t n)
//{
//	KNH_ASSERT(knh_Bytes_size(ctx->bconvbuf) == 0);
//	KNH_ASSERT(n > 0);
//	Bytes *o = ctx->bconvbuf;
//	if(o->size + n >= o->capacity) {
//		size_t newsize = o->capacity * 2;
//		if(newsize < o->size + n) newsize = knh_bytes_initsize(o->size + n);
//		knh_Bytes_expands(ctx, o, newsize);
//	}
//	return (void*)o->buf;
//}
//
///* ------------------------------------------------------------------------ */
//
//void knh_Context_freeOnce(Ctx* ctx, void *p)
//{
//	KNH_ASSERT(p == (void*)ctx->bconvbuf->buf);
//	knh_Bytes_clear(ctx->bconvbuf);
//}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
