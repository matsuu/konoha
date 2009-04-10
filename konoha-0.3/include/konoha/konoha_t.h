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

#define __STDC_LIMIT_MACROS
#include<stdint.h>
#define __STDC_FORMAT_MACROS
#include<inttypes.h>

#include"konoha_config.h"

#if defined(KNH_USING_PTHREAD)
	#include<pthread.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */

#define METHOD             void  KNH_CC_FASTCALL
#define MAPPER             METHOD
#define ITRNEXT            METHOD

#ifdef KNH_USING_THREAD
#define KNH_MT_VOLATILE           volatile
#else
#define KNH_MT_VOLATILE
#endif

#define KONOHA_SYSTEM_BIT        (sizeof(void*) * CHAR_BIT))

/* ------------------------------------------------------------------------ */
/* Bool(ean), knh_bool_t */
/* ------------------------------------------------------------------------ */

typedef int                      knh_bool_t;
typedef int                      knh_boolean_t;

/* ------------------------------------------------------------------------ */
/* Int, knh_int_t */
/* ------------------------------------------------------------------------ */

typedef int16_t           knh_int16_t;
typedef uint16_t          knh_uint16_t;
typedef int16_t           knh_short_t;
typedef uint16_t          knh_ushort_t;
typedef int32_t           knh_int32_t;
typedef uint32_t          knh_uint32_t;
typedef int64_t           knh_int64_t;
typedef uint64_t          knh_uint64_t;

typedef intptr_t                  knh_intptr_t;
typedef uintptr_t                 knh_uintptr_t;
typedef knh_intptr_t              knh_index_t;

#define KNH_INTPTR_FMT               "%"PRIdPTR

//OLD
//#define KNH_INTPTR_FMTX              "%"PRIxPTR
//#define KNH_INT_BSIZE             (sizeof(knh_int_t))
//#define KNH_UINT_FMT              "%lu"
//typedef size_t                    knh_size_t;
//typedef size_t                    bsize_t;
//typedef knh_intptr_t                 int_byte_t;
//#define KNH_INTPTR_MAX               LONG_MAX
//#define KNH_INTPTR_MIN               LONG_MIN
//#define KNH_UINTPTR_MAX              ULONG_MAX
//#define KNH_UINTPTR_MIN              0

/* ------------------------------------------------------------------------ */
/* Integer, knh_int_t */
/* ------------------------------------------------------------------------ */

#ifdef KNH_USING_INT32

typedef int32_t        knh_int_t;
typedef uint32_t       knh_uint_t;

#define KNH_INT_MAX               LONG_MAX
#define KNH_INT_MIN               (LONG_MIN + 1)
#define KNH_INT_NULL              (LONG_MIN)
#define KNH_INT_FMT               "%ld"
#define KNH_INT_XFMT              "%lx"
#define KNH_UINT_MAX              ULONG_MAX
#define KNH_UINT_MIN              0
#define KNH_UINT_FMT              "%lu"
#define knh_abs(n)                labs(n)

#else /*KNH_USING_INT32*/

typedef knh_int64_t        knh_int_t;
typedef knh_uint64_t       knh_uint_t;

#ifndef LLONG_MIN
#define LLONG_MIN -9223372036854775807LL
#define LLONG_MAX  9223372036854775807LL
#endif

#ifndef ULLONG_MAX
#define ULLONG_MAX 18446744073709551615ULL
#endif

#define KNH_INT_MAX               LLONG_MAX
#define KNH_INT_MIN               (LLONG_MIN + 1)
#define KNH_INT_NULL              (LLONG_MIN)
#define KNH_INT_FMT               "%lld"
#define KNH_INT_XFMT              "%llx"
#define KNH_UINT_MAX              ULLONG_MAX
#define KNH_UINT_MIN              0
#define KNH_UINT_FMT              "%llu"
#define knh_abs(n)                llabs(n)

#endif/*KNH_USING_INT32*/

#define KNH_INT_FMTSIZ            40

//OLD
//#define KNH_INT_BSIZE             (sizeof(knh_int_t))

