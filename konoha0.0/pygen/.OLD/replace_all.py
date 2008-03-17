#!/usr/bin/python
import sys, os

TERM = {
	'knh_':    'knh_',
	'KNH_':    'KNH_',
	'Konoha Software': 'Konoha Software',
	'konohaware.org': 'konohaware.org',
}

def file_replace(fname) :
	f = open(fname, "r")
	text = f.read()
	for k in TERM.keys():
		if text.find(k) > 0 : text = text.replace(k, TERM[k])	
	f.close()
	print text
	
	f = open(fname, "w")
	f.write(text)
	f.close()   

def file_rename(fname):
	if fname.find('knh_') >= 0:
		newname = fname.replace('knh_', 'knh_')
		os.rename(fname, newname)

for fname in sys.argv[1:] :
    print "replacing", fname
    file_replace(fname)

