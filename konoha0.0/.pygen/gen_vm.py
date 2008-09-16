#!/usr/bin/python
import os, sys
import copy
from pygenlib import *

#------------------------------------------------------------------------------

CPROTO = []
CPROTO_Compiler = []

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
			return 'knh_Compiler_labelId(ctx, o, %s)' % v
		return v

TPARAM = [
		  ASMType('i1', 'knhvm_i1_t', '''
	knh_write__i(ctx, w,  (int)%s);'''), 
		  ASMType('u1', 'knhvm_u1_t', '''
	knh_write__i(ctx, w,  (int)%s);'''),
		  ASMType('u2', 'knhvm_u2_t', '''
	knh_write__i(ctx, w,  (int)%s);'''), 
		  ASMType('ebp', 'knhvm_ebp_t', '''
	knh_printf(ctx, w, "ebp[%%d].o", (int)%s);'''), 
		  ASMType('sfp', 'knhvm_sfp_t', '''
	knh_printf(ctx, w, "sfp[%%d].o", (int)%s);'''), 
		  ASMType('ofp', 'knhvm_ofp_t', '''
	knh_printf(ctx, w, "ofp[%%d]", (int)%s);'''),
		  ASMType('OBJ', 'Object*', '''
	knh_format(ctx, w, METHODN__k, %s, KNH_NULL);'''),
		  ASMType('addr', 'knhvm_addr_t', '''
	knh_printf(ctx, w, "->%%p", (((char*)bw) + %s - off));'''),
		  ASMType('c2',   'knhvm_class_t', '''
	knh_write__type(ctx, w, (knh_type_t)%s);'''), 
		  ASMType('mn',   'knhvm_methodn_t', '''
	knh_write__mn(ctx, w, (knh_methodn_t)%s);'''), 
		  ASMType('e2',   'knhvm_expt_t', '''
	knh_write__expt(ctx, w, (knh_expt_t)%s);'''),
]

PARAMTBL = {}

for p in TPARAM:
	PARAMTBL[p.name] = p
	
#------------------------------------------------------------------------------

CODE_DATA = [
	['halt'],

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

	['push*', 'ebp'],
	['push*', 'sfp'],
	['push*', 'ofp'],
	['push*', 'OBJ'],
	['push__oidx', 'OBJ', 'u1'],
	
#	['puti',        'u2'],
#	['push__mn',    'mn'],
	['put_sysconst', 'u2'],
	['push_sysconst', 'u2'],
	
	['push__def',   'c2'],
    ['vargs',       'u2'],
	
	['shift',       'i1'],

    ['scall',       'u1'],
    ['nscall',    'u1'],
    ['call',        'u1', 'mn'],
    ['dcall',       'u1', 'mn'],

    ['new'  ,    'u2', 'u2', 'c2'],
 
 #   ['mcall',    'u1'],
 #   ['call_wm',  'u1', 'OBJ'],
 #   ['ncall_wm',  'u1', 'OBJ'],


    ['mt'  ,     'mn'],

	['smap',  'OBJ'],
	['smape', 'OBJ'],
	['map',   'c2'],
	['mape',  'c2'],
	['anymap',   'c2'],
	['anymape',  'c2'],

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

   ['jmp_iftnn*', 'addr', 'ebp'],
   ['jmp_iftnn*', 'addr', 'sfp'],
   ['jmp_iftnn*', 'addr', 'ofp'],
   ['jmp_iftnn__oidx', 'addr', 'OBJ', 'u1'],

   ['jmp_iffn*', 'addr', 'ebp'],
   ['jmp_iffn*', 'addr', 'sfp'],
   ['jmp_iffn*', 'addr', 'ofp'],
   ['jmp_iffn__oidx', 'addr', 'OBJ', 'u1'],

   ['jmp_ifnn*', 'addr', 'ebp'],
   ['jmp_ifnn*', 'addr', 'sfp'],
   ['jmp_ifnn*', 'addr', 'ofp'],
   ['jmp_ifnn__oidx', 'addr', 'OBJ', 'u1'],

   ['next', 'addr', 'sfp', 'sfp'],
   ['mapnext',  'addr', 'sfp', 'sfp', 'c2'],
   ['smapnext', 'addr', 'sfp', 'sfp', 'OBJ'],

   ['try_begin',   'addr', 'sfp', 'sfp'],
   ['try_end',     'sfp'],
   ['catch', 'addr', 'e2', 'sfp'], 

   ['throw*', 'ebp'],
   ['throw*', 'sfp'],
   ['throw*', 'OBJ'],

   ['print*', 'u2', 'OBJ', 'mn', 'ebp'],
   ['print*', 'u2', 'OBJ', 'mn', 'sfp'],
   ['print*', 'u2', 'OBJ', 'mn', 'ofp'],
   ['print*', 'u2', 'OBJ', 'mn', 'OBJ'],
   ['print__oidx', 'u2', 'OBJ', 'mn', 'OBJ', 'u1'],

 #  ['diagnose', 'u1'], 
 #  ['stackdump'],
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
	knhvm_opcode_t code;''')
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
	knhvm_opcode_t code;''')
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

	def asmv_argv_(self):
		t = ''
		c = 1;
		for a in self.struct[1:-1]:
			t += ', %s a%d' % (PARAMTBL[a].ptype, c)
			c += 1
		t += ', knh_asmv_t v'
		return t

	def asmv_argv(self):
		t = ''
		c = 1;
		for a in self.struct[1:-1]:
			t += ', %s a%d' % (PARAMTBL[a].ptype, c)
			c += 1
		t += ', Term *v'
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
		write_define(f, ac.code, '((knhvm_opcode_t)%d)' % c, 40)
		c += 1

	write_line(f)
	write_ifndef(f, 'METHODN__k', 'METHODN__s', 40)
	write_line(f)

	for p in CPROTO:
		f.write(p + ';\n')

	f.write('''
#ifdef CLASS_Compiler
''')
	for p in CPROTO_Compiler:
		f.write(p + ';\n')
	f.write('''
#endif/*CLASS_Compiler*/
''')
	write_line(f)

	for ac in TCODE:
		ac.write_ctype(f)
		write_line(f)

