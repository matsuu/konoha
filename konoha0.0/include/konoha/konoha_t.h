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

#if defined(KNH_USING_PTHREAD)
	#include<pthread.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */

#ifndef INLINE
#define INLINE             /*__inline__*/
#endif

#define synchronized

#define PUBLIC
#define PRIVATE            static

#define METHOD             void  KNH_CC_FASTCALL

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Bool(ean), knh_bool_t */
/* ------------------------------------------------------------------------ */

typedef int                      knh_bool_t;
#define knh_boolean_t            knh_bool_t

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
#define knh_abs(n)                labs(n)

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

typedef struct {
	knh_uchar_t   *mbuf;
	size_t         mlen;
} knh_mbytes_t;

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

typedef knh_ushort_t          knh_nsid_t;
typedef knh_ushort_t          knh_fileid_t;

typedef knh_ushort_t          knh_fieldn_t;
typedef knh_ushort_t          knh_methodn_t;

/* ------------------------------------------------------------------------ */
/* Object */
/* ------------------------------------------------------------------------ */

#define KNH_OBJECT_MAGIC      578

typedef struct knh_hObject_t {
	knh_ushort_t magic;
	knh_flag_t  flag;
	knh_class_t bcid;
	knh_class_t cid;
#ifdef KONOHA_WITH_RCGC
	knh_uint_t   refc;
#endif
} knh_hObject_t ;


typedef struct knh_Object_t {
	knh_hObject_t h;
	void *ref;
	void *ref2;
	void *ref3;
} knh_Object_t ;

#ifdef KNH_OBJECT_MAGIC
	#ifdef KONOHA_FASTMODE
		#define KNH_ASSERT_ISOBJECT(o)
	#else
		#define KNH_ASSERT_ISOBJECT(o)        KNH_ASSERT((o)->h.magic == KNH_OBJECT_MAGIC)
	#endif
#else/*KONOHA_OBJECT_MAGIC*/
	#define KNH_ASSERT_ISOBJECT(o)
#endif/*KONOHA_OBJECT_MAGIC*/

/* types of basic objects (not type-checked) */

#define Object          knh_Object_t
#define ObjectNULL      Object
#define Any             knh_Object_t
#define This            knh_Object_t
#define Any1            knh_Object_t
#define Any2            knh_Object_t
#define UP(o)           (Object*)(o)

//typedef void            Struct;

//#define KNH_FIELDn(v,n)         ((Object**)(v))[n]
#define KNH_FIELDn(v,n)            ((Script*)(v))->fields[(n)]

/* ------------------------------------------------------------------------ */
/* Context */
/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */

typedef struct knh_sfp_t {
	union {
		Object *o;
		struct knh_Int_t    *i;
		struct knh_Float_t  *f;
		struct knh_Class_t  *c;
		struct knh_String_t *s;
		struct knh_Method_t *mtd;
		struct knh_ExceptionHandler_t *hdr;
	} ;
	knh_uint_t op;
} knh_sfp_t;

typedef struct knh_Context_t {
	knh_hObject_t h;
	knh_Object_t        *unusedObject;
	size_t               unusedObjectSize;

	struct knh_Runtime_t        *runtime;
	knh_flag_t                   flag;
	knh_nsid_t                   nsid;
	knh_sfp_t*                   stack;
	knh_sfp_t*                   ebp;
	size_t                       stacksize;
	struct knh_String_t*         enc;
	struct knh_InputStream_t*    in;
	struct knh_OutputStream_t*   out;
	struct knh_OutputStream_t*   err;
	struct knh_Bytes_t*          bufa;
	struct knh_OutputStream_t*   bufw;
	struct knh_Bytes_t*          bconvbuf;
	struct knh_DictMap_t*        props;
	struct knh_HashMap_t        *tmapperHashMap;
	struct knh_HashMap_t        *tmethodHashMap;
	struct knh_NameSpace_t      *ns;
	struct knh_Compiler_t       *cmpr;
} knh_Context_t ;

typedef const knh_Context_t    Ctx;

/* ------------------------------------------------------------------------ */
/* Struct, Class */
/* ------------------------------------------------------------------------ */

#ifndef KNH_TSTRUCT_SIZE
#define KNH_TSTRUCT_SIZE 256
#endif

typedef void (*f_traverse)(Ctx *ctx, Object *);

typedef void        (*f_tStruct_init)(Ctx *, void *, int, Object *);
typedef void        (*f_tStruct_copy)(Ctx *, void *, void *);
typedef int         (*f_tStruct_compare)(void *, void *);
typedef void        (*f_tStruct_traverse)(Ctx *, void *, f_traverse);

typedef knh_uint_t                knh_hcode_t;  /* knh_hcode_t */
typedef union {
	knh_hcode_t hcode;
	struct {
		knh_ushort_t u1;
		knh_ushort_t u2;
	} value2;
	float fvalue;
} knh_hcode_u;

