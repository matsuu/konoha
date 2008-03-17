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

#ifndef KONOHAC_TOKEN__H
#define KONOHAC_TOKEN__H

#include<konoha/konoha_t.h>
#include<konoha/class/konohac.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

/* ======================================================================== */
/* TT_MACRO knh_token_t */
#define TT_UKNOWN                       0
#define TT_NAMESPACE                    ((knh_token_t)1)
#define TT_INCLUDE                      ((knh_token_t)2)
#define TT_USING                        ((knh_token_t)3)
#define TT_WEAVE                        ((knh_token_t)4)
#define TT_CLASS                        ((knh_token_t)5)
#define TT_EXTENDS                      ((knh_token_t)6)
#define TT_IMPLEMENTS                   ((knh_token_t)7)
#define TT_IF                           ((knh_token_t)8)
#define TT_ELSE                         ((knh_token_t)9)
#define TT_TRY                          ((knh_token_t)10)
#define TT_CATCH                        ((knh_token_t)11)
#define TT_FINALLY                      ((knh_token_t)12)
#define TT_DO                           ((knh_token_t)13)
#define TT_WHILE                        ((knh_token_t)14)
#define TT_FOR                          ((knh_token_t)15)
#define TT_FOREACH                      ((knh_token_t)16)
#define TT_FROM                         ((knh_token_t)17)
#define TT_WHERE                        ((knh_token_t)18)
#define TT_CONTINUE                     ((knh_token_t)19)
#define TT_BREAK                        ((knh_token_t)20)
#define TT_GOTO                         ((knh_token_t)21)
#define TT_THROW                        ((knh_token_t)22)
#define TT_RETURN                       ((knh_token_t)23)
#define TT_EVAL                         ((knh_token_t)24)
#define TT_ASSERT                       ((knh_token_t)25)
#define TT_PRINT                        ((knh_token_t)26)
#define TT_HELP                         ((knh_token_t)27)
#define TT_BRACE                        ((knh_token_t)28)
#define TT_PARENTHESIS                  ((knh_token_t)29)
#define TT_BRANCET                      ((knh_token_t)30)
#define TT_DOTS                         ((knh_token_t)31)
#define TT_SEMICOLON                    ((knh_token_t)32)
#define TT_COMMA                        ((knh_token_t)33)
#define TT_LET                          ((knh_token_t)34)
#define TT_LSHIFTE                      ((knh_token_t)35)
#define TT_RSHIFTE                      ((knh_token_t)36)
#define TT_ADDE                         ((knh_token_t)37)
#define TT_SUBE                         ((knh_token_t)38)
#define TT_MULE                         ((knh_token_t)39)
#define TT_DIVE                         ((knh_token_t)40)
#define TT_MODE                         ((knh_token_t)41)
#define TT_BITORE                       ((knh_token_t)42)
#define TT_BITANDE                      ((knh_token_t)43)
#define TT_ALTLET                       ((knh_token_t)44)
#define TT_QUESTION                     ((knh_token_t)45)
#define TT_SUBSET                       ((knh_token_t)46)
#define TT_SLICE                        ((knh_token_t)47)
#define TT_OFFSET                       ((knh_token_t)48)
#define TT_COLON                        ((knh_token_t)49)
#define TT_PSLICE                       ((knh_token_t)50)
#define TT_POFFSET                      ((knh_token_t)51)
#define TT_OR                           ((knh_token_t)52)
#define TT_AND                          ((knh_token_t)53)
#define TT_NOT                          ((knh_token_t)54)
#ifndef METHODN_opNot
#define METHODN_opNot                   METHODN_NONAME
#endif
#define TT_INSTANCEOF                   ((knh_token_t)55)
#ifndef METHODN_opInstanceof
#define METHODN_opInstanceof            METHODN_NONAME
#endif
#define TT_IN                           ((knh_token_t)56)
#ifndef METHODN_opIn
#define METHODN_opIn                    METHODN_NONAME
#endif
#define TT_SEQ                          ((knh_token_t)57)
#ifndef METHODN_opSeq
#define METHODN_opSeq                   METHODN_NONAME
#endif
#define TT_ISMAPTO                      ((knh_token_t)58)
#ifndef METHODN_opIsMapTo
#define METHODN_opIsMapTo               METHODN_NONAME
#endif
#define TT_EQ                           ((knh_token_t)59)
#ifndef METHODN_opEq
#define METHODN_opEq                    METHODN_NONAME
#endif
#define TT_NEQ                          ((knh_token_t)60)
#ifndef METHODN_opNeq
#define METHODN_opNeq                   METHODN_NONAME
#endif
#define TT_LT                           ((knh_token_t)61)
#ifndef METHODN_opLt
#define METHODN_opLt                    METHODN_NONAME
#endif
#define TT_LTE                          ((knh_token_t)62)
#ifndef METHODN_opLte
#define METHODN_opLte                   METHODN_NONAME
#endif
#define TT_GT                           ((knh_token_t)63)
#ifndef METHODN_opGt
#define METHODN_opGt                    METHODN_NONAME
#endif
#define TT_GTE                          ((knh_token_t)64)
#ifndef METHODN_opGte
#define METHODN_opGte                   METHODN_NONAME
#endif
#define TT_LSHIFT                       ((knh_token_t)65)
#ifndef METHODN_opLShift
#define METHODN_opLShift                METHODN_NONAME
#endif
#define TT_RSHIFT                       ((knh_token_t)66)
#ifndef METHODN_opRShift
#define METHODN_opRShift                METHODN_NONAME
#endif
#define TT_ADD                          ((knh_token_t)67)
#ifndef METHODN_opAdd
#define METHODN_opAdd                   METHODN_NONAME
#endif
#define TT_SUB                          ((knh_token_t)68)
#ifndef METHODN_opSub
#define METHODN_opSub                   METHODN_NONAME
#endif
#define TT_MOD                          ((knh_token_t)69)
#ifndef METHODN_opMod
#define METHODN_opMod                   METHODN_NONAME
#endif
#define TT_DIV                          ((knh_token_t)70)
#ifndef METHODN_opDiv
#define METHODN_opDiv                   METHODN_NONAME
#endif
#define TT_MUL                          ((knh_token_t)71)
#ifndef METHODN_opMul
#define METHODN_opMul                   METHODN_NONAME
#endif
#define TT_LOGICALOR                    ((knh_token_t)72)
#ifndef METHODN_opLogicalOr
#define METHODN_opLogicalOr             METHODN_NONAME
#endif
#define TT_LOGICALAND                   ((knh_token_t)73)
#ifndef METHODN_opLogicalAnd
#define METHODN_opLogicalAnd            METHODN_NONAME
#endif
#define TT_ALT                          ((knh_token_t)74)
#define TT_LOGICALNOT                   ((knh_token_t)75)
#ifndef METHODN_opLogicalNot
#define METHODN_opLogicalNot            METHODN_NONAME
#endif
#define TT_LOGICALXOR                   ((knh_token_t)76)
#ifndef METHODN_opLogicalXor
#define METHODN_opLogicalXor            METHODN_NONAME
#endif
#define TT_NEXT                         ((knh_token_t)77)
#define TT_PREV                         ((knh_token_t)78)
#define TT_SHARP                        ((knh_token_t)79)
#define TT_ASIS                         ((knh_token_t)80)
#define TT_NUM                          ((knh_token_t)81)
#define TT_STR                          ((knh_token_t)82)
#define TT_QSTR                         ((knh_token_t)83)
#define TT_FMTSTR                       ((knh_token_t)84)
#define TT_LABEL                        ((knh_token_t)85)
#define TT_METAN                        ((knh_token_t)86)
#define TT_PROPN                        ((knh_token_t)87)
#define TT_URN                          ((knh_token_t)88)
#define TT_MOVTEXT                      ((knh_token_t)89)
#define TT_CONSTN                       ((knh_token_t)90)
#define TT_TYPEN                        ((knh_token_t)91)
#define TT_NAME                         ((knh_token_t)92)
#define TT_RAW                          ((knh_token_t)93)
#define TT_ERR                          ((knh_token_t)94)

