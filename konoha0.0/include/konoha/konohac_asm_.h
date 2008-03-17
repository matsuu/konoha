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

#ifndef KONOHAC_ASM__H
#define KONOHAC_ASM__H

#include<konoha/konoha_dev.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */
#define ASMC_RET_VOID                   ((knh_asmc_t)0)
#define ASMC_RET__EBP                   ((knh_asmc_t)1)
#define ASMC_RET__SFP                   ((knh_asmc_t)2)
#define ASMC_RET__OFP                   ((knh_asmc_t)3)
#define ASMC_RET__OBJ                   ((knh_asmc_t)4)
#define ASMC_RET__OIDX                  ((knh_asmc_t)5)
#define ASMC_MOVE__EBP                  ((knh_asmc_t)6)
#define ASMC_MOVE__SFP                  ((knh_asmc_t)7)
#define ASMC_MOVE__OFP                  ((knh_asmc_t)8)
#define ASMC_MOVE__OBJ                  ((knh_asmc_t)9)
#define ASMC_MOVE__OIDX                 ((knh_asmc_t)10)
#define ASMC_MOVS__EBP                  ((knh_asmc_t)11)
#define ASMC_MOVS__SFP                  ((knh_asmc_t)12)
#define ASMC_MOVS__OFP                  ((knh_asmc_t)13)
#define ASMC_MOVS__OBJ                  ((knh_asmc_t)14)
#define ASMC_MOVS__OIDX                 ((knh_asmc_t)15)
#define ASMC_MOVO__EBP                  ((knh_asmc_t)16)
#define ASMC_MOVO__SFP                  ((knh_asmc_t)17)
#define ASMC_MOVO__OFP                  ((knh_asmc_t)18)
#define ASMC_MOVO__OBJ                  ((knh_asmc_t)19)
#define ASMC_MOVO__OIDX                 ((knh_asmc_t)20)
#define ASMC_MOVOI__EBP                 ((knh_asmc_t)21)
#define ASMC_MOVOI__SFP                 ((knh_asmc_t)22)
#define ASMC_MOVOI__OFP                 ((knh_asmc_t)23)
#define ASMC_MOVOI__OBJ                 ((knh_asmc_t)24)
#define ASMC_MOVOI__OIDX                ((knh_asmc_t)25)
#define ASMC_MOVSFP_IFNUL               ((knh_asmc_t)26)
#define ASMC_PUSH__SFP                  ((knh_asmc_t)27)
#define ASMC_PUSH__OFP                  ((knh_asmc_t)28)
#define ASMC_PUSH__OBJ                  ((knh_asmc_t)29)
#define ASMC_PUSH__OIDX                 ((knh_asmc_t)30)
#define ASMC_PUTI                       ((knh_asmc_t)31)
#define ASMC_PUSH__MN                   ((knh_asmc_t)32)
#define ASMC_PUSH__DEF                  ((knh_asmc_t)33)
#define ASMC_VARGS                      ((knh_asmc_t)34)
#define ASMC_SCALL                      ((knh_asmc_t)35)
#define ASMC_CALL                       ((knh_asmc_t)36)
#define ASMC_DCALL                      ((knh_asmc_t)37)
#define ASMC_MCALL                      ((knh_asmc_t)38)
#define ASMC_CALL_WM                    ((knh_asmc_t)39)
#define ASMC_NCALL_WM                   ((knh_asmc_t)40)
#define ASMC_NEW                        ((knh_asmc_t)41)
#define ASMC_NEWE                       ((knh_asmc_t)42)
#define ASMC_NEW__DEF                   ((knh_asmc_t)43)
#define ASMC_MT                         ((knh_asmc_t)44)
#define ASMC_MT__OPT                    ((knh_asmc_t)45)
#define ASMC_MAP                        ((knh_asmc_t)46)
#define ASMC_MAPE                       ((knh_asmc_t)47)
#define ASMC_MAP_WM                     ((knh_asmc_t)48)
#define ASMC_MAPE_WM                    ((knh_asmc_t)49)
#define ASMC_MAP2                       ((knh_asmc_t)50)
#define ASMC_MAP2E                      ((knh_asmc_t)51)
#define ASMC_TYPECHK__EBP               ((knh_asmc_t)52)
#define ASMC_TYPECHK__SFP               ((knh_asmc_t)53)
#define ASMC_TYPECHK__OFP               ((knh_asmc_t)54)
#define ASMC_TYPECHK__OBJ               ((knh_asmc_t)55)
#define ASMC_TYPECHK__OIDX              ((knh_asmc_t)56)
#define ASMC_NULLCHK__EBP               ((knh_asmc_t)57)
#define ASMC_NULLCHK__SFP               ((knh_asmc_t)58)
#define ASMC_NULLCHK__OFP               ((knh_asmc_t)59)
#define ASMC_NULLCHK__OBJ               ((knh_asmc_t)60)
#define ASMC_NULLCHK__OIDX              ((knh_asmc_t)61)
#define ASMC_JMP                        ((knh_asmc_t)62)
#define ASMC_SKIP                       ((knh_asmc_t)63)
#define ASMC_JMP_IFT__EBP               ((knh_asmc_t)64)
#define ASMC_JMP_IFT__SFP               ((knh_asmc_t)65)
#define ASMC_JMP_IFT__OFP               ((knh_asmc_t)66)
#define ASMC_JMP_IFT__OIDX              ((knh_asmc_t)67)
#define ASMC_JMP_IFF__EBP               ((knh_asmc_t)68)
#define ASMC_JMP_IFF__SFP               ((knh_asmc_t)69)
#define ASMC_JMP_IFF__OFP               ((knh_asmc_t)70)
#define ASMC_JMP_IFF__OIDX              ((knh_asmc_t)71)
#define ASMC_JMP_IFNUL__EBP             ((knh_asmc_t)72)
#define ASMC_JMP_IFNUL__SFP             ((knh_asmc_t)73)
#define ASMC_JMP_IFNUL__OFP             ((knh_asmc_t)74)
#define ASMC_JMP_IFNUL__OIDX            ((knh_asmc_t)75)
#define ASMC_JMP_IFNONUL__EBP           ((knh_asmc_t)76)
#define ASMC_JMP_IFNONUL__SFP           ((knh_asmc_t)77)
#define ASMC_JMP_IFNONUL__OFP           ((knh_asmc_t)78)
#define ASMC_JMP_IFNONUL__OIDX          ((knh_asmc_t)79)
#define ASMC_ITER                       ((knh_asmc_t)80)
#define ASMC_FOREACH                    ((knh_asmc_t)81)
#define ASMC_TRY_BEGIN                  ((knh_asmc_t)82)
#define ASMC_TRY_END                    ((knh_asmc_t)83)
#define ASMC_CATCH                      ((knh_asmc_t)84)
#define ASMC_THROW__EBP                 ((knh_asmc_t)85)
#define ASMC_THROW__SFP                 ((knh_asmc_t)86)
#define ASMC_THROW__OBJ                 ((knh_asmc_t)87)
#define ASMC_PRINT__EBP                 ((knh_asmc_t)88)
#define ASMC_PRINT__SFP                 ((knh_asmc_t)89)
#define ASMC_PRINT__OFP                 ((knh_asmc_t)90)
#define ASMC_PRINT__OBJ                 ((knh_asmc_t)91)
#define ASMC_PRINT__OIDX                ((knh_asmc_t)92)
#define ASMC_DIAGNOSE                   ((knh_asmc_t)93)
#define ASMC_STACKDUMP                  ((knh_asmc_t)94)
#define ASMC_NOP                        ((knh_asmc_t)95)

