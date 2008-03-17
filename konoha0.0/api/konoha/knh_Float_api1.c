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
/* ======================================================================== */
/* [method] */

/* @method[STATIC] Float! Float.opAdd(Float! v) */

METHOD knh__Float_opAdd(Ctx *ctx, Object **sfp)
{
	Float *v = new_Float__fast(ctx, CLASS_Float, knh_Number_tofloat(sfp[0]) + knh_Number_tofloat(sfp[1]));
	VM_RET(ctx, v);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Float! Float.opSub(Float! v) */

METHOD knh__Float_opSub(Ctx *ctx, Object **sfp)
{
	Float *v = new_Float__fast(ctx, CLASS_Float, knh_Number_tofloat(sfp[0]) - knh_Number_tofloat(sfp[1]));
	VM_RET(ctx, v);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Float! Float.opMul(Float! v) */

METHOD knh__Float_opMul(Ctx *ctx, Object **sfp)
{
	Float *v = new_Float__fast(ctx, CLASS_Float, knh_Number_tofloat(sfp[0]) * knh_Number_tofloat(sfp[1]));
	VM_RET(ctx, v);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Float! Float.opDiv(Float! v) */

METHOD knh__Float_opDiv(Ctx *ctx, Object **sfp)
{
	Float *v = new_Float__fast(ctx, CLASS_Float, knh_Number_tofloat(sfp[0]) / knh_Number_tofloat(sfp[1]));
	VM_RET(ctx, v);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool! Float.opEq(Float value) */

METHOD knh__Float_opEq(Ctx *ctx, Object **sfp)
{
	if(knh_Number_tofloat(sfp[0]) == knh_Number_tofloat(sfp[1])) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool! Float.opNeq(Float value) */

METHOD knh__Float_opNeq(Ctx *ctx, Object **sfp)
{
	if(knh_Number_tofloat(sfp[0]) != knh_Number_tofloat(sfp[1])) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool! Float.opLt(Float value) */

METHOD knh__Float_opLt(Ctx *ctx, Object **sfp)
{
	if(knh_Number_tofloat(sfp[0]) < knh_Number_tofloat(sfp[1])) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool! Float.opLte(Float value) */

METHOD knh__Float_opLte(Ctx *ctx, Object **sfp)
{
	if(knh_Number_tofloat(sfp[0]) <= knh_Number_tofloat(sfp[1])) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool! Float.opGt(Float value) */

METHOD knh__Float_opGt(Ctx *ctx, Object **sfp)
{
	if(knh_Number_tofloat(sfp[0]) > knh_Number_tofloat(sfp[1])) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool! Float.opGte(Float value) */

METHOD knh__Float_opGte(Ctx *ctx, Object **sfp)
{
	if(knh_Number_tofloat(sfp[0]) >= knh_Number_tofloat(sfp[1])) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [mapping] */

/* @map[STATIC] String Float */

Object* knh_String_Float(Ctx *ctx, Object *self, MapMap *map)
{
	knh_bytes_t t = knh_String_tobytes(self);
//	if(!knh_byte_isnum(t)) {
//		return_Null(ctx, "NumberFormat!!: %s", t.buf);
//	}
	return new_Float(ctx, knh_bytes_tofloat(t));
}

/* ------------------------------------------------------------------------ */
/* @map[STATIC] Float String */

Object* knh_Float_String(Ctx *ctx, Object *self, MapMap *map)
{
	char buf[KNH_FLOATUNIT_BUFSIZ];
	knh_FloatUnit_format(knh_tclass_getFloatUnit(ctx, knh_Object_cid(self)), buf, knh_Float_value((Float*)self));
	return new_String__fast(ctx, CLASS_String, B(buf));
}

/* ------------------------------------------------------------------------ */
/* @map[STATIC] Int Float */

Object* knh_Int_Float(Ctx *ctx, Object *self, MapMap *map)
{
	return new_Float__fast(ctx, CLASS_Float, (knh_float_t)knh_Int_value(((Int*)self)));
}

/* ------------------------------------------------------------------------ */
/* @map[STATIC] Float Int */

Object* knh_Float_Int(Ctx *ctx, Object *self, MapMap *map)
{
	return new_Int__fast(ctx, CLASS_Int, knh_Float_toint(((Float*)self)));
}

/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */
/* @method void Float.%s(OutputStream w, Any m) */

void knh_Float__s(Ctx *ctx, Float *b, OutputStream *w, Any *m)
{
	FloatUnit *fu = knh_tclass_getFloatUnit(ctx, knh_Object_cid(b));
	knh_write__ffmt(ctx, w, fu->FMT, b->value);
}

/* ------------------------------------------------------------------------ */
/* @method void Float.%dump(OutputStream w, Any m) */

void knh_Float__dump(Ctx *ctx, Float *b, OutputStream *w, Any *m)
{
	FloatUnit *fu = knh_tclass_getFloatUnit(ctx, knh_Object_cid(b));
	knh_write__ffmt(ctx, w, fu->FMT, b->value);
	knh_bytes_t tag = knh_String_tobytes(fu->spec.tag);
	if(tag.len > 0) {
		knh_putc(ctx, w, '[');
		knh_write(ctx, w, tag);
		knh_putc(ctx, w, ']');
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
