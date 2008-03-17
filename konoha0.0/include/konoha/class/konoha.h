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

/* @flag Nue.GCHook NUE:1 knh_Object_head(%s)->flag 'is:set:*:*' */
/* @flag Nue.ObjectText NUE:2 knh_Object_head(%s)->flag 'is:set:*:*' */
/* @flag String.STEXT STRING:1 knh_Object_head(%s)->flag 'is:set:*:*' */
/* @flag Bytes.StackBuffer BYTES:1 knh_Object_head(%s)->flag 'is:set:*:*' */
/* @flag Object.Release!Debug OF knh_Object_head(%s)->flag 'is:*:is:*' */
/* @flag Object.Immutable OF knh_Object_head(%s)->flag 'is:*:is:*' */
/* @flag Object.MetaData OF knh_Object_head(%s)->flag 'has:set:has:*' */
/* @flag Object.Synchronized OF knh_Object_head(%s)->flag 'is:*:is:*' */
/* @flag Object.Modified OF knh_Object_head(%s)->flag 'is:set:is:set' */
/* @flag Object.Local4 OF knh_Object_head(%s)->flag 'is:set:*:*' */
/* @flag Object.Local3 OF knh_Object_head(%s)->flag 'is:set:*:*' */
/* @flag Object.Local2 OF knh_Object_head(%s)->flag 'is:set:*:*' */
/* @flag Object.Local1 OF knh_Object_head(%s)->flag 'is:set:*:*' */
/* @flag Class.Release!Debug CF knh_tclass_table(%s)->cflag 'is:*:is:*' */
/* @flag Class.Immutable CF knh_tclass_table(%s)->cflag 'is:*:is:*' */
/* @flag Class.MetaExtensible CF knh_tclass_table(%s)->cflag 'is:*:is:*' */
/* @flag Class.Private!Public CF knh_tclass_table(%s)->cflag 'is:*:is:*' */
/* @flag Class.Final CF knh_tclass_table(%s)->cflag 'is:*:is:*' */
/* @flag Class.Strict CF knh_tclass_table(%s)->cflag 'is:*:*:*' */
/* @flag Class.System CF knh_tclass_table(%s)->cflag 'is:*:is:*' */
/* @flag Class.NullObject CF knh_tclass_table(%s)->cflag 'is:*:*:*' */
/* @flag Class.NA CF knh_tclass_table(%s)->cflag 'is:*:is:*' */
/* @flag ClassStruct.Hidden CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */
/* @flag ClassStruct.AutoName CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */
/* @flag ClassStruct.SafeValue CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */
/* @flag ClassStruct.Protected CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */
/* @flag ClassStruct.Getter CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */
/* @flag ClassStruct.Setter CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */
/* @flag ClassStruct.Key CFF ((ClassStruct)%s)->fields[n].flag 'is:set:*:*' */
/* @flag Method.Public!Private MF ((Method*)%s)->flag 'is:set:is:*' */
/* @flag Method.Virtual!Final MF ((Method*)%s)->flag 'is:set:is:*' */
/* @flag Method.Static MF ((Method*)%s)->flag 'is:*:is:*' */
/* @flag Method.Class MF ((Method*)%s)->flag 'is:*:is:*' */
/* @flag Method.VarArgs MF ((Method*)%s)->mf->flag 'is:set:is:*' */
/* @flag Method.Aspect MF ((Method*)%s)->mf->flag 'is:set:is:*' */
/* @flag Method.ObjectCode MF ((Method*)%s)->flag 'is:set:*:*' */
/* @flag Method.Generated MF ((Method*)%s)->mf->flag 'is:set:*:*' */
/* @flag MapMap.Interface MMF ((MapMap*)%s)->flag 'is:set:is:*' */
/* @flag MapMap.VerySignificant MMF ((MapMap*)%s)->flag '*:*:*:*' */
/* @flag MapMap.Significant MMF ((MapMap*)%s)->flag 'is:set:is:*' */
/* @flag MapMap.Synonym MMF ((MapMap*)%s)->flag 'is:set:is:*' */
/* @flag MapMap.LossLess MMF ((MapMap*)%s)->flag 'is:set:is:*' */
/* @flag MapMap.Total!Partial MMF ((MapMap*)%s)->flag 'is:set:is:*' */
/* @flag MapMap.Static!Temporal MMF ((MapMap*)%s)->flag 'is:set:is:*' */
/* @flag MapMap.Local MMF ((MapMap*)%s)->flag 'is:set:is:*' */
/* @flag MapMap.Derived MMF ((MapMap*)%s)->flag 'is:set:is:*' */
/* @flag Exception.Fatal EF ((Exception*)%s)->flag 'is:*:is:*' */
/* @flag Exception.Logging EF ((Exception*)%s)->flag 'is:*:is:*' */
/* @flag Exception.Generated EF ((Exception*)%s)->flag 'is:*:is:*' */
/* @flag Exception.Caught EF ((Exception*)%s)->flag 'is:set:*:*' */
/* @flag ExceptionHandler.Catching EHF:1 knh_Object_head(%s)->flag 'is:set:*:*' */
/* @flag IntUnit.Unsigned UF ((IntUnit*)%s)->spec.flag 'is:*:is:*' */

