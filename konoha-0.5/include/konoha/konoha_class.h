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

#ifndef CLASS_KONOHA_H_
#define CLASS_KONOHA_H_

#include<konoha/konoha_t.h>

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */
/* flag */
/* ------------------------------------------------------------------------ */
/* @class Object Object knh_Object_t @Cyclic */
/* @flag Object.Release!Debug OF (%s)->h.flag 'is:*:is:*' */
/* @flag Object.Immutable OF (%s)->h.flag 'is:*:is:*' */
/* @flag Object.Cyclic OF (%s)->h.flag 'is:set:*:*' */
/* @flag Object.Undefined OF (%s)->h.flag 'is:*:is:*' */
/* @flag Object.Modified OF (%s)->h.flag 'is:set:is:set' */
/* @flag Object.Formatted OF (%s)->h.flag 'is:set:is:set' */
/* @flag Object.Shared OF (%s)->h.flag 'is:set:is:set' */
/* @flag Object.Local4 OF (%s)->h.flag 'is:set:*:*' */
/* @flag Object.Local3 OF (%s)->h.flag 'is:set:*:*' */
/* @flag Object.Local2 OF (%s)->h.flag 'is:set:*:*' */
/* @flag Object.Local1 OF (%s)->h.flag 'is:set:*:*' */

#ifndef KNH_OBJECT_FIELDSIZE
#define KNH_OBJECT_FIELDSIZE 64
#endif

typedef struct knh_ObjectField_t {
	knh_hObject_t h;
	Object  **fields;
	size_t  bsize;
} knh_ObjectField_t ;

#define knh_Object_cid(o)           (o)->h.cid
#define knh_Object_bcid(o)          (o)->h.bcid

/* ------------------------------------------------------------------------ */

#define IS_IMM(o) (!knh_Object_isImmutable(o))

/* ------------------------------------------------------------------------ */
/* @class Any Object knh_Any_t @Cyclic */
/* @class This Any knh_Any_t @Cyclic  @Private */
/* @class Any0 Any knh_Any_t @Cyclic  @Private */
/* @class Any1 Any knh_Any_t @Cyclic  @Private */
/* @class Any2 Any knh_Any_t @Cyclic  @Private */
/* @class Any3 Any knh_Any_t @Cyclic  @Private */
/* @class AnyVar Any knh_Any_t @Cyclic  @Private */

struct knh_Glue_t;
typedef void (*knh_fgfree)(Ctx *, struct knh_Glue_t *o);

typedef struct knh_Glue_t {
	knh_hObject_t h;
	void *ptr;
	knh_fgfree gfree;
} knh_Glue_t ;

#define CLASS_Glue    CLASS_Any

typedef knh_Glue_t knh_Any_t;
typedef knh_Glue_t knh_This_t;
typedef knh_Glue_t knh_Any0_t;
typedef knh_Glue_t knh_Any1_t;
typedef knh_Glue_t knh_Any2_t;
typedef knh_Glue_t knh_Any3_t;

#define IS_NULL(o)            ((ctx)->share->constNull == UP(o))
#define IS_NOTNULL(o)         ((ctx)->share->constNull != UP(o))

/* ------------------------------------------------------------------------ */
/* @class Boolean Object knh_Boolean_t @Immutable */

typedef struct {
	union {
		knh_boolean_t bvalue;
		knh_int_t ivalue;
		knh_float_t   fvalue;
		knh_uint64_t  data;
	};
} knh_nObject_t ;

typedef struct knh_Boolean_t {
	knh_hObject_t h;
	knh_nObject_t n;
} knh_Boolean_t;

#define IS_TRUE(o)         ((o)->h.bcid == CLASS_Boolean && ((Int*)o)->n.bvalue)
#define IS_FALSE(o)        ((o)->h.bcid == CLASS_Boolean && (((Int*)o)->n.bvalue == 0))
#define new_Boolean(ctx, c)    ((c) ? KNH_TRUE : KNH_FALSE)

#define _BOOL_ISTRUE(o)         (o == KNH_TRUE)
#define _BOOL_ISFALSE(o)        (o == KNH_FALSE)

/* ------------------------------------------------------------------------ */
/* @class Number Object knh_Number_t @Immutable */

typedef struct knh_Number_t {
	knh_hObject_t h;
	knh_nObject_t n;
} knh_Number_t;

/* ------------------------------------------------------------------------ */
/* @class Int Number  knh_Int_t @Immutable */
/* @ class IntX Number knh_Int_t @Immutable */

typedef struct knh_Int_t {
	knh_hObject_t h;
	knh_nObject_t n;
} knh_Int_t;

typedef knh_Int_t knh_IntX_t;

/* ------------------------------------------------------------------------ */
/* @class Float Number knh_Float_t @Immutable */
/* @ class FloatX Number knh_Float_t @Immutable */

typedef struct knh_Float_t {
	knh_hObject_t h;
	knh_nObject_t n;
} knh_Float_t;

typedef knh_Float_t knh_FloatX_t;

