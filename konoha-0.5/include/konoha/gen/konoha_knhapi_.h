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

#ifndef KONOHA_KNHAPI__H
#define KONOHA_KNHAPI__H

#include<konoha/gen/konoha_class_.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

/* ======================================================================== */
/* [MACROS] */
#define KNH_FLAG_MMF_AFFINE (KNH_FLAG_MMF_SIGNIFICANT|KNH_FLAG_MMF_SYNONYM|KNH_FLAG_MMF_TOTAL|KNH_FLAG_MMF_CONST)
#define knh_Array_n(a,n)      (a)->list[(n)]
#define knh_Array_size(a)     (a)->size
#define knh_Bytes_size(o)      (o)->size
#define knh_Bytes_value(o)     (o)->buf
#define knh_Bytes_last(o)      ((o)->buf + (o)->size)
#define knh_Bytes_tochar(b)  (char*)knh_Bytes_value(b)
#define KNH_SIZE(v)         knh_size(v)
#define B(c)     new_bytes(c)
#define B2(c,n)   new_bytes__2(c,n)
#define STEXT(c)  new_bytes__2(c,sizeof(c)-1)
#define ISB(t,c) (t.len == (sizeof(c)-1) && knh_strncmp((char*)t.buf,c,t.len) == 0)
#define KNH_DEF(ctx, cid)  konoha_getClassDefaultValue(ctx, cid)
#define KNH_DEF(ctx, cid)  konoha_getClassDefaultValue(ctx, cid)
#define KNH_STDIN          (((Context*)ctx)->in)
#define KNH_STDOUT         (((Context*)ctx)->out)
#define KNH_STDERR         (((Context*)ctx)->err)
#define new_DictSet(ctx, c)   new_DictSet0(ctx, c)
#define EXPT_unknown  ((knh_expt_t)-1)
#define EXPT_newid    ((knh_expt_t)0)
#define KNH_ASSERT_eid(eid)    KNH_ASSERT(eid < ctx->share->ExptTableSize + 1)
#define EXPTN(eid)   knh_String_tochar(knh_ExptTable_name(ctx, eid))
#define new_Exception__s(ctx, s)     new_Exception__b(ctx, B(s))
#define KNH_PERRNO(ctx, emsg, func) { \
		knh_perrno(ctx, emsg, func, __FILE__, __LINE__); \
	}\


#define KNH_THROW_OUTOFINDEX(ctx, n, max) { \
		knh_throw_OutOfIndex(ctx, n, max, __FILE__, __LINE__); \
	}\


