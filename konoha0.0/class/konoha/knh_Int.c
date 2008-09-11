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

#define _knh_Int_value(o)      (o)->value

/* ======================================================================== */
/* [constructors] */

Int* new_IntX0(Ctx *ctx, knh_class_t cid, knh_int_t value)
{
	knh_Int_t *b = (knh_Int_t*)new_PObject0(ctx, FLAG_Int, CLASS_Int, cid);
	b->value = value;
	return b;
}

/* ------------------------------------------------------------------------ */

Int *new_IntX(Ctx *ctx, knh_class_t cid, knh_int_t value)
{
	DEBUG_ASSERT_cid(cid);
	{
		IntUnit *u = (IntUnit*)knh_tClass[cid].cspec;
		KNH_ASSERT(IS_IntUnit(u));

		if(knh_IntUnit_isBuffered(u, value)) {
			return DP(u)->bfarray[value - DP(u)->bfoffset];
		}
		if(DP(u)->fchk(u, value)) {
			Int *n = new_Int__fast(ctx, DP(u)->spec.cid, value);
			return n;
		}
		else {
			char buf[CLASSNAME_BUFSIZ];
			if(knh_IntUnit_isUnsigned(u)) {
				knh_snprintf(buf, sizeof(buf), "Format!!: %s(" KNH_UINT_FMT ")", CLASSN(cid), value);
			}else {
				knh_snprintf(buf, sizeof(buf), "Format!!: %s(" KNH_INT_FMT ")", CLASSN(cid), value);
			}
			DBG2_P("%s", buf);
			return (Int*)new_Nue__s(ctx, buf);
		}
	}
}

/* ------------------------------------------------------------------------ */

Int *new_IntX__b(Ctx *ctx, knh_class_t cid, knh_bytes_t t)
{
	knh_uint_t n = 0, prev = 0, base = 10;
	int i = 0;

	if(t.len > 1) {
		if(t.buf[0] == '0') {
			if(t.buf[1] == 'x') {
				base = 16; i = 2;
			}
			else if(t.buf[1] == 'b') {
				base = 2;  i = 2;
			}
		}else if(t.buf[0] == '-') {
			base = 10; i = 1;
		}
	}

	for(;i < t.len; i++) {
		int c = t.buf[i];
		if('0' <= c && c <= '9') {
			prev = n;
			n = n * base + (c - '0');
		}else if(base == 16) {
			if('A' <= c && c <= 'F') {
				prev = n;
				n = n * 16 + (10 + c - 'A');
			}else if('a' <= c && c <= 'f') {
				prev = n;
				n = n * 16 + (10 + c - 'a');
			}else {
				break;
			}
		}else if(c == '_') {
			continue;
		}else {
			break;
		}
		if(!(n > prev)) {
			char buf[1024];
			knh_snprintf(buf, sizeof(buf), "IntegerOverflow!!: %s", (char*)t.buf);
			DBG2_P("%s", buf);
			return (Int*)new_Nue__s(ctx, buf);
		}
	}
	if(t.buf[0] == '-') {
		return new_IntX(ctx, cid, (knh_int_t)-n);
	}
	else {
		return new_IntX(ctx, cid, (knh_int_t)n);
	}
}

/* ------------------------------------------------------------------------ */

Object *knh_Int_cspec(Ctx *ctx)
{
	knh_IntUnit_t *u = new_IntUnit(ctx, 0, CLASS_Int, TS_EMPTY, TS_EMPTY, KNH_INT_MIN, KNH_INT_MAX, 0, KNH_TINT_MIN, KNH_TINT_MAX);
	KNH_TCONST__T(ctx, "konoha.Int.MAX", (Object*)new_IntX0(ctx, CLASS_Int, KNH_INT_MAX));
	KNH_TCONST__T(ctx, "konoha.Int.MIN", (Object*)new_IntX0(ctx, CLASS_Int, KNH_INT_MIN));
	return (Object*)u;
}

/* ------------------------------------------------------------------------ */

Object *knh_Int_fdefault(Ctx *ctx, knh_class_t cid)
{
	return (Object*)knh_tInt[0-KNH_TINT_MIN];
}

/* ------------------------------------------------------------------------ */

Object *knh_IntX_fdefault(Ctx *ctx, knh_class_t cid)
{
	IntUnit *o = (IntUnit*)knh_tClass[cid].cspec;
	KNH_ASSERT(IS_IntUnit(o));
	return DP(o)->spec.defvalue;
}

/* ------------------------------------------------------------------------ */

knh_hcode_t knh_Int_hashCode(Int *o)
{
	return (knh_hcode_t)o->value;
}

/* ------------------------------------------------------------------------ */

int knh_Int_compareTo(Int *o, Int *o2)
{
	if(o->h.cid == CLASS_Int || o2->h.cid == CLASS_Int) {
		return (o->value - o2->value);
	}
	else {
		IntUnit *u = (IntUnit*)knh_tClass[o->h.cid].cspec;
		KNH_ASSERT(IS_IntUnit(u));
		return DP(u)->fcmp(u, o->value, o2->value);
	}
}

/* ------------------------------------------------------------------------ */

char *knh_format_Int(char *buf, size_t bufsiz, Int *n)
{
	IntUnit *u = (IntUnit*)knh_tClass[n->h.cid].cspec;
	KNH_ASSERT(IS_IntUnit(u));
	DP(u)->ffmt(u, buf, bufsiz, n->value);
	return buf;
}

/* ======================================================================== */
/* [utils] */

INLINE
knh_int_t knh_int_max(knh_int_t a, knh_int_t b)
{
	return (a > b) ? a : b;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_int_t knh_int_min(knh_int_t a, knh_int_t b)
{
	return (a < b) ? a : b;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_uint_t knh_uint_max(knh_uint_t a, knh_uint_t b)
{
	return (a > b) ? a : b;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_uint_t knh_uint_min(knh_uint_t a, knh_uint_t b)
{
	return (a < b) ? a : b;
}

/* ======================================================================== */

knh_int_t knh_IntNULL_toint(Int *v)
{
	if(IS_NULL(v)) {
		return 0;
	}else {
		return v->value;
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
