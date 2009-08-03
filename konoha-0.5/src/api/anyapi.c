/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2005-2009, Kimio Kuramitsu <kimio at ynu.ac.jp>
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

#ifdef KNH_CC_METHODAPI

/* ======================================================================== */
/* [operators] */

//knh_class_t knh_class_bcg(knh_class_t c0, knh_class_t c1)
//{
//	if(c0 == c1) {
//		return c0;
//	}
//	if(c0 == CLASS_String || c1 == CLASS_String) return CLASS_String;
//	if(c0 == CLASS_Float || c1 == CLASS_Float) return CLASS_Float;
//}
//
///* ------------------------------------------------------------------------ */
///* @method[CONST] Any! Any.opAdd(Any! v) */
//
//METHOD knh__Any_opAdd(Ctx *ctx, knh_sfp_t *sfp)
//{
//	knh_class_t bcid0 = ARG_bcid(sfp[0]);
//	knh_class_t bcid1 = ARG_bcid(sfp[1]);
//	KNH_RETURN_Any(ctx, sfp, ARG_int(sfp[0]) + ARG_int(sfp[1]));
//}
//
///* ------------------------------------------------------------------------ */
///* @method[CONST] Any! Any.opNeg() */
//
//METHOD knh__Any_opNeg(Ctx *ctx, knh_sfp_t *sfp)
//{
//	KNH_RETURN_Any(ctx, sfp, -(ARG_int(sfp[0])));
//}
//
///* ------------------------------------------------------------------------ */
///* @method[CONST] Any! Any.opSub(Any! n) */
//
//METHOD knh__Any_opSub(Ctx *ctx, knh_sfp_t *sfp)
//{
//	KNH_RETURN_Any(ctx, sfp, ARG_int(sfp[0]) - ARG_int(sfp[1]));
//}
//
///* ------------------------------------------------------------------------ */
///* @method[CONST] Any! Any.opMul(Any! n) */
//
//METHOD knh__Any_opMul(Ctx *ctx, knh_sfp_t *sfp)
//{
//	KNH_RETURN_Any(ctx, sfp, ARG_int(sfp[0]) * ARG_int(sfp[1]));
//}
//
///* ------------------------------------------------------------------------ */
///* @method[CONST] Any! Any.opDiv(Any! n) */
//
//METHOD knh__Any_opDiv(Ctx *ctx, knh_sfp_t *sfp)
//{
//	KNH_RETURN_Any(ctx, sfp, ARG_int(sfp[0]) / ARG_int(sfp[1]));
//}
//
///* ------------------------------------------------------------------------ */
///* @method[VARARGS|CONST] Any! Any.opAdd(Any! v) */
//
//METHOD knh__Any_opAdd(Ctx *ctx, knh_sfp_t *sfp)
//{
//	int ac = knh_sfp_argc(ctx, sfp);
//	knh_int_t i, n = ARG_int(sfp[0]);
//	for(i = 1; i < ac; i++) {
//		n += ARG_int(sfp[i]);
//	}
//	KNH_RETURN_Any(ctx, sfp, n);
//}
//
///* ------------------------------------------------------------------------ */
///* @method[VARARGS|CONST] Any! Any.opSub(Any! n) */
//
//METHOD knh__Any_opSub(Ctx *ctx, knh_sfp_t *sfp)
//{
//	int ac = knh_sfp_argc(ctx, sfp);
//	knh_int_t i, n = ARG_int(sfp[0]);
//	for(i = 1; i < ac; i++) {
//		n -= ARG_int(sfp[i]);
//	}
//	KNH_RETURN_Any(ctx, sfp, n);
//}
//
///* ------------------------------------------------------------------------ */
///* @method[VARARGS|CONST] Any! Any.opMul(Any! n) */
//
//METHOD knh__Any_opMul(Ctx *ctx, knh_sfp_t *sfp)
//{
//	int ac = knh_sfp_argc(ctx, sfp);
//	knh_int_t i, n = ARG_int(sfp[0]);
//	for(i = 1; i < ac; i++) {
//		n *= ARG_int(sfp[i]);
//	}
//	KNH_RETURN_Any(ctx, sfp, n);
//}
//
///* ------------------------------------------------------------------------ */
///* @method[VARARGS|CONST] Any! Any.opDiv(Any! n) */
//
//METHOD knh__Any_opDiv(Ctx *ctx, knh_sfp_t *sfp)
//{
//	int ac = knh_sfp_argc(ctx, sfp);
//	knh_int_t i, n = ARG_int(sfp[0]);
//	for(i = 1; i < ac; i++) {
//		n /= ARG_int(sfp[i]);
//	}
//	KNH_RETURN_Any(ctx, sfp, n);
//}
//
///* ------------------------------------------------------------------------ */
///* @method[CONST] Any! Any.opMod(Any! n) */
//
//METHOD knh__Any_opMod(Ctx *ctx, knh_sfp_t *sfp)
//{
//	KNH_RETURN_Any(ctx, sfp, ARG_int(sfp[0]) % ARG_int(sfp[1]));
//}
//

/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [method] */

/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [mapping] */


#endif/* KNH_CC_METHODAPI*/

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
