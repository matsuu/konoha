#!/usr/bin/python
import os, sys
from pygenlib import *

CPROTO = []

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------
# ----------------------------------------------------------------------------

TT = [
  ["namespace", "", 'keyword stmt stage1', 
     ['namespace', '$NAME', ';'],
  ],
  ["include", "", 'keyword stmt stage1', 
     ['include', '$ANY', ';'],
  ],
  ["using", "", 'keyword stmt stage1', 
#     ['using', '?using_option', '$CLASSQN', '$URN', ';'],
  ],
  ["weave", "", 'keyword stmt stage1',
     ['weave', '$ANY', '$ANY', ';'],
  ],
  ["class", "", 'keyword stmt stage1 stage2', 
   ['class', '$CLASSN', '?extends', '$CLASSN', '?implements', '{']
  ],
  ["extends", "", 'keyword + nothead'],
  ["implements", "", 'keyword + nothead'],
  ["if", "", 'keyword stmt', [
    'if', '(expr)', '{stmt}', '?else', '{stmt}'
  ]],
  ["else", "", 'keyword + nothead' ],
  
  ["try", "", 'keyword stmt', None, [
    'try', '{', '?catch', '?finally', '{'
  ]],  
  ["catch", "", 'keyword nothead' ],
  ["finally", "", 'keyword + nothead', ],

  ["do", "", 'keyword stmt', [
    'do', '{', 'while', '(expr)', ';' 
  ]],
  ["while", "", 'keyword stmt +do', [
    'while', '(expr)', '{stmt}', 
  ]],
  
  ["for", "", 'keyword stmt', [
    'for', '(stmt3)', '{stmt}', 
  ]],
  
  ["foreach", "", 'keyword stmt', 
    ['foreach', '(fromwhere)', '{stmt}']
  ],
  
  ["from", "", 'keyword + nothead'],
  ["where", "", 'keyword + nothead'],

  ["continue", "", 'stmt keyword', [
    'continue', '?ANY', ';'
  ]],
  ["break", "", 'stmt keyword', [
    'break', '?ANY', ';'
  ]],
  ["goto", "", 'stmt keyword', [
    'goto', '$ANY', ';'
  ]],
  ["throw", "", 'stmt keyword', [
    'throw', 'expr', ';'
  ]],
  ["return", "", 'stmt keyword', [
    'return', ';expr', ';'
  ]],
  ["eval", "", 'keyword stmt',
     ['eval', 'expr', ';'],
  ],
  ["assert", "", 'stmt keyword', [
    'assert', '(expr)', ';'
  ]],
  ["print", "", 'stmt keyword', [
    'print', 'expr...', ';',
  ]],

  ["help", "", 'stmt keyword', [
    'help', '?ANY', ';',
  ]],

  ["{", "_BRACE", 'Array inexpr value', None],
  ["(", '_PARENTHESIS', 'Array inexpr value', None],
  ["[", '_BRANCET', 'Array inexpr value', None],

  ["...", '_DOTS', 'tk eval value 2 nothead inexpr'], 
  [";", '_SEMICOLON', '', None],
  [",", '_COMMA', 'nothead inexpr', None],
  
#  ["|=", 'bitore',  'tk assign nothead'],
#  ["&=", 'bitande', 'tk assign nothead'],
  ["=", '_LET', 'tk asm eval 2 nothead'],
  
  ["<<=", 'lshifte',  'tk assign nothead'],
  [">>=", 'rshifte', 'tk assign nothead'],
  ["+=", 'adde','tk assign nothead'],
  ["-=", 'sube','tk assign nothead'],
  ["*=", 'mule','tk assign nothead'],
  ["/=", 'dive','tk assign nothead'],
  ["%=", 'mode','tk assign nothead'],
  ["|=", 'bitore',  'tk assign nothead'],
  ["&=", 'bitande', 'tk assign nothead'],
  ["?\\?=", '_ALTLET', 'tk asm eval 2 nothead'],  #trigraph ?

  ["?", '_QUESTION', 'tk asm eval 3 inexpr'],
  ["..", '_SUBSET', 'tk eval value 2 nothead inexpr'], 
  ["..<", '_SLICE', 'tk eval value 2 nothead inexpr'], 
  ["..+", '_OFFSET', 'tk eval value 2 nothead inexpr'], 
  [":",   '_COLON', 'tk eval value 2 nothead inexpr'],
  [":<",  '_PSLICE', 'tk eval value 2 nothead inexpr'], 
  [":+",  '_POFFSET', 'tk eval value 2 nothead inexpr'], 

  ["||",  '_OR', 'tk asm eval value 2+ nothead inexpr'],
  ["&&", '_AND', 'tk asm eval value 2+ inexpr'],
  ["not", 'Not', 'expr eval value top 1 inexpr'],

  ["instanceof", 'Instanceof', 'tk expr eval value 2 nothead inexpr'],
#  ["is",  'Is', 'tk expr eval value 2 nothead inexpr'],
  ["in",  'In', 'tk expr eval value 2 nothead inexpr'],

  ["===",'Seq', 'tk expr eval value 2 nothead inexpr'],
  ["-->",'IsMapTo', 'tk expr eval value 2 nothead inexpr'],

  ["==",'Eq', 'tk expr eval value 2 nothead inexpr'],
  ["!=",'Neq', 'tk expr eval value 2 nothead inexpr'],
  ["<", 'Lt', 'tk expr eval value 2 nothead inexpr'],
  ["<=",'Lte', 'tk expr eval value 2 nothead inexpr'],
  [">", 'Gt', 'tk expr eval value 2 nothead inexpr'],
  [">=",'Gte', 'tk expr eval value 2 nothead inexpr'],

#  ["|",  'BitOr',  'tk expr eval value 2+ inexpr'],
#  ["&",  'BitAnd', 'tk expr eval value 2+ inexpr'],
  ["<<", 'LShift',  'tk expr eval value 2 nothead inexpr'],
  [">>", 'RShift',  'tk expr eval value 2 nothead inexpr'],
  ["+",  'Add', 'tk expr eval value 2+ nothead inexpr'],
  ["-",  'Sub', 'tk expr eval value 2+ nothead inexpr'],
  ["%",  'Mod', 'expr eval value 2 nothead inexpr'],
  ["/",  'Div', 'expr eval value 2+ nothead inexpr'],
  ["*",  'Mul', 'tk expr eval value 2+ nothead inexpr'],
  ["|",  'LogicalOr',  'tk expr eval value 2+ inexpr'],
  ["&",  'LogicalAnd', 'tk expr eval value 2+ inexpr'],
  ["?\\?",  '_ALT', 'tk asm eval value nothead inexpr'], #trigraph ?

  ["~",  'LogicalNot', 'tk expr eval value top 1 inexpr'],
  ["^",  'LogicalXor', 'tk expr eval value top 1 inexpr'],
  ["++", '_NEXT', 'tk expr eval value 1 inexpr'],
  ["--", '_PREV', 'tk expr eval value 1 inexpr'],
  ["#",  '_SHARP', 'tk expr eval value 1 inexpr'],
  
  ["_", '_ASIS', 'expr svalue inexpr', None],

  ["", '_NUM', 'expr svalue String inexpr'],
  ["", '_STR', 'expr svalue String inexpr'],
  ["", '_QSTR', 'expr svalue String inexpr'],
  ["", '_FMTSTR', 'expr svalue String inexpr'],

  ["", '_LABEL', 'expr String'],
  ["", '_METAN', 'expr String'],
  ["", '_PROPN', 'expr String inexpr'],
  ["", '_URN', 'expr svalue String inexpr'],
  ["", '_MOVTEXT', 'expr String inexpr'],
  ["", '_CONSTN', 'expr svalue String inexpr'],
  ["", '_TYPEN', 'expr svalue String inexpr'],
  ["", '_NAME', 'expr String inexpr'],
  ["", '_RAW', 'expr svalue Any inexpr'],
  ["", '_ERR', 'String nothead'],
#  ["", '_DONE', ''],
]