/* ------------------------------------------------------------------------ */
/* @class String Object knh_String_t @Immutable */
/* @ class StringX String knh_String_t @Immutable */
/* @flag String.TextSgm STRING:1 (%s)->h.flag 'is:set:*:*' */
/* @flag String.ASCII STRING:2 (%s)->h.flag 'is:set:*:*' */

typedef struct knh_String_t {
	knh_hObject_t h;
	knh_uchar_t *str;
	size_t size;
	struct knh_String_t *orign;
} knh_String_t;

typedef knh_String_t   knh_StringX_t;

/* ------------------------------------------------------------------------ */
/* @class Bytes Object knh_Bytes_t */
/* @flag Bytes.StackBuffer BYTES:1 (%s)->h.flag 'is:set:*:*' */

typedef struct knh_Bytes_t {
	knh_hObject_t h;
	knh_uchar_t *buf;
	size_t size;
	size_t capacity;
} knh_Bytes_t ;

/* ------------------------------------------------------------------------ */
/* @class Tuple2 Object knh_Tuple2_t @Immutable @Param2 */

typedef struct knh_Tuple2_t {
	knh_hObject_t h;
	knh_Object_t  *first;
	knh_Object_t  *second;
} knh_Tuple2_t;

/* ------------------------------------------------------------------------ */
/* @class Range Object knh_Range_t @Immutable */

typedef struct knh_Range_t {
	knh_hObject_t h;
	knh_Object_t  *start;
	knh_Object_t  *end;
} knh_Range_t;

/* ------------------------------------------------------------------------ */
/* @class Array Object knh_Array_t @Cyclic @Param1 */
/* @flag Array.Dim ARY:1 (%s)->h.flag 'is:set:*:*' */
/* @generics ArrayCmp int(Any1!,Any1!) Int! Any1! Any1! void */

#define KNH_ARRAY_INITSIZE  (KNH_FASTMALLOC_SIZE / sizeof(knh_Object_t*))

typedef struct knh_Array_t {
	knh_hObject_t h;
	struct knh_Object_t **list;
	size_t size;
	size_t capacity;
} knh_Array_t;

/* ------------------------------------------------------------------------ */
/* @class IArray Object knh_IArray_t @Cyclic @Param1 */
/* @flag IArray.Dim ARY:1 (%s)->h.flag 'is:set:*:*' */

#define KNH_IARRAY_INITSIZE  (KONOHA_SMALLPAGESIZE / sizeof(knh_int_t))

typedef struct knh_IArray_t {
	knh_hObject_t h;
	knh_int_t *ilist;
	size_t size;
	size_t capacity;
} knh_IArray_t;

/* ------------------------------------------------------------------------ */
/* @class FArray Object knh_FArray_t @Cyclic @Param1 */
/* @flag FArray.Dim ARY:1 (%s)->h.flag 'is:set:*:*' */

#define KNH_FARRAY_INITSIZE  (KONOHA_SMALLPAGESIZE / sizeof(knh_float_t))

typedef struct knh_FArray_t {
	knh_hObject_t h;
	knh_float_t *flist;
	size_t size;
	size_t capacity;
} knh_FArray_t;

/* ------------------------------------------------------------------------ */
/* @class Iterator Object knh_Iterator_struct @Param1 */

#ifdef _MSC_VER
typedef int   (KNH_CC_FASTCALL *knh_fitrnext)(Ctx *, knh_sfp_t *, int n);
#else
typedef ITRNEXT (*knh_fitrnext)(Ctx *, knh_sfp_t *, int n);
#endif

typedef void (*knh_ffree)(void *ptr);

typedef struct knh_Iterator {
	knh_fitrnext fnext;
	Object* source;
	size_t  pos;
	union {
		void*   ref;
		knh_code_t *pc; /* @see(Generator) */
	};
	knh_ffree freffree;
//	size_t count;
//	size_t start;
//	size_t end;
//	Object* prefetch;    /* @see(Generator) */
} knh_Iterator_struct;

/* ------------------------------------------------------------------------ */
/* @class DictMap Object knh_DictMap_t @Cyclic @Param1 */
/* @flag DictMap.IgnoreCase DICTM:1 (%s)->h.flag 'is:set:is:*' */
/* @class DictSet Object knh_DictSet_t @Cyclic @Param1 */
/* @flag DictSet.IgnoreCase DICTS:1 (%s)->h.flag 'is:set:is:*' */

#define KNH_DICT_INITSIZE (KNH_FASTMALLOC_SIZE/(sizeof(void*)*2))

typedef int (*knh_fbytescmp)(knh_bytes_t, knh_bytes_t);

typedef struct knh_dict_t {
	struct knh_String_t *key;
	union {
		Object *_unused;
		knh_uintptr_t _unused_int;
	};
} knh_dict_t;

typedef struct knh_dictmape_t {
	struct knh_String_t *key;
	Object *value;
} knh_dictmape_t;

typedef struct knh_DictMap_t {
	knh_hObject_t h;
	union {
		knh_dictmape_t *list;
		knh_dict_t *_list;  // To avoid stupid casting
	};
	size_t size;
	knh_fbytescmp fcmp;
} knh_DictMap_t;

