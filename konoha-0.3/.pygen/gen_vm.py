#!/usr/bin/python
import os, sys
import copy
from pygenlib import *

#------------------------------------------------------------------------------

INSTRUCTIONS = """
HALT

##MOV
MOVa sfi sfi
MOVn sfi sfi
MOVo sfi OBJ
MOVx sfi sfx
MOVDEF sfi cid
MOVSYS sfi ushort

XMOVs sfx sfi
XMOVo sfx OBJ
XMOVx sfx sfx
XMOVDEF sfx cid
XMOVSYS sfx ushort

SWAP  sfi sfi

PINIo sfi OBJ

SETESP sfi
CHECKESP sfi
RET
RETn sfi sfi
RETa sfi sfi
RETo sfi OBJ
RETx sfi sfx

BOX sfi cid
BOXnc sfi cid
NNBOX sfi cid
NNBOXnc sfi cid
UNBOX sfi

ISNULL sfi
ISNULLx sfx
ISTYPE sfi cid
ISNNTYPE sfi type

FCALL sfi ushort sfi mtd
SCALL sfi ushort mtd 
AINVOKE sfi ushort mtd
CALL  sfi ushort mn 
ACALL sfi ushort mn
NEW   sfi flag cid ushort mtd

TOSTR      sfi mn
TOSTRf     sfi mn OBJ

SMAP   sfi mpr
SMAPnc   sfi mpr
MAP    sfi cid
MAPnc   sfi cid
AMAP   sfi cid
NNMAP   sfi cid

#MAP2   cid

JMP     addr
#SKIP    addr
bJIFT    addr sfi
bJIFF    addr sfi
bJIFF_LOOP addr sfi
JIFNUL  addr sfi
JIFNN   addr sfi

NEXT addr sfi sfi sfi
INEXT addr cid sfi sfi sfi
MAPNEXT addr cid sfi sfi sfi
SMAPNEXT addr sfi sfi sfi OBJ

TRY     addr sfi
TRYEND  sfi
CATCH   addr sfi sfi OBJ

THROW   sfi 
THROWs  OBJ 
THROW_AGAIN sfi

P  flag mn sfi
PMSG flag OBJ


iCAST sfi
inCAST sfi
fCAST sfi
fnCAST sfi

bNOT sfi sfi

iNEG sfi sfi
iADD sfi sfi sfi
iADDn sfi sfi integer
iSUB sfi sfi sfi
iSUBn sfi sfi integer
iMUL sfi sfi sfi
iMULn sfi sfi integer
iDIV  sfi sfi sfi
iDIVn  sfi sfi integer
iMOD  sfi sfi sfi
iMODn  sfi sfi integer

iEQ   sfi sfi sfi
iEQn  sfi sfi integer
iNEQ   sfi sfi sfi
iNEQn  sfi sfi integer

iLT   sfi sfi sfi
iLTn   sfi sfi integer
iLTE  sfi sfi sfi
iLTEn  sfi sfi integer
iGT   sfi sfi sfi
iGTn  sfi sfi integer
iGTE  sfi sfi sfi
iGTEn  sfi sfi integer

fNEG sfi sfi
fADD sfi sfi sfi
fADDn sfi sfi float
fSUB sfi sfi sfi
fSUBn sfi sfi float
fMUL sfi sfi sfi
fMULn sfi sfi float
fDIV  sfi sfi sfi
fDIVn  sfi sfi float

fEQ   sfi sfi sfi
fEQn  sfi sfi float
fNEQ   sfi sfi sfi
fNEQn  sfi sfi float

fLT   sfi sfi sfi
fLTn   sfi sfi float
fLTE  sfi sfi sfi
fLTEn  sfi sfi float
fGT   sfi sfi sfi
fGTn  sfi sfi float
fGTE  sfi sfi sfi
fGTEn  sfi sfi float

INITCODE  sfi
NOP
"""

