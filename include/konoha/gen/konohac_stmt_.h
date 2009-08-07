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

#ifndef KONOHAC_STMT__H
#define KONOHAC_STMT__H

#include<konoha/konoha_t.h>
#include<konoha/konoha_class.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

/* ======================================================================== */
/* TT_MACRO knh_token_t */
#define TT_NAMESPACE                    ((knh_token_t)0)
#define TT_IMPORT                       ((knh_token_t)1)
#define TT_PRAGMA                       ((knh_token_t)2)
#define TT_USING                        ((knh_token_t)3)
#define TT_WITH                         ((knh_token_t)4)
#define TT_CLASS                        ((knh_token_t)5)
#define TT_EXTENDS                      ((knh_token_t)6)
#define TT_IMPLEMENTS                   ((knh_token_t)7)
#define TT_METHOD                       ((knh_token_t)8)
#define TT_FUNCTION                     ((knh_token_t)9)
#define TT_FORMAT                       ((knh_token_t)10)
#define TT_RETURN                       ((knh_token_t)11)
#define TT_MAPMAP                       ((knh_token_t)12)
#define TT_WEAVE                        ((knh_token_t)13)
#define TT_ASPECT                       ((knh_token_t)14)
#define TT_IF                           ((knh_token_t)15)
#define TT_ELSE                         ((knh_token_t)16)
#define TT_SWITCH                       ((knh_token_t)17)
#define TT_CASE                         ((knh_token_t)18)
#define TT_WHILE                        ((knh_token_t)19)
#define TT_DO                           ((knh_token_t)20)
#define TT_FOR                          ((knh_token_t)21)
#define TT_FOREACH                      ((knh_token_t)22)
#define TT_FROM                         ((knh_token_t)23)
#define TT_WHERE                        ((knh_token_t)24)
#define TT_BREAK                        ((knh_token_t)25)
#define TT_CONTINUE                     ((knh_token_t)26)
#define TT_TRY                          ((knh_token_t)27)
#define TT_CATCH                        ((knh_token_t)28)
#define TT_FINALLY                      ((knh_token_t)29)
#define TT_THROW                        ((knh_token_t)30)
#define TT_REGISTER                     ((knh_token_t)31)
#define TT_PRINT                        ((knh_token_t)32)
#define TT_ASSERT                       ((knh_token_t)33)
#define TT_BRACE                        ((knh_token_t)34)
#define TT_PARENTHESIS                  ((knh_token_t)35)
#define TT_BRANCET                      ((knh_token_t)36)
#define TT_PROMPT                       ((knh_token_t)37)
#define TT_DOTS                         ((knh_token_t)38)
#define TT_SEMICOLON                    ((knh_token_t)39)
#define TT_COMMA                        ((knh_token_t)40)
#define TT_FUNCMAP                      ((knh_token_t)41)
#define TT_LET                          ((knh_token_t)42)
#define TT_LSHIFTE                      ((knh_token_t)43)
#define TT_RSHIFTE                      ((knh_token_t)44)
#define TT_ADDE                         ((knh_token_t)45)
#define TT_SUBE                         ((knh_token_t)46)
#define TT_DIVE                         ((knh_token_t)47)
#define TT_MODE                         ((knh_token_t)48)
#define TT_MULE                         ((knh_token_t)49)
#define TT_BITANDE                      ((knh_token_t)50)
#define TT_BITORE                       ((knh_token_t)51)
#define TT_ALTLET                       ((knh_token_t)52)
#define TT_QUESTION                     ((knh_token_t)53)
#define TT_ITR                          ((knh_token_t)54)
#define TT_SUBSET                       ((knh_token_t)55)
#define TT_OFFSET                       ((knh_token_t)56)
#define TT_COLON                        ((knh_token_t)57)
#define TT_ALT                          ((knh_token_t)58)
#define TT_OR                           ((knh_token_t)59)
#define TT_AND                          ((knh_token_t)60)
#define TT_NOT                          ((knh_token_t)61)
#define TT_INSTANCEOF                   ((knh_token_t)62)
#define TT_ISA                          ((knh_token_t)63)
#define TT_AS                           ((knh_token_t)64)
#define TT_HAS                          ((knh_token_t)65)
#define TT_IS                           ((knh_token_t)66)
#define TT_TO                           ((knh_token_t)67)
#define TT_EQ                           ((knh_token_t)68)
#define TT_NEQ                          ((knh_token_t)69)
#define TT_LT                           ((knh_token_t)70)
#define TT_LTE                          ((knh_token_t)71)
#define TT_GT                           ((knh_token_t)72)
#define TT_GTE                          ((knh_token_t)73)
#define TT_MATCH                        ((knh_token_t)74)
#define TT_LSHIFT                       ((knh_token_t)75)
#define TT_RSHIFT                       ((knh_token_t)76)
#define TT_ADD                          ((knh_token_t)77)
#define TT_SUB                          ((knh_token_t)78)
#define TT_DIV                          ((knh_token_t)79)
#define TT_MOD                          ((knh_token_t)80)
#define TT_MUL                          ((knh_token_t)81)
#define TT_LAND                         ((knh_token_t)82)
#define TT_LOR                          ((knh_token_t)83)
#define TT_LNOT                         ((knh_token_t)84)
#define TT_XOR                          ((knh_token_t)85)
#define TT_NEXT                         ((knh_token_t)86)
#define TT_PREV                         ((knh_token_t)87)
#define TT_NEG                          ((knh_token_t)88)
#define TT_NUM                          ((knh_token_t)89)
#define knh_Token_isNUM(tk_)            (SP(tk_)->tt == TT_NUM)
#define TT_STR                          ((knh_token_t)90)
#define knh_Token_isSTR(tk_)            (SP(tk_)->tt == TT_STR)
#define TT_TSTR                         ((knh_token_t)91)
#define knh_Token_isTSTR(tk_)           (SP(tk_)->tt == TT_TSTR)
#define TT_ESTR                         ((knh_token_t)92)
#define knh_Token_isESTR(tk_)           (SP(tk_)->tt == TT_ESTR)
#define TT_LABEL                        ((knh_token_t)93)
#define knh_Token_isLABEL(tk_)          (SP(tk_)->tt == TT_LABEL)
#define TT_DOC                          ((knh_token_t)94)
#define knh_Token_isDOC(tk_)            (SP(tk_)->tt == TT_DOC)
#define TT_METAN                        ((knh_token_t)95)
#define knh_Token_isMETAN(tk_)          (SP(tk_)->tt == TT_METAN)
#define TT_PROPN                        ((knh_token_t)96)
#define knh_Token_isPROPN(tk_)          (SP(tk_)->tt == TT_PROPN)
#define TT_URN                          ((knh_token_t)97)
#define knh_Token_isURN(tk_)            (SP(tk_)->tt == TT_URN)
#define TT_MT                           ((knh_token_t)98)
#define knh_Token_isMT(tk_)             (SP(tk_)->tt == TT_MT)
#define TT_CONSTN                       ((knh_token_t)99)
#define knh_Token_isCONSTN(tk_)         (SP(tk_)->tt == TT_CONSTN)
#define TT_TYPEN                        ((knh_token_t)100)
#define knh_Token_isTYPEN(tk_)          (SP(tk_)->tt == TT_TYPEN)
#define TT_CMETHODN                     ((knh_token_t)101)
#define knh_Token_isCMETHODN(tk_)       (SP(tk_)->tt == TT_CMETHODN)
#define TT_CCONSTN                      ((knh_token_t)102)
#define knh_Token_isCCONSTN(tk_)        (SP(tk_)->tt == TT_CCONSTN)
#define TT_NAME                         ((knh_token_t)103)
#define knh_Token_isNAME(tk_)           (SP(tk_)->tt == TT_NAME)
#define TT_ERR                          ((knh_token_t)104)
#define knh_Token_isERR(tk_)            (SP(tk_)->tt == TT_ERR)
#define TT_MN                           ((knh_token_t)105)
#define knh_Token_isMN(tk_)             (SP(tk_)->tt == TT_MN)
#define TT_FN                           ((knh_token_t)106)
#define knh_Token_isFN(tk_)             (SP(tk_)->tt == TT_FN)
#define TT_CID                          ((knh_token_t)107)
#define knh_Token_isCID(tk_)            (SP(tk_)->tt == TT_CID)
#define TT_MPR                          ((knh_token_t)108)
#define knh_Token_isMPR(tk_)            (SP(tk_)->tt == TT_MPR)
#define TT_EOT                          ((knh_token_t)109)
#define knh_Token_isEOT(tk_)            (SP(tk_)->tt == TT_EOT)
#define TT_CONST                        ((knh_token_t)110)
#define knh_Token_isCONST(tk_)          (SP(tk_)->tt == TT_CONST)
#define TT_DEFVAL                       ((knh_token_t)111)
#define knh_Token_isDEFVAL(tk_)         (SP(tk_)->tt == TT_DEFVAL)
#define TT_SYSVAL                       ((knh_token_t)112)
#define knh_Token_isSYSVAL(tk_)         (SP(tk_)->tt == TT_SYSVAL)
#define TT_STACK                        ((knh_token_t)113)
#define knh_Token_isSTACK(tk_)          (SP(tk_)->tt == TT_STACK)
#define TT_FIELD                        ((knh_token_t)114)
#define knh_Token_isFIELD(tk_)          (SP(tk_)->tt == TT_FIELD)
#define TT_GLOBAL                       ((knh_token_t)115)
#define knh_Token_isGLOBAL(tk_)         (SP(tk_)->tt == TT_GLOBAL)
#define TT_MEMBER                       ((knh_token_t)116)
#define knh_Token_isMEMBER(tk_)         (SP(tk_)->tt == TT_MEMBER)
#define TT_CLASSID                      ((knh_token_t)117)
#define knh_Token_isCLASSID(tk_)        (SP(tk_)->tt == TT_CLASSID)
#define TT_ASIS                         ((knh_token_t)118)
#define knh_Token_isASIS(tk_)           (SP(tk_)->tt == TT_ASIS)
#define TT_NOP                          ((knh_token_t)119)
#define knh_Token_isNOP(tk_)            (SP(tk_)->tt == TT_NOP)
#define KNH_TOKEN_MAXSIZ                ((knh_token_t)120)

