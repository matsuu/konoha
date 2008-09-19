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

#include "konoha_gc.h"

#ifndef KONOHA_VM_H_
#define KONOHA_VM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */

#define VM_DEBUG_ASSERT(c)        KNH_ASSERT(c)

int knh_Method_pctoline(Method *mtd, knhvmc_t *pc);

/* ======================================================================== */

//#define ebp_(n)                   ((Context*)ctx)->ebp[n]
#define ebp_(n)                   ((Context*)ctx)->ebp[(n)].o
#define sfp_(n)                   sfp[(n)].o
#define ofp_(n)                   KNH_FIELDn(sfp[0].o, (n))
#define oidx_(o,idx)              KNH_FIELDn((o), (idx))
#define i1_(n)                    (n)
#define u1_(n)                    (n)
#define u2_(n)                    (n)
#define mn_(n)                    (knh_methodn_t)(n)
#define c2_(n)                    (knh_class_t)(n)
#define e2_(n)                    (knh_expt_t)(n)
#define OBJ_(o)                   (o)

/* ------------------------------------------------------------------------ */

/* ======================================================================== */

#define NPC
#define VM_EBP(ctx,n)             ((Context*)ctx)->ebp[n].o
#define VM_FILE                   ""
#define VM_LINE                   0

/* ======================================================================== */

#define VM_MOV(ctx, v1, v2)   \
	knh_Object_RCinc(v2); \
	knh_Object_RCdec(v1); \
	if(knh_Object_isRC0(v1)) { \
		knh_Object_free(ctx, v1); \
	} \
	v1 = v2; \

#define VM_MOV__ngc(ctx, v1, v2)   \
	knh_Object_RCinc(v2); \
	knh_Object_RCdec((Object*)v1); \
	v1 = v2; \

#define METHOD_RETURN(ctx, sfp, v)      {\
		Object *retval_ = (Object*)(v); \
		VM_MOV__ngc(ctx, sfp[-1].o, retval_); \
		return; \
	}\

#define METHOD_RETURN_BOOLEAN(ctx, sfp, c)      {\
		if((c)) { \
			VM_MOV__ngc(ctx, sfp[-1].o, KNH_TRUE); \
		}else { \
			VM_MOV__ngc(ctx, sfp[-1].o, KNH_FALSE); \
		} \
		return; \
	}\

#define VM_HALT(ctx)  \
	KNH_THROWs(ctx, "Halt!!");     \

#define VM_RET(ctx, v)      \
	VM_MOV__ngc(ctx, sfp[-1].o, v); \
	return; \

#define VM_RET__OIDX(ctx, v, idx)      \
	VM_MOV__ngc(ctx, sfp[-1].o, oidx_(v, idx)); \
	return; \

#define VM_MOV_(ctx,v,v2)            KNH_SETv(ctx,v,v2)

#define VM_MOVE(ctx,v,v2)            VM_MOV(ctx,v,v2)
#define VM_MOVS(ctx,v,v2)            VM_MOV(ctx,v,v2)
#define VM_MOVO(ctx,v,v2)            VM_MOV(ctx,v,v2)
#define VM_MOVI(ctx,o,idx,v2)        VM_MOV(ctx,oidx_(o,idx),v2)

#define VM_MOVE__OIDX(ctx,v,o,idx)   VM_MOV(ctx,v,oidx_(o,idx))
#define VM_MOVS__OIDX(ctx,v,o,idx)   VM_MOV(ctx,v,oidx_(o,idx))
#define VM_MOVO__OIDX(ctx,v,o,idx)   VM_MOV(ctx,v,oidx_(o,idx))
#define VM_MOVI__OIDX(ctx,o,idx,o2,idx2)   VM_MOV(ctx,oidx_(o,idx),oidx_(o2,idx2))

#define VM_MOVSFP_IFNUL(ctx, n, v2) \
	if(IS_NULL(sfp[n].o)) {\
		KNH_SETv(ctx, sfp[n].o, v2);\
	}\

#define _VM_PUT_(ctx,v) \
	VM_MOV(ctx, ((Context*)ctx)->ebp[0].o, v); \

