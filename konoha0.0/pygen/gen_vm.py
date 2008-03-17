#!/usr/bin/python
import os, sys
import copy
from pygenlib import *

#------------------------------------------------------------------------------

CPROTO = []
CPROTO_Cmpl = []

#------------------------------------------------------------------------------

class ASMType:
	def __init__(self, name, ctype, fmt) :
		self.name  = name
		self.ctype = ctype
		self.ptype = ctype
		if self.name == 'addr':
			self.ptype = 'knh_bytes_t'
		self.fmt = fmt
	
	def isObject(self):
		return (self.ctype == 'Object*')

	def asm(self, v):
		if self.name == 'addr':
			return 'knh_Cmpl_labelId(ctx, b, %s)' % v
		return v

TPARAM = [
		  ASMType('u1', 'knh_vmc_u1_t', '''
	knh_write__i(ctx, w,  (int)%s);'''),
		  ASMType('u2', 'knh_vmc_u2_t', '''
	knh_write__i(ctx, w,  (int)%s);'''), 
		  ASMType('ebp', 'knh_vmc_i1_t', '''
	knh_printf(ctx, w, "ebp[%%d]", (int)%s);'''), 
		  ASMType('sfp', 'knh_vmc_u1_t', '''
	knh_printf(ctx, w, "sfp[%%d]", (int)%s);'''), 
		  ASMType('ofp', 'knh_vmc_u1_t', '''
	knh_printf(ctx, w, "ofp[%%d]", (int)%s);'''),
		  ASMType('OBJ', 'Object*', '''
	knh_format(ctx, w, METHODN__repr, %s, KNH_NULL);'''),
		  ASMType('addr', 'knh_vmc_addr_t', '''
	knh_printf(ctx, w, ">>[%%p]", (((void*)bw) + %s - off));'''),
		  ASMType('c2',   'knh_class_t', '''
	knh_write__type(ctx, w, (knh_type_t)%s);'''), 
		  ASMType('mn',   'knh_methodn_t', '''
	knh_write__mn(ctx, w, (knh_methodn_t)%s);'''), 
		  ASMType('e2',   'knh_expt_t', '''
	knh_write__expt(ctx, w, (knh_expt_t)%s);'''),
]

PARAMTBL = {}

for p in TPARAM:
	PARAMTBL[p.name] = p
	
#------------------------------------------------------------------------------

