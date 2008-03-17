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
knh_Token_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Token *b = (Token*)s;
	b->flag = 0;
	b->tt = 0;
	b->filen = 0;
	b->line =  1;
	KNH_INITv(b->data, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

#define _knh_Token_struct_copy  NULL

/* ------------------------------------------------------------------------ */

#define _knh_Token_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void
knh_Token_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Token *b = (Token*)s;
	gc(ctx, b->data);
}

/* ======================================================================== */
/* [constructors] */

Token* new_Token(Ctx *ctx, knh_flag_t flag, knh_filen_t filen, knh_line_t line, knh_bytes_t t, knh_token_t tt)
{
	Token* b = (Token*)knh_Object_malloc(ctx, CLASS_Token);
	knh_Token_struct_init(ctx, (Struct*)b, 0, NULL);
	b->flag = flag;
	b->tt = tt;
	b->filen =  filen;
	b->line =  line;
	if(TT_NUM <= tt) {
		if(tt == TT_PROPN) t = knh_bytes_last(t, 1);
		if(tt == TT_LABEL) t.len--;
		if(tt == TT_STR || tt == TT_QSTR || tt == TT_FMTSTR) {
			t = knh_bytes_last(t, 1);
			t.len--;
		}
		KNH_SETv(ctx, b->data, new_String__fast(ctx, CLASS_String, t));
	}
	return b;
}

/* ------------------------------------------------------------------------ */

INLINE
Token *new_Token__text(Ctx *ctx, Token *ftk, knh_bytes_t text)
{
	return new_Token__parse(ctx, KNH_FLAG_TKF_GENERATED, ftk->filen, ftk->line, text);
}

/* ------------------------------------------------------------------------ */

INLINE
Token *new_Token__ASIS(Ctx *ctx, Token *ftk)
{
	Token* b = (Token*)knh_Object_malloc(ctx, CLASS_Token);
	knh_Token_struct_init(ctx, (Struct*)b, 0, NULL);
	b->flag = KNH_FLAG_TKF_GENERATED;
	b->tt = TT_ASIS;
	b->filen =  ftk->filen;
	b->line =  ftk->line;
	return b;
}

/* ======================================================================== */
/* [Array] */


Token** knh_Token_ts(Token *b)
{
	DEBUG_ASSERT(knh_token_isNested(b->tt));
	if(IS_Array(b->data)) {
		return (Token**)knh_Array_list((Array*)b->data);
	}else{
		return &(b->data);
	}
}

/* ------------------------------------------------------------------------ */


size_t knh_Token_tokens_size(Token *b)
{
	DEBUG_ASSERT(knh_token_isNested(b->tt));
	if(IS_NULL(b->data)) return 0;
	if(IS_Token(b->data)) return 1;
	return knh_Array_size((Array*)b->data);
}

/* ------------------------------------------------------------------------ */


Token* knh_Tokens(Token *b, size_t n)
{
	DEBUG_ASSERT(knh_token_isNested(b->tt));
	DEBUG_ASSERT(IS_NOTNULL(b->data));
	if(IS_Token(b->data)) {
		DEBUG_ASSERT(n == 0);
		return (Token*)b->data;
	}
	DEBUG_ASSERT(n < knh_Array_size((Array*)b->data));
	return knh_Array_n((Array*)b->data, n);
}

/* ------------------------------------------------------------------------ */


void knh_Token_tokens_add(Ctx *ctx, Token *b, Token *tk)
{
	DEBUG_ASSERT(knh_token_isNested(b->tt));
	DEBUG_ASSERT(IS_Token(tk));
	if(IS_NULL(b->data)) {
		KNH_SETv(ctx, b->data, tk);
		return ;
	}
	if(IS_Token(b->data)) {
		Array *a = new_Array(ctx, 2);
		knh_Array_append(ctx, a, b->data);
		KNH_SETv(ctx, b->data, a);
	}
//	DEBUG("typeof(b->data)=%s", CLASSNo(b->data));
	DEBUG_ASSERT(IS_Array(b->data));
	knh_Array_add(ctx, (Array*)b->data, tk);
}

