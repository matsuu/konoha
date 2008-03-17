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

/* ------------------------------------------------------------------------ */

#ifndef KNH_INTUNIT_BUFSIZ
#define KNH_INTUNIT_BUFSIZ   256
#endif

#define knh_IntUnit_isBuffered(b,n)   (b->bfarray != NULL && b->bfoffset <= n && n < b->bfoffset + b->bfsize)

/* ======================================================================== */
/* [structs] */

void
knh_IntUnit_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	IntUnit *b =  (IntUnit*)s1;
	b->spec.flag = 0;
	b->spec.cid  = CLASS_Int;
	KNH_INITv(b->spec.urn,  knh_String_EMPTY());
	KNH_INITv(b->spec.tag,  knh_String_EMPTY());
	KNH_INITv(b->spec.defvalue, new_Int__fast(ctx, CLASS_Int, 0));
	//
	b->step = 1;
	b->max  = KNH_INT_MAX;
	b->min  = KNH_INT_MIN;
	b->fchk = knh_IntUnit_fchk__nop;
	b->fcmp = knh_IntUnit_fcmp__signed;
	b->ffmt = knh_IntUnit_ffmt__signed;
	b->bfoffset = 0;
	b->bfsize = 0;
	b->bfarray = NULL;	
}

/* ------------------------------------------------------------------------ */

#define _knh_IntUnit_struct_copy    NULL

/* ------------------------------------------------------------------------ */

#define _knh_IntUnit_struct_compare NULL

/* ------------------------------------------------------------------------ */

void
knh_IntUnit_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	IntUnit *b = (IntUnit*)s;
	gc(ctx, b->spec.urn);
	gc(ctx, b->spec.tag);
	gc(ctx, b->spec.defvalue);

	if(IS_SWEEP(gc)) {
		if(b->bfarray != NULL) {
			knh_oarray_traverse(ctx, b->bfarray, b->bfsize, gc);
		}
	}
}

/* ======================================================================== */
/* [fvalue] */

Object *knh_intunit_fvalue(Ctx *ctx, knh_class_t cid)
{
	return ((IntUnit*)knh_tclass_spec(cid))->spec.defvalue;
}

/* ======================================================================== */
/* [constructors] */

IntUnit *new_IntUnit__STEXT(Ctx *ctx, knh_flag_t flag, knh_class_t cid, char *urn, char *tag, knh_int_t min, knh_int_t max, knh_int_t defvalue, knh_int_t bf_start, knh_int_t bf_end)
{
	IntUnit* b = (IntUnit*)knh_Object_malloc0(ctx, KNH_FLAG_IntUnit, CLASS_IntUnit, sizeof(IntUnit));
	knh_IntUnit_struct_init(ctx, (Struct*)b, 0, NULL);

	b->spec.flag = flag;
	b->spec.cid  = cid;
	if(urn != NULL) {
		KNH_SETv(ctx, b->spec.urn,  new_String__fast(ctx, CLASS_String__urn, B(urn)));
	}
	if(tag != NULL) {
		KNH_SETv(ctx, b->spec.tag,  new_String__fast(ctx, CLASS_String, B(tag)));
	}
	knh_IntUnit_initMinMax(ctx, b, min, max);
	knh_IntUnit_init_bfarray(ctx, b, bf_start, bf_end);
	knh_IntUnit_initDefaultValue(ctx, b, defvalue);
	return b;
}

/* ======================================================================== */
/* [spec] */

INLINE
IntUnit* knh_tclass_getIntUnit(Ctx *ctx, knh_class_t cid)
{
	KNH_ASSERT(IS_IntUnit(knh_tclass_spec(cid)));
	return (IntUnit*)knh_tclass_spec(cid);
}

/* ------------------------------------------------------------------------ */

IntUnit *knh_Int_spec(Ctx *ctx)
{
	return new_IntUnit__STEXT(ctx, 0, CLASS_Int, NULL, NULL, KNH_INT_MIN, KNH_INT_MAX, 0, -1, 256);
}

/* ------------------------------------------------------------------------ */

knh_class_t
KNH_TENUM(Ctx *ctx, char *urn, char *tag, knh_int_t min, knh_int_t max, knh_int_t defv, knh_int_t bf_start, knh_int_t bf_end)
{
	knh_class_t cid = knh_tclass_newId(ctx);
	IntUnit *u = new_IntUnit__STEXT(ctx, 0, cid, urn, tag, min, max, defv, bf_start, bf_end);
	KNH_TCLASS_SPEC(ctx, CLASS_Int, u);
	return cid;
}

