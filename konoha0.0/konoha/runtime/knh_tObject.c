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

#define KNH_TOBJECT_C  1

#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

#define KNH_STATMODE0   -1  /* @property */

/* ======================================================================== */
/* [malloc] */

static size_t knh_statUsedMemorySize = 0;  /* @stat */

/* ------------------------------------------------------------------------ */

KNHAPI(size_t) knh_stat_usedMemorySize(void)
{
   return knh_statUsedMemorySize;
}

/* ------------------------------------------------------------------------ */

INLINE void *knh_malloc(Ctx *ctx, size_t size)
{
	void *block = malloc(size);
	if (block == NULL) {
		KNH_EXIT("OutOfMemory!!: %d bytes used", (int)knh_statUsedMemorySize);
		//KNH_THROWs(ctx, "OutOfMemory!!");
	}
#ifdef KNH_STATMODE0
	knh_statUsedMemorySize += size;
#endif
	return block;
}

/* ------------------------------------------------------------------------ */

INLINE void knh_free(void *block, size_t size)
{
#ifdef KNH_STATMODE0
	knh_statUsedMemorySize -= size;
#endif
	free(block);
}

/* ------------------------------------------------------------------------ */

void *DBG2_malloc(Ctx *ctx, size_t size)
{
	size_t *block = (size_t*)malloc(size + sizeof(size_t));
	if (block == NULL) {
		KNH_EXIT("OutOfMemory!!: %d bytes used", (int)knh_statUsedMemorySize);
		//KNH_THROWs(ctx, "OutOfMemory!!");
	}
#ifdef KNH_STATMODE0
	knh_statUsedMemorySize += size;
#endif
	block[0] = size;
	void *p = (void*)(block + 1);
//	knh_bzero(p, size);
	return p;
}

/* ------------------------------------------------------------------------ */

void DBG2_free(void *p, size_t size)
{
	size_t *block = ((size_t*)p) - 1;
#ifdef KNH_STATMODE0
	knh_statUsedMemorySize -= size;
#endif
	if(size != block[0]) {
		DBG2_P("ptr = %p, block.size = %d, free.size=%d", p, (int)block[0], (int)size);
		KNH_ASSERT(size == block[0]);
	}
	free(block);
}

/* ======================================================================== */
/* [tObject] */

#ifndef KNH_TOBJECTLIST_SIZE
#define KNH_TOBJECTLIST_SIZE    1024   /* @property */
#endif

#ifndef KNH_TOBJECT_SIZE
#define KNH_TOBJECT_SIZE        4096   /* @property */
#endif

static knh_Object_t **knh_tObjectList = NULL;
static size_t knh_tObjectListSize = 0;
static knh_Object_t *knh_UnusedObject = NULL;
static size_t knh_UnusedObjectSize = 0;

#define SIZEOF_TOBJECTLIST  (sizeof(knh_Object_t*) * KNH_TOBJECTLIST_SIZE)
#define SIZEOF_TOBJECT      (sizeof(knh_Object_t) * KNH_TOBJECT_SIZE)

/* ------------------------------------------------------------------------ */

#define KNH_SLOCK()
#define KNH_UNSLOCK()

/* ------------------------------------------------------------------------ */

static
knh_Object_t *new_UnusedObject(Ctx *ctx)
{
	knh_Object_t *t;
	int i;
	synchronized {
		KNH_SLOCK();
		if(!(knh_tObjectListSize < KNH_TOBJECTLIST_SIZE)) {
			KNH_EXIT("Enlarge KNH_TOBJECTLIST_SIZE %d", KNH_TOBJECTLIST_SIZE);
			return NULL;
		}
		knh_tObjectListSize++;
		KNH_UNSLOCK();
	}
	t = (knh_Object_t*)KNH_MALLOC(ctx, SIZEOF_TOBJECT);
	for(i = 0; i < KNH_TOBJECT_SIZE - 1; i++) {
		t[i].h.magic = 0;
		t[i].ref = &(t[i+1]);
	}
	t[KNH_TOBJECT_SIZE - 1].ref = NULL;
	knh_tObjectList[knh_tObjectListSize-1] = t;
	return t;
}

/* ------------------------------------------------------------------------ */

static
void knh_tObject_free(knh_Object_t *t)
{
	int i;
	for(i = 0; i < KNH_TOBJECT_SIZE; i++) {
		if(t[i].h.magic == 0) continue;
		DBG_(
		fprintf(stderr, "Memory Leak cid = %d,%s, refc=%d\n", (int)t[i].h.cid, STRUCTN(t[i].h.bcid), (int)t[i].h.refc);
		{
			Object *o = &t[i];
			switch(o->h.bcid) {
			case CLASS_Class:
				fprintf(stderr, "\t%s cid=%d\n", STRUCTN(o->h.bcid), (int)((knh_Class_t*)o)->cid);
			break;
			case CLASS_String:
				fprintf(stderr, "\t%s str='%s'\n", STRUCTN(o->h.bcid), (char*)((knh_String_t*)o)->str);
			break;
			}
		} )
	}
	KNH_FREE(t, SIZEOF_TOBJECT);
	t = NULL;
}

/* ------------------------------------------------------------------------ */
/* [PObject] */