CODE_DATA = [
	['ret_void'],
	
	['ret*',  'ebp'],
	['ret*',  'sfp'],
	['ret*',  'ofp'],
	['ret*',  'OBJ'],
	['ret__oidx', 'OBJ', 'u1'],

	['move*', 'ebp', 'ebp'],
	['move*', 'ebp', 'sfp'],
	['move*', 'ebp', 'ofp'],
	['move*', 'ebp', 'OBJ'],
	['move__oidx', 'ebp', 'OBJ', 'u1'],

	['movs*', 'sfp', 'ebp'],
	['movs*', 'sfp', 'sfp'],
	['movs*', 'sfp', 'ofp'],
	['movs*', 'sfp', 'OBJ'],
	['movs__oidx', 'sfp', 'OBJ', 'u1'],

	['movo*', 'ofp', 'ebp'],
	['movo*', 'ofp', 'sfp'],
	['movo*', 'ofp', 'ofp'],
	['movo*', 'ofp', 'OBJ'],
	['movo__oidx', 'ofp', 'OBJ', 'u1'],

	['movoi*', 'OBJ', 'ofp', 'ebp'],
	['movoi*', 'OBJ', 'ofp', 'sfp'],
	['movoi*', 'OBJ', 'ofp', 'ofp'],
	['movoi*', 'OBJ', 'ofp', 'OBJ'],
	['movoi__oidx', 'OBJ', 'u1', 'OBJ', 'u1'],

	['movsfp_ifnul', 'u1', 'OBJ'],

#	['push*', 'ebp'],
	['push*', 'sfp'],
	['push*', 'ofp'],
	['push*', 'OBJ'],
	['push__oidx', 'OBJ', 'u1'],
	
	['puti',        'u2'],
	['push__mn',    'mn'],
	['push__def',   'c2'],
    ['vargs',       'u2'],
	
#	['shift',  'u1'],

    ['scall',    'u1'],
    ['call',     'u1'],
    ['dcall',    'u1'],
    ['mcall',    'u1'],
    ['call_wm',  'u1', 'OBJ'],
    ['ncall_wm',  'u1', 'OBJ'],

    ['new'  ,    'u2', 'OBJ', 'u2', 'c2'],
    ['newe'  ,   'u2', 'OBJ', 'u2', 'c2'],
    ['new__def'  ,   'u1', 'u2', 'c2'],

    ['mt'  ,     'mn'],
    ['mt__opt',  'mn', 'OBJ'],

#    ['callget',  'u1'],
#    ['callset',  'u1'],

#	['call_idx', 'u1'],
#	['call_omt0', 'mn'],
#	['call_omt',  'mn', 'OBJ'],
#	['call_imt',  'mn', 'OBJ'],

	['map', 'c2'],
	['mape', 'c2'],
	['map_wm', 'OBJ'],
	['mape_wm', 'OBJ'],
	['map2', 'c2'],
	['map2e', 'c2'],

	['typechk*', 'c2', 'ebp'],
	['typechk*', 'c2', 'sfp'],
	['typechk*', 'c2', 'ofp'],
	['typechk*', 'c2', 'OBJ'],  # TO simplify compiler
	['typechk__oidx', 'c2', 'OBJ', 'u1'],

   ['nullchk*',    'ebp'],
   ['nullchk*',    'sfp'],
   ['nullchk*',    'ofp'],
	['nullchk*',    'OBJ'],    # TO simplify compiler
	['nullchk__oidx', 'OBJ', 'u1'],

	['jmp',    'addr'],
   ['skip',   'addr'],

	['jmp_ift*', 'addr', 'ebp'],
   ['jmp_ift*', 'addr', 'sfp'],
   ['jmp_ift*', 'addr', 'ofp'],
   ['jmp_ift__oidx', 'addr', 'OBJ', 'u1'],

	['jmp_iff*', 'addr', 'ebp'],
   ['jmp_iff*', 'addr', 'sfp'],
   ['jmp_iff*', 'addr', 'ofp'],
   ['jmp_iff__oidx', 'addr', 'OBJ', 'u1'],

   ['jmp_ifnul*', 'addr', 'ebp'],
   ['jmp_ifnul*', 'addr', 'sfp'],
   ['jmp_ifnul*', 'addr', 'ofp'],    
   ['jmp_ifnul__oidx', 'addr', 'OBJ', 'u1'],

   ['jmp_ifnonul*', 'addr', 'ebp'],
   ['jmp_ifnonul*', 'addr', 'sfp'],
   ['jmp_ifnonul*', 'addr', 'ofp'],
   ['jmp_ifnonul__oidx', 'addr', 'OBJ', 'u1'],

   ['iter', 'c2', 'sfp'],
   ['foreach',  'addr', 'c2', 'sfp', 'sfp'],    
#   ['mapfor', 'addr', 'c2', 'sfp', 'sfp'],

   ['try_begin',   'addr', 'sfp', 'sfp'],
   ['try_end',     'sfp'],
   ['catch', 'addr', 'e2', 'sfp'], 

   ['throw*', 'ebp'],
   ['throw*', 'sfp'],
   ['throw*', 'OBJ'],

   ['print*', 'u2', 'mn', 'ebp'],
   ['print*', 'u2', 'mn', 'sfp'],
   ['print*', 'u2', 'mn', 'ofp'],
   ['print*', 'u2', 'mn', 'OBJ'],
   ['print__oidx', 'u2', 'mn', 'OBJ', 'u1'],

   ['diagnose', 'u1'], 
   ['stackdump'],
   ['nop'],
]

#------------------------------------------------------------------------------