#------------------------------------------------------------------------------

TT_IS = [
 ('isNested', 'Array'),
 ('isKeyword', 'keyword'),
 ('isStatement', 'stmt'),
 ('isInExpr', 'inexpr'),
 ('isNotFirst', 'nothead'),
]

#------------------------------------------------------------------------------

NAKNH_OBJ = [
    ['int:',   'TT_TYPEN'],
    ['float:', 'TT_TYPEN'],
    ['long:',  'TT_TYPEN'],
]

#------------------------------------------------------------------------------

ALIAS = [
    [':=', '=:'],
    ['and', '&&'],
    ['or',  '||'],
    ['!',  'not'],

    ['public',  '@Public'], 
    ['private', '@Private'], 
    ['final',   '@Final'], 
    ['static',  '@Static'], 
    ['const',   '@Const'], 
    ['virtual', '@Virtual'],
    ['mod', '%'],
    ['int', 'Int!'],
    ['long', 'Int64!'],
    ['float', 'Float!'],
    ['double', 'Float!'],
    ['boolean', 'Bool!'],
    ['function', 'any'],
    ['?\\?\\?',  'help'],
]

def make_aliasdb2():
    for a in ALIAS:
        fc = a[0][0]
        func = ''
        if ALIASDB.has_key(fc):
            func = ALIASDB[fc]
        func += '''
            if(ISB(t, "%s")) {
                return new_Token__parse(ctx, flag, fname, fln, STEXT("%s"));
            } ''' % (a[0], a[1])
        ALIASDB[fc] = func
    #print ALIASDB

#------------------------------------------------------------------------------

#------------------------------------------------------------------------------

class Token:
    def __init__(self, ll):
        self.name = ll[0].replace(':*', '')
        self.qname = self.name
        if self.qname == '\\': self.qname = '\\' + self.qname
        self.token = ll[0]
        self.tt = 'TT_%s' % ll[1].upper()
        if ll[1] == '' and len(self.name) > 0 : self.tt = 'TT_%s' % self.name.upper()
        if ll[1].startswith('_') : self.tt = 'TT%s' % ll[1].upper()
        self.opFunc = None
        if ll[1] != '' and ll[1][0].isupper(): self.opFunc = 'op%s' % ll[1]
        self.options = ll[2]
        self.op = ll[2].lower()
        self.grammar = None
        if len(ll) > 3: self.grammar = ll[3]
        self.isname = self.tt.replace('TT_', 'is')
        self.L_ERR = False

    def isf(self, t):
        if self.op.find(t.lower()) != -1: return True
        return False

#------------------------------------------------------------------------------

TT_LIST = []
TT_MAP  = {}

ALIASDB = {}
NAMEDB  = {}

for tt in TT:
    tk = Token(tt)
    TT_LIST.append(tk)
    TT_MAP[tk.name] = tk
make_aliasdb2()

#------------------------------------------------------------------------------

def write_token_h(f):
    write_chapter(f, 'TT_MACRO knh_token_t')
    write_define(f, 'TT_UKNOWN',  '0', 40)
    DC = {}
    tn = 1        
    for tk in TT_LIST:
        if DC.has_key(tk.tt): continue
        write_define(f, tk.tt, '((knh_token_t)%d)' % tn, 40)
        if tk.opFunc != None:
            write_ifndef(f, 'METHODN_%s' % tk.opFunc, 'METHODN_NONAME', 40)
        DC[tk.tt] = tk
        tn += 1

    write_line(f)

#------------------------------------------------------------------------------