/* ------------------------------------------------------------------------ */
/* @class Object Object 0 */

//#ifndef KONOHA_OBJECT_MAGIC
//#ifdef  KONOHA_SAFEMODE
#define KONOHA_OBJECT_MAGIC  ((7777 << 7) + 777)
//#endif 
//#endif

typedef struct hObject {
#ifdef KONOHA_OBJECT_MAGIC
	knh_uint_t   magic;
#endif
	knh_uint_t   refc;
	knh_class_t  cid;   
	knh_flag_t   flag;
} hObject;
                   
#define knh_Object_head(b)     (((hObject*)b) - 1)

/* ------------------------------------------------------------------------ */
/* @class Tuple Object 0 */

#ifndef KNH_OBJECT_FIELDSIZE
#define KNH_OBJECT_FIELDSIZE 64
#endif

typedef struct {
	Object* v[KNH_OBJECT_FIELDSIZE];
} knh_Tuple;

/* ------------------------------------------------------------------------ */
/* @class Tuple1 Tuple knh_ */

typedef struct {
	Object* v[1];
} knh_Tuple1; 

/* ------------------------------------------------------------------------ */
/* @class Tuple2 Tuple knh_ */

typedef struct {
	Object* v[2];
} knh_Tuple2; 

/* ------------------------------------------------------------------------ */
/* @class Tuple3 Tuple knh_ */

typedef struct {
	Object* v[3];
} knh_Tuple3; 

/* ------------------------------------------------------------------------ */
/* @class Tuple4 Tuple knh_ */

typedef struct {
 	Object* v[4];
} knh_Tuple4; 

/* ------------------------------------------------------------------------ */
/* @class Tuple5 Tuple knh_ */

typedef struct {
 	Object* v[5];
} knh_Tuple5; 

/* ------------------------------------------------------------------------ */
/* @class Tuple6 Tuple knh_ */

typedef struct {
 	Object* v[6];
} knh_Tuple6; 

/* ------------------------------------------------------------------------ */
/* @class Tuple7 Tuple knh_ */

typedef struct {
 	Object* v[7];
} knh_Tuple7; 

/* ------------------------------------------------------------------------ */
/* @class Tuple8 Tuple knh_ */

typedef struct {
	Object* v[8];
} knh_Tuple8; 

/* ------------------------------------------------------------------------ */
/* @class Tuple9 Tuple knh_ */

typedef struct {
	Object* v[9];
} knh_Tuple9; 

/* ------------------------------------------------------------------------ */
/* @class Tuple10 Tuple knh_ */

typedef struct {
	Object* v[10];
} knh_Tuple10; 

/* ------------------------------------------------------------------------ */
/* @class Tuple11 Tuple knh_ */

typedef struct {
	Object* v[11];
} knh_Tuple11; 

/* ------------------------------------------------------------------------ */
/* @class Tuple12 Tuple knh_ */

typedef struct {
 	Object* v[12];
} knh_Tuple12; 

/* ------------------------------------------------------------------------ */
/* @class Tuple13 Tuple knh_ */

