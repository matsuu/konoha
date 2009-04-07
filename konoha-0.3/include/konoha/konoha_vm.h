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

#ifdef OLDVM
/* ======================================================================== */

#define VM_DEBUG_ASSERT(c)        KNH_ASSERT(c)

int knh_Method_pctoline(Method *mtd, knh_code_t *pc);
#define _HERE_    knh_Method_file(sfp[-1].mtd), knh_Method_pctoline(sfp[-1].mtd, pc)

/* ======================================================================== */

//#define esp_(n)                   ((Context*)ctx)->esp[n]
#define esp_(n)                   ((Context*)ctx)->esp[(n)].o
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
#define VM_ESP(ctx,n)             ((Context*)ctx)->esp[n].o
//#define VM_FILE                   ""
//#define VM_LINE                   0

/* ======================================================================== */
/* [BOXING/UNBOXING] */


/* ======================================================================== */


/* ======================================================================== */

#define VM_MOV__ngc(ctx, v1, v2)   \
	knh_Object_RCinc(v2); \
	knh_Object_RCdec((Object*)v1); \
	v1 = v2; \

#ifdef KNH_USING_DRCGC
#define VM_MOV(ctx, v1, v2)  VM_MOV__ngc(ctx, v1, v2)

#else/*KNH_USING_DRCGC*/
#define VM_MOV(ctx, v1, v2)   \
	knh_Object_RCinc(v2); \
	knh_Object_RCdec(v1); \
	if(knh_Object_isRC0(v1)) { \
		knh_Object_free(ctx, v1); \
	} \
	v1 = v2; \

#endif/*KNH_USING_DRCGC*/


/* ======================================================================== */

#define VM_HALT(ctx)  \
	KNH_THROWs(ctx, "Halt!!");     \

#define VM_RET(ctx, v)      \
	VM_MOV__ngc(ctx, sfp[-1].o, v); \
	return ; \

#define VM_RET__OIDX(ctx, v, idx)      \
	VM_MOV__ngc(ctx, sfp[-1].o, oidx_(v, idx)); \
	return ; \

//#define VM_MOV_(ctx,v,v2)            KNH_SETv(ctx,v,v2)

#define VM_MOVE(ctx,v,v2)            VM_MOV(ctx,v,v2)
#define VM_MOVS(ctx,v,v2)            VM_MOV(ctx,v,v2)
#define VM_MOVO(ctx,v,v2)            VM_MOV(ctx,v,v2)
#define VM_MOVI(ctx,o,idx,v2)        VM_MOV(ctx,oidx_(o,idx),v2)

#define VM_MOVE__OIDX(ctx,v,o,idx)          VM_MOV(ctx,v,oidx_(o,idx))
#define VM_MOVS__OIDX(ctx,v,o,idx)          VM_MOV(ctx,v,oidx_(o,idx))
#define VM_MOVO__OIDX(ctx,v,o,idx)          VM_MOV(ctx,v,oidx_(o,idx))
#define VM_MOVI__OIDX(ctx,o,idx,o2,idx2)    VM_MOV(ctx,oidx_(o,idx),oidx_(o2,idx2))

#define VM_MOVSFP_IFNUL(ctx, n, v2) \
	if(IS_NULL(sfp[n].o)) {\
		KNH_SETv(ctx, sfp[n].o, v2);\
	}\


/* ======================================================================== */

#define VM_BBOXS(ctx, n) { \
		KNH_SETv(ctx, sfp[n].o, sfp[n].bvalue == 0 ? KNH_FALSE : KNH_TRUE);\
	}\

#define VM_BUNBOXS(ctx, n) { \
		sfp[n].bvalue = IS_TRUE(sfp[n].o);\
	}\

#define VM_BBOXE(ctx, n) { \
		KNH_SETv(ctx, esp[n].o, esp[n].bvalue == 0 ? KNH_FALSE : KNH_TRUE);\
	}\

#define VM_BUNBOXE(ctx, n) { \
		esp[n].bvalue = IS_TRUE(esp[n].o);\
	}\

#define VM_IBOXS(ctx, n) { \
		KNH_SETv(ctx, sfp[n].o, new_Int(ctx, sfp[n].ivalue));\
	}\

