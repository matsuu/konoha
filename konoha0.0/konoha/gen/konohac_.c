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

static char* knh_token_array_tochar[] = {
    "namespace",  /* namespace */ 
    "import",  /* import */ 
    "pragma",  /* pragma */ 
    "using",  /* using */ 
    "with",  /* with */ 
    "class",  /* class */ 
    "extends",  /* extends */ 
    "implements",  /* implements */ 
    "method",  /* method */ 
    "format",  /* format */ 
    "return",  /* return */ 
    "mapmap",  /* mapmap */ 
    "weave",  /* weave */ 
    "aspect",  /* aspect */ 
    "if",  /* if */ 
    "else",  /* else */ 
    "while",  /* while */ 
    "do",  /* do */ 
    "for",  /* for */ 
    "foreach",  /* foreach */ 
    "from",  /* from */ 
    "where",  /* where */ 
    "break",  /* break */ 
    "continue",  /* continue */ 
    "goto",  /* goto */ 
    "try",  /* try */ 
    "catch",  /* catch */ 
    "finally",  /* finally */ 
    "throw",  /* throw */ 
    "print",  /* print */ 
    "assert",  /* assert */ 
    "{",  /* BRACE */ 
    "(",  /* PARENTHESIS */ 
    "[",  /* BRANCET */ 
    "...",  /* DOTS */ 
    ";",  /* SEMICOLON */ 
    ",",  /* COMMA */ 
    "=",  /* LET */ 
    "<<=",  /* lshifte */ 
    ">>=",  /* rshifte */ 
    "+=",  /* adde */ 
    "-=",  /* sube */ 
    "*=",  /* mule */ 
    "/=",  /* dive */ 
    "%=",  /* mode */ 
    "|=",  /* bitore */ 
    "&=",  /* bitande */ 
    "?\?=",  /* ALTLET */ 
    "?",  /* QUESTION */ 
    "..",  /* SUBSET */ 
    "..<",  /* SLICE */ 
    "..+",  /* OFFSET */ 
    ":",  /* COLON */ 
    "||",  /* OR */ 
    "&&",  /* AND */ 
    "!",  /* Not */ 
    "instanceof",  /* Instanceof */ 
    "isa?",  /* Isa */ 
    "as",  /* As */ 
    "in?",  /* In */ 
    "===",  /* Is */ 
    "to?",  /* To */ 
    "==",  /* Eq */ 
    "!=",  /* Neq */ 
    "<",  /* Lt */ 
    "<=",  /* Lte */ 
    ">",  /* Gt */ 
    ">=",  /* Gte */ 
    "<<",  /* LShift */ 
    ">>",  /* RShift */ 
    "+",  /* Add */ 
    "-",  /* Sub */ 
    "/",  /* Div */ 
    "*",  /* Mul */ 
    "|",  /* LogicalOr */ 
    "&",  /* LogicalAnd */ 
    "?\?",  /* ALT */ 
    "~",  /* LogicalNot */ 
    "^",  /* LogicalXor */ 
    "++",  /* Next */ 
    "--",  /* Prev */ 
    "%",  /* Mod */ 
    "NUM",  /* NUM */ 
    "STR",  /* STR */ 
    "TSTR",  /* TSTR */ 
    "FMTSTR",  /* FMTSTR */ 
    "LABEL",  /* LABEL */ 
    "METAN",  /* METAN */ 
    "PROPN",  /* PROPN */ 
    "URN",  /* URN */ 
    "MT",  /* MT */ 
    "CONSTN",  /* CONSTN */ 
    "TYPEN",  /* TYPEN */ 
    "CMETHODN",  /* CMETHODN */ 
    "NAME",  /* NAME */ 
    "MN",  /* MN */ 
    "FN",  /* FN */ 
    "CID",  /* CID */ 
    "CONST",  /* CONST */ 
    "MTDMPR",  /* MTDMPR */ 
    "EBPIDX",  /* EBPIDX */ 
    "SFPIDX",  /* SFPIDX */ 
    "FLDIDX",  /* FLDIDX */ 
    "OBJIDX",  /* OBJIDX */ 
    "SYSCONST",  /* SYSCONST */ 
    "_",  /* ASIS */ 
    "ERR",  /* ERR */ 
    "EOT",  /* EOT */ 
    //(char*)0
};

char* knh_token_tochar(knh_token_t t)
{
    DEBUG_ASSERT(t < KNH_TOKEN_MAXSIZ);
    return knh_token_array_tochar[t];
}

/* ------------------------------------------------------------------------ */

