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

KNHAPI(Mapper*) new_Mapper(Ctx *ctx, knh_flag_t flag, knh_class_t scid, knh_class_t tcid, knh_fmapper fmap, Object *mapdata)
{
	knh_Mapper_t* o = (Mapper*)new_Object_bcid(ctx, CLASS_Mapper, 0);
	DP(o)->size = 0;
	if(knh_class_isFinal(scid)) {
		DP(o)->flag = flag | KNH_FLAG_MMF_FINAL;
	}
	else {
		DP(o)->flag = flag;
	}
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
	KNH_NOTICE(ctx, "generated mapper: %C => %C => %C", DP(m1)->scid, DP(m1)->tcid, DP(m2)->tcid);
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
}

/* ======================================================================== */
/* [mapper] */

KNHAPI(void) knh_addMapper(Ctx *ctx, Mapper *mpr)
{
	knh_ClassTable_readyClassMap(ctx, DP(mpr)->scid);
	knh_ClassMap_add(ctx, ctx->share->ClassTable[DP(mpr)->scid].cmap, mpr);
}

/* ------------------------------------------------------------------------ */

void knh_addMapperFunc(Ctx *ctx, knh_flag_t flag, knh_type_t stype, knh_type_t ttype, knh_fmapper fmap, Object *mapdata)
{
	knh_class_t cid = CLASS_type(stype);
	KNH_ASSERT_cid(cid);
	knh_ClassTable_readyClassMap(ctx, cid);
	knh_ClassMap_add(ctx, ClassTable(cid).cmap,
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
	DBG2_(
	Mapper *mpr = sfp[1].mpr;
	DBG2_P("mpr: %s ==> %s", CLASSN(DP(mpr)->scid), CLASSN(DP(mpr)->tcid));
	);
	KNH_THROWs(ctx, "ClassCast!!");
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
	if(scid == CLASS_Any) {
		if(isgen == 0) return (Mapper*)KNH_NULL;
		KNH_ASSERT(scid != CLASS_Any);
	}

	Mapper *mpr = knh_Context_getMapperCache(ctx, scid, tcid);
	if(mpr != NULL) { return mpr; }
	DBG2_P("finding.. %s ==> %s",CLASSN(scid), CLASSN(tcid));

	{
		knh_class_t sbcid = scid;
		while(1) {
			ClassMap *cmap = ctx->share->ClassTable[sbcid].cmap;
			//DBG2_P("scid=%d,%s", sbcid, CLASSN(sbcid));
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
				knh_class_t mcid = DP(DP(cmap)->maplist[i])->tcid;
				KNH_ASSERT_cid(mcid);
				if(mcid <= CLASS_Class) {
					DBG_P("forbid lowlevel transitivity %s", CLASSN(mcid));
					continue;   /* Stop lowlevel inference */
				}
				ClassMap *cmap2 = ctx->share->ClassTable[mcid].cmap;
				int j;
				for(j = 0; j < DP(cmap2)->size; j++) {
					mpr = DP(cmap2)->maplist[j];
					if(DP(mpr)->tcid == tcid) {
						Mapper *mapmap = new_MapMap(ctx, DP(cmap)->maplist[i], mpr);
						knh_addMapper(ctx, mapmap);
						return knh_Context_setMapperCache(ctx, scid, tcid, mapmap);
					}
				}
				for(j = 0; j < DP(cmap2)->size; j++) {
					mpr = DP(cmap2)->maplist[j];
					if(knh_class_instanceof(ctx, DP(mpr)->tcid, tcid)) {
						Mapper *mapmap = new_MapMap(ctx, DP(cmap)->maplist[i], mpr);
						knh_addMapper(ctx, mapmap);
						return knh_Context_setMapperCache(ctx, scid, tcid, mapmap);
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
	if(scid == tcid || knh_class_instanceof(ctx, scid, tcid)) {  /* default */
		mpr = new_Mapper__asis(ctx, scid, tcid);
		knh_addMapper(ctx, mpr);
		return knh_Context_setMapperCache(ctx, scid, tcid, mpr);
	}

	if(isgen) {
		mpr = new_Mapper__NoSuchMapping(ctx, scid, tcid);
		knh_addMapper(ctx, mpr);
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
