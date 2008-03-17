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
/* [stmt] */


Stmt *new_Stmt__stmt(Ctx *ctx, Stmt *stmt)
{
	Stmt *b = new_Stmt(ctx, 0, STT_CALL);
	knh_Stmt_terms_add(ctx, b, stmt);
	return b;	
}

/* ------------------------------------------------------------------------ */


Stmt *new_Stmt__term(Ctx *ctx, knh_flag_t flag, knh_stmt_t stt, Term *tm)
{
	Stmt *b = new_Stmt(ctx, flag, stt);
	knh_Stmt_terms_add(ctx, b, tm);
	return b;	
}

/* ======================================================================== */
/* [term] */

Term *
new_Term__value(Ctx *ctx, Token *tk, int value)
{
	
	switch(tk->tt) {
		case TT_NAME:
		{
			knh_bytes_t t = knh_Token_tobytes(tk);
			if(ISB(t, "null")) {
				return new_Token__RAW(ctx, 0, tk, KNH_NULL);
			}
			if(ISB(t, "true")) {
				return new_Token__RAW(ctx, 0, tk, KNH_TRUE);
			}
			if(ISB(t, "false")) {
				return new_Token__RAW(ctx, 0, tk, KNH_FALSE);
			}
			return new_Term__name(ctx, tk, value);
		}
		case TT_PARENTHESIS:
			return new_Term__Tuple(ctx, tk);
		case TT_BRANCET:
			return new_Stmt__Array(ctx, tk);
		case TT_BRACE:
			return new_Stmt__DictMap(ctx, tk);
		case TT_PROPN:
			return new_Term__PROPN(ctx, tk, value);
		case TT_FMTSTR:
			TODO();
		case TT_STR:
		case TT_NUM:
		case TT_QSTR:
		case TT_URN:
		case TT_TYPEN:
		case TT_CONSTN:
		case TT_ERR:
			return tk;
	}
	MC_EPRINT(ctx, tk, MC_ERROR, "unexpected value: %s", knh_Token_tochar(tk));
	//knh_Token_toERR(ctx, tk);
	return tk;
}

/* ======================================================================== */
/* [this] */

Token *new_Token__this(Ctx *ctx, Token *tk)
{
	return new_Token__text(ctx, tk, STEXT("_"));
}

/* ======================================================================== */
/* [name] */