static knh_methodn_t knh_token_array_tomethodn[] = {
    METHODN_NONAME,  /* namespace */ 
    METHODN_NONAME,  /* import */ 
    METHODN_NONAME,  /* pragma */ 
    METHODN_NONAME,  /* using */ 
    METHODN_NONAME,  /* with */ 
    METHODN_NONAME,  /* class */ 
    METHODN_NONAME,  /* extends */ 
    METHODN_NONAME,  /* implements */ 
    METHODN_NONAME,  /* method */ 
    METHODN_NONAME,  /* format */ 
    METHODN_NONAME,  /* return */ 
    METHODN_NONAME,  /* mapmap */ 
    METHODN_NONAME,  /* weave */ 
    METHODN_NONAME,  /* aspect */ 
    METHODN_NONAME,  /* if */ 
    METHODN_NONAME,  /* else */ 
    METHODN_NONAME,  /* while */ 
    METHODN_NONAME,  /* do */ 
    METHODN_NONAME,  /* for */ 
    METHODN_NONAME,  /* foreach */ 
    METHODN_NONAME,  /* from */ 
    METHODN_NONAME,  /* where */ 
    METHODN_NONAME,  /* break */ 
    METHODN_NONAME,  /* continue */ 
    METHODN_NONAME,  /* goto */ 
    METHODN_NONAME,  /* try */ 
    METHODN_NONAME,  /* catch */ 
    METHODN_NONAME,  /* finally */ 
    METHODN_NONAME,  /* throw */ 
    METHODN_NONAME,  /* print */ 
    METHODN_NONAME,  /* assert */ 
    METHODN_NONAME,  /* BRACE */ 
    METHODN_NONAME,  /* PARENTHESIS */ 
    METHODN_NONAME,  /* BRANCET */ 
    METHODN_NONAME,  /* DOTS */ 
    METHODN_NONAME,  /* SEMICOLON */ 
    METHODN_NONAME,  /* COMMA */ 
    METHODN_NONAME,  /* LET */ 
    METHODN_NONAME,  /* lshifte */ 
    METHODN_NONAME,  /* rshifte */ 
    METHODN_NONAME,  /* adde */ 
    METHODN_NONAME,  /* sube */ 
    METHODN_NONAME,  /* mule */ 
    METHODN_NONAME,  /* dive */ 
    METHODN_NONAME,  /* mode */ 
    METHODN_NONAME,  /* bitore */ 
    METHODN_NONAME,  /* bitande */ 
    METHODN_NONAME,  /* ALTLET */ 
    METHODN_NONAME,  /* QUESTION */ 
    METHODN_NONAME,  /* SUBSET */ 
    METHODN_NONAME,  /* SLICE */ 
    METHODN_NONAME,  /* OFFSET */ 
    METHODN_NONAME,  /* COLON */ 
    METHODN_NONAME,  /* OR */ 
    METHODN_NONAME,  /* AND */ 
    METHODN_opNot,  /* Not */ 
    METHODN_opInstanceof,  /* Instanceof */ 
    METHODN_opIsa,  /* Isa */ 
    METHODN_opAs,  /* As */ 
    METHODN_opIn,  /* In */ 
    METHODN_opIs,  /* Is */ 
    METHODN_opTo,  /* To */ 
    METHODN_opEq,  /* Eq */ 
    METHODN_opNeq,  /* Neq */ 
    METHODN_opLt,  /* Lt */ 
    METHODN_opLte,  /* Lte */ 
    METHODN_opGt,  /* Gt */ 
    METHODN_opGte,  /* Gte */ 
    METHODN_opLShift,  /* LShift */ 
    METHODN_opRShift,  /* RShift */ 
    METHODN_opAdd,  /* Add */ 
    METHODN_opSub,  /* Sub */ 
    METHODN_opDiv,  /* Div */ 
    METHODN_opMul,  /* Mul */ 
    METHODN_opLogicalOr,  /* LogicalOr */ 
    METHODN_opLogicalAnd,  /* LogicalAnd */ 
    METHODN_opALT,  /* ALT */ 
    METHODN_opLogicalNot,  /* LogicalNot */ 
    METHODN_opLogicalXor,  /* LogicalXor */ 
    METHODN_opNext,  /* Next */ 
    METHODN_opPrev,  /* Prev */ 
    METHODN_opMod,  /* Mod */ 
    METHODN_NONAME,  /* NUM */ 
    METHODN_NONAME,  /* STR */ 
    METHODN_NONAME,  /* TSTR */ 
    METHODN_NONAME,  /* FMTSTR */ 
    METHODN_NONAME,  /* LABEL */ 
    METHODN_NONAME,  /* METAN */ 
    METHODN_NONAME,  /* PROPN */ 
    METHODN_NONAME,  /* URN */ 
    METHODN_NONAME,  /* MT */ 
    METHODN_NONAME,  /* CONSTN */ 
    METHODN_NONAME,  /* TYPEN */ 
    METHODN_NONAME,  /* CMETHODN */ 
    METHODN_NONAME,  /* NAME */ 
    METHODN_NONAME,  /* MN */ 
    METHODN_NONAME,  /* FN */ 
    METHODN_NONAME,  /* CID */ 
    METHODN_NONAME,  /* CONST */ 
    METHODN_NONAME,  /* MTDMPR */ 
    METHODN_NONAME,  /* EBPIDX */ 
    METHODN_NONAME,  /* SFPIDX */ 
    METHODN_NONAME,  /* FLDIDX */ 
    METHODN_NONAME,  /* OBJIDX */ 
    METHODN_NONAME,  /* SYSCONST */ 
    METHODN_NONAME,  /* ASIS */ 
    METHODN_NONAME,  /* ERR */ 
    METHODN_NONAME,  /* EOT */ 
    //(knh_methodn_t)0
};

knh_methodn_t knh_token_tomethodn(knh_token_t t)
{
    DEBUG_ASSERT(t < KNH_TOKEN_MAXSIZ);
    return knh_token_array_tomethodn[t];
}

/* ------------------------------------------------------------------------ */

static knh_bool_t knh_token_array_isEndOfStmt[] = {
    1,  /* namespace */ 
    1,  /* import */ 
    1,  /* pragma */ 
    1,  /* using */ 
    1,  /* with */ 
    1,  /* class */ 
    1,  /* extends */ 
    1,  /* implements */ 
    1,  /* method */ 
    1,  /* format */ 
    1,  /* return */ 
    1,  /* mapmap */ 
    1,  /* weave */ 
    1,  /* aspect */ 
    1,  /* if */ 
    1,  /* else */ 
    1,  /* while */ 
    1,  /* do */ 
    1,  /* for */ 
    1,  /* foreach */ 
    1,  /* from */ 
    1,  /* where */ 
    1,  /* break */ 
    1,  /* continue */ 
    1,  /* goto */ 
    1,  /* try */ 
    1,  /* catch */ 
    1,  /* finally */ 
    1,  /* throw */ 
    1,  /* print */ 
    1,  /* assert */ 
    0,  /* BRACE */ 
    0,  /* PARENTHESIS */ 
    0,  /* BRANCET */ 
    0,  /* DOTS */ 
    1,  /* SEMICOLON */ 
    0,  /* COMMA */ 
    0,  /* LET */ 
    0,  /* lshifte */ 
    0,  /* rshifte */ 
    0,  /* adde */ 
    0,  /* sube */ 
    0,  /* mule */ 
    0,  /* dive */ 
    0,  /* mode */ 
    0,  /* bitore */ 
    0,  /* bitande */ 
    0,  /* ALTLET */ 
    0,  /* QUESTION */ 
    0,  /* SUBSET */ 
    0,  /* SLICE */ 
    0,  /* OFFSET */ 
    0,  /* COLON */ 
    0,  /* OR */ 
    0,  /* AND */ 
    0,  /* Not */ 
    0,  /* Instanceof */ 
    0,  /* Isa */ 
    0,  /* As */ 
    0,  /* In */ 
    0,  /* Is */ 
    0,  /* To */ 
    0,  /* Eq */ 
    0,  /* Neq */ 
    0,  /* Lt */ 
    0,  /* Lte */ 
    0,  /* Gt */ 
    0,  /* Gte */ 
    0,  /* LShift */ 
    0,  /* RShift */ 
    0,  /* Add */ 
    0,  /* Sub */ 
    0,  /* Div */ 
    0,  /* Mul */ 
    0,  /* LogicalOr */ 
    0,  /* LogicalAnd */ 
    0,  /* ALT */ 
    0,  /* LogicalNot */ 
    0,  /* LogicalXor */ 
    0,  /* Next */ 
    0,  /* Prev */ 
    0,  /* Mod */ 
    0,  /* NUM */ 
    0,  /* STR */ 
    0,  /* TSTR */ 
    0,  /* FMTSTR */ 
    0,  /* LABEL */ 
    1,  /* METAN */ 
    0,  /* PROPN */ 
    0,  /* URN */ 
    0,  /* MT */ 
    0,  /* CONSTN */ 
    0,  /* TYPEN */ 
    0,  /* CMETHODN */ 
    0,  /* NAME */ 
    0,  /* MN */ 
    0,  /* FN */ 
    0,  /* CID */ 
    0,  /* CONST */ 
    0,  /* MTDMPR */ 
    0,  /* EBPIDX */ 
    0,  /* SFPIDX */ 
    0,  /* FLDIDX */ 
    0,  /* OBJIDX */ 
    0,  /* SYSCONST */ 
    0,  /* ASIS */ 
    0,  /* ERR */ 
    1,  /* EOT */ 
    //(knh_bool_t)0
};

knh_bool_t knh_token_isEndOfStmt(knh_token_t t)
{
    DEBUG_ASSERT(t < KNH_TOKEN_MAXSIZ);
    return knh_token_array_isEndOfStmt[t];
}

/* ------------------------------------------------------------------------ */

