#!/usr/bin/python
import os, sys
from pygenlib2 import *

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------
# ----------------------------------------------------------------------------

CPROTO = []
TOKEN_LIST = []
TT_LIST = []
TT_MAP = {}
STT_LIST = []
STT_MAP  = {}
ADD_MAP = {}

#------------------------------------------------------------------------------

STMT = '''
done                     @stmt
namespace NSNAME:ns ;    @stmt @token @new
import FURN:file ;        @stmt @token @new @decl
pragma VARN:name pragma.. ANY:value ;       @stmt @token @new

using uoption..            @token @stmt
using_import NSCLASSN:ns ;  @stmt @decl
using_alias  CLASSN:class  CURN:urn ;     @stmt @decl
using_unit   CLASSTN:class CURN:urn ;     @stmt @decl
using_enum   CLASSTN:class CURN:urn ;     @stmt @decl
using_vocab  CLASSTN:class CURN:urn ;     @stmt @decl
with @token
using_func   CMETHODN:func ;   @stmt @decl
using_mapmap CLASSTN:target CLASSTN:source CURN:urn ;  @stmt @decl

class CLASSN:class extends.. CLASSN:superclass STT_IMPLEMENTS:interface {:instmt  @stmt @token @new @decl @name @cmpl
extends @token
implements CLASSN*:class[] @stmt @token

method TYPEN:rtype cmethod.. CLASSN:class METHODN:method STT_DECL:params {:instmt  @stmt  @token @name @cmpl
function NAME:name STT_DECL:params {:instmt @stmt @token

format MT:name PARAM*:params STR:format ;   @stmt  @token @new @name @cmpl
decl TYPEN:type VARN:name expr:value @stmt @name
return EXPR*:values   @stmt  @token @new @cmpl
mapmap CLASSTN*:paths[]   @stmt   @token @new 

weave ANY:aspect CMETHODN:method @stmt @token @new
aspect TYPEN:type cmethod.. CLASSN:class METHODN:method STT_DECL:params {:instmt  @stmt @token @new

block {:block @stmt @new

if pexpr:bool {:truecase else.. {:falsecase  @stmt @token @new @name @cmpl
else @token
switch pexpr:bool {:case @token @stmt @new @name @cmpl
case @token 
while pexpr:bool {:loop @token @stmt @new @name @cmpl
do {:loop pexpr:bool ; @stmt @token @new @name @cmpl
for pstmt3.. stmt:init expr:bool stmt:redo {:loop  @stmt @token @new @name @cmpl
foreach peach.. TYPEN:type VARN:name expr:iter expr:where {:loop @stmt @token @new @name @cmpl
from @token
where @token

break    any_:label ; @stmt @token @new @cmpl
continue any_:label ;  @stmt @token @new @cmpl
#goto ANY:label ;  @stmt @token @new @cmpl

try {:try catch.. {:catch {:finally   @stmt  @token @new  @name @cmpl
catch EXPTN:type VARN:name {:catch   @token @stmt
finally @token
throw expr:expt ;   @stmt  @token @new @name @cmpl
err ANY:msg     @stmt @cmpl

let         VARN:lvalue expr:rvalue     @stmt  @name @cmpl  @expr
register    expr*:exprs[] ; @stmt @token @new @cmpl
#letexpr  VARN:lvalue expr:rvalue     @stmt  @name @cmpl  @expr
letmulti VARN*:names[]               @stmt    

@expr new     METHODN:new CLASSN:class expr*:args[]  @stmt @cmpl
@expr mapcast CLASSN:class expr:source expr:option   @stmt @cmpl
@expr call    METHODN:method expr:base expr*:args[]  @stmt @cmpl
@expr call1   expr:value @stmt @cmpl
@expr pcall   METHODN:method expr:base pcall.. expr*:args[] @stmt
@expr mt      MT:mt expr:target expr:option @stmt  @cmpl
@expr op      expr:first expr:second expr*:args[] @stmt  @cmpl
@expr proceed METHODN:method expr:base expr*args[]

@expr tri     expr:bool expr:tvalue expr:fvalue @stmt  @cmpl
@expr alt     expr*:bools[]  @stmt   @cmpl
@expr and     expr*:bools[]  @stmt   @cmpl
@expr or      expr*:bools[]  @stmt   @cmpl

print  expr*:values[] ;  @stmt @token @new  @cmpl
assert pexpr:bool ;    @token @stmt @new 
#utest  pexpr:bool {:testcase  @stmt @test
#man   ANY:keyword ;  @stmt @new

'''

