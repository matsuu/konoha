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
/* [prototype] */

knh_class_t knh_system_loadEnum(Ctx *ctx, knh_bytes_t urn);
knh_class_t knh_system_loadUnit(Ctx *ctx, knh_bytes_t urn);
knh_class_t knh_system_loadVocabulary(Ctx *ctx, knh_bytes_t urn);

/* ======================================================================== */
/* [structs] */

void knh_NameSpace_struct_init(Ctx *ctx, knh_NameSpace_struct *b, int init, Object *cs)
{
	KNH_INITv(b->parent, KNH_NULL);
	KNH_INITv(b->nsname, KNH_NULL);
	KNH_INITv(b->script, KNH_NULL);
	KNH_INITv(b->imports, KNH_NULL);
	KNH_INITv(b->lconstDictMap, KNH_NULL);
	KNH_INITv(b->name2cidDictSet, KNH_NULL);
	KNH_INITv(b->tag2urnDictMap, KNH_NULL);
	KNH_INITv(b->func2cidDictSet, KNH_NULL);
	b->dlhdr = NULL;
	b->ftraverse = NULL;
}

/* ------------------------------------------------------------------------ */

#define _knh_NameSpace_struct_copy  NULL

/* ------------------------------------------------------------------------ */

#define _knh_NameSpace_struct_compare NULL

/* ------------------------------------------------------------------------ */

void knh_NameSpace_struct_traverse(Ctx *ctx, knh_NameSpace_struct *b, f_traverse ftr)
{
	ftr(ctx, UP(b->parent));
	ftr(ctx, UP(b->nsname));
	ftr(ctx, UP(b->script));
	ftr(ctx, UP(b->imports));
	ftr(ctx, UP(b->lconstDictMap));
	ftr(ctx, UP(b->name2cidDictSet));
	ftr(ctx, UP(b->tag2urnDictMap));
	ftr(ctx, UP(b->func2cidDictSet));
	if(b->ftraverse != NULL) {
		b->ftraverse(ctx, ftr);
	}
	if(IS_SWEEP(ftr)) {
		if(b->dlhdr != NULL) {
			knh_dlclose(b->dlhdr);
			b->dlhdr = NULL;
		}
	}
}

/* ======================================================================== */
/* [constructors] */

NameSpace* new_NameSpace(Ctx *ctx, NameSpace *parent, String *nsname)
{
	knh_NameSpace_t* o =
		(NameSpace*)new_Object_malloc(ctx, FLAG_NameSpace, CLASS_NameSpace, sizeof(knh_NameSpace_struct));
	knh_NameSpace_struct_init(ctx, DP(o), 0, NULL);
	KNH_SETv(ctx, DP(o)->nsname, nsname);
	if(IS_NULL(parent)) {
		KNH_SETv(ctx, DP(o)->name2cidDictSet, new_DictSet(ctx, KONOHA_TCLASS_SIZE));
	}
	else{
		KNH_SETv(ctx, DP(o)->parent, parent);
		KNH_SETv(ctx, DP(o)->name2cidDictSet, new_DictSet(ctx, 64));
		knh_NameSpace_import(ctx, o, STEXT("konoha"));
	}
	return o;
}


/* ======================================================================== */
/* [class] */

/* @ method void NameSpace.setClass(String name, Class c) */

void knh_NameSpace_setClass(Ctx *ctx, NameSpace *o, String *name, knh_class_t c)
{
	KNH_ASSERT(IS_NameSpace(o));
	KNH_ASSERT(IS_String(name));
	knh_DictSet_set(ctx, DP(o)->name2cidDictSet, name, (knh_uint_t)(c+1));
}

/* ------------------------------------------------------------------------ */
/* @ method Class NameSpace.getClass(String name) */

knh_class_t knh_NameSpace_getClass(Ctx *ctx, NameSpace *o, knh_bytes_t name)
{
	if(knh_bytes_equals(name, STEXT("Script")) && IS_bScript(DP(o)->script)) {
		return knh_Object_cid(DP(o)->script);
	}
	NameSpace *ns = o;
	L_TAIL:;
	//DEMO_DUMP(ctx, ns->name2cidDictSet, KNH_NULL, "ns");
	knh_uint_t cid = knh_DictSet_get__b(DP(ns)->name2cidDictSet, name);
	//DEBUG("**** name='%s', name.len=%d cid=%d", name.buf, name.len, cid);
	if(cid > 0) return (knh_class_t)(cid-1);
	if(IS_NULL(DP(ns)->parent)) {
		return CLASS_unknown;
	}
	ns = DP(ns)->parent;
	goto L_TAIL;
}

