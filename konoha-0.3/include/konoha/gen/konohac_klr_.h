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

#ifndef KONOHAC_KLR__H
#define KONOHAC_KLR__H

#include<konoha/konoha_dev.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */
knh_code_t* KNH_ASM_HALT_(Ctx *ctx, Asm *o);
knh_code_t* KNH_ASM_MOVa_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_MOVn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_MOVo_(Ctx *ctx, Asm *o,knh_sfi_t a1,Object* a2);
knh_code_t* KNH_ASM_MOVx_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfx_t a2);
knh_code_t* KNH_ASM_MOVDEF_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_class_t a2);
knh_code_t* KNH_ASM_MOVSYS_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_ushort_t a2);
knh_code_t* KNH_ASM_XMOVs_(Ctx *ctx, Asm *o,knh_sfx_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_XMOVo_(Ctx *ctx, Asm *o,knh_sfx_t a1,Object* a2);
knh_code_t* KNH_ASM_XMOVx_(Ctx *ctx, Asm *o,knh_sfx_t a1,knh_sfx_t a2);
knh_code_t* KNH_ASM_XMOVDEF_(Ctx *ctx, Asm *o,knh_sfx_t a1,knh_class_t a2);
knh_code_t* KNH_ASM_XMOVSYS_(Ctx *ctx, Asm *o,knh_sfx_t a1,knh_ushort_t a2);
knh_code_t* KNH_ASM_MOVxi_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfx_t a2);
knh_code_t* KNH_ASM_XMOVsi_(Ctx *ctx, Asm *o,knh_sfx_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_XMOVxi_(Ctx *ctx, Asm *o,knh_sfx_t a1,knh_sfx_t a2);
knh_code_t* KNH_ASM_MOVxf_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfx_t a2);
knh_code_t* KNH_ASM_XMOVsf_(Ctx *ctx, Asm *o,knh_sfx_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_XMOVxf_(Ctx *ctx, Asm *o,knh_sfx_t a1,knh_sfx_t a2);
knh_code_t* KNH_ASM_MOVxb_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfx_t a2);
knh_code_t* KNH_ASM_XMOVsb_(Ctx *ctx, Asm *o,knh_sfx_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_XMOVxb_(Ctx *ctx, Asm *o,knh_sfx_t a1,knh_sfx_t a2);
knh_code_t* KNH_ASM_SWAP_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_PINIo_(Ctx *ctx, Asm *o,knh_sfi_t a1,Object* a2);
knh_code_t* KNH_ASM_SETESP_(Ctx *ctx, Asm *o,knh_sfi_t a1);
knh_code_t* KNH_ASM_CHECKESP_(Ctx *ctx, Asm *o,knh_sfi_t a1);
knh_code_t* KNH_ASM_RET_(Ctx *ctx, Asm *o);
knh_code_t* KNH_ASM_RETn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_RETa_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_RETo_(Ctx *ctx, Asm *o,knh_sfi_t a1,Object* a2);
knh_code_t* KNH_ASM_RETx_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfx_t a2);
knh_code_t* KNH_ASM_BOX_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_class_t a2);
knh_code_t* KNH_ASM_BOXnc_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_class_t a2);
knh_code_t* KNH_ASM_NNBOX_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_class_t a2);
knh_code_t* KNH_ASM_NNBOXnc_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_class_t a2);
knh_code_t* KNH_ASM_UNBOX_(Ctx *ctx, Asm *o,knh_sfi_t a1);
knh_code_t* KNH_ASM_ISNULL_(Ctx *ctx, Asm *o,knh_sfi_t a1);
knh_code_t* KNH_ASM_ISNULLx_(Ctx *ctx, Asm *o,knh_sfx_t a1);
knh_code_t* KNH_ASM_ISTYPE_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_class_t a2);
knh_code_t* KNH_ASM_ISNNTYPE_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_type_t a2);
knh_code_t* KNH_ASM_FCALL_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_ushort_t a2,knh_sfi_t a3,Object* a4);
knh_code_t* KNH_ASM_SCALL_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_ushort_t a2,Object* a3);
knh_code_t* KNH_ASM_AINVOKE_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_ushort_t a2,Object* a3);
knh_code_t* KNH_ASM_CALL_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_ushort_t a2,knh_methodn_t a3);
knh_code_t* KNH_ASM_ACALL_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_ushort_t a2,knh_methodn_t a3);
knh_code_t* KNH_ASM_NEW_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_flag_t a2,knh_class_t a3,knh_ushort_t a4,Object* a5);
knh_code_t* KNH_ASM_TOSTR_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_methodn_t a2);
knh_code_t* KNH_ASM_TOSTRf_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_methodn_t a2,Object* a3);
knh_code_t* KNH_ASM_SMAP_(Ctx *ctx, Asm *o,knh_sfi_t a1,Object* a2);
knh_code_t* KNH_ASM_SMAPnc_(Ctx *ctx, Asm *o,knh_sfi_t a1,Object* a2);
knh_code_t* KNH_ASM_MAP_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_class_t a2);
knh_code_t* KNH_ASM_MAPnc_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_class_t a2);
knh_code_t* KNH_ASM_AMAP_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_class_t a2);
knh_code_t* KNH_ASM_NNMAP_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_class_t a2);
knh_code_t* KNH_ASM_JMP_(Ctx *ctx, Asm *o,knh_labelid_t a1);
knh_code_t* KNH_ASM_bJIFT_(Ctx *ctx, Asm *o,knh_labelid_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_bJIFF_(Ctx *ctx, Asm *o,knh_labelid_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_bJIFF_LOOP_(Ctx *ctx, Asm *o,knh_labelid_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_JIFNUL_(Ctx *ctx, Asm *o,knh_labelid_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_JIFNN_(Ctx *ctx, Asm *o,knh_labelid_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_NEXT_(Ctx *ctx, Asm *o,knh_labelid_t a1,knh_sfi_t a2,knh_sfi_t a3,knh_sfi_t a4);
knh_code_t* KNH_ASM_INEXT_(Ctx *ctx, Asm *o,knh_labelid_t a1,knh_class_t a2,knh_sfi_t a3,knh_sfi_t a4,knh_sfi_t a5);
knh_code_t* KNH_ASM_MAPNEXT_(Ctx *ctx, Asm *o,knh_labelid_t a1,knh_class_t a2,knh_sfi_t a3,knh_sfi_t a4,knh_sfi_t a5);
knh_code_t* KNH_ASM_SMAPNEXT_(Ctx *ctx, Asm *o,knh_labelid_t a1,knh_sfi_t a2,knh_sfi_t a3,knh_sfi_t a4,Object* a5);
knh_code_t* KNH_ASM_TRY_(Ctx *ctx, Asm *o,knh_labelid_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_TRYEND_(Ctx *ctx, Asm *o,knh_sfi_t a1);
knh_code_t* KNH_ASM_CATCH_(Ctx *ctx, Asm *o,knh_labelid_t a1,knh_sfi_t a2,knh_sfi_t a3,Object* a4);
knh_code_t* KNH_ASM_THROW_(Ctx *ctx, Asm *o,knh_sfi_t a1);
knh_code_t* KNH_ASM_THROWs_(Ctx *ctx, Asm *o,Object* a1);
knh_code_t* KNH_ASM_THROW_AGAIN_(Ctx *ctx, Asm *o,knh_sfi_t a1);
knh_code_t* KNH_ASM_P_(Ctx *ctx, Asm *o,knh_flag_t a1,knh_methodn_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_PMSG_(Ctx *ctx, Asm *o,knh_flag_t a1,Object* a2);
knh_code_t* KNH_ASM_iCAST_(Ctx *ctx, Asm *o,knh_sfi_t a1);
knh_code_t* KNH_ASM_inCAST_(Ctx *ctx, Asm *o,knh_sfi_t a1);
knh_code_t* KNH_ASM_fCAST_(Ctx *ctx, Asm *o,knh_sfi_t a1);
knh_code_t* KNH_ASM_fnCAST_(Ctx *ctx, Asm *o,knh_sfi_t a1);
knh_code_t* KNH_ASM_bNOT_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_iNEG_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_iADD_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_iADDn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_int_t a3);
knh_code_t* KNH_ASM_iSUB_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_iSUBn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_int_t a3);
knh_code_t* KNH_ASM_iMUL_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_iMULn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_int_t a3);
knh_code_t* KNH_ASM_iDIV_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_iDIVn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_int_t a3);
knh_code_t* KNH_ASM_iMOD_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_iMODn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_int_t a3);
knh_code_t* KNH_ASM_iEQ_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_iEQn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_int_t a3);
knh_code_t* KNH_ASM_iNEQ_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_iNEQn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_int_t a3);
knh_code_t* KNH_ASM_iLT_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_iLTn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_int_t a3);
knh_code_t* KNH_ASM_iLTE_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_iLTEn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_int_t a3);
knh_code_t* KNH_ASM_iGT_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_iGTn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_int_t a3);
knh_code_t* KNH_ASM_iGTE_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_iGTEn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_int_t a3);
knh_code_t* KNH_ASM_fNEG_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2);
knh_code_t* KNH_ASM_fADD_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_fADDn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_float_t a3);
knh_code_t* KNH_ASM_fSUB_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_fSUBn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_float_t a3);
knh_code_t* KNH_ASM_fMUL_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_fMULn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_float_t a3);
knh_code_t* KNH_ASM_fDIV_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_fDIVn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_float_t a3);
knh_code_t* KNH_ASM_fEQ_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_fEQn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_float_t a3);
knh_code_t* KNH_ASM_fNEQ_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_fNEQn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_float_t a3);
knh_code_t* KNH_ASM_fLT_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_fLTn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_float_t a3);
knh_code_t* KNH_ASM_fLTE_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_fLTEn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_float_t a3);
knh_code_t* KNH_ASM_fGT_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_fGTn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_float_t a3);
knh_code_t* KNH_ASM_fGTE_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_sfi_t a3);
knh_code_t* KNH_ASM_fGTEn_(Ctx *ctx, Asm *o,knh_sfi_t a1,knh_sfi_t a2,knh_float_t a3);
knh_code_t* KNH_ASM_INITCODE_(Ctx *ctx, Asm *o,knh_sfi_t a1);
knh_code_t* KNH_ASM_NOP_(Ctx *ctx, Asm *o);
void knh_Asm_remapAddress(Ctx *ctx, Asm *o);
void knh_code_traverse(Ctx *ctx, knh_code_t *pc, knh_ftraverse ftr);
METHOD knh_KLRCode_exec(Ctx *ctx, knh_sfp_t *sfp);
void knh_code_generate(Ctx *ctx, Asm *abr, knh_code_t *pc_start, OutputStream *w);

