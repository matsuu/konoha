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
#include<konoha/konoha_api.h>

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

typedef knh_Object_t* (*knh_fparser)(Ctx *, knh_class_t cid, knh_bytes_t p);

typedef struct {
	int  type;
	char *name;
	knh_fparser parser;
} knh_parser_drvapi_t;

/* ------------------------------------------------------------------------ */
/* @class Any Object knh_Any_t @Cyclic */
/* @class This Any knh_Any_t @Cyclic  */
/* @class Any1 Any knh_Any_t @Cyclic  */
/* @class Any2 Any knh_Any_t @Cyclic  */

typedef void (*f_wrapper_free)(void *);

typedef struct {
	knh_hObject_t h;
	void *wrapped;
	f_wrapper_free w_free;
} knh_Any_t ;

typedef knh_Any_t knh_This_t;
typedef knh_Any_t knh_Any1_t;
typedef knh_Any_t knh_Any2_t;

/* ------------------------------------------------------------------------ */
/* @class Nue Object knh_Nue_t @Immutable */
/* @flag Nue.GCHook NUE:1 (%s)->h.flag 'is:set:*:*' */

typedef struct knh_Nue_t {
	knh_hObject_t h;
	knh_uchar_t *str;
	size_t size;
	struct knh_String_t *orign;
} knh_Nue_t;

/* ------------------------------------------------------------------------ */
/* @class Boolean Object knh_Boolean_t @Immutable */

typedef struct knh_Boolean_t {
	knh_hObject_t h;
	knh_bool_t value;
} knh_Boolean_t;

/* ------------------------------------------------------------------------ */
/* @class Number Object knh_Number_t @Immutable */

typedef struct knh_Number_t {
	knh_hObject_t h;
	knh_int_t   ivalue;
	knh_float_t value;
} knh_Number_t;

/* ------------------------------------------------------------------------ */
/* @class Int Number  knh_Int_t @Immutable */
/* @class IntX Number knh_Int_t @Immutable */

typedef struct knh_Int_t {
	knh_hObject_t h;
	knh_int_t value;
} knh_Int_t;

typedef knh_Int_t knh_IntX_t;

/* ------------------------------------------------------------------------ */
/* @class Int64  Number knh_Int64_t @Immutable */
/* @class Int64X Number knh_Int64_t @Immutable */

typedef struct knh_Int64_t {
	knh_hObject_t h;
	knh_int_t   ivalue;
	knh_int64_t value;
} knh_Int64_t;

typedef knh_Int64_t knh_Int64X_t;

/* ------------------------------------------------------------------------ */
/* @class Float Number knh_Float_t @Immutable */
/* @class FloatX Number knh_Float_t @Immutable */

