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

/* ======================================================================== */
/* [label] */

int knh_Cmpl_nastep(Cmpl *b)
{
	return (int)b->nastep++;
}

/* ------------------------------------------------------------------------ */

int knh_Cmpl_llstep(Cmpl *b)
{
	return (int)b->llstep++;
}

/* ------------------------------------------------------------------------ */

void knh_Cmpl_setGlobalLabel(Ctx *ctx, Cmpl *b, String *label)
{
	knh_DictIdx_add(ctx, b->labelIdDictIdx, label);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_Cmpl_hasGlobalLabel(Ctx *ctx, Cmpl *b, knh_bytes_t label)
{
#if defined(KONOHA_DEBUGMODE)
	knh_ushort_t id = (knh_ushort_t)knh_DictIdx_add__b(ctx, b->labelIdDictIdx, label);
	DEBUG("LABEL %s id=%d", label.buf, (int)id);
#endif
	return (knh_DictIdx_add__b(ctx, b->labelIdDictIdx, label) != 0);
}

/* ------------------------------------------------------------------------ */

void knh_Cmpl_setBreakLabel(Ctx *ctx, Cmpl *b, String *label)
{
	knh_DictIdx_add(ctx, b->labelIdDictIdx, label);
	char bufl[LABEL_BUFSIZ];
	snprintf(bufl, sizeof(bufl), "_END_%s", knh_String_tochar(label));
	knh_DictIdx_add__b(ctx, b->labelIdDictIdx, B(bufl));
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_Cmpl_hasBreakLabel(Ctx *ctx, Cmpl *b, knh_bytes_t label)
{
	char bufl[LABEL_BUFSIZ];
	snprintf(bufl, sizeof(bufl), "_END_%s", label.buf);
	knh_DictIdx_add__b(ctx, b->labelIdDictIdx, B(bufl));
	return knh_Cmpl_hasGlobalLabel(ctx, b, B(bufl));
}

/* ------------------------------------------------------------------------ */

knh_short_t knh_Cmpl_labelId(Ctx *ctx, Cmpl *b, knh_bytes_t label)
{
	knh_ushort_t id = (knh_ushort_t)knh_DictIdx_add__b(ctx, b->labelIdDictIdx, label);
//	DEBUG("LABEL %s id=%d", label.buf, (int)id);
	return id;
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_LABEL(Ctx *ctx, Cmpl *b, Token *tkl)
{
	knh_bytes_t label = knh_Token_tobytes(tkl);
	if(knh_DictSet_get__b(b->labelAddrDictSet, label) != 0) {
		MC_EPRINT(ctx, tkl, MC_IGNORED, "Duplicated label: %s", label.buf);
		return;
	}
	knh_vmc_t *pc = (knh_vmc_t*)knh_Bytes_last(b->elf);
	DEBUG_ASSERT(IS_String(tkl->data));
	knh_DictSet_put(ctx, b->labelAddrDictSet, (String*)tkl->data, (knh_uint_t)pc);
	//DEBUG("SET LABEL '%s' at %p", label.buf, pc);
}

/* ------------------------------------------------------------------------ */

void KNH_ASM_LABEL__b(Ctx *ctx, Cmpl *b, knh_bytes_t t)
{
	if(knh_DictSet_get__b(b->labelAddrDictSet, t) != 0) {
		DEBUG("Duplicated label: %s", t.buf);
		DEBUG_ASSERT(ctx == NULL);
		return;
	}
	knh_vmc_t *pc = (knh_vmc_t*)knh_Bytes_last(b->elf);
	knh_DictSet_put(ctx, b->labelAddrDictSet, new_String__fast(ctx, CLASS_String, t), (knh_uint_t)pc);
	//DEBUG("SET LABEL '%s' at %p", t.buf, pc);
}

/* ======================================================================== */
/* [lstack] */

knh_bool_t knh_Stmt_hasContinueBreak(Stmt *b)
{
	switch(b->stt) {
		case STT_WHILE:
		case STT_DO:
		case STT_FOR:
		case STT_FOREACH:	
			return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

void knh_Cmpl_lstack_push(Ctx *ctx, Cmpl *b, String *label)
{
	knh_Array_add(ctx, b->lstacks, label);
}

/* ------------------------------------------------------------------------ */

StringNULL *knh_Cmpl_lstack_label(Ctx *ctx, Cmpl *b)
{
	size_t s = knh_Array_size(b->lstacks);
	if(s == 0) {
		return NULL;
	}
	return knh_Array_n(b->lstacks, s-1);
}

/* ------------------------------------------------------------------------ */

void knh_Cmpl_lstack_pop(Ctx *ctx, Cmpl *b)
{
	knh_Array_pop(ctx, b->lstacks);
}

/* ======================================================================== */
/* [line] */

void KNH_ASM_SETLINE(Ctx *ctx, Cmpl *b, int line)
{
	if(line > b->line) {
		char *top = knh_Bytes_tochar(b->elf);
		char *cur = (char*)knh_Bytes_last(b->elf);
		int offset = cur - top;
		//DEBUG("line=%d at=%d", line, offset);
		knh_dwarf_t dw = {offset, line};
		knh_Bytes_write(ctx, b->dwarf, B2((void*)(&dw), sizeof(knh_dwarf_t)));
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