#------------------------------------------------------------------------------

def write_asm_each(f, ac):
	rtype = 'void'
	index = 0
#	if len(ac.struct) > 1 and PARAMTBL[ac.struct[-1]].isObject(): 
#		rtype = 'Object **'
#		index = len(ac.struct) - 1
	
	CPROTO_Compiler.append('%s KNH_ASM_%s(Ctx *ctx, Compiler *o%s)' % (rtype, ac.NAME, ac.asm_argv()))
	f.write('''
%s KNH_ASM_%s(Ctx *ctx, Compiler *o%s)
{
	if(!knh_Compiler_isStopped(o)) {
		%s *bw = (%s*)knh_Compiler_asmmalloc(ctx, o, %s);
		bw->code = %s;''' % (rtype, ac.NAME, ac.asm_argv(), ac.ctype, ac.ctype, ac.size, ac.code))
	c = 1;
	for a in ac.struct[1:]:
		f.write('''
		bw->a%d = %s;''' % (c, PARAMTBL[a].asm('a%d' % c)))
		if(PARAMTBL[a].isObject()):
			f.write('''
		knh_Object_RCinc(bw->a%d);''' % c)
			if index == c:
				f.write('''
		return &(bw->a%d);''' % c)
		c += 1
	f.write('''
	}
}
''')
	write_line(f)


def write_asm_eval(f, acl):
	ac0 = acl[0]
	TYPE = ac0.type.upper()
	CPROTO_Compiler.append('void KNH_ASM_%s(Ctx *ctx, Compiler *o%s)' % (ac0.type.upper(), ac0.asmv_argv()))
	EBP = ''
	if not TYPE.startswith('PUSH'):
		EBP = 'KNH_ASM_%s__ebp(ctx, o%s, 0)' % (TYPE, ac0.asm_name())
	f.write('''
void KNH_ASM_%s(Ctx *ctx, Compiler *o%s)
{''' % (ac0.type.upper(), ac0.asmv_argv()))
	f.write('''
	if(IS_Token((Token*)v)) {
		Token *tk = (Token*)v;
#ifdef ASMC_%s__OBJ
		if(SP(tk)->tt == TT_CONST || SP(tk)->tt == TT_MTDMPR) {
			KNH_ASM_%s__OBJ(ctx, o%s, DP(tk)->data);
			return;
		}
#endif/*ASMC_%s__OBJ*/''' % (TYPE, TYPE, ac0.asm_name(), TYPE))
	f.write('''
#ifdef ASMC_%s__SFP
		if(SP(tk)->tt == TT_SFPIDX) {
			KNH_ASM_%s__sfp(ctx, o%s, DP(tk)->index);
			return;
		}
#endif/*ASMC_%s__SFP*/''' % (TYPE, TYPE, ac0.asm_name(), TYPE))
	f.write('''
#ifdef ASMC_%s__OFP
		if(SP(tk)->tt == TT_FLDIDX) {
			KNH_ASM_%s__ofp(ctx, o%s, DP(tk)->index);
			return;
		}
#endif/*ASMC_%s__OFP*/''' % (TYPE, TYPE, ac0.asm_name(), TYPE))
	f.write('''
#ifdef ASMC_%s__OIDX
		if(SP(tk)->tt == TT_OBJIDX) {
			KNH_ASM_%s__OIDX(ctx, o%s, DP(tk)->data, DP(tk)->index);
			return;
		}
#endif/*ASMC_%s__OIDX*/''' % (TYPE, TYPE, ac0.asm_name(), TYPE))
	f.write('''
#ifdef ASMC_%s__EBP
		if(SP(tk)->tt == TT_EBPIDX) {
			KNH_ASM_%s__ebp(ctx, o%s, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_%s__ebp(ctx, o%s, 0);
			return;
		}
#endif/*ASMC_%s__EBP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			%s;
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Compiler_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));
''' % (TYPE, TYPE, ac0.asm_name(), TYPE, ac0.asm_name(), TYPE, EBP))
	if TYPE.startswith('PUSH'):
		f.write('''
#ifdef ASMC_%s__EBP
		/*KNH_ASM_%s__ebp(ctx, o%s, 0); CALLED */
		return;
#else
		DBG_P("unsupported stmt stt=%%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_%s__EBP*/
	}
}
''' % (TYPE, TYPE, ac0.asm_name(), TYPE))
	else:
		f.write('''
#ifdef ASMC_%s__EBP
		KNH_ASM_%s__ebp(ctx, o%s, 0);
		return;
#else
		DBG_P("unsupported stmt stt=%%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_%s__EBP*/
	}
}
''' % (TYPE, TYPE, ac0.asm_name(), TYPE))
		
	write_line(f)