typedef struct {
	Object* v[13];
} knh_Tuple13; 

/* ------------------------------------------------------------------------ */
/* @class Tuple14 Tuple knh_ */

typedef struct {
	Object* v[14];
} knh_Tuple14; 

/* ------------------------------------------------------------------------ */
/* @class Tuple15 Tuple knh_ */

typedef struct {
	Object* v[15];
} knh_Tuple15; 

/* ------------------------------------------------------------------------ */
/* @class Prototype Object knh_ */

#define KNH_PROTOTYPE_FIELDSIZE  KNH_OBJECT_FIELDSIZE

typedef struct knh_Prototype {
	Object* value[KNH_PROTOTYPE_FIELDSIZE];
	Object* ns;
} knh_Prototype;


/* ------------------------------------------------------------------------ */
/* @class Nue Object knh_ */

typedef struct knh_Nue {
	void* msg;
} knh_Nue;

/* ------------------------------------------------------------------------ */
/* @class Bool Object knh_ */

typedef struct knh_Bool {
	knh_bool_t value;
} knh_Bool;

/* ------------------------------------------------------------------------ */
/* @class Int Object knh_ */

typedef struct knh_Int {
	knh_int_t value;
} knh_Int;

/* ------------------------------------------------------------------------ */
/* @class Int64 Object knh_ */

typedef struct knh_Int64 {
	knh_int64_t value;
} knh_Int64;

/* ------------------------------------------------------------------------ */
/* @class Float Object knh_ */

typedef struct knh_Float {
	knh_float_t value;
} knh_Float;

/* ------------------------------------------------------------------------ */
/* @class String Object knh_ */

typedef struct knh_String {
	knh_uchar_t* value;
	size_t strlen;
	knh_hcode_t hcode;
	Object* orig;
} knh_String;

/* ------------------------------------------------------------------------ */
/* @class Regex Object knh_ */

typedef struct knh_Regex {
	knh_String* pstr;
	void * re;
} knh_Regex;

/* ------------------------------------------------------------------------ */
/* @class Bytes Object knh_ */

typedef struct knh_Bytes {
	knh_uchar_t* value;
	size_t size;
	size_t capacity;
} knh_Bytes;

/* ------------------------------------------------------------------------ */
/* @class BytesConv Object knh_ */

struct knh_BytesConv;
typedef size_t (*f_bconv)(Ctx *ctx, struct knh_BytesConv *b, char *buf, size_t bufsiz, knh_Bytes *ba);

#ifdef KONOHA_USING_ICONV
	#include<iconv.h>
#endif

typedef struct knh_BytesConv {
	knh_String *name;
	f_bconv fbconv;
#ifdef KONOHA_USING_ICONV
	iconv_t iconv_d;
#endif
} knh_BytesConv;


/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* @class Array Object knh_ */

typedef struct knh_Array {
	Object** list;
	size_t size;
	size_t capacity;
} knh_Array;

/* ------------------------------------------------------------------------ */
/* HashMap, HashSet */

typedef struct {
	knh_hcode_t key;
	Object *keyobj;
} knh_hashkey_t;

typedef struct knh_hashmape_t {
	knh_hashkey_t           h;
	struct knh_hashmape_t  *next;
	Object             *value;
} knh_hashmape_t ;

/* ------------------------------------------------------------------------ */
/* @class HashMap Object knh_ */

typedef struct knh_HashMap {
	size_t size;
	size_t capacity;
	knh_hashmape_t** array;
	float factor;
} knh_HashMap;

/* ------------------------------------------------------------------------ */
/* @class HashSet Object knh_ */

typedef struct knh_hashsete_t {
	knh_hashkey_t            h;
	struct knh_hashsete_t   *next;
	knh_uint_t               value;
} knh_hashsete_t ;

typedef struct knh_HashSet {
	size_t size;
	size_t capacity;
	knh_hashsete_t** array;
	float factor;
} knh_HashSet;

/* ------------------------------------------------------------------------ */
/* @class DictMap Object knh_ */

#define knh_qsort qsort

typedef struct knh_dictmape_t {
	struct knh_String *key;
	Object *value;
} knh_dictmape_t; 

