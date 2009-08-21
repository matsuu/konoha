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
/* [Common] */

/* ------------------------------------------------------------------------ */
/* @method[NULLBASE] Int! Object.opAddr() */

static METHOD knh__Object_opAddr(Ctx *ctx, knh_sfp_t *sfp)
{
	void *p = NULL;
	if(IS_bInt(sfp[0].o) || IS_bFloat(sfp[0].o)) {
		p = (void*)(&sfp[0] + sizeof(void*));
	}
	else if(IS_Boolean(sfp[0].o)) {
		p = (sfp[0].bvalue) ? (void*)(KNH_TRUE) : (void*)(KNH_FALSE);
	}
	else if(IS_NOTNULL(sfp[0].o)) {
		p = (void*)sfp[0].o;
	}
	KNH_RETURN_Int(ctx, sfp, (knh_intptr_t)p);
}


/* ------------------------------------------------------------------------ */

static void knh_stack_utest(Ctx *ctx, knh_sfp_t *sfp, int result, Object *o)
{
	if(result) {
		knh_printf(ctx, KNH_STDERR, "[PASS]\n");
	}
	else {
		knh_printf(ctx, KNH_STDERR, "[FAILED] %O\n", o);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[NULLBASE] Any Object.opTest(Any it) @Hidden */

static METHOD knh__Object_opTest(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_stack_utest(ctx, sfp, knh_Object_compareTo(ctx, sfp[0].o, sfp[1].o) != 0, sfp[1].o);
	KNH_RETURN(ctx, sfp, sfp[1].o);
}

/* ------------------------------------------------------------------------ */
/* @method Any Boolean.opTest(Any it) @Hidden */

static METHOD knh__Boolean_opTest(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_stack_utest(ctx, sfp, sfp[0].bvalue, sfp[1].o);
	KNH_RETURN(ctx, sfp, sfp[1].o);
}

/* ------------------------------------------------------------------------ */
/* @method Any Exception.opTest(Any it) @Hidden */

static METHOD knh__Exception_opTest(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_ASSERT(IS_bString(sfp[0].s));
	if(IS_Exception(sfp[1].o)) {
		knh_expt_t eid =  (IS_Exception(sfp[0].o)) ?
			DP(sfp[0].e)->eid : knh_geteid(ctx, knh_String_tobytes(sfp[0].s), EXPT_newid);
		if(knh_expt_isa(ctx, DP(sfp[1].e)->eid, eid)) {
			knh_stack_utest(ctx, sfp, 1, sfp[1].o);
			KNH_RETURN(ctx, sfp, KNH_NULL);
		}
		knh_throwException(ctx, sfp[1].e, NULL, 0);
	}
	knh_stack_utest(ctx, sfp, 0, sfp[1].o);
	KNH_RETURN(ctx, sfp, sfp[1].o);
}

/* ======================================================================== */
/* [Comparator] */

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.opEq(Any value) */

static METHOD knh__Object_opEq(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_compareTo(ctx, sfp[0].o, sfp[1].o) == 0);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.opNeq(Any value) */

static METHOD knh__Object_opNeq(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_compareTo(ctx, sfp[0].o, sfp[1].o) != 0);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.opLt(Any value) */

static METHOD knh__Object_opLt(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_compareTo(ctx, sfp[0].o, sfp[1].o) < 0);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.opLte(Any value) */

static METHOD knh__Object_opLte(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_compareTo(ctx, sfp[0].o, sfp[1].o) <= 0);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.opGt(Any value) */

static METHOD knh__Object_opGt(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_compareTo(ctx, sfp[0].o, sfp[1].o) > 0);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.opGte(Any value) */

static METHOD knh__Object_opGte(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_compareTo(ctx, sfp[0].o, sfp[1].o) >= 0);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Int.opEq(Int! value) */

static METHOD knh__Int_opEq(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, p_integer(sfp[0]) == p_integer(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Int.opNeq(Int! value) */

static METHOD knh__Int_opNeq(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, p_integer(sfp[0]) != p_integer(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! Int.opLt(Int! value) */

static METHOD knh__Int_opLt(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, p_integer(sfp[0]) < p_integer(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! Int.opLte(Int! value) */

static METHOD knh__Int_opLte(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, p_integer(sfp[0]) <= p_integer(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! Int.opGt(Int! value) */

static METHOD knh__Int_opGt(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, p_integer(sfp[0]) > p_integer(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! Int.opGte(Int! value) */

static METHOD knh__Int_opGte(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, p_integer(sfp[0]) >= p_integer(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Float.opEq(Float value) */

static METHOD knh__Float_opEq(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, p_float(sfp[0]) == p_float(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Float.opNeq(Float value) */

static METHOD knh__Float_opNeq(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, p_float(sfp[0]) != p_float(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! Float.opLt(Float! value) */

static METHOD knh__Float_opLt(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, p_float(sfp[0]) < p_float(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! Float.opLte(Float! value) */

static METHOD knh__Float_opLte(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, p_float(sfp[0]) <= p_float(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! Float.opGt(Float! value) */

static METHOD knh__Float_opGt(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, p_float(sfp[0]) > p_float(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! Float.opGte(Float! value) */

static METHOD knh__Float_opGte(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, p_float(sfp[0]) >= p_float(sfp[1]));
}

/* ======================================================================== */
/* [Case] */

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.opCase(Any v) */

static METHOD knh__Object_opCase(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_compareTo(ctx, sfp[0].o, sfp[1].o) == 0);
}

/* ======================================================================== */
/* [Semantic Comparator] */

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! Object.opIs(Any v) */

static METHOD knh__Object_opIs(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_class_t scid = knh_Object_cid(sfp[0].o);
	knh_class_t tcid = knh_Object_cid(sfp[1].o);
	DBG2_P("Semantic Matching %s === %s", CLASSN(scid), CLASSN(tcid));
	if(scid == tcid) {
		knh__Object_opEq(ctx, sfp);
	}
	else if(IS_NULL(sfp[1].o)) {
		KNH_RETURN_Boolean(ctx, sfp, IS_NULL(sfp[0].o));
	}
	else {
		TODO_THROW(ctx);
		KNH_RETURN_Boolean(ctx, sfp, 0);
//		knh_sfp_t *lsfp = KNH_LOCAL(ctx);
//		KNH_LPUSH(ctx, sfp[1].o);
//		VM_MAP(ctx, scid);
//		KNH_SETv(ctx, sfp[1].o, ctx->esp[0].o);
//		KNH_LOCALBACK(ctx, lsfp);
//		if(IS_NULL(sfp[1].o)) {
//			KNH_RETURN_Boolean(ctx, sfp, 0);
//		}
//		else {
//			knh__Object_opEq(ctx, sfp);
//		}
	}
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! Object.opAs(Any o) */

static METHOD knh__Object_opAs(Ctx *ctx, knh_sfp_t *sfp)
{
	TODO_THROW(ctx);
	KNH_RETURN_Boolean(ctx, sfp, 0);
//	knh_class_t scid = knh_Object_cid(sfp[0].o);
//	knh_class_t tcid = (sfp[1].c)->cid;
//	if(scid == tcid) {
//		KNH_RETURN_Boolean(ctx, sfp, 1);
//	}
//	else {
//		TODO_THROW(ctx);
//		KNH_RETURN_Boolean(ctx, sfp, 0);
//	}
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! Object.opInTo(Class! c) */

static METHOD knh__Object_opInTo(Ctx *ctx, knh_sfp_t *sfp)
{
	TODO_THROW(ctx);
	KNH_RETURN_Boolean(ctx, sfp, 0);
}

/* ======================================================================== */
/* [Arithemetic] */

/* ------------------------------------------------------------------------ */
/* [Int] */
/* @method[CONST] Int! Int.opAdd(Int! v) */

static METHOD knh__Int_opAdd(Ctx *ctx, knh_sfp_t *sfp)
{
	//DBG2_P("<<%d + %d>>", (int)p_int(sfp[0]), (int)p_int(sfp[1]));
	KNH_RETURN_Int(ctx, sfp, p_integer(sfp[0]) + p_integer(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Int! Int.opNeg() */

static METHOD knh__Int_opNeg(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Int(ctx, sfp, -(p_integer(sfp[0])));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Int! Int.opSub(Int! n) */

static METHOD knh__Int_opSub(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Int(ctx, sfp, p_integer(sfp[0]) - p_integer(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Int! Int.opMul(Int! n) */

static METHOD knh__Int_opMul(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Int(ctx, sfp, p_integer(sfp[0]) * p_integer(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Int! Int.opDiv(Int! n) */

static METHOD knh__Int_opDiv(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_THROW_iZERODIV(p_integer(sfp[1]));
	KNH_RETURN_Int(ctx, sfp, p_integer(sfp[0]) / p_integer(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Int! Int.opMod(Int! n) */

static METHOD knh__Int_opMod(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_THROW_iZERODIV(p_integer(sfp[1]));
	KNH_RETURN_Int(ctx, sfp, p_integer(sfp[0]) % p_integer(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* [Float] */
/* @method[CONST] Float! Float.opAdd(Float! v) */

static METHOD knh__Float_opAdd(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Float(ctx, sfp, p_float(sfp[0]) + p_float(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Float! Float.opNeg() */

static METHOD knh__Float_opNeg(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Float(ctx, sfp, -(p_float(sfp[0])));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Float! Float.opSub(Float! n) */

static METHOD knh__Float_opSub(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Float(ctx, sfp, p_float(sfp[0]) - p_float(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Float! Float.opMul(Float! n) */

static METHOD knh__Float_opMul(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Float(ctx, sfp, p_float(sfp[0]) * p_float(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Float! Float.opDiv(Float! n) */

static METHOD knh__Float_opDiv(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_THROW_fZERODIV(p_float(sfp[1]));
	KNH_RETURN_Float(ctx, sfp, p_float(sfp[0]) / p_float(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* [Any] */
/* @method Any Any.opAdd(Any v) */

METHOD knh__Any_opAdd(Ctx *ctx, knh_sfp_t *sfp)
{
	TODO_THROW(ctx);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

/* ------------------------------------------------------------------------ */
/* @method Any Any.opNeg() */

METHOD knh__Any_opNeg(Ctx *ctx, knh_sfp_t *sfp)
{
	TODO_THROW(ctx);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

/* ------------------------------------------------------------------------ */
/* @method Any Any.opSub(Any n) */

METHOD knh__Any_opSub(Ctx *ctx, knh_sfp_t *sfp)
{
	TODO_THROW(ctx);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

/* ------------------------------------------------------------------------ */
/* @method Any Any.opMul(Any n) */

METHOD knh__Any_opMul(Ctx *ctx, knh_sfp_t *sfp)
{
	TODO_THROW(ctx);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

/* ------------------------------------------------------------------------ */
/* @method Any Any.opDiv(Any n) */

METHOD knh__Any_opDiv(Ctx *ctx, knh_sfp_t *sfp)
{
	TODO_THROW(ctx);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

/* ------------------------------------------------------------------------ */
/* @method Any Any.opMod(Any n) */

METHOD knh__Any_opMod(Ctx *ctx, knh_sfp_t *sfp)
{
	TODO_THROW(ctx);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

/* ======================================================================== */
/* [Logical] */

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! Boolean.opNot() */

static METHOD knh__Boolean_opNot(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(p_bool(sfp[0])));
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS|CONST] Int! Int.opLand(Int! v) */

static METHOD knh__Int_opLand(Ctx *ctx, knh_sfp_t *sfp)
{
	int ac = knh_stack_argc(ctx, sfp);
	knh_int_t n = p_integer(sfp[0]);
	size_t i;
	for(i = 1; i < ac; i++) {
		n = n & p_integer(sfp[i]);
	}
	KNH_RETURN_Int(ctx, sfp, n);
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS|CONST] Int! Int.opLor(Int! v) */

static METHOD knh__Int_opLor(Ctx *ctx, knh_sfp_t *sfp)
{
	int ac = knh_stack_argc(ctx, sfp);
	knh_int_t n = p_integer(sfp[0]);
	size_t i;
	for(i = 1; i < ac; i++) {
		n = n | p_integer(sfp[i]);
	}
	KNH_RETURN_Int(ctx, sfp, n);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Int! Int.opXor(Int! n) */

static METHOD knh__Int_opXor(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Int(ctx, sfp, p_integer(sfp[0]) ^ p_integer(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Int! Int.opLnot() */

static METHOD knh__Int_opLnot(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Int(ctx, sfp, ~(p_integer(sfp[0])));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Int! Int.opLshift(Int! n) */

static METHOD knh__Int_opLshift(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Int(ctx, sfp, p_integer(sfp[0]) << p_integer(sfp[1]));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Int! Int.opRshift(Int! n) */

static METHOD knh__Int_opRshift(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Int(ctx, sfp, p_integer(sfp[0]) >> p_integer(sfp[1]));
}



/* ======================================================================== */
/* [Enum] */


/* ------------------------------------------------------------------------ */
/* @method[CONST] Int! Int.opNext() */

static METHOD knh__Int_opNext(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Int(ctx, sfp, p_integer(sfp[0])+1);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Int! Int.opPrev() */

static METHOD knh__Int_opPrev(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Int(ctx, sfp, p_integer(sfp[0])-1);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Float! Float.opNext() */

static METHOD knh__Float_opNext(Ctx *ctx, knh_sfp_t *sfp)
{
  #ifndef KONOHA_ON_LKM
	KNH_RETURN_Float(ctx, sfp, (p_float(sfp[0]))+1.0);
  #else
	KNH_RETURN_Float(ctx, sfp, (p_float(sfp[0]))+1);
  #endif
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Float! Float.opPrev() */

static METHOD knh__Float_opPrev(Ctx *ctx, knh_sfp_t *sfp)
{
#ifndef KONOHA_ON_LKM
	KNH_RETURN_Float(ctx, sfp, (p_float(sfp[0]))-1.0);
#else
	KNH_RETURN_Float(ctx, sfp, (p_float(sfp[0])) - 1);
#endif
}

/* ======================================================================== */
/* [getSize] */

/* ------------------------------------------------------------------------ */
/* @method[NULLBASE|CONST] Int! Int.getSize() */

static METHOD knh__Int_getSize(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_NULL(sfp[0].o)) {
		KNH_RETURN_Int(ctx, sfp, 0);
	}
	else {
		knh_int_t n = p_integer(sfp[0]);
		if(n >= 0) {
			KNH_RETURN_Int(ctx, sfp, n);
		}
		else {
			KNH_RETURN_Int(ctx, sfp, -(n));
		}
	}
}

/* ------------------------------------------------------------------------ */
/* @method[NULLBASE|CONST] Int! Float.getSize() */

static METHOD knh__Float_getSize(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_NULL(sfp[0].o)) {
		KNH_RETURN_Int(ctx, sfp, 0);
	}
	else {
		knh_uint_t n = (knh_uint_t)p_float(sfp[0]);
		KNH_RETURN_Int(ctx, sfp, n);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[NULLBASE] Int! Bytes.getSize() */

static METHOD knh__Bytes_getSize(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_NULL(sfp[0].o)) {
		KNH_RETURN_Int(ctx, sfp, 0);
	}
	else {
		Bytes *o = (Bytes*)sfp[0].o;
		KNH_RETURN_Int(ctx, sfp, o->size);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[NULLBASE] Int! Array.getSize() */
/* @method[NULLBASE] Int! IArray.getSize() */
/* @method[NULLBASE] Int! FArray.getSize() */

static METHOD knh__Array_getSize(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_NULL(sfp[0].o)) {
		KNH_RETURN_Int(ctx, sfp, 0);
	}
	else {
		Array *o = (Array*)sfp[0].o;
		KNH_RETURN_Int(ctx, sfp, o->size);
	}
}

/* ======================================================================== */
/* [opHas] */

/* ------------------------------------------------------------------------ */
/* @method Boolean! Array.opHas(T1 v) */

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
/* [get,set] */

/* ------------------------------------------------------------------------ */
/* @method Int! Bytes.get(Int! n) */

static METHOD knh__Bytes_get(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *o = (Bytes*)sfp[0].o;
	size_t n2 = knh_array_index(ctx, p_int(sfp[1]), o->size);
	KNH_RETURN_Int(ctx, sfp, o->buf[n2]);
}

/* ------------------------------------------------------------------------ */
/* @method void Bytes.set(Int! n, Int! c) */

static METHOD knh__Bytes_set(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *o = (Bytes*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		size_t n2 = knh_array_index(ctx, p_int(sfp[1]), o->size);
		o->buf[n2] = (knh_uchar_t)p_int(sfp[2]);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void Bytes.setAll(Int! c) */

static METHOD knh__Bytes_setAll(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *o = (Bytes*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		size_t i, n = p_int(sfp[1]);
		for(i = 0; i < o->size; i++) {
			o->buf[i] = n;
		}
	}
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* @method T1! Array.get(Int! n) */

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
/* @method void Array.set(Int! n, T1! v) */

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
/* @method void Array.setAll(T1 v) */

static METHOD knh__Array_setAll(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {
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
/* @method void IArray.setAll(Int! v) */

static METHOD knh__IArray_setAll(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {
		IArray *o = (IArray*)sfp[0].o;
		size_t i;
		for(i = 0; i < o->size; i++) {
			o->ilist[i] = sfp[1].ivalue;
		}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void FArray.setAll(Float! v) */

static METHOD knh__FArray_setAll(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {;
		FArray *o = (FArray*)sfp[0].o;
		size_t i;
		for(i = 0; i < o->size; i++) {
			o->flist[i] = sfp[1].fvalue;
		}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ======================================================================== */
/* [opRange] */

/* ------------------------------------------------------------------------ */

static
Array *new_Array__range(Ctx *ctx, Array *a, size_t s, size_t e /*until*/)
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
		{
			size_t i;
			for(i = 0; i < newsize; i++) {
				knh_Object_RCinc(newa->list[i]);
			}
		}
#endif
		newa->capacity = newsize;
		newa->size = newsize;
	}
	return newa;
}

/* ------------------------------------------------------------------------ */
/* @method This! Array.opRangeUntil(Int s, Int e) @Debug */

static METHOD knh__Array_opRangeUntil(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	size_t s = IS_NULL(sfp[1].o) ? 0 : knh_array_index(ctx, p_int(sfp[1]), o->size);
	size_t e = IS_NULL(sfp[2].o) ? (o->size) : knh_array_index(ctx, p_int(sfp[2]), o->size);
	KNH_RETURN(ctx, sfp, new_Array__range(ctx, o, s, e));
}

/* ------------------------------------------------------------------------ */
/* @method This! Array.opRangeTo(Int s, Int e) @Debug */

static METHOD knh__Array_opRangeTo(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	size_t s = IS_NULL(sfp[1].o) ? 0 : knh_array_index(ctx, p_int(sfp[1]), o->size);
	size_t e = IS_NULL(sfp[2].o) ? (o->size) : knh_array_index(ctx, p_int(sfp[2]) + 1, o->size) ;
	KNH_RETURN(ctx, sfp, new_Array__range(ctx, o, s, e));
}

/* ======================================================================== */
/* [op1] */

/* ------------------------------------------------------------------------ */
/* @method T1! Array.op1()  */

static METHOD knh__Array_op1(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *a = sfp[0].a;
	KNH_RETURN(ctx, sfp, knh_Array_n(a, knh_array_index(ctx, 0, a->size)));
}

/* ------------------------------------------------------------------------ */
/* @method T1! Array.op2()  */

static METHOD knh__Array_op2(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *a = sfp[0].a;
	KNH_RETURN(ctx, sfp, knh_Array_n(a, knh_array_index(ctx, 1, a->size)));
}

/* ------------------------------------------------------------------------ */
/* @method T1! Array.opN(Int! n)  */

static METHOD knh__Array_opN(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *a = sfp[0].a;
	KNH_RETURN(ctx, sfp, knh_Array_n(a, knh_array_index(ctx, p_int(sfp[1]), a->size)));
}

/* ------------------------------------------------------------------------ */
/* @method Int! IArray.op1()  */

static METHOD knh__IArray_op1(Ctx *ctx, knh_sfp_t *sfp)
{
	IArray *a = sfp[0].ia;
	KNH_RETURN_Int(ctx, sfp, a->ilist[knh_array_index(ctx, 0, a->size)]);
}

/* ------------------------------------------------------------------------ */
/* @method Int! IArray.op2()  */

static METHOD knh__IArray_op2(Ctx *ctx, knh_sfp_t *sfp)
{
	IArray *a = sfp[0].ia;
	KNH_RETURN_Int(ctx, sfp, a->ilist[knh_array_index(ctx, 1, a->size)]);
}

/* ------------------------------------------------------------------------ */
/* @method Int! IArray.opN(Int! n)  */

static METHOD knh__IArray_opN(Ctx *ctx, knh_sfp_t *sfp)
{
	IArray *a = sfp[0].ia;
	KNH_RETURN_Int(ctx, sfp, a->ilist[knh_array_index(ctx, p_int(sfp[1]), a->size)]);
}

/* ------------------------------------------------------------------------ */
/* @method Float! FArray.op1()  */

static METHOD knh__FArray_op1(Ctx *ctx, knh_sfp_t *sfp)
{
	FArray *a = sfp[0].fa;
	KNH_RETURN_Float(ctx, sfp, a->flist[knh_array_index(ctx, 0, a->size)]);
}

/* ------------------------------------------------------------------------ */
/* @method Float! FArray.op2()  */

static METHOD knh__FArray_op2(Ctx *ctx, knh_sfp_t *sfp)
{
	FArray *a = sfp[0].fa;
	KNH_RETURN_Float(ctx, sfp, a->flist[knh_array_index(ctx, 1, a->size)]);
}

/* ------------------------------------------------------------------------ */
/* @method Float! FArray.opN(Int! n)  */

static METHOD knh__FArray_opN(Ctx *ctx, knh_sfp_t *sfp)
{
	FArray *a = sfp[0].fa;
	KNH_RETURN_Float(ctx, sfp, a->flist[knh_array_index(ctx, p_int(sfp[1]), a->size)]);
}

/* ======================================================================== */
/* [Class] */

/* @method Array! Class.domain() */

static
METHOD knh__Class_domain(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, knh_getClassDomain(ctx, (sfp[0].c)->cid));
}


/* ======================================================================== */


/* ------------------------------------------------------------------------ */

#endif /*KNH_CC_METHODAPI*/

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
