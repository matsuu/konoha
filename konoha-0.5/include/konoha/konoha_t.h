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

#ifndef KONOHA_T_H_
#define KONOHA_T_H_

#include"konoha_config.h"

#ifdef KNH_USING_STDC
#include<stdio.h>
#include<limits.h>
#include<float.h>
#include<setjmp.h>

#define __STDC_LIMIT_MACROS
#include<stdint.h>
#define __STDC_FORMAT_MACROS
#include<inttypes.h>

#endif

#if defined(KNH_USING_PTHREAD)
	#include<pthread.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */

#ifdef KONOHA_ON_WINDOWS
#define METHOD             void __declspec(dllexport)
#else
#define METHOD             void  KNH_CC_FASTCALL
#endif

#define MAPPER             METHOD
#define ITRNEXT            int   KNH_CC_FASTCALL

#ifdef KNH_USING_THREAD
#define KNH_MT_VOLATILE           volatile
#else
#define KNH_MT_VOLATILE
#endif

#define KONOHA_SYSTEM_BIT        (sizeof(void*) * CHAR_BIT))

typedef int16_t           knh_int16_t;
typedef uint16_t          knh_uint16_t;
typedef int32_t           knh_int32_t;
typedef uint32_t          knh_uint32_t;
typedef int64_t           knh_int64_t;
typedef uint64_t          knh_uint64_t;

typedef intptr_t                  knh_intptr_t;
typedef uintptr_t                 knh_uintptr_t;
typedef knh_intptr_t              knh_index_t;

#if defined(__LP64__)
typedef int32_t           knh_short_t;
typedef uint32_t          knh_ushort_t;
#else
typedef int16_t           knh_short_t;
typedef uint16_t          knh_ushort_t;
#endif

/* ------------------------------------------------------------------------ */
/* Bool(ean), knh_bool_t */
/* ------------------------------------------------------------------------ */

typedef knh_intptr_t      knh_bool_t;
typedef knh_intptr_t      knh_boolean_t;

/* ------------------------------------------------------------------------ */
/* Int, knh_int_t */
/* ------------------------------------------------------------------------ */

#define KNH_INTPTR_FMT               "%"PRIdPTR
#define KNH_INTPTR_UFMT              "%"PRIuPTR

/* ------------------------------------------------------------------------ */
/* Integer, knh_int_t */
/* ------------------------------------------------------------------------ */

#ifdef KNH_USING_INT32

typedef long                knh_int_t;
typedef unsigned long       knh_uint_t;

#define KNH_INT_MAX               LONG_MAX
#define KNH_INT_MIN               LONG_MIN
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
#define KNH_INT_MIN               LLONG_MIN
#define KNH_INT_FMT               "%lld"
#define KNH_INT_XFMT              "%llx"
#define KNH_UINT_MAX              ULLONG_MAX
#define KNH_UINT_MIN              0
#define KNH_UINT_FMT              "%llu"
#define knh_abs(n)                llabs(n)

#endif/*KNH_USING_INT32*/

#define KNH_INT_FMTSIZ            40

/* ------------------------------------------------------------------------ */
/* Float, knh_float_t */
/* ------------------------------------------------------------------------ */

#ifdef KNH_USING_NOFLOAT
/* dummy */
typedef int               knh_float_t;
#define KNH_FLOAT_MAX             0
#define KNH_FLOAT_MIN             0
#define KNH_FLOAT_STEP            0
#define KNH_FLOAT_FMT             "%d"
#define KNH_FLOAT_FMT1            "%d"
#define KNH_FLOAT_FMT2            "%d"
#define KNH_FLOAT_FMT3            "%d"
#define KNH_FLOAT_FMT4            "%d"
#define KNH_FLOAT_FMTE            "%d"
#define KNH_FLOAT_NAN             0
#define KNH_FLOAT_NULL            KNH_FLOAT_NAN
#define KNH_FLOAT_FMTSIZ          40
#endif/*KNH_USING_NOFLOAT*/

#if defined(KNH_USING_LONGDOUBLE) && !defined(KNH_FLOAT_FMT)
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
#endif