class KCODE:
	def __init__(self, c, t):
		self.tokens = t.split()
		self.name = self.tokens[0]
		self.NAME = self.name.upper()
		self.opcode = c
		self.OPCODE = 'OPCODE_%s' % self.NAME
		self.SIZE = 'OPSIZE_%s' % self.NAME
		self.OPLABEL = 'L_%s' % self.NAME
		self.ctype = 'klr_%s_t' % self.name.lower()
	
	def hasObject(self):
		for a in self.tokens[1:]:
			ctype = getctype(a)
			if ctype == "Object*": return True
		return False
		
	def args(self):
		args = ''
		c = 1
		for a in self.tokens[1:]:
			ctype = getctype(a)
			args = args + ',%s a%d' % (ctype, c)
			c += 1
		return args

KCODE_LIST = []

c = 0
for line in INSTRUCTIONS.split('\n'):
	if line.startswith("#") or len(line) == 0: continue
	KCODE_LIST.append(KCODE(c, line))
	c += 1

#------------------------------------------------------------------------------

CTYPE = {
	'sfi' : 'knh_sfi_t', 
	'sfx' : 'knh_sfx_t',
	'boolean': 'knh_boolean_t',
	'integer': 'knh_int_t',
	'float': 'knh_float_t',
	'cid': 'knh_class_t',
	'type': 'knh_type_t',
	'mn': 'knh_methodn_t',
	'flag': 'knh_flag_t',
	'addr': 'knh_labelid_t',
	'short': 'knh_short_t',
	'ushort': 'knh_ushort_t',
}

def getctype(a):
	if CTYPE.has_key(a): return CTYPE[a]
	return 'Object*'

def getfmt(a):
	if CTYPE.has_key(a): return "knh_write__%s(ctx, w, %%s);" % a
	return "knh_write__OBJ(ctx, w, %s);"

def write_KCODE_h(f, kc):
	f.write('''
#define %s ((knh_opcode_t)%d)''' % (kc.OPCODE, kc.opcode))

	f.write('''
typedef struct {
#ifdef KNH_USING_THREADEDCODE
	void *codeaddr;
#endif/*KNH_USING_THREADEDCODE*/''')
	f.write('''
	knh_opcode_t opcode;''')
	c = 0
	for a in kc.tokens[1:]:
		c += 1
		if a == "addr" : 
			f.write('''
#ifdef KNH_USING_THREADEDCODE
	void *jumpaddr;
#endif/*KNH_USING_THREADEDCODE*/
	union {
		knh_labelid_t a1;  /* labelid */
		knh_code_t *jumppc;
	};''')
		else: 
			f.write('''
	%s a%d;''' % (getctype(a), c))
	
	f.write('''
	void *nextaddr;
} %s;
''' % kc.ctype)
	f.write('''
#define %s  (sizeof(%s)-sizeof(void*))
''' % (kc.SIZE, kc.ctype))

#------------------------------------------------------------------------------

CPROTO = []

def write_define_h(f):
	for p in CPROTO:
		f.write(p + ';\n')
	for kc in KCODE_LIST:
		write_KCODE_h(f,kc)

#------------------------------------------------------------------------------

def write_data_c(f):
	f.write('''
static size_t OPSIZE[] = {''')
	for kc in KCODE_LIST:
		f.write('''
	%s,''' % kc.SIZE)
	f.write('''
};
''')

#------------------------------------------------------------------------------

def write_KCODE_asm_c(f, kc):
	proto = 'knh_code_t* KNH_ASM_%s_(Ctx *ctx, Asm *o%s)' % (kc.name, kc.args())
	CPROTO.append(proto)
	COND = '!knh_Asm_isCancelled(o)'
	if kc.opcode == 0: COND = '1'
	f.write('''
%s
{
	%s *op = NULL;
	if(%s) {
		op = (%s*)knh_Asm_asmmalloc(ctx, o, %s);
		op->opcode = %s;''' % (proto, kc.ctype, COND, kc.ctype, kc.SIZE, kc.opcode))
	c = 1;
	for a in kc.tokens[1:]:
		ctype = getctype(a)
		if a == 'cid':
			f.write('''
		KNH_ASSERT_%s(a%d);''' % (a, c))
		f.write('''
		op->a%d = /*(%s)*/a%d;''' % (c, ctype,c))
		if ctype == 'Object*':
			f.write('''
		knh_Object_RCinc(op->a%d);''' % c)
		c += 1
	f.write('''
		DP(o)->prev_op = (knh_kode_t*)op;
	}
	return (knh_code_t*)op;
}
''')
	write_line(f)

