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
/* [token] */

knh_int_t knh_tokens_lastexpr(Token **ts, knh_int_t s, knh_int_t e)
{
	knh_int_t i;
	for(i = s; i < e; i++) {
		if(!knh_token_isInExpr(ts[i]->tt)) {
			return i;
		}
	}
	return e;
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_tokens_nextstmt(Token **ts, knh_int_t s, knh_int_t e)
{
	knh_int_t i;
	for(i = s; i < e; i++) {
		if(ts[i]->tt == TT_SEMICOLON) {
			while(ts[i]->tt == TT_SEMICOLON) {
				i++;
				if(i == e) break;
			}
			return i;
		}
		if(knh_token_isStatement(ts[i]->tt)) {
			return i;
		}
	}
	return e;
}


/* ------------------------------------------------------------------------ */

knh_index_t knh_tokens_find(Token **ts, knh_int_t s, knh_int_t e, knh_type_t type)
{
	knh_index_t i ;
	for(i = s; i < e; i++) {
		if(ts[i]->tt == type) return i;
	}
	return -1;
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_tokens_lastexpr_withlet(Token **ts, knh_int_t s, knh_int_t e)
{
	knh_int_t i;
	for(i = s; i < e; i++) {
		if(TT_LET <= ts[i]->tt && ts[i]->tt <= TT_ALTLET) continue;
		if(!knh_token_isInExpr(ts[i]->tt)) {
			return i;
		}
	}
	return e;
}

/* ------------------------------------------------------------------------ */

knh_index_t knh_tokens_findlet(Token **ts, knh_int_t s, knh_int_t e)
{
	knh_index_t i ;
	for(i = s; i < e; i++) {
		if(TT_LET <= ts[i]->tt && ts[i]->tt <= TT_ALTLET) return i;
	}
	return -1;
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_tokens_count(Token **ts, knh_int_t s, knh_int_t e, knh_type_t type)
{
	knh_index_t i, c = 0;
	for(i = s; i < e; i++) {
		if(ts[i]->tt == type) c++;
	}
	return c;
}

/* ======================================================================== */
/* [token] */

#define _knh_Token_isFirstExpr(tk)    (knh_token_isInExpr(tk->tt) && !knh_token_isNotFirst(tk->tt))

/* ======================================================================== */
/* [expr] */

Stmt *new_Stmt__expr(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
	knh_int_t le = knh_tokens_lastexpr_withlet(ts, s, e);
	*cp = le;
	if(le < e && ts[le]->tt == TT_ERR) {
		return new_Stmt__SyntaxError(ctx, ts, s, e, cp);
	}
	e = le;
	//DEBUG("e = %d, *cp = %d, le =%d", e, *cp, le);
	
	if(e - s == 0) {
		return new_Stmt(ctx, 0, STT_DONE);
	}
	
	if(knh_tokens_isVariableDeclared(ts, s, e)) {
		return new_Stmt__decl(ctx, ts, s, e);
	}
	
	/* Check assignment */
	knh_index_t idx = knh_tokens_findlet(ts, s, e);
	if(idx == -1) {
		Term *term = new_Term__expr(ctx, ts, s, e, KNH_STT_RVALUE);
		if(IS_Token(term)) {
			Stmt *stmt = new_Stmt(ctx, 0, STT_CALL);
			knh_Stmt_terms_add(ctx, stmt, term);
			return stmt;
		}
		DEBUG_ASSERT(IS_Stmt(term));
		return (Stmt*)term;
	}

	DEBUG_ASSERT(s < idx);
	Term *lterm = new_Term__expr(ctx, ts, s, idx, KNH_STT_LVALUE);
	
	Stmt *stmt = NULL;
	if(IS_Stmt(lterm)) {
		if(knh_Term_isLTermSetter(lterm)) {
			stmt = (Stmt*)lterm;
		}
		else {
			MC_EPRINT(ctx, ts[idx], MC_ERROR, "invalid lvalue");
			knh_Stmt_toSyntaxError(ctx, stmt, ts[idx]);
			return stmt;
		}
	}
	else {
		Token *tkl = (Token*)lterm;
		DEBUG_ASSERT(IS_Token(tkl));

		stmt = new_Stmt(ctx, 0, STT_LET);
		knh_Stmt_terms_add(ctx, stmt, lterm);

//		knh_Token_dump(ctx, tkl, KNH_STDOUT, KNH_NULL);
		if(tkl->tt != TT_NAME || knh_bytes_index(knh_Token_tobytes(tkl), '.') != -1 || knh_Token_isSystemVariable(tkl)) {
			MC_EPRINT(ctx, ts[idx], MC_ERROR, "invalid lvalue: %s", knh_Token_tochar(tkl));
			knh_Stmt_toSyntaxError(ctx, stmt, tkl);
			return stmt;
		}
	}
	if(ts[idx]->tt == TT_LET) {
		knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, idx+1, e, KNH_STT_RVALUE));
	}
	else {
		ts[idx]->tt = ts[idx]->tt - (TT_ADDE - TT_ADD);
		Token *op = knh_tokens_findop(ts, s, e);
		if(IS_NULL(op) || op->tt == ts[idx]->tt) {
			knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, s, e, KNH_STT_RVALUE));
		}
		else {
			Stmt *stmtop = new_Stmt(ctx, 0, STT_OP);
			knh_Stmt_terms_add(ctx, stmtop, ts[idx]);
			knh_Stmt_terms_add(ctx, stmtop, new_Term__expr(ctx, ts, s, idx, KNH_STT_RVALUE));
			knh_Stmt_terms_add(ctx, stmtop, new_Term__expr(ctx, ts, idx+1, e, KNH_STT_RVALUE));
			knh_Stmt_terms_add(ctx, stmt, stmtop);
		}
	}
	return stmt;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_Term_isLTermSetter(Term *b)
{
	if(!IS_Stmt(b)) return 0;
	
	Stmt *stmt = (Stmt*)b;
	DEBUG("stmt->size='%d'", stmt->size);
	DEBUG_ASSERT(stmt->size > 1);
//	if(stmt->size < 2) return 0;

	Token *tk = (Token*)stmt->terms[0];
	DEBUG_ASSERT(IS_Token(tk));

	char *f = knh_Token_tochar(tk);
	DEBUG("f='%s'", f);
	if(f[0] == 's' && f[1] == 'e' && f[2] == 't' && (f[3] == '\0' || isupper(f[3]))) {
		return 1;
	}
	return 0;
}