/* ------------------------------------------------------------------------ */
#ifndef METHODN_opItr
#define METHODN_opItr                   METHODN_NONAME
#endif
#ifndef METHODN_opALT
#define METHODN_opALT                   METHODN_NONAME
#endif
#ifndef METHODN_opNot
#define METHODN_opNot                   METHODN_NONAME
#endif
#ifndef METHODN_opInstanceof
#define METHODN_opInstanceof            METHODN_NONAME
#endif
#ifndef METHODN_opIsa
#define METHODN_opIsa                   METHODN_NONAME
#endif
#ifndef METHODN_opAs
#define METHODN_opAs                    METHODN_NONAME
#endif
#ifndef METHODN_opHas
#define METHODN_opHas                   METHODN_NONAME
#endif
#ifndef METHODN_opIs
#define METHODN_opIs                    METHODN_NONAME
#endif
#ifndef METHODN_opTo
#define METHODN_opTo                    METHODN_NONAME
#endif
#ifndef METHODN_opEq
#define METHODN_opEq                    METHODN_NONAME
#endif
#ifndef METHODN_opNeq
#define METHODN_opNeq                   METHODN_NONAME
#endif
#ifndef METHODN_opLt
#define METHODN_opLt                    METHODN_NONAME
#endif
#ifndef METHODN_opLte
#define METHODN_opLte                   METHODN_NONAME
#endif
#ifndef METHODN_opGt
#define METHODN_opGt                    METHODN_NONAME
#endif
#ifndef METHODN_opGte
#define METHODN_opGte                   METHODN_NONAME
#endif
#ifndef METHODN_opMatch
#define METHODN_opMatch                 METHODN_NONAME
#endif
#ifndef METHODN_opLshift
#define METHODN_opLshift                METHODN_NONAME
#endif
#ifndef METHODN_opRshift
#define METHODN_opRshift                METHODN_NONAME
#endif
#ifndef METHODN_opAdd
#define METHODN_opAdd                   METHODN_NONAME
#endif
#ifndef METHODN_opSub
#define METHODN_opSub                   METHODN_NONAME
#endif
#ifndef METHODN_opDiv
#define METHODN_opDiv                   METHODN_NONAME
#endif
#ifndef METHODN_opMod
#define METHODN_opMod                   METHODN_NONAME
#endif
#ifndef METHODN_opMul
#define METHODN_opMul                   METHODN_NONAME
#endif
#ifndef METHODN_opLand
#define METHODN_opLand                  METHODN_NONAME
#endif
#ifndef METHODN_opLor
#define METHODN_opLor                   METHODN_NONAME
#endif
#ifndef METHODN_opLnot
#define METHODN_opLnot                  METHODN_NONAME
#endif
#ifndef METHODN_opXor
#define METHODN_opXor                   METHODN_NONAME
#endif
#ifndef METHODN_opNext
#define METHODN_opNext                  METHODN_NONAME
#endif
#ifndef METHODN_opPrev
#define METHODN_opPrev                  METHODN_NONAME
#endif
#ifndef METHODN_opNeg
#define METHODN_opNeg                   METHODN_NONAME
#endif

