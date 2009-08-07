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

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif


/* ======================================================================== */
/* [constructors] */

Token* new_Token(Ctx *ctx, knh_flag_t flag, knh_uri_t uri, knh_sline_t line, knh_token_t tt)
{
	knh_Token_t *o = (Token*)new_Object_bcid(ctx, CLASS_Token, 0);
	SP(o)->flag =   flag;
	SP(o)->uri = uri;
	SP(o)->line =   line;
	SP(o)->tt   =   tt;
	return o;
}

/* ------------------------------------------------------------------------ */

void knh_Token_setFL(Token *o, Any *fln)
{
	if(IS_Token(fln)) {
		Token *tk = (Token*)fln;
		SP(o)->uri =  SP(tk)->uri;
		SP(o)->line =  SP(tk)->line;
	}
	else if(IS_Asm((Object*)fln)) {
		Asm *abr = (Asm*)fln;
		SP(o)->uri =  DP(abr)->uri;
		SP(o)->line =  DP(abr)->line;
	}
	else {
		Stmt *stmt = (Stmt*)fln;
		KNH_ASSERT(IS_Stmt(stmt));
		SP(o)->uri =  SP(stmt)->uri;
		SP(o)->line =  SP(stmt)->line;
	}
}

/* ------------------------------------------------------------------------ */

Token *new_TokenASIS(Ctx *ctx, Any *fln)
{
	knh_Token_t *o = (Token*)new_Object_bcid(ctx, CLASS_Token, 0);
	SP(o)->flag = 0;
	SP(o)->tt = TT_ASIS;
	knh_Token_setFL(o, fln);
	return o;
}

/* ------------------------------------------------------------------------ */

Token *new_TokenCID(Ctx *ctx, Any *fln, knh_class_t cid)
{
	knh_Token_t *o = (Token*)new_Object_bcid(ctx, CLASS_Token, 0);
	SP(o)->flag = 0;
	SP(o)->tt = TT_CID;
	knh_Token_setFL(o, fln);
	DP(o)->cid = cid;
	return o;
}

/* ------------------------------------------------------------------------ */

Token *new_TokenMN(Ctx *ctx, Any *fln, knh_methodn_t mn)
{
	knh_Token_t *o = (Token*)new_Object_bcid(ctx, CLASS_Token, 0);
	SP(o)->flag = 0;
	SP(o)->tt = TT_MN;
	knh_Token_setFL(o, fln);
	DP(o)->mn = mn;
	return o;
}

/* ------------------------------------------------------------------------ */

Token *new_TokenFN(Ctx *ctx, Any *fln, knh_fieldn_t fn)
{
	knh_Token_t *o = (Token*)new_Object_bcid(ctx, CLASS_Token, 0);
	SP(o)->flag = 0;
	SP(o)->tt = TT_FN;
	knh_Token_setFL(o, fln);
	DP(o)->fn = fn;
	return o;
}

/* ------------------------------------------------------------------------ */

Token *new_Token__S(Ctx *ctx, Any *fln, knh_token_t tt, String *t)
{
	knh_Token_t *o = (Token*)new_Object_bcid(ctx, CLASS_Token, 0);
	SP(o)->flag = 0;
	SP(o)->tt = tt;
	knh_Token_setFL(o, fln);
	KNH_SETv(ctx, DP(o)->data, t);
	return o;
}

/* ======================================================================== */
/* [Array] */

#define knh_token_isNested(tt)  (tt == TT_BRACE || tt == TT_PARENTHESIS || tt == TT_BRANCET)

/* ------------------------------------------------------------------------ */

knh_tkc_t* knh_Token_tc(Ctx *ctx, Token *o, knh_tkc_t *tc)
{
	DBG2_ASSERT(knh_token_isNested(SP(o)->tt));
	tc->meta = 0;
	tc->c = 0;
	if(IS_Array(DP(o)->data)) {
		tc->ts = (Token**)knh_Array_list((Array*)DP(o)->data);
		tc->e = knh_Array_size(((Array*)DP(o)->data));
	}
	else if(IS_NULL(DP(o)->data)) {
		tc->ts = NULL;
		tc->e = 0;
	}
	else{
		KNH_ASSERT(IS_Token(DP(o)->data));
		tc->ts = &(DP(o)->token);
		tc->e = 1;
	}
	return tc;
}

