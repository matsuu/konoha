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
/* [macro] */

/* ------------------------------------------------------------------------ */
/* [malloc] */


Object *knh_Object_malloc0(Ctx *ctx, knh_flag_t flag, knh_class_t cid, size_t size) 
{
#ifdef KONOHA_SAFEMODE
	if(ctx != NULL && cid < KONOHA_TSTRUCT_SIZE && knh_tstruct_size(cid) != size) {
		DEBUG("TODO: %s size=%d, but %d is given", STRUCTN(cid), (int)knh_tstruct_size(cid), (int)size);
	}
#endif

	hObject *h = (hObject*)knh_malloc(ctx, KNH_SIZE(size) + sizeof(hObject));
#ifdef KONOHA_OBJECT_MAGIC
	h->magic = KONOHA_OBJECT_MAGIC;
#endif
	h->cid  = cid;
	h->flag = flag;
	h->refc = 0;
	knh_tclass_count_inc(cid);
	return (Object*)(h+1);
}

/* ------------------------------------------------------------------------ */

Object *knh_Object_malloc(Ctx *ctx, knh_class_t cid) 
{
	size_t size = knh_tclass_size(cid);
//	KNH_ASSERT(size > 0);
	hObject *h = (hObject*)knh_malloc(ctx, size + sizeof(hObject));
#ifdef KONOHA_OBJECT_MAGIC
	h->magic = KONOHA_OBJECT_MAGIC;
#endif
	h->cid  = cid;
	h->flag = knh_tclass_oflag(cid);
	h->refc = 0;
	knh_tclass_count_inc(cid);
	return (Object*)(h+1);
}

/* ------------------------------------------------------------------------ */
/* [cast] */

//Object *knh_Object_cast(Ctx *ctx, Object *o)
//{
//	KNH_ASSERT(IS_NOTNULL(o));
//#ifdef KONOHA_OBJECT_MAGIC
//	KNH_ASSERT(knh_Object_head(o)->magic == KONOHA_OBJECT_MAGIC);
//#endif
//	return o;
//}
//
///* ------------------------------------------------------------------------ */
//
//Object *knh_Object_castOrNull(Ctx *ctx, Object *o)
//{
//#ifdef KONOHA_OBJECT_MAGIC
//	KNH_ASSERT(knh_Object_head(o)->magic == KONOHA_OBJECT_MAGIC);
//#endif
//	return o;
//}

/* ------------------------------------------------------------------------ */

void knh_Object_dispose(Ctx *ctx, Object *o)
{
	hObject *h = knh_Object_head(o);
	knh_class_t cid = h->cid;
	size_t size = sizeof(hObject);
	knh_struct_t sid;
	size_t offset; //int f = 0;
	while((offset = knh_tclass_offset(cid)) != 0) {
		sid = knh_tclass_sid(cid); //f = 1;
//		DEBUG("[cid=%d] cid=%d, sid=%d, supcid=%d, offset=%d", h->cid, cid, sid, knh_tclass_supcid(ctx, cid), offset);
		knh_tstruct_ftraverse(sid)(ctx, (Struct*)(&KNH_FIELDn(o, offset)), knh_sweep);
		size += knh_tstruct_size(sid);
		cid = knh_tclass_supcid(cid);
	}
	sid = knh_tclass_topsid(cid);
//	if(cid >= KONOHA_TSTRUCT_SIZE) {
//		DEBUG("[cid=%d]* cid=%d, sid=%d, offset=%d", h->cid, cid, sid, offset);
//	}
	knh_tstruct_ftraverse(sid)(ctx, (Struct*)o, knh_sweep);
	size += knh_tstruct_size(sid);
#ifdef KNH_FLAG_OF_METADATA
	if((h->flag & KNH_FLAG_OF_METADATA) == KNH_FLAG_OF_METADATA && ctx != NULL) {
		knh_metadata_clear(ctx, o);
	}
#endif
	knh_tclass_count_dec(h->cid);
	knh_free(h, size);
}

/* ------------------------------------------------------------------------ */

INLINE
void knh_Object_refc_inc(Object *self)
{
	hObject *h = knh_Object_head(self);
#ifdef KONOHA_OBJECT_MAGIC
	KNH_ASSERT(h->magic == KONOHA_OBJECT_MAGIC);
#endif
	h->refc++;
}

/* ------------------------------------------------------------------------ */

/* @see(knh_VirtualMachineCode_utraverse) */

void knh_Object_vmcinc(Ctx *ctx, Object *self)
{
	hObject *h = knh_Object_head(self);
#ifdef KONOHA_OBJECT_MAGIC
	KNH_ASSERT(h->magic == KONOHA_OBJECT_MAGIC);
#endif
	h->refc++;
}

/* ------------------------------------------------------------------------ */

void knh_Object_refc_dec(Ctx *ctx, Object *self)
{
	hObject *h = knh_Object_head(self);
#ifdef KONOHA_OBJECT_MAGIC
	KNH_ASSERT(h->magic == KONOHA_OBJECT_MAGIC);
#endif
	h->refc--;
	if(h->refc == 0) {
		knh_Object_dispose(ctx, self);
	}
}

#define _knh_sweep      knh_Object_refc_dec
#define _IS_SWEEP(gc)   (gc == knh_sweep)