TOKEN = '''
{ BRACE          @array     @top @P99
( PARENTHESIS    @array     @top @P99
[ BRANCET        @array     @top @P99
... DOTS         @top

; SEMICOLON      @stmt     @eos
, COMMA          @P0
=> FUNCMAP       @P99
= LET            @P0
<<= lshifte      
>>= rshifte       
+= adde           
-= sube            
/= dive          
%= mode          
*= mule          
&= bitande       
|= bitore        
?\?= ALTLET      
? QUESTION       @P2
.. Itr           @op @P2 @A1
..< SUBSET       @P99
..+ OFFSET       @P99
: COLON          @P99
?\? ALT          @op    @P2

|| OR            @P5
or TT_OR         @alias @P5
&& AND           @P6
and TT_AND       @alias  @P6
!  Not           @top  @op  @P7 @A1
not TT_NOT       @alias  @P7  @A1

instanceof Instanceof  @op    @P9  @A2
isa? Isa               @op    @P9  @A2
isa  TT_ISA @alias     @P9  @A2
as  As                 @op  @P9  @A2
in? Has                @op  @P9  @A2

=== Is                 @op @A2  @P9
is?  TT_IS @alias      @op @A2  @P9
to? To                 @op @A2  @P9
-->  TT_TO @alias      @op @A2  @P9

== Eq                  @op @A2   @P9
!= Neq                 @op @A2   @P9
< Lt                   @op @A2   @P9
<= Lte                 @op @A2   @P9
> Gt                   @op @A2   @P9
>= Gte                 @op @A2   @P9
=~  Match              @op @A2   @P9

<< Lshift              @op @2    @P15
>> Rshift              @op @2    @P15
+ Add                  @op @top  @P20
- Sub                  @op @top  @P20  @A2
/ Div                  @op @2    @P24  @A2
% Mod                  @op @2    @P24  @A2
* Mul                  @op @2    @P24  @A2

& Land                 @op @top      @P27
|  Lor                  @op @top     @P27

~ Lnot                 @op @A1 @top  @P27
^ Xor                  @op @A2 @top  @P27
++ Next                @op @A1 @top  @P28
-- Prev                @op @A1 @top  @P28
--- Neg                @op @A1 @top  @P28

NUM                    @system @top @const @P99
STR                    @system @top @const @P99
TSTR                   @system @top @const @P99
ESTR                   @system @top @P99
LABEL                  @system @top
METAN                  @system @top @eos
PROPN                  @system @top @P99
URN                    @system @top @const @P99
MT                     @system @top @P99
CONSTN                 @system @top @const @P99
TYPEN                  @system @top @const @P99
CMETHODN               @system @top @const @P99
NAME                   @system @top @const @P99
ERR                    @system 
MN                     @system @top @P99
FN                     @system @top @P99
CID                    @system @top @P99
MPR                    @system @top @P99
EOT                    @system @eos

#Typed Token
CONST                  @system @P99
DEFVAL                 @system @P99
SYSVAL                 @system @P99
STACK                  @system @P99
FIELD                  @system @P99
GLOBAL                 @system @P99
MEMBER                 @system @P99
CLASSID                @system @P99
_ ASIS                 @system @P99
NOP                    @system @P99


public  TT_METAN        @alias
private TT_METAN        @alias
final   TT_METAN        @alias
virtual TT_METAN        @alias
static  TT_METAN        @alias
const   TT_METAN        @alias

mod     TT_MOD          @alias

char    Int!            @alias
short   Int!            @alias
int     Int!            @alias
long    Int!            @alias
float   Float!          @alias
double  Float!          @alias
boolean Boolean!        @alias
string  String!         @alias
def     Any             @alias
ArrayList Array         @alias
Integer Int             @alias

TRUE    true            @alias
FALSE   false           @alias
NULL    null            @alias
True    true            @alias
False   false           @alias

'''

