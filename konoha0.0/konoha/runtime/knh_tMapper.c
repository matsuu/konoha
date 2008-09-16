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

#define mprHashMap(ctx) ((Context*)ctx)->tmapperHashMap

#ifdef KNH_STATMODE1
static size_t cache_hit  = 0;
static size_t cache_miss = 0;
#endif

/* ------------------------------------------------------------------------ */

//#ifdef KNH_STATMODE1
//void konoha_stat_tmapmap_cache()
//{
//	DBG2_P("hit=%d, miss=%d", (int)cache_hit, (int)cache_miss);
//}
//#endif

/* ======================================================================== */
/* [tmapmap] */

void KNH_TMAPPER(Ctx *ctx, knh_flag_t flag, knh_type_t stype, knh_type_t ttype, f_mapper fmap, Object *mapdata)
{
	knh_class_t cid = TYPE_UNMASK(stype);
	DEBUG_ASSERT_cid(cid);
	knh_ClassMap_add(ctx, knh_tClass[cid].cmap,
		new_Mapper(ctx, flag, TYPE_UNMASK(stype), TYPE_UNMASK(ttype), fmap, mapdata));
}

#define _KNH_TMAPMAP  KNH_TMAPPER

/* ======================================================================== */
/* [tcache] */

static
Mapper *knh_tmapper_getcache(Ctx *ctx, knh_class_t scid, knh_class_t tcid)
{
	knh_uint_t hcode = (scid << (sizeof(knh_class_t) * 8)) + tcid;
#ifdef KNH_STATMODE1
	Mapper *mar = knh_HashMap_get(ctx, mprHashMap(ctx), hcode, NULL);
	if(IS_NOTNULL(mar)) {
		cache_hit++;
		KNH_ASSERT(scid == DP(mpr)->scid && tcid == DP(mpr)->tcid);
	}
	else {
		cache_miss++;
	}
	return mar;
#else
	return (Mapper*)knh_HashMap_get__hcode(ctx, mprHashMap(ctx), hcode);
#endif
}

/* ------------------------------------------------------------------------ */

static
Mapper *knh_tmapper_setcache(Ctx *ctx, knh_class_t scid, knh_class_t tcid, Mapper *mpr)
{
	knh_uint_t hcode = (scid << (sizeof(knh_class_t) * 8)) + tcid;
	//DBG2_P("scid=%d, tcid=%d, hcode=%d", scid, tcid, hcode);
	knh_HashMap_set__hcode(ctx, mprHashMap(ctx), hcode, UP(mpr));
	return mpr;
}

/* ------------------------------------------------------------------------ */
/* [Mapper] */

Object* knh_Mapper_fInterface(Ctx *ctx, Object *o, Mapper *mpr)
{
	return o;
}

/* ------------------------------------------------------------------------ */