#define _VM_PUTI_(ctx,i) \
	((Context*)ctx)->ebp[0].op = (knh_stackop_t)i; \

#define _VM_PUSHI_(ctx,v) \
	((Context*)ctx)->ebp++; \
	((Context*)ctx)->ebp[0].op = (knh_stackop_t)v; \

#define _VM_PUSH__MN_(ctx,mn) \
	((Context*)ctx)->ebp++; \
	((Context*)ctx)->ebp[0].op = (knh_uint_t)mn; \

#define VM_PUSH(ctx,v) \
	((Context*)ctx)->ebp++; \
	VM_MOV(ctx, ((Context*)ctx)->ebp[0].o, v); \

#define VM_PUSH__OIDX(ctx, v, idx) \
	((Context*)ctx)->ebp++; \
	VM_MOV(ctx, ((Context*)ctx)->ebp[0].o, oidx_(v,idx)); \


#define VM_SHIFT(ctx,n) \
	((Context*)ctx)->ebp += (n); \

#define VM_PUSH__DEF(ctx, cid) \
	((Context*)ctx)->ebp++; \
	KNH_SETv(ctx, ((Context*)ctx)->ebp[0].o, knh_tClass_defaultValue(ctx, TYPE_UNMASK(cid))); \

#define VM_CONST_CTX    0
#define VM_CONST_STDIN  1
#define VM_CONST_STDOUT 2
#define VM_CONST_STDERR 3

#define VM_PUT_SYSCONST(ctx, n) { \
		VM_MOV(ctx, ((Context*)ctx)->ebp[0].o, knh_tConst_systemValue(ctx, n)); \
	}\

#define VM_PUSH_SYSCONST(ctx, n) { \
		((Context*)ctx)->ebp++; \
		VM_MOV(ctx, ((Context*)ctx)->ebp[0].o, knh_tConst_systemValue(ctx, n)); \
	}\

#define VM_VARGV(ctx, n) { \
		KNH_SETv(ctx, sfp[n].o, knh_sfp_toArray(ctx, &sfp[n-1])); \
		((Context*)ctx)->ebp = &sfp[n]; \
	} \

#define KNH_SCALL(ctx, n) { \
		knh_sfp_t *mbp_ = ctx->ebp - (n) ; \
		KNH_ASSERT(IS_Method(mbp_[0].mtd)); \
		mbp_[0].op = 0; \
		(mbp_[0].mtd)->fcall_1(ctx, mbp_ + 1); \
		mbp_[0].op = 0; \
		((Context*)ctx)->ebp = mbp_; \
	} \

#define VM_SCALL(ctx, n) { \
		knh_sfp_t *mbp_ = ((Context*)ctx)->ebp - (n) ; \
		KNH_ASSERT(IS_Method(mbp_[0].mtd)); \
		KNH_ASSERT(IS_NOTNULL(mbp_[1].o)); \
		mbp_[0].op = (knh_stackop_t)pc; \
		(mbp_[0].mtd)->fcall_1(ctx, mbp_ + 1); \
		mbp_[0].op = 0; \
		((Context*)ctx)->ebp = mbp_; \
	} \

#define VM_NSCALL(ctx, n) { \
		knh_sfp_t *mbp_ = ((Context*)ctx)->ebp - (n) ; \
		if(IS_NULL(mbp_[1].o)) { \
			DBG2_P("********* NullPointerException!!************");\
			KNH_SETv(ctx, mbp_[0].o, KNH_NULL); \
		} \
		else { \
			KNH_ASSERT(IS_Method(mbp_[0].mtd)); \
			mbp_[0].op = (knh_stackop_t)pc; \
			(mbp_[0].mtd)->fcall_1(ctx, mbp_ + 1); \
			mbp_[0].op = 0; \
		} \
		((Context*)ctx)->ebp = mbp_; \
	} \


#define VM_CALL(ctx, n, mn) { \
		knh_sfp_t *mbp_ = ctx->ebp - (n) ; \
		KNH_SETv(ctx, mbp_[0].o, knh_Method_ufind(ctx, knh_Object_cid(mbp_[1].o), mn)); \
		KNH_ASSERT(IS_Method(mbp_[0].mtd)); \
		mbp_[0].op = (knh_stackop_t)pc; \
		(mbp_[0].mtd)->fcall_1(ctx, mbp_ + 1); \
		mbp_[0].op = 0; \
		((Context*)ctx)->ebp = mbp_; \
	} \