/* ======================================================================== */
/* [decl] */

knh_bool_t knh_tokens_isVariableDeclared(Token **ts, knh_int_t s, knh_int_t e)
{
	return (s + 1 < e && knh_Token_isTYPEN(ts[s]) && knh_Token_isFIELDN(ts[s+1]));
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__decl(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e)
{
	Stmt *stmt_head = new_Stmt(ctx, 0, STT_DECL);
	s = knh_tokens_skipmeta(ts, s, e);
	knh_Stmt_add_meta(ctx, stmt_head, ts, s);

	knh_int_t typeidx = s, nameidx = s + 1, cmaidx = 0;
	Stmt *stmt = stmt_head;
	
	L_TYPE:;
	knh_Stmt_terms_add(ctx, stmt, ts[typeidx]);        /* Type */
	knh_Stmt_terms_add(ctx, stmt, ts[nameidx]);        /* name */
	if(nameidx+1 == e) {
		knh_Stmt_terms_add(ctx, stmt, new_Token__ASIS(ctx, ts[nameidx]));
		return stmt_head;              /* @see(new_Stmt__foreach) */
	}
	if(ts[nameidx+1]->tt == TT_SEMICOLON) {
		knh_Stmt_terms_add(ctx, stmt, new_Token__ASIS(ctx, ts[nameidx]));
		return stmt_head;
	}
	
	if(ts[nameidx+1]->tt == TT_LET) {
		knh_int_t le = knh_tokens_find(ts, nameidx+2, e, TT_COMMA);
		if(le == -1) {
			le = knh_tokens_lastexpr(ts, nameidx+2, e);
		}
		if(nameidx+2 == le) {
			MC_EPRINT(ctx, ts[nameidx], MC_WARNING, "illegal initial value: %s", knh_Token_tochar(ts[nameidx]));
			knh_Stmt_terms_add(ctx, stmt, new_Token__ASIS(ctx, ts[nameidx]));
		}
		else {
			knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, nameidx+2, le, KNH_STT_RVALUE));
		}
	}
	else {
		if(ts[nameidx+1]->tt != TT_COMMA) {
			MC_EPRINT(ctx, ts[nameidx], MC_WARNING, "illegal initial value: %s", knh_Token_tochar(ts[nameidx]));
		}
		knh_Stmt_terms_add(ctx, stmt, new_Token__ASIS(ctx, ts[nameidx]));
	}

	cmaidx = knh_tokens_find(ts, nameidx, e, TT_COMMA);
	if(cmaidx == -1 || !(cmaidx + 1 < e)) {
		return stmt_head;
	}
	
	nameidx = cmaidx + 1;
	if(knh_Token_isFIELDN(ts[nameidx])) {
		stmt = new_Stmt(ctx, 0, STT_DECL);
		KNH_SETv(ctx, stmt->meta, stmt_head->meta);
		knh_Stmt_tail_append(ctx, stmt_head, stmt);
		goto L_TYPE;
	}
	else {
		MC_EPRINT(ctx, ts[nameidx], MC_WARNING, "illegal name: %s", knh_Token_tochar(ts[nameidx]));
		return stmt_head;
	}
}

