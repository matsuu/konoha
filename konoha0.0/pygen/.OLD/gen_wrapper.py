#!/usr/bin/python
import os, os.path, sys
from pygenlib  import *

CTYPE = [
	['this',  'T', 'sf[0]', 'N/A'],
	['int',   'i', 'knh_Number_toint(o)', 'new_Number__i(ctx, o)'],
	['float', 'f', 'knh_Number_tofloat(o)', 'new_Number__f(ctx, knh_Method_rtype(sf[-1]), o)'],
	['Object', 'O', 'o', 'o'],
]

bdir = '..'

def add_clists(dir, fn, clists):
	cpath = dir + '/' + fn
	if cpath.startswith('../'):
		cpath = cpath.replace('../', '')
	oname = cpath.split('/')[-1].replace('.c', '.o')
	clists.append((cpath, oname))

def find_c(dir, clists):
	fl = os.listdir(dir)
	for fn in fl:
		if fn.startswith('.'): continue
		if fn.startswith('_'): continue
		if fn.endswith('.c'): 
			add_clists(dir, fn, clists)
		if os.path.isdir(dir + '/' + fn):
			find_c(dir + '/' + fn, clists)

def make_make(bdir):
	clists = []
	find_c(bdir, clists)
	for cf in clists:
		print cf