#ifdef KNH_STATMODE1
static size_t knh_statUsedObjectSize = 0;  /* @stat */
#endif

/* ------------------------------------------------------------------------ */

knh_Object_t *new_PObject__NNctx(Ctx *ctx, knh_flag_t flag, knh_class_t bcid, knh_class_t cid)
{
	KNH_ASSERT(ctx != NULL);
	if(ctx->unusedObject == NULL) {
		KNH_ASSERT(ctx->unusedObjectSize == 0);
		((knh_Context_t*)ctx)->unusedObject = new_UnusedObject(ctx);
		if(ctx->unusedObject == NULL) {
			KNH_EXIT("Enlarge KNH_TOBJECTLIST_SIZE %d x %d",
					KNH_TOBJECTLIST_SIZE, KNH_TOBJECT_SIZE);
			return NULL;
		}
		else {
			((knh_Context_t*)ctx)->unusedObjectSize += KNH_TOBJECT_SIZE;
		}
	}
	{
		knh_Object_t *o = ctx->unusedObject;
		((knh_Context_t*)ctx)->unusedObject = (knh_Object_t*)o->ref;
		((knh_Context_t*)ctx)->unusedObjectSize -= 1;

#ifdef KNH_STATMODE1
		knh_statUsedObjectSize++;
#endif
		o->h.magic = KNH_OBJECT_MAGIC;
		o->h.refc = 0;
		o->h.flag = flag;
		o->h.bcid = bcid;
		o->h.cid  = cid;
		return o;
	}
}

/* ------------------------------------------------------------------------ */

knh_Object_t *new_PObject0(Ctx *ctx, knh_flag_t flag, knh_class_t bcid, knh_class_t cid)
{
	if(ctx == NULL) {
		if(knh_UnusedObject == NULL) {
			KNH_ASSERT(knh_UnusedObjectSize == 0);
			knh_UnusedObject = new_UnusedObject(NULL);
			if(knh_UnusedObject == NULL) {
				KNH_EXIT("Enlarge KNH_TOBJECTLIST_SIZE %d x %d",
						KNH_TOBJECTLIST_SIZE, KNH_TOBJECT_SIZE);
				return NULL;
			}
			else {
				knh_UnusedObjectSize += KNH_TOBJECT_SIZE;
			}
		}
		{
			knh_Object_t *o = knh_UnusedObject;
			knh_UnusedObject = (knh_Object_t*)o->ref;
			knh_UnusedObjectSize -= 1;
	#ifdef KNH_STATMODE1
			knh_statUsedObjectSize++;
	#endif
			o->h.magic = KNH_OBJECT_MAGIC;
			o->h.refc = 0;
			o->h.flag = flag;
			o->h.bcid = bcid;
			o->h.cid  = cid;
			o->ref = NULL;
			return o;
		}
	}
	else {
		DEBUG_ASSERT_cid(cid);
		KNH_ASSERT(knh_tClass[cid].bcid == bcid);
		return new_PObject__NNctx(ctx, flag, bcid, cid);
	}
}

/* ------------------------------------------------------------------------ */

#define _new_Object_malloc(ctx, flag, cid, size)   new_ObjectX_malloc(ctx, flag, cid, cid, size)

knh_Object_t *new_ObjectX_malloc(Ctx *ctx, knh_flag_t flag, knh_class_t bcid, knh_class_t cid, size_t size)
{
	knh_Object_t *o;
	KNH_ASSERT(bcid < KNH_TSTRUCT_SIZE);
	if(ctx == NULL) {
		if(knh_UnusedObject == NULL) {
			KNH_ASSERT(knh_UnusedObjectSize == 0);
			knh_UnusedObject = new_UnusedObject(NULL);
			if(knh_UnusedObject == NULL) {
				KNH_EXIT("Enlarge KNH_TOBJECTLIST_SIZE %d x %d",
						KNH_TOBJECTLIST_SIZE, KNH_TOBJECT_SIZE);
				return NULL;
			}
			else {
				knh_UnusedObjectSize += KNH_TOBJECT_SIZE;
			}
		}
		o = knh_UnusedObject;
		knh_UnusedObject = (knh_Object_t*)o->ref;
		knh_UnusedObjectSize -= 1;
		o->h.bcid = bcid;
	}
	else {
		if(ctx->unusedObject == NULL) {
			KNH_ASSERT(ctx->unusedObjectSize == 0);
			((knh_Context_t*)ctx)->unusedObject = new_UnusedObject(ctx);
			if(ctx->unusedObject == NULL) {
				KNH_EXIT("Enlarge KNH_TOBJECTLIST_SIZE %d x %d",
						KNH_TOBJECTLIST_SIZE, KNH_TOBJECT_SIZE);
				return NULL;
			}
			else {
				((knh_Context_t*)ctx)->unusedObjectSize += KNH_TOBJECT_SIZE;
			}
		}
		o = ctx->unusedObject;
		((knh_Context_t*)ctx)->unusedObject = (knh_Object_t*)o->ref;
		((knh_Context_t*)ctx)->unusedObjectSize -= 1;
		DEBUG_ASSERT_cid(cid);
		KNH_ASSERT(knh_tClass[cid].bcid == bcid);
		KNH_ASSERT(knh_tClass[cid].size == size);
		o->h.bcid = knh_tClass[cid].bcid;
	}

#ifdef KNH_STATMODE1
		knh_statUsedObjectSize++;
#endif
	o->h.magic = KNH_OBJECT_MAGIC;
	o->h.refc = 0;
	o->h.flag = flag;
	o->h.cid  = cid;
	if(size > 0) {
		o->ref = KNH_MALLOC(ctx, size);
	}
	else {
		o->ref = NULL;
	}
	return o;
}

