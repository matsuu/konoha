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

#undef DEBUG3
#define DEBUG3(fmt, ...)

/* ======================================================================== */
/* [data] */

#define TKSTACK_MAXSIZ 32
#define knh_Token_add_whitespace  knh_Token_add_space

/* ======================================================================== */
/* [util] */

#ifndef KMSG_EINDENT
#define KMSG_EINDENT KMSG_ESYNTAX
#endif

#ifndef KMSG_UTOKEN
#define KMSG_UTOKEN KMSG_ESYNTAX
#endif

#ifndef KMSG_WCHAR
#define KMSG_WCHAR KMSG_ESYNTAX
#endif

#ifndef KMSG_IGBLOCK
#define KMSG_IGBLOCK KMSG_ESYNTAX
#endif

/* ======================================================================== */
/* [util] */

static
void knh_InputStream_perror(Ctx *ctx, InputStream *in, int pe, char *msg)
{
	knh_perror(ctx, DP(in)->fileid, DP(in)->line, pe, msg);
}

/* ======================================================================== */
/* [NAME] */

String *new_String__NAME(Ctx *ctx, knh_bytes_t tname)
{
	knh_index_t idx = knh_DictMap_index__b((ctx)->tsymbolDictMap, tname);
	if(idx == -1) {
		String *s = new_String(ctx, tname, NULL);
		knh_DictMap_set(ctx, (ctx)->tsymbolDictMap, s, UP(s));
		return s;
	}
	else {
		return knh_DictMap_keyAt((ctx)->tsymbolDictMap, idx);
	}
}

/* ------------------------------------------------------------------------ */

#ifndef KONOHA_NAME_BUFSIZ
#define KONOHA_NAME_BUFSIZ  256
#endif

#ifndef KONOHA_NAME_MAXSIZ
#define KONOHA_NAME_MAXSIZ  80
#endif

Token *new_Token__NAME(Ctx *ctx, knh_flag_t flag, InputStream *in, knh_bytes_t t)
{
	char name[KONOHA_NAME_BUFSIZ], *p = name;
	knh_token_t tt = TT_NAME;

	size_t i = 0;
	if(t.buf[0] == '.' && islower(t.buf[1])) {   /* .name   => name */
		flag |= KNH_FLAG_TKF_TOPDOT;
		t.buf++; t.len--;
	}
	if(isupper(t.buf[0])) { /* CLASS */
		tt = TT_TYPEN;
		goto CLASS_PART;
	}
	else if(islower(t.buf[0]) || t.buf[0] == '_'){
		tt = TT_NAME;
		goto NAME_PART;
	}
	else {
		knh_InputStream_perror(ctx, in, KMSG_UTOKEN, (char*)t.buf);
		return new_Token(ctx, flag, DP(in)->fileid, DP(in)->line, TT_ERR);
	}

	CLASS_PART:
	{
		int has_lower = 0;
		for(; i < t.len; i++) {
			if(p - name >= KONOHA_NAME_MAXSIZ) {
				goto WLENGTH_PART;
			}
			if(t.buf[i] == '.') {
				if(isupper(t.buf[i+1])) { /* Class.CONST */
					tt = TT_CONSTN;
					*p = '.'; p++; i++;
					goto CONSTN_PART;
				}
				else if(islower(t.buf[i+1])){ /* Class.name */
					tt = TT_CMETHODN;
					*p = '.'; p++; i++;
					goto NAME_PART;
				}
			}
			if(t.buf[i] == '_') {
				if(!has_lower) { /* CLASS_NAME */
					tt = TT_CONSTN;
					*p = t.buf[i]; p++; i++;
					goto CONSTN_PART;
				}
				continue; /* ignoring '_' */
			}
			if(!isalnum(t.buf[i]) && t.buf[i] != ':') {
				char cb[2] = {t.buf[i], 0};
				knh_InputStream_perror(ctx, in, KMSG_WCHAR, cb);
				goto TOKEN_PART;
			}
			if(islower(t.buf[i])) has_lower = 1;
			*p = t.buf[i]; p++;
		}
		goto TOKEN_PART;
	}

	CONSTN_PART:
	{
		for(; i < t.len; i++) {
			if(p - name >= KONOHA_NAME_MAXSIZ) {
				goto WLENGTH_PART;
			}
			if(isupper(t.buf[i]) || isdigit(t.buf[i]) || t.buf[i] == '_') {
				*p = t.buf[i]; p++;
			}
			else if(t.buf[i] == '.' && islower(t.buf[i+1])) {
				tt = TT_NAME;
				*p = '.'; p++; i++;
				goto NAME_PART;
			}
			else {
				char cb[2] = {t.buf[i], 0};
				knh_InputStream_perror(ctx, in, KMSG_WCHAR, cb);
				goto TOKEN_PART;
			}
		}
		goto TOKEN_PART;
	}

	NAME_PART:
	{
		int upper = 0;
		for(; t.buf[i] == '_'; i++) {
			if(p - name >= KONOHA_NAME_MAXSIZ) {
				goto WLENGTH_PART;
			}
			*p = t.buf[i]; p++;
		}

		for(; i < t.len; i++) {
			if(p - name >= KONOHA_NAME_MAXSIZ) {
				goto WLENGTH_PART;
			}
			if(t.buf[i] == '_') {
				if(upper) {
					*p = '_'; p++;
					*p = '_'; p++;
				}
				upper = 1;
				continue;
			}
			if(!isalnum(t.buf[i]) && t.buf[i] != ':') {
				if(t.buf[i] == '.'/* && tt == TT_CMETHODN*/) {
					*p = '.'; p++;
					continue;
				}
				else {
					char cb[2] = {t.buf[i], 0};
					knh_InputStream_perror(ctx, in, KMSG_WCHAR, cb);
					goto TOKEN_PART;
				}
			}
			if(upper) {
				upper = 0;
				if(islower(t.buf[i])) {
					*p = t.buf[i] - ('a' - 'A'); p++;
				}
				else {
					*p = t.buf[i]; p++;
				}
			}
			else {
				*p = t.buf[i]; p++;
			}
		}
		goto TOKEN_PART;
	}


	WLENGTH_PART: {
		*p = 0;
		knh_InputStream_perror(ctx, in, KMSG_WLENGTH, (char*)t.buf);
		knh_perrata(ctx, DP(in)->fileid, DP(in)->line, (char*)t.buf, name);
	}

	TOKEN_PART: {
		*p = 0;
		if(tt == TT_NAME) {
			if(name[0] == 'v' && name[1] == 'o' && name[2] == 'i' && name[3] == 'd' && name[4] == 0) {
				tt = TT_TYPEN;
			}
			if(name[0] == 'a' && name[1] == 'n' && name[2] == 'y' && name[3] == 0) {
				name[0] = 'A';
				tt = TT_TYPEN;
			}
		}
		Token *o = new_Token(ctx, flag, DP(in)->fileid, DP(in)->line, tt);
//		DBG2_(
//		if(!knh_bytes_equals(t, B(name))) {
//			DBG2_P("(%s) '%s' ==> '%s'", knh_token_tochar(tt), (char*)t.buf, name);
//		});
		KNH_SETv(ctx, DP(o)->data, new_String__NAME(ctx, B(name)));
		return o;
	}
}

