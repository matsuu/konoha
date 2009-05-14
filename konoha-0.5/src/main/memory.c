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

#define KNH_TOBJECT_C  1

#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

#define KNH_STATMODE0   -1  /* @property */

/* ======================================================================== */
/* [malloc] */

#ifdef KNH_DEBUGMODE2
static int canFree = 1;
#define DBG_ENABLE_FREE()     canFree = 1
#define DBG_DISABLE_FREE()    canFree = 0
#define DBG_ASSERT_FREE()     KNH_ASSERT(canFree)
#else
#define DBG_ENABLE_FREE()
#define DBG_DISABLE_FREE()
#define DBG_ASSERT_FREE()
#endif

/* ------------------------------------------------------------------------ */

void *knh_malloc(Ctx *ctx, size_t size)
{
#ifdef KONOHA_OS__TB
	if(size == 0) size=4;
#endif
	void *block = malloc(size);
	if (unlikely(block == NULL)) {
		KNH_EXIT("OutOfMemory!!: %d bytes used", (int)ctx->stat->usedMemorySize);
		//KNH_THROWs(ctx, "OutOfMemory!!");
	}
	knh_stat_incUsedMemorySize(ctx, size);
	return block;
}

/* ------------------------------------------------------------------------ */

void knh_free(Ctx *ctx, void *block, size_t size)
{
	DBG_ASSERT_FREE();
	SECURE_bzero(block, size);
	free(block);
	knh_stat_dclUsedMemorySize(ctx, size);
}

/* ------------------------------------------------------------------------ */

void *DBG2_malloc(Ctx *ctx, size_t size, char *func)
{
	size_t *block = (size_t*)malloc(size + sizeof(size_t));
	//if(size >32) { fprintf(stdout, "%p: M(%s, size=%d)\n", block, func, (int)size); };
	if (unlikely(block == NULL)) {
		KNH_EXIT("OutOfMemory!!: %d bytes used", (int)ctx->stat->usedMemorySize);
		//KNH_THROWs(ctx, "OutOfMemory!!");
	}
	knh_stat_incUsedMemorySize(ctx, size);
	block[0] = size;
	return (void*)(block + 1);
}

/* ------------------------------------------------------------------------ */

void DBG2_free(Ctx *ctx, void *p, size_t size, char *func)
{
	DBG_ASSERT_FREE();
	size_t *block = ((size_t*)p) - 1;
	if(size != block[0]) {
		fprintf(stderr, "%s: ptr = %p, block.size = %d, free.size=%d", func, p, (int)block[0], (int)size);
		KNH_ASSERT(size == block[0]);
	}
	block[0]=0;
	SECURE_bzero(block, size + sizeof(size_t));
	free(block);
	knh_stat_dclUsedMemorySize(ctx, size);
}

/* ======================================================================== */
/* [tObject] */

#define KNH_OBJECT_REUSE(ctx, used) { \
		used->ref = ctx->unusedObject;\
		((knh_Context_t*)ctx)->unusedObject = used;\
		((knh_Context_t*)ctx)->unusedObjectSize += 1;\
	}\


///* ------------------------------------------------------------------------ */
//
//static void* knh_pagetop(void *p)
//{
//	return (void*)((((knh_uint_t)p) / KONOHA_PAGESIZE) * KONOHA_PAGESIZE);
//}

/* ------------------------------------------------------------------------ */