typedef struct knh_DictMap {
	size_t size;
	size_t capacity;
	knh_dictmape_t* list;
	size_t sorted;
} knh_DictMap;

/* ------------------------------------------------------------------------ */
/* @class DictSet Object knh_ */

typedef struct knh_dictsete_t {
	struct knh_String *key;
	knh_uint_t  value;
} knh_dictsete_t; 

typedef struct knh_DictSet {
	size_t size;
	size_t capacity;
	knh_dictsete_t* list;
	size_t sorted;
} knh_DictSet;


/* ------------------------------------------------------------------------ */
/* @class Iterator Object knh_ */

struct knh_Iterator;
typedef Object* (*f_next)(Ctx *, struct knh_Iterator *);
typedef Object* (*f_each)(Ctx *, struct knh_Iterator *, knh_class_t);

typedef struct knh_Iterator {
	Object* source;
	knh_class_t cid;
	knh_flag_t flag;
	f_each feach;
	size_t pos;
	void* ref;
	f_next fnext;
	size_t count;
	size_t start;
	size_t end;
} knh_Iterator;

/* ------------------------------------------------------------------------ */
/* @class DictIdx Object knh_ */

typedef struct knh_DictIdx {
	knh_int_t offset;
	knh_Array* terms;
	knh_DictSet* termsDictSet;
} knh_DictIdx;


/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* @class Class Object knh_ */

typedef struct knh_Class {
	knh_class_t bcid;
	knh_type_t type;
} knh_Class;

/* ------------------------------------------------------------------------ */
/* @class ClassStruct Object knh_ */


typedef struct knh_cfield_t {
	knh_flag_t    flag  ;
	knh_type_t    type  ; 
	knh_fieldn_t  fn    ;
	Object      *value; 
} knh_cfield_t ;

typedef struct knh_ClassStruct {
	knh_struct_t sid;
	knh_ushort_t fsize;
	knh_cfield_t* fields;
	knh_Array* methods;
} knh_ClassStruct;

/* ------------------------------------------------------------------------ */
/* @class MethodField Object knh_ */

typedef struct  knh_mfield_t {
	knh_type_t   type  ; 
	knh_fieldn_t  fn    ;
} knh_mfield_t ;

typedef struct knh_MethodField {
	knh_flag_t flag;
	knh_ushort_t size;
	knh_mfield_t* params;
} knh_MethodField;

/* ------------------------------------------------------------------------ */
/* @class Method Object knh_ */

typedef struct knh_Method {
	knh_flag_t flag;
	knh_class_t cid;
	knh_methodn_t mn;
	knh_ushort_t delta;
	knh_MethodField* mf;
	f_method func;
	void* code;
} knh_Method;

/* ------------------------------------------------------------------------ */
/* @class MapMap Object knh_ */

typedef struct knh_MapMap {
	knh_flag_t flag;
	knh_ushort_t size;
	knh_class_t scid;
	knh_class_t tcid;
	f_mapmap fmap;
	Object* config;
} knh_MapMap;

/* ------------------------------------------------------------------------ */
/* @class ClassRel Object knh_ */

typedef struct knh_ClassRel {
	knh_MapMap** maplist;
	knh_ushort_t size;
	knh_ushort_t capacity;
	knh_ushort_t psize;
	knh_ushort_t sorted;
} knh_ClassRel;


/* ------------------------------------------------------------------------ */
/* class Closure Object knh_ */

typedef struct knh_Closure {
	Object* self;
	knh_Method* method;
} knh_Closure;

/* ------------------------------------------------------------------------ */
/* @class AffineConv Object knh_ */

typedef struct knh_AffineConv {
	knh_float_t scale;
	knh_float_t shift;
	knh_int_t iscale;
	knh_int_t ishift;
} knh_AffineConv;


/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* IntSpec, FloatSpec, StringSpec */

typedef struct knh_cspec_t {
	knh_flag_t  flag;
	knh_class_t cid;
	knh_String* urn;
	knh_String* tag;
	Object* defvalue;
} knh_cspec_t;

typedef struct knh_ClassSpec {
	knh_cspec_t spec;
} knh_ClassSpec;