/* ------------------------------------------------------------------------ */

/* ======================================================================== */
/* STT_MACRO knh_stmt_t */
#define STT_DONE                        ((knh_stmt_t)0)
#define STT_NAMESPACE                   ((knh_stmt_t)1)
#define STT_INCLUDE                     ((knh_stmt_t)2)
#define STT_UIMPORT                     ((knh_stmt_t)3)
#define STT_UVOCAB                      ((knh_stmt_t)4)
#define STT_UINT                        ((knh_stmt_t)5)
#define STT_UINT64                      ((knh_stmt_t)6)
#define STT_UFLOAT                      ((knh_stmt_t)7)
#define STT_UTABLE                      ((knh_stmt_t)8)
#define STT_UFUNC                       ((knh_stmt_t)9)
#define STT_WEAVE                       ((knh_stmt_t)10)
#define STT_CLASS                       ((knh_stmt_t)11)
#define STT_IMPLEMENTS                  ((knh_stmt_t)12)
#define STT_METHOD                      ((knh_stmt_t)13)
#define STT_DECL                        ((knh_stmt_t)14)
#define STT_IF                          ((knh_stmt_t)15)
#define STT_TRY                         ((knh_stmt_t)16)
#define STT_CATCH                       ((knh_stmt_t)17)
#define STT_DO                          ((knh_stmt_t)18)
#define STT_WHILE                       ((knh_stmt_t)19)
#define STT_FOR                         ((knh_stmt_t)20)
#define STT_FOREACH                     ((knh_stmt_t)21)
#define STT_CONTINUE                    ((knh_stmt_t)22)
#define STT_BREAK                       ((knh_stmt_t)23)
#define STT_GOTO                        ((knh_stmt_t)24)
#define STT_THROW                       ((knh_stmt_t)25)
#define STT_RETURN                      ((knh_stmt_t)26)
#define STT_EVAL                        ((knh_stmt_t)27)
#define STT_PRINT                       ((knh_stmt_t)28)
#define STT_ASSERT                      ((knh_stmt_t)29)
#define STT_HELP                        ((knh_stmt_t)30)
#define STT_NEW                         ((knh_stmt_t)31)
#define STT_MAP                         ((knh_stmt_t)32)
#define STT_LET                         ((knh_stmt_t)33)
#define STT_CALL                        ((knh_stmt_t)34)
#define STT_MOVTEXT                     ((knh_stmt_t)35)
#define STT_TRINARY                     ((knh_stmt_t)36)
#define STT_OP                          ((knh_stmt_t)37)
#define STT_ALT                         ((knh_stmt_t)38)
#define STT_AND                         ((knh_stmt_t)39)
#define STT_OR                          ((knh_stmt_t)40)
#define STT_NEXT                        ((knh_stmt_t)41)
#define STT_META                        ((knh_stmt_t)42)
#define STT_ERR                         ((knh_stmt_t)43)
#define STT_MAXSIZ                      ((knh_stmt_t)44)

