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
	#define DEBUG_STMT2(ctx, stmt)
	#define DEBUG_STMT(ctx, stmt) \
		DEBUG("level=%d", level); \
		knh_Stmt__dump(ctx, stmt, KNH_STDOUT, knh_String_EMPTY()); \
		knh_flush(ctx, KNH_STDOUT); \

#else
	#define DEBUG_STMT(ctx, stmt)
#endif

/* ------------------------------------------------------------------------ */
/* [asm] */

void knh_stmtvisit_asm__class(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
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
			knh_stmtvisit_asm__method(ctx, instmt, v, 1, 0);
		}
		else {
			//DEBUG_STMT(ctx, instmt);
		}
		instmt = instmt->next;
	}
	b->this_cid = prev_cid;
	knh_Stmt_done(ctx, stmt);
	DEBUG_ASSERT(b->this_cid == prev_cid);	
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__method(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['TYPEN', 'METHODFN', 'decl', '?{'] */

	Cmpl *b = (Cmpl*)v;
	DEBUG_ASSERT(stmt->size == 4);
	Method *mtd = ((Token*)stmt->terms[1])->data;
	DEBUG_ASSERT(IS_Method(mtd));
	knh_class_t prev_cid = b->this_cid;
	KNH_SETv(ctx, b->method, mtd);
	b->this_cid = mtd->cid;
	DEBUG("S@@@@");
	knh_Cmpl_startCompilation(ctx, b, ((Token*)stmt->terms[1])->filen);
	DEBUG("E@@@@");
	KNH_ASM_SETLINE(ctx, b, ((Token*)stmt->terms[0])->line);
	knh_Cmpl_initMethodParams(ctx, b, stmt, mtd->cid);
	
	DEBUG_ASSERT(IS_Stmt(stmt->terms[3]));
	knh_Cmpl_initLocalVariables(ctx, b, stmt->terms[3]);
	knh_Stmt_visit(ctx, stmt->terms[3], knh_stmtvisit_asm, v, level+1);
	knh_Cmpl_endCompilation(ctx, b);
	b->this_cid = prev_cid;
	
	//knh_Stmt_done(ctx, stmt);

}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declv__if(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['if', 'expr', '{', '{'] */
	if(level > 1) {
		knh_Stmt_visit(ctx, stmt->terms[2], knh_stmtvisit_declv, v, level+1);
		knh_Stmt_visit(ctx, stmt->terms[3], knh_stmtvisit_declv, v, level+1);
	}
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__if(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['if', 'expr', '{', '{'] */
	Cmpl *b = (Cmpl*)v;
	knh_Stmt_terms_seval(ctx, stmt, 1, CLASS_Bool, knh_Cmpl_getNameSpace(ctx, b));
	knh_asmv_t cnd = knh_Cmpl_asmv(ctx, b, stmt->terms[1], TYPE_Bool, MC_FIRST);

	if(cnd.potype == KNH_ASMV_OBJ) {
		if(IS_TRUE(cnd.value)) {
			knh_Stmt_visit(ctx, stmt->terms[2], knh_stmtvisit_asm, v, level+1);
		}
		else {
			knh_Stmt_visit(ctx, stmt->terms[3], knh_stmtvisit_asm, v, level+1);
		}
		knh_Stmt_done(ctx, stmt);
		return; 
	}

	char lbelse[LABEL_BUFSIZ];
	knh_snprintf(lbelse, sizeof(lbelse), "_ELSE_%d", knh_Cmpl_llstep(b));
	char lbend[LABEL_BUFSIZ];
	knh_snprintf(lbend, sizeof(lbend), "_END_%d", knh_Cmpl_llstep(b));
	
	/* if */
	KNH_ASM_JMP_IFF(ctx, (Cmpl*)v, B(lbelse), cnd);
	knh_Stmt_visit(ctx, stmt->terms[2], knh_stmtvisit_asm, v, level+1);
	KNH_ASM_JMP(ctx, (Cmpl*)v, B(lbend));

	/* else */
	KNH_ASM_LABEL__b(ctx, (Cmpl*)v, B(lbelse));
	knh_Stmt_visit(ctx, stmt->terms[3], knh_stmtvisit_asm, v, level+1);
	/* endif */
	KNH_ASM_LABEL__b(ctx, (Cmpl*)v, B(lbend));
	
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declv__while(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['while', 'expr', '{'] */
	if(level > 1) {
		knh_Stmt_visit(ctx, stmt->terms[2], knh_stmtvisit_declv, v, level+1);
	}
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__while(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *mc = (Cmpl*)v;
	/* ['while', 'expr', '{'] */

	Cmpl *b = (Cmpl*)v;

	String *label = knh_Cmpl_lstack_label(ctx, b);
	DEBUG_ASSERT(label != NULL);
	DEBUG("while label='%s'", knh_String_tochar(label));
	KNH_ASM_LABEL__b(ctx, b, knh_String_tobytes(label));
	
	knh_Stmt_terms_seval(ctx, stmt, 1, CLASS_Bool, knh_Cmpl_getNameSpace(ctx, b));
	knh_asmv_t cnd = knh_Cmpl_asmv(ctx, b, stmt->terms[1], TYPE_Bool, MC_FIRST);

	char lbend[LABEL_BUFSIZ];
	knh_snprintf(lbend, sizeof(lbend), "_END_%s", knh_String_tochar(label));

	if(cnd.potype == KNH_ASMV_OBJ) {
		if(IS_TRUE(cnd.value)) {  /* infinite loop */
			knh_Stmt_visit(ctx, stmt->terms[2], knh_stmtvisit_asm, v, level+1);
			KNH_ASM_JMP(ctx, (Cmpl*)v, knh_String_tobytes(label));
		}
		else { /* no loop */
			KNH_ASM_JMP(ctx, (Cmpl*)v, B(lbend));
		}
	}
	else {
		/* while */
		KNH_ASM_JMP_IFF(ctx, (Cmpl*)v, B(lbend), cnd);
		knh_Stmt_visit(ctx, stmt->terms[2], knh_stmtvisit_asm, v, level+1);
		KNH_ASM_JMP(ctx, (Cmpl*)v, knh_String_tobytes(label));
	}
	/* end */
	KNH_ASM_LABEL__b(ctx, (Cmpl*)v, B(lbend));
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declv__do(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['do', '{', 'while', 'expr'] */
	if(level > 1) {
		knh_Stmt_visit(ctx, stmt->terms[1], knh_stmtvisit_declv, v, level+1);
	}
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__do(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *mc = (Cmpl*)v;
	/* ['do', '{', 'while', 'expr'] */

	Cmpl *b = (Cmpl*)v;

	String *label = knh_Cmpl_lstack_label(ctx, b);
	DEBUG_ASSERT(label != NULL);
	KNH_ASM_LABEL__b(ctx, b, knh_String_tobytes(label));

	/* loop */
	knh_Stmt_visit(ctx, stmt->terms[1], knh_stmtvisit_asm, v, level+1);
	
	knh_Stmt_terms_seval(ctx, stmt, 3, CLASS_Bool, knh_Cmpl_getNameSpace(ctx, b));
	knh_asmv_t cnd = knh_Cmpl_asmv(ctx, b, stmt->terms[3], TYPE_Bool, MC_FIRST);

	if(cnd.potype == KNH_ASMV_OBJ) {
		if(IS_TRUE(cnd.value)) {  /* infinite loop */
			KNH_ASM_JMP(ctx, b, knh_String_tobytes(label));
		}
		else { /* no loop */
//			KNH_ASM_JMP(ctx, b, B(lbend));
		}
	}
	else {
		/* while */
		KNH_ASM_JMP_IFT(ctx, (Cmpl*)v, knh_String_tobytes(label), cnd);
	}

	/* end */
	char lbend[LABEL_BUFSIZ];
	knh_snprintf(lbend, sizeof(lbend), "_END_%s", knh_String_tochar(label));
	KNH_ASM_LABEL__b(ctx, (Cmpl*)v, B(lbend));
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declv__for(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['for', 'expr', 'expr', 'expr', '{'] */
	if(level > 1) {
		if(IS_Stmt(stmt->terms[1])) {
			knh_Stmt_visit(ctx, stmt->terms[1], knh_stmtvisit_declv, v, level+1);
		}
		knh_Stmt_visit(ctx, stmt->terms[4], knh_stmtvisit_declv, v, level+1);
	}
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__for(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *mc = (Cmpl*)v;
	/* ['for', 'expr', 'expr', 'expr', '{'] */

	Cmpl *b = (Cmpl*)v;

	String *label = knh_Cmpl_lstack_label(ctx, b);
	DEBUG_ASSERT(label != NULL);
	DEBUG("for label='%s'", knh_String_tochar(label));
	//KNH_ASM_LABEL__b(ctx, b, knh_String_tobytes(label));

	/* i = 1 part */
	knh_Stmt_visit(ctx, stmt->terms[1], knh_stmtvisit_asm, v, level+1);
	char lbredo[LABEL_BUFSIZ];
	knh_snprintf(lbredo, sizeof(lbredo), "_REDO_%s", knh_String_tochar(label));
	KNH_ASM_JMP(ctx, b, B(lbredo)); /* GOTO REDO */

	/* i++ part */
	KNH_ASM_LABEL__b(ctx, b, knh_String_tobytes(label)); /* CONTINUE */
	knh_Stmt_visit(ctx, stmt->terms[3], knh_stmtvisit_asm, v, level+1);

	/* i < 10 part */
	KNH_ASM_LABEL__b(ctx, b, B(lbredo)); /* REDO */
	knh_Stmt_terms_seval(ctx, stmt, 2, CLASS_Bool, knh_Cmpl_getNameSpace(ctx, b));
	knh_asmv_t cnd = knh_Cmpl_asmv(ctx, b, stmt->terms[2], TYPE_Bool, MC_FIRST);

	char lbend[LABEL_BUFSIZ];
	knh_snprintf(lbend, sizeof(lbend), "_END_%s", knh_String_tochar(label));

	if(cnd.potype == KNH_ASMV_OBJ) {
		if(IS_TRUE(cnd.value)) {  /* infinite loop */
			knh_Stmt_visit(ctx, stmt->terms[4], knh_stmtvisit_asm, v, level+1);
			KNH_ASM_JMP(ctx, (Cmpl*)v, knh_String_tobytes(label));  /* GOTO CONTINUE */
		}
		else { /* no loop */
			KNH_ASM_JMP(ctx, (Cmpl*)v, B(lbend));
		}
	}
	else {
		/* loop */
		KNH_ASM_JMP_IFF(ctx, b, B(lbend), cnd);
		knh_Stmt_visit(ctx, stmt->terms[4], knh_stmtvisit_asm, v, level+1);
		KNH_ASM_JMP(ctx, (Cmpl*)v, knh_String_tobytes(label));
	}
	/* end */
	KNH_ASM_LABEL__b(ctx, (Cmpl*)v, B(lbend));
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declv__foreach(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['foreach', 'decl', 'FIELDN', 'expr', 'expr', '{'] */
	if(level > 1) {
		knh_Stmt_visit(ctx, stmt->terms[1], knh_stmtvisit_declv, v, level+1);
		knh_Stmt_visit(ctx, stmt->terms[5], knh_stmtvisit_declv, v, level+1);
		Cmpl *b = (Cmpl*)v;
		knh_Cmpl_declareVariable(ctx, b, (Token*)stmt->terms[0], 0, CLASS_any, knh_tfieldn_level(ctx, level), KNH_NULL);
	}
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__foreach(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	Cmpl *b = (Cmpl*)v;
	NameSpace *ns = knh_Cmpl_getNameSpace(ctx, b);

	String *label = knh_Cmpl_lstack_label(ctx, b);
	DEBUG_ASSERT(label != NULL);

	/* ['foreach', 'decl', 'FIELDN', 'expr', 'expr', '{'] */
	
	knh_Stmt_terms_seval(ctx, stmt, 2, CLASS_any, ns);
	knh_asmv_t name = knh_Cmpl_asmv(ctx, b, stmt->terms[2], TYPE_any, MC_FIRST);
	if(name.potype != KNH_ASMV_SFP) {
		MC_EPRINT(ctx, (Token*)stmt->terms[2], MC_ERROR, "local variable only");
		knh_Stmt_done(ctx, stmt);
		return;	
	}

	knh_index_t itr_sfp = knh_Cmpl_indexOfVariable(b, knh_tfieldn_level(ctx, level));
	DEBUG_ASSERT(itr_sfp != -1);
	
	knh_Stmt_terms_seval(ctx, stmt, 3, CLASS_any, ns);
	knh_asmv_t iter = knh_Cmpl_asmv(ctx, b, stmt->terms[3], TYPE_any, MC_FIRST);
	KNH_ASM_MOVS(ctx, b, itr_sfp, iter);
	KNH_ASM_ITER(ctx, b, name.type, itr_sfp);

	KNH_ASM_LABEL__b(ctx, b, knh_String_tobytes(label));
	char lbend[LABEL_BUFSIZ];
	knh_snprintf(lbend, sizeof(lbend), "_END_%s", knh_String_tochar(label));

	KNH_ASM_FOREACH(ctx, b, B(lbend), TYPE_TONOTNULL(name.type), name.index, itr_sfp);
	knh_Stmt_visit(ctx, stmt->terms[5], knh_stmtvisit_asm, v, level+1);
	KNH_ASM_JMP(ctx, (Cmpl*)v, knh_String_tobytes(label));

	/* end */
	KNH_ASM_LABEL__b(ctx, (Cmpl*)v, B(lbend));

	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__continue(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['continue', '?LABEL'] */
	Cmpl *b = (Cmpl*)v;
	Token *tke = (Token*)stmt->terms[0];
	
	String *label = knh_Cmpl_lstack_label(ctx, b);
	if(label == NULL) {
		MC_EPRINT(ctx, tke, MC_ERROR, "outside loop/switch");
		knh_Stmt_done(ctx, stmt);
		return;
	}
	if(stmt->size == 2) {
		label = knh_Term_getString(stmt->terms[1]);
		DEBUG("continue %s", knh_String_tochar(label));
	}

	if(!knh_Cmpl_hasBreakLabel(ctx, b, knh_String_tobytes(label))) {
		MC_EPRINT(ctx, tke, MC_ERROR, "unknown label: continue %s", knh_String_tochar(label));
	}
	else {
		KNH_ASM_JMP(ctx, b, knh_String_tobytes(label));
	}
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__break(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['break', '?LABEL'] */
	Cmpl *b = (Cmpl*)v;
	Token *tke = (Token*)stmt->terms[0];
	
	String *label = knh_Cmpl_lstack_label(ctx, b);
	if(label == NULL) {
		MC_EPRINT(ctx, tke, MC_ERROR, "outside loop/switch");
		knh_Stmt_done(ctx, stmt);
		return;
	}
	if(stmt->size == 2) {
		label = knh_Term_getString(stmt->terms[1]);
		DEBUG("break %s", knh_String_tochar(label));
	}

	if(!knh_Cmpl_hasBreakLabel(ctx, b, knh_String_tobytes(label))) {
		MC_EPRINT(ctx, tke, MC_ERROR, "unknown label: break %s", knh_String_tochar(label));
	}
	else {
		char lb[LABEL_BUFSIZ];
		knh_snprintf(lb, sizeof(lb), "_END_%s", knh_String_tochar(label));
		KNH_ASM_JMP(ctx, b, B(lb));
	}
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__goto(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['goto', 'LABEL'] */
	Cmpl *b = (Cmpl*)v;
	Token *tke = (Token*)stmt->terms[0];

	DEBUG_ASSERT(stmt->size == 2);
	String *label = knh_Term_getString(stmt->terms[1]);

	if(!knh_Cmpl_hasGlobalLabel(ctx, b, knh_String_tobytes(label))) {
		MC_EPRINT(ctx, tke, MC_ERROR, "unknown goto label: %s", knh_String_tochar(label));
		knh_Cmpl_stopCompilation(ctx, b);
	}
	else {
		KNH_ASM_JMP(ctx, b, knh_String_tobytes(label));
	}
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declv__try(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['try', '{', '__catch', '{'] */

	if(level > 1) {
		knh_Stmt_visit(ctx, stmt->terms[1], knh_stmtvisit_declv, v, level+1);
		TODO();
		knh_Stmt_visit(ctx, stmt->terms[3], knh_stmtvisit_declv, v, level+1);
	}
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__try(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *mc = (Cmpl*)v;
	/* ['try', '{', '__catch', '{'] */

	//knh_Stmt_dispatch(ctx, stmt, knh_stmtvisit_asm, v, level, step);
	//knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__catch(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *mc = (Cmpl*)v;
	/* ['catch', 'EXPTN', 'FIELDN', '{'] */

	//knh_Stmt_dispatch(ctx, stmt, knh_stmtvisit_asm, v, level, step);
	//knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__throw(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['throw', 'expr'] */
	DEBUG_ASSERT(stmt->size == 2);
	Cmpl *b = (Cmpl*)v;
	Token *tke = (Token*)stmt->terms[0];
	
	knh_Stmt_terms_seval(ctx, stmt, 1, CLASS_Exception, knh_Cmpl_getNameSpace(ctx, b));
	knh_asmv_t e = knh_Cmpl_asmv(ctx, b, stmt->terms[1], TYPE_Exception, MC_FIRST);
	knh_class_t cid = TYPE_TONOTNULL(e.type);
	if(cid != CLASS_Exception && cid != CLASS_String && cid != CLASS_Nue) {
		MC_EPRINT(ctx, tke, MC_TYPE, "incompatible exception: %s%s", CLASSQN(cid));
	}
	KNH_ASM_THROW(ctx, b, e);
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__return(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['return', '?expr'] */
	Cmpl *b = (Cmpl*)v;
	Token *tke = (Token*)stmt->terms[0];

	knh_type_t rtype = knh_Method_rtype(b->method);
	if(rtype == TYPE_void) {
		if(stmt->size == 2) {
			MC_EPRINT(ctx, tke, MC_IGNORED, "not necessary return value");
		}	
		KNH_ASM_RET_VOID(ctx, b);
		return;
	}
	if(stmt->size == 1) {
		Object *v = knh_Method_returnValue(ctx, b->method);
		if(TYPE_ISNOTNULL(rtype) && IS_NULL(v)) {
			MC_EPRINT(ctx, tke, MC_WARNING, "return something else");
			KNH_ASM_NULLCHK__OBJ(ctx, b, v);
		}
		KNH_ASM_RET__OBJ(ctx, b, v);
		return;
	}
	knh_Stmt_terms_seval(ctx, stmt, 1, TYPE_TONOTNULL(rtype), knh_Cmpl_getNameSpace(ctx, b));
	knh_asmv_t rv = knh_Cmpl_asmv(ctx, b, stmt->terms[1], rtype, MC_FIRST);
	rv = KNH_ASM_TYPECHECK__asmv(ctx, b, tke, 0, rtype, rv, knh_Token_isTailC(tke));
	KNH_ASM_RET(ctx, b, rv);
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__eval(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *b = (Cmpl*)v;
	/* ['eval', 'expr'] */

	//knh_Stmt_dispatch(ctx, stmt, knh_stmtvisit_asm, v, level, step);
	//knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__print(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	Cmpl *b = (Cmpl*)v;
	/* ['print', '+expr'] */
	
	int i;
	for(i = 1; i < stmt->size - 1; i++) {
		knh_Stmt_terms_seval(ctx, stmt, i, CLASS_any, knh_Cmpl_getNameSpace(ctx, b));
		knh_asmv_t vv = knh_Cmpl_asmv(ctx, b, stmt->terms[i], TYPE_any, MC_FIRST);
		KNH_ASM_PRINT(ctx, b, 0, METHODN__s, vv);
	}
	
	knh_flag_t pflag = 0;
	if(knh_Stmt_isPrintLine(stmt)) {
		pflag |= KNH_FLAG_PF_LINEFEED;
	}
	if(stmt->size == 1) {
		KNH_ASM_PRINT__OBJ(ctx, b, pflag, METHODN__s, knh_String_EMPTY());
	}
	else {
		knh_Stmt_terms_seval(ctx, stmt, stmt->size-1, CLASS_any, knh_Cmpl_getNameSpace(ctx, b));
		knh_asmv_t vv = knh_Cmpl_asmv(ctx, b, stmt->terms[stmt->size-1], TYPE_any, MC_FIRST);
		KNH_ASM_PRINT(ctx, b, pflag, METHODN__s, vv);
	}
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__assert(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *mc = (Cmpl*)v;
	/* ['assert', 'expr'] */

	//knh_Stmt_dispatch(ctx, stmt, knh_stmtvisit_asm, v, level, step);
	//knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOV(Ctx *ctx, Cmpl *b, knh_asmv_t n, knh_asmv_t v)
{
	if(n.potype == KNH_ASMV_EBP) {
		KNH_ASM_MOVE(ctx, b, n.index, v);
		return;
	}
	if(n.potype == KNH_ASMV_SFP) {
		KNH_ASM_MOVS(ctx, b, n.index, v);
		return;
	}
	if(n.potype == KNH_ASMV_OFP) {
		KNH_ASM_MOVO(ctx, b, n.index, v);
		return;
	}
	
	DEBUG_ASSERT(ctx == NULL);  /* this can be happen */
	return;
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__let(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *mc = (Cmpl*)v;   /* ['FIELDN', 'expr'] */

	Token *tke = (Token*)stmt->terms[0];

	knh_asmv_t n = knh_Cmpl_asmv(ctx, (Cmpl*)v, stmt->terms[0], TYPE_any, MC_FIRST);
	knh_Stmt_terms_seval(ctx, stmt, 1, TYPE_TONOTNULL(n.type), knh_Cmpl_getNameSpace(ctx, (Cmpl*)v));
	knh_asmv_t val = knh_Cmpl_asmv(ctx, (Cmpl*)v, stmt->terms[1], TYPE_any, MC_FIRST);
	val = KNH_ASM_TYPECHECK__asmv(ctx, (Cmpl*)v, tke, 0, n.type, val, 0);
	KNH_ASM_MOV(ctx, (Cmpl*)v, n, val);
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__call(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *mc = (Cmpl*)v;
	/* ['METHODN', '+expr'] */

	knh_Cmpl_asmv(ctx, (Cmpl*)v, stmt, TYPE_any, MC_FIRST);
	knh_Stmt_done(ctx, stmt);
}


#define _knh_stmtvisit_asm__op           knh_stmtvisit_asm__call
#define _knh_stmtvisit_asm__new          knh_stmtvisit_asm__call
#define _knh_stmtvisit_asm__map          knh_stmtvisit_asm__call
#define _knh_stmtvisit_asm__movtext      knh_stmtvisit_asm__call

#define _knh_stmtvisit_asm__alt          knh_stmtvisit_asm__call
#define _knh_stmtvisit_asm__and          knh_stmtvisit_asm__call
#define _knh_stmtvisit_asm__or           knh_stmtvisit_asm__call
#define _knh_stmtvisit_asm__trinary      knh_stmtvisit_asm__call
#define _knh_stmtvisit_asm__next         knh_stmtvisit_asm__call

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_asm__err(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	/* ['ERR'] */
	Cmpl *b = (Cmpl*)v;
	
	Token *tke = (Token*)stmt->terms[0];
	DEBUG_ASSERT(IS_Token(tke));
	DEBUG("SyntaxError!!: %s", knh_Token_tochar(tke));
		
	char buf[CLASSNAME_BUFSIZ*2];
	knh_snprintf(buf, sizeof(buf), "SyntaxError!!:[%s:%d]: %s", FILEN(tke->filen), (int)tke->line, knh_Token_tochar(tke));
	
	KNH_ASM_THROW__OBJ(ctx, b, new_Exception__b(ctx, B(buf)));
	knh_Cmpl_setSyntaxError(b, 1);
	knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
