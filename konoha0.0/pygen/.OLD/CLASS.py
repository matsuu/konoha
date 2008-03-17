#!/usr/bin/python
import os, sys
from pygenlib  import *
from CONFIG import *

#------------------------------------------------------------------------------
#------------------------------------------------------------------------------

TFLAG = []
FLAGTBL = {}

class FlagBool:
    def __init__(self, l):
        self.prefix = l[0]
        if l[1].find('!') > 0:
            self.pname, self.nname = l[1].split('!')
        else:
            self.pname = l[1]
            self.nname = None
        self.flagn = ('KNH_FLAG_%s_%s' % (self.prefix, self.pname)).upper()
        self.ctype = l[2]
        self.fmt   = l[3]
        self.func = l[4].split(':')

class Flag:
    def __init__(self, l):
        self.ctype = None
        self.flags = []
        for fl in l:
            fb = FlagBool(fl)
            self.flags.append(fb)
            if self.ctype == None and fb.ctype.startswith("knh_"):
                self.ctype = fb.ctype

    def write_typedef(self, f):
        if self.ctype is not None:
            f.write('''
typedef knh_flag_t %s;
''' % self.ctype)

        n = 0
        for fb in self.flags:
            if fb.flagn is None: continue
            if fb.ctype.startswith('knh_'):
                write_define(f, fb.flagn, 'KNH_FLAG%d' % n, 40)
                n += 1
            else:
                write_define(f, fb.flagn, 'KNH_FLAG_OF_LOCAL%s' % fb.ctype, 40)
        write_line(f)
    
    def write_func_h(self, f, c):
        for fb in self.flags:
            if fb.flagn is None: continue
            args = 'o'
            if fb.fmt.find('[n]') > 0: args = 'o,n'
            if fb.func[0] != '*':   #/* is */
                f.write('''
#define %s_%s%s(%s)   ((%s & %s) == %s)
''' % (c.funcbase, fb.func[0], fb.pname, args, fb.fmt % 'o', fb.flagn, fb.flagn))
                if fb.nname is not None:
                    f.write('''
#define %s_%s%s(%s)   ((%s & %s) != %s)
''' % (c.funcbase, fb.func[0], fb.nname, args, fb.fmt % 'o', fb.flagn, fb.flagn))
            if fb.func[1] != '*':  #/* set */
                f.write('''
#define %s_%s%s(%s,b)  \\
\tif(b) %s |= %s; else %s &= ~(%s);

''' % (c.funcbase, fb.func[1], fb.pname, args, fb.fmt % 'o', fb.flagn, fb.fmt % 'o', fb.flagn))
                if fb.nname is not None:
                    f.write('''
#define %s_%s%s(%s,b)  \\
\tif(b) %s &= ~(%s); else %s |= %s;

''' % (c.funcbase, fb.func[1], fb.nname, args, fb.fmt % 'o', fb.flagn, fb.fmt % 'o', fb.flagn))

    def write_func_c(self, f, c):
        for fb in self.flags:
            if fb.flagn is None: continue
            if fb.func[2] != '*':   # /* is */
                fn = fb.func[2] + fb.pname
                write_line(f)
                f.write('''
/* @method Bool! %s.%s() */
''' % (c.mtdbase.replace('knh__', ''), fn))

                f.write('''

#ifndef BEFORE_$MN
#define BEFORE_$MN
#endif
#ifndef AFTER_$MN
#define AFTER_$MN
#endif

METHOD $MN(Ctx *ctx, Object **sfp)
{
\tBEFORE_$MN;
\tif(%s_%s(sfp[0])) {
\t\tVM_RET(ctx, KNH_TRUE);
\t}else{
\t\tVM_RET(ctx, KNH_FALSE);
\t}
\tAFTER_$MN;
}
'''.replace('$MN', '%s_%s' % (c.mtdbase, fn)) % (c.funcbase, fn))
                if fb.nname is not None:
                    fnn = fb.func[2] + fb.nname
                    write_line(f)
                    f.write('''
/* @method Bool! %s.%s() */
''' % (c.mtdbase.replace('knh__', ''), fn))
                    f.write('''

#ifndef BEFORE_$MN
#define BEFORE_$MN
#endif
#ifndef AFTER_$MN
#define AFTER_$MN
#endif

METHOD $MN(Ctx *ctx, Object **sfp)
{
\tBEFORE_$MN;
\tif(%s_%s(sfp[0])) {
\t\tVM_RET(ctx, KNH_TRUE);
\t}else{
\t\tVM_RET(ctx, KNH_FALSE);
\t}
\tAFTER_$MN;
}
'''.replace('$MN', '%s_%s' % (c.mtdbase, fnn)) % (c.funcbase, fnn))
            if fb.func[3] != '*':
                fn = fb.func[3] + fb.pname
                write_line(f)
                f.write('''
/* @method void %s.%s(Bool b) */
''' % (c.mtdbase.replace('knh__', ''), fn))

                f.write('''

#ifndef BEFORE_$MN
#define BEFORE_$MN
#endif
#ifndef AFTER_$MN
#define AFTER_$MN
#endif

METHOD $MN(Ctx *ctx, Object **sfp)
{
\tBEFORE_$MN;
\tif(IS_TRUE(sfp[1])) {
\t\t%s |= %s;
\t}else{
\t\t%s &= ~(%s);
\t}
\tAFTER_$MN;
}
'''.replace('$MN', '%s_%s' % (c.mtdbase, fn)) % (fb.fmt % 'sfp[0]', fb.flagn, fb.fmt % 'sfp[0]', fb.flagn))
                if fb.nname is not None:
                    fnn = fb.func[3] + fb.nname
                    write_line(f)
                    f.write('''
/* @method void %s.%s(Bool b) */
''' % (c.mtdbase.replace('knh__', ''), fn))
                    f.write('''

#ifndef BEFORE_$MN
#define BEFORE_$MN
#endif
#ifndef AFTER_$MN
#define AFTER_$MN
#endif

METHOD $MN(Ctx *ctx, Object **sfp)
{
\tBEFORE_$MN;
\tif(IS_TRUE(sfp[1])) {
\t\t%s &= ~(%s);
\t}else{
\t\t%s |= %s;
\t}
\tAFTER_$MN;
}
'''.replace('$MN', '%s_%s' % (c.mtdbase, fnn)) % (fb.fmt % 'sfp[0]', fb.flagn, fb.fmt % 'sfp[0]', fb.flagn))


    def write_writerTODO(self, f):
        ff.write('''
PUBLIC
void knh_write__%s(Ctx *ctx, Writer *w, %s f)
{
    int_t c = 0;''' % (self.name, self.name))
        n = 0
        for tf in self.flags:
            fn = '%s_%s' % (self.prefix, tf.upper())
            ff.write('''
    if((f & %s) == %s) {
        if(c > 0) knh_write_dots(ctx, w);
        knh_write(ctx, w, B("%s"));
        c++;
    }''' % (fn, fn, tf.lower()))
        ff.write('''
}
''')


