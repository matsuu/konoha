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


/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [argc] */

/* ------------------------------------------------------------------------ */

int knh_sfp_argc(Ctx *ctx, knh_sfp_t *v)
{
	return (((Context*)ctx)->esp - v);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_sfp_boxing(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_class_t bcid = (sfp[0].o)->h.bcid;
	if(CLASS_Boolean <= bcid
#ifndef KNH_USING_NOFLOAT
            && bcid <= CLASS_Float
#endif
            && sfp[0].data != knh_Object_data(sfp[0].o)) {
		KNH_MOV(ctx, sfp[0].o, new_Object_boxing(ctx, knh_Object_cid(sfp[0].o), sfp));
	}
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_sfp_unboxing(Ctx *ctx, knh_sfp_t *sfp)
{
	sfp[0].data = knh_Object_data(sfp[0].o);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_esp1_sformat(Ctx *ctx, Method *mtd, OutputStream *w, Any *m)
{
	DBG2_ASSERT(IS_Method(mtd));
	knh_sfp_t *esp = KNH_LOCAL(ctx);
	KNH_SETv(ctx, esp[2].o, w);
	KNH_SETv(ctx, esp[3].o, m);
	KNH_SCALL(ctx, esp, 0, mtd, /*args*/2);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_esp1_format(Ctx *ctx, knh_methodn_t mn, OutputStream *w, Any *m)
{
	knh_sfp_t *esp = KNH_LOCAL(ctx);
	Method *mtd = konoha_lookupFormatter(ctx, knh_Object_cid(esp[1].o), mn);
	DBG2_ASSERT(esp == ctx->esp);
	KNH_SETv(ctx, esp[2].o, w);
	KNH_SETv(ctx, esp[3].o, m);
	KNH_SCALL(ctx, esp, 0, mtd, /*args*/2);
}

/* ------------------------------------------------------------------------ */
/* @method void System.stackdump() */

METHOD knh__System_stackdump(Ctx *ctx, knh_sfp_t *sfp)
{
	fprintf(stderr, "\n** ** ** ** ** ** ** ** **\n");
	int i;
	if(sfp-1 > ctx->stack && IS_Method(sfp[-1].mtd)) {
		char buf[CLASSNAME_BUFSIZ];
		knh_format_cmethodn(ctx, buf, sizeof(buf), DP(sfp[-1].mtd)->cid, DP(sfp[-1].mtd)->mn);
		fprintf(stderr, "sfp[-1] %s data=%d\n", buf, (int)sfp[-1].data);
	}
	for(i = 0; sfp + i < ctx->esp; i++) {
		fprintf(stderr, "sfp[%2d] %s data=%d\n", i, CLASSN(sfp[i].o->h.cid), (int)sfp[i].data);
	}
	for(i = 0; i < 2; i++) {
		fprintf(stderr, "esp[%2d] %s data=%d\n", i, CLASSN(ctx->esp[i].o->h.cid), (int)sfp[i].data);
	}
	fprintf(stderr, "** ** ** ** ** ** ** ** **\n");
}

/* ======================================================================== */
/* [call] */

void knh_sfp_typecheck(Ctx *ctx, knh_sfp_t *sfp, Method *mtd, knh_code_t *pc)
{
	DBG2_ASSERT(IS_Method(sfp[-1].mtd));
	char *emsg;
	knh_class_t this_cid = knh_Object_cid(sfp[0].o);
	int i, argc = knh_Method_isVarArgs(mtd) ? (ctx->esp - sfp) : knh_Method_psize(mtd);
	for(i = 1; i < argc; i++) {
		knh_type_t type = knh_Method_ptype(ctx, mtd, this_cid, i);
		if(IS_NULL(sfp[i].o)) {
			if(IS_NNTYPE(type)) {
				emsg = "Null!!: the parameter %d of %M"; goto L_THROWERR;
			}
		}
		else {
			knh_class_t reqc = CLASS_type(type);
			if(!knh_class_instanceof(ctx, knh_Object_cid(sfp[i].o), reqc)) {
				emsg = "Null!!: the parameter %d of %M"; goto L_THROWERR;
			}
		}
	}
	return;

	L_THROWERR:
	{
		knh_cwb_t cwb = new_cwb(ctx);
		knh_printf(ctx, cwb.w, emsg, i, DP(mtd)->mn);
		String *s = new_String__cwb(ctx, cwb);
		knh_throw(ctx, (Object*)s, knh_Method_file(ctx, sfp[-1].mtd), knh_Method_pctoline(sfp[-1].mtd, pc));
	}
}

/* ======================================================================== */
/* [macros] */

#define _KNH_THROW(ctx, e) knh_throw(ctx, UP(e), KNH_SAFEFILE(__FILE__), __LINE__)

#define _KNH_THROWs(ctx, s) \
	knh_throwException(ctx, new_Exception__b(ctx, B(s)), KNH_SAFEFILE(__FILE__), __LINE__); \

#define _KNH_THROWf(ctx, fmt, ...) \
	char throcwb_[256]; \
	knh_snprintf(throcwb_, sizeof(throcwb_), fmt, ## __VA_ARGS__); \
	knh_throwException(ctx, new_Exception__b(ctx, B(throcwb_)), KNH_SAFEFILE(__FILE__), __LINE__); \

#define DEBUG_THROWf(ctx, fmt, ...) \
	fprintf(stderr, "THROW?[%s:%d]: ", __FUNCTION__, __LINE__); \
	fprintf(stderr, fmt, ## __VA_ARGS__); \
	fprintf(stderr, "\n"); \

#define _TODO_THROW(ctx) knh_throw_TODO(ctx, (char*)__FILE__, __LINE__, (char*)__FUNCTION__)

/* ======================================================================== */
/* [throw] */

KNHAPI(void) knh_throw_TODO(Ctx *ctx, char *file, int line, char *func)
{
	fprintf(stderr, "**************************************************************************\n");
	fprintf(stderr, "         THIS FUNCTION IS FULLY (OR PARTIALLY) NOT IMPLEMENTED.\n\n");
	fprintf(stderr, "   function: %s\n", func);
	fprintf(stderr, "   file='%s', line=%d\n\n", file, line);
	fprintf(stderr, "We will appliciate if you help us implementing this function. Thank you\n");
	fprintf(stderr, "for your cooperation.\n");
	fprintf(stderr, "**************************************************************************\n");
	knh_throwException(ctx, new_Exception__b(ctx, STEXT("UnsupportedOperation!!")), KNH_SAFEFILE(file), line);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_throw_bugstop(Ctx *ctx, char *file, int line, char *func)
{
	knh_throwException(ctx, new_Exception__b(ctx, STEXT("ReportedBugStop!!")), KNH_SAFEFILE(file), line);
}

/* ======================================================================== */
/* [throw] */

static
void knh_Exception_addStackTrace(Ctx *ctx, Exception *o, String *msg)
{
	KNH_ASSERT(IS_Exception(o));
	if(IS_NOTNULL(msg)) {
		if(IS_NULL(DP(o)->traces)) {
			KNH_SETv(ctx, DP(o)->traces, new_Array(ctx, CLASS_String, 16));
		}
		knh_Array_add(ctx, DP(o)->traces, UP(msg));
	}
}

/* ------------------------------------------------------------------------ */

static
String *knh_stackf_getStackTraceMsg(Ctx *ctx, knh_sfp_t *sfp)
{
	Method *mtd = sfp[-1].mtd;
	knh_code_t *pc = sfp[-1].pc;
	DBG2_P("pc=%p, mtd->func=%p, mtd->pc=%p", pc, mtd->fcall_1, mtd->pc_start);
	char *fn = "-";
	int  line = 0;
	if(pc != NULL && pc != (knh_code_t*)mtd->fcall_1 && pc != mtd->pc_start) {
		fn = knh_Method_file(ctx, mtd);
		line = knh_Method_pctoline(mtd, pc);
	}
	knh_cwb_t cwb = new_cwb(ctx);
	knh_write_cid(ctx, cwb.w, DP(mtd)->cid);
	knh_putc(ctx, cwb.w, '.');
	knh_write_mn(ctx, cwb.w, DP(mtd)->mn);
	knh_putc(ctx, cwb.w, ':');
	knh_write_fline(ctx, cwb.w, fn, line);
	return new_String__cwb(ctx, cwb);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_throwException(Ctx *ctx, Exception *e, char *file, int line)
{
	KNH_ASSERT(IS_Exception(e));
	if(file != NULL) {
		DP(e)->file = file;
		DP(e)->line = line;
	}
	knh_sfp_t *sp = ctx->esp;
	while(ctx->stack <= sp) {
		if(IS_ExceptionHandler(sp[0].hdr) && knh_ExceptionHandler_isCatching(sp[0].hdr)) {
			knh_ExceptionHandler_setCatching(sp[0].hdr, 0);
			knh_ExceptionHandler_longjmp(ctx, sp[0].hdr, e);
		}
		else if(IS_Method(sp[0].o)) {
			knh_Exception_addStackTrace(ctx, e, knh_stackf_getStackTraceMsg(ctx, sp+1));
		}
		sp--;
	}

	fprintf(stderr, "********** USE STACKTRACE IN YOUR C/C++ DEBUGGER ************\n");
	fprintf(stderr, "Uncaught Exception: %s\n", knh_String_tochar(DP(e)->message));
	fprintf(stderr, "*************************************************************\n");
	abort();
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_throw__s(Ctx *ctx, char *msg, char *file, int line)
{
	knh_throwException(ctx, new_Exception__b(ctx, B(msg)), file, line);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_throw(Ctx *ctx, Object *e, char *file, int line)
{
	if(IS_NULL(e)) {
		knh_throwException(ctx, new_Exception__Nue(ctx, e), file, line);
	}else if(IS_Exception(e)) {
		knh_throwException(ctx, (Exception*)e, file, line);
	}else if(IS_bString(e)) {
		knh_throwException(ctx, new_Exception(ctx, (String*)e), file, line);
	}else {
		DBG2_P("Cannot throw %s", CLASSN(knh_Object_cid(e)));
		knh_throwException(ctx, new_Exception__b(ctx, STEXT("Type!!")), file, line);
	}
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_throwSecurityException(void)
{
	Ctx *ctx = konoha_getCurrentContext();
	knh_throwException(ctx, new_Exception(ctx, TS_SecurityException), NULL, 0);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
