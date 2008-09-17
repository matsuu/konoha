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

/* ======================================================================== */
/* [private functions] */

static knh_bool_t knh_FloatUnit_fchk__default(FloatUnit *b, knh_float_t v);
static knh_int_t knh_FloatUnit_fcmp__default(FloatUnit *b, knh_float_t v1, knh_float_t v2);
static knh_int_t knh_FloatUnit_fcmp__step(FloatUnit *b, knh_float_t v1, knh_float_t v2);
static void knh_FloatUnit_ffmt__default(FloatUnit *b, char *buf, size_t bufsiz, knh_float_t v);
static knh_bool_t knh_FloatUnit_fchk__min(FloatUnit *b, knh_float_t v);
static knh_bool_t knh_FloatUnit_fchk__max(FloatUnit *b, knh_float_t v);
static knh_bool_t knh_FloatUnit_fchk__range(FloatUnit *b, knh_float_t v);

/* ======================================================================== */
/* [structs] */

void
knh_FloatUnit_struct_init(Ctx *ctx, knh_FloatUnit_struct *b, int init, Object *cs)
{
	b->spec.flag = 0;
	b->spec.cid  = CLASS_Float;
	KNH_INITv(b->spec.urn,  TS_EMPTY);
	KNH_INITv(b->spec.tag,  TS_EMPTY);
	KNH_INITv(b->spec.defvalue, new_FloatX0(ctx, CLASS_Float, 0.0));
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
knh_FloatUnit_struct_traverse(Ctx *ctx, knh_FloatUnit_struct *b, f_traverse gc)
{
	gc(ctx, UP(b->spec.urn));
	gc(ctx, UP(b->spec.tag));
	gc(ctx, b->spec.defvalue);
}

/* ======================================================================== */
/* [constructors] */

FloatUnit *new_FloatUnit(Ctx *ctx, knh_flag_t flag, knh_class_t cid, String *urn, String *tag, knh_float_t min, knh_float_t max, knh_float_t defvalue, knh_float_t step)
{
	FloatUnit* o = (FloatUnit*)new_Object_malloc(ctx, FLAG_FloatUnit, CLASS_FloatUnit, sizeof(knh_FloatUnit_struct));
	knh_FloatUnit_struct_init(ctx, DP(o), 0, NULL);
	DP(o)->spec.flag = flag;
	DP(o)->spec.cid  = cid;
	KNH_SETv(ctx, DP(o)->spec.urn,  urn);
	KNH_SETv(ctx, DP(o)->spec.tag,  tag);
	knh_FloatUnit_initStep(ctx, o, step);
	knh_FloatUnit_initMinMax(ctx, o, min, max);
	knh_FloatUnit_initDefaultValue(ctx, o, defvalue);
	return o;
}

/* ======================================================================== */
/* [tclass] */

//knh_class_t
//KNH_TUNIT(Ctx *ctx, char *urn, char *tag, knh_float_t min, knh_float_t max, knh_float_t defv, knh_float_t step)
//{
//	knh_class_t cid = knh_tclass_newId(ctx);
//	FloatUnit *fu = new_FloatUnit__STEXT(ctx, 0, cid, urn, tag, min, max, defv, step);
//	KNH_TCLASS_SPEC(ctx, CLASS_Float, fu);
//	return cid;
//}

/* ======================================================================== */
/* [set] */

void knh_FloatUnit_initId(Ctx *ctx, FloatUnit *b, knh_flag_t flag, knh_class_t cid, String *urn, String *tag)
{
	KNH_ASSERT(IS_NOTNULL(urn));
	KNH_ASSERT(IS_NOTNULL(tag));

	DP(b)->spec.flag = flag;
	DP(b)->spec.cid  = cid;
	KNH_SETv(ctx, DP(b)->spec.urn, urn);
	KNH_SETv(ctx, DP(b)->spec.tag, tag);
}

/* ------------------------------------------------------------------------ */

void knh_FloatUnit_initStep(Ctx *ctx, FloatUnit *b, knh_float_t step)
{
	DP(b)->step = step;
	if(DP(b)->step == 0.0) {
		DP(b)->fcmp = knh_FloatUnit_fcmp__default;
		return;
	}
	DP(b)->fcmp = knh_FloatUnit_fcmp__step;
	if(0.1 <= step && step < 1.0) {
		DP(b)->FMT = KNH_FLOAT_FMT1;
	}
	else if(0.01 <= step && step < 0.1) {
		DP(b)->FMT = KNH_FLOAT_FMT2;
	}
	else if(0.001 <= step && step < 0.01) {
		DP(b)->FMT = KNH_FLOAT_FMT3;
	}
	else if(0.0001 <= step && step < 0.001) {
		DP(b)->FMT = KNH_FLOAT_FMT4;
	}
}

/* ------------------------------------------------------------------------ */

void knh_FloatUnit_initMinMax(Ctx *ctx, FloatUnit *b, knh_float_t min, knh_float_t max)
{
	KNH_ASSERT(min <= max);
	DP(b)->min = min;
	DP(b)->max = max;
	if(DP(b)->min == KNH_FLOAT_MIN) {
		if(DP(b)->max == KNH_FLOAT_MAX) {
			KNH_ASSERT(DP(b)->fchk == knh_FloatUnit_fchk__default);
			//DEBUG("*min=%f, *max=%f", min, max);
		}
		else {
			DP(b)->fchk = knh_FloatUnit_fchk__max;
			//DEBUG("min=%f, *max=%f", min, max);
		}
	}
	else {
		if(DP(b)->max == KNH_FLOAT_MAX) {
			DP(b)->fchk = knh_FloatUnit_fchk__min;
			//DEBUG("*min=%f, max=%f", min, max);
		}
		else {
			DP(b)->fchk = knh_FloatUnit_fchk__range;
			//DEBUG("*min=%f, max=%f", min, max);
		}
	}
}

/* ------------------------------------------------------------------------ */

void knh_FloatUnit_initDefaultValue(Ctx *ctx, FloatUnit *b, knh_float_t v)
{
	if(!DP(b)->fchk(b, v)) {
		v = DP(b)->min;
	}
	KNH_SETv(ctx, DP(b)->spec.defvalue, new_FloatX0(ctx, DP(b)->spec.cid, v));
}

///* ------------------------------------------------------------------------ */
//
//INLINE
//knh_bool_t knh_FloatUnit_check(FloatUnit *b, knh_int_t value)
//{
//	return DP(b)->fchk(b, value);
//}



/* ------------------------------------------------------------------------ */
/* [Float] */


/* ------------------------------------------------------------------------ */


/* ======================================================================== */
/* [default_func] */

static
knh_bool_t knh_FloatUnit_fchk__default(FloatUnit *b, knh_float_t v)
{
	return 1;
}

/* ------------------------------------------------------------------------ */

static
knh_int_t knh_FloatUnit_fcmp__default(FloatUnit *b, knh_float_t v1, knh_float_t v2)
{
	return v1 - v2;
}

/* ------------------------------------------------------------------------ */

static
knh_int_t knh_FloatUnit_fcmp__step(FloatUnit *b, knh_float_t v1, knh_float_t v2)
{
	knh_float_t delta = v1 - v2;
	if(delta < 0.0) delta = -delta;
	if(delta < DP(b)->step) return 0;
	return v1 - v2;
}

/* ------------------------------------------------------------------------ */

static
void knh_FloatUnit_ffmt__default(FloatUnit *b, char *buf, size_t bufsiz, knh_float_t v)
{
	knh_snprintf(buf, bufsiz, KNH_FLOAT_FMT, v);
}

/* ======================================================================== */
/* [range] */

static
knh_bool_t knh_FloatUnit_fchk__min(FloatUnit *b, knh_float_t v)
{
	return (DP(b)->min <= v);
}

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_FloatUnit_fchk__max(FloatUnit *b, knh_float_t v)
{
	return (v <= DP(b)->max);
}

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_FloatUnit_fchk__range(FloatUnit *b, knh_float_t v)
{
	return (DP(b)->min <= v && v <= DP(b)->max);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
