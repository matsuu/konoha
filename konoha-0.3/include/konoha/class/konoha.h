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
/* @flag Object.MetaData OF (%s)->h.flag 'has:set:has:*' */
/* @flag Object.Synchronized OF (%s)->h.flag 'is:*:is:*' */
/* @flag Object.Modified OF (%s)->h.flag 'is:set:is:set' */
/* @flag Object.GCMarked OF (%s)->h.flag 'is:set:is:set' */
/* @flag Object.Formatted OF (%s)->h.flag 'is:set:is:set' */
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

/* ------------------------------------------------------------------------ */

#define IS_IMM(o) (!knh_Object_isImmutable(o))

/* ------------------------------------------------------------------------ */
/* @class Any Object knh_Any_t @Cyclic */
/* @class This Any knh_Any_t @Cyclic  @Private */
/* @class Any0 Any knh_Any_t @Cyclic  @Private */
/* @class Any1 Any knh_Any_t @Cyclic  @Private */
/* @class Any2 Any knh_Any_t @Cyclic  @Private */
/* @class Any3 Any knh_Any_t @Cyclic  @Private */

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

/* ------------------------------------------------------------------------ */
/* @class Nue Object knh_Nue_t @Immutable @Private */
/* @flag Nue.GCHook NUE:1 (%s)->h.flag 'is:set:*:*' */

typedef struct knh_Nue_t {
	knh_hObject_t h;
	knh_uchar_t *str;
	size_t size;
	struct knh_String_t *orign;
} knh_Nue_t;

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

/* ------------------------------------------------------------------------ */
/* @class Number Object knh_Number_t @Immutable */

typedef struct knh_Number_t {
	knh_hObject_t h;
	knh_nObject_t n;
} knh_Number_t;

/* ------------------------------------------------------------------------ */
/* @class Int Number  knh_Int_t @Immutable */
/* @class IntX Number knh_Int_t @Immutable */

typedef struct knh_Int_t {
	knh_hObject_t h;
	knh_nObject_t n;
} knh_Int_t;

typedef knh_Int_t knh_IntX_t;

/* ------------------------------------------------------------------------ */
/* @class Float Number knh_Float_t @Immutable */
/* @class FloatX Number knh_Float_t @Immutable */

typedef struct knh_Float_t {
	knh_hObject_t h;
	knh_nObject_t n;
} knh_Float_t;

typedef knh_Float_t knh_FloatX_t;

/* ------------------------------------------------------------------------ */
/* @class String Object knh_String_t @Immutable */
/* @class StringX String knh_String_t @Immutable */
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