#------------------------------------------------------------------------------

UNUSE_CLASS = ['Long']

def is_UNUSE_cname(cname):
    return cname in UNUSE_CLASS

def set_UNUSE_cname(cname):
    if not cname in UNUSE_CLASS: UNUSE_CLASS.append(cname)

#------------------------------------------------------------------------------

class Class:
    def __init__(self, pkgn, ns, t):
        self.pkgn  = pkgn
        self.ns    = ns
        self.name  = t[0]
        self.cname = '%s_%s' % (ns, t[0])
        if self.cname.startswith('knh_'):
            self.cnameS = self.cname.replace('knh_', '')
        else:
            self.cnameS = self.cname
        
        self.funcbase = '%s_%s' % (ns, t[0])
        self.mtdbase = '%s__%s' % (ns, t[0])
        if pkgn == 'konoha':
            self.fullname = self.cnameS
        else:
            self.fullname = self.cname.replace('%s_' % ns, self.pkgn + '.')
        
        self.super_cname = t[1]
        self.interfaces = t[2]
        self.options = parse_options(t[3])
        
        if type(t[4]) == type(1):
            self.bsize = t[4]
            self.struct = None
            self.sname = self.cname
        else:
            self.bsize = -1
            self.struct = t[4]
            if self.options.has_key('@tuple'):
                self.sname = 'Tuple%d' % len(self.struct)
            else:
                self.sname = self.cname
    
    def isf(self, op):
        return self.options.find(op) >= 0
    
    def isUNUSE(self):
        return is_UNUSE_cname(self.cname)

    def isDEBUG(self):
        return True