/* ------------------------------------------------------------------------ */
#ifndef METHODN__repr
#define METHODN__repr                   METHODN__s
#endif

/* ------------------------------------------------------------------------ */
void knh_Cmpl_remapAddress(Ctx *ctx, Cmpl *b);
void knh_VirtualMachineCode_utraverse(Ctx *ctx, knh_bytes_t vmc, f_gc gc);
void knh_VirtualMachineCode__dump_(Ctx *ctx, VirtualMachineCode *b, Writer *w, Any *m);
void knh_VirtualMachineCode_exec(Ctx *ctx, Object **sf);

#ifdef CLASS_Cmpl
void KNH_ASM_RET_VOID(Ctx *ctx, Cmpl *b);
void KNH_ASM_RET(Ctx *ctx, Cmpl *b, knh_asmv_t v);
void KNH_ASM_RET__ebp(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1);
void KNH_ASM_RET__sfp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1);
void KNH_ASM_RET__ofp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1);
void KNH_ASM_RET__OBJ(Ctx *ctx, Cmpl *b, Object* a1);
void KNH_ASM_RET__OIDX(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2);
void KNH_ASM_MOVE(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1, knh_asmv_t v);
void KNH_ASM_MOVE__ebp(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1, knh_vmc_i1_t a2);
void KNH_ASM_MOVE__sfp(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1, knh_vmc_u1_t a2);
void KNH_ASM_MOVE__ofp(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1, knh_vmc_u1_t a2);
void KNH_ASM_MOVE__OBJ(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1, Object* a2);
void KNH_ASM_MOVE__OIDX(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1, Object* a2, knh_vmc_u1_t a3);
void KNH_ASM_MOVS(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_asmv_t v);
void KNH_ASM_MOVS__ebp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_vmc_i1_t a2);
void KNH_ASM_MOVS__sfp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_vmc_u1_t a2);
void KNH_ASM_MOVS__ofp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_vmc_u1_t a2);
void KNH_ASM_MOVS__OBJ(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, Object* a2);
void KNH_ASM_MOVS__OIDX(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, Object* a2, knh_vmc_u1_t a3);
void KNH_ASM_MOVO(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_asmv_t v);
void KNH_ASM_MOVO__ebp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_vmc_i1_t a2);
void KNH_ASM_MOVO__sfp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_vmc_u1_t a2);
void KNH_ASM_MOVO__ofp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_vmc_u1_t a2);
void KNH_ASM_MOVO__OBJ(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, Object* a2);
void KNH_ASM_MOVO__OIDX(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, Object* a2, knh_vmc_u1_t a3);
void KNH_ASM_MOVOI(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2, knh_asmv_t v);
void KNH_ASM_MOVOI__ebp(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2, knh_vmc_i1_t a3);
void KNH_ASM_MOVOI__sfp(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2, knh_vmc_u1_t a3);
void KNH_ASM_MOVOI__ofp(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2, knh_vmc_u1_t a3);
void KNH_ASM_MOVOI__OBJ(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2, Object* a3);
void KNH_ASM_MOVOI__OIDX(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2, Object* a3, knh_vmc_u1_t a4);
void KNH_ASM_MOVSFP_IFNUL(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, Object* a2);
void KNH_ASM_PUSH(Ctx *ctx, Cmpl *b, knh_asmv_t v);
void KNH_ASM_PUSH__sfp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1);
void KNH_ASM_PUSH__ofp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1);
void KNH_ASM_PUSH__OBJ(Ctx *ctx, Cmpl *b, Object* a1);
void KNH_ASM_PUSH__OIDX(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2);
void KNH_ASM_PUTI(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1);
void KNH_ASM_PUSH__MN(Ctx *ctx, Cmpl *b, knh_methodn_t a1);
void KNH_ASM_PUSH__DEF(Ctx *ctx, Cmpl *b, knh_class_t a1);
void KNH_ASM_VARGS(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1);
void KNH_ASM_SCALL(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1);
void KNH_ASM_CALL(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1);
void KNH_ASM_DCALL(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1);
void KNH_ASM_MCALL(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1);
void KNH_ASM_CALL_WM(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, Object* a2);
void KNH_ASM_NCALL_WM(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, Object* a2);
void KNH_ASM_NEW(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1, Object* a2, knh_vmc_u2_t a3, knh_class_t a4);
void KNH_ASM_NEWE(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1, Object* a2, knh_vmc_u2_t a3, knh_class_t a4);
void KNH_ASM_NEW__DEF(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1, knh_vmc_u2_t a2, knh_class_t a3);
void KNH_ASM_MT(Ctx *ctx, Cmpl *b, knh_methodn_t a1);
void KNH_ASM_MT__OPT(Ctx *ctx, Cmpl *b, knh_methodn_t a1, Object* a2);
void KNH_ASM_MAP(Ctx *ctx, Cmpl *b, knh_class_t a1);
void KNH_ASM_MAPE(Ctx *ctx, Cmpl *b, knh_class_t a1);
void KNH_ASM_MAP_WM(Ctx *ctx, Cmpl *b, Object* a1);
void KNH_ASM_MAPE_WM(Ctx *ctx, Cmpl *b, Object* a1);
void KNH_ASM_MAP2(Ctx *ctx, Cmpl *b, knh_class_t a1);
void KNH_ASM_MAP2E(Ctx *ctx, Cmpl *b, knh_class_t a1);
void KNH_ASM_TYPECHK(Ctx *ctx, Cmpl *b, knh_class_t a1, knh_asmv_t v);
void KNH_ASM_TYPECHK__ebp(Ctx *ctx, Cmpl *b, knh_class_t a1, knh_vmc_i1_t a2);
void KNH_ASM_TYPECHK__sfp(Ctx *ctx, Cmpl *b, knh_class_t a1, knh_vmc_u1_t a2);
void KNH_ASM_TYPECHK__ofp(Ctx *ctx, Cmpl *b, knh_class_t a1, knh_vmc_u1_t a2);
void KNH_ASM_TYPECHK__OBJ(Ctx *ctx, Cmpl *b, knh_class_t a1, Object* a2);
void KNH_ASM_TYPECHK__OIDX(Ctx *ctx, Cmpl *b, knh_class_t a1, Object* a2, knh_vmc_u1_t a3);
void KNH_ASM_NULLCHK(Ctx *ctx, Cmpl *b, knh_asmv_t v);
void KNH_ASM_NULLCHK__ebp(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1);
void KNH_ASM_NULLCHK__sfp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1);
void KNH_ASM_NULLCHK__ofp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1);
void KNH_ASM_NULLCHK__OBJ(Ctx *ctx, Cmpl *b, Object* a1);
void KNH_ASM_NULLCHK__OIDX(Ctx *ctx, Cmpl *b, Object* a1, knh_vmc_u1_t a2);
void KNH_ASM_JMP(Ctx *ctx, Cmpl *b, knh_bytes_t a1);
void KNH_ASM_SKIP(Ctx *ctx, Cmpl *b, knh_bytes_t a1);
void KNH_ASM_JMP_IFT(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_asmv_t v);
void KNH_ASM_JMP_IFT__ebp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_i1_t a2);
void KNH_ASM_JMP_IFT__sfp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2);
void KNH_ASM_JMP_IFT__ofp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2);
void KNH_ASM_JMP_IFT__OIDX(Ctx *ctx, Cmpl *b, knh_bytes_t a1, Object* a2, knh_vmc_u1_t a3);
void KNH_ASM_JMP_IFF(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_asmv_t v);
void KNH_ASM_JMP_IFF__ebp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_i1_t a2);
void KNH_ASM_JMP_IFF__sfp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2);
void KNH_ASM_JMP_IFF__ofp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2);
void KNH_ASM_JMP_IFF__OIDX(Ctx *ctx, Cmpl *b, knh_bytes_t a1, Object* a2, knh_vmc_u1_t a3);
void KNH_ASM_JMP_IFNUL(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_asmv_t v);
void KNH_ASM_JMP_IFNUL__ebp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_i1_t a2);
void KNH_ASM_JMP_IFNUL__sfp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2);
void KNH_ASM_JMP_IFNUL__ofp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2);
void KNH_ASM_JMP_IFNUL__OIDX(Ctx *ctx, Cmpl *b, knh_bytes_t a1, Object* a2, knh_vmc_u1_t a3);
void KNH_ASM_JMP_IFNONUL(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_asmv_t v);
void KNH_ASM_JMP_IFNONUL__ebp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_i1_t a2);
void KNH_ASM_JMP_IFNONUL__sfp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2);
void KNH_ASM_JMP_IFNONUL__ofp(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2);
void KNH_ASM_JMP_IFNONUL__OIDX(Ctx *ctx, Cmpl *b, knh_bytes_t a1, Object* a2, knh_vmc_u1_t a3);
void KNH_ASM_ITER(Ctx *ctx, Cmpl *b, knh_class_t a1, knh_vmc_u1_t a2);
void KNH_ASM_FOREACH(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_class_t a2, knh_vmc_u1_t a3, knh_vmc_u1_t a4);
void KNH_ASM_TRY_BEGIN(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_vmc_u1_t a2, knh_vmc_u1_t a3);
void KNH_ASM_TRY_END(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1);
void KNH_ASM_CATCH(Ctx *ctx, Cmpl *b, knh_bytes_t a1, knh_expt_t a2, knh_vmc_u1_t a3);
void KNH_ASM_THROW(Ctx *ctx, Cmpl *b, knh_asmv_t v);
void KNH_ASM_THROW__ebp(Ctx *ctx, Cmpl *b, knh_vmc_i1_t a1);
void KNH_ASM_THROW__sfp(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1);
void KNH_ASM_THROW__OBJ(Ctx *ctx, Cmpl *b, Object* a1);
void KNH_ASM_PRINT(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1, knh_methodn_t a2, knh_asmv_t v);
void KNH_ASM_PRINT__ebp(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1, knh_methodn_t a2, knh_vmc_i1_t a3);
void KNH_ASM_PRINT__sfp(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1, knh_methodn_t a2, knh_vmc_u1_t a3);
void KNH_ASM_PRINT__ofp(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1, knh_methodn_t a2, knh_vmc_u1_t a3);
void KNH_ASM_PRINT__OBJ(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1, knh_methodn_t a2, Object* a3);
void KNH_ASM_PRINT__OIDX(Ctx *ctx, Cmpl *b, knh_vmc_u2_t a1, knh_methodn_t a2, Object* a3, knh_vmc_u1_t a4);
void KNH_ASM_DIAGNOSE(Ctx *ctx, Cmpl *b, knh_vmc_u1_t a1);
void KNH_ASM_STACKDUMP(Ctx *ctx, Cmpl *b);
void KNH_ASM_NOP(Ctx *ctx, Cmpl *b);

