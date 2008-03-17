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

NameSpace* new_NameSpace(Ctx *ctx0, NameSpace *parent, String *nsname)
{
	NameSpace* b = 
		(NameSpace*)knh_Object_malloc0(ctx0, KNH_FLAG_NameSpace, CLASS_NameSpace, sizeof(NameSpace));
	KNH_INITv(b->parent,  parent);
	KNH_INITv(b->nsname, nsname);
	KNH_INITv(b->imports, new_Array(ctx0, 4));
	KNH_INITv(b->tag2urnDictMap, new_DictMap(ctx0, 8));
	if(IS_NULL(parent)) {
		KNH_INITv(b->name2cidDictSet, new_DictSet(ctx0, KONOHA_TCLASS_SIZE));
		knh_NameSpace_setClass(ctx0, b, new_String__STEXT(ctx0, CLASS_String__class, "any"), CLASS_any);
	}
	else{
		KNH_INITv(b->name2cidDictSet, new_DictSet(ctx0, 128));
		knh_NameSpace_import(ctx0, b, STEXT("konoha."));
	}
	return b;
}

/* ======================================================================== */
/* [class] */

/* @method void NameSpace.setClass(String name, Class c) */

void knh_NameSpace_setClass(Ctx *ctx, NameSpace *b, String *name, knh_class_t c)
{
	DEBUG_ASSERT(IS_NameSpace(b));
	DEBUG_ASSERT(IS_String(name));
	knh_DictSet_set(ctx, b->name2cidDictSet, name, (knh_uint_t)(c+1));
}

/* ------------------------------------------------------------------------ */

void knh_NameSpace_setLocalName(Ctx *ctx, NameSpace *b, String *name, knh_class_t c)
{
	DEBUG_ASSERT(IS_NameSpace(b));
	DEBUG_ASSERT(IS_String(name));
	DEBUG_ASSERT(knh_bytes_rindex(knh_String_tobytes(name), '+') == -1);
	knh_index_t loc = knh_bytes_rindex(knh_String_tobytes(name), '.');
	if(loc == -1) {
		knh_DictSet_set(ctx, b->name2cidDictSet, name, (knh_uint_t)(c+1));
	}
	else {
		String *lname = new_String__sub(ctx, CLASS_String__class, name, (loc+1), name->strlen - (loc+1));
		knh_DictSet_set(ctx, b->name2cidDictSet, lname, (knh_uint_t)(c+1));
	}
}

/* ------------------------------------------------------------------------ */
/* @method Class NameSpace.getClass(String name) */

knh_class_t knh_NameSpace_getClass(Ctx *ctx, NameSpace *b, knh_bytes_t name)
{
	if(knh_bytes_equals(name, STEXT("GLOBAL"))) {
		return knh_Object_cid(knh_Context_getCompiler(ctx, (Context*)ctx)->nsproto);
	}
	
	NameSpace *ns = b;
	L_TAIL:;
	//DEMO_DUMP(ctx, ns->name2cidDictSet, KNH_NULL, "ns");
	knh_uint_t cid = knh_DictSet_get__b(ns->name2cidDictSet, name);
	//DEBUG("**** name='%s', name.len=%d cid=%d", name.buf, name.len, cid);
	if(cid > 0) return (knh_class_t)(cid-1);
	if(IS_NULL(ns->parent)) {
		return CLASS_unknown;
	}
	ns = ns->parent;
	goto L_TAIL;
}

/* ======================================================================== */
/* [type] */

knh_type_t knh_NameSpace_getType(Ctx *ctx, NameSpace *b, knh_bytes_t name)
{
	if(name.len == 4 && 
		name.buf[0] == 'v' && name.buf[1] == 'o' && 
		name.buf[2] == 'i' && name.buf[3] == 'd') return TYPE_void;
	
	if(knh_bytes_isNotNullType(name)) {
		name.len--;
		return knh_NameSpace_getClass(ctx, b, name);
	}
	if(knh_bytes_isPluralType(name)) {
		name.len -= 2;
		knh_class_t cid = knh_NameSpace_getClass(ctx, b, name);
		return (cid == CLASS_unknown) ? cid : CLASS_TOPLURAL(cid);
	}
	knh_class_t cid = knh_NameSpace_getClass(ctx, b, name);
	return (cid == CLASS_unknown) ? cid : CLASS_TONULLABLE(cid);
}

/* ======================================================================== */
/* [tag] */

knh_class_t knh_tclass_classURN(Ctx *ctx, knh_class_t bcid, knh_bytes_t urn)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), KNH_CLASSSPEC_FMT, CLASSN(bcid), urn.buf);
	knh_class_t cid = knh_NameSpace_getClass(ctx, knh_NameSpace_SYSTEM(), B(buf));
	if(cid == CLASS_unknown) {
		cid = knh_tclass_loadURN(ctx, bcid, urn);
	}
	return cid;
}

