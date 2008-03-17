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
#include<unistd.h>
#include<time.h>

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */
/* [structs] */

void knh_Amazon_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Amazon *b = (Amazon*)s;
	b->dummy = 0;
}

/* ------------------------------------------------------------------------ */

#define _knh_Amazon_struct_copy      NULL

/* ------------------------------------------------------------------------ */

#define _knh_Amazon_struct_compare   NULL

/* ------------------------------------------------------------------------ */

#define _knh_Amazon_struct_traverse  NULL

/* ======================================================================== */
/* [constructors] */

Amazon *new_Amazon(Ctx *ctx)
{
	Amazon *b = knh_Object_malloc(ctx, CLASS_Amazon);
	knh_Amazon_struct_init(ctx, (Struct*)b, 0, NULL);
	return b;
}

/* ------------------------------------------------------------------------ */

static Object *staticAmazon = NULL;

/* ------------------------------------------------------------------------ */

Object *knh_Amazon_fvalue(Ctx *ctx, knh_class_t cid)
{
	if(staticAmazon == NULL) {
		staticAmazon = new_Amazon(ctx);
		KNH_TGLOBAL(staticAmazon);
	}
	return staticAmazon;
}

/* ======================================================================== */
/* [demo] */

/* @method void Amazon.placeOrder(String uname, String order) */

void knh_Amazon_placeOrder(Ctx *ctx, Amazon *b, String *uname, String *order)
{
	fprintf(stdout, "%s's ordering %s", knh_String_tochar(uname), knh_String_tochar(order));
	fflush(stdout);
	int i;
	for(i = 0; i < 8; i++) {
		fputc('.',stdout); fflush(stdout);
		//sleep(i%3);
	}
	fprintf(stdout, " OK\n\n");
}

/* ------------------------------------------------------------------------ */

void knh_security_RBAC(Ctx *ctx, Object **sfp)
{
	if(knh_String_equals((String*)sfp[1], STEXT("sensei"))) {
		Method *mtd = (Method*)((Method*)sfp[-1])->code;
		DEBUG_ASSERT(mtd->func != knh_security_RBAC);
		mtd->func(ctx, sfp);
	}else {
		KNH_THROWf(ctx, "Security!!: %s disallowed", knh_String_tochar(sfp[1]));
	}
}

/* ------------------------------------------------------------------------ */

void 
knh_security_Audit(Ctx *ctx, Object **sfp)
{
   time_t timer;
   struct tm *t_st;
   time(&timer);
   t_st = localtime(&timer);
   
   knh_printf(ctx, KNH_STDOUT, "logging.. [%d/%d/%d %d:%d:%d] Amazon.placeOrder uname=%O order=%O\n", 
   	t_st->tm_year+1900, t_st->tm_mon+1, t_st->tm_mday, t_st->tm_hour, t_st->tm_min, t_st->tm_sec,
   	sfp[1], sfp[2]);
	Method *mtd = (Method*)((Method*)sfp[-1])->code;
	DEBUG_ASSERT(mtd->func != knh_security_Audit);
	mtd->func(ctx, sfp);
}

/* ------------------------------------------------------------------------ */

void knh_Method_weave(Ctx *ctx, Method *b, f_method f)
{
	if(f == NULL) goto L_UNWEAVE;
	
	Method* mtd = 
		(Method*)knh_Object_malloc0(ctx, KNH_FLAG_Method, CLASS_Method, sizeof(Method));
	knh_Method_struct_init(ctx, (Struct*)mtd, 0, NULL);
	mtd->flag   = b->flag;
	mtd->cid    = b->cid;
	mtd->mn     = b->mn;
	KNH_SETv(ctx, mtd->mf, b->mf);
	mtd->func   = b->func;
	if(knh_Method_isObjectCode(b)) {
		DEBUG_ASSERT(mtd->code == NULL);
		KNH_INITv(mtd->code, b->code);
	}
	else {
		mtd->code = b->code;
	}
	
	knh_Method_setAspect(b, 1);
	DEBUG_ASSERT(knh_Method_isAspect(b));
	b->func = f;
	if(knh_Method_isObjectCode(b)) {
		KNH_SETv(ctx, b->code, mtd);
	}
	else {
		b->code = NULL;
		knh_Method_setObjectCode(b, 1);
		KNH_INITv(b->code, mtd);
	}
	return;
	
	L_UNWEAVE:;
	mtd = (Method*)b->code;
	if(!IS_Method(mtd)) {
		return;
	}
	b->func = mtd->func;
//	fprintf(stderr, "@@ func=%p (!NULL)\n", b->func);
	if(knh_Method_isObjectCode(mtd)) {
		KNH_SETv(ctx, b->code, mtd->code);
	}
	else {
		knh_Method_setObjectCode(b, 0);
		b->code = mtd->code;
	}
	knh_Method_setAspect(b, 0);
	KNH_FINALv(ctx, mtd);
}

/* ------------------------------------------------------------------------ */

void knh_weave(Ctx *ctx, f_method f, Method *mtd)
{
	if(knh_Method_isAspect(mtd)) {
		if(f == NULL) {
			knh_Method_weave(ctx, mtd, NULL);
			return;
		}
		mtd->func = f;
	}
	else {
		if(f == NULL) return;
		knh_Method_weave(ctx, mtd, f);
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
