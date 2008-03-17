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
/* [constructor] */

/* ------------------------------------------------------------------------ */
/* @method Array! Array.new(Int init) */

Array* knh_Array_new(Ctx *ctx, Array *b, knh_int_t init)
{
	if(init > 0) {
		if(init > b->capacity) {
			knh_Array_resize(ctx, b, (size_t)init);
		}
	}
	return b;
}

/* ------------------------------------------------------------------------ */
/* @method Array! Array.new::array(Int init, Any value) */

Array* knh_Array_new__array(Ctx *ctx, Array *b, knh_int_t init, Any *value)
{
	if(init > 0) {
		if(init > b->capacity) {
			knh_Array_resize(ctx, b, (size_t)init);
		}
		int i;
		for(i = 0; i < init; i++) {
			knh_Array_add__fast(ctx, b, value);
		}
	}
		
	return b;
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] Array! Array.new::init(Any value) */

Array* knh_Array_new__init(Ctx *ctx, Array *b, knh_vargc_t n, Any **v)
{
	if(n > b->capacity) {
		knh_Array_resize(ctx, b, (size_t)n);
	}
	knh_int_t i;
	for(i = 0; i < n; i++) {
		knh_Array_add__fast(ctx, b, v[i]);
	}
	return b;
}

/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [method] */

/* ------------------------------------------------------------------------ */
/* @method Any Array.get::fast(Int! index) */

INLINE
Any* knh_Array_get__fast(Array *b, size_t index)
{
	KNH_FAST_ASSERT(index < b->size);
	return b->list[index];
}

/* ------------------------------------------------------------------------ */
/* @method void Array.set::fast(Int! index, Any value) */

#define _knh_Array_setn(ctx,b,n,v) knh_Array_set__fast(ctx,b,n,v)

INLINE
void knh_Array_set__fast(Ctx *ctx, Array *b, size_t index, Object *value)
{
	KNH_FAST_ASSERT(index < b->size);
	KNH_SETv(ctx, b->list[index], value);
}

/* ------------------------------------------------------------------------ */

/* @method Any Array.get(Int! index) */

INLINE
Any* knh_Array_get(Array *b, knh_int_t index)
{
	size_t n2 = knh_array_index(index, b->size);
	return b->list[n2];
}

/* ------------------------------------------------------------------------ */

/* @method void Array.set(Int! index, Any value) */

INLINE
void knh_Array_set(Ctx *ctx, Array *b, knh_int_t index, Any *value)
{
	size_t n2 = knh_array_index(index, b->size);
	KNH_SETv(ctx, b->list[n2], value);
}

/* ------------------------------------------------------------------------ */

/* ======================================================================== */
/* [mapping] */

/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
