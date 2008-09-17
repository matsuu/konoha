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
knh_Stmt_struct_init(Ctx *ctx, knh_Stmt_struct *b, int init, Object *cs)
{
	b->size = 0;
	b->capacity = init;
	b->type = CLASS_Any;
	b->line_end = 0;
	if(b->capacity > 0) {
		b->terms = (Object**)KNH_MALLOC(ctx, sizeof(Term*) * b->capacity);
		size_t i;
		for(i = 0; i < b->capacity; i++) {
			KNH_INITv(b->terms[i], KNH_NULL);
		}
	}else {
		b->terms = NULL;
	}
	KNH_INITv(b->metaDictMap,  KNH_NULL);
	KNH_INITv(b->next,  KNH_NULL);
}

/* ------------------------------------------------------------------------ */

#define _knh_Stmt_struct_copy  NULL

/* ------------------------------------------------------------------------ */

#define _knh_Stmt_struct_compare  NULL

/* ------------------------------------------------------------------------ */

static
void knh_Stmt_terms_traverse(Ctx *ctx, knh_Stmt_struct *b, f_traverse gc)
{
	size_t i;
	for(i = 0; i < b->capacity; i++) {
		gc(ctx, b->terms[i]);
	}
	if(IS_SWEEP(gc)) {
		KNH_FREE(b->terms, sizeof(Term*) * b->capacity);
		b->terms = NULL;
		b->capacity = 0;
		b->size = 0;
	}
}

/* ------------------------------------------------------------------------ */

void
knh_Stmt_struct_traverse(Ctx *ctx, knh_Stmt_struct *b, f_traverse gc)
{
	if(b->terms != NULL) {
		knh_Stmt_terms_traverse(ctx, b, gc);
	}
	gc(ctx, UP(b->metaDictMap));
	gc(ctx, UP(b->next));
}

/* ======================================================================== */
/* [constructors] */

Stmt* new_Stmt(Ctx *ctx, knh_flag_t flag, knh_stmt_t stt)
{
	knh_Stmt_t *o =
		(Stmt*)new_Object_malloc(ctx, FLAG_Stmt, CLASS_Stmt, sizeof(knh_Stmt_struct));
	knh_Stmt_struct_init(ctx, DP(o), knh_stmt_size(stt), NULL);
	SP(o)->fileid = 0;
	SP(o)->line = 0;
	SP(o)->flag = flag;
	SP(o)->stt  = stt;
	return o;
}

/* ======================================================================== */
/* [DONE] */

static Object *tglobalStmtDONE = NULL;

/* ------------------------------------------------------------------------ */

Stmt* new_StmtDONE(Ctx *ctx)
{
	if(tglobalStmtDONE == NULL) {
		tglobalStmtDONE = (Object*)new_Stmt(ctx, 0, STT_DONE);
		KNH_TSTATICOBJ(&tglobalStmtDONE);
	}
	return (Stmt*)tglobalStmtDONE;
}

/* ------------------------------------------------------------------------ */

void knh_Stmt_done(Ctx *ctx, Stmt *o)
{
	SP(o)->stt = STT_DONE;
	if(DP(o)->terms != NULL) {
		knh_Stmt_terms_traverse(ctx, DP(o), knh_Object_RCsweep);
	}
	KNH_SETv(ctx, DP(o)->metaDictMap, KNH_NULL);
}

/* ======================================================================== */
/* [terms] */

static
void knh_Stmt_terms_expand(Ctx *ctx, Stmt *o)
{
	size_t i, newcapacity = DP(o)->capacity * 2;
	Object **newterms = (Object**)KNH_MALLOC(ctx, sizeof(Object*) * newcapacity);
	knh_memcpy(newterms, DP(o)->terms, sizeof(Object*) * DP(o)->capacity);
	for(i = DP(o)->capacity; i < newcapacity; i++) {
		KNH_INITv(newterms[i], KNH_NULL);
	}
	KNH_FREE(DP(o)->terms, sizeof(Object*) * DP(o)->capacity);
	DP(o)->terms = newterms;
	DP(o)->capacity = newcapacity;
	KNH_ASSERT(DP(o)->size < DP(o)->capacity);
}

/* ------------------------------------------------------------------------ */

