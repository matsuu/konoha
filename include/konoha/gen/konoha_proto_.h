/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER  
 * 
 * Copyright (c) 2005-2009, Kimio Kuramitsu <kimio at ynu.ac.jp>
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

#ifndef KONOHA_PROTO__H
#define KONOHA_PROTO__H

#include<konoha/gen/konoha_class_.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

/* ======================================================================== */
/* [PROTOTYPE] */
/* ../src/api/arrayapi.c */
void knh_Array_clear(Ctx *ctx, Array *o);
void knh_Array__k(Ctx *ctx, Array *o, OutputStream *w, String *m);
void knh_IArray__k(Ctx *ctx, IArray *o, OutputStream *w, String *m);
void knh_FArray__k(Ctx *ctx, FArray *o, OutputStream *w, String *m);
MAPPER knh_Array_Iterator(Ctx *ctx, knh_sfp_t *sfp);
MAPPER knh_Iterator_Array(Ctx *ctx, knh_sfp_t *sfp);
MAPPER knh_IArray_Iterator(Ctx *ctx, knh_sfp_t *sfp);
MAPPER knh_FArray_Iterator(Ctx *ctx, knh_sfp_t *sfp);
Mapper *knh_tMapper_newIteratorArray(Ctx *ctx, knh_class_t icid, knh_class_t acid);
Mapper *knh_tMapper_newArrayIterator(Ctx *ctx, knh_class_t acid, knh_class_t icid);
void knh_array_dfree(Ctx *ctx, void *ptr, size_t capacity, size_t usize);
void knh_Iterator__k(Ctx *ctx, Iterator *o, OutputStream *w, String *m);
/* ../src/api/dbapi.c */
int knh_ResultSet_indexof_(Ctx *ctx, knh_sfp_t *sfp);
/* ../src/api/hashapi.c */
void knh_HashMap__k(Ctx *ctx, knh_Hash_t *o, OutputStream *w, String *m);
void knh_HashMap__dump(Ctx *ctx, HashMap *o, OutputStream *w, String *m);
MAPPER knh_HashMap_Iterator(Ctx *ctx, knh_sfp_t *sfp);
/* ../src/api/objectapi.c */
void knh_Method__s(Ctx *ctx, Method *o, OutputStream *w, String *m);
void knh_Method__k(Ctx *ctx, Method *o, OutputStream *w, String *m);
void knh_Method__dump(Ctx *ctx, Method *o, OutputStream *w, String *m);
/* ../src/api/streamapi.c */
void knh_OutputStream__k(Ctx *ctx, OutputStream *o, OutputStream *w, String *m);
METHOD knh__Socket_new(Ctx *ctx, knh_sfp_t *sfp);
METHOD knh__Socket_getInputStream(Ctx *ctx, knh_sfp_t *sfp);
METHOD knh__Socket_getOutputStream(Ctx *ctx, knh_sfp_t *sfp);
METHOD knh__Socket_close(Ctx *ctx, knh_sfp_t *sfp);
METHOD knh__Socket_isClosed(Ctx *ctx, knh_sfp_t *sfp);
void knh_InputStream_setEncoding(Ctx *ctx, InputStream *o, String *enc);
void knh_OutputStream_setEncoding(Ctx *ctx, OutputStream *o, String *enc);
/* ../src/api/stringapi.c */
size_t bconv__toLower(Ctx *ctx, BytesConv *o, knh_bytes_t t, knh_Bytes_t *ba);
size_t bconv__toUpper(Ctx *ctx, BytesConv *o, knh_bytes_t t, knh_Bytes_t *ba);
Array *knh_Regex_split(Ctx *ctx, Regex *o, String *s);
void knh_Regex__s(Ctx *ctx, Regex *o, OutputStream *w, String *m);
/* ../src/api/systemapi.c */
METHOD knh__System_setRandomSeed(Ctx *ctx, knh_sfp_t *sfp);
Object* knh_Context_getProperty(Ctx *ctx, Context *b, knh_bytes_t key);
void knh_Context_setProperty(Ctx *ctx, Context *b, String *key, Any *value);
void knh_System__k(Ctx *ctx, System *o, OutputStream *w, String *m);
void knh_System__dump(Ctx *ctx, System *o, OutputStream *w, String *m);
void knh_Context_setEncoding(Ctx *ctx, knh_Context_t *o, String *enc);
/* ../src/class/knh_Array.c */
size_t knh_array_newsize(size_t newsize, size_t usize);
size_t knh_array_index0(Ctx *ctx, knh_intptr_t n, size_t size);
size_t knh_array_index(Ctx *ctx, knh_intptr_t n, size_t size);
void knh_Array_grow(Ctx *ctx, Array *a, size_t newsize, Object *v);
knh_Array_t* new_Array0(Ctx *ctx, size_t capacity);
Object** knh_Array_list(Array *o);
Object* knh_Array_last(Array *o);
void knh_Array_subclear(Ctx *ctx, Array *o, size_t n);
void knh_Array_addArray(Ctx *ctx, Array *o, Array *other);
void knh_Array_remove(Ctx *ctx, Array *o, size_t n);
Any* knh_Array_pop(Ctx *ctx, Array *o);
/* ../src/class/knh_Bytes.c */
size_t knh_bytes_newsize(size_t s);
void knh_Bytes_unputc(Bytes *o);
/* ../src/class/knh_bytes_t.c */
size_t knh_size(size_t s);
knh_bytes_t knh_bytes_subset(knh_bytes_t t, size_t s, size_t e);
knh_bytes_t knh_bytes_offlen(knh_bytes_t t, size_t off, size_t len);
knh_bytes_t knh_bytes_trim(knh_bytes_t t /*, knh_intptr_t ch*/);
int knh_bytes_parseint(knh_bytes_t t, knh_int_t *value);
int knh_bytes_parsefloat(knh_bytes_t t, knh_float_t *value);
/* ../src/class/knh_BytesConv.c */
size_t knh_BytesConv_conv(Ctx *ctx, BytesConv *o, knh_bytes_t t, knh_Bytes_t *ba);
iconv_t knh_iconv_open(Ctx *ctx, char *to, char *from);
void knh_iconv_close(Ctx *ctx, iconv_t cd);
BytesConv* new_BytesConv__iconv(Ctx *ctx, char *from, char *to);
BytesConv* new_BytesConv__in(Ctx *ctx, char *from);
BytesConv* new_BytesConv__out(Ctx *ctx, char *to);
String *new_String__bconv(Ctx *ctx, knh_bytes_t t, BytesConv *bc);
String *new_String__cwbconv(Ctx *ctx, knh_cwb_t cwb, BytesConv *bc);
void knh_OutputStream_write__bconv(Ctx *ctx, OutputStream *w, knh_bytes_t t);
/* ../src/class/knh_Class.c */
knh_struct_t knh_StructTable_newId(Ctx *ctx);
knh_class_t knh_ClassTable_newId(Ctx *ctx);
void konoha_setClassName(Ctx *ctx, knh_class_t cid, String *lname);
char *knh_ClassTable_CLASSN(Ctx *ctx, knh_class_t cid);
void konoha_setClassDefaultValue(Ctx *ctx, knh_class_t cid, Object *value, knh_fdefault fdefault);
Object *konoha_getClassDefaultValue(Ctx *ctx, knh_class_t cid);
Object *konoha_getDefaultValue(Ctx *ctx, knh_type_t type);
void konoha_setClassParam(Ctx *ctx, knh_class_t cid, knh_class_t p1, knh_class_t p2);
knh_class_t konoha_addGenericsClass(Ctx *ctx, knh_class_t cid, String *name, knh_class_t bcid, knh_class_t p1, knh_class_t p2);
ClassStruct* new_ClassStruct0(Ctx *ctx, int field_size, int method_size);
knh_index_t knh_Class_indexOfField(Ctx *ctx, knh_class_t cid, knh_fieldn_t fn);
knh_index_t knh_Class_queryField(Ctx *ctx, knh_class_t cid, knh_fieldn_t fnq);
knh_cfield_t *knh_Class_fieldAt(Ctx *ctx, knh_class_t cid, size_t n);
void knh_cfield_dump(Ctx *ctx, knh_cfield_t *f, size_t offset, size_t fsize, OutputStream *w);
ClassMap* new_ClassMap0(Ctx *ctx, knh_ushort_t capacity);
int knh_ClassMap_isDefault(Ctx *ctx, ClassMap *o);
void knh_ClassTable_readyClassMap(Ctx *ctx, knh_class_t cid);
void knh_ClassMap_resize(Ctx *ctx, ClassMap *o, size_t newsize);
int knh_ClassMap_util_cmp(const Mapper *m1, const Mapper *m2);
void knh_ClassMap_sort(Ctx *ctx, ClassMap *o);
void knh_ClassMap_add(Ctx *ctx, ClassMap *o, Mapper *map);
void knh_ClassMap__dump(Ctx *ctx, ClassMap *o, OutputStream *w, String *m);
void knh_ClassMap__man(Ctx *ctx, ClassMap *o, OutputStream *w, knh_class_t cid);
Array* konoha_getClassDomain(Ctx *ctx, knh_class_t cid);
/* ../src/class/knh_ClassSpec.c */
void knh_write_intx(Ctx *ctx, OutputStream *w, ClassSpec *u, knh_int_t v);
void knh_write_floatx(Ctx *ctx, OutputStream *w, ClassSpec *u, knh_float_t v);
void knh_ClassSpec_reuse(Ctx *ctx, ClassSpec *u, knh_class_t cid);
knh_bytes_t konoha_getURNAlias(Ctx *ctx, knh_bytes_t aurn);
ClassSpec *konoha_getClassSpec(Ctx *ctx, knh_class_t cid);
knh_class_t konoha_findcidx(Ctx *ctx, knh_bytes_t lname);
/* ../src/class/knh_Closure.c */
METHOD knh__Closure_new(Ctx *ctx, knh_sfp_t *sfp);
METHOD knh__Closure_invoke(Ctx *ctx, knh_sfp_t *sfp);
METHOD knh__Closure_callcc(Ctx *ctx, knh_sfp_t *sfp);
knh_class_t konoha_addClosureClass(Ctx *ctx, knh_class_t cid, String *name, knh_type_t r0, knh_type_t p1, knh_type_t p2, knh_type_t p3);
knh_class_t knh_class_Closure(Ctx *ctx, knh_type_t r0, knh_type_t p1, knh_type_t p2, knh_type_t p3);
knh_class_t knh_class_MethodClosure(Ctx *ctx, knh_class_t cid, Method *mtd);
/* ../src/class/knh_Connection.c */
void knh_Connection_open(Ctx *ctx, Connection *o, String *urn);
Connection* new_Connection(Ctx *ctx, String *urn);
void knh_Connection_close(Ctx *ctx, Connection *o);
/* ../src/class/knh_Context.c */
void knh_Context_clearstack(Ctx *ctx);
/* ../src/class/knh_cwb_t.c */
knh_cwb_t new_cwb(Ctx* ctx);
size_t knh_cwb_size(knh_cwb_t cwb);
knh_bytes_t knh_cwb_tobytes(knh_cwb_t cwb);
char *knh_cwb_tochar(knh_cwb_t cwb);
void knh_cwb_clear(knh_cwb_t cwb);
String *new_String__cwb(Ctx *ctx, knh_cwb_t cwb);
String *new_StringX__cwb(Ctx *ctx, knh_class_t cid, knh_cwb_t cwb);
/* ../src/class/knh_DictIdx.c */
DictIdx* new_DictIdx0(Ctx *ctx, size_t init, knh_intptr_t offset);
DictIdx* new_DictIdx0__ignoreCase(Ctx *ctx, size_t init, knh_intptr_t offset);
size_t knh_DictIdx_size(DictIdx *o);
knh_index_t knh_DictIdx_index(Ctx *ctx, DictIdx *o, knh_bytes_t v);
knh_index_t knh_DictIdx_add__fast(Ctx *ctx, DictIdx *o, String *term);
knh_index_t knh_DictIdx_add(Ctx *ctx, DictIdx *o, String *term);
knh_index_t knh_DictIdx_add__b(Ctx *ctx, DictIdx *o, knh_bytes_t term);
String* knh_DictIdx_get__fast(DictIdx *o, knh_intptr_t termid);
String* knh_DictIdx_get(Ctx *ctx, DictIdx *o, knh_intptr_t termid);
void knh_DictIdx_clear(Ctx *ctx, DictIdx *o);
void knh_DictIdx__k(Ctx *ctx, DictIdx *o, OutputStream *w, String *m);
/* ../src/class/knh_DictMapSet.c */
knh_dict_t* knh_dict_resize(Ctx *ctx, knh_dict_t *a, size_t newsize);
void knh_dict_traverse(Ctx *ctx, knh_dict_t *a, knh_ftraverse ftr);
void knh_DictMap_sort(DictMap *o);
void knh_DictSet_sort(DictSet *o);
void knh_DictMap_toIgnoreCase(DictMap *o);
void knh_DictSet_toIgnoreCase(DictSet *o);
knh_dict_t *knh_dictmap_malloc(Ctx *ctx, size_t init);
DictMap* new_DictMap0(Ctx *ctx, knh_intptr_t capacity);
DictMap* new_DictMap(Ctx *ctx, knh_class_t p1, knh_intptr_t capacity);
size_t knh_DictMap_size(DictMap *o);
String* knh_DictMap_keyAt(DictMap *o, size_t n);
Object* knh_DictMap_valueAt(DictMap *o, size_t n);
void knh_DictMap_removeAt(Ctx *ctx, DictMap *o, size_t n);
knh_index_t knh_DictMap_index__b(DictMap *o, knh_bytes_t key);
String *new_String__DictMap(Ctx *ctx, DictMap *o, knh_bytes_t key);
Object *knh_DictMap_get__b(Ctx *ctx, DictMap *o, knh_bytes_t key);
Object *knh_DictMap_get(Ctx *ctx, DictMap *o, String *key);
void knh_DictMap_append(Ctx *ctx, DictMap *o, String *key, Any *value);
void knh_DictMap_set(Ctx *ctx, DictMap *o, String *key, Any *v);
void knh_DictMap_remove(Ctx *ctx, DictMap *o, String *key);
void knh_DictMap_clear(Ctx *ctx, DictMap *o);
knh_dict_t *knh_dictset_malloc(Ctx *ctx, size_t init);
DictSet* new_DictSet0(Ctx *ctx, knh_intptr_t capacity);
size_t knh_DictSet_size(DictSet *o);
String* knh_DictSet_keyAt(DictSet *o, size_t n);
knh_uintptr_t knh_DictSet_valueAt(DictSet *o, size_t n);
void knh_DictSet_removeAt(Ctx *ctx, DictSet *o, size_t n);
String *new_String__DictSet(Ctx *ctx, DictSet *o, knh_bytes_t key);
knh_uintptr_t knh_DictSet_get__b(DictSet *o, knh_bytes_t key);
knh_uintptr_t knh_DictSet_get(Ctx *ctx, DictSet *o, String *key);
void knh_DictSet_append(Ctx *ctx, DictSet *o, String *key, knh_uintptr_t n);
void knh_DictSet_set(Ctx *ctx, DictSet *o, String *key, knh_uintptr_t n);
void knh_DictSet_add(Ctx *ctx, DictSet *o, String *key);
void knh_DictSet_remove(Ctx *ctx, DictSet *o, String *key);
void knh_DictSet_clear(Ctx *ctx, DictSet *o);
/* ../src/class/knh_Exception.c */
String *knh_ExptTable_name(Ctx *ctx, knh_expt_t eid);
knh_expt_t konoha_addException(Ctx *ctx, knh_flag_t flag, knh_class_t eid, String *name, char *pname);
Exception* knh_Exception_new__init(Ctx *ctx, Exception *o, String *e, String *msg, Object *bag);
int knh_Exception_isa(Ctx *ctx, Exception *o, String *msg);
Exception* new_NullException (Ctx *ctx, Object *o);
ExceptionHandler* new_ExceptionHandler(Ctx *ctx);
void knh_ExceptionHandler_longjmp(Ctx *ctx, ExceptionHandler *o, Exception *e);
Exception* knh_ExceptionHandler_getCaughtException(ExceptionHandler *o);
/* ../src/class/knh_Hash.c */
knh_hashentry_t *new_hashentry(Ctx *ctx, knh_Hash_t *o);
void knh_hashentry_collect(Ctx *ctx, knh_Hash_t *o, knh_hashentry_t *e);
knh_hashentry_t *knh_hashentry_at(knh_Hash_t *o, size_t n);
HashMap* new_HashMap(Ctx *ctx, char *name, size_t capacity);
knh_hashentry_t *knh_Hash_get__hcode(Ctx *ctx, knh_Hash_t *o, knh_hcode_t hcode);
Object *knh_HashMap_get__hcode(Ctx *ctx, HashMap *o, knh_hcode_t hcode);
knh_uintptr_t knh_HashSet_get__hcode(Ctx *ctx, HashSet *o, knh_hcode_t hcode);
void knh_Hash_remove__hcode(Ctx *ctx, knh_Hash_t *o, knh_hcode_t hcode);
void knh_Hash_rehash(Ctx *ctx, knh_Hash_t *o);
void knh_HashMap_set__hcode(Ctx *ctx, HashMap *o, knh_hcode_t hcode, Any *value);
void knh_HashSet_set__hcode(Ctx *ctx, HashSet *o, knh_hcode_t hcode, knh_uintptr_t uvalue);
/* ../src/class/knh_InputStream.c */
Object *knh_InputStream_open(Ctx *ctx, InputStream *o, String *urn, String *m);
int knh_InputStream_getc(Ctx *ctx, InputStream *o);
size_t knh_InputStream_read(Ctx *ctx, InputStream *o, char *buf, size_t bufsiz);
String* knh_InputStream_readLine(Ctx *ctx, InputStream *o);
void knh_InputStream_close(Ctx *ctx, InputStream *o);
int knh_InputStream_isClosed(InputStream *o);
MAPPER knh_Bytes_InputStream(Ctx *ctx, knh_sfp_t *sfp);
/* ../src/class/knh_Iterator.c */
void knh_Iterator_close(Ctx *ctx, Iterator *it);
Iterator* new_Iterator(Ctx *ctx, knh_class_t p1, Any *source, knh_fitrnext fnext);
Iterator* new_ArrayIterator(Ctx *ctx, knh_class_t cid, Array *a);
/* ../src/class/knh_Mapper.c */
Mapper* new_MapMap(Ctx *ctx, Mapper *m1, Mapper *m2);
void knh_Mapper__k(Ctx *ctx, Mapper *o, OutputStream *w, String *m);
void konoha_addMapperFunc(Ctx *ctx, knh_flag_t flag, knh_type_t stype, knh_type_t ttype, knh_fmapper fmap, Object *mapdata);
MAPPER knh_Mapper_fasis(Ctx *ctx, knh_sfp_t *sfp);
MAPPER knh_fmapper_null(Ctx *ctx, knh_sfp_t *sfp);
knh_bool_t knh_Mapper_isNoSuchMapping(Mapper *mpr);
Mapper *konoha_findMapper_(Ctx *ctx, knh_class_t scid, knh_class_t tcid, int isgen);
/* ../src/class/knh_Method.c */
MethodField* new_MethodField(Ctx *ctx, knh_type_t rtype, size_t psize);
knh_hcode_t knh_mparam_hcode(knh_hcode_t h, knh_type_t type, knh_fieldn_t fn);
void knh_MethodField_set(MethodField *o, size_t n, knh_type_t type, knh_fieldn_t fn);
knh_type_t knh_MethodField_pztype(MethodField *o, size_t n);
knh_mparam_t knh_MethodField_param(MethodField *o, size_t n);
knh_type_t knh_Method_rtype(Ctx *ctx, Method *mtd, knh_class_t cid);
knh_type_t knh_Method_ptype(Ctx *ctx, Method *o, knh_class_t cid, size_t n);
knh_mparam_t knh_Method_param(Method *o, size_t n);
int knh_MethodField_equalsType(MethodField *o, MethodField *o2);
METHOD knh_fmethod_abstract(Ctx *ctx, knh_sfp_t *sfp);
knh_bool_t knh_Method_isAbstract(Method *o);
void knh_Method_toAbstract(Ctx *ctx, Method *o);
void knh_Method_syncfunc(Method *o, knh_fmethod f);
Method* new_Method(Ctx *ctx, knh_flag_t flag, knh_class_t cid, knh_methodn_t mn, knh_fmethod func);
knh_bool_t knh_Method_isNoSuchMethod(Method *o);
Method* new_Method__NoSuchMethod(Ctx *ctx, knh_class_t cid, knh_methodn_t mn);
int knh_methodn_isNew(Ctx *ctx, knh_methodn_t mn);
int knh_Method_isConstructor(Ctx *ctx, Method *o);
int knh_methodn_isOp(Ctx *ctx, knh_methodn_t mn);
String* knh_Method_getName(Ctx *ctx, Method *o);
int knh_Method_isWoven(Method *mtd);
int knh_Method_canWeave(Ctx *ctx, Method *mtd, Method *aspect);
void knh_Method_weave(Ctx *ctx, Method *aspect, Method *mtd);
void knh_Class_addMethod(Ctx *ctx, knh_class_t cid, Method *mtd);
void konoha_addMethodFieldTable(Ctx *ctx, MethodField *mf);
MethodField *konoha_findMethodField0(Ctx *ctx, knh_type_t rtype);
MethodField *konoha_findMethodField1(Ctx *ctx, knh_type_t rtype, knh_type_t p1, knh_fieldn_t fn1);
Method* knh_Class_getMethod__(Ctx *ctx, knh_class_t this_cid, knh_methodn_t mn, knh_bool_t gen);
Method *konoha_lookupMethod(Ctx *ctx, knh_class_t cid, knh_methodn_t mn);
Method *konoha_lookupFormatter(Ctx *ctx, knh_class_t cid, knh_methodn_t mn);
/* ../src/class/knh_NameSpace.c */
NameSpace* new_NameSpace(Ctx *ctx, String *nsname);
void knh_NameSpace_importNameSpace(Ctx *ctx, NameSpace *ns, NameSpace *other);
Script *knh_NameSpace_getScript(Ctx *ctx, NameSpace *ns);
knh_class_t konoha_getcid(Ctx *ctx, knh_bytes_t lname);
void knh_NameSpace_setcid(Ctx *ctx, NameSpace *o, String *name, knh_class_t c);
void knh_NameSpace_setLocalName(Ctx *ctx, NameSpace *o, knh_class_t cid);
knh_class_t knh_NameSpace_getcid(Ctx *ctx, NameSpace *o, knh_bytes_t name);
char* knh_Context_CLASSN(Ctx *ctx, knh_class_t cid);
void knh_NameSpace_importClass(Ctx *ctx, NameSpace *o, knh_bytes_t pkgname);
knh_type_t knh_NameSpace_gettype(Ctx *ctx, NameSpace *ns, knh_bytes_t name, int isNullable);
Object * knh_NameSpace_getConstNULL(Ctx *ctx, NameSpace *ns, knh_bytes_t name);
void knh_NameSpace_addConst(Ctx *ctx, NameSpace *ns, String *name, Object *value);
void knh_NameSpace_setFuncClass(Ctx *ctx, NameSpace *o, knh_methodn_t mn, knh_class_t c);
knh_class_t knh_NameSpace_getFuncClass(Ctx *ctx, NameSpace *o, knh_bytes_t funcname);
knh_type_t knh_NameSpace_tagcid(Ctx *ctx, NameSpace *o, knh_class_t cid, knh_bytes_t tag);
/* ../src/class/knh_Number.c */
knh_int_t knh_Number_tointeger(Any *o);
knh_float_t knh_Number_tofloat(Any *o);
/* ../src/class/knh_Object.c */
METHOD knh__Object_new(Ctx *ctx, knh_sfp_t *sfp);
String *knh_Object_getkey(Ctx *ctx, Object *o);
METHOD knh__Object_getKey(Ctx *ctx, knh_sfp_t *sfp);
Object *knh_Object_copy(Ctx *ctx, Object *b);
knh_hcode_t knh_Object_hashCode(Ctx *ctx, Object *o);
int knh_Object_compareTo(Ctx *ctx, Object *o1, Object *o2);
int knh_Object_cmp(Object *o1, Object *o2);
knh_bool_t knh_Object_equals(Ctx *ctx, Object *o1, Object *o2);
knh_bytes_t knh_Object_tobytes(Ctx *ctx, Object *o);
/* ../src/class/knh_OutputStream.c */
Object *knh_OutputStream_open(Ctx *ctx, OutputStream *o, String *urn, String *m);
void knh_OutputStream_putc(Ctx *ctx, OutputStream *o, knh_int_t ch);
void knh_OutputStream_write(Ctx *ctx, OutputStream *o, knh_bytes_t buf);
void knh_OutputStream_flush(Ctx *ctx, OutputStream *o);
void knh_OutputStream_clear(Ctx *ctx, OutputStream *o);
void knh_OutputStream_close(Ctx *ctx, OutputStream *o);
int knh_OutputStream_isClosed(OutputStream *o);
void knh_OutputStream_indent_inc(Ctx *ctx, OutputStream *o);
void knh_OutputStream_indent_dec(Ctx *ctx, OutputStream *o);
void knh_OutputStream_write_indent(Ctx *ctx, OutputStream *o);
void knh_OutputStream_print_(Ctx *ctx, OutputStream *o, knh_bytes_t str, knh_bool_t isnl);
/* ../src/class/knh_ResultSet.c */
ResultSet* new_ResultSet(Ctx *ctx);
knh_boolean_t knh_ResultSet_next(Ctx *ctx, ResultSet *o);
METHOD knh__ResultSet_next(Ctx *ctx, knh_sfp_t *sfp);
void knh_ResultSet_close(Ctx *ctx, ResultSet *o);
void knh_ResultSet_initTargetClass(ResultSet *o, knh_class_t tcid);
String *knh_ResultSet_getName(Ctx *ctx, ResultSet *o, size_t n);
int knh_ResultSet_findColumn(Ctx *ctx, ResultSet *o, knh_bytes_t name);
knh_type_t knh_ResultSet_get_type(Ctx *ctx, ResultSet *o, size_t n);
knh_int_t knh_ResultSet_getInt(Ctx *ctx, ResultSet *o, size_t n);
knh_float_t knh_ResultSet_getFloat(Ctx *ctx, ResultSet *o, size_t n);
String* knh_ResultSet_getString(Ctx *ctx, ResultSet *o, size_t n);
/* ../src/class/knh_Script.c */
Script *new_Script(Ctx *ctx, knh_bytes_t nsname);
void knh_Script__k(Ctx *ctx, Script *o, OutputStream *w, String *m);
void knh_Script__dump(Ctx *ctx, Script *o, OutputStream *w, String *m);
/* ../src/class/knh_String.c */
knh_hcode_t knh_uchar_hcode(knh_hcode_t h, knh_uchar_t *buf, size_t len);
void knh_String_checkASCII(String *o);
knh_String_t *new_StringX__T(Ctx *ctx, knh_class_t cid, const char *text);
String *new_StringX__fast(Ctx *ctx, knh_class_t cid, knh_bytes_t t, String *orign);
String *new_StringX(Ctx *ctx, knh_class_t cid, knh_bytes_t t, String *orign);
String *new_String__int(Ctx *ctx, knh_int_t n);
String *new_String__float(Ctx *ctx, knh_float_t n);
knh_bool_t knh_String_equals(String *o, knh_bytes_t s);
knh_bool_t knh_String_startsWith(String *b, knh_bytes_t s);
knh_bool_t knh_String_endsWith(String *b, knh_bytes_t s);
Object* new_String_parseOf(Ctx *ctx, String *p);
int knh_bytes_splitTag(knh_bytes_t t, knh_bytes_t *tag, knh_bytes_t *body);
Object *new_Object_parseOf(Ctx *ctx, String *s);
/* ../src/class/knh_String_mbytes.c */
knh_bool_t knh_bytes_checkENCODING(knh_bytes_t s);
size_t knh_bytes_mlen(knh_bytes_t s);
knh_bytes_t knh_bytes_mofflen(knh_bytes_t m, size_t moff, size_t mlen);
knh_int_t knh_uchar_toucs4(knh_uchar_t *utf8);
char *knh_format_utf8(char *buf, size_t bufsiz, knh_int_t ucs4);
/* ../src/class/knh_System.c */
char * knh_bytes_nzenvkey(knh_bytes_t t, char *buf, size_t bufsiz);
Any* knh_System_getProperty(Ctx *ctx, System *o, knh_bytes_t key);
void knh_System_setProperty(Ctx *ctx, System *o, String *key, Any *value);
knh_bool_t konoha_initcheck(void);
/* ../src/class/knh_type_t.c */
knh_class_t knh_pmztype_toclass(Ctx *ctx, knh_type_t t, knh_class_t this_cid);
knh_type_t knh_pmztype_totype(Ctx *ctx, knh_type_t t, knh_class_t this_cid);
knh_class_t knh_class_Array(Ctx *ctx, knh_class_t p1);
knh_class_t knh_class_Iterator(Ctx *ctx, knh_class_t p1);
knh_class_t knh_class_Generics(Ctx *ctx, knh_class_t bcid, knh_class_t p1, knh_class_t p2);
char* knh_format_type(Ctx *ctx, char *buf, size_t bufsiz, knh_type_t type);
char *TYPEQ(knh_type_t type);
char *knh_TYPEN(Ctx *ctx, knh_type_t type);
/* ../src/class/knh_write.c */
void knh_write__s(Ctx *ctx, OutputStream *w, char *s);
void knh_write__p(Ctx *ctx, OutputStream *w, void *ptr);
void knh_write__ifmt(Ctx *ctx, OutputStream *w, char *fmt, knh_intptr_t n);
void knh_write__ffmt(Ctx *ctx, OutputStream *w, char *fmt, knh_float_t n);
void knh_write_integerfmt(Ctx *ctx, OutputStream *w, char *fmt, knh_int_t n);
void knh_write__flag(Ctx *ctx, OutputStream *w, knh_flag_t flag);
void knh_write_cid(Ctx *ctx, OutputStream *w, knh_class_t cid);
void knh_write_mn(Ctx *ctx, OutputStream *w, knh_methodn_t mn);
void knh_write_type(Ctx *ctx, OutputStream *w, knh_type_t type);
void knh_write_fline(Ctx *ctx, OutputStream *w, char *file, int line);
void knh_vprintf(Ctx *ctx, OutputStream *w, char *fmt, va_list ap);
void konoha_setverbose(int v);
METHOD knh_fmethod_movableText(Ctx *ctx, knh_sfp_t *sfp);
/* ../src/compiler/asm.c */
Asm* knh_Context_getAsm(Ctx *ctx);
NameSpace *knh_Context_getNameSpace(Ctx *ctx);
NameSpace *knh_Context_setNameSpace(Ctx *ctx, String *nsname);
NameSpace *knh_Context_switchNameSpace(Ctx *ctx, NameSpace *newns);
Script *knh_Asm_getScript(Ctx *ctx, Asm *o);
void knh_Asm_initThis(Ctx *ctx, Asm *abr, knh_class_t cid);
void knh_Asm_initThisScript(Ctx *ctx, Asm *abr);
void *knh_Asm_asmmalloc(Ctx *ctx, Asm *abr, size_t size);
void knh_Asm_rewind(Ctx *ctx, Asm *abr);
void KNH_ASM_SETLINE(Ctx *ctx, Asm *abr, int line);
void knh_StmtALT_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx);
void knh_StmtOR_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx);
void knh_StmtAND_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx);
void knh_StmtTRI_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx);
void knh_StmtLET_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx);
void knh_StmtEXPR_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx);
void knh_StmtPRINT_asm(Ctx *ctx, Stmt *stmt, Asm *abr);
void knh_StmtASSERT_asm(Ctx *ctx, Stmt *stmt, Asm *abr);
void knh_Stmt_asmBLOCK(Ctx *ctx, Stmt *stmt, Asm *abr, int isIteration);
void KNH_ASM_METHOD(Ctx *ctx, Asm *abr, Method *mtd, Stmt *params, Stmt *body, int isIteration);
void knh_StmtMETHOD_asm(Ctx *ctx, Stmt *stmt, Asm *abr);
void knh_StmtFORMAT_asm(Ctx *ctx, Stmt *stmt, Asm *abr);
void knh_StmtCLASS_asm(Ctx *ctx, Stmt *stmt, Asm *abr);
/* ../src/compiler/kcode.c */
KLRCode* new_KLRCode(Ctx *ctx, knh_fileid_t fileid, knh_bytes_t elf, knh_bytes_t dwarf);
void knh_Method_setKLRCode(Ctx *ctx, Method *mtd, KLRCode *code);
knh_code_t* knh_Method_pcstartNULL(Method *mtd);
knh_bytes_t knh_KLRCode_tobytes(KLRCode *o);
char *knh_Method_file(Ctx *ctx, Method *mtd);
int knh_Method_pctoline(Method *mtd, knh_code_t *pc);
int knh_Asm_constId(Ctx *ctx, Asm *abr, Object *o);
int knh_Asm_classId(Ctx *ctx, Asm *abr, knh_class_t cid);
void knh_Int__const(Ctx *ctx, Int *o, OutputStream *w, String *m);
void knh_Method__const(Ctx *ctx, Method *o, OutputStream *w, String *m);
void knh_Method__c(Ctx *ctx, Method *mtd, OutputStream *w, String *m);
void knh_Asm_genMethod(Ctx *ctx, Asm *abr, OutputStream *w);
void knh_Asm_loadCompiledMethod(Ctx *ctx, Asm *abr);
knh_fmethod knh_Asm_getCompiledMethod(Ctx *ctx, Asm *abr, knh_bytes_t cname, knh_bytes_t mname);
/* ../src/compiler/konohac.c */
int knh_Stmt_compile(Ctx *ctx, Stmt *stmt, String *nsname, int isEval);
Stmt *knh_bytes_parseStmt(Ctx *ctx, knh_bytes_t kscript, int fileid, int line);
void konohac_eval(Ctx *ctx, String *nsname, InputStream *in);
void knh_Asm_openlib(Ctx *ctx, Asm *abr, knh_bytes_t fpath);
int knh_NameSpace_loadScript(Ctx *ctx, NameSpace *ns, knh_bytes_t fpath, int isEval);
void konoha_compile(Ctx *ctx, String *nsname, knh_bytes_t fpath);
/* ../src/compiler/parser.c */
Stmt *new_StmtINSTMT(Ctx *ctx, Token *tk);
void knh_Stmt_add_PEACH(Ctx *ctx, Stmt *o, knh_tokens_t *tc);
/* ../src/compiler/perror.c */
void knh_vperror(Ctx *ctx, knh_fileid_t fileid, int line, int pe, char *fmt, va_list ap);
void knh_perror(Ctx *ctx, knh_fileid_t fileid, int line, int pe, char *fmt, ...);
void knh_Token_perror(Ctx *ctx, Token *tk, int pe, char *fmt, ...);
void knh_Asm_perror(Ctx *ctx, Asm *abr, int pe, char *fmt, ...);
/* ../src/compiler/stmt.c */
Stmt* new_Stmt(Ctx *ctx, knh_flag_t flag, knh_stmt_t stt);
void knh_Stmt_toERR(Ctx *ctx, Stmt *stmt, Term *tm);
void knh_Stmt_add(Ctx *ctx, Stmt *o, Term *tm);
Stmt *knh_Stmt_tail(Ctx *ctx, Stmt *o);
Stmt* knh_StmtNULL_tail_append(Ctx *ctx, Stmt *o, Stmt *stmt);
knh_bool_t knh_Stmt_hasMeta(Stmt *o);
knh_flag_t knh_StmtMETHOD_flag(Ctx *ctx, Stmt *o);
knh_flag_t knh_Stmt_metaflag__field(Ctx *ctx, Stmt *b);
knh_flag_t knh_StmtPRINT_flag(Ctx *ctx, Stmt *o);
knh_bool_t knh_StmtMETA_isOverride(Ctx *ctx, Stmt *o);
int knh_StmtMETA_is(Ctx *ctx, Stmt *stmt, knh_bytes_t name);
void knh_Stmt__s(Ctx *ctx, Stmt *o, OutputStream *w, String *m);
void knh_Stmt__dump(Ctx *ctx, Stmt *o, OutputStream *w, String *m);
/* ../src/compiler/token.c */
Token* new_Token(Ctx *ctx, knh_flag_t flag, knh_fileid_t fileid, knh_sline_t line, knh_token_t tt);
void knh_Token_setFL(Token *o, Any *fln);
Token *new_TokenASIS(Ctx *ctx, Any *fln);
Token *new_TokenCID(Ctx *ctx, Any *fln, knh_class_t cid);
Token *new_TokenMN(Ctx *ctx, Any *fln, knh_methodn_t mn);
Token *new_TokenFN(Ctx *ctx, Any *fln, knh_fieldn_t fn);
Token *new_Token__S(Ctx *ctx, Any *fln, knh_token_t tt, String *t);
void knh_Token_tc(Ctx *ctx, Token *o, knh_tokens_t *tc);
void knh_Token_tokens_add(Ctx *ctx, Token *o, Token *tk);
void knh_Token_tokens_empty(Ctx *ctx, Token *o);
char *knh_Token_tochar(Ctx *ctx, Token *o);
knh_bytes_t knh_Token_tobytes(Ctx *ctx, Token *o);
void knh_Token__s(Ctx *ctx, Token *o, OutputStream *w, String *m);
void knh_Token__k(Ctx *ctx, Token *o, OutputStream *w, String *m);
void knh_Token__dump(Ctx *ctx, Token *o, OutputStream *w, String *m);
/* ../src/compiler/tokenizer.c */
String *new_String__NAME(Ctx *ctx, knh_bytes_t tname);
Token *new_Token__NAME(Ctx *ctx, knh_flag_t flag, InputStream *in, knh_bytes_t t);
knh_token_t knh_char_totoken(int ch);
void knh_Token_parse(Ctx *ctx, Token *tk, InputStream *in);
/* ../src/compiler/typing.c */
Token* new_TokenCONST(Ctx *ctx, Any *fln, Any *data);
void knh_Token_setCONST(Ctx *ctx, Token *o, Any *data);
Token* knh_Token_toCONST(Ctx *ctx, Token *o);
Token* new_TokenNULL(Ctx *ctx, Any *fln, knh_type_t type);
knh_index_t knh_Asm_indexOfVariable(Asm *abr, knh_fieldn_t fnq);
int knh_ismtchar(int c);
int knh_bytes_findMT(Ctx *ctx, knh_bytes_t text, knh_bytes_t *mt, knh_bytes_t *expr, knh_bytes_t *next);
int TERMs_isCONST(Stmt *stmt, size_t n);
int TERMs_isTRUE(Stmt *stmt, size_t n);
int TERMs_isFALSE(Stmt *stmt, size_t n);
knh_type_t TERMs_gettype(Stmt *stmt, size_t n);
void knh_Stmt_setType(Ctx *ctx, Stmt *stmt, knh_type_t type);
Term * knh_StmtDECL_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns);
Term *knh_StmtLET_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_type_t reqt);
Term *knh_StmtEXPR_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_class_t reqt);
void knh_Stmt_toBLOCK(Ctx *ctx, Stmt *stmt, size_t n);
void knh_Asm_initReg(Ctx *ctx, Asm *abr);
int knh_Stmt_initParams(Ctx *ctx, Stmt *pstmt, Asm *abr, NameSpace *ns, int level);
Term * knh_StmtMETHOD_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns);
Term *knh_StmtFORMAT_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns);
Term *knh_StmtCLASS_typing(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns);
int knh_Stmt_typingBLOCK(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, int isIteration);
/* ../src/deps/dlopen.c */
void *knh_dlopen(Ctx *ctx, const char* path, int mode);
void *knh_dlsym(Ctx *ctx, void* hdr, const char* symbol);
const char *knh_dlerror(Ctx *ctx);
int knh_dlclose(Ctx *ctx, void* hdr);
/* ../src/deps/fileio.c */
knh_iodrv_t *konoha_getIODriver(Ctx *ctx, knh_bytes_t name);
knh_iodrv_t *konoha_getDefaultIODriver();
void  init_IO(Ctx *ctx);
InputStream *new_InputStream__stdio(Ctx *ctx, FILE *fp, String *enc);
OutputStream *new_OutputStream__stdio(Ctx *ctx, FILE *fp, String *enc);
/* ../src/deps/filesystem.c */
knh_boolean_t knh_isfile(Ctx *ctx, knh_bytes_t path);
knh_boolean_t knh_isdir(Ctx *ctx, knh_bytes_t path);
knh_boolean_t knh_unlink(Ctx *ctx, knh_bytes_t f, int isThrowable);
knh_boolean_t knh_rename(Ctx *ctx, knh_bytes_t on, knh_bytes_t nn, int isThrowable);
char * knh_format_homepath(char *buf, size_t bufsiz);
/* ../src/deps/konoha_locale.c */
char *konoha_encoding();
char *knh_format_lang(char *buf, size_t bufsiz);
/* ../src/deps/regex.c */
void knh_write_USING_REGEX(Ctx *ctx, OutputStream *w);
knh_regex_drvapi_t *knh_System_getRegexDriver(Ctx *ctx, knh_bytes_t name);
void  init_Regex(Ctx *ctx);
/* ../src/deps/socket.c */
knh_iodrv_t *konoha_getSocketDriver();
void  init_SocketDriver(Ctx *ctx);
/* ../src/deps/sqlite3.c */
void knh_dbcurfree__NOP(knh_dbcur_t *dbcur);
void knh_write_USING_SQLITE3(Ctx *ctx, OutputStream *w);
knh_db_drvapi_t *knh_System_getDefaultDBDriver();
knh_db_drvapi_t *knh_System_getDBDriver(Ctx *ctx, knh_bytes_t name);
void  init_DB(Ctx *ctx);
/* ../src/deps/thread.c */
knh_thread_t knh_thread_self();
int thread_create(knh_thread_t *thread, void *attr, void *(*frun)(void *), void * arg);
int knh_thread_key_create(knh_thread_key_t *key);
int knh_thread_setspecific(knh_thread_key_t key, const void *data);
void* knh_thread_getspecific(knh_thread_key_t key);
int knh_thread_key_delete(knh_thread_key_t key);
/* ../src/deps/time.c */
knh_uint_t knh_initseed();
knh_uint64_t konoha_getTimeMilliSecond(void);
knh_uint64_t konoha_getProfCount(void);
knh_uint64_t konoha_getProfCountPerSecond(void);
/* ../src/konoha.c */
int main(int argc, char **argv);
/* ../src/labs/b4.c */
METHOD knh__Script_changeChannel(Ctx *ctx, knh_sfp_t *sfp);
METHOD knh__Script_hook(Ctx *ctx, knh_sfp_t *sfp);
int package_init(Ctx *ctx);
/* ../src/main/classapi.c */
knh_hcode_t knh_MethodField_hachCode(Ctx *ctx, MethodField *o);
size_t knh_fbyteconv_nop(Ctx *ctx, BytesConv *bc, knh_bytes_t t, knh_Bytes_t *ba);
void knh_fbyteconvfree_nop(Ctx *ctx, BytesConv *bc);
void knh_OutputStream_init(Ctx *ctx, OutputStream *out, int init);
void knh_ExceptionHandler_traverse(Ctx *ctx, ExceptionHandler *hdr, knh_ftraverse gc);
void knh_Context_init(Ctx *ctx, knh_Context_t *o, int init);
void knh_Stmt_done(Ctx *ctx, Stmt *o);
/* ../src/main/exports.c */
/* ../src/main/fileutils.c */
char * knh_format_parentpath(char *buf, size_t bufsiz, knh_bytes_t path, int n);
char * knh_format_nzpath(char *buf, size_t bufsiz, knh_bytes_t path);
char * knh_format_catpath(char *buf, size_t bufsiz, knh_bytes_t path, knh_bytes_t file);
/* ../src/main/glue.c */
int knh_fcallback_cmpr(Object *obj, Object *obj2);
void *konoha_generateCallBackFunc(Ctx *ctx, void *func, Closure *c);
/* ../src/main/konoha_api.c */
void konoha_init(void);
int knh_readline_askYesNo(char *prompt, int def);
METHOD knh__Script_eval(Ctx *ctx, knh_sfp_t *sfp);
METHOD knh__Script_isStatement(Ctx *ctx, knh_sfp_t *sfp);
METHOD knh__Script_readLine(Ctx *ctx, knh_sfp_t *sfp);
METHOD knh__Script_addHistory(Ctx *ctx, knh_sfp_t *sfp);
/* ../src/main/konoha_ext.c */
void knh_srand(knh_uint_t seed);
knh_uint_t knh_rand();
knh_float_t knh_float_rand();
/* ../src/main/logging.c */
void knh_stack_pmsg(Ctx *ctx, knh_sfp_t *sfp, knh_flag_t flag, String *s);
void knh_stack_p(Ctx *ctx, knh_sfp_t *sfp, knh_flag_t flag, knh_methodn_t mn, int sfpidx);
int knh_verbose(void);
/* ../src/main/memory.c */
void *knh_malloc(Ctx *ctx, size_t size);
void knh_free(Ctx *ctx, void *block, size_t size);
void *DBG2_malloc(Ctx *ctx, size_t size, char *func);
void DBG2_free(Ctx *ctx, void *p, size_t size, char *func);
int knh_isFastMallocMemory(void *p);
void *knh_fastmalloc(Ctx *ctx, size_t size);
void knh_fastfree(Ctx *ctx, void *block, size_t size);
knh_Object_t *new_hObject(Ctx *ctx, knh_flag_t flag, knh_class_t bcid, knh_class_t cid);
knh_Object_t *new_Object_bcid(Ctx *ctx, knh_class_t bcid, int init);
knh_Object_t *new_Object_init(Ctx *ctx, knh_flag_t flag, knh_class_t cid, int init);
void knh_Object_free(Ctx *ctx, knh_Object_t *o);
void knh_Object_traverse(Ctx *ctx, knh_Object_t *o, knh_ftraverse ftr);
void knh_Object_mark1(Ctx *ctx, Object *o);
METHOD knh__System_gc(Ctx *ctx, knh_sfp_t *sfp);
void knh_System_gc(Ctx *ctx);
void knh_Object_RCsweep(Ctx *ctx, Object *o);
knh_ftraverse konoha_getDefaultSweepFunc();
/* ../src/main/stack.c */
int knh_sfp_argc(Ctx *ctx, knh_sfp_t *v);
METHOD knh__System_stackdump(Ctx *ctx, knh_sfp_t *sfp);
void knh_sfp_typecheck(Ctx *ctx, knh_sfp_t *sfp, Method *mtd, knh_code_t *pc);
/* ../src/main/system.c */
int konoha_addClassConst(Ctx *ctx, knh_class_t cid, String* name, Object *value);
Object *konoha_getClassConstNULL(Ctx *ctx, knh_class_t cid, knh_bytes_t name);
void knh_Const__man(Ctx *ctx, knh_class_t cid, OutputStream *w);
Object *konoha_getSystemConst(Ctx *ctx, int n);
int knh_bytes_isOptionalMT(knh_bytes_t t);
knh_bytes_t knh_bytes_mtoption(knh_bytes_t t);
char *knh_format_newFMT(char *buf, size_t bufsiz, knh_bytes_t t, int dot, char *fmt);
String *konoha_getFieldName(Ctx *ctx, knh_fieldn_t fn);
knh_fieldn_t knh_tName_get_fnq(Ctx *ctx, knh_bytes_t tname, knh_fieldn_t def);
String *new_String__mn(Ctx *ctx, knh_methodn_t mn);
knh_methodn_t konoha_getMethodName(Ctx *ctx, knh_bytes_t tname, knh_methodn_t def);
char *knh_format_methodn(Ctx *ctx, char *buf, size_t bufsiz, knh_methodn_t mn);
char * knh_format_cmethodn(Ctx *ctx, char *buf, size_t bufsiz, knh_class_t cid, knh_methodn_t mn);
knh_fileid_t konoha_getFileId(Ctx *ctx, knh_bytes_t t);
String *konoha_getFileName(Ctx *ctx, knh_fileid_t fileid);
void konoha_addDriverAPI(Ctx *ctx, char *alias, knh_drvapi_t* p);
knh_drvapi_t *konoha_getDriverAPI(Ctx *ctx, int type, knh_bytes_t name);
NameSpace *knh_System_loadPackage(Ctx *ctx, knh_bytes_t pkgname);
NameSpace *knh_System_getNameSpace(Ctx *ctx, knh_bytes_t name);
/* ../src/main/systemtable.c */
Ctx *new_Context(Ctx *parent);
void knh_Context_traverse(Ctx *ctx, knh_Context_t *o, knh_ftraverse ftr);
void konoha_traverse(Ctx* ctx, knh_ftraverse ftr);
/* ../src/main/typesystem.c */
knh_bool_t knh_class_instanceof(Ctx *ctx, knh_class_t scid, knh_class_t tcid);
METHOD knh__Object_opInstanceof(Ctx *ctx, knh_sfp_t *sfp);
knh_bool_t knh_Object_opTypeOf(Ctx *ctx, Object *o, knh_type_t t);
Exception* new_Exception__type(Ctx *ctx, Object *value, knh_type_t spec_type);

#ifdef __cplusplus
}
#endif

/* ======================================================================== */

#endif/*KONOHA_PROTO__H*/
