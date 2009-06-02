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

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif


/* ======================================================================== */
/* [func] */

static
MAPPER knh_fmapper_method(Ctx *ctx, knh_sfp_t *sfp)
{
	Method *mtd = (Method*)DP(sfp[1].mpr)->mapdata;
	KNH_ASSERT(IS_Method(mtd));
	KNH_SWAP(ctx, sfp, 1, 0);
	KNH_SCALL(ctx, sfp, 0, mtd, /*args */0);
}

/* ------------------------------------------------------------------------ */

static
knh_fmapper konoha_findMapperFunc(Ctx *ctx, Object *mapdata, knh_class_t scid, knh_class_t tcid)
{
	if(IS_Method(mapdata)) return knh_fmapper_method;
	return knh_fmapper_null;
}

/* ======================================================================== */
/* [constructors] */

Mapper* new_Mapper(Ctx *ctx, knh_flag_t flag, knh_class_t scid, knh_class_t tcid, knh_fmapper fmap, Object *mapdata)
{
	knh_Mapper_t* o = (Mapper*)new_Object_bcid(ctx, CLASS_Mapper, 0);
	DP(o)->size = 0;
	DP(o)->flag = flag;
	DP(o)->scid = scid;
	DP(o)->tcid = tcid;
	if(fmap == NULL) {
		o->fmap_1 = konoha_findMapperFunc(ctx, mapdata, scid, tcid);
		KNH_ASSERT(fmap != NULL);
	}else {
		o->fmap_1 = fmap;
	}
	KNH_SETv(ctx, DP(o)->mapdata, mapdata);
	return o;
}

/* ======================================================================== */
/* [MapMap] */

static
MAPPER knh_fmapper_mapmap(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_ASSERT(IS_Mapper(sfp[1].mpr));
	Mapper *mpr = sfp[1].mpr;
	Mapper *m1 = DP(mpr)->m1, *m2 = DP(mpr)->m2;
	KNH_ASSERT(knh_Mapper_isMapMap(mpr));
	KNH_ASSERT(IS_Mapper(m1));
	KNH_MOV(ctx, sfp[1].o, m1);
	(m1)->fmap_1(ctx, sfp);
	if(IS_NULL(sfp[0].o)) return ;
	KNH_ASSERT(IS_Mapper(m2));
	KNH_MOV(ctx, sfp[1].o, m2);
	(m2)->fmap_1(ctx, sfp);
}

/* ------------------------------------------------------------------------ */

Mapper* new_MapMap(Ctx *ctx, Mapper *m1, Mapper *m2)
{
	knh_Mapper_t* mpr = (Mapper*)new_Object_bcid(ctx, CLASS_Mapper, 0);
	mpr->h.flag = FLAG_Mapper|KNH_FLAG_MMF_MAPMAP;
	DBG2_P("MAPMAP %p %s => %s => %s", mpr, CLASSN(DP(m1)->scid), CLASSN(DP(m1)->tcid), CLASSN(DP(m2)->tcid));
	DP(mpr)->size = 0;
	DP(mpr)->flag = DP(m1)->flag | DP(m2)->flag;
	DP(mpr)->scid = DP(m1)->scid;
	DP(mpr)->tcid = DP(m2)->tcid;
	KNH_ASSERT(IS_Mapper(m1));
	KNH_SETv(ctx, DP(mpr)->m1, m1);
	KNH_ASSERT(IS_Mapper(m2));
	KNH_SETv(ctx, DP(mpr)->m2, m2);
	mpr->fmap_1 = knh_fmapper_mapmap;
	return mpr;
}

/* ======================================================================== */
/* [movabletext] */
/* @method void Mapper.%k(OutputStream w, String m) */

void knh_Mapper__k(Ctx *ctx, Mapper *o, OutputStream *w, String *m)
{
	knh_write_cid(ctx, w, DP(o)->scid);
	if(knh_Mapper_isTotal(o)) {
		knh_write(ctx, w, STEXT("==>"));
	}else{
		knh_write(ctx, w, STEXT("-->"));
	}
	knh_write_cid(ctx, w, DP(o)->tcid);
//	knh_putc(ctx, w, ':');
//	knh_write__flag(ctx, w, DP(o)->flag);
}