/* ------------------------------------------------------------------------ */

Object *new_Object(Ctx *ctx, knh_flag_t flag, knh_class_t cid)
{
	KNH_ASSERT(ctx != NULL);
	if(ctx->unusedObject == NULL) {
		KNH_ASSERT(ctx->unusedObjectSize == 0);
		((knh_Context_t*)ctx)->unusedObject = new_UnusedObject(ctx);
		if(ctx->unusedObject == NULL) {
			KNH_EXIT("Enlarge KNH_TOBJECTLIST_SIZE %d x %d",
					KNH_TOBJECTLIST_SIZE, KNH_TOBJECT_SIZE);
			return NULL;
		}
		else {
			((knh_Context_t*)ctx)->unusedObjectSize += KNH_TOBJECT_SIZE;
		}
	}
	{
		knh_Object_t *o = ctx->unusedObject;
		((knh_Context_t*)ctx)->unusedObject = (knh_Object_t*)o->ref;
		((knh_Context_t*)ctx)->unusedObjectSize -= 1;
		DEBUG_ASSERT_cid(cid);
		o->h.bcid = knh_tClass[cid].bcid;

#ifdef KNH_STATMODE1
	knh_statUsedObjectSize++;
#endif

		o->h.magic = KNH_OBJECT_MAGIC;
		o->h.refc = 0;
		o->h.flag = (knh_tClass[cid].oflag | flag);
		o->h.cid  = cid;

		if(knh_tClass[cid].size > 0) {
			Object **v = (Object**)KNH_MALLOC(ctx, knh_tClass[cid].size);
			//knh_class_t cid = o->h.cid;
			knh_struct_t sid;
			size_t offset;
			while((offset = knh_tClass[cid].offset) != 0) {
				sid = knh_tClass[cid].sid;
				if(STRUCT_ISFIELD(sid)) {
					knh_ClassStruct_finit(ctx, knh_tClass[cid].cstruct, o->h.cid, v + offset);
				}
				else {
					DEBUG_ASSERT_sid(sid);
					knh_tStruct[sid].finit(ctx, (void*)&(v[offset]), 0, NULL);
				}
				cid = knh_tClass[cid].supcid;
				DEBUG_ASSERT_cid(cid);
			}
			sid = knh_tClass[cid].sid;
			if(STRUCT_ISFIELD(sid)) {
				knh_ClassStruct_finit(ctx, knh_tClass[cid].cstruct, o->h.cid, v + offset);
			}
			else {
				knh_tStruct[sid].finit(ctx, (void*)&(v[offset]), 0, NULL);
			}
			o->ref = v;
		}
		else {
			o->ref = NULL;
		}
		return o;
	}
}


/* ------------------------------------------------------------------------ */

void knh_Object_RCsweep(Ctx *ctx, Object *o)
{
	knh_Object_RCdec(o);
	if(knh_Object_isRC0(o)) {
		knh_Object_free(ctx, o);
	}
}

#define _IS_SWEEP(f)   (f == knh_Object_RCsweep)

/* ------------------------------------------------------------------------ */

KNHAPI(f_traverse) konoha_sweep()
{
	return knh_Object_RCsweep;
}

/* ------------------------------------------------------------------------ */

KNHAPI(int) konoha_issweep(f_traverse ftr)
{
	return _IS_SWEEP(ftr);
}

/* ------------------------------------------------------------------------ */

static INLINE
void knh_fields_traverse(Ctx *ctx, Object **a, size_t capacity, f_traverse ftr)
{
	size_t i = 0;
	for(i = 0; i < capacity; i++) {
		ftr(ctx, a[i]);
	}
}

/* ------------------------------------------------------------------------ */