/* ------------------------------------------------------------------------ */

knh_class_t knh_tclass_loadURN(Ctx *ctx, knh_class_t bcid, knh_bytes_t urn)
{
	switch(bcid) {
	case CLASS_Int:
		return knh_system_loadEnum(ctx, urn);
	case CLASS_Float:
		return knh_system_loadUnit(ctx, urn);
	case CLASS_String:
		return knh_system_loadVocabulary(ctx, urn);
	}
	DEBUG("unknown bcid=%d,'%s'", bcid, CLASSN(bcid));
	return bcid;
}

/* ------------------------------------------------------------------------ */

knh_type_t knh_NameSpace_tagcid(Ctx *ctx, NameSpace *b, knh_class_t bcid, knh_bytes_t tag)
{
	char buf[CLASSNAME_BUFSIZ];
	DEBUG("%s::'%s'", CLASSN(bcid), tag.buf);
	knh_snprintf(buf, sizeof(buf), "%s::%s", CLASSN(bcid), tag.buf);
	knh_class_t cid = knh_NameSpace_getClass(ctx, b, B(buf));
	if(cid == CLASS_unknown) {
		if(bcid == CLASS_Int) {
			knh_snprintf(buf, sizeof(buf), "Float::%s", tag.buf);
			cid = knh_NameSpace_getClass(ctx, b, B(buf));
		}
	}
	return cid;
}

/* ======================================================================== */
/* [func] */

Class *knh_NameSpace_getFuncClass(Ctx *ctx, NameSpace *b, knh_bytes_t funcname)
{
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

//knh_type_t knh_NameSpace_guess_type(Ctx *ctx, NameSpace *b, FL *fl, knh_bytes_t name)
//{
//	if(knh_byte_isEXPTN(name)) {
//		return CLASS_Exception;
//	}
//	knh_type_t type = knh_tclass_ptype_forname(ctx, name, CLASS_unknown);
//	if(type == CLASS_unknown) {
//		if(name.buf[name.len-1] == '!') {
//			type = TYPE_NOTNULL(CLASS_Any);
//		}else if(name.buf[name.len-1] == '.') {
//			type = TYPE_PLURAL(CLASS_Any);
//		}else {
//			type = CLASS_Any;
//		}
//		if(fl != NULL) {
//			NOTE_UndefinedType(ctx, fl, name, type);
//		}else{
//			return CLASS_unknown;
//		}
//	}
//	return type;
//}
//
///* ======================================================================== */
///* [tag] */
//
//
//void knh_NameSpace_addURN(Ctx *ctx, NameSpace *b, String *tag, String *urn)
//{
//	knh_DictMap_put(ctx, b->tag2urnDictMap, tag, urn);
//	knh_DictMap_put(ctx, b->tag2urnDictMap, urn, tag);
//}
//
///* ------------------------------------------------------------------------ */
//
//
//String *knh_NameSpace_findb_urn(NameSpace *b, knh_bytes_t tag)
//{
//	return (String*)knh_DictMap_getb(b->tag2urnDictMap, tag);
//}
//
///* ------------------------------------------------------------------------ */
//
//
//knh_class_t knh_NameSpace_spec(Ctx *ctx, NameSpace *b, FL *fl, knh_class_t cid, knh_bytes_t u)
//{
//	char urn[CLASSNAKNH_BUFSIZ], cname[CLASSNAKNH_BUFSIZ];
//	knh_byte_copyto(u, urn, sizeof(urn));
//	knh_snprintf(cname, sizeof(cname), "%s{%s}", CLASSN(cid), urn);
//	TODO();
//	DEBUG("@@ Searching '%s'\n", cname);
//	return cid;
//}
//
///* ------------------------------------------------------------------------ */
//
//
//knh_class_t knh_NameSpace_spec_tag(Ctx *ctx, NameSpace *b, FL *fl, knh_class_t cid, knh_bytes_t tag)
//{
//	String *urn = knh_NameSpace_findb_urn(b, tag);
//	if(IS_NULL(urn)) {
////		if(fl != NULL) {
//			char buf[CLASSNAKNH_BUFSIZ];
//			knh_byte_copyto(tag, buf, sizeof(buf)-1);
//			NOTE_UnknownTag(ctx, fl, cid, B(buf));
////		}
//		return cid;
//	}
//	return knh_NameSpace_spec(ctx, b, fl, cid, knh_String_tobytes(urn));
//}
//
///* ------------------------------------------------------------------------ */
//
//knh_bool_t
//knh_byte_isSystemTag(knh_bytes_t tag)
//{
//	return 0;	
//	
//}
//
///* ------------------------------------------------------------------------ */
//
//Object *knh_NameSpace_value__tag(Ctx *ctx, NameSpace *b, FL *fl, knh_bytes_t tag, knh_bytes_t t)
//{
//	return KNH_NULL;
//}
//


#ifdef __cplusplus
}
#endif