def write_asm_c(f):
	write_data_c(f)
	for kc in KCODE_LIST:
		write_KCODE_asm_c(f, kc)

#----------------------------------------------------------------------------
#------------------------------------------------------------------------------

###############################################################################
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------

def write_label(f):
	write_chapter(f, '[label]')
	CPROTO.append('void knh_Asm_remapAddress(Ctx *ctx, Asm *o)')
	f.write('''

typedef void (*frewrite)(Ctx *ctx, Asm *o, knh_code_t *pc_start, knh_kode_t *op);

void knh_rewrite_addr(Ctx *ctx, Asm *o, knh_code_t *pc_start, knh_kode_t *op)
{
	int offset = DP(o)->labels[op->a1].offset;
	if(offset == -1) {
		DBG_P("Asm!!: unknown Labelid=%d", op->a1);
		knh_Asm_setCancelled(o, 1);
	}else {
		op->jumppc = pc_start + offset;
		//DBG2_P("%p, op=%d, jmp=%p", op, op->opcode, op->jumpaddr);
	}
}

/* ------------------------------------------------------------------------ */

void knh_rewrite_NOP(Ctx *ctx, Asm *o, knh_code_t *pc_start, knh_kode_t *op)
{
	//DBG2_P("%p, op=%d", op, op->opcode);
}

/* ------------------------------------------------------------------------ */

static frewrite OPREWRITE[] = {''')

	for kc in KCODE_LIST:
		func = 'knh_rewrite_NOP'
		if len(kc.tokens)>1 and kc.tokens[1] == 'addr' :
			func = 'knh_rewrite_addr'
		f.write('''
	%s, /* %s */''' % (func, kc.name))
	f.write('''
};

/* ------------------------------------------------------------------------ */

void knh_Asm_writeAddress(Ctx *ctx, Asm *o, knh_code_t *pc_start)
{
	knh_code_t *pc = pc_start;
	while(1) {
		int opcode = KNH_OPCODE(pc);
		if(opcode == OPCODE_HALT) return ; 
		OPREWRITE[opcode](ctx, o, pc_start, (knh_kode_t*)pc);
		pc += OPSIZE[opcode];
	}
}
''')

	write_chapter(f, '[vmc]')
	proto = 'void knh_code_traverse(Ctx *ctx, knh_code_t *pc, knh_ftraverse ftr)'
	CPROTO.append(proto)
	f.write('''
%s
{
	L_NEXT:
	switch(KNH_OPCODE(pc)) {
		case OPCODE_HALT:
			return;''' % proto)
	for kc in KCODE_LIST[1:]:
		if not kc.hasObject(): continue
		f.write('''
		case %s :''' % (kc.OPCODE))
		c = 1
		for a in kc.tokens[1:]:
			ctype = getctype(a)
			if ctype == 'Object*':
				f.write('''
			ftr(ctx, ((%s*)pc)->a%d);''' % (kc.ctype, c))
			c += 1
		f.write('''
			break;''')
	f.write('''
	}
	pc += OPSIZE[KNH_OPCODE(pc)];
	goto L_NEXT;
}
''')

#------------------------------------------------------------------------------

def write_KCODE_dump(f, kc):
	LC = ''
	if len(kc.tokens) == 1: LC = '//'	
	f.write('''
static
void KNH_DUMP_%s(Ctx *ctx, knh_code_t *pc, int flag, OutputStream *w, Method *mtd)
{
	%s%s *op = (%s*)pc;
	KNH_DUMP_OPCODE(ctx, pc, w, mtd, "%s");'''  % (kc.name, LC, kc.ctype, kc.ctype, kc.name))
	c = 1
	for a in kc.tokens[1:]:
		f.write('''
	knh_putc(ctx, w, ' '); ''')
		f.write(getfmt(a) % ('(op->a%d)' % c))
		c += 1
	
	f.write('''
	knh_write_EOL(ctx, w);
}
''')
	write_line(f)