void knh_Object_free(Ctx *ctx, knh_Object_t *o)
{
#ifdef KONOHA_WITH_RCGC
	KNH_ASSERT(o->h.refc == 0);
#endif
	//DBG2_P("sid=%d,%s", o->h.bcid, STRUCTN(o->h.bcid));
	if(o->h.magic == 0) {
		return;
	}
	else {
		o->h.magic = 0;
	}
//	DBG2_(
//		if(o == knh_tObjectList[0]) {
//			fprintf(stderr, "*********************************************************\n");
//			fprintf(stderr, "                   FREEING KNH_NULL..\n");
//			fprintf(stderr, "*********************************************************\n");
//		}
//	)

	switch(o->h.bcid) {
	case CLASS_Object:
		{
			size_t i, bsize = knh_tClass[o->h.cid].bsize;
			Object **v = (Object**)o->ref;
			//DBG2_P("cid=%d,%s, bsize=%d", o->h.cid, CLASSN(o->h.cid), bsize);
			if(bsize > 0) {
				for(i = 0; i < bsize; i++) {
					knh_Object_RCsweep(ctx, v[i]);
				}
				KNH_FREE(o->ref, bsize * sizeof(Object*));
			}
			o->ref = NULL;
		}
		break;

	case CLASS_Nue :
		{
			knh_Nue_t *v = (knh_Nue_t*)o;
			if(knh_Nue_isGCHook(v)) {
				o->h.magic = KNH_OBJECT_MAGIC;
				knh_Object_RCinc(o);
				knh_throwException(ctx, new_Exception__Nue(ctx, v));
			}
			if(v->orign != NULL) {
				KNH_ASSERT(IS_bString(v->orign));
				knh_Object_RCsweep(ctx, UP(v->orign));
				v->orign = NULL;
			}
		}
		break;

	case CLASS_Boolean :  case CLASS_Class :
	case CLASS_Int :   case CLASS_IntX :
	case CLASS_Int64 : case CLASS_Int64X :
	case CLASS_Float : case CLASS_FloatX :
		break;

	case CLASS_String : case CLASS_StringX :
		{
			knh_String_t *s = (knh_String_t*)o;
			if(s->orign != NULL) {
				knh_Object_RCsweep(ctx, UP(s->orign));
			}
			else if(!knh_String_isTextSgm(o)) {
				KNH_FREE(s->str, KNH_SIZE(s->size + 1));
				s->str = NULL;
			}
		}
		break;

	case CLASS_Bytes :
		{
			knh_Bytes_t *b = (knh_Bytes_t*)o;
			knh_barray_free(b->buf);
			b->buf = NULL;
		}
		break;

	case CLASS_Range:
	case CLASS_Tuple2:
		{
			knh_Tuple2_t *t = (knh_Tuple2_t*)o;
			knh_Object_RCsweep(ctx, t->first);
			knh_Object_RCsweep(ctx, t->second);
		}
		break;

	case CLASS_Array :
		{
			knh_Array_t *a = (knh_Array_t*)o;
			knh_oarray_free(ctx, a->list);
		}
		break;

	case CLASS_DictMap2 :
	case CLASS_DictSet2 :
		{
			knh_DictMap2_t *d = (knh_DictMap2_t*)o;
			knh_array_traverse(ctx, d->list, knh_Object_RCsweep);
		}
		break;

	case CLASS_Context:
		{
			knh_Context_traverse(ctx, (Context*)o, knh_Object_RCsweep);
			return ;
		}

	default :
		{
			knh_class_t cid = o->h.cid;
			DBG_(size_t size = 0;)
			knh_struct_t sid;
			size_t offset;
			while((offset = knh_tClass[cid].offset) != 0) {
				sid = knh_tClass[cid].sid;
				if(STRUCT_ISFIELD(sid)) {
					knh_fields_traverse(ctx, &(KNH_FIELDn(o->ref, offset)), STRUCT_FIELDSIZE(sid), knh_Object_RCsweep);
					DBG_(size += STRUCT_FIELDSIZE(sid);)
				}
				else {
					DEBUG_ASSERT_sid(sid);
					knh_tStruct[sid].ftraverse(ctx, (void*)(&KNH_FIELDn(o->ref, offset)), knh_Object_RCsweep);
					DBG_(size += knh_tStruct[sid].size;)
				}
				cid = knh_tClass[cid].supcid;
				DEBUG_ASSERT_cid(cid);
			}
			sid = knh_tClass[cid].sid;
			if(STRUCT_ISFIELD(sid)) {
				knh_fields_traverse(ctx, (knh_Object_t**)o->ref, STRUCT_FIELDSIZE(sid), knh_Object_RCsweep);
				DBG_(size += (STRUCT_FIELDSIZE(sid) * sizeof(Object*));)
			}
			else {
				DEBUG_ASSERT_sid(sid);
				knh_tStruct[sid].ftraverse(ctx, (void*)o->ref, knh_Object_RCsweep);
				DBG_(size += knh_tStruct[sid].size;)
			}
#ifdef KNH_FLAG_OF_METADATA
			if((o->h.flag & KNH_FLAG_OF_METADATA) == KNH_FLAG_OF_METADATA && ctx != NULL) {
				TODO();
//				knh_metadata_clear(ctx, o);
			}
#endif
//			if(size != knh_tClass[o->h.cid].size) {
//				DBG2_P("sid=%d,%s size=%d,%d", o->h.bcid, STRUCTN(o->h.bcid), size, knh_tClass[o->h.cid].size);
//			}
			DBG_(KNH_ASSERT(size == knh_tClass[o->h.cid].size);)
			KNH_FREE(o->ref, knh_tClass[o->h.cid].size);
			o->ref = NULL;
		}
	}

	/* FREE */
	if(ctx == NULL) {
		//o->h.magic = 0;
		o->ref = knh_UnusedObject;
		knh_UnusedObject = o;
		knh_UnusedObjectSize += 1;
	}
	else {
		//o->h.magic = 0;
		o->ref = ctx->unusedObject;
		((knh_Context_t*)ctx)->unusedObject = o;
		((knh_Context_t*)ctx)->unusedObjectSize += 1;
	}
#ifdef KNH_STATMODE1
	knh_statUsedObjectSize--;
#endif

}