/* ======================================================================== */
/* [parse] */

static
knh_bool_t knh_Bytes_isTripleQuote(Bytes *o, knh_intptr_t ch)
{
	if(o->size > 2 &&
		o->buf[o->size-1] == ch &&
		o->buf[o->size-2] == ch &&
		o->buf[o->size-3] == ch) return 1;
	return 0;
}

/* ------------------------------------------------------------------------ */
/* [Token] */

static
Token *new_Token__buffer(Ctx *ctx, knh_token_t tt, knh_cwb_t tbuf, InputStream *in)
{
	Token *o = new_Token(ctx, 0, DP(in)->fileid, DP(in)->line, tt);
	knh_bytes_t t = knh_cwb_tobytes(tbuf);
	//DBG2_P("tt=%s, '%s', len=%d", knh_token_tochar(tt), t.buf, t.len);

	if(tt == TT_METAN && islower(t.buf[0])) {
		t.buf[0] = toupper(t.buf[0]);
	}

	if(t.len == 0) {
		KNH_SETv(ctx, DP(o)->data, TS_EMPTY);
	}
	else {
		if(IS_NULL(DP(in)->bconv)) {
			KNH_SETv(ctx, DP(o)->data, new_String(ctx, t, NULL));
		}
		else {
			KNH_SETv(ctx, DP(o)->data, new_String__bconv(ctx, t, DP(in)->bconv));
		}
		knh_cwb_clear(tbuf);
	}
	return o;
}



/* ------------------------------------------------------------------------ */
#define knh_token_isNested(tt)  (tt == TT_BRACE || tt == TT_PARENTHESIS || tt == TT_BRANCET)

