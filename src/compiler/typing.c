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

static Term *knh_Stmt_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt);
static int TERMs_typing(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, NameSpace *ns, knh_type_t reqt, int mode);

#define KNH_ASM_ASSERT(ctx, abr, c)   KNH_ASSERT(c)

/* ======================================================================== */
/* [getter] */

static
knh_fieldn_t knh_Token_getfnq(Ctx *ctx, Token *o)
{
	if(SP(o)->tt == TT_NAME) {
		return knh_getfnq(ctx, knh_Token_tobytes(ctx, o), FIELDN_NEWID);
	}
	else if(SP(o)->tt == TT_FN) {
		return DP(o)->fn;
	}
	DBG2_P("SP(o)->tt=%s", knh_token_tochar(SP(o)->tt));
	KNH_ASSERT(ctx == NULL);
	return FIELDN_NONAME;
}

/* ------------------------------------------------------------------------ */

static
knh_methodn_t knh_Token_getmn(Ctx *ctx, Token *tk)
{
	DBG2_ASSERT(IS_Token(tk));
	if(SP(tk)->tt == TT_MN) {
		return DP(tk)->mn;
	}
	else if(SP(tk)->tt == TT_FN) {
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
		if(SP(tk)->tt == TT_NAME) {
			knh_methodn_t mn = knh_getmn(ctx, name, METHODN_NEWID);
			if(knh_Token_isGetter(tk)) {
				return mn | KNH_FLAG_MN_GETTER;
			}
			if(knh_Token_isSetter(tk)) {
				return mn | KNH_FLAG_MN_SETTER;
			}
			return mn;
		}
		else if(SP(tk)->tt == TT_CMETHODN) {
			knh_index_t idx = knh_bytes_rindex(name, '.');
			if(idx != -1) {
				name = knh_bytes_last(name, idx+1);
			}
			knh_methodn_t mn = knh_getmn(ctx, name, METHODN_NEWID);
			return mn;
		}
		else if(SP(tk)->tt == TT_MT) {
			return knh_getmn(ctx, name, METHODN_NEWID) | KNH_FLAG_MN_MOVTEXT;
		}
		//DBG2_P("SP(o)->tt=%s, '%s'", knh_token_tochar(SP(tk)->tt), (char*)name.buf);
		return METHODN_NONAME;
	}
}

/* ======================================================================== */
/* [type] */

static
int knh_Token_isNullable(Ctx *ctx, Token *o)
{
	DBG2_ASSERT(IS_Token(o));
	if(knh_Token_isNullableType(o)) return 1;
	if(knh_Token_isNotNullType(o)) return 0;
	return 0; /* Default */
}

/* ------------------------------------------------------------------------ */

static
knh_type_t knh_Token_gettype(Ctx *ctx, Token *tk, NameSpace *ns, knh_class_t defc)
{
	DBG2_ASSERT(IS_Token(tk));
	knh_type_t type;
	if(SP(tk)->tt == TT_ASIS) {
		type = defc;
	}
	else if(SP(tk)->tt == TT_CID) {
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
	if(CLASS_type(type) == CLASS_Any) return NATYPE_Any;
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
	DBG2_ASSERT(IS_Token(tk));
	if(SP(tk)->tt == TT_CID) return DP(tk)->cid;
	if(knh_Token_isExceptionType(tk)) return CLASS_Exception;

	knh_bytes_t name = knh_Token_tobytes(ctx, tk);
	knh_class_t cid = knh_NameSpace_getcid(ctx, ns, name);

	if(cid == CLASS_unknown) {
		if(defc == CLASS_unknown) return cid;
		cid = defc;
		knh_Token_perror(ctx, tk, KERR_ERRATA, _("unknown class: %s ==> %C"), sToken(tk), defc);
	}
	return cid;
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
	SP(o)->tt = TT_CONST;
	DP(o)->type = knh_Object_cid(DP(o)->data);
	if(IS_NULL(DP(o)->data)) DP(o)->type = NATYPE_Any;
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
	SP(o)->tt = TT_DEFVAL;
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
		SP(tk)->tt = TT_SYSVAL;
		DP(tk)->index = KNH_SYS_CTX; DP(tk)->type = NNTYPE_Context;
		return 1;
	}
	else if(IS_SYSVAL(t, "IN") || IS_SYSVAL(t, "STDIN")) {
		SP(tk)->tt = TT_SYSVAL;
		DP(tk)->index = KNH_SYS_STDIN; DP(tk)->type = NNTYPE_InputStream;
		return 1;
	}
	else if(IS_SYSVAL(t, "OUT") || IS_SYSVAL(t, "STDOUT")) {
		SP(tk)->tt = TT_SYSVAL;
		DP(tk)->index = KNH_SYS_STDOUT; DP(tk)->type = NNTYPE_OutputStream;
		return 1;
	}
	else if(IS_SYSVAL(t, "ERR") || IS_SYSVAL(t, "STDERR")) {
		SP(tk)->tt = TT_SYSVAL;
		DP(tk)->index = KNH_SYS_STDERR; DP(tk)->type = NNTYPE_OutputStream;
		return 1;
	}
	else if(IS_SYSVAL(t, "OS")) {
		SP(tk)->tt = TT_SYSVAL;
		DP(tk)->index = KNH_SYS_OS; DP(tk)->type = NNTYPE_System;
		return 1;
	}
	else if(ISB(t, "__")) {
		SP(tk)->tt = TT_SYSVAL;
		DP(tk)->index = KNH_SYS_SCRIPT; DP(tk)->type = NNTYPE_Script;
		return 1;
	}
	else if(IS_SYSVAL(t, "__line__")) {
		knh_Token_setCONST(ctx, tk, UP(new_Int(ctx, SP(tk)->line)));
		return 1;
	}
	else if(IS_SYSVAL(t, "__file__")) {
		knh_Token_setCONST(ctx, tk, UP(knh_getResourceName(ctx, SP(tk)->uri)));
		return 1;
	}
	else if(IS_SYSVAL(t, "__method__") || IS_SYSVAL(t, "__function__")) {
		knh_Token_setCONST(ctx, tk, UP(knh_Object_getkey(ctx, UP(DP(abr)->mtd))));
		return 1;
	}
	else if(IS_SYSVAL(t, "__namespace__") || IS_SYSVAL(t, "__ns__")) {
		NameSpace *ns = knh_getCurrentNameSpace(ctx);
		knh_Token_setCONST(ctx, tk, UP(DP(ns)->nsname));
		return 1;
	}
	else if(IS_SYSVAL(t, "EOL")) {
		knh_Token_setCONST(ctx, tk, UP(TS_EOL));
		return 1;
	}
	else if(IS_SYSVAL(t, "BEGIN")) {
		knh_Token_setCONST(ctx, tk, UP(TS_BEGIN));
		return 1;
	}
	else if(IS_SYSVAL(t, "END")) {
		knh_Token_setCONST(ctx, tk, UP(TS_END));
		return 1;
	}
	return 0;
}

/* ======================================================================== */
/* [STACK, FIELD, GLOBAL, MEMBER] */

static
void knh_Token_toSTACK(Ctx *ctx, Token *tk, int sfpidx, knh_type_t type)
{
	SP(tk)->tt = TT_STACK;
	DP(tk)->index = (knh_short_t)sfpidx;
	DP(tk)->type = type;
}

/* ------------------------------------------------------------------------ */

static
void knh_Token_toFIELD(Ctx *ctx, Token *tk, int idx, knh_type_t type)
{
	SP(tk)->tt = TT_FIELD;
	DP(tk)->index = (knh_short_t)idx;
	DP(tk)->type = type;
}

/* ------------------------------------------------------------------------ */

static
void knh_Token_toGLOBAL(Ctx *ctx, Token *tk, int idx, knh_type_t type)
{
	SP(tk)->tt = TT_GLOBAL;
	DP(tk)->index = (knh_short_t)idx;
	DP(tk)->type = type;
}

/* ------------------------------------------------------------------------ */

//static
//void knh_Token_toMEMBER(Ctx *ctx, Token *tk, int sfi, int idx, knh_type_t type)
//{
//	SP(tk)->tt = TT_MEMBER;
//	DP(tk)->index = (knh_short_t)sfi;
//	KNH_SETv(ctx, DP(tk)->data, new_Int(ctx, idx));
//	DP(tk)->type = type;
//}

/* ------------------------------------------------------------------------ */

static
knh_index_t knh_Asm_addVariableTable(Ctx *ctx, Asm *abr,
		knh_cfield_t *cf, size_t max, knh_flag_t flag, knh_type_t type, knh_fieldn_t fn, Object *value)
{
	size_t idx;
	KNH_ASSERT_cid(CLASS_type(type));
	for(idx = 0; idx < max; idx++) {
		if(cf[idx].fn == FIELDN_NONAME) {
			cf[idx].flag = flag;
			cf[idx].fn   = fn;
			cf[idx].type = type;
			KNH_SETv(ctx, cf[idx].value, value);
			return idx;
		}
		if(cf[idx].fn == fn && fn != FIELDN_register) {
			if(cf[idx].type != type) {
				knh_Asm_perror(ctx, abr, KERR_ERROR, _("variable declared differently: %T %N"), cf->type, fn);
				return -1;
			}
			return idx;
		}
	}
	knh_Asm_perror(ctx, abr, KERR_ERROR, _("too many declared variables: must be %d < %d"), max, max);
	return -1;
}

/* ------------------------------------------------------------------------ */
/* [variable] */