void knh_Stmt_add(Ctx *ctx, Stmt *o, Term *tm)
{
	KNH_ASSERT(IS_Term(tm));
	KNH_ASSERT(SP(o)->stt != STT_DONE);
	if(!(DP(o)->size < DP(o)->capacity)) {
		knh_Stmt_terms_expand(ctx, o);
	}
	KNH_SETv(ctx, DP(o)->terms[DP(o)->size], tm);
	DP(o)->size++;
	if(IS_Stmt((Stmt*)tm)) {
		Stmt *stmt = (Stmt*)tm;
		DP(o)->line_end = SP(stmt)->line;
		if(SP(o)->line == 0) {
			SP(o)->line = DP(stmt)->line_end;
			SP(o)->fileid = SP(stmt)->fileid;
		}
		if(SP(o)->stt == STT_ERR) return;
		if(SP(stmt)->stt == STT_ERR) {
			DBG2_P("switching .. from %s to STT_ERR", knh_stmt_tochar(SP(o)->stt));
			KNH_SETv(ctx, DP(o)->terms[0], DP(stmt)->terms[0]);
			SP(o)->stt = STT_ERR;
		}
	}
	else {
		Token *tk = (Token*)tm;
		DP(o)->line_end = SP(tk)->line;
		if(SP(o)->line == 0) {
			SP(o)->line = DP(o)->line_end;
			SP(o)->fileid = SP(tk)->fileid;
		}
		if(SP(o)->stt == STT_ERR) return;
		if(SP(tk)->tt == TT_ERR) {
			DBG2_P("switching .. from %s to STT_ERR", knh_stmt_tochar(SP(o)->stt));
			KNH_SETv(ctx, DP(o)->terms[0], tk);
			SP(o)->stt = STT_ERR;
		}
	}
}

/* ------------------------------------------------------------------------ */

void knh_Stmt_add_ERR(Ctx *ctx, Stmt *o, Token *tk)
{
	KNH_ASSERT(IS_Token(tk));
	KNH_ASSERT(SP(o)->stt != STT_DONE);
	if(!(DP(o)->size < DP(o)->capacity)) {
		knh_Stmt_terms_expand(ctx, o);
	}
	KNH_SETv(ctx, DP(o)->terms[DP(o)->size], tk);
	DP(o)->size++;
	DP(o)->line_end = SP(tk)->line;
	if(SP(o)->line == 0) {
		SP(o)->line = DP(o)->line_end;
		SP(o)->fileid = SP(tk)->fileid;
	}
	if(SP(o)->stt == STT_ERR) return;
	DBG2_P("switching .. from %s to STT_ERR", knh_stmt_tochar(SP(o)->stt));
	KNH_ASSERT(DP(o)->size > 0);
	KNH_SETv(ctx, DP(o)->terms[0], tk);
	SP(o)->stt = STT_ERR;
}

/* ======================================================================== */
/* [visit] */

Stmt *knh_Stmt_tail(Stmt *o)
{
	Stmt *tail = o;
	while(IS_NOTNULL(DP(tail)->next)) {
		tail = DP(tail)->next;
	}
	return tail;
}

/* ------------------------------------------------------------------------ */

void knh_Stmt_tail_append(Ctx *ctx, Stmt *o, Stmt *stmt)
{
	KNH_ASSERT(IS_Stmt(o));
	if(SP(stmt)->stt != STT_DONE) {
		Stmt *tail = knh_Stmt_tail(o);
		KNH_ASSERT(SP(o)->stt != STT_ERR);
		KNH_SETv(ctx, DP(tail)->next, stmt);
	}
}

/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */
/* @method void Stmt.%s(OutputStream w, Any m) */

void knh_Stmt__s(Ctx *ctx, Stmt *o, OutputStream *w, Any *m)
{
	knh_int_t i;
	knh_putc(ctx, w, '(');
	if(SP(o)->stt != STT_OP && SP(o)->stt != STT_NEW && SP(o)->stt != STT_CALL ) {
		knh_write__s(ctx, w, knh_stmt_tochar(SP(o)->stt));
		if(DP(o)->size > 0) {
			knh_putc(ctx, w, ' ');
		}
	}
	for(i = 0; i < DP(o)->size; i++) {
		if(i > 0) knh_putc(ctx, w, ' ');
		if(IS_Token(DP(o)->terms[i])) {
			knh_Token__s(ctx, DP(o)->tokens[i], w, m);
		}else {
			KNH_ASSERT(IS_Stmt(DP(o)->terms[i]));
			knh_Stmt__s(ctx, DP(o)->stmts[i], w, m);
			if(IS_NOTNULL(DP(DP(o)->stmts[i])->next)) {
				knh_write_dots(ctx, w);
			}
		}
	}
	knh_putc(ctx, w, ')');
}

/* ------------------------------------------------------------------------ */
/* @method void Stmt.%dump(OutputStream w, Any m) */

void knh_Stmt__dump(Ctx *ctx, Stmt *o, OutputStream *w, Any *m)
{
	L_RESTART:;
	knh_StmtMETA_dump(ctx, o, w, m);
	knh_printf(ctx, w, "%s\t", knh_stmt_tochar(SP(o)->stt));
	knh_Stmt__s(ctx, o, w, m);
	if(IS_NOTNULL(DP(o)->next)) {
		knh_putc(ctx, w, '\n');
		o = DP(o)->next;
		goto L_RESTART;
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
