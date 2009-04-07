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
/* [constructors] */

NameSpace* new_NameSpace(Ctx *ctx, NameSpace *parent, String *nsname)
{
	knh_NameSpace_t* o = (NameSpace*)new_Object_bcid(ctx, CLASS_NameSpace, KNH_OBJECT_RAWINIT);
	//DBG2_P("@@@@@@@@ %p, %p %p", o, DP(o), DP(o)->nsname);
	KNH_INITv(DP(o)->nsname, nsname);
	KNH_INITv(DP(o)->parent, parent);
	if(IS_NULL(parent)) {
		KNH_INITv(DP(o)->name2cidDictSet, new_DictSet(ctx, KONOHA_TCLASS_SIZE));
	}
	else{
		KNH_INITv(DP(o)->name2cidDictSet, new_DictSet(ctx, 64));
		knh_NameSpace_import(ctx, o, STEXT("konoha"));
	}
	return o;
}

/* ======================================================================== */
/* [class] */

/* @ method void NameSpace.seClassTable(String name, Class c) */

void knh_NameSpace_seClassTable(Ctx *ctx, NameSpace *o, String *name, knh_class_t c)
{
	KNH_ASSERT(IS_NameSpace(o));
	KNH_ASSERT(IS_String(name));
	knh_DictSet_set(ctx, DP(o)->name2cidDictSet, name, (knh_uintptr_t)(c+1));
}

/* ------------------------------------------------------------------------ */

static
knh_bytes_t knh_NameSpace_firstType(Ctx *ctx, NameSpace *o, knh_bytes_t name, knh_type_t *type)
{
	int i, level = 1;
	for(i = 0; i < (int)name.len; i++) {
		int ch = name.buf[i];
		if(ch == '(' || ch == '<') level++;
		if(ch == ')' || ch == '>') level--;
		if((ch == ',' && level == 1) ||((ch == '>' || ch == ')') && level == 0)) {
			knh_bytes_t t = {name.buf, i};
			*type = knh_NameSpace_getType(ctx, o, t);
			if(*type == CLASS_unknown) {
				*type = TYPE_Any;
			}
			name.buf = name.buf+i+1;
			name.len = name.len-(i+1);
			return name;
		}
	}
	return STEXT("");
}


/* ------------------------------------------------------------------------ */
/* @ method Class NameSpace.geClassTable(String name) */

knh_class_t knh_NameSpace_geClassTable(Ctx *ctx, NameSpace *o, knh_bytes_t name)
{
	if(knh_bytes_equals(name, STEXT("Script")) && IS_NOTNULL(DP(o)->script)) {
		return knh_Object_cid(DP(o)->script);
	}
	if(knh_bytes_equals(name, STEXT("This"))) {
		return CLASS_This;
	}

	{
		NameSpace *ns = o;
		while(1) {
			knh_uintptr_t cid = knh_DictSet_get__b(DP(ns)->name2cidDictSet, name);
			if(cid > 0) return (knh_class_t)(cid-1);
			if(IS_NULL(DP(ns)->parent)) {
				goto L_GENPART;
			}
			ns = DP(ns)->parent;
		}
	}

	L_GENPART:
	if(o != knh_rootNameSpace) {
		knh_index_t loc = knh_bytes_index(name, '<');
		if(loc > 0) {
			knh_class_t bcid = knh_NameSpace_geClassTable(ctx, o, knh_bytes_first(name, loc));
			KNH_ASSERT_cid(bcid);
			if(!knh_Class_isGenerics(bcid)) return bcid;
			knh_class_t p1 = CLASS_Any, p2 = ctx->share->ClassTable[bcid].p2;
			name = knh_NameSpace_firstType(ctx, o, knh_bytes_last(name, loc+1), &p1);
			knh_NameSpace_firstType(ctx, o, name, &p2);
			return knh_class_Generics(ctx, bcid, CLASS_type(p1), CLASS_type(p2));
		}
		loc = knh_bytes_index(name, '(');
		if(loc > 0) {
			knh_type_t r0 = knh_NameSpace_getType(ctx, o, knh_bytes_first(name, loc));
			knh_type_t t1 = TYPE_void, t2 = TYPE_void, t3 = TYPE_void;
			name = knh_NameSpace_firstType(ctx, o, knh_bytes_last(name, loc+1), &t1);
			name = knh_NameSpace_firstType(ctx, o, name, &t2);
			knh_NameSpace_firstType(ctx, o, name, &t3);
			return knh_class_Closure(ctx, r0, t1, t2, t3);
		}
	}
	return CLASS_unknown;
}

/* ------------------------------------------------------------------------ */

void knh_NameSpace_setLocalName(Ctx *ctx, NameSpace *o, knh_class_t cid)
{
	KNH_ASSERT(IS_NameSpace(o));
	KNH_ASSERT_cid(cid);
	knh_DictSet_set(ctx, DP(o)->name2cidDictSet, ctx->share->ClassTable[cid].sname, (knh_uintptr_t)(cid+1));
}

/* ------------------------------------------------------------------------ */

char* knh_Context_CLASSN(Ctx *ctx, knh_class_t cid)
{
	KNH_ASSERT_cid(cid);
	String *name = ctx->share->ClassTable[cid].lname;
	if(knh_String_startsWith(name, STEXT("konoha."))) {
		return knh_String_tochar(ctx->share->ClassTable[cid].sname);
	}
	else {
		knh_uintptr_t cid2 = knh_DictSet_get__b(DP(ctx->ns)->name2cidDictSet, knh_String_tobytes(ctx->share->ClassTable[cid].sname));
		if(cid2 > 0 && cid == cid2 - 1) {
			return knh_String_tochar(ctx->share->ClassTable[cid].sname);
		}
		return CLASSN(cid);
	}
}

