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
/* [constructors] */

/* ------------------------------------------------------------------------ */


Int64* new_Int64X__fast(Ctx *ctx, knh_class_t cid, knh_int64_t value)
{
	Int64 *o = (Int64*)new_PObject0(ctx, FLAG_Float, CLASS_Int64, cid);
	o->value = value;
	return o;
}

/* ------------------------------------------------------------------------ */

Int64* new_Int64X(Ctx *ctx, knh_class_t cid, knh_int64_t value)
{
	TODO();
	return new_Int64X__fast(ctx, cid, value);
}

/* ======================================================================== */
/* [utils] */

INLINE
knh_int64_t knh_int64_max(knh_int64_t a, knh_int64_t b)
{
	return (a > b) ? a : b;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_int64_t knh_int64_min(knh_int64_t a, knh_int64_t b)
{
	return (a < b) ? a : b;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_uint64_t knh_uint64_max(knh_uint64_t a, knh_uint64_t b)
{
	return (a > b) ? a : b;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_uint64_t knh_uint64_min(knh_uint64_t a, knh_uint64_t b)
{
	return (a < b) ? a : b;
}

/* ======================================================================== */
/* [movabletext] */

/* @method void Int64.%dump(OutputStream w, Any m) */


void knh_Int64__dump(Ctx *ctx, Int64 *b, OutputStream *w, Any *m)
{
//	char buf[FMT_NSPEC_BUFSIZE];
//	IntSpec *spec = knh_tclass_getIntUnit(ctx, knh_Object_cid(b));
//	knh_IntSpec_format(spec, buf, knh_Int64_value(b));
//	knh_prints(ctx, w, buf);
}

#ifdef __cplusplus
}
#endif
