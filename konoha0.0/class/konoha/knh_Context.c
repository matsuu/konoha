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

#ifndef KONOHA_CONTEXT_BUFSIZ
#define KONOHA_CONTEXT_BUFSIZ  4096
#endif

/* ------------------------------------------------------------------------ */
/* [macros] */

#define _KNH_STDIN          (((Context*)ctx)->in)
#define _KNH_STDOUT         (((Context*)ctx)->out)
#define _KNH_STDERR         (((Context*)ctx)->err)

#define _IntCache(ctx)      ((Context*)ctx)->cacheIntLRUMap
#define _FloatCache(ctx)    ((Context*)ctx)->cacheFloatLRUMap
#define _StringCache(ctx)   ((Context*)ctx)->cacheStringLRUMap


/* ======================================================================== */
/* [structs] */

void
knh_Context_struct_init(Ctx *ctx0, Struct *s, int init, Object *cs)
{
	Context *b = (Context*)s;
	init = (init == DEFAULT_SIZE) ? KONOHA_STACK_SIZE : init;
	if(ctx0 != NULL) {
		b->runtime = ((Context*)ctx0)->runtime;
	}else{
		b->runtime = NULL;
	}
	
	b->flag   = 0;
	b->size  = (size_t)knh_int_max(init, 64);
	b->stack = knh_oarray_malloc(ctx0, b->size, KNH_NULL);
	KNH_SETv(ctx0, b->stack[b->size-1], new_Nue__STEXT(ctx0, "StackOverflow!!"));
	knh_Nue_setGCHook(b->stack[b->size-1], 1);
	b->ebp = b->stack;
	b->stackop = (knh_uint_t*)knh_malloc(ctx0, sizeof(knh_stackop_t) * b->size);
//	int i;
//	for(i = 0; i < b->size; i++) {
//		b->stackop[i] = i;
//	}
	knh_bzero(b->stackop, sizeof(knh_uint_t) * b->size);

	KNH_INITv(b->name, knh_String_EMPTY());
	KNH_INITv(b->bufa, new_Bytes(ctx0, KONOHA_CONTEXT_BUFSIZ));
	KNH_INITv(b->bufw, new_OutputStream__Bytes(ctx0, b->bufa));
	KNH_INITv(b->props, new_DictMap(ctx0, 16));
	KNH_INITv(b->in,  new_InputStream__FILE(ctx0, stdin));
	KNH_INITv(b->out, new_OutputStream__FILE(ctx0, stdout));
	KNH_INITv(b->err, new_OutputStream__FILE(ctx0, stderr));

	KNH_INITv(b->cmpl, KNH_NULL);
	;
	b->cacheIntLRUMap = NULL;
	b->cacheFloatLRUMap = NULL;
	b->cacheStringLRUMap = NULL;
	;
}

/* ------------------------------------------------------------------------ */

#define _knh_Context_struct_copy   NULL

/* ------------------------------------------------------------------------ */

#define _knh_Context_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void
knh_Context_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Context *b = (Context*)s;
	if(IS_SWEEP(gc)) {
		knh_Nue_setGCHook(b->stack[b->size-1], 0);
		knh_free(b->stackop, sizeof(knh_stackop_t) * b->size);
		b->runtime = NULL;
	}
	knh_oarray_traverse(ctx, b->stack, b->size, gc);

	gc(ctx, b->name);
	gc(ctx, b->bufw);
	gc(ctx, b->bufa);
	gc(ctx, b->props);
	gc(ctx, b->in);
	gc(ctx, b->out);
	gc(ctx, b->err);
	gc(ctx, b->cmpl);

	if(b->cacheIntLRUMap != NULL) {
		gc(ctx, b->cacheIntLRUMap);
	}
	if(b->cacheFloatLRUMap != NULL) {
		gc(ctx, b->cacheFloatLRUMap);
	}
	if(b->cacheStringLRUMap != NULL) {
		gc(ctx, b->cacheStringLRUMap);
	}
}

/* ======================================================================== */
/* [constructors] */

Context* new_Context(Ctx *ctx0, Runtime *runtime, String *name, size_t size)
{
//	DEBUG("%s", knh_String_tochar(name));
	Context* b = (Context*)
		knh_Object_malloc0(ctx0, KNH_FLAG_Context, CLASS_Context, sizeof(Context));
	knh_Context_struct_init(ctx0, (Struct*)b, size, NULL);
	b->runtime  = runtime;  /* @see(Runtime->tnameContextDictMap) */
	KNH_SETv(ctx0, b->name, name);

	/* The cache should be switched by flag in future */
	//KNH_INITv(b->cacheIntLRUMap, new_LRUMap(ctx0, 1237));
	return b;
}

/* ------------------------------------------------------------------------ */

Object* knh_Context_fvalue(Ctx *ctx, knh_class_t cid)
{
	return (Context*)ctx;
}

/* ======================================================================== */
/* [properties] */

/* ------------------------------------------------------------------------ */
/* @method Any Context.getProperty(String! key) */

Any* knh_Context_getProperty(Ctx *ctx, Context *b, knh_bytes_t key)
{
	Any *v = knh_DictMap_getb(ctx, b->props, key);	
	if(IS_NULL(v)) {
		return knh_System_getProperty(ctx, knh_System_ROOT(), key);
	}
	return v;
}

/* ------------------------------------------------------------------------ */
/* @method void Context.setProperty(String! key, Any value) */


void knh_Context_setProperty(Ctx *ctx, Context *b, String *key, Any *value)
{
	knh_DictMap_set(ctx, b->props, key, value);	
}

/* ======================================================================== */
/* [movabletext] */

/* @method void Context.%dump(OutputStream w, Any m) */

void knh_Context__dump(Ctx *ctx, Context *b, OutputStream *w, Any *m)
{
//	knh_int_t i = 0;
//	for(i = b->ebp - b->stack; i >= 0; i--) {
//		knh_printf(ctx, w, "[%d]\t%o\n", i, b->stack[i]);
//	}	
}


#ifdef __cplusplus
}
#endif