/* ------------------------------------------------------------------------ */

typedef struct knh_dictsete_t {
	struct knh_String_t *key;
	knh_uintptr_t value;
} knh_dictsete_t;

typedef struct knh_DictSet_t {
	knh_hObject_t h;
	union {
		knh_dictsete_t *list;
		knh_dict_t *_list;  // To avoid stupid casting
	};
	size_t size;
	knh_fbytescmp fcmp;
} knh_DictSet_t;

/* ------------------------------------------------------------------------ */

typedef struct knh_hashentry_t {
	knh_hcode_t hcode;
	struct knh_hashentry_t *next;
	Object *key;
	union {
		Object *value;
		knh_uintptr_t uvalue;
	};
} knh_hashentry_t;

typedef knh_hashentry_t* (*knh_fhashentry_init)(Ctx *);
typedef void (*knh_fhashentry_traverse)(Ctx *, knh_hashentry_t*, knh_ftraverse);

typedef struct {
	size_t size;
	knh_fhashentry_init finit;
	knh_fhashentry_traverse ftraverse;
} knh_hash_op ;

/* ------------------------------------------------------------------------ */
/* @class HashMap Object knh_HashMap_struct @Param2 */
/* @class HashSet Object knh_HashSet_struct @Param1 */

#define KNH_HASH_INITSIZE 83
#define KNH_HASH_TABLESIZE  KONOHA_PAGESIZE
#define KNH_HASHENTRY(T,ESIZE,i)  (knh_hashentry_t*)&((T)[(ESIZE) * (i)])

typedef struct {
	knh_hashentry_t** array;
	size_t hmax;
	size_t capacity;
	size_t size;
	knh_hashentry_t*  unused_first;
	char** tables;
	size_t tables_capacity;
	size_t tables_size;
	char*  tables_first;
	char *DBG_name;
} knh_Hash_struct;

typedef knh_Hash_struct knh_HashMap_struct;
typedef knh_Hash_struct knh_HashSet_struct;

typedef struct {
	knh_hObject_t h;
	knh_Hash_struct *b;
	knh_fstruct_compareTo fcmp;
	knh_hash_op *hashop;
} knh_Hash_t ;

/* ------------------------------------------------------------------------ */
/* @class DictIdx Object knh_DictIdx_t @Private */

typedef struct knh_DictIdx_t {
	knh_hObject_t h;
	struct knh_Array_t *terms;
	struct knh_DictSet_t *termsDictSet;
	knh_intptr_t offset;
} knh_DictIdx_t;

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* @class Class Object knh_Class_t */
/* @flag Class.Release!Debug CF ctx->share->ClassTable[(%s)].cflag 'is:*:is:*' */
/* @flag Class.Immutable CF ctx->share->ClassTable[(%s)].cflag 'is:*:is:*' */
/* @flag Class.Cyclic CF ctx->share->ClassTable[(%s)].cflag 'is:set:*:*' */
/* @flag Class.MetaExtensible CF ctx->share->ClassTable[(%s)].cflag 'is:*:is:*' */
/* @flag Class.Private!Public CF ctx->share->ClassTable[(%s)].cflag 'is:*:is:*' */
/* @flag Class.Final CF ctx->share->ClassTable[(%s)].cflag 'is:*:is:*' */
/* @flag Class.Singleton CF ctx->share->ClassTable[(%s)].cflag 'is:*:*:*' */
/* @flag Class.Interface  CF ctx->share->ClassTable[(%s)].cflag 'is:*:is:*' */

typedef struct knh_Class_t {
	knh_hObject_t h;
	knh_class_t   cid;
	knh_type_t    type;
} knh_Class_t;

// dummy
#define KNH_FLAG_CF_PARAM1 0
#define KNH_FLAG_CF_PARAM2 0
#define KNH_FLAG_CF_PARAM4 0


/* class */

#define knh_Class_cid(c)     (knh_class_t)(c)->cid
#define KNH_FLAG_CF2OF(f)        (f)
#define knh_Class_isGenerics(cid)    (ctx->share->ClassTable[cid].p1 != CLASS_unknown)

/* ------------------------------------------------------------------------ */
/* @class ClassStruct Object knh_ClassStruct_t @Private */
/* @flag ClassStruct.Hidden CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */
/* @flag ClassStruct.AutoName CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */
/* @flag ClassStruct.NullAssinged CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */
/* @flag ClassStruct.Protected CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */
/* @flag ClassStruct.Getter CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */
/* @flag ClassStruct.Setter CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */
/* @flag ClassStruct.Key CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */

typedef struct knh_cfield_t {
	knh_flag_t    flag  ;
	knh_type_t    type  ;
	knh_fieldn_t  fn    ;
	Object        *value;
} knh_cfield_t ;

typedef struct knh_ClassStruct_t {
	knh_hObject_t h;
	knh_cfield_t* fields;
	/* knh_struct_t sid; knh_ushort_t fsize; */
	size_t fsize;
	knh_Array_t*  methods;
} knh_ClassStruct_t;