/* ------------------------------------------------------------------------ */

void knh_Object_traverse(Ctx *ctx, knh_Object_t *o, f_traverse ftr)
{
	if(IS_SWEEP(ftr)) {
		knh_Object_free(ctx, o);
		return;
	}

	switch(o->h.bcid) {
	case CLASS_Object:
		{
			size_t i, bsize = knh_tClass[o->h.cid].bsize;
			Object **v = (Object**)o->ref;
			for(i = 0; i < bsize; i++) {
				ftr(ctx, v[i]);
			}
		}
		break;

	case CLASS_Nue :
		{
			knh_Nue_t *v = (knh_Nue_t*)o;
			if(v->orign != NULL) {
				KNH_ASSERT(IS_bString(v->orign));
				ftr(ctx, UP(v->orign));
			}
		}
		break;

	case CLASS_Boolean :  case CLASS_Class :
	case CLASS_Int :   case CLASS_IntX :
	case CLASS_Int64 : case CLASS_Int64X :
	case CLASS_Float : case CLASS_FloatX :
		break;

	case CLASS_String : case CLASS_StringX :
		{
			knh_String_t *s = (knh_String_t*)o;
			if(s->orign != NULL) {
				ftr(ctx, UP(s->orign));
			}
		}
		break;

	case CLASS_Bytes :
		break;

	case CLASS_Range:
	case CLASS_Tuple2:
		{
			knh_Tuple2_t *t = (knh_Tuple2_t*)o;
			ftr(ctx, t->first);
			ftr(ctx, t->second);
		}
		break;

	case CLASS_Array :
		{
			knh_Array_t *a = (knh_Array_t*)o;
			knh_oarray_traverse(ctx, a->list, ftr);
		}
		break;

	case CLASS_DictMap2 : case CLASS_DictSet2 :
		{
			knh_DictMap2_t *a = (knh_DictMap2_t*)o;
			knh_array_traverse(ctx, a->list, ftr);
		}
		break;

	case CLASS_Context:
		{
			knh_Context_traverse(ctx, (Context*)o, ftr);
			return ;
		}

	default :
		{
			knh_class_t cid = o->h.cid;
			knh_struct_t sid;
			size_t offset;
			while((offset = knh_tClass[cid].offset) != 0) {
				sid = knh_tClass[cid].sid;
				if(STRUCT_ISFIELD(sid)) {
					knh_fields_traverse(ctx, &(KNH_FIELDn(o->ref, offset)), STRUCT_FIELDSIZE(sid), ftr);
				}
				else {
					DEBUG_ASSERT_sid(sid);
					knh_tStruct[sid].ftraverse(ctx, (void*)(&KNH_FIELDn(o->ref, offset)), ftr);
				}
				cid = knh_tClass[cid].supcid;
				DEBUG_ASSERT_cid(cid);
			}
			sid = knh_tClass[cid].sid;
			if(STRUCT_ISFIELD(sid)) {
				knh_fields_traverse(ctx, (knh_Object_t**)o->ref, STRUCT_FIELDSIZE(sid), ftr);
			}
			else {
				DEBUG_ASSERT_sid(sid);
				knh_tStruct[sid].ftraverse(ctx, (void*)o->ref, ftr);
			}
		}
	}
}

/* ======================================================================== */
/* [INITVALUE] */

#define KNH_NULL knh_constNull
void                         *knh_constNull  = NULL;
/* @global */ void           *knh_constVoid  = NULL;
/* @global */ knh_Object_t   *knh_constTrue  = NULL;
/* @global */ knh_Object_t   *knh_constFalse = NULL;

/* @global */ knh_System_t   *knh_rootSystem = NULL;
#define _knh_rootNameSpace    DP(knh_rootSystem)->ns
#define _knh_systemEncoding    DP(knh_rootSystem)->enc
#define _knh_systemStdIn       DP(knh_rootSystem)->in
#define _knh_systemStdOut      DP(knh_rootSystem)->out
#define _knh_systemStdErr      DP(knh_rootSystem)->err

#define SIZEOF_TINT (sizeof(knh_Object_t*) * (KNH_TINT_MAX - KNH_TINT_MIN + 1))
/* @global */ knh_Int_t **knh_tInt = NULL;

#define SIZEOF_TSTRING (sizeof(knh_Object_t*) * KNH_TSTRING_SIZE)
/* @global */ knh_String_t **knh_tString = NULL;

void knh_tString_init0(void);

//#define SIZEOF_TMETHODFIELD (sizeof(knh_Object_t*) * KNH_TMETHODFIELD_SIZE)
///* @global */ knh_MethodField_t **knh_tMethodField = NULL;

#define _knh_tMethodField_add(ctx, mf)       knh_Array_add(ctx, DP(knh_rootSystem)->tMethodFields, UP(mf))
#define _knh_tMethodField(n)                 (MethodField*)knh_Array_n(DP(knh_rootSystem)->tMethodFields, n)
#define _knh_tMethodField_size               knh_Array_size(DP(knh_rootSystem)->tMethodFields)