/* ======================================================================== */
/* [token parser] */

PUBLIC
Token *new_Token__parse(Ctx *ctx, knh_flag_t flag, knh_fileid_t fileid, knh_line_t line, knh_bytes_t token, BytesConv *bconv)
{
    knh_bytes_t t = token;
    knh_token_t tt = ((knh_token_t)-1);
    L_TAIL:;
    //if(t.buf[0] == '.' && islower(t.buf[1])) {   /* .name   => name */
        //flag |= KNH_FLAG_TKF_TOPDOT;
        //t.buf++; t.len--;
    //}
    if(isalpha(t.buf[0])) {
        if(t.buf[t.len-2]=='.' && t.buf[t.len-1]=='.') {
            flag |= KNH_FLAG_TKF_ITERATORTYPE;
            t.len -= 2;
        }
        if(t.buf[t.len-2]=='.' && t.buf[t.len-1]=='*') {
            flag |= KNH_FLAG_TKF_TAILWILDCARD;
            t.len -= 2;
        }
        if(isupper(t.buf[0]) && t.len > 9 && knh_bytes_endsWith(t, STEXT("Exception"))) {
            flag |= (KNH_FLAG_TKF_EXCEPTIONTYPE|KNH_FLAG_TKF_NOTNULLTYPE);
            t.len -= 9;
        }
        else if(t.buf[t.len-2]=='!' && t.buf[t.len-1]=='!') {
            flag |= (KNH_FLAG_TKF_EXCEPTIONTYPE|KNH_FLAG_TKF_NOTNULLTYPE);
            t.len -= 2;
        }
        else if(t.buf[t.len-1]=='!') {
            flag |= KNH_FLAG_TKF_NOTNULLTYPE;
            t.len -= 1;
        }
    }

    switch(t.buf[0]) {
    case '!':
        if(ISB(t, "!")) { tt = TT_NOT; break; }
        if(ISB(t, "!=")) { tt = TT_NEQ; break; }
    break;
    case '%':
        if(ISB(t, "%=")) { tt = TT_MODE; break; }
        if(ISB(t, "%")) { tt = TT_MOD; break; }
    break;
    case '&':
        if(ISB(t, "&=")) { tt = TT_BITANDE; break; }
        if(ISB(t, "&&")) { tt = TT_AND; break; }
        if(ISB(t, "&")) { tt = TT_LOGICALAND; break; }
    break;
    case '(':
        if(ISB(t, "(")) { tt = TT_PARENTHESIS; break; }
    break;
    case '*':
        if(ISB(t, "*=")) { tt = TT_MULE; break; }
        if(ISB(t, "*")) { tt = TT_MUL; break; }
    break;
    case '+':
        if(ISB(t, "+=")) { tt = TT_ADDE; break; }
        if(ISB(t, "+")) { tt = TT_ADD; break; }
        if(ISB(t, "++")) { tt = TT_NEXT; break; }
    break;
    case ',':
        if(ISB(t, ",")) { tt = TT_COMMA; break; }
    break;
    case '-':
        if(ISB(t, "-=")) { tt = TT_SUBE; break; }
        if(ISB(t, "-->")) { tt = TT_TO; break; }
        if(ISB(t, "-")) { tt = TT_SUB; break; }
        if(ISB(t, "--")) { tt = TT_PREV; break; }
    break;
    case '.':
        if(ISB(t, "...")) { tt = TT_DOTS; break; }
        if(ISB(t, "..")) { tt = TT_SUBSET; break; }
        if(ISB(t, "..<")) { tt = TT_SLICE; break; }
        if(ISB(t, "..+")) { tt = TT_OFFSET; break; }
    break;
    case '/':
        if(ISB(t, "/=")) { tt = TT_DIVE; break; }
        if(ISB(t, "/")) { tt = TT_DIV; break; }
    break;
    case ':':
        if(ISB(t, ":")) { tt = TT_COLON; break; }
    break;
    case ';':
        if(ISB(t, ";")) { tt = TT_SEMICOLON; break; }
    break;
    case '<':
        if(ISB(t, "<<=")) { tt = TT_LSHIFTE; break; }
        if(ISB(t, "<")) { tt = TT_LT; break; }
        if(ISB(t, "<=")) { tt = TT_LTE; break; }
        if(ISB(t, "<<")) { tt = TT_LSHIFT; break; }
    break;
    case '=':
        if(ISB(t, "=")) { tt = TT_LET; break; }
        if(ISB(t, "===")) { tt = TT_IS; break; }
        if(ISB(t, "==")) { tt = TT_EQ; break; }
    break;
    case '>':
        if(ISB(t, ">>=")) { tt = TT_RSHIFTE; break; }
        if(ISB(t, ">")) { tt = TT_GT; break; }
        if(ISB(t, ">=")) { tt = TT_GTE; break; }
        if(ISB(t, ">>")) { tt = TT_RSHIFT; break; }
    break;
    case '?':
        if(ISB(t, "?\?=")) { tt = TT_ALTLET; break; }
        if(ISB(t, "?")) { tt = TT_QUESTION; break; }
        if(ISB(t, "?\?")) { tt = TT_ALT; break; }
    break;
    case 'A':
        if(ISB(t, "ArrayList")) { t = STEXT("Array"); goto L_TAIL; }
    break;
    case 'F':
        if(ISB(t, "FALSE")) { t = STEXT("false"); goto L_TAIL; }
        if(ISB(t, "False")) { t = STEXT("false"); goto L_TAIL; }
    break;
    case 'I':
        if(ISB(t, "Integer")) { t = STEXT("Int"); goto L_TAIL; }
    break;
    case 'N':
        if(ISB(t, "NULL")) { t = STEXT("null"); goto L_TAIL; }
    break;
    case 'T':
        if(ISB(t, "TRUE")) { t = STEXT("true"); goto L_TAIL; }
        if(ISB(t, "True")) { t = STEXT("true"); goto L_TAIL; }
    break;
    case '[':
        if(ISB(t, "[")) { tt = TT_BRANCET; break; }
    break;
    case '^':
        if(ISB(t, "^")) { tt = TT_LOGICALXOR; break; }
    break;
    case '_':
        if(ISB(t, "_")) { tt = TT_ASIS; break; }
    break;
    case 'a':
        if(ISB(t, "aspect")) { tt = TT_ASPECT; break; }
        if(ISB(t, "assert")) { tt = TT_ASSERT; break; }
        if(ISB(t, "and")) { tt = TT_AND; break; }
        if(ISB(t, "as")) { tt = TT_AS; break; }
    break;
    case 'b':
        if(ISB(t, "break")) { tt = TT_BREAK; break; }
        if(ISB(t, "boolean")) { t = STEXT("Boolean!"); goto L_TAIL; }
    break;
    case 'c':
        if(ISB(t, "class")) { tt = TT_CLASS; break; }
        if(ISB(t, "continue")) { tt = TT_CONTINUE; break; }
        if(ISB(t, "catch")) { tt = TT_CATCH; break; }
        if(ISB(t, "const")) { tt = TT_METAN; break; }
    break;
    case 'd':
        if(ISB(t, "do")) { tt = TT_DO; break; }
        if(ISB(t, "double")) { t = STEXT("Float!"); goto L_TAIL; }
        if(ISB(t, "def")) { t = STEXT("Any"); goto L_TAIL; }
    break;
    case 'e':
        if(ISB(t, "extends")) { tt = TT_EXTENDS; break; }
        if(ISB(t, "else")) { tt = TT_ELSE; break; }
    break;
    case 'f':
        if(ISB(t, "format")) { tt = TT_FORMAT; break; }
        if(ISB(t, "for")) { tt = TT_FOR; break; }
        if(ISB(t, "foreach")) { tt = TT_FOREACH; break; }
        if(ISB(t, "from")) { tt = TT_FROM; break; }
        if(ISB(t, "finally")) { tt = TT_FINALLY; break; }
        if(ISB(t, "final")) { tt = TT_METAN; break; }
        if(ISB(t, "float")) { t = STEXT("Float!"); goto L_TAIL; }
    break;
    case 'g':
        if(ISB(t, "goto")) { tt = TT_GOTO; break; }
    break;
    case 'i':
        if(ISB(t, "import")) { tt = TT_IMPORT; break; }
        if(ISB(t, "implements")) { tt = TT_IMPLEMENTS; break; }
        if(ISB(t, "if")) { tt = TT_IF; break; }
        if(ISB(t, "instanceof")) { tt = TT_INSTANCEOF; break; }
        if(ISB(t, "isa?")) { tt = TT_ISA; break; }
        if(ISB(t, "isa")) { tt = TT_ISA; break; }
        if(ISB(t, "in?")) { tt = TT_IN; break; }
        if(ISB(t, "is?")) { tt = TT_IS; break; }
        if(ISB(t, "int")) { t = STEXT("Int!"); goto L_TAIL; }
    break;
    case 'l':
        if(ISB(t, "long")) { t = STEXT("Int64!"); goto L_TAIL; }
    break;
    case 'm':
        if(ISB(t, "method")) { tt = TT_METHOD; break; }
        if(ISB(t, "mapmap")) { tt = TT_MAPMAP; break; }
        if(ISB(t, "mod")) { tt = TT_MOD; break; }
    break;
    case 'n':
        if(ISB(t, "namespace")) { tt = TT_NAMESPACE; break; }
        if(ISB(t, "not")) { tt = TT_NOT; break; }
    break;
    case 'o':
        if(ISB(t, "or")) { tt = TT_OR; break; }
    break;
    case 'p':
        if(ISB(t, "pragma")) { tt = TT_PRAGMA; break; }
        if(ISB(t, "print")) { tt = TT_PRINT; break; }
        if(ISB(t, "public")) { tt = TT_METAN; break; }
        if(ISB(t, "private")) { tt = TT_METAN; break; }
    break;
    case 'r':
        if(ISB(t, "return")) { tt = TT_RETURN; break; }
    break;
    case 's':
        if(ISB(t, "static")) { tt = TT_METAN; break; }
    break;
    case 't':
        if(ISB(t, "try")) { tt = TT_TRY; break; }
        if(ISB(t, "throw")) { tt = TT_THROW; break; }
        if(ISB(t, "to?")) { tt = TT_TO; break; }
    break;
    case 'u':
        if(ISB(t, "using")) { tt = TT_USING; break; }
    break;
    case 'v':
        if(ISB(t, "virtual")) { tt = TT_METAN; break; }
    break;
    case 'w':
        if(ISB(t, "with")) { tt = TT_WITH; break; }
        if(ISB(t, "weave")) { tt = TT_WEAVE; break; }
        if(ISB(t, "while")) { tt = TT_WHILE; break; }
        if(ISB(t, "where")) { tt = TT_WHERE; break; }
    break;
    case '{':
        if(ISB(t, "{")) { tt = TT_BRACE; break; }
    break;
    case '|':
        if(ISB(t, "|=")) { tt = TT_BITORE; break; }
        if(ISB(t, "||")) { tt = TT_OR; break; }
        if(ISB(t, "|")) { tt = TT_LOGICALOR; break; }
    break;
    case '~':
        if(ISB(t, "~")) { tt = TT_LOGICALNOT; break; }
    break;
    /* built-in */
    }
    if(tt == ((knh_token_t)-1)) {
        return new_Token__name(ctx, flag, fileid, line, t);
    }
    else {
        Token *tk = new_Token(ctx, flag, fileid, line, tt);
        if(tt == TT_METAN) {
            KNH_SETv(ctx, DP(tk)->data, new_String(ctx, t, NULL));
        }
        return  tk;
    }
}

