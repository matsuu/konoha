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

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Int! Int.opAdd(Int! v) */

METHOD knh__Int_opAdd(Ctx *ctx, Object **sfp)
{
	Int *n = new_Int(ctx, (knh_Int_value((Int*)sfp[0]) + knh_Int_value((Int*)sfp[1])));
	VM_RET(ctx, n);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Int! Int.opSub(Int! n) */

METHOD knh__Int_opSub(Ctx *ctx, Object **sfp)
{
	Int *n = new_Int(ctx, (knh_Int_value((Int*)sfp[0]) - knh_Int_value((Int*)sfp[1])));
	VM_RET(ctx, n);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Int! Int.opMul(Int! n) */

METHOD knh__Int_opMul(Ctx *ctx, Object **sfp)
{
	Int *n = new_Int(ctx, (knh_Int_value((Int*)sfp[0]) * knh_Int_value((Int*)sfp[1])));
	VM_RET(ctx, n);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Int! Int.opDiv(Int! n) */

METHOD knh__Int_opDiv(Ctx *ctx, Object **sfp)
{
	Int *n = new_Int(ctx, (knh_Int_value((Int*)sfp[0]) / knh_Int_value((Int*)sfp[1])));
	VM_RET(ctx, n);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Int! Int.opMod(Int! n) */

METHOD knh__Int_opMod(Ctx *ctx, Object **sfp)
{
	Int *n = new_Int(ctx, (knh_Int_value((Int*)sfp[0]) % knh_Int_value((Int*)sfp[1])));
	VM_RET(ctx, n);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool Int.opEq(Int! value) */

METHOD knh__Int_opEq(Ctx *ctx, Object **sfp)
{
	if(((Int*)sfp[0])->value == ((Int*)sfp[1])->value) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool Int.opNeq(Int! value) */

METHOD knh__Int_opNeq(Ctx *ctx, Object **sfp)
{
	if(((Int*)sfp[0])->value != ((Int*)sfp[1])->value) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool! Int.opLt(Int! value) */

METHOD knh__Int_opLt(Ctx *ctx, Object **sfp)
{
	if(((Int*)sfp[0])->value < ((Int*)sfp[1])->value) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool! Int.opLte(Int! value) */

METHOD knh__Int_opLte(Ctx *ctx, Object **sfp)
{
	if(((Int*)sfp[0])->value <= ((Int*)sfp[1])->value) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool! Int.opGt(Int! value) */

METHOD knh__Int_opGt(Ctx *ctx, Object **sfp)
{
	if(((Int*)sfp[0])->value > ((Int*)sfp[1])->value) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool! Int.opGte(Int! value) */

METHOD knh__Int_opGte(Ctx *ctx, Object **sfp)
{
	if(((Int*)sfp[0])->value >= ((Int*)sfp[1])->value) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}


/* ------------------------------------------------------------------------ */
/* @method[STATIC] Int! Int.opLogicalAnd(Int! v) */

METHOD knh__Int_opLogicalAnd(Ctx *ctx, Object **sfp)
{
	Int *n = new_Int(ctx, (knh_Int_value((Int*)sfp[0]) & knh_Int_value((Int*)sfp[1])));
	VM_RET(ctx, n);
}

/* ------------------------------------------------------------------------ */

/* @method[STATIC] Int! Int.opLogicalOr(Int! v) */

METHOD knh__Int_opLogicalOr(Ctx *ctx, Object **sfp)
{
	Int *n = new_Int(ctx, (knh_Int_value((Int*)sfp[0]) | knh_Int_value((Int*)sfp[1])));
	VM_RET(ctx, n);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Int! Int.opLogicalXor(Int! n) */

METHOD knh__Int_opLogicalXor(Ctx *ctx, Object **sfp)
{
	Int *n = new_Int(ctx, (knh_Int_value((Int*)sfp[0]) ^ knh_Int_value((Int*)sfp[1])));
	VM_RET(ctx, n);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Int! Int.opLogicalNot() */

METHOD knh__Int_opLogicalNot(Ctx *ctx, Object **sfp)
{
	Int *n = new_Int(ctx, ~(knh_Int_value((Int*)sfp[0])));
	VM_RET(ctx, n);
}

/* ------------------------------------------------------------------------ */

/* @method[STATIC] Int! Int.opLShift(Int! n) */

METHOD knh__Int_opLShift(Ctx *ctx, Object **sfp)
{
	Int *n = new_Int(ctx, (knh_Int_value((Int*)sfp[0]) << knh_Int_value((Int*)sfp[1])));
	VM_RET(ctx, n);
}

/* ------------------------------------------------------------------------ */

/* @method[STATIC] Int! Int.opRShift(Int! n) */

METHOD knh__Int_opRShift(Ctx *ctx, Object **sfp)
{
	Int *n = new_Int(ctx, (knh_Int_value((Int*)sfp[0]) >> knh_Int_value((Int*)sfp[1])));
	VM_RET(ctx, n);
}


/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [mapping] */

/* ------------------------------------------------------------------------ */
/* @map[STATIC] String Int */

Object* knh_String_Int(Ctx *ctx, Object *self, MapMap *map)
{
	knh_bytes_t t = knh_String_tobytes(self);
//	if(!knh_byte_isNumber(t)) {
//		return_Null(ctx, "Format!!: %s", t.buf);
//	}
	return new_Int(ctx, knh_bytes_toint(t));
}

/* ------------------------------------------------------------------------ */
/* @map[STATIC] Int String! */

Object* knh_Int_String(Ctx *ctx, Object *self, MapMap *map)
{
	Int *b = (Int*)self;
	char buf[KNH_INTUNIT_BUFSIZ];
	knh_IntUnit_format(knh_tclass_getIntUnit(ctx, knh_Object_cid(b)), buf, b->value);
	return new_String__fast(ctx, CLASS_String, B(buf));
}

/* ------------------------------------------------------------------------ */

/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */
/* @method void Int.%s(OutputStream w, Any m) */

void knh_Int__s(Ctx *ctx, Int *b, OutputStream *w, Any *m)
{
	knh_write__i(ctx, w, b->value);
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%x(OutputStream w, Any m) */

void knh_Int__x(Ctx *ctx, Int *b, OutputStream *w, Any *m)
{
	knh_write__x(ctx, w, b->value);
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%bits(OutputStream w=new, Any m) */

void knh_Int__bits(Ctx *ctx, Int *b, OutputStream *w, Any *m)
{
	knh_uint_t i, flag = 1 << ((sizeof(knh_int_t) * 8)- 1);
	for(i = 0; i < (sizeof(knh_int_t) * 8); i++) {
		if(i > 0 && i % 8 == 0) {
			knh_putc(ctx, w, ' ');
		}
		if((flag & b->value) == flag) {
			knh_putc(ctx, w, '1');
		}else{
			knh_putc(ctx, w, '0');
		}
		flag >>= 1;
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%dump(OutputStream w, Any m) */

void knh_Int__dump(Ctx *ctx, Int *b, OutputStream *w, Any *m)
{
	IntUnit *u = knh_tclass_getIntUnit(ctx, knh_Object_cid(b));
	knh_write__i(ctx, w, b->value);
	knh_bytes_t tag = knh_String_tobytes(u->spec.tag);
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