#endif/*CLASS_Cmpl*/

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
} knh_asmc_ret_void_t;

typedef struct {
	knh_asmc_t code;
	void *w;
} knh_asmc_ret_void_tw;

#define KNH_ASMC_RET_VOID_SIZ  (sizeof(knh_asmc_ret_void_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_i1_t a1;
} knh_asmc_ret_ebp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_i1_t a1;
	void *w;
} knh_asmc_ret_ebp_tw;

#define KNH_ASMC_RET_ebp_SIZ  (sizeof(knh_asmc_ret_ebp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
} knh_asmc_ret_sfp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	void *w;
} knh_asmc_ret_sfp_tw;

#define KNH_ASMC_RET_sfp_SIZ  (sizeof(knh_asmc_ret_sfp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
} knh_asmc_ret_ofp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	void *w;
} knh_asmc_ret_ofp_tw;

#define KNH_ASMC_RET_ofp_SIZ  (sizeof(knh_asmc_ret_ofp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	Object* a1;
} knh_asmc_ret_obj_t;

typedef struct {
	knh_asmc_t code;
	Object* a1;
	void *w;
} knh_asmc_ret_obj_tw;

#define KNH_ASMC_RET_OBJ_SIZ  (sizeof(knh_asmc_ret_obj_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a2;
	Object* a1;
} knh_asmc_ret_oidx_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a2;
	Object* a1;
	void *w;
} knh_asmc_ret_oidx_tw;