/* ======================================================================== */
/* [stmt] */

static char* knh_stmt_array_tochar[] = {
    "done",  /* done */ 
    "namespace",  /* namespace */ 
    "import",  /* import */ 
    "pragma",  /* pragma */ 
    "using",  /* using */ 
    "using import",  /* using import */ 
    "using alias",  /* using alias */ 
    "using unit",  /* using unit */ 
    "using enum",  /* using enum */ 
    "using vocab",  /* using vocab */ 
    "with",  /* with */ 
    "using func",  /* using func */ 
    "using mapmap",  /* using mapmap */ 
    "class",  /* class */ 
    "extends",  /* extends */ 
    "implements",  /* implements */ 
    "method",  /* method */ 
    "closure",  /* closure */ 
    "format",  /* format */ 
    "decl",  /* decl */ 
    "return",  /* return */ 
    "mapmap",  /* mapmap */ 
    "weave",  /* weave */ 
    "aspect",  /* aspect */ 
    "if",  /* if */ 
    "else",  /* else */ 
    "while",  /* while */ 
    "do",  /* do */ 
    "for",  /* for */ 
    "foreach",  /* foreach */ 
    "from",  /* from */ 
    "where",  /* where */ 
    "break",  /* break */ 
    "continue",  /* continue */ 
    "goto",  /* goto */ 
    "try",  /* try */ 
    "catch",  /* catch */ 
    "finally",  /* finally */ 
    "throw",  /* throw */ 
    "err",  /* err */ 
    "let",  /* let */ 
    "letmulti",  /* letmulti */ 
    "new",  /* new */ 
    "mapcast",  /* mapcast */ 
    "call",  /* call */ 
    "call1",  /* call1 */ 
    "pcall",  /* pcall */ 
    "mt",  /* mt */ 
    "op",  /* op */ 
    "trinary",  /* trinary */ 
    "alt",  /* alt */ 
    "and",  /* and */ 
    "or",  /* or */ 
    "print",  /* print */ 
    "assert",  /* assert */ 
    "man",  /* man */ 
    //(char*)0
};

char* knh_stmt_tochar(knh_stmt_t t)
{
    DEBUG_ASSERT(t < KNH_STMT_MAXSIZ);
    return knh_stmt_array_tochar[t];
}

/* ------------------------------------------------------------------------ */

