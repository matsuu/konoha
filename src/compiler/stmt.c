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

Stmt* new_Stmt(Ctx *ctx, knh_flag_t flag, knh_stmt_t stt)
{
	knh_Stmt_t *o = (Stmt*)new_Object_bcid(ctx, CLASS_Stmt, knh_stmt_size(stt));
	SP(o)->uri = 0;
	SP(o)->line = 0;
	SP(o)->flag = flag;
	SP(o)->stt  = stt;
	return o;
}

/* ======================================================================== */
/* [ERR] */

void knh_Stmt_toERR(Ctx *ctx, Stmt *stmt, Term *tm)
{
	if(SP(stmt)->stt == STT_ERR) return;
	SP(stmt)->stt = STT_ERR;
	knh_uri_t uri = 0;
	int line = 0;
	if(IS_Token(tm)) {
		uri =  SP((Token*)tm)->uri;
		line =  SP((Token*)tm)->line;
	}
	else if(IS_Stmt(tm)) {
		uri =  SP((Stmt*)tm)->uri;
		line =  SP((Stmt*)tm)->line;
	}
	{
		char buf[256];
		knh_snprintf(buf, sizeof(buf), "Script!!: running errors at %s:%d", URIDN(SP(stmt)->uri), SP(stmt)->line);
		KNH_SETv(ctx, DP(stmt)->errMsg, new_String(ctx, B(buf), NULL));
		KNH_SETv(ctx, DP(stmt)->next, KNH_NULL);
	}
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
	KNH_FREE(ctx, DP(o)->terms, sizeof(Object*) * DP(o)->capacity);
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
	if(IS_Stmt(tm)) {
		Stmt *stmt = (Stmt*)tm;
		DP(o)->line_end = SP(stmt)->line;
		if(SP(o)->line == 0) {
			SP(o)->line = DP(stmt)->line_end;
			SP(o)->uri = SP(stmt)->uri;
		}
		if(SP(stmt)->stt == STT_ERR) {
			knh_Stmt_toERR(ctx, o, tm);
		}
	}
	else {
		Token *tk = (Token*)tm;
		DP(o)->line_end = SP(tk)->line;
		if(SP(o)->line == 0) {
			SP(o)->line = DP(o)->line_end;
			SP(o)->uri = SP(tk)->uri;
		}
		if(SP(tk)->tt == TT_ERR) {
			knh_Stmt_toERR(ctx, o, tm);
		}
	}
}

/* ======================================================================== */
/* [visit] */

Stmt *knh_Stmt_tail(Ctx *ctx, Stmt *o)
{
	Stmt *tail = o;
	while(IS_NOTNULL(DP(tail)->next)) {
		//DBG_P("stt=%s", knh_stmt_tochar(SP(tail)->stt));
		tail = DP(tail)->next;
	}
	return tail;
}

/* ------------------------------------------------------------------------ */

Stmt* knh_StmtNULL_tail_append(Ctx *ctx, Stmt *o, Stmt *stmt)
{
	if(o == NULL) {
		return stmt;
	}
	else {
		Stmt *tail = knh_Stmt_tail(ctx, o);
		KNH_SETv(ctx, DP(tail)->next, stmt);
		return o;
	}
}

/* ------------------------------------------------------------------------ */
/* [META] */

knh_bool_t knh_Stmt_hasMeta(Stmt *o)
{
	return (IS_bDictMap(DP(o)->metaDictMap));
}

/* ------------------------------------------------------------------------ */