/* ------------------------------------------------------------------------ */
/* @class MethodField Object knh_MethodField_t @Private */

typedef struct {
	knh_type_t    type;
	knh_fieldn_t  fn;
} knh_mparam_t ;

#define KNH_METHODFIELD_2  2

typedef struct knh_MethodField_t {
	knh_hObject_t h;
	knh_type_t rtype; 	knh_ushort_t psize;
	union {
		knh_mparam_t* mparams;
		knh_mparam_t  p0;
	};
	knh_mparam_t p1;
} knh_MethodField_t;

/* ------------------------------------------------------------------------ */
/* @class Method Object knh_Method_struct */
/* @flag Method.Private!Public MF DP((Method*)%s)->flag 'is:set:is:*' */
/* @flag Method.Virtual!Final MF DP((Method*)%s)->flag 'is:set:is:*' */
/* @flag Method.Release!Debug MF DP((Method*)%s)->flag 'is:set:*:*' */
/* @flag Method.Const  MF DP((Method*)%s)->flag 'is:*:is:*' */
/* @flag Method.Static MF DP((Method*)%s)->flag 'is:*:is:*' */
/* @flag Method.NullBase MF DP((Method*)%s)->flag 'is:*:is:*' */
/* @flag Method.VarArgs MF DP((Method*)%s)->flag 'is:set:is:*' */
/* @flag Method.Generator MF DP((Method*)%s)->flag 'is:set:*:*' */
/* @flag Method.Aspect MF DP((Method*)%s)->flag 'is:set:is:*' */
/* @flag Method.ObjectCode MF DP((Method*)%s)->flag 'is:set:*:*' */
/* @flag Method.Generated MF DP((Method*)%s)->flag 'is:set:*:*' */

typedef knh_uint64_t   knh_proftime_t;

typedef struct {
	knh_flag_t     flag;  knh_class_t    cid;
	knh_methodn_t  mn;    knh_ushort_t   delta;
	struct knh_MethodField_t* mf;
	knh_fmethod       fproceed;
	void*             code;
#ifdef KNH_USING_KONOHA_PROF
	knh_uintptr_t     prof_count;  /*recode how many times called */
	knh_proftime_t    prof_time;   /*recode how long spending */
#endif
} knh_Method_struct;

/* ------------------------------------------------------------------------ */
/* @class Mapper Object knh_Mapper_struct */
/* @flag Mapper.Interface MMF DP((Mapper*)%s)->flag     'is:set:is:*' */
/* @flag Mapper.ICast MMF DP((Mapper*)%s)->flag  'is:*:is:*' */
/* @flag Mapper.Significant MMF DP((Mapper*)%s)->flag   'is:set:is:*' */
/* @flag Mapper.Final MMF DP((Mapper*)%s)->flag         'is:*:is:*' */
/* @flag Mapper.Synonym MMF DP((Mapper*)%s)->flag       'is:set:is:*' */
/* @flag Mapper.LossLess MMF DP((Mapper*)%s)->flag      'is:set:is:*' */
/* @flag Mapper.Total!Partial MMF DP((Mapper*)%s)->flag 'is:set:is:*' */
/* @flag Mapper.Const!Temporal MMF DP((Mapper*)%s)->flag 'is:set:is:*' */
/* @flag Mapper.Local MMF DP((Mapper*)%s)->flag 'is:set:is:*' */
/* @flag Mapper.Derived MMF DP((Mapper*)%s)->flag 'is:set:is:*' */
/* @flag Mapper.MapMap MMF:1 (%s)->h.flag              'is:set:*:*' */

typedef struct knh_Mapper {
	knh_flag_t   flag; knh_ushort_t size;
	knh_class_t  scid; knh_class_t  tcid;
	//knh_fmapper     fmap;
	union {
		Object*      mapdata;
		struct knh_Mapper_t *m1;
	};
	struct knh_Mapper_t *m2;
} knh_Mapper_struct;

/* ------------------------------------------------------------------------ */
/* @class ClassMap Object knh_ClassMap_struct @Private */
/* @flag ClassMap.Sorted CM:1 (%s)->h.flag 'is:set:*:*' */

typedef struct knh_ClassMap {
	struct knh_Mapper_t**   maplist;
	knh_ushort_t   size;
	knh_ushort_t   capacity;
} knh_ClassMap_struct ;

/* ------------------------------------------------------------------------ */
/* @class Closure Object knh_Closure_t @Param2 */
/* @flag Closure.StoredEnv CCF:1 (%s)->h.flag 'is:set:*:*' */

typedef struct knh_Closure_t {
	knh_hObject_t h;
	union {
		Object* base;
		struct knh_Closure_t *self;
	};
	struct knh_Method_t* mtd;
	union {
		knh_sfp_t *envsfp;
		size_t *hstacksize;
	};
} knh_Closure_t ;

