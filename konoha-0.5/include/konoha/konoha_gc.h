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

#ifndef KONOHA_GC_H_
#define KONOHA_GC_H_

#include"konoha_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */

#ifdef KNH_USING_DRCGC
#define KNH_RCGC_INIT           ((knh_uint_t)1 << (sizeof(knh_uint_t) * 8 - 1))
#define KNH_RCGC_MASK           (~(KNH_RCGC_INIT))
#else
#define KNH_RCGC_INIT           0
#endif

#ifdef KNH_USING_RCGC

#ifdef KNH_RCGC_MASK
#define knh_Object_RCinc(o)     (o)->h.refc = (KNH_RCGC_MASK & ((o)->h.refc + 1))
#define knh_Object_RCplus(o,n)  (o)->h.refc = (KNH_RCGC_MASK & ((o)->h.refc + n))
#define knh_Object_DRCsweep(ctx, o)  knh_Object_RCdec(o)
#else
#define knh_Object_RCinc(o)     (o)->h.refc ++
#define knh_Object_RCplus(o,n)  (o)->h.refc += n
#define knh_Object_DRCsweep(ctx, o)  knh_Object_sweep(ctx, o)
#endif
#define knh_Object_RCdec(o)     (o)->h.refc--
#define knh_Object_RCset(o,c)   (o)->h.refc = (c)
#define knh_Object_isRC0(o)     ((o)->h.refc == 0)

#else/* KNH_USING_RCGC*/

#define knh_Object_RCinc(o)
#define knh_Object_RCplus(o,n)
#define knh_Object_RCdec(o)
#define knh_Object_isRC0(o)    (0)
#define knh_Object_RCset(o,c)
#define knh_Object_DRCsweep(ctx, o)

#endif/*KNH_USING_RCGC*/

#ifdef _MSC_VER

#define KNH_INITv(v,o) {\
		knh_Object_t *h_ = (knh_Object_t*)o; \
		knh_Object_t **v_ = (knh_Object_t**)&v; \
		KNH_ASSERT_ISOBJECT(h_); \
		knh_Object_RCinc(h_); \
		v_[0] = (h_); \
	}\


#define KNH_SETv(ctx,v,o) {\
		knh_Object_t *h_ = (knh_Object_t*)o; \
		knh_Object_t **v_ = (knh_Object_t**)&v; \
		KNH_ASSERT_ISOBJECT(h_); \
		knh_Object_RCinc(h_); \
		knh_Object_DRCsweep(ctx, (knh_Object_t*)v); \
		v_[0] = (h_); \
	}\

#define KNH_RCSETv(ctx,v,o) {\
		knh_Object_t *h_ = (knh_Object_t*)o; \
		knh_Object_t **v_ = (knh_Object_t**)&v; \
		KNH_ASSERT_ISOBJECT(h_); \
		knh_Object_RCinc(h_); \
		knh_Object_DRCsweep(ctx, (knh_Object_t*)v); \
		v_[0] = (h_); \
	}\

#define KNH_NGCSETv(ctx,v,o) {\
		knh_Object_t *h_ = (knh_Object_t*)o; \
		knh_Object_t **v_ = (knh_Object_t**)&v; \
		KNH_ASSERT_ISOBJECT(h_); \
		knh_Object_RCinc(h_); \
		knh_Object_RCdec(v); \
		v_[0] = (h_); \
	}\

#else

#define KNH_INITv(v,o) {\
		knh_Object_t *h_ = (knh_Object_t*)o; \
		KNH_ASSERT_ISOBJECT(h_); \
		knh_Object_RCinc(h_); \
		v = (typeof(v))(h_); \
	}\

#define KNH_SETv(ctx,v,o) {\
		knh_Object_t *h_ = (knh_Object_t*)o; \
		KNH_ASSERT_ISOBJECT(h_); \
		knh_Object_RCinc(h_); \
		knh_Object_DRCsweep(ctx, (knh_Object_t*)v); \
		v = (typeof(v))(h_); \
	}\

#define KNH_RCSETv(ctx,v,o) {\
		knh_Object_t *h_ = (knh_Object_t*)o; \
		KNH_ASSERT_ISOBJECT(h_); \
		knh_Object_RCinc(h_); \
		knh_Object_DRCsweep(ctx, (knh_Object_t*)v); \
		v = (typeof(v))(h_); \
	}\

#define KNH_NGCSETv(ctx,v,o) {\
		knh_Object_t *h_ = (knh_Object_t*)o; \
		KNH_ASSERT_ISOBJECT(h_); \
		knh_Object_RCinc(h_); \
		knh_Object_RCdec(v); \
		v = (typeof(v))(h_); \
	}\

#endif/*_MSC_VER*/

#define KNH_FINALv(ctx, v) {\
		knh_Object_DRCsweep(ctx, UP(v)); \
		v = NULL; \
	}\

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

#endif /*KONOHA_GC_H_*/