class ASMCode:
	def __init__(self, ll) :
		self.struct = ll[:]
		self.type = ll[0].replace('*', '')
		if ll[0].endswith('*'):
			self.lparam = ll[-1]
			self.potype = 'KNH_ASMV_%s' % (self.lparam.upper())
			self.name = ll[0].replace('*', '__') + ll[-1]
			self.NAME = ll[0].upper().replace('*', '__') + ll[-1]
		else:
			self.name = ll[0]
			self.lparam = None
			self.NAME = self.name.upper()
		self.code  = 'ASMC_%s' % self.name.upper()
		self.label = self.code.replace('ASMC_', 'L_')
		self.ctype = 'knh_asmc_%s_t' % self.NAME.lower().replace('__', '_')
		self.size = 'KNH_ASMC_%s_SIZ' % self.NAME.replace('__', '_')
	
	def write_ctype(self, f):
		f.write('''
typedef struct {
	knh_asmc_t code;''')
		c = 0
		for a in self.struct[1:]:
			c += 1
			if PARAMTBL[a].isObject(): continue
			f.write('''
	%s a%d;''' % (PARAMTBL[a].ctype, c))
		c = 0
		for a in self.struct[1:]:
			c += 1
			if not PARAMTBL[a].isObject(): continue
			f.write('''
	%s a%d;''' % (PARAMTBL[a].ctype, c))
		f.write('''
} %s;
''' % self.ctype)

		f.write('''
typedef struct {
	knh_asmc_t code;''')
		c = 0
		for a in self.struct[1:]:
			c += 1
			if PARAMTBL[a].isObject(): continue
			f.write('''
	%s a%d;''' % (PARAMTBL[a].ctype, c))
		c = 0
		for a in self.struct[1:]:
			c += 1
			if not PARAMTBL[a].isObject(): continue
			f.write('''
	%s a%d;''' % (PARAMTBL[a].ctype, c))
		f.write('''
	void *w;
} %sw;

#define %s  (sizeof(%sw)-sizeof(void*))
''' % (self.ctype, self.size, self.ctype))
	
	
	def asm_argv(self):
		t = ''
		c = 1;
		for a in self.struct[1:]:
			t += ', %s a%d' % (PARAMTBL[a].ptype, c)
			c += 1
		return t

	def asm_name(self):
		t = ''
		c = 1;
		for a in self.struct[1:-1]:
			t += ', a%d' % (c)
			c += 1
		return t

	def asmv_argv(self):
		t = ''
		c = 1;
		for a in self.struct[1:-1]:
			t += ', %s a%d' % (PARAMTBL[a].ptype, c)
			c += 1
		t += ', knh_asmv_t v'
		return t

	
	def povalue(self):
		if self.lparam == 'OBJ':
			return '(Object*)v.value';
		return '(%s)v.index' % PARAMTBL[self.lparam].ctype
	
	### 

	def incpc(self) :
		t = '0'
		for a in self.struct[1:]:
			t += '+sizeof(%s)' % PARAMTBL[a].ctype
		t = t.replace('0+', '')
		return 'pc += (%s)' % t

	def delta(self, n) :
		if n == 1: return '0'
		t = '0'
		c = 1
		for a in self.struct[1:]:
			t += '+sizeof(%s)' % PARAMTBL[a].ctype
			c += 1
			if c == n: break
		t = t.replace('0+', '')
		return '(%s)' % t

#------------------------------------------------------------------------------

TCODE = []
CODETBL = {}

for ll in CODE_DATA:
	ac = ASMCode(ll)
	TCODE.append(ac)
	if ac.lparam is None: continue
	if not CODETBL.has_key(ac.type):
		CODETBL[ac.type] = []
	CODETBL[ac.type].append(ac)

print 'numofasmc', len(TCODE)

#------------------------------------------------------------------------------
#------------------------------------------------------------------------------

def write_define_h(f):
	c = 0
	for ac in TCODE:
		write_define(f, ac.code, '((knh_asmc_t)%d)' % c, 40)
		c += 1

	write_line(f)
	write_ifndef(f, 'METHODN__repr', 'METHODN__s', 40)
	write_line(f)

	for p in CPROTO:
		f.write(p + ';\n')

	f.write('''
#ifdef CLASS_Cmpl
''')
	for p in CPROTO_Cmpl:
		f.write(p + ';\n')
	f.write('''
#endif/*CLASS_Cmpl*/
''')
	write_line(f)

	for ac in TCODE:
		ac.write_ctype(f)
		write_line(f)

#------------------------------------------------------------------------------