/* ------------------------------------------------------------------------ */
/* Float, knh_float_t */
/* ------------------------------------------------------------------------ */

#ifdef KNH_USING_LONGDOUBLE
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
#else/*KNH_USING_LONGDOUBLE*/

#ifdef KNH_USING_FLOAT
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
#else/*KNH_USING_FLOAT*/

typedef double                    knh_float_t;
#define KNH_FLOAT_MAX             DBL_MAX
#define KNH_FLOAT_MIN             (-(DBL_MAX))
#define KNH_FLOAT_STEP            DBL_MIN
#define KNH_FLOAT_FMT             "%f"
#define KNH_FLOAT_FMT1            "%.1f"
#define KNH_FLOAT_FMT2            "%.2f"
#define KNH_FLOAT_FMT3            "%.3f"
#define KNH_FLOAT_FMT4            "%.4f"
#define KNH_FLOAT_FMTE            "%e"
#endif/*KNH_USING_FLOAT*/
#endif/*KNH_USING_LONGDOUBLE*/

#define KNH_FLOAT_NAN             (0.0/0.0)
#define KNH_FLOAT_NULL            KNH_FLOAT_NAN
#define KNH_FLOAT_FMTSIZ          80

/* ------------------------------------------------------------------------ */
/* String, knh_uchar_t */
/* ------------------------------------------------------------------------ */

typedef unsigned char           knh_uchar_t;    /* byte */

typedef struct {
	knh_uchar_t *buf;
	size_t     len;
} knh_bytes_t;

#define ismulti(c)             (((knh_uchar_t)c)>127)

/* ------------------------------------------------------------------------ */
/* ConstData  */
/* ------------------------------------------------------------------------ */

typedef struct {
	char *name;
	knh_int_t ivalue;
} knh_IntConstData_t;

typedef struct {
	char *name;
	knh_float_t fvalue;
} knh_FloatConstData_t;

typedef struct {
	char *name;
	char *value;
} knh_StringConstData_t;

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

#define KNH_FLAG_SET(f,op)     (f) = ((f)|(op))
#define KNH_FLAG_UNSET(f,op)   (f) = ((f)&(~(op)))
#define KNH_FLAG_IS(f,op)      (((f) & (op)) == (op))

/* ------------------------------------------------------------------------ */
/* Struct, Class, Type  */
/* ------------------------------------------------------------------------ */

typedef const struct knh_Context_t    Ctx;

typedef knh_uint16_t       knh_struct_t ; /* struct id*/
typedef knh_uint16_t       knh_class_t;   /* class id */
typedef knh_uint16_t       knh_type_t;    /* extended knh_type_t */
typedef knh_uint16_t       knh_expt_t;    /* knh_expt_t */

#define KNH_FLAG_TF_NN                KNH_FLAG_T0
#define TYPE_ISNULLABLE(t)            ((t & KNH_FLAG_TF_NN)==0)
#define IS_NNTYPE(t)                  ((t & KNH_FLAG_TF_NN)==KNH_FLAG_TF_NN)
#define NNTYPE_cid(c)                 (c|KNH_FLAG_TF_NN)
#define TYPE_TONNTYPE(t)              (t|KNH_FLAG_TF_NN)

#define CLASS_type(t)                (t&(~KNH_FLAG_TF_NN))

// @NOUSE
#define TYPEQN(t)                     TYPEN(t), TYPEQ(t)

#define TYPE_void                     NNTYPE_cid(CLASS_Nue)
#define NNTYPE_void                   NNTYPE_cid(CLASS_Nue)
#define TYPE_any                      CLASS_Any
#define NNTYPE_any                    CLASS_any

//OLD
//typedef knh_ushort_t          knh_nsid_t;

/* ------------------------------------------------------------------------ */

typedef knh_ushort_t          knh_fieldn_t;
typedef knh_ushort_t          knh_methodn_t;

#define FIELDN_NONAME    ((knh_fieldn_t)-1)
#define FIELDN_NEWID     ((knh_fieldn_t)-2)
#define FIELDN_return    FIELDN_
#define METHODN_NONAME   ((knh_methodn_t)-1)
#define METHODN_NEWID    ((knh_methodn_t)-2)