/* ------------------------------------------------------------------------ */
/* @class IntUnit Object knh_ */

struct  knh_IntUnit;
typedef knh_bool_t  (*f_iunit_chk)(struct knh_IntUnit *, knh_int_t v);
typedef knh_int_t   (*f_iunit_cmp)(struct knh_IntUnit *, knh_int_t v1, knh_int_t v2);
typedef void       (*f_iunit_fmt)(struct knh_IntUnit *, char *buf, knh_int_t v);

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
	Object** bfarray;
} knh_IntUnit;

/* ------------------------------------------------------------------------ */
/* @class FloatUnit Object knh_ */

struct knh_FloatUnit;
typedef knh_bool_t  (*f_funit_chk)(struct knh_FloatUnit *, knh_float_t v);
typedef knh_int_t   (*f_funit_cmp)(struct knh_FloatUnit *, knh_float_t v1, knh_float_t v2);
typedef void       (*f_funit_fmt)(struct knh_FloatUnit *, char *buf, knh_float_t v);

typedef struct knh_FloatUnit {
	knh_cspec_t spec;
	f_funit_chk fchk;
	f_funit_cmp fcmp;
	f_funit_fmt ffmt;
	knh_float_t min;
	knh_float_t max;
	knh_float_t step;
	char* FMT;
} knh_FloatUnit;


/* ------------------------------------------------------------------------ */
/* @class Vocabulary Object knh_ */

struct knh_Vocabulary;
typedef knh_bool_t   (*f_vocab_nmz)(Ctx *, knh_bytes_t, struct knh_Bytes *);
typedef struct knh_String *(*f_vocab_val)(Ctx *, struct knh_Vocabulary *, knh_bytes_t, void *, size_t, size_t);
typedef knh_int_t   (*f_vocab_cmp)(struct knh_Vocabulary *, knh_bytes_t, knh_bytes_t);

typedef struct knh_Vocabulary {
	knh_cspec_t spec;
	f_vocab_nmz fnmz;
	f_vocab_val fval;
	f_vocab_cmp fcmp;
	knh_ushort_t bytelen;
	knh_ushort_t charlen;
	Object* pattern;
	knh_DictIdx* vocabDictIdx;
} knh_Vocabulary;


/* ------------------------------------------------------------------------ */
/* InputStream, OutputStream */

/* ------------------------------------------------------------------------ */
/* @class InputStream Object knh_ */

struct knh_InputStream;
typedef void knh_inptr_t;

typedef knh_inptr_t* (*f_inptr_open)(Ctx *ctx, knh_bytes_t);
typedef int (*f_inptr_getc)(Ctx *ctx, knh_inptr_t *);
typedef size_t (*f_inptr_read)(Ctx *ctx, knh_inptr_t *, char *buf, size_t bufsiz);
typedef void (*f_inptr_close)(Ctx *ctx, knh_inptr_t *);

typedef struct knh_inptr_drivers_t {
	f_inptr_open  fopen;
	f_inptr_getc  fgetc;
	f_inptr_read  fread;
	f_inptr_close fclose;
} knh_inptr_drivers_t; 

typedef knh_inptr_drivers_t* (*f_inptr_drivers)(Ctx *ctx, knh_bytes_t);

typedef struct knh_InputStream {
	knh_inptr_t* inptr;
	knh_Bytes*   ba;
	size_t  bapos;
	size_t  baend;
	knh_inptr_drivers_t drv;
	knh_BytesConv* bconv;
	knh_String*  urn;
	knh_filen_t  filen;
	knh_ushort_t prev;
	size_t line;
	size_t size;
} knh_InputStream;

/* ------------------------------------------------------------------------ */
/* @class OutputStream Object knh_ */

struct knh_OutputStream;

typedef void knh_outptr_t;

typedef knh_outptr_t* (*f_outptr_open)(Ctx *ctx, knh_bytes_t);
typedef void (*f_outptr_putc)(Ctx *ctx, knh_outptr_t *, int ch);
typedef size_t (*f_outptr_write)(Ctx *ctx, knh_outptr_t *, char *buf, size_t bufsiz);
typedef void (*f_outptr_flush)(Ctx *ctx, knh_outptr_t *);
typedef void (*f_outptr_close)(Ctx *ctx, knh_outptr_t *);