#define VM_IUNBOXS(ctx, n) { \
		sfp[n].ivalue = (sfp[n].i)->value;\
	}\

#define VM_IBOXE(ctx, n) { \
		KNH_SETv(ctx, esp[n].o, new_Int(ctx, esp[n].ivalue));\
	}\

#define VM_IUNBOXE(ctx, n) { \
		esp[n].ivalue = (esp[n].i)->value;\
	}\

#define VM_FBOXS(ctx, n) { \
		KNH_SETv(ctx, sfp[n].o, new_Int(ctx, sfp[n].fvalue));\
	}\

#define VM_FUNBOXS(ctx, n) { \
		sfp[n].fvalue = (sfp[n].f)->value;\
	}\

#define VM_FBOXE(ctx, n) { \
		KNH_SETv(ctx, esp[n].o, new_Int(ctx, esp[n].fvalue));\
	}\

#define VM_FUNBOXE(ctx, n) { \
		esp[n].fvalue = (esp[n].f)->value;\
	}\

/* ======================================================================== */

#define _VM_PUT_(ctx,v) \
	VM_MOV(ctx, ((Context*)ctx)->esp[0].o, v); \

#define _VM_PUTI_(ctx,i) \
	((Context*)ctx)->esp[0].op = (knh_stackop_t)i; \

#define _VM_PUSHI_(ctx,v) \
	((Context*)ctx)->esp++; \
	((Context*)ctx)->esp[0].op = (knh_stackop_t)v; \

#define _VM_PUSH__MN_(ctx,mn) \
	((Context*)ctx)->esp++; \
	((Context*)ctx)->esp[0].op = (knh_uint_t)mn; \

#define VM_PUSH(ctx,v) \
	((Context*)ctx)->esp++; \
	VM_MOV(ctx, ((Context*)ctx)->esp[0].o, v); \

#define VM_PUSH__OIDX(ctx, v, idx) \
	((Context*)ctx)->esp++; \
	VM_MOV(ctx, ((Context*)ctx)->esp[0].o, oidx_(v,idx)); \

#define VM_SHIFT(ctx,n) \
	((Context*)ctx)->esp += (n); \

#define VM_PUSH__DEF(ctx, cid) \
	((Context*)ctx)->esp++; \
	KNH_SETv(ctx, ((Context*)ctx)->esp[0].o, knh_ClassTable_defaultValue(ctx, CLASS_type(cid))); \

#define KNH_SYS_CTX    0
#define KNH_SYS_STDIN  1
#define KNH_SYS_STDOUT 2
#define KNH_SYS_STDERR 3

#define VM_PUT_SYSCONST(ctx, n) { \
		VM_MOV(ctx, ((Context*)ctx)->esp[0].o, knh_tConst_systemValue(ctx, n)); \
	}\

#define VM_PUSH_SYSCONST(ctx, n) { \
		((Context*)ctx)->esp++; \
		VM_MOV(ctx, ((Context*)ctx)->esp[0].o, knh_tConst_systemValue(ctx, n)); \
	}\

#define VM_VARGV(ctx, n) { \
		KNH_SETv(ctx, sfp[n].o, knh_sfp_toArray(ctx, &sfp[n-1])); \
		((Context*)ctx)->esp = &sfp[n]; \
	} \

/* ------------------------------------------------------------------------ */

#define KNH_CHECKSTACK(ctx) \
	if(unlikely((ctx)->stacksize - ((ctx)->esp - (ctx)->stack) < 256)) {\
		KNH_THROWs(ctx, "StackOverflow!!"); \
	}\

#define KNH_SCALL(ctx, n) { \
		KNH_CHECKSTACK(ctx); \
		knh_sfp_t *mbp_ = ctx->esp - (n) ; \
		KNH_CHECKSTACK(ctx); \
		KNH_ASSERT(IS_Method(mbp_[0].mtd)); \
		mbp_[0].op = 0; \
		(mbp_[0].mtd)->fcall_1(ctx, mbp_ + 1); \
		mbp_[0].op = 0; \
		((Context*)ctx)->esp = mbp_; \
	} \

