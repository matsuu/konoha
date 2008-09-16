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
/* [global] */


/* ======================================================================== */
/* [TMETHOD] */

void
KNH_TMETHOD(Ctx *ctx, knh_flag_t tflag, f_method func, void *optfunc, knh_ushort_t delta, knh_class_t cid, knh_methodn_t mn, MethodField *mf)
{
	Method *mtd = new_Method(ctx, tflag, cid, mn, func);
	DP(mtd)->code  = optfunc;
	DP(mtd)->delta = delta;
	KNH_ASSERT(IS_MethodField(mf));
	KNH_SETv(ctx, DP(mtd)->mf, mf);
	knh_Class_addMethod__fast(ctx, cid, mtd);
}

/* ======================================================================== */
/* [utils] */

Method *knh_Method_ufind(Ctx *ctx, knh_class_t cid, knh_methodn_t mn)
{
	KNH_ASSERT(!METHODN_IS_MOVTEXT(mn));
	DBG2_({
		char bufcm[CLASSNAME_BUFSIZ];
		knh_format_cmethodn(bufcm, sizeof(bufcm), cid, mn);
		DBG2_P("finding ..: %s", bufcm);
	})
	return knh_Class_findMethod(ctx, cid, mn);
}

/* ------------------------------------------------------------------------ */

Method *knh_tMethod_findMT(Ctx *ctx, knh_class_t cid, knh_methodn_t mn)
{
	KNH_ASSERT(METHODN_IS_MOVTEXT(mn));
//	DBG2_({
//		char bufcm[CLASSNAME_BUFSIZ];
//		knh_format_cmethodn(bufcm, sizeof(bufcm), cid, mn);
//		DBG2_P("finding ..: %s", bufcm);
//	})
	return knh_Class_findMethod(ctx, cid, mn);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
