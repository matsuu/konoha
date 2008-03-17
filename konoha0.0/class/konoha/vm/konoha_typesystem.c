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
/* [instaceof] */

INLINE
knh_bool_t knh_class_instanceof(knh_class_t scid, knh_class_t tcid)
{
	DEBUG_ASSERT(TYPE_ISNOTNULL(scid));
	DEBUG_ASSERT(TYPE_ISNOTNULL(tcid));
	
	if(knh_tclass_bcid(scid) == tcid || tcid == CLASS_any || tcid == CLASS_Bool) return 1;

	if(TYPE_ISPLURAL(scid)) {
		if(tcid == CLASS_any || tcid == CLASS_Iterator) return 1;
		if(!TYPE_ISPLURAL(tcid)) return 0;
		scid = TYPE_UNMASK(scid);
		tcid = TYPE_UNMASK(tcid);
	}

	int i;
	L_TAIL:;
	if(scid == tcid) return 1;

	ClassRel *crel = knh_tclass_crel(scid);
	for(i = 0; i < crel->size; i++) {
		if(knh_MapMap_isInterface(crel->maplist[i]) && crel->maplist[i]->tcid == tcid) return 1;
	}
	scid = knh_tclass_supcid(scid);
	if(scid == CLASS_Object) return 0;
	goto L_TAIL;
}

/* ------------------------------------------------------------------------ */
/* @method Bool Object.opInstanceof(Class c) */

INLINE
knh_bool_t knh_Object_opInstanceof(Ctx *ctx, Object *b, knh_type_t c)
{
	if(IS_NULL(b)) {
		return TYPE_ISNULLABLE(c);
	}
	knh_class_t scid = knh_Object_pcid(b), tcid = TYPE_TONOTNULL(c);
	return knh_class_instanceof(scid, tcid);
}

/* ------------------------------------------------------------------------ */

INLINE
knh_type_t knh_typesystem_parentType(knh_type_t t1, knh_type_t t2)
{
	knh_class_t c1 = TYPE_TONOTNULL(t1);
	knh_class_t c2 = TYPE_TONOTNULL(t2);
	if(c1 == c2) {
		if(t1 == t2) return t1;
		return CLASS_TONULLABLE(c1);
	}
	knh_class_t bcid1 = knh_tclass_bcid(c1);
	knh_class_t bcid2 = knh_tclass_bcid(c2);
	if(bcid1 == bcid2) {
		if(TYPE_ISNULLABLE(t1) || TYPE_ISNULLABLE(t2)) return CLASS_TONULLABLE(bcid1);
		return bcid1;
	}
	if(c1 == t1 && c2 == t2) {
		return CLASS_any;
	}
	return TYPE_any;
}

/* ------------------------------------------------------------------------ */
/* [coercion] */

Object *
knh_typesystem_doCoercion(Ctx *ctx, knh_type_t type, Object *v)
{
	if(IS_NULL(v)) return v;  /* @see */
	if(knh_Object_opInstanceof(ctx, v, type)) {
		return v;
	}
	//DEBUG("NEED MAPPING %s%s ==> %s", TYPEQN(type), CLASSNo(v));
	
	KNH_LOPEN(ctx, 0);
	KNH_LPUSH(ctx, v);
	MapMap *map = knh_tmapmap_find(ctx, knh_Object_pcid(v), TYPE_TONOTNULL(type));
	VM_MAP_WM(ctx, map);
//	if(TYPE_ISNULLABLE(type)) {
//		VM_MAP_WM(ctx, map);
//	}
//	else {
//		VM_MAPE_WM(ctx, map);
//	}			
	KNH_LCLOSE(ctx);
	return KNH_LVALUE(0);
}

/* ------------------------------------------------------------------------ */
/* [map] */