#define KNH_INVOKE(ctx, lsfp) {\
		Closure* cc_ = sfp[0].cc;\
		int argc_ = (ctx->esp - sfp) - 1; \
		KNH_MOV(ctx, sfp[0].o, (cc_)->base);\
		KNH_SCALL(ctx, sfp, -1, (cc_)->mtd, argc_);\
	}\

/* ------------------------------------------------------------------------ */
/* @class AffineConv Object knh_AffineConv_t @Private */

#ifndef KONOHA_ON_LKM
  typedef float knh_affinefloat_t;
#else
  typedef int knh_affinefloat_t;
#endif

typedef struct knh_AffineConv_t {
	knh_hObject_t h;
	knh_affinefloat_t scale;
	knh_affinefloat_t shift;
} knh_AffineConv_t;

/* ------------------------------------------------------------------------ */
/* @class Regex Object knh_Regex_t @Immutable */

typedef struct {
	knh_hObject_t h;
	knh_regex_t *reg;
	knh_regex_drvapi_t *df;
	struct knh_String_t *pattern;
} knh_Regex_t;

/* ------------------------------------------------------------------------ */
/* @class BytesConv Object knh_BytesConv_t @Private */

//struct knh_BytesConv_t;
//typedef size_t (*knh_fbyteconv)(Ctx *ctx, struct knh_BytesConv_t *o, knh_bytes_t t, struct knh_Bytes_t *ba);
//typedef void   (*knh_fbyteconvfree)(Ctx *ctx, struct knh_BytesConv_t *);

#ifdef KNH_USING_ICONV
	#include<iconv.h>
#else
typedef knh_intptr_t iconv_t;
#endif

typedef struct knh_BytesConv_t {
	knh_hObject_t h;
	knh_fbyteconv      fbconv;
	knh_fbyteconvfree  fbconvfree;
	union {
		iconv_t iconv_d;
		void *convp;
	};
} knh_BytesConv_t;

/* ------------------------------------------------------------------------ */
/* @class ClassSpec Object knh_ClassSpec_struct @Private */

#define KNH_CLASSSPEC_FMT    "%s{%s}"
struct  knh_ClassSpec_t;

typedef int (*knh_fichk)(struct knh_ClassSpec_t *, knh_int_t v);
typedef int (*knh_ficmp)(struct knh_ClassSpec_t *, knh_int_t v1, knh_int_t v2);

typedef int (*knh_ffchk)(struct knh_ClassSpec_t *, knh_float_t v);
typedef int (*knh_ffcmp)(struct knh_ClassSpec_t *, knh_float_t v1, knh_float_t v2);

typedef knh_String_t *(*knh_fsnew)(Ctx *, knh_class_t cid, knh_bytes_t, struct knh_String_t *, int *);
typedef int (*knh_fscmp)(struct knh_ClassSpec_t *, knh_bytes_t, knh_bytes_t);

typedef struct {
	knh_flag_t  flag;
	knh_class_t ucid;
	knh_class_t ubcid;
	knh_String_t* urn;
	knh_String_t* tag;
	struct knh_Int_t    *ivalue;
	struct knh_Float_t  *fvalue;
	struct knh_String_t *svalue;

	// int
	union {
		knh_int_t imin;
		knh_uint_t umin;
	};
	union {
		knh_int_t imax;
		knh_uint_t umax;
	};
	knh_fichk fichk;
	knh_ficmp ficmp;

	// float
	knh_float_t fmin;
	knh_float_t fmax;
	knh_float_t fstep;
	knh_ffchk   ffchk;
	knh_ffcmp   ffcmp;

	// String
	size_t bytelen;
	size_t charlen;
	Object* pattern;
	struct knh_DictIdx_t* vocabDictIdx;
	struct knh_BytesConv_t *bconv;
	knh_fsnew    fsnew;
	knh_fscmp    fscmp;
} knh_ClassSpec_struct;

typedef struct knh_ClassSpec_t* (*knh_fspec)(Ctx *ctx, knh_bytes_t urn);

/* ------------------------------------------------------------------------ */
/* InputStream, OutputStream */

/* ------------------------------------------------------------------------ */
/* @class InputStream Object knh_InputStream_struct */
/* @flag InputStream.FILE IN:1 (%s)->h.flag 'is:set:*:*' */

typedef struct knh_InputStream {
	union {
		knh_io_t fd;
		FILE *fp;
	};
	knh_iodrv_t *driver;
	union {
		struct knh_Bytes_t *ba;
		struct knh_String_t *str;
	};
	char *buf;
	size_t bufpos;
	size_t bufend;
	size_t bufsiz;
	knh_String_t *enc;
	struct knh_BytesConv_t* bconv;
	knh_String_t*  urn;
	knh_fileid_t  fileid;
	knh_ushort_t  prev;
	size_t line;
	size_t size;
} knh_InputStream_struct;

/* ------------------------------------------------------------------------ */
/* @class OutputStream Object knh_OutputStream_struct */
/* @flag OutputStream.BOL OUT:1 (%s)->h.flag 'is:set:*:*' */
/* @flag OutputStream.AutoFlush OUT:2 (%s)->h.flag 'is:set:is:set' */
/* @flag OutputStream.StoringBuffer OUT:3 (%s)->h.flag 'is:set:is:set' */

