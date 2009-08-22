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
/* [opHas] */

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! String.opHas(String! s) */

static METHOD knh__String_opHas(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp,
		knh_bytes_indexOf(knh_String_tobytes(sfp[0].s), knh_String_tobytes(sfp[1].s)) != -1);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Pair.opHas(Any v) */
/* @method Boolean! Pair.opCase(Any v) */

static METHOD knh__Pair_opHas(Ctx *ctx, knh_sfp_t *sfp)
{
	Pair *t = sfp[0].pair;
	int res;
	knh_sfp_boxing(ctx, sfp + 1);
	res = ((knh_Object_compareTo(ctx, t->first, sfp[1].o) == 0)
			|| (knh_Object_compareTo(ctx, t->second, sfp[1].o) == 0));
	KNH_RETURN_Boolean(ctx, sfp, res);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Range.opHas(Any v) */
/* @method Boolean! Range.opCase(Any v) */

static METHOD knh__Range_opHas(Ctx *ctx, knh_sfp_t *sfp)
{
	int res = 0/*NotFound*/;
	Range *o = sfp[0].range;
	if(IS_Int((o)->start) && IS_Float(sfp[1].o)) {
		KNH_SETv(ctx, sfp[1].o, new_Int(ctx, (knh_int_t)sfp[1].fvalue));
	}
	else if(IS_Float((o)->start) && IS_Int(sfp[1].o)) {
		KNH_SETv(ctx, sfp[1].o, new_Float(ctx, (knh_float_t)sfp[1].ivalue));
	}
	else {
		knh_sfp_boxing(ctx, sfp + 1);
	}
	if(knh_Object_compareTo(ctx, o->start, sfp[1].o) <= 0) {
		if(knh_Range_isInclusive(o)) {
			if(knh_Object_compareTo(ctx, sfp[1].o, o->end) <= 0) {
				res = 1;
			}
		}
		else {
			if(knh_Object_compareTo(ctx, sfp[1].o, o->end) < 0) {
				res = 1;
			}
		}
	}
	KNH_RETURN_Boolean(ctx, sfp, res);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Array.opHas(Any v) */
/* @method Boolean! Array.opCase(Any v) */

static METHOD knh__Array_opHas(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *o = (Array*)sfp[0].o;
	knh_sfp_boxing(ctx, sfp + 1);
	size_t i, res = 0/*NotFound*/;
	for(i = 0; i < o->size; i++) {
		if(knh_Object_compareTo(ctx, o->list[i], sfp[1].o) == 0) {
			res = 1; break;
		}
	}
	KNH_RETURN_Boolean(ctx, sfp, res);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Tuple.opHas(Any v) */
/* @method Boolean! Tuple.opCase(Any v) */

static METHOD knh__Tuple_opHas(Ctx *ctx, knh_sfp_t *sfp)
{
	if(knh_Tuple_isTriple(sfp[0].tuple)) {
		Tuple *t = sfp[0].tuple;
		int res;
		knh_sfp_boxing(ctx, sfp + 1);
		res = ((knh_Object_compareTo(ctx, t->first, sfp[1].o) == 0)
				|| (knh_Object_compareTo(ctx, t->second, sfp[1].o) == 0)
				|| (knh_Object_compareTo(ctx, t->third, sfp[1].o) == 0));
		KNH_RETURN_Boolean(ctx, sfp, res);
	}
	else {
		knh__Array_opHas(ctx, sfp); // reuse
	}
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! IArray.opHas(Any v) */
/* @method Boolean! IArray.opCase(Any v) */

static METHOD knh__IArray_opHas(Ctx *ctx, knh_sfp_t *sfp)
{
	int res = 0/*NotFound*/;
	if(IS_bInt(sfp[1].o)) {
		IArray *o = (IArray*)sfp[0].o;
		knh_int_t v = sfp[1].ivalue;
		size_t i;
		for(i = 0; i < o->size; i++) {
			if(o->ilist[i] == v) {
				res = 1; break;
			}
		}
	}
	KNH_RETURN_Boolean(ctx, sfp, res);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! FArray.opHas(Any v) */
/* @method Boolean! FArray.opCase(Any v) */

static METHOD knh__FArray_opHas(Ctx *ctx, knh_sfp_t *sfp)
{
	int res = 0/*NotFound*/;
	if(IS_bFloat(sfp[1].o)) {
		FArray *o = (FArray*)sfp[0].o;
		knh_float_t v = sfp[1].fvalue;
		size_t i;
		for(i = 0; i < o->size; i++) {
			if(o->flist[i] == v) {
				res = 1; break;
			}
		}
	}
	KNH_RETURN_Boolean(ctx, sfp, res);
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
/* @method[CONST|NULLBASE] String! String.opAdd(Any v) */

static METHOD knh__String_opAdd(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
	knh_sfp_t *esp = KNH_LOCAL(ctx);
	if(IS_bString(sfp[0].o)) {
		knh_Bytes_write(ctx, cwb->ba, knh_String_tobytes(sfp[0].s));
	}
	else {
		KNH_SETv(ctx, esp[1].o, sfp[0].o); esp[1].data = sfp[0].data;
		knh_esp1_format(ctx, METHODN__s, cwb->w, KNH_NULL);
	}
	if(IS_bString(sfp[1].o)) {
		knh_Bytes_write(ctx, cwb->ba, knh_String_tobytes(sfp[1].s));
	}
	else {
		KNH_ASSERT(esp == ctx->esp);
		KNH_SETv(ctx, esp[1].o, sfp[1].o); esp[1].data = sfp[1].data;
		knh_esp1_format(ctx, METHODN__s, cwb->w, KNH_NULL);
	}
	KNH_RETURN(ctx, sfp, knh_cwb_newString(ctx, cwb));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String! String.opSub(String! t) */

static METHOD knh__String_opSub(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t base = knh_String_tobytes(sfp[0].s);
	knh_bytes_t t = knh_String_tobytes(sfp[1].s);
	knh_uchar_t c = t.buf[0];
	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
	size_t i;
	for(i = 0; i < base.len; i++) {
		if(base.buf[i] == c) {
			size_t j;
			for(j = 1; j < t.len; j++) {
				if(base.buf[i+j] != t.buf[j]) break;
			}
			if(j == t.len) {
				i += t.len - 1;
				continue;
			}
		}
		knh_Bytes_putc(ctx, cwb->ba, base.buf[i]);
	}
	if(base.len == knh_cwb_size(cwb)) {
		knh_cwb_close(cwb);
		KNH_RETURN(ctx, sfp, sfp[0].o);
	}
	else {
		KNH_RETURN(ctx, sfp, knh_cwb_newString(ctx, cwb));
	}
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

///* ------------------------------------------------------------------------ */
///* @ method[NULLBASE|CONST] Int! Int.getSize() */
//
//static METHOD knh__Int_getSize(Ctx *ctx, knh_sfp_t *sfp)
//{
//	if(IS_NULL(sfp[0].o)) {
//		KNH_RETURN_Int(ctx, sfp, 0);
//	}
//	else {
//		knh_int_t n = p_integer(sfp[0]);
//		if(n >= 0) {
//			KNH_RETURN_Int(ctx, sfp, n);
//		}
//		else {
//			KNH_RETURN_Int(ctx, sfp, -(n));
//		}
//	}
//}
//
///* ------------------------------------------------------------------------ */
///* @ method[NULLBASE|CONST] Int! Float.getSize() */
//
//static METHOD knh__Float_getSize(Ctx *ctx, knh_sfp_t *sfp)
//{
//	if(IS_NULL(sfp[0].o)) {
//		KNH_RETURN_Int(ctx, sfp, 0);
//	}
//	else {
//		knh_uint_t n = (knh_uint_t)p_float(sfp[0]);
//		KNH_RETURN_Int(ctx, sfp, n);
//	}
//}

/* ------------------------------------------------------------------------ */
/* @method[NULLBASE] Int! Bytes.getSize() */

static METHOD knh__Bytes_getSize(Ctx *ctx, knh_sfp_t *sfp)
{
	size_t size = IS_bBytes(sfp[0].ba) ? (sfp[0].ba)->size : 0;
	KNH_RETURN_Int(ctx, sfp, size);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Int! String.getSize() */

static METHOD knh__String_getSize(Ctx *ctx, knh_sfp_t *sfp)
{
	size_t size = IS_bString(sfp[0].s) ? (sfp[0].s)->size : 0;
	if(!knh_String_isASCII(sfp[0].s)) {
		size = knh_bytes_mlen(knh_String_tobytes(sfp[0].s));
	}
	KNH_RETURN_Int(ctx, sfp, size);
}

/* ------------------------------------------------------------------------ */
/* @method[NULLBASE] Int! Pair.getSize() */

static METHOD knh__Pair_getSize(Ctx *ctx, knh_sfp_t *sfp)
{
	size_t size = (IS_NULL(sfp[0].o)) ? 0 : 2;
	KNH_RETURN_Int(ctx, sfp, size);
}

/* ------------------------------------------------------------------------ */
/* @method[NULLBASE] Int! Tuple.getSize() */

static METHOD knh__Tuple_getSize(Ctx *ctx, knh_sfp_t *sfp)
{
	size_t size = (IS_NULL(sfp[0].o)) ? 0 : 2;
	if(!knh_Tuple_isTriple(sfp[0].tuple)) size = (sfp[0].tuple)->size;
	KNH_RETURN_Int(ctx, sfp, size);
}

/* ------------------------------------------------------------------------ */
/* @method[NULLBASE] Int! Range.getSize() */

static METHOD knh__Range_getSize(Ctx *ctx, knh_sfp_t *sfp)
{
	size_t size = (IS_NULL(sfp[0].o)) ? 0 : 2;
	knh_printf(ctx, KNH_STDOUT, "Do you really want to count Range.size ?\n");
	KNH_RETURN_Int(ctx, sfp, size);
}

/* ------------------------------------------------------------------------ */
/* @method[NULLBASE] Int! Array.getSize() */
/* @method[NULLBASE] Int! IArray.getSize() */
/* @method[NULLBASE] Int! FArray.getSize() */

static METHOD knh__Array_getSize(Ctx *ctx, knh_sfp_t *sfp)
{
	size_t size = IS_NULL(sfp[0].o) ? 0 : (sfp[0].a)->size ;
	KNH_RETURN_Int(ctx, sfp, size);
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
/* @method[CONST] String! String.get(Int! n) */

static METHOD knh__String_get(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t base = knh_String_tobytes(sfp[0].s);
	String *s;
	if(knh_String_isASCII(sfp[0].s)) {
		size_t n = knh_array_index(ctx, p_int(sfp[1]), knh_String_strlen(sfp[0].s));
		base.buf = base.buf + n;
		base.len = 1;
		s = new_String(ctx, base, sfp[0].s);
	}
	else {
		size_t off = knh_array_index(ctx, p_int(sfp[1]), knh_bytes_mlen(base));
		knh_bytes_t sub = knh_bytes_mofflen(base, off, 1);
		s = new_String(ctx, sub, sfp[0].s);
	}
	KNH_RETURN(ctx, sfp, s);
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
/* @method Any Tuple.get(Int! n) */

static METHOD knh__Tuple_get(Ctx *ctx, knh_sfp_t *sfp)
{
	if(knh_Tuple_isTriple(sfp[0].tuple)) {
		Object *v = KNH_NULL;
		switch(p_int(sfp[1])) {
		case 0: v = (sfp[0].tuple)->first; break;
		case 1: v = (sfp[1].tuple)->first; break;
		case 2: v = (sfp[2].tuple)->first; break;
		default: knh_array_index(ctx, p_int(sfp[1]), 3);
		}
		KNH_RETURN(ctx, sfp, v);
	}
	else {
		knh__Array_get(ctx, sfp); /* reuse */
	}
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

static
void knh_stack_rangeUntil(Ctx *ctx, knh_sfp_t *sfp, size_t size, size_t *s, size_t *e)
{
	*s = IS_NULL(sfp[1].o) ? 0 : knh_array_index(ctx, p_int(sfp[1]), size);
	*e = IS_NULL(sfp[2].o) ? (size) : knh_array_index(ctx, p_int(sfp[2]), size);
}

/* ------------------------------------------------------------------------ */

static
void knh_stack_rangeTo(Ctx *ctx, knh_sfp_t *sfp, size_t size, size_t *s, size_t *e)
{
	*s = IS_NULL(sfp[1].o) ? 0 : knh_array_index(ctx, p_int(sfp[1]), size);
	*e = IS_NULL(sfp[2].o) ? (size) : knh_array_index(ctx, p_int(sfp[2]) + 1, size);
}

/* ------------------------------------------------------------------------ */

static
Bytes *new_Bytes__range(Ctx *ctx, Bytes *ba, size_t s, size_t e)
{
	Bytes *newa = (Bytes*)new_Object_init(ctx, ba->h.flag, ba->h.cid, 0);
	if(e < s) {
		size_t t = s; s = e; e = t;
	}
	DBG2_ASSERT(e <= ba->size);
	if(s < e) {
		size_t newsize = e - s;
		size_t capacity = newsize;
		if(newsize > 0) {
			if(capacity < 256) capacity = 256;
			newa->buf = (knh_uchar_t*)KNH_MALLOC(ctx, capacity);
			knh_bzero(newa->buf, capacity);
			knh_memcpy(newa->buf, &ba->buf[s], newsize);
		}
		else {
			newa->buf = (knh_uchar_t*)"";
		}
		newa->capacity = capacity;
		newa->size = newsize;
	}
	return newa;
}

/* ------------------------------------------------------------------------ */
/* @method Bytes! Bytes.opRangeUntil(Int s, Int e) @Debug */

static METHOD knh__Bytes_opRangeUntil(Ctx *ctx, knh_sfp_t *sfp)
{
	size_t s, e;
	knh_stack_rangeUntil(ctx, sfp, (sfp[0].ba)->size, &s, &e);
	KNH_RETURN(ctx, sfp, new_Bytes__range(ctx, sfp[0].ba, s, e));
}

/* ------------------------------------------------------------------------ */
/* @method Bytes! Bytes.opRangeTo(Int s, Int e) @Debug */

static METHOD knh__Bytes_opRangeTo(Ctx *ctx, knh_sfp_t *sfp)
{
	size_t s, e;
	knh_stack_rangeTo(ctx, sfp, (sfp[0].ba)->size, &s, &e);
	KNH_RETURN(ctx, sfp, new_Bytes__range(ctx, sfp[0].ba, s, e));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String! String.substring(Int offset, Int len) */

static METHOD knh__String_substring(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t base = knh_String_tobytes(sfp[0].s);
	knh_bytes_t sub;
	if(knh_String_isASCII(sfp[0].s)) {
		size_t offset = IS_NULL(sfp[1].o) ? 0 : knh_array_index(ctx, sfp[1].ivalue, base.len);
		sub = knh_bytes_last(base, offset);
		if(IS_NOTNULL(sfp[2].o)) {
			size_t len = (size_t)sfp[2].ivalue;
			if(len < sub.len) sub = knh_bytes_first(sub, len);
		}
	}
	else { // multibytes
		size_t mlen = knh_bytes_mlen(base);
		size_t offset = IS_NULL(sfp[1].o) ? 0 : knh_array_index(ctx, sfp[1].ivalue, mlen);
		size_t length = IS_NULL(sfp[2].o) ? (mlen - offset) : (size_t)sfp[2].ivalue;
		sub = knh_bytes_mofflen(base, offset, length);
	}
	String *s;
	if(sub.len == 0) {
		s = TS_EMPTY;
	}
	else if(sub.len == base.len) {
		s = sfp[0].s;
	}
	else {
		s = new_String(ctx, sub, sfp[0].s);
	}
	KNH_RETURN(ctx, sfp, s);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String! String.opRangeUntil(Int s, Int e) */

static METHOD knh__String_opRangeUntil(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_NOTNULL(sfp[2].o)) {
		size_t offset = IS_NULL(sfp[1].o) ? 0 : (size_t)sfp[1].ivalue;
		sfp[2].ivalue = sfp[2].ivalue - offset;
	}
	knh__String_substring(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String! String.opRangeTo(Int s, Int e) */

static METHOD knh__String_opRangeTo(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_NOTNULL(sfp[2].o)) {
		size_t offset = IS_NULL(sfp[1].o) ? 0 : (size_t)sfp[1].ivalue;
		sfp[2].ivalue = sfp[2].ivalue - offset + 1;
	}
	knh__String_substring(ctx, sfp);
}

/* ------------------------------------------------------------------------ */

static
Array *new_Array__range(Ctx *ctx, Array *a, size_t s, size_t e /*until*/, size_t sizeofdata)
{
	Array *newa = (Array*)new_Object_init(ctx, a->h.flag, a->h.cid, 0);
	if(e < s) {
		size_t t = s; s = e; e = t;
	}
	if(s < e) {
		KNH_ASSERT(e <= a->size);
		size_t newsize = e - s;
		if(newsize > 0) {
			char *p = (char*)a->list;
			newa->list = (Object**)KNH_MALLOC(ctx, newsize * sizeofdata);
			knh_memcpy(newa->list, p + (s * sizeofdata), newsize * sizeofdata);
			if(IS_bArray(a)) {
				size_t i;
				for(i = 0; i < newsize; i++) {
					knh_Object_RCinc(newa->list[i]);
				}
			}
		}
		else {
			newa->list = NULL;
		}
		newa->capacity = newsize;
		newa->size = newsize;
	}
	return newa;
}

/* ------------------------------------------------------------------------ */
/* @method This! Array.opRangeUntil(Int s, Int e) @Debug */

static METHOD knh__Array_opRangeUntil(Ctx *ctx, knh_sfp_t *sfp)
{
	size_t s, e;
	knh_stack_rangeUntil(ctx, sfp, (sfp[0].a)->size, &s, &e);
	KNH_RETURN(ctx, sfp, new_Array__range(ctx, sfp[0].a, s, e, sizeof(Object*)));
}

/* ------------------------------------------------------------------------ */
/* @method This! Array.opRangeTo(Int s, Int e) @Debug */

static METHOD knh__Array_opRangeTo(Ctx *ctx, knh_sfp_t *sfp)
{
	size_t s, e;
	knh_stack_rangeTo(ctx, sfp, (sfp[0].a)->size, &s, &e);
	KNH_RETURN(ctx, sfp, new_Array__range(ctx, sfp[0].a, s, e, sizeof(Object*)));
}

/* ------------------------------------------------------------------------ */
/* @method This! IArray.opRangeUntil(Int s, Int e) @Debug */

static METHOD knh__IArray_opRangeUntil(Ctx *ctx, knh_sfp_t *sfp)
{
	size_t s, e;
	knh_stack_rangeUntil(ctx, sfp, (sfp[0].a)->size, &s, &e);
	KNH_RETURN(ctx, sfp, new_Array__range(ctx, sfp[0].a, s, e, sizeof(knh_int_t)));
}

/* ------------------------------------------------------------------------ */
/* @method This! IArray.opRangeTo(Int s, Int e) @Debug */

static METHOD knh__IArray_opRangeTo(Ctx *ctx, knh_sfp_t *sfp)
{
	size_t s, e;
	knh_stack_rangeTo(ctx, sfp, (sfp[0].a)->size, &s, &e);
	KNH_RETURN(ctx, sfp, new_Array__range(ctx, sfp[0].a, s, e, sizeof(knh_int_t)));
}

/* ------------------------------------------------------------------------ */
/* @method This! FArray.opRangeUntil(Int s, Int e) @Debug */

static METHOD knh__FArray_opRangeUntil(Ctx *ctx, knh_sfp_t *sfp)
{
	size_t s, e;
	knh_stack_rangeUntil(ctx, sfp, (sfp[0].a)->size, &s, &e);
	KNH_RETURN(ctx, sfp, new_Array__range(ctx, sfp[0].a, s, e, sizeof(knh_float_t)));
}

/* ------------------------------------------------------------------------ */
/* @method This! FArray.opRangeTo(Int s, Int e) @Debug */

static METHOD knh__FArray_opRangeTo(Ctx *ctx, knh_sfp_t *sfp)
{
	size_t s, e;
	knh_stack_rangeTo(ctx, sfp, (sfp[0].a)->size, &s, &e);
	KNH_RETURN(ctx, sfp, new_Array__range(ctx, sfp[0].a, s, e, sizeof(knh_float_t)));
}

/* ======================================================================== */
/* [op1] */

/* ------------------------------------------------------------------------ */
/* @method T1! Pair.op0()  */

static METHOD knh__Pair_op0(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, (sfp[0].pair)->first);
}

/* ------------------------------------------------------------------------ */
/* @method T2! Pair.op1()  */

static METHOD knh__Pair_op1(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, (sfp[0].pair)->second);
}

/* ------------------------------------------------------------------------ */
/* @method Any Tuple.op0()  */

static METHOD knh__Tuple_op0(Ctx *ctx, knh_sfp_t *sfp)
{
	Object *res;
	if(knh_Tuple_isTriple(sfp[0].tuple)) {
		res = (sfp[0].tuple)->first;
	}
	else {
		knh_array_index(ctx, 0, (sfp[0].tuple)->size);
		res = (sfp[0].tuple)->list[0];
	}
	KNH_RETURN(ctx, sfp, res);
}

/* ------------------------------------------------------------------------ */
/* @method Any Tuple.op1()  */

static METHOD knh__Tuple_op1(Ctx *ctx, knh_sfp_t *sfp)
{
	Object *res;
	if(knh_Tuple_isTriple(sfp[0].tuple)) {
		res = (sfp[0].tuple)->second;
	}
	else {
		knh_array_index(ctx, 1, (sfp[0].tuple)->size);
		res = (sfp[0].tuple)->list[1];
	}
	KNH_RETURN(ctx, sfp, res);
}

/* ------------------------------------------------------------------------ */
/* @method Any Tuple.opN(Int! n)  */

static METHOD knh__Tuple_opN(Ctx *ctx, knh_sfp_t *sfp)
{
	Object *res;
	size_t size = knh_array_index(ctx, p_int(sfp[1]), (sfp[0].tuple)->size);
	if(knh_Tuple_isTriple(sfp[0].tuple)) {
		res = (sfp[0].tuple)->third;
	}
	else {
		res = (sfp[0].tuple)->list[size];
	}
	KNH_RETURN(ctx, sfp, res);
}

/* ------------------------------------------------------------------------ */
/* @method T1! Array.op0()  */

static METHOD knh__Array_op0(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *a = sfp[0].a;
	KNH_RETURN(ctx, sfp, knh_Array_n(a, knh_array_index(ctx, 0, a->size)));
}

/* ------------------------------------------------------------------------ */
/* @method T1! Array.op1()  */

static METHOD knh__Array_op1(Ctx *ctx, knh_sfp_t *sfp)
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
/* @method Int! IArray.op0()  */

static METHOD knh__IArray_op0(Ctx *ctx, knh_sfp_t *sfp)
{
	IArray *a = sfp[0].ia;
	KNH_RETURN_Int(ctx, sfp, a->ilist[knh_array_index(ctx, 0, a->size)]);
}

/* ------------------------------------------------------------------------ */
/* @method Int! IArray.op1()  */

static METHOD knh__IArray_op1(Ctx *ctx, knh_sfp_t *sfp)
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
/* @method Float! FArray.op0()  */

static METHOD knh__FArray_op0(Ctx *ctx, knh_sfp_t *sfp)
{
	FArray *a = sfp[0].fa;
	KNH_RETURN_Float(ctx, sfp, a->flist[knh_array_index(ctx, 0, a->size)]);
}

/* ------------------------------------------------------------------------ */
/* @method Float! FArray.op1()  */

static METHOD knh__FArray_op1(Ctx *ctx, knh_sfp_t *sfp)
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
