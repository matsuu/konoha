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

#ifndef KONOHA_GLUE_H_
#define KONOHA_GLUE_H_

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */

#define p_size(a)      ((size_t)(a).ivalue)
#define p_int(a)         ((knh_int_t)(a).ivalue)
#define p_uint(a)        ((knh_uint_t)(a).ivalue)
#define p_integer(a)     ((a).ivalue)
#define p_uinteger(a)    ((knh_uint_t)(a).ivalue)

#define p_float(a)       ((a).fvalue)
#ifdef KONOHA_OS__LKM
#define p_double(a)      ((a).fvalue)
#else
#define p_double(a)      ((double)(a).fvalue)
#endif
#define p_bool(a)        ((a).bvalue)
#define p_char(a)        (knh_String_tochar(a.s))
#define p_bytes(a)       (knh_Bytes_tobytes(a.s))
#define p_cid(a)         ((a.c)->cid)
#define ARG_Object_cid(a)  knh_Object_cid(a.o)
#define p_cptr(a)        ((a.glue)->ptr)

/* ------------------------------------------------------------------------ */

#define sfp_bool(n_)           (sfp[n_].bvalue)
#define sfp_int(n_)            sfp[n_].ivalue
#define sfp_intOR(n_, d_)      (IS_bInt(sfp[n_].o) ? (sfp[n_].ivalue) : (d_))
#define sfp_float(n_)          (sfp[n_].fvalue)
#define sfp_floatOR(n_, d_)    (IS_bFloat(sfp[n_].o) ? (sfp[n_].fvalue) : (d_))
#define sfp_double(n_)         (sfp[n_].fvalue)
#define sfp_doubleOR(n_, d_)   (IS_bFloat(sfp[n_].o) ? (sfp[n_].fvalue) : (d_))

#define sfp_charptr(n_)            knh_Object_charptr(ctx, sfp[n_].s)
#define sfp_charptrOR(n_, d_)      (IS_NULL(sfp[n_].o) ? (d_) : knh_Object_charptr(ctx, sfp[n_].s))

#define sfp_glueptr(n_)            ((sfp[n_].glue)->ptr)
#define sfp_glueptrOR(n_, d_)      (IS_NULL(sfp[n_].o) ? (d_) : ((sfp[n_].glue)->ptr))

/* ------------------------------------------------------------------------ */


#define KNH_RETURN(ctx, sfp, v) {\
		Int *n_ = (Int*)v;\
		KNH_NGCMOV(ctx, sfp[-1].o, n_);\
		sfp[-1].data = (n_)->n.data;\
		return; \
	}\

#define KNH_RETURN_void(ctx, sfp)      {\
		KNH_NGCMOV(ctx, sfp[-1].o, KNH_VOID); \
		return; \
	}\

#define KNH_RETURN_Boolean(ctx, sfp, c) {\
		sfp[-1].bvalue = c; \
		return; \
	}\

#define KNH_RETURN_Int(ctx, sfp, n)      {\
		sfp[-1].ivalue = (knh_int_t)n;\
		return; \
	}\

#define KNH_RETURN_NNInt(ctx, sfp, n)      {\
		KNH_NGCMOV(ctx, sfp[-1].o, KNH_INT0);\
		sfp[-1].ivalue = (knh_int_t)n;\
		return; \
	}\

#define KNH_RETURN_Float(ctx, sfp, n)      {\
		sfp[-1].fvalue = (knh_float_t)n;\
		return; \
	}\

#define KNH_RETURN_NNFloat(ctx, sfp, n)      {\
		KNH_NGCMOV(ctx, sfp[-1].o, KNH_FLOAT0);\
		sfp[-1].fvalue = (knh_float_t)n;\
		return; \
	}\

/* --------------------------------------------------------------------------- */
/* [Iterator] */

#define KNH_ITRNEXT(ctx, sfp, i, v) {\
		KNH_MOV(ctx, sfp[i].o, v);\
		sfp[i].data = ((Int*)v)->n.data;\
		return 1; \
	}\

#define KNH_ITRNEXT_Int(ctx, sfp, i, n) {\
		KNH_MOV(ctx, sfp[i].o, KNH_INT0);\
		sfp[i].ivalue = n;\
		return 1; \
	}\

#define KNH_ITRNEXT_Float(ctx, sfp, i, n) {\
		KNH_MOV(ctx, sfp[i].o, KNH_FLOAT0);\
		sfp[i].fvalue = n;\
		return 1; \
	}\

#define KNH_ITREND(ctx, sfp, n) {\
		knh_Iterator_close(ctx, sfp[0].it);\
		KNH_MOV(ctx, sfp[n].o, KNH_VOID);\
		return 0; \
	}\

#define HAS_ITRNEXT(v)   IS_NOTNULL(v)

#define KNH_MAPPED(ctx, sfp, v) {\
		Int *vn_ = (Int*)(v);\
		KNH_MOV(ctx, sfp[0].o, vn_);\
		sfp[0].data = (vn_)->n.data;\
		return; \
	}\

#define KNH_MAPPED_Boolean(ctx, sfp, value) {\
		KNH_MOV(ctx, sfp[0].o, KNH_FALSE);\
		sfp[0].bvalue = value;\
		return; \
	}\

#define KNH_MAPPED_Int(ctx, sfp, value) {\
		KNH_MOV(ctx, sfp[0].o, KNH_INT0); \
		sfp[0].ivalue = value;\
		return; \
	}\

#define KNH_MAPPED_Float(ctx, sfp, value) {\
		KNH_MOV(ctx, sfp[0].o, KNH_FLOAT0);\
		sfp[0].fvalue = value;\
		return;\
	}\


/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

#endif /*KONOHA_GLUE_H_*/