#if defined(KNH_USING_FLOAT) && !defined(KNH_FLOAT_FMT)
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
#endif

#ifndef KNH_FLOAT_FMT
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
#endif

#ifndef KNH_FLOAT_NAN
#define KNH_FLOAT_NAN             (0.0/0.0)
#define KNH_FLOAT_NULL            KNH_FLOAT_NAN
#define KNH_FLOAT_FMTSIZ          80
#endif /*KNH_FLOAT_NAN*/

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

typedef struct {
	char *name;
	void *ptr;
} knh_NamedPointerData_t;

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

/* knh_struct_t */
#define KNH_FLAG_SF_FIELD          KNH_FLAG_T1

#define STRUCT_ISFIELD(sid)        ((sid & KNH_FLAG_SF_FIELD) == KNH_FLAG_SF_FIELD)
#define BSIZE_TOSID(bsize)         (((knh_struct_t)bsize)|KNH_FLAG_SF_FIELD)
#define STRUCT_FIELD(bsize)        (((knh_struct_t)bsize)|KNH_FLAG_SF_FIELD)
#define STRUCT_FIELDSIZE(sid)      (sid & (~KNH_FLAG_SF_FIELD))
#define STRUCT_UNMASK(sid)         (sid & (~KNH_FLAG_SF_FIELD))
#define KNH_ASSERT_sid(sid)        KNH_ASSERT(((knh_struct_t)sid) < ctx->share->StructTableSize)

/* knh_class_t */

#define CLASS_newid                ((knh_class_t)-1)
#define CLASS_unknown              ((knh_class_t)-2)
#define CLASS_type(t)              (t&(~KNH_FLAG_TF_NN))

#define KNH_ASSERT_cid(cid)        KNH_ASSERT(cid < KNH_TCLASS_SIZE)
#define CLASSN(cid)                knh_ClassTable_CLASSN(ctx, cid)
#define CLASSNo(o)                 knh_ClassTable_CLASSN(ctx, knh_Object_cid(o))

/* knh_type_t */

#define KNH_FLAG_TF_NN      KNH_FLAG_T0
#define TYPE_ISNULLABLE(t)  ((t & KNH_FLAG_TF_NN)==0)
#define IS_NNTYPE(t)        ((t & KNH_FLAG_TF_NN)==KNH_FLAG_TF_NN)
#define NNTYPE_cid(c)       (c|KNH_FLAG_TF_NN)
#define TYPE_TONNTYPE(t)    (t|KNH_FLAG_TF_NN)

#define IS_ubxint(t)        (IS_NNTYPE(t) && ClassTable(CLASS_type(t)).bcid == CLASS_Int)
#define IS_ubxfloat(t)      (IS_NNTYPE(t) && ClassTable(CLASS_type(t)).bcid == CLASS_Float)
#define IS_ubxboolean(t)    (NNTYPE_Boolean == t)
#define IS_ubxtype(t)       (IS_NNTYPE(t) && (ClassTable(CLASS_type(t)).bcid == CLASS_Int || ClassTable(CLASS_type(t)).bcid == CLASS_Float || t == NNTYPE_Boolean) )
#define IS_bxint(t)         (!IS_NNTYPE(t) && ClassTable(CLASS_type(t)).bcid == CLASS_Int)
#define IS_bxfloat(t)       (!IS_NNTYPE(t) && ClassTable(CLASS_type(t)).bcid == CLASS_Float)

// @NOUSE
#define TYPEQN(t)                     TYPEN(t), TYPEQ(t)

#define TYPE_var                      CLASS_AnyVar
#define TYPE_void                     NNTYPE_cid(CLASS_Any)
#define NNTYPE_void                   NNTYPE_cid(CLASS_Any)

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