def write_asm_each(f, ac):
	CPROTO_Cmpl.append('void KNH_ASM_%s(Ctx *ctx, Cmpl *b%s)' % (ac.NAME, ac.asm_argv()))
	f.write('''
void KNH_ASM_%s(Ctx *ctx, Cmpl *b%s)
{
	%s *bw = (%s*)knh_Cmpl_asmmalloc(ctx, b, %s);
	bw->code = %s;''' % (ac.NAME, ac.asm_argv(), ac.ctype, ac.ctype, ac.size, ac.code))
	c = 1;
	for a in ac.struct[1:]:
		f.write('''
	bw->a%d = %s;''' % (c, PARAMTBL[a].asm('a%d' % c)))
		if(PARAMTBL[a].isObject()):
			f.write('''
	knh_Object_refc_inc(bw->a%d);''' % c)
		c += 1
	f.write('''
}
''')
	write_line(f)


def write_asm_eval(f, acl):
	ac0 = acl[0]
	TYPE = ac0.type.upper()
	CPROTO_Cmpl.append('void KNH_ASM_%s(Ctx *ctx, Cmpl *b%s)' % (ac0.type.upper(), ac0.asmv_argv()))
	f.write('''
void KNH_ASM_%s(Ctx *ctx, Cmpl *b%s)
{''' % (ac0.type.upper(), ac0.asmv_argv()))
	f.write('''
#ifdef ASMC_%s__EBP
	if(v.potype == KNH_ASMV_EBP) {
		KNH_ASM_%s__ebp(ctx, b%s, v.index);
		return;
	}
#endif/*ASMC_%s__EBP*/''' % (TYPE, TYPE, ac0.asm_name(), TYPE))
	f.write('''
#ifdef ASMC_%s__SFP
	if(v.potype == KNH_ASMV_SFP) {
		KNH_ASM_%s__sfp(ctx, b%s, v.index);
		return;
	}
#endif/*ASMC_%s__SFP*/''' % (TYPE, TYPE, ac0.asm_name(), TYPE))
	f.write('''
#ifdef ASMC_%s__OFP
	if(v.potype == KNH_ASMV_OFP) {
		KNH_ASM_%s__ofp(ctx, b%s, v.index);
		return;
	}
#endif/*ASMC_%s__OFP*/''' % (TYPE, TYPE, ac0.asm_name(), TYPE))
	f.write('''
#ifdef ASMC_%s__OBJ
	if(v.potype == KNH_ASMV_OBJ) {
		KNH_ASM_%s__OBJ(ctx, b%s, v.value);
		return;
	}
#endif/*ASMC_%s__OBJ*/''' % (TYPE, TYPE, ac0.asm_name(), TYPE))
	f.write('''
#ifdef ASMC_%s__OIDX
	if(v.potype == KNH_ASMV_OIDX) {
		KNH_ASM_%s__OIDX(ctx, b%s, v.value, v.index);
		return;
	}
#endif/*ASMC_%s__OIDX*/
	DEBUG("unsupported asmv.potype=%%d", v.potype);
	KNH_ASSERT(ctx == NULL); /* stop here!!*/
}''' % (TYPE, TYPE, ac0.asm_name(), TYPE))
	write_line(f)

def write_asm_c(f):
	write_chapter(f, '[Cmpl]')
	d = copy.copy(CODETBL)
	for ac in TCODE:
		if d.has_key(ac.type):
			write_asm_eval(f, d[ac.type])
			del d[ac.type]
		write_asm_each(f, ac)

###############################################################################
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------