#define OPCODE_HALT ((knh_opcode_t)0)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	void *nextaddr;
} klr_halt_t;

#define OPSIZE_HALT  (sizeof(klr_halt_t)-sizeof(void*))

#define OPCODE_MOVA ((knh_opcode_t)1)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	void *nextaddr;
} klr_mova_t;

#define OPSIZE_MOVA  (sizeof(klr_mova_t)-sizeof(void*))

#define OPCODE_MOVN ((knh_opcode_t)2)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	void *nextaddr;
} klr_movn_t;

#define OPSIZE_MOVN  (sizeof(klr_movn_t)-sizeof(void*))

#define OPCODE_MOVO ((knh_opcode_t)3)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	Object* a2;
	void *nextaddr;
} klr_movo_t;

#define OPSIZE_MOVO  (sizeof(klr_movo_t)-sizeof(void*))

#define OPCODE_MOVX ((knh_opcode_t)4)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfx_t a2;
	void *nextaddr;
} klr_movx_t;

#define OPSIZE_MOVX  (sizeof(klr_movx_t)-sizeof(void*))

#define OPCODE_MOVDEF ((knh_opcode_t)5)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_class_t a2;
	void *nextaddr;
} klr_movdef_t;

#define OPSIZE_MOVDEF  (sizeof(klr_movdef_t)-sizeof(void*))

