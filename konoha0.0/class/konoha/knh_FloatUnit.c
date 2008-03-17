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

#ifndef KNH_FLOATUNIT_BUFSIZ
#define KNH_FLOATUNIT_BUFSIZ   256
#endif

/* ======================================================================== */
/* [structs] */

void
knh_FloatUnit_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	FloatUnit *b =  (FloatUnit*)s1;
	b->spec.flag = 0;
	b->spec.cid  = CLASS_Float;
	KNH_INITv(b->spec.urn,  knh_String_EMPTY());
	KNH_INITv(b->spec.tag,  knh_String_EMPTY());
	KNH_INITv(b->spec.defvalue, new_Float__fast(ctx, CLASS_Float, 0.0));
	//
	b->step = 0.0;
	b->max  = KNH_FLOAT_MAX;
	b->min  = KNH_FLOAT_MIN;
	b->fchk = knh_FloatUnit_fchk__default;
	b->fcmp = knh_FloatUnit_fcmp__default;
	b->ffmt = knh_FloatUnit_ffmt__default;
	b->FMT  = KNH_FLOAT_FMT;
}

/* ------------------------------------------------------------------------ */

#define _knh_FloatUnit_struct_copy    NULL

/* ------------------------------------------------------------------------ */

#define _knh_FloatUnit_struct_compare NULL

/* ------------------------------------------------------------------------ */

void
knh_FloatUnit_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	FloatUnit *b = (FloatUnit*)s;
	gc(ctx, b->spec.urn);
	gc(ctx, b->spec.tag);
	gc(ctx, b->spec.defvalue);
}

/* ======================================================================== */
/* [constructors] */

FloatUnit *new_FloatUnit__STEXT(Ctx *ctx, knh_flag_t flag, knh_class_t cid, char *urn, char *tag, knh_float_t min, knh_float_t max, knh_float_t defvalue, knh_float_t step)
{
	FloatUnit* b = (FloatUnit*)knh_Object_malloc0(ctx, KNH_FLAG_FloatUnit, CLASS_FloatUnit, sizeof(FloatUnit));
	knh_FloatUnit_struct_init(ctx, (Struct*)b, 0, NULL);

	b->spec.flag = flag;
	b->spec.cid  = cid;
	if(urn != NULL) {
		KNH_SETv(ctx, b->spec.urn,  new_String__fast(ctx, CLASS_String__urn, B(urn)));
	}
	if(tag != NULL) {
		KNH_SETv(ctx, b->spec.tag,  new_String__fast(ctx, CLASS_String, B(tag)));
	}
	knh_FloatUnit_initStep(ctx, b, step);
	knh_FloatUnit_initMinMax(ctx, b, min, max);
	knh_FloatUnit_initDefaultValue(ctx, b, defvalue);
	return b;
}

/* ======================================================================== */
/* [tclass] */

FloatUnit* knh_tclass_getFloatUnit(Ctx *ctx, knh_class_t cid)
{
	KNH_ASSERT(IS_FloatUnit(knh_tclass_spec(cid)));
	return (FloatUnit*)knh_tclass_spec(cid);
}

/* ------------------------------------------------------------------------ */

FloatUnit *knh_Float_spec(Ctx *ctx)
{
	return new_FloatUnit__STEXT(ctx, 0, CLASS_Float, NULL, NULL, KNH_FLOAT_MIN, KNH_FLOAT_MAX, 0.0, 0.0);
}

/* ------------------------------------------------------------------------ */

knh_class_t
KNH_TUNIT(Ctx *ctx, char *urn, char *tag, knh_float_t min, knh_float_t max, knh_float_t defv, knh_float_t step)
{
	knh_class_t cid = knh_tclass_newId(ctx);
	FloatUnit *fu = new_FloatUnit__STEXT(ctx, 0, cid, urn, tag, min, max, defv, step);
	KNH_TCLASS_SPEC(ctx, CLASS_Float, fu);
	return cid;
}

/* ======================================================================== */
/* [set] */

void knh_FloatUnit_initId(Ctx *ctx, FloatUnit *b, knh_flag_t flag, knh_class_t cid, String *urn, String *tag)
{
	DEBUG_ASSERT(IS_NOTNULL(urn));
	DEBUG_ASSERT(IS_NOTNULL(tag));

	b->spec.flag = flag;
	b->spec.cid  = cid;
	KNH_SETv(ctx, b->spec.urn, urn);
	KNH_SETv(ctx, b->spec.tag, tag);
}

/* ------------------------------------------------------------------------ */

