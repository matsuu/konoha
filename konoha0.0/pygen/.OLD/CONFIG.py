import os

#------------------------------------------------------------------------------

TCONFIG = [
	['VERSION',"1.0"],
	['VERSION_STATUS', "Experimental"],
	['CC', "gcc"],
	['ARCH', "unknown"],
	['HOME', "/usr/local/konoha"],

	['TSTRUCT_SIZE', 128],
	['TGLOBAL_SIZE',  32],
	['TCLASS_SIZE', 1024],
	['TEXP_SIZE',    256],

	['STRUCT', 0],
	['CLASS', 0],

	['FIELD_SIZE',    64],
	['STACK_SIZE',  4096],
]


#------------------------------------------------------------------------------

CONFIGTBL = {}

def read_CONFIG():
	for p in TCONFIG:
		CONFIGTBL[p[0]] = p[1]