#define OPCODE_MOVSYS ((knh_opcode_t)6)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_ushort_t a2;
	void *nextaddr;
} klr_movsys_t;

#define OPSIZE_MOVSYS  (sizeof(klr_movsys_t)-sizeof(void*))

#define OPCODE_XMOVS ((knh_opcode_t)7)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfx_t a1;
	knh_sfi_t a2;
	void *nextaddr;
} klr_xmovs_t;

#define OPSIZE_XMOVS  (sizeof(klr_xmovs_t)-sizeof(void*))

#define OPCODE_XMOVO ((knh_opcode_t)8)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfx_t a1;
	Object* a2;
	void *nextaddr;
} klr_xmovo_t;

#define OPSIZE_XMOVO  (sizeof(klr_xmovo_t)-sizeof(void*))

#define OPCODE_XMOVX ((knh_opcode_t)9)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfx_t a1;
	knh_sfx_t a2;
	void *nextaddr;
} klr_xmovx_t;

#define OPSIZE_XMOVX  (sizeof(klr_xmovx_t)-sizeof(void*))

#define OPCODE_XMOVDEF ((knh_opcode_t)10)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfx_t a1;
	knh_class_t a2;
	void *nextaddr;
} klr_xmovdef_t;

#define OPSIZE_XMOVDEF  (sizeof(klr_xmovdef_t)-sizeof(void*))

#define OPCODE_XMOVSYS ((knh_opcode_t)11)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfx_t a1;
	knh_ushort_t a2;
	void *nextaddr;
} klr_xmovsys_t;

#define OPSIZE_XMOVSYS  (sizeof(klr_xmovsys_t)-sizeof(void*))

#define OPCODE_MOVXI ((knh_opcode_t)12)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfx_t a2;
	void *nextaddr;
} klr_movxi_t;

#define OPSIZE_MOVXI  (sizeof(klr_movxi_t)-sizeof(void*))

#define OPCODE_XMOVSI ((knh_opcode_t)13)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfx_t a1;
	knh_sfi_t a2;
	void *nextaddr;
} klr_xmovsi_t;

#define OPSIZE_XMOVSI  (sizeof(klr_xmovsi_t)-sizeof(void*))

#define OPCODE_XMOVXI ((knh_opcode_t)14)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfx_t a1;
	knh_sfx_t a2;
	void *nextaddr;
} klr_xmovxi_t;

#define OPSIZE_XMOVXI  (sizeof(klr_xmovxi_t)-sizeof(void*))

#define OPCODE_MOVXF ((knh_opcode_t)15)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfx_t a2;
	void *nextaddr;
} klr_movxf_t;

#define OPSIZE_MOVXF  (sizeof(klr_movxf_t)-sizeof(void*))

#define OPCODE_XMOVSF ((knh_opcode_t)16)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfx_t a1;
	knh_sfi_t a2;
	void *nextaddr;
} klr_xmovsf_t;

#define OPSIZE_XMOVSF  (sizeof(klr_xmovsf_t)-sizeof(void*))

#define OPCODE_XMOVXF ((knh_opcode_t)17)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfx_t a1;
	knh_sfx_t a2;
	void *nextaddr;
} klr_xmovxf_t;

#define OPSIZE_XMOVXF  (sizeof(klr_xmovxf_t)-sizeof(void*))

#define OPCODE_MOVXB ((knh_opcode_t)18)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfx_t a2;
	void *nextaddr;
} klr_movxb_t;

#define OPSIZE_MOVXB  (sizeof(klr_movxb_t)-sizeof(void*))

#define OPCODE_XMOVSB ((knh_opcode_t)19)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfx_t a1;
	knh_sfi_t a2;
	void *nextaddr;
} klr_xmovsb_t;

#define OPSIZE_XMOVSB  (sizeof(klr_xmovsb_t)-sizeof(void*))