/* ------------------------------------------------------------------------ */

Term *new_Term__pexpr(Ctx *ctx, Token *tk)
{
	DEBUG_ASSERT(tk->tt == TT_PARENTHESIS);
	if(knh_Token_tokens_size(tk) == 0) {
		return new_Token__using_Null(ctx, tk);
	}
	Token **ts = knh_Token_ts(tk);
	knh_int_t e = knh_Token_tokens_size(tk);
	knh_int_t ee = knh_tokens_find(ts, 0, e, TT_LET);
	if(ee != -1) {
		MC_EPRINT(ctx, ts[ee], MC_WARNING, "you should have used '=='");
		ts[ee]->tt = TT_EQ;		
	}
	ee = knh_tokens_lastexpr(ts, 0, e);
	if(ee < e) {
		MC_EPRINT(ctx, ts[ee], MC_IGNORED, "%s ...", knh_Token_tochar(ts[ee]));
	}
	return new_Term__expr(ctx, ts, 0, ee, KNH_STT_RVALUE);
}

/* ------------------------------------------------------------------------ */

Term *new_Term__expr(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, int value)
{
	Stmt *stmt = NULL;
	knh_int_t c = s;

	if(!(s < e)) {
		DEBUG("s=%d, e=%d", (int)s, (int)e);
		DEBUG_ASSERT(s < e);
	}
	if (s + 1 == e) {
		return new_Term__value(ctx, ts[s], value);
	}
	
	if(ts[s+1]->tt == TT_QUESTION) {
		if(ts[s]->tt != TT_PARENTHESIS) {
			KNH_GOTO(L_ERR);
		}
		return new_Stmt__trinary(ctx, ts, s, e, ts[s+1]);
	}
	
	Token *op = knh_tokens_findop(ts, s, e);
	if(IS_NOTNULL(op)) {
		//DEBUG("found op %s", knh_Token_tochar(op));
		return new_Stmt__op(ctx, ts, s, e, op);
	}

	/* cast operator (C)a */
	if(knh_Token_isCast(ctx, ts[s])) {
		return new_Stmt__cast(ctx, ts, s, e);
	}

	/** first **/
	DEBUG_ASSERT(c+1 < e);
	
	if(ts[c]->tt == TT_NAME) {
		if(knh_Token_isNEW(ts[c])) {  /* new Class (...) */
			if(knh_Token_isTYPEN(ts[c+1]) && knh_Token_isNextParenthesis(ts[c+1])) {
				stmt = new_Stmt(ctx, 0, STT_NEW);
				knh_Stmt_terms_add(ctx, stmt, ts[c]);
				if(knh_Token_isExceptionType(ts[c+1])) {
					knh_Stmt_terms_add(ctx, stmt, new_Token__text(ctx, ts[c], STEXT("Exception")));
					knh_Stmt_terms_add(ctx, stmt, ts[c+1]);
					{
						char buf[KONOHA_NAME_SIZE];
						snprintf(buf, sizeof(buf), "%s!!", knh_Token_tochar(ts[c+1]));
						KNH_SETv(ctx, ts[c+1]->data, new_String__fast(ctx, CLASS_String, B(buf)));
						ts[c+1]->tt = TT_RAW;
					}
				}
				else {
					knh_Stmt_terms_add(ctx, stmt, ts[c+1]);
				}
				c+=2;
				goto L_PARAM;
			}
			if(knh_Token_isTYPEN(ts[c+1]) && knh_Token_isNextBrancet(ts[c+1])) {
				stmt = new_Stmt(ctx, 0, STT_NEW);
				knh_Stmt_terms_add(ctx, stmt, new_Token__text(ctx, ts[c], STEXT("new::array")));
				knh_Stmt_terms_add(ctx, stmt, ts[c+1]);
				knh_Token_setArrayType(ts[c+1], 1); 
				ts[c+2]->tt = TT_PARENTHESIS;
				c+=2;
				goto L_PARAM;
			}
			c++;
			KNH_GOTO(L_ERR);
		}

		if(knh_Token_isNextParenthesis(ts[c])) {
			stmt = new_Stmt__name(ctx, ts[c], value);
			c++;
			goto L_PARAM;
		}		
		if((c + 1 < e && ts[c+1]->tt == TT_BRANCET)) {
			Term *tmn = new_Term__value(ctx, ts[s], KNH_STT_RVALUE);
			if(IS_Stmt(tmn) && ((Stmt*)tmn)->size == 1) {
				stmt = (Stmt*)tmn;
			}else {
				stmt = new_Stmt__term(ctx, 0, STT_CALL, tmn);
			}
			c++;
			goto L_FUNC;
		}
		c++;
		KNH_GOTO(L_ERR);
	}
	if(ts[c]->tt == TT_MOVTEXT) {
		if(!knh_Token_isNextParenthesis(ts[c])) {
			c++; 
			KNH_GOTO(L_ERR);
		}
		stmt = new_Stmt(ctx, 0, STT_MOVTEXT);
		knh_Stmt_terms_add(ctx, stmt, ts[c]);
		c++;
		goto L_PARAM;
	}
	if(knh_Token_isTYPEN(ts[c])) {
		if(knh_Token_isNextParenthesis(ts[c])) { /* Class(o, n) */
			stmt = new_Stmt(ctx, 0, STT_MAP);
			knh_Stmt_terms_add(ctx, stmt, ts[c]);
			c++;
			goto L_PARAM;
		}
		if(c+1 < e && ts[c+1]->tt == TT_BRACE) {  /* Class{..} */
			stmt = new_Stmt__newClass(ctx, ts[c], ts[c+1]);
			c+=2;
			goto L_NEXT;
		}
#ifdef KONOHAC_CLOSURE
		if(c+1 < e && ts[c+1]->tt == TT_LAMBDA && knh_Token_isNextParenthesis(ts[c+1])) {
			/* TYPE lamda () {} */
			stmt = new_Stmt__method(ctx, ts, c, e);
			c+=4;
			goto L_NEXT;
		}
#endif
		c++;
		KNH_GOTO(L_ERR);
	}
	
	DEBUG_ASSERT(stmt == NULL);
	Term *tm = new_Term__value(ctx, ts[c], value);
	if(IS_Token(tm) && ((Token*)tm)->tt == TT_ERR) {
		return tm;
	}
	
	stmt = new_Stmt(ctx, 0, STT_CALL);
	knh_Stmt_terms_add(ctx, stmt, tm);
	c++;

	L_FUNC:; /****** second ************************************/
	DEBUG_ASSERT(stmt != NULL);
	DEBUG_ASSERT(stmt->size == 1);
	
	if(ts[c]->tt == TT_NAME) {
		stmt = knh_Stmt_add_name__second(ctx, stmt, ts[c], value);
		if(knh_Token_isNextParenthesis(ts[c])) {
			c++;
			goto L_PARAM;
		}
		if(c + 1 < e) {  /* f """ """ */
			MC_EPRINT(ctx, ts[c+1], MC_IGNORED, "%s ...", knh_Token_tochar(ts[c+1]));
		}
		return stmt;
	}
	if(ts[c]->tt == TT_BRANCET) {
		knh_Stmt_add_index(ctx, stmt, ts[c], value);
		c++;
		goto L_NEXT;
	}
	KNH_GOTO(L_ERR);

	/** third *************************************************************/

	L_PARAM:;
	DEBUG_ASSERT(stmt != NULL);
	DEBUG_ASSERT(stmt->size >= 2 || ((stmt->stt == STT_MOVTEXT || stmt->stt == STT_MAP) && stmt->size == 1));
	DEBUG_ASSERT(c < e && ts[c]->tt == TT_PARENTHESIS);
	knh_Stmt_add_exprs(ctx, stmt, knh_Token_ts(ts[c]), 0, knh_Token_tokens_size(ts[c]));
	if((stmt->stt == STT_MOVTEXT || stmt->stt == STT_MAP) && stmt->size == 1) {
		MC_EPRINT(ctx, ts[c], MC_WARNING, "empty ()");
		knh_Stmt_terms_add(ctx, stmt, new_Token__RAW(ctx, 0, ts[c], KNH_NULL));
	}
	c++;
	
	L_NEXT:;
	//DEBUG("CHECK_NEXT: s=%d c=%d e=%d\n", (int)s, (int)c, (int)e);
	if(c < e) {
		stmt = new_Stmt__stmt(ctx, stmt);
		goto L_FUNC;
	}
	return stmt;
	
	L_ERR:; /* error */
	knh_int_t ee = knh_tokens_epos(s, c, e);
	MC_EPRINT(ctx, ts[ee], MC_ERROR, "%s", knh_Token_tochar(ts[ee]));
	if(stmt == NULL) {
		return new_Stmt__SyntaxError(ctx, ts, c, e, &c);
	}
	knh_Stmt_toSyntaxError(ctx, stmt, ts[ee]);
	return stmt;
}


