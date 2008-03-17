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
/* [begin] */

void knh_Cmpl_startCompilation(Ctx *ctx, Cmpl *b, knh_filen_t filen)
{
	DEBUG_ASSERT(IS_Method(b->method));
	//DEBUG("%s.(fn=%s)", CLASSN(b->this_cid), METHODN(b->method->mn));
	DEBUG_ASSERT(b->method->cid == b->this_cid);
	
	b->flag = 0;
//	KNH_SETv(ctx, b->stmt_label, KNH_NULL);
	
	b->nastep = 0;
	b->llstep = 0;
	b->filen  = filen;
	b->line   = 0;
	knh_Bytes_clear(b->elf);
	knh_Bytes_clear(b->dwarf);
	knh_DictIdx_clear(ctx, b->labelIdDictIdx);
	knh_DictSet_clear(ctx, b->labelAddrDictSet);
	knh_Array_clear(ctx, b->lstacks);
	knh_Cmpl_setCancelled(b, 0);

	//DEBUG(" ** START COMPILATION **");
}

/* ------------------------------------------------------------------------ */

void knh_Cmpl_clear(Ctx *ctx, Cmpl *b)
{
	b->flag = 0;	
	b->nastep = 0;
	b->llstep = 0;
	b->filen  = 0;
	b->line   = 0;
	knh_Bytes_clear(b->elf);
	knh_Bytes_clear(b->dwarf);
	knh_DictIdx_clear(ctx, b->labelIdDictIdx);
	knh_DictSet_clear(ctx, b->labelAddrDictSet);
	knh_Array_clear(ctx, b->lstacks);
	knh_Cmpl_setCancelled(b, 0);
}

/* ------------------------------------------------------------------------ */

void knh_Cmpl_stopCompilation(Ctx *ctx, Cmpl *b)
{
	knh_Cmpl_setCancelled(b, 1);
	TODO();
}

/* ------------------------------------------------------------------------ */

void knh_Cmpl_endCompilation(Ctx *ctx, Cmpl *b)
{
	KNH_ASSERT(IS_NOTNULL(b->method));
	
	/* 1. add safety return */
	KNH_ASM_SETLINE(ctx, b, 0);
	 /* generated code */
	knh_type_t rtype = knh_Method_rtype(b->method);
	if(rtype == TYPE_void) {
		//KNH_ASM_STACKDUMP(ctx, b);
		KNH_ASM_RET_VOID(ctx, b);
	}
	else if(knh_Method_isNew(b->method)) {
		if(TYPE_ISNOTNULL(rtype)) {
			KNH_ASM_NULLCHK__sfp(ctx, b, 0);
		}
		KNH_ASM_RET__sfp(ctx, b, 0);
	}
	else {
		if(rtype == TYPE_any) {
			/* return final top value */
			if(TYPE_ISNOTNULL(rtype)) {
				KNH_ASM_NULLCHK__ebp(ctx, b, 0);
			}
			//KNH_ASM_STACKDUMP(ctx, b);
			KNH_ASM_RET__ebp(ctx, b, 0);
		}
		else {
			Object *v = knh_Method_returnValue(ctx, b->method);
			if(IS_NOTNULL(v) || TYPE_ISNULLABLE(rtype)) {
				KNH_ASM_RET__OBJ(ctx, b, v);
			}
			else {
				KNH_ASM_MOVE__OBJ(ctx, b, 0, v);
				KNH_ASM_NULLCHK__ebp(ctx, b, 0);
				KNH_ASM_RET__ebp(ctx, b, 0);
			}	
		}
	}
	KNH_ASM_SETLINE(ctx, b, b->line+1);

	/* 2. remap address */
	knh_Cmpl_remapAddress(ctx, b);

	//DEBUG(" ** END COMPILATION **");

	if(knh_Cmpl_isCancelled(b)) {
		DEBUG("compliation cancelled");
		knh_Method_toAbstract(ctx, b->method);
	}
	else {
		VirtualMachineCode *vmc = new_VirtualMachineCode(ctx, b->filen, b->nsn, knh_Bytes_tobytes(b->elf), knh_Bytes_tobytes(b->dwarf));
		knh_Method_setVirtualMachineCode(ctx, b->method, vmc);
		DEMO_DUMP(ctx, vmc, b->method, "compiled code");
	}
	knh_Cmpl_clear(ctx, b);
}

/* ======================================================================== */
/* [asmmalloc] */

INLINE
void *knh_Cmpl_asmmalloc(Ctx *ctx, Cmpl *b, size_t size)
{
//	DEBUG("size=%d", (int)size);
	size_t off = knh_Bytes_size(b->elf);
	int i ;
	for(i = 0; i < size; i++) {
		knh_Bytes_putc(ctx, b->elf, 0);
	}
	return (void*)(knh_Bytes_value(b->elf) + off);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
