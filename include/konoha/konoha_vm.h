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
 * (1) GNU Lesser General Public License 3.0 (with KONOHA_UNDER_LGPL3)
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

#include "konoha_t.h"

#ifndef KONOHA_VM_H_
#define KONOHA_VM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* KCODE */
/* ======================================================================== */

int knh_Method_pctoline(Method *mtd, knh_code_t *pc);
#define _HERE_    knh_Method_file(ctx, sfp[-1].mtd), knh_Method_pctoline(sfp[-1].mtd, pc)

#define KFUNC FIELDN(DP(sfp[-1].mtd)->mn)
#define KLINE knh_Method_pctoline(sfp[-1].mtd, pc)

/* ------------------------------------------------------------------------ */

#define KNH_THROW_iZERODIV(n)  \
	if(unlikely(n == 0)) { \
		KNH_THROWs(ctx, "Arithmetic!!: Zero Divided"); \
	}\

#ifndef KONOHA_OS__LKM
#define KNH_THROW_fZERODIV(n)  \
	if(unlikely(n == 0.0)) { \
		KNH_THROWs(ctx, "Arithmetic!!: Zero Divided"); \
	}\

#else
#define KNH_THROW_fZERODIV(n)  \
	if(unlikely(n == 0)) { \
		KNH_THROWs(ctx, "Arithmetic!!: Zero Divided"); \
	}\

#endif
/* ------------------------------------------------------------------------ */

#define KLR_MOV__wogc(ctx, v1, v2) {\
		Object *v2_ = (Object*)v2;\
		knh_Object_RCinc(v2_); \
		knh_Object_RCdec(v1); \
		v1 = v2_; \
	}\

#ifdef KNH_USING_DRCGC
#define KLR_MOV(ctx, v1, v2)  KLR_MOV__wogc(ctx, v1, v2)

#else/*KNH_USING_DRCGC*/

#define KLR_MOV(ctx, v1, v2) {\
		Object *v2_ = (Object*)v2;\
		knh_Object_RCinc(v2_); \
		knh_Object_RCdec(v1); \
		if(knh_Object_isRC0(v1)) { \
			knh_Object_free(ctx, v1); \
		} \
		v1 = v2_; \
	}\

#endif/*KNH_USING_DRCGC*/

#define KNH_MOV(ctx, v1, v2) KLR_MOV(ctx, v1, v2)

#define KNH_NGCMOV(ctx, v1, v2)  KLR_MOV__wogc(ctx, v1, v2)

#define KLR_SWAP(ctx, a, b) {\
		knh_sfp_t temp = sfp[(a)];\
		sfp[(a)] = sfp[(b)];\
		sfp[(b)] = temp;\
	}\

#define JIT_SWAP(ctx, a, b)  KLR_SWAP(ctx, a, b)

#define KNH_SWAP(ctx, sfp, n, n2) {\
		knh_sfp_t temp = sfp[(n)];\
		sfp[(n)] = sfp[(n2)];\
		sfp[(n2)] = temp;\
	}\

#define KNH_SETESP(ctx, sfp, n) \
	((Context*)ctx)->esp = &(sfp[n]);\
	if(unlikely((ctx)->stacksize - ((ctx)->esp - (ctx)->stack) < KNH_LOCALSIZE)) {\
		KNH_THROWs(ctx, "StackOverflow!!"); \
	}\

/* ======================================================================== */

#define KLR_HALT(ctx) KNH_THROWs(ctx, "Halt!!")
#define KLR_RET(ctx)  return

#define JIT_HALT(ctx) knh_throw__s(ctx, "Halt!!", NULL, 0)
#define JIT_RET(ctx)  KLR_RET(ctx)

/* ------------------------------------------------------------------------ */
#define SFX(x)   KNH_FIELDn(sfp[x.i].o, x.n)
#define JITSFX(a, b) KNH_FIELDn(sfp[a].o, b)

#define KLR_MOVn(ctx, a, b) {\
		sfp[a].data = sfp[b].data;\
	}\

#define KLR_MOVa(ctx, a, b) { \
		KLR_MOV(ctx, sfp[a].o, sfp[b].o);\
		sfp[a].data = sfp[b].data;\
	}\

#define KLR_MOVo(ctx, a, v) {\
		KLR_MOV(ctx, sfp[a].o, v);\
		sfp[a].data = ((Int*)v)->n.data;\
	}\

#define KLR_MOVx(ctx, a, b) {\
		Int *v_ = (Int*)SFX(b);\
		KLR_MOV(ctx, sfp[a].o, v_);\
		sfp[a].data = (v_)->n.data;\
	}\

#define KLR_MOVDEF(ctx, a, cid) {\
		Int *v_ = (Int*)KNH_DEF(ctx, cid);\
		KLR_MOV(ctx, sfp[a].o, v_);\
		sfp[a].data = (v_)->n.data;\
	}

#define KLR_MOVSYS(ctx, a, cid)  KLR_MOV(ctx, sfp[a].o, KNH_SYS(ctx, cid))


#define JITSFX(a, b) KNH_FIELDn(sfp[a].o, b)

#define JIT_MOVn(ctx, a, b) KLR_MOVn(ctx, a, b)

#define JIT_MOVa(ctx, a, b) { \
		KNH_SETv(ctx, sfp[a].o, sfp[b].o);\
		sfp[a].data = sfp[b].data;\
	}\

#define JIT_MOVo(ctx, a, v) KLR_MOVo(ctx, a, v)

#define JIT_MOVx(ctx, a, b, y) {\
		Int *v_ = (Int*)JITSFX(b, y);\
		KLR_MOV(ctx, sfp[a].o, v_);\
		sfp[a].data = (v_)->n.data;\
	}\

#define JIT_MOVDEF(ctx, a, cid) KLR_MOVDEF(ctx, a, cid)
#define JIT_MOVSYS(ctx, a, cid) KLR_MOVSYS(ctx, a, cid)

/* ------------------------------------------------------------------------ */

#define KLR_XMOVs(ctx, a, b) KLR_MOV(ctx, SFX(a), sfp[b].o)
#define KLR_XMOVo(ctx, a, b) KLR_MOV(ctx, SFX(a), b)
#define KLR_XMOVx(ctx, a, b) KLR_MOV(ctx, SFX(a), SFX(b))
#define KLR_XMOVDEF(ctx, a, cid)  KLR_MOV(ctx, SFX(a), KNH_DEF(ctx, cid))
#define KLR_XMOVSYS(ctx, a, cid)  KLR_MOV(ctx, SFX(a), KNH_SYS(ctx, cid))

#define JIT_XMOVs(ctx, a, x, b) KLR_MOV(ctx, JITSFX(a, x), sfp[b].o)
#define JIT_XMOVo(ctx, a, x, b) KLR_MOV(ctx, JITSFX(a, x), b)
#define JIT_XMOVx(ctx, a, x, b, y) KLR_MOV(ctx, JITSFX(a, x), JITSFX(b, y))
#define JIT_XMOVDEF(ctx, a, x, cid)  KLR_MOV(ctx, JITSFX(a, x), KNH_DEF(ctx, cid))
#define JIT_XMOVSYS(ctx, a, x, cid)  KLR_MOV(ctx, JITSFX(a, x), KNH_SYS(ctx, cid))

#define SFXi(x)   (*((knh_int_t*)(&KNH_FIELDn(sfp[x.i].o, x.n))))
#define KLR_MOVxi(ctx, a, b)    sfp[a].ivalue = SFXi(b)
#define KLR_XMOVsi(ctx, a, b)   SFXi(a) = sfp[b].ivalue
#define KLR_XMOVoi(ctx, a, o)   SFXi(a) = ((knh_Int_t*)o)->n.ivalue
#define KLR_XMOVxi(ctx, a, b)   SFXi(a) = SFXi(b)
#define KLR_XMOVxio(ctx, a, b)  SFXi(a) = ((knh_Int_t*)SFX(b))->n.ivalue
#define KLR_XMOVxBXi(ctx, a, b, cid) KLR_MOV(ctx, SFX(a), new_IntX(ctx, cid, SFXi(b)))