Term *new_Term__name(Ctx *ctx, Token *tk, int value)
{
	DEBUG_ASSERT(tk->tt == TT_NAME);
	if(knh_bytes_rindex(knh_Token_tobytes(tk), '.') == -1) {
		return tk;
	}
	if(knh_Token_isCMETHODN(tk) && !knh_Token_isNextParenthesis(tk)) {
		return tk;
	}
	Stmt* stmt = new_Stmt(ctx, 0, STT_CALL);
	knh_Stmt_add_name__first(ctx, stmt, tk, knh_Token_tobytes(tk), value);
	return stmt;
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__name(Ctx *ctx, Token *tk, int value)
{
	DEBUG_ASSERT(tk->tt == TT_NAME);
	if(knh_bytes_rindex(knh_Token_tobytes(tk), '.') == -1) {
		Stmt *stmt = new_Stmt(ctx, 0, STT_CALL);
		knh_Stmt_terms_add(ctx, stmt, tk);
		knh_Stmt_terms_add(ctx, stmt, new_Token__this(ctx, tk));
		return stmt;
	}
	Stmt* stmt = new_Stmt(ctx, 0, STT_CALL);
	knh_Stmt_add_name__first(ctx, stmt, tk, knh_Token_tobytes(tk), value);
	return stmt;
}

/* ------------------------------------------------------------------------ */
/* [name] */

Token *new_Token__funcname(Ctx *ctx, Token *tk, knh_bytes_t name, knh_bool_t isfunc, int value)
{
	char buf[256], *p = buf;
	knh_int_t i, c = 0;
	if(!isfunc) {
		if(value == KNH_STT_LVALUE) {
			buf[0] = 's';	
		}
		else {
			buf[0] = 'g';
		}
		buf[1] = 'e'; buf[2] = 't';
		c = 1;
		p = buf + 3;
	}
	for(i = 0; i < name.len; i++) {
		if(name.buf[i] == '_') {
			c = 1;
			continue;
		}
		if(c == 1) {
			*p = toupper(name.buf[i]);
			c = 0;
		}else {
			*p = name.buf[i];
		}
		p++;
	}
	*p = 0;
	return new_Token__text(ctx, tk, B(buf));
}

/* ------------------------------------------------------------------------ */

void knh_Stmt_add_name__first(Ctx *ctx, Stmt *b, Token *tk, knh_bytes_t name, int value)
{
	DEBUG_ASSERT(tk->tt == TT_NAME);
	DEBUG_ASSERT(b->size == 0);

	knh_bool_t isfunc = (knh_Token_isNextParenthesis(tk)) ? 1 : 0; 
	knh_index_t idx = knh_bytes_rindex(name, '.');

	if(idx == -1) {
		knh_Stmt_terms_add(ctx, b, tk);
		if(knh_Token_isNextParenthesis(tk)) {
			TODO(); /* YOU MUST CHECK */
			DEBUG_ASSERT(ctx == NULL);
			knh_Stmt_terms_add(ctx, b, new_Token__text(ctx, tk, STEXT("_")));
		}
		return;
	}

	L_NAMEDIV:;
	knh_bytes_t fname = knh_bytes_first(name, idx);
	knh_bytes_t lname = knh_bytes_last(name,  idx+1);

	Token *tkfunc = new_Token__funcname(ctx, tk, lname, isfunc, value);
	knh_Stmt_terms_add(ctx, b, tkfunc);

	//DEBUG("**1 idx=%d, len=%d", (int)idx, fn.len);
	idx = knh_bytes_rindex(fname, '.');
	if(idx == -1 || knh_bytes_isCONSTN(fname) || knh_bytes_isCLASSN(fname)) {
		knh_Stmt_terms_add(ctx, b, new_Token__text(ctx, tk, fname));
		return;
	}
	isfunc = 0; value = KNH_STT_RVALUE;
	name = fname;
	Stmt *stmt = new_Stmt(ctx, 0, STT_CALL);
	knh_Stmt_terms_add(ctx, b, stmt);
	b = stmt;	
	goto L_NAMEDIV;
}

/* ------------------------------------------------------------------------ */

void knh_Stmt_swap01(Ctx *ctx, Stmt *b)
{
	DEBUG_ASSERT(b->size > 1);
	Term *temp = b->terms[0];
	b->terms[0] = b->terms[1];
	b->terms[1] = temp;
}

/* ------------------------------------------------------------------------ */

Stmt* knh_Stmt_add_name__second(Ctx *ctx, Stmt *b, Token *tk, int value)
{
	DEBUG_ASSERT(tk->tt == TT_NAME);
	DEBUG_ASSERT(b->size == 1);
	
	Stmt *stmt = b;
	knh_bytes_t name = knh_Token_tobytes(tk);
	knh_index_t idx = knh_bytes_index(name, '.');

	while(idx > 0) {
		knh_Stmt_terms_add(ctx, stmt, new_Token__funcname(ctx, tk, knh_bytes_first(name, idx), 0, KNH_STT_RVALUE));
		knh_Stmt_swap01(ctx, stmt);
		stmt = new_Stmt__stmt(ctx, stmt);
		name = knh_bytes_last(name, idx+1);
		idx = knh_bytes_index(name, '.');
	}
	knh_Stmt_terms_add(ctx, stmt, new_Token__funcname(ctx, tk, name, knh_Token_isNextParenthesis(tk), value));
	knh_Stmt_swap01(ctx, stmt);
	return stmt;
}

/* ======================================================================== */
/* [list] */

Term *new_Term__Tuple(Ctx *ctx, Token *tk)
{
	Token **ts = knh_Token_ts(tk);
	knh_int_t e = knh_Token_tokens_size(tk);
	if(e == 0) {
		return new_Token__RAW(ctx, 0, tk, KNH_NULL);
	}
	knh_int_t c = knh_tokens_count(ts, 0, e, TT_COMMA);
	if(c == 0) {
		return new_Term__expr(ctx, ts, 0, e, KNH_STT_RVALUE);
	}
	Stmt *stmt = new_Stmt(ctx, 0, STT_NEW);
	Token *tknew = new_Token__text(ctx, tk, STEXT("new::init"));
	knh_Stmt_terms_add(ctx, stmt, tknew);
	knh_Stmt_terms_add(ctx, stmt, tknew /*new_Token__text(ctx, tk, STEXT("Tuple"))*/);
	knh_Stmt_add_exprs(ctx, stmt, ts, 0, e);
	c = stmt->size - 2;
	if(c >= CLASS_Prototype) {
		c = CLASS_Prototype - 1;
		stmt->size = c + 2;
	}
	char buf[16];
	knh_snprintf(buf, sizeof(buf), "Tuple%d", (int)c);
	KNH_SETv(ctx, stmt->terms[1], new_Token__text(ctx, tk, B(buf)));
	return stmt;
}

/* ------------------------------------------------------------------------ */


Stmt *new_Stmt__Array(Ctx *ctx, Token *tk)
{
	Stmt *stmt = new_Stmt(ctx, 0, STT_NEW);
	knh_Stmt_terms_add(ctx, stmt, new_Token__text(ctx, tk, STEXT("new::init")));
	knh_Stmt_terms_add(ctx, stmt, new_Token__text(ctx, tk, STEXT("Array")));
	knh_Stmt_add_exprs(ctx, stmt, knh_Token_ts(tk), 0, knh_Token_tokens_size(tk));
	return stmt;
}

/* ======================================================================== */
/* [HashMap] */


Stmt *new_Stmt__DictMap(Ctx *ctx, Token *tk)
{
	Stmt *stmt = new_Stmt(ctx, 0, STT_NEW);
	knh_Stmt_terms_add(ctx, stmt, new_Token__text(ctx, tk, STEXT("new::init")));
	knh_Stmt_terms_add(ctx, stmt, new_Token__text(ctx, tk, STEXT("DictMap")));
	knh_Stmt_add_pairs(ctx, stmt, knh_Token_ts(tk), 0, knh_Token_tokens_size(tk));
	return stmt;
}

/* ------------------------------------------------------------------------ */

void knh_Stmt_add_pairs(Ctx *ctx, Stmt *b, Token **ts, knh_int_t s, knh_int_t e)
{
	knh_int_t i;
	for(i = s; i < e; i++) {
		if(ts[i]->tt == TT_COMMA || ts[i]->tt == TT_SEMICOLON) {
			knh_Stmt_add_pair(ctx, b, ts, s, i);
			s = i + 1;
		}
	}
	if(s != e) {
		knh_Stmt_add_pair(ctx, b, ts, s, e);
	}
}

/* ------------------------------------------------------------------------ */

void knh_Stmt_add_pair(Ctx *ctx, Stmt *stmt, Token **ts, knh_int_t s, knh_int_t e)
{
	if(s == e) return;
	if(s+1 == e) {
		MC_EPRINT(ctx, ts[s], MC_WARNING, "empty");
		return;
	}	
	if(ts[s]->tt == TT_LABEL) {
		ts[s]->tt = TT_RAW;
		knh_Stmt_terms_add(ctx, stmt, ts[s]);
		knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, s+1, e, KNH_STT_RVALUE));
		return;
	}
	if(s+2 < e || ts[s+1]->tt != TT_COLON) {
		knh_Stmt_terms_add(ctx, stmt, new_Term__value(ctx, ts[s], KNH_STT_RVALUE));
		knh_Stmt_terms_add(ctx, stmt, new_Term__expr(ctx, ts, s+2, e, KNH_STT_RVALUE));
		return ;
	}
	MC_EPRINT(ctx, ts[s], MC_WARNING, "there is no name");
}

