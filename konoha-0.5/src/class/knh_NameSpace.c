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
/* [prototype] */

knh_class_t knh_system_loadEnum(Ctx *ctx, knh_bytes_t urn);
knh_class_t knh_system_loadUnit(Ctx *ctx, knh_bytes_t urn);
knh_class_t knh_system_loadVocabulary(Ctx *ctx, knh_bytes_t urn);

/* ======================================================================== */
/* [constructors] */

NameSpace* new_NameSpace(Ctx *ctx, String *nsname)
{
	knh_NameSpace_t* o = (NameSpace*)new_Object_bcid(ctx, CLASS_NameSpace, KNH_OBJECT_RAWINIT);
	KNH_INITv(DP(o)->nsname, nsname);
	return o;
}

/* ======================================================================== */
/* [imported namespace] */

void knh_NameSpace_importNameSpace(Ctx *ctx, NameSpace *ns, NameSpace *other)
{
	if(IS_NULL(DP(ns)->importedNameSpaces)) {
		KNH_SETv(ctx, DP(ns)->importedNameSpaces, new_Array0(ctx, 0));
	}
	knh_Array_add(ctx, DP(ns)->importedNameSpaces, UP(other));
}

/* ------------------------------------------------------------------------ */

static
NameSpace *knh_NameSpace_getImportedNameSpace(Ctx *ctx, NameSpace *ns, size_t n)
{
	if(IS_NULL(DP(ns)->importedNameSpaces)) {
		return NULL;
	}
	if(n < knh_Array_size(DP(ns)->importedNameSpaces)) {
		return (NameSpace*)knh_Array_n(DP(ns)->importedNameSpaces, n);
	}
	return NULL;
}

/* ======================================================================== */
/* [NameSpace] */

Script *knh_NameSpace_getScript(Ctx *ctx, NameSpace *ns)
{
	if(IS_NULL(DP(ns)->script)) {
		KNH_SETv(ctx, DP(ns)->script, new_Script(ctx, knh_String_tobytes(DP(ns)->nsname)));
	}
	return DP(ns)->script;
}

/* ======================================================================== */
/* [class] */

knh_class_t konoha_getcid(Ctx *ctx, knh_bytes_t lname)
{
	knh_uintptr_t cid = knh_DictSet_get__b(DP(ctx->sys)->ClassNameDictSet, lname);
	if(cid > 0) return (knh_class_t)(cid-1);
	return CLASS_unknown;
}

/* ------------------------------------------------------------------------ */

KNHAPI(knh_class_t) konoha_findcid(Ctx *ctx, knh_bytes_t lname)
{
	knh_class_t cid = konoha_getcid(ctx, lname);
	if(cid != CLASS_unknown) {
		return cid;
	}
	if(knh_bytes_endsWith(lname, STEXT("[]"))) {
		lname.len -= 2;
		cid = konoha_getcid(ctx, lname);
		if(cid == CLASS_unknown || knh_class_isPrivate(cid)) {
			return CLASS_Array;
		}
		return knh_class_Array(ctx, cid);
	}
	if(knh_bytes_endsWith(lname, STEXT(".."))) {
		lname.len -= 2;
		cid = konoha_getcid(ctx, lname);
		if(cid == CLASS_unknown || knh_class_isPrivate(cid)) {
			return CLASS_Iterator;
		}
		return knh_class_Iterator(ctx, cid);
	}
	if(lname.buf[lname.len-1] == '}') {
		return konoha_findcidx(ctx, lname);
	}
	return cid;
}

/* ------------------------------------------------------------------------ */