static
Mapper* new_Mapper__asis(Ctx *ctx, knh_class_t scid, knh_class_t tcid)
{
	return new_Mapper(ctx, 0, scid, tcid, knh_Mapper_fInterface, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

Object* knh_Mapper_fNull(Ctx *ctx, Object *o, Mapper *mpr)
{
	char buf[CLASSNAME_BUFSIZ*2];
	if(knh_Context_isVerbose(ctx)) {
		knh_snprintf(buf, sizeof(buf), "NoSuchMapping!!: %s ==> %s", CTXCLASSN(DP(mpr)->scid), CTXCLASSN(DP(mpr)->tcid));
	}else {
		knh_snprintf(buf, sizeof(buf), "NoSuchMapping!!: %s ==> %s", CLASSN(DP(mpr)->scid), CLASSN(DP(mpr)->tcid));
	}
	return (Object*)new_Nue__s(ctx, buf);
}

/* ------------------------------------------------------------------------ */

static
Mapper* new_Mapper__NoSuchMapping(Ctx *ctx, knh_class_t scid, knh_class_t tcid)
{
	return new_Mapper(ctx, 0, scid, tcid, knh_Mapper_fNull, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_Mapper_isNoSuchMapping(Mapper *o)
{
	return (DP(o)->fmap == knh_Mapper_fNull);
}

/* ======================================================================== */

Mapper *knh_tMapper_find(Ctx *ctx, knh_class_t scid, knh_class_t tcid)
{
	DEBUG_ASSERT_cid(scid);
	DEBUG_ASSERT_cid(tcid);
	DBG2_P("finding.. %s ==> %s", CLASSN(scid), CLASSN(tcid));

	Mapper *mpr = knh_tmapper_getcache(ctx, scid, tcid);
	if(IS_NOTNULL(mpr)) { return mpr; }

	if(scid == tcid || scid == CLASS_Nue || knh_class_instanceof(scid, tcid)) {  /* default */
		return knh_tmapper_setcache(ctx, scid, tcid, new_Mapper__asis(ctx, scid, tcid));
	}

	knh_class_t sbcid = scid;

	while(1) {
		ClassMap *cmap = knh_tClass[sbcid].cmap;
		int i;
		DBG2_P("scid=%d,%s", sbcid, CLASSN(sbcid));
		DBG2_(knh_ClassMap__dump(ctx, cmap, KNH_STDOUT, KNH_NULL));
		for(i = 0; i < DP(cmap)->size; i++) {
			mpr = DP(cmap)->maplist[i];
			if(DP(mpr)->tcid == tcid) return knh_tmapper_setcache(ctx, scid, tcid, mpr);
		}
		for(i = 0; i < DP(cmap)->size; i++) {
			mpr = DP(cmap)->maplist[i];
			if(knh_class_instanceof(DP(mpr)->tcid, tcid)) return knh_tmapper_setcache(ctx, scid, tcid, mpr);
		}
		for(i = 0; i < DP(cmap)->size; i++) {
			ClassMap *cmap2 = knh_tClass[DP(DP(cmap)->maplist[i])->tcid].cmap;
			int j;
			DEBUG_ASSERT_cid(DP(DP(cmap)->maplist[i])->tcid);
			for(j = 0; j < DP(cmap2)->size; j++) {
				mpr = DP(cmap2)->maplist[j];
				if(DP(mpr)->tcid == tcid) {
					return knh_tmapper_setcache(ctx, scid, tcid, new_MapMap(ctx, DP(cmap)->maplist[i], mpr));
				}
			}
			for(j = 0; j < DP(cmap2)->size; j++) {
				mpr = DP(cmap2)->maplist[j];
				if(knh_class_instanceof(DP(mpr)->tcid, tcid)) {
					return knh_tmapper_setcache(ctx, scid, tcid, new_MapMap(ctx, DP(cmap)->maplist[i], mpr));
				}
			}
		}
		if(sbcid == CLASS_Object) break;
		if(knh_tClass_isPMZ(sbcid) && knh_tClass[sbcid].bcid != sbcid) {
			sbcid = knh_tClass[sbcid].bcid;
		}
		else {
			sbcid = knh_tClass[sbcid].supcid;
		}
	}

	/* GENERATIVE PART */
	if(knh_tClass[scid].p1 != CLASS_Nue && knh_tClass[scid].p1 == knh_tClass[tcid].p1) {
		/* C.. ==> C[] */
		if(knh_tClass[scid].bcid == CLASS_Iterator && knh_tClass[tcid].bcid == CLASS_Array) {
			return knh_tmapper_setcache(ctx, scid, tcid, knh_tMapper_newIteratorArray(ctx, scid, tcid));
		}
		/* C[] ==> C.. */
		if(knh_tClass[scid].bcid == CLASS_Array && knh_tClass[tcid].bcid == CLASS_Iterator) {
			return knh_tmapper_setcache(ctx, scid, tcid, knh_tMapper_newArrayIterator(ctx, scid, tcid));
		}
	}

	return knh_tmapper_setcache(ctx, scid, tcid, new_Mapper__NoSuchMapping(ctx, scid, tcid));
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
