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

#include<konoha/konoha_dev.h>
#include<konoha/gen/konohac_asm_.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

/* ======================================================================== */
/* [Compiler] */

void KNH_ASM_HALT(Ctx *ctx, Compiler *o)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_halt_t *bw = (knh_asmc_halt_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_HALT_SIZ);
		bw->code = ASMC_HALT;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_RET(Ctx *ctx, Compiler *o, Term *v)
{
	if(IS_Token((Token*)v)) {
		Token *tk = (Token*)v;
#ifdef ASMC_RET__OBJ
		if(SP(tk)->tt == TT_CONST || SP(tk)->tt == TT_MTDMPR) {
			KNH_ASM_RET__OBJ(ctx, o, DP(tk)->data);
			return;
		}
#endif/*ASMC_RET__OBJ*/
#ifdef ASMC_RET__SFP
		if(SP(tk)->tt == TT_SFPIDX) {
			KNH_ASM_RET__sfp(ctx, o, DP(tk)->index);
			return;
		}
#endif/*ASMC_RET__SFP*/
#ifdef ASMC_RET__OFP
		if(SP(tk)->tt == TT_FLDIDX) {
			KNH_ASM_RET__ofp(ctx, o, DP(tk)->index);
			return;
		}
#endif/*ASMC_RET__OFP*/
#ifdef ASMC_RET__OIDX
		if(SP(tk)->tt == TT_OBJIDX) {
			KNH_ASM_RET__OIDX(ctx, o, DP(tk)->data, DP(tk)->index);
			return;
		}
#endif/*ASMC_RET__OIDX*/
#ifdef ASMC_RET__EBP
		if(SP(tk)->tt == TT_EBPIDX) {
			KNH_ASM_RET__ebp(ctx, o, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_RET__ebp(ctx, o, 0);
			return;
		}
#endif/*ASMC_RET__EBP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			KNH_ASM_RET__ebp(ctx, o, 0);
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Compiler_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));

#ifdef ASMC_RET__EBP
		KNH_ASM_RET__ebp(ctx, o, 0);
		return;
#else
		DBG_P("unsupported stmt stt=%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_RET__EBP*/
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_RET__ebp(Ctx *ctx, Compiler *o, knhvm_ebp_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_ret_ebp_t *bw = (knh_asmc_ret_ebp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_RET_ebp_SIZ);
		bw->code = ASMC_RET__EBP;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_RET__sfp(Ctx *ctx, Compiler *o, knhvm_sfp_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_ret_sfp_t *bw = (knh_asmc_ret_sfp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_RET_sfp_SIZ);
		bw->code = ASMC_RET__SFP;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_RET__ofp(Ctx *ctx, Compiler *o, knhvm_ofp_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_ret_ofp_t *bw = (knh_asmc_ret_ofp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_RET_ofp_SIZ);
		bw->code = ASMC_RET__OFP;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_RET__OBJ(Ctx *ctx, Compiler *o, Object* a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_ret_obj_t *bw = (knh_asmc_ret_obj_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_RET_OBJ_SIZ);
		bw->code = ASMC_RET__OBJ;
		bw->a1 = a1;
		knh_Object_RCinc(bw->a1);
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_RET__OIDX(Ctx *ctx, Compiler *o, Object* a1, knhvm_u1_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_ret_oidx_t *bw = (knh_asmc_ret_oidx_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_RET_OIDX_SIZ);
		bw->code = ASMC_RET__OIDX;
		bw->a1 = a1;
		knh_Object_RCinc(bw->a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVE(Ctx *ctx, Compiler *o, knhvm_ebp_t a1, Term *v)
{
	if(IS_Token((Token*)v)) {
		Token *tk = (Token*)v;
#ifdef ASMC_MOVE__OBJ
		if(SP(tk)->tt == TT_CONST || SP(tk)->tt == TT_MTDMPR) {
			KNH_ASM_MOVE__OBJ(ctx, o, a1, DP(tk)->data);
			return;
		}
#endif/*ASMC_MOVE__OBJ*/
#ifdef ASMC_MOVE__SFP
		if(SP(tk)->tt == TT_SFPIDX) {
			KNH_ASM_MOVE__sfp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_MOVE__SFP*/
#ifdef ASMC_MOVE__OFP
		if(SP(tk)->tt == TT_FLDIDX) {
			KNH_ASM_MOVE__ofp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_MOVE__OFP*/
#ifdef ASMC_MOVE__OIDX
		if(SP(tk)->tt == TT_OBJIDX) {
			KNH_ASM_MOVE__OIDX(ctx, o, a1, DP(tk)->data, DP(tk)->index);
			return;
		}
#endif/*ASMC_MOVE__OIDX*/
#ifdef ASMC_MOVE__EBP
		if(SP(tk)->tt == TT_EBPIDX) {
			KNH_ASM_MOVE__ebp(ctx, o, a1, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_MOVE__ebp(ctx, o, a1, 0);
			return;
		}
#endif/*ASMC_MOVE__EBP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			KNH_ASM_MOVE__ebp(ctx, o, a1, 0);
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Compiler_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));

#ifdef ASMC_MOVE__EBP
		KNH_ASM_MOVE__ebp(ctx, o, a1, 0);
		return;
#else
		DBG_P("unsupported stmt stt=%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_MOVE__EBP*/
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVE__ebp(Ctx *ctx, Compiler *o, knhvm_ebp_t a1, knhvm_ebp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_move_ebp_t *bw = (knh_asmc_move_ebp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVE_ebp_SIZ);
		bw->code = ASMC_MOVE__EBP;
		bw->a1 = a1;
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVE__sfp(Ctx *ctx, Compiler *o, knhvm_ebp_t a1, knhvm_sfp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_move_sfp_t *bw = (knh_asmc_move_sfp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVE_sfp_SIZ);
		bw->code = ASMC_MOVE__SFP;
		bw->a1 = a1;
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVE__ofp(Ctx *ctx, Compiler *o, knhvm_ebp_t a1, knhvm_ofp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_move_ofp_t *bw = (knh_asmc_move_ofp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVE_ofp_SIZ);
		bw->code = ASMC_MOVE__OFP;
		bw->a1 = a1;
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVE__OBJ(Ctx *ctx, Compiler *o, knhvm_ebp_t a1, Object* a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_move_obj_t *bw = (knh_asmc_move_obj_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVE_OBJ_SIZ);
		bw->code = ASMC_MOVE__OBJ;
		bw->a1 = a1;
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVE__OIDX(Ctx *ctx, Compiler *o, knhvm_ebp_t a1, Object* a2, knhvm_u1_t a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_move_oidx_t *bw = (knh_asmc_move_oidx_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVE_OIDX_SIZ);
		bw->code = ASMC_MOVE__OIDX;
		bw->a1 = a1;
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
		bw->a3 = a3;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVS(Ctx *ctx, Compiler *o, knhvm_sfp_t a1, Term *v)
{
	if(IS_Token((Token*)v)) {
		Token *tk = (Token*)v;
#ifdef ASMC_MOVS__OBJ
		if(SP(tk)->tt == TT_CONST || SP(tk)->tt == TT_MTDMPR) {
			KNH_ASM_MOVS__OBJ(ctx, o, a1, DP(tk)->data);
			return;
		}
#endif/*ASMC_MOVS__OBJ*/
#ifdef ASMC_MOVS__SFP
		if(SP(tk)->tt == TT_SFPIDX) {
			KNH_ASM_MOVS__sfp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_MOVS__SFP*/
#ifdef ASMC_MOVS__OFP
		if(SP(tk)->tt == TT_FLDIDX) {
			KNH_ASM_MOVS__ofp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_MOVS__OFP*/
#ifdef ASMC_MOVS__OIDX
		if(SP(tk)->tt == TT_OBJIDX) {
			KNH_ASM_MOVS__OIDX(ctx, o, a1, DP(tk)->data, DP(tk)->index);
			return;
		}
#endif/*ASMC_MOVS__OIDX*/
#ifdef ASMC_MOVS__EBP
		if(SP(tk)->tt == TT_EBPIDX) {
			KNH_ASM_MOVS__ebp(ctx, o, a1, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_MOVS__ebp(ctx, o, a1, 0);
			return;
		}
#endif/*ASMC_MOVS__EBP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			KNH_ASM_MOVS__ebp(ctx, o, a1, 0);
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Compiler_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));

#ifdef ASMC_MOVS__EBP
		KNH_ASM_MOVS__ebp(ctx, o, a1, 0);
		return;
#else
		DBG_P("unsupported stmt stt=%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_MOVS__EBP*/
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVS__ebp(Ctx *ctx, Compiler *o, knhvm_sfp_t a1, knhvm_ebp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_movs_ebp_t *bw = (knh_asmc_movs_ebp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVS_ebp_SIZ);
		bw->code = ASMC_MOVS__EBP;
		bw->a1 = a1;
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVS__sfp(Ctx *ctx, Compiler *o, knhvm_sfp_t a1, knhvm_sfp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_movs_sfp_t *bw = (knh_asmc_movs_sfp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVS_sfp_SIZ);
		bw->code = ASMC_MOVS__SFP;
		bw->a1 = a1;
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVS__ofp(Ctx *ctx, Compiler *o, knhvm_sfp_t a1, knhvm_ofp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_movs_ofp_t *bw = (knh_asmc_movs_ofp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVS_ofp_SIZ);
		bw->code = ASMC_MOVS__OFP;
		bw->a1 = a1;
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVS__OBJ(Ctx *ctx, Compiler *o, knhvm_sfp_t a1, Object* a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_movs_obj_t *bw = (knh_asmc_movs_obj_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVS_OBJ_SIZ);
		bw->code = ASMC_MOVS__OBJ;
		bw->a1 = a1;
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVS__OIDX(Ctx *ctx, Compiler *o, knhvm_sfp_t a1, Object* a2, knhvm_u1_t a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_movs_oidx_t *bw = (knh_asmc_movs_oidx_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVS_OIDX_SIZ);
		bw->code = ASMC_MOVS__OIDX;
		bw->a1 = a1;
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
		bw->a3 = a3;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVO(Ctx *ctx, Compiler *o, knhvm_ofp_t a1, Term *v)
{
	if(IS_Token((Token*)v)) {
		Token *tk = (Token*)v;
#ifdef ASMC_MOVO__OBJ
		if(SP(tk)->tt == TT_CONST || SP(tk)->tt == TT_MTDMPR) {
			KNH_ASM_MOVO__OBJ(ctx, o, a1, DP(tk)->data);
			return;
		}
#endif/*ASMC_MOVO__OBJ*/
#ifdef ASMC_MOVO__SFP
		if(SP(tk)->tt == TT_SFPIDX) {
			KNH_ASM_MOVO__sfp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_MOVO__SFP*/
#ifdef ASMC_MOVO__OFP
		if(SP(tk)->tt == TT_FLDIDX) {
			KNH_ASM_MOVO__ofp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_MOVO__OFP*/
#ifdef ASMC_MOVO__OIDX
		if(SP(tk)->tt == TT_OBJIDX) {
			KNH_ASM_MOVO__OIDX(ctx, o, a1, DP(tk)->data, DP(tk)->index);
			return;
		}
#endif/*ASMC_MOVO__OIDX*/
#ifdef ASMC_MOVO__EBP
		if(SP(tk)->tt == TT_EBPIDX) {
			KNH_ASM_MOVO__ebp(ctx, o, a1, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_MOVO__ebp(ctx, o, a1, 0);
			return;
		}
#endif/*ASMC_MOVO__EBP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			KNH_ASM_MOVO__ebp(ctx, o, a1, 0);
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Compiler_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));

#ifdef ASMC_MOVO__EBP
		KNH_ASM_MOVO__ebp(ctx, o, a1, 0);
		return;
#else
		DBG_P("unsupported stmt stt=%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_MOVO__EBP*/
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVO__ebp(Ctx *ctx, Compiler *o, knhvm_ofp_t a1, knhvm_ebp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_movo_ebp_t *bw = (knh_asmc_movo_ebp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVO_ebp_SIZ);
		bw->code = ASMC_MOVO__EBP;
		bw->a1 = a1;
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVO__sfp(Ctx *ctx, Compiler *o, knhvm_ofp_t a1, knhvm_sfp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_movo_sfp_t *bw = (knh_asmc_movo_sfp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVO_sfp_SIZ);
		bw->code = ASMC_MOVO__SFP;
		bw->a1 = a1;
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVO__ofp(Ctx *ctx, Compiler *o, knhvm_ofp_t a1, knhvm_ofp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_movo_ofp_t *bw = (knh_asmc_movo_ofp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVO_ofp_SIZ);
		bw->code = ASMC_MOVO__OFP;
		bw->a1 = a1;
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVO__OBJ(Ctx *ctx, Compiler *o, knhvm_ofp_t a1, Object* a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_movo_obj_t *bw = (knh_asmc_movo_obj_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVO_OBJ_SIZ);
		bw->code = ASMC_MOVO__OBJ;
		bw->a1 = a1;
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVO__OIDX(Ctx *ctx, Compiler *o, knhvm_ofp_t a1, Object* a2, knhvm_u1_t a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_movo_oidx_t *bw = (knh_asmc_movo_oidx_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVO_OIDX_SIZ);
		bw->code = ASMC_MOVO__OIDX;
		bw->a1 = a1;
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
		bw->a3 = a3;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVOI(Ctx *ctx, Compiler *o, Object* a1, knhvm_ofp_t a2, Term *v)
{
	if(IS_Token((Token*)v)) {
		Token *tk = (Token*)v;
#ifdef ASMC_MOVOI__OBJ
		if(SP(tk)->tt == TT_CONST || SP(tk)->tt == TT_MTDMPR) {
			KNH_ASM_MOVOI__OBJ(ctx, o, a1, a2, DP(tk)->data);
			return;
		}
#endif/*ASMC_MOVOI__OBJ*/
#ifdef ASMC_MOVOI__SFP
		if(SP(tk)->tt == TT_SFPIDX) {
			KNH_ASM_MOVOI__sfp(ctx, o, a1, a2, DP(tk)->index);
			return;
		}
#endif/*ASMC_MOVOI__SFP*/
#ifdef ASMC_MOVOI__OFP
		if(SP(tk)->tt == TT_FLDIDX) {
			KNH_ASM_MOVOI__ofp(ctx, o, a1, a2, DP(tk)->index);
			return;
		}
#endif/*ASMC_MOVOI__OFP*/
#ifdef ASMC_MOVOI__OIDX
		if(SP(tk)->tt == TT_OBJIDX) {
			KNH_ASM_MOVOI__OIDX(ctx, o, a1, a2, DP(tk)->data, DP(tk)->index);
			return;
		}
#endif/*ASMC_MOVOI__OIDX*/
#ifdef ASMC_MOVOI__EBP
		if(SP(tk)->tt == TT_EBPIDX) {
			KNH_ASM_MOVOI__ebp(ctx, o, a1, a2, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_MOVOI__ebp(ctx, o, a1, a2, 0);
			return;
		}
#endif/*ASMC_MOVOI__EBP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			KNH_ASM_MOVOI__ebp(ctx, o, a1, a2, 0);
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Compiler_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));

#ifdef ASMC_MOVOI__EBP
		KNH_ASM_MOVOI__ebp(ctx, o, a1, a2, 0);
		return;
#else
		DBG_P("unsupported stmt stt=%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_MOVOI__EBP*/
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVOI__ebp(Ctx *ctx, Compiler *o, Object* a1, knhvm_ofp_t a2, knhvm_ebp_t a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_movoi_ebp_t *bw = (knh_asmc_movoi_ebp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVOI_ebp_SIZ);
		bw->code = ASMC_MOVOI__EBP;
		bw->a1 = a1;
		knh_Object_RCinc(bw->a1);
		bw->a2 = a2;
		bw->a3 = a3;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVOI__sfp(Ctx *ctx, Compiler *o, Object* a1, knhvm_ofp_t a2, knhvm_sfp_t a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_movoi_sfp_t *bw = (knh_asmc_movoi_sfp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVOI_sfp_SIZ);
		bw->code = ASMC_MOVOI__SFP;
		bw->a1 = a1;
		knh_Object_RCinc(bw->a1);
		bw->a2 = a2;
		bw->a3 = a3;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVOI__ofp(Ctx *ctx, Compiler *o, Object* a1, knhvm_ofp_t a2, knhvm_ofp_t a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_movoi_ofp_t *bw = (knh_asmc_movoi_ofp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVOI_ofp_SIZ);
		bw->code = ASMC_MOVOI__OFP;
		bw->a1 = a1;
		knh_Object_RCinc(bw->a1);
		bw->a2 = a2;
		bw->a3 = a3;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVOI__OBJ(Ctx *ctx, Compiler *o, Object* a1, knhvm_ofp_t a2, Object* a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_movoi_obj_t *bw = (knh_asmc_movoi_obj_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVOI_OBJ_SIZ);
		bw->code = ASMC_MOVOI__OBJ;
		bw->a1 = a1;
		knh_Object_RCinc(bw->a1);
		bw->a2 = a2;
		bw->a3 = a3;
		knh_Object_RCinc(bw->a3);
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVOI__OIDX(Ctx *ctx, Compiler *o, Object* a1, knhvm_u1_t a2, Object* a3, knhvm_u1_t a4)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_movoi_oidx_t *bw = (knh_asmc_movoi_oidx_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVOI_OIDX_SIZ);
		bw->code = ASMC_MOVOI__OIDX;
		bw->a1 = a1;
		knh_Object_RCinc(bw->a1);
		bw->a2 = a2;
		bw->a3 = a3;
		knh_Object_RCinc(bw->a3);
		bw->a4 = a4;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVSFP_IFNUL(Ctx *ctx, Compiler *o, knhvm_u1_t a1, Object* a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_movsfp_ifnul_t *bw = (knh_asmc_movsfp_ifnul_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MOVSFP_IFNUL_SIZ);
		bw->code = ASMC_MOVSFP_IFNUL;
		bw->a1 = a1;
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PUSH(Ctx *ctx, Compiler *o, Term *v)
{
	if(IS_Token((Token*)v)) {
		Token *tk = (Token*)v;
#ifdef ASMC_PUSH__OBJ
		if(SP(tk)->tt == TT_CONST || SP(tk)->tt == TT_MTDMPR) {
			KNH_ASM_PUSH__OBJ(ctx, o, DP(tk)->data);
			return;
		}
#endif/*ASMC_PUSH__OBJ*/
#ifdef ASMC_PUSH__SFP
		if(SP(tk)->tt == TT_SFPIDX) {
			KNH_ASM_PUSH__sfp(ctx, o, DP(tk)->index);
			return;
		}
#endif/*ASMC_PUSH__SFP*/
#ifdef ASMC_PUSH__OFP
		if(SP(tk)->tt == TT_FLDIDX) {
			KNH_ASM_PUSH__ofp(ctx, o, DP(tk)->index);
			return;
		}
#endif/*ASMC_PUSH__OFP*/
#ifdef ASMC_PUSH__OIDX
		if(SP(tk)->tt == TT_OBJIDX) {
			KNH_ASM_PUSH__OIDX(ctx, o, DP(tk)->data, DP(tk)->index);
			return;
		}
#endif/*ASMC_PUSH__OIDX*/
#ifdef ASMC_PUSH__EBP
		if(SP(tk)->tt == TT_EBPIDX) {
			KNH_ASM_PUSH__ebp(ctx, o, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_PUSH__ebp(ctx, o, 0);
			return;
		}
#endif/*ASMC_PUSH__EBP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			;
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Compiler_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));

#ifdef ASMC_PUSH__EBP
		/*KNH_ASM_PUSH__ebp(ctx, o, 0); CALLED */
		return;
#else
		DBG_P("unsupported stmt stt=%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_PUSH__EBP*/
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PUSH__ebp(Ctx *ctx, Compiler *o, knhvm_ebp_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_push_ebp_t *bw = (knh_asmc_push_ebp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_PUSH_ebp_SIZ);
		bw->code = ASMC_PUSH__EBP;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PUSH__sfp(Ctx *ctx, Compiler *o, knhvm_sfp_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_push_sfp_t *bw = (knh_asmc_push_sfp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_PUSH_sfp_SIZ);
		bw->code = ASMC_PUSH__SFP;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PUSH__ofp(Ctx *ctx, Compiler *o, knhvm_ofp_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_push_ofp_t *bw = (knh_asmc_push_ofp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_PUSH_ofp_SIZ);
		bw->code = ASMC_PUSH__OFP;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PUSH__OBJ(Ctx *ctx, Compiler *o, Object* a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_push_obj_t *bw = (knh_asmc_push_obj_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_PUSH_OBJ_SIZ);
		bw->code = ASMC_PUSH__OBJ;
		bw->a1 = a1;
		knh_Object_RCinc(bw->a1);
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PUSH__OIDX(Ctx *ctx, Compiler *o, Object* a1, knhvm_u1_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_push_oidx_t *bw = (knh_asmc_push_oidx_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_PUSH_OIDX_SIZ);
		bw->code = ASMC_PUSH__OIDX;
		bw->a1 = a1;
		knh_Object_RCinc(bw->a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PUT_SYSCONST(Ctx *ctx, Compiler *o, knhvm_u2_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_put_sysconst_t *bw = (knh_asmc_put_sysconst_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_PUT_SYSCONST_SIZ);
		bw->code = ASMC_PUT_SYSCONST;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PUSH_SYSCONST(Ctx *ctx, Compiler *o, knhvm_u2_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_push_sysconst_t *bw = (knh_asmc_push_sysconst_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_PUSH_SYSCONST_SIZ);
		bw->code = ASMC_PUSH_SYSCONST;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PUSH__DEF(Ctx *ctx, Compiler *o, knhvm_class_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_push_def_t *bw = (knh_asmc_push_def_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_PUSH_DEF_SIZ);
		bw->code = ASMC_PUSH__DEF;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_VARGS(Ctx *ctx, Compiler *o, knhvm_u2_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_vargs_t *bw = (knh_asmc_vargs_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_VARGS_SIZ);
		bw->code = ASMC_VARGS;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_SHIFT(Ctx *ctx, Compiler *o, knhvm_i1_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_shift_t *bw = (knh_asmc_shift_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_SHIFT_SIZ);
		bw->code = ASMC_SHIFT;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_SCALL(Ctx *ctx, Compiler *o, knhvm_u1_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_scall_t *bw = (knh_asmc_scall_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_SCALL_SIZ);
		bw->code = ASMC_SCALL;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NSCALL(Ctx *ctx, Compiler *o, knhvm_u1_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_nscall_t *bw = (knh_asmc_nscall_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_NSCALL_SIZ);
		bw->code = ASMC_NSCALL;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_CALL(Ctx *ctx, Compiler *o, knhvm_u1_t a1, knhvm_methodn_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_call_t *bw = (knh_asmc_call_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_CALL_SIZ);
		bw->code = ASMC_CALL;
		bw->a1 = a1;
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_DCALL(Ctx *ctx, Compiler *o, knhvm_u1_t a1, knhvm_methodn_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_dcall_t *bw = (knh_asmc_dcall_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_DCALL_SIZ);
		bw->code = ASMC_DCALL;
		bw->a1 = a1;
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NEW(Ctx *ctx, Compiler *o, knhvm_u2_t a1, knhvm_u2_t a2, knhvm_class_t a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_new_t *bw = (knh_asmc_new_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_NEW_SIZ);
		bw->code = ASMC_NEW;
		bw->a1 = a1;
		bw->a2 = a2;
		bw->a3 = a3;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MT(Ctx *ctx, Compiler *o, knhvm_methodn_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_mt_t *bw = (knh_asmc_mt_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MT_SIZ);
		bw->code = ASMC_MT;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_SMAP(Ctx *ctx, Compiler *o, Object* a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_smap_t *bw = (knh_asmc_smap_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_SMAP_SIZ);
		bw->code = ASMC_SMAP;
		bw->a1 = a1;
		knh_Object_RCinc(bw->a1);
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_SMAPE(Ctx *ctx, Compiler *o, Object* a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_smape_t *bw = (knh_asmc_smape_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_SMAPE_SIZ);
		bw->code = ASMC_SMAPE;
		bw->a1 = a1;
		knh_Object_RCinc(bw->a1);
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MAP(Ctx *ctx, Compiler *o, knhvm_class_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_map_t *bw = (knh_asmc_map_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MAP_SIZ);
		bw->code = ASMC_MAP;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MAPE(Ctx *ctx, Compiler *o, knhvm_class_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_mape_t *bw = (knh_asmc_mape_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MAPE_SIZ);
		bw->code = ASMC_MAPE;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_ANYMAP(Ctx *ctx, Compiler *o, knhvm_class_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_anymap_t *bw = (knh_asmc_anymap_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_ANYMAP_SIZ);
		bw->code = ASMC_ANYMAP;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_ANYMAPE(Ctx *ctx, Compiler *o, knhvm_class_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_anymape_t *bw = (knh_asmc_anymape_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_ANYMAPE_SIZ);
		bw->code = ASMC_ANYMAPE;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MAP2(Ctx *ctx, Compiler *o, knhvm_class_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_map2_t *bw = (knh_asmc_map2_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MAP2_SIZ);
		bw->code = ASMC_MAP2;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MAP2E(Ctx *ctx, Compiler *o, knhvm_class_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_map2e_t *bw = (knh_asmc_map2e_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MAP2E_SIZ);
		bw->code = ASMC_MAP2E;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_TYPECHK(Ctx *ctx, Compiler *o, knhvm_class_t a1, Term *v)
{
	if(IS_Token((Token*)v)) {
		Token *tk = (Token*)v;
#ifdef ASMC_TYPECHK__OBJ
		if(SP(tk)->tt == TT_CONST || SP(tk)->tt == TT_MTDMPR) {
			KNH_ASM_TYPECHK__OBJ(ctx, o, a1, DP(tk)->data);
			return;
		}
#endif/*ASMC_TYPECHK__OBJ*/
#ifdef ASMC_TYPECHK__SFP
		if(SP(tk)->tt == TT_SFPIDX) {
			KNH_ASM_TYPECHK__sfp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_TYPECHK__SFP*/
#ifdef ASMC_TYPECHK__OFP
		if(SP(tk)->tt == TT_FLDIDX) {
			KNH_ASM_TYPECHK__ofp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_TYPECHK__OFP*/
#ifdef ASMC_TYPECHK__OIDX
		if(SP(tk)->tt == TT_OBJIDX) {
			KNH_ASM_TYPECHK__OIDX(ctx, o, a1, DP(tk)->data, DP(tk)->index);
			return;
		}
#endif/*ASMC_TYPECHK__OIDX*/
#ifdef ASMC_TYPECHK__EBP
		if(SP(tk)->tt == TT_EBPIDX) {
			KNH_ASM_TYPECHK__ebp(ctx, o, a1, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_TYPECHK__ebp(ctx, o, a1, 0);
			return;
		}
#endif/*ASMC_TYPECHK__EBP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			KNH_ASM_TYPECHK__ebp(ctx, o, a1, 0);
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Compiler_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));

#ifdef ASMC_TYPECHK__EBP
		KNH_ASM_TYPECHK__ebp(ctx, o, a1, 0);
		return;
#else
		DBG_P("unsupported stmt stt=%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_TYPECHK__EBP*/
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_TYPECHK__ebp(Ctx *ctx, Compiler *o, knhvm_class_t a1, knhvm_ebp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_typechk_ebp_t *bw = (knh_asmc_typechk_ebp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_TYPECHK_ebp_SIZ);
		bw->code = ASMC_TYPECHK__EBP;
		bw->a1 = a1;
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_TYPECHK__sfp(Ctx *ctx, Compiler *o, knhvm_class_t a1, knhvm_sfp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_typechk_sfp_t *bw = (knh_asmc_typechk_sfp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_TYPECHK_sfp_SIZ);
		bw->code = ASMC_TYPECHK__SFP;
		bw->a1 = a1;
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_TYPECHK__ofp(Ctx *ctx, Compiler *o, knhvm_class_t a1, knhvm_ofp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_typechk_ofp_t *bw = (knh_asmc_typechk_ofp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_TYPECHK_ofp_SIZ);
		bw->code = ASMC_TYPECHK__OFP;
		bw->a1 = a1;
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_TYPECHK__OBJ(Ctx *ctx, Compiler *o, knhvm_class_t a1, Object* a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_typechk_obj_t *bw = (knh_asmc_typechk_obj_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_TYPECHK_OBJ_SIZ);
		bw->code = ASMC_TYPECHK__OBJ;
		bw->a1 = a1;
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_TYPECHK__OIDX(Ctx *ctx, Compiler *o, knhvm_class_t a1, Object* a2, knhvm_u1_t a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_typechk_oidx_t *bw = (knh_asmc_typechk_oidx_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_TYPECHK_OIDX_SIZ);
		bw->code = ASMC_TYPECHK__OIDX;
		bw->a1 = a1;
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
		bw->a3 = a3;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NULLCHK(Ctx *ctx, Compiler *o, Term *v)
{
	if(IS_Token((Token*)v)) {
		Token *tk = (Token*)v;
#ifdef ASMC_NULLCHK__OBJ
		if(SP(tk)->tt == TT_CONST || SP(tk)->tt == TT_MTDMPR) {
			KNH_ASM_NULLCHK__OBJ(ctx, o, DP(tk)->data);
			return;
		}
#endif/*ASMC_NULLCHK__OBJ*/
#ifdef ASMC_NULLCHK__SFP
		if(SP(tk)->tt == TT_SFPIDX) {
			KNH_ASM_NULLCHK__sfp(ctx, o, DP(tk)->index);
			return;
		}
#endif/*ASMC_NULLCHK__SFP*/
#ifdef ASMC_NULLCHK__OFP
		if(SP(tk)->tt == TT_FLDIDX) {
			KNH_ASM_NULLCHK__ofp(ctx, o, DP(tk)->index);
			return;
		}
#endif/*ASMC_NULLCHK__OFP*/
#ifdef ASMC_NULLCHK__OIDX
		if(SP(tk)->tt == TT_OBJIDX) {
			KNH_ASM_NULLCHK__OIDX(ctx, o, DP(tk)->data, DP(tk)->index);
			return;
		}
#endif/*ASMC_NULLCHK__OIDX*/
#ifdef ASMC_NULLCHK__EBP
		if(SP(tk)->tt == TT_EBPIDX) {
			KNH_ASM_NULLCHK__ebp(ctx, o, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_NULLCHK__ebp(ctx, o, 0);
			return;
		}
#endif/*ASMC_NULLCHK__EBP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			KNH_ASM_NULLCHK__ebp(ctx, o, 0);
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Compiler_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));

#ifdef ASMC_NULLCHK__EBP
		KNH_ASM_NULLCHK__ebp(ctx, o, 0);
		return;
#else
		DBG_P("unsupported stmt stt=%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_NULLCHK__EBP*/
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NULLCHK__ebp(Ctx *ctx, Compiler *o, knhvm_ebp_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_nullchk_ebp_t *bw = (knh_asmc_nullchk_ebp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_NULLCHK_ebp_SIZ);
		bw->code = ASMC_NULLCHK__EBP;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NULLCHK__sfp(Ctx *ctx, Compiler *o, knhvm_sfp_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_nullchk_sfp_t *bw = (knh_asmc_nullchk_sfp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_NULLCHK_sfp_SIZ);
		bw->code = ASMC_NULLCHK__SFP;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NULLCHK__ofp(Ctx *ctx, Compiler *o, knhvm_ofp_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_nullchk_ofp_t *bw = (knh_asmc_nullchk_ofp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_NULLCHK_ofp_SIZ);
		bw->code = ASMC_NULLCHK__OFP;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NULLCHK__OBJ(Ctx *ctx, Compiler *o, Object* a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_nullchk_obj_t *bw = (knh_asmc_nullchk_obj_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_NULLCHK_OBJ_SIZ);
		bw->code = ASMC_NULLCHK__OBJ;
		bw->a1 = a1;
		knh_Object_RCinc(bw->a1);
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NULLCHK__OIDX(Ctx *ctx, Compiler *o, Object* a1, knhvm_u1_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_nullchk_oidx_t *bw = (knh_asmc_nullchk_oidx_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_NULLCHK_OIDX_SIZ);
		bw->code = ASMC_NULLCHK__OIDX;
		bw->a1 = a1;
		knh_Object_RCinc(bw->a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP(Ctx *ctx, Compiler *o, knh_bytes_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_t *bw = (knh_asmc_jmp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_SIZ);
		bw->code = ASMC_JMP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_SKIP(Ctx *ctx, Compiler *o, knh_bytes_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_skip_t *bw = (knh_asmc_skip_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_SKIP_SIZ);
		bw->code = ASMC_SKIP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFT(Ctx *ctx, Compiler *o, knh_bytes_t a1, Term *v)
{
	if(IS_Token((Token*)v)) {
		Token *tk = (Token*)v;
#ifdef ASMC_JMP_IFT__OBJ
		if(SP(tk)->tt == TT_CONST || SP(tk)->tt == TT_MTDMPR) {
			KNH_ASM_JMP_IFT__OBJ(ctx, o, a1, DP(tk)->data);
			return;
		}
#endif/*ASMC_JMP_IFT__OBJ*/
#ifdef ASMC_JMP_IFT__SFP
		if(SP(tk)->tt == TT_SFPIDX) {
			KNH_ASM_JMP_IFT__sfp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_JMP_IFT__SFP*/
#ifdef ASMC_JMP_IFT__OFP
		if(SP(tk)->tt == TT_FLDIDX) {
			KNH_ASM_JMP_IFT__ofp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_JMP_IFT__OFP*/
#ifdef ASMC_JMP_IFT__OIDX
		if(SP(tk)->tt == TT_OBJIDX) {
			KNH_ASM_JMP_IFT__OIDX(ctx, o, a1, DP(tk)->data, DP(tk)->index);
			return;
		}
#endif/*ASMC_JMP_IFT__OIDX*/
#ifdef ASMC_JMP_IFT__EBP
		if(SP(tk)->tt == TT_EBPIDX) {
			KNH_ASM_JMP_IFT__ebp(ctx, o, a1, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_JMP_IFT__ebp(ctx, o, a1, 0);
			return;
		}
#endif/*ASMC_JMP_IFT__EBP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			KNH_ASM_JMP_IFT__ebp(ctx, o, a1, 0);
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Compiler_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));

#ifdef ASMC_JMP_IFT__EBP
		KNH_ASM_JMP_IFT__ebp(ctx, o, a1, 0);
		return;
#else
		DBG_P("unsupported stmt stt=%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_JMP_IFT__EBP*/
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFT__ebp(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_ebp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_ift_ebp_t *bw = (knh_asmc_jmp_ift_ebp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFT_ebp_SIZ);
		bw->code = ASMC_JMP_IFT__EBP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFT__sfp(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_sfp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_ift_sfp_t *bw = (knh_asmc_jmp_ift_sfp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFT_sfp_SIZ);
		bw->code = ASMC_JMP_IFT__SFP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFT__ofp(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_ofp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_ift_ofp_t *bw = (knh_asmc_jmp_ift_ofp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFT_ofp_SIZ);
		bw->code = ASMC_JMP_IFT__OFP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFT__OIDX(Ctx *ctx, Compiler *o, knh_bytes_t a1, Object* a2, knhvm_u1_t a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_ift_oidx_t *bw = (knh_asmc_jmp_ift_oidx_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFT_OIDX_SIZ);
		bw->code = ASMC_JMP_IFT__OIDX;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
		bw->a3 = a3;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFF(Ctx *ctx, Compiler *o, knh_bytes_t a1, Term *v)
{
	if(IS_Token((Token*)v)) {
		Token *tk = (Token*)v;
#ifdef ASMC_JMP_IFF__OBJ
		if(SP(tk)->tt == TT_CONST || SP(tk)->tt == TT_MTDMPR) {
			KNH_ASM_JMP_IFF__OBJ(ctx, o, a1, DP(tk)->data);
			return;
		}
#endif/*ASMC_JMP_IFF__OBJ*/
#ifdef ASMC_JMP_IFF__SFP
		if(SP(tk)->tt == TT_SFPIDX) {
			KNH_ASM_JMP_IFF__sfp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_JMP_IFF__SFP*/
#ifdef ASMC_JMP_IFF__OFP
		if(SP(tk)->tt == TT_FLDIDX) {
			KNH_ASM_JMP_IFF__ofp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_JMP_IFF__OFP*/
#ifdef ASMC_JMP_IFF__OIDX
		if(SP(tk)->tt == TT_OBJIDX) {
			KNH_ASM_JMP_IFF__OIDX(ctx, o, a1, DP(tk)->data, DP(tk)->index);
			return;
		}
#endif/*ASMC_JMP_IFF__OIDX*/
#ifdef ASMC_JMP_IFF__EBP
		if(SP(tk)->tt == TT_EBPIDX) {
			KNH_ASM_JMP_IFF__ebp(ctx, o, a1, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_JMP_IFF__ebp(ctx, o, a1, 0);
			return;
		}
#endif/*ASMC_JMP_IFF__EBP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			KNH_ASM_JMP_IFF__ebp(ctx, o, a1, 0);
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Compiler_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));

#ifdef ASMC_JMP_IFF__EBP
		KNH_ASM_JMP_IFF__ebp(ctx, o, a1, 0);
		return;
#else
		DBG_P("unsupported stmt stt=%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_JMP_IFF__EBP*/
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFF__ebp(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_ebp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_iff_ebp_t *bw = (knh_asmc_jmp_iff_ebp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFF_ebp_SIZ);
		bw->code = ASMC_JMP_IFF__EBP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFF__sfp(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_sfp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_iff_sfp_t *bw = (knh_asmc_jmp_iff_sfp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFF_sfp_SIZ);
		bw->code = ASMC_JMP_IFF__SFP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFF__ofp(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_ofp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_iff_ofp_t *bw = (knh_asmc_jmp_iff_ofp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFF_ofp_SIZ);
		bw->code = ASMC_JMP_IFF__OFP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFF__OIDX(Ctx *ctx, Compiler *o, knh_bytes_t a1, Object* a2, knhvm_u1_t a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_iff_oidx_t *bw = (knh_asmc_jmp_iff_oidx_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFF_OIDX_SIZ);
		bw->code = ASMC_JMP_IFF__OIDX;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
		bw->a3 = a3;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFTNN(Ctx *ctx, Compiler *o, knh_bytes_t a1, Term *v)
{
	if(IS_Token((Token*)v)) {
		Token *tk = (Token*)v;
#ifdef ASMC_JMP_IFTNN__OBJ
		if(SP(tk)->tt == TT_CONST || SP(tk)->tt == TT_MTDMPR) {
			KNH_ASM_JMP_IFTNN__OBJ(ctx, o, a1, DP(tk)->data);
			return;
		}
#endif/*ASMC_JMP_IFTNN__OBJ*/
#ifdef ASMC_JMP_IFTNN__SFP
		if(SP(tk)->tt == TT_SFPIDX) {
			KNH_ASM_JMP_IFTNN__sfp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_JMP_IFTNN__SFP*/
#ifdef ASMC_JMP_IFTNN__OFP
		if(SP(tk)->tt == TT_FLDIDX) {
			KNH_ASM_JMP_IFTNN__ofp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_JMP_IFTNN__OFP*/
#ifdef ASMC_JMP_IFTNN__OIDX
		if(SP(tk)->tt == TT_OBJIDX) {
			KNH_ASM_JMP_IFTNN__OIDX(ctx, o, a1, DP(tk)->data, DP(tk)->index);
			return;
		}
#endif/*ASMC_JMP_IFTNN__OIDX*/
#ifdef ASMC_JMP_IFTNN__EBP
		if(SP(tk)->tt == TT_EBPIDX) {
			KNH_ASM_JMP_IFTNN__ebp(ctx, o, a1, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_JMP_IFTNN__ebp(ctx, o, a1, 0);
			return;
		}
#endif/*ASMC_JMP_IFTNN__EBP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			KNH_ASM_JMP_IFTNN__ebp(ctx, o, a1, 0);
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Compiler_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));

#ifdef ASMC_JMP_IFTNN__EBP
		KNH_ASM_JMP_IFTNN__ebp(ctx, o, a1, 0);
		return;
#else
		DBG_P("unsupported stmt stt=%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_JMP_IFTNN__EBP*/
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFTNN__ebp(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_ebp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_iftnn_ebp_t *bw = (knh_asmc_jmp_iftnn_ebp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFTNN_ebp_SIZ);
		bw->code = ASMC_JMP_IFTNN__EBP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFTNN__sfp(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_sfp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_iftnn_sfp_t *bw = (knh_asmc_jmp_iftnn_sfp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFTNN_sfp_SIZ);
		bw->code = ASMC_JMP_IFTNN__SFP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFTNN__ofp(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_ofp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_iftnn_ofp_t *bw = (knh_asmc_jmp_iftnn_ofp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFTNN_ofp_SIZ);
		bw->code = ASMC_JMP_IFTNN__OFP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFTNN__OIDX(Ctx *ctx, Compiler *o, knh_bytes_t a1, Object* a2, knhvm_u1_t a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_iftnn_oidx_t *bw = (knh_asmc_jmp_iftnn_oidx_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFTNN_OIDX_SIZ);
		bw->code = ASMC_JMP_IFTNN__OIDX;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
		bw->a3 = a3;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFFN(Ctx *ctx, Compiler *o, knh_bytes_t a1, Term *v)
{
	if(IS_Token((Token*)v)) {
		Token *tk = (Token*)v;
#ifdef ASMC_JMP_IFFN__OBJ
		if(SP(tk)->tt == TT_CONST || SP(tk)->tt == TT_MTDMPR) {
			KNH_ASM_JMP_IFFN__OBJ(ctx, o, a1, DP(tk)->data);
			return;
		}
#endif/*ASMC_JMP_IFFN__OBJ*/
#ifdef ASMC_JMP_IFFN__SFP
		if(SP(tk)->tt == TT_SFPIDX) {
			KNH_ASM_JMP_IFFN__sfp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_JMP_IFFN__SFP*/
#ifdef ASMC_JMP_IFFN__OFP
		if(SP(tk)->tt == TT_FLDIDX) {
			KNH_ASM_JMP_IFFN__ofp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_JMP_IFFN__OFP*/
#ifdef ASMC_JMP_IFFN__OIDX
		if(SP(tk)->tt == TT_OBJIDX) {
			KNH_ASM_JMP_IFFN__OIDX(ctx, o, a1, DP(tk)->data, DP(tk)->index);
			return;
		}
#endif/*ASMC_JMP_IFFN__OIDX*/
#ifdef ASMC_JMP_IFFN__EBP
		if(SP(tk)->tt == TT_EBPIDX) {
			KNH_ASM_JMP_IFFN__ebp(ctx, o, a1, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_JMP_IFFN__ebp(ctx, o, a1, 0);
			return;
		}
#endif/*ASMC_JMP_IFFN__EBP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			KNH_ASM_JMP_IFFN__ebp(ctx, o, a1, 0);
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Compiler_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));

#ifdef ASMC_JMP_IFFN__EBP
		KNH_ASM_JMP_IFFN__ebp(ctx, o, a1, 0);
		return;
#else
		DBG_P("unsupported stmt stt=%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_JMP_IFFN__EBP*/
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFFN__ebp(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_ebp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_iffn_ebp_t *bw = (knh_asmc_jmp_iffn_ebp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFFN_ebp_SIZ);
		bw->code = ASMC_JMP_IFFN__EBP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFFN__sfp(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_sfp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_iffn_sfp_t *bw = (knh_asmc_jmp_iffn_sfp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFFN_sfp_SIZ);
		bw->code = ASMC_JMP_IFFN__SFP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFFN__ofp(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_ofp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_iffn_ofp_t *bw = (knh_asmc_jmp_iffn_ofp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFFN_ofp_SIZ);
		bw->code = ASMC_JMP_IFFN__OFP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFFN__OIDX(Ctx *ctx, Compiler *o, knh_bytes_t a1, Object* a2, knhvm_u1_t a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_iffn_oidx_t *bw = (knh_asmc_jmp_iffn_oidx_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFFN_OIDX_SIZ);
		bw->code = ASMC_JMP_IFFN__OIDX;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
		bw->a3 = a3;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFNN(Ctx *ctx, Compiler *o, knh_bytes_t a1, Term *v)
{
	if(IS_Token((Token*)v)) {
		Token *tk = (Token*)v;
#ifdef ASMC_JMP_IFNN__OBJ
		if(SP(tk)->tt == TT_CONST || SP(tk)->tt == TT_MTDMPR) {
			KNH_ASM_JMP_IFNN__OBJ(ctx, o, a1, DP(tk)->data);
			return;
		}
#endif/*ASMC_JMP_IFNN__OBJ*/
#ifdef ASMC_JMP_IFNN__SFP
		if(SP(tk)->tt == TT_SFPIDX) {
			KNH_ASM_JMP_IFNN__sfp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_JMP_IFNN__SFP*/
#ifdef ASMC_JMP_IFNN__OFP
		if(SP(tk)->tt == TT_FLDIDX) {
			KNH_ASM_JMP_IFNN__ofp(ctx, o, a1, DP(tk)->index);
			return;
		}
#endif/*ASMC_JMP_IFNN__OFP*/
#ifdef ASMC_JMP_IFNN__OIDX
		if(SP(tk)->tt == TT_OBJIDX) {
			KNH_ASM_JMP_IFNN__OIDX(ctx, o, a1, DP(tk)->data, DP(tk)->index);
			return;
		}
#endif/*ASMC_JMP_IFNN__OIDX*/
#ifdef ASMC_JMP_IFNN__EBP
		if(SP(tk)->tt == TT_EBPIDX) {
			KNH_ASM_JMP_IFNN__ebp(ctx, o, a1, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_JMP_IFNN__ebp(ctx, o, a1, 0);
			return;
		}
#endif/*ASMC_JMP_IFNN__EBP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			KNH_ASM_JMP_IFNN__ebp(ctx, o, a1, 0);
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Compiler_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));

#ifdef ASMC_JMP_IFNN__EBP
		KNH_ASM_JMP_IFNN__ebp(ctx, o, a1, 0);
		return;
#else
		DBG_P("unsupported stmt stt=%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_JMP_IFNN__EBP*/
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFNN__ebp(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_ebp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_ifnn_ebp_t *bw = (knh_asmc_jmp_ifnn_ebp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFNN_ebp_SIZ);
		bw->code = ASMC_JMP_IFNN__EBP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFNN__sfp(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_sfp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_ifnn_sfp_t *bw = (knh_asmc_jmp_ifnn_sfp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFNN_sfp_SIZ);
		bw->code = ASMC_JMP_IFNN__SFP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFNN__ofp(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_ofp_t a2)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_ifnn_ofp_t *bw = (knh_asmc_jmp_ifnn_ofp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFNN_ofp_SIZ);
		bw->code = ASMC_JMP_IFNN__OFP;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFNN__OIDX(Ctx *ctx, Compiler *o, knh_bytes_t a1, Object* a2, knhvm_u1_t a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_jmp_ifnn_oidx_t *bw = (knh_asmc_jmp_ifnn_oidx_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_JMP_IFNN_OIDX_SIZ);
		bw->code = ASMC_JMP_IFNN__OIDX;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
		bw->a3 = a3;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NEXT(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_sfp_t a2, knhvm_sfp_t a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_next_t *bw = (knh_asmc_next_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_NEXT_SIZ);
		bw->code = ASMC_NEXT;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
		bw->a3 = a3;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MAPNEXT(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_sfp_t a2, knhvm_sfp_t a3, knhvm_class_t a4)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_mapnext_t *bw = (knh_asmc_mapnext_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_MAPNEXT_SIZ);
		bw->code = ASMC_MAPNEXT;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
		bw->a3 = a3;
		bw->a4 = a4;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_SMAPNEXT(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_sfp_t a2, knhvm_sfp_t a3, Object* a4)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_smapnext_t *bw = (knh_asmc_smapnext_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_SMAPNEXT_SIZ);
		bw->code = ASMC_SMAPNEXT;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
		bw->a3 = a3;
		bw->a4 = a4;
		knh_Object_RCinc(bw->a4);
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_TRY_BEGIN(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_sfp_t a2, knhvm_sfp_t a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_try_begin_t *bw = (knh_asmc_try_begin_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_TRY_BEGIN_SIZ);
		bw->code = ASMC_TRY_BEGIN;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
		bw->a3 = a3;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_TRY_END(Ctx *ctx, Compiler *o, knhvm_sfp_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_try_end_t *bw = (knh_asmc_try_end_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_TRY_END_SIZ);
		bw->code = ASMC_TRY_END;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_CATCH(Ctx *ctx, Compiler *o, knh_bytes_t a1, knhvm_expt_t a2, knhvm_sfp_t a3)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_catch_t *bw = (knh_asmc_catch_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_CATCH_SIZ);
		bw->code = ASMC_CATCH;
		bw->a1 = knh_Compiler_labelId(ctx, o, a1);
		bw->a2 = a2;
		bw->a3 = a3;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_THROW(Ctx *ctx, Compiler *o, Term *v)
{
	if(IS_Token((Token*)v)) {
		Token *tk = (Token*)v;
#ifdef ASMC_THROW__OBJ
		if(SP(tk)->tt == TT_CONST || SP(tk)->tt == TT_MTDMPR) {
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			return;
		}
#endif/*ASMC_THROW__OBJ*/
#ifdef ASMC_THROW__SFP
		if(SP(tk)->tt == TT_SFPIDX) {
			KNH_ASM_THROW__sfp(ctx, o, DP(tk)->index);
			return;
		}
#endif/*ASMC_THROW__SFP*/
#ifdef ASMC_THROW__OFP
		if(SP(tk)->tt == TT_FLDIDX) {
			KNH_ASM_THROW__ofp(ctx, o, DP(tk)->index);
			return;
		}
#endif/*ASMC_THROW__OFP*/
#ifdef ASMC_THROW__OIDX
		if(SP(tk)->tt == TT_OBJIDX) {
			KNH_ASM_THROW__OIDX(ctx, o, DP(tk)->data, DP(tk)->index);
			return;
		}
#endif/*ASMC_THROW__OIDX*/
#ifdef ASMC_THROW__EBP
		if(SP(tk)->tt == TT_EBPIDX) {
			KNH_ASM_THROW__ebp(ctx, o, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_THROW__ebp(ctx, o, 0);
			return;
		}
#endif/*ASMC_THROW__EBP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			KNH_ASM_THROW__ebp(ctx, o, 0);
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Compiler_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));

#ifdef ASMC_THROW__EBP
		KNH_ASM_THROW__ebp(ctx, o, 0);
		return;
#else
		DBG_P("unsupported stmt stt=%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_THROW__EBP*/
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_THROW__ebp(Ctx *ctx, Compiler *o, knhvm_ebp_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_throw_ebp_t *bw = (knh_asmc_throw_ebp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_THROW_ebp_SIZ);
		bw->code = ASMC_THROW__EBP;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_THROW__sfp(Ctx *ctx, Compiler *o, knhvm_sfp_t a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_throw_sfp_t *bw = (knh_asmc_throw_sfp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_THROW_sfp_SIZ);
		bw->code = ASMC_THROW__SFP;
		bw->a1 = a1;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_THROW__OBJ(Ctx *ctx, Compiler *o, Object* a1)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_throw_obj_t *bw = (knh_asmc_throw_obj_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_THROW_OBJ_SIZ);
		bw->code = ASMC_THROW__OBJ;
		bw->a1 = a1;
		knh_Object_RCinc(bw->a1);
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PRINT(Ctx *ctx, Compiler *o, knhvm_u2_t a1, Object* a2, knhvm_methodn_t a3, Term *v)
{
	if(IS_Token((Token*)v)) {
		Token *tk = (Token*)v;
#ifdef ASMC_PRINT__OBJ
		if(SP(tk)->tt == TT_CONST || SP(tk)->tt == TT_MTDMPR) {
			KNH_ASM_PRINT__OBJ(ctx, o, a1, a2, a3, DP(tk)->data);
			return;
		}
#endif/*ASMC_PRINT__OBJ*/
#ifdef ASMC_PRINT__SFP
		if(SP(tk)->tt == TT_SFPIDX) {
			KNH_ASM_PRINT__sfp(ctx, o, a1, a2, a3, DP(tk)->index);
			return;
		}
#endif/*ASMC_PRINT__SFP*/
#ifdef ASMC_PRINT__OFP
		if(SP(tk)->tt == TT_FLDIDX) {
			KNH_ASM_PRINT__ofp(ctx, o, a1, a2, a3, DP(tk)->index);
			return;
		}
#endif/*ASMC_PRINT__OFP*/
#ifdef ASMC_PRINT__OIDX
		if(SP(tk)->tt == TT_OBJIDX) {
			KNH_ASM_PRINT__OIDX(ctx, o, a1, a2, a3, DP(tk)->data, DP(tk)->index);
			return;
		}
#endif/*ASMC_PRINT__OIDX*/
#ifdef ASMC_PRINT__EBP
		if(SP(tk)->tt == TT_EBPIDX) {
			KNH_ASM_PRINT__ebp(ctx, o, a1, a2, a3, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_PRINT__ebp(ctx, o, a1, a2, a3, 0);
			return;
		}
#endif/*ASMC_PRINT__EBP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			KNH_ASM_PRINT__ebp(ctx, o, a1, a2, a3, 0);
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Compiler_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));

#ifdef ASMC_PRINT__EBP
		KNH_ASM_PRINT__ebp(ctx, o, a1, a2, a3, 0);
		return;
#else
		DBG_P("unsupported stmt stt=%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_PRINT__EBP*/
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PRINT__ebp(Ctx *ctx, Compiler *o, knhvm_u2_t a1, Object* a2, knhvm_methodn_t a3, knhvm_ebp_t a4)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_print_ebp_t *bw = (knh_asmc_print_ebp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_PRINT_ebp_SIZ);
		bw->code = ASMC_PRINT__EBP;
		bw->a1 = a1;
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
		bw->a3 = a3;
		bw->a4 = a4;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PRINT__sfp(Ctx *ctx, Compiler *o, knhvm_u2_t a1, Object* a2, knhvm_methodn_t a3, knhvm_sfp_t a4)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_print_sfp_t *bw = (knh_asmc_print_sfp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_PRINT_sfp_SIZ);
		bw->code = ASMC_PRINT__SFP;
		bw->a1 = a1;
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
		bw->a3 = a3;
		bw->a4 = a4;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PRINT__ofp(Ctx *ctx, Compiler *o, knhvm_u2_t a1, Object* a2, knhvm_methodn_t a3, knhvm_ofp_t a4)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_print_ofp_t *bw = (knh_asmc_print_ofp_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_PRINT_ofp_SIZ);
		bw->code = ASMC_PRINT__OFP;
		bw->a1 = a1;
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
		bw->a3 = a3;
		bw->a4 = a4;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PRINT__OBJ(Ctx *ctx, Compiler *o, knhvm_u2_t a1, Object* a2, knhvm_methodn_t a3, Object* a4)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_print_obj_t *bw = (knh_asmc_print_obj_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_PRINT_OBJ_SIZ);
		bw->code = ASMC_PRINT__OBJ;
		bw->a1 = a1;
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
		bw->a3 = a3;
		bw->a4 = a4;
		knh_Object_RCinc(bw->a4);
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PRINT__OIDX(Ctx *ctx, Compiler *o, knhvm_u2_t a1, Object* a2, knhvm_methodn_t a3, Object* a4, knhvm_u1_t a5)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_print_oidx_t *bw = (knh_asmc_print_oidx_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_PRINT_OIDX_SIZ);
		bw->code = ASMC_PRINT__OIDX;
		bw->a1 = a1;
		bw->a2 = a2;
		knh_Object_RCinc(bw->a2);
		bw->a3 = a3;
		bw->a4 = a4;
		knh_Object_RCinc(bw->a4);
		bw->a5 = a5;
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NOP(Ctx *ctx, Compiler *o)
{
	if(!knh_Compiler_isStopped(o)) {
		knh_asmc_nop_t *bw = (knh_asmc_nop_t*)knh_Compiler_asmmalloc(ctx, o, KNH_ASMC_NOP_SIZ);
		bw->code = ASMC_NOP;
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
