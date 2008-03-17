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

#include<konoha/konohac_asm_.h>

/* ======================================================================== */
/* [structs] */

void
knh_VirtualMachineCode_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	VirtualMachineCode *b =  (VirtualMachineCode*)s1;
	b->size = 0;
	b->code = (knh_vmc_t*)"";
	b->filen = 0;
	b->nsn = 0;
	b->dwarf = NULL;
	b->dsize = 0;
}

/* ------------------------------------------------------------------------ */

void
knh_VirtualMachineCode_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
	VirtualMachineCode *b =  (VirtualMachineCode*)s1;
	VirtualMachineCode *b2 = (VirtualMachineCode*)s2;
	
	b2->size = b->size;
	b2->code = (knh_vmc_t*)knh_malloc(ctx, KNH_SIZE(b->size));
	knh_memcpy(b2->code, b->code, b2->size);
	
	b2->filen = b->filen;
	b2->nsn = b->nsn;
	b2->dsize = b->dsize;
	b2->dwarf = (knh_dwarf_t*)knh_malloc(ctx, b2->dsize * sizeof(knh_dwarf_t));
	knh_memcpy(b2->dwarf, b->dwarf, b2->dsize);
}

/* ------------------------------------------------------------------------ */

#define _knh_VirtualMachineCode_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void
knh_VirtualMachineCode_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	VirtualMachineCode *b = (VirtualMachineCode*)s;
	knh_VirtualMachineCode_utraverse(ctx, knh_VirtualMachineCode_tobytes(b), gc);
	if(IS_SWEEP(gc)) {
		knh_free(b->code, KNH_SIZE(b->size));
		if(b->dwarf != NULL) {
			knh_free(b->dwarf, b->dsize * sizeof(knh_dwarf_t));
		}
	}
}

/* ======================================================================== */
/* [constructors] */


VirtualMachineCode* new_VirtualMachineCode(Ctx *ctx, knh_filen_t filen, knh_nsn_t nsn, knh_bytes_t elf, knh_bytes_t dwarf)
{
	VirtualMachineCode* b = (VirtualMachineCode*)knh_Object_malloc(ctx, CLASS_VirtualMachineCode);
	knh_VirtualMachineCode_struct_init(ctx, (Struct*)b, 0, NULL);

	b->filen = filen;
	b->nsn = nsn;
	
	b->code = (knh_vmc_t*)knh_malloc(ctx, KNH_SIZE(elf.len));
	b->size = elf.len;
	knh_memcpy(b->code, elf.buf, elf.len);

	DEBUG_ASSERT(dwarf.len % sizeof(knh_dwarf_t) == 0);
	b->dsize = dwarf.len / sizeof(knh_dwarf_t);
	b->dwarf = (knh_dwarf_t*)knh_malloc(ctx, b->dsize * sizeof(knh_dwarf_t));
	knh_memcpy(b->dwarf, dwarf.buf, dwarf.len);
	return b;
}

/* ======================================================================== */
/* [methods] */

void knh_VirtualMachineCode_exec(Ctx *ctx, Object **sf);

/* ------------------------------------------------------------------------ */

void knh_Method_setVirtualMachineCode(Ctx *ctx, Method *b, VirtualMachineCode *code)
{
	DEBUG_ASSERT(IS_VirtualMachineCode(code));
	if(knh_Method_isObjectCode(b)) {
		KNH_SETv(ctx, b->code, code);
	}else {
		KNH_INITv(b->code, code);
		knh_Method_setObjectCode(b, 1);
	}
	b->func = knh_VirtualMachineCode_exec;
}

/* ------------------------------------------------------------------------ */

INLINE
VirtualMachineCode *knh_Method_vmc(Method *b)
{
	DEBUG_ASSERT(IS_VirtualMachineCode(b->code));
	return (VirtualMachineCode*)b->code;
}

/* ------------------------------------------------------------------------ */

knh_bytes_t knh_VirtualMachineCode_tobytes(VirtualMachineCode *b)
{
	return new_bytes__2(b->code, b->size);
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bytes_t knh_stackf_vmc(Ctx *ctx, Object **sf)
{
	return knh_VirtualMachineCode_tobytes((VirtualMachineCode*)knh_Method_vmc(sf[-1]));
}

/* ------------------------------------------------------------------------ */

INLINE
knh_vmc_t *knh_VirtualMachineCode_pc(VirtualMachineCode *b)
{
	return b->code;
}

/* ------------------------------------------------------------------------ */

char *knh_Method_file(Method *mtd, knh_vmc_t *pc)
{
	if(!knh_Method_isObjectCode(mtd) || !IS_VirtualMachineCode(mtd->code)) {
		return "(unknown)";
	}
	return FILEN(((VirtualMachineCode*)mtd->code)->filen);
}

/* ------------------------------------------------------------------------ */

int knh_Method_pcline(Method *mtd, knh_vmc_t *pc)
{
	if(!knh_Method_isObjectCode(mtd) || !IS_VirtualMachineCode(mtd->code)) {
		return 0;
	}
	VirtualMachineCode *b = (VirtualMachineCode*)mtd->code;
	if(b->dwarf == NULL && b->dsize > 0) {
		return 0;
	}
	int i = 0, offset = pc - b->code;
	for(i = 0; i < b->dsize - 1; i++) {
		if(b->dwarf[i].offset <= offset && offset < b->dwarf[i+1].offset) {
			return b->dwarf[i].line;
		}
	}
	return b->dwarf[b->dsize-1].line;
}

/* ------------------------------------------------------------------------ */
/* @method void VirtualMachineCode.%dump(OutputStream w, Any m) */

void knh_VirtualMachineCode__dump(Ctx *ctx, VirtualMachineCode *b, OutputStream *w, Any *m)
{
	knh_VirtualMachineCode__dump_(ctx, b, w, m);
}

/* ------------------------------------------------------------------------ */
/* @method void Method.%code(OutputStream w, Any m) */

void knh_Method__code(Ctx *ctx, Method *b, OutputStream *w, Any *m)
{
	knh_Method__dump(ctx, b, w, m);
	knh_println(ctx, w, STEXT(""));
	if(knh_Method_isObjectCode(b)) {
		if(IS_VirtualMachineCode(b->code)) {
			knh_VirtualMachineCode__dump_(ctx, (VirtualMachineCode*)b->code, w, b);
		}
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
