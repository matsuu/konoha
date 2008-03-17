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

#define KONOHA_GLOBAL_NULL
#define KONOHA_GLOBAL_BOOL
#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

void konoha_load_builtins(Ctx *ctx);

/* ======================================================================== */
/* [global] */

Object    *knh_Nue_gNULL            = NULL;
Object    *knh_Bool_gTRUE           = NULL;
Object    *knh_Bool_gFALSE          = NULL;
#define    KNH_NULL                knh_Nue_gNULL

static System    *knh_System_gROOT         = NULL;
static NameSpace *knh_NameSpace_gSYSTEM    = NULL;
static Runtime   *knh_Runtime_gROOT        = NULL;

/* ------------------------------------------------------------------------ */
/* [Nue] */

INLINE 
Object *knh_Nue_NULL(void) 
{
	return knh_Nue_gNULL; 
}

/* ======================================================================== */
/* [Runtime] */

Runtime *knh_Runtime_ROOT()
{
	return knh_Runtime_gROOT;
}

/* ------------------------------------------------------------------------ */
/* @method Runtime! Context.getRuntime() */

Runtime *knh_Context_getRuntime(Ctx *ctx, Context *b)
{
	if(ctx == NULL) {
		return knh_Runtime_ROOT();
	}
	return ((Context*)ctx)->runtime;	
}

/* ------------------------------------------------------------------------ */

Object *knh_Runtime_fvalue(Ctx *ctx, knh_class_t cid)
{
	return ((Context*)ctx)->runtime;	
}

/* ======================================================================== */
/* [System] */

INLINE 
System *knh_System_ROOT(void) 
{
	return knh_System_gROOT; 
}

/* ------------------------------------------------------------------------ */

Object *knh_System_fvalue(Ctx *ctx, knh_class_t cid)
{
	return knh_System_gROOT; 
}

/* ======================================================================== */
/* [Bool] */

INLINE 
Bool *knh_Bool_TRUE(void) 
{
	return knh_Bool_gTRUE; 
}

/* ------------------------------------------------------------------------ */

INLINE 
Bool *knh_Bool_FALSE(void)
{
	return knh_Bool_gFALSE; 
}

/* ------------------------------------------------------------------------ */

Object *knh_Bool_fvalue(Ctx *ctx, knh_class_t cid)
{
	return knh_Bool_gFALSE; 
}

/* ------------------------------------------------------------------------ */
/* [NameSpace] */

INLINE
NameSpace *knh_NameSpace_SYSTEM(void)
{
	return knh_NameSpace_gSYSTEM;
}

/* ======================================================================== */
/* [ginit] */

void knh_konoha_ginit()
{
	knh_tstruct_ginit();
//	knh_tstruct_ginit_();
	knh_tclass_ginit();
	knh_tglobal_ginit();

	KNH_ASSERT(knh_Nue_gNULL == NULL);
	KNH_INITv(knh_Nue_gNULL, new_Nue__STEXT(NULL, "Null!!"));
	KNH_ASSERT(IS_NULL(KNH_NULL));
	KNH_ASSERT(knh_NameSpace_gSYSTEM == NULL);
	KNH_INITv(knh_NameSpace_gSYSTEM, new_NameSpace(NULL, KNH_NULL, new_String__STEXT(NULL, CLASS_String, "")));

	knh_tname_ginit();
	knh_texpt_ginit();
	knh_loader_ginit();

	konoha_load_builtins(NULL);
//	knh_tclass_ginit_();
//	knh_tmethod_ginit_();

	KNH_ASSERT(knh_Bool_gTRUE == NULL);
	KNH_INITv(knh_Bool_gTRUE, knh_Object_malloc0(NULL, KNH_FLAG_Bool, CLASS_Bool, sizeof(Bool)));
	((Bool*)knh_Bool_gTRUE)->value = 1;
	KNH_INITv(knh_Bool_gFALSE, knh_Object_malloc0(NULL, KNH_FLAG_Bool, CLASS_Bool, sizeof(Bool)));
	((Bool*)knh_Bool_gFALSE)->value = 0;
	KNH_ASSERT(knh_System_gROOT == NULL);
	KNH_INITv(knh_System_gROOT, new_System(NULL));
	KNH_ASSERT(knh_Runtime_gROOT == NULL);
	KNH_INITv(knh_Runtime_gROOT, new_Runtime(NULL, 0));
}

/* ------------------------------------------------------------------------ */

void knh_konoha_gtraverse(Ctx *ctx, f_gc gc)
{
	knh_loader_gtraverse(ctx, gc);
	
	knh_tglobal_gtraverse(ctx, gc);
	knh_texpt_gtraverse(ctx, gc);
	knh_tname_gtraverse(ctx, gc);

	gc(ctx, knh_Runtime_gROOT);
	gc(ctx, knh_System_gROOT);
	gc(ctx, knh_NameSpace_gSYSTEM);
	gc(ctx, knh_Bool_gTRUE);
	gc(ctx, knh_Bool_gFALSE);
	gc(ctx, knh_Nue_gNULL);

	knh_tclass_gtraverse(ctx, gc);
	
	if(IS_SWEEP(gc)) {
		knh_Runtime_gROOT = NULL;
		knh_System_gROOT  = NULL;
		knh_Nue_gNULL     = NULL;
		knh_Bool_gTRUE    = NULL;
		knh_Bool_gFALSE   = NULL;
	}
	
	knh_tstruct_gtraverse(ctx, gc);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
