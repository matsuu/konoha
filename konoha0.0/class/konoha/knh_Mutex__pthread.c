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

/* ------------------------------------------------------------------------ */
/* [macros] */


#ifdef KONOHA_LIBPTHREAD
//static int knh_mutex_pthread_loaded = 0;
//typedef int (*f_pthread_mutex_init)(pthread_mutex_t*, const pthread_mutexattr_t*);
//typedef int (*f_pthread_mutex_lock)(pthread_mutex_t*);
//typedef int (*f_pthread_mutex_unlock)(pthread_mutex_t*);
//typedef int (*f_pthread_mutex_destory)(pthread_mutex_t*);
//static f_pthread_mutex_init    knh_mutex_init    = NULL;
//static f_pthread_mutex_lock    knh_mutex_lock    = NULL;
//static f_pthread_mutex_unlock  knh_mutex_unlock  = NULL;
//static f_pthread_mutex_destory knh_mutex_destory = NULL;
#endif

/* ------------------------------------------------------------------------ */
/* [macros] */

#define _KNH_MUTEX_RECURSIVE    0
#define _KNH_MUTEX_FAST         1

#define KNH_MUTEX_MAGIC         20071001
#define IS_MUTEX(b)            (b->magic == KNH_MUTEX_MAGIC)

/* ======================================================================== */
/* [structs] */

void knh_Mutex_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	Mutex *b =  (Mutex*)s1;
	b->magic = KNH_MUTEX_MAGIC;
#ifdef KONOHA_LIBPTHREAD
//	if(knh_pthread_loaded == 0) {
//		knh_mutex_init = 
//			(f_pthread_mutex_init)knh_loader_load_dylib(ctx, NULL, "pthread", NULL, "pthread_mutex_init", knh_mutex_init__nop);
//		knh_mutex_lock = 
//			(f_pthread_mutex_lock)knh_loader_load_dylib(ctx, NULL, "pthread", NULL, "pthread_mutex_lock", knh_mutex_lock__nop);
//		knh_mutex_unlock = 
//			(f_pthread_mutex_unlock)knh_loader_load_dylib(ctx, NULL, "pthread", NULL, "pthread_mutex_unlock", knh_mutex_unlock__nop);
//		knh_mutex_destory = 
//			(f_pthread_mutex_destroy)knh_loader_load_dylib(ctx, NULL, "pthread", NULL, "pthread_mutex_destory", knh_mutex_destory__nop);
//		dylib_thread = 1;		
//	}
	if(init == KNH_MUTEX_FAST) {
		pthread_mutex_init(&b->mutex, PTHREAD_MUTEX_INITIALIZER);
	} else {
		pthread_mutex_init(&b->mutex, PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP);
	}
#endif
	b->loccount = 0;
}

/* ------------------------------------------------------------------------ */

#define _knh_Mutex_struct_copy  NULL
#define _knh_Mutex_struct_compare   NULL

/* ------------------------------------------------------------------------ */

void
knh_Mutex_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Mutex *b = (Mutex*)s;
	DEBUG_ASSERT(IS_MUTEX(b));
	if(IS_SWEEP(gc)) {
		if(b->loccount != 0) {
			DEBUG("this mutex is still unlocked");
		}
#ifdef KONOHA_LIBPTHREAD
		pthread_mutex_destory(&b->mutex);
#endif
	}
}

/* ======================================================================== */
/* [constructors] */

Mutex* new_Mutex(Ctx *ctx)
{
	Mutex* b = (Mutex*)knh_Object_malloc0(ctx, KNH_FLAG_Mutex, CLASS_Mutex, sizeof(Mutex));
	knh_Mutex_struct_init(ctx, (Struct*)b, KNH_MUTEX_FAST, NULL);
	return b;
}

/* ======================================================================== */
/* [lock] */

void knh_Mutex_lock(Ctx *ctx, Mutex *b)
{
	DEBUG_ASSERT(IS_MUTEX(b));
#ifdef KONOHA_LIBPTHREAD
	pthread_mutex_lock(&b->mutex);
	b2->loccount++;
#endif
}

/* ------------------------------------------------------------------------ */

void knh_Mutex_unlock(Ctx *ctx, Mutex *b)
{
	DEBUG_ASSERT(IS_MUTEX(b));
#ifdef KONOHA_LIBPTHREAD
	b2->loccount--;
	pthread_mutex_lock(&b->mutex);
#endif
}

/* ======================================================================== */
/* [Object] */

void knh_Object_lock(Ctx *ctx, Object *b)
{
	if(!knh_Object_isSynchronized(b)) {
		KNH_NOTICE(ctx, "trying lock unlockable object");
		return;
	}
	if(IS_Mutex(b)) {
		knh_Mutex_lock(ctx, b);
	}
	else {
		knh_Mutex_lock(ctx, b + knh_tclass_size(knh_Object_cid(b)));
	}
}

/* ------------------------------------------------------------------------ */

void knh_Object_unlock(Ctx *ctx, Object *b)
{
	if(!knh_Object_isSynchronized(b)) {
		return;
	}
	if(IS_Mutex(b)) {
		knh_Mutex_unlock(ctx, b);
	}
	else {
		knh_Mutex_unlock(ctx, b + knh_tclass_size(knh_Object_cid(b)));
	}
}

/* ======================================================================== */
/* [movabletext] */

/* @method void Mutex.%dump(OutputStream w, Any m) */

void knh_Mutex__dump(Ctx *ctx, Mutex *b, OutputStream *w, Any *m)
{
	if(b->loccount == 0) {
		knh_write__s(ctx, w, "mutex: unlocked");
	}
	else{
		knh_write__s(ctx, w, "mutex: locked ");
		knh_write__i(ctx, w, b->loccount);
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