def write_asm_c(f):
	write_chapter(f, '[Compiler]')
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
	CPROTO.append('void knh_Compiler_remapAddress(Ctx *ctx, Compiler *o)')
	f.write('''

void knh_Compiler_rewriteAddress(Ctx *ctx, Compiler *o, knh_asmc_jmp_t *bw)
{
	//DBG_P("label: id=%d", knh_KLRCode_uread_short(pc));
	String *name = knh_DictIdx_get(DP(o)->labelIdDictIdx, bw->a1);
	KNH_ASSERT(IS_NOTNULL(name));
	knhvmc_t *pa = (knhvmc_t*)knh_DictSet_get__b(DP(o)->labelAddrDictSet, knh_String_tobytes(name));
	if(pa == NULL) {
		TODO();
		DBG_P("Asm!!: Unknown Label '%s'", knh_String_tochar(name));
	}else {
		bw->a1 = (knh_short_t)(pa - (knhvmc_t*)bw);
	}
}

/* ------------------------------------------------------------------------ */

void knh_Compiler_remapAddress(Ctx *ctx, Compiler *o)
{
	knhvmc_t *pc = (knhvmc_t*)knh_Bytes_tochar(DP(o)->elf);
	knhvmc_t *tail = pc + knh_Bytes_size(DP(o)->elf);
	while(pc < tail) {
		switch(PCT_(pc)) {
''');
	for ac in TCODE:
		if len(ac.struct)>1 and ac.struct[1] == 'addr' :
			f.write('''\t\tcase %s :
			knh_Compiler_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
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
			DBG_P("UNKNOWN VMCODE: %d\\n", PCT_(pc));
			KNH_ASSERT(ctx == NULL);
			return;
		}
	}
}
''')

	write_chapter(f, '[vmc]')

	CPROTO.append('void knh_KLRCode_utraverse(Ctx *ctx, knh_bytes_t vmc, f_traverse gc)')
	f.write('''
void knh_KLRCode_utraverse(Ctx *ctx, knh_bytes_t vmc, f_traverse gc)
{
	knhvmc_t *pc = (knhvmc_t*)vmc.buf;
	knhvmc_t *tail = vmc.buf + vmc.len;
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
			DBG_P("UNKNOWN VMCODE: %d\\n", PCT_(pc));
			KNH_ASSERT(ctx == NULL);
			return;
		}
	}
}
''')


#------------------------------------------------------------------------------

def write_dump_each(f, ac):
#	m = '\tVM_%s(ctx' % ac.NAME
	f.write('''
void knh_KLRCode_%s__dump(Ctx *ctx, %s *bw, int off, OutputStream *w, Method *mtd)
{
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, (knhvmc_t*)bw);
	}
	knh_putc(ctx, w, ' ');
	if(line == 0) {
		knh_printf(ctx, w, "[%%p]", ((knhvmc_t*)bw) - off);
	}else{
		knh_printf(ctx, w, "[%%d:%%p]", line, ((knhvmc_t*)bw) - off);
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
	knh_write_EOL(ctx, w);
}
''')
	write_line(f)

