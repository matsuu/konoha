#!/usr/bin/python

#############################################
#  gen_stub.py
#  generate stub_pkgname.c from pkgname.k 
#  shinpei(c)2009
############################################
import os, sys
import re

if len(sys.argv) is 1:
    print "usage: python " + sys.argv[0] + " *.k"
    print "(example: python " + sys.argv[0] + " math.k)"
    sys.exit()

pkgname = sys.argv[1];
INFILE = pkgname
pkgname = pkgname.replace(".k","")
STUBFILE = "".join(("stub_",pkgname ,".c"))

input = open(INFILE, 'r')
output = open(STUBFILE, 'w')

L = input.readlines()
input.close()
lines = []
for s in xrange(len(L)):
    if L[s] != '\n' and (L[s].startswith("//") is False):
        lines.append(L[s].replace('\n','').replace(';',''))
        
output.writelines("""#include <konoha.h>
#include <wand/MagickWand.h>

""")


TYPES = {
    'void': 'KNH_RETURN_void(ctx, sfp)',
    'Boolean': 'KNH_RETURN_Boolean(ctx, sfp, ret)',
    'Int': 'KNH_RETURN_Int(ctx, sfp, ret)',
    'int': 'KNH_RETURN_Int(ctx, sfp, ret)',
    'Float': 'KNH_RETURN_Float(ctx, sfp, ret)',
    'float': 'KNH_RETURN_Float(ctx, sfp, ret)',
    'new': 'KNH_RETURN(ctx, sfp, sfp[0].o)',
    'String': 'KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL))'
    }

RETURNS = {
    'void': '',
    'Int': 'int ',
    'int': 'int ',
    'Float': 'double ',
    'float': 'double ',
    'String': 'char *',
    'Boolean': 'int ',
    }

ARGS = {
    'Object': 'Object *%s = sfp[%d].o',
    'Class': 'knh_Class_t *%s = sfp[%d].c',
    'String': 'char *%s = p_char(sfp[%d])',
    'Bytes': 'knh_Bytes_t *%s = sfp[%d].ba',
    'Iterator': 'knh_Iterator_t *%s = sfp[%d].it',
    'Closure': 'knh_Closure_t *%s = sfp[%d].cc',
    'Glue' : 'knh_Glue_t *%s = sfp[%d].glue',
    'OutputStream': 'knh_OutputStream_t *%s = sfp[%d].w',
    'Method': 'knh_Method_t *%s = sfp[%d].mtd',
    'Mapper': 'knh_Mapper_t *%s = sfp[%d].mpr',
    'Exception': 'knh_Exception_t *%s = sfp[%d].e',
    'ExceptionHandler': 'knh_ExceptionHandler_t *%s = sfp[%d].hdr',
    'int': 'int %s = p_int(sfp[%d])',
    'Int': 'int %s = p_int(sfp[%d])',
    'Float': 'float %s = p_float(sfp[%d])',
    'float': 'float %s = p_float(sfp[%d])',
    'Array': 'Array *%s = (Array*)sfp[%d].o',
    'Boolean': 'int %s = p_int(sfp[%d])'
    }

PREFIX = [
    'class',
    '@singleton'
    ]

funcflag = False
classflag = False
classes = []

for s in lines:
    classflag = False
    if 'class' in s:
        classflag = True
    a = re.split(ur"[ .,(){}]", s)
    while '' in a: a.remove('')
    if classflag is True:
        key = a.pop()
        print "CLASS:", key, "is defined."
        ARGS[key] =  '%s *' % key + '%s =' + '(%s*)' % key + '((sfp[%d].glue)->ptr)'
        TYPES[key] = 'KNH_RETURN(ctx, sfp, ret)'
        RETURNS[key] = '%s *' % key
        
for s in lines:
    funcflag = False

    if '(' in s:
        funcflag = True

    a = re.split(ur"[ .,()]", s)
    while '' in a: a.remove('')
#    if not a[0] in PREFIX and len(a) > 2:
    if funcflag is True:
        thisreturn = a[0];
        thisclass = a[1];
        thismethod = a[2];
        bindingname = "".join((a[1], "_" ,a[2]))
        output.writelines("""
/* %s */

METHOD %s(Ctx *ctx, knh_sfp_t* sfp)
{
""" % (s,bindingname))
        types=[]
        args=[]

        if len(a) > 3:
            tmp = a[3:]
            print 'tmp:',tmp
            num = 0
            selfflag = 0;
            for line in tmp:
                if num % 2 is 0:
                    if 'self' in line:
                        types.append(thisclass)
                        args.append("self")
                        num=num+1
                    else:
                        types.append(line)
                else:
                    args.append(line)
                num=num+1
            
            dargs = dict(zip(args, types))

            #now, get ready to get arguments.

            for idx in xrange(len(args)):
                key = types[idx]
                if ARGS.has_key(key):
                    val = ARGS[key]
                    output.writelines("""\t%s;
""" % (val % (args[idx], idx)))
                    
        
        else: 
            #when no arg is set
            print "no arg func"
        #now, ready for library dependent part. 
        thismethod = thismethod[0].upper() + thismethod[1:]
        funcname = "".join((thisclass.replace("Wand",""), thismethod))
        funccall = funcname + "("
        
        if args != []:
            for idx in xrange(len(args)):
                if idx is 0:
                    funccall = funccall + "%s " % args[idx]
                else:
                    funccall = funccall + ",%s " % args[idx]
        funccall = funccall + ")"
        retval = RETURNS[thisreturn]
        if not retval is '':
            retval = retval + "ret = "
            output.writelines("\t" + retval + funccall + ";\n")

        #now, make KNH_RETURN.    
        s.replace('!','')
        key = a[0]
        if TYPES.has_key(key):
            val = TYPES[key]
            output.writelines("""
\t%s;
}
""" % val)
            
        else:
            output.writelines("""
}
""")
output.writelines('''

METHOD MagickWand_new(Ctx *ctx, knh_sfp_t* sfp)
{
  knh_Glue_t *glue = sfp[0].glue;
  glue->ptr = (void *)NewMagickWand();
  KNH_RETURN(ctx, sfp, sfp[0].o);
}
''')
output.close()
