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

#ifdef KNH_USING_PTHREAD
#include<pthread.h>
#endif


/* ************************************************************************ */

//機能 	pthread関数名 	win32 スレッドapi名
//スレッドの作成 	pthread_create 	CreateThread, _beginthreadex*2
//自スレッドの終了 	pthread_exit 	ExitThread, _endthreadex*3
//他スレッドを終了 	pthread_cancel 	TerminateThread*4
//スレッド終了時に自動的にスレッド作成時に確保したデータ(stack領域等）を解放するように指示 	pthread_detach 	デフォルトでこの設定
//他スレッドの終了を待つ 	pthread_join 	WaitForSingleObject, WaitForMultipleObjects
//使い終わったスレッドid(handle)を解放する 	解放する必要なし 	CloseHandle
//現在実行中のスレッドのid(handle)を返す 	pthread_self 	GetCurrentThread
//スレッド固有の大域変数(TSD*5 or TLS*6 )を指す領域を確保 	pthread_key_create 	TlsAlloc
//TSD(TLS)を指す領域を解放 	pthread_key_delete 	TlsFree
//TSD(TLS)のアドレスを得る 	pthread_getspecific 	TlsGetValue
//TSD(TLS)のアドレスをセット 	pthread_setspecific 	TlsSetValue

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [TLS] */

knh_thread_t knh_thread_self(void)
{
#if defined(KNH_USING_PTHREAD)
	return pthread_self();
#else
	return 0;
#endif
}

/* ------------------------------------------------------------------------ */

int knh_thread_create(Ctx *ctx, knh_thread_t *thread, void *attr, void *(*frun)(void *), void * arg)
{
#if defined(KNH_USING_PTHREAD)
	return pthread_create((pthread_t*)thread, attr, frun, arg);
#else
	return -1;
#endif
}

/* ------------------------------------------------------------------------ */

int knh_thread_detach(Ctx *ctx, knh_thread_t *thread)
{
#if defined(KNH_USING_PTHREAD)
	return pthread_detach(*thread);
#else
	return 0;
#endif
}

/* ------------------------------------------------------------------------ */
/* @data */

typedef struct knh_threadcc_t {
	Ctx *ctx;
	knh_sfp_t *sfp;
} knh_threadcc_t ;

static void *threading(void *p)
{
	knh_threadcc_t ta = *((knh_threadcc_t*)p);
	Ctx *ctx = new_ThreadContext(ta.ctx);

	knh_setCurrentContext(ctx);
	knh_sfp_t *lsfp = ctx->stack;

	KNH_MOV(ctx, lsfp[0].o, new_ExceptionHandler(ctx));
	KNH_TRY(ctx, L_CATCH, lsfp, 0);
	{
		Method *mtd = ta.sfp[0].mtd;
		DBG2_ASSERT(IS_Method(mtd));
		KNH_SETv(ctx, lsfp[1].o, mtd);
		KNH_SETv(ctx, lsfp[2].o, ta.sfp[1].o);
		lsfp[2].data = knh_Object_data(ta.sfp[1].o);
		{
			int i, args = knh_Method_psize(mtd);
			for(i = 0; i < args; i++) {
				KNH_SETv(ctx, lsfp[3+i].o, ta.sfp[2+i].o);
				lsfp[3+i].data = knh_Object_data(ta.sfp[2+i].o);
			}
			KNH_SCALL(ctx, lsfp, 1, mtd, args);
		}
		goto L_FINALLY;
	}
	/* catch */
	L_CATCH:;
	KNH_PRINT_STACKTRACE(ctx, lsfp, 0);

	L_FINALLY:
	knh_Context_clearstack(ctx);
	knh_setCurrentContext(NULL);
	knh_ThreadContext_dispose(ctx);
	return NULL;
}

/* ------------------------------------------------------------------------ */

void knh_stack_threadRun(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_thread_t th;
	knh_threadcc_t ta = {ctx, sfp};
	knh_thread_create(ctx, &th, NULL, threading, (void*)&ta);
	knh_thread_detach(ctx, &th);
}

/* ======================================================================== */
/* [mutex] */

//mutexの作成 	pthread_mutex_init 	CreateMutex
//mutexのロックを取る 	pthread_mutex_lock 	WaitForSingleObject
//mutexのロックを解除する 	pthread_mutex_unlock 	ReleaseMutex
//mutexの破棄 	pthread_mutex_destroy 	CloseHandle

int knh_mutex_init(knh_mutex_t *m)
{
#if defined(KNH_USING_PTHREAD)
	return pthread_mutex_init((pthread_mutex_t*)m, NULL);
#else
	return -1;
#endif
}

/* ------------------------------------------------------------------------ */

int knh_mutex_lock(knh_mutex_t *m)
{
#if defined(KNH_USING_PTHREAD)
	return pthread_mutex_lock((pthread_mutex_t*)m);
#else
	return -1;
#endif
}

/* ------------------------------------------------------------------------ */

int knh_mutex_unlock(knh_mutex_t *m)
{
#if defined(KNH_USING_PTHREAD)
	return pthread_mutex_unlock((pthread_mutex_t*)m);
#else
	return -1;
#endif
}

/* ------------------------------------------------------------------------ */

int knh_mutex_destory(knh_mutex_t *m)
{
#if defined(KNH_USING_PTHREAD)
	return pthread_mutex_destory((pthread_mutex_t*)m);
#else
	return -1;
#endif
}

/* ======================================================================== */
/* [TLS] */

#if defined(KNH_USING_PTHREAD)
static void destr(void *data)
{
	DBG2_P("destruction data=%p", data)
}
#endif

/* ------------------------------------------------------------------------ */

int knh_thread_key_create(knh_thread_key_t *key)
{
#if defined(KNH_USING_PTHREAD)
	return pthread_key_create((pthread_key_t*)key, destr);
#else
	return -1;
#endif
}

/* ------------------------------------------------------------------------ */

int knh_thread_setspecific(knh_thread_key_t key, const void *data)
{
#if defined(KNH_USING_PTHREAD)
	return pthread_setspecific(key, data);
#else
	return -1;
#endif
}

/* ------------------------------------------------------------------------ */

void* knh_thread_getspecific(knh_thread_key_t key)
{
#if defined(KNH_USING_PTHREAD)
	return pthread_getspecific(key);
#else
	return NULL;
#endif
}

/* ------------------------------------------------------------------------ */

int knh_thread_key_delete(knh_thread_key_t key)
{
#if defined(KNH_USING_PTHREAD)
	return pthread_key_delete(key);
#else
	return -1;
#endif
}

/* ======================================================================== */

#ifdef __cplusplus
}
#endif