typedef struct knh_Float_t {
	knh_hObject_t h;
	knh_int_t   ivalue;
	knh_float_t value;
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

typedef struct knh_Array_t {
	knh_hObject_t h;
	struct knh_Object_t **list;
	size_t size;
//	size_t capacity;
} knh_Array_t;

/* ------------------------------------------------------------------------ */
/* @class Iterator Object knh_Iterator_struct @Param1 */

struct knh_Iterator_t;
typedef Object* (*f_next)(Ctx *, struct knh_Iterator_t *);

typedef struct knh_Iterator {
	f_next fnext;
	Object* source;
	size_t pos;
	void* ref;
	size_t count;
	size_t start;
	size_t end;
} knh_Iterator_struct;

/* ------------------------------------------------------------------------ */
/* @class DictMap2 Object knh_DictMap2_t @Cyclic */
/* @class DictSet2 Object knh_DictSet2_t @Cyclic */

typedef struct {
	union {
		Object *key;
		struct knh_String_t *name;
	};
	union {
		Object *value;
		knh_uint_t uvalue;
	};
} knh_dictentry_t;

typedef struct knh_DictMap2_t {
	knh_hObject_t h;
	struct dictentry *list;
	size_t size;
} knh_DictMap2_t;

#define knh_DictSet2_t    knh_DictMap2_t

/* ------------------------------------------------------------------------ */
/* @class DictMap Object knh_DictMap_struct */

typedef struct knh_dictmape_t {
	struct knh_String_t *key;
	Object *value;
} knh_dictmape_t;

typedef struct knh_DictMap {
	size_t size;
	size_t capacity;
	knh_dictmape_t* list;
	size_t sorted;
} knh_DictMap_struct;

/* ------------------------------------------------------------------------ */
/* @class DictSet Object knh_DictSet_struct */

typedef struct knh_dictsete_t {
	struct knh_String_t *key;
	knh_uint_t  value;
} knh_dictsete_t;

typedef struct knh_DictSet {
	size_t size;
	size_t capacity;
	knh_dictsete_t* list;
	size_t sorted;
} knh_DictSet_struct;

/* ------------------------------------------------------------------------ */
/* @class HashMap Object knh_HashMap_struct @Param2 */

typedef struct knh_hashmapentry_t {
	knh_hcode_t hcode;
	Object *key;
	Object *value;
	struct knh_hashmapentry_t *next;
} knh_hashmapentry_t ;

typedef struct knh_HashMap {
	size_t capacity;
	size_t size;
	knh_hashmapentry_t** array;
	f_compareTo fcompareTo;
	size_t table_size;
	knh_hashmapentry_t*  unused;
	knh_hashmapentry_t*  table;
	knh_hashmapentry_t** ex_tables;
	size_t               ex_capacity;
	size_t               ex_size;
	char *DBG_name;
} knh_HashMap_struct;

/* ------------------------------------------------------------------------ */
/* @class HashSet Object knh_HashSet_struct @Param1 */

typedef struct knh_hashsetentry_t {
	knh_hcode_t hcode;
	Object *key;
	knh_uint_t value;
	struct knh_hashsetentry_t *next;
} knh_hashsetentry_t ;

typedef struct knh_HashSet {
	size_t capacity;
	size_t size;
	knh_hashsetentry_t** array;
	f_compareTo fcompareTo;
	size_t table_size;
	knh_hashsetentry_t*  unused;
	knh_hashsetentry_t*  table;
	knh_hashsetentry_t** ex_tables;
	size_t               ex_capacity;
	size_t               ex_size;
	char *DBG_name;
} knh_HashSet_struct;

/* ------------------------------------------------------------------------ */
/* @class LRUHashMap Object knh_LRUHashMap_struct */

typedef struct knh_lruentry_t {
	knh_hcode_t hcode;
	Object *key;
	Object *value;
	struct knh_lruentry_t  *value_next;
	struct knh_lruentry_t  *prev;
	struct knh_lruentry_t  *next;
} knh_lruentry_t ;

typedef struct knh_LRUHashMap {
	size_t table_size;
	knh_lruentry_t*  table;
	knh_lruentry_t*  unused;
	knh_lruentry_t** array;
	knh_lruentry_t *first;
	knh_lruentry_t *last;
	char *dbg_name;
	size_t hitc;
	size_t missc;
} knh_LRUHashMap_struct;

///* ------------------------------------------------------------------------ */
///* class Map Object knh_Map */
//
//struct knh_Map;
//typedef Object* (*f_map_get)(Ctx *, Object *b, Object *k);
//typedef Object* (*f_map_set)(Ctx *, Object *b, Object *k, Object *v);
//
//typedef struct knh_Map {
//	Object *map;
//} knh_Map ;

/* ------------------------------------------------------------------------ */
/* @class DictIdx Object knh_DictIdx_struct */

typedef struct knh_DictIdx {
	knh_int_t    offset;
	knh_Array_t* terms;
	struct knh_DictSet_t* termsDictSet;
} knh_DictIdx_struct ;

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* @class Class Object knh_Class_t */
/* @flag Class.Release!Debug CF knh_tClass[(%s)].cflag 'is:*:is:*' */
/* @flag Class.Immutable CF knh_tClass[(%s)].cflag 'is:*:is:*' */
/* @flag Class.Cyclic CF knh_tClass[(%s)].cflag 'is:set:*:*' */
/* @flag Class.MetaExtensible CF knh_tClass[(%s)].cflag 'is:*:is:*' */
/* @flag Class.Private!Public CF knh_tClass[(%s)].cflag 'is:*:is:*' */
/* @flag Class.Final CF knh_tClass[(%s)].cflag 'is:*:is:*' */
/* @flag Class.Singleton CF knh_tClass[(%s)].cflag 'is:*:*:*' */
/* @ flag Class.System CF knh_tClass[(%s)].cflag 'is:*:is:*' */
/* @flag Class.NullObject CF knh_tClass[(%s)].cflag 'is:*:*:*' */
/* @flag Class.Interface  CF knh_tClass[(%s)].cflag 'is:*:is:*' */

typedef struct knh_Class_t {
	knh_hObject_t h;
	knh_class_t   cid;
	knh_type_t    type;
} knh_Class_t;

// dummy
#define KNH_FLAG_CF_PARAM1 0
#define KNH_FLAG_CF_PARAM2 0

/* ------------------------------------------------------------------------ */
/* @class ClassStruct Object knh_ClassStruct_struct @Private */
/* @flag ClassStruct.Hidden CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */
/* @flag ClassStruct.AutoName CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */
/* @flag ClassStruct.SafeValue CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */
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

typedef struct knh_ClassStruct {
	knh_struct_t sid;
	knh_ushort_t fsize;
	knh_cfield_t* fields;
	knh_Array_t*  methods;
} knh_ClassStruct_struct;

/* ------------------------------------------------------------------------ */
/* @class MethodField Object knh_MethodField_struct @Private */

typedef struct  knh_mfield_t {
	knh_type_t   type  ;
	knh_fieldn_t  fn    ;
} knh_mfield_t ;

typedef struct knh_MethodField {
	knh_flag_t flag;
	knh_ushort_t size;
	knh_mfield_t* params;
} knh_MethodField_struct;

/* ------------------------------------------------------------------------ */
/* @class Method Object knh_Method_struct */
/* @flag Method.Private!Public MF DP((Method*)%s)->flag 'is:set:is:*' */
/* @flag Method.Virtual!Final MF DP((Method*)%s)->flag 'is:set:is:*' */
/* @flag Method.Static MF DP((Method*)%s)->flag 'is:*:is:*' */
/* @flag Method.ClassFunc MF DP((Method*)%s)->flag 'is:*:is:*' */
/* @flag Method.NullBase MF DP((Method*)%s)->flag 'is:*:is:*' */
/* @flag Method.VarArgs MF DP((Method*)%s)->flag 'is:set:is:*' */
/* @flag Method.Smart   MF DP((Method*)%s)->flag 'is:*:*:*' */
/* @flag Method.Aspect MF DP((Method*)%s)->flag 'is:set:is:*' */
/* @flag Method.ObjectCode MF DP((Method*)%s)->flag 'is:set:*:*' */
/* @flag Method.Generated MF DP((Method*)%s)->flag 'is:set:*:*' */

typedef struct knh_Method {
	knh_flag_t     flag;  knh_class_t    cid;
	knh_methodn_t  mn;    knh_ushort_t   delta;
	struct knh_MethodField_t* mf;
	f_method       func;
	void*          code;
} knh_Method_struct;

/* ------------------------------------------------------------------------ */
/* @class Mapper Object knh_Mapper_struct */
/* @flag Mapper.Interface MMF DP((Mapper*)%s)->flag     'is:set:is:*' */
/* @flag Mapper.Significant MMF DP((Mapper*)%s)->flag   'is:set:is:*' */
/* @flag Mapper.Final MMF DP((Mapper*)%s)->flag         'is:*:is:*' */
/* @flag Mapper.Synonym MMF DP((Mapper*)%s)->flag       'is:set:is:*' */
/* @flag Mapper.LossLess MMF DP((Mapper*)%s)->flag      'is:set:is:*' */
/* @flag Mapper.Total!Partial MMF DP((Mapper*)%s)->flag 'is:set:is:*' */
/* @flag Mapper.Static!Temporal MMF DP((Mapper*)%s)->flag 'is:set:is:*' */
/* @flag Mapper.Local MMF DP((Mapper*)%s)->flag 'is:set:is:*' */
/* @flag Mapper.Derived MMF DP((Mapper*)%s)->flag 'is:set:is:*' */
/* @flag Mapper.MapMap MMF:1 (%s)->h.flag              'is:set:*:*' */

typedef struct knh_Mapper {
	knh_flag_t   flag;
	knh_ushort_t size;
	knh_class_t  scid;
	knh_class_t  tcid;
	union {
		f_mapper     fmap;
		struct knh_Mapper_t *m1;
	};
	union {
		Object*      mapdata;
		struct knh_Mapper_t *m2;
	};
} knh_Mapper_struct;

/* ------------------------------------------------------------------------ */
/* @class ClassMap Object knh_ClassMap_struct @Private */
/* @flag ClassMap.Sorted CM:1 (%s)->h.flag 'is:set:*:*' */

typedef struct knh_ClassMap {
	struct knh_Mapper_t**   maplist;
	knh_ushort_t   size;
	knh_ushort_t   capacity;
} knh_ClassMap_struct ;

///* ------------------------------------------------------------------------ */
///* class Closure Object knh_ */
//
//typedef struct knh_Closure {
//	Object* self;
//	struct knh_Method_t* method;
//} knh_Closure;

/* ------------------------------------------------------------------------ */
/* @class AffineConv Object knh_AffineConv_struct @Private */

typedef struct knh_AffineConv {
	knh_float_t scale;
	knh_float_t shift;
} knh_AffineConv_struct;

/* ------------------------------------------------------------------------ */
/* IntSpec, FloatSpec, StringSpec */

typedef struct knh_cspec_t {
	knh_flag_t  flag;
	knh_class_t cid;
	knh_String_t* urn;
	knh_String_t* tag;
	Object* defvalue;
} knh_cspec_t;

/* ------------------------------------------------------------------------ */
/* @class IntUnit Object knh_IntUnit_struct @Private */
/* @flag IntUnit.Unsigned UF DP((IntUnit*)%s)->spec.flag 'is:*:is:*' */

struct  knh_IntUnit_t;
typedef knh_bool_t  (*f_iunit_chk)(struct knh_IntUnit_t *, knh_int_t v);
typedef knh_int_t   (*f_iunit_cmp)(struct knh_IntUnit_t *, knh_int_t v1, knh_int_t v2);
typedef void        (*f_iunit_fmt)(struct knh_IntUnit_t *, char *buf, size_t bufsiz, knh_int_t v);

typedef struct knh_IntUnit {
	knh_cspec_t spec;
	f_iunit_chk fchk;
	f_iunit_cmp fcmp;
	f_iunit_fmt ffmt;
	knh_int_t min;
	knh_int_t max;
	knh_int_t step;
	knh_int_t bfoffset;
	size_t bfsize;
	knh_Int_t** bfarray;
} knh_IntUnit_struct;

/* ------------------------------------------------------------------------ */
/* @class FloatUnit Object knh_FloatUnit_struct @Private */

struct knh_FloatUnit_t;
typedef knh_bool_t  (*f_funit_chk)(struct knh_FloatUnit_t *, knh_float_t v);
typedef knh_int_t   (*f_funit_cmp)(struct knh_FloatUnit_t *, knh_float_t v1, knh_float_t v2);
typedef void       (*f_funit_fmt)(struct knh_FloatUnit_t *, char *buf, size_t bufsiz, knh_float_t v);

typedef struct knh_FloatUnit {
	knh_cspec_t spec;
	f_funit_chk fchk;
	f_funit_cmp fcmp;
	f_funit_fmt ffmt;
	knh_float_t min;
	knh_float_t max;
	knh_float_t step;
	char* FMT;
} knh_FloatUnit_struct;

/* ------------------------------------------------------------------------ */
/* @class Regex Object knh_Regex_t */

typedef void knh_regex_t;

#ifndef KNH_REGEX_NMATCH_MAX
#define KNH_REGEX_NMATCH_MAX    16
#endif

typedef struct {
	int rm_so;   /* start of match */
	int rm_eo;   /* endo of match */
	char *rm_name;  /* NULL, if not NAMED */
} knh_regmatch_t;

typedef knh_regex_t* (*knh_fregmalloc)(Ctx *);
typedef int (*knh_fregcomp)(Ctx *, knh_regex_t *, char *pattern, int flags);
typedef int (*knh_fregexec)(Ctx *, knh_regex_t *, char *str, size_t nmatch, knh_regmatch_t p[], int flags);
typedef void (*knh_fregfree)(knh_regex_t *);

typedef struct {
	int  type;
	char *name;
	knh_fregmalloc regmalloc;
	knh_fregcomp   regcomp;
	knh_fregexec   regexec;
	knh_fregfree   regfree;
} knh_regex_drvapi_t;

typedef struct {
	knh_hObject_t h;
	knh_regex_t *reg;
	knh_regex_drvapi_t *df;
	struct knh_String_t *pattern;
} knh_Regex_t;

/* ------------------------------------------------------------------------ */
/* @class BytesConv Object knh_BytesConv_struct @Private */

struct knh_BytesConv_t;
typedef size_t (*f_bconv)(Ctx *ctx, struct knh_BytesConv_t *o, knh_bytes_t t, knh_Bytes_t *ba);

typedef struct {
	int  type;
	char *name;
	f_bconv      fbconv;
	f_bconv      fbconv_inverse;
} knh_bconv_driapi_t;

/* ------------------------------------------------------------------------ */

#ifdef KNH_USING_ICONV
	#include<iconv.h>
#endif

typedef struct knh_BytesConv {
	struct knh_String_t *name;
	f_bconv fbconv;
#ifdef KNH_USING_ICONV
	iconv_t iconv_d;
#endif
} knh_BytesConv_struct;

/* ------------------------------------------------------------------------ */
/* @class StringUnit Object knh_StringUnit_struct @Private */

struct knh_StringUnit_t;
typedef knh_String_t *(*f_sunit_new)(Ctx *, knh_class_t cid, knh_bytes_t, struct knh_String_t *);
typedef int (*f_sunit_cmp)(struct knh_StringUnit_t *, knh_bytes_t, knh_bytes_t);

typedef struct knh_StringUnit {
	knh_cspec_t spec;
	f_sunit_new fnew;
	f_sunit_cmp fcmp;
	f_bconv     fbconv;
	struct knh_BytesConv_t *bconv;
	knh_ushort_t bytelen;
	knh_ushort_t charlen;
	Object* pattern;
	Object* vocabDictIdx;
} knh_StringUnit_struct;


/* ------------------------------------------------------------------------ */
/* InputStream, OutputStream */

/* ------------------------------------------------------------------------ */
/* @class InputStream Object knh_InputStream_struct */

struct knh_InputStream;
typedef void knh_inptr_t;

typedef knh_inptr_t* (*f_inptr_open)(Ctx *ctx, knh_bytes_t);
typedef int (*f_inptr_getc)(Ctx *ctx, knh_inptr_t *);
typedef size_t (*f_inptr_read)(Ctx *ctx, knh_inptr_t *, char *buf, size_t bufsiz);
typedef void (*f_inptr_close)(Ctx *ctx, knh_inptr_t *);

typedef struct {
	int type; char *name;
	f_inptr_open  fopen;
	f_inptr_getc  fgetc;
	f_inptr_read  fread;
	f_inptr_close fclose;
} knh_inptr_drvapi_t;

typedef knh_inptr_drvapi_t* (*f_inptr_drivers)(Ctx *ctx, knh_bytes_t);

typedef struct knh_InputStream {
	knh_inptr_t* inptr;
	knh_Bytes_t* ba;
	size_t  bapos;
	size_t  baend;
	knh_inptr_drvapi_t apis;
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

struct knh_OutputStream;
typedef void knh_outptr_t;

typedef knh_outptr_t* (*f_outptr_open)(Ctx *ctx, knh_bytes_t, char *mode);
typedef void (*f_outptr_putc)(Ctx *ctx, knh_outptr_t *, int ch);
typedef size_t (*f_outptr_write)(Ctx *ctx, knh_outptr_t *, char *buf, size_t bufsiz);
typedef void (*f_outptr_flush)(Ctx *ctx, knh_outptr_t *);
typedef void (*f_outptr_close)(Ctx *ctx, knh_outptr_t *);

typedef struct knh_outptr_apis_t {
	int type; char *name;
	f_outptr_open   fopen;
	f_outptr_putc   fputc;
	f_outptr_write  fwrite;
	f_outptr_flush  fflush;
	f_outptr_close  fclose;
} knh_outptr_drvapi_t;

typedef struct knh_OutputStream {
	knh_outptr_t* outptr;
	knh_Bytes_t* ba;
	knh_outptr_drvapi_t apis;
	knh_String_t *enc;
	struct knh_BytesConv_t* bconv;
	knh_String_t*  urn;
	size_t size;
	size_t line;
	knh_String_t*  NEWLINE;
	knh_String_t*  TAB;
	size_t indent;
} knh_OutputStream_struct;

///* ------------------------------------------------------------------------ */
///* @ class Socket Object knh_ */
//
//typedef int knh_socket_t;
//
//typedef struct knh_Socket {
//	knh_String_t* urn;
//	int port;
//	knh_socket_t sd;
//	FILE *fp_in;
//	FILE *fp_out;
//	struct knh_InputStream_t  *in;
//	struct knh_OutputStream_t *out;
//} knh_Socket;

/* ======================================================================== */

typedef void   knh_connptr_t;
typedef        knh_connptr_t* (*f_connptr_open)(Ctx *ctx, knh_bytes_t url);
typedef struct knh_ResultSet_t* (*f_connptr_query)(Ctx *ctx, knh_connptr_t *, char *query);
typedef void   (*f_connptr_close)(Ctx *ctx, knh_connptr_t *);

struct knh_ResultSet_t;
typedef void   knh_rshdlr_t;
typedef int    (*f_rshdlr_next)(Ctx *, knh_rshdlr_t *, struct knh_ResultSet_t*);
typedef void   (*f_rshdlr_free)(knh_rshdlr_t *);

typedef struct {
	int  type;
	char *name;
	f_connptr_open   open_conn;
	f_connptr_query  query_conn;
	f_connptr_close  close_conn;
	f_rshdlr_next    next_rset;
	f_rshdlr_free    free_rset;
} knh_db_drvapi_t;

/* ------------------------------------------------------------------------ */
/* @class Connection Object knh_Connection_struct */
/* @class ResultSet Object knh_ResultSet_struct */

typedef struct knh_Connection {
	knh_connptr_t      *connptr;
	knh_db_drvapi_t    *df;
	knh_String_t       *urn;
} knh_Connection_struct;

#define knh_ResultSet_CTYPE__null    0
#define knh_ResultSet_CTYPE__int     1
#define knh_ResultSet_CTYPE__int64   2
#define knh_ResultSet_CTYPE__float   3
#define knh_ResultSet_CTYPE__bytes   4
#define knh_ResultSet_CTYPE__Object  5

typedef struct knh_rscolumn_t {
	knh_type_t type;
	knh_ushort_t ctype;
	knh_String_t *name;
	size_t start;
	size_t len;
	int dbtype;
} knh_rscolumn_t;

typedef struct knh_ResultSet {
	knh_rshdlr_t         *rsetptr;
	struct knh_Connection_t *conn;
	f_rshdlr_free         free_rset;
	knh_String_t         *tableName;
	knh_class_t           tcid;
	knh_ushort_t          column_size;
	knh_rscolumn_t        *column;
	knh_Bytes_t           *databuf;
	size_t                count;
} knh_ResultSet_struct;

/* ------------------------------------------------------------------------ */
/* @class Exception Object knh_Exception_struct */
/* @flag Exception.Fatal EF DP((Exception*)%s)->flag 'is:*:is:*' */
/* @flag Exception.Logging EF DP((Exception*)%s)->flag 'is:*:is:*' */
/* @flag Exception.Generated EF DP((Exception*)%s)->flag 'is:*:is:*' */
/* @flag Exception.Caught EF DP((Exception*)%s)->flag 'is:set:*:*' */

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
/* @flag ExceptionHandler.Catching EHF:1 (%s)->h.flag 'is:set:*:*' */

typedef struct knh_ExceptionHandler {
	jmp_buf jmpbuf;
	struct knh_Exception_t* caught;
} knh_ExceptionHandler_struct;

/* ------------------------------------------------------------------------ */
/* @class Script Object knh_Script_t */

#define KNH_SCRIPT_FIELDSIZE   128

typedef struct knh_Script_t {
	knh_hObject_t h;
	Object **fields;
} knh_Script_t ;

/* ------------------------------------------------------------------------ */
/* @class NameSpace Object knh_NameSpace_struct @Private */

typedef int (*f_libknh_init)(Ctx *ctx);
typedef void (*f_libknh_traverse)(Ctx *ctx, f_traverse ftr);

typedef struct knh_NameSpace {
	struct knh_NameSpace_t* parent;
	knh_String_t*           nsname;
	knh_Array_t*            imports;
	struct knh_DictSet_t*   name2cidDictSet;
	struct knh_DictSet_t*   func2cidDictSet;
	struct knh_DictMap_t*   lconstDictMap;
	struct knh_DictMap_t*   tag2urnDictMap;
	struct knh_Script_t*    script;
	void                   *dlhdr;
	f_libknh_traverse       ftraverse;
} knh_NameSpace_struct;

/* ------------------------------------------------------------------------ */
/* @class System Object knh_System_struct @Field */

typedef struct knh_System {
	struct knh_DictMap_t* props;
	struct knh_NameSpace_t* ns;
	struct knh_String_t*       enc;
	struct knh_InputStream_t*  in;
	struct knh_OutputStream_t* out;
	struct knh_OutputStream_t* err;
	struct knh_DictIdx_t *tfileidDictIdx;
	struct knh_DictIdx_t *tfieldnDictIdx;
	struct knh_Array_t   *tMethodFields;
	struct knh_DictMap_t *tConstDictMap;
	knh_String_t         *homeDir;
	struct knh_DictMap_t *sysnsDictMap;
	struct knh_DictSet_t *funcDictSet;
	struct knh_DictSet_t *drvapiDictSet;
} knh_System_struct;

/* ------------------------------------------------------------------------ */
/* @class Runtime Object knh_Runtime_struct */

typedef struct knh_Runtime {
	knh_uint_t runtime_id;
	size_t     ctxcount;
	struct knh_HashMap_t* tmetaHashMap;
	struct knh_DictMap_t* tnameSpaceDictMap;
//	struct knh_DictMap_t* tnameContextDictMap;
	struct knh_HashMap_t* tmapperHashMap;
	struct knh_HashMap_t* tmethodHashMap;
} knh_Runtime_struct;

/* ------------------------------------------------------------------------ */
/* @class Context Object knh_Context_t */
/* @flag Context.Release!Debug CTXF ((Context*)%s)->flag 'is:set:is:set' */
/* @flag Context.Compiling CTXF ((Context*)%s)->flag 'is:set:is:set' */
/* @flag Context.Verbose CTXF ((Context*)%s)->flag 'is:set:is:set' */
/* @flag Context.Verbose2 CTXF ((Context*)%s)->flag 'is:set:is:set' */

///* ------------------------------------------------------------------------ */
///* class Mutex Object knh_ */
//
//typedef struct knh_Mutex {
//	knh_uint_t magic;
//	knh_uint_t loccount;
//	knh_mutex_t mutex;
//} knh_Mutex;


/* ------------------------------------------------------------------------ */

#define KONOHA_TABLE_MAGIC   4219881

#define TSTRUCTDB_SIZE  (KONOHA_TSTRUCT_SIZE * sizeof(knh_tstruct_t))

/* ------------------------------------------------------------------------ */

//#ifndef KONOHA_TCLASS_SIZE
//#define KONOHA_TCLASS_SIZE 256
//#endif
//
//#define TCLASSDB_SIZE  (KONOHA_TCLASS_SIZE * sizeof(knh_tclass_t))
//
//#ifndef KONOHA_TFIELDN_SIZE
//#define KONOHA_TFIELDN_SIZE 256
//#endif
//
//#ifndef KONOHA_TMETHODN_SIZE
//#define KONOHA_TMETHODN_SIZE 512
//#endif
//
///* ------------------------------------------------------------------------ */
//
//typedef struct {
//	knh_flag_t   flag;
//	knh_expt_t   parent;
//	struct knh_String_t     *name;
//} knh_texpt_t;
//
//#ifndef KONOHA_TEXPT_SIZE
//#define KONOHA_TEXPT_SIZE (KONOHA_TCLASS_SIZE/4)
//#endif
//
//#define TEXPTDB_SIZE  (KONOHA_TEXPT_SIZE * sizeof(knh_texpt_t))

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* include generated header file */

#ifdef __cplusplus
}
#endif

#endif /*CLASS_KONOHA_H_*/