#------------------------------------------------------------------------------

class Token:
    def __init__(self, line):
        self.line = line
        self.options = []
        self.alias = None
        
        c = 0
        for t in line.split():
            if t.startswith('@'):
                self.options.append(t)
                continue
            if c == 0:
                c += 1
                if t == "\\#": t = '#'
                self.token = t
                self.name = t
            elif c == 1:
                c += 1
                self.name = t
        
        if not '@system' in self.options:
            TOKEN_LIST.append(self)            
        if '@alias' in self.options:
            if self.name.startswith('TT_'):
                self.TT = self.name
            else:
                self.alias = self.name
        else:
            self.TT = 'TT_%s' % self.name.upper()
            TT_LIST.append(self)
            TT_MAP[self.name] = self
        self.opFunc = 'METHODN_NONAME'
        if '@op' in self.options:
            self.opFunc = 'METHODN_op' + self.name
            
    def isf(self, op):
        return op in self.options
    
    def array(self, op):
        if op == '@P':
            for op in self.options:
                if op.startswith('@P'): return op[2:]
            return '0'
        if op == '@A':
            for op in self.options:
                if op.startswith('@A'): return op[2:]
            return '0'
        if op == '@name': return '"%s"' % self.token
        if op == '@op': return self.opFunc
        if op == '@eos': 
            if op in self.options or '@stmt' in self.options:
                return '1';
            return '0'
        if op in self.options: return '1'
        return '0'

class Param:
    def __init__(self, type, name):
        #print type, name
        self.type = type
        self.name = name
        self.cast = 'terms'
        self.check = 'knh_Term_isExpr(%s)'
        if type == '{' :
            self.cast = 'stmts'
            self.check = 'IS_Stmt(%s)'
        if type.startswith('STT_'):
            self.cast = 'stmts'
            self.check = '(SP((Stmt*)(%%s))->stt = %s)' % type
            return
        if type[0].isupper():
            self.cast = 'tokens'
            self.check = 'knh_Token_is%s(%%s)' % type

    def __k__(self):
        if self.type == self.name:
            return self.type
        return '%s:%s' % (self.type, self.name)


class Stmt:
    def __init__(self, line):
        self.line = line
        self.options = []
        self.structs = []
        self.grammars = []
        self.size = 0
        self.has_args = False
        
        c = 0
        e = 0
        for t in line.split():
            if t.startswith('@'): 
                self.options.append(t)
                continue
            if c == 0:
                if t.startswith('_'): t = t[1:]
                
                self.name = t.replace('_', ' ')
                self.id = '_' + t.replace('using_', 'u').replace('pragma_', 'p')
                self.macro = self.id[1:].upper()
                self.STT = 'STT%s' % self.id.upper()
                c += 1
            else:
                type = t
                if t.find(':') > 0:
                    type, name = t.split(':')
                    self.structs.append(Param(type, name))
                    if not ADD_MAP.has_key(type): 
                        ADD_MAP[type] = type
                if e == 0:
                    if type.endswith('..'): 
                        e = 1
                        type = type.replace('..', '')
                    self.grammars.append(type)
                if type.endswith('*'): self.size += 4
        if self.isf('@token'):
            if self.isf('@stmt'): 
                Token('%s @stmt' % self.id.replace('_', ''))
            else:
                Token('%s @eos' % self.id.replace('_', ''))
                
        self.funcbase = 'Stmt' + self.STT.replace('STT_', '')
        self.size += len(self.structs)

    def isf(self, op):
        return op in self.options

    def array(self, op):
        if op == '@size': return '%d' % self.size
        if op == '@tochar': return '"%s"' % self.name
        if op in ['@decl', '@name', '@cmpl']:
            if op in self.options:
                return 'knh_%s_%s' % (self.funcbase, op[1:])
            else:
                return 'knh_StmtDONE_%s' % (op[1:])
        if op in self.options: return '1'
        return '0'

