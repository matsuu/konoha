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
/* [macros] */

#define _knh_Object_cid(o)           (knh_class_t)(knh_Object_head(o)->cid)
#define _knh_Object_topsid(o)        knh_tclass_topsid(knh_Object_cid(o))
#define _knh_Object_offset(o)        knh_tclass_offset(knh_Object_cid(o))


/* ======================================================================== */
/* [copy] */

Object *
new_Object__cid(Ctx *ctx, knh_flag_t flag, knh_class_t cid)
{
	Object **s = (Object**)knh_Object_malloc(ctx, cid);
	L_TAIL:;
	ClassStruct *cs = knh_tclass_cstruct(cid);
	size_t offset = knh_tclass_offset(cid);
	
	f_struct_init finit = knh_tstruct_finit(cs->sid);
	finit(ctx, (Struct*)(&(s[offset])), 0, cs);

	if(offset == 0) return (Object*)s;
	cid = knh_tclass_supcid(cid);
	goto L_TAIL;
}

/* ======================================================================== */
/* [copy] */


Object *knh_Object_copy(Ctx *ctx, Object *b)
{
	if(knh_Object_isImmutable(b)) {
		return b;
	}
	DEBUG("!IMMUTABLE %s", CLASSN(knh_Object_cid(b)));
	return b;
}

/* ======================================================================== */
/* [class] */

/* @method Class! Object.getClass() */

INLINE
knh_class_t knh_Object_getClass(Object *b)
{
	return knh_Object_pcid(b);
}

/* ======================================================================== */
/* [commons] */


knh_hcode_t knh_Object_hcode(Ctx *ctx, Object *self)
{
	switch(knh_Object_topsid(self)) {
		case STRUCT_String :  return knh_String_hcode(self);
		case STRUCT_Int :     return (knh_hcode_t)knh_Int_value((Int*)self);
		case STRUCT_Float:    return (knh_hcode_t)(knh_Float_value((Float*)self));
	}
	TODO();
	return (knh_hcode_t)self / sizeof(Object*);
}

/* ------------------------------------------------------------------------ */

knh_bytes_t knh_Object_tobytes(Ctx *ctx, Object *v)
{
	switch(knh_Object_topsid(v)) {
		case STRUCT_String : return knh_String_tobytes(v);
		case STRUCT_Bytes : return knh_Bytes_tobytes(v);
	}
	TODO();
	return STEXT("");
}

/* ======================================================================== */
/* [structs] */

/* @method Int! Object.compare(Any other) */

