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

#include"commons.h"

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus 
extern "C" {
#endif

/* ------------------------------------------------------------------------ */

INLINE
knh_asmv_t 
new_asmv(knh_uchar_t potype, knh_uchar_t idx, knh_type_t type, Object *value)
{
	knh_asmv_t v = {potype, idx, type, value};
	return v;
}

#define _new_asmv__EBP(n,type)     new_asmv(KNH_ASMV_EBP, n, type, NULL)
#define _new_asmv__SFP(n,type)     new_asmv(KNH_ASMV_SFP, n, type, NULL)
#define _new_asmv__OFP(n,type)     new_asmv(KNH_ASMV_OFP, n, type, NULL)
#define _new_asmv__OIDX(o,n,type)  new_asmv(KNH_ASMV_OIDX, n, type, o)
#define _new_asmv__ONSTACK(type)   new_asmv(KNH_ASMV_ONSTACK, 0, type, NULL)

/* ------------------------------------------------------------------------ */

knh_asmv_t
new_asmv__OBJ(Object *v)
{
	return new_asmv(KNH_ASMV_OBJ, 0, knh_Object_cid(v), v);	
}

/* ------------------------------------------------------------------------ */

knh_asmv_t
new_asmv__StaticValue(Ctx *ctx, Token *tk, knh_type_t req)
{
	knh_class_t cid = knh_Object_cid(tk->data);
//	if(cid != TYPE_TONOTNULL(req)) {
//		TODO();
//		DEBUG("need map from cid=%s, req=%s%s", CLASSN(cid), TYPEQN(req));
//	}
	return new_asmv(KNH_ASMV_OBJ, 0, cid, tk->data);	
}

/* ------------------------------------------------------------------------ */

knh_asmv_t
new_asmv__noname(Ctx *ctx, Token *tk, knh_type_t req)
{
	MC_EPRINT(ctx, tk, MC_WARNING, "unknown variable '%s'", knh_Token_tochar(tk));
	if(TYPE_ISNULLABLE(req)) {
		return new_asmv__OBJ(KNH_NULL);
	}
	Object *v = knh_tclass_value(ctx, TYPE_TONOTNULL(req), KNH_NULL);
	return new_asmv__OBJ(v);
}

/* ------------------------------------------------------------------------ */

knh_bool_t
knh_Token_isSystemVariable(Token *tk)
{
	knh_bytes_t t = knh_Token_tobytes(tk);
	return (t.len - 1 > 0 && t.buf[t.len-1] == '_' && t.buf[t.len-2] == '_');
}

/* ------------------------------------------------------------------------ */

knh_asmv_t
new_asmv__name(Ctx *ctx, Cmpl *b, Token *tk, knh_type_t req, knh_bool_t isfirst)
{
	if(knh_Token_isSystemVariable(tk)) {
		knh_bytes_t t = knh_Token_tobytes(tk);
		if(knh_bytes_equals(t, STEXT("__"))) {
			return new_asmv__OBJ(b->nsproto);
		}
		else if(knh_bytes_equals(t, STEXT("__line__"))) {
			return new_asmv__OBJ(new_Int(ctx, tk->line));
		}
		else if(knh_bytes_equals(t, STEXT("__file__"))) {
			return new_asmv__OBJ(knh_tfilen_name(tk->filen));
		}
		else if(knh_bytes_equals(t, STEXT("__method__")) || 
			knh_bytes_equals(t, STEXT("__func__"))) {
			return new_asmv__OBJ(knh_Method_getURN(ctx, b->method));
		}
		else if(knh_bytes_equals(t, STEXT("__namespace__"))) {
			return new_asmv__OBJ(knh_tnsn_name(b->nsn));
		}
		DEBUG("unknown system variable=%s", t.buf);
	}
	
	knh_fieldn_t fnq = knh_Token_tofieldn(ctx, tk);

	if(FIELDN_IS_U2(fnq)) {
		goto L_GLOBAL;
	}

	if(FIELDN_IS_U1(fnq)) {
		goto L_FIELD;
	}
	
	knh_index_t idx = knh_Cmpl_indexOfVariable(b, FIELDN_UNMASK(fnq));
	if(idx != -1) {
		//DEBUG("local variable");
		knh_cfield_t *cf = knh_Cmpl_cfieldOfVariable(b, idx);
		return new_asmv__SFP(idx, cf->type);
	}
	
	L_FIELD:;
	idx = knh_Class_queryField(b->this_cid, fnq);
	if(idx != -1) {
		//DEBUG("field variable");
		knh_cfield_t *cf = knh_Class_fieldAt(b->this_cid, idx);
		return new_asmv__OFP(idx, cf->type);
	}
	
	L_GLOBAL:;
	idx = knh_Class_queryField(knh_Object_cid(b->nsproto), fnq);
	if(idx != -1) {
		//DEBUG("global variable");
		knh_cfield_t *cf = knh_Class_fieldAt(knh_Object_cid(b->nsproto), idx);
		return new_asmv__OIDX(b->nsproto, idx, cf->type);
	}
	return new_asmv__noname(ctx, tk, req);
}


/* ------------------------------------------------------------------------ */
/* [ASM_CALL] */

void 
KNH_ASM_PUSH__mn(Ctx *ctx, Cmpl *b, knh_methodn_t mn, knh_bool_t isfirst)
{
	if(isfirst) {
		KNH_ASM_PUTI(ctx, b, mn);
	}
	else {
		KNH_ASM_PUSH__MN(ctx, b, mn);
	}	
}


/* ------------------------------------------------------------------------ */

void 
KNH_ASM_PUSH__asmv(Ctx *ctx, Cmpl *b, knh_asmv_t v, knh_bool_t isfirst)
{
	if(v.potype == KNH_ASMV_ONSTACK) {
		DEBUG_ASSERT(v.index == 0);
		return;
	}
	if(isfirst) {
		KNH_ASM_MOVE(ctx, b, 0, v);
	}
	else {
		KNH_ASM_PUSH(ctx, b, v);
	}
}

/* ------------------------------------------------------------------------ */

knh_asmv_t
KNH_ASM_TYPECHECK__asmv(Ctx *ctx, Cmpl *b, Token *tke, int at, knh_type_t type, knh_asmv_t v, knh_bool_t isautomap)
{
	if(type == v.type || type == TYPE_any 
		|| (v.type == CLASS_Nue && TYPE_ISNULLABLE(type))) {
		return v;
	}
	
	knh_class_t scid = TYPE_TONOTNULL(v.type);
	knh_class_t tcid = TYPE_TONOTNULL(type);
	if(scid == tcid || knh_class_instanceof(scid, tcid)) {
		if(TYPE_ISNOTNULL(type) && TYPE_ISNULLABLE(v.type)) {
			KNH_ASM_NULLCHK(ctx, b, v);
		}
		return v;
	}

	if(scid == CLASS_any) {
		goto L_DYMAP;
	}

	if(!isautomap) {
		if(at > 1) {
			MC_EPRINT(ctx, tke, MC_TYPE, "%s(%d): incompatible type: %s%s := %s%s", 
				knh_Token_tochar(tke), at, TYPEQN(type), TYPEQN(v.type));
		}
		else {
			MC_EPRINT(ctx, tke, MC_TYPE, "%s: incompatible type: %s%s := %s%s", 
				knh_Token_tochar(tke), TYPEQN(type), TYPEQN(v.type));
		}		
		KNH_ASM_TYPECHK(ctx, b, type, v);
		return v;
	}	
	
	MapMap *map = knh_tmapmap_find(ctx, scid, tcid);
	if(knh_MapMap_isNoSuchMapping(map)) {
		MC_EPRINT(ctx, tke, MC_INFO, "there is no mapping: %s%s --> %s%s", CLASSQN(scid), CLASSQN(tcid));
		KNH_SAFEFREE(ctx, map);
	}
	
	L_DYMAP:;
	KNH_ASM_PUSH__asmv(ctx, b, v, MC_FIRST);
	if(TYPE_ISNULLABLE(type)) {
		KNH_ASM_MAP(ctx, b, tcid);
	}
	else {
		KNH_ASM_MAPE(ctx, b, tcid);
	}
	return new_asmv__ONSTACK(type);
}


/* ------------------------------------------------------------------------ */

int
KNH_ASM_PUSH_PARAMS(Ctx *ctx, Cmpl *b, Token *tke, Stmt *stmt, knh_type_t this_type, Method *mtd, knh_bool_t isautomap)
{
	int c = 1;
	NameSpace *ns = knh_Cmpl_getNameSpace(ctx, b);
	
	if(!IS_Method(mtd)) {
		if(TYPE_TONOTNULL(this_type) != CLASS_any) {
			MC_EPRINT(ctx, tke, MC_TYPE, "no such method %s", knh_Token_tochar(tke));
		}
		goto L_DYNAMIC;
	}

	DEBUG_ASSERT(IS_Method(mtd));

	knh_asmv_t asmv;
	knh_type_t reqt;
	
	int i;
	for(i = 0; i < knh_Method_psize(mtd); i++) {
		reqt = knh_Method_ptype(mtd, i);
		if(i + 2 < stmt->size) {
			knh_Stmt_terms_seval(ctx, stmt, i + 2, TYPE_TONOTNULL(reqt), ns);
			asmv = knh_Cmpl_asmv(ctx, b, stmt->terms[i + 2], reqt, 0);
		}
		else {
			if(TYPE_ISNOTNULL(reqt)) {
				knh_Cmpl_setTypeError(b, 1);
				MC_EPRINT(ctx, tke, MC_TYPE, "Too few parameters: %s", knh_Token_tochar(tke));
			}
			asmv = new_asmv__OBJ(KNH_NULL);
		}
		KNH_ASM_PUSH__asmv(ctx, b, asmv, 0); c++;
		KNH_ASM_TYPECHECK__asmv(ctx, b, tke, i + 1, reqt, new_asmv__ONSTACK(asmv.type), isautomap);
	}
	if(knh_Method_isVarArgs(mtd)) {
		reqt = knh_Method_ptype(mtd, knh_Method_psize(mtd) - 1);
		for(i = knh_Method_psize(mtd); i + 2 < stmt->size; i++) {
			knh_Stmt_terms_seval(ctx, stmt, i + 2, TYPE_TONOTNULL(reqt), ns);
			asmv = knh_Cmpl_asmv(ctx, b, stmt->terms[i + 2], reqt, 0);
			KNH_ASM_PUSH__asmv(ctx, b, asmv, 0); c++;
			KNH_ASM_TYPECHECK__asmv(ctx, b, tke, i + 1, reqt, new_asmv__ONSTACK(asmv.type), isautomap);
		}
	}
	if(i + 2 == stmt->size) {
		//DEBUG("good");
	}
	else {
		MC_EPRINT(ctx, tke, MC_IGNORED, "some parameter(s): %s(%d)", knh_Token_tochar(tke), i+1);
	}
	return c;
	
	L_DYNAMIC:; /***********************************************************/

	for(i = 0; i + 2 < stmt->size; i++) {
		knh_Stmt_terms_seval(ctx, stmt, i+2, CLASS_any, knh_Cmpl_getNameSpace(ctx, b));
		asmv = knh_Cmpl_asmv(ctx, b, stmt->terms[i + 2], CLASS_any, 0);
		KNH_ASM_PUSH__asmv(ctx, b, asmv, 0); c++;
	}
	return c;
}

/* ------------------------------------------------------------------------ */

void
KNH_ASM_CALL_METHOD(Ctx *ctx, Cmpl *b, Method *mtd, knh_type_t this_type, int c)
{
	if(knh_Method_isFinal(mtd)) {
		if(TYPE_ISNULLABLE(this_type)) {
			KNH_ASM_NCALL_WM(ctx, b, c, mtd);
		}
		else {
			KNH_ASM_CALL_WM(ctx, b, c, mtd);
		}
	}
	else {
		KNH_ASM_CALL(ctx, b, c);
	}
}

/* ------------------------------------------------------------------------ */

void
KNH_ASM_DCALL_METHOD(Ctx *ctx, Cmpl *b, knh_bool_t isautomap, int c)
{
	if(isautomap) {
		KNH_ASM_MCALL(ctx, b, c);
	}
	else {
		KNH_ASM_DCALL(ctx, b, c);
	}
}

/* ------------------------------------------------------------------------ */

knh_asmv_t
knh_Cmpl_asmv__call(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst)
{
	DEBUG_ASSERT(IS_Token(stmt->terms[0]));
	Token *tke = (Token*)stmt->terms[0];

	if(stmt->size == 1) {
		knh_Stmt_setVisible(stmt, 1);
		knh_Stmt_terms_seval(ctx, stmt, 0, CLASS_any, knh_Cmpl_getNameSpace(ctx, b));
		knh_asmv_t asmv = knh_Cmpl_asmv(ctx, b, stmt->terms[0], req, isfirst);
		KNH_ASM_PUSH__asmv(ctx, b, asmv, isfirst);
		return new_asmv__ONSTACK(asmv.type);
	}
	
	knh_methodn_t mn = knh_Token_tomethodn(ctx, tke);
	KNH_ASM_PUSH__mn(ctx, b, mn, isfirst);
	knh_bool_t isautomap = knh_Token_isTailC(tke);
	
	Token *tk_ = (Token*)stmt->terms[1]; 
	if(IS_Token(tk_) && tk_->tt == TT_ASIS) {
		DEBUG("find function.. %s", knh_Token_tochar(tke));
		DEBUG("fn=%d, size=%d", b->vars[0].fn, b->vars_size);
		DEBUG_ASSERT(b->vars[0].fn == FIELDN_this);
		knh_class_t _cid = TYPE_TONOTNULL(b->vars[0].type);
		Method *_mtd = knh_Class_getMethod(ctx, _cid, mn);
		if(IS_NOTNULL(_mtd)) {
			KNH_SETv(ctx, stmt->terms[1], new_Token__text(ctx, tk_, STEXT("this")));
			goto L_SELF;
		}
		if(_cid != knh_Object_cid(b->nsproto)) {
			_cid = knh_Object_cid(b->nsproto);
			_mtd = knh_Class_getMethod(ctx, _cid, mn);
			if(IS_NOTNULL(_mtd)) {
				KNH_SETv(ctx, stmt->terms[1], new_Token__text(ctx, tk_, STEXT("__")));
				goto L_SELF;
			}
		}
		Class *c_ = knh_NameSpace_getFuncClass(ctx, knh_Cmpl_getNameSpace(ctx, b), knh_Token_tobytes(tke));
		if(IS_NOTNULL(c_)) {
			knh_Token_setRAW(ctx, tk_, c_);
		}
		else {
			KNH_SETv(ctx, stmt->terms[1], new_Token__text(ctx, tk_, STEXT("this")));
		}
	}
	
	L_SELF:;	
	knh_Stmt_terms_seval(ctx, stmt, 1, CLASS_any, knh_Cmpl_getNameSpace(ctx, b));
	knh_asmv_t self = knh_Cmpl_asmv(ctx, b, stmt->terms[1], TYPE_any, 0);
	if(self.potype == KNH_ASMV_OBJ && IS_Class(self.value)) {
		KNH_ASM_PUSH__DEF(ctx, b, knh_Class_cid(self.value));
		self.type = knh_Class_cid(self.value);
	} else {
		KNH_ASM_PUSH__asmv(ctx, b, self, 0); 
	}

	/* CHECK_PARAMS */
	Method *mtd = NULL;
	if(self.type == CLASS_any || self.type == TYPE_any) {
		mtd = KNH_NULL;
	}
	else {
		mtd = knh_Class_getMethod(ctx, knh_type_toclass(self.type), mn);
	}
	int c = KNH_ASM_PUSH_PARAMS(ctx, b, tke, stmt, self.type, mtd, isautomap);

	if(IS_Method(mtd) && !knh_Method_isNoSuchMethod(mtd)) {
		if(knh_Method_rtype(mtd) != TYPE_void) {
			knh_Stmt_setVisible(stmt, 1);
		}
		KNH_ASM_CALL_METHOD(ctx, b, mtd, self.type, c);
		return new_asmv__ONSTACK(knh_Method_rtype(mtd));
	}
	else {
		DEBUG("dynamic call");
		if(METHODN_IS_GETTER(mn)) {
			knh_Stmt_setVisible(stmt, 1);
		}
		KNH_ASM_DCALL_METHOD(ctx, b, isautomap, c);
		return new_asmv__ONSTACK(TYPE_any);
	}
}

/* ------------------------------------------------------------------------ */

knh_bool_t
knh_methodop_isAssociative(knh_methodn_t mn)
{
	switch(mn) {
	case METHODN_opAdd:
	case METHODN_opSub:
	case METHODN_opMul:
	case METHODN_opDiv:
	case METHODN_opLogicalAnd:
	case METHODN_opLogicalOr:
		return 1;
	}
	return 0;
}


/* ------------------------------------------------------------------------ */

knh_asmv_t
knh_Cmpl_asmv__op(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst)
{
	DEBUG_ASSERT(stmt->size > 1);
	DEBUG_ASSERT(IS_Token(stmt->terms[0]));
	Token *tke = (Token*)stmt->terms[0];
	knh_Stmt_setVisible(stmt, 1);

	knh_methodn_t mn = knh_token_tomethodn(tke->tt);
	if(mn == METHODN_NONAME) {
		MC_EPRINT(ctx, tke, MC_LANG, "unsupported operator: %s", knh_Token_tochar(tke));
	}
	
	if(stmt->size > 3 && knh_methodop_isAssociative(mn)) {
		TODO();
	}
	
	KNH_ASM_PUSH__mn(ctx, b, mn, isfirst);
	
	knh_Stmt_terms_seval(ctx, stmt, 1, CLASS_any, knh_Cmpl_getNameSpace(ctx, b));
	knh_asmv_t self = knh_Cmpl_asmv(ctx, b, stmt->terms[1], TYPE_any, 0);
	KNH_ASM_PUSH__asmv(ctx, b, self, 0 /* not-first*/); 

	/* CHECK_PARAMS */
	Method *mtd = knh_Class_getMethod(ctx, knh_type_toclass(self.type), mn);
	int c = KNH_ASM_PUSH_PARAMS(ctx, b, tke, stmt, self.type, mtd, 0);

	if(IS_Method(mtd)) {
		KNH_ASM_CALL_METHOD(ctx, b, mtd, self.type, c);
		return new_asmv__ONSTACK(knh_Method_rtype(mtd));
	}
	else {
		KNH_ASM_DCALL_METHOD(ctx, b, 0, c);
		return new_asmv__ONSTACK(TYPE_any);
	}
}

/* ------------------------------------------------------------------------ */

Exception *new_Exception__NoSuchConstructor(Ctx *ctx, knh_class_t cid, char *mname)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), "NoSuchConstructor!!: %s in %s", CLASSN(cid), mname);
	return new_Exception__b(ctx, B(buf));
}