void knh_NameSpace_setcid(Ctx *ctx, NameSpace *o, String *name, knh_class_t c)
{
	DBG2_ASSERT(IS_NameSpace(o));
	DBG2_ASSERT(IS_String(name));
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
			*type = knh_NameSpace_gettype(ctx, o, t, 0);
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

void knh_NameSpace_setLocalName(Ctx *ctx, NameSpace *o, knh_class_t cid)
{
	KNH_ASSERT(IS_NameSpace(o));
	KNH_ASSERT_cid(cid);
	knh_DictSet_set(ctx, DP(o)->name2cidDictSet, ctx->share->ClassTable[cid].sname, (knh_uintptr_t)(cid+1));
}

/* ------------------------------------------------------------------------ */

knh_class_t knh_NameSpace_getcid(Ctx *ctx, NameSpace *o, knh_bytes_t name)
{
	if(knh_bytes_equals(name, STEXT("This"))) return CLASS_This;
	if(knh_bytes_equals(name, STEXT("Script"))) {
		Script *scr = knh_NameSpace_getScript(ctx, o);
		return knh_Object_cid(scr);
	}

	{
		size_t i = 0;
		knh_uintptr_t cididx = knh_DictSet_get__b(DP(o)->name2cidDictSet, name);
		if(cididx > 0) return (knh_class_t)(cididx-1);
		NameSpace *ins = NULL;
		while((ins = knh_NameSpace_getImportedNameSpace(ctx, o, i++)) != NULL) {
			cididx = knh_DictSet_get__b(DP(ins)->name2cidDictSet, name);
			if(cididx > 0) return (knh_class_t)(cididx-1);
		}
	}

	{
		knh_class_t cid = konoha_getcid(ctx, name);
		if(cid != CLASS_unknown) {
			knh_NameSpace_setLocalName(ctx, o, cid);
			return cid;
		}
	}

	{
		knh_index_t loc = knh_bytes_index(name, '<');
		if(loc > 0) {
			knh_class_t bcid = knh_NameSpace_getcid(ctx, o, knh_bytes_first(name, loc));
			KNH_ASSERT_cid(bcid);
			if(!knh_Class_isGenerics(bcid)) return bcid;
			knh_class_t p1 = CLASS_Any, p2 = ctx->share->ClassTable[bcid].p2;
			knh_bytes_t nsub = knh_NameSpace_firstType(ctx, o, knh_bytes_last(name, loc+1), &p1);
			knh_NameSpace_firstType(ctx, o, nsub, &p2);
			knh_class_t cid = knh_class_Generics(ctx, bcid, CLASS_type(p1), CLASS_type(p2));
			if(cid != CLASS_unknown) {
				knh_NameSpace_setcid(ctx, o, new_String(ctx, name, NULL), cid);
				knh_NameSpace_setLocalName(ctx, o, cid);
			}
			return cid;
		}

		loc = knh_bytes_index(name, '(');
		if(loc > 0) {
			knh_type_t r0 = knh_NameSpace_gettype(ctx, o, knh_bytes_first(name, loc), 0);
			knh_type_t t1 = TYPE_void, t2 = TYPE_void, t3 = TYPE_void;
			knh_bytes_t nsub = knh_NameSpace_firstType(ctx, o, knh_bytes_last(name, loc+1), &t1);
			name = knh_NameSpace_firstType(ctx, o, nsub, &t2);
			knh_NameSpace_firstType(ctx, o, nsub, &t3);
			knh_class_t cid = knh_class_Closure(ctx, r0, t1, t2, t3);
			if(cid != CLASS_unknown) {
				knh_NameSpace_setcid(ctx, o, new_String(ctx, name, NULL), cid);
				knh_NameSpace_setLocalName(ctx, o, cid);
			}
			return cid;
		}
	}
	return CLASS_unknown;
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
		knh_uintptr_t cid2 =
			knh_DictSet_get__b(DP(ctx->ns)->name2cidDictSet, knh_String_tobytes(ctx->share->ClassTable[cid].sname));
		if(cid2 > 0 && cid == cid2 - 1) {
			return knh_String_tochar(ctx->share->ClassTable[cid].sname);
		}
		return CLASSN(cid);
	}
}

#define _CTXCLASSN(cid)     knh_Context_CLASSN(ctx,cid)
#define _CTXTYPEQN(cid)     knh_Context_CLASSN(ctx,CLASS_type(cid)), TYPEQ(cid)

/* ------------------------------------------------------------------------ */

void knh_NameSpace_importClass(Ctx *ctx, NameSpace *o, knh_bytes_t pkgname)
{
	size_t i;
	if(pkgname.buf[pkgname.len-1] == '.') {
		pkgname.len--;
	}
	for(i = 0; i < KNH_TCLASS_SIZE; i++) {
		if(ctx->share->ClassTable[i].sname == NULL) continue;
		KNH_ASSERT(IS_bString(ctx->share->ClassTable[i].lname));
		if(knh_class_isPrivate(i)) continue;
		knh_bytes_t cname = knh_String_tobytes(ctx->share->ClassTable[i].lname);
		if(knh_bytes_startsWith(cname, pkgname)
				&& cname.buf[pkgname.len] == '.'
					&& isupper(cname.buf[pkgname.len+1])) {
			knh_NameSpace_setLocalName(ctx, o, (knh_class_t)i);
		}
	}
}