#define knh_hcode_join(s1,s2)	   ((knh_hcode_t)s1 << (sizeof(knh_short_t)*8)) + s2;

typedef knh_hcode_t (*f_hashCode)(Object *);
typedef int         (*f_compareTo)(Object*, Object*);

typedef struct {
	size_t                 size;
	char                  *name;
	f_tStruct_init         finit;
	f_tStruct_traverse     ftraverse;
//	f_tStruct_compare      fcompare;
	f_tStruct_copy         fcopy;
	f_hashCode             fhashCode;
	f_compareTo            fcompareTo;
} knh_tStruct_t ;


/* ------------------------------------------------------------------------ */

typedef int (*f_compare)(knh_Object_t *, knh_Object_t *);
typedef knh_Object_t* (*f_default)(Ctx *ctx, knh_class_t cid);

typedef struct {
	knh_flag_t    cflag;   knh_flag_t    oflag;
	knh_class_t   bcid;    knh_class_t   supcid;
	knh_class_t   p1;      knh_type_t    p2;
	knh_ushort_t  offset;  knh_struct_t  sid;
	knh_ushort_t  size;    knh_ushort_t  bsize;
	knh_short_t   keyidx;  knh_short_t   keyidx2;
	struct knh_String_t       *sname;
	struct knh_String_t       *lname;
	struct knh_Class_t        *class_cid;
	struct knh_ClassStruct_t  *cstruct;
	struct knh_ClassMap_t     *cmap;
	struct knh_Object_t       *cspec;
	f_default                  fdefault;
} knh_tClass_t;

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */

typedef knh_uint_t                knh_vargc_t;
typedef knh_uint_t                knh_stackop_t;

/* ------------------------------------------------------------------------ */
/* KLRCode */
/* ------------------------------------------------------------------------ */

typedef unsigned char           knhvmc_t;          /* knh_vmc_t */
#ifdef KNH_FASTMODE
typedef unsigned int            knhvm_opcode_t;
typedef signed int              knhvm_i1_t;
typedef unsigned int            knhvm_u1_t;
typedef signed int              knhvm_i2_t;
typedef unsigned int            knhvm_u2_t;
typedef signed int              knhvm_ebp_t;
typedef signed int              knhvm_sfp_t;
typedef signed int              knhvm_ofp_t;
typedef signed int              knhvm_addr_t;
typedef unsigned int            knhvm_class_t;
typedef unsigned int            knhvm_methodn_t;
typedef unsigned int            knhvm_expt_t;
typedef unsigned int            knhvm_line_t;
#else
typedef unsigned char           knhvm_opcode_t;
typedef char                    knhvm_i1_t;
typedef unsigned char           knhvm_u1_t;
typedef knh_short_t             knhvm_i2_t;
typedef knh_ushort_t            knhvm_u2_t;
typedef knhvm_u1_t              knhvm_ebp_t;
typedef knhvm_u1_t              knhvm_sfp_t;
typedef knhvm_u1_t              knhvm_ofp_t;
typedef knh_short_t             knhvm_addr_t;
typedef knh_class_t             knhvm_class_t;
typedef knh_methodn_t           knhvm_methodn_t;
typedef knh_expt_t              knhvm_expt_t;
typedef knh_int_t               knhvm_line_t;
#endif

/* ------------------------------------------------------------------------ */

typedef struct {
	size_t pos;
	struct knh_Bytes_t          *ba;
	struct knh_OutputStream_t   *w;
} knh_wbuf_t;

/* ------------------------------------------------------------------------ */
/* Functions */
/* ------------------------------------------------------------------------ */

#ifdef _MSC_VER
typedef void   (KNH_CC_FASTCALL *f_method)(Ctx *, knh_sfp_t *);
#else
typedef METHOD (*f_method)(Ctx *, knh_sfp_t *);
#endif

typedef void       MapData;
struct knh_Mapper_t;
typedef Object*    (*f_mapper)(Ctx *, Object *, struct knh_Mapper_t *);

typedef knh_ushort_t             knh_line_t;

//typedef knh_ushort_t             flpos_t;
//
//typedef struct {
//	char    *fname;
//	knh_line_t  fline;
//	flpos_t  flpos;
//} knh_filelog_t;

/* ------------------------------------------------------------------------ */
/* driver */
/* ------------------------------------------------------------------------ */

#define KNHINIT

typedef struct {
	int   type;
	char *name;
} knh_drvapi_t ;

#define KNH_DRVAPI_TYPE__UNKNOWN 0
#define KNH_DRVAPI_TYPE__BCONV   1
#define KNH_DRVAPI_TYPE__INPUTSTREAM      2
#define KNH_DRVAPI_TYPE__OUTPUTSTREAM     3
#define KNH_DRVAPI_TYPE__PARSER           4
#define KNH_DRVAPI_TYPE__REGEX            5
#define KNH_DRVAPI_TYPE__DB               6

#define IS_DRVAPI(c)   (0 < c && c < 7)

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