static
knh_Object_t *new_UnusedObject(Ctx *ctx)
{
	KNH_LOCK(ctx, LOCK_MEMORY, NULL);
	int tindex = ctx->share->ObjectPageTableSize;
	if(unlikely(!(tindex < KNH_TOBJECTPAGE_SIZE))) {
		KNH_EXIT("Enlarge %d x %d", KNH_OBJECTPAGE_SIZE, KNH_TOBJECTPAGE_SIZE);
		KNH_UNLOCK(ctx, LOCK_MEMORY, NULL);
		return NULL;
	}
	ctx->share->ObjectPageTableSize += 1;
	KNH_UNLOCK(ctx, LOCK_MEMORY, NULL);

	char *t = (char*)KNH_MALLOC(ctx, SIZEOF_OBJECTPAGE);
	knh_bzero(t, SIZEOF_OBJECTPAGE);
	ctx->share->ObjectPageTable[tindex].ctxid = ctx->ctxid;
	ctx->share->ObjectPageTable[tindex].thead = t;
	if((knh_uintptr_t)t % KONOHA_PAGESIZE != 0) {
		t = (char*)((((knh_uintptr_t)t / KONOHA_PAGESIZE) + 1) * KONOHA_PAGESIZE);
		KNH_ASSERT((knh_uintptr_t)t % KONOHA_PAGESIZE == 0);
	}
	char *h = t, *max = ctx->share->ObjectPageTable[tindex].thead + SIZEOF_OBJECTPAGE;
	int cnt = 0;
	while(t + KONOHA_PAGESIZE < max) {
		size_t i;
		knh_Object_t *o = (knh_Object_t*)t;
		for(i = 1; i < (KONOHA_PAGESIZE / sizeof(knh_Object_t)) - 1; i++) {
			//o[i].h.magic = 0;
			o[i].ref = &(o[i+1]);
			cnt++;
		}
		t += KONOHA_PAGESIZE;
		if(t + KONOHA_PAGESIZE < max) {
			o[KONOHA_PAGESIZE / sizeof(knh_Object_t) - 1].ref = ((knh_Object_t*)t) + 1;
		}
		else {
			o[KONOHA_PAGESIZE / sizeof(knh_Object_t) - 1].ref = ctx->unusedObject;
		}
		cnt++;
	}
	((Context*)ctx)->unusedObject = ((knh_Object_t*)h) + 1;
	((Context*)ctx)->unusedObjectSize += cnt;
	DBG_P("*** new object page tindex=%d, ctxid=%d unused=%p,%d ***",
			tindex, ctx->ctxid, ctx->unusedObject, (int)ctx->unusedObjectSize);
	return ctx->unusedObject;
}

/* ------------------------------------------------------------------------ */
/* [fastmalloc] */

/* ------------------------------------------------------------------------ */

static void knh_setFastMallocMemory(void *p)
{
	knh_uintptr_t *b = (knh_uintptr_t*)((((knh_uintptr_t)p) / KONOHA_PAGESIZE) * KONOHA_PAGESIZE);
	int n = ((knh_uintptr_t)p % KONOHA_PAGESIZE) / sizeof(knh_Object_t);
	int x = n/(sizeof(knh_uintptr_t)*8);
	knh_uintptr_t mask = 1 << (n % (sizeof(knh_uintptr_t)*8));
	b[x] = b[x] | mask;
}

/* ------------------------------------------------------------------------ */

static void knh_unsetFastMallocMemory(void *p)
{
	knh_uintptr_t *b = (knh_uintptr_t*)((((knh_uintptr_t)p) / KONOHA_PAGESIZE) * KONOHA_PAGESIZE);
	int n = ((knh_uintptr_t)p % KONOHA_PAGESIZE) / sizeof(knh_Object_t);
	int x = n/(sizeof(knh_uintptr_t)*8);
	knh_uintptr_t mask = 1 << (n % (sizeof(knh_uintptr_t)*8));
	b[x] = b[x] & ~(mask);
}

/* ------------------------------------------------------------------------ */

int knh_isFastMallocMemory(void *p)
{
	knh_uintptr_t *b = (knh_uintptr_t*)((((knh_uintptr_t)p) / KONOHA_PAGESIZE) * KONOHA_PAGESIZE);
	int n = ((knh_uintptr_t)p % KONOHA_PAGESIZE) / sizeof(knh_Object_t);
	int x = n/(sizeof(knh_uintptr_t)*8);
	knh_uintptr_t mask = 1 << (n % (sizeof(knh_uintptr_t)*8));
	return ((b[x] & mask) == mask);
}

/* ------------------------------------------------------------------------ */

void *knh_fastmalloc(Ctx *ctx, size_t size)
{
	if(size <= KNH_FASTMALLOC_SIZE) {
		if(unlikely(ctx->unusedObject == NULL)) {
			KNH_ASSERT(ctx->unusedObjectSize == 0);
			((knh_Context_t*)ctx)->unusedObject = new_UnusedObject(ctx);
		}
		Object *o = ctx->unusedObject;
		((knh_Context_t*)ctx)->unusedObject = (knh_Object_t*)o->ref;
		((knh_Context_t*)ctx)->unusedObjectSize -= 1;
		DBG2_ASSERT(!knh_isFastMallocMemory((void*)o));
		knh_setFastMallocMemory((void*)o);
		return (void*)o;
	}
	void *block = malloc(size);
	if (unlikely(block == NULL)) {
		KNH_EXIT("OutOfMemory!!: %d bytes used", (int)ctx->stat->usedMemorySize);
		//KNH_THROWs(ctx, "OutOfMemory!!");
	}
	knh_stat_incUsedMemorySize(ctx, size);
	return block;
}

/* ------------------------------------------------------------------------ */