/* ------------------------------------------------------------------------ */


void knh_Token_tokens_empty(Ctx *ctx, Token *b)
{
	DEBUG_ASSERT(knh_token_isNested(b->tt));
	KNH_SETv(ctx, b->data, KNH_NULL);
}


/* ======================================================================== */
/* [RAW] */

Token* new_Token__RAW(Ctx *ctx, knh_flag_t flag, Token *tk, Object *data)
{
	Token* b = (Token*)knh_Object_malloc(ctx, CLASS_Token);
	b->flag = flag | KNH_FLAG_TKF_GENERATED;
	b->tt = TT_RAW;
	b->filen =  tk->filen;
	b->line =  tk->line;
	KNH_INITv(b->data, data);
	return b;
}

/* ------------------------------------------------------------------------ */


void knh_Token_setRAW(Ctx *ctx, Token *b, Object *data)
{
	b->tt = TT_RAW;
	KNH_SETv(ctx, b->data, data);
}

/* ------------------------------------------------------------------------ */


void knh_Token_toRAW(Token *b)
{
	b->tt = TT_RAW;
}

/* ------------------------------------------------------------------------ */

Token *new_Token__using_Null(Ctx *ctx, Token *tk)
{
	MC_EPRINT(ctx, tk, 3, "using null");
	return new_Token__RAW(ctx, KNH_FLAG_TKF_GENERATED, tk, KNH_NULL);
}


/* ======================================================================== */
/* [movabletext] */


char *knh_Token_tochar(Token *b)
{
	DEBUG_ASSERT(IS_Token(b));
	if(b->tt < TT_NUM) {
		return knh_token_tochar(b->tt);
	}
	if(IS_String(b->data)) {
		return knh_String_tochar(b->data);
	}
	if(b->tt == TT_RAW) {
		return "TT_RAW";
	}
	return "Token: unknown";
}

/* ------------------------------------------------------------------------ */

INLINE knh_bytes_t knh_Token_tobytes(Token *b)
{
	knh_bytes_t t;
	t.buf = (knh_uchar_t*)knh_Token_tochar(b);
	t.len = knh_strlen(t.buf);
	return t;
}

/* ------------------------------------------------------------------------ */
/* @method void Token.%s(OutputStream w, Any m) */

void knh_Token__s(Ctx *ctx, Token *b, OutputStream *w, Any *m)
{
	DEBUG_ASSERT(IS_Token(b));
	if(b->tt < TT_NUM) {
		knh_write__s(ctx, w, knh_token_tochar(b->tt));
	}else if(IS_String(b->data)) {
		knh_write__s(ctx, w, knh_String_tochar(b->data));
	}else if(IS_NULL(b->data)) {
		knh_write__s(ctx, w, "null");
	}else if(b->tt == TT_RAW) {
		knh_format(ctx, w, METHODN__s, b->data, KNH_NULL);
	}
}	

/* ------------------------------------------------------------------------ */
/* @method void Token.%dump(OutputStream w, Any m) */

void knh_Token__dump(Ctx *ctx, Token *b, OutputStream *w, Any *m)
{
	DEBUG_ASSERT(IS_Token(b));
	knh_OutputStream_write_indent(ctx, w);
	knh_printf(ctx, w, "%s[%d]", knh_token_tochar(b->tt), (int)b->line);
	//knh_write_flag(ctx, w, b->flag);
	knh_putc(ctx, w, ' ');
	knh_Token__s(ctx, b, w, m);
	knh_println(ctx, w, STEXT(""));
	if(knh_token_isNested(b->tt)) {
		knh_OutputStream_indent_inc(ctx, w);
		knh_int_t i = 0; 
		for(i = 0; i < knh_Token_tokens_size(b); i++) {
			knh_Token__dump(ctx, knh_Tokens(b, i), w, m);
		}
		knh_OutputStream_indent_dec(ctx, w);
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