/* ======================================================================== */

INLINE 
void knh_Object_safefree(Ctx *ctx, Object *self)
{
	hObject *h = knh_Object_head(self);
#ifdef KONOHA_OBJECT_MAGIC
	KNH_ASSERT(h->magic == KONOHA_OBJECT_MAGIC);
#endif
	if(h->refc == 0) {
		knh_Object_dispose(ctx, self);
	}
}

#define _KNH_SAFEFREE(ctx,o)  knh_Object_safefree(ctx,o)

/* ======================================================================== */
/* [aspect] */


void knh_INITv(Object **var, Object *o)
{
	KNH_ASSERT(o != NULL);
	var[0] = o;
	knh_Object_refc_inc(o);
}

#define _KNH_INITv(v, o) {\
		v = o; \
		DEBUG_ASSERT(v != NULL); \
		knh_Object_head(v)->refc++; \
	}\

/* ------------------------------------------------------------------------ */


void knh_INITn(Object **var, int n, Object *o)
{
	int i ;
	KNH_ASSERT(o != NULL);
	for(i = 0; i < n; i++) {
		var[i] = o;
		knh_Object_refc_inc(o);
	}
}

#define _KNH_INITn(a,n,v)          knh_INITn((a),(n),(v))

/* ------------------------------------------------------------------------ */

void knh_SETv(Ctx *ctx, Object **var, Object *o)
{
	KNH_ASSERT(o != NULL);
	knh_Object_refc_inc(o);
	knh_Object_refc_dec(ctx, var[0]);
	var[0] = o;
}

#define _KNH_SETv_(ctx,a,v)         knh_SETv(ctx,&(a),(v))

#define _KNH_SETv(ctx,v,o) {\
		Object *o_tmp = (Object *)o; \
		DEBUG_ASSERT(o_tmp != NULL); \
		knh_Object_head(o_tmp)->refc++; \
		knh_Object_refc_dec(ctx, v); \
		v = o_tmp; \
	}\

#define _KNH_SETt(ctx,T,v,o) {\
		T *o_tmp = (T *)o; \
		DEBUG_ASSERT(o_tmp != NULL); \
		knh_Object_head(o_tmp)->refc++; \
		knh_Object_refc_dec(ctx, v); \
		v = (T *)o_tmp; \
	}\

/* ------------------------------------------------------------------------ */

void knh_SETv__ngc(Ctx *ctx, Object **v, Object *o)
{
	KNH_ASSERT(o != NULL);
	knh_Object_head(o)->refc++;
	knh_Object_head(v[0])->refc--;
	v[0] = o;
}

#define _KNH_SETv__ngc_(ctx,a,v)    knh_SETv__ngc(ctx,&((Object*)a),(v))

#define _KNH_SETv__ngc(ctx,v,o) {\
		Object *o_tmp = (Object*)o; \
		knh_Object_head(o_tmp)->refc++; \
		knh_Object_head(v)->refc--; \
		v = o_tmp; \
	} \

#define _KNH_SETt__ngc(ctx, T, v,o) {\
		T *o_tmp = (T *)o; \
		knh_Object_head(o_tmp)->refc++; \
		knh_Object_head(v)->refc--; \
		v = (T *)o_tmp; \
	} \

/* ------------------------------------------------------------------------ */

void knh_SETn(Ctx *ctx, Object **var, int n, Object *o)
{
	int i;
	KNH_ASSERT(o != NULL);
	for(i = 0; i < n; i++) {
		knh_Object_refc_inc(o);
		knh_Object_refc_dec(ctx, var[i]);
		var[i] = o;
	}
}

#define _KNH_SETn_(ctx,a,n,v)       knh_SETn(ctx,a,(n),(v))

/* ------------------------------------------------------------------------ */

void knh_FINALv(Ctx *ctx, Object **var)
{
   knh_Object_refc_dec(ctx, var[0]);
   var[0] = NULL;
}

#define _KNH_FINALv_(ctx,a) knh_FINALv(ctx,(Object**)&(a))

#define _KNH_FINALv(ctx, v) {\
		knh_Object_refc_dec(ctx, v); \
		v = NULL; \
	}\

/* ------------------------------------------------------------------------ */

void
knh_FINALn(Ctx *ctx, Object **var, int n)
{
	int i;
	for(i = 0; i < n; i++) {
		knh_Object_refc_dec(ctx, var[i]);	
		var[i] = NULL;
	}
}

#define _KNH_FINALn(ctx,a,n)       knh_FINALn(ctx,(a),(n))

/* ======================================================================== */
/* [oarray] */

INLINE
Object** knh_oarray_malloc(Ctx *ctx, size_t size, Object *value)
{
	Object **a = (Object**)knh_malloc(ctx, size * sizeof(Object*));
	knh_INITn(a, size, value);
	return a;
}

/* ------------------------------------------------------------------------ */

void knh_oarray_traverse(Ctx *ctx, Object **a, size_t size, f_gc gc)
{
	size_t i;
	for(i = 0; i < size; i++) {
		gc(ctx, a[i]);
	}
	if(IS_SWEEP(gc)) {
		knh_free(a, size * sizeof(Object*));
	}
}

/* ------------------------------------------------------------------------ */
	

#ifdef __cplusplus
}
#endif