#define KNH_FLAG_FN_U1         KNH_FLAG_T0
#define KNH_FLAG_FN_U2         KNH_FLAG_T1
#define KNH_FLAG_FN_SUPER      (KNH_FLAG_T0|KNH_FLAG_T1)

#define FIELDN_IS_SUPER(fnq)       ((fnq & KNH_FLAG_FN_SUPER) == KNH_FLAG_FN_SUPER)
#define FIELDN_IS_U1(fnq)          ((fnq & KNH_FLAG_FN_U1) == KNH_FLAG_FN_U1)
#define FIELDN_IS_U2(fnq)          ((fnq & KNH_FLAG_FN_U2) == KNH_FLAG_FN_U2)

#define FIELDN_UNMASK(fnq)         (fnq & (~(KNH_FLAG_FN_SUPER|KNH_FLAG_FN_U1|KNH_FLAG_FN_U2)))

#define KNH_FLAG_MN_SUPER        KNH_FLAG_T0
#define KNH_FLAG_MN_GETTER       KNH_FLAG_T1
#define KNH_FLAG_MN_SETTER       KNH_FLAG_T2
#define KNH_FLAG_MN_MOVTEXT      (KNH_FLAG_T1|KNH_FLAG_T2)
#define KNH_FLAG_MN_FIELDN       (~(KNH_FLAG_T0|KNH_FLAG_T1|KNH_FLAG_T2))

#define METHODN_IS_GETTER(mn)   ((mn & KNH_FLAG_MN_MOVTEXT) == KNH_FLAG_MN_GETTER)
#define METHODN_TO_GETTER(mn)   (mn | KNH_FLAG_MN_GETTER)
#define METHODN_IS_SETTER(mn)   ((mn & KNH_FLAG_MN_MOVTEXT) == KNH_FLAG_MN_SETTER)
#define METHODN_TO_SETTER(mn)   (mn | KNH_FLAG_MN_SETTER)
#define METHODN_IS_MOVTEXT(mn)  ((mn & KNH_FLAG_MN_MOVTEXT) == KNH_FLAG_MN_MOVTEXT)
#define METHODN_TO_MOVTEXT(mn)  (mn | KNH_FLAG_MN_MOVTEXT)

#define METHODN_TOFIELDN(mn)     (mn & KNH_FLAG_MN_FIELDN)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Object */
/* ------------------------------------------------------------------------ */

#define KNH_OBJECT_MAGIC         578

#ifdef KNH_USING_RCGC
#define KNH_HOBJECT_REFC      1
#endif

typedef knh_ushort_t knh_lock_t;

#ifdef KNH_OBJECT_MAGIC
	#define KNH_ASSERT_ISOBJECT(o)        DBG2_ASSERT((o)->h.magic == KNH_OBJECT_MAGIC)
#else/*KONOHA_OBJECT_MAGIC*/
	#define KNH_ASSERT_ISOBJECT(o)
#endif/*KONOHA_OBJECT_MAGIC*/

typedef struct knh_hObject_t {
	knh_ushort_t magic; knh_flag_t  flag;
	knh_class_t bcid;   knh_class_t cid;
	knh_ushort_t ctxid; knh_lock_t  lock;
//#ifdef KNH_HOBJECT_REFC
	KNH_MT_VOLATILE knh_uintptr_t refc;
//#endif
	void *meta;
} knh_hObject_t ;

typedef struct knh_Object_t {
	knh_hObject_t h;
	void *ref;
	void *ref2_unused;
	void *ref3_unused;
} knh_Object_t ;

/* types of basic objects (not type-checked) */

#define Object          knh_Object_t
#define ObjectNULL      Object
#define Any             knh_Object_t
#define This            knh_Object_t
#define Any1            knh_Object_t
#define Any2            knh_Object_t
#define UP(o)           (Object*)(o)

#define KNH_FIELDn(v,n)            ((Script*)(v))->fields[(n)]

/* ------------------------------------------------------------------------ */
/* Common Object Structure */