typedef struct {
	knh_io_t fd;
	knh_iodrv_t *driver;
	knh_Bytes_t* ba;
	knh_String_t *enc;
	struct knh_BytesConv_t* bconv;
	knh_String_t*  urn;
	size_t size;
	size_t line;
	knh_String_t*  NEWLINE;
	knh_String_t*  TAB;
	knh_short_t indent;
	knh_flag_t flag;  /*unused */
} knh_OutputStream_struct;

/* ------------------------------------------------------------------------ */
/* @class Socket Object knh_Socket_struct */

typedef struct {
	knh_intptr_t sd;
	knh_intptr_t port;
	struct knh_String_t *urn;
	struct knh_InputStream_t  *in;
	struct knh_OutputStream_t *out;
} knh_Socket_struct;

/* ======================================================================== */
/* @class Connection Object knh_Connection_struct */
/* @class ResultSet Object knh_ResultSet_struct */

typedef struct knh_Connection {
	knh_db_t           *conn;
	knh_db_drvapi_t    *df;
	knh_String_t       *urn;
} knh_Connection_struct;

/* ------------------------------------------------------------------------ */

#define knh_ResultSet_CTYPE__null    0
#define knh_ResultSet_CTYPE__integer 1
#define knh_ResultSet_CTYPE__float   2
#define knh_ResultSet_CTYPE__text    3  /* UTF-8*/
#define knh_ResultSet_CTYPE__bytes   4
#define knh_ResultSet_CTYPE__Object  5

typedef struct {
	knh_type_t type;
	knh_ushort_t ctype;
	knh_String_t *name;
	size_t start;
	size_t len;
	int dbtype;
} knh_dbschema_t;

typedef struct knh_ResultSet {
	struct knh_Connection_t *conn;
	knh_dbcur_t             *dbcur;
	knh_fdbcurfree           dbcur_free;  /* necessary if conn is closed before */
	knh_String_t            *tableName;
	knh_class_t              tcid;
	knh_ushort_t             column_size;
	knh_dbschema_t          *column;
	knh_Bytes_t             *databuf;
	size_t                   count;
} knh_ResultSet_struct;

/* ------------------------------------------------------------------------ */
/* @class Exception Object knh_Exception_struct */
/* @flag Exception.Fatal EF DP((Exception*)%s)->flag 'is:*:is:*' */
/* @flag Exception.Logging EF DP((Exception*)%s)->flag 'is:*:is:*' */
/* @flag Exception.Generated EF DP((Exception*)%s)->flag 'is:*:is:*' */
/* @flag Exception.Caught EF DP((Exception*)%s)->flag 'is:set:*:*' */

/* @expt Exception!! - */
/* @expt Fatal!! - */
/* @expt OutOfMemory!! Fatal!! */
/* @expt Security!! - */
/* @expt Null!! - */
/* @expt OutOfIndex!! - */
/* @expt IO!! - */
/* @expt Script!! - */
/* @expt Syntax!! Script!! */
/* @expt Type!! Script!! */

typedef struct knh_Exception {
	knh_flag_t flag;
	knh_expt_t eid;
	knh_String_t* msg;
	Object* bag;
	knh_Array_t* traces;
	char*     file;
	size_t    line;
} knh_Exception_struct;

/* ------------------------------------------------------------------------ */
/* @class ExceptionHandler Object knh_ExceptionHandler_struct @Private */
/* @flag ExceptionHandler.Jumpable   EHF:1 (%s)->h.flag 'is:set:*:*' */
/* @flag ExceptionHandler.Catching EHF:2 (%s)->h.flag 'is:set:*:*' */

typedef struct knh_ExceptionHandler {
	jmp_buf jmpbuf;
	knh_sfp_t *esp;
	knh_code_t *pc;
	struct knh_Exception_t* caught;
} knh_ExceptionHandler_struct;

/* ------------------------------------------------------------------------ */
/* @class Script Object knh_Script_t @Private */

#define KNH_SCRIPT_FIELDSIZE   128

typedef struct knh_Script_t {
	knh_hObject_t h;
	Object **fields;
} knh_Script_t ;

/* ------------------------------------------------------------------------ */
/* @class NameSpace Object knh_NameSpace_struct @Private */

typedef struct knh_NameSpace {
	knh_String_t*           nsname;
	struct knh_Script_t*    script;
	knh_Array_t*            importedNameSpaces;
	struct knh_DictSet_t*   name2cidDictSet;
	struct knh_DictSet_t*   func2cidDictSet;
	struct knh_DictMap_t*   lconstDictMap;
	struct knh_DictMap_t*   tag2urnDictMap;
//	void                   *dlhdr;
//	knh_pkgmeta_t          *pkgmeta;
} knh_NameSpace_struct;

/* ------------------------------------------------------------------------ */
/* @class System Object knh_System_struct @Singleton */

