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
#include<konoha/konohac_asm_.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

#define PCT_(pc)    (((knh_asmc_nop_t*)pc)->code)

/* ------------------------------------------------------------------------ */

/* ======================================================================== */
/* [label] */


void knh_Cmpl_rewriteAddress(Ctx *ctx, Cmpl *b, knh_asmc_jmp_t *bw)
{
	//DEBUG("label: id=%d", knh_VirtualMachineCode_uread_short(pc));
	String *name = knh_DictIdx_get(b->labelIdDictIdx, bw->a1);
	DEBUG_ASSERT(IS_NOTNULL(name));
	knh_vmc_t *pa = (knh_vmc_t*)knh_DictSet_get__b(b->labelAddrDictSet, knh_String_tobytes(name));
	if(pa == NULL) {
		TODO();
		DEBUG("Asm!!: Unknown Label '%s'", knh_String_tochar(name));
	}else {
		bw->a1 = (knh_short_t)(pa - (knh_vmc_t*)bw);
	}
}

/* ------------------------------------------------------------------------ */

void knh_Cmpl_remapAddress(Ctx *ctx, Cmpl *b)
{
	knh_vmc_t *pc = (knh_vmc_t*)knh_Bytes_tochar(b->elf);
	knh_vmc_t *tail = pc + knh_Bytes_size(b->elf);
	while(pc < tail) {
		switch(PCT_(pc)) {
		case ASMC_RET_VOID :
			pc += KNH_ASMC_RET_VOID_SIZ;
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
		case ASMC_PUTI :
			pc += KNH_ASMC_PUTI_SIZ;
			break;
		case ASMC_PUSH__MN :
			pc += KNH_ASMC_PUSH_MN_SIZ;
			break;
		case ASMC_PUSH__DEF :
			pc += KNH_ASMC_PUSH_DEF_SIZ;
			break;
		case ASMC_VARGS :
			pc += KNH_ASMC_VARGS_SIZ;
			break;
		case ASMC_SCALL :
			pc += KNH_ASMC_SCALL_SIZ;
			break;
		case ASMC_CALL :
			pc += KNH_ASMC_CALL_SIZ;
			break;
		case ASMC_DCALL :
			pc += KNH_ASMC_DCALL_SIZ;
			break;
		case ASMC_MCALL :
			pc += KNH_ASMC_MCALL_SIZ;
			break;
		case ASMC_CALL_WM :
			pc += KNH_ASMC_CALL_WM_SIZ;
			break;
		case ASMC_NCALL_WM :
			pc += KNH_ASMC_NCALL_WM_SIZ;
			break;
		case ASMC_NEW :
			pc += KNH_ASMC_NEW_SIZ;
			break;
		case ASMC_NEWE :
			pc += KNH_ASMC_NEWE_SIZ;
			break;
		case ASMC_NEW__DEF :
			pc += KNH_ASMC_NEW_DEF_SIZ;
			break;
		case ASMC_MT :
			pc += KNH_ASMC_MT_SIZ;
			break;
		case ASMC_MT__OPT :
			pc += KNH_ASMC_MT_OPT_SIZ;
			break;
		case ASMC_MAP :
			pc += KNH_ASMC_MAP_SIZ;
			break;
		case ASMC_MAPE :
			pc += KNH_ASMC_MAPE_SIZ;
			break;
		case ASMC_MAP_WM :
			pc += KNH_ASMC_MAP_WM_SIZ;
			break;
		case ASMC_MAPE_WM :
			pc += KNH_ASMC_MAPE_WM_SIZ;
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
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_SIZ;
			break;
		case ASMC_SKIP :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_SKIP_SIZ;
			break;
		case ASMC_JMP_IFT__EBP :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFT_ebp_SIZ;
			break;
		case ASMC_JMP_IFT__SFP :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFT_sfp_SIZ;
			break;
		case ASMC_JMP_IFT__OFP :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFT_ofp_SIZ;
			break;
		case ASMC_JMP_IFT__OIDX :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFT_OIDX_SIZ;
			break;
		case ASMC_JMP_IFF__EBP :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFF_ebp_SIZ;
			break;
		case ASMC_JMP_IFF__SFP :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFF_sfp_SIZ;
			break;
		case ASMC_JMP_IFF__OFP :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFF_ofp_SIZ;
			break;
		case ASMC_JMP_IFF__OIDX :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFF_OIDX_SIZ;
			break;
		case ASMC_JMP_IFNUL__EBP :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFNUL_ebp_SIZ;
			break;
		case ASMC_JMP_IFNUL__SFP :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFNUL_sfp_SIZ;
			break;
		case ASMC_JMP_IFNUL__OFP :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFNUL_ofp_SIZ;
			break;
		case ASMC_JMP_IFNUL__OIDX :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFNUL_OIDX_SIZ;
			break;
		case ASMC_JMP_IFNONUL__EBP :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFNONUL_ebp_SIZ;
			break;
		case ASMC_JMP_IFNONUL__SFP :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFNONUL_sfp_SIZ;
			break;
		case ASMC_JMP_IFNONUL__OFP :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFNONUL_ofp_SIZ;
			break;
		case ASMC_JMP_IFNONUL__OIDX :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_JMP_IFNONUL_OIDX_SIZ;
			break;
		case ASMC_ITER :
			pc += KNH_ASMC_ITER_SIZ;
			break;
		case ASMC_FOREACH :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_FOREACH_SIZ;
			break;
		case ASMC_TRY_BEGIN :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += KNH_ASMC_TRY_BEGIN_SIZ;
			break;
		case ASMC_TRY_END :
			pc += KNH_ASMC_TRY_END_SIZ;
			break;
		case ASMC_CATCH :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
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
		case ASMC_DIAGNOSE :
			pc += KNH_ASMC_DIAGNOSE_SIZ;
			break;
		case ASMC_STACKDUMP :
			pc += KNH_ASMC_STACKDUMP_SIZ;
			break;
		case ASMC_NOP :
			pc += KNH_ASMC_NOP_SIZ;
			break;

		default :
			DEBUG("UNKNOWN VMCODE: %d\n", PCT_(pc));
			DEBUG_ASSERT(ctx == NULL);
			return;
		}
	}
}

/* ======================================================================== */
/* [vmc] */

void knh_VirtualMachineCode_utraverse(Ctx *ctx, knh_bytes_t vmc, f_gc gc)
{
	knh_vmc_t *pc = (knh_vmc_t*)vmc.buf;
	knh_vmc_t *tail = vmc.buf + vmc.len;
	while(pc < tail) {
		switch(PCT_(pc)) {
		case ASMC_RET_VOID :
			pc += KNH_ASMC_RET_VOID_SIZ;
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

		case ASMC_PUTI :
			pc += KNH_ASMC_PUTI_SIZ;
			break;

		case ASMC_PUSH__MN :
			pc += KNH_ASMC_PUSH_MN_SIZ;
			break;

		case ASMC_PUSH__DEF :
			pc += KNH_ASMC_PUSH_DEF_SIZ;
			break;

		case ASMC_VARGS :
			pc += KNH_ASMC_VARGS_SIZ;
			break;

		case ASMC_SCALL :
			pc += KNH_ASMC_SCALL_SIZ;
			break;

		case ASMC_CALL :
			pc += KNH_ASMC_CALL_SIZ;
			break;

		case ASMC_DCALL :
			pc += KNH_ASMC_DCALL_SIZ;
			break;

		case ASMC_MCALL :
			pc += KNH_ASMC_MCALL_SIZ;
			break;

		case ASMC_CALL_WM :
			gc(ctx, ((knh_asmc_call_wm_t*)pc)->a2);
			pc += KNH_ASMC_CALL_WM_SIZ;
			break;

		case ASMC_NCALL_WM :
			gc(ctx, ((knh_asmc_ncall_wm_t*)pc)->a2);
			pc += KNH_ASMC_NCALL_WM_SIZ;
			break;

		case ASMC_NEW :
			gc(ctx, ((knh_asmc_new_t*)pc)->a2);
			pc += KNH_ASMC_NEW_SIZ;
			break;

		case ASMC_NEWE :
			gc(ctx, ((knh_asmc_newe_t*)pc)->a2);
			pc += KNH_ASMC_NEWE_SIZ;
			break;

		case ASMC_NEW__DEF :
			pc += KNH_ASMC_NEW_DEF_SIZ;
			break;

		case ASMC_MT :
			pc += KNH_ASMC_MT_SIZ;
			break;

		case ASMC_MT__OPT :
			gc(ctx, ((knh_asmc_mt_opt_t*)pc)->a2);
			pc += KNH_ASMC_MT_OPT_SIZ;
			break;

		case ASMC_MAP :
			pc += KNH_ASMC_MAP_SIZ;
			break;

		case ASMC_MAPE :
			pc += KNH_ASMC_MAPE_SIZ;
			break;

		case ASMC_MAP_WM :
			gc(ctx, ((knh_asmc_map_wm_t*)pc)->a1);
			pc += KNH_ASMC_MAP_WM_SIZ;
			break;

		case ASMC_MAPE_WM :
			gc(ctx, ((knh_asmc_mape_wm_t*)pc)->a1);
			pc += KNH_ASMC_MAPE_WM_SIZ;
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

		case ASMC_JMP_IFNUL__EBP :
			pc += KNH_ASMC_JMP_IFNUL_ebp_SIZ;
			break;

		case ASMC_JMP_IFNUL__SFP :
			pc += KNH_ASMC_JMP_IFNUL_sfp_SIZ;
			break;

		case ASMC_JMP_IFNUL__OFP :
			pc += KNH_ASMC_JMP_IFNUL_ofp_SIZ;
			break;

		case ASMC_JMP_IFNUL__OIDX :
			gc(ctx, ((knh_asmc_jmp_ifnul_oidx_t*)pc)->a2);
			pc += KNH_ASMC_JMP_IFNUL_OIDX_SIZ;
			break;

		case ASMC_JMP_IFNONUL__EBP :
			pc += KNH_ASMC_JMP_IFNONUL_ebp_SIZ;
			break;

		case ASMC_JMP_IFNONUL__SFP :
			pc += KNH_ASMC_JMP_IFNONUL_sfp_SIZ;
			break;

		case ASMC_JMP_IFNONUL__OFP :
			pc += KNH_ASMC_JMP_IFNONUL_ofp_SIZ;
			break;

		case ASMC_JMP_IFNONUL__OIDX :
			gc(ctx, ((knh_asmc_jmp_ifnonul_oidx_t*)pc)->a2);
			pc += KNH_ASMC_JMP_IFNONUL_OIDX_SIZ;
			break;

		case ASMC_ITER :
			pc += KNH_ASMC_ITER_SIZ;
			break;

		case ASMC_FOREACH :
			pc += KNH_ASMC_FOREACH_SIZ;
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
			pc += KNH_ASMC_PRINT_ebp_SIZ;
			break;

		case ASMC_PRINT__SFP :
			pc += KNH_ASMC_PRINT_sfp_SIZ;
			break;

		case ASMC_PRINT__OFP :
			pc += KNH_ASMC_PRINT_ofp_SIZ;
			break;

		case ASMC_PRINT__OBJ :
			gc(ctx, ((knh_asmc_print_obj_t*)pc)->a3);
			pc += KNH_ASMC_PRINT_OBJ_SIZ;
			break;

		case ASMC_PRINT__OIDX :
			gc(ctx, ((knh_asmc_print_oidx_t*)pc)->a3);
			pc += KNH_ASMC_PRINT_OIDX_SIZ;
			break;

		case ASMC_DIAGNOSE :
			pc += KNH_ASMC_DIAGNOSE_SIZ;
			break;

		case ASMC_STACKDUMP :
			pc += KNH_ASMC_STACKDUMP_SIZ;
			break;

		case ASMC_NOP :
			pc += KNH_ASMC_NOP_SIZ;
			break;

		default :
			DEBUG("UNKNOWN VMCODE: %d\n", PCT_(pc));
			DEBUG_ASSERT(ctx == NULL);
			return;
		}
	}
}

/* ======================================================================== */
/* [dump] */