typedef knh_ushort_t          knh_fileid_t;
typedef knh_ushort_t          knh_sline_t;

typedef struct {
	knh_hObject_t h;
	void *ref;
	knh_fileid_t fileid;
	knh_sline_t  line;
} knh_FileLine_t ;

#define knh_Object_data(o)       (((Int*)(o))->n.data)

/* ------------------------------------------------------------------------ */
/* Thread */
/* ------------------------------------------------------------------------ */

#define KNH_USING_NOTHREAD 1
#ifdef KNH_USING_PTHREAD
#undef KNH_USING_NOTHREAD
typedef pthread_t knh_thread_t;
typedef pthread_key_t knh_thread_key_t;
typedef pthread_mutex_t  knh_mutex_t;
#endif

#ifdef KNH_USING_NOTHREAD
typedef knh_int_t knh_thread_t;
typedef knh_int_t knh_thread_key_t;
typedef knh_int_t knh_mutex_t;
#endif

typedef struct knh_Thread_t {
	knh_hObject_t h;
	knh_thread_t thid;
} knh_Thread_t ;


#ifndef KNH_TLOCK_SIZE
#define KNH_TLOCK_SIZE 256
#endif

#define SIZEOF_TLOCK       (KNH_TLOCK_SIZE * sizeof(knh_LockTable_t))

typedef void (*knh_fmutexlock)(Ctx *ctx, knh_lock_t lock, Object *o);
typedef void (*knh_fmutexunlock)(Ctx *ctx, knh_lock_t lock);

typedef struct knh_LockTable_t {
	knh_lock_t  lock;     knh_flag_t  flag;
	knh_mutex_t mutex;
	knh_fmutexlock       flock;
	knh_fmutexunlock       funlock;
	int ctxid;
	size_t count;
	struct knh_String_t *name;
	union {
		Object *sharedObject;
		struct knh_LockTable_t *unused;
	};
} knh_LockTable_t;

#define LOCK_NO           ((knh_lock_t)0)
#define LOCK_MEMORY       ((knh_lock_t)1)
#define LOCK_SYSTBL       ((knh_lock_t)2)
#define LOCK_GIANT        ((knh_lock_t)3)

#define KNH_LOCK(ctx, lk, o)    (ctx->share)->LockTable[lk].flock(ctx, lk, o)
#define KNH_UNLOCK(ctx, lk, o)  (ctx->share)->LockTable[lk].funlock(ctx, lk)

/* ------------------------------------------------------------------------ */
/* Stack Frame Pointer */
/* ------------------------------------------------------------------------ */

typedef unsigned char           knh_code_t;          /* knh_vmc_t */

typedef struct knh_sfp_t {
	union {
		void   *ref;
		Object *o;
		struct knh_Int_t    *i;
		struct knh_Float_t  *f;
		struct knh_Class_t  *c;
		struct knh_String_t *s;
		struct knh_Bytes_t  *ba;
		struct knh_Iterator_t *it;
		struct knh_Closure_t *cc;
		struct knh_Glue_t   *glue;
		struct knh_OutputStream_t *w;
		struct knh_Method_t *mtd;
		struct knh_Mapper_t *mpr;
		struct knh_Exception_t *e;
		struct knh_ExceptionHandler_t *hdr;
	};
	union {
		knh_boolean_t bvalue;
		knh_int_t     ivalue;
		knh_float_t   fvalue;
		knh_uint64_t  data;
		knh_code_t    *pc;
	};
} knh_sfp_t;

/* ------------------------------------------------------------------------ */
/* [Context] */
/* ------------------------------------------------------------------------ */

#define KNH_FASTMALLOC_SIZE  sizeof(knh_Object_t)
#define KNH_FASTMALLOC_BSIZE (KNH_FASTMALLOC_SIZE/sizeof(knh_Object_t*))
#define KNH_SMALLMALLOC_SIZE 80

/* ------------------------------------------------------------------------ */
/* [StructTable] */

#ifndef KNH_TSTRUCT_SIZE
#define KNH_TSTRUCT_SIZE 256
#endif

