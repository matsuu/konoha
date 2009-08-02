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

#ifdef KNH_CC_METHODAPI

void knh_KLRCode__dumpmtd(Ctx *ctx, KLRCode* o, OutputStream *w, Method *mtd);

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] This! Object.new:init(Any value) @VARARGS */

static METHOD knh__Object_new__init(Ctx *ctx, knh_sfp_t *sfp)
{
	Object *o = sfp[0].o;
//	knh_class_t cid = knh_Object_cid(o);
//	knh_sfp_t *v = sfp + 1;
//	int ac = knh_sfp_argc(ctx, v);
//	size_t i;
//	for(i = 0; i < ac; i+= 2) {
//		if(IS_bString(v[i].s)) {
			TODO();
//			knh_fieldn_t fn = knh_tName_get_fnq(ctx, knh_String_tobytes(v[i].s), FIELDN_NONAME);
//			if(fn == FIELDN_NONAME) continue;
//			knh_index_t idx = knh_Class_queryField(ctx, cid, fn);
//			if(idx == -1) continue;
//			knh_cfield_t *cf = knh_Class_fieldAt(ctx, cid, idx);
//			knh_type_t type = knh_pmztype_totype(ctx, cf->type, cid);
//			DBG2_P("[%d] %s%s %s", (int)idx, TYPEQN(type), FIELDN(fn));
//			KNH_SETv(ctx, KNH_FIELDn(o, idx), knh_Object_opAs__type(ctx, v[i+1].o, type, KNH_FIELDn(o,idx)));
//		}
//	}
	KNH_RETURN(ctx, sfp, o);
}

/* ======================================================================== */

/* ------------------------------------------------------------------------ */
/* @method[NULLBASE] Int! Object.opAddr() */

