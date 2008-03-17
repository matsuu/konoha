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
/* [globals] */
//
//GLOBAL MapMap *tglobalMapMapNULL = NULL;
//
///* ------------------------------------------------------------------------ */
//
//MapMap* knh_MapMap_NULL()
//{
//	if(tglobalMapMapNULL == NULL) {
//		tglobalMapMapNULL = new_MapMap(NULL, 0, CLASS_Object, CLASS_Object, knh_MapMap_fmap__Null, KNH_NULL);
//		KNH_TGLOBAL(tglobalMapMapNULL);
//	}
//	return tglobalMapMapNULL;
//}


/* ======================================================================== */
/* [structs] */

void
knh_MapMap_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	MapMap *b =  (MapMap*)s1;
	b->size = 0;
	b->flag = 0;
	b->scid = CLASS_Object;
	b->tcid = CLASS_Object;
	b->fmap = knh_MapMap_fmap__Null;
	KNH_INITv(b->config, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

void
knh_MapMap_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
	MapMap *b =  (MapMap*)s1;
	MapMap *b2 = (MapMap*)s2;
	b2->fmap = b->fmap;
	KNH_INITv(b2->config, b->config);
}

/* ------------------------------------------------------------------------ */

#define _knh_MapMap_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void
knh_MapMap_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	MapMap *b =  (MapMap*)s;
	gc(ctx, b->config);
}

/* ======================================================================== */
/* [constructors] */

MapMap* 
new_MapMap(Ctx *ctx, knh_flag_t flag, knh_class_t scid, knh_class_t tcid, f_mapmap fmap, Object *conf)
{
	MapMap* b = 
		(MapMap*)knh_Object_malloc0(ctx, KNH_FLAG_MapMap, CLASS_MapMap, sizeof(MapMap));
	knh_MapMap_struct_init(ctx, (Struct*)b, 0, NULL);
	b->size = 0;
	b->flag = flag;
	b->scid = scid;
	b->tcid = tcid;
	if(fmap == NULL) {
		b->fmap = knh_tmapmap_config(ctx, conf, scid, tcid);
		DEBUG_ASSERT(fmap != NULL);
	}else {
		b->fmap = fmap;
	}
	KNH_SETv(ctx, b->config, conf);
	return b;
}

/* ======================================================================== */
/* [interface] */

Object* knh_MapMap_fmap__Interface(Ctx *ctx, Object *self, MapMap *map)
{
	return self;
}

/* ------------------------------------------------------------------------ */

MapMap* 
new_MapMap__interface(Ctx *ctx, knh_class_t scid, knh_class_t tcid)
{
	return new_MapMap(ctx, KNH_FLAG_MMF_INTERFACE, scid, tcid, knh_MapMap_fmap__Interface, KNH_NULL);
}

/* ======================================================================== */
/* [interface] */

Object* knh_MapMap_fmap__defvalue(Ctx *ctx, Object *self, MapMap *map)
{
	return knh_tclass_safevalue(ctx, map->tcid);
}

/* ------------------------------------------------------------------------ */

Object* knh_MapMap_fmap__Null(Ctx *ctx, Object *self, MapMap *map)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), "NoSuchMapping!!: %s%s ==> %s%s", CLASSQN(map->scid), CLASSQN(map->tcid));
	return new_Nue(ctx, new_String__fast(ctx, CLASS_String, B(buf)));
}

/* ------------------------------------------------------------------------ */

MapMap* 
new_MapMap__NoSuchMapping(Ctx *ctx, knh_class_t scid, knh_class_t tcid)
{
	if(scid == CLASS_Nue && knh_tclass_hasDefaultValue(tcid)) {
		return new_MapMap(ctx, 0, scid, tcid, knh_MapMap_fmap__defvalue, KNH_NULL);
	}
	return new_MapMap(ctx, 0, scid, tcid, knh_MapMap_fmap__Null, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_MapMap_isNoSuchMapping(MapMap *b)
{
	return (b->fmap == knh_MapMap_fmap__Null);
}

/* ======================================================================== */
/* [methods] */

INLINE
Object *knh_MapMap_execMap(Ctx *ctx, MapMap *b, Object *sub)
{
	return b->fmap(ctx, sub, b);
}

/* ======================================================================== */
/* [MapMaps] */

/* @Map MapMap, String */


Object* knh_MapMap_toString(Ctx *ctx, Object *self, MapMap *map)
{
	//MapMap *b = (MapMap*)DEBUG_CAST(SELF, self);
	
	return KNH_NULL;
}

/* ======================================================================== */
/* [movabletext] */

/* @method void MapMap.%dump(OutputStream w, Any m) */

void knh_MapMap__dump(Ctx *ctx, MapMap *b, OutputStream *w, Any *m)
{
	knh_write__type(ctx, w, b->scid);
	if(knh_MapMap_isTotal(b)) {
		knh_write(ctx, w, STEXT("==>"));
	}else{
		knh_write(ctx, w, STEXT("-->"));
	}
	knh_write__type(ctx, w, b->tcid);
	knh_putc(ctx, w, ':');
	knh_write__i(ctx, w, b->flag);
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