#------------------------------------------------------------------------------

for line in STMT.split('\n'):
    if line == '' or line.startswith('#'):
        continue
    st = Stmt(line)
    STT_LIST.append(st)
    STT_MAP[st.id] = st

for line in TOKEN.split('\n'):
    if line == '' or line.startswith('#'):
        continue
    Token(line)

#------------------------------------------------------------------------------

def write_token_h(f):
    write_chapter(f, 'TT_MACRO knh_token_t')
    tn = 0        
    for tk in TT_LIST:
        write_define(f, tk.TT, '((knh_token_t)%d)' % tn, 40)
#        if tk.opFunc != None:
#            write_ifndef(f, 'METHODN_%s' % tk.opFunc, 'METHODN_NONAME', 40)
        tn += 1
        if tk.isf('@system'):
            write_define(f, 'knh_Token_is%s(tk_)' % tk.name, '(SP(tk_)->tt == %s)' % tk.TT, 40)
    write_define(f, 'KNH_TOKEN_MAXSIZ',  '((knh_token_t)%d)' % tn, 40)
    write_line(f)

    for tk in TT_LIST:
        if tk.opFunc != 'METHODN_NONAME':
            write_ifndef(f, '%s' % tk.opFunc, 'METHODN_NONAME', 40)
    write_line(f)


def write_stmt_h(f):
    write_chapter(f, 'STT_MACRO knh_stmt_t')
    tn = 0
    for st in STT_LIST:
        write_define(f, st.STT, '((knh_stmt_t)%d)' % tn, 40)
        tn += 1
    write_define(f, 'KNH_STMT_MAXSIZ',  '((knh_stmt_t)%d)' % tn, 40)

    write_line(f)

    for st in STT_LIST:
        write_chapter(f, '[%s]' % st.name)
        loc = -1
        for p in st.structs:
            loc += 1
            if p.name.endswith('[]'):
                write_define(f, 'Stmt%s_%s_size(stmt)' % (st.macro, p.name[:-2]), '(DP(stmt)->size - %d)' % loc, 40)
                write_define(f, 'Stmt%s_%s(stmt,n)' % (st.macro, p.name[:-2]), 'DP(stmt)->%s[n-%d]' % (p.cast, loc), 40)
                continue
            if p.name.endswith('[-1]'):
                write_define(f, 'Stmt%s_%s(stmt)' % (st.macro, p.name[:-4]), 'DP(stmt)->%s[DP(stmt)->size - 1]' % (p.cast), 40)
            else:
                write_define(f, 'Stmt%s_%s(stmt)' % (st.macro, p.name), 'DP(stmt)->%s[%d]' % (p.cast, loc), 40)
                write_define(f, '%s_%s' % (st.macro, p.name), '%d' % loc, 40)
    
    ###
    
#------------------------------------------------------------------------------
# common
#------------------------------------------------------------------------------

def write_array(f, ctype, ttype, fn, list, op):
    f.write('''
static %s knh_%s_array_%s[] = {''' % (ctype, ttype, fn))
    for t in list:
        f.write('''
    %s,  /* %s */ ''' % (t.array(op), t.name))
    f.write('''
    //(%s)0
};
''' % (ctype))
    
    func = '%s knh_%s_%s(knh_%s_t t)' % (ctype, ttype, fn, ttype)
    CPROTO.append(func+';')
    f.write('''
%s
{
    KNH_ASSERT(t < KNH_%s_MAXSIZ);
    return knh_%s_array_%s[t];
}
''' % (func, ttype.upper(), ttype, fn))
    write_line(f)