def write_token(f):
    write_chapter(f, '[token]')
    for kp in TT_IS:
        write_token_is(f, kp[0], kp[1])
    
    CPROTO.append('char* knh_token_tochar(knh_token_t tt);')
    f.write('''
char* knh_token_tochar(knh_token_t tt)
{
    switch(tt) {''')
    DC = {}
    for tk in TT_LIST:
        if DC.has_key(tk.tt): continue
        DC[tk.tt] = tk
        text = tk.name
        if text == '' : text = tk.tt
        f.write('''
    case %s: return "%s";''' % (tk.tt, text))
    f.write('''
    }
    return "TT_UKNOWN";
}
''')
    write_line(f)
    
    CPROTO.append('knh_methodn_t knh_token_tomethodn(knh_token_t tt);')
    f.write('''
knh_methodn_t knh_token_tomethodn(knh_token_t tt)
{
    switch(tt) {''')
    DC = {}
    for tk in TT_LIST:
        if tk.opFunc is None: continue
        if DC.has_key(tk.tt): continue
        DC[tk.tt] = tk
        f.write('''
    case %s: return METHODN_%s;''' % (tk.tt, tk.opFunc))
    f.write('''
    }
    return METHODN_NONAME;
}
''')
    write_line(f)


    CPROTO.append('knh_bool_t knh_Token_isOP(Token *b);')
    f.write('''
INLINE
knh_bool_t knh_Token_isOP(Token *b)
{
    return (knh_token_tomethodn(b->tt) != METHODN_NONAME);
}
''')
    write_line(f)

    CPROTO.append('knh_bool_t knh_methodn_isOperator(knh_methodn_t mn);')
    f.write('''
knh_bool_t knh_methodn_isOperator(knh_methodn_t mn)
{
    switch(mn) {''')
    DC = {}
    for tk in TT_LIST:
        if tk.opFunc is None: continue
        if DC.has_key(tk.tt): continue
        DC[tk.tt] = tk
        f.write('''
    case METHODN_%s: return 1;''' % (tk.opFunc))
    f.write('''
    }
    return 0;
}
''')
    write_line(f)

    CPROTO.append('char *knh_methodop_tochar(knh_methodn_t mn);')
    f.write('''
char *knh_methodop_tochar(knh_methodn_t mn)
{
    switch(mn) {''')
    DC = {}
    for tk in TT_LIST:
        if tk.opFunc is None: continue
        if DC.has_key(tk.tt): continue
        DC[tk.tt] = tk
        f.write('''
    case METHODN_%s: return "%s";''' % (tk.opFunc, tk.name))
    f.write('''
    }
    DEBUG_ASSERT(mn == 0); /* this cann't happen */
    DEBUG_ASSERT(mn == 1); /* this cann't happen */
    return "";
}
''')
    write_line(f)
    

    CPROTO.append('Token *new_Token__parse(Ctx *ctx, knh_flag_t flag, knh_filen_t filen, knh_line_t fln, knh_bytes_t t);')
    f.write('''
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
    switch(t.buf[0]) {''')

    DC = {}
    for tk in TT_LIST:
        if tk.name == '': continue
        if not DC.has_key(tk.name[0]):
            DC[tk.name[0]] = []
        DC[tk.name[0]].append(tk)

    fcl = DC.keys()
    fcl.sort()
    al = ALIASDB.keys()
    al.sort()
    #print al
    for fc in fcl:
        f.write('''
        case '%s':''' % fc)
        if ALIASDB.has_key(fc):
        	f.write(ALIASDB[fc])
        	al.remove(fc)
        for tk in DC[fc]:
            f.write('''
            if(ISB(t, "%s")) {
                return new_Token(ctx, flag, fname, fln, t, %s);
            }''' % (tk.qname, tk.tt));
        f.write('''
        break;''')
    #print al
    for fc in al:
        f.write('''
        case '%s':''' % fc)
        if ALIASDB.has_key(fc):
        	f.write(ALIASDB[fc])
        f.write('''
        break;''')

    f.write('''
    }''')
    for tk in TT_LIST:
        if tk.name != '': continue
        if tk.isname == 'isLABEL': 
            f.write('''
    if(t.len > KONOHA_NAME_SIZE - 1) {
        return new_Token(ctx, flag, fname, fln, t, TT_ERR);
    }''')
        if tk.isname == 'isRAW': break
        f.write('''
    if(knh_bytes_%s(t)) {
            return new_Token(ctx, flag, fname, fln, t, %s);
    }''' % (tk.isname, tk.tt))
    f.write('''
    DEBUG("unknown: %s", t.buf);
    return new_Token(ctx, flag, fname, fln, t, TT_ERR);
}
''')

def write_token_is(f, funcn, cond):
    CPROTO.append('knh_bool_t knh_token_%s(knh_token_t tt);' % funcn)
    f.write('''
knh_bool_t knh_token_%s(knh_token_t tt)
{
    switch(tt) {''' % funcn)
    DC = {}
    for tk in TT_LIST:
        if DC.has_key(tk.tt): continue
        DC[tk.tt] = tk
        if tk.isf(cond):
            f.write('''
    case %s: return 1;''' % tk.tt)
    f.write('''
    }
    return 0;
}
''')
    write_line(f)

#------------------------------------------------------------------------------
# grammar
#------------------------------------------------------------------------------