typedef struct knh_outptr_drivers_t {
	f_outptr_open   fopen;
	f_outptr_putc   fputc;
	f_outptr_write  fwrite;
	f_outptr_flush  fflush;
	f_outptr_close  fclose;
} knh_outptr_drivers_t; 

typedef struct knh_OutputStream {
	knh_outptr_t* outptr;
	knh_Bytes*   ba;
	knh_outptr_drivers_t drv;
	knh_BytesConv* bconv;
	knh_String*  urn;
	size_t size;
	size_t line;
	knh_String*  NEWLINE;
	knh_String*  TAB;
	size_t indent;
} knh_OutputStream;

/* ------------------------------------------------------------------------ */
/* @class Socket Object knh_ */

typedef int knh_socket_t;


typedef struct knh_Socket {
	knh_String* urn;
	int port;
	knh_socket_t sd;
	FILE *fp_in;
	FILE *fp_out;
	knh_InputStream  *in;
	knh_OutputStream *out;
} knh_Socket;

/* ------------------------------------------------------------------------ */
/* @class ResultSet Object knh_ */

struct knh_ResultSet;
typedef void        knh_rsptr_t;
typedef knh_bool_t  (*f_rsptr_next)(Ctx *, knh_rsptr_t *, struct knh_ResultSet*);
typedef void        (*f_rsptr_free)(knh_rsptr_t *);

typedef struct knh_rsptr_drivers_t {
	f_rsptr_free  ffree;
	f_rsptr_next  fnext;
} knh_rsptr_drivers_t;

#define knh_ResultSet_CTYPE__null    0
#define knh_ResultSet_CTYPE__int     1
#define knh_ResultSet_CTYPE__int64   2
#define knh_ResultSet_CTYPE__float   3
#define knh_ResultSet_CTYPE__bytes   4

typedef struct knh_rscolumn_t {
	knh_type_t type;
	knh_ushort_t ctype;
	knh_String *name;
	size_t start;
	size_t len;
	int dbtype;
} knh_rscolumn_t;

typedef struct knh_ResultSet {
	knh_rsptr_t         *rsptr;
	knh_rsptr_drivers_t drv;
	knh_String          *tableName;
	knh_class_t         tcid;
	knh_ushort_t        column_size;
	knh_rscolumn_t      *column;
	knh_Bytes           *databuf;
} knh_ResultSet;

/* ------------------------------------------------------------------------ */
/* @class Connection Object knh_ */

struct knh_Connection;

typedef void   knh_connptr_t;
typedef knh_connptr_t* (*f_connptr_open)(Ctx *ctx, knh_bytes_t url, char *uname, char *upwd);
typedef struct knh_ResultSet* (*f_connptr_query)(Ctx *ctx, knh_connptr_t *, char *query);
typedef void  (*f_connptr_close)(Ctx *ctx, knh_connptr_t *);

typedef struct knh_connptr_drivers_t {
	f_connptr_open  fopen;
	f_connptr_query fquery;
	f_connptr_close fclose;
} knh_connptr_drivers_t;

typedef struct knh_Connection {
	knh_connptr_t  *conn;
	knh_connptr_drivers_t drv;
	knh_String *urn;
} knh_Connection;


/* ------------------------------------------------------------------------ */
/* @class Exception Object knh_ */

typedef struct knh_Exception {
	knh_expt_t eid;
	knh_flag_t flag;
	knh_String* message;
	Object* bag;
	knh_Array* traces;
	char* file;
	int line;
} knh_Exception;

/* ------------------------------------------------------------------------ */
/* @class ExceptionHandler Object knh_ */

typedef struct knh_ExceptionHandler {
	knh_Exception* caught;
	jmp_buf jmpbuf;
} knh_ExceptionHandler;

/* ------------------------------------------------------------------------ */
/* @class System Object knh_ @Tuple */

typedef struct knh_System {
	knh_DictMap* props;
	knh_InputStream* in;
	knh_OutputStream* out;
	knh_OutputStream* err;
	knh_String* rootDir;
} knh_System;