def write_knh_StmtDONE(f):
    f.write('''
''')

#------------------------------------------------------------------------------
# parser
#------------------------------------------------------------------------------

def write_chktoken_c(f):
    write_chapter(f, '[token checker]')
    CPROTO.append('int knh_bytes_istoken(knh_bytes_t t, int ch);')
    f.write('''
int knh_bytes_istoken(knh_bytes_t t, int ch)
{
    switch(ch) {
''')
    DC = {}
    for tk in TOKEN_LIST:
        ch = tk.token[-1]
        if ch.isalnum() or len(tk.token) == 1: continue
        if not DC.has_key(ch):
            DC[ch] = []
        DC[ch].append(tk)

    fcl = DC.keys()
    fcl.sort()
    
    for fc in fcl:
        f.write('''
    case '%s':''' % fc)
        for tk in DC[fc]:
            f.write('''
        if(ISB(t, "%s")) { return 1; }''' % (tk.token[:-1].replace("\\", "")))
        f.write('''
        return 0; ''')
    
    f.write('''
    /* built-in */
    }
    return 0;
}
''')


def write_tparser_c(f):
    write_chapter(f, '[token parser]')
    CPROTO.append('Token *new_Token__parse(Ctx *ctx, knh_flag_t flag, InputStream *in, knh_bytes_t token);')
    f.write('''

Token *new_Token__parse(Ctx *ctx, knh_flag_t flag, InputStream *in, knh_bytes_t token)
{
    knh_bytes_t t = token;
    knh_token_t tt = ((knh_token_t)-1);
    L_TAIL:;
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

    switch(t.buf[0]) {''')
    DC = {}
    for tk in TOKEN_LIST:
        if not DC.has_key(tk.token[0]):
            DC[tk.token[0]] = []
        DC[tk.token[0]].append(tk)

    fcl = DC.keys()
    fcl.sort()

    #print al
    for fc in fcl:
        f.write('''
    case '%s':''' % fc)
        for tk in DC[fc]:
            if tk.alias is None :
                f.write('''
        if(ISB(t, "%s")) { tt = %s; break; }''' % (tk.token, tk.TT));
            else:
                f.write('''
        if(ISB(t, "%s")) { t = STEXT("%s"); goto L_TAIL; }''' % (tk.token, tk.alias));
        f.write('''
    break;''')
    f.write('''
    /* built-in */
    }
    if(tt == ((knh_token_t)-1)) {
        return new_Token__NAME(ctx, flag, in, t);
    }
    else {
        Token *tk = new_Token(ctx, flag, DP(in)->urid, DP(in)->line, tt);
        if(tt == TT_METAN) {
            KNH_SETv(ctx, DP(tk)->data, new_String(ctx, t, NULL));
        }
        return  tk;
    }
}
''')

#------------------------------------------------------------------------------
# parser
#------------------------------------------------------------------------------

def write_stmt_add(f, token):
    write_section(f, '[%s]' % token)
    func = 'void knh_Stmt_add_%s(Ctx *ctx, Stmt *o, knh_tokens_t *tc)' % token
    #CPROTO.append('%s;' % func)
    f.write('''
static %s
{
\tif(SP(o)->stt == STT_ERR) return;
\tif(tc->c < tc->e && knh_Token_is%s(tc->ts[tc->c])) {
\t\tknh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
\t\ttc->c += 1;
\t}
\telse {
\t\tknh_Stmt_tokens_perror(ctx, o, tc, KMSG_T%s);
\t}
}
''' % (func, token, token))
    
