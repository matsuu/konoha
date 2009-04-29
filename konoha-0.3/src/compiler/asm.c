/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2005-2008, Kimio Kuramitsu <kimio at ynu.ac.jp>
 *           (c) 2008-      Konoha Software Foundation
 * All rights reserved.
 *
 * You may choose one of the following two licenses when you use konoha.
 * See www.konohaware.org/license.html for further information.
 *
 * (1) GNU General Public License 2.0      (with    KONOHA_UNDER_GPL2)
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
#include<konoha/gen/konohac_klr_.h>

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

void knh_code_traverse(Ctx *ctx, knh_code_t *pc, knh_ftraverse ftr);
void knh_Asm_writeAddress(Ctx *ctx, Asm *o, knh_code_t *pc_start);

/* ======================================================================== */
/* [structs] */

#define KNH_ASM_ASSERT(ctx,abr,c) KNH_ASSERT(c)

static knh_labelid_t knh_Asm_newLabelId(Ctx *ctx, Asm *abr, Token *tk);

#define KNH_ASM_PANIC(ctx, abr, fmt, ...) {\
		knh_Asm_setCancelled(abr, 1);\
		fprintf(stderr, "PANIC[%s:%d/%s]: ", KNH_SAFEFILE(__FILE__), __LINE__, __FUNCTION__); \
		fprintf(stderr, fmt, ## __VA_ARGS__); \
		fprintf(stderr, "\n"); \
	}\

static
void TERMs_asm(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, knh_type_t reqt, int sfpidx);

/* ======================================================================== */
/* [structs] */


/* ======================================================================== */
/* [constructor] */

static Asm *new_Asm(Ctx *ctx)
{
	return (Asm*)new_Object_bcid(ctx, CLASS_Asm, 0);
}

/* ======================================================================== */
/* [Asm] */

Asm* knh_Context_getAsm(Ctx *ctx)
{
	if(IS_NULL(ctx->cmpr)) {
		KNH_SETv(ctx, ((Context*)ctx)->cmpr, new_Asm(ctx));
	}
	return ctx->cmpr;
}

/* ======================================================================== */
/* [namespace] */

NameSpace *knh_Context_getNameSpace(Ctx *ctx)
{
	return DP(knh_Context_getAsm(ctx))->ns;
}

/* ------------------------------------------------------------------------ */

NameSpace *knh_Context_setNameSpace(Ctx *ctx, String *nsname)
{
	Asm *abr = knh_Context_getAsm(ctx);
	if(IS_NULL(nsname)) {
		if(IS_NameSpace(DP(abr)->ns)) {
			KNH_SETv(ctx, DP(abr)->ns, knh_System_getNameSpace(ctx, knh_String_tobytes(TS_main)));
		}
	}
	else {
		KNH_SETv(ctx, DP(abr)->ns, knh_System_getNameSpace(ctx, knh_String_tobytes(nsname)));
	}
	return DP(abr)->ns;
}

/* ------------------------------------------------------------------------ */

NameSpace *knh_Context_switchNameSpace(Ctx *ctx, NameSpace *newns)
{
	Asm *abr = knh_Context_getAsm(ctx);
	KNH_ASSERT(IS_NameSpace(DP(abr)->ns));
	NameSpace *oldns = DP(abr)->ns;
	KNH_SETv(ctx, DP(abr)->ns, newns);
	return oldns;
}

/* ------------------------------------------------------------------------ */

Script *knh_Asm_getScript(Ctx *ctx, Asm *o)
{
	return knh_NameSpace_getScript(ctx, DP(o)->ns);
}

/* ======================================================================== */
/* [compile method] */

static
void knh_Asm_prepare(Ctx *ctx, Asm *abr, Method *mtd, Stmt *stmt)
{
	DP(abr)->flag = 0;
	KNH_SETv(ctx, DP(abr)->mtd, mtd);
	DP(abr)->this_cid = DP(mtd)->cid;
	DP(abr)->rtype = knh_pmztype_totype(ctx, knh_Method_rztype(DP(abr)->mtd), DP(abr)->this_cid);
	DP(abr)->level = 0;

	size_t i;
	DP(abr)->vars_size = 0;
	for(i = 0; i < KONOHA_LOCALSIZE; i++) {
		DP(abr)->vars[i].flag  = 0;
		DP(abr)->vars[i].type  = TYPE_Any;
		DP(abr)->vars[i].fn    = FIELDN_NONAME;
//		DP(abr)->vars[i].count = 0;
		KNH_SETv(ctx, DP(abr)->vars[i].value, KNH_NULL);
	}
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

	DP(abr)->fileid  = SP(stmt)->fileid;
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
	DP(abr)->vars[0].flag = 0;
	DP(abr)->vars[0].type = NNTYPE_cid(cid);
	DP(abr)->vars[0].fn   = FIELDN_this;
	KNH_SETv(ctx, DP(abr)->vars[0].value, KNH_NULL);
	DP(abr)->vars_size = 1;
}

/* ------------------------------------------------------------------------ */

void knh_Asm_initThisScript(Ctx *ctx, Asm *abr)
{
	knh_Asm_initThis(ctx, abr, knh_Object_cid(knh_Asm_getScript(ctx, abr)));
}

/* ------------------------------------------------------------------------ */