static size_t knh_stmt_array_size[] = {
    0,  /* done */ 
    1,  /* namespace */ 
    1,  /* import */ 
    2,  /* pragma */ 
    0,  /* using */ 
    1,  /* using import */ 
    2,  /* using alias */ 
    2,  /* using unit */ 
    2,  /* using enum */ 
    2,  /* using vocab */ 
    0,  /* with */ 
    1,  /* using func */ 
    3,  /* using mapmap */ 
    4,  /* class */ 
    0,  /* extends */ 
    5,  /* implements */ 
    5,  /* method */ 
    3,  /* closure */ 
    7,  /* format */ 
    3,  /* decl */ 
    5,  /* return */ 
    5,  /* mapmap */ 
    2,  /* weave */ 
    5,  /* aspect */ 
    3,  /* if */ 
    0,  /* else */ 
    2,  /* while */ 
    2,  /* do */ 
    4,  /* for */ 
    5,  /* foreach */ 
    0,  /* from */ 
    0,  /* where */ 
    1,  /* break */ 
    1,  /* continue */ 
    1,  /* goto */ 
    3,  /* try */ 
    3,  /* catch */ 
    0,  /* finally */ 
    1,  /* throw */ 
    1,  /* err */ 
    2,  /* let */ 
    5,  /* letmulti */ 
    7,  /* new */ 
    3,  /* mapcast */ 
    7,  /* call */ 
    1,  /* call1 */ 
    7,  /* pcall */ 
    3,  /* mt */ 
    7,  /* op */ 
    3,  /* trinary */ 
    5,  /* alt */ 
    5,  /* and */ 
    5,  /* or */ 
    5,  /* print */ 
    1,  /* assert */ 
    1,  /* man */ 
    //(size_t)0
};

size_t knh_stmt_size(knh_stmt_t t)
{
    DEBUG_ASSERT(t < KNH_STMT_MAXSIZ);
    return knh_stmt_array_size[t];
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [EXPTN] */

void knh_Stmt_add_EXPTN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isEXPTN(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_perror(ctx, o, tc, KMSG_TEXPTN);
	}
}

/* ------------------------------------------------------------------------ */
/* [NSNAME] */

void knh_Stmt_add_NSNAME(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isNSNAME(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_perror(ctx, o, tc, KMSG_TNSNAME);
	}
}

/* ------------------------------------------------------------------------ */
/* [CURN] */

void knh_Stmt_add_CURN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isCURN(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_perror(ctx, o, tc, KMSG_TCURN);
	}
}

/* ------------------------------------------------------------------------ */
/* [NSCLASSN] */

void knh_Stmt_add_NSCLASSN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isNSCLASSN(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_perror(ctx, o, tc, KMSG_TNSCLASSN);
	}
}

/* ------------------------------------------------------------------------ */
/* [TYPEN] */

void knh_Stmt_add_TYPEN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isTYPEN(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_perror(ctx, o, tc, KMSG_TTYPEN);
	}
}

/* ------------------------------------------------------------------------ */
/* [METHODN] */

void knh_Stmt_add_METHODN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isMETHODN(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_perror(ctx, o, tc, KMSG_TMETHODN);
	}
}

/* ------------------------------------------------------------------------ */
/* [FURN] */

void knh_Stmt_add_FURN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isFURN(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_perror(ctx, o, tc, KMSG_TFURN);
	}
}

/* ------------------------------------------------------------------------ */
/* [CLASSTN] */

void knh_Stmt_add_CLASSTN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isCLASSTN(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_perror(ctx, o, tc, KMSG_TCLASSTN);
	}
}

/* ------------------------------------------------------------------------ */
/* [STR] */

void knh_Stmt_add_STR(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isSTR(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_perror(ctx, o, tc, KMSG_TSTR);
	}
}

/* ------------------------------------------------------------------------ */
/* [VARN] */

void knh_Stmt_add_VARN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isVARN(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_perror(ctx, o, tc, KMSG_TVARN);
	}
}

/* ------------------------------------------------------------------------ */
/* [CLASSN] */

void knh_Stmt_add_CLASSN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isCLASSN(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_perror(ctx, o, tc, KMSG_TCLASSN);
	}
}

/* ------------------------------------------------------------------------ */
/* [CMETHODN] */

void knh_Stmt_add_CMETHODN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isCMETHODN(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_perror(ctx, o, tc, KMSG_TCMETHODN);
	}
}

/* ------------------------------------------------------------------------ */
/* [MT] */

void knh_Stmt_add_MT(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isMT(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_perror(ctx, o, tc, KMSG_TMT);
	}
}

/* ------------------------------------------------------------------------ */
/* [ANY] */

void knh_Stmt_add_ANY(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isANY(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_perror(ctx, o, tc, KMSG_TANY);
	}
}

/* ======================================================================== */
/* [stmt parser] */

/* ------------------------------------------------------------------------ */
/* [namespace] */

static Stmt *new_StmtNAMESPACE(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_NAMESPACE);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_NSNAME(ctx, o, tc); /* NSNAME */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [import] */

static Stmt *new_StmtIMPORT(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_IMPORT);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_FURN(ctx, o, tc); /* FURN */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [pragma] */

static Stmt *new_StmtPRAGMA(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_PRAGMA);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_VARN(ctx, o, tc); /* VARN */
	knh_Stmt_add_PRAGMA(ctx, o, tc); /* pragma */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [class] */

static Stmt *new_StmtCLASS(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_CLASS);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_CLASSN(ctx, o, tc); /* CLASSN */
	knh_Stmt_add_EXTENDS(ctx, o, tc); /* extends */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [format] */

static Stmt *new_StmtFORMAT(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_FORMAT);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_MT(ctx, o, tc); /* MT */
	knh_Stmt_add_PARAMs(ctx, o, tc); /* PARAM* */
	knh_Stmt_add_STR(ctx, o, tc); /* STR */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [return] */

static Stmt *new_StmtRETURN(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_RETURN);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_EXPRs(ctx, o, tc); /* EXPR* */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [mapmap] */

static Stmt *new_StmtMAPMAP(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_MAPMAP);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_CLASSTNs(ctx, o, tc); /* CLASSTN* */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [weave] */

static Stmt *new_StmtWEAVE(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_WEAVE);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_ANY(ctx, o, tc); /* ANY */
	knh_Stmt_add_CMETHODN(ctx, o, tc); /* CMETHODN */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [aspect] */

static Stmt *new_StmtASPECT(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_ASPECT);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_TYPEN(ctx, o, tc); /* TYPEN */
	knh_Stmt_add_CMETHOD(ctx, o, tc); /* cmethod */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [if] */

static Stmt *new_StmtIF(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_IF);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_PEXPR(ctx, o, tc); /* pexpr */
	knh_Stmt_add_STMT1(ctx, o, tc); /* { */
	knh_Stmt_add_ELSE(ctx, o, tc); /* else */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [while] */

static Stmt *new_StmtWHILE(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_WHILE);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_PEXPR(ctx, o, tc); /* pexpr */
	knh_Stmt_add_STMT1(ctx, o, tc); /* { */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [do] */

static Stmt *new_StmtDO(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_DO);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_STMT1(ctx, o, tc); /* { */
	knh_Stmt_add_PEXPR(ctx, o, tc); /* pexpr */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [for] */

static Stmt *new_StmtFOR(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_FOR);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_PSTMT3(ctx, o, tc); /* pstmt3 */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [foreach] */

static Stmt *new_StmtFOREACH(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_FOREACH);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_PEACH(ctx, o, tc); /* peach */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [break] */

static Stmt *new_StmtBREAK(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_BREAK);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_ANY_(ctx, o, tc); /* any_ */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [continue] */