knh_flag_t knh_StmtMETHOD_flag(Ctx *ctx, Stmt *o)
{
	knh_flag_t flag = 0;
	if(IS_DictMap(DP(o)->metaDictMap)) {
		Object *v = knh_DictMap_get__b(ctx, DP(o)->metaDictMap, STEXT("Virtual"));
		if(IS_NOTNULL(v)) {
			flag |= KNH_FLAG_MF_VIRTUAL;
		}
		v = knh_DictMap_get__b(ctx, DP(o)->metaDictMap, STEXT("Abstract"));
		if(IS_NOTNULL(v)) {
			flag |= KNH_FLAG_MF_VIRTUAL;
		}
		v = knh_DictMap_get__b(ctx, DP(o)->metaDictMap, STEXT("Private"));
		if(IS_NOTNULL(v)) {
			flag |= KNH_FLAG_MF_PRIVATE;
		}
		v = knh_DictMap_get__b(ctx, DP(o)->metaDictMap, STEXT("Const"));
		if(IS_NOTNULL(v)) {
			flag |= KNH_FLAG_MF_CONST;
		}
		v = knh_DictMap_get__b(ctx, DP(o)->metaDictMap, STEXT("Static"));
		if(IS_NOTNULL(v)) {
			flag |= KNH_FLAG_MF_STATIC;
		}
	}
	return flag;
}

/* ------------------------------------------------------------------------ */

knh_flag_t knh_Stmt_metaflag__field(Ctx *ctx, Stmt *b)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

knh_flag_t knh_StmtPRINT_flag(Ctx *ctx, Stmt *o)
{
	knh_flag_t flag = 0;
	if(IS_bDictMap(DP(o)->metaDictMap)) {
		Object *v = knh_DictMap_get__b(ctx,  DP(o)->metaDictMap, STEXT("time"));
		if(IS_NOTNULL(v)) {
			flag |= KNH_FLAG_PF_TIME;
		}
	}
	return flag;
}

/* ======================================================================== */
/* [Annotation] */

knh_bool_t knh_StmtMETA_isOverride(Ctx *ctx, Stmt *o)
{
	if(IS_DictMap(DP(o)->metaDictMap)) {
		Object *v = knh_DictMap_get__b(ctx, DP(o)->metaDictMap, STEXT("Override"));
		if(IS_NOTNULL(v)) return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

int knh_StmtMETA_is(Ctx *ctx, Stmt *stmt, knh_bytes_t name)
{
	if(IS_DictMap(DP(stmt)->metaDictMap)) {
		Object *v = knh_DictMap_get__b(ctx, DP(stmt)->metaDictMap, name);
		if(IS_NOTNULL(v)) return 1;
	}
	return 0;
}

/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */
/* @method void Stmt.%s(OutputStream w, String m) */

void knh_Stmt__s(Ctx *ctx, Stmt *o, OutputStream *w, String *m)
{
	knh_intptr_t i;
	knh_putc(ctx, w, '(');
	if(SP(o)->stt != STT_OP && SP(o)->stt != STT_NEW && SP(o)->stt != STT_CALL ) {
		knh_write_char(ctx, w, knh_stmt_tochar(SP(o)->stt));
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

static
void knh_StmtMETA_dump(Ctx *ctx, Stmt *o, OutputStream *w, String *m)
{
	if(!IS_DictMap(DP(o)->metaDictMap)) return ;
	int i = 0, size = (DP(o)->metaDictMap)->size;
	for(i = 0; i < size; i++) {
		String *k = (String*)knh_DictMap_keyAt(DP(o)->metaDictMap, i);
		String *v = (String*)knh_DictMap_valueAt(DP(o)->metaDictMap, i);
		if(k == v) {
			knh_printf(ctx, w, "@%s ", knh_String_tochar(k));
		}
		else {
			knh_printf(ctx, w, "@%s(%O) ", knh_String_tochar(k), v);
		}
	}
	if(size > 0) {
		knh_println(ctx, w, STEXT(""));
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Stmt.%dump(OutputStream w, String m) */

void knh_Stmt__dump(Ctx *ctx, Stmt *o, OutputStream *w, String *m)
{
	L_RESTART:;
	if(IS_DictMap(DP(o)->metaDictMap)) {
		knh_StmtMETA_dump(ctx, o, w, m);
	}
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