def write_new_Stmt(f, st):
    write_section(f, '[%s]' % st.name)
    if st.name.startswith("using "):
        #CPROTO.append('Stmt *new_%s(Ctx *ctx, knh_tokens_t *tc);' % st.funcbase)
        f.write('''
static
Stmt *new_%s(Ctx *ctx, knh_tokens_t *tc)
{
\tStmt *o = new_Stmt(ctx, 0, %s);''' % (st.funcbase, st.STT))
        for type in st.grammars:
            comment = '/* %s */' % (type)
            t = type.upper().replace('*', 's').replace('{', 'STMT1').replace('STT_', '')
            func = 'knh_Stmt_add_%s(ctx, o, tc)' % t
            if t == ';':
                func = 'knh_Stmt_add_SEMICOLON(ctx, o, tc)';
            f.write('''
\t%s; %s''' % (func, comment))
        f.write('''
\treturn o;
}
''')
    else:
        f.write('''
static Stmt *new_%s(Ctx *ctx, knh_tokens_t *tc)
{
\tStmt *o = new_Stmt(ctx, 0, %s);
\tknh_StmtMETA_add_prestmt(ctx, o, tc, -2);''' % (st.funcbase, st.STT))
        for type in st.grammars:
            comment = '/* %s */' % (type)
            t = type.upper().replace('*', 's').replace('{', 'STMT1').replace('STT_', '')
            func = 'knh_Stmt_add_%s(ctx, o, tc)' % t
            if t == ';':
                func = 'knh_Stmt_add_SEMICOLON(ctx, o, tc)';
            f.write('''
\t%s; %s''' % (func, comment))
        f.write('''
\treturn o;
}
''')
    write_line(f)

def write_sparser_c(f):
    for t in ADD_MAP.keys():
        if not t[0].isupper() : 
            del ADD_MAP[t]
            continue
        if t.startswith('STT_') or t.endswith('*') : 
            del ADD_MAP[t]
            continue
        #print 'T%s:3\n\tja:"(%s)"\n' % (t, t)
        write_stmt_add(f, t)

    write_chapter(f, '[stmt parser]')
    for st in STT_LIST:
        if st.isf('@new'):
            write_new_Stmt(f, st)

    write_section(f, '[stmt1]')

    #CPROTO.append('Stmt *new_StmtSTMT1(Ctx *ctx, knh_tokens_t *tc);')
    f.write('''
static
Stmt *new_StmtSTMT1(Ctx *ctx, knh_tokens_t *tc)
{
    Token *tkc = NULL;
    L_TAIL:;
    if(!(tc->c < tc->e)) {
        DBG2_P("c = %d, e = %d", tc->c, tc->e);
        return new_Stmt(ctx, 0, STT_DONE)(ctx);
    }
    tkc = tc->ts[tc->c];
    tc->c += 1;
    switch(SP(tkc)->tt) {
 ''')
    for tk in TT_LIST:
        if tk.TT == 'TT_LABEL':
            f.write('''
    case TT_LABEL: 
        goto L_TAIL;''')
            continue
        if tk.TT == 'TT_METAN' :
            f.write('''
    case TT_METAN: 
        if(DP(tkc)->tt_next == TT_PARENTHESIS) {
            tc->c += 1;
        };
        goto L_TAIL;''')
            continue
        if tk.TT == 'TT_SEMICOLON' :
            f.write('''
    case TT_SEMICOLON:
        return new_Stmt(ctx, 0, STT_DONE)(ctx);''')
            continue
#        if tk.TT == 'TT_QUESTION' :
#            f.write('''
#//   case TT_QUESTION:
#//      return new_StmtMAN(ctx, tc);''')
#            continue
        if tk.TT == 'TT_ERR' :
            f.write('''
    case TT_ERR:
        /* no error message */
        return new_StmtERR(ctx, tc);''')
            continue
        if tk.TT == 'TT_IMPLEMENTS' or tk.TT == 'TT_CATCH':
            f.write('''
    case %s:  /* %s */
        break;''' % (tk.TT, tk.name))
            continue
        if tk.isf('@stmt') :
            f.write('''
    case %s: 
        return new_Stmt%s(ctx, tc);''' % (tk.TT, tk.name.upper()))
            continue
        if tk.isf('@top'):
            f.write('''
    case %s:  /* %s */
        tc->c -= 1;
        return new_StmtFUNCEXPR(ctx, tc);''' % (tk.TT, tk.name))
        else:
            f.write('''
    case %s:  /* %s */
        break;''' % (tk.TT, tk.name))
    f.write('''
    }
    knh_Token_perror(ctx, tkc, KMSG_TSTMT1);
    return new_StmtERR(ctx, tc);
}
''')

