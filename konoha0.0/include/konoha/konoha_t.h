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

#ifndef KONOHA_T_H_
#define KONOHA_T_H_


#include<stdio.h>
#include<limits.h>
#include<float.h>
#include<setjmp.h>

#include"konoha_config.h"
#include"konoha_alias_.h"

#if defined(KONOHA_MULTITHREAD) && defined(KONOHA_LIBPTHREAD)
	#include<pthread.h>
#endif

#ifdef __cplusplus 
extern "C" {
#endif

/* ------------------------------------------------------------------------ */

#ifndef INLINE
#define INLINE             /*__inline__*/
#endif

#define PUBLIC             
#define PRIVATE            static

#define METHOD             void 
#define CLASS              void

/* ------------------------------------------------------------------------ */

#define DEFAULT_SIZE       0
#define CTX_NULL        NULL

/* ------------------------------------------------------------------------ */
/* Bool(ean), knh_bool_t */  
/* ------------------------------------------------------------------------ */

typedef int                      knh_bool_t;

/* ------------------------------------------------------------------------ */
/* Int, knh_int_t */  
/* ------------------------------------------------------------------------ */

typedef signed long int           knh_int_t;    /* sizeof(knh_int_t) = sizeof(*p) */
#define KNH_INT_MAX               LONG_MAX
#define KNH_INT_MIN               LONG_MIN
#define KNH_INT_FMT               "%ld"
#define KNH_INT_FMTX              "%lx"
#define KNH_INT_BSIZE             (sizeof(knh_int_t))
#define KNH_INT_FMTSIZ            40

typedef unsigned long int         knh_uint_t;   /* sizeof(knh_uint_t) = sizeof(*p) */
#define KNH_UINT_MAX              ULONG_MAX
#define KNH_UINT_MIN              0
#define KNH_UINT_FMT              "%lu"

typedef knh_int_t                 knh_index_t;
typedef size_t                    knh_size_t;
typedef size_t                    bsize_t;
typedef knh_int_t                 int_byte_t;

#define KONOHA_SYSTEM_BIT        (sizeof(knh_int_t) * CHAR_BIT))

/* ------------------------------------------------------------------------ */
/* knh_flag_t */  
/* ------------------------------------------------------------------------ */

typedef short                     knh_short_t;
typedef unsigned short            knh_ushort_t;

/* ------------------------------------------------------------------------ */
/* knh_flag_t */  
/* ------------------------------------------------------------------------ */

typedef knh_ushort_t              knh_flag_t;    /* flag field */

#define KNH_FLAG_T0     ((knh_flag_t)(1 << 15))
#define KNH_FLAG_T1     ((knh_flag_t)(1 << 14))
#define KNH_FLAG_T2     ((knh_flag_t)(1 << 13))
#define KNH_FLAG_T3     ((knh_flag_t)(1 << 12))
#define KNH_FLAG_T4     ((knh_flag_t)(1 << 11))
#define KNH_FLAG_T5     ((knh_flag_t)(1 << 10))
#define KNH_FLAG_T6     ((knh_flag_t)(1 << 9))
#define KNH_FLAG_T7     ((knh_flag_t)(1 << 8))
#define KNH_FLAG_T8     ((knh_flag_t)(1 << 7))
#define KNH_FLAG_T9     ((knh_flag_t)(1 << 6))
#define KNH_FLAG_T10    ((knh_flag_t)(1 << 5))
#define KNH_FLAG_T11    ((knh_flag_t)(1 << 4))
#define KNH_FLAG_T12    ((knh_flag_t)(1 << 3))
#define KNH_FLAG_T13    ((knh_flag_t)(1 << 2))
#define KNH_FLAG_T14    ((knh_flag_t)(1 << 1))
#define KNH_FLAG_T15    ((knh_flag_t)(1 << 0))

#define KNH_FLAG15    ((knh_flag_t)(1 << 15))
#define KNH_FLAG14    ((knh_flag_t)(1 << 14))
#define KNH_FLAG13    ((knh_flag_t)(1 << 13))
#define KNH_FLAG12    ((knh_flag_t)(1 << 12))
#define KNH_FLAG11    ((knh_flag_t)(1 << 11))
#define KNH_FLAG10    ((knh_flag_t)(1 << 10))
#define KNH_FLAG09     ((knh_flag_t)(1 << 9))
#define KNH_FLAG08     ((knh_flag_t)(1 << 8))
#define KNH_FLAG07     ((knh_flag_t)(1 << 7))
#define KNH_FLAG06     ((knh_flag_t)(1 << 6))
#define KNH_FLAG05     ((knh_flag_t)(1 << 5))
#define KNH_FLAG04     ((knh_flag_t)(1 << 4))
#define KNH_FLAG03     ((knh_flag_t)(1 << 3))
#define KNH_FLAG02     ((knh_flag_t)(1 << 2))
#define KNH_FLAG01     ((knh_flag_t)(1 << 1))
#define KNH_FLAG00     ((knh_flag_t)(1 << 0))

#define KNH_FLAG9      ((knh_flag_t)(1 << 9))
#define KNH_FLAG8      ((knh_flag_t)(1 << 8))
#define KNH_FLAG7      ((knh_flag_t)(1 << 7))
#define KNH_FLAG6      ((knh_flag_t)(1 << 6))
#define KNH_FLAG5      ((knh_flag_t)(1 << 5))
#define KNH_FLAG4      ((knh_flag_t)(1 << 4))
#define KNH_FLAG3      ((knh_flag_t)(1 << 3))
#define KNH_FLAG2      ((knh_flag_t)(1 << 2))
#define KNH_FLAG1      ((knh_flag_t)(1 << 1))
#define KNH_FLAG0      ((knh_flag_t)(1 << 0))

#define KNH_FLAG_SET(f,op)     (f) = ((f)|(op))
#define KNH_FLAG_UNSET(f,op)   (f) = ((f)&(~(op)))
#define KNH_FLAG_IS(f,op)      (((f) & (op)) == (op))

/* ------------------------------------------------------------------------ */
/* Float, knh_float_t */  
/* ------------------------------------------------------------------------ */

#ifdef KNH_FLOAT_TYPE__LONG_DOUBLE
	typedef long double               knh_float_t;
	#define KNH_FLOAT_MAX             LDBL_MAX
	#define KNH_FLOAT_MIN             (-(LDBL_MAX))
	#define KNH_FLOAT_STEP            LDBL_MIN
	#define KNH_FLOAT_FMT             "%Lf"
	#define KNH_FLOAT_FMT1            "%.1Lf"
	#define KNH_FLOAT_FMT2            "%.2Lf"
	#define KNH_FLOAT_FMT3            "%.3Lf"
	#define KNH_FLOAT_FMT4            "%.4Lf"
	#define KNH_FLOAT_FMTE            "%Le"
#else
	#ifdef KNH_FLOAT_TYPE__FLOAT
		typedef float                     knh_float_t;
		#define KNH_FLOAT_MAX             FLT_MAX
		#define KNH_FLOAT_MIN             (-(FLT_MAX))
		#define KNH_FLOAT_STEP            FLT_MIN
		#define KNH_FLOAT_FMT             "%f"
		#define KNH_FLOAT_FMT1            "%.1f"
		#define KNH_FLOAT_FMT2            "%.2f"
		#define KNH_FLOAT_FMT3            "%.3f"
		#define KNH_FLOAT_FMT4            "%.4f"
		#define KNH_FLOAT_FMTE            "%e"
	#else
		typedef double                    knh_float_t;
		#define KNH_FLOAT_MAX             DBL_MAX
		#define KNH_FLOAT_MIN             (-(DBL_MAX))
		#define KNH_FLOAT_STEP            DBL_MIN
		#define KNH_FLOAT_FMT             "%lf"
		#define KNH_FLOAT_FMT1            "%.1lf"
		#define KNH_FLOAT_FMT2            "%.2lf"
		#define KNH_FLOAT_FMT3            "%.3lf"
		#define KNH_FLOAT_FMT4            "%.4lf"
		#define KNH_FLOAT_FMTE            "%le"
	#endif
#endif

#define knh_double_t                    knh_float_t /* just in case */
#define KNH_FLOAT_FMTSIZ                256

/* ------------------------------------------------------------------------ */
/* Long, knh_int64_t */  
/* ------------------------------------------------------------------------ */

typedef signed long long int           knh_int64_t;
typedef unsigned long long int         knh_uint64_t;
#define KNH_LONG_MAX   LLONG_MAX
#define KNH_LONG_MIN   LLONG_MIN
#define KNH_ULONG_MAX  ULLONG_MAX
#define KNH_ULONG_MIN  ((knh_uint64_t)0)

/* ------------------------------------------------------------------------ */
/* String, knh_uchar_t */  
/* ------------------------------------------------------------------------ */

typedef unsigned char           knh_uchar_t;    /* byte */

typedef struct {
	knh_uchar_t   *buf;
	size_t     len;
} knh_bytes_t;

#define ismulti(c)             (((knh_uchar_t)c)>127)

/* ------------------------------------------------------------------------ */
/* Struct, Class, Type  */  
/* ------------------------------------------------------------------------ */

typedef unsigned short       knh_struct_t ; /* struct id*/
typedef unsigned short       knh_class_t;   /* class id */
typedef unsigned short       knh_type_t;    /* extended knh_type_t */
typedef unsigned short       knh_expt_t;    /* knh_expt_t */

#define KNH_CLASSSPEC_FMT    "%s{%s}"

/* ------------------------------------------------------------------------ */

typedef knh_ushort_t          knh_fieldn_t;
typedef knh_ushort_t          knh_methodn_t;

/* ------------------------------------------------------------------------ */
/* Object */
/* ------------------------------------------------------------------------ */

/* types of basic objects (not type-checked) */

#define Object          void
#define ObjectNULL      Object
#define knh_Object      Object
typedef void            Any;
typedef void            Struct;

#define STRUCT_Object           ((knh_struct_t)0)
#define IS_STRUCT_Object(o)     (knh_Object_topsid(o) == STRUCT_Object)
#define CLASS_Object            ((knh_class_t)0)
#define KNH_CFLAG_Object        ((knh_flag_t)0)
#define KNH_FLAG_Object         KNH_FLAG_CF2OF(CF_Object)
#define CLASS_Object__          TYPE_PLURAL(CLASS_Object)
#define IS_Object(o)            (knh_Object_cid(o) == CLASS_Tuple)

#define KNH_FIELDn(v,n)         ((Object**)(v))[n]

/* ------------------------------------------------------------------------ */
/* Abstract Class */

typedef Object         Number;

/* ------------------------------------------------------------------------ */

typedef knh_uint_t                knh_hcode_t;  /* knh_hcode_t */
#define knh_hcode_join(s1,s2)	   ((knh_hcode_t)s1 << (sizeof(knh_short_t)*8)) + s2;
typedef knh_uint_t                knh_vargc_t;
typedef knh_uint_t                knh_stackop_t;

/* ------------------------------------------------------------------------ */
/* VirtualMachineCode */
/* ------------------------------------------------------------------------ */

typedef unsigned char            knh_vmc_t;     /* knh_vmc_t */
typedef knh_vmc_t                knh_asmc_t;
typedef knh_vmc_t                knh_vmc_i1_t;
typedef knh_vmc_t                knh_vmc_u1_t;
typedef knh_short_t              knh_vmc_i2_t;
typedef knh_ushort_t             knh_vmc_u2_t;
typedef knh_short_t              knh_vmc_addr_t;

typedef knh_int_t                vmc_line_t;

//typedef knh_short_t              vmc_lb2_t;

/* ------------------------------------------------------------------------ */
/* konoha, Context */
/* ------------------------------------------------------------------------ */

typedef const void            Ctx;
typedef void                  Writer;

typedef struct {
	size_t pos;
	struct knh_Bytes          *ba;
	struct knh_OutputStream   *w;
} knh_buffer_t;

/* ------------------------------------------------------------------------ */
/* Functions */
/* ------------------------------------------------------------------------ */

typedef void        (*f_gc)(Ctx *ctx, Object *);

typedef void        (*f_struct_init)(Ctx *, Struct *, int, Object *);
typedef void        (*f_struct_copy)(Ctx *, Struct *, Struct *);
typedef knh_int_t   (*f_struct_compare)(Ctx *, Struct *, Struct *);
typedef void        (*f_struct_traverse)(Ctx *, Struct *, f_gc);

typedef void        (*f_method)(Ctx *, Object **);

typedef void       MapData;
struct knh_MapMap;
typedef Object*    (*f_mapmap)(Ctx *, Object *, struct knh_MapMap *);

/* ------------------------------------------------------------------------ */
/* ns, file */
/* ------------------------------------------------------------------------ */

typedef knh_ushort_t             knh_nsn_t;
typedef knh_ushort_t             knh_filen_t;
typedef knh_ushort_t             knh_line_t;

//typedef knh_ushort_t             flpos_t;
//
//typedef struct {
//	char    *fname;
//	knh_line_t  fline;
//	flpos_t  flpos;
//} knh_filelog_t;

/* ------------------------------------------------------------------------ */
/* mutex */
/* ------------------------------------------------------------------------ */

#ifndef KONOHA_MULTITHREAD
	typedef knh_uint_t            knh_mutex_t;
#else
	#if (KONOHA_MULTITHREAD == KONOHA_LIBPTHREAD)
		typedef pthread_mutex_t    knh_mutex_t;
	#else
		#undef KONOHA_MULTITHREAD
		typedef knh_uint_t         knh_mutex_t;
	#endif
#endif

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus 
}
#endif

#endif /*KONOHA_T_H_*/