/* ------------------------------------------------------------------------ */

/* ======================================================================== */
knh_bool_t knh_token_isNested(knh_token_t tt);
knh_bool_t knh_token_isKeyword(knh_token_t tt);
knh_bool_t knh_token_isStatement(knh_token_t tt);
knh_bool_t knh_token_isInExpr(knh_token_t tt);
knh_bool_t knh_token_isNotFirst(knh_token_t tt);
char* knh_token_tochar(knh_token_t tt);
knh_methodn_t knh_token_tomethodn(knh_token_t tt);
knh_bool_t knh_Token_isOP(Token *b);
knh_bool_t knh_methodn_isOperator(knh_methodn_t mn);
char *knh_methodop_tochar(knh_methodn_t mn);
Token *new_Token__parse(Ctx *ctx, knh_flag_t flag, knh_filen_t filen, knh_line_t fln, knh_bytes_t t);
Stmt *new_Stmt__namespace(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__include(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__weave(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__class(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__if(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__do(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__while(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__for(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__foreach(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__continue(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__break(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__goto(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__throw(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__return(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__eval(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__assert(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__print(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__help(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__stmt1(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);
Stmt *new_Stmt__block(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e);
size_t knh_stmt_initsize(knh_stmt_t stt);
char* knh_stmt_tochar(knh_stmt_t stt);
knh_bool_t knh_stmt_isDecl(knh_stmt_t stt);
knh_bool_t knh_stmt_isDeclInClass(knh_stmt_t stt);
knh_bool_t knh_stmt_isStatement(knh_stmt_t stt);
knh_bool_t knh_stmt_isExpr(knh_stmt_t stt);
knh_bool_t knh_stmt_isEval(knh_stmt_t stt);
void knh_stmtvisit_declc(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declm(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_declv(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
void knh_stmtvisit_asm(Ctx *ctx, Stmt *stmt, Object *v, int level, int step);
Term* knh_Term_seval(Ctx *ctx, Term *b, knh_class_t req, NameSpace *ns);
knh_asmv_t knh_Cmpl_asmv(Ctx *ctx, Cmpl *b, Term *tm, knh_type_t req, int sp);

#ifdef __cplusplus
}
#endif

/* ======================================================================== */

#endif/*KONOHAC_TOKEN__H*/