#define VM_DCALL(ctx, n, mn) { \
		knh_sfp_t *mbp_ = ((Context*)ctx)->ebp - (n) ; \
		KNH_SETv(ctx, mbp_[0].o, knh_Method_ufind(ctx, knh_Object_cid(mbp_[1].o), mn)); \
		KNH_ASSERT(IS_Method(mbp_[0].mtd)); \
		knh_sfp_typecheck__DCALL(ctx, mbp_); \
		mbp_[0].op = (knh_stackop_t)pc; \
		(mbp_[0].mtd)->fcall_1(ctx, mbp_ + 1); \
		mbp_[0].op = 0; \
		((Context*)ctx)->ebp = mbp_; \
	} \


#define VM_SMAP(ctx, mpr)  { \
		knh_Mapper_t *mpr_ = (knh_Mapper_t*)mpr; \
		VM_DEBUG_ASSERT(IS_Mapper(mpr)); \
		KNH_SETv(ctx, ebp_(0), (mpr_)->fmap_1(ctx, ebp_(0), mpr_)); \
	} \

#define KNH_SMAP(ctx, mpr)  { \
		knh_Mapper_t *mpr_ = (knh_Mapper_t*)mpr; \
		KNH_SETv(ctx, ebp_(0), (mpr_)->fmap_1(ctx, ebp_(0), mpr_)); \
	} \

#define VM_SMAPE(ctx, mpr)  { \
		knh_Mapper_t *mpr_ = (knh_Mapper_t*)mpr; \
		VM_DEBUG_ASSERT(IS_Mapper(mpr)); \
		KNH_SETv(ctx, ebp_(0), (mpr_)->fmap_1(ctx, ebp_(0), mpr_)); \
		if(IS_NULL(ebp_(0))) { \
			knh_konohavm_throwException(ctx, new_Exception__Nue(ctx, (Nue*)ebp_(0))); \
		} \
	} \

#define VM_MAP(ctx, tcid)  { \
		knh_Mapper_t *mpr_ = knh_tMapper_find(ctx, knh_Object_cid(ebp_(0)), tcid); \
		KNH_SETv(ctx, ebp_(0), (mpr_)->fmap_1(ctx, ebp_(0), mpr_)); \
	} \

#define VM_MAPE(ctx, tcid)  { \
		knh_Mapper_t *mpr_ = knh_tMapper_find(ctx, knh_Object_cid(ebp_(0)), tcid); \
		KNH_SETv(ctx, ebp_(0), (mpr_)->fmap_1(ctx, ebp_(0), mpr_)); \
		if(IS_NULL(ebp_(0))) { \
			knh_konohavm_throwException(ctx, new_Exception__Nue(ctx, (Nue*)ebp_(0))); \
		} \
	} \

#define VM_ANYMAP(ctx, tcid)  { \
		if(knh_Object_cid(ebp_(0)) != tcid && !knh_class_instanceof(knh_Object_cid(ebp_(0)), tcid)) { \
			knh_Mapper_t *mpr_ = knh_tMapper_find(ctx, knh_Object_cid(ebp_(0)), tcid); \
			KNH_SETv(ctx, ebp_(0), (mpr_)->fmap_1(ctx, ebp_(0), mpr_)); \
		} \
	} \

#define VM_ANYMAPE(ctx, tcid)  { \
		if(knh_Object_cid(ebp_(0)) != tcid && !knh_class_instanceof(knh_Object_cid(ebp_(0)), tcid)) { \
			knh_Mapper_t *mpr_ = knh_tMapper_find(ctx, knh_Object_cid(ebp_(0)), tcid); \
			KNH_SETv(ctx, ebp_(0), (mpr_)->fmap_1(ctx, ebp_(0), mpr_)); \
		} \
		if(IS_NULL(ebp_(0))) { \
			knh_konohavm_throwException(ctx, new_Exception__Nue(ctx, (Nue*)ebp_(0))); \
		} \
	} \

