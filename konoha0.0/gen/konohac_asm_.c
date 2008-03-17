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

/* ======================================================================== */
/* [Cmpl] */

void KNH_ASM_RET_VOID(Ctx *ctx, Cmpl *b)
{
	knh_asmc_ret_void_t *bw = (knh_asmc_ret_void_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_RET_VOID_SIZ);
	bw->code = ASMC_RET_VOID;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_RET(Ctx *ctx, Cmpl *b, knh_asmv_t v)
{
#ifdef ASMC_RET__EBP
	if(v.potype == KNH_ASMV_EBP) {
		KNH_ASM_RET__ebp(ctx, b, v.index);
		return;
	}
#endif/*ASMC_RET__EBP*/
#ifdef ASMC_RET__SFP
	if(v.potype == KNH_ASMV_SFP) {
		KNH_ASM_RET__sfp(ctx, b, v.index);
		return;
	}
#endif/*ASMC_RET__SFP*/
#ifdef ASMC_RET__OFP
	if(v.potype == KNH_ASMV_OFP) {
		KNH_ASM_RET__ofp(ctx, b, v.index);
		return;
	}
#endif/*ASMC_RET__OFP*/
#ifdef ASMC_RET__OBJ
	if(v.potype == KNH_ASMV_OBJ) {
		KNH_ASM_RET__OBJ(ctx, b, v.value);
		return;
	}
#endif/*ASMC_RET__OBJ*/
#ifdef ASMC_RET__OIDX
	if(v.potype == KNH_ASMV_OIDX) {
		KNH_ASM_RET__OIDX(ctx, b, v.value, v.index);
		return;
	}
#endif/*ASMC_RET__OIDX*/
	DEBUG("unsupported asmv.potype=%d", v.potype);
	KNH_ASSERT(ctx == NULL); /* stop here!!*/
}
/* ------------------------------------------------------------------------ */

void KNH_ASM_RET__ebp(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1)
{
	knh_asmc_ret_ebp_t *bw = (knh_asmc_ret_ebp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_RET_ebp_SIZ);
	bw->code = ASMC_RET__EBP;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_RET__sfp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1)
{
	knh_asmc_ret_sfp_t *bw = (knh_asmc_ret_sfp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_RET_sfp_SIZ);
	bw->code = ASMC_RET__SFP;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_RET__ofp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1)
{
	knh_asmc_ret_ofp_t *bw = (knh_asmc_ret_ofp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_RET_ofp_SIZ);
	bw->code = ASMC_RET__OFP;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_RET__OBJ(Ctx *ctx, Cmpl *b, Object* a1)
{
	knh_asmc_ret_obj_t *bw = (knh_asmc_ret_obj_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_RET_OBJ_SIZ);
	bw->code = ASMC_RET__OBJ;
	bw->a1 = a1;
	knh_Object_refc_inc(bw->a1);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_RET__OIDX(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2)
{
	knh_asmc_ret_oidx_t *bw = (knh_asmc_ret_oidx_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_RET_OIDX_SIZ);
	bw->code = ASMC_RET__OIDX;
	bw->a1 = a1;
	knh_Object_refc_inc(bw->a1);
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVE(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1, knh_asmv_t v)
{
#ifdef ASMC_MOVE__EBP
	if(v.potype == KNH_ASMV_EBP) {
		KNH_ASM_MOVE__ebp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_MOVE__EBP*/
#ifdef ASMC_MOVE__SFP
	if(v.potype == KNH_ASMV_SFP) {
		KNH_ASM_MOVE__sfp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_MOVE__SFP*/
#ifdef ASMC_MOVE__OFP
	if(v.potype == KNH_ASMV_OFP) {
		KNH_ASM_MOVE__ofp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_MOVE__OFP*/
#ifdef ASMC_MOVE__OBJ
	if(v.potype == KNH_ASMV_OBJ) {
		KNH_ASM_MOVE__OBJ(ctx, b, a1, v.value);
		return;
	}
#endif/*ASMC_MOVE__OBJ*/
#ifdef ASMC_MOVE__OIDX
	if(v.potype == KNH_ASMV_OIDX) {
		KNH_ASM_MOVE__OIDX(ctx, b, a1, v.value, v.index);
		return;
	}
#endif/*ASMC_MOVE__OIDX*/
	DEBUG("unsupported asmv.potype=%d", v.potype);
	KNH_ASSERT(ctx == NULL); /* stop here!!*/
}
/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVE__ebp(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1, knh_vmc_i1_t a2)
{
	knh_asmc_move_ebp_t *bw = (knh_asmc_move_ebp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVE_ebp_SIZ);
	bw->code = ASMC_MOVE__EBP;
	bw->a1 = a1;
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVE__sfp(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_move_sfp_t *bw = (knh_asmc_move_sfp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVE_sfp_SIZ);
	bw->code = ASMC_MOVE__SFP;
	bw->a1 = a1;
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVE__ofp(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_move_ofp_t *bw = (knh_asmc_move_ofp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVE_ofp_SIZ);
	bw->code = ASMC_MOVE__OFP;
	bw->a1 = a1;
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVE__OBJ(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1, Object* a2)
{
	knh_asmc_move_obj_t *bw = (knh_asmc_move_obj_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVE_OBJ_SIZ);
	bw->code = ASMC_MOVE__OBJ;
	bw->a1 = a1;
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVE__OIDX(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1, Object* a2, knh_vmc_u1_t a3)
{
	knh_asmc_move_oidx_t *bw = (knh_asmc_move_oidx_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVE_OIDX_SIZ);
	bw->code = ASMC_MOVE__OIDX;
	bw->a1 = a1;
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVS(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_asmv_t v)
{
#ifdef ASMC_MOVS__EBP
	if(v.potype == KNH_ASMV_EBP) {
		KNH_ASM_MOVS__ebp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_MOVS__EBP*/
#ifdef ASMC_MOVS__SFP
	if(v.potype == KNH_ASMV_SFP) {
		KNH_ASM_MOVS__sfp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_MOVS__SFP*/
#ifdef ASMC_MOVS__OFP
	if(v.potype == KNH_ASMV_OFP) {
		KNH_ASM_MOVS__ofp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_MOVS__OFP*/
#ifdef ASMC_MOVS__OBJ
	if(v.potype == KNH_ASMV_OBJ) {
		KNH_ASM_MOVS__OBJ(ctx, b, a1, v.value);
		return;
	}
#endif/*ASMC_MOVS__OBJ*/
#ifdef ASMC_MOVS__OIDX
	if(v.potype == KNH_ASMV_OIDX) {
		KNH_ASM_MOVS__OIDX(ctx, b, a1, v.value, v.index);
		return;
	}
#endif/*ASMC_MOVS__OIDX*/
	DEBUG("unsupported asmv.potype=%d", v.potype);
	KNH_ASSERT(ctx == NULL); /* stop here!!*/
}
/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVS__ebp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_vmc_i1_t a2)
{
	knh_asmc_movs_ebp_t *bw = (knh_asmc_movs_ebp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVS_ebp_SIZ);
	bw->code = ASMC_MOVS__EBP;
	bw->a1 = a1;
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVS__sfp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_movs_sfp_t *bw = (knh_asmc_movs_sfp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVS_sfp_SIZ);
	bw->code = ASMC_MOVS__SFP;
	bw->a1 = a1;
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVS__ofp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_movs_ofp_t *bw = (knh_asmc_movs_ofp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVS_ofp_SIZ);
	bw->code = ASMC_MOVS__OFP;
	bw->a1 = a1;
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVS__OBJ(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, Object* a2)
{
	knh_asmc_movs_obj_t *bw = (knh_asmc_movs_obj_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVS_OBJ_SIZ);
	bw->code = ASMC_MOVS__OBJ;
	bw->a1 = a1;
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVS__OIDX(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, Object* a2, knh_vmc_u1_t a3)
{
	knh_asmc_movs_oidx_t *bw = (knh_asmc_movs_oidx_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVS_OIDX_SIZ);
	bw->code = ASMC_MOVS__OIDX;
	bw->a1 = a1;
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVO(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_asmv_t v)
{
#ifdef ASMC_MOVO__EBP
	if(v.potype == KNH_ASMV_EBP) {
		KNH_ASM_MOVO__ebp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_MOVO__EBP*/
#ifdef ASMC_MOVO__SFP
	if(v.potype == KNH_ASMV_SFP) {
		KNH_ASM_MOVO__sfp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_MOVO__SFP*/
#ifdef ASMC_MOVO__OFP
	if(v.potype == KNH_ASMV_OFP) {
		KNH_ASM_MOVO__ofp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_MOVO__OFP*/
#ifdef ASMC_MOVO__OBJ
	if(v.potype == KNH_ASMV_OBJ) {
		KNH_ASM_MOVO__OBJ(ctx, b, a1, v.value);
		return;
	}
#endif/*ASMC_MOVO__OBJ*/
#ifdef ASMC_MOVO__OIDX
	if(v.potype == KNH_ASMV_OIDX) {
		KNH_ASM_MOVO__OIDX(ctx, b, a1, v.value, v.index);
		return;
	}
#endif/*ASMC_MOVO__OIDX*/
	DEBUG("unsupported asmv.potype=%d", v.potype);
	KNH_ASSERT(ctx == NULL); /* stop here!!*/
}
/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVO__ebp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_vmc_i1_t a2)
{
	knh_asmc_movo_ebp_t *bw = (knh_asmc_movo_ebp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVO_ebp_SIZ);
	bw->code = ASMC_MOVO__EBP;
	bw->a1 = a1;
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVO__sfp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_movo_sfp_t *bw = (knh_asmc_movo_sfp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVO_sfp_SIZ);
	bw->code = ASMC_MOVO__SFP;
	bw->a1 = a1;
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVO__ofp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_movo_ofp_t *bw = (knh_asmc_movo_ofp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVO_ofp_SIZ);
	bw->code = ASMC_MOVO__OFP;
	bw->a1 = a1;
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVO__OBJ(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, Object* a2)
{
	knh_asmc_movo_obj_t *bw = (knh_asmc_movo_obj_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVO_OBJ_SIZ);
	bw->code = ASMC_MOVO__OBJ;
	bw->a1 = a1;
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVO__OIDX(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, Object* a2, knh_vmc_u1_t a3)
{
	knh_asmc_movo_oidx_t *bw = (knh_asmc_movo_oidx_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVO_OIDX_SIZ);
	bw->code = ASMC_MOVO__OIDX;
	bw->a1 = a1;
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVOI(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2, knh_asmv_t v)
{
#ifdef ASMC_MOVOI__EBP
	if(v.potype == KNH_ASMV_EBP) {
		KNH_ASM_MOVOI__ebp(ctx, b, a1, a2, v.index);
		return;
	}
#endif/*ASMC_MOVOI__EBP*/
#ifdef ASMC_MOVOI__SFP
	if(v.potype == KNH_ASMV_SFP) {
		KNH_ASM_MOVOI__sfp(ctx, b, a1, a2, v.index);
		return;
	}
#endif/*ASMC_MOVOI__SFP*/
#ifdef ASMC_MOVOI__OFP
	if(v.potype == KNH_ASMV_OFP) {
		KNH_ASM_MOVOI__ofp(ctx, b, a1, a2, v.index);
		return;
	}
#endif/*ASMC_MOVOI__OFP*/
#ifdef ASMC_MOVOI__OBJ
	if(v.potype == KNH_ASMV_OBJ) {
		KNH_ASM_MOVOI__OBJ(ctx, b, a1, a2, v.value);
		return;
	}
#endif/*ASMC_MOVOI__OBJ*/
#ifdef ASMC_MOVOI__OIDX
	if(v.potype == KNH_ASMV_OIDX) {
		KNH_ASM_MOVOI__OIDX(ctx, b, a1, a2, v.value, v.index);
		return;
	}
#endif/*ASMC_MOVOI__OIDX*/
	DEBUG("unsupported asmv.potype=%d", v.potype);
	KNH_ASSERT(ctx == NULL); /* stop here!!*/
}
/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVOI__ebp(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2, knh_vmc_i1_t a3)
{
	knh_asmc_movoi_ebp_t *bw = (knh_asmc_movoi_ebp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVOI_ebp_SIZ);
	bw->code = ASMC_MOVOI__EBP;
	bw->a1 = a1;
	knh_Object_refc_inc(bw->a1);
	bw->a2 = a2;
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVOI__sfp(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2, knh_vmc_u1_t a3)
{
	knh_asmc_movoi_sfp_t *bw = (knh_asmc_movoi_sfp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVOI_sfp_SIZ);
	bw->code = ASMC_MOVOI__SFP;
	bw->a1 = a1;
	knh_Object_refc_inc(bw->a1);
	bw->a2 = a2;
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVOI__ofp(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2, knh_vmc_u1_t a3)
{
	knh_asmc_movoi_ofp_t *bw = (knh_asmc_movoi_ofp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVOI_ofp_SIZ);
	bw->code = ASMC_MOVOI__OFP;
	bw->a1 = a1;
	knh_Object_refc_inc(bw->a1);
	bw->a2 = a2;
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVOI__OBJ(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2, Object* a3)
{
	knh_asmc_movoi_obj_t *bw = (knh_asmc_movoi_obj_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVOI_OBJ_SIZ);
	bw->code = ASMC_MOVOI__OBJ;
	bw->a1 = a1;
	knh_Object_refc_inc(bw->a1);
	bw->a2 = a2;
	bw->a3 = a3;
	knh_Object_refc_inc(bw->a3);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVOI__OIDX(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2, Object* a3, knh_vmc_u1_t a4)
{
	knh_asmc_movoi_oidx_t *bw = (knh_asmc_movoi_oidx_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVOI_OIDX_SIZ);
	bw->code = ASMC_MOVOI__OIDX;
	bw->a1 = a1;
	knh_Object_refc_inc(bw->a1);
	bw->a2 = a2;
	bw->a3 = a3;
	knh_Object_refc_inc(bw->a3);
	bw->a4 = a4;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MOVSFP_IFNUL(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, Object* a2)
{
	knh_asmc_movsfp_ifnul_t *bw = (knh_asmc_movsfp_ifnul_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MOVSFP_IFNUL_SIZ);
	bw->code = ASMC_MOVSFP_IFNUL;
	bw->a1 = a1;
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PUSH(Ctx *ctx, Cmpl *b, knh_asmv_t v)
{
#ifdef ASMC_PUSH__EBP
	if(v.potype == KNH_ASMV_EBP) {
		KNH_ASM_PUSH__ebp(ctx, b, v.index);
		return;
	}
#endif/*ASMC_PUSH__EBP*/
#ifdef ASMC_PUSH__SFP
	if(v.potype == KNH_ASMV_SFP) {
		KNH_ASM_PUSH__sfp(ctx, b, v.index);
		return;
	}
#endif/*ASMC_PUSH__SFP*/
#ifdef ASMC_PUSH__OFP
	if(v.potype == KNH_ASMV_OFP) {
		KNH_ASM_PUSH__ofp(ctx, b, v.index);
		return;
	}
#endif/*ASMC_PUSH__OFP*/
#ifdef ASMC_PUSH__OBJ
	if(v.potype == KNH_ASMV_OBJ) {
		KNH_ASM_PUSH__OBJ(ctx, b, v.value);
		return;
	}
#endif/*ASMC_PUSH__OBJ*/
#ifdef ASMC_PUSH__OIDX
	if(v.potype == KNH_ASMV_OIDX) {
		KNH_ASM_PUSH__OIDX(ctx, b, v.value, v.index);
		return;
	}
#endif/*ASMC_PUSH__OIDX*/
	DEBUG("unsupported asmv.potype=%d", v.potype);
	KNH_ASSERT(ctx == NULL); /* stop here!!*/
}
/* ------------------------------------------------------------------------ */

void KNH_ASM_PUSH__sfp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1)
{
	knh_asmc_push_sfp_t *bw = (knh_asmc_push_sfp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_PUSH_sfp_SIZ);
	bw->code = ASMC_PUSH__SFP;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PUSH__ofp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1)
{
	knh_asmc_push_ofp_t *bw = (knh_asmc_push_ofp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_PUSH_ofp_SIZ);
	bw->code = ASMC_PUSH__OFP;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PUSH__OBJ(Ctx *ctx, Cmpl *b, Object* a1)
{
	knh_asmc_push_obj_t *bw = (knh_asmc_push_obj_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_PUSH_OBJ_SIZ);
	bw->code = ASMC_PUSH__OBJ;
	bw->a1 = a1;
	knh_Object_refc_inc(bw->a1);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PUSH__OIDX(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2)
{
	knh_asmc_push_oidx_t *bw = (knh_asmc_push_oidx_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_PUSH_OIDX_SIZ);
	bw->code = ASMC_PUSH__OIDX;
	bw->a1 = a1;
	knh_Object_refc_inc(bw->a1);
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PUTI(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1)
{
	knh_asmc_puti_t *bw = (knh_asmc_puti_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_PUTI_SIZ);
	bw->code = ASMC_PUTI;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PUSH__MN(Ctx *ctx, Cmpl *b, knh_methodn_t a1)
{
	knh_asmc_push_mn_t *bw = (knh_asmc_push_mn_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_PUSH_MN_SIZ);
	bw->code = ASMC_PUSH__MN;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PUSH__DEF(Ctx *ctx, Cmpl *b, knh_class_t a1)
{
	knh_asmc_push_def_t *bw = (knh_asmc_push_def_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_PUSH_DEF_SIZ);
	bw->code = ASMC_PUSH__DEF;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_VARGS(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1)
{
	knh_asmc_vargs_t *bw = (knh_asmc_vargs_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_VARGS_SIZ);
	bw->code = ASMC_VARGS;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_SCALL(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1)
{
	knh_asmc_scall_t *bw = (knh_asmc_scall_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_SCALL_SIZ);
	bw->code = ASMC_SCALL;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_CALL(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1)
{
	knh_asmc_call_t *bw = (knh_asmc_call_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_CALL_SIZ);
	bw->code = ASMC_CALL;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_DCALL(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1)
{
	knh_asmc_dcall_t *bw = (knh_asmc_dcall_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_DCALL_SIZ);
	bw->code = ASMC_DCALL;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MCALL(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1)
{
	knh_asmc_mcall_t *bw = (knh_asmc_mcall_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MCALL_SIZ);
	bw->code = ASMC_MCALL;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_CALL_WM(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, Object* a2)
{
	knh_asmc_call_wm_t *bw = (knh_asmc_call_wm_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_CALL_WM_SIZ);
	bw->code = ASMC_CALL_WM;
	bw->a1 = a1;
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NCALL_WM(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, Object* a2)
{
	knh_asmc_ncall_wm_t *bw = (knh_asmc_ncall_wm_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_NCALL_WM_SIZ);
	bw->code = ASMC_NCALL_WM;
	bw->a1 = a1;
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NEW(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1, Object* a2, knh_vmc_u2_t a3, knh_class_t a4)
{
	knh_asmc_new_t *bw = (knh_asmc_new_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_NEW_SIZ);
	bw->code = ASMC_NEW;
	bw->a1 = a1;
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
	bw->a3 = a3;
	bw->a4 = a4;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NEWE(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1, Object* a2, knh_vmc_u2_t a3, knh_class_t a4)
{
	knh_asmc_newe_t *bw = (knh_asmc_newe_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_NEWE_SIZ);
	bw->code = ASMC_NEWE;
	bw->a1 = a1;
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
	bw->a3 = a3;
	bw->a4 = a4;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NEW__DEF(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_vmc_u2_t a2, knh_class_t a3)
{
	knh_asmc_new_def_t *bw = (knh_asmc_new_def_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_NEW_DEF_SIZ);
	bw->code = ASMC_NEW__DEF;
	bw->a1 = a1;
	bw->a2 = a2;
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MT(Ctx *ctx, Cmpl *b, knh_methodn_t a1)
{
	knh_asmc_mt_t *bw = (knh_asmc_mt_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MT_SIZ);
	bw->code = ASMC_MT;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MT__OPT(Ctx *ctx, Cmpl *b, knh_methodn_t a1, Object* a2)
{
	knh_asmc_mt_opt_t *bw = (knh_asmc_mt_opt_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MT_OPT_SIZ);
	bw->code = ASMC_MT__OPT;
	bw->a1 = a1;
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MAP(Ctx *ctx, Cmpl *b, knh_class_t a1)
{
	knh_asmc_map_t *bw = (knh_asmc_map_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MAP_SIZ);
	bw->code = ASMC_MAP;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MAPE(Ctx *ctx, Cmpl *b, knh_class_t a1)
{
	knh_asmc_mape_t *bw = (knh_asmc_mape_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MAPE_SIZ);
	bw->code = ASMC_MAPE;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MAP_WM(Ctx *ctx, Cmpl *b, Object* a1)
{
	knh_asmc_map_wm_t *bw = (knh_asmc_map_wm_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MAP_WM_SIZ);
	bw->code = ASMC_MAP_WM;
	bw->a1 = a1;
	knh_Object_refc_inc(bw->a1);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MAPE_WM(Ctx *ctx, Cmpl *b, Object* a1)
{
	knh_asmc_mape_wm_t *bw = (knh_asmc_mape_wm_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MAPE_WM_SIZ);
	bw->code = ASMC_MAPE_WM;
	bw->a1 = a1;
	knh_Object_refc_inc(bw->a1);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MAP2(Ctx *ctx, Cmpl *b, knh_class_t a1)
{
	knh_asmc_map2_t *bw = (knh_asmc_map2_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MAP2_SIZ);
	bw->code = ASMC_MAP2;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_MAP2E(Ctx *ctx, Cmpl *b, knh_class_t a1)
{
	knh_asmc_map2e_t *bw = (knh_asmc_map2e_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_MAP2E_SIZ);
	bw->code = ASMC_MAP2E;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_TYPECHK(Ctx *ctx, Cmpl *b, knh_class_t a1, knh_asmv_t v)
{
#ifdef ASMC_TYPECHK__EBP
	if(v.potype == KNH_ASMV_EBP) {
		KNH_ASM_TYPECHK__ebp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_TYPECHK__EBP*/
#ifdef ASMC_TYPECHK__SFP
	if(v.potype == KNH_ASMV_SFP) {
		KNH_ASM_TYPECHK__sfp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_TYPECHK__SFP*/
#ifdef ASMC_TYPECHK__OFP
	if(v.potype == KNH_ASMV_OFP) {
		KNH_ASM_TYPECHK__ofp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_TYPECHK__OFP*/
#ifdef ASMC_TYPECHK__OBJ
	if(v.potype == KNH_ASMV_OBJ) {
		KNH_ASM_TYPECHK__OBJ(ctx, b, a1, v.value);
		return;
	}
#endif/*ASMC_TYPECHK__OBJ*/
#ifdef ASMC_TYPECHK__OIDX
	if(v.potype == KNH_ASMV_OIDX) {
		KNH_ASM_TYPECHK__OIDX(ctx, b, a1, v.value, v.index);
		return;
	}
#endif/*ASMC_TYPECHK__OIDX*/
	DEBUG("unsupported asmv.potype=%d", v.potype);
	KNH_ASSERT(ctx == NULL); /* stop here!!*/
}
/* ------------------------------------------------------------------------ */

void KNH_ASM_TYPECHK__ebp(Ctx *ctx, Cmpl *b, knh_class_t a1, knh_vmc_i1_t a2)
{
	knh_asmc_typechk_ebp_t *bw = (knh_asmc_typechk_ebp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_TYPECHK_ebp_SIZ);
	bw->code = ASMC_TYPECHK__EBP;
	bw->a1 = a1;
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_TYPECHK__sfp(Ctx *ctx, Cmpl *b, knh_class_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_typechk_sfp_t *bw = (knh_asmc_typechk_sfp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_TYPECHK_sfp_SIZ);
	bw->code = ASMC_TYPECHK__SFP;
	bw->a1 = a1;
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_TYPECHK__ofp(Ctx *ctx, Cmpl *b, knh_class_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_typechk_ofp_t *bw = (knh_asmc_typechk_ofp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_TYPECHK_ofp_SIZ);
	bw->code = ASMC_TYPECHK__OFP;
	bw->a1 = a1;
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_TYPECHK__OBJ(Ctx *ctx, Cmpl *b, knh_class_t a1, Object* a2)
{
	knh_asmc_typechk_obj_t *bw = (knh_asmc_typechk_obj_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_TYPECHK_OBJ_SIZ);
	bw->code = ASMC_TYPECHK__OBJ;
	bw->a1 = a1;
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_TYPECHK__OIDX(Ctx *ctx, Cmpl *b, knh_class_t a1, Object* a2, knh_vmc_u1_t a3)
{
	knh_asmc_typechk_oidx_t *bw = (knh_asmc_typechk_oidx_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_TYPECHK_OIDX_SIZ);
	bw->code = ASMC_TYPECHK__OIDX;
	bw->a1 = a1;
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NULLCHK(Ctx *ctx, Cmpl *b, knh_asmv_t v)
{
#ifdef ASMC_NULLCHK__EBP
	if(v.potype == KNH_ASMV_EBP) {
		KNH_ASM_NULLCHK__ebp(ctx, b, v.index);
		return;
	}
#endif/*ASMC_NULLCHK__EBP*/
#ifdef ASMC_NULLCHK__SFP
	if(v.potype == KNH_ASMV_SFP) {
		KNH_ASM_NULLCHK__sfp(ctx, b, v.index);
		return;
	}
#endif/*ASMC_NULLCHK__SFP*/
#ifdef ASMC_NULLCHK__OFP
	if(v.potype == KNH_ASMV_OFP) {
		KNH_ASM_NULLCHK__ofp(ctx, b, v.index);
		return;
	}
#endif/*ASMC_NULLCHK__OFP*/
#ifdef ASMC_NULLCHK__OBJ
	if(v.potype == KNH_ASMV_OBJ) {
		KNH_ASM_NULLCHK__OBJ(ctx, b, v.value);
		return;
	}
#endif/*ASMC_NULLCHK__OBJ*/
#ifdef ASMC_NULLCHK__OIDX
	if(v.potype == KNH_ASMV_OIDX) {
		KNH_ASM_NULLCHK__OIDX(ctx, b, v.value, v.index);
		return;
	}
#endif/*ASMC_NULLCHK__OIDX*/
	DEBUG("unsupported asmv.potype=%d", v.potype);
	KNH_ASSERT(ctx == NULL); /* stop here!!*/
}
/* ------------------------------------------------------------------------ */

void KNH_ASM_NULLCHK__ebp(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1)
{
	knh_asmc_nullchk_ebp_t *bw = (knh_asmc_nullchk_ebp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_NULLCHK_ebp_SIZ);
	bw->code = ASMC_NULLCHK__EBP;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NULLCHK__sfp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1)
{
	knh_asmc_nullchk_sfp_t *bw = (knh_asmc_nullchk_sfp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_NULLCHK_sfp_SIZ);
	bw->code = ASMC_NULLCHK__SFP;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NULLCHK__ofp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1)
{
	knh_asmc_nullchk_ofp_t *bw = (knh_asmc_nullchk_ofp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_NULLCHK_ofp_SIZ);
	bw->code = ASMC_NULLCHK__OFP;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NULLCHK__OBJ(Ctx *ctx, Cmpl *b, Object* a1)
{
	knh_asmc_nullchk_obj_t *bw = (knh_asmc_nullchk_obj_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_NULLCHK_OBJ_SIZ);
	bw->code = ASMC_NULLCHK__OBJ;
	bw->a1 = a1;
	knh_Object_refc_inc(bw->a1);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NULLCHK__OIDX(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2)
{
	knh_asmc_nullchk_oidx_t *bw = (knh_asmc_nullchk_oidx_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_NULLCHK_OIDX_SIZ);
	bw->code = ASMC_NULLCHK__OIDX;
	bw->a1 = a1;
	knh_Object_refc_inc(bw->a1);
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP(Ctx *ctx, Cmpl *b, knh_bytes_t a1)
{
	knh_asmc_jmp_t *bw = (knh_asmc_jmp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_SIZ);
	bw->code = ASMC_JMP;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_SKIP(Ctx *ctx, Cmpl *b, knh_bytes_t a1)
{
	knh_asmc_skip_t *bw = (knh_asmc_skip_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_SKIP_SIZ);
	bw->code = ASMC_SKIP;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFT(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_asmv_t v)
{
#ifdef ASMC_JMP_IFT__EBP
	if(v.potype == KNH_ASMV_EBP) {
		KNH_ASM_JMP_IFT__ebp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_JMP_IFT__EBP*/
#ifdef ASMC_JMP_IFT__SFP
	if(v.potype == KNH_ASMV_SFP) {
		KNH_ASM_JMP_IFT__sfp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_JMP_IFT__SFP*/
#ifdef ASMC_JMP_IFT__OFP
	if(v.potype == KNH_ASMV_OFP) {
		KNH_ASM_JMP_IFT__ofp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_JMP_IFT__OFP*/
#ifdef ASMC_JMP_IFT__OBJ
	if(v.potype == KNH_ASMV_OBJ) {
		KNH_ASM_JMP_IFT__OBJ(ctx, b, a1, v.value);
		return;
	}
#endif/*ASMC_JMP_IFT__OBJ*/
#ifdef ASMC_JMP_IFT__OIDX
	if(v.potype == KNH_ASMV_OIDX) {
		KNH_ASM_JMP_IFT__OIDX(ctx, b, a1, v.value, v.index);
		return;
	}
#endif/*ASMC_JMP_IFT__OIDX*/
	DEBUG("unsupported asmv.potype=%d", v.potype);
	KNH_ASSERT(ctx == NULL); /* stop here!!*/
}
/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFT__ebp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_i1_t a2)
{
	knh_asmc_jmp_ift_ebp_t *bw = (knh_asmc_jmp_ift_ebp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_IFT_ebp_SIZ);
	bw->code = ASMC_JMP_IFT__EBP;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFT__sfp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_jmp_ift_sfp_t *bw = (knh_asmc_jmp_ift_sfp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_IFT_sfp_SIZ);
	bw->code = ASMC_JMP_IFT__SFP;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFT__ofp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_jmp_ift_ofp_t *bw = (knh_asmc_jmp_ift_ofp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_IFT_ofp_SIZ);
	bw->code = ASMC_JMP_IFT__OFP;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFT__OIDX(Ctx *ctx, Cmpl *b, knh_bytes_t a1, Object* a2, knh_vmc_u1_t a3)
{
	knh_asmc_jmp_ift_oidx_t *bw = (knh_asmc_jmp_ift_oidx_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_IFT_OIDX_SIZ);
	bw->code = ASMC_JMP_IFT__OIDX;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFF(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_asmv_t v)
{
#ifdef ASMC_JMP_IFF__EBP
	if(v.potype == KNH_ASMV_EBP) {
		KNH_ASM_JMP_IFF__ebp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_JMP_IFF__EBP*/
#ifdef ASMC_JMP_IFF__SFP
	if(v.potype == KNH_ASMV_SFP) {
		KNH_ASM_JMP_IFF__sfp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_JMP_IFF__SFP*/
#ifdef ASMC_JMP_IFF__OFP
	if(v.potype == KNH_ASMV_OFP) {
		KNH_ASM_JMP_IFF__ofp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_JMP_IFF__OFP*/
#ifdef ASMC_JMP_IFF__OBJ
	if(v.potype == KNH_ASMV_OBJ) {
		KNH_ASM_JMP_IFF__OBJ(ctx, b, a1, v.value);
		return;
	}
#endif/*ASMC_JMP_IFF__OBJ*/
#ifdef ASMC_JMP_IFF__OIDX
	if(v.potype == KNH_ASMV_OIDX) {
		KNH_ASM_JMP_IFF__OIDX(ctx, b, a1, v.value, v.index);
		return;
	}
#endif/*ASMC_JMP_IFF__OIDX*/
	DEBUG("unsupported asmv.potype=%d", v.potype);
	KNH_ASSERT(ctx == NULL); /* stop here!!*/
}
/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFF__ebp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_i1_t a2)
{
	knh_asmc_jmp_iff_ebp_t *bw = (knh_asmc_jmp_iff_ebp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_IFF_ebp_SIZ);
	bw->code = ASMC_JMP_IFF__EBP;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFF__sfp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_jmp_iff_sfp_t *bw = (knh_asmc_jmp_iff_sfp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_IFF_sfp_SIZ);
	bw->code = ASMC_JMP_IFF__SFP;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFF__ofp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_jmp_iff_ofp_t *bw = (knh_asmc_jmp_iff_ofp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_IFF_ofp_SIZ);
	bw->code = ASMC_JMP_IFF__OFP;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFF__OIDX(Ctx *ctx, Cmpl *b, knh_bytes_t a1, Object* a2, knh_vmc_u1_t a3)
{
	knh_asmc_jmp_iff_oidx_t *bw = (knh_asmc_jmp_iff_oidx_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_IFF_OIDX_SIZ);
	bw->code = ASMC_JMP_IFF__OIDX;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFNUL(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_asmv_t v)
{
#ifdef ASMC_JMP_IFNUL__EBP
	if(v.potype == KNH_ASMV_EBP) {
		KNH_ASM_JMP_IFNUL__ebp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_JMP_IFNUL__EBP*/
#ifdef ASMC_JMP_IFNUL__SFP
	if(v.potype == KNH_ASMV_SFP) {
		KNH_ASM_JMP_IFNUL__sfp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_JMP_IFNUL__SFP*/
#ifdef ASMC_JMP_IFNUL__OFP
	if(v.potype == KNH_ASMV_OFP) {
		KNH_ASM_JMP_IFNUL__ofp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_JMP_IFNUL__OFP*/
#ifdef ASMC_JMP_IFNUL__OBJ
	if(v.potype == KNH_ASMV_OBJ) {
		KNH_ASM_JMP_IFNUL__OBJ(ctx, b, a1, v.value);
		return;
	}
#endif/*ASMC_JMP_IFNUL__OBJ*/
#ifdef ASMC_JMP_IFNUL__OIDX
	if(v.potype == KNH_ASMV_OIDX) {
		KNH_ASM_JMP_IFNUL__OIDX(ctx, b, a1, v.value, v.index);
		return;
	}
#endif/*ASMC_JMP_IFNUL__OIDX*/
	DEBUG("unsupported asmv.potype=%d", v.potype);
	KNH_ASSERT(ctx == NULL); /* stop here!!*/
}
/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFNUL__ebp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_i1_t a2)
{
	knh_asmc_jmp_ifnul_ebp_t *bw = (knh_asmc_jmp_ifnul_ebp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_IFNUL_ebp_SIZ);
	bw->code = ASMC_JMP_IFNUL__EBP;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFNUL__sfp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_jmp_ifnul_sfp_t *bw = (knh_asmc_jmp_ifnul_sfp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_IFNUL_sfp_SIZ);
	bw->code = ASMC_JMP_IFNUL__SFP;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFNUL__ofp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_jmp_ifnul_ofp_t *bw = (knh_asmc_jmp_ifnul_ofp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_IFNUL_ofp_SIZ);
	bw->code = ASMC_JMP_IFNUL__OFP;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFNUL__OIDX(Ctx *ctx, Cmpl *b, knh_bytes_t a1, Object* a2, knh_vmc_u1_t a3)
{
	knh_asmc_jmp_ifnul_oidx_t *bw = (knh_asmc_jmp_ifnul_oidx_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_IFNUL_OIDX_SIZ);
	bw->code = ASMC_JMP_IFNUL__OIDX;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFNONUL(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_asmv_t v)
{
#ifdef ASMC_JMP_IFNONUL__EBP
	if(v.potype == KNH_ASMV_EBP) {
		KNH_ASM_JMP_IFNONUL__ebp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_JMP_IFNONUL__EBP*/
#ifdef ASMC_JMP_IFNONUL__SFP
	if(v.potype == KNH_ASMV_SFP) {
		KNH_ASM_JMP_IFNONUL__sfp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_JMP_IFNONUL__SFP*/
#ifdef ASMC_JMP_IFNONUL__OFP
	if(v.potype == KNH_ASMV_OFP) {
		KNH_ASM_JMP_IFNONUL__ofp(ctx, b, a1, v.index);
		return;
	}
#endif/*ASMC_JMP_IFNONUL__OFP*/
#ifdef ASMC_JMP_IFNONUL__OBJ
	if(v.potype == KNH_ASMV_OBJ) {
		KNH_ASM_JMP_IFNONUL__OBJ(ctx, b, a1, v.value);
		return;
	}
#endif/*ASMC_JMP_IFNONUL__OBJ*/
#ifdef ASMC_JMP_IFNONUL__OIDX
	if(v.potype == KNH_ASMV_OIDX) {
		KNH_ASM_JMP_IFNONUL__OIDX(ctx, b, a1, v.value, v.index);
		return;
	}
#endif/*ASMC_JMP_IFNONUL__OIDX*/
	DEBUG("unsupported asmv.potype=%d", v.potype);
	KNH_ASSERT(ctx == NULL); /* stop here!!*/
}
/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFNONUL__ebp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_i1_t a2)
{
	knh_asmc_jmp_ifnonul_ebp_t *bw = (knh_asmc_jmp_ifnonul_ebp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_IFNONUL_ebp_SIZ);
	bw->code = ASMC_JMP_IFNONUL__EBP;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFNONUL__sfp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_jmp_ifnonul_sfp_t *bw = (knh_asmc_jmp_ifnonul_sfp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_IFNONUL_sfp_SIZ);
	bw->code = ASMC_JMP_IFNONUL__SFP;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFNONUL__ofp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_jmp_ifnonul_ofp_t *bw = (knh_asmc_jmp_ifnonul_ofp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_IFNONUL_ofp_SIZ);
	bw->code = ASMC_JMP_IFNONUL__OFP;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_JMP_IFNONUL__OIDX(Ctx *ctx, Cmpl *b, knh_bytes_t a1, Object* a2, knh_vmc_u1_t a3)
{
	knh_asmc_jmp_ifnonul_oidx_t *bw = (knh_asmc_jmp_ifnonul_oidx_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_JMP_IFNONUL_OIDX_SIZ);
	bw->code = ASMC_JMP_IFNONUL__OIDX;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
	knh_Object_refc_inc(bw->a2);
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_ITER(Ctx *ctx, Cmpl *b, knh_class_t a1, knh_vmc_u1_t a2)
{
	knh_asmc_iter_t *bw = (knh_asmc_iter_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_ITER_SIZ);
	bw->code = ASMC_ITER;
	bw->a1 = a1;
	bw->a2 = a2;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_FOREACH(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_class_t a2, knh_vmc_u1_t a3, knh_vmc_u1_t a4)
{
	knh_asmc_foreach_t *bw = (knh_asmc_foreach_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_FOREACH_SIZ);
	bw->code = ASMC_FOREACH;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
	bw->a3 = a3;
	bw->a4 = a4;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_TRY_BEGIN(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2, knh_vmc_u1_t a3)
{
	knh_asmc_try_begin_t *bw = (knh_asmc_try_begin_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_TRY_BEGIN_SIZ);
	bw->code = ASMC_TRY_BEGIN;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_TRY_END(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1)
{
	knh_asmc_try_end_t *bw = (knh_asmc_try_end_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_TRY_END_SIZ);
	bw->code = ASMC_TRY_END;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_CATCH(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_expt_t a2, knh_vmc_u1_t a3)
{
	knh_asmc_catch_t *bw = (knh_asmc_catch_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_CATCH_SIZ);
	bw->code = ASMC_CATCH;
	bw->a1 = knh_Cmpl_labelId(ctx, b, a1);
	bw->a2 = a2;
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_THROW(Ctx *ctx, Cmpl *b, knh_asmv_t v)
{
#ifdef ASMC_THROW__EBP
	if(v.potype == KNH_ASMV_EBP) {
		KNH_ASM_THROW__ebp(ctx, b, v.index);
		return;
	}
#endif/*ASMC_THROW__EBP*/
#ifdef ASMC_THROW__SFP
	if(v.potype == KNH_ASMV_SFP) {
		KNH_ASM_THROW__sfp(ctx, b, v.index);
		return;
	}
#endif/*ASMC_THROW__SFP*/
#ifdef ASMC_THROW__OFP
	if(v.potype == KNH_ASMV_OFP) {
		KNH_ASM_THROW__ofp(ctx, b, v.index);
		return;
	}
#endif/*ASMC_THROW__OFP*/
#ifdef ASMC_THROW__OBJ
	if(v.potype == KNH_ASMV_OBJ) {
		KNH_ASM_THROW__OBJ(ctx, b, v.value);
		return;
	}
#endif/*ASMC_THROW__OBJ*/
#ifdef ASMC_THROW__OIDX
	if(v.potype == KNH_ASMV_OIDX) {
		KNH_ASM_THROW__OIDX(ctx, b, v.value, v.index);
		return;
	}
#endif/*ASMC_THROW__OIDX*/
	DEBUG("unsupported asmv.potype=%d", v.potype);
	KNH_ASSERT(ctx == NULL); /* stop here!!*/
}
/* ------------------------------------------------------------------------ */

void KNH_ASM_THROW__ebp(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1)
{
	knh_asmc_throw_ebp_t *bw = (knh_asmc_throw_ebp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_THROW_ebp_SIZ);
	bw->code = ASMC_THROW__EBP;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_THROW__sfp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1)
{
	knh_asmc_throw_sfp_t *bw = (knh_asmc_throw_sfp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_THROW_sfp_SIZ);
	bw->code = ASMC_THROW__SFP;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_THROW__OBJ(Ctx *ctx, Cmpl *b, Object* a1)
{
	knh_asmc_throw_obj_t *bw = (knh_asmc_throw_obj_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_THROW_OBJ_SIZ);
	bw->code = ASMC_THROW__OBJ;
	bw->a1 = a1;
	knh_Object_refc_inc(bw->a1);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PRINT(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1, knh_methodn_t a2, knh_asmv_t v)
{
#ifdef ASMC_PRINT__EBP
	if(v.potype == KNH_ASMV_EBP) {
		KNH_ASM_PRINT__ebp(ctx, b, a1, a2, v.index);
		return;
	}
#endif/*ASMC_PRINT__EBP*/
#ifdef ASMC_PRINT__SFP
	if(v.potype == KNH_ASMV_SFP) {
		KNH_ASM_PRINT__sfp(ctx, b, a1, a2, v.index);
		return;
	}
#endif/*ASMC_PRINT__SFP*/
#ifdef ASMC_PRINT__OFP
	if(v.potype == KNH_ASMV_OFP) {
		KNH_ASM_PRINT__ofp(ctx, b, a1, a2, v.index);
		return;
	}
#endif/*ASMC_PRINT__OFP*/
#ifdef ASMC_PRINT__OBJ
	if(v.potype == KNH_ASMV_OBJ) {
		KNH_ASM_PRINT__OBJ(ctx, b, a1, a2, v.value);
		return;
	}
#endif/*ASMC_PRINT__OBJ*/
#ifdef ASMC_PRINT__OIDX
	if(v.potype == KNH_ASMV_OIDX) {
		KNH_ASM_PRINT__OIDX(ctx, b, a1, a2, v.value, v.index);
		return;
	}
#endif/*ASMC_PRINT__OIDX*/
	DEBUG("unsupported asmv.potype=%d", v.potype);
	KNH_ASSERT(ctx == NULL); /* stop here!!*/
}
/* ------------------------------------------------------------------------ */

void KNH_ASM_PRINT__ebp(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1, knh_methodn_t a2, knh_vmc_i1_t a3)
{
	knh_asmc_print_ebp_t *bw = (knh_asmc_print_ebp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_PRINT_ebp_SIZ);
	bw->code = ASMC_PRINT__EBP;
	bw->a1 = a1;
	bw->a2 = a2;
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PRINT__sfp(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1, knh_methodn_t a2, knh_vmc_u1_t a3)
{
	knh_asmc_print_sfp_t *bw = (knh_asmc_print_sfp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_PRINT_sfp_SIZ);
	bw->code = ASMC_PRINT__SFP;
	bw->a1 = a1;
	bw->a2 = a2;
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PRINT__ofp(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1, knh_methodn_t a2, knh_vmc_u1_t a3)
{
	knh_asmc_print_ofp_t *bw = (knh_asmc_print_ofp_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_PRINT_ofp_SIZ);
	bw->code = ASMC_PRINT__OFP;
	bw->a1 = a1;
	bw->a2 = a2;
	bw->a3 = a3;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PRINT__OBJ(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1, knh_methodn_t a2, Object* a3)
{
	knh_asmc_print_obj_t *bw = (knh_asmc_print_obj_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_PRINT_OBJ_SIZ);
	bw->code = ASMC_PRINT__OBJ;
	bw->a1 = a1;
	bw->a2 = a2;
	bw->a3 = a3;
	knh_Object_refc_inc(bw->a3);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_PRINT__OIDX(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1, knh_methodn_t a2, Object* a3, knh_vmc_u1_t a4)
{
	knh_asmc_print_oidx_t *bw = (knh_asmc_print_oidx_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_PRINT_OIDX_SIZ);
	bw->code = ASMC_PRINT__OIDX;
	bw->a1 = a1;
	bw->a2 = a2;
	bw->a3 = a3;
	knh_Object_refc_inc(bw->a3);
	bw->a4 = a4;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_DIAGNOSE(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1)
{
	knh_asmc_diagnose_t *bw = (knh_asmc_diagnose_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_DIAGNOSE_SIZ);
	bw->code = ASMC_DIAGNOSE;
	bw->a1 = a1;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_STACKDUMP(Ctx *ctx, Cmpl *b)
{
	knh_asmc_stackdump_t *bw = (knh_asmc_stackdump_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_STACKDUMP_SIZ);
	bw->code = ASMC_STACKDUMP;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_NOP(Ctx *ctx, Cmpl *b)
{
	knh_asmc_nop_t *bw = (knh_asmc_nop_t*)knh_Cmpl_asmmalloc(ctx, b, KNH_ASMC_NOP_SIZ);
	bw->code = ASMC_NOP;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