#define KNH_ASMC_RET_OIDX_SIZ  (sizeof(knh_asmc_ret_oidx_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_i1_t a1;
	knh_vmc_i1_t a2;
} knh_asmc_move_ebp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_i1_t a1;
	knh_vmc_i1_t a2;
	void *w;
} knh_asmc_move_ebp_tw;

#define KNH_ASMC_MOVE_ebp_SIZ  (sizeof(knh_asmc_move_ebp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_i1_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_move_sfp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_i1_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_move_sfp_tw;

#define KNH_ASMC_MOVE_sfp_SIZ  (sizeof(knh_asmc_move_sfp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_i1_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_move_ofp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_i1_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_move_ofp_tw;

#define KNH_ASMC_MOVE_ofp_SIZ  (sizeof(knh_asmc_move_ofp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_i1_t a1;
	Object* a2;
} knh_asmc_move_obj_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_i1_t a1;
	Object* a2;
	void *w;
} knh_asmc_move_obj_tw;

#define KNH_ASMC_MOVE_OBJ_SIZ  (sizeof(knh_asmc_move_obj_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_i1_t a1;
	knh_vmc_u1_t a3;
	Object* a2;
} knh_asmc_move_oidx_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_i1_t a1;
	knh_vmc_u1_t a3;
	Object* a2;
	void *w;
} knh_asmc_move_oidx_tw;

#define KNH_ASMC_MOVE_OIDX_SIZ  (sizeof(knh_asmc_move_oidx_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_i1_t a2;
} knh_asmc_movs_ebp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_i1_t a2;
	void *w;
} knh_asmc_movs_ebp_tw;

#define KNH_ASMC_MOVS_ebp_SIZ  (sizeof(knh_asmc_movs_ebp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_movs_sfp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_movs_sfp_tw;

#define KNH_ASMC_MOVS_sfp_SIZ  (sizeof(knh_asmc_movs_sfp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_movs_ofp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_movs_ofp_tw;

#define KNH_ASMC_MOVS_ofp_SIZ  (sizeof(knh_asmc_movs_ofp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	Object* a2;
} knh_asmc_movs_obj_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	Object* a2;
	void *w;
} knh_asmc_movs_obj_tw;