/* ------------------------------------------------------------------------ */

void knh_NameSpace_setLocalName(Ctx *ctx, NameSpace *o, knh_class_t cid)
{
	KNH_ASSERT(IS_NameSpace(o));
	DEBUG_ASSERT_cid(cid);
	knh_DictSet_set(ctx, DP(o)->name2cidDictSet, knh_tClass[cid].sname, (knh_uint_t)(cid+1));
}

/* ------------------------------------------------------------------------ */

char* knh_Context_CLASSN(Ctx *ctx, knh_class_t cid)
{
	DEBUG_ASSERT_cid(cid);
	String *name = knh_tClass[cid].lname;
	if(knh_String_startsWith(name, STEXT("konoha."))) {
		return knh_String_tochar(knh_tClass[cid].sname);
	}
	else {
		knh_uint_t cid2 = knh_DictSet_get__b(DP(ctx->ns)->name2cidDictSet, knh_String_tobytes(knh_tClass[cid].sname));
		if(cid2 > 0 && cid == cid2 - 1) {
			return knh_String_tochar(knh_tClass[cid].sname);
		}
		return CLASSN(cid);
	}
}

#define _CTXCLASSN(cid)     knh_Context_CLASSN(ctx,cid)
#define _CTXTYPEQN(cid)     knh_Context_CLASSN(ctx,TYPE_UNMASK_NN(cid)), TYPEQ(cid)

/* ------------------------------------------------------------------------ */

void
knh_NameSpace_import(Ctx *ctx, NameSpace *o, knh_bytes_t p)
{
	int i;
	if(p.buf[p.len-1] == '.') {
		p.len--;
	}
	for(i = 0; i < knh_tClass_size(); i++) {
		if(knh_tClass[i].cspec == NULL) continue;
		KNH_ASSERT(IS_bString(knh_tClass[i].lname));
		if(knh_class_isPrivate(i)) continue;
		knh_bytes_t cname = knh_String_tobytes(knh_tClass[i].lname);
		if(knh_bytes_startsWith(cname, p) && cname.buf[p.len] == '.' && isupper(cname.buf[p.len+1])) {
			knh_NameSpace_setLocalName(ctx, o, (knh_class_t)i);
		}
	}
}

/* ======================================================================== */
/* [type] */

knh_type_t knh_NameSpace_getType(Ctx *ctx, NameSpace *o, knh_bytes_t name)
{
	if(name.len == 4 &&
		name.buf[0] == 'v' && name.buf[1] == 'o' &&
		name.buf[2] == 'i' && name.buf[3] == 'd') return TYPE_void;

	if(knh_bytes_isNotNullType(name)) {
		knh_class_t cid;
		name.len--;
		cid = knh_NameSpace_getClass(ctx, o, name);
		return (cid == CLASS_unknown) ? cid : CLASS_TONNTYPE(cid);
	}
	else {
		return knh_NameSpace_getClass(ctx, o, name);
	}
}

/* ======================================================================== */
/* [tag] */

knh_class_t knh_tclass_classURN(Ctx *ctx, knh_class_t bcid, knh_bytes_t urn)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), KNH_CLASSSPEC_FMT, CLASSN(bcid), urn.buf);
	knh_class_t cid = knh_NameSpace_getClass(ctx, knh_rootNameSpace, B(buf));
	if(cid == CLASS_unknown) {
		cid = knh_tclass_loadURN(ctx, bcid, urn);
	}
	return cid;
}

/* ------------------------------------------------------------------------ */

knh_class_t knh_tclass_loadURN(Ctx *ctx, knh_class_t bcid, knh_bytes_t urn)
{
//	switch(bcid) {
//	case CLASS_Int:
//		return knh_system_loadEnum(ctx, urn);
//	case CLASS_Float:
//		return knh_system_loadUnit(ctx, urn);
//	case CLASS_String:
//		return knh_system_loadVocabulary(ctx, urn);
//	}
	TODO();
	DBG2_P("unknown bcid=%d,'%s'", bcid, CLASSN(bcid));
	return bcid;
}

/* ------------------------------------------------------------------------ */

