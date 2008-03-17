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
#define _knh_Bytes_value(o)     (o)->value

/* ======================================================================== */
/* [structs] */

void
knh_Bytes_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	Bytes *b =  (Bytes*)s1;
   b->capacity = knh_uint_max(16, init);
   b->size = 0;
   b->value = (knh_uchar_t*)knh_malloc(ctx, b->capacity);
   knh_bzero(b->value, b->capacity);
}

/* ------------------------------------------------------------------------ */

void
knh_Bytes_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
	Bytes *b =  (Bytes*)s1;
	Bytes *b2 = (Bytes*)s2;
	
	b2->size  =     b->size;
	b2->capacity =  b->capacity;
   b2->value = (knh_uchar_t*)knh_malloc(ctx, b2->capacity);
   knh_memcpy(b2->value, b->value, b2->size);
//	KNH_INITv(b2->enc,  b->enc);
}

/* ------------------------------------------------------------------------ */

knh_int_t
knh_Bytes_struct_compare(Ctx *ctx, Struct *s1, Struct *s2) 
{
	Bytes *b =  (Bytes*)s1;
	Bytes *b2 = (Bytes*)s2;
	size_t i;
	for(i = 0; i < knh_uint_max(b->size, b2->size); i++) {
		knh_int_t res = (b->value[i] - b2->value[i]);
		if(res != 0) return res;
	}
	return b->size - b2->size;	
}

/* ------------------------------------------------------------------------ */

void
knh_Bytes_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Bytes *b = (Bytes*)s;
	if(IS_SWEEP(gc) && b->value != NULL) {
		if(!knh_Bytes_isStackBuffer(b)) {
   		knh_free(b->value, b->capacity);
		}
		b->value = NULL;
	}
}

/* ======================================================================== */
/* [constructors] */

/* ------------------------------------------------------------------------ */

Bytes* new_Bytes(Ctx *ctx, size_t capacity)
{
	Bytes* b = (Bytes*)knh_Object_malloc(ctx, CLASS_Bytes);
	knh_Bytes_struct_init(ctx, (Struct*)b, capacity, NULL);
	return b;
}

/* ------------------------------------------------------------------------ */

Object* knh_Bytes_fvalue(Ctx *ctx, knh_class_t cid)
{
	return new_Bytes(ctx, 256);
}

/* ------------------------------------------------------------------------ */

Bytes* new_Bytes__buf(Ctx *ctx, char *buf, size_t bufsiz)
{
	Bytes* b = (Bytes*)knh_Object_malloc(ctx, CLASS_Bytes);
	b->size = 0;
	b->capacity = bufsiz;
	knh_bzero(buf, bufsiz);
	knh_Bytes_setStackBuffer(b, 1);
	b->value = (knh_uchar_t*)buf;
	return b;
}

/* ======================================================================== */
/* [methods] */

INLINE
knh_bytes_t knh_Bytes_tobytes(Bytes *b)
{
	knh_bytes_t v = {b->value, b->size};
	return v;
}

#define _knh_Bytes_tochar(b)  (char*)knh_Bytes_value(b)

/* ------------------------------------------------------------------------ */

knh_bytes_t knh_BytesNULL_tobytes(Bytes *b)
{
	if(IS_NULL(b)) {
		knh_bytes_t v = {(knh_uchar_t*)"", 0};
		return v;
	}
	else {
		knh_bytes_t v = {b->value, b->size};
		return v;
	}
}

/* ------------------------------------------------------------------------ */

char *knh_BytesNULL_tochar(Bytes *b)
{
	if(IS_NULL(b)) {
		return "";
	}
	else {
		return (char*)b->value;
	}
}

/* ------------------------------------------------------------------------ */

INLINE
knh_uchar_t *knh_Bytes_last(Bytes *b)
{
	return b->value + b->size;
}

/* ------------------------------------------------------------------------ */

void knh_Bytes_resize(Ctx *ctx, Bytes *b, size_t newsize)
{
	DEBUG_ASSERT(!knh_Bytes_isStackBuffer(b));

	knh_uchar_t *newba = (knh_uchar_t*)knh_malloc(ctx, newsize);
	if(newsize < b->size) {
		knh_memcpy(newba, b->value, newsize);
	}else{
		knh_memcpy(newba, b->value, b->size);
		knh_bzero(&newba[b->size], newsize - b->size);
	}
	knh_free(b->value, b->capacity);
	b->value = newba;
	b->capacity = newsize;
}

///* ------------------------------------------------------------------------ */
//
//void knh_Bytes_ensureSize(Ctx *ctx, Bytes *b, size_t offset, size_t size)
//{
//	if(offset + size < b->size) {
//		return;
//	}
//	knh_Bytes_resize(ctx, b, offset + size);
//}

/* ------------------------------------------------------------------------ */

INLINE
void knh_Bytes_clear(Bytes *b)
{
	knh_bzero(b->value, b->size);
	b->size = 0;
}

/* ------------------------------------------------------------------------ */

void knh_Bytes_putc(Ctx *ctx, Bytes *b, int_byte_t ch)
{
	if(b->size == b->capacity) {
		if(knh_Bytes_isStackBuffer(b)) {
			return;
		}
		knh_Bytes_resize(ctx, b, b->capacity * 2);
	}
	b->value[b->size] = ch;
	b->size += 1;
}

/* ------------------------------------------------------------------------ */

void knh_Bytes_write(Ctx *ctx, Bytes *b, knh_bytes_t v)
{
	if(b->size + v.len >= b->capacity) {
		if(knh_Bytes_isStackBuffer(b)) {
			return;
		}
		size_t newsize = b->capacity * 2;
		if(newsize < b->size + v.len) newsize = b->size + v.len;
		knh_Bytes_resize(ctx, b, newsize);
	}
	knh_memcpy(&b->value[b->size], v.buf, v.len);
	b->size += v.len;
}

/* ------------------------------------------------------------------------ */

void knh_Bytes_unputc(Bytes *b)
{
	if(b->size > 0) {
		b->size -= 1;
		b->value[b->size] = '\0';
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
