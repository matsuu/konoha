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
/* [constructors] */

Float* new_FloatX0(Ctx *ctx, knh_class_t cid, knh_float_t value)
{
	Float *b = (Float*)new_PObject0(ctx, FLAG_Float, CLASS_Float, cid);
	b->value = value;
	return b;
}

/* ------------------------------------------------------------------------ */

Float* new_FloatX(Ctx *ctx, knh_class_t cid, knh_float_t value)
{
	DEBUG_ASSERT_cid(cid);
	{
		FloatUnit *o = (FloatUnit*)knh_tClass[cid].cspec;
		KNH_ASSERT(IS_FloatUnit(o));
		if(DP(o)->fchk(o, value)) {
			return new_Float__fast(ctx, cid, value);
		}
		else {
			char buf[CLASSNAME_BUFSIZ];
			knh_snprintf(buf, sizeof(buf), "Format!!: %s(" KNH_FLOAT_FMT ")", CLASSN(cid), value);
			DBG2_P("%s", buf);
			return (Float*)new_Nue__s(ctx, buf);
		}
	}
}

/* ------------------------------------------------------------------------ */

Float* new_FloatX__b(Ctx *ctx, knh_class_t cid, knh_bytes_t t)
{
	int i = 0, c = 1;
	knh_float_t v = 0.0, prev;

	if(t.buf[0] == '-') i = 1;

	for(;i < t.len; i++) {
		if('0' <= t.buf[i] && t.buf[i] <= '9') {
			prev = v;
			v = v * 10 + (t.buf[i] - '0');
		}
		else if(t.buf[i] == '.') {
			i++;
			break;
		}
		else {
			return new_FloatX(ctx, cid, (t.buf[0] == '-') ? -v : v);
		}
		if(!(v > prev)) {
			char buf[1024];
			knh_snprintf(buf, sizeof(buf), "FloatOverflow!!: %s", (char*)t.buf);
			DBG2_P("%s", buf);
			return (Float*)new_Nue__s(ctx, buf);
		}
	}

	for(; i < t.len; i++) {
		if('0' <= t.buf[i] && t.buf[i] <= '9') {
			prev = v;
			v = v * 10 + (t.buf[i] - '0');
			c *= 10;
		}else {
			break;
		}
		if(!(v > prev)) {
			char buf[1024];
			knh_snprintf(buf, sizeof(buf), "FloatOverflow!!: %s", (char*)t.buf);
			DBG2_P("%s", buf);
			return (Float*)new_Nue__s(ctx, buf);
		}
	}
	return new_FloatX(ctx, cid, (t.buf[0] == '-') ? (-v /c) : (v / c)) ;
}

/* ------------------------------------------------------------------------ */

Object *knh_Float_cspec(Ctx *ctx)
{
	KNH_TCONST__T(ctx, "konoha.Float.MAX", (Object*)new_FloatX0(ctx, CLASS_Float, KNH_FLOAT_MAX));
	KNH_TCONST__T(ctx, "konoha.Float.MIN", (Object*)new_FloatX0(ctx, CLASS_Float, KNH_FLOAT_MIN));
	return (Object*)new_FloatUnit(ctx, 0, CLASS_Float, TS_EMPTY, TS_EMPTY, KNH_FLOAT_MIN, KNH_FLOAT_MAX, 0.0, 0.0);
}

/* ------------------------------------------------------------------------ */

Object *knh_Float_fdefault(Ctx *ctx, knh_class_t cid)
{
	FloatUnit *o = (FloatUnit*)knh_tClass[cid].cspec;
	KNH_ASSERT(IS_FloatUnit(o));
	return DP(o)->spec.defvalue;
}

/* ------------------------------------------------------------------------ */

int knh_Float_compareTo(Float *o, Float *o2)
{
	if(o->h.cid == CLASS_Float || o2->h.cid == CLASS_Float) {
		return (int)(o->value - o2->value);
	}
	else {
		FloatUnit *fu = (FloatUnit*)knh_tClass[o->h.cid].cspec;
		KNH_ASSERT(IS_FloatUnit(fu));
		return DP(fu)->fcmp(fu, o->value, o2->value);
	}
}

/* ------------------------------------------------------------------------ */

char *knh_format_Float(char *buf, size_t bufsiz, Float *o)
{
	FloatUnit *fu = (FloatUnit*)knh_tClass[o->h.cid].cspec;
	KNH_ASSERT(IS_FloatUnit(fu));
	DP(fu)->ffmt(fu, buf, bufsiz, o->value);
	return buf;
}

/* ======================================================================== */
/* [utils] */

INLINE
knh_float_t knh_float_max(knh_float_t a, knh_float_t b)
{
	return (a > b) ? a : b;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_float_t knh_float_min(knh_float_t a, knh_float_t b)
{
	return (a < b) ? a : b;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