/* ------------------------------------------------------------------------ */

knh_asmv_t
knh_Cmpl_asmv__new(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst)
{
	/*['new', 'Class', 'p', 'p2'] */
	DEBUG_ASSERT(stmt->size > 1);
	Token *tke = (Token*)stmt->terms[1];
	knh_Stmt_setVisible(stmt, 1);

	knh_flag_t flag = knh_Stmt_metaflag__new(ctx, stmt);
	knh_methodn_t mn = knh_Token_tomethodn(ctx, (Token*)stmt->terms[0]);
	
	knh_class_t cid = knh_Token_toclass(ctx, tke, CLASS_unknown, knh_Cmpl_getNameSpace(ctx, b));
	if(knh_Token_isArrayType(tke)) {
		if(cid == CLASS_unknown || cid == CLASS_any) {
			cid = CLASS_Array;
		}
		else {
			cid = knh_type_toarray(ctx, cid);
		}
	}
	if(cid == CLASS_unknown) {
		MC_EPRINT(ctx, tke, MC_WARNING, "unknown class : %s", knh_Token_tochar(tke));
		KNH_ASM_PUSH__asmv(ctx, b, new_asmv__OBJ(KNH_NULL), isfirst); /* null */
		if(knh_Token_isNotNullType(tke)) {
			KNH_ASM_NULLCHK__ebp(ctx, b, 0);
			knh_Cmpl_setTypeError(b, 1);
		}	
		return new_asmv__OBJ(KNH_NULL);
	}
	
	knh_type_t type = (knh_Token_isNotNullType(tke)) ? cid : CLASS_TONULLABLE(cid);

	Method *mtd = knh_Class_getMethod(ctx, cid, mn);
	if(IS_NULL(mtd)) {
		if(stmt->size == 2) {
			KNH_ASM_NEW__DEF(ctx, b, isfirst, flag, cid);
		}
		else {
			MC_EPRINT(ctx, tke, MC_ERROR, "no such constructor: %s in %s", 
				knh_Token_tochar((Token*)stmt->terms[0]), CLASSN(cid));
			KNH_ASM_THROW__OBJ(ctx, b, new_Exception__NoSuchConstructor(ctx, cid, knh_Token_tochar((Token*)stmt->terms[0])));
			knh_Cmpl_setTypeError(b, 1);
		}
		return new_asmv__ONSTACK(type);
	}

	KNH_ASM_PUSH__asmv(ctx, b, new_asmv__OBJ(KNH_NULL), isfirst); /* new */
	KNH_ASM_PUSH__asmv(ctx, b, new_asmv__OBJ(knh_tclass_class(cid)), 0); /* self */

	if(knh_Token_isArrayType(tke)) {
		if(stmt->size == 2) {
			knh_Stmt_terms_add(ctx, stmt, new_Token__RAW(ctx, 0, tke, new_Int(ctx, 0)));
		}
		if(stmt->size == 3) {
			knh_class_t ecid = knh_Token_toclass(ctx, tke, CLASS_Nue, knh_Cmpl_getNameSpace(ctx, b));
			Object *ev = KNH_NULL;
			if(knh_tclass_hasDefaultValue(ecid)) {
				ev = knh_tclass_safevalue(ctx, ecid);
			}
			knh_Stmt_terms_add(ctx, stmt, new_Token__RAW(ctx, 0, tke, ev));
		}
	}

	knh_bool_t isautomap = knh_Token_isTailC(tke);
	int c = KNH_ASM_PUSH_PARAMS(ctx, b, tke, stmt, type, mtd, isautomap);

	if(TYPE_ISNULLABLE(knh_Method_rtype(mtd))) {
		if(knh_Token_isNotNullType(tke)) {
			KNH_ASM_NEW(ctx, b, c, mtd, flag, cid);
			return new_asmv__ONSTACK(type);
		}
		else{
			KNH_ASM_NEWE(ctx, b, c, mtd, flag, cid);
			return new_asmv__ONSTACK(TYPE_TONOTNULL(type));
		}
	}
	else {
		KNH_ASM_NEW(ctx, b, c, mtd, flag, cid);
		return new_asmv__ONSTACK(TYPE_TONOTNULL(type));
	}
}

