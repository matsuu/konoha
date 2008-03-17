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

/* ======================================================================== */
/* [run] */

void knh_Cmpl_prepareRun(Ctx *ctx, Cmpl *b, Stmt *stmt)
{
	DEBUG_ASSERT(b->this_cid == knh_Object_cid(b->nsproto));
//	DEBUG("command");
	knh_Cmpl_initDecl(ctx, b);
	knh_Cmpl_initThisVariable(ctx, b, b->this_cid);
	KNH_SETv(ctx, b->method, knh_Class_getMethod(ctx, b->this_cid, METHODN_run));

	DEBUG_ASSERT(IS_Token(stmt->terms[0]));
	knh_Cmpl_startCompilation(ctx, b, ((Token*)stmt->terms[0])->filen);
	KNH_ASM_SETLINE(ctx, b, ((Token*)stmt->terms[0])->line);
	
	KNH_LOPEN(ctx, 0);
	KNH_PUSHv(ctx, stmt->next);
	KNH_SETv(ctx, stmt->next, KNH_NULL);
	knh_Cmpl_initLocalVariables(ctx, b, stmt);
	KNH_SETv(ctx, stmt->next, KNH_LOCALv(0));
	KNH_LCLOSE(ctx);
}

/* ------------------------------------------------------------------------ */

void knh_Cmpl_commitRun(Ctx *ctx, Cmpl *b, knh_bool_t isshow)
{
	knh_Cmpl_endCompilation(ctx, b);

	KNH_LOPEN(ctx, 0);
	KNH_PUSHv(ctx, new_ExceptionHandler(ctx));      /* 0 */
	KNH_PUSHv(ctx, KNH_NULL);                           /* 1 Exception e */

	DEBUG_ASSERT(IS_ExceptionHandler(KNH_LOCALv(0)));
	VM_TRY_BEGIN(ctx, NPC, L_CATCH_EXCEPTION, KNH_LOCALv(0), KNH_LOCALv(1));

	Method *mtd = knh_Class_getMethod(ctx, knh_Object_cid(b->nsproto), METHODN_run);
	KNH_PUSHv(ctx, mtd);                           /* 2 mtd, return ebp[-1] */
	KNH_PUSHv(ctx, b->nsproto);                    /* 3 this ebp[0] */
	KNH_SCALL(ctx, 1);
	if(isshow) {
		knh_format(ctx, KNH_STDOUT, METHODN__dump, KNH_LOCALv(2), KNH_NULL);
		knh_println(ctx, KNH_STDOUT, STEXT(""));
	}
#ifdef KONOHA_DEBUGMODE
	else {
		fprintf(stdout, "ebp[+%d] = ", (int)(((Context*)ctx)->ebp - ((Context*)ctx)->stack));
		knh_format(ctx, KNH_STDOUT, METHODN__s, KNH_LOCALv(2), KNH_NULL);
	}
#endif
	VM_TRY_END(ctx, KNH_LOCALv(0));
	KNH_LCLOSE(ctx);
	return ;
	
	L_CATCH_EXCEPTION:;
	VM_TRY_END(ctx, KNH_LOCALv(0));
	DEBUG_ASSERT(IS_Exception(KNH_LOCALv(1)));
	knh_format(ctx, KNH_STDOUT, METHODN__dump, KNH_LOCALv(1), KNH_NULL);
	KNH_LCLOSE(ctx);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