/* ======================================================================== */
/* [mapper] */

void konoha_addMapper(Ctx *ctx, Mapper *mpr)
{
	knh_ClassTable_readyClassMap(ctx, DP(mpr)->scid);
	knh_ClassMap_add(ctx, ctx->share->ClassTable[DP(mpr)->scid].cmap, mpr);
}

/* ------------------------------------------------------------------------ */

void konoha_addMapperFunc(Ctx *ctx, knh_flag_t flag, knh_type_t stype, knh_type_t ttype, knh_fmapper fmap, Object *mapdata)
{
	knh_class_t cid = CLASS_type(stype);
	KNH_ASSERT_cid(cid);
	knh_ClassTable_readyClassMap(ctx, cid);
	knh_ClassMap_add(ctx, ctx->share->ClassTable[cid].cmap,
		new_Mapper(ctx, flag, CLASS_type(stype), CLASS_type(ttype), fmap, mapdata));
}

/* ======================================================================== */
/* [cache] */

static
Mapper *knh_Context_getMapperCache(Ctx *ctx, knh_class_t scid, knh_class_t tcid)
{
	knh_hcode_t h = ((((knh_hcode_t)scid) << (sizeof(knh_class_t) * 8)) + tcid) % ctx->cachesize;
	Mapper *mpr = ctx->mprCache[h];
	if(mpr != NULL) {
		if(DP(mpr)->scid == scid && DP(mpr)->tcid == tcid) {
			knh_stat_mprCacheHit(ctx);
			return mpr;
		}
		knh_stat_fmtCacheMiss(ctx);
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
Mapper *knh_Context_setMapperCache(Ctx *ctx, knh_class_t scid, knh_class_t tcid, Mapper *mpr)
{
	knh_hcode_t h = ((((knh_hcode_t)scid) << (sizeof(knh_class_t) * 8)) + tcid) % ctx->cachesize;
	ctx->mprCache[h] = mpr;
	return mpr;
}

/* ------------------------------------------------------------------------ */
/* [Mapper] */

MAPPER knh_Mapper_fasis(Ctx *ctx, knh_sfp_t *sfp)
{
}

/* ------------------------------------------------------------------------ */

static
Mapper* new_Mapper__asis(Ctx *ctx, knh_class_t scid, knh_class_t tcid)
{
	return new_Mapper(ctx, 0, scid, tcid, knh_Mapper_fasis, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

MAPPER knh_fmapper_null(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_MAPPED(ctx, sfp, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

static
Mapper* new_Mapper__NoSuchMapping(Ctx *ctx, knh_class_t scid, knh_class_t tcid)
{
	return new_Mapper(ctx, 0, scid, tcid, knh_fmapper_null, KNH_NULL);
}

/* ------------------------------------------------------------------------ */


knh_bool_t knh_Mapper_isNoSuchMapping(Mapper *mpr)
{
	return ((mpr)->fmap_1 == knh_fmapper_null);
}

/* ======================================================================== */

#define _konoha_findMapper(ctx, scid, tcid) konoha_findMapper_(ctx, scid, tcid, 1)
#define _knh_Class_getMapper(ctx, scid, tcid)  konoha_findMapper_(ctx, scid, tcid, 0)

Mapper *konoha_findMapper_(Ctx *ctx, knh_class_t scid, knh_class_t tcid, int isgen)
{
	KNH_ASSERT_cid(scid);
	KNH_ASSERT_cid(tcid);
	DBG2_P("finding.. %s ==> %s",CLASSN(scid), CLASSN(tcid));
	if(scid == CLASS_Any) {
		if(isgen == 0) return (Mapper*)KNH_NULL;
		KNH_ASSERT(scid != CLASS_Any);
	}
	KNH_ASSERT(tcid != CLASS_Nue);

	Mapper *mpr = knh_Context_getMapperCache(ctx, scid, tcid);
	if(mpr != NULL) { return mpr; }

	{
		knh_class_t sbcid = scid;
		while(1) {
			ClassMap *cmap = ctx->share->ClassTable[sbcid].cmap;
			//DBG2_P("scid=%d,%s", sbcid, CLASSN(sbcid));
			//DBG2_(knh_ClassMap__dump(ctx, cmap, KNH_STDOUT, (String*)KNH_NULL));
			int i;
			for(i = 0; i < DP(cmap)->size; i++) {
				mpr = DP(cmap)->maplist[i];
				if(DP(mpr)->tcid == tcid) {
					return knh_Context_setMapperCache(ctx, scid, tcid, mpr);
				}
			}
			for(i = 0; i < DP(cmap)->size; i++) {
				mpr = DP(cmap)->maplist[i];
				if(knh_class_instanceof(ctx, DP(mpr)->tcid, tcid)) {
					return knh_Context_setMapperCache(ctx, scid, tcid, mpr);
				}
			}
			if(sbcid == CLASS_Object) break;
			for(i = 0; i < DP(cmap)->size; i++) {
				ClassMap *cmap2 = ctx->share->ClassTable[DP(DP(cmap)->maplist[i])->tcid].cmap;
				int j;
				KNH_ASSERT_cid(DP(DP(cmap)->maplist[i])->tcid);
				for(j = 0; j < DP(cmap2)->size; j++) {
					mpr = DP(cmap2)->maplist[j];
					if(DP(mpr)->tcid == tcid) {
						return knh_Context_setMapperCache(ctx, scid, tcid, new_MapMap(ctx, DP(cmap)->maplist[i], mpr));
					}
				}
				for(j = 0; j < DP(cmap2)->size; j++) {
					mpr = DP(cmap2)->maplist[j];
					if(knh_class_instanceof(ctx, DP(mpr)->tcid, tcid)) {
						return knh_Context_setMapperCache(ctx, scid, tcid, new_MapMap(ctx, DP(cmap)->maplist[i], mpr));
					}
				}
			}
			if(knh_Class_isGenerics(sbcid) && ctx->share->ClassTable[sbcid].bcid != sbcid) {
				sbcid = ctx->share->ClassTable[sbcid].bcid;
			}
			else {
				sbcid = ctx->share->ClassTable[sbcid].supcid;
			}
		}
	}
	/* GENERATIVE PART */
	if(scid == tcid || scid == CLASS_Nue || knh_class_instanceof(ctx, scid, tcid)) {  /* default */
		mpr = new_Mapper__asis(ctx, scid, tcid);
		konoha_addMapper(ctx, mpr);
		return knh_Context_setMapperCache(ctx, scid, tcid, mpr);
	}
//
//	if(ctx->share->ClassTable[scid].p1 != CLASS_Nue && ctx->share->ClassTable[scid].p1 == ctx->share->ClassTable[tcid].p1) {
//		/* C.. ==> C[] */
//		if(ctx->share->ClassTable[scid].bcid == CLASS_Iterator && ctx->share->ClassTable[tcid].bcid == CLASS_Array) {
//			return knh_tmapper_setcache(ctx, scid, tcid, knh_tMapper_newIteratorArray(ctx, scid, tcid));
//		}
//		/* C[] ==> C.. */
//		if(ctx->share->ClassTable[scid].bcid == CLASS_Array && ctx->share->ClassTable[tcid].bcid == CLASS_Iterator) {
//			return knh_tmapper_setcache(ctx, scid, tcid, knh_tMapper_newArrayIterator(ctx, scid, tcid));
//		}
//	}
	if(isgen) {
		mpr = new_Mapper__NoSuchMapping(ctx, scid, tcid);
		konoha_addMapper(ctx, mpr);
		return knh_Context_setMapperCache(ctx, scid, tcid, mpr);
	}
	else {
		return (Mapper*)KNH_NULL;
	}
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif