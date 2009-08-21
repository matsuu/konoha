/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2005-2009, Kimio Kuramitsu <kimio at ynu.ac.jp>
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

#ifdef KNH_CC_METHODAPI

/* ======================================================================== */
/* [new] */



/* ======================================================================== */
/* [add] */

/* @method void Array.add(T1! value) */

static METHOD knh__Array_add(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {
		Array *o = (Array*)sfp[0].o;
		if(o->size == o->capacity) {
			knh_Array_grow(ctx, o, knh_array_newsize(o->capacity * 2, sizeof(Object*)), KNH_NULL);
		}
		knh_sfp_boxing(ctx, sfp + 1);
		KNH_SETv(ctx, o->list[o->size], sfp[1].o);
		o->size++;
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] void Array.opLshift(T1! v) */

static METHOD knh__Array_opLshift(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {
		Array *o = (Array*)sfp[0].o;
		knh_sfp_t *v = sfp + 1;
		int i, ac = knh_stack_argc(ctx, v);
		for(i = 0; i < ac; i++) {
			knh_sfp_boxing(ctx, v + i);
			knh_Array_add(ctx, o, v[i].o);
		}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void IArray.add(Int! value) */

static METHOD knh__IArray_add(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	IArray *o = (IArray*)sfp[0].o;
	if(o->size == o->capacity) {
		knh_IArray_grow(ctx, o, knh_array_newsize(o->capacity * 2, sizeof(knh_int_t)), 0);
	}
	o->ilist[o->size] = sfp[1].ivalue;
	o->size++;
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] void IArray.opLshift(Int! v) */

static METHOD knh__IArray_opLshift(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	IArray *o = (IArray*)sfp[0].o;
	knh_sfp_t *v = sfp + 1;
	int i, ac = knh_stack_argc(ctx, v);
	for(i = 0; i < ac; i++) {
		knh_IArray_add(ctx, o, v[i].ivalue);
	}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void FArray.add(Float! value) */

static METHOD knh__FArray_add(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	FArray *o = (FArray*)sfp[0].o;
	if(o->size == o->capacity) {
		knh_FArray_grow(ctx, o, knh_array_newsize(o->capacity * 2, sizeof(knh_float_t)), 0.0);
	}
	o->flist[o->size] = sfp[1].fvalue;
	o->size++;
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] void FArray.opLshift(Float! v) */

static METHOD knh__FArray_opLshift(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	FArray *o = (FArray*)sfp[0].o;
	knh_sfp_t *v = sfp + 1;
	int i, ac = knh_stack_argc(ctx, v);
	for(i = 0; i < ac; i++) {
		knh_FArray_add(ctx, o, v[i].fvalue);
	}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ======================================================================== */


///* ------------------------------------------------------------------------ */
///* @ method This! Array.opOffset(Int s, Int offset) @Debug */
//
//static METHOD knh__Array_opOffset(Ctx *ctx, knh_sfp_t *sfp)
//{
//	Array *o = (Array*)sfp[0].o;
//	size_t s = IS_NULL(sfp[1].o) ? 0 : knh_array_index(ctx, p_int(sfp[1]), o->size);
//	knh_intptr_t e = IS_NULL(sfp[1].o) ? o->size : s + p_int(sfp[2]);
//	if(e > o->size) e = o->size; else if(e < 0) e = 0;
//	KNH_RETURN(ctx, sfp, new_Array__subset(ctx, o, s, e));
//}

/* ======================================================================== */

/* ------------------------------------------------------------------------ */
/* @method void Array.insert(Int! n, T1 v) */

static METHOD knh__Array_insert(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		size_t i, n = knh_array_index(ctx, p_int(sfp[1]), o->size);
		if(o->size == o->capacity) {
			knh_Array_grow(ctx, o, knh_array_newsize(o->capacity * 2, sizeof(Object*)), KNH_NULL);
		}
		Object *temp = o->list[o->size];
		o->size++;
		for(i = o->size - 1; i > n ; i--) {
			o->list[i] = o->list[i-1];
		}
		o->list[n] = temp;
		knh_sfp_boxing(ctx, sfp + 2);
		KNH_SETv(ctx, o->list[n], sfp[2].o);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void Array.remove(Int! n) */

static METHOD knh__Array_remove(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		size_t n = knh_array_index(ctx, p_int(sfp[1]), o->size);
		knh_Array_remove(ctx, o, n);
	}
	KNH_RETURN_void(ctx,sfp);
}

/* ------------------------------------------------------------------------ */
/* @method T1 Array.pop() */

static METHOD knh__Array_pop(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	if(!knh_Object_isImmutable(o) && o->size > 0) {
		o->size--;
		KNH_RETURN(ctx, sfp, o->list[o->size]);
	}else {
		KNH_RETURN(ctx,sfp, KNH_NULL);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Array.clear() */

void knh_Array_clear(Ctx *ctx, Array *o)
{
	if(!knh_Object_isImmutable(o)) {
		size_t i;
		for(i = 0; i < o->size; i++) {
			KNH_SETv(ctx, o->list[i], KNH_NULL);
		}
		o->size = 0;
	}
}

/* ------------------------------------------------------------------------ */
/* @method Int! Array.indexOf(T1 v) */

static METHOD knh__Array_indexOf(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	knh_sfp_boxing(ctx, sfp + 1);
	size_t i;
	for(i = 0; i < o->size; i++) {
		if(knh_Object_compareTo(ctx, o->list[i], sfp[1].o) == 0) {
			KNH_RETURN_Int(ctx, sfp, i);
		}
	}
	KNH_RETURN_Int(ctx, sfp, -1); // Not Found
}

/* ------------------------------------------------------------------------ */
/* @method Int! Array.lastIndexOf(T1 v) */

static METHOD knh__Array_lastIndexOf(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	knh_sfp_boxing(ctx, sfp + 1);
	/* size_t i; */
	int i;
	for(i = o->size - 1; i >= 0; i--) {
		if(knh_Object_compareTo(ctx, o->list[i], sfp[1].o) == 0) {
			KNH_RETURN_Int(ctx, sfp, i);
		}
	}
	KNH_RETURN_Int(ctx, sfp, -1); // Not Found
}

/* ======================================================================== */
/* [Collections] */

/* ------------------------------------------------------------------------ */
/* @method void Array.sort(ArrayCmp f) */

static METHOD knh__Array_sort(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	TODO_THROW(ctx);
	Array *o = (Array*)sfp[0].o;
	knh_qsort(o->list, o->size, sizeof(Object*), (int (*)(const void*, const void*))knh_Object_compareTo);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void Array.reverse() */

static METHOD knh__Array_reverse(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	Array *o = (Array*)sfp[0].o;
	size_t i;
	for(i = 0; i < o->size / 2; i++) {
		size_t n = o->size - i - 1;
		Object *temp = o->list[i];
		o->list[i] = o->list[n];
		o->list[n] = temp;
	}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void Array.swap(Int! m, Int! n) */

static METHOD knh__Array_swap(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	Array *o = (Array*)sfp[0].o;
	size_t m = knh_array_index(ctx, p_int(sfp[1]), o->size);
	size_t n = knh_array_index(ctx, p_int(sfp[2]), o->size);
	Object *temp = o->list[n];
	o->list[n] = o->list[m];
	o->list[m] = temp;
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void Array.shuffle() */

static METHOD knh__Array_shuffle(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	Array *o = (Array*)sfp[0].o;
	size_t i;
	for(i = 0; i < o->size; i++) {
		size_t m = knh_rand() % o->size;
		size_t n = knh_rand() % o->size;
		Object *temp = o->list[n];
		o->list[n] = o->list[m];
		o->list[m] = temp;
	}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* [IArray] */

static int qsort_icmp(const void* ap, const void* bp)
{
	knh_int_t a = *((knh_int_t*)ap);
	knh_int_t b = *((knh_int_t*)bp);
	if(a < b) return -1;
	if(a > b) return 1;
	return 0;
}

/* ------------------------------------------------------------------------ */
/* @method void IArray.sort() */

static METHOD knh__IArray_sort(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	IArray *o = (IArray*)sfp[0].o;
	knh_qsort(o->ilist, o->size, sizeof(knh_int_t), qsort_icmp);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void IArray.reverse() */

static METHOD knh__IArray_reverse(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	IArray *o = (IArray*)sfp[0].o;
	size_t i;
	for(i = 0; i < o->size / 2; i++) {
		size_t n = o->size - i - 1;
		knh_int_t temp = o->ilist[i];
		o->ilist[i] = o->ilist[n];
		o->ilist[n] = temp;
	}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void IArray.swap(Int! m, Int! n) */

static METHOD knh__IArray_swap(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	IArray *o = (IArray*)sfp[0].o;
	size_t m = knh_array_index(ctx, p_int(sfp[1]), o->size);
	size_t n = knh_array_index(ctx, p_int(sfp[2]), o->size);
	knh_int_t temp = o->ilist[n];
	o->ilist[n] = o->ilist[m];
	o->ilist[m] = temp;
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void IArray.shuffle() */

static METHOD knh__IArray_shuffle(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	IArray *o = (IArray*)sfp[0].o;
	size_t i;
	for(i = 0; i < o->size; i++) {
		size_t m = knh_rand() % o->size;
		size_t n = knh_rand() % o->size;
		knh_int_t temp = o->ilist[n];
		o->ilist[n] = o->ilist[m];
		o->ilist[m] = temp;
	}
	}
	KNH_RETURN_void(ctx, sfp);
}


/* ------------------------------------------------------------------------ */
/* [FArray] */

static int qsort_fcmp(const void* ap, const void* bp)
{
	knh_float_t a = *((knh_float_t*)ap);
	knh_float_t b = *((knh_float_t*)bp);
	if(a < b) return -1;
	if(a > b) return 1;
	return 0;
}

/* ------------------------------------------------------------------------ */
/* @method void FArray.sort() */

static METHOD knh__FArray_sort(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	FArray *o = (FArray*)sfp[0].o;
	knh_qsort(o->flist, o->size, sizeof(knh_float_t), qsort_fcmp);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void FArray.reverse() */

static METHOD knh__FArray_reverse(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	FArray *o = (FArray*)sfp[0].o;
	size_t i;
	for(i = 0; i < o->size / 2; i++) {
		size_t n = o->size - i - 1;
		knh_float_t temp = o->flist[i];
		o->flist[i] = o->flist[n];
		o->flist[n] = temp;
	}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void FArray.swap(Int! m, Int! n) */

static METHOD knh__FArray_swap(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	FArray *o = (FArray*)sfp[0].o;
	size_t m = knh_array_index(ctx, p_int(sfp[1]), o->size);
	size_t n = knh_array_index(ctx, p_int(sfp[2]), o->size);
	knh_float_t temp = o->flist[n];
	o->flist[n] = o->flist[m];
	o->flist[m] = temp;
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void FArray.shuffle() */

static METHOD knh__FArray_shuffle(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	FArray *o = (FArray*)sfp[0].o;
	size_t i;
	for(i = 0; i < o->size; i++) {
		size_t m = knh_rand() % o->size;
		size_t n = knh_rand() % o->size;
		knh_float_t temp = o->flist[n];
		o->flist[n] = o->flist[m];
		o->flist[m] = temp;
	}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ======================================================================== */
/* [movabletext] */


/* ======================================================================== */
/* [mapping] */


/* ------------------------------------------------------------------------ */

Mapper *knh_tMapper_newIteratorArray(Ctx *ctx, knh_class_t icid, knh_class_t acid)
{
	Mapper *mpr = new_Mapper(ctx, KNH_FLAG_MMF_TOTAL, acid, icid, knh_Array_Iterator, KNH_NULL);
	knh_ClassMap_add(ctx, ctx->share->ClassTable[acid].cmap, mpr);
	mpr = new_Mapper(ctx, KNH_FLAG_MMF_TOTAL, icid, acid, knh_Iterator_Array, KNH_NULL);
	knh_ClassMap_add(ctx, ctx->share->ClassTable[icid].cmap, mpr);
	return mpr;
}

/* ------------------------------------------------------------------------ */

Mapper *knh_tMapper_newArrayIterator(Ctx *ctx, knh_class_t acid, knh_class_t icid)
{
	Mapper *mpr = new_Mapper(ctx, KNH_FLAG_MMF_TOTAL, icid, acid, knh_Iterator_Array, KNH_NULL);
	knh_ClassMap_add(ctx, ctx->share->ClassTable[icid].cmap, mpr);
	mpr = new_Mapper(ctx, KNH_FLAG_MMF_TOTAL, acid, icid, knh_Array_Iterator, KNH_NULL);
	knh_ClassMap_add(ctx, ctx->share->ClassTable[acid].cmap, mpr);
	return mpr;
}

/* ======================================================================== */
/* [2d,3d] */
/* @data */

typedef struct {
	size_t x;
	size_t y;
	size_t z;
	size_t w;   /* unused */
} knh_darray_t;

/* ------------------------------------------------------------------------ */

static
void *knh_array_dmalloc(Ctx *ctx, size_t x, size_t y, size_t z, size_t usize)
{
	size_t capacity = x * y * z;
	knh_darray_t *d = (knh_darray_t*)KNH_MALLOC(ctx, (capacity * usize) + sizeof(knh_darray_t));
	d->x = x; d->y = y; d->z = z; d->w = d->x * d->y;
	return (void*)(d+1);
}

/* ------------------------------------------------------------------------ */

void knh_array_dfree(Ctx *ctx, void *ptr, size_t capacity, size_t usize)
{
	knh_darray_t *d = ((knh_darray_t*)ptr) - 1;
	KNH_FREE(ctx, d, (capacity * usize) + sizeof(knh_darray_t));
}

/* ------------------------------------------------------------------------ */
/* [Array] */

static
void knh_ArrayDim_init(Ctx *ctx, Array *a, size_t x, size_t y, size_t z)
{
	knh_Array_setDim(a, 1);
	a->list = (Object**)knh_array_dmalloc(ctx, x, y, z, sizeof(Object*));
	a->capacity = x * y * z;
	knh_class_t p1 = ctx->share->ClassTable[knh_Object_cid(a)].p1;
	Object *v = (p1 == CLASS_Any) ? KNH_NULL : knh_getClassDefaultValue(ctx, p1);
	int i = 0;
	for(i = 0; i < a->capacity; i++) {
		KNH_INITv(a->list[i], v);
	}
	a->size = a->capacity;
}

/* ------------------------------------------------------------------------ */
/* @method This! Array.new:array2D(Int! x, Int! y) @Private */

static METHOD knh__Array_new__array2D(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_ArrayDim_init(ctx, (Array*)sfp[0].o, p_size(sfp[1]), p_size(sfp[2]), 1);
	KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ------------------------------------------------------------------------ */
/* @method This! Array.new:array3D(Int! x, Int! y, Int! z) @Private */

static METHOD knh__Array_new__array3D(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_ArrayDim_init(ctx, (Array*)sfp[0].o, p_size(sfp[1]), p_size(sfp[2]), p_size(sfp[3]));
	KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ------------------------------------------------------------------------ */
/* @method T1 Array.get2D(Int! x, Int! y) */

static METHOD knh__Array_get2D(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	knh_darray_t *d = ((knh_darray_t*)o->list) - 1;
	size_t x = knh_array_index(ctx, p_int(sfp[1]), d->x);
	size_t y = knh_array_index(ctx, p_int(sfp[2]), d->y);
	KNH_RETURN(ctx, sfp, o->list[x + y * d->x]);
}

/* ------------------------------------------------------------------------ */
/* @method T1 Array.get3D(Int! x, Int! y, Int! z) */

static METHOD knh__Array_get3D(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	knh_darray_t *d = ((knh_darray_t*)o->list) - 1;
	size_t x = knh_array_index(ctx, p_int(sfp[1]), d->x);
	size_t y = knh_array_index(ctx, p_int(sfp[2]), d->y);
	size_t z = knh_array_index(ctx, p_int(sfp[3]), d->z);
	KNH_RETURN(ctx, sfp, o->list[x + y * d->x + z * d->w]);
}

/* ------------------------------------------------------------------------ */
/* @method void Array.set2D(Int! x, Int! y, T1 v) */

static METHOD knh__Array_set2D(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	Array *o = (Array*)sfp[0].o;
	knh_darray_t *d = ((knh_darray_t*)o->list) - 1;
	size_t x = knh_array_index(ctx, p_int(sfp[1]), d->x);
	size_t y = knh_array_index(ctx, p_int(sfp[2]), d->y);
	knh_sfp_boxing(ctx, sfp + 3);
	KNH_SETv(ctx, o->list[x + y * d->x], sfp[3].o);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void Array.set3D(Int! x, Int! y, Int! z, T1 v) */

static METHOD knh__Array_set3D(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	Array *o = (Array*)sfp[0].o;
	knh_darray_t *d = ((knh_darray_t*)o->list) - 1;
	size_t x = knh_array_index(ctx, p_int(sfp[1]), d->x);
	size_t y = knh_array_index(ctx, p_int(sfp[2]), d->y);
	size_t z = knh_array_index(ctx, p_int(sfp[3]), d->z);
	knh_sfp_boxing(ctx, sfp + 4);
	KNH_SETv(ctx, o->list[x + y * d->x + z * d->w], sfp[4].o);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* [IArray] */

static
void knh_IArrayDim_init(Ctx *ctx, IArray *a, size_t x, size_t y, size_t z)
{
	knh_IArray_setDim(a, 1);
	a->ilist = (knh_int_t*)knh_array_dmalloc(ctx, x, y, z, sizeof(knh_int_t));
	a->capacity = x * y * z;
	int i = 0;
	for(i = 0; i < a->capacity; i++) {
		a->ilist[i] = 0;
	}
	a->size = a->capacity;
}

/* ------------------------------------------------------------------------ */
/* @method This! IArray.new:array2D(Int! x, Int! y) @Private */

static METHOD knh__IArray_new__array2D(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_IArrayDim_init(ctx, (IArray*)sfp[0].o, p_size(sfp[1]), p_size(sfp[2]), 1);
	KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ------------------------------------------------------------------------ */
/* @method This! IArray.new:array3D(Int! x, Int! y, Int! z) @Private */

static METHOD knh__IArray_new__array3D(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_IArrayDim_init(ctx, (IArray*)sfp[0].o, p_size(sfp[1]), p_size(sfp[2]), p_size(sfp[3]));
	KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ------------------------------------------------------------------------ */
/* @method Int! IArray.get2D(Int! x, Int! y) */

static METHOD knh__IArray_get2D(Ctx *ctx, knh_sfp_t *sfp)
{
	IArray *o = (IArray*)sfp[0].o;
	knh_darray_t *d = ((knh_darray_t*)o->ilist) - 1;
	size_t x = knh_array_index(ctx, p_int(sfp[1]), d->x);
	size_t y = knh_array_index(ctx, p_int(sfp[2]), d->y);
	KNH_RETURN_Int(ctx, sfp, o->ilist[x + y * d->x]);
}

/* ------------------------------------------------------------------------ */
/* @method Int! IArray.get3D(Int! x, Int! y, Int! z) */

static METHOD knh__IArray_get3D(Ctx *ctx, knh_sfp_t *sfp)
{
	IArray *o = (IArray*)sfp[0].o;
	knh_darray_t *d = ((knh_darray_t*)o->ilist) - 1;
	size_t x = knh_array_index(ctx, p_int(sfp[1]), d->x);
	size_t y = knh_array_index(ctx, p_int(sfp[2]), d->y);
	size_t z = knh_array_index(ctx, p_int(sfp[3]), d->z);
	KNH_RETURN_Int(ctx, sfp, o->ilist[x + y * d->x + z * d->w]);
}

/* ------------------------------------------------------------------------ */
/* @method void IArray.set2D(Int! x, Int! y, Int! v) */

static METHOD knh__IArray_set2D(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	IArray *o = (IArray*)sfp[0].o;
	knh_darray_t *d = ((knh_darray_t*)o->ilist) - 1;
	size_t x = knh_array_index(ctx, p_int(sfp[1]), d->x);
	size_t y = knh_array_index(ctx, p_int(sfp[2]), d->y);
	o->ilist[x + y * d->x] = sfp[3].ivalue;
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void IArray.set3D(Int! x, Int! y, Int! z, Int! v) */

static METHOD knh__IArray_set3D(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	IArray *o = (IArray*)sfp[0].o;
	knh_darray_t *d = ((knh_darray_t*)o->ilist) - 1;
	size_t x = knh_array_index(ctx, p_int(sfp[1]), d->x);
	size_t y = knh_array_index(ctx, p_int(sfp[2]), d->y);
	size_t z = knh_array_index(ctx, p_int(sfp[3]), d->z);
	o->ilist[x + y * d->x + z * d->w] = sfp[4].ivalue;
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* [FArray] */

static
void knh_FArrayDim_init(Ctx *ctx, FArray *a, size_t x, size_t y, size_t z)
{
	knh_FArray_setDim(a, 1);
	a->flist = (knh_float_t*)knh_array_dmalloc(ctx, x, y, z, sizeof(knh_float_t));
	a->capacity = x * y * z;
	int i = 0;
	for(i = 0; i < a->capacity; i++) {
		a->flist[i] = 0.0;
	}
	a->size = a->capacity;
}

/* ------------------------------------------------------------------------ */
/* @method This! FArray.new:array2D(Int! x, Int! y) @Private */

static METHOD knh__FArray_new__array2D(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_FArrayDim_init(ctx, (FArray*)sfp[0].o, p_size(sfp[1]), p_size(sfp[2]), 1);
	KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ------------------------------------------------------------------------ */
/* @method This! FArray.new:array3D(Int! x, Int! y, Int! z) @Private */

static METHOD knh__FArray_new__array3D(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_FArrayDim_init(ctx, (FArray*)sfp[0].o, p_size(sfp[1]), p_size(sfp[2]), p_size(sfp[3]));
	KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ------------------------------------------------------------------------ */
/* @method Float! FArray.get2D(Int! x, Int! y) */

static METHOD knh__FArray_get2D(Ctx *ctx, knh_sfp_t *sfp)
{
	FArray *o = (FArray*)sfp[0].o;
	knh_darray_t *d = ((knh_darray_t*)o->flist) - 1;
	size_t x = knh_array_index(ctx, p_int(sfp[1]), d->x);
	size_t y = knh_array_index(ctx, p_int(sfp[2]), d->y);
	KNH_RETURN_Float(ctx, sfp, o->flist[x + y * d->x]);
}

/* ------------------------------------------------------------------------ */
/* @method Float! FArray.get3D(Int! x, Int! y, Int! z) */

static METHOD knh__FArray_get3D(Ctx *ctx, knh_sfp_t *sfp)
{
	FArray *o = (FArray*)sfp[0].o;
	knh_darray_t *d = ((knh_darray_t*)o->flist) - 1;
	size_t x = knh_array_index(ctx, p_int(sfp[1]), d->x);
	size_t y = knh_array_index(ctx, p_int(sfp[2]), d->y);
	size_t z = knh_array_index(ctx, p_int(sfp[3]), d->z);
	KNH_RETURN_Float(ctx, sfp, o->flist[x + y * d->x + z * d->w]);
}

/* ------------------------------------------------------------------------ */
/* @method void FArray.set2D(Int! x, Int! y, Float! v) */

static METHOD knh__FArray_set2D(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	FArray *o = (FArray*)sfp[0].o;
	knh_darray_t *d = ((knh_darray_t*)o->flist) - 1;
	size_t x = knh_array_index(ctx, p_int(sfp[1]), d->x);
	size_t y = knh_array_index(ctx, p_int(sfp[2]), d->y);
	o->flist[x + y * d->x] = sfp[3].fvalue;
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void FArray.set3D(Int! x, Int! y, Int! z, Float! v) */

static METHOD knh__FArray_set3D(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	FArray *o = (FArray*)sfp[0].o;
	knh_darray_t *d = ((knh_darray_t*)o->flist) - 1;
	size_t x = knh_array_index(ctx, p_int(sfp[1]), d->x);
	size_t y = knh_array_index(ctx, p_int(sfp[2]), d->y);
	size_t z = knh_array_index(ctx, p_int(sfp[3]), d->z);
	o->flist[x + y * d->x + z * d->w] = sfp[4].fvalue;
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */

#endif/*KNH_CC_METHODAPI*/


#ifdef __cplusplus
}
#endif