static Stmt *new_StmtCONTINUE(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_CONTINUE);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_ANY_(ctx, o, tc); /* any_ */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [goto] */

static Stmt *new_StmtGOTO(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_GOTO);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_ANY(ctx, o, tc); /* ANY */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [try] */

static Stmt *new_StmtTRY(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_TRY);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_STMT1(ctx, o, tc); /* { */
	knh_Stmt_add_CATCH(ctx, o, tc); /* STT_CATCH */
	knh_Stmt_add_STMT1(ctx, o, tc); /* { */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [throw] */

static Stmt *new_StmtTHROW(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_THROW);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_EXPR(ctx, o, tc); /* expr */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [print] */

static Stmt *new_StmtPRINT(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_PRINT);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_EXPRs(ctx, o, tc); /* expr* */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [assert] */

static Stmt *new_StmtASSERT(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_ASSERT);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_PEXPR(ctx, o, tc); /* pexpr */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [man] */

static Stmt *new_StmtMAN(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_MAN);
	knh_StmtMETA_add_prestmt(ctx, o, tc, -2);
	knh_Stmt_add_ANY(ctx, o, tc); /* ANY */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* [stmt1] */

Stmt *
new_StmtSTMT1(Ctx *ctx, knh_tokens_t *tc)
{
    Token *tkc = NULL;
    L_TAIL:;
    if(!(tc->c < tc->e)) {
        DBG2_P("c = %d, e = %d", tc->c, tc->e);
        return new_StmtDONE(ctx);
    }
    tkc = tc->ts[tc->c];
    tc->c += 1;
    switch(SP(tkc)->tt) {
 
    case TT_NAMESPACE: 
        return new_StmtNAMESPACE(ctx, tc);
    case TT_IMPORT: 
        return new_StmtIMPORT(ctx, tc);
    case TT_PRAGMA: 
        return new_StmtPRAGMA(ctx, tc);
    case TT_USING: 
        return new_StmtUSING(ctx, tc);
    case TT_WITH:  /* with */
        break;
    case TT_CLASS: 
        return new_StmtCLASS(ctx, tc);
    case TT_EXTENDS:  /* extends */
        break;
    case TT_IMPLEMENTS:  /* implements */
        break;
    case TT_METHOD: 
        return new_StmtMETHOD(ctx, tc);
    case TT_FORMAT: 
        return new_StmtFORMAT(ctx, tc);
    case TT_RETURN: 
        return new_StmtRETURN(ctx, tc);
    case TT_MAPMAP: 
        return new_StmtMAPMAP(ctx, tc);
    case TT_WEAVE: 
        return new_StmtWEAVE(ctx, tc);
    case TT_ASPECT: 
        return new_StmtASPECT(ctx, tc);
    case TT_IF: 
        return new_StmtIF(ctx, tc);
    case TT_ELSE:  /* else */
        break;
    case TT_WHILE: 
        return new_StmtWHILE(ctx, tc);
    case TT_DO: 
        return new_StmtDO(ctx, tc);
    case TT_FOR: 
        return new_StmtFOR(ctx, tc);
    case TT_FOREACH: 
        return new_StmtFOREACH(ctx, tc);
    case TT_FROM:  /* from */
        break;
    case TT_WHERE:  /* where */
        break;
    case TT_BREAK: 
        return new_StmtBREAK(ctx, tc);
    case TT_CONTINUE: 
        return new_StmtCONTINUE(ctx, tc);
    case TT_GOTO: 
        return new_StmtGOTO(ctx, tc);
    case TT_TRY: 
        return new_StmtTRY(ctx, tc);
    case TT_CATCH:  /* catch */
        break;
    case TT_FINALLY:  /* finally */
        break;
    case TT_THROW: 
        return new_StmtTHROW(ctx, tc);
    case TT_PRINT: 
        return new_StmtPRINT(ctx, tc);
    case TT_ASSERT: 
        return new_StmtASSERT(ctx, tc);
    case TT_BRACE:  /* BRACE */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_PARENTHESIS:  /* PARENTHESIS */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_BRANCET:  /* BRANCET */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_DOTS:  /* DOTS */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_SEMICOLON:
        return new_StmtDONE(ctx);
    case TT_COMMA:  /* COMMA */
        break;
    case TT_LET:  /* LET */
        break;
    case TT_LSHIFTE:  /* lshifte */
        break;
    case TT_RSHIFTE:  /* rshifte */
        break;
    case TT_ADDE:  /* adde */
        break;
    case TT_SUBE:  /* sube */
        break;
    case TT_MULE:  /* mule */
        break;
    case TT_DIVE:  /* dive */
        break;
    case TT_MODE:  /* mode */
        break;
    case TT_BITORE:  /* bitore */
        break;
    case TT_BITANDE:  /* bitande */
        break;
    case TT_ALTLET:  /* ALTLET */
        break;
    case TT_QUESTION:
        return new_StmtMAN(ctx, tc);
    case TT_SUBSET:  /* SUBSET */
        break;
    case TT_SLICE:  /* SLICE */
        break;
    case TT_OFFSET:  /* OFFSET */
        break;
    case TT_COLON:  /* COLON */
        break;
    case TT_OR:  /* OR */
        break;
    case TT_AND:  /* AND */
        break;
    case TT_NOT:  /* Not */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_INSTANCEOF:  /* Instanceof */
        break;
    case TT_ISA:  /* Isa */
        break;
    case TT_AS:  /* As */
        break;
    case TT_IN:  /* In */
        break;
    case TT_IS:  /* Is */
        break;
    case TT_TO:  /* To */
        break;
    case TT_EQ:  /* Eq */
        break;
    case TT_NEQ:  /* Neq */
        break;
    case TT_LT:  /* Lt */
        break;
    case TT_LTE:  /* Lte */
        break;
    case TT_GT:  /* Gt */
        break;
    case TT_GTE:  /* Gte */
        break;
    case TT_LSHIFT:  /* LShift */
        break;
    case TT_RSHIFT:  /* RShift */
        break;
    case TT_ADD:  /* Add */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_SUB:  /* Sub */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_DIV:  /* Div */
        break;
    case TT_MUL:  /* Mul */
        break;
    case TT_LOGICALOR:  /* LogicalOr */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_LOGICALAND:  /* LogicalAnd */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_ALT:  /* ALT */
        break;
    case TT_LOGICALNOT:  /* LogicalNot */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_LOGICALXOR:  /* LogicalXor */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_NEXT:  /* Next */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_PREV:  /* Prev */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_MOD:  /* Mod */
        break;
    case TT_NUM:  /* NUM */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_STR:  /* STR */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_TSTR:  /* TSTR */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_FMTSTR:  /* FMTSTR */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_LABEL: 
        goto L_TAIL;
    case TT_METAN: 
        if(DP(tkc)->tt_next == TT_PARENTHESIS) {
            tc->c += 1;
        };
        goto L_TAIL;
    case TT_PROPN:  /* PROPN */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_URN:  /* URN */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_MT:  /* MT */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_CONSTN:  /* CONSTN */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_TYPEN:  /* TYPEN */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_CMETHODN:  /* CMETHODN */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_NAME:  /* NAME */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_MN:  /* MN */
        break;
    case TT_FN:  /* FN */
        break;
    case TT_CID:  /* CID */
        break;
    case TT_CONST:  /* CONST */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_MTDMPR:  /* MTDMPR */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_EBPIDX:  /* EBPIDX */
        break;
    case TT_SFPIDX:  /* SFPIDX */
        break;
    case TT_FLDIDX:  /* FLDIDX */
        break;
    case TT_OBJIDX:  /* OBJIDX */
        break;
    case TT_SYSCONST:  /* SYSCONST */
        break;
    case TT_ASIS:  /* ASIS */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);
    case TT_ERR:
        /* no error message */
        return new_StmtERR(ctx, tc);
    case TT_EOT:  /* EOT */
        break;
    }
    knh_Token_perror(ctx, tkc, KMSG_TSTMT1);
    return new_StmtERR(ctx, tc);
}