GRAMMAR = {
    'expr':'''
    /* expr */
    if(*cp < e && knh_Token_isFirstExpr(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, new_Term__expr(ctx, ts, *cp, knh_tokens_lastexpr(ts, *cp, e), KNH_STT_RVALUE));
        *cp = knh_tokens_nextstmt(ts, *cp, e);
        goto L_$NEXT;
    }
    else {
        KNH_GOTO(L_ERR);
    }''',

    ';expr': '''
    /* ;expr */
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    if(*cp < e && knh_Token_isFirstExpr(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, new_Term__expr(ctx, ts, *cp, knh_tokens_lastexpr(ts, *cp, e), KNH_STT_RVALUE));
        *cp = knh_tokens_nextstmt(ts, *cp, e);
        goto L_$NEXT;
    }
    else {
        KNH_GOTO(L_ERR);
    }''',

    '(expr)': '''
    /* (expr) */
    if(*cp < e && ts[*cp]->tt == TT_PARENTHESIS) {
        knh_Stmt_terms_add(ctx, b, new_Term__pexpr(ctx, ts[*cp]));
        *cp += 1;
        goto L_$NEXT;
    }
    else {
        KNH_GOTO(L_ERR);
    }''',

    'expr...': '''
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
    }''',
 
    '{': '''
    /* { */
    if(*cp < e && ts[*cp]->tt == TT_BRACE) {
        knh_Stmt_terms_add(ctx, b, new_Stmt__block(ctx, knh_Token_ts(ts[*cp]), 0, knh_Token_tokens_size(ts[*cp])));
        knh_Token_tokens_empty(ctx, ts[*cp]);
        *cp += 1;
        goto L_$NEXT;
    }
    else {
        KNH_GOTO(L_ERR);
    }''',

    '{stmt}': '''
    /* {stmt} */
    if(*cp < e) {
        if(ts[*cp]->tt == TT_BRACE) {
            knh_Stmt_terms_add(ctx, b, new_Stmt__block(ctx, knh_Token_ts(ts[*cp]), 0, knh_Token_tokens_size(ts[*cp])));
            knh_Token_tokens_empty(ctx, ts[*cp]);
            *cp += 1;
            goto L_$NEXT;
        }
        if(ts[*cp]->tt == TT_SEMICOLON) {
            knh_Stmt_terms_add(ctx, b, new_Stmt(ctx, 0, STT_DONE));
            *cp += 1;
            goto L_$NEXT;
        }
        knh_Stmt_terms_add(ctx, b, new_Stmt__stmt1(ctx, ts, *cp, e, cp));
        goto L_$NEXT;
    }
    else {
        KNH_GOTO(L_ERR);
    }''',

    '(stmt3)': '''
    /* (stmt3) */
    if(*cp < e && ts[*cp]->tt == TT_PARENTHESIS) {
        knh_Stmt_add_stmt3(ctx, b, ts[*cp]);
        knh_Token_tokens_empty(ctx, ts[*cp]);
        *cp += 1;
        goto L_$NEXT;
    }
    else {
        KNH_GOTO(L_ERR);
    }''',

    '(fromwhere)': '''
    /* (fromwhere) */
    if(*cp < e && ts[*cp]->tt == TT_PARENTHESIS) {
        knh_Stmt_add_fromwhere(ctx, b, ts[*cp]);
        knh_Token_tokens_empty(ctx, ts[*cp]);
        *cp += 1;
        goto L_$NEXT;
    }
    else {
        KNH_GOTO(L_ERR);
    }''',

    ';': '''
    /* ; */
    if(*cp < e && ts[*cp]->tt == TT_SEMICOLON) {
        *cp += 1;
        return b;
    }
    else {
        //MC_EPRINT(ctx, ts[*cp-1], MC_NOTICE, "; required");
        return b;
    }''',

############################################################################

    '$T': '''
    /* $T */
    if(*cp < e && knh_Token_is$T(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, ts[*cp]);
        *cp += 1;
        goto L_$NEXT;
    }
    else {
        KNH_GOTO(L_ERR);
    }''',

    'TT': '''
    /* TT */
    if(*cp < e && ts[*cp]->tt == TT) {
        knh_Stmt_terms_add(ctx, b, ts[*cp]);
        *cp += 1;
        goto L_$NEXT;
    }
    else {
        KNH_GOTO(L_ERR);
    }''',

############################################################################

    '?using_option': '''
    /* ?using_option */
    if(*cp < e && knh_Token_isUsingOption(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, ts[*cp]);
        *cp += 1;
        goto L_$NEXT;
    }
    else {
        knh_Stmt_terms_add(ctx, b, new_Token__text(ctx, ts[*cp-1], STEXT("import")));
        goto L_3;
    }''',

    '?extends': '''
    /* ?extends */
    if(*cp < e && ts[*cp]->tt == TT_EXTENDS) {
        *cp += 1;
        goto L_$NEXT;
    }
    else {
        knh_Stmt_terms_add(ctx, b, new_Token__text(ctx, ts[*cp-1], STEXT("Object")));
        goto L_4;
    }''',

    '?implements': '''
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
        goto L_$NEXT;
    }
    else {
        knh_Stmt_terms_add(ctx, b, new_Stmt(ctx, 0, STT_DONE));
        goto L_$NEXT;
    }''',

    '?else': '''
    /* ?else */
    if(*cp < e && ts[*cp]->tt == TT_ELSE) {
        *cp += 1;
    }else {
        knh_Stmt_terms_add(ctx, b, new_Stmt(ctx, 0, STT_DONE));
        return b;
    }''',

    '?catch': '''
    /* ?catch */
    if(*cp < e && ts[*cp]->tt == TT_CATCH) {
        knh_Stmt_terms_add(ctx, b, new_Stmt__catch(ctx, ts, *cp, e, cp));
        goto L_$NEXT;
    }else {
        knh_Stmt_terms_add(ctx, b, new_Stmt(ctx, 0, STT_DONE));
        goto L_$NEXT;
    }''',

    '?finally': '''
    /* ?finally */
    if(*cp < e && ts[*cp]->tt == TT_FINALLY) {
        *cp += 1;
        goto L_$NEXT;
    }else {
        knh_Stmt_terms_add(ctx, b, new_Stmt(ctx, 0, STT_DONE));
        return b;
    }''',

   '?decl': '''
    /* ?LABEL */
    if(*cp < e && knh_Token_isTYPEN(ts[*cp])) {
        TODO();
        *cp += 1;
        goto L_$NEXT;
    }else {
        goto L_$NEXT;
    }''',

   '?where': '''
    /* ?where */
    if(*cp < e && ts[*cp]->tt == TT_WHERE) {
        *cp += 1;
        goto L_$NEXT;
    }else {
        knh_Stmt_terms_add(ctx, b, new_Stmt(ctx, 0, STT_DONE));
        goto L_7;
    }''',

    '?ANY': '''
    /* ?ANY */
    if(*cp < e && knh_Token_isANY(ts[*cp])) {
        knh_Stmt_terms_add(ctx, b, ts[*cp]);
        *cp += 1;
        goto L_$NEXT;
    }else {
        goto L_$NEXT;
    }''',

    'L_ERR' : '''
    L_ERR:;
    knh_int_t ee = knh_tokens_epos(s, *cp, e);
    MC_EPRINT(ctx, ts[ee], MC_ERROR, "%s statement: %%s", knh_Token_tochar(ts[ee]));
    knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
    *cp = knh_tokens_nextstmt(ts, *cp, e);
    return b; ''',

}