#define OPCODE_XMOVXB ((knh_opcode_t)20)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfx_t a1;
	knh_sfx_t a2;
	void *nextaddr;
} klr_xmovxb_t;

#define OPSIZE_XMOVXB  (sizeof(klr_xmovxb_t)-sizeof(void*))

#define OPCODE_SWAP ((knh_opcode_t)21)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	void *nextaddr;
} klr_swap_t;

#define OPSIZE_SWAP  (sizeof(klr_swap_t)-sizeof(void*))

#define OPCODE_PINIO ((knh_opcode_t)22)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	Object* a2;
	void *nextaddr;
} klr_pinio_t;

#define OPSIZE_PINIO  (sizeof(klr_pinio_t)-sizeof(void*))

#define OPCODE_SETESP ((knh_opcode_t)23)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	void *nextaddr;
} klr_setesp_t;

#define OPSIZE_SETESP  (sizeof(klr_setesp_t)-sizeof(void*))

#define OPCODE_CHECKESP ((knh_opcode_t)24)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	void *nextaddr;
} klr_checkesp_t;

#define OPSIZE_CHECKESP  (sizeof(klr_checkesp_t)-sizeof(void*))

#define OPCODE_RET ((knh_opcode_t)25)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	void *nextaddr;
} klr_ret_t;

#define OPSIZE_RET  (sizeof(klr_ret_t)-sizeof(void*))

#define OPCODE_RETN ((knh_opcode_t)26)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	void *nextaddr;
} klr_retn_t;

#define OPSIZE_RETN  (sizeof(klr_retn_t)-sizeof(void*))

#define OPCODE_RETA ((knh_opcode_t)27)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	void *nextaddr;
} klr_reta_t;

#define OPSIZE_RETA  (sizeof(klr_reta_t)-sizeof(void*))

#define OPCODE_RETO ((knh_opcode_t)28)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	Object* a2;
	void *nextaddr;
} klr_reto_t;

#define OPSIZE_RETO  (sizeof(klr_reto_t)-sizeof(void*))

#define OPCODE_RETX ((knh_opcode_t)29)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfx_t a2;
	void *nextaddr;
} klr_retx_t;

#define OPSIZE_RETX  (sizeof(klr_retx_t)-sizeof(void*))

#define OPCODE_BOX ((knh_opcode_t)30)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_class_t a2;
	void *nextaddr;
} klr_box_t;

#define OPSIZE_BOX  (sizeof(klr_box_t)-sizeof(void*))

#define OPCODE_BOXNC ((knh_opcode_t)31)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_class_t a2;
	void *nextaddr;
} klr_boxnc_t;

#define OPSIZE_BOXNC  (sizeof(klr_boxnc_t)-sizeof(void*))

#define OPCODE_NNBOX ((knh_opcode_t)32)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_class_t a2;
	void *nextaddr;
} klr_nnbox_t;

#define OPSIZE_NNBOX  (sizeof(klr_nnbox_t)-sizeof(void*))

#define OPCODE_NNBOXNC ((knh_opcode_t)33)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_class_t a2;
	void *nextaddr;
} klr_nnboxnc_t;

#define OPSIZE_NNBOXNC  (sizeof(klr_nnboxnc_t)-sizeof(void*))

#define OPCODE_UNBOX ((knh_opcode_t)34)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	void *nextaddr;
} klr_unbox_t;

#define OPSIZE_UNBOX  (sizeof(klr_unbox_t)-sizeof(void*))

#define OPCODE_ISNULL ((knh_opcode_t)35)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	void *nextaddr;
} klr_isnull_t;

#define OPSIZE_ISNULL  (sizeof(klr_isnull_t)-sizeof(void*))

#define OPCODE_ISNULLX ((knh_opcode_t)36)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfx_t a1;
	void *nextaddr;
} klr_isnullx_t;

#define OPSIZE_ISNULLX  (sizeof(klr_isnullx_t)-sizeof(void*))

#define OPCODE_ISTYPE ((knh_opcode_t)37)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_class_t a2;
	void *nextaddr;
} klr_istype_t;

#define OPSIZE_ISTYPE  (sizeof(klr_istype_t)-sizeof(void*))

#define OPCODE_ISNNTYPE ((knh_opcode_t)38)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_type_t a2;
	void *nextaddr;
} klr_isnntype_t;

#define OPSIZE_ISNNTYPE  (sizeof(klr_isnntype_t)-sizeof(void*))

#define OPCODE_FCALL ((knh_opcode_t)39)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_ushort_t a2;
	knh_sfi_t a3;
	Object* a4;
	void *nextaddr;
} klr_fcall_t;

#define OPSIZE_FCALL  (sizeof(klr_fcall_t)-sizeof(void*))

#define OPCODE_SCALL ((knh_opcode_t)40)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_ushort_t a2;
	Object* a3;
	void *nextaddr;
} klr_scall_t;

#define OPSIZE_SCALL  (sizeof(klr_scall_t)-sizeof(void*))

#define OPCODE_AINVOKE ((knh_opcode_t)41)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_ushort_t a2;
	Object* a3;
	void *nextaddr;
} klr_ainvoke_t;

#define OPSIZE_AINVOKE  (sizeof(klr_ainvoke_t)-sizeof(void*))

#define OPCODE_CALL ((knh_opcode_t)42)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_ushort_t a2;
	knh_methodn_t a3;
	void *nextaddr;
} klr_call_t;