#define _CTXCLASSN(cid)     knh_Context_CLASSN(ctx,cid)
#define _CTXTYPEQN(cid)     knh_Context_CLASSN(ctx,CLASS_type(cid)), TYPEQ(cid)

/* ------------------------------------------------------------------------ */

void knh_NameSpace_import(Ctx *ctx, NameSpace *o, knh_bytes_t p)
{
	size_t i;
	if(p.buf[p.len-1] == '.') {
		p.len--;
	}
	for(i = 0; i < ctx->share->ClassTableSize; i++) {
		if(ctx->share->ClassTable[i].cspec == NULL) continue;
		KNH_ASSERT(IS_bString(ctx->share->ClassTable[i].lname));
		if(knh_class_isPrivate(i)) continue;
		knh_bytes_t cname = knh_String_tobytes(ctx->share->ClassTable[i].lname);
		if(knh_bytes_startsWith(cname, p) && cname.buf[p.len] == '.' && isupper(cname.buf[p.len+1])) {
			knh_NameSpace_setLocalName(ctx, o, (knh_class_t)i);
		}
	}
}

/* ======================================================================== */
/* [type] */

static
knh_bool_t knh_bytes_isNotNullType(knh_bytes_t t)
{
	if(t.len > 2 && t.buf[t.len-1] == '!' && t.buf[t.len-2] != '!') {
		return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

knh_type_t knh_NameSpace_getType(Ctx *ctx, NameSpace *o, knh_bytes_t name)
{
	if(name.len == 4 &&
		name.buf[0] == 'v' && name.buf[1] == 'o' &&
		name.buf[2] == 'i' && name.buf[3] == 'd') return TYPE_void;

	if(knh_bytes_isNotNullType(name)) {
		knh_class_t cid;
		name.len--;
		cid = knh_NameSpace_geClassTable(ctx, o, name);
		return (cid == CLASS_unknown) ? cid : NNTYPE_cid(cid);
	}
	else {
		return knh_NameSpace_geClassTable(ctx, o, name);
	}
}

/* ======================================================================== */
/* [tag] */

knh_class_t knh_tclass_classURN(Ctx *ctx, knh_class_t bcid, knh_bytes_t urn)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), KNH_CLASSSPEC_FMT, CLASSN(bcid), urn.buf);
	knh_class_t cid = knh_NameSpace_geClassTable(ctx, knh_rootNameSpace, B(buf));
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
//	knh_class_t cid = knh_NameSpace_geClassTable(ctx, o, B(buf));
//	if(cid == CLASS_unknown) {
//		if(bcid == CLASS_Int) {
//			knh_snprintf(buf, sizeof(buf), "Float:%s", tag.buf);
//			cid = knh_NameSpace_geClassTable(ctx, o, B(buf));
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
	knh_DictSet_set(ctx, DP(o)->func2cidDictSet, new_String__mn(ctx, mn), (knh_uintptr_t)(c+1));
}

/* ------------------------------------------------------------------------ */

knh_class_t
knh_NameSpace_getFuncClass(Ctx *ctx, NameSpace *o, knh_bytes_t funcname)
{
	if(IS_NOTNULL(DP(o)->func2cidDictSet)) {
		knh_uintptr_t cid = knh_DictSet_get__b(DP(o)->func2cidDictSet, funcname);
		if(cid != 0) {
			return (knh_class_t)(cid-1);
		}
	}
	return CLASS_unknown; /* if it isn't found */
}

/* ======================================================================== */
/* [const] */

knh_bool_t
knh_NameSpace_existsConst(Ctx *ctx, NameSpace *o, knh_bytes_t name)
{
	if(knh_bytes_index(name, '_') == -1) {
		if(IS_NOTNULL(DP(o)->lconstDictMap)) {
			return (knh_DictMap_index__b(DP(o)->lconstDictMap, name) != -1);
		}
		return 0;
	}
	return konoha_existsConst(ctx, name);
}

/* ------------------------------------------------------------------------ */

void knh_NameSpace_addConst(Ctx *ctx, NameSpace *o, String *name, Object *value)
{
	KNH_ASSERT(IS_NameSpace(o));
	KNH_ASSERT(IS_String(name));
	if(knh_bytes_index(knh_String_tobytes(name), '_') == -1) {
		if(IS_NULL(DP(o)->lconstDictMap)) {
			KNH_SETv(ctx, DP(o)->lconstDictMap, new_DictMap0(ctx, 16));
		}
		knh_DictMap_set(ctx, DP(o)->lconstDictMap, name, value);
	}
	else {
		konoha_addConst(ctx, name, value);
	}
}


/* ------------------------------------------------------------------------ */

Object*
knh_NameSpace_getConst(Ctx *ctx, NameSpace *o, knh_bytes_t name)
{
	if(knh_bytes_index(name, '_') == -1) {
		if(IS_NOTNULL(DP(o)->lconstDictMap)) {
			return knh_DictMap_get__b(ctx,  DP(o)->lconstDictMap, name);
		}
		return (Object*)KNH_NULL;
	}
	return konoha_getConst(ctx, name);
}


/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