def write_grammar_token(f, tk, gtk):
    if gtk.startswith('$'):
       fmt = GRAMMAR['$T']
       return fmt.replace('$T', gtk.replace('$', '')) 
    if GRAMMAR.has_key(gtk):
        return GRAMMAR[gtk]
    fmt = GRAMMAR['TT']
    return fmt.replace('TT', 'TT_%s' % (gtk.upper()))

def write_grammar_each(f, tk):
    CPROTO.append('Stmt *new_Stmt__%s(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);' % tk.name)
    f.write('''
Stmt *new_Stmt__%s(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
    DEBUG_ASSERT(ts[s]->tt == %s);
    DEBUG_ASSERT(s == *cp);
    Stmt *b = new_Stmt(ctx, 0, STT_%s);
    knh_Stmt_add_meta(ctx, b, ts, s);
    knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;''' % (tk.name, tk.tt, tk.name.upper()))

    labelc = 2
    hase = False
    for gtk in tk.grammar[1:]:
        code = write_grammar_token(f, tk, gtk)
        if code.find('L_ERR') > 0 :
            hase = True
        if code.find('L_$NEXT') > 0 :
            code = code + '\n\n\tL_$NEXT:;'
        f.write(code.replace('L_$NEXT', 'L_%d' % labelc))
        labelc += 1

    f.write('''
    return b;''')

    if hase:
        f.write(GRAMMAR['L_ERR'] % tk.name)
    f.write('''
}
''')
    
def write_grammar(f):
    write_chapter(f, '[grammar]')
    DC = {}
    for tk in TT_LIST:
        if tk.grammar is None: continue
        if DC.has_key(tk.tt): continue
        DC[tk.tt] = tk
        write_grammar_each(f, tk)
        write_line(f)

    CPROTO.append('Stmt *new_Stmt__stmt1(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp);')
    f.write('''
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
''')

    for tk in TT_LIST:
        if not STT_MAP.has_key(tk.name): continue
        if tk.isf('nothead'): continue
        if tk.grammar is None: continue
        f.write('''
    case %s: 
        return new_Stmt__%s(ctx, ts, *cp, e, cp); ''' % (tk.tt, tk.name))
#    f.write('''
#    case TT_TRY: 
#        return new_Stmt__try(ctx, ts, *cp, e, cp);''')
    for tk in TT_LIST:
        if not tk.isf('nothead'): continue
        f.write('''
    case %s:''' % tk.tt)
    f.write('''
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
''')

    CPROTO.append('Stmt *new_Stmt__block(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e);')
    f.write('''
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
''')

#------------------------------------------------------------------------------

