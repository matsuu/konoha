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

#ifndef KONOHA_TGLOBAL_SIZE
#define KONOHA_TGLOBAL_SIZE 256
#endif 

#define TGLOBALDB_SIZE  (KONOHA_TGLOBAL_SIZE * sizeof(Object**))

static Object ***tglobalList           = 0;
static size_t    tglobalList_size      = 0;

/* ------------------------------------------------------------------------ */

void knh_tglobal_ginit()
{
	KNH_ASSERT(tglobalList == NULL);
	tglobalList = (Object***)knh_malloc(NULL, TGLOBALDB_SIZE);
	tglobalList_size = 0;
	size_t i;
	for(i = 0; i < KONOHA_TGLOBAL_SIZE; i++) {
		tglobalList[i] = NULL;
	}
}

/* ------------------------------------------------------------------------ */

#define _KNH_TGLOBAL(v)   knh_tglobal_insert(&(v))

void knh_tglobal_insert(Object **var)
{
	if(tglobalList_size == KONOHA_TGLOBAL_SIZE) {
		KNH_NOTICE("Enlarge KONOHA_TGLOBAL_SIZE: %d", KONOHA_TGLOBAL_SIZE);
		return;
	}
	tglobalList[tglobalList_size] = var;
	knh_Object_refc_inc(var[0]);
	tglobalList_size++;
}

/* ------------------------------------------------------------------------ */

void knh_tglobal_gtraverse(Ctx *ctx, f_gc gc)
{
	knh_int_t i;
	if(IS_SWEEP(gc)) {
		for(i = tglobalList_size - 1; i >= 0; i--) {
			Object **var = tglobalList[i];
//			DEBUG("cid=%d", knh_Object_cid(var[0]));
			gc(ctx, var[0]);
			var[0] = NULL;
		}
		knh_free(tglobalList, TGLOBALDB_SIZE);
		tglobalList = NULL;
	}
	else {
		for(i = tglobalList_size - 1; i >= 0; i--) {
			Object **var = tglobalList[i];
			gc(ctx, var[0]);
		}
	}		
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