#define VM_SCALL(ctx, n) { \
		KNH_CHECKSTACK(ctx); \
		knh_sfp_t *mbp_ = ((Context*)ctx)->esp - (n) ; \
		KNH_ASSERT(IS_Method(mbp_[0].mtd)); \
		KNH_ASSERT(IS_NOTNULL(mbp_[1].o) || knh_Method_isNullBase(mbp_[0].mtd)); \
		mbp_[0].op = (knh_stackop_t)pc; \
		(mbp_[0].mtd)->fcall_1(ctx, mbp_ + 1); \
		mbp_[0].op = 0; \
		((Context*)ctx)->esp = mbp_; \
	} \

#define VM_NSCALL(ctx, n) { \
		KNH_CHECKSTACK(ctx); \
		knh_sfp_t *mbp_ = ((Context*)ctx)->esp - (n) ; \
		if(unlikely(IS_NULL(mbp_[1].o))) { \
			knh_throwException(ctx, new_Exception__Nue(ctx, (Nue*)(mbp_[1].o)), _HERE_); \
		} \
		else { \
			KNH_ASSERT(IS_Method(mbp_[0].mtd)); \
			mbp_[0].op = (knh_stackop_t)pc; \
			(mbp_[0].mtd)->fcall_1(ctx, mbp_ + 1); \
			mbp_[0].op = 0; \
		} \
		((Context*)ctx)->esp = mbp_; \
	} \

#define VM_CALL(ctx, n, mn) { \
		KNH_CHECKSTACK(ctx); \
		knh_sfp_t *mbp_ = ctx->esp - (n) ; \
		KNH_SETv(ctx, mbp_[0].o, konoha_lookupMethod(ctx, knh_Object_cid(mbp_[1].o), mn)); \
		KNH_ASSERT(IS_Method(mbp_[0].mtd)); \
		mbp_[0].op = (knh_stackop_t)pc; \
		(mbp_[0].mtd)->fcall_1(ctx, mbp_ + 1); \
		mbp_[0].op = 0; \
		((Context*)ctx)->esp = mbp_; \
	} \

#define VM_DCALL(ctx, n, mn) { \
		KNH_CHECKSTACK(ctx); \
		knh_sfp_t *mbp_ = ((Context*)ctx)->esp - (n) ; \
		KNH_SETv(ctx, mbp_[0].o, konoha_lookupMethod(ctx, knh_Object_cid(mbp_[1].o), mn)); \
		KNH_ASSERT(IS_Method(mbp_[0].mtd)); \
		mbp_[0].op = (knh_stackop_t)pc; \
		knh_dynamiccall(ctx, mbp_); \
		(mbp_[0].mtd)->fcall_1(ctx, mbp_ + 1); \
		mbp_[0].op = 0; \
		((Context*)ctx)->esp = mbp_; \
	} \


#define VM_SMAP(ctx, mpr)  { \
		knh_Mapper_t *mpr_ = (knh_Mapper_t*)mpr; \
		VM_DEBUG_ASSERT(IS_Mapper(mpr)); \
		KNH_SETv(ctx, esp_(0), (mpr_)->fmap_1(ctx, esp_(0), mpr_)); \
	} \

#define KNH_SMAP(ctx, mpr)  { \
		knh_Mapper_t *mpr_ = (knh_Mapper_t*)mpr; \
		KNH_SETv(ctx, esp_(0), (mpr_)->fmap_1(ctx, esp_(0), mpr_)); \
	} \

#define VM_SMAPE(ctx, mpr)  { \
		knh_Mapper_t *mpr_ = (knh_Mapper_t*)mpr; \
		VM_DEBUG_ASSERT(IS_Mapper(mpr)); \
		KNH_SETv(ctx, esp_(0), (mpr_)->fmap_1(ctx, esp_(0), mpr_)); \
		if(unlikely(IS_NULL(esp_(0)))) { \
			knh_throwException(ctx, new_Exception__Nue(ctx, (Nue*)esp_(0)), _HERE_); \
		} \
	} \

#define VM_MAP(ctx, tcid)  { \
		knh_Mapper_t *mpr_ = knh_tMapper_find(ctx, knh_Object_cid(esp_(0)), tcid); \
		KNH_SETv(ctx, esp_(0), (mpr_)->fmap_1(ctx, esp_(0), mpr_)); \
	} \

