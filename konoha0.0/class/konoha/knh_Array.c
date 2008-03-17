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
/* [define] */

#ifndef KNH_ARRAY_INITSIZE
#define KNH_ARRAY_INITSIZE  4
#endif/*KNH_ARRAY_INITSIZE*/

#define KNH_INITSIZE(n)   ((n == 0) ? KNH_ARRAY_INITSIZE : n)

/* ======================================================================== */
/* [macros] */

#define _knh_Array_size(a)     (a)->size
#define _knh_Array_n(a,n)      (a)->list[(n)]

#define _KNH_ARRAY_RESIZE(ctx, TYPE, array, oldsize, newsize) \
	if(newsize != 0 && newsize != oldsize) { \
		TYPE *newarray = (TYPE *)knh_malloc(ctx, KNH_SIZE(sizeof(TYPE) * newsize)); \
		if(newsize < oldsize) { \
			knh_memcpy(newarray, array, (sizeof(TYPE) * newsize)); \
		}else { \
			knh_memcpy(newarray, array, (sizeof(TYPE) * oldsize)); \
		} \
		knh_free(array, KNH_SIZE(sizeof(TYPE) * oldsize)); \
		array = newarray; \
		oldsize = newsize; \
	} \

/* ======================================================================== */
/* [structs] */

void knh_Array_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	Array *b =  (Array*)s1;
	b->capacity = knh_uint_max(KNH_INITSIZE(init), 1);
	b->size = 0;
	b->list = knh_oarray_malloc(ctx, b->capacity, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

void knh_Array_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
	Array *b =  (Array*)s1;
	Array *b2 = (Array*)s2;
	
	size_t i;
	b2->capacity = b->capacity;
	b2->size = b->size;
	b2->list = knh_oarray_malloc(ctx, b2->capacity, KNH_NULL);
	for(i = 0; i < b2->size; i++) {
		KNH_SETv(ctx, b2->list[i], b->list[i]);
	}
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_Array_struct_compare(Ctx *ctx, Struct *s1, Struct *s2) 
{
	Array *b =  (Array*)s1;
	Array *b2 = (Array*)s2;
	
	size_t i;
	for(i = 0; i < knh_uint_min(b->size, b2->size); i++) {
		knh_int_t res = knh_Object_compare(ctx, b->list[i], b2->list[i]);
		if(res != 0) return res;
	}
	return (knh_int_t)b->size - (knh_int_t)b2->size;
}

/* ------------------------------------------------------------------------ */

void knh_Array_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Array *b = (Array*)s;
	if(b->list != NULL) {
		knh_oarray_traverse(ctx, b->list, b->capacity, gc);
	}
}

/* ======================================================================== */
/* [constructors] */

/* ------------------------------------------------------------------------ */

Array* new_Array(Ctx *ctx, size_t capacity)
{
	Array *b = (Array*)knh_Object_malloc0(ctx, KNH_FLAG_Array, CLASS_Array, sizeof(Array));
	knh_Array_struct_init(ctx, (Struct*)b, capacity, NULL);
	return b;
}

/* ------------------------------------------------------------------------ */

Object* knh_Array_fvalue(Ctx *ctx, knh_class_t cid)
{
	return new_Array(ctx, 0);
}


/* ======================================================================== */
/* [field] */

INLINE
Object** knh_Array_list(Array *b)
{
	return b->list;
}

/* ------------------------------------------------------------------------ */


Object* knh_Array_last(Array *b)
{
	DEBUG_ASSERT(b->size != 0);
	return b->list[b->size-1];
}

/* ------------------------------------------------------------------------ */


void knh_Array_subclear(Ctx *ctx, Array *b, size_t n)
{
	size_t i;
	for(i = n; i < b->size; i++) {
		KNH_SETv(ctx, b->list[i], KNH_NULL);
	}
	if(n <= b->size) {
		b->size = n;
	}
}

/* ======================================================================== */
/* [utils] */

INLINE
size_t knh_array_index(knh_int_t n, size_t size)
{
	return (n < 0) ? size + n : n;
}

/* ------------------------------------------------------------------------ */

INLINE
size_t knh_Array_util_slice(knh_int_t n, size_t size)
{
	if(size == 0) return 0;
	if(n < 0) return (n % size);
	return knh_uint_min(n, size-1);
}

/* ======================================================================== */
/* [methods] */