/* ------------------------------------------------------------------------ */

knh_asmv_t
knh_Cmpl_asmv__movtext(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst)
{
	DEBUG_ASSERT(IS_Token(stmt->terms[0]));
	Token *tke = (Token*)stmt->terms[0];
	knh_Stmt_setVisible(stmt, 1);
	
	knh_methodn_t mn = knh_Token_tomethodn(ctx, tke);
	
	knh_Stmt_terms_seval(ctx, stmt, 1, CLASS_any, knh_Cmpl_getNameSpace(ctx, b));
	knh_asmv_t mtv = knh_Cmpl_asmv(ctx, b, stmt->terms[1], TYPE_any, isfirst);
	KNH_ASM_PUSH__asmv(ctx, b, mtv, isfirst);
	if(stmt->size == 2) {
		KNH_ASM_MT(ctx, b, mn);
		return new_asmv__ONSTACK(CLASS_String);
	}
	DEBUG_ASSERT(stmt->size == 3);
	knh_Stmt_terms_seval(ctx, stmt, 2, CLASS_any, knh_Cmpl_getNameSpace(ctx, b));
	if(knh_Term_isStaticValue(stmt->terms[2])) {
		KNH_ASM_MT__OPT(ctx, b, mn, ((Token*)stmt->terms[2])->data);
		return new_asmv__ONSTACK(CLASS_String);
	}
	else {
		MC_EPRINT(ctx, tke, MC_IGNORED, "illegal option");
		KNH_ASM_MT(ctx, b, mn);
		return new_asmv__ONSTACK(CLASS_String);
	}
}

