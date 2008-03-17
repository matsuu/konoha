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

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif
	
void knh_Object_vmcinc(Ctx *ctx, Object *self);

/* ======================================================================== */
/* [structs] */

void 
knh_Cmpl_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Cmpl *b = (Cmpl*)s;
	b->flag = 0;
	b->this_cid = CLASS_Object;

	b->vars = (knh_cfield_t*)knh_malloc(ctx, KONOHA_LOCALVAR_SIZE * sizeof(knh_cfield_t));
	b->vars_size = 0;
	b->vars_offset = 0;

	knh_int_t i;
	for(i = 0; i < KONOHA_LOCALVAR_SIZE; i++) {
		b->vars[i].flag  = 0;
		b->vars[i].type  = TYPE_any;
		b->vars[i].fn    = FIELDN_NONAME;
		KNH_INITv(b->vars[i].value, KNH_NULL);
	}
	
	b->nsn = 0;
	KNH_INITv(b->nsproto, new_Prototype(ctx, b->nsn));
	b->this_cid = knh_Object_cid(b->nsproto);
	
	KNH_INITv(b->method,   KNH_NULL);

	b->nastep = 0;
	KNH_INITv(b->elf, new_Bytes(ctx, 1024));
	KNH_INITv(b->dwarf, new_Bytes(ctx, 1024));
	KNH_INITv(b->labelIdDictIdx, new_DictIdx(ctx, 256, 1));
	KNH_INITv(b->labelAddrDictSet, new_DictSet(ctx, 256));
	KNH_INITv(b->lstacks, new_Array(ctx, 8));
//	KNH_INITv(b->stmt_label, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

#define _knh_Cmpl_struct_copy   NULL

/* ------------------------------------------------------------------------ */

#define _knh_Cmpl_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void knh_Cmpl_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Cmpl *b = (Cmpl*)s;
	
	knh_int_t i;
	for(i = 0; i < KONOHA_LOCALVAR_SIZE; i++) {
		gc(ctx, b->vars[i].value);
	}
	
	if(IS_SWEEP(gc)) {
		knh_free(b->vars, KONOHA_LOCALVAR_SIZE * sizeof(knh_cfield_t));
	}

	gc(ctx, b->nsproto);
	gc(ctx, b->method);
	gc(ctx, b->elf);
	gc(ctx, b->dwarf);
	gc(ctx, b->labelIdDictIdx);
	gc(ctx, b->labelAddrDictSet);
	gc(ctx, b->lstacks);
}

/* ======================================================================== */
/* [constructor] */

Cmpl *new_Cmpl(Ctx *ctx)
{
	Cmpl *b = knh_Object_malloc(ctx, CLASS_Cmpl);
	knh_Cmpl_struct_init(ctx, (Struct*)b, 0, NULL);
	return b;
}

/* ======================================================================== */
/* [Cmpl] */

Cmpl* knh_Context_getCompiler(Ctx *ctx, Context *b)
{
	if(IS_NULL(b->cmpl)) {
		KNH_SETv(ctx, b->cmpl, new_Cmpl(ctx));
	}
	return b->cmpl;
}

/* ======================================================================== */
/* [namespace] */

void knh_Cmpl_changeNameSpace(Ctx *ctx, Cmpl *b, knh_nsn_t nsn)
{
	if(b->nsn == nsn) return ;
	//DEBUG("b->nsn=%d,%s nsn=%d,%s", b->nsn, NSN(b->nsn), nsn, NSN(nsn));

	b->nsn = nsn;
	KNH_SETv(ctx, b->nsproto, new_Prototype(ctx, nsn));
	b->this_cid = knh_Object_cid(b->nsproto);
}

/* ------------------------------------------------------------------------ */

INLINE
NameSpace *knh_Cmpl_getNameSpace(Ctx *ctx, Cmpl *b)
{
	return b->nsproto->ns;
}

/* ======================================================================== */
/* [main] */



Stmt *knh_konohac_parse(Ctx *ctx, InputStream *in)
{
	KNH_LOPEN(ctx, 0);
	Token *tk = new_Token__ch(ctx, in, '{');
	KNH_LPUSH(ctx, tk);
	knh_Token_parse(ctx, tk, in);
	DEMO_DUMP(ctx, tk, KNH_NULL, "tokens");
	Stmt *stmt = new_Stmt__block(ctx, knh_Token_ts(tk), 0, knh_Token_tokens_size(tk));
	KNH_LCLOSE(ctx);
	return stmt; 
}

/* ------------------------------------------------------------------------ */

knh_nsn_t knh_konohac_compile(Ctx *ctx, knh_nsn_t nsn, Stmt *stmt)
{
	DEMO_DUMP(ctx, stmt, KNH_NULL, "parsed tree");

	Cmpl *cmpl = knh_Context_getCompiler(ctx, (Context*)ctx);

	knh_Cmpl_changeNameSpace(ctx, cmpl, nsn);
	knh_Stmt_visit(ctx, stmt, knh_stmtvisit_declc, cmpl, 0);

	knh_Cmpl_changeNameSpace(ctx, cmpl, nsn);
	knh_Stmt_visit(ctx, stmt, knh_stmtvisit_declm, cmpl, 0);

	knh_Cmpl_changeNameSpace(ctx, cmpl, nsn);
	knh_Stmt_visit(ctx, stmt, knh_stmtvisit_declv, cmpl, 0);

	knh_Cmpl_changeNameSpace(ctx, cmpl, nsn);
	knh_Stmt_visit(ctx, stmt, knh_stmtvisit_asm, cmpl, 0);

	return cmpl->nsn;
}

/* ------------------------------------------------------------------------ */

knh_nsn_t
knh_konohac_eval(Ctx *ctx, knh_nsn_t nsn, InputStream *in)
{
	/* try */
	KNH_LOPEN(ctx, 0);
	KNH_PUSHv(ctx, new_ExceptionHandler(ctx));          /* 0 */
	KNH_PUSHv(ctx, KNH_NULL);                           /* 1 Exception e */

	DEBUG_ASSERT(IS_ExceptionHandler(KNH_LOCALv(0)));
	VM_TRY_BEGIN(ctx, NPC, L_CATCH_EXCEPTION, KNH_LOCALv(0), KNH_LOCALv(1));

	/* body */
	KNH_LPUSH(ctx, in);
//	int ch;
//	while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
//		putchar(ch);
//	}
//	putchar('\n');
	Stmt *stmt = knh_konohac_parse(ctx, in);
	KNH_LPUSH(ctx, stmt);
	nsn = knh_konohac_compile(ctx, nsn, stmt);
	KNH_LCLOSE(ctx);	
	return nsn;
	
	/* catch */
	L_CATCH_EXCEPTION:;
	VM_TRY_END(ctx, KNH_LOCALv(0));
	DEBUG_ASSERT(IS_Exception(KNH_LOCALv(1)));
	knh_format(ctx, KNH_STDOUT, METHODN__dump, KNH_LOCALv(1), KNH_NULL);
	KNH_LCLOSE(ctx);
	return nsn;
}



/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
