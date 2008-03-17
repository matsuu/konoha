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


#define SELF STRUCT_Object

#ifndef DEBUG_Object
#undef  DEBUG
#define DEBUG(fmt, ...)
#undef  DEBUG_ASSERT
#define DEBUG_ASSERT(c)
#endif

/* Prototypetypes in this file */
size_t knh_tmemory_used_size(void) ;
void knh_diagnose_memory(Ctx *ctx, Object *tgt);
size_t knh_tmemory_round(size_t size) ;
void *knh_malloc(Ctx *ctx, size_t size) ;
void *knh_realloc(Ctx *ctx, void *ptr, size_t oldsize, size_t newsize) ;
void knh_free(void *block, size_t size);
void knh_tmemory_beginMemoryLeakNotice();
void knh_tmemory_endMemoryLeakNotice();


/* Checks */
#define CHECK_knh_tmemory_used_size
#define CHECK_knh_diagnose_memory
#define CHECK_knh_tmemory_round
#define CHECK_knh_malloc
#define CHECK_knh_realloc
#define CHECK_knh_free
#define CHECK_knh_tmemory_beginMemoryLeakNotice
#define CHECK_knh_tmemory_endMemoryLeakNotice


/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

static size_t tglobal_used_memory = 0;

#ifdef KONOHA_SAFEMODE
static knh_bool_t tmemoryMemoryLeak = 0;
#endif

/* ======================================================================== */
/* [mem] */

INLINE 
size_t knh_tmemory_used_size(void) 
{
   return tglobal_used_memory; 
}

/* ------------------------------------------------------------------------ */


void *knh_malloc(Ctx *ctx, size_t size) 
{
	void *block = malloc(size);
	if (block == NULL) {
		//KNH_REPORT(ctx, ctx, LG_RED, "OutOfMemory!!: used %d requested %d", tglobal_used_memory, size);
		KNH_THROWs(ctx, "OutOfMemory!!");
	}
	tglobal_used_memory += size;
	return block;
}

/* ------------------------------------------------------------------------ */


void knh_free(void *block, size_t size)
{
	tglobal_used_memory -= size;
	free(block);
}


/* ======================================================================== */
/* [mem_leak] */

void knh_tmemory_beginMemoryLeakNotice()
{
#ifdef KONOHA_SAFEMODE
	if(tmemoryMemoryLeak == 0) {
		fprintf(stderr, "\n\n");
		fprintf(stderr, "/* ************************************************************************ */\n");
		fprintf(stderr, "/* NOTICE OF MEMORY LEAKS by konohaVM */\n");
	}
	tmemoryMemoryLeak = 1;
#endif
}

/* ------------------------------------------------------------------------ */

void knh_tmemory_endMemoryLeakNotice()
{
#ifdef KONOHA_SAFEMODE
	if(tmemoryMemoryLeak == 1) {
		fprintf(stderr, "/* ************************************************************************ */\n");
	}
	tmemoryMemoryLeak = 0;
#endif
}


#ifdef __cplusplus
}
#endif