///* ------------------------------------------------------------------------ */
//
//Any* ALT_NULL(void)
//{
//	return knh_constNull;
//}

/* ------------------------------------------------------------------------ */

Object *new_Nue__T(Ctx *ctx, char *text)
{
	knh_Nue_t *o = (knh_Nue_t*)new_PObject0(ctx, FLAG_Nue, CLASS_Nue, CLASS_Nue);
	o->str = (knh_uchar_t*)text;
	o->size = knh_strlen(text);
	o->orign = NULL;
	return (Object*)o;
}

/* ------------------------------------------------------------------------ */

static
knh_Object_t *new_Boolean0(knh_bool_t tf)
{
	knh_Boolean_t *o = (knh_Boolean_t*)new_PObject0(NULL, FLAG_Boolean, CLASS_Boolean, CLASS_Boolean);
	o->value = tf;
	return (knh_Object_t*)o;
}

/* ------------------------------------------------------------------------ */

static
knh_Int_t *new_Int0_(knh_int_t n)
{
	knh_Int_t *o = (knh_Int_t*)new_PObject0(NULL, FLAG_Int, CLASS_Int, CLASS_Int);
	o->value = n;
	return o;
}

/* ------------------------------------------------------------------------ */

#define _new_Int(ctx, n)      new_Int__fast(ctx, CLASS_Int, (n))

KNHAPI(Int*) new_Int__fast(Ctx *ctx, knh_class_t cid, knh_int_t value)
{
	KNH_ASSERT(ctx != NULL);
	if(cid == CLASS_Int && KNH_TINT_MIN <= value && value <= KNH_TINT_MAX) {
		return knh_tInt[value - KNH_TINT_MIN];
	}

	if(ctx->unusedObject == NULL) {
		KNH_ASSERT(ctx->unusedObjectSize == 0);
		((knh_Context_t*)ctx)->unusedObject = new_UnusedObject(ctx);
		if(ctx->unusedObject == NULL) {
			KNH_EXIT("Enlarge KNH_TOBJECTLIST_SIZE %d x %d",
					KNH_TOBJECTLIST_SIZE, KNH_TOBJECT_SIZE);
			return NULL;
		}
		else {
			((knh_Context_t*)ctx)->unusedObjectSize += KNH_TOBJECT_SIZE;
		}
	}
	{
		knh_Object_t *o = ctx->unusedObject;
		((knh_Context_t*)ctx)->unusedObject = (knh_Object_t*)o->ref;
		((knh_Context_t*)ctx)->unusedObjectSize -= 1;

#ifdef KNH_STATMODE1
		knh_statUsedObjectSize++;
#endif
		o->h.magic = KNH_OBJECT_MAGIC;
		o->h.refc = 0;
		o->h.flag = FLAG_Int;
		o->h.bcid = CLASS_Int;
		o->h.cid  = cid;
		knh_Int_t *v = (knh_Int_t*)o;
		v->value = value;
		return v;
	}
}

/* ------------------------------------------------------------------------ */

#define _new_Int64(ctx, n)      new_Int64__fast(ctx, CLASS_Int64, (n))

KNHAPI(Int64*) new_Int64__fast(Ctx *ctx, knh_class_t cid, knh_int64_t value)
{
	KNH_ASSERT(ctx != NULL);
	if(ctx->unusedObject == NULL) {
		KNH_ASSERT(ctx->unusedObjectSize == 0);
		((knh_Context_t*)ctx)->unusedObject = new_UnusedObject(ctx);
		if(ctx->unusedObject == NULL) {
			KNH_EXIT("Enlarge KNH_TOBJECTLIST_SIZE %d x %d",
					KNH_TOBJECTLIST_SIZE, KNH_TOBJECT_SIZE);
			return NULL;
		}
		else {
			((knh_Context_t*)ctx)->unusedObjectSize += KNH_TOBJECT_SIZE;
		}
	}
	{
		knh_Object_t *o = ctx->unusedObject;
		((knh_Context_t*)ctx)->unusedObject = (knh_Object_t*)o->ref;
		((knh_Context_t*)ctx)->unusedObjectSize -= 1;

#ifdef KNH_STATMODE1
		knh_statUsedObjectSize++;
#endif
		o->h.magic = KNH_OBJECT_MAGIC;
		o->h.refc = 0;
		o->h.flag = FLAG_Int64;
		o->h.bcid = CLASS_Int64;
		o->h.cid  = cid;
		knh_Int64_t *v = (knh_Int64_t*)o;
		v->value = value;
		v->ivalue = (knh_int_t)value;
		return v;
	}
}

/* ------------------------------------------------------------------------ */

#define _new_Float(ctx, n)      new_Float__fast(ctx, CLASS_Float, (n))