#define SFXf(x)   (*((knh_float_t*)(&KNH_FIELDn(sfp[x.i].o, x.n))))
#define KLR_MOVxf(ctx, a, b)    sfp[a].fvalue = SFXf(b)
#define KLR_XMOVsf(ctx, a, b)   SFXf(a) = sfp[b].fvalue
#define KLR_XMOVof(ctx, a, o)   SFXf(a) = ((knh_Float_t*)o)->n.fvalue
#define KLR_XMOVxf(ctx, a, b)   SFXf(a) = SFXf(b)
#define KLR_XMOVxfo(ctx, a, b)  SFXf(a) = ((knh_Float_t*)SFX(b))->n.fvalue
#define KLR_XMOVxBXf(ctx, a, b, cid) KLR_MOV(ctx, SFX(a), new_FloatX(ctx, cid, SFXf(b)))

#define SFXb(x)   (*((knh_bool_t*)(&KNH_FIELDn(sfp[x.i].o, x.n))))
#define KLR_MOVxb(ctx, a, b)    sfp[a].bvalue = SFXb(b)
#define KLR_XMOVsb(ctx, a, b)   SFXb(a) = sfp[b].bvalue
#define KLR_XMOVob(ctx, a, o)   SFXb(a) = ((knh_Int_t*)o)->n.bvalue
#define KLR_XMOVxb(ctx, a, b)   SFXb(a) = SFXb(b)

/* ------------------------------------------------------------------------ */

#define KLR_ARRAY_INDEX(ctx, n, size)   (size_t)n

#define KLR_AGET(ctx, b, a, n)  {\
		size_t idxn_ = KLR_ARRAY_INDEX(ctx, sfp[n].ivalue, ((Array*)sfp[a].o)->size);\
		if(idxn_ >= ((Array*)sfp[a].o)->size) knh_throw_OutOfIndex(ctx, idxn_, ((Array*)sfp[a].o)->size, _HERE_); \
		KLR_MOV(ctx, sfp[b].o, KNH_FIELDn(sfp[a].o, idxn_));\
	}\

#define KLR_AGETn(ctx, b, a, n)  {\
		size_t idxn_ = KLR_ARRAY_INDEX(ctx, n, ((Array*)sfp[a].o)->size);\
		if(idxn_ >= ((Array*)sfp[a].o)->size) knh_throw_OutOfIndex(ctx, idxn_, ((Array*)sfp[a].o)->size, _HERE_); \
		KLR_MOV(ctx, sfp[b].o, KNH_FIELDn(sfp[n].o, idxn_));\
	}\

#define KLR_IAGET(ctx, b, a, n)  {\
		size_t idxn_ = KLR_ARRAY_INDEX(ctx, sfp[n].ivalue, ((IArray*)sfp[a].o)->size);\
		if(idxn_ >= ((IArray*)sfp[a].o)->size) knh_throw_OutOfIndex(ctx, idxn_, ((Array*)sfp[a].o)->size, _HERE_); \
		sfp[b].ivalue = ((IArray*)sfp[a].o)->ilist[idxn_];\
	}\

#define KLR_IAGETn(ctx, b, a, n)  {\
		size_t idxn_ = KLR_ARRAY_INDEX(ctx, n, ((IArray*)sfp[a].o)->size);\
		if(idxn_ >= ((IArray*)sfp[a].o)->size) knh_throw_OutOfIndex(ctx, idxn_, ((Array*)sfp[a].o)->size, _HERE_); \
		sfp[b].ivalue = ((IArray*)sfp[a].o)->ilist[idxn_];\
	}\

#define KLR_FAGET(ctx, b, a, n)  {\
		size_t idxn_ = KLR_ARRAY_INDEX(ctx, sfp[n].ivalue, ((FArray*)sfp[a].o)->size);\
		if(idxn_ >= ((FArray*)sfp[a].o)->size) knh_throw_OutOfIndex(ctx, idxn_, ((Array*)sfp[a].o)->size, _HERE_); \
		sfp[b].fvalue = ((FArray*)sfp[a].o)->flist[idxn_];\
	}\

#define KLR_FAGETn(ctx, b, a, n)  {\
		size_t idxn_ = KLR_ARRAY_INDEX(ctx, n, ((FArray*)sfp[a].o)->size);\
		if(idxn_ >= ((FArray*)sfp[a].o)->size) knh_throw_OutOfIndex(ctx, idxn_, ((Array*)sfp[a].o)->size, _HERE_); \
		sfp[b].fvalue = ((FArray*)sfp[a].o)->flist[idxn_];\
	}\

#define KLR_ASET(ctx, b, a, n)  {\
		size_t idxn_ = KLR_ARRAY_INDEX(ctx, sfp[n].ivalue, ((Array*)sfp[a].o)->size);\
		if(idxn_ >= ((Array*)sfp[a].o)->size) knh_throw_OutOfIndex(ctx, idxn_, ((Array*)sfp[a].o)->size, _HERE_); \
		KLR_MOV(ctx, KNH_FIELDn(sfp[a].o, idxn_), sfp[b].o);\
	}\

#define KLR_ASETn(ctx, b, a, n)  {\
		size_t idxn_ = KLR_ARRAY_INDEX(ctx, n, ((Array*)sfp[a].o)->size);\
		if(idxn_ >= ((Array*)sfp[a].o)->size) knh_throw_OutOfIndex(ctx, idxn_, ((Array*)sfp[a].o)->size, _HERE_); \
		KLR_MOV(ctx, KNH_FIELDn(sfp[n].o, idxn_), sfp[b].o);\
	}\

#define KLR_IASET(ctx, b, a, n)  {\
		size_t idxn_ = KLR_ARRAY_INDEX(ctx, sfp[n].ivalue, ((IArray*)sfp[a].o)->size);\
		if(idxn_ >= ((IArray*)sfp[a].o)->size) knh_throw_OutOfIndex(ctx, idxn_, ((Array*)sfp[a].o)->size, _HERE_); \
		((IArray*)sfp[a].o)->ilist[idxn_] = sfp[b].ivalue;\
	}\

#define KLR_IASETn(ctx, b, a, n)  {\
		size_t idxn_ = KLR_ARRAY_INDEX(ctx, n, ((IArray*)sfp[a].o)->size);\
		if(idxn_ >= ((IArray*)sfp[a].o)->size) knh_throw_OutOfIndex(ctx, idxn_, ((Array*)sfp[a].o)->size, _HERE_); \
		((IArray*)sfp[a].o)->ilist[idxn_] = sfp[b].ivalue;\
	}\

#define KLR_FASET(ctx, b, a, n)  {\
		size_t idxn_ = KLR_ARRAY_INDEX(ctx, sfp[n].ivalue, ((FArray*)sfp[a].o)->size);\
		if(idxn_ >= ((FArray*)sfp[a].o)->size) knh_throw_OutOfIndex(ctx, idxn_, ((Array*)sfp[a].o)->size, _HERE_); \
		((FArray*)sfp[a].o)->flist[idxn_] = sfp[b].fvalue;\
	}\

#define KLR_FASETn(ctx, b, a, n)  {\
		size_t idxn_ = KLR_ARRAY_INDEX(ctx, n, ((FArray*)sfp[a].o)->size);\
		if(idxn_ >= ((FArray*)sfp[a].o)->size) knh_throw_OutOfIndex(ctx, idxn_, ((Array*)sfp[a].o)->size, _HERE_); \
		((FArray*)sfp[a].o)->flist[idxn_] = sfp[b].fvalue;\
	}\

