/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2005-2009, Kimio Kuramitsu <kimio at ynu.ac.jp>
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

#define KNH_USING_UNBOXFIELD 1

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */

static knh_index_t knh_Asm_declareScriptVariable(Ctx *ctx, Asm *abr, knh_cfield_t *decl);

static Term *knh_Stmt_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt);
static Term *knh_StmtCALL_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_class_t reqt);

static int TERMs_typing(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, NameSpace *ns, knh_type_t reqt, int mode);
static int TERMs_isNULL(Ctx *ctx, Stmt *stmt, size_t n);

#define KNH_ASM_ASSERT(ctx, abr, c)   KNH_ASSERT(c)

/* ======================================================================== */
/* [getter] */

static
knh_fieldn_t knh_Token_getfnq(Ctx *ctx, Token *tk)
{
	DBG2_ASSERT(IS_Token(tk));
	if(TT_(tk) == TT_NAME) {
		DP(tk)->fn = knh_getfnq(ctx, knh_Token_tobytes(ctx, tk), FIELDN_NEWID);
		TT_(tk)  = TT_FN;
		return DP(tk)->fn;
	}
	else if(TT_(tk) == TT_FN) {
		return DP(tk)->fn;
	}
	DBG2_P("TT_(tk)=%s, '%s'", knh_token_tochar(TT_(tk)), sToken(tk));
	DBG2_ABORT();
	return FIELDN_NONAME;
}

/* ------------------------------------------------------------------------ */

static
knh_methodn_t knh_Token_getmn(Ctx *ctx, Token *tk)
{
	DBG2_ASSERT(IS_Token(tk));
	if(TT_(tk) == TT_MN) {
		return DP(tk)->mn;
	}
	else if(TT_(tk) == TT_FN) {
		knh_methodn_t mn = FIELDN_UNMASK(DP(tk)->fn);
		if(knh_Token_isGetter(tk)) {
			return mn | KNH_FLAG_MN_GETTER;
		}
		else if(knh_Token_isSetter(tk)) {
			return mn | KNH_FLAG_MN_SETTER;
		}
		return mn;
	}
	else {
		knh_bytes_t name = knh_Token_tobytes(ctx, tk);
		if(TT_(tk) == TT_NAME) {
			knh_methodn_t mn = knh_getmn(ctx, name, METHODN_NEWID);
			if(knh_Token_isGetter(tk)) {
				return mn | KNH_FLAG_MN_GETTER;
			}
			if(knh_Token_isSetter(tk)) {
				return mn | KNH_FLAG_MN_SETTER;
			}
			return mn;
		}
		else if(TT_(tk) == TT_CMETHODN) {
			knh_index_t idx = knh_bytes_rindex(name, '.');
			if(idx != -1) {
				name = knh_bytes_last(name, idx+1);
			}
			knh_methodn_t mn = knh_getmn(ctx, name, METHODN_NEWID);
			return mn;
		}
		else if(TT_(tk) == TT_MT) {
			return knh_getmn(ctx, name, METHODN_NEWID) | KNH_FLAG_MN_MOVTEXT;
		}
		DBG2_P("TT_(tk)=%s, '%s'", knh_token_tochar(TT_(tk)), sToken(tk));
		DBG2_ABORT();
		return METHODN_NONAME;
	}
}

/* ------------------------------------------------------------------------ */
/* [type] */

static int knh_Token_isNullable(Ctx *ctx, Token *tk)
{
	DBG2_ASSERT(IS_Token(tk));
	if(knh_Token_isNullableType(tk)) return 1;
	if(knh_Token_isNotNullType(tk)) return 0;
	return 0; /* Default */
}

/* ------------------------------------------------------------------------ */

static
knh_type_t knh_Token_gettype(Ctx *ctx, Token *tk, NameSpace *ns, knh_class_t defc)
{
	DBG2_ASSERT(IS_Token(tk));
	knh_type_t type;
	if(TT_(tk) == TT_ASIS) {
		type = TYPE_var;
	}
	else if(TT_(tk) == TT_CID) {
		type = DP(tk)->cid;
	}
	else if(knh_Token_isExceptionType(tk)) {
		type = TYPE_Exception;
	}
	else {
		knh_bytes_t name = knh_Token_tobytes(ctx, tk);
		type = knh_NameSpace_gettype(ctx, ns, name, knh_Token_isNullable(ctx, tk));
		if(type == CLASS_unknown) {
			type = defc;
			knh_Token_perror(ctx, tk, KERR_ERRATA, _("unknown type: %s ==> %T"), sToken(tk), defc);
		}
	}
	if(CLASS_type(type) == CLASS_Any) return type;
	if(knh_Token_isNullable(ctx, tk)) {
		return NATYPE_cid(type);
	}
	else {
		return NNTYPE_cid(type);
	}
}

/* ------------------------------------------------------------------------ */

static
knh_class_t knh_Token_getcid(Ctx *ctx, Token *tk, NameSpace *ns, knh_class_t defc)
{
	knh_class_t cid;
	DBG2_ASSERT(IS_Token(tk));
	if(TT_(tk) == TT_CID) {
		cid = DP(tk)->cid;
	}
	else if(knh_Token_isExceptionType(tk)) {
		cid = CLASS_Exception;
	}
	else if(TT_(tk) == TT_ASIS) {
		cid = CLASS_Object;
	}
	else {
		knh_bytes_t name = knh_Token_tobytes(ctx, tk);
		cid = knh_NameSpace_getcid(ctx, ns, name);
		if(cid == CLASS_unknown) {
			if(defc != CLASS_unknown) {
				cid = defc;
				knh_Token_perror(ctx, tk, KERR_ERRATA, _("unknown class: %s ==> %C"), sToken(tk), defc);
			}
		}
	}
	return cid;
}

/* ======================================================================== */
/* [Type Inference] */

static
Term *knh_Stmt_typed(Ctx *ctx, Stmt *stmt, knh_type_t type)
{
	DP(stmt)->type = type;
	return TM(stmt);
}

static
Term *knh_Stmt_untyped(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	DBG2_ASSERT(DP(stmt)->type == TYPE_var);
	DBG2_P("stt=%s untyped", knh_stmt_tochar(STT_(stmt)));
	return TM(stmt);
}

static
int knh_Token_isUntypedName(Token *tk)
{
	return (DP(tk)->type == TYPE_var
		&& (TT_(tk) == TT_LOCAL || TT_(tk) == TT_STACK));
}

static
Token *knh_Asm_getUntypedName(Ctx *ctx, Asm *abr, size_t n)
{
	Token *tkVAR = (Token*)DP(abr)->gamma[n+1-DP(abr)->xstack_size].value;
	DBG2_ASSERT(knh_Token_isUntypedName(tkVAR));
	return tkVAR;
}

static
Token *knh_Asm_getSharedUntypedToken(Ctx *ctx, Asm *abr, Token *tkN)
{
	int idx = DP(tkN)->index;
	if(TT_(tkN) == TT_LOCAL) idx += DP(abr)->xstack_size;
	Token *tkVAR = (Token*)DP(abr)->gamma[idx].value;
	DBG2_ASSERT(IS_Token(tkVAR) && DP(tkN)->index == DP(tkVAR)->index);
	return tkVAR;
}

static
void knh_Asm_derivedClass(Ctx *ctx, Asm *abr, knh_class_t origc, knh_class_t cid)
{
	if(origc != cid) {
		knh_Asm_perror(ctx, abr, KERR_TINFO, _("specialized: %C => %C"), origc, cid);
	}
}

static
void knh_Asm_derivedVariable(Ctx *ctx, Asm *abr, Object *tm, knh_type_t itype)
{
	DBG2_ASSERT(itype != TYPE_var);
	if(IS_Token(tm)) {
		Token *tk = (Token*)tm;
		if(CLASS_type(itype) == CLASS_Any) {
			knh_Asm_perror(ctx, abr, KERR_DWARN,
					_("failed to type inference: %T %s"), itype, sToken(tk));
		}
		else {
			knh_Asm_perror(ctx, abr, KERR_TINFO, _("%T %s"), itype, sToken(tk));
		}
	}
	else {
		Method *mtd = (Method*)tm;
		DBG2_ASSERT(IS_Method(mtd));
		if(CLASS_type(itype) == CLASS_Any) {
			knh_Asm_perror(ctx, abr, KERR_DWARN,
					_("failed to type inference: %M ==> return %T"), DP(mtd)->mn, itype);
		}
		else {
			knh_Asm_perror(ctx, abr, KERR_TINFO, _("%M ==> return %T"), DP(mtd)->mn, itype);
		}
	}
}

static
void knh_Asm_derivedParamType(Ctx *ctx, Asm *abr, Token *tkVAR, knh_type_t itype)
{
	int idx = DP(tkVAR)->index + DP(abr)->xstack_size;
	DBG2_ASSERT(knh_Token_isUntypedName(tkVAR));
	DBG2_ASSERT(DP(abr)->gamma[idx].value == (Object*)tkVAR);
	knh_Asm_derivedVariable(ctx, abr, UP(tkVAR), itype);
	DP(tkVAR)->type = itype;
	KNH_FINALv(ctx, DP(abr)->gamma[idx].value);
	DP(abr)->gamma[idx].value = NULL;
}

static
void knh_Asm_derivedReturnType(Ctx *ctx, Asm *abr, Method *mtd, knh_type_t itype)
{
	DBG2_ASSERT(DP(abr)->rtype == TYPE_var);
	DP(abr)->rtype = itype;
	if(mtd != NULL) {
		DBG2_ASSERT(DP(abr)->mtd == mtd);
		DBG2_ASSERT(knh_Method_rztype(mtd) == TYPE_var);
		(DP(mtd)->mf)->rtype = itype;
	}
}

static
knh_type_t TERMs_inferType(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, NameSpace *ns)
{
	if(n < DP(stmt)->size) {
		if(!TERMs_typing(ctx, stmt, n, abr, ns, TYPE_Any, TWARN_)) {
			return TYPE_var;
		}
		if(TERMs_isNULL(ctx, stmt, n)) {
			knh_Token_perror(ctx, DP(stmt)->tokens[n], KERR_DWARN, _("var should not be null"));
			return TYPE_Any;
		}
		return TERMs_gettype(stmt, n);
	}
	else {
		DBG2_ASSERT(STT_(stmt) == STT_RETURN);
		return TYPE_void;
	}
}

static
int knh_Method_isUntyped(Method *mtd)
{
	int i, psize = knh_Method_psize(mtd);
	if(knh_Method_rztype(mtd) == TYPE_var) return 1;
	for(i = 0; i < psize; i++) {
		if(knh_Method_pztype(mtd,i) == TYPE_var) return 1;
	}
	return 0;
}

static
int knh_Asm_updateMethodType(Ctx *ctx, Asm *abr)
{
	int hasUntypedType = 0;
	Method *mtd = DP(abr)->mtd;
	int i, psize = knh_Method_psize(mtd);
	MethodField *mf = DP(mtd)->mf;
	if(mf->rtype == TYPE_var) {
		if(DP(abr)->rtype != TYPE_var) {
			mf->rtype = DP(abr)->rtype;
		}
		else {
			hasUntypedType = 1;
		}
	}
	for(i = 0; i < psize; i++) {
		if(knh_Method_pztype(mtd,i) == TYPE_var) {
			Token *tkVAR = knh_Asm_getUntypedName(ctx, abr, i);
			if(DP(tkVAR)->type != TYPE_var) {
				knh_mparam_t p = knh_MethodField_param(mf, i);
				knh_MethodField_set(mf, i, DP(tkVAR)->type, p.fn);
			}
			else {
				hasUntypedType = 1;
			}
		}
	}
	return hasUntypedType;
}

static
knh_class_t knh_Token_unifyClass(Ctx *ctx, Token *tkVAR, knh_type_t reqt, Stmt *stmt)
{
	Token *tkM = DP(stmt)->tokens[0];
	knh_methodn_t mn = DP(tkM)->mn;
	DBG2_P("*** %s reqt=%s%s mn(fn)=%s", sToken(tkVAR), TYPEQN(reqt), FIELDN(METHODN_TOFIELDN(mn)));
	return CLASS_type(TYPE_var); /* not derived */
}

/* ======================================================================== */
/* [CONST] */

#define _new_TermCONST(ctx, fln, d)   TM(new_TokenCONST(ctx, fln, d))

Token* new_TokenCONST(Ctx *ctx, Any *fln, Any *data)
{
	knh_Token_t *o = (Token*)new_Object_bcid(ctx, CLASS_Token, 0);
	knh_Token_setFL(o, fln);
	knh_Token_setCONST(ctx, o, data);
	return o;
}

/* ------------------------------------------------------------------------ */

void knh_Token_setCONST(Ctx *ctx, Token *o, Any *data)
{
	KNH_SETv(ctx, DP(o)->data, data);
	knh_Token_toCONST(ctx, o);
}

/* ------------------------------------------------------------------------ */

Token* knh_Token_toCONST(Ctx *ctx, Token *o)
{
	TT_(o) = TT_CONST;
	DP(o)->type = knh_Object_cid(DP(o)->data);
	if(IS_NULL(DP(o)->data)) {
		DP(o)->type = TYPE_Any;
	}
	return o;
}

/* ------------------------------------------------------------------------ */

Token* new_TokenNULL(Ctx *ctx, Any *fln, knh_type_t type)
{
	Token *tk = new_TokenCONST(ctx, fln, KNH_NULL);
	DP(tk)->type = CLASS_type(type);
	return tk;
}

/* ======================================================================== */
/* [DEFVAL] */

static
Token* knh_Token_toDEFVAL(Token *o, knh_class_t cid)
{
	DBG2_ASSERT(cid != TYPE_var);
	TT_(o) = TT_DEFVAL;
	DP(o)->cid = cid;
	if(cid == CLASS_Any) {
		DP(o)->type = NATYPE_Any;
	}
	else {
		DP(o)->type = NNTYPE_cid(cid);
	}
	return o;
}

/* ======================================================================== */
/* [SYSVAL] */

#define IS_SYSVAL(t,v)  (knh_bytes_strcasecmp(t, STEXT(v)) == 0)

static
int knh_Token_toSYSVAL(Ctx *ctx, Token *tk, Asm *abr)
{
	knh_bytes_t t = knh_Token_tobytes(ctx, tk);
	if(IS_SYSVAL(t, "CTX")) {
		TT_(tk) = TT_SYSVAL;
		DP(tk)->index = KNH_SYS_CTX; DP(tk)->type = NNTYPE_Context;
	}
	else if(IS_SYSVAL(t, "IN") || IS_SYSVAL(t, "STDIN")) {
		TT_(tk) = TT_SYSVAL;
		DP(tk)->index = KNH_SYS_STDIN; DP(tk)->type = NNTYPE_InputStream;
	}
	else if(IS_SYSVAL(t, "OUT") || IS_SYSVAL(t, "STDOUT")) {
		TT_(tk) = TT_SYSVAL;
		DP(tk)->index = KNH_SYS_STDOUT; DP(tk)->type = NNTYPE_OutputStream;
	}
	else if(IS_SYSVAL(t, "ERR") || IS_SYSVAL(t, "STDERR")) {
		TT_(tk) = TT_SYSVAL;
		DP(tk)->index = KNH_SYS_STDERR; DP(tk)->type = NNTYPE_OutputStream;
	}
	else if(IS_SYSVAL(t, "OS")) {
		TT_(tk) = TT_SYSVAL;
		DP(tk)->index = KNH_SYS_OS; DP(tk)->type = NNTYPE_System;
	}
	else if(ISB(t, "__")) {
		TT_(tk) = TT_SYSVAL;
		DP(tk)->index = KNH_SYS_SCRIPT; DP(tk)->type = NNTYPE_Script;
	}
	else if(IS_SYSVAL(t, "__line__")) {
		knh_Token_setCONST(ctx, tk, UP(new_Int(ctx, SP(tk)->line)));
	}
	else if(IS_SYSVAL(t, "__file__")) {
		knh_Token_setCONST(ctx, tk, UP(knh_getResourceName(ctx, SP(tk)->uri)));
	}
	else if(IS_SYSVAL(t, "__method__") || IS_SYSVAL(t, "__function__")) {
		knh_Token_setCONST(ctx, tk, UP(knh_Object_getkey(ctx, UP(DP(abr)->mtd))));
	}
	else if(IS_SYSVAL(t, "__namespace__") || IS_SYSVAL(t, "__ns__")) {
		NameSpace *ns = knh_getAsmNameSpace(ctx);
		knh_Token_setCONST(ctx, tk, UP(DP(ns)->nsname));
	}
	else if(IS_SYSVAL(t, "EOL")) {
		knh_Token_setCONST(ctx, tk, UP(TS_EOL));
	}
	else if(IS_SYSVAL(t, "BEGIN")) {
		knh_Token_setCONST(ctx, tk, UP(TS_BEGIN));
	}
	else if(IS_SYSVAL(t, "END")) {
		knh_Token_setCONST(ctx, tk, UP(TS_END));
	}
	else {
		return 0;
	}
	knh_foundKonohaStyle(1);
	return 1;
}

/* ======================================================================== */
/* [STACK, FIELD, GLOBAL, MEMBER] */

static
void knh_Token_toLOCAL(Ctx *ctx, Token *tk, knh_type_t type, int sfpidx)
{
	TT_(tk) = TT_LOCAL;
	DP(tk)->index = (knh_short_t)sfpidx;
	DP(tk)->type = type;
	if(type == TYPE_var) {
		DBG2_P("needs type inferencing LOCAL[%d]", sfpidx);
	}
}

static
void knh_Token_toSTACK(Ctx *ctx, Token *tk, knh_type_t type, int sfpidx)
{
	DBG2_ASSERT(type != TYPE_var);
	TT_(tk) = TT_STACK;
	DP(tk)->index = (knh_short_t)sfpidx;
	DP(tk)->type = type;
}

static
void knh_Token_toFIELD(Ctx *ctx, Token *tk, knh_type_t type, int idx)
{
	DBG2_ASSERT(type != TYPE_var);
	TT_(tk) = TT_FIELD;
	DP(tk)->index = (knh_short_t)idx;
	DP(tk)->type = type;
}

static
void knh_Token_toSCRIPT(Ctx *ctx, Token *tk, knh_type_t type, int idx)
{
	DBG2_ASSERT(type != TYPE_var);
	TT_(tk) = TT_SCRIPT;
	DP(tk)->index = (knh_short_t)idx;
	DP(tk)->type = type;
}

static
void knh_Token_toCLOSURE(Ctx *ctx, Token *tk, Method *mtd)
{
	TT_(tk) = TT_CLOSURE;
	KNH_SETv(ctx, DP(tk)->data, mtd);
	DP(tk)->type = NNTYPE_cid(knh_class_MethodClosure(ctx, DP(mtd)->cid, mtd));
}

/* ------------------------------------------------------------------------ */

//static
//void knh_Token_toMEMBER(Ctx *ctx, Token *tk, int sfi, int idx, knh_type_t type)
//{
//	TT_(tk) = TT_MEMBER;
//	DP(tk)->index = (knh_short_t)sfi;
//	KNH_SETv(ctx, DP(tk)->data, new_Int(ctx, idx));
//	DP(tk)->type = type;
//}

/* ------------------------------------------------------------------------ */
/* [VARIABLE] */
/* ------------------------------------------------------------------------ */

knh_index_t knh_Asm_indexOfLocalVariable(Asm *abr, knh_fieldn_t fnq)
{
	knh_fieldn_t fn = FIELDN_UNMASK(fnq);
	knh_index_t idx;
	for(idx = DP(abr)->gamma_size - 1; idx >= 0; idx--) {
		if(DP(abr)->gamma[idx].fn == fn) {
			return idx;
		}
	}
	return -1;
}

static
knh_cfield_t *knh_Asm_getLocalField(Asm *abr, knh_index_t idx)
{
	KNH_ASSERT(idx != -1 && idx < KONOHA_LOCALSIZE);
	KNH_ASSERT(DP(abr)->gamma[idx].fn != FIELDN_NONAME);
	return (knh_cfield_t*)&(DP(abr)->gamma[idx]);
}

/* ------------------------------------------------------------------------ */

