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

#ifndef KONOHA__H
#define KONOHA__H

#include<konoha/konoha_config.h>
#include<konoha/konoha_t.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

/* ======================================================================== */
/* [prototype] */

/* ../api/konoha/knh_Array_api1.c */
Array* knh_Array_new(Ctx *ctx, Array *b, knh_int_t init);
Array* knh_Array_new__array(Ctx *ctx, Array *b, knh_int_t init, Any *value);
Array* knh_Array_new__init(Ctx *ctx, Array *b, knh_vargc_t n, Any **v);
Any* knh_Array_get__fast(Array *b, size_t index);
void knh_Array_set__fast(Ctx *ctx, Array *b, size_t index, Object *value);
Any* knh_Array_get(Array *b, knh_int_t index);
void knh_Array_set(Ctx *ctx, Array *b, knh_int_t index, Any *value);
/* ../api/konoha/knh_Bytes_api2.c */
Bytes* knh_Bytes_new(Ctx *ctx, Bytes *b, size_t init);
Object* knh_Bytes_String(Ctx *ctx, Object *self, MapMap *map);
Object* knh_String_Bytes(Ctx *ctx, Object *self, MapMap *map);
/* ../api/konoha/knh_Int_api1.c */
METHOD knh__Int_opAdd(Ctx *ctx, Object **sfp);
METHOD knh__Int_opSub(Ctx *ctx, Object **sfp);
METHOD knh__Int_opMul(Ctx *ctx, Object **sfp);
METHOD knh__Int_opDiv(Ctx *ctx, Object **sfp);
METHOD knh__Int_opMod(Ctx *ctx, Object **sfp);
METHOD knh__Int_opEq(Ctx *ctx, Object **sfp);
METHOD knh__Int_opNeq(Ctx *ctx, Object **sfp);
METHOD knh__Int_opLt(Ctx *ctx, Object **sfp);
METHOD knh__Int_opLte(Ctx *ctx, Object **sfp);
METHOD knh__Int_opGt(Ctx *ctx, Object **sfp);
METHOD knh__Int_opGte(Ctx *ctx, Object **sfp);
METHOD knh__Int_opLogicalAnd(Ctx *ctx, Object **sfp);
METHOD knh__Int_opLogicalOr(Ctx *ctx, Object **sfp);
METHOD knh__Int_opLogicalXor(Ctx *ctx, Object **sfp);
METHOD knh__Int_opLogicalNot(Ctx *ctx, Object **sfp);
METHOD knh__Int_opLShift(Ctx *ctx, Object **sfp);
METHOD knh__Int_opRShift(Ctx *ctx, Object **sfp);
Object* knh_String_Int(Ctx *ctx, Object *self, MapMap *map);
Object* knh_Int_String(Ctx *ctx, Object *self, MapMap *map);
void knh_Int__s(Ctx *ctx, Int *b, OutputStream *w, Any *m);
void knh_Int__x(Ctx *ctx, Int *b, OutputStream *w, Any *m);
void knh_Int__bits(Ctx *ctx, Int *b, OutputStream *w, Any *m);
void knh_Int__dump(Ctx *ctx, Int *b, OutputStream *w, Any *m);
/* ../api/konoha/knh_Float_api2.c */
METHOD knh__Float_random(Ctx *ctx, Object **sfp);
/* ../api/konoha/knh_System_api1.c */
METHOD knh__System_getIn(Ctx *ctx, Object **sfp);
METHOD knh__System_setIn(Ctx *ctx, Object **sfp);
METHOD knh__System_getOut(Ctx *ctx, Object **sfp);
METHOD knh__System_setOut(Ctx *ctx, Object **sfp);
METHOD knh__System_getErr(Ctx *ctx, Object **sfp);
METHOD knh__System_setErr(Ctx *ctx, Object **sfp);
/* ../api/konoha/knh_String_api1.c */
METHOD knh__String_opAdd(Ctx *ctx, Object **sfp);
/* ../api/konoha/knh_Bool_api1.c */
METHOD knh__Bool_opEq(Ctx *ctx, Object **sfp);
METHOD knh__Bool_opNeq(Ctx *ctx, Object **sfp);
Object* knh_Bool_String(Ctx *ctx, Object *self, MapMap *map);
void knh_Bool__s(Ctx *ctx, Bool *b, OutputStream *w, Any *m);
/* ../api/konoha/knh_Float_api1.c */
METHOD knh__Float_opAdd(Ctx *ctx, Object **sfp);
METHOD knh__Float_opSub(Ctx *ctx, Object **sfp);
METHOD knh__Float_opMul(Ctx *ctx, Object **sfp);
METHOD knh__Float_opDiv(Ctx *ctx, Object **sfp);
METHOD knh__Float_opEq(Ctx *ctx, Object **sfp);
METHOD knh__Float_opNeq(Ctx *ctx, Object **sfp);
METHOD knh__Float_opLt(Ctx *ctx, Object **sfp);
METHOD knh__Float_opLte(Ctx *ctx, Object **sfp);
METHOD knh__Float_opGt(Ctx *ctx, Object **sfp);
METHOD knh__Float_opGte(Ctx *ctx, Object **sfp);
Object* knh_String_Float(Ctx *ctx, Object *self, MapMap *map);
Object* knh_Float_String(Ctx *ctx, Object *self, MapMap *map);
Object* knh_Int_Float(Ctx *ctx, Object *self, MapMap *map);
Object* knh_Float_Int(Ctx *ctx, Object *self, MapMap *map);
void knh_Float__s(Ctx *ctx, Float *b, OutputStream *w, Any *m);
void knh_Float__dump(Ctx *ctx, Float *b, OutputStream *w, Any *m);
/* ../api/konoha/knh_Connection_api1.c */
METHOD knh__Connection_new(Ctx *ctx, Object **sfp);
METHOD knh__Connection_query(Ctx *ctx, Object **sfp);
/* ../class/konoha/knh_MethodField.c */
void knh_MethodField_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_MethodField_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
knh_int_t knh_MethodField_struct_compare(Ctx *ctx, Struct *s1, Struct *s2);
void knh_MethodField_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
MethodField* new_MethodField(Ctx *ctx, knh_flag_t flag, size_t size);
knh_hcode_t knh_methodfield_hcode(knh_type_t r, knh_type_t a0, knh_type_t a1);
knh_hcode_t knh_MethodField_hcode(MethodField *b);
knh_bool_t knh_MethodField_equalsType(MethodField *b, MethodField *b2);
void knh_MethodField_setVarArgs(MethodField *b);
knh_bool_t knh_MethodField_isVarArgs(MethodField *b);
knh_type_t knh_MethodField_rtype(MethodField *b);
size_t knh_MethodField_psize(MethodField *b);
knh_index_t knh_MethodField_pindex(MethodField *b, knh_fieldn_t fn);
knh_type_t knh_MethodField_ptype(MethodField *b, size_t n);
knh_mfield_t knh_MethodField_pfields(MethodField *b, size_t n);
knh_mfield_t knh_MethodField_lastfield(MethodField *b);
MethodField* new_MethodField__mt(Ctx *ctx);
MethodField* new_MethodField__NoSuchMethod(Ctx *ctx);
MethodField* new_MethodField__PrototypeRun(Ctx *ctx);
/* ../class/konoha/knh_Tuple.c */
void knh_Tuple0_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_Tuple0_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
knh_int_t knh_Tuple0_struct_compare(Ctx *ctx, Struct *s1, Struct *s2);
void knh_Tuple0_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
void knh__Tuple_get_field(Ctx *ctx, Object **sf);
void knh__Tuple_set_field(Ctx *ctx, Object **sf);
Tuple* knh_Tuple_new(Ctx *ctx, Tuple *b, knh_vargc_t ac, Any **value);
size_t knh_Tuple_getSize(Tuple *b);
Object *knh_Tuple_get__fast(Tuple *b, knh_int_t index);
Object *knh_Tuple_get(Tuple *b, knh_int_t index);
Object* knh_Array_Tuple(Ctx *ctx, Object *self, MapMap *map);
Object* knh_Tuple_next(Ctx *ctx, Iterator *it);
Object* knh_Tuple_Iterator(Ctx *ctx, Object *self, MapMap *map);
void knh_Tuple__dump(Ctx *ctx, Tuple *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_DictIdx.c */
void knh_DictIdx_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_DictIdx_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
DictIdx* new_DictIdx(Ctx *ctx, size_t initialCapacity, knh_int_t offset);
knh_index_t knh_DictIdx_index(Ctx *ctx, DictIdx *b, knh_bytes_t v);
knh_index_t knh_DictIdx_add__fast(Ctx *ctx, DictIdx *b, String *term);
knh_index_t knh_DictIdx_add(Ctx *ctx, DictIdx *b, String *term);
knh_index_t knh_DictIdx_add__b(Ctx *ctx, DictIdx *b, knh_bytes_t term);
String* knh_DictIdx_get__fast(DictIdx *b, knh_int_t termid);
String* knh_DictIdx_get(DictIdx *b, knh_int_t termid);
void knh_DictIdx_clear(Ctx *ctx, DictIdx *b);
Object* knh_DictIdx_Iterator(Ctx *ctx, Object *self, MapMap *map);
void knh_DictIdx__dump(Ctx *ctx, DictIdx *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_InputStream.c */
void knh_InputStream_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_InputStream_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
InputStream * new_InputStream(Ctx *ctx, String *urn, knh_inptr_t *inptr, knh_inptr_drivers_t drv);
void knh_InputStream_open(Ctx *ctx, InputStream *b, String *urn);
int knh_InputStream_getc(Ctx *ctx, InputStream *b);
size_t knh_InputStream_read(Ctx *ctx, InputStream *b, char *buf, size_t bufsiz);
String* knh_InputStream_readLine(Ctx *ctx, InputStream *b);
void knh_InputStream_close(Ctx *ctx, InputStream *b);
knh_inptr_t* knh_InputStream_open__nop(Ctx *ctx, knh_bytes_t n);
int knh_InputStream_getc__nop(Ctx *ctx, knh_inptr_t *ptr);
size_t knh_InputStream_read__nop(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz);
void knh_InputStream_close__nop(Ctx *ctx, knh_inptr_t *ptr);
InputStream *new_InputStream__NULL(Ctx *ctx);
knh_inptr_t* knh_InputStream_open__FILE(Ctx *ctx, knh_bytes_t file);
int knh_InputStream_getc__FILE(Ctx *ctx, knh_inptr_t *ptr);
size_t knh_InputStream_read__FILE(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz);
void knh_InputStream_close__FILE(Ctx *ctx, knh_inptr_t *ptr);
InputStream *new_InputStream__FILE(Ctx *ctx, FILE *fp);
int knh_InputStream_getc__Bytes(Ctx *ctx, knh_inptr_t *ptr);
size_t knh_InputStream_read__Bytes(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz);
void knh_InputStream_close__Bytes(Ctx *ctx, knh_inptr_t *ptr);
InputStream *new_InputStream__Bytes(Ctx *ctx, Bytes *ba, size_t s, size_t e);
Object* knh_InputStream_line_next(Ctx *ctx, Iterator *it);
Object* knh_InputStream_String__(Ctx *ctx, Object *self, MapMap *map);
void knh_InputStream__dump(Ctx *ctx, InputStream *b, OutputStream *w, Any *m);
void KNH_TFUNC_INPUTSTREAM_OPEN(Ctx *ctx, char *n, f_inptr_open f);
void KNH_TFUNC_INPUTSTREAM_GETC(Ctx *ctx, char *n, f_inptr_getc f);
void KNH_TFUNC_INPUTSTREAM_READ(Ctx *ctx, char *n, f_inptr_read f);
void KNH_TFUNC_INPUTSTREAM_CLOSE(Ctx *ctx, char *n, f_inptr_close f);
/* ../class/konoha/knh_Array.c */
void knh_Array_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_Array_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
knh_int_t knh_Array_struct_compare(Ctx *ctx, Struct *s1, Struct *s2);
void knh_Array_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Array* new_Array(Ctx *ctx, size_t capacity);
Object* knh_Array_fvalue(Ctx *ctx, knh_class_t cid);
Object** knh_Array_list(Array *b);
Object* knh_Array_last(Array *b);
void knh_Array_subclear(Ctx *ctx, Array *b, size_t n);
size_t knh_array_index(knh_int_t n, size_t size);
size_t knh_Array_util_slice(knh_int_t n, size_t size);
void knh_Array_resize(Ctx *ctx, Array *b, size_t newsize);
void knh_Array_add__fast(Ctx *ctx, Array *b, Any *value);
void knh_Array_add(Ctx *ctx, Array *b, Any *value);
Any* knh_Array_pop(Ctx *ctx, Array *b);
Array *knh_Array_slice(Ctx *ctx, Array *b, knh_int_t start, knh_int_t end);
void knh_Array_swap(Array *b, knh_int_t n, knh_int_t n2);
void knh_Array_clear(Ctx *ctx, Array *b);
knh_bool_t knh_array_isdump(size_t c);
void knh_Array__dump(Ctx *ctx, Array *b, OutputStream *w, Any *m);
Object* knh_Array_var_next(Ctx *ctx, Iterator *it);
Object* knh_Array_Iterator(Ctx *ctx, Object *self, MapMap *map);
/* ../class/konoha/knh_Socket.c */
void knh_Socket_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Socket_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Socket* new_Socket(Ctx *ctx, knh_bytes_t urn, int port);
InputStream *knh_Socket_getInputStream(Ctx *ctx, Socket *b);
OutputStream *knh_Socket_getOutputStream(Ctx *ctx, Socket *b);
void knh_Socket_close(Ctx *ctx, Socket *b);
/* ../class/konoha/knh_String_charset.c */
size_t knh_string_size(knh_bytes_t s);
size_t knh_string_index(knh_bytes_t s, size_t n);
knh_bool_t knh_string_isvalid(knh_bytes_t s);
/* ../class/konoha/knh_Int.c */
void knh_Int_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_Int_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
knh_int_t knh_Int_struct_compare(Ctx *ctx, Struct *s1, Struct *s2);
Int* new_Int__fast(Ctx *ctx, knh_class_t cid, knh_int_t value);
knh_int_t knh_int_max(knh_int_t a, knh_int_t b);
knh_int_t knh_int_min(knh_int_t a, knh_int_t b);
knh_uint_t knh_uint_max(knh_uint_t a, knh_uint_t b);
knh_uint_t knh_uint_min(knh_uint_t a, knh_uint_t b);
knh_int_t knh_IntNULL_toint(Int *v);
/* ../class/konoha/knh_Regex.c */
void knh_Regex_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Regex_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Regex *new_Regex(Ctx *ctx, String *pstr);
knh_bool_t knh_Regex_match__b(Ctx *ctx, Regex *b, knh_bytes_t s);
knh_bool_t knh_Regex_match(Ctx *ctx, Regex *b, String *s);
Object *knh_Regex_transform(Ctx *ctx, Regex *b, knh_class_t tcid, String *s);
Object *knh_mapserv__Regex(Ctx *ctx, Object *mapserv, Object *s, knh_class_t tcid);
void knh_Regex__s(Ctx *ctx, Regex *b, OutputStream *w, Any *m);
void knh_Regex__dump(Ctx *ctx, Regex *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_ClassStruct.c */
void knh_ClassStruct_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_ClassStruct_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
ClassStruct* new_ClassStruct(Ctx *ctx, knh_struct_t sid);
void knh_cfield_safetype(knh_cfield_t *cf);
Object *knh_cfield_safevalue(Ctx *ctx, knh_cfield_t *cf);
knh_index_t knh_Class_initField(Ctx *ctx, knh_class_t cid, knh_flag_t flag, knh_type_t type, knh_fieldn_t fn, Object *value);
knh_index_t knh_Class_indexOfField(knh_class_t cid, knh_fieldn_t fn);
knh_index_t knh_Class_queryField(knh_class_t cid, knh_fieldn_t fnq);
knh_cfield_t *knh_Class_fieldAt(knh_class_t cid, size_t n);
Object *knh_ClassStruct_safevalue(Ctx *ctx, ClassStruct *b, size_t n);
void knh_Class_addMethod__fast(Ctx *ctx, knh_class_t cid, Method *method);
void knh_Class_addMethod(Ctx *ctx, knh_class_t cid, Method *method);
Method* knh_Class_getMethod__(Ctx *ctx, knh_class_t this_cid, knh_methodn_t mn, knh_bool_t gen);
void knh__ClassStruct_fmethodGetter(Ctx *ctx, Object **sfp);
void knh__ClassStruct_fmethodSetter(Ctx *ctx, Object **sfp);
MethodField* new_MethodField__getter(Ctx *ctx, knh_type_t type);
MethodField* new_MethodField__setter(Ctx *ctx, knh_type_t type, knh_fieldn_t fn);
void knh_cfield_dump(Ctx *ctx, knh_cfield_t *f, size_t offset, size_t fsize, OutputStream *w);
/* ../class/konoha/knh_Float.c */
void knh_Float_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_Float_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
knh_int_t knh_Float_struct_compare(Ctx *ctx, Struct *s1, Struct *s2);
Float* new_Float__fast(Ctx *ctx, knh_class_t cid, knh_float_t value);
Float* new_Float__checked(Ctx *ctx, knh_class_t cid, knh_float_t value);
knh_float_t knh_float_max(knh_float_t a, knh_float_t b);
knh_float_t knh_float_min(knh_float_t a, knh_float_t b);
/* ../class/konoha/knh_Bool.c */
void knh_Bool_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Bool_struct_copy(Ctx *ctx, Struct *s, Struct *s2);
knh_int_t knh_Bool_struct_compare(Ctx *ctx, Struct *s, Struct *s2);
/* ../class/konoha/knh_DictMap.c */
void knh_DictMap_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_DictMap_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
knh_int_t knh_DictMap_struct_compare(Ctx *ctx, Struct *s1, Struct *s2);
void knh_DictMap_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
DictMap* new_DictMap(Ctx *ctx0, knh_int_t capacity);
DictMap *knh_DictMap_new(Ctx *ctx, DictMap *b, knh_int_t initialCapacity);
DictMap* knh_DictMap_new__init(Ctx *ctx, DictMap *b, knh_vargc_t ac, Object **a);
int knh_DictMap_util_cmp(const knh_dictmape_t *n1, const knh_dictmape_t *n2);
void knh_DictMap_sort(DictMap *b);
	 knh_int_t knh_DictMap_findb_between(DictMap *b, knh_bytes_t kv, size_t sp, size_t ep);
knh_index_t knh_DictMap_indexb(DictMap *b, knh_bytes_t kv);
String* knh_DictMaps_key(DictMap *b, size_t n);
Any* knh_DictMaps_value(DictMap *b, size_t n);
Any *knh_DictMap_getb(Ctx *ctx, DictMap *b, knh_bytes_t key);
Any *knh_DictMap_get(Ctx *ctx, DictMap *b, String *key);
void knh_DictMap_resize(Ctx *ctx, DictMap *b, size_t newsize);
void knh_DictMap_append(Ctx *ctx, DictMap *b, String *key, Any *value);
void knh_DictMap_set(Ctx *ctx, DictMap *b, String *key, Any *value);
void knh_DictMap_remove(Ctx *ctx, DictMap *b, String *key);
void knh_DictMap_clear(Ctx *ctx, DictMap *b);
Object *knh_DictMap_key_next(Ctx *ctx, Iterator *it);
Any* knh_DictMap_Iterator(Ctx *ctx, Object *self, MapMap *map);
void knh_DictMap__dump(Ctx *ctx, DictMap *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_HashMap.c */
knh_hashmape_t *knh_HashMape_new(Ctx *ctx, knh_hcode_t key, Object *kobj, Object *value);
void knh_HashMape_traverse(Ctx *ctx, knh_hashmape_t *cur, f_gc gc);
void knh_HashMap_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_HashMap_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
void knh_HashMap_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
HashMap* new_HashMap(Ctx *ctx, size_t capacity);
HashMap *knh_HashMap_new(Ctx *ctx, HashMap *b, size_t initialCapacity);
HashMap* knh_HashMap_new__init(Ctx *ctx, HashMap *b, knh_vargc_t ac, Object **a);
Any *knh_HashMap_get(Ctx *ctx, HashMap *b, knh_hcode_t key, Any *kobj);
Object *knh_HashMap_get__b(HashMap *b, knh_bytes_t kv);
void knh_HashMap_rehash(Ctx *ctx, HashMap *b);
void knh_HashMap_resize(Ctx *ctx, HashMap *b, size_t nc);
void knh_HashMap_set(Ctx *ctx, HashMap *b, knh_hcode_t key, Any *kobj, Any *value);
void knh_HashMap_remove(Ctx *ctx, HashMap *b, knh_hcode_t key, Any *kobj);
knh_bool_t knh_HashMap_opIn(Ctx *ctx, HashMap *b, knh_hcode_t key, Any *keyobj);
knh_hashmape_t * knh_HashMape_next(Ctx *ctx, Iterator *it);
Object* knh_HashMap_key_next(Ctx *ctx, Iterator *it);
Iterator *knh_HashMap_keys(Ctx *ctx, HashMap *b);
Object* knh_HashMap_Iterator(Ctx *ctx, Object *self, MapMap *map);
void knh_HashMap__dump(Ctx *ctx, HashMap *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_AffineConv.c */
void knh_AffineConv_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
AffineConv *new_AffineConv(Ctx *ctx, knh_float_t fa, knh_float_t fb);
Object *knh_AffineConv_fmap__ftof(Ctx *ctx, Object *self, MapMap *map);
Object *knh_AffineConv_fmap__itof(Ctx *ctx, Object *self, MapMap *map);
Object *knh_AffineConv_fmap__ftoi(Ctx *ctx, Object *self, MapMap *map);
Object *knh_AffineConv_fmap__itoi(Ctx *ctx, Object *self, MapMap *map);
f_mapmap knh_AffineConv_fmap(Ctx *ctx, AffineConv *b, knh_class_t scpid, knh_class_t tpcid);
MapMap *new_MapMap_inv__AffineConv(Ctx *ctx, MapMap *map);
void KNH_TAFFINE(Ctx *ctx, knh_class_t scid, knh_class_t tcid, knh_float_t scale, knh_float_t shift);
/* ../class/konoha/knh_MapMap.c */
void knh_MapMap_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_MapMap_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
void knh_MapMap_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
MapMap* new_MapMap(Ctx *ctx, knh_flag_t flag, knh_class_t scid, knh_class_t tcid, f_mapmap fmap, Object *conf);
Object* knh_MapMap_fmap__Interface(Ctx *ctx, Object *self, MapMap *map);
MapMap* new_MapMap__interface(Ctx *ctx, knh_class_t scid, knh_class_t tcid);
Object* knh_MapMap_fmap__defvalue(Ctx *ctx, Object *self, MapMap *map);
Object* knh_MapMap_fmap__Null(Ctx *ctx, Object *self, MapMap *map);
MapMap* new_MapMap__NoSuchMapping(Ctx *ctx, knh_class_t scid, knh_class_t tcid);
knh_bool_t knh_MapMap_isNoSuchMapping(MapMap *b);
Object *knh_MapMap_execMap(Ctx *ctx, MapMap *b, Object *sub);
Object* knh_MapMap_toString(Ctx *ctx, Object *self, MapMap *map);
void knh_MapMap__dump(Ctx *ctx, MapMap *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_Prototype.c */
void knh_Prototype_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Prototype_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Prototype *new_Prototype(Ctx *ctx, knh_nsn_t nsn);
knh_bool_t knh_Class_isPrototype(Ctx *ctx, knh_class_t cid);
void knh_Prototype__dump(Ctx *ctx, Prototype *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_Socket_utils.c */
char * knh_bytes_urlencode(knh_bytes_t s, char *buf, size_t bufsiz);
char * knh_bytes_urldecode(knh_bytes_t s, char *buf, size_t bufsiz);
char * knh_bytes_urlhost(knh_bytes_t url, char *buf, size_t bufsiz);
int knh_bytes_urlport(knh_bytes_t url, int defport);
char * knh_bytes_urlpath(knh_bytes_t url, char *buf, size_t bufsiz);
/* ../class/konoha/knh_Nue.c */
void knh_Nue_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_Nue_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
knh_int_t knh_Nue_struct_compare(Ctx *ctx, Struct *s, Struct *s2);
void knh_Nue_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Nue * new_Nue__STEXT(Ctx *ctx, char *msg);
Nue * new_Nue(Ctx *ctx, String *msg);
ObjectNULL *knh_Nue_fvalue(Ctx *ctx, knh_class_t cid);
Object* knh_Nue_String(Ctx *ctx, Object *self, MapMap *map);
void knh_Nue__s(Ctx *ctx, Nue *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_Iterator.c */
void knh_Iterator_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_Iterator_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
void knh_Iterator_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Object * knh_Object_single_next(Ctx *ctx, Iterator *it);
Iterator* new_Iterator(Ctx *ctx, knh_class_t cid, Object *source, f_next f);
Object *knh_Iterator_fvalue(Ctx *ctx, knh_class_t cid);
Object* knh_MapMap_fmap__Iterator(Ctx *ctx, Object *self, MapMap *map);
knh_class_t knh_Object_pcid(Object *b);
Object *knh_Iterator_foreach(Ctx *ctx, Iterator *b, knh_class_t cid);
Object *knh_Iterator_each(Ctx *ctx, Iterator *b, knh_class_t cid);
Object *knh_Iterator_each__slice(Ctx *ctx, Iterator *b, knh_class_t cid);
Object *knh_Iterator_each__map(Ctx *ctx, Iterator *b, knh_class_t tcid);
Object* knh_Iterator_Array(Ctx *ctx, Object *self, MapMap *map);
void knh_Iterator__dump(Ctx *ctx, Iterator *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_HashSet.c */
knh_hashsete_t *knh_HashSete_new(Ctx *ctx, knh_hcode_t key, Object *keyobj, knh_uint_t value);
void knh_HashSete_traverse(Ctx *ctx, knh_hashsete_t *cur, f_gc gc);
void knh_HashSet_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_HashSet_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
void knh_HashSet_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
HashSet* new_HashSet(Ctx *ctx, size_t capacity);
HashSet *knh_HashSet_new(Ctx *ctx, HashSet *b, size_t initialCapacity);
void knh_HashSet_rehash(Ctx *ctx, HashSet *b);
void knh_HashSet_resize(Ctx *ctx, HashSet *b, size_t nc);
knh_uint_t knh_HashSet_get(Ctx *ctx, HashSet *b, knh_hcode_t key, Object *keyobj);
knh_bool_t knh_HashSet_opIn(Ctx *ctx, HashSet *b, knh_hcode_t key, Object *keyobj);
knh_uint_t knh_HashSet_get__b(Ctx *ctx, HashSet *b, knh_bytes_t kv);
void knh_HashSet_set(Ctx *ctx, HashSet *b, knh_hcode_t key, Any *keyobj, knh_uint_t value);
void knh_HashSet_add(Ctx *ctx, HashSet *b, knh_hcode_t key, Any *keyobj);
void knh_HashSet_remove(Ctx *ctx, HashSet *b, knh_hcode_t key, Any *keyobj);
Object* knh_HashSet_Iterator(Ctx *ctx, Object *self, MapMap *map);
void knh_HashSet__dump(Ctx *ctx, HashSet *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_OutputStream.c */
void knh_OutputStream_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_OutputStream_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
OutputStream * new_OutputStream(Ctx *ctx, String *urn, knh_outptr_t *outptr, knh_outptr_drivers_t drv);
void knh_OutputStream_putc(Ctx *ctx, OutputStream *b, int ch);
void knh_OutputStream_write(Ctx *ctx, OutputStream *b, knh_bytes_t buf);
void knh_OutputStream_flush(Ctx *ctx, OutputStream *b);
void knh_OutputStream_close(Ctx *ctx, OutputStream *b);
void knh_OutputStream_print_(Ctx *ctx, OutputStream *b, knh_bytes_t str, knh_bool_t isnl);
void knh_OutputStream_indent_inc(Ctx *ctx, OutputStream *b);
void knh_OutputStream_indent_dec(Ctx *ctx, OutputStream *b);
void knh_OutputStream_write_indent(Ctx *ctx, OutputStream *b);
knh_outptr_t* knh_OutputStream_open__nop(Ctx *ctx, knh_bytes_t n);
void knh_OutputStream_putc__nop(Ctx *ctx, knh_outptr_t *ptr, int ch);
size_t knh_OutputStream_write__nop(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz);
void knh_OutputStream_flush__nop(Ctx *ctx, knh_outptr_t *ptr);
void knh_OutputStream_close__nop(Ctx *ctx, knh_outptr_t *ptr);
OutputStream *new_OutputStream__NULL(Ctx *ctx);
knh_outptr_t* knh_OutputStream_open__FILE(Ctx *ctx, knh_bytes_t file);
void knh_OutputStream_putc__FILE(Ctx *ctx, knh_outptr_t *ptr, int ch);
size_t knh_OutputStream_write__FILE(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz);
void knh_OutputStream_flush__FILE(Ctx *ctx, knh_outptr_t *ptr);
void knh_OutputStream_close__FILE(Ctx *ctx, knh_outptr_t *ptr);
OutputStream *new_OutputStream__FILE(Ctx *ctx, FILE *fp);
void knh_OutputStream_putc__Bytes(Ctx *ctx, knh_outptr_t *ptr, int ch);
size_t knh_OutputStream_write__Bytes(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz);
void knh_OutputStream_close__Bytes(Ctx *ctx, knh_outptr_t *ptr);
OutputStream *new_OutputStream__Bytes(Ctx *ctx, Bytes *ba);
void KNH_TFUNC_OUTPUTSTREAM_OPEN(Ctx *ctx, char *n, f_outptr_open f);
void KNH_TFUNC_OUTPUTSTREAM_PUTC(Ctx *ctx, char *n, f_outptr_putc f);
void KNH_TFUNC_OUTPUTSTREAM_WRITE(Ctx *ctx, char *n, f_outptr_write f);
void KNH_TFUNC_OUTPUTSTREAM_FLUSH(Ctx *ctx, char *n, f_outptr_flush f);
void KNH_TFUNC_OUTPUTSTREAM_CLOSE(Ctx *ctx, char *n, f_outptr_close f);
/* ../class/konoha/vm/konoha_print.c */
int knh_verbose(void);
char *KNH_SAFEFILE(char *file);
void knh_vmprint(Ctx *ctx, Object **sfp, /* knh_dwarf_t dwf,*/ knh_flag_t flag, knh_methodn_t mn, Object *o);
/* ../class/konoha/vm/konoha_tname.c */
void knh_tname_ginit();
void knh_tname_gtraverse(Ctx *ctx, f_gc gc);
char * knh_format_nzname(char *buf, size_t bufsiz, knh_bytes_t t);
knh_fieldn_t knh_tfieldn_common(Ctx *ctx, knh_bytes_t n, knh_fieldn_t def);
String *knh_tfieldn_name(knh_fieldn_t fn);
knh_fieldn_t knh_tfieldn_forname(Ctx *ctx, knh_bytes_t tname, knh_fieldn_t def);
void KNH_TFIELDN(Ctx *ctx, knh_fieldn_t fn, String *name);
knh_fieldn_t knh_tfieldn_level(Ctx *ctx, int level);
knh_methodn_t knh_tmethodn_forname(Ctx *ctx, knh_bytes_t tname, knh_methodn_t def);
char * knh_format_methodn(char *buf, size_t bufsiz, knh_methodn_t mn);
char * knh_bytes_nznsn(knh_bytes_t t, char *buf, size_t bufsiz);
knh_nsn_t knh_tnsn_forname(Ctx *ctx, knh_bytes_t t);
String *knh_tnsn_name(knh_nsn_t nsn);
knh_filen_t knh_tfilen_forname(Ctx *ctx, knh_bytes_t t);
String *knh_tfilen_name(knh_filen_t filen);
/* ../class/konoha/vm/konoha_throwcatch.c */
void knh_konohavm_throwException(Ctx *ctx, Exception *e);
void knh_Exception_addStackTrace(Ctx *ctx, Exception *b, String *msg);
String *knh_stackf_getStackTraceMsg(Ctx *ctx, Object **sf);
/* ../class/konoha/vm/konoha_ext.c */
void knh_srand(knh_int_t seed);
knh_int_t knh_rand();
/* ../class/konoha/vm/konoha_init.c */
Object *knh_Nue_NULL(void);
Runtime *knh_Runtime_ROOT();
Runtime *knh_Context_getRuntime(Ctx *ctx, Context *b);
Object *knh_Runtime_fvalue(Ctx *ctx, knh_class_t cid);
System *knh_System_ROOT(void);
Object *knh_System_fvalue(Ctx *ctx, knh_class_t cid);
Bool *knh_Bool_TRUE(void);
Bool *knh_Bool_FALSE(void);
Object *knh_Bool_fvalue(Ctx *ctx, knh_class_t cid);
NameSpace *knh_NameSpace_SYSTEM(void);
void knh_konoha_ginit();
void knh_konoha_gtraverse(Ctx *ctx, f_gc gc);
/* ../class/konoha/vm/konoha_call.c */
void knh_stackf_locals(Ctx *ctx, size_t n);
knh_vargc_t knh_stackf_argc(Ctx *ctx, Object **varg);
Array *knh_stackf_toArray(Ctx *ctx, Object **varg);
Method *knh_stackf_getMethod(Ctx *ctx, Object **sf);
Struct *knh_stackf_structDelta(Ctx *ctx, Object **sf);
void knh_stackf_new(Ctx *ctx, Object **mtdp);
void knh_stackf_typecheck__DCALL(Ctx *ctx, Object **mtdp);
void knh_stackf_typecheck__MCALL(Ctx *ctx, Object **mtdp);
void knh_stackf_dump(Ctx *ctx, Object **sf);
void knh_stackf_diagnose(Ctx *ctx, Object **sf, knh_int_t n);
/* ../class/konoha/vm/konoha_tconst.c */
knh_bool_t knh_tconst_exists(Ctx *ctx, knh_bytes_t name);
Object *knh_tconst_value(Ctx *ctx, knh_bytes_t name);
knh_type_t knh_tconst_type(Ctx *ctx, knh_bytes_t name);
char *knh_tconst_uname(void);
/* ../class/konoha/vm/konoha_tstruct.c */
void knh_tstruct_ginit(void);
void knh_tstruct_gtraverse(Ctx *ctx, f_gc gc);
knh_struct_t KNH_TSTRUCT(Ctx *ctx, knh_struct_t sid, size_t size, char *name, f_struct_init f0, f_struct_copy f1, f_struct_compare f2, f_struct_traverse f3);
void knh_tstruct_init__default(Ctx *ctx, Struct *s1, int init, Object *cs);
knh_int_t knh_tstruct_compare__default(Ctx *ctx, Struct *s1, Struct *s2);
void knh_tstruct_traverse__default(Ctx *ctx, Struct *s, f_gc gc);
size_t knh_tstruct_size(knh_struct_t sid);
bsize_t knh_tstruct_bsize(knh_struct_t sid);
char *knh_tstruct_name(knh_struct_t sid);
f_struct_init knh_tstruct_finit(knh_struct_t sid);
f_struct_copy knh_tstruct_fcopy(knh_struct_t sid);
f_struct_compare knh_tstruct_fcompare(knh_struct_t sid);
f_struct_traverse knh_tstruct_ftraverse(knh_struct_t sid);
/* ../class/konoha/vm/konoha_shell.c */
char *knh_readline(char *prompt);
void konoha_show_version(Ctx *ctx);
knh_int_t konoha_shell_checkline(knh_bytes_t line);
void konoha_shell(konoha_t konoha);
/* ../class/konoha/vm/konoha_hobject.c */
Object *knh_Object_malloc0(Ctx *ctx, knh_flag_t flag, knh_class_t cid, size_t size);
Object *knh_Object_malloc(Ctx *ctx, knh_class_t cid);
void knh_Object_dispose(Ctx *ctx, Object *o);
void knh_Object_refc_inc(Object *self);
void knh_Object_vmcinc(Ctx *ctx, Object *self);
void knh_Object_refc_dec(Ctx *ctx, Object *self);
void knh_Object_safefree(Ctx *ctx, Object *self);
void knh_INITv(Object **var, Object *o);
void knh_INITn(Object **var, int n, Object *o);
void knh_SETv(Ctx *ctx, Object **var, Object *o);
void knh_SETv__ngc(Ctx *ctx, Object **v, Object *o);
void knh_SETn(Ctx *ctx, Object **var, int n, Object *o);
void knh_FINALv(Ctx *ctx, Object **var);
void knh_FINALn(Ctx *ctx, Object **var, int n);
Object** knh_oarray_malloc(Ctx *ctx, size_t size, Object *value);
void knh_oarray_traverse(Ctx *ctx, Object **a, size_t size, f_gc gc);
/* ../class/konoha/vm/konoha_tmemory.c */
size_t knh_tmemory_used_size(void);
void *knh_malloc(Ctx *ctx, size_t size);
void knh_free(void *block, size_t size);
void knh_tmemory_beginMemoryLeakNotice();
void knh_tmemory_endMemoryLeakNotice();
/* ../class/konoha/vm/konoha_typesystem.c */
knh_bool_t knh_class_instanceof(knh_class_t scid, knh_class_t tcid);
knh_bool_t knh_Object_opInstanceof(Ctx *ctx, Object *b, knh_type_t c);
knh_type_t knh_typesystem_parentType(knh_type_t t1, knh_type_t t2);
Object * knh_typesystem_doCoercion(Ctx *ctx, knh_type_t type, Object *v);
Object * knh_typesystem_map(Ctx *ctx, Object *v, knh_type_t type);
Object * knh_typesystem_initialValue(Ctx *ctx, knh_type_t type);
Iterator * knh_typesystem_foreach(Ctx *ctx, Object *v, knh_class_t cid);
Exception* new_Exception__type(Ctx *ctx, Object *value, knh_type_t spec_type);
/* ../class/konoha/vm/konoha_texpt.c */
void knh_texpt_ginit();
void knh_texpt_gtraverse(Ctx *ctx, f_gc gc);
knh_expt_t knh_texpt_newId(Ctx *ctx);
knh_bool_t knh_texpt_isvalid(knh_expt_t eid);
knh_flag_t knh_texpt_flag(knh_expt_t eid);
knh_expt_t knh_texpt_parent(knh_expt_t eid);
knh_bool_t knh_texpt_isa(knh_expt_t eid, knh_expt_t parent);
String *knh_texpt_name(knh_expt_t eid);
knh_expt_t TEXPT(Ctx *ctx, knh_flag_t flag, knh_class_t eid, knh_bytes_t ename, char *pname);
knh_expt_t knh_texpt_forname(Ctx *ctx, knh_bytes_t msg, knh_expt_t def);
/* ../class/konoha/vm/konoha_metadata.c */
void knh_metadata_set(Ctx *ctx, Object *b, String *key, Any *value);
Any *knh_metadata_get(Ctx *ctx, Object *b, knh_bytes_t key);
void knh_metadata_clear(Ctx *ctx, Object *b);
/* ../class/konoha/vm/konoha_tglobal.c */
void knh_tglobal_ginit();
void knh_tglobal_insert(Object **var);
void knh_tglobal_gtraverse(Ctx *ctx, f_gc gc);
/* ../class/konoha/vm/konoha_api.c */
knh_bool_t konoha_initcheck(void);
konoha_t konoha_open(void);
void konoha_close(konoha_t konoha);
Ctx *konoha_ctx(konoha_t konoha);
konoha_t konoha_context(konoha_t konoha, char *name);
void konoha_eval(konoha_t konoha, char *script);
void konoha_read(konoha_t konoha, knh_nsn_t nsn, char *fpath);
/* ../class/konoha/vm/konoha_tclass.c */
void knh_tclass_ginit();
	 void knh_tclass_gtraverse(Ctx *ctx, f_gc gc);
knh_class_t knh_tclass_newId(Ctx *ctx);
knh_bool_t knh_tclass_isvalid(knh_class_t cid);
knh_tclass_t* knh_tclass_table(knh_class_t cid);
void knh_tclass_count_inc(knh_class_t cid);
void knh_tclass_count_dec(knh_class_t cid);
knh_flag_t knh_tclass_cflag(knh_class_t cid);
knh_flag_t knh_tclass_oflag(knh_class_t cid);
knh_struct_t knh_tclass_topsid(knh_class_t cid);
knh_ushort_t knh_tclass_offset(knh_class_t cid);
knh_struct_t knh_tclass_sid(knh_class_t cid);
knh_ushort_t knh_tclass_supcid(knh_class_t cid);
knh_index_t knh_tclass_keyidx(knh_class_t cid);
String *knh_tclass_name(knh_class_t cid);
Class *knh_tclass_class(knh_class_t cid);
knh_class_t knh_tclass_bcid(knh_class_t cid);
knh_class_t knh_tclass_ensurebcid(knh_class_t bcid, knh_class_t cid);
ClassStruct *knh_tclass_cstruct(knh_class_t cid);
bsize_t knh_tclass_bsize(knh_class_t cid);
size_t knh_tclass_size(knh_class_t cid);
ClassRel *knh_tclass_crel(knh_class_t cid);
Object *knh_tclass_spec(knh_class_t cid);
knh_bool_t knh_class_isSingleton(knh_class_t b);
ObjectNULL *knh_tclass_fvalue__singleton(Ctx *ctx, knh_class_t cid);
ObjectNULL *knh_tclass_fvalue__default(Ctx *ctx, knh_class_t cid);
knh_bool_t knh_tclass_hasDefaultValue(knh_class_t cid);
Object *knh_tclass_value(Ctx *ctx, knh_class_t cid, Object *alt);
Object *knh_tclass_safevalue(Ctx *ctx, knh_class_t cid);
knh_class_t KNH_TCLASS(Ctx *ctx, knh_flag_t flag, String *name, knh_class_t cid, knh_struct_t sid, knh_class_t supcid, Object *spec, f_value fvalue, int isize, ...);
ObjectNULL *knh_tclass_fvalue__spec(Ctx *ctx, knh_class_t cid);
knh_class_t KNH_TCLASS_SPEC(Ctx *ctx, knh_class_t bcid, Object *spec);
knh_class_t KNH_TCLASS_NEWCLASS(Ctx *ctx, String *name);
knh_class_t KNH_TCLASS_STRUCT(Ctx *ctx, knh_flag_t flag, knh_class_t cid, knh_struct_t sid, knh_class_t supcid, ClassStruct *cs);
void knh_tclass_load(Ctx *ctx, knh_bytes_t nsname);
void knh_NameSpace_import(Ctx *ctx, NameSpace *ns, knh_bytes_t p);
knh_class_t knh_type_toarray(Ctx *ctx, knh_type_t type);
/* ../class/konoha/vm/konoha_tmethod.c */
knh_bool_t knh_Method_checkMethodField(Ctx *ctx, Method *mtd, knh_flag_t flag, knh_type_t rtype, size_t psize);
void TMETHOD(Ctx *ctx, knh_flag_t tflag, f_method func, knh_type_t rtype, knh_class_t cid, knh_methodn_t mn, knh_ushort_t psize, ...);
void KNH_TMETHOD(Ctx *ctx, knh_flag_t tflag, f_method func, void *optfunc, knh_ushort_t delta, knh_type_t rtype, knh_class_t cid, knh_methodn_t mn, knh_ushort_t psize, ...);
Method *knh_Method_ufind(Ctx *ctx, knh_class_t cid, knh_methodn_t mn);
Method *knh_Method_ufindb(Ctx *ctx, knh_class_t cid, knh_bytes_t mnm);
/* ../class/konoha/vm/konoha_tmapmap.c */
void konoha_stat_tmapmap_cache();
void KNH_TMAPMAP(Ctx *ctx, knh_flag_t flag, knh_type_t stype, knh_type_t ttype, f_mapmap fmap, Object *conf);
MapMap *knh_tmapmap_find_cache(Ctx *ctx, knh_class_t scid, knh_class_t tcid);
void knh_tmapmap_set_cache(Ctx *ctx, MapMap *map);
MapMap *knh_tmapmap_find(Ctx *ctx, knh_class_t scid, knh_class_t tcid);
Object* knh_MapMap_fMethod(Ctx *ctx, Object *self, MapMap *map);
f_mapmap knh_tmapmap_config(Ctx *ctx, Object *conf, knh_class_t scid, knh_class_t tcid);
/* ../class/konoha/vm/konoha_loader.c */
void knh_loader_ginit();
void knh_loader_gtraverse(Ctx *ctx, f_gc gc);
void KNH_TFUNC(Ctx *ctx, char *funcname, void *func);
void * knh_system_loadBuiltInFunc(Ctx *ctx, knh_bytes_t funcname, void *deffunc);
void * knh_system_loadFunc(Ctx *ctx, char *dirname, char *libname, char *funcname, void *deffunc);
void *knh_system_loadPackageFunc(Ctx *ctx, knh_bytes_t pname, knh_bytes_t fname);
void *knh_system_loadDriverFunc(Ctx *ctx, knh_bytes_t drvname, char *funcbase, void *deffunc);
/* ../class/konoha/knh_Vocabulary.c */
void knh_Vocabulary_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_Vocabulary_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Vocabulary *new_Vocabulary__STEXT(Ctx *ctx, knh_flag_t flag, knh_class_t cid, char *urn, char *tag, ...);
Vocabulary* knh_tclass_getVocabulary(Ctx *ctx, knh_class_t cid);
Vocabulary *knh_String_spec(Ctx *ctx);
knh_class_t KNH_TVOCAB(Ctx *ctx, char *urn, char *tag, ...);
knh_bool_t knh_Vocabulary_fnmz__toupper(Ctx *ctx, knh_bytes_t t, Bytes *ba);
knh_bool_t knh_Vocabulary_fnmz__tolower(Ctx *ctx, knh_bytes_t t, Bytes *ba);
String *knh_Vocabulary_newString(Ctx *ctx, Vocabulary *b, knh_bytes_t t, void *orig, size_t off, size_t len);
String *new_Nue__asIllegalString(Ctx *ctx, Vocabulary *b, knh_bytes_t t);
String *knh_Vocabulary_value(Ctx *ctx, Vocabulary *b, knh_bytes_t t, void *orig, size_t off, size_t len);
knh_int_t knh_Vocabulary_fcmp__default(Vocabulary *b, knh_bytes_t v1, knh_bytes_t v2);
knh_int_t knh_Vocabulary_compare(Vocabulary *b, knh_bytes_t v1, knh_bytes_t v2);
void knh_Vocabulary_initDict(Ctx *ctx, Vocabulary *b, ObjectNULL *dict, f_vocab_nmz fnmz, f_vocab_val fval, f_vocab_cmp fcmp);
String* knh_Vocabulary_fval__dict(Ctx *ctx, Vocabulary *b, knh_bytes_t t, void *orig, size_t off, size_t len);
knh_int_t knh_Vocabulary_fcmp__dict(Vocabulary *b, knh_bytes_t v1, knh_bytes_t v2);
void knh_Vocabulary_addDict__STEXT(Ctx *ctx, Vocabulary *b, char *vocab);
/* ../class/konoha/knh_Context.c */
void knh_Context_struct_init(Ctx *ctx0, Struct *s, int init, Object *cs);
void knh_Context_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Context* new_Context(Ctx *ctx0, Runtime *runtime, String *name, size_t size);
Object* knh_Context_fvalue(Ctx *ctx, knh_class_t cid);
Any* knh_Context_getProperty(Ctx *ctx, Context *b, knh_bytes_t key);
void knh_Context_setProperty(Ctx *ctx, Context *b, String *key, Any *value);
void knh_Context__dump(Ctx *ctx, Context *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_NameSpace.c */
NameSpace* new_NameSpace(Ctx *ctx0, NameSpace *parent, String *nsname);
void knh_NameSpace_setClass(Ctx *ctx, NameSpace *b, String *name, knh_class_t c);
void knh_NameSpace_setLocalName(Ctx *ctx, NameSpace *b, String *name, knh_class_t c);
knh_class_t knh_NameSpace_getClass(Ctx *ctx, NameSpace *b, knh_bytes_t name);
knh_type_t knh_NameSpace_getType(Ctx *ctx, NameSpace *b, knh_bytes_t name);
knh_class_t knh_tclass_classURN(Ctx *ctx, knh_class_t bcid, knh_bytes_t urn);
knh_class_t knh_tclass_loadURN(Ctx *ctx, knh_class_t bcid, knh_bytes_t urn);
knh_type_t knh_NameSpace_tagcid(Ctx *ctx, NameSpace *b, knh_class_t bcid, knh_bytes_t tag);
Class *knh_NameSpace_getFuncClass(Ctx *ctx, NameSpace *b, knh_bytes_t funcname);
/* ../class/konoha/knh_Method.c */
void knh_Method_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_Method_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
knh_int_t knh_Method_struct_compare(Ctx *ctx, Struct *s1, Struct *s2);
void knh_Method_code_traverse(Ctx *ctx, Method *b, f_gc gc);
void knh_Method_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Method* new_Method(Ctx *ctx, knh_flag_t flag, knh_class_t cid, knh_methodn_t mn, f_method func);
void knh_Method_fAbstractMethod(Ctx *ctx, Object **sf);
knh_bool_t knh_Method_isAbstract(Method *b);
void knh_Method_toAbstract(Ctx *ctx, Method *b);
void knh_ClassStruct_toAbstractAll(Ctx *ctx, ClassStruct *b);
Object * knh_Method_returnValue(Ctx *ctx, Method *b);
void knh_Method_fNoSuchMethod(Ctx *ctx, Object **sf);
knh_bool_t knh_Method_isNoSuchMethod(Method *b);
Method* new_Method__NoSuchMethod(Ctx *ctx, knh_class_t cid, knh_methodn_t mn);
knh_bool_t knh_methodn_isNew(knh_methodn_t mn);
knh_bool_t knh_Method_isNew(Method *b);
knh_bool_t knh_methodn_isOp(knh_methodn_t mn);
String* knh_Method_getName(Ctx *ctx, Method *b);
String* knh_Method_getURN(Ctx *ctx, Method *b);
void knh_Method__s(Ctx *ctx, Method *b, OutputStream *w, Any *m);
void knh_Method__dump(Ctx *ctx, Method *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_Class_type_t.c */
knh_class_t knh_type_toclass(knh_type_t t);
knh_bool_t knh_bytes_isPluralType(knh_bytes_t t);
knh_bool_t knh_bytes_isNotNullType(knh_bytes_t t);
knh_int_t knh_type_compare(Ctx *ctx, knh_type_t t1, knh_type_t t2);
char *TYPEQ(knh_type_t type);
char *knh_TYPEN(Ctx *ctx, knh_type_t type);
char *knh_CLASSQ(knh_type_t type);
/* ../class/konoha/knh_IntUnit.c */
void knh_IntUnit_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_IntUnit_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Object *knh_intunit_fvalue(Ctx *ctx, knh_class_t cid);
IntUnit *new_IntUnit__STEXT(Ctx *ctx, knh_flag_t flag, knh_class_t cid, char *urn, char *tag, knh_int_t min, knh_int_t max, knh_int_t defvalue, knh_int_t bf_start, knh_int_t bf_end);
IntUnit* knh_tclass_getIntUnit(Ctx *ctx, knh_class_t cid);
IntUnit *knh_Int_spec(Ctx *ctx);
knh_class_t KNH_TENUM(Ctx *ctx, char *urn, char *tag, knh_int_t min, knh_int_t max, knh_int_t defv, knh_int_t bf_start, knh_int_t bf_end);
void knh_IntUnit_initId(Ctx *ctx, IntUnit *b, knh_flag_t flag, knh_class_t cid, String *urn, String *tag);
void knh_IntUnit_initMinMax(Ctx *ctx, IntUnit *b, knh_int_t min, knh_int_t max);
void knh_IntUnit_init_bfarray(Ctx *ctx, IntUnit *b, knh_int_t bf_start, knh_int_t bf_end);
void knh_IntUnit_initDefaultValue(Ctx *ctx, IntUnit *b, knh_int_t v);
knh_bool_t knh_IntUnit_check(IntUnit *b, knh_int_t value);
Int *new_Nue__asInt(Ctx *ctx, knh_class_t cid, knh_int_t value);
Int *new_Nue__asuInt(Ctx *ctx, knh_class_t cid, knh_uint_t value);
Int *new_Int__checked(Ctx *ctx, knh_class_t cid, knh_int_t value);
knh_int_t knh_IntUnit_compare(IntUnit *b, knh_int_t v1, knh_int_t v2);
void knh_IntUnit_format(IntUnit *b, char *buf, knh_int_t v);
void knh_IntUnit_format_unit(IntUnit *b, char *buf);
knh_bool_t knh_IntUnit_fchk__nop(IntUnit *b, knh_int_t v);
knh_int_t knh_IntUnit_fcmp__signed(IntUnit *b, knh_int_t v1, knh_int_t v2);
knh_int_t knh_IntUnit_fcmp__unsigned(IntUnit *b, knh_int_t v1, knh_int_t v2);
void knh_IntUnit_ffmt__signed(IntUnit *b, char *buf, knh_int_t v);
void knh_IntUnit_ffmt__unsigned(IntUnit *b, char *buf, knh_int_t v);
knh_bool_t knh_IntUnit_fchk__signed_min(IntUnit *b, knh_int_t v);
knh_bool_t knh_IntUnit_fchk__signed_max(IntUnit *b, knh_int_t v);
knh_bool_t knh_IntUnit_fchk__signed(IntUnit *b, knh_int_t v);
knh_bool_t knh_IntUnit_fchk__unsigned_min(IntUnit *b, knh_int_t v);
knh_bool_t knh_IntUnit_fchk__unsigned_max(IntUnit *b, knh_int_t v);
knh_bool_t knh_IntUnit_fchk__unsigned(IntUnit *b, knh_int_t v);
/* ../class/konoha/knh_ResultSet.c */
knh_bool_t knh_ResultSet_next__nop(Ctx *ctx, knh_rsptr_t *rsptr, ResultSet *b);
void knh_ResultSet_free__nop(knh_rsptr_t *rsptr);
void knh_ResultSet_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_ResultSet_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
ResultSet* new_ResultSet(Ctx *ctx, size_t column_size, knh_rsptr_t *rsptr, f_rsptr_next fnext, f_rsptr_free ffree);
ResultSet *knh_ResultSet_next(Ctx *ctx, ResultSet *b);
Object* knh_ResultSet_it_next(Ctx *ctx, Iterator *it);
Object* knh_ResultSet_Iterator(Ctx *ctx, Object *self, MapMap *map);
void knh_ResultSet_initTargetClass(ResultSet *b, knh_class_t tcid);
void knh_ResultSet_initMetaInfo(Ctx *ctx, ResultSet *b, size_t n, knh_type_t type, String *name);
knh_index_t knh_ResultSet_index(Ctx *ctx, ResultSet *b, knh_bytes_t name);
String *knh_ResultSet_getName(Ctx *ctx, ResultSet *b, size_t n);
knh_type_t knh_ResultSet_get_type(Ctx *ctx, ResultSet *b, size_t n);
void knh_ResultSet_initData(Ctx *ctx, ResultSet *b);
void knh_ResultSet_set__int(Ctx *ctx, ResultSet *b, size_t n, knh_int_t value);
void knh_ResultSet_set__float(Ctx *ctx, ResultSet *b, size_t n, knh_float_t value);
void knh_ResultSet_set__int64(Ctx *ctx, ResultSet *b, size_t n, knh_int64_t value);
void knh_ResultSet_set__bytes(Ctx *ctx, ResultSet *b, size_t n, knh_bytes_t t);
void knh_ResultSet_set__null(Ctx *ctx, ResultSet *b, size_t n);
knh_int_t knh_ResultSet_get__int(Ctx *ctx, ResultSet *b, size_t n);
knh_float_t knh_ResultSet_get__float(Ctx *ctx, ResultSet *b, size_t n);
knh_int64_t knh_ResultSet_get__int64(Ctx *ctx, ResultSet *b, size_t n);
Object *knh_ResultSet_get(Ctx *ctx, ResultSet *b, size_t n);
void knh_ResultSet__dump(Ctx *ctx, ResultSet *b, OutputStream *w, Any *m);
void KNH_TFUNC_RESULTSET_NEXT(Ctx *ctx, char *n, f_rsptr_next f);
void KNH_TFUNC_RESULTSET_FREE(Ctx *ctx, char *n, f_rsptr_free f);
/* ../class/konoha/knh_Context_buffer.c */
knh_bytes_t knh_Bytes_firstbyte(Bytes *b, size_t pos);
knh_bytes_t knh_Bytes_lastbyte(Bytes *b, size_t pos);
size_t knh_Bytes_lastsize(Bytes *b, size_t pos);
void knh_Bytes_subclear(Bytes *b, size_t pos);
String *new_String__buffer(Ctx *ctx, knh_class_t cid, knh_buffer_t cb);
String *new_String__bufferconv(Ctx *ctx, knh_class_t cid, knh_buffer_t cb, BytesConv *bconv);
knh_buffer_t knh_Context_buffer(Ctx* ctx);
size_t knh_buffer_size(knh_buffer_t cb);
knh_bytes_t knh_buffer_tobytes(knh_buffer_t cb);
char *knh_buffer_top(knh_buffer_t cb);
void knh_buffer_clear(knh_buffer_t cb);
/* ../class/konoha/knh_Bytes.c */
void knh_Bytes_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_Bytes_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
knh_int_t knh_Bytes_struct_compare(Ctx *ctx, Struct *s1, Struct *s2);
void knh_Bytes_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Bytes* new_Bytes(Ctx *ctx, size_t capacity);
Object* knh_Bytes_fvalue(Ctx *ctx, knh_class_t cid);
Bytes* new_Bytes__buf(Ctx *ctx, char *buf, size_t bufsiz);
knh_bytes_t knh_Bytes_tobytes(Bytes *b);
knh_bytes_t knh_BytesNULL_tobytes(Bytes *b);
char *knh_BytesNULL_tochar(Bytes *b);
knh_uchar_t *knh_Bytes_last(Bytes *b);
void knh_Bytes_resize(Ctx *ctx, Bytes *b, size_t newsize);
void knh_Bytes_clear(Bytes *b);
void knh_Bytes_putc(Ctx *ctx, Bytes *b, int_byte_t ch);
void knh_Bytes_write(Ctx *ctx, Bytes *b, knh_bytes_t v);
void knh_Bytes_unputc(Bytes *b);
/* ../class/konoha/knh_BytesConv.c */
void knh_BytesConv_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_BytesConv_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
BytesConv* new_BytesConv(Ctx *ctx, knh_bytes_t name, f_bconv fbconv);
BytesConv* new_BytesConv__iconv(Ctx *ctx, knh_bytes_t from, knh_bytes_t to);
size_t knh_BytesConv_fbconv__nop(Ctx *ctx, BytesConv *b, char *buf, size_t bufsiz, knh_Bytes *ba);
size_t knh_BytesConv_fbconv__iconv(Ctx *ctx, BytesConv *b, char *buf, size_t bufsiz, knh_Bytes *ba);
/* ../class/konoha/knh_Writer.c */
void knh_putc(Ctx *ctx, Writer *w, int ch);
void knh_write(Ctx *ctx, Writer *w, knh_bytes_t s);
void knh_flush(Ctx *ctx, Writer *w);
void knh_print(Ctx *ctx, Writer *w, knh_bytes_t s);
void knh_println(Ctx *ctx, Writer *w, knh_bytes_t s);
void knh_write_newline(Ctx *ctx, Writer *w);
void knh_write_tab(Ctx *ctx, Writer *w);
void knh_write_indent(Ctx *ctx, Writer *w);
void knh_write__s(Ctx *ctx, Writer *w, char *s);
void knh_write__p(Ctx *ctx, Writer *w, void *ptr);
void knh_write__ifmt(Ctx *ctx, Writer *w, char *fmt, knh_int_t n);
void knh_write__ffmt(Ctx *ctx, Writer *w, char *fmt, knh_float_t n);
void knh_write__flag(Ctx *ctx, Writer *w, knh_flag_t flag);
void knh_write__type(Ctx *ctx, Writer *w, knh_type_t type);
void knh_write__class(Ctx *ctx, Writer *w, knh_class_t cid);
void knh_write__mn(Ctx *ctx, Writer *w, knh_methodn_t mn);
void knh_format(Ctx *ctx, OutputStream *b, knh_methodn_t mn, Object *o, Any *m);
String* knh_Object_movableText(Ctx *ctx, Object *b, knh_methodn_t mn, Any *m);
void knh_printf(Ctx *ctx, Writer *w, char *fmt, ...);
METHOD knh_fmethod_movableText(Ctx *ctx, Object **sfp);
/* ../class/konoha/knh_Exception.c */
void knh_Exception_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Exception_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Exception* knh_Exception_new(Ctx *ctx, Exception *b, String *e, String *msg, Object *bag);
Exception* new_Exception(Ctx *ctx, String *msg);
Exception* new_Exception__b(Ctx *ctx, knh_bytes_t msg);
Exception* new_Exception__Nue(Ctx *ctx, Nue *nue);
void knh_Exception__s(Ctx *ctx, Exception *b, OutputStream *w, Any *m);
void knh_Exception__dump(Ctx *ctx, Exception *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_Number.c */
Number *new_Number__RAW(Ctx *ctx, knh_class_t cid, knh_bytes_t t);
knh_int_t knh_Nue_toint(Number *b);
knh_int_t knh_Bool_toint(Number *b);
knh_int_t knh_String_toint(Number *b);
knh_float_t knh_Nue_tofloat(Number *b);
knh_float_t knh_Bool_tofloat(Number *b);
knh_float_t knh_String_tofloat(Number *b);
knh_int64_t knh_Nue_toint64(Number *b);
knh_int64_t knh_Bool_toint64(Number *b);
knh_int64_t knh_String_toint64(Number *b);
Number *new_Number__i(Ctx *ctx, knh_class_t cid, knh_int_t n);
Number *new_Number__f(Ctx *ctx, knh_class_t cid, knh_float_t n);
Number *new_Number__l(Ctx *ctx, knh_class_t cid, knh_int64_t n);
Number *new_Number__b(Ctx *ctx, knh_class_t cid, knh_bytes_t t);
knh_int_t knh_Number_toint(Number *n);
knh_float_t knh_Number_tofloat(Number *n);
knh_int64_t knh_Number_toint64(Number *n);
Number *new_Int__i(Ctx *ctx, knh_class_t cid, knh_int_t n);
Number *new_Int__f(Ctx *ctx, knh_class_t cid, knh_float_t n);
Number *new_Int__l(Ctx *ctx, knh_class_t cid, knh_int64_t n);
Number *new_Int__b(Ctx *ctx, knh_class_t cid, knh_bytes_t t);
knh_int_t knh_Int_toint(Number *b);
knh_float_t knh_Int_tofloat(Number *b);
knh_int64_t knh_Int_toint64(Number *b);
Number *new_Float__i(Ctx *ctx, knh_class_t cid, knh_int_t n);
Number *new_Float__f(Ctx *ctx, knh_class_t cid, knh_float_t n);
Number *new_Float__l(Ctx *ctx, knh_class_t cid, knh_int64_t n);
Number *new_Float__b(Ctx *ctx, knh_class_t cid, knh_bytes_t t);
knh_int_t knh_Float_toint(Number *b);
knh_float_t knh_Float_tofloat(Number *b);
knh_int64_t knh_Float_toint64(Number *b);
Number *new_Int64__i(Ctx *ctx, knh_class_t cid, knh_int_t n);
Number *new_Int64__f(Ctx *ctx, knh_class_t cid, knh_float_t n);
Number *new_Int64__l(Ctx *ctx, knh_class_t cid, knh_int64_t n);
Number *new_Int64__b(Ctx *ctx, knh_class_t cid, knh_bytes_t t);
knh_int_t knh_Int64_toint(Number *b);
knh_float_t knh_Int64_tofloat(Number *b);
knh_int64_t knh_Int64_toint64(Number *b);
/* ../class/konoha/knh_System.c */
System *new_System(Ctx *ctx);
char * knh_bytes_nzenvkey(knh_bytes_t t, char *buf, size_t bufsiz);
Any* knh_System_getProperty(Ctx *ctx, System *b, knh_bytes_t key);
void knh_System_setProperty(Ctx *ctx, System *b, String *key, Any *value);
char* knh_system_rootDir();
char* knh_system_path(char *buf, size_t bufsiz, char *sub, char *file);
void knh_System__dump(Ctx *ctx, System *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_Object.c */
Object * new_Object__cid(Ctx *ctx, knh_flag_t flag, knh_class_t cid);
Object *knh_Object_copy(Ctx *ctx, Object *b);
knh_class_t knh_Object_getClass(Object *b);
knh_hcode_t knh_Object_hcode(Ctx *ctx, Object *self);
knh_bytes_t knh_Object_tobytes(Ctx *ctx, Object *v);
knh_int_t knh_Object_compare(Ctx *ctx, Object *o1, Object *o2);
knh_bool_t knh_Object_equals(Ctx *ctx, Object *o1, Object *o2);
void knh__Object_opEq(Ctx *ctx, Object **sfp);
void knh__Object_opNeq(Ctx *ctx, Object **sfp);
void knh__Object_opLt(Ctx *ctx, Object **sfp);
void knh__Object_opLte(Ctx *ctx, Object **sfp);
void knh__Object_opGt(Ctx *ctx, Object **sfp);
void knh__Object_opGte(Ctx *ctx, Object **sfp);
void knh__Object_opNot(Ctx *ctx, Object **sfp);
void knh__Object_opSeq(Ctx *ctx, Object **sfp);
void knh__Object_opIsMapTo(Ctx *ctx, Object **sfp);
Object* knh_Object_Iterator(Ctx *ctx, Object *self, MapMap *map);
Object* knh_Object_String(Ctx *ctx, Object *self, MapMap *map);
void knh_Object__s(Ctx *ctx, Object *b, OutputStream *w, Any *m);
void knh_Object__dump(Ctx *ctx, Object *b, OutputStream *w, Any *m);
void knh_Object__empty(Ctx *ctx, Object *b, OutputStream *w, Any *m);
void knh_Object__refc(Ctx *ctx, Object *b, OutputStream *w, Any *m);
void knh_Object__addr(Ctx *ctx, Object *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_Connection.c */
void knh_Connection_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_Connection_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
void knh_Connection_init(Ctx *ctx, Connection *b, knh_bytes_t urn);
Connection* new_Connection(Ctx *ctx, String *urn);
void knh_Connection_close(Ctx *ctx, Connection *b);
knh_connptr_t * knh_Connection_open__nop(Ctx *ctx, knh_bytes_t url, char *uname, char *upwd);
ResultSet* knh_Connection_query__nop(Ctx *ctx, knh_connptr_t *ptr, char *sql);
void knh_Connection_close__nop(Ctx *ctx, knh_connptr_t *ptr);
void KNH_TFUNC_CONNECTION_OPEN(Ctx *ctx, char *n, f_connptr_open f);
void KNH_TFUNC_CONNECTION_QUERY(Ctx *ctx, char *n, f_connptr_query f);
void KNH_TFUNC_CONNECTION_CLOSE(Ctx *ctx, char *n, f_connptr_close f);
/* ../class/konoha/knh_Mutex__pthread.c */
void knh_Mutex_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_Mutex_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Mutex* new_Mutex(Ctx *ctx);
void knh_Mutex_lock(Ctx *ctx, Mutex *b);
void knh_Mutex_unlock(Ctx *ctx, Mutex *b);
void knh_Object_lock(Ctx *ctx, Object *b);
void knh_Object_unlock(Ctx *ctx, Object *b);
void knh_Mutex__dump(Ctx *ctx, Mutex *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_FloatUnit.c */
void knh_FloatUnit_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_FloatUnit_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
FloatUnit *new_FloatUnit__STEXT(Ctx *ctx, knh_flag_t flag, knh_class_t cid, char *urn, char *tag, knh_float_t min, knh_float_t max, knh_float_t defvalue, knh_float_t step);
FloatUnit* knh_tclass_getFloatUnit(Ctx *ctx, knh_class_t cid);
FloatUnit *knh_Float_spec(Ctx *ctx);
knh_class_t KNH_TUNIT(Ctx *ctx, char *urn, char *tag, knh_float_t min, knh_float_t max, knh_float_t defv, knh_float_t step);
void knh_FloatUnit_initId(Ctx *ctx, FloatUnit *b, knh_flag_t flag, knh_class_t cid, String *urn, String *tag);
void knh_FloatUnit_initStep(Ctx *ctx, FloatUnit *b, knh_float_t step);
void knh_FloatUnit_initMinMax(Ctx *ctx, FloatUnit *b, knh_float_t min, knh_float_t max);
void knh_FloatUnit_initDefaultValue(Ctx *ctx, FloatUnit *b, knh_float_t v);
knh_bool_t knh_FloatUnit_check(FloatUnit *b, knh_int_t value);
Float *new_Nue__asFloat(Ctx *ctx, knh_class_t cid, knh_float_t value);
Float *knh_FloatUnit_value(Ctx *ctx, FloatUnit *b, knh_float_t value);
knh_int_t knh_FloatUnit_compare(FloatUnit *b, knh_float_t v1, knh_float_t v2);
void knh_FloatUnit_format(FloatUnit *b, char *buf, knh_float_t v);
knh_bool_t knh_FloatUnit_fchk__default(FloatUnit *b, knh_float_t v);
knh_int_t knh_FloatUnit_fcmp__default(FloatUnit *b, knh_float_t v1, knh_float_t v2);
knh_int_t knh_FloatUnit_fcmp__step(FloatUnit *b, knh_float_t v1, knh_float_t v2);
void knh_FloatUnit_ffmt__default(FloatUnit *b, char *buf, knh_float_t v);
knh_bool_t knh_FloatUnit_fchk__min(FloatUnit *b, knh_float_t v);
knh_bool_t knh_FloatUnit_fchk__max(FloatUnit *b, knh_float_t v);
knh_bool_t knh_FloatUnit_fchk__range(FloatUnit *b, knh_float_t v);
/* ../class/konoha/knh_DictSet.c */
void knh_DictSet_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_DictSet_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
knh_int_t knh_DictSet_struct_compare(Ctx *ctx, Struct *s1, Struct *s2);
void knh_DictSet_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
DictSet *new_DictSet(Ctx *ctx, knh_int_t capacity);
DictSet* knh_DictSet_new(Ctx *ctx, DictSet *b, knh_int_t initialCapacity);
void knh_DictSet_sort(DictSet *b);
knh_index_t knh_DictSet_index__b(DictSet *b, knh_bytes_t kv);
String* knh_DictSet_key(DictSet *b, size_t n);
knh_uint_t knh_DictSet_value(DictSet *b, size_t n);
knh_uint_t knh_DictSet_get__b(DictSet *b, knh_bytes_t kv);
knh_int_t knh_DictSet_get(DictSet *b, String *key);
knh_bool_t knh_DictSet_opIn(Ctx *ctx, DictSet *b, Any *value);
void knh_DictSet_resize(Ctx *ctx, DictSet *b, size_t newsize);
void knh_DictSet_append(Ctx *ctx, DictSet *b, String *key, knh_uint_t value);
void knh_DictSet_set(Ctx *ctx, DictSet *b, String *key, knh_uint_t value);
void knh_DictSet_add(Ctx *ctx, DictSet *b, String *key);
void knh_DictSet_clear(Ctx *ctx, DictSet *b);
Object* knh_DictSet_key_next(Ctx *ctx, Iterator *it);
Object* knh_DictSet_Iterator(Ctx *ctx, Object *self, MapMap *map);
void knh_DictSet__dump(Ctx *ctx, DictSet *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_Runtime.c */
void knh_Runtime_struct_init(Ctx *ctx0, Struct *s1, int init, Object *cs);
void knh_Runtime_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Runtime* new_Runtime(Ctx *ctx0, knh_uint_t runtime_id);
Context *knh_Runtime_getContext(Ctx *ctx0, Runtime *b, knh_bytes_t name);
void knh_Runtime_removeContext(Ctx *ctx0, Runtime *b, knh_bytes_t name);
/* ../class/konoha/knh_Class.c */
void knh_Class_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
knh_int_t knh_Class_struct_compare(Ctx *ctx, Struct *s1, Struct *s2);
Class* new_Class__base(Ctx *ctx, knh_class_t bcid, knh_class_t cid);
Class* new_Class__type(Ctx *ctx, knh_type_t type);
knh_class_t knh_Class_cid(Class *b);
Object* knh_Class_null_next(Ctx *ctx, Iterator *it);
void knh_Class__s(Ctx *ctx, Class *b, OutputStream *w, Any *m);
void knh_Class__dump(Ctx *ctx, Class *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_Connection__ubiql.c */
knh_connptr_t* knh_Connection_open__ubiql(Ctx *ctx, knh_bytes_t url, char *uname, char *upwd);
knh_bool_t knh_ResultSet_next__ubiql(Ctx *ctx, knh_rsptr_t *rsptr, ResultSet *b);
void knh_ResultSet_free__ubiql(knh_rsptr_t *rsptr);
knh_ResultSet* knh_Connection_query__ubiql(Ctx *ctx, knh_connptr_t *conn, char *sql);
void knh_Connection_close__ubiql(Ctx *ctx, knh_connptr_t *conn);
/* ../class/konoha/knh_Bytes_byte_t.c */
size_t knh_size(size_t s);
size_t knh_strlen(void *c);
void knh_memcpy(void *d, void *s, size_t n);
void knh_bzero(void *s, size_t n);
knh_int_t knh_strcmp(char *s1, char *s2);
knh_int_t knh_strncmp(char *s1, char *s2, size_t n);
knh_bytes_t new_bytes(char *c);
knh_bytes_t new_bytes__2(void *buf, size_t len);
knh_int_t knh_bytes_strcmp(knh_bytes_t v1, knh_bytes_t v2);
knh_bool_t knh_bytes_equals(knh_bytes_t v1, knh_bytes_t v2);
knh_bool_t knh_bytes_startsWith(knh_bytes_t v1, knh_bytes_t v2);
knh_bool_t knh_bytes_endsWith(knh_bytes_t v1, knh_bytes_t v2);
knh_index_t knh_bytes_index(knh_bytes_t v, knh_int_t ch);
knh_index_t knh_bytes_rindex(knh_bytes_t v, knh_int_t ch);
knh_bytes_t knh_bytes_first(knh_bytes_t t, knh_int_t loc);
knh_bytes_t knh_bytes_last(knh_bytes_t t, knh_int_t loc);
knh_bytes_t knh_bytes_trim(knh_bytes_t t, knh_int_t ch);
knh_int_t knh_bytes_toint(knh_bytes_t t);
knh_float_t knh_bytes_tofloat(knh_bytes_t t);
knh_int_t knh_bytes_toint64(knh_bytes_t t);
/* ../class/konoha/deps/api/posix/knh_socket__posix.c */
int knh_socket_open(Ctx *ctx, char *ip_or_host, int port);
void knh_socket_close(Ctx *ctx, int sd);
knh_bool_t knh_Socket_open__deps(Ctx *ctx, knh_Socket *b, char *ip_or_host, int port);
void knh_Socket_close__deps(Ctx *ctx, knh_Socket *b);
int knh_InputStream_getc__Socket(Ctx *ctx, knh_inptr_t *ptr);
size_t knh_InputStream_read__Socket(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz);
void knh_OutputStream_putc__Socket(Ctx *ctx, knh_outptr_t *ptr, int ch);
size_t knh_OutputStream_write__Socket(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz);
void knh_OutputStream_flush__Socket(Ctx *ctx, knh_outptr_t *ptr);
/* ../class/konoha/deps/api/btron/knh_socket__btron.c */
int knh_socket_open(Ctx *ctx, char *ip_or_host, int port);
void knh_socket_close(Ctx *ctx, int sd);
knh_bool_t knh_Socket_open__deps(Ctx *ctx, knh_Socket *b, char *ip_or_host, int port);
void knh_Socket_close__deps(Ctx *ctx, knh_Socket *b);
int knh_InputStream_getc__Socket(Ctx *ctx, knh_inptr_t *ptr);
size_t knh_InputStream_read__Socket(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz);
void knh_OutputStream_putc__Socket(Ctx *ctx, knh_outptr_t *ptr, int ch);
size_t knh_OutputStream_write__Socket(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz);
void knh_OutputStream_flush__Socket(Ctx *ctx, knh_outptr_t *ptr);
/* ../class/konoha/deps/api/win32/knh_socket__win32.c */
knh_socket_t knh_socket_open(Ctx *ctx, char *ip_or_host, int port);
void knh_socket_close(Ctx *ctx, knh_socket_t sd);
knh_bool_t knh_Socket_open__deps(Ctx *ctx, knh_Socket *b, char *ip_or_host, int port);
void knh_Socket_close__deps(Ctx *ctx, knh_Socket *b);
int knh_InputStream_getc__Socket(Ctx *ctx, knh_inptr_t *ptr);
size_t knh_InputStream_read__Socket(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz);
void knh_OutputStream_putc__Socket(Ctx *ctx, knh_outptr_t *ptr, int ch);
size_t knh_OutputStream_write__Socket(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz);
void knh_OutputStream_flush__Socket(Ctx *ctx, knh_outptr_t *ptr);
/* ../class/konoha/deps/os/windows/file__windows.c */
char * knh_file_ospath(Ctx *ctx, knh_bytes_t path, char *buf, size_t bufsiz);
char * knh_file_knhpath(Ctx *ctx, knh_bytes_t path, char *buf, size_t bufsiz);
char *knh_file_getInstalledHomePath(char *buf, size_t bufsiz);
/* ../class/konoha/deps/os/linux/file__linux.c */
char * knh_file_ospath(Ctx *ctx, knh_bytes_t path, char *buf, size_t bufsiz);
char * knh_file_knhpath(Ctx *ctx, knh_bytes_t path, char *buf, size_t bufsiz);
char *knh_file_getInstalledHomePath(char *buf, size_t bufsiz);
/* ../class/konoha/deps/os/macosx/file__macosx.c */
char * knh_file_ospath(Ctx *ctx, knh_bytes_t path, char *buf, size_t bufsiz);
char * knh_file_knhpath(Ctx *ctx, knh_bytes_t path, char *buf, size_t bufsiz);
char *knh_file_getInstalledHomePath(char *buf, size_t bufsiz);
/* ../class/konoha/deps/os/tk/file__tk.c */
char * knh_file_ospath(Ctx *ctx, knh_bytes_t path, char *buf, size_t bufsiz);
char * knh_file_knhpath(Ctx *ctx, knh_bytes_t path, char *buf, size_t bufsiz);
char *knh_file_getInstalledHomePath(char *buf, size_t bufsiz);
/* ../class/konoha/knh_Int64.c */
void knh_Int64_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_Int64_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
knh_int_t knh_Int64_struct_compare(Ctx *ctx, Struct *s1, Struct *s2);
Int64* new_Int64__fast(Ctx *ctx, knh_class_t cid, knh_int64_t value);
Int64* new_Int64__checked(Ctx *ctx, knh_class_t cid, knh_int64_t value);
knh_int64_t knh_int64_max(knh_int64_t a, knh_int64_t b);
knh_int64_t knh_int64_min(knh_int64_t a, knh_int64_t b);
knh_uint64_t knh_uint64_max(knh_uint64_t a, knh_uint64_t b);
knh_uint64_t knh_uint64_min(knh_uint64_t a, knh_uint64_t b);
void knh_Int64__dump(Ctx *ctx, Int64 *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_String.c */
void knh_String_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
knh_int_t knh_String_struct_compare(Ctx *ctx, Struct *s1, Struct *s2);
void knh_String_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
knh_hcode_t knh_string_hash(knh_uchar_t *buf, knh_size_t len);
String *new_String__fast(Ctx *ctx, knh_class_t cid, knh_bytes_t t);
String *new_String__subfast(Ctx *ctx, knh_class_t cid, String *sub, knh_size_t offset, knh_size_t len);
String *new_String__checked(Ctx *ctx, knh_class_t cid, knh_bytes_t value);
String *new_String__sub(Ctx *ctx, knh_class_t cid, String *sub, knh_size_t offset, knh_size_t len);
knh_hcode_t knh_String_hcode(String *b);
char *knh_String_tochar(String *b);
char *knh_StringNULL_tochar(String *b);
knh_bytes_t knh_String_tobytes(String *b);
knh_bytes_t knh_StringNULL_tobytes(String *b);
knh_bool_t knh_String_equals(String *b, knh_bytes_t s);
knh_bool_t knh_String_startsWith(String *b, knh_bytes_t s);
knh_bool_t knh_String_endsWith(String *b, knh_bytes_t s);
size_t knh_String_getSize(String *b);
String* knh_String_opMul(Ctx *ctx, String *b, knh_int_t n);
void knh_String__s(Ctx *ctx, String *b, OutputStream *w, Any *m);
void knh_String__dump(Ctx *ctx, String *b, OutputStream *w, Any *m);
String *knh_String_EMPTY(void);
String *knh_String_NL(void);
String *knh_String_TAB(void);
String *knh_String_NULL(void);
String *knh_String_cTRUE(void);
String *knh_String_cFALSE(void);
/* ../class/konoha/knh_ClassRel.c */
void knh_ClassRel_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_ClassRel_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
ClassRel* new_ClassRel(Ctx *ctx, knh_ushort_t capacity);
void knh_ClassRel_resize(Ctx *ctx, ClassRel *b, size_t newsize);
int knh_ClassRel_util_cmp(const MapMap *m1, const MapMap *m2);
void knh_ClassRel_sort(Ctx *ctx, ClassRel *b);
void knh_ClassRel_add(Ctx *ctx, ClassRel *b, MapMap *map);
MapMapNULL *knh_ClassRel_find__first(ClassRel *b, knh_class_t tcid);
MapMapNULL *knh_ClassRel_findp__first(ClassRel *b, knh_class_t tcid);
void knh_ClassRel__dump(Ctx *ctx, ClassRel *b, OutputStream *w, Any *m);
/* ../class/konoha/knh_ExceptionHandler.c */
void knh_ExceptionHandler_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_ExceptionHandler_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
ExceptionHandler* new_ExceptionHandler(Ctx *ctx);
Object *knh_ExceptionHandler_fvalue(Ctx *ctx, knh_class_t cid);
void knh_ExceptionHandler_longjmp(Ctx *ctx, ExceptionHandler *b, Exception *e);
Exception* knh_ExceptionHandler_getCaughtException(ExceptionHandler *b);
/* ======================================================================== */

#ifdef __cplusplus
}
#endif

/* ======================================================================== */

#endif/*KONOHA__H*/
