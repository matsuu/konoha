#!/usr/bin/python
import os, sys
import copy
from pygenlib import *

#------------------------------------------------------------------------------

CPROTO = []
CPROTO_Asm = []

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
			return 'knh_Asm_labelId(ctx, o, %s)' % v
		return v

TPARAM = [
		  ASMType('i1', 'knhvm_i1_t', '''
	knh_write__i(ctx, w,  (int)%s);'''), 
		  ASMType('u1', 'knhvm_u1_t', '''
	knh_write__i(ctx, w,  (int)%s);'''),
		  ASMType('u2', 'knhvm_u2_t', '''
	knh_write__i(ctx, w,  (int)%s);'''), 
		  ASMType('esp', 'knhvm_esp_t', '''
	knh_printf(ctx, w, "esp[%%d].o", (int)%s);'''), 
		  ASMType('sfp', 'knhvm_sfp_t', '''
	knh_printf(ctx, w, "sfp[%%d].o", (int)%s);'''), 
		  ASMType('ofp', 'knhvm_ofp_t', '''
	knh_printf(ctx, w, "ofp[%%d]", (int)%s);'''),
		  ASMType('OBJ', 'Object*', '''
	knh_format(ctx, w, METHODN__k, %s, KNH_NULL);'''),
		  ASMType('addr', 'knhvm_addr_t', '''
	knh_printf(ctx, w, "goto->%%p", (%s - off));'''),
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

	['ret*',  'esp'],
	['ret*',  'sfp'],
	['ret*',  'ofp'],
	['ret*',  'OBJ'],
	['ret__oidx', 'OBJ', 'u1'],

	['move*', 'esp', 'esp'],
	['move*', 'esp', 'sfp'],
	['move*', 'esp', 'ofp'],
	['move*', 'esp', 'OBJ'],
	['move__oidx', 'esp', 'OBJ', 'u1'],

	['movs*', 'sfp', 'esp'],
	['movs*', 'sfp', 'sfp'],
	['movs*', 'sfp', 'ofp'],
	['movs*', 'sfp', 'OBJ'],
	['movs__oidx', 'sfp', 'OBJ', 'u1'],

	['movo*', 'ofp', 'esp'],
	['movo*', 'ofp', 'sfp'],
	['movo*', 'ofp', 'ofp'],
	['movo*', 'ofp', 'OBJ'],
	['movo__oidx', 'ofp', 'OBJ', 'u1'],

	['movoi*', 'OBJ', 'ofp', 'esp'],
	['movoi*', 'OBJ', 'ofp', 'sfp'],
	['movoi*', 'OBJ', 'ofp', 'ofp'],
	['movoi*', 'OBJ', 'ofp', 'OBJ'],
	['movoi__oidx', 'OBJ', 'u1', 'OBJ', 'u1'],

	['movsfp_ifnul', 'u1', 'OBJ'],

	['push*', 'esp'],
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

    ['mt'  ,     'mn'],
    ['mt__fmt',    'mn', 'OBJ'], 

	['smap',  'OBJ'],
	['smape', 'OBJ'],
	['map',   'c2'],
	['mape',  'c2'],
	['anymap',   'c2'],
	['anymape',  'c2'],

	['map2', 'c2'],
	['map2e', 'c2'],

	['typechk*', 'c2', 'esp'],
	['typechk*', 'c2', 'sfp'],
	['typechk*', 'c2', 'ofp'],
	['typechk*', 'c2', 'OBJ'],  # TO simplify compiler
	['typechk__oidx', 'c2', 'OBJ', 'u1'],

    ['nullchk*',    'esp'],
    ['nullchk*',    'sfp'],
    ['nullchk*',    'ofp'],
    ['nullchk*',    'OBJ'],    # TO simplify compiler
    ['nullchk__oidx', 'OBJ', 'u1'],

   ['jmp',    'addr'],
   ['skip',   'addr'],

   ['jmp_ift*', 'addr', 'esp'],
   ['jmp_ift*', 'addr', 'sfp'],
   ['jmp_ift*', 'addr', 'ofp'],
   ['jmp_ift__oidx', 'addr', 'OBJ', 'u1'],

   ['jmp_iff*', 'addr', 'esp'],
   ['jmp_iff*', 'addr', 'sfp'],
   ['jmp_iff*', 'addr', 'ofp'],
   ['jmp_iff__oidx', 'addr', 'OBJ', 'u1'],

   ['jmp_ifn*', 'addr', 'esp'],
   ['jmp_ifn*', 'addr', 'sfp'],
   ['jmp_ifn*', 'addr', 'ofp'],
   ['jmp_ifn__oidx', 'addr', 'OBJ', 'u1'],

   ['jmp_ifnn*', 'addr', 'esp'],
   ['jmp_ifnn*', 'addr', 'sfp'],
   ['jmp_ifnn*', 'addr', 'ofp'],
   ['jmp_ifnn__oidx', 'addr', 'OBJ', 'u1'],

   ['next', 'addr', 'sfp', 'sfp'],
   ['mapnext',  'addr', 'sfp', 'sfp', 'c2'],
   ['smapnext', 'addr', 'sfp', 'sfp', 'OBJ'],

   ['try', 'addr', 'sfp', 'sfp'],
   ['try_wc', 'addr', 'sfp'],
   ['try_end', 'sfp'],
   ['catch', 'addr', 'OBJ', 'sfp'], 
   ['throw_again', 'sfp'],

   ['throw*', 'esp'],
   ['throw*', 'sfp'],
   ['throw*', 'OBJ'],

   ['print*', 'u2', 'OBJ', 'mn', 'esp'],
   ['print*', 'u2', 'OBJ', 'mn', 'sfp'],
   ['print*', 'u2', 'OBJ', 'mn', 'ofp'],
   ['print*', 'u2', 'OBJ', 'mn', 'OBJ'],
   ['print__oidx', 'u2', 'OBJ', 'mn', 'OBJ', 'u1'],

 #  ['diagnose', 'u1'], 
 #  ['stackdump'],
   ['iadd'], ['isub'], ['ilt'],
   ['init'], # for code threading 
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
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/''')
		f.write('''
	knhvm_opcode_t opcode;''')
		c = 0
		for a in self.struct[1:]:
			c += 1
			if a == "addr" : 
				f.write('''
#ifdef KNH_USING_THREADEDCODE
	void *jumpaddr;
#endif/*KNH_USING_THREADEDCODE*/
	union {
		knh_int_t a1;  /* oldname */
		knhvmc_t *jumppc;
	};''')
				continue
			if PARAMTBL[a].isObject(): continue
			f.write('''
	%s a%d;''' % (PARAMTBL[a].ctype, c))
		c = 0
		for a in self.struct[1:]:
			c += 1
			if a == "addr" : continue
			if not PARAMTBL[a].isObject(): continue
			f.write('''
	%s a%d;''' % (PARAMTBL[a].ctype, c))
		f.write('''
	void *nextaddr;
} %s;
''' % self.ctype)

		f.write('''
