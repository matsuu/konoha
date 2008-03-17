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
	#define DEBUG_STMT(ctx, stmt)
	#define DEBUG_STMT0(ctx, stmt) \
		DEBUG("level=%d", level); \
		knh_Stmt__dump(ctx, stmt, KNH_STDOUT, knh_String_EMPTY()); \
		knh_flush(ctx, KNH_STDOUT); \

#else
	#define DEBUG_STMT(ctx, stmt)
#endif

/* ------------------------------------------------------------------------ */
/* [declm] */

void knh_stmtvisit_declm__class(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	/* ['class', 'CLASSN', 'CLASSN', 'implements', '{'] */
	//DEBUG_STMT(ctx, stmt);
	Cmpl *b = (Cmpl*)v;
	NameSpace *ns = knh_Cmpl_getNameSpace(ctx, b);
	
	
	knh_class_t prev_cid = b->this_cid;
	b->this_cid = knh_Token_toclass(ctx, (Token*)stmt->terms[1], CLASS_Object, ns);

	Stmt *instmt = (Stmt*)stmt->terms[4];
	DEBUG_ASSERT(IS_Stmt(instmt));
	while(IS_Stmt(instmt)) {
		if(instmt->stt == STT_METHOD) {
			knh_stmtvisit_declm__method(ctx, instmt, v, 1, 0);
		}
		else {
			//DEBUG_STMT(ctx, instmt);
		}
		instmt = instmt->next;
	}
	b->this_cid = prev_cid;
	DEBUG_ASSERT(b->this_cid == prev_cid);	
}

/* ------------------------------------------------------------------------ */

void
knh_Cmpl_initMethodParams(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_class_t cid)
{
	/* ['TYPEN', 'METHODFN', 'decl', '?{'] */
	knh_Cmpl_initDecl(ctx, b);
	knh_Cmpl_initThisVariable(ctx, b, cid);

	Stmt *instmt = (Stmt*)stmt->terms[2];
	DEBUG_ASSERT(IS_Stmt(instmt));
	while(IS_Stmt(instmt)) {
		if(instmt->stt == STT_DECL) {
			knh_stmtvisit_declv__decl(ctx, instmt, b, -1, 0);
		}
		else if(instmt->stt == STT_DONE) {
			;
		}
		else {
//			DEBUG_STMT(ctx, instmt);
		}
		instmt = instmt->next;
	}
}

/* ------------------------------------------------------------------------ */