/* ------------------------------------------------------------------------ */

/* ======================================================================== */
/* STT_MACRO knh_stmt_t */
#define STT_DONE                        ((knh_stmt_t)0)
#define STT_NAMESPACE                   ((knh_stmt_t)1)
#define STT_IMPORT                      ((knh_stmt_t)2)
#define STT_PRAGMA                      ((knh_stmt_t)3)
#define STT_USING                       ((knh_stmt_t)4)
#define STT_UIMPORT                     ((knh_stmt_t)5)
#define STT_UALIAS                      ((knh_stmt_t)6)
#define STT_UUNIT                       ((knh_stmt_t)7)
#define STT_UENUM                       ((knh_stmt_t)8)
#define STT_UVOCAB                      ((knh_stmt_t)9)
#define STT_WITH                        ((knh_stmt_t)10)
#define STT_UFUNC                       ((knh_stmt_t)11)
#define STT_UMAPMAP                     ((knh_stmt_t)12)
#define STT_CLASS                       ((knh_stmt_t)13)
#define STT_EXTENDS                     ((knh_stmt_t)14)
#define STT_IMPLEMENTS                  ((knh_stmt_t)15)
#define STT_METHOD                      ((knh_stmt_t)16)
#define STT_FUNCTION                    ((knh_stmt_t)17)
#define STT_FORMAT                      ((knh_stmt_t)18)
#define STT_DECL                        ((knh_stmt_t)19)
#define STT_RETURN                      ((knh_stmt_t)20)
#define STT_MAPMAP                      ((knh_stmt_t)21)
#define STT_WEAVE                       ((knh_stmt_t)22)
#define STT_ASPECT                      ((knh_stmt_t)23)
#define STT_BLOCK                       ((knh_stmt_t)24)
#define STT_IF                          ((knh_stmt_t)25)
#define STT_ELSE                        ((knh_stmt_t)26)
#define STT_SWITCH                      ((knh_stmt_t)27)
#define STT_CASE                        ((knh_stmt_t)28)
#define STT_WHILE                       ((knh_stmt_t)29)
#define STT_DO                          ((knh_stmt_t)30)
#define STT_FOR                         ((knh_stmt_t)31)
#define STT_FOREACH                     ((knh_stmt_t)32)
#define STT_FROM                        ((knh_stmt_t)33)
#define STT_WHERE                       ((knh_stmt_t)34)
#define STT_BREAK                       ((knh_stmt_t)35)
#define STT_CONTINUE                    ((knh_stmt_t)36)
#define STT_TRY                         ((knh_stmt_t)37)
#define STT_CATCH                       ((knh_stmt_t)38)
#define STT_FINALLY                     ((knh_stmt_t)39)
#define STT_THROW                       ((knh_stmt_t)40)
#define STT_ERR                         ((knh_stmt_t)41)
#define STT_LET                         ((knh_stmt_t)42)
#define STT_REGISTER                    ((knh_stmt_t)43)
#define STT_LETMULTI                    ((knh_stmt_t)44)
#define STT_NEW                         ((knh_stmt_t)45)
#define STT_MAPCAST                     ((knh_stmt_t)46)
#define STT_CALL                        ((knh_stmt_t)47)
#define STT_CALL1                       ((knh_stmt_t)48)
#define STT_PCALL                       ((knh_stmt_t)49)
#define STT_MT                          ((knh_stmt_t)50)
#define STT_OP                          ((knh_stmt_t)51)
#define STT_PROCEED                     ((knh_stmt_t)52)
#define STT_TRI                         ((knh_stmt_t)53)
#define STT_ALT                         ((knh_stmt_t)54)
#define STT_AND                         ((knh_stmt_t)55)
#define STT_OR                          ((knh_stmt_t)56)
#define STT_PRINT                       ((knh_stmt_t)57)
#define STT_ASSERT                      ((knh_stmt_t)58)
#define KNH_STMT_MAXSIZ                 ((knh_stmt_t)59)