#define knh_Float_value(o)    (o)->value
#define knh_Int_value(o)      (o)->value
#define konoha_findMapper(ctx, scid, tcid) konoha_findMapper_(ctx, scid, tcid, 1)
#define knh_Class_getMapper(ctx, scid, tcid)  konoha_findMapper_(ctx, scid, tcid, 0)
#define knh_Method_mn(mtd)    DP(mtd)->mn
#define knh_Method_mf(mtd)    DP(mtd)->mf
#define knh_MethodField_rztype(mf)   ((mf)->rtype)
#define knh_MethodField_psize(mf)    ((mf)->psize)
#define knh_Method_rztype(mtd)      ((DP(mtd)->mf)->rtype)
#define knh_Method_psize(mtd)       ((DP(mtd)->mf)->psize)
#define knh_Method_pztype(mtd,n)    knh_MethodField_pztype(DP(mtd)->mf,n)
#define knh_Class_getMethod(ctx, c, mn)    knh_Class_getMethod__(ctx, c, mn, 0)
#define knh_Class_findMethod(ctx, c, mn)   knh_Class_getMethod__(ctx, c, mn, 1)
#define CTXCLASSN(cid)     knh_Context_CLASSN(ctx,cid)
#define CTXTYPEQN(cid)     knh_Context_CLASSN(ctx,CLASS_type(cid)), TYPEQ(cid)
#define knh_Object_cid(o)           (o)->h.cid
#define knh_Object_bcid(o)          (o)->h.bcid
#define IS_NULL(o)          (((Object*)o)->h.cid == CLASS_Nue)
#define IS_NOTNULL(o)       (((Object*)o)->h.cid != CLASS_Nue)
#define IS_TRUE(o)         ((o)->h.bcid == CLASS_Boolean && ((Int*)o)->n.bvalue)
#define IS_FALSE(o)        ((o)->h.bcid == CLASS_Boolean && (((Int*)o)->n.bvalue == 0))
#define new_Boolean(ctx, c)    (c) ? KNH_TRUE : KNH_FALSE
#define BOOL_ISTRUE(o)         (o == KNH_TRUE)
#define BOOL_ISFALSE(o)        (o == KNH_FALSE)
#define new_Nue__b(ctx, txt)   new_Nue(ctx, new_String(ctx, txt, NULL));
#define new_Nue__s(ctx, txt)   new_Nue(ctx, new_String(ctx, B(txt), NULL));
#define knh_write_delim(ctx, w)    knh_write(ctx, w, STEXT(", "))
#define knh_write_dots(ctx, w)     knh_write(ctx, w, STEXT("..."))
#define knh_write__i(ctx, w, n)   knh_write__ifmt(ctx, w, KNH_INTPTR_FMT, n)
#define knh_write__u(ctx, w, n)   knh_write__ifmt(ctx, w, KNH_UINT_FMT, n)
#define knh_write__x(ctx, w, n)   knh_write__ifmt(ctx, w, KNH_INTPTR_FMTX, n)
#define knh_write__f(ctx, w, f)  knh_write__ffmt(ctx, w, KNH_FLOAT_FMT, f)
#define knh_write__e(ctx, w, f)  knh_write__ffmt(ctx, w, KNH_FLOAT_FMTE, f)
#define knh_write_fn(ctx, w, fn)   knh_write__s(ctx, w, FIELDN(fn))
#define knh_write__O(ctx, w, o)    knh_format(ctx, w, METHODN__k, o, KNH_NULL)
#define knh_String_value(o)   ((o)->str)
#define knh_String_tochar(o)  (char*)((o)->str)
#define knh_String_strlen(o)  (o)->size
#define new_String__T(ctx, text)    new_StringX__T(ctx, CLASS_String, text)
#define NSN_main           0
#define FILEN_unknown      0
#define TYPEN(type)  knh_TYPEN(ctx,type)
#define KNH_ASM_JMP(ctx, abr, l)  KNH_ASM_JMP_(ctx, abr, l);
#define sToken(o)  knh_Token_tochar(ctx, o)
#define new_TermCONST(ctx, fln, d)   TM(new_TokenCONST(ctx, fln, d))
#define TERMs_getcid(stmt, n)    CLASS_type(TERMs_gettype(stmt, n))
#define TERMs_getbcid(stmt, n)   ctx->share->ClassTable[TERMs_getcid(stmt,n)].bcid
#define KNH_OUTERPARAMS -1
#define KNH_INNERPARAMS -2
#define KNH_FLAG_PF_STDERR      KNH_FLAG_T0
#define KNH_FLAG_PF_EOL         KNH_FLAG_T1
#define KNH_FLAG_PF_TIME        KNH_FLAG_T2
#define KNH_FLAG_PF_FUNC        KNH_FLAG_T3
#define KNH_FLAG_PF_NAME        KNH_FLAG_T4
#define KNH_FLAG_PF_BOL         KNH_FLAG_T7
#define KNH_THROW(ctx, e) knh_throw(ctx, UP(e), KNH_SAFEFILE(__FILE__), __LINE__)
#define KNH_THROWs(ctx, s) \
	knh_throwException(ctx, new_Exception__b(ctx, B(s)), KNH_SAFEFILE(__FILE__), __LINE__); \