#define OPSIZE_CALL  (sizeof(klr_call_t)-sizeof(void*))

#define OPCODE_ACALL ((knh_opcode_t)43)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_ushort_t a2;
	knh_methodn_t a3;
	void *nextaddr;
} klr_acall_t;

#define OPSIZE_ACALL  (sizeof(klr_acall_t)-sizeof(void*))

#define OPCODE_NEW ((knh_opcode_t)44)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_flag_t a2;
	knh_class_t a3;
	knh_ushort_t a4;
	Object* a5;
	void *nextaddr;
} klr_new_t;

#define OPSIZE_NEW  (sizeof(klr_new_t)-sizeof(void*))

#define OPCODE_TOSTR ((knh_opcode_t)45)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_methodn_t a2;
	void *nextaddr;
} klr_tostr_t;

#define OPSIZE_TOSTR  (sizeof(klr_tostr_t)-sizeof(void*))

#define OPCODE_TOSTRF ((knh_opcode_t)46)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_methodn_t a2;
	Object* a3;
	void *nextaddr;
} klr_tostrf_t;

#define OPSIZE_TOSTRF  (sizeof(klr_tostrf_t)-sizeof(void*))

#define OPCODE_SMAP ((knh_opcode_t)47)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	Object* a2;
	void *nextaddr;
} klr_smap_t;

#define OPSIZE_SMAP  (sizeof(klr_smap_t)-sizeof(void*))

#define OPCODE_SMAPNC ((knh_opcode_t)48)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	Object* a2;
	void *nextaddr;
} klr_smapnc_t;

#define OPSIZE_SMAPNC  (sizeof(klr_smapnc_t)-sizeof(void*))

#define OPCODE_MAP ((knh_opcode_t)49)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_class_t a2;
	void *nextaddr;
} klr_map_t;

#define OPSIZE_MAP  (sizeof(klr_map_t)-sizeof(void*))

#define OPCODE_MAPNC ((knh_opcode_t)50)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_class_t a2;
	void *nextaddr;
} klr_mapnc_t;

#define OPSIZE_MAPNC  (sizeof(klr_mapnc_t)-sizeof(void*))

#define OPCODE_AMAP ((knh_opcode_t)51)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_class_t a2;
	void *nextaddr;
} klr_amap_t;

#define OPSIZE_AMAP  (sizeof(klr_amap_t)-sizeof(void*))

#define OPCODE_NNMAP ((knh_opcode_t)52)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_class_t a2;
	void *nextaddr;
} klr_nnmap_t;

#define OPSIZE_NNMAP  (sizeof(klr_nnmap_t)-sizeof(void*))

#define OPCODE_JMP ((knh_opcode_t)53)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
#ifdef KNH_USING_THREADEDCODE
	void *jumpaddr;
#endif/*KNH_USING_THREADEDCODE*/
	union {
		knh_labelid_t a1;  /* labelid */
		knh_code_t *jumppc;
	};
	void *nextaddr;
} klr_jmp_t;

#define OPSIZE_JMP  (sizeof(klr_jmp_t)-sizeof(void*))

#define OPCODE_BJIFT ((knh_opcode_t)54)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
#ifdef KNH_USING_THREADEDCODE
	void *jumpaddr;
#endif/*KNH_USING_THREADEDCODE*/
	union {
		knh_labelid_t a1;  /* labelid */
		knh_code_t *jumppc;
	};
	knh_sfi_t a2;
	void *nextaddr;
} klr_bjift_t;

#define OPSIZE_BJIFT  (sizeof(klr_bjift_t)-sizeof(void*))

#define OPCODE_BJIFF ((knh_opcode_t)55)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
#ifdef KNH_USING_THREADEDCODE
	void *jumpaddr;
#endif/*KNH_USING_THREADEDCODE*/
	union {
		knh_labelid_t a1;  /* labelid */
		knh_code_t *jumppc;
	};
	knh_sfi_t a2;
	void *nextaddr;
} klr_bjiff_t;

#define OPSIZE_BJIFF  (sizeof(klr_bjiff_t)-sizeof(void*))

#define OPCODE_BJIFF_LOOP ((knh_opcode_t)56)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
#ifdef KNH_USING_THREADEDCODE
	void *jumpaddr;
#endif/*KNH_USING_THREADEDCODE*/
	union {
		knh_labelid_t a1;  /* labelid */
		knh_code_t *jumppc;
	};
	knh_sfi_t a2;
	void *nextaddr;
} klr_bjiff_loop_t;

#define OPSIZE_BJIFF_LOOP  (sizeof(klr_bjiff_loop_t)-sizeof(void*))

#define OPCODE_JIFNUL ((knh_opcode_t)57)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
#ifdef KNH_USING_THREADEDCODE
	void *jumpaddr;
#endif/*KNH_USING_THREADEDCODE*/
	union {
		knh_labelid_t a1;  /* labelid */
		knh_code_t *jumppc;
	};
	knh_sfi_t a2;
	void *nextaddr;
} klr_jifnul_t;

#define OPSIZE_JIFNUL  (sizeof(klr_jifnul_t)-sizeof(void*))

#define OPCODE_JIFNN ((knh_opcode_t)58)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
#ifdef KNH_USING_THREADEDCODE
	void *jumpaddr;
