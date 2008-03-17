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

#ifndef KONOHAC_ERROR_BUFSIZ
#define KONOHAC_ERROR_BUFSIZ 512
#endif  

static char *tglobalPerrorMsg[] = 
{
	"fatal", "language", "error", "type error", "warning", "ignored",
	"errata", "notice", "info",
};

/* ======================================================================== */
/* [perror] */

OutputStream *konohac_perror(Ctx *ctx, Token *tk, int lv)
{
	DEBUG_ASSERT(lv < sizeof(tglobalPerrorMsg));
	if(knh_Token_isPerrored(tk)) {
		OutputStream *w = KNH_STDOUT;
		knh_printf(ctx, KNH_STDOUT, "%s:%d: *%s: ", FILEN(tk->filen), (int)tk->line, tglobalPerrorMsg[lv]);
		return w;
	}
	else {
		OutputStream *w = KNH_STDOUT;
		knh_printf(ctx, KNH_STDOUT, "%s:%d: %s: ", FILEN(tk->filen), (int)tk->line, tglobalPerrorMsg[lv]);
		knh_Token_setPerrored(tk, 1);
		return w;
	}
}

/* ======================================================================== */
/* [ERR] */

void knh_Token_toERR(Ctx *ctx, Token *b)
{
	if(IS_NULL(b->data)) {
		String *s = new_String__fast(ctx, CLASS_String, B(knh_Token_tochar(b)));
		KNH_SETv(ctx, b->data, s);
	}
	b->tt = TT_ERR;
}

/* ======================================================================== */
/* [term] */

knh_bool_t knh_Term_isERR(Term *b)
{
	if(IS_Token(b)) {
		return (((Token*)b)->tt == TT_ERR);
	}
	else {
		DEBUG_ASSERT(IS_Stmt(b));
		return (((Stmt*)b)->stt == STT_ERR);
	}
}

/* ======================================================================== */
/* [Stmt] */

knh_int_t knh_tokens_epos(knh_int_t s, knh_int_t cp, knh_int_t e)
{

	if(cp < e) return cp;
	DEBUG_ASSERT(s <= e - 1);
	return e - 1;
}

/* ------------------------------------------------------------------------ */

Stmt* new_Stmt__SyntaxError(Ctx *ctx, Token** ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
	Stmt *b = new_Stmt(ctx, 0, STT_ERR);
	knh_Stmt_terms_add(ctx, b, ts[knh_tokens_epos(s, *cp, e)]);
	*cp = knh_tokens_nextstmt(ts, *cp, e);
	return b;
}

/* ------------------------------------------------------------------------ */

void knh_Stmt_toSyntaxError(Ctx *ctx, Stmt *b, Term *tm)
{
	DEBUG_ASSERT(IS_Stmt(b));
	DEBUG_ASSERT(b->stt != STT_DONE);
	
	if(b->stt == STT_ERR) {
		knh_Stmt_terms_add__fast(ctx, b, tm);
		return;
	}
	b->stt = STT_ERR;
	Token *tk;
	if(IS_Stmt(tm)) {
		Stmt *stmt = (Stmt*)tm;
		DEBUG_ASSERT(stmt->stt == STT_ERR);
		tk = stmt->terms[0];
		DEBUG_ASSERT(IS_Token(tk));
	}
	else{
		tk = (Token*)tm;
	}
	if(b->size == 0) {
		KNH_SETv(ctx, b->terms[0], tk);
		b->size++;
	}
	else {
		KNH_SETv(ctx, b->terms[0], tk);
	}
	DEBUG_ASSERT(IS_Token(b->terms[0]));
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