# in Class ###########################################

    def write_define(self, f, n):
        if self.isUNUSE(): n = 0
        write_comment(f, self.cname)
            
        if self.cname == self.sname:
            write_define(f, STRUCT_cname(self.cnameS), '((knh_struct_t)%d)' % n, 32)
            write_define(f, 'STRUCT_IS_%s(o)' % self.cnameS, '(knh_Object_topsid(o) == %s)' % STRUCT_cname(self.cnameS), 32)
            write_define(f, CLASS_cname(self.cnameS), '((knh_class_t)%d)' % n, 32)
        else:
            write_define(f, STRUCT_cname(self.cnameS), '(knh_struct_t)(sizeof(%s)/sizeof(Object*))' % self.cname, 32)
            #write_define(f, 'STRUCT_IS_%s(o)' % self.cnameS, 'STRUCT_IS_%s(o)' % self.sname, 32)
            write_define(f, CLASS_cname(self.cnameS), '((knh_class_t)KONOHA_TSTRUCT_SIZE+%d)' % n, 32)

        write_define(f, 'CF_%s' % self.cnameS, '((knh_flag_t)0)', 32)
        write_define(f, 'OF_%s' % self.cnameS, 'KNH_FLAG_CF2OF(CF_%s)' % self.cnameS, 32)
        write_define(f, TYPE_cname(self.cnameS), 'CLASS_TONULLABLE(%s)' % CLASS_cname(self.cnameS), 32)
        write_define(f, TYPE_cname(self.cnameS+'..'), 'CLASS_TOPLURAL(%s)' % CLASS_cname(self.cnameS), 32)
        
        write_define(f, 'IS_%s(o)' % self.cnameS, '(knh_Object_cid(o) == %s)' % CLASS_cname(self.cnameS), 32)
        
        if self.isDEBUG():
            write_define(f, 'DEBUG_%s' % self.cnameS, '1', 40)
            write_define(f, 'KNH_CAST_%s(ctx,o)' % self.cnameS, '%s_cast(ctx,o)' % self.funcbase, 40)
            write_define(f, 'KNH_CAST_%sOrNull(ctx,o)' % self.cnameS, '%s_castOrNull(ctx,o)' % self.funcbase, 40)
        else:
            write_define(f, 'KNH_CAST_%s(ctx,o)' % self.cnameS, '((%s*)o)' % self.cname, 40)
            write_define(f, 'KNH_CAST_%sOrNull(ctx,o)' % self.cnameS, '((%s*)o)' % self.cname, 40)
        
        ################    

# in Class ###########################################
    
    def write_typedef(self, f):
        if FLAGTBL.has_key(self.cnameS):
            fg = FLAGTBL[self.cnameS]
            fg.write_typedef(f)
        if FLAGTBL.has_key(self.cname):
            fg = FLAGTBL[self.cname]
            fg.write_typedef(f)
            
        if self.struct == None :
            if self.bsize != 0:
                f.write('''
//typedef struct {
//\tObject* v[%d];
//} %s; 

''' % (self.bsize, self.cname))
                #write_define(f, '%sNULL' % self.cname, self.cname, 32)
            return
        if self.isUNUSE():
            f.write('''/* CAUTION: %s is unused */
''' % (self.cname))
        
        if not self.options.has_key('@Struct') :
           ifdef,endif = check_ifdef(self.options)
           elements = ''
           for tnf in self.struct:
              #print 'DEBUG', tnf
              elements += '\t%s %s;\n' % (tnf[0], tnf[1])
           f.write('''/* class %s */

typedef struct %s {
%s} %s;

''' % (self.cname, self.cname, elements, self.cname))
        #endif    
        write_define(f, '%sNULL' % self.cname, self.cname, 40)

        self.write_prototype(f)

    def write_prototype(self, f):
        write_section(f, self.cname)
        f.write('''
%s* %s_cast(Ctx *ctx, Object *b);''' % (self.cname, self.funcbase))
        f.write('''
%s* %s_castOrNull(Ctx *ctx, Object *b);
''' % (self.cname, self.funcbase))

    def write_CAST(self, f):
        write_line(f)
        f.write('''
#ifndef ISA_%s
#define ISA_%s(ctx, o)   IS_%s(o)
#endif
''' % (self.cnameS, self.cnameS, self.cnameS)) 
        write_line(f)
        f.write('''
#ifdef DEBUG_%s
%s* %s_cast(Ctx *ctx, Object *b)
{
\tKNH_ASSERT(ISA_%s(ctx, b));
\treturn (%s*)b;
}
''' % (self.cnameS, self.cname, self.funcbase, self.cnameS, self.cname))
        write_line(f)
        f.write('''
%s* %s_castOrNull(Ctx *ctx, Object *b)
{
\tKNH_ASSERT(IS_NULL(b) || ISA_%s(ctx, b));
\treturn (%s*)b;
}
#endif
''' % (self.cname, self.funcbase, self.cnameS, self.cname))
        
    def write_flag(self, gen):
