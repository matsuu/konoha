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
/* [macro] */

#define _KNH_SETr(ctx,sf,v)          KNH_SETv(ctx,sf[-1],v)
#define _KNH_SETr_void(ctx,sf)       KNH_SETv(ctx,sf[-1],KNH_NULL)
#define _KNH_SAFE_SETr(ctx, sf, v)   KNH_SETv(ctx, sf[-1], v)

/* ======================================================================== */
/* [local] */

// stackf (Ctx *ctx, Object **sf)  
// ebp                                                                 
// sf[-1]  sf[0]  sf[1]  sf[2]
// method  this   arg1   arg2
//                       ebp
// return
// ebp

#define _KNH_LOPEN(ctx, n) \
	Object **local_ = ((Context*)ctx)->ebp; \
	knh_stackf_locals(ctx, n) \

#define _KNH_LOCALv(n)                 local_[n+1]
#define _KNH_LVALUE(n)                 local_[n+1]
#define _KNH_LSETv(ctx, n, v)          KNH_SETv(ctx, local_[n+1], v) 
#define _KNH_LCLOSE(ctx)              ((Context*)ctx)->ebp = local_

/* ------------------------------------------------------------------------ */

#define _KNH_LPUSH(ctx,v) \
	((Context*)ctx)->ebp++; \
	KNH_SETv(ctx, ((Context*)ctx)->ebp[0], v); \

#define _KNH_PUSHv(ctx,v) \
	((Context*)ctx)->ebp++; \
	KNH_SETv(ctx, ((Context*)ctx)->ebp[0], v); \

/* ------------------------------------------------------------------------ */

#define _KNH_STACKOP(p)        ((Context*)ctx)->stackop[(p)-((Context*)ctx)->stack]

/* ------------------------------------------------------------------------ */

void knh_stackf_locals(Ctx *ctx, size_t n)
{
	knh_int_t i;
	for(i = 0; i < n; i++) {
		KNH_PUSHv(ctx, KNH_NULL);
	}
}

/* ======================================================================== */
/* [argc] */

// stackf (Ctx *ctx, Object **sf)  
// this.func(a, b..)
// ebp                                                                 
// sf[-1]  sf[0]  sf[1]  sf[2] 
// sf[-1]  sf[0]  sf[1]  varg[0] varg[1] 
// method  this   a      b
// method  this   a      b       b
//                               ebp
// return
// ebp


/* ------------------------------------------------------------------------ */

INLINE
knh_vargc_t knh_stackf_argc(Ctx *ctx, Object **varg)
{
	return (((Context*)ctx)->ebp - varg + 1);
}

/* ------------------------------------------------------------------------ */

Array *knh_stackf_toArray(Ctx *ctx, Object **varg)
{
	Object **p = varg;
	Array *a = new_Array(ctx, knh_stackf_argc(ctx, varg));
	while(p <= ((Context*)ctx)->ebp) {
		knh_Array_add(ctx, a, p[0]);
		p++;
	}
	return a;
}

/* ------------------------------------------------------------------------ */

INLINE
Method *knh_stackf_getMethod(Ctx *ctx, Object **sf)
{
	DEBUG_ASSERT(IS_Method(sf[-1]));
	return sf[-1];
}

/* ======================================================================== */
/* [delta] */


INLINE
Struct *knh_stackf_structDelta(Ctx *ctx, Object **sf)
{
	DEBUG_ASSERT(IS_Method(sf[-1]));
	return (Struct*)(&(KNH_FIELDn(sf[0], ((Method*)sf[-1])->delta)));
}

/* ======================================================================== */
/* [call] */

INLINE
void knh_stackf_new(Ctx *ctx, Object **mtdp)
{
	TODO();
}

/* ------------------------------------------------------------------------ */

void 
knh_stackf_typecheck__DCALL(Ctx *ctx, Object **mtdp)
{
	DEBUG_ASSERT(IS_Method(mtdp[0]));
	Method *mtd = (Method*)mtdp[0];
	Object **argv = mtdp + 2;
	
	//DEBUG("B argc=%d, psize=%d\", (int)knh_stackf_argc(ctx, argv), (int)knh_Method_psize(mtd)); 

	while(knh_stackf_argc(ctx, argv) < knh_Method_psize(mtd)) {
		KNH_PUSHv(ctx, KNH_NULL);
	}

	//DEBUG("E argc=%d, psize=%d\", (int)knh_stackf_argc(ctx, argv), (int)knh_Method_psize(mtd)); 

	knh_int_t i;
	for(i = 0; i < knh_Method_psize(mtd); i++) {
		knh_mfield_t f = knh_Method_pfields(mtd, i);
		VM_TYPECHK(ctx, f.type, argv[i]);
	}	

	if(knh_Method_isVarArgs(mtd)) {
		knh_mfield_t f = knh_Method_lastfield(mtd);
		for(i = knh_Method_psize(mtd); i < knh_stackf_argc(ctx, argv); i++) {
			VM_TYPECHK(ctx, f.type, argv[i]);
		}
	}
}

/* ------------------------------------------------------------------------ */


void knh_stackf_typecheck__MCALL(Ctx *ctx, Object **mtdp)
{
	TODO();
	knh_stackf_typecheck__DCALL(ctx, mtdp);
}

/* ------------------------------------------------------------------------ */


//Object *knh_Object_call(Ctx *ctx, Object *b, knh_methodn_t mn, ...) 
//{
//	Method *mtd = knh_Method_ufind(ctx, knh_Object_cid(b), mn); 
//	KNH_PUSHv(ctx, mtd);
//	KNH_PUSHv(ctx, b);
//	va_list args; 
//	va_start(args , mn);
//	Object *a; knh_int_t c = 0;
//	while((a = va_arg(args, Object*)) != NULL) {
//		KNH_PUSHv(ctx, a); c++;
//	}
//	va_end(args);
//	VM_DCALL(ctx, c); 
//	return ((Context*)ctx)->ebp[0];
//}

/* ======================================================================== */
/* [movabletext] */

void knh_stackf_dump(Ctx *ctx, Object **sf)
{
	fprintf(stderr, "\n** ** ** ** ** ** ** ** **\n");
	int s = sf - ((Context*)ctx)->stack, i = 0;
	for(i = 0; sf + i <= ((Context*)ctx)->ebp; i++) {
		fprintf(stderr, "stack[%d:%d] == %s,op=%d\n", s, i, CLASSN(knh_Object_cid(sf[i])), (int)((Context*)ctx)->stackop[s+i]);
	}
	fprintf(stderr, "** ** ** ** ** ** ** ** **\n");
}

/* ------------------------------------------------------------------------ */

void knh_stackf_diagnose(Ctx *ctx, Object **sf, knh_int_t n)
{
	TODO();	
}

#ifdef __cplusplus
}
#endif