def write_label(f):
	f.write('''
#define PCT_(pc)    (((knh_asmc_nop_t*)pc)->code)
''')
	write_line(f)
	write_chapter(f, '[label]')
	CPROTO.append('void knh_Cmpl_remapAddress(Ctx *ctx, Cmpl *b)')
	f.write('''

void knh_Cmpl_rewriteAddress(Ctx *ctx, Cmpl *b, knh_asmc_jmp_t *bw)
{
	//DEBUG("label: id=%d", knh_VirtualMachineCode_uread_short(pc));
	String *name = knh_DictIdx_get(b->labelIdDictIdx, bw->a1);
	DEBUG_ASSERT(IS_NOTNULL(name));
	knh_vmc_t *pa = (knh_vmc_t*)knh_DictSet_get__b(b->labelAddrDictSet, knh_String_tobytes(name));
	if(pa == NULL) {
		TODO();
		DEBUG("Asm!!: Unknown Label '%s'", knh_String_tochar(name));
	}else {
		bw->a1 = (knh_short_t)(pa - (knh_vmc_t*)bw);
	}
}

/* ------------------------------------------------------------------------ */

void knh_Cmpl_remapAddress(Ctx *ctx, Cmpl *b)
{
	knh_vmc_t *pc = (knh_vmc_t*)knh_Bytes_tochar(b->elf);
	knh_vmc_t *tail = pc + knh_Bytes_size(b->elf);
	while(pc < tail) {
		switch(PCT_(pc)) {
''');
	for ac in TCODE:
		if len(ac.struct)>1 and ac.struct[1] == 'addr' :
			f.write('''\t\tcase %s :
			knh_Cmpl_rewriteAddress(ctx, b, (knh_asmc_jmp_t*)pc);
			pc += %s;
			break;
''' % (ac.code, ac.size))
		else :
			f.write('''\t\tcase %s :
			pc += %s;
			break;
''' % (ac.code, ac.size))
	f.write('''
		default :
			DEBUG("UNKNOWN VMCODE: %d\\n", PCT_(pc));
			DEBUG_ASSERT(ctx == NULL);
			return;
		}
	}
}
''')

	write_chapter(f, '[vmc]')

	CPROTO.append('void knh_VirtualMachineCode_utraverse(Ctx *ctx, knh_bytes_t vmc, f_gc gc)')
	f.write('''
void knh_VirtualMachineCode_utraverse(Ctx *ctx, knh_bytes_t vmc, f_gc gc)
{
	knh_vmc_t *pc = (knh_vmc_t*)vmc.buf;
	knh_vmc_t *tail = vmc.buf + vmc.len;
	while(pc < tail) {
		switch(PCT_(pc)) {''');
	for ac in TCODE:
		f.write('''
		case %s :''' % (ac.code))
		c = 1
		for a in ac.struct[1:]:
			if PARAMTBL[a].isObject() :
				f.write('''
			gc(ctx, ((%s*)pc)->a%d);''' % (ac.ctype, c))
			c += 1
		f.write('''
			pc += %s;
			break;
''' % (ac.size))
	f.write('''
		default :
			DEBUG("UNKNOWN VMCODE: %d\\n", PCT_(pc));
			DEBUG_ASSERT(ctx == NULL);
			return;
		}
	}
}
''')


#------------------------------------------------------------------------------

def write_dump_each(f, ac):
#	m = '\tVM_%s(ctx' % ac.NAME
	f.write('''
void knh_VirtualMachineCode_%s__dump(Ctx *ctx, %s *bw, int off, Writer *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pcline(mtd, (knh_vmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%%p]", ((knh_vmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%%d:%%p]", line, ((knh_vmc_t*)bw) - off);
	}
	knh_putc(ctx, w, ' ');
	knh_write__s(ctx, w, "%s");'''  % (ac.NAME, ac.ctype, ac.NAME.lower()))
	c = 1
	for a in ac.struct[1:]:
		f.write('''
	knh_putc(ctx, w, ' ');''')
		f.write(PARAMTBL[a].fmt % ('(bw->a%d)' % c))
		c += 1
	f.write('''
	knh_println(ctx, w, TEXT(""));
}
''')
	write_line(f)

def write_dump(f):
	write_chapter(f, '[dump]')

	for ac in TCODE:
		write_dump_each(f, ac)

	write_line(f)
	CPROTO.append('void knh_VirtualMachineCode__dump_(Ctx *ctx, VirtualMachineCode *b, Writer *w, Any *m)')
	f.write('''

PUBLIC
void knh_VirtualMachineCode__dump_(Ctx *ctx, VirtualMachineCode *b, Writer *w, Any *m)
{
	knh_bytes_t vmc = knh_VirtualMachineCode_tobytes(b);
	knh_vmc_t *pc = (knh_vmc_t*)vmc.buf;
	knh_vmc_t *tail = pc + vmc.len;	
	int off = (int)pc;
	while(pc < tail) {
		switch(PCT_(pc)) {
''');
	for ac in TCODE:
		f.write('''\t\tcase %s :
			knh_VirtualMachineCode_%s__dump(ctx, (%s*)pc, off, w, m);
			pc += %s;
			break;
''' % (ac.code, ac.NAME, ac.ctype, ac.size))
	f.write('''
		default :
			DEBUG("UNKNOWN VMCODE: %d\\n", PCT_(pc));
			DEBUG_ASSERT(ctx == NULL);
			return;
		}
	}
}

/* ------------------------------------------------------------------------ */

''');