/* ------------------------------------------------------------------------ */
/* @class NameSpace Object knh_ @Tuple */

typedef struct knh_NameSpace {
	struct knh_NameSpace* parent;
	knh_String* nsname;
	knh_Array* imports;
	knh_DictSet* name2cidDictSet;
	knh_DictMap* tag2urnDictMap;
} knh_NameSpace;

/* ------------------------------------------------------------------------ */
/* @class Runtime Object knh_ */

typedef struct knh_Runtime {
	knh_uint_t runtime_id;
	knh_HashMap* tmetaHashMap;
	knh_DictMap* tnameContextDictMap;
	knh_HashMap* tmapmapHashMap;
	knh_HashMap* tmethodHashMap;
	knh_NameSpace* ns;
} knh_Runtime;

/* ------------------------------------------------------------------------ */
/* @class Context Object knh_ */

typedef struct knh_Context {
	knh_Runtime* runtime;
	knh_flag_t flag;
	knh_nsn_t nsn;
	Object** ebp;
	Object** stack;
	knh_uint_t* stackop;
	size_t size;
	knh_String* name;
	knh_InputStream*   in;
	knh_OutputStream*  out;
	knh_OutputStream*  err;
	knh_Bytes*         bufa;
	knh_OutputStream*  bufw;
	knh_DictMap* props;
	Object* cmpl;
	knh_HashMap* cacheIntLRUMap;
	knh_HashMap* cacheStringLRUMap;
	knh_HashMap* cacheFloatLRUMap;
} knh_Context;


/* ------------------------------------------------------------------------ */
/* @class Mutex Object knh_ */

typedef struct knh_Mutex {
	knh_uint_t magic;
	knh_uint_t loccount;
	knh_mutex_t mutex;
} knh_Mutex;

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */

#define KONOHA_TABLE_MAGIC   4219881

/* ------------------------------------------------------------------------ */

typedef struct {
	size_t                size;
	char                 *name;
	f_struct_init         finit;
	f_struct_traverse     ftravr;
	f_struct_compare      fcompr;
	f_struct_copy         fcopy;
} knh_tstruct_t ;

#ifndef KONOHA_TSTRUCT_SIZE
#define KONOHA_TSTRUCT_SIZE 256
#endif

#define TSTRUCTDB_SIZE  (KONOHA_TSTRUCT_SIZE * sizeof(knh_tstruct_t))

/* ------------------------------------------------------------------------ */

typedef ObjectNULL* (*f_value)(Ctx *ctx, knh_class_t cid);

typedef struct {
	knh_uint_t    count;
	knh_flag_t    cflag;
	knh_flag_t    oflag;
	knh_struct_t  topsid;    
	knh_class_t   supcid;
	knh_ushort_t  offset;
	knh_struct_t  sid;    
	knh_index_t   keyidx;
	Object    *name;
	Object    *class;
	Object    *cstruct;
	Object    *crel;
	Object    *spec;
	f_value   fvalue;
} knh_tclass_t;

#ifndef KONOHA_TCLASS_SIZE 
#define KONOHA_TCLASS_SIZE 256
#endif  

#define TCLASSDB_SIZE  (KONOHA_TCLASS_SIZE * sizeof(knh_tclass_t))

#ifndef KONOHA_TFIELDN_SIZE
#define KONOHA_TFIELDN_SIZE 256
#endif

#ifndef KONOHA_TMETHODN_SIZE
#define KONOHA_TMETHODN_SIZE 512
#endif

/* ------------------------------------------------------------------------ */

typedef struct {
	knh_flag_t   flag;
	knh_expt_t   parent;
	Object     *name;
} knh_texpt_t;

#ifndef KONOHA_TEXPT_SIZE
#define KONOHA_TEXPT_SIZE (KONOHA_TCLASS_SIZE/4)
#endif

#define TEXPTDB_SIZE  (KONOHA_TEXPT_SIZE * sizeof(knh_texpt_t))


/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* include generated header file */

#ifdef __cplusplus 
}
#endif

#include"../gen/konoha_.h"
#include"../gen/konoha_tuple_.h"

#endif /*CLASS_KONOHA_H_*/

