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

/* ------------------------------------------------------------------------ */
/* [new] */

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] This! Object.new:init(Any value) @VARARGS */

static METHOD knh__Object_new__init(Ctx *ctx, knh_sfp_t *sfp)
{
	Object *o = sfp[0].o;
//	knh_class_t cid = knh_Object_cid(o);
//	knh_sfp_t *v = sfp + 1;
//	int ac = knh_stack_argc(ctx, v);
//	size_t i;
//	for(i = 0; i < ac; i+= 2) {
//		if(IS_bString(v[i].s)) {
			TODO();
//			knh_fieldn_t fn = knh_tName_get_fnq(ctx, knh_String_tobytes(v[i].s), FIELDN_NONAME);
//			if(fn == FIELDN_NONAME) continue;
//			knh_index_t idx = knh_Class_queryField(ctx, cid, fn);
//			if(idx == -1) continue;
//			knh_cfield_t *cf = knh_Class_fieldAt(ctx, cid, idx);
//			knh_type_t type = knh_pmztype_totype(ctx, cf->type, cid);
//			DBG2_P("[%d] %s%s %s", (int)idx, TYPEQN(type), FIELDN(fn));
//			KNH_SETv(ctx, KNH_FIELDn(o, idx), knh_Object_opAs__type(ctx, v[i+1].o, type, KNH_FIELDn(o,idx)));
//		}
//	}
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* [Bytes] */
/* @method Bytes! Bytes.new(Int init) */

static METHOD knh__Bytes_new(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *o = (Bytes*)sfp[0].o;
	size_t init = IS_NULL(sfp[1].o) ? 0 : knh_bytes_newsize(p_size(sfp[1]));
	KNH_ASSERT(o->capacity == 0);
	if(init > 0) {
	  o->buf = (knh_uchar_t*)KNH_MALLOC(ctx, init);
		o->capacity = init;
		knh_bzero(o->buf, init);
	}
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* [Array] */
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
	knh_intptr_t init = (knh_intptr_t)sfp[1].ivalue;
	if(init >= 0 && init == sfp[1].ivalue) {
		knh_class_t p1 = ctx->share->ClassTable[knh_Object_cid(o)].p1;
		Object *v = knh_getClassDefaultValue(ctx, p1);
		knh_Array_grow(ctx, o, init, v);
		o->size = init;
	}
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] This! Array.new:init(T1 value) @VARARGS */

static METHOD knh__Array_new__init(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	knh_sfp_t *v = sfp + 1;
	int i, ac = knh_stack_argc(ctx, v);
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
	int i, ac = knh_stack_argc(ctx, v);
	if(ac > 0) {
		knh_IArray_grow(ctx, o, ac, 0);
	}
	for(i = 0; i < ac; i++) {
		knh_IArray_add(ctx, o, v[i].ivalue);
	}
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] This! IArray.new:range(Int! start, Int! end, Int isInclusive) @VARARGS */

static METHOD knh__IArray_new__range(Ctx *ctx, knh_sfp_t *sfp)
{
	IArray *o = (IArray*)sfp[0].o;
	knh_int_t s = sfp[1].ivalue;
	knh_int_t e = sfp[2].ivalue;
	if(e > s) {
		s = e;
		e = sfp[1].ivalue;
	}
	knh_IArray_grow(ctx, o, e - s + 1, 0);
	for(; s < e; s++) {
		knh_IArray_add(ctx, o, s);
	}
	if(IS_NULL(sfp[3].o) || sfp[3].ivalue != 0) {
		knh_IArray_add(ctx, o, e);
	}
	KNH_RETURN(ctx, sfp, o);
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
	int i, ac = knh_stack_argc(ctx, v);
	if(ac > 0) {
		knh_FArray_grow(ctx, o, ac, 0.0);
	}
	for(i = 0; i < ac; i++) {
		knh_FArray_add(ctx, o, v[i].fvalue);
	}
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* [new] */



#endif/* KNH_CC_METHODAPI*/

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
