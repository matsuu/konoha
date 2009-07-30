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
#ifdef KONOHA_ON_LKM
#include"../../include/konoha/gen/konohac_klr_.h"
#else
#include<konoha/gen/konohac_klr_.h>
#endif

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [structs] */


/* ======================================================================== */
/* [constructors] */

KLRCode* new_KLRCode(Ctx *ctx, knh_urid_t urid, knh_bytes_t elf, knh_bytes_t dwarf)
{
	knh_KLRCode_t *o = (KLRCode*)new_Object_bcid(ctx, CLASS_KLRCode, 0);

	DP(o)->urid = urid;
	DP(o)->code = (knh_code_t*)KNH_MALLOC(ctx, KNH_SIZE(elf.len));
	DP(o)->size = elf.len;
	knh_memcpy(DP(o)->code, elf.buf, elf.len);

	KNH_ASSERT(dwarf.len % sizeof(knh_dwarf_t) == 0);
	DP(o)->dsize = dwarf.len / sizeof(knh_dwarf_t);
	DP(o)->dwarf = (knh_dwarf_t*)KNH_MALLOC(ctx, DP(o)->dsize * sizeof(knh_dwarf_t));
	knh_memcpy(DP(o)->dwarf, dwarf.buf, dwarf.len);
	return o;
}

/* ======================================================================== */
/* [methods] */

METHOD knh_KLRCode_exec(Ctx *ctx, knh_sfp_t *sfp);

/* ------------------------------------------------------------------------ */

void knh_Method_setKLRCode(Ctx *ctx, Method *mtd, KLRCode *code)
{
	KNH_ASSERT(IS_KLRCode(code));
	if(knh_Method_isObjectCode(mtd)) {
		KNH_SETv(ctx, DP(mtd)->code, code);
	}else {
		KNH_INITv(DP(mtd)->code, code);
		knh_Method_setObjectCode(mtd, 1);
	}
	knh_Method_syncFunc(mtd, knh_KLRCode_exec);
	mtd->pc_start = DP(code)->code;
}


/* ------------------------------------------------------------------------ */