#        print '@@@', FLAGTBL
        if FLAGTBL.has_key(self.cnameS):
            fg = FLAGTBL[self.cnameS]
            fg.write_func_h(gen.fh, self)
            fg.write_func_c(gen.fc, self)
            return

        if FLAGTBL.has_key(self.cname):
            fg = FLAGTBL[self.cname]
            fg.write_func_h(gen.fh, self)
            fg.write_func_c(gen.fc, self)
        
            #fg.write_func_h(sys.stdout, self)
        
    def write_TSTRUCT(self, f):
        if self.cnameS == 'Object':
            f.write('''
\tKNH_TSTRUCT(ctx, 0, 0, "Tuple0", NULL, NULL, NULL, NULL); ''')
            return
        f.write('''
\tKNH_TSTRUCT(ctx, %s, sizeof(%s),
\t\t"%s",
\t\t%s_struct_init,
\t\t%s_struct_copy, 
\t\t%s_struct_compare, 
\t\t%s_struct_traverse);''' % (STRUCT_cname(self.cnameS), self.cname, self.cnameS, self.funcbase, self.funcbase, self.funcbase, self.funcbase))

    def write_TCLASS(self, f):
        f.write('''
\tKNH_TCLASS(ctx, CF_%s, new_String__STEXT(ctx, CLASS_String__class, "%s"),
\t\t%s, %s, %s,''' % (self.cnameS, self.fullname, CLASS_cname(self.cnameS), STRUCT_cname(self.cnameS), CLASS_cname(self.super_cname)))
        spec = '%s_spec' % (self.funcbase)
        if not FUNCMAP_exists(spec): 
            spec = 'KNH_NULL'
        else:
            spec += '(ctx)'
        fvalue = '%s_fvalue' % (self.funcbase)
        if not FUNCMAP_exists(fvalue): fvalue = 'NULL'
        f.write('''
\t\t%s,%s, ''' % (spec, fvalue))
        if self.interfaces is not None:
            s = '%d' % len(self.interfaces)
            for n in self.interfaces:
                s += ', ' + CLASS_cname(n)
        else:
            s = '0'
        f.write('''
\t\t%s);''' % (s))

#------------------------------------------------------------------------------

TSTRUCT = []
TCLASS  = []
TCLASSALL = []
CLASSTBL = {}

def CLASSTBL_Class(cname):
    if CLASSTBL.has_key(cname): return CLASSTBL[cname]
    return None

#------------------------------------------------------------------------------

def read_CLASSTBL_class(pkgn, ns, classes):
    for t in classes:
        c = Class(pkgn, ns, t)
        if c.cname in TCLASSALL:
            print 'ERROR!! Duplicated ccame', c.cname
            continue
        TCLASSALL.append(c.cname)
        if not CLASSTBL.has_key(c.sname):
            TSTRUCT.append(c.sname)
        else:
            TCLASS.append(c.cname)
        CLASSTBL[c.cname] = c
        CLASSTBL[c.cnameS] = c
        if c.cnameS == 'Tuple1':
        	CLASSTBL['Tuple'] = c
        #debug_print("read class cname='%s'" % c.cname)
        #c.write_typedef(sys.stdout)

#------------------------------------------------------------------------------

PACKAGETBL = {}

