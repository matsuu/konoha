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
/* [method] */

Stmt *
new_Stmt__method(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
	Stmt *b = new_Stmt(ctx, 0, STT_METHOD);
	knh_Stmt_add_meta(ctx, b, ts, s);

	if(knh_Token_isTYPEN(ts[*cp])) {
		knh_Stmt_terms_add(ctx, b, ts[*cp]);
		*cp += 1;
	}else {
		KNH_GOTO(L_ERR);
	}
	
	if(*cp < e && knh_Token_isNAME(ts[*cp])) {
		knh_Stmt_terms_add(ctx, b, ts[*cp]);
		*cp += 1;
	}else {
		KNH_GOTO(L_ERR);
	}
	
	if(*cp < e && ts[*cp]->tt == TT_PARENTHESIS) {
		knh_Stmt_terms_add(ctx, b, new_Stmt__params(ctx, ts[*cp]));
		knh_Token_tokens_empty(ctx, ts[*cp]);
		*cp += 1;
	}else {
		KNH_GOTO(L_ERR);
	}
	
	if(*cp < e && ts[*cp]->tt == TT_BRACE) {
		knh_Stmt_terms_add(ctx, b, new_Stmt__block(ctx, knh_Token_ts(ts[*cp]), 0, knh_Token_tokens_size(ts[*cp])));
		knh_Token_tokens_empty(ctx, ts[*cp]);
		*cp += 1;
	}else if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
		*cp += 1;
	}
	return b;
		
	L_ERR:;
	knh_int_t ee = knh_tokens_epos(s, *cp, e);
	MC_EPRINT(ctx, ts[ee], MC_ERROR, "method defintion: %s", knh_Token_tochar(ts[ee]));
	knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
	if(*cp == s) *cp += 1;
	*cp = knh_tokens_nextstmt(ts, *cp, e);
	return b;
}

/* ------------------------------------------------------------------------ */

Stmt *
new_Stmt__defun(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
	Stmt *b = new_Stmt(ctx, 0, STT_METHOD);
	knh_Stmt_add_meta(ctx, b, ts, s);

	knh_Stmt_terms_add(ctx, b, new_Token__text(ctx, ts[*cp], STEXT("any")));
	
	if(*cp < e && knh_Token_isNAME(ts[*cp])) {
		knh_Stmt_terms_add(ctx, b, ts[*cp]);
		*cp += 1;
	}else {
		KNH_GOTO(L_ERR);
	}
	
	if(*cp < e && ts[*cp]->tt == TT_PARENTHESIS) {
		knh_Stmt_terms_add(ctx, b, new_Stmt__params(ctx, ts[*cp]));
		knh_Token_tokens_empty(ctx, ts[*cp]);
		*cp += 1;
	}else {
		KNH_GOTO(L_ERR);
	}
	
	if(*cp < e && ts[*cp]->tt == TT_BRACE) {
		knh_Stmt_terms_add(ctx, b, new_Stmt__block(ctx, knh_Token_ts(ts[*cp]), 0, knh_Token_tokens_size(ts[*cp])));
		knh_Token_tokens_empty(ctx, ts[*cp]);
		*cp += 1;
	}else if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
		*cp += 1;
	}
	return b;
		
	L_ERR:;
	knh_int_t ee = knh_tokens_epos(s, *cp, e);
	MC_EPRINT(ctx, ts[ee], MC_ERROR, "method defintion: %s", knh_Token_tochar(ts[ee]));
	knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
	if(*cp == s) *cp += 1;
	*cp = knh_tokens_nextstmt(ts, *cp, e);
	return b;
}

/* ------------------------------------------------------------------------ */