#define STRUCT_newid         ((knh_struct_t)-1)
#define SIZEOF_TSTRUCT       (KNH_TSTRUCT_SIZE * sizeof(knh_StructTable_t))

char *konoha_geStructTableName(Ctx *ctx, knh_struct_t sid);
#define STRUCTN(sid)         konoha_geStructTableName(ctx, sid)

typedef void (*knh_fgchook)(Ctx *ctx);
typedef void (*knh_ftraverse)(Ctx *ctx, Object *);
typedef int (*knh_finit)(Ctx *);

typedef knh_uintptr_t                knh_hcode_t;  /* knh_hcode_t */
#define knh_hcode_join(s1,s2)	   ((knh_hcode_t)s1 << (sizeof(knh_short_t)*8)) + s2;

#define KNH_OBJECT_RAWINIT              (-1)

typedef void         (*knh_fstruct_init)(Ctx *, Object *, int);
typedef void         (*knh_fstruct_traverse)(Ctx *, Object*, knh_ftraverse);
typedef int          (*knh_fstruct_compareTo)(Object*, Object*);
typedef knh_hcode_t  (*knh_fstruct_hashCode)(Ctx *ctx, Object *);
typedef Object*      (*knh_fstruct_copy)(Ctx *, Object *);
typedef void         (*knh_fstruct_newClass)(Ctx *ctx, knh_class_t cid);
typedef struct knh_String_t* (*knh_fstruct_getkey)(Ctx *ctx, knh_sfp_t *lsfp);

typedef struct {
	knh_fstruct_traverse   ftraverse;
	knh_fstruct_compareTo  fcompareTo;
	knh_fstruct_init       finit;
	knh_fstruct_getkey     fgetkey;
	size_t                 size;
	knh_flag_t             flag;
	knh_struct_t           sid;
	knh_fstruct_hashCode   fhashCode;
	knh_fstruct_copy       fcopy;
	knh_fstruct_newClass   fnewClass;
	char                  *name;
} knh_StructTable_t ;

/* ------------------------------------------------------------------------ */

#ifndef KNH_TCLASS_SIZE
#define KNH_TCLASS_SIZE 1024
#endif

#define SIZEOF_TCLASS  (KNH_TCLASS_SIZE * sizeof(knh_ClassTable_t))

typedef knh_Object_t* (*knh_fdefault)(Ctx *ctx, knh_class_t cid);

typedef struct {
	knh_flag_t    cflag;   knh_flag_t    oflag;
	knh_class_t   bcid;    knh_class_t   supcid;
	knh_class_t   p1;      knh_type_t    p2;
	knh_ushort_t  offset;  knh_struct_t  sid;
	knh_ushort_t  size;    knh_ushort_t  bsize;
	union {
		knh_short_t   keyidx;
		knh_type_t    r0;
	};
	union {
		knh_short_t   keyidx2;
		knh_type_t    p3;
	};
	struct knh_String_t       *sname;
	struct knh_String_t       *lname;
	struct knh_Class_t        *class_cid;
	struct knh_ClassStruct_t  *cstruct;
	struct knh_ClassMap_t     *cmap;
	struct knh_Object_t       *cspec;
	knh_fdefault               fdefault;
	knh_mutex_t                dataLock;
	struct knh_Array_t        *dataList;
	struct knh_DictMap_t      *dataMap;
} knh_ClassTable_t;

/* ------------------------------------------------------------------------ */

#ifndef KNH_TEXPT_SIZE
#define KNH_TEXPT_SIZE (KNH_TCLASS_SIZE/4)
#endif

#define SIZEOF_TEXPT  (KNH_TEXPT_SIZE * sizeof(knh_ExptTable_t))

typedef struct {
	knh_flag_t   flag;
	knh_expt_t   parent;
	struct knh_String_t     *name;
} knh_ExptTable_t;

/* ------------------------------------------------------------------------ */
/* [SystemStat] */

typedef struct {
	size_t usedMemorySize;
	size_t usedObjectSize;
	size_t mtdCacheHit;
	size_t mtdCacheMiss;
	size_t fmtCacheHit;
	size_t fmtCacheMiss;
	size_t mprCacheHit;
	size_t mprCacheMiss;
} knh_ctxstat_t;