void knh_fastfree(Ctx *ctx, void *block, size_t size)
{
	DBG_ASSERT_FREE();
	if(size <= KNH_FASTMALLOC_SIZE) {
		DBG2_ASSERT(knh_isFastMallocMemory(block));
		knh_unsetFastMallocMemory(block);
		knh_Object_t *o = (knh_Object_t*)block;
		o->ref = ctx->unusedObject;
		((knh_Context_t*)ctx)->unusedObject = o;
		((knh_Context_t*)ctx)->unusedObjectSize += 1;
		o->h.magic = 0;
	}
	else {
		SECURE_bzero(block, size);
		free(block);
		knh_stat_dclUsedMemorySize(ctx, size);
	}
}

/* ------------------------------------------------------------------------ */
/* [hObject] */

knh_Object_t *new_hObject(Ctx *ctx, knh_flag_t flag, knh_class_t bcid, knh_class_t cid)
{
	DBG2_ASSERT(bcid != CLASS_Context);
	DBG2_ASSERT(bcid < KNH_TSTRUCT_SIZE);
	DBG2_ASSERT(ctx != NULL);
	if(unlikely(ctx->unusedObject == NULL)) {
		KNH_ASSERT(ctx->unusedObjectSize == 0);
		((knh_Context_t*)ctx)->unusedObject = new_UnusedObject(ctx);
	}
	{
		knh_Object_t *o = ctx->unusedObject;
		((knh_Context_t*)ctx)->unusedObject = (knh_Object_t*)o->ref;
		((knh_Context_t*)ctx)->unusedObjectSize -= 1;
		knh_stat_incUsedObjectSize(ctx, 1);
		o->h.magic = KNH_OBJECT_MAGIC;
		knh_Object_RCset(o, KNH_RCGC_INIT);
		o->h.flag = flag;
		o->h.bcid = bcid;
		o->h.cid  = cid;
		o->h.ctxid = ctx->ctxid;
		o->h.lock  = LOCK_NO;
		DBG2_({o->ref = NULL;});
		return o;
	}
}

/* ------------------------------------------------------------------------ */

knh_Object_t *new_Object_bcid(Ctx *ctx, knh_class_t bcid, int init)
{
	DBG2_ASSERT(bcid != CLASS_Context);
	DBG2_ASSERT(bcid < KNH_TSTRUCT_SIZE);
	if(unlikely(ctx->unusedObject == NULL)) {
		KNH_ASSERT(ctx->unusedObjectSize == 0);
		((knh_Context_t*)ctx)->unusedObject = new_UnusedObject(ctx);
	}
	{
		knh_Object_t *o = ctx->unusedObject;
		((knh_Context_t*)ctx)->unusedObject = (knh_Object_t*)o->ref;
		((knh_Context_t*)ctx)->unusedObjectSize -= 1;
		knh_stat_incUsedObjectSize(ctx, 1);
		o->h.magic = KNH_OBJECT_MAGIC;
		knh_Object_RCset(o, KNH_RCGC_INIT);
		o->h.flag = ctx->share->StructTable[bcid].flag;
		o->h.bcid = bcid;
		o->h.cid  = bcid;
		o->h.ctxid = ctx->ctxid;
		o->h.lock  = LOCK_NO;
		size_t size = ctx->share->StructTable[bcid].size;
		//DBG2_P("cid=%d,%s,size=%d", bcid, STRUCTN(bcid), size);
		if(size > 0) {
			o->ref = KNH_MALLOC(ctx, size);
		}
		else {
			o->ref = NULL;
		}
		ctx->share->StructTable[bcid].finit(ctx, o, init);
		return o;
	}
}

/* ------------------------------------------------------------------------ */

knh_Object_t *new_Object_init(Ctx *ctx, knh_flag_t flag, knh_class_t cid, int init)
{
	DBG2_ASSERT(cid != CLASS_Context);
	if(ctx->unusedObject == NULL) {
		KNH_ASSERT(ctx->unusedObjectSize == 0);
		((knh_Context_t*)ctx)->unusedObject = new_UnusedObject(ctx);
	}
	{
		knh_Object_t *o = ctx->unusedObject;
		((knh_Context_t*)ctx)->unusedObject = (knh_Object_t*)o->ref;
		((knh_Context_t*)ctx)->unusedObjectSize -= 1;
		knh_stat_incUsedObjectSize(ctx, 1);
		o->h.magic = KNH_OBJECT_MAGIC;
		knh_Object_RCset(o, KNH_RCGC_INIT);
		KNH_ASSERT_cid(cid);
		knh_class_t bcid = ctx->share->ClassTable[cid].bcid;
		o->h.bcid = bcid;
		o->h.flag = ctx->share->ClassTable[cid].oflag | flag;
		o->h.cid  = cid;
		o->h.ctxid = ctx->ctxid;
		o->h.lock  = LOCK_NO;
		size_t size = ctx->share->ClassTable[cid].size;
		if(size > 0) {
			o->ref = KNH_MALLOC(ctx, size);
		}
		else {
			o->ref = NULL;
		}
		ctx->share->StructTable[bcid].finit(ctx, o, init);
		return o;
	}
}