def read_PACKAGE(pdir, pkgn):
    if PACKAGETBL.has_key(pkgn): return
    f = open('%s/%s/classdef.py' % (pdir, pkgn))
    KNH_PACKAGE = {}
    KNH_NAMESPACE = ''
    KNH_PACKAGE_DEPS = ''
    KNH_FLAGS = []
    KNH_CLASSES   = []
    exec(f)
    for pd in KNH_PACKAGE_DEPS.split():
        if not PACKAGETBL.has_key(pd) : read_PACKAGE(pdir, pd)

    debug_print("read package '%s' .." % pkgn)
    PACKAGETBL[pkgn] = KNH_PACKAGE
    if len(KNH_CLASSES) == 0: return
    if KNH_NAMESPACE == '': KNH_NAMESPACE = 'knh_'
    read_CLASSTBL_class(pkgn, KNH_NAMESPACE, KNH_CLASSES)
    for ft in KNH_FLAGS:
    	fg = Flag(ft[1])
    	TFLAG.append(fg)
        FLAGTBL[ft[0]] = fg

#------------------------------------------------------------------------------

def read_PACKAGETBL(bdir):
    pdir = '%s/class' % bdir
    read_PACKAGE(pdir, 'konoha')
    
    fl = os.listdir(pdir)
    for pkgn in fl:
        if pkgn.startswith('_') or pkgn.find('.') > 0 : continue
        if pkgn == 'konoha': continue
        read_PACKAGE(pdir, pkgn)

#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
# konoha_.c

def write_init_struct(f):
    write_chapter(f, '[struct]')
    f.write('''
void knh_tstruct_ginit_(void)
{
\tCtx *ctx = NULL;''')
    for cname in TSTRUCT:
        c = CLASSTBL[cname]
        if c.isUNUSE(): continue
        c.write_TSTRUCT(f)
    f.write('''
}
''')

def write_init_class(f):
    write_chapter(f, "[class]")
    f.write('''
void knh_tclass_ginit_(void)
{
\tCtx *ctx = NULL;''')
    for cname in TSTRUCT + TCLASS:
        c = CLASSTBL[cname]
        if c.isUNUSE(): continue
        c.write_TCLASS(f)
    f.write('''
}
''')

    write_line(f)
    for cname in TSTRUCT + TCLASS:
        c = CLASSTBL[cname]
        if c.isUNUSE(): continue
        write_METHODTBL_p(f, c)    
    
    write_line(f)
    f.write('''
void knh_tmethod_ginit_(void)
{
\tCtx *ctx = NULL;''')
    for n in TNAME:
        f.write('''
\tKNH_TFIELDN(ctx, %s, new_String__STEXT(ctx, CLASS_String__field, "%s"));''' % (FIELDN_name(n.replace(':','__')), n))
        
    write_line(f)
    
    for cname in TSTRUCT + TCLASS:
        c = CLASSTBL[cname]
        if c.isUNUSE(): continue
        f.write('''
\t/* %s */''' % (c.cname))
        write_METHODTBL(f, c)
        write_MAPTBL(f, c)
    f.write('''
}
''')
    
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------

import TYPE

# ---------------------------------------------------------------------------
# mspec

TNAME = ['']
TFIELDN  = ['this', 'vargs']
TMETHODN = ['run']
METHODTBL = {}

def make_name():
    d = {}
    for fn in TFIELDN:
        d[fn] = fn
        TNAME.append(fn)

    for mn in TMETHODN:
        if mn == 'get' or mn == 'set': continue
        if mn.startswith('get'): mn = mn[3:]
        elif mn.startswith('set'): mn = mn[3:]
        elif mn.startswith('%'): mn = mn[1:]
        mn = mn[0].lower() + mn[1:]
        if not d.has_key(mn):
            TNAME.append(mn)
            d[mn] = mn

def write_TFIELDN(f):
    make_name()
    write_chapter(f, 'FIELDN, METHODN')
    c = 0
    for n in TNAME:
        write_define(f, FIELDN_name(n.replace(':', '__')), '((knh_fieldn_t)%d)' % c)
        write_define(f, METHODN_mname(n), '((knh_methodn_t)%d)' % c)
        write_define(f, METHODN_mname('%' + n), '((knh_methodn_t)%d|KNH_FLAG_MN_MOVTEXT)' % c)
        if(len(n) > 0):
            n = n[0].upper() + n[1:]
        write_define(f, METHODN_mname('get' + n), '((knh_methodn_t)%d|KNH_FLAG_MN_GETTER)' % c)
        write_define(f, METHODN_mname('set' + n), '((knh_methodn_t)%d|KNH_FLAG_MN_SETTER)' % c)
        c += 1
    
