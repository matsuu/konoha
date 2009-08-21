/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2005-2009, Kimio Kuramitsu <kimio at ynu.ac.jp>
 *           (c) 2008-      Konoha Software Foundation
 * All rights reserved.
 *
 * You may choose one of the following two licenses when you use konoha.
 * See www.konohaware.org/license.html for further information.
 *
 * (1) GNU Lesser General Public License 3.0 (with KONOHA_UNDER_LGPL3)
 * (2) Konoha Software Foundation License 1.0
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/* ************************************************************************ */

#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif


/* ======================================================================== */
/* @data */

static int knh_Asm_inTry(Asm *abr);
void knh_code_traverse(Ctx *ctx, knh_code_t *pc, knh_ftraverse ftr);
void knh_Asm_writeAddress(Ctx *ctx, Asm *o, knh_code_t *pc_start);

#define ASML(abr, idx)   (idx < DP(abr)->stack) ? (DP(abr)->stack) : idx

#define MOVL(ctx, abr, local, idx) {\
		if(idx < DP(abr)->stack) { \
			KNH_ASM_MOVa_(ctx, abr, sfi_(idx), sfi_(local));\
		}\
	}\

#define nMOVL(ctx, abr, local, idx) {\
		if(idx < DP(abr)->stack) { \
			KNH_ASM_MOVn_(ctx, abr, sfi_(idx), sfi_(local));\
		}\
	}\

#define KNH_ASM_ASSERT(ctx,abr,c) KNH_ASSERT(c)

static knh_labelid_t knh_Asm_newLabelId(Ctx *ctx, Asm *abr, Token *tk);

#define KNH_ASM_PANIC(ctx, abr, fmt, ...) {\
		knh_Asm_setCancelled(abr, 1);\
		fprintf(stderr, "PANIC[%s:%d/%s]: ", knh_safefile(__FILE__), __LINE__, __FUNCTION__); \
		fprintf(stderr, fmt, ## __VA_ARGS__); \
		fprintf(stderr, "\n"); \
	}\

static
void TERMs_asm(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, knh_type_t reqt, int sfpidx);

/* ======================================================================== */
/* [constructor] */

void knh_Context_initAsm(Ctx *ctx)
{
	if(IS_NULL(ctx->abr)) {
		KNH_SETv(ctx, ((Context*)ctx)->abr, (Asm*)new_Object_bcid(ctx, CLASS_Asm, 0));
	}
}

/* ======================================================================== */
/* [namespace] */

NameSpace *knh_getAsmNameSpace(Ctx *ctx)
{
	knh_Context_initAsm(ctx);
	return DP(knh_Context_getAsm(ctx))->ns;
}

/* ------------------------------------------------------------------------ */

NameSpace *knh_setAsmNameSpace(Ctx *ctx, String *nsname)
{
	knh_Context_initAsm(ctx);
	Asm *abr = knh_Context_getAsm(ctx);
	if(IS_NULL(nsname) || knh_String_equals(nsname, STEXT("main"))) {
		KNH_SETv(ctx, DP(abr)->ns, ctx->share->mainns);
	}
	else {
		KNH_SETv(ctx, DP(abr)->ns, knh_getNameSpace(ctx, knh_String_tobytes(nsname)));
	}
	return DP(abr)->ns;
}

/* ------------------------------------------------------------------------ */

NameSpace *knh_switchAsmNameSpace(Ctx *ctx, NameSpace *newns)
{
	knh_Context_initAsm(ctx);
	Asm *abr = knh_Context_getAsm(ctx);
	NameSpace *oldns = DP(abr)->ns;
	KNH_SETv(ctx, DP(abr)->ns, newns);
	return oldns;
}

/* ------------------------------------------------------------------------ */

Script *knh_getAsmScript(Ctx *ctx)
{
	Asm *abr = knh_Context_getAsm(ctx);
	return knh_NameSpace_getScript(ctx, DP(abr)->ns);
}

/* ======================================================================== */
/* [compile method] */

void knh_Asm_initGamma(Ctx *ctx, Asm *abr, size_t c)
{
	size_t i;
	DP(abr)->gamma_size = c;
	for(i = c; i < KONOHA_LOCALSIZE; i++) {
		DP(abr)->gamma[i].flag  = 0;
		DP(abr)->gamma[i].type  = TYPE_void;
		DP(abr)->gamma[i].fn    = FIELDN_NONAME;
		if(DP(abr)->gamma[i].value != NULL) {
			KNH_FINALv(ctx, DP(abr)->gamma[i].value);
			DP(abr)->gamma[i].value = NULL;
		}
	}
}

/* ------------------------------------------------------------------------ */

void knh_Asm_prepare(Ctx *ctx, Asm *abr, Method *mtd, Stmt *stmt)
{
	size_t i;
	DP(abr)->flag = 0;
	KNH_SETv(ctx, DP(abr)->mtd, mtd);
	DP(abr)->this_cid = DP(mtd)->cid;
	DP(abr)->rtype = knh_pmztype_totype(ctx, knh_Method_rztype(DP(abr)->mtd), DP(abr)->this_cid);
	DP(abr)->level = 0;

	knh_Asm_initGamma(ctx, abr, 0);
	knh_Asm_initReg(ctx, abr);
	DP(abr)->nnrtti  = 0;
	DP(abr)->nnrtti0 = 0;

	DP(abr)->stack = 1;
	DP(abr)->globalidx = -1;

	DP(abr)->llstep = 0;
	for(i = 0; i < DP(abr)->labelmax; i++) {
		KNH_SETv(ctx, DP(abr)->labels[i].tklabel, KNH_NULL);
	}
	DP(abr)->labelmax = 0;
	knh_Array_clear(ctx, DP(abr)->lstacks);

	DP(abr)->uri  = SP(stmt)->uri;
	DP(abr)->line   = 0;
	knh_Bytes_clear(DP(abr)->elf, 0);
	knh_Bytes_clear(DP(abr)->dwarf, 0);
	DP(abr)->prev_op = NULL;
	knh_Asm_setCancelled(abr, 0);
}

/* ------------------------------------------------------------------------ */

void knh_Asm_initThis(Ctx *ctx, Asm *abr, knh_class_t cid)
{
	KNH_ASSERT_cid(cid);
	DP(abr)->this_cid = cid;
	DP(abr)->gamma[0].flag = 0;
	DP(abr)->gamma[0].type = NNTYPE_cid(cid);
	DP(abr)->gamma[0].fn   = FIELDN_this;
	DBG2_ASSERT(DP(abr)->gamma[0].value == NULL);
	DP(abr)->gamma_size = 1;
}

/* ------------------------------------------------------------------------ */

void knh_Asm_initThisScript(Ctx *ctx, Asm *abr)
{
	knh_Asm_initThis(ctx, abr, knh_Object_cid(knh_getAsmScript(ctx)));
}

/* ------------------------------------------------------------------------ */

static
void knh_Asm_gc(Ctx *ctx, Asm *abr)
{
	size_t i;
	KNH_SETv(ctx, DP(abr)->mtd, KNH_NULL);
	knh_Asm_initGamma(ctx, abr, 0);
	knh_Asm_initReg(ctx, abr);
	for(i = 0; i < DP(abr)->labelmax; i++) {
		KNH_SETv(ctx, DP(abr)->labels[i].tklabel, KNH_NULL);
	}
	DP(abr)->labelmax = 0;
	knh_Array_clear(ctx, DP(abr)->lstacks);
	knh_Bytes_clear(DP(abr)->elf, 0);
	knh_Bytes_clear(DP(abr)->dwarf, 0);
}

/* ------------------------------------------------------------------------ */

static
void knh_Asm_finish(Ctx *ctx, Asm *abr)
{
	Method *mtd = (Method*)DP(abr)->mtd;
	KNH_ASSERT(IS_Method(mtd));

	KNH_ASM_HALT_(ctx, abr);

	if(knh_Asm_isCancelled(abr)) {
		knh_code_traverse(ctx, (knh_code_t*)knh_Bytes_tochar(DP(abr)->elf), knh_Object_sweep);
		knh_Asm_gc(ctx, abr);
		return;
	}

	KLRCode *vmc = new_KLRCode(ctx, DP(abr)->uri,
			knh_Bytes_tobytes(DP(abr)->elf), knh_Bytes_tobytes(DP(abr)->dwarf));
	knh_Method_setKLRCode(ctx, mtd, vmc);
	knh_Asm_writeAddress(ctx, abr, DP(vmc)->code);

	if(knh_Asm_isCancelled(abr)) {
		if(DP(mtd)->mn != METHODN_lambda) {
			knh_Asm_perror(ctx, abr, KERR_DWARN, "abstract? %C.%M", DP(mtd)->cid, DP(mtd)->mn);
		}
		knh_Method_toAbstract(ctx, mtd);
	}
	else {
		knh_sfp_t *lsfp = KNH_LOCAL(ctx);
		KNH_SETv(ctx, lsfp[0].o, mtd);
		lsfp[0].pc = mtd->pc_start;
		knh_KLRCode_exec(ctx, lsfp+1); /* code threading */
		DBG2_P("mtd(%p)", mtd);
		DBG2_DUMP(ctx, mtd, KNH_NULL, "Compiled Code");
	}
	knh_Asm_gc(ctx, abr);
}

/* ------------------------------------------------------------------------ */
/* @data */

static knh_rtti_t RuntimeNullCheck [] = {
	1LL<<0,  1LL<<1,  1LL<<2,  1LL<<3,  1LL<<4,
	1LL<<5,  1LL<<6,  1LL<<7,  1LL<<8,  1LL<<9,
	1LL<<10, 1LL<<11, 1LL<<12, 1LL<<13, 1LL<<14,
	1LL<<15, 1LL<<16, 1LL<<17, 1LL<<18, 1LL<<19,
	1LL<<20, 1LL<<21, 1LL<<22, 1LL<<23, 1LL<<24,
	1LL<<25, 1LL<<26, 1LL<<27, 1LL<<28, 1LL<<29,
	1LL<<30, 1LL<<31, 1LL<<32, 1LL<<33, 1LL<<34,
	1LL<<35, 1LL<<36, 1LL<<37, 1LL<<38, 1LL<<39,
	1LL<<40, 1LL<<41, 1LL<<42, 1LL<<43, 1LL<<44,
	1LL<<45, 1LL<<46, 1LL<<47, 1LL<<48, 1LL<<49,
	1LL<<50, 1LL<<51, 1LL<<52, 1LL<<53, 1LL<<54,
	1LL<<55, 1LL<<56, 1LL<<57, 1LL<<58, 1LL<<59,
	1LL<<60, 1LL<<61, 1LL<<62, 1LL<<63,
};

/* ------------------------------------------------------------------------ */