typedef knh_ushort_t              knh_uri_t;
#define KNH_FLAG_URI_UNTRUSTED    KNH_FLAG_T0
#define URI_UNMASK(uri)           (uri & (~(KNH_FLAG_URI_UNTRUSTED)))
#define URI_TRUSTED(uri)          (uri & (~(KNH_FLAG_URI_UNTRUSTED)))
#define URI_UNTRUSTED(uri)        (uri & KNH_FLAG_URI_UNTRUSTED)
#define URI_ISTRUSTED(uri)        ((uri & KNH_FLAG_URI_UNTRUSTED) == 0)
#define URI_EVAL                  URI_UNTRUSTED(((knh_uri_t)0)

typedef knh_ushort_t              knh_sline_t;

typedef struct {
	knh_hObject_t h;
	void *ref;
	knh_uri_t uri;
	knh_sline_t  line;
} knh_FileLine_t ;

typedef struct {
	const char *file;
	int   line;
} knh_fline_t;

#define knh_Object_data(o)       (((Int*)(o))->n.data)

/* ------------------------------------------------------------------------ */
/* Thread */
/* ------------------------------------------------------------------------ */

#if defined(KNH_USING_PTHREAD)
#define knh_thread_t pthread_t
#define knh_thread_key_t pthread_key_t
#define knh_mutex_t pthread_mutex_t
#elif defined(KNH_USING_BTRON)
#define knh_thread_t W
#define knh_thread_key_t W
#define knh_mutex_t W
#else
typedef knh_intptr_t knh_thread_t;
typedef knh_intptr_t knh_thread_key_t;
typedef knh_intptr_t knh_mutex_t;
#endif

typedef struct knh_Thread_t {
	knh_hObject_t h;
	knh_thread_t thid;
} knh_Thread_t ;

typedef struct knh_LockTable_t {
	knh_mutex_t *mutex;
	size_t count;
	struct knh_String_t *name;
	union {
		Object *so;   /* shared object*/
		struct knh_LockTable_t *unused;
	};
	char *filename;
	int   lineno;
} knh_LockTable_t;

#define LOCK_NOP          ((knh_lock_t)0)
#define LOCK_MEMORY       ((knh_lock_t)1)
#define LOCK_SYSTBL       ((knh_lock_t)2)
#define LOCK_UNUSED       3

#ifndef KNH_TLOCK_SIZE
#define KNH_TLOCK_SIZE (LOCK_UNUSED+1)
#endif

#define SIZEOF_TLOCK   (KNH_TLOCK_SIZE * sizeof(knh_LockTable_t))

#define KNH_LOCK(ctx, lockid, o)    knh_lockID(ctx, lockid, o, (char*)__FILE__, (int)__LINE__)
#define KNH_UNLOCK(ctx, lockid, o)  knh_unlockID(ctx, lockid, (char*)__FILE__, __LINE__)

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
		knh_uint_t    uvalue;
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
	struct knh_DictMap_t      *constPool;
	knh_fdefault               fdefault;

#ifndef KNH_USING_NODATAPOOL
	knh_mutex_t                dataLock;
	struct knh_Array_t        *dataList;
	struct knh_DictMap_t      *dataMap;
#endif
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

#define SIZEOF_TSTRING (sizeof(knh_Object_t*) * KNH_TSTRING_SIZE)

#define KNH_ENC             DP(ctx->sys)->enc

#define KNH_NULL            (ctx->share->constNull)
#define KNH_VOID            (ctx->share->constNull)
#define KNH_TRUE            (ctx->share->constTrue)
#define KNH_FALSE           (ctx->share->constFalse)
#define KNH_INT0            (ctx->share->constInt0)
#define KNH_FLOAT0          (ctx->share->constFloat0)
#define KNH_SYSTEM          (ctx->sys)

/* ------------------------------------------------------------------------ */

#define knh_Object_sweep       (ctx)->fsweep
#define IS_SWEEP(f)            (f == knh_Object_sweep)

/* ------------------------------------------------------------------------ */

#ifndef KNH_TOBJECTPAGE_INITSIZE
#define KNH_TOBJECTPAGE_INITSIZE     1024
#endif

