#!/usr/bin/python
import os, sys
from pygenlib2 import *

CPROTO = []
TMSG = []
TLANG = ['en']

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

def sjis_filter(t):
    return t

# ----------------------------------------------------------------------------

class Msg:
    def __init__(self, token):
        self.id, self.type = token.split(':')
        self.KMSG = 'KMSG_%s' % self.id
        self.lmap = {}

#------------------------------------------------------------------------------

def read_message(file):
    f = open(file)
    msg = None
    for ln in f:
        if ln.startswith("#"): continue
        ln = ln.replace('\t', '').replace('\n','')
        if ln[0].isupper():
            msg = Msg(ln)
            TMSG.append(msg)
            continue
        if ln[0].islower() and msg is not None:
            lang, text = ln.split(':"')
            msg.lmap[lang] = text[:-1]
            if not lang in TLANG: TLANG.append(lang)
    f.close()

#------------------------------------------------------------------------------
def write_message_h(f):
    tn = 0
    write_define(f, 'KONOHA_LANG',  '"%s"' % TLANG[0], 40)
    for m in TLANG:
        write_define(f, 'KONOHA_LANG__%s' % m, '%d' % tn, 40)
        tn += 1
    write_define(f, 'KONOHA_LANG__debug',  '%d' % tn, 40)
    write_define(f, 'KONOHA_LANG_MAXSIZ',  '%d' % (tn+1), 40)
    write_line(f)
    
    tn = 0
    for m in TMSG:
        write_define(f, m.KMSG, '%d' % tn, 40)
        tn += 1
    write_define(f, 'KMSG_MAXSIZ',  '%d' % tn, 40)
    write_line(f)

    
#------------------------------------------------------------------------------

def write_message_c(f):
    f.write('''
static int local_lang = 0;
''')
    write_line(f)
    f.write('''
static char* knh_system_lang[] = {
    "en", 
#ifdef KNH_USING_I18N''')
    for m in TLANG[1:]:
        f.write('''
    "%s",''' % m)
    f.write('''
#endif
    "debug"
};
''')

    func = 'int knh_system_langid(char *lang)'
    CPROTO.append(func+';')
    f.write('''
%s
{
    int i;
    for(i = 0; i < KONOHA_LANG_MAXSIZ; i++) {
        if(knh_strncmp(knh_system_lang[i], lang, 2) == 0) return i;
    }
    return local_lang;
}
''' % (func))
    write_line(f)

    func = 'void knh_Asm_setLang(char *lang)'
    CPROTO.append(func+';')
    f.write('''
%s
{
#ifdef KNH_USING_I18N
    local_lang = knh_system_langid(lang);
#endif
    //return local_lang;
}
''' % (func))
    write_line(f)

    f.write('''
static int knh_message_typedata[] = {''')
    tn = 0
    for m in TMSG:
        f.write('''
    /* %s */ %s,''' % (m.KMSG, m.type))
    f.write('''
    0
};
''')

    func = 'int knh_message_type(int e)'
    CPROTO.append(func+';')
    f.write('''
%s
{
    DEBUG_ASSERT(e<KMSG_MAXSIZ);
    return knh_message_typedata[e];
}
''' % func)
    write_line(f)

    f.write('''
static char* knh_message_data[] = {''')
    tn = 0
    for m in TMSG:
        f.write('''
    /* %s */ ''' % m.KMSG)
        if m.lmap.has_key("en"):
            f.write('''
        /* en */ "%s",
#ifdef KNH_USING_I18N''' % (sjis_filter(m.lmap["en"])))
        else:
            f.write('''
        /* en */ NULL,
#ifdef KNH_USING_I18N''')
        for l in TLANG[1:]:
            if m.lmap.has_key(l):
                f.write('''
        /* %s */ "%s" ,
''' % (l, sjis_filter(m.lmap[l])))
            else:
                f.write('''
        /* %s */ NULL,''' % l)
        f.write('''
#endif
        "%s",
    ''' % (m.id))
    f.write('''
};
''')
    write_line(f)
    f.write('''

#ifndef KNH_USING_I18N
#undef KONOHA_LANG_MAXSIZ
#define KONOHA_LANG_MAXSIZ 2
#endif

''')

    func = 'char *knh_message_text(int e)'
    CPROTO.append(func+';')
    f.write('''
%s
{
    char *msg;
    DEBUG_ASSERT(e<KMSG_MAXSIZ);
    msg = knh_message_data[e * (KONOHA_LANG_MAXSIZ) + local_lang];
    if(msg != NULL) return msg;
    return knh_message_data[e * (KONOHA_LANG_MAXSIZ) + KONOHA_LANG__debug];
}
''' % (func))
    write_line(f)

    func = 'char *knh_message_tochar(int e)'
    CPROTO.append(func+';')
    f.write('''
%s
{
    DEBUG_ASSERT(e<KMSG_MAXSIZ);
    return knh_message_data[e * (KONOHA_LANG_MAXSIZ) + KONOHA_LANG__debug];
}
''' % func)
    write_line(f)
    
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------

def gen_message(bdir):
    fname = '%s/src/gen/konoha_message_.c' % bdir
    f = open_c(fname, ['<konoha/konoha_dev.h>'])
    write_message_c(f)
    close_c(f, fname)

    fname = '%s/include/konoha/gen/konoha_message_.h' % bdir
    f = open_h(fname, ['<konoha/konoha_t.h>'])
    write_message_h(f)
    write_dline(f)
    for p in CPROTO: f.write(p+'\n')
    close_h(f, fname)
    
#------------------------------------------------------------------------------

if __name__ == '__main__':
    bdir = '..'
    read_message('message.txt')
    gen_message(bdir)