STT = [
  ["namespace", 2, "decl", 
   'struct: namespace NAME', 
   'declc', 'declm', 'declv', 'asm', 
  ],

  ["include", 2, "decl", 
   'struct: include ANY', 
   'declc', 
  ],
  
  ["uimport", 2, "decl using +import", 
   'struct: NSCLASSN', 
   'declc', 
  ],
  ["uvocab", 2, "decl using +vocabulary", 
   'struct: CLASSTN CURN', 
   'declc', 
  ],
  ["uint", 2, "decl using +int", 
   'struct: CLASSTN CURN', 
   'declc', 
  ],
  ["uint64", 2, "decl using +long", 
   'struct: CLASSTN CURN', 
   'declc', 
  ],
  ["ufloat", 2, "decl using +unit", 
   'struct: CLASSTN CURN', 
   'declc', 
  ],
  ["utable", 2, "decl using +unit", 
   'struct: CLASSTN CURN', 
   'declc', 
  ],
  ["ufunc", 2, "decl using +unit", 
   'struct: CMETHODN NAME', 
   'declc', 
  ],
  
  ['weave', 2, "decl", 
    'struct: ANY ANY',
    'declc',
  ],
  ["class", 5, "decl", 
   'struct: class CLASSN CLASSN implements {', 
   'declc', 'declm', 'declv', 'asm',
  ],
  ["implements", 5, "", 
   'struct: implements +CLASSN', 
  ],
  ['method', 4, 'decl class expr', 
   'struct: TYPEN METHODFN decl ?{', 
   'declm', 'declv', 'asm',
  ],
  ['decl', 3, 'decl class stmt', 
   'struct: TYPEN FIELDN expr', 
   'declv',
  ],
  ['if', 4, 'stmt run', 
   'struct: if expr { {',
   'declv', 'asm',
  ],
  ['try', 4, 'stmt run', 
   'struct: try { __catch {',
   'declv', 'asm',
  ],
  ['catch', 4, '', 
   'struct: catch EXPTN FIELDN {',
#   'declv', 'asm',
  ],
  ['do', 4, 'stmt run', 
   'struct: do { while expr', 
   'declv', 'asm',
  ],
  ['while', 3, 'stmt run', 
   'struct: while expr {',
   'declv', 'asm',
  ],
  ['for', 4, 'stmt run', 
   'struct: for expr expr expr {',
   'declv', 'asm',
  ],
  ['foreach', 6, 'stmt run', 
   'struct: foreach decl FIELDN expr expr {',
   'declv', 'asm',
  ],
  ['continue', 2, 'stmt nop', 
   'struct: continue ?ANY',
   'asm',
  ],
  ['break', 2, 'stmt nop', 
   'struct: break ?ANY',
   'asm',
  ],
  ['goto', 2, 'stmt nop', 
   'struct: goto ANY',
   'asm',
  ],
  ["throw", 2, 'stmt run', 
   'struct: throw expr', 
   'asm',
  ],
  ["return", 2, 'stmt run', 
   'struct: return ?expr',
   'asm',
  ],
  ['eval', 2, "stmt run", 
    'struct: eval expr',
    'asm',
  ],
  ['print', 4, 'stmt run', 
   'struct: print +expr',
   'asm',
  ],
  ['assert', 2, 'stmt run', 
   'struct: assert expr', 
   'asm', 
  ],
  ['help', 2, 'stmt run', 
   'struct: help ?ANY',
   'declc',
  ],
  ['new', 4, 'expr eval seval run',  
   'struct: NEW CLASSN +expr', 
   'asm', 'stmt_eval', 
  ],
  ['map', 3, 'expr eval seval run', 
   'struct: CLASSN expr ?expr', 
   'asm', 'stmt_eval', 
  ],
  ['let', 2, 'class stmt eval run',
   'struct: FIELDN expr', 
   'declv', 'asm', 'stmt_eval', 
  ],
  ['call', 4, 'stmt expr eval seval run', 
   'struct: METHODN +expr', 
   'asm', 'stmt_eval', 
  ],
  ['movtext', 2, 'expr eval seval run', 
   'struct: MOVTEXT expr', 
   'asm', 'stmt_eval', 
  ],
  ['trinary', 3, 'expr eval seva run',
   'struct: expr expr expr',  
   'asm', 'stmt_eval', 
  ],
  ['op', 4, 'expr eval seval run',
   'struct: OP expr +expr', 
   'asm', 'stmt_eval', 
  ],
  ['alt', 2, 'expr eval seval run',   
   'struct: expr +expr', 
   'asm',  
  ],
  ['and', 2, 'expr eval seval run',   
   'struct: expr +expr', 
   'asm',  
  ],
  ['or', 2, 'expr eval seval run',   
   'struct: expr +expr', 
   'asm',  
  ],
  
  ['next', 2, 'expr eval seval run',   
   'struct: expr ANY', 
   'asm',  
  ],
  
  ['meta', 4, '',
   'struct: +META', 
  ],
  ['err', 1, 'stmt run', 
   'struct: ERR',
   'asm',
  ],
]

#------------------------------------------------------------------------------

class Stmt:
    def __init__(self, ll):
        self.name = ll[0]
        self.stt  = 'STT_%s' % self.name.upper()
        self.size = ll[1]
        self.op = ll[2]
        self.using = None
        for u in self.op:
            if u.startswith('+'): self.using = u[1:]
        
        self.has_expr = False
        if ll[3].find('expr') > 0: self.has_expr = True
        self.struct = ll[3].split()[1:]
        self.isDispatch = False
        for t in self.struct:
            if t == '{' or t == '?{' or t.startswith('__'):
                self.isDispatch = True
        self.visits = ll[4:]
        self.visits.append('srcdump')

    def isf(self, t):
        if self.op.find(t.lower()) != -1: return True
        return False
    
    def visit_op(self, v):
        for t in self.visits:
            if t.startswith(v):
                if t.endswith('+'):
                    return v, True
                if t.find(':') > 0:
                    v1, op = t.split(':')
                    return v1, op
                return v, False
        return None, False

#------------------------------------------------------------------------------

STT_LIST = []
STT_MAP  = {}

for stt in STT:
    st = Stmt(stt)
    STT_LIST.append(st)
    STT_MAP[st.name] = st

#------------------------------------------------------------------------------

def write_stmt_h(f):
    write_chapter(f, 'STT_MACRO knh_stmt_t')
    write_define(f, 'STT_DONE',  '((knh_stmt_t)0)', 40)
    tn = 1
    for st in STT_LIST:
        write_define(f, st.stt, '((knh_stmt_t)%d)' % tn, 40)
        tn += 1
    write_define(f, 'STT_MAXSIZ',  '((knh_stmt_t)%d)' % tn, 40)
    write_line(f)

#------------------------------------------------------------------------------

def write_stmt_is(f, fn, op):
    CPROTO.append('knh_bool_t knh_stmt_is%s(knh_stmt_t stt);' % fn)
    f.write('''
knh_bool_t knh_stmt_is%s(knh_stmt_t stt)
{
    switch(stt) {
    case STT_DONE: return 0;''' % (fn))
    for st in STT_LIST:
        if st.isf(op):
            f.write('''
    case %s: return 1;''' % (st.stt))
        else:
            f.write('''
    case %s: return 0;''' % (st.stt))
    f.write('''
    }
    return 0;
}
''')
    write_line(f)