knh_class_t knh_Cmpl_getMethodClass(Ctx *ctx, Cmpl *b, Token *tk, int level)
{
	DEBUG_ASSERT(IS_Token(tk));
	knh_bytes_t name = knh_Token_tobytes(tk);
	knh_index_t idx = knh_bytes_rindex(name, '.');
	if(idx != -1) {
		name = knh_bytes_first(name, idx);
		knh_class_t cid = knh_NameSpace_getClass(ctx, knh_Cmpl_getNameSpace(ctx, b), name);
		if(level == 0) {
			if(cid == CLASS_unknown) {
				MC_EPRINT(ctx, tk, MC_ERRATA, "%s => %s", name.buf, CLASSN(b->this_cid));
				return b->this_cid;
			}
		}
		else {
			if(cid != b->this_cid) {
				MC_EPRINT(ctx, tk, MC_ERROR, "%s => %s", name.buf, CLASSN(b->this_cid));
				return b->this_cid;
			}
		}
		return cid;
	}
	return b->this_cid;
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declm__method(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	/* ['TYPEN', 'METHODFN', 'decl', '?{'] */
	//DEBUG_STMT(ctx, stmt);
	Cmpl *b = (Cmpl*)v;
	Token *tke = (Token*)stmt->terms[1];
	NameSpace *ns = knh_Cmpl_getNameSpace(ctx, b);
	
	if(tke->tt == TT_ASIS) {
		if(level == 1) {
			KNH_SETv(ctx, tke->data, new_String__fast(ctx, CLASS_String, STEXT("new")));
		}
		else {
			KNH_SETv(ctx, tke->data, new_String__fast(ctx, CLASS_String, STEXT("lambda")));
		}
		tke->tt = TT_NAME;
	}

	knh_flag_t flag = knh_Stmt_metaflag__method(ctx, stmt);
	knh_class_t cid  = knh_Cmpl_getMethodClass(ctx, b, (Token*)stmt->terms[1], level);
	knh_type_t rtype = knh_Token_totype(ctx, (Token*)stmt->terms[0], CLASS_any, ns);

	knh_Cmpl_initMethodParams(ctx, b, stmt, cid);
	knh_methodn_t mn = knh_Token_tomethodn(ctx, (Token*)stmt->terms[1]);
	
	if(knh_methodn_isNew(mn) && cid != TYPE_TONOTNULL(rtype)) {
		rtype = (TYPE_ISNULLABLE(rtype)) ? CLASS_TONULLABLE(rtype) : rtype;
		MC_EPRINT(ctx, tke, MC_ERRATA, "illegal constructor type: %s ==> %T", knh_Token_tochar((Token*)stmt->terms[0]), rtype);
	}
	
	Method *mtd = knh_Class_getMethod(ctx, cid, mn);
	if(IS_NOTNULL(mtd)) {
		if(mtd->cid == cid) {
			if(knh_Method_isGenerated(mtd)) {
				knh_Method_setGenerated(mtd, 0);
			}
			else {
				MC_EPRINT(ctx, tke, MC_INFO, "redefinition of method: %s", knh_Token_tochar(tke));
			}
		}
		else {
			if(knh_Method_isFinal(mtd)) {
				MC_EPRINT(ctx, tke, MC_ERROR, "cannot override: %s", knh_Token_tochar(tke));
				knh_Stmt_done(ctx, stmt);
				return;
			}
			MC_EPRINT(ctx, tke, MC_INFO, "override method: %s", knh_Token_tochar(tke));
			Method *newmtd = new_Method(ctx, flag, cid, mn, NULL);
			KNH_SETv(ctx, newmtd->mf, mtd->mf);
			mtd = newmtd;
			KNH_SETv(ctx, b->method, mtd); /* avoid gc */
		}
	}
	else {
		mtd = new_Method(ctx, flag, cid, mn, NULL);
		KNH_SETv(ctx, b->method, mtd);  /* avoid gc */
	}
	
	int i;
	MethodField *mf = mtd->mf;
	if(IS_NULL(mf)) {
		mf = new_MethodField(ctx, flag, b->vars_size);
		mf->params[0].type = rtype;
		mf->params[0].fn   = FIELDN_return;
		for(i = 1; i < b->vars_size; i++) {
			mf->params[i].type = b->vars[i].type;
			mf->params[i].fn = b->vars[i].fn;
		}
		KNH_SETv(ctx, mtd->mf, mf);
	}
	else {
		if(knh_Method_isVarArgs(mtd)) {
			TODO();
		}
		if(mf->params[0].type != rtype) {
			MC_EPRINT(ctx, tke, MC_ERROR, "redifinition of method: different return type: %s", knh_Token_tochar(tke));
			knh_Stmt_done(ctx, stmt);
			return;
		}
		if(b->vars_size != mf->size) {
			MC_EPRINT(ctx, tke, MC_ERROR, "redifinition of method: different parameter size: %s", knh_Token_tochar(tke));
			knh_Stmt_done(ctx, stmt);
			return;
		}
		for(i = 1; i < b->vars_size; i++) {
			if(mf->params[i].type != b->vars[i].type) {
				MC_EPRINT(ctx, tke, MC_ERROR, "redifinition of method: different parameter: %s(.. %s%s %s ..)", 
					knh_Token_tochar(tke), TYPEQN(mf->params[i].type), FIELDN(mf->params[i].fn));
				knh_Stmt_done(ctx, stmt);
				return;
			}
		}
	}
	/* ['TYPEN', 'METHODFN', 'decl', '?{'] */
	knh_Class_addMethod(ctx, cid, mtd);
	if(stmt->size == 3) {
		//DEBUG("abstract");
		knh_Stmt_done(ctx, stmt);
	}
	else {
		knh_Token_setRAW(ctx, (Token*)stmt->terms[1], mtd);
	}
//	DEMO_DUMP(ctx, mtd, "** method **");
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
