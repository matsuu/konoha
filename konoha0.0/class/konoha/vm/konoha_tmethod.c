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

//#define tmeta(ctx) ((Context*)ctx)->runtime->tmetaHashMap

/* ======================================================================== */
/* [TMETHOD] */

knh_bool_t 
knh_Method_checkMethodField(Ctx *ctx, Method *mtd, knh_flag_t flag, knh_type_t rtype, size_t psize)
{
	MethodField *mf = knh_Method_mf(mtd);
	if(IS_NULL(mf)) {
		mf = new_MethodField(ctx, flag, psize+1);
		KNH_SETv(ctx, mtd->mf, mf);
		mf->params[0].fn = FIELDN_return;
		mf->params[0].type = rtype;
		return 1;
	}
	if(knh_MethodField_rtype(mf) != rtype) {
		DEBUG("MismatchedReturnType: %s%s %s%s", 
			TYPEN(knh_MethodField_rtype(mf)), TYPEQ(knh_MethodField_rtype(mf)), TYPEN(rtype), TYPEQ(rtype));
		return 0;
	}
	if(knh_MethodField_psize(mf) != psize) {
		DEBUG("MismatchedParamSize: %d %d", (int)knh_MethodField_psize(mf), (int)psize);
		return 0;
	}
	return 1;
}

//* ------------------------------------------------------------------------ */

knh_bool_t 
knh_Method_checkMethodFieldParams(Ctx *ctx, Method *mtd, knh_index_t pn, knh_type_t type, knh_fieldn_t fn)
{
	MethodField *mf = knh_Method_mf(mtd);
	DEBUG_ASSERT(IS_MethodField(mf));
	DEBUG_ASSERT(pn+1 < mf->size);

	if(mf->params[pn+1].fn == FIELDN_NONAME) {
		mf->params[pn+1].fn   = fn;
		mf->params[pn+1].type = type;
		return 1;
	}
	else if(knh_MethodField_ptype(mf, pn) != type) {
		DEBUG("MismatchedParam(%s): %s%s %s%s", FIELDN(knh_MethodField_pfields(mf, pn).fn),
			TYPEN(knh_MethodField_ptype(mf, pn)), TYPEQ(knh_MethodField_ptype(mf, pn)), TYPEN(type), TYPEQ(type));
		return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

void 
TMETHOD(Ctx *ctx, knh_flag_t tflag, f_method func, knh_type_t rtype, knh_class_t cid, knh_methodn_t mn, knh_ushort_t psize, ...)
{
	Method *mtd = new_Method(ctx, tflag, cid, mn, func);
	if(!knh_Method_checkMethodField(ctx, mtd, tflag, rtype, psize)) {
		KNH_SAFEFREE(ctx,mtd);
		return;
	}

	va_list args; 
	va_start(args , psize);
	knh_int_t i;
	for(i = 0; i < psize; i++) {
		knh_type_t   ft = (knh_type_t)va_arg(args, int);
		knh_fieldn_t fn = (knh_fieldn_t)va_arg(args, int);
		if(!knh_Method_checkMethodFieldParams(ctx, mtd, i, ft, fn)) {
			KNH_SAFEFREE(ctx,mtd);
			return;
		}
	}
	va_end(args);
	knh_Class_addMethod__fast(ctx, cid, mtd);
	KNH_SAFEFREE(ctx,mtd);
}

/* ------------------------------------------------------------------------ */

void 
KNH_TMETHOD(Ctx *ctx, knh_flag_t tflag, f_method func, void *optfunc, knh_ushort_t delta, knh_type_t rtype, knh_class_t cid, knh_methodn_t mn, knh_ushort_t psize, ...)
{
	Method *mtd = new_Method(ctx, tflag, cid, mn, func);
	if(!knh_Method_checkMethodField(ctx, mtd, tflag, rtype, psize)) {
		KNH_SAFEFREE(ctx,mtd);
		return;
	}

	va_list args; 
	va_start(args , psize);
	knh_int_t i;
	for(i = 0; i < psize; i++) {
		knh_type_t   ft = (knh_type_t)va_arg(args, int);
		knh_fieldn_t fn = (knh_fieldn_t)va_arg(args, int);
		if(!knh_Method_checkMethodFieldParams(ctx, mtd, i, ft, fn)) {
			KNH_SAFEFREE(ctx,mtd);
			return;
		}
	}
	va_end(args);
	mtd->code = optfunc;
	mtd->delta = delta;
	knh_Class_addMethod__fast(ctx, cid, mtd);
	KNH_SAFEFREE(ctx,mtd);
}

/* ------------------------------------------------------------------------ */

/* ======================================================================== */
/* [utils] */


Method *knh_Method_ufind(Ctx *ctx, knh_class_t cid, knh_methodn_t mn) 
{
	if(!METHODN_IS_MOVTEXT(mn)) {
		DEBUG("cid=%d, mn=%d", cid, mn);
	}
	return knh_Class_findMethod(ctx, cid, mn);
}

/* ------------------------------------------------------------------------ */


Method *knh_Method_ufindb(Ctx *ctx, knh_class_t cid, knh_bytes_t mnm) 
{
	knh_methodn_t mn = knh_tmethodn_forname(ctx, mnm, METHODN_NONAME);
	if(mn == METHODN_NONAME) {
		KNH_THROWf(ctx, "NoSuchMethod!!: %s.%s", CLASSN(cid), mnm.buf);
	}
	return knh_Class_findMethod(ctx, cid, mn);
}


#ifdef __cplusplus
}
#endif