/* ------------------------------------------------------------------------ */

/* ======================================================================== */
/* [done] */

/* ======================================================================== */
/* [namespace] */
#define StmtNAMESPACE_ns(stmt)          DP(stmt)->tokens[0]
#define NAMESPACE_ns                    0

/* ======================================================================== */
/* [import] */
#define StmtIMPORT_file(stmt)           DP(stmt)->tokens[0]
#define IMPORT_file                     0

/* ======================================================================== */
/* [pragma] */
#define StmtPRAGMA_name(stmt)           DP(stmt)->tokens[0]
#define PRAGMA_name                     0
#define StmtPRAGMA_value(stmt)          DP(stmt)->tokens[1]
#define PRAGMA_value                    1

/* ======================================================================== */
/* [using] */

/* ======================================================================== */
/* [using import] */
#define StmtUIMPORT_ns(stmt)            DP(stmt)->tokens[0]
#define UIMPORT_ns                      0

/* ======================================================================== */
/* [using alias] */
#define StmtUALIAS_class(stmt)          DP(stmt)->tokens[0]
#define UALIAS_class                    0
#define StmtUALIAS_urn(stmt)            DP(stmt)->tokens[1]
#define UALIAS_urn                      1

/* ======================================================================== */
/* [using unit] */
#define StmtUUNIT_class(stmt)           DP(stmt)->tokens[0]
#define UUNIT_class                     0
#define StmtUUNIT_urn(stmt)             DP(stmt)->tokens[1]
#define UUNIT_urn                       1