/* ------------------------------------------------------------------------ */

#define KLR_INITCODE(ctx, n) { \
		knh_code_thread(ctx, pc, OPJUMP); \
		((knh_kode_t*)pc)->opcode = OPCODE_SETESP;\
		return; \
	}\

#define KLR_SETESP(ctx, n) \
	((Context*)ctx)->esp = &(sfp[n]);\
	if(unlikely((ctx)->stacksize - ((ctx)->esp - (ctx)->stack) < KNH_LOCALSIZE)) {\
		KNH_THROWs(ctx, "StackOverflow!!"); \
	}\

#define KLR_CHECKESP(ctx, n) \
	if(unlikely((ctx)->stacksize - (&sfp[n] - (ctx)->stack) < KNH_LOCALSIZE)) {\
		KNH_THROWs(ctx, "StackOverflow!!"); \
	}\

#define KLR_PINIo(ctx, a, v) {\
		if(IS_NULL(sfp[a].o)) {\
			sfp[a].data = ((Int*)v)->n.data;\
			KLR_MOV(ctx, sfp[a].o, v);\
		}\
	}\

#define KLR_RETn(ctx, dummy, b) {\
		KLR_MOVn(ctx, -1, b);\
		KLR_RET(ctx);\
	}\

#define KLR_RETa(ctx, dummy, b) {\
		sfp[-1].data = sfp[b].data;\
		KLR_MOV__wogc(ctx, sfp[-1].o, sfp[b].o);\
		KLR_RET(ctx);\
	}\

#define KLR_RETo(ctx, dummy, v) {\
		sfp[-1].data = ((Int*)v)->n.data;\
		KLR_MOV__wogc(ctx, sfp[-1].o, v);\
		KLR_RET(ctx);\
	}\

#define KLR_RETx(ctx, dummy, b) {\
		Int *v_ = (Int*)SFX(b);\
		sfp[-1].data = (v_)->n.data;\
		KLR_MOV__wogc(ctx, sfp[-1].o, v_);\
		KLR_RET(ctx);\
	}\

#define JIT_INITCODE(ctx, n) KLR_INITCODE(ctx, n)
#define JIT_SETESP(ctx, n) KLR_SETESP(ctx, n)
#define JIT_CHECKESP(ctx, n) KLR_CHECKESP(ctx, n)
#define JIT_PINIo(ctx, a, v) KLR_PINIo(ctx, a, v)
#define JIT_RETn(ctx, dummy, b) KLR_RETn(ctx, dummy, b)
#define JIT_RETa(ctx, dummy, b) KLR_RETa(ctx, dummy, b)
#define JIT_RETo(ctx, dummy, v) KLR_RETo(ctx, dummy, v)

#define JIT_RETx(ctx, dummy, b, y) {\
		Int *v_ = (Int*)JITSFX(b, y);\
		sfp[-1].data = (v_)->n.data;\
		KLR_MOV__wogc(ctx, sfp[-1].o, v_);\
		KLR_RET(ctx);\
	}\

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */

#define KLR_BOX(ctx, n, cid) {\
		KLR_MOV(ctx, sfp[n].o, new_Object_boxing(ctx, cid, &sfp[n]));\
	}\

#define KLR_BOXnc(ctx, n, cid) \
	if(IS_NOTNULL(sfp[n].o)){ \
		KLR_MOV(ctx, sfp[n].o, new_Object_boxing(ctx, cid, &sfp[n]));\
	}\

#define KLR_NNBOX(ctx, n, cid) {\
		KLR_MOV(ctx, sfp[n].o, KNH_DEF(ctx, cid));\
	}\

#define KLR_NNBOXnc(ctx, n, cid) \
	if(knh_Object_cid(sfp[n].o) != ((knh_class_t)cid)){ \
		KLR_MOV(ctx, sfp[n].o, KNH_DEF(ctx, cid));\
	}\

#define KLR_UNBOX(ctx, a) {\
		sfp[a].data = (sfp[a].i)->n.data;\
	}\

/* ------------------------------------------------------------------------ */

#define JIT_BOX(ctx, n, cid)  KLR_BOX(ctx, n, cid)
#define JIT_BOXnc(ctx, n, cid)  KLR_BOXnc(ctx, n, cid)
#define JIT_NNBOX(ctx, n, cid)  KLR_NNBOX(ctx, n, cid)
#define JIT_NNBOXnc(ctx, n, cid)  KLR_NNBOXnc(ctx, n, cid)
#define JIT_UNBOX(ctx, a) KLR_UNBOX(ctx, a)

/* ======================================================================== */

#define KLR_ISNULL(ctx, n) \
	if(unlikely(IS_NULL(sfp[n].o))) { \
		knh_throwException(ctx, new_NullException (ctx, sfp[n].o), _HERE_); \
	} \

#define KLR_ISNULLx(ctx, n) \
	if(unlikely(IS_NULL(SFX(n)))) { \
		knh_throwException(ctx, new_NullException (ctx, SFX(n)), _HERE_); \
	} \

#define KLR_ISTYPE(ctx, n, cid) \
	if(unlikely(!knh_Object_opTypeOf(ctx, sfp[n].o, cid))) { \
		knh_throwException(ctx, new_Exception__type(ctx, sfp[n].o, cid), _HERE_); \
	} \

#define KLR_ISNNTYPE(ctx, n, cid) {\
		KLR_ISTYPE(ctx, n, cid);\
		KLR_ISNULL(ctx, n);\
	}\

#define JIT_ISNULL(ctx, n)  KLR_ISNULL(ctx, n)
#define JIT_ISTYPE(ctx, n, cid)   KLR_ISTYPE(ctx, n, cid)
#define JIT_ISNNTYPE(ctx, n, cid)  KLR_ISNNTYPE(ctx, n, cid)

#define JIT_ISNULLx(ctx, a, x) \
	if(unlikely(IS_NULL(JITSFX(a, x)))) { \
		knh_throwException(ctx, new_NullException (ctx, JITSFX(a, x)), _HERE_); \
	} \

/* ======================================================================== */

#define KLR_RECSFP(ctx, sfp)
#define KLR_RECSFP2(ctx, sfp)  ctx->esp[0].sp = sfp

#define KLR_SCALL(ctx, n, shift, m) { \
		KLR_MOV(ctx, sfp[n].o, m); \
		((Context*)ctx)->esp = &(sfp[n + shift]); \
		sfp[-1].pc = pc; \
		sfp[n].pc = (sfp[n].mtd)->pc_start; \
		(sfp[n].mtd)->fcall_1(ctx, sfp + (n + 1)); \
		((Context*)ctx)->esp = &(sfp[n]); \
	} \

#define KNH_SCALL(ctx, lsfp, n, m, args) { \
		KLR_MOV(ctx, lsfp[n].o, m); \
		((Context*)ctx)->esp = &(lsfp[n+args+2]); \
		lsfp[n].pc = (lsfp[n].mtd)->pc_start; \
		(lsfp[n].mtd)->fcall_1(ctx, lsfp + (n + 1)); \
		((Context*)ctx)->esp = &(lsfp[n]); \
	} \

#define KLR_FCALL(ctx, n, shift, self, m) { \
		int n1_ = n + 1;\
		KLR_MOVa(ctx, n1_, self); \
		KLR_MOV(ctx, sfp[n].o, m); \
		((Context*)ctx)->esp = &(sfp[n + shift]); \
		sfp[-1].pc = pc; \
		sfp[n].pc = (sfp[n].mtd)->pc_start; \
		(sfp[n].mtd)->fcall_1(ctx, sfp + n1_); \
		((Context*)ctx)->esp = &(sfp[n]); \
	} \