static
int knh_Asm_declareScriptVariable(Ctx *ctx, Asm *abr, knh_flag_t flag, knh_type_t type, knh_fieldn_t fn, Object *value)
{
	knh_Script_t *scr = knh_getCurrentScript(ctx);
	knh_class_t cid = knh_Object_cid(scr);
	knh_cfield_t *cf = (ClassTable(cid).cstruct)->fields;
	knh_index_t idx = knh_Asm_addVariableTable(ctx, abr, cf, KNH_SCRIPT_FIELDSIZE, flag, type, fn, value);
	if(idx != -1) {
#ifdef KNH_USING_UNBOXFIELD
		if(IS_ubxint(type)) {
			if(sizeof(knh_int_t) > sizeof(void*)) {
				if(knh_Asm_addVariableTable(ctx, abr, cf, KNH_SCRIPT_FIELDSIZE, 0, TYPE_void, FIELDN_register, value) == -1) {
					return 0;
				}
			}
			knh_int_t *v = (knh_int_t*)(scr->fields + idx);
			v[0] = (IS_NULL(value)) ? 0 : ((Int*)value)->n.ivalue;
		}
		else if(IS_ubxfloat(type)) {
			if(sizeof(knh_float_t) > sizeof(void*)) {
				if(knh_Asm_addVariableTable(ctx, abr, cf, KNH_SCRIPT_FIELDSIZE, 0, TYPE_void, FIELDN_register, value) == -1) {
					return 0;
				}
			}
			knh_float_t *v = (knh_float_t*)(scr->fields + idx);
#ifndef KONOHA_ON_LKM
v[0] = (IS_NULL(value)) ? 0.0 : ((Float*)value)->n.fvalue;
#else
	v[0] = (IS_NULL(value)) ? 0 : ((Float*)value)->n.fvalue;
#endif
		}
		else if(IS_ubxboolean(type)) {
			knh_bool_t *v = (knh_bool_t*)(scr->fields + idx);
			v[0] = (IS_NULL(value)) ? 0 : ((Int*)value)->n.bvalue;
		}
		else {
			KNH_INITv(scr->fields[idx], value);
		}
#else
	KNH_INITv(scr->fields[idx], value);
#endif/*KNH_USING_UNBOXFIELD*/
	return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static
int knh_Asm_declareFieldVariable(Ctx *ctx, Asm *abr, knh_flag_t flag, knh_type_t type, knh_fieldn_t fn, Object *value)
{
	knh_index_t idx =
		knh_Asm_addVariableTable(ctx, abr, (knh_cfield_t*)DP(abr)->vars, KONOHA_LOCALSIZE, flag, type, fn, value);
	if(idx != -1) {
#ifdef KNH_USING_UNBOXFIELD
		if(IS_ubxint(type)) {
			if(sizeof(knh_int_t) > sizeof(void*)) {
				if(knh_Asm_addVariableTable(ctx, abr,
						(knh_cfield_t*)DP(abr)->vars, KONOHA_LOCALSIZE, 0, TYPE_void, FIELDN_register, value) == -1) {
					return -1;
				}
				if((idx + 1) > DP(abr)->vars_size) {
					DP(abr)->vars_size = (knh_ushort_t)(idx + 2);
				}
				return idx;
			}
		}
		else if(IS_ubxfloat(type)) {
			if(sizeof(knh_float_t) > sizeof(void*)) {
				if(knh_Asm_addVariableTable(ctx, abr,
						(knh_cfield_t*)DP(abr)->vars, KONOHA_LOCALSIZE, 0, TYPE_void, FIELDN_register, value) == -1) {
					return -1;
				}
				if((idx + 1) > DP(abr)->vars_size) {
					DP(abr)->vars_size = (knh_ushort_t)(idx + 2);
				}
				return idx;
			}
		}
#endif/*KNH_USING_UNBOXFIELD*/
if((idx + 1) > DP(abr)->vars_size) {
	DP(abr)->vars_size = (knh_ushort_t)(idx + 1);
}
return idx;
	}
	return -1;
}

/* ------------------------------------------------------------------------ */

static
knh_index_t knh_Asm_declareLocalVariable(Ctx *ctx, Asm *abr, knh_flag_t flag, knh_type_t type, knh_fieldn_t fn, Object *value)
{
	knh_index_t idx =
		knh_Asm_addVariableTable(ctx, abr, (knh_cfield_t*)DP(abr)->vars, KONOHA_LOCALSIZE, flag, type, fn, value);
	if(idx != -1 && (idx + 1) > DP(abr)->vars_size) {
		DP(abr)->vars_size = (knh_ushort_t)(idx + 1);
	}
	return idx;
}

/* ------------------------------------------------------------------------ */

knh_index_t knh_Asm_indexOfVariable(Asm *abr, knh_fieldn_t fnq)
{
	knh_fieldn_t fn = FIELDN_UNMASK(fnq);
	knh_index_t idx = 0;
	for(idx = 0; idx < DP(abr)->vars_size; idx++) {
		//DBG2_P("idx=%d, fn=%s, fnq=%s", idx, FIELDN(DP(abr)->vars[idx].fn), FIELDN(fn));
		if(DP(abr)->vars[idx].fn == fn) {
			return idx;
		}
		if(DP(abr)->vars[idx].fn == FIELDN_NONAME) {
			return -1;
		}
	}
	return -1;
}

#define knh_Asm_indexOfScriptVariable(abr, fnq)\
	knh_Class_queryField(ctx, knh_Object_cid(knh_getCurrentScript(ctx)), fnq)

#define knh_Asm_indexOfFieldVariable(abr, fnq)\
	knh_Class_queryField(ctx, DP(abr)->this_cid, fnq)

/* ------------------------------------------------------------------------ */

static
knh_cfield_t *knh_Asm_cfieldOfVariable(Asm *abr, knh_index_t idx)
{
	KNH_ASSERT(idx != -1 && idx < KONOHA_LOCALSIZE);
	KNH_ASSERT(DP(abr)->vars[idx].fn != FIELDN_NONAME);
	return (knh_cfield_t*)&(DP(abr)->vars[idx]);
}

/* ------------------------------------------------------------------------ */

static
int knh_Asm_globalIndex(Ctx *ctx, Asm *abr)
{
	if(DP(abr)->globalidx == -1) {
		DP(abr)->globalidx =
			knh_Asm_declareLocalVariable(ctx, abr, 0, NNTYPE_Script, FIELDN_GLOBAL, UP(knh_getCurrentScript(ctx)));
		if(DP(abr)->globalidx == -1) return 0;
	}
	return 1;
}



/* ------------------------------------------------------------------------ */

static int knh_TokenNAME_typing(Ctx *ctx, Token *tk, Asm *abr)
{
	knh_fieldn_t fnq = knh_Token_getfnq(ctx, tk);
	knh_index_t idx;
	if(fnq == FIELDN_NONAME) {
		goto L_ERROR;
	}

	if(fnq == FIELDN_super) {  /* super.f() */
		knh_type_t type = NNTYPE_cid(ctx->share->ClassTable[DP(abr)->this_cid].supcid);
		knh_Token_toSTACK(ctx, tk, 0, type);
		knh_Token_setSUPER(tk, 1);
		return 1;
	}

	if(FIELDN_IS_U1(fnq) || FIELDN_IS_SUPER(fnq)) goto L_FIELD;  /* _name */
	if(FIELDN_IS_U2(fnq)) goto L_GLOBAL; /* __name */


	idx = knh_Asm_indexOfVariable(abr, FIELDN_UNMASK(fnq));
	if(idx != -1) {
		knh_cfield_t *cf = knh_Asm_cfieldOfVariable(abr, idx);
		knh_type_t type = knh_pmztype_totype(ctx, cf->type, DP(abr)->this_cid);
		knh_Token_toSTACK(ctx, tk, idx, type);
		return 1;
	}

	L_FIELD:;
	idx = knh_Class_queryField(ctx, DP(abr)->this_cid, fnq);
	if(idx != -1) {
		knh_cfield_t *cf = knh_Class_fieldAt(ctx, DP(abr)->this_cid, idx);
		knh_type_t type = knh_pmztype_totype(ctx, cf->type, DP(abr)->this_cid);
		knh_Token_toFIELD(ctx, tk, idx, type);
		return 1;
	}
	if(FIELDN_IS_SUPER(fnq)) goto L_ERROR;

	L_GLOBAL:;
	{
		Script *scr = knh_getCurrentScript(ctx);
		idx = knh_Class_queryField(ctx, knh_Object_cid(scr), fnq);
		if(idx != -1) {
			knh_cfield_t *cf = knh_Class_fieldAt(ctx, knh_Object_cid(scr), idx);
			knh_type_t type = knh_pmztype_totype(ctx, cf->type, knh_Object_cid(scr));
			knh_Token_toGLOBAL(ctx, tk, idx, type);
			return knh_Asm_globalIndex(ctx, abr);
		}
	}
	if(knh_Token_toSYSVAL(ctx, tk, abr)) {
		return 1;
	}

	L_ERROR:;
	knh_Token_perror(ctx, tk, KERR_ERROR, _("undefined variable: %s"), sToken(tk));
	return 0;
}

/* ------------------------------------------------------------------------ */

static
int knh_TokenCONSTN_typing(Ctx *ctx, Token *tk, Asm *abr, NameSpace *ns)
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
	knh_Token_perror(ctx, tk, KERR_ERROR, _("unknown constant variable: %s"), sToken(tk));
	return 0;
}

/* ======================================================================== */
/* [CLASSID] */

//CLASSID                @system @P99
//FIELDN                 @system @P99
//METHODN                @system @P99
//OPERATOR               @system @P99
//NOP                    @system @P99

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* [CLASSID] */

static
void knh_Token_toCLASSID(Ctx *ctx, Token *o, knh_class_t cid)
{
	KNH_ASSERT_cid(cid);
	SP(o)->tt = TT_CLASSID;
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
		if(knh_Token_toSYSVAL(ctx, tk, abr)) {
			return 1;
		}
		knh_bytes_t t = knh_Token_tobytes(ctx, tk);
		Object *value = knh_NameSpace_getConstNULL(ctx, ns, t);
		if(value != NULL) {
			knh_Token_setCONST(ctx, tk, value);
			return 1;
		}
		knh_Token_perror(ctx, tk, KERR_ERROR, _("unknown class: %s"), sToken(tk));
		return 0;
	}
	knh_Token_toCLASSID(ctx, tk, cid);
	return 1;
}

/* ------------------------------------------------------------------------ */

static
int knh_TokenCMETHODN_typing(Ctx *ctx, Token *tk, NameSpace *ns)
{
	knh_bytes_t t = knh_Token_tobytes(ctx, tk);
	knh_index_t idx = knh_bytes_index(t, '.');
	if(idx == -1) return 0;

	knh_bytes_t cname = knh_bytes_first(t, idx);
	knh_class_t cid = knh_NameSpace_getcid(ctx, ns, cname);
	if(cid == CLASS_unknown) {
		knh_Token_perror(ctx, tk, KERR_ERROR, _("unknown class: %s"), sToken(tk));
		return 0;
	}
	t = knh_bytes_last(t, idx+1);
	knh_methodn_t mn = knh_getmn(ctx, t, METHODN_NONAME);
	Method *mtd = knh_Class_getMethod(ctx, cid, mn);
	if(IS_NULL(mtd)) {
		knh_Token_perror(ctx, tk, KERR_ERROR, _("undefined method: %s"), sToken(tk));
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
		knh_Token_perror(ctx, tk, KERR_ERROR, _("type error: %C is not numeric"), reqc);
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
				knh_Token_perror(ctx, tk, KERR_ERROR, _("invalid string: %O of %C"), DP(tk)->data, reqc);
				return 0;
			}
			knh_Token_setCONST(ctx, tk, UP(s));
			return 1;
		}
	}
	knh_Token_perror(ctx, tk, KERR_ERROR, _("type error: %C is not string"), reqc);
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
				knh_Token_perror(ctx, tk, KERR_ERROR, _("invalid string: '%B:%B' of %C"), tag, t, tagcid);
				return 0;
			}
		}
		else {
			knh_Token_setCONST(ctx, tk, new_Object_parseOf(ctx, (String*)DP(tk)->data));
		}
	}
	return 1;
}

/* ------------------------------------------------------------------------ */
/* [typing_Token] */

static
int knh_Token_typing(Ctx *ctx, Token *tk, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	if(SP(tk)->tt != TT_ASIS && knh_Token_isTyped(tk)) return 1;
	knh_class_t reqc = CLASS_type(reqt);

	switch(SP(tk)->tt) {
	case TT_CID:

	case TT_TYPEN:
		return knh_TokenTYEPN_typing(ctx, tk, abr, ns);
	case TT_CONSTN:
		return knh_TokenCONSTN_typing(ctx, tk, abr, ns);

	case TT_FN :
	case TT_NAME:
		return knh_TokenNAME_typing(ctx, tk, abr);
	case TT_NUM:
		return knh_TokenNUM_typing(ctx, tk, ns, reqc);
	case TT_CMETHODN:
		return knh_TokenCMETHODN_typing(ctx, tk, ns);
	case TT_URN:
		KNH_ASSERT(IS_String(DP(tk)->data));
		knh_Token_toCONST(ctx, tk);
		return 1;

	case TT_ESTR:
		TODO();
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
			DBG2_P("unknown tt=%s", knh_token_tochar(SP(tk)->tt));
	}
	knh_Token_perror(ctx, tk, KERR_ERROR, _("untyped token: %s"), sToken(tk));
	return 0;
}

/* ======================================================================== */
/* [ESTR] */

int knh_ismtchar(int c)
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
		SP(tk)->tt = TT_STR;
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
		return TM(stmt);
	}
}

/* ======================================================================== */
/* [TERMs] */

int TERMs_isCONST(Stmt *stmt, size_t n)
{
	Token *tk = DP(stmt)->tokens[n];
	return (IS_Token(tk) && SP(tk)->tt == TT_CONST);
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
		return (IS_Token(DP(stmt)->tokens[n]) && IS_NULL(DP(DP(stmt)->tokens[n])->data));
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
		if(SP(tk)->tt == TT_CONST) return DP(tk)->data;
		if(SP(tk)->tt == TT_ASIS) {
			return IS_NNTYPE(type) ?
					knh_getClassDefaultValue(ctx, CLASS_type(type)) : KNH_NULL;
		}
	}
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

static int TERMs_isASIS(Stmt *stmt, size_t n)
{
	Token *tk = DP(stmt)->tokens[n];
	return (IS_Token(tk) && SP(tk)->tt == TT_ASIS);
}

/* ------------------------------------------------------------------------ */

static int TERMs_isCLASSID(Stmt *stmt, size_t n)
{
	Token *tk = DP(stmt)->tokens[n];
	return (IS_Token(tk) && SP(tk)->tt == TT_CLASSID);
}

/* ------------------------------------------------------------------------ */

#define _TERMs_getcid(stmt, n)    CLASS_type(TERMs_gettype(stmt, n))
#define _TERMs_getbcid(stmt, n)   ctx->share->ClassTable[TERMs_getcid(stmt,n)].bcid

knh_type_t TERMs_gettype(Stmt *stmt, size_t n)
{
	if(IS_Token(DP(stmt)->tokens[n])) {
		Token *tk = DP(stmt)->tokens[n];
		KNH_ASSERT(knh_Token_isTyped(tk));
		return DP(tk)->type;
	}
	else {
		Stmt *stmt2 = DP(stmt)->stmts[n];
		KNH_ASSERT(knh_Stmt_isTyped(stmt2));
		return DP(stmt2)->type;
	}
}

/* ------------------------------------------------------------------------ */