/* ======================================================================== */
/* [set] */

void knh_IntUnit_initId(Ctx *ctx, IntUnit *b, knh_flag_t flag, knh_class_t cid, String *urn, String *tag)
{
	DEBUG_ASSERT(IS_NOTNULL(urn));
	DEBUG_ASSERT(IS_NOTNULL(tag));

	b->spec.flag = flag;
	b->spec.cid  = cid;
	KNH_SETv(ctx, b->spec.urn, urn);
	KNH_SETv(ctx, b->spec.tag, tag);

	if(knh_IntUnit_isUnsigned(b)) {
		b->max  = KNH_UINT_MAX;
		b->min  = KNH_UINT_MIN;
		b->fchk = knh_IntUnit_fchk__nop;
		b->fcmp = knh_IntUnit_fcmp__unsigned;
		b->ffmt = knh_IntUnit_ffmt__unsigned;
	}
}

/* ------------------------------------------------------------------------ */

void knh_IntUnit_initMinMax(Ctx *ctx, IntUnit *b, knh_int_t min, knh_int_t max)
{
	b->min = min;
	b->max = max;
	if(knh_IntUnit_isUnsigned(b)) {
		b->fcmp = knh_IntUnit_fcmp__unsigned;
		b->ffmt = knh_IntUnit_ffmt__unsigned;
		if(b->min == KNH_UINT_MIN) {
			if(b->max == KNH_UINT_MAX) {
				DEBUG_ASSERT(b->fchk == knh_IntUnit_fchk__nop);
			}
			else {
				b->fchk = knh_IntUnit_fchk__unsigned_max;
			}
		}
		else {
			if(b->max == KNH_UINT_MAX) {
				b->fchk = knh_IntUnit_fchk__unsigned_min;
			}
			else {
				b->fchk = knh_IntUnit_fchk__unsigned;
			}
		}
	}
	else {
		if(b->min == KNH_INT_MIN) {
			if(b->max == KNH_INT_MAX) {
				DEBUG_ASSERT(b->fchk == knh_IntUnit_fchk__nop);
			}
			else {
				b->fchk = knh_IntUnit_fchk__signed_max;
			}
		}
		else {
			if(b->max == KNH_INT_MAX) {
				b->fchk = knh_IntUnit_fchk__signed_min;
			}
			else {
				b->fchk = knh_IntUnit_fchk__signed;
			}
		}
	}
}

/* ------------------------------------------------------------------------ */

void knh_IntUnit_init_bfarray(Ctx *ctx, IntUnit *b, knh_int_t bf_start, knh_int_t bf_end)
{
	if(bf_start < bf_end) {
		DEBUG_ASSERT(b->bfarray == NULL);
		b->bfoffset  = bf_start;
		b->bfsize    = bf_end - bf_start + 1;
		b->bfarray  = knh_oarray_malloc(ctx, b->bfsize, KNH_NULL);
		knh_int_t i;
		for(i = bf_start; i <= bf_end; i++) {
			KNH_SETv(ctx, b->bfarray[i - bf_start], new_Int__fast(ctx, b->spec.cid, i));	
		}
	}
}

/* ------------------------------------------------------------------------ */

void knh_IntUnit_initDefaultValue(Ctx *ctx, IntUnit *b, knh_int_t v)
{
	if(!b->fchk(b, v)) {
		v = b->min;
	}
	if(knh_IntUnit_isBuffered(b, v)) {
		KNH_SETv(ctx, b->spec.defvalue, b->bfarray[v - b->bfoffset]);
	}else {
		KNH_SETv(ctx, b->spec.defvalue, new_Int__fast(ctx, b->spec.cid, v));
	}
}


/* ======================================================================== */
/* [methods] */

INLINE
knh_bool_t knh_IntUnit_check(IntUnit *b, knh_int_t value)
{
	return b->fchk(b, value);
}

/* ------------------------------------------------------------------------ */

Int *new_Nue__asInt(Ctx *ctx, knh_class_t cid, knh_int_t value)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), "Type!!: " KNH_INT_FMT " is not in %s", value, CLASSN(cid));
	return (Int*)new_Nue(ctx, new_String__fast(ctx, CLASS_String, B(buf))); 
}