#define KLR_CALL(ctx, n, shift, mn) { \
		KLR_MOV(ctx, sfp[n].o, konoha_lookupMethod(ctx, knh_Object_cid(sfp[n+1].o), mn)); \
		DBG2_ASSERT(IS_Method(sfp[n].o)); \
		((Context*)ctx)->esp = &(sfp[n + shift]); \
		sfp[n].pc = (sfp[n].mtd)->pc_start; \
		sfp[-1].pc = pc; \
		(sfp[n].mtd)->fcall_1(ctx, sfp + n + 1); \
		((Context*)ctx)->esp = &(sfp[n]); \
	} \

#define KLR_ACALL(ctx, n, shift, mn) { \
		Method *mtd_ = konoha_lookupMethod(ctx, knh_Object_cid(sfp[n+1].o), mn);\
		KLR_MOV(ctx, sfp[n].o, mtd_); \
		((Context*)ctx)->esp = &(sfp[n + shift]); \
		knh_sfp_typecheck(ctx, sfp + n + 1, mtd_, pc); \
		sfp[-1].pc = pc; \
		sfp[n].pc = (sfp[n].mtd)->pc_start; \
		(mtd_)->fcall_1(ctx, sfp + n + 1); \
		((Context*)ctx)->esp = &(sfp[n]); \
	} \

/* this is used only for Closure.invoke */

#define KLR_AINVOKE(ctx, n, shift, m) { \
		KLR_MOV(ctx, sfp[n].o, m); \
		((Context*)ctx)->esp = &(sfp[n + shift]); \
		DBG2_ASSERT(IS_Closure(sfp[n+1].o));\
		knh_sfp_typecheck(ctx, sfp + n + 1, DP(sfp[n+1].cc)->mtd, pc); \
		sfp[-1].pc = pc; \
		sfp[n].pc = (sfp[n].mtd)->pc_start; \
		(sfp[n].mtd)->fcall_1(ctx, sfp + n + 1); \
		((Context*)ctx)->esp = &(sfp[n]); \
	} \

#define KLR_NEW(ctx, n, flag, cid, shift, m) { \
		KLR_MOV(ctx, sfp[n].o, m); \
		KLR_MOV(ctx, sfp[n+1].o, new_Object_init(ctx, flag, cid, 0)); \
		((Context*)ctx)->esp = &(sfp[n + shift]); \
		sfp[-1].pc = pc; \
		sfp[n].pc = (sfp[n].mtd)->pc_start; \
		(sfp[n].mtd)->fcall_1(ctx, sfp + n + 1); \
		((Context*)ctx)->esp = &(sfp[n]); \
	} \


#define JIT_SCALL(ctx, n, shift, m) { \
		KLR_MOV(ctx, sfp[n].o, m); \
		((Context*)ctx)->esp = &(sfp[n + shift]); \
		sfp[n].pc = (sfp[n].mtd)->pc_start; \
		(sfp[n].mtd)->fcall_1(ctx, sfp + n + 1); \
		((Context*)ctx)->esp = &(sfp[n]); \
	} \

#define JIT_FCALL(ctx, n, shift, self, m) { \
		int n1_ = n + 1;\
		KLR_MOVa(ctx, n1_, self); \
		KLR_MOV(ctx, sfp[n].o, m); \
		((Context*)ctx)->esp = &(sfp[n + shift]); \
		sfp[n].pc = (sfp[n].mtd)->pc_start; \
		(sfp[n].mtd)->fcall_1(ctx, sfp + n1_); \
		((Context*)ctx)->esp = &(sfp[n]); \
	} \

#define JIT_CALL(ctx, n, shift, mn) { \
		KLR_MOV(ctx, sfp[n].o, konoha_lookupMethod(ctx, knh_Object_cid(sfp[n+1].o), mn)); \
		DBG2_ASSERT(IS_Method(sfp[n].o)); \
		((Context*)ctx)->esp = &(sfp[n + shift]); \
		sfp[n].pc = (sfp[n].mtd)->pc_start; \
		(sfp[n].mtd)->fcall_1(ctx, sfp + n + 1); \
		((Context*)ctx)->esp = &(sfp[n]); \
	} \

#define JIT_ACALL(ctx, n, shift, mn) { \
		Method *mtd_ = konoha_lookupMethod(ctx, knh_Object_cid(sfp[n+1].o), mn);\
		KLR_MOV(ctx, sfp[n].o, mtd_); \
		((Context*)ctx)->esp = &(sfp[n + shift]); \
		knh_sfp_typecheck(ctx, sfp + n + 1, mtd_, NULL); \
		sfp[n].pc = (sfp[n].mtd)->pc_start; \
		(mtd_)->fcall_1(ctx, sfp + n + 1); \
		((Context*)ctx)->esp = &(sfp[n]); \
	} \

/* this is used only for Closure.invoke */

#define JIT_AINVOKE(ctx, n, shift, m) { \
		KLR_MOV(ctx, sfp[n].o, m); \
		((Context*)ctx)->esp = &(sfp[n + shift]); \
		DBG2_ASSERT(IS_Closure(sfp[n+1].o));\
		knh_sfp_typecheck(ctx, sfp + n + 1, DP(sfp[n+1].cc)->mtd, NULL); \
		sfp[n].pc = (sfp[n].mtd)->pc_start; \
		(sfp[n].mtd)->fcall_1(ctx, sfp + n + 1); \
		((Context*)ctx)->esp = &(sfp[n]); \
	} \

#define JIT_NEW(ctx, n, flag, cid, shift, m) { \
		KLR_MOV(ctx, sfp[n].o, m); \
		KLR_MOV(ctx, sfp[n+1].o, new_Object_init(ctx, flag, cid, 0)); \
		((Context*)ctx)->esp = &(sfp[n + shift]); \
		sfp[n].pc = (sfp[n].mtd)->pc_start; \
		(sfp[n].mtd)->fcall_1(ctx, sfp + n + 1); \
		((Context*)ctx)->esp = &(sfp[n]); \
	} \

/* ------------------------------------------------------------------------- */

#define KLR_TOSTRf(ctx, n, mn, fmt) { \
		KNH_ASSERT(ctx->esp <= (sfp + n));\
		KLR_SWAP(ctx, n, n+1); \
		knh_cwb_t cwb = new_cwb(ctx);\
		KLR_MOV(ctx, sfp[n+2].o, cwb.w);\
		KLR_MOV(ctx, sfp[n+3].o, fmt);\
		Method *mtd_ = konoha_lookupFormatter(ctx, knh_Object_cid(sfp[n+1].o), mn);\
		KLR_SCALL(ctx, n, 4, mtd_);\
		KNH_SETv(ctx, sfp[n].o, new_String__cwb(ctx, cwb)); \
	}\

#define KLR_TOSTR(ctx, n, mn)  KLR_TOSTRf(ctx, n, mn, KNH_NULL)

#define JIT_TOSTRf(ctx, n, mn, fmt) { \
		KLR_SWAP(ctx, n, n+1); \
		knh_cwb_t cwb = new_cwb(ctx);\
		KLR_MOV(ctx, sfp[n+2].o, cwb.w);\
		KLR_MOV(ctx, sfp[n+3].o, fmt);\
		Method *mtd_ = konoha_lookupFormatter(ctx, knh_Object_cid(sfp[n+1].o), mn);\
		JIT_SCALL(ctx, n, 4, mtd_);\
		KLR_MOV(ctx, sfp[n].o, new_String__cwb(ctx, cwb)); \
	}\

#define JIT_TOSTR(ctx, n, mn)       JIT_TOSTRf(ctx, n, mn, KNH_NULL)
/* ------------------------------------------------------------------------- */

#define KLR_SMAP(ctx, n, m)  { \
		KLR_MOV(ctx, sfp[n+1].o, m);\
		(sfp[n+1].mpr)->fmap_1(ctx, sfp + n); \
	} \