#define KNH_ASMC_MOVS_OBJ_SIZ  (sizeof(knh_asmc_movs_obj_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_u1_t a3;
	Object* a2;
} knh_asmc_movs_oidx_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_u1_t a3;
	Object* a2;
	void *w;
} knh_asmc_movs_oidx_tw;

#define KNH_ASMC_MOVS_OIDX_SIZ  (sizeof(knh_asmc_movs_oidx_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_i1_t a2;
} knh_asmc_movo_ebp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_i1_t a2;
	void *w;
} knh_asmc_movo_ebp_tw;

#define KNH_ASMC_MOVO_ebp_SIZ  (sizeof(knh_asmc_movo_ebp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_movo_sfp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_movo_sfp_tw;

#define KNH_ASMC_MOVO_sfp_SIZ  (sizeof(knh_asmc_movo_sfp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_movo_ofp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_movo_ofp_tw;

#define KNH_ASMC_MOVO_ofp_SIZ  (sizeof(knh_asmc_movo_ofp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	Object* a2;
} knh_asmc_movo_obj_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	Object* a2;
	void *w;
} knh_asmc_movo_obj_tw;

#define KNH_ASMC_MOVO_OBJ_SIZ  (sizeof(knh_asmc_movo_obj_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_u1_t a3;
	Object* a2;
} knh_asmc_movo_oidx_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_u1_t a3;
	Object* a2;
	void *w;
} knh_asmc_movo_oidx_tw;

#define KNH_ASMC_MOVO_OIDX_SIZ  (sizeof(knh_asmc_movo_oidx_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a2;
	knh_vmc_i1_t a3;
	Object* a1;
} knh_asmc_movoi_ebp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a2;
	knh_vmc_i1_t a3;
	Object* a1;
	void *w;
} knh_asmc_movoi_ebp_tw;

#define KNH_ASMC_MOVOI_ebp_SIZ  (sizeof(knh_asmc_movoi_ebp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a2;
	knh_vmc_u1_t a3;
	Object* a1;
} knh_asmc_movoi_sfp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a2;
	knh_vmc_u1_t a3;
	Object* a1;
	void *w;
} knh_asmc_movoi_sfp_tw;

#define KNH_ASMC_MOVOI_sfp_SIZ  (sizeof(knh_asmc_movoi_sfp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a2;
	knh_vmc_u1_t a3;
	Object* a1;
} knh_asmc_movoi_ofp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a2;
	knh_vmc_u1_t a3;
	Object* a1;
	void *w;
} knh_asmc_movoi_ofp_tw;

#define KNH_ASMC_MOVOI_ofp_SIZ  (sizeof(knh_asmc_movoi_ofp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a2;
	Object* a1;
	Object* a3;
} knh_asmc_movoi_obj_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a2;
	Object* a1;
	Object* a3;
	void *w;
} knh_asmc_movoi_obj_tw;

#define KNH_ASMC_MOVOI_OBJ_SIZ  (sizeof(knh_asmc_movoi_obj_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a2;
	knh_vmc_u1_t a4;
	Object* a1;
	Object* a3;
} knh_asmc_movoi_oidx_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a2;
	knh_vmc_u1_t a4;
	Object* a1;
	Object* a3;
	void *w;
} knh_asmc_movoi_oidx_tw;

#define KNH_ASMC_MOVOI_OIDX_SIZ  (sizeof(knh_asmc_movoi_oidx_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	Object* a2;
} knh_asmc_movsfp_ifnul_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	Object* a2;
	void *w;
} knh_asmc_movsfp_ifnul_tw;

#define KNH_ASMC_MOVSFP_IFNUL_SIZ  (sizeof(knh_asmc_movsfp_ifnul_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
} knh_asmc_push_sfp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	void *w;
} knh_asmc_push_sfp_tw;

#define KNH_ASMC_PUSH_sfp_SIZ  (sizeof(knh_asmc_push_sfp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
} knh_asmc_push_ofp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	void *w;
} knh_asmc_push_ofp_tw;

#define KNH_ASMC_PUSH_ofp_SIZ  (sizeof(knh_asmc_push_ofp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	Object* a1;
} knh_asmc_push_obj_t;

typedef struct {
	knh_asmc_t code;
	Object* a1;
	void *w;
} knh_asmc_push_obj_tw;

#define KNH_ASMC_PUSH_OBJ_SIZ  (sizeof(knh_asmc_push_obj_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a2;
	Object* a1;
} knh_asmc_push_oidx_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a2;
	Object* a1;
	void *w;
} knh_asmc_push_oidx_tw;

#define KNH_ASMC_PUSH_OIDX_SIZ  (sizeof(knh_asmc_push_oidx_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
} knh_asmc_puti_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
	void *w;
} knh_asmc_puti_tw;

#define KNH_ASMC_PUTI_SIZ  (sizeof(knh_asmc_puti_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_methodn_t a1;
} knh_asmc_push_mn_t;

typedef struct {
	knh_asmc_t code;
	knh_methodn_t a1;
	void *w;
} knh_asmc_push_mn_tw;

#define KNH_ASMC_PUSH_MN_SIZ  (sizeof(knh_asmc_push_mn_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
} knh_asmc_push_def_t;

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	void *w;
} knh_asmc_push_def_tw;

#define KNH_ASMC_PUSH_DEF_SIZ  (sizeof(knh_asmc_push_def_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
} knh_asmc_vargs_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
	void *w;
} knh_asmc_vargs_tw;