/* ======================================================================== */
/* [using enum] */
#define StmtUENUM_class(stmt)           DP(stmt)->tokens[0]
#define UENUM_class                     0
#define StmtUENUM_urn(stmt)             DP(stmt)->tokens[1]
#define UENUM_urn                       1

/* ======================================================================== */
/* [using vocab] */
#define StmtUVOCAB_class(stmt)          DP(stmt)->tokens[0]
#define UVOCAB_class                    0
#define StmtUVOCAB_urn(stmt)            DP(stmt)->tokens[1]
#define UVOCAB_urn                      1

/* ======================================================================== */
/* [with] */

/* ======================================================================== */
/* [using func] */
#define StmtUFUNC_func(stmt)            DP(stmt)->tokens[0]
#define UFUNC_func                      0

/* ======================================================================== */
/* [using mapmap] */
#define StmtUMAPMAP_target(stmt)        DP(stmt)->tokens[0]
#define UMAPMAP_target                  0
#define StmtUMAPMAP_source(stmt)        DP(stmt)->tokens[1]
#define UMAPMAP_source                  1
#define StmtUMAPMAP_urn(stmt)           DP(stmt)->tokens[2]
#define UMAPMAP_urn                     2

/* ======================================================================== */
/* [class] */
#define StmtCLASS_class(stmt)           DP(stmt)->tokens[0]
#define CLASS_class                     0
#define StmtCLASS_superclass(stmt)      DP(stmt)->tokens[1]
#define CLASS_superclass                1
#define StmtCLASS_interface(stmt)       DP(stmt)->stmts[2]
#define CLASS_interface                 2
#define StmtCLASS_instmt(stmt)          DP(stmt)->stmts[3]
#define CLASS_instmt                    3

/* ======================================================================== */
/* [extends] */

/* ======================================================================== */
/* [implements] */
#define StmtIMPLEMENTS_class_size(stmt) (DP(stmt)->size - 0)
#define StmtIMPLEMENTS_class(stmt,n)    DP(stmt)->tokens[n-0]

