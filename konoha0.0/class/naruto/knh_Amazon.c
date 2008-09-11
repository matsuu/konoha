///****************************************************************************
// * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER  
// * 
// * Copyright (c) 2005-2008, Kimio Kuramitsu <kimio at ynu.ac.jp>
// *           (c) 2008-      Konoha Software Foundation  
// * All rights reserved.
// * 
// * You may choose one of the following two licenses when you use konoha. 
// * See www.konohaware.org/license.html for further information.
// * 
// * (1) GNU General Public License 2.0      (with    KONOHA_UNDER_GPL2)
// * (2) Konoha Software Foundation License 1.0
// * 
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER 
// * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// *  
// ****************************************************************************/
//
///* ************************************************************************ */
//
//#include"commons.h"
//#include<unistd.h>
//#include<time.h>
//
///* ************************************************************************ */
//
//#ifdef __cplusplus 
//extern "C" {
//#endif
//
///* ======================================================================== */
///* [structs] */
//
//void knh_Amazon_struct_init(Ctx *ctx, knh_Amazon *b, int init, Object *cs)
//{
//	b->dummy = 0;
//}
//
///* ------------------------------------------------------------------------ */
//
//#define _knh_Amazon_struct_copy      NULL
//
///* ------------------------------------------------------------------------ */
//
//#define _knh_Amazon_struct_compare   NULL
//
///* ------------------------------------------------------------------------ */
//
//#define _knh_Amazon_struct_traverse  NULL
//
/////* ======================================================================== */
/////* [constructors] */
////
////Amazon *new_Amazon(Ctx *ctx)
////{
////	Amazon *b = knh_Object_malloc(ctx, CLASS_Amazon);
////	knh_Amazon_struct_init(ctx, (Struct*)b, 0, NULL);
////	return b;
////}
////
/////* ------------------------------------------------------------------------ */
////
////static Object *staticAmazon = NULL;
////
/////* ------------------------------------------------------------------------ */
////
////Object *knh_Amazon_fvalue(Ctx *ctx, knh_class_t cid)
////{
////	if(staticAmazon == NULL) {
////		staticAmazon = new_Amazon(ctx);
////		KNH_TSTATICOBJ(staticAmazon);
////	}
////	return staticAmazon;
////}
//
/////* ======================================================================== */
/////* [demo] */
////
/////* @method void Amazon.placeOrder(String uname, String order) */
////
////void knh_Amazon_placeOrder(Ctx *ctx, Amazon *b, String *uname, String *order)
////{
////	fprintf(stdout, "%s's ordering %s", knh_String_tochar(uname), knh_String_tochar(order));
////	fflush(stdout);
////	int i;
////	for(i = 0; i < 8; i++) {
////		fputc('.',stdout); fflush(stdout);
////		//sleep(i%3);
////	}
////	fprintf(stdout, " OK\n\n");
////}
////
/////* ------------------------------------------------------------------------ */
////
////void knh_security_RBAC(Ctx *ctx, knh_sfp_t *sfp)
////{
////	if(knh_String_equals((String*)sfp[1].o, STEXT("sensei"))) {
////		Method *mtd = (Method*)(sfp[-1].mtd)->code;
////		KNH_ASSERT(mtd->func != knh_security_RBAC);
////		mtd->func(ctx, sfp);
////	}else {
////		KNH_THROWf(ctx, "Security!!: %s disallowed", knh_String_tochar(sfp[1].o));
////	}
////}
////
/////* ------------------------------------------------------------------------ */
////
////void 
////knh_security_Audit(Ctx *ctx, knh_sfp_t *sfp)
////{
////   time_t timer;
////   struct tm *t_st;
////   time(&timer);
////   t_st = localtime(&timer);
////   
////   knh_printf(ctx, KNH_STDOUT, "logging.. [%d/%d/%d %d:%d:%d] Amazon.placeOrder uname=%O order=%O\n", 
////   	t_st->tm_year+1900, t_st->tm_mon+1, t_st->tm_mday, t_st->tm_hour, t_st->tm_min, t_st->tm_sec,
////   	sfp[1].o, sfp[2].o);
////	Method *mtd = (Method*)(sfp[-1].mtd)->code;
////	KNH_ASSERT(mtd->func != knh_security_Audit);
////	mtd->func(ctx, sfp);
////}
////
/////* ------------------------------------------------------------------------ */
////
////void knh_Method_weave(Ctx *ctx, Method *b, f_method f)
////{
////	if(f == NULL) goto L_UNWEAVE;
////	
////	Method* mtd = 
////		(Method*)new_Object__RAW(ctx, KNH_FLAG_Method, CLASS_Method, sizeof(Method));
////	knh_Method_struct_init(ctx, (Struct*)mtd, 0, NULL);
////	mtd->flag   = DP(b)->flag;
////	mtd->cid    = DP(b)->cid;
////	mtd->mn     = DP(b)->mn;
////	KNH_SETv(ctx, mtd->mf, DP(b)->mf);
////	mtd->func   = DP(b)->func;
////	if(knh_Method_isObjectCode(b)) {
////		KNH_ASSERT(mtd->code == NULL);
////		KNH_INITv(mtd->code, DP(b)->code);
////	}
////	else {
////		mtd->code = DP(b)->code;
////	}
////	
////	knh_Method_setAspect(b, 1);
////	KNH_ASSERT(knh_Method_isAspect(b));
////	DP(b)->func = f;
////	if(knh_Method_isObjectCode(b)) {
////		KNH_SETv(ctx, DP(b)->code, mtd);
////	}
////	else {
////		DP(b)->code = NULL;
////		knh_Method_setObjectCode(b, 1);
////		KNH_INITv(DP(b)->code, mtd);
////	}
////	return;
////	
////	L_UNWEAVE:;
////	mtd = (Method*)DP(b)->code;
////	if(!IS_Method(mtd)) {
////		return;
////	}
////	DP(b)->func = mtd->func;
//////	fprintf(stderr, "@@ func=%p (!NULL)\n", DP(b)->func);
////	if(knh_Method_isObjectCode(mtd)) {
////		KNH_SETv(ctx, DP(b)->code, mtd->code);
////	}
////	else {
////		knh_Method_setObjectCode(b, 0);
////		DP(b)->code = mtd->code;
////	}
////	knh_Method_setAspect(b, 0);
////	KNH_FINALv(ctx, mtd);
////}
////
/////* ------------------------------------------------------------------------ */
////
////void knh_weave(Ctx *ctx, f_method f, Method *mtd)
////{
////	if(knh_Method_isAspect(mtd)) {
////		if(f == NULL) {
////			knh_Method_weave(ctx, mtd, NULL);
////			return;
////		}
////		mtd->func = f;
////	}
////	else {
////		if(f == NULL) return;
////		knh_Method_weave(ctx, mtd, f);
////	}
////}
//
///* ------------------------------------------------------------------------ */
//
//#ifdef __cplusplus
//}
//#endif