#define KLR_SMAPnc(ctx, n, m)  { \
		if(likely(IS_NOTNULL(sfp[n].o))) {\
			KLR_MOV(ctx, sfp[n+1].o, m);\
			(sfp[n+1].mpr)->fmap_1(ctx, sfp + n); \
		}\
	} \

#define KLR_MAP(ctx, n, tcid)  { \
		KLR_MOV(ctx, sfp[n+1].o, konoha_findMapper(ctx, knh_Object_cid(sfp[n].o), tcid)); \
		(sfp[n+1].mpr)->fmap_1(ctx, sfp + n); \
	} \

#define KLR_MAPnc(ctx, n, tcid)  { \
		if(likely(IS_NOTNULL(sfp[n].o))) {\
			KLR_MOV(ctx, sfp[n+1].o, konoha_findMapper(ctx, knh_Object_cid(sfp[n].o), tcid)); \
			(sfp[n+1].mpr)->fmap_1(ctx, sfp + n); \
		}\
	}\

#define KLR_AMAP(ctx, n, tcid)  { \
		knh_class_t scid = knh_Object_cid(sfp[n].o);\
		if(scid != ((knh_class_t)tcid) && !knh_class_instanceof(ctx, scid, tcid) && IS_NOTNULL(sfp[n].o)) { \
			KLR_MOV(ctx, sfp[n+1].o, konoha_findMapper(ctx, scid, tcid)); \
			(sfp[n+1].mpr)->fmap_1(ctx, sfp + n); \
		} \
	} \

#define KLR_NNMAP(ctx, a, tcid)  { \
		if(unlikely(IS_NULL(sfp[a].o))) {\
			Int *v_ = (Int*)KNH_DEF(ctx, tcid);\
			KLR_MOV(ctx, sfp[a].o, v_);\
			sfp[a].data = (v_)->n.data;\
		} \
	}\

#define JIT_SMAP(ctx, n, m) KLR_SMAP(ctx, n, m)
#define JIT_SMAPnc(ctx, n, m) KLR_SMAPnc(ctx, n, m)
#define JIT_MAP(ctx, n, tcid) KLR_MAP(ctx, n, tcid)
#define JIT_MAPnc(ctx, n, tcid) KLR_MAPnc(ctx, n, tcid)
#define JIT_AMAP(ctx, n, tcid) KLR_AMAP(ctx, n, tcid)
#define JIT_NNMAP(ctx, a, tcid) KLR_NNMAP(ctx, a, tcid)

/* ======================================================================== */

#define KLR_JMP(ctx, PC, JUMP) {\
		PC; \
		goto JUMP; \
	}\

#define KLR_SKIP(ctx, PC, JUMP) \
	if(!knh_Context_isDebug(ctx)) { \
		KLR_JMP(ctx, PC, JUMP); \
	} \

#define KLR_bJIFT(ctx, PC, JUMP, n) \
	if(sfp[n].bvalue) { \
		KLR_JMP(ctx, PC, JUMP); \
	} \

#define KLR_bJIFF(ctx, PC, JUMP, n) \
	if(!sfp[n].bvalue) { \
		KLR_JMP(ctx, PC, JUMP); \
	} \

#define KLR_bJIFF_LOOP(ctx, PC, JUMP, n) \
	if(unlikely(!sfp[n].bvalue)) { \
		KLR_JMP(ctx, PC, JUMP); \
	} \

#define KLR_JIFNUL(ctx, PC, JUMP, n) \
	if(IS_NULL(sfp[n].o)) { \
		KLR_JMP(ctx, PC, JUMP); \
	} \

#define KLR_JIFNN(ctx, PC, JUMP, n) \
	if(IS_NOTNULL(sfp[n].o)) { \
		KLR_JMP(ctx, PC, JUMP); \
	} \

#define JIT_JMP(ctx, PC, JUMP) KLR_JMP(ctx, PC, JUMP)
#define JIT_SKIP(ctx, PC, JUMP) KLR_SKIP(ctx, PC, JUMP)
#define JIT_bJIFT(ctx, PC, JUMP, n) KLR_bJIFT(ctx, PC, JUMP, n)
#define JIT_bJIFF(ctx, PC, JUMP, n) KLR_bJIFF(ctx, PC, JUMP, n)
#define JIT_bJIFF_LOOP(ctx, PC, JUMP, n) KLR_bJIFF_LOOP(ctx, PC, JUMP, n)
#define JIT_JIFNUL(ctx, PC, JUMP, n) KLR_JIFNUL(ctx, PC, JUMP, n)
#define JIT_JIFNN(ctx, PC, JUMP, n) KLR_JIFNN(ctx, PC, JUMP, n)

/* ------------------------------------------------------------------------- */

#define KLR_NEXT(ctx, PC, JUMP, na, ib, sc) { \
		knh_sfp_t *itrsfp_ = sfp + ib; \
		DBG2_ASSERT(IS_bIterator(itrsfp_[0].it));\
		(itrsfp_[0].it)->fnext_1(ctx, itrsfp_, sc - ib); \
		if(!HAS_ITRNEXT(sfp[sc].o)) { \
			KLR_JMP(ctx, PC, JUMP); \
		} \
		KLR_MOV(ctx, sfp[na].o, sfp[sc].o); sfp[na].data = sfp[sc].data;\
	} \

#define KLR_INEXT(ctx, PC, JUMP, reqc, na, ib, sc) { \
		knh_sfp_t *itrsfp_ = sfp + ib; \
		KNH_ASSERT(IS_bIterator(itrsfp_[0].it));\
		knh_class_t ncid_;\
		do {\
			(itrsfp_[0].it)->fnext_1(ctx, itrsfp_, sc - ib); \
			if(!HAS_ITRNEXT(sfp[sc].o)) { \
				KLR_JMP(ctx, PC, JUMP); \
			} \
			ncid_ = knh_Object_cid(sfp[sc].o);\
		}while(ncid_ != reqc && !knh_class_instanceof(ctx, reqc, ncid_));\
		KLR_MOV(ctx, sfp[na].o, sfp[sc].o); sfp[na].data = sfp[sc].data;\
	} \

#define KLR_MAPNEXT(ctx, PC, JUMP, reqc, na, ib, sc) { \
		knh_sfp_t *itrsfp_ = sfp + ib; \
		KNH_ASSERT(IS_bIterator(itrsfp_[0].it));\
		knh_class_t ncid_;\
		do {\
			(itrsfp_[0].it)->fnext_1(ctx, itrsfp_, sc - ib); \
			if(!HAS_ITRNEXT(sfp[sc].o)) { \
				KLR_JMP(ctx, PC, JUMP); \
			} \
			ncid_ = knh_Object_cid(sfp[sc].o);\
			if(ncid_ == reqc || knh_class_instanceof(ctx, reqc, ncid_)) break;\
			KLR_MOV(ctx, sfp[sc+1].o, konoha_findMapper(ctx, ncid_, reqc));\
			(sfp[sc+1].mpr)->fmap_1(ctx, sfp + sc); \
		}while(IS_NOTNULL(sfp[sc].o));\
		KLR_MOV(ctx, sfp[na].o, sfp[sc].o); sfp[na].data = sfp[sc].data;\
	} \

#define KLR_SMAPNEXT(ctx, PC, JUMP, na, ib, sc, mm) { \
		knh_sfp_t *itrsfp_ = sfp + ib; \
		KLR_MOV(ctx, sfp[sc+1].o, mm); \
		do {\
			(itrsfp_[0].it)->fnext_1(ctx, itrsfp_, sc - ib); \
			if(!HAS_ITRNEXT(sfp[sc].o)) { \
				KLR_JMP(ctx, PC, JUMP); \
			} \
			(sfp[sc+1].mpr)->fmap_1(ctx, sfp + sc); \
		}while(IS_NOTNULL(sfp[sc].o));\
		KLR_MOV(ctx, sfp[na].o, sfp[sc].o); sfp[na].data = sfp[sc].data;\
	} \

