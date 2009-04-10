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

""")


TYPES = {
    'void': 'KNH_RETURN_void(ctx, sfp)',
    'Boolean': 'KNH_RETURN_Boolean(ctx, sfp, ret)',
    'Int': 'KNH_RETURN_Int(ctx, sfp, ret)',
    'int': 'KNH_RETURN_Int(ctx, sfp, ret)',
    'Float': 'KNH_RETURN_Float(ctx, sfp, ret)',
    'float': 'KNH_RETURN_Float(ctx, sfp, ret)',
    'unknown': 'KNH_RETURN(ctx, sfp, o)',
    'new': 'KNH_RETURN(ctx, sfp, sfp[0].o)'
    }

ARGS = {
    'Object': 'Object *%s = sfp[%d].o',
    'Class': 'knh_Class_t *%s = sfp[%d].c',
    'String': 'knh_String_t *%s = sfp[%d].s',
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
    'unkonow': 'knh_Glue_t *glue = sfp[%d].glue',
    }

PREFIX = [
    'class',
    '@singleton'
    ]

funcflag = False
for s in lines:
    if '(' in s:
        funcflag = True
        
    a = re.split(ur"[ .,()]", s)
    while '' in a: a.remove('')
#    if not a[0] in PREFIX and len(a) > 2:
    if funcflag is True:
        funcname = "".join((a[1], "_" ,a[2]))
        output.writelines("""
/* %s */

METHOD %s(Ctx *ctx, knh_sfp_t* sfp)
{
""" % (s,funcname))

        if len(a) > 3:
            tmp = a[3:]
            #print tmp
            num = 0
            types=[]
            args=[]
            for line in tmp:
                if num % 2 is 0:
                    types.append(line)
                else:
                    args.append(line)
                num=num+1
            #print types, args
            dargs = dict(zip(args, types))

            #print dargs
            count = len(dargs)
            for pair in dargs:
                print dargs[pair]
                key = dargs[pair]
                if ARGS.has_key(key):
                    val = ARGS[key]
                    output.writelines("""\t%s;
""" % (val % (pair, count)))
                    count = count - 1
            
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

output.close()
