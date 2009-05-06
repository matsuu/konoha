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
//mutexの作成 	pthread_mutex_init 	CreateMutex
//mutexのロックを取る 	pthread_mutex_lock 	WaitForSingleObject
//mutexのロックを解除する 	pthread_mutex_unlock 	ReleaseMutex
//mutexの破棄 	pthread_mutex_destroy 	CloseHandle
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
#ifdef KNH_USING_PTHREAD
#undef KNH_USING_NOTHREAD
	return pthread_self();
#endif
#ifdef KNH_USING_NOTHREAD
	return 0;
#endif
}

/* ------------------------------------------------------------------------ */

int thread_create(knh_thread_t *thread, void *attr, void *(*frun)(void *), void * arg)
{
#ifdef KNH_USING_PTHREAD
#undef KNH_USING_NOTHREAD
	return pthread_create((pthread_t*)thread, attr, frun, arg);
#endif
#ifdef KNH_USING_NOTHREAD
	return -1;
#endif
}

/* ======================================================================== */
/* [TLS] */

#ifdef KNH_USING_PTHREAD
static void destr(void *data)
{
	DBG2_P("destruction data=%p", data)
}
#endif

/* ------------------------------------------------------------------------ */

int knh_thread_key_create(knh_thread_key_t *key)
{
#ifdef KNH_USING_PTHREAD
	return pthread_key_create((pthread_key_t*)key, destr);
#endif
#ifdef KNH_USING_NOTHREAD
	return -1;
#endif
}

/* ------------------------------------------------------------------------ */

int knh_thread_setspecific(knh_thread_key_t key, const void *data)
{
#ifdef KNH_USING_PTHREAD
	return pthread_setspecific(key, data);
#endif
#ifdef KNH_USING_NOTHREAD
	return -1;
#endif
}

/* ------------------------------------------------------------------------ */

void* knh_thread_getspecific(knh_thread_key_t key)
{
#ifdef KNH_USING_PTHREAD
	return pthread_getspecific(key);
#endif
#ifdef KNH_USING_NOTHREAD
	return NULL;
#endif
}

/* ------------------------------------------------------------------------ */

int knh_thread_key_delete(knh_thread_key_t key)
{
#ifdef KNH_USING_PTHREAD
#undef KNH_USING_NOTHREAD
	return pthread_key_delete(key);
#endif
#ifdef KNH_USING_NOTHREAD
	return -1;
#endif
}

/* ======================================================================== */

#ifdef __cplusplus
}
#endif