/* ------------------------------------------------------------------------ */

KNHAPI(Object*) new_Object_boxing(Ctx *ctx, knh_class_t cid, knh_sfp_t *sfp)
{
	KNH_ASSERT(ctx != NULL);
	if(unlikely(ctx->unusedObject == NULL)) {
		KNH_ASSERT(ctx->unusedObjectSize == 0);
		((knh_Context_t*)ctx)->unusedObject = new_UnusedObject(ctx);
	}
	{
		knh_Object_t *o = ctx->unusedObject;
		((knh_Context_t*)ctx)->unusedObject = (knh_Object_t*)o->ref;
		((knh_Context_t*)ctx)->unusedObjectSize -= 1;
		knh_stat_incUsedObjectSize(ctx, 1);
		o->h.magic = KNH_OBJECT_MAGIC;
		knh_Object_RCset(o, KNH_RCGC_INIT);
		o->h.flag = FLAG_Float;
		o->h.bcid = ctx->share->ClassTable[cid].bcid;
		o->h.cid  = cid;
		o->h.ctxid = ctx->ctxid;
		o->h.lock  = LOCK_NO;
		knh_Float_t *v = (knh_Float_t*)o;
		v->n.data = sfp[0].data;
		return o;
	}
}

/* ------------------------------------------------------------------------ */

void knh_Object_free(Ctx *ctx, knh_Object_t *o)
{
	DBG_ASSERT_FREE();
#ifdef KNH_USING_RCGC
	KNH_ASSERT(knh_Object_isRC0(o));
#endif
//	DBG2_P("o=%p, sid=%d,%s", o, o->h.bcid, STRUCTN(o->h.bcid));
	if(unlikely(o->h.magic == 0)) return;
	o->h.magic = 0;
	ctx->share->StructTable[o->h.bcid].ftraverse(ctx, o, knh_Object_sweep);
	size_t size = ctx->share->ClassTable[o->h.cid].size;
	if(size > 0) {
		KNH_FREE(ctx, o->ref, size);
	}
#ifdef KNH_FLAG_OF_METADATA
	if((o->h.flag & KNH_FLAG_OF_METADATA) == KNH_FLAG_OF_METADATA && ctx != NULL) {
		TODO();
//		knh_metadata_clear(ctx, o);
	}
#endif
	if(o->h.bcid == CLASS_Context) return;
	KNH_OBJECT_REUSE(ctx, o);
	knh_stat_dclUsedObjectSize(ctx, 1);
}

/* ------------------------------------------------------------------------ */

void knh_Object_traverse(Ctx *ctx, knh_Object_t *o, knh_ftraverse ftr)
{
	if(IS_SWEEP(ftr)) {
		knh_Object_free(ctx, o);
		return;
	}
	ctx->share->StructTable[o->h.bcid].ftraverse(ctx, o, ftr);
}


/* ========================================================================= */

#define BSHIFT ((KONOHA_PAGESIZE / sizeof(knh_Object_t)) / (sizeof(knh_uintptr_t) * 8))

static int mcount = 0;

/* ------------------------------------------------------------------------ */