knh_type_t knh_NameSpace_tagcid(Ctx *ctx, NameSpace *o, knh_class_t bcid, knh_bytes_t tag)
{
	TODO();
	//	char buf[CLASSNAME_BUFSIZ];
//	DBG2_P("%s:'%s'", CLASSN(bcid), tag.buf);
//	knh_snprintf(buf, sizeof(buf), "%s:%s", CLASSN(bcid), tag.buf);
//	knh_class_t cid = knh_NameSpace_getClass(ctx, o, B(buf));
//	if(cid == CLASS_unknown) {
//		if(bcid == CLASS_Int) {
//			knh_snprintf(buf, sizeof(buf), "Float:%s", tag.buf);
//			cid = knh_NameSpace_getClass(ctx, o, B(buf));
//		}
//	}
//	return cid;
	return CLASS_unknown;
}

/* ======================================================================== */
/* [func] */

void knh_NameSpace_setFuncClass(Ctx *ctx, NameSpace *o, knh_methodn_t mn, knh_class_t c)
{
	KNH_ASSERT(IS_NameSpace(o));
	if(IS_NULL(DP(o)->func2cidDictSet)) {
		KNH_SETv(ctx, DP(o)->func2cidDictSet, new_DictSet(ctx, 16));
	}
	knh_DictSet_set(ctx, DP(o)->func2cidDictSet, new_String__mn(ctx, mn), (knh_uint_t)(c+1));
}

/* ------------------------------------------------------------------------ */

knh_class_t
knh_NameSpace_getFuncClass(Ctx *ctx, NameSpace *o, knh_bytes_t funcname)
{
	if(IS_NOTNULL(DP(o)->func2cidDictSet)) {
		knh_uint_t cid = knh_DictSet_get__b(DP(o)->func2cidDictSet, funcname);
		if(cid != 0) {
			return (knh_class_t)(cid-1);
		}
	}
	return CLASS_unknown; /* if it isn't found */
}

/* ======================================================================== */
/* [const] */

void knh_NameSpace_addLocalConst(Ctx *ctx, NameSpace *o, String *name, Object *value)
{
	KNH_ASSERT(IS_NameSpace(o));
	KNH_ASSERT(IS_String(name));
	if(IS_NULL(DP(o)->lconstDictMap)) {
		KNH_SETv(ctx, DP(o)->lconstDictMap, new_DictMap(ctx, 16));
	}
	knh_DictMap_set(ctx, DP(o)->lconstDictMap, name, value);
}

/* ------------------------------------------------------------------------ */

knh_bool_t
knh_NameSpace_existsLocalConst(Ctx *ctx, NameSpace *o, knh_bytes_t name)
{
	if(IS_NOTNULL(DP(o)->lconstDictMap)) {
		return (knh_DictMap_index__b(DP(o)->lconstDictMap, name) != -1);
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

Object*
knh_NameSpace_getLocalConst(Ctx *ctx, NameSpace *o, knh_bytes_t name)
{
	if(IS_NOTNULL(DP(o)->lconstDictMap)) {
		return knh_DictMap_get__b(ctx, DP(o)->lconstDictMap, name);
	}
	return (Object*)KNH_NULL;
}

/* ======================================================================== */
/* [loaded] */

void knh_NameSpace_loaded(Ctx *ctx, NameSpace *o, knh_fileid_t fileid)
{
	KNH_ASSERT(IS_NameSpace(o));
	if(IS_NULL(DP(o)->lconstDictMap)) {
		KNH_SETv(ctx, DP(o)->lconstDictMap, new_DictMap(ctx, 16));
	}
	char buf[80];
	knh_snprintf(buf, sizeof(buf), "_LOADED_%d", (int)fileid);
	knh_DictMap_set(ctx, DP(o)->lconstDictMap, new_String(ctx, B(buf), NULL), UP(knh_tfileid_name(fileid)));
}

/* ------------------------------------------------------------------------ */

knh_bool_t
knh_NameSpace_isLoaded(Ctx *ctx, NameSpace *o, knh_fileid_t fileid)
{
	if(IS_NOTNULL(DP(o)->lconstDictMap)) {
		char buf[80];
		knh_snprintf(buf, sizeof(buf), "_LOADED_%d", (int)fileid);
		return (knh_DictMap_index__b(DP(o)->lconstDictMap, B(buf)) != -1);
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