#define VM_MAPE(ctx, tcid)  { \
		knh_Mapper_t *mpr_ = knh_tMapper_find(ctx, knh_Object_cid(esp_(0)), tcid); \
		KNH_SETv(ctx, esp_(0), (mpr_)->fmap_1(ctx, esp_(0), mpr_)); \
		if(IS_NULL(esp_(0))) { \
			knh_throwException(ctx, new_Exception__Nue(ctx, (Nue*)esp_(0)), _HERE_); \
		} \
	} \

#define VM_ANYMAP(ctx, tcid)  { \
		if(knh_Object_cid(esp_(0)) != tcid && !knh_class_instanceof(ctx, knh_Object_cid(esp_(0)), tcid)) { \
			knh_Mapper_t *mpr_ = knh_tMapper_find(ctx, knh_Object_cid(esp_(0)), tcid); \
			KNH_SETv(ctx, esp_(0), (mpr_)->fmap_1(ctx, esp_(0), mpr_)); \
		} \
	} \

#define VM_ANYMAPE(ctx, tcid)  { \
		if(knh_Object_cid(esp_(0)) != tcid && !knh_class_instanceof(ctx, knh_Object_cid(esp_(0)), tcid)) { \
			knh_Mapper_t *mpr_ = knh_tMapper_find(ctx, knh_Object_cid(esp_(0)), tcid); \
			KNH_SETv(ctx, esp_(0), (mpr_)->fmap_1(ctx, esp_(0), mpr_)); \
		} \
		if(unlikely(IS_NULL(esp_(0)))) { \
			knh_throwException(ctx, new_Exception__Nue(ctx, (Nue*)esp_(0)), _HERE_); \
		} \
	} \

#define VM_NULLCHK(ctx, v) \
	if(unlikely(IS_NULL(v))) { \
		knh_throwException(ctx, new_Exception__Nue(ctx, (Nue*)v), _HERE_); \
	} \

#define VM_NULLCHK__OIDX(ctx, v, idx) \
	if(unlikely(IS_NULL(oidx_(v,idx)))) { \
		knh_throwException(ctx, new_Exception__Nue(ctx, (Nue*)(oidx_(v,idx))), _HERE_); \
	} \

#define VM_TYPECHK(ctx, type, v) \
	if(unlikely(!knh_Object_opTypeOf(ctx, v, type))) { \
		knh_throwException(ctx, new_Exception__type(ctx, v, type), _HERE_); \
	} \

#define VM_TYPECHK__OIDX(ctx, type, v, idx) \
	if(unlikely(!knh_Object_opTypeOf(ctx, oidx_(v, idx), type))) { \
		knh_throwException(ctx, new_Exception__type(ctx, oidx_(v, idx), type), _HERE_); \
	} \

#define VM_NEW(ctx, n, flag, cid) { \
		knh_sfp_t *mbp_ = ((Context*)ctx)->esp - (n) ; \
		KNH_ASSERT(IS_Method(mbp_[0].mtd)); \
		KNH_SETv(ctx, mbp_[1].o, new_Object__init(ctx, flag, cid)); \
		mbp_[0].op = (knh_stackop_t)pc; \
		(mbp_[0].mtd)->fcall_1(ctx, mbp_ + 1); \
		mbp_[0].op = 0; \
		((Context*)ctx)->esp = mbp_; \
	} \

#define VM_MT(ctx, mn) { \
		knh_sfp_t *mbp_ = ((Context*)ctx)->esp; \
		KNH_SETv(ctx, esp_(0), knh_Object_movableText(ctx, esp_(0), mn, KNH_NULL)); \
		((Context*)ctx)->esp = mbp_; \
	} \