def write_dump(f):
	write_chapter(f, '[dump]')

	for ac in TCODE:
		write_dump_each(f, ac)

	write_line(f)
	CPROTO.append('void knh_KLRCode__dump_(Ctx *ctx, KLRCode *o, OutputStream *w, Any *m)')
	f.write('''

PUBLIC
void knh_KLRCode__dump_(Ctx *ctx, KLRCode *o, OutputStream *w, Any *m)
{
	knh_bytes_t vmc = knh_KLRCode_tobytes(o);
	knhvmc_t *pc = (knhvmc_t*)vmc.buf;
	knhvmc_t *tail = pc + vmc.len;	
	int off = (int)pc;
	while(pc < tail) {
		switch(PCT_(pc)) {
''');
	for ac in TCODE:
		f.write('''\t\tcase %s :
			knh_KLRCode_%s__dump(ctx, (%s*)pc, off, w, (Method*)m);
			pc += %s;
			break;
''' % (ac.code, ac.NAME, ac.ctype, ac.size))
	f.write('''
		default :
			DBG_P("UNKNOWN VMCODE: %d\\n", PCT_(pc));
			KNH_ASSERT(ctx == NULL);
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
			m += ', pc += ((const %s*)pc)->a%d, %s' % (ac.ctype, c, label)
		else:
			m += ', %s_(((const %s*)pc)->a%d)' % (a, ac.ctype, c)
		c += 1
	m += ')'
	return m

def write_exec(f):
	CPROTO.append('METHOD knh_KLRCode_exec(Ctx *ctx, knh_sfp_t *sfp)')
	write_chapter(f, '[exec]')
	f.write('''
#ifndef KNH_CC_LABELPTR
METHOD knh_KLRCode_exec(Ctx *ctx, knh_sfp_t *sfp)
{
	register knhvmc_t *pc = DP((KLRCode*)DP(sfp[-1].mtd)->code)->code;
	L_HEAD:;
	switch(PCT_(pc)) {
''');
	for ac in TCODE:
		f.write('''\tcase %s :
#ifdef DBG_P_VM
		knh_KLRCode_%s__dump(ctx, (%s*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_%s
		%s;
#else
		DBG_P("TODO: VM_%s");
#endif
		pc += %s;
		break;
''' % (ac.code, ac.code, ac.ctype, ac.type.upper(), vm_macro(ac, 'L_HEAD'), ac.type.upper(), ac.size))

	f.write('''
	}
	goto L_HEAD;
}
#endif
''')

	write_line(f)
	f.write('''
#ifdef KNH_CC_LABELPTR
METHOD knh_KLRCode_exec(Ctx *ctx, knh_sfp_t *sfp)
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
	knhvmc_t *pc =  DP((KLRCode*)DP(sfp[-1].mtd)->code)->code;
	goto *globalMachineToJump[PCT_(pc)];

''')
	for ac in TCODE:
		f.write('''
	L_%s:;
#ifdef DBG_P_VMC
	knh_KLRCode_%s__dump(ctx, (%s*)pc, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_%s
		%s;
#else
		DBG_P("TODO: VM_%s");
#endif
	pc += %s;
	goto *globalMachineToJump[PCT_(pc)];
''' % (ac.code, ac.NAME, ac.ctype, ac.type.upper(), vm_macro(ac, '*globalMachineToJump[PCT_(pc)]'), ac.type.upper(), ac.size))

	f.write('''
	L_UNKNOWN:;
	DBG_P("Broken code??");
	KNH_ASSERT(pc == NULL);
	KNH_THROWs(ctx, "Halt!!");
}
#endif
''')

#------------------------------------------------------------------------------

def gen_vm_c(bdir):
	fname = '%s/konoha/gen/konoha_vm_.c' % bdir
	f = open_c(fname, ['<konoha/konoha_dev.h>', '<konoha/gen/konohac_asm_.h>'])
	write_label(f)
	write_dump(f)
	write_exec(f)
	close_c(f, fname)

	fname = '%s/konoha/gen/konohac_asm_.c' % bdir
	f = open_c(fname, ['<konoha/konoha_dev.h>', '<konoha/gen/konohac_asm_.h>'])
	write_asm_c(f)
	close_c(f, fname)

	fname = '%s/include/konoha/gen/konohac_asm_.h' % bdir
	f = open_h(fname, ['<konoha/konoha_dev.h>'])
	write_define_h(f)
	close_h(f, fname)

#------------------------------------------------------------------------------

if __name__ == '__main__':
	bdir = '..'
	gen_vm_c(bdir)