/* ------------------------------------------------------------------------ */

void knh_Token_tokens_add(Ctx *ctx, Token *o, Token *tk)
{
	KNH_ASSERT(knh_token_isNested(SP(o)->tt));
	KNH_ASSERT(IS_Token(tk));
	if(IS_NULL(DP(o)->data)) {
		KNH_SETv(ctx, DP(o)->data, tk);
		return ;
	}
	if(IS_Token(DP(o)->data)) {
		Array *a = new_Array(ctx, CLASS_Any, 2);
		knh_Array_add(ctx, a, DP(o)->data);
		KNH_SETv(ctx, DP(o)->data, a);
	}
	KNH_ASSERT(IS_Array(DP(o)->data));
	knh_Array_add(ctx, (Array*)DP(o)->data, UP(tk));
}

/* ------------------------------------------------------------------------ */

void knh_Token_tokens_empty(Ctx *ctx, Token *o)
{
	KNH_ASSERT(knh_token_isNested(SP(o)->tt));
	KNH_SETv(ctx, DP(o)->data, KNH_NULL);
}


/* ======================================================================== */
/* [movabletext] */

#define _sToken(o)  knh_Token_tochar(ctx, o)

char *knh_Token_tochar(Ctx *ctx, Token *o)
{
	KNH_ASSERT(IS_Token(o));
	if(SP(o)->tt == TT_ASIS) { return "_"; }
	if(SP(o)->tt < TT_NUM) {
		return knh_token_tochar(SP(o)->tt);
	}
	if(IS_String(DP(o)->text)) {
		return knh_String_tochar(DP(o)->text);
	}
	if(SP(o)->tt == TT_CID) {
		return CLASSN(DP(o)->cid);
	}
	if(SP(o)->tt == TT_FN) {
		return FIELDN(DP(o)->fn);
	}
	if(IS_NULL(DP(o)->data)) {
		return "null";
	}
#ifdef KNH_DBGMODE
	if(SP(o)->tt == TT_CONST) {
		return "TT_CONST";
	}
	return "Token: unknown";
#else
	return "";
#endif
}

/* ------------------------------------------------------------------------ */

knh_bytes_t knh_Token_tobytes(Ctx *ctx, Token *o)
{
	return new_bytes(sToken(o));
}

/* ------------------------------------------------------------------------ */
/* @method void Token.%s(OutputStream w, String m) */