#define JIT_NEXT(ctx, PC, JUMP, na, ib, sc) { \
		knh_sfp_t *itrsfp_ = sfp + ib; \
		(itrsfp_[0].it)->fnext_1(ctx, itrsfp_, sc - ib); \
		if(!HAS_ITRNEXT(sfp[sc].o)) { \
			KLR_JMP(ctx, PC, JUMP); \
		} \
		KLR_MOV(ctx, sfp[na].o, sfp[sc].o); sfp[na].data = sfp[sc].data;\
	} \

#define JIT_INEXT(ctx, PC, JUMP, reqc, na, ib, sc) { \
		knh_sfp_t *itrsfp_ = sfp + ib; \
		knh_class_t ncid_;\
		do {\
			(itrsfp_[0].it)->fnext_1(ctx, itrsfp_, sc - ib); \
			if(!HAS_ITRNEXT(sfp[sc].o)) { \
				KLR_JMP(ctx, PC, JUMP); \
			} \
			ncid_ = knh_Object_cid(sfp[sc].o);\
		}while(ncid_ != ((knh_class_t)reqc) && !knh_class_instanceof(ctx, reqc, ncid_));\
		KLR_MOV(ctx, sfp[na].o, sfp[sc].o); sfp[na].data = sfp[sc].data;\
	} \

#define JIT_MAPNEXT(ctx, PC, JUMP, reqc, na, ib, sc) { \
		knh_sfp_t *itrsfp_ = sfp + ib; \
		knh_class_t ncid_;\
		do {\
			(itrsfp_[0].it)->fnext_1(ctx, itrsfp_, sc - ib); \
			if(!HAS_ITRNEXT(sfp[sc].o)) { \
				KLR_JMP(ctx, PC, JUMP); \
			} \
			ncid_ = knh_Object_cid(sfp[sc].o);\
			if(ncid_ == ((knh_class_t)reqc) || knh_class_instanceof(ctx, reqc, ncid_)) break;\
			KLR_MOV(ctx, sfp[sc+1].o, konoha_findMapper(ctx, ncid_, reqc));\
			(sfp[sc+1].mpr)->fmap_1(ctx, sfp + sc); \
		}while(IS_NOTNULL(sfp[sc].o));\
		KLR_MOV(ctx, sfp[na].o, sfp[sc].o); sfp[na].data = sfp[sc].data;\
	} \

#define JIT_SMAPNEXT(ctx, PC, JUMP, na, ib, sc, mm) { \
		knh_sfp_t *itrsfp_ = sfp + ib; \
		KLR_MOV(ctx, sfp[sc+1].o, mm); \
		do {\
			(itrsfp_[0].it)->fnext_1(ctx, itrsfp_, sc - ib); \
			if(!HAS_ITRNEXT(sfp[sc].o)) { \
				KLR_JMP(ctx, PC, JUMP); \
			} \
			(sfp[sc+1].mpr)->fmap_1(ctx, sfp + sc); \
		}while(IS_NOTNULL(sfp[sc].o));\
		KLR_MOV(ctx, sfp[na].o, sfp[sc].o); sfp[na].data = sfp[sc].data;\
	} \

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------- */

#define NPC  /* for KNH_TRY */

#define KNH_SETJUMP(hdlr) setjmp(DP(hdlr)->jmpbuf)

#define KNH_TRY(ctx, JUMP, lsfp, hn)  {\
		ExceptionHandler* _hdr = lsfp[hn].hdr; \
		if(!knh_ExceptionHandler_isJumpable(_hdr)) { \
			knh_ExceptionHandler_setJumpable(_hdr, 1); \
			int jump = KNH_SETJUMP(_hdr); \
			if(jump != 0) { \
				((Context*)ctx)->esp = &(lsfp[hn]); \
				KLR_JMP(ctx, NPC, JUMP); \
			} \
			DP(_hdr)->esp = ctx->esp; \
		} \
		knh_ExceptionHandler_setCatching(_hdr, 1); \
	} \

#define KLR_TRY(ctx, PC, JUMP, hn)  {\
		ExceptionHandler* _hdr = sfp[hn].hdr; \
		if(!IS_ExceptionHandler(_hdr)) { \
			_hdr = new_ExceptionHandler(ctx); \
			KLR_MOV(ctx, sfp[hn].o, _hdr); \
		} \
		if(!knh_ExceptionHandler_isJumpable(_hdr)) { \
			knh_ExceptionHandler_setJumpable(_hdr, 1); \
			int jump = KNH_SETJUMP(_hdr); \
			if(jump != 0) { \
				((Context*)ctx)->esp = DP(_hdr)->esp; \
				pc = DP(_hdr)->pc; \
				KLR_JMP(ctx, PC, JUMP); \
			} \
			DP(_hdr)->esp = ctx->esp; \
			DP(_hdr)->pc  = pc; \
		} \
		knh_ExceptionHandler_setCatching(_hdr, 1); \
	} \

#define JIT_TRY(ctx, PC, JUMP, hn)  {\
		ExceptionHandler* _hdr = sfp[hn].hdr; \
		if(!IS_ExceptionHandler(_hdr)) { \
			_hdr = new_ExceptionHandler(ctx); \
			KLR_MOV(ctx, sfp[hn].o, _hdr); \
		} \
		if(!knh_ExceptionHandler_isJumpable(_hdr)) { \
			knh_ExceptionHandler_setJumpable(_hdr, 1); \
			int jump = KNH_SETJUMP(_hdr); \
			if(jump != 0) { \
				((Context*)ctx)->esp = DP(_hdr)->esp; \
				KLR_JMP(ctx, PC, JUMP); \
			} \
			DP(_hdr)->esp = ctx->esp; \
		} \
		knh_ExceptionHandler_setCatching(_hdr, 1); \
	} \

#define KLR_TRYEND(ctx, hn)  {\
		KNH_ASSERT(IS_ExceptionHandler(sfp[hn].o)); \
		knh_ExceptionHandler_setCatching(sfp[hn].hdr, 0); \
	} \

#define JIT_TRYEND(ctx, hn)  {\
		knh_ExceptionHandler_setCatching(sfp[hn].hdr, 0); \
	} \

#define KLR_CATCH(ctx, PC, JUMP, hn, en, emsg) { \
		Exception* _e = DP(sfp[hn].hdr)->caught; \
		if(!knh_Exception_isa(ctx, _e, (String*)emsg)) { \
			KLR_JMP(ctx, PC, JUMP); \
		} \
		else { \
			KLR_MOV(ctx, sfp[en].o, _e); \
		} \
	} \

#define JIT_CATCH(ctx, PC, JUMP, hn, en, emsg) { \
		Exception* _e = DP(sfp[hn].hdr)->caught; \
		if(!knh_Exception_isa(ctx, _e, (String*)emsg)) { \
			KLR_JMP(ctx, PC, JUMP); \
		} \
		else { \
			KLR_MOV(ctx, sfp[en].o, _e); \
		} \
	} \

#define KLR_THROW_AGAIN(ctx, hn) { \
		KNH_ASSERT(IS_ExceptionHandler(sfp[hn].o)); \
		Exception *_e = DP(sfp[hn].hdr)->caught; \
		if(IS_Exception(_e)) {\
			DBG2_P("THROW AGAIN .. %s", knh_String_tochar(DP(_e)->message)); \
			knh_throwException(ctx, _e, NULL, 0); \
		} \
	} \