/* ======================================================================== */
/* [op] */

Token *knh_tokens_findop(Token **ts, knh_int_t s, knh_int_t e)
{
	knh_int_t i;
	Token *op = KNH_NULL;
	knh_token_t op_type = TT_NAME;
	for(i = s; i < e; i++) {
//		if(ts[i]->tt == TT_LET) {
//			MC_EPRINT(ctx, ts[i], MC_WARNING, "you should have used '=='");
//			ts[i]->tt = TT_EQ;
//		}
		if(TT_ALTLET < ts[i]->tt && ts[i]->tt < op_type) {
			op = ts[i];
			op_type = ts[i]->tt;
		}
	}
	if(knh_Token_isOP(op) || op->tt == TT_AND || op->tt == TT_OR || op->tt == TT_ALT || op->tt == TT_QUESTION) {
		return op;
	}
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__op(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, Token *op)
{
	knh_int_t c = s;
	Stmt *stmt;
	knh_stmt_t stt = STT_OP;
	switch(op->tt) {
		case TT_AND: stt = STT_AND; break;
		case TT_OR:  stt = STT_OR; break;
		case TT_ALT: stt = STT_ALT; break;
	}
	if(ts[c]->tt == op->tt) {
		stmt = new_Stmt(ctx, KNH_FLAG_STMTF_ADPOSITION, stt);
		c++;
	}
	else{
		stmt = new_Stmt(ctx, 0, stt);
	}
	if(stt == STT_OP) {
		knh_Stmt_terms_add(ctx, stmt, op);
	}
	int i;
	for(i = c; i < e; i++) {
		if(ts[i]->tt == op->tt) {
			knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, c, i, KNH_STT_RVALUE));
			c = i + 1;
		}
	}
	if(c < e) {
		knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, c, e, KNH_STT_RVALUE));
	}
	return stmt;
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__trinary(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, Token *op)
{
	DEBUG_ASSERT(ts[s]->tt == TT_PARENTHESIS && ts[s+1]->tt == TT_QUESTION);
	Stmt *stmt = new_Stmt(ctx, 0, STT_TRINARY);
	knh_Stmt_terms_add(ctx, stmt, new_Term__pexpr(ctx, ts[s]));
	int i;
	for(i = s + 2; i < e; i++) {
		if(ts[i]->tt == TT_LABEL) {
			ts[i]->tt = TT_NAME;
			if(i+1 < e) {
				knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, s+2, i+1, KNH_STT_RVALUE));
				knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, i+1, e, KNH_STT_RVALUE));
			}
			else {
				MC_EPRINT(ctx, op, MC_ERROR, "illegal trinary operator");
				knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, s+2, i+1, KNH_STT_RVALUE));
				knh_Stmt_terms_add(ctx, stmt, new_Token__using_Null(ctx, ts[i]));
			}
			break;
		}
		if(ts[i]->tt == TT_COLON) {
			if(i+1 < e) {
				knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, s+2, i, KNH_STT_RVALUE));
				knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, i+1, e, KNH_STT_RVALUE));
			}
			else {
				MC_EPRINT(ctx, op, MC_ERROR, "illegal trinary operator: ");
				knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, s+2, i, KNH_STT_RVALUE));
				knh_Stmt_terms_add(ctx, stmt, new_Token__using_Null(ctx, ts[i]));
			}
			break;
		}
	}
	if(i < e) {
		return stmt;
	}
	MC_EPRINT(ctx, op, MC_ERROR, "illegal trinary operator");
	knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, s+2, e, KNH_STT_RVALUE));
	knh_Stmt_terms_add(ctx, stmt, new_Token__using_Null(ctx, ts[e-1]));
	return stmt;
}