#define knh_StmtEXPR_decl knh_StmtDONE_decl
#define knh_StmtEXPR_name knh_StmtDONE_name
void knh_StmtEXPR_cmpl(Ctx *ctx, Stmt *stmt, Compiler *cpr, NameSpace *ns, knh_type_t reqt, int level);

static
void knh_StmtDONE_decl(Ctx *ctx, Stmt *stmt, Compiler *cpr, NameSpace *ns, int level)
{

}

static
void knh_StmtDONE_name(Ctx *ctx, Stmt *stmt, Compiler *cpr, NameSpace *ns, int level)
{

}

static
void knh_StmtDONE_cmpl(Ctx *ctx, Stmt *stmt, Compiler *cpr, NameSpace *ns, knh_type_t reqt, int level)
{

}

static int knh_stmt_array_isExpr[] = {
    0,  /* done */ 
    0,  /* namespace */ 
    0,  /* import */ 
    0,  /* pragma */ 
    0,  /* using */ 
    0,  /* using import */ 
    0,  /* using alias */ 
    0,  /* using unit */ 
    0,  /* using enum */ 
    0,  /* using vocab */ 
    0,  /* with */ 
    0,  /* using func */ 
    0,  /* using mapmap */ 
    0,  /* class */ 
    0,  /* extends */ 
    0,  /* implements */ 
    0,  /* method */ 
    0,  /* closure */ 
    0,  /* format */ 
    0,  /* decl */ 
    0,  /* return */ 
    0,  /* mapmap */ 
    0,  /* weave */ 
    0,  /* aspect */ 
    0,  /* if */ 
    0,  /* else */ 
    0,  /* while */ 
    0,  /* do */ 
    0,  /* for */ 
    0,  /* foreach */ 
    0,  /* from */ 
    0,  /* where */ 
    0,  /* break */ 
    0,  /* continue */ 
    0,  /* goto */ 
    0,  /* try */ 
    0,  /* catch */ 
    0,  /* finally */ 
    0,  /* throw */ 
    0,  /* err */ 
    0,  /* let */ 
    0,  /* letmulti */ 
    1,  /* new */ 
    1,  /* mapcast */ 
    1,  /* call */ 
    1,  /* call1 */ 
    1,  /* pcall */ 
    1,  /* mt */ 
    1,  /* op */ 
    1,  /* trinary */ 
    1,  /* alt */ 
    1,  /* and */ 
    1,  /* or */ 
    0,  /* print */ 
    0,  /* assert */ 
    0,  /* man */ 
    //(int)0
};

int knh_stmt_isExpr(knh_stmt_t t)
{
    DEBUG_ASSERT(t < KNH_STMT_MAXSIZ);
    return knh_stmt_array_isExpr[t];
}

/* ------------------------------------------------------------------------ */

static f_visitdecl knh_stmt_array_decl[] = {
    knh_StmtDONE_decl,  /* done */ 
    knh_StmtDONE_decl,  /* namespace */ 
    knh_StmtIMPORT_decl,  /* import */ 
    knh_StmtDONE_decl,  /* pragma */ 
    knh_StmtDONE_decl,  /* using */ 
    knh_StmtUIMPORT_decl,  /* using import */ 
    knh_StmtUALIAS_decl,  /* using alias */ 
    knh_StmtUUNIT_decl,  /* using unit */ 
    knh_StmtUENUM_decl,  /* using enum */ 
    knh_StmtUVOCAB_decl,  /* using vocab */ 
    knh_StmtDONE_decl,  /* with */ 
    knh_StmtUFUNC_decl,  /* using func */ 
    knh_StmtUMAPMAP_decl,  /* using mapmap */ 
    knh_StmtCLASS_decl,  /* class */ 
    knh_StmtDONE_decl,  /* extends */ 
    knh_StmtDONE_decl,  /* implements */ 
    knh_StmtDONE_decl,  /* method */ 
    knh_StmtDONE_decl,  /* closure */ 
    knh_StmtDONE_decl,  /* format */ 
    knh_StmtDONE_decl,  /* decl */ 
    knh_StmtDONE_decl,  /* return */ 
    knh_StmtDONE_decl,  /* mapmap */ 
    knh_StmtDONE_decl,  /* weave */ 
    knh_StmtDONE_decl,  /* aspect */ 
    knh_StmtDONE_decl,  /* if */ 
    knh_StmtDONE_decl,  /* else */ 
    knh_StmtDONE_decl,  /* while */ 
    knh_StmtDONE_decl,  /* do */ 
    knh_StmtDONE_decl,  /* for */ 
    knh_StmtDONE_decl,  /* foreach */ 
    knh_StmtDONE_decl,  /* from */ 
    knh_StmtDONE_decl,  /* where */ 
    knh_StmtDONE_decl,  /* break */ 
    knh_StmtDONE_decl,  /* continue */ 
    knh_StmtDONE_decl,  /* goto */ 
    knh_StmtDONE_decl,  /* try */ 
    knh_StmtDONE_decl,  /* catch */ 
    knh_StmtDONE_decl,  /* finally */ 
    knh_StmtDONE_decl,  /* throw */ 
    knh_StmtDONE_decl,  /* err */ 
    knh_StmtDONE_decl,  /* let */ 
    knh_StmtDONE_decl,  /* letmulti */ 
    knh_StmtDONE_decl,  /* new */ 
    knh_StmtDONE_decl,  /* mapcast */ 
    knh_StmtDONE_decl,  /* call */ 
    knh_StmtDONE_decl,  /* call1 */ 
    knh_StmtDONE_decl,  /* pcall */ 
    knh_StmtDONE_decl,  /* mt */ 
    knh_StmtDONE_decl,  /* op */ 
    knh_StmtDONE_decl,  /* trinary */ 
    knh_StmtDONE_decl,  /* alt */ 
    knh_StmtDONE_decl,  /* and */ 
    knh_StmtDONE_decl,  /* or */ 
    knh_StmtDONE_decl,  /* print */ 
    knh_StmtDONE_decl,  /* assert */ 
    knh_StmtDONE_decl,  /* man */ 
    //(f_visitdecl)0
};

f_visitdecl knh_stmt_decl(knh_stmt_t t)
{
    DEBUG_ASSERT(t < KNH_STMT_MAXSIZ);
    return knh_stmt_array_decl[t];
}

/* ------------------------------------------------------------------------ */

