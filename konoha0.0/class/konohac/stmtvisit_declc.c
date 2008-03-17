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

#ifdef KONOHA_DEBUGMODE
	#define DEBUG_STMT0(ctx, stmt)
	#define DEBUG_STMT(ctx, stmt) \
		DEBUG("level=%d", level); \
		knh_Stmt__dump(ctx, stmt, KNH_STDOUT, knh_String_EMPTY()); \
		knh_flush(ctx, KNH_STDOUT); \

#else
	#define DEBUG_STMT(ctx, stmt)
#endif

/* ------------------------------------------------------------------------ */
/* [declc] */


void knh_stmtvisit_declc__namespace(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['namespace', 'NAME'] */
	Cmpl *b = (Cmpl*)v;
	DEBUG_ASSERT(stmt->size == 2);
	Token *tke = (Token*)stmt->terms[1];
	knh_Cmpl_changeNameSpace(ctx, b, knh_tnsn_forname(ctx, knh_Token_tobytes(tke)));
	//knh_Stmt_done(ctx, stmt);
}

#define _knh_stmtvisit_declm__namespace  knh_stmtvisit_declc__namespace
#define _knh_stmtvisit_declv__namespace  knh_stmtvisit_declc__namespace
#define _knh_stmtvisit_asm__namespace    knh_stmtvisit_declc__namespace

/* ------------------------------------------------------------------------ */

