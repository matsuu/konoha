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

#include<konoha/konoha_dev.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

/* ======================================================================== */
/* [token] */

knh_bool_t knh_token_isNested(knh_token_t tt)
{
    switch(tt) {
    case TT_BRACE: return 1;
    case TT_PARENTHESIS: return 1;
    case TT_BRANCET: return 1;
    }
    return 0;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_token_isKeyword(knh_token_t tt)
{
    switch(tt) {
    case TT_NAMESPACE: return 1;
    case TT_INCLUDE: return 1;
    case TT_USING: return 1;
    case TT_WEAVE: return 1;
    case TT_CLASS: return 1;
    case TT_EXTENDS: return 1;
    case TT_IMPLEMENTS: return 1;
    case TT_IF: return 1;
    case TT_ELSE: return 1;
    case TT_TRY: return 1;
    case TT_CATCH: return 1;
    case TT_FINALLY: return 1;
    case TT_DO: return 1;
    case TT_WHILE: return 1;
    case TT_FOR: return 1;
    case TT_FOREACH: return 1;
    case TT_FROM: return 1;
    case TT_WHERE: return 1;
    case TT_CONTINUE: return 1;
    case TT_BREAK: return 1;
    case TT_GOTO: return 1;
    case TT_THROW: return 1;
    case TT_RETURN: return 1;
    case TT_EVAL: return 1;
    case TT_ASSERT: return 1;
    case TT_PRINT: return 1;
    case TT_HELP: return 1;
    }
    return 0;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_token_isStatement(knh_token_t tt)
{
    switch(tt) {
    case TT_NAMESPACE: return 1;
    case TT_INCLUDE: return 1;
    case TT_USING: return 1;
    case TT_WEAVE: return 1;
    case TT_CLASS: return 1;
    case TT_IF: return 1;
    case TT_TRY: return 1;
    case TT_DO: return 1;
    case TT_WHILE: return 1;
    case TT_FOR: return 1;
    case TT_FOREACH: return 1;
    case TT_CONTINUE: return 1;
    case TT_BREAK: return 1;
    case TT_GOTO: return 1;
    case TT_THROW: return 1;
    case TT_RETURN: return 1;
    case TT_EVAL: return 1;
    case TT_ASSERT: return 1;
    case TT_PRINT: return 1;
    case TT_HELP: return 1;
    }
    return 0;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_token_isInExpr(knh_token_t tt)
{
    switch(tt) {
    case TT_BRACE: return 1;
    case TT_PARENTHESIS: return 1;
    case TT_BRANCET: return 1;
    case TT_DOTS: return 1;
    case TT_COMMA: return 1;
    case TT_QUESTION: return 1;
    case TT_SUBSET: return 1;
    case TT_SLICE: return 1;
    case TT_OFFSET: return 1;
    case TT_COLON: return 1;
    case TT_PSLICE: return 1;
    case TT_POFFSET: return 1;
    case TT_OR: return 1;
    case TT_AND: return 1;
    case TT_NOT: return 1;
    case TT_INSTANCEOF: return 1;
    case TT_IN: return 1;
    case TT_SEQ: return 1;
    case TT_ISMAPTO: return 1;
    case TT_EQ: return 1;
    case TT_NEQ: return 1;
    case TT_LT: return 1;
    case TT_LTE: return 1;
    case TT_GT: return 1;
    case TT_GTE: return 1;
    case TT_LSHIFT: return 1;
    case TT_RSHIFT: return 1;
    case TT_ADD: return 1;
    case TT_SUB: return 1;
    case TT_MOD: return 1;
    case TT_DIV: return 1;
    case TT_MUL: return 1;
    case TT_LOGICALOR: return 1;
    case TT_LOGICALAND: return 1;
    case TT_ALT: return 1;
    case TT_LOGICALNOT: return 1;
    case TT_LOGICALXOR: return 1;
    case TT_NEXT: return 1;
    case TT_PREV: return 1;
    case TT_SHARP: return 1;
    case TT_ASIS: return 1;
    case TT_NUM: return 1;
    case TT_STR: return 1;
    case TT_QSTR: return 1;
    case TT_FMTSTR: return 1;
    case TT_PROPN: return 1;
    case TT_URN: return 1;
    case TT_MOVTEXT: return 1;
    case TT_CONSTN: return 1;
    case TT_TYPEN: return 1;
    case TT_NAME: return 1;
    case TT_RAW: return 1;
    }
    return 0;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_token_isNotFirst(knh_token_t tt)
{
    switch(tt) {
    case TT_EXTENDS: return 1;
    case TT_IMPLEMENTS: return 1;
    case TT_ELSE: return 1;
    case TT_CATCH: return 1;
    case TT_FINALLY: return 1;
    case TT_FROM: return 1;
    case TT_WHERE: return 1;
    case TT_DOTS: return 1;
    case TT_COMMA: return 1;
    case TT_LET: return 1;
    case TT_LSHIFTE: return 1;
    case TT_RSHIFTE: return 1;
    case TT_ADDE: return 1;
    case TT_SUBE: return 1;
    case TT_MULE: return 1;
    case TT_DIVE: return 1;
    case TT_MODE: return 1;
    case TT_BITORE: return 1;
    case TT_BITANDE: return 1;
    case TT_ALTLET: return 1;
    case TT_SUBSET: return 1;
    case TT_SLICE: return 1;
    case TT_OFFSET: return 1;
    case TT_COLON: return 1;
    case TT_PSLICE: return 1;
    case TT_POFFSET: return 1;
    case TT_OR: return 1;
    case TT_INSTANCEOF: return 1;
    case TT_IN: return 1;
    case TT_SEQ: return 1;
    case TT_ISMAPTO: return 1;
    case TT_EQ: return 1;
    case TT_NEQ: return 1;
    case TT_LT: return 1;
    case TT_LTE: return 1;
    case TT_GT: return 1;
    case TT_GTE: return 1;
    case TT_LSHIFT: return 1;
    case TT_RSHIFT: return 1;
    case TT_ADD: return 1;
    case TT_SUB: return 1;
    case TT_MOD: return 1;
    case TT_DIV: return 1;
    case TT_MUL: return 1;
    case TT_ALT: return 1;
    case TT_ERR: return 1;
    }
    return 0;
}

/* ------------------------------------------------------------------------ */

char* knh_token_tochar(knh_token_t tt)
{
    switch(tt) {
    case TT_NAMESPACE: return "namespace";
    case TT_INCLUDE: return "include";
    case TT_USING: return "using";
    case TT_WEAVE: return "weave";
    case TT_CLASS: return "class";
    case TT_EXTENDS: return "extends";
    case TT_IMPLEMENTS: return "implements";
    case TT_IF: return "if";
    case TT_ELSE: return "else";
    case TT_TRY: return "try";
    case TT_CATCH: return "catch";
    case TT_FINALLY: return "finally";
    case TT_DO: return "do";
    case TT_WHILE: return "while";
    case TT_FOR: return "for";
    case TT_FOREACH: return "foreach";
    case TT_FROM: return "from";
    case TT_WHERE: return "where";
    case TT_CONTINUE: return "continue";
    case TT_BREAK: return "break";
    case TT_GOTO: return "goto";
    case TT_THROW: return "throw";
    case TT_RETURN: return "return";
    case TT_EVAL: return "eval";
    case TT_ASSERT: return "assert";
    case TT_PRINT: return "print";
    case TT_HELP: return "help";
    case TT_BRACE: return "{";
    case TT_PARENTHESIS: return "(";
    case TT_BRANCET: return "[";
    case TT_DOTS: return "...";
    case TT_SEMICOLON: return ";";
    case TT_COMMA: return ",";
    case TT_LET: return "=";
    case TT_LSHIFTE: return "<<=";
    case TT_RSHIFTE: return ">>=";
    case TT_ADDE: return "+=";
    case TT_SUBE: return "-=";
    case TT_MULE: return "*=";
    case TT_DIVE: return "/=";
    case TT_MODE: return "%=";
    case TT_BITORE: return "|=";
    case TT_BITANDE: return "&=";
    case TT_ALTLET: return "?\?=";
    case TT_QUESTION: return "?";
    case TT_SUBSET: return "..";
    case TT_SLICE: return "..<";
    case TT_OFFSET: return "..+";
    case TT_COLON: return ":";
    case TT_PSLICE: return ":<";
    case TT_POFFSET: return ":+";
    case TT_OR: return "||";
    case TT_AND: return "&&";
    case TT_NOT: return "not";
    case TT_INSTANCEOF: return "instanceof";
    case TT_IN: return "in";
    case TT_SEQ: return "===";
    case TT_ISMAPTO: return "-->";
    case TT_EQ: return "==";
    case TT_NEQ: return "!=";
    case TT_LT: return "<";
    case TT_LTE: return "<=";
    case TT_GT: return ">";
    case TT_GTE: return ">=";
    case TT_LSHIFT: return "<<";
    case TT_RSHIFT: return ">>";
    case TT_ADD: return "+";
    case TT_SUB: return "-";
    case TT_MOD: return "%";
    case TT_DIV: return "/";
    case TT_MUL: return "*";
    case TT_LOGICALOR: return "|";
    case TT_LOGICALAND: return "&";
    case TT_ALT: return "?\?";
    case TT_LOGICALNOT: return "~";
    case TT_LOGICALXOR: return "^";
    case TT_NEXT: return "++";
    case TT_PREV: return "--";
    case TT_SHARP: return "#";
    case TT_ASIS: return "_";
    case TT_NUM: return "TT_NUM";
    case TT_STR: return "TT_STR";
    case TT_QSTR: return "TT_QSTR";
    case TT_FMTSTR: return "TT_FMTSTR";
    case TT_LABEL: return "TT_LABEL";
    case TT_METAN: return "TT_METAN";
    case TT_PROPN: return "TT_PROPN";
    case TT_URN: return "TT_URN";
    case TT_MOVTEXT: return "TT_MOVTEXT";
    case TT_CONSTN: return "TT_CONSTN";
    case TT_TYPEN: return "TT_TYPEN";
    case TT_NAME: return "TT_NAME";
    case TT_RAW: return "TT_RAW";
    case TT_ERR: return "TT_ERR";
    }
    return "TT_UKNOWN";
}

/* ------------------------------------------------------------------------ */

knh_methodn_t knh_token_tomethodn(knh_token_t tt)
{
    switch(tt) {
    case TT_NOT: return METHODN_opNot;
    case TT_INSTANCEOF: return METHODN_opInstanceof;
    case TT_IN: return METHODN_opIn;
    case TT_SEQ: return METHODN_opSeq;
    case TT_ISMAPTO: return METHODN_opIsMapTo;
    case TT_EQ: return METHODN_opEq;
    case TT_NEQ: return METHODN_opNeq;
    case TT_LT: return METHODN_opLt;
    case TT_LTE: return METHODN_opLte;
    case TT_GT: return METHODN_opGt;
    case TT_GTE: return METHODN_opGte;
    case TT_LSHIFT: return METHODN_opLShift;
    case TT_RSHIFT: return METHODN_opRShift;
    case TT_ADD: return METHODN_opAdd;
    case TT_SUB: return METHODN_opSub;
    case TT_MOD: return METHODN_opMod;
    case TT_DIV: return METHODN_opDiv;
    case TT_MUL: return METHODN_opMul;
    case TT_LOGICALOR: return METHODN_opLogicalOr;
    case TT_LOGICALAND: return METHODN_opLogicalAnd;
    case TT_LOGICALNOT: return METHODN_opLogicalNot;
    case TT_LOGICALXOR: return METHODN_opLogicalXor;
    }
    return METHODN_NONAME;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_Token_isOP(Token *b)
{
    return (knh_token_tomethodn(b->tt) != METHODN_NONAME);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_methodn_isOperator(knh_methodn_t mn)
{
    switch(mn) {
    case METHODN_opNot: return 1;
    case METHODN_opInstanceof: return 1;
    case METHODN_opIn: return 1;
    case METHODN_opSeq: return 1;
    case METHODN_opIsMapTo: return 1;
    case METHODN_opEq: return 1;
    case METHODN_opNeq: return 1;
    case METHODN_opLt: return 1;
    case METHODN_opLte: return 1;
    case METHODN_opGt: return 1;
    case METHODN_opGte: return 1;
    case METHODN_opLShift: return 1;
    case METHODN_opRShift: return 1;
    case METHODN_opAdd: return 1;
    case METHODN_opSub: return 1;
    case METHODN_opMod: return 1;
    case METHODN_opDiv: return 1;
    case METHODN_opMul: return 1;
    case METHODN_opLogicalOr: return 1;
    case METHODN_opLogicalAnd: return 1;
    case METHODN_opLogicalNot: return 1;
    case METHODN_opLogicalXor: return 1;
    }
    return 0;
}

/* ------------------------------------------------------------------------ */

char *knh_methodop_tochar(knh_methodn_t mn)
{
    switch(mn) {
    case METHODN_opNot: return "not";
    case METHODN_opInstanceof: return "instanceof";
    case METHODN_opIn: return "in";
    case METHODN_opSeq: return "===";
    case METHODN_opIsMapTo: return "-->";
    case METHODN_opEq: return "==";
    case METHODN_opNeq: return "!=";
    case METHODN_opLt: return "<";
    case METHODN_opLte: return "<=";
    case METHODN_opGt: return ">";
    case METHODN_opGte: return ">=";
    case METHODN_opLShift: return "<<";
    case METHODN_opRShift: return ">>";
    case METHODN_opAdd: return "+";
    case METHODN_opSub: return "-";
    case METHODN_opMod: return "%";
    case METHODN_opDiv: return "/";
    case METHODN_opMul: return "*";
    case METHODN_opLogicalOr: return "|";
    case METHODN_opLogicalAnd: return "&";
    case METHODN_opLogicalNot: return "~";
    case METHODN_opLogicalXor: return "^";
    }
    DEBUG_ASSERT(mn == 0); /* this cann't happen */
    DEBUG_ASSERT(mn == 1); /* this cann't happen */
    return "";
}

/* ------------------------------------------------------------------------ */

PUBLIC
Token *new_Token__parse(Ctx *ctx, knh_flag_t flag, knh_filen_t fname, knh_line_t fln, knh_bytes_t t)
{
    if(t.len > 3 && t.buf[t.len-1] == ')' && t.buf[t.len-2] == '(') {
        flag |= KNH_FLAG_TKF_NEXTPARENTHESIS;
        t.len -=2;
    }
    if(t.len > 2 && t.buf[t.len-1] == ':' && t.buf[t.len-2] == ':') {
        flag |= KNH_FLAG_TKF_TAILC;
        t.len -=2;
    }
    if(t.len > 1 && t.buf[t.len-1] == '!' && t.buf[t.len-2] != '!') {
        flag |= KNH_FLAG_TKF_NOTNULLTYPE;
        t.len -=1;
    }
    if(t.len > 1 && t.buf[0] == '.' && islower(t.buf[1])) {
        flag |= KNH_FLAG_TKF_TOPDOT;
        t.buf++;
        t.len--;
        return new_Token(ctx, flag, fname, fln, t, TT_NAME);
    }
    switch(t.buf[0]) {
        case '!':
            if(ISB(t, "!")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("not"));
            } 
            if(ISB(t, "!=")) {
                return new_Token(ctx, flag, fname, fln, t, TT_NEQ);
            }
        break;
        case '#':
            if(ISB(t, "#")) {
                return new_Token(ctx, flag, fname, fln, t, TT_SHARP);
            }
        break;
        case '%':
            if(ISB(t, "%=")) {
                return new_Token(ctx, flag, fname, fln, t, TT_MODE);
            }
            if(ISB(t, "%")) {
                return new_Token(ctx, flag, fname, fln, t, TT_MOD);
            }
        break;
        case '&':
            if(ISB(t, "&=")) {
                return new_Token(ctx, flag, fname, fln, t, TT_BITANDE);
            }
            if(ISB(t, "&&")) {
                return new_Token(ctx, flag, fname, fln, t, TT_AND);
            }
            if(ISB(t, "&")) {
                return new_Token(ctx, flag, fname, fln, t, TT_LOGICALAND);
            }
        break;
        case '(':
            if(ISB(t, "(")) {
                return new_Token(ctx, flag, fname, fln, t, TT_PARENTHESIS);
            }
        break;
        case '*':
            if(ISB(t, "*=")) {
                return new_Token(ctx, flag, fname, fln, t, TT_MULE);
            }
            if(ISB(t, "*")) {
                return new_Token(ctx, flag, fname, fln, t, TT_MUL);
            }
        break;
        case '+':
            if(ISB(t, "+=")) {
                return new_Token(ctx, flag, fname, fln, t, TT_ADDE);
            }
            if(ISB(t, "+")) {
                return new_Token(ctx, flag, fname, fln, t, TT_ADD);
            }
            if(ISB(t, "++")) {
                return new_Token(ctx, flag, fname, fln, t, TT_NEXT);
            }
        break;
        case ',':
            if(ISB(t, ",")) {
                return new_Token(ctx, flag, fname, fln, t, TT_COMMA);
            }
        break;
        case '-':
            if(ISB(t, "-=")) {
                return new_Token(ctx, flag, fname, fln, t, TT_SUBE);
            }
            if(ISB(t, "-->")) {
                return new_Token(ctx, flag, fname, fln, t, TT_ISMAPTO);
            }
            if(ISB(t, "-")) {
                return new_Token(ctx, flag, fname, fln, t, TT_SUB);
            }
            if(ISB(t, "--")) {
                return new_Token(ctx, flag, fname, fln, t, TT_PREV);
            }
        break;
        case '.':
            if(ISB(t, "...")) {
                return new_Token(ctx, flag, fname, fln, t, TT_DOTS);
            }
            if(ISB(t, "..")) {
                return new_Token(ctx, flag, fname, fln, t, TT_SUBSET);
            }
            if(ISB(t, "..<")) {
                return new_Token(ctx, flag, fname, fln, t, TT_SLICE);
            }
            if(ISB(t, "..+")) {
                return new_Token(ctx, flag, fname, fln, t, TT_OFFSET);
            }
        break;
        case '/':
            if(ISB(t, "/=")) {
                return new_Token(ctx, flag, fname, fln, t, TT_DIVE);
            }
            if(ISB(t, "/")) {
                return new_Token(ctx, flag, fname, fln, t, TT_DIV);
            }
        break;
        case ':':
            if(ISB(t, ":=")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("=:"));
            } 
            if(ISB(t, ":")) {
                return new_Token(ctx, flag, fname, fln, t, TT_COLON);
            }
            if(ISB(t, ":<")) {
                return new_Token(ctx, flag, fname, fln, t, TT_PSLICE);
            }
            if(ISB(t, ":+")) {
                return new_Token(ctx, flag, fname, fln, t, TT_POFFSET);
            }
        break;
        case ';':
            if(ISB(t, ";")) {
                return new_Token(ctx, flag, fname, fln, t, TT_SEMICOLON);
            }
        break;
        case '<':
            if(ISB(t, "<<=")) {
                return new_Token(ctx, flag, fname, fln, t, TT_LSHIFTE);
            }
            if(ISB(t, "<")) {
                return new_Token(ctx, flag, fname, fln, t, TT_LT);
            }
            if(ISB(t, "<=")) {
                return new_Token(ctx, flag, fname, fln, t, TT_LTE);
            }
            if(ISB(t, "<<")) {
                return new_Token(ctx, flag, fname, fln, t, TT_LSHIFT);
            }
        break;
        case '=':
            if(ISB(t, "=")) {
                return new_Token(ctx, flag, fname, fln, t, TT_LET);
            }
            if(ISB(t, "===")) {
                return new_Token(ctx, flag, fname, fln, t, TT_SEQ);
            }
            if(ISB(t, "==")) {
                return new_Token(ctx, flag, fname, fln, t, TT_EQ);
            }
        break;
        case '>':
            if(ISB(t, ">>=")) {
                return new_Token(ctx, flag, fname, fln, t, TT_RSHIFTE);
            }
            if(ISB(t, ">")) {
                return new_Token(ctx, flag, fname, fln, t, TT_GT);
            }
            if(ISB(t, ">=")) {
                return new_Token(ctx, flag, fname, fln, t, TT_GTE);
            }
            if(ISB(t, ">>")) {
                return new_Token(ctx, flag, fname, fln, t, TT_RSHIFT);
            }
        break;
        case '?':
            if(ISB(t, "?\?\?")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("help"));
            } 
            if(ISB(t, "?\?=")) {
                return new_Token(ctx, flag, fname, fln, t, TT_ALTLET);
            }
            if(ISB(t, "?")) {
                return new_Token(ctx, flag, fname, fln, t, TT_QUESTION);
            }
            if(ISB(t, "?\?")) {
                return new_Token(ctx, flag, fname, fln, t, TT_ALT);
            }
        break;
        case '[':
            if(ISB(t, "[")) {
                return new_Token(ctx, flag, fname, fln, t, TT_BRANCET);
            }
        break;
        case '^':
            if(ISB(t, "^")) {
                return new_Token(ctx, flag, fname, fln, t, TT_LOGICALXOR);
            }
        break;
        case '_':
            if(ISB(t, "_")) {
                return new_Token(ctx, flag, fname, fln, t, TT_ASIS);
            }
        break;
        case 'a':
            if(ISB(t, "and")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("&&"));
            } 
            if(ISB(t, "assert")) {
                return new_Token(ctx, flag, fname, fln, t, TT_ASSERT);
            }
        break;
        case 'b':
            if(ISB(t, "boolean")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("Bool!"));
            } 
            if(ISB(t, "break")) {
                return new_Token(ctx, flag, fname, fln, t, TT_BREAK);
            }
        break;
        case 'c':
            if(ISB(t, "const")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("@Const"));
            } 
            if(ISB(t, "class")) {
                return new_Token(ctx, flag, fname, fln, t, TT_CLASS);
            }
            if(ISB(t, "catch")) {
                return new_Token(ctx, flag, fname, fln, t, TT_CATCH);
            }
            if(ISB(t, "continue")) {
                return new_Token(ctx, flag, fname, fln, t, TT_CONTINUE);
            }
        break;
        case 'd':
            if(ISB(t, "double")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("Float!"));
            } 
            if(ISB(t, "do")) {
                return new_Token(ctx, flag, fname, fln, t, TT_DO);
            }
        break;
        case 'e':
            if(ISB(t, "extends")) {
                return new_Token(ctx, flag, fname, fln, t, TT_EXTENDS);
            }
            if(ISB(t, "else")) {
                return new_Token(ctx, flag, fname, fln, t, TT_ELSE);
            }
            if(ISB(t, "eval")) {
                return new_Token(ctx, flag, fname, fln, t, TT_EVAL);
            }
        break;
        case 'f':
            if(ISB(t, "final")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("@Final"));
            } 
            if(ISB(t, "float")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("Float!"));
            } 
            if(ISB(t, "function")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("any"));
            } 
            if(ISB(t, "finally")) {
                return new_Token(ctx, flag, fname, fln, t, TT_FINALLY);
            }
            if(ISB(t, "for")) {
                return new_Token(ctx, flag, fname, fln, t, TT_FOR);
            }
            if(ISB(t, "foreach")) {
                return new_Token(ctx, flag, fname, fln, t, TT_FOREACH);
            }
            if(ISB(t, "from")) {
                return new_Token(ctx, flag, fname, fln, t, TT_FROM);
            }
        break;
        case 'g':
            if(ISB(t, "goto")) {
                return new_Token(ctx, flag, fname, fln, t, TT_GOTO);
            }
        break;
        case 'h':
            if(ISB(t, "help")) {
                return new_Token(ctx, flag, fname, fln, t, TT_HELP);
            }
        break;
        case 'i':
            if(ISB(t, "int")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("Int!"));
            } 
            if(ISB(t, "include")) {
                return new_Token(ctx, flag, fname, fln, t, TT_INCLUDE);
            }
            if(ISB(t, "implements")) {
                return new_Token(ctx, flag, fname, fln, t, TT_IMPLEMENTS);
            }
            if(ISB(t, "if")) {
                return new_Token(ctx, flag, fname, fln, t, TT_IF);
            }
            if(ISB(t, "instanceof")) {
                return new_Token(ctx, flag, fname, fln, t, TT_INSTANCEOF);
            }
            if(ISB(t, "in")) {
                return new_Token(ctx, flag, fname, fln, t, TT_IN);
            }
        break;
        case 'n':
            if(ISB(t, "namespace")) {
                return new_Token(ctx, flag, fname, fln, t, TT_NAMESPACE);
            }
            if(ISB(t, "not")) {
                return new_Token(ctx, flag, fname, fln, t, TT_NOT);
            }
        break;
        case 'p':
            if(ISB(t, "public")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("@Public"));
            } 
            if(ISB(t, "private")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("@Private"));
            } 
            if(ISB(t, "print")) {
                return new_Token(ctx, flag, fname, fln, t, TT_PRINT);
            }
        break;
        case 'r':
            if(ISB(t, "return")) {
                return new_Token(ctx, flag, fname, fln, t, TT_RETURN);
            }
        break;
        case 't':
            if(ISB(t, "try")) {
                return new_Token(ctx, flag, fname, fln, t, TT_TRY);
            }
            if(ISB(t, "throw")) {
                return new_Token(ctx, flag, fname, fln, t, TT_THROW);
            }
        break;
        case 'u':
            if(ISB(t, "using")) {
                return new_Token(ctx, flag, fname, fln, t, TT_USING);
            }
        break;
        case 'w':
            if(ISB(t, "weave")) {
                return new_Token(ctx, flag, fname, fln, t, TT_WEAVE);
            }
            if(ISB(t, "while")) {
                return new_Token(ctx, flag, fname, fln, t, TT_WHILE);
            }
            if(ISB(t, "where")) {
                return new_Token(ctx, flag, fname, fln, t, TT_WHERE);
            }
        break;
        case '{':
            if(ISB(t, "{")) {
                return new_Token(ctx, flag, fname, fln, t, TT_BRACE);
            }
        break;
        case '|':
            if(ISB(t, "|=")) {
                return new_Token(ctx, flag, fname, fln, t, TT_BITORE);
            }
            if(ISB(t, "||")) {
                return new_Token(ctx, flag, fname, fln, t, TT_OR);
            }
            if(ISB(t, "|")) {
                return new_Token(ctx, flag, fname, fln, t, TT_LOGICALOR);
            }
        break;
        case '~':
            if(ISB(t, "~")) {
                return new_Token(ctx, flag, fname, fln, t, TT_LOGICALNOT);
            }
        break;
        case 'l':
            if(ISB(t, "long")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("Int64!"));
            } 
        break;
        case 'm':
            if(ISB(t, "mod")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("%"));
            } 
        break;
        case 'o':
            if(ISB(t, "or")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("||"));
            } 
        break;
        case 's':
            if(ISB(t, "static")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("@Static"));
            } 
        break;
        case 'v':
            if(ISB(t, "virtual")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("@Virtual"));
            } 
        break;
    }
    if(knh_bytes_isNUM(t)) {
            return new_Token(ctx, flag, fname, fln, t, TT_NUM);
    }
    if(knh_bytes_isSTR(t)) {
            return new_Token(ctx, flag, fname, fln, t, TT_STR);
    }
    if(knh_bytes_isQSTR(t)) {
            return new_Token(ctx, flag, fname, fln, t, TT_QSTR);
    }
    if(knh_bytes_isFMTSTR(t)) {
            return new_Token(ctx, flag, fname, fln, t, TT_FMTSTR);
    }
    if(t.len > KONOHA_NAME_SIZE - 1) {
        return new_Token(ctx, flag, fname, fln, t, TT_ERR);
    }
    if(knh_bytes_isLABEL(t)) {
            return new_Token(ctx, flag, fname, fln, t, TT_LABEL);
    }
    if(knh_bytes_isMETAN(t)) {
            return new_Token(ctx, flag, fname, fln, t, TT_METAN);
    }
    if(knh_bytes_isPROPN(t)) {
            return new_Token(ctx, flag, fname, fln, t, TT_PROPN);
    }
    if(knh_bytes_isURN(t)) {
            return new_Token(ctx, flag, fname, fln, t, TT_URN);
    }
    if(knh_bytes_isMOVTEXT(t)) {
            return new_Token(ctx, flag, fname, fln, t, TT_MOVTEXT);
    }
    if(knh_bytes_isCONSTN(t)) {
            return new_Token(ctx, flag, fname, fln, t, TT_CONSTN);
    }
    if(knh_bytes_isTYPEN(t)) {
            return new_Token(ctx, flag, fname, fln, t, TT_TYPEN);
    }
    if(knh_bytes_isNAME(t)) {
            return new_Token(ctx, flag, fname, fln, t, TT_NAME);
    }
    DEBUG("unknown: %s", t.buf);
    return new_Token(ctx, flag, fname, fln, t, TT_ERR);
}

