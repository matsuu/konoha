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

#ifndef KONOHA_VM_H_
#define KONOHA_VM_H_

#ifdef __cplusplus 
extern "C" {
#endif

#define VM_DEBUG_ASSERT(c)        DEBUG_ASSERT(c)

/* ======================================================================== */

#define ebp_(n)                   ((Context*)ctx)->ebp[n]
#define sfp_(n)                   sfp[n]
#define ofp_(n)                   KNH_FIELDn(sfp[0], n)
#define oidx_(o,idx)              KNH_FIELDn(o, idx)
#define u1_(n)                    n
#define u2_(n)                    n
#define mn_(n)                    (knh_methodn_t)n
#define c2_(n)                    (knh_type_t)n
#define e2_(n)                    (knh_expt_t)n
#define OBJ_(o)                   o

/* ------------------------------------------------------------------------ */

/* ======================================================================== */

#define NPC                       
#define VM_EBP(ctx,n)             ((Context*)ctx)->ebp[n]
#define VM_FILE                   ""
#define VM_LINE                   0

/* ======================================================================== */

#define VM_MOV(ctx, v1, v2)   \
	knh_Object_head(v2)->refc++; \
	knh_Object_head(v1)->refc--; \
	if(knh_Object_head(v1)->refc == 0) { \
		knh_Object_dispose(ctx, v1); \
	} \
	v1 = v2; \

#define VM_MOV__ngc(ctx, v1, v2)   \
	knh_Object_head(v2)->refc++; \
	knh_Object_head(v1)->refc--; \
	v1 = v2; \

#define KNH_VOID                  KNH_NULL
#define METHOD_RETURN(ctx, sfp, v)      \
	VM_MOV__ngc(ctx, sfp[-1], v);        \
	return; \

#define VM_RET_VOID(ctx)          VM_RET(ctx, KNH_VOID)

#define VM_RET(ctx, v)      \
	VM_MOV__ngc(ctx, sfp[-1], v); \
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
	if(IS_NULL(sfp[n])) {\
		KNH_SETv(ctx, sfp[n], v2);\
	}\

#define VM_PUT(ctx,v) \
	VM_MOV(ctx, ((Context*)ctx)->ebp[0], v); \

#define VM_PUTI(ctx,i) \
	KNH_STACKOP(((Context*)ctx)->ebp) = (knh_stackop_t)i; \

#define VM_PUSHI(ctx,v) \
	((Context*)ctx)->ebp++; \
	KNH_STACKOP(((Context*)ctx)->ebp) = (knh_stackop_t)v; \

#define VM_PUSH(ctx,v) \
	((Context*)ctx)->ebp++; \
	VM_MOV(ctx, ((Context*)ctx)->ebp[0], v); \

#define VM_SHIFT(ctx,n) \
	((Context*)ctx)->ebp += (n); \

#define VM_PUSH__DEF(ctx,cid) \
	((Context*)ctx)->ebp++; \
	KNH_SETv(ctx, ((Context*)ctx)->ebp[0], knh_tclass_safevalue(ctx, cid)); \

#define KNH_SCALL(ctx, n) { \
		Object **mtdp_ = ((Context*)ctx)->ebp - (n) ; \
		VM_DEBUG_ASSERT(IS_Method(mtdp_[0])); \
		KNH_STACKOP(mtdp_) = (knh_stackop_t)0; \
		((Method*)mtdp_[0])->func(ctx, mtdp_ + 1); \
		KNH_STACKOP(mtdp_) = 0; \
		((Context*)ctx)->ebp = mtdp_; \
	} \

#define VM_SCALL(ctx, n) { \
		Object **mtdp_ = ((Context*)ctx)->ebp - (n) ; \
		VM_DEBUG_ASSERT(IS_Method(mtdp_[0])); \
		KNH_STACKOP(mtdp_) = (knh_stackop_t)pc; \
		((Method*)mtdp_[0])->func(ctx, mtdp_ + 1); \
		KNH_STACKOP(mtdp_) = 0; \
		((Context*)ctx)->ebp = mtdp_; \
	} \

#define VM_PUSH__MN(ctx,mn) \
	((Context*)ctx)->ebp++; \
	KNH_STACKOP(((Context*)ctx)->ebp) = (knh_uint_t)mn; \

