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
/* [define] */

/* ======================================================================== */
/* [macros] */

#define _knh_Array_n(a,n)      (a)->list[(n)]
#define _knh_Array_size(a)     (a)->size

/* ======================================================================== */

size_t knh_array_newsize(size_t newsize, size_t usize)
{
	if(newsize == 0) return (KNH_FASTMALLOC_SIZE / usize);
	return knh_bytes_newsize(newsize * usize);
}

/* ------------------------------------------------------------------------ */

size_t knh_array_index0(Ctx *ctx, knh_intptr_t n, size_t size)
{
	size_t idx = (size_t)n;
	if(!(idx < size)) KNH_THROW_OUTOFINDEX(ctx, n, size);
	return idx;
}

/* ------------------------------------------------------------------------ */

size_t knh_array_index(Ctx *ctx, knh_intptr_t n, size_t size)
{
	size_t idx = (n < 0) ? size + n : n;
	if(!(idx < size)) KNH_THROW_OUTOFINDEX(ctx, n, size);
	return idx;
}

/* ------------------------------------------------------------------------ */

void knh_Array_grow(Ctx *ctx, Array *a, size_t newsize, Object *v)
{
	KNH_ASSERT(a->capacity < newsize);
	size_t i;
	if(newsize == 0) newsize = (KNH_FASTMALLOC_SIZE / sizeof(Object*));
	Object **newa = (Object**)KNH_MALLOC(ctx, sizeof(Object*) * newsize);
	if(a->capacity > 0) {
		knh_memcpy(newa, a->list, (sizeof(Object*) * a->capacity));
	}
	for(i = a->capacity; i < newsize; i++) {
		KNH_INITv(newa[i], v);
	}
	Object **olda = a->list;
	a->list = newa;
	if(a->capacity > 0) {
		KNH_FREE(ctx, olda, sizeof(Object*) * a->capacity);
	}
	a->capacity = newsize;
}

/* ======================================================================== */
/* [constructors] */

knh_Array_t* new_Array0(Ctx *ctx, size_t capacity)
{
	knh_Array_t *o = (knh_Array_t*)new_hObject(ctx, FLAG_Array, CLASS_Array, CLASS_Array);
	o->capacity = 0;
	if(capacity == 0) capacity = KNH_ARRAY_INITSIZE;
	knh_Array_grow(ctx, o, capacity, KNH_NULL);
	o->size = 0;
	return o;
}

/* ------------------------------------------------------------------------ */

KNHAPI(knh_Array_t*) new_Array(Ctx *ctx, knh_class_t p1, size_t capacity)
{
	knh_class_t cid = knh_class_Generics(ctx, CLASS_Array, p1, CLASS_Any);
	knh_Array_t *o = (knh_Array_t*)new_hObject(ctx, FLAG_Array, CLASS_Array, cid);
	o->capacity = 0;
	if(capacity == 0) capacity = KNH_ARRAY_INITSIZE;
	knh_Array_grow(ctx, o, capacity, KNH_NULL);
	o->size = 0;
	return o;
}

/* ======================================================================== */
/* [field] */

Object** knh_Array_list(Array *o)
{
	return o->list;
}

/* ------------------------------------------------------------------------ */

Object* knh_Array_last(Array *o)
{
	KNH_ASSERT(o->size != 0);
	return o->list[o->size-1];
}

/* ------------------------------------------------------------------------ */

void knh_Array_subclear(Ctx *ctx, Array *o, size_t n)
{
	size_t i;
	for(i = n; i < o->size; i++) {
		KNH_SETv(ctx, o->list[i], KNH_NULL);
	}
	if(n <= o->size) {
		o->size = n;
	}
}

/* ======================================================================== */
/* [utils] */

KNHAPI(void) knh_Array_add(Ctx *ctx, Array *o, Any *value)
{
	if(o->size == o->capacity) {
		knh_Array_grow(ctx, o, knh_array_newsize(o->capacity * 2, sizeof(Object*)), KNH_NULL);
	}
	DBG2_ASSERT(o->size < o->capacity);
	KNH_SETv(ctx, o->list[o->size], value);
	o->size++;
}

/* ------------------------------------------------------------------------ */

void knh_Array_addArray(Ctx *ctx, Array *o, Array *other)
{
	L_TAIL:;
	{
		size_t i, asize = other->size;
		if(!(o->size + asize < o->capacity)) {
			knh_Array_grow(ctx, o, knh_array_newsize(o->capacity * 2, sizeof(Object*)), KNH_NULL);
			goto L_TAIL;
		}
		DBG2_ASSERT(o->size < o->capacity);
		for(i = 0; i < asize; i++) {
			KNH_SETv(ctx, o->list[o->size], knh_Array_n(other, i));
			o->size++;
		}
	}
}

/* ------------------------------------------------------------------------ */

void knh_Array_remove(Ctx *ctx, Array *o, size_t n)
{
	DBG2_ASSERT(n < o->size);
	size_t i;
	Object *removed = o->list[n];
	for(i = n; i < o->size - 1; i++) {
		o->list[i] = o->list[i+1];
	}
	o->size--;
	o->list[o->size] = removed;
}

/* ------------------------------------------------------------------------ */

Any* knh_Array_pop(Ctx *ctx, Array *o)
{
	if(o->size > 0) {
		o->size--;
		return o->list[o->size];
	}else {
		return KNH_NULL;
	}
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