void knh_VirtualMachineCode_RET_VOID__dump(Ctx *ctx, knh_asmc_ret_void_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "ret_void");
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_RET__ebp__dump(Ctx *ctx, knh_asmc_ret_ebp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "ret__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_RET__sfp__dump(Ctx *ctx, knh_asmc_ret_sfp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "ret__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_RET__ofp__dump(Ctx *ctx, knh_asmc_ret_ofp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "ret__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_RET__OBJ__dump(Ctx *ctx, knh_asmc_ret_obj_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "ret__obj");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a1), KNH_NULL);
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_RET__OIDX__dump(Ctx *ctx, knh_asmc_ret_oidx_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "ret__oidx");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a1), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVE__ebp__dump(Ctx *ctx, knh_asmc_move_ebp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "move__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVE__sfp__dump(Ctx *ctx, knh_asmc_move_sfp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "move__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVE__ofp__dump(Ctx *ctx, knh_asmc_move_ofp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "move__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVE__OBJ__dump(Ctx *ctx, knh_asmc_move_obj_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "move__obj");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVE__OIDX__dump(Ctx *ctx, knh_asmc_move_oidx_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "move__oidx");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVS__ebp__dump(Ctx *ctx, knh_asmc_movs_ebp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movs__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVS__sfp__dump(Ctx *ctx, knh_asmc_movs_sfp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movs__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVS__ofp__dump(Ctx *ctx, knh_asmc_movs_ofp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movs__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVS__OBJ__dump(Ctx *ctx, knh_asmc_movs_obj_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movs__obj");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVS__OIDX__dump(Ctx *ctx, knh_asmc_movs_oidx_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movs__oidx");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVO__ebp__dump(Ctx *ctx, knh_asmc_movo_ebp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movo__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVO__sfp__dump(Ctx *ctx, knh_asmc_movo_sfp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movo__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVO__ofp__dump(Ctx *ctx, knh_asmc_movo_ofp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movo__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVO__OBJ__dump(Ctx *ctx, knh_asmc_movo_obj_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movo__obj");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVO__OIDX__dump(Ctx *ctx, knh_asmc_movo_oidx_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movo__oidx");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVOI__ebp__dump(Ctx *ctx, knh_asmc_movoi_ebp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movoi__ebp");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a1), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVOI__sfp__dump(Ctx *ctx, knh_asmc_movoi_sfp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movoi__sfp");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a1), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVOI__ofp__dump(Ctx *ctx, knh_asmc_movoi_ofp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movoi__ofp");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a1), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVOI__OBJ__dump(Ctx *ctx, knh_asmc_movoi_obj_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movoi__obj");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a1), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a3), KNH_NULL);
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVOI__OIDX__dump(Ctx *ctx, knh_asmc_movoi_oidx_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movoi__oidx");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a1), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a3), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a4));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MOVSFP_IFNUL__dump(Ctx *ctx, knh_asmc_movsfp_ifnul_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "movsfp_ifnul");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_PUSH__sfp__dump(Ctx *ctx, knh_asmc_push_sfp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "push__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_PUSH__ofp__dump(Ctx *ctx, knh_asmc_push_ofp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "push__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_PUSH__OBJ__dump(Ctx *ctx, knh_asmc_push_obj_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "push__obj");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a1), KNH_NULL);
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_PUSH__OIDX__dump(Ctx *ctx, knh_asmc_push_oidx_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "push__oidx");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a1), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_PUTI__dump(Ctx *ctx, knh_asmc_puti_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "puti");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_PUSH__MN__dump(Ctx *ctx, knh_asmc_push_mn_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "push__mn");
	knh_putc(ctx, w, ' ');
	knh_write__mn(ctx, w, (knh_methodn_t)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_PUSH__DEF__dump(Ctx *ctx, knh_asmc_push_def_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "push__def");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_VARGS__dump(Ctx *ctx, knh_asmc_vargs_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "vargs");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_SCALL__dump(Ctx *ctx, knh_asmc_scall_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "scall");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_CALL__dump(Ctx *ctx, knh_asmc_call_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "call");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_DCALL__dump(Ctx *ctx, knh_asmc_dcall_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "dcall");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MCALL__dump(Ctx *ctx, knh_asmc_mcall_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "mcall");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_CALL_WM__dump(Ctx *ctx, knh_asmc_call_wm_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "call_wm");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_NCALL_WM__dump(Ctx *ctx, knh_asmc_ncall_wm_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "ncall_wm");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_NEW__dump(Ctx *ctx, knh_asmc_new_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "new");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a4));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_NEWE__dump(Ctx *ctx, knh_asmc_newe_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "newe");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a4));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_NEW__DEF__dump(Ctx *ctx, knh_asmc_new_def_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "new__def");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MT__dump(Ctx *ctx, knh_asmc_mt_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "mt");
	knh_putc(ctx, w, ' ');
	knh_write__mn(ctx, w, (knh_methodn_t)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MT__OPT__dump(Ctx *ctx, knh_asmc_mt_opt_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "mt__opt");
	knh_putc(ctx, w, ' ');
	knh_write__mn(ctx, w, (knh_methodn_t)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MAP__dump(Ctx *ctx, knh_asmc_map_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "map");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MAPE__dump(Ctx *ctx, knh_asmc_mape_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "mape");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MAP_WM__dump(Ctx *ctx, knh_asmc_map_wm_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "map_wm");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a1), KNH_NULL);
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MAPE_WM__dump(Ctx *ctx, knh_asmc_mape_wm_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "mape_wm");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a1), KNH_NULL);
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MAP2__dump(Ctx *ctx, knh_asmc_map2_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "map2");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_MAP2E__dump(Ctx *ctx, knh_asmc_map2e_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "map2e");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_TYPECHK__ebp__dump(Ctx *ctx, knh_asmc_typechk_ebp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "typechk__ebp");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_TYPECHK__sfp__dump(Ctx *ctx, knh_asmc_typechk_sfp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "typechk__sfp");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_TYPECHK__ofp__dump(Ctx *ctx, knh_asmc_typechk_ofp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "typechk__ofp");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_TYPECHK__OBJ__dump(Ctx *ctx, knh_asmc_typechk_obj_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "typechk__obj");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_TYPECHK__OIDX__dump(Ctx *ctx, knh_asmc_typechk_oidx_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "typechk__oidx");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_NULLCHK__ebp__dump(Ctx *ctx, knh_asmc_nullchk_ebp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "nullchk__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_NULLCHK__sfp__dump(Ctx *ctx, knh_asmc_nullchk_sfp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "nullchk__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_NULLCHK__ofp__dump(Ctx *ctx, knh_asmc_nullchk_ofp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "nullchk__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_NULLCHK__OBJ__dump(Ctx *ctx, knh_asmc_nullchk_obj_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "nullchk__obj");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a1), KNH_NULL);
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_NULLCHK__OIDX__dump(Ctx *ctx, knh_asmc_nullchk_oidx_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "nullchk__oidx");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a1), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP__dump(Ctx *ctx, knh_asmc_jmp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_SKIP__dump(Ctx *ctx, knh_asmc_skip_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "skip");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP_IFT__ebp__dump(Ctx *ctx, knh_asmc_jmp_ift_ebp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ift__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP_IFT__sfp__dump(Ctx *ctx, knh_asmc_jmp_ift_sfp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ift__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP_IFT__ofp__dump(Ctx *ctx, knh_asmc_jmp_ift_ofp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ift__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP_IFT__OIDX__dump(Ctx *ctx, knh_asmc_jmp_ift_oidx_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ift__oidx");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP_IFF__ebp__dump(Ctx *ctx, knh_asmc_jmp_iff_ebp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_iff__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP_IFF__sfp__dump(Ctx *ctx, knh_asmc_jmp_iff_sfp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_iff__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP_IFF__ofp__dump(Ctx *ctx, knh_asmc_jmp_iff_ofp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_iff__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP_IFF__OIDX__dump(Ctx *ctx, knh_asmc_jmp_iff_oidx_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_iff__oidx");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP_IFNUL__ebp__dump(Ctx *ctx, knh_asmc_jmp_ifnul_ebp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ifnul__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP_IFNUL__sfp__dump(Ctx *ctx, knh_asmc_jmp_ifnul_sfp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ifnul__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP_IFNUL__ofp__dump(Ctx *ctx, knh_asmc_jmp_ifnul_ofp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ifnul__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP_IFNUL__OIDX__dump(Ctx *ctx, knh_asmc_jmp_ifnul_oidx_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ifnul__oidx");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP_IFNONUL__ebp__dump(Ctx *ctx, knh_asmc_jmp_ifnonul_ebp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ifnonul__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP_IFNONUL__sfp__dump(Ctx *ctx, knh_asmc_jmp_ifnonul_sfp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ifnonul__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP_IFNONUL__ofp__dump(Ctx *ctx, knh_asmc_jmp_ifnonul_ofp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ifnonul__ofp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_JMP_IFNONUL__OIDX__dump(Ctx *ctx, knh_asmc_jmp_ifnonul_oidx_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "jmp_ifnonul__oidx");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a2), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_ITER__dump(Ctx *ctx, knh_asmc_iter_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "iter");
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a2));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_FOREACH__dump(Ctx *ctx, knh_asmc_foreach_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "foreach");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_write__type(ctx, w, (knh_type_t)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a3));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a4));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_TRY_BEGIN__dump(Ctx *ctx, knh_asmc_try_begin_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "try_begin");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_TRY_END__dump(Ctx *ctx, knh_asmc_try_end_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "try_end");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_CATCH__dump(Ctx *ctx, knh_asmc_catch_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "catch");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, ">>[%p]", (((void*)bw) + (bw->a1) - off));
	knh_putc(ctx, w, ' ');
	knh_write__expt(ctx, w, (knh_expt_t)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_THROW__ebp__dump(Ctx *ctx, knh_asmc_throw_ebp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "throw__ebp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_THROW__sfp__dump(Ctx *ctx, knh_asmc_throw_sfp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "throw__sfp");
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_THROW__OBJ__dump(Ctx *ctx, knh_asmc_throw_obj_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "throw__obj");
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a1), KNH_NULL);
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_PRINT__ebp__dump(Ctx *ctx, knh_asmc_print_ebp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "print__ebp");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_write__mn(ctx, w, (knh_methodn_t)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ebp[%d]", (int)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_PRINT__sfp__dump(Ctx *ctx, knh_asmc_print_sfp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "print__sfp");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_write__mn(ctx, w, (knh_methodn_t)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "sfp[%d]", (int)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_PRINT__ofp__dump(Ctx *ctx, knh_asmc_print_ofp_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "print__ofp");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_write__mn(ctx, w, (knh_methodn_t)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_printf(ctx, w, "ofp[%d]", (int)(bw->a3));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_PRINT__OBJ__dump(Ctx *ctx, knh_asmc_print_obj_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "print__obj");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_write__mn(ctx, w, (knh_methodn_t)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a3), KNH_NULL);
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_PRINT__OIDX__dump(Ctx *ctx, knh_asmc_print_oidx_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "print__oidx");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_putc(ctx, w, ' ');
	knh_write__mn(ctx, w, (knh_methodn_t)(bw->a2));
	knh_putc(ctx, w, ' ');
	knh_format(ctx, w, METHODN__repr, (bw->a3), KNH_NULL);
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a4));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_DIAGNOSE__dump(Ctx *ctx, knh_asmc_diagnose_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "diagnose");
	knh_putc(ctx, w, ' ');
	knh_write__i(ctx, w,  (int)(bw->a1));
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_STACKDUMP__dump(Ctx *ctx, knh_asmc_stackdump_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "stackdump");
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

void knh_VirtualMachineCode_NOP__dump(Ctx *ctx, knh_asmc_nop_t *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%d:%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "nop");
	knh_println(ctx, w, TEXT(""));
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */


PUBLIC
void knh_VirtualMachineCode__dump_(Ctx *ctx, VirtualMachineCode *b, Writer *w, Any *m)
{
	knh_bytes_t vmc = knh_VirtualMachineCode_tobytes(b);
	knh_vmc_t *pc = (knh_vmc_t*)vmc.buf;
	knh_vmc_t *tail = pc + vmc.len;	
	int off = (int)pc;
	while(pc < tail) {
		switch(PCT_(pc)) {
		case ASMC_RET_VOID :
			knh_VirtualMachineCode_RET_VOID__dump(ctx, (knh_asmc_ret_void_t*)pc, off, w, m);
			pc += KNH_ASMC_RET_VOID_SIZ;
			break;
		case ASMC_RET__EBP :
			knh_VirtualMachineCode_RET__ebp__dump(ctx, (knh_asmc_ret_ebp_t*)pc, off, w, m);
			pc += KNH_ASMC_RET_ebp_SIZ;
			break;
		case ASMC_RET__SFP :
			knh_VirtualMachineCode_RET__sfp__dump(ctx, (knh_asmc_ret_sfp_t*)pc, off, w, m);
			pc += KNH_ASMC_RET_sfp_SIZ;
			break;
		case ASMC_RET__OFP :
			knh_VirtualMachineCode_RET__ofp__dump(ctx, (knh_asmc_ret_ofp_t*)pc, off, w, m);
			pc += KNH_ASMC_RET_ofp_SIZ;
			break;
		case ASMC_RET__OBJ :
			knh_VirtualMachineCode_RET__OBJ__dump(ctx, (knh_asmc_ret_obj_t*)pc, off, w, m);
			pc += KNH_ASMC_RET_OBJ_SIZ;
			break;
		case ASMC_RET__OIDX :
			knh_VirtualMachineCode_RET__OIDX__dump(ctx, (knh_asmc_ret_oidx_t*)pc, off, w, m);
			pc += KNH_ASMC_RET_OIDX_SIZ;
			break;
		case ASMC_MOVE__EBP :
			knh_VirtualMachineCode_MOVE__ebp__dump(ctx, (knh_asmc_move_ebp_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVE_ebp_SIZ;
			break;
		case ASMC_MOVE__SFP :
			knh_VirtualMachineCode_MOVE__sfp__dump(ctx, (knh_asmc_move_sfp_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVE_sfp_SIZ;
			break;
		case ASMC_MOVE__OFP :
			knh_VirtualMachineCode_MOVE__ofp__dump(ctx, (knh_asmc_move_ofp_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVE_ofp_SIZ;
			break;
		case ASMC_MOVE__OBJ :
			knh_VirtualMachineCode_MOVE__OBJ__dump(ctx, (knh_asmc_move_obj_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVE_OBJ_SIZ;
			break;
		case ASMC_MOVE__OIDX :
			knh_VirtualMachineCode_MOVE__OIDX__dump(ctx, (knh_asmc_move_oidx_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVE_OIDX_SIZ;
			break;
		case ASMC_MOVS__EBP :
			knh_VirtualMachineCode_MOVS__ebp__dump(ctx, (knh_asmc_movs_ebp_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVS_ebp_SIZ;
			break;
		case ASMC_MOVS__SFP :
			knh_VirtualMachineCode_MOVS__sfp__dump(ctx, (knh_asmc_movs_sfp_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVS_sfp_SIZ;
			break;
		case ASMC_MOVS__OFP :
			knh_VirtualMachineCode_MOVS__ofp__dump(ctx, (knh_asmc_movs_ofp_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVS_ofp_SIZ;
			break;
		case ASMC_MOVS__OBJ :
			knh_VirtualMachineCode_MOVS__OBJ__dump(ctx, (knh_asmc_movs_obj_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVS_OBJ_SIZ;
			break;
		case ASMC_MOVS__OIDX :
			knh_VirtualMachineCode_MOVS__OIDX__dump(ctx, (knh_asmc_movs_oidx_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVS_OIDX_SIZ;
			break;
		case ASMC_MOVO__EBP :
			knh_VirtualMachineCode_MOVO__ebp__dump(ctx, (knh_asmc_movo_ebp_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVO_ebp_SIZ;
			break;
		case ASMC_MOVO__SFP :
			knh_VirtualMachineCode_MOVO__sfp__dump(ctx, (knh_asmc_movo_sfp_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVO_sfp_SIZ;
			break;
		case ASMC_MOVO__OFP :
			knh_VirtualMachineCode_MOVO__ofp__dump(ctx, (knh_asmc_movo_ofp_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVO_ofp_SIZ;
			break;
		case ASMC_MOVO__OBJ :
			knh_VirtualMachineCode_MOVO__OBJ__dump(ctx, (knh_asmc_movo_obj_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVO_OBJ_SIZ;
			break;
		case ASMC_MOVO__OIDX :
			knh_VirtualMachineCode_MOVO__OIDX__dump(ctx, (knh_asmc_movo_oidx_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVO_OIDX_SIZ;
			break;
		case ASMC_MOVOI__EBP :
			knh_VirtualMachineCode_MOVOI__ebp__dump(ctx, (knh_asmc_movoi_ebp_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVOI_ebp_SIZ;
			break;
		case ASMC_MOVOI__SFP :
			knh_VirtualMachineCode_MOVOI__sfp__dump(ctx, (knh_asmc_movoi_sfp_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVOI_sfp_SIZ;
			break;
		case ASMC_MOVOI__OFP :
			knh_VirtualMachineCode_MOVOI__ofp__dump(ctx, (knh_asmc_movoi_ofp_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVOI_ofp_SIZ;
			break;
		case ASMC_MOVOI__OBJ :
			knh_VirtualMachineCode_MOVOI__OBJ__dump(ctx, (knh_asmc_movoi_obj_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVOI_OBJ_SIZ;
			break;
		case ASMC_MOVOI__OIDX :
			knh_VirtualMachineCode_MOVOI__OIDX__dump(ctx, (knh_asmc_movoi_oidx_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVOI_OIDX_SIZ;
			break;
		case ASMC_MOVSFP_IFNUL :
			knh_VirtualMachineCode_MOVSFP_IFNUL__dump(ctx, (knh_asmc_movsfp_ifnul_t*)pc, off, w, m);
			pc += KNH_ASMC_MOVSFP_IFNUL_SIZ;
			break;
		case ASMC_PUSH__SFP :
			knh_VirtualMachineCode_PUSH__sfp__dump(ctx, (knh_asmc_push_sfp_t*)pc, off, w, m);
			pc += KNH_ASMC_PUSH_sfp_SIZ;
			break;
		case ASMC_PUSH__OFP :
			knh_VirtualMachineCode_PUSH__ofp__dump(ctx, (knh_asmc_push_ofp_t*)pc, off, w, m);
			pc += KNH_ASMC_PUSH_ofp_SIZ;
			break;
		case ASMC_PUSH__OBJ :
			knh_VirtualMachineCode_PUSH__OBJ__dump(ctx, (knh_asmc_push_obj_t*)pc, off, w, m);
			pc += KNH_ASMC_PUSH_OBJ_SIZ;
			break;
		case ASMC_PUSH__OIDX :
			knh_VirtualMachineCode_PUSH__OIDX__dump(ctx, (knh_asmc_push_oidx_t*)pc, off, w, m);
			pc += KNH_ASMC_PUSH_OIDX_SIZ;
			break;
		case ASMC_PUTI :
			knh_VirtualMachineCode_PUTI__dump(ctx, (knh_asmc_puti_t*)pc, off, w, m);
			pc += KNH_ASMC_PUTI_SIZ;
			break;
		case ASMC_PUSH__MN :
			knh_VirtualMachineCode_PUSH__MN__dump(ctx, (knh_asmc_push_mn_t*)pc, off, w, m);
			pc += KNH_ASMC_PUSH_MN_SIZ;
			break;
		case ASMC_PUSH__DEF :
			knh_VirtualMachineCode_PUSH__DEF__dump(ctx, (knh_asmc_push_def_t*)pc, off, w, m);
			pc += KNH_ASMC_PUSH_DEF_SIZ;
			break;
		case ASMC_VARGS :
			knh_VirtualMachineCode_VARGS__dump(ctx, (knh_asmc_vargs_t*)pc, off, w, m);
			pc += KNH_ASMC_VARGS_SIZ;
			break;
		case ASMC_SCALL :
			knh_VirtualMachineCode_SCALL__dump(ctx, (knh_asmc_scall_t*)pc, off, w, m);
			pc += KNH_ASMC_SCALL_SIZ;
			break;
		case ASMC_CALL :
			knh_VirtualMachineCode_CALL__dump(ctx, (knh_asmc_call_t*)pc, off, w, m);
			pc += KNH_ASMC_CALL_SIZ;
			break;
		case ASMC_DCALL :
			knh_VirtualMachineCode_DCALL__dump(ctx, (knh_asmc_dcall_t*)pc, off, w, m);
			pc += KNH_ASMC_DCALL_SIZ;
			break;
		case ASMC_MCALL :
			knh_VirtualMachineCode_MCALL__dump(ctx, (knh_asmc_mcall_t*)pc, off, w, m);
			pc += KNH_ASMC_MCALL_SIZ;
			break;
		case ASMC_CALL_WM :
			knh_VirtualMachineCode_CALL_WM__dump(ctx, (knh_asmc_call_wm_t*)pc, off, w, m);
			pc += KNH_ASMC_CALL_WM_SIZ;
			break;
		case ASMC_NCALL_WM :
			knh_VirtualMachineCode_NCALL_WM__dump(ctx, (knh_asmc_ncall_wm_t*)pc, off, w, m);
			pc += KNH_ASMC_NCALL_WM_SIZ;
			break;
		case ASMC_NEW :
			knh_VirtualMachineCode_NEW__dump(ctx, (knh_asmc_new_t*)pc, off, w, m);
			pc += KNH_ASMC_NEW_SIZ;
			break;
		case ASMC_NEWE :
			knh_VirtualMachineCode_NEWE__dump(ctx, (knh_asmc_newe_t*)pc, off, w, m);
			pc += KNH_ASMC_NEWE_SIZ;
			break;
		case ASMC_NEW__DEF :
			knh_VirtualMachineCode_NEW__DEF__dump(ctx, (knh_asmc_new_def_t*)pc, off, w, m);
			pc += KNH_ASMC_NEW_DEF_SIZ;
			break;
		case ASMC_MT :
			knh_VirtualMachineCode_MT__dump(ctx, (knh_asmc_mt_t*)pc, off, w, m);
			pc += KNH_ASMC_MT_SIZ;
			break;
		case ASMC_MT__OPT :
			knh_VirtualMachineCode_MT__OPT__dump(ctx, (knh_asmc_mt_opt_t*)pc, off, w, m);
			pc += KNH_ASMC_MT_OPT_SIZ;
			break;
		case ASMC_MAP :
			knh_VirtualMachineCode_MAP__dump(ctx, (knh_asmc_map_t*)pc, off, w, m);
			pc += KNH_ASMC_MAP_SIZ;
			break;
		case ASMC_MAPE :
			knh_VirtualMachineCode_MAPE__dump(ctx, (knh_asmc_mape_t*)pc, off, w, m);
			pc += KNH_ASMC_MAPE_SIZ;
			break;
		case ASMC_MAP_WM :
			knh_VirtualMachineCode_MAP_WM__dump(ctx, (knh_asmc_map_wm_t*)pc, off, w, m);
			pc += KNH_ASMC_MAP_WM_SIZ;
			break;
		case ASMC_MAPE_WM :
			knh_VirtualMachineCode_MAPE_WM__dump(ctx, (knh_asmc_mape_wm_t*)pc, off, w, m);
			pc += KNH_ASMC_MAPE_WM_SIZ;
			break;
		case ASMC_MAP2 :
			knh_VirtualMachineCode_MAP2__dump(ctx, (knh_asmc_map2_t*)pc, off, w, m);
			pc += KNH_ASMC_MAP2_SIZ;
			break;
		case ASMC_MAP2E :
			knh_VirtualMachineCode_MAP2E__dump(ctx, (knh_asmc_map2e_t*)pc, off, w, m);
			pc += KNH_ASMC_MAP2E_SIZ;
			break;
		case ASMC_TYPECHK__EBP :
			knh_VirtualMachineCode_TYPECHK__ebp__dump(ctx, (knh_asmc_typechk_ebp_t*)pc, off, w, m);
			pc += KNH_ASMC_TYPECHK_ebp_SIZ;
			break;
		case ASMC_TYPECHK__SFP :
			knh_VirtualMachineCode_TYPECHK__sfp__dump(ctx, (knh_asmc_typechk_sfp_t*)pc, off, w, m);
			pc += KNH_ASMC_TYPECHK_sfp_SIZ;
			break;
		case ASMC_TYPECHK__OFP :
			knh_VirtualMachineCode_TYPECHK__ofp__dump(ctx, (knh_asmc_typechk_ofp_t*)pc, off, w, m);
			pc += KNH_ASMC_TYPECHK_ofp_SIZ;
			break;
		case ASMC_TYPECHK__OBJ :
			knh_VirtualMachineCode_TYPECHK__OBJ__dump(ctx, (knh_asmc_typechk_obj_t*)pc, off, w, m);
			pc += KNH_ASMC_TYPECHK_OBJ_SIZ;
			break;
		case ASMC_TYPECHK__OIDX :
			knh_VirtualMachineCode_TYPECHK__OIDX__dump(ctx, (knh_asmc_typechk_oidx_t*)pc, off, w, m);
			pc += KNH_ASMC_TYPECHK_OIDX_SIZ;
			break;
		case ASMC_NULLCHK__EBP :
			knh_VirtualMachineCode_NULLCHK__ebp__dump(ctx, (knh_asmc_nullchk_ebp_t*)pc, off, w, m);
			pc += KNH_ASMC_NULLCHK_ebp_SIZ;
			break;
		case ASMC_NULLCHK__SFP :
			knh_VirtualMachineCode_NULLCHK__sfp__dump(ctx, (knh_asmc_nullchk_sfp_t*)pc, off, w, m);
			pc += KNH_ASMC_NULLCHK_sfp_SIZ;
			break;
		case ASMC_NULLCHK__OFP :
			knh_VirtualMachineCode_NULLCHK__ofp__dump(ctx, (knh_asmc_nullchk_ofp_t*)pc, off, w, m);
			pc += KNH_ASMC_NULLCHK_ofp_SIZ;
			break;
		case ASMC_NULLCHK__OBJ :
			knh_VirtualMachineCode_NULLCHK__OBJ__dump(ctx, (knh_asmc_nullchk_obj_t*)pc, off, w, m);
			pc += KNH_ASMC_NULLCHK_OBJ_SIZ;
			break;
		case ASMC_NULLCHK__OIDX :
			knh_VirtualMachineCode_NULLCHK__OIDX__dump(ctx, (knh_asmc_nullchk_oidx_t*)pc, off, w, m);
			pc += KNH_ASMC_NULLCHK_OIDX_SIZ;
			break;
		case ASMC_JMP :
			knh_VirtualMachineCode_JMP__dump(ctx, (knh_asmc_jmp_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_SIZ;
			break;
		case ASMC_SKIP :
			knh_VirtualMachineCode_SKIP__dump(ctx, (knh_asmc_skip_t*)pc, off, w, m);
			pc += KNH_ASMC_SKIP_SIZ;
			break;
		case ASMC_JMP_IFT__EBP :
			knh_VirtualMachineCode_JMP_IFT__ebp__dump(ctx, (knh_asmc_jmp_ift_ebp_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_IFT_ebp_SIZ;
			break;
		case ASMC_JMP_IFT__SFP :
			knh_VirtualMachineCode_JMP_IFT__sfp__dump(ctx, (knh_asmc_jmp_ift_sfp_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_IFT_sfp_SIZ;
			break;
		case ASMC_JMP_IFT__OFP :
			knh_VirtualMachineCode_JMP_IFT__ofp__dump(ctx, (knh_asmc_jmp_ift_ofp_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_IFT_ofp_SIZ;
			break;
		case ASMC_JMP_IFT__OIDX :
			knh_VirtualMachineCode_JMP_IFT__OIDX__dump(ctx, (knh_asmc_jmp_ift_oidx_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_IFT_OIDX_SIZ;
			break;
		case ASMC_JMP_IFF__EBP :
			knh_VirtualMachineCode_JMP_IFF__ebp__dump(ctx, (knh_asmc_jmp_iff_ebp_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_IFF_ebp_SIZ;
			break;
		case ASMC_JMP_IFF__SFP :
			knh_VirtualMachineCode_JMP_IFF__sfp__dump(ctx, (knh_asmc_jmp_iff_sfp_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_IFF_sfp_SIZ;
			break;
		case ASMC_JMP_IFF__OFP :
			knh_VirtualMachineCode_JMP_IFF__ofp__dump(ctx, (knh_asmc_jmp_iff_ofp_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_IFF_ofp_SIZ;
			break;
		case ASMC_JMP_IFF__OIDX :
			knh_VirtualMachineCode_JMP_IFF__OIDX__dump(ctx, (knh_asmc_jmp_iff_oidx_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_IFF_OIDX_SIZ;
			break;
		case ASMC_JMP_IFNUL__EBP :
			knh_VirtualMachineCode_JMP_IFNUL__ebp__dump(ctx, (knh_asmc_jmp_ifnul_ebp_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_IFNUL_ebp_SIZ;
			break;
		case ASMC_JMP_IFNUL__SFP :
			knh_VirtualMachineCode_JMP_IFNUL__sfp__dump(ctx, (knh_asmc_jmp_ifnul_sfp_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_IFNUL_sfp_SIZ;
			break;
		case ASMC_JMP_IFNUL__OFP :
			knh_VirtualMachineCode_JMP_IFNUL__ofp__dump(ctx, (knh_asmc_jmp_ifnul_ofp_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_IFNUL_ofp_SIZ;
			break;
		case ASMC_JMP_IFNUL__OIDX :
			knh_VirtualMachineCode_JMP_IFNUL__OIDX__dump(ctx, (knh_asmc_jmp_ifnul_oidx_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_IFNUL_OIDX_SIZ;
			break;
		case ASMC_JMP_IFNONUL__EBP :
			knh_VirtualMachineCode_JMP_IFNONUL__ebp__dump(ctx, (knh_asmc_jmp_ifnonul_ebp_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_IFNONUL_ebp_SIZ;
			break;
		case ASMC_JMP_IFNONUL__SFP :
			knh_VirtualMachineCode_JMP_IFNONUL__sfp__dump(ctx, (knh_asmc_jmp_ifnonul_sfp_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_IFNONUL_sfp_SIZ;
			break;
		case ASMC_JMP_IFNONUL__OFP :
			knh_VirtualMachineCode_JMP_IFNONUL__ofp__dump(ctx, (knh_asmc_jmp_ifnonul_ofp_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_IFNONUL_ofp_SIZ;
			break;
		case ASMC_JMP_IFNONUL__OIDX :
			knh_VirtualMachineCode_JMP_IFNONUL__OIDX__dump(ctx, (knh_asmc_jmp_ifnonul_oidx_t*)pc, off, w, m);
			pc += KNH_ASMC_JMP_IFNONUL_OIDX_SIZ;
			break;
		case ASMC_ITER :
			knh_VirtualMachineCode_ITER__dump(ctx, (knh_asmc_iter_t*)pc, off, w, m);
			pc += KNH_ASMC_ITER_SIZ;
			break;
		case ASMC_FOREACH :
			knh_VirtualMachineCode_FOREACH__dump(ctx, (knh_asmc_foreach_t*)pc, off, w, m);
			pc += KNH_ASMC_FOREACH_SIZ;
			break;
		case ASMC_TRY_BEGIN :
			knh_VirtualMachineCode_TRY_BEGIN__dump(ctx, (knh_asmc_try_begin_t*)pc, off, w, m);
			pc += KNH_ASMC_TRY_BEGIN_SIZ;
			break;
		case ASMC_TRY_END :
			knh_VirtualMachineCode_TRY_END__dump(ctx, (knh_asmc_try_end_t*)pc, off, w, m);
			pc += KNH_ASMC_TRY_END_SIZ;
			break;
		case ASMC_CATCH :
			knh_VirtualMachineCode_CATCH__dump(ctx, (knh_asmc_catch_t*)pc, off, w, m);
			pc += KNH_ASMC_CATCH_SIZ;
			break;
		case ASMC_THROW__EBP :
			knh_VirtualMachineCode_THROW__ebp__dump(ctx, (knh_asmc_throw_ebp_t*)pc, off, w, m);
			pc += KNH_ASMC_THROW_ebp_SIZ;
			break;
		case ASMC_THROW__SFP :
			knh_VirtualMachineCode_THROW__sfp__dump(ctx, (knh_asmc_throw_sfp_t*)pc, off, w, m);
			pc += KNH_ASMC_THROW_sfp_SIZ;
			break;
		case ASMC_THROW__OBJ :
			knh_VirtualMachineCode_THROW__OBJ__dump(ctx, (knh_asmc_throw_obj_t*)pc, off, w, m);
			pc += KNH_ASMC_THROW_OBJ_SIZ;
			break;
		case ASMC_PRINT__EBP :
			knh_VirtualMachineCode_PRINT__ebp__dump(ctx, (knh_asmc_print_ebp_t*)pc, off, w, m);
			pc += KNH_ASMC_PRINT_ebp_SIZ;
			break;
		case ASMC_PRINT__SFP :
			knh_VirtualMachineCode_PRINT__sfp__dump(ctx, (knh_asmc_print_sfp_t*)pc, off, w, m);
			pc += KNH_ASMC_PRINT_sfp_SIZ;
			break;
		case ASMC_PRINT__OFP :
			knh_VirtualMachineCode_PRINT__ofp__dump(ctx, (knh_asmc_print_ofp_t*)pc, off, w, m);
			pc += KNH_ASMC_PRINT_ofp_SIZ;
			break;
		case ASMC_PRINT__OBJ :
			knh_VirtualMachineCode_PRINT__OBJ__dump(ctx, (knh_asmc_print_obj_t*)pc, off, w, m);
			pc += KNH_ASMC_PRINT_OBJ_SIZ;
			break;
		case ASMC_PRINT__OIDX :
			knh_VirtualMachineCode_PRINT__OIDX__dump(ctx, (knh_asmc_print_oidx_t*)pc, off, w, m);
			pc += KNH_ASMC_PRINT_OIDX_SIZ;
			break;
		case ASMC_DIAGNOSE :
			knh_VirtualMachineCode_DIAGNOSE__dump(ctx, (knh_asmc_diagnose_t*)pc, off, w, m);
			pc += KNH_ASMC_DIAGNOSE_SIZ;
			break;
		case ASMC_STACKDUMP :
			knh_VirtualMachineCode_STACKDUMP__dump(ctx, (knh_asmc_stackdump_t*)pc, off, w, m);
			pc += KNH_ASMC_STACKDUMP_SIZ;
			break;
		case ASMC_NOP :
			knh_VirtualMachineCode_NOP__dump(ctx, (knh_asmc_nop_t*)pc, off, w, m);
			pc += KNH_ASMC_NOP_SIZ;
			break;

		default :
			DEBUG("UNKNOWN VMCODE: %d\n", PCT_(pc));
			DEBUG_ASSERT(ctx == NULL);
			return;
		}
	}
}

/* ------------------------------------------------------------------------ */


/* ======================================================================== */
/* [exec] */

PUBLIC
void knh_VirtualMachineCode_exec0(Ctx *ctx, Object **sfp)
{
	register knh_vmc_t *pc = ((VirtualMachineCode*)((Method*)sfp[-1])->code)->code;
	L_HEAD:;
	switch(PCT_(pc)) {
	case ASMC_RET_VOID :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_RET_VOID__dump(ctx, (knh_asmc_ret_void_t*)pc, 0, StdOut);
#endif
#ifdef VM_RET_VOID
		VM_RET_VOID(ctx);
#else
		DEBUG("TODO: VM_RET_VOID");
#endif
		pc += KNH_ASMC_RET_VOID_SIZ;
		break;
	case ASMC_RET__EBP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_RET__EBP__dump(ctx, (knh_asmc_ret_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_RET
		VM_RET(ctx, ebp_(((knh_asmc_ret_ebp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_RET");
#endif
		pc += KNH_ASMC_RET_ebp_SIZ;
		break;
	case ASMC_RET__SFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_RET__SFP__dump(ctx, (knh_asmc_ret_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_RET
		VM_RET(ctx, sfp_(((knh_asmc_ret_sfp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_RET");
#endif
		pc += KNH_ASMC_RET_sfp_SIZ;
		break;
	case ASMC_RET__OFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_RET__OFP__dump(ctx, (knh_asmc_ret_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_RET
		VM_RET(ctx, ofp_(((knh_asmc_ret_ofp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_RET");
#endif
		pc += KNH_ASMC_RET_ofp_SIZ;
		break;
	case ASMC_RET__OBJ :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_RET__OBJ__dump(ctx, (knh_asmc_ret_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_RET
		VM_RET(ctx, OBJ_(((knh_asmc_ret_obj_t*)pc)->a1));
#else
		DEBUG("TODO: VM_RET");
#endif
		pc += KNH_ASMC_RET_OBJ_SIZ;
		break;
	case ASMC_RET__OIDX :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_RET__OIDX__dump(ctx, (knh_asmc_ret_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_RET__OIDX
		VM_RET__OIDX(ctx, OBJ_(((knh_asmc_ret_oidx_t*)pc)->a1), u1_(((knh_asmc_ret_oidx_t*)pc)->a2));
#else
		DEBUG("TODO: VM_RET__OIDX");
#endif
		pc += KNH_ASMC_RET_OIDX_SIZ;
		break;
	case ASMC_MOVE__EBP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVE__EBP__dump(ctx, (knh_asmc_move_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVE
		VM_MOVE(ctx, ebp_(((knh_asmc_move_ebp_t*)pc)->a1), ebp_(((knh_asmc_move_ebp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVE");
#endif
		pc += KNH_ASMC_MOVE_ebp_SIZ;
		break;
	case ASMC_MOVE__SFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVE__SFP__dump(ctx, (knh_asmc_move_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVE
		VM_MOVE(ctx, ebp_(((knh_asmc_move_sfp_t*)pc)->a1), sfp_(((knh_asmc_move_sfp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVE");
#endif
		pc += KNH_ASMC_MOVE_sfp_SIZ;
		break;
	case ASMC_MOVE__OFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVE__OFP__dump(ctx, (knh_asmc_move_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVE
		VM_MOVE(ctx, ebp_(((knh_asmc_move_ofp_t*)pc)->a1), ofp_(((knh_asmc_move_ofp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVE");
#endif
		pc += KNH_ASMC_MOVE_ofp_SIZ;
		break;
	case ASMC_MOVE__OBJ :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVE__OBJ__dump(ctx, (knh_asmc_move_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVE
		VM_MOVE(ctx, ebp_(((knh_asmc_move_obj_t*)pc)->a1), OBJ_(((knh_asmc_move_obj_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVE");
#endif
		pc += KNH_ASMC_MOVE_OBJ_SIZ;
		break;
	case ASMC_MOVE__OIDX :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVE__OIDX__dump(ctx, (knh_asmc_move_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVE__OIDX
		VM_MOVE__OIDX(ctx, ebp_(((knh_asmc_move_oidx_t*)pc)->a1), OBJ_(((knh_asmc_move_oidx_t*)pc)->a2), u1_(((knh_asmc_move_oidx_t*)pc)->a3));
#else
		DEBUG("TODO: VM_MOVE__OIDX");
#endif
		pc += KNH_ASMC_MOVE_OIDX_SIZ;
		break;
	case ASMC_MOVS__EBP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVS__EBP__dump(ctx, (knh_asmc_movs_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVS
		VM_MOVS(ctx, sfp_(((knh_asmc_movs_ebp_t*)pc)->a1), ebp_(((knh_asmc_movs_ebp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVS");
#endif
		pc += KNH_ASMC_MOVS_ebp_SIZ;
		break;
	case ASMC_MOVS__SFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVS__SFP__dump(ctx, (knh_asmc_movs_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVS
		VM_MOVS(ctx, sfp_(((knh_asmc_movs_sfp_t*)pc)->a1), sfp_(((knh_asmc_movs_sfp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVS");
#endif
		pc += KNH_ASMC_MOVS_sfp_SIZ;
		break;
	case ASMC_MOVS__OFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVS__OFP__dump(ctx, (knh_asmc_movs_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVS
		VM_MOVS(ctx, sfp_(((knh_asmc_movs_ofp_t*)pc)->a1), ofp_(((knh_asmc_movs_ofp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVS");
#endif
		pc += KNH_ASMC_MOVS_ofp_SIZ;
		break;
	case ASMC_MOVS__OBJ :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVS__OBJ__dump(ctx, (knh_asmc_movs_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVS
		VM_MOVS(ctx, sfp_(((knh_asmc_movs_obj_t*)pc)->a1), OBJ_(((knh_asmc_movs_obj_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVS");
#endif
		pc += KNH_ASMC_MOVS_OBJ_SIZ;
		break;
	case ASMC_MOVS__OIDX :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVS__OIDX__dump(ctx, (knh_asmc_movs_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVS__OIDX
		VM_MOVS__OIDX(ctx, sfp_(((knh_asmc_movs_oidx_t*)pc)->a1), OBJ_(((knh_asmc_movs_oidx_t*)pc)->a2), u1_(((knh_asmc_movs_oidx_t*)pc)->a3));
#else
		DEBUG("TODO: VM_MOVS__OIDX");
#endif
		pc += KNH_ASMC_MOVS_OIDX_SIZ;
		break;
	case ASMC_MOVO__EBP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVO__EBP__dump(ctx, (knh_asmc_movo_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVO
		VM_MOVO(ctx, ofp_(((knh_asmc_movo_ebp_t*)pc)->a1), ebp_(((knh_asmc_movo_ebp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVO");
#endif
		pc += KNH_ASMC_MOVO_ebp_SIZ;
		break;
	case ASMC_MOVO__SFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVO__SFP__dump(ctx, (knh_asmc_movo_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVO
		VM_MOVO(ctx, ofp_(((knh_asmc_movo_sfp_t*)pc)->a1), sfp_(((knh_asmc_movo_sfp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVO");
#endif
		pc += KNH_ASMC_MOVO_sfp_SIZ;
		break;
	case ASMC_MOVO__OFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVO__OFP__dump(ctx, (knh_asmc_movo_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVO
		VM_MOVO(ctx, ofp_(((knh_asmc_movo_ofp_t*)pc)->a1), ofp_(((knh_asmc_movo_ofp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVO");
#endif
		pc += KNH_ASMC_MOVO_ofp_SIZ;
		break;
	case ASMC_MOVO__OBJ :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVO__OBJ__dump(ctx, (knh_asmc_movo_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVO
		VM_MOVO(ctx, ofp_(((knh_asmc_movo_obj_t*)pc)->a1), OBJ_(((knh_asmc_movo_obj_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVO");
#endif
		pc += KNH_ASMC_MOVO_OBJ_SIZ;
		break;
	case ASMC_MOVO__OIDX :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVO__OIDX__dump(ctx, (knh_asmc_movo_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVO__OIDX
		VM_MOVO__OIDX(ctx, ofp_(((knh_asmc_movo_oidx_t*)pc)->a1), OBJ_(((knh_asmc_movo_oidx_t*)pc)->a2), u1_(((knh_asmc_movo_oidx_t*)pc)->a3));
#else
		DEBUG("TODO: VM_MOVO__OIDX");
#endif
		pc += KNH_ASMC_MOVO_OIDX_SIZ;
		break;
	case ASMC_MOVOI__EBP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVOI__EBP__dump(ctx, (knh_asmc_movoi_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVOI
		VM_MOVOI(ctx, OBJ_(((knh_asmc_movoi_ebp_t*)pc)->a1), ofp_(((knh_asmc_movoi_ebp_t*)pc)->a2), ebp_(((knh_asmc_movoi_ebp_t*)pc)->a3));
#else
		DEBUG("TODO: VM_MOVOI");
#endif
		pc += KNH_ASMC_MOVOI_ebp_SIZ;
		break;
	case ASMC_MOVOI__SFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVOI__SFP__dump(ctx, (knh_asmc_movoi_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVOI
		VM_MOVOI(ctx, OBJ_(((knh_asmc_movoi_sfp_t*)pc)->a1), ofp_(((knh_asmc_movoi_sfp_t*)pc)->a2), sfp_(((knh_asmc_movoi_sfp_t*)pc)->a3));
#else
		DEBUG("TODO: VM_MOVOI");
#endif
		pc += KNH_ASMC_MOVOI_sfp_SIZ;
		break;
	case ASMC_MOVOI__OFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVOI__OFP__dump(ctx, (knh_asmc_movoi_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVOI
		VM_MOVOI(ctx, OBJ_(((knh_asmc_movoi_ofp_t*)pc)->a1), ofp_(((knh_asmc_movoi_ofp_t*)pc)->a2), ofp_(((knh_asmc_movoi_ofp_t*)pc)->a3));
#else
		DEBUG("TODO: VM_MOVOI");
#endif
		pc += KNH_ASMC_MOVOI_ofp_SIZ;
		break;
	case ASMC_MOVOI__OBJ :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVOI__OBJ__dump(ctx, (knh_asmc_movoi_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVOI
		VM_MOVOI(ctx, OBJ_(((knh_asmc_movoi_obj_t*)pc)->a1), ofp_(((knh_asmc_movoi_obj_t*)pc)->a2), OBJ_(((knh_asmc_movoi_obj_t*)pc)->a3));
#else
		DEBUG("TODO: VM_MOVOI");
#endif
		pc += KNH_ASMC_MOVOI_OBJ_SIZ;
		break;
	case ASMC_MOVOI__OIDX :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVOI__OIDX__dump(ctx, (knh_asmc_movoi_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVOI__OIDX
		VM_MOVOI__OIDX(ctx, OBJ_(((knh_asmc_movoi_oidx_t*)pc)->a1), u1_(((knh_asmc_movoi_oidx_t*)pc)->a2), OBJ_(((knh_asmc_movoi_oidx_t*)pc)->a3), u1_(((knh_asmc_movoi_oidx_t*)pc)->a4));
#else
		DEBUG("TODO: VM_MOVOI__OIDX");
#endif
		pc += KNH_ASMC_MOVOI_OIDX_SIZ;
		break;
	case ASMC_MOVSFP_IFNUL :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MOVSFP_IFNUL__dump(ctx, (knh_asmc_movsfp_ifnul_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVSFP_IFNUL
		VM_MOVSFP_IFNUL(ctx, u1_(((knh_asmc_movsfp_ifnul_t*)pc)->a1), OBJ_(((knh_asmc_movsfp_ifnul_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVSFP_IFNUL");
#endif
		pc += KNH_ASMC_MOVSFP_IFNUL_SIZ;
		break;
	case ASMC_PUSH__SFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_PUSH__SFP__dump(ctx, (knh_asmc_push_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_PUSH
		VM_PUSH(ctx, sfp_(((knh_asmc_push_sfp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_PUSH");
#endif
		pc += KNH_ASMC_PUSH_sfp_SIZ;
		break;
	case ASMC_PUSH__OFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_PUSH__OFP__dump(ctx, (knh_asmc_push_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_PUSH
		VM_PUSH(ctx, ofp_(((knh_asmc_push_ofp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_PUSH");
#endif
		pc += KNH_ASMC_PUSH_ofp_SIZ;
		break;
	case ASMC_PUSH__OBJ :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_PUSH__OBJ__dump(ctx, (knh_asmc_push_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_PUSH
		VM_PUSH(ctx, OBJ_(((knh_asmc_push_obj_t*)pc)->a1));
#else
		DEBUG("TODO: VM_PUSH");
#endif
		pc += KNH_ASMC_PUSH_OBJ_SIZ;
		break;
	case ASMC_PUSH__OIDX :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_PUSH__OIDX__dump(ctx, (knh_asmc_push_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_PUSH__OIDX
		VM_PUSH__OIDX(ctx, OBJ_(((knh_asmc_push_oidx_t*)pc)->a1), u1_(((knh_asmc_push_oidx_t*)pc)->a2));
#else
		DEBUG("TODO: VM_PUSH__OIDX");
#endif
		pc += KNH_ASMC_PUSH_OIDX_SIZ;
		break;
	case ASMC_PUTI :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_PUTI__dump(ctx, (knh_asmc_puti_t*)pc, 0, StdOut);
#endif
#ifdef VM_PUTI
		VM_PUTI(ctx, u2_(((knh_asmc_puti_t*)pc)->a1));
#else
		DEBUG("TODO: VM_PUTI");
#endif
		pc += KNH_ASMC_PUTI_SIZ;
		break;
	case ASMC_PUSH__MN :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_PUSH__MN__dump(ctx, (knh_asmc_push_mn_t*)pc, 0, StdOut);
#endif
#ifdef VM_PUSH__MN
		VM_PUSH__MN(ctx, mn_(((knh_asmc_push_mn_t*)pc)->a1));
#else
		DEBUG("TODO: VM_PUSH__MN");
#endif
		pc += KNH_ASMC_PUSH_MN_SIZ;
		break;
	case ASMC_PUSH__DEF :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_PUSH__DEF__dump(ctx, (knh_asmc_push_def_t*)pc, 0, StdOut);
#endif
#ifdef VM_PUSH__DEF
		VM_PUSH__DEF(ctx, c2_(((knh_asmc_push_def_t*)pc)->a1));
#else
		DEBUG("TODO: VM_PUSH__DEF");
#endif
		pc += KNH_ASMC_PUSH_DEF_SIZ;
		break;
	case ASMC_VARGS :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_VARGS__dump(ctx, (knh_asmc_vargs_t*)pc, 0, StdOut);
#endif
#ifdef VM_VARGS
		VM_VARGS(ctx, u2_(((knh_asmc_vargs_t*)pc)->a1));
#else
		DEBUG("TODO: VM_VARGS");
#endif
		pc += KNH_ASMC_VARGS_SIZ;
		break;
	case ASMC_SCALL :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_SCALL__dump(ctx, (knh_asmc_scall_t*)pc, 0, StdOut);
#endif
#ifdef VM_SCALL
		VM_SCALL(ctx, u1_(((knh_asmc_scall_t*)pc)->a1));
#else
		DEBUG("TODO: VM_SCALL");
#endif
		pc += KNH_ASMC_SCALL_SIZ;
		break;
	case ASMC_CALL :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_CALL__dump(ctx, (knh_asmc_call_t*)pc, 0, StdOut);
#endif
#ifdef VM_CALL
		VM_CALL(ctx, u1_(((knh_asmc_call_t*)pc)->a1));
#else
		DEBUG("TODO: VM_CALL");
#endif
		pc += KNH_ASMC_CALL_SIZ;
		break;
	case ASMC_DCALL :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_DCALL__dump(ctx, (knh_asmc_dcall_t*)pc, 0, StdOut);
#endif
#ifdef VM_DCALL
		VM_DCALL(ctx, u1_(((knh_asmc_dcall_t*)pc)->a1));
#else
		DEBUG("TODO: VM_DCALL");
#endif
		pc += KNH_ASMC_DCALL_SIZ;
		break;
	case ASMC_MCALL :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MCALL__dump(ctx, (knh_asmc_mcall_t*)pc, 0, StdOut);
#endif
#ifdef VM_MCALL
		VM_MCALL(ctx, u1_(((knh_asmc_mcall_t*)pc)->a1));
#else
		DEBUG("TODO: VM_MCALL");
#endif
		pc += KNH_ASMC_MCALL_SIZ;
		break;
	case ASMC_CALL_WM :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_CALL_WM__dump(ctx, (knh_asmc_call_wm_t*)pc, 0, StdOut);
#endif
#ifdef VM_CALL_WM
		VM_CALL_WM(ctx, u1_(((knh_asmc_call_wm_t*)pc)->a1), OBJ_(((knh_asmc_call_wm_t*)pc)->a2));
#else
		DEBUG("TODO: VM_CALL_WM");
#endif
		pc += KNH_ASMC_CALL_WM_SIZ;
		break;
	case ASMC_NCALL_WM :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_NCALL_WM__dump(ctx, (knh_asmc_ncall_wm_t*)pc, 0, StdOut);
#endif
#ifdef VM_NCALL_WM
		VM_NCALL_WM(ctx, u1_(((knh_asmc_ncall_wm_t*)pc)->a1), OBJ_(((knh_asmc_ncall_wm_t*)pc)->a2));
#else
		DEBUG("TODO: VM_NCALL_WM");
#endif
		pc += KNH_ASMC_NCALL_WM_SIZ;
		break;
	case ASMC_NEW :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_NEW__dump(ctx, (knh_asmc_new_t*)pc, 0, StdOut);
#endif
#ifdef VM_NEW
		VM_NEW(ctx, u2_(((knh_asmc_new_t*)pc)->a1), OBJ_(((knh_asmc_new_t*)pc)->a2), u2_(((knh_asmc_new_t*)pc)->a3), c2_(((knh_asmc_new_t*)pc)->a4));
#else
		DEBUG("TODO: VM_NEW");
#endif
		pc += KNH_ASMC_NEW_SIZ;
		break;
	case ASMC_NEWE :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_NEWE__dump(ctx, (knh_asmc_newe_t*)pc, 0, StdOut);
#endif
#ifdef VM_NEWE
		VM_NEWE(ctx, u2_(((knh_asmc_newe_t*)pc)->a1), OBJ_(((knh_asmc_newe_t*)pc)->a2), u2_(((knh_asmc_newe_t*)pc)->a3), c2_(((knh_asmc_newe_t*)pc)->a4));
#else
		DEBUG("TODO: VM_NEWE");
#endif
		pc += KNH_ASMC_NEWE_SIZ;
		break;
	case ASMC_NEW__DEF :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_NEW__DEF__dump(ctx, (knh_asmc_new_def_t*)pc, 0, StdOut);
#endif
#ifdef VM_NEW__DEF
		VM_NEW__DEF(ctx, u1_(((knh_asmc_new_def_t*)pc)->a1), u2_(((knh_asmc_new_def_t*)pc)->a2), c2_(((knh_asmc_new_def_t*)pc)->a3));
#else
		DEBUG("TODO: VM_NEW__DEF");
#endif
		pc += KNH_ASMC_NEW_DEF_SIZ;
		break;
	case ASMC_MT :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MT__dump(ctx, (knh_asmc_mt_t*)pc, 0, StdOut);
#endif
#ifdef VM_MT
		VM_MT(ctx, mn_(((knh_asmc_mt_t*)pc)->a1));
#else
		DEBUG("TODO: VM_MT");
#endif
		pc += KNH_ASMC_MT_SIZ;
		break;
	case ASMC_MT__OPT :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MT__OPT__dump(ctx, (knh_asmc_mt_opt_t*)pc, 0, StdOut);
#endif
#ifdef VM_MT__OPT
		VM_MT__OPT(ctx, mn_(((knh_asmc_mt_opt_t*)pc)->a1), OBJ_(((knh_asmc_mt_opt_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MT__OPT");
#endif
		pc += KNH_ASMC_MT_OPT_SIZ;
		break;
	case ASMC_MAP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MAP__dump(ctx, (knh_asmc_map_t*)pc, 0, StdOut);
#endif
#ifdef VM_MAP
		VM_MAP(ctx, c2_(((knh_asmc_map_t*)pc)->a1));
#else
		DEBUG("TODO: VM_MAP");
#endif
		pc += KNH_ASMC_MAP_SIZ;
		break;
	case ASMC_MAPE :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MAPE__dump(ctx, (knh_asmc_mape_t*)pc, 0, StdOut);
#endif
#ifdef VM_MAPE
		VM_MAPE(ctx, c2_(((knh_asmc_mape_t*)pc)->a1));
#else
		DEBUG("TODO: VM_MAPE");
#endif
		pc += KNH_ASMC_MAPE_SIZ;
		break;
	case ASMC_MAP_WM :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MAP_WM__dump(ctx, (knh_asmc_map_wm_t*)pc, 0, StdOut);
#endif
#ifdef VM_MAP_WM
		VM_MAP_WM(ctx, OBJ_(((knh_asmc_map_wm_t*)pc)->a1));
#else
		DEBUG("TODO: VM_MAP_WM");
#endif
		pc += KNH_ASMC_MAP_WM_SIZ;
		break;
	case ASMC_MAPE_WM :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MAPE_WM__dump(ctx, (knh_asmc_mape_wm_t*)pc, 0, StdOut);
#endif
#ifdef VM_MAPE_WM
		VM_MAPE_WM(ctx, OBJ_(((knh_asmc_mape_wm_t*)pc)->a1));
#else
		DEBUG("TODO: VM_MAPE_WM");
#endif
		pc += KNH_ASMC_MAPE_WM_SIZ;
		break;
	case ASMC_MAP2 :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MAP2__dump(ctx, (knh_asmc_map2_t*)pc, 0, StdOut);
#endif
#ifdef VM_MAP2
		VM_MAP2(ctx, c2_(((knh_asmc_map2_t*)pc)->a1));
#else
		DEBUG("TODO: VM_MAP2");
#endif
		pc += KNH_ASMC_MAP2_SIZ;
		break;
	case ASMC_MAP2E :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_MAP2E__dump(ctx, (knh_asmc_map2e_t*)pc, 0, StdOut);
#endif
#ifdef VM_MAP2E
		VM_MAP2E(ctx, c2_(((knh_asmc_map2e_t*)pc)->a1));
#else
		DEBUG("TODO: VM_MAP2E");
#endif
		pc += KNH_ASMC_MAP2E_SIZ;
		break;
	case ASMC_TYPECHK__EBP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_TYPECHK__EBP__dump(ctx, (knh_asmc_typechk_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_TYPECHK
		VM_TYPECHK(ctx, c2_(((knh_asmc_typechk_ebp_t*)pc)->a1), ebp_(((knh_asmc_typechk_ebp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_TYPECHK");
#endif
		pc += KNH_ASMC_TYPECHK_ebp_SIZ;
		break;
	case ASMC_TYPECHK__SFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_TYPECHK__SFP__dump(ctx, (knh_asmc_typechk_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_TYPECHK
		VM_TYPECHK(ctx, c2_(((knh_asmc_typechk_sfp_t*)pc)->a1), sfp_(((knh_asmc_typechk_sfp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_TYPECHK");
#endif
		pc += KNH_ASMC_TYPECHK_sfp_SIZ;
		break;
	case ASMC_TYPECHK__OFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_TYPECHK__OFP__dump(ctx, (knh_asmc_typechk_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_TYPECHK
		VM_TYPECHK(ctx, c2_(((knh_asmc_typechk_ofp_t*)pc)->a1), ofp_(((knh_asmc_typechk_ofp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_TYPECHK");
#endif
		pc += KNH_ASMC_TYPECHK_ofp_SIZ;
		break;
	case ASMC_TYPECHK__OBJ :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_TYPECHK__OBJ__dump(ctx, (knh_asmc_typechk_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_TYPECHK
		VM_TYPECHK(ctx, c2_(((knh_asmc_typechk_obj_t*)pc)->a1), OBJ_(((knh_asmc_typechk_obj_t*)pc)->a2));
#else
		DEBUG("TODO: VM_TYPECHK");
#endif
		pc += KNH_ASMC_TYPECHK_OBJ_SIZ;
		break;
	case ASMC_TYPECHK__OIDX :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_TYPECHK__OIDX__dump(ctx, (knh_asmc_typechk_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_TYPECHK__OIDX
		VM_TYPECHK__OIDX(ctx, c2_(((knh_asmc_typechk_oidx_t*)pc)->a1), OBJ_(((knh_asmc_typechk_oidx_t*)pc)->a2), u1_(((knh_asmc_typechk_oidx_t*)pc)->a3));
#else
		DEBUG("TODO: VM_TYPECHK__OIDX");
#endif
		pc += KNH_ASMC_TYPECHK_OIDX_SIZ;
		break;
	case ASMC_NULLCHK__EBP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_NULLCHK__EBP__dump(ctx, (knh_asmc_nullchk_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_NULLCHK
		VM_NULLCHK(ctx, ebp_(((knh_asmc_nullchk_ebp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_NULLCHK");
#endif
		pc += KNH_ASMC_NULLCHK_ebp_SIZ;
		break;
	case ASMC_NULLCHK__SFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_NULLCHK__SFP__dump(ctx, (knh_asmc_nullchk_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_NULLCHK
		VM_NULLCHK(ctx, sfp_(((knh_asmc_nullchk_sfp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_NULLCHK");
#endif
		pc += KNH_ASMC_NULLCHK_sfp_SIZ;
		break;
	case ASMC_NULLCHK__OFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_NULLCHK__OFP__dump(ctx, (knh_asmc_nullchk_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_NULLCHK
		VM_NULLCHK(ctx, ofp_(((knh_asmc_nullchk_ofp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_NULLCHK");
#endif
		pc += KNH_ASMC_NULLCHK_ofp_SIZ;
		break;
	case ASMC_NULLCHK__OBJ :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_NULLCHK__OBJ__dump(ctx, (knh_asmc_nullchk_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_NULLCHK
		VM_NULLCHK(ctx, OBJ_(((knh_asmc_nullchk_obj_t*)pc)->a1));
#else
		DEBUG("TODO: VM_NULLCHK");
#endif
		pc += KNH_ASMC_NULLCHK_OBJ_SIZ;
		break;
	case ASMC_NULLCHK__OIDX :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_NULLCHK__OIDX__dump(ctx, (knh_asmc_nullchk_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_NULLCHK__OIDX
		VM_NULLCHK__OIDX(ctx, OBJ_(((knh_asmc_nullchk_oidx_t*)pc)->a1), u1_(((knh_asmc_nullchk_oidx_t*)pc)->a2));
#else
		DEBUG("TODO: VM_NULLCHK__OIDX");
#endif
		pc += KNH_ASMC_NULLCHK_OIDX_SIZ;
		break;
	case ASMC_JMP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP__dump(ctx, (knh_asmc_jmp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP
		VM_JMP(ctx, pc += ((knh_asmc_jmp_t*)pc)->a1, L_HEAD);
#else
		DEBUG("TODO: VM_JMP");
#endif
		pc += KNH_ASMC_JMP_SIZ;
		break;
	case ASMC_SKIP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_SKIP__dump(ctx, (knh_asmc_skip_t*)pc, 0, StdOut);
#endif
#ifdef VM_SKIP
		VM_SKIP(ctx, pc += ((knh_asmc_skip_t*)pc)->a1, L_HEAD);
#else
		DEBUG("TODO: VM_SKIP");
#endif
		pc += KNH_ASMC_SKIP_SIZ;
		break;
	case ASMC_JMP_IFT__EBP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP_IFT__EBP__dump(ctx, (knh_asmc_jmp_ift_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFT
		VM_JMP_IFT(ctx, pc += ((knh_asmc_jmp_ift_ebp_t*)pc)->a1, L_HEAD, ebp_(((knh_asmc_jmp_ift_ebp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFT");
#endif
		pc += KNH_ASMC_JMP_IFT_ebp_SIZ;
		break;
	case ASMC_JMP_IFT__SFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP_IFT__SFP__dump(ctx, (knh_asmc_jmp_ift_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFT
		VM_JMP_IFT(ctx, pc += ((knh_asmc_jmp_ift_sfp_t*)pc)->a1, L_HEAD, sfp_(((knh_asmc_jmp_ift_sfp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFT");
#endif
		pc += KNH_ASMC_JMP_IFT_sfp_SIZ;
		break;
	case ASMC_JMP_IFT__OFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP_IFT__OFP__dump(ctx, (knh_asmc_jmp_ift_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFT
		VM_JMP_IFT(ctx, pc += ((knh_asmc_jmp_ift_ofp_t*)pc)->a1, L_HEAD, ofp_(((knh_asmc_jmp_ift_ofp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFT");
#endif
		pc += KNH_ASMC_JMP_IFT_ofp_SIZ;
		break;
	case ASMC_JMP_IFT__OIDX :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP_IFT__OIDX__dump(ctx, (knh_asmc_jmp_ift_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFT__OIDX
		VM_JMP_IFT__OIDX(ctx, pc += ((knh_asmc_jmp_ift_oidx_t*)pc)->a1, L_HEAD, OBJ_(((knh_asmc_jmp_ift_oidx_t*)pc)->a2), u1_(((knh_asmc_jmp_ift_oidx_t*)pc)->a3));
#else
		DEBUG("TODO: VM_JMP_IFT__OIDX");
#endif
		pc += KNH_ASMC_JMP_IFT_OIDX_SIZ;
		break;
	case ASMC_JMP_IFF__EBP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP_IFF__EBP__dump(ctx, (knh_asmc_jmp_iff_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFF
		VM_JMP_IFF(ctx, pc += ((knh_asmc_jmp_iff_ebp_t*)pc)->a1, L_HEAD, ebp_(((knh_asmc_jmp_iff_ebp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFF");
#endif
		pc += KNH_ASMC_JMP_IFF_ebp_SIZ;
		break;
	case ASMC_JMP_IFF__SFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP_IFF__SFP__dump(ctx, (knh_asmc_jmp_iff_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFF
		VM_JMP_IFF(ctx, pc += ((knh_asmc_jmp_iff_sfp_t*)pc)->a1, L_HEAD, sfp_(((knh_asmc_jmp_iff_sfp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFF");
#endif
		pc += KNH_ASMC_JMP_IFF_sfp_SIZ;
		break;
	case ASMC_JMP_IFF__OFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP_IFF__OFP__dump(ctx, (knh_asmc_jmp_iff_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFF
		VM_JMP_IFF(ctx, pc += ((knh_asmc_jmp_iff_ofp_t*)pc)->a1, L_HEAD, ofp_(((knh_asmc_jmp_iff_ofp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFF");
#endif
		pc += KNH_ASMC_JMP_IFF_ofp_SIZ;
		break;
	case ASMC_JMP_IFF__OIDX :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP_IFF__OIDX__dump(ctx, (knh_asmc_jmp_iff_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFF__OIDX
		VM_JMP_IFF__OIDX(ctx, pc += ((knh_asmc_jmp_iff_oidx_t*)pc)->a1, L_HEAD, OBJ_(((knh_asmc_jmp_iff_oidx_t*)pc)->a2), u1_(((knh_asmc_jmp_iff_oidx_t*)pc)->a3));
#else
		DEBUG("TODO: VM_JMP_IFF__OIDX");
#endif
		pc += KNH_ASMC_JMP_IFF_OIDX_SIZ;
		break;
	case ASMC_JMP_IFNUL__EBP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP_IFNUL__EBP__dump(ctx, (knh_asmc_jmp_ifnul_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFNUL
		VM_JMP_IFNUL(ctx, pc += ((knh_asmc_jmp_ifnul_ebp_t*)pc)->a1, L_HEAD, ebp_(((knh_asmc_jmp_ifnul_ebp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFNUL");
#endif
		pc += KNH_ASMC_JMP_IFNUL_ebp_SIZ;
		break;
	case ASMC_JMP_IFNUL__SFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP_IFNUL__SFP__dump(ctx, (knh_asmc_jmp_ifnul_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFNUL
		VM_JMP_IFNUL(ctx, pc += ((knh_asmc_jmp_ifnul_sfp_t*)pc)->a1, L_HEAD, sfp_(((knh_asmc_jmp_ifnul_sfp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFNUL");
#endif
		pc += KNH_ASMC_JMP_IFNUL_sfp_SIZ;
		break;
	case ASMC_JMP_IFNUL__OFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP_IFNUL__OFP__dump(ctx, (knh_asmc_jmp_ifnul_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFNUL
		VM_JMP_IFNUL(ctx, pc += ((knh_asmc_jmp_ifnul_ofp_t*)pc)->a1, L_HEAD, ofp_(((knh_asmc_jmp_ifnul_ofp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFNUL");
#endif
		pc += KNH_ASMC_JMP_IFNUL_ofp_SIZ;
		break;
	case ASMC_JMP_IFNUL__OIDX :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP_IFNUL__OIDX__dump(ctx, (knh_asmc_jmp_ifnul_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFNUL__OIDX
		VM_JMP_IFNUL__OIDX(ctx, pc += ((knh_asmc_jmp_ifnul_oidx_t*)pc)->a1, L_HEAD, OBJ_(((knh_asmc_jmp_ifnul_oidx_t*)pc)->a2), u1_(((knh_asmc_jmp_ifnul_oidx_t*)pc)->a3));
#else
		DEBUG("TODO: VM_JMP_IFNUL__OIDX");
#endif
		pc += KNH_ASMC_JMP_IFNUL_OIDX_SIZ;
		break;
	case ASMC_JMP_IFNONUL__EBP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP_IFNONUL__EBP__dump(ctx, (knh_asmc_jmp_ifnonul_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFNONUL
		VM_JMP_IFNONUL(ctx, pc += ((knh_asmc_jmp_ifnonul_ebp_t*)pc)->a1, L_HEAD, ebp_(((knh_asmc_jmp_ifnonul_ebp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFNONUL");
#endif
		pc += KNH_ASMC_JMP_IFNONUL_ebp_SIZ;
		break;
	case ASMC_JMP_IFNONUL__SFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP_IFNONUL__SFP__dump(ctx, (knh_asmc_jmp_ifnonul_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFNONUL
		VM_JMP_IFNONUL(ctx, pc += ((knh_asmc_jmp_ifnonul_sfp_t*)pc)->a1, L_HEAD, sfp_(((knh_asmc_jmp_ifnonul_sfp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFNONUL");
#endif
		pc += KNH_ASMC_JMP_IFNONUL_sfp_SIZ;
		break;
	case ASMC_JMP_IFNONUL__OFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP_IFNONUL__OFP__dump(ctx, (knh_asmc_jmp_ifnonul_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFNONUL
		VM_JMP_IFNONUL(ctx, pc += ((knh_asmc_jmp_ifnonul_ofp_t*)pc)->a1, L_HEAD, ofp_(((knh_asmc_jmp_ifnonul_ofp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFNONUL");
#endif
		pc += KNH_ASMC_JMP_IFNONUL_ofp_SIZ;
		break;
	case ASMC_JMP_IFNONUL__OIDX :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_JMP_IFNONUL__OIDX__dump(ctx, (knh_asmc_jmp_ifnonul_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFNONUL__OIDX
		VM_JMP_IFNONUL__OIDX(ctx, pc += ((knh_asmc_jmp_ifnonul_oidx_t*)pc)->a1, L_HEAD, OBJ_(((knh_asmc_jmp_ifnonul_oidx_t*)pc)->a2), u1_(((knh_asmc_jmp_ifnonul_oidx_t*)pc)->a3));
#else
		DEBUG("TODO: VM_JMP_IFNONUL__OIDX");
#endif
		pc += KNH_ASMC_JMP_IFNONUL_OIDX_SIZ;
		break;
	case ASMC_ITER :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_ITER__dump(ctx, (knh_asmc_iter_t*)pc, 0, StdOut);
#endif
#ifdef VM_ITER
		VM_ITER(ctx, c2_(((knh_asmc_iter_t*)pc)->a1), sfp_(((knh_asmc_iter_t*)pc)->a2));
#else
		DEBUG("TODO: VM_ITER");
#endif
		pc += KNH_ASMC_ITER_SIZ;
		break;
	case ASMC_FOREACH :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_FOREACH__dump(ctx, (knh_asmc_foreach_t*)pc, 0, StdOut);
#endif
#ifdef VM_FOREACH
		VM_FOREACH(ctx, pc += ((knh_asmc_foreach_t*)pc)->a1, L_HEAD, c2_(((knh_asmc_foreach_t*)pc)->a2), sfp_(((knh_asmc_foreach_t*)pc)->a3), sfp_(((knh_asmc_foreach_t*)pc)->a4));
#else
		DEBUG("TODO: VM_FOREACH");
#endif
		pc += KNH_ASMC_FOREACH_SIZ;
		break;
	case ASMC_TRY_BEGIN :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_TRY_BEGIN__dump(ctx, (knh_asmc_try_begin_t*)pc, 0, StdOut);
#endif
#ifdef VM_TRY_BEGIN
		VM_TRY_BEGIN(ctx, pc += ((knh_asmc_try_begin_t*)pc)->a1, L_HEAD, sfp_(((knh_asmc_try_begin_t*)pc)->a2), sfp_(((knh_asmc_try_begin_t*)pc)->a3));
#else
		DEBUG("TODO: VM_TRY_BEGIN");
#endif
		pc += KNH_ASMC_TRY_BEGIN_SIZ;
		break;
	case ASMC_TRY_END :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_TRY_END__dump(ctx, (knh_asmc_try_end_t*)pc, 0, StdOut);
#endif
#ifdef VM_TRY_END
		VM_TRY_END(ctx, sfp_(((knh_asmc_try_end_t*)pc)->a1));
#else
		DEBUG("TODO: VM_TRY_END");
#endif
		pc += KNH_ASMC_TRY_END_SIZ;
		break;
	case ASMC_CATCH :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_CATCH__dump(ctx, (knh_asmc_catch_t*)pc, 0, StdOut);
#endif
#ifdef VM_CATCH
		VM_CATCH(ctx, pc += ((knh_asmc_catch_t*)pc)->a1, L_HEAD, e2_(((knh_asmc_catch_t*)pc)->a2), sfp_(((knh_asmc_catch_t*)pc)->a3));
#else
		DEBUG("TODO: VM_CATCH");
#endif
		pc += KNH_ASMC_CATCH_SIZ;
		break;
	case ASMC_THROW__EBP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_THROW__EBP__dump(ctx, (knh_asmc_throw_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_THROW
		VM_THROW(ctx, ebp_(((knh_asmc_throw_ebp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_THROW");
#endif
		pc += KNH_ASMC_THROW_ebp_SIZ;
		break;
	case ASMC_THROW__SFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_THROW__SFP__dump(ctx, (knh_asmc_throw_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_THROW
		VM_THROW(ctx, sfp_(((knh_asmc_throw_sfp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_THROW");
#endif
		pc += KNH_ASMC_THROW_sfp_SIZ;
		break;
	case ASMC_THROW__OBJ :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_THROW__OBJ__dump(ctx, (knh_asmc_throw_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_THROW
		VM_THROW(ctx, OBJ_(((knh_asmc_throw_obj_t*)pc)->a1));
#else
		DEBUG("TODO: VM_THROW");
#endif
		pc += KNH_ASMC_THROW_OBJ_SIZ;
		break;
	case ASMC_PRINT__EBP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_PRINT__EBP__dump(ctx, (knh_asmc_print_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_PRINT
		VM_PRINT(ctx, u2_(((knh_asmc_print_ebp_t*)pc)->a1), mn_(((knh_asmc_print_ebp_t*)pc)->a2), ebp_(((knh_asmc_print_ebp_t*)pc)->a3));
#else
		DEBUG("TODO: VM_PRINT");
#endif
		pc += KNH_ASMC_PRINT_ebp_SIZ;
		break;
	case ASMC_PRINT__SFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_PRINT__SFP__dump(ctx, (knh_asmc_print_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_PRINT
		VM_PRINT(ctx, u2_(((knh_asmc_print_sfp_t*)pc)->a1), mn_(((knh_asmc_print_sfp_t*)pc)->a2), sfp_(((knh_asmc_print_sfp_t*)pc)->a3));
#else
		DEBUG("TODO: VM_PRINT");
#endif
		pc += KNH_ASMC_PRINT_sfp_SIZ;
		break;
	case ASMC_PRINT__OFP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_PRINT__OFP__dump(ctx, (knh_asmc_print_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_PRINT
		VM_PRINT(ctx, u2_(((knh_asmc_print_ofp_t*)pc)->a1), mn_(((knh_asmc_print_ofp_t*)pc)->a2), ofp_(((knh_asmc_print_ofp_t*)pc)->a3));
#else
		DEBUG("TODO: VM_PRINT");
#endif
		pc += KNH_ASMC_PRINT_ofp_SIZ;
		break;
	case ASMC_PRINT__OBJ :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_PRINT__OBJ__dump(ctx, (knh_asmc_print_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_PRINT
		VM_PRINT(ctx, u2_(((knh_asmc_print_obj_t*)pc)->a1), mn_(((knh_asmc_print_obj_t*)pc)->a2), OBJ_(((knh_asmc_print_obj_t*)pc)->a3));
#else
		DEBUG("TODO: VM_PRINT");
#endif
		pc += KNH_ASMC_PRINT_OBJ_SIZ;
		break;
	case ASMC_PRINT__OIDX :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_PRINT__OIDX__dump(ctx, (knh_asmc_print_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_PRINT__OIDX
		VM_PRINT__OIDX(ctx, u2_(((knh_asmc_print_oidx_t*)pc)->a1), mn_(((knh_asmc_print_oidx_t*)pc)->a2), OBJ_(((knh_asmc_print_oidx_t*)pc)->a3), u1_(((knh_asmc_print_oidx_t*)pc)->a4));
#else
		DEBUG("TODO: VM_PRINT__OIDX");
#endif
		pc += KNH_ASMC_PRINT_OIDX_SIZ;
		break;
	case ASMC_DIAGNOSE :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_DIAGNOSE__dump(ctx, (knh_asmc_diagnose_t*)pc, 0, StdOut);
#endif
#ifdef VM_DIAGNOSE
		VM_DIAGNOSE(ctx, u1_(((knh_asmc_diagnose_t*)pc)->a1));
#else
		DEBUG("TODO: VM_DIAGNOSE");
#endif
		pc += KNH_ASMC_DIAGNOSE_SIZ;
		break;
	case ASMC_STACKDUMP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_STACKDUMP__dump(ctx, (knh_asmc_stackdump_t*)pc, 0, StdOut);
#endif
#ifdef VM_STACKDUMP
		VM_STACKDUMP(ctx);
#else
		DEBUG("TODO: VM_STACKDUMP");
#endif
		pc += KNH_ASMC_STACKDUMP_SIZ;
		break;
	case ASMC_NOP :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_ASMC_NOP__dump(ctx, (knh_asmc_nop_t*)pc, 0, StdOut);
#endif
#ifdef VM_NOP
		VM_NOP(ctx);
#else
		DEBUG("TODO: VM_NOP");
#endif
		pc += KNH_ASMC_NOP_SIZ;
		break;

	}
	goto L_HEAD;
}

/* ------------------------------------------------------------------------ */

PUBLIC
void knh_VirtualMachineCode_exec(Ctx *ctx, Object **sfp)
{
	static void *globalMachineToJump[] = {
		&&L_ASMC_RET_VOID,
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
		&&L_ASMC_PUSH__SFP,
		&&L_ASMC_PUSH__OFP,
		&&L_ASMC_PUSH__OBJ,
		&&L_ASMC_PUSH__OIDX,
		&&L_ASMC_PUTI,
		&&L_ASMC_PUSH__MN,
		&&L_ASMC_PUSH__DEF,
		&&L_ASMC_VARGS,
		&&L_ASMC_SCALL,
		&&L_ASMC_CALL,
		&&L_ASMC_DCALL,
		&&L_ASMC_MCALL,
		&&L_ASMC_CALL_WM,
		&&L_ASMC_NCALL_WM,
		&&L_ASMC_NEW,
		&&L_ASMC_NEWE,
		&&L_ASMC_NEW__DEF,
		&&L_ASMC_MT,
		&&L_ASMC_MT__OPT,
		&&L_ASMC_MAP,
		&&L_ASMC_MAPE,
		&&L_ASMC_MAP_WM,
		&&L_ASMC_MAPE_WM,
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
		&&L_ASMC_JMP_IFNUL__EBP,
		&&L_ASMC_JMP_IFNUL__SFP,
		&&L_ASMC_JMP_IFNUL__OFP,
		&&L_ASMC_JMP_IFNUL__OIDX,
		&&L_ASMC_JMP_IFNONUL__EBP,
		&&L_ASMC_JMP_IFNONUL__SFP,
		&&L_ASMC_JMP_IFNONUL__OFP,
		&&L_ASMC_JMP_IFNONUL__OIDX,
		&&L_ASMC_ITER,
		&&L_ASMC_FOREACH,
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
		&&L_ASMC_DIAGNOSE,
		&&L_ASMC_STACKDUMP,
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
		&&L_UNKNOWN,
		&&L_UNKNOWN,
		&&L_UNKNOWN
	};
	knh_vmc_t *pc =  ((VirtualMachineCode*)((Method*)sfp[-1])->code)->code;
	goto *globalMachineToJump[PCT_(pc)];


	L_ASMC_RET_VOID:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_RET_VOID__dump(ctx, (knh_asmc_ret_void_t*)pc, 0, StdOut);
#endif
#ifdef VM_RET_VOID
		VM_RET_VOID(ctx);
#else
		DEBUG("TODO: VM_RET_VOID");
#endif
	pc += KNH_ASMC_RET_VOID_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_RET__EBP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_RET__ebp__dump(ctx, (knh_asmc_ret_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_RET
		VM_RET(ctx, ebp_(((knh_asmc_ret_ebp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_RET");
#endif
	pc += KNH_ASMC_RET_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_RET__SFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_RET__sfp__dump(ctx, (knh_asmc_ret_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_RET
		VM_RET(ctx, sfp_(((knh_asmc_ret_sfp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_RET");
#endif
	pc += KNH_ASMC_RET_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_RET__OFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_RET__ofp__dump(ctx, (knh_asmc_ret_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_RET
		VM_RET(ctx, ofp_(((knh_asmc_ret_ofp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_RET");
#endif
	pc += KNH_ASMC_RET_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_RET__OBJ:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_RET__OBJ__dump(ctx, (knh_asmc_ret_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_RET
		VM_RET(ctx, OBJ_(((knh_asmc_ret_obj_t*)pc)->a1));
#else
		DEBUG("TODO: VM_RET");
#endif
	pc += KNH_ASMC_RET_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_RET__OIDX:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_RET__OIDX__dump(ctx, (knh_asmc_ret_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_RET__OIDX
		VM_RET__OIDX(ctx, OBJ_(((knh_asmc_ret_oidx_t*)pc)->a1), u1_(((knh_asmc_ret_oidx_t*)pc)->a2));
#else
		DEBUG("TODO: VM_RET__OIDX");
#endif
	pc += KNH_ASMC_RET_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVE__EBP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVE__ebp__dump(ctx, (knh_asmc_move_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVE
		VM_MOVE(ctx, ebp_(((knh_asmc_move_ebp_t*)pc)->a1), ebp_(((knh_asmc_move_ebp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVE");
#endif
	pc += KNH_ASMC_MOVE_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVE__SFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVE__sfp__dump(ctx, (knh_asmc_move_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVE
		VM_MOVE(ctx, ebp_(((knh_asmc_move_sfp_t*)pc)->a1), sfp_(((knh_asmc_move_sfp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVE");
#endif
	pc += KNH_ASMC_MOVE_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVE__OFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVE__ofp__dump(ctx, (knh_asmc_move_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVE
		VM_MOVE(ctx, ebp_(((knh_asmc_move_ofp_t*)pc)->a1), ofp_(((knh_asmc_move_ofp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVE");
#endif
	pc += KNH_ASMC_MOVE_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVE__OBJ:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVE__OBJ__dump(ctx, (knh_asmc_move_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVE
		VM_MOVE(ctx, ebp_(((knh_asmc_move_obj_t*)pc)->a1), OBJ_(((knh_asmc_move_obj_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVE");
#endif
	pc += KNH_ASMC_MOVE_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVE__OIDX:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVE__OIDX__dump(ctx, (knh_asmc_move_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVE__OIDX
		VM_MOVE__OIDX(ctx, ebp_(((knh_asmc_move_oidx_t*)pc)->a1), OBJ_(((knh_asmc_move_oidx_t*)pc)->a2), u1_(((knh_asmc_move_oidx_t*)pc)->a3));
#else
		DEBUG("TODO: VM_MOVE__OIDX");
#endif
	pc += KNH_ASMC_MOVE_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVS__EBP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVS__ebp__dump(ctx, (knh_asmc_movs_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVS
		VM_MOVS(ctx, sfp_(((knh_asmc_movs_ebp_t*)pc)->a1), ebp_(((knh_asmc_movs_ebp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVS");
#endif
	pc += KNH_ASMC_MOVS_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVS__SFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVS__sfp__dump(ctx, (knh_asmc_movs_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVS
		VM_MOVS(ctx, sfp_(((knh_asmc_movs_sfp_t*)pc)->a1), sfp_(((knh_asmc_movs_sfp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVS");
#endif
	pc += KNH_ASMC_MOVS_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVS__OFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVS__ofp__dump(ctx, (knh_asmc_movs_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVS
		VM_MOVS(ctx, sfp_(((knh_asmc_movs_ofp_t*)pc)->a1), ofp_(((knh_asmc_movs_ofp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVS");
#endif
	pc += KNH_ASMC_MOVS_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVS__OBJ:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVS__OBJ__dump(ctx, (knh_asmc_movs_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVS
		VM_MOVS(ctx, sfp_(((knh_asmc_movs_obj_t*)pc)->a1), OBJ_(((knh_asmc_movs_obj_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVS");
#endif
	pc += KNH_ASMC_MOVS_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVS__OIDX:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVS__OIDX__dump(ctx, (knh_asmc_movs_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVS__OIDX
		VM_MOVS__OIDX(ctx, sfp_(((knh_asmc_movs_oidx_t*)pc)->a1), OBJ_(((knh_asmc_movs_oidx_t*)pc)->a2), u1_(((knh_asmc_movs_oidx_t*)pc)->a3));
#else
		DEBUG("TODO: VM_MOVS__OIDX");
#endif
	pc += KNH_ASMC_MOVS_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVO__EBP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVO__ebp__dump(ctx, (knh_asmc_movo_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVO
		VM_MOVO(ctx, ofp_(((knh_asmc_movo_ebp_t*)pc)->a1), ebp_(((knh_asmc_movo_ebp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVO");
#endif
	pc += KNH_ASMC_MOVO_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVO__SFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVO__sfp__dump(ctx, (knh_asmc_movo_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVO
		VM_MOVO(ctx, ofp_(((knh_asmc_movo_sfp_t*)pc)->a1), sfp_(((knh_asmc_movo_sfp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVO");
#endif
	pc += KNH_ASMC_MOVO_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVO__OFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVO__ofp__dump(ctx, (knh_asmc_movo_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVO
		VM_MOVO(ctx, ofp_(((knh_asmc_movo_ofp_t*)pc)->a1), ofp_(((knh_asmc_movo_ofp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVO");
#endif
	pc += KNH_ASMC_MOVO_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVO__OBJ:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVO__OBJ__dump(ctx, (knh_asmc_movo_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVO
		VM_MOVO(ctx, ofp_(((knh_asmc_movo_obj_t*)pc)->a1), OBJ_(((knh_asmc_movo_obj_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVO");
#endif
	pc += KNH_ASMC_MOVO_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVO__OIDX:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVO__OIDX__dump(ctx, (knh_asmc_movo_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVO__OIDX
		VM_MOVO__OIDX(ctx, ofp_(((knh_asmc_movo_oidx_t*)pc)->a1), OBJ_(((knh_asmc_movo_oidx_t*)pc)->a2), u1_(((knh_asmc_movo_oidx_t*)pc)->a3));
#else
		DEBUG("TODO: VM_MOVO__OIDX");
#endif
	pc += KNH_ASMC_MOVO_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVOI__EBP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVOI__ebp__dump(ctx, (knh_asmc_movoi_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVOI
		VM_MOVOI(ctx, OBJ_(((knh_asmc_movoi_ebp_t*)pc)->a1), ofp_(((knh_asmc_movoi_ebp_t*)pc)->a2), ebp_(((knh_asmc_movoi_ebp_t*)pc)->a3));
#else
		DEBUG("TODO: VM_MOVOI");
#endif
	pc += KNH_ASMC_MOVOI_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVOI__SFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVOI__sfp__dump(ctx, (knh_asmc_movoi_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVOI
		VM_MOVOI(ctx, OBJ_(((knh_asmc_movoi_sfp_t*)pc)->a1), ofp_(((knh_asmc_movoi_sfp_t*)pc)->a2), sfp_(((knh_asmc_movoi_sfp_t*)pc)->a3));
#else
		DEBUG("TODO: VM_MOVOI");
#endif
	pc += KNH_ASMC_MOVOI_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVOI__OFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVOI__ofp__dump(ctx, (knh_asmc_movoi_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVOI
		VM_MOVOI(ctx, OBJ_(((knh_asmc_movoi_ofp_t*)pc)->a1), ofp_(((knh_asmc_movoi_ofp_t*)pc)->a2), ofp_(((knh_asmc_movoi_ofp_t*)pc)->a3));
#else
		DEBUG("TODO: VM_MOVOI");
#endif
	pc += KNH_ASMC_MOVOI_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVOI__OBJ:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVOI__OBJ__dump(ctx, (knh_asmc_movoi_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVOI
		VM_MOVOI(ctx, OBJ_(((knh_asmc_movoi_obj_t*)pc)->a1), ofp_(((knh_asmc_movoi_obj_t*)pc)->a2), OBJ_(((knh_asmc_movoi_obj_t*)pc)->a3));
#else
		DEBUG("TODO: VM_MOVOI");
#endif
	pc += KNH_ASMC_MOVOI_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVOI__OIDX:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVOI__OIDX__dump(ctx, (knh_asmc_movoi_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVOI__OIDX
		VM_MOVOI__OIDX(ctx, OBJ_(((knh_asmc_movoi_oidx_t*)pc)->a1), u1_(((knh_asmc_movoi_oidx_t*)pc)->a2), OBJ_(((knh_asmc_movoi_oidx_t*)pc)->a3), u1_(((knh_asmc_movoi_oidx_t*)pc)->a4));
#else
		DEBUG("TODO: VM_MOVOI__OIDX");
#endif
	pc += KNH_ASMC_MOVOI_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MOVSFP_IFNUL:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MOVSFP_IFNUL__dump(ctx, (knh_asmc_movsfp_ifnul_t*)pc, 0, StdOut);
#endif
#ifdef VM_MOVSFP_IFNUL
		VM_MOVSFP_IFNUL(ctx, u1_(((knh_asmc_movsfp_ifnul_t*)pc)->a1), OBJ_(((knh_asmc_movsfp_ifnul_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MOVSFP_IFNUL");
#endif
	pc += KNH_ASMC_MOVSFP_IFNUL_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PUSH__SFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_PUSH__sfp__dump(ctx, (knh_asmc_push_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_PUSH
		VM_PUSH(ctx, sfp_(((knh_asmc_push_sfp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_PUSH");
#endif
	pc += KNH_ASMC_PUSH_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PUSH__OFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_PUSH__ofp__dump(ctx, (knh_asmc_push_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_PUSH
		VM_PUSH(ctx, ofp_(((knh_asmc_push_ofp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_PUSH");
#endif
	pc += KNH_ASMC_PUSH_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PUSH__OBJ:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_PUSH__OBJ__dump(ctx, (knh_asmc_push_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_PUSH
		VM_PUSH(ctx, OBJ_(((knh_asmc_push_obj_t*)pc)->a1));
#else
		DEBUG("TODO: VM_PUSH");
#endif
	pc += KNH_ASMC_PUSH_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PUSH__OIDX:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_PUSH__OIDX__dump(ctx, (knh_asmc_push_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_PUSH__OIDX
		VM_PUSH__OIDX(ctx, OBJ_(((knh_asmc_push_oidx_t*)pc)->a1), u1_(((knh_asmc_push_oidx_t*)pc)->a2));
#else
		DEBUG("TODO: VM_PUSH__OIDX");
#endif
	pc += KNH_ASMC_PUSH_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PUTI:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_PUTI__dump(ctx, (knh_asmc_puti_t*)pc, 0, StdOut);
#endif
#ifdef VM_PUTI
		VM_PUTI(ctx, u2_(((knh_asmc_puti_t*)pc)->a1));
#else
		DEBUG("TODO: VM_PUTI");
#endif
	pc += KNH_ASMC_PUTI_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PUSH__MN:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_PUSH__MN__dump(ctx, (knh_asmc_push_mn_t*)pc, 0, StdOut);
#endif
#ifdef VM_PUSH__MN
		VM_PUSH__MN(ctx, mn_(((knh_asmc_push_mn_t*)pc)->a1));
#else
		DEBUG("TODO: VM_PUSH__MN");
#endif
	pc += KNH_ASMC_PUSH_MN_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PUSH__DEF:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_PUSH__DEF__dump(ctx, (knh_asmc_push_def_t*)pc, 0, StdOut);
#endif
#ifdef VM_PUSH__DEF
		VM_PUSH__DEF(ctx, c2_(((knh_asmc_push_def_t*)pc)->a1));
#else
		DEBUG("TODO: VM_PUSH__DEF");
#endif
	pc += KNH_ASMC_PUSH_DEF_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_VARGS:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_VARGS__dump(ctx, (knh_asmc_vargs_t*)pc, 0, StdOut);
#endif
#ifdef VM_VARGS
		VM_VARGS(ctx, u2_(((knh_asmc_vargs_t*)pc)->a1));
#else
		DEBUG("TODO: VM_VARGS");
#endif
	pc += KNH_ASMC_VARGS_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_SCALL:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_SCALL__dump(ctx, (knh_asmc_scall_t*)pc, 0, StdOut);
#endif
#ifdef VM_SCALL
		VM_SCALL(ctx, u1_(((knh_asmc_scall_t*)pc)->a1));
#else
		DEBUG("TODO: VM_SCALL");
#endif
	pc += KNH_ASMC_SCALL_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_CALL:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_CALL__dump(ctx, (knh_asmc_call_t*)pc, 0, StdOut);
#endif
#ifdef VM_CALL
		VM_CALL(ctx, u1_(((knh_asmc_call_t*)pc)->a1));
#else
		DEBUG("TODO: VM_CALL");
#endif
	pc += KNH_ASMC_CALL_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_DCALL:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_DCALL__dump(ctx, (knh_asmc_dcall_t*)pc, 0, StdOut);
#endif
#ifdef VM_DCALL
		VM_DCALL(ctx, u1_(((knh_asmc_dcall_t*)pc)->a1));
#else
		DEBUG("TODO: VM_DCALL");
#endif
	pc += KNH_ASMC_DCALL_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MCALL:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MCALL__dump(ctx, (knh_asmc_mcall_t*)pc, 0, StdOut);
#endif
#ifdef VM_MCALL
		VM_MCALL(ctx, u1_(((knh_asmc_mcall_t*)pc)->a1));
#else
		DEBUG("TODO: VM_MCALL");
#endif
	pc += KNH_ASMC_MCALL_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_CALL_WM:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_CALL_WM__dump(ctx, (knh_asmc_call_wm_t*)pc, 0, StdOut);
#endif
#ifdef VM_CALL_WM
		VM_CALL_WM(ctx, u1_(((knh_asmc_call_wm_t*)pc)->a1), OBJ_(((knh_asmc_call_wm_t*)pc)->a2));
#else
		DEBUG("TODO: VM_CALL_WM");
#endif
	pc += KNH_ASMC_CALL_WM_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NCALL_WM:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_NCALL_WM__dump(ctx, (knh_asmc_ncall_wm_t*)pc, 0, StdOut);
#endif
#ifdef VM_NCALL_WM
		VM_NCALL_WM(ctx, u1_(((knh_asmc_ncall_wm_t*)pc)->a1), OBJ_(((knh_asmc_ncall_wm_t*)pc)->a2));
#else
		DEBUG("TODO: VM_NCALL_WM");
#endif
	pc += KNH_ASMC_NCALL_WM_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NEW:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_NEW__dump(ctx, (knh_asmc_new_t*)pc, 0, StdOut);
#endif
#ifdef VM_NEW
		VM_NEW(ctx, u2_(((knh_asmc_new_t*)pc)->a1), OBJ_(((knh_asmc_new_t*)pc)->a2), u2_(((knh_asmc_new_t*)pc)->a3), c2_(((knh_asmc_new_t*)pc)->a4));
#else
		DEBUG("TODO: VM_NEW");
#endif
	pc += KNH_ASMC_NEW_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NEWE:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_NEWE__dump(ctx, (knh_asmc_newe_t*)pc, 0, StdOut);
#endif
#ifdef VM_NEWE
		VM_NEWE(ctx, u2_(((knh_asmc_newe_t*)pc)->a1), OBJ_(((knh_asmc_newe_t*)pc)->a2), u2_(((knh_asmc_newe_t*)pc)->a3), c2_(((knh_asmc_newe_t*)pc)->a4));
#else
		DEBUG("TODO: VM_NEWE");
#endif
	pc += KNH_ASMC_NEWE_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NEW__DEF:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_NEW__DEF__dump(ctx, (knh_asmc_new_def_t*)pc, 0, StdOut);
#endif
#ifdef VM_NEW__DEF
		VM_NEW__DEF(ctx, u1_(((knh_asmc_new_def_t*)pc)->a1), u2_(((knh_asmc_new_def_t*)pc)->a2), c2_(((knh_asmc_new_def_t*)pc)->a3));
#else
		DEBUG("TODO: VM_NEW__DEF");
#endif
	pc += KNH_ASMC_NEW_DEF_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MT:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MT__dump(ctx, (knh_asmc_mt_t*)pc, 0, StdOut);
#endif
#ifdef VM_MT
		VM_MT(ctx, mn_(((knh_asmc_mt_t*)pc)->a1));
#else
		DEBUG("TODO: VM_MT");
#endif
	pc += KNH_ASMC_MT_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MT__OPT:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MT__OPT__dump(ctx, (knh_asmc_mt_opt_t*)pc, 0, StdOut);
#endif
#ifdef VM_MT__OPT
		VM_MT__OPT(ctx, mn_(((knh_asmc_mt_opt_t*)pc)->a1), OBJ_(((knh_asmc_mt_opt_t*)pc)->a2));
#else
		DEBUG("TODO: VM_MT__OPT");
#endif
	pc += KNH_ASMC_MT_OPT_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MAP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MAP__dump(ctx, (knh_asmc_map_t*)pc, 0, StdOut);
#endif
#ifdef VM_MAP
		VM_MAP(ctx, c2_(((knh_asmc_map_t*)pc)->a1));
#else
		DEBUG("TODO: VM_MAP");
#endif
	pc += KNH_ASMC_MAP_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MAPE:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MAPE__dump(ctx, (knh_asmc_mape_t*)pc, 0, StdOut);
#endif
#ifdef VM_MAPE
		VM_MAPE(ctx, c2_(((knh_asmc_mape_t*)pc)->a1));
#else
		DEBUG("TODO: VM_MAPE");
#endif
	pc += KNH_ASMC_MAPE_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MAP_WM:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MAP_WM__dump(ctx, (knh_asmc_map_wm_t*)pc, 0, StdOut);
#endif
#ifdef VM_MAP_WM
		VM_MAP_WM(ctx, OBJ_(((knh_asmc_map_wm_t*)pc)->a1));
#else
		DEBUG("TODO: VM_MAP_WM");
#endif
	pc += KNH_ASMC_MAP_WM_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MAPE_WM:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MAPE_WM__dump(ctx, (knh_asmc_mape_wm_t*)pc, 0, StdOut);
#endif
#ifdef VM_MAPE_WM
		VM_MAPE_WM(ctx, OBJ_(((knh_asmc_mape_wm_t*)pc)->a1));
#else
		DEBUG("TODO: VM_MAPE_WM");
#endif
	pc += KNH_ASMC_MAPE_WM_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MAP2:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MAP2__dump(ctx, (knh_asmc_map2_t*)pc, 0, StdOut);
#endif
#ifdef VM_MAP2
		VM_MAP2(ctx, c2_(((knh_asmc_map2_t*)pc)->a1));
#else
		DEBUG("TODO: VM_MAP2");
#endif
	pc += KNH_ASMC_MAP2_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_MAP2E:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_MAP2E__dump(ctx, (knh_asmc_map2e_t*)pc, 0, StdOut);
#endif
#ifdef VM_MAP2E
		VM_MAP2E(ctx, c2_(((knh_asmc_map2e_t*)pc)->a1));
#else
		DEBUG("TODO: VM_MAP2E");
#endif
	pc += KNH_ASMC_MAP2E_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_TYPECHK__EBP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_TYPECHK__ebp__dump(ctx, (knh_asmc_typechk_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_TYPECHK
		VM_TYPECHK(ctx, c2_(((knh_asmc_typechk_ebp_t*)pc)->a1), ebp_(((knh_asmc_typechk_ebp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_TYPECHK");
#endif
	pc += KNH_ASMC_TYPECHK_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_TYPECHK__SFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_TYPECHK__sfp__dump(ctx, (knh_asmc_typechk_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_TYPECHK
		VM_TYPECHK(ctx, c2_(((knh_asmc_typechk_sfp_t*)pc)->a1), sfp_(((knh_asmc_typechk_sfp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_TYPECHK");
#endif
	pc += KNH_ASMC_TYPECHK_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_TYPECHK__OFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_TYPECHK__ofp__dump(ctx, (knh_asmc_typechk_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_TYPECHK
		VM_TYPECHK(ctx, c2_(((knh_asmc_typechk_ofp_t*)pc)->a1), ofp_(((knh_asmc_typechk_ofp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_TYPECHK");
#endif
	pc += KNH_ASMC_TYPECHK_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_TYPECHK__OBJ:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_TYPECHK__OBJ__dump(ctx, (knh_asmc_typechk_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_TYPECHK
		VM_TYPECHK(ctx, c2_(((knh_asmc_typechk_obj_t*)pc)->a1), OBJ_(((knh_asmc_typechk_obj_t*)pc)->a2));
#else
		DEBUG("TODO: VM_TYPECHK");
#endif
	pc += KNH_ASMC_TYPECHK_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_TYPECHK__OIDX:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_TYPECHK__OIDX__dump(ctx, (knh_asmc_typechk_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_TYPECHK__OIDX
		VM_TYPECHK__OIDX(ctx, c2_(((knh_asmc_typechk_oidx_t*)pc)->a1), OBJ_(((knh_asmc_typechk_oidx_t*)pc)->a2), u1_(((knh_asmc_typechk_oidx_t*)pc)->a3));
#else
		DEBUG("TODO: VM_TYPECHK__OIDX");
#endif
	pc += KNH_ASMC_TYPECHK_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NULLCHK__EBP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_NULLCHK__ebp__dump(ctx, (knh_asmc_nullchk_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_NULLCHK
		VM_NULLCHK(ctx, ebp_(((knh_asmc_nullchk_ebp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_NULLCHK");
#endif
	pc += KNH_ASMC_NULLCHK_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NULLCHK__SFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_NULLCHK__sfp__dump(ctx, (knh_asmc_nullchk_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_NULLCHK
		VM_NULLCHK(ctx, sfp_(((knh_asmc_nullchk_sfp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_NULLCHK");
#endif
	pc += KNH_ASMC_NULLCHK_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NULLCHK__OFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_NULLCHK__ofp__dump(ctx, (knh_asmc_nullchk_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_NULLCHK
		VM_NULLCHK(ctx, ofp_(((knh_asmc_nullchk_ofp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_NULLCHK");
#endif
	pc += KNH_ASMC_NULLCHK_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NULLCHK__OBJ:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_NULLCHK__OBJ__dump(ctx, (knh_asmc_nullchk_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_NULLCHK
		VM_NULLCHK(ctx, OBJ_(((knh_asmc_nullchk_obj_t*)pc)->a1));
#else
		DEBUG("TODO: VM_NULLCHK");
#endif
	pc += KNH_ASMC_NULLCHK_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NULLCHK__OIDX:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_NULLCHK__OIDX__dump(ctx, (knh_asmc_nullchk_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_NULLCHK__OIDX
		VM_NULLCHK__OIDX(ctx, OBJ_(((knh_asmc_nullchk_oidx_t*)pc)->a1), u1_(((knh_asmc_nullchk_oidx_t*)pc)->a2));
#else
		DEBUG("TODO: VM_NULLCHK__OIDX");
#endif
	pc += KNH_ASMC_NULLCHK_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP__dump(ctx, (knh_asmc_jmp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP
		VM_JMP(ctx, pc += ((knh_asmc_jmp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)]);
#else
		DEBUG("TODO: VM_JMP");
#endif
	pc += KNH_ASMC_JMP_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_SKIP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_SKIP__dump(ctx, (knh_asmc_skip_t*)pc, 0, StdOut);
#endif
#ifdef VM_SKIP
		VM_SKIP(ctx, pc += ((knh_asmc_skip_t*)pc)->a1, *globalMachineToJump[PCT_(pc)]);
#else
		DEBUG("TODO: VM_SKIP");
#endif
	pc += KNH_ASMC_SKIP_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFT__EBP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP_IFT__ebp__dump(ctx, (knh_asmc_jmp_ift_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFT
		VM_JMP_IFT(ctx, pc += ((knh_asmc_jmp_ift_ebp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ebp_(((knh_asmc_jmp_ift_ebp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFT");
#endif
	pc += KNH_ASMC_JMP_IFT_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFT__SFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP_IFT__sfp__dump(ctx, (knh_asmc_jmp_ift_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFT
		VM_JMP_IFT(ctx, pc += ((knh_asmc_jmp_ift_sfp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], sfp_(((knh_asmc_jmp_ift_sfp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFT");
#endif
	pc += KNH_ASMC_JMP_IFT_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFT__OFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP_IFT__ofp__dump(ctx, (knh_asmc_jmp_ift_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFT
		VM_JMP_IFT(ctx, pc += ((knh_asmc_jmp_ift_ofp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ofp_(((knh_asmc_jmp_ift_ofp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFT");
#endif
	pc += KNH_ASMC_JMP_IFT_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFT__OIDX:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP_IFT__OIDX__dump(ctx, (knh_asmc_jmp_ift_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFT__OIDX
		VM_JMP_IFT__OIDX(ctx, pc += ((knh_asmc_jmp_ift_oidx_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], OBJ_(((knh_asmc_jmp_ift_oidx_t*)pc)->a2), u1_(((knh_asmc_jmp_ift_oidx_t*)pc)->a3));
#else
		DEBUG("TODO: VM_JMP_IFT__OIDX");
#endif
	pc += KNH_ASMC_JMP_IFT_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFF__EBP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP_IFF__ebp__dump(ctx, (knh_asmc_jmp_iff_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFF
		VM_JMP_IFF(ctx, pc += ((knh_asmc_jmp_iff_ebp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ebp_(((knh_asmc_jmp_iff_ebp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFF");
#endif
	pc += KNH_ASMC_JMP_IFF_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFF__SFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP_IFF__sfp__dump(ctx, (knh_asmc_jmp_iff_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFF
		VM_JMP_IFF(ctx, pc += ((knh_asmc_jmp_iff_sfp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], sfp_(((knh_asmc_jmp_iff_sfp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFF");
#endif
	pc += KNH_ASMC_JMP_IFF_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFF__OFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP_IFF__ofp__dump(ctx, (knh_asmc_jmp_iff_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFF
		VM_JMP_IFF(ctx, pc += ((knh_asmc_jmp_iff_ofp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ofp_(((knh_asmc_jmp_iff_ofp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFF");
#endif
	pc += KNH_ASMC_JMP_IFF_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFF__OIDX:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP_IFF__OIDX__dump(ctx, (knh_asmc_jmp_iff_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFF__OIDX
		VM_JMP_IFF__OIDX(ctx, pc += ((knh_asmc_jmp_iff_oidx_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], OBJ_(((knh_asmc_jmp_iff_oidx_t*)pc)->a2), u1_(((knh_asmc_jmp_iff_oidx_t*)pc)->a3));
#else
		DEBUG("TODO: VM_JMP_IFF__OIDX");
#endif
	pc += KNH_ASMC_JMP_IFF_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFNUL__EBP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP_IFNUL__ebp__dump(ctx, (knh_asmc_jmp_ifnul_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFNUL
		VM_JMP_IFNUL(ctx, pc += ((knh_asmc_jmp_ifnul_ebp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ebp_(((knh_asmc_jmp_ifnul_ebp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFNUL");
#endif
	pc += KNH_ASMC_JMP_IFNUL_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFNUL__SFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP_IFNUL__sfp__dump(ctx, (knh_asmc_jmp_ifnul_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFNUL
		VM_JMP_IFNUL(ctx, pc += ((knh_asmc_jmp_ifnul_sfp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], sfp_(((knh_asmc_jmp_ifnul_sfp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFNUL");
#endif
	pc += KNH_ASMC_JMP_IFNUL_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFNUL__OFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP_IFNUL__ofp__dump(ctx, (knh_asmc_jmp_ifnul_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFNUL
		VM_JMP_IFNUL(ctx, pc += ((knh_asmc_jmp_ifnul_ofp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ofp_(((knh_asmc_jmp_ifnul_ofp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFNUL");
#endif
	pc += KNH_ASMC_JMP_IFNUL_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFNUL__OIDX:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP_IFNUL__OIDX__dump(ctx, (knh_asmc_jmp_ifnul_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFNUL__OIDX
		VM_JMP_IFNUL__OIDX(ctx, pc += ((knh_asmc_jmp_ifnul_oidx_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], OBJ_(((knh_asmc_jmp_ifnul_oidx_t*)pc)->a2), u1_(((knh_asmc_jmp_ifnul_oidx_t*)pc)->a3));
#else
		DEBUG("TODO: VM_JMP_IFNUL__OIDX");
#endif
	pc += KNH_ASMC_JMP_IFNUL_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFNONUL__EBP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP_IFNONUL__ebp__dump(ctx, (knh_asmc_jmp_ifnonul_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFNONUL
		VM_JMP_IFNONUL(ctx, pc += ((knh_asmc_jmp_ifnonul_ebp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ebp_(((knh_asmc_jmp_ifnonul_ebp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFNONUL");
#endif
	pc += KNH_ASMC_JMP_IFNONUL_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFNONUL__SFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP_IFNONUL__sfp__dump(ctx, (knh_asmc_jmp_ifnonul_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFNONUL
		VM_JMP_IFNONUL(ctx, pc += ((knh_asmc_jmp_ifnonul_sfp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], sfp_(((knh_asmc_jmp_ifnonul_sfp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFNONUL");
#endif
	pc += KNH_ASMC_JMP_IFNONUL_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFNONUL__OFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP_IFNONUL__ofp__dump(ctx, (knh_asmc_jmp_ifnonul_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFNONUL
		VM_JMP_IFNONUL(ctx, pc += ((knh_asmc_jmp_ifnonul_ofp_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], ofp_(((knh_asmc_jmp_ifnonul_ofp_t*)pc)->a2));
#else
		DEBUG("TODO: VM_JMP_IFNONUL");
#endif
	pc += KNH_ASMC_JMP_IFNONUL_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_JMP_IFNONUL__OIDX:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_JMP_IFNONUL__OIDX__dump(ctx, (knh_asmc_jmp_ifnonul_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_JMP_IFNONUL__OIDX
		VM_JMP_IFNONUL__OIDX(ctx, pc += ((knh_asmc_jmp_ifnonul_oidx_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], OBJ_(((knh_asmc_jmp_ifnonul_oidx_t*)pc)->a2), u1_(((knh_asmc_jmp_ifnonul_oidx_t*)pc)->a3));
#else
		DEBUG("TODO: VM_JMP_IFNONUL__OIDX");
#endif
	pc += KNH_ASMC_JMP_IFNONUL_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_ITER:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_ITER__dump(ctx, (knh_asmc_iter_t*)pc, 0, StdOut);
#endif
#ifdef VM_ITER
		VM_ITER(ctx, c2_(((knh_asmc_iter_t*)pc)->a1), sfp_(((knh_asmc_iter_t*)pc)->a2));
#else
		DEBUG("TODO: VM_ITER");
#endif
	pc += KNH_ASMC_ITER_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_FOREACH:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_FOREACH__dump(ctx, (knh_asmc_foreach_t*)pc, 0, StdOut);
#endif
#ifdef VM_FOREACH
		VM_FOREACH(ctx, pc += ((knh_asmc_foreach_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], c2_(((knh_asmc_foreach_t*)pc)->a2), sfp_(((knh_asmc_foreach_t*)pc)->a3), sfp_(((knh_asmc_foreach_t*)pc)->a4));
#else
		DEBUG("TODO: VM_FOREACH");
#endif
	pc += KNH_ASMC_FOREACH_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_TRY_BEGIN:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_TRY_BEGIN__dump(ctx, (knh_asmc_try_begin_t*)pc, 0, StdOut);
#endif
#ifdef VM_TRY_BEGIN
		VM_TRY_BEGIN(ctx, pc += ((knh_asmc_try_begin_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], sfp_(((knh_asmc_try_begin_t*)pc)->a2), sfp_(((knh_asmc_try_begin_t*)pc)->a3));
#else
		DEBUG("TODO: VM_TRY_BEGIN");
#endif
	pc += KNH_ASMC_TRY_BEGIN_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_TRY_END:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_TRY_END__dump(ctx, (knh_asmc_try_end_t*)pc, 0, StdOut);
#endif
#ifdef VM_TRY_END
		VM_TRY_END(ctx, sfp_(((knh_asmc_try_end_t*)pc)->a1));
#else
		DEBUG("TODO: VM_TRY_END");
#endif
	pc += KNH_ASMC_TRY_END_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_CATCH:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_CATCH__dump(ctx, (knh_asmc_catch_t*)pc, 0, StdOut);
#endif
#ifdef VM_CATCH
		VM_CATCH(ctx, pc += ((knh_asmc_catch_t*)pc)->a1, *globalMachineToJump[PCT_(pc)], e2_(((knh_asmc_catch_t*)pc)->a2), sfp_(((knh_asmc_catch_t*)pc)->a3));
#else
		DEBUG("TODO: VM_CATCH");
#endif
	pc += KNH_ASMC_CATCH_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_THROW__EBP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_THROW__ebp__dump(ctx, (knh_asmc_throw_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_THROW
		VM_THROW(ctx, ebp_(((knh_asmc_throw_ebp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_THROW");
#endif
	pc += KNH_ASMC_THROW_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_THROW__SFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_THROW__sfp__dump(ctx, (knh_asmc_throw_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_THROW
		VM_THROW(ctx, sfp_(((knh_asmc_throw_sfp_t*)pc)->a1));
#else
		DEBUG("TODO: VM_THROW");
#endif
	pc += KNH_ASMC_THROW_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_THROW__OBJ:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_THROW__OBJ__dump(ctx, (knh_asmc_throw_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_THROW
		VM_THROW(ctx, OBJ_(((knh_asmc_throw_obj_t*)pc)->a1));
#else
		DEBUG("TODO: VM_THROW");
#endif
	pc += KNH_ASMC_THROW_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PRINT__EBP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_PRINT__ebp__dump(ctx, (knh_asmc_print_ebp_t*)pc, 0, StdOut);
#endif
#ifdef VM_PRINT
		VM_PRINT(ctx, u2_(((knh_asmc_print_ebp_t*)pc)->a1), mn_(((knh_asmc_print_ebp_t*)pc)->a2), ebp_(((knh_asmc_print_ebp_t*)pc)->a3));
#else
		DEBUG("TODO: VM_PRINT");
#endif
	pc += KNH_ASMC_PRINT_ebp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PRINT__SFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_PRINT__sfp__dump(ctx, (knh_asmc_print_sfp_t*)pc, 0, StdOut);
#endif
#ifdef VM_PRINT
		VM_PRINT(ctx, u2_(((knh_asmc_print_sfp_t*)pc)->a1), mn_(((knh_asmc_print_sfp_t*)pc)->a2), sfp_(((knh_asmc_print_sfp_t*)pc)->a3));
#else
		DEBUG("TODO: VM_PRINT");
#endif
	pc += KNH_ASMC_PRINT_sfp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PRINT__OFP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_PRINT__ofp__dump(ctx, (knh_asmc_print_ofp_t*)pc, 0, StdOut);
#endif
#ifdef VM_PRINT
		VM_PRINT(ctx, u2_(((knh_asmc_print_ofp_t*)pc)->a1), mn_(((knh_asmc_print_ofp_t*)pc)->a2), ofp_(((knh_asmc_print_ofp_t*)pc)->a3));
#else
		DEBUG("TODO: VM_PRINT");
#endif
	pc += KNH_ASMC_PRINT_ofp_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PRINT__OBJ:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_PRINT__OBJ__dump(ctx, (knh_asmc_print_obj_t*)pc, 0, StdOut);
#endif
#ifdef VM_PRINT
		VM_PRINT(ctx, u2_(((knh_asmc_print_obj_t*)pc)->a1), mn_(((knh_asmc_print_obj_t*)pc)->a2), OBJ_(((knh_asmc_print_obj_t*)pc)->a3));
#else
		DEBUG("TODO: VM_PRINT");
#endif
	pc += KNH_ASMC_PRINT_OBJ_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_PRINT__OIDX:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_PRINT__OIDX__dump(ctx, (knh_asmc_print_oidx_t*)pc, 0, StdOut);
#endif
#ifdef VM_PRINT__OIDX
		VM_PRINT__OIDX(ctx, u2_(((knh_asmc_print_oidx_t*)pc)->a1), mn_(((knh_asmc_print_oidx_t*)pc)->a2), OBJ_(((knh_asmc_print_oidx_t*)pc)->a3), u1_(((knh_asmc_print_oidx_t*)pc)->a4));
#else
		DEBUG("TODO: VM_PRINT__OIDX");
#endif
	pc += KNH_ASMC_PRINT_OIDX_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_DIAGNOSE:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_DIAGNOSE__dump(ctx, (knh_asmc_diagnose_t*)pc, 0, StdOut);
#endif
#ifdef VM_DIAGNOSE
		VM_DIAGNOSE(ctx, u1_(((knh_asmc_diagnose_t*)pc)->a1));
#else
		DEBUG("TODO: VM_DIAGNOSE");
#endif
	pc += KNH_ASMC_DIAGNOSE_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_STACKDUMP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_STACKDUMP__dump(ctx, (knh_asmc_stackdump_t*)pc, 0, StdOut);
#endif
#ifdef VM_STACKDUMP
		VM_STACKDUMP(ctx);
#else
		DEBUG("TODO: VM_STACKDUMP");
#endif
	pc += KNH_ASMC_STACKDUMP_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_ASMC_NOP:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_NOP__dump(ctx, (knh_asmc_nop_t*)pc, 0, StdOut);
#endif
#ifdef VM_NOP
		VM_NOP(ctx);
#else
		DEBUG("TODO: VM_NOP");
#endif
	pc += KNH_ASMC_NOP_SIZ;
	goto *globalMachineToJump[PCT_(pc)];

	L_UNKNOWN:;
	DEBUG("Broken code??");
	DEBUG_ASSERT(pc == NULL);
	return;
}

#ifdef __cplusplus
}
#endif
