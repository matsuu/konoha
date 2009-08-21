/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2005-2009, Kimio Kuramitsu <kimio at ynu.ac.jp>
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

#define KNH_TSTRUCT_C

#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [ContextTable] */

void knh_loadSystemString(Ctx *o); /* konoha_data.c */
void knh_loadSystemStructData(Ctx *o);
void knh_loadSystemData(Ctx *o);

/* ======================================================================== */
/* [INITCONST] */

static Object *new_Null(Ctx *ctx)
{
	knh_Glue_t *glue = (knh_Glue_t*)new_hObject(ctx, KNH_FLAG_OF_IMMUTABLE, CLASS_Any, CLASS_Any);
	knh_Glue_init(ctx, glue, NULL, NULL);
	return (Object*)glue;
}

/* ------------------------------------------------------------------------ */

static knh_Object_t *new_Boolean0(Ctx *ctx, knh_bool_t tf)
{
	knh_Boolean_t *o = (knh_Boolean_t*)new_hObject(ctx, FLAG_Boolean, CLASS_Boolean, CLASS_Boolean);
	o->n.bvalue = tf;
	return (knh_Object_t*)o;
}

/* ------------------------------------------------------------------------ */

static knh_System_t *new_System(Ctx *ctx)
{
	return (knh_System_t*)new_Object_bcid(ctx, CLASS_System, 0);
}

/* ------------------------------------------------------------------------ */

#ifdef KNH_DBGMODE
#define FLAG_CTX(f)      (f|KNH_FLAG_CTXF_VERBOSE|KNH_FLAG_CTXF_STRICT)
#else
#define FLAG_CTX(f)      (f|KNH_FLAG_CTXF_STRICT)
#endif


/* ------------------------------------------------------------------------ */

static
void knh_Object_finalSweep(Ctx *ctx, Object *o)
{
	// DO Nothing;
}

/* ------------------------------------------------------------------------ */

static
void knh_ObjectPageTable_free(Ctx *ctx, char *thead)
{
	char *t = thead, *max = thead + SIZEOF_OBJECTPAGE;
	if((knh_uintptr_t)t % KONOHA_PAGESIZE != 0) {
		t = (char*)((((knh_uintptr_t)t / KONOHA_PAGESIZE) + 1) * KONOHA_PAGESIZE);
		KNH_ASSERT((knh_uintptr_t)t % KONOHA_PAGESIZE == 0);
	}
	while(t + KONOHA_PAGESIZE < max) {
		size_t i;
		for(i = 1; i < (KONOHA_PAGESIZE / sizeof(knh_Object_t)); i++) {
			Object *o = ((knh_Object_t*)t) + i;
			if(o->h.magic != KNH_OBJECT_MAGIC) continue;
#ifdef KNH_HOBJECT_REFC
			DBG_(
			{
				switch(o->h.bcid) {
				case CLASS_Class:
					fprintf(stderr, "async mem cid=%d, refc=%d\n", (int)((knh_Class_t*)o)->cid, (int)o->h.refc);
				break;
				case CLASS_Int:
					fprintf(stderr, "async mem cid=%s(%d), refc=%d ivalue='%d'\n", STRUCTN(o->h.bcid), (int)o->h.cid, (int)o->h.refc, (int)((Int*)o)->n.ivalue);
				break;
				case CLASS_String:
					fprintf(stderr, "async mem cid=%s(%d), refc=%d str='%s'\n", STRUCTN(o->h.bcid), (int)o->h.cid, (int)o->h.refc, (char*)((knh_String_t*)o)->str);
				break;
				case CLASS_Stmt:
					fprintf(stderr, "async mem stmt='%s', refc=%d\n", knh_stmt_tochar((SP(Stmt*)o)->stt), (int)o->h.refc);
				break;
				default:
					fprintf(stderr, "async mem cid=%s(%d), refc=%d\n", STRUCTN(o->h.bcid), (int)o->h.cid, (int)o->h.refc);
				}
			} )
			o->h.refc = 0;
#endif
			knh_Object_free(ctx, o);
		}
		t += KONOHA_PAGESIZE;
	}
	KNH_FREE(ctx, thead, SIZEOF_OBJECTPAGE);
}