# ---------------------------------------------------------------------------

#test = "@method[F|F2] Int! MyClass.dump(String out=\"\", Int lv=0)"

class Param:
    def __init__(self, arg):
        arg = arg.replace("w=new", "w")
        arg = arg.replace("Writer", "OutputStream")
        t = arg.replace('=',' ').split()
        
        if len(t) == 1:
            self.type = 'Any'
            self.name = t[0]
            self.value = None
        elif len(t) == 2:
            self.type = t[0]
            self.name = t[1]
            self.value = None
        else:
            self.type = t[0]
            self.name = t[1]
            self.value = t[2]
        self.type = self.type.replace('*', '')

# ---------------------------------------------------------------------------

def new_Method(text):
    loc = text.find('/* @method')
    if loc == -1 : return None
    text = text[loc+3:]
    loc = text.find(')')
    if loc == -1 : return None
    text = text[:loc+1]
    m = Method(text)
    #print '#new_Method "%s"' % text
    if m.cfunc is None: return None
    return m

class Method :
    def __init2__(self, ln) :
        try:
            self.__init2__(ln)
            self.cfunc = None
        except :
            print 'ERROR!', ln
            
    def __init__(self, ln):
        self.flag = parse_flag('KNH_FLAG_MF', ln)
        ln, args = ln.split('(')
        t = ln.replace('.',' ').split()
        self.rtype = t[1]
        self.cname = t[2]
        self.mname = t[3]
        
        if not self.mname in TMETHODN:         
            TMETHODN.append(self.mname)

        self.params = []
        args = args[:args.find(')')]
        if len(args) > 0:
            for arg in args.split(','):
                p = Param(arg)
                self.params.append(p)
                if not p.name in TFIELDN: TFIELDN.append(p.name)
        #
        c = CLASSTBL_Class(self.cname)
        if c is not None:
            self.methodfunc = c.mtdbase + '_' + SAFE_mname(self.mname)
            self.cfunc = c.funcbase + '_' + SAFE_mname(self.mname)
            if not METHODTBL.has_key(self.cname):
                METHODTBL[self.cname] = []
            METHODTBL[self.cname].append(self)
        else:
            print '# Method.parse: class not found', self.cname
            self.cfunc = None
    #

    def write_TMETHOD(self, f):
        if self.methodfunc == None: return
        f.write('''
\tTMETHOD(ctx, %s, %s,
\t\t%s, %s, %s, ''' % (self.flag, self.methodfunc, TYPE_cname(self.rtype), CLASS_cname(self.cname), METHODN_mname(self.mname)))
        s = '%d' % len(self.params)
        for p in self.params:
            s += ', %s, %s' % (TYPE_cname(p.type), FIELDN_name(p.name))
        f.write('''
\t\t%s);
''' % (s))

    def get_param(self, n):
        if n == -1: return Param("%s self" % self.cname)
        if n < len(self.params):
            return self.params[n]
        return Param('TO_CHECK_PARAM param%d' % n)

    def write_methodfunc(self, f, functype):
        f.write('''
#ifndef BEFORE_$METHOD
#define BEFORE_$METHOD
#endif
#ifndef AFTER_$METHOD
#define AFTER_$METHOD
#endif

METHOD $METHOD(Ctx *ctx, Object **sf)
{
\tBEFORE_$METHOD;'''.replace('$METHOD', self.methodfunc)) 
        params = parse_funcparams(functype)
        c = 0
        for fa in params[1:]:
            ctype, cname = TYPE.nz_ctype(fa[0]), TYPE.nz_cname(fa[1]) ###
            if ctype == 'Ctx*' : continue
            p = self.get_param(c-1)
            conv = TYPE.convToC(ctype, p.type, p.value, 'sf[%d]' % c)
            f.write('''
\t%s %s = %s;''' % (ctype, cname, conv))
            c += TYPE.cskip(ctype, p.type)
        #
        rctype = (params[0])[0]
        rval = ''
        if rctype != 'void': rval = '%s _rval_ = ' % SAFE_cname(rctype)
        args = ''
        for fa in params[1:]:
            args += ', ' + TYPE.nz_cname(fa[1])
        if len(args)>1: args = args[2:]
        f.write('''

\t%s%s(%s);

\tBEFORE_%s;''' % (rval, self.cfunc, args, self.methodfunc))
        
        if rval == '':
            f.write('''
\tKNH_SETr_void(ctx, sf);
}

''')
        else:
            safe = ''
            if self.rtype.endswith('!'):
                safe = 'SAFE_'
            f.write('''
\tKNH_%sSETr(ctx, sf, %s);
}

''' % (safe, TYPE.convTokonoha(rctype, self.rtype, '_rval_')))
            #