static
Token *knh_Token_tokens_lastNULL(Token *o)
{
	KNH_ASSERT(knh_token_isNested(SP(o)->tt));
	if(IS_bArray(DP(o)->list)) {
		Token *tk = (Token*)knh_Array_last(DP(o)->list);
		KNH_ASSERT(IS_Token(tk));
		return tk;
	}
	else if(IS_Token(DP(o)->token)) {
		return DP(o)->token;
	}
	else {
		return NULL;
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_Token_padd(Ctx *ctx, Token *ptk, int *BOL, Token *tk)
{
	if(*BOL == 1) {
		knh_Token_setBOL(tk, 1); *BOL = 0;
	}

	Token *tkp = knh_Token_tokens_lastNULL(ptk);
	if(tkp != NULL) {
		DP(tkp)->tt_next = SP(tk)->tt;
		/* (1+-1) */
		if(SP(tk)->tt == TT_SUB && knh_token_tomethodn(SP(tkp)->tt) != METHODN_NONAME) {
			SP(tk)->tt = TT_NEG;
		}
	}
	else {
		if(SP(tk)->tt == TT_SUB) { /* (- 1) */
			SP(tk)->tt = TT_NEG;
		}
	}

	if(SP(tk)->tt == TT_SEMICOLON || knh_token_isEndOfStmt(SP(tk)->tt)) {
		knh_Token_setBOL(tk, 1);
	}

	knh_Token_tokens_add(ctx, ptk, tk);
}

/* ------------------------------------------------------------------------ */

static
void knh_Token_add_space(Ctx *ctx, Token *tk, int *BOL, knh_cwb_t tbuf, InputStream *in)
{
	knh_bytes_t t = knh_cwb_tobytes(tbuf);
	if(t.len == 0) return;

	Token *tkp = knh_Token_tokens_lastNULL(tk);
	if(tkp != NULL && SP(tkp)->tt == TT_TYPEN) {
		if(t.buf[0] == '.' && t.buf[1] == '.' && t.buf[2] == '\0') {
			knh_Token_setIteratorType(tkp, 1);
			knh_Token_setNotNullType(tkp, 1);
			*BOL = 0; goto L_CLEAR;
		}
		if(t.buf[0] == '!' && t.buf[1] == '!' && t.buf[2] == '\0') {
			knh_Token_setExceptionType(tkp, 1);
			*BOL = 0; goto L_CLEAR;
		}
		if(t.buf[0] == '!' && t.buf[2] == '\0') {
			if(knh_Token_isNotNullType(tkp)) {
				knh_Token_setNotNullType(tkp, 0);
				knh_Token_setExceptionType(tkp, 1);
			}
			else {
				knh_Token_setNotNullType(tkp, 1);
			}
			*BOL = 0; goto L_CLEAR;
		}
		if(t.buf[0] == '?' && t.buf[2] == '\0') {
			knh_Token_setPluralType(tkp, 1);
			*BOL = 0; goto L_CLEAR;
		}
	}
	knh_Token_padd(ctx, tk, BOL, new_Token__parse(ctx, 0, in, t));

	L_CLEAR:;
	knh_cwb_clear(tbuf);
}

/* ------------------------------------------------------------------------ */

static
void knh_Token_addTypeParam(Ctx *ctx, Token *tkt, Array *a, size_t s)
{
	size_t i;
	for(i = s; i < knh_Array_size(a); i++) {
		Token *tk = (Token*)knh_Array_n(a, i);
		if(SP(tk)->tt == TT_GT) goto L_PASS2;
	}
	return ;

	L_PASS2:;
	knh_cwb_t cwb = new_cwb(ctx);
	knh_write(ctx, cwb.w, knh_Token_tobytes(ctx, tkt));
	knh_putc(ctx, cwb.w, '<');
	knh_Array_remove(ctx, a, s);
	i = s;
	while(1) {
		Token *tk = (Token*)knh_Array_n(a, i);
		if(SP(tk)->tt == TT_GT) {
			if(DP(tk)->tt_next == TT_NOT) {
				tk = (Token*)knh_Array_n(a, i+1);
				DP(tkt)->tt_next = DP(tk)->tt_next;
				knh_Token_setNotNullType(tkt, 1);
				knh_Array_remove(ctx, a, i);
				knh_Array_remove(ctx, a, i);
			}
			else {
				DP(tkt)->tt_next = DP(tk)->tt_next;
				knh_Array_remove(ctx, a, i);
			}
			break;
		}
		knh_write(ctx, cwb.w, knh_Token_tobytes(ctx, tk));
		knh_Array_remove(ctx, a, i);
	}
	knh_putc(ctx, cwb.w, '>');
	KNH_SETv(ctx, DP(tkt)->data, new_String__cwb(ctx, cwb));
}

/* ------------------------------------------------------------------------ */

static
void knh_write_tktype(Ctx *ctx, OutputStream *w, Token *tk)
{
	if(knh_Token_isExceptionType(tk)) {
		knh_write(ctx, w, STEXT("Exception"));
	}
	else {
		knh_write(ctx, w, knh_Token_tobytes(ctx, tk));
	}
	if(knh_Token_isIteratorType(tk)) {
		knh_write(ctx, w, STEXT(".."));
		return;
	}
	if(knh_Token_isArrayType(tk)) {
		knh_write(ctx, w, STEXT("[]"));
	}
	if(knh_Token_isNotNullType(tk)) {
		knh_putc(ctx, w, '!');
	}
}

/* ------------------------------------------------------------------------ */

static
int knh_Token_toClosureType(Ctx *ctx, Token *tkt, Token *tkp)
{
	knh_tokens_t tc ;
	knh_Token_tc(tkp, &tc);
	knh_cwb_t cwb = new_cwb(ctx);
	knh_write_tktype(ctx, cwb.w, tkt);
	knh_putc(ctx, cwb.w, '(');
	int i, c = 0;
	for(i = 0; i < tc.e; i++) {
		if(SP(tc.ts[i])->tt == TT_COMMA) continue;
		if(SP(tc.ts[i])->tt != TT_TYPEN) {
			knh_cwb_clear(cwb);
			return 0;
		}
		if(c > 0) knh_putc(ctx, cwb.w, ',');
		knh_write_tktype(ctx, cwb.w, tc.ts[i]);
		c++;
	}
	if(c > 3) {
		KNH_SETv(ctx, DP(tkt)->data, ctx->share->ClassTable[CLASS_Closure].sname);
		knh_cwb_clear(cwb);
		return 1;
	}
	if(tc.e == 0) {
		knh_cwb_clear(cwb);
		return 0;
		//knh_write(ctx, cwb.w, STEXT("void"));
	}
	knh_putc(ctx, cwb.w, ')');
	KNH_SETv(ctx, DP(tkt)->data, new_String__cwb(ctx, cwb));
	//DBG2_P("closure='%s'", knh_String_tochar(DP(tkt)->text));
	return 1;
}

/* ------------------------------------------------------------------------ */

static
void knh_Token_join(Ctx *ctx, Token *o)
{
	Array *a = (Array*)DP(o)->data;
	if(IS_Array(a)) {
		size_t i;
		for(i = 0; i < knh_Array_size(a) - 1; i++) {
			Token *tk = (Token*)knh_Array_n(a, i);
			if(SP(tk)->tt == TT_TYPEN) {
				Token *tkn = (Token*)knh_Array_n(a, i+1);
				if(SP(tkn)->tt == TT_LT) {  /* T<T> */
					knh_Token_addTypeParam(ctx, tk, a, i+1);
				}
				if(SP(tkn)->tt == TT_PARENTHESIS) {
					if(i > 0 && knh_Token_isNEW(ctx, (Token*)knh_Array_n(a, i-1))) {
						/* new Person() is not closure */
					}
					else if(knh_Token_toClosureType(ctx, tk, tkn)) {
						knh_Array_remove(ctx, a, i+1);
					}
				}
				if(SP(tkn)->tt == TT_BRANCET && IS_NULL(DP(tkn)->data)) {
					knh_Token_setArrayType(tk, 1);
					DP(tk)->tt_next = DP(tkn)->tt_next;
					if(DP(tkn)->tt_next == TT_NOT) {
						knh_Token_setNotNullType(tk, 1);
						DP(tk)->tt_next = DP((Token*)knh_Array_n(a, i+2))->tt_next;
						knh_Array_remove(ctx, a, i+1);
						knh_Array_remove(ctx, a, i+1);
					}
					else {
						knh_Array_remove(ctx, a, i+1);
					}
				}
			}
			if(SP(tk)->tt == TT_NAME && ISB(knh_Token_tobytes(ctx, tk), "byte")) {
				Token *tkn = (Token*)knh_Array_n(a, i+1);
				if(SP(tkn)->tt == TT_BRANCET && IS_NULL(DP(tkn)->data)) {
					SP(tk)->tt = TT_TYPEN;
					KNH_SETv(ctx, DP(tk)->data, ctx->share->ClassTable[CLASS_Bytes].sname);
					if(i>0) {
						Token *tkp = (Token*)knh_Array_n(a, i-1);
						DP(tkp)->tt_next = TT_TYPEN;
					}
					DP(tk)->tt_next = DP(tkn)->tt_next;
					if(DP(tkn)->tt_next == TT_NOT) {
						knh_Token_setNotNullType(tk, 1);
						DP(tk)->tt_next = DP((Token*)knh_Array_n(a, i+2))->tt_next;
						knh_Array_remove(ctx, a, i+1);
						knh_Array_remove(ctx, a, i+1);
					}
					else {
						knh_Array_remove(ctx, a, i+1);
					}
				}
			}
		}
	}
}

/* ------------------------------------------------------------------------ */

knh_token_t knh_char_totoken(int ch)
{
	switch(ch) {
		case '{': case '}': return TT_BRACE;
		case '(': case ')': return TT_PARENTHESIS;
		case '[': case ']': return TT_BRANCET;
		case '@': return TT_METAN;
		case '$': return TT_PROPN;
		case '%': return TT_MT;
		case ';': return TT_SEMICOLON;
		case ',': return TT_COMMA;
		case '"': return TT_STR;
		case '\'': return TT_TSTR;
		case '`': return TT_EVAL;
	}
	KNH_ASSERT(ch == -1);
	return TT_ERR;
}

/* ------------------------------------------------------------------------ */

static
int knh_InputStream_getc__urlencoded(Ctx *ctx, InputStream *in)
{
	int num, ch = knh_InputStream_getc(ctx, in);
	if(isdigit(ch)) {
		num = (ch - '0') * 16;
	}else if('a' <= ch && ch <= 'f') {
		num = (ch - 'a' + 10) * 16;
	}else if('A' <= ch && ch <= 'F') {
		num = (ch - 'A' + 10) * 16;
	}else {
		if(ch == '\n') return EOF;
		return ch;
	}
	ch = knh_InputStream_getc(ctx, in);
	if(isdigit(ch)) {
		num += (ch - '0');
	}else if('a' <= ch && ch <= 'f') {
		num += (ch - 'a' + 10);
	}else if('A' <= ch && ch <= 'F') {
		num += (ch - 'A' + 10);
	}else {
		if(ch == '\n') return EOF;
		return ch;
	}
	return num;
}


/* ------------------------------------------------------------------------ */

static
void knh_InputStream_skipBLOCK(Ctx *ctx, InputStream *in, int prev, Token *tk)
{
	int ch, endch = '}';
	if(tk == NULL) return;
	if(SP(tk)->tt == TT_BRACE) endch = ']';
	SP(tk)->tt = TT_ERR;
	KNH_SETv(ctx, DP(tk)->data, KNH_NULL);

	MAIN_PART:
	while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
		if(prev == '\n' && ch == endch) {
			char buf[40];
			knh_snprintf(buf, sizeof(buf), "lines: %d..%d", (int)SP(tk)->line, (int)DP(in)->line);
			knh_InputStream_perror(ctx, in, KMSG_IGBLOCK, buf);
			return ;
		}
		if(prev == '/' && ch == '*') {
			prev = 0;
			goto BLOCK_COMMENT;
		}
		prev = ch;
	}
	return;

	BLOCK_COMMENT:
	{
		int nest = 1;
		while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
			if(prev == '*' && ch == '/') {
				nest--;
				if(nest == 0) goto MAIN_PART;
			}else if(prev == '/' && ch == '*') {
				nest++;
			}
			prev = ch;
		}
	}
	return;
}