#define VM_VARGV(ctx, n) { \
		KNH_SETv(ctx, sfp[n], knh_stackf_toArray(ctx, &sfp[n-1])); \
		((Context*)ctx)->ebp = &sfp[n]; \
	} \


#define VM_CALL(ctx, n) { \
		Object **mtdp_ = ((Context*)ctx)->ebp - (n) ; \
		KNH_SETv(ctx, mtdp_[0], knh_Method_ufind(ctx, knh_Object_cid(mtdp_[1]), (knh_methodn_t)KNH_STACKOP(mtdp_))); \
		VM_DEBUG_ASSERT(IS_Method(mtdp_[0])); \
		KNH_STACKOP(mtdp_) = (knh_stackop_t)pc; \
		((Method*)mtdp_[0])->func(ctx, mtdp_ + 1); \
		KNH_STACKOP(mtdp_) = 0; \
		((Context*)ctx)->ebp = mtdp_; \
	} \

#define VM_CALL_WM(ctx, n, mtd) { \
		Object **mtdp_ = ((Context*)ctx)->ebp - (n) ; \
		VM_DEBUG_ASSERT(IS_Method(mtd)); \
		VM_MOV(ctx, mtdp_[0], mtd); \
		KNH_STACKOP(mtdp_) = (knh_stackop_t)pc; \
		((Method*)mtdp_[0])->func(ctx, mtdp_ + 1); \
		KNH_STACKOP(mtdp_) = 0; \
		((Context*)ctx)->ebp = mtdp_; \
	} \

#define VM_NCALL_WM(ctx, n, mtd) { \
		Object **mtdp_ = ((Context*)ctx)->ebp - (n) ; \
		if(IS_NULL(mtdp_[1])) { \
			KNH_SETv(ctx, mtdp_[0], knh_Method_returnValue(ctx, mtd)); \
		} \
		else { \
			VM_MOV(ctx, mtdp_[0], mtd); \
			KNH_STACKOP(mtdp_) = (knh_stackop_t)pc; \
			((Method*)mtdp_[0])->func(ctx, mtdp_ + 1); \
		} \
		KNH_STACKOP(mtdp_) = 0; \
		((Context*)ctx)->ebp = mtdp_; \
	} \

#define VM_DCALL(ctx, n) { \
		Object **mtdp_ = ((Context*)ctx)->ebp - (n) ; \
		KNH_SETv(ctx, mtdp_[0], knh_Method_ufind(ctx, knh_Object_cid(mtdp_[1]), (knh_methodn_t)KNH_STACKOP(mtdp_))); \
		knh_stackf_typecheck__DCALL(ctx, mtdp_); \
		KNH_STACKOP(mtdp_) = (knh_stackop_t)pc; \
		((Method*)mtdp_[0])->func(ctx, mtdp_ + 1); \
		KNH_STACKOP(mtdp_) = 0; \
		((Context*)ctx)->ebp = mtdp_; \
	} \

#define VM_MCALL(ctx, n) { \
		Object **mtdp_ = ((Context*)ctx)->ebp - (n) ; \
		KNH_SETv(ctx, mtdp_[0], knh_Method_ufind(ctx, knh_Object_cid(mtdp_[1]), (knh_methodn_t)KNH_STACKOP(mtdp_))); \
		knh_stackf_typecheck__MCALL(ctx, mtdp_); \
		KNH_STACKOP(mtdp_) = (knh_stackop_t)pc; \
		((Method*)mtdp_[0])->func(ctx, mtdp_ + 1); \
		KNH_STACKOP(mtdp_) = 0; \
		((Context*)ctx)->ebp = mtdp_; \
	} \


#define VM_NEW(ctx, n, mtd, flag, cid) { \
		Object **mtdp_ = ((Context*)ctx)->ebp - (n) ; \
		VM_DEBUG_ASSERT(IS_Method(mtd)); \
		VM_MOV(ctx, mtdp_[0], mtd); \
		KNH_STACKOP(mtdp_) = (knh_stackop_t)pc; \
		KNH_SETv(ctx, mtdp_[1], new_Object__cid(ctx, flag, cid)); \
		((Method*)mtdp_[0])->func(ctx, mtdp_ + 1); \
		KNH_STACKOP(mtdp_) = 0; \
		((Context*)ctx)->ebp = mtdp_; \
	} \

