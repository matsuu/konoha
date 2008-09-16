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

#define PCT_(pc)    (((knh_asmc_nop_t*)pc)->code)

/* ------------------------------------------------------------------------ */

/* ======================================================================== */
/* [label] */


void knh_Compiler_rewriteAddress(Ctx *ctx, Compiler *o, knh_asmc_jmp_t *bw)
{
	//DBG_P("label: id=%d", knh_KLRCode_uread_short(pc));
	String *name = knh_DictIdx_get(DP(o)->labelIdDictIdx, bw->a1);
	KNH_ASSERT(IS_NOTNULL(name));
	knhvmc_t *pa = (knhvmc_t*)knh_DictSet_get__b(DP(o)->labelAddrDictSet, knh_String_tobytes(name));
	if(pa == NULL) {
		TODO();
		DBG_P("Asm!!: Unknown Label '%s'", knh_String_tochar(name));
	}else {
		bw->a1 = (knh_short_t)(pa - (knhvmc_t*)bw);
	}
}

/* ------------------------------------------------------------------------ */

void knh_Compiler_remapAddress(Ctx *ctx, Compiler *o)
{
	knhvmc_t *pc = (knhvmc_t*)knh_Bytes_tochar(DP(o)->elf);
	knhvmc_t *tail = pc + knh_Bytes_size(DP(o)->elf);
	while(pc < tail) {
		switch(PCT_(pc)) {
		case ASMC_HALT :
			pc += KNH_ASMC_HALT_SIZ;
			break;
		case ASMC_RET__EBP :
			pc += KNH_ASMC_RET_ebp_SIZ;
			break;
		case ASMC_RET__SFP :
			pc += KNH_ASMC_RET_sfp_SIZ;
			break;
		case ASMC_RET__OFP :
			pc += KNH_ASMC_RET_ofp_SIZ;
			break;
		case ASMC_RET__OBJ :
			pc += KNH_ASMC_RET_OBJ_SIZ;
			break;
		case ASMC_RET__OIDX :
			pc += KNH_ASMC_RET_OIDX_SIZ;
			break;
		case ASMC_MOVE__EBP :
			pc += KNH_ASMC_MOVE_ebp_SIZ;
			break;
		case ASMC_MOVE__SFP :
			pc += KNH_ASMC_MOVE_sfp_SIZ;
			break;
		case ASMC_MOVE__OFP :
			pc += KNH_ASMC_MOVE_ofp_SIZ;
			break;
		case ASMC_MOVE__OBJ :
			pc += KNH_ASMC_MOVE_OBJ_SIZ;
			break;
		case ASMC_MOVE__OIDX :
			pc += KNH_ASMC_MOVE_OIDX_SIZ;
			break;
		case ASMC_MOVS__EBP :
			pc += KNH_ASMC_MOVS_ebp_SIZ;
			break;
		case ASMC_MOVS__SFP :
			pc += KNH_ASMC_MOVS_sfp_SIZ;
			break;
		case ASMC_MOVS__OFP :
			pc += KNH_ASMC_MOVS_ofp_SIZ;
			break;
		case ASMC_MOVS__OBJ :
			pc += KNH_ASMC_MOVS_OBJ_SIZ;
			break;
		case ASMC_MOVS__OIDX :
			pc += KNH_ASMC_MOVS_OIDX_SIZ;
			break;
		case ASMC_MOVO__EBP :
			pc += KNH_ASMC_MOVO_ebp_SIZ;
			break;
		case ASMC_MOVO__SFP :
			pc += KNH_ASMC_MOVO_sfp_SIZ;
			break;
		case ASMC_MOVO__OFP :
			pc += KNH_ASMC_MOVO_ofp_SIZ;
			break;
		case ASMC_MOVO__OBJ :
			pc += KNH_ASMC_MOVO_OBJ_SIZ;
			break;
		case ASMC_MOVO__OIDX :
			pc += KNH_ASMC_MOVO_OIDX_SIZ;
			break;
		case ASMC_MOVOI__EBP :
			pc += KNH_ASMC_MOVOI_ebp_SIZ;
			break;
		case ASMC_MOVOI__SFP :
			pc += KNH_ASMC_MOVOI_sfp_SIZ;
			break;
		case ASMC_MOVOI__OFP :
			pc += KNH_ASMC_MOVOI_ofp_SIZ;
			break;
		case ASMC_MOVOI__OBJ :
			pc += KNH_ASMC_MOVOI_OBJ_SIZ;
			break;
		case ASMC_MOVOI__OIDX :
			pc += KNH_ASMC_MOVOI_OIDX_SIZ;
			break;
		case ASMC_MOVSFP_IFNUL :
			pc += KNH_ASMC_MOVSFP_IFNUL_SIZ;
			break;
		case ASMC_PUSH__EBP :
			pc += KNH_ASMC_PUSH_ebp_SIZ;
			break;
		case ASMC_PUSH__SFP :
			pc += KNH_ASMC_PUSH_sfp_SIZ;
			break;
		case ASMC_PUSH__OFP :
			pc += KNH_ASMC_PUSH_ofp_SIZ;
			break;
		case ASMC_PUSH__OBJ :
			pc += KNH_ASMC_PUSH_OBJ_SIZ;
			break;
		case ASMC_PUSH__OIDX :
			pc += KNH_ASMC_PUSH_OIDX_SIZ;
			break;
		case ASMC_PUT_SYSCONST :
			pc += KNH_ASMC_PUT_SYSCONST_SIZ;
			break;
		case ASMC_PUSH_SYSCONST :
			pc += KNH_ASMC_PUSH_SYSCONST_SIZ;
			break;
		case ASMC_PUSH__DEF :
			pc += KNH_ASMC_PUSH_DEF_SIZ;
			break;
		case ASMC_VARGS :
			pc += KNH_ASMC_VARGS_SIZ;
			break;
		case ASMC_SHIFT :
			pc += KNH_ASMC_SHIFT_SIZ;
			break;
		case ASMC_SCALL :
			pc += KNH_ASMC_SCALL_SIZ;
			break;
		case ASMC_NSCALL :
			pc += KNH_ASMC_NSCALL_SIZ;
			break;
		case ASMC_CALL :
			pc += KNH_ASMC_CALL_SIZ;
			break;
		case ASMC_DCALL :
			pc += KNH_ASMC_DCALL_SIZ;
			break;
		case ASMC_NEW :
			pc += KNH_ASMC_NEW_SIZ;
			break;
		case ASMC_MT :
			pc += KNH_ASMC_MT_SIZ;
			break;
		case ASMC_SMAP :
			pc += KNH_ASMC_SMAP_SIZ;
			break;
		case ASMC_SMAPE :
			pc += KNH_ASMC_SMAPE_SIZ;
			break;
		case ASMC_MAP :
			pc += KNH_ASMC_MAP_SIZ;
			break;
		case ASMC_MAPE :
			pc += KNH_ASMC_MAPE_SIZ;
			break;
		case ASMC_ANYMAP :
			pc += KNH_ASMC_ANYMAP_SIZ;
			break;
		case ASMC_ANYMAPE :
			pc += KNH_ASMC_ANYMAPE_SIZ;
			break;
		case ASMC_MAP2 :
			pc += KNH_ASMC_MAP2_SIZ;
			break;
		case ASMC_MAP2E :
			pc += KNH_ASMC_MAP2E_SIZ;
			break;
		case ASMC_TYPECHK__EBP :
			pc += KNH_ASMC_TYPECHK_ebp_SIZ;
			break;
		case ASMC_TYPECHK__SFP :
			pc += KNH_ASMC_TYPECHK_sfp_SIZ;
			break;
		case ASMC_TYPECHK__OFP :
			pc += KNH_ASMC_TYPECHK_ofp_SIZ;
			break;
		case ASMC_TYPECHK__OBJ :
			pc += KNH_ASMC_TYPECHK_OBJ_SIZ;
			break;
		case ASMC_TYPECHK__OIDX :
			pc += KNH_ASMC_TYPECHK_OIDX_SIZ;
			break;
		case ASMC_NULLCHK__EBP :
			pc += KNH_ASMC_NULLCHK_ebp_SIZ;
			break;
		case ASMC_NULLCHK__SFP :
			pc += KNH_ASMC_NULLCHK_sfp_SIZ;
			break;
		case ASMC_NULLCHK__OFP :
			pc += KNH_ASMC_NULLCHK_ofp_SIZ;
			break;
		case ASMC_NULLCHK__OBJ :
			pc += KNH_ASMC_NULLCHK_OBJ_SIZ;
			break;
		case ASMC_NULLCHK__OIDX :
			pc += KNH_ASMC_NULLCHK_OIDX_SIZ;
			break;
		case ASMC_JMP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_SIZ;
			break;
		case ASMC_SKIP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_SKIP_SIZ;
			break;
		case ASMC_JMP_IFT__EBP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFT_ebp_SIZ;
			break;
		case ASMC_JMP_IFT__SFP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFT_sfp_SIZ;
			break;
		case ASMC_JMP_IFT__OFP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFT_ofp_SIZ;
			break;
		case ASMC_JMP_IFT__OIDX :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFT_OIDX_SIZ;
			break;
		case ASMC_JMP_IFF__EBP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFF_ebp_SIZ;
			break;
		case ASMC_JMP_IFF__SFP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFF_sfp_SIZ;
			break;
		case ASMC_JMP_IFF__OFP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFF_ofp_SIZ;
			break;
		case ASMC_JMP_IFF__OIDX :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFF_OIDX_SIZ;
			break;
		case ASMC_JMP_IFTNN__EBP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFTNN_ebp_SIZ;
			break;
		case ASMC_JMP_IFTNN__SFP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFTNN_sfp_SIZ;
			break;
		case ASMC_JMP_IFTNN__OFP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFTNN_ofp_SIZ;
			break;
		case ASMC_JMP_IFTNN__OIDX :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFTNN_OIDX_SIZ;
			break;
		case ASMC_JMP_IFFN__EBP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFFN_ebp_SIZ;
			break;
		case ASMC_JMP_IFFN__SFP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFFN_sfp_SIZ;
			break;
		case ASMC_JMP_IFFN__OFP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFFN_ofp_SIZ;
			break;
		case ASMC_JMP_IFFN__OIDX :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFFN_OIDX_SIZ;
			break;
		case ASMC_JMP_IFNN__EBP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFNN_ebp_SIZ;
			break;
		case ASMC_JMP_IFNN__SFP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFNN_sfp_SIZ;
			break;
		case ASMC_JMP_IFNN__OFP :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFNN_ofp_SIZ;
			break;
		case ASMC_JMP_IFNN__OIDX :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFNN_OIDX_SIZ;
			break;
		case ASMC_NEXT :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_NEXT_SIZ;
			break;
		case ASMC_MAPNEXT :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_MAPNEXT_SIZ;
			break;
		case ASMC_SMAPNEXT :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_SMAPNEXT_SIZ;
			break;
		case ASMC_TRY_BEGIN :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_TRY_BEGIN_SIZ;
			break;
		case ASMC_TRY_END :
			pc += KNH_ASMC_TRY_END_SIZ;
			break;
		case ASMC_CATCH :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_CATCH_SIZ;
			break;
		case ASMC_THROW__EBP :
			pc += KNH_ASMC_THROW_ebp_SIZ;
			break;
		case ASMC_THROW__SFP :
			pc += KNH_ASMC_THROW_sfp_SIZ;
			break;
		case ASMC_THROW__OBJ :
			pc += KNH_ASMC_THROW_OBJ_SIZ;
			break;
		case ASMC_PRINT__EBP :
			pc += KNH_ASMC_PRINT_ebp_SIZ;
			break;
		case ASMC_PRINT__SFP :
			pc += KNH_ASMC_PRINT_sfp_SIZ;
			break;
		case ASMC_PRINT__OFP :
			pc += KNH_ASMC_PRINT_ofp_SIZ;
			break;
		case ASMC_PRINT__OBJ :
			pc += KNH_ASMC_PRINT_OBJ_SIZ;
			break;
		case ASMC_PRINT__OIDX :
			pc += KNH_ASMC_PRINT_OIDX_SIZ;
			break;
		case ASMC_NOP :
			pc += KNH_ASMC_NOP_SIZ;
			break;

		default :
			DBG_P("UNKNOWN VMCODE: %d\n", PCT_(pc));
			KNH_ASSERT(ctx == NULL);
			return;
		}
	}
}

/* ======================================================================== */
/* [vmc] */