/* ------------------------------------------------------------------------ */

knh_asmv_t
knh_Cmpl_asmv__map(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst)
{
	DEBUG_ASSERT(stmt->size > 1);
	DEBUG_ASSERT(IS_Token(stmt->terms[0]));
	Token *tke = (Token*)stmt->terms[0];
	knh_Stmt_setVisible(stmt, 1);
	
	knh_type_t ttype = knh_Token_totype(ctx, stmt->terms[0], CLASS_any, knh_Cmpl_getNameSpace(ctx, b));
	if(ttype == CLASS_any || ttype == TYPE_any) {
		ttype = req;
		if(ttype == CLASS_any || ttype == TYPE_any) {
			MC_EPRINT(ctx, tke, MC_WARNING, "unspecified target in mapping");
		}
		else{
			DEBUG("requested target in mapping: => %s%s", TYPEQN(ttype));
		}
	}
	knh_class_t tcid = TYPE_TONOTNULL(ttype);

	knh_Stmt_terms_seval(ctx, stmt, 1, tcid, knh_Cmpl_getNameSpace(ctx, b));
	knh_asmv_t srce = knh_Cmpl_asmv(ctx, b, stmt->terms[1], ttype, isfirst);
	knh_class_t scid = TYPE_TONOTNULL(srce.type);

	/* S extends T  S.instanceof(T)  S --> T */

	if(tcid == CLASS_any || knh_class_instanceof(scid, tcid)) {
		if(TYPE_ISNOTNULL(ttype) && TYPE_ISNULLABLE(srce.type)) {
			KNH_ASM_NULLCHK(ctx, b, srce);
		}
		else {
			MC_EPRINT(ctx, tke, MC_IGNORED, "%s --> %s", CLASSN(scid), CLASSN(tcid));
		}
		return srce;
	}
	
	if(scid == CLASS_any) {
		goto L_DYMAP;
	}

	MapMap *map = knh_tmapmap_find(ctx, scid, tcid);
	if(knh_MapMap_isNoSuchMapping(map)) {
		MC_EPRINT(ctx, tke, MC_TYPE, "no mapping: %s --> %s", CLASSN(scid), CLASSN(tcid));
		KNH_SAFEFREE(ctx, map);
		goto L_DYMAP;
	}

	if(knh_class_isFinal(TYPE_UNMASK(scid))) {
		KNH_ASM_PUSH__asmv(ctx, b, srce, isfirst);
		if(TYPE_ISNULLABLE(ttype)) {
			KNH_ASM_MAP_WM(ctx, b, map);
		}
		else {
			KNH_ASM_MAPE_WM(ctx, b, map);
		}			
		return new_asmv__ONSTACK(ttype);
	}
	
	L_DYMAP:;
	KNH_ASM_PUSH__asmv(ctx, b, srce, isfirst);
	if(TYPE_ISNULLABLE(ttype)) {
		KNH_ASM_MAP(ctx, b, tcid);
	}
	else {
		KNH_ASM_MAPE(ctx, b, tcid);
	}
	return new_asmv__ONSTACK(ttype);
}