#endif/*KNH_USING_THREADEDCODE*/
	union {
		knh_labelid_t a1;  /* labelid */
		knh_code_t *jumppc;
	};
	knh_sfi_t a2;
	void *nextaddr;
} klr_jifnn_t;

#define OPSIZE_JIFNN  (sizeof(klr_jifnn_t)-sizeof(void*))

#define OPCODE_NEXT ((knh_opcode_t)59)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
#ifdef KNH_USING_THREADEDCODE
	void *jumpaddr;
#endif/*KNH_USING_THREADEDCODE*/
	union {
		knh_labelid_t a1;  /* labelid */
		knh_code_t *jumppc;
	};
	knh_sfi_t a2;
	knh_sfi_t a3;
	knh_sfi_t a4;
	void *nextaddr;
} klr_next_t;

#define OPSIZE_NEXT  (sizeof(klr_next_t)-sizeof(void*))

#define OPCODE_INEXT ((knh_opcode_t)60)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
#ifdef KNH_USING_THREADEDCODE
	void *jumpaddr;
#endif/*KNH_USING_THREADEDCODE*/
	union {
		knh_labelid_t a1;  /* labelid */
		knh_code_t *jumppc;
	};
	knh_class_t a2;
	knh_sfi_t a3;
	knh_sfi_t a4;
	knh_sfi_t a5;
	void *nextaddr;
} klr_inext_t;

#define OPSIZE_INEXT  (sizeof(klr_inext_t)-sizeof(void*))

#define OPCODE_MAPNEXT ((knh_opcode_t)61)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
#ifdef KNH_USING_THREADEDCODE
	void *jumpaddr;
#endif/*KNH_USING_THREADEDCODE*/
	union {
		knh_labelid_t a1;  /* labelid */
		knh_code_t *jumppc;
	};
	knh_class_t a2;
	knh_sfi_t a3;
	knh_sfi_t a4;
	knh_sfi_t a5;
	void *nextaddr;
} klr_mapnext_t;

#define OPSIZE_MAPNEXT  (sizeof(klr_mapnext_t)-sizeof(void*))

#define OPCODE_SMAPNEXT ((knh_opcode_t)62)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
#ifdef KNH_USING_THREADEDCODE
	void *jumpaddr;
#endif/*KNH_USING_THREADEDCODE*/
	union {
		knh_labelid_t a1;  /* labelid */
		knh_code_t *jumppc;
	};
	knh_sfi_t a2;
	knh_sfi_t a3;
	knh_sfi_t a4;
	Object* a5;
	void *nextaddr;
} klr_smapnext_t;

#define OPSIZE_SMAPNEXT  (sizeof(klr_smapnext_t)-sizeof(void*))

#define OPCODE_TRY ((knh_opcode_t)63)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
#ifdef KNH_USING_THREADEDCODE
	void *jumpaddr;
#endif/*KNH_USING_THREADEDCODE*/
	union {
		knh_labelid_t a1;  /* labelid */
		knh_code_t *jumppc;
	};
	knh_sfi_t a2;
	void *nextaddr;
} klr_try_t;

#define OPSIZE_TRY  (sizeof(klr_try_t)-sizeof(void*))

#define OPCODE_TRYEND ((knh_opcode_t)64)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	void *nextaddr;
} klr_tryend_t;

#define OPSIZE_TRYEND  (sizeof(klr_tryend_t)-sizeof(void*))

#define OPCODE_CATCH ((knh_opcode_t)65)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
#ifdef KNH_USING_THREADEDCODE
	void *jumpaddr;
#endif/*KNH_USING_THREADEDCODE*/
	union {
		knh_labelid_t a1;  /* labelid */
		knh_code_t *jumppc;
	};
	knh_sfi_t a2;
	knh_sfi_t a3;
	Object* a4;
	void *nextaddr;
} klr_catch_t;

#define OPSIZE_CATCH  (sizeof(klr_catch_t)-sizeof(void*))

#define OPCODE_THROW ((knh_opcode_t)66)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	void *nextaddr;
} klr_throw_t;

#define OPSIZE_THROW  (sizeof(klr_throw_t)-sizeof(void*))

#define OPCODE_THROWS ((knh_opcode_t)67)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	Object* a1;
	void *nextaddr;
} klr_throws_t;

#define OPSIZE_THROWS  (sizeof(klr_throws_t)-sizeof(void*))

#define OPCODE_THROW_AGAIN ((knh_opcode_t)68)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	void *nextaddr;
} klr_throw_again_t;

#define OPSIZE_THROW_AGAIN  (sizeof(klr_throw_again_t)-sizeof(void*))

#define OPCODE_P ((knh_opcode_t)69)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_flag_t a1;
	knh_methodn_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_p_t;

#define OPSIZE_P  (sizeof(klr_p_t)-sizeof(void*))

#define OPCODE_PMSG ((knh_opcode_t)70)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_flag_t a1;
	Object* a2;
	void *nextaddr;
} klr_pmsg_t;

#define OPSIZE_PMSG  (sizeof(klr_pmsg_t)-sizeof(void*))

#define OPCODE_ICAST ((knh_opcode_t)71)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	void *nextaddr;
} klr_icast_t;

#define OPSIZE_ICAST  (sizeof(klr_icast_t)-sizeof(void*))

#define OPCODE_INCAST ((knh_opcode_t)72)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	void *nextaddr;
} klr_incast_t;

