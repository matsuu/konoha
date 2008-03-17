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

/* ======================================================================== */
/* [constructors] */

void
knh_Stmt_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Stmt *b = (Stmt*)s;
	b->flag = 0;
	b->stt  = STT_DONE;
	b->size = 0;
	b->capacity = init;
	if(b->capacity > 0) {
		b->terms = knh_malloc(ctx, sizeof(Term*) * b->capacity);
		size_t i;
		for(i = 0; i < b->capacity; i++) {
			KNH_INITv(b->terms[i], KNH_NULL);
		}
	}else {
		b->terms = NULL;
	}
	KNH_INITv(b->meta,  KNH_NULL);
	KNH_INITv(b->next,  KNH_NULL);
}

/* ------------------------------------------------------------------------ */

#define _knh_Stmt_struct_copy  NULL

/* ------------------------------------------------------------------------ */

#define _knh_Stmt_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void
knh_Stmt_terms_traverse(Ctx *ctx, Stmt *b, f_gc gc)
{
	size_t i;
	for(i = 0; i < b->capacity; i++) {
		gc(ctx, b->terms[i]);
	}
	if(IS_SWEEP(gc)) {
		knh_free(b->terms, sizeof(Term*) * b->capacity);
		b->terms = NULL;
		b->capacity = 0;
		b->size = 0;
	}
}

/* ------------------------------------------------------------------------ */

void
knh_Stmt_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Stmt *b = (Stmt*)s;
	if(b->terms != NULL) {
		knh_Stmt_terms_traverse(ctx, b, gc);
	}
	gc(ctx, b->meta);
	gc(ctx, b->next);
}

/* ======================================================================== */
/* [constructors] */

Stmt* new_Stmt(Ctx *ctx, knh_flag_t flag, knh_stmt_t stt)
{
	Stmt* b = (Stmt*)knh_Object_malloc(ctx, CLASS_Stmt);
	knh_Stmt_struct_init(ctx, (Struct*)b, knh_stmt_initsize(stt), NULL);
	b->flag = flag;
	b->stt  = stt;
	return b;
}

/* ======================================================================== */
/* [done] */

void knh_Stmt_done(Ctx *ctx, Stmt *b)
{
	b->stt = STT_DONE;
	if(b->terms != NULL) {
		knh_Stmt_terms_traverse(ctx, b, knh_sweep);
	}
	KNH_SETv(ctx, b->meta, KNH_NULL);
}

/* ======================================================================== */
/* [terms] */


Term *knh_Stmt_terms(Stmt *b, size_t n)
{
	DEBUG_ASSERT(n < b->size);
	return b->terms[n];
}

/* ------------------------------------------------------------------------ */


void knh_Stmt_terms_expand(Ctx *ctx, Stmt *b)
{
	size_t i, newcapacity = b->capacity + 4;
	Term **newterms = knh_malloc(ctx, sizeof(Term*) * newcapacity);
	knh_memcpy(newterms, b->terms, sizeof(Term*) * b->capacity);
	for(i = b->capacity; i < newcapacity; i++) {
		KNH_INITv(newterms[i], KNH_NULL);
	}
	knh_free(b->terms, sizeof(Term*) * b->capacity);
	b->terms = newterms;
	b->capacity = newcapacity;
}

/* ------------------------------------------------------------------------ */

void knh_Stmt_terms_add__fast(Ctx *ctx, Stmt *b, Term *tm)
{
	DEBUG_ASSERT(IS_Term(tm));
	if(b->size == b->capacity) {
		knh_Stmt_terms_expand(ctx, b);
	}
	KNH_SETv(ctx, b->terms[b->size], tm);
	b->size++;
}

/* ------------------------------------------------------------------------ */

void knh_Stmt_terms_add(Ctx *ctx, Stmt *b, Term *tm)
{
	DEBUG_ASSERT(IS_Term(tm));
	if(knh_Term_isERR(tm)) {
		KNH_LOPEN(ctx, 0);
		KNH_LPUSH(ctx, tm);
		knh_Stmt_toSyntaxError(ctx, b, tm);
		KNH_LCLOSE(ctx);
		return;
	}
	knh_Stmt_terms_add__fast(ctx, b, tm);
}

/* ======================================================================== */
/* [visit] */


Stmt *knh_Stmt_tail(Stmt *b)
{
	Stmt *tail = b;
	while(IS_NOTNULL(tail->next)) {
		tail = tail->next;
	}
	return tail;
}

/* ------------------------------------------------------------------------ */


void knh_Stmt_tail_append(Ctx *ctx, Stmt *b, Stmt *stmt)
{
	DEBUG_ASSERT(IS_Stmt(b));
	Stmt *tail = knh_Stmt_tail(b);
	KNH_SETv(ctx, tail->next, stmt);
}

/* ------------------------------------------------------------------------ */


void knh_Stmt_visit(Ctx *ctx, Stmt *b, f_stmtvisit fvisit, Object *v, int nest)
{
	int step = 0;
	Stmt *next = b;
	while(IS_NOTNULL(next)) {
		step++;
		if(next->stt != STT_DONE) {
			fvisit(ctx, next, v, nest, step);
		}
		next = next->next;
	}
}

/* ======================================================================== */
/* [movabletext] */

/* @method void Stmt.%s(OutputStream w, Any m) */

void knh_Stmt__s(Ctx *ctx, Stmt *b, OutputStream *w, Any *m)
{
	knh_putc(ctx, w, '(');
	knh_int_t i;
	for(i = 0; i < b->size; i++) {
		Term *tm = knh_Stmt_terms(b, i);
		if(i > 0) knh_putc(ctx, w, ' ');
		if(IS_Token(tm)) {
			knh_Token__s(ctx, (Token*)tm, w, m);
		}else {
			DEBUG_ASSERT(IS_Stmt(tm));
			knh_Stmt__s(ctx, (Stmt*)tm, w, m);
			if(IS_NOTNULL(((Stmt*)tm)->next)) {
				knh_write_dots(ctx, w);
			}
		}
	}
	knh_putc(ctx, w, ')');
}

/* ------------------------------------------------------------------------ */

/* @method void Stmt.%dump(OutputStream w, Any m) */

void knh_Stmt__dump(Ctx *ctx, Stmt *b, OutputStream *w, Any *m)
{
	L_RESTART:;
	knh_printf(ctx, w, "%s\t", knh_stmt_tochar(b->stt));
	if(knh_Stmt_hasMeta(b)) {
		knh_Stmt__s(ctx, b->meta, w, m);
		knh_putc(ctx, w, ':');
	}
	knh_Stmt__s(ctx, b, w, m);
	if(IS_NOTNULL(b->next)) {
		knh_putc(ctx, w, '\n');
		b = b->next;
		goto L_RESTART;
	}	
}

/* ------------------------------------------------------------------------ */



#ifdef __cplusplus
}
#endif