/* ------------------------------------------------------------------------ */

knh_asmv_t
knh_Cmpl_asmv__alt(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst)
{
	char bufl[32];
	knh_snprintf(bufl, sizeof(bufl), "LL%3d", knh_Cmpl_llstep(b));
	knh_bytes_t lbn = B(bufl);
	knh_type_t type = req;
	knh_Stmt_setVisible(stmt, 1);

	int i;
	for(i = 0; i < stmt->size; i++) {
		knh_Stmt_terms_seval(ctx, stmt, i, CLASS_any, knh_Cmpl_getNameSpace(ctx, b));
		knh_asmv_t asmv = knh_Cmpl_asmv(ctx, b, stmt->terms[i], req, isfirst);
		KNH_ASM_PUSH__asmv(ctx, b, asmv, isfirst);
		isfirst = 1;
		if(i + 1 < stmt->size) {
			KNH_ASM_JMP_IFNONUL__ebp(ctx, b, lbn, 0);
		}
		if(i == 0) {
			type = TYPE_TONOTNULL(asmv.type);
		}
		else {
			if(type != TYPE_TONOTNULL(asmv.type)) 
				type = TYPE_TONOTNULL(TYPE_any);
		}
	}
	KNH_ASM_NULLCHK__ebp(ctx, b, 0);
	KNH_ASM_LABEL__b(ctx, b, lbn);
	return new_asmv__ONSTACK(type);
}