/* ------------------------------------------------------------------------ */
/* [ContextCommon] */

static
void knh_Context_initCommon(Ctx *ctx, knh_Context_t *o, size_t stacksize)
{
	o->stacksize = (stacksize < 64) ? KONOHA_STACKSIZE : stacksize;
	o->stack = (knh_sfp_t*)KNH_MALLOC(ctx, sizeof(knh_sfp_t) * o->stacksize);
	o->esp = o->stack;
	{
		size_t i;
		for(i = 0; i < o->stacksize; i++) {
			KNH_INITv(o->stack[i].o, KNH_NULL);
			o->stack[i].data = 0;
		}
	}

	o->cachesize = (KNH_TCLASS_SIZE / 2) + 1;
	o->mtdCache = (knh_Method_t**)KNH_MALLOC(ctx, sizeof(knh_Method_t*) * o->cachesize);
	o->fmtCache = (knh_Method_t**)KNH_MALLOC(ctx, sizeof(knh_Method_t*) * o->cachesize);
	o->mprCache = (knh_Mapper_t**)KNH_MALLOC(ctx, sizeof(knh_Mapper_t*) * o->cachesize);
	{
		size_t i;
		knh_Method_t *mtdInit = NULL;
		knh_Method_t *fmtInit = NULL;
		knh_Mapper_t *mprInit = NULL;
		for(i = 0; i < o->cachesize; i++) {
			o->mtdCache[i] = mtdInit;
			o->fmtCache[i] = fmtInit;
			o->mprCache[i] = mprInit;
		}
	}
	if(o->bufa == NULL) {
		KNH_INITv(o->bufa, new_Bytes(ctx, KONOHA_PAGESIZE));
		KNH_INITv(o->bufw, new_BytesOutputStream(ctx, o->bufa));
	}
	KNH_INITv(o->bconvbuf, new_Bytes(ctx, KONOHA_PAGESIZE));
	KNH_INITv(o->props, new_DictMap0(ctx, 16));

	o->ctxlock = (knh_mutex_t*)KNH_MALLOC(ctx, sizeof(knh_mutex_t));
	knh_mutex_init(o->ctxlock);
	DBG2_ASSERT(ctx->sys != NULL);
	KNH_INITv(o->enc, DP(ctx->sys)->enc);
	KNH_INITv(o->in,  DP(ctx->sys)->in);
	KNH_INITv(o->out, DP(ctx->sys)->out);
	KNH_INITv(o->err, DP(ctx->sys)->err);
	KNH_INITv(o->abr, KNH_NULL);
	KNH_INITv(o->msgError, UP(TS_EMPTY));
}

/* ------------------------------------------------------------------------ */

static
void knh_Context_traverseCommon(Ctx *ctx, knh_Context_t *o, knh_ftraverse ftr)
{
	size_t i;
	for(i = 0; i < o->stacksize; i++) {
		ftr(ctx, o->stack[i].o);
	}

	ftr(ctx, UP(o->bufa));
	ftr(ctx, UP(o->bufw));
	ftr(ctx, UP(o->bconvbuf));
	ftr(ctx, UP(o->props));

	ftr(ctx, UP(o->enc));
	ftr(ctx, UP(o->in));
	ftr(ctx, UP(o->out));
	ftr(ctx, UP(o->err));
	ftr(ctx, UP(o->abr));
	ftr(ctx, UP(o->msgError));

	if(IS_SWEEP(ftr)) {
		DBG2_P("freeing stack (ctxid=%d)...", o->ctxid);
		KNH_FREE(ctx, o->stack, sizeof(knh_sfp_t) * o->stacksize);
		o->stack = NULL;
		o->esp = NULL;
		KNH_FREE(ctx, o->mtdCache, sizeof(knh_Method_t*) * o->cachesize);
		KNH_FREE(ctx, o->fmtCache, sizeof(knh_Method_t*) * o->cachesize);
		KNH_FREE(ctx, o->mprCache, sizeof(knh_Mapper_t*) * o->cachesize);
		o->mtdCache = NULL;
		o->fmtCache = NULL;
		o->mprCache = NULL;
		knh_mutex_destroy(o->ctxlock);
		KNH_FREE(ctx, o->ctxlock, sizeof(knh_mutex_t));
		o->ctxlock = NULL;
	}
}