/* ======================================================================== */
/* [type] */

knh_type_t knh_NameSpace_gettype(Ctx *ctx, NameSpace *ns, knh_bytes_t name, int isNullable)
{
	if(name.buf[0] == 'v') {
		if(name.len == 4 && name.buf[1] == 'o' &&
			name.buf[2] == 'i' && name.buf[3] == 'd') return TYPE_void;
		if(name.len == 3 && name.buf[1] == 'a' && name.buf[2] == 'r') return TYPE_var;
	}

	if(name.len > 2 && name.buf[name.len-1] == '!') {
		name.len--;
		isNullable = 0;
	}

	if(name.len > 2 && name.buf[name.len-1] == '?') {
		name.len--;
		isNullable = 1;
	}

	{
		knh_class_t cid = knh_NameSpace_getcid(ctx, ns, name);
		if(cid != CLASS_unknown && !isNullable) return NNTYPE_cid(cid);
		return cid;
	}
}

/* ======================================================================== */
/* [const] */

Object *
knh_NameSpace_getConstNULL(Ctx *ctx, NameSpace *ns, knh_bytes_t name)
{
	knh_index_t idx = knh_bytes_index(name, '.');
	if(idx > 0) {
		knh_class_t cid = knh_NameSpace_getcid(ctx, ns, knh_bytes_first(name, idx));
		if(cid == CLASS_unknown) return NULL;
		return konoha_getClassConstNULL(ctx, cid, knh_bytes_last(name, idx+1));
	}
	if(knh_bytes_index(name, '_') == -1) {
		if(IS_NOTNULL(DP(ns)->lconstDictMap)) {
			idx = knh_DictMap_index__b(DP(ns)->lconstDictMap, name);
			if(idx != -1) return knh_DictMap_valueAt(DP(ns)->lconstDictMap, idx);
		}
		size_t i = 0;
		NameSpace *ins = NULL;
		while((ins = knh_NameSpace_getImportedNameSpace(ctx, ns, i++)) != NULL) {
			if(IS_NOTNULL(DP(ins)->lconstDictMap)) {
				idx = knh_DictMap_index__b(DP(ins)->lconstDictMap, name);
				if(idx != -1) return knh_DictMap_valueAt(DP(ins)->lconstDictMap, idx);
			}
		}
		return NULL;
	}
	return konoha_getClassConstNULL(ctx, CLASS_Any, name);
}

/* ------------------------------------------------------------------------ */

void knh_NameSpace_addConst(Ctx *ctx, NameSpace *ns, String *name, Object *value)
{
	KNH_ASSERT(IS_NameSpace(ns));
	KNH_ASSERT(IS_String(name));
	if(knh_bytes_index(knh_String_tobytes(name), '_') == -1) {
		if(IS_NULL(DP(ns)->lconstDictMap)) {
			KNH_SETv(ctx, DP(ns)->lconstDictMap, new_DictMap0(ctx, 16));
		}
		knh_DictMap_set(ctx, DP(ns)->lconstDictMap, name, value);
	}
	else {
		konoha_addClassConst(ctx, CLASS_Any, name, value);
	}
}

/* ======================================================================== */
/* [Func] */

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
/* [tag] */

knh_type_t knh_NameSpace_tagcid(Ctx *ctx, NameSpace *o, knh_class_t cid, knh_bytes_t tag)
{
	knh_cwb_t cwb = new_cwb(ctx);
	knh_class_t bcid = ctx->share->ClassTable[cid].bcid;
	//DBG2_P("%s:'%s'", CLASSN(bcid), tag.buf);
	knh_printf(ctx, cwb.w, "%C:%B", bcid, tag);
	cid = knh_NameSpace_getcid(ctx, o, knh_cwb_tobytes(cwb));
	knh_cwb_clear(cwb);
//	if(cid == CLASS_unknown) {
//		if(bcid == CLASS_Int) {
//			knh_printf(ctx, cwb.w, "Float:%B", tag);
//			cid = knh_NameSpace_getcid(ctx, o, knh_cwb_tobytes(cwb));
//			knh_cwb_clear(cwb);
//		}
//		else if(bcid == CLASS_Float) {
//			knh_printf(ctx, cwb.w, "Int:%B", tag);
//			cid = knh_NameSpace_getcid(ctx, o, knh_cwb_tobytes(cwb));
//			knh_cwb_clear(cwb);
//		}
//	}
	return cid;
}


/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
