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

#ifndef KONOHAC__H
#define KONOHAC__H

#include<konoha/konoha_config.h>
#include<konoha/konoha_t.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

/* ======================================================================== */
/* [prototype] */

/* ../class/konohac/knh_Stmt_value.c */
Stmt *new_Stmt__stmt(Ctx *ctx, Stmt *stmt);
Stmt *new_Stmt__term(Ctx *ctx, knh_flag_t flag, knh_stmt_t stt, Term *tm);
Term * new_Term__value(Ctx *ctx, Token *tk, int value);
Token *new_Token__this(Ctx *ctx, Token *tk);
Term *new_Term__name(Ctx *ctx, Token *tk, int value);
Stmt *new_Stmt__name(Ctx *ctx, Token *tk, int value);
Token *new_Token__funcname(Ctx *ctx, Token *tk, knh_bytes_t name, knh_bool_t isfunc, int value);
void knh_Stmt_add_name__first(Ctx *ctx, Stmt *b, Token *tk, knh_bytes_t name, int value);
void knh_Stmt_swap01(Ctx *ctx, Stmt *b);
Stmt* knh_Stmt_add_name__second(Ctx *ctx, Stmt *b, Token *tk, int value);
Term *new_Term__Tuple(Ctx *ctx, Token *tk);
Stmt *new_Stmt__Array(Ctx *ctx, Token *tk);
Stmt *new_Stmt__DictMap(Ctx *ctx, Token *tk);
void knh_Stmt_add_pairs(Ctx *ctx, Stmt *b, Token **ts, knh_int_t s, knh_int_t e);
void knh_Stmt_add_pair(Ctx *ctx, Stmt *stmt, Token **ts, knh_int_t s, knh_int_t e);
Stmt* new_Stmt__newClass(Ctx *ctx, Token *tk, Token *brc);
Term *new_Term__PROPN(Ctx *ctx, Token *tk, int value);
void knh_Stmt_add_printname(Ctx *ctx, Stmt *b, Token **ts, int s, int e);
/* ../class/konohac/knh_Cmpl_class.c */
void knh_Cmpl_declareClass(Ctx *ctx, Cmpl *b, Token *tke, knh_flag_t flag, knh_class_t cid, knh_class_t supcid);
/* ../class/konohac/knh_Stmt.c */
void knh_Stmt_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Stmt_terms_traverse(Ctx *ctx, Stmt *b, f_gc gc);
void knh_Stmt_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Stmt* new_Stmt(Ctx *ctx, knh_flag_t flag, knh_stmt_t stt);
void knh_Stmt_done(Ctx *ctx, Stmt *b);
Term *knh_Stmt_terms(Stmt *b, size_t n);
void knh_Stmt_terms_expand(Ctx *ctx, Stmt *b);
void knh_Stmt_terms_add__fast(Ctx *ctx, Stmt *b, Term *tm);
void knh_Stmt_terms_add(Ctx *ctx, Stmt *b, Term *tm);
Stmt *knh_Stmt_tail(Stmt *b);
void knh_Stmt_tail_append(Ctx *ctx, Stmt *b, Stmt *stmt);
void knh_Stmt_visit(Ctx *ctx, Stmt *b, f_stmtvisit fvisit, Object *v, int nest);
void knh_Stmt__s(Ctx *ctx, Stmt *b, OutputStream *w, Any *m);
void knh_Stmt__dump(Ctx *ctx, Stmt *b, OutputStream *w, Any *m);
/* ../class/konohac/knh_Token_parser.c */
knh_bool_t knh_Bytes_isTripleQuote(Bytes *b, knh_int_t ch);
Token *new_Token__ch(Ctx *ctx, InputStream *in, int_byte_t ch);
void knh_Token_toMismatchedBlock(Ctx *ctx, Token *b, int_byte_t ch, InputStream *in);
void knh_Token_padd(Ctx *ctx, Token *b, Token *tk);
void knh_Token_padd__cb(Ctx *ctx, Token *b, knh_buffer_t cb, InputStream *in);
void knh_Token_parse(Ctx *ctx, Token *b, InputStream *in);
knh_bool_t knh_bytes_isLABEL(knh_bytes_t t);
knh_bool_t knh_Token_isLABEL(Token *b);
knh_bool_t knh_bytes_isMETAN(knh_bytes_t t);
knh_bool_t knh_Token_isMETAN(Token *b);
knh_bool_t knh_bytes_isPROPN(knh_bytes_t t);
knh_bool_t knh_Token_isPROPN(Token *b);
knh_bool_t knh_bytes_isMOVTEXT(knh_bytes_t t);
knh_bool_t knh_Token_isMOVTEXT(Token *b);
knh_bool_t knh_bytes_isURN(knh_bytes_t t);
knh_bool_t knh_Token_isURN(Token *b);
knh_bool_t knh_bytes_isCLASSN(knh_bytes_t t);
knh_bool_t knh_Token_isCLASSN(Token *b);
knh_bool_t knh_bytes_isCONSTN(knh_bytes_t t);
knh_bool_t knh_Token_isCONSTN(Token *b);
knh_bool_t knh_bytes_isCLASSTN(knh_bytes_t t);
knh_bool_t knh_Token_isCLASSTN(Token *b);
knh_bool_t knh_bytes_isTYPEN(knh_bytes_t t);
knh_bool_t knh_Token_isTYPEN(Token *b);
knh_bool_t knh_bytes_isNSN(knh_bytes_t t);
knh_bool_t knh_Token_isNSN(Token *b);
knh_bool_t knh_bytes_isNSCLASSN(knh_bytes_t t);
knh_bool_t knh_Token_isNSCLASSN(Token *b);
knh_bool_t knh_bytes_isFIELDN(knh_bytes_t t);
knh_bool_t knh_Token_isFIELDN(Token *b);
knh_bool_t knh_bytes_isMETHODN(knh_bytes_t t);
knh_bool_t knh_Token_isMETHODN(Token *b);
knh_bool_t knh_bytes_isCMETHODN(knh_bytes_t t);
knh_bool_t knh_Token_isCMETHODN(Token *b);
knh_bool_t knh_bytes_isNAME(knh_bytes_t t);
knh_bool_t knh_Token_isNAME(Token *b);
knh_bool_t knh_bytes_isNEW(knh_bytes_t t);
knh_bool_t knh_Token_isNEW(Token *b);
knh_bool_t knh_bytes_isNUM(knh_bytes_t t);
knh_bool_t knh_bytes_isSTR(knh_bytes_t t);
knh_bool_t knh_bytes_isQSTR(knh_bytes_t t);
knh_bool_t knh_bytes_isFMTSTR(knh_bytes_t t);
knh_bool_t knh_Token_isANY(Token *tk);
/* ../class/konohac/knh_Stmt_expr.c */
knh_int_t knh_tokens_lastexpr(Token **ts, knh_int_t s, knh_int_t e);
knh_int_t knh_tokens_nextstmt(Token **ts, knh_int_t s, knh_int_t e);
knh_index_t knh_tokens_find(Token **ts, knh_int_t s, knh_int_t e, knh_type_t type);
knh_int_t knh_tokens_lastexpr_withlet(Token **ts, knh_int_t s, knh_int_t e);
knh_index_t knh_tokens_findlet(Token **ts, knh_int_t s, knh_int_t e);
knh_int_t knh_tokens_count(Token **ts, knh_int_t s, knh_int_t e, knh_type_t type);
Stmt *new_Stmt__expr(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
knh_bool_t knh_Term_isLTermSetter(Term *b);
knh_bool_t knh_tokens_isVariableDeclared(Token **ts, knh_int_t s, knh_int_t e);
Stmt *new_Stmt__decl(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e);
Term *new_Term__pexpr(Ctx *ctx, Token *tk);
Term *new_Term__expr(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, int value);
Token *knh_tokens_findop(Token **ts, knh_int_t s, knh_int_t e);
Stmt *new_Stmt__op(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, Token *op);
Stmt *new_Stmt__trinary(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, Token *op);
knh_bool_t knh_Token_isCast(Ctx *ctx, Token *b);
Stmt *new_Stmt__cast(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e);
void knh_Stmt_add_index(Ctx *ctx, Stmt *stmt, Token *brc, int value);
void knh_Stmt_add_exprs(Ctx *ctx, Stmt *stmt, Token **ts, knh_int_t s, knh_int_t e);
void knh_Stmt_add_stmt3(Ctx *ctx, Stmt *b, Token *tk);
void knh_Stmt_add_fromwhere(Ctx *ctx, Stmt *b, Token *tk);
/* ../class/konohac/knh_VirtualMachineCode.c */
void knh_VirtualMachineCode_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs);
void knh_VirtualMachineCode_struct_copy(Ctx *ctx, Struct *s1, Struct *s2);
void knh_VirtualMachineCode_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
VirtualMachineCode* new_VirtualMachineCode(Ctx *ctx, knh_filen_t filen, knh_nsn_t nsn, knh_bytes_t elf, knh_bytes_t dwarf);
void knh_Method_setVirtualMachineCode(Ctx *ctx, Method *b, VirtualMachineCode *code);
VirtualMachineCode *knh_Method_vmc(Method *b);
knh_bytes_t knh_VirtualMachineCode_tobytes(VirtualMachineCode *b);
knh_bytes_t knh_stackf_vmc(Ctx *ctx, Object **sf);
knh_vmc_t *knh_VirtualMachineCode_pc(VirtualMachineCode *b);
char *knh_Method_file(Method *mtd, knh_vmc_t *pc);
int knh_Method_pcline(Method *mtd, knh_vmc_t *pc);
void knh_VirtualMachineCode__dump(Ctx *ctx, VirtualMachineCode *b, OutputStream *w, Any *m);
void knh_Method__code(Ctx *ctx, Method *b, OutputStream *w, Any *m);
/* ../class/konohac/knh_Stmt_using.c */
Stmt *new_Stmt__using(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
/* ../class/konohac/stmtvisit_declv.c */
void knh_stmtvisit_declv__class(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declv__method(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declv__decl(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declv__let(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
/* ../class/konohac/knh_String_parser.c */
knh_bool_t knh_byte_isBackQuoted(knh_bytes_t t);
knh_int_t knh_write__BackQuoted(Ctx *ctx, OutputStream *w, knh_uchar_t *p);
String *new_String__parser(Ctx *ctx, knh_class_t cid, knh_flag_t pf, knh_bytes_t t);
String *new_String__UPROPN(Ctx *ctx, knh_bytes_t urn);
/* ../class/konohac/knh_Cmpl.c */
void knh_Cmpl_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Cmpl_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Cmpl *new_Cmpl(Ctx *ctx);
Cmpl* knh_Context_getCompiler(Ctx *ctx, Context *b);
void knh_Cmpl_changeNameSpace(Ctx *ctx, Cmpl *b, knh_nsn_t nsn);
NameSpace *knh_Cmpl_getNameSpace(Ctx *ctx, Cmpl *b);
Stmt *knh_konohac_parse(Ctx *ctx, InputStream *in);
knh_nsn_t knh_konohac_compile(Ctx *ctx, knh_nsn_t nsn, Stmt *stmt);
knh_nsn_t knh_konohac_eval(Ctx *ctx, knh_nsn_t nsn, InputStream *in);
/* ../class/konohac/stmtvisit_asm.c */
void knh_stmtvisit_asm__class(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__method(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declv__if(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__if(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declv__while(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__while(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declv__do(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__do(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declv__for(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__for(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declv__foreach(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__foreach(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__continue(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__break(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__goto(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declv__try(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__try(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__catch(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__throw(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__return(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__eval(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__print(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__assert(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void KNH_ASM_MOV(Ctx *ctx, Cmpl *b, knh_asmv_t n, knh_asmv_t v);
void knh_stmtvisit_asm__let(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__call(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm__err(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
/* ../class/konohac/knh_Stmt_method.c */
Stmt * new_Stmt__method(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt * new_Stmt__defun(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt * new_Stmt__lambda(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__params(Ctx *ctx, Token *tk);
Stmt *new_Stmt__param(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e);
/* ../class/konohac/knh_Cmpl_label.c */
int knh_Cmpl_nastep(Cmpl *b);
int knh_Cmpl_llstep(Cmpl *b);
void knh_Cmpl_setGlobalLabel(Ctx *ctx, Cmpl *b, String *label);
knh_bool_t knh_Cmpl_hasGlobalLabel(Ctx *ctx, Cmpl *b, knh_bytes_t label);
void knh_Cmpl_setBreakLabel(Ctx *ctx, Cmpl *b, String *label);
knh_bool_t knh_Cmpl_hasBreakLabel(Ctx *ctx, Cmpl *b, knh_bytes_t label);
knh_short_t knh_Cmpl_labelId(Ctx *ctx, Cmpl *b, knh_bytes_t label);
void KNH_ASM_LABEL(Ctx *ctx, Cmpl *b, Token *tkl);
void KNH_ASM_LABEL__b(Ctx *ctx, Cmpl *b, knh_bytes_t t);
knh_bool_t knh_Stmt_hasContinueBreak(Stmt *b);
void knh_Cmpl_lstack_push(Ctx *ctx, Cmpl *b, String *label);
StringNULL *knh_Cmpl_lstack_label(Ctx *ctx, Cmpl *b);
void knh_Cmpl_lstack_pop(Ctx *ctx, Cmpl *b);
void KNH_ASM_SETLINE(Ctx *ctx, Cmpl *b, int line);
/* ../class/konohac/knh_Cmpl_variable.c */
void knh_Cmpl_initDecl(Ctx *ctx, Cmpl *b);
void knh_Cmpl_initThisVariable(Ctx *ctx, Cmpl *b, knh_class_t this_cid);
void knh_Cmpl_declareGlobalVariable(Ctx *ctx, Cmpl *b, Token *tke, knh_flag_t flag, knh_type_t type, knh_fieldn_t fn, int isasis, Object *value);
void knh_Cmpl_declareVariable(Ctx *ctx, Cmpl *b, Token *tke, knh_flag_t flag, knh_type_t type, knh_fieldn_t fn, Object *value);
knh_index_t knh_Cmpl_indexOfVariable(Cmpl *b, knh_fieldn_t fnq);
knh_cfield_t *knh_Cmpl_cfieldOfVariable(Cmpl *b, knh_index_t idx);
knh_bool_t knh_Cmpl_existsName(Cmpl *b, knh_fieldn_t fnq);
/* ../class/konohac/stmtvisit_declm.c */
void knh_stmtvisit_declm__class(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_Cmpl_initMethodParams(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_class_t cid);
knh_class_t knh_Cmpl_getMethodClass(Ctx *ctx, Cmpl *b, Token *tk, int level);
void knh_stmtvisit_declm__method(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
/* ../class/konohac/knh_Cmpl_method.c */
void knh_Cmpl_initLocalVariables(Ctx *ctx, Cmpl *b, Stmt *stmt);
/* ../class/konohac/stmtvisit_declc.c */
void knh_stmtvisit_declc__namespace(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
char * knh_os_npath(knh_bytes_t orig, char *buf, size_t bufsiz);
void knh_stmtvisit_declc__include(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declc__uimport(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declc__uvocab(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declc__uint(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declc__ufloat(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declc__uint64(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declc__ufunc(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declc__utable(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declc__weave(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declc__class(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declc__help(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
/* ../class/konohac/knh_Token.c */
void knh_Token_struct_init(Ctx *ctx, Struct *s, int init, Object *cs);
void knh_Token_struct_traverse(Ctx *ctx, Struct *s, f_gc gc);
Token* new_Token(Ctx *ctx, knh_flag_t flag, knh_filen_t filen, knh_line_t line, knh_bytes_t t, knh_token_t tt);
Token *new_Token__text(Ctx *ctx, Token *ftk, knh_bytes_t text);
Token *new_Token__ASIS(Ctx *ctx, Token *ftk);
Token** knh_Token_ts(Token *b);
size_t knh_Token_tokens_size(Token *b);
Token* knh_Tokens(Token *b, size_t n);
void knh_Token_tokens_add(Ctx *ctx, Token *b, Token *tk);
void knh_Token_tokens_empty(Ctx *ctx, Token *b);
Token* new_Token__RAW(Ctx *ctx, knh_flag_t flag, Token *tk, Object *data);
void knh_Token_setRAW(Ctx *ctx, Token *b, Object *data);
void knh_Token_toRAW(Token *b);
Token *new_Token__using_Null(Ctx *ctx, Token *tk);
char *knh_Token_tochar(Token *b);
knh_bytes_t knh_Token_tobytes(Token *b);
void knh_Token__s(Ctx *ctx, Token *b, OutputStream *w, Any *m);
void knh_Token__dump(Ctx *ctx, Token *b, OutputStream *w, Any *m);
/* ../class/konohac/knh_Cmpl_run.c */
void knh_Cmpl_prepareRun(Ctx *ctx, Cmpl *b, Stmt *stmt);
void knh_Cmpl_commitRun(Ctx *ctx, Cmpl *b, knh_bool_t isshow);
/* ../class/konohac/knh_Cmpl_annotation.c */
void knh_Cmpl_before_declv(Ctx *ctx, Cmpl *b, Stmt *stmt, int level);
void knh_Cmpl_after_declv(Ctx *ctx, Cmpl *b, Stmt *stmt, int level);
void knh_Cmpl_before_asm(Ctx *ctx, Cmpl *b, Stmt *stmt, int level);
void knh_Cmpl_after_asm(Ctx *ctx, Cmpl *b, Stmt *stmt, int level);
/* ../class/konohac/knh_Cmpl_seval.c */
knh_bool_t knh_Term_isStaticValue(Term *b);
Object *knh_Term_value_ifStaticValue(Term *b);
String *knh_Term_getString(Term *b);
knh_type_t knh_Stmt_reqtype(Stmt *stmt, knh_type_t req, knh_index_t n);
knh_bool_t knh_Stmt_terms_seval(Ctx *ctx, Stmt *b, size_t n, knh_class_t reqc, NameSpace *ns);
knh_class_t knh_Token_toclass(Ctx *ctx, Token *b, knh_class_t def, NameSpace *ns);
knh_type_t knh_Token_totype(Ctx *ctx, Token *b, knh_class_t def, NameSpace *ns);
knh_fieldn_t knh_Token_tofieldn(Ctx *ctx, Token *b);
knh_fieldn_t knh_Token_tomethodn(Ctx *ctx, Token *b);
Token * knh_Token_seval(Ctx *ctx, Token *b, knh_class_t reqc, NameSpace *ns);
void knh_Token_toRAW__Class(Ctx *ctx, Token *b, NameSpace *ns);
void knh_Token_toRAW__Method(Ctx *ctx, Token *b, NameSpace *ns);
void knh_Token_toNumberData(Ctx *ctx, Token *b, knh_class_t reqc, NameSpace *ns);
void knh_Token_toStringData(Ctx *ctx, Token *b, knh_class_t reqc, NameSpace *ns);
Object *knh_Token_substitute_const(Ctx *ctx, Token *b);
knh_class_t knh_Token_substitute_tagcid(Ctx *ctx, Token *b, knh_bytes_t tag, knh_class_t tagcid);
void knh_Token_toConstData(Ctx *ctx, Token *b, NameSpace *ns);
Term *knh_Stmt_seval__new(Ctx *ctx, Stmt *b, knh_class_t req);
Term *knh_Stmt_seval__map(Ctx *ctx, Stmt *b, knh_class_t req);
Term *knh_Stmt_seval__call(Ctx *ctx, Stmt *b, knh_class_t req);
Term *knh_Stmt_seval__movtext(Ctx *ctx, Stmt *b, knh_class_t req);
Term *knh_Stmt_seval__op(Ctx *ctx, Stmt *b, knh_class_t req);
Term *knh_Stmt_seval__alt(Ctx *ctx, Stmt *b, knh_class_t req);
Term *knh_Stmt_seval__and(Ctx *ctx, Stmt *b, knh_class_t req);
Term *knh_Stmt_seval__or(Ctx *ctx, Stmt *b, knh_class_t req);
Term *knh_Stmt_seval__next(Ctx *ctx, Stmt *b, knh_class_t req);
/* ../class/konohac/knh_Stmt_meta.c */
knh_int_t knh_tokens_skipmeta(Token **ts, knh_int_t s, knh_int_t e);
Token *new_Token__metavalue(Ctx *ctx, Token *tk);
knh_bool_t knh_Stmt_hasMeta(Stmt *b);
void knh_Stmt_add_meta(Ctx *ctx, Stmt *b, Token **ts, knh_int_t e);
Token *knh_Stmt_getLabel(Stmt *b);
knh_flag_t knh_Stmt_metaflag__class(Ctx *ctx, Stmt *b);
knh_flag_t knh_Stmt_metaflag__method(Ctx *ctx, Stmt *b);
knh_flag_t knh_Stmt_metaflag__field(Ctx *ctx, Stmt *b);
knh_flag_t knh_Stmt_metaflag__new(Ctx *ctx, Stmt *b);
/* ../class/konohac/knh_Stmt_trycatch.c */
Stmt *new_Stmt__catch(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
/* ../class/konohac/knh_Cmpl_eprint.c */
OutputStream *konohac_perror(Ctx *ctx, Token *tk, int lv);
void knh_Token_toERR(Ctx *ctx, Token *b);
knh_bool_t knh_Term_isERR(Term *b);
knh_int_t knh_tokens_epos(knh_int_t s, knh_int_t cp, knh_int_t e);
Stmt* new_Stmt__SyntaxError(Ctx *ctx, Token** ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
void knh_Stmt_toSyntaxError(Ctx *ctx, Stmt *b, Term *tm);
/* ../class/konohac/knh_Cmpl_asm.c */
void knh_Cmpl_startCompilation(Ctx *ctx, Cmpl *b, knh_filen_t filen);
void knh_Cmpl_clear(Ctx *ctx, Cmpl *b);
void knh_Cmpl_stopCompilation(Ctx *ctx, Cmpl *b);
void knh_Cmpl_endCompilation(Ctx *ctx, Cmpl *b);
void *knh_Cmpl_asmmalloc(Ctx *ctx, Cmpl *b, size_t size);
/* ../class/konohac/knh_Cmpl_asmv.c */
knh_asmv_t new_asmv(knh_uchar_t potype, knh_uchar_t idx, knh_type_t type, Object *value);
knh_asmv_t new_asmv__OBJ(Object *v);
knh_asmv_t new_asmv__StaticValue(Ctx *ctx, Token *tk, knh_type_t req);
knh_asmv_t new_asmv__noname(Ctx *ctx, Token *tk, knh_type_t req);
knh_bool_t knh_Token_isSystemVariable(Token *tk);
knh_asmv_t new_asmv__name(Ctx *ctx, Cmpl *b, Token *tk, knh_type_t req, knh_bool_t isfirst);
void KNH_ASM_PUSH__mn(Ctx *ctx, Cmpl *b, knh_methodn_t mn, knh_bool_t isfirst);
void KNH_ASM_PUSH__asmv(Ctx *ctx, Cmpl *b, knh_asmv_t v, knh_bool_t isfirst);
knh_asmv_t KNH_ASM_TYPECHECK__asmv(Ctx *ctx, Cmpl *b, Token *tke, int at, knh_type_t type, knh_asmv_t v, knh_bool_t isautomap);
int KNH_ASM_PUSH_PARAMS(Ctx *ctx, Cmpl *b, Token *tke, Stmt *stmt, knh_type_t this_type, Method *mtd, knh_bool_t isautomap);
void KNH_ASM_CALL_METHOD(Ctx *ctx, Cmpl *b, Method *mtd, knh_type_t this_type, int c);
void KNH_ASM_DCALL_METHOD(Ctx *ctx, Cmpl *b, knh_bool_t isautomap, int c);
knh_asmv_t knh_Cmpl_asmv__call(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst);
knh_bool_t knh_methodop_isAssociative(knh_methodn_t mn);
knh_asmv_t knh_Cmpl_asmv__op(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst);
Exception *new_Exception__NoSuchConstructor(Ctx *ctx, knh_class_t cid, char *mname);
knh_asmv_t knh_Cmpl_asmv__new(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst);
knh_asmv_t knh_Cmpl_asmv__movtext(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst);
knh_asmv_t knh_Cmpl_asmv__map(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst);
knh_asmv_t knh_Cmpl_asmv__alt(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst);
knh_asmv_t knh_Cmpl_asmv__and(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst);
knh_asmv_t knh_Cmpl_asmv__or(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst);
knh_asmv_t knh_Cmpl_asmv__trinary(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t reqt, knh_bool_t isfirst);
knh_asmv_t knh_Cmpl_asmv__next(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst);
knh_asmv_t knh_Cmpl_asmv__method(Ctx *ctx, Cmpl *b, Stmt *stmt, knh_type_t req, knh_bool_t isfirst);
/* ======================================================================== */

#ifdef __cplusplus
}
#endif

/* ======================================================================== */

#endif/*KONOHAC__H*/
