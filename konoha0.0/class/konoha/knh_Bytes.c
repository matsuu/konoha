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
/* [constructors] */

Bytes* new_Bytes(Ctx *ctx, size_t capacity)
{
	knh_Bytes_t* o = (Bytes*)new_PObject0(ctx, FLAG_Bytes, CLASS_Bytes, CLASS_Bytes);
	o->buf = knh_barray_malloc(ctx, capacity);
	o->size = 0;
	return o;
}

/* ------------------------------------------------------------------------ */

static Object *knh_constBytes = NULL;

Object* knh_Bytes_fdefault(Ctx *ctx, knh_class_t cid)
{
	if(knh_constBytes == NULL) {
		knh_constBytes = (Object*)new_Bytes(ctx, 0);
		KNH_TSTATICOBJ(&knh_constBytes);
	}
	return knh_constBytes;
}

/* ======================================================================== */
/* [methods] */

INLINE
knh_bytes_t knh_Bytes_tobytes(Bytes *o)
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

///* ------------------------------------------------------------------------ */
//
//void knh_Bytes_ensureSize(Ctx *ctx, Bytes *o, size_t offset, size_t size)
//{
//	if(offset + size < o->size) {
//		return;
//	}
//	knh_Bytes_resize(ctx, b, offset + size);
//}

/* ------------------------------------------------------------------------ */

INLINE
void knh_Bytes_clear(Bytes *o)
{
	knh_bzero(o->buf, o->size);
	o->size = 0;
}

/* ------------------------------------------------------------------------ */

void knh_Bytes_putc(Ctx *ctx, Bytes *o, int ch)
{
	size_t capacity = knh_barray_capacity(o->buf);
	if(o->size == capacity) {
		if(o->buf == NULL) {
			o->buf = knh_barray_malloc(ctx, 256);
		}
		else {
			o->buf = knh_barray_resize(ctx, o->buf, capacity * 2);
		}
	}
	o->buf[o->size] = ch;
	o->size += 1;
}

/* ------------------------------------------------------------------------ */

void knh_Bytes_write(Ctx *ctx, Bytes *o, knh_bytes_t v)
{
	if(v.len == 0) {
		return ;
	}
	else {
		size_t capacity = knh_barray_capacity(o->buf);
		if(o->size + v.len >= capacity) {
			size_t newsize = knh_uint_max(capacity * 2, o->size + v.len);
			if(o->buf == NULL) {
				o->buf = knh_barray_malloc(ctx, newsize);
			}
			else {
				o->buf = knh_barray_resize(ctx, o->buf, newsize);
			}
		}
		knh_memcpy(&o->buf[o->size], v.buf, v.len);
		o->size += v.len;
	}
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

#ifdef __cplusplus
}
#endif