/* ------------------------------------------------------------------------ */

knh_asmv_t
knh_Cmpl_asmv__and(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst)
{
	char bufl[32];
	knh_snprintf(bufl, sizeof(bufl), "LL%3d", knh_Cmpl_llstep(b));
	knh_bytes_t lbn = B(bufl);
	
	int i;
	for(i = 0; i < stmt->size; i++) {
		knh_Stmt_terms_seval(ctx, stmt, i, CLASS_any, knh_Cmpl_getNameSpace(ctx, b));
		knh_asmv_t asmv = knh_Cmpl_asmv(ctx, b, stmt->terms[i], TYPE_Bool, isfirst);
		KNH_ASM_PUSH__asmv(ctx, b, asmv, isfirst);
		isfirst = 1;
		if(i + 1 < stmt->size) {
			KNH_ASM_JMP_IFF__ebp(ctx, b, lbn, 0);
		}
	}
	KNH_ASM_LABEL__b(ctx, b, lbn);
	knh_Stmt_setVisible(stmt, 1);
	return new_asmv__ONSTACK(TYPE_Bool);
}

/* ------------------------------------------------------------------------ */

knh_asmv_t
knh_Cmpl_asmv__or(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst)
{
	char bufl[32];
	knh_snprintf(bufl, sizeof(bufl), "LL%3d", knh_Cmpl_llstep(b));
	knh_bytes_t lbn = B(bufl);

	int i;
	for(i = 0; i < stmt->size; i++) {
		knh_Stmt_terms_seval(ctx, stmt, i, CLASS_any, knh_Cmpl_getNameSpace(ctx, b));
		knh_asmv_t asmv = knh_Cmpl_asmv(ctx, b, stmt->terms[i], TYPE_Bool, isfirst);
		KNH_ASM_PUSH__asmv(ctx, b, asmv, isfirst);
		isfirst = 1;
		if(i + 1 < stmt->size) {
			KNH_ASM_JMP_IFT__ebp(ctx, b, lbn, 0);
		}
	}
	KNH_ASM_LABEL__b(ctx, b, lbn);
	knh_Stmt_setVisible(stmt, 1);
	return new_asmv__ONSTACK(TYPE_Bool);
}