void knh_FloatUnit_initStep(Ctx *ctx, FloatUnit *b, knh_float_t step)
{
	b->step = step;
	if(b->step == 0.0) {
		b->fcmp = knh_FloatUnit_fcmp__default;
		return;
	}
	b->fcmp = knh_FloatUnit_fcmp__step;
	if(0.1 <= step && step < 1.0) {
		b->FMT = KNH_FLOAT_FMT1;
	}
	else if(0.01 <= step && step < 0.1) {
		b->FMT = KNH_FLOAT_FMT2;
	}
	else if(0.001 <= step && step < 0.01) {
		b->FMT = KNH_FLOAT_FMT3;
	}
	else if(0.0001 <= step && step < 0.001) {
		b->FMT = KNH_FLOAT_FMT4;
	}
}

/* ------------------------------------------------------------------------ */

void knh_FloatUnit_initMinMax(Ctx *ctx, FloatUnit *b, knh_float_t min, knh_float_t max)
{
	DEBUG_ASSERT(min <= max);
	b->min = min;
	b->max = max;
	if(b->min == KNH_FLOAT_MIN) {
		if(b->max == KNH_FLOAT_MAX) {
			DEBUG_ASSERT(b->fchk == knh_FloatUnit_fchk__default);
			//DEBUG("*min=%f, *max=%f", min, max);
		}
		else {
			b->fchk = knh_FloatUnit_fchk__max;
			//DEBUG("min=%f, *max=%f", min, max);
		}
	}
	else {
		if(b->max == KNH_FLOAT_MAX) {
			b->fchk = knh_FloatUnit_fchk__min;
			//DEBUG("*min=%f, max=%f", min, max);
		}
		else {
			b->fchk = knh_FloatUnit_fchk__range;
			//DEBUG("*min=%f, max=%f", min, max);
		}
	}
}

/* ------------------------------------------------------------------------ */

void knh_FloatUnit_initDefaultValue(Ctx *ctx, FloatUnit *b, knh_float_t v)
{
	if(!b->fchk(b, v)) {
		v = b->min;
	}
	KNH_SETv(ctx, b->spec.defvalue, new_Float__fast(ctx, b->spec.cid, v));
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_FloatUnit_check(FloatUnit *b, knh_int_t value)
{
	return b->fchk(b, value);
}

/* ------------------------------------------------------------------------ */

Float *new_Nue__asFloat(Ctx *ctx, knh_class_t cid, knh_float_t value)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), "Type!!: " KNH_FLOAT_FMT " is not in %s", value, CLASSN(cid));
	DEBUG("%s", buf);
	return (Float*)new_Nue(ctx, new_String__fast(ctx, CLASS_String, B(buf))); 
}

/* ------------------------------------------------------------------------ */

Float *knh_FloatUnit_value(Ctx *ctx, FloatUnit *b, knh_float_t value)
{
	if(!knh_FloatUnit_check(b, value)) {
		return new_Nue__asFloat(ctx, b->spec.cid, value);
	}
	return new_Float__fast(ctx, b->spec.cid, value);
}

/* ------------------------------------------------------------------------ */

INLINE
knh_int_t knh_FloatUnit_compare(FloatUnit *b, knh_float_t v1, knh_float_t v2)
{
	return b->fcmp(b, v1, v2);
}

/* ------------------------------------------------------------------------ */

INLINE
void knh_FloatUnit_format(FloatUnit *b, char *buf, knh_float_t v)
{
	b->ffmt(b, buf, v);
}

/* ======================================================================== */
/* [default_func] */

knh_bool_t knh_FloatUnit_fchk__default(FloatUnit *b, knh_float_t v)
{
	return 1;
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_FloatUnit_fcmp__default(FloatUnit *b, knh_float_t v1, knh_float_t v2)
{
	return v1 - v2;
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_FloatUnit_fcmp__step(FloatUnit *b, knh_float_t v1, knh_float_t v2)
{
	knh_float_t delta = v1 - v2;
	if(delta < 0.0) delta = -delta;
	if(delta < b->step) return 0;
	return v1 - v2;
}

/* ------------------------------------------------------------------------ */

void knh_FloatUnit_ffmt__default(FloatUnit *b, char *buf, knh_float_t v)
{
	knh_snprintf(buf, KNH_FLOATUNIT_BUFSIZ, KNH_FLOAT_FMT, v);	
}

/* ======================================================================== */
/* [range] */

knh_bool_t knh_FloatUnit_fchk__min(FloatUnit *b, knh_float_t v)
{
	return (b->min <= v);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_FloatUnit_fchk__max(FloatUnit *b, knh_float_t v)
{
	return (v <= b->max);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_FloatUnit_fchk__range(FloatUnit *b, knh_float_t v)
{
	return (b->min <= v && v <= b->max);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