#define VM_MT__FMT(ctx, mn, opt) { \
		knh_sfp_t *mbp_ = ((Context*)ctx)->esp; \
		KNH_SETv(ctx, esp_(0), knh_Object_movableText(ctx, esp_(0), mn, opt)); \
		((Context*)ctx)->esp = mbp_; \
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
	if(IS_TRUE(v)) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFT__OIDX(ctx, PC, JUMP, v, idx) \
	if(IS_TRUE(oidx_(v, idx))) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFF(ctx, PC, JUMP, v) \
	if(IS_FALSE(v)) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFF_oidx_(ctx, PC, JUMP, v, idx) \
	if(IS_FALSE(oidx_(v, idx))) { \
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

/* ------------------------------------------------------------------------- */

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
			KNH_SETv(ctx, esp_(0), (it_)->fnext_1(ctx, it_)); \
			if(IS_NULL(esp_(0))) { \
				VM_JMP(ctx, PC, JUMP); \
			} \
			KNH_SETv(ctx, v, (mpr_)->fmap_1(ctx, esp_(0), mpr_)); \
		}while(IS_NULL(v)); \
	} \

#define VM_MAPNEXT(ctx, PC, JUMP, v, it, tcid)  { \
		knh_Iterator_t *it_ = (knh_Iterator_t*)it; \
		KNH_ASSERT(IS_bIterator(it_)); \
		do { \
			KNH_SETv(ctx, esp_(0), (it_)->fnext_1(ctx, it_)); \
			if(IS_NULL(esp_(0))) { \
				VM_JMP(ctx, PC, JUMP); \
			} \
			knh_Mapper_t *mpr_ = knh_tMapper_find(ctx, knh_Object_cid(esp_(0)), tcid); \
			KNH_SETv(ctx, v, (mpr_)->fmap_1(ctx, esp_(0), mpr_)); \
		}while(IS_NULL(v)); \
	} \

/* ------------------------------------------------------------------------ */

#define KNH_TRY(ctx, JUMP, hdr, e)  {\
		ExceptionHandler* _hdr = (ExceptionHandler*)hdr; \
		if(!knh_ExceptionHandler_isJumpable(_hdr)) { \
			knh_ExceptionHandler_setJumpable(_hdr, 1); \
			int jump = KNH_SETJUMP(_hdr); \
			if(jump != 0) { \
				KNH_SETv(ctx, e, DP(_hdr)->caught); \
				VM_JMP(ctx, NPC, JUMP); \
			} \
		} \
		knh_ExceptionHandler_setCatching(_hdr, 1); \
	} \

#define VM_TRY(ctx, PC, JUMP, hdr, esfp)  {\
		ExceptionHandler* _hdr = (ExceptionHandler*)hdr; \
		if(!IS_ExceptionHandler(_hdr)) { \
			_hdr = new_ExceptionHandler(ctx); \
			KNH_SETv(ctx, hdr, _hdr); \
		} \
		if(!knh_ExceptionHandler_isJumpable(_hdr)) { \
			knh_ExceptionHandler_setJumpable(_hdr, 1); \
			int jump = KNH_SETJUMP(_hdr); \
			if(jump != 0) { \
				pc = (knhvmc_t*)DP(_hdr)->pc; \
				KNH_SETv(ctx, esfp, DP(_hdr)->caught); \
				DBG2_P("JUMPED jump=%d .. %p", jump, esfp); \
				VM_JMP(ctx, PC, JUMP); \
			} \
			DP(_hdr)->pc = pc; \
		} \
		knh_ExceptionHandler_setCatching(_hdr, 1); \
	} \

#define VM_TRY_WC(ctx, PC, JUMP, hdr)  {\
		ExceptionHandler* _hdr = (ExceptionHandler*)hdr; \
		if(!IS_ExceptionHandler(_hdr)) { \
			_hdr = new_ExceptionHandler(ctx); \
			KNH_SETv(ctx, hdr, _hdr); \
		} \
		if(!knh_ExceptionHandler_isJumpable(_hdr)) { \
			knh_ExceptionHandler_setJumpable(_hdr, 1); \
			int jump = KNH_SETJUMP(_hdr); \
			if(jump != 0) { \
				DBG2_P("JUMPED jump=%d ..", jump); \
				pc = (knhvmc_t*)DP(_hdr)->pc; \
				VM_JMP(ctx, PC, JUMP); \
			} \
			DP(_hdr)->pc = pc; \
		} \
		knh_ExceptionHandler_setCatching(_hdr, 1); \
	} \

