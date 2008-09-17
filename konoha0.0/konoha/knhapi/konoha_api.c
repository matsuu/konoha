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
/* [konoha] */

/* ------------------------------------------------------------------------ */

static int knh_systemIsInitialized = 0;
static knh_uint_t knh_runtimeId = 0;

void konoha_class_init0(Ctx *ctx);

/* ------------------------------------------------------------------------ */

static
void konoha_init0()
{
	knh_tObject_init0();
	knh_tContext_init0();
	knh_tStruct_init0();
	knh_tClass_init0();
	konoha_class_init0(NULL);
}

/* ------------------------------------------------------------------------ */

KNHAPI(konoha_t) konoha_open(void)
{
	if(knh_systemIsInitialized == 0) {
		konoha_init0();
		knh_systemIsInitialized = 1;
	}
	{
		Runtime *runtime = new_Runtime0(knh_runtimeId++);
		konoha_t k = {KONOHA_MAGIC, runtime};
		knh_Object_RCinc((Object*)runtime);
		return k;
	}
}

/* ------------------------------------------------------------------------ */

static
void konoha_traverse(Ctx *ctx, f_traverse f)
{
	knh_tContext_traverse(ctx, f);
	knh_tObject_traverse(ctx, f);
	knh_tStruct_traverse(ctx, f);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_close(konoha_t konoha)
{
	if(konoha.magic == KONOHA_MAGIC) {
		if(!IS_Runtime(konoha.runtime)) {
			KNH_SAYS("Maybe already closed");
			return;
		}
		knh_Object_RCsweep(NULL, UP(konoha.runtime));
		if(knh_Runtime_isAllClosed()) {
			konoha_traverse(NULL, knh_Object_RCsweep);
#ifdef KNH_DBGMODE
			if(knh_stat_usedMemorySize() != 0) {
				KNH_SAYS("MEMORY LEAK: %d bytes", (int)knh_stat_usedMemorySize());
			}
#endif
		}
	}
	else{
		KNH_SAYS("This is not a Konoha Scripting Engine");
	}
}

/* ======================================================================== */
/* [context] */

KNHAPI(Ctx*) konoha_open_context(konoha_t konoha)
{
	if(konoha.magic == KONOHA_MAGIC && IS_Runtime(konoha.runtime)) {
		return new_Context0(konoha.runtime, KNH_STACKSIZE);
	}
	else {
		KNH_SAYS("This is not a Konoha Scripting Engine");
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_close_context(konoha_t konoha, Ctx *ctx)
{
	knh_Object_t *o = (knh_Object_t*)ctx;
	knh_Context_clearstack(ctx);
	if(konoha.magic == KONOHA_MAGIC && IS_Context(o)) {
		knh_Object_RCsweep(ctx, o);
	}
	else {
		KNH_SAYS("This is not a Konoha Scripting Engine");
	}
}

/* ======================================================================== */
/* [konoha] */

//void konoha_eval(Ctx *ctx, char *script)
//{
//	if(ctx == NULL) {
//		return;
//	}
//	else {
//		TODO();
////		knh_wbuf_t cb = knh_Context_wbuf(ctx);
////		knh_Bytes_write(ctx, cb.ba, B(script));
////		InputStream *in = new_InputStream__Bytes(ctx, cb.ba, cb.pos, knh_Bytes_size(cb.ba));
////		in->filen = knh_tfilen_forname(ctx, STEXT("(eval)"));
////		knh_konohac_eval(ctx, NSN_main, in);
////		knh_wbuf_clear(cb)
//	}
//}
//

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_read(Ctx *ctx, char *fpath)
{
	if(ctx == NULL) return;
	FILE *fp = knh_fopen(fpath, "r");
	if(fp == NULL) {
		KNH_WARNING(ctx, "No such script file: %s\n", fpath);
		return;
	}

	InputStream *in = new_InputStream__FILE(ctx, fp);
	DP(in)->fileid = knh_tName_getFileId(ctx, B(fpath));
	knh_InputStream_setEncoding(ctx, in, knh_systemEncoding);
	knh_konohac_eval(ctx, (String*)KNH_NULL, in);
	knh_Context_clearstack(ctx);
}

/* ------------------------------------------------------------------------ */

KNHAPI(int) konoha_main(Ctx *ctx, int argc, char **argv)
{
	/* try */
	KNH_LOPEN(ctx, 0);
	KNH_LPUSH(ctx, new_ExceptionHandler(ctx));          /* 0 */
	KNH_LPUSH(ctx, KNH_NULL);                           /* 1 Exception e */

	KNH_ASSERT(IS_ExceptionHandler(KNH_LOCALn(0)));
	VM_TRY_BEGIN(ctx, NPC, L_CATCH_EXCEPTION, KNH_LOCALn(0), KNH_LOCALn(1));
	{
		NameSpace *ns = knh_Runtime_getNameSpace(ctx, STEXT("main"));
		Script *scr = knh_NameSpace_getScript(ctx, ns);
		Method *mtd = knh_Class_getMethod(ctx, knh_Object_cid(scr), METHODN_main);

		if(IS_NULL(mtd)) {
			goto L_END_TRY;
		}
		if(knh_Method_psize(mtd) == 1) {
			knh_type_t ptype = knh_Method_ptype(mtd, 0);
			if(ptype != ATYPE_String) {
				KNH_WARNING(ctx, "Type!!: cannot invoke main()");
				goto L_END_TRY;
			}
			else {
				Array *a = new_Array(ctx, CLASS_String, argc);
				int i;
				for(i = 0; i < argc; i++) {
					knh_Array_add(ctx, a, UP(new_String__T(ctx, argv[i])));
				}
				KNH_LPUSH(ctx, mtd);                            /* 2 mtd, return ebp[-1] */
				KNH_LPUSH(ctx, scr);                            /* 3 this ebp[0] */
				KNH_LPUSH(ctx, a);
				KNH_SCALL(ctx, 2);
			}
		}
		else {
			KNH_WARNING(ctx, "Type!!: cannot invoke main()");
			goto L_END_TRY;
		}
	}
	L_END_TRY:
	KNH_LCLOSE(ctx);
	knh_Context_clearstack(ctx);
	return 0;

	/* catch */
	L_CATCH_EXCEPTION:;
	VM_TRY_END(ctx, (ExceptionHandler*)KNH_LOCALn(0));
	KNH_ASSERT(IS_Exception(KNH_LOCALn(1)));
	knh_format(ctx, KNH_STDOUT, METHODN__dump, KNH_LOCALn(1), KNH_NULL);
	KNH_LCLOSE(ctx);
	return 0;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
