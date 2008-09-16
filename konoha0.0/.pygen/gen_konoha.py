#!/usr/bin/python
import os, os.path, sys
from pygenlib2  import *
from source import *
from gen_class import *
from gen_make import *

#############

if __name__ == '__main__':
	bdir = '..'
	data = read_data(bdir)
	gen_konoha_init_c(bdir, data)
	gen_class_h(bdir, data)
	gen_makefile(bdir, data)
	if '-a' in data.OPTIONS:
		from gen_message import read_message
		from gen_message import gen_message
		read_message(bdir + '/.pygen/message.txt')
		gen_message(bdir)
		from gen_vm import gen_vm_c
		gen_vm_c(bdir)
		from gen_konohac import gen_stmt
		gen_stmt(bdir)
		gen_automake(bdir)