#define VM_NULLCHK(ctx, v) \
	if(IS_NULL(v)) { \
		knh_konohavm_throwException(ctx, new_Exception__Nue(ctx, (Nue*)v)); \
	} \

#define VM_NULLCHK__OIDX(ctx, v, idx) \
	if(IS_NULL(oidx_(v,idx))) { \
		knh_konohavm_throwException(ctx, new_Exception__Nue(ctx, (Nue*)(oidx_(v,idx)))); \
	} \

#define VM_TYPECHK(ctx, type, v) \
	if(!knh_Object_opTypeOf(ctx, v, type)) { \
		knh_konohavm_throwException(ctx, new_Exception__type(ctx, v, type)); \
	} \

#define VM_TYPECHK__OIDX(ctx, type, v, idx) \
	if(!knh_Object_opTypeOf(ctx, oidx_(v, idx), type)) { \
		knh_konohavm_throwException(ctx, new_Exception__type(ctx, oidx_(v, idx), type)); \
	} \

#define VM_NEW(ctx, n, flag, cid) { \
		knh_sfp_t *mbp_ = ((Context*)ctx)->ebp - (n) ; \
		KNH_ASSERT(IS_Method(mbp_[0].mtd)); \
		KNH_SETv(ctx, mbp_[1].o, new_Object__init(ctx, flag, cid)); \
		mbp_[0].op = (knh_stackop_t)pc; \
		(mbp_[0].mtd)->fcall_1(ctx, mbp_ + 1); \
		mbp_[0].op = 0; \
		((Context*)ctx)->ebp = mbp_; \
	} \

#define VM_MT(ctx, mn) { \
		knh_sfp_t *mbp_ = ((Context*)ctx)->ebp; \
		KNH_SETv(ctx, ebp_(0), knh_Object_movableText(ctx, ebp_(0), mn, KNH_NULL)); \
		((Context*)ctx)->ebp = mbp_; \
	} \

#define VM_MT__OPT(ctx, mn, opt) { \
		knh_sfp_t *mbp_ = ((Context*)ctx)->ebp; \
		KNH_SETv(ctx, ebp_(0), knh_Object_movableText(ctx, ebp_(0), mn, opt)); \
		((Context*)ctx)->ebp = mbp_; \
	} \

/* ------------------------------------------------------------------------- */

#define VM_JMP(ctx, PC, JUMP) \
	PC; \
	goto JUMP; \

#define VM_SKIP(ctx, PC, JUMP) \
	if(!knh_Object_isDebug(sfp[0].o)) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFT(ctx, PC, JUMP, v) \
	if(BOOL_ISTRUE(v)) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFT__OIDX(ctx, PC, JUMP, v, idx) \
	if(BOOL_ISTRUE(oidx_(v, idx))) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFF(ctx, PC, JUMP, v) \
	if(BOOL_ISFALSE(v)) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFF_oidx_(ctx, PC, JUMP, v, idx) \
	if(BOOL_ISFALSE(oidx_(v, idx))) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFTNN(ctx, PC, JUMP, v) \
	if(IS_TRUE(v)) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFTNN_oidx_(ctx, PC, JUMP, v, idx) \
	if(IS_TRUE(oidx_(v,idx))) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFFN(ctx, PC, JUMP, v) \
	if(IS_FALSE(v)) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFFN_oidx_(ctx, PC, JUMP, v, idx) \
	if(IS_FALSE(oidx_(v,idx))) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFN(ctx, PC, JUMP, v) \
	if(IS_NULL(v)) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFN_oidx_(ctx, PC, JUMP, v, idx) \
	if(IS_NULL(oidx_(v, idx))) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFNN(ctx, PC, JUMP, v) \
	if(IS_NOTNULL(v)) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFNN_oidx_(ctx, PC, JUMP, v, idx) \
	if(IS_NOTNULL(oidx_(v,idx))) { \
		VM_JMP(ctx, PC, JUMP); \
	} \


#define VM_NEXT(ctx, PC, JUMP, v, it) { \
		knh_Iterator_t *it_ = (knh_Iterator_t*)it; \
		KNH_ASSERT(IS_bIterator(it)); \
		KNH_SETv(ctx, v, (it_)->fnext_1(ctx, it_)); \
		if(IS_NULL(v)) { \
			VM_JMP(ctx, PC, JUMP); \
		} \
	} \