void knh_Token__s(Ctx *ctx, Token *o, OutputStream *w, String *m)
{
	KNH_ASSERT(IS_Token(o));
	if(SP(o)->tt < TT_NUM || SP(o)->tt == TT_ASIS) {
		knh_write_char(ctx, w, knh_token_tochar(SP(o)->tt));
	}else if(SP(o)->tt == TT_CID) {
		knh_write_char(ctx, w, CLASSN(DP(o)->cid));
	}else if(SP(o)->tt == TT_FN) {
		knh_write_char(ctx, w, FIELDN(DP(o)->fn));
	}else if(SP(o)->tt == TT_MN) {
		char bufm[CLASSNAME_BUFSIZ];
		knh_format_methodn(ctx, bufm, sizeof(bufm), DP(o)->mn);
		knh_write_char(ctx, w, bufm);
	}else if(IS_String(DP(o)->text)) {
		if(SP(o)->tt == TT_STR) {
			knh_putc(ctx, w, '"');
			knh_write_char(ctx, w, knh_String_tochar(DP(o)->text));
			knh_putc(ctx, w, '"');
		}
		else if(SP(o)->tt == TT_TSTR) {
			knh_putc(ctx, w, '\'');
			knh_write_char(ctx, w, knh_String_tochar(DP(o)->text));
			knh_putc(ctx, w, '\'');
		}
		else {
			knh_write_char(ctx, w, knh_String_tochar(DP(o)->text));
		}
	}else if(IS_NULL(DP(o)->data)) {
		knh_write_char(ctx, w, "null");
	}else {
		knh_format(ctx, w, METHODN__k, DP(o)->data, KNH_NULL);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Token.%k(OutputStream w, String m) */

void knh_Token__k(Ctx *ctx, Token *o, OutputStream *w, String *m)
{
	KNH_ASSERT(IS_Token(o));
	if(knh_token_isNested(SP(o)->tt)) {
		int i;
		knh_tkc_t tc;
		knh_Token_tc(ctx, o, &tc);
		if(SP(o)->tt == TT_PARENTHESIS) {
			knh_write(ctx, w, STEXT("("));
		}
		else if(SP(o)->tt == TT_BRANCET) {
			knh_write(ctx, w, STEXT("["));
		}
		else {
			KNH_ASSERT(SP(o)->tt == TT_BRACE);
			knh_write(ctx, w, STEXT("{"));
		}
		for(i = 0; i < tc.e; i++) {
			knh_Token__k(ctx, tc.ts[i], w, m);
		}
		if(SP(o)->tt == TT_PARENTHESIS) {
			knh_write(ctx, w, STEXT("("));
		}
		else if(SP(o)->tt == TT_BRANCET) {
			knh_write(ctx, w, STEXT("["));
		}
		else {
			KNH_ASSERT(SP(o)->tt == TT_BRACE);
			knh_write(ctx, w, STEXT("{"));
		}
		return;
	}
	/* PREFIX */
	if(knh_Token_isTopDot(o)) {
		knh_putc(ctx, w, '.');
	}
	if(SP(o)->tt == TT_METAN) {
		knh_putc(ctx, w, '@');
	}
	else if(SP(o)->tt == TT_PROPN) {
		knh_putc(ctx, w, '$');
	}
	else if(SP(o)->tt == TT_MT) {
		knh_putc(ctx, w, '%');
	}
	else if(SP(o)->tt == TT_STR) {
		knh_putc(ctx, w, '"');
	}
	else if(SP(o)->tt == TT_TSTR) {
		knh_putc(ctx, w, '\'');
	}

	/* BODY */
	if(SP(o)->tt == TT_CID) {
		knh_write_char(ctx, w, CLASSN(DP(o)->cid));
	}else if(SP(o)->tt == TT_FN) {
		knh_write_char(ctx, w, FIELDN(DP(o)->fn));
	}else if(SP(o)->tt == TT_MN) {
		char bufm[CLASSNAME_BUFSIZ];
		knh_format_methodn(ctx, bufm, sizeof(bufm), DP(o)->mn);
		knh_write_char(ctx, w, bufm);
	}else {
		knh_write_char(ctx, w, sToken(o));
	}
	/* POSTFIX */
	if(SP(o)->tt == TT_LABEL) {
		knh_putc(ctx, w, ':'); knh_putc(ctx, w, ' ');
	}
	else if(SP(o)->tt == TT_METAN) {
		knh_putc(ctx, w, ' ');
	}
	else if(SP(o)->tt == TT_STR) {
		knh_putc(ctx, w, '"');
	}
	else if(SP(o)->tt == TT_TSTR) {
		knh_putc(ctx, w, '\'');
	}
	if(knh_Token_isTailWildCard(o)) {
		knh_write(ctx, w, STEXT(".*"));
	}
	if(knh_Token_isExceptionType(o)) {
		knh_write(ctx, w, STEXT("!!"));
	}
	else if(knh_Token_isNotNullType(o)) {
		knh_write(ctx, w, STEXT("!"));
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Token.%dump(OutputStream w, String m) */

void knh_Token__dump(Ctx *ctx, Token *o, OutputStream *w, String *m)
{
	KNH_ASSERT(IS_Token(o));
	knh_OutputStream_write_indent(ctx, w);
	knh_printf(ctx, w, "%s[%d]", knh_token_tochar(SP(o)->tt), (knh_intptr_t)SP(o)->line);
	knh_putc(ctx, w, ' ');
	knh_Token__s(ctx, o, w, m);
	knh_printf(ctx, w, " (>>%s) ", knh_token_tochar(DP(o)->tt_next));
	if(SP(o)->flag != 0)
		knh_write__flag(ctx, w, SP(o)->flag);
	knh_println(ctx, w, STEXT(""));
	if(knh_token_isNested(SP(o)->tt)) {
		int i;
		knh_tkc_t tc;
		knh_Token_tc(ctx, o, &tc);
		knh_OutputStream_indent_inc(ctx, w);
		for(i = 0; i < tc.e; i++) {
			knh_Token__dump(ctx, tc.ts[i], w, m);
		}
		knh_OutputStream_indent_dec(ctx, w);
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