/* ------------------------------------------------------------------------ */

Stmt* new_Stmt__newClass(Ctx *ctx, Token *tk, Token *brc)
{
	Stmt *stmt = new_Stmt(ctx, 0, STT_MAP);
	knh_Stmt_terms_add(ctx, stmt, tk);
	knh_Stmt_terms_add(ctx, stmt, new_Stmt__DictMap(ctx, brc));
	return stmt;
}

/* ======================================================================== */
/* [PROPN] */

Term *new_Term__PROPN(Ctx *ctx, Token *tk, int value)
{
	if(value == KNH_STT_RVALUE && knh_Token_isURN(tk)) {
		tk->tt = TT_URN;
		KNH_SETv(ctx, tk->data, new_String__UPROPN(ctx, knh_String_tobytes(tk->data)));
		return tk;
	}
	Stmt *stmt = new_Stmt(ctx, 0, STT_CALL);
	if(value == KNH_STT_LVALUE) {
		knh_Stmt_terms_add(ctx, stmt, new_Token__text(ctx, tk, STEXT("setProperty")));
	}else{
		knh_Stmt_terms_add(ctx, stmt, new_Token__text(ctx, tk, STEXT("getProperty")));
	}
	knh_Stmt_terms_add(ctx, stmt, new_Token__text(ctx, tk, STEXT("Context")));
	knh_Token_toRAW(tk);
	knh_Stmt_terms_add(ctx, stmt, tk);
	return stmt;
}

/* ======================================================================== */
/* [print] */

void knh_Stmt_add_printname(Ctx *ctx, Stmt *b, Token **ts, int s, int e)
{
	//DEBUG("s=%d, e=%d", s, e);
	if(s + 1 == e) {
		knh_buffer_t cb = knh_Context_buffer(ctx);
		if(b->size > 2) {
			knh_putc(ctx, cb.w, ',');
			knh_putc(ctx, cb.w, ' ');
		}
		int pn = 0;
		switch(ts[s]->tt) {
		case TT_NAME:
			knh_write(ctx, cb.w, knh_Token_tobytes(ts[s]));
			pn = 1;
			break;
		case TT_PROPN:
			knh_putc(ctx, cb.w, '$');
			knh_write(ctx, cb.w, knh_Token_tobytes(ts[s]));
			pn = 1;
			break;
		}
		if(pn == 1) {
//			knh_putc(ctx, cb.w, ' ');
			knh_putc(ctx, cb.w, '=');
			knh_Stmt_terms_add(ctx, b, new_Token__RAW(ctx, 0, ts[s], new_String__buffer(ctx, CLASS_String, cb)));					
		}
		else {
			knh_buffer_clear(cb);
		}
	}
	;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