static
void TERMs_perrorTYPE(Ctx *ctx, Stmt *stmt, size_t n, knh_type_t reqt)
{
	knh_type_t type = TERMs_gettype(stmt, n);
	DBG_P("TYPEERROR: type=%s%s reqt=%s%s", TYPEQN(type), TYPEQN(reqt));
	switch(SP(stmt)->stt) {
	case STT_CALL:
	case STT_NEW:
	case STT_OP:
	{
		Method *mtd = DP(DP(stmt)->tokens[0])->mtd;
		DBG2_ASSERT(IS_Method(mtd));
		knh_perror(ctx, SP(stmt)->uri, SP(stmt)->line,
				KERR_ERROR, _("type error: %T must be %T at the parameter %d of %M"), type, reqt, n - 1, DP(mtd)->mn);
	}
	break;
	case STT_DECL:
	case STT_LET:
		knh_perror(ctx, SP(stmt)->uri, SP(stmt)->line,
				KERR_ERROR, _("type error: %T must be %T at the assignment"), type, reqt);
		break;
		//	case STT_FOREACH:
		//		at = "foreach";
		//		if(n == 2) {
		//			if(knh_Stmt_isMAPNEXT(stmt)) at = "from ..";
		//			else at = "in ..";
		//		}
		//		else if(n == 3) {
		//			at = "where ..";
		//		}
		//		break;
	default :
		knh_perror(ctx, SP(stmt)->uri, SP(stmt)->line,
				KERR_ERROR, _("type error: %T must be %T at %s(%d)"), type, reqt, knh_stmt_tochar(SP(stmt)->stt), n);
	}
}

/* ------------------------------------------------------------------------ */

static
knh_type_t knh_Asm_typeinfer(Ctx *ctx, Asm *abr, knh_type_t type, char *varname)
{
	if(type == CLASS_Any || type == NNTYPE_Any) {
		//		knh_Asm_perror(ctx, abr, KERR_ERROR, _("error")WTYPEINF, varname);
	}
	return type;
}


/* ======================================================================== */
/* [STMT] */

void knh_Stmt_setType(Ctx *ctx, Stmt *stmt, knh_type_t type)
{
	//DBG2_P("stt=%s, type=%s%s", knh_stmt_tochar(SP(stmt)->stt), TYPEQN(type));
	DP(stmt)->type = type;
	knh_Stmt_setTyped(stmt, 1);
}

/* ------------------------------------------------------------------------ */
/* [DECL] */

static
knh_bool_t knh_Asm_existsName(Ctx *ctx, Asm *abr, knh_fieldn_t fnq)
{
	knh_index_t idx = -1;
	knh_fieldn_t fn = FIELDN_UNMASK(fnq);
	if(FIELDN_IS_U2(fnq)) goto L_GLOBAL;
	if(FIELDN_IS_U1(fnq)) goto L_FIELD;

	idx = knh_Asm_indexOfVariable(abr, fn);
	if(idx != -1) return 1;

	L_FIELD:;
	idx = knh_Class_queryField(ctx, DP(abr)->this_cid, fnq);
	if(idx != -1) return 1;

	L_GLOBAL:;
	idx = knh_Class_queryField(ctx, knh_Object_cid(knh_getCurrentScript(ctx)), fnq);
	if(idx != -1) return 1;
	return 0;
}

/* ------------------------------------------------------------------------ */

static
Object *knh_StmtDECL_value(Ctx *ctx, knh_type_t type)
{
	return IS_NNTYPE(type) ? knh_getClassDefaultValue(ctx, CLASS_type(type)) : KNH_NULL;
}

/* ------------------------------------------------------------------------ */

static void knh_StmtDECL_toLET(Ctx *ctx, Stmt *stmt)
{
	DBG2_ASSERT(SP(stmt)->stt == STT_DECL);
	SP(stmt)->stt = STT_LET;
	KNH_SETv(ctx, DP(stmt)->terms[0], DP(stmt)->terms[1]);
	KNH_SETv(ctx, DP(stmt)->terms[1], DP(stmt)->terms[2]);
	KNH_SETv(ctx, DP(stmt)->terms[2], KNH_NULL);
	DP(stmt)->size = 2;
}

/* ------------------------------------------------------------------------ */

Term * knh_StmtDECL_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	int level = DP(abr)->level;
	knh_fieldn_t fnq = knh_Token_getfnq(ctx, StmtDECL_name(stmt));
	knh_fieldn_t fn  = FIELDN_UNMASK(fnq);
	knh_flag_t flag  = knh_Stmt_metaflag__field(ctx, stmt);

	knh_type_t pmztype  = knh_Token_gettype(ctx, StmtDECL_type(stmt), ns, TYPE_Any/*var*/);
	knh_type_t type = knh_pmztype_totype(ctx, pmztype, DP(abr)->this_cid);

	if(TERMs_isNULL(ctx, stmt, 2) && !TERMs_isASIS(stmt, 2)
			&& !knh_Token_isNotNullType(DP(stmt)->tokens[0])) {
		DBG2_P("type inferencing: Nullable");
		type = CLASS_type(type);
	}

	/* Type name value */
	if(!TERMs_typing(ctx, stmt, 2, abr, ns, type, TCHECK_)) {
		return NULL;
	}

	if(type == TYPE_var) {
		type = TERMs_gettype(stmt, 2);
		DBG2_P("type inferencing: var => %s%s", TYPEQN(type));
		if(type == TYPE_var) type = TYPE_Any;
	}

	if(level == 0) {  /* SCRIPT VARIABLE */
		flag = flag | KNH_FLAG_CFF_GETTER | KNH_FLAG_CFF_SETTER;
		Object *value = knh_StmtDECL_value(ctx, type);
		if(!knh_Asm_declareScriptVariable(ctx, abr, flag, type, fn, value)) {
			return NULL;
		}
	}
	else if(level == 1) { /* FIELD VARIABLE */
		if(!FIELDN_IS_U1(fnq)) {
			flag |= KNH_FLAG_CFF_GETTER | KNH_FLAG_CFF_SETTER;
		}
		Object *value = TERMs_value(ctx, stmt, 2, type);
		if(!TERMs_isCONST(stmt, 2) && !TERMs_isASIS(stmt, 2)) {
			knh_Asm_perror(ctx, abr, KERR_EWARN, _("ignored initialization of field variable: %N"), fn);
		}
		knh_Asm_declareFieldVariable(ctx, abr, flag, type, fn, value);
		knh_Stmt_done(ctx, stmt);
		return TM(stmt);
	}
	else if(level == -1 || level == -2) {  /* -1 OUTER_PARAM, -2: INNER_PARAM */
		Object *value = KNH_NULL;
		if(TERMs_isCONST(stmt, 2)) {
			value = TERMs_const(stmt, 2);
			if(IS_NOTNULL(value)) {
				if(TERMs_isASIS(stmt, 0)) {  /* (a = 1) ==> Int a = 1 */
					type = NATYPE_cid(knh_Object_cid(value));
				}
				else {  /* Int! a = 1 ==> Int a = 1 */
					type = NATYPE_cid(type);
				}
				if(level == -2) {
					type = NNTYPE_cid(type);  // a = 1 ==> Int! if inner
				}
			}
		}
		knh_Asm_declareLocalVariable(ctx, abr, flag, type, fn, value);
		return TM(stmt);
	}
	else {
		Object *value = knh_StmtDECL_value(ctx, type);
		if(FIELDN_IS_U2(fnq) || FIELDN_IS_U1(fnq)) {
			knh_Asm_perror(ctx, abr, KERR_EWARN, _("ignored scope of script/field variable: %N"), fn);
		}
		knh_Asm_declareLocalVariable(ctx, abr, flag, type, fn, value);
	}

	if(TERMs_isASIS(stmt, 2)) {
		knh_Stmt_done(ctx, stmt);
	}
	else {
		knh_StmtDECL_toLET(ctx, stmt);
		if(!TERMs_typing(ctx, stmt, 0, abr, ns, TYPE_Any, TWARN_)) {
			return NULL;
		}
	}
	return TM(stmt);
}

/* ======================================================================== */
/* [LET] */