Object *
knh_typesystem_map(Ctx *ctx, Object *v, knh_type_t type)
{
	if(IS_NULL(v)) return v;  /* @see */
	if(knh_Object_opInstanceof(ctx, v, type)) {
		return v;
	}
	//DEBUG("NEED MAPPING %s%s ==> %s", TYPEQN(type), CLASSNo(v));
	
	KNH_LOPEN(ctx, 0);
	KNH_LPUSH(ctx, v);
	MapMap *map = knh_tmapmap_find(ctx, knh_Object_pcid(v), TYPE_TONOTNULL(type));
	if(TYPE_ISNULLABLE(type)) {
		VM_MAP_WM(ctx, map);
	}
	else {
		VM_MAPE_WM(ctx, map);
	}			
	KNH_LCLOSE(ctx);
	return KNH_LVALUE(0);
}

/* ------------------------------------------------------------------------ */

Object *
knh_typesystem_initialValue(Ctx *ctx, knh_type_t type)
{
	TODO();
	return KNH_NULL;
}


/* ------------------------------------------------------------------------ */
/* [foreach] */

Iterator *
knh_typesystem_foreach(Ctx *ctx, Object *v, knh_class_t cid)
{
	knh_class_t tcid = TYPE_TONOTNULL(cid);
	if(tcid == CLASS_any) {
		tcid = CLASS_Iterator;
	}else {
		tcid = CLASS_TOPLURAL(tcid);
	}
	
	KNH_LOPEN(ctx, 0);
	KNH_LPUSH(ctx, v);
	MapMap *map = knh_tmapmap_find(ctx, knh_Object_pcid(v), tcid);
	VM_MAP_WM(ctx, map);
	KNH_LCLOSE(ctx);
	return KNH_LVALUE(0);
}

/* ======================================================================== */
/* [Exception_type] */

Exception* new_Exception__type(Ctx *ctx, Object *value, knh_type_t spec_type)
{
	if(IS_NULL(value)) {
		return new_Exception__Nue(ctx, value);
	}
	char buf[CLASSNAME_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), "Type!!: %s%s := %s%s", CLASSQN(spec_type), CLASSQN(knh_Object_pcid(value)));
	return new_Exception__b(ctx, B(buf));
}

///* ------------------------------------------------------------------------ */
//
//INLINE
//Exception* new_Exception__Type(Ctx *ctx, knh_type_t gtype, knh_class_t cid, knh_methodn_t mn, knh_fieldn_t fn, knh_type_t type)
//{
//	char buf[CLASSNAKNH_BUFSIZ];
//	if(fn == FIELDN_NONAME) {
//		knh_snprintf(buf, sizeof(buf), "Type!!: %s%s, type=%s%s", 
//			TYPEN(gtype), TYPEQ(gtype), TYPEN(type), TYPEQ(type));
//	}else if(mn != METHODN_NONAME) {
//		if(fn == FIELDN_return) {
//			knh_snprintf(buf, sizeof(buf), "Type!!: %s%s, at return %s%s of %s.%s", 
//				TYPEN(gtype), TYPEQ(gtype), TYPEN(type), TYPEQ(type),
//				CLASSN(cid), METHODN(mn));
//		}else {
//			knh_snprintf(buf, sizeof(buf), "Type!!: %s%s, at %s.%s(%s%s %s)", 
//				TYPEN(gtype), TYPEQ(gtype), 
//				CLASSN(cid), METHODN(mn), TYPEN(type), TYPEQ(type), FIELDN(fn));
//		}
//	}else if(cid != CLASS_unknown) {
//		knh_snprintf(buf, sizeof(buf), "Type!!: %s%s, at field %s%s %s.%s", 
//			TYPEN(gtype), TYPEQ(gtype), TYPEN(type), TYPEQ(type),
//			CLASSN(cid), METHODN(mn));
//	}else {
//		knh_snprintf(buf, sizeof(buf), "Type!!: %s%s, type=%s%s", 
//			TYPEN(gtype), TYPEQ(gtype), TYPEN(type), TYPEQ(type));
//	}
//	return new_Exception(ctx, B(buf));
//}
//
//#define _new_Exception__type(ctx, t, t2) new_Exception__Type(ctx, t, CLASS_unknown, METHODN_NONAME, FIELDN_NONAME, t2)

#ifdef __cplusplus
}
#endif