void knh_KLRCode_utraverse(Ctx *ctx, knh_bytes_t vmc, f_traverse gc)
{
	knhvmc_t *pc = (knhvmc_t*)vmc.buf;
	knhvmc_t *tail = vmc.buf + vmc.len;
	while(pc < tail) {
		switch(PCT_(pc)) {
		case ASMC_HALT :
			pc += KNH_ASMC_HALT_SIZ;
			break;

		case ASMC_RET__EBP :
			pc += KNH_ASMC_RET_ebp_SIZ;
			break;

		case ASMC_RET__SFP :
			pc += KNH_ASMC_RET_sfp_SIZ;
			break;

		case ASMC_RET__OFP :
			pc += KNH_ASMC_RET_ofp_SIZ;
			break;

		case ASMC_RET__OBJ :
			gc(ctx, ((knh_asmc_ret_obj_t*)pc)->a1);
			pc += KNH_ASMC_RET_OBJ_SIZ;
			break;

		case ASMC_RET__OIDX :
			gc(ctx, ((knh_asmc_ret_oidx_t*)pc)->a1);
			pc += KNH_ASMC_RET_OIDX_SIZ;
			break;

		case ASMC_MOVE__EBP :
			pc += KNH_ASMC_MOVE_ebp_SIZ;
			break;

		case ASMC_MOVE__SFP :
			pc += KNH_ASMC_MOVE_sfp_SIZ;
			break;

		case ASMC_MOVE__OFP :
			pc += KNH_ASMC_MOVE_ofp_SIZ;
			break;

		case ASMC_MOVE__OBJ :
			gc(ctx, ((knh_asmc_move_obj_t*)pc)->a2);
			pc += KNH_ASMC_MOVE_OBJ_SIZ;
			break;

		case ASMC_MOVE__OIDX :
			gc(ctx, ((knh_asmc_move_oidx_t*)pc)->a2);
			pc += KNH_ASMC_MOVE_OIDX_SIZ;
			break;

		case ASMC_MOVS__EBP :
			pc += KNH_ASMC_MOVS_ebp_SIZ;
			break;

		case ASMC_MOVS__SFP :
			pc += KNH_ASMC_MOVS_sfp_SIZ;
			break;

		case ASMC_MOVS__OFP :
			pc += KNH_ASMC_MOVS_ofp_SIZ;
			break;

		case ASMC_MOVS__OBJ :
			gc(ctx, ((knh_asmc_movs_obj_t*)pc)->a2);
			pc += KNH_ASMC_MOVS_OBJ_SIZ;
			break;

		case ASMC_MOVS__OIDX :
			gc(ctx, ((knh_asmc_movs_oidx_t*)pc)->a2);
			pc += KNH_ASMC_MOVS_OIDX_SIZ;
			break;

		case ASMC_MOVO__EBP :
			pc += KNH_ASMC_MOVO_ebp_SIZ;
			break;

		case ASMC_MOVO__SFP :
			pc += KNH_ASMC_MOVO_sfp_SIZ;
			break;

		case ASMC_MOVO__OFP :
			pc += KNH_ASMC_MOVO_ofp_SIZ;
			break;

		case ASMC_MOVO__OBJ :
			gc(ctx, ((knh_asmc_movo_obj_t*)pc)->a2);
			pc += KNH_ASMC_MOVO_OBJ_SIZ;
			break;

		case ASMC_MOVO__OIDX :
			gc(ctx, ((knh_asmc_movo_oidx_t*)pc)->a2);
			pc += KNH_ASMC_MOVO_OIDX_SIZ;
			break;

		case ASMC_MOVOI__EBP :
			gc(ctx, ((knh_asmc_movoi_ebp_t*)pc)->a1);
			pc += KNH_ASMC_MOVOI_ebp_SIZ;
			break;

		case ASMC_MOVOI__SFP :
			gc(ctx, ((knh_asmc_movoi_sfp_t*)pc)->a1);
			pc += KNH_ASMC_MOVOI_sfp_SIZ;
			break;

		case ASMC_MOVOI__OFP :
			gc(ctx, ((knh_asmc_movoi_ofp_t*)pc)->a1);
			pc += KNH_ASMC_MOVOI_ofp_SIZ;
			break;

		case ASMC_MOVOI__OBJ :
			gc(ctx, ((knh_asmc_movoi_obj_t*)pc)->a1);
			gc(ctx, ((knh_asmc_movoi_obj_t*)pc)->a3);
			pc += KNH_ASMC_MOVOI_OBJ_SIZ;
			break;

		case ASMC_MOVOI__OIDX :
			gc(ctx, ((knh_asmc_movoi_oidx_t*)pc)->a1);
			gc(ctx, ((knh_asmc_movoi_oidx_t*)pc)->a3);
			pc += KNH_ASMC_MOVOI_OIDX_SIZ;
			break;

		case ASMC_MOVSFP_IFNUL :
			gc(ctx, ((knh_asmc_movsfp_ifnul_t*)pc)->a2);
			pc += KNH_ASMC_MOVSFP_IFNUL_SIZ;
			break;

		case ASMC_PUSH__EBP :
			pc += KNH_ASMC_PUSH_ebp_SIZ;
			break;

		case ASMC_PUSH__SFP :
			pc += KNH_ASMC_PUSH_sfp_SIZ;
			break;

		case ASMC_PUSH__OFP :
			pc += KNH_ASMC_PUSH_ofp_SIZ;
			break;

		case ASMC_PUSH__OBJ :
			gc(ctx, ((knh_asmc_push_obj_t*)pc)->a1);
			pc += KNH_ASMC_PUSH_OBJ_SIZ;
			break;

		case ASMC_PUSH__OIDX :
			gc(ctx, ((knh_asmc_push_oidx_t*)pc)->a1);
			pc += KNH_ASMC_PUSH_OIDX_SIZ;
			break;

		case ASMC_PUT_SYSCONST :
			pc += KNH_ASMC_PUT_SYSCONST_SIZ;
			break;

		case ASMC_PUSH_SYSCONST :
			pc += KNH_ASMC_PUSH_SYSCONST_SIZ;
			break;

		case ASMC_PUSH__DEF :
			pc += KNH_ASMC_PUSH_DEF_SIZ;
			break;

		case ASMC_VARGS :
			pc += KNH_ASMC_VARGS_SIZ;
			break;

		case ASMC_SHIFT :
			pc += KNH_ASMC_SHIFT_SIZ;
			break;

		case ASMC_SCALL :
			pc += KNH_ASMC_SCALL_SIZ;
			break;

		case ASMC_NSCALL :
			pc += KNH_ASMC_NSCALL_SIZ;
			break;

		case ASMC_CALL :
			pc += KNH_ASMC_CALL_SIZ;
			break;

		case ASMC_DCALL :
			pc += KNH_ASMC_DCALL_SIZ;
			break;

		case ASMC_NEW :
			pc += KNH_ASMC_NEW_SIZ;
			break;

		case ASMC_MT :
			pc += KNH_ASMC_MT_SIZ;
			break;

		case ASMC_SMAP :
			gc(ctx, ((knh_asmc_smap_t*)pc)->a1);
			pc += KNH_ASMC_SMAP_SIZ;
			break;

		case ASMC_SMAPE :
			gc(ctx, ((knh_asmc_smape_t*)pc)->a1);
			pc += KNH_ASMC_SMAPE_SIZ;
			break;

		case ASMC_MAP :
			pc += KNH_ASMC_MAP_SIZ;
			break;

		case ASMC_MAPE :
			pc += KNH_ASMC_MAPE_SIZ;
			break;

		case ASMC_ANYMAP :
			pc += KNH_ASMC_ANYMAP_SIZ;
			break;

		case ASMC_ANYMAPE :
			pc += KNH_ASMC_ANYMAPE_SIZ;
			break;

		case ASMC_MAP2 :
			pc += KNH_ASMC_MAP2_SIZ;
			break;

		case ASMC_MAP2E :
			pc += KNH_ASMC_MAP2E_SIZ;
			break;

		case ASMC_TYPECHK__EBP :
			pc += KNH_ASMC_TYPECHK_ebp_SIZ;
			break;

		case ASMC_TYPECHK__SFP :
			pc += KNH_ASMC_TYPECHK_sfp_SIZ;
			break;

		case ASMC_TYPECHK__OFP :
			pc += KNH_ASMC_TYPECHK_ofp_SIZ;
			break;

		case ASMC_TYPECHK__OBJ :
			gc(ctx, ((knh_asmc_typechk_obj_t*)pc)->a2);
			pc += KNH_ASMC_TYPECHK_OBJ_SIZ;
			break;

		case ASMC_TYPECHK__OIDX :
			gc(ctx, ((knh_asmc_typechk_oidx_t*)pc)->a2);
			pc += KNH_ASMC_TYPECHK_OIDX_SIZ;
			break;

		case ASMC_NULLCHK__EBP :
			pc += KNH_ASMC_NULLCHK_ebp_SIZ;
			break;

		case ASMC_NULLCHK__SFP :
			pc += KNH_ASMC_NULLCHK_sfp_SIZ;
			break;

		case ASMC_NULLCHK__OFP :
			pc += KNH_ASMC_NULLCHK_ofp_SIZ;
			break;

		case ASMC_NULLCHK__OBJ :
			gc(ctx, ((knh_asmc_nullchk_obj_t*)pc)->a1);
			pc += KNH_ASMC_NULLCHK_OBJ_SIZ;
			break;

		case ASMC_NULLCHK__OIDX :
			gc(ctx, ((knh_asmc_nullchk_oidx_t*)pc)->a1);
			pc += KNH_ASMC_NULLCHK_OIDX_SIZ;
			break;

		case ASMC_JMP :
			pc += KNH_ASMC_JMP_SIZ;
			break;

		case ASMC_SKIP :
			pc += KNH_ASMC_SKIP_SIZ;
			break;

		case ASMC_JMP_IFT__EBP :
			pc += KNH_ASMC_JMP_IFT_ebp_SIZ;
			break;

		case ASMC_JMP_IFT__SFP :
			pc += KNH_ASMC_JMP_IFT_sfp_SIZ;
			break;

		case ASMC_JMP_IFT__OFP :
			pc += KNH_ASMC_JMP_IFT_ofp_SIZ;
			break;

		case ASMC_JMP_IFT__OIDX :
			gc(ctx, ((knh_asmc_jmp_ift_oidx_t*)pc)->a2);
			pc += KNH_ASMC_JMP_IFT_OIDX_SIZ;
			break;

		case ASMC_JMP_IFF__EBP :
			pc += KNH_ASMC_JMP_IFF_ebp_SIZ;
			break;

		case ASMC_JMP_IFF__SFP :
			pc += KNH_ASMC_JMP_IFF_sfp_SIZ;
			break;

		case ASMC_JMP_IFF__OFP :
			pc += KNH_ASMC_JMP_IFF_ofp_SIZ;
			break;

		case ASMC_JMP_IFF__OIDX :
			gc(ctx, ((knh_asmc_jmp_iff_oidx_t*)pc)->a2);
			pc += KNH_ASMC_JMP_IFF_OIDX_SIZ;
			break;

		case ASMC_JMP_IFTNN__EBP :
			pc += KNH_ASMC_JMP_IFTNN_ebp_SIZ;
			break;

		case ASMC_JMP_IFTNN__SFP :
			pc += KNH_ASMC_JMP_IFTNN_sfp_SIZ;
			break;

		case ASMC_JMP_IFTNN__OFP :
			pc += KNH_ASMC_JMP_IFTNN_ofp_SIZ;
			break;

		case ASMC_JMP_IFTNN__OIDX :
			gc(ctx, ((knh_asmc_jmp_iftnn_oidx_t*)pc)->a2);
			pc += KNH_ASMC_JMP_IFTNN_OIDX_SIZ;
			break;

		case ASMC_JMP_IFFN__EBP :
			pc += KNH_ASMC_JMP_IFFN_ebp_SIZ;
			break;

		case ASMC_JMP_IFFN__SFP :
			pc += KNH_ASMC_JMP_IFFN_sfp_SIZ;
			break;

		case ASMC_JMP_IFFN__OFP :
			pc += KNH_ASMC_JMP_IFFN_ofp_SIZ;
			break;

		case ASMC_JMP_IFFN__OIDX :
			gc(ctx, ((knh_asmc_jmp_iffn_oidx_t*)pc)->a2);
			pc += KNH_ASMC_JMP_IFFN_OIDX_SIZ;
			break;

		case ASMC_JMP_IFNN__EBP :
			pc += KNH_ASMC_JMP_IFNN_ebp_SIZ;
			break;

		case ASMC_JMP_IFNN__SFP :
			pc += KNH_ASMC_JMP_IFNN_sfp_SIZ;
			break;

		case ASMC_JMP_IFNN__OFP :
			pc += KNH_ASMC_JMP_IFNN_ofp_SIZ;
			break;

		case ASMC_JMP_IFNN__OIDX :
			gc(ctx, ((knh_asmc_jmp_ifnn_oidx_t*)pc)->a2);
			pc += KNH_ASMC_JMP_IFNN_OIDX_SIZ;
			break;

		case ASMC_NEXT :
			pc += KNH_ASMC_NEXT_SIZ;
			break;

		case ASMC_MAPNEXT :
			pc += KNH_ASMC_MAPNEXT_SIZ;
			break;

		case ASMC_SMAPNEXT :
			gc(ctx, ((knh_asmc_smapnext_t*)pc)->a4);
			pc += KNH_ASMC_SMAPNEXT_SIZ;
			break;

		case ASMC_TRY_BEGIN :
			pc += KNH_ASMC_TRY_BEGIN_SIZ;
			break;

		case ASMC_TRY_END :
			pc += KNH_ASMC_TRY_END_SIZ;
			break;

		case ASMC_CATCH :
			pc += KNH_ASMC_CATCH_SIZ;
			break;

		case ASMC_THROW__EBP :
			pc += KNH_ASMC_THROW_ebp_SIZ;
			break;

		case ASMC_THROW__SFP :
			pc += KNH_ASMC_THROW_sfp_SIZ;
			break;

		case ASMC_THROW__OBJ :
			gc(ctx, ((knh_asmc_throw_obj_t*)pc)->a1);
			pc += KNH_ASMC_THROW_OBJ_SIZ;
			break;

		case ASMC_PRINT__EBP :
			gc(ctx, ((knh_asmc_print_ebp_t*)pc)->a2);
			pc += KNH_ASMC_PRINT_ebp_SIZ;
			break;

		case ASMC_PRINT__SFP :
			gc(ctx, ((knh_asmc_print_sfp_t*)pc)->a2);
			pc += KNH_ASMC_PRINT_sfp_SIZ;
			break;

		case ASMC_PRINT__OFP :
			gc(ctx, ((knh_asmc_print_ofp_t*)pc)->a2);
			pc += KNH_ASMC_PRINT_ofp_SIZ;
			break;

		case ASMC_PRINT__OBJ :
			gc(ctx, ((knh_asmc_print_obj_t*)pc)->a2);
			gc(ctx, ((knh_asmc_print_obj_t*)pc)->a4);
			pc += KNH_ASMC_PRINT_OBJ_SIZ;
			break;

		case ASMC_PRINT__OIDX :
			gc(ctx, ((knh_asmc_print_oidx_t*)pc)->a2);
			gc(ctx, ((knh_asmc_print_oidx_t*)pc)->a4);
			pc += KNH_ASMC_PRINT_OIDX_SIZ;
			break;

		case ASMC_NOP :
			pc += KNH_ASMC_NOP_SIZ;
			break;

		default :
			DBG_P("UNKNOWN VMCODE: %d\n", PCT_(pc));
			KNH_ASSERT(ctx == NULL);
			return;
		}
	}
}

/* ======================================================================== */
/* [dump] */

void knh_KLRCode_HALT__dump(Ctx *ctx, knh_asmc_halt_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "halt");
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_RET__ebp__dump(Ctx *ctx, knh_asmc_ret_ebp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "ret__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_RET__sfp__dump(Ctx *ctx, knh_asmc_ret_sfp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "ret__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_RET__ofp__dump(Ctx *ctx, knh_asmc_ret_ofp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "ret__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_RET__OBJ__dump(Ctx *ctx, knh_asmc_ret_obj_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "ret__obj");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a1), KNH_NULL);
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_RET__OIDX__dump(Ctx *ctx, knh_asmc_ret_oidx_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "ret__oidx");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a1), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVE__ebp__dump(Ctx *ctx, knh_asmc_move_ebp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "move__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVE__sfp__dump(Ctx *ctx, knh_asmc_move_sfp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "move__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVE__ofp__dump(Ctx *ctx, knh_asmc_move_ofp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "move__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVE__OBJ__dump(Ctx *ctx, knh_asmc_move_obj_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "move__obj");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVE__OIDX__dump(Ctx *ctx, knh_asmc_move_oidx_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "move__oidx");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVS__ebp__dump(Ctx *ctx, knh_asmc_movs_ebp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movs__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVS__sfp__dump(Ctx *ctx, knh_asmc_movs_sfp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movs__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVS__ofp__dump(Ctx *ctx, knh_asmc_movs_ofp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movs__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVS__OBJ__dump(Ctx *ctx, knh_asmc_movs_obj_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movs__obj");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVS__OIDX__dump(Ctx *ctx, knh_asmc_movs_oidx_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movs__oidx");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVO__ebp__dump(Ctx *ctx, knh_asmc_movo_ebp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movo__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVO__sfp__dump(Ctx *ctx, knh_asmc_movo_sfp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movo__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVO__ofp__dump(Ctx *ctx, knh_asmc_movo_ofp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movo__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVO__OBJ__dump(Ctx *ctx, knh_asmc_movo_obj_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movo__obj");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVO__OIDX__dump(Ctx *ctx, knh_asmc_movo_oidx_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movo__oidx");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVOI__ebp__dump(Ctx *ctx, knh_asmc_movoi_ebp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movoi__ebp");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a1), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a3));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVOI__sfp__dump(Ctx *ctx, knh_asmc_movoi_sfp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movoi__sfp");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a1), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a3));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVOI__ofp__dump(Ctx *ctx, knh_asmc_movoi_ofp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movoi__ofp");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a1), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a3));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVOI__OBJ__dump(Ctx *ctx, knh_asmc_movoi_obj_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movoi__obj");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a1), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a3), KNH_NULL);
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVOI__OIDX__dump(Ctx *ctx, knh_asmc_movoi_oidx_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movoi__oidx");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a1), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a3), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a4));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MOVSFP_IFNUL__dump(Ctx *ctx, knh_asmc_movsfp_ifnul_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movsfp_ifnul");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_PUSH__ebp__dump(Ctx *ctx, knh_asmc_push_ebp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "push__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_PUSH__sfp__dump(Ctx *ctx, knh_asmc_push_sfp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "push__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_PUSH__ofp__dump(Ctx *ctx, knh_asmc_push_ofp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "push__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_PUSH__OBJ__dump(Ctx *ctx, knh_asmc_push_obj_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "push__obj");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a1), KNH_NULL);
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_PUSH__OIDX__dump(Ctx *ctx, knh_asmc_push_oidx_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "push__oidx");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a1), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_PUT_SYSCONST__dump(Ctx *ctx, knh_asmc_put_sysconst_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "put_sysconst");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_PUSH_SYSCONST__dump(Ctx *ctx, knh_asmc_push_sysconst_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "push_sysconst");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_PUSH__DEF__dump(Ctx *ctx, knh_asmc_push_def_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "push__def");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_VARGS__dump(Ctx *ctx, knh_asmc_vargs_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "vargs");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_SHIFT__dump(Ctx *ctx, knh_asmc_shift_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "shift");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_SCALL__dump(Ctx *ctx, knh_asmc_scall_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "scall");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_NSCALL__dump(Ctx *ctx, knh_asmc_nscall_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "nscall");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_CALL__dump(Ctx *ctx, knh_asmc_call_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "call");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_write__mn(ctx, w, (knh_methodn_t)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_DCALL__dump(Ctx *ctx, knh_asmc_dcall_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "dcall");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_write__mn(ctx, w, (knh_methodn_t)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_NEW__dump(Ctx *ctx, knh_asmc_new_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "new");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a3));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MT__dump(Ctx *ctx, knh_asmc_mt_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "mt");
	knh_putc(ctx, w, ' ');
	knh_write__mn(ctx, w, (knh_methodn_t)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_SMAP__dump(Ctx *ctx, knh_asmc_smap_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "smap");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a1), KNH_NULL);
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_SMAPE__dump(Ctx *ctx, knh_asmc_smape_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "smape");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a1), KNH_NULL);
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MAP__dump(Ctx *ctx, knh_asmc_map_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "map");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MAPE__dump(Ctx *ctx, knh_asmc_mape_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "mape");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_ANYMAP__dump(Ctx *ctx, knh_asmc_anymap_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "anymap");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_ANYMAPE__dump(Ctx *ctx, knh_asmc_anymape_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "anymape");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MAP2__dump(Ctx *ctx, knh_asmc_map2_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "map2");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MAP2E__dump(Ctx *ctx, knh_asmc_map2e_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "map2e");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_TYPECHK__ebp__dump(Ctx *ctx, knh_asmc_typechk_ebp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "typechk__ebp");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_TYPECHK__sfp__dump(Ctx *ctx, knh_asmc_typechk_sfp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "typechk__sfp");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_TYPECHK__ofp__dump(Ctx *ctx, knh_asmc_typechk_ofp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "typechk__ofp");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_TYPECHK__OBJ__dump(Ctx *ctx, knh_asmc_typechk_obj_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "typechk__obj");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_TYPECHK__OIDX__dump(Ctx *ctx, knh_asmc_typechk_oidx_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "typechk__oidx");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_NULLCHK__ebp__dump(Ctx *ctx, knh_asmc_nullchk_ebp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "nullchk__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_NULLCHK__sfp__dump(Ctx *ctx, knh_asmc_nullchk_sfp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "nullchk__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_NULLCHK__ofp__dump(Ctx *ctx, knh_asmc_nullchk_ofp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "nullchk__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_NULLCHK__OBJ__dump(Ctx *ctx, knh_asmc_nullchk_obj_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "nullchk__obj");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a1), KNH_NULL);
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_NULLCHK__OIDX__dump(Ctx *ctx, knh_asmc_nullchk_oidx_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "nullchk__oidx");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a1), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP__dump(Ctx *ctx, knh_asmc_jmp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_SKIP__dump(Ctx *ctx, knh_asmc_skip_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "skip");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFT__ebp__dump(Ctx *ctx, knh_asmc_jmp_ift_ebp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ift__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFT__sfp__dump(Ctx *ctx, knh_asmc_jmp_ift_sfp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ift__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFT__ofp__dump(Ctx *ctx, knh_asmc_jmp_ift_ofp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ift__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFT__OIDX__dump(Ctx *ctx, knh_asmc_jmp_ift_oidx_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ift__oidx");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFF__ebp__dump(Ctx *ctx, knh_asmc_jmp_iff_ebp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_iff__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFF__sfp__dump(Ctx *ctx, knh_asmc_jmp_iff_sfp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_iff__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFF__ofp__dump(Ctx *ctx, knh_asmc_jmp_iff_ofp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_iff__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFF__OIDX__dump(Ctx *ctx, knh_asmc_jmp_iff_oidx_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_iff__oidx");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFTNN__ebp__dump(Ctx *ctx, knh_asmc_jmp_iftnn_ebp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_iftnn__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFTNN__sfp__dump(Ctx *ctx, knh_asmc_jmp_iftnn_sfp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_iftnn__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFTNN__ofp__dump(Ctx *ctx, knh_asmc_jmp_iftnn_ofp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_iftnn__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFTNN__OIDX__dump(Ctx *ctx, knh_asmc_jmp_iftnn_oidx_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_iftnn__oidx");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFFN__ebp__dump(Ctx *ctx, knh_asmc_jmp_iffn_ebp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_iffn__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFFN__sfp__dump(Ctx *ctx, knh_asmc_jmp_iffn_sfp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_iffn__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFFN__ofp__dump(Ctx *ctx, knh_asmc_jmp_iffn_ofp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_iffn__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFFN__OIDX__dump(Ctx *ctx, knh_asmc_jmp_iffn_oidx_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_iffn__oidx");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFNN__ebp__dump(Ctx *ctx, knh_asmc_jmp_ifnn_ebp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ifnn__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFNN__sfp__dump(Ctx *ctx, knh_asmc_jmp_ifnn_sfp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ifnn__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFNN__ofp__dump(Ctx *ctx, knh_asmc_jmp_ifnn_ofp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ifnn__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_JMP_IFNN__OIDX__dump(Ctx *ctx, knh_asmc_jmp_ifnn_oidx_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ifnn__oidx");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_NEXT__dump(Ctx *ctx, knh_asmc_next_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "next");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a3));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_MAPNEXT__dump(Ctx *ctx, knh_asmc_mapnext_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "mapnext");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a3));
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a4));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_SMAPNEXT__dump(Ctx *ctx, knh_asmc_smapnext_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "smapnext");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a3));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a4), KNH_NULL);
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_TRY_BEGIN__dump(Ctx *ctx, knh_asmc_try_begin_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "try_begin");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a3));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_TRY_END__dump(Ctx *ctx, knh_asmc_try_end_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "try_end");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_CATCH__dump(Ctx *ctx, knh_asmc_catch_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "catch");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "->%p", (((char*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_write__expt(ctx, w, (knh_expt_t)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a3));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_THROW__ebp__dump(Ctx *ctx, knh_asmc_throw_ebp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "throw__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_THROW__sfp__dump(Ctx *ctx, knh_asmc_throw_sfp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "throw__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a1));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_THROW__OBJ__dump(Ctx *ctx, knh_asmc_throw_obj_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "throw__obj");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a1), KNH_NULL);
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_PRINT__ebp__dump(Ctx *ctx, knh_asmc_print_ebp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "print__ebp");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__mn(ctx, w, (knh_methodn_t)(bw->a3));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d].o", (int)(bw->a4));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_PRINT__sfp__dump(Ctx *ctx, knh_asmc_print_sfp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "print__sfp");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__mn(ctx, w, (knh_methodn_t)(bw->a3));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d].o", (int)(bw->a4));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_PRINT__ofp__dump(Ctx *ctx, knh_asmc_print_ofp_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "print__ofp");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__mn(ctx, w, (knh_methodn_t)(bw->a3));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a4));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_PRINT__OBJ__dump(Ctx *ctx, knh_asmc_print_obj_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "print__obj");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__mn(ctx, w, (knh_methodn_t)(bw->a3));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a4), KNH_NULL);
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_PRINT__OIDX__dump(Ctx *ctx, knh_asmc_print_oidx_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "print__oidx");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__mn(ctx, w, (knh_methodn_t)(bw->a3));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__k, (bw->a4), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a5));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