knh_code_t* knh_Method_pcstartNULL(Method *mtd)
{
	if(knh_Method_isObjectCode(mtd)) {
		KLRCode *o = (KLRCode*)DP(mtd)->code;
		if(IS_KLRCode(o)) {
			return DP(o)->code;
		}
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

knh_bytes_t knh_KLRCode_tobytes(KLRCode *o)
{
	KNH_ASSERT(IS_KLRCode(o));
	return new_bytes__2((char*)DP(o)->code, DP(o)->size);
}

/* ------------------------------------------------------------------------ */

char *knh_Method_file(Ctx *ctx, Method *mtd)
{
	if(!knh_Method_isObjectCode(mtd) || !IS_KLRCode((Object*)DP(mtd)->code)) {
		return "(naitive)";
	}
	KLRCode *o = (KLRCode*)DP(mtd)->code;
	return URIDN(DP(o)->urid);
}

/* ------------------------------------------------------------------------ */

int knh_Method_pctoline(Method *mtd, knh_code_t *pc)
{
	if(knh_Method_isObjectCode(mtd) && IS_KLRCode((Object*)DP(mtd)->code)) {
		knh_KLRCode_t *o = (KLRCode*)DP(mtd)->code;
		int offset = pc - DP(o)->code;
		if(0 <= offset && offset <= DP(o)->size) {
			int i;
			for(i = 0; i < (int)DP(o)->dsize - 1; i++) {
				if(DP(o)->dwarf[i].offset <= offset && offset < DP(o)->dwarf[i+1].offset) {
					return DP(o)->dwarf[i].line;
				}
			}
			return DP(o)->dwarf[DP(o)->dsize-1].line;
		}
	}
	return 0;
}

/* ------------------------------------------------------------------------ */
/* [asm] */
/* ------------------------------------------------------------------------ */

int knh_Asm_constId(Ctx *ctx, Asm *abr, Object *o)
{
	if(IS_NOTNULL(DP(abr)->constPools)) {
		knh_class_t cid = knh_Object_cid(o);
		Array *a = DP(abr)->constPools;
		size_t i;
		for(i = 0; i < (a)->size; i++) {
			Object *ao = knh_Array_n(a, i);
			if(cid != knh_Object_cid(ao)) continue;
			if(knh_Object_compareTo(ctx, o, ao) == 0) {
				return (int)i;
			}
		}
	}
	else {
		KNH_SETv(ctx, DP(abr)->constPools, new_Array0(ctx, 0));
	}
	knh_Array_add(ctx, DP(abr)->constPools, o);
	return (int)(DP(abr)->constPools)->size - 1;
}

/* ------------------------------------------------------------------------ */

int knh_Asm_classId(Ctx *ctx, Asm *abr, knh_class_t cid)
{
	TODO();
	return 0;
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%const(OutputStream w, String m) */

void knh_Int__const(Ctx *ctx, Int *o, OutputStream *w, String *m)
{
	knh_write(ctx, w, STEXT("new_Int(ctx, "));
	knh_write_ifmt(ctx, w, KNH_INT_FMT, o->n.ivalue);
	knh_write(ctx, w, STEXT(")"));
}

/* ------------------------------------------------------------------------ */
/* @method void Method.%const(OutputStream w, String m) */

void knh_Method__const(Ctx *ctx, Method *o, OutputStream *w, String *m)
{
	knh_write(ctx, w, STEXT("knh_Class_getMethod(ctx, CLASS_(\""));
	knh_write_cid(ctx, w, DP(o)->cid);
	knh_write(ctx, w, STEXT("\"), METHODN_(\""));
	knh_write_mn(ctx, w, DP(o)->mn);
	knh_write(ctx, w, STEXT("\"))"));
}

/* ------------------------------------------------------------------------ */

static
void knh_Asm_genConstPool(Ctx *ctx, Asm *abr, OutputStream *w)
{
	knh_println(ctx, w, STEXT("size_t knh_loadConstPools(Ctx *ctx)"));
	knh_println(ctx, w, STEXT("{"));
	knh_println(ctx, w, STEXT("\tsize_t delta = (DP(ctx->sys)->constPools)->size;"));
	if(IS_NOTNULL(DP(abr)->constPools)) {
		Array *a = DP(abr)->constPools;
		size_t i;
		for(i = 0; i < (a)->size; i++) {
			Object *ao = knh_Array_n(a, i);
			knh_write(ctx, w, STEXT("\tknh_addConstPools(ctx, "));
			knh_format(ctx, w, METHODN__const, ao, KNH_NULL);
			knh_println(ctx, w, STEXT(");"));
		}
	}
	knh_println(ctx, w, STEXT("\treturn delta;"));
	knh_println(ctx, w, STEXT("}"));
}

/* ------------------------------------------------------------------------ */
/* @method void Method.%c(OutputStream w, String m) */

void knh_Method__c(Ctx *ctx, Method *mtd, OutputStream *w, String *m)
{
	knh_write(ctx, w, STEXT("METHOD knh__"));
	KNH_ASSERT_cid(DP(mtd)->cid);
	knh_write(ctx, w, knh_String_tobytes(ctx->share->ClassTable[DP(mtd)->cid].sname));
	knh_putc(ctx, w, '_');
	knh_write_mn(ctx, w, DP(mtd)->mn);
	knh_println(ctx, w, STEXT("(Ctx *ctx, knh_sfp_t *sfp)"));
	if((mtd)->fcall_1 == knh_KLRCode_exec) {
		knh_code_generate(ctx, knh_Context_getAsm(ctx), (mtd)->pc_start, w);
	}
}

/* ------------------------------------------------------------------------ */

void knh_Asm_genMethod(Ctx *ctx, Asm *abr, OutputStream *w)
{
	knh_println(ctx, w, STEXT("#include<konoha.h>"));
	knh_write_EOL(ctx, w);
	if(IS_NOTNULL(DP(abr)->exportsMethods)) {
		Array *a = DP(abr)->exportsMethods;
		size_t i;
		for(i = 0; i < (a)->size; i++) {
			Method *mtd = (Method*)knh_Array_n(a, i);
			knh_println(ctx, w, STEXT("static"));
			knh_Method__c(ctx, mtd, w, (String*)KNH_NULL);
			knh_write_EOL(ctx, w);
		}
	}

	knh_println(ctx, w, STEXT("knh_fmethod konoha_findCompiledFunc(Ctx *ctx, knh_bytes_t cname, knh_bytes_t mname)"));
	knh_println(ctx, w, STEXT("{"));
	knh_println(ctx, w, STEXT("\tsize_t delta = (DP(ctx->sys)->constPools)->size;"));
	if(IS_NOTNULL(DP(abr)->exportsMethods)) {
		Array *a = DP(abr)->exportsMethods;
		size_t i;
		for(i = 0; i < (a)->size; i++) {
			Method *mtd = (Method*)knh_Array_n(a, i);
			knh_write(ctx, w, STEXT("\tif(ISB(mname, \""));
			knh_write_mn(ctx, w, DP(mtd)->mn);
			knh_write(ctx, w, STEXT("\") && ISB(cname, \""));
			knh_write_cid(ctx, w, DP(mtd)->cid);
			knh_println(ctx, w, STEXT("\")) {"));
			knh_write(ctx, w, STEXT("\t\treturn knh__"));
			knh_write(ctx, w, knh_String_tobytes(ctx->share->ClassTable[DP(mtd)->cid].sname));
			knh_putc(ctx, w, '_');
			knh_write_mn(ctx, w, DP(mtd)->mn);
			knh_println(ctx, w, STEXT(";"));
			knh_write(ctx, w, STEXT("\t}"));
		}
	}
	knh_println(ctx, w, STEXT("\treturn NULL"));
	knh_println(ctx, w, STEXT("}"));
	knh_write_EOL(ctx, w);
	knh_Asm_genConstPool(ctx, abr, w);
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */

void knh_Asm_loadCompiledMethod(Ctx *ctx, Asm *abr)
{

}

/* ------------------------------------------------------------------------ */

knh_fmethod knh_Asm_getCompiledMethod(Ctx *ctx, Asm *abr, knh_bytes_t cname, knh_bytes_t mname)
{
	return NULL;
}


/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