def write_dump(f):
	write_chapter(f, '[dump]')
	f.write('''
#define knh_write__addr(ctx, w, a)  knh_printf(ctx, w, "%p", a)
#define knh_write__boolean(ctx, w, a)  knh_write__s(ctx, w, (a) ? "true" : "false")
#define knh_write__cid(ctx, w, a) knh_write_cid(ctx, w, a)
#define knh_write__float(ctx, w, a) knh_write__f(ctx, w, a)
#define knh_write__integer(ctx, w, a) knh_write_integerfmt(ctx, w, KNH_INT_FMT, a)
#define knh_write__OBJ(ctx, w, a)  knh_format(ctx, w, METHODN__k, a, KNH_NULL)
#define knh_write__sfi(ctx, w, a)  knh_printf(ctx, w, "sfp[%d]", (int)a);
#define knh_write__sfx(ctx, w, a)  knh_printf(ctx, w, "sfp[%d]+%d", (int)a.i, (int)a.n)
#define knh_write__ushort(ctx, w, a)    knh_write__i(ctx, w, (knh_int_t)a)
#define knh_write__mn(ctx, w, a)    knh_write_mn(ctx, w, (knh_methodn_t)a)
#define knh_write__type(ctx, w, a)    knh_write_type(ctx, w, (knh_type_t)a)

static
void KNH_DUMP_OPCODE(Ctx *ctx, knh_code_t *pc, OutputStream *w, Method *mtd, char *name)
{
	knh_kode_t *op = (knh_kode_t*)pc;
	int line = 0;
	if(IS_Method(mtd)) {
		line = knh_Method_pctoline(mtd, pc);
	}
	if(line == 0) {
		knh_printf(ctx, w, " [%p] %s(%d)", pc, name, op->opcode);
	}else{
		knh_printf(ctx, w, " [%d:%p] %s(%d)", line, pc, name, op->opcode);
	}
}

/* ------------------------------------------------------------------------ */

''')

	for kc in KCODE_LIST:
		write_KCODE_dump(f, kc)
	
	f.write('''
/* ------------------------------------------------------------------------ */

typedef void (*fdump)(Ctx *ctx, knh_code_t *pc, int flag, OutputStream *w, Method *mtd);

static fdump OPDUMP[] = {''')

	for kc in KCODE_LIST:
		f.write('''
	KNH_DUMP_%s,''' % (kc.name))
	
	f.write('''
};

/* ------------------------------------------------------------------------ */

void knh_KLRCode__dumpmtd(Ctx *ctx, KLRCode *o, OutputStream *w, Method *mtd)
{
	knh_bytes_t vmc = knh_KLRCode_tobytes(o);
	knh_code_t *pc = (knh_code_t*)vmc.buf;
	while(1) {
		int opcode = KNH_OPCODE(pc);
		if(opcode == OPCODE_HALT) return;
		KNH_ASSERT_OPCODE(opcode);
		OPDUMP[opcode](ctx, pc, 0, w, mtd);
		pc += OPSIZE[opcode];
	}
}

/* ------------------------------------------------------------------------ */

''');

#############################################################################

def getmacro(kc, label):
	m = 'KLR_%s(ctx' % kc.name
	c = 1
	for a in kc.tokens[1:]:
		if a == 'addr':
			m += ', pc = op->jumppc, %s' % (label)
		else:
			m += ', op->a%d' % (c)
		c += 1
	m += ')'
	return m

