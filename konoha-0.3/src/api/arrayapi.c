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

#ifdef KNH_CC_METHODAPI

/* ======================================================================== */
/* [new] */

/* ------------------------------------------------------------------------ */
/* @method This! Array.new(Int init) */

static METHOD knh__Array_new(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	int init = IS_NULL(sfp[1].o) ? KNH_ARRAY_INITSIZE: p_int(sfp[1]);
	if(init > 0) {
		knh_Array_grow(ctx, o, init, KNH_NULL);
	}
	o->size = 0;
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* @method This! Array.new:array(Int! n) */

static METHOD knh__Array_new__array(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	int init = p_int(sfp[1]);
	if(init > 0) {
		knh_class_t p1 = ctx->share->ClassTable[knh_Object_cid(o)].p1;
		Object *v = konoha_getClassDefaultValue(ctx, p1);
		knh_Array_grow(ctx, o, init, v);
		o->size = init;
	}
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] This! Array.new:init(Any1 value) @VARARGS */

static METHOD knh__Array_new__init(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	knh_sfp_t *v = sfp + 1;
	int i, ac = knh_sfp_argc(ctx, v);
	if(ac > 0) {
		knh_Array_grow(ctx, o, ac, KNH_NULL);
	}
	for(i = 0; i < ac; i++) {
		knh_sfp_boxing(ctx, v + i);
		knh_Array_add(ctx, o, v[i].o);
	}
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* [IArray] */

static
void knh_IArray_grow(Ctx *ctx, IArray *a, size_t newsize, knh_int_t v)
{
	KNH_ASSERT(a->capacity < newsize);
	size_t i;
	if(newsize == 0) newsize = (KNH_FASTMALLOC_SIZE / sizeof(knh_int_t));
	knh_int_t *newa = (knh_int_t*)KNH_MALLOC(ctx, sizeof(knh_int_t) * newsize);
	if(a->capacity > 0) {
		knh_memcpy(newa, a->ilist, sizeof(knh_int_t) * a->capacity);
	}
	for(i = a->capacity; i < newsize; i++) {
		newa[i] =  v;
	}
	knh_int_t *olda = a->ilist;
	a->ilist = newa;
	if(a->capacity > 0) {
		KNH_FREE(ctx, olda, sizeof(knh_int_t) * a->capacity);
	}
	a->capacity = newsize;
}

/* ------------------------------------------------------------------------ */

static
void knh_IArray_add(Ctx *ctx, IArray *o, knh_int_t value)
{
	if(o->size == o->capacity) {
		knh_IArray_grow(ctx, o, knh_array_newsize(o->capacity * 2, sizeof(knh_int_t)), 0);
	}
	DBG2_ASSERT(o->size < o->capacity);
	o->ilist[o->size] = value;
	o->size++;
}

/* ------------------------------------------------------------------------ */
/* @method This! IArray.new(Int init) */

static METHOD knh__IArray_new(Ctx *ctx, knh_sfp_t *sfp)
{
	IArray *o = (IArray*)sfp[0].o;
	int init = IS_NULL(sfp[1].o) ? KNH_IARRAY_INITSIZE: p_int(sfp[1]);
	if(init > 0) {
		knh_IArray_grow(ctx, o, init, 0);
	}
	o->size = 0;
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* @method This! IArray.new:array(Int! n) */

static METHOD knh__IArray_new__array(Ctx *ctx, knh_sfp_t *sfp)
{
	IArray *o = (IArray*)sfp[0].o;
	int init = p_int(sfp[1]);
	if(init > 0) {
		knh_IArray_grow(ctx, o, init, 0);
		o->size = init;
	}
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] This! IArray.new:init(Int! value) @VARARGS */

static METHOD knh__IArray_new__init(Ctx *ctx, knh_sfp_t *sfp)
{
	IArray *o = (IArray*)sfp[0].o;
	knh_sfp_t *v = sfp + 1;
	int i, ac = knh_sfp_argc(ctx, v);
	if(ac > 0) {
		knh_IArray_grow(ctx, o, ac, 0);
	}
	for(i = 0; i < ac; i++) {
		knh_IArray_add(ctx, o, v[i].ivalue);
	}
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* [FArray] */

static
void knh_FArray_grow(Ctx *ctx, FArray *a, size_t newsize, knh_float_t v)
{
	KNH_ASSERT(a->capacity < newsize);
	size_t i;
	if(newsize == 0) newsize = (KNH_FASTMALLOC_SIZE / sizeof(knh_float_t));
	knh_float_t *newa = (knh_float_t*)KNH_MALLOC(ctx, (sizeof(knh_float_t)) * newsize);
	if(a->capacity > 0) {
		knh_memcpy(newa, a->flist, sizeof(knh_float_t) * a->capacity);
	}
	for(i = a->capacity; i < newsize; i++) {
		newa[i] =  v;
	}
	knh_float_t *olda = a->flist;
	a->flist = newa;
	if(a->capacity > 0) {
		KNH_FREE(ctx, olda, sizeof(knh_float_t) * a->capacity);
	}
	a->capacity = newsize;
}

/* ------------------------------------------------------------------------ */

static
void knh_FArray_add(Ctx *ctx, FArray *o, knh_float_t value)
{
	if(o->size == o->capacity) {
		knh_FArray_grow(ctx, o, knh_array_newsize(o->capacity * 2, sizeof(knh_float_t)), 0.0);
	}
	DBG2_ASSERT(o->size < o->capacity);
	o->flist[o->size] = value;
	o->size++;
}

/* ------------------------------------------------------------------------ */
/* @method This! FArray.new(Int init) */

static METHOD knh__FArray_new(Ctx *ctx, knh_sfp_t *sfp)
{
	FArray *o = (FArray*)sfp[0].o;
	int init = IS_NULL(sfp[1].o) ? KNH_FARRAY_INITSIZE: p_int(sfp[1]);
	if(init > 0) {
		knh_FArray_grow(ctx, o, init, 0.0);
	}
	o->size = 0;
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* @method This! FArray.new:array(Int! n) */

static METHOD knh__FArray_new__array(Ctx *ctx, knh_sfp_t *sfp)
{
	FArray *o = (FArray*)sfp[0].o;
	int init = p_int(sfp[1]);
	if(init > 0) {
		knh_FArray_grow(ctx, o, init, 0.0);
		o->size = init;
	}
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] This! FArray.new:init(Float! value) @VARARGS */

static METHOD knh__FArray_new__init(Ctx *ctx, knh_sfp_t *sfp)
{
	FArray *o = (FArray*)sfp[0].o;
	knh_sfp_t *v = sfp + 1;
	int i, ac = knh_sfp_argc(ctx, v);
	if(ac > 0) {
		knh_FArray_grow(ctx, o, ac, 0.0);
	}
	for(i = 0; i < ac; i++) {
		knh_FArray_add(ctx, o, v[i].fvalue);
	}
	KNH_RETURN(ctx, sfp, o);
}

/* ======================================================================== */
/* [add] */

/* ------------------------------------------------------------------------ */
/* @method void Array.add(Any1! value) */

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
/* @method[VARARGS] void Array.opLshift(Any1! v) */

static METHOD knh__Array_opLshift(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {
		Array *o = (Array*)sfp[0].o;
		knh_sfp_t *v = sfp + 1;
		int i, ac = knh_sfp_argc(ctx, v);
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
	int i, ac = knh_sfp_argc(ctx, v);
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
	int i, ac = knh_sfp_argc(ctx, v);
	for(i = 0; i < ac; i++) {
		knh_FArray_add(ctx, o, v[i].fvalue);
	}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ======================================================================== */
/* @method Int! Array.getSize() */
/* @method Int! IArray.getSize() */
/* @method Int! FArray.getSize() */

static METHOD knh__Array_getSize(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	KNH_RETURN_Int(ctx, sfp, o->size);
}

/* ------------------------------------------------------------------------ */
/* @method Any1! Array.get(Int! n) */

static METHOD knh__Array_get(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	size_t n2 = knh_array_index(ctx, p_int(sfp[1]), o->size);
	KNH_RETURN(ctx, sfp, o->list[n2]);
}

/* ------------------------------------------------------------------------ */
/* @method Int! IArray.get(Int! n) */

static METHOD knh__IArray_get(Ctx *ctx, knh_sfp_t *sfp)
{
	IArray *o = (IArray*)sfp[0].o;
	size_t n2 = knh_array_index(ctx, p_int(sfp[1]), o->size);
	KNH_RETURN_Int(ctx, sfp, o->ilist[n2]);
}

/* ------------------------------------------------------------------------ */
/* @method Float! FArray.get(Int! n) */

static METHOD knh__FArray_get(Ctx *ctx, knh_sfp_t *sfp)
{
	FArray *o = (FArray*)sfp[0].o;
	size_t n2 = knh_array_index(ctx, p_int(sfp[1]), o->size);
	KNH_RETURN_Float(ctx, sfp, o->flist[n2]);
}

/* ------------------------------------------------------------------------ */
/* @method void Array.set(Int! n, Any1! v) */

static METHOD knh__Array_set(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	Array *o = (Array*)sfp[0].o;
	size_t n2 = knh_array_index(ctx, p_int(sfp[1]), o->size);
	knh_sfp_boxing(ctx, sfp + 2);
	KNH_SETv(ctx, o->list[n2], sfp[2].o);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void IArray.set(Int! n, Int! v) */

static METHOD knh__IArray_set(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	IArray *o = (IArray*)sfp[0].o;
	size_t n2 = knh_array_index(ctx, p_int(sfp[1]), o->size);
	o->ilist[n2] = sfp[2].ivalue;
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void FArray.set(Int! n, Float! v) */

static METHOD knh__FArray_set(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	FArray *o = (FArray*)sfp[0].o;
	size_t n2 = knh_array_index(ctx, p_int(sfp[1]), o->size);
	o->flist[n2] = sfp[2].fvalue;
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void Array.setAll(Any1 v) */

static METHOD knh__Array_setAll(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
	Array *o = (Array*)sfp[0].o;
	size_t i;
	knh_sfp_boxing(ctx, sfp + 1);
	for(i = 0; i < o->size; i++) {
		KNH_SETv(ctx, o->list[i], sfp[1].o);
	}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */

static
Array *new_Array__subset(Ctx *ctx, Array *a, size_t s, size_t e)
{
	Array *newa = (Array*)new_Object_init(ctx, a->h.flag, a->h.cid, 0);
	if(e < s) {
		size_t t = s; s = e; e = t;
	}
	if(s < e) {
		KNH_ASSERT(e <= a->size);
		size_t newsize = e - s;
		newa->list = (Object**)KNH_MALLOC(ctx, newsize * sizeof(Object*));
		knh_memcpy(newa->list, &a->list[s], newsize * sizeof(Object*));
#ifdef KNH_USING_RCGC
		size_t i;
		for(i = 0; i < newsize; i++) {
			knh_Object_RCinc(newa->list[i]);
		}
#endif
		newa->capacity = newsize;
		newa->size = newsize;
	}
	return newa;
}

/* ------------------------------------------------------------------------ */
/* @method This! Array.opSubset(Int s, Int e) @Debug */

static METHOD knh__Array_opSubset(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	size_t s = IS_NULL(sfp[1].o) ? 0 : knh_array_index(ctx, p_int(sfp[1]), o->size);
	size_t e = IS_NULL(sfp[2].o) ? (o->size) : knh_array_index(ctx, p_int(sfp[2]), o->size);
	KNH_RETURN(ctx, sfp, new_Array__subset(ctx, o, s, e));
}

/* ------------------------------------------------------------------------ */
/* @method This! Array.opSubsete(Int s, Int e) @Debug */

static METHOD knh__Array_opSubsete(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	size_t s = IS_NULL(sfp[1].o) ? 0 : knh_array_index(ctx, p_int(sfp[1]), o->size);
	size_t e = IS_NULL(sfp[2].o) ? (o->size) : knh_array_index(ctx, p_int(sfp[2]) + 1, o->size) ;
	KNH_RETURN(ctx, sfp, new_Array__subset(ctx, o, s, e));
}

/* ------------------------------------------------------------------------ */
/* @method This! Array.opOffset(Int s, Int offset) @Debug */

static METHOD knh__Array_opOffset(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	size_t s = IS_NULL(sfp[1].o) ? 0 : knh_array_index(ctx, p_int(sfp[1]), o->size);
	knh_intptr_t e = IS_NULL(sfp[1].o) ? o->size : s + p_int(sfp[2]);
	if(e > o->size) e = o->size; else if(e < 0) e = 0;
	KNH_RETURN(ctx, sfp, new_Array__subset(ctx, o, s, e));
}

/* ======================================================================== */

/* ------------------------------------------------------------------------ */
/* @method void Array.insert(Int! n, Any1 v) */

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
/* @method Any1 Array.pop() */

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
/* @method Int! Array.indexOf(Any1 v) */

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
/* @method Int! Array.lastIndexOf(Any1 v) */

static METHOD knh__Array_lastIndexOf(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	knh_sfp_boxing(ctx, sfp + 1);
	size_t i;
	for(i = o->size - 1; i >= 0; i--) {
		if(knh_Object_compareTo(ctx, o->list[i], sfp[1].o) == 0) {
			KNH_RETURN_Int(ctx, sfp, i);
		}
	}
	KNH_RETURN_Int(ctx, sfp, -1); // Not Found
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Array.opHas(Any1 v) */

static METHOD knh__Array_opHas(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	knh_sfp_boxing(ctx, sfp + 1);
	size_t i;
	for(i = 0; i < o->size; i++) {
		if(knh_Object_compareTo(ctx, o->list[i], sfp[1].o) == 0) {
			KNH_RETURN_Boolean(ctx, sfp, 1);
		}
	}
	KNH_RETURN_Boolean(ctx, sfp, 0); // Not Found
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
		size_t n = o->size - i;
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
		size_t n = o->size - i;
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
		size_t n = o->size - i;
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

/* ------------------------------------------------------------------------ */
/* @method void Array.%k(OutputStream w, String m) */

void knh_Array__k(Ctx *ctx, Array *o, OutputStream *w, String *m)
{
	knh_putc(ctx, w, '[');
	size_t c;
	for(c = 0; c < o->size; c++) {
		if(c > 0) {
			knh_write_delim(ctx,w);
		}
		knh_format(ctx, w, METHODN__k, o->list[c], KNH_NULL);
	}
	knh_putc(ctx, w, ']');
}

/* ======================================================================== */
/* [mapping] */

static
ITRNEXT knh_Array_var_next(Ctx *ctx, knh_sfp_t *sfp, int n)
{
	Array *o = (Array*)DP(sfp[0].it)->source;
	KNH_ASSERT(IS_bArray(o));
	size_t pos = DP(sfp[0].it)->pos;
	while(pos < o->size) {
		if(IS_NOTNULL(o->list[pos])) {
			DP(sfp[0].it)->pos = pos+1;
			KNH_ITRNEXT(ctx, sfp, n, o->list[pos]);
		}
		pos++;
	}
	KNH_ITREND(ctx, sfp, n);
}

/* ------------------------------------------------------------------------ */
/* @map Array Iterator! */

MAPPER knh_Array_Iterator(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_MAPPED(ctx, sfp,
		new_Iterator(ctx, ctx->share->ClassTable[(sfp[0].o)->h.cid].p1, sfp[0].o, knh_Array_var_next));
}

/* ------------------------------------------------------------------------ */
/* @method Any1.. Array.opItr() */

static METHOD knh__Array_opItr(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	KNH_RETURN(ctx, sfp, new_Iterator(ctx, ctx->share->ClassTable[o->h.cid].p1, UP(o), knh_Array_var_next));
}

/* ------------------------------------------------------------------------ */
/* @map Iterator Array! */

MAPPER knh_Iterator_Array(Ctx *ctx, knh_sfp_t *sfp)
{
	Iterator *it = sfp[0].it;
	Array *a = new_Array(ctx, ctx->share->ClassTable[it->h.cid].p1, 0);
	it->fnext_1(ctx, sfp, 1);
	while(HAS_ITRNEXT(sfp[1].o)) {
		knh_Array_add(ctx, a, sfp[1].o);
		it->fnext_1(ctx, sfp, 1);
	}
	KNH_MAPPED(ctx, sfp, a);
}

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
	Object *v = (p1 == CLASS_Any) ? KNH_NULL : konoha_getClassDefaultValue(ctx, p1);
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
/* @method Any1 Array.get2D(Int! x, Int! y) */

static METHOD knh__Array_get2D(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	knh_darray_t *d = ((knh_darray_t*)o->list) - 1;
	size_t x = knh_array_index(ctx, p_int(sfp[1]), d->x);
	size_t y = knh_array_index(ctx, p_int(sfp[2]), d->y);
	KNH_RETURN(ctx, sfp, o->list[x + y * d->x]);
}

/* ------------------------------------------------------------------------ */
/* @method Any1 Array.get3D(Int! x, Int! y, Int! z) */

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
/* @method void Array.set2D(Int! x, Int! y, Any1 v) */

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
/* @method void Array.set3D(Int! x, Int! y, Int! z, Any1 v) */

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
/* [Iterator] */

/* ------------------------------------------------------------------------ */
/* @method void Iterator.%k(OutputStream w, String m) */

void knh_Iterator__k(Ctx *ctx, Iterator *o, OutputStream *w, String *m)
{
	size_t c = 0;
	knh_sfp_t *lsfp = KNH_LOCAL(ctx);
	KNH_MOV(ctx, lsfp[0].o, o);
	KNH_SHIFTESP(ctx, lsfp+3);
	o->fnext_1(ctx, lsfp, 2);
	while(HAS_ITRNEXT(lsfp[2].o)) {
		if(c > 0) {
			knh_write_EOL(ctx,w);
		}
		KNH_SHIFTESP(ctx, lsfp+1);
		knh_esp1_format(ctx, METHODN__k, w, KNH_NULL);
		c++;
		KNH_SHIFTESP(ctx, lsfp+3);
		o->fnext_1(ctx, lsfp, 2);
	}
}

/* ------------------------------------------------------------------------ */

#endif/*KNH_CC_METHODAPI*/


#ifdef __cplusplus
}
#endif