#define knh_stat_incUsedMemorySize(ctx, n)   (ctx->stat)->usedMemorySize += (n)
#define knh_stat_dclUsedMemorySize(ctx, n)   (ctx->stat)->usedMemorySize -= (n)
#define knh_stat_incUsedObjectSize(ctx, n)   (ctx->stat)->usedObjectSize += (n)
#define knh_stat_dclUsedObjectSize(ctx, n)   (ctx->stat)->usedObjectSize -= (n)
#define knh_stat_mtdCacheHit(ctx)   (ctx->stat)->mtdCacheHit += 1
#define knh_stat_mtdCacheMiss(ctx)  (ctx->stat)->mtdCacheMiss += 1
#define knh_stat_fmtCacheHit(ctx)   (ctx->stat)->fmtCacheHit += 1
#define knh_stat_fmtCacheMiss(ctx)  (ctx->stat)->fmtCacheMiss += 1
#define knh_stat_mprCacheHit(ctx)   (ctx->stat)->mprCacheHit += 1
#define knh_stat_mprCacheMiss(ctx)  (ctx->stat)->mprCacheMiss += 1

/* ------------------------------------------------------------------------ */
/* [SystemShare] */

#ifndef KNH_TINT_MIN
#define KNH_TINT_MIN (-1)  /* @property */
#endif

#ifndef KNH_TINT_MAX
#ifdef KNH_FASTMODE
#define KNH_TINT_MAX 1024  /* @property */
#else
#define KNH_TINT_MAX 256  /* @property */
#endif
#endif

#define SIZEOF_TINT (sizeof(knh_Object_t*) * (KNH_TINT_MAX - KNH_TINT_MIN + 1))
#define SIZEOF_TSTRING (sizeof(knh_Object_t*) * KNH_TSTRING_SIZE)

#define knh_rootNameSpace     DP(ctx->sys)->ns
#define knh_systemEncoding    DP(ctx->sys)->enc

#define KNH_NULL            (ctx->share->constNull)
#define KNH_VOID            (ctx->share->constVoid)
#define KNH_TRUE            (ctx->share->constTrue)
#define KNH_FALSE           (ctx->share->constFalse)
#define KNH_SYSTEM          (ctx->sys)
#define KNH_INT0            (ctx->share->tInt[0 - KNH_TINT_MIN])
#define KNH_FLOAT0          (ctx->share->constFloat0)

/* ------------------------------------------------------------------------ */

#define knh_Object_sweep       (ctx)->fsweep
#define IS_SWEEP(f)            (f == knh_Object_sweep)

/* ------------------------------------------------------------------------ */

#ifndef KNH_TOBJECTPAGE_SIZE
#define KNH_TOBJECTPAGE_SIZE     1024
#endif

#define SIZEOF_TOBJECTPAGE       (sizeof(knh_ObjectPageTable_t) * KNH_TOBJECTPAGE_SIZE)

#ifndef KNH_OBJECTPAGE_SIZE
#define KNH_OBJECTPAGE_SIZE     4096
#endif

#define SIZEOF_OBJECTPAGE       (sizeof(knh_Object_t) * KNH_OBJECTPAGE_SIZE)

typedef struct knh_ObjectPageTable_t {
	int   ctxid;
	char *thead;
} knh_ObjectPageTable_t ;

/* ------------------------------------------------------------------------ */

typedef struct {
	/* system table */
	size_t              threadSize;
	knh_LockTable_t    *LockTable;
	knh_LockTable_t    *unusedLockTable;
	knh_ObjectPageTable_t  *ObjectPageTable; size_t ObjectPageTableSize;
	knh_StructTable_t  *StructTable; size_t StructTableSize;
	knh_ClassTable_t   *ClassTable;  size_t ClassTableSize;
	knh_ExptTable_t    *ExptTable;   size_t ExptTableSize;

	/* system const */
	knh_Object_t   *constNull;
	knh_Object_t   *constVoid;
	knh_Object_t   *constTrue;
	knh_Object_t   *constFalse;
	struct knh_Float_t   *constFloat0;
	struct knh_Int_t     **tInt;
	struct knh_String_t  **tString;
} knh_ctxshare_t ;