/* ======================================================================== */
/* [parse] */

void knh_Token_parse(Ctx *ctx, Token *tk, InputStream *in)
{
	knh_cwb_t tbuf = new_cwb(ctx);
	int ch, prev=0, indent = 0, pindent, BOL = 0;
	Token *tks[TKSTACK_MAXSIZ] = {NULL};
	Token *blocktk = NULL;
	tks[0] = tk;
	int tkl = 0;

	INDENT_PART:;
	pindent = indent;
	indent = 0;
	while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
		if(ch == '\t') {
			indent+=3;
		}
		else if(ch == ' ') {
			indent++;
		}
		else if(ch == '/' || ch == '\n' || ch == '\r' || ch == EOF) {
			goto MAIN_PART_INLOOP;
		}
		else {
			break;
		}
	}
	BOL = 0;
	if(pindent == indent && SP(tks[tkl])->tt == TT_BRACE) {
		BOL = 1;
	}
	goto MAIN_PART_INLOOP;

	MAIN_PART:;
	while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
		MAIN_PART_INLOOP:;

		switch(ch) {
		case '\n':
			knh_Token_add_whitespace(ctx, tks[tkl], &BOL, tbuf, in);
		goto INDENT_PART;

		case '\t': case ' ': case '\v': case '\r':
			knh_Token_add_whitespace(ctx, tks[tkl], &BOL, tbuf, in);
			prev = ch;

		goto MAIN_PART;

		case '{': case '[': case '(':
			knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
			if(tkl < (TKSTACK_MAXSIZ - 1)) {
				Token *intk = new_Token(ctx, 0, DP(in)->fileid, DP(in)->line, knh_char_totoken(ch));
				knh_Token_padd(ctx, tks[tkl], &BOL, intk);
				tkl++;
				tks[tkl] = intk;
				if(blocktk == NULL && ch != '(') {
					blocktk = intk;
				}
			}
			else {
				knh_InputStream_perror(ctx, in, KMSG_ESYNTAX, "TOO MANY NESTED");
				knh_InputStream_skipBLOCK(ctx, in, prev, blocktk);
				blocktk = NULL;
			}
			goto MAIN_PART;

		case '}':
			knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
			if(tkl > 0 && SP(tks[tkl])->tt == TT_BRACE) {
				knh_Token_join(ctx, tks[tkl]);
				tkl--;
			}
			else {
				knh_InputStream_perror(ctx, in, KMSG_EMISMATCH, " ...}");
				knh_InputStream_skipBLOCK(ctx, in, prev, blocktk);
				blocktk = NULL;
			}
			goto MAIN_PART;

		case ')':
			knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
			if(tkl > 0 && SP(tks[tkl])->tt == TT_PARENTHESIS) {
				knh_Token_join(ctx, tks[tkl]);
				tkl--;
			}
			else {
				knh_InputStream_perror(ctx, in, KMSG_EMISMATCH, " ...)");
				knh_InputStream_skipBLOCK(ctx, in, prev, blocktk);
				blocktk = NULL;
			}
			goto MAIN_PART;

		case ']':
			knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
			if(tkl > 0 && SP(tks[tkl])->tt == TT_BRANCET) {
				knh_Token_join(ctx, tks[tkl]);
				tkl--;
			}
			else {
				knh_InputStream_perror(ctx, in, KMSG_EMISMATCH, " ...]");
				knh_InputStream_skipBLOCK(ctx, in, prev, blocktk);
				blocktk = NULL;
			}
			goto MAIN_PART;

		case '"': case '\'': case '`' :
			knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
			prev = ch;
			goto QUOTED_PART;

		case ';':
			knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
			knh_Token_padd(ctx, tks[tkl], &BOL, new_Token(ctx, 0, DP(in)->fileid, DP(in)->line, knh_char_totoken(ch)));
			break;

		case ',':
			knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
			knh_Token_padd(ctx, tks[tkl], &BOL, new_Token(ctx, 0, DP(in)->fileid, DP(in)->line, knh_char_totoken(ch)));
			break;

		case '$':
			knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
			prev = ch;
			goto QNAME_PART;

		case '@':
			knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
			ch = knh_InputStream_getc(ctx, in);
			if(ch == '"' || ch == '\'' || ch == '`') {
				prev = ch;
				goto RAWSTR_PART;
			}
			prev = '@';
			knh_Bytes_putc(ctx, tbuf.ba, ch);
			goto QNAME_PART;

		case '%':
			knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
			ch = knh_InputStream_getc(ctx, in);
			if(isalnum(ch)) {
				prev = '%';
				knh_Bytes_putc(ctx, tbuf.ba, ch);
				goto QNAME_PART;
			}
			else if(ch == '%') {
				knh_Bytes_putc(ctx, tbuf.ba, '%');
				knh_Bytes_putc(ctx, tbuf.ba, '%');
				knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
				break;
			}
			else {
				knh_Bytes_putc(ctx, tbuf.ba, '%');
				knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
				goto MAIN_PART_INLOOP;
			}

		case '+': case '-': case '*': case '=':
		case '&': case '|': case '<':
		case '>': case '^': case '!': case '~':
			knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
			knh_Bytes_putc(ctx, tbuf.ba, ch);
			prev = ch;
			goto OP_PART;

		case '?':
			if(!islower(prev)) {
				knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
				knh_Bytes_putc(ctx, tbuf.ba, ch);
				prev = ch;
				goto OP_PART;
			}
			else {
				knh_Bytes_putc(ctx, tbuf.ba, ch);
				knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
				break;
			}

		case '/':
			knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
			ch = knh_InputStream_getc(ctx, in);
			if(ch == '*') {
				goto BLOCK_COMMENT;
			}else if(ch == '/') {
				goto LINE_COMMENT;
			}
			knh_Bytes_putc(ctx, tbuf.ba, '/');
			prev = '/';
			goto OP_PART_INLOOP;

		case '#':
			knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
			goto LINE_COMMENT;

		case '.':
			ch = knh_InputStream_getc(ctx, in);
			if(ch == '.') { /* .. */
				knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
				knh_Bytes_putc(ctx, tbuf.ba, '.');
				knh_Bytes_putc(ctx, tbuf.ba, ch);
				prev = '.';
				goto OP_PART;
			}
			else if(ch == '*') {
				knh_Bytes_putc(ctx, tbuf.ba, '.');
				knh_Bytes_putc(ctx, tbuf.ba, '*');
				knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
				prev = ' ';
				break;
			}
			else { /* a.b */
				knh_Bytes_putc(ctx, tbuf.ba, '.');
				goto MAIN_PART_INLOOP;
			}
			break;

		case ':':
			ch = knh_InputStream_getc(ctx, in);
			if(knh_cwb_size(tbuf) == 0) {
				if(ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || ch == ';') {
					knh_Bytes_putc(ctx, tbuf.ba, ':');
					knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
					break;
				}
				knh_Bytes_putc(ctx, tbuf.ba, ':');
				goto URN_PART_INLOOP;
			}
			if(ch == '/') {
				knh_Bytes_putc(ctx, tbuf.ba, ':');
				knh_Bytes_putc(ctx, tbuf.ba, ch);
				goto URN_PART;
			}
			else if(ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || ch == ';') {
				knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, TT_LABEL, tbuf, in));
				//knh_Bytes_putc(ctx, tbuf.ba, ':');
				goto MAIN_PART_INLOOP;
			}
			else {
				knh_Bytes_putc(ctx, tbuf.ba, ':');
				knh_Bytes_putc(ctx, tbuf.ba, ch);
			}
			break;

		case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9': case '0':
			if(knh_cwb_size(tbuf) == 0) {
				knh_Bytes_putc(ctx, tbuf.ba, ch);
				goto NUM_PART;
			}
			else {
				knh_Bytes_putc(ctx, tbuf.ba, ch);
			}

		case EOF :
			break;

		default:
			if(ch > 127) {
				knh_InputStream_perror(ctx, in, KMSG_WASCII, NULL);
				ch = ' ';
			}
			knh_Bytes_putc(ctx, tbuf.ba, ch);
		} /* switch */
		prev = ch;
	}/* while */
	goto L_JOIN;

	NUM_PART:;  /* 0x0000 */
	{
		int unit = 0;
		//DEBUG3("=> NUM_PART");
		while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
			NUM_PART_INLOOP:;
			switch(ch) {
				case '0': case '1': case '2': case '3': case '4':
				case '5': case '6': case '7': case '8': case '9':
				case '_':
					knh_Bytes_putc(ctx, tbuf.ba, ch);
				break;
				case '.':
					ch = knh_InputStream_getc(ctx, in);
					if(ch == '.') {
						knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, TT_NUM, tbuf, in));
						knh_Bytes_putc(ctx, tbuf.ba, '.');
						goto OP_PART_INLOOP;
					}
					else {
						knh_Bytes_putc(ctx, tbuf.ba, '.');
						goto NUM_PART_INLOOP;
					}
				break;

				case '[':
					unit++;
					knh_Bytes_putc(ctx, tbuf.ba, ch);
				break;

				case ']':   /* 1.0[km/h] */
					unit--;
					if(unit < 0) {
						knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, TT_NUM, tbuf, in));
						goto MAIN_PART_INLOOP;
					}
					else if(unit == 0) {
						knh_Bytes_putc(ctx, tbuf.ba, ch);
						knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, TT_NUM, tbuf, in));
						goto MAIN_PART;
					}
				break;

				default:
					if(unit > 0 || isalnum(ch) || ch > 127) {  /* 1.0a */
						knh_Bytes_putc(ctx, tbuf.ba, ch);
					}
					else {
						knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, TT_NUM, tbuf, in));
						goto MAIN_PART_INLOOP;
					}
				/*break*/
			}
		}
		knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, TT_NUM, tbuf, in));
		//knh_InputStream_perror(ctx, in, KMSG_WEOF, NULL);
	}
	goto MAIN_PART_INLOOP; /* EOF */

	QNAME_PART:;
	KNH_ASSERT(prev == '@' || prev == '$' || prev == '%');
	{
		while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
			if(isalnum(ch) || ch == '_' || ch == ':' || ch == '.') {
				knh_Bytes_putc(ctx, tbuf.ba, ch);
				continue;
			}
			if(ch == '*' && prev == '$') {
				knh_Bytes_putc(ctx, tbuf.ba, ch);
				continue;
			}
			break;
		}
		knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, knh_char_totoken(prev), tbuf, in));
	}
	goto MAIN_PART_INLOOP; /* EOF */

	OP_PART:;
	{
		while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
			OP_PART_INLOOP:;
			knh_bytes_t top = knh_cwb_tobytes(tbuf);
			if(knh_bytes_istoken(top, ch)) {
				knh_Bytes_putc(ctx, tbuf.ba, ch);
			}
			else {
				knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
				goto MAIN_PART_INLOOP;
			}
		}
	}
	goto MAIN_PART_INLOOP; /* EOF */

	URN_PART:;
	{
		DEBUG3("=> URN_PART");
		while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
			URN_PART_INLOOP:;
			switch(ch) {
				case '\n': case '\r':
				case ' ':  case '\t':
				case ';':
				case '(': case ')':
				case '{': case '}':
				case '[': case ']':
					knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, TT_URN, tbuf, in));
					goto MAIN_PART_INLOOP;
				case '%':
					ch = knh_InputStream_getc__urlencoded(ctx, in);
					if(ch == EOF) {
						ch = '\n';
						knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, TT_URN, tbuf, in));
						goto MAIN_PART_INLOOP;
					}
					knh_Bytes_putc(ctx, tbuf.ba, ch);
				default:
					knh_Bytes_putc(ctx, tbuf.ba, ch);
			}
		}
		knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, TT_URN, tbuf, in));
	}/*URN_PART*/
	goto L_EOF;

	RAWSTR_PART:;
	KNH_ASSERT(prev == '"' || prev == '\'' || prev == '`');
	{
		//knh_Bytes_putc(ctx, tbuf.ba, prev);
		while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
			if(ch == prev) {
				knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, knh_char_totoken(prev), tbuf, in));
				goto MAIN_PART;
			}
			knh_Bytes_putc(ctx, tbuf.ba, ch);
		}
		knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, knh_char_totoken(prev), tbuf, in));
	}/*RAWSTR_PART*/
	goto L_EOF;

	QUOTED_PART:;
	KNH_ASSERT(prev == '"' || prev == '\'' || prev == '`');
	{
		//knh_Bytes_putc(ctx, tbuf.ba, prev);
		ch = knh_InputStream_getc(ctx, in);
		if(ch == prev) {
			ch = knh_InputStream_getc(ctx, in);
			if(prev == ch) { /* triple quote */
				goto TRIPLE_QUOTED_PART;
			}else {
				knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, knh_char_totoken(prev), tbuf, in));
				goto MAIN_PART_INLOOP;
			}
		}
		else {
			goto QUOTED_PART_INLOOP;
		}
		while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
			QUOTED_PART_INLOOP:;
			if(ch == '\\') {
				ch = knh_InputStream_getc(ctx, in);
				switch(ch) {
				case 'n':
					knh_Bytes_putc(ctx, tbuf.ba, '\n');
					break;
				case 't':
					knh_Bytes_putc(ctx, tbuf.ba, '\t');
					break;
				case '"': case '\'': case '\\':
					knh_Bytes_putc(ctx, tbuf.ba, ch);
					break;
				case EOF:

				default:
					knh_Bytes_putc(ctx, tbuf.ba, '\\');
					knh_Bytes_putc(ctx, tbuf.ba, ch);
				}
				continue;
			}
			if(ch == '\n' || ch == '\r' || ch == EOF) {
				knh_InputStream_perror(ctx, in, KMSG_WCHAR, "\\n");
				knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, knh_char_totoken(prev), tbuf, in));
				goto MAIN_PART_INLOOP;
			}
			if(ch == prev) {
				knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, knh_char_totoken(prev), tbuf, in));
				goto MAIN_PART;
			}
			knh_Bytes_putc(ctx, tbuf.ba, ch);
		}
	}
	knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, knh_char_totoken(prev), tbuf, in));
	goto L_EOF;

	TRIPLE_QUOTED_PART:;
	KNH_ASSERT(prev == '"' || prev == '\'' || prev == '`');
	{
		while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
			if(ch == '\\') {
				ch = knh_InputStream_getc(ctx, in);
				switch(ch) {
				case 'n':
					knh_Bytes_putc(ctx, tbuf.ba, '\n');
					break;
				case 't':
					knh_Bytes_putc(ctx, tbuf.ba, '\t');
					break;
				case '"': case '\'': case '\\':
					knh_Bytes_putc(ctx, tbuf.ba, ch);
					break;
				case EOF:

				default:
					knh_Bytes_putc(ctx, tbuf.ba, '\\');
					knh_Bytes_putc(ctx, tbuf.ba, ch);
				}
				continue;
			}
			if(ch == '\n' || ch == '\r') {
				if(knh_Bytes_size(tbuf.ba) - tbuf.pos == 0) {
					DBG2_P("remove first linefeed at triplequote");
					continue;
				}
			}
			knh_Bytes_putc(ctx, tbuf.ba, ch);
			if(knh_Bytes_isTripleQuote(tbuf.ba, prev)) {
				knh_Bytes_unputc(tbuf.ba);
				knh_Bytes_unputc(tbuf.ba);
				knh_Bytes_unputc(tbuf.ba);
				knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, knh_char_totoken(prev), tbuf, in));
				goto MAIN_PART;
			}
		}
		knh_Token_padd(ctx, tks[tkl], &BOL, new_Token__buffer(ctx, knh_char_totoken(prev), tbuf, in));
	}
	goto L_EOF; /* EOF */

	/** COMMENT **/
	LINE_COMMENT:
	{
		while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
			if(ch == '\n') {
				goto MAIN_PART_INLOOP;
			}
		}
	}
	goto L_EOF; /* EOF */

	BLOCK_COMMENT:
	{
		int nest = 1;
		while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
			if(prev == '*' && ch == '/') {
				nest--;
				if(nest == 0) goto MAIN_PART;
			}else if(prev == '/' && ch == '*') {
				DBG2_P("nesting /* ")
				nest++;
			}
			prev = ch;
		}
	}
	goto L_EOF; /* EOF */

	L_EOF:;
	knh_InputStream_perror(ctx, in, KMSG_WEOF, NULL);

	L_JOIN:
	knh_Token_add_space(ctx, tks[tkl], &BOL, tbuf, in);
	while(tkl >= 0) {
		knh_Token_join(ctx, tks[tkl]);
		tkl--;
	}
	return ;
}


/* ======================================================================== */

#ifdef __cplusplus
}
#endif