/* ------------------------------------------------------------------------ */

Int *new_Nue__asuInt(Ctx *ctx, knh_class_t cid, knh_uint_t value)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), "Type!!: " KNH_UINT_FMT " is not in %s", value, CLASSN(cid));
	return (Int*)new_Nue(ctx, new_String__fast(ctx, CLASS_String, B(buf))); 
}

/* ------------------------------------------------------------------------ */

Int *new_Int__checked(Ctx *ctx, knh_class_t cid, knh_int_t value)
{
	IntUnit *b = knh_tclass_getIntUnit(ctx, cid);

	if(knh_IntUnit_isBuffered(b, value)) {
		return b->bfarray[value - b->bfoffset];
	}

	if(IntCache(ctx) != NULL) {
		Int *n = (Int*)knh_LRUMap_get(ctx, IntCache(ctx), value, NULL);
		if(IS_NOTNULL(n)) {
//			DEBUG("get n = %d", n->value);
			DEBUG_ASSERT(n->value == value);
			return n;
		}
	}

	if(!knh_IntUnit_check(b, value)) {
		if(knh_IntUnit_isUnsigned(b)) {
			return new_Nue__asuInt(ctx, b->spec.cid, (knh_uint_t)value);
		}else {
			return new_Nue__asInt(ctx, b->spec.cid, value);
		}
	}

	/* generating an instance */
	Int *n = new_Int__fast(ctx, b->spec.cid, value);
	if(IntCache(ctx) != NULL) {
		DEBUG("set n = %ld", n->value);
		knh_LRUMap_set(ctx, IntCache(ctx), value, NULL, n);
	}
	return n;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_int_t knh_IntUnit_compare(IntUnit *b, knh_int_t v1, knh_int_t v2)
{
	return b->fcmp(b, v1, v2);
}

/* ------------------------------------------------------------------------ */

INLINE
void knh_IntUnit_format(IntUnit *b, char *buf, knh_int_t v)
{
	b->ffmt(b, buf, v);
}

/* ------------------------------------------------------------------------ */

INLINE
void knh_IntUnit_format_unit(IntUnit *b, char *buf)
{
	TODO();
}

/* ======================================================================== */
/* [default_func] */

knh_bool_t knh_IntUnit_fchk__nop(IntUnit *b, knh_int_t v)
{
	return 1;
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_IntUnit_fcmp__signed(IntUnit *b, knh_int_t v1, knh_int_t v2)
{
	return v1 - v2;
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_IntUnit_fcmp__unsigned(IntUnit *b, knh_int_t v1, knh_int_t v2)
{
	if(v1 == v2) return 0;
	return ((knh_uint_t)v1) > ((knh_uint_t)v2) ? 1 : 0;
}

/* ------------------------------------------------------------------------ */

void knh_IntUnit_ffmt__signed(IntUnit *b, char *buf, knh_int_t v)
{
	knh_snprintf(buf, KNH_INTUNIT_BUFSIZ, KNH_INT_FMT, v); 	
}

/* ------------------------------------------------------------------------ */

void knh_IntUnit_ffmt__unsigned(IntUnit *b, char *buf, knh_int_t v)
{
	knh_snprintf(buf, KNH_INTUNIT_BUFSIZ, KNH_UINT_FMT, (knh_uint_t)v); 
}

/* ======================================================================== */
/* [range] */

knh_bool_t knh_IntUnit_fchk__signed_min(IntUnit *b, knh_int_t v)
{
	return (b->min <= v);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_IntUnit_fchk__signed_max(IntUnit *b, knh_int_t v)
{
	return (v <= b->max);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_IntUnit_fchk__signed(IntUnit *b, knh_int_t v)
{
	return (b->min <= v && v <= b->max);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_IntUnit_fchk__unsigned_min(IntUnit *b, knh_int_t v)
{
	return ((knh_uint_t)b->min) <= ((knh_uint_t)v);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_IntUnit_fchk__unsigned_max(IntUnit *b, knh_int_t v)
{
	return ((knh_uint_t)v) <= ((knh_uint_t)b->max);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_IntUnit_fchk__unsigned(IntUnit *b, knh_int_t v)
{
	return (((knh_uint_t)b->min) <= ((knh_uint_t)v) && ((knh_uint_t)v) <= ((knh_uint_t)b->max));
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