char *
knh_os_npath(knh_bytes_t orig, char *buf, size_t bufsiz)
{
	TODO();
	knh_snprintf(buf, bufsiz, "%s", orig.buf);
	return buf;
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declc__include(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['include', 'ANY'] */
	Cmpl *b = (Cmpl*)v;
	DEBUG_ASSERT(stmt->size == 2);
	char npath[KONOHA_FILEN_SIZE];
	knh_os_npath(knh_String_tobytes(knh_Term_getString(stmt->terms[1])), npath, sizeof(npath));
	DEBUG("including '%s'...", npath);
	FILE *fp = fopen(npath, "r");
	if(fp == NULL) {
		MC_EPRINT(ctx, (Token*)stmt->terms[0], MC_ERROR, "cannot open: '%s'", npath);
		knh_Stmt_done(ctx, stmt);
		return;
	}

	InputStream *in = new_InputStream__FILE(ctx, fp);
	in->filen = knh_tfilen_forname(ctx, B(npath));
	knh_konohac_eval(ctx, b->nsn, in);
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declc__uimport(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *mc = (Cmpl*)v;
	/* ['CLASS, NSNAME'] */
	Token *ctk = (Token*)stmt->terms[0];
	Token *ntk = (Token*)stmt->terms[1];
//	DEBUG("using %s %s", knh_Token_tochar(ctk), knh_Token_tochar(ntk));
	NameSpace *ns = knh_Cmpl_getNameSpace(ctx, (Cmpl*)v);

	knh_bytes_t cname = knh_Token_tobytes(ctk);
	knh_bytes_t lname = knh_Token_tobytes(ntk);
	
	if(ctk->tt == TT_ASIS) {
		knh_index_t idx = knh_bytes_rindex(lname, '.');
		if(idx == -1) {
			MC_EPRINT(ctx, ntk, MC_IGNORED, "wrong class name: %s", lname.buf);
		}

		knh_tclass_load(ctx, knh_bytes_first(lname, idx));
		if(lname.buf[lname.len - 1] == '*') {
			knh_NameSpace_import(ctx, ns, lname);
			return;
		}
		cname = knh_bytes_last(lname, idx+1);
	}

	/* single */
	if(lname.buf[lname.len - 1] == '*') {
		MC_EPRINT(ctx, ntk, MC_IGNORED, "ambigious name: %s", lname.buf);
		return;
	}
	knh_class_t newcid = knh_NameSpace_getClass(ctx, ns, lname);
	if(newcid == CLASS_unknown) {
		MC_EPRINT(ctx, ntk, MC_WARNING, "unknown class: %s", lname.buf);
		return;
	}
	knh_class_t oldcid = knh_NameSpace_getClass(ctx, ns, cname);
	if(oldcid != CLASS_unknown && newcid != oldcid) {
		MC_EPRINT(ctx, ntk, MC_INFO, "renaming class: %s => %s", CLASSN(oldcid), CLASSN(newcid));
	}
	knh_NameSpace_setLocalName(ctx, ns, new_String__fast(ctx, CLASS_String, cname), newcid);
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declc__uvocab(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *mc = (Cmpl*)v;
	/* ['CLASSTN', 'CURN'] */

	Cmpl *b = (Cmpl*)v;
	Token *tkc = (Token*)stmt->terms[0];
	Token *tku = (Token*)stmt->terms[1];
	DEBUG_ASSERT(IS_Token(tkc)); DEBUG_ASSERT(IS_Token(tku));
	NameSpace *ns = knh_Cmpl_getNameSpace(ctx, b);
	
	knh_class_t cid = knh_tclass_classURN(ctx, CLASS_String, knh_Token_tobytes(tku));
	if(cid == CLASS_String) {
		MC_EPRINT(ctx, tkc, MC_ERRATA, "undefined '%s': %s => %s", 
			knh_Token_tochar(tku), knh_Token_tochar(tkc), CLASSN(cid));
		return;	
	}
	
	knh_class_t oldcid = knh_NameSpace_getClass(ctx, ns, knh_Token_tobytes(tkc));
	if(oldcid != CLASS_unknown && cid != oldcid) {
		MC_EPRINT(ctx, tkc, MC_INFO, "renaming class: %s => %s", CLASSN(oldcid), CLASSN(cid));
	}

	DEBUG_ASSERT(IS_String(tkc->data));
	knh_NameSpace_setLocalName(ctx, ns, tkc->data, cid);
	
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declc__uint(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *mc = (Cmpl*)v;
	/* ['CLASSTN', 'CURN'] */

	Cmpl *b = (Cmpl*)v;
	Token *tkc = (Token*)stmt->terms[0];
	Token *tku = (Token*)stmt->terms[1];
	DEBUG_ASSERT(IS_Token(tkc)); DEBUG_ASSERT(IS_Token(tku));
	NameSpace *ns = knh_Cmpl_getNameSpace(ctx, b);
	
	knh_class_t cid = knh_tclass_classURN(ctx, CLASS_Int, knh_Token_tobytes(tku));
	if(cid == CLASS_Int) {
		MC_EPRINT(ctx, tkc, MC_ERRATA, "undefined '%s': %s => %s", 
			knh_Token_tochar(tku), knh_Token_tochar(tkc), CLASSN(cid));
		return;	
	}
	
	knh_class_t oldcid = knh_NameSpace_getClass(ctx, ns, knh_Token_tobytes(tkc));
	if(oldcid != CLASS_unknown && cid != oldcid) {
		MC_EPRINT(ctx, tkc, MC_INFO, "renaming class: %s => %s", CLASSN(oldcid), CLASSN(cid));
	}

	DEBUG_ASSERT(IS_String(tkc->data));
	knh_NameSpace_setLocalName(ctx, ns, tkc->data, cid);
	
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declc__ufloat(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['CLASSTN', 'CURN'] */
	Cmpl *b = (Cmpl*)v;
	Token *tkc = (Token*)stmt->terms[0];
	Token *tku = (Token*)stmt->terms[1];
	DEBUG_ASSERT(IS_Token(tkc)); DEBUG_ASSERT(IS_Token(tku));
	NameSpace *ns = knh_Cmpl_getNameSpace(ctx, b);
	
	knh_class_t cid = knh_tclass_classURN(ctx, CLASS_Float, knh_Token_tobytes(tku));
	if(cid == CLASS_Float) {
		MC_EPRINT(ctx, tkc, MC_ERRATA, "undefined '%s': %s => %s", 
			knh_Token_tochar(tku), knh_Token_tochar(tkc), CLASSN(cid));
		return;	
	}
	
	knh_class_t oldcid = knh_NameSpace_getClass(ctx, ns, knh_Token_tobytes(tkc));
	if(oldcid != CLASS_unknown && cid != oldcid) {
		MC_EPRINT(ctx, tkc, MC_INFO, "renaming class: %s => %s", CLASSN(oldcid), CLASSN(cid));
	}

	DEBUG_ASSERT(IS_String(tkc->data));
	knh_NameSpace_setLocalName(ctx, ns, tkc->data, cid);
	
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declc__uint64(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *mc = (Cmpl*)v;
	/* ['CLASSQN', 'CURN'] */
	DEBUG("I'm really waiting for Mr. Hashimoto@NTTLAB");
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declc__ufunc(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *mc = (Cmpl*)v;
	/* ['CLASSQN', 'CURN'] */
	DEBUG("I'm really waiting for Mr. Hashimoto@NTTLAB");
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declc__utable(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *mc = (Cmpl*)v;
	/* ['CLASSQN', 'CURN'] */
	DEBUG("I'm really waiting for Mr. Hashimoto@NTTLAB");
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declc__weave(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *mc = (Cmpl*)v;
	/* ['weave', 'ANY', 'METHODFN'] */
	fprintf(stdout, "weaving %s into %s..\n", knh_Token_tochar((Token*)stmt->terms[1]), knh_Token_tochar((Token*)stmt->terms[2]));
	Method *mtd = knh_Class_getMethod(ctx, CLASS_Amazon, METHODN_placeOrder);
	if(IS_Method(mtd)) {
		String *aspect = ((Token*)stmt->terms[1])->data;
		if(IS_NULL(aspect)) {
			knh_weave(ctx, NULL, mtd);
		}
		else if(knh_String_equals(aspect, STEXT("null"))) {
			knh_weave(ctx, NULL, mtd);
		}	
		else if(knh_String_equals(aspect, STEXT("RBAC"))) {
			knh_weave(ctx, knh_security_RBAC, mtd);
		}
		else if(knh_String_equals(aspect, STEXT("Audit"))) {	
			knh_weave(ctx, knh_security_Audit, mtd);
		}
		else {
			KNH_THROWf(ctx, "NoSuchAspect!!: %s", knh_String_tochar(aspect));
		}
	}
	else{
		DEBUG("what?");
	}
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declc__class(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	Cmpl *b = (Cmpl*)v;
	/* ['class', 'CLASSN', 'CLASSN', 'implements', '{'] */
	Token *tkname = (Token*)stmt->terms[1];
	Token *tke    = (Token*)stmt->terms[1];
	
	char bufn[CLASSNAME_BUFSIZ];
	knh_snprintf(bufn, sizeof(bufn), "%s.%s", NSN(b->nsn), knh_Token_tochar(tkname));
	
	knh_class_t cid = knh_NameSpace_getClass(ctx, knh_Cmpl_getNameSpace(ctx, b), B(bufn));
	if(cid != CLASS_unknown) {
		if(KNH_FLAG_IS(knh_tclass_cflag(cid), KNH_FLAG_CF_STRICT)) {
			knh_Token_setPerrored(tke, 0);
			MC_EPRINT(ctx, tke, MC_ERROR, "you cannot override class %s", bufn);
			knh_Stmt_done(ctx, stmt);
		}
	}
	cid = knh_NameSpace_getClass(ctx, knh_Cmpl_getNameSpace(ctx, b), knh_Token_tobytes(tkname));
	if(cid != CLASS_unknown) {
		MC_EPRINT(ctx, tke, MC_INFO, "renaming %s for %s", knh_Token_tochar(tkname), CLASSN(cid));
	}
	;
	String *cname = new_String__fast(ctx, CLASS_String__class, B(bufn));
	cid = KNH_TCLASS_NEWCLASS(ctx, cname);
	knh_NameSpace_setLocalName(ctx, knh_Cmpl_getNameSpace(ctx, b), cname, cid);
	;
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declc__help(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
//	Cmpl *b = (Cmpl*)v;
	/* ['help', '?ANY'] */
//	Token *tke    = (Token*)stmt->terms[0];
	char *keyword = "konoha";
	if(stmt->size == 2) {
		keyword = knh_Token_tochar(stmt->terms[1]);
	}
	;	
	knh_printf(ctx, KNH_STDOUT, "http://sourceforge.jp/projects/konoha/wiki?%s\n", keyword);
	;
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