static
int TERMs_isCONSTNAME(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, NameSpace *ns)
{
	Token *tk = DP(stmt)->tokens[n];
	if(!IS_Token(tk)) return 0;
	if(SP(tk)->tt == TT_CONSTN) {
		if(knh_Token_toSYSVAL(ctx, tk, abr)) {
			return 0;
		}
		return 1;
	}
	if(SP(tk)->tt == TT_TYPEN) {
		knh_bytes_t cname = knh_Token_tobytes(ctx, tk);
		size_t i;
		for(i = 0; i < cname.len; i++) {
			if(islower(cname.buf[i])) return 0;
		}
		knh_class_t cid = knh_NameSpace_getcid(ctx, ns, cname);
		return (cid == CLASS_unknown);
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtLET_declConst(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, int level)
{
	Token *tk = DP(stmt)->tokens[0];
	knh_bytes_t cn = knh_Token_tobytes(ctx, tk);

	if(level > 1) {
		goto L_NOTHERE;
	}

	if(!TERMs_typing(ctx, stmt, 1, abr, ns, TYPE_Any, TWARN_)) {
		return NULL;
	}

	if(!TERMs_isCONST(stmt, 1)) {
		knh_Token_perror(ctx, tk, KERR_ERROR, _("syntax error: r-value is not const: %s"), sToken(tk));
		return NULL;
	}

	{
		Object *value = TERMs_const(stmt, 1);
		knh_index_t dotidx = knh_bytes_index(cn, '.');

		if(level == 0) {
			if(dotidx == -1) {
				if(knh_NameSpace_getConstNULL(ctx, ns, cn)) {
					goto L_DUPCONST;
				}
				KNH_ASSERT(IS_String(DP(tk)->text));
				knh_NameSpace_addConst(ctx, ns, DP(tk)->text, value);
			}
			else {
				knh_bytes_t fn = knh_bytes_first(cn, dotidx);
				knh_class_t cid = knh_NameSpace_getcid(ctx, ns, fn);
				if(cid == CLASS_unknown) {
					knh_Token_perror(ctx, tk, KERR_ERROR, _("unknown class: %B"), fn);
					return NULL;
				}
				if(!knh_addClassConst(ctx, cid, new_String(ctx, knh_bytes_last(cn, dotidx+1), NULL), value)) {
					goto L_DUPCONST;
				}
			}
		}
		else if(level == 1) {
			knh_class_t cid = DP(abr)->this_cid;
			if(dotidx != -1) {
				goto L_NOTHERE;
			}
			if(!knh_addClassConst(ctx, cid, new_String(ctx, knh_bytes_last(cn, dotidx+1), NULL), value)) {
				goto L_DUPCONST;
			}
		}
		knh_Stmt_done(ctx, stmt);
		return TM(stmt);
	}

	L_NOTHERE:
	knh_Token_perror(ctx, tk, KERR_ERROR, _("syntax error: don't declare const HERE: %s"), sToken(tk));
	return NULL;

	L_DUPCONST:
	knh_Token_perror(ctx, tk, KERR_ERROR, _("cannot override the existing const: %s"), sToken(tk));
	return NULL;
}

/* ------------------------------------------------------------------------ */

Term *knh_StmtLET_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	int level = DP(abr)->level;
	if(TERMs_isCONSTNAME(ctx, stmt, 0, abr, ns)) {
		return knh_StmtLET_declConst(ctx, stmt, abr, ns, level);
	}
	if(knh_Token_isTyped(DP(stmt)->tokens[0])) {
		if(!TERMs_typing(ctx, stmt, 1, abr, ns, TERMs_gettype(stmt, 0), TCHECK_)) {
			return NULL;
		}
		return TM(stmt);
	}

	Token *tk0 = DP(stmt)->tokens[0];
	knh_fieldn_t fnq = knh_Token_getfnq(ctx, tk0);
	knh_fieldn_t fn = FIELDN_UNMASK(fnq);
	if(fn == FIELDN_NONAME) {
		knh_Token_perror(ctx, tk0, KERR_ERROR, _("unavailable l-value: %s"), sToken(tk0));
		return NULL;
	}

	knh_flag_t  flag = KNH_FLAG_CFF_AUTONAME;
	int existsName = 0;
	if(level == 0) {  /* SCRIPT LEVEL */
		if(knh_Asm_indexOfScriptVariable(abr, fnq) != -1) {
			existsName = 1;
		}
	}
	else if(level > 1) {  /* LOCAL LEVEL */
		if(knh_Asm_existsName(ctx, abr, fnq)) {
			existsName = 1;
		}
		else if(FIELDN_IS_U1(fnq) || FIELDN_IS_U2(fnq)) {
			knh_Token_perror(ctx, tk0, KERR_ERROR, _("undefined variable: %s"), sToken(tk0));
			return NULL;
		}
	}

	//DBG2_P("LEVEL=%d, existsName=%d", level, existsName);
	if(existsName == 0){   /* TYPE INFERENCING : a = 1 */
		if(!TERMs_typing(ctx, stmt, 1, abr, ns, TYPE_Any, TCHECK_)) {
			return NULL;
		}
		knh_type_t type = TERMs_gettype(stmt, 1);
		type = knh_Asm_typeinfer(ctx, abr, type, FIELDN(fn));
		Object *value = TERMs_value(ctx, stmt, 1, type);

		if(level == 0) { /* SCRIPT LEVEL */
			Script *scr = knh_getCurrentScript(ctx);
			DP(abr)->this_cid = knh_Object_cid(scr);
			//KNH_ASSERT(DP(abr)->vars_size == 1);  /* That means prepared */
			flag |= KNH_FLAG_CFF_GETTER | KNH_FLAG_CFF_SETTER;
			if(!knh_Asm_declareScriptVariable(ctx, abr, flag, type, fn, value)) {
				return NULL;
			}
		}
		else if(level == 1) {  /* CLASS FIELD LEVEL */
			if(!TERMs_isCONST(stmt, 1)) {
				knh_Asm_perror(ctx, abr, KERR_ERROR, _("ignored value of field variable: %s"), sToken(tk0));
			}
			// flag |= KNH_FLAG_CFF_GETTER | KNH_FLAG_CFF_SETTER;
			knh_Asm_declareFieldVariable(ctx, abr, flag, type, fn, value);
			knh_Stmt_done(ctx, stmt);
			return TM(stmt);
		}
		else if(level > 1) { /* LOCAL_LEVEL */
			knh_Asm_declareLocalVariable(ctx, abr, flag, type, fn, value);
		}
		if(!TERMs_typing(ctx, stmt, 0, abr, ns, TYPE_Any, TCHECK_)) {
			return NULL;
		}
		knh_Stmt_setType(ctx, stmt, type);
	}
	else {
		if(!TERMs_typing(ctx, stmt, 0, abr, ns, TYPE_Any, TCHECK_)) {
			return NULL;
		}
		if(SP(tk0)->tt != TT_STACK && SP(tk0)->tt != TT_GLOBAL && SP(tk0)->tt != TT_FIELD) {
			knh_Asm_perror(ctx, abr, KERR_ERROR, _("unavailable l-value: %s"), sToken(tk0));
			return NULL;
		}
		knh_type_t type = TERMs_gettype(stmt, 0);
		if(!TERMs_typing(ctx, stmt, 1, abr, ns, type, TCHECK_)) {
			return NULL;
		}
		knh_Stmt_setType(ctx, stmt, type);
	}
	if(reqt != TYPE_void) {
		TODO();
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
		if(TERMs_typing(ctx, stmt, 0, abr, ns, TYPE_Any, TWARN_)) {
			knh_Stmt_setType(ctx, stmt, TERMs_gettype(stmt, 0));
		}
		else {
			knh_Stmt_done(ctx, stmt);
		}
		return TM(stmt);
	}
	else {
		TERMs_typing(ctx, stmt, 0, abr, ns, reqt, TCHECK_);
		return DP(stmt)->terms[0];
	}
}

/* ------------------------------------------------------------------------ */

static
knh_Class_t *new_Class__type(Ctx *ctx, knh_type_t type)
{
	knh_Class_t *o = (knh_Class_t*)new_hObject(ctx, FLAG_Class, CLASS_Class, CLASS_Class);
	o->type = type;
	o->cid = CLASS_type(type);
	return o;
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
		if(!IS_Token(tk) || SP(tk)->tt != TT_CONST) {
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
	SP(tk)->tt = TT_MN;
	DP(tk)->mn = mn;
	KNH_SETv(ctx, DP(tk)->data, mtd);
	DP(tk)->type = TYPE_Method;
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtPARAMS_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_class_t mtd_cid, Method *mtd)
{
	KNH_ASSERT(IS_Method(mtd));
	size_t i, size = DP(stmt)->size;
	knh_type_t rtype = knh_pmztype_totype(ctx, knh_Method_rztype(mtd), mtd_cid);
	knh_Stmt_setType(ctx, stmt, rtype);

	for(i = 0; i < knh_Method_psize(mtd); i++) {
		knh_type_t reqt = knh_pmztype_totype(ctx, knh_Method_pztype(mtd, i), mtd_cid);
		size_t n = i + 2; //DBG2_P("reqt[%d]=%d,%s%s", n, reqt, TYPEQN(reqt));
		if(n < size) {
			if(!TERMs_typing(ctx, stmt, n, abr, ns, reqt, TCHECK_)) {
				return NULL;
			}
		}
		else {
			if(IS_NNTYPE(reqt)) {
				knh_Asm_perror(ctx, abr, KERR_ERROR, _("too few parameters: %C.%M"), mtd_cid, DP(mtd)->mn);
				return NULL;
			}
			else if(!knh_Method_isVarArgs(mtd)) {
				Token *tk = new_TokenCONST(ctx, UP(stmt), KNH_NULL);
				DP(tk)->type = CLASS_type(reqt);
				knh_Stmt_add(ctx, stmt, UP(tk));
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
		//DBG2_P("i+2=%d, size=%d", i+2, size);
		knh_Asm_perror(ctx, abr, KERR_DWARN, _("too many parameters: %C.%M"), mtd_cid, DP(mtd)->mn);
		DP(stmt)->size = i + 2;
	}
	return knh_StmtCALL_toCONST(ctx, stmt, mtd);
}

/* ------------------------------------------------------------------------ */

static int knh_type_isClosure(Ctx *ctx, knh_type_t type)
{
	knh_class_t cid = CLASS_type(type);
	KNH_ASSERT_cid(cid);
	return (ClassTable(cid).bcid == CLASS_Closure);
}

/* ------------------------------------------------------------------------ */

static int knh_TokenNAME_isClosure(Ctx *ctx, Token *tk, Asm *abr)
{
	knh_fieldn_t fnq = knh_Token_getfnq(ctx, tk);
	if(fnq == FIELDN_NONAME) return 0;

	if(FIELDN_IS_U1(fnq) || FIELDN_IS_SUPER(fnq)) goto L_FIELD;  /* _name */
	if(FIELDN_IS_U2(fnq)) goto L_GLOBAL; /* __name */

	{
		knh_index_t idx = knh_Asm_indexOfVariable(abr, FIELDN_UNMASK(fnq));
		if(idx != -1) {
			knh_cfield_t *cf = knh_Asm_cfieldOfVariable(abr, idx);
			knh_type_t type = knh_pmztype_totype(ctx, cf->type, DP(abr)->this_cid);
			if(knh_type_isClosure(ctx, type)) {
				knh_Token_toSTACK(ctx, tk, idx, type);
				return 1;
			}
			return 0;
		}
	}

	L_FIELD:;
	{
		knh_index_t idx = knh_Class_queryField(ctx, DP(abr)->this_cid, fnq);
		if(idx != -1) {
			knh_cfield_t *cf = knh_Class_fieldAt(ctx, DP(abr)->this_cid, idx);
			knh_type_t type = knh_pmztype_totype(ctx, cf->type, DP(abr)->this_cid);
			if(knh_type_isClosure(ctx, type)) {
				knh_Token_toFIELD(ctx, tk, idx, type);
				return 1;
			}
			return 0;
		}
	}

	L_GLOBAL:;
	{
		Script *scr = knh_getCurrentScript(ctx);
		knh_index_t idx = knh_Class_queryField(ctx, knh_Object_cid(scr), fnq);
		if(idx != -1) {
			knh_cfield_t *cf = knh_Class_fieldAt(ctx, knh_Object_cid(scr), idx);
			knh_type_t type = knh_pmztype_totype(ctx, cf->type, knh_Object_cid(scr));
			if(knh_type_isClosure(ctx, type)) {
				knh_Token_toGLOBAL(ctx, tk, idx, type);
				knh_Asm_globalIndex(ctx, abr);
				return 1;
			}
		}
	}
	return 0;
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
		knh_Stmt_setType(ctx, stmt, TYPE_Any);
		return TM(stmt);
	}

	knh_Stmt_setType(ctx, stmt, ClassTable(cid).r0);

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
	if(IS_Stmt(tk1) || SP(tk1)->tt != TT_ASIS) {
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
	char *emsg = _("wrong parameters: built-in function %s()");
	if(mn == METHODN_typeof) {
		if(DP(stmt)->size != 3) goto L_ERROR;
		if(TERMs_typing(ctx, stmt, 2, abr, ns, TYPE_Any, TWARN_)) {
			knh_Token_setCONST(ctx, tk1, UP(new_Class__type(ctx, TERMs_gettype(stmt, 2))));
			return TM(tk1);
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
			knh_Stmt_setType(ctx, stmt,
					NNTYPE_cid(knh_class_Generics(ctx, CLASS_Array, cid1, CLASS_Any)));
			return TM(stmt);
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
		knh_class_t mtd_cid = CLASS_type(DP(abr)->vars[0].type);
		Token *tkMTD = DP(stmt)->tokens[0]; /* change */
		if(mn == METHODN_super) {
			KNH_ASSERT_cid(mtd_cid);
			if(ClassTable(mtd_cid).supcid == CLASS_Object) {
				knh_Asm_perror(ctx, abr,
					KERR_ERROR, _("%s is not extended"), CTXCLASSN(mtd_cid));
				return NULL;
			}
			mtd_cid = ClassTable(mtd_cid).supcid;
		}
		SP(tkMTD)->tt = TT_MN;
		DP(tkMTD)->mn = METHODN_new;
		knh_Token_toSTACK(ctx, tk1, 0, NNTYPE_cid(mtd_cid));
		return TM(stmt);
	}
	else if(mn == METHODN_delegate) { /* delegate */
		knh_class_t cid;
		if(DP(stmt)->size == 4) { /* delegate(a,f) */
			Token *ftk = DP(stmt)->tokens[3];
			if(!IS_Token(ftk)) goto L_ERROR;
			knh_methodn_t mn = knh_Token_getmn(ctx, ftk);
			if(!TERMs_typing(ctx, stmt, 2, abr, ns, TYPE_Any, TWARN_)) {
				return NULL;
			}
			if(TERMs_isCLASSID(stmt, 2)) {
				Token *ctk = DP(stmt)->tokens[2];
				knh_Token_toDEFVAL(ctk, DP(ctk)->cid);
			}
			cid = TERMs_getcid(stmt, 2);
			Method *mtd = knh_Class_getMethod(ctx, cid, mn);
			if(IS_NULL(mtd)) { emsg = _("undefined method: %s"); goto L_ERROR; }
			knh_Token_setCONST(ctx, DP(stmt)->tokens[3], UP(mtd));
			cid = knh_class_MethodClosure(ctx, cid, mtd);
		}
		else if(DP(stmt)->size == 3) { /* delegate(f) */
			Token *ftk = DP(stmt)->tokens[2];
			if(!IS_Token(ftk)) goto L_ERROR;
			knh_methodn_t mn = knh_Token_getmn(ctx, ftk);
			cid = CLASS_type(DP(abr)->vars[0].type);
			Method *mtd = knh_Class_getMethod(ctx, cid, mn);
			if(IS_NULL(mtd)) {
				Script *scr = knh_getCurrentScript(ctx);
				cid = knh_Object_cid(scr);
				mtd = knh_Class_getMethod(ctx, cid, mn);
				if(IS_NULL(mtd)) { emsg = _("undefined method: %s"); goto L_ERROR; }
				knh_Token_setCONST(ctx, DP(stmt)->tokens[2], UP(scr));
			}
			else {
				knh_Token_toSTACK(ctx, ftk, 0, DP(abr)->vars[0].type);
			}
			knh_Stmt_add(ctx, stmt, UP(new_TokenCONST(ctx, FL(stmt), UP(mtd))));
			cid = knh_class_MethodClosure(ctx, cid, mtd);
		}
		else {
			goto L_ERROR;
		}
		knh_Token_toCLASSID(ctx, tk1, cid);
		SP(stmt)->stt = STT_NEW;
		Method *mtd = knh_Class_getMethod(ctx, CLASS_Closure, METHODN_new);
		KNH_ASSERT((IS_Method(mtd)));
		knh_Token_toMTD(ctx, DP(stmt)->tokens[0], mn, mtd);
		//DBG2_P("cid=%s", CLASSN(cid));
		knh_Stmt_setType(ctx, stmt, NNTYPE_cid(cid));
		return TM(stmt);
	}
	else if(mn == METHODN_proceed) { /* proceed() */
		knh_Asm_setPROCEED(abr, 1);
		SP(stmt)->stt = STT_PROCEED;
		Method *mtd = DP(abr)->mtd;
		knh_Token_toMTD(ctx, DP(stmt)->tokens[0], DP(mtd)->mn, mtd);
		knh_Token_toSTACK(ctx, tk1, 0, DP(abr)->vars[0].type);
		if(DP(stmt)->size > 1) {
			knh_StmtPARAMS_typing(ctx, stmt, abr, ns, CLASS_type(DP(abr)->vars[0].type), mtd);
		}
		knh_Stmt_setType(ctx, stmt, DP(abr)->rtype);
		return TM(stmt);
	}
	else if(mn == METHODN_likely || mn == METHODN_unlikely) { /* likely() */
		if(DP(stmt)->size != 3) goto L_ERROR;
		if(TERMs_typing(ctx, stmt, 2, abr, ns, TYPE_Boolean, TCHECK_)) {
			return DP(stmt)->terms[2];
		}
		return NULL;
	}
	else {
		char bufmn[CLASSNAME_BUFSIZ];
		knh_format_methodn(ctx, bufmn, sizeof(bufmn), mn);
		//DBG2_P("0. lookup closure..");
		if(knh_TokenNAME_isClosure(ctx, DP(stmt)->tokens[0], abr)) {
			return knh_StmtINVOKE_typing(ctx, stmt, abr, ns);
		}

		//DBG2_P("1. lookup function.. %s()", bufmn);
		knh_class_t mtd_cid = knh_NameSpace_getFuncClass(ctx, ns, B(bufmn));
		if(mtd_cid != CLASS_unknown) {
			KNH_ASSERT_cid(mtd_cid);
			knh_Token_toDEFVAL(tk1, mtd_cid);
			return TM(stmt);
		}

		//DBG2_P("2. lookup this.%s()", bufmn);
		if(DP(abr)->vars[0].fn == FIELDN_this) {
			mtd_cid = CLASS_type(DP(abr)->vars[0].type);
			Method *mtd = knh_Class_getMethod(ctx, mtd_cid, mn);
			if(IS_NOTNULL(mtd)) {
				knh_Token_toSTACK(ctx, tk1, 0, DP(abr)->vars[0].type);
				return TM(stmt);
			}
		}

		//DBG2_P("3. lookup script function %s()", bufmn);
		Script *scr = knh_getCurrentScript(ctx);
		mtd_cid = knh_Object_cid(scr);
		Method *mtd = knh_Class_getMethod(ctx, mtd_cid, mn);
		//KNH_ASSERT(IS_NOTNULL(mtd));
		if(IS_NOTNULL(mtd)) {
			knh_Token_setCONST(ctx, tk1, UP(scr));
			return TM(stmt);
		}
		emsg = _("undefined method: %s");
	}

	L_ERROR:;
	knh_Asm_perror(ctx, abr, KERR_ERROR, emsg, sToken(DP(stmt)->tokens[0]));
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtCALL_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_class_t reqt)
{
	DBG2_ASSERT(DP(stmt)->size > 1);
	knh_methodn_t mn = knh_Token_getmn(ctx, DP(stmt)->tokens[0]);
	if(mn == METHODN_new) {
		/* reported by Dr. Maeda */
		knh_Asm_perror(ctx, abr, KERR_ERROR, _("don't call a %M method"), mn);
		return NULL;
	}

	Term *tm = knh_StmtCALLBASE_typing(ctx, stmt, abr, ns, mn);
	if(tm == NULL || IS_Token(tm) || knh_Stmt_isTyped(stmt)) {
		return tm;
	}
	if(mn == METHODN_super || mn == METHODN_this) {
		mn = METHODN_new;
	}
	knh_type_t    btype   = TERMs_gettype(stmt, 1);
	knh_class_t   mtd_cid = CLASS_type(btype);
	Method *mtd = knh_Class_getMethod(ctx, mtd_cid, mn);
	if(mtd_cid != CLASS_Any && IS_NULL(mtd)) {
		knh_Asm_perror(ctx, abr, KERR_ERROR, _("undefined method: %C.%M"), mtd_cid, mn);
		return NULL;
	}
	knh_Token_toMTD(ctx, DP(stmt)->tokens[0], mn, mtd);
	if(IS_Token(DP(stmt)->tokens[1]) && knh_Token_isSUPER(DP(stmt)->tokens[1])) {
		knh_Token_setSUPER(DP(stmt)->tokens[0], 1);
	}

	if(IS_NOTNULL(mtd)) {
		Term *tm = knh_StmtPARAMS_typing(ctx, stmt, abr, ns, mtd_cid, mtd);
		if(tm != NULL && IS_Stmt(tm)) {
			if(knh_methodn_isNew(ctx, mn)) {
				knh_Stmt_setType(ctx, stmt, TYPE_void);
			}
		}
		return TM(tm);
	}
	else {
		int i;
		for(i = 2; i < DP(stmt)->size; i++) {
			if(!TERMs_typing(ctx, stmt, i, abr, ns, TYPE_Any, TWARN_)) {
				return NULL;
			}
		}
		knh_Stmt_setType(ctx, stmt, TYPE_Any);
		return UP(stmt);
	}
}

/* ------------------------------------------------------------------------ */
/* [NEW] */

static
Term *knh_StmtNEW_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_class_t reqt)
{
	DBG2_ASSERT(DP(stmt)->size > 1);
	knh_methodn_t mn = knh_Token_getmn(ctx, DP(stmt)->tokens[0]);

	knh_class_t mtd_cid = knh_Token_getcid(ctx, DP(stmt)->tokens[1], ns, CLASS_unknown);
	if(mtd_cid == CLASS_Exception) {
		Token *mtk = new_TokenCONST(ctx, FL(stmt), DP(DP(stmt)->tokens[1])->data);
		mn = METHODN_new__init;
		if(DP(stmt)->size == 2) {
			knh_Stmt_add(ctx, stmt, TM(mtk));
		}
		else if(DP(stmt)->size == 3) {
			knh_Stmt_add(ctx, stmt, DP(stmt)->terms[2]);
			KNH_SETv(ctx, DP(stmt)->terms[2], mtk);
		}
		else if(DP(stmt)->size == 4) {
			knh_Stmt_add(ctx, stmt, DP(stmt)->terms[3]);
			KNH_SETv(ctx, DP(stmt)->terms[3], DP(stmt)->terms[2]);
			KNH_SETv(ctx, DP(stmt)->terms[2], mtk);
		}
		else {
			KNH_SETv(ctx, DP(stmt)->terms[4], DP(stmt)->terms[3]);
			KNH_SETv(ctx, DP(stmt)->terms[3], DP(stmt)->terms[2]);
			KNH_SETv(ctx, DP(stmt)->terms[2], mtk);
		}
	}

	if(mtd_cid == CLASS_unknown) {
		if(!IS_NNTYPE(reqt)) {
			knh_Token_perror(ctx, DP(stmt)->tokens[1], KERR_ERRATA, _("unknown class: %s ==> null"), sToken(DP(stmt)->tokens[1]));
			return TM(new_TokenNULL(ctx, FL(DP(stmt)->tokens[1]), reqt));
		}
		else {
			knh_Token_perror(ctx, DP(stmt)->tokens[1], KERR_ERROR, _("unknown class: %s"), sToken(DP(stmt)->tokens[1]));
		}
		return NULL;
	}

	if(mtd_cid == CLASS_Array) {
		knh_class_t reqc = CLASS_type(reqt);
		KNH_ASSERT_cid(reqc);
		knh_class_t bcid = ctx->share->ClassTable[reqc].bcid;
		if(bcid == CLASS_Array || bcid == CLASS_IArray || bcid == CLASS_FArray) {
			mtd_cid = reqc;
		}
		else if(reqc == CLASS_Any && mn == METHODN_new__init && DP(stmt)->size > 2) {
			if(!TERMs_typing(ctx, stmt, 2, abr, ns, CLASS_Any, TWARN_)) {
				return NULL;
			}
			knh_type_t icid = TERMs_getcid(stmt, 2);
			if(icid != CLASS_Any) {
				int i;
				for(i = 3; i < DP(stmt)->size; i++) {
					if(!TERMs_typing(ctx, stmt, i, abr, ns, CLASS_Any, TWARN_)) {
						return NULL;
					}
					if(icid != TERMs_getcid(stmt, i)) {
						icid = CLASS_Any;
						break;
					}
				}
				if(icid != CLASS_Any) {
					mtd_cid = knh_class_Array(ctx, icid);
				}
			}
		}
	}

	KNH_ASSERT_cid(mtd_cid);
	Method *mtd = knh_Class_getMethod(ctx, mtd_cid, mn);
	if(IS_NULL(mtd) || knh_class_isPrivate(mtd_cid) || knh_Method_isPrivate(mtd)) {
		knh_Asm_perror(ctx, abr, KERR_ERROR, _("unknown constructor: %s %C(...)"), sToken(DP(stmt)->tokens[0]), mtd_cid);
		return NULL;
	}
	DP(DP(stmt)->tokens[1])->cid = mtd_cid;
	knh_Token_toMTD(ctx, DP(stmt)->tokens[0], mn, mtd);
	return knh_StmtPARAMS_typing(ctx, stmt, abr, ns, mtd_cid, mtd);
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

static
int knh_Stmt_checkOPSIZE(Ctx *ctx,Stmt *stmt, size_t n)
{
	if(DP(stmt)->size == n + 1) return 1;
	if(n == 1) {
		knh_perror(ctx, SP(stmt)->uri, SP(stmt)->line, KERR_ERROR, _("must be uniary operator"));
	}
	else if(n == 2) {
		knh_perror(ctx, SP(stmt)->uri, SP(stmt)->line, KERR_ERROR, _("must be binary operator"));
	}
	else {
		knh_perror(ctx, SP(stmt)->uri, SP(stmt)->line, KERR_ERROR, _("syntax error"));
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtOP_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	DBG2_ASSERT(DP(stmt)->size > 1);
	size_t opsize = DP(stmt)->size - 1;
	Token *optk = DP(stmt)->tokens[0];
	knh_methodn_t mn = knh_token_tomethodn(SP(optk)->tt);
	KNH_ASM_ASSERT(ctx, abr, mn != METHODN_NONAME);
	knh_class_t mtd_cid = CLASS_unknown;

	size_t i;
	for(i = 1; i < opsize + 1; i++) {
		if(!TERMs_typing(ctx, stmt, i, abr, ns, CLASS_Any, TWARN_)) {
			return NULL;
		}
		if(TERMs_getbcid(stmt, i) == CLASS_String) {
			mtd_cid = CLASS_String;
		}
	}

	switch(mn) {
	case METHODN_opAdd:
	{
		if(opsize == 1) { /* +1 */
			return DP(stmt)->terms[1];
		}
		if(mtd_cid == CLASS_String) {
			if(opsize > 2) {
				mn = METHODN_concat;
			}
			break;
		}
	}
	case METHODN_opSub:
	case METHODN_opMul:
	case METHODN_opDiv:
	{
		if(opsize > 2) {
			return knh_StmtTOBINARY_typing(ctx, stmt, abr, ns, reqt);
		}
		if(!knh_Stmt_checkOPSIZE(ctx, stmt, 2)) {
			return NULL;
		}
		mtd_cid = knh_StmtOPADD_basecid(ctx, stmt);
		break;
	}

	case METHODN_opEq:
	{
		if(!knh_Stmt_checkOPSIZE(ctx, stmt, 2)) {
			return NULL;
		}
		if(TERMs_isNULL(ctx, stmt, 1) || TERMs_isTRUE(stmt, 1) || TERMs_isFALSE(stmt, 1)) {
			Term *temp = DP(stmt)->terms[1];
			DP(stmt)->terms[1] = DP(stmt)->terms[2];
			DP(stmt)->terms[2] = temp;
		}
		if(TERMs_isNULL(ctx, stmt, 2)) { /* o == null */
			if(IS_NNTYPE(TERMs_gettype(stmt,1))) {
				return TM(new_TokenCONST(ctx, FL(stmt), KNH_FALSE));
			}
		mn = METHODN_isNull;
		mtd_cid = CLASS_Object;
		DP(stmt)->size = 2;
		break;
		}
		if(TERMs_isTRUE(stmt, 2)) {  /* b == true */
			if(TERMs_gettype(stmt, 1) == NNTYPE_Boolean) {
				return DP(stmt)->terms[1];
			}
		}
		if(TERMs_isFALSE(stmt, 2)) { /* b == false */
			if(TERMs_gettype(stmt, 1) == NNTYPE_Boolean) {
				mn = METHODN_opNot;
				mtd_cid = CLASS_Boolean;
				DP(stmt)->size = 2;
				break;
			}
		}
		mtd_cid = knh_StmtOPEQ_basecid(ctx, stmt);
		if(mtd_cid == CLASS_unknown) {
			knh_Asm_perror(ctx, abr, KERR_DWARN, _("comparison of different type: %T %T"), TERMs_gettype(stmt, 1), TERMs_gettype(stmt, 2));
			return new_TermCONST(ctx, FL(optk), KNH_FALSE); /* CONST */
		}
		break;
	}
	case METHODN_opNeq:
	{
		if(!knh_Stmt_checkOPSIZE(ctx, stmt, 2)) {
			return NULL;
		}
		if(TERMs_isNULL(ctx, stmt, 1) || TERMs_isTRUE(stmt, 1) || TERMs_isFALSE(stmt, 1)) {
			Term *temp = DP(stmt)->terms[1];
			DP(stmt)->terms[1] = DP(stmt)->terms[2];
			DP(stmt)->terms[2] = temp;
		}
		if(TERMs_isNULL(ctx, stmt, 2)) { /* o != null */
			if(IS_NNTYPE(TERMs_gettype(stmt,1))) {
				return TM(new_TokenCONST(ctx, FL(stmt), KNH_TRUE));
			}
		mn = METHODN_isNotNull;
		mtd_cid = CLASS_Object;
		DP(stmt)->size = 2;
		break;
		}
		if(TERMs_isTRUE(stmt, 2)) { /* b != true */
			if(TERMs_gettype(stmt, 1) == NNTYPE_Boolean) {
				mn = METHODN_opNot;
				mtd_cid = CLASS_Boolean;
				DP(stmt)->size = 2;
				break;
			}
		}
		if(TERMs_isFALSE(stmt, 2)) { /* b != false */
			if(TERMs_gettype(stmt, 1) == NNTYPE_Boolean) {
				return DP(stmt)->terms[1];
			}
		}
		mtd_cid = knh_StmtOPEQ_basecid(ctx, stmt);
		if(mtd_cid == CLASS_unknown) {
			knh_Asm_perror(ctx, abr, KERR_DWARN, _("comparison of different type: %T %T"), TERMs_gettype(stmt, 1), TERMs_gettype(stmt, 2));
			return new_TermCONST(ctx, FL(optk), KNH_TRUE); /* CONST */
		}
		break;
	}

	case METHODN_opGt: case METHODN_opGte:
	case METHODN_opLt: case METHODN_opLte:
	{
		if(!knh_Stmt_checkOPSIZE(ctx, stmt, 2)) {
			return NULL;
		}
		mtd_cid = knh_StmtOPEQ_basecid(ctx, stmt);
		if(mtd_cid == CLASS_unknown) {
			knh_Asm_perror(ctx, abr, KERR_EWARN, _("comparison of different type: %T %T"), TERMs_gettype(stmt, 1), TERMs_gettype(stmt, 2));
			return NULL;
		}
		break;
	}

	case METHODN_opHas:
	{
		if(!knh_Stmt_checkOPSIZE(ctx, stmt, 2)) {
			return NULL;
		}
		Term *temp = DP(stmt)->terms[1];
		DP(stmt)->terms[1] = DP(stmt)->terms[2];
		DP(stmt)->terms[2] = temp;
		mtd_cid = TERMs_getcid(stmt, 1);
		break;
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
	}
	break;

	default:
		mtd_cid = TERMs_getcid(stmt, 1);
		break;
	}

	KNH_ASM_ASSERT(ctx, abr, mtd_cid != CLASS_unknown);
	Method *mtd = knh_Class_getMethod(ctx, mtd_cid, mn);
	if(IS_NULL(mtd)) {
		knh_Asm_perror(ctx, abr, KERR_ERROR, _("unsupported operator in %C"), mtd_cid);
		return NULL;
	}
	knh_Token_toMTD(ctx, DP(stmt)->tokens[0], mn, mtd);
	if(!TERMs_typing(ctx, stmt, 1, abr, ns, mtd_cid, TCHECK_)) {
		return NULL;
	}
	return knh_StmtPARAMS_typing(ctx, stmt, abr, ns, mtd_cid, mtd);
}

/* ------------------------------------------------------------------------ */
/* [MAPCAST] */

static
void knh_Token_toMPR(Ctx *ctx, Token *tk, knh_class_t cid, Mapper *mpr)
{
	SP(tk)->tt = TT_MPR;
	DP(tk)->cid = cid;
	KNH_SETv(ctx, DP(tk)->data, mpr);
	if(IS_NULL(mpr)) {
		DP(tk)->type = NATYPE_cid(cid);
	}
	else {
		DP(tk)->type = knh_Mapper_isTotal(mpr) ? NNTYPE_cid(DP(mpr)->tcid) : NATYPE_cid(DP(mpr)->tcid);
	}
}

/* ------------------------------------------------------------------------ */

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
	knh_Stmt_setType(ctx, stmt, isNonNullCast ? NNTYPE_cid(mprcid) : NATYPE_cid(mprcid));
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
	knh_Stmt_setType(ctx, stmt, NNTYPE_String);
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
	knh_Stmt_setType(ctx, stmt, NNTYPE_Boolean);
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
	knh_Stmt_setType(ctx, stmt, NNTYPE_Boolean);
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtALT_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	DBG2_ASSERT(DP(stmt)->size > 1);
	size_t i;
	knh_class_t reqc = CLASS_type(reqt);
	for(i = 0; i < DP(stmt)->size; i++) {
		if(!TERMs_typing(ctx, stmt, i, abr, ns, reqc, TCHECK_)) {
			return NULL;
		}
		knh_type_t type = TERMs_gettype(stmt, i);
		if(IS_NNTYPE(type)) {
			DP(stmt)->size = i + 1;
			knh_Stmt_setType(ctx, stmt, NNTYPE_cid(reqc));
			return TM(stmt);
		}
	}
	knh_Stmt_setType(ctx, stmt, reqt);
	return TM(stmt);
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

	if(TERMs_isCONST(stmt, 0)) {
		if(IS_TRUE(TERMs_const(stmt, 0))) {
			return DP(stmt)->terms[1];
		}
		else {
			return DP(stmt)->terms[2];
		}
	}
	knh_type_t type = TERMs_gettype(stmt, 1);
	knh_type_t type2 = TERMs_gettype(stmt, 2);
	if(IS_NNTYPE(type) && IS_NNTYPE(type2)) {
		reqt = NNTYPE_cid(reqt);
	}
	else {
		reqt = NATYPE_cid(reqt);
	}
	knh_Stmt_setType(ctx, stmt, reqt);
	return TM(stmt);
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
		knh_Stmt_setType(ctx, cstmt, reqc);
		return TM(cstmt);
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
		knh_Stmt_setType(ctx, cstmt, DP(tk)->type);
		return TM(cstmt);
	}
}

/* ------------------------------------------------------------------------ */

static
int TERMs_typecheck(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, knh_type_t reqt, int mode)
{
	knh_type_t vart = TERMs_gettype(stmt, n);
	knh_class_t varc = CLASS_type(vart);
	knh_class_t reqc = CLASS_type(reqt);

	if(TERMs_isNULL(ctx, stmt, n)) {
		//DBG2_P("reqc=%s varc=%s", CTXCLASSN(reqc), CTXCLASSN(varc));
		if(IS_NNTYPE(reqt) && varc != reqc) {
			TERMs_perrorTYPE(ctx, stmt, n, reqt);
			return 0;
		}
		return 1;
	}

	if(vart == TYPE_void) {
		TERMs_perrorTYPE(ctx, stmt, n, reqt);
		return 0;
	}

	if(reqt == NNTYPE_Boolean && vart != NNTYPE_Boolean) {
		DBG2_P("stt=%s, vart=%s%s", knh_stmt_tochar(SP(stmt)->stt), TYPEQN(vart));
		TERMs_perrorTYPE(ctx, stmt, n, reqt);
		return 0;
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
			knh_Asm_perror(ctx, abr, KERR_INFO, _("implict casting: %C => %C"), varc, reqc);
		}
	}

	if(mode == TCONV_ || mode == TITERCONV_) {
		Term *mcast = new_TermINCAST(ctx, reqc, stmt, n);
		if(mcast != NULL) {
			KNH_SETv(ctx, DP(stmt)->stmts[n], mcast);
			return 1;
		}
		if(mode == TITERCONV_) return 0;
	}
	DBG_P("stt=%s reqt=%s%s, vart=%s%s", knh_stmt_tochar(SP(stmt)->stt), TYPEQN(reqt), TYPEQN(vart));
	TERMs_perrorTYPE(ctx, stmt, n, reqt);
	return 0;
}

/* ------------------------------------------------------------------------ */

static
int TERMs_typing(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, NameSpace *ns, knh_type_t reqt, int mode)
{
	if(SP(stmt)->stt == STT_ERR) return 0;
	if(reqt == TYPE_var) reqt = TYPE_Any;

	if(IS_Token(DP(stmt)->tokens[n]) && SP(DP(stmt)->tokens[n])->tt == TT_ESTR) {
		KNH_SETv(ctx, DP(stmt)->terms[n], knh_TokenESTR_toTerm(ctx, DP(stmt)->tokens[n], abr));
	}

	if(IS_Token(DP(stmt)->tokens[n])) {
		Token *tk = DP(stmt)->tokens[n];
		if(SP(tk)->tt == TT_ASIS || !knh_Token_isTyped(tk) ) {
			if(!knh_Token_typing(ctx, tk, abr, ns, reqt)) {
				return 0;
			}
		}
	}
	else {
		Stmt *stmt_n = DP(stmt)->stmts[n];
		if(!knh_Stmt_isTyped(stmt_n)) {
			Term *tm = knh_Stmt_typing(ctx, stmt_n, abr, ns, reqt);
			if(tm == NULL) {
				return 0;
			}
			if(tm != DP(stmt)->terms[n]) {
				KNH_SETv(ctx, DP(stmt)->stmts[n], tm);
			}
		}
	}
	if(mode == TWARN_ || reqt == TYPE_Any) return 1;
	return TERMs_typecheck(ctx, stmt, n, abr, reqt, mode);
}

/* ======================================================================== */

static
int TERMs_typingBLOCK(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, NameSpace *ns)
{
	KNH_ASSERT(IS_Stmt(DP(stmt)->terms[n]));
	return knh_Stmt_typingBLOCK(ctx, DP(stmt)->stmts[n], abr, ns, 1);
}

/* ======================================================================== */
/* [IF] */

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

	if(TERMs_isCONST(stmt, 0)) {
		if(IS_TRUE(TERMs_const(stmt, 0))) {
			TERMs_typingBLOCK(ctx, stmt, 1, abr, ns);
			knh_Stmt_done(ctx, DP(stmt)->stmts[2]);
			knh_Stmt_toBLOCK(ctx, stmt, 1);
			return TM(stmt);
		}
		if(IS_FALSE(TERMs_const(stmt, 0))) {
			knh_Stmt_done(ctx, DP(stmt)->stmts[1]);
			TERMs_typingBLOCK(ctx, stmt, 2, abr, ns);
			knh_Stmt_toBLOCK(ctx, stmt, 2);
			return TM(stmt);
		}
	}
	else {
		TERMs_typingBLOCK(ctx, stmt, 1, abr, ns);
		TERMs_typingBLOCK(ctx, stmt, 2, abr, ns);
	}
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtSWITCH_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	knh_Stmt_done(ctx, stmt);
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
		knh_Stmt_done(ctx, stmt);
		return TM(stmt);
	}
	else {
		TERMs_typingBLOCK(ctx, stmt, 1, abr, ns);
	}
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtDO_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	TERMs_typingBLOCK(ctx, stmt, 0, abr, ns);
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
	if(!TERMs_typingBLOCK(ctx, stmt, 0, abr, ns)) return NULL;
	/* i < N */
	if(!TERMs_typing(ctx, stmt, 1, abr, ns, NNTYPE_Boolean, TCHECK_)) return NULL;

	if(TERMs_isFALSE(stmt, 1)) {
		return DP(stmt)->terms[0];
	}
	else {
		/* i++ */
		if(!TERMs_typingBLOCK(ctx, stmt, 2, abr, ns)) return NULL;
		TERMs_typingBLOCK(ctx, stmt, 3, abr, ns);
	}
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */
/* [FOREACH] */

static
knh_fieldn_t knh_tName_local(Ctx *ctx, const char *fmt, int level)
{
	char bufn[40];
	knh_snprintf(bufn, sizeof(bufn), fmt, level);
	knh_bytes_t tname = B(bufn);
	knh_index_t idx = knh_DictIdx_index(ctx, DP(ctx->sys)->FieldNameDictIdx, tname);
	if(idx == -1) {
		String *s = new_String(ctx, tname, NULL);
		idx = knh_DictIdx_add__fast(ctx, DP(ctx->sys)->FieldNameDictIdx, s);
	}
	return (knh_fieldn_t)idx;
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtFOREACH_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	knh_type_t type = TYPE_Any;
	knh_fieldn_t fn = knh_Token_getfnq(ctx, StmtFOREACH_name(stmt));
	knh_class_t itrcid = CLASS_unknown;
	if(TERMs_isASIS(stmt, FOREACH_type)) {  /* foreach(n in itr) */
		knh_index_t idx = knh_Asm_indexOfVariable(abr, fn);
		if(idx == -1) { //DBG2_P("type inferencing..");
			if(!TERMs_typing(ctx, stmt, FOREACH_iter, abr, ns, TYPE_Any, TWARN_)) {
				return NULL;
			}
			if(TERMs_getbcid(stmt, FOREACH_iter) != CLASS_Iterator) {
				Stmt *stmt_call = new_Stmt(ctx, 0, STT_CALL);
				Token *tk = new_TokenMN(ctx, FL(stmt), METHODN_opItr);
				knh_Stmt_add(ctx, stmt_call, UP(tk));
				knh_Stmt_add(ctx, stmt_call, StmtFOREACH_iter(stmt));
				KNH_SETv(ctx, DP(stmt)->stmts[FOREACH_iter], stmt_call);
				if(!TERMs_typing(ctx, stmt, FOREACH_iter, abr, ns, NNTYPE_Iterator, TCHECK_)) {
					return NULL;
				}
			}
			itrcid = TERMs_getcid(stmt, FOREACH_iter);
			type = NNTYPE_cid(ctx->share->ClassTable[itrcid].p1);
			type = knh_Asm_typeinfer(ctx, abr, type, FIELDN(fn));
			knh_Asm_declareLocalVariable(ctx, abr, 0, type, fn, knh_getClassDefaultValue(ctx, CLASS_type(type)));
			if(!TERMs_typing(ctx, stmt, FOREACH_name, abr, ns, type, TCHECK_)) {
				return NULL;
			}
			goto L_BLOCK;
		}
	}
	else { //DBG2_P("defined type .."); /* foreach(String line in itr) */
		type = knh_Token_gettype(ctx, StmtFOREACH_type(stmt), ns, CLASS_Any);
		type = knh_pmztype_totype(ctx, type, DP(abr)->this_cid);
		knh_index_t idx = knh_Asm_indexOfVariable(abr, fn);
		if(idx == -1) { //DBG2_P("defining new type ..");
			knh_Asm_declareLocalVariable(ctx, abr, /*flag*/0, type, fn, KNH_NULL);
		}
	}
	//DBG2_P("type=%s%s", TYPEQN(type));
	if(!TERMs_typing(ctx, stmt, FOREACH_name, abr, ns, type, TWARN_)) {
		return NULL;
	}
	itrcid = knh_class_Iterator(ctx, TERMs_getcid(stmt, FOREACH_name));
	if(!TERMs_typing(ctx, stmt, FOREACH_iter, abr, ns, NNTYPE_cid(itrcid), TITERCONV_)) {
		//DBG2_P("No mapper, using opItr");
		Stmt *stmt_call = new_Stmt(ctx, 0, STT_CALL);
		Token *tk = new_TokenMN(ctx, FL(stmt), METHODN_opItr);
		knh_Stmt_add(ctx, stmt_call, UP(tk));
		knh_Stmt_add(ctx, stmt_call, StmtFOREACH_iter(stmt));
		KNH_SETv(ctx, DP(stmt)->stmts[FOREACH_iter], stmt_call);
		if(!TERMs_typing(ctx, stmt, FOREACH_iter, abr, ns, NNTYPE_Iterator, TCHECK_)) {
			return NULL;
		}
	}

	L_BLOCK:;
	KNH_ASSERT(itrcid != CLASS_unknown);
	{
		int sfpidx = knh_Asm_declareLocalVariable(ctx, abr, 0, TYPE_Any,
				knh_tName_local(ctx, "__S%d__", DP(abr)->level), KNH_NULL);
		//DBG2_P("sfpidx=%d", sfpidx);
		if(sfpidx == -1) return NULL;
		Token *tkitr = new_TokenNULL(ctx, FL(stmt), itrcid);
		knh_Token_toSTACK(ctx, tkitr, sfpidx, itrcid);
		knh_Stmt_add(ctx, stmt, TM(tkitr));

		if(!TERMs_typing(ctx, stmt, FOREACH_where, abr, ns, NNTYPE_Boolean, TCHECK_)) {
			return NULL;
		}
		if(TERMs_isFALSE(stmt, FOREACH_where)) {
			knh_Stmt_done(ctx, stmt);
			return TM(stmt);
		}
		TERMs_typingBLOCK(ctx, stmt, FOREACH_loop, abr, ns);
		return TM(stmt);
	}
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtTRY_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	int sfpidx = knh_Asm_declareLocalVariable(ctx, abr,
			0, TYPE_Any, knh_tName_local(ctx, "__E%d__", DP(abr)->level), KNH_NULL);
	if(sfpidx == -1) {
		return NULL;
	}
	{
		Token *tkHDR = new_TokenNULL(ctx, FL(stmt), CLASS_ExceptionHandler);
		knh_Token_toSTACK(ctx, tkHDR, sfpidx, CLASS_ExceptionHandler);
		knh_Stmt_add(ctx, stmt, TM(tkHDR));
	}

	TERMs_typingBLOCK(ctx, stmt, TRY_try, abr, ns);
	{
		Stmt *stmtCATCH = DP(stmt)->stmts[TRY_catch];
		while(IS_Stmt(stmtCATCH)) {
			if(SP(stmtCATCH)->stt == STT_CATCH) {
				Token *tkV = DP(stmtCATCH)->tokens[1];
				knh_fieldn_t fn = knh_Token_getfnq(ctx, tkV);
				if(fn == FIELDN_NONAME) {
					knh_Token_perror(ctx, tkV, KERR_ERROR, _("invalid variable name: %s"), sToken(tkV));
				}
				else {
					knh_Asm_declareLocalVariable(ctx, abr, 0, TYPE_Exception, fn, KNH_NULL);
					if(!TERMs_typing(ctx, stmtCATCH, 1, abr, ns, TYPE_Exception, TCHECK_)) {
						knh_Stmt_done(ctx, stmtCATCH);
					}
					else {
						TERMs_typingBLOCK(ctx, stmtCATCH, 2, abr, ns);
					}
				}
			}
			stmtCATCH = DP(stmtCATCH)->next;
		}
	}
	TERMs_typingBLOCK(ctx, stmt, TRY_finally, abr, ns);
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
void knh_StmtRETURN_addValue(Ctx *ctx, Stmt *stmt, knh_type_t rtype)
{
	KNH_ASSERT(SP(stmt)->stt == STT_RETURN && DP(stmt)->size == 0);
	if(rtype != TYPE_void) {
		Token *tk = new_TokenNULL(ctx, FL(stmt), rtype);
		if(IS_NNTYPE(rtype)) {
			knh_Token_toDEFVAL(tk, CLASS_type(rtype));
		}
		knh_Stmt_add(ctx, stmt, TM(tk));
	}
}

/* ------------------------------------------------------------------------ */

static
Term *knh_StmtRETURN_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	knh_type_t rtype = DP(abr)->rtype;
	//DBG2_P("this_cid=%s, rtype=%s%s", CTXCLASSN(DP(abr)->this_cid), TYPEQN(rtype));
	if(rtype == TYPE_void) {
		if(DP(stmt)->size > 0) {
			knh_Asm_perror(ctx, abr, KERR_EWARN, _("ignored return value"));
			DP(stmt)->size = 0;
		}
	}
	else if(knh_Method_isConstructor(ctx, DP(abr)->mtd)) {
		if(DP(stmt)->size > 0) {
			knh_Asm_perror(ctx, abr, KERR_EWARN, _("ignored return value"));
			DP(stmt)->size = 1;
		}
		else {
			Token *tk = new_TokenNULL(ctx, FL(stmt), rtype);
			knh_Stmt_add(ctx, stmt, TM(tk));
		}
		knh_Token_toSTACK(ctx, DP(stmt)->tokens[0], 0, rtype);
	}
	else if(DP(stmt)->size == 0) {
		knh_Asm_perror(ctx, abr, KERR_ERRATA, _("added return value"));
		knh_StmtRETURN_addValue(ctx, stmt, rtype);
	}
	else if(!TERMs_typing(ctx, stmt, 0, abr, ns, rtype, TCHECK_)){
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
	if(!TERMs_typing(ctx, stmt, 0, abr, ns, NNTYPE_Boolean, TWARN_)) {
		return NULL;
	}

	if(TERMs_isCONST(stmt, 0)) {
		if(IS_TRUE(TERMs_const(stmt, 0))) {
			knh_Stmt_done(ctx, stmt);
			return TM(stmt);
		}
		if(IS_FALSE(TERMs_const(stmt, 0))) {
			knh_Asm_perror(ctx, abr, KERR_EWARN, _("always throw Assert!!"));
		}
	}
	TERMs_typingBLOCK(ctx, stmt, 1, abr, ns);
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

/* ------------------------------------------------------------------------ */

static
knh_index_t knh_Asm_beginRegister(Ctx *ctx, Asm *abr, Stmt *stmt)
{
	if(DP(abr)->regs_size < KNH_ASM_REGMAX) {
		size_t size = DP(abr)->regs_size;
		DP(abr)->regs[size].level = DP(abr)->level;
		DP(abr)->regs[size].stmt = stmt;
		if(DP(abr)->regs[size].varidx == -1) {
			DP(abr)->regs[size].varidx =
				knh_Asm_addVariableTable(ctx, abr, (knh_cfield_t*)DP(abr)->vars, KONOHA_LOCALSIZE,
						0/* flag */, TYPE_void, FIELDN_register, KNH_NULL);
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

/* ------------------------------------------------------------------------ */

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
Token *new_TokenSTACK(Ctx *ctx, Any *fln, knh_type_t type, int varidx)
{
	knh_Token_t *o = (Token*)new_Object_bcid(ctx, CLASS_Token, 0);
	knh_Token_setFL(o, fln);
	SP(o)->flag = 0;
	SP(o)->tt = TT_STACK;
	DP(o)->index = varidx;
	DP(o)->type = type;
	return o;
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
				Token *tk = new_TokenSTACK(ctx, DP(stmt)->terms[i], type, varidx);
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
		//DBG2_P("*********** data ***********");
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
				return TM(new_TokenSTACK(ctx, TM(stmt), DP(stmt)->type, DP(abr)->regs[i].varidx));
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
	return knh_Token_gettype(ctx, DP(stmt)->tokens[0], ns, CLASS_Any);
}

/* ------------------------------------------------------------------------ */

static
knh_class_t knh_StmtMETHOD_class(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, int level)
{
	Token *tk = DP(stmt)->tokens[1];
	KNH_ASSERT(IS_Token(tk));
	if(SP(tk)->tt == TT_ASIS) {
		if(level == 0) {
			Script *scr = knh_getCurrentScript(ctx);
			return knh_Object_cid(scr);
		}
		else {
			return DP(abr)->this_cid;
		}
	}
	{
		knh_bytes_t name = knh_Token_tobytes(ctx, tk);
		if(SP(tk)->tt == TT_CMETHODN) {
			knh_index_t idx = knh_bytes_rindex(name, '.');
			DBG2_ASSERT(idx != -1);
			name = knh_bytes_first(name, idx);
		}

		knh_class_t cid = knh_NameSpace_getcid(ctx, ns, name);
		if(cid == CLASS_unknown) {
			cid = DP(abr)->this_cid;
			knh_Asm_perror(ctx, abr, KERR_ERRATA, _("unknown class: %B ==> %s"), name, cid);
		}
		else if(level > 0 && cid != DP(abr)->this_cid) {
			cid = DP(abr)->this_cid;
			knh_Asm_perror(ctx, abr, KERR_ERRATA, _("different class: %B ==> %s"), name, cid);
		}
		KNH_ASSERT(cid != CLASS_unknown);
		return cid;
	}
}

/* ------------------------------------------------------------------------ */

static
knh_methodn_t knh_StmtMETHOD_name(Ctx *ctx, Stmt *stmt, Asm *abr, int level)
{
	Token *tk = DP(stmt)->tokens[2];
	KNH_ASSERT(IS_Token(tk));
	if(SP(tk)->tt == TT_ASIS) {
		if(level == 1) {
			return METHODN_new;
		}
		else {
			TODO();
			return METHODN_lambda;
		}
	}
	else {
		return knh_Token_getmn(ctx, tk);
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_Asm_initParamField(Ctx *ctx, Asm *abr, knh_class_t this_cid)
{
	int i;
	for(i = 0; i < KONOHA_LOCALSIZE; i++) {
		DP(abr)->vars[i].flag  = 0;
		DP(abr)->vars[i].type  = TYPE_Any;
		DP(abr)->vars[i].fn    = FIELDN_NONAME;
		KNH_SETv(ctx, DP(abr)->vars[i].value, KNH_NULL);
	}
	DP(abr)->vars[0].flag = 0;
	DP(abr)->vars[0].type = NNTYPE_cid(DP(abr)->this_cid);
	DP(abr)->vars[0].fn   = FIELDN_this;
	DP(abr)->vars_size = 1;
}

/* ------------------------------------------------------------------------ */

#define _KNH_OUTERPARAMS -1
#define _KNH_INNERPARAMS -2

int knh_Stmt_initParams(Ctx *ctx, Stmt *pstmt, Asm *abr, NameSpace *ns, int level)
{
	knh_Asm_initParamField(ctx, abr, DP(abr)->this_cid);
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
	//	size_t i;
	//	for(i = 1; i < DP(abr)->vars_size; i++) {
		//		DBG2_P("[%d] %s%s %s", i, TYPEQN(DP(abr)->vars[i].type), FIELDN(DP(abr)->vars[i].fn));
	//	}
	return 1;
}

/* ------------------------------------------------------------------------ */

static
MethodField *knh_tMethodField_find(Ctx *ctx, Asm *abr, knh_type_t rztype, size_t mfsize)
{
	knh_hcode_t h = rztype;
	size_t i;
	for(i = 1; i < mfsize; i++) {
		knh_type_t vtype = DP(abr)->vars[i].type;
		if(IS_NOTNULL(DP(abr)->vars[i].value)) {
			vtype = CLASS_type(vtype);
		}
		h = knh_mparam_hcode(h, vtype, DP(abr)->vars[i].fn);
	}
	HashMap *hmap = DP(ctx->sys)->MethodFieldHashMap;
	if(IS_NOTNULL(hmap)) {
		KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
		MethodField *mf = (MethodField*)knh_HashMap_get__hcode(ctx, hmap, h);
		KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
		if(IS_MethodField(mf)) {
			if(mf->rtype != rztype || mf->psize + 1 != mfsize) {
				return NULL;
			}
			for(i = 1; i < mfsize; i++) {
				knh_mparam_t p = knh_MethodField_param(mf, i-1);
				knh_type_t vtype = DP(abr)->vars[i].type;
				if(IS_NOTNULL(DP(abr)->vars[i].value)) {
					vtype = CLASS_type(vtype);
				}
				if(vtype != p.type || p.fn != DP(abr)->vars[i].fn) {
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
int knh_Stmt_checkLastReturn(Ctx *ctx, Stmt *stmt, Method *mtd)
{
	Stmt *last_stmt = knh_Stmt_tail(ctx, stmt);
	knh_stmt_t stt = SP(last_stmt)->stt;
	if(stt == STT_RETURN || stt == STT_THROW || stt == STT_ERR) {
		return 1;
	}
	else if(stt == STT_IF) {
		if(knh_Stmt_checkLastReturn(ctx, StmtIF_truecase(last_stmt), NULL) &&
				knh_Stmt_checkLastReturn(ctx, StmtIF_falsecase(last_stmt), NULL)) {
			return 1;
		}
	}
	if(mtd == NULL) return 0;
	/* Generate default return statement */
	Stmt *rstmt = new_Stmt(ctx, 0, STT_RETURN);
	if(knh_Method_isConstructor(ctx, mtd) || knh_Method_rztype(mtd) == TYPE_void) {

	}
	else { /* return default value */
		knh_perror(ctx, SP(last_stmt)->uri, SP(last_stmt)->line, KERR_ERRATA, _("added return value"));
		knh_StmtRETURN_addValue(ctx, rstmt, knh_Method_rtype(ctx, mtd, DP(mtd)->cid));
	}
	KNH_ASSERT(last_stmt != NULL);
	KNH_SETv(ctx, DP(last_stmt)->next, rstmt);
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

Term * knh_StmtMETHOD_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	Method *mtd;

	int level = DP(abr)->level;
	knh_flag_t flag   = knh_StmtMETHOD_flag(ctx, stmt);
	knh_type_t rztype = knh_StmtMETHOD_rtype(ctx, stmt, ns);
	knh_class_t mtd_cid = knh_StmtMETHOD_class(ctx, stmt, abr, ns, level);
	knh_methodn_t mn = knh_StmtMETHOD_name(ctx, stmt, abr, level);

	if(!knh_Stmt_initParams(ctx, StmtMETHOD_params(stmt), abr, ns, KNH_OUTERPARAMS)) {
		return NULL;
	}

	mtd = knh_Class_getMethod(ctx, mtd_cid, mn);

	/* Check the type of Constructor */
	if(knh_methodn_isNew(ctx, mn) &&
			(mtd_cid != CLASS_type(rztype) && mtd_cid != CLASS_This)) {
		knh_Asm_perror(ctx, abr, KERR_ERRATA, _("different constructor class: %C == %C"), CLASS_type(rztype), mtd_cid);
		rztype = mtd_cid;
	}

	/* New method, and constructors are always new */
	if(IS_NULL(mtd) || knh_Method_isPrivate(mtd) || knh_methodn_isNew(ctx, mn)) {
		size_t i, mfsize = DP(abr)->vars_size;
		MethodField *mf = knh_tMethodField_find(ctx, abr, rztype, mfsize);
		if(mf == NULL) {
			size_t psize = mfsize - 1;
			mf = new_MethodField(ctx, rztype, psize);
			for(i = 1; i < mfsize; i++) {
				if(IS_NOTNULL(DP(abr)->vars[i].value)) {
					knh_MethodField_set(mf, i - 1, CLASS_type(DP(abr)->vars[i].type), DP(abr)->vars[i].fn);
				}
				else {
					knh_MethodField_set(mf, i - 1, DP(abr)->vars[i].type, DP(abr)->vars[i].fn);
				}
			}
			knh_addMethodFieldTable(ctx, mf);
		}
		mtd = new_Method(ctx, flag, mtd_cid, mn, NULL);
		KNH_SETv(ctx, DP(mtd)->mf, mf);
		knh_Class_addMethod(ctx, mtd_cid, mtd);
	}
	else {
		size_t i, mfsize = DP(abr)->vars_size;
		MethodField *mf = DP(mtd)->mf;
		//DBG2_P("(mtd)->cid=%s, mtd_cid=%s", CLASSN(DP(mtd)->cid), CLASSN(mtd_cid));
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
			knh_Asm_perror(ctx, abr, KERR_DWARN, _("differnt parameter size: must be %C.%M(%d)"), mtd_cid, mn, mf->psize+1);
			return NULL;
		}

		if(mf->rtype != rztype) {
			knh_Asm_perror(ctx, abr, KERR_DWARN, _("differnt return type: must be %T %C.%M"), mf->rtype, mtd_cid, mn);
			return NULL;
		}

		for(i = 1; i < mfsize; i++) {
			knh_type_t ptype = knh_MethodField_pztype(mf, i - 1);
			knh_type_t vtype = DP(abr)->vars[i].type;
			if(IS_NOTNULL(DP(abr)->vars[i].value)) {
				vtype = CLASS_type(vtype);
			}
			if(ptype != vtype) {
				knh_Asm_perror(ctx, abr, KERR_DWARN, _("differnt type: parameter %d of %C.%M"), i, mtd_cid, mn);
				return NULL;
			}
		}
	}
	{
		//DBG2_(knh_Method__dump(ctx, mtd, KNH_STDOUT, (String*)KNH_NULL););
		knh_Token_setCONST(ctx, StmtMETHOD_method(stmt), UP(mtd));
		if(DP(stmt)->size != 4) {
			knh_Stmt_checkLastReturn(ctx, StmtMETHOD_instmt(stmt), mtd);
		}
	}
	knh_invokeMethodTypingListener(ctx, DP(stmt)->metaDictMap, mtd);
	{
		knh_fmethod func = knh_Asm_loadMethodFunc(ctx, abr, mtd_cid, DP(mtd)->mn, knh_StmtMETA_is(ctx, stmt, STEXT("Naitive")));
		if(func != NULL) {
			knh_Method_syncFunc(mtd, func);
			knh_Stmt_done(ctx, stmt);
		}
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
void knh_Asm_iniClassTableField(Ctx *ctx, Asm *abr, knh_class_t cid)
{
	DP(abr)->flag = 0;
	DP(abr)->this_cid = cid;
	DP(abr)->level = 0;
	knh_intptr_t i;
	DP(abr)->vars_size = 0;
	for(i = 0; i < KONOHA_LOCALSIZE; i++) {
		DP(abr)->vars[i].flag  = 0;
		DP(abr)->vars[i].type  = TYPE_Any;
		DP(abr)->vars[i].fn    = FIELDN_NONAME;
		//		DP(abr)->vars[i].count = 0;
		KNH_SETv(ctx, DP(abr)->vars[i].value, KNH_NULL);
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_Asm_declareClassField(Ctx *ctx, Asm *abr, NameSpace* ns, knh_class_t cid)
{
	knh_ClassTable_t *TC = (knh_ClassTable_t*)(&ClassTable(cid));
	DBG2_ASSERT(IS_ClassStruct(TC->cstruct));
	DBG2_ASSERT((TC->cstruct)->fields == NULL);
	{
		int i, fsize = DP(abr)->vars_size;
		knh_cfield_t *cf = (knh_cfield_t*)KNH_MALLOC(ctx, sizeof(knh_cfield_t) * fsize);
		//DBG2_P("class %s fsize=%d", CLASSN(cid), fsize);
		for(i = 0; i < fsize; i++) {
			cf[i].flag = DP(abr)->vars[i].flag;
			cf[i].type = DP(abr)->vars[i].type;
			cf[i].fn = DP(abr)->vars[i].fn;
			KNH_INITv(cf[i].value, DP(abr)->vars[i].value);
		}
		(TC->cstruct)->fields =cf;
		(TC->cstruct)->fsize = fsize;
		TC->sid = BSIZE_TOSID(fsize);
		if(TC->supcid != CLASS_Object) {
			TC->offset = ctx->share->ClassTable[TC->supcid].bsize;
			//DBG2_P("offset extending 0 -> %d", TC->offset);
		}
		TC->bsize = fsize + TC->offset;
		TC->size = sizeof(Object*) * TC->bsize;

		knh_NameSpace_setcid(ctx, ns, TC->sname, cid);
		DBG2_({
			DBG2_P("HERE IS DEFINED STRUCT (offset=%d)", TC->offset);
			knh_cfield_dump(ctx, cf, 0, fsize, KNH_STDOUT);
		})
	}
}

/* ------------------------------------------------------------------------ */

Term *knh_StmtCLASS_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	knh_class_t prev_cid = DP(abr)->this_cid;
	knh_class_t this_cid = DP(StmtCLASS_class(stmt))->cid;

	knh_Asm_iniClassTableField(ctx, abr, this_cid);

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

	knh_Asm_iniClassTableField(ctx, abr, this_cid);
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
			knh_Asm_perror(ctx, abr, KERR_DWARN, _("don't use %s HERE"), knh_stmt_tochar(SP(instmt)->stt));
		}
		instmt = DP(instmt)->next;
	}
	DP(abr)->this_cid = prev_cid;
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */

static
Term *knh_Stmt_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt)
{
	/* check statement or expr */
	if(reqt == TYPE_void) {  /* Statement */
		switch(SP(stmt)->stt) {
		case STT_BLOCK:
			if(!TERMs_typingBLOCK(ctx, stmt, 0, abr, ns)) {
				return NULL;
			}
			return TM(stmt);
		case STT_DECL:
			return knh_StmtDECL_typing(ctx, stmt, abr, ns);
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
	int level = DP(abr)->level ;
	Stmt *cur = stmt;
	while(IS_Stmt(cur)) {
		DP(abr)->line = SP(cur)->line;
		DP(abr)->level = level + 1;
		Term *tm = knh_Stmt_typing(ctx, cur, abr, ns, TYPE_void);
		if(tm == NULL) {
			knh_Stmt_toERR(ctx, stmt, TM(cur));
			knh_Asm_endRegister(ctx, abr, level + 1);
			DP(abr)->level = level;
			return 0;
		}
		if(!isIteration) break;
		cur = DP(cur)->next;
	}
	knh_Asm_endRegister(ctx, abr, level + 1);
	DP(abr)->level = level;
	return 1;
}

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
