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
/* [default_func] */

static knh_bool_t knh_IntUnit_fchk__nop(IntUnit *b, knh_int_t v);
static knh_int_t knh_IntUnit_fcmp__signed(IntUnit *b, knh_int_t v1, knh_int_t v2);
static knh_int_t knh_IntUnit_fcmp__unsigned(IntUnit *b, knh_int_t v1, knh_int_t v2);
static void knh_IntUnit_ffmt__signed(IntUnit *b, char *buf, size_t bufsiz, knh_int_t v);
static void knh_IntUnit_ffmt__unsigned(IntUnit *b, char *buf, size_t bufsiz, knh_int_t v);
static knh_bool_t knh_IntUnit_fchk__signed_min(IntUnit *b, knh_int_t v);
static knh_bool_t knh_IntUnit_fchk__signed_max(IntUnit *b, knh_int_t v);
static knh_bool_t knh_IntUnit_fchk__signed(IntUnit *b, knh_int_t v);
static knh_bool_t knh_IntUnit_fchk__unsigned_min(IntUnit *b, knh_int_t v);
static knh_bool_t knh_IntUnit_fchk__unsigned_max(IntUnit *b, knh_int_t v);
static knh_bool_t knh_IntUnit_fchk__unsigned(IntUnit *b, knh_int_t v);

/* ------------------------------------------------------------------------ */

#ifndef KNH_INTUNIT_BUFSIZ
#define KNH_INTUNIT_BUFSIZ   256
#endif

#define _knh_IntUnit_isBuffered(u,n)   (DP(u)->bfarray != NULL && DP(u)->bfoffset <= n && n < DP(u)->bfoffset + DP(u)->bfsize)

/* ======================================================================== */
/* [structs] */