def write_exec(f):
	CPROTO.append('METHOD knh_KLRCode_exec(Ctx *ctx, knh_sfp_t *sfp)')
	#CPROTO.append('knh_code_t* KNH_CC_FASTCALL konohavm(Ctx *ctx, knh_sfp_t *sfp, knh_code_t *pc_start)')
	#CPROTO.append('void knhvmc_codethreading(Ctx *ctx, knh_code_t *pc, void **codeaddr)')
	write_chapter(f, '[exec]')

	f.write('''
/* ------------------------------------------------------------------------ */

#ifndef DBG2_OPDUMP
#define DBG2_OPDUMP(ctx, pc)
#endif

static
void knh_code_thread(Ctx *ctx, knh_code_t *pc, void **codeaddr)
{
#ifdef KNH_USING_THREADEDCODE
	while(1) {
		knh_kode_t *op = (knh_kode_t*)pc;
		KNH_ASSERT_OPCODE(op->opcode);
		//DBG2_P("%p opcode=%d next=%p", op, op->opcode, op->nextaddr);
		op->codeaddr = codeaddr[op->opcode];
		if(op->opcode == OPCODE_HALT) {
			return;
		}
		switch(op->opcode) {''');
	for kc in KCODE_LIST:
		if len(kc.tokens)>1 and kc.tokens[1] == 'addr' :
			f.write('''
		case %s : ''' % kc.OPCODE)
	f.write('''
			DBG2_P("%p GOTO %p", op, op->jumppc);
			op->jumpaddr = codeaddr[((knh_kode_t*)(op->jumppc))->opcode];
			break;
		}
		pc += OPSIZE[op->opcode];
	}
#endif/*KNH_USING_THREADEDCODE*/
}

''')

	f.write('''
#ifndef KNH_USING_THREADEDCODE
#define OPJUMP NULL
METHOD knh_KLRCode_exec(Ctx *ctx, knh_sfp_t *sfp)
{
	static void **globalMachineToJump = NULL;
	//register knh_code_t *pc = DP((KLRCode*)DP(sfp[-1].mtd)->code)->code;
	register knh_code_t *pc = sfp[-1].pc;
	DBG2_ASSERT(pc == DP((KLRCode*)DP(sfp[-1].mtd)->code)->code);
	L_HEAD:;
	switch(((knh_kode_t*)pc)->opcode) {
''');
	for kc in KCODE_LIST:
		LC = ''
		if len(kc.tokens) == 1: LC = '//'
		f.write('''
	case %s :
		{
			%sconst %s* op = (%s*)pc;
			DBG2_OPDUMP(ctx, pc);
			%s;
			pc += %s;
			goto L_HEAD;
		}
''' % (kc.OPCODE, LC, kc.ctype, kc.ctype, getmacro(kc, 'L_HEAD'), kc.SIZE))
	f.write('''
	}
	KNH_WARNING(ctx, "unknown opcode=%d", ((knh_kode_t*)pc)->opcode);
	goto L_HEAD;
}
#endif/*KNH_USING_THREADEDCODE*/
''')

	write_line(f)
	f.write('''
#ifdef KNH_USING_THREADEDCODE
METHOD knh_KLRCode_exec(Ctx *ctx, knh_sfp_t *sfp)
{
	static void *OPJUMP[] = {''')
	for kc in KCODE_LIST:
		f.write('''
		&&%s,''' % kc.OPLABEL)
	f.write('''
	};
	
	register knh_code_t *pc = sfp[-1].pc;
	DBG2_ASSERT(pc == DP((KLRCode*)DP(sfp[-1].mtd)->code)->code);
	//register knh_code_t *pc =  DP((KLRCode*)DP(sfp[-1].mtd)->code)->code;
	goto *OPJUMP[KNH_OPCODE(pc)]; /* this is needed to init */

''')
	for kc in KCODE_LIST:
		f.write('''
	%s:; {
		const %s *op = (%s*)pc;
		//DBG2_P("%%p sfp[1]=%%d", pc, (int)sfp[1].ivalue);
		DBG2_OPDUMP(ctx, pc);
		%s;
		pc += %s;
		goto *(op->nextaddr);
	}
''' % (kc.OPLABEL, kc.ctype, kc.ctype, getmacro(kc, '*(op->jumpaddr)'), kc.SIZE))

	f.write('''
}
#endif

''')

def getparam(kc, p):
	m = 'JIT_%s(ctx' % kc.name
	c = 1
	for a in kc.tokens[1:]:
		if a == 'addr':
			if p == c :
				m += ', NPC, JUMP1'
			else:
				m += ', NPC, JUMP0'
		elif a == 'sfx':
			if p == c:
				m += ', (%d)' % (c)
			else:
				m += ', (-1)'
			c += 1
			if p == c:
				m += ', (%d)' % (c)
			else:
				m += ', (-1)'
		elif a == 'OBJ':
			if p == c:
				m += ', ((Object*)%d)' % (c)
			else:
				m += ', ((Object*)-1)'
		else:
			if p == c:
				m += ', (%d)' % (c)
			else:
				m += ', (-1)'
		c += 1
	m += ')'
	return m