#define %s  (sizeof(%s)-sizeof(void*))
''' % (self.size, self.ctype))
	
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
#ifdef CLASS_Asm
''')
	for p in CPROTO_Asm:
		f.write(p + ';\n')
	f.write('''
#endif/*CLASS_Asm*/
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
	
	CPROTO_Asm.append('%s KNH_ASM_%s(Ctx *ctx, Asm *o%s)' % (rtype, ac.NAME, ac.asm_argv()))
	f.write('''
%s KNH_ASM_%s(Ctx *ctx, Asm *o%s)
{
	if(!knh_Asm_isStopped(o)) {
		%s *bw = (%s*)knh_Asm_asmmalloc(ctx, o, %s);
		bw->opcode = %s;''' % (rtype, ac.NAME, ac.asm_argv(), ac.ctype, ac.ctype, ac.size, ac.code))
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
	CPROTO_Asm.append('void KNH_ASM_%s(Ctx *ctx, Asm *o%s)' % (ac0.type.upper(), ac0.asmv_argv()))
	ESP = ''
	if not TYPE.startswith('PUSH'):
		ESP = 'KNH_ASM_%s__esp(ctx, o%s, 0)' % (TYPE, ac0.asm_name())
	f.write('''
void KNH_ASM_%s(Ctx *ctx, Asm *o%s)
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
#ifdef ASMC_%s__ESP
		if(SP(tk)->tt == TT_ESPIDX) {
			KNH_ASM_%s__esp(ctx, o%s, DP(tk)->index);
			return;
		}
		if(SP(tk)->tt == TT_ASIS) {
			KNH_ASM_%s__esp(ctx, o%s, 0);
			return;
		}
#endif/*ASMC_%s__ESP*/
		if(SP(tk)->tt == TT_SYSCONST) {
			KNH_ASM_PUSH_SYSCONST(ctx, o, DP(tk)->index);
			%s;
			return;
		}
		if(SP(tk)->tt == TT_ERR) {
			KNH_ASSERT(IS_bString(DP(tk)->data));
			KNH_ASM_THROW__OBJ(ctx, o, DP(tk)->data);
			knh_Asm_setStopped(o, 1);
			return;
		}
		DBG_P("unsupported token tt=%%s", knh_token_tochar(SP(tk)->tt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
	}else {
		KNH_ASSERT(IS_Stmt((Stmt*)v));
''' % (TYPE, TYPE, ac0.asm_name(), TYPE, ac0.asm_name(), TYPE, ESP))
	if TYPE.startswith('PUSH'):
		f.write('''
#ifdef ASMC_%s__ESP
		/*KNH_ASM_%s__esp(ctx, o%s, 0); CALLED */
		return;
#else
		DBG_P("unsupported stmt stt=%%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_%s__ESP*/
	}
}
''' % (TYPE, TYPE, ac0.asm_name(), TYPE))
	else:
		f.write('''
#ifdef ASMC_%s__ESP
		KNH_ASM_%s__esp(ctx, o%s, 0);
		return;
#else
		DBG_P("unsupported stmt stt=%%s", knh_stmt_tochar(DP((Stmt*)v)->stt));
		KNH_ASSERT(ctx == NULL); /* stop here!!*/
#endif/*ASMC_%s__ESP*/
	}
}
''' % (TYPE, TYPE, ac0.asm_name(), TYPE))
		
	write_line(f)

def write_asm_c(f):
	write_chapter(f, '[Asm]')
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
#define PCT_(pc)    (((knh_asmc_nop_t*)pc)->opcode)
''')
	write_line(f)
	write_chapter(f, '[label]')
	CPROTO.append('void knh_Asm_remapAddress(Ctx *ctx, Asm *o)')
	f.write('''

void knh_Asm_rewriteAddress(Ctx *ctx, Asm *o, knh_asmc_jmp_t *bw)
{
	//DBG_P("label: id=%d", knh_KLRCode_uread_short(pc));
	String *name = knh_DictIdx_get(ctx, DP(o)->labelIdDictIdx, bw->a1);
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

void knh_Asm_remapAddress(Ctx *ctx, Asm *o)
{
	knhvmc_t *pc = (knhvmc_t*)knh_Bytes_tochar(DP(o)->elf);
	knhvmc_t *tail = pc + knh_Bytes_size(DP(o)->elf);
	while(pc < tail) {
		switch(PCT_(pc)) {
''');
	for ac in TCODE:
		if len(ac.struct)>1 and ac.struct[1] == 'addr' :
			f.write('''\t\tcase %s :
			knh_Asm_rewriteAddress(ctx, o, (knh_asmc_jmp_t*)pc);
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

	CPROTO.append('void knh_KLRCode_utraverse(Ctx *ctx, knh_bytes_t vmc, knh_ftraverse gc)')
	f.write('''
void knh_KLRCode_utraverse(Ctx *ctx, knh_bytes_t vmc, knh_ftraverse gc)
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
	knh_write__s(ctx, w, "%s");
	knh_printf(ctx, w, "(%%d)", bw->opcode); '''  % (ac.NAME, ac.ctype, ac.NAME.lower()))
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
	CPROTO.append('void knh_KLRCode__dumpmtd(Ctx *ctx, KLRCode *o, OutputStream *w, Method *mtd)')
	f.write('''

void knh_KLRCode__dumpmtd(Ctx *ctx, KLRCode *o, OutputStream *w, Method *mtd)
{
	knh_bytes_t vmc = knh_KLRCode_tobytes(o);
	knhvmc_t *pc = (knhvmc_t*)vmc.buf;
	knhvmc_t *tail = pc + vmc.len;	
//	int off = (int)pc;
	while(pc < tail) {
		switch(PCT_(pc)) {
''');
	for ac in TCODE:
		f.write('''\t\tcase %s :
			knh_KLRCode_%s__dump(ctx, (%s*)pc, 0 /*off*/, w, mtd);
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
			m += ', pc = asmcode->jumppc, %s' % (label)
		else:
			m += ', %s_(asmcode->a%d)' % (a, c)
		c += 1
	m += ')'
	return m

def write_exec(f):
	CPROTO.append('METHOD knh_KLRCode_exec(Ctx *ctx, knh_sfp_t *sfp)')
	CPROTO.append('knhvmc_t* KNH_CC_FASTCALL konohavm(Ctx *ctx, knh_sfp_t *sfp, knhvmc_t *pc_start)')
	CPROTO.append('void knhvmc_codethreading(Ctx *ctx, knhvmc_t *pc, void **codeaddr)')
	write_chapter(f, '[exec]')

	f.write('''
/* ------------------------------------------------------------------------ */

void knhvmc_codethreading(Ctx *ctx, knhvmc_t *pc, void **codeaddr)
{
	while(1) {
		knh_asmc_jmp_t *asmc = (knh_asmc_jmp_t*)pc;
		KNH_ASSERT(asmc->opcode <= ASMC_NOP);
#ifdef KNH_USING_THREADEDCODE
		DBG2_P("opcode=%d %p %p", asmc->opcode, &asmc->codeaddr, &asmc->nextaddr);
#endif/*KNH_USING_THREADEDCODE*/
		if(asmc->opcode == ASMC_HALT) {
#ifdef KNH_USING_THREADEDCODE
			asmc->codeaddr = codeaddr[asmc->opcode];
#endif/*KNH_USING_THREADEDCODE*/
			return;
		}
#ifdef KNH_USING_THREADEDCODE
		asmc->codeaddr = codeaddr[asmc->opcode];
#endif/*KNH_USING_THREADEDCODE*/
		switch(asmc->opcode) {
''');
	for ac in TCODE:
		if len(ac.struct)>1 and ac.struct[1] == 'addr' :
			f.write('''\t\tcase %s : {
			asmc->jumppc = pc + asmc->a1;
#ifdef KNH_USING_THREADEDCODE
			asmc->jumpaddr = codeaddr[((knh_asmc_jmp_t*)(asmc->jumppc))->opcode];
#endif/*KNH_USING_THREADEDCODE*/
			pc += %s; 
			break;
		}
''' % (ac.code, ac.size))
		else :
			f.write('''\t\tcase %s :  {
			pc += %s; 
			break;
		}
''' % (ac.code, ac.size))
	f.write('''
		default :
			DBG_P("UNKNOWN VMCODE: %d\\n", PCT_(pc));
			KNH_ASSERT(pc == NULL);
			return;
		}
	}
}
''')

	f.write('''
#ifndef KNH_USING_THREADEDCODE
METHOD knh_KLRCode_exec(Ctx *ctx, knh_sfp_t *sfp)
/*knhvmc_t* KNH_CC_FASTCALL konohavm(Ctx *ctx, knh_sfp_t *sfp, knhvmc_t *pc_start)*/
{
	static void **globalMachineToJump = NULL;
	register knhvmc_t *pc = DP((KLRCode*)DP(sfp[-1].mtd)->code)->code;
	//register knhvmc_t *pc = pc_start;
	
	L_HEAD:;
	switch(PCT_(pc)) {
''');
	for ac in TCODE:
		f.write('''\tcase %s :
		{
			const %s *asmcode = (%s*)pc;
#ifdef DBG_P_VM
			knh_KLRCode_%s__dump(ctx, asmcode, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_%s
			%s;
#else
			DBG_P("TODO: VM_%s");
#endif
			pc += %s;
			goto L_HEAD;
		}
''' % (ac.code, ac.ctype, ac.ctype, ac.code, ac.type.upper(), vm_macro(ac, 'L_HEAD'), ac.type.upper(), ac.size))

	f.write('''
	}
	goto L_HEAD;
}
#endif/*KNH_USING_THREADEDCODE*/
''')

	write_line(f)
	f.write('''
#ifdef KNH_USING_THREADEDCODE
METHOD knh_KLRCode_exec(Ctx *ctx, knh_sfp_t *sfp)
/* knhvmc_t* KNH_CC_FASTCALL konohavm(Ctx *ctx, knh_sfp_t *sfp, knhvmc_t *pc_start) */
{
	static void *globalMachineToJump[] = {''')
	c = 0
	for ac in TCODE:
		f.write('\n\t\t&&L_%s,' % ac.code)
		c += 1
#	for n in range(256 - c):
#		f.write('\n\t\t&&L_ASMC_HALT,')

	f.write('''
		&&L_ASMC_HALT
	};
	
	register knhvmc_t *pc =  DP((KLRCode*)DP(sfp[-1].mtd)->code)->code;
	//register knhvmc_t *pc =  pc_start;
	//goto *(((knh_asmc_jmp_t*)pc)->codeaddr);
	goto *globalMachineToJump[PCT_(pc)]; /* this is needed to init */

''')
	for ac in TCODE:
		f.write('''
	L_%s:; {
		const %s *asmcode = (%s*)pc;
#ifdef DBG_P_VMC
		knh_KLRCode_%s__dump(ctx, asmcode, 0, KNH_STDOUT, KNH_NULL);
#endif
#ifdef VM_%s
		%s;
#else
		DBG_P("TODO: VM_%s");
#endif
		pc += %s;
		goto *(asmcode->nextaddr);
	}
''' % (ac.code, ac.ctype, ac.ctype, ac.NAME, ac.type.upper(), vm_macro(ac, '*(asmcode->jumpaddr)'), ac.type.upper(), ac.size))

	f.write('''
}
#endif

/*******
METHOD knh_KLRCode_exec(Ctx *ctx, knh_sfp_t *sfp)
{
	konohavm(ctx, sfp, DP((KLRCode*)DP(sfp[-1].mtd)->code)->code);
}
*******/

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