/* ======================================================================== */
/* [method] */
#define StmtMETHOD_rtype(stmt)          DP(stmt)->tokens[0]
#define METHOD_rtype                    0
#define StmtMETHOD_class(stmt)          DP(stmt)->tokens[1]
#define METHOD_class                    1
#define StmtMETHOD_method(stmt)         DP(stmt)->tokens[2]
#define METHOD_method                   2
#define StmtMETHOD_params(stmt)         DP(stmt)->stmts[3]
#define METHOD_params                   3
#define StmtMETHOD_instmt(stmt)         DP(stmt)->stmts[4]
#define METHOD_instmt                   4

/* ======================================================================== */
/* [function] */
#define StmtFUNCTION_name(stmt)         DP(stmt)->tokens[0]
#define FUNCTION_name                   0
#define StmtFUNCTION_params(stmt)       DP(stmt)->stmts[1]
#define FUNCTION_params                 1
#define StmtFUNCTION_instmt(stmt)       DP(stmt)->stmts[2]
#define FUNCTION_instmt                 2

/* ======================================================================== */
/* [format] */
#define StmtFORMAT_name(stmt)           DP(stmt)->tokens[0]
#define FORMAT_name                     0
#define StmtFORMAT_params(stmt)         DP(stmt)->tokens[1]
#define FORMAT_params                   1
#define StmtFORMAT_format(stmt)         DP(stmt)->tokens[2]
#define FORMAT_format                   2

/* ======================================================================== */
/* [decl] */
#define StmtDECL_type(stmt)             DP(stmt)->tokens[0]
#define DECL_type                       0
#define StmtDECL_name(stmt)             DP(stmt)->tokens[1]
#define DECL_name                       1
#define StmtDECL_value(stmt)            DP(stmt)->terms[2]
#define DECL_value                      2

/* ======================================================================== */
/* [return] */
#define StmtRETURN_values(stmt)         DP(stmt)->tokens[0]
#define RETURN_values                   0

/* ======================================================================== */
/* [mapmap] */
#define StmtMAPMAP_paths_size(stmt)     (DP(stmt)->size - 0)
#define StmtMAPMAP_paths(stmt,n)        DP(stmt)->tokens[n-0]

/* ======================================================================== */
/* [weave] */
#define StmtWEAVE_aspect(stmt)          DP(stmt)->tokens[0]
#define WEAVE_aspect                    0
#define StmtWEAVE_method(stmt)          DP(stmt)->tokens[1]
#define WEAVE_method                    1

/* ======================================================================== */
/* [aspect] */
#define StmtASPECT_type(stmt)           DP(stmt)->tokens[0]
#define ASPECT_type                     0
#define StmtASPECT_class(stmt)          DP(stmt)->tokens[1]
#define ASPECT_class                    1
#define StmtASPECT_method(stmt)         DP(stmt)->tokens[2]
#define ASPECT_method                   2
#define StmtASPECT_params(stmt)         DP(stmt)->stmts[3]
#define ASPECT_params                   3
#define StmtASPECT_instmt(stmt)         DP(stmt)->stmts[4]
#define ASPECT_instmt                   4

/* ======================================================================== */
/* [block] */
#define StmtBLOCK_block(stmt)           DP(stmt)->stmts[0]
#define BLOCK_block                     0

/* ======================================================================== */
/* [if] */
#define StmtIF_bool(stmt)               DP(stmt)->terms[0]
#define IF_bool                         0
#define StmtIF_truecase(stmt)           DP(stmt)->stmts[1]
#define IF_truecase                     1
#define StmtIF_falsecase(stmt)          DP(stmt)->stmts[2]
#define IF_falsecase                    2

/* ======================================================================== */
/* [else] */

/* ======================================================================== */
/* [switch] */
#define StmtSWITCH_bool(stmt)           DP(stmt)->terms[0]
#define SWITCH_bool                     0
#define StmtSWITCH_case(stmt)           DP(stmt)->stmts[1]
#define SWITCH_case                     1

/* ======================================================================== */
/* [case] */

/* ======================================================================== */
/* [while] */
#define StmtWHILE_bool(stmt)            DP(stmt)->terms[0]
#define WHILE_bool                      0
#define StmtWHILE_loop(stmt)            DP(stmt)->stmts[1]
#define WHILE_loop                      1

/* ======================================================================== */
/* [do] */
#define StmtDO_loop(stmt)               DP(stmt)->stmts[0]
#define DO_loop                         0
#define StmtDO_bool(stmt)               DP(stmt)->terms[1]
#define DO_bool                         1