typedef struct knh_System {
	knh_uintptr_t sysid;
	size_t     ctxcount;

	struct knh_DictMap_t*      props;
	struct knh_InputStream_t*  in;
	struct knh_OutputStream_t* out;
	struct knh_OutputStream_t* err;
	struct knh_String_t*       enc;
	knh_String_t              *homeDir;

	struct knh_DictIdx_t *FileNameDictIdx;
	struct knh_DictIdx_t *FieldNameDictIdx;
	struct knh_HashMap_t* MethodFieldHashMap;

	struct knh_DictSet_t *ClassNameDictSet;
	struct knh_DictSet_t *ExptNameDictSet;

	struct knh_DictMap_t* NameSpaceTableDictMap;
	struct knh_DictMap_t* URNAliasDictMap;
	struct knh_DictSet_t *DriversTableDictSet;
	struct knh_DictSet_t *SpecFuncDictSet;
	struct knh_Array_t   *UsingResources;

	struct knh_DictMap_t *sysnsDictMap_UNUSED;
	struct knh_DictSet_t *funcDictSet_UNUSED;

} knh_System_struct;

/* ------------------------------------------------------------------------ */
/* @class Context Object knh_Context_t */
/* @ flag Context.System CTXF ((Context*)%s)->flag 'is:set:*:*' */
/* @flag Context.Strict CTXF ((Context*)%s)->flag 'is:set:is:set' */
/* @flag Context.Debug  CTXF ((Context*)%s)->flag 'is:set:is:set' */
/* @flag Context.Verbose CTXF ((Context*)%s)->flag 'is:set:is:set' */

/* @flag Context.Trusted CTXF ((Context*)%s)->flag 'is:set:is:*' */
/* @flag Context.Interactive CTXF ((Context*)%s)->flag 'is:set:is:*' */
/* @flag Context.Compiling CTXF ((Context*)%s)->flag 'is:set:*:*' */

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* konohac.h */

/* ------------------------------------------------------------------------ */

typedef knh_ushort_t   knh_token_t;
typedef knh_ushort_t   knh_stmt_t;
#define knh_perror0_t   int

/* ------------------------------------------------------------------------ */
/* @class Token Object knh_Token_struct */
/* @flag Token.BOL TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.TailWildCard TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.TopDot TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.Getter TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.Setter TKF SP(%s)->flag 'is:set:*:*' */

/* @flag Token.ExceptionType TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.NotNullType TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.IteratorType TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.ArrayType TKF SP(%s)->flag 'is:set:*:*' */
/* @flag Token.NullableType TKF SP(%s)->flag 'is:set:*:*' */

#define knh_Token_isUnsafeType(o)  knh_Token_isTailWildCard(o)
#define knh_Token_setUnsafeType(o, b) knh_Token_setTailWildCard(o, b)

#define knh_Token_isPNAME(o)  knh_Token_isTailWildCard(o)
#define knh_Token_setPNAME(o, b) knh_Token_setTailWildCard(o, b)

#define knh_Token_isSUPER(o)      knh_Token_isTailWildCard(o)
#define knh_Token_setSUPER(o, b)  knh_Token_setTailWildCard(o, b)

/* ------------------------------------------------------------------------ */

#define knh_Token_isTyped(o)    (TT_CONST <= SP(o)->tt && SP(o)->tt <=TT_NOP)

typedef struct knh_Token {
	knh_type_t   type;
	union {
		knh_token_t   tt_next;
		knh_short_t   index;   /* STACK, FIELD, GLOBAL, SYSVAL, DEFVAL */
		knh_methodn_t mn;
		knh_token_t   tt_op;
		knh_fieldn_t  fn;
		knh_class_t   cid;
	};
	union {
		Object* data;
		struct knh_Array_t*  list;
		struct knh_String_t* text;
		struct knh_Token_t* token;
		struct knh_Method_t* mtd;
		struct knh_Int_t *num;
	};
} knh_Token_struct;

typedef struct knh_tokens_t {
	struct knh_Token_t** ts;
	int meta;
	int c;
	int e;
} knh_tokens_t;

//#define TT_RAW   TT_CONST

/* ------------------------------------------------------------------------ */
/* @class Stmt Object knh_Stmt_struct */
/* @flag Stmt.Adposition STMTF SP(%s)->flag 'is:set:*:*' */
/* @flag Stmt.NonNewLine STMTF SP(%s)->flag 'is:set:*:*' */
/* @flag Stmt.Literal    STMTF SP(%s)->flag 'is:*:*:*' */
/* @flag Stmt.Typed STMTF SP(%s)->flag 'is:set:*:*' */
/* @flag Stmt.Memo1 STMTF SP(%s)->flag 'is:set:*:*' */

/* MAPCAST */
/* DEBUG {} */
#define knh_Stmt_isDEBUG(s)       knh_Stmt_isMemo1(s)
#define knh_Stmt_setDEBUG(s,b)    knh_Stmt_setMemo1(s,b)