def write_METHODTBL_p(f, c):
    if METHODTBL.has_key(c.cnameS): 
        for m in METHODTBL[c.cnameS]:
            if m.methodfunc is None: continue 
            f.write('''
void %s(Ctx *ctx, Object **sf); ''' % (m.methodfunc))
    if c.cnameS != c.name and METHODTBL.has_key(c.cname): 
        for m in METHODTBL[c.cname]:
            if m.methodfunc is None: continue 
            f.write('''
void %s(Ctx *ctx, Object **sf); ''' % (m.methodfunc))


def write_METHODTBL(f, c):
    if METHODTBL.has_key(c.cnameS): 
        for m in METHODTBL[c.cnameS]:
            m.write_TMETHOD(f)
    if c.cnameS != c.cname and METHODTBL.has_key(c.cname): 
        for m in METHODTBL[c.cname]:
            m.write_TMETHOD(f)

# ---------------------------------------------------------------------------
# ---------------------------------------------------------------------------
# map


#    '@map' : 'TMAPPING(ctx, $FLAG, $FTYPE, $TTYPE, $FUNC);'

MAPTBL = {}

# ---------------------------------------------------------------------------

test = "@map[F|F2] Int String! 'Null'"

def new_Map(text):
    loc = text.find('/* @map')
    if loc == -1 : return None
    text = text[loc+3:]
    loc = text.find('*/')
    if loc == -1 : return None
    text = text[:loc]
    #print '#new_Map "%s"' % text
    m = Map(text)
    if m.cfunc is None: return None
    return m
class Map :
    def __init__(self, ln) :
        self.flag = parse_flag('KNH_FLAG_MMF', ln)
        t = ln.split()
        self.fcname = t[1]
        self.tcname = t[2]
        if self.tcname.endswith('..') or self.tcname == 'Bool':
            self.tcname += '!'
        if self.tcname.endswith('!'):
            self.tcname = self.tcname.replace('!', '')
            self.flag += '|KNH_FLAG_MMF_TOTAL'
        #else :
        #    self.flag += '|MAPF_PARTIAL'
        #self.config = ''
        #for cf in t[3:]:
        #    self.config += ' ' + cf.replace("'", '')
        #    if cf.endswith("'") : break
        #if len(self.config) > 0 : self.config = self.config[1:]

        cname = SAFE_cname(self.fcname)
        c = CLASSTBL_Class(cname)
        if c is not None:
            self.cfunc = c.funcbase + '_' + SAFE_cname(self.tcname)
            if not MAPTBL.has_key(cname):
                MAPTBL[cname] = []
            MAPTBL[cname].append(self)
        else:
            print '# Method.parse: class not found', cname
            self.cfunc = None

    def write_TMAPMAP(self, f):
        if self.cfunc == None: return
        f.write('''
\tTMAPMAP(ctx, %s, %s, %s, %s, KNH_NULL);''' % (self.flag, self.cfunc, TYPE_cname(self.fcname), TYPE_cname(self.tcname)))


# ---------------------------------------------------------------------------

def write_MAPTBL(f, c):
    if MAPTBL.has_key(c.cnameS): 
        for m in MAPTBL[c.cnameS]:
            m.write_TMAPMAP(f)
    if c.cnameS != c.cname and MAPTBL.has_key(c.cname): 
        for m in MAPTBL[c.cname]:
            m.write_TMAPMAP(f)

#------------------------------------------------------------------------------
#------------------------------------------------------------------------------