#define KNH_THROWf(ctx, fmt, ...) \
	char throcwb_[256]; \
	knh_snprintf(throcwb_, sizeof(throcwb_), fmt, ## __VA_ARGS__); \
	knh_throwException(ctx, new_Exception__b(ctx, B(throcwb_)), KNH_SAFEFILE(__FILE__), __LINE__); \


#define TODO_THROW(ctx) knh_throw_TODO(ctx, (char*)__FILE__, __LINE__, (char*)__FUNCTION__)
#define KNH_SYS(ctx, n)    konoha_getSystemConst(ctx, n)
#define KNH_SYS_CTX    0
#define KNH_SYS_STDIN  1
#define KNH_SYS_STDOUT 2
#define KNH_SYS_STDERR 3
#define KNH_SYS_OS     4
#define KNH_SYS_SCRIPT 5
#define FIELDN(fn) knh_String_tochar(konoha_getFieldName(ctx, fn))
#define FILEIDN(fileid) knh_String_tochar(konoha_getFileName(ctx, fileid))

/* ======================================================================== */
/* [PROTOTYPE] */
KNHAPI(void) konoha_addAffineMapper(Ctx *ctx, knh_class_t scid, char *text, knh_float_t scale, knh_float_t shift);
KNHAPI(knh_Array_t*) new_Array(Ctx *ctx, knh_class_t p1, size_t capacity);
KNHAPI(void) knh_Array_add(Ctx *ctx, Array *o, Any *value);
KNHAPI(Bytes*) new_Bytes(Ctx *ctx, size_t capacity);
KNHAPI(knh_bytes_t) knh_Bytes_tobytes(Bytes *o);
KNHAPI(void) knh_Bytes_clear(Bytes *o, size_t pos);
KNHAPI(void) knh_Bytes_ensureSize(Ctx *ctx, Bytes *o, size_t len);
KNHAPI(void) knh_Bytes_putc(Ctx *ctx, Bytes *o, int ch);
KNHAPI(void) knh_Bytes_write(Ctx *ctx, Bytes *o, knh_bytes_t v);
KNHAPI(knh_bytes_t) new_bytes(char *c);
KNHAPI(knh_bytes_t) new_bytes__2(char *buf, size_t len);
KNHAPI(int) knh_bytes_indexOf(knh_bytes_t base, knh_bytes_t delim);
KNHAPI(int) knh_bytes_strcmp(knh_bytes_t v1, knh_bytes_t v2);
KNHAPI(int) knh_bytes_strcasecmp(knh_bytes_t v1, knh_bytes_t v2);
KNHAPI(knh_bool_t) knh_bytes_equals(knh_bytes_t v1, knh_bytes_t v2);
KNHAPI(knh_bool_t) knh_bytes_equalsIgnoreCase(knh_bytes_t v1, knh_bytes_t v2);
KNHAPI(knh_bool_t) knh_bytes_startsWith(knh_bytes_t v1, knh_bytes_t v2);
KNHAPI(knh_bool_t) knh_bytes_endsWith(knh_bytes_t v1, knh_bytes_t v2);
KNHAPI(knh_index_t) knh_bytes_index(knh_bytes_t v, knh_intptr_t ch);
KNHAPI(knh_index_t) knh_bytes_rindex(knh_bytes_t v, knh_intptr_t ch);
KNHAPI(knh_bytes_t) knh_bytes_first(knh_bytes_t t, knh_intptr_t loc);
KNHAPI(knh_bytes_t) knh_bytes_last(knh_bytes_t t, knh_intptr_t loc);
KNHAPI(knh_bytes_t) knh_bytes_skipscheme(knh_bytes_t t);
KNHAPI(char*) knh_format_bytes(char *buf, size_t bufsiz, knh_bytes_t t);
KNHAPI(knh_intptr_t) knh_bytes_toint(knh_bytes_t t);
KNHAPI(knh_float_t) knh_bytes_tofloat(knh_bytes_t t);
KNHAPI(knh_int64_t) knh_bytes_toint64(knh_bytes_t t);
KNHAPI(String*) new_String__fbcnv(Ctx *ctx, String *s, knh_fbyteconv fbcnv, BytesConv *bc);
KNHAPI(void) knh_putsfp(Ctx *ctx, knh_sfp_t *lsfp, int n, Object *obj);
KNHAPI(void) knh_Closure_invokesfp(Ctx *ctx, Closure *c, knh_sfp_t *lsfp, int argc);
KNHAPI(knh_sfp_t*) knh_Closure_invokef(Ctx *ctx, Closure *c, const char *fmt, ...);
KNHAPI(Exception*) new_Exception(Ctx *ctx, String *msg);
KNHAPI(Exception*) new_Exception__b(Ctx *ctx, knh_bytes_t msg);
KNHAPI(void) knh_perrno(Ctx *ctx, char *emsg, char *func, char *file, int line);
KNHAPI(void) knh_throw_OutOfIndex(Ctx *ctx, knh_int_t n, size_t max, char *file, int line);
KNHAPI(ClassSpec*) new_Unit(Ctx *ctx, char *tag, knh_float_t min, knh_float_t max, knh_float_t defv, knh_float_t step);
KNHAPI(InputStream*) new_InputStream__io(Ctx *ctx, String *urn, knh_io_t fd, knh_iodrv_t *drv);
KNHAPI(InputStream*) new_InputStream__FILE(Ctx *ctx, String *urn, FILE *fp, knh_iodrv_t *drv);
KNHAPI(InputStream*) new_FileInputStream(Ctx *ctx, knh_bytes_t file);
KNHAPI(InputStream*) new_BytesInputStream(Ctx *ctx, Bytes *ba, size_t s, size_t e);
KNHAPI(InputStream*) new_StringInputStream(Ctx *ctx, String *str, size_t s, size_t e);
KNHAPI(Int*) new_Int(Ctx *ctx, knh_int_t value);
KNHAPI(Int*) new_IntX__fast(Ctx *ctx, knh_class_t cid, knh_int_t value);
KNHAPI(Int*) new_IntX(Ctx *ctx, knh_class_t cid, knh_int_t value);
KNHAPI(void) knh_Glue_init(Ctx *ctx, knh_Glue_t *g, void *ptr, knh_fgfree gfree);
KNHAPI(Object*) new_Glue(Ctx *ctx, char *lname, void *ptr, knh_fgfree gfree);
KNHAPI(OutputStream*) new_OutputStream__io(Ctx *ctx, String *urn, knh_io_t fd, knh_iodrv_t *drv);
KNHAPI(OutputStream*) new_OutputStream__FILE(Ctx *ctx, String *urn, FILE *fp, knh_iodrv_t *drv);
KNHAPI(OutputStream*) new_FileOutputStream(Ctx *ctx, knh_bytes_t file, char *mode);
KNHAPI(OutputStream*) new_BytesOutputStream(Ctx *ctx, Bytes *ba);
KNHAPI(void) knh_putc(Ctx *ctx, OutputStream *w, int ch);
KNHAPI(void) knh_write(Ctx *ctx, OutputStream *w, knh_bytes_t s);
KNHAPI(void) knh_flush(Ctx *ctx, OutputStream *w);
KNHAPI(void) knh_print(Ctx *ctx, OutputStream *w, knh_bytes_t s);
KNHAPI(void) knh_println(Ctx *ctx, OutputStream *w, knh_bytes_t s);
KNHAPI(void) knh_write_EOL(Ctx *ctx, OutputStream *w);
KNHAPI(void) knh_write_TAB(Ctx *ctx, OutputStream *w);
KNHAPI(void) knh_write_BOL(Ctx *ctx, OutputStream *w);
KNHAPI(void) knh_format(Ctx *ctx, OutputStream *w, knh_methodn_t mn, Object *o, Any *m);
KNHAPI(void) knh_printf(Ctx *ctx, OutputStream *w, char *fmt, ...);
KNHAPI(void) konoha_says(Ctx *ctx, int type, char *fmt, ...);
KNHAPI(void) knh_ResultSet_initColumn(Ctx *ctx, ResultSet *o, size_t column_size);
KNHAPI(void) knh_ResultSet_setName(Ctx *ctx, ResultSet *o, size_t n, String *name);
KNHAPI(void) knh_ResultSet_initData(Ctx *ctx, ResultSet *o);
KNHAPI(void) knh_ResultSet_setInt(Ctx *ctx, ResultSet *o, size_t n, knh_int_t value);
KNHAPI(void) knh_ResultSet_setFloat(Ctx *ctx, ResultSet *o, size_t n, knh_float_t value);
KNHAPI(void) knh_ResultSet_setText(Ctx *ctx, ResultSet *o, size_t n, knh_bytes_t t);
KNHAPI(void) knh_ResultSet_setBlob(Ctx *ctx, ResultSet *o, size_t n, knh_bytes_t t);
KNHAPI(void) knh_ResultSet_setNULL(Ctx *ctx, ResultSet *o, size_t n);
KNHAPI(String*) new_String(Ctx *ctx, knh_bytes_t t, String *orign);
KNHAPI(knh_bytes_t) knh_String_tobytes(String *o);
KNHAPI(knh_bytes_t) knh_StringNULL_tobytes(String *o, knh_bytes_t def);
KNHAPI(void) konoha_addParserDriver(Ctx *ctx, char *alias, knh_parser_drvapi_t *d);
KNHAPI(ClassSpec*) new_Vocabulary(Ctx *ctx, char *lang, char *defval, ...);
KNHAPI(void) konoha_addVocabularyMapper(Ctx *ctx, knh_class_t scid, char *text);
KNHAPI(void) konoha_setSystemPropertyText(Ctx *ctx, char *key, char *value);
KNHAPI(void) konoha_addAliasURN(Ctx *ctx, char *alias, char *urn);
KNHAPI(FILE*) knh_fopen(Ctx *ctx, char *filename, char *mode);
KNHAPI(size_t) knh_fgetc(Ctx *ctx, FILE *fp);
KNHAPI(size_t) knh_fread(Ctx *ctx, void *ptr, size_t size, FILE *fp);
KNHAPI(size_t) knh_fwrite(Ctx *ctx, void *ptr, size_t size, FILE *fp);
KNHAPI(int) knh_fflush(Ctx *ctx, FILE *fp);
KNHAPI(int) knh_fclose(Ctx *ctx, FILE *fp);
KNHAPI(void) konoha_addIODriver(Ctx *ctx, char *alias, knh_iodrv_t *d);
KNHAPI(void) konoha_addRegexDriver(Ctx *ctx, char *alias, knh_regex_drvapi_t *d);
KNHAPI(knh_intptr_t) knh_socket_open(Ctx *ctx, char *ip_or_host, int port);
KNHAPI(int) knh_socket_send(Ctx *ctx, knh_intptr_t sd, char *buf, size_t bufsiz, int flags);
KNHAPI(int) knh_socket_recv(Ctx *ctx, knh_intptr_t sd, char *buf, size_t bufsiz, int flags);
KNHAPI(int) knh_socket_close(Ctx *ctx, knh_intptr_t sd);
KNHAPI(void) konoha_addDBDriver(Ctx *ctx, char *alias, knh_db_drvapi_t *d);
KNHAPI(void) konoha_SETv(Ctx *ctx, Object **v, Object *o);
KNHAPI(void) konoha_FINALv(Ctx *ctx, Object **v);
KNHAPI(char*) knh_format_ospath(Ctx *ctx, char *buf, size_t bufsiz, knh_bytes_t path);
KNHAPI(Ctx*) konoha_getCurrentContext(void);
KNHAPI(Ctx*) konoha_getThreadContext(Ctx *ctx);
KNHAPI(int) konoha_isDebugMode2();
KNHAPI(int) konoha_parseopt(konoha_t konoha, int argc, char **argv);
KNHAPI(char*) konoha_eval(konoha_t konoha, char *script);
KNHAPI(void) konoha_readFile(Ctx *ctx, char *fpath);
KNHAPI(void) konoha_read(konoha_t konoha, char *fpath);
KNHAPI(int) konoha_main(konoha_t konoha, int argc, char **argv);
KNHAPI(void) konoha_shell(konoha_t konoha);
KNHAPI(char*) KNH_SAFEFILE(char *file);
KNHAPI(Object*) new_Object_boxing(Ctx *ctx, knh_class_t cid, knh_sfp_t *sfp);
KNHAPI(void) knh_sfp_boxing(Ctx *ctx, knh_sfp_t *sfp);
KNHAPI(void) knh_sfp_unboxing(Ctx *ctx, knh_sfp_t *sfp);
KNHAPI(void) knh_esp1_sformat(Ctx *ctx, Method *mtd, OutputStream *w, Any *m);
KNHAPI(void) knh_esp1_format(Ctx *ctx, knh_methodn_t mn, OutputStream *w, Any *m);
KNHAPI(void) knh_throw_TODO(Ctx *ctx, char *file, int line, char *func);
KNHAPI(void) knh_throw_bugstop(Ctx *ctx, char *file, int line, char *func);
KNHAPI(void) knh_throwException(Ctx *ctx, Exception *e, char *file, int line);
KNHAPI(void) knh_throw__s(Ctx *ctx, char *msg, char *file, int line);
KNHAPI(void) knh_throw(Ctx *ctx, Object *e, char *file, int line);
KNHAPI(void) konoha_throwSecurityException(void);
KNHAPI(void) konoha_loadIntConstData(Ctx *ctx, knh_IntConstData_t *data);
KNHAPI(void) konoha_loadFloatConstData(Ctx *ctx, knh_FloatConstData_t *data);
KNHAPI(void) konoha_loadStringConstData(Ctx *ctx, knh_StringConstData_t *data);
KNHAPI(void) konoha_addClassSpecFunc(Ctx *ctx, char *urn, knh_fspec func);
KNHAPI(konoha_t) konoha_open(size_t stacksize);
KNHAPI(void) konoha_close(konoha_t konoha);

#ifdef __cplusplus
}
#endif

/* ======================================================================== */

#endif/*KONOHA_KNHAPI__H*/