static
void knh_Asm_gc(Ctx *ctx, Asm *abr)
{
	size_t i;
	KNH_SETv(ctx, DP(abr)->mtd, KNH_NULL);
	for(i = 0; i < KONOHA_LOCALSIZE; i++) {

		KNH_SETv(ctx, DP(abr)->vars[i].value, KNH_NULL);
	}
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

	KLRCode *vmc = new_KLRCode(ctx, DP(abr)->fileid,
			knh_Bytes_tobytes(DP(abr)->elf), knh_Bytes_tobytes(DP(abr)->dwarf));
	knh_Method_setKLRCode(ctx, mtd, vmc);
	knh_Asm_writeAddress(ctx, abr, DP(vmc)->code);

	if(knh_Asm_isCancelled(abr)) {
		if(DP(mtd)->mn != METHODN_lambda) {
			knh_Asm_perrorMTD(ctx, abr, KMSG_TOABSTRACT, DP(mtd)->cid, DP(mtd)->mn);
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
	if(0 <= n && n < (sizeof(knh_rtti_t) * 8)) {
		DP(abr)->nnrtti = DP(abr)->nnrtti | RuntimeNullCheck[n];
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_rtti_nullable(Asm *abr, size_t n)
{
	if(0 <= n && n < (sizeof(knh_rtti_t) * 8)) {
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

/* ------------------------------------------------------------------------ */

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

/* ------------------------------------------------------------------------ */

#define sfi_(n)    ((knh_sfi_t)(n))

#define IS_BOOL(t)  (t == NNTYPE_Boolean)

#define IS_INT(t)  (t == NNTYPE_Int || t == TYPE_Int)
#define IS_NNINT(t)  (t == NNTYPE_Int)
#define IS_NAINT(t)  (t == TYPE_Int)

#define IS_FLOAT(t)  (t == NNTYPE_Float || t == TYPE_Float)
#define IS_NNFLOAT(t)  (t == NNTYPE_Float)
#define IS_NAFLOAT(t)  (t == TYPE_Float)

#define IS_VAL(t) (IS_BOOL(t)||IS_INT(t)||IS_FLOAT(t))
#define IS_NNVAL(t) (IS_BOOL(t)||IS_NNINT(t)||IS_NNFLOAT(t))
#define IS_ANY(t) (CLASS_type(t) == CLASS_Any || CLASS_type(t) == CLASS_Object)

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */

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
	knh_class_t bcid = ctx->share->ClassTable[cid].bcid;
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
	knh_class_t bcid = ctx->share->ClassTable[cid].bcid;
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
	if(btype == NNTYPE_Int) {
		KNH_ASM_MOVxi_(ctx, abr, sfi_(a), bx);
		if(!IS_NNTYPE(atype)) {
			KNH_ASM_NNBOX_(ctx, abr, sfi_(a), CLASS_type(btype));
		}
		return;
	}
	if(btype == NNTYPE_Float) {
		KNH_ASM_MOVxf_(ctx, abr, sfi_(a), bx);
		if(!IS_NNTYPE(atype)) {
			KNH_ASM_NNBOX_(ctx, abr, sfi_(a), CLASS_type(btype));
		}
		return;
	}
	if(btype == NNTYPE_Boolean) {
		KNH_ASM_MOVxb_(ctx, abr, sfi_(a), bx);
		if(!IS_NNTYPE(atype)) {
			KNH_ASM_NNBOX_(ctx, abr, sfi_(a), CLASS_type(btype));
		}
		return;
	}
#endif
	if(IS_NNTYPE(atype) && !IS_NNTYPE(btype)) {
		KNH_ASM_ISNULLx_(ctx, abr, bx);
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

	switch(SP(tkb)->tt) {
		case TT_CLASSID:
		case TT_CONST: {
			Object *v = DP(tkb)->data;
			KNH_ASM_MOVo_(ctx, abr, sfi_(a), v);
			knh_rtti_sync(abr, a);
			break;
		}
		case TT_STACK: {
			int b = (int)DP(tkb)->index;
			knh_type_t btype = knh_rtti_type(abr, DP(tkb)->type, b);
			if(IS_NNTYPE(atype) && !IS_NNTYPE(btype)) {
				KNH_ASM_ISNULL_(ctx, abr, b);
				knh_rtti_nullChecked(abr, b);
				btype = NNTYPE_cid(btype);
			}
			if(IS_BOOL(btype) || IS_NNINT(btype) || IS_NNFLOAT(btype)) {
				KNH_ASM_MOVn_(ctx, abr, sfi_(a), sfi_(b));
				if(IS_ANY(atype)) {
					KNH_ASM_NNBOX(ctx, abr, btype, a);
				}
			}
			else if(IS_NAINT(btype) || IS_NAFLOAT(btype)) {
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

		case TT_GLOBAL: {
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

		default: {
			DBG2_P("unknown TT=%s", knh_token_tochar(SP(tkb)->tt));
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
		KNH_ASM_ISNULLx_(ctx, abr, bx);
	}
	if(atype == NNTYPE_Int) {
		if(btype == NNTYPE_Int) {
			KNH_ASM_XMOVxi_(ctx, abr, ax, bx);
		}
		else {
			KNH_ASM_XMOVxio_(ctx, abr, ax, bx);
		}
		return;
	}
	if(atype == NNTYPE_Float) {
		if(btype == NNTYPE_Float) {
			KNH_ASM_XMOVxf_(ctx, abr, ax, bx);
		}
		else {
			KNH_ASM_XMOVxfo_(ctx, abr, ax, bx);
		}
		return;
	}
	if(atype == NNTYPE_Boolean && btype == NNTYPE_Boolean) {
		KNH_ASM_XMOVxb_(ctx, abr, ax, bx);
		return;
	}
	if(atype == TYPE_Int && btype == NNTYPE_Int) {
		KNH_ASM_XMOVxBXi_(ctx, abr, ax, bx, CLASS_type(btype));
		return;
	}
	if(atype == TYPE_Int && btype == NNTYPE_Int) {
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
	switch(SP(tkb)->tt) {
		case TT_CLASSID:
		case TT_CONST: {
			Object *v = DP(tkb)->data;
#ifdef KNH_USING_UNBOXFIELD
			if(atype == NNTYPE_Int) {
				KNH_ASM_XMOVoi_(ctx, abr, ax, v);
				break;
			}
			if(atype == NNTYPE_Float) {
				KNH_ASM_XMOVof_(ctx, abr, ax, v);
				break;
			}
			if(atype == NNTYPE_Boolean) {
				KNH_ASM_XMOVob_(ctx, abr, ax, v);
				break;
			}
#endif/*KNU_USING_UNBOXFIED*/
			KNH_ASM_XMOVo_(ctx, abr, ax, v);
			break;
		}

		case TT_STACK: {
			int b = (int)DP(tkb)->index;
			if(IS_NNTYPE(atype) && !IS_NNTYPE(btype)) {
				KNH_ASM_ISNULL_(ctx, abr, b);
				knh_rtti_nullChecked(abr, b);
			}
#ifdef KNH_USING_UNBOXFIELD
			if(atype == NNTYPE_Int) {
				KNH_ASM_XMOVsi_(ctx, abr, ax, sfi_(b));
				break;
			}
			if(atype == NNTYPE_Float) {
				KNH_ASM_XMOVsf_(ctx, abr, ax, sfi_(b));
				break;
			}
			if(atype == NNTYPE_Boolean) {
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

		case TT_GLOBAL: {
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
			if(atype == NNTYPE_Int) {
				KNH_ASM_XMOVoi_(ctx, abr, ax, UP(KNH_INT0));
				break;
			}
			if(atype == NNTYPE_Float) {
				KNH_ASM_XMOVof_(ctx, abr, ax, UP(KNH_FLOAT0));
				break;
			}
			if(atype == NNTYPE_Boolean) {
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

		case TT_NOP: {
			return;
		}

		default: {
			DBG2_P("unknown TT=%d", SP(tkb)->tt);
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

	if(SP(tka)->tt == TT_STACK) {
		KNH_ASM_SMOV(ctx, abr, atype, (int)DP(tka)->index, tkb);
	}
	else if(SP(tka)->tt == TT_FIELD) {
		int an = (int)DP(tka)->index;
		KNH_ASM_XMOV(ctx, abr, atype, 0, an, tkb);
	}
	else if(SP(tka)->tt == TT_GLOBAL) {
		int a = (int)DP(abr)->globalidx;
		KNH_ASM_ASSERT(ctx, abr, a != -1);
		int an = (int)DP(tka)->index;
		KNH_ASM_XMOV(ctx, abr, atype, a, an, tkb);
	}
	else if(SP(tka)->tt == TT_MEMBER) {
		int a = (int)DP(tka)->index;
		KNH_ASM_ASSERT(ctx, abr, IS_Int(DP(tka)->data));
		int an = (int)(DP(tka)->num)->n.ivalue;
		KNH_ASM_XMOV(ctx, abr, atype, a, an, tkb);
	}
	else if(SP(tka)->tt == TT_NOP) {

	}
	else {
		DBG2_P("unknown TT=%d", SP(tka)->tt);
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
		if(knh_Method_isFinal(mtd) || knh_Method_isConstructor(ctx, mtd)) {
			KNH_ASM_SCALL_(ctx, abr, sfpidx, args + 2, UP(mtd));
		}
		else {
			KNH_ASM_CALL_(ctx, abr, sfpidx, args + 2, DP(mtd)->mn);
		}
		rtype = knh_Method_rztype(mtd);
		if(IS_NNTYPE(reqt) && !IS_NNTYPE(rtype)) {
			KNH_ASM_ISNULL_(ctx, abr, sfpidx);
			knh_rtti_nullChecked(abr, sfpidx);
		}
	}
	else if(SP(tkb)->tt == TT_MN) {
		KNH_ASM_ACALL_(ctx, abr, sfpidx, args + 2, DP(tkb)->mn);
		if(IS_NNTYPE(reqt) && !IS_NNTYPE(rtype)) {
			KNH_ASM_ISNULL_(ctx, abr, sfpidx);
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
		KNH_ASM_ISNULL_(ctx, abr, sfpidx);
		knh_rtti_nullChecked(abr, sfpidx);
	}
}

/* ------------------------------------------------------------------------ */

static
void KNH_ASM_MAP(Ctx *ctx, Asm *abr, knh_type_t reqt, int sfpidx, Token *tkb, knh_type_t srct)
{
	KNH_ASSERT(IS_Token(tkb));
	KNH_ASSERT(sfpidx >= DP(abr)->stack);
	Mapper *mpr = (Mapper*)DP(tkb)->data;
	if(IS_Mapper(mpr)) {
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
				if(!knh_Mapper_isTotal(mpr)) srct = CLASS_type(srct);
			}
			else {
				KNH_ASM_MAPnc_(ctx, abr, sfpidx, DP(mpr)->tcid);
			}
		}
	}
	else {
		KNH_ASSERT(SP(tkb)->tt == TT_MPR);
		KNH_ASM_AMAP_(ctx, abr, sfpidx, DP(tkb)->cid);
		srct = CLASS_type(srct);
	}

	if(!IS_NNTYPE(srct) && knh_Token_isNotNullType(tkb)) {
		KNH_ASM_NNMAP_(ctx, abr, sfpidx, DP(tkb)->cid);
	}
	else if(IS_NNTYPE(reqt)) {
		KNH_ASM_ISNULL_(ctx, abr, sfpidx);
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
	if(IS_Token(tk) && SP(tk)->tt == TT_STACK /*TT_LOCAL ??*/) {
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
	if(IS_Token(tk) && SP(tk)->tt == TT_STACK /*TT_LOCAL ??*/) {
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
	if(IS_Token(tk) && SP(tk)->tt == TT_STACK /*TT_LOCAL ??*/) {
		KNH_ASM_bJIFF_(ctx, abr, label, sfi_(DP(tk)->index));
	}
	else {
		if(TERMs_isCALLISNUL(stmt, n)) {
			// o == null -> false  o == null;
			TERMs_ASM_JIFNUL(ctx, DP(stmt)->stmts[n], 1, abr, label);
			return;
		}
		else if(TERMs_isCALLISNN(stmt, n)) {
			TERMs_ASM_JIFNN(ctx, DP(stmt)->stmts[n], 1, abr, label);
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
	if(IS_Token(tk) && SP(tk)->tt == TT_STACK /*TT_LOCAL ??*/) {
		KNH_ASM_bJIFF_(ctx, abr, label, sfi_(DP(tk)->index));
	}
	else {
		if(TERMs_isCALLISNUL(stmt, n)) {
			// o == null -> false  o == null;
			TERMs_ASM_JIFNUL(ctx, DP(stmt)->stmts[n], 1, abr, label);
			return;
		}
		else if(TERMs_isCALLISNN(stmt, n)) {
			TERMs_ASM_JIFNN(ctx, DP(stmt)->stmts[n], 1, abr, label);
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
	if(IS_Token(tk) && SP(tk)->tt == TT_STACK /*TT_LOCAL ??*/) {
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
	if(IS_Token(tk) && SP(tk)->tt == TT_STACK /*TT_LOCAL ??*/) {
		KNH_ASM_THROW_(ctx, abr, sfi_(DP(tk)->index));
	}
	else {
		TERMs_asm(ctx, stmt, n, abr, NNTYPE_Exception, DP(abr)->stack);
		KNH_ASM_THROW_(ctx, abr, sfi_(DP(abr)->stack));
	}
}

/* ------------------------------------------------------------------------ */
/* [EXPR] */
/* ------------------------------------------------------------------------ */
/* @data */

#define ASML(abr, idx)   (idx < DP(abr)->stack) ? DP(abr)->stack : idx
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

/* ------------------------------------------------------------------------ */

static
knh_type_t knh_Method_reqtTERMs(Method *mtd, knh_class_t mtd_cid, Stmt *stmt, size_t n)
{
	if(!IS_Method(mtd)) {
		return TYPE_Any;  // boxing
	}
	if(n == 1) { // base
		return knh_Method_isNullBase(mtd) ? mtd_cid : NNTYPE_cid(mtd_cid);
	}
	else {
		knh_type_t ptype = knh_Method_pztype(mtd, n - 2);
		if(ptype == TYPE_Object || ptype == TYPE_Any1 || ptype == TYPE_Any2) {
			return TYPE_Any; // boxing
		}
		if(ptype == NNTYPE_Object || ptype == NNTYPE_Any1 || ptype == NNTYPE_Any2) {
			return NNTYPE_Any; // boxing
		}
		if(ptype == NNTYPE_This) return NNTYPE_cid(mtd_cid);
		if(ptype == TYPE_This) return mtd_cid;
		return ptype;
	}
}

/* ------------------------------------------------------------------------ */

static
int TERMs_putSTACK(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, knh_type_t reqt, int sfpidx)
{
	Token *tk = DP(stmt)->tokens[n];
	if(IS_Token(tk) && SP(tk)->tt == TT_STACK) {
		int a = DP(tk)->index;
		if(!IS_NNTYPE(knh_rtti_type(abr, DP(tk)->type, a))) {
			KNH_ASM_ISNULL_(ctx, abr, a);
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
	if(swap && IS_Token(tm) && SP((Token*)tm)->tt == TT_CONST) {
		DP(stmt)->terms[1] = DP(stmt)->terms[2];
		DP(stmt)->terms[2] = tm;
		if(*mn == METHODN_opLt) *mn = METHODN_opGte;
		else if(*mn == METHODN_opLte) *mn = METHODN_opGt;
		else if(*mn == METHODN_opGt) *mn = METHODN_opLte;
		else if(*mn == METHODN_opGte) *mn = METHODN_opLt;
	}
	Token *tk = DP(stmt)->tokens[2];
	return (IS_Token(tk) && SP(tk)->tt == TT_CONST);
}

/* ------------------------------------------------------------------------ */

static
knh_int_t TERMs_integer(Stmt *stmt, size_t n)
{
	Token *tk = DP(stmt)->tokens[n];
	KNH_ASSERT(SP(tk)->tt == TT_CONST);
	return (DP(tk)->num)->n.ivalue;
}

/* ------------------------------------------------------------------------ */

static
knh_float_t TERMs_float(Stmt *stmt, size_t n)
{
	Token *tk = DP(stmt)->tokens[n];
	KNH_ASSERT(SP(tk)->tt == TT_CONST);
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
				int a = TERMs_putSTACK(ctx, stmt, 1, abr, NNTYPE_Int, local + 1);
				knh_int_t b = TERMs_integer(stmt, 2);
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
				int a = TERMs_putSTACK(ctx, stmt, 1, abr, NNTYPE_Int, local + 1);
				int b = TERMs_putSTACK(ctx, stmt, 2, abr, NNTYPE_Int, local + 2);
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
				int a = TERMs_putSTACK(ctx, stmt, 1, abr, NNTYPE_Int, local + 1);
				knh_int_t b = TERMs_integer(stmt, 2);
				switch(mn) {
				case METHODN_opSub:
					KNH_ASM_iSUBn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opDiv:
					KNH_ASM_iDIVn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opMod:
					KNH_ASM_iMODn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				}
			}
			else {
				int a = TERMs_putSTACK(ctx, stmt, 1, abr, NNTYPE_Int, local + 1);
				int b = TERMs_putSTACK(ctx, stmt, 2, abr, NNTYPE_Int, local + 2);
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
				int a = TERMs_putSTACK(ctx, stmt, 1, abr, NNTYPE_Float, local + 1);
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
				int a = TERMs_putSTACK(ctx, stmt, 1, abr, NNTYPE_Float, local + 1);
				int b = TERMs_putSTACK(ctx, stmt, 2, abr, NNTYPE_Float, local + 2);
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
				int a = TERMs_putSTACK(ctx, stmt, 1, abr, NNTYPE_Float, local + 1);
				knh_float_t b = TERMs_float(stmt, 2);
				switch(mn) {
				case METHODN_opSub:
					KNH_ASM_fSUBn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				case METHODN_opDiv:
					KNH_ASM_fDIVn_(ctx, abr, sfi_(sfpidx), sfi_(a), b);
					return 1;
				}
			}
			else {
				int a = TERMs_putSTACK(ctx, stmt, 1, abr, NNTYPE_Float, local + 1);
				int b = TERMs_putSTACK(ctx, stmt, 2, abr, NNTYPE_Float, local + 2);
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
int TERMs_isSTACK(Stmt *stmt, size_t n)
{
	Token *tk = DP(stmt)->tokens[n];
	return (IS_Token(tk) && SP(tk)->tt == TT_STACK);
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
		KNH_ASM_AINVOKE_(ctx, abr, sfi_(local), (knh_ushort_t)DP(stmt)->size, UP(mtd));
		return;
	}
	/* PEEPHOLE */
	if(IS_Method(mtd) && knh_Method_isFinal(mtd) && TERMs_isSTACK(stmt, 1)) {
		int a = DP(DP(stmt)->tokens[1])->index;
		knh_type_t reqt2 = knh_Method_reqtTERMs(mtd, cid, stmt, 1);
		knh_type_t vart2 = knh_rtti_type(abr, TERMs_gettype(stmt, 1), a);
		if(IS_NNTYPE(reqt2) && !IS_NNTYPE(vart2)) {
			KNH_ASM_ISNULL_(ctx, abr, sfi_(a));
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
	if(IS_NNVAL(rtype)) {
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
	if(knh_Stmt_isNNCAST(stmt)) {
		KNH_ASM_NNMAP_(ctx, abr, local, DP(DP(stmt)->tokens[0])->cid);
	}
	else {
		KNH_ASM_MAP(ctx, abr, reqt, local, DP(stmt)->tokens[0], srct);
	}
	MOVL(ctx, abr, local, sfpidx);
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtMT_asm(Ctx *ctx, Stmt *stmt, Asm *abr, knh_type_t reqt, int sfpidx)
{
	int local = ASML(abr, sfpidx);
	TERMs_asm(ctx, stmt, 1, abr, TYPE_any, local);
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
	Token *ltk = DP(stmt)->tokens[0];
	if(SP(ltk)->tt == TT_STACK) {
		TERMs_asm(ctx, stmt, 1, abr, DP(ltk)->type, DP(ltk)->index);
		if(reqt != TYPE_void) {
			KNH_ASM_SMOV(ctx, abr, reqt, sfpidx, ltk);
		}
	}
	else if(IS_Token(DP(stmt)->tokens[1])) {
		KNH_ASM_MOV(ctx, abr, ltk, DP(stmt)->tokens[1]);
		if(reqt != TYPE_void) {
			KNH_ASM_SMOV(ctx, abr, reqt, sfpidx, ltk);
		}
	}
	else {
		int local = ASML(abr, sfpidx);
		knh_token_t tt = SP(ltk)->tt; /* NOTE: ltk is reused inside stmt */
		knh_short_t index = DP(ltk)->index;
		TERMs_asm(ctx, stmt, 1, abr, DP(ltk)->type, local);
		SP(ltk)->tt = tt;
		DP(ltk)->index = index;
		KNH_ASM_MOV(ctx, abr, ltk, DP(stmt)->tokens[1]);
		if(reqt != TYPE_void && local != sfpidx) {
			KNH_ASM_SMOV(ctx, abr, reqt, sfpidx, ltk);
		}
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_Token_toSTACK(Ctx *ctx, Token *tk, int sfpidx, knh_type_t type)
{
	SP(tk)->tt = TT_STACK;
	DP(tk)->index = (knh_short_t)sfpidx;
	DP(tk)->type = type;
}

/* ------------------------------------------------------------------------ */

static
Token *knh_Stmt_toSTACK(Ctx *ctx, Stmt *stmt, knh_type_t reqt, int sfpidx, int level)
{
//	DBG2_P("stt=%s, toSTACK=%d", knh_stmt_tochar(SP(stmt)->stt), sfpidx);
	size_t i;
	for(i = 0; i < DP(stmt)->size; i++) {
		if(IS_Token(DP(stmt)->tokens[i])) {
			knh_Token_toSTACK(ctx, DP(stmt)->tokens[i], sfpidx, reqt);
			return DP(stmt)->tokens[i];
		}
		else {
			Token *tk = knh_Stmt_toSTACK(ctx, DP(stmt)->stmts[i], sfpidx, reqt, 1);
			if(tk != NULL) return tk;
		}
	}
	if(level == 1) return NULL;
	Token *tk = new_TokenNULL(ctx, FL(stmt), reqt);
	knh_Token_toSTACK(ctx, tk, sfpidx, reqt);
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
}

/* ------------------------------------------------------------------------ */

static
void TERMs_asm(Ctx *ctx, Stmt *stmt, size_t n, Asm *abr, knh_type_t reqt, int sfpidx)
{
	if(IS_Token(DP(stmt)->tokens[n])) {
		Token *tk = DP(stmt)->tokens[n];
		KNH_ASM_SMOV(ctx, abr, reqt, sfpidx, tk);
		knh_Token_toSTACK(ctx, tk, sfpidx, reqt);
	}
	else {
		knh_StmtEXPR_asm(ctx, DP(stmt)->stmts[n], abr, reqt, sfpidx);
		KNH_SETv(ctx, DP(stmt)->tokens[n], knh_Stmt_toSTACK(ctx, DP(stmt)->stmts[n], reqt, sfpidx, 0));
	}
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

//static
//void knh_rtti_updateIFNOTNOLL(Stmt *stmt, size_t n)
//{
//	Stmt *call = DP(stmt)->stmts[n];
//	if(!IS_Stmt(call) || SP(call)->stt != STT_CALL) return;
//	int idx = TERMs_getlocalidx(call, 1);
//	if(idx == -1) return;
//	if(TERMs_getmn(call, 0) == METHODN_isNotNull) {
//		knh_rtti_nullChecked(rtti, (size_t)idx);
//	}
//}
//
///* ------------------------------------------------------------------------ */
//
//static
//void knh_rtti_updateIFNOTNOLL(knh_rtti_t *rtti, Stmt *stmt, size_t n)
//{
//	Stmt *call = DP(stmt)->stmts[n];
//	if(!IS_Stmt(call) || SP(call)->stt != STT_CALL) return;
//	int idx = TERMs_getlocalidx(call, 1);
//	if(idx == -1) return;
//	if(TERMs_getmn(call, 0) == METHODN_isNotNull) {
//		knh_rtti_nullChecked(*rtti, (size_t)idx);
//	}
//}

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
//	knh_rtti_t rtti_orig = knh_rtti_updateIFNOTNUDP(abr)->nnrtti;
//	knh_rtti_updateIFNOTNULL(&(DP(abr)->nnrtti), stmt, 0);
	TERMs_asmBLOCK(ctx, stmt, 1, abr);

	if(TERMs_isDONE(stmt, 2)) { /* PEEPHOLE */
		KNH_ASM_LLABEL(ctx, abr, lbelse);
		return;
	}

	KNH_ASM_JMP(ctx, abr, lbend);
	/* else */
	KNH_ASM_LLABEL(ctx, abr, lbelse);
//	knh_rtti_t rtti_true = DP(abr)->nnrtti;
//	DP(abr)->nnrtti = rtti_orig;
//	knh_rtti_updateIFNULL(&(DP(abr)->nnrtti), stmt, 0);
	TERMs_asmBLOCK(ctx, stmt, 2, abr);
	/* endif */
//	DP(abr)->nnrtti = DP(abr)->nnrtti & rtti_true;
	KNH_ASM_LLABEL(ctx, abr, lbend);
}

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */

static
Token *knh_StmtMETA_getLabel(Ctx *ctx, Stmt *o)
{
	if(IS_DictMap(DP(o)->metaDictMap)) {
		Token *tk = (Token*)knh_DictMap_get(ctx, DP(o)->metaDictMap, TS_ATlabel);
		KNH_ASSERT(IS_Token(tk));
		return tk;
	}
	return (Token*)KNH_NULL;
}

/* ------------------------------------------------------------------------ */

static
knh_labelid_t knh_Asm_pushLabelStack(Ctx *ctx, Asm *abr, Stmt *stmt)
{
	Token *ltk = knh_StmtMETA_getLabel(ctx, stmt);
	if(IS_NULL(ltk)) {
		char lbn[8];
		knh_snprintf(lbn, sizeof(lbn), "%d", DP(abr)->llstep);
		ltk = new_TokenCONST(ctx, FL(stmt), UP(new_String(ctx, B(lbn), NULL)));
		SP(ltk)->tt = TT_LABEL;
	}
	else {
		DEBUG3("label=%s", sToken(ltk));
	}
	DP(ltk)->index = (DP(abr)->llstep)++;
	knh_Array_add(ctx, DP(abr)->lstacks, UP(ltk));
	knh_labelid_t labelid = knh_Asm_newLabelId(ctx, abr, ltk);
	knh_labelid_t labelid2 = knh_Asm_newLabelId(ctx, abr, NULL);
	DBG2_P("label L1, L2 = %d, %d", labelid, labelid2);
	KNH_ASSERT(labelid + 1 == labelid2);
	return labelid;
}

/* ------------------------------------------------------------------------ */

static
knh_labelid_t knh_Asm_stackLabelId(Ctx *ctx, Asm *abr, Stmt *stmt)
{
	size_t s = knh_Array_size(DP(abr)->lstacks);
	if(s == 0) {
		if(SP(stmt)->stt == STT_CONTINUE)
			knh_Asm_perror(ctx, abr, KMSG_EABORT, "continue");
		else
			knh_Asm_perror(ctx, abr, KMSG_EABORT, "break");
		return -1;
	}
	Token *tk = NULL;
	if(DP(stmt)->size == 1) {
		tk = DP(stmt)->tokens[0];
	}
	if(tk != NULL) {
		int i;
		for(i = s - 1; i >= 0; i--) {
			Token *tk2 = (Token*)knh_Array_n(DP(abr)->lstacks, i);
			if(knh_String_equals(DP(tk)->text, knh_String_tobytes(DP(tk2)->text))) {
				tk = tk2;
			}
		}
		knh_Asm_perror(ctx, abr, KMSG_ULABEL, sToken(tk));
		tk = NULL;
	}
	if(tk == NULL) {
		tk = (Token*)knh_Array_n(DP(abr)->lstacks, s-1);
	}
	return knh_Asm_findLabelId(ctx, abr, tk);
}

/* ------------------------------------------------------------------------ */

static
void knh_Asm_popLabelStack(Ctx *ctx, Asm *abr)
{
	knh_Array_pop(ctx, DP(abr)->lstacks);
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtCONTINUE_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	knh_labelid_t labelid = knh_Asm_stackLabelId(ctx, abr, stmt);
	if(labelid != -1) {
		KNH_ASM_JMP(ctx, abr, labelid);
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtBREAK_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	knh_labelid_t labelid = knh_Asm_stackLabelId(ctx, abr, stmt);
	if(labelid != -1) {
		KNH_ASM_JMP(ctx, abr, labelid);
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
void knh_StmtFOREACH_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	knh_labelid_t lbbegin = knh_Asm_pushLabelStack(ctx, abr, stmt);
	knh_labelid_t lbend = lbbegin + 1;

	Token *tkn = DP(stmt)->tokens[FOREACH_name];
	KNH_ASSERT(SP(tkn)->tt == TT_STACK);
	Token *tkitr = DP(stmt)->tokens[FOREACH_loop + 1];
	KNH_ASSERT(SP(tkitr)->tt == TT_STACK);

	TERMs_asm(ctx, stmt, FOREACH_iter, abr, NNTYPE_Iterator, DP(tkitr)->index);
	KNH_ASM_GLABEL(ctx, abr, lbbegin);
	DBG2_P("**(%d)ntype=%s%s (%d)itrtype=%s%s **", DP(tkn)->index, TYPEQN(DP(tkn)->type), DP(tkitr)->index, TYPEQN(DP(tkitr)->type));
	knh_class_t ncid = CLASS_type(DP(tkn)->type);
	knh_class_t itrcid = CLASS_type(DP(tkitr)->type);
	KNH_ASSERT_cid(itrcid); itrcid = ctx->share->ClassTable[itrcid].p1;
	if(ncid == itrcid || ncid == CLASS_Any || knh_class_instanceof(ctx, ncid, itrcid)) {
		KNH_ASM_NEXT_(ctx, abr, lbend, sfi_(DP(tkn)->index), sfi_(DP(tkitr)->index), sfi_(DP(abr)->stack));
	}
	else if(!knh_Stmt_isMAPNEXT(stmt)) {
		KNH_ASM_INEXT_(ctx, abr, lbend, ncid, sfi_(DP(tkn)->index), sfi_(DP(tkitr)->index), sfi_(DP(abr)->stack));
	}
	else {
		Mapper *mpr = knh_Class_getMapper(ctx, itrcid, ncid);
		if(IS_NOTNULL(mpr) && knh_Mapper_isFinal(mpr)) {
			KNH_ASM_SMAPNEXT_(ctx, abr, lbend, sfi_(DP(tkn)->index), sfi_(DP(tkitr)->index), sfi_(DP(abr)->stack), UP(mpr));
		}
		else {
			KNH_ASM_MAPNEXT_(ctx, abr, lbend, ncid, sfi_(DP(tkn)->index), sfi_(DP(tkitr)->index), sfi_(DP(abr)->stack));
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

/* ------------------------------------------------------------------------ */

static
void knh_Asm_setFinallyStmt(Ctx *ctx, Asm *abr, Stmt *stmt)
{
	if(IS_NOTNULL(stmt)) {
		if(IS_NOTNULL(DP(abr)->finallyStmt)) {
			knh_Asm_perror(ctx, abr, KMSG_ETRY, NULL);
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

	Token *tkhdr = DP(stmt)->tokens[TRY_finally + 1];
	KNH_ASSERT(SP(tkhdr)->tt == TT_STACK);

	knh_Asm_setFinallyStmt(ctx, abr, StmtTRY_finally(stmt));

	/* try { */
	KNH_ASM_TRY_(ctx, abr, lbcatch, sfi_(DP(tkhdr)->index));
	TERMs_asmBLOCK(ctx, stmt, TRY_try, abr);
	KNH_ASM_TRYEND_(ctx, abr, sfi_(DP(tkhdr)->index));
	KNH_ASM_JMP(ctx, abr, lbfinally);

	/* catch */
	KNH_ASM_GLABEL(ctx, abr, lbcatch);
	Stmt *stmtcatch = DP(stmt)->stmts[TRY_catch];
	while(IS_Stmt(stmtcatch)) {
		if(SP(stmtcatch)->stt == STT_CATCH) {
			Object *emsg = DP(DP(stmtcatch)->tokens[0])->data;
			KNH_ASSERT(IS_String(emsg));
			Token *tkn = DP(stmtcatch)->tokens[1];
			KNH_ASSERT(SP(tkn)->tt == TT_STACK);
			lbcatch = knh_Asm_newLabelId(ctx, abr, NULL);
			KNH_ASM_CATCH_(ctx, abr, lbcatch, sfi_(DP(tkhdr)->index), sfi_(DP(tkn)->index), emsg);
			TERMs_asmBLOCK(ctx, stmtcatch, 2, abr);
			KNH_ASM_JMP(ctx, abr, lbfinally);  /* GOTO FINALLY */
			KNH_ASM_GLABEL(ctx, abr, lbcatch); /* _CATCH_NEXT_ */
		}
		stmtcatch = DP(stmtcatch)->next;
	}

	knh_Asm_setFinallyStmt(ctx, abr, (Stmt*)KNH_NULL);

	KNH_ASM_GLABEL(ctx, abr, lbfinally); /* FINALLY */
	TERMs_asmBLOCK(ctx, stmt, TRY_finally, abr);
	KNH_ASM_THROW_AGAIN_(ctx, abr, sfi_(DP(tkhdr)->index));
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
		knh_snprintf(buf, sizeof(buf), "Script!!: running errors at %s:%d", FILEIDN(SP(stmt)->fileid), SP(stmt)->line);
		KNH_SETv(ctx, DP(stmt)->errMsg, new_String(ctx, B(buf), NULL));
		KNH_SETv(ctx, DP(stmt)->next, KNH_NULL);
	}
	KNH_ASM_THROWs_(ctx, abr, (Object*)DP(stmt)->errMsg);
}

/* ======================================================================== */
/* [PRINT] */

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

static
String *knh_Term_getNameNULL(Term *tm)
{
	Token *tk = (Token*)tm;
	if(!IS_Token(tk)) {
		return NULL;
	}
	else if(SP(tk)->tt == TT_NAME) {
		DBG2_ASSERT(IS_String(DP(tk)->data));
		return (String*)DP(tk)->data;
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

void knh_StmtPRINT_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	knh_flag_t flag = knh_StmtPRINT_flag(ctx, stmt);
	if(DP(stmt)->size == 0) {
		Object *o = (Object*)TS_EMPTY;
		KNH_ASM_PMSG_(ctx, abr, flag | KNH_FLAG_PF_EOL, o);
	}
	else {
		int i;
		knh_flag_t mask = 0;
		for(i = 0; i < DP(stmt)->size; i++) {
			if(i == 0) {
				mask |= KNH_FLAG_PF_BOL;
			}
			if(i == DP(stmt)->size - 1) {
				mask |= KNH_FLAG_PF_EOL;
			}
			String *name = knh_Term_getNameNULL(DP(stmt)->terms[i]);
			if(name != NULL) {
				mask |= KNH_FLAG_PF_NAME;
				KNH_ASM_PMSG_(ctx, abr, flag, UP(name));
			}
			knh_methodn_t mn = knh_Stmt_getMT(ctx, stmt, i);
			TERMs_asm(ctx, stmt, i, abr, TYPE_Any, DP(abr)->stack);
			KNH_ASM_P_(ctx, abr, flag | mask, mn, DP(abr)->stack);
			mask = 0;
		}
	}
}


/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */

void knh_Stmt_asmBLOCK(Ctx *ctx, Stmt *stmt, Asm *abr, int isIteration)
{
	int level = DP(abr)->level ;
	Stmt *cur = stmt;
	while(IS_Stmt(cur)) {
		DP(abr)->level = level + 1;
		KNH_ASM_SETLINE(ctx, abr, SP(cur)->line);
		switch(SP(cur)->stt) {
		case STT_BLOCK:
			knh_Stmt_asmBLOCK(ctx, DP(stmt)->stmts[0], abr, 1); break;
		case STT_LET:
			knh_StmtLET_asm(ctx, cur, abr, TYPE_void, DP(abr)->stack); break;
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
			/*knh_StmtSWITCH_asm(ctx, cur, abr);*/ break;
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
	DP(abr)->level = level;
}

/* ------------------------------------------------------------------------ */

static
void KNH_ASM_INITLOCAL(Ctx *ctx, Asm *abr)
{
	Method *mtd = DP(abr)->mtd;
	DP(abr)->stack = DP(abr)->vars_size;
	KNH_ASM_INITCODE_(ctx, abr, sfi_(DP(abr)->stack));
	DP(abr)->nnrtti0 = 0;
	DP(abr)->nnrtti = 0;
	KNH_ASSERT(IS_Method(mtd));

	size_t i = 1;
	for(;i < knh_Method_psize(mtd) + 1; i++) {
		if(IS_NOTNULL(DP(abr)->vars[i].value)) {
			KNH_ASM_PINIo_(ctx, abr, sfi_(i), DP(abr)->vars[i].value);
		}
	}

//	if(DP(abr)->vars[i].fn == FIELDN_vargs) {
//		KNH_ASM_VARGS(ctx, abr, i); i++;
//	}

	for(; i < DP(abr)->vars_size; i++) {
		DBG2_P("LOCAL VARIABLE %s%s %s", TYPEQN(DP(abr)->vars[i].type), FIELDN(DP(abr)->vars[i].fn));
		if(DP(abr)->vars[i].type == TYPE_void) continue;
		if(IS_NNTYPE(DP(abr)->vars[i].type)) {
			if(IS_NULL(DP(abr)->vars[i].value)) {
				KNH_ASM_MOVDEF_(ctx, abr, sfi_(i), CLASS_type(DP(abr)->vars[i].type));
			}
			else {
				KNH_ASM_MOVo_(ctx, abr, sfi_(i), DP(abr)->vars[i].value);
			}
		}
		else {
			KNH_ASM_MOVo_(ctx, abr, sfi_(i), DP(abr)->vars[i].value);
			if(IS_NOTNULL(DP(abr)->vars[i].value)) {
				knh_rtti_nullChecked(abr, (int)i);
			}
		}
	}
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_METHOD(Ctx *ctx, Asm *abr, Method *mtd, Stmt *params, Stmt *body, int isIteration)
{
	knh_class_t prev_cid = DP(abr)->this_cid;
	NameSpace *ns = DP(abr)->ns;
	KNH_ASSERT(IS_Method(mtd));
	knh_Method_toAbstract(ctx, mtd);

	knh_Asm_prepare(ctx, abr, mtd, body);
	knh_Asm_initThis(ctx, abr, DP(abr)->this_cid);
	if(params != NULL) {
		if(!knh_Stmt_initParams(ctx, params, abr, ns, KNH_INNERPARAMS)) {
			return;
		}
	}

	DP(abr)->level = 1;
	if(!knh_Stmt_typingBLOCK(ctx, body, abr, ns, isIteration)) {
		return;
	}
	DP(abr)->line = 0;
	KNH_ASM_SETLINE(ctx, abr, SP(body)->line);
	KNH_ASM_INITLOCAL(ctx, abr);

	DP(abr)->level = 1;
	knh_Stmt_asmBLOCK(ctx, body, abr, isIteration);
	if(params == NULL) {
		KNH_ASM_RET(ctx, abr);
	}

	knh_Asm_finish(ctx, abr);
	DP(abr)->this_cid = prev_cid;
}

/* ------------------------------------------------------------------------ */

void knh_StmtMETHOD_asm(Ctx *ctx, Stmt *stmt, Asm *abr)
{
	if(DP(stmt)->size == 4) return;
	Method *mtd = DP(StmtMETHOD_method(stmt))->mtd;
	KNH_ASM_METHOD(ctx, abr, mtd, DP(stmt)->stmts[3], StmtMETHOD_instmt(stmt), 1 /*Iteration */);
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