#define VM_NEWE(ctx, n, mtd, flag, cid) { \
		Object **mtdp_ = ((Context*)ctx)->ebp - (n) ; \
		VM_DEBUG_ASSERT(IS_Method(mtd)); \
		VM_MOV(ctx, mtdp_[0], mtd); \
		KNH_STACKOP(mtdp_) = (knh_stackop_t)pc; \
		KNH_SETv(ctx, mtdp_[1], new_Object__cid(ctx, flag, cid)); \
		((Method*)mtdp_[0])->func(ctx, mtdp_ + 1); \
		KNH_STACKOP(mtdp_) = 0; \
		((Context*)ctx)->ebp = mtdp_; \
		if(IS_NULL(ebp_(0))) { \
			knh_konohavm_throwException(ctx, new_Exception__Nue(ctx, ebp_(0))); \
		} \
	} \

#define VM_NEW__DEF(ctx, isfirst, flag, cid) { \
		if(!isfirst) { \
			((Context*)ctx)->ebp++; \
		} \
		KNH_SETv(ctx, ebp_(0), new_Object__cid(ctx, flag, cid)); \
	} \

#define VM_MT(ctx, mn) { \
		Object **mtdp_ = ((Context*)ctx)->ebp; \
		KNH_SETv(ctx, ebp_(0), knh_Object_movableText(ctx, ebp_(0), mn, KNH_NULL)); \
		((Context*)ctx)->ebp = mtdp_; \
	} \

#define VM_MT__OPT(ctx, mn, opt) { \
		Object **mtdp_ = ((Context*)ctx)->ebp; \
		KNH_SETv(ctx, ebp_(0), knh_Object_movableText(ctx, ebp_(0), mn, opt)); \
		((Context*)ctx)->ebp = mtdp_; \
	} \

/* ------------------------------------------------------------------------- */

#define VM_MAP(ctx, tcid)  \
	KNH_SETv(ctx, ebp_(0), knh_MapMap_execMap(ctx, knh_tmapmap_find(ctx, knh_Object_pcid(ebp_(0)), tcid), ebp_(0))); \
	
#define VM_MAPE(ctx, tcid)  \
	KNH_SETv(ctx, ebp_(0), knh_MapMap_execMap(ctx, knh_tmapmap_find(ctx, knh_Object_pcid(ebp_(0)), tcid), ebp_(0))); \
	if(IS_NULL(ebp_(0))) { \
		knh_konohavm_throwException(ctx, new_Exception__Nue(ctx, ebp_(0))); \
	} \

#define VM_MAP_WM(ctx, map)  \
	KNH_SETv(ctx, ebp_(0), knh_MapMap_execMap(ctx, map, ebp_(0))); \
	
#define VM_MAPE_WM(ctx, map)  \
	KNH_SETv(ctx, ebp_(0), knh_MapMap_execMap(ctx, map, ebp_(0))); \
	if(IS_NULL(ebp_(0))) { \
		knh_konohavm_throwException(ctx, new_Exception__Nue(ctx, ebp_(0))); \
	} \


#define VM_NULLCHK(ctx, v) \
	if(IS_NULL(v)) { \
		knh_konohavm_throwException(ctx, new_Exception__Nue(ctx, v)); \
	} \

#define VM_TYPECHK(ctx, type, v) \
	if(!knh_Object_opInstanceof(ctx, v, type)) { \
		knh_konohavm_throwException(ctx, new_Exception__type(ctx, v, type)); \
	} \

#define VM_JMP(ctx, PC, JUMP) \
	PC; \
	goto JUMP; \
	
#define VM_SKIP(ctx, PC, JUMP) \
	if(!knh_Object_isDebug(sfp[0])) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFT(ctx, PC, JUMP, v) \
	if(IS_TRUE(v)) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFF(ctx, PC, JUMP, v) \
	if(IS_FALSE(v)) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFNUL(ctx, PC, JUMP, v) \
	if(IS_NULL(v)) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_JMP_IFNONUL(ctx, PC, JUMP, v) \
	if(IS_NOTNULL(v)) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