static int knh_Asm_globalIndex(Ctx *ctx, Asm *abr, Script *scr)
{
	if(DP(abr)->globalidx == -1) {
		DBG2_ABORT();
//		knh_cfiled_t decl = {0, NNTYPE_Script, FIELDN_GLOBAL, NULL};
//		KNH_SETv(ctx, decl.value, knh_getCurrentScript(ctx));
//		DP(abr)->globalidx = knh_Asm_declareLocalVariable(ctx, abr, &decl);
		if(DP(abr)->globalidx == -1) return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

static int knh_type_isClosure(Ctx *ctx, knh_type_t type)
{
	knh_class_t cid = CLASS_type(type);
	KNH_ASSERT_cid(cid);
	return (ClassTable(cid).bcid == CLASS_Closure);
}
/* ------------------------------------------------------------------------ */

static
Method *knh_NameSpace_findFuncMethod(Ctx *ctx, NameSpace *ns, knh_class_t this_cid, knh_methodn_t mn)
{
	if(mn == METHODN_NONAME) {
		return (Method*)KNH_NULL;
	}
	else {
		Method *mtd;
		knh_class_t mtd_cid = knh_NameSpace_getFuncClass(ctx, ns, mn);
		if(mtd_cid != CLASS_unknown) {
			mtd = knh_Class_getMethod(ctx, mtd_cid, mn);
			if(IS_NOTNULL(mtd)) { return mtd; }
		}
		mtd = knh_Class_getMethod(ctx, this_cid, mn);
		if(IS_NOTNULL(mtd)) {
			return mtd;
		}
		return knh_Class_getMethod(ctx, knh_Object_cid(knh_getAsmScript(ctx)), mn);
	}
}

/* ------------------------------------------------------------------------ */

static int knh_TokenNAME_typing(Ctx *ctx, Token *tk, Asm *abr, NameSpace *ns, int checkClosure)
{
	knh_fieldn_t fnq = knh_Token_getfnq(ctx, tk);
	knh_index_t idx;

	if(fnq == FIELDN_NONAME) {
		goto L_ERROR;
	}

	if(fnq == FIELDN_super  && !checkClosure) {  /* super.f() */
		knh_type_t type = NNTYPE_cid(ClassTable(DP(abr)->this_cid).supcid);
		knh_Token_toLOCAL(ctx, tk, type, 0);
		knh_Token_setSUPER(tk, 1);
		return 1;
	}

	if(FIELDN_IS_U1(fnq) || FIELDN_IS_SUPER(fnq)) goto L_FIELD;  /* _name */
	if(FIELDN_IS_U2(fnq)) goto L_SCRIPT; /* __name */

	idx = knh_Asm_indexOfLocalVariable(abr, FIELDN_UNMASK(fnq));
	if(idx != -1) {
		knh_cfield_t *cf = knh_Asm_getLocalField(abr, idx);
		knh_type_t type = knh_pmztype_totype(ctx, cf->type, DP(abr)->this_cid);
		if(checkClosure && !knh_type_isClosure(ctx, type)) goto L_FIELD;
		if(idx < DP(abr)->xstack_size) {
			knh_Token_toSTACK(ctx, tk, type, idx);
		}
		else {
			knh_Token_toLOCAL(ctx, tk, type, idx - DP(abr)->xstack_size);
		}
		return 1;
	}

	L_FIELD:;
	idx = knh_Class_queryField(ctx, DP(abr)->this_cid, fnq);
	if(idx != -1) {
		knh_cfield_t *cf = knh_Class_fieldAt(ctx, DP(abr)->this_cid, idx);
		knh_type_t type = knh_pmztype_totype(ctx, cf->type, DP(abr)->this_cid);
		if(checkClosure && !knh_type_isClosure(ctx, type)) goto L_SCRIPT;
		knh_Token_toFIELD(ctx, tk, type, idx);
		return 1;
	}

	if(FIELDN_IS_SUPER(fnq)) goto L_ERROR;

	L_SCRIPT:;
	{
		Script *scr = knh_getAsmScript(ctx);
		idx = knh_Class_queryField(ctx, knh_Object_cid(scr), fnq);
		if(idx != -1) {
			knh_cfield_t *cf = knh_Class_fieldAt(ctx, knh_Object_cid(scr), idx);
			knh_type_t type = knh_pmztype_totype(ctx, cf->type, knh_Object_cid(scr));
			if(checkClosure && !knh_type_isClosure(ctx, type)) goto L_ERROR;
			knh_Token_toSCRIPT(ctx, tk, type, idx);
			return knh_Asm_globalIndex(ctx, abr, scr);
		}
	}

	if(!checkClosure) {
		Method *mtd = knh_NameSpace_findFuncMethod(ctx, ns, DP(abr)->this_cid, FIELDN_UNMASK(fnq));
		if(IS_NOTNULL(mtd)) {
			knh_Token_toCLOSURE(ctx, tk, mtd);
			return 1;
		}
		if(knh_Token_toSYSVAL(ctx, tk, abr)) {
			return 1;
		}
	}

	L_ERROR:;
	if(!checkClosure) {
		knh_Token_perror(ctx, tk, KERR_ERROR, _("undefined variable: %s"), sToken(tk));
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static
int knh_TokenCONSTN_typing(Ctx *ctx, Token *tk, Asm *abr, NameSpace *ns, int isVerbose)
{
	if(knh_Token_toSYSVAL(ctx, tk, abr)) {
		return 1;
	}
	else {
		Object *value = knh_NameSpace_getConstNULL(ctx, ns, knh_Token_tobytes(ctx, tk));
		if(value != NULL) {
			knh_Token_setCONST(ctx, tk, value);
			return 1;
		}
	}
	if(isVerbose) {
		knh_Token_perror(ctx, tk, KERR_ERROR, _("unknown constant: %s"), sToken(tk));
	}
	return 0;
}

/* ======================================================================== */
/* [CLASSID] */

static
void knh_Token_toCLASSID(Ctx *ctx, Token *o, knh_class_t cid)
{
	KNH_ASSERT_cid(cid);
	TT_(o) = TT_CLASSID;
	DP(o)->cid = cid;
	DP(o)->type = NNTYPE_Class;
	KNH_SETv(ctx, DP(o)->data, new_Class(ctx, cid));
}

/* ------------------------------------------------------------------------ */

static
int knh_TokenTYEPN_typing(Ctx *ctx, Token *tk, Asm *abr, NameSpace *ns)
{
	knh_class_t cid = knh_Token_getcid(ctx, tk, ns, CLASS_unknown);
	if(cid == CLASS_unknown) {
		knh_Token_perror(ctx, tk, KERR_ERROR, _("unknown class: %s"), sToken(tk));
		return 0;
	}
	knh_Token_toCLASSID(ctx, tk, cid);
	return 1;
}

/* ------------------------------------------------------------------------ */

static
int knh_TokenCMETHODN_typing(Ctx *ctx, Token *tk, NameSpace *ns, int isVerbose)
{
	knh_bytes_t t = knh_Token_tobytes(ctx, tk);
	knh_index_t idx = knh_bytes_rindex(t, '.');
	knh_bytes_t cname = knh_bytes_first(t, idx);
	knh_class_t cid = knh_NameSpace_getcid(ctx, ns, cname);
	Method *mtd = NULL;
	if(cid == CLASS_unknown) {
		if(isVerbose) {
			knh_Token_perror(ctx, tk, KERR_ERROR, _("unknown class: %s"), sToken(tk));
		}
		return 0;
	}
	t = knh_bytes_last(t, idx+1);
	mtd = knh_Class_getMethod(ctx, cid, knh_getmn(ctx, t, METHODN_NONAME));
	if(IS_NULL(mtd)) {
		if(isVerbose) {
			knh_Token_perror(ctx, tk, KERR_ERROR, _("undefined method: %s"), sToken(tk));
		}
		return 0;
	}
	knh_Token_setCONST(ctx, tk, UP(mtd));
	return 1;
}

/* ------------------------------------------------------------------------ */
/* [NUM] */

static
knh_class_t knh_Token_tagcNUM(Ctx *ctx, Token *tk, knh_class_t reqc, NameSpace *ns)
{
	knh_bytes_t t = knh_Token_tobytes(ctx, tk), tag = STEXT("");
	size_t i = 1;
	int ishex = 0;
	if(t.buf[0] == '0' && (t.buf[1] == 'x' || t.buf[1] == 'b')) {
		i = 2;
		ishex = 1;
		knh_foundKonohaStyle(1);
	}
	for(; i < t.len; i++) {
		if(isdigit(t.buf[i]) || t.buf[i] == '_' || t.buf[i] == '.') continue;
		if(t.buf[i] == '[') {
			int loc;
			tag.buf = t.buf + i + 1;
			tag.len = t.len - (i + 1);
			loc = knh_bytes_index(tag, ']');
			if(loc > 0) {
				tag = knh_bytes_first(tag, loc);
			}
			break;
		}
		else if(t.buf[i] == ':') {
			tag.buf = t.buf + i + 1;
			tag.len = t.len - (i + 1);
			break;
		}
		else {
			if((t.buf[i] == 'E' || t.buf[i] == 'e')) {
				if(isdigit(t.buf[i+1]) || t.buf[i+1] == '-') {
					i++;
					continue;
				}
			}
			tag.buf = t.buf + i;
			tag.len = t.len - (i);
			break;
		}
	}
	//DBG2_P("TAG %s, %d", tag.buf, tag.len);
	if(tag.len == 0 || ishex) {
		return reqc;
	}
	else {
		knh_class_t tagc = knh_NameSpace_tagcid(ctx, ns, reqc, tag);
		if(tagc == CLASS_unknown) {
			knh_Token_perror(ctx, tk, KERR_DWARN, _("unknown class tag: %s"), sToken(tk));
			return reqc;
		}
		knh_foundKonohaStyle(1);
		return tagc;
	}
}

/* ------------------------------------------------------------------------ */

static
knh_class_t knh_bytes_guessNUMcid(Ctx *ctx, knh_bytes_t t)
{
	size_t i;
	if(t.buf[0] == 0 && (t.buf[1] == 'x' || t.buf[1]=='b')) {
		return CLASS_Int;
	}
	for(i = 1; i < t.len; i++) {
		if(t.buf[i] == '_') {
#ifdef CLASS_Decimal
			return CLASS_Decimal;
#endif
		}
		else if(t.buf[i] == '.') {
			return CLASS_Float;
		}
		if(!isdigit(t.buf[i])) break;
	}
	return CLASS_Int;
}

/* ------------------------------------------------------------------------ */

static
int knh_TokenNUM_typing(Ctx *ctx, Token *tk, NameSpace *ns, knh_class_t reqc)
{
	KNH_ASSERT_cid(reqc);
	knh_bytes_t t = knh_Token_tobytes(ctx, tk);
	knh_class_t breqc = ctx->share->ClassTable[reqc].bcid;
	//DBG2_P("reqc=%s", CLASSN(breqc));

	if(breqc == CLASS_Boolean) {
		if(t.buf[0] == '0') {
			knh_Token_perror(ctx, tk, KERR_ERRATA, _("false is much better than: %B"), t);
			knh_Token_setCONST(ctx, tk, KNH_FALSE);
		}
		else {
			knh_Token_perror(ctx, tk, KERR_ERRATA, _("true is much better than: %B"), t);
			knh_Token_setCONST(ctx, tk, KNH_TRUE);
		}
		return 1;
	}

	if(breqc == CLASS_Int || breqc == CLASS_Float) {

	}
	else if(breqc == CLASS_Any || breqc == CLASS_Object || breqc == CLASS_Number) {
		breqc = knh_bytes_guessNUMcid(ctx, t);
		reqc = breqc;
	}
	else {
		knh_Token_perror(ctx, tk, KERR_TERROR, _("not numeric: %C"), reqc);
		return 0;
	}

	if(breqc == CLASS_Float) {
		knh_float_t n = 0.0;
		if(!knh_bytes_parsefloat(t, &n)) {
			knh_Token_perror(ctx, tk, KERR_EWARN, _("float overflow: %B"), t);
		}
		knh_class_t tagc = knh_Token_tagcNUM(ctx, tk, reqc, ns);
		ClassSpec *u = knh_getClassSpec(ctx, tagc);
		if(!DP(u)->ffchk(u, n)) {
			knh_Token_perror(ctx, tk, KERR_ERRATA, _("%C: out of range: %B ==> %O"), tagc, t, DP(u)->fvalue);
			knh_Token_setCONST(ctx, tk, UP(DP(u)->fvalue));
		}
		else {
			knh_Token_setCONST(ctx, tk, UP(new_FloatX(ctx, tagc, n)));
		}
	}
	else { /* if(req_bcid == CLASS_Int) */
		knh_int_t n = 0;
		if(!knh_bytes_parseint(t, &n)) {
			knh_Token_perror(ctx, tk, KERR_EWARN, _("int overflow: %B"), t);
		}
		knh_class_t tagc = knh_Token_tagcNUM(ctx, tk, reqc, ns);
		ClassSpec *u = knh_getClassSpec(ctx, tagc);
		if(!DP(u)->fichk(u, n)) {
			knh_Token_perror(ctx, tk, KERR_ERRATA, _("%C: out of range: %B ==> %O"), tagc, t, DP(u)->ivalue);
			knh_Token_setCONST(ctx, tk, UP(DP(u)->ivalue));
		}
		else {
			knh_Token_setCONST(ctx, tk, UP(new_IntX(ctx, tagc, n)));
		}
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

static
int knh_TokenSTR_typing(Ctx *ctx, Token *tk, NameSpace *ns, knh_class_t reqt)
{
	knh_class_t reqc = CLASS_type(reqt);
	if(reqc == CLASS_String || reqc == CLASS_Object || reqc == CLASS_Any) {
		KNH_ASSERT(IS_String(DP(tk)->data));
		knh_Token_toCONST(ctx, tk);
		return 1;
	}
	else if(reqc == CLASS_Exception) {
		knh_Token_setCONST(ctx, tk, UP(new_Exception(ctx, DP(tk)->text)));
		return 1;
	}
	else {
		knh_class_t breqc = ctx->share->ClassTable[reqc].bcid;
		if(breqc == CLASS_String) {
			knh_bytes_t t = knh_Token_tobytes(ctx, tk);
			ClassSpec *u = knh_getClassSpec(ctx, reqc);
			int foundError = 0;
			String *s = DP(u)->fsnew(ctx, reqc, t, NULL, &foundError);
			if(foundError) {
				knh_Token_perror(ctx, tk, KERR_TERROR, _("invalid string: %O of %C"), DP(tk)->data, reqc);
				return 0;
			}
			knh_Token_setCONST(ctx, tk, UP(s));
			return 1;
		}
	}
	knh_Token_perror(ctx, tk, KERR_TERROR, _("not string: %C"), reqc);
	return 0;
}

/* ------------------------------------------------------------------------ */

static
int knh_TokenTSTR_typing(Ctx *ctx, Token *tk, NameSpace *ns, knh_class_t reqt)
{
	knh_bytes_t t = knh_Token_tobytes(ctx, tk), tag;
	if(CLASS_type(reqt) == CLASS_Int && t.len == 1) {
		/* 'A' ==> int if int requested */
		knh_Token_setCONST(ctx, tk, UP(new_Int(ctx, (int)t.buf[0])));
		return 1;
	}
	if(!knh_bytes_splitTag(t, &tag, &t)) {
		KNH_ASSERT(IS_String(DP(tk)->data));
		return knh_TokenSTR_typing(ctx, tk, ns, reqt);
	}
	else if(knh_bytes_endsWith(tag, STEXT("!!"))) {
		knh_Token_setCONST(ctx, tk, UP(new_Exception(ctx, DP(tk)->text)));
	}
	else {
		knh_class_t tagcid = knh_NameSpace_tagcid(ctx, ctx->share->mainns, CLASS_String, tag);
		if(tagcid != CLASS_unknown) {
			ClassSpec *u = knh_getClassSpec(ctx, tagcid);
			int foundError = 0;
			String *s = DP(u)->fsnew(ctx, tagcid, t, NULL, &foundError);
			knh_Token_setCONST(ctx, tk, UP(s));
			if(foundError) {
				knh_Token_perror(ctx, tk, KERR_TERROR, _("invalid string: '%B:%B' of %C"), tag, t, tagcid);
				return 0;
			}
		}
		else {
			knh_Token_setCONST(ctx, tk, new_Object_parseOf(ctx, (String*)DP(tk)->data));
		}
	}
	knh_foundKonohaStyle(1);
	return 1;
}

/* ------------------------------------------------------------------------ */
/* [typing_Token] */

static
int knh_Token_typing(Ctx *ctx, Token *tk, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	if(TT_(tk) != TT_ASIS && knh_Token_isTyped(tk)) return 1;
	knh_class_t reqc = CLASS_type(reqt);

	switch(TT_(tk)) {
	case TT_CID:
	case TT_TYPEN:
		return knh_TokenTYEPN_typing(ctx, tk, abr, ns);
	case TT_CCONSTN:
	case TT_CONSTN:
		return knh_TokenCONSTN_typing(ctx, tk, abr, ns, 1/*isVerbose*/);

	case TT_FN :
	case TT_NAME:
		return knh_TokenNAME_typing(ctx, tk, abr, ns, 0/*checkClosure*/);
	case TT_NUM:
		return knh_TokenNUM_typing(ctx, tk, ns, reqc);
	case TT_CMETHODN:
		return knh_TokenCMETHODN_typing(ctx, tk, ns, 1/*isVerbose*/);

	case TT_URN:
		KNH_ASSERT(IS_String(DP(tk)->data));
		knh_Token_toCONST(ctx, tk);
		return 1;

	case TT_ESTR:
	case TT_STR:
		return knh_TokenSTR_typing(ctx, tk, ns, reqt);

	case TT_TSTR:
		return knh_TokenTSTR_typing(ctx, tk, ns, reqt);

	case TT_ASIS:
		/* This is used in DECL for default value */
		DP(tk)->cid  = reqc;
		DP(tk)->type = reqt;
		return 1;

	default:
		DBG2_P("unknown tt=%s", knh_token_tochar(TT_(tk)));
	}
	knh_Token_perror(ctx, tk, KERR_ERROR, _("untyped token: %s"), sToken(tk));
	return 0;
}

/* ======================================================================== */
/* [ESTR] */

static int knh_ismtchar(int c)
{
	return isalnum(c);
}

/* ------------------------------------------------------------------------ */

int knh_bytes_findMT(Ctx *ctx, knh_bytes_t text, knh_bytes_t *mt, knh_bytes_t *expr, knh_bytes_t *next)
{
	int i;
	mt->buf = (knh_uchar_t*)""; mt->len = 0;
	expr->buf = (knh_uchar_t*)""; expr->len = 0;
	next->buf = (knh_uchar_t*)""; next->len = 0;

	for(i = 0; i < (int)text.len - 1; i++) {
		if(text.buf[i] == '%') {
			i++;
			if(knh_ismtchar(text.buf[i])) {
				mt->buf = text.buf + (i);
				goto L_MT;
			}
		}
	}
	return 0;

	L_MT:;
	for(; i < (int)text.len - 1; i++) {
		if(knh_ismtchar(text.buf[i])) {
			mt->len += 1; continue;
		}
		if(text.buf[i] == '{') {
			i++;
			goto L_EXPR;
		}
		break;
	}
	next->buf = text.buf + i;
	next->len = text.len - i;
	return 0;

	L_EXPR: {
		int level = 1;
		expr->buf = text.buf + i;
		for(; i < text.len; i++) {
			if(text.buf[i] == '}') {
				level--;
				if(level == 0) {
					if(i + 1 < text.len) {
						next->buf = text.buf + (i+1);
						next->len = text.len - (i+1);
					}
					return 1;
				}
			}
			expr->len += 1;
			if(text.buf[i] == '{') level++;
		}
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static
Stmt *knh_bytes_parseExpr(Ctx *ctx, knh_bytes_t expr, int uri, int line)
{
	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
	knh_Bytes_write(ctx, cwb->ba, expr);
	knh_Bytes_putc(ctx, cwb->ba, ';');
	{
		InputStream *in = new_BytesInputStream(ctx, cwb->ba, cwb->pos, knh_Bytes_size(cwb->ba));
		DP(in)->uri = (knh_uri_t)uri;
		DP(in)->line = line;
		Stmt *stmt = knh_InputStream_parseStmt(ctx, in, 0/*isData*/);
		knh_cwb_close(cwb);
		return stmt;
	}
}

/* ------------------------------------------------------------------------ */

static
Term *knh_TokenESTR_toTerm(Ctx *ctx, Token *tk, Asm *abr)
{
	knh_bytes_t text = knh_Token_tobytes(ctx, tk);
	knh_bytes_t mt, expr, next;
	int res = knh_bytes_findMT(ctx, text, &mt, &expr, &next);
	if(res == 0) {
		TT_(tk) = TT_STR;
		return TM(tk);
	}
	else {
		knh_sfp_t *lsfp = KNH_LOCAL(ctx);
		KNH_LPUSH(ctx, KNH_NULL);   // lsfp[0]
		Stmt *stmt = new_Stmt(ctx, 0, STT_OP);
		Token *tkop = new_Token(ctx, 0, SP(tk)->uri, SP(tk)->line, TT_ADD);
		knh_Stmt_add(ctx, stmt, TM(tkop));
		while(res) {
			//DBG2_P("mt='%s', len=%d", mt.buf, mt.len);
			//DBG2_P("expr='%s', len=%d", expr.buf, expr.len);
			//DBG2_P("next='%s', len=%d", next.buf, next.len);
			text.len = (mt.buf - text.buf) - 1;
			if(text.len > 0) {
				knh_Stmt_add(ctx, stmt, new_TermCONST(ctx, FL(tk), UP(new_String(ctx, text, NULL))));
			}
			Stmt *stmt_expr = knh_bytes_parseExpr(ctx, expr, SP(tk)->uri, SP(tk)->line);
			KNH_SETv(ctx, lsfp[0].o, stmt_expr);
			if(knh_stmt_isExpr(SP(stmt_expr)->stt)) {
				Stmt *stmt_mt = new_Stmt(ctx, 0, STT_MT);
				knh_Stmt_add(ctx, stmt, TM(stmt_mt));
				tkop = new_Token(ctx, 0, SP(tk)->uri, SP(tk)->line, TT_MT);
				KNH_SETv(ctx, DP(tkop)->data, new_String(ctx, mt, NULL));
				knh_Stmt_add(ctx, stmt_mt, TM(tkop));
				knh_Stmt_add(ctx, stmt_mt, TM(stmt_expr));
			}
			else {
				knh_Asm_perror(ctx, abr, KERR_ERROR, _("some expression is needed: {%B}"), expr);
			}
			text = next;
			res = knh_bytes_findMT(ctx, text, &mt, &expr, &next);
		}
		if(text.len > 0) {
			knh_Stmt_add(ctx, stmt, new_TermCONST(ctx, FL(tk), UP(new_String(ctx, text, NULL))));
		}
		KNH_LOCALBACK(ctx, lsfp);
		knh_foundKonohaStyle(1);
		return TM(stmt);
	}
}

/* ======================================================================== */
/* [TERMs] */

int TERMs_isCONST(Stmt *stmt, size_t n)
{
	Token *tk = DP(stmt)->tokens[n];
	return (IS_Token(tk) && (TT_(tk) == TT_CONST));
}

/* ------------------------------------------------------------------------ */

static Object *TERMs_const(Stmt *stmt, size_t n)
{
	KNH_ASSERT(TERMs_isCONST(stmt, n));
	Token *tk = DP(stmt)->tokens[n];
	return DP(tk)->data;
}

/* ------------------------------------------------------------------------ */

static int TERMs_isNULL(Ctx *ctx, Stmt *stmt, size_t n)
{
	if(n < DP(stmt)->size) {
		Token *tk = DP(stmt)->tokens[n];
		return (IS_Token(tk) && TT_(tk) == TT_CONST && IS_NULL(DP(tk)->data));
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

int TERMs_isTRUE(Stmt *stmt, size_t n)
{
	if(n < DP(stmt)->size) {
		return (IS_Token(DP(stmt)->tokens[n]) && IS_TRUE(DP(DP(stmt)->tokens[n])->data));
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

int TERMs_isFALSE(Stmt *stmt, size_t n)
{
	if(n < DP(stmt)->size) {
		return (IS_Token(DP(stmt)->tokens[n]) && IS_FALSE(DP(DP(stmt)->tokens[n])->data));
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static Object *TERMs_value(Ctx *ctx, Stmt *stmt, size_t n, knh_type_t type)
{
	Token *tk = DP(stmt)->tokens[n];
	if(IS_Token(tk)) {
		if(TT_(tk) == TT_CONST) return DP(tk)->data;
		if(TT_(tk) == TT_ASIS) {
			return IS_NNTYPE(type) ?
					knh_getClassDefaultValue(ctx, CLASS_type(type)) : KNH_NULL;
		}
	}
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

int TERMs_isASIS(Stmt *stmt, size_t n)
{
	Token *tk = DP(stmt)->tokens[n];
	return (IS_Token(tk) && TT_(tk) == TT_ASIS);
}

/* ------------------------------------------------------------------------ */

static int TERMs_isCLASSID(Stmt *stmt, size_t n)
{
	Token *tk = DP(stmt)->tokens[n];
	return (IS_Token(tk) && TT_(tk) == TT_CLASSID);
}

/* ------------------------------------------------------------------------ */

#define _TERMs_getcid(stmt, n)    CLASS_type(TERMs_gettype(stmt, n))
#define _TERMs_getbcid(stmt, n)   ctx->share->ClassTable[TERMs_getcid(stmt,n)].bcid

knh_type_t TERMs_gettype(Stmt *stmt, size_t n)
{
	if(IS_Token(DP(stmt)->tokens[n])) {
		Token *tk = DP(stmt)->tokens[n];
		return DP(tk)->type;
	}
	else {
		Stmt *stmt2 = DP(stmt)->stmts[n];
		return DP(stmt2)->type;
	}
}

/* ------------------------------------------------------------------------ */

static
void TERMs_perrorTYPE(Ctx *ctx, Stmt *stmt, size_t n, knh_type_t reqt)
{
	knh_type_t type = TERMs_gettype(stmt, n);
	switch(SP(stmt)->stt) {
	case STT_CALL:
	case STT_NEW:
	case STT_OP:
	{
		Method *mtd = DP(DP(stmt)->tokens[0])->mtd;
		DBG2_ASSERT(IS_Method(mtd));
		knh_perror(ctx, SP(stmt)->uri, SP(stmt)->line,
				KERR_TERROR, _("%T must be %T at the parameter %d of %M"), type, reqt, n - 1, DP(mtd)->mn);
	}
	break;
	case STT_DECL:
	case STT_LET:
		knh_perror(ctx, SP(stmt)->uri, SP(stmt)->line,
				KERR_TERROR, _("%T must be %T at ="), type, reqt);
		break;
	default :
		knh_perror(ctx, SP(stmt)->uri, SP(stmt)->line,
				KERR_TERROR, _("%T must be %T at %s(%d)"), type, reqt, knh_stmt_tochar(SP(stmt)->stt), n);
	}
}

/* ======================================================================== */
/* [STMT] */

/* ------------------------------------------------------------------------ */
/* [DECL] */

static
knh_flag_t knh_StmtDECL_flag(Ctx *ctx, Stmt *o)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

static
knh_index_t knh_Asm_addVariableTable(Ctx *ctx, Asm *abr, knh_cfield_t *tbl, size_t max, knh_cfield_t *decl)
{
	DBG2_ASSERT(decl->fn != FIELDN_register);
	knh_index_t idx;
	if(decl->type == TYPE_var) {
		knh_foundKonohaStyle(1);
		DBG2_P("********* var %s", FIELDN(decl->fn));
	}
	for(idx = 0; idx < max - 1; idx++) {
		if(tbl[idx].fn == FIELDN_NONAME) {
			DBG2_ASSERT(tbl[idx].value == NULL);
			tbl[idx] = *decl;
			if(decl->value != NULL) {
				KNH_INITv(tbl[idx].value, decl->value);
			}
			if(tbl[idx].value == NULL && IS_NATYPE(tbl[idx].type)) {
				KNH_INITv(tbl[idx].value, KNH_NULL);
			}
#ifdef KNH_USING_UNBOXFIELD
			if((IS_ubxint(decl->type) && (sizeof(knh_int_t) > sizeof(void*))) ||
				(IS_ubxfloat(decl->type) && (sizeof(knh_float_t) > sizeof(void*)))) {
				tbl[idx+1].flag = 0;
				tbl[idx+1].type = TYPE_void;
				tbl[idx+1].type = FIELDN_register;
				DBG2_ASSERT(tbl[idx].value == NULL);
			}
#endif
			return idx;
		}
		if(tbl[idx].fn == decl->fn) {
			if(tbl[idx].type == decl->type) return idx;
			if(!knh_Context_isInteractive(ctx)) {
				knh_Asm_perror(ctx, abr, KERR_TERROR, _("differently declared: previous %T %N"), tbl->type, decl->fn);
				return -1;
			}
		}
	}
	knh_Asm_perror(ctx, abr, KERR_ERROR, _("too many declared variables: %d"), max);
	return -1;
}

static
knh_index_t knh_Asm_declareScriptVariable(Ctx *ctx, Asm *abr, knh_cfield_t *decl)
{
	knh_Script_t *scr = knh_getAsmScript(ctx);
	knh_class_t cid = knh_Object_cid(scr);
	knh_cfield_t *tbl = (ClassTable(cid).cstruct)->fields;
	knh_index_t idx = knh_Asm_addVariableTable(ctx, abr, tbl, KNH_SCRIPT_FIELDSIZE, decl);
	if(idx != -1) {
		knh_Object_t *value = decl->value;
#ifdef KNH_USING_UNBOXFIELD
		knh_type_t type = decl->type;
		if(IS_ubxint(type)) {
			knh_int_t *v = (knh_int_t*)(scr->fields + idx);
			v[0] = (value == NULL) ? 0 : ((Int*)value)->n.ivalue;
			return 1;
		}
		if(IS_ubxfloat(type)) {
			knh_float_t *v = (knh_float_t*)(scr->fields + idx);
#ifdef KNH_USING_NOFLOAT
			v[0] = (value == NULL) ? 0 : ((Float*)value)->n.fvalue;
#else
			v[0] = (value == NULL) ? 0.0 : ((Float*)value)->n.fvalue;
#endif
			return 1;
		}
		if(IS_ubxboolean(type)) {
			knh_bool_t *v = (knh_bool_t*)(scr->fields + idx);
			v[0] = (value == NULL) ? 0 : ((Int*)value)->n.bvalue;
			return 1;
		}
#endif/*KNH_USING_UNBOXFIELD*/
		if(value == NULL) {
			value = KNH_DEF(ctx, CLASS_type(type));
		}
		KNH_INITv(scr->fields[idx], value);
		return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static
knh_index_t knh_Asm_declareFieldVariable(Ctx *ctx, Asm *abr, knh_cfield_t *decl)
{
	knh_index_t idx =
		knh_Asm_addVariableTable(ctx, abr, DP(abr)->gamma, KONOHA_LOCALSIZE, decl);
	if(idx != -1) {
		knh_type_t type = decl->type;
#ifdef KNH_USING_UNBOXFIELD
		if(IS_ubxint(type) && (sizeof(knh_int_t) > sizeof(void*))) {
			if((idx + 1) > DP(abr)->gamma_size) {
				DP(abr)->gamma_size = (knh_ushort_t)(idx + 2);
			}
			return idx;
		}
		if(IS_ubxfloat(type) && sizeof(knh_float_t) > sizeof(void*)) {
			if((idx + 1) > DP(abr)->gamma_size) {
				DP(abr)->gamma_size = (knh_ushort_t)(idx + 2);
			}
			return idx;
		}
#endif/*KNH_USING_UNBOXFIELD*/
		if((idx + 1) > DP(abr)->gamma_size) {
			DP(abr)->gamma_size = (knh_ushort_t)(idx + 1);
		}
		return idx;
	}
	return -1;
}

/* ------------------------------------------------------------------------ */

static
knh_index_t knh_Asm_declareLocalVariable(Ctx *ctx, Asm *abr, knh_cfield_t *decl)
{
	knh_index_t idx =
		knh_Asm_addVariableTable(ctx, abr, (knh_cfield_t*)DP(abr)->gamma, KONOHA_LOCALSIZE, decl);
	if(idx != -1 && (idx + 1) > DP(abr)->gamma_size) {
		DP(abr)->gamma_size = (knh_ushort_t)(idx + 1);
	}
	return idx;
}

/* ------------------------------------------------------------------------ */

Term * knh_StmtDECL_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	int level = DP(abr)->level;
	knh_cfield_t declbuf, *decl = &declbuf;
	Token *tkN = StmtDECL_name(stmt);
	knh_fieldn_t fnq = knh_Token_getfnq(ctx, tkN);
	knh_type_t pmztype  = knh_Token_gettype(ctx, StmtDECL_type(stmt), ns, TYPE_var);

	decl->flag = knh_StmtDECL_flag(ctx, stmt);
	decl->fn  = FIELDN_UNMASK(fnq);
	decl->type = knh_pmztype_totype(ctx, pmztype, DP(abr)->this_cid);
	decl->value = NULL;

	if(decl->type == TYPE_var) {
		if(TERMs_isASIS(stmt, 2)) {
			if(level >= 0) {
				decl->type = TYPE_Any;
				knh_Asm_derivedVariable(ctx, abr, UP(tkN), decl->type);
			}
			else {
				knh_Token_toLOCAL(ctx, tkN, TYPE_var, 0);
				decl->value = (Object*)tkN;
				DP(tkN)->index = knh_Asm_declareLocalVariable(ctx, abr, decl);
			}
		}
		else if(TERMs_typing(ctx, stmt, 2, abr, ns, TYPE_Any, TWARN_)) {
			decl->type = TERMs_gettype(stmt, 2);
			knh_Asm_derivedVariable(ctx, abr, UP(tkN), decl->type);
			knh_foundKonohaStyle(1);
		}
		else {
			return NULL;
		}
	}
	else {
		if(TERMs_isNULL(ctx, stmt, 2)) {
			decl->type = NATYPE_cid(CLASS_type(decl->type));
			knh_Asm_derivedVariable(ctx, abr, UP(tkN), decl->type);
		}
		else if(TERMs_typing(ctx, stmt, 2, abr, ns, decl->type, TCHECK_)) {
			if(IS_NNTYPE(decl->type) && IS_NATYPE(TERMs_gettype(stmt, 2))) {
				decl->type = NATYPE_cid(CLASS_type(decl->type));
				knh_Asm_derivedVariable(ctx, abr, UP(tkN), decl->type);
			}
		}
		else {
			return NULL;
		}
	}

	//DBG2_P("LEVEL= %d type=%s%s, value=%p", level, TYPEQN(decl->type), decl->value);

	if(level == 0) {  /* SCRIPT VARIABLE */
		decl->flag |= KNH_FLAG_CFF_GETTER | KNH_FLAG_CFF_SETTER;
		decl->value = IS_NNTYPE(decl->type) ? NULL : KNH_NULL;
		if(!knh_Asm_declareScriptVariable(ctx, abr, decl)) {
			return NULL;
		}
	}
	else if(level == 1) { /* FIELD VARIABLE */
		if(!FIELDN_IS_U1(fnq)) {
			decl->flag |= KNH_FLAG_CFF_GETTER | KNH_FLAG_CFF_SETTER;
		}
		if(!TERMs_isCONST(stmt, 2) && !TERMs_isASIS(stmt, 2)) {
			knh_Asm_perror(ctx, abr, KERR_EWARN, _("%N must be initialized in constructor"), decl->fn);
		}
		else {
			decl->value = TERMs_value(ctx, stmt, 2, decl->type);
		}
		knh_Asm_declareFieldVariable(ctx, abr, decl);
		knh_Stmt_done(ctx, stmt);
		return TM(stmt);
	}
	else if(level == -1 || level == -2) {  /* -1 OUTER_PARAM, -2: INNER_PARAM */
		DBG2_P("PARAM %d type=%s%s, value=%p", level, TYPEQN(decl->type), decl->value);
		if(TERMs_isCONST(stmt, 2)) {
			decl->value = TERMs_const(stmt, 2);
			if(IS_NULL(decl->value)) {
				decl->type = NATYPE_cid(decl->type);
			}
		}
		DBG2_P("PARAM %d type=%s%s, value=%p", level, TYPEQN(decl->type), decl->value);
		if(level == -1) {  /* Outer Param */
			if(decl->value != NULL) {
				decl->type = NATYPE_cid(decl->type);
			}
		}
		knh_Asm_declareLocalVariable(ctx, abr, decl);
		return TM(stmt);
	}
	else {
		if(FIELDN_IS_U2(fnq)) {
			knh_Asm_perror(ctx, abr, KERR_ERRATA, _("__%N ==> local variable"), decl->fn);
		}
		if(FIELDN_IS_U1(fnq)) {
			knh_Asm_perror(ctx, abr, KERR_ERRATA, _("_%N ==> local variable"), decl->fn);
		}
		decl->value = IS_NNTYPE(decl->type) ? NULL : KNH_NULL;
		knh_Asm_declareLocalVariable(ctx, abr, decl);
	}
	if(TERMs_isASIS(stmt, 2)) {
		knh_Stmt_done(ctx, stmt);
	}
	else {
		DBG2_ASSERT(SP(stmt)->stt == STT_DECL); /* STT_DECL => STT_LET */
		SP(stmt)->stt = STT_LET;
		KNH_SETv(ctx, DP(stmt)->terms[0], DP(stmt)->terms[1]);
		KNH_SETv(ctx, DP(stmt)->terms[1], DP(stmt)->terms[2]);
		KNH_SETv(ctx, DP(stmt)->terms[2], KNH_NULL);
		DP(stmt)->size = 2;
		if(!TERMs_typing(ctx, stmt, 0, abr, ns, TYPE_Any, TWARN_)) {
			return NULL;
		}
		knh_Stmt_typed(ctx, stmt, TERMs_gettype(stmt, 0));
	}
	return TM(stmt);
}

/* ======================================================================== */
/* [LET] */

static
Term *knh_StmtLET_CONST(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, int level)
{
	Token *tkN = DP(stmt)->tokens[0];
	knh_bytes_t cn = knh_Token_tobytes(ctx, tkN);
	knh_class_t cid = CLASS_unknown;
	char *emsg = _("re-declaration of %s");
	if(TT_(tkN) == TT_CONSTN) {
		if(level != 0) {
			emsg = _("don't declare const HERE: %s");
			goto L_ERROR;
		}
		if(knh_Token_toSYSVAL(ctx, tkN, abr)) {
			return NULL;
		}
		if(knh_NameSpace_getConstNULL(ctx, ns, cn) != NULL) {
			goto L_ERROR;
		}
	}
	else if(TT_(tkN) == TT_CCONSTN) {
		int idx = knh_bytes_rindex(cn, '.');
		if(level != 0) {
			emsg = _("don't declare const HERE: %s");
			goto L_ERROR;
		}
		cid = knh_NameSpace_getcid(ctx, ns, knh_bytes_first(cn, idx));
		if(cid == CLASS_unknown) {
			emsg = _("unknown class: %s");
			goto L_ERROR;
		}
		if(knh_getClassConstNULL(ctx, cid, knh_bytes_last(cn, idx+1)) != NULL) {
			goto L_ERROR;
		}
	}
	else {
		return NULL;
	}

	if(!TERMs_typing(ctx, stmt, 1, abr, ns, TYPE_Any, TWARN_)) {
		return NULL;
	}
	else { /* STT_LET ==> STT_CALL */
		STT_(stmt) = STT_CALL;
		knh_Stmt_insert(ctx, stmt, 0, TM(new_TokenMN(ctx, FL(tkN), METHODN_setConst)));
		knh_Stmt_insert(ctx, stmt, 1, TM(new_TokenCONST(ctx, FL(tkN), UP(ns))));
		TT_(tkN) = TT_STR;
		//knh_Stmt_addT(ctx, stmtCALL, tkN);
		//knh_Stmt_add(ctx, stmtCALL, DP(stmt)->terms[1]);
		return knh_StmtCALL_typing(ctx, stmt, abr, ns, TYPE_void);
	}

	L_ERROR:;
	if(emsg != NULL) {
		knh_Token_perror(ctx, tkN, KERR_ERROR, emsg, sToken(tkN));
	}
	knh_Stmt_done(ctx, stmt);
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_Asm_existsName(Ctx *ctx, Asm *abr, knh_fieldn_t fnq)
{
	knh_index_t idx = -1;
	knh_fieldn_t fn = FIELDN_UNMASK(fnq);
	if(FIELDN_IS_U2(fnq)) goto L_GLOBAL;
	if(FIELDN_IS_U1(fnq)) goto L_FIELD;

	idx = knh_Asm_indexOfLocalVariable(abr, fn);
	if(idx != -1) return 1;

	L_FIELD:;
	idx = knh_Class_queryField(ctx, DP(abr)->this_cid, fnq);
	if(idx != -1) return 1;

	L_GLOBAL:;
	idx = knh_Class_queryField(ctx, knh_Object_cid(knh_getAsmScript(ctx)), fnq);
	if(idx != -1) return 1;
	return 0;
}

/* ------------------------------------------------------------------------ */

Term *knh_StmtLET_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	int level = DP(abr)->level;
	Term *tm = knh_StmtLET_CONST(ctx, stmt, abr, ns, level);
	if(tm != NULL) return tm;

	Token *tkN = DP(stmt)->tokens[0];
	if(knh_Token_isTyped(tkN)) {
		if(!TERMs_typing(ctx, stmt, 1, abr, ns, TERMs_gettype(stmt, 0), TCHECK_)) {
			return NULL;
		}
		return knh_Stmt_typed(ctx, stmt, TERMs_gettype(stmt, 0));
	}
	else if(knh_Token_isUntypedName(tkN)) {
		goto L_INFERTYPE;
	}
	else {
		knh_fieldn_t fnq = knh_Token_getfnq(ctx, tkN);
		int existsName = 0;
		if(level == 0) {  /* SCRIPT LEVEL */
			if(knh_Class_queryField(ctx, knh_Object_cid(knh_getAsmScript(ctx)), fnq) != -1) {
				existsName = 1;
			}
		}
		else if(level > 1) {  /* LOCAL LEVEL */
			if(knh_Asm_existsName(ctx, abr, fnq)) {
				existsName = 1;
			}
			else if(FIELDN_IS_U1(fnq) || FIELDN_IS_U2(fnq)) {
				knh_Token_perror(ctx, tkN, KERR_ERROR, _("undefined variable: %s"), sToken(tkN));
				return NULL;
			}
		}
		//DBG2_P("LEVEL=%d, existsName=%d", level, existsName);
		if(existsName == 0){   /* TYPE INFERENCING : a = 1 */
			STT_(stmt) = STT_DECL;
			knh_Stmt_addT(ctx, stmt, new_TokenASIS(ctx, FL(tkN)));
			knh_Stmt_swap(ctx, stmt, 0, 1);
			knh_Stmt_swap(ctx, stmt, 0, 2);
			return knh_StmtDECL_typing(ctx, stmt, abr, ns);
		}
		else {
			knh_type_t type;
			if(!TERMs_typing(ctx, stmt, 0, abr, ns, TYPE_Any, TWARN_)) {
				return NULL;
			}
			if(TT_(tkN) < TT_LOCAL && TT_(tkN) > TT_MEMBER) {
				knh_Asm_perror(ctx, abr, KERR_ERROR, _("not (l-value) variable: %s"), sToken(tkN));
				return NULL;
			}
			type = TERMs_gettype(stmt, 0);
			if(type == TYPE_var) {
				goto L_INFERTYPE;
			}
			if(!TERMs_typing(ctx, stmt, 1, abr, ns, type, TCHECK_)) {
				return NULL;
			}
			return knh_Stmt_typed(ctx, stmt, type);
		}
	}
	L_INFERTYPE: {
		knh_type_t itype;
		DBG2_ASSERT(DP(tkN)->type == TYPE_var);
		if(!TERMs_typing(ctx, stmt, 1, abr, ns, TYPE_Any, TWARN_)) {
			return NULL;
		}
		itype = TERMs_gettype(stmt, 1);
		if(itype != TYPE_var) {
			knh_Asm_derivedParamType(ctx, abr, tkN, itype);
			return knh_Stmt_typed(ctx, stmt, itype);
		}
	}
	return knh_Stmt_untyped(ctx, stmt, abr);
}

/* ------------------------------------------------------------------------ */

static
void knh_Asm_addDefaultReturnValue(Ctx *ctx, Asm *abr, Stmt *stmt, knh_type_t rtype)
{
	DBG2_ASSERT(SP(stmt)->stt == STT_RETURN)
	DBG2_ASSERT(DP(stmt)->size == 0);
	if(rtype != TYPE_void) {
		Token *tk = new_TokenNULL(ctx, FL(stmt), rtype);
		if(IS_NNTYPE(rtype)) {
			knh_Token_toDEFVAL(tk, CLASS_type(rtype));
		}
		knh_Stmt_add(ctx, stmt, TM(tk));
		knh_Asm_perror(ctx, abr, KERR_ERRATA,
			_("return default value of %C"), CLASS_type(rtype));
	}
}

static
Term *knh_StmtRETURN_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	knh_type_t rtype = DP(abr)->rtype;
	if(rtype == TYPE_var) {
		knh_type_t itype = TERMs_inferType(ctx, stmt, 0, abr, ns);
		if(itype == TYPE_var) {
			return knh_Stmt_untyped(ctx, stmt, abr);
		}
		knh_Asm_derivedReturnType(ctx, abr, DP(abr)->mtd, itype);
	}

	if(rtype == TYPE_void) {
		if(DP(stmt)->size > 0) {
			knh_Asm_perror(ctx, abr, KERR_ERRATA, _("return nothing"));
			DP(stmt)->size = 0;
		}
	}
	else if(knh_Method_isConstructor(ctx, DP(abr)->mtd)) {
		if(DP(stmt)->size > 0) {
			knh_Asm_perror(ctx, abr, KERR_ERRATA, _("return this"));
			DP(stmt)->size = 1;
		}
		else {
			Token *tk = new_TokenNULL(ctx, FL(stmt), rtype);
			knh_Stmt_add(ctx, stmt, TM(tk));
		}
		knh_Token_toSTACK(ctx, DP(stmt)->tokens[0], rtype, 0);
	}
	else if(DP(stmt)->size == 0) {
		knh_Asm_addDefaultReturnValue(ctx, abr, stmt, rtype);
	}
	else if(!TERMs_typing(ctx, stmt, 0, abr, ns, rtype, TCHECK_)){
		return NULL;
	}
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */
/* [CALL1] */

static
Term *knh_StmtCALL1_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	DBG2_ASSERT(DP(stmt)->size == 1);
	if(reqt == TYPE_void) {
		if(IS_NULL(DP(stmt)->next)) {
			STT_(stmt) = STT_RETURN;
			knh_foundKonohaStyle(1);
			return knh_StmtRETURN_typing(ctx, stmt, abr, ns);
		}
		knh_Asm_perror(ctx, abr, KERR_DWARN, _("no effect"));
//		if(TERMs_typing(ctx, stmt, 0, abr, ns, TYPE_Any, TWARN_)) {
//			return knh_Stmt_typed(ctx, stmt, TERMs_gettype(stmt, 0));
//		}
		return knh_Stmt_done(ctx, stmt);
	}
	else {
		TERMs_typing(ctx, stmt, 0, abr, ns, reqt, TCHECK_);
		return DP(stmt)->terms[0];
	}
}

/* ------------------------------------------------------------------------ */
/* [CALL] */

static
void KNH_BOX(Ctx *ctx, knh_sfp_t *sfp, knh_type_t type)
{
	knh_class_t cid = CLASS_type(type);
	KNH_ASSERT_cid(cid);
	knh_class_t bcid = ClassTable(cid).bcid;
	if(bcid == CLASS_Int || bcid == CLASS_Float || bcid == CLASS_Boolean) {
		if(IS_NNTYPE(type) || IS_NOTNULL(sfp[0].o)) {
			KNH_SETv(ctx, sfp[0].o, new_Object_boxing(ctx, cid, sfp));
		}
	}
}

/* ------------------------------------------------------------------------ */

static void KNH_UNBOX(Ctx *ctx, knh_sfp_t *sfp)
{
	sfp[0].data = (sfp[0].i)->n.ivalue;
}

/* ------------------------------------------------------------------------ */

static Term *knh_StmtCALL_toCONST(Ctx *ctx, Stmt *stmt, Method *mtd)
{
	if(!knh_Method_isConst(mtd)) return TM(stmt);
	if(DP(mtd)->mn == METHODN_isNull && IS_NNTYPE(TERMs_gettype(stmt, 1))) {
		return TM(new_TokenCONST(ctx, DP(stmt)->terms[0], KNH_FALSE));
	}
	if(DP(mtd)->mn == METHODN_isNotNull && IS_NNTYPE(TERMs_gettype(stmt, 1))) {
		return TM(new_TokenCONST(ctx, DP(stmt)->terms[0], KNH_TRUE));
	}

	knh_sfp_t *lsfp = KNH_LOCAL(ctx);
	int i;
	for(i = 1; i < DP(stmt)->size; i++) {
		Token *tk = DP(stmt)->tokens[i];
		if(!IS_Token(tk) || TT_(tk) != TT_CONST) {
			return TM(stmt);
		}
		KNH_MOV(ctx, lsfp[i].o, DP(tk)->data);
		KNH_UNBOX(ctx, &lsfp[i]);
	}
	DBG2_P("STMT TO CONST ..");
	KNH_SCALL(ctx, lsfp, 0, mtd, (DP(stmt)->size - 2));
	KNH_BOX(ctx, &lsfp[0], knh_Method_rztype(mtd));
	knh_Token_setCONST(ctx, DP(stmt)->tokens[0], lsfp[0].o);
	return DP(stmt)->terms[0];
}

/* ------------------------------------------------------------------------ */

static
void knh_Token_toMTD(Ctx *ctx, Token *tk, knh_methodn_t mn, Method *mtd)
{
	TT_(tk) = TT_MN;
	DP(tk)->mn = mn;
	KNH_SETv(ctx, DP(tk)->data, mtd);
	DP(tk)->type = TYPE_Method;
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtPARAMS_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_class_t mtd_cid, Method *mtd)
{
	size_t i, size = DP(stmt)->size;
	knh_type_t rtype = knh_pmztype_totype(ctx, knh_Method_rztype(mtd), mtd_cid);
	if(knh_Method_isUntyped(mtd)) {
		DBG2_ASSERT(mtd == DP(abr)->mtd); /* Recursive Call */
		if(!knh_Asm_updateMethodType(ctx, abr)) {
			if(knh_Method_psize(mtd) + 2 < size) {
				size = knh_Method_psize(mtd) + 2;
			}
			for(i = 2; i < size; i++) {
				knh_type_t reqt = knh_pmztype_totype(ctx, knh_Method_pztype(mtd, i - 2), mtd_cid);
				if(reqt == TYPE_var) {
					if(!TERMs_typing(ctx, stmt, i, abr, ns, TYPE_Any, TWARN_)) {
						return NULL;
					}
					reqt = TERMs_gettype(stmt, i);
					if(!TERMs_isNULL(ctx, stmt, i) && reqt != TYPE_var) {
						Token *tkVAR = knh_Asm_getUntypedName(ctx, abr, i);
						knh_Asm_derivedParamType(ctx, abr, tkVAR, reqt);
					}
				}
				else {
					if(!TERMs_typing(ctx, stmt, i, abr, ns, reqt, TCHECK_)) {
						return NULL;
					}
				}
			}
			if(!knh_Asm_updateMethodType(ctx, abr)) { /* recheck */
				return knh_Stmt_untyped(ctx, stmt, abr);
			}
		}
	}

	knh_Stmt_typed(ctx, stmt, rtype);
	for(i = 0; i < knh_Method_psize(mtd); i++) {
		knh_type_t reqt = knh_pmztype_totype(ctx, knh_Method_pztype(mtd, i), mtd_cid);
		size_t n = i + 2;
		if(n < size) {
			if(!TERMs_typing(ctx, stmt, n, abr, ns, reqt, TCHECK_)) {
				return NULL;
			}
		}
		else {
			if(IS_NNTYPE(reqt)) {
				knh_Asm_perror(ctx, abr, KERR_TERROR,
					_("too few parameters: %C.%M"), mtd_cid, DP(mtd)->mn);
				return NULL;
			}
			else if(!knh_Method_isVarArgs(mtd)) {
				knh_Stmt_addT(ctx, stmt, new_TokenNULL(ctx, UP(stmt), reqt));
			}
		}
	}
	if(knh_Method_isVarArgs(mtd)) {
		knh_type_t reqt = knh_pmztype_totype(ctx, knh_Method_pztype(mtd, knh_Method_psize(mtd) - 1), mtd_cid);
		for(i = knh_Method_psize(mtd); i + 2 < size; i++) {
			if(!TERMs_typing(ctx, stmt, i + 2, abr, ns, reqt, TCHECK_)) {
				return NULL;
			}
		}
	}
	else if(i + 2 < size) {
		knh_Asm_perror(ctx, abr, KERR_DWARN,
			_("too many parameters: %C.%M"), mtd_cid, DP(mtd)->mn);
		DP(stmt)->size = i + 2;
	}

	Term *tm = knh_StmtCALL_toCONST(ctx, stmt, mtd);
	if(tm != NULL) {
		if(knh_Stmt_isToReturn(stmt)) {
			if(IS_Token(tm) || (STT_(stmt) == STT_CALL && METHODN_IS_GETTER(DP(mtd)->mn))
				|| STT_(stmt) == STT_NEW || STT_(stmt) == STT_OP) {
					Stmt *stmtRETURN = new_Stmt(ctx, 0, STT_RETURN);
					knh_Stmt_add(ctx, stmtRETURN, TM(stmt));
					knh_StmtRETURN_typing(ctx, stmtRETURN, abr, ns);
					knh_foundKonohaStyle(1);
					return TM(stmtRETURN);
			}
		}
		if(STT_(stmt) == STT_CALL && IS_Stmt(tm) && knh_methodn_isNew(ctx, DP(mtd)->mn)) {
			knh_Stmt_typed(ctx, stmt, TYPE_void);
		}
	}
	return tm;
}


/* ------------------------------------------------------------------------ */

static
Term *knh_StmtINVOKE_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	knh_class_t cid = TERMs_getcid(stmt, 0);
	KNH_ASSERT_cid(cid); DBG2_ASSERT(knh_type_isClosure(ctx, cid));
	/* 0 1 2 3 4 .. 5 */
	Method *mtd = knh_Class_getMethod(ctx, CLASS_Closure, METHODN_invoke);
	knh_Token_toMTD(ctx, DP(stmt)->tokens[1], METHODN_invoke, mtd);
	Token *tktemp = DP(stmt)->tokens[0];
	DP(stmt)->tokens[0] = DP(stmt)->tokens[1];
	DP(stmt)->tokens[1] = tktemp;

	if(cid == CLASS_Closure /* || DP(stmt)->size > 4 */) {
		size_t i;
		for(i = 0; i < DP(stmt)->size; i++) {
			if(!TERMs_typing(ctx, stmt, i, abr, ns, TYPE_Any, TWARN_)) {
				return NULL;
			}
		}
		return knh_Stmt_typed(ctx, stmt, TYPE_Any);
	}

	knh_Stmt_typed(ctx, stmt, ClassTable(cid).r0);

	if(ClassTable(cid).p1 != TYPE_void) {
		if(!(DP(stmt)->size > 2)) {
			knh_Stmt_add(ctx, stmt, UP(new_TokenNULL(ctx, FL(stmt), ClassTable(cid).p1)));
		}
		if(!TERMs_typing(ctx, stmt, 2, abr, ns, ClassTable(cid).p1, TCHECK_)) {
			return NULL;
		}
	}
	else {
		DP(stmt)->size = 2;
		return TM(stmt);
	}

	if(ClassTable(cid).p2 != TYPE_void) {
		if(!(DP(stmt)->size > 3)) {
			knh_Stmt_add(ctx, stmt, UP(new_TokenNULL(ctx, FL(stmt), ClassTable(cid).p2)));
		}
		if(!TERMs_typing(ctx, stmt, 3, abr, ns, ClassTable(cid).p2, TCHECK_)) {
			return NULL;
		}
	}
	else {
		DP(stmt)->size = 3;
		return TM(stmt);
	}

	if(ClassTable(cid).p3 != TYPE_void) {
		if(!(DP(stmt)->size > 4)) {
			knh_Stmt_add(ctx, stmt, UP(new_TokenNULL(ctx, FL(stmt), ClassTable(cid).p3)));
		}
		if(!TERMs_typing(ctx, stmt, 4, abr, ns, ClassTable(cid).p3, TCHECK_)) {
			return NULL;
		}
		DP(stmt)->size = 5;
		return TM(stmt);
	}
	else {
		DP(stmt)->size = 4;
		return TM(stmt);
	}
}

/* ------------------------------------------------------------------------- */

static
Term *knh_StmtCALLBASE_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_methodn_t mn)
{
	Token *tk1 = DP(stmt)->tokens[1];
	if(IS_Stmt(tk1) || TT_(tk1) != TT_ASIS) {
		if(!TERMs_typing(ctx, stmt, 1, abr, ns, CLASS_Any, TWARN_)) {
			return NULL;
		}
		if(TERMs_isCLASSID(stmt, 1)) {
			knh_Token_toDEFVAL(tk1, DP(tk1)->cid);
		}
		return TM(stmt);
	}

	/* (func _ ...) */
	/* built-in function */
	char *emsg = _("built-in function %s()");
	if(mn == METHODN_typeof) {
		if(DP(stmt)->size != 3) goto L_ERROR;
		if(TERMs_typing(ctx, stmt, 2, abr, ns, TYPE_Any, TWARN_)) {
			knh_Token_setCONST(ctx, tk1, UP(new_Type(ctx, TERMs_gettype(stmt, 2))));
			return TM(tk1);
		}
		return NULL;
	}
	else if(mn == METHODN_likely || mn == METHODN_unlikely) { /* likely() */
		if(DP(stmt)->size != 3) goto L_ERROR;
		if(TERMs_typing(ctx, stmt, 2, abr, ns, TYPE_Boolean, TCHECK_)) {
			return DP(stmt)->terms[2];
		}
		return NULL;
	}
	else if(mn == METHODN_format) {
		int i;
		for(i = 1; i < DP(stmt)->size-1; i++) {
			KNH_SETv(ctx, DP(stmt)->terms[i], DP(stmt)->terms[i+1]);
		}
		DP(stmt)->size -= 1;
		if(!TERMs_typing(ctx, stmt, 1, abr, ns, CLASS_String, TCHECK_)) {
			return NULL;
		}
		return TM(stmt);
	}
	else if(mn == METHODN_default) {
		if(DP(stmt)->size != 3) goto L_ERROR;
		if(TERMs_typing(ctx, stmt, 2, abr, ns, CLASS_Any, TWARN_)) {
			if(TERMs_isCLASSID(stmt, 2)) {
				tk1 = DP(stmt)->tokens[2];
				knh_Token_toDEFVAL(tk1, DP(tk1)->cid);
			}
			else {
				knh_Token_toDEFVAL(tk1, TERMs_getcid(stmt, 2));
			}
			return TM(tk1);
		}
		return NULL;
	}
	else if(mn == METHODN_domain) {
		if(DP(stmt)->size != 3) goto L_ERROR;
		if(TERMs_typing(ctx, stmt, 2, abr, ns, CLASS_Any, TWARN_)) {
			knh_class_t cid1;
			if(TERMs_isCLASSID(stmt, 2)) {
				cid1 = DP(DP(stmt)->tokens[2])->cid;
			}
			else {
				cid1 = TERMs_getcid(stmt, 2);
			}
			KNH_ASSERT_cid(cid1);
			knh_Token_setCONST(ctx, tk1, UP(new_Class(ctx, cid1)));
			DP(stmt)->size = 2;
			knh_Token_toMTD(ctx, DP(stmt)->tokens[0], METHODN_domain,
					knh_Class_getMethod(ctx, CLASS_Class, METHODN_domain));
			return knh_Stmt_typed(ctx, stmt,
					NNTYPE_cid(knh_class_Generics(ctx, CLASS_Array, cid1, CLASS_Any)));
		}
		return NULL;
	}
	else if(mn == METHODN_defined) {
		if(DP(stmt)->size != 3) goto L_ERROR;
		if(TERMs_typing(ctx, stmt, 2, abr, ns, CLASS_Any, TWARN_)) {
			knh_Token_setCONST(ctx, tk1, KNH_TRUE);
		}
		else {
			knh_Token_setCONST(ctx, tk1, KNH_FALSE);
		}
		return TM(tk1);
	}
	else if(mn == METHODN_super || mn == METHODN_this) {
		knh_class_t mtd_cid = DP(abr)->this_cid; /* CLASS_type(DP(abr)->vars[0].type)*/;
		Token *tkMTD = DP(stmt)->tokens[0]; /* change */
		Method *mtd;
		if(mn == METHODN_super) {
			KNH_ASSERT_cid(mtd_cid);
			if(ClassTable(mtd_cid).supcid == CLASS_Object) {
				knh_Asm_perror(ctx, abr,
					KERR_ERROR, _("not extended: %s"), CTXCLASSN(mtd_cid));
				return NULL;
			}
			mtd_cid = ClassTable(mtd_cid).supcid;
		}
		mtd = knh_Class_getMethod(ctx, mtd_cid, METHODN_new);
		if(IS_NULL(mtd) || DP(mtd)->cid != mtd_cid) {
			knh_Asm_perror(ctx, abr,
				KERR_ERROR, _("undefined constructor: %s"), CTXCLASSN(mtd_cid));
			return NULL;
		}
		knh_Token_toLOCAL(ctx, tk1, NNTYPE_cid(mtd_cid), 0); /* this */
		knh_Token_toMTD(ctx, tkMTD, METHODN_new, mtd);
		return TM(stmt);
	}
	else if(mn == METHODN_delegate) { /* delegate */
		if(DP(stmt)->size == 4) { /* delegate(a,f) */
			Token *tkF = DP(stmt)->tokens[3];
			if(!IS_Token(tkF)) goto L_ERROR;
			if(!TERMs_typing(ctx, stmt, 2, abr, ns, TYPE_Any, TWARN_)) {
				return NULL;
			}
			if(TERMs_isCLASSID(stmt, 2)) { /* delegate(Class, f) */
				Token *tkC = DP(stmt)->tokens[2];
				knh_Token_toDEFVAL(tkC, DP(tkC)->cid);
			}
			knh_class_t cid = TERMs_getcid(stmt, 2);
			knh_methodn_t mn = knh_Token_getmn(ctx, tkF);
			Method *mtd = knh_Class_getMethod(ctx, cid, mn);
			if(IS_NULL(mtd)) {
				knh_Asm_perror(ctx, abr,
					KERR_ERROR, _("undefined method: %s"), sToken(tkF));
				return NULL;
			}
			knh_Token_setCONST(ctx, DP(stmt)->tokens[3], UP(mtd));
			cid = knh_class_MethodClosure(ctx, cid, mtd);
			knh_Token_toCLASSID(ctx, tk1, cid);
			SP(stmt)->stt = STT_NEW;
			mtd = knh_Class_getMethod(ctx, CLASS_Closure, METHODN_new);
			KNH_ASSERT((IS_Method(mtd)));
			knh_Token_toMTD(ctx, DP(stmt)->tokens[0], mn, mtd);
			//DBG2_P("cid=%s", CLASSN(cid));
			return knh_Stmt_typed(ctx, stmt, NNTYPE_cid(cid));
		}
		else if(DP(stmt)->size == 3) { /* delegate(f) */
			Token *tkF = DP(stmt)->tokens[2];
			if(!IS_Token(tkF)) goto L_ERROR;
			Method *mtd = knh_NameSpace_findFuncMethod(ctx, ns, DP(abr)->this_cid, knh_Token_getmn(ctx, tkF));
			if(IS_NULL(mtd)) {
				knh_Asm_perror(ctx, abr,
					KERR_ERROR, _("undefined function: %s"), sToken(tkF));
				return NULL;
			}
			knh_Token_toCLOSURE(ctx, tkF, mtd);
			return TM(tkF);
		}
	}
//	else if(mn == METHODN_proceed) { /* proceed() */
//		knh_Asm_setPROCEED(abr, 1);
//		SP(stmt)->stt = STT_PROCEED;
//		Method *mtd = DP(abr)->mtd;
//		knh_Token_toMTD(ctx, DP(stmt)->tokens[0], DP(mtd)->mn, mtd);
//		knh_Token_toSTACK(ctx, tk1, 0, DP(abr)->vars[0].type);
//		if(DP(stmt)->size > 1) {
//			knh_StmtPARAMS_typing(ctx, stmt, abr, ns, CLASS_type(DP(abr)->vars[0].type), mtd);
//		}
//		knh_Stmt_setType(ctx, stmt, DP(abr)->rtype);
//		return TM(stmt);
//	}
	else {
		Method *mtd;
		if(knh_TokenNAME_typing(ctx, DP(stmt)->tokens[0], abr, ns, 1/*checkClosure*/)) {
			return knh_StmtINVOKE_typing(ctx, stmt, abr, ns);
		}
		mtd = knh_NameSpace_findFuncMethod(ctx, ns, DP(abr)->this_cid, mn);
		if(IS_NOTNULL(mtd)) {
			if(DP(mtd)->cid == DP(abr)->this_cid ||
				knh_class_instanceof(ctx, DP(abr)->this_cid, DP(mtd)->cid)) {
				knh_Token_toLOCAL(ctx, tk1, NNTYPE_cid(DP(abr)->this_cid), 0);
			}
			else if(DP(mtd)->cid == knh_Object_cid(knh_getAsmScript(ctx))) {
				knh_Token_setCONST(ctx, tk1, UP(knh_getAsmScript(ctx)));
			}
			else {  /* class function */
				knh_Token_toDEFVAL(tk1, DP(mtd)->cid);
			}
			knh_Token_toMTD(ctx, DP(stmt)->tokens[0], mn, mtd);
			return TM(stmt);
		}
		emsg = _("undefined function: %s");
	}

	L_ERROR:;
	knh_Asm_perror(ctx, abr, KERR_ERROR, emsg, sToken(DP(stmt)->tokens[0]));
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtCALL_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_class_t reqt)
{
	KNH_ASSERT(DP(abr)->this_cid == CLASS_type(DP(abr)->gamma[0].type));

	Token *tk0 = DP(stmt)->tokens[0];
	Method *mtd = NULL; knh_class_t mtd_cid;
	knh_methodn_t mn = knh_Token_getmn(ctx, tk0);

	if(mn == METHODN_new) {
		/* reported by Dr. Maeda */
		knh_Asm_perror(ctx, abr, KERR_ERROR, _("don't call a %M method"), mn);
		return NULL;
	}

	{
		Term *tm = knh_StmtCALLBASE_typing(ctx, stmt, abr, ns, mn);
		if(tm == NULL || IS_Token(tm) || knh_Stmt_isTyped((Stmt*)tm)) {
			return tm;
		}
	}

	if(TT_(tk0) == TT_MN && IS_Method(DP(tk0)->mtd)) {
		mtd = DP(tk0)->mtd;
		goto L_TYPING_PARAMS;
	}

//	if(mn == METHODN_super || mn == METHODN_this) {
//		mn = METHODN_new;
//	}

	mtd_cid = CLASS_type(TERMs_gettype(stmt, 1));
	if(mtd_cid == CLASS_type(TYPE_var)) {
		if(IS_Token(DP(stmt)->tokens[1])) {
			Token *tkVAR = DP(stmt)->tokens[1];
			DBG2_ASSERT(TT_(tkVAR) == TT_LOCAL || TT_(tkVAR) == TT_STACK);
			mtd_cid = knh_Token_unifyClass(ctx, tkVAR, reqt, stmt);
			if(mtd_cid != TYPE_var) {
				goto L_LOOKUPMETHOD;
			}
		}
		return TM(stmt);
	}

	L_LOOKUPMETHOD:;
	DBG2_ASSERT(mtd_cid != CLASS_type(TYPE_var));
	mtd = knh_Class_getMethod(ctx, mtd_cid, mn);
	if(mtd_cid != CLASS_Any && IS_NULL(mtd)) {
		knh_Asm_perror(ctx, abr, KERR_ERROR, _("undefined method: %C.%M"), mtd_cid, mn);
		return NULL;
	}
	knh_Token_toMTD(ctx, DP(stmt)->tokens[0], mn, mtd);

	if(IS_Token(DP(stmt)->tokens[1]) && knh_Token_isSUPER(DP(stmt)->tokens[1])) {
		knh_Token_setSUPER(tk0, 1);
	}

	L_TYPING_PARAMS:
	if(IS_NOTNULL(mtd) && knh_Method_rztype(mtd) == TYPE_var && reqt != TYPE_Any) {
		knh_Asm_derivedReturnType(ctx, abr, mtd, reqt);
	}
	if(IS_NULL(mtd)) {
		int i;
		for(i = 2; i < DP(stmt)->size; i++) {
			if(!TERMs_typing(ctx, stmt, i, abr, ns, TYPE_Any, TWARN_)) {
				return NULL;
			}
		}
		return knh_Stmt_typed(ctx, stmt, TYPE_Any);
	}
	return knh_StmtPARAMS_typing(ctx, stmt, abr, ns, mtd_cid, mtd);
}

/* ------------------------------------------------------------------------ */
/* [NEW] */

static
int knh_StmtPARAMs_findCommonClass(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_class_t *cdef)
{
	if(DP(stmt)->size > 1) {
		int i;
		knh_class_t ccid;
		if(!TERMs_typing(ctx, stmt, 2, abr, ns, CLASS_Any, TWARN_)) {
			return 0;
		}
		ccid = TERMs_getcid(stmt, 2);
		for(i = 3; i < DP(stmt)->size; i++) {
			knh_class_t cid;
			if(!TERMs_typing(ctx, stmt, i, abr, ns, CLASS_Any, TWARN_)) {
				return 0;
			}
			cid = TERMs_getcid(stmt, i);
			if(ccid != cid) {
				ccid = knh_class_parent(ctx, ccid, cid);
				if(ccid == CLASS_Object) return 1;  /* use default */
			}
		}
		*cdef = ccid;
	}
	return 1;
}

static
Term *knh_StmtNEW_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_class_t reqt)
{
	knh_class_t reqc = CLASS_type(reqt);
	Token *tkNEW = DP(stmt)->tokens[0];
	Token *tkC = DP(stmt)->tokens[1];
	knh_methodn_t mn = knh_Token_getmn(ctx, tkNEW);
	knh_class_t mtd_cid = knh_Token_getcid(ctx, tkC, ns, CLASS_unknown);
	KNH_ASSERT_cid(reqc);

	if(mtd_cid == CLASS_Object) {
		if(reqc != CLASS_Any) {
			mtd_cid = reqc;
			knh_Asm_derivedClass(ctx, abr, CLASS_Object, mtd_cid);
			knh_foundKonohaStyle(1);
		}
		else {
			knh_Token_perror(ctx, tkC, KERR_TERROR, _("needs class"));
			return NULL;
		}
	}

	if(mtd_cid == CLASS_unknown) {
		if(!IS_NNTYPE(reqt)) {
			knh_Token_perror(ctx, tkC, KERR_ERRATA, _("unknown class: %s ==> null"), sToken(tkC));
			return TM(new_TokenNULL(ctx, FL(tkC), reqt));
		}
		else {
			knh_Token_perror(ctx, tkC, KERR_ERROR, _("unknown class: %s"), sToken(tkC));
		}
		return NULL;
	}

	if(mtd_cid == CLASS_Pair) {
		knh_class_t bcid = ClassTable(reqc).bcid;
		if(bcid == CLASS_Pair) {
			mtd_cid = reqc;
			knh_Asm_derivedClass(ctx, abr, CLASS_Pair, mtd_cid);
		}
		else {
			if(!TERMs_typing(ctx, stmt, 2, abr, ns, TYPE_Any, TWARN_)
			|| !TERMs_typing(ctx, stmt, 3, abr, ns, TYPE_Any, TWARN_)) {
				return NULL;
			}
			knh_class_t p1 = TERMs_getcid(stmt, 2);
			knh_class_t p2 = TERMs_getcid(stmt, 3);
			mtd_cid = knh_class_Generics(ctx, CLASS_Pair, p1, p2);
			knh_Asm_derivedClass(ctx, abr, CLASS_Pair, mtd_cid);
		}
		knh_foundKonohaStyle(1);
		goto L_LOOKUPMETHOD;
	}

	if(mtd_cid == CLASS_Range) {
		knh_class_t bcid = ClassTable(reqc).bcid;
		knh_class_t ccid = CLASS_Any;
		if(bcid == CLASS_Range) {
			mtd_cid = reqc;
			knh_Asm_derivedClass(ctx, abr, CLASS_Range, mtd_cid);
		}
		else {
			if(knh_StmtPARAMs_findCommonClass(ctx, stmt, abr, ns, &ccid)) {
				if(ccid != CLASS_Any) {
					mtd_cid = knh_class_Generics(ctx, CLASS_Range, ccid, CLASS_unknown);
					knh_Asm_derivedClass(ctx, abr, CLASS_Range, mtd_cid);
				}
			}
			else {
				return NULL;
			}
		}
		knh_foundKonohaStyle(1);
		goto L_LOOKUPMETHOD;
	}

	if(mtd_cid == CLASS_Array) {
		knh_class_t bcid = ClassTable(reqc).bcid;
		if(bcid == CLASS_Array || bcid == CLASS_IArray || bcid == CLASS_FArray) {
			mtd_cid = reqc;
			knh_Asm_derivedClass(ctx, abr, CLASS_Array, mtd_cid);
			goto L_LOOKUPMETHOD;
		}
		if(mn == METHODN_new__array) {
			if(DP(stmt)->size == 4) mn = METHODN_new__array2D;
			if(DP(stmt)->size == 5) mn = METHODN_new__array3D;
			knh_foundKonohaStyle(1);
			goto L_LOOKUPMETHOD;
		}
		if(/*reqc == CLASS_Any && */ mn == METHODN_new__init) {
			knh_class_t ccid = CLASS_Any;
			if(knh_StmtPARAMs_findCommonClass(ctx, stmt, abr, ns, &ccid)) {
				if(ccid != CLASS_Any) {
					mtd_cid = knh_class_Array(ctx, CLASS_Array, ccid);
					knh_Asm_derivedClass(ctx, abr, CLASS_Array, mtd_cid);
				}
			}
			else {
				return NULL;
			}
			knh_foundKonohaStyle(1);
			goto L_LOOKUPMETHOD;
		}
	}

	if(mtd_cid == CLASS_Exception) {
		Token *tkE = new_TokenCONST(ctx, FL(stmt), DP(tkC)->data);
		mn = METHODN_new__init;
		knh_Stmt_insert(ctx, stmt, 2, TM(tkE));
		goto L_LOOKUPMETHOD;
	}

	L_LOOKUPMETHOD:
	KNH_ASSERT_cid(mtd_cid);
	{
		Method *mtd = knh_Class_getMethod(ctx, mtd_cid, mn);
		if(IS_NULL(mtd) || ClassTable(DP(mtd)->cid).bcid != ClassTable(mtd_cid).bcid) {
			knh_Asm_perror(ctx, abr, KERR_ERROR, _("unknown constructor: %s %C(...)"), sToken(tkNEW), mtd_cid);
			return NULL;
		}
		//DBG2_P("LOOKUP CONSTRUCTOR %s %s", CLASSN(mtd_cid), CLASSN(DP(mtd)->cid));
		DP(tkC)->cid = mtd_cid;
		knh_Token_toMTD(ctx, tkNEW, mn, mtd);
		return knh_StmtPARAMS_typing(ctx, stmt, abr, ns, mtd_cid, mtd);
	}
}

/* ======================================================================== */
/* [OP] */

/* ------------------------------------------------------------------------ */
//1 2 3 4  => (((1 + 2) + 3) + 4)

static
Term *knh_StmtTOBINARY_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	size_t i;
	while(DP(stmt)->size > 3) {
		Stmt *newstmt = new_Stmt(ctx, 0, STT_OP);
		knh_Stmt_add(ctx, newstmt, DP(stmt)->terms[0]);
		knh_Stmt_add(ctx, newstmt, DP(stmt)->terms[1]);
		knh_Stmt_add(ctx, newstmt, DP(stmt)->terms[2]);
		KNH_SETv(ctx, DP(stmt)->terms[1], newstmt);
		DP(stmt)->size -= 1;
		for(i = 2; i < DP(stmt)->size; i++) {
			KNH_SETv(ctx, DP(stmt)->terms[i], DP(stmt)->terms[i+1]);
		}
	}
	return knh_StmtEXPR_typing(ctx, stmt, abr, ns, reqt);
}

/* ------------------------------------------------------------------------ */

static
knh_class_t knh_StmtOPADD_basecid(Ctx *ctx, Stmt *stmt)
{
	KNH_ASSERT(DP(stmt)->size == 3);

	knh_class_t cid1 = TERMs_getcid(stmt, 1);
	knh_class_t cid2 = TERMs_getcid(stmt, 2);

	if(cid1 == CLASS_Any || cid2 == CLASS_Any) return CLASS_Any;
	if(cid1 == cid2) return cid1;

	knh_class_t bcid1 = ctx->share->ClassTable[cid1].bcid;
	knh_class_t bcid2 = ctx->share->ClassTable[cid2].bcid;

	if(bcid1 == bcid2) return bcid1;

	if(bcid1 == CLASS_Float && bcid2 == CLASS_Int) {
		return cid1;
	}
	if(bcid2 == CLASS_Float && bcid1 == CLASS_Int) {
		return cid2;
	}
	return cid1;
}

/* ------------------------------------------------------------------------ */

static
knh_class_t knh_StmtOPEQ_basecid(Ctx *ctx, Stmt *stmt)
{
	knh_class_t cid1 = TERMs_getcid(stmt, 1);
	knh_class_t cid2 = TERMs_getcid(stmt, 2);

	if(cid1 == cid2) return cid1;
	if(cid1 == CLASS_Any || cid2 == CLASS_Any) return CLASS_Any;

	knh_class_t bcid1 = ctx->share->ClassTable[cid1].bcid;
	knh_class_t bcid2 = ctx->share->ClassTable[cid2].bcid;

	if(bcid1 == cid2) return bcid1;
	if(bcid2 == cid1) return bcid2;

	if(bcid1 == CLASS_Float && bcid2 == CLASS_Int) {
		return cid1;
	}
	if(bcid2 == CLASS_Float && bcid1 == CLASS_Int) {
		return cid2;
	}
	return CLASS_unknown;
}

/* ------------------------------------------------------------------------ */

char *METHODN_op(knh_methodn_t mn)
{
	switch(mn) {
	case METHODN_opAdd : return "+";
	case METHODN_opAddr : return "&";
	case METHODN_opAs : return "as";
	case METHODN_opDiv : return "/";
	case METHODN_opEq : return "==";
	case METHODN_opGt : return "<";
	case METHODN_opGte : return "<=";
	case METHODN_opHas : return "in";
	case METHODN_opInTo : return "into";
	case METHODN_opInstanceof : return "instanceof";
	case METHODN_opIs : return "is";
	case METHODN_opIsa : return "isa";
	case METHODN_opItr : return "..";
	case METHODN_opLand : return "&& (and)";
	case METHODN_opLnot : return "~";
	case METHODN_opLor : return "|| (or)";
	case METHODN_opLshift : return ">>";
	case METHODN_opLt : return "<";
	case METHODN_opLte : return "<=";
	case METHODN_opMatch : return "=~";
	case METHODN_opMod : return "mod (%)";
	case METHODN_opMul : return "*";
	case METHODN_opNeg : return "-";
	case METHODN_opNeq : return "!=";
	case METHODN_opNext : return "++";
	case METHODN_opNot : return "! (not)";
	case METHODN_opPrev : return "--";
	case METHODN_opRangeTo : return "to";
	case METHODN_opRangeUntil : return "until";
	case METHODN_opRshift : return "<<";
	case METHODN_opSub : return "-";
	case METHODN_opTest : return "==>";
	case METHODN_opXor : return "^";
	}
	DBG2_P("unknown operator mn=%d", mn);
	return "";
}

/* ------------------------------------------------------------------------ */

static
int knh_Stmt_checkOPSIZE(Ctx *ctx, Stmt *stmt, size_t n, knh_methodn_t mn)
{
	if(DP(stmt)->size == n + 1) return 1;
	{
		Token *tkOP = DP(stmt)->tokens[0];
		char *emsg = _("%s must be binary operator");
		if(n == 1) {
			emsg = _("%s must be uniary operator");
		}
		else {
			DBG2_ASSERT(n == 2);
		}
		knh_Token_perror(ctx, tkOP, KERR_ERROR, emsg, METHODN_op(mn));
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static
int knh_Asm_isTypedBINARYOP(Ctx *ctx, Asm *abr, Stmt *stmt)
{
	DBG2_ASSERT(DP(stmt)->size == 3);
	knh_type_t t1 = TERMs_gettype(stmt, 1);
	knh_type_t t2 = TERMs_gettype(stmt, 2);
	if(t1 == TYPE_var) {
		if(t2 == TYPE_var || t2 == TYPE_Any) {
			return 0; // untyped
		}
		if(IS_Token(DP(stmt)->terms[1])) {
			Token *tkVAR = DP(stmt)->tokens[1];
			DBG2_ASSERT(knh_Token_isUntypedName(tkVAR));
			knh_Asm_derivedParamType(ctx, abr, tkVAR, t2);
			return 1;
		}
		return 0;
	}
	if(t2 == TYPE_var) {
		if(t1 == TYPE_Any) {
			return 0; // untyped
		}
		if(IS_Token(DP(stmt)->terms[2])) {
			Token *tkVAR = DP(stmt)->tokens[2];
			DBG2_ASSERT(knh_Token_isUntypedName(tkVAR));
			knh_Asm_derivedParamType(ctx, abr, tkVAR, t1);
			return 1;
		}
		return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtOP_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	size_t i, opsize = DP(stmt)->size - 1;
	Token *tkOP = DP(stmt)->tokens[0];
	knh_class_t mtd_cid = CLASS_unknown;
	knh_methodn_t mn = knh_token_tomethodn(TT_(tkOP));

	KNH_ASM_ASSERT(ctx, abr, mn != METHODN_NONAME);

	for(i = 1; i < opsize + 1; i++) {
		if(!TERMs_typing(ctx, stmt, i, abr, ns, TYPE_Any, TWARN_)) {
			return NULL;
		}
	}

	switch(mn) {
	case METHODN_opAdd:
	{
		if(opsize == 1) { /* +1 */
			return DP(stmt)->terms[1];
		}
		for(i = 1; i < opsize + 1; i++) {
			if(TERMs_getbcid(stmt, i) == CLASS_String) {
				mtd_cid = CLASS_String;
			}
		}
		if(mtd_cid == CLASS_String) {
			if(opsize > 2) {
				mn = METHODN_concat;
			}
			goto L_LOOKUPMETHOD;
		}
	}
	case METHODN_opSub:
	case METHODN_opMul:
	case METHODN_opDiv:
	{
		if(opsize > 2) {
			return knh_StmtTOBINARY_typing(ctx, stmt, abr, ns, reqt);
		}
		if(!knh_Stmt_checkOPSIZE(ctx, stmt, 2, mn)) {
			return NULL;
		}
		if(!knh_Asm_isTypedBINARYOP(ctx, abr, stmt)) {
			return knh_Stmt_untyped(ctx, stmt, abr);
		}
		mtd_cid = knh_StmtOPADD_basecid(ctx, stmt);
		goto L_LOOKUPMETHOD;
	}

	case METHODN_opEq:
	{
		if(!knh_Asm_isTypedBINARYOP(ctx, abr, stmt)) {
			return knh_Stmt_untyped(ctx, stmt, abr);
		}
		if(TERMs_isNULL(ctx, stmt, 1) || TERMs_isTRUE(stmt, 1) || TERMs_isFALSE(stmt, 1)) {
			knh_Stmt_swap(ctx, stmt, 1, 2);
		}
		if(TERMs_isNULL(ctx, stmt, 2)) { /* o == null */
			if(IS_NNTYPE(TERMs_gettype(stmt,1))) {
				return TM(new_TokenCONST(ctx, FL(stmt), KNH_FALSE));
			}
			mn = METHODN_isNull;
			mtd_cid = CLASS_Object;
			DP(stmt)->size = 2;
			goto L_LOOKUPMETHOD;
		}
		if(TERMs_isTRUE(stmt, 2)) {  /* b == true */
			if(TERMs_gettype(stmt, 1) == NNTYPE_Boolean) {
				return DP(stmt)->terms[1];
			}
		}
		if(TERMs_isFALSE(stmt, 2)) { /* b == false */
			if(TERMs_gettype(stmt, 1) == NNTYPE_Boolean) {
				mn = METHODN_opNot; mtd_cid = CLASS_Boolean;
				DP(stmt)->size = 2;
				goto L_LOOKUPMETHOD;
			}
		}
		mtd_cid = knh_StmtOPEQ_basecid(ctx, stmt);
		if(mtd_cid == CLASS_unknown) {
			knh_Asm_perror(ctx, abr, KERR_DWARN,
				_("comparison of different type: %T %T"), TERMs_gettype(stmt, 1), TERMs_gettype(stmt, 2));
			return new_TermCONST(ctx, FL(tkOP), KNH_FALSE); /* CONST */
		}
		goto L_LOOKUPMETHOD;
	}
	case METHODN_opNeq:
	{
		if(!knh_Asm_isTypedBINARYOP(ctx, abr, stmt)) {
			return knh_Stmt_untyped(ctx, stmt, abr);
		}
		if(TERMs_isNULL(ctx, stmt, 1) || TERMs_isTRUE(stmt, 1) || TERMs_isFALSE(stmt, 1)) {
			knh_Stmt_swap(ctx, stmt, 1, 2);
		}
		if(TERMs_isNULL(ctx, stmt, 2)) { /* o != null */
			if(IS_NNTYPE(TERMs_gettype(stmt,1))) {
				return TM(new_TokenCONST(ctx, FL(stmt), KNH_TRUE));
			}
			mn = METHODN_isNotNull; mtd_cid = CLASS_Object;
			DP(stmt)->size = 2;
			goto L_LOOKUPMETHOD;
		}
		if(TERMs_isTRUE(stmt, 2)) { /* b != true */
			if(TERMs_gettype(stmt, 1) == NNTYPE_Boolean) {
				mn = METHODN_opNot; mtd_cid = CLASS_Boolean;
				DP(stmt)->size = 2;
				goto L_LOOKUPMETHOD;
			}
		}
		if(TERMs_isFALSE(stmt, 2)) { /* b != false */
			if(TERMs_gettype(stmt, 1) == NNTYPE_Boolean) {
				return DP(stmt)->terms[1];
			}
		}
		mtd_cid = knh_StmtOPEQ_basecid(ctx, stmt);
		if(mtd_cid == CLASS_unknown) {
			knh_Asm_perror(ctx, abr, KERR_DWARN,
				_("comparison of different type: %T %T"), TERMs_gettype(stmt, 1), TERMs_gettype(stmt, 2));
			return new_TermCONST(ctx, FL(tkOP), KNH_TRUE); /* CONST */
		}
		goto L_LOOKUPMETHOD;
	}

	case METHODN_opGt: case METHODN_opGte:
	case METHODN_opLt: case METHODN_opLte:
	{
		if(!knh_Asm_isTypedBINARYOP(ctx, abr, stmt)) {
			return knh_Stmt_untyped(ctx, stmt, abr);
		}
		mtd_cid = knh_StmtOPEQ_basecid(ctx, stmt);
		if(mtd_cid == CLASS_unknown) {
			knh_Asm_perror(ctx, abr, KERR_TERROR,
				_("comparison of different type: %T %T"), TERMs_gettype(stmt, 1), TERMs_gettype(stmt, 2));
			return NULL;
		}
		goto L_LOOKUPMETHOD;
	}

	case METHODN_opHas:
	{
		DBG2_ASSERT(opsize == 2);
		knh_Stmt_swap(ctx, stmt, 1, 2);
		mtd_cid = TERMs_getcid(stmt, 1);
		goto L_LOOKUPMETHOD;
	}

	case METHODN_opLand:
	{
		if(opsize == 1) {
			mn = METHODN_opAddr;
			mtd_cid = CLASS_Object;
		}
		else {
			mtd_cid = TERMs_getcid(stmt, 1);
		}
		goto L_LOOKUPMETHOD;
	}

	default:
		mtd_cid = TERMs_getcid(stmt, 1);
		break;
	}

	L_LOOKUPMETHOD:;
	{
		Method *mtd = knh_Class_getMethod(ctx, mtd_cid, mn);
		if(IS_NULL(mtd)) {
			knh_Asm_perror(ctx, abr, KERR_ERROR,
				_("unsupported %s in %C"), METHODN_op(mn), mtd_cid);
			return NULL;
		}
		knh_Token_toMTD(ctx, DP(stmt)->tokens[0], mn, mtd);
		if(!TERMs_typing(ctx, stmt, 1, abr, ns, mtd_cid, TCHECK_)) {
			return NULL;
		}
		return knh_StmtPARAMS_typing(ctx, stmt, abr, ns, mtd_cid, mtd);
	}
}

/* ------------------------------------------------------------------------ */
/* [MAPCAST] */

static
void knh_Token_toMPR(Ctx *ctx, Token *tk, knh_class_t cid, Mapper *mpr)
{
	TT_(tk) = TT_MPR;
	DP(tk)->cid = cid;
	KNH_SETv(ctx, DP(tk)->data, mpr);
	if(IS_NULL(mpr)) {
		DP(tk)->type = NATYPE_cid(cid);
	}
	else {
		DP(tk)->type = knh_Mapper_isTotal(mpr) ? NNTYPE_cid(DP(mpr)->tcid) : NATYPE_cid(DP(mpr)->tcid);
	}
}

static
Term *knh_StmtMAPCAST_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	Token *tk0 = DP(stmt)->tokens[0];
	DBG2_ASSERT(DP(stmt)->size > 1);
	if(!TERMs_typing(ctx, stmt, 0, abr, ns, TYPE_Any, TWARN_)) {
		return NULL;
	}
	if(!TERMs_isCLASSID(stmt, 0)) {
		knh_Token_perror(ctx, tk0, KERR_ERROR, _("unknown class: %s"), sToken(tk0));
		return NULL;
	}

	if(!TERMs_typing(ctx, stmt, 1, abr, ns, TYPE_Any, TWARN_)) {
		return NULL;
	}

	knh_class_t mprcid = DP(tk0)->cid;
	knh_type_t  exprt = TERMs_gettype(stmt, 1);
	knh_class_t exprc = CLASS_type(exprt);
	int isNonNullCast = (knh_Token_isNotNullType(tk0) || (!knh_Token_isNullableType(tk0) && IS_NNTYPE(reqt)));
	DBG2_P("MAPCAST %s => %s isNonNullCast=%d", CLASSN(exprc), CLASSN(mprcid), isNonNullCast);
	knh_Stmt_typed(ctx, stmt, isNonNullCast ? NNTYPE_cid(mprcid) : NATYPE_cid(mprcid));
	if(isNonNullCast) {
		knh_Stmt_setNNCAST(stmt, 1);
	}

	if(mprcid == CLASS_Any) {   /* (Any)expr */
		mprcid = CLASS_type(reqt);
		if(mprcid == CLASS_Any) {
			return DP(stmt)->terms[1];
		}
	}

	if(TERMs_isNULL(ctx, stmt, 1)) {  /* (T)null */
		if(isNonNullCast) {
			knh_Token_toDEFVAL(DP(stmt)->tokens[1], mprcid);
		}
		else {
			knh_Asm_perror(ctx, abr, KERR_DWARN, _("casting null"));
		}
		return DP(stmt)->terms[1];
	}

	if(exprc == CLASS_Any) {     /* (T)anyexpr */
		knh_Token_toMPR(ctx, tk0, mprcid, (Mapper*)KNH_NULL);
		return TM(stmt);
	}

	if(mprcid == exprc || knh_class_instanceof(ctx, mprcid, exprc)) {
		/* upcast */
		if(isNonNullCast && IS_NNTYPE(exprt)) {
			knh_Token_toMPR(ctx, tk0, mprcid, (Mapper*)KNH_NULL);
			return TM(stmt);
		}
		if(!TERMs_isCONST(stmt, 1) && mprcid == exprc) {
			knh_Asm_perror(ctx, abr, KERR_DWARN, _("upcast does not need (%C)"), mprcid);
		}
		return DP(stmt)->terms[1];
	}

	if(knh_class_instanceof(ctx, exprc, mprcid)) {  /* downcast */
		knh_Token_toMPR(ctx, tk0, mprcid, (Mapper*)KNH_NULL);
		return TM(stmt);
	}

	Mapper *mpr = knh_Class_getMapper(ctx, exprc, mprcid);
	if(IS_NULL(mpr)) {
		knh_Asm_perror(ctx, abr, KERR_ERROR, _("undefined mapper: %C ==> %C"), exprc, mprcid);
		return NULL;
	}
	else if(knh_Mapper_isConst(mpr) && TERMs_isCONST(stmt, 1)) {
		DBG2_P("MAPCAST TO CONST .. %s ==> %s", CLASSN(DP(mpr)->scid), CLASSN(DP(mpr)->tcid));
		Token *tk1 = DP(stmt)->tokens[1];
		knh_sfp_t *lsfp = KNH_LOCAL(ctx);
		KNH_MOV(ctx, lsfp[0].o, DP(tk1)->data);
		KNH_UNBOX(ctx, &lsfp[0]);
		KNH_SMAP(ctx, lsfp, 0, mpr);
		KNH_BOX(ctx, &lsfp[0], DP(mpr)->tcid);
		knh_Token_setCONST(ctx, tk1, lsfp[0].o);
		return TM(tk1);
	}
	else {
		knh_Token_toMPR(ctx, tk0, mprcid, mpr);
		return TM(stmt);
	}
}

/* ======================================================================== */
/* [MT,AND,OR,] */

static
Term *knh_StmtMT_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	DBG2_ASSERT(DP(stmt)->size > 1);
	Token *tk = DP(stmt)->tokens[0];
	knh_methodn_t mn = knh_Token_getmn(ctx, tk);
	if(!TERMs_typing(ctx, stmt, 1, abr, ns, CLASS_Any, TCHECK_)) {
		return NULL;
	}
	if(knh_bytes_isOptionalMT(knh_Token_tobytes(ctx, tk))) {
		KNH_ASSERT(DP(stmt)->size == 2);
		KNH_ASSERT(IS_String(DP(tk)->data));
		knh_Stmt_add(ctx, stmt, TM(new_TokenCONST(ctx, FL(tk), DP(tk)->data)));
	}
	knh_Token_toMTD(ctx, tk, mn, (Method*)KNH_NULL);
	knh_Stmt_typed(ctx, stmt, NNTYPE_String);
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtAND_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	size_t i;
	for(i = 0; i < DP(stmt)->size; i++) {
		if(!TERMs_typing(ctx, stmt, i, abr, ns, NNTYPE_Boolean, TCHECK_)) {
			return NULL;
		}
		if(TERMs_isTRUE(stmt, i)) {
			return new_TermCONST(ctx, UP(stmt), KNH_TRUE);
		}
	}
	knh_Stmt_typed(ctx, stmt, NNTYPE_Boolean);
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtOR_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	size_t i;
	for(i = 0; i < DP(stmt)->size; i++) {
		if(!TERMs_typing(ctx, stmt, i, abr, ns, NNTYPE_Boolean, TCHECK_)) {
			return NULL;
		}
		if(TERMs_isTRUE(stmt, i)) {
			return new_TermCONST(ctx, UP(stmt), KNH_TRUE);
		}
	}
	knh_Stmt_typed(ctx, stmt, NNTYPE_Boolean);
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtALT_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	DBG2_ASSERT(DP(stmt)->size > 1);
	size_t i;
	knh_type_t nareqt = NATYPE_cid(CLASS_type(reqt));
	for(i = 0; i < DP(stmt)->size; i++) {
		if(!TERMs_typing(ctx, stmt, i, abr, ns, nareqt, TCHECK_)) {
			return NULL;
		}
		knh_type_t type = TERMs_gettype(stmt, i);
		if(IS_NNTYPE(type)) {
			DP(stmt)->size = i + 1;
			return knh_Stmt_typed(ctx, stmt, type);
		}
	}
	return knh_Stmt_typed(ctx, stmt, reqt);
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtTRI_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	DBG2_ASSERT(DP(stmt)->size == 3);
	int res = 1;
	if(!TERMs_typing(ctx, stmt, 0, abr, ns, NNTYPE_Boolean, TCHECK_)) res = 0;
	if(!TERMs_typing(ctx, stmt, 1, abr, ns, reqt, TCHECK_)) res = 0;
	if(!TERMs_typing(ctx, stmt, 2, abr, ns, reqt, TCHECK_)) res = 0;
	if(res == 0) return NULL;

	if(TERMs_isTRUE(stmt, 0)) {
		return DP(stmt)->terms[1];
	}
	if(TERMs_isFALSE(stmt, 0)) {
		return DP(stmt)->terms[2];
	}

	knh_type_t type = TERMs_gettype(stmt, 1);
	knh_type_t type2 = TERMs_gettype(stmt, 2);
	if(IS_NNTYPE(type) && IS_NNTYPE(type2)) {
		reqt = NNTYPE_cid(reqt);
	}
	else {
		reqt = NATYPE_cid(reqt);
	}
	return knh_Stmt_typed(ctx, stmt, reqt);
}

/* ======================================================================== */

Term *knh_StmtEXPR_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_class_t reqt)
{
	knh_stmt_t stt = SP(stmt)->stt;
	switch(stt) {
	case STT_CALL1:
		return knh_StmtCALL1_typing(ctx, stmt, abr, ns, reqt);
	case STT_LET:
		return knh_StmtLET_typing(ctx, stmt, abr, ns, reqt);
	case STT_CALL:
		return knh_StmtCALL_typing(ctx, stmt, abr, ns, reqt);
	case STT_NEW:
		return knh_StmtNEW_typing(ctx, stmt, abr, ns, reqt);
	case STT_OP:
		return knh_StmtOP_typing(ctx, stmt, abr, ns, reqt);
	case STT_MAPCAST:
		return knh_StmtMAPCAST_typing(ctx, stmt, abr, ns, reqt);
	case STT_MT:
		return knh_StmtMT_typing(ctx, stmt, abr, ns, reqt);
	case STT_AND:
		return knh_StmtAND_typing(ctx, stmt, abr, ns, reqt);
	case STT_OR:
		return knh_StmtOR_typing(ctx, stmt, abr, ns, reqt);
	case STT_ALT:
		return knh_StmtALT_typing(ctx, stmt, abr, ns, reqt);
	case STT_TRI:
		return knh_StmtTRI_typing(ctx, stmt, abr, ns, reqt);
	default:
		DBG2_P("undefined stmt=%s", knh_stmt_tochar(stt));
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
Term *new_TermINCAST(Ctx *ctx, knh_class_t reqc, Stmt *stmt, size_t n)
{
	knh_class_t varc = TERMs_getcid(stmt, n);
	if(varc == CLASS_Any) {
		Token *tk = new_TokenNULL(ctx, FL(stmt), CLASS_Any);
		knh_Token_toMPR(ctx, tk, reqc, (Mapper*)KNH_NULL);
		Stmt *cstmt = new_Stmt(ctx, 0, STT_MAPCAST);
		knh_Stmt_add(ctx, cstmt, TM(tk));
		knh_Stmt_add(ctx, cstmt, DP(stmt)->terms[n]);
		return knh_Stmt_typed(ctx, cstmt, reqc);
	}
	Mapper *mpr = knh_Class_getMapper(ctx, varc, reqc);
	if(IS_NULL(mpr)) {
		DBG2_P("cannot convert");
		return NULL;
	}
	if(TERMs_isCONST(stmt, n)) {
		Token *tk2 = DP(stmt)->tokens[n];
		knh_sfp_t *lsfp = KNH_LOCAL(ctx);
		KNH_MOV(ctx, lsfp[0].o, DP(tk2)->data);
		KNH_UNBOX(ctx, &lsfp[0]);
		KNH_SMAP(ctx, lsfp, 0, mpr);
		KNH_BOX(ctx, &lsfp[0], DP(mpr)->tcid);
		knh_Token_setCONST(ctx, tk2, lsfp[0].o);
		return TM(tk2);
	}
	else {
		Token *tk = new_TokenNULL(ctx, FL(stmt), CLASS_Any);
		knh_Token_toMPR(ctx, tk, reqc, mpr);
		Stmt *cstmt = new_Stmt(ctx, 0, STT_MAPCAST);
		knh_Stmt_add(ctx, cstmt, TM(tk));
		knh_Stmt_add(ctx, cstmt, DP(stmt)->terms[n]);
		return knh_Stmt_typed(ctx, cstmt, DP(tk)->type);
	}
}

/* ------------------------------------------------------------------------ */

static
int TERMs_typing(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, NameSpace *ns, knh_type_t reqt, int mode)
{
	Token *tkN = DP(stmt)->tokens[n];
	if(SP(stmt)->stt == STT_ERR) {
		goto L_ERROR;
	}
	if(IS_Token(tkN) && TT_(tkN) == TT_ESTR) {
		KNH_SETv(ctx, DP(stmt)->terms[n], knh_TokenESTR_toTerm(ctx, tkN, abr));
	}
	if(IS_Token(tkN)) {
		if(TT_(tkN) == TT_ASIS || !knh_Token_isTyped(tkN) ) {
			if(!knh_Token_typing(ctx, tkN, abr, ns, reqt)) {
				goto L_ERROR;
			}
			if(knh_Token_isUntypedName(tkN)) {
				tkN = knh_Asm_getSharedUntypedToken(ctx, abr, tkN);
				KNH_SETv(ctx, DP(stmt)->terms[n], tkN);
				if(DP(tkN)->type == TYPE_var) {
					if(mode == TCHECK_) {
						knh_Asm_derivedParamType(ctx, abr, tkN, reqt);
					}
				}
			}
		}
	}
	else {
		Stmt *stmtN = DP(stmt)->stmts[n];
		if(!knh_Stmt_isTyped(stmtN)) {
			Term *tm = knh_Stmt_typing(ctx, stmtN, abr, ns, reqt);
			if(tm == NULL) {
				goto L_ERROR;
			}
			if(tm != DP(stmt)->terms[n]) {
				KNH_SETv(ctx, DP(stmt)->stmts[n], tm);
			}
		}
	}

	if(mode == TWARN_ || reqt == TYPE_Any || reqt == TYPE_var) {
		return 1;
	}

	/*TYPECHECK*/ {
		knh_type_t vart = TERMs_gettype(stmt, n);
		knh_class_t varc = CLASS_type(vart);
		knh_class_t reqc = CLASS_type(reqt);

		if(TERMs_isNULL(ctx, stmt, n)) {
			if(IS_NNTYPE(reqt) && varc != reqc) {
				TERMs_perrorTYPE(ctx, stmt, n, reqt);
				goto L_ERROR;
			}
			return 1;
		}

		if(vart == TYPE_void) {
			TERMs_perrorTYPE(ctx, stmt, n, reqt);
			goto L_ERROR;
		}

		if(reqt == NNTYPE_Boolean && vart != NNTYPE_Boolean) {
			DBG2_P("stt=%s, vart=%s%s", knh_stmt_tochar(SP(stmt)->stt), TYPEQN(vart));
			TERMs_perrorTYPE(ctx, stmt, n, reqt);
			goto L_ERROR;
		}

		if(vart == reqt || reqc == CLASS_Any || knh_class_instanceof(ctx, varc, reqc)) return 1;

		if(mode == TITERCONV_ && ctx->share->ClassTable[varc].bcid == CLASS_Iterator) return 1;

		if(varc == CLASS_Any ||
				(varc == CLASS_Float && reqc == CLASS_Int) ||
				(varc == CLASS_Int && CLASS_Float)) {
			mode = TCONV_;
		}

		if(mode != TCONV_) {
			Mapper *mpr = knh_Class_getMapper(ctx, varc, reqc);
			if(IS_Mapper(mpr) && knh_Mapper_isICast(mpr)) {
				mode = TCONV_;
				knh_Asm_perror(ctx, abr, KERR_BAD, _("implict casting: %C => %C"), varc, reqc);
			}
		}

		if(mode == TCONV_ || mode == TITERCONV_) {
			Term *mcast = new_TermINCAST(ctx, reqc, stmt, n);
			if(mcast != NULL) {
				KNH_SETv(ctx, DP(stmt)->stmts[n], mcast);
				return 1;
			}
			//if(mode == TITERCONV_) goto L_ERROR;
		}
		DBG_P("stt=%s reqt=%s%s, vart=%s%s", knh_stmt_tochar(SP(stmt)->stt), TYPEQN(reqt), TYPEQN(vart));
		TERMs_perrorTYPE(ctx, stmt, n, reqt);
	}

	L_ERROR:;
	if(STT_(stmt) != STT_ERR) {
		DBG2_P("FOUND ERROR %s ==> STT_ERR", knh_stmt_tochar(STT_(stmt)));
		STT_(stmt) = STT_ERR;
	}
	return 0;
}

/* ======================================================================== */

static
int TERMs_typingBLOCK(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, NameSpace *ns, int isIteration)
{
	KNH_ASSERT(IS_Stmt(DP(stmt)->terms[n]));
	return knh_Stmt_typingBLOCK(ctx, DP(stmt)->stmts[n], abr, ns, isIteration);
}

/* ======================================================================== */
/* [IT] */

static
Token *new_TokenLOCAL(Ctx *ctx, Any *fln, knh_type_t type, int varidx)
{
	knh_Token_t *o = (Token*)new_Object_bcid(ctx, CLASS_Token, 0);
	knh_Token_setFL(o, fln);
	SP(o)->flag = 0;
	TT_(o) = TT_LOCAL;
	DP(o)->index = varidx;
	DP(o)->type = type;
	return o;
}

static
Token *knh_Stmt_add_IT(Ctx *ctx, Stmt *stmt, knh_type_t type, int index)
{
	Token *tk = new_TokenLOCAL(ctx, FL(stmt), type, index);
	DBG2_ASSERT(index == DP(stmt)->used_stack);
	DP(stmt)->used_stack += 1;
	knh_Stmt_addT(ctx, stmt, tk);
	return tk;
}

/* ======================================================================== */
/* [IF] */

static
void knh_Stmt_toBLOCK(Ctx *ctx, Stmt *stmt, size_t n)
{
	KNH_ASSERT(DP(stmt)->size > 0);
	SP(stmt)->stt = STT_BLOCK;
	KNH_SETv(ctx, DP(stmt)->terms[0], DP(stmt)->terms[n]);
	DP(stmt)->size = 1;
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtIF_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	if(!TERMs_typing(ctx, stmt, 0, abr, ns, NNTYPE_Boolean, TCHECK_)) {
		return NULL;
	}
	if(TERMs_isTRUE(stmt, 0)) {
		knh_Stmt_done(ctx, DP(stmt)->stmts[2]);
		TERMs_typingBLOCK(ctx, stmt, 1, abr, ns, 2/*ToReturn*/);
		knh_Stmt_toBLOCK(ctx, stmt, 1);
	}
	else if(TERMs_isFALSE(stmt, 0)) {
		knh_Stmt_done(ctx, DP(stmt)->stmts[1]);
		TERMs_typingBLOCK(ctx, stmt, 2, abr, ns, 2/*ToReturn*/);
		knh_Stmt_toBLOCK(ctx, stmt, 2);
	}
	else {
		TERMs_typingBLOCK(ctx, stmt, 1, abr, ns, 2/*ToReturn*/);
		TERMs_typingBLOCK(ctx, stmt, 2, abr, ns, 2/*ToReturn*/);
	}
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
Stmt *new_StmtMN(Ctx *ctx, Any *fl, knh_methodn_t mn)
{
	Stmt *stmt = new_Stmt(ctx, 0, STT_CALL);
	Token *tk = new_TokenMN(ctx, fl, mn);
	knh_Stmt_addT(ctx, stmt, tk);
	return stmt;
}

static
Term *knh_StmtSWITCH_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	Stmt *stmtCASE, *stmtDEFAULT = NULL;
	Token *tkIT = NULL;
	int c = 0;
	if(!TERMs_typing(ctx, stmt, 0, abr, ns, TYPE_Any, TWARN_)) {
		return NULL;
	}
	else {
		tkIT = knh_Stmt_add_IT(ctx, stmt, TERMs_gettype(stmt, 0), 0);
	}
	stmtCASE = DP(stmt)->stmts[1];
	while(IS_Stmt(stmtCASE)) {
		if(SP(stmtCASE)->stt == STT_CASE) {
			if(TERMs_isASIS(stmtCASE, 0)) {
				if(stmtDEFAULT != NULL) {
					knh_Asm_perror(ctx, abr, KERR_EWARN, _("duplicated default in switch"));
					knh_Stmt_done(ctx, stmtCASE);
					goto L_NEXT;
				}
				stmtDEFAULT = stmtCASE;
				TERMs_typingBLOCK(ctx, stmtCASE, 1, abr, ns, 2/*ToReturn*/);
				c++;
			}
			if(!TERMs_typing(ctx, stmtCASE, 0, abr, ns, TYPE_Any, TWARN_)) {
				knh_Stmt_done(ctx, stmtCASE);
				goto L_NEXT;
			}
			{
				Stmt *stmtOP = new_StmtMN(ctx, FL(stmt), METHODN_opCase);
				knh_Stmt_add(ctx, stmtOP, DP(stmtCASE)->terms[0]);
				knh_Stmt_addT(ctx, stmtOP, tkIT);
				KNH_SETv(ctx, DP(stmtCASE)->terms[0], stmtOP);
				if(!TERMs_typing(ctx, stmtCASE, 0, abr, ns, NNTYPE_Boolean, TCHECK_)) {
					knh_Stmt_done(ctx, stmtCASE);
					goto L_NEXT;
				}
			}
			TERMs_typingBLOCK(ctx, stmtCASE, 1, abr, ns, 2/*ToReturn*/);
			c++;
		}
		L_NEXT:;
		stmtCASE = DP(stmtCASE)->next;
	}
	if(c == 0) {
		return knh_Stmt_done(ctx, stmt);
	}
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtWHILE_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	if(!TERMs_typing(ctx, stmt, 0, abr, ns, NNTYPE_Boolean, TCHECK_)) {
		return NULL;
	}
	if(TERMs_isFALSE(stmt, 0)) {
		return knh_Stmt_done(ctx, stmt);
	}
	else {
		TERMs_typingBLOCK(ctx, stmt, 1, abr, ns, 1);
	}
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtDO_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	TERMs_typingBLOCK(ctx, stmt, 0, abr, ns, 1);
	if(!TERMs_typing(ctx, stmt, 1, abr, ns, NNTYPE_Boolean, TCHECK_)) {
		return NULL;
	}
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtFOR_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	/* i = 0*/
	if(!TERMs_typingBLOCK(ctx, stmt, 0, abr, ns, 0)) return NULL;
	/* i < N */
	if(!TERMs_typing(ctx, stmt, 1, abr, ns, NNTYPE_Boolean, TCHECK_)) return NULL;

	if(TERMs_isFALSE(stmt, 1)) {
		return DP(stmt)->terms[0];
	}
	else {
		/* i++ */
		if(!TERMs_typingBLOCK(ctx, stmt, 2, abr, ns, 0)) return NULL;
		TERMs_typingBLOCK(ctx, stmt, 3, abr, ns, 1);
	}
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */
/* [SEPARATOR] */

static
int knh_Asm_typingSEPARATOR(Ctx *ctx, Asm *abr, NameSpace *ns, Stmt *stmtDECL, Token *tkIT)
{
	knh_int_t c = 1;
	Method *mtd = knh_Class_getMethod(ctx, CLASS_type(DP(tkIT)->type), METHODN_op0);
	if(IS_NULL(mtd)) {
		knh_Asm_perror(ctx, abr, KERR_TERROR, _("unsupported multi-selection: %C"));
		return 0;
	}
	while(IS_Stmt(stmtDECL)) {
		Stmt *stmtVALUE;
		if(c < 3) {
			stmtVALUE = new_StmtMN(ctx, FL(stmtDECL), (c == 1) ? METHODN_op0 : METHODN_op2);
			knh_Stmt_addT(ctx, stmtVALUE, tkIT);
		}
		else {
			stmtVALUE = new_StmtMN(ctx, FL(stmtDECL), METHODN_opN);
			knh_Stmt_addT(ctx, stmtVALUE, tkIT);
			knh_Stmt_addT(ctx, stmtVALUE, new_TokenCONST(ctx, FL(stmtDECL), UP(new_Int(ctx, c))));
		}
		DBG2_ASSERT(SP(stmtDECL)->stt == STT_DECL);
		KNH_SETv(ctx, DP(stmtDECL)->terms[2], stmtVALUE);
		{
			int templevel = DP(abr)->level;
			DP(abr)->level = INNERPARAMS;
			Term *tm = knh_StmtDECL_typing(ctx, stmtDECL, abr, ns);
			DP(abr)->level = templevel;
			if(tm == NULL) return 0;
			DBG2_ASSERT(STT_(stmtDECL) == STT_LET);
		}
		stmtDECL = DP(stmtDECL)->next;
	}
	return 1;
}

static
Term *knh_StmtSEPARATOR_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	if(TERMs_typing(ctx, stmt, 1, abr, ns, TYPE_Any, TWARN_)) {
		Token *tkIT = knh_Stmt_add_IT(ctx, stmt, TERMs_getcid(stmt, 1), 0);
		if(knh_Asm_typingSEPARATOR(ctx, abr, ns, DP(stmt)->stmts[0], tkIT)) {
			return TM(stmt);
		}
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */
/* [FOREACH] */

static
int knh_Stmt_isSEPARATOR(Stmt *stmt)
{
	return (IS_Stmt(DP(stmt)->next) && STT_(DP(stmt)->next) == STT_DECL);
}

#ifndef METHODN_opItr__2
#define METHODN_opItr__2   METHODN_opItr
#endif

static
Term *knh_StmtFOREACH_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	knh_type_t reqt  = TYPE_var;
	Stmt *stmtDECL = DP(stmt)->stmts[0];
	Token *tkITR = knh_Stmt_add_IT(ctx, stmt, NNTYPE_Iterator, 0);
	Token *tkSPR = NULL;
	knh_methodn_t mn_opItr = METHODN_opItr;
	if(knh_Stmt_isSEPARATOR(stmtDECL)) {
		tkSPR = knh_Stmt_add_IT(ctx, stmt, TYPE_Any, 1);
		mn_opItr = METHODN_opItr__2;
	}
	else {
		int templevel = DP(abr)->level;
		DP(abr)->level = INNERPARAMS;
		Term *tm = knh_StmtDECL_typing(ctx, stmtDECL, abr, ns);
		DP(abr)->level = templevel;
		if(tm == NULL) return NULL;
		DBG2_ASSERT(STT_(stmtDECL) == STT_DECL);
		reqt = TERMs_gettype(stmtDECL, 1);
		DBG2_P("reqt=%s%s", TYPEQN(reqt));
	}

	if(reqt == TYPE_var) {
		if(!TERMs_typing(ctx, stmt, FOREACH_iter, abr, ns, TYPE_Any, TWARN_)) {
			return NULL;
		}
		if(TERMs_getbcid(stmt, FOREACH_iter) != CLASS_Iterator) {
			Stmt *stmtCALL = new_StmtMN(ctx, FL(stmt), mn_opItr);
			knh_Stmt_add(ctx, stmtCALL, StmtFOREACH_iter(stmt));
			KNH_SETv(ctx, DP(stmt)->stmts[FOREACH_iter], stmtCALL);
			if(!TERMs_typing(ctx, stmt, FOREACH_iter, abr, ns, NNTYPE_Iterator, TCHECK_)) {
				return NULL;
			}
		}
		DP(tkITR)->type = TERMs_gettype(stmt, FOREACH_iter);
		reqt = NNTYPE_cid(ClassTable(CLASS_type(DP(tkITR)->type)).p1);
		if(tkSPR == NULL) {
			knh_Asm_derivedParamType(ctx, abr, DP(stmtDECL)->tokens[1], reqt);
		}
		else {
			DP(tkSPR)->type = reqt;
			if(!knh_Asm_typingSEPARATOR(ctx, abr, ns, stmtDECL, tkSPR)) {
				return NULL;
			}
		}
	}
	else {
		DBG2_ASSERT(tkSPR == NULL);
		DP(tkITR)->type = knh_class_Iterator(ctx, CLASS_type(reqt));
		if(!TERMs_typing(ctx, stmt, FOREACH_iter, abr, ns, DP(tkITR)->type, TITERCONV_)) {
			Stmt *stmtCALL = new_StmtMN(ctx, FL(stmt), mn_opItr);
			knh_Stmt_add(ctx, stmtCALL, StmtFOREACH_iter(stmt));
			KNH_SETv(ctx, DP(stmt)->stmts[FOREACH_iter], stmtCALL);
			if(!TERMs_typing(ctx, stmt, FOREACH_iter, abr, ns, NNTYPE_Iterator, TCHECK_)) {
				return NULL;
			}
		}
	}
	if(!TERMs_typing(ctx, stmt, FOREACH_where, abr, ns, NNTYPE_Boolean, TCHECK_)) {
		return NULL;
	}
	if(TERMs_isFALSE(stmt, FOREACH_where)) {
		knh_Stmt_done(ctx, stmt);
		return TM(stmt);
	}
	TERMs_typingBLOCK(ctx, stmt, FOREACH_loop, abr, ns, 1);
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtTRY_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	knh_Stmt_add_IT(ctx, stmt, NNTYPE_Exception, 0);
	TERMs_typingBLOCK(ctx, stmt, TRY_try, abr, ns, 2/*ToReturn*/);
	{
		Stmt *stmtCATCH = DP(stmt)->stmts[TRY_catch];
		while(IS_Stmt(stmtCATCH)) {
			if(SP(stmtCATCH)->stt == STT_CATCH) {
				Token *tkV = DP(stmtCATCH)->tokens[1];
				knh_fieldn_t fn = knh_Token_getfnq(ctx, tkV);
				knh_cfield_t decl = {0, TYPE_Exception, fn, NULL};
				knh_index_t idx = knh_Asm_declareLocalVariable(ctx, abr, &decl);
				if(idx == -1) {
					knh_Stmt_done(ctx, stmtCATCH);
				}
				else {
					if(!TERMs_typing(ctx, stmtCATCH, 1, abr, ns, TYPE_Exception, TCHECK_)) {
						knh_Stmt_done(ctx, stmtCATCH);
					}
					else {
						TERMs_typingBLOCK(ctx, stmtCATCH, 2, abr, ns, 2/*ToReturn*/);
					}
				}
			}
			stmtCATCH = DP(stmtCATCH)->next;
		}
	}
	TERMs_typingBLOCK(ctx, stmt, TRY_finally, abr, ns, 2/*ToReturn*/);
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtTHROW_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	if(!TERMs_typing(ctx, stmt, 0, abr, ns, NNTYPE_Exception, TCHECK_)) {
		return NULL;
	}
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtPRINT_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	size_t i;
	for(i = 0; i < DP(stmt)->size; i++) {
		if(!TERMs_typing(ctx, stmt, i, abr, ns, TYPE_Any, TWARN_)) {
			return NULL;
		}
	}
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtASSERT_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	if(!TERMs_typing(ctx, stmt, 0, abr, ns, NNTYPE_Boolean, TCHECK_)) {
		return NULL;
	}
	if(TERMs_isTRUE(stmt, 0)) {
		return knh_Stmt_done(ctx, stmt);
	}
	if(TERMs_isFALSE(stmt, 0)) {
		knh_Asm_perror(ctx, abr, KERR_EWARN, _("always throw Assert!!"));
	}
	TERMs_typingBLOCK(ctx, stmt, 1, abr, ns, 1);
	return TM(stmt);
}

/* ======================================================================== */
/* [REGISTER] */

void knh_Asm_initReg(Ctx *ctx, Asm *abr)
{
	size_t i;
	for(i = 0; i < KNH_ASM_REGMAX; i++) {
		DP(abr)->regs[i].level = -1;
		DP(abr)->regs[i].varidx = -1;
		DP(abr)->regs[i].stmt = NULL; /* NullPointerException */
	}
	DP(abr)->regs_size = 0;
	DP(abr)->regs_usedsize = 0;
}

static
knh_index_t knh_Asm_beginRegister(Ctx *ctx, Asm *abr, Stmt *stmt)
{
	if(DP(abr)->regs_size < KNH_ASM_REGMAX) {
		size_t size = DP(abr)->regs_size;
		DP(abr)->regs[size].level = DP(abr)->level;
		DP(abr)->regs[size].stmt = stmt;
		if(DP(abr)->regs[size].varidx == -1) {
			knh_cfield_t decl = {0, TYPE_void, FIELDN_register, NULL};
			DP(abr)->regs[size].varidx =
				knh_Asm_addVariableTable(ctx, abr, DP(abr)->gamma, KONOHA_LOCALSIZE, &decl);
		}
		DP(abr)->regs_size = size + 1;
		if(DP(abr)->regs_size > DP(abr)->regs_usedsize) {
			DP(abr)->regs_usedsize = DP(abr)->regs_size;
		}
		DBG2_P("level=%d, regs_size=%d, varidx=%d", DP(abr)->level, DP(abr)->regs_size, DP(abr)->regs[size].varidx);
		return DP(abr)->regs[size].varidx;
	}
	else {
		TODO(); /* MSG */
	}
	return -1;
}

static
void knh_Asm_endRegister(Ctx *ctx, Asm *abr, int level)
{
	size_t i;
	for(i = 0; i < DP(abr)->regs_size; i++) {
		if(DP(abr)->regs[i].level == level) {
			DP(abr)->regs_size = i;
			DP(abr)->regs[i].stmt = NULL; /* NullPointerException */
			//DBG2_P("level=%d, regs_size=%d", level, i);
			return;
		}
	}
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtREGISTER_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	size_t i;
	for(i = 0; i < DP(stmt)->size; i++) {
		if(!TERMs_typing(ctx, stmt, i, abr, ns, TYPE_Any, TWARN_)) {
			return NULL;
		}
		if(IS_Stmt(DP(stmt)->terms[i])) {
			knh_index_t varidx = knh_Asm_beginRegister(ctx, abr, DP(stmt)->stmts[i]);
			if(varidx != -1) {
				Stmt *stmtlet = new_Stmt(ctx, 0, STT_LET);
				knh_type_t type = DP(DP(stmt)->stmts[i])->type;
				Token *tk = new_TokenLOCAL(ctx, DP(stmt)->terms[i], type, varidx);
				knh_Stmt_add(ctx, stmtlet, TM(tk));
				knh_Stmt_add(ctx, stmtlet, DP(stmt)->terms[i]);
				KNH_SETv(ctx, DP(stmt)->terms[i], stmtlet);
				DP(stmtlet)->type = type;
			}
		}
	}
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
int knh_Token_equals(Ctx *ctx, Token *tk, Term *tm)
{
	if(IS_Stmt(tm)) return 0;
	Token *atk = (Token*)tm;
	if(SP(tk)->tt != SP(atk)->tt) return 0;
	if(DP(tk)->type != DP(atk)->type) return 0;
	if(DP(tk)->index != DP(atk)->index) return 0;
	if(SP(tk)->tt == TT_CONST) {
		if(knh_Object_cid(DP(tk)->data) != knh_Object_cid(DP(atk)->data)) return 0;
		return (knh_Object_cmp(DP(tk)->data, DP(atk)->data) == 0);
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

static
int knh_Stmt_equals(Ctx *ctx, Stmt *stmt, Term *tm)
{
	if(!IS_Stmt(tm)) return 0;
	Stmt *astmt = (Stmt*)tm;
	if(SP(stmt)->stt != SP(astmt)->stt) return 0;
	//	if(SP(stmt)->flag != SP(astmt)->flag) return 0;
	if(DP(stmt)->type != DP(astmt)->type) return 0;
	if(DP(stmt)->size != DP(astmt)->size) return 0;
	size_t i;
	for(i = 0; i < DP(stmt)->size; i++) {
		if(IS_Stmt(DP(stmt)->terms[i])) {
			if(!knh_Stmt_equals(ctx, DP(stmt)->stmts[i], DP(astmt)->terms[i])) return 0;
		}
		if(IS_Token(DP(stmt)->terms[i])) {
			if(!knh_Token_equals(ctx, DP(stmt)->tokens[i], DP(astmt)->terms[i])) return 0;
		}
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

static
Term *knh_Asm_lookupRegisteredStmt(Ctx *ctx, Asm *abr, Stmt *stmt)
{
	DBG2_ASSERT(IS_Stmt(stmt));
	int i;
	for(i = DP(abr)->regs_size - 1; i >= 0; i--) {
		if(knh_Stmt_equals(ctx, DP(abr)->regs[i].stmt, TM(stmt))) {
			DBG_P("REGISTER(%d) TO sfp[=%d]", i, DP(abr)->regs[i].varidx);
			if(DP(abr)->regs[i].varidx != -1) {
				return TM(new_TokenLOCAL(ctx, TM(stmt), DP(stmt)->type, DP(abr)->regs[i].varidx));
			}
			return TM(stmt);
		}
	}
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */
/* [METHOD] */

static
knh_type_t knh_StmtMETHOD_rtype(Ctx *ctx, Stmt *stmt, NameSpace *ns)
{
	return knh_Token_gettype(ctx, DP(stmt)->tokens[0], ns, NATYPE_Any);
}

static
knh_class_t knh_StmtMETHOD_class(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, int level)
{
	Token *tk = DP(stmt)->tokens[1];
	KNH_ASSERT(IS_Token(tk));
	if(TT_(tk) == TT_ASIS) {
		if(level == 0) {
			Script *scr = knh_getAsmScript(ctx);
			return knh_Object_cid(scr);
		}
		else {
			return DP(abr)->this_cid;
		}
	}
	{
		knh_bytes_t name = knh_Token_tobytes(ctx, tk);
		if(TT_(tk) == TT_CMETHODN) {
			knh_index_t idx = knh_bytes_rindex(name, '.');
			DBG2_ASSERT(idx != -1);
			name = knh_bytes_first(name, idx);
		}

		knh_class_t cid = knh_NameSpace_getcid(ctx, ns, name);
		if(cid == CLASS_unknown) {
			cid = DP(abr)->this_cid;
			knh_Asm_perror(ctx, abr, KERR_ERRATA,
				_("unknown class: %B ==> %s"), name, cid);
		}
		else if(level > 0 && cid != DP(abr)->this_cid) {
			cid = DP(abr)->this_cid;
			knh_Asm_perror(ctx, abr, KERR_ERRATA,
				_("different class: %B ==> %s"), name, cid);
		}
		KNH_ASSERT(cid != CLASS_unknown);
		return cid;
	}
}

static
knh_methodn_t knh_StmtMETHOD_name(Ctx *ctx, Stmt *stmt, Asm *abr, int level)
{
	Token *tk = DP(stmt)->tokens[2];
	KNH_ASSERT(IS_Token(tk));
	if(TT_(tk) == TT_ASIS) {
		if(level == 1) {
			return METHODN_new;
		}
		else {
			KNH_ASSERT(ctx == NULL);
			//return METHODN_mapper;
		}
	}
	return knh_Token_getmn(ctx, tk);
}

/* ------------------------------------------------------------------------ */

int knh_Stmt_initParams(Ctx *ctx, Stmt *pstmt, Asm *abr, NameSpace *ns, int level)
{
	knh_Asm_initGamma(ctx, abr, 0);
	DP(abr)->gamma[0].flag = 0;
	DP(abr)->gamma[0].type = NNTYPE_cid(DP(abr)->this_cid);
	DP(abr)->gamma[0].fn   = FIELDN_this;
	DP(abr)->gamma_size = 1;
	while(IS_Stmt(pstmt)) {
		if(SP(pstmt)->stt == STT_DECL) {
			int templevel = DP(abr)->level;
			DP(abr)->level = level;
			Term *tm = knh_StmtDECL_typing(ctx, pstmt, abr, ns);
			DP(abr)->level = templevel;
			if(tm == NULL) return 0;
			KNH_ASSERT(pstmt == (Stmt*)tm);
		}
		pstmt = DP(pstmt)->next;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

static
MethodField *knh_Asm_findMethodField(Ctx *ctx, Asm *abr, knh_type_t rztype, size_t mfsize)
{
	size_t i;
	knh_hcode_t h = rztype;
	for(i = 1; i < mfsize; i++) {
		knh_type_t vtype = DP(abr)->gamma[i].type;
		h = knh_mparam_hcode(h, vtype, DP(abr)->gamma[i].fn);
	}
	if(IS_NOTNULL(DP(ctx->sys)->MethodFieldHashMap)) {
		HashMap *hmap = DP(ctx->sys)->MethodFieldHashMap;
		KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
		MethodField *mf = (MethodField*)knh_HashMap_get__hcode(ctx, hmap, h);
		KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
		if(IS_MethodField(mf)) {
			if(mf->rtype != rztype || mf->psize + 1 != mfsize) {
				return NULL;
			}
			for(i = 1; i < mfsize; i++) {
				knh_mparam_t p = knh_MethodField_param(mf, i-1);
				knh_type_t vtype = DP(abr)->gamma[i].type;
				if(vtype != p.type || p.fn != DP(abr)->gamma[i].fn) {
					return NULL;
				}
			}
			DBG2_P("Found Predefined MethodField %p", mf);
			return mf;
		}
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
Stmt *knh_Stmt_tailReturn(Ctx *ctx, Stmt *stmt)
{
	Stmt *o = stmt;
	while(IS_NOTNULL(DP(o)->next)) {
		if(STT_(o) == STT_RETURN || STT_(o) == STT_THROW) {
			goto L_RETURN;
		}
		o = DP(o)->next;
	}
	L_RETURN:;
	if(IS_NOTNULL(DP(o)->next)) {
		knh_perror(ctx, SP(o)->uri, SP(o)->line + 1, KERR_DWARN, _("not reached"));
	}
	return o;
}

static
int knh_Stmt_checkLastReturn(Ctx *ctx, Stmt *stmt, Method *mtd)
{
	Stmt *stmtLAST = knh_Stmt_tailReturn(ctx, stmt);
	knh_stmt_t stt = SP(stmtLAST)->stt;
	if(stt == STT_RETURN || stt == STT_THROW || stt == STT_ERR) {
		return 1;
	}
	if(stt == STT_CALL1) {
		STT_(stmtLAST) = STT_RETURN;
		return 1;
	}
	if(STT_NEW <= stt && stt <= STT_OR) {
		if(stt != STT_CALL || knh_Method_rztype(mtd) != TYPE_void) {
			Stmt *o = knh_Stmt_copy(ctx, stmtLAST);
			STT_(stmtLAST) = STT_RETURN;
			knh_Stmt_resize(ctx, stmtLAST, 1);
			KNH_SETv(ctx, DP(stmtLAST)->stmts[0], o);
			return 1;
		}
	}
	if(stt == STT_IF) {
		if(knh_Stmt_checkLastReturn(ctx, StmtIF_truecase(stmtLAST), NULL) &&
				knh_Stmt_checkLastReturn(ctx, StmtIF_falsecase(stmtLAST), NULL)) {
			return 1;
		}
	}

	if(mtd == NULL) return 0;
	KNH_ASSERT(stmtLAST != NULL);
	/* Generate default return statement */
	{
		Stmt *stmtRETURN = new_Stmt(ctx, 0, STT_RETURN);
		if(!knh_Method_isConstructor(ctx, mtd)) {
			knh_Asm_addDefaultReturnValue(ctx, ctx->abr, stmtRETURN, knh_Method_rtype(ctx, mtd, DP(mtd)->cid));
		}
		KNH_SETv(ctx, DP(stmtLAST)->next, stmtRETURN);
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

static
void *knh_Asm_loadFunc(Ctx *ctx, Asm *abr, char *funcname, int isNaitive)
{
	if(DP(abr)->dlhdr != NULL) {
		void *f = knh_dlsym(ctx, DP(abr)->dlhdr, funcname);
		if(f != NULL) return f;
	}
	if(isNaitive) {
		knh_Asm_perror(ctx, abr, KERR_EWARN, _("cannot bind %s"), funcname);
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
knh_fmethod knh_Asm_loadMethodFunc(Ctx *ctx, Asm *abr, knh_class_t cid, knh_methodn_t mn, int isNaitive)
{
	KNH_ASSERT_cid(cid);
	char buf[80];
	char *cname = knh_String_tochar(ClassTable(cid).sname);
	if(METHODN_IS_MOVTEXT(mn)) {
		knh_snprintf(buf, sizeof(buf), "%s__%s", cname, FIELDN(METHODN_TOFIELDN(mn)));
	}
	else if(METHODN_IS_GETTER(mn)) {
		int off = knh_strlen(cname)+4;
		knh_snprintf(buf, sizeof(buf), "%s_get%s", cname, FIELDN(METHODN_TOFIELDN(mn)));
		if(islower(buf[off])) buf[off] = toupper(buf[off]);
	}
	else if(METHODN_IS_SETTER(mn)) {
		int off = knh_strlen(cname)+4;
		knh_snprintf(buf, sizeof(buf), "%s_set%s", cname, FIELDN(METHODN_TOFIELDN(mn)));
		if(islower(buf[off])) buf[off] = toupper(buf[off]);
	}
	else {
		knh_snprintf(buf, sizeof(buf), "%s_%s", cname, FIELDN(mn));
	}
	return (knh_fmethod)knh_Asm_loadFunc(ctx, abr, buf, isNaitive);
}

/* ------------------------------------------------------------------------ */

void knh_StmtMETHOD_typingBODY(Ctx *ctx, Asm *abr, NameSpace *ns, Method *mtd, Stmt *stmtPARAMS, Stmt *stmtBODY, int isIteration)
{
	DBG2_P("START TYPING BODY OF FUNCTION..");
	knh_Method_toAbstract(ctx, mtd);
	knh_Asm_prepare(ctx, abr, mtd, stmtBODY);
	knh_Asm_initThis(ctx, abr, DP(abr)->this_cid);
	if(stmtPARAMS != NULL) {
		if(!knh_Stmt_initParams(ctx, stmtPARAMS, abr, ns, INNERPARAMS)) {
			return;
		}
	}
	DP(abr)->level = 1;
	if(isIteration == 1) isIteration = 2; /*ToReturn*/
	if(!knh_Stmt_typingBLOCK(ctx, stmtBODY, abr, ns, isIteration)) {
		return;
	}
	DBG2_P("END TYPING BODY OF FUNCTION..");
}

/* ------------------------------------------------------------------------ */

Term * knh_StmtMETHOD_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	Method *mtd;
	int level = DP(abr)->level;
	knh_flag_t flag   = knh_StmtMETHOD_flag(ctx, stmt);
	knh_type_t rztype = knh_StmtMETHOD_rtype(ctx, stmt, ns);
	knh_class_t mtd_cid = knh_StmtMETHOD_class(ctx, stmt, abr, ns, level);
	knh_methodn_t mn = knh_StmtMETHOD_name(ctx, stmt, abr, level);

	if(!knh_Stmt_initParams(ctx, StmtMETHOD_params(stmt), abr, ns, OUTERPARAMS)) {
		return NULL;
	}

	mtd = knh_Class_getMethod(ctx, mtd_cid, mn);
	/* Check the type of Constructor */
	if(knh_methodn_isNew(ctx, mn) &&
			(mtd_cid != CLASS_type(rztype) && mtd_cid != CLASS_This)) {
		knh_Asm_perror(ctx, abr, KERR_ERRATA,
			_("constructor class: %C ==> %C"), CLASS_type(rztype), mtd_cid);
		rztype = mtd_cid;
	}

	/* New method, and constructors are always new */
	if(IS_NULL(mtd) || knh_Method_isPrivate(mtd) || knh_methodn_isNew(ctx, mn)) {
		size_t i, mfsize = DP(abr)->gamma_size;
		MethodField *mf = knh_Asm_findMethodField(ctx, abr, rztype, mfsize);
		int hasUntyped = 0;
		if(mf == NULL) {
			size_t psize = mfsize - 1;
			mf = new_MethodField(ctx, rztype, psize);
			if(rztype == TYPE_var) hasUntyped = 1;
			for(i = 1; i < mfsize; i++) {
				knh_MethodField_set(mf, i - 1, DP(abr)->gamma[i].type, DP(abr)->gamma[i].fn);
				if(DP(abr)->gamma[i].type == TYPE_var) hasUntyped = 1;
			}
			if(hasUntyped == 0) {
				knh_addMethodFieldTable(ctx, mf);
			}
		}
		mtd = new_Method(ctx, flag, mtd_cid, mn, NULL);
		KNH_SETv(ctx, DP(mtd)->mf, mf);
		knh_Class_addMethod(ctx, mtd_cid, mtd);
	}
	else {
		size_t i, mfsize = DP(abr)->gamma_size;
		MethodField *mf = DP(mtd)->mf;
		if(DP(mtd)->cid != mtd_cid) { /* Overriding */
			if(knh_Method_isFinal(mtd)) { /* CHECK @Final */
				knh_Asm_perror(ctx, abr, KERR_ERROR, _("%C.%M is final; add @Virtual %C.%M"),
						DP(mtd)->cid, mn, ctx->share->ClassTable[DP(mtd)->cid].supcid, mn);
				return NULL;
			}
			mtd = new_Method(ctx, flag, mtd_cid, mn, NULL);
			KNH_SETv(ctx, DP(mtd)->mf, mf);
			knh_Class_addMethod(ctx, mtd_cid, mtd);
		}

		if(!knh_StmtMETA_isOverride(ctx, stmt) &&
				!knh_Method_isAbstract(mtd) && DP(mtd)->mn != METHODN_main) {
			/* Konoha: To override, you need @Override */
			if(!knh_Context_isInteractive(ctx)) {
				knh_Asm_perror(ctx, abr, KERR_DWARN, _("%C.%M is overriden"), mtd_cid, mn);
			}
		}

		if(mfsize != mf->psize+1) {
			knh_Asm_perror(ctx, abr, KERR_TERROR,
				_("parameter size: must be %C.%M(%d)"), mtd_cid, mn, (knh_intptr_t)mf->psize+1);
			return NULL;
		}

		if(mf->rtype != rztype) {
			if(rztype == TYPE_var) {
				KNH_SETv(ctx, DP(abr)->mtd, mtd); DP(abr)->rtype = rztype;
				knh_Asm_derivedReturnType(ctx, abr, mtd, rztype);
			}
			else {
				knh_Asm_perror(ctx, abr, KERR_TERROR,
					_("return type: must be %T %C.%M"), mf->rtype, mtd_cid, mn);
				return NULL;
			}
		}

		for(i = 1; i < mfsize; i++) {
			knh_type_t ptype = knh_MethodField_pztype(mf, i - 1);
			knh_type_t vtype = DP(abr)->gamma[i].type;
			if(vtype == TYPE_var) {
				Token *tkVAR = (Token*)DP(abr)->gamma[i].value;
				KNH_ASSERT(IS_Token(tkVAR));
				knh_Asm_derivedParamType(ctx, abr, tkVAR, ptype);
			}
			else if(ptype != vtype) {
				knh_Asm_perror(ctx, abr, KERR_TERROR,
					_("parameter %d of %C.%M"), i, mtd_cid, mn);
				return NULL;
			}
		}
	}

	DP(mtd)->uri = SP(stmt)->uri;
	knh_Token_setCONST(ctx, StmtMETHOD_method(stmt), UP(mtd));

	if(knh_Method_isUntyped(mtd)) { /* type inferencing */
		int i, hasUntypedName = 0;
		DBG2_P("START TO INFER METHOD TYPE..");
		knh_StmtMETHOD_typingBODY(ctx, abr, ns, mtd, DP(stmt)->stmts[3], StmtMETHOD_instmt(stmt), 1 /*Iteration */);
		if(DP(abr)->rtype == TYPE_var) {
			hasUntypedName = 1;
			knh_Asm_derivedReturnType(ctx, abr, mtd, TYPE_Any);
		}
		for(i = 1; i < DP(abr)->gamma_size; i++) {
			if(DP(abr)->gamma[i].type == TYPE_var) {
				hasUntypedName = 1;
				knh_Asm_derivedParamType(ctx, abr, (Token*)DP(abr)->gamma[i].value, TYPE_Any);
			}
		}
		if(hasUntypedName) {
			knh_Asm_perror(ctx, abr, KERR_EWARN, _("failed to infer types in %C.%M"), DP(mtd)->cid, DP(mtd)->mn);
		}
		DBG2_P("END OF TYPE INFERENCE..");
	}
	{
		knh_fmethod func = NULL;
		knh_invokeMethodTypingListener(ctx, DP(stmt)->metaDictMap, mtd);
		func = knh_Asm_loadMethodFunc(ctx, abr, mtd_cid, DP(mtd)->mn, knh_StmtMETA_is(ctx, stmt, STEXT("Naitive")));
		if(func != NULL) {
			knh_Method_syncFunc(mtd, func);
			return knh_Stmt_done(ctx, stmt);
		}
	}
	if(DP(stmt)->size != 4 && rztype != TYPE_void) {
		knh_Stmt_checkLastReturn(ctx, StmtMETHOD_instmt(stmt), mtd);
	}
	return TM(stmt);
}


/* ------------------------------------------------------------------------ */

Term *knh_StmtFORMAT_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	knh_Stmt_done(ctx, stmt);
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
void knh_Asm_initClassTableField(Ctx *ctx, Asm *abr, knh_class_t cid)
{
	DP(abr)->flag = 0;
	DP(abr)->this_cid = cid;
	DP(abr)->level = 0;
	knh_Asm_initGamma(ctx, abr, 0);
}

/* ------------------------------------------------------------------------ */

static
void knh_Asm_declareClassField(Ctx *ctx, Asm *abr, NameSpace* ns, knh_class_t cid)
{
	knh_ClassTable_t *t = (knh_ClassTable_t*)(&ClassTable(cid));
	DBG2_ASSERT(IS_ClassStruct(t->cstruct));
	DBG2_ASSERT((t->cstruct)->fields == NULL);
	{
		int i, fsize = DP(abr)->gamma_size;
		knh_cfield_t *cf = (knh_cfield_t*)KNH_MALLOC(ctx, sizeof(knh_cfield_t) * fsize);
		//DBG2_P("class %s fsize=%d", CLASSN(cid), fsize);
		for(i = 0; i < fsize; i++) {
			cf[i] = DP(abr)->gamma[i];
			if(cf[i].value != NULL) {
				DP(abr)->gamma[i].value = NULL; /* COPY TO GC */
			}
		}
		(t->cstruct)->fields = cf;
		(t->cstruct)->fsize = fsize;
		t->sid = BSIZE_TOSID(fsize);
		if(t->supcid != CLASS_Object) {
			t->offset = ctx->share->ClassTable[t->supcid].bsize;
			//DBG2_P("offset extending 0 -> %d", TC->offset);
		}
		t->bsize = fsize + t->offset;
		t->size = sizeof(Object*) * t->bsize;
		knh_NameSpace_setcid(ctx, ns, t->sname, cid);
		DBG2_({
			DBG2_P("HERE IS DEFINED STRUCT (offset=%d)", t->offset);
			knh_cfield_dump(ctx, cf, 0, fsize, KNH_STDOUT);
		});
		/* update default value */
		DBG2_ASSERT(knh_Object_cid(t->cspec) == cid);
		{
			knh_ObjectField_t *of = (knh_ObjectField_t*)t->cspec;
			of->bsize = t->bsize;
			if(t->bsize == 0) {
				of->fields = NULL;
			}
			else {
				of->fields = KNH_MALLOC(ctx, sizeof(Object*) * of->bsize);
				knh_ObjectField_init(ctx, of, 0);
			}
		}
	}
}

/* ------------------------------------------------------------------------ */

Term *knh_StmtCLASS_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	knh_class_t prev_cid = DP(abr)->this_cid;
	knh_class_t this_cid = DP(StmtCLASS_class(stmt))->cid;
	knh_Asm_initClassTableField(ctx, abr, this_cid);

	Stmt *instmt = StmtCLASS_instmt(stmt);
	while(IS_Stmt(instmt)) {
		DP(abr)->line = SP(instmt)->line;
		DP(abr)->level = 1;
		if(SP(instmt)->stt == STT_DECL) {
			knh_StmtDECL_typing(ctx, instmt, abr, ns);
			knh_Stmt_done(ctx, instmt);
		}
		else if(SP(instmt)->stt == STT_LET) {
			knh_StmtLET_typing(ctx, instmt, abr, ns, TYPE_void);
			knh_Stmt_done(ctx, instmt);
		}
		instmt = DP(instmt)->next;
	}
	knh_Asm_declareClassField(ctx, abr, ns, this_cid);
	knh_Asm_initClassTableField(ctx, abr, this_cid);
	instmt = StmtCLASS_instmt(stmt);
	while(IS_Stmt(instmt)) {
		DP(abr)->line = SP(instmt)->line;
		DP(abr)->level = 1;
		if(SP(instmt)->stt == STT_METHOD) {
			if(knh_StmtMETHOD_typing(ctx, instmt, abr, ns) == NULL) {
				knh_Stmt_done(ctx, instmt);
			}
		}
		else if(SP(instmt)->stt == STT_FORMAT) {
			DP(abr)->line = SP(instmt)->line;
			if(knh_StmtFORMAT_typing(ctx, instmt, abr, ns) == NULL) {
				knh_Stmt_done(ctx, instmt);
			}
		}
		else if(SP(instmt)->stt == STT_DONE || SP(instmt)->stt == STT_ERR) {
			;; /* NO perror */
		}
		else {
			knh_Asm_perror(ctx, abr, KERR_DWARN, _("don't use %s in class{}"), knh_stmt_tochar(SP(instmt)->stt));
		}
		instmt = DP(instmt)->next;
	}
	DP(abr)->this_cid = prev_cid;
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
Term *knh_Stmt_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	/* check statement or expr */
	if(reqt == TYPE_void) {  /* Statement */
		switch(SP(stmt)->stt) {
		case STT_BLOCK:
			if(!TERMs_typingBLOCK(ctx, stmt, 0, abr, ns, 1)) {
				return NULL;
			}
			return TM(stmt);
		case STT_DECL:
			return knh_StmtDECL_typing(ctx, stmt, abr, ns);
		case STT_SEPARATOR:
			return knh_StmtSEPARATOR_typing(ctx, stmt, abr, ns);
		case STT_IF:
			return knh_StmtIF_typing(ctx, stmt, abr, ns);
		case STT_SWITCH:
			return knh_StmtSWITCH_typing(ctx, stmt, abr, ns);
		case STT_WHILE:
			return knh_StmtWHILE_typing(ctx, stmt, abr, ns);
		case STT_DO:
			return knh_StmtDO_typing(ctx, stmt, abr, ns);
		case STT_FOR:
			return knh_StmtFOR_typing(ctx, stmt, abr, ns);
		case STT_FOREACH:
			return knh_StmtFOREACH_typing(ctx, stmt, abr, ns);
		case STT_BREAK:
		case STT_CONTINUE:
			return TM(stmt);
		case STT_TRY:
			return knh_StmtTRY_typing(ctx, stmt, abr, ns);
		case STT_THROW:
			return knh_StmtTHROW_typing(ctx, stmt, abr, ns);
		case STT_CALL1:
			return knh_StmtCALL1_typing(ctx, stmt, abr, ns, TYPE_void);
		case STT_RETURN:
			return knh_StmtRETURN_typing(ctx, stmt, abr, ns);
		case STT_PRINT:
			return knh_StmtPRINT_typing(ctx, stmt, abr, ns);
		case STT_ASSERT:
			return knh_StmtASSERT_typing(ctx, stmt, abr, ns);
		case STT_REGISTER:
			return knh_StmtREGISTER_typing(ctx, stmt, abr, ns);
		case STT_ERR:
		case STT_DONE:
			return TM(stmt);
		}
	}
	if(!knh_stmt_isExpr(SP(stmt)->stt)) {
		knh_Asm_perror(ctx, abr, KERR_EWARN, _("don't use %s HERE"), knh_stmt_tochar(SP(stmt)->stt));
		knh_Stmt_done(ctx, stmt);
		return TM(stmt);
	}
	{
		Stmt *rstmt = (Stmt*)knh_StmtEXPR_typing(ctx, stmt, abr, ns, reqt);
		if(rstmt != NULL && IS_Stmt(rstmt)) {
			return knh_Asm_lookupRegisteredStmt(ctx, abr, rstmt);
		}
		return TM(rstmt);
	}
}

/* ------------------------------------------------------------------------ */

int
knh_Stmt_typingBLOCK(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, int isIteration)
{
	int res = 1, level = DP(abr)->level ;
	Stmt *cur = stmt;
	while(IS_Stmt(cur)) {
		DP(abr)->line = SP(cur)->line;
		DP(abr)->level = level + 1;
		Term *tm = knh_Stmt_typing(ctx, cur, abr, ns, TYPE_void);
		if(tm == NULL) {
			knh_Stmt_toERR(ctx, stmt, TM(cur));
			res = 0;
			break;
		}
		if(isIteration == 0) break;
		if(IS_NULL(DP(cur)->next) && isIteration == 2) { /* toReturn*/
			knh_Stmt_setToReturn(cur, 1);
		}
		cur = DP(cur)->next;
	}
	knh_Asm_endRegister(ctx, abr, level + 1);
	DP(abr)->level = level;
	return res;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