//#define SIZEOF_TOBJECTPAGE       (sizeof(knh_ObjectPageTable_t) * KNH_TOBJECTPAGE_INITSIZE)

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
	knh_ObjectPageTable_t    *ObjectPageTable;
	const knh_StructTable_t  *StructTable;
	const knh_ClassTable_t   *ClassTable;
	const knh_ExptTable_t    *ExptTable;
	size_t ObjectPageTableSize;
	size_t ObjectPageTableMaxSize;
	size_t StructTableSize;
	size_t ClassTableSize;
	size_t ExptTableSize;

	/* system shared const */
	knh_Object_t         *constNull;
	knh_Object_t         *constTrue;
	knh_Object_t         *constFalse;
	struct knh_Int_t     *constInt0;
	struct knh_Float_t   *constFloat0;
	struct knh_String_t  **tString;
	/* share level=2 */
	struct knh_NameSpace_t   *mainns;

	/* thread */
	size_t              contextCounter;
	size_t              threadCounter;
	knh_LockTable_t    *LockTable;
	knh_LockTable_t    *unusedLockTable;
} knh_SharedData_t ;

#define LockTable(mx)     ctx->share->LockTable[mx]
#define pLockTable(mx)    (knh_LockTable_t*)(ctx->share->LockTable + (mx))

#define StructTable(sid)  ctx->share->StructTable[sid]
#define pStructTable(sid) (knh_StructTable_t*)(ctx->share->StructTable + (sid))
#define ClassTable(cid)   ctx->share->ClassTable[cid]
#define pClassTable(cid)  (knh_ClassTable_t*)(ctx->share->ClassTable + (cid))
#define ExptTable(eid)    ctx->share->ExptTable[eid]
#define pExptTable(eid)   (knh_ExptTable_t*)(ctx->share->ExptTable + (eid))

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

	/* shared table */
	const knh_SharedData_t       *share;
	knh_ctxstat_t                *stat;

	knh_flag_t                   flag;
	knh_ushort_t                 ctxid;
	char*                        cwd;
	const struct knh_Context_t   *parent;
	knh_mutex_t                  *ctxlock;
	const struct knh_Context_t   *unusedContext;

	struct knh_System_t*         sys;
	struct knh_String_t*         enc;
	struct knh_InputStream_t*    in;
	struct knh_OutputStream_t*   out;
	struct knh_OutputStream_t*   err;
	struct knh_Bytes_t*          bufa;
	struct knh_OutputStream_t*   bufw;
	struct knh_Bytes_t*          bconvbuf;
	struct knh_DictMap_t*        props;
	struct knh_Asm_t            *abr;
	struct knh_Array_t          *lines;

	int    hasError;
	struct knh_String_t *msgError;

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
typedef size_t (*knh_fbyteconv)(Ctx *ctx, struct knh_BytesConv_t *o, knh_bytes_t t, struct knh_Bytes_t *ba);
typedef void   (*knh_fbyteconvfree)(Ctx *ctx, struct knh_BytesConv_t *);

typedef struct {
	int  type;
	char *name;
	knh_fbyteconv  fbconv;
	knh_fbyteconv  fbconv_inverse;
} knh_bconv_driapi_t;

/* ------------------------------------------------------------------------ */
/* KNH_DRVAPI_TYPE__IO */

typedef knh_intptr_t knh_io_t;

typedef knh_io_t (*f_io_open)(Ctx *ctx, knh_bytes_t urn, char *mode, int isThrowable);
typedef void (*f_io_init)(Ctx *ctx, Object *stream, char *mode);
typedef knh_intptr_t (*f_io_read)(Ctx *ctx, knh_io_t fd, char *buf, size_t bufsiz);
typedef knh_intptr_t (*f_io_write)(Ctx *ctx, knh_io_t fd, char *buf, size_t bufsiz);
typedef void   (*f_io_close)(Ctx *ctx, knh_io_t fd);

typedef struct {
	int type;
	char *name;
	size_t bufsiz;  /* knh_io_t == FILE* if bufsiz == 0 */
	f_io_open    fopen;
	f_io_init    finit;
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
typedef int (*knh_fregcomp)(Ctx *, knh_regex_t *, char *pattern, char *option);
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