#define KNH_ASMC_VARGS_SIZ  (sizeof(knh_asmc_vargs_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
} knh_asmc_scall_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	void *w;
} knh_asmc_scall_tw;

#define KNH_ASMC_SCALL_SIZ  (sizeof(knh_asmc_scall_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
} knh_asmc_call_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	void *w;
} knh_asmc_call_tw;

#define KNH_ASMC_CALL_SIZ  (sizeof(knh_asmc_call_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
} knh_asmc_dcall_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	void *w;
} knh_asmc_dcall_tw;

#define KNH_ASMC_DCALL_SIZ  (sizeof(knh_asmc_dcall_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
} knh_asmc_mcall_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	void *w;
} knh_asmc_mcall_tw;

#define KNH_ASMC_MCALL_SIZ  (sizeof(knh_asmc_mcall_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	Object* a2;
} knh_asmc_call_wm_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	Object* a2;
	void *w;
} knh_asmc_call_wm_tw;

#define KNH_ASMC_CALL_WM_SIZ  (sizeof(knh_asmc_call_wm_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	Object* a2;
} knh_asmc_ncall_wm_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	Object* a2;
	void *w;
} knh_asmc_ncall_wm_tw;

#define KNH_ASMC_NCALL_WM_SIZ  (sizeof(knh_asmc_ncall_wm_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
	knh_vmc_u2_t a3;
	knh_class_t a4;
	Object* a2;
} knh_asmc_new_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
	knh_vmc_u2_t a3;
	knh_class_t a4;
	Object* a2;
	void *w;
} knh_asmc_new_tw;

#define KNH_ASMC_NEW_SIZ  (sizeof(knh_asmc_new_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
	knh_vmc_u2_t a3;
	knh_class_t a4;
	Object* a2;
} knh_asmc_newe_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
	knh_vmc_u2_t a3;
	knh_class_t a4;
	Object* a2;
	void *w;
} knh_asmc_newe_tw;

#define KNH_ASMC_NEWE_SIZ  (sizeof(knh_asmc_newe_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_u2_t a2;
	knh_class_t a3;
} knh_asmc_new_def_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	knh_vmc_u2_t a2;
	knh_class_t a3;
	void *w;
} knh_asmc_new_def_tw;

#define KNH_ASMC_NEW_DEF_SIZ  (sizeof(knh_asmc_new_def_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_methodn_t a1;
} knh_asmc_mt_t;

typedef struct {
	knh_asmc_t code;
	knh_methodn_t a1;
	void *w;
} knh_asmc_mt_tw;

#define KNH_ASMC_MT_SIZ  (sizeof(knh_asmc_mt_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_methodn_t a1;
	Object* a2;
} knh_asmc_mt_opt_t;

typedef struct {
	knh_asmc_t code;
	knh_methodn_t a1;
	Object* a2;
	void *w;
} knh_asmc_mt_opt_tw;

#define KNH_ASMC_MT_OPT_SIZ  (sizeof(knh_asmc_mt_opt_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
} knh_asmc_map_t;

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	void *w;
} knh_asmc_map_tw;

#define KNH_ASMC_MAP_SIZ  (sizeof(knh_asmc_map_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
} knh_asmc_mape_t;

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	void *w;
} knh_asmc_mape_tw;

#define KNH_ASMC_MAPE_SIZ  (sizeof(knh_asmc_mape_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	Object* a1;
} knh_asmc_map_wm_t;

typedef struct {
	knh_asmc_t code;
	Object* a1;
	void *w;
} knh_asmc_map_wm_tw;

#define KNH_ASMC_MAP_WM_SIZ  (sizeof(knh_asmc_map_wm_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	Object* a1;
} knh_asmc_mape_wm_t;

typedef struct {
	knh_asmc_t code;
	Object* a1;
	void *w;
} knh_asmc_mape_wm_tw;

#define KNH_ASMC_MAPE_WM_SIZ  (sizeof(knh_asmc_mape_wm_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
} knh_asmc_map2_t;

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	void *w;
} knh_asmc_map2_tw;

#define KNH_ASMC_MAP2_SIZ  (sizeof(knh_asmc_map2_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
} knh_asmc_map2e_t;

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	void *w;
} knh_asmc_map2e_tw;

#define KNH_ASMC_MAP2E_SIZ  (sizeof(knh_asmc_map2e_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	knh_vmc_i1_t a2;
} knh_asmc_typechk_ebp_t;

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	knh_vmc_i1_t a2;
	void *w;
} knh_asmc_typechk_ebp_tw;

#define KNH_ASMC_TYPECHK_ebp_SIZ  (sizeof(knh_asmc_typechk_ebp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_typechk_sfp_t;

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_typechk_sfp_tw;

#define KNH_ASMC_TYPECHK_sfp_SIZ  (sizeof(knh_asmc_typechk_sfp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_typechk_ofp_t;

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_typechk_ofp_tw;

#define KNH_ASMC_TYPECHK_ofp_SIZ  (sizeof(knh_asmc_typechk_ofp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	Object* a2;
} knh_asmc_typechk_obj_t;

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	Object* a2;
	void *w;
} knh_asmc_typechk_obj_tw;

#define KNH_ASMC_TYPECHK_OBJ_SIZ  (sizeof(knh_asmc_typechk_obj_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	knh_vmc_u1_t a3;
	Object* a2;
} knh_asmc_typechk_oidx_t;

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	knh_vmc_u1_t a3;
	Object* a2;
	void *w;
} knh_asmc_typechk_oidx_tw;