/* ======================================================================== */
/* [cast] */

knh_bool_t knh_Token_isCast(Ctx *ctx, Token *b)
{
	if(b->tt != TT_PARENTHESIS || knh_Token_tokens_size(b) != 1) return 0;
	Token *tk = knh_Tokens(b, 0);
	if(tk->tt == TT_MUL) {
		DEBUG("* => any");
		tk->tt = TT_TYPEN;
		KNH_SETv(ctx, tk->data, new_String__fast(ctx, CLASS_String, STEXT("any")));
	}
	return knh_Token_isTYPEN(tk);
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__cast(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e)
{
	Stmt *stmt = new_Stmt(ctx, 0, STT_MAP);
	knh_Stmt_terms_add(ctx, stmt, new_Term__value(ctx, ts[s], KNH_STT_RVALUE));
	knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, s+1, e, KNH_STT_RVALUE));
	return stmt;
}

/* ======================================================================== */
/* [index] */

void knh_Stmt_add_index(Ctx *ctx, Stmt *stmt, Token *brc, int value)
{
	DEBUG_ASSERT(brc->tt == TT_BRANCET);
	Token **ts = knh_Token_ts(brc);
	int i = 0, s = 0, c = -1, e = knh_Token_tokens_size(brc);
	knh_bytes_t func;
	
	for(i = 0; i < e; i++) {
		if(ts[i]->tt == TT_SUBSET || ts[i]->tt == TT_COLON) {
			func = STEXT("sub()");
			c = i; break;
		}
		if(ts[i]->tt == TT_LABEL) {
			func = STEXT("sub()");
			c = i + 1; break;
		}
		if(ts[i]->tt == TT_OFFSET || ts[i]->tt == TT_POFFSET) {
			func = STEXT("slice()");
			c = i; break;
		}
		if(ts[i]->tt == TT_SLICE || ts[i]->tt == TT_PSLICE) {
			func = STEXT("slice()");
			c = i; break;
		}
	}
	if(c >= 0) {
		if(value == KNH_STT_LVALUE) {
			MC_EPRINT(ctx, brc, MC_ERROR, "cannot subset slicing in lvalue");
			knh_Stmt_toSyntaxError(ctx, stmt, brc);
			return;
		}
		knh_Stmt_terms_add(ctx, stmt, new_Token__text(ctx, brc, func));
		knh_Stmt_swap01(ctx, stmt);
		if(i == 0) {
			knh_Stmt_terms_add(ctx, stmt, new_Token__RAW(ctx, 0, brc, KNH_NULL));
		}
		else{
			knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, 0, c, KNH_STT_RVALUE));
		}
		if(i + 1 == e) {
			knh_Stmt_terms_add(ctx, stmt, new_Token__RAW(ctx, 0, brc, KNH_NULL));
		}
		else {
			knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, i+1, e, KNH_STT_RVALUE));
		}
		knh_Token_tokens_empty(ctx, brc);
		return;
	}

	if(value == KNH_STT_LVALUE) {
		knh_Stmt_terms_add(ctx, stmt, new_Token__text(ctx, brc, STEXT("set()")));
	}
	else{
		knh_Stmt_terms_add(ctx, stmt, new_Token__text(ctx, brc, STEXT("get()")));
	}		
	knh_Stmt_swap01(ctx, stmt);
	for(i = s; i < e; i++) {
		if(ts[i]->tt == TT_COMMA) {
			knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, s, i, KNH_STT_RVALUE));
			s = i + 1;
		}
	}
	if(s != e) {
		knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, s, e, KNH_STT_RVALUE));
	}
	else if(e == 0) {
		MC_EPRINT(ctx, brc, MC_WARNING, "empty");
		knh_Stmt_terms_add(ctx, stmt, new_Token__using_Null(ctx, brc));
	}
	knh_Token_tokens_empty(ctx, brc);
}