#define JIT_THROW_AGAIN(ctx, hn) { \
		KNH_ASSERT(IS_ExceptionHandler(sfp[hn].o)); \
		Exception *_e = DP(sfp[hn].hdr)->caught; \
		if(IS_Exception(_e)) {\
			knh_throwException(ctx, _e, NULL, 0); \
		} \
	} \

#define KLR_THROW(ctx, n) \
	if(IS_bString((sfp[n].o))) { \
		knh_throwException(ctx, new_Exception(ctx, sfp[n].s), _HERE_); \
	}else { \
		KNH_ASSERT(IS_Exception(sfp[n].e)); \
		knh_throwException(ctx, sfp[n].e, _HERE_); \
	}\

#define JIT_THROW(ctx, n) \
	if(IS_bString((sfp[n].o))) { \
		knh_throwException(ctx, new_Exception(ctx, sfp[n].s), NULL, 0); \
	}else { \
		KNH_ASSERT(IS_Exception(sfp[n].e)); \
		knh_throwException(ctx, sfp[n].e, NULL, 0); \
	}\

#define KLR_THROWs(ctx, v) \
	if(IS_bString((Object*)v)) { \
		knh_throwException(ctx, new_Exception(ctx, (String*)v), _HERE_); \
	}else { \
		KNH_ASSERT(IS_Exception((Object*)v)); \
		knh_throwException(ctx, (Exception*)v, _HERE_); \
	}\

#define JIT_THROWs(ctx, v) \
	if(IS_bString((Object*)v)) { \
		knh_throwException(ctx, new_Exception(ctx, (String*)v), NULL, 0); \
	}else { \
		KNH_ASSERT(IS_Exception((Object*)v)); \
		knh_throwException(ctx, (Exception*)v, NULL, 0); \
	}\

/* ------------------------------------------------------------------------ */

#define KNH_THROW_BUGSTOP(ctx) \
	knh_throw_bugstop(ctx, __FILE__, __LINE__, __FUNCTION__)

/* ------------------------------------------------------------------------ */

#define KLR_P(ctx, flag, mn, n) knh_stack_p(ctx, sfp, flag, mn, n)
#define KLR_PMSG(ctx, flag, v) knh_stack_pmsg(ctx, sfp, flag, (String*)v)

#define JIT_P(ctx, flag, mn, n) KLR_P(ctx, flag, mn, n)
#define JIT_PMSG(ctx, flag, v)  KLR_PMSG(ctx, flag, v)

/* ------------------------------------------------------------------------ */

#define KLR_iCAST(ctx, a) {\
		knh_int_t n_ = (knh_int_t)sfp[a].fvalue; \
		sfp[a].ivalue = n_; \
	}\

#define KLR_inCAST(ctx, a) {\
		if(IS_NULL(sfp[a].o)) { \
			sfp[a].ivalue = 0; \
		}else{\
			knh_int_t n_ = (knh_int_t)sfp[a].fvalue; \
			sfp[a].ivalue = n_; \
		}\
	}\

#define KLR_fCAST(ctx, a) {\
		knh_float_t n_ = (knh_float_t)sfp[a].ivalue; \
		sfp[a].fvalue = n_; \
	}\

#define KLR_fnCAST(ctx, a) {\
		if(IS_NULL(sfp[a].o)) { \
			sfp[a].fvalue = 0; \
		}else{\
			knh_float_t n_ = (knh_float_t)sfp[a].ivalue; \
			sfp[a].fvalue = n_; \
		}\
	}\

#define JIT_iCAST(ctx, a) KLR_iCAST(ctx, a)
#define JIT_inCAST(ctx, a) KLR_inCAST(ctx, a)
#define JIT_fCAST(ctx, a) KLR_fCAST(ctx, a)
#define JIT_fnCAST(ctx, a) KLR_fnCAST(ctx, a)

/* ------------------------------------------------------------------------ */

#define SFb(x)   sfp[x].bvalue
#define SFi(x)   sfp[x].ivalue
#define SFf(x)   sfp[x].fvalue

#define KLR_bNOT(ctx, c, a)     SFb(c) = !(SFb(a))

#define KLR_iNEG(ctx, c, a)     SFi(c) = -(SFi(a))
#define KLR_iADD(ctx, c, a, b)  SFi(c) = (SFi(a) + SFi(b))
#define KLR_iADDn(ctx, c, a, n) SFi(c) = (SFi(a) + n)
#define KLR_iSUB(ctx, c, a, b)  SFi(c) = (SFi(a) - SFi(b))
#define KLR_iSUBn(ctx, c, a, n) SFi(c) = (SFi(a) - n)
#define KLR_iMUL(ctx, c, a, b)  SFi(c) = (SFi(a) * SFi(b))
#define KLR_iMULn(ctx, c, a, n) SFi(c) = (SFi(a) * n)
#define KLR_iDIV(ctx, c, a, b)  { \
		KNH_THROW_iZERODIV(SFi(b)); \
		SFi(c) = (SFi(a) / SFi(b)); \
	} \

#define KLR_iDIVn(ctx, c, a, n)  SFi(c) = (SFi(a) / n)
#define KLR_iMOD(ctx, c, a, b)  { \
		KNH_THROW_iZERODIV(SFi(b)); \
		SFi(c) = (SFi(a) % SFi(b)); \
	} \

#define KLR_iMODn(ctx, c, a, n)  SFi(c) = (SFi(a) % n)

#define KLR_iEQ(ctx, c, a, b)  SFi(c) = (SFi(a) == SFi(b))
#define KLR_iEQn(ctx, c, a, n)  SFi(c) = (SFi(a) == n)
#define KLR_iNEQ(ctx, c, a, b)  SFi(c) = (SFi(a) != SFi(b))
#define KLR_iNEQn(ctx, c, a, n)  SFi(c) = (SFi(a) != n)

#define KLR_iLT(ctx, c, a, b)  SFb(c) = (SFi(a) < SFi(b))
#define KLR_iLTn(ctx, c, a, n)  SFb(c) = (SFi(a) < n)
#define KLR_iLTE(ctx, c, a, b)  SFb(c) = (SFi(a) <= SFi(b))
#define KLR_iLTEn(ctx, c, a, n)  SFb(c) = (SFi(a) <= n)
#define KLR_iGT(ctx, c, a, b)  SFb(c) = (SFi(a) > SFi(b))
#define KLR_iGTn(ctx, c, a, n)  SFb(c) = (SFi(a) > n)
#define KLR_iGTE(ctx, c, a, b)  SFb(c) = (SFi(a) >= SFi(b))
#define KLR_iGTEn(ctx, c, a, n)  SFb(c) = (SFi(a) >= n)

/* ------------------------------------------------------------------------ */

#define KLR_fNEG(ctx, c, a)     SFf(c) = -(SFf(a))
#define KLR_fADD(ctx, c, a, b)  SFf(c) = (SFf(a) + SFf(b))
#define KLR_fADDn(ctx, c, a, n) SFf(c) = (SFf(a) + n)
#define KLR_fSUB(ctx, c, a, b)  SFf(c) = (SFf(a) - SFf(b))
#define KLR_fSUBn(ctx, c, a, n) SFf(c) = (SFf(a) - n)
#define KLR_fMUL(ctx, c, a, b)  SFf(c) = (SFf(a) * SFf(b))
#define KLR_fMULn(ctx, c, a, n) SFf(c) = (SFf(a) * n)
#define KLR_fDIV(ctx, c, a, b)  { \
		KNH_THROW_fZERODIV(SFf(b)); \
		SFf(c) = (SFf(a) / SFf(b)); \
	} \

#define KLR_fDIVn(ctx, c, a, n)  SFf(c) = (SFf(a) / n)