/* ------------------------------------------------------------------------ */

knh_asmv_t
knh_Cmpl_asmv__trinary(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t reqt, knh_bool_t isfirst)
{
	/* ['expr', 'expr', 'expr'] */
	DEBUG_ASSERT(stmt->size == 3);
	
	knh_Stmt_terms_seval(ctx, stmt, 0, CLASS_Bool, knh_Cmpl_getNameSpace(ctx, b));
	knh_asmv_t cnd = knh_Cmpl_asmv(ctx, b, stmt->terms[0], TYPE_Bool, isfirst);

	char lbelse[LABEL_BUFSIZ];
	knh_snprintf(lbelse, sizeof(lbelse), "ELSE_LL%d", knh_Cmpl_llstep(b));
	char lbend[LABEL_BUFSIZ];
	knh_snprintf(lbend, sizeof(lbend), "END_LL%d", knh_Cmpl_llstep(b));
	
	/* if */
	KNH_ASM_JMP_IFF(ctx, b, B(lbelse), cnd);
	knh_Stmt_terms_seval(ctx, stmt, 1, TYPE_TONOTNULL(reqt), knh_Cmpl_getNameSpace(ctx, b));
	knh_asmv_t tv = knh_Cmpl_asmv(ctx, b, stmt->terms[1], reqt, MC_FIRST);
	KNH_ASM_PUSH__asmv(ctx, b, tv, MC_FIRST);
	KNH_ASM_JMP(ctx, b, B(lbend));

	/* else */
	KNH_ASM_LABEL__b(ctx, b, B(lbelse));
	knh_Stmt_terms_seval(ctx, stmt, 2, TYPE_TONOTNULL(reqt), knh_Cmpl_getNameSpace(ctx, b));
	knh_asmv_t fv = knh_Cmpl_asmv(ctx, b, stmt->terms[2], reqt, MC_FIRST);
	KNH_ASM_PUSH__asmv(ctx, b, fv, MC_FIRST);
	KNH_ASM_LABEL__b(ctx, b, B(lbend));

	knh_Stmt_done(ctx, stmt);
	DEBUG("return type %s%s", TYPEQN(knh_typesystem_parentType(tv.type, fv.type)));
	knh_Stmt_setVisible(stmt, 1);
	return new_asmv__ONSTACK(knh_typesystem_parentType(tv.type, fv.type));
}

/* ------------------------------------------------------------------------ */

knh_asmv_t
knh_Cmpl_asmv__next(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst)
{
	/* Closure */
	TODO();
	return new_asmv__OBJ(KNH_NULL);	
}

/* ------------------------------------------------------------------------ */

knh_asmv_t
knh_Cmpl_asmv__method(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst)
{
	/* Closure */
	TODO();
	return new_asmv__OBJ(KNH_NULL);	
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