void knh_Object_mark1(Ctx *ctx, Object *o)
{
	if(IS_Context(o)) {
		//DBG2_P("marked %p, cid=%d,%s", o, knh_Object_cid(o), CLASSN(knh_Object_cid(o)));
		knh_Object_traverse(ctx, o, knh_Object_mark1);
	}
	else {
		DBG2_ASSERT(o->h.magic == KNH_OBJECT_MAGIC);
		DBG2_ASSERT(!knh_isFastMallocMemory((void*)o));
		knh_uintptr_t *b = (knh_uintptr_t*)((((knh_uintptr_t)o) / KONOHA_PAGESIZE) * KONOHA_PAGESIZE);
		b = b + BSHIFT;
		int n = ((knh_uintptr_t)o % KONOHA_PAGESIZE) / sizeof(knh_Object_t);
		int x = n/(sizeof(knh_uintptr_t)*8);
		knh_uintptr_t mask = 1 << (n % (sizeof(knh_uintptr_t)*8));
		if(!((b[x] & mask) == mask)) {
			//DBG2_P("marked %p, cid=%d,%s", o, knh_Object_cid(o), CLASSN(knh_Object_cid(o)));
			mcount++;
			b[x] = b[x] | mask;
			knh_Object_traverse(ctx, o, knh_Object_mark1);
		}
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_Object_finalSweep(Ctx *ctx, Object *o)
{
	// DO Nothing;
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] void System.gc() */

METHOD knh__System_gc(Ctx *ctx, knh_sfp_t *sfp)
{
	int tindex, size = (int)(ctx->share->ObjectPageTableSize);

	DBG_P("** GC - Starting (used %d Kb) ***", (int)ctx->stat->usedMemorySize/1024);
	for(tindex = 0; tindex < size; tindex++) {
		char *t = ctx->share->ObjectPageTable[tindex].thead;

		if((knh_uintptr_t)t % KONOHA_PAGESIZE != 0) {
			t = (char*)((((knh_uintptr_t)t / KONOHA_PAGESIZE) + 1) * KONOHA_PAGESIZE);
			KNH_ASSERT((knh_uintptr_t)t % KONOHA_PAGESIZE == 0);
		}
		char *max = ctx->share->ObjectPageTable[tindex].thead + SIZEOF_OBJECTPAGE;
		while(t + KONOHA_PAGESIZE < max) {
			knh_uintptr_t *b = (knh_uintptr_t*)t;
			int i;
			for(i = 0; i < BSHIFT; i++) {
				b[i + BSHIFT] = b[i];
			}
			t += KONOHA_PAGESIZE;
		}
	}

	DBG_DISABLE_FREE();
	mcount = 0;
	konoha_traverse(ctx, knh_Object_mark1);
	DBG_ENABLE_FREE();
	DBG_P("** GC - Marked %d/%d object(s)", (int)mcount, (int)ctx->stat->usedObjectSize);

	size_t cnt = 0;
	knh_ftraverse fsweep = ctx->fsweep;
	((Context*)ctx)->fsweep = knh_Object_finalSweep;
	for(tindex = 0; tindex < size; tindex++) {
		char *t = ctx->share->ObjectPageTable[tindex].thead;

		if((knh_uintptr_t)t % KONOHA_PAGESIZE != 0) {
			t = (char*)((((knh_uintptr_t)t / KONOHA_PAGESIZE) + 1) * KONOHA_PAGESIZE);
			KNH_ASSERT((knh_uintptr_t)t % KONOHA_PAGESIZE == 0);
		}
		char *max = ctx->share->ObjectPageTable[tindex].thead + SIZEOF_OBJECTPAGE;

		while(t + KONOHA_PAGESIZE < max) {
			knh_uintptr_t *b = ((knh_uintptr_t*)t) + BSHIFT;
			int i;
			for(i = 1; i < (KONOHA_PAGESIZE / sizeof(knh_Object_t)); i++) {
				int x = i/(sizeof(knh_uintptr_t)*8);
				knh_uintptr_t mask = 1 << (i % (sizeof(knh_uintptr_t)*8));
				if((b[x] & mask) == mask) continue;
				knh_Object_t *o = ((Object*)t) + i;
				DBG2_ASSERT(!knh_isFastMallocMemory((void*)o));
				knh_Object_RCset(o, 0);
				if(o->h.magic == 0) continue;
				//DBG2_P("i=%d, x=%d, o=%p, magic=%d, cid=%s(%d)", i, x, o, o->h.magic, CLASSN(o->h.bcid), o->h.bcid);
				knh_Object_free(ctx, o);
				cnt++;
			}
			t += KONOHA_PAGESIZE;
		}
	}
	((Context*)ctx)->fsweep = fsweep;
	DBG_P("** GC - Collected %d/%d object(s) used=%d Kbytes", (int)cnt, (int)ctx->stat->usedObjectSize, (int)ctx->stat->usedMemorySize/1024);
}

/* ------------------------------------------------------------------------ */

void knh_System_gc(Ctx *ctx)
{
	knh__System_gc(ctx, NULL);
}

/* ------------------------------------------------------------------------ */
/* [RCGC] */

void knh_Object_RCsweep(Ctx *ctx, Object *o)
{
	knh_Object_RCdec(o);
	if(knh_Object_isRC0(o)) {
		knh_Object_free(ctx, o);
	}
}

/* ------------------------------------------------------------------------ */

knh_ftraverse konoha_getDefaultSweepFunc()
{
	return knh_Object_RCsweep;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
