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

#define cache(ctx) ((Context*)ctx)->runtime->tmapmapHashMap

#ifdef KONOHA_DEBUGMODE

static size_t cache_hit  = 0;
static size_t cache_miss = 0;

#endif

/* ------------------------------------------------------------------------ */

#ifdef KONOHA_DEBUGMODE

void konoha_stat_tmapmap_cache()
{
	DEBUG("hit=%d, miss=%d", (int)cache_hit, (int)cache_miss);
}

#endif

/* ======================================================================== */
/* [tmapmap] */

void KNH_TMAPMAP(Ctx *ctx, knh_flag_t flag, knh_type_t stype, knh_type_t ttype, f_mapmap fmap, Object *conf)
{
	ClassRel *crel = knh_tclass_crel(TYPE_UNMASK(stype));
	knh_ClassRel_add(ctx, crel, new_MapMap(ctx, flag, TYPE_UNMASK_NULL(stype), TYPE_UNMASK_NULL(ttype), fmap, conf));
}

/* ======================================================================== */
/* [tcache] */

MapMap *knh_tmapmap_find_cache(Ctx *ctx, knh_class_t scid, knh_class_t tcid)
{
	knh_uint_t hcode = (scid << (sizeof(knh_class_t) * 8)) + tcid;
#ifdef KONOHA_DEBUGMODE
//	DEBUG("hcode=%d", (int)hcode);
	MapMap *map = knh_HashMap_get(ctx, cache(ctx), hcode, NULL);
	if(IS_NOTNULL(map)) {
		cache_hit++;
		DEBUG_ASSERT(scid == map->scid && tcid == map->tcid);
	}
	else {
		cache_miss++;
	}
	return map;
#else
	return (MapMap*)knh_HashMap_get(ctx, cache(ctx), hcode, NULL);
#endif
}

/* ------------------------------------------------------------------------ */

void knh_tmapmap_set_cache(Ctx *ctx, MapMap *map)
{
	knh_uint_t hcode = (map->scid << (sizeof(knh_class_t) * 8)) + map->tcid;
//	DEBUG("hcode=%d", (int)hcode);
	return knh_HashMap_set(ctx, cache(ctx), hcode, NULL, map);
}

/* ------------------------------------------------------------------------ */
/* [search] */

Object* knh_MapMap_fmap__Iterator(Ctx *ctx, Object *self, MapMap *map);

/* ------------------------------------------------------------------------ */

MapMap *knh_tmapmap_find(Ctx *ctx, knh_class_t scid, knh_class_t tcid)
{
	DEBUG("finding.. %s%s ==> %s%s", CLASSQN(scid), CLASSQN(tcid));

	MapMapNULL *map = NULL;
	map = knh_tmapmap_find_cache(ctx, scid, tcid);
	if(IS_NOTNULL(map)) {
		return map;
	}
	
	if(scid == tcid) {  /* default */
		map = new_MapMap__interface(ctx, scid, tcid);
		knh_tmapmap_set_cache(ctx, map);
		return map;
	}
	
	ClassRel *cm = knh_tclass_crel(TYPE_UNMASK(scid));
	//knh_ClassRel__dump(ctx, cm, KNH_STDOUT);

	if(TYPE_ISPLURAL(scid)) {
		map = knh_ClassRel_findp__first(cm, tcid);
		if(map != NULL) return map;
//		while(1) {
//			map = knh_ClassRel_findp__second(ctx, cm, tcid);
//			if(map != NULL) return map;		
//			cid = knh_tclass_supcid(ctx, cid);
//			if(cid == CLASS_Object) break;
//			cm = knh_tclass_cmap(ctx, cid);
//		}
	}else{
		map = knh_ClassRel_find__first(cm, tcid);
		if(map != NULL) return map;		
//		while(1) {
//			map = knh_ClassRel_find__second(ctx, cm, tcid);
//			if(map != NULL) return map;		
//			cid = knh_tclass_supcid(ctx, cid);
//			if(cid == CLASS_Object) break;
//			cm = knh_tclass_cmap(ctx, cid);
//		}
	}
	
	/* generative mapping */
	if(tcid == CLASS_Iterator || tcid == CLASS_TOPLURAL(scid)) {
		map = new_MapMap(ctx, 0, scid, tcid, knh_MapMap_fmap__Iterator, KNH_NULL);
	}
	else {
		map = new_MapMap__NoSuchMapping(ctx, scid, tcid);
	}
	knh_tmapmap_set_cache(ctx, map);
	return map;	
}

///* ------------------------------------------------------------------------ */
//
//
//MapMap *knh_Mapping_ufind(Ctx *ctx, classes_t cid, classes_t tcid)
//{
//	MapMap *map = knh_tmapmap_find(ctx, cid, tcid);
//	if(IS_NULL(map)) return knh_Mapping_NULL(ctx);
//	return map;
//}
//
///* ------------------------------------------------------------------------ */
//
//
//MapMap *knh_mapdb_ufind(Ctx *ctx, Object *mapdb, classes_t cid, classes_t tcid)
//{
//	TODO();
//	return knh_Mapping_ufind(ctx, cid, tcid);
//}	


/* ======================================================================== */
/* [config] */

/* ------------------------------------------------------------------------ */

Object* knh_MapMap_fMethod(Ctx *ctx, Object *self, MapMap *map)
{
	DEBUG_ASSERT(IS_Method(map->config));
	KNH_PUSHv(ctx, map->config);    /* ebp[-1] */
	KNH_PUSHv(ctx, self);           /* ebp[0] */
	KNH_SCALL(ctx, -1);
	VM_SHIFT(ctx, -1);
	return VM_EBP(ctx, 1);
}

/* ------------------------------------------------------------------------ */

f_mapmap knh_tmapmap_config(Ctx *ctx, Object *conf, knh_class_t scid, knh_class_t tcid)
{
	if(IS_Method(conf)) return knh_MapMap_fMethod;
	return knh_MapMap_fmap__Null;
}
 
/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