def write_stmt(f):
    write_chapter(f, '[stmt]')

    CPROTO.append('size_t knh_stmt_initsize(knh_stmt_t stt);')
    f.write('''
static size_t tglobal_stmt_initsize[] = {
    0,''')
    for st in STT_LIST:
        f.write('''
    %d,''' % st.size)
    f.write('''
    0
};

size_t knh_stmt_initsize(knh_stmt_t stt)
{
    return tglobal_stmt_initsize[stt];
}
''')
    write_line(f)

    CPROTO.append('char* knh_stmt_tochar(knh_stmt_t stt);')
    f.write('''
char* knh_stmt_tochar(knh_stmt_t stt)
{
    switch(stt) {
    case STT_DONE: return "STT_DONE";''')
    for st in STT_LIST:
        f.write('''
    case %s: return "%s";''' % (st.stt, st.stt))
    f.write('''
    }
    return "STT_UKNOWN";
}
''')
    write_line(f)
    write_stmt_is(f, 'Decl', 'decl')
    write_stmt_is(f, 'DeclInClass', 'class')
    write_stmt_is(f, 'Statement', 'stmt')
    write_stmt_is(f, 'Expr', 'expr')
    write_stmt_is(f, 'Eval', 'eval')

#------------------------------------------------------------------------------

def write_dispatch_each(f, st):
    funcname = 'void knh_Stmt_dispatch__%s(Ctx *ctx, Stmt *b, f_stmtvisit f, Object *v, int level, int step)' % (st.name)
    CPROTO.append('%s;' % funcname)
    f.write('''
%s
{
    //DEBUG_STMT(ctx, b)
    /* %s */ ''' % (funcname, st.struct))
    c = 0
    for t in st.struct:
        if t == '{':
            f.write('''
    DEBUG_ASSERT(IS_Stmt(b->terms[%d]));
    knh_Stmt_visit(ctx, (Stmt*)b->terms[%d], f, v, level+1);''' % (c, c))
        if t == '?{':
            f.write('''
    if(%d < b->size) {
        DEBUG_ASSERT(IS_Stmt(b->terms[%d]));
        knh_Stmt_visit(ctx, (Stmt*)b->terms[%d], f, v, level+1);
    }''' % (c, c, c))
        if t.startswith('__') :
            f.write('''
    DEBUG_ASSERT(IS_Stmt(b->terms[%d]));
    knh_Stmt_visit(ctx, (Stmt*)b->terms[%d], f, v, level);''' % (c, c))
        c = c + 1
    f.write('''
}
''')
    write_line(f)

def write_dispacth(f):
    return
    write_chapter(f, '[dispacth]')
    for st in STT_LIST:
        if st.isDispatch:
            write_dispatch_each(f, st)
    funcname = 'void knh_Stmt_dispatch(Ctx *ctx, Stmt *b, f_stmtvisit f, Object *v, int level, int step)'
    CPROTO.append('%s;' % funcname)
    f.write('''
%s
{
    switch(b->stt) {
        case STT_DONE: break; ''' % funcname)
    for st in STT_LIST:
        if st.isDispatch:
            f.write('''
        case STT_%s:
            knh_Stmt_dispatch__%s(ctx, b, f, v, level, step);
            break;''' % (st.name.upper(), st.name))
        else:
            f.write('''
        case STT_%s:
            break;''' % (st.name.upper(), ))
    f.write('''
    }
}
''')
    write_line(f)

#------------------------------------------------------------------------------

def write_seval_each(f, st):
    f.write('''
    case %s: /* %s */''' % (st.stt, st.struct))
    c = 0
    for t in st.struct:
        if t == 'expr':
            f.write('''
        v = knh_Term_seval(ctx, stmt->terms[%d], knh_Stmt_reqtype(stmt, req, %d), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[%d] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[%d], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        ''' % (c, c, c, c))
        if t == '+expr' or t == 'expr+':
            f.write('''
        for(i = %d; i < stmt->size; i++) {
            v = knh_Term_seval(ctx, stmt->terms[i], knh_Stmt_reqtype(stmt, req, i), ns);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(stmt->terms[i] != v) {
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[i], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
            }
            if(!knh_Term_isStaticValue(v)) {
                isall = 0;
            }
        }''' % (c))

        if t == '?expr':
            f.write('''
    if(%d == stmt->size) {
            v = knh_Term_seval(ctx, stmt->terms[%d], knh_Stmt_reqtype(stmt, req, %d), ns);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(stmt->terms[%d] != v) {
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[%d], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
            }
            if(!knh_Term_isStaticValue(v)) {
                isall = 0;
            }
        }''' % (c+1, c, c, c, c))
        c = c + 1
    if st.isf('seval'):
        f.write('''
        if(isall) {
            v = knh_Stmt_seval__%s(ctx, stmt, req);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(knh_Term_isStaticValue(v)) {
                DEBUG("switch CALL1..");
                stmt->stt = STT_CALL;
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[0], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
                stmt->size = 1;
            }
        }''' % (st.name))
    f.write('''
    break;''')

def write_seval(f):
    write_chapter(f, '[seval]')
    funcname = 'Term* knh_Term_seval(Ctx *ctx, Term *b, knh_class_t req, NameSpace *ns)'
    CPROTO.append('%s;' % funcname)
    f.write('''
%s
{
    if(IS_Token(b)) {
        return knh_Token_seval(ctx, (Token*)b, req, ns);
    }
    Stmt *stmt = (Stmt*)b;
    DEBUG_ASSERT(IS_Stmt(stmt));
    Term *v;
    knh_int_t i, isall = 1;
    switch(stmt->stt) {
    case STT_DONE: 
        return b; ''' % funcname)
    for st in STT_LIST:
        if st.has_expr:
            write_seval_each(f, st)
        else:
            f.write('''
    case %s: /* %s */
        return b;''' % (st.stt, st.struct))
    f.write('''
    }
    return b;
}
''')
    return 
    for st in STT_LIST:
        if st.isf('seval'):
            f.write('''
Term *knh_Stmt_seval__%s(Ctx *ctx, Stmt *b, knh_class_t req)
{
    /* THIS FUNCTION SHOULD BE CALLED BY knh_Term_seval() */
    /* %s */
    DEBUG_STMT(ctx, b);
    return NULL;
}'''  % (st.name, st.struct))
            write_line(f)