#define KNH_ASMC_TYPECHK_OIDX_SIZ  (sizeof(knh_asmc_typechk_oidx_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_i1_t a1;
} knh_asmc_nullchk_ebp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_i1_t a1;
	void *w;
} knh_asmc_nullchk_ebp_tw;

#define KNH_ASMC_NULLCHK_ebp_SIZ  (sizeof(knh_asmc_nullchk_ebp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
} knh_asmc_nullchk_sfp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	void *w;
} knh_asmc_nullchk_sfp_tw;

#define KNH_ASMC_NULLCHK_sfp_SIZ  (sizeof(knh_asmc_nullchk_sfp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
} knh_asmc_nullchk_ofp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	void *w;
} knh_asmc_nullchk_ofp_tw;

#define KNH_ASMC_NULLCHK_ofp_SIZ  (sizeof(knh_asmc_nullchk_ofp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	Object* a1;
} knh_asmc_nullchk_obj_t;

typedef struct {
	knh_asmc_t code;
	Object* a1;
	void *w;
} knh_asmc_nullchk_obj_tw;

#define KNH_ASMC_NULLCHK_OBJ_SIZ  (sizeof(knh_asmc_nullchk_obj_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a2;
	Object* a1;
} knh_asmc_nullchk_oidx_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a2;
	Object* a1;
	void *w;
} knh_asmc_nullchk_oidx_tw;

#define KNH_ASMC_NULLCHK_OIDX_SIZ  (sizeof(knh_asmc_nullchk_oidx_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
} knh_asmc_jmp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	void *w;
} knh_asmc_jmp_tw;

#define KNH_ASMC_JMP_SIZ  (sizeof(knh_asmc_jmp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
} knh_asmc_skip_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	void *w;
} knh_asmc_skip_tw;

#define KNH_ASMC_SKIP_SIZ  (sizeof(knh_asmc_skip_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_i1_t a2;
} knh_asmc_jmp_ift_ebp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_i1_t a2;
	void *w;
} knh_asmc_jmp_ift_ebp_tw;

#define KNH_ASMC_JMP_IFT_ebp_SIZ  (sizeof(knh_asmc_jmp_ift_ebp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_jmp_ift_sfp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_jmp_ift_sfp_tw;

#define KNH_ASMC_JMP_IFT_sfp_SIZ  (sizeof(knh_asmc_jmp_ift_sfp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_jmp_ift_ofp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_jmp_ift_ofp_tw;

#define KNH_ASMC_JMP_IFT_ofp_SIZ  (sizeof(knh_asmc_jmp_ift_ofp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a3;
	Object* a2;
} knh_asmc_jmp_ift_oidx_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a3;
	Object* a2;
	void *w;
} knh_asmc_jmp_ift_oidx_tw;

#define KNH_ASMC_JMP_IFT_OIDX_SIZ  (sizeof(knh_asmc_jmp_ift_oidx_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_i1_t a2;
} knh_asmc_jmp_iff_ebp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_i1_t a2;
	void *w;
} knh_asmc_jmp_iff_ebp_tw;

#define KNH_ASMC_JMP_IFF_ebp_SIZ  (sizeof(knh_asmc_jmp_iff_ebp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_jmp_iff_sfp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_jmp_iff_sfp_tw;

#define KNH_ASMC_JMP_IFF_sfp_SIZ  (sizeof(knh_asmc_jmp_iff_sfp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_jmp_iff_ofp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_jmp_iff_ofp_tw;

#define KNH_ASMC_JMP_IFF_ofp_SIZ  (sizeof(knh_asmc_jmp_iff_ofp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a3;
	Object* a2;
} knh_asmc_jmp_iff_oidx_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a3;
	Object* a2;
	void *w;
} knh_asmc_jmp_iff_oidx_tw;

#define KNH_ASMC_JMP_IFF_OIDX_SIZ  (sizeof(knh_asmc_jmp_iff_oidx_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_i1_t a2;
} knh_asmc_jmp_ifnul_ebp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_i1_t a2;
	void *w;
} knh_asmc_jmp_ifnul_ebp_tw;

#define KNH_ASMC_JMP_IFNUL_ebp_SIZ  (sizeof(knh_asmc_jmp_ifnul_ebp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_jmp_ifnul_sfp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_jmp_ifnul_sfp_tw;

#define KNH_ASMC_JMP_IFNUL_sfp_SIZ  (sizeof(knh_asmc_jmp_ifnul_sfp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_jmp_ifnul_ofp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_jmp_ifnul_ofp_tw;

#define KNH_ASMC_JMP_IFNUL_ofp_SIZ  (sizeof(knh_asmc_jmp_ifnul_ofp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a3;
	Object* a2;
} knh_asmc_jmp_ifnul_oidx_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a3;
	Object* a2;
	void *w;
} knh_asmc_jmp_ifnul_oidx_tw;

#define KNH_ASMC_JMP_IFNUL_OIDX_SIZ  (sizeof(knh_asmc_jmp_ifnul_oidx_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_i1_t a2;
} knh_asmc_jmp_ifnonul_ebp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_i1_t a2;
	void *w;
} knh_asmc_jmp_ifnonul_ebp_tw;

#define KNH_ASMC_JMP_IFNONUL_ebp_SIZ  (sizeof(knh_asmc_jmp_ifnonul_ebp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_jmp_ifnonul_sfp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_jmp_ifnonul_sfp_tw;

#define KNH_ASMC_JMP_IFNONUL_sfp_SIZ  (sizeof(knh_asmc_jmp_ifnonul_sfp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_jmp_ifnonul_ofp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_jmp_ifnonul_ofp_tw;

