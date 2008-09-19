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

knh_bool_t knh_class_instanceof(knh_class_t scid, knh_class_t tcid)
{
	DEBUG_ASSERT_cid(scid);
	DEBUG_ASSERT_cid(tcid);

	//DBG2_P("@@@@@@@@@ %s %s", CLASSN(knh_tClass[scid].bcid), CLASSN(tcid));
	if(knh_tClass[scid].bcid == tcid /* Int:km Int */
			|| scid == tcid
			|| tcid == CLASS_Object  /* Int    Object */
			|| tcid == CLASS_Any ) return 1;   /* Any */

	if(knh_tClass[scid].bcid == knh_tClass[tcid].bcid && knh_tClass_isPMZ(scid) && knh_tClass_isPMZ(tcid)) {
		return knh_class_instanceof(knh_tClass[scid].p1, knh_tClass[tcid].p1) &&
			knh_class_instanceof(knh_tClass[scid].p2, knh_tClass[tcid].p2);
	}

	while(scid != CLASS_Object) {
		ClassMap *cmap = knh_tClass[scid].cmap;
		int i;
		for(i = 0; i < DP(cmap)->size; i++) {
			Mapper *mpr = DP(cmap)->maplist[i];
			if(DP(mpr)->tcid == tcid && DP(mpr)->flag == KNH_FLAG_MMF_INTERFACE) return 1;
		}
		scid = knh_tClass[scid].supcid;
		if(scid == tcid) return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */
/* @method Boolean Object.opInstanceof(Class! c) */

//knh_bool_t knh_Object_opInstanceof(Ctx *ctx, Object *o, knh_class_t c)
//{
//	return knh_class_instanceof(o->h.cid, c);
//}

METHOD knh__Object_opInstanceof(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_class_instanceof(ARG_Object_cid(sfp[0]), ARG_cid(sfp[1])));
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_Object_opTypeOf(Ctx *ctx, Object *o, knh_type_t t)
{
	if(IS_NULL(o)) {
		return TYPE_ISNULLABLE(t);
	}
	return knh_class_instanceof(o->h.cid, TYPE_UNMASK(t));
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_class_isSynonym(Ctx *ctx, knh_class_t scid, knh_class_t tcid)
{
	DEBUG_ASSERT_cid(scid);
	DEBUG_ASSERT_cid(tcid);
	return 0;
}

/* ------------------------------------------------------------------------ */

//INLINE
//knh_type_t knh_typesystem_parentType(knh_type_t t1, knh_type_t t2)
//{
//	knh_class_t c1 = TYPE_TONOTNULL(t1);
//	knh_class_t c2 = TYPE_TONOTNULL(t2);
//	if(c1 == c2) {
//		if(t1 == t2) return t1;
//		return CLASS_TONULLABLE(c1);
//	}
//	knh_class_t bcid1 = knh_tclass_bcid(c1);
//	knh_class_t bcid2 = knh_tclass_bcid(c2);
//	if(bcid1 == bcid2) {
//		if(TYPE_ISNULLABLE(t1) || TYPE_ISNULLABLE(t2)) return CLASS_TONULLABLE(bcid1);
//		return bcid1;
//	}
//	if(c1 == t1 && c2 == t2) {
//		return CLASS_Any;
//	}
//	return TYPE_any;
//}

/* ------------------------------------------------------------------------ */
/* [coercion] */

Object * knh_Object_opAs(Ctx *ctx, Object *o, knh_class_t tcid)
{
	DEBUG_ASSERT_cid(tcid);
	if(IS_NULL(o)) {
		return o;  /* @see */
	}
	else {
		knh_class_t scid = knh_Object_cid(o);
		if(scid == tcid || knh_tClass[scid].bcid == tcid || knh_class_instanceof(scid, tcid)) {
			return o;
		}
		else if(knh_tClass[tcid].bcid == scid) {
			if(IS_String(o)) {
				String *s = (String*)o;
				return UP(new_StringX(ctx, tcid, knh_String_tobytes(s), s));
			}
			return o;
		}
		else {
			KNH_LOPEN(ctx, 0);
			DBG2_P("COERCION %s -> %s", CLASSN(scid), CLASSN(tcid));
			KNH_LPUSH(ctx, o);
			VM_MAP(ctx, tcid);
			o = ctx->ebp[0].o;
			KNH_LCLOSE(ctx);
			return o;
		}
	}
}

/* ------------------------------------------------------------------------ */

Object *knh_Object_opAs__type(Ctx *ctx, Object *o, knh_type_t reqt, Object *def)
{
	knh_class_t tcid = TYPE_UNMASK_NN(reqt);
	DEBUG_ASSERT_cid(tcid);
	if(IS_NULL(o)) {
		return def;
	}
	else {
		knh_class_t scid = knh_Object_cid(o);
		if(scid == tcid || knh_tClass[scid].bcid == tcid || knh_class_instanceof(scid, tcid)) {
			return o;
		}
		else {
			KNH_LOPEN(ctx, 0);
			DBG2_P("COERCION %s -> %s", CLASSN(scid), CLASSN(tcid));
			KNH_LPUSH(ctx, o);
			VM_MAP(ctx, tcid);
			o = ctx->ebp[0].o;
			KNH_LCLOSE(ctx);
			if(IS_NOTNULL(o) || TYPE_ISNULLABLE(reqt)) {
				return o;
			}
			else {
				return def;
			}
		}
	}
}

///* ------------------------------------------------------------------------ */
///* [foreach] */
//
//Iterator *
//knh_typesystem_foreach(Ctx *ctx, Object *v, knh_class_t cid)
//{
//	knh_class_t tcid = TYPE_TONOTNULL(cid);
//	if(tcid == CLASS_Any) {
//		tcid = CLASS_Iterator;
//	}else {
//		tcid = CLASS_TOPLURAL(tcid);
//	}
//
//	KNH_LOPEN(ctx, 0);
//	KNH_LPUSH(ctx, v);
//	Mapper *map = knh_tMapper_find(ctx, knh_Object_pcid(v), tcid);
//	VM_MAP_WM(ctx, map);
//	KNH_LCLOSE(ctx);
//	return KNH_LOCALn(0);
//}

/* ======================================================================== */
/* [Exception_type] */

Exception* new_Exception__type(Ctx *ctx, Object *value, knh_type_t spec_type)
{
	if(IS_NULL(value)) {
		return new_Exception__Nue(ctx, (Nue*)value);
	}
	else {
		char buf[CLASSNAME_BUFSIZ];
		knh_snprintf(buf, sizeof(buf), "Type!!: req=%s given=%s", CLASSN(TYPE_UNMASK(spec_type)), CLASSN(knh_Object_cid(value)));
		return new_Exception__s(ctx, buf);
	}
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

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