/* ======================================================================== */
/* [for] */
#define StmtFOR_init(stmt)              DP(stmt)->terms[0]
#define FOR_init                        0
#define StmtFOR_bool(stmt)              DP(stmt)->terms[1]
#define FOR_bool                        1
#define StmtFOR_redo(stmt)              DP(stmt)->terms[2]
#define FOR_redo                        2
#define StmtFOR_loop(stmt)              DP(stmt)->stmts[3]
#define FOR_loop                        3

/* ======================================================================== */
/* [foreach] */
#define StmtFOREACH_type(stmt)          DP(stmt)->tokens[0]
#define FOREACH_type                    0
#define StmtFOREACH_name(stmt)          DP(stmt)->tokens[1]
#define FOREACH_name                    1
#define StmtFOREACH_iter(stmt)          DP(stmt)->terms[2]
#define FOREACH_iter                    2
#define StmtFOREACH_where(stmt)         DP(stmt)->terms[3]
#define FOREACH_where                   3
#define StmtFOREACH_loop(stmt)          DP(stmt)->stmts[4]
#define FOREACH_loop                    4

/* ======================================================================== */
/* [from] */

/* ======================================================================== */
/* [where] */

/* ======================================================================== */
/* [break] */
#define StmtBREAK_label(stmt)           DP(stmt)->terms[0]
#define BREAK_label                     0

/* ======================================================================== */
/* [continue] */
#define StmtCONTINUE_label(stmt)        DP(stmt)->terms[0]
#define CONTINUE_label                  0

/* ======================================================================== */
/* [try] */
#define StmtTRY_try(stmt)               DP(stmt)->stmts[0]
#define TRY_try                         0
#define StmtTRY_catch(stmt)             DP(stmt)->stmts[1]
#define TRY_catch                       1
#define StmtTRY_finally(stmt)           DP(stmt)->stmts[2]
#define TRY_finally                     2

/* ======================================================================== */
/* [catch] */
#define StmtCATCH_type(stmt)            DP(stmt)->tokens[0]
#define CATCH_type                      0
#define StmtCATCH_name(stmt)            DP(stmt)->tokens[1]
#define CATCH_name                      1
#define StmtCATCH_catch(stmt)           DP(stmt)->stmts[2]
#define CATCH_catch                     2

/* ======================================================================== */
/* [finally] */

/* ======================================================================== */
/* [throw] */
#define StmtTHROW_expt(stmt)            DP(stmt)->terms[0]
#define THROW_expt                      0

/* ======================================================================== */
/* [err] */
#define StmtERR_msg(stmt)               DP(stmt)->tokens[0]
#define ERR_msg                         0

/* ======================================================================== */
/* [let] */
#define StmtLET_lvalue(stmt)            DP(stmt)->tokens[0]
#define LET_lvalue                      0
#define StmtLET_rvalue(stmt)            DP(stmt)->terms[1]
#define LET_rvalue                      1

/* ======================================================================== */
/* [register] */
#define StmtREGISTER_exprs_size(stmt)   (DP(stmt)->size - 0)
#define StmtREGISTER_exprs(stmt,n)      DP(stmt)->terms[n-0]

/* ======================================================================== */
/* [letmulti] */
#define StmtLETMULTI_names_size(stmt)   (DP(stmt)->size - 0)
#define StmtLETMULTI_names(stmt,n)      DP(stmt)->tokens[n-0]

/* ======================================================================== */
/* [new] */
#define StmtNEW_new(stmt)               DP(stmt)->tokens[0]
#define NEW_new                         0
#define StmtNEW_class(stmt)             DP(stmt)->tokens[1]
#define NEW_class                       1
#define StmtNEW_args_size(stmt)         (DP(stmt)->size - 2)
#define StmtNEW_args(stmt,n)            DP(stmt)->terms[n-2]

/* ======================================================================== */
/* [mapcast] */
#define StmtMAPCAST_class(stmt)         DP(stmt)->tokens[0]
#define MAPCAST_class                   0
#define StmtMAPCAST_source(stmt)        DP(stmt)->terms[1]
#define MAPCAST_source                  1
#define StmtMAPCAST_option(stmt)        DP(stmt)->terms[2]
#define MAPCAST_option                  2