void knh_Array_resize(Ctx *ctx, Array *b, size_t newsize)
{
	Object **newlist; size_t i;
	if(newsize == 0 || newsize == b->capacity) {
		return ;
	}
	
	newlist = knh_malloc(ctx, sizeof(Object*) * newsize);
	if(newsize < b->capacity) { 
		knh_memcpy(newlist, b->list, sizeof(Object*) * newsize);
		for(i = newsize; i < b->size; i++) {
			knh_sweep(ctx, b->list[i]);
		}
	}else {
		knh_memcpy(newlist, b->list, sizeof(Object*) * b->capacity);
		for(i = b->capacity; i < newsize; i++) {
			KNH_INITv(newlist[i], KNH_NULL);
		}
	}
	knh_free(b->list, sizeof(Object*) * b->capacity);
	b->list = newlist;
	b->capacity = newsize;
}

/* ------------------------------------------------------------------------ */
/* @method void Array.add::fast(Any value) */

void knh_Array_add__fast(Ctx *ctx, Array *b, Any *value)
{
	if(b->size == b->capacity) {
		knh_Array_resize(ctx, b, b->capacity * 2);
	}
	KNH_SETv(ctx, b->list[b->size], value);
	b->size++;
}

#define _knh_Array_append(ctx,b,n) knh_Array_add__fast(ctx,b,n)

/* ------------------------------------------------------------------------ */
/* @method void Array.add(Any value) */


void knh_Array_add(Ctx *ctx, Array *b, Any *value)
{
	if(b->size == b->capacity) {
		knh_Array_resize(ctx, b, b->capacity * 2);
	}
	KNH_SETv(ctx, b->list[b->size], value);
	b->size++;
}

/* ------------------------------------------------------------------------ */
/* @method Any Array.pop() */

INLINE
Any* knh_Array_pop(Ctx *ctx, Array *b)
{
	if(b->size > 0) {
		b->size--;
		return b->list[b->size];
	}else {
		return KNH_NULL;
	}
}

/* ------------------------------------------------------------------------ */

/* @method Array! Array.slice(Int start, Int end) */


Array *knh_Array_slice(Ctx *ctx, Array *b, knh_int_t start, knh_int_t end) 
{
	size_t s = knh_array_index(start, b->size);
	size_t e = knh_Array_util_slice(end, b->size);	
	size_t i = e - s + 1;
	if(i <= 0) {
		return new_Array(ctx,  1);
	}
	Array *a = new_Array(ctx, knh_uint_min(i,1));
	for(i = s; i <= e; i++) {
		knh_Array_add(ctx, a, b->list[i]);
	}
	return a;
}

/* ------------------------------------------------------------------------ */


void knh_Array_swap(Array *b, knh_int_t n, knh_int_t n2)
{
	Object *temp = b->list[n2];
	b->list[n2] = b->list[n];
	b->list[n] = temp;
}

/* ------------------------------------------------------------------------ */
/* @method void Array.clear() */

void knh_Array_clear(Ctx *ctx, Array *b) 
{
	size_t i;
	for(i = 0; i < b->capacity; i++) {
		KNH_SETv(ctx, b->list[i], KNH_NULL);
	}
	b->size = 0;
}

/* ======================================================================== */
/* [movabletext] */

INLINE
knh_bool_t knh_array_isdump(size_t c)
{
	return (c < 100);
}

/* ------------------------------------------------------------------------ */
/* @method void Array.%dump(OutputStream w, Any m) */

void knh_Array__dump(Ctx *ctx, Array *b, OutputStream *w, Any *m)
{
	knh_putc(ctx, w, '[');
	size_t c;
	for(c = 0; c < b->size; c++) {
		if(c > 0) {
			knh_write_delim(ctx,w);
		}
		if(!knh_array_isdump(c)) {
			knh_write_dots(ctx, w);
			break;
		}
		knh_format(ctx, w, METHODN__dump, b->list[c], KNH_NULL);
	}
	knh_putc(ctx, w, ']');
}

/* ======================================================================== */
/* [iterators] */

Object*
knh_Array_var_next(Ctx *ctx, Iterator *it)
{
	Array *b = (Array*)knh_Iterator_source(it);
	DEBUG_ASSERT(IS_Array(b));
	size_t pos = knh_Iterator_pos(it);
	while(pos < b->size) {
		//DEBUG("pos=%d", pos);
		if(IS_NOTNULL(b->list[pos])) {
			knh_Iterator_setpos(it, pos+1);
			return b->list[pos]; 
		}
	}
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

/* @map Array Iterator! */

Object* knh_Array_Iterator(Ctx *ctx, Object *self, MapMap *map)
{
	return new_Iterator(ctx, CLASS_any, self, knh_Array_var_next);	
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