INLINE
knh_int_t knh_Object_compare(Ctx *ctx, Object *o1, Object *o2)
{
	if(o1 == o2) return 0;
	knh_class_t cid  = knh_Object_cid(o1);
	knh_class_t cid2 = knh_Object_cid(o2);

	if(cid == cid2) {
		if(cid == CLASS_Int) {
			return ((Int*)o1)->value - ((Int*)o2)->value;
		}
		f_struct_compare fcmp = knh_tstruct_fcompare(knh_Object_topsid(o1));
		DEBUG_ASSERT(fcmp != NULL);
		return fcmp(ctx, (Struct*)o1, (Struct*)o2);
	}
	DEBUG("%s - %s", CLASSN(cid), CLASSN(cid2));	
	return (knh_int_t)o1 - (knh_int_t)o2;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_Object_equals(Ctx *ctx, Object *o1, Object *o2)
{
	return (knh_Object_compare(ctx, o1, o2) == 0); 
}


/* ======================================================================== */
/* [operators] */

/* @method[STATIC] Bool Object.opEq(Any value) */

void knh__Object_opEq(Ctx *ctx, Object **sfp)
{
	if(knh_Object_compare(ctx, sfp[0], sfp[1]) == 0) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool Object.opNeq(Any value) */

void knh__Object_opNeq(Ctx *ctx, Object **sfp)
{
	if(knh_Object_compare(ctx, sfp[0], sfp[1]) == 0) {
		VM_RET(ctx, KNH_FALSE);
	}
	else {
		VM_RET(ctx, KNH_TRUE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool Object.opLt(Any value) */

void knh__Object_opLt(Ctx *ctx, Object **sfp)
{
	if(knh_Object_compare(ctx, sfp[0], sfp[1]) < 0) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool Object.opLte(Any value) */

void knh__Object_opLte(Ctx *ctx, Object **sfp)
{
	if(knh_Object_compare(ctx, sfp[0], sfp[1]) <= 0) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool Object.opGt(Any value) */

void knh__Object_opGt(Ctx *ctx, Object **sfp)
{
	if(knh_Object_compare(ctx, sfp[0], sfp[1]) > 0) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool Object.opGte(Any value) */

void knh__Object_opGte(Ctx *ctx, Object **sfp)
{
	if(knh_Object_compare(ctx, sfp[0], sfp[1]) >= 0) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool Object.opNot() */

void knh__Object_opNot(Ctx *ctx, Object **sfp)
{
	if(!(IS_TRUE(sfp[0]))) {
		VM_RET(ctx, KNH_TRUE);
	}
	else {
		VM_RET(ctx, KNH_FALSE);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool Object.opSeq(Any value) */

void knh__Object_opSeq(Ctx *ctx, Object **sfp)
{
	TODO();
	VM_RET(ctx, KNH_FALSE);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Bool Object.opIsMapTo(Any value) */

void knh__Object_opIsMapTo(Ctx *ctx, Object **sfp)
{
	TODO();
	VM_RET(ctx, KNH_FALSE);
}

/* ======================================================================== */
/* [mapping] */

/* @map Object Iterator! */

Object* knh_Object_Iterator(Ctx *ctx, Object *self, MapMap *map)
{
	return new_Iterator(ctx, knh_Object_cid(self), self, NULL);
}

/* ------------------------------------------------------------------------ */
/* @map Object String! */

Object* knh_Object_String(Ctx *ctx, Object *self, MapMap *map)
{
	return knh_Object_movableText(ctx, self, METHODN__s, KNH_NULL);
}

///* ------------------------------------------------------------------------ */
///* @method void Object.save(Int lv=0) */
//
//void knh_Object_save(Ctx *ctx, Object *b, knh_int_t lv)
//{
//	TODO();
//}

/* ======================================================================== */
/* [movabletext] */

/* @method void Object.%s(OutputStream w, Any m) */

INLINE
void knh_Object__s(Ctx *ctx, Object *b, OutputStream *w, Any *m)
{
	if(IS_NULL(b)) {
		knh_write(ctx, w, STEXT("null"));
	}
	else {
		knh_write__s(ctx,w, CLASSN(knh_Object_cid(b)));
		knh_write(ctx,w, STEXT(":"));
		knh_write__p(ctx,w, (void*)b);
	}
}

/* ------------------------------------------------------------------------ */

/* @method void Object.%dump(OutputStream w=new, Any m) */

INLINE
void knh_Object__dump(Ctx *ctx, Object *b, OutputStream *w, Any *m)
{
	knh_class_t cid = knh_Object_cid(b);
	if(cid < KONOHA_TSTRUCT_SIZE) {
		knh_format(ctx, w, METHODN__s, b, KNH_NULL);
		return ;
	}
	knh_int_t i, c = 0;
	knh_putc(ctx, w, '[');
	for(i = 0; i < knh_tclass_bsize(cid); i++) {
		knh_cfield_t *cf = knh_Class_fieldAt(cid, i);
		if(cf->fn == FIELDN_NONAME || KNH_FLAG_IS(cf->flag, KNH_FLAG_CFF_HIDDEN)) continue;
		if(c > 0) {
			knh_write_delim(ctx, w);
		}
		knh_printf(ctx, w, "%s=", /* cf->type, */ FIELDN(cf->fn));
		Object *v = KNH_FIELDn(b, i);
		if(STRUCT_IS_String(v)) {
			knh_format(ctx, w, METHODN__dump, v, KNH_NULL);
		}
		else {
			knh_format(ctx, w, METHODN__s, v, KNH_NULL);
		}
		c++;
	}
	knh_putc(ctx, w, ']');
}

/* ------------------------------------------------------------------------ */
/* @method void Object.%empty(OutputStream w=new, Any m) */

INLINE
void knh_Object__empty(Ctx *ctx, Object *b, OutputStream *w, Any *m)
{
	
}

/* ------------------------------------------------------------------------ */
/* @method void Object.%refc(OutputStream w=new, Any m) */

INLINE
void knh_Object__refc(Ctx *ctx, Object *b, OutputStream *w, Any *m)
{
	knh_write__u(ctx, w, knh_Object_head(b)->refc);
}

/* ------------------------------------------------------------------------ */
/* @method void Object.%addr(OutputStream w=new, Any m) */

INLINE
void knh_Object__addr(Ctx *ctx, Object *b, OutputStream *w, Any *m)
{
	knh_write__p(ctx, w, (void*)b);
}


#ifdef __cplusplus
}
#endif
