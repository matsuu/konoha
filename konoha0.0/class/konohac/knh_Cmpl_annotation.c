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
/* [debug] */

#ifdef KONOHA_DEBUGMODE
	#define DEBUG_STMT0(ctx, stmt)
	#define DEBUG_STMT(ctx, stmt) \
		DEBUG("level=%d", level); \
		knh_Stmt__dump(ctx, stmt, KNH_STDOUT, knh_String_EMPTY()); \
		knh_flush(ctx, KNH_STDOUT); \

#else
	#define DEBUG_STMT(ctx, stmt)
#endif


/* ======================================================================== */
/* [declv] */

void
knh_Cmpl_before_declv(Ctx *ctx, Cmpl *b, Stmt *stmt, int level)
{
	if(knh_Stmt_hasMeta(stmt)) {
		DEBUG_STMT(ctx, stmt);	
	}
}

/* ------------------------------------------------------------------------ */

void
knh_Cmpl_after_declv(Ctx *ctx, Cmpl *b, Stmt *stmt, int level)
{
	if(knh_Stmt_hasMeta(stmt)) {
		DEBUG_STMT(ctx, stmt);	
	}
}

/* ======================================================================== */
/* [asm] */

void
knh_Cmpl_before_asm(Ctx *ctx, Cmpl *b, Stmt *stmt, int level)
{
	/* setline */
	if(stmt->size > 0 && IS_Token(stmt->terms[0])) {
		KNH_ASM_SETLINE(ctx, b, ((Token*)stmt->terms[0])->line);
	}

	/* continue-labeling */
	if(knh_Stmt_hasContinueBreak(stmt)) {
		Token *tkl = knh_Stmt_getLabel(stmt);
		if(IS_NOTNULL(tkl)) {
			//KNH_ASM_LABEL(ctx, b, tkl);
			DEBUG_ASSERT(IS_String(tkl->data));
			String *label = (String*)tkl->data;
			knh_Cmpl_lstack_push(ctx, b, label);
			knh_Cmpl_setBreakLabel(ctx, b, label);
		}
		else {
			char lb[LABEL_BUFSIZ];
			knh_snprintf(lb, sizeof(lb), "_L%d_", knh_Cmpl_llstep(b));
			//KNH_ASM_LABEL__b(ctx, b, B(lb));
			String *label = new_String__fast(ctx, CLASS_String, B(lb));
			knh_Cmpl_lstack_push(ctx, b, label);
			knh_Cmpl_setBreakLabel(ctx, b, label);
		}
	}
#ifdef KONOHA_LANG_GOTO
	else {
		Token *tkl = knh_Stmt_getLabel(stmt);
		if(IS_NOTNULL(tkl)) {
			KNH_ASM_LABEL(ctx, b, tkl);
			String *label = (String*)tkl->data;
			knh_Cmpl_setGlobalLabel(ctx, b, label);
		}
	}
#endif
}

/* ------------------------------------------------------------------------ */

void
knh_Cmpl_after_asm(Ctx *ctx, Cmpl *b, Stmt *stmt, int level)
{
	/* break-labeling */
	if(knh_Stmt_hasContinueBreak(stmt)) {
		String *label = knh_Cmpl_lstack_label(ctx, b);
		DEBUG_ASSERT(label != NULL);
		knh_Cmpl_lstack_pop(ctx, b);
//		char lb[LABEL_BUFSIZ];
//		knh_snprintf(lb, sizeof(lb), "_END_%s", knh_String_tochar(label));
//		KNH_ASM_LABEL__b(ctx, b, B(lb));
		
		knh_Stmt_done(ctx, stmt);
	}
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