#define VM_TRY_END(ctx, hdr)  {\
		ExceptionHandler* _hdr = (ExceptionHandler*)hdr; \
		KNH_ASSERT(IS_ExceptionHandler(_hdr)); \
		knh_ExceptionHandler_setCatching(_hdr, 0); \
	} \

#define VM_CATCH(ctx, PC, JUMP, emsg, esfp) { \
		Exception* _e = (Exception*)esfp; \
		KNH_ASSERT(IS_String(emsg)); \
		KNH_ASSERT(IS_Exception(_e)); \
		DBG2_P("CATCHING(%s eid=%d, %s).. %p", knh_String_tochar((String*)emsg), DP(_e)->eid, knh_String_tochar(DP(_e)->message), sfp); \
		if(!knh_Exception_isa(ctx, _e, (String*)emsg)) { \
			VM_JMP(ctx, PC, JUMP); \
		} \
	} \

#define VM_THROW_AGAIN(ctx, hdr) { \
		KNH_ASSERT(IS_ExceptionHandler(hdr)); \
		Exception *_e = (Exception*)DP(((ExceptionHandler*)(hdr)))->caught; \
		DBG2_P("THROW AGAIN .. %s", knh_String_tochar(DP(_e)->message)); \
		knh_throwException(ctx, _e, NULL, 0); \
	} \

/* ------------------------------------------------------------------------ */

#define VM_THROW(ctx, e) \
	if(IS_bString((e))) { \
		knh_throwException(ctx, new_Exception(ctx, (String*)(e)), _HERE_); \
	}else if(IS_Exception((e))) { \
		knh_throwException(ctx, (Exception*)(e), _HERE_); \
	}else { \
		knh_throwException(ctx, new_Exception__type(ctx, (e), CLASS_Exception), _HERE_); \
	} \

#define VM_THROW_oidx_(ctx, v, idx) {\
		Object *e_ = oidx_(v, idx); \
		if(IS_bString((e_))) { \
			knh_throwException(ctx, new_Exception(ctx, (String*)(e_)), _HERE_); \
		}else if(IS_Exception((e_))) { \
			knh_throwException(ctx, (Exception*)(e_), _HERE_); \
		}else { \
			knh_throwException(ctx, new_Exception__type(ctx, (e_), CLASS_Exception), _HERE_); \
		} \
	}

/* ------------------------------------------------------------------------ */

#define VM_PRINT(ctx, flag, s, mn, v) \
	knh_sfp_print(ctx, sfp, flag, s, mn, v)

#define VM_STACKDUMP(ctx)   knh_sfp_dump(ctx, sfp)

/* ------------------------------------------------------------------------ */

#define VM_INIT(ctx) { \
		KLRCode *c_ = (KLRCode*)DP(sfp[-1].mtd)->code; \
		knhvmc_codethreading(ctx, pc, globalMachineToJump); \
		DP(c_)->code = pc + KNH_ASMC_INIT_SIZ; \
		DP(c_)->size = DP(c_)->size - KNH_ASMC_INIT_SIZ; \
		return; \
	}\

/* ------------------------------------------------------------------------ */

#define VM_IADD(ctx) { \
		((Context*)ctx)->esp--; \
		Object *n_ = UP(new_Int(ctx, ((Int*)(esp_(0)))->value + ((Int*)(esp_(1)))->value)); \
		VM_MOV(ctx, ((Context*)ctx)->esp[0].o, n_); \
	}\

#define VM_ISUB(ctx) { \
		((Context*)ctx)->esp--; \
		Object *n_ = UP(new_Int(ctx, ((Int*)(esp_(0)))->value - ((Int*)(esp_(1)))->value)); \
		VM_MOV(ctx, ((Context*)ctx)->esp[0].o, n_); \
	}\

#define VM_ILT(ctx) { \
		((Context*)ctx)->esp--; \
		Object *n_ = (((Int*)(esp_(0)))->value < ((Int*)(esp_(1)))->value) ? KNH_TRUE : KNH_FALSE ; \
		VM_MOV(ctx, ((Context*)ctx)->esp[0].o, n_); \
	}\

#define VM_NOP(ctx)

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */



/* ------------------------------------------------------------------------ */

#endif

#ifdef __cplusplus
}
#endif

#endif /*KONOHA_VM_H_*/
