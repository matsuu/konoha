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
/* [declv] */

void knh_stmtvisit_declv__class(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	DEBUG_ASSERT(stmt->stt == STT_CLASS);
	/* ['class', 'CLASSN', 'CLASSN', 'implements', '{'] */
	//DEBUG_STMT(ctx, stmt);

	Cmpl *mc = (Cmpl*)v;
	Token *tke = (Token*)stmt->terms[1];
	knh_class_t prev_cid = mc->this_cid;
	mc->this_cid = knh_Token_toclass(ctx, (Token*)stmt->terms[1], CLASS_Object, knh_Cmpl_getNameSpace(ctx, mc));
	knh_Cmpl_initDecl(ctx, mc);

	Stmt *instmt = (Stmt*)stmt->terms[4];
	DEBUG_ASSERT(IS_Stmt(instmt));
	while(IS_Stmt(instmt)) {
		if(instmt->stt == STT_DECL) {
			knh_stmtvisit_declv__decl(ctx, instmt, v, 1, 0);
		}
		else if(instmt->stt == STT_LET) {
			knh_stmtvisit_declv__let(ctx, instmt, v, 1, 0);
		}
		else if(instmt->stt == STT_METHOD) {
			;
		}
		else if(instmt->stt == STT_DONE) {
			;
		}
		else {
			DEBUG_STMT(ctx, instmt);
		}
		instmt = instmt->next;
	}

	knh_flag_t flag = knh_Stmt_metaflag__class(ctx, stmt);
	knh_class_t supcid = knh_Token_toclass(ctx, (Token*)stmt->terms[2], CLASS_Object, knh_Cmpl_getNameSpace(ctx, mc));
	knh_Cmpl_declareClass(ctx, mc, tke, flag, mc->this_cid, supcid);
	
	mc->this_cid = prev_cid;
	//knh_Stmt_dispatch(ctx, stmt, knh_stmtvisit_declv, v, level, step);
	//knh_Stmt_done(ctx, stmt);
	DEBUG_ASSERT(mc->this_cid == prev_cid);	
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declv__method(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	//DEBUG_STMT(ctx, stmt);
	//Cmpl *mc = (Cmpl*)v;
	/* ['method', 'TYPEN', 'METHODFN', 'decl', '?{'] */

	//knh_Stmt_dispatch(ctx, stmt, knh_stmtvisit_declv, v, level, step);
	//knh_Stmt_done(ctx, stmt);
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declv__decl(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	/* ['TYPEN', 'FIELDN', expr] or [_, n, _] */
	DEBUG_STMT(ctx, stmt);

	Cmpl *b = (Cmpl*)v;
	Token *tke = (Token*)stmt->terms[1];

	knh_fieldn_t fnq = knh_Token_tofieldn(ctx, (Token*)stmt->terms[1]);
	knh_fieldn_t fn = FIELDN_UNMASK(fnq);
	
	knh_flag_t flag = knh_Stmt_metaflag__field(ctx, stmt);
	knh_type_t type = knh_Token_totype(ctx, (Token*)stmt->terms[0], CLASS_any, knh_Cmpl_getNameSpace(ctx, b));

	int isasis = (((Token*)stmt->terms[2])->tt == TT_ASIS) ? 1: 0;
	knh_Stmt_terms_seval(ctx, stmt, 2, TYPE_TONOTNULL(type), knh_Cmpl_getNameSpace(ctx, b));
	Object *value = knh_Term_value_ifStaticValue(stmt->terms[2]);
	value = knh_typesystem_doCoercion(ctx, type, value);
	

	if(level == 0) {  /* GLOBAL */
		flag = flag | KNH_FLAG_CFF_GETTER | KNH_FLAG_CFF_SETTER;
		if(FIELDN_IS_U1(fnq) && FIELDN_IS_U2(fnq)) {
			flag |= KNH_FLAG_CFF_PROTECTED;
		}
		if(IS_NULL(value) && TYPE_ISNOTNULL(type)) {
			if(knh_tclass_hasDefaultValue(type)) {
				value = knh_tclass_safevalue(ctx, type);
			}
			else {
				MC_EPRINT(ctx, tke, MC_ERRATA, "no default value: %s%s => %s%s", TYPEQN(type), CLASSQN(type));
				type = CLASS_TONULLABLE(type);
			}
		}
		knh_Cmpl_declareGlobalVariable(ctx, b, tke, flag, type, fn, isasis, value);
	}
	else if(level == 1) {
		if(FIELDN_IS_U1(fnq)) {
			flag |= KNH_FLAG_CFF_PROTECTED;
		}
		else {
			flag |= KNH_FLAG_CFF_GETTER | KNH_FLAG_CFF_SETTER;
		}
		if(FIELDN_IS_U2(fnq)) {
			MC_EPRINT(ctx, tke, MC_IGNORED, "you cann't declare global variable HERE: %s", knh_Token_tochar(tke));
			knh_Stmt_done(ctx, stmt);
			return;
		}
		knh_Cmpl_declareVariable(ctx, b, tke, flag, type, fn, value);
	}
	else {
		if(FIELDN_IS_U1(fnq)) {
			MC_EPRINT(ctx, tke, MC_IGNORED, "you cann't declare field variable HERE: %s", knh_Token_tochar(tke));
			knh_Stmt_done(ctx, stmt);
			return;
		}
		if(FIELDN_IS_U2(fnq)) {
			MC_EPRINT(ctx, tke, MC_IGNORED, "you cann't declare global variable HERE: %s", knh_Token_tochar(tke));
			knh_Stmt_done(ctx, stmt);
			return;
		}
		knh_Cmpl_declareVariable(ctx, b, tke, flag, type, fn, value);
	}
	
	if(knh_Term_isStaticValue(stmt->terms[2])) {
		if(level != -1) {
			knh_Stmt_done(ctx, stmt);
		}
		return;
	}
	if(!isasis) {
		DEBUG("switching .. DECL => LET");
		stmt->stt = STT_LET;
		KNH_SETv(ctx, stmt->terms[0], stmt->terms[1]);
		KNH_SETv(ctx, stmt->terms[1], stmt->terms[2]);
		KNH_SETv(ctx, stmt->terms[2], KNH_NULL);
		stmt->size = 2;
	}
	else {
		knh_Stmt_done(ctx, stmt);
	}
}

/* ------------------------------------------------------------------------ */

void knh_stmtvisit_declv__let(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
	DEBUG_STMT(ctx, stmt);
	Cmpl *b = (Cmpl*)v;
	/* ['name', 'expr'] */
	knh_flag_t flag = KNH_FLAG_CFF_AUTONAME;
	knh_fieldn_t fnq = knh_Token_tofieldn(ctx, (Token*)stmt->terms[0]);
	knh_fieldn_t fn = FIELDN_UNMASK(fnq);

	knh_Stmt_terms_seval(ctx, stmt, 1, CLASS_any, knh_Cmpl_getNameSpace(ctx, b));
	Object *value = knh_Term_value_ifStaticValue(stmt->terms[1]);
	Token *tke = (Token*)stmt->terms[0];
	
	if(level == 0) {
		if(knh_Cmpl_indexOfGlobalVariable(b, fnq) != -1) {
			return ;
		}
		flag |= KNH_FLAG_CFF_GETTER | KNH_FLAG_CFF_SETTER;
		if(FIELDN_IS_U2(fnq)) {
			flag |= KNH_FLAG_CFF_PROTECTED;
		}
		knh_Cmpl_declareGlobalVariable(ctx, b, tke, flag, TYPE_any, fn, 0, value);
	}
	else if(level == 1) {
		MC_EPRINT(ctx, tke, MC_IGNORED, "implicit field declaration is not allowed");
		knh_Stmt_done(ctx, stmt);
		return;
	}
	else {
		if(FIELDN_IS_U1(fnq) || FIELDN_IS_U2(fnq)) {
			return;
		}
		if(knh_Cmpl_existsName(b, fnq)) {
			return;
		}
		knh_Cmpl_declareVariable(ctx, b, tke, flag, TYPE_any, fn, value);
	}
	
//	if(knh_Term_isStaticValue(stmt->terms[1])) {
//		knh_Stmt_done(ctx, stmt);
//	}

}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