/* ------------------------------------------------------------------------ */

static Ctx *new_Context0(Ctx *parent)
{
	knh_Context_t *ctx;
	if(parent == NULL) {
		ctx = (knh_Context_t*)malloc(sizeof(knh_Context_t));
		parent = ctx;
	}
	else {
		ctx = (knh_Context_t*)knh_malloc(parent, sizeof(knh_Context_t));
	}
	knh_bzero(ctx, sizeof(knh_Context_t));
	ctx->h.magic = KNH_OBJECT_MAGIC;
#ifdef KNH_HOBJECT_REFC
	ctx->h.refc = KNH_RCGC_INIT;
#endif
	ctx->h.flag = 	FLAG_CTX(FLAG_Context);
	ctx->h.bcid = CLASS_Context;
	ctx->h.cid  = CLASS_Context;
	ctx->h.ctxid = 0;
	ctx->h.lock  = LOCK_NOP;
	ctx->ctxid = 0;
	ctx->unusedObject = NULL;
	ctx->unusedObjectSize = 0;
	ctx->parent = parent;
	ctx->fsweep = knh_getDefaultSweepFunc();
	ctx->unusedContext = NULL;
	return (Ctx*)ctx;
}

/* ------------------------------------------------------------------------ */
/* [LOCKTABLE] */

void knh_lockID(Ctx *ctx, knh_lock_t lockid, Object *ref, char *filename, int lineno)
{
	knh_LockTable_t *t = pLockTable(lockid);
	if(t->mutex != NULL) {
		DBG_(fprintf(stderr, "LOCK[%d] count=%d at %s:%d\n", (int)lockid, (int)(t->count + 1), filename, lineno));
		knh_mutex_lock(t->mutex);
		t->count += 1;
		DBG2_({
			t->filename = filename;
			t->lineno = lineno;
		});
	}
}

/* ------------------------------------------------------------------------ */