/* ------------------------------------------------------------------------ */

typedef struct knh_Context_t {
	knh_hObject_t h;
	knh_Object_t        *unusedObject;
	size_t               unusedObjectSize;

	/* stack */
	knh_sfp_t*                   stack;
	knh_sfp_t*                   esp;
	size_t                       stacksize;
	knh_ftraverse                fsweep;

	/* cache (stacksize * 2 + 1) */
	size_t                        cachesize;
	struct knh_Method_t         **mtdCache;
	struct knh_Method_t         **fmtCache;
	struct knh_Mapper_t         **mprCache;

	/* root table */
	knh_ctxshare_t   *share;
	knh_ctxstat_t    *stat;

	knh_flag_t                   flag;
	knh_ushort_t                 ctxid;
	char*                        cwd;
	knh_thread_t                 threadid;
	struct knh_Context_t        *parent;

	struct knh_System_t*         sys;
	struct knh_String_t*         enc;
	struct knh_InputStream_t*    in;
	struct knh_OutputStream_t*   out;
	struct knh_OutputStream_t*   err;
	struct knh_Bytes_t*          bufa;
	struct knh_OutputStream_t*   bufw;
	struct knh_Bytes_t*          bconvbuf;
	struct knh_DictMap_t*        props;

	struct knh_NameSpace_t      *ns;
	struct knh_DictMap_t        *tsymbolDictMap;
	struct knh_Asm_t            *cmpr;

//	struct knh_HashMap_t        *tmapperHashMap;
//	struct knh_HashMap_t        *tmethodHashMap;
} knh_Context_t ;

/* ------------------------------------------------------------------------ */

#define KONOHA_MAGIC        314159

typedef struct konoha_t {
	knh_uintptr_t  magic;
	Ctx *ctx;
} konoha_t ;

/* ------------------------------------------------------------------------ */

#define KONOHA_CHECK_(konoha) \
	if(konoha.magic != KONOHA_MAGIC) { \
		KNH_SAYS("This is not a Konoha Scripting Engine"); \
		return; \
	}\

#define KONOHA_CHECK(konoha, value) \
	if(konoha.magic != KONOHA_MAGIC) { \
		KNH_SAYS("This is not a Konoha Scripting Engine"); \
		return value; \
	}\

/* ------------------------------------------------------------------------ */
/* KLRCode */
/* ------------------------------------------------------------------------ */

typedef struct {
	size_t pos;
	struct knh_Bytes_t          *ba;
	struct knh_OutputStream_t   *w;
} knh_cwb_t;

/* ------------------------------------------------------------------------ */
/* Functions */
/* ------------------------------------------------------------------------ */

#ifdef _MSC_VER
typedef void   (KNH_CC_FASTCALL *knh_fmethod)(Ctx *, knh_sfp_t *);
#else
typedef METHOD (*knh_fmethod)(Ctx *, knh_sfp_t *);
#endif

#ifdef _MSC_VER
typedef void   (KNH_CC_FASTCALL *knh_fmapper)(Ctx *, knh_sfp_t *);
#else
typedef MAPPER (*knh_fmapper)(Ctx *, knh_sfp_t *);
#endif

/* ======================================================================== */
/* driver */
/* ======================================================================== */

#define KNHINIT

typedef struct {
	int   type;
	char *name;
} knh_drvapi_t ;

#define KNH_DRVAPI_TYPE__UNKNOWN          0
#define KNH_DRVAPI_TYPE__BCONV            1
#define KNH_DRVAPI_TYPE__SCONV            2
#define KNH_DRVAPI_TYPE__IO               3
#define KNH_DRVAPI_TYPE__PARSER           4
#define KNH_DRVAPI_TYPE__REGEX            5
#define KNH_DRVAPI_TYPE__DB               6

#define IS_DRVAPI(c)   (0 < c && c < 7)

