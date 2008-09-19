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
/* [struct] */

void
knh_Token_struct_init(Ctx *ctx, knh_Token_struct *b, int init, Object *cs)
{
	b->tt_next = TT_EOT;
	b->type    =  CLASS_Any;
	KNH_INITv(b->data, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

#define _knh_Token_struct_copy  NULL

/* ------------------------------------------------------------------------ */

#define _knh_Token_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void
knh_Token_struct_traverse(Ctx *ctx, knh_Token_struct *b, f_traverse gc)
{
	gc(ctx, b->data);
}

/* ======================================================================== */
/* [constructors] */

Token* new_Token(Ctx *ctx, knh_flag_t flag, knh_fileid_t fileid, knh_line_t line, knh_token_t tt)
{
	knh_Token_t *o =
		(Token*)new_Object_malloc(ctx, FLAG_Token, CLASS_Token, sizeof(knh_Token_struct));
	knh_Token_struct_init(ctx, DP(o), 0, NULL);
	SP(o)->flag =   flag;
	SP(o)->fileid = fileid;
	SP(o)->line =   line;
	SP(o)->tt   =   tt;
	return o;
}

/* ------------------------------------------------------------------------ */

Token *new_Token__text(Ctx *ctx, Token *ftk, knh_bytes_t text)
{
	Token *o = new_Token__parse(ctx, KNH_FLAG_TKF_GENERATED, SP(ftk)->fileid, SP(ftk)->line, text, (BytesConv*)KNH_NULL);
	DP(o)->tt_next = DP(ftk)->tt_next;
	return o;
}

/* ------------------------------------------------------------------------ */

void knh_Token_setFL(Token *o, Any *fln)
{
	if(IS_Token(fln)) {
		Token *tk = (Token*)fln;
		SP(o)->fileid =  SP(tk)->fileid;
		SP(o)->line =  SP(tk)->line;
	}
	else if(IS_Compiler((Object*)fln)) {
		Compiler *cpr = (Compiler*)fln;
		SP(o)->fileid =  DP(cpr)->fileid;
		SP(o)->line =  DP(cpr)->line;
	}
	else {
		Stmt *stmt = (Stmt*)fln;
		KNH_ASSERT(IS_Stmt(stmt));
		SP(o)->fileid =  SP(stmt)->fileid;
		SP(o)->line =  SP(stmt)->line;
	}
}

/* ------------------------------------------------------------------------ */

Token *new_TokenASIS(Ctx *ctx, Any *fln)
{
	knh_Token_t *o = (Token*)new_Object_malloc(ctx, FLAG_Token, CLASS_Token, sizeof(knh_Token_struct));
	knh_Token_struct_init(ctx, DP(o), 0, NULL);
	SP(o)->flag = KNH_FLAG_TKF_GENERATED;
	SP(o)->tt = TT_ASIS;
	knh_Token_setFL(o, fln);
	return o;
}

/* ------------------------------------------------------------------------ */

Token *new_TokenCID(Ctx *ctx, Any *fln, knh_class_t cid)
{
	knh_Token_t *o = (Token*)new_Object_malloc(ctx, FLAG_Token, CLASS_Token, sizeof(knh_Token_struct));
	knh_Token_struct_init(ctx, DP(o), 0, NULL);
	SP(o)->flag = KNH_FLAG_TKF_GENERATED;
	SP(o)->tt = TT_CID;
	knh_Token_setFL(o, fln);
	DP(o)->cid = cid;
	return o;
}

/* ------------------------------------------------------------------------ */

Token *new_TokenMN(Ctx *ctx, Any *fln, knh_methodn_t mn)
{
	knh_Token_t *o = (Token*)new_Object_malloc(ctx, FLAG_Token, CLASS_Token, sizeof(knh_Token_struct));
	knh_Token_struct_init(ctx, DP(o), 0, NULL);
	SP(o)->flag = KNH_FLAG_TKF_GENERATED;
	SP(o)->tt = TT_MN;
	knh_Token_setFL(o, fln);
	DP(o)->mn = mn;
	return o;
}

/* ------------------------------------------------------------------------ */

Token *new_TokenFN(Ctx *ctx, Any *fln, knh_fieldn_t fn)
{
	knh_Token_t *o = (Token*)new_Object_malloc(ctx, FLAG_Token, CLASS_Token, sizeof(knh_Token_struct));
	knh_Token_struct_init(ctx, DP(o), 0, NULL);
	SP(o)->flag = KNH_FLAG_TKF_GENERATED;
	SP(o)->tt = TT_FN;
	knh_Token_setFL(o, fln);
	DP(o)->fn = fn;
	return o;
}

///* ------------------------------------------------------------------------ */
//
//Token *new_Token__T(Ctx *ctx, Token *ftk, knh_token_t tt, char *token)
//{
//	knh_Token_t *o =
//		(Token*)new_Object__RAW(ctx, FLAG_Token, CLASS_Token, sizeof(knh_Token_struct));
//	knh_Token_struct_init(ctx, DP(o), 0, NULL);
//	DP(o)->flag = KNH_FLAG_TKF_GENERATED;
//	SP(o)->tt = tt;
//	DP(o)->fileid =  DP(ftk)->fileid;
//	DP(o)->line =  DP(ftk)->line;
//	DP(o)->tt_next = DP(ftk)->tt_next;
//	KNH_SETv(ctx, DP(o)->data, new_String__T(ctx, token));
//	return o;
//}
//
/* ------------------------------------------------------------------------ */

Token *new_Token__S(Ctx *ctx, Any *fln, knh_token_t tt, String *t)
{
	knh_Token_t *o =
		(Token*)new_Object_malloc(ctx, FLAG_Token, CLASS_Token, sizeof(knh_Token_struct));
	knh_Token_struct_init(ctx, DP(o), 0, NULL);
	SP(o)->flag = KNH_FLAG_TKF_GENERATED;
	SP(o)->tt = tt;
	knh_Token_setFL(o, fln);
	KNH_SETv(ctx, DP(o)->data, t);
	return o;
}

/* ======================================================================== */
/* [Array] */

#define knh_token_isNested(tt)  (tt == TT_BRACE || tt == TT_PARENTHESIS || tt == TT_BRANCET)

/* ------------------------------------------------------------------------ */

void knh_Token_tc(Token *o, knh_tokens_t *tc)
{
	KNH_ASSERT(knh_token_isNested(SP(o)->tt));
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

char *knh_Token_tochar(Token *o)
{
	KNH_ASSERT(IS_Token(o));
	if(SP(o)->tt == TT_ASIS) { return "_"; }
	if(SP(o)->tt < TT_NUM) {
		return knh_token_tochar(SP(o)->tt);
	}
	if(IS_String(DP(o)->str)) {
		return knh_String_tochar(DP(o)->str);
	}
	if(IS_NULL(DP(o)->data)) {
		return "null";
	}
	if(SP(o)->tt == TT_CID) {
		return CLASSN(DP(o)->cid);
	}
	if(SP(o)->tt == TT_FN) {
		return FIELDN(DP(o)->fn);
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

knh_bytes_t knh_Token_tobytes(Token *o)
{
	return new_bytes(knh_Token_tochar(o));
}

/* ------------------------------------------------------------------------ */
/* @method void Token.%s(OutputStream w, Any m) */

void knh_Token__s(Ctx *ctx, Token *o, OutputStream *w, Any *m)
{
	KNH_ASSERT(IS_Token(o));
	if(SP(o)->tt < TT_NUM || SP(o)->tt == TT_ASIS) {
		knh_write__s(ctx, w, knh_token_tochar(SP(o)->tt));
	}else if(SP(o)->tt == TT_CID) {
		knh_write__s(ctx, w, CLASSN(DP(o)->cid));
	}else if(SP(o)->tt == TT_FN) {
		knh_write__s(ctx, w, FIELDN(DP(o)->fn));
	}else if(SP(o)->tt == TT_MN) {
		char bufm[CLASSNAME_BUFSIZ];
		knh_format_methodn(bufm, sizeof(bufm), DP(o)->mn);
		knh_write__s(ctx, w, bufm);
	}else if(IS_String(DP(o)->str)) {
		if(SP(o)->tt == TT_STR) {
			knh_putc(ctx, w, '"');
			knh_write__s(ctx, w, knh_String_tochar(DP(o)->str));
			knh_putc(ctx, w, '"');
		}
		else if(SP(o)->tt == TT_TSTR) {
			knh_putc(ctx, w, '\'');
			knh_write__s(ctx, w, knh_String_tochar(DP(o)->str));
			knh_putc(ctx, w, '\'');
		}
		else {
			knh_write__s(ctx, w, knh_String_tochar(DP(o)->str));
		}
	}else if(IS_NULL(DP(o)->data)) {
		knh_write__s(ctx, w, "null");
	}else {
		knh_format(ctx, w, METHODN__k, DP(o)->data, KNH_NULL);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Token.%dump(OutputStream w, Any m) */

void knh_Token__dump(Ctx *ctx, Token *o, OutputStream *w, Any *m)
{
	KNH_ASSERT(IS_Token(o));
	knh_OutputStream_write_indent(ctx, w);
	knh_printf(ctx, w, "%s[%d]", knh_token_tochar(SP(o)->tt), (int)SP(o)->line);
	knh_putc(ctx, w, ' ');
	knh_Token__s(ctx, o, w, m);
	knh_printf(ctx, w, " (>>%s) ", knh_token_tochar(DP(o)->tt_next));
	if(SP(o)->flag != 0)
		knh_write__flag(ctx, w, SP(o)->flag);
	knh_println(ctx, w, STEXT(""));
	if(knh_token_isNested(SP(o)->tt)) {
		int i;
		knh_tokens_t tc;
		knh_Token_tc(o, &tc);
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