void knh_unlockID(Ctx *ctx, knh_lock_t lockid, char *filename, int lineno)
{
	knh_LockTable_t *t = pLockTable(lockid);
	if(t->mutex != NULL) {
		DBG_(fprintf(stderr, "UNLOCK[%d] count=%d at %s:%d\n", (int)lockid, (int)t->count, filename, lineno));
		t->count -= 1;
		knh_mutex_unlock(t->mutex);
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_initSharedData(Context *ctx)
{
	size_t i;
	knh_SharedData_t *share = (knh_SharedData_t*)malloc(sizeof(knh_SharedData_t) + sizeof(knh_ctxstat_t));
	ctx->share = share;
	knh_bzero(share, sizeof(knh_SharedData_t) + sizeof(knh_ctxstat_t));
	share->threadCounter = 1;
	ctx->stat = (knh_ctxstat_t*)((share+1));

	DBG2_ASSERT(share->ObjectPageTable == NULL);
	share->ObjectPageTableMaxSize = KNH_TOBJECTPAGE_INITSIZE;
	share->ObjectPageTable =
		(knh_ObjectPageTable_t*)KNH_MALLOC(ctx,
			share->ObjectPageTableMaxSize * sizeof(knh_ObjectPageTable_t));
	knh_bzero(share->ObjectPageTable,
		share->ObjectPageTableMaxSize * sizeof(knh_ObjectPageTable_t));
	share->ObjectPageTableSize = 0;

	DBG2_ASSERT(share->LockTable == NULL);
	share->LockTable = (knh_LockTable_t*)KNH_MALLOC(ctx, SIZEOF_TLOCK);
	knh_bzero(share->LockTable, SIZEOF_TLOCK);
	for(i = 0; i < KNH_TLOCK_SIZE; i++) {
		if(LOCK_UNUSED <= i && i < KNH_TLOCK_SIZE - 1) {
			share->LockTable[i].unused = &(share->LockTable[i+1]);
		}
	}
	share->unusedLockTable = &(share->LockTable[LOCK_UNUSED]);

	DBG2_ASSERT(share->StructTable == NULL);
	share->StructTable = (knh_StructTable_t*)KNH_MALLOC(ctx, SIZEOF_TSTRUCT);
	knh_bzero((void*)share->StructTable, SIZEOF_TSTRUCT);
	share->StructTableSize = 0;

	DBG2_ASSERT(share->ClassTable == NULL);
	share->ClassTable = (knh_ClassTable_t*)KNH_MALLOC((Ctx*)ctx, SIZEOF_TCLASS);
	knh_bzero((void*)share->ClassTable, SIZEOF_TCLASS);
	for(i = 0; i < KNH_TCLASS_SIZE; i++) {
		knh_ClassTable_t *t = pClassTable(i);
		t->p1       = CLASS_unknown;   /* @deps knh_Class_isGenerics(cid)*/
		t->p2       = CLASS_unknown;
		t->keyidx   = -1;
		t->keyidx2   = -1;
	}
	share->ClassTableSize = KNH_TCLASS_SIZE;

	share->ExptTable = (knh_ExptTable_t*)KNH_MALLOC(ctx, SIZEOF_TEXPT);
	knh_bzero((void*)share->ExptTable, SIZEOF_TEXPT);
	share->ExptTableSize = 0;

	knh_loadSystemStructData(ctx);

	KNH_INITv(share->constNull, new_Null(ctx));
	KNH_INITv(share->constTrue, new_Boolean0(ctx, 1));
	KNH_INITv(share->constFalse, new_Boolean0(ctx, 0));
	{
		knh_Int_t *io = (knh_Int_t*)new_hObject(ctx, FLAG_Float, CLASS_Int, CLASS_Int);
		(io)->n.ivalue = 0;
		KNH_INITv(share->constInt0, io);
	}
	{
		knh_Float_t *fo = (knh_Float_t*)new_hObject(ctx, FLAG_Float, CLASS_Float, CLASS_Float);
		(fo)->n.fvalue = 0.0;
		KNH_INITv(share->constFloat0, fo);
	}

	KNH_ASSERT(share->tString == NULL);
	share->tString = (knh_String_t**)KNH_MALLOC(ctx, SIZEOF_TSTRING);
	knh_bzero(share->tString, SIZEOF_TSTRING);
	knh_loadSystemString(ctx);

	KNH_INITv(ctx->sys, new_System(ctx));
	KNH_INITv(ctx->bufa, new_Bytes(ctx, KONOHA_PAGESIZE));
	KNH_INITv(ctx->bufw, new_BytesOutputStream(ctx, ctx->bufa));
	knh_loadSystemData(ctx);
	KNH_INITv(share->mainns, new_NameSpace(ctx, TS_main));
}

/* ------------------------------------------------------------------------ */

static
Ctx *knh_createRootContext(size_t stacksize)
{
	Ctx *ctx = new_Context0(NULL);
	knh_initSharedData((Context*)ctx);
	knh_Context_initCommon(ctx, (Context*)ctx, stacksize);
	knh_System_initPath(ctx, ctx->sys);
	return ctx;
}

/* ------------------------------------------------------------------------ */

static
void knh_ClassStruct_toAbstractAll(Ctx *ctx, ClassStruct *cs)
{
	Array *a = cs->methods;
	if(IS_bArray(a)) {
		size_t i;
		for(i = 0; i < knh_Array_size(a); i++) {
			Method *mtd = (Method*)knh_Array_n(a, i);
			knh_Method_toAbstract(ctx, mtd);
		}
	}
	if(cs->fsize > 0) {
		size_t i;
		for(i = 0; i < cs->fsize; i++) {
			if(cs->fields[i].value != NULL) {
				KNH_FINALv(ctx, cs->fields[i].value);
				cs->fields[i].value = NULL;
			}
		}
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_traverseSharedData(Ctx *ctx, knh_SharedData_t *share, knh_ftraverse ftr)
{
	int i;
	ftr(ctx, share->constNull);
	ftr(ctx, share->constTrue);
	ftr(ctx, share->constFalse);
	ftr(ctx, UP(share->constInt0));
	ftr(ctx, UP(share->constFloat0));
	ftr(ctx, UP(ctx->sys));
	ftr(ctx, UP(share->mainns));

	for(i = 0; i < KNH_TSTRING_SIZE; i++) {
		ftr(ctx, UP(share->tString[i]));
	}

	for(i = 0; i < KNH_TLOCK_SIZE; i++) {
		if(share->LockTable[i].name != NULL) {
			ftr(ctx, UP(share->LockTable[i].name));
			if(share->LockTable[i].so != NULL) {
				ftr(ctx, share->LockTable[i].so);
			}
		}
	}

	for(i = 0; i < (int)(share->ExptTableSize); i++) {
		if(ExptTable(i).name != NULL) {
			ftr(ctx, UP(ExptTable(i).name));
		}
	}

	/* tclass */
	if(IS_SWEEP(ftr)) {
		for(i = 0; i < share->StructTableSize; i++) {
			DBG2_ASSERT(ClassTable(i).sname != NULL);
			knh_ClassStruct_toAbstractAll(ctx, ClassTable(i).cstruct);
		}
		for(i = share->ClassTableSize; i < KNH_TCLASS_SIZE; i++) {
			DBG2_ASSERT(ClassTable(i).sname != NULL);
			knh_ClassStruct_toAbstractAll(ctx, ClassTable(i).cstruct);
		}
	}

	for(i = 0; i < share->StructTableSize; i++) {
		DBG2_ASSERT(ClassTable(i).sname != NULL);
		if(ClassTable(i).class_cid != NULL)
			ftr(ctx, UP(ClassTable(i).class_cid));
		if(ClassTable(i).class_natype != NULL)
			ftr(ctx, UP(ClassTable(i).class_natype));
		ftr(ctx, UP(ClassTable(i).cmap));
		ftr(ctx, UP(ClassTable(i).cspec));
		if(ClassTable(i).constPool != NULL) {
			ftr(ctx, UP(ClassTable(i).constPool));
		}
		if(ClassTable(i).dataList != NULL) {
			ftr(ctx, UP(ClassTable(i).dataList));
		}
		if(ClassTable(i).dataMap != NULL) {
			ftr(ctx, UP(ClassTable(i).dataMap));
		}
		ftr(ctx, UP(ClassTable(i).lname));
	}

	for(i = share->ClassTableSize; i < KNH_TCLASS_SIZE; i++) {
		DBG2_ASSERT(ClassTable(i).sname != NULL);
		if(ClassTable(i).class_cid != NULL)
			ftr(ctx, UP(ClassTable(i).class_cid));
		if(ClassTable(i).class_natype != NULL)
			ftr(ctx, UP(ClassTable(i).class_natype));
		ftr(ctx, UP(ClassTable(i).cmap));
		ftr(ctx, UP(ClassTable(i).cspec));
		if(ClassTable(i).constPool != NULL) {
			ftr(ctx, UP(ClassTable(i).constPool));
		}
		if(ClassTable(i).dataList != NULL) {
			ftr(ctx, UP(ClassTable(i).dataList));
		}
		if(ClassTable(i).dataMap != NULL) {
			ftr(ctx, UP(ClassTable(i).dataMap));
		}
		ftr(ctx, UP(ClassTable(i).lname));
	}

	for(i = 0; i < share->StructTableSize; i++) {
		DBG2_ASSERT(ClassTable(i).sname != NULL);
		ftr(ctx, UP(ClassTable(i).cstruct));
		ftr(ctx, UP(ClassTable(i).sname));
	}
	for(i = share->ClassTableSize; i < KNH_TCLASS_SIZE; i++) {
		DBG2_ASSERT(ClassTable(i).sname != NULL);
		ftr(ctx, UP(ClassTable(i).cstruct));
		ftr(ctx, UP(ClassTable(i).sname));
	}

	/* System Table */
	if(IS_SWEEP(ftr)) {
		DBG2_P("*** FREEING ALL SYSTEM TABLES ***");

		KNH_FREE(ctx, (void*)share->ExptTable, SIZEOF_TEXPT);
		share->ExptTable = NULL;
		KNH_FREE(ctx, share->tString, SIZEOF_TSTRING);
		share->tString = NULL;

		((Context*)ctx)->fsweep = knh_Object_finalSweep;
		KNH_ASSERT(share->ObjectPageTable != NULL);
		for(i = 0; i < (int)(share->ObjectPageTableSize); i++) {
			knh_ObjectPageTable_free(ctx, share->ObjectPageTable[i].thead);
			share->ObjectPageTable[i].thead = NULL;
		}

		KNH_ASSERT(share->LockTable != NULL);
		KNH_FREE(ctx, share->LockTable, SIZEOF_TLOCK);
		share->unusedLockTable = NULL;

		KNH_FREE(ctx, (void*)share->ClassTable, SIZEOF_TCLASS);
		share->ClassTable = NULL;

		KNH_FREE(ctx, (void*)share->StructTable, SIZEOF_TSTRUCT);
		share->StructTable = NULL;

		KNH_FREE(ctx, share->ObjectPageTable,
				share->ObjectPageTableMaxSize * sizeof(knh_ObjectPageTable_t));
		share->ObjectPageTable = NULL;

		if(ctx->stat->usedMemorySize != 0) {
			fprintf(stderr, "memory leaks: %d bytes", (int)ctx->stat->usedMemorySize);
		}

		DBG_P("method cache hit/miss %d/%d", (int)ctx->stat->mtdCacheHit, (int)ctx->stat->mtdCacheMiss);
		DBG_P("formatter cache hit/miss %d/%d", (int)ctx->stat->fmtCacheHit, (int)ctx->stat->fmtCacheMiss);
		DBG_P("mapper cache hit/miss %d/%d", (int)ctx->stat->mprCacheHit, (int)ctx->stat->mprCacheMiss);

		knh_bzero(share, sizeof(knh_SharedData_t) + sizeof(knh_ctxstat_t));
		free(share);
	}
}


/* ------------------------------------------------------------------------ */

static
void knh_traverseUnusedContext(Ctx *ctx, knh_ftraverse ftr)
{
	if(ctx->unusedContext != NULL) {
		knh_traverseUnusedContext(ctx->unusedContext, ftr);
	}
	knh_Context_traverseCommon(ctx, (knh_Context_t*)ctx, ftr);
	if(IS_SWEEP(ftr)) {
		knh_bzero((void*)ctx, sizeof(knh_Context_t));
		knh_free(ctx, (void*)ctx, sizeof(knh_Context_t));
	}
}

/* ------------------------------------------------------------------------ */

void knh_Context_traverse(Ctx *ctx, Context *o, knh_ftraverse ftr)
{
	knh_Context_traverseCommon(ctx, (knh_Context_t*)o, ftr);
	if(o->parent == (Context*)o) {
		if(o->unusedContext != NULL) {
			knh_traverseUnusedContext(o->unusedContext, ftr);
		}
		knh_traverseSharedData(ctx, (knh_SharedData_t*)o->share, ftr);
		if(IS_SWEEP(ftr)) {
			knh_bzero((void*)o, sizeof(knh_Context_t));
			free((void*)o);
		}
	}
	else {
		if(IS_SWEEP(ftr)) {
			knh_bzero((void*)o, sizeof(knh_Context_t));
			knh_free(o, (void*)o, sizeof(knh_Context_t));
		}
	}
}

/* ------------------------------------------------------------------------ */

static
Ctx *knh_getRootContext(Ctx *ctx)
{
	if(ctx->parent == ctx) return ctx;
	return knh_getRootContext(ctx->parent);
}

/* ------------------------------------------------------------------------ */

Ctx *new_ThreadContext(Ctx *parent)
{
	Ctx *root = knh_getRootContext(parent);
	knh_Context_t *ctx = NULL;
	if(root->unusedContext != NULL) {
		KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
		ctx = (knh_Context_t*)root->unusedContext;
		if(ctx != NULL) {
			((Context*)root)->unusedContext = ctx->unusedContext;
		}
		KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
		if(ctx != NULL) {
			DBG2_P("reuseing Context: ctxid=%d", (int)ctx->ctxid);
			ctx->parent = parent;
			ctx->esp = ctx->stack;
			ctx->fsweep = knh_getDefaultSweepFunc();
			KNH_SETv(root, ctx->props, new_DictMap0(root, 16));
			KNH_SETv(root, ctx->enc, DP(root->sys)->enc);
			KNH_SETv(root, ctx->in,  DP(root->sys)->in);
			KNH_SETv(root, ctx->out, DP(root->sys)->out);
			KNH_SETv(root, ctx->err, DP(root->sys)->err);
			KNH_SETv(root, ctx->abr, KNH_NULL);
		}
	}
	if(ctx == NULL) {
		ctx = (knh_Context_t*)new_Context0(parent);
		ctx->share = parent->share;
		ctx->stat = parent->stat;
		ctx->sys  = parent->sys;
		knh_Context_initCommon(root, ctx, parent->stacksize);
		((knh_SharedData_t*)ctx->share)->contextCounter += 1;
		ctx->ctxid = (knh_ushort_t)ctx->share->contextCounter;
	}
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	((knh_SharedData_t*)ctx->share)->threadCounter += 1;
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	if(ctx->share->threadCounter == 2) {
		DBG2_P("Activating multi-threading mode!!");

	}
	return (Ctx*)ctx;
}

/* ------------------------------------------------------------------------ */

void knh_ThreadContext_dispose(Ctx *ctx)
{
	KNH_ASSERT(ctx->parent != ctx);
	Ctx *root = knh_getRootContext(ctx);
	knh_mutex_lock((((Context*)ctx)->ctxlock));  // checking using or not
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	((Context*)ctx)->unusedContext = root->unusedContext;
	((Context*)root)->unusedContext = ctx;
	((knh_SharedData_t*)ctx->share)->threadCounter -= 1;
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	knh_mutex_unlock((((Context*)ctx)->ctxlock));
}

/* ======================================================================== */
/* [konohaapi] */

/* ------------------------------------------------------------------------ */

static int isFirstVirtualMachine = 1;

/* ------------------------------------------------------------------------ */

KNHAPI(konoha_t) konoha_open(size_t stacksize)
{
	konoha_t k = {KONOHA_MAGIC};
	if(isFirstVirtualMachine) {
		isFirstVirtualMachine = 0;
		konoha_init();
	}
	if(stacksize < KONOHA_STACKSIZE) stacksize = KONOHA_STACKSIZE;
	k.ctx = knh_createRootContext(stacksize);
	return k;
}

/* ------------------------------------------------------------------------ */

void knh_traverseAll(Ctx* ctx, knh_ftraverse ftr)
{
	knh_Context_traverse(ctx, (Context*)ctx, ftr);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_close(konoha_t konoha)
{
	KONOHA_CHECK_(konoha);
	if(konoha.ctx->share->threadCounter > 1) {
		fprintf(stderr, "Many threads are still running... Found %d threads", (int)konoha.ctx->share->threadCounter);
		return;
	}
	knh_Context_traverse(konoha.ctx, (Context*)konoha.ctx, konoha.ctx->fsweep);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