static f_visitname knh_stmt_array_name[] = {
    knh_StmtDONE_name,  /* done */ 
    knh_StmtDONE_name,  /* namespace */ 
    knh_StmtDONE_name,  /* import */ 
    knh_StmtDONE_name,  /* pragma */ 
    knh_StmtDONE_name,  /* using */ 
    knh_StmtDONE_name,  /* using import */ 
    knh_StmtDONE_name,  /* using alias */ 
    knh_StmtDONE_name,  /* using unit */ 
    knh_StmtDONE_name,  /* using enum */ 
    knh_StmtDONE_name,  /* using vocab */ 
    knh_StmtDONE_name,  /* with */ 
    knh_StmtDONE_name,  /* using func */ 
    knh_StmtDONE_name,  /* using mapmap */ 
    knh_StmtCLASS_name,  /* class */ 
    knh_StmtDONE_name,  /* extends */ 
    knh_StmtDONE_name,  /* implements */ 
    knh_StmtMETHOD_name,  /* method */ 
    knh_StmtDONE_name,  /* closure */ 
    knh_StmtFORMAT_name,  /* format */ 
    knh_StmtDECL_name,  /* decl */ 
    knh_StmtDONE_name,  /* return */ 
    knh_StmtDONE_name,  /* mapmap */ 
    knh_StmtDONE_name,  /* weave */ 
    knh_StmtDONE_name,  /* aspect */ 
    knh_StmtIF_name,  /* if */ 
    knh_StmtDONE_name,  /* else */ 
    knh_StmtWHILE_name,  /* while */ 
    knh_StmtDO_name,  /* do */ 
    knh_StmtFOR_name,  /* for */ 
    knh_StmtFOREACH_name,  /* foreach */ 
    knh_StmtDONE_name,  /* from */ 
    knh_StmtDONE_name,  /* where */ 
    knh_StmtDONE_name,  /* break */ 
    knh_StmtDONE_name,  /* continue */ 
    knh_StmtDONE_name,  /* goto */ 
    knh_StmtDONE_name,  /* try */ 
    knh_StmtDONE_name,  /* catch */ 
    knh_StmtDONE_name,  /* finally */ 
    knh_StmtDONE_name,  /* throw */ 
    knh_StmtDONE_name,  /* err */ 
    knh_StmtLET_name,  /* let */ 
    knh_StmtDONE_name,  /* letmulti */ 
    knh_StmtDONE_name,  /* new */ 
    knh_StmtDONE_name,  /* mapcast */ 
    knh_StmtDONE_name,  /* call */ 
    knh_StmtDONE_name,  /* call1 */ 
    knh_StmtDONE_name,  /* pcall */ 
    knh_StmtDONE_name,  /* mt */ 
    knh_StmtDONE_name,  /* op */ 
    knh_StmtDONE_name,  /* trinary */ 
    knh_StmtDONE_name,  /* alt */ 
    knh_StmtDONE_name,  /* and */ 
    knh_StmtDONE_name,  /* or */ 
    knh_StmtDONE_name,  /* print */ 
    knh_StmtDONE_name,  /* assert */ 
    knh_StmtDONE_name,  /* man */ 
    //(f_visitname)0
};

f_visitname knh_stmt_name(knh_stmt_t t)
{
    DEBUG_ASSERT(t < KNH_STMT_MAXSIZ);
    return knh_stmt_array_name[t];
}

/* ------------------------------------------------------------------------ */

static f_visitcmpl knh_stmt_array_cmpl[] = {
    knh_StmtDONE_cmpl,  /* done */ 
    knh_StmtDONE_cmpl,  /* namespace */ 
    knh_StmtDONE_cmpl,  /* import */ 
    knh_StmtDONE_cmpl,  /* pragma */ 
    knh_StmtDONE_cmpl,  /* using */ 
    knh_StmtDONE_cmpl,  /* using import */ 
    knh_StmtDONE_cmpl,  /* using alias */ 
    knh_StmtDONE_cmpl,  /* using unit */ 
    knh_StmtDONE_cmpl,  /* using enum */ 
    knh_StmtDONE_cmpl,  /* using vocab */ 
    knh_StmtDONE_cmpl,  /* with */ 
    knh_StmtDONE_cmpl,  /* using func */ 
    knh_StmtDONE_cmpl,  /* using mapmap */ 
    knh_StmtCLASS_cmpl,  /* class */ 
    knh_StmtDONE_cmpl,  /* extends */ 
    knh_StmtDONE_cmpl,  /* implements */ 
    knh_StmtMETHOD_cmpl,  /* method */ 
    knh_StmtDONE_cmpl,  /* closure */ 
    knh_StmtFORMAT_cmpl,  /* format */ 
    knh_StmtDONE_cmpl,  /* decl */ 
    knh_StmtRETURN_cmpl,  /* return */ 
    knh_StmtDONE_cmpl,  /* mapmap */ 
    knh_StmtDONE_cmpl,  /* weave */ 
    knh_StmtDONE_cmpl,  /* aspect */ 
    knh_StmtIF_cmpl,  /* if */ 
    knh_StmtDONE_cmpl,  /* else */ 
    knh_StmtWHILE_cmpl,  /* while */ 
    knh_StmtDO_cmpl,  /* do */ 
    knh_StmtFOR_cmpl,  /* for */ 
    knh_StmtFOREACH_cmpl,  /* foreach */ 
    knh_StmtDONE_cmpl,  /* from */ 
    knh_StmtDONE_cmpl,  /* where */ 
    knh_StmtBREAK_cmpl,  /* break */ 
    knh_StmtCONTINUE_cmpl,  /* continue */ 
    knh_StmtGOTO_cmpl,  /* goto */ 
    knh_StmtDONE_cmpl,  /* try */ 
    knh_StmtDONE_cmpl,  /* catch */ 
    knh_StmtDONE_cmpl,  /* finally */ 
    knh_StmtDONE_cmpl,  /* throw */ 
    knh_StmtERR_cmpl,  /* err */ 
    knh_StmtLET_cmpl,  /* let */ 
    knh_StmtDONE_cmpl,  /* letmulti */ 
    knh_StmtNEW_cmpl,  /* new */ 
    knh_StmtMAPCAST_cmpl,  /* mapcast */ 
    knh_StmtCALL_cmpl,  /* call */ 
    knh_StmtCALL1_cmpl,  /* call1 */ 
    knh_StmtDONE_cmpl,  /* pcall */ 
    knh_StmtMT_cmpl,  /* mt */ 
    knh_StmtOP_cmpl,  /* op */ 
    knh_StmtTRINARY_cmpl,  /* trinary */ 
    knh_StmtALT_cmpl,  /* alt */ 
    knh_StmtAND_cmpl,  /* and */ 
    knh_StmtOR_cmpl,  /* or */ 
    knh_StmtPRINT_cmpl,  /* print */ 
    knh_StmtDONE_cmpl,  /* assert */ 
    knh_StmtDONE_cmpl,  /* man */ 
    //(f_visitcmpl)0
};

f_visitcmpl knh_stmt_cmpl(knh_stmt_t t)
{
    DEBUG_ASSERT(t < KNH_STMT_MAXSIZ);
    return knh_stmt_array_cmpl[t];
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