#define KNH_ASMC_JMP_IFNONUL_ofp_SIZ  (sizeof(knh_asmc_jmp_ifnonul_ofp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a3;
	Object* a2;
} knh_asmc_jmp_ifnonul_oidx_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a3;
	Object* a2;
	void *w;
} knh_asmc_jmp_ifnonul_oidx_tw;

#define KNH_ASMC_JMP_IFNONUL_OIDX_SIZ  (sizeof(knh_asmc_jmp_ifnonul_oidx_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	knh_vmc_u1_t a2;
} knh_asmc_iter_t;

typedef struct {
	knh_asmc_t code;
	knh_class_t a1;
	knh_vmc_u1_t a2;
	void *w;
} knh_asmc_iter_tw;

#define KNH_ASMC_ITER_SIZ  (sizeof(knh_asmc_iter_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_class_t a2;
	knh_vmc_u1_t a3;
	knh_vmc_u1_t a4;
} knh_asmc_foreach_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_class_t a2;
	knh_vmc_u1_t a3;
	knh_vmc_u1_t a4;
	void *w;
} knh_asmc_foreach_tw;

#define KNH_ASMC_FOREACH_SIZ  (sizeof(knh_asmc_foreach_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
	knh_vmc_u1_t a3;
} knh_asmc_try_begin_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_vmc_u1_t a2;
	knh_vmc_u1_t a3;
	void *w;
} knh_asmc_try_begin_tw;

#define KNH_ASMC_TRY_BEGIN_SIZ  (sizeof(knh_asmc_try_begin_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
} knh_asmc_try_end_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	void *w;
} knh_asmc_try_end_tw;

#define KNH_ASMC_TRY_END_SIZ  (sizeof(knh_asmc_try_end_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_expt_t a2;
	knh_vmc_u1_t a3;
} knh_asmc_catch_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_addr_t a1;
	knh_expt_t a2;
	knh_vmc_u1_t a3;
	void *w;
} knh_asmc_catch_tw;

#define KNH_ASMC_CATCH_SIZ  (sizeof(knh_asmc_catch_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_i1_t a1;
} knh_asmc_throw_ebp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_i1_t a1;
	void *w;
} knh_asmc_throw_ebp_tw;

#define KNH_ASMC_THROW_ebp_SIZ  (sizeof(knh_asmc_throw_ebp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
} knh_asmc_throw_sfp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	void *w;
} knh_asmc_throw_sfp_tw;

#define KNH_ASMC_THROW_sfp_SIZ  (sizeof(knh_asmc_throw_sfp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	Object* a1;
} knh_asmc_throw_obj_t;

typedef struct {
	knh_asmc_t code;
	Object* a1;
	void *w;
} knh_asmc_throw_obj_tw;

#define KNH_ASMC_THROW_OBJ_SIZ  (sizeof(knh_asmc_throw_obj_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
	knh_methodn_t a2;
	knh_vmc_i1_t a3;
} knh_asmc_print_ebp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
	knh_methodn_t a2;
	knh_vmc_i1_t a3;
	void *w;
} knh_asmc_print_ebp_tw;

#define KNH_ASMC_PRINT_ebp_SIZ  (sizeof(knh_asmc_print_ebp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
	knh_methodn_t a2;
	knh_vmc_u1_t a3;
} knh_asmc_print_sfp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
	knh_methodn_t a2;
	knh_vmc_u1_t a3;
	void *w;
} knh_asmc_print_sfp_tw;

#define KNH_ASMC_PRINT_sfp_SIZ  (sizeof(knh_asmc_print_sfp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
	knh_methodn_t a2;
	knh_vmc_u1_t a3;
} knh_asmc_print_ofp_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
	knh_methodn_t a2;
	knh_vmc_u1_t a3;
	void *w;
} knh_asmc_print_ofp_tw;

#define KNH_ASMC_PRINT_ofp_SIZ  (sizeof(knh_asmc_print_ofp_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
	knh_methodn_t a2;
	Object* a3;
} knh_asmc_print_obj_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
	knh_methodn_t a2;
	Object* a3;
	void *w;
} knh_asmc_print_obj_tw;

#define KNH_ASMC_PRINT_OBJ_SIZ  (sizeof(knh_asmc_print_obj_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
	knh_methodn_t a2;
	knh_vmc_u1_t a4;
	Object* a3;
} knh_asmc_print_oidx_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u2_t a1;
	knh_methodn_t a2;
	knh_vmc_u1_t a4;
	Object* a3;
	void *w;
} knh_asmc_print_oidx_tw;

#define KNH_ASMC_PRINT_OIDX_SIZ  (sizeof(knh_asmc_print_oidx_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
} knh_asmc_diagnose_t;

typedef struct {
	knh_asmc_t code;
	knh_vmc_u1_t a1;
	void *w;
} knh_asmc_diagnose_tw;

#define KNH_ASMC_DIAGNOSE_SIZ  (sizeof(knh_asmc_diagnose_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
} knh_asmc_stackdump_t;

typedef struct {
	knh_asmc_t code;
	void *w;
} knh_asmc_stackdump_tw;

#define KNH_ASMC_STACKDUMP_SIZ  (sizeof(knh_asmc_stackdump_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_asmc_t code;
} knh_asmc_nop_t;

typedef struct {
	knh_asmc_t code;
	void *w;
} knh_asmc_nop_tw;

#define KNH_ASMC_NOP_SIZ  (sizeof(knh_asmc_nop_tw)-sizeof(void*))

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

/* ======================================================================== */

#endif/*KONOHAC_ASM__H*/