static
void knh_rtti_nullChecked(Asm *abr, size_t n)
{
	if(/*0 <= n &&*/ n < (sizeof(knh_rtti_t) * 8)) {
		DP(abr)->nnrtti = DP(abr)->nnrtti | RuntimeNullCheck[n];
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_rtti_nullable(Asm *abr, size_t n)
{
	if(/*0 <= n &&*/ n < (sizeof(knh_rtti_t) * 8)) {
		DP(abr)->nnrtti = DP(abr)->nnrtti & (~RuntimeNullCheck[n]);
	}
}

/* ------------------------------------------------------------------------ */

static
knh_type_t knh_rtti_type(Asm *abr, knh_type_t type, int a)
{
	if(0 <= a && a < DP(abr)->stack) {
		KNH_ASSERT(a < (sizeof(knh_rtti_t) * 8));
		if(((DP(abr)->nnrtti & RuntimeNullCheck[a])) == RuntimeNullCheck[a]) {
			return NNTYPE_cid(type);
		}
	}
	return type;
}

/* ------------------------------------------------------------------------ */

static
void knh_rtti_reset(Asm *abr)
{
	DP(abr)->nnrtti = DP(abr)->nnrtti0;
}

/* ------------------------------------------------------------------------ */

static
int knh_rtti_issync(Asm *abr, int a)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

static
void knh_rtti_sync(Asm *abr, int a)
{
	// TODO();
}

/* ------------------------------------------------------------------------ */

static
void knh_rtti_async(Asm *abr, int a)
{
	// TODO();
}

/* ======================================================================== */
/* [asmmalloc] */

void *knh_Asm_asmmalloc(Ctx *ctx, Asm *abr, size_t size)
{
//	DEBUG("size=%d", (int)size);
	size_t off = knh_Bytes_size(DP(abr)->elf);
	size_t i ;
	for(i = 0; i < size; i++) {
		knh_Bytes_putc(ctx, DP(abr)->elf, 0);
	}
	return (void*)(knh_Bytes_value(DP(abr)->elf) + off);
}

/* ------------------------------------------------------------------------ */

void knh_Asm_rewind(Ctx *ctx, Asm *abr)
{
	Bytes *ba = DP(abr)->elf;
	ba->size = (knh_uchar_t*)DP(abr)->prev_op - ba->buf;
	DP(abr)->prev_op = NULL;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_SETLINE(Ctx *ctx, Asm *abr, int line)
{
	if(line > DP(abr)->line) {
		char *top = knh_Bytes_tochar(DP(abr)->elf);
		char *cur = (char*)knh_Bytes_last(DP(abr)->elf);
		int offset = cur - top;
		//DEBUG("line=%d at=%d", line, offset);
		knh_dwarf_t dw = {offset, line};
		knh_Bytes_write(ctx, DP(abr)->dwarf, B2((char*)(&dw), sizeof(knh_dwarf_t)));
		DP(abr)->line = line;
	}
}

/* ======================================================================== */
/* [ASM] */

#define sfi_(n)    ((knh_sfi_t)(n))

#define IS_VAL(t) (IS_BOOL(t)||IS_INT(t)||IS_FLOAT(t))
#define IS_ANY(t) (CLASS_type(t) == CLASS_Any || CLASS_type(t) == CLASS_Object)

/* ------------------------------------------------------------------------ */

//                            int   Int    Any(sfp)   Any(obj)
// int [??, 1]                             [Int0, 1]  [Int, 1]
// Int [null, ??] [??, 1]

//                            int   Int    Any(sfp)   Any(obj)
// int [Int0, 1]                           [Int0, 1]  [Int, 1]
// Int [null, ??] [Int0, 1]


/* ------------------------------------------------------------------------ */

static
void KNH_ASM_BOX(Ctx *ctx, Asm *abr, knh_type_t atype, int a)
{
	if(knh_rtti_issync(abr, a)) return;
	knh_class_t cid = CLASS_type(atype);
	KNH_ASSERT_cid(cid);
	knh_class_t bcid = ClassTable(cid).bcid;
	if(bcid == CLASS_Boolean || bcid == CLASS_Int || bcid == CLASS_Float) {
		if(IS_NNTYPE(atype)) {
			KNH_ASM_BOX_(ctx, abr, a, cid);
		}
		else {
			KNH_ASM_BOXnc_(ctx, abr, a, cid);
		}
	}
	knh_rtti_sync(abr, a);
}

/* ------------------------------------------------------------------------ */

static
void KNH_ASM_NNBOX(Ctx *ctx, Asm *abr, knh_type_t atype, int a)
{
	if(knh_rtti_issync(abr, a)) return;
	knh_class_t cid = CLASS_type(atype);
	KNH_ASSERT_cid(cid);
	knh_class_t bcid = ClassTable(cid).bcid;
	if(bcid == CLASS_Boolean || bcid == CLASS_Int || bcid == CLASS_Float) {
		if(IS_NNTYPE(atype)) {
			KNH_ASM_NNBOX_(ctx, abr, a, cid);
		}
		else {
			KNH_ASM_NNBOXnc_(ctx, abr, a, cid);
		}
	}
}

/* ------------------------------------------------------------------------ */

static
void KNH_ASM_SMOVx(Ctx *ctx, Asm *abr, knh_type_t atype, int a, knh_type_t btype, knh_sfx_t bx)
{
#ifdef KNH_USING_UNBOXFIELD
	if(IS_ubxint(btype)) {
		KNH_ASM_MOVxi_(ctx, abr, sfi_(a), bx);
		if(!IS_NNTYPE(atype)) {
			KNH_ASM_NNBOX_(ctx, abr, sfi_(a), CLASS_type(btype));
		}
		return;
	}
	if(IS_ubxfloat(btype)) {
		KNH_ASM_MOVxf_(ctx, abr, sfi_(a), bx);
		if(!IS_NNTYPE(atype)) {
			KNH_ASM_NNBOX_(ctx, abr, sfi_(a), CLASS_type(btype));
		}
		return;
	}
	if(IS_ubxboolean(btype)) {
		KNH_ASM_MOVxb_(ctx, abr, sfi_(a), bx);
		if(!IS_NNTYPE(atype)) {
			KNH_ASM_NNBOX_(ctx, abr, sfi_(a), CLASS_type(btype));
		}
		return;
	}
#endif
	if(IS_NNTYPE(atype) && !IS_NNTYPE(btype)) {
		KNH_ASM_CHECKNULLx_(ctx, abr, bx);
		btype = NNTYPE_cid(btype);
	}
	knh_rtti_async(abr, a);
	KNH_ASM_MOVx_(ctx, abr, sfi_(a), bx);
}

/* ------------------------------------------------------------------------ */

static
void KNH_ASM_SMOV(Ctx *ctx, Asm *abr, knh_type_t atype, int a, Token *tkb)
{
	KNH_ASSERT(IS_Token(tkb));
	knh_type_t btype = DP(tkb)->type;

	switch(TT_(tkb)) {
		case TT_CLASSID:
		case TT_CONST: {
			Object *v = DP(tkb)->data;
			KNH_ASM_MOVo_(ctx, abr, sfi_(a), v);
			knh_rtti_sync(abr, a);
			break;
		}
		case TT_LOCAL: {
			int b = (int)DP(tkb)->index;
			knh_type_t btype = knh_rtti_type(abr, DP(tkb)->type, b);
			if(IS_NNTYPE(atype) && IS_NATYPE(btype)) {
				KNH_ASM_CHECKNULL_(ctx, abr, b);
				knh_rtti_nullChecked(abr, b);
				btype = NNTYPE_cid(btype);
			}
			if(IS_ubxtype(btype)) {
				KNH_ASM_MOVn_(ctx, abr, sfi_(a), sfi_(b));
				if(IS_ANY(atype) || !IS_NNTYPE(atype)) {
					KNH_ASM_NNBOX(ctx, abr, btype, a);
				}
			}
			else if(IS_bxint(btype) || IS_bxfloat(btype)) {
				KNH_ASM_MOVa_(ctx, abr, sfi_(a), sfi_(b));
				if(IS_ANY(atype)) {
					KNH_ASM_NNBOX(ctx, abr, btype, a);
				}
			}
			else {
				KNH_ASM_MOVa_(ctx, abr, sfi_(a), sfi_(b));
			}
			break;
		}

		case TT_FIELD: {
			int b = (int)DP(tkb)->index;
			knh_sfx_t bx = {sfi_(0), (size_t)b};
			KNH_ASM_SMOVx(ctx, abr, atype, a, btype, bx);
			break;
		}

		case TT_SCRIPT: {
			int b = (int)DP(tkb)->index;
			knh_sfx_t bx = {sfi_(DP(abr)->globalidx), (size_t)b};
			KNH_ASM_ASSERT(ctx, abr, bx.i != -1);
			KNH_ASM_SMOVx(ctx, abr, atype, a, btype, bx);
			break;
		}

		case TT_MEMBER: {
			int idx = (int)DP(tkb)->index;
			size_t b = (size_t)(DP(tkb)->num)->n.ivalue;
			knh_sfx_t bx = {sfi_(idx), b};
			KNH_ASM_SMOVx(ctx, abr, atype, a, btype, bx);
			break;
		}

		case TT_DEFVAL: {
			knh_class_t cid = DP(tkb)->cid;
			KNH_ASM_MOVDEF_(ctx, abr, sfi_(a), cid);
			knh_rtti_sync(abr, a);
			break;
		}

		case TT_SYSVAL: {
			knh_ushort_t sysid = DP(tkb)->index;
			KNH_ASM_MOVSYS_(ctx, abr, sfi_(a), sysid);
			knh_rtti_sync(abr, a);
			break;
		}

		case TT_NOP: {
			return;
		}

		case TT_CLOSURE: {
			int local = ASML(abr, a);
			Method *mtd = DP(tkb)->mtd;
			knh_class_t cid = DP(mtd)->cid;
			if(cid == DP(abr)->this_cid || knh_class_instanceof(ctx, DP(abr)->this_cid, cid)) {
				KNH_ASM_MOVa_(ctx, abr, sfi_(local+2), sfi_(0));
			}
			else if(cid == knh_Object_cid(knh_getAsmScript(ctx))) {
				KNH_ASM_MOVo_(ctx, abr, sfi_(local+2), UP(knh_getAsmScript(ctx)));
			}
			else {
				KNH_ASM_MOVDEF_(ctx, abr, sfi_(local+2), cid);
			}
			KNH_ASM_MOVo_(ctx, abr, sfi_(local+3), UP(mtd));
			mtd = knh_Class_getMethod(ctx, CLASS_Closure, METHODN_new);
			DBG2_ASSERT(IS_Method(mtd));
			KNH_ASM_NEW_(ctx, abr, local, 0, CLASS_type(DP(tkb)->type), 2, UP(mtd));
			MOVL(ctx, abr, local, a);
			break;
		}

		default: {
			DBG2_P("unknown TT=%s", knh_token_tochar(TT_(tkb)));
			KNH_ASSERT(ctx == NULL);
		}
	}/*switch*/

	if(IS_NNTYPE(btype)) {
		knh_rtti_nullChecked(abr, a);
	}
	else {
		knh_rtti_nullable(abr, a);
	}
}

/* ------------------------------------------------------------------------ */

static
void KNH_ASM_XMOVx(Ctx *ctx, Asm *abr, knh_type_t atype, knh_sfx_t ax, knh_type_t btype, knh_sfx_t bx)
{
	if(IS_NNTYPE(atype) && !IS_NNTYPE(btype)) {
		KNH_ASM_CHECKNULLx_(ctx, abr, bx);
	}
	if(IS_ubxint(atype)) {
		if(IS_ubxint(btype)) {
			KNH_ASM_XMOVxi_(ctx, abr, ax, bx);
		}
		else {
			KNH_ASM_XMOVxio_(ctx, abr, ax, bx);
		}
		return;
	}
	if(IS_ubxfloat(atype)) {
		if(IS_ubxfloat(btype)) {
			KNH_ASM_XMOVxf_(ctx, abr, ax, bx);
		}
		else {
			KNH_ASM_XMOVxfo_(ctx, abr, ax, bx);
		}
		return;
	}
	if(IS_ubxboolean(atype) && IS_ubxboolean(btype)) {
		KNH_ASM_XMOVxb_(ctx, abr, ax, bx);
		return;
	}
	if(IS_bxint(atype) && IS_ubxint(btype)) {
		KNH_ASM_XMOVxBXi_(ctx, abr, ax, bx, CLASS_type(btype));
		return;
	}
	if(IS_bxfloat(atype) && IS_ubxfloat(btype)) {
		KNH_ASM_XMOVxBXf_(ctx, abr, ax, bx, CLASS_type(btype));
		return;
	}
	KNH_ASM_XMOVx_(ctx, abr, ax, bx);
}

/* ------------------------------------------------------------------------ */

static
void KNH_ASM_XMOV(Ctx *ctx, Asm *abr, knh_type_t atype, int a, size_t an, Token *tkb)
{
	KNH_ASSERT(IS_Token(tkb) && knh_Token_isTyped(tkb));
	knh_sfx_t ax = {sfi_(a), an};
	knh_type_t btype = DP(tkb)->type;
	switch(TT_(tkb)) {
		case TT_CLASSID:
		case TT_CONST: {
			Object *v = DP(tkb)->data;
#ifdef KNH_USING_UNBOXFIELD
			if(IS_ubxint(atype)) {
				KNH_ASM_XMOVoi_(ctx, abr, ax, v);
				break;
			}
			if(IS_ubxfloat(atype)) {
				KNH_ASM_XMOVof_(ctx, abr, ax, v);
				break;
			}
			if(IS_ubxboolean(atype)) {
				KNH_ASM_XMOVob_(ctx, abr, ax, v);
				break;
			}
#endif/*KNU_USING_UNBOXFIED*/
			KNH_ASM_XMOVo_(ctx, abr, ax, v);
			break;
		}

		case TT_LOCAL: {
			int b = (int)DP(tkb)->index;
			if(IS_NNTYPE(atype) && !IS_NNTYPE(btype)) {
				KNH_ASM_CHECKNULL_(ctx, abr, b);
				knh_rtti_nullChecked(abr, b);
			}
#ifdef KNH_USING_UNBOXFIELD
			if(IS_ubxint(atype)) {
				KNH_ASM_XMOVsi_(ctx, abr, ax, sfi_(b));
				break;
			}
			if(IS_ubxfloat(atype)) {
				KNH_ASM_XMOVsf_(ctx, abr, ax, sfi_(b));
				break;
			}
			if(IS_ubxboolean(atype)) {
				KNH_ASM_XMOVsb_(ctx, abr, ax, sfi_(b));
				break;
			}
#endif/*KNU_USING_UNBOXFIED*/
			KNH_ASM_BOX(ctx, abr, btype, b);
			KNH_ASM_XMOVs_(ctx, abr, ax, sfi_(b));
			break;
		}

		case TT_FIELD: {
			int b = (int)DP(tkb)->index;
			knh_sfx_t bx = {(knh_sfi_t)0, (size_t)b};
			KNH_ASM_XMOVx(ctx, abr, atype, ax, btype, bx);
			break;
		}

		case TT_SCRIPT: {
			int b = (int)DP(tkb)->index;
			knh_sfx_t bx = {(knh_sfi_t)DP(abr)->globalidx, (size_t)b};
			KNH_ASM_ASSERT(ctx, abr, bx.i != -1);
			KNH_ASM_XMOVx(ctx, abr, atype, ax, btype, bx);
			break;
		}

		case TT_MEMBER : {
			int idx = (int)DP(tkb)->index;
			size_t b = (size_t)(DP(tkb)->num)->n.ivalue;
			knh_sfx_t bx = {sfi_(idx), b};
			KNH_ASM_XMOVx(ctx, abr, atype, ax, btype, bx);
			break;

		}
		case TT_DEFVAL: {
#ifdef KNH_USING_UNBOXFIELD
			if(IS_ubxint(atype)) {
				KNH_ASM_XMOVoi_(ctx, abr, ax, KNH_DEF(ctx, CLASS_type(atype)));
				break;
			}
			if(IS_ubxfloat(atype)) {
				KNH_ASM_XMOVof_(ctx, abr, ax, KNH_DEF(ctx, CLASS_type(atype)));
				break;
			}
			if(IS_ubxfloat(atype)) {
				KNH_ASM_XMOVob_(ctx, abr, ax, KNH_FALSE);
				break;
			}
#endif/*KNU_USING_UNBOXFIED*/
			knh_class_t cid = DP(tkb)->cid;
			KNH_ASM_XMOVDEF_(ctx, abr, ax, cid);
			break;
		}

		case TT_SYSVAL: {
			knh_ushort_t sysid = DP(tkb)->index;
			KNH_ASM_XMOVSYS_(ctx, abr, ax, sysid);
			break;
		}

		case TT_CLOSURE: {
			int local = DP(abr)->stack;
			Method *mtd = DP(tkb)->mtd;
			knh_class_t cid = DP(mtd)->cid;
			if(cid == DP(abr)->this_cid || knh_class_instanceof(ctx, DP(abr)->this_cid, cid)) {
				KNH_ASM_MOVa_(ctx, abr, sfi_(local+2), sfi_(0));
			}
			else if(cid == knh_Object_cid(knh_getAsmScript(ctx))) {
				KNH_ASM_MOVo_(ctx, abr, sfi_(local+2), UP(knh_getAsmScript(ctx)));
			}
			else {
				KNH_ASM_MOVDEF_(ctx, abr, sfi_(local+2), cid);
			}
			KNH_ASM_MOVo_(ctx, abr, sfi_(local+3), UP(mtd));
			mtd = knh_Class_getMethod(ctx, CLASS_Closure, METHODN_new);
			KNH_ASSERT(IS_Method(mtd));
			KNH_ASM_NEW_(ctx, abr, local, 0, CLASS_type(DP(tkb)->type), 2, UP(mtd));
			KNH_ASM_XMOVs_(ctx, abr, ax, sfi_(local));
			break;
		}

		case TT_NOP: {
			return;
		}

		default: {
			DBG2_P("unknown TT=%d", TT_(tkb));
			KNH_ASSERT(ctx == NULL);
		}
	}/*switch*/

}

/* ------------------------------------------------------------------------ */

static
void KNH_ASM_MOV(Ctx *ctx, Asm *abr, Token *tka, Token *tkb)
{
	KNH_ASSERT(IS_Token(tka) && knh_Token_isTyped(tka));
	knh_type_t atype = DP(tka)->type;

	if(TT_(tka) == TT_LOCAL) {
		KNH_ASM_SMOV(ctx, abr, atype, (int)DP(tka)->index, tkb);
	}
	else if(TT_(tka) == TT_FIELD) {
		int an = (int)DP(tka)->index;
		KNH_ASM_XMOV(ctx, abr, atype, 0, an, tkb);
	}
	else if(TT_(tka) == TT_SCRIPT) {
		int a = (int)DP(abr)->globalidx;
		KNH_ASM_ASSERT(ctx, abr, a != -1);
		int an = (int)DP(tka)->index;
		KNH_ASM_XMOV(ctx, abr, atype, a, an, tkb);
	}
	else if(TT_(tka) == TT_MEMBER) {
		int a = (int)DP(tka)->index;
		KNH_ASM_ASSERT(ctx, abr, IS_Int(DP(tka)->data));
		int an = (int)(DP(tka)->num)->n.ivalue;
		KNH_ASM_XMOV(ctx, abr, atype, a, an, tkb);
	}
	else if(TT_(tka) == TT_NOP) {

	}
	else {
		DBG2_P("unknown TT=%d", TT_(tka));
		KNH_ASSERT(ctx == NULL);
	}
}

/* ------------------------------------------------------------------------ */

static
void KNH_ASM_RET(Ctx *ctx, Asm *abr)
{
	knh_opcode_t p = DP(abr)->prev_op->opcode;
	if(OPCODE_RET <= p && p <= OPCODE_RETX) {
		return;
	}
	if(p == OPCODE_MOVN) { /* PEEPHOLE */
		klr_movn_t *op = (klr_movn_t*)DP(abr)->prev_op;
		if(op->a1 == -1) {
			op->opcode = OPCODE_RETN;
			return;
		}
	}
	if(p == OPCODE_MOVA) { /* PEEPHOLE */
		klr_movn_t *op = (klr_movn_t*)DP(abr)->prev_op;
		if(op->a1 == -1) {
			op->opcode = OPCODE_RETA;
			return;
		}
	}
	if(p == OPCODE_MOVO) { /* PEEPHOLE */
		klr_movn_t *op = (klr_movn_t*)DP(abr)->prev_op;
		if(op->a1 == -1) {
			op->opcode = OPCODE_RETO;
			return;
		}
	}
	if(p == OPCODE_MOVX) { /* PEEPHOLE */
		klr_movn_t *op = (klr_movn_t*)DP(abr)->prev_op;
		if(op->a1 == -1) {
			op->opcode = OPCODE_RETX;
			return;
		}
	}
	KNH_ASM_RET_(ctx, abr);
}


/* ------------------------------------------------------------------------ */

static
void KNH_ASM_CALL(Ctx *ctx, Asm *abr, knh_type_t reqt, int sfpidx, Token *tkb, size_t args)
{
	KNH_ASSERT(IS_Token(tkb));
	KNH_ASSERT(sfpidx >= DP(abr)->stack);
	Method *mtd = DP(tkb)->mtd;
	knh_type_t rtype = CLASS_Any;
	if(IS_Method(mtd)) {
		if(knh_Method_isFinal(mtd) || knh_Method_isConstructor(ctx, mtd) || knh_Token_isSUPER(tkb)) {
			KNH_ASM_SCALL_(ctx, abr, sfpidx, args + 2, UP(mtd));
		}
		else {
			KNH_ASM_CALL_(ctx, abr, sfpidx, args + 2, DP(mtd)->mn);
		}
		rtype = knh_Method_rztype(mtd);
		if(IS_NNTYPE(reqt) && !IS_NNTYPE(rtype)) {
			KNH_ASM_CHECKNULL_(ctx, abr, sfpidx);
			knh_rtti_nullChecked(abr, sfpidx);
		}
	}
	else if(TT_(tkb) == TT_MN) {
		KNH_ASM_ACALL_(ctx, abr, sfpidx, args + 2, DP(tkb)->mn);
		if(IS_NNTYPE(reqt) && !IS_NNTYPE(rtype)) {
			KNH_ASM_CHECKNULL_(ctx, abr, sfpidx);
			knh_rtti_nullChecked(abr, sfpidx);
		}
	}
	else {
		KNH_ASM_PANIC(ctx, abr, "unknown call type");
	}
}

/* ------------------------------------------------------------------------ */

static
void KNH_ASM_NEW(Ctx *ctx, Asm *abr, knh_type_t reqt, int sfpidx, Token *tkb,
		knh_flag_t flag, knh_class_t cid, size_t args)
{
	KNH_ASSERT(IS_Token(tkb));
	KNH_ASSERT(sfpidx >= DP(abr)->stack);
	Method *mtd = DP(tkb)->mtd;
	KNH_ASM_ASSERT(ctx, abr, IS_Method(mtd));
	KNH_ASM_NEW_(ctx, abr, sfpidx, flag, cid, args + 2, UP(mtd));

	knh_type_t rtype = knh_Method_rztype(mtd);
	if(IS_NNTYPE(reqt) && !IS_NNTYPE(rtype)) {
		KNH_ASM_CHECKNULL_(ctx, abr, sfpidx);
		knh_rtti_nullChecked(abr, sfpidx);
	}
}

/* ------------------------------------------------------------------------ */

static
void KNH_ASM_MAP(Ctx *ctx, Asm *abr, knh_type_t reqt, int sfpidx, Token *tkb, knh_type_t srct, int isNonNullCast)
{
	KNH_ASSERT(IS_Token(tkb));
	KNH_ASSERT(sfpidx >= DP(abr)->stack);
	Mapper *mpr = (Mapper*)DP(tkb)->data;

	if(IS_Mapper(mpr)) {
//		DBG2_P("reqt=%s%s tcid=%s srct=%s%s isNonNullCast=%d",
//				TYPEQN(reqt), CLASSN(DP(mpr)->tcid), TYPEQN(srct), isNonNullCast);
		if(knh_Mapper_isFinal(mpr)) {
			if(IS_NNTYPE(srct)) {
				if(DP(mpr)->scid == CLASS_Int && DP(mpr)->tcid == CLASS_Float) {
					KNH_ASM_fCAST_(ctx, abr, sfpidx);
					return;
				}
				else if(DP(mpr)->scid == CLASS_Float && DP(mpr)->tcid == CLASS_Int) {
					KNH_ASM_iCAST_(ctx, abr, sfpidx);
					return;
				}
				KNH_ASM_SMAP_(ctx, abr, sfpidx, UP(mpr));
				if(!knh_Mapper_isTotal(mpr)) srct = CLASS_type(srct);
			}
			else {
				if(DP(mpr)->scid == CLASS_Int && DP(mpr)->tcid == CLASS_Float) {
					KNH_ASM_fnCAST_(ctx, abr, sfpidx);
					return;
				}
				else if(DP(mpr)->scid == CLASS_Float && DP(mpr)->tcid == CLASS_Int) {
					KNH_ASM_inCAST_(ctx, abr, sfpidx);
					return;
				}
				KNH_ASM_SMAPnc_(ctx, abr, sfpidx, UP(mpr));
			}
		}
		else {
			if(IS_NNTYPE(srct)) {
				KNH_ASM_MAP_(ctx, abr, sfpidx, DP(mpr)->tcid);
				if(!knh_Mapper_isTotal(mpr)) {
					srct = CLASS_type(srct);
				}
			}
			else {
				KNH_ASM_MAPnc_(ctx, abr, sfpidx, DP(mpr)->tcid);
			}
		}
	}
	else {
		KNH_ASSERT(TT_(tkb) == TT_MPR);
		//DBG2_P("reqt=%s%s mprcid=%s srct=%s%s isNonNullCast=%d", TYPEQN(reqt), DP(tkb)->cid, TYPEQN(srct), isNonNullCast);
		KNH_ASM_AMAP_(ctx, abr, sfpidx, DP(tkb)->cid);
		srct = CLASS_type(srct);
	}
	if(!IS_NNTYPE(srct) && isNonNullCast) {
		KNH_ASM_NNMAP_(ctx, abr, sfpidx, DP(tkb)->cid);
	}
	else if(IS_NNTYPE(reqt)) {
		KNH_ASM_CHECKNULL_(ctx, abr, sfpidx);
	}
}

/* ======================================================================== */
/* [CONTROL] */

static
knh_labelid_t knh_Asm_findLabelId(Ctx *ctx, Asm *abr, Token *tk)
{
	size_t i;
	if(tk != NULL) {
		knh_bytes_t name = knh_String_tobytes(DP(tk)->text);
		for(i = 0; i < DP(abr)->labelmax; i++) {
			Token *ltk = DP(abr)->labels[i].tklabel;
			if(IS_NOTNULL(ltk) && knh_String_equals(DP(ltk)->text, name)) {
				return (knh_labelid_t)i;
			}
		}
	}
	return ((knh_labelid_t)-1);
}

/* ------------------------------------------------------------------------ */

static
knh_labelid_t knh_Asm_newLabelId(Ctx *ctx, Asm *abr, Token *tk)
{
	KNH_ASSERT(tk == NULL || IS_Token(tk));
	knh_labelid_t newlabel = knh_Asm_findLabelId(ctx, abr, tk);
	if(newlabel != (knh_labelid_t)-1) {
		DBG_P("DUPLICATED LABEL id = %d", (int)newlabel);
		return newlabel; /* DUPLICATED */
	}

	if(DP(abr)->labelmax == DP(abr)->labelcapacity) {
		if(DP(abr)->labelcapacity == 0) DP(abr)->labelcapacity = 32;
		DP(abr)->labelcapacity *= 2;
		knh_labeltbl_t *newtable =
			(knh_labeltbl_t*)KNH_MALLOC(ctx, sizeof(knh_labeltbl_t) * DP(abr)->labelcapacity);
		if(DP(abr)->labelmax > 0) {
			knh_memcpy(newtable, DP(abr)->labels, sizeof(knh_labeltbl_t) * DP(abr)->labelmax);
		}
		size_t i;
		for(i = DP(abr)->labelmax; i < DP(abr)->labelcapacity; i++) {
			newtable[i].offset = -1;
			KNH_INITv(newtable[i].tklabel, KNH_NULL);
		}
		DP(abr)->labels = newtable;
	}
	newlabel = DP(abr)->labelmax;
	DP(abr)->labelmax += 1;
	DP(abr)->labels[newlabel].offset = -1; // carefully
	if(tk != NULL) {
		KNH_SETv(ctx, DP(abr)->labels[newlabel].tklabel, tk);
	}
	return newlabel;
}

/* ------------------------------------------------------------------------ */

static
void KNH_ASM_LLABEL(Ctx *ctx, Asm *abr, knh_labelid_t label)
{
	int offset = (int)knh_Bytes_size(DP(abr)->elf);
	KNH_ASM_ASSERT(ctx, abr, label < (int)DP(abr)->labelmax);
	if(DP(abr)->labels[label].offset != -1) {
		KNH_ASM_PANIC(ctx, abr, "DUPLICATED LABEL id = %d", (int)label);
	}
	DP(abr)->labels[label].offset = offset;
}

/* ------------------------------------------------------------------------ */

static
void KNH_ASM_GLABEL(Ctx *ctx, Asm *abr, knh_labelid_t label)
{
	KNH_ASM_LLABEL(ctx, abr, label);
	knh_rtti_reset(abr);
}

/* ------------------------------------------------------------------------ */

static
int TERMs_isCALLISNUL(Stmt *stmt, size_t n)
{
	if(IS_Stmt(DP(stmt)->stmts[n])) {
		Token *tk = DP(DP(stmt)->stmts[n])->tokens[0];
		return (IS_Token(tk) && IS_Method(DP(tk)->mtd) && DP(DP(tk)->mtd)->mn == METHODN_isNull);
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static
int TERMs_isCALLISNN(Stmt *stmt, size_t n)
{
	if(IS_Stmt(DP(stmt)->stmts[n])) {
		Token *tk = DP(DP(stmt)->stmts[n])->tokens[0];
		return (IS_Token(tk) && IS_Method(DP(tk)->mtd) && DP(DP(tk)->mtd)->mn == METHODN_isNotNull);
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

#define _KNH_ASM_JMP(ctx, abr, l)  KNH_ASM_JMP_(ctx, abr, l);

/* ------------------------------------------------------------------------ */

static
void TERMs_ASM_JIFNUL(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, knh_labelid_t label)
{
	Token *tk = DP(stmt)->tokens[n];
	if(IS_Token(tk) && TT_(tk) == TT_LOCAL /*TT_LOCAL ??*/) {
		KNH_ASM_JIFNUL_(ctx, abr, label, sfi_(DP(tk)->index));
	}
	else {
		TERMs_asm(ctx, stmt, n, abr, TERMs_gettype(stmt, n), DP(abr)->stack);
		KNH_ASM_JIFNUL_(ctx, abr, label, sfi_(DP(abr)->stack));
	}
}

/* ------------------------------------------------------------------------ */

static
void TERMs_ASM_JIFNN(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, knh_labelid_t label)
{
	Token *tk = DP(stmt)->tokens[n];
	if(IS_Token(tk) && TT_(tk) == TT_LOCAL /*TT_LOCAL ??*/) {
		KNH_ASM_JIFNN_(ctx, abr, label, sfi_(DP(tk)->index));
	}
	else {
		TERMs_asm(ctx, stmt, n, abr, TERMs_gettype(stmt, n), DP(abr)->stack);
		KNH_ASM_JIFNN_(ctx, abr, label, sfi_(DP(abr)->stack));
	}
}

/* ------------------------------------------------------------------------ */

static
void TERMs_ASM_JIFF(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, knh_labelid_t label)
{
	Token *tk = DP(stmt)->tokens[n];
	if(IS_Token(tk) && TT_(tk) == TT_LOCAL /*TT_LOCAL ??*/) {
		KNH_ASM_bJIFF_(ctx, abr, label, sfi_(DP(tk)->index));
	}
	else {
		if(TERMs_isCALLISNUL(stmt, n)) {
			// o == null -> false  o == null;
			TERMs_ASM_JIFNN(ctx, DP(stmt)->stmts[n], 1, abr, label);
			return;
		}
		else if(TERMs_isCALLISNN(stmt, n)) {
			TERMs_ASM_JIFNUL(ctx, DP(stmt)->stmts[n], 1, abr, label);
			return;
		}
		TERMs_asm(ctx, stmt, n, abr, NNTYPE_Boolean, DP(abr)->stack);
		KNH_ASM_bJIFF_(ctx, abr, label, sfi_(DP(abr)->stack));
	}
}

/* ------------------------------------------------------------------------ */

static
void TERMs_ASM_JIFF_LOOP(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, knh_labelid_t label)
{
	Token *tk = DP(stmt)->tokens[n];
	if(IS_Token(tk) && TT_(tk) == TT_LOCAL /*TT_LOCAL ??*/) {
		KNH_ASM_bJIFF_LOOP_(ctx, abr, label, sfi_(DP(tk)->index));
	}
	else {
		if(TERMs_isCALLISNUL(stmt, n)) {
			// o == null -> false  o == null;
			TERMs_ASM_JIFNN(ctx, DP(stmt)->stmts[n], 1, abr, label);
			return;
		}
		else if(TERMs_isCALLISNN(stmt, n)) {
			TERMs_ASM_JIFNUL(ctx, DP(stmt)->stmts[n], 1, abr, label);
			return;
		}
		TERMs_asm(ctx, stmt, n, abr, NNTYPE_Boolean, DP(abr)->stack);
		KNH_ASM_bJIFF_LOOP_(ctx, abr, label, sfi_(DP(abr)->stack));
	}
}

/* ------------------------------------------------------------------------ */

static
void TERMs_ASM_JIFT(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, knh_labelid_t label)
{
	Token *tk = DP(stmt)->tokens[n];
	if(IS_Token(tk) && TT_(tk) == TT_LOCAL /*TT_LOCAL ??*/) {
		KNH_ASM_bJIFT_(ctx, abr, label, sfi_(DP(tk)->index));
	}
	else {
		if(TERMs_isCALLISNUL(stmt, n)) {
			// o == null -> false  o == null;
			TERMs_ASM_JIFNN(ctx, DP(stmt)->stmts[n], 1, abr, label);
			return;
		}
		else if(TERMs_isCALLISNN(stmt, n)) {
			TERMs_ASM_JIFNUL(ctx, DP(stmt)->stmts[n], 1, abr, label);
			return;
		}
		TERMs_asm(ctx, stmt, n, abr, NNTYPE_Boolean, DP(abr)->stack);
		KNH_ASM_bJIFT_(ctx, abr, label, sfi_(DP(abr)->stack));
	}
}

/* ------------------------------------------------------------------------ */

static
void TERMs_ASM_THROW(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr)
{
	Token *tk = DP(stmt)->tokens[n];

	if(IS_Token(tk) && TT_(tk) == TT_LOCAL /*TT_LOCAL ??*/) {
		KNH_ASM_THROW_(ctx, abr, knh_Asm_inTry(abr), sfi_(DP(tk)->index));
	}
	else {
		TERMs_asm(ctx, stmt, n, abr, NNTYPE_Exception, DP(abr)->stack);
		KNH_ASM_THROW_(ctx, abr, knh_Asm_inTry(abr), sfi_(DP(abr)->stack));
	}
}

/* ------------------------------------------------------------------------ */
/* [EXPR] */
/* ------------------------------------------------------------------------ */
/* @data */
/* ------------------------------------------------------------------------ */

static
knh_type_t knh_Method_reqtTERMs(Method *mtd, knh_class_t mtd_cid, Stmt *stmt, size_t n)
{
	if(!IS_Method(mtd)) {
		return TYPE_Any;  // boxing
	}
	if(n == 1) { // base
		return knh_Method_isNullBase(mtd) ? NATYPE_cid(mtd_cid) : NNTYPE_cid(mtd_cid);
	}
	else {
		knh_type_t ptype = knh_Method_pztype(mtd, n - 2);
		if(ptype == TYPE_Object || ptype == TYPE_T1 || ptype == TYPE_T2) {
			return TYPE_Any; // boxing
		}
		if(ptype == NNTYPE_Object || ptype == NNTYPE_T1 || ptype == NNTYPE_T2) {
			return NNTYPE_Any; // boxing
		}
		if(ptype == NNTYPE_This) return NNTYPE_cid(mtd_cid);
		if(ptype == TYPE_This) return mtd_cid;
		return ptype;
	}
}

/* ------------------------------------------------------------------------ */

static
int TERMs_putLOCAL(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, knh_type_t reqt, int sfpidx)
{
	Token *tk = DP(stmt)->tokens[n];
	if(IS_Token(tk) && TT_(tk) == TT_LOCAL) {
		int a = DP(tk)->index;
		if(!IS_NNTYPE(knh_rtti_type(abr, DP(tk)->type, a))) {
			KNH_ASM_CHECKNULL_(ctx, abr, a);
			knh_rtti_nullChecked(abr, a);
		}
		return a;
	}
	TERMs_asm(ctx, stmt, n, abr, reqt, sfpidx);
	return sfpidx;
}

/* ------------------------------------------------------------------------ */

static
int knh_StmtOP_checkConst(Ctx *ctx, Stmt *stmt, knh_methodn_t *mn, int swap)
{
	Term *tm = DP(stmt)->terms[1];
	if(swap && IS_Token(tm) && TT_((Token*)tm) == TT_CONST) {
		DP(stmt)->terms[1] = DP(stmt)->terms[2];
		DP(stmt)->terms[2] = tm;
		if(*mn == METHODN_opLt) *mn = METHODN_opGte;
		else if(*mn == METHODN_opLte) *mn = METHODN_opGt;
		else if(*mn == METHODN_opGt) *mn = METHODN_opLte;
		else if(*mn == METHODN_opGte) *mn = METHODN_opLt;
	}
	Token *tk = DP(stmt)->tokens[2];
	return (IS_Token(tk) && TT_(tk) == TT_CONST);
}

/* ------------------------------------------------------------------------ */

static
knh_int_t TERMs_int(Stmt *stmt, size_t n)
{
	Token *tk = DP(stmt)->tokens[n];
	KNH_ASSERT(TT_(tk) == TT_CONST);
	return (DP(tk)->num)->n.ivalue;
}

/* ------------------------------------------------------------------------ */

static
knh_float_t TERMs_float(Stmt *stmt, size_t n)
{
	Token *tk = DP(stmt)->tokens[n];
	KNH_ASSERT(TT_(tk) == TT_CONST);
	return (DP(tk)->num)->n.fvalue;
}

/* ------------------------------------------------------------------------ */

static
int IS_OPSIM(knh_methodn_t mn)
{
	switch(mn) {
	case METHODN_opAdd:
	case METHODN_opMul:
	case METHODN_opEq:
	case METHODN_opNeq:
	case METHODN_opLt:
	case METHODN_opLte:
	case METHODN_opGt:
	case METHODN_opGte:
		return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static
int IS_OPASIM(knh_methodn_t mn)
{
	switch(mn) {
	case METHODN_opSub:
	case METHODN_opDiv:
	case METHODN_opMod:
		return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static
int knh_StmtOP_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx)
{
	int local = ASML(abr, sfpidx);
	Method *mtd = DP(DP(stmt)->tokens[0])->mtd;
	if(IS_NULL(mtd)) return 0;
	knh_methodn_t mn = DP(mtd)->mn;
	knh_class_t cid = CLASS_type(DP(DP(stmt)->tokens[1])->type);

	if(cid == CLASS_Int) {
		if(IS_OPSIM(mn)) {
			if(knh_StmtOP_checkConst(ctx, stmt, &mn, /*swap*/ 1)) {
				int a = TERMs_putLOCAL(ctx, stmt, 1, abr, NNTYPE_Int, local + 1);
				knh_int_t b = TERMs_int(stmt, 2);
				switch(mn) {
				case METHODN_opAdd:
					KNH_ASM_iADDn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opMul:
					KNH_ASM_iMULn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opEq:
					KNH_ASM_iEQn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opNeq:
					KNH_ASM_iNEQn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opLt:
					KNH_ASM_iLTn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opLte:
					KNH_ASM_iLTEn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opGt:
					KNH_ASM_iGTn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opGte:
					KNH_ASM_iGTEn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				}
				return 0;
			}
			else {
				int a = TERMs_putLOCAL(ctx, stmt, 1, abr, NNTYPE_Int, local + 1);
				int b = TERMs_putLOCAL(ctx, stmt, 2, abr, NNTYPE_Int, local + 2);
				switch(mn) {
				case METHODN_opAdd:
					KNH_ASM_iADD_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opMul:
					KNH_ASM_iMUL_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opEq:
					KNH_ASM_iEQ_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opNeq:
					KNH_ASM_iNEQ_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opLt:
					KNH_ASM_iLT_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opLte:
					KNH_ASM_iLTE_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opGt:
					KNH_ASM_iGT_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opGte:
					KNH_ASM_iGTE_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				}
				return 0;
			}
		}
		else if(IS_OPASIM(mn)) {
			if(knh_StmtOP_checkConst(ctx, stmt, &mn, /*swap*/ 0)) {
				int a = TERMs_putLOCAL(ctx, stmt, 1, abr, NNTYPE_Int, local + 1);
				knh_int_t b = TERMs_int(stmt, 2);
				switch(mn) {
				case METHODN_opSub:
					KNH_ASM_iSUBn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opDiv:
					if(b == 0) {
						b = 1;
						knh_Asm_perror(ctx, abr, KERR_ERRATA, _("divided by zero: /0 ==> /1"));
					}
					KNH_ASM_iDIVn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;

				case METHODN_opMod:
					if(b == 0) {
						b = 1;
						knh_Asm_perror(ctx, abr, KERR_ERRATA, _("divided by zero: %0 ==> %1"));
					}
					KNH_ASM_iMODn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				}
			}
			else {
				int a = TERMs_putLOCAL(ctx, stmt, 1, abr, NNTYPE_Int, local + 1);
				int b = TERMs_putLOCAL(ctx, stmt, 2, abr, NNTYPE_Int, local + 2);
				switch(mn) {
				case METHODN_opSub:
					KNH_ASM_iSUB_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opDiv:
					KNH_ASM_iDIV_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opMod:
					KNH_ASM_iMOD_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				}
			}
			return 0;
		}
	} /* CLASS_Int */
	if(cid == CLASS_Float) {
		if(IS_OPSIM(mn)) {
			if(knh_StmtOP_checkConst(ctx, stmt, &mn, /*swap*/ 1)) {
				int a = TERMs_putLOCAL(ctx, stmt, 1, abr, NNTYPE_Float, local + 1);
				knh_float_t b = TERMs_float(stmt, 2);
				switch(mn) {
				case METHODN_opAdd:
					KNH_ASM_fADDn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opMul:
					KNH_ASM_fMULn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opEq:
					KNH_ASM_fEQn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opNeq:
					KNH_ASM_fNEQn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opLt:
					KNH_ASM_fLTn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opLte:
					KNH_ASM_fLTEn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opGt:
					KNH_ASM_fGTn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opGte:
					KNH_ASM_fGTEn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				}
				return 0;
			}
			else {
				int a = TERMs_putLOCAL(ctx, stmt, 1, abr, NNTYPE_Float, local + 1);
				int b = TERMs_putLOCAL(ctx, stmt, 2, abr, NNTYPE_Float, local + 2);
				switch(mn) {
				case METHODN_opAdd:
					KNH_ASM_fADD_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opMul:
					KNH_ASM_fMUL_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opEq:
					KNH_ASM_fEQ_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opNeq:
					KNH_ASM_fNEQ_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opLt:
					KNH_ASM_fLT_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opLte:
					KNH_ASM_fLTE_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opGt:
					KNH_ASM_fGT_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opGte:
					KNH_ASM_fGTE_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				}
				return 0;
			}
		}
		else if(IS_OPASIM(mn)) {
			if(knh_StmtOP_checkConst(ctx, stmt, &mn, /*swap*/ 0)) {
				int a = TERMs_putLOCAL(ctx, stmt, 1, abr, NNTYPE_Float, local + 1);
				knh_float_t b = TERMs_float(stmt, 2);
				switch(mn) {
				case METHODN_opSub:
					KNH_ASM_fSUBn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opDiv:
#ifndef KONOHA_ON_LKM
					if(b == 0.0) {
						b = 1.0;
						knh_Asm_perror(ctx, abr, KERR_ERRATA, _("divided by zero: 0.0 ==> 1.0"));
					}
#else
					if(b == 0) {
						b = 1;
						knh_Asm_perror(ctx, abr, KERR_ERRATA, _("divided by zero: 0.0 ==> 1.0"));
					}
#endif
					KNH_ASM_fDIVn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				}
			}
			else {
				int a = TERMs_putLOCAL(ctx, stmt, 1, abr, NNTYPE_Float, local + 1);
				int b = TERMs_putLOCAL(ctx, stmt, 2, abr, NNTYPE_Float, local + 2);
				switch(mn) {
				case METHODN_opSub:
					KNH_ASM_fSUB_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				case METHODN_opDiv:
					KNH_ASM_fDIV_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(b));
					return 1;
				}
			}
			return 0;
		}
	} /* CLASS_Float */
	return 0;
}

/* ------------------------------------------------------------------------ */

static
int TERMs_isLOCAL(Stmt *stmt, size_t n)
{
	Token *tk = DP(stmt)->tokens[n];
	return (IS_Token(tk) && TT_(tk) == TT_LOCAL);
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtCALL_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx)
{
	if(knh_StmtOP_asm(ctx, stmt, abr, reqt, sfpidx)) return ;
	int local = ASML(abr, sfpidx);
	Method *mtd = DP(DP(stmt)->tokens[0])->mtd;
	knh_class_t cid = TERMs_getcid(stmt, 1);
	size_t i;
	/* UNTYPED CLOSURE */
	if(cid == CLASS_Closure && IS_Method(mtd) && DP(mtd)->mn == METHODN_invoke) {
		for(i = 1; i < DP(stmt)->size; i++) {
			TERMs_asm(ctx, stmt, i, abr, TYPE_Any, local + i);
		}
		KNH_ASM_AINVOKE_(ctx, abr, sfi_(local), (knh_ushort_t)DP(stmt)->size/*, UP(mtd)*/);
		goto L_RTYPE;
	}
	/* INSTRUCTION */
	if(cid == CLASS_Array || cid == CLASS_IArray || cid == CLASS_FArray) {
		if(DP(mtd)->mn == METHODN_get) {
			int a = TERMs_putLOCAL(ctx, stmt, 1, abr, NNTYPE_Array, local + 1);
			if(TERMs_isCONST(stmt, 2)) {
				knh_intptr_t n = (knh_intptr_t)TERMs_int(stmt, 2);
				if(cid == CLASS_Array) {
					KNH_ASM_AGETn_(ctx, abr, sfi_(sfpidx), sfi_(a), n);
				}
				else if(cid == CLASS_IArray) {
					KNH_ASM_IAGETn_(ctx, abr, sfi_(sfpidx), sfi_(a), n);
				}
				else {
					KNH_ASM_FAGETn_(ctx, abr, sfi_(sfpidx), sfi_(a), n);
				}
			}
			else {
				int an = TERMs_putLOCAL(ctx, stmt, 2, abr, NNTYPE_Int, local + 2);
				if(cid == CLASS_Array) {
					KNH_ASM_AGET_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(an));
				}
				else if(cid == CLASS_IArray) {
					KNH_ASM_IAGET_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(an));
				}
				else {
					KNH_ASM_FAGET_(ctx, abr, sfi_(sfpidx), sfi_(a), sfi_(an));
				}
			}
			return;
		}
		if(DP(mtd)->mn == METHODN_set) {
			int a = TERMs_putLOCAL(ctx, stmt, 1, abr, NNTYPE_Array, local + 1);
			knh_type_t ptype = knh_Method_ptype(ctx, mtd, cid, 1);
			int v = TERMs_putLOCAL(ctx, stmt, 3, abr, ptype, local + 3);
			if(TERMs_isCONST(stmt, 2)) {
				knh_intptr_t n = (knh_intptr_t)TERMs_int(stmt, 2);
				if(cid == CLASS_Array) {
					KNH_ASM_ASETn_(ctx, abr, sfi_(v), sfi_(a), n);
				}
				else if(cid == CLASS_IArray) {
					KNH_ASM_IASETn_(ctx, abr, sfi_(v), sfi_(a), n);
				}
				else {
					KNH_ASM_FASETn_(ctx, abr, sfi_(v), sfi_(a), n);
				}
			}
			else {
				int an = TERMs_putLOCAL(ctx, stmt, 2, abr, NNTYPE_Int, local + 2);
				if(cid == CLASS_Array) {
					KNH_ASM_ASET_(ctx, abr, sfi_(v), sfi_(a), sfi_(an));
				}
				else if(cid == CLASS_IArray) {
					KNH_ASM_IASET_(ctx, abr, sfi_(v), sfi_(a), sfi_(an));
				}
				else {
					KNH_ASM_FASET_(ctx, abr, sfi_(v), sfi_(a), sfi_(an));
				}
			}
			return;
		}
	}/* INSTRUCTION*/

	/* PEEPHOLE */
	if(IS_Method(mtd) && knh_Method_isFinal(mtd) && TERMs_isLOCAL(stmt, 1)) {
		int a = DP(DP(stmt)->tokens[1])->index;
		knh_type_t reqt2 = knh_Method_reqtTERMs(mtd, cid, stmt, 1);
		knh_type_t vart2 = knh_rtti_type(abr, TERMs_gettype(stmt, 1), a);
		if(IS_NNTYPE(reqt2) && !IS_NNTYPE(vart2)) {
			KNH_ASM_CHECKNULL_(ctx, abr, sfi_(a));
			knh_rtti_nullChecked(abr, a);
		}
		for(i = 2; i < DP(stmt)->size; i++) {
			reqt2 = knh_Method_reqtTERMs(mtd, cid, stmt, i);
			TERMs_asm(ctx, stmt, i, abr, reqt2, local + i);
		}
		KNH_ASM_FCALL_(ctx, abr, sfi_(local), (knh_ushort_t)DP(stmt)->size, sfi_(a), UP(mtd));
		goto L_RTYPE;
	}/*PEEPHOLE*/
	for(i = 1; i < DP(stmt)->size; i++) {
		knh_type_t reqt2 = knh_Method_reqtTERMs(mtd, cid, stmt, i);
		TERMs_asm(ctx, stmt, i, abr, reqt2, local + i);
	}
	KNH_ASM_CALL(ctx, abr, reqt, local, DP(stmt)->tokens[0], DP(stmt)->size - 2);

	L_RTYPE:;
	knh_type_t rtype = DP(stmt)->type;
	if(IS_ubxtype(rtype)) {
		nMOVL(ctx, abr, local, sfpidx);
	}
	else {
		MOVL(ctx, abr, local, sfpidx);
	}
}

/* ------------------------------------------------------------------------ */

static
knh_flag_t knh_StmtNEW_flag(Ctx *ctx, Stmt *stmt)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtNEW_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx)
{
	int local = ASML(abr, sfpidx);
	Method *mtd = DP(DP(stmt)->tokens[0])->mtd;
	knh_class_t cid = DP(DP(stmt)->tokens[1])->cid;
	size_t i;
	for(i = 2; i < DP(stmt)->size; i++) {
		knh_type_t reqt = knh_Method_reqtTERMs(mtd, cid, stmt, i);
		TERMs_asm(ctx, stmt, i, abr, reqt, local + i);
	}
	KNH_ASM_NEW(ctx, abr, reqt, local, DP(stmt)->tokens[0],
			knh_StmtNEW_flag(ctx, stmt), cid, DP(stmt)->size - 2);
	MOVL(ctx, abr, local, sfpidx);
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtMAPCAST_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx)
{
	int local = ASML(abr, sfpidx);
	knh_type_t srct = TERMs_gettype(stmt, 1);
	TERMs_asm(ctx, stmt, 1, abr, TYPE_Any, local);
//	if(knh_Stmt_isNNCAST(stmt)) {
//		KNH_ASM_NNMAP_(ctx, abr, local, DP(DP(stmt)->tokens[0])->cid);
//	}
//	else {
		KNH_ASM_MAP(ctx, abr, reqt, local, DP(stmt)->tokens[0], srct, knh_Stmt_isNNCAST(stmt));
//	}
	MOVL(ctx, abr, local, sfpidx);
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtMT_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx)
{
	int local = ASML(abr, sfpidx);
	TERMs_asm(ctx, stmt, 1, abr, TYPE_Any, local);
	Token *tk = DP(stmt)->tokens[0];
	if(DP(stmt)->size == 2) {
		KNH_ASM_TOSTR_(ctx, abr, local, DP(tk)->mn);
	}
	else {
		String *fmt = DP(DP(stmt)->tokens[2])->text;
		KNH_ASM_ASSERT(ctx, abr, IS_String(fmt));
		KNH_ASM_TOSTRf_(ctx, abr, local, DP(tk)->mn, UP(fmt));
	}
	MOVL(ctx, abr, local, sfpidx);
}

/* ------------------------------------------------------------------------ */

void knh_StmtALT_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx)
{
	knh_labelid_t label = knh_Asm_newLabelId(ctx, abr, NULL);
	int local = ASML(abr, sfpidx);
	int i, size = DP(stmt)->size;
	knh_type_t reqc = CLASS_type(reqt);
	for(i = 0; i < size - 1; i++) {
		TERMs_asm(ctx, stmt, i, abr, reqc, local);
		TERMs_ASM_JIFNN(ctx, stmt, i, abr, label);
	}
	KNH_ASM_LLABEL(ctx, abr, label);
	MOVL(ctx, abr, local, sfpidx);
}

/* ------------------------------------------------------------------------ */

void knh_StmtOR_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx)
{
	int local = ASML(abr, sfpidx);
	knh_labelid_t label = knh_Asm_newLabelId(ctx, abr, NULL);
	int i, size = DP(stmt)->size;
	for(i = 0; i < size; i++) {
		TERMs_asm(ctx, stmt, i, abr, NNTYPE_Boolean, local);
		TERMs_ASM_JIFT(ctx, stmt, i, abr, label);
	}
	KNH_ASM_LLABEL(ctx, abr, label);
	nMOVL(ctx, abr, local, sfpidx);
}

/* ------------------------------------------------------------------------ */

void knh_StmtAND_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx)
{
	int local = ASML(abr, sfpidx);
	knh_labelid_t label = knh_Asm_newLabelId(ctx, abr, NULL);
	int i, size = DP(stmt)->size;
	for(i = 0; i < size; i++) {
		TERMs_asm(ctx, stmt, i, abr, NNTYPE_Boolean, local);
		TERMs_ASM_JIFF(ctx, stmt, i, abr, label);
	}
	KNH_ASM_LLABEL(ctx, abr, label);
	nMOVL(ctx, abr, local, sfpidx);
}

/* ------------------------------------------------------------------------ */

void knh_StmtTRI_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx)
{
	int local = ASML(abr, sfpidx);
	knh_labelid_t lbelse = knh_Asm_newLabelId(ctx, abr, NULL);
	knh_labelid_t lbend  = knh_Asm_newLabelId(ctx, abr, NULL);
	TERMs_asm(ctx, stmt, 0, abr, NNTYPE_Boolean, local);
	TERMs_ASM_JIFF(ctx, stmt, 0, abr, lbelse);

	TERMs_asm(ctx, stmt, 1, abr, reqt, local);
	KNH_ASM_JMP(ctx, abr, lbend);

	/* else */
	KNH_ASM_LLABEL(ctx, abr, lbelse);
	TERMs_asm(ctx, stmt, 2, abr, reqt, local);
	KNH_ASM_LLABEL(ctx, abr, lbend);

	MOVL(ctx, abr, local, sfpidx);
}

/* ------------------------------------------------------------------------ */

void knh_StmtLET_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx)
{
	Token *tkL = DP(stmt)->tokens[0];
	if(TT_(tkL) == TT_LOCAL) {
		TERMs_asm(ctx, stmt, 1, abr, DP(tkL)->type, DP(tkL)->index);
		if(reqt != TYPE_void) {
			KNH_ASM_SMOV(ctx, abr, reqt, sfpidx, tkL);
		}
	}
	else if(IS_Token(DP(stmt)->tokens[1])) {
		KNH_ASM_MOV(ctx, abr, tkL, DP(stmt)->tokens[1]);
		if(reqt != TYPE_void) {
			KNH_ASM_SMOV(ctx, abr, reqt, sfpidx, tkL);
		}
	}
	else {
		int local = ASML(abr, sfpidx);
		knh_token_t tt = TT_(tkL); /* NOTE: ltk is reused inside stmt */
		knh_short_t index = DP(tkL)->index;
		TERMs_asm(ctx, stmt, 1, abr, DP(tkL)->type, local);
		TT_(tkL) = tt;
		DP(tkL)->index = index;
		KNH_ASM_MOV(ctx, abr, tkL, DP(stmt)->tokens[1]);
		if(reqt != TYPE_void && local != sfpidx) {
			KNH_ASM_SMOV(ctx, abr, reqt, sfpidx, tkL);
		}
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_Token_toLOCAL(Ctx *ctx, Token *tk, knh_type_t type, int sfpidx)
{
	TT_(tk) = TT_LOCAL;
	DP(tk)->index = (knh_short_t)sfpidx;
	DP(tk)->type = type;
}

/* ------------------------------------------------------------------------ */

static
Token *knh_Stmt_toLOCAL(Ctx *ctx, Stmt *stmt, int sfpidx, knh_type_t reqt, int level)
{
//	DBG2_P("stt=%s, toLOCAL=%d", knh_stmt_tochar(SP(stmt)->stt), sfpidx);
	size_t i;
	for(i = 0; i < DP(stmt)->size; i++) {
		if(IS_Token(DP(stmt)->tokens[i])) {
			knh_Token_toLOCAL(ctx, DP(stmt)->tokens[i], reqt, sfpidx);
			return DP(stmt)->tokens[i];
		}
		else {
			Token *tk = knh_Stmt_toLOCAL(ctx, DP(stmt)->stmts[i], reqt, sfpidx, 1);
			if(tk != NULL) return tk;
		}
	}
	if(level == 1) return NULL;
	Token *tk = new_TokenNULL(ctx, FL(stmt), reqt);
	knh_Token_toLOCAL(ctx, tk, reqt, sfpidx);
	return tk;
}

/* ------------------------------------------------------------------------ */

void
knh_StmtEXPR_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx)
{
	KNH_ASSERT(IS_Stmt(stmt));
	switch(SP(stmt)->stt) {
	case STT_CALL:
	case STT_OP:
		knh_StmtCALL_asm(ctx, stmt, abr, reqt, sfpidx);
		break;
	case STT_NEW:
		knh_StmtNEW_asm(ctx, stmt, abr, reqt, sfpidx);
		break;
	case STT_MT:
		knh_StmtMT_asm(ctx, stmt, abr, reqt, sfpidx);
		break;
	case STT_MAPCAST:
		knh_StmtMAPCAST_asm(ctx, stmt, abr, reqt, sfpidx);
		break;
	case STT_ALT:
		knh_StmtALT_asm(ctx, stmt, abr, reqt, sfpidx);
		break;
	case STT_AND:
		knh_StmtAND_asm(ctx, stmt, abr, reqt, sfpidx);
		break;
	case STT_OR:
		knh_StmtOR_asm(ctx, stmt, abr, reqt, sfpidx);
		break;
	case STT_TRI:
		knh_StmtTRI_asm(ctx, stmt, abr, reqt, sfpidx);
		break;
	case STT_LET:
		knh_StmtLET_asm(ctx, stmt, abr, reqt, sfpidx);
		break;
	default:
		KNH_ASM_PANIC(ctx, abr, "unknown stt=%s", knh_stmt_tochar(SP(stmt)->stt));
	}
	if(IS_ANY(reqt)) {
		KNH_ASM_NNBOX(ctx, abr, DP(stmt)->type, sfpidx);
	}
	else if(IS_NNTYPE(reqt) && !IS_NNTYPE(DP(stmt)->type)) {
		KNH_ASM_CHECKNULL_(ctx, abr, sfpidx);
	}
}

/* ------------------------------------------------------------------------ */

static
void TERMs_asm(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, knh_type_t reqt, int sfpidx)
{
	if(IS_Token(DP(stmt)->tokens[n])) {
		Token *tk = DP(stmt)->tokens[n];
		KNH_ASM_SMOV(ctx, abr, reqt, sfpidx, tk);
		knh_Token_toLOCAL(ctx, tk, reqt, sfpidx);
	}
	else {
		knh_StmtEXPR_asm(ctx, DP(stmt)->stmts[n], abr, reqt, sfpidx);
		KNH_SETv(ctx, DP(stmt)->tokens[n], knh_Stmt_toLOCAL(ctx, DP(stmt)->stmts[n], sfpidx, reqt, 0));
	}
}

/* ======================================================================== */
/* [LABEL]  */


static
Token *knh_StmtMETA_getLabelNULL(Ctx *ctx, Stmt *o)
{
	if(IS_DictMap(DP(o)->metaDictMap)) {
		Token *tk = (Token*)knh_DictMap_get(ctx, DP(o)->metaDictMap, TS_ATlabel);
		if(IS_Token(tk)) return tk;
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
knh_labelid_t knh_Asm_pushLabelStack(Ctx *ctx, Asm *abr, Stmt *stmt)
{
	Token *tkL = knh_StmtMETA_getLabelNULL(ctx, stmt);
	if(tkL == NULL) {
		char lbn[8];
		knh_snprintf(lbn, sizeof(lbn), "%d", DP(abr)->llstep);
		tkL = new_TokenCONST(ctx, FL(stmt), UP(new_String(ctx, B(lbn), NULL)));
		TT_(tkL) = TT_LABEL;
	}
	DP(tkL)->index = (DP(abr)->llstep)++;
	knh_Array_add(ctx, DP(abr)->lstacks, UP(tkL));
	{
		knh_labelid_t labelid = knh_Asm_newLabelId(ctx, abr, tkL);
		knh_labelid_t labelid2 = knh_Asm_newLabelId(ctx, abr, NULL);
		if(labelid + 1 == labelid2) {
			return labelid;
		}
		else {
			DBG2_P("label %s (begin, end) = %d, %d", sToken(tkL), labelid, labelid2);
			KNH_ASSERT(labelid + 1 == labelid2);
			return labelid;
		}
	}
}

/* ------------------------------------------------------------------------ */

static
knh_labelid_t knh_Asm_stackLabelId(Ctx *ctx, Asm *abr, Stmt *stmt)
{
	size_t s = knh_Array_size(DP(abr)->lstacks);
	if(s == 0) {
		knh_Asm_perror(ctx, abr, KERR_ERROR, _("don't use '%s' HERE"), knh_stmt_tochar(SP(stmt)->stt));
		knh_Stmt_done(ctx, stmt);
		return -1;
	}
	else {
		Token *tkL = NULL;
		if(DP(stmt)->size == 1) {
			tkL = DP(stmt)->tokens[0];
			if(TT_(tkL) == TT_ASIS) tkL = NULL;
		}
		if(tkL != NULL) {
			int i;
			for(i = s - 1; i >= 0; i--) {
				Token *tk2 = (Token*)knh_Array_n(DP(abr)->lstacks, i);
				//DBG2_P("i=%d, %s %s", i, sToken(tkL), sToken(tk2));
				if(knh_String_equals(DP(tkL)->text, knh_String_tobytes(DP(tk2)->text))) {
					tkL = tk2;
					break;
				}
			}
			if(tkL == NULL) {
				knh_Asm_perror(ctx, abr, KERR_EWARN, _("unknown label: %s"), sToken(tkL));
			}
		}
		if(tkL == NULL) {
			tkL = (Token*)knh_Array_n(DP(abr)->lstacks, s-1);
		}
		return knh_Asm_findLabelId(ctx, abr, tkL);
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_Asm_popLabelStack(Ctx *ctx, Asm *abr)
{
	knh_Array_pop(ctx, DP(abr)->lstacks);
}

/* ------------------------------------------------------------------------ */
/* [IT] */

static
Token *knh_Stmt_get_IT(Ctx *ctx, Stmt *stmt, Asm *abr, int index)
{
	DBG2_ASSERT(index < DP(stmt)->used_stack);
	int n = DP(stmt)->size - DP(stmt)->used_stack + index;
	Token *tk = DP(stmt)->tokens[n];
	DBG2_ASSERT(TT_(tk) == TT_LOCAL);
	if(DP(tk)->index == index) {
		DP(tk)->index = DP(abr)->stack - DP(stmt)->used_stack + index;
	}
	return tk;
}

/* ======================================================================== */
/* [IF, WHILE, DO, FOR, FOREACH]  */

/* ------------------------------------------------------------------------ */

static
void TERMs_asmBLOCK(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr)
{
	KNH_ASM_ASSERT(ctx, abr, IS_Stmt(DP(stmt)->stmts[n]));
	knh_Stmt_asmBLOCK(ctx, DP(stmt)->stmts[n], abr, 1);
}

/* ------------------------------------------------------------------------ */

static
int TERMs_isDONE(Stmt *stmt, size_t n)
{
	Stmt *cur = DP(stmt)->stmts[n];
	return (IS_Stmt(cur) && SP(cur)->stt == STT_DONE);
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtIF_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	knh_labelid_t lbelse = knh_Asm_newLabelId(ctx, abr, NULL);
	knh_labelid_t lbend = knh_Asm_newLabelId(ctx, abr, NULL);
	/* if */
	TERMs_ASM_JIFF(ctx, stmt, 0, abr, lbelse);
	/*then*/
	TERMs_asmBLOCK(ctx, stmt, 1, abr);
	if(TERMs_isDONE(stmt, 2)) {
		/* PEEPHOLE this isn't a bug */
		KNH_ASM_LLABEL(ctx, abr, lbelse);
		return ;
	}
	KNH_ASM_JMP(ctx, abr, lbend);
	/* else */
	KNH_ASM_LLABEL(ctx, abr, lbelse);
	TERMs_asmBLOCK(ctx, stmt, 2, abr);
	/* endif */
	KNH_ASM_LLABEL(ctx, abr, lbend);
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtSWITCH_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	Stmt *stmtCASE;
	Token *tkIT = knh_Stmt_get_IT(ctx, stmt, abr, 0);
	knh_labelid_t lbcontinue = knh_Asm_pushLabelStack(ctx, abr, stmt);
	knh_labelid_t lbbreak = lbcontinue + 1;
	KNH_ASM_GLABEL(ctx, abr, lbcontinue);
	TERMs_asm(ctx, stmt, 0, abr, DP(tkIT)->type, sfi_(DP(tkIT)->index));
	stmtCASE = DP(stmt)->stmts[1];
	while(IS_Stmt(stmtCASE)) {
		if(SP(stmtCASE)->stt == STT_CASE) {
			if(TERMs_isASIS(stmtCASE, 0)) {
				TERMs_asmBLOCK(ctx, stmtCASE, 1, abr);
			}
			else {
				knh_labelid_t lbend = knh_Asm_newLabelId(ctx, abr, NULL);
				TERMs_ASM_JIFF(ctx, stmtCASE, 0, abr, lbend);
				TERMs_asmBLOCK(ctx, stmtCASE, 1, abr);
				KNH_ASM_LLABEL(ctx, abr, lbend);
			}
		}
		stmtCASE = DP(stmtCASE)->next;
	}
	KNH_ASM_GLABEL(ctx, abr, lbbreak);
	knh_Asm_popLabelStack(ctx, abr);
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtCONTINUE_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	knh_labelid_t labelid = knh_Asm_stackLabelId(ctx, abr, stmt);
	if(labelid != -1) {
		KNH_ASM_JMP(ctx, abr, labelid);
	}
	else if(SP(stmt)->stt == STT_CONTINUE) {
		KNH_ASM_PANIC(ctx, abr, "unknown continue label");
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtBREAK_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	knh_labelid_t labelid = knh_Asm_stackLabelId(ctx, abr, stmt);
	if(labelid != -1) {
		KNH_ASM_JMP(ctx, abr, labelid + 1);
	}
	else if(SP(stmt)->stt == STT_BREAK) {
		KNH_ASM_PANIC(ctx, abr, "unknown break label");
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtWHILE_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	knh_labelid_t lbbegin = knh_Asm_pushLabelStack(ctx, abr, stmt);
	knh_labelid_t lbend = lbbegin + 1;
	KNH_ASM_GLABEL(ctx, abr, lbbegin);
	if(!TERMs_isTRUE(stmt, 0)) {
		TERMs_ASM_JIFF_LOOP(ctx, stmt, 0, abr, lbend);
	}
	TERMs_asmBLOCK(ctx, stmt, 1, abr);
	KNH_ASM_JMP(ctx, abr, lbbegin);
	KNH_ASM_GLABEL(ctx, abr, lbend);
	knh_Asm_popLabelStack(ctx, abr);
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtDO_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	knh_labelid_t lbbegin = knh_Asm_pushLabelStack(ctx, abr, stmt);
	knh_labelid_t lbend = lbbegin + 1;
	KNH_ASM_GLABEL(ctx, abr, lbbegin);
	TERMs_asmBLOCK(ctx, stmt, 0, abr);
	TERMs_ASM_JIFF_LOOP(ctx, stmt, 1, abr, lbend);
	KNH_ASM_JMP(ctx, abr, lbbegin);
	KNH_ASM_GLABEL(ctx, abr, lbend);
	knh_Asm_popLabelStack(ctx, abr);
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtFOR_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	knh_labelid_t lbbegin = knh_Asm_pushLabelStack(ctx, abr, stmt);
	knh_labelid_t lbend = lbbegin + 1;
	knh_labelid_t lbredo = knh_Asm_newLabelId(ctx, abr, NULL);

	/* i = 1 part */
	TERMs_asmBLOCK(ctx, stmt, 0, abr);

	KNH_ASM_JMP(ctx, abr, lbredo);

	/* i++ part */
	KNH_ASM_GLABEL(ctx, abr, lbbegin); /* CONTINUE */
	TERMs_asmBLOCK(ctx, stmt, 2, abr);

	/* i < 10 part */
	KNH_ASM_LLABEL(ctx, abr, lbredo);
	if(!TERMs_isTRUE(stmt, 1)) {
		TERMs_ASM_JIFF_LOOP(ctx, stmt, 1, abr, lbend);
	}
	TERMs_asmBLOCK(ctx, stmt, FOR_loop, abr);
	KNH_ASM_JMP(ctx, abr, lbbegin);

	KNH_ASM_GLABEL(ctx, abr, lbend);
	knh_Asm_popLabelStack(ctx, abr);
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtSEPARATOR_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	Stmt *stmtDECL = DP(stmt)->stmts[0];
	Token *tkIT = knh_Stmt_get_IT(ctx, stmt, abr, 0);
	TERMs_asm(ctx, stmt, FOREACH_iter, abr, DP(tkIT)->type, DP(tkIT)->index);
	while(IS_NOTNULL(stmtDECL)) {
		if(STT_(stmtDECL) == STT_LET) {
			knh_StmtLET_asm(ctx, stmtDECL, abr, TYPE_void, 0);
		}
		stmtDECL = DP(stmt)->next;
	}
}

/* ------------------------------------------------------------------------ */

static
int knh_Stmt_isSEPARATOR(Stmt *stmt)
{
	return (IS_Stmt(DP(stmt)->next) && STT_(DP(stmt)->next) == STT_LET);
}

static
void knh_StmtFOREACH_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	knh_labelid_t lbbegin = knh_Asm_pushLabelStack(ctx, abr, stmt);
	knh_labelid_t lbend = lbbegin + 1;

	Stmt *stmtDECL = DP(stmt)->stmts[0];
	Token *tkITR = knh_Stmt_get_IT(ctx, stmt, abr, 0);
	Token *tkN = NULL;
	if(knh_Stmt_isSEPARATOR(stmtDECL)) {
		tkN = knh_Stmt_get_IT(ctx, stmt, abr, 1);
	}
	else {
		tkN = DP(stmtDECL)->tokens[1];
	}

	TERMs_asm(ctx, stmt, FOREACH_iter, abr, NNTYPE_Iterator, DP(tkITR)->index);
	KNH_ASM_GLABEL(ctx, abr, lbbegin);
	//DBG2_P("**(%d)ntype=%s%s (%d)itrtype=%s%s **", DP(tkn)->index, TYPEQN(DP(tkn)->type), DP(tkitr)->index, TYPEQN(DP(tkitr)->type));
	if(knh_Stmt_isSEPARATOR(stmtDECL)) {
		KNH_ASM_NEXT_(ctx, abr, lbend, sfi_(DP(tkN)->index), sfi_(DP(tkITR)->index));
		while(IS_NOTNULL(stmtDECL)) {
			if(STT_(stmtDECL) == STT_LET) {
				knh_StmtLET_asm(ctx, stmtDECL, abr, TYPE_void, 0);
			}
			stmtDECL = DP(stmt)->next;
		}
	}
	else {
		knh_class_t reqc = CLASS_type(DP(tkN)->type);
		knh_class_t foundc = CLASS_type(DP(tkITR)->type);
		KNH_ASSERT_cid(foundc); foundc = ClassTable(foundc).p1;
		if(reqc == foundc || reqc == CLASS_Any || knh_class_instanceof(ctx, reqc, foundc)) {
			KNH_ASM_NEXT_(ctx, abr, lbend, sfi_(DP(tkN)->index), sfi_(DP(tkITR)->index));
		}
		else if(!knh_Stmt_isMAPNEXT(stmt)) {
			KNH_ASM_INEXT_(ctx, abr, lbend, reqc, sfi_(DP(tkN)->index), sfi_(DP(tkITR)->index));
		}
		else {
			Mapper *mpr = knh_Class_getMapper(ctx, foundc, reqc);
			if(IS_NOTNULL(mpr) && knh_Mapper_isFinal(mpr)) {
				KNH_ASM_SMAPNEXT_(ctx, abr, lbend, sfi_(DP(tkN)->index), sfi_(DP(tkITR)->index), UP(mpr));
			}
			else {
				KNH_ASM_MAPNEXT_(ctx, abr, lbend, reqc, sfi_(DP(tkN)->index), sfi_(DP(tkITR)->index));
			}
		}
	}
	if(!TERMs_isTRUE(stmt, FOREACH_where)) {
		TERMs_ASM_JIFF(ctx, stmt, FOREACH_where, abr, lbbegin);
	}
	TERMs_asmBLOCK(ctx, stmt, FOREACH_loop, abr);
	KNH_ASM_JMP(ctx, abr, lbbegin);
	/* end */
	KNH_ASM_GLABEL(ctx, abr, lbend);
	knh_Asm_popLabelStack(ctx, abr);
}

/* ======================================================================== */
/* [TRY] */


static int knh_Asm_inTry(Asm *abr)
{
	return IS_Stmt(DP(abr)->finallyStmt);
}

/* ------------------------------------------------------------------------ */

static
void knh_Asm_setFinallyStmt(Ctx *ctx, Asm *abr, Stmt *stmt)
{
	if(IS_NOTNULL(stmt)) {
		if(IS_NOTNULL(DP(abr)->finallyStmt)) {
			knh_Asm_perror(ctx, abr, KERR_ERROR, _("cannot use nested try statements"));
			return;
		}
		KNH_SETv(ctx, DP(abr)->finallyStmt, stmt);
	}
	else { /* stmt == null */
		KNH_SETv(ctx, DP(abr)->finallyStmt, stmt);
	}
}

/* ------------------------------------------------------------------------ */

static
void KNH_ASM_FINALLY(Ctx *ctx, Asm *abr)
{
	if(IS_NOTNULL(DP(abr)->finallyStmt)) {
		DBG2_P("adding finally {} ..");
		knh_Stmt_asmBLOCK(ctx, DP(abr)->finallyStmt, abr, 1/* Iteration */);
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtTRY_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	knh_labelid_t lbcatch   = knh_Asm_newLabelId(ctx, abr, NULL);
	knh_labelid_t lbfinally = knh_Asm_newLabelId(ctx, abr, NULL);
	Token *tkIT = knh_Stmt_get_IT(ctx, stmt, abr, 0);

	knh_Asm_setFinallyStmt(ctx, abr, StmtTRY_finally(stmt));

	/* try { */
	KNH_ASM_TRY_(ctx, abr, lbcatch, sfi_(DP(tkIT)->index));
	TERMs_asmBLOCK(ctx, stmt, TRY_try, abr);
	KNH_ASM_TRYEND_(ctx, abr, sfi_(DP(tkIT)->index));
	KNH_ASM_JMP(ctx, abr, lbfinally);
	knh_Asm_setFinallyStmt(ctx, abr, (Stmt*)KNH_NULL); // InTry

	/* catch */
	KNH_ASM_GLABEL(ctx, abr, lbcatch);
	Stmt *stmtCATCH = DP(stmt)->stmts[TRY_catch];
	KNH_ASSERT(IS_Stmt(stmtCATCH));
	while(IS_Stmt(stmtCATCH)) {
		if(SP(stmtCATCH)->stt == STT_CATCH) {
			Object *emsg = DP(DP(stmtCATCH)->tokens[0])->data;
			KNH_ASSERT(IS_String(emsg));
			Token *tkn = DP(stmtCATCH)->tokens[1];
			KNH_ASSERT(TT_(tkn) == TT_LOCAL);
			lbcatch = knh_Asm_newLabelId(ctx, abr, NULL);
			KNH_ASM_CATCH_(ctx, abr, lbcatch, sfi_(DP(tkIT)->index), sfi_(DP(tkn)->index), emsg);
			TERMs_asmBLOCK(ctx, stmtCATCH, 2, abr);
			KNH_ASM_JMP(ctx, abr, lbfinally);  /* GOTO FINALLY */
			KNH_ASM_GLABEL(ctx, abr, lbcatch); /* _CATCH_NEXT_ */
		}
		stmtCATCH = DP(stmtCATCH)->next;
	}
	KNH_ASM_GLABEL(ctx, abr, lbfinally); /* FINALLY */
	TERMs_asmBLOCK(ctx, stmt, TRY_finally, abr);
	KNH_ASM_THROW_AGAIN_(ctx, abr, sfi_(DP(tkIT)->index));
	KNH_ASM_MOVo_(ctx, abr, sfi_(DP(tkIT)->index), KNH_NULL);
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtTHROW_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	//KNH_ASM_HOOKED_FINALLY(ctx, abr);
	TERMs_ASM_THROW(ctx, stmt, 0, abr);
}


/* ------------------------------------------------------------------------ */

static
void knh_StmtRETURN_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	KNH_ASM_FINALLY(ctx, abr);
	if(DP(stmt)->size > 0) {
		knh_type_t rtype = TERMs_gettype(stmt, 0);
		if(rtype == TYPE_void) {
			// @see(konohac.c new Eval)
			TERMs_asm(ctx, stmt, 0, abr, DP(abr)->rtype, DP(abr)->stack);
			knh_Stmt_setVOID(stmt, 1);
		}
		else {
			TERMs_asm(ctx, stmt, 0, abr, DP(abr)->rtype, -1);
		}
	}
	KNH_ASM_RET(ctx, abr);
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtERR_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	if(!IS_bString(DP(stmt)->errMsg)) {
		char buf[512];
		knh_snprintf(buf, sizeof(buf), "Script!!: you'll fix bugs at %s:%d", FILEN(SP(stmt)->uri), SP(stmt)->line);
		KNH_SETv(ctx, DP(stmt)->errMsg, new_String(ctx, B(buf), NULL));
		KNH_SETv(ctx, DP(stmt)->next, KNH_NULL);
	}
	KNH_ASM_THROWs_(ctx, abr, knh_Asm_inTry(abr), (Object*)DP(stmt)->errMsg);
}

/* ======================================================================== */
/* [PRINT] */

static int knh_Asm_isDEBUG(Ctx *ctx, Asm *abr)
{
	if(knh_Method_isRelease(DP(abr)->mtd)) return 0;
	return knh_Context_isDebug(ctx);
}

/* ------------------------------------------------------------------------ */

static
knh_methodn_t knh_Stmt_getMT(Ctx *ctx, Stmt *stmt, size_t n)
{
	knh_methodn_t mn = METHODN__k;
	Stmt *o = DP(stmt)->stmts[n];
	if(IS_Stmt(o) && SP(o)->stt == STT_MT) {
		KNH_ASSERT(DP(o)->size > 1);
		mn = DP(DP(o)->tokens[0])->mn;
		KNH_SETv(ctx, DP(stmt)->terms[n], DP(o)->terms[1]);
	}
	return mn;
}

/* ------------------------------------------------------------------------ */

void knh_StmtPRINT_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	if(!knh_Asm_isDEBUG(ctx, abr) || DP(stmt)->size == 0) {
		return ;
	}
	knh_flag_t flag = knh_StmtPRINT_flag(ctx, stmt);
	knh_labelid_t lbskip = knh_Asm_newLabelId(ctx, abr, NULL);
	KNH_ASM_SKIP_(ctx, abr, lbskip);
	if(konoha_debugLevel() > 1) {
		char buf[128];
		knh_snprintf(buf, sizeof(buf), "[%s:%d]", FILEN(DP(abr)->uri), DP(abr)->line);
		KNH_ASM_PMSG_(ctx, abr, flag | KNH_FLAG_PF_BOL, UP(new_String(ctx, B(buf), NULL)));
	}
	else if(flag != 0 ) {
		KNH_ASM_PMSG_(ctx, abr, flag | KNH_FLAG_PF_BOL, UP(TS_EMPTY));
	}
	int i;
	for(i = 0; i < DP(stmt)->size; i++) {
		L_REDO:;
		knh_flag_t mask = 0;
		if(i == DP(stmt)->size - 1) {
			mask |= KNH_FLAG_PF_EOL;
		}
		/* name= */ {
			Token *tkn = DP(stmt)->tokens[i];
			if(IS_Token(tkn) && knh_Token_isPNAME(tkn)) {
				KNH_ASM_PMSG_(ctx, abr, flag | mask | KNH_FLAG_PF_NAME, DP(tkn)->data);
				i++;
				KNH_ASSERT(i < DP(stmt)->size);
				goto L_REDO;
			}
		}
		/* "literal"*/ {
			Token *tkn = DP(stmt)->tokens[i];
			if(IS_Token(tkn) && knh_Token_isCONST(tkn) && IS_String(DP(tkn)->data)) {
				KNH_ASM_PMSG_(ctx, abr, flag | mask, DP(tkn)->data);
				continue;
			}
		}
		TERMs_asm(ctx, stmt, i, abr, TYPE_Any, DP(abr)->stack);
		knh_methodn_t mn = knh_Stmt_getMT(ctx, stmt, i);
		KNH_ASM_P_(ctx, abr, flag | mask, mn, DP(abr)->stack);
	}
	KNH_ASM_LLABEL(ctx, abr, lbskip);
}

/* ------------------------------------------------------------------------ */

void knh_StmtASSERT_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	if(!knh_StmtMETA_is(ctx, stmt, STEXT("@Release"))) {
		if(!knh_Asm_isDEBUG(ctx, abr)) {
			return ;
		}
	}
	knh_labelid_t lbskip = knh_Asm_newLabelId(ctx, abr, NULL);
	if(!knh_StmtMETA_is(ctx, stmt, STEXT("@Release"))) {
		KNH_ASM_SKIP_(ctx, abr, lbskip);
	}

	/* if */
	TERMs_ASM_JIFT(ctx, stmt, 0, abr, lbskip);
	/*then*/
	TERMs_asmBLOCK(ctx, stmt, 1, abr);
	KNH_ASM_THROWs_(ctx, abr, knh_Asm_inTry(abr), UP(TS_AssertionException));
	KNH_ASM_LLABEL(ctx, abr, lbskip);
}

/* ------------------------------------------------------------------------ */

void knh_Stmt_asmBLOCK(Ctx *ctx, Stmt *stmt, Asm *abr, int isIteration)
{
	int stack = DP(abr)->stack;
	Stmt *cur = stmt;
	while(IS_Stmt(cur)) {
		DP(abr)->stack = stack + DP(cur)->used_stack;
		KNH_ASM_SETLINE(ctx, abr, SP(cur)->line);
		switch(SP(cur)->stt) {
		case STT_BLOCK:
			if(!knh_Stmt_isDEBUG(stmt)) {
				knh_Stmt_asmBLOCK(ctx, DP(stmt)->stmts[0], abr, 1); break;
			}
			else {
				if(knh_Asm_isDEBUG(ctx, abr)) {
					knh_Stmt_asmBLOCK(ctx, DP(stmt)->stmts[0], abr, 1); break;
				}
			}
		case STT_LET:
			knh_StmtLET_asm(ctx, cur, abr, TYPE_void, DP(abr)->stack); break;
		case STT_SEPARATOR:
			knh_StmtSEPARATOR_asm(ctx, cur, abr); break;
		case STT_REGISTER:
		{
			size_t i;
			for(i = 0; i < DP(cur)->size; i++) {
				if(IS_Stmt(DP(cur)->terms[i]) && SP(DP(cur)->stmts[i])->stt == STT_LET) {
					knh_StmtLET_asm(ctx, DP(cur)->stmts[i], abr, TYPE_void, DP(abr)->stack);
				}
			}
			break;
		}
		case STT_IF:
			knh_StmtIF_asm(ctx, cur, abr); break;
		case STT_SWITCH:
			knh_StmtSWITCH_asm(ctx, cur, abr); break;
		case STT_WHILE:
			knh_StmtWHILE_asm(ctx, cur, abr); break;
		case STT_DO:
			knh_StmtDO_asm(ctx, cur, abr); break;
		case STT_FOR:
			knh_StmtFOR_asm(ctx, cur, abr); break;
		case STT_FOREACH:
			knh_StmtFOREACH_asm(ctx, cur, abr); break;
		case STT_BREAK:
			knh_StmtBREAK_asm(ctx, cur, abr); break;
		case STT_CONTINUE:
			knh_StmtCONTINUE_asm(ctx, cur, abr); break;
		case STT_TRY:
			knh_StmtTRY_asm(ctx, cur, abr); break;
		case STT_THROW:
			knh_StmtTHROW_asm(ctx, cur, abr); break;
		case STT_RETURN:
			knh_StmtRETURN_asm(ctx, cur, abr); break;
		case STT_PRINT:
			knh_StmtPRINT_asm(ctx, cur, abr); break;
		case STT_ASSERT:
			knh_StmtASSERT_asm(ctx, cur, abr); break;
		case STT_ERR:
			knh_StmtERR_asm(ctx, cur, abr); break;

		case STT_CALL1:
		case STT_DONE:
			break;
		default:
			if(knh_stmt_isExpr(SP(cur)->stt)) {
				knh_StmtEXPR_asm(ctx, cur, abr, TYPE_void, DP(abr)->stack);
			}
			else {
				KNH_ASM_PANIC(ctx, abr, "stt=%s", knh_stmt_tochar(SP(cur)->stt));
			}
		}
		//knh_Stmt_done(ctx, cur);
		if(!isIteration) break;
		cur = DP(cur)->next;
	}
	DP(abr)->stack = stack;
}

/* ------------------------------------------------------------------------ */

static
void KNH_ASM_INITLOCAL(Ctx *ctx, Asm *abr)
{
	Method *mtd = DP(abr)->mtd;
	DP(abr)->stack = DP(abr)->gamma_size;
	KNH_ASM_INITCODE_(ctx, abr, sfi_(DP(abr)->stack));
	DP(abr)->nnrtti0 = 0;
	DP(abr)->nnrtti = 0;
	KNH_ASSERT(IS_Method(mtd));

	size_t i = 1;
	for(;i < knh_Method_psize(mtd) + 1; i++) {
		knh_type_t ztype = knh_Method_pztype(mtd, i - 1);
		knh_type_t ptype = DP(abr)->gamma[i].type;
		DBG2_ASSERT(CLASS_type(ztype) == CLASS_type(ptype));
		DBG2_P("PARAM TYPE %s%s %s", TYPEQN(ptype), FIELDN(DP(abr)->gamma[i].fn));
		if(IS_NATYPE(ptype)) {
			Object *value = DP(abr)->gamma[i].value;
			if(value == NULL) {
				KNH_ASM_PINIDEF_(ctx, abr, sfi_(i), CLASS_type(ptype));
			}
			else {
				KNH_ASM_PINIo_(ctx, abr, sfi_(i), value);
			}
		}
	}

	if(DP(abr)->gamma[i].fn == FIELDN_vargs) {
		knh_class_t cid = ClassTable(CLASS_type(DP(abr)->gamma[i].type)).p1;
		KNH_ASSERT_cid(cid);
		KNH_ASM_PARAMS_(ctx, abr, i, cid); i++;
	}

	for(; i < DP(abr)->gamma_size; i++) {
		knh_type_t ptype = DP(abr)->gamma[i].type;
		DBG2_P("LOCAL VARIABLE %s%s %s", TYPEQN(ptype), FIELDN(DP(abr)->gamma[i].fn));
		if(ptype == TYPE_void) continue;
		if(IS_NNTYPE(ptype)) {
			if(DP(abr)->gamma[i].value == NULL) {
				KNH_ASM_MOVDEF_(ctx, abr, sfi_(i), CLASS_type(ptype));
			}
			else {
				KNH_ASM_MOVo_(ctx, abr, sfi_(i), DP(abr)->gamma[i].value);
			}
		}
		else {
			if(DP(abr)->gamma[i].value == NULL) {
				KNH_ASM_MOVo_(ctx, abr, sfi_(i), KNH_NULL);
			}
			else {
				KNH_ASM_MOVo_(ctx, abr, sfi_(i), DP(abr)->gamma[i].value);
				if(IS_NOTNULL(DP(abr)->gamma[i].value)) {
					knh_rtti_nullChecked(abr, (int)i);
				}
			}
		}
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_METHOD(Ctx *ctx, Asm *abr, Method *mtd, Stmt *params, Stmt *body, int isIteration)
{
	knh_class_t prev_cid = DP(abr)->this_cid;
	knh_StmtMETHOD_typingBODY(ctx, abr, DP(abr)->ns, mtd, params, body, isIteration);

	DP(abr)->line = 0;
	KNH_ASM_SETLINE(ctx, abr, SP(body)->line);
	KNH_ASM_INITLOCAL(ctx, abr);

	DP(abr)->level = 1;
	knh_Stmt_asmBLOCK(ctx, body, abr, isIteration);
	if(params == NULL) {
		KNH_ASM_RET(ctx, abr);
	}

	knh_Asm_finish(ctx, abr);
	DP(mtd)->sline = SP(body)->line;
	DP(abr)->this_cid = prev_cid;
}

/* ------------------------------------------------------------------------ */

void knh_StmtMETHOD_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	if(DP(stmt)->size == 4) return;
	Method *mtd = DP(StmtMETHOD_method(stmt))->mtd;
	KNH_ASM_METHOD(ctx, abr, mtd, DP(stmt)->stmts[3], StmtMETHOD_instmt(stmt), 1 /*Iteration */);
	knh_invokeMethodCompilationListener(ctx, DP(stmt)->metaDictMap, mtd);
}

/* ------------------------------------------------------------------------ */

void knh_StmtFORMAT_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	TODO();
}

/* ------------------------------------------------------------------------ */

void knh_StmtCLASS_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	knh_class_t prev_cid = DP(abr)->this_cid;
	knh_class_t this_cid = DP(StmtCLASS_class(stmt))->cid;
	DP(abr)->this_cid = this_cid;

	Stmt *instmt = StmtCLASS_instmt(stmt);
	while(IS_Stmt(instmt)) {
		if(SP(instmt)->stt == STT_METHOD) {
			DP(abr)->line = SP(instmt)->line;
			knh_StmtMETHOD_asm(ctx, instmt, abr);
		}
		else if(SP(instmt)->stt == STT_FORMAT) {
			DP(abr)->line = SP(instmt)->line;
			knh_StmtFORMAT_asm(ctx, instmt, abr);
		}
		instmt = DP(instmt)->next;
	}
	DP(abr)->this_cid = prev_cid;
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