#------------------------------------------------------------------------------

def write_stmtvisit_each(f, visit, st, isDispatch = True):
    funcname = 'void knh_stmtvisit_%s__%s(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)' % (visit, st.name)
    CPROTO.append('%s;' % funcname)
    f.write('''
%s
{
    //DEBUG_STMT(ctx, stmt);
    //Cmpl *mc = (Cmpl*)v;
    /* %s */
''' % (funcname, st.struct))
    if isDispatch:
        f.write('''
    knh_Stmt_dispatch(ctx, stmt, knh_stmtvisit_%s, v, level, step);''' % visit)
    else:
        f.write('''
    //knh_Stmt_dispatch(ctx, stmt, knh_stmtvisit_%s, v, level, step);''' % visit)
    f.write('''
    //knh_Stmt_done(ctx, stmt);
}
''')
    write_line(f)

def write_stmtvisit_all(f, visit):
    for st in STT_LIST:
        v, op = st.visit_op(visit)
        if v is None: continue
        if op == True: continue
        write_stmtvisit_each(f, visit, st, False)

def before_stmtvisit(visit, st):
    if visit == 'asm' :
        if st.isf('run'): return '''
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);'''
        elif st.isf('nop') : return '''
            if(level == 0) {
                    return;
            }'''
        else :
            return '''
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);'''
    if visit == 'declv' :
        return ''' 
            knh_Cmpl_before_declv(ctx, (Cmpl*)v, stmt, level);'''
    return ''

def after_stmtvisit(visit, st):
    if visit == 'asm' :
        if st.isf('run'): return '''
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }'''
        else :
            return '''
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);'''
    if visit == 'declv' :
        return ''' 
            knh_Cmpl_after_declv(ctx, (Cmpl*)v, stmt, level);'''
    return ''

def write_stmtvisit(f, visit):
    write_chapter(f, '[visit_%s]' % visit)
    for st in STT_LIST:
        v, op = st.visit_op(visit)
        if v is None: continue
        if op == True:
            write_stmtvisit_each(f, visit, st, op)
    #
    funcname = 'void knh_stmtvisit_%s(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)' % (visit)
    CPROTO.append('%s;' % funcname)
    f.write('''
%s
{
    switch(stmt->stt) {
        case STT_DONE: break;''' % funcname)
    for st in STT_LIST:
        v, op = st.visit_op(visit)
        if v is None: continue
        if op == True or op == False:
            f.write('''
        case STT_%s:%s
            knh_stmtvisit_%s__%s(ctx, stmt, v, level, step);%s
            break;''' % (st.name.upper(), before_stmtvisit(visit, st), visit, st.name, after_stmtvisit(visit, st)))
        else:
            f.write('''
        case STT_%s:%s
            knh_stmtvisit_%s__%s(ctx, stmt, v, level, step);%s
            break;''' % (st.name.upper(), before_stmtvisit(visit, st), visit, op, after_stmtvisit(visit, st)))
    f.write('''
    }
}
''')

def write_cmpl_asm(f):
	write_chapter(f, '[cmpl_asm]')
	CPROTO.append('knh_asmv_t knh_Cmpl_asmv(Ctx *ctx, Cmpl *b, Term *tm, knh_type_t req, int sp);')
	f.write('''
knh_asmv_t
knh_Cmpl_asmv(Ctx *ctx, Cmpl *b, Term *tm, knh_type_t req, int sp)
{
	if(IS_Token(tm)) {
		if(knh_Term_isStaticValue(tm)) {
			return new_asmv__StaticValue(ctx, (Token*)tm, req);
		}
		Token *tk = (Token*)tm;
		if(knh_Token_isFIELDN(tk)) {
			return new_asmv__name(ctx, b, tk, req, sp);
		}
		DEBUG("unknown token %s", knh_Token_tochar(tk));
		return new_asmv__noname(ctx, tk, req);
	}
	DEBUG_ASSERT(IS_Stmt(tm));
	Stmt *stmt = (Stmt*)tm;
	switch(stmt->stt) {''')
	
	for st in STT_LIST:
		if not st.isf("expr"): continue
		f.write('''
	case %s:
		return knh_Cmpl_asmv__%s(ctx, b, tm, req, sp);''' % (st.stt, st.name))
		
	f.write('''
	}
	DEBUG("unknown expr %s", knh_stmt_tochar(stmt->stt));
	return new_asmv__OBJ(KNH_NULL);
}
''')
	write_line(f)

#------------------------------------------------------------------------------

def gen_compiler(bdir):

    fname = '%s/gen/konohac_parser_.c' % bdir
    f = open_c(fname, ['<konoha/konoha_dev.h>'])
#    write_name_c(f)
    write_token(f)
    write_grammar(f)
#    write_stmt_using(f)
    write_stmt(f)
    close_c(f, fname)
    
    fname = '%s/gen/konohac_visitor_.c' % bdir
    f = open_c(fname, ['<konoha/konoha_dev.h>'])
    write_dispacth(f)
    write_stmtvisit(f, 'declc')
    write_stmtvisit(f, 'declm')
    write_stmtvisit(f, 'declv')
    write_stmtvisit(f, 'asm')
    write_seval(f)
    write_cmpl_asm(f)
    #write_stmtvisit_all(f, 'asm')
    close_c(f, fname)

    fname = '%s/include/konoha/konohac_token_.h' % bdir
    f = open_h(fname, ['<konoha/konoha_t.h>', '<konoha/class/konohac.h>'])
    write_token_h(f)
    write_stmt_h(f)
    write_dline(f)
    for p in CPROTO: f.write(p+'\n')
    close_h(f, fname)
    
#------------------------------------------------------------------------------

if __name__ == '__main__':
    bdir = '..'
    gen_compiler(bdir)
