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
/* [tContext] */

#ifndef KNH_TCONTEXT_SIZE
#define KNH_TCONTEXT_SIZE   4
#endif

#define SIZEOF_TCONTEXT (KNH_TCONTEXT_SIZE * sizeof(knh_Context_t))
	
knh_Context_t *knh_tContext = NULL;
static size_t knh_tContextSize = 0;

/* ------------------------------------------------------------------------ */
/* [tContext] */

void knh_tContext_init0(void)
{
	KNH_ASSERT(knh_tContext == NULL);
	knh_tContext = (knh_Context_t*)KNH_MALLOC(NULL, SIZEOF_TCONTEXT);
	{
		int i;
		for(i = 0; i < KNH_TCONTEXT_SIZE; i++) {
			knh_Context_t *o = &knh_tContext[i];
			o->h.magic = KNH_OBJECT_MAGIC;
			o->h.refc = 1;
			o->h.flag = FLAG_Context;
			o->h.bcid = CLASS_Context;
			o->h.cid  = CLASS_Context;
			
			o->unusedObject = NULL;
			o->unusedObjectSize = 0;
			
			o->runtime = NULL;  /* unused context */
		}
	}
}

/* ------------------------------------------------------------------------ */

static
knh_Context_t *new_UnusedContext()
{
	int i;
	for(i = 0; i < KNH_TCONTEXT_SIZE; i++) {
		knh_Context_t *o = &knh_tContext[i];
		if(o->runtime == NULL) {
			knh_tContextSize++;
			return o;
		}
	}
	TODO();
	KNH_EXIT("No context!!");
}

/* ------------------------------------------------------------------------ */

#ifdef KNH_DBGMODE
#define FLAG_CTX(f)      (f|KNH_FLAG_CTXF_VERBOSE)
#else
#define FLAG_CTX(f)      (f)
#endif

knh_Context_t *new_Context0(Runtime *runtime, size_t stacksize)
{
	knh_Context_t *o = new_UnusedContext();
	Ctx *ctx = (Ctx*)o;
	KNH_ASSERT(o->runtime == NULL);
	KNH_INITv(o->runtime, runtime);
	DP(o->runtime)->ctxcount += 1;
	
	o->flag  = FLAG_CTX(0);
	o->stacksize = (stacksize < 64) ? KNH_STACKSIZE : stacksize;
	o->stack = (knh_sfp_t*)KNH_MALLOC(ctx, sizeof(knh_sfp_t) * o->stacksize);
	o->ebp = o->stack;
	{
		int i;
		for(i = 0; i < o->stacksize; i++) {
			KNH_INITv(o->stack[i].o, KNH_NULL);
			o->stack[i].op = 0;
		}
		KNH_SETv(ctx, o->stack[o->stacksize-1].o, new_Nue__T(ctx, "StackOverflow!!"));
		knh_Nue_setGCHook(o->stack[o->stacksize-1].o, 1);
	}

	KNH_INITv(o->bufa, new_Bytes(ctx, o->stacksize * 4));
	KNH_INITv(o->bufw, new_OutputStream__Bytes(ctx, o->bufa));
	KNH_INITv(o->bconvbuf, new_Bytes(ctx, 256));
	KNH_INITv(o->props, new_DictMap(ctx, 16));
	
	KNH_INITv(o->enc, knh_systemEncoding);
	KNH_INITv(o->in,  knh_systemStdIn);
	KNH_INITv(o->out, knh_systemStdOut);
	KNH_INITv(o->err, knh_systemStdErr);
	
	KNH_INITv(o->tmapperHashMap, new_HashMap(ctx, "tmapperHashMap", 0));
	KNH_INITv(o->tmethodHashMap, new_HashMap(ctx, "tmethodHashMap", 0));

	KNH_INITv(o->ns,   KNH_NULL);
	KNH_INITv(o->cmpr, KNH_NULL);

	//	o->cacheIntLRUMap = NULL;
//	o->cacheFloatLRUMap = NULL;
//	o->cacheStringLRUMap = NULL;
	return o;
}

/* ------------------------------------------------------------------------ */

void knh_Context_traverse(Ctx *ctx, knh_Context_t *o, f_traverse ftr)
{
	if(IS_SWEEP(ftr)) {
		knh_Nue_setGCHook(o->stack[o->stacksize-1].o, 0);
	}
	{
		int i;
		for(i = 0; i < o->stacksize; i++) {
			ftr(ctx, o->stack[i].o);
		}
		if(IS_SWEEP(ftr)) {
			KNH_FREE(o->stack, sizeof(knh_sfp_t) * o->stacksize);
			o->stack = NULL;
			o->ebp = NULL;
		}
	}

	ftr(ctx, UP(o->bufa));
	ftr(ctx, UP(o->bufw));
	ftr(ctx, UP(o->bconvbuf));
	ftr(ctx, UP(o->props));
	ftr(ctx, UP(o->enc));
	ftr(ctx, UP(o->in));
	ftr(ctx, UP(o->out));
	ftr(ctx, UP(o->err));
	ftr(ctx, UP(o->tmapperHashMap));
	ftr(ctx, UP(o->tmethodHashMap));
	ftr(ctx, UP(o->ns));
	ftr(ctx, UP(o->cmpr));
	ftr(ctx, UP(o->runtime));

	if(IS_SWEEP(ftr)) {
		DP(o->runtime)->ctxcount -= 1;
		o->runtime = NULL;           /* TO SET UNUSED */
	}
}

/* ------------------------------------------------------------------------ */

void knh_tContext_traverse(Ctx* ctx, f_traverse f)
{
	int i;
	for(i = 0; i < KNH_TCONTEXT_SIZE; i++) {
		knh_Context_t *o = &knh_tContext[i];
		if(o->runtime != NULL) {
			knh_Context_traverse(ctx, o, f);
		}
	}
	if(IS_SWEEP(f)) {
		KNH_FREE(knh_tContext, SIZEOF_TCONTEXT);
		knh_tContext = NULL;
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