#define OPSIZE_INCAST  (sizeof(klr_incast_t)-sizeof(void*))

#define OPCODE_FCAST ((knh_opcode_t)73)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	void *nextaddr;
} klr_fcast_t;

#define OPSIZE_FCAST  (sizeof(klr_fcast_t)-sizeof(void*))

#define OPCODE_FNCAST ((knh_opcode_t)74)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	void *nextaddr;
} klr_fncast_t;

#define OPSIZE_FNCAST  (sizeof(klr_fncast_t)-sizeof(void*))

#define OPCODE_BNOT ((knh_opcode_t)75)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	void *nextaddr;
} klr_bnot_t;

#define OPSIZE_BNOT  (sizeof(klr_bnot_t)-sizeof(void*))

#define OPCODE_INEG ((knh_opcode_t)76)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	void *nextaddr;
} klr_ineg_t;

#define OPSIZE_INEG  (sizeof(klr_ineg_t)-sizeof(void*))

#define OPCODE_IADD ((knh_opcode_t)77)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_iadd_t;

#define OPSIZE_IADD  (sizeof(klr_iadd_t)-sizeof(void*))

#define OPCODE_IADDN ((knh_opcode_t)78)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_int_t a3;
	void *nextaddr;
} klr_iaddn_t;

#define OPSIZE_IADDN  (sizeof(klr_iaddn_t)-sizeof(void*))

#define OPCODE_ISUB ((knh_opcode_t)79)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_isub_t;

#define OPSIZE_ISUB  (sizeof(klr_isub_t)-sizeof(void*))

#define OPCODE_ISUBN ((knh_opcode_t)80)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_int_t a3;
	void *nextaddr;
} klr_isubn_t;

#define OPSIZE_ISUBN  (sizeof(klr_isubn_t)-sizeof(void*))

#define OPCODE_IMUL ((knh_opcode_t)81)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_imul_t;

#define OPSIZE_IMUL  (sizeof(klr_imul_t)-sizeof(void*))

#define OPCODE_IMULN ((knh_opcode_t)82)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_int_t a3;
	void *nextaddr;
} klr_imuln_t;

#define OPSIZE_IMULN  (sizeof(klr_imuln_t)-sizeof(void*))

#define OPCODE_IDIV ((knh_opcode_t)83)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_idiv_t;

#define OPSIZE_IDIV  (sizeof(klr_idiv_t)-sizeof(void*))

#define OPCODE_IDIVN ((knh_opcode_t)84)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_int_t a3;
	void *nextaddr;
} klr_idivn_t;

#define OPSIZE_IDIVN  (sizeof(klr_idivn_t)-sizeof(void*))

#define OPCODE_IMOD ((knh_opcode_t)85)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_imod_t;

#define OPSIZE_IMOD  (sizeof(klr_imod_t)-sizeof(void*))

#define OPCODE_IMODN ((knh_opcode_t)86)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_int_t a3;
	void *nextaddr;
} klr_imodn_t;

#define OPSIZE_IMODN  (sizeof(klr_imodn_t)-sizeof(void*))

#define OPCODE_IEQ ((knh_opcode_t)87)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_ieq_t;

#define OPSIZE_IEQ  (sizeof(klr_ieq_t)-sizeof(void*))

#define OPCODE_IEQN ((knh_opcode_t)88)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_int_t a3;
	void *nextaddr;
} klr_ieqn_t;

#define OPSIZE_IEQN  (sizeof(klr_ieqn_t)-sizeof(void*))

#define OPCODE_INEQ ((knh_opcode_t)89)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_ineq_t;

#define OPSIZE_INEQ  (sizeof(klr_ineq_t)-sizeof(void*))

#define OPCODE_INEQN ((knh_opcode_t)90)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_int_t a3;
	void *nextaddr;
} klr_ineqn_t;

#define OPSIZE_INEQN  (sizeof(klr_ineqn_t)-sizeof(void*))

#define OPCODE_ILT ((knh_opcode_t)91)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_ilt_t;

#define OPSIZE_ILT  (sizeof(klr_ilt_t)-sizeof(void*))

#define OPCODE_ILTN ((knh_opcode_t)92)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_int_t a3;
	void *nextaddr;
} klr_iltn_t;

#define OPSIZE_ILTN  (sizeof(klr_iltn_t)-sizeof(void*))

#define OPCODE_ILTE ((knh_opcode_t)93)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_ilte_t;

#define OPSIZE_ILTE  (sizeof(klr_ilte_t)-sizeof(void*))

#define OPCODE_ILTEN ((knh_opcode_t)94)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_int_t a3;
	void *nextaddr;
} klr_ilten_t;

#define OPSIZE_ILTEN  (sizeof(klr_ilten_t)-sizeof(void*))

#define OPCODE_IGT ((knh_opcode_t)95)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_igt_t;

#define OPSIZE_IGT  (sizeof(klr_igt_t)-sizeof(void*))

#define OPCODE_IGTN ((knh_opcode_t)96)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_int_t a3;
	void *nextaddr;
} klr_igtn_t;

#define OPSIZE_IGTN  (sizeof(klr_igtn_t)-sizeof(void*))

#define OPCODE_IGTE ((knh_opcode_t)97)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_igte_t;

#define OPSIZE_IGTE  (sizeof(klr_igte_t)-sizeof(void*))