#define KLR_fEQ(ctx, c, a, b)  SFb(c) = (SFf(a) == SFf(b))
#define KLR_fEQn(ctx, c, a, n)  SFb(c) = (SFf(a) == n)
#define KLR_fNEQ(ctx, c, a, b)  SFb(c) = (SFf(a) != SFf(b))
#define KLR_fNEQn(ctx, c, a, n)  SFb(c) = (SFf(a) != n)
#define KLR_fLT(ctx, c, a, b)  SFb(c) = (SFf(a) < SFf(b))
#define KLR_fLTn(ctx, c, a, n)  SFb(c) = (SFf(a) < n)
#define KLR_fLTE(ctx, c, a, b)  SFb(c) = (SFf(a) <= SFf(b))
#define KLR_fLTEn(ctx, c, a, n)  SFb(c) = (SFf(a) <= n)
#define KLR_fGT(ctx, c, a, b)  SFb(c) = (SFf(a) > SFf(b))
#define KLR_fGTn(ctx, c, a, n)  SFb(c) = (SFf(a) > n)
#define KLR_fGTE(ctx, c, a, b)  SFb(c) = (SFf(a) >= SFf(b))
#define KLR_fGTEn(ctx, c, a, n)  SFb(c) = (SFf(a) >= n)

/* ------------------------------------------------------------------------ */

#define JIT_bNOT(ctx, c, a)     SFb(c) = !(SFb(a))

#define JIT_iNEG(ctx, c, a)     SFi(c) = -(SFi(a))
#define JIT_iADD(ctx, c, a, b)  SFi(c) = (SFi(a) + SFi(b))
#define JIT_iADDn(ctx, c, a, n) SFi(c) = (SFi(a) + n)
#define JIT_iSUB(ctx, c, a, b)  SFi(c) = (SFi(a) - SFi(b))
#define JIT_iSUBn(ctx, c, a, n) SFi(c) = (SFi(a) - n)
#define JIT_iMUL(ctx, c, a, b)  SFi(c) = (SFi(a) * SFi(b))
#define JIT_iMULn(ctx, c, a, n) SFi(c) = (SFi(a) * n)
#define JIT_iDIV(ctx, c, a, b)  { \
		KNH_THROW_iZERODIV(SFi(b)); \
		SFi(c) = (SFi(a) / SFi(b)); \
	} \

#define JIT_iDIVn(ctx, c, a, n)  SFi(c) = (SFi(a) / n)
#define JIT_iMOD(ctx, c, a, b) { \
		KNH_THROW_iZERO(SFi(b)); \
		SFi(c) = (SFi(a) % SFi(b)); \
	} \

#define JIT_iMODn(ctx, c, a, n)  SFi(c) = (SFi(a) % n)


#define JIT_iEQ(ctx, c, a, b)  SFi(c) = (SFi(a) == SFi(b))
#define JIT_iEQn(ctx, c, a, n)  SFi(c) = (SFi(a) == n)
#define JIT_iNEQ(ctx, c, a, b)  SFi(c) = (SFi(a) != SFi(b))
#define JIT_iNEQn(ctx, c, a, n)  SFi(c) = (SFi(a) != n)

#define JIT_iLT(ctx, c, a, b)  SFb(c) = (SFi(a) < SFi(b))
#define JIT_iLTn(ctx, c, a, n)  SFb(c) = (SFi(a) < n)
#define JIT_iLTE(ctx, c, a, b)  SFb(c) = (SFi(a) <= SFi(b))
#define JIT_iLTEn(ctx, c, a, n)  SFb(c) = (SFi(a) <= n)
#define JIT_iGT(ctx, c, a, b)  SFb(c) = (SFi(a) > SFi(b))
#define JIT_iGTn(ctx, c, a, n)  SFb(c) = (SFi(a) > n)
#define JIT_iGTE(ctx, c, a, b)  SFb(c) = (SFi(a) >= SFi(b))
#define JIT_iGTEn(ctx, c, a, n)  SFb(c) = (SFi(a) >= n)

#define JIT_fNEG(ctx, c, a)     SFf(c) = -(SFf(a))
#define JIT_fADD(ctx, c, a, b)  SFf(c) = (SFf(a) + SFf(b))
#define JIT_fADDn(ctx, c, a, n) SFf(c) = (SFf(a) + n)
#define JIT_fSUB(ctx, c, a, b)  SFf(c) = (SFf(a) - SFf(b))
#define JIT_fSUBn(ctx, c, a, n) SFf(c) = (SFf(a) - n)
#define JIT_fMUL(ctx, c, a, b)  SFf(c) = (SFf(a) * SFf(b))
#define JIT_fMULn(ctx, c, a, n) SFf(c) = (SFf(a) * n)
#define JIT_fDIV(ctx, c, a, b)  { \
		KNH_THROW_fZERODIV(SFf(b)); \
		SFf(c) = (SFf(a) / SFf(b)); \
	} \

#define JIT_fDIVn(ctx, c, a, n)  SFf(c) = (SFf(a) / n)

#define JIT_fEQ(ctx, c, a, b)  SFb(c) = (SFf(a) == SFf(b))
#define JIT_fEQn(ctx, c, a, n)  SFb(c) = (SFf(a) == n)
#define JIT_fNEQ(ctx, c, a, b)  SFb(c) = (SFf(a) != SFf(b))
#define JIT_fNEQn(ctx, c, a, n)  SFb(c) = (SFf(a) != n)
#define JIT_fLT(ctx, c, a, b)  SFb(c) = (SFf(a) < SFf(b))
#define JIT_fLTn(ctx, c, a, n)  SFb(c) = (SFf(a) < n)
#define JIT_fLTE(ctx, c, a, b)  SFb(c) = (SFf(a) <= SFf(b))
#define JIT_fLTEn(ctx, c, a, n)  SFb(c) = (SFf(a) <= n)
#define JIT_fGT(ctx, c, a, b)  SFb(c) = (SFf(a) > SFf(b))
#define JIT_fGTn(ctx, c, a, n)  SFb(c) = (SFf(a) > n)
#define JIT_fGTE(ctx, c, a, b)  SFb(c) = (SFf(a) >= SFf(b))
#define JIT_fGTEn(ctx, c, a, n)  SFb(c) = (SFf(a) >= n)

/* ------------------------------------------------------------------------ */

#define KLR_NOP(ctx)
#define JIT_NOP(ctx)

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */

#define KNH_LOCAL(ctx)  ((Context*)ctx)->esp
#define KNH_SHIFTESP(ctx, newesp)  ((Context*)ctx)->esp = (newesp)
#define KNH_LOCALBACK(ctx, lsfp)  ((Context*)ctx)->esp = lsfp

#define KNH_LPUSH(ctx, v)  {\
		KLR_MOV(ctx, ((Context*)ctx)->esp[0].o, v); \
		((Context*)ctx)->esp += 1;\
	}

#define KNH_SMAP(ctx, lsfp, n, m)  { \
		KLR_MOV(ctx, lsfp[n+1].o, m);\
		KNH_ASSERT(IS_Mapper(m)); \
		(lsfp[n+1].mpr)->fmap_1(ctx, lsfp + n); \
	} \


#define KNH_PRINT_STACKTRACE(ctx, lsfp, hn) {\
		KNH_ASSERT(IS_ExceptionHandler(lsfp[hn].hdr));\
		knh_format(ctx, KNH_STDERR, METHODN__dump, UP(DP(lsfp[hn].hdr)->caught), KNH_NULL);\
		KNH_LOCALBACK(ctx, lsfp);\
	}\

/* ------------------------------------------------------------------------ */


#define KNH_SECURE(ctx) \
	if(((ctx)->flag & KNH_FLAG_CTXF_TRUSTED) != KNH_FLAG_CTXF_TRUSTED) { \
		knh_throwException(ctx, new_Exception(ctx, TS_SecurityException), KNH_SAFEFILE(__FILE__), __LINE__); \
	} \

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif

#endif /*KONOHA_VM_H_*/