void knh_KLRCode_NOP__dump(Ctx *ctx, knh_asmc_nop_t *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knhvmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "nop");
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */


PUBLIC
void knh_KLRCode__dump_(Ctx *ctx, KLRCode *o, OutputStream *w, Any *m)
{
	knh_bytes_t vmc = knh_KLRCode_tobytes(o);
	knhvmc_t *pc = (knhvmc_t*)vmc.buf;
	knhvmc_t *tail = pc + vmc.len;	
	int off = (int)pc;
	while(pc < tail) {
		switch(PCT_(pc)) {
		case ASMC_HALT :
			knh_KLRCode_HALT__dump(ctx, (knh_asmc_halt_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_HALT_SIZ;
			break;
		case ASMC_RET__EBP :
			knh_KLRCode_RET__ebp__dump(ctx, (knh_asmc_ret_ebp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_RET_ebp_SIZ;
			break;
		case ASMC_RET__SFP :
			knh_KLRCode_RET__sfp__dump(ctx, (knh_asmc_ret_sfp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_RET_sfp_SIZ;
			break;
		case ASMC_RET__OFP :
			knh_KLRCode_RET__ofp__dump(ctx, (knh_asmc_ret_ofp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_RET_ofp_SIZ;
			break;
		case ASMC_RET__OBJ :
			knh_KLRCode_RET__OBJ__dump(ctx, (knh_asmc_ret_obj_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_RET_OBJ_SIZ;
			break;
		case ASMC_RET__OIDX :
			knh_KLRCode_RET__OIDX__dump(ctx, (knh_asmc_ret_oidx_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_RET_OIDX_SIZ;
			break;
		case ASMC_MOVE__EBP :
			knh_KLRCode_MOVE__ebp__dump(ctx, (knh_asmc_move_ebp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVE_ebp_SIZ;
			break;
		case ASMC_MOVE__SFP :
			knh_KLRCode_MOVE__sfp__dump(ctx, (knh_asmc_move_sfp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVE_sfp_SIZ;
			break;
		case ASMC_MOVE__OFP :
			knh_KLRCode_MOVE__ofp__dump(ctx, (knh_asmc_move_ofp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVE_ofp_SIZ;
			break;
		case ASMC_MOVE__OBJ :
			knh_KLRCode_MOVE__OBJ__dump(ctx, (knh_asmc_move_obj_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVE_OBJ_SIZ;
			break;
		case ASMC_MOVE__OIDX :
			knh_KLRCode_MOVE__OIDX__dump(ctx, (knh_asmc_move_oidx_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVE_OIDX_SIZ;
			break;
		case ASMC_MOVS__EBP :
			knh_KLRCode_MOVS__ebp__dump(ctx, (knh_asmc_movs_ebp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVS_ebp_SIZ;
			break;
		case ASMC_MOVS__SFP :
			knh_KLRCode_MOVS__sfp__dump(ctx, (knh_asmc_movs_sfp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVS_sfp_SIZ;
			break;
		case ASMC_MOVS__OFP :
			knh_KLRCode_MOVS__ofp__dump(ctx, (knh_asmc_movs_ofp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVS_ofp_SIZ;
			break;
		case ASMC_MOVS__OBJ :
			knh_KLRCode_MOVS__OBJ__dump(ctx, (knh_asmc_movs_obj_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVS_OBJ_SIZ;
			break;
		case ASMC_MOVS__OIDX :
			knh_KLRCode_MOVS__OIDX__dump(ctx, (knh_asmc_movs_oidx_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVS_OIDX_SIZ;
			break;
		case ASMC_MOVO__EBP :
			knh_KLRCode_MOVO__ebp__dump(ctx, (knh_asmc_movo_ebp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVO_ebp_SIZ;
			break;
		case ASMC_MOVO__SFP :
			knh_KLRCode_MOVO__sfp__dump(ctx, (knh_asmc_movo_sfp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVO_sfp_SIZ;
			break;
		case ASMC_MOVO__OFP :
			knh_KLRCode_MOVO__ofp__dump(ctx, (knh_asmc_movo_ofp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVO_ofp_SIZ;
			break;
		case ASMC_MOVO__OBJ :
			knh_KLRCode_MOVO__OBJ__dump(ctx, (knh_asmc_movo_obj_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVO_OBJ_SIZ;
			break;
		case ASMC_MOVO__OIDX :
			knh_KLRCode_MOVO__OIDX__dump(ctx, (knh_asmc_movo_oidx_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVO_OIDX_SIZ;
			break;
		case ASMC_MOVOI__EBP :
			knh_KLRCode_MOVOI__ebp__dump(ctx, (knh_asmc_movoi_ebp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVOI_ebp_SIZ;
			break;
		case ASMC_MOVOI__SFP :
			knh_KLRCode_MOVOI__sfp__dump(ctx, (knh_asmc_movoi_sfp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVOI_sfp_SIZ;
			break;
		case ASMC_MOVOI__OFP :
			knh_KLRCode_MOVOI__ofp__dump(ctx, (knh_asmc_movoi_ofp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVOI_ofp_SIZ;
			break;
		case ASMC_MOVOI__OBJ :
			knh_KLRCode_MOVOI__OBJ__dump(ctx, (knh_asmc_movoi_obj_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVOI_OBJ_SIZ;
			break;
		case ASMC_MOVOI__OIDX :
			knh_KLRCode_MOVOI__OIDX__dump(ctx, (knh_asmc_movoi_oidx_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVOI_OIDX_SIZ;
			break;
		case ASMC_MOVSFP_IFNUL :
			knh_KLRCode_MOVSFP_IFNUL__dump(ctx, (knh_asmc_movsfp_ifnul_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MOVSFP_IFNUL_SIZ;
			break;
		case ASMC_PUSH__EBP :
			knh_KLRCode_PUSH__ebp__dump(ctx, (knh_asmc_push_ebp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_PUSH_ebp_SIZ;
			break;
		case ASMC_PUSH__SFP :
			knh_KLRCode_PUSH__sfp__dump(ctx, (knh_asmc_push_sfp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_PUSH_sfp_SIZ;
			break;
		case ASMC_PUSH__OFP :
			knh_KLRCode_PUSH__ofp__dump(ctx, (knh_asmc_push_ofp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_PUSH_ofp_SIZ;
			break;
		case ASMC_PUSH__OBJ :
			knh_KLRCode_PUSH__OBJ__dump(ctx, (knh_asmc_push_obj_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_PUSH_OBJ_SIZ;
			break;
		case ASMC_PUSH__OIDX :
			knh_KLRCode_PUSH__OIDX__dump(ctx, (knh_asmc_push_oidx_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_PUSH_OIDX_SIZ;
			break;
		case ASMC_PUT_SYSCONST :
			knh_KLRCode_PUT_SYSCONST__dump(ctx, (knh_asmc_put_sysconst_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_PUT_SYSCONST_SIZ;
			break;
		case ASMC_PUSH_SYSCONST :
			knh_KLRCode_PUSH_SYSCONST__dump(ctx, (knh_asmc_push_sysconst_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_PUSH_SYSCONST_SIZ;
			break;
		case ASMC_PUSH__DEF :
			knh_KLRCode_PUSH__DEF__dump(ctx, (knh_asmc_push_def_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_PUSH_DEF_SIZ;
			break;
		case ASMC_VARGS :
			knh_KLRCode_VARGS__dump(ctx, (knh_asmc_vargs_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_VARGS_SIZ;
			break;
		case ASMC_SHIFT :
			knh_KLRCode_SHIFT__dump(ctx, (knh_asmc_shift_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_SHIFT_SIZ;
			break;
		case ASMC_SCALL :
			knh_KLRCode_SCALL__dump(ctx, (knh_asmc_scall_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_SCALL_SIZ;
			break;
		case ASMC_NSCALL :
			knh_KLRCode_NSCALL__dump(ctx, (knh_asmc_nscall_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_NSCALL_SIZ;
			break;
		case ASMC_CALL :
			knh_KLRCode_CALL__dump(ctx, (knh_asmc_call_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_CALL_SIZ;
			break;
		case ASMC_DCALL :
			knh_KLRCode_DCALL__dump(ctx, (knh_asmc_dcall_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_DCALL_SIZ;
			break;
		case ASMC_NEW :
			knh_KLRCode_NEW__dump(ctx, (knh_asmc_new_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_NEW_SIZ;
			break;
		case ASMC_MT :
			knh_KLRCode_MT__dump(ctx, (knh_asmc_mt_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MT_SIZ;
			break;
		case ASMC_SMAP :
			knh_KLRCode_SMAP__dump(ctx, (knh_asmc_smap_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_SMAP_SIZ;
			break;
		case ASMC_SMAPE :
			knh_KLRCode_SMAPE__dump(ctx, (knh_asmc_smape_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_SMAPE_SIZ;
			break;
		case ASMC_MAP :
			knh_KLRCode_MAP__dump(ctx, (knh_asmc_map_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MAP_SIZ;
			break;
		case ASMC_MAPE :
			knh_KLRCode_MAPE__dump(ctx, (knh_asmc_mape_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MAPE_SIZ;
			break;
		case ASMC_ANYMAP :
			knh_KLRCode_ANYMAP__dump(ctx, (knh_asmc_anymap_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_ANYMAP_SIZ;
			break;
		case ASMC_ANYMAPE :
			knh_KLRCode_ANYMAPE__dump(ctx, (knh_asmc_anymape_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_ANYMAPE_SIZ;
			break;
		case ASMC_MAP2 :
			knh_KLRCode_MAP2__dump(ctx, (knh_asmc_map2_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MAP2_SIZ;
			break;
		case ASMC_MAP2E :
			knh_KLRCode_MAP2E__dump(ctx, (knh_asmc_map2e_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MAP2E_SIZ;
			break;
		case ASMC_TYPECHK__EBP :
			knh_KLRCode_TYPECHK__ebp__dump(ctx, (knh_asmc_typechk_ebp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_TYPECHK_ebp_SIZ;
			break;
		case ASMC_TYPECHK__SFP :
			knh_KLRCode_TYPECHK__sfp__dump(ctx, (knh_asmc_typechk_sfp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_TYPECHK_sfp_SIZ;
			break;
		case ASMC_TYPECHK__OFP :
			knh_KLRCode_TYPECHK__ofp__dump(ctx, (knh_asmc_typechk_ofp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_TYPECHK_ofp_SIZ;
			break;
		case ASMC_TYPECHK__OBJ :
			knh_KLRCode_TYPECHK__OBJ__dump(ctx, (knh_asmc_typechk_obj_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_TYPECHK_OBJ_SIZ;
			break;
		case ASMC_TYPECHK__OIDX :
			knh_KLRCode_TYPECHK__OIDX__dump(ctx, (knh_asmc_typechk_oidx_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_TYPECHK_OIDX_SIZ;
			break;
		case ASMC_NULLCHK__EBP :
			knh_KLRCode_NULLCHK__ebp__dump(ctx, (knh_asmc_nullchk_ebp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_NULLCHK_ebp_SIZ;
			break;
		case ASMC_NULLCHK__SFP :
			knh_KLRCode_NULLCHK__sfp__dump(ctx, (knh_asmc_nullchk_sfp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_NULLCHK_sfp_SIZ;
			break;
		case ASMC_NULLCHK__OFP :
			knh_KLRCode_NULLCHK__ofp__dump(ctx, (knh_asmc_nullchk_ofp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_NULLCHK_ofp_SIZ;
			break;
		case ASMC_NULLCHK__OBJ :
			knh_KLRCode_NULLCHK__OBJ__dump(ctx, (knh_asmc_nullchk_obj_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_NULLCHK_OBJ_SIZ;
			break;
		case ASMC_NULLCHK__OIDX :
			knh_KLRCode_NULLCHK__OIDX__dump(ctx, (knh_asmc_nullchk_oidx_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_NULLCHK_OIDX_SIZ;
			break;
		case ASMC_JMP :
			knh_KLRCode_JMP__dump(ctx, (knh_asmc_jmp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_SIZ;
			break;
		case ASMC_SKIP :
			knh_KLRCode_SKIP__dump(ctx, (knh_asmc_skip_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_SKIP_SIZ;
			break;
		case ASMC_JMP_IFT__EBP :
			knh_KLRCode_JMP_IFT__ebp__dump(ctx, (knh_asmc_jmp_ift_ebp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFT_ebp_SIZ;
			break;
		case ASMC_JMP_IFT__SFP :
			knh_KLRCode_JMP_IFT__sfp__dump(ctx, (knh_asmc_jmp_ift_sfp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFT_sfp_SIZ;
			break;
		case ASMC_JMP_IFT__OFP :
			knh_KLRCode_JMP_IFT__ofp__dump(ctx, (knh_asmc_jmp_ift_ofp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFT_ofp_SIZ;
			break;
		case ASMC_JMP_IFT__OIDX :
			knh_KLRCode_JMP_IFT__OIDX__dump(ctx, (knh_asmc_jmp_ift_oidx_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFT_OIDX_SIZ;
			break;
		case ASMC_JMP_IFF__EBP :
			knh_KLRCode_JMP_IFF__ebp__dump(ctx, (knh_asmc_jmp_iff_ebp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFF_ebp_SIZ;
			break;
		case ASMC_JMP_IFF__SFP :
			knh_KLRCode_JMP_IFF__sfp__dump(ctx, (knh_asmc_jmp_iff_sfp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFF_sfp_SIZ;
			break;
		case ASMC_JMP_IFF__OFP :
			knh_KLRCode_JMP_IFF__ofp__dump(ctx, (knh_asmc_jmp_iff_ofp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFF_ofp_SIZ;
			break;
		case ASMC_JMP_IFF__OIDX :
			knh_KLRCode_JMP_IFF__OIDX__dump(ctx, (knh_asmc_jmp_iff_oidx_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFF_OIDX_SIZ;
			break;
		case ASMC_JMP_IFTNN__EBP :
			knh_KLRCode_JMP_IFTNN__ebp__dump(ctx, (knh_asmc_jmp_iftnn_ebp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFTNN_ebp_SIZ;
			break;
		case ASMC_JMP_IFTNN__SFP :
			knh_KLRCode_JMP_IFTNN__sfp__dump(ctx, (knh_asmc_jmp_iftnn_sfp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFTNN_sfp_SIZ;
			break;
		case ASMC_JMP_IFTNN__OFP :
			knh_KLRCode_JMP_IFTNN__ofp__dump(ctx, (knh_asmc_jmp_iftnn_ofp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFTNN_ofp_SIZ;
			break;
		case ASMC_JMP_IFTNN__OIDX :
			knh_KLRCode_JMP_IFTNN__OIDX__dump(ctx, (knh_asmc_jmp_iftnn_oidx_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFTNN_OIDX_SIZ;
			break;
		case ASMC_JMP_IFFN__EBP :
			knh_KLRCode_JMP_IFFN__ebp__dump(ctx, (knh_asmc_jmp_iffn_ebp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFFN_ebp_SIZ;
			break;
		case ASMC_JMP_IFFN__SFP :
			knh_KLRCode_JMP_IFFN__sfp__dump(ctx, (knh_asmc_jmp_iffn_sfp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFFN_sfp_SIZ;
			break;
		case ASMC_JMP_IFFN__OFP :
			knh_KLRCode_JMP_IFFN__ofp__dump(ctx, (knh_asmc_jmp_iffn_ofp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFFN_ofp_SIZ;
			break;
		case ASMC_JMP_IFFN__OIDX :
			knh_KLRCode_JMP_IFFN__OIDX__dump(ctx, (knh_asmc_jmp_iffn_oidx_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFFN_OIDX_SIZ;
			break;
		case ASMC_JMP_IFNN__EBP :
			knh_KLRCode_JMP_IFNN__ebp__dump(ctx, (knh_asmc_jmp_ifnn_ebp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFNN_ebp_SIZ;
			break;
		case ASMC_JMP_IFNN__SFP :
			knh_KLRCode_JMP_IFNN__sfp__dump(ctx, (knh_asmc_jmp_ifnn_sfp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFNN_sfp_SIZ;
			break;
		case ASMC_JMP_IFNN__OFP :
			knh_KLRCode_JMP_IFNN__ofp__dump(ctx, (knh_asmc_jmp_ifnn_ofp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFNN_ofp_SIZ;
			break;
		case ASMC_JMP_IFNN__OIDX :
			knh_KLRCode_JMP_IFNN__OIDX__dump(ctx, (knh_asmc_jmp_ifnn_oidx_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_JMP_IFNN_OIDX_SIZ;
			break;
		case ASMC_NEXT :
			knh_KLRCode_NEXT__dump(ctx, (knh_asmc_next_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_NEXT_SIZ;
			break;
		case ASMC_MAPNEXT :
			knh_KLRCode_MAPNEXT__dump(ctx, (knh_asmc_mapnext_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_MAPNEXT_SIZ;
			break;
		case ASMC_SMAPNEXT :
			knh_KLRCode_SMAPNEXT__dump(ctx, (knh_asmc_smapnext_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_SMAPNEXT_SIZ;
			break;
		case ASMC_TRY_BEGIN :
			knh_KLRCode_TRY_BEGIN__dump(ctx, (knh_asmc_try_begin_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_TRY_BEGIN_SIZ;
			break;
		case ASMC_TRY_END :
			knh_KLRCode_TRY_END__dump(ctx, (knh_asmc_try_end_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_TRY_END_SIZ;
			break;
		case ASMC_CATCH :
			knh_KLRCode_CATCH__dump(ctx, (knh_asmc_catch_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_CATCH_SIZ;
			break;
		case ASMC_THROW__EBP :
			knh_KLRCode_THROW__ebp__dump(ctx, (knh_asmc_throw_ebp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_THROW_ebp_SIZ;
			break;
		case ASMC_THROW__SFP :
			knh_KLRCode_THROW__sfp__dump(ctx, (knh_asmc_throw_sfp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_THROW_sfp_SIZ;
			break;
		case ASMC_THROW__OBJ :
			knh_KLRCode_THROW__OBJ__dump(ctx, (knh_asmc_throw_obj_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_THROW_OBJ_SIZ;
			break;
		case ASMC_PRINT__EBP :
			knh_KLRCode_PRINT__ebp__dump(ctx, (knh_asmc_print_ebp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_PRINT_ebp_SIZ;
			break;
		case ASMC_PRINT__SFP :
			knh_KLRCode_PRINT__sfp__dump(ctx, (knh_asmc_print_sfp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_PRINT_sfp_SIZ;
			break;
		case ASMC_PRINT__OFP :
			knh_KLRCode_PRINT__ofp__dump(ctx, (knh_asmc_print_ofp_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_PRINT_ofp_SIZ;
			break;
		case ASMC_PRINT__OBJ :
			knh_KLRCode_PRINT__OBJ__dump(ctx, (knh_asmc_print_obj_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_PRINT_OBJ_SIZ;
			break;
		case ASMC_PRINT__OIDX :
			knh_KLRCode_PRINT__OIDX__dump(ctx, (knh_asmc_print_oidx_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_PRINT_OIDX_SIZ;
			break;
		case ASMC_NOP :
			knh_KLRCode_NOP__dump(ctx, (knh_asmc_nop_t*)pc, off, w, (Method*)m);
			pc += KNH_ASMC_NOP_SIZ;
			break;

		default :
			DBG_P("UNKNOWN VMCODE: %d\n", PCT_(pc));
			KNH_ASSERT(ctx == NULL);
			return;
		}
	}
}

/* ------------------------------------------------------------------------ */


/* ======================================================================== */
/* [exec] */

#ifndef KNH_CC_LABELPTR
METHOD knh_KLRCode_exec(Ctx *ctx, knh_sfp_t *sfp)
{
	register knhvmc_t *pc = DP((KLRCode*)DP(sfp[-1].mtd)->code)->code;
	L_HEAD:;
	switch(PCT_(pc)) {
	case ASMC_HALT :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_HALT__dump(ctx, (knh_asmc_halt_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_HALT
		VM_HALT(ctx);
#else
		DBG_P("TODO: VM_HALT");
#endif
		pc += KNH_ASMC_HALT_SIZ;
		break;
	case ASMC_RET__EBP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_RET__EBP__dump(ctx, (knh_asmc_ret_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_RET
		VM_RET(ctx, ebp_(((const knh_asmc_ret_ebp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_RET");
#endif
		pc += KNH_ASMC_RET_ebp_SIZ;
		break;
	case ASMC_RET__SFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_RET__SFP__dump(ctx, (knh_asmc_ret_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_RET
		VM_RET(ctx, sfp_(((const knh_asmc_ret_sfp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_RET");
#endif
		pc += KNH_ASMC_RET_sfp_SIZ;
		break;
	case ASMC_RET__OFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_RET__OFP__dump(ctx, (knh_asmc_ret_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_RET
		VM_RET(ctx, ofp_(((const knh_asmc_ret_ofp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_RET");
#endif
		pc += KNH_ASMC_RET_ofp_SIZ;
		break;
	case ASMC_RET__OBJ :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_RET__OBJ__dump(ctx, (knh_asmc_ret_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_RET
		VM_RET(ctx, OBJ_(((const knh_asmc_ret_obj_t*)pc)->a1));
#else
		DBG_P("TODO: VM_RET");
#endif
		pc += KNH_ASMC_RET_OBJ_SIZ;
		break;
	case ASMC_RET__OIDX :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_RET__OIDX__dump(ctx, (knh_asmc_ret_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_RET__OIDX
		VM_RET__OIDX(ctx, OBJ_(((const knh_asmc_ret_oidx_t*)pc)->a1), u1_(((const knh_asmc_ret_oidx_t*)pc)->a2));
#else
		DBG_P("TODO: VM_RET__OIDX");
#endif
		pc += KNH_ASMC_RET_OIDX_SIZ;
		break;
	case ASMC_MOVE__EBP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVE__EBP__dump(ctx, (knh_asmc_move_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVE
		VM_MOVE(ctx, ebp_(((const knh_asmc_move_ebp_t*)pc)->a1), ebp_(((const knh_asmc_move_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVE");
#endif
		pc += KNH_ASMC_MOVE_ebp_SIZ;
		break;
	case ASMC_MOVE__SFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVE__SFP__dump(ctx, (knh_asmc_move_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVE
		VM_MOVE(ctx, ebp_(((const knh_asmc_move_sfp_t*)pc)->a1), sfp_(((const knh_asmc_move_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVE");
#endif
		pc += KNH_ASMC_MOVE_sfp_SIZ;
		break;
	case ASMC_MOVE__OFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVE__OFP__dump(ctx, (knh_asmc_move_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVE
		VM_MOVE(ctx, ebp_(((const knh_asmc_move_ofp_t*)pc)->a1), ofp_(((const knh_asmc_move_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVE");
#endif
		pc += KNH_ASMC_MOVE_ofp_SIZ;
		break;
	case ASMC_MOVE__OBJ :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVE__OBJ__dump(ctx, (knh_asmc_move_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVE
		VM_MOVE(ctx, ebp_(((const knh_asmc_move_obj_t*)pc)->a1), OBJ_(((const knh_asmc_move_obj_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVE");
#endif
		pc += KNH_ASMC_MOVE_OBJ_SIZ;
		break;
	case ASMC_MOVE__OIDX :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVE__OIDX__dump(ctx, (knh_asmc_move_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVE__OIDX
		VM_MOVE__OIDX(ctx, ebp_(((const knh_asmc_move_oidx_t*)pc)->a1), OBJ_(((const knh_asmc_move_oidx_t*)pc)->a2), u1_(((const knh_asmc_move_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_MOVE__OIDX");
#endif
		pc += KNH_ASMC_MOVE_OIDX_SIZ;
		break;
	case ASMC_MOVS__EBP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVS__EBP__dump(ctx, (knh_asmc_movs_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVS
		VM_MOVS(ctx, sfp_(((const knh_asmc_movs_ebp_t*)pc)->a1), ebp_(((const knh_asmc_movs_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVS");
#endif
		pc += KNH_ASMC_MOVS_ebp_SIZ;
		break;
	case ASMC_MOVS__SFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVS__SFP__dump(ctx, (knh_asmc_movs_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVS
		VM_MOVS(ctx, sfp_(((const knh_asmc_movs_sfp_t*)pc)->a1), sfp_(((const knh_asmc_movs_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVS");
#endif
		pc += KNH_ASMC_MOVS_sfp_SIZ;
		break;
	case ASMC_MOVS__OFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVS__OFP__dump(ctx, (knh_asmc_movs_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVS
		VM_MOVS(ctx, sfp_(((const knh_asmc_movs_ofp_t*)pc)->a1), ofp_(((const knh_asmc_movs_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVS");
#endif
		pc += KNH_ASMC_MOVS_ofp_SIZ;
		break;
	case ASMC_MOVS__OBJ :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVS__OBJ__dump(ctx, (knh_asmc_movs_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVS
		VM_MOVS(ctx, sfp_(((const knh_asmc_movs_obj_t*)pc)->a1), OBJ_(((const knh_asmc_movs_obj_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVS");
#endif
		pc += KNH_ASMC_MOVS_OBJ_SIZ;
		break;
	case ASMC_MOVS__OIDX :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVS__OIDX__dump(ctx, (knh_asmc_movs_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVS__OIDX
		VM_MOVS__OIDX(ctx, sfp_(((const knh_asmc_movs_oidx_t*)pc)->a1), OBJ_(((const knh_asmc_movs_oidx_t*)pc)->a2), u1_(((const knh_asmc_movs_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_MOVS__OIDX");
#endif
		pc += KNH_ASMC_MOVS_OIDX_SIZ;
		break;
	case ASMC_MOVO__EBP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVO__EBP__dump(ctx, (knh_asmc_movo_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVO
		VM_MOVO(ctx, ofp_(((const knh_asmc_movo_ebp_t*)pc)->a1), ebp_(((const knh_asmc_movo_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVO");
#endif
		pc += KNH_ASMC_MOVO_ebp_SIZ;
		break;
	case ASMC_MOVO__SFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVO__SFP__dump(ctx, (knh_asmc_movo_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVO
		VM_MOVO(ctx, ofp_(((const knh_asmc_movo_sfp_t*)pc)->a1), sfp_(((const knh_asmc_movo_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVO");
#endif
		pc += KNH_ASMC_MOVO_sfp_SIZ;
		break;
	case ASMC_MOVO__OFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVO__OFP__dump(ctx, (knh_asmc_movo_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVO
		VM_MOVO(ctx, ofp_(((const knh_asmc_movo_ofp_t*)pc)->a1), ofp_(((const knh_asmc_movo_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVO");
#endif
		pc += KNH_ASMC_MOVO_ofp_SIZ;
		break;
	case ASMC_MOVO__OBJ :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVO__OBJ__dump(ctx, (knh_asmc_movo_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVO
		VM_MOVO(ctx, ofp_(((const knh_asmc_movo_obj_t*)pc)->a1), OBJ_(((const knh_asmc_movo_obj_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVO");
#endif
		pc += KNH_ASMC_MOVO_OBJ_SIZ;
		break;
	case ASMC_MOVO__OIDX :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVO__OIDX__dump(ctx, (knh_asmc_movo_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVO__OIDX
		VM_MOVO__OIDX(ctx, ofp_(((const knh_asmc_movo_oidx_t*)pc)->a1), OBJ_(((const knh_asmc_movo_oidx_t*)pc)->a2), u1_(((const knh_asmc_movo_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_MOVO__OIDX");
#endif
		pc += KNH_ASMC_MOVO_OIDX_SIZ;
		break;
	case ASMC_MOVOI__EBP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVOI__EBP__dump(ctx, (knh_asmc_movoi_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVOI
		VM_MOVOI(ctx, OBJ_(((const knh_asmc_movoi_ebp_t*)pc)->a1), ofp_(((const knh_asmc_movoi_ebp_t*)pc)->a2), ebp_(((const knh_asmc_movoi_ebp_t*)pc)->a3));
#else
		DBG_P("TODO: VM_MOVOI");
#endif
		pc += KNH_ASMC_MOVOI_ebp_SIZ;
		break;
	case ASMC_MOVOI__SFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVOI__SFP__dump(ctx, (knh_asmc_movoi_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVOI
		VM_MOVOI(ctx, OBJ_(((const knh_asmc_movoi_sfp_t*)pc)->a1), ofp_(((const knh_asmc_movoi_sfp_t*)pc)->a2), sfp_(((const knh_asmc_movoi_sfp_t*)pc)->a3));
#else
		DBG_P("TODO: VM_MOVOI");
#endif
		pc += KNH_ASMC_MOVOI_sfp_SIZ;
		break;
	case ASMC_MOVOI__OFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVOI__OFP__dump(ctx, (knh_asmc_movoi_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVOI
		VM_MOVOI(ctx, OBJ_(((const knh_asmc_movoi_ofp_t*)pc)->a1), ofp_(((const knh_asmc_movoi_ofp_t*)pc)->a2), ofp_(((const knh_asmc_movoi_ofp_t*)pc)->a3));
#else
		DBG_P("TODO: VM_MOVOI");
#endif
		pc += KNH_ASMC_MOVOI_ofp_SIZ;
		break;
	case ASMC_MOVOI__OBJ :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVOI__OBJ__dump(ctx, (knh_asmc_movoi_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVOI
		VM_MOVOI(ctx, OBJ_(((const knh_asmc_movoi_obj_t*)pc)->a1), ofp_(((const knh_asmc_movoi_obj_t*)pc)->a2), OBJ_(((const knh_asmc_movoi_obj_t*)pc)->a3));
#else
		DBG_P("TODO: VM_MOVOI");
#endif
		pc += KNH_ASMC_MOVOI_OBJ_SIZ;
		break;
	case ASMC_MOVOI__OIDX :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVOI__OIDX__dump(ctx, (knh_asmc_movoi_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVOI__OIDX
		VM_MOVOI__OIDX(ctx, OBJ_(((const knh_asmc_movoi_oidx_t*)pc)->a1), u1_(((const knh_asmc_movoi_oidx_t*)pc)->a2), OBJ_(((const knh_asmc_movoi_oidx_t*)pc)->a3), u1_(((const knh_asmc_movoi_oidx_t*)pc)->a4));
#else
		DBG_P("TODO: VM_MOVOI__OIDX");
#endif
		pc += KNH_ASMC_MOVOI_OIDX_SIZ;
		break;
	case ASMC_MOVSFP_IFNUL :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MOVSFP_IFNUL__dump(ctx, (knh_asmc_movsfp_ifnul_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVSFP_IFNUL
		VM_MOVSFP_IFNUL(ctx, u1_(((const knh_asmc_movsfp_ifnul_t*)pc)->a1), OBJ_(((const knh_asmc_movsfp_ifnul_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVSFP_IFNUL");
#endif
		pc += KNH_ASMC_MOVSFP_IFNUL_SIZ;
		break;
	case ASMC_PUSH__EBP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_PUSH__EBP__dump(ctx, (knh_asmc_push_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PUSH
		VM_PUSH(ctx, ebp_(((const knh_asmc_push_ebp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_PUSH");
#endif
		pc += KNH_ASMC_PUSH_ebp_SIZ;
		break;
	case ASMC_PUSH__SFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_PUSH__SFP__dump(ctx, (knh_asmc_push_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PUSH
		VM_PUSH(ctx, sfp_(((const knh_asmc_push_sfp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_PUSH");
#endif
		pc += KNH_ASMC_PUSH_sfp_SIZ;
		break;
	case ASMC_PUSH__OFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_PUSH__OFP__dump(ctx, (knh_asmc_push_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PUSH
		VM_PUSH(ctx, ofp_(((const knh_asmc_push_ofp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_PUSH");
#endif
		pc += KNH_ASMC_PUSH_ofp_SIZ;
		break;
	case ASMC_PUSH__OBJ :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_PUSH__OBJ__dump(ctx, (knh_asmc_push_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PUSH
		VM_PUSH(ctx, OBJ_(((const knh_asmc_push_obj_t*)pc)->a1));
#else
		DBG_P("TODO: VM_PUSH");
#endif
		pc += KNH_ASMC_PUSH_OBJ_SIZ;
		break;
	case ASMC_PUSH__OIDX :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_PUSH__OIDX__dump(ctx, (knh_asmc_push_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PUSH__OIDX
		VM_PUSH__OIDX(ctx, OBJ_(((const knh_asmc_push_oidx_t*)pc)->a1), u1_(((const knh_asmc_push_oidx_t*)pc)->a2));
#else
		DBG_P("TODO: VM_PUSH__OIDX");
#endif
		pc += KNH_ASMC_PUSH_OIDX_SIZ;
		break;
	case ASMC_PUT_SYSCONST :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_PUT_SYSCONST__dump(ctx, (knh_asmc_put_sysconst_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PUT_SYSCONST
		VM_PUT_SYSCONST(ctx, u2_(((const knh_asmc_put_sysconst_t*)pc)->a1));
#else
		DBG_P("TODO: VM_PUT_SYSCONST");
#endif
		pc += KNH_ASMC_PUT_SYSCONST_SIZ;
		break;
	case ASMC_PUSH_SYSCONST :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_PUSH_SYSCONST__dump(ctx, (knh_asmc_push_sysconst_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PUSH_SYSCONST
		VM_PUSH_SYSCONST(ctx, u2_(((const knh_asmc_push_sysconst_t*)pc)->a1));
#else
		DBG_P("TODO: VM_PUSH_SYSCONST");
#endif
		pc += KNH_ASMC_PUSH_SYSCONST_SIZ;
		break;
	case ASMC_PUSH__DEF :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_PUSH__DEF__dump(ctx, (knh_asmc_push_def_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PUSH__DEF
		VM_PUSH__DEF(ctx, c2_(((const knh_asmc_push_def_t*)pc)->a1));
#else
		DBG_P("TODO: VM_PUSH__DEF");
#endif
		pc += KNH_ASMC_PUSH_DEF_SIZ;
		break;
	case ASMC_VARGS :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_VARGS__dump(ctx, (knh_asmc_vargs_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_VARGS
		VM_VARGS(ctx, u2_(((const knh_asmc_vargs_t*)pc)->a1));
#else
		DBG_P("TODO: VM_VARGS");
#endif
		pc += KNH_ASMC_VARGS_SIZ;
		break;
	case ASMC_SHIFT :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_SHIFT__dump(ctx, (knh_asmc_shift_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_SHIFT
		VM_SHIFT(ctx, i1_(((const knh_asmc_shift_t*)pc)->a1));
#else
		DBG_P("TODO: VM_SHIFT");
#endif
		pc += KNH_ASMC_SHIFT_SIZ;
		break;
	case ASMC_SCALL :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_SCALL__dump(ctx, (knh_asmc_scall_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_SCALL
		VM_SCALL(ctx, u1_(((const knh_asmc_scall_t*)pc)->a1));
#else
		DBG_P("TODO: VM_SCALL");
#endif
		pc += KNH_ASMC_SCALL_SIZ;
		break;
	case ASMC_NSCALL :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_NSCALL__dump(ctx, (knh_asmc_nscall_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NSCALL
		VM_NSCALL(ctx, u1_(((const knh_asmc_nscall_t*)pc)->a1));
#else
		DBG_P("TODO: VM_NSCALL");
#endif
		pc += KNH_ASMC_NSCALL_SIZ;
		break;
	case ASMC_CALL :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_CALL__dump(ctx, (knh_asmc_call_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_CALL
		VM_CALL(ctx, u1_(((const knh_asmc_call_t*)pc)->a1), mn_(((const knh_asmc_call_t*)pc)->a2));
#else
		DBG_P("TODO: VM_CALL");
#endif
		pc += KNH_ASMC_CALL_SIZ;
		break;
	case ASMC_DCALL :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_DCALL__dump(ctx, (knh_asmc_dcall_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_DCALL
		VM_DCALL(ctx, u1_(((const knh_asmc_dcall_t*)pc)->a1), mn_(((const knh_asmc_dcall_t*)pc)->a2));
#else
		DBG_P("TODO: VM_DCALL");
#endif
		pc += KNH_ASMC_DCALL_SIZ;
		break;
	case ASMC_NEW :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_NEW__dump(ctx, (knh_asmc_new_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NEW
		VM_NEW(ctx, u2_(((const knh_asmc_new_t*)pc)->a1), u2_(((const knh_asmc_new_t*)pc)->a2), c2_(((const knh_asmc_new_t*)pc)->a3));
#else
		DBG_P("TODO: VM_NEW");
#endif
		pc += KNH_ASMC_NEW_SIZ;
		break;
	case ASMC_MT :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MT__dump(ctx, (knh_asmc_mt_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MT
		VM_MT(ctx, mn_(((const knh_asmc_mt_t*)pc)->a1));
#else
		DBG_P("TODO: VM_MT");
#endif
		pc += KNH_ASMC_MT_SIZ;
		break;
	case ASMC_SMAP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_SMAP__dump(ctx, (knh_asmc_smap_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_SMAP
		VM_SMAP(ctx, OBJ_(((const knh_asmc_smap_t*)pc)->a1));
#else
		DBG_P("TODO: VM_SMAP");
#endif
		pc += KNH_ASMC_SMAP_SIZ;
		break;
	case ASMC_SMAPE :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_SMAPE__dump(ctx, (knh_asmc_smape_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_SMAPE
		VM_SMAPE(ctx, OBJ_(((const knh_asmc_smape_t*)pc)->a1));
#else
		DBG_P("TODO: VM_SMAPE");
#endif
		pc += KNH_ASMC_SMAPE_SIZ;
		break;
	case ASMC_MAP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MAP__dump(ctx, (knh_asmc_map_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MAP
		VM_MAP(ctx, c2_(((const knh_asmc_map_t*)pc)->a1));
#else
		DBG_P("TODO: VM_MAP");
#endif
		pc += KNH_ASMC_MAP_SIZ;
		break;
	case ASMC_MAPE :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MAPE__dump(ctx, (knh_asmc_mape_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MAPE
		VM_MAPE(ctx, c2_(((const knh_asmc_mape_t*)pc)->a1));
#else
		DBG_P("TODO: VM_MAPE");
#endif
		pc += KNH_ASMC_MAPE_SIZ;
		break;
	case ASMC_ANYMAP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_ANYMAP__dump(ctx, (knh_asmc_anymap_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_ANYMAP
		VM_ANYMAP(ctx, c2_(((const knh_asmc_anymap_t*)pc)->a1));
#else
		DBG_P("TODO: VM_ANYMAP");
#endif
		pc += KNH_ASMC_ANYMAP_SIZ;
		break;
	case ASMC_ANYMAPE :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_ANYMAPE__dump(ctx, (knh_asmc_anymape_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_ANYMAPE
		VM_ANYMAPE(ctx, c2_(((const knh_asmc_anymape_t*)pc)->a1));
#else
		DBG_P("TODO: VM_ANYMAPE");
#endif
		pc += KNH_ASMC_ANYMAPE_SIZ;
		break;
	case ASMC_MAP2 :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MAP2__dump(ctx, (knh_asmc_map2_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MAP2
		VM_MAP2(ctx, c2_(((const knh_asmc_map2_t*)pc)->a1));
#else
		DBG_P("TODO: VM_MAP2");
#endif
		pc += KNH_ASMC_MAP2_SIZ;
		break;
	case ASMC_MAP2E :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MAP2E__dump(ctx, (knh_asmc_map2e_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MAP2E
		VM_MAP2E(ctx, c2_(((const knh_asmc_map2e_t*)pc)->a1));
#else
		DBG_P("TODO: VM_MAP2E");
#endif
		pc += KNH_ASMC_MAP2E_SIZ;
		break;
	case ASMC_TYPECHK__EBP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_TYPECHK__EBP__dump(ctx, (knh_asmc_typechk_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_TYPECHK
		VM_TYPECHK(ctx, c2_(((const knh_asmc_typechk_ebp_t*)pc)->a1), ebp_(((const knh_asmc_typechk_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_TYPECHK");
#endif
		pc += KNH_ASMC_TYPECHK_ebp_SIZ;
		break;
	case ASMC_TYPECHK__SFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_TYPECHK__SFP__dump(ctx, (knh_asmc_typechk_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_TYPECHK
		VM_TYPECHK(ctx, c2_(((const knh_asmc_typechk_sfp_t*)pc)->a1), sfp_(((const knh_asmc_typechk_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_TYPECHK");
#endif
		pc += KNH_ASMC_TYPECHK_sfp_SIZ;
		break;
	case ASMC_TYPECHK__OFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_TYPECHK__OFP__dump(ctx, (knh_asmc_typechk_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_TYPECHK
		VM_TYPECHK(ctx, c2_(((const knh_asmc_typechk_ofp_t*)pc)->a1), ofp_(((const knh_asmc_typechk_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_TYPECHK");
#endif
		pc += KNH_ASMC_TYPECHK_ofp_SIZ;
		break;
	case ASMC_TYPECHK__OBJ :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_TYPECHK__OBJ__dump(ctx, (knh_asmc_typechk_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_TYPECHK
		VM_TYPECHK(ctx, c2_(((const knh_asmc_typechk_obj_t*)pc)->a1), OBJ_(((const knh_asmc_typechk_obj_t*)pc)->a2));
#else
		DBG_P("TODO: VM_TYPECHK");
#endif
		pc += KNH_ASMC_TYPECHK_OBJ_SIZ;
		break;
	case ASMC_TYPECHK__OIDX :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_TYPECHK__OIDX__dump(ctx, (knh_asmc_typechk_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_TYPECHK__OIDX
		VM_TYPECHK__OIDX(ctx, c2_(((const knh_asmc_typechk_oidx_t*)pc)->a1), OBJ_(((const knh_asmc_typechk_oidx_t*)pc)->a2), u1_(((const knh_asmc_typechk_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_TYPECHK__OIDX");
#endif
		pc += KNH_ASMC_TYPECHK_OIDX_SIZ;
		break;
	case ASMC_NULLCHK__EBP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_NULLCHK__EBP__dump(ctx, (knh_asmc_nullchk_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NULLCHK
		VM_NULLCHK(ctx, ebp_(((const knh_asmc_nullchk_ebp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_NULLCHK");
#endif
		pc += KNH_ASMC_NULLCHK_ebp_SIZ;
		break;
	case ASMC_NULLCHK__SFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_NULLCHK__SFP__dump(ctx, (knh_asmc_nullchk_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NULLCHK
		VM_NULLCHK(ctx, sfp_(((const knh_asmc_nullchk_sfp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_NULLCHK");
#endif
		pc += KNH_ASMC_NULLCHK_sfp_SIZ;
		break;
	case ASMC_NULLCHK__OFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_NULLCHK__OFP__dump(ctx, (knh_asmc_nullchk_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NULLCHK
		VM_NULLCHK(ctx, ofp_(((const knh_asmc_nullchk_ofp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_NULLCHK");
#endif
		pc += KNH_ASMC_NULLCHK_ofp_SIZ;
		break;
	case ASMC_NULLCHK__OBJ :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_NULLCHK__OBJ__dump(ctx, (knh_asmc_nullchk_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NULLCHK
		VM_NULLCHK(ctx, OBJ_(((const knh_asmc_nullchk_obj_t*)pc)->a1));
#else
		DBG_P("TODO: VM_NULLCHK");
#endif
		pc += KNH_ASMC_NULLCHK_OBJ_SIZ;
		break;
	case ASMC_NULLCHK__OIDX :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_NULLCHK__OIDX__dump(ctx, (knh_asmc_nullchk_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NULLCHK__OIDX
		VM_NULLCHK__OIDX(ctx, OBJ_(((const knh_asmc_nullchk_oidx_t*)pc)->a1), u1_(((const knh_asmc_nullchk_oidx_t*)pc)->a2));
#else
		DBG_P("TODO: VM_NULLCHK__OIDX");
#endif
		pc += KNH_ASMC_NULLCHK_OIDX_SIZ;
		break;
	case ASMC_JMP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP__dump(ctx, (knh_asmc_jmp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP
		VM_JMP(ctx, pc += ((const knh_asmc_jmp_t*)pc)->a1, L_HEAD);
#else
		DBG_P("TODO: VM_JMP");
#endif
		pc += KNH_ASMC_JMP_SIZ;
		break;
	case ASMC_SKIP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_SKIP__dump(ctx, (knh_asmc_skip_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_SKIP
		VM_SKIP(ctx, pc += ((const knh_asmc_skip_t*)pc)->a1, L_HEAD);
#else
		DBG_P("TODO: VM_SKIP");
#endif
		pc += KNH_ASMC_SKIP_SIZ;
		break;
	case ASMC_JMP_IFT__EBP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFT__EBP__dump(ctx, (knh_asmc_jmp_ift_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFT
		VM_JMP_IFT(ctx, pc += ((const knh_asmc_jmp_ift_ebp_t*)pc)->a1, L_HEAD, ebp_(((const knh_asmc_jmp_ift_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFT");
#endif
		pc += KNH_ASMC_JMP_IFT_ebp_SIZ;
		break;
	case ASMC_JMP_IFT__SFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFT__SFP__dump(ctx, (knh_asmc_jmp_ift_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFT
		VM_JMP_IFT(ctx, pc += ((const knh_asmc_jmp_ift_sfp_t*)pc)->a1, L_HEAD, sfp_(((const knh_asmc_jmp_ift_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFT");
#endif
		pc += KNH_ASMC_JMP_IFT_sfp_SIZ;
		break;
	case ASMC_JMP_IFT__OFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFT__OFP__dump(ctx, (knh_asmc_jmp_ift_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFT
		VM_JMP_IFT(ctx, pc += ((const knh_asmc_jmp_ift_ofp_t*)pc)->a1, L_HEAD, ofp_(((const knh_asmc_jmp_ift_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFT");
#endif
		pc += KNH_ASMC_JMP_IFT_ofp_SIZ;
		break;
	case ASMC_JMP_IFT__OIDX :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFT__OIDX__dump(ctx, (knh_asmc_jmp_ift_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFT__OIDX
		VM_JMP_IFT__OIDX(ctx, pc += ((const knh_asmc_jmp_ift_oidx_t*)pc)->a1, L_HEAD, OBJ_(((const knh_asmc_jmp_ift_oidx_t*)pc)->a2), u1_(((const knh_asmc_jmp_ift_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_JMP_IFT__OIDX");
#endif
		pc += KNH_ASMC_JMP_IFT_OIDX_SIZ;
		break;
	case ASMC_JMP_IFF__EBP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFF__EBP__dump(ctx, (knh_asmc_jmp_iff_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFF
		VM_JMP_IFF(ctx, pc += ((const knh_asmc_jmp_iff_ebp_t*)pc)->a1, L_HEAD, ebp_(((const knh_asmc_jmp_iff_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFF");
#endif
		pc += KNH_ASMC_JMP_IFF_ebp_SIZ;
		break;
	case ASMC_JMP_IFF__SFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFF__SFP__dump(ctx, (knh_asmc_jmp_iff_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFF
		VM_JMP_IFF(ctx, pc += ((const knh_asmc_jmp_iff_sfp_t*)pc)->a1, L_HEAD, sfp_(((const knh_asmc_jmp_iff_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFF");
#endif
		pc += KNH_ASMC_JMP_IFF_sfp_SIZ;
		break;
	case ASMC_JMP_IFF__OFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFF__OFP__dump(ctx, (knh_asmc_jmp_iff_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFF
		VM_JMP_IFF(ctx, pc += ((const knh_asmc_jmp_iff_ofp_t*)pc)->a1, L_HEAD, ofp_(((const knh_asmc_jmp_iff_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFF");
#endif
		pc += KNH_ASMC_JMP_IFF_ofp_SIZ;
		break;
	case ASMC_JMP_IFF__OIDX :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFF__OIDX__dump(ctx, (knh_asmc_jmp_iff_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFF__OIDX
		VM_JMP_IFF__OIDX(ctx, pc += ((const knh_asmc_jmp_iff_oidx_t*)pc)->a1, L_HEAD, OBJ_(((const knh_asmc_jmp_iff_oidx_t*)pc)->a2), u1_(((const knh_asmc_jmp_iff_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_JMP_IFF__OIDX");
#endif
		pc += KNH_ASMC_JMP_IFF_OIDX_SIZ;
		break;
	case ASMC_JMP_IFTNN__EBP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFTNN__EBP__dump(ctx, (knh_asmc_jmp_iftnn_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFTNN
		VM_JMP_IFTNN(ctx, pc += ((const knh_asmc_jmp_iftnn_ebp_t*)pc)->a1, L_HEAD, ebp_(((const knh_asmc_jmp_iftnn_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFTNN");
#endif
		pc += KNH_ASMC_JMP_IFTNN_ebp_SIZ;
		break;
	case ASMC_JMP_IFTNN__SFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFTNN__SFP__dump(ctx, (knh_asmc_jmp_iftnn_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFTNN
		VM_JMP_IFTNN(ctx, pc += ((const knh_asmc_jmp_iftnn_sfp_t*)pc)->a1, L_HEAD, sfp_(((const knh_asmc_jmp_iftnn_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFTNN");
#endif
		pc += KNH_ASMC_JMP_IFTNN_sfp_SIZ;
		break;
	case ASMC_JMP_IFTNN__OFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFTNN__OFP__dump(ctx, (knh_asmc_jmp_iftnn_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFTNN
		VM_JMP_IFTNN(ctx, pc += ((const knh_asmc_jmp_iftnn_ofp_t*)pc)->a1, L_HEAD, ofp_(((const knh_asmc_jmp_iftnn_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFTNN");
#endif
		pc += KNH_ASMC_JMP_IFTNN_ofp_SIZ;
		break;
	case ASMC_JMP_IFTNN__OIDX :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFTNN__OIDX__dump(ctx, (knh_asmc_jmp_iftnn_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFTNN__OIDX
		VM_JMP_IFTNN__OIDX(ctx, pc += ((const knh_asmc_jmp_iftnn_oidx_t*)pc)->a1, L_HEAD, OBJ_(((const knh_asmc_jmp_iftnn_oidx_t*)pc)->a2), u1_(((const knh_asmc_jmp_iftnn_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_JMP_IFTNN__OIDX");
#endif
		pc += KNH_ASMC_JMP_IFTNN_OIDX_SIZ;
		break;
	case ASMC_JMP_IFFN__EBP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFFN__EBP__dump(ctx, (knh_asmc_jmp_iffn_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFFN
		VM_JMP_IFFN(ctx, pc += ((const knh_asmc_jmp_iffn_ebp_t*)pc)->a1, L_HEAD, ebp_(((const knh_asmc_jmp_iffn_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFFN");
#endif
		pc += KNH_ASMC_JMP_IFFN_ebp_SIZ;
		break;
	case ASMC_JMP_IFFN__SFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFFN__SFP__dump(ctx, (knh_asmc_jmp_iffn_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFFN
		VM_JMP_IFFN(ctx, pc += ((const knh_asmc_jmp_iffn_sfp_t*)pc)->a1, L_HEAD, sfp_(((const knh_asmc_jmp_iffn_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFFN");
#endif
		pc += KNH_ASMC_JMP_IFFN_sfp_SIZ;
		break;
	case ASMC_JMP_IFFN__OFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFFN__OFP__dump(ctx, (knh_asmc_jmp_iffn_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFFN
		VM_JMP_IFFN(ctx, pc += ((const knh_asmc_jmp_iffn_ofp_t*)pc)->a1, L_HEAD, ofp_(((const knh_asmc_jmp_iffn_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFFN");
#endif
		pc += KNH_ASMC_JMP_IFFN_ofp_SIZ;
		break;
	case ASMC_JMP_IFFN__OIDX :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFFN__OIDX__dump(ctx, (knh_asmc_jmp_iffn_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFFN__OIDX
		VM_JMP_IFFN__OIDX(ctx, pc += ((const knh_asmc_jmp_iffn_oidx_t*)pc)->a1, L_HEAD, OBJ_(((const knh_asmc_jmp_iffn_oidx_t*)pc)->a2), u1_(((const knh_asmc_jmp_iffn_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_JMP_IFFN__OIDX");
#endif
		pc += KNH_ASMC_JMP_IFFN_OIDX_SIZ;
		break;
	case ASMC_JMP_IFNN__EBP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFNN__EBP__dump(ctx, (knh_asmc_jmp_ifnn_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFNN
		VM_JMP_IFNN(ctx, pc += ((const knh_asmc_jmp_ifnn_ebp_t*)pc)->a1, L_HEAD, ebp_(((const knh_asmc_jmp_ifnn_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFNN");
#endif
		pc += KNH_ASMC_JMP_IFNN_ebp_SIZ;
		break;
	case ASMC_JMP_IFNN__SFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFNN__SFP__dump(ctx, (knh_asmc_jmp_ifnn_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFNN
		VM_JMP_IFNN(ctx, pc += ((const knh_asmc_jmp_ifnn_sfp_t*)pc)->a1, L_HEAD, sfp_(((const knh_asmc_jmp_ifnn_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFNN");
#endif
		pc += KNH_ASMC_JMP_IFNN_sfp_SIZ;
		break;
	case ASMC_JMP_IFNN__OFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFNN__OFP__dump(ctx, (knh_asmc_jmp_ifnn_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFNN
		VM_JMP_IFNN(ctx, pc += ((const knh_asmc_jmp_ifnn_ofp_t*)pc)->a1, L_HEAD, ofp_(((const knh_asmc_jmp_ifnn_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFNN");
#endif
		pc += KNH_ASMC_JMP_IFNN_ofp_SIZ;
		break;
	case ASMC_JMP_IFNN__OIDX :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_JMP_IFNN__OIDX__dump(ctx, (knh_asmc_jmp_ifnn_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFNN__OIDX
		VM_JMP_IFNN__OIDX(ctx, pc += ((const knh_asmc_jmp_ifnn_oidx_t*)pc)->a1, L_HEAD, OBJ_(((const knh_asmc_jmp_ifnn_oidx_t*)pc)->a2), u1_(((const knh_asmc_jmp_ifnn_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_JMP_IFNN__OIDX");
#endif
		pc += KNH_ASMC_JMP_IFNN_OIDX_SIZ;
		break;
	case ASMC_NEXT :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_NEXT__dump(ctx, (knh_asmc_next_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NEXT
		VM_NEXT(ctx, pc += ((const knh_asmc_next_t*)pc)->a1, L_HEAD, sfp_(((const knh_asmc_next_t*)pc)->a2), sfp_(((const knh_asmc_next_t*)pc)->a3));
#else
		DBG_P("TODO: VM_NEXT");
#endif
		pc += KNH_ASMC_NEXT_SIZ;
		break;
	case ASMC_MAPNEXT :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_MAPNEXT__dump(ctx, (knh_asmc_mapnext_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MAPNEXT
		VM_MAPNEXT(ctx, pc += ((const knh_asmc_mapnext_t*)pc)->a1, L_HEAD, sfp_(((const knh_asmc_mapnext_t*)pc)->a2), sfp_(((const knh_asmc_mapnext_t*)pc)->a3), c2_(((const knh_asmc_mapnext_t*)pc)->a4));
#else
		DBG_P("TODO: VM_MAPNEXT");
#endif
		pc += KNH_ASMC_MAPNEXT_SIZ;
		break;
	case ASMC_SMAPNEXT :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_SMAPNEXT__dump(ctx, (knh_asmc_smapnext_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_SMAPNEXT
		VM_SMAPNEXT(ctx, pc += ((const knh_asmc_smapnext_t*)pc)->a1, L_HEAD, sfp_(((const knh_asmc_smapnext_t*)pc)->a2), sfp_(((const knh_asmc_smapnext_t*)pc)->a3), OBJ_(((const knh_asmc_smapnext_t*)pc)->a4));
#else
		DBG_P("TODO: VM_SMAPNEXT");
#endif
		pc += KNH_ASMC_SMAPNEXT_SIZ;
		break;
	case ASMC_TRY_BEGIN :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_TRY_BEGIN__dump(ctx, (knh_asmc_try_begin_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_TRY_BEGIN
		VM_TRY_BEGIN(ctx, pc += ((const knh_asmc_try_begin_t*)pc)->a1, L_HEAD, sfp_(((const knh_asmc_try_begin_t*)pc)->a2), sfp_(((const knh_asmc_try_begin_t*)pc)->a3));
#else
		DBG_P("TODO: VM_TRY_BEGIN");
#endif
		pc += KNH_ASMC_TRY_BEGIN_SIZ;
		break;
	case ASMC_TRY_END :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_TRY_END__dump(ctx, (knh_asmc_try_end_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_TRY_END
		VM_TRY_END(ctx, sfp_(((const knh_asmc_try_end_t*)pc)->a1));
#else
		DBG_P("TODO: VM_TRY_END");
#endif
		pc += KNH_ASMC_TRY_END_SIZ;
		break;
	case ASMC_CATCH :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_CATCH__dump(ctx, (knh_asmc_catch_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_CATCH
		VM_CATCH(ctx, pc += ((const knh_asmc_catch_t*)pc)->a1, L_HEAD, e2_(((const knh_asmc_catch_t*)pc)->a2), sfp_(((const knh_asmc_catch_t*)pc)->a3));
#else
		DBG_P("TODO: VM_CATCH");
#endif
		pc += KNH_ASMC_CATCH_SIZ;
		break;
	case ASMC_THROW__EBP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_THROW__EBP__dump(ctx, (knh_asmc_throw_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_THROW
		VM_THROW(ctx, ebp_(((const knh_asmc_throw_ebp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_THROW");
#endif
		pc += KNH_ASMC_THROW_ebp_SIZ;
		break;
	case ASMC_THROW__SFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_THROW__SFP__dump(ctx, (knh_asmc_throw_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_THROW
		VM_THROW(ctx, sfp_(((const knh_asmc_throw_sfp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_THROW");
#endif
		pc += KNH_ASMC_THROW_sfp_SIZ;
		break;
	case ASMC_THROW__OBJ :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_THROW__OBJ__dump(ctx, (knh_asmc_throw_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_THROW
		VM_THROW(ctx, OBJ_(((const knh_asmc_throw_obj_t*)pc)->a1));
#else
		DBG_P("TODO: VM_THROW");
#endif
		pc += KNH_ASMC_THROW_OBJ_SIZ;
		break;
	case ASMC_PRINT__EBP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_PRINT__EBP__dump(ctx, (knh_asmc_print_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PRINT
		VM_PRINT(ctx, u2_(((const knh_asmc_print_ebp_t*)pc)->a1), OBJ_(((const knh_asmc_print_ebp_t*)pc)->a2), mn_(((const knh_asmc_print_ebp_t*)pc)->a3), ebp_(((const knh_asmc_print_ebp_t*)pc)->a4));
#else
		DBG_P("TODO: VM_PRINT");
#endif
		pc += KNH_ASMC_PRINT_ebp_SIZ;
		break;
	case ASMC_PRINT__SFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_PRINT__SFP__dump(ctx, (knh_asmc_print_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PRINT
		VM_PRINT(ctx, u2_(((const knh_asmc_print_sfp_t*)pc)->a1), OBJ_(((const knh_asmc_print_sfp_t*)pc)->a2), mn_(((const knh_asmc_print_sfp_t*)pc)->a3), sfp_(((const knh_asmc_print_sfp_t*)pc)->a4));
#else
		DBG_P("TODO: VM_PRINT");
#endif
		pc += KNH_ASMC_PRINT_sfp_SIZ;
		break;
	case ASMC_PRINT__OFP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_PRINT__OFP__dump(ctx, (knh_asmc_print_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PRINT
		VM_PRINT(ctx, u2_(((const knh_asmc_print_ofp_t*)pc)->a1), OBJ_(((const knh_asmc_print_ofp_t*)pc)->a2), mn_(((const knh_asmc_print_ofp_t*)pc)->a3), ofp_(((const knh_asmc_print_ofp_t*)pc)->a4));
#else
		DBG_P("TODO: VM_PRINT");
#endif
		pc += KNH_ASMC_PRINT_ofp_SIZ;
		break;
	case ASMC_PRINT__OBJ :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_PRINT__OBJ__dump(ctx, (knh_asmc_print_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PRINT
		VM_PRINT(ctx, u2_(((const knh_asmc_print_obj_t*)pc)->a1), OBJ_(((const knh_asmc_print_obj_t*)pc)->a2), mn_(((const knh_asmc_print_obj_t*)pc)->a3), OBJ_(((const knh_asmc_print_obj_t*)pc)->a4));
#else
		DBG_P("TODO: VM_PRINT");
#endif
		pc += KNH_ASMC_PRINT_OBJ_SIZ;
		break;
	case ASMC_PRINT__OIDX :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_PRINT__OIDX__dump(ctx, (knh_asmc_print_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PRINT__OIDX
		VM_PRINT__OIDX(ctx, u2_(((const knh_asmc_print_oidx_t*)pc)->a1), OBJ_(((const knh_asmc_print_oidx_t*)pc)->a2), mn_(((const knh_asmc_print_oidx_t*)pc)->a3), OBJ_(((const knh_asmc_print_oidx_t*)pc)->a4), u1_(((const knh_asmc_print_oidx_t*)pc)->a5));
#else
		DBG_P("TODO: VM_PRINT__OIDX");
#endif
		pc += KNH_ASMC_PRINT_OIDX_SIZ;
		break;
	case ASMC_NOP :
#ifdef DBG_P_VM
		knh_KLRCode_ASMC_NOP__dump(ctx, (knh_asmc_nop_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NOP
		VM_NOP(ctx);
#else
		DBG_P("TODO: VM_NOP");
#endif
		pc += KNH_ASMC_NOP_SIZ;
		break;

	}
	goto L_HEAD;
}
#endif

/* ------------------------------------------------------------------------ */

#ifdef KNH_CC_LABELPTR
METHOD knh_KLRCode_exec(Ctx *ctx, knh_sfp_t *sfp)
{
	static void *globalMachineToJump[] = {
		&&L_ASMC_HALT,
		&&L_ASMC_RET__EBP,
		&&L_ASMC_RET__SFP,
		&&L_ASMC_RET__OFP,
		&&L_ASMC_RET__OBJ,
		&&L_ASMC_RET__OIDX,
		&&L_ASMC_MOVE__EBP,
		&&L_ASMC_MOVE__SFP,
		&&L_ASMC_MOVE__OFP,
		&&L_ASMC_MOVE__OBJ,
		&&L_ASMC_MOVE__OIDX,
		&&L_ASMC_MOVS__EBP,
		&&L_ASMC_MOVS__SFP,
		&&L_ASMC_MOVS__OFP,
		&&L_ASMC_MOVS__OBJ,
		&&L_ASMC_MOVS__OIDX,
		&&L_ASMC_MOVO__EBP,
		&&L_ASMC_MOVO__SFP,
		&&L_ASMC_MOVO__OFP,
		&&L_ASMC_MOVO__OBJ,
		&&L_ASMC_MOVO__OIDX,
		&&L_ASMC_MOVOI__EBP,
		&&L_ASMC_MOVOI__SFP,
		&&L_ASMC_MOVOI__OFP,
		&&L_ASMC_MOVOI__OBJ,
		&&L_ASMC_MOVOI__OIDX,
		&&L_ASMC_MOVSFP_IFNUL,
		&&L_ASMC_PUSH__EBP,
		&&L_ASMC_PUSH__SFP,
		&&L_ASMC_PUSH__OFP,
		&&L_ASMC_PUSH__OBJ,
		&&L_ASMC_PUSH__OIDX,
		&&L_ASMC_PUT_SYSCONST,
		&&L_ASMC_PUSH_SYSCONST,
		&&L_ASMC_PUSH__DEF,
		&&L_ASMC_VARGS,
		&&L_ASMC_SHIFT,
		&&L_ASMC_SCALL,
		&&L_ASMC_NSCALL,
		&&L_ASMC_CALL,
		&&L_ASMC_DCALL,
		&&L_ASMC_NEW,
		&&L_ASMC_MT,
		&&L_ASMC_SMAP,
		&&L_ASMC_SMAPE,
		&&L_ASMC_MAP,
		&&L_ASMC_MAPE,
		&&L_ASMC_ANYMAP,
		&&L_ASMC_ANYMAPE,
		&&L_ASMC_MAP2,
		&&L_ASMC_MAP2E,
		&&L_ASMC_TYPECHK__EBP,
		&&L_ASMC_TYPECHK__SFP,
		&&L_ASMC_TYPECHK__OFP,
		&&L_ASMC_TYPECHK__OBJ,
		&&L_ASMC_TYPECHK__OIDX,
		&&L_ASMC_NULLCHK__EBP,
		&&L_ASMC_NULLCHK__SFP,
		&&L_ASMC_NULLCHK__OFP,
		&&L_ASMC_NULLCHK__OBJ,
		&&L_ASMC_NULLCHK__OIDX,
		&&L_ASMC_JMP,
		&&L_ASMC_SKIP,
		&&L_ASMC_JMP_IFT__EBP,
		&&L_ASMC_JMP_IFT__SFP,
		&&L_ASMC_JMP_IFT__OFP,
		&&L_ASMC_JMP_IFT__OIDX,
		&&L_ASMC_JMP_IFF__EBP,
		&&L_ASMC_JMP_IFF__SFP,
		&&L_ASMC_JMP_IFF__OFP,
		&&L_ASMC_JMP_IFF__OIDX,
		&&L_ASMC_JMP_IFTNN__EBP,
		&&L_ASMC_JMP_IFTNN__SFP,
		&&L_ASMC_JMP_IFTNN__OFP,
		&&L_ASMC_JMP_IFTNN__OIDX,
		&&L_ASMC_JMP_IFFN__EBP,
		&&L_ASMC_JMP_IFFN__SFP,
		&&L_ASMC_JMP_IFFN__OFP,
		&&L_ASMC_JMP_IFFN__OIDX,
		&&L_ASMC_JMP_IFNN__EBP,
		&&L_ASMC_JMP_IFNN__SFP,
		&&L_ASMC_JMP_IFNN__OFP,
		&&L_ASMC_JMP_IFNN__OIDX,
		&&L_ASMC_NEXT,
		&&L_ASMC_MAPNEXT,
		&&L_ASMC_SMAPNEXT,
		&&L_ASMC_TRY_BEGIN,
		&&L_ASMC_TRY_END,
		&&L_ASMC_CATCH,
		&&L_ASMC_THROW__EBP,
		&&L_ASMC_THROW__SFP,
		&&L_ASMC_THROW__OBJ,
		&&L_ASMC_PRINT__EBP,
		&&L_ASMC_PRINT__SFP,
		&&L_ASMC_PRINT__OFP,
		&&L_ASMC_PRINT__OBJ,
		&&L_ASMC_PRINT__OIDX,
		&&L_ASMC_NOP,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN
	};
	knhvmc_t *pc =  DP((KLRCode*)DP(sfp[-1].mtd)->code)->code;
	goto *globalMachineToJump[PCT_(pc)];


	L_ASMC_HALT:;
#ifdef DBG_P_VMC
	knh_KLRCode_HALT__dump(ctx, (knh_asmc_halt_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_HALT
		VM_HALT(ctx);
#else
		DBG_P("TODO: VM_HALT");
#endif
	pc += KNH_ASMC_HALT_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_RET__EBP:;
#ifdef DBG_P_VMC
	knh_KLRCode_RET__ebp__dump(ctx, (knh_asmc_ret_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_RET
		VM_RET(ctx, ebp_(((const knh_asmc_ret_ebp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_RET");
#endif
	pc += KNH_ASMC_RET_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_RET__SFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_RET__sfp__dump(ctx, (knh_asmc_ret_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_RET
		VM_RET(ctx, sfp_(((const knh_asmc_ret_sfp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_RET");
#endif
	pc += KNH_ASMC_RET_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_RET__OFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_RET__ofp__dump(ctx, (knh_asmc_ret_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_RET
		VM_RET(ctx, ofp_(((const knh_asmc_ret_ofp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_RET");
#endif
	pc += KNH_ASMC_RET_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_RET__OBJ:;
#ifdef DBG_P_VMC
	knh_KLRCode_RET__OBJ__dump(ctx, (knh_asmc_ret_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_RET
		VM_RET(ctx, OBJ_(((const knh_asmc_ret_obj_t*)pc)->a1));
#else
		DBG_P("TODO: VM_RET");
#endif
	pc += KNH_ASMC_RET_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_RET__OIDX:;
#ifdef DBG_P_VMC
	knh_KLRCode_RET__OIDX__dump(ctx, (knh_asmc_ret_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_RET__OIDX
		VM_RET__OIDX(ctx, OBJ_(((const knh_asmc_ret_oidx_t*)pc)->a1), u1_(((const knh_asmc_ret_oidx_t*)pc)->a2));
#else
		DBG_P("TODO: VM_RET__OIDX");
#endif
	pc += KNH_ASMC_RET_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVE__EBP:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVE__ebp__dump(ctx, (knh_asmc_move_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVE
		VM_MOVE(ctx, ebp_(((const knh_asmc_move_ebp_t*)pc)->a1), ebp_(((const knh_asmc_move_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVE");
#endif
	pc += KNH_ASMC_MOVE_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVE__SFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVE__sfp__dump(ctx, (knh_asmc_move_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVE
		VM_MOVE(ctx, ebp_(((const knh_asmc_move_sfp_t*)pc)->a1), sfp_(((const knh_asmc_move_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVE");
#endif
	pc += KNH_ASMC_MOVE_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVE__OFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVE__ofp__dump(ctx, (knh_asmc_move_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVE
		VM_MOVE(ctx, ebp_(((const knh_asmc_move_ofp_t*)pc)->a1), ofp_(((const knh_asmc_move_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVE");
#endif
	pc += KNH_ASMC_MOVE_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVE__OBJ:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVE__OBJ__dump(ctx, (knh_asmc_move_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVE
		VM_MOVE(ctx, ebp_(((const knh_asmc_move_obj_t*)pc)->a1), OBJ_(((const knh_asmc_move_obj_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVE");
#endif
	pc += KNH_ASMC_MOVE_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVE__OIDX:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVE__OIDX__dump(ctx, (knh_asmc_move_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVE__OIDX
		VM_MOVE__OIDX(ctx, ebp_(((const knh_asmc_move_oidx_t*)pc)->a1), OBJ_(((const knh_asmc_move_oidx_t*)pc)->a2), u1_(((const knh_asmc_move_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_MOVE__OIDX");
#endif
	pc += KNH_ASMC_MOVE_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVS__EBP:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVS__ebp__dump(ctx, (knh_asmc_movs_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVS
		VM_MOVS(ctx, sfp_(((const knh_asmc_movs_ebp_t*)pc)->a1), ebp_(((const knh_asmc_movs_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVS");
#endif
	pc += KNH_ASMC_MOVS_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVS__SFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVS__sfp__dump(ctx, (knh_asmc_movs_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVS
		VM_MOVS(ctx, sfp_(((const knh_asmc_movs_sfp_t*)pc)->a1), sfp_(((const knh_asmc_movs_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVS");
#endif
	pc += KNH_ASMC_MOVS_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVS__OFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVS__ofp__dump(ctx, (knh_asmc_movs_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVS
		VM_MOVS(ctx, sfp_(((const knh_asmc_movs_ofp_t*)pc)->a1), ofp_(((const knh_asmc_movs_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVS");
#endif
	pc += KNH_ASMC_MOVS_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVS__OBJ:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVS__OBJ__dump(ctx, (knh_asmc_movs_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVS
		VM_MOVS(ctx, sfp_(((const knh_asmc_movs_obj_t*)pc)->a1), OBJ_(((const knh_asmc_movs_obj_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVS");
#endif
	pc += KNH_ASMC_MOVS_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVS__OIDX:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVS__OIDX__dump(ctx, (knh_asmc_movs_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVS__OIDX
		VM_MOVS__OIDX(ctx, sfp_(((const knh_asmc_movs_oidx_t*)pc)->a1), OBJ_(((const knh_asmc_movs_oidx_t*)pc)->a2), u1_(((const knh_asmc_movs_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_MOVS__OIDX");
#endif
	pc += KNH_ASMC_MOVS_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVO__EBP:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVO__ebp__dump(ctx, (knh_asmc_movo_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVO
		VM_MOVO(ctx, ofp_(((const knh_asmc_movo_ebp_t*)pc)->a1), ebp_(((const knh_asmc_movo_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVO");
#endif
	pc += KNH_ASMC_MOVO_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVO__SFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVO__sfp__dump(ctx, (knh_asmc_movo_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVO
		VM_MOVO(ctx, ofp_(((const knh_asmc_movo_sfp_t*)pc)->a1), sfp_(((const knh_asmc_movo_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVO");
#endif
	pc += KNH_ASMC_MOVO_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVO__OFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVO__ofp__dump(ctx, (knh_asmc_movo_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVO
		VM_MOVO(ctx, ofp_(((const knh_asmc_movo_ofp_t*)pc)->a1), ofp_(((const knh_asmc_movo_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVO");
#endif
	pc += KNH_ASMC_MOVO_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVO__OBJ:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVO__OBJ__dump(ctx, (knh_asmc_movo_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVO
		VM_MOVO(ctx, ofp_(((const knh_asmc_movo_obj_t*)pc)->a1), OBJ_(((const knh_asmc_movo_obj_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVO");
#endif
	pc += KNH_ASMC_MOVO_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVO__OIDX:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVO__OIDX__dump(ctx, (knh_asmc_movo_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVO__OIDX
		VM_MOVO__OIDX(ctx, ofp_(((const knh_asmc_movo_oidx_t*)pc)->a1), OBJ_(((const knh_asmc_movo_oidx_t*)pc)->a2), u1_(((const knh_asmc_movo_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_MOVO__OIDX");
#endif
	pc += KNH_ASMC_MOVO_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVOI__EBP:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVOI__ebp__dump(ctx, (knh_asmc_movoi_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVOI
		VM_MOVOI(ctx, OBJ_(((const knh_asmc_movoi_ebp_t*)pc)->a1), ofp_(((const knh_asmc_movoi_ebp_t*)pc)->a2), ebp_(((const knh_asmc_movoi_ebp_t*)pc)->a3));
#else
		DBG_P("TODO: VM_MOVOI");
#endif
	pc += KNH_ASMC_MOVOI_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVOI__SFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVOI__sfp__dump(ctx, (knh_asmc_movoi_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVOI
		VM_MOVOI(ctx, OBJ_(((const knh_asmc_movoi_sfp_t*)pc)->a1), ofp_(((const knh_asmc_movoi_sfp_t*)pc)->a2), sfp_(((const knh_asmc_movoi_sfp_t*)pc)->a3));
#else
		DBG_P("TODO: VM_MOVOI");
#endif
	pc += KNH_ASMC_MOVOI_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVOI__OFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVOI__ofp__dump(ctx, (knh_asmc_movoi_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVOI
		VM_MOVOI(ctx, OBJ_(((const knh_asmc_movoi_ofp_t*)pc)->a1), ofp_(((const knh_asmc_movoi_ofp_t*)pc)->a2), ofp_(((const knh_asmc_movoi_ofp_t*)pc)->a3));
#else
		DBG_P("TODO: VM_MOVOI");
#endif
	pc += KNH_ASMC_MOVOI_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVOI__OBJ:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVOI__OBJ__dump(ctx, (knh_asmc_movoi_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVOI
		VM_MOVOI(ctx, OBJ_(((const knh_asmc_movoi_obj_t*)pc)->a1), ofp_(((const knh_asmc_movoi_obj_t*)pc)->a2), OBJ_(((const knh_asmc_movoi_obj_t*)pc)->a3));
#else
		DBG_P("TODO: VM_MOVOI");
#endif
	pc += KNH_ASMC_MOVOI_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVOI__OIDX:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVOI__OIDX__dump(ctx, (knh_asmc_movoi_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVOI__OIDX
		VM_MOVOI__OIDX(ctx, OBJ_(((const knh_asmc_movoi_oidx_t*)pc)->a1), u1_(((const knh_asmc_movoi_oidx_t*)pc)->a2), OBJ_(((const knh_asmc_movoi_oidx_t*)pc)->a3), u1_(((const knh_asmc_movoi_oidx_t*)pc)->a4));
#else
		DBG_P("TODO: VM_MOVOI__OIDX");
#endif
	pc += KNH_ASMC_MOVOI_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVSFP_IFNUL:;
#ifdef DBG_P_VMC
	knh_KLRCode_MOVSFP_IFNUL__dump(ctx, (knh_asmc_movsfp_ifnul_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MOVSFP_IFNUL
		VM_MOVSFP_IFNUL(ctx, u1_(((const knh_asmc_movsfp_ifnul_t*)pc)->a1), OBJ_(((const knh_asmc_movsfp_ifnul_t*)pc)->a2));
#else
		DBG_P("TODO: VM_MOVSFP_IFNUL");
#endif
	pc += KNH_ASMC_MOVSFP_IFNUL_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PUSH__EBP:;
#ifdef DBG_P_VMC
	knh_KLRCode_PUSH__ebp__dump(ctx, (knh_asmc_push_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PUSH
		VM_PUSH(ctx, ebp_(((const knh_asmc_push_ebp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_PUSH");
#endif
	pc += KNH_ASMC_PUSH_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PUSH__SFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_PUSH__sfp__dump(ctx, (knh_asmc_push_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PUSH
		VM_PUSH(ctx, sfp_(((const knh_asmc_push_sfp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_PUSH");
#endif
	pc += KNH_ASMC_PUSH_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PUSH__OFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_PUSH__ofp__dump(ctx, (knh_asmc_push_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PUSH
		VM_PUSH(ctx, ofp_(((const knh_asmc_push_ofp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_PUSH");
#endif
	pc += KNH_ASMC_PUSH_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PUSH__OBJ:;
#ifdef DBG_P_VMC
	knh_KLRCode_PUSH__OBJ__dump(ctx, (knh_asmc_push_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PUSH
		VM_PUSH(ctx, OBJ_(((const knh_asmc_push_obj_t*)pc)->a1));
#else
		DBG_P("TODO: VM_PUSH");
#endif
	pc += KNH_ASMC_PUSH_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PUSH__OIDX:;
#ifdef DBG_P_VMC
	knh_KLRCode_PUSH__OIDX__dump(ctx, (knh_asmc_push_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PUSH__OIDX
		VM_PUSH__OIDX(ctx, OBJ_(((const knh_asmc_push_oidx_t*)pc)->a1), u1_(((const knh_asmc_push_oidx_t*)pc)->a2));
#else
		DBG_P("TODO: VM_PUSH__OIDX");
#endif
	pc += KNH_ASMC_PUSH_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PUT_SYSCONST:;
#ifdef DBG_P_VMC
	knh_KLRCode_PUT_SYSCONST__dump(ctx, (knh_asmc_put_sysconst_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PUT_SYSCONST
		VM_PUT_SYSCONST(ctx, u2_(((const knh_asmc_put_sysconst_t*)pc)->a1));
#else
		DBG_P("TODO: VM_PUT_SYSCONST");
#endif
	pc += KNH_ASMC_PUT_SYSCONST_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PUSH_SYSCONST:;
#ifdef DBG_P_VMC
	knh_KLRCode_PUSH_SYSCONST__dump(ctx, (knh_asmc_push_sysconst_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PUSH_SYSCONST
		VM_PUSH_SYSCONST(ctx, u2_(((const knh_asmc_push_sysconst_t*)pc)->a1));
#else
		DBG_P("TODO: VM_PUSH_SYSCONST");
#endif
	pc += KNH_ASMC_PUSH_SYSCONST_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PUSH__DEF:;
#ifdef DBG_P_VMC
	knh_KLRCode_PUSH__DEF__dump(ctx, (knh_asmc_push_def_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PUSH__DEF
		VM_PUSH__DEF(ctx, c2_(((const knh_asmc_push_def_t*)pc)->a1));
#else
		DBG_P("TODO: VM_PUSH__DEF");
#endif
	pc += KNH_ASMC_PUSH_DEF_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_VARGS:;
#ifdef DBG_P_VMC
	knh_KLRCode_VARGS__dump(ctx, (knh_asmc_vargs_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_VARGS
		VM_VARGS(ctx, u2_(((const knh_asmc_vargs_t*)pc)->a1));
#else
		DBG_P("TODO: VM_VARGS");
#endif
	pc += KNH_ASMC_VARGS_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_SHIFT:;
#ifdef DBG_P_VMC
	knh_KLRCode_SHIFT__dump(ctx, (knh_asmc_shift_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_SHIFT
		VM_SHIFT(ctx, i1_(((const knh_asmc_shift_t*)pc)->a1));
#else
		DBG_P("TODO: VM_SHIFT");
#endif
	pc += KNH_ASMC_SHIFT_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_SCALL:;
#ifdef DBG_P_VMC
	knh_KLRCode_SCALL__dump(ctx, (knh_asmc_scall_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_SCALL
		VM_SCALL(ctx, u1_(((const knh_asmc_scall_t*)pc)->a1));
#else
		DBG_P("TODO: VM_SCALL");
#endif
	pc += KNH_ASMC_SCALL_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NSCALL:;
#ifdef DBG_P_VMC
	knh_KLRCode_NSCALL__dump(ctx, (knh_asmc_nscall_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NSCALL
		VM_NSCALL(ctx, u1_(((const knh_asmc_nscall_t*)pc)->a1));
#else
		DBG_P("TODO: VM_NSCALL");
#endif
	pc += KNH_ASMC_NSCALL_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_CALL:;
#ifdef DBG_P_VMC
	knh_KLRCode_CALL__dump(ctx, (knh_asmc_call_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_CALL
		VM_CALL(ctx, u1_(((const knh_asmc_call_t*)pc)->a1), mn_(((const knh_asmc_call_t*)pc)->a2));
#else
		DBG_P("TODO: VM_CALL");
#endif
	pc += KNH_ASMC_CALL_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_DCALL:;
#ifdef DBG_P_VMC
	knh_KLRCode_DCALL__dump(ctx, (knh_asmc_dcall_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_DCALL
		VM_DCALL(ctx, u1_(((const knh_asmc_dcall_t*)pc)->a1), mn_(((const knh_asmc_dcall_t*)pc)->a2));
#else
		DBG_P("TODO: VM_DCALL");
#endif
	pc += KNH_ASMC_DCALL_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NEW:;
#ifdef DBG_P_VMC
	knh_KLRCode_NEW__dump(ctx, (knh_asmc_new_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NEW
		VM_NEW(ctx, u2_(((const knh_asmc_new_t*)pc)->a1), u2_(((const knh_asmc_new_t*)pc)->a2), c2_(((const knh_asmc_new_t*)pc)->a3));
#else
		DBG_P("TODO: VM_NEW");
#endif
	pc += KNH_ASMC_NEW_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MT:;
#ifdef DBG_P_VMC
	knh_KLRCode_MT__dump(ctx, (knh_asmc_mt_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MT
		VM_MT(ctx, mn_(((const knh_asmc_mt_t*)pc)->a1));
#else
		DBG_P("TODO: VM_MT");
#endif
	pc += KNH_ASMC_MT_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_SMAP:;
#ifdef DBG_P_VMC
	knh_KLRCode_SMAP__dump(ctx, (knh_asmc_smap_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_SMAP
		VM_SMAP(ctx, OBJ_(((const knh_asmc_smap_t*)pc)->a1));
#else
		DBG_P("TODO: VM_SMAP");
#endif
	pc += KNH_ASMC_SMAP_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_SMAPE:;
#ifdef DBG_P_VMC
	knh_KLRCode_SMAPE__dump(ctx, (knh_asmc_smape_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_SMAPE
		VM_SMAPE(ctx, OBJ_(((const knh_asmc_smape_t*)pc)->a1));
#else
		DBG_P("TODO: VM_SMAPE");
#endif
	pc += KNH_ASMC_SMAPE_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MAP:;
#ifdef DBG_P_VMC
	knh_KLRCode_MAP__dump(ctx, (knh_asmc_map_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MAP
		VM_MAP(ctx, c2_(((const knh_asmc_map_t*)pc)->a1));
#else
		DBG_P("TODO: VM_MAP");
#endif
	pc += KNH_ASMC_MAP_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MAPE:;
#ifdef DBG_P_VMC
	knh_KLRCode_MAPE__dump(ctx, (knh_asmc_mape_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MAPE
		VM_MAPE(ctx, c2_(((const knh_asmc_mape_t*)pc)->a1));
#else
		DBG_P("TODO: VM_MAPE");
#endif
	pc += KNH_ASMC_MAPE_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_ANYMAP:;
#ifdef DBG_P_VMC
	knh_KLRCode_ANYMAP__dump(ctx, (knh_asmc_anymap_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_ANYMAP
		VM_ANYMAP(ctx, c2_(((const knh_asmc_anymap_t*)pc)->a1));
#else
		DBG_P("TODO: VM_ANYMAP");
#endif
	pc += KNH_ASMC_ANYMAP_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_ANYMAPE:;
#ifdef DBG_P_VMC
	knh_KLRCode_ANYMAPE__dump(ctx, (knh_asmc_anymape_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_ANYMAPE
		VM_ANYMAPE(ctx, c2_(((const knh_asmc_anymape_t*)pc)->a1));
#else
		DBG_P("TODO: VM_ANYMAPE");
#endif
	pc += KNH_ASMC_ANYMAPE_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MAP2:;
#ifdef DBG_P_VMC
	knh_KLRCode_MAP2__dump(ctx, (knh_asmc_map2_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MAP2
		VM_MAP2(ctx, c2_(((const knh_asmc_map2_t*)pc)->a1));
#else
		DBG_P("TODO: VM_MAP2");
#endif
	pc += KNH_ASMC_MAP2_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MAP2E:;
#ifdef DBG_P_VMC
	knh_KLRCode_MAP2E__dump(ctx, (knh_asmc_map2e_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MAP2E
		VM_MAP2E(ctx, c2_(((const knh_asmc_map2e_t*)pc)->a1));
#else
		DBG_P("TODO: VM_MAP2E");
#endif
	pc += KNH_ASMC_MAP2E_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_TYPECHK__EBP:;
#ifdef DBG_P_VMC
	knh_KLRCode_TYPECHK__ebp__dump(ctx, (knh_asmc_typechk_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_TYPECHK
		VM_TYPECHK(ctx, c2_(((const knh_asmc_typechk_ebp_t*)pc)->a1), ebp_(((const knh_asmc_typechk_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_TYPECHK");
#endif
	pc += KNH_ASMC_TYPECHK_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_TYPECHK__SFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_TYPECHK__sfp__dump(ctx, (knh_asmc_typechk_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_TYPECHK
		VM_TYPECHK(ctx, c2_(((const knh_asmc_typechk_sfp_t*)pc)->a1), sfp_(((const knh_asmc_typechk_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_TYPECHK");
#endif
	pc += KNH_ASMC_TYPECHK_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_TYPECHK__OFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_TYPECHK__ofp__dump(ctx, (knh_asmc_typechk_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_TYPECHK
		VM_TYPECHK(ctx, c2_(((const knh_asmc_typechk_ofp_t*)pc)->a1), ofp_(((const knh_asmc_typechk_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_TYPECHK");
#endif
	pc += KNH_ASMC_TYPECHK_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_TYPECHK__OBJ:;
#ifdef DBG_P_VMC
	knh_KLRCode_TYPECHK__OBJ__dump(ctx, (knh_asmc_typechk_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_TYPECHK
		VM_TYPECHK(ctx, c2_(((const knh_asmc_typechk_obj_t*)pc)->a1), OBJ_(((const knh_asmc_typechk_obj_t*)pc)->a2));
#else
		DBG_P("TODO: VM_TYPECHK");
#endif
	pc += KNH_ASMC_TYPECHK_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_TYPECHK__OIDX:;
#ifdef DBG_P_VMC
	knh_KLRCode_TYPECHK__OIDX__dump(ctx, (knh_asmc_typechk_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_TYPECHK__OIDX
		VM_TYPECHK__OIDX(ctx, c2_(((const knh_asmc_typechk_oidx_t*)pc)->a1), OBJ_(((const knh_asmc_typechk_oidx_t*)pc)->a2), u1_(((const knh_asmc_typechk_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_TYPECHK__OIDX");
#endif
	pc += KNH_ASMC_TYPECHK_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NULLCHK__EBP:;
#ifdef DBG_P_VMC
	knh_KLRCode_NULLCHK__ebp__dump(ctx, (knh_asmc_nullchk_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NULLCHK
		VM_NULLCHK(ctx, ebp_(((const knh_asmc_nullchk_ebp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_NULLCHK");
#endif
	pc += KNH_ASMC_NULLCHK_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NULLCHK__SFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_NULLCHK__sfp__dump(ctx, (knh_asmc_nullchk_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NULLCHK
		VM_NULLCHK(ctx, sfp_(((const knh_asmc_nullchk_sfp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_NULLCHK");
#endif
	pc += KNH_ASMC_NULLCHK_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NULLCHK__OFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_NULLCHK__ofp__dump(ctx, (knh_asmc_nullchk_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NULLCHK
		VM_NULLCHK(ctx, ofp_(((const knh_asmc_nullchk_ofp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_NULLCHK");
#endif
	pc += KNH_ASMC_NULLCHK_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NULLCHK__OBJ:;
#ifdef DBG_P_VMC
	knh_KLRCode_NULLCHK__OBJ__dump(ctx, (knh_asmc_nullchk_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NULLCHK
		VM_NULLCHK(ctx, OBJ_(((const knh_asmc_nullchk_obj_t*)pc)->a1));
#else
		DBG_P("TODO: VM_NULLCHK");
#endif
	pc += KNH_ASMC_NULLCHK_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NULLCHK__OIDX:;
#ifdef DBG_P_VMC
	knh_KLRCode_NULLCHK__OIDX__dump(ctx, (knh_asmc_nullchk_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NULLCHK__OIDX
		VM_NULLCHK__OIDX(ctx, OBJ_(((const knh_asmc_nullchk_oidx_t*)pc)->a1), u1_(((const knh_asmc_nullchk_oidx_t*)pc)->a2));
#else
		DBG_P("TODO: VM_NULLCHK__OIDX");
#endif
	pc += KNH_ASMC_NULLCHK_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP__dump(ctx, (knh_asmc_jmp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP
		VM_JMP(ctx, pc += ((const knh_asmc_jmp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)]);
#else
		DBG_P("TODO: VM_JMP");
#endif
	pc += KNH_ASMC_JMP_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_SKIP:;
#ifdef DBG_P_VMC
	knh_KLRCode_SKIP__dump(ctx, (knh_asmc_skip_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_SKIP
		VM_SKIP(ctx, pc += ((const knh_asmc_skip_t*)pc)->a1, *globalMachineToJump[PCT_(pc)]);
#else
		DBG_P("TODO: VM_SKIP");
#endif
	pc += KNH_ASMC_SKIP_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFT__EBP:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFT__ebp__dump(ctx, (knh_asmc_jmp_ift_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFT
		VM_JMP_IFT(ctx, pc += ((const knh_asmc_jmp_ift_ebp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ebp_(((const knh_asmc_jmp_ift_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFT");
#endif
	pc += KNH_ASMC_JMP_IFT_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFT__SFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFT__sfp__dump(ctx, (knh_asmc_jmp_ift_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFT
		VM_JMP_IFT(ctx, pc += ((const knh_asmc_jmp_ift_sfp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], sfp_(((const knh_asmc_jmp_ift_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFT");
#endif
	pc += KNH_ASMC_JMP_IFT_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFT__OFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFT__ofp__dump(ctx, (knh_asmc_jmp_ift_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFT
		VM_JMP_IFT(ctx, pc += ((const knh_asmc_jmp_ift_ofp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ofp_(((const knh_asmc_jmp_ift_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFT");
#endif
	pc += KNH_ASMC_JMP_IFT_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFT__OIDX:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFT__OIDX__dump(ctx, (knh_asmc_jmp_ift_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFT__OIDX
		VM_JMP_IFT__OIDX(ctx, pc += ((const knh_asmc_jmp_ift_oidx_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], OBJ_(((const knh_asmc_jmp_ift_oidx_t*)pc)->a2), u1_(((const knh_asmc_jmp_ift_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_JMP_IFT__OIDX");
#endif
	pc += KNH_ASMC_JMP_IFT_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFF__EBP:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFF__ebp__dump(ctx, (knh_asmc_jmp_iff_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFF
		VM_JMP_IFF(ctx, pc += ((const knh_asmc_jmp_iff_ebp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ebp_(((const knh_asmc_jmp_iff_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFF");
#endif
	pc += KNH_ASMC_JMP_IFF_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFF__SFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFF__sfp__dump(ctx, (knh_asmc_jmp_iff_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFF
		VM_JMP_IFF(ctx, pc += ((const knh_asmc_jmp_iff_sfp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], sfp_(((const knh_asmc_jmp_iff_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFF");
#endif
	pc += KNH_ASMC_JMP_IFF_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFF__OFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFF__ofp__dump(ctx, (knh_asmc_jmp_iff_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFF
		VM_JMP_IFF(ctx, pc += ((const knh_asmc_jmp_iff_ofp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ofp_(((const knh_asmc_jmp_iff_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFF");
#endif
	pc += KNH_ASMC_JMP_IFF_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFF__OIDX:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFF__OIDX__dump(ctx, (knh_asmc_jmp_iff_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFF__OIDX
		VM_JMP_IFF__OIDX(ctx, pc += ((const knh_asmc_jmp_iff_oidx_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], OBJ_(((const knh_asmc_jmp_iff_oidx_t*)pc)->a2), u1_(((const knh_asmc_jmp_iff_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_JMP_IFF__OIDX");
#endif
	pc += KNH_ASMC_JMP_IFF_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFTNN__EBP:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFTNN__ebp__dump(ctx, (knh_asmc_jmp_iftnn_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFTNN
		VM_JMP_IFTNN(ctx, pc += ((const knh_asmc_jmp_iftnn_ebp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ebp_(((const knh_asmc_jmp_iftnn_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFTNN");
#endif
	pc += KNH_ASMC_JMP_IFTNN_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFTNN__SFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFTNN__sfp__dump(ctx, (knh_asmc_jmp_iftnn_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFTNN
		VM_JMP_IFTNN(ctx, pc += ((const knh_asmc_jmp_iftnn_sfp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], sfp_(((const knh_asmc_jmp_iftnn_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFTNN");
#endif
	pc += KNH_ASMC_JMP_IFTNN_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFTNN__OFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFTNN__ofp__dump(ctx, (knh_asmc_jmp_iftnn_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFTNN
		VM_JMP_IFTNN(ctx, pc += ((const knh_asmc_jmp_iftnn_ofp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ofp_(((const knh_asmc_jmp_iftnn_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFTNN");
#endif
	pc += KNH_ASMC_JMP_IFTNN_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFTNN__OIDX:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFTNN__OIDX__dump(ctx, (knh_asmc_jmp_iftnn_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFTNN__OIDX
		VM_JMP_IFTNN__OIDX(ctx, pc += ((const knh_asmc_jmp_iftnn_oidx_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], OBJ_(((const knh_asmc_jmp_iftnn_oidx_t*)pc)->a2), u1_(((const knh_asmc_jmp_iftnn_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_JMP_IFTNN__OIDX");
#endif
	pc += KNH_ASMC_JMP_IFTNN_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFFN__EBP:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFFN__ebp__dump(ctx, (knh_asmc_jmp_iffn_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFFN
		VM_JMP_IFFN(ctx, pc += ((const knh_asmc_jmp_iffn_ebp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ebp_(((const knh_asmc_jmp_iffn_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFFN");
#endif
	pc += KNH_ASMC_JMP_IFFN_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFFN__SFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFFN__sfp__dump(ctx, (knh_asmc_jmp_iffn_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFFN
		VM_JMP_IFFN(ctx, pc += ((const knh_asmc_jmp_iffn_sfp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], sfp_(((const knh_asmc_jmp_iffn_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFFN");
#endif
	pc += KNH_ASMC_JMP_IFFN_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFFN__OFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFFN__ofp__dump(ctx, (knh_asmc_jmp_iffn_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFFN
		VM_JMP_IFFN(ctx, pc += ((const knh_asmc_jmp_iffn_ofp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ofp_(((const knh_asmc_jmp_iffn_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFFN");
#endif
	pc += KNH_ASMC_JMP_IFFN_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFFN__OIDX:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFFN__OIDX__dump(ctx, (knh_asmc_jmp_iffn_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFFN__OIDX
		VM_JMP_IFFN__OIDX(ctx, pc += ((const knh_asmc_jmp_iffn_oidx_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], OBJ_(((const knh_asmc_jmp_iffn_oidx_t*)pc)->a2), u1_(((const knh_asmc_jmp_iffn_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_JMP_IFFN__OIDX");
#endif
	pc += KNH_ASMC_JMP_IFFN_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFNN__EBP:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFNN__ebp__dump(ctx, (knh_asmc_jmp_ifnn_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFNN
		VM_JMP_IFNN(ctx, pc += ((const knh_asmc_jmp_ifnn_ebp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ebp_(((const knh_asmc_jmp_ifnn_ebp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFNN");
#endif
	pc += KNH_ASMC_JMP_IFNN_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFNN__SFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFNN__sfp__dump(ctx, (knh_asmc_jmp_ifnn_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFNN
		VM_JMP_IFNN(ctx, pc += ((const knh_asmc_jmp_ifnn_sfp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], sfp_(((const knh_asmc_jmp_ifnn_sfp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFNN");
#endif
	pc += KNH_ASMC_JMP_IFNN_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFNN__OFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFNN__ofp__dump(ctx, (knh_asmc_jmp_ifnn_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFNN
		VM_JMP_IFNN(ctx, pc += ((const knh_asmc_jmp_ifnn_ofp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ofp_(((const knh_asmc_jmp_ifnn_ofp_t*)pc)->a2));
#else
		DBG_P("TODO: VM_JMP_IFNN");
#endif
	pc += KNH_ASMC_JMP_IFNN_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFNN__OIDX:;
#ifdef DBG_P_VMC
	knh_KLRCode_JMP_IFNN__OIDX__dump(ctx, (knh_asmc_jmp_ifnn_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_JMP_IFNN__OIDX
		VM_JMP_IFNN__OIDX(ctx, pc += ((const knh_asmc_jmp_ifnn_oidx_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], OBJ_(((const knh_asmc_jmp_ifnn_oidx_t*)pc)->a2), u1_(((const knh_asmc_jmp_ifnn_oidx_t*)pc)->a3));
#else
		DBG_P("TODO: VM_JMP_IFNN__OIDX");
#endif
	pc += KNH_ASMC_JMP_IFNN_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NEXT:;
#ifdef DBG_P_VMC
	knh_KLRCode_NEXT__dump(ctx, (knh_asmc_next_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NEXT
		VM_NEXT(ctx, pc += ((const knh_asmc_next_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], sfp_(((const knh_asmc_next_t*)pc)->a2), sfp_(((const knh_asmc_next_t*)pc)->a3));
#else
		DBG_P("TODO: VM_NEXT");
#endif
	pc += KNH_ASMC_NEXT_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MAPNEXT:;
#ifdef DBG_P_VMC
	knh_KLRCode_MAPNEXT__dump(ctx, (knh_asmc_mapnext_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_MAPNEXT
		VM_MAPNEXT(ctx, pc += ((const knh_asmc_mapnext_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], sfp_(((const knh_asmc_mapnext_t*)pc)->a2), sfp_(((const knh_asmc_mapnext_t*)pc)->a3), c2_(((const knh_asmc_mapnext_t*)pc)->a4));
#else
		DBG_P("TODO: VM_MAPNEXT");
#endif
	pc += KNH_ASMC_MAPNEXT_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_SMAPNEXT:;
#ifdef DBG_P_VMC
	knh_KLRCode_SMAPNEXT__dump(ctx, (knh_asmc_smapnext_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_SMAPNEXT
		VM_SMAPNEXT(ctx, pc += ((const knh_asmc_smapnext_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], sfp_(((const knh_asmc_smapnext_t*)pc)->a2), sfp_(((const knh_asmc_smapnext_t*)pc)->a3), OBJ_(((const knh_asmc_smapnext_t*)pc)->a4));
#else
		DBG_P("TODO: VM_SMAPNEXT");
#endif
	pc += KNH_ASMC_SMAPNEXT_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_TRY_BEGIN:;
#ifdef DBG_P_VMC
	knh_KLRCode_TRY_BEGIN__dump(ctx, (knh_asmc_try_begin_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_TRY_BEGIN
		VM_TRY_BEGIN(ctx, pc += ((const knh_asmc_try_begin_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], sfp_(((const knh_asmc_try_begin_t*)pc)->a2), sfp_(((const knh_asmc_try_begin_t*)pc)->a3));
#else
		DBG_P("TODO: VM_TRY_BEGIN");
#endif
	pc += KNH_ASMC_TRY_BEGIN_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_TRY_END:;
#ifdef DBG_P_VMC
	knh_KLRCode_TRY_END__dump(ctx, (knh_asmc_try_end_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_TRY_END
		VM_TRY_END(ctx, sfp_(((const knh_asmc_try_end_t*)pc)->a1));
#else
		DBG_P("TODO: VM_TRY_END");
#endif
	pc += KNH_ASMC_TRY_END_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_CATCH:;
#ifdef DBG_P_VMC
	knh_KLRCode_CATCH__dump(ctx, (knh_asmc_catch_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_CATCH
		VM_CATCH(ctx, pc += ((const knh_asmc_catch_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], e2_(((const knh_asmc_catch_t*)pc)->a2), sfp_(((const knh_asmc_catch_t*)pc)->a3));
#else
		DBG_P("TODO: VM_CATCH");
#endif
	pc += KNH_ASMC_CATCH_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_THROW__EBP:;
#ifdef DBG_P_VMC
	knh_KLRCode_THROW__ebp__dump(ctx, (knh_asmc_throw_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_THROW
		VM_THROW(ctx, ebp_(((const knh_asmc_throw_ebp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_THROW");
#endif
	pc += KNH_ASMC_THROW_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_THROW__SFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_THROW__sfp__dump(ctx, (knh_asmc_throw_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_THROW
		VM_THROW(ctx, sfp_(((const knh_asmc_throw_sfp_t*)pc)->a1));
#else
		DBG_P("TODO: VM_THROW");
#endif
	pc += KNH_ASMC_THROW_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_THROW__OBJ:;
#ifdef DBG_P_VMC
	knh_KLRCode_THROW__OBJ__dump(ctx, (knh_asmc_throw_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_THROW
		VM_THROW(ctx, OBJ_(((const knh_asmc_throw_obj_t*)pc)->a1));
#else
		DBG_P("TODO: VM_THROW");
#endif
	pc += KNH_ASMC_THROW_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PRINT__EBP:;
#ifdef DBG_P_VMC
	knh_KLRCode_PRINT__ebp__dump(ctx, (knh_asmc_print_ebp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PRINT
		VM_PRINT(ctx, u2_(((const knh_asmc_print_ebp_t*)pc)->a1), OBJ_(((const knh_asmc_print_ebp_t*)pc)->a2), mn_(((const knh_asmc_print_ebp_t*)pc)->a3), ebp_(((const knh_asmc_print_ebp_t*)pc)->a4));
#else
		DBG_P("TODO: VM_PRINT");
#endif
	pc += KNH_ASMC_PRINT_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PRINT__SFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_PRINT__sfp__dump(ctx, (knh_asmc_print_sfp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PRINT
		VM_PRINT(ctx, u2_(((const knh_asmc_print_sfp_t*)pc)->a1), OBJ_(((const knh_asmc_print_sfp_t*)pc)->a2), mn_(((const knh_asmc_print_sfp_t*)pc)->a3), sfp_(((const knh_asmc_print_sfp_t*)pc)->a4));
#else
		DBG_P("TODO: VM_PRINT");
#endif
	pc += KNH_ASMC_PRINT_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PRINT__OFP:;
#ifdef DBG_P_VMC
	knh_KLRCode_PRINT__ofp__dump(ctx, (knh_asmc_print_ofp_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PRINT
		VM_PRINT(ctx, u2_(((const knh_asmc_print_ofp_t*)pc)->a1), OBJ_(((const knh_asmc_print_ofp_t*)pc)->a2), mn_(((const knh_asmc_print_ofp_t*)pc)->a3), ofp_(((const knh_asmc_print_ofp_t*)pc)->a4));
#else
		DBG_P("TODO: VM_PRINT");
#endif
	pc += KNH_ASMC_PRINT_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PRINT__OBJ:;
#ifdef DBG_P_VMC
	knh_KLRCode_PRINT__OBJ__dump(ctx, (knh_asmc_print_obj_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PRINT
		VM_PRINT(ctx, u2_(((const knh_asmc_print_obj_t*)pc)->a1), OBJ_(((const knh_asmc_print_obj_t*)pc)->a2), mn_(((const knh_asmc_print_obj_t*)pc)->a3), OBJ_(((const knh_asmc_print_obj_t*)pc)->a4));
#else
		DBG_P("TODO: VM_PRINT");
#endif
	pc += KNH_ASMC_PRINT_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PRINT__OIDX:;
#ifdef DBG_P_VMC
	knh_KLRCode_PRINT__OIDX__dump(ctx, (knh_asmc_print_oidx_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_PRINT__OIDX
		VM_PRINT__OIDX(ctx, u2_(((const knh_asmc_print_oidx_t*)pc)->a1), OBJ_(((const knh_asmc_print_oidx_t*)pc)->a2), mn_(((const knh_asmc_print_oidx_t*)pc)->a3), OBJ_(((const knh_asmc_print_oidx_t*)pc)->a4), u1_(((const knh_asmc_print_oidx_t*)pc)->a5));
#else
		DBG_P("TODO: VM_PRINT__OIDX");
#endif
	pc += KNH_ASMC_PRINT_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NOP:;
#ifdef DBG_P_VMC
	knh_KLRCode_NOP__dump(ctx, (knh_asmc_nop_t*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_NOP
		VM_NOP(ctx);
#else
		DBG_P("TODO: VM_NOP");
#endif
	pc += KNH_ASMC_NOP_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_UNKNOWN:;
	DBG_P("Broken code??");
	KNH_ASSERT(pc == NULL);
	KNH_THROWs(ctx, "Halt!!");
}
#endif

#ifdef __cplusplus
}
#endif