typedef struct knh_Iterator {
	knh_fitrnext fnext;
	Object* source;
	size_t  pos;
	union {
		void*   ref;
		knh_code_t *pc; /* @see(Generator) */
	};
	size_t count;
	size_t start;
	size_t end;
	Object* prefetch; /* @see(Generator) */
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
/* @ flag Class.System CF ctx->share->ClassTable[(%s)].cflag 'is:*:is:*' */
/* @flag Class.NullObject CF ctx->share->ClassTable[(%s)].cflag 'is:*:*:*' */
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
/* @flag Method.Const  MF DP((Method*)%s)->flag 'is:*:is:*' */
/* @flag Method.Static MF DP((Method*)%s)->flag 'is:*:is:*' */
/* @flag Method.NullBase MF DP((Method*)%s)->flag 'is:*:is:*' */
/* @flag Method.VarArgs MF DP((Method*)%s)->flag 'is:set:is:*' */
/* @flag Method.Generator MF DP((Method*)%s)->flag 'is:set:*:*' */
/* @flag Method.Aspect MF DP((Method*)%s)->flag 'is:set:is:*' */
/* @flag Method.ObjectCode MF DP((Method*)%s)->flag 'is:set:*:*' */
/* @flag Method.Generated MF DP((Method*)%s)->flag 'is:set:*:*' */

typedef struct knh_Method {
	knh_flag_t     flag;  knh_class_t    cid;
	knh_methodn_t  mn;    knh_ushort_t   delta;
	struct knh_MethodField_t* mf;
	knh_fmethod       fproceed;
	void*             code;
} knh_Method_struct;

/* ------------------------------------------------------------------------ */
/* @class Mapper Object knh_Mapper_struct */
/* @flag Mapper.Interface MMF DP((Mapper*)%s)->flag     'is:set:is:*' */
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
/* @class Closure Object knh_Closure_struct @Param2 */
/* @flag Closure.SharedStack CCF:1 (%s)->h.flag 'is:set:*:*' */
/* @flag Closure.CopiedStack CCF:2 (%s)->h.flag 'is:set:*:*' */

typedef struct knh_Closure {
	Object* base;
	struct knh_Method_t* mtd;
	size_t stacksize;
	knh_sfp_t *stack;
} knh_Closure_struct ;

/* ------------------------------------------------------------------------ */
/* @class AffineConv Object knh_AffineConv_t @Private */

typedef float knh_affinefloat_t;

typedef struct knh_AffineConv_t {
	knh_hObject_t h;
	knh_affinefloat_t scale;
	knh_affinefloat_t shift;
} knh_AffineConv_t;

/* ------------------------------------------------------------------------ */
/* IntSpec, FloatSpec, StringSpec */

#define KNH_CLASSSPEC_FMT    "%s{%s}"

typedef struct {
	knh_flag_t  flag;
	knh_class_t cid;
	knh_String_t* urn;
	knh_String_t* tag;
	Object* defvalue;
} knh_hClassSpec_struct;

typedef struct knh_ClassSpec_t {
	knh_hObject_t h;
	knh_hClassSpec_struct *b;
} knh_ClassSpec_t ;

#define ClassSpec        knh_ClassSpec_t
typedef knh_ClassSpec_t* (*knh_fspec)(Ctx *ctx, knh_class_t bcid, char *extra);

/* ------------------------------------------------------------------------ */
/* @class IntUnit Object knh_IntUnit_struct @Private */
/* @flag IntUnit.Unsigned UF DP((IntUnit*)%s)->spec.flag 'is:*:is:*' */

struct  knh_IntUnit_t;
typedef knh_bool_t (*knh_fenumchk)(struct knh_IntUnit_t *, knh_int_t v);
typedef int (*knh_fenumcmp)(struct knh_IntUnit_t *, knh_int_t v1, knh_int_t v2);
typedef void (*knh_fenumfmt)(struct knh_IntUnit_t *, char *buf, size_t bufsiz, knh_int_t v);

typedef struct knh_IntUnit {
	knh_hClassSpec_struct spec;
	knh_fenumchk fchk;
	knh_fenumcmp fcmp;
	knh_fenumfmt ffmt;
	knh_int_t min;
	knh_int_t max;
	knh_int_t step;
} knh_IntUnit_struct;

/* ------------------------------------------------------------------------ */
/* @class FloatUnit Object knh_FloatUnit_struct @Private */

struct knh_FloatUnit_t;
typedef knh_bool_t (*knh_funitchk)(struct knh_FloatUnit_t *, knh_float_t v);
typedef int (*knh_funitcmp)(struct knh_FloatUnit_t *, knh_float_t v1, knh_float_t v2);
typedef void (*knh_funitfmt)(struct knh_FloatUnit_t *, char *buf, size_t bufsiz, knh_float_t v);

typedef struct knh_FloatUnit {
	knh_hClassSpec_struct spec;
	knh_funitchk fchk;
	knh_funitcmp fcmp;
	knh_funitfmt ffmt;
	knh_float_t min;
	knh_float_t max;
	knh_float_t step;
	char* FMT;
} knh_FloatUnit_struct;

/* ------------------------------------------------------------------------ */
/* @class Regex Object knh_Regex_t @Immutable */

typedef struct {
	knh_hObject_t h;
	knh_regex_t *reg;
	knh_regex_drvapi_t *df;
	struct knh_String_t *pattern;
} knh_Regex_t;

/* ------------------------------------------------------------------------ */
/* @class BytesConv Object knh_BytesConv_struct @Private */

#ifdef KNH_USING_ICONV
	#include<iconv.h>
#endif

typedef struct knh_BytesConv {
	struct knh_String_t *name;
	knh_fbcnv fbconv;
#ifdef KNH_USING_ICONV
	iconv_t iconv_d;
#endif
} knh_BytesConv_struct;

/* ------------------------------------------------------------------------ */
/* @class StringUnit Object knh_StringUnit_struct @Private */

struct knh_StringUnit_t;
typedef knh_String_t *(*knh_fvcabnew)(Ctx *, knh_class_t cid, knh_bytes_t, struct knh_String_t *);
typedef int (*knh_fvcabcmp)(struct knh_StringUnit_t *, knh_bytes_t, knh_bytes_t);

typedef struct knh_StringUnit {
	knh_hClassSpec_struct spec;
	knh_fvcabnew fnew;
	knh_fvcabcmp fcmp;
	knh_fbcnv     fbconv;
	struct knh_BytesConv_t *bconv;
	knh_ushort_t bytelen;
	knh_ushort_t charlen;
	Object* pattern;
	struct knh_DictIdx_t* vocabDictIdx;
} knh_StringUnit_struct;

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
	knh_String_t* message;
	Object* bag;
	knh_Array_t* traces;
	char* file;
	int line;
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
/* @flag Context.Release!Debug CTXF ((Context*)%s)->flag 'is:set:is:set' */
/* @flag Context.Admin CTXF ((Context*)%s)->flag 'is:set:*:*' */
/* @flag Context.Strict CTXF ((Context*)%s)->flag 'is:set:*:*' */
/* @flag Context.Compiling CTXF ((Context*)%s)->flag 'is:set:*:*' */
/* @flag Context.Verbose CTXF ((Context*)%s)->flag 'is:set:is:set' */
/* @flag Context.Verbose2 CTXF ((Context*)%s)->flag 'is:set:is:set' */
/* @flag Context.Interactive CTXF ((Context*)%s)->flag 'is:set:*:*' */

///* ------------------------------------------------------------------------ */
///* class Mutex Object knh_ */
//


/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* include generated header file */

#ifdef __cplusplus
}
#endif

#endif /*CLASS_KONOHA_H_*/