KNHAPI(Float*) new_Float__fast(Ctx *ctx, knh_class_t cid, knh_float_t value)
{
	KNH_ASSERT(ctx != NULL);
	if(ctx->unusedObject == NULL) {
		KNH_ASSERT(ctx->unusedObjectSize == 0);
		((knh_Context_t*)ctx)->unusedObject = new_UnusedObject(ctx);
		if(ctx->unusedObject == NULL) {
			KNH_EXIT("Enlarge KNH_TOBJECTLIST_SIZE %d x %d",
					KNH_TOBJECTLIST_SIZE, KNH_TOBJECT_SIZE);
			return NULL;
		}
		else {
			((knh_Context_t*)ctx)->unusedObjectSize += KNH_TOBJECT_SIZE;
		}
	}
	{
		knh_Object_t *o = ctx->unusedObject;
		((knh_Context_t*)ctx)->unusedObject = (knh_Object_t*)o->ref;
		((knh_Context_t*)ctx)->unusedObjectSize -= 1;

#ifdef KNH_STATMODE1
		knh_statUsedObjectSize++;
#endif
		o->h.magic = KNH_OBJECT_MAGIC;
		o->h.refc = 0;
		o->h.flag = FLAG_Float;
		o->h.bcid = CLASS_Float;
		o->h.cid  = cid;
		knh_Float_t *v = (knh_Float_t*)o;
		v->value = value;
		v->ivalue = (knh_int_t)value;
		return v;
	}
}

/* ------------------------------------------------------------------------ */

knh_String_t *new_StringX__T(Ctx *ctx, knh_class_t cid, char *text)
{
	knh_String_t *o = (knh_String_t*)new_PObject0(ctx, FLAG_String, CLASS_String, cid);
	o->str = (knh_uchar_t*)text;
	o->size = knh_strlen(text);
	o->orign = NULL;
	knh_String_setTextSgm(o, 1);
	knh_String_checkASCII(o);
	return o;
}

#define _new_String__T(ctx, text)    new_StringX__T(ctx, CLASS_String, text)


/* ------------------------------------------------------------------------ */

static
knh_System_t *new_System0(void)
{
	char buf[FILENAME_BUFSIZ];
	knh_System_t *o = (knh_System_t*)new_ObjectX_malloc(NULL, FLAG_System, CLASS_Object, CLASS_System, sizeof(knh_System_struct));
	KNH_INITv(DP(o)->ns,    new_NameSpace(NULL, (NameSpace*)KNH_NULL, TS_EMPTY));
	KNH_INITv(DP(o)->enc,   new_String__T(NULL, konoha_encoding()));
	KNH_INITv(DP(o)->in,    new_InputStream__FILE(NULL, stdin));
	KNH_INITv(DP(o)->out,   new_OutputStream__FILE(NULL, stdout));
	KNH_INITv(DP(o)->err,   new_OutputStream__FILE(NULL, stderr));
	knh_InputStream_setEncoding(NULL, DP(o)->in,   DP(o)->enc);
	knh_OutputStream_setEncoding(NULL, DP(o)->out, DP(o)->enc);
	knh_OutputStream_setEncoding(NULL, DP(o)->err, DP(o)->enc);

	KNH_INITv(DP(o)->props, new_DictMap(NULL, 64));

	KNH_INITv(DP(o)->tConstDictMap, new_DictMap(NULL, 256));

	KNH_INITv(DP(o)->tfieldnDictIdx, new_DictIdx(NULL, KNH_TFIELDN_SIZE * 2, 0));
	KNH_INITv(DP(o)->tfileidDictIdx, new_DictIdx(NULL, 32, 0));
	knh_DictIdx_add__fast(NULL, DP(o)->tfileidDictIdx, new_String__T(NULL, "(unknown)"));
	KNH_INITv(DP(o)->tMethodFields, new_Array(NULL, CLASS_Any, KNH_TMETHODFIELD_SIZE * 2));

	KNH_INITv(DP(o)->homeDir, new_String0(NULL, B(knh_format_homepath(buf,sizeof(buf))), NULL));
	KNH_INITv(DP(o)->sysnsDictMap, new_DictMap(NULL, 16));
	KNH_INITv(DP(o)->funcDictSet, new_DictSet(NULL, 16));
	KNH_INITv(DP(o)->drvapiDictSet, new_DictSet(NULL, 32));
	KNH_INITv(DP(o)->makespecDictSet, new_DictSet(NULL, 32));

	knh_DictMap_set(NULL, DP(o)->props, new_String__T(NULL, "konoha.version"), UP(new_String__T(NULL, KONOHA_VERSION)));
	knh_DictMap_set(NULL, DP(o)->props, new_String__T(NULL, "konoha.encoding"), UP(DP(o)->enc));
	knh_DictMap_set(NULL, DP(o)->props, new_String__T(NULL, "konoha.dir.home"), UP(DP(o)->homeDir));
	knh_DictMap_set(NULL, DP(o)->props, new_String__T(NULL, "konoha.dir.package"),
			UP(new_String0(NULL, B(knh_format_packagedir(buf, sizeof(buf),knh_String_tochar(DP(o)->homeDir))), NULL)));
	knh_DictMap_set(NULL, DP(o)->props, new_String__T(NULL, "konoha.lang"),
			UP(new_String0(NULL, B(knh_format_lang(buf, sizeof(buf))), NULL)));
	knh_Compiler_setLang(buf);
	return o;
}

/* ======================================================================== */
/* [STATICOBJ] */

#ifndef KNH_TSTATICOBJ_SIZE
#define KNH_TSTATICOBJ_SIZE   512 /* @property */
#endif

