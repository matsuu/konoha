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

#ifdef KNH_CC_METHODAPI

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! Boolean.opNot() */

static METHOD knh__Boolean_opNot(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(p_bool(sfp[0])));
}

/* ------------------------------------------------------------------------ */
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
/* @method[VARARGS|CONST] Int! Int.opLand(Int! v) */

static METHOD knh__Int_opLand(Ctx *ctx, knh_sfp_t *sfp)
{
	int ac = knh_sfp_argc(ctx, sfp);
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
	int ac = knh_sfp_argc(ctx, sfp);
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
/* @method[STATIC] Int! Int.random(Int n) */

static METHOD knh__Int_random(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_int_t n = knh_rand();
	if(IS_NOTNULL(sfp[1].o)) {
		knh_int_t max = p_integer(sfp[1]);
		if(max > 0) {
			KNH_RETURN_Int(ctx, sfp,  n % max);
		}
	}
	KNH_RETURN_Int(ctx, sfp, n);
}

/* ------------------------------------------------------------------------ */
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

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Float! Float.random()  */

static METHOD knh__Float_random(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Float(ctx, sfp, knh_float_rand());
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Int! Float.floatToIntBits(Float! n) */

static METHOD knh__Float_floatToIntBits(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Int(ctx, sfp, sfp[1].fvalue);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Float! Float.intToFloatBits(Int! n) */

static METHOD knh__Float_intToFloatBits(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Float(ctx, sfp, sfp[1].ivalue);
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
/* @method void Boolean.%s(OutputStream w, String m) */

static METHOD knh__Boolean__s(Ctx *ctx, knh_sfp_t *sfp)
{
	if(p_bool(sfp[0])) {
		knh_write(ctx, sfp[1].w, knh_String_tobytes(TS_true));
	}
	else {
		knh_write(ctx, sfp[1].w, knh_String_tobytes(TS_false));
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Boolean.%k(OutputStream w, String m) */

static METHOD knh__Boolean__k(Ctx *ctx, knh_sfp_t *sfp)
{
	if(p_bool(sfp[0])) {
		knh_write(ctx, sfp[1].w, knh_String_tobytes(TS_true));
	}
	else {
		knh_write(ctx, sfp[1].w, knh_String_tobytes(TS_false));
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%s(OutputStream w, String m) */

static METHOD knh__Int__s(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_write_integerfmt(ctx, sfp[1].w, KNH_INT_FMT, sfp[0].ivalue);
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%k(OutputStream w, String m) */

static METHOD knh__Int__k(Ctx *ctx, knh_sfp_t *sfp)
{
	ClassSpec *u = konoha_getClassSpec(ctx, knh_Object_cid(sfp[0].o));
	knh_write_intx(ctx, sfp[1].w, u, sfp[0].ivalue);
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%d(OutputStream w, String m) */

static METHOD knh__Int__d(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_String(sfp[2].s)) {
		char fmt[40];
		knh_format_newFMT(fmt, sizeof(fmt), knh_String_tobytes(sfp[2].s), 0, KNH_INT_FMT);
		knh_write_integerfmt(ctx, sfp[1].w, fmt, sfp[0].ivalue);
	}
	else {
		knh_write_integerfmt(ctx, sfp[1].w, KNH_INT_FMT, sfp[0].ivalue);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%u(OutputStream w, String m) */

static METHOD knh__Int__u(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_String(sfp[2].s)) {
		char fmt[40];
		knh_format_newFMT(fmt, sizeof(fmt), knh_String_tobytes(sfp[2].s), 0, KNH_UINT_FMT);
		knh_write_integerfmt(ctx, sfp[1].w, fmt, sfp[0].ivalue);
	}
	else {
		knh_write_integerfmt(ctx, sfp[1].w, KNH_UINT_FMT, sfp[0].ivalue);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%f(OutputStream w, String m) */

static METHOD knh__Int__f(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_String(sfp[2].s)) {
		char fmt[40];
		knh_format_newFMT(fmt, sizeof(fmt), knh_String_tobytes(sfp[2].s), 1, KNH_FLOAT_FMT);
		knh_write__ffmt(ctx, sfp[1].w, fmt, (knh_float_t)sfp[0].ivalue);
	}
	else {
		knh_write__f(ctx, sfp[1].w, (knh_float_t)sfp[0].ivalue);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%x(OutputStream w, String m) */

static METHOD knh__Int__x(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_write_integerfmt(ctx, sfp[1].w, KNH_INT_XFMT, sfp[0].ivalue);
}

/* ------------------------------------------------------------------------ */

static
void knh_write_bits(Ctx *ctx, OutputStream *w, knh_uint64_t n, size_t bits)
{
	size_t i;
	knh_uint64_t flag = 1ULL << (bits - 1);
	for(i = 0; i < bits; i++) {
		if(i > 0 && i % 8 == 0) {
			knh_putc(ctx, w, ' ');
		}
		if((flag & n) == flag) {
			knh_putc(ctx, w, '1');
		}else{
			knh_putc(ctx, w, '0');
		}
		flag = flag >> 1;
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%bits(OutputStream w, String m) */

static METHOD knh__Int__bits(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_write_bits(ctx, sfp[1].w, sfp[0].ivalue, sizeof(knh_int_t) * 8);
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%c(OutputStream w, String m) */

static METHOD knh__Int__c(Ctx *ctx, knh_sfp_t *sfp)
{
	char buf[16];
	knh_format_utf8(buf, sizeof(buf), sfp[0].ivalue);
	knh_write(ctx, sfp[1].w, B(buf));
}

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* @method void Float.%s(OutputStream w, String m) */

static METHOD knh__Float__s(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_write__ffmt(ctx, sfp[1].w, KNH_FLOAT_FMT, p_float(sfp[0]));
}

/* ------------------------------------------------------------------------ */
/* @method void Float.%d(OutputStream w, String m) */

static METHOD knh__Float__d(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_String(sfp[2].s)) {
		char fmt[40];
		knh_format_newFMT(fmt, sizeof(fmt), knh_String_tobytes(sfp[2].s), 0, KNH_INT_FMT);
		//DBG_P("fmt='%s'", fmt);
		knh_write_integerfmt(ctx, sfp[1].w, fmt, (knh_int_t)p_float(sfp[0]));
	}
	else {
		knh_write_integerfmt(ctx, sfp[1].w, KNH_INT_FMT, (knh_int_t)p_float(sfp[0]));
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Float.%f(OutputStream w, String m) */

static METHOD knh__Float__f(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_String(sfp[2].s)) {
		char fmt[40];
		knh_format_newFMT(fmt, sizeof(fmt), knh_String_tobytes(sfp[2].s), 1, KNH_FLOAT_FMT);
		//DBG_P("fmt='%s'", fmt);
		knh_write__ffmt(ctx, sfp[1].w, fmt, p_float(sfp[0]));
	}
	else {
		knh_write__ffmt(ctx, sfp[1].w, KNH_FLOAT_FMT, p_float(sfp[0]));
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Float.%bits(OutputStream w, String m) */

static METHOD knh__Float__bits(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_write_bits(ctx, sfp[1].w, sfp[0].data, sizeof(knh_float_t) * 8);
}

/* ------------------------------------------------------------------------ */
/* @method void Float.%k(OutputStream w, String m) */

static METHOD knh__Float__k(Ctx *ctx, knh_sfp_t *sfp)
{
	ClassSpec *u = konoha_getClassSpec(ctx, knh_Object_cid(sfp[0].o));
	knh_write_floatx(ctx, sfp[1].w, u, p_float(sfp[0]));
}

/* ======================================================================== */
/* [Boolean] */

/* ------------------------------------------------------------------------ */
/* @map[CONST] Boolean String! @Const @Final @LossLess */

static MAPPER knh_Boolean_String(Ctx *ctx, knh_sfp_t *sfp)
{
	String *s = (p_bool(sfp[0])) ? TS_true : TS_false;
	KNH_MAPPED(ctx, sfp, s);
}

/* ------------------------------------------------------------------------ */
/* @map[CONST] String Boolean! @Const @Final */

static MAPPER knh_String_Boolean(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t t = knh_String_tobytes(sfp[0].s);
	int b = (knh_bytes_equalsIgnoreCase(t, STEXT("true")) ||
				knh_bytes_equalsIgnoreCase(t, STEXT("yes")));
	KNH_MAPPED_Boolean(ctx, sfp, b);
}

/* ------------------------------------------------------------------------ */
/* @map String Int @Const @Final */

static MAPPER knh_String_Int(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_int_t v = 0;
	if(knh_bytes_parseint(knh_String_tobytes(sfp[0].s), &v)) {
		KNH_MAPPED_Int(ctx, sfp, v);
	}
	KNH_MAPPED(ctx, sfp, KNH_NULL);
}

/* ------------------------------------------------------------------------ */
/* @map Int String! @Const @Final @LossLess */

static MAPPER knh_Int_String(Ctx *ctx, knh_sfp_t *sfp)
{
	char buf[256];
	knh_snprintf(buf, sizeof(buf), KNH_INT_FMT, sfp[0].ivalue);
	KNH_MAPPED(ctx, sfp, new_String(ctx, B(buf), NULL));
}

/* ------------------------------------------------------------------------ */
/* @map String Float @Final @Const */

static MAPPER knh_String_Float(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_float_t f = 0.0;
	if(knh_bytes_parsefloat(knh_String_tobytes(sfp[0].s), &f)) {
		KNH_MAPPED_Float(ctx, sfp, f);
	}
	else {
		KNH_MAPPED(ctx, sfp, KNH_NULL);
	}
}

/* ------------------------------------------------------------------------ */
/* @map Float String! @Const @Final @LossLess */

static MAPPER knh_Float_String(Ctx *ctx, knh_sfp_t *sfp)
{
	char buf[256];
	knh_snprintf(buf, sizeof(buf), KNH_FLOAT_FMT, sfp[0].fvalue);
	KNH_MAPPED(ctx, sfp, new_String(ctx, B(buf), NULL));
}

/* ------------------------------------------------------------------------ */
/* @map Int Float! @Const @Final */

static MAPPER knh_Int_Float(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_float_t v = (knh_float_t)sfp[0].ivalue;
	KNH_MAPPED_Float(ctx, sfp, v);
}

/* ------------------------------------------------------------------------ */
/* @map Float Int! @Const @Final */

static MAPPER knh_Float_Int(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_int_t v = (knh_int_t)sfp[0].fvalue;
	KNH_MAPPED_Int(ctx, sfp, v);
}

/* ------------------------------------------------------------------------ */

#endif /*KNH_CC_METHODAPI*/


#ifdef __cplusplus
}
#endif