#define VM_SMAPNEXT(ctx, PC, JUMP, v, it, mpr)  { \
		knh_Mapper_t *mpr_ = (knh_Mapper_t*)mpr; \
		VM_DEBUG_ASSERT(IS_Mapper(mpr)); \
		knh_Iterator_t *it_ = (knh_Iterator_t*)it; \
		KNH_ASSERT(IS_bIterator(it_)); \
		do { \
			KNH_SETv(ctx, ebp_(0), (it_)->fnext_1(ctx, it_)); \
			if(IS_NULL(ebp_(0))) { \
				VM_JMP(ctx, PC, JUMP); \
			} \
			KNH_SETv(ctx, v, (mpr_)->fmap_1(ctx, ebp_(0), mpr_)); \
		}while(IS_NULL(v)); \
	} \

#define VM_MAPNEXT(ctx, PC, JUMP, v, it, tcid)  { \
		knh_Iterator_t *it_ = (knh_Iterator_t*)it; \
		KNH_ASSERT(IS_bIterator(it_)); \
		do { \
			KNH_SETv(ctx, ebp_(0), (it_)->fnext_1(ctx, it_)); \
			if(IS_NULL(ebp_(0))) { \
				VM_JMP(ctx, PC, JUMP); \
			} \
			knh_Mapper_t *mpr_ = knh_tMapper_find(ctx, knh_Object_cid(ebp_(0)), tcid); \
			KNH_SETv(ctx, v, (mpr_)->fmap_1(ctx, ebp_(0), mpr_)); \
		}while(IS_NULL(v)); \
	} \

/* ------------------------------------------------------------------------ */

#define VM_TRY_BEGIN(ctx, PC, JUMP, hdr, e)  \
	if(!knh_ExceptionHandler_isCatching(((ExceptionHandler*)(hdr)))) { \
		if(KNH_SETJUMP(((ExceptionHandler*)(hdr))) != 0) { \
			KNH_SETv(ctx, e, DP(((ExceptionHandler*)(hdr)))->caught); \
			VM_JMP(ctx, PC, JUMP); \
		} \
		knh_ExceptionHandler_setCatching(((ExceptionHandler*)(hdr)), 1); \
	} \

#define VM_TRY_END(ctx, hdr) \
	knh_ExceptionHandler_setCatching(((ExceptionHandler*)(hdr)), 0) \

#define _VM_CATCH_(ctx, PC, JUMP, exptid, e) \
	if(!knh_texpt_isa(DP((Exception*)e)->eid, exptid)) { \
		VM_JMP(ctx, PC, JUMP); \
	} \
	knh_Exception_setCaught(e, 1); \

#define VM_THROW(ctx, e) \
	if(IS_bString((e))) { \
		knh_konohavm_throwException(ctx, new_Exception(ctx, (String*)(e))); \
	}else if(IS_Exception((e))) { \
		knh_konohavm_throwException(ctx, (Exception*)(e)); \
	}else { \
		knh_konohavm_throwException(ctx, new_Exception__type(ctx, (e), CLASS_Exception)); \
	} \

#define VM_THROW_oidx_(ctx, v, idx) {\
		Object *e_ = oidx_(v, idx); \
		if(IS_bString((e_))) { \
			knh_konohavm_throwException(ctx, new_Exception(ctx, (String*)(e_))); \
		}else if(IS_Exception((e_))) { \
			knh_konohavm_throwException(ctx, (Exception*)(e_)); \
		}else { \
			knh_konohavm_throwException(ctx, new_Exception__type(ctx, (e_), CLASS_Exception)); \
		} \
	} \

/* ------------------------------------------------------------------------ */

#define VM_PRINT(ctx, flag, s, mn, v) \
	knh_sfp_print(ctx, sfp, flag, s, mn, v)

#define VM_STACKDUMP(ctx)   knh_sfp_dump(ctx, sfp)

#define VM_NOP(ctx)

#ifdef __cplusplus
}
#endif

#endif /*KONOHA_VM_H_*/