/* ------------------------------------------------------------------------ */
/* KNH_DRVAPI_TYPE__BYTECONV */

struct knh_BytesConv_t;
typedef size_t (*knh_fbcnv)(Ctx *ctx, struct knh_BytesConv_t *o, knh_bytes_t t, struct knh_Bytes_t *ba);

typedef struct {
	int  type;
	char *name;
	knh_fbcnv  fbconv;
	knh_fbcnv  fbconv_inverse;
} knh_bconv_driapi_t;

/* ------------------------------------------------------------------------ */
/* KNH_DRVAPI_TYPE__IO */

typedef knh_intptr_t knh_io_t;

typedef knh_io_t (*f_io_open)(Ctx *ctx, struct knh_InputStream_t *in, struct knh_OutputStream_t *out, knh_bytes_t urn, char *mode);
typedef knh_intptr_t (*f_io_read)(Ctx *ctx, knh_io_t fd, char *buf, size_t bufsiz);
typedef knh_intptr_t (*f_io_write)(Ctx *ctx, knh_io_t fd, char *buf, size_t bufsiz);
typedef void   (*f_io_close)(Ctx *ctx, knh_io_t fd);

typedef struct {
	int type; char *name;
	size_t bufsiz;
	f_io_open    fopen;
	f_io_read    fread;
	f_io_write   fwrite;
	f_io_close   fclose;
} knh_iodrv_t;

/* ------------------------------------------------------------------------ */
/* KNH_DRVAPI_TYPE__PARSER */

typedef knh_Object_t* (*knh_fparser)(Ctx *, struct knh_String_t *p);

typedef struct {
	int   type;
	char *name;
	knh_type_t  rtype;
	knh_fparser parser;
} knh_parser_drvapi_t;

/* ------------------------------------------------------------------------ */
/* KNH_DRVAPI_TYPE__REGEX */

typedef void knh_regex_t;

#ifndef KNH_REGEX_NMATCH_SIZE
#define KNH_REGEX_NMATCH_SIZE    16
#endif

typedef struct {
	int rm_so;   /* start of match */
	int rm_eo;   /* endo of match */
	knh_bytes_t rm_name;  /* {NULL, 0}, if not NAMED */
} knh_regmatch_t;

typedef knh_regex_t* (*knh_fregmalloc)(Ctx *);
typedef int (*knh_fregcomp)(Ctx *, knh_regex_t *, char *pattern, int flags);
typedef int (*knh_fregexec)(Ctx *, knh_regex_t *, char *str, size_t nmatch, knh_regmatch_t p[], int flags);
typedef void (*knh_fregfree)(Ctx *, knh_regex_t *);

typedef struct {
	int  type;
	char *name;
	knh_fregmalloc regmalloc;
	knh_fregcomp   regcomp;
	knh_fregexec   regexec;
	knh_fregfree   regfree;
} knh_regex_drvapi_t;

/* ------------------------------------------------------------------------ */
/* KNH_DRVAPI_TYPE__DB */

typedef void   knh_db_t;
typedef void   knh_dbcur_t;
struct knh_ResultSet_t;
typedef knh_db_t* (*knh_fdbopen)(Ctx *ctx, knh_bytes_t url);
typedef knh_dbcur_t* (*knh_fdbquery)(Ctx *ctx, knh_db_t *, knh_bytes_t query, struct knh_ResultSet_t*);
typedef void   (*knh_fdbclose)(Ctx *ctx, knh_db_t *);

typedef int    (*knh_fdbcurnext)(Ctx *, knh_dbcur_t *, struct knh_ResultSet_t*);
typedef void   (*knh_fdbcurfree)(knh_dbcur_t *);

typedef struct {
	int  type;
	char *name;
	knh_fdbopen   dbopen;
	knh_fdbquery  dbquery;
	knh_fdbclose  dbclose;
	knh_fdbcurnext dbcurnext;
	knh_fdbcurfree dbcurfree;
} knh_db_drvapi_t;

/* ======================================================================== */
/* mutex */
/* ======================================================================== */


/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

#endif /*KONOHA_T_H_*/