/* ======================================================================== */
/* [(expr,expr,expr)] */

void knh_Stmt_add_exprs(Ctx *ctx, Stmt *stmt, Token **ts, knh_int_t s, knh_int_t e)
{
	knh_int_t i;
	for(i = s; i < e; i++) {
		if(ts[i]->tt == TT_COMMA) {
			knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, s, i, KNH_STT_RVALUE));
			s = i + 1;
		}
	}
	if(s != e) {
		knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, s, e, KNH_STT_RVALUE));
	}
}

/* ======================================================================== */
/* [stmt3] */

void knh_Stmt_add_stmt3(Ctx *ctx, Stmt *b, Token *tk)
{
	DEBUG_ASSERT(tk->tt == TT_PARENTHESIS);
	
	Token **ts = knh_Token_ts(tk);
	knh_int_t i, s = 0, e = knh_Token_tokens_size(tk), cp = 0;

	/* for(FIRST;second;third) */
	i = knh_tokens_find(ts, 0, e, TT_SEMICOLON);
	if(i == -1) {
		MC_EPRINT(ctx, tk, MC_ERROR, "';' required in for statement");
		knh_Stmt_toSyntaxError(ctx, b, tk);
		return;
	}
	if(i == 0) {
		knh_Stmt_terms_add(ctx, b, new_Stmt(ctx, 0, STT_DONE));
	}
	else {
		knh_Stmt_terms_add(ctx, b, new_Stmt__expr(ctx, ts, 0, i, &cp));
		//DEBUG("s=%d, cp=%d", (int)(i+1), (int)cp);
	}
	
	/* for(first;SECODN;third) */
	s = i+1;
	i = knh_tokens_find(ts, s, e, TT_SEMICOLON);
	if(i == -1) {
		MC_EPRINT(ctx, tk, MC_ERROR, "';' required in for statement");
		knh_Stmt_toSyntaxError(ctx, b, tk);
		return ;
	}
	if(i == s) {
		knh_Stmt_terms_add(ctx, b, new_Token__RAW(ctx, 0, ts[s], KNH_TRUE));
	}
	else if(knh_Token_isFirstExpr(ts[s])) {
		knh_Stmt_terms_add(ctx, b, new_Term__expr(ctx, ts, s, i, KNH_STT_RVALUE));
	}
	else {
		MC_EPRINT(ctx, tk, MC_ERROR, "not expression: %s ..", knh_Token_tochar(ts[s]));
		knh_Stmt_toSyntaxError(ctx, b, ts[s]);
		return ;
	}
	
	/* for(first;second;THIRD) */
	if(i+1==e) {
		knh_Stmt_terms_add(ctx, b, new_Stmt(ctx, 0, STT_DONE));
	}
	else {
		knh_Stmt_terms_add(ctx, b, new_Stmt__expr(ctx, ts, i+1, e, &cp));
		//DEBUG("e=%d, cp=%d", (int)(e), (int)cp);
	}
}