#define OPCODE_IGTEN ((knh_opcode_t)98)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_int_t a3;
	void *nextaddr;
} klr_igten_t;

#define OPSIZE_IGTEN  (sizeof(klr_igten_t)-sizeof(void*))

#define OPCODE_FNEG ((knh_opcode_t)99)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	void *nextaddr;
} klr_fneg_t;

#define OPSIZE_FNEG  (sizeof(klr_fneg_t)-sizeof(void*))

#define OPCODE_FADD ((knh_opcode_t)100)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_fadd_t;

#define OPSIZE_FADD  (sizeof(klr_fadd_t)-sizeof(void*))

#define OPCODE_FADDN ((knh_opcode_t)101)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_float_t a3;
	void *nextaddr;
} klr_faddn_t;

#define OPSIZE_FADDN  (sizeof(klr_faddn_t)-sizeof(void*))

#define OPCODE_FSUB ((knh_opcode_t)102)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_fsub_t;

#define OPSIZE_FSUB  (sizeof(klr_fsub_t)-sizeof(void*))

#define OPCODE_FSUBN ((knh_opcode_t)103)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_float_t a3;
	void *nextaddr;
} klr_fsubn_t;

#define OPSIZE_FSUBN  (sizeof(klr_fsubn_t)-sizeof(void*))

#define OPCODE_FMUL ((knh_opcode_t)104)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_fmul_t;

#define OPSIZE_FMUL  (sizeof(klr_fmul_t)-sizeof(void*))

#define OPCODE_FMULN ((knh_opcode_t)105)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_float_t a3;
	void *nextaddr;
} klr_fmuln_t;

#define OPSIZE_FMULN  (sizeof(klr_fmuln_t)-sizeof(void*))

#define OPCODE_FDIV ((knh_opcode_t)106)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_fdiv_t;

#define OPSIZE_FDIV  (sizeof(klr_fdiv_t)-sizeof(void*))

#define OPCODE_FDIVN ((knh_opcode_t)107)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_float_t a3;
	void *nextaddr;
} klr_fdivn_t;

#define OPSIZE_FDIVN  (sizeof(klr_fdivn_t)-sizeof(void*))

#define OPCODE_FEQ ((knh_opcode_t)108)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_feq_t;

#define OPSIZE_FEQ  (sizeof(klr_feq_t)-sizeof(void*))

#define OPCODE_FEQN ((knh_opcode_t)109)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_float_t a3;
	void *nextaddr;
} klr_feqn_t;

#define OPSIZE_FEQN  (sizeof(klr_feqn_t)-sizeof(void*))

#define OPCODE_FNEQ ((knh_opcode_t)110)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_fneq_t;

#define OPSIZE_FNEQ  (sizeof(klr_fneq_t)-sizeof(void*))

#define OPCODE_FNEQN ((knh_opcode_t)111)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_float_t a3;
	void *nextaddr;
} klr_fneqn_t;

#define OPSIZE_FNEQN  (sizeof(klr_fneqn_t)-sizeof(void*))

#define OPCODE_FLT ((knh_opcode_t)112)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_flt_t;

#define OPSIZE_FLT  (sizeof(klr_flt_t)-sizeof(void*))

#define OPCODE_FLTN ((knh_opcode_t)113)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_float_t a3;
	void *nextaddr;
} klr_fltn_t;

#define OPSIZE_FLTN  (sizeof(klr_fltn_t)-sizeof(void*))

#define OPCODE_FLTE ((knh_opcode_t)114)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_flte_t;

#define OPSIZE_FLTE  (sizeof(klr_flte_t)-sizeof(void*))

#define OPCODE_FLTEN ((knh_opcode_t)115)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_float_t a3;
	void *nextaddr;
} klr_flten_t;

#define OPSIZE_FLTEN  (sizeof(klr_flten_t)-sizeof(void*))

#define OPCODE_FGT ((knh_opcode_t)116)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_fgt_t;

#define OPSIZE_FGT  (sizeof(klr_fgt_t)-sizeof(void*))

#define OPCODE_FGTN ((knh_opcode_t)117)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_float_t a3;
	void *nextaddr;
} klr_fgtn_t;

#define OPSIZE_FGTN  (sizeof(klr_fgtn_t)-sizeof(void*))

#define OPCODE_FGTE ((knh_opcode_t)118)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_sfi_t a3;
	void *nextaddr;
} klr_fgte_t;

#define OPSIZE_FGTE  (sizeof(klr_fgte_t)-sizeof(void*))

#define OPCODE_FGTEN ((knh_opcode_t)119)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	knh_sfi_t a2;
	knh_float_t a3;
	void *nextaddr;
} klr_fgten_t;

#define OPSIZE_FGTEN  (sizeof(klr_fgten_t)-sizeof(void*))

#define OPCODE_INITCODE ((knh_opcode_t)120)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	knh_sfi_t a1;
	void *nextaddr;
} klr_initcode_t;

#define OPSIZE_INITCODE  (sizeof(klr_initcode_t)-sizeof(void*))

#define OPCODE_NOP ((knh_opcode_t)121)
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
	void *nextaddr;
} klr_nop_t;

#define OPSIZE_NOP  (sizeof(klr_nop_t)-sizeof(void*))

#ifdef __cplusplus
}
#endif

/* ======================================================================== */

#endif/*KONOHAC_KLR__H*/