/* ======================================================================== */
/* [call] */
#define StmtCALL_method(stmt)           DP(stmt)->tokens[0]
#define CALL_method                     0
#define StmtCALL_base(stmt)             DP(stmt)->terms[1]
#define CALL_base                       1
#define StmtCALL_args_size(stmt)        (DP(stmt)->size - 2)
#define StmtCALL_args(stmt,n)           DP(stmt)->terms[n-2]

/* ======================================================================== */
/* [call1] */
#define StmtCALL1_value(stmt)           DP(stmt)->terms[0]
#define CALL1_value                     0

/* ======================================================================== */
/* [pcall] */
#define StmtPCALL_method(stmt)          DP(stmt)->tokens[0]
#define PCALL_method                    0
#define StmtPCALL_base(stmt)            DP(stmt)->terms[1]
#define PCALL_base                      1
#define StmtPCALL_args_size(stmt)       (DP(stmt)->size - 2)
#define StmtPCALL_args(stmt,n)          DP(stmt)->terms[n-2]

/* ======================================================================== */
/* [mt] */
#define StmtMT_mt(stmt)                 DP(stmt)->tokens[0]
#define MT_mt                           0
#define StmtMT_target(stmt)             DP(stmt)->terms[1]
#define MT_target                       1
#define StmtMT_option(stmt)             DP(stmt)->terms[2]
#define MT_option                       2

/* ======================================================================== */
/* [op] */
#define StmtOP_first(stmt)              DP(stmt)->terms[0]
#define OP_first                        0
#define StmtOP_second(stmt)             DP(stmt)->terms[1]
#define OP_second                       1
#define StmtOP_args_size(stmt)          (DP(stmt)->size - 2)
#define StmtOP_args(stmt,n)             DP(stmt)->terms[n-2]

/* ======================================================================== */
/* [proceed] */
#define StmtPROCEED_method(stmt)        DP(stmt)->tokens[0]
#define PROCEED_method                  0
#define StmtPROCEED_base(stmt)          DP(stmt)->terms[1]
#define PROCEED_base                    1

/* ======================================================================== */
/* [tri] */
#define StmtTRI_bool(stmt)              DP(stmt)->terms[0]
#define TRI_bool                        0
#define StmtTRI_tvalue(stmt)            DP(stmt)->terms[1]
#define TRI_tvalue                      1
#define StmtTRI_fvalue(stmt)            DP(stmt)->terms[2]
#define TRI_fvalue                      2

/* ======================================================================== */
/* [alt] */
#define StmtALT_bools_size(stmt)        (DP(stmt)->size - 0)
#define StmtALT_bools(stmt,n)           DP(stmt)->terms[n-0]

/* ======================================================================== */
/* [and] */
#define StmtAND_bools_size(stmt)        (DP(stmt)->size - 0)
#define StmtAND_bools(stmt,n)           DP(stmt)->terms[n-0]

/* ======================================================================== */
/* [or] */
#define StmtOR_bools_size(stmt)         (DP(stmt)->size - 0)
#define StmtOR_bools(stmt,n)            DP(stmt)->terms[n-0]

/* ======================================================================== */
/* [print] */
#define StmtPRINT_values_size(stmt)     (DP(stmt)->size - 0)
#define StmtPRINT_values(stmt,n)        DP(stmt)->terms[n-0]

/* ======================================================================== */
/* [assert] */
#define StmtASSERT_bool(stmt)           DP(stmt)->terms[0]
#define ASSERT_bool                     0

/* ======================================================================== */
char* knh_token_tochar(knh_token_t t);
knh_methodn_t knh_token_tomethodn(knh_token_t t);
int knh_token_getOpPriority(knh_token_t t);
int knh_token_getOpSize(knh_token_t t);
knh_bool_t knh_token_isBeginOfStmt(knh_token_t t);
Token *new_Token__parse(Ctx *ctx, knh_flag_t flag, InputStream *in, knh_bytes_t token);
int knh_bytes_istoken(knh_bytes_t t, int ch);
char* knh_stmt_tochar(knh_stmt_t t);
size_t knh_stmt_size(knh_stmt_t t);
int knh_stmt_isExpr(knh_stmt_t t);

#ifdef __cplusplus
}
#endif

/* ======================================================================== */

#endif/*KONOHAC_STMT__H*/