static knh_Object_t ***knh_tStaticVariable = NULL;
static size_t knh_tStaticVariableSize = 0;

#define SIZEOF_TSTATICOBJ  (KNH_TSTATICOBJ_SIZE * sizeof(knh_Object_t**))

/* ------------------------------------------------------------------------ */

void KNH_TSTATICOBJ(knh_Object_t **varaddr)
{
	if(knh_tStaticVariableSize == KNH_TSTATICOBJ_SIZE) {
		KNH_EXIT("Enlarge KNH_TSTATICOBJ_SIZE %d", KNH_TSTATICOBJ_SIZE);
		return;
	}
	knh_tStaticVariable[knh_tStaticVariableSize] = varaddr;
	knh_tStaticVariableSize++;
	knh_Object_RCinc(varaddr[0]);
}

/* ------------------------------------------------------------------------ */
/* [tObject] */

void knh_tObject_init0(void)
{
	if(knh_tObjectList != NULL) {
		KNH_EXIT("knh_tObjectList has been initiallized twice!!");
	}
	else {
		knh_tObjectList = (knh_Object_t**)KNH_MALLOC(NULL, SIZEOF_TOBJECTLIST);
		knh_UnusedObject = new_UnusedObject(NULL);
		knh_UnusedObjectSize += KNH_TOBJECT_SIZE;
	}
	knh_constNull = new_Nue__T(NULL, "Null!!");  knh_Object_RCinc((Object*)knh_constNull);
	knh_constVoid = new_Nue__T(NULL, "Null!!: return void"); knh_Object_RCinc((Object*)knh_constVoid);
	knh_constTrue = new_Boolean0(1);  knh_Object_RCinc(knh_constTrue);
	knh_constFalse = new_Boolean0(0); knh_Object_RCinc(knh_constFalse);


	/*TINT*/ {
		knh_int_t i;
		KNH_ASSERT(KNH_TINT_MIN < KNH_TINT_MAX);
		knh_tInt = (knh_Int_t**)KNH_MALLOC(NULL, SIZEOF_TINT);
		for(i = KNH_TINT_MIN; i <= KNH_TINT_MAX; i++) {
			knh_tInt[i - KNH_TINT_MIN] = new_Int0_(i);
			knh_Object_RCinc((Object*)knh_tInt[i - KNH_TINT_MIN]);
		}
	}

	/*TSTRING, TMETHODFIELD*/ {
		knh_tString = (knh_String_t**)KNH_MALLOC(NULL, SIZEOF_TSTRING);
	}

	knh_tString_init0();
	knh_rootSystem = new_System0();
	knh_Object_RCinc((Object*)knh_rootSystem);

	/*TSTATICOBJ*/ {
		int i;
		knh_tStaticVariable = (knh_Object_t***)KNH_MALLOC(NULL, SIZEOF_TSTATICOBJ);
		for(i = 0; i < KNH_TSTATICOBJ_SIZE; i++) {
			knh_tStaticVariable[i] = NULL;
		}
	}
}

/* ------------------------------------------------------------------------ */

void knh_tObject_traverse(Ctx *ctx, f_traverse ftr)
{
	/* TSTATICOBJ */ {
		int i;
		for(i = knh_tStaticVariableSize - 1; i >= 0; i--) {
			knh_Object_t **var = knh_tStaticVariable[i];
			ftr(ctx, var[0]);
			if(IS_SWEEP(ftr)) {
				var[0] = NULL;
			}
		}
		if(IS_SWEEP(ftr)) {
			KNH_FREE(knh_tStaticVariable, SIZEOF_TSTATICOBJ);
			knh_tStaticVariable = NULL;
			knh_tStaticVariableSize = 0;
		}
	}
	/*TSTRING, TMETHODFIELD*/ {
		knh_int_t i;
		for(i = 0; i < KNH_TSTRING_SIZE; i++) {
			ftr(ctx, UP(knh_tString[i]));
		}
		if(IS_SWEEP(ftr)) {
			KNH_FREE(knh_tString, SIZEOF_TSTRING);
			knh_tString = NULL;
		}
	}

	/* TINT */ {
		knh_int_t i;
		for(i = KNH_TINT_MIN; i <= KNH_TINT_MAX; i++) {
			ftr(ctx, UP(knh_tInt[i - KNH_TINT_MIN]));
		}
		if(IS_SWEEP(ftr)) {
			KNH_FREE(knh_tInt, SIZEOF_TINT);
			knh_tInt = NULL;
		}
	}

	ftr(ctx, UP(knh_rootSystem));
	ftr(ctx, knh_constTrue);
	ftr(ctx, knh_constFalse);
	ftr(ctx, (Object*)knh_constVoid);
	ftr(ctx, (Object*)knh_constNull);

	knh_tClass_traverse(ctx, ftr);

	if(IS_SWEEP(ftr)) {
		int i;
		for(i = 0; i < knh_tObjectListSize; i++) {
			knh_tObject_free(knh_tObjectList[i]);
			knh_tObjectList[i] = NULL;
		}
		KNH_FREE(knh_tObjectList, SIZEOF_TOBJECTLIST);
		knh_tObjectList = NULL;
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