#############################################################################

def vm_macro(ac, label):
	m = 'VM_%s(ctx' % ac.type.upper()
	c = 1
	for a in ac.struct[1:]:
		if a == 'addr':
			m += ', pc += ((%s*)pc)->a%d, %s' % (ac.ctype, c, label)
		else:
			m += ', %s_(((%s*)pc)->a%d)' % (a, ac.ctype, c)
		c += 1
	m += ')'
	return m

def write_exec(f):
	CPROTO.append('void knh_VirtualMachineCode_exec(Ctx *ctx, Object **sf)')
	write_chapter(f, '[exec]')
	f.write('''
PUBLIC
void knh_VirtualMachineCode_exec0(Ctx *ctx, Object **sfp)
{
	register knh_vmc_t *pc = ((VirtualMachineCode*)((Method*)sfp[-1])->code)->code;
	L_HEAD:;
	switch(PCT_(pc)) {
''');
	for ac in TCODE:
		f.write('''\tcase %s :
#ifdef DEBUG_VM
		knh_VirtualMachineCode_%s__dump(ctx, (%s*)pc, 0, StdOut);
#endif
#ifdef VM_%s
		%s;
#else
		DEBUG("TODO: VM_%s");
#endif
		pc += %s;
		break;
''' % (ac.code, ac.code, ac.ctype, ac.type.upper(), vm_macro(ac, 'L_HEAD'), ac.type.upper(), ac.size))

	f.write('''
	}
	goto L_HEAD;
}
''')

	write_line(f)
	f.write('''
PUBLIC
void knh_VirtualMachineCode_exec(Ctx *ctx, Object **sfp)
{
	static void *globalMachineToJump[] = {''')
	c = 0
	for ac in TCODE:
		f.write('\n\t\t&&L_%s,' % ac.code)
		c += 1
	for n in range(256 - c):
		f.write('\n\t\t&&L_UNKNOWN,')

	f.write('''
		&&L_UNKNOWN
	};
	knh_vmc_t *pc =  ((VirtualMachineCode*)((Method*)sfp[-1])->code)->code;
	goto *globalMachineToJump[PCT_(pc)];

''')
	for ac in TCODE:
		f.write('''
	L_%s:;
#ifdef DEBUG_VMC
	knh_VirtualMachineCode_%s__dump(ctx, (%s*)pc, 0, StdOut);
#endif
#ifdef VM_%s
		%s;
#else
		DEBUG("TODO: VM_%s");
#endif
	pc += %s;
	goto *globalMachineToJump[PCT_(pc)];
''' % (ac.code, ac.NAME, ac.ctype, ac.type.upper(), vm_macro(ac, '*globalMachineToJump[PCT_(pc)]'), ac.type.upper(), ac.size))

	f.write('''
	L_UNKNOWN:;
	DEBUG("Broken code??");
	DEBUG_ASSERT(pc == NULL);
	return;
}
''')

	

#------------------------------------------------------------------------------

def gen_vm_c(bdir):
	fname = '%s/gen/konoha_vm_.c' % bdir
	f = open_c(fname, ['<konoha/konoha_dev.h>', '<konoha/konohac_asm_.h>'])
	write_label(f)
	write_dump(f)
	write_exec(f)
	close_c(f, fname)

	fname = '%s/gen/konohac_asm_.c' % bdir
	f = open_c(fname, ['<konoha/konoha_dev.h>', '<konoha/konohac_asm_.h>'])
	write_asm_c(f)
	close_c(f, fname)

	fname = '%s/include/konoha/konohac_asm_.h' % bdir
	f = open_h(fname, ['<konoha/konoha_dev.h>'])
	write_define_h(f)
	close_h(f, fname)

#------------------------------------------------------------------------------

if __name__ == '__main__':
	bdir = '..'
	gen_vm_c(bdir)