/* ------------------------------------------------------------------------ */

void knh_Stmt_add_fromwhere(Ctx *ctx, Stmt *b, Token *tk)
{
	DEBUG_ASSERT(tk->tt == TT_PARENTHESIS);
	
	Token **ts = knh_Token_ts(tk);
	knh_int_t s = 0, e = knh_Token_tokens_size(tk), c = 0;

	/* TYPEN */
	if(c+1 < e && knh_Token_isTYPEN(ts[c]) && knh_Token_isFIELDN(ts[c+1])) {
		knh_Stmt_terms_add(ctx, b, new_Stmt__decl(ctx, ts, c, c+2));
		knh_Stmt_terms_add(ctx, b, ts[c+1]);
		c += 2;
	}
	/* FIELDN */
	else if(c < e && knh_Token_isFIELDN(ts[c])) {
		Stmt *d = new_Stmt(ctx, 0, STT_DECL);
		knh_Stmt_terms_add(ctx, d, new_Token__ASIS(ctx, ts[c]));
		knh_Stmt_terms_add(ctx, d, ts[c]);
		knh_Stmt_terms_add(ctx, b, d);
		knh_Stmt_terms_add(ctx, b, ts[c]);
		c += 1;
	}
	else {
		KNH_GOTO(L_ERR);
	}
	
	/* TT_FROM */
	if(c < e && (ts[c]->tt == TT_FROM || ts[c]->tt == TT_IN)) {
		c += 1;
	}
	else {
		KNH_GOTO(L_ERR);
	}

    /* expr */
	if(c < e && knh_Token_isFirstExpr(ts[c])) {
		knh_int_t ef = knh_tokens_find(ts, c, e, TT_WHERE);
		if(ef == -1) ef = e;
		knh_Stmt_terms_add(ctx, b, new_Term__expr(ctx, ts, c, ef, KNH_STT_RVALUE));
		c = ef;
	}
	else {
		KNH_GOTO(L_ERR);
	}

   /* ?where */
	if(c < e && ts[c]->tt == TT_WHERE) {
		c += 1;
		if(c < e && knh_Token_isFirstExpr(ts[c])) {
			knh_Stmt_terms_add(ctx, b, new_Term__expr(ctx, ts, c, e, KNH_STT_RVALUE));
			return;
		}
	}

	knh_Stmt_terms_add(ctx, b, new_Token__RAW(ctx, 0, tk, KNH_TRUE));
	return;
	
	L_ERR:;
	knh_int_t ee = knh_tokens_epos(s, c, e);
	MC_EPRINT(ctx, ts[ee], MC_ERROR, "foreach statement: %s", knh_Token_tochar(ts[ee]));
	knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
	return;
}

/* ======================================================================== */

#ifdef __cplusplus
}
#endif