Stmt *
new_Stmt__lambda(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
	Stmt *b = new_Stmt(ctx, 0, STT_METHOD);
	knh_Stmt_add_meta(ctx, b, ts, s);

	if(knh_Token_isTYPEN(ts[*cp])) {
		knh_Stmt_terms_add(ctx, b, ts[*cp]);
		*cp += 1;
	}else {
		KNH_GOTO(L_ERR);
	}

	knh_Stmt_terms_add(ctx, b, new_Token__ASIS(ctx, ts[*cp]));
	
	if(*cp < e && ts[*cp]->tt == TT_PARENTHESIS) {
		knh_Stmt_terms_add(ctx, b, new_Stmt__params(ctx, ts[*cp]));
		knh_Token_tokens_empty(ctx, ts[*cp]);
		*cp += 1;
	}else {
		KNH_GOTO(L_ERR);
	}
	
	if(*cp < e && ts[*cp]->tt == TT_BRACE) {
		knh_Stmt_terms_add(ctx, b, new_Stmt__block(ctx, knh_Token_ts(ts[*cp]), 0, knh_Token_tokens_size(ts[*cp])));
		knh_Token_tokens_empty(ctx, ts[*cp]);
		*cp += 1;
	}else if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
		*cp += 1;
	}
	return b;
	
	L_ERR:;
	knh_int_t ee = knh_tokens_epos(s, *cp, e);
	MC_EPRINT(ctx, ts[ee], MC_ERROR, "constructor/lambda: %s", knh_Token_tochar(ts[ee]));
	knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
	if(*cp == s) *cp += 1;
	*cp = knh_tokens_nextstmt(ts, *cp, e);
	return b;
}

/* ------------------------------------------------------------------------ */


Stmt *new_Stmt__params(Ctx *ctx, Token *tk)
{
	DEBUG_ASSERT(tk->tt == TT_PARENTHESIS);
	Token **ts = knh_Token_ts(tk);
	knh_int_t i, s = 0, e = knh_Token_tokens_size(tk);
	Stmt *stmt_head = NULL, *stmt;
	for(i = s; i < e; i++) {
		if(ts[i]->tt == TT_COMMA) {
			if(s == i) {
				MC_EPRINT(ctx, ts[i], MC_WARNING, "empty");
			}else {
				stmt = new_Stmt__param(ctx, ts, s, i);
				if(stmt_head == NULL) {
					stmt_head = stmt;
				}else{
					knh_Stmt_tail_append(ctx, stmt_head, stmt);
				}
			}
			s = i + 1;
		}
	}
	if(s != e) {
		stmt = new_Stmt__param(ctx, ts, s, e);
		if(stmt_head == NULL) {
			stmt_head = stmt;
		}else{
			knh_Stmt_tail_append(ctx, stmt_head, stmt);
		}
	}
	if(stmt_head == NULL) {
		return new_Stmt(ctx, 0, STT_DONE);
	}
	return stmt_head;
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__param(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e)
{
	DEBUG_ASSERT(s < e);
	knh_int_t c = knh_tokens_skipmeta(ts, s, e);
	
	if(!(c < e)) {
		MC_EPRINT(ctx, ts[s], MC_WARNING, "empty");
		return new_Stmt(ctx, 0, STT_DONE);
	}
	
	Stmt *stmt;
	if(knh_Token_isFIELDN(ts[c])) {
		stmt = new_Stmt(ctx, 0, STT_DECL);
		knh_Stmt_add_meta(ctx, stmt, ts, c);
		knh_Stmt_terms_add(ctx, stmt, new_Token__text(ctx, ts[c], STEXT("any")));
		knh_Stmt_terms_add(ctx, stmt, ts[c]);
		goto L_EXPR;
	}
	if(knh_Token_isTYPEN(ts[c]) && c+1 < e && knh_Token_isFIELDN(ts[c+1])) {
		stmt = new_Stmt(ctx, 0, STT_DECL);
		knh_Stmt_add_meta(ctx, stmt, ts, c);
		knh_Stmt_terms_add(ctx, stmt, ts[c]);
		knh_Stmt_terms_add(ctx, stmt, ts[c+1]);
		c++;
		goto L_EXPR;
	}
	
	MC_EPRINT(ctx, ts[c], MC_ERROR, "wrong param: %s", knh_Token_tochar(ts[c]));
	return new_Stmt__SyntaxError(ctx, ts, s, e, &c);

	L_EXPR:;
	if(c + 1 == e) {
		knh_Stmt_terms_add(ctx, stmt, new_Token__RAW(ctx, 0, ts[c], KNH_NULL));
		return stmt;
	}
	
	if(ts[c+1]->tt == TT_LET && c + 2 < e) {
		knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, c+2, e, KNH_STT_RVALUE));
		return stmt;
	}
	
	MC_EPRINT(ctx, ts[c], MC_WARNING, "wrong parameter value: %s", knh_Token_tochar(ts[c+1]));
	knh_Stmt_terms_add(ctx, stmt, new_Token__using_Null(ctx, ts[c]));
	return stmt;
}


#ifdef __cplusplus
}
#endif