/* ======================================================================== */
/* [grammar] */

Stmt *new_Stmt__namespace(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_NAMESPACE);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_NAMESPACE);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* NAME */
    if(*cp < e && knh_Token_isNAME(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, ts[*cp]);
        *cp += 1;
        goto L_2;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_2:;
    /* ; */
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    else {
        //MC_EPRINT(ctx, ts[*cp-1], MC_NOTICE, "; required");
        return b;
    }
    return b;
    L_ERR:;
    knh_int_t ee = knh_tokens_epos(s, *cp, e);
    MC_EPRINT(ctx, ts[ee], MC_ERROR, "namespace statement: %s", knh_Token_tochar(ts[ee]));
    knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
    *cp = knh_tokens_nextstmt(ts, *cp, e);
    return b; 
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__include(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_INCLUDE);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_INCLUDE);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* ANY */
    if(*cp < e && knh_Token_isANY(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, ts[*cp]);
        *cp += 1;
        goto L_2;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_2:;
    /* ; */
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    else {
        //MC_EPRINT(ctx, ts[*cp-1], MC_NOTICE, "; required");
        return b;
    }
    return b;
    L_ERR:;
    knh_int_t ee = knh_tokens_epos(s, *cp, e);
    MC_EPRINT(ctx, ts[ee], MC_ERROR, "include statement: %s", knh_Token_tochar(ts[ee]));
    knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
    *cp = knh_tokens_nextstmt(ts, *cp, e);
    return b; 
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__weave(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_WEAVE);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_WEAVE);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* ANY */
    if(*cp < e && knh_Token_isANY(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, ts[*cp]);
        *cp += 1;
        goto L_2;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_2:;
    /* ANY */
    if(*cp < e && knh_Token_isANY(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, ts[*cp]);
        *cp += 1;
        goto L_3;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_3:;
    /* ; */
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    else {
        //MC_EPRINT(ctx, ts[*cp-1], MC_NOTICE, "; required");
        return b;
    }
    return b;
    L_ERR:;
    knh_int_t ee = knh_tokens_epos(s, *cp, e);
    MC_EPRINT(ctx, ts[ee], MC_ERROR, "weave statement: %s", knh_Token_tochar(ts[ee]));
    knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
    *cp = knh_tokens_nextstmt(ts, *cp, e);
    return b; 
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__class(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_CLASS);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_CLASS);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* CLASSN */
    if(*cp < e && knh_Token_isCLASSN(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, ts[*cp]);
        *cp += 1;
        goto L_2;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_2:;
    /* ?extends */
    if(*cp < e && ts[*cp]->tt == TT_EXTENDS) {
        *cp += 1;
        goto L_3;
    }
    else {
        knh_Stmt_terms_add(ctx, b, new_Token__text(ctx, ts[*cp-1], STEXT("Object")));
        goto L_4;
    }

	L_3:;
    /* CLASSN */
    if(*cp < e && knh_Token_isCLASSN(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, ts[*cp]);
        *cp += 1;
        goto L_4;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_4:;
    /* ?implements */
    if(*cp < e && ts[*cp]->tt == TT_IMPLEMENTS) {
        *cp += 1;
        if(*cp < e && knh_Token_isCLASSN(ts[*cp])) {
        }
        else {
            KNH_GOTO(L_ERR);
        }
        Stmt *stmt = new_Stmt(ctx, 0, STT_IMPLEMENTS);
        knh_Stmt_terms_add(ctx, b, stmt);
        L_COMMA:;
        if(*cp < e && knh_Token_isCLASSN(ts[*cp])) {
            knh_Stmt_terms_add(ctx, stmt, ts[*cp]);
            *cp += 1;
        }
        if(*cp < e && ts[*cp]->tt == TT_COMMA) {
            *cp += 1;
            goto L_COMMA;
        }
        goto L_5;
    }
    else {
        knh_Stmt_terms_add(ctx, b, new_Stmt(ctx, 0, STT_DONE));
        goto L_5;
    }

	L_5:;
    /* { */
    if(*cp < e && ts[*cp]->tt == TT_BRACE) {
        knh_Stmt_terms_add(ctx, b, new_Stmt__block(ctx, knh_Token_ts(ts[*cp]), 0, knh_Token_tokens_size(ts[*cp])));
        knh_Token_tokens_empty(ctx, ts[*cp]);
        *cp += 1;
        goto L_6;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_6:;
    return b;
    L_ERR:;
    knh_int_t ee = knh_tokens_epos(s, *cp, e);
    MC_EPRINT(ctx, ts[ee], MC_ERROR, "class statement: %s", knh_Token_tochar(ts[ee]));
    knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
    *cp = knh_tokens_nextstmt(ts, *cp, e);
    return b; 
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__if(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_IF);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_IF);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* (expr) */
    if(*cp < e && ts[*cp]->tt == TT_PARENTHESIS) {
        knh_Stmt_terms_add(ctx, b, new_Term__pexpr(ctx, ts[*cp]));
        *cp += 1;
        goto L_2;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_2:;
    /* {stmt} */
    if(*cp < e) {
        if(ts[*cp]->tt == TT_BRACE) {
            knh_Stmt_terms_add(ctx, b, new_Stmt__block(ctx, knh_Token_ts(ts[*cp]), 0, knh_Token_tokens_size(ts[*cp])));
            knh_Token_tokens_empty(ctx, ts[*cp]);
            *cp += 1;
            goto L_3;
        }
        if(ts[*cp]->tt == TT_SEMICOLON) {
            knh_Stmt_terms_add(ctx, b, new_Stmt(ctx, 0, STT_DONE));
            *cp += 1;
            goto L_3;
        }
        knh_Stmt_terms_add(ctx, b, new_Stmt__stmt1(ctx, ts, *cp, e, cp));
        goto L_3;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_3:;
    /* ?else */
    if(*cp < e && ts[*cp]->tt == TT_ELSE) {
        *cp += 1;
    }else {
        knh_Stmt_terms_add(ctx, b, new_Stmt(ctx, 0, STT_DONE));
        return b;
    }
    /* {stmt} */
    if(*cp < e) {
        if(ts[*cp]->tt == TT_BRACE) {
            knh_Stmt_terms_add(ctx, b, new_Stmt__block(ctx, knh_Token_ts(ts[*cp]), 0, knh_Token_tokens_size(ts[*cp])));
            knh_Token_tokens_empty(ctx, ts[*cp]);
            *cp += 1;
            goto L_5;
        }
        if(ts[*cp]->tt == TT_SEMICOLON) {
            knh_Stmt_terms_add(ctx, b, new_Stmt(ctx, 0, STT_DONE));
            *cp += 1;
            goto L_5;
        }
        knh_Stmt_terms_add(ctx, b, new_Stmt__stmt1(ctx, ts, *cp, e, cp));
        goto L_5;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_5:;
    return b;
    L_ERR:;
    knh_int_t ee = knh_tokens_epos(s, *cp, e);
    MC_EPRINT(ctx, ts[ee], MC_ERROR, "if statement: %s", knh_Token_tochar(ts[ee]));
    knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
    *cp = knh_tokens_nextstmt(ts, *cp, e);
    return b; 
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__do(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_DO);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_DO);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* { */
    if(*cp < e && ts[*cp]->tt == TT_BRACE) {
        knh_Stmt_terms_add(ctx, b, new_Stmt__block(ctx, knh_Token_ts(ts[*cp]), 0, knh_Token_tokens_size(ts[*cp])));
        knh_Token_tokens_empty(ctx, ts[*cp]);
        *cp += 1;
        goto L_2;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_2:;
    /* TT_WHILE */
    if(*cp < e && ts[*cp]->tt == TT_WHILE) {
        knh_Stmt_terms_add(ctx, b, ts[*cp]);
        *cp += 1;
        goto L_3;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_3:;
    /* (expr) */
    if(*cp < e && ts[*cp]->tt == TT_PARENTHESIS) {
        knh_Stmt_terms_add(ctx, b, new_Term__pexpr(ctx, ts[*cp]));
        *cp += 1;
        goto L_4;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_4:;
    /* ; */
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    else {
        //MC_EPRINT(ctx, ts[*cp-1], MC_NOTICE, "; required");
        return b;
    }
    return b;
    L_ERR:;
    knh_int_t ee = knh_tokens_epos(s, *cp, e);
    MC_EPRINT(ctx, ts[ee], MC_ERROR, "do statement: %s", knh_Token_tochar(ts[ee]));
    knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
    *cp = knh_tokens_nextstmt(ts, *cp, e);
    return b; 
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__while(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_WHILE);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_WHILE);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* (expr) */
    if(*cp < e && ts[*cp]->tt == TT_PARENTHESIS) {
        knh_Stmt_terms_add(ctx, b, new_Term__pexpr(ctx, ts[*cp]));
        *cp += 1;
        goto L_2;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_2:;
    /* {stmt} */
    if(*cp < e) {
        if(ts[*cp]->tt == TT_BRACE) {
            knh_Stmt_terms_add(ctx, b, new_Stmt__block(ctx, knh_Token_ts(ts[*cp]), 0, knh_Token_tokens_size(ts[*cp])));
            knh_Token_tokens_empty(ctx, ts[*cp]);
            *cp += 1;
            goto L_3;
        }
        if(ts[*cp]->tt == TT_SEMICOLON) {
            knh_Stmt_terms_add(ctx, b, new_Stmt(ctx, 0, STT_DONE));
            *cp += 1;
            goto L_3;
        }
        knh_Stmt_terms_add(ctx, b, new_Stmt__stmt1(ctx, ts, *cp, e, cp));
        goto L_3;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_3:;
    return b;
    L_ERR:;
    knh_int_t ee = knh_tokens_epos(s, *cp, e);
    MC_EPRINT(ctx, ts[ee], MC_ERROR, "while statement: %s", knh_Token_tochar(ts[ee]));
    knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
    *cp = knh_tokens_nextstmt(ts, *cp, e);
    return b; 
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__for(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_FOR);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_FOR);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* (stmt3) */
    if(*cp < e && ts[*cp]->tt == TT_PARENTHESIS) {
        knh_Stmt_add_stmt3(ctx, b, ts[*cp]);
        knh_Token_tokens_empty(ctx, ts[*cp]);
        *cp += 1;
        goto L_2;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_2:;
    /* {stmt} */
    if(*cp < e) {
        if(ts[*cp]->tt == TT_BRACE) {
            knh_Stmt_terms_add(ctx, b, new_Stmt__block(ctx, knh_Token_ts(ts[*cp]), 0, knh_Token_tokens_size(ts[*cp])));
            knh_Token_tokens_empty(ctx, ts[*cp]);
            *cp += 1;
            goto L_3;
        }
        if(ts[*cp]->tt == TT_SEMICOLON) {
            knh_Stmt_terms_add(ctx, b, new_Stmt(ctx, 0, STT_DONE));
            *cp += 1;
            goto L_3;
        }
        knh_Stmt_terms_add(ctx, b, new_Stmt__stmt1(ctx, ts, *cp, e, cp));
        goto L_3;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_3:;
    return b;
    L_ERR:;
    knh_int_t ee = knh_tokens_epos(s, *cp, e);
    MC_EPRINT(ctx, ts[ee], MC_ERROR, "for statement: %s", knh_Token_tochar(ts[ee]));
    knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
    *cp = knh_tokens_nextstmt(ts, *cp, e);
    return b; 
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__foreach(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_FOREACH);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_FOREACH);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* (fromwhere) */
    if(*cp < e && ts[*cp]->tt == TT_PARENTHESIS) {
        knh_Stmt_add_fromwhere(ctx, b, ts[*cp]);
        knh_Token_tokens_empty(ctx, ts[*cp]);
        *cp += 1;
        goto L_2;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_2:;
    /* {stmt} */
    if(*cp < e) {
        if(ts[*cp]->tt == TT_BRACE) {
            knh_Stmt_terms_add(ctx, b, new_Stmt__block(ctx, knh_Token_ts(ts[*cp]), 0, knh_Token_tokens_size(ts[*cp])));
            knh_Token_tokens_empty(ctx, ts[*cp]);
            *cp += 1;
            goto L_3;
        }
        if(ts[*cp]->tt == TT_SEMICOLON) {
            knh_Stmt_terms_add(ctx, b, new_Stmt(ctx, 0, STT_DONE));
            *cp += 1;
            goto L_3;
        }
        knh_Stmt_terms_add(ctx, b, new_Stmt__stmt1(ctx, ts, *cp, e, cp));
        goto L_3;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_3:;
    return b;
    L_ERR:;
    knh_int_t ee = knh_tokens_epos(s, *cp, e);
    MC_EPRINT(ctx, ts[ee], MC_ERROR, "foreach statement: %s", knh_Token_tochar(ts[ee]));
    knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
    *cp = knh_tokens_nextstmt(ts, *cp, e);
    return b; 
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__continue(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_CONTINUE);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_CONTINUE);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* ?ANY */
    if(*cp < e && knh_Token_isANY(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, ts[*cp]);
        *cp += 1;
        goto L_2;
    }else {
        goto L_2;
    }

	L_2:;
    /* ; */
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    else {
        //MC_EPRINT(ctx, ts[*cp-1], MC_NOTICE, "; required");
        return b;
    }
    return b;
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__break(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_BREAK);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_BREAK);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* ?ANY */
    if(*cp < e && knh_Token_isANY(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, ts[*cp]);
        *cp += 1;
        goto L_2;
    }else {
        goto L_2;
    }

	L_2:;
    /* ; */
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    else {
        //MC_EPRINT(ctx, ts[*cp-1], MC_NOTICE, "; required");
        return b;
    }
    return b;
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__goto(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_GOTO);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_GOTO);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* ANY */
    if(*cp < e && knh_Token_isANY(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, ts[*cp]);
        *cp += 1;
        goto L_2;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_2:;
    /* ; */
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    else {
        //MC_EPRINT(ctx, ts[*cp-1], MC_NOTICE, "; required");
        return b;
    }
    return b;
    L_ERR:;
    knh_int_t ee = knh_tokens_epos(s, *cp, e);
    MC_EPRINT(ctx, ts[ee], MC_ERROR, "goto statement: %s", knh_Token_tochar(ts[ee]));
    knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
    *cp = knh_tokens_nextstmt(ts, *cp, e);
    return b; 
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__throw(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_THROW);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_THROW);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* expr */
    if(*cp < e && knh_Token_isFirstExpr(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, new_Term__expr(ctx, ts, *cp, knh_tokens_lastexpr(ts, *cp, e), KNH_STT_RVALUE));
        *cp = knh_tokens_nextstmt(ts, *cp, e);
        goto L_2;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_2:;
    /* ; */
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    else {
        //MC_EPRINT(ctx, ts[*cp-1], MC_NOTICE, "; required");
        return b;
    }
    return b;
    L_ERR:;
    knh_int_t ee = knh_tokens_epos(s, *cp, e);
    MC_EPRINT(ctx, ts[ee], MC_ERROR, "throw statement: %s", knh_Token_tochar(ts[ee]));
    knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
    *cp = knh_tokens_nextstmt(ts, *cp, e);
    return b; 
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__return(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_RETURN);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_RETURN);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* ;expr */
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    if(*cp < e && knh_Token_isFirstExpr(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, new_Term__expr(ctx, ts, *cp, knh_tokens_lastexpr(ts, *cp, e), KNH_STT_RVALUE));
        *cp = knh_tokens_nextstmt(ts, *cp, e);
        goto L_2;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_2:;
    /* ; */
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    else {
        //MC_EPRINT(ctx, ts[*cp-1], MC_NOTICE, "; required");
        return b;
    }
    return b;
    L_ERR:;
    knh_int_t ee = knh_tokens_epos(s, *cp, e);
    MC_EPRINT(ctx, ts[ee], MC_ERROR, "return statement: %s", knh_Token_tochar(ts[ee]));
    knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
    *cp = knh_tokens_nextstmt(ts, *cp, e);
    return b; 
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__eval(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_EVAL);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_EVAL);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* expr */
    if(*cp < e && knh_Token_isFirstExpr(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, new_Term__expr(ctx, ts, *cp, knh_tokens_lastexpr(ts, *cp, e), KNH_STT_RVALUE));
        *cp = knh_tokens_nextstmt(ts, *cp, e);
        goto L_2;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_2:;
    /* ; */
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    else {
        //MC_EPRINT(ctx, ts[*cp-1], MC_NOTICE, "; required");
        return b;
    }
    return b;
    L_ERR:;
    knh_int_t ee = knh_tokens_epos(s, *cp, e);
    MC_EPRINT(ctx, ts[ee], MC_ERROR, "eval statement: %s", knh_Token_tochar(ts[ee]));
    knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
    *cp = knh_tokens_nextstmt(ts, *cp, e);
    return b; 
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__assert(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_ASSERT);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_ASSERT);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* (expr) */
    if(*cp < e && ts[*cp]->tt == TT_PARENTHESIS) {
        knh_Stmt_terms_add(ctx, b, new_Term__pexpr(ctx, ts[*cp]));
        *cp += 1;
        goto L_2;
    }
    else {
        KNH_GOTO(L_ERR);
    }

	L_2:;
    /* ; */
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    else {
        //MC_EPRINT(ctx, ts[*cp-1], MC_NOTICE, "; required");
        return b;
    }
    return b;
    L_ERR:;
    knh_int_t ee = knh_tokens_epos(s, *cp, e);
    MC_EPRINT(ctx, ts[ee], MC_ERROR, "assert statement: %s", knh_Token_tochar(ts[ee]));
    knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
    *cp = knh_tokens_nextstmt(ts, *cp, e);
    return b; 
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__print(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_PRINT);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_PRINT);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* expr... */
    knh_Stmt_setPrintLine(b, 1);
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    while(*cp < e) {
        if(ts[*cp]->tt == TT_DOTS) {
            knh_Stmt_setPrintLine(b, 0);
            *cp += 1;
            break;
        }
        if(ts[*cp]->tt == TT_SEMICOLON) {
            break;
        }
        if(!knh_Token_isFirstExpr(ts[*cp])) {
            KNH_GOTO(L_ERR);
        }
        knh_int_t pe = knh_tokens_lastexpr(ts, *cp, e);
        knh_Stmt_add_printname(ctx, b, ts, *cp, pe);
        knh_Stmt_terms_add(ctx, b, new_Term__expr(ctx, ts, *cp, pe, KNH_STT_RVALUE));
        *cp = pe; 
        if(*cp < e && ts[*cp]->tt == TT_COMMA) {
            *cp += 1;
            continue;
        }
    }
    /* ; */
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    else {
        //MC_EPRINT(ctx, ts[*cp-1], MC_NOTICE, "; required");
        return b;
    }
    return b;
    L_ERR:;
    knh_int_t ee = knh_tokens_epos(s, *cp, e);
    MC_EPRINT(ctx, ts[ee], MC_ERROR, "print statement: %s", knh_Token_tochar(ts[ee]));
    knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
    *cp = knh_tokens_nextstmt(ts, *cp, e);
    return b; 
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__help(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == TT_HELP);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_HELP);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* ?ANY */
    if(*cp < e && knh_Token_isANY(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, ts[*cp]);
        *cp += 1;
        goto L_2;
    }else {
        goto L_2;
    }

	L_2:;
    /* ; */
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    else {
        //MC_EPRINT(ctx, ts[*cp-1], MC_NOTICE, "; required");
        return b;
    }
    return b;
}

/* ------------------------------------------------------------------------ */

Stmt *new_Stmt__stmt1(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(s == *cp);
    L_HEAD:;
    if(!(*cp < e)) {
    	DEBUG("s = %d, *cp = %d, e = %d", (int)s, (int)*cp, (int)e);
    	return new_Stmt(ctx, 0, STT_DONE);
    }
    switch(ts[*cp]->tt) {
    case TT_METAN: 
        if(knh_Token_isNextParenthesis(ts[*cp])) {
            *cp += 1;
        };
    case TT_LABEL: 
        *cp += 1;
        goto L_HEAD;
    case TT_USING:
        return new_Stmt__using(ctx, ts, *cp, e, cp);

    case TT_NAMESPACE: 
        return new_Stmt__namespace(ctx, ts, *cp, e, cp); 
    case TT_INCLUDE: 
        return new_Stmt__include(ctx, ts, *cp, e, cp); 
    case TT_WEAVE: 
        return new_Stmt__weave(ctx, ts, *cp, e, cp); 
    case TT_CLASS: 
        return new_Stmt__class(ctx, ts, *cp, e, cp); 
    case TT_IF: 
        return new_Stmt__if(ctx, ts, *cp, e, cp); 
    case TT_DO: 
        return new_Stmt__do(ctx, ts, *cp, e, cp); 
    case TT_WHILE: 
        return new_Stmt__while(ctx, ts, *cp, e, cp); 
    case TT_FOR: 
        return new_Stmt__for(ctx, ts, *cp, e, cp); 
    case TT_FOREACH: 
        return new_Stmt__foreach(ctx, ts, *cp, e, cp); 
    case TT_CONTINUE: 
        return new_Stmt__continue(ctx, ts, *cp, e, cp); 
    case TT_BREAK: 
        return new_Stmt__break(ctx, ts, *cp, e, cp); 
    case TT_GOTO: 
        return new_Stmt__goto(ctx, ts, *cp, e, cp); 
    case TT_THROW: 
        return new_Stmt__throw(ctx, ts, *cp, e, cp); 
    case TT_RETURN: 
        return new_Stmt__return(ctx, ts, *cp, e, cp); 
    case TT_EVAL: 
        return new_Stmt__eval(ctx, ts, *cp, e, cp); 
    case TT_ASSERT: 
        return new_Stmt__assert(ctx, ts, *cp, e, cp); 
    case TT_PRINT: 
        return new_Stmt__print(ctx, ts, *cp, e, cp); 
    case TT_HELP: 
        return new_Stmt__help(ctx, ts, *cp, e, cp); 
    case TT_EXTENDS:
    case TT_IMPLEMENTS:
    case TT_ELSE:
    case TT_CATCH:
    case TT_FINALLY:
    case TT_FROM:
    case TT_WHERE:
    case TT_DOTS:
    case TT_COMMA:
    case TT_LET:
    case TT_LSHIFTE:
    case TT_RSHIFTE:
    case TT_ADDE:
    case TT_SUBE:
    case TT_MULE:
    case TT_DIVE:
    case TT_MODE:
    case TT_BITORE:
    case TT_BITANDE:
    case TT_ALTLET:
    case TT_SUBSET:
    case TT_SLICE:
    case TT_OFFSET:
    case TT_COLON:
    case TT_PSLICE:
    case TT_POFFSET:
    case TT_OR:
    case TT_INSTANCEOF:
    case TT_IN:
    case TT_SEQ:
    case TT_ISMAPTO:
    case TT_EQ:
    case TT_NEQ:
    case TT_LT:
    case TT_LTE:
    case TT_GT:
    case TT_GTE:
    case TT_LSHIFT:
    case TT_RSHIFT:
    case TT_ADD:
    case TT_SUB:
    case TT_MOD:
    case TT_DIV:
    case TT_MUL:
    case TT_ALT:
    case TT_ERR:
        MC_EPRINT(ctx, ts[knh_tokens_epos(s, *cp, e)], MC_ERROR, "syntax error: %s", knh_Token_tochar(ts[knh_tokens_epos(s, *cp, e)]));
        return new_Stmt__SyntaxError(ctx, ts, *cp, e, cp);
    default:
        if(*cp + 1 < e && ts[*cp]->tt == TT_TYPEN && ts[*cp+1]->tt == TT_NAME && knh_Token_isNextParenthesis(ts[*cp+1])) {
            return new_Stmt__method(ctx, ts, *cp, e, cp);
        }
        else if(*cp + 1 < e && ts[*cp]->tt == TT_NAME && knh_Token_isNextParenthesis(ts[*cp]) && knh_Token_isNextBrace(ts[*cp+1])) {
            return new_Stmt__defun(ctx, ts, *cp, e, cp);
        }
        else if(*cp + 1 < e && ts[*cp]->tt == TT_TYPEN && knh_Token_isNextParenthesis(ts[*cp]) && knh_Token_isNextBrace(ts[*cp+1])) {
            return new_Stmt__lambda(ctx, ts, *cp, e, cp);
        }
        else{
            return new_Stmt__expr(ctx, ts, *cp, e, cp);
        }
    }
}

Stmt *
new_Stmt__block(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e)
{
	knh_int_t c = s;
	int prev;
	Stmt *b = NULL;
	while(c < e) {
		//DEBUG("S s = %d, c = %d, e = %d", (int)s, (int)c, (int)e);
		if(ts[c]->tt == TT_SEMICOLON) {
			c++;
			continue;
		}
		prev = c;
		if(b == NULL) {
			b = new_Stmt__stmt1(ctx, ts, c, e, &c);
		}else{
			knh_Stmt_tail_append(ctx, b, new_Stmt__stmt1(ctx, ts, c, e, &c));
		}
		if(prev == c) { /* infinate loop */
			DEBUG("Infinate loop? s = %d, prev = %d, c = %d, e = %d", (int)s, prev, (int)c, (int)e);
			goto L_EXIT;
		}
	}
	L_EXIT:;
	if(b == NULL) {
		b = new_Stmt(ctx, 0, STT_DONE);
	}
	//DEBUG("E s = %d, c = %d, e = %d", (int)s, (int)c, (int)e);
	return b;
}

/* ======================================================================== */
/* [stmt] */

static size_t tglobal_stmt_initsize[] = {
    0,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    5,
    5,
    4,
    3,
    4,
    4,
    4,
    4,
    3,
    4,
    6,
    2,
    2,
    2,
    2,
    2,
    2,
    4,
    2,
    2,
    4,
    3,
    2,
    4,
    2,
    3,
    4,
    2,
    2,
    2,
    2,
    4,
    1,
    0
};

size_t knh_stmt_initsize(knh_stmt_t stt)
{
    return tglobal_stmt_initsize[stt];
}

/* ------------------------------------------------------------------------ */

char* knh_stmt_tochar(knh_stmt_t stt)
{
    switch(stt) {
    case STT_DONE: return "STT_DONE";
    case STT_NAMESPACE: return "STT_NAMESPACE";
    case STT_INCLUDE: return "STT_INCLUDE";
    case STT_UIMPORT: return "STT_UIMPORT";
    case STT_UVOCAB: return "STT_UVOCAB";
    case STT_UINT: return "STT_UINT";
    case STT_UINT64: return "STT_UINT64";
    case STT_UFLOAT: return "STT_UFLOAT";
    case STT_UTABLE: return "STT_UTABLE";
    case STT_UFUNC: return "STT_UFUNC";
    case STT_WEAVE: return "STT_WEAVE";
    case STT_CLASS: return "STT_CLASS";
    case STT_IMPLEMENTS: return "STT_IMPLEMENTS";
    case STT_METHOD: return "STT_METHOD";
    case STT_DECL: return "STT_DECL";
    case STT_IF: return "STT_IF";
    case STT_TRY: return "STT_TRY";
    case STT_CATCH: return "STT_CATCH";
    case STT_DO: return "STT_DO";
    case STT_WHILE: return "STT_WHILE";
    case STT_FOR: return "STT_FOR";
    case STT_FOREACH: return "STT_FOREACH";
    case STT_CONTINUE: return "STT_CONTINUE";
    case STT_BREAK: return "STT_BREAK";
    case STT_GOTO: return "STT_GOTO";
    case STT_THROW: return "STT_THROW";
    case STT_RETURN: return "STT_RETURN";
    case STT_EVAL: return "STT_EVAL";
    case STT_PRINT: return "STT_PRINT";
    case STT_ASSERT: return "STT_ASSERT";
    case STT_HELP: return "STT_HELP";
    case STT_NEW: return "STT_NEW";
    case STT_MAP: return "STT_MAP";
    case STT_LET: return "STT_LET";
    case STT_CALL: return "STT_CALL";
    case STT_MOVTEXT: return "STT_MOVTEXT";
    case STT_TRINARY: return "STT_TRINARY";
    case STT_OP: return "STT_OP";
    case STT_ALT: return "STT_ALT";
    case STT_AND: return "STT_AND";
    case STT_OR: return "STT_OR";
    case STT_NEXT: return "STT_NEXT";
    case STT_META: return "STT_META";
    case STT_ERR: return "STT_ERR";
    }
    return "STT_UKNOWN";
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_stmt_isDecl(knh_stmt_t stt)
{
    switch(stt) {
    case STT_DONE: return 0;
    case STT_NAMESPACE: return 1;
    case STT_INCLUDE: return 1;
    case STT_UIMPORT: return 1;
    case STT_UVOCAB: return 1;
    case STT_UINT: return 1;
    case STT_UINT64: return 1;
    case STT_UFLOAT: return 1;
    case STT_UTABLE: return 1;
    case STT_UFUNC: return 1;
    case STT_WEAVE: return 1;
    case STT_CLASS: return 1;
    case STT_IMPLEMENTS: return 0;
    case STT_METHOD: return 1;
    case STT_DECL: return 1;
    case STT_IF: return 0;
    case STT_TRY: return 0;
    case STT_CATCH: return 0;
    case STT_DO: return 0;
    case STT_WHILE: return 0;
    case STT_FOR: return 0;
    case STT_FOREACH: return 0;
    case STT_CONTINUE: return 0;
    case STT_BREAK: return 0;
    case STT_GOTO: return 0;
    case STT_THROW: return 0;
    case STT_RETURN: return 0;
    case STT_EVAL: return 0;
    case STT_PRINT: return 0;
    case STT_ASSERT: return 0;
    case STT_HELP: return 0;
    case STT_NEW: return 0;
    case STT_MAP: return 0;
    case STT_LET: return 0;
    case STT_CALL: return 0;
    case STT_MOVTEXT: return 0;
    case STT_TRINARY: return 0;
    case STT_OP: return 0;
    case STT_ALT: return 0;
    case STT_AND: return 0;
    case STT_OR: return 0;
    case STT_NEXT: return 0;
    case STT_META: return 0;
    case STT_ERR: return 0;
    }
    return 0;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_stmt_isDeclInClass(knh_stmt_t stt)
{
    switch(stt) {
    case STT_DONE: return 0;
    case STT_NAMESPACE: return 0;
    case STT_INCLUDE: return 0;
    case STT_UIMPORT: return 0;
    case STT_UVOCAB: return 0;
    case STT_UINT: return 0;
    case STT_UINT64: return 0;
    case STT_UFLOAT: return 0;
    case STT_UTABLE: return 0;
    case STT_UFUNC: return 0;
    case STT_WEAVE: return 0;
    case STT_CLASS: return 0;
    case STT_IMPLEMENTS: return 0;
    case STT_METHOD: return 1;
    case STT_DECL: return 1;
    case STT_IF: return 0;
    case STT_TRY: return 0;
    case STT_CATCH: return 0;
    case STT_DO: return 0;
    case STT_WHILE: return 0;
    case STT_FOR: return 0;
    case STT_FOREACH: return 0;
    case STT_CONTINUE: return 0;
    case STT_BREAK: return 0;
    case STT_GOTO: return 0;
    case STT_THROW: return 0;
    case STT_RETURN: return 0;
    case STT_EVAL: return 0;
    case STT_PRINT: return 0;
    case STT_ASSERT: return 0;
    case STT_HELP: return 0;
    case STT_NEW: return 0;
    case STT_MAP: return 0;
    case STT_LET: return 1;
    case STT_CALL: return 0;
    case STT_MOVTEXT: return 0;
    case STT_TRINARY: return 0;
    case STT_OP: return 0;
    case STT_ALT: return 0;
    case STT_AND: return 0;
    case STT_OR: return 0;
    case STT_NEXT: return 0;
    case STT_META: return 0;
    case STT_ERR: return 0;
    }
    return 0;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_stmt_isStatement(knh_stmt_t stt)
{
    switch(stt) {
    case STT_DONE: return 0;
    case STT_NAMESPACE: return 0;
    case STT_INCLUDE: return 0;
    case STT_UIMPORT: return 0;
    case STT_UVOCAB: return 0;
    case STT_UINT: return 0;
    case STT_UINT64: return 0;
    case STT_UFLOAT: return 0;
    case STT_UTABLE: return 0;
    case STT_UFUNC: return 0;
    case STT_WEAVE: return 0;
    case STT_CLASS: return 0;
    case STT_IMPLEMENTS: return 0;
    case STT_METHOD: return 0;
    case STT_DECL: return 1;
    case STT_IF: return 1;
    case STT_TRY: return 1;
    case STT_CATCH: return 0;
    case STT_DO: return 1;
    case STT_WHILE: return 1;
    case STT_FOR: return 1;
    case STT_FOREACH: return 1;
    case STT_CONTINUE: return 1;
    case STT_BREAK: return 1;
    case STT_GOTO: return 1;
    case STT_THROW: return 1;
    case STT_RETURN: return 1;
    case STT_EVAL: return 1;
    case STT_PRINT: return 1;
    case STT_ASSERT: return 1;
    case STT_HELP: return 1;
    case STT_NEW: return 0;
    case STT_MAP: return 0;
    case STT_LET: return 1;
    case STT_CALL: return 1;
    case STT_MOVTEXT: return 0;
    case STT_TRINARY: return 0;
    case STT_OP: return 0;
    case STT_ALT: return 0;
    case STT_AND: return 0;
    case STT_OR: return 0;
    case STT_NEXT: return 0;
    case STT_META: return 0;
    case STT_ERR: return 1;
    }
    return 0;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_stmt_isExpr(knh_stmt_t stt)
{
    switch(stt) {
    case STT_DONE: return 0;
    case STT_NAMESPACE: return 0;
    case STT_INCLUDE: return 0;
    case STT_UIMPORT: return 0;
    case STT_UVOCAB: return 0;
    case STT_UINT: return 0;
    case STT_UINT64: return 0;
    case STT_UFLOAT: return 0;
    case STT_UTABLE: return 0;
    case STT_UFUNC: return 0;
    case STT_WEAVE: return 0;
    case STT_CLASS: return 0;
    case STT_IMPLEMENTS: return 0;
    case STT_METHOD: return 1;
    case STT_DECL: return 0;
    case STT_IF: return 0;
    case STT_TRY: return 0;
    case STT_CATCH: return 0;
    case STT_DO: return 0;
    case STT_WHILE: return 0;
    case STT_FOR: return 0;
    case STT_FOREACH: return 0;
    case STT_CONTINUE: return 0;
    case STT_BREAK: return 0;
    case STT_GOTO: return 0;
    case STT_THROW: return 0;
    case STT_RETURN: return 0;
    case STT_EVAL: return 0;
    case STT_PRINT: return 0;
    case STT_ASSERT: return 0;
    case STT_HELP: return 0;
    case STT_NEW: return 1;
    case STT_MAP: return 1;
    case STT_LET: return 0;
    case STT_CALL: return 1;
    case STT_MOVTEXT: return 1;
    case STT_TRINARY: return 1;
    case STT_OP: return 1;
    case STT_ALT: return 1;
    case STT_AND: return 1;
    case STT_OR: return 1;
    case STT_NEXT: return 1;
    case STT_META: return 0;
    case STT_ERR: return 0;
    }
    return 0;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_stmt_isEval(knh_stmt_t stt)
{
    switch(stt) {
    case STT_DONE: return 0;
    case STT_NAMESPACE: return 0;
    case STT_INCLUDE: return 0;
    case STT_UIMPORT: return 0;
    case STT_UVOCAB: return 0;
    case STT_UINT: return 0;
    case STT_UINT64: return 0;
    case STT_UFLOAT: return 0;
    case STT_UTABLE: return 0;
    case STT_UFUNC: return 0;
    case STT_WEAVE: return 0;
    case STT_CLASS: return 0;
    case STT_IMPLEMENTS: return 0;
    case STT_METHOD: return 0;
    case STT_DECL: return 0;
    case STT_IF: return 0;
    case STT_TRY: return 0;
    case STT_CATCH: return 0;
    case STT_DO: return 0;
    case STT_WHILE: return 0;
    case STT_FOR: return 0;
    case STT_FOREACH: return 0;
    case STT_CONTINUE: return 0;
    case STT_BREAK: return 0;
    case STT_GOTO: return 0;
    case STT_THROW: return 0;
    case STT_RETURN: return 0;
    case STT_EVAL: return 0;
    case STT_PRINT: return 0;
    case STT_ASSERT: return 0;
    case STT_HELP: return 0;
    case STT_NEW: return 1;
    case STT_MAP: return 1;
    case STT_LET: return 1;
    case STT_CALL: return 1;
    case STT_MOVTEXT: return 1;
    case STT_TRINARY: return 1;
    case STT_OP: return 1;
    case STT_ALT: return 1;
    case STT_AND: return 1;
    case STT_OR: return 1;
    case STT_NEXT: return 1;
    case STT_META: return 0;
    case STT_ERR: return 0;
    }
    return 0;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
