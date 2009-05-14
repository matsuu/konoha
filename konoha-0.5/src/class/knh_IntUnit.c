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

/* ======================================================================== */
/* [default_func] */

static knh_bool_t knh_fenumchk__nop(IntUnit *b, knh_int_t v);
static int knh_fenumcmp__unsigned(IntUnit *b, knh_int_t v1, knh_int_t v2);
static void knh_fenumfmt__unsigned(IntUnit *b, char *buf, size_t bufsiz, knh_int_t v);
static knh_bool_t knh_fenumchk__signed_min(IntUnit *b, knh_int_t v);
static knh_bool_t knh_fenumchk__signed_max(IntUnit *b, knh_int_t v);
static knh_bool_t knh_fenumchk__signed(IntUnit *b, knh_int_t v);
static knh_bool_t knh_fenumchk__unsigned_min(IntUnit *b, knh_int_t v);
static knh_bool_t knh_fenumchk__unsigned_max(IntUnit *b, knh_int_t v);
static knh_bool_t knh_fenumchk__unsigned(IntUnit *b, knh_int_t v);

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_fenumchk__nop(IntUnit *b, knh_int_t v)
{
	return 1;
}

/* ------------------------------------------------------------------------ */

static
int knh_fenumcmp__unsigned(IntUnit *b, knh_int_t v1, knh_int_t v2)
{
	if(v1 == v2) return 0;
	return ((knh_uintptr_t)v1) > ((knh_uintptr_t)v2) ? 1 : 0;
}

/* ------------------------------------------------------------------------ */

static
void knh_fenumfmt__unsigned(IntUnit *b, char *buf, size_t bufsiz, knh_int_t v)
{
	knh_snprintf(buf, bufsiz, KNH_UINT_FMT, (knh_uint_t)v);
}

/* ======================================================================== */
/* [range] */

static
knh_bool_t knh_fenumchk__signed_min(IntUnit *b, knh_int_t v)
{
	return (DP(b)->min <= v);
}

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_fenumchk__signed_max(IntUnit *b, knh_int_t v)
{
	return (v <= DP(b)->max);
}

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_fenumchk__signed(IntUnit *b, knh_int_t v)
{
	return (DP(b)->min <= v && v <= DP(b)->max);
}

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_fenumchk__unsigned_min(IntUnit *b, knh_int_t v)
{
	return ((knh_uint_t)DP(b)->min) <= ((knh_uint_t)v);
}

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_fenumchk__unsigned_max(IntUnit *b, knh_int_t v)
{
	return ((knh_uint_t)v) <= ((knh_uint_t)DP(b)->max);
}

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_fenumchk__unsigned(IntUnit *b, knh_int_t v)
{
	return (((knh_uint_t)DP(b)->min) <= ((knh_uint_t)v) && ((knh_uint_t)v) <= ((knh_uint_t)DP(b)->max));
}

/* ======================================================================== */
/* [set] */

/* ------------------------------------------------------------------------ */

void knh_IntUnit_initMinMax(Ctx *ctx, IntUnit *b, knh_int_t min, knh_int_t max)
{
	DP(b)->min = min;
	DP(b)->max = max;
	if(knh_IntUnit_isUnsigned(b)) {
		DP(b)->fcmp = knh_fenumcmp__unsigned;
		DP(b)->ffmt = knh_fenumfmt__unsigned;
		if(DP(b)->min == KNH_UINT_MIN) {
			if(DP(b)->max == KNH_UINT_MAX) {
				//KNH_ASSERT(DP(b)->fchk == knh_fenumchk__nop);
			}
			else {
				DP(b)->fchk = knh_fenumchk__unsigned_max;
			}
		}
		else {
			if(DP(b)->max == KNH_UINT_MAX) {
				DP(b)->fchk = knh_fenumchk__unsigned_min;
			}
			else {
				DP(b)->fchk = knh_fenumchk__unsigned;
			}
		}
	}
	else {
		if(DP(b)->min == KNH_INT_MIN) {
			if(DP(b)->max == KNH_INT_MAX) {
				//KNH_ASSERT(DP(b)->fchk == knh_fenumchk__nop);
			}
			else {
				DP(b)->fchk = knh_fenumchk__signed_max;
			}
		}
		else {
			if(DP(b)->max == KNH_INT_MAX) {
				DP(b)->fchk = knh_fenumchk__signed_min;
			}
			else {
				DP(b)->fchk = knh_fenumchk__signed;
			}
		}
	}
}

/* ------------------------------------------------------------------------ */

void knh_IntUnit_initDefaultValue(Ctx *ctx, IntUnit *b, knh_int_t v)
{
	if(!DP(b)->fchk(b, v)) {
		v = DP(b)->min;
	}
	KNH_SETv(ctx, DP(b)->spec.defvalue, new_IntX__fast(ctx, DP(b)->spec.cid, v));
}

/* ------------------------------------------------------------------------ */

IntUnit *new_IntUnit(Ctx *ctx, knh_flag_t flag, knh_class_t cid, String *urn, String *tag, knh_int_t min, knh_int_t max, knh_int_t defvalue)
{
	IntUnit* o = (IntUnit*)new_Object_bcid(ctx, CLASS_IntUnit, 0);

	DP(o)->spec.flag = flag;
	DP(o)->spec.cid  = cid;
	KNH_SETv(ctx, DP(o)->spec.urn,  urn);
	KNH_SETv(ctx, DP(o)->spec.tag,  tag);
	knh_IntUnit_initMinMax(ctx, o, min, max);
	knh_IntUnit_initDefaultValue(ctx, o, defvalue);
	return o;
}

/* ------------------------------------------------------------------------ */

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
		DP(b)->fchk = knh_fenumchk__nop;
		DP(b)->fcmp = knh_fenumcmp__unsigned;
		DP(b)->ffmt = knh_fenumfmt__unsigned;
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