#define knh_Stmt_isNNCAST(s)       knh_Stmt_isMemo1(s)
#define knh_Stmt_setNNCAST(s,b)    knh_Stmt_setMemo1(s,b)
#define knh_Stmt_isMAPNEXT(s)      knh_Stmt_isMemo1(s)
#define knh_Stmt_setMAPNEXT(s,b)   knh_Stmt_setMemo1(s,b)
#define knh_Stmt_isVOID(s)         knh_Stmt_isMemo1(s)
#define knh_Stmt_setVOID(s,b)      knh_Stmt_setMemo1(s,b)
#define knh_Stmt_isTHISSUPER(s)    knh_Stmt_isMemo1(s)
#define knh_Stmt_setTHISSUPER(s,b) knh_Stmt_setMemo1(s,b)

/* ------------------------------------------------------------------------ */

typedef struct knh_Stmt {
	knh_type_t   type;
	knh_short_t  line_end;
	knh_ushort_t size;
	knh_ushort_t capacity;
	union {
		Object** terms;
		struct knh_Token_t** tokens;
		struct knh_Stmt_t** stmts;
	};
	union {
		struct knh_DictMap_t* metaDictMap;
		struct knh_String_t*  errMsg;
	};
	struct knh_Stmt_t* next;
} knh_Stmt_struct;

/* ------------------------------------------------------------------------ */

#define Term         Any
#define IS_Term(o)   (IS_Token((Object*)o)||IS_Stmt((Object*)o))

#define KNH_LOCALSIZE 64

/* ------------------------------------------------------------------------ */
/* KLRCode */
/* ------------------------------------------------------------------------ */

typedef unsigned char          knh_opcode_t;
typedef int                    knh_labelid_t;
typedef knh_short_t            knh_sfi_t;
typedef knh_short_t            knh_sfe_t;

typedef struct {
	knh_sfi_t i;
	size_t    n;
} knh_sfx_t;

typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/
	knh_opcode_t opcode;
#ifdef KNH_USING_THREADEDCODE
	void *jumpaddr;
#endif/*KNH_USING_THREADEDCODE*/
	union {
		knh_labelid_t a1;  /* labelid */
		knh_code_t *jumppc;
	};
	void *nextaddr;
} knh_kode_t;

#define KNH_OPCODE(pc)          ((knh_kode_t*)pc)->opcode

#define KNH_ASSERT_OPCODE(c) \
	if(c > OPCODE_NOP) {\
		DBG_P("Invalid opcode=%d", (int)c); \
		KNH_ASSERT(c <= OPCODE_NOP); \
	}\

/* ------------------------------------------------------------------------ */
/* @class Asm Object knh_Asm_struct @Private */
/* @flag Asm.Cancelled  CPF DP(%s)->flag 'is:set:*:*' */
/* @flag Asm.PROCEED    CPF DP(%s)->flag 'is:set:*:*' */
/* @flag Asm.YEILD      CPF DP(%s)->flag 'is:set:*:*' */

#ifndef KONOHA_LOCALSIZE
#define KONOHA_LOCALSIZE 128
#endif

#define KNH_ASM_REGMAX 32

typedef struct {
	knh_short_t level;
	knh_short_t varidx;
	struct knh_Stmt_t *stmt;
} knh_asmreg_t ;

typedef struct {
	int offset;
	struct knh_Token_t *tklabel;
} knh_labeltbl_t ;

typedef knh_uint64_t  knh_rtti_t;

typedef struct knh_Asm {
	knh_flag_t             flag;
	knh_class_t            this_cid;
	struct knh_NameSpace_t *ns;
	struct knh_Method_t    *mtd;
	knh_type_t             rtype;
	knh_ushort_t vars_size;
	knh_cfield_t* vars;
	knh_rtti_t nnrtti0;
	knh_rtti_t nnrtti;
	int                     level; /* 0.3 */
	int stack;
	int globalidx;
	int llstep;

	knh_asmreg_t *regs;
	knh_ushort_t regs_size;
	knh_ushort_t regs_usedsize;

	struct knh_DictSet_t* name2labelIdDictSet;
	size_t labelmax;
	size_t labelcapacity;
	knh_labeltbl_t *labels;
	knh_Array_t*          lstacks;
	struct knh_Stmt_t*    finallyStmt;

	knh_fileid_t           fileid;
	knh_sline_t            line;
	struct knh_Bytes_t* elf;
	struct knh_Bytes_t* dwarf;
	knh_kode_t         *prev_op;

	void *dlhdr;
	struct knh_Array_t *constPools;
	struct knh_Array_t *exportsMethods;
} knh_Asm_struct;

/* ------------------------------------------------------------------------ */
/* @class KLRCode Object knh_KLRCode_struct */

typedef struct {
	knh_ushort_t offset;
	knh_ushort_t line;
} knh_dwarf_t;

typedef struct knh_KLRCode {
	knh_code_t* code;
	size_t size;
	knh_fileid_t fileid;
//	knh_nsid_t nsid;
	knh_dwarf_t* dwarf;
	size_t dsize;
} knh_KLRCode_struct;

/* ======================================================================== */

#ifdef __cplusplus
}
#endif

#endif /*CLASS_KONOHA_H_*/