#define VM_ITER(ctx, cid, it) \
	KNH_SETv(ctx, it, knh_typesystem_foreach(ctx, it, cid)); \
	

#define VM_FOREACH(ctx, PC, JUMP, cid, v, it) \
	KNH_SETv(ctx, v, knh_Iterator_foreach(ctx, it, cid)); \
	if(IS_NULL(v)) { \
		VM_JMP(ctx, PC, JUMP); \
	} \

/* ------------------------------------------------------------------------ */

#define VM_TRY_BEGIN(ctx, PC, JUMP, hdr, e) \
	if(!knh_ExceptionHandler_isCatching(hdr)) { \
		if(KNH_SETJUMP(hdr) != 0) { \
			VM_MOV(ctx, e, ((ExceptionHandler*)hdr)->caught); \
			VM_JMP(ctx, PC, JUMP); \
		} \
		knh_ExceptionHandler_setCatching(hdr, 1); \
	} \

#define VM_TRY_END(ctx, hdr) \
	knh_ExceptionHandler_setCatching(hdr, 0) \

#define VM_CATCH(ctx, PC, JUMP, exptid, e) \
	if(!knh_texpt_isa(((Exception*)e)->eid, exptid)) { \
		VM_JMP(ctx, PC, JUMP); \
	} \
	knh_Exception_setCaught(e, 1); \

#define VM_THROW(ctx, e) \
	if(IS_NULL(e)) { \
		knh_konohavm_throwException(ctx, new_Exception__Nue(ctx, (Nue*)e)); \
	}else if(IS_String(e)) { \
		knh_konohavm_throwException(ctx, new_Exception(ctx, (String*)e)); \
	}else if(IS_Exception(e)) { \
		knh_konohavm_throwException(ctx, e); \
	}else { \
		knh_konohavm_throwException(ctx, new_Exception__type(ctx, e, CLASS_Exception)); \
	} \

/* ------------------------------------------------------------------------ */

#define VM_PRINT(ctx, flag, mn, v) \
	knh_vmprint(ctx, sfp, flag, mn, v)


#define VM_STACKDUMP(ctx)   knh_stackf_dump(ctx, sfp)

#define VM_NOP(ctx)

#ifdef OLD /******/

#define VM_RSHIFT(ctx,n) \
	((Context*)ctx)->ebp -= (n); \

#define VM_PRINT(ctx, mn, v) \
	knh_stackf_print(ctx, mn, v)

#define VM_PUSH_CALLED(ctx) \
	((Context*)ctx)->ebp++; \

#define VM_CALL_IDX(ctx, n) \
	VM_MOV(ctx, ebp_(-1), KNH_FIELDn(ebp_(-1), n)); \
	((Context*)ctx)->ebp--; \

#define VM_CALL_OMT0(ctx, mn) \
	KNH_SETv(ctx, ebp_(-1), knh_Object_toString(ctx, ebp_(-1), mn, KNH_NULL)); \
	((Context*)ctx)->ebp--; \

#define VM_CALL_OMT(ctx, mn, v) \
	KNH_SETv(ctx, ebp_(-1), knh_Object_toString(ctx, ebp_(-1), mn, v)); \
	((Context*)ctx)->ebp--; \

#define VM_CALL_IMT(ctx, mn, v) \
	KNH_SETv(ctx, ebp_(-1), knh_Iterator_toString(ctx, ebp_(-1), mn, v)); \
	((Context*)ctx)->ebp--; \


#define VM_FIND_MAP(ctx, cid)  \
	KNH_SETv(ctx, ebp_(-1), knh_mapdb_ufind(ctx, ebp_(-1), knh_Object_pcid(ebp_(-2)), cid)); \




#define VM_SETLINE(ctx, n) \
	knh_stackf_setline(ctx, sf, n)

#define VM_SYSLOG(ctx, type, flag, v) \
	knh_stackf_syslog(ctx, sf, type, flag, VM_FILE, VM_LINE, v)

#define VM_DIAGNOSE(ctx, n) \
	knh_stackf_diagnose(ctx, sf, n)

#endif

#ifdef __cplusplus 
}
#endif

#endif /*KONOHA_VM_H_*/
