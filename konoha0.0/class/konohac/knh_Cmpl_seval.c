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

#ifdef KONOHA_DEBUGMODE
	#define DEBUG_STMT(ctx, stmt)
	#define DEBUG_STMT0(ctx, stmt) \
		DEBUG("on stack"); \
		knh_Stmt__dump(ctx, stmt, KNH_STDOUT, knh_String_EMPTY()); \
		knh_flush(ctx, KNH_STDOUT); \

#else
	#define DEBUG_STMT(ctx, stmt)
#endif

/* ------------------------------------------------------------------------ */
/* [Term] */

knh_bool_t knh_Term_isStaticValue(Term *b)
{
	if(IS_Stmt(b)) {
		return 0;
	}
	Token *tk = (Token*)b;
	DEBUG_ASSERT(IS_Token(tk));
	return (tk->tt == TT_RAW);
}


/* ------------------------------------------------------------------------ */

Object *knh_Term_value_ifStaticValue(Term *b)
{
	if(knh_Term_isStaticValue(b)) {
		return ((Token*)b)->data;
	}
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

String *knh_Term_getString(Term *b)
{
	if(IS_Token(b)) {
		String *s = ((Token*)b)->data;
		if(STRUCT_IS_String(s)) return s;
	}
	DEBUG("not string");
	return knh_String_EMPTY();
}

/* ------------------------------------------------------------------------ */

knh_type_t knh_Stmt_reqtype(Stmt *stmt, knh_type_t req, knh_index_t n)
{
    DEBUG_ASSERT(IS_Stmt(stmt));

    switch(stmt->stt) {
    case STT_DONE: 
    case STT_NAMESPACE: /* ['namespace', 'NAME'] */
    case STT_UIMPORT: /* ['CURN'] */
    case STT_UVOCAB: /* ['CLASSQN', 'CURN'] */
    case STT_UINT: /* ['CLASSQN', 'CURN'] */
    case STT_UINT64: /* ['CLASSQN', 'CURN'] */
    case STT_UFLOAT: /* ['CLASSQN', 'CURN'] */
    case STT_CLASS: /* ['class', 'CLASSN', 'CLASSN', 'implements', '{'] */
    case STT_IMPLEMENTS: /* ['implements', '+CLASSN'] */
    case STT_METHOD: /* ['TYPEN', 'METHODFN', 'decl', '?{'] */
    case STT_DECL: /* ['TYPEN', 'FIELDN', 'expr'] */
    case STT_IF: /* ['if', 'expr', '{', '{'] */
    case STT_TRY: /* ['try', '{', '__catch', '{'] */
    case STT_CATCH: /* ['catch', 'EXPTN', 'FIELDN', '{'] */
    case STT_DO: /* ['do', '{', 'while', 'exprdeclv+'] */
    case STT_WHILE: /* ['while', 'expr', '{'] */
    case STT_FOR: /* ['for', 'expr', 'expr', 'expr', '{'] */
    case STT_FOREACH: /* ['foreach', 'TYPEN', 'FIELDN', 'from', 'expr', 'where', 'expr', '{'] */
    case STT_CONTINUE: /* ['continue', '?LABEL'] */
    case STT_BREAK: /* ['break', '?LABEL'] */
    case STT_GOTO: /* ['goto', 'LABEL'] */
//		return CLASS_any;
    case STT_THROW: /* ['throw', 'expr'] */
//    	return CLASS_Exception;
    case STT_RETURN: /* ['return', '?expr'] */
    case STT_PRINT: /* ['print', '+expr'] */
    case STT_ASSERT: /* ['assert', 'expr'] */

    case STT_NEW: /* ['NEW', 'CLASSN', '+expr'] */
    case STT_MAP: /* ['CLASSN', 'expr', '?expr'] */
    case STT_LET: /* ['FIELDN', 'expr'] */
    case STT_CALL: /* ['METHODN', '+expr'] */
    case STT_MOVTEXT: /* ['MOVTEXT', 'expr'] */
    case STT_TRINARY: /* ['expr', 'expr', 'expr'] */
    case STT_OP: /* ['OP', 'expr', '+expr'] */
    case STT_ALT: /* ['expr', '+expr'] */
    case STT_AND: /* ['expr', '+expr'] */
    case STT_OR:  /* ['expr', '+expr'] */
    case STT_META: /* ['+META'] */
    case STT_ERR: /* ['ERRasm'] */
    	return CLASS_any;
    }
    return CLASS_any;
}

/* ------------------------------------------------------------------------ */

knh_bool_t
knh_Stmt_terms_seval(Ctx *ctx, Stmt *b, size_t n, knh_class_t reqc, NameSpace *ns)
{
	Term *v = knh_Term_seval(ctx, b->terms[n], reqc, ns);
	DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
	if(b->terms[n] != v) {
		Object *avoid_gc = NULL;
		KNH_INITv(avoid_gc, v);
		KNH_SETv(ctx, b->terms[n], avoid_gc);
		KNH_FINALv(ctx, avoid_gc);
	}
	return knh_Term_isStaticValue(v);
}

/* ------------------------------------------------------------------------ */
/* [type] */

knh_class_t knh_Token_toclass(Ctx *ctx, Token *b, knh_class_t def, NameSpace *ns)
{
	DEBUG_ASSERT(IS_Token(b));
	knh_bytes_t name = knh_Token_tobytes(b);
	knh_class_t cid = knh_NameSpace_getClass(ctx, ns, name);
	if(cid == CLASS_unknown) {
		cid = def;
		MC_EPRINT(ctx, b, MC_ERRATA, "unknown class: %s ==> %s", name.buf, CLASSN(cid));
	}
	return cid;		
}

/* ------------------------------------------------------------------------ */

knh_type_t knh_Token_totype(Ctx *ctx, Token *b, knh_class_t def, NameSpace *ns)
{
	DEBUG_ASSERT(IS_Token(b));
	knh_bytes_t name = knh_Token_tobytes(b);
	knh_type_t type;
	if(ISB(name, "void")) {
		type = TYPE_void;
	}
	else if(ISB(name, "_")) {  /* AS_IS */
		type = TYPE_any;
	}
	else {
		type = knh_NameSpace_getClass(ctx, ns, name);
	}

	int error = 0;
	if(type ==CLASS_unknown) {
		type = def; error = 1;
	}

	if(knh_Token_isIteratorType(b)) {
		type = (type == CLASS_any) ? CLASS_Iterator : CLASS_TOPLURAL(type);
	}
	else if(!knh_Token_isNotNullType(b)) {
		type = CLASS_TONULLABLE(type);
	}

	if(knh_Token_isArrayType(b)) {
		type = knh_type_toarray(ctx, type);
	}
	
	if(error) {
		MC_EPRINT(ctx, b, MC_ERRATA, "unknown type: %s ==> %s%s", name.buf, TYPEQN(type));
	}

	return type;
}

/* ------------------------------------------------------------------------ */
/* [fieldn] */

knh_fieldn_t knh_Token_tofieldn(Ctx *ctx, Token *b)
{
	DEBUG_ASSERT(IS_Token(b));
	knh_bytes_t name = knh_Token_tobytes(b);
	knh_fieldn_t mask = 0;
	if(name.buf[0] == '_') {
		mask = KNH_FLAG_FN_U1;
		name = knh_bytes_last(name, 1);
	}
	if(name.buf[0] == '_') {
		mask = KNH_FLAG_FN_U2;
		name = knh_bytes_last(name, 1);
	}
	knh_fieldn_t fn = knh_tfieldn_forname(ctx, name, FIELDN_NEWID);
	return fn | mask;
}

/* ------------------------------------------------------------------------ */

knh_fieldn_t knh_Token_tomethodn(Ctx *ctx, Token *b)
{
	DEBUG_ASSERT(IS_Token(b));
	knh_bytes_t name = knh_Token_tobytes(b);
	knh_index_t idx = knh_bytes_rindex(name, '.');
	if(idx != -1) {
		name = knh_bytes_last(name, idx+1);
	}
	knh_methodn_t mn = knh_tmethodn_forname(ctx, name, METHODN_NEWID);
//	if(KNH_FLAG_IS(stmtflag, KNH_FLAG_STMTF_TOGET)) {
//		return mn | KNH_FLAG_MN_GETTER;
//	}
//	if(KNH_FLAG_IS(stmtflag, KNH_FLAG_STMTF_TOSET)) {
//		return mn | KNH_FLAG_MN_SETTER;
//	}
	return mn;
}

/* ------------------------------------------------------------------------ */
/* [Token] */

Token *
knh_Token_seval(Ctx *ctx, Token *b, knh_class_t reqc, NameSpace *ns)
{
#ifdef KONOHA_DEBUGMODE
	if(TYPE_ISNULLABLE(reqc)) {
		DEBUG("check reqc=%s%s", TYPEQN(reqc));
		reqc = TYPE_TONOTNULL(reqc);
	}
#endif

	switch(b->tt) {

	case TT_NAME:
		knh_Token_toRAW__Method(ctx, b, ns);
		return b;

	case TT_TYPEN: 
		knh_Token_toRAW__Class(ctx, b, ns);
		return b;

	case TT_NUM:
		knh_Token_toNumberData(ctx, b, reqc, ns);
		return b;

	case TT_URN: 
		DEBUG_ASSERT(IS_String(b->data));
		b->tt = TT_RAW;
		return b;

	case TT_STR:
		DEBUG_ASSERT(IS_String(b->data));
		b->tt = TT_RAW;
		return b;

	case TT_CONSTN: 
		knh_Token_toConstData(ctx, b, ns);
		return b;

	case TT_QSTR:
		knh_Token_toStringData(ctx, b, reqc, ns);
		return b;
	case TT_RAW: 
		return b;
	}
	return b;
}

/* ------------------------------------------------------------------------ */

void knh_Token_toRAW__Class(Ctx *ctx, Token *b, NameSpace *ns)
{
	knh_Token_setRAW(ctx, b, new_Class__type(ctx, knh_Token_totype(ctx, b, CLASS_any, ns)));
}

/* ------------------------------------------------------------------------ */

void knh_Token_toRAW__Method(Ctx *ctx, Token *b, NameSpace *ns)
{
	knh_bytes_t t = knh_Token_tobytes(b);
	knh_index_t idx = knh_bytes_index(t, '.');
	if(idx == -1) {
		return;
	}
	knh_bytes_t cname = knh_bytes_first(t, idx);
	knh_class_t cid = knh_NameSpace_getClass(ctx, ns, cname);
	if(cid == CLASS_unknown) {
		MC_EPRINT(ctx, b, MC_ERROR, "unknown class: %B", cname);
		knh_Token_setRAW(ctx, b, KNH_NULL);
		return;
	}
	t = knh_bytes_last(t, idx+1);
	knh_methodn_t mn = knh_tmethodn_forname(ctx, t, METHODN_NONAME);
	if(mn == METHODN_NONAME) {
		MC_EPRINT(ctx, b, MC_ERROR, "unknown method name: %B", t);
		knh_Token_setRAW(ctx, b, KNH_NULL);
		return;
	}
	Method *mtd = knh_Class_getMethod(ctx, cid, mn);
	if(IS_NULL(mtd)) {
		MC_EPRINT(ctx, b, MC_ERROR, "undefined method: %s", knh_Token_tochar(b));
		knh_Token_setRAW(ctx, b, KNH_NULL);
		return;
	}
	knh_Token_setRAW(ctx, b, mtd);
}

/* ------------------------------------------------------------------------ */

void knh_Token_toNumberData(Ctx *ctx, Token *b, knh_class_t reqc, NameSpace *ns)
{
	knh_bytes_t t = knh_Token_tobytes(b);

	if(t.buf[0] == '0' && (t.buf[1] == 'x' || t.buf[1] == 'b')) {
		knh_Token_setRAW(ctx, b, new_Int__checked(ctx, knh_tclass_ensurebcid(CLASS_Int, reqc), knh_bytes_toint(t)));
	}
	
	// 1ns    => Int
	// 1Lns   => Long
	// 1.0ns  => Float
	// 1.0Lns => Decimal
	
	knh_class_t guess_cid = CLASS_Int;
	knh_int_t i;
	for(i = 1; i < t.len; i++) {
		if(t.buf[i] == '_') continue;   /* 1_000_000 */
		if(t.buf[i] == '.') {
			if(guess_cid == CLASS_Float) {
				MC_EPRINT(ctx, b, MC_WARNING, "invalid float format: %s", knh_Token_tochar(b));
			}
			if(guess_cid == CLASS_Int) guess_cid = CLASS_Float;
			continue;
		}
		if(t.buf[i] == 'L') {
#ifdef CLASS_Long
			if(guess_cid == CLASS_Int) guess_cid = CLASS_Int64;
#endif
#ifdef CLASS_Decimal
			if(guess_cid == CLASS_Float) guess_cid = CLASS_Decimal;
#endif
			i++; break;
		}
		if(!isdigit(t.buf[i])) break;
	}

	if(i < t.len) {   /* tag exists */
		knh_bytes_t tag = knh_bytes_last(t, i);
		knh_class_t tagcid = knh_NameSpace_tagcid(ctx, ns, guess_cid, tag);
		if(tagcid == CLASS_unknown) {
			MC_EPRINT(ctx, b, MC_ERRATA, "unknown tag: %s ==> %s%s", tag.buf, TYPEQN(guess_cid));
			tagcid = guess_cid;
		}
		knh_Token_setRAW(ctx, b, new_Number__b(ctx, tagcid, t));
		return;
	}

	if(CLASS_ISNUMBER(reqc)) {
//		DEBUG("requested reqc=%s", CLASSN(reqc));
		knh_Token_setRAW(ctx, b, new_Number__b(ctx, reqc, t));
		return;
	}

//	DEBUG("guess_cid=%s", CLASSN(guess_cid));
	knh_Token_setRAW(ctx, b, new_Number__b(ctx, guess_cid, t));
}

/* ------------------------------------------------------------------------ */

void knh_Token_toStringData(Ctx *ctx, Token *b, knh_class_t reqc, NameSpace *ns)
{
//	knh_bytes_t t = knh_Token_tobytes(b);
//	knh_class_t cid = knh_tclass_safebcid(CLASS_String, reqc);
//	
//	knh_index_t loc = knh_bytes_index(t, ':');
//	if(loc <= 0) {
//		if(knh_bytes_hasBackQuoted(t)) {
//			knh_Token_setRAW(ctx, b, new_String__parser(ctx, cid, SPF_BACKQUOTED, t));
//		}
//		else {
//			DEBUG_ASSERT(IS_String(b->data));
//			if(cid == CLASS_String) {
//				knh_Token_toRAW(b);
//			}
//			else {
//				knh_Token_setRAW(ctx, b, new_String__sub(ctx, cid, b->data));
//			}
//		}
//		return;
//	}
//
//	knh_bytes_t tag = knh_bytes_first(t, loc);
//	knh_class_t tagcid = knh_NameSpace_tagcid(ctx, ns, CLASS_String, tag);
//	if(tagcid == CLASS_unknown) {
//		TODO();
//		MC_EPRINT(ctx, b, MC_ERRATA, "unknown tag: %s ==> String", tag.buf);
//		
//	}
//	t = knh_bytes_last(t, loc+1);
//	knh_Token_setRAW(ctx, b, new_String__parser(ctx, tagcid, SPF_BACKQUOTED, t));
}


/* ------------------------------------------------------------------------ */
/* [substitute] */

Object *knh_Token_substitute_const(Ctx *ctx, Token *b)
{
	knh_bytes_t t = knh_Token_tobytes(b);
	KNH_NOTICE(ctx, b, "undefined const '%s'; substitute null for this", t.buf);
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

knh_class_t knh_Token_substitute_tagcid(Ctx *ctx, Token *b, knh_bytes_t tag, knh_class_t tagcid)
{
	KNH_NOTICE(ctx, b, "unknown tag '%s'; substitute %s for this", tag.buf, CLASSN(tagcid));
	return tagcid;
}

/* ------------------------------------------------------------------------ */

void knh_Token_toConstData(Ctx *ctx, Token *b, NameSpace *ns)
{
	knh_bytes_t t = knh_Token_tobytes(b);
	knh_index_t loc = knh_bytes_rindex(t, '.');
	DEBUG_ASSERT(loc != -1);
	knh_class_t cid = knh_NameSpace_getClass(ctx, ns, knh_bytes_first(t, loc));
	Object *value;
	if(cid == CLASS_unknown) {
		value = knh_Token_substitute_const(ctx, b);
	}
	else {
		char buf[CLASSNAME_BUFSIZ];
		knh_snprintf(buf, sizeof(buf), "%s.%s", CLASSN(cid), &t.buf[loc+1]);
		t = B(buf);
		if(knh_tconst_exists(ctx, t)) {
			value = knh_tconst_value(ctx, t);
		}else{
			value = knh_Token_substitute_const(ctx, b);
		}
	}
	knh_Token_setRAW(ctx, b, value);
}



/* ------------------------------------------------------------------------ */
/* [Stmt] */

Term *knh_Stmt_seval__new(Ctx *ctx, Stmt *b, knh_class_t req)
{
	/* THIS FUNCTION SHOULD BE CALLED BY knh_Term_seval() */
	/* ['NEW', 'CLASSN', '+expr'] */
	DEBUG_ASSERT(IS_Stmt(b));
	DEBUG_STMT(ctx, b);
	
	return b;
}

/* ------------------------------------------------------------------------ */

Term *knh_Stmt_seval__map(Ctx *ctx, Stmt *b, knh_class_t req)
{
	/* THIS FUNCTION SHOULD BE CALLED BY knh_Term_seval() */
	/* ['CLASSN', 'expr', '?expr'] */
	DEBUG_STMT(ctx, b);
	return b;
}

/* ------------------------------------------------------------------------ */

Term *knh_Stmt_seval__call(Ctx *ctx, Stmt *b, knh_class_t req)
{
	/* THIS FUNCTION SHOULD BE CALLED BY knh_Term_seval() */
	/* ['METHODN', '+expr'] */
	DEBUG_STMT(ctx, b);
	return b;
}
/* ------------------------------------------------------------------------ */

Term *knh_Stmt_seval__movtext(Ctx *ctx, Stmt *b, knh_class_t req)
{
	/* THIS FUNCTION SHOULD BE CALLED BY knh_Term_seval() */
	/* ['MOVTEXT', 'expr'] */
	DEBUG_STMT(ctx, b);
	return b;
}

/* ------------------------------------------------------------------------ */

Term *knh_Stmt_seval__op(Ctx *ctx, Stmt *b, knh_class_t req)
{
	/* THIS FUNCTION SHOULD BE CALLED BY knh_Term_seval() */
	/* ['OP', 'expr', '+expr'] */
	DEBUG_STMT(ctx, b);
	return b;
}

/* ------------------------------------------------------------------------ */

Term *knh_Stmt_seval__alt(Ctx *ctx, Stmt *b, knh_class_t req)
{
	/* THIS FUNCTION SHOULD BE CALLED BY knh_Term_seval() */
	/* ['expr', '+expr'] */
	DEBUG_STMT(ctx, b);
	return b;
}

/* ------------------------------------------------------------------------ */

Term *knh_Stmt_seval__and(Ctx *ctx, Stmt *b, knh_class_t req)
{
	/* THIS FUNCTION SHOULD BE CALLED BY knh_Term_seval() */
	/* ['expr', 'expr', '+expr'] */
	DEBUG_STMT(ctx, b);
	return b;
}

/* ------------------------------------------------------------------------ */

Term *knh_Stmt_seval__or(Ctx *ctx, Stmt *b, knh_class_t req)
{
	/* THIS FUNCTION SHOULD BE CALLED BY knh_Term_seval() */
	/* ['expr', 'expr', '+expr'] */
	DEBUG_STMT(ctx, b);
	return b;
}

/* ------------------------------------------------------------------------ */

Term *knh_Stmt_seval__next(Ctx *ctx, Stmt *b, knh_class_t req)
{
	/* THIS FUNCTION SHOULD BE CALLED BY knh_Term_seval() */
	/* ['expr', 'expr', '+expr'] */
	DEBUG_STMT(ctx, b);
	return b;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