#------------------------------------------------------------------------------

def write_check(f, st):
    func = 'knh_bool_t knh_Stmt_is%s(Stmt *o)' % (st.id[1:])
    CPROTO.append(func+';')
    f.write('''
%s
{''' % (func))
    if st.has_args:
        f.write('''
    int i;''')
    loc = -1
    for e in st.elements:
        loc += 1
        if e.name.endswith('args'):
            f.write('''
    for(i = %d; i < DP(o)->size; i++) {
        SAFE_ASSERT(%s(DP(o)->terms[i]), "%s i=%%d", i);
    }''' % (loc, e.check, e.name))
            break
        f.write('''
    SAFE_ASSERT(%s(DP(o)->terms[%d]), "%s i=%d");''' % (e.check, loc, e.name, loc))
    ###
    f.write('''
}
''')

#------------------------------------------------------------------------------

def write_visitfunc(f, st, visit, rtype = 'void', args = 'Cmpl *cmpl, NameSpace *ns,'):
    return
    write_section(f, "[%s]" % visit)
    f.write('''
#define _knh_%s_%s     knh_StmtNOP_%s

//%s
//knh_%s_%s(Ctx *ctx, Stmt *b, %s int level) 
//{
//\t/* %s */

//}

''' %(st.funcbase, visit, visit, rtype, st.funcbase, visit, args, st.elements))
     
#------------------------------------------------------------------------------

def gen_stmt(bdir):
    fname = '%s/src/gen/konohac_.c' % bdir
    f = open_c(fname, ['<konoha/konoha_dev.h>'])
    
    write_chapter(f,'[token]')
    write_array(f, 'char*', 'token', 'tochar', TT_LIST, '@name')
    write_array(f, 'knh_methodn_t', 'token', 'tomethodn', TT_LIST, '@op')
    write_array(f, 'int', 'token', 'getOpPriority', TT_LIST, '@P')
    write_array(f,  'int', 'token', 'getOpSize', TT_LIST, '@A')
    write_array(f, 'knh_bool_t', 'token', 'isEndOfStmt', TT_LIST, '@eos')
    write_tparser_c(f)
    write_chktoken_c(f)
        
    write_chapter(f,'[stmt]')
    write_array(f, 'char*', 'stmt', 'tochar', STT_LIST, '@tochar')
    write_array(f, 'size_t', 'stmt', 'size', STT_LIST, '@size')
    #write_sparser_c(f)

    write_knh_StmtDONE(f)
    write_array(f, 'int', 'stmt', 'isExpr', STT_LIST, '@expr')
    #write_array(f, 'f_visitdecl', 'stmt', 'decl', STT_LIST, '@decl')
    #write_array(f, 'f_visitname', 'stmt', 'name', STT_LIST, '@name')
    #write_array(f, 'f_visitcmpl', 'stmt', 'cmpl', STT_LIST, '@cmpl')
    
    close_c(f, fname)
    ##
    
    fname = '%s/include/konoha/gen/konohac_stmt_.h' % bdir
    f = open_h(fname, ['<konoha/konoha_t.h>', '<konoha/konoha_class.h>'])
    write_token_h(f)
    write_stmt_h(f)
    write_dline(f)
    for p in CPROTO: f.write(p+'\n')
    close_h(f, fname)
    
#------------------------------------------------------------------------------

if __name__ == '__main__':
    bdir = '..'
    gen_stmt(bdir)