static METHOD knh__Object_opAddr(Ctx *ctx, knh_sfp_t *sfp)
{
	void *p = NULL;
	if(IS_bInt(sfp[0].o) || IS_bFloat(sfp[0].o)) {
		p = (void*)(&sfp[0] + sizeof(void*));
	}
	else if(IS_Boolean(sfp[0].o)) {
		p = (sfp[0].bvalue) ? (void*)(KNH_TRUE) : (void*)(KNH_FALSE);
	}
	else if(IS_NOTNULL(sfp[0].o)) {
		p = (void*)sfp[0].o;
	}
	KNH_RETURN_Int(ctx, sfp, (knh_intptr_t)p);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.opEq(Any value) */

static METHOD knh__Object_opEq(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_compareTo(ctx, sfp[0].o, sfp[1].o) == 0);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.opNeq(Any value) */

static METHOD knh__Object_opNeq(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_compareTo(ctx, sfp[0].o, sfp[1].o) != 0);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.opLt(Any value) */

static METHOD knh__Object_opLt(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_compareTo(ctx, sfp[0].o, sfp[1].o) < 0);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.opLte(Any value) */

static METHOD knh__Object_opLte(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_compareTo(ctx, sfp[0].o, sfp[1].o) <= 0);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.opGt(Any value) */

static METHOD knh__Object_opGt(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_compareTo(ctx, sfp[0].o, sfp[1].o) > 0);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.opGte(Any value) */

static METHOD knh__Object_opGte(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_compareTo(ctx, sfp[0].o, sfp[1].o) >= 0);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! Object.opIs(Any v) */

static METHOD knh__Object_opIs(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_class_t scid = knh_Object_cid(sfp[0].o);
	knh_class_t tcid = knh_Object_cid(sfp[1].o);
	DBG2_P("Semantic Matching %s === %s", CLASSN(scid), CLASSN(tcid));
	if(scid == tcid) {
		knh__Object_opEq(ctx, sfp);
	}
	else if(IS_NULL(sfp[1].o)) {
		KNH_RETURN_Boolean(ctx, sfp, IS_NULL(sfp[0].o));
	}
	else {
		TODO_THROW(ctx);
		KNH_RETURN_Boolean(ctx, sfp, 0);
//		knh_sfp_t *lsfp = KNH_LOCAL(ctx);
//		KNH_LPUSH(ctx, sfp[1].o);
//		VM_MAP(ctx, scid);
//		KNH_SETv(ctx, sfp[1].o, ctx->esp[0].o);
//		KNH_LOCALBACK(ctx, lsfp);
//		if(IS_NULL(sfp[1].o)) {
//			KNH_RETURN_Boolean(ctx, sfp, 0);
//		}
//		else {
//			knh__Object_opEq(ctx, sfp);
//		}
	}
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! Object.opIsa(Class! c) */

static METHOD knh__Object_opIsa(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_class_t scid = knh_Object_cid(sfp[0].o);
	knh_class_t tcid = (sfp[1].c)->cid;
	if(scid == tcid) {
		KNH_RETURN_Boolean(ctx, sfp, 1);
	}
	else {
		TODO_THROW(ctx);
		KNH_RETURN_Boolean(ctx, sfp, 0);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! Object.opTo(Class! c) */

static METHOD knh__Object_opTo(Ctx *ctx, knh_sfp_t *sfp)
{
	TODO_THROW(ctx);
	KNH_RETURN_Boolean(ctx, sfp, 0);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Class! Object.getClass() */

static METHOD knh__Object_getClass(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, ctx->share->ClassTable[(sfp[0].o)->h.cid].class_cid);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.isNull() */

static METHOD knh__Object_isNull(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, IS_NULL(sfp[0].o));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.isNotNull() */

static METHOD knh__Object_isNotNull(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, IS_NOTNULL(sfp[0].o));
}

/* ------------------------------------------------------------------------ */
/* @map Object Iterator! @Const */

static MAPPER knh_Object_Iterator(Ctx *ctx, knh_sfp_t *sfp)
{
	Object *o = sfp[0].o;
	KNH_MAPPED(ctx, sfp, new_Iterator(ctx, o->h.cid, o, NULL));
}

/* ------------------------------------------------------------------------ */
/* @method This.. Object.opItr() */

static METHOD knh__Object_opItr(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, new_Iterator(ctx, knh_Object_cid(sfp[0].o), sfp[0].o, NULL));
}

/* ------------------------------------------------------------------------ */
/* @method void Object.%s(OutputStream w, String m) */

static
void knh_Object__s(Ctx *ctx, Object *b, OutputStream *w, String *m)
{
	if(IS_NULL(b)) {
		knh_write(ctx, w, STEXT("null"));
	}
	else {
		knh_write_char(ctx,w, CLASSN(knh_Object_cid(b)));
		knh_write(ctx,w, STEXT(":"));
		knh_write__p(ctx,w, (void*)b);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Object.%p(OutputStream w, String m) */

static METHOD knh__Object__p(Ctx *ctx, knh_sfp_t *sfp)
{
	void *p = NULL;
	if(IS_bInt(sfp[0].o) || IS_bFloat(sfp[0].o)) {
		p = (void*)(&sfp[0] + sizeof(void*));
	}
	else if(IS_Boolean(sfp[0].o)) {
		p = (sfp[0].bvalue) ? (void*)(KNH_TRUE) : (void*)(KNH_FALSE);
	}
	else if(IS_NOTNULL(sfp[0].o)) {
		p = (void*)sfp[0].o;
	}
	knh_write__p(ctx, sfp[1].w, p);
}

/* ------------------------------------------------------------------------ */
/* @method void Object.%k(OutputStream w, String m) */

static
void knh_Object__k(Ctx *ctx, Object *o, OutputStream *w, String *m)
{
	if(knh_Object_isUndefined(o)) {
		knh_write(ctx, w, STEXT("undefined"));
	}
	else if(IS_NULL(o)) {
		knh_write(ctx, w, STEXT("null"));
	}
	else if(o->h.bcid == CLASS_Object) {
		size_t bsize = ctx->share->ClassTable[o->h.cid].bsize;
		knh_write_char(ctx, w, CLASSN(o->h.cid));
		if(bsize > 0) {
			size_t i;
			Object **v = (Object**)o->ref;
			knh_putc(ctx, w, '{');
			for(i = 0; i < bsize; i++) {
				knh_cfield_t *cf = knh_Class_fieldAt(ctx, knh_Object_cid(o), i);
				if(cf->fn == FIELDN_NONAME) break;
				if(cf->fn == FIELDN_register) continue;
				if(i > 0) {
					knh_write_delim(ctx, w);
				}
				knh_printf(ctx, w, "%s: ", FIELDN(cf->fn));
#ifdef KNH_USING_UNBOXFIELD
				if(IS_ubxint(cf->type)) {
					knh_int_t *data = (knh_int_t*)(v + i);
					knh_write_ifmt(ctx, w, KNH_INT_FMT, data[0]);
					continue;
				}
				else if(IS_ubxfloat(cf->type)) {
					knh_float_t *data = (knh_float_t*)(v + i);
					knh_write_ffmt(ctx, w, KNH_FLOAT_FMT, data[0]);
					continue;
				}
				else if(IS_ubxboolean(cf->type)) {
					knh_bool_t *data = (knh_bool_t*)(v + i);
					if(data[0]) knh_write(ctx, w, STEXT("true"));
					else knh_write(ctx, w, STEXT("false"));
					continue;
				}
#else
				knh_format(ctx, w, METHODN__k, v[i], KNH_NULL);
#endif
			}
			knh_putc(ctx, w, '}');
		}
	}
	else {
		knh_format(ctx, w, METHODN__s, o, KNH_NULL);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Object.%dump(OutputStream w, String m) */

static
void knh_Object__dump(Ctx *ctx, Object *b, OutputStream *w, String *m)
{
	TODO();
//	knh_class_t cid = knh_Object_cid(b);
//	if(cid < KONOHA_TSTRUCT_SIZE) {
//		knh_format(ctx, w, METHODN__s, b, KNH_NULL);
//		return ;
//	}
//	knh_intptr_t i, c = 0;
//	knh_putc(ctx, w, '[');
//	for(i = 0; i < ClassTable(cid).bsize; i++) {
//		knh_cfield_t *cf = knh_Class_fieldAt(ctx, cid, i);
//		if(cf->fn == FIELDN_NONAME || KNH_FLAG_IS(cf->flag, KNH_FLAG_CFF_HIDDEN)) continue;
//		if(c > 0) {
//			knh_write_delim(ctx, w);
//		}
//		knh_printf(ctx, w, "%s=", /* cf->type, */ FIELDN(cf->fn));
//		Object *v = KNH_FIELDn(b, i);
//		if(IS_bString(v)) {
//			knh_format(ctx, w, METHODN__dump, v, KNH_NULL);
//		}
//		else {
//			knh_format(ctx, w, METHODN__s, v, KNH_NULL);
//		}
//		c++;
//	}
//	knh_putc(ctx, w, ']');
}

/* ------------------------------------------------------------------------ */
/* @method void Object.%empty(OutputStream w, String m) */

static
void knh_Object__empty(Ctx *ctx, Object *b, OutputStream *w, String *m)
{
}

/* ------------------------------------------------------------------------ */
/* @map Object String! */

static
MAPPER knh_Object_String(Ctx *ctx, knh_sfp_t *sfp)
{
	Object *o = sfp[0].o;
	Method *mtd = knh_lookupFormatter(ctx, knh_Object_cid(o), METHODN__s);
	if(IS_NULL(mtd)) {
		KNH_MAPPED(ctx, sfp, TS_EMPTY);
	}
	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
	KNH_MOV(ctx, sfp[2].o, o);
	KNH_MOV(ctx, sfp[3].o, cwb->w);
	KNH_MOV(ctx, sfp[4].o, KNH_NULL);
	KNH_SCALL(ctx, sfp, 1, mtd, 2);
	KNH_MAPPED(ctx, sfp, new_String__cwb(ctx, cwb));
}

/* ------------------------------------------------------------------------ */
/* @method void Any.%k(OutputStream w, String m) */

static
void knh_Any__k(Ctx *ctx, knh_Any_t *o, OutputStream *w, String *m)
{
	knh_write(ctx, w, knh_String_tobytes(TS_null));
}

/* ======================================================================== */
/* [Class] */

/* @method Array! Class.domain() */

static
METHOD knh__Class_domain(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, knh_getClassDomain(ctx, (sfp[0].c)->cid));
}

/* ------------------------------------------------------------------------ */
/* @method void Class.%s(OutputStream w, String m) */

static
void knh_Class__s(Ctx *ctx, Class *o, OutputStream *w, String *m)
{
	knh_write_cid(ctx, w, o->cid);
}

/* ------------------------------------------------------------------------ */
/* @method void Class.%k(OutputStream w, String m) */

static
void knh_Class__k(Ctx *ctx, Class *o, OutputStream *w, String *m)
{
	knh_write_cid(ctx, w, o->cid);
}

/* ------------------------------------------------------------------------ */
/* @method void Class.%dump(OutputStream w, String m) */

static
void knh_Class__dump(Ctx *ctx, Class *o, OutputStream *w, String *m)
{
	TODO_THROW(ctx);
}

/* ------------------------------------------------------------------------ */

static
char *knh_methodop_tochar(knh_methodn_t mn)
{
	switch(mn) {
	case METHODN_opNot: return "!x";
	case METHODN_opInstanceof: return "x instanceof T";
	case METHODN_opAs:  return "x as T";

	case METHODN_opHas:  return "y in? x";
	case METHODN_opIsa: return "x isa? y";
	case METHODN_opIs:  return "x is? y";
	case METHODN_opTo:  return "x to? y";

	case METHODN_opEq:  return "x == y";
	case METHODN_opNeq:  return "x != x";
	case METHODN_opLt:  return "x < y";
	case METHODN_opLte:  return "x <= y";
	case METHODN_opGt:  return "x > y";
	case METHODN_opGte:  return "x >= y";

	case METHODN_opLshift:  return "x << y";
	case METHODN_opRshift:  return "x >> y";

	case METHODN_opMod:  return "x mod y";

#ifdef METHODN_opAdd__2
	case METHODN_opAdd__2 :
#endif
	case METHODN_opAdd:  return "x + y";

#ifdef METHODN_opSub__2
	case METHODN_opSub__2 :
#endif
	case METHODN_opNeg: return "-x";

	case METHODN_opSub:  return "x - y";

#ifdef METHODN_opDiv__2
	case METHODN_opDiv__2 :
#endif
	case METHODN_opDiv:  return "x / y";

#ifdef METHODN_opMul__2
	case METHODN_opMul__2 :
#endif
	case METHODN_opMul:  return "x * y";

	case METHODN_opLor:  return "x & y";
	case METHODN_opLand:  return "x | y";
	case METHODN_opLnot:  return "~x";
	case METHODN_opXor:  return "x ^ y";
	case METHODN_opNext:  return "x++";
	case METHODN_opPrev:  return "x--";
	case METHODN_opItr:   return "x..";
	case METHODN_getSize: return "|x|";
	case METHODN_get: return "x[n]";
	case METHODN_set: return "x[n]=y";
	case METHODN_setAll: return "x[]=y";
	case METHODN_opSubsete: return "x[m..n]";
	case METHODN_opOffset: return "x[m..+n]";
	case METHODN_opSubset: return "x[m..<n]";
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
void knh_Class_NAME__man(Ctx *ctx, knh_class_t cid, OutputStream *w)
{
	knh_write_char(ctx, w, _("Class"));
	knh_write_EOL(ctx, w);

	knh_write_TAB(ctx, w);
	knh_write(ctx, w, knh_String_tobytes(ClassTable(cid).lname));
	knh_write_EOL(ctx, w);

	while(ClassTable(cid).supcid != CLASS_Object) {
		cid = ClassTable(cid).supcid;
		knh_write_TAB(ctx, w);
		knh_write(ctx, w, STEXT("extends "));
		knh_write(ctx, w, knh_String_tobytes(ClassTable(cid).lname));
		knh_write_EOL(ctx, w);
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_Method__man(Ctx *ctx, Method *o, OutputStream *w, knh_class_t cid)
{
	if(!knh_Context_isVerbose(ctx)) {
		if(knh_Method_isPrivate(o)) return;
	}

	if(knh_Method_isAbstract(o)) {
		knh_write(ctx, w, STEXT("@Abstract"));
		knh_putc(ctx, w, ' ');
	}
//	if(knh_Method_rztype(o) == TYPE_void) {
//		knh_write(ctx, w, knh_String_tobytes(TS_void));
//	}else{
		knh_write_type(ctx, w, knh_pmztype_totype(ctx, knh_Method_rztype(o), cid));
//	}
	knh_putc(ctx, w, ' ');

	if(knh_Method_isStatic(o)) {
		knh_write_char(ctx, w, CTXCLASSN(cid));
		knh_putc(ctx, w, '.');
	}
	knh_write_mn(ctx, w, DP(o)->mn);

	knh_putc(ctx, w, '(');
	size_t i;
	for(i = 0; i < knh_Method_psize(o); i++) {
		if(i > 0) {
			knh_write_delim(ctx, w);
		}
		knh_mparam_t mf = knh_Method_param(o, i);
		knh_write_type(ctx, w, knh_pmztype_totype(ctx, mf.type, cid));
		knh_putc(ctx, w, ' ');
		knh_write(ctx, w, B(FIELDN(mf.fn)));
	}
	if(knh_Method_isVarArgs(o)) {
		knh_write_delim(ctx, w);
		knh_write_dots(ctx, w);
	}
	knh_putc(ctx, w, ')');
}

/* ------------------------------------------------------------------------ */
/* @method void Class.%man(OutputStream w, String m) */

static
void knh_Class__man(Ctx *ctx, Class *o, OutputStream *w, String *m)
{
	knh_class_t cid = (o)->cid;
	knh_Class_NAME__man(ctx, cid, w);
	knh_Const__man(ctx, cid, w);

	char bufmn[CLASSNAME_BUFSIZ];
	KNH_ASSERT_cid(cid);
	knh_sfp_t *lsfp = KNH_LOCAL(ctx);
	DictMap *dm = new_DictMap0(ctx, 128);
	KNH_LPUSH(ctx, dm);
	size_t i = 0;
	while(1) {
		Array *a = ClassTable(cid).cstruct->methods;
		for(i = 0; i < knh_Array_size(a); i++) {
			Method *mtd = (Method*)knh_Array_n(a, i);
			char *op = knh_methodop_tochar(DP(mtd)->mn);
			if(op == NULL) {
				knh_format_methodn(ctx, bufmn, sizeof(bufmn), DP(mtd)->mn);
				//DBG2_P("mn='%s'", bufmn);
				knh_bytes_t name = B(bufmn);
				if(IS_NULL(knh_DictMap_get__b(ctx,  dm, name))) {
					knh_DictMap_set(ctx, dm, new_String(ctx, name, NULL), UP(mtd));
				}
			}
			else {
				knh_bytes_t name = B(op);
				if(IS_NULL(knh_DictMap_get__b(ctx,  dm, name))) {
					knh_DictMap_set(ctx, dm, T(op), UP(mtd));
				}
			}
		}
		if(cid == CLASS_Object) break;
		cid = ClassTable(cid).supcid;
	}

	int cnt = 0;
	cid = (o)->cid;

	int hasCaption = 0;
	int isBOL = 1;
	for(i = 0; i < knh_DictMap_size(dm); i++) {
		Method *mtd = (Method*)knh_DictMap_valueAt(dm, i);
		if(IS_Method(mtd)) {
			char *op = knh_methodop_tochar(DP(mtd)->mn);
			if(op == NULL) continue;
			knh_DictMap_removeAt(ctx, dm, i);
			if(DP(mtd)->cid == CLASS_Object && cid != CLASS_Object) continue;
			if(hasCaption == 0) {
				knh_write_char(ctx, w, _("Operator"));
				knh_write_EOL(ctx, w);
				hasCaption = 1;
			}
			if(isBOL == 1) {
				knh_write_TAB(ctx, w);
				isBOL = 0;
			}
			knh_snprintf(bufmn, sizeof(bufmn), "%10s  ", op);
			knh_write_char(ctx, w, bufmn);
			if(cnt % 5 == 4) {
				knh_write_EOL(ctx, w);
				isBOL = 1;
			}
			cnt++;
		}
	}
	if(isBOL != 1) {
		knh_write_EOL(ctx, w);
	}

	hasCaption = 0;
	isBOL = 1;
	knh_DictMap_sort(dm);

	for(i = 0; i < knh_DictMap_size(dm); i++) {
		Method *mtd = (Method*)knh_DictMap_valueAt(dm, i);
		if(IS_Method(mtd)) {
			if(METHODN_IS_MOVTEXT(DP(mtd)->mn)) continue;
			if(DP(mtd)->cid == CLASS_Object && cid != CLASS_Object) continue;
//			if(DP(mtd)->cid != ClassTable(cid).bcid) continue;
			if(hasCaption == 0) {
				knh_write_char(ctx, w, _("Method"));
				knh_write_EOL(ctx, w);
				hasCaption = 1;
			}
			knh_write_TAB(ctx, w);
			knh_Method__man(ctx, mtd, w, cid);
			knh_write_EOL(ctx, w);
			knh_DictMap_removeAt(ctx, dm, i);
		}
	}

	hasCaption = 0;
	cnt = 8;
	for(i = 0; i < knh_DictMap_size(dm); i++) {
		Method *mtd = (Method*)knh_DictMap_valueAt(dm, i);
		if(IS_Method(mtd)) {
			if(!METHODN_IS_MOVTEXT(DP(mtd)->mn)) continue;
			if(DP(mtd)->cid == CLASS_Object && cid != CLASS_Object) continue;
			if(hasCaption == 0) {
				knh_write_char(ctx, w, _("Formatter"));
				knh_write_EOL(ctx, w);
				knh_write_TAB(ctx, w);
				hasCaption = 1;
			}
			knh_bytes_t k = knh_String_tobytes(knh_DictMap_keyAt(dm, i));
			if(cnt + k.len > 72) {
				knh_write_EOL(ctx, w);
				knh_write_TAB(ctx, w);
				cnt = 8;
			}
			knh_write(ctx, w, k); knh_putc(ctx, w, ' ');
			cnt += (k.len + 1);
		}
	}
	knh_write_EOL(ctx, w);

	knh_ClassMap__man(ctx, ClassTable(cid).cmap, w, cid);
	KNH_LOCALBACK(ctx, lsfp);
}

/* ======================================================================== */

/* ------------------------------------------------------------------------ */
/* @method void Method.%s(OutputStream w, String m) */

void knh_Method__s(Ctx *ctx, Method *o, OutputStream *w, String *m)
{
	knh_write_char(ctx, w, CTXCLASSN(DP(o)->cid));
	knh_putc(ctx, w, '.');
	knh_write_mn(ctx, w, DP(o)->mn);
}

/* ------------------------------------------------------------------------ */
/* @method void Method.%k(OutputStream w, String m) */

void knh_Method__k(Ctx *ctx, Method *o, OutputStream *w, String *m)
{
	if(knh_Method_isAbstract(o)) {
		knh_write(ctx, w, STEXT("@abstract"));
		knh_putc(ctx, w, ' ');
	}
	if(knh_Method_rztype(o) == TYPE_void) {
		knh_write(ctx, w, knh_String_tobytes(TS_void));
	}else{
		knh_write_type(ctx, w, knh_Method_rztype(o));
	}
	knh_putc(ctx, w, ' ');
	knh_Method__s(ctx, o, w, (String*)KNH_NULL);
	knh_putc(ctx, w, '(');
	size_t i;
	for(i = 0; i < knh_Method_psize(o); i++) {
		if(i > 0) {
			knh_write_delim(ctx, w);
		}
		knh_mparam_t mf = knh_Method_param(o, i);
		knh_write_type(ctx, w, mf.type);
		knh_putc(ctx, w, ' ');
		knh_write(ctx, w, B(FIELDN(mf.fn)));
	}
	if(knh_Method_isVarArgs(o)) {
		knh_write_delim(ctx, w);
		knh_write_dots(ctx, w);
	}
	knh_putc(ctx, w, ')');
}

/* ------------------------------------------------------------------------ */
/* @method void Method.%dump(OutputStream w, String m) */

void knh_Method__dump(Ctx *ctx, Method *o, OutputStream *w, String *m)
{
	knh_Method__k(ctx, o, w, m);
	knh_println(ctx, w, STEXT(""));
	if(knh_Method_isObjectCode(o)) {
		if(IS_KLRCode((Object*)DP(o)->code)) {
			knh_KLRCode__dumpmtd(ctx, (KLRCode*)DP(o)->code, w, o);
		}
	}
}

/* ------------------------------------------------------------------------ */

#endif /*KNH_CC_METHODAPI*/

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
