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

#define _knh_Float_value(o)    (o)->value

/* ======================================================================== */
/* [FloatUnit] */

static
int knh_funitcmp__step(FloatUnit *b, knh_float_t v1, knh_float_t v2)
{
	knh_float_t delta = v1 - v2, step = DP(b)->step;
	if(-step < delta && step < delta) return 0;
	return delta < 0 ? -1 : 1;
}

/* ------------------------------------------------------------------------ */

static
void knh_FloatUnit_initStep(Ctx *ctx, FloatUnit *b, knh_float_t step)
{
	DP(b)->step = step;
	if(DP(b)->step == 0.0) {
		return;
	}
	DP(b)->fcmp = knh_funitcmp__step;
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

static
knh_bool_t knh_funitchk__min(FloatUnit *b, knh_float_t v)
{
	return (DP(b)->min <= v);
}

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_funitchk__max(FloatUnit *b, knh_float_t v)
{
	return (v <= DP(b)->max);
}

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_funitchk__range(FloatUnit *b, knh_float_t v)
{
	return (DP(b)->min <= v && v <= DP(b)->max);
}

/* ------------------------------------------------------------------------ */

static
void knh_FloatUnit_initMinMax(Ctx *ctx, FloatUnit *b, knh_float_t min, knh_float_t max)
{
	KNH_ASSERT(min <= max);
	DP(b)->min = min;
	DP(b)->max = max;
	if(DP(b)->min == KNH_FLOAT_MIN) {
		if(DP(b)->max == KNH_FLOAT_MAX) {
			//DEBUG("*min=%f, *max=%f", min, max);
		}
		else {
			DP(b)->fchk = knh_funitchk__max;
			//DEBUG("min=%f, *max=%f", min, max);
		}
	}
	else {
		if(DP(b)->max == KNH_FLOAT_MAX) {
			DP(b)->fchk = knh_funitchk__min;
			//DEBUG("*min=%f, max=%f", min, max);
		}
		else {
			DP(b)->fchk = knh_funitchk__range;
			//DEBUG("*min=%f, max=%f", min, max);
		}
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_FloatUnit_initDefaultValue(Ctx *ctx, FloatUnit *b, knh_float_t v)
{
	if(!DP(b)->fchk(b, v)) {
		v = DP(b)->min;
	}
	KNH_SETv(ctx, DP(b)->spec.defvalue, new_FloatX__fast(ctx, DP(b)->spec.cid, v));
}

/* ------------------------------------------------------------------------ */

FloatUnit *new_FloatUnit(Ctx *ctx, knh_flag_t flag, knh_class_t cid, String *tag, knh_float_t min, knh_float_t max, knh_float_t defvalue, knh_float_t step)
{
	FloatUnit* o = (FloatUnit*)new_Object_bcid(ctx, CLASS_FloatUnit, 0);
	DP(o)->spec.flag = flag;
	DP(o)->spec.cid  = cid;
	KNH_SETv(ctx, DP(o)->spec.tag,  tag);
	knh_FloatUnit_initStep(ctx, o, step);
	knh_FloatUnit_initMinMax(ctx, o, min, max);
	knh_FloatUnit_initDefaultValue(ctx, o, defvalue);
	return o;
}

/* ------------------------------------------------------------------------ */

KNHAPI(ClassSpec*) new_Unit(Ctx *ctx, char *tag, knh_float_t min, knh_float_t max, knh_float_t defv, knh_float_t step)
{
	knh_class_t cid = knh_ClassTable_newId(ctx);
	FloatUnit *fu = new_FloatUnit(ctx, 0, cid, new_String__T(ctx, tag), min, max, defv, step);
	return (ClassSpec*)fu;
}

/* ======================================================================== */
/* [Float] */

Float* new_Float(Ctx *ctx, knh_float_t value)
{
	Float *b = (Float*)new_hObject(ctx, FLAG_Float, CLASS_Float, CLASS_Float);
	b->n.fvalue = value;
	return b;
}

/* ------------------------------------------------------------------------ */

Float* new_FloatX__fast(Ctx *ctx, knh_class_t cid, knh_float_t value)
{
	Float *b = (Float*)new_hObject(ctx, FLAG_Float, CLASS_Float, cid);
	b->n.fvalue = value;
	return b;
}

/* ------------------------------------------------------------------------ */

Float* new_FloatX(Ctx *ctx, knh_class_t cid, knh_float_t value)
{
	KNH_ASSERT_cid(cid);
	FloatUnit *o = (FloatUnit*)ctx->share->ClassTable[cid].cspec;
	KNH_ASSERT(IS_FloatUnit(o));
	if(DP(o)->fchk(o, value)) {
		Float *f = (Float*)new_hObject(ctx, FLAG_Float, CLASS_Float, cid);
		f->n.fvalue = value;
		return f;
	}
	else {
		char buf[CLASSNAME_BUFSIZ];
		knh_snprintf(buf, sizeof(buf), "Format!!: %s(" KNH_FLOAT_FMT ")", CLASSN(cid), value);
		DBG2_P("%s", buf);
		return (Float*)new_Nue__s(ctx, buf);
	}
}



///* ------------------------------------------------------------------------ */
//
//char *knh_format_Float(char *buf, size_t bufsiz, Float *o)
//{
//	FloatUnit *fu = (FloatUnit*)ctx->share->ClassTable[o->h.cid].cspec;
//	KNH_ASSERT(IS_FloatUnit(fu));
//	DP(fu)->ffmt(fu, buf, bufsiz, o->n.fvalue);
//	return buf;
//}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