def getpsize(kc):
	c = 1
	for a in kc.tokens[1:]:
		if a == 'sfx':
			c += 2
		else:
			c += 1
	return c
	
def write_ftemp(f, kc, c):
	f.write('''
static
METHOD jc%d_%s(Ctx *ctx, knh_sfp_t *sfp)
{
	__asm__ __volatile__("int3");
	%s;
	__asm__ __volatile__("int3");
}

''' % (c, kc.NAME, getparam(kc, c)))
	
def write_flist(f, kc):
	m = '\t{jc0_%s' % kc.NAME
	c = 1
	psize = getpsize(kc)
	while c < psize:
		m += ',jc%d_%s' % (c, kc.NAME)
		c += 1
	m += '},\n'
	f.write(m)
	
def write_template(f):

	write_line(f)
	f.write('''
#ifdef KONOHA_CODETEMPLATE
#define NPC
#ifdef _HERE_
#undef _HERE_ 
#endif
#define _HERE_ NULL, 0
#define JUMP0 *(0xffffffff)
#define JUMP1 *(0x00000001)
//static volatile knh_sfp_t *reset_ifneed = NULL;	
''')
	fmax = 0
	pmax = 0
	for kc in KCODE_LIST[:-2]:
		fmax += 1
		c = 0
		psize = getpsize(kc)
		while c < psize:
			write_ftemp(f, kc, c)
			c += 1
		if pmax < psize: pmax = psize
	
	f.write('''
static knh_fmethod codeTempList[%d][%d] = {
''' % (fmax, pmax))
	for kc in KCODE_LIST[:-2]:
		write_flist(f, kc)
	f.write('''
};

knh_fmethod konoha_getCodeTemplate(int opcode, int pos)
{
	return codeTempList[opcode][pos];
}

#endif/*KONOHA_CODETEMPLATE*/
''')

#------------------------------------------------------------------------------

def write_KCODE_cfunc(f, kc):
	LC = ''
	if len(kc.tokens) == 1: LC = '//'	
	f.write('''
static
void KNH_KLR_%s(Ctx *ctx, OutputStream *w, Asm *abr, knh_code_t *pc_start, knh_code_t *pc, int step)
{
	%s%s *op = (%s*)pc;
	KNH_KLR_LABEL(ctx, w, pc_start, pc);'''  % (kc.name, LC, kc.ctype, kc.ctype))
	c = 1
	for a in kc.tokens[1:]:
		if a == 'sfx':
			f.write('''
	knh_printf(ctx, w, "\\tconst knh_sfx_t x%%d_%d = {%%d, %%d};\\n", step, op->a%d.i, op->a%d.n); ''' % (c, c, c))
		c += 1
	f.write('''
	knh_printf(ctx, w, "\\tKLR_%s(");''' % kc.name)
	c = 1
	for a in kc.tokens[1:]:
		if c > 1 :
			f.write('''
	knh_write(ctx, w,  STEXT(", "));''')
		if a == "addr":
			f.write('''
	knh_printf(ctx, w, "NPC, L%p", op->jumppc);''')
			c += 1
			continue
		if a == "sfx":
			f.write('''
	knh_printf(ctx, w, "x%%d_%d", step);''' % (c))
			c += 1
			continue
		if a == "integer":
			f.write('''
	knh_write__integer(ctx, w, op->a%d);''' % (c))
			c += 1
			continue
		if a == "float":
			f.write('''
	knh_write__float(ctx, w, op->a%d);''' % (c))
			c += 1
			continue
		if a == "cid":
			f.write('''
	knh_printf(ctx, w, "_CLASS_%%d /* %%s */", knh_Asm_classId(ctx, abr, op->a%d), CTXCLASSN(op->a%d));''' % (c, c))
			c += 1
			continue
		ctype = getctype(a)
		if ctype == 'Object*':
			f.write('''
	knh_printf(ctx, w, "CONSTPOOL(ctx, delta + %%d)", knh_Asm_constId(ctx, abr, op->a%d));''' % (c))
			c += 1
			continue
		f.write('''
	knh_write__i(ctx, w, (knh_int_t)op->a%d);''' % c)
		c += 1
	f.write('''
	knh_println(ctx, w, STEXT(");"));
}
''')
	write_line(f)