void
knh_IntUnit_struct_init(Ctx *ctx, knh_IntUnit_struct *b, int init, Object *cs)
{
	b->spec.flag = 0;
	b->spec.cid  = CLASS_Int;
	KNH_INITv(b->spec.urn,  TS_EMPTY);
	KNH_INITv(b->spec.tag,  TS_EMPTY);
	KNH_INITv(b->spec.defvalue, knh_tInt[0-KNH_TINT_MIN]);
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
knh_IntUnit_struct_traverse(Ctx *ctx, knh_IntUnit_struct *b, f_traverse gc)
{
	gc(ctx, UP(b->spec.urn));
	gc(ctx, UP(b->spec.tag));
	gc(ctx, b->spec.defvalue);

	if(IS_SWEEP(gc)) {
		if(b->bfarray != NULL && b->spec.cid != CLASS_Int) {
			knh_oarray_traverse(ctx, (Object**)b->bfarray, gc);
		}
		b->bfarray = NULL;
	}
}

/* ======================================================================== */
/* [constructors] */

IntUnit *new_IntUnit(Ctx *ctx, knh_flag_t flag, knh_class_t cid, String *urn, String *tag, knh_int_t min, knh_int_t max, knh_int_t defvalue, knh_int_t bf_start, knh_int_t bf_end)
{
	IntUnit* o = (IntUnit*)new_Object_malloc(ctx, FLAG_IntUnit, CLASS_IntUnit, sizeof(knh_IntUnit_struct));
	knh_IntUnit_struct_init(ctx, DP(o), 0, NULL);

	DP(o)->spec.flag = flag;
	DP(o)->spec.cid  = cid;
	KNH_SETv(ctx, DP(o)->spec.urn,  urn);
	KNH_SETv(ctx, DP(o)->spec.tag,  tag);
	knh_IntUnit_initMinMax(ctx, o, min, max);
	if(cid != CLASS_Int) {
		knh_IntUnit_init_bfarray(ctx, o, bf_start, bf_end);
	}
	else {
		KNH_ASSERT(bf_start == KNH_TINT_MIN && bf_end == KNH_TINT_MAX);
		DP(o)->bfoffset  = bf_start;
		DP(o)->bfsize    = bf_end - bf_start + 1;
		DP(o)->bfarray   = knh_tInt;
	}
	knh_IntUnit_initDefaultValue(ctx, o, defvalue);
	return o;
}

/* ======================================================================== */
/* [spec] */


///* ------------------------------------------------------------------------ */
//
//knh_class_t
//KNH_TENUM(Ctx *ctx, char *urn, char *tag, knh_int_t min, knh_int_t max, knh_int_t defv, knh_int_t bf_start, knh_int_t bf_end)
//{
//	knh_class_t cid = knh_tclass_newId(ctx);
//	IntUnit *u = new_IntUnit__STEXT(ctx, 0, cid, urn, tag, min, max, defv, bf_start, bf_end);
//	KNH_TCLASS_SPEC(ctx, CLASS_Int, u);
//	return cid;
//}

/* ======================================================================== */
/* [set] */

void knh_IntUnit_initId(Ctx *ctx, IntUnit *b, knh_flag_t flag, knh_class_t cid, String *urn, String *tag)
{
	KNH_ASSERT(IS_NOTNULL(urn));
	KNH_ASSERT(IS_NOTNULL(tag));

	DP(b)->spec.flag = flag;
	DP(b)->spec.cid  = cid;
	KNH_SETv(ctx, DP(b)->spec.urn, urn);
	KNH_SETv(ctx, DP(b)->spec.tag, tag);

	if(knh_IntUnit_isUnsigned(b)) {
		DP(b)->max  = KNH_UINT_MAX;
		DP(b)->min  = KNH_UINT_MIN;
		DP(b)->fchk = knh_IntUnit_fchk__nop;
		DP(b)->fcmp = knh_IntUnit_fcmp__unsigned;
		DP(b)->ffmt = knh_IntUnit_ffmt__unsigned;
	}
}

/* ------------------------------------------------------------------------ */

void knh_IntUnit_initMinMax(Ctx *ctx, IntUnit *b, knh_int_t min, knh_int_t max)
{
	DP(b)->min = min;
	DP(b)->max = max;
	if(knh_IntUnit_isUnsigned(b)) {
		DP(b)->fcmp = knh_IntUnit_fcmp__unsigned;
		DP(b)->ffmt = knh_IntUnit_ffmt__unsigned;
		if(DP(b)->min == KNH_UINT_MIN) {
			if(DP(b)->max == KNH_UINT_MAX) {
				KNH_ASSERT(DP(b)->fchk == knh_IntUnit_fchk__nop);
			}
			else {
				DP(b)->fchk = knh_IntUnit_fchk__unsigned_max;
			}
		}
		else {
			if(DP(b)->max == KNH_UINT_MAX) {
				DP(b)->fchk = knh_IntUnit_fchk__unsigned_min;
			}
			else {
				DP(b)->fchk = knh_IntUnit_fchk__unsigned;
			}
		}
	}
	else {
		if(DP(b)->min == KNH_INT_MIN) {
			if(DP(b)->max == KNH_INT_MAX) {
				KNH_ASSERT(DP(b)->fchk == knh_IntUnit_fchk__nop);
			}
			else {
				DP(b)->fchk = knh_IntUnit_fchk__signed_max;
			}
		}
		else {
			if(DP(b)->max == KNH_INT_MAX) {
				DP(b)->fchk = knh_IntUnit_fchk__signed_min;
			}
			else {
				DP(b)->fchk = knh_IntUnit_fchk__signed;
			}
		}
	}
}

/* ------------------------------------------------------------------------ */

void knh_IntUnit_init_bfarray(Ctx *ctx, IntUnit *b, knh_int_t bf_start, knh_int_t bf_end)
{
	if(bf_start < bf_end) {
		KNH_ASSERT(DP(b)->bfarray == NULL);
		DP(b)->bfoffset  = bf_start;
		DP(b)->bfsize    = bf_end - bf_start + 1;
		DP(b)->bfarray  =  (knh_Int_t**)knh_oarray_malloc(ctx, DP(b)->bfsize, KNH_NULL);
		knh_int_t i;
		for(i = bf_start; i <= bf_end; i++) {
			KNH_SETv(ctx, DP(b)->bfarray[i - bf_start], new_Int__fast(ctx, DP(b)->spec.cid, i));
		}
	}
}

/* ------------------------------------------------------------------------ */

void knh_IntUnit_initDefaultValue(Ctx *ctx, IntUnit *b, knh_int_t v)
{
	if(!DP(b)->fchk(b, v)) {
		v = DP(b)->min;
	}
	if(knh_IntUnit_isBuffered(b, v)) {
		KNH_SETv(ctx, DP(b)->spec.defvalue, DP(b)->bfarray[v - DP(b)->bfoffset]);
	}else {
		KNH_SETv(ctx, DP(b)->spec.defvalue, new_IntX0(ctx, DP(b)->spec.cid, v));
	}
}

/* ======================================================================== */
/* [default_func] */

static
knh_bool_t knh_IntUnit_fchk__nop(IntUnit *b, knh_int_t v)
{
	return 1;
}

/* ------------------------------------------------------------------------ */

static
knh_int_t knh_IntUnit_fcmp__signed(IntUnit *b, knh_int_t v1, knh_int_t v2)
{
	return v1 - v2;
}

/* ------------------------------------------------------------------------ */

static
knh_int_t knh_IntUnit_fcmp__unsigned(IntUnit *b, knh_int_t v1, knh_int_t v2)
{
	if(v1 == v2) return 0;
	return ((knh_uint_t)v1) > ((knh_uint_t)v2) ? 1 : 0;
}

/* ------------------------------------------------------------------------ */

static
void knh_IntUnit_ffmt__signed(IntUnit *b, char *buf, size_t bufsiz, knh_int_t v)
{
	knh_snprintf(buf, bufsiz, KNH_INT_FMT, v);
}

/* ------------------------------------------------------------------------ */

static
void knh_IntUnit_ffmt__unsigned(IntUnit *b, char *buf, size_t bufsiz, knh_int_t v)
{
	knh_snprintf(buf, bufsiz, KNH_UINT_FMT, (knh_uint_t)v);
}

/* ======================================================================== */
/* [range] */

static
knh_bool_t knh_IntUnit_fchk__signed_min(IntUnit *b, knh_int_t v)
{
	return (DP(b)->min <= v);
}

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_IntUnit_fchk__signed_max(IntUnit *b, knh_int_t v)
{
	return (v <= DP(b)->max);
}

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_IntUnit_fchk__signed(IntUnit *b, knh_int_t v)
{
	return (DP(b)->min <= v && v <= DP(b)->max);
}

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_IntUnit_fchk__unsigned_min(IntUnit *b, knh_int_t v)
{
	return ((knh_uint_t)DP(b)->min) <= ((knh_uint_t)v);
}

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_IntUnit_fchk__unsigned_max(IntUnit *b, knh_int_t v)
{
	return ((knh_uint_t)v) <= ((knh_uint_t)DP(b)->max);
}

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_IntUnit_fchk__unsigned(IntUnit *b, knh_int_t v)
{
	return (((knh_uint_t)DP(b)->min) <= ((knh_uint_t)v) && ((knh_uint_t)v) <= ((knh_uint_t)DP(b)->max));
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