def write_cfunc(f):
	write_chapter(f, "CODE_GENERATOR")
	f.write('''

typedef int (*fhaslabel)(knh_kode_t *op, knh_code_t *pc_start);

static
int knh_hasLabel_LABEL(knh_kode_t *op, knh_code_t *jumppc)
{
	return (op->jumppc == jumppc);
}

/* ------------------------------------------------------------------------ */

static
int knh_hasLabel_NOP(knh_kode_t *op, knh_code_t *jumppc)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

static fhaslabel OPHASLABEL[] = {''')

	for kc in KCODE_LIST:
		func = 'knh_hasLabel_NOP'
		if len(kc.tokens)>1 and kc.tokens[1] == 'addr' :
			func = 'knh_hasLabel_LABEL'
		f.write('''
	%s, /* %s */''' % (func, kc.name))
	f.write('''
};

/* ------------------------------------------------------------------------ */

static
int knh_hasLabel(knh_code_t *pc_start, knh_code_t *jumppc)
{
	int res = 0;
	knh_code_t *pc = pc_start;
	while(res == 0) {
		knh_kode_t *op = (knh_kode_t*)pc;
		if(op->opcode == OPCODE_HALT) return 0; 
		res = OPHASLABEL[op->opcode](op, jumppc);
		pc += OPSIZE[KNH_OPCODE(pc)];
	}
	return res;
}

/* ------------------------------------------------------------------------ */

static
void KNH_KLR_LABEL(Ctx *ctx, OutputStream *w, knh_code_t *pc_start, knh_code_t *pc)
{
	if(knh_hasLabel(pc_start, pc)) {
		knh_printf(ctx, w, "\\tL%p:\\n", pc);
	}
}

/* ------------------------------------------------------------------------ */

''')
	
	for kc in KCODE_LIST[1:]:
		write_KCODE_cfunc(f, kc)

	proto = 'void knh_code_generate(Ctx *ctx, Asm *abr, knh_code_t *pc_start, OutputStream *w)'
	CPROTO.append(proto)
	f.write('''
%s
{
	knh_code_t *pc = pc_start;
	int step = 1;
	knh_println(ctx, w, STEXT("{"));
	knh_println(ctx, w, STEXT("\tsize_t delta = knh_Method_codeDelta(sfp[-1].mtd);"));
	while(1) {
		knh_kode_t *op = (knh_kode_t*)pc;
		switch(op->opcode) {
		case OPCODE_HALT:
			knh_println(ctx, w, STEXT("}"));
			return;''' % proto)
	for kc in KCODE_LIST[1:]:
		f.write('''
		case %s :
			KNH_KLR_%s(ctx, w, abr, pc_start, pc, step);
			break;''' % (kc.OPCODE, kc.name))
	f.write('''
		}
		pc += OPSIZE[KNH_OPCODE(pc)];
		step++;
	}
}
''')

#------------------------------------------------------------------------------

def gen_vm_c(bdir):
	fname = '%s/src/gen/konoha_klr_.c' % bdir
	f = open_c(fname, ['<konoha/konoha_dev.h>', '<konoha/gen/konohac_klr_.h>'])
	write_asm_c(f)
	write_label(f)
	write_dump(f)
	write_exec(f)
	write_cfunc(f)
	close_c(f, fname)

	fname = '%s/include/konoha/gen/konohac_klr_.h' % bdir
	f = open_h(fname, ['<konoha/konoha_dev.h>'])
	write_define_h(f)
	close_h(f, fname)

	fname = '%s/src/gen/codetemplate.c' % bdir
	f = open_c(fname, ['<konoha/konoha_dev.h>', '<konoha/gen/konohac_klr_.h>'])
	write_template(f)
	close_c(f, fname)

#------------------------------------------------------------------------------

if __name__ == '__main__':
	bdir = '..'
	gen_vm_c(bdir)

