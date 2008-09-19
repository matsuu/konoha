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
/* [macros] */

#define _KNH_THROW(ctx, e) knh_throw(ctx, e)

#define _KNH_THROWs(ctx, s) \
	knh_throwException(ctx, new_Exception__b(ctx, B(s))); \

#define _KNH_THROWf(ctx, fmt, ...) \
	char throwbuf_[256]; \
	knh_snprintf(throwbuf_, sizeof(throwbuf_), fmt, ## __VA_ARGS__); \
	knh_throwException(ctx, new_Exception__b(ctx, B(throwbuf_))); \

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
	knh_throwException(ctx, new_Exception__b(ctx, STEXT("UnsupportedOperation!!")));
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
	KNH_ASSERT(IS_Method(sfp[-1].mtd));
	{
		char *fn = "-";
		int  loc = 0;
		char bufm[CLASSNAME_BUFSIZ];
		char bufn[CLASSNAME_BUFSIZ*2];
		knh_snprintf(bufn, sizeof(bufn), "%s.%s:(%s:%d)",
			CLASSN(knh_Object_cid(sfp[0].o)), knh_format_methodn(bufm, sizeof(bufm), DP(sfp[-1].mtd)->mn), fn, loc);
		return new_String(ctx, B(bufn), NULL);
	}
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_throwException(Ctx *ctx, Exception *e)
{
	KNH_ASSERT(IS_Exception(e));
	{
		Context *o = (Context*)ctx;
		if(ctx == NULL || !IS_Context(ctx)) {
			TODO();
			return ;
		}

		while(o->stack <= o->ebp) {
	//		fprintf(stderr, "stack[%d]\t %d:%s\n",
	//			(b->ebp - b->stack), (int)b->line[(b->ebp - b->stack)], CLASSNo(b->ebp[0]));
			if(IS_ExceptionHandler(o->ebp[0].o)) {
				knh_ExceptionHandler_longjmp(ctx, o->ebp[0].hdr, e);
			}
			else if(IS_Method(o->ebp[0].o)) {
				knh_Exception_addStackTrace(ctx, e, knh_stackf_getStackTraceMsg(ctx, o->ebp+1));
			}
			o->ebp--;
		}
	}
#ifdef KONOHA_SAFEMODE
	fprintf(stderr, "Uncaught Exception: %s\n", knh_String_tochar(DP(e)->message));
	TODO(); //TOGCv(ctx, b->ebp[1], e);
//	knh_print(ctx, StdErr, STEXT("Exception uncaught:"));
//	knh_Exception_dump(ctx, e, StdErr, 0);
//	knh_println(ctx, StdErr, STEXT(""));
#endif
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_throw(Ctx *ctx, Object *e)
{
	if(IS_NULL(e)) {
		knh_throwException(ctx, new_Exception__Nue(ctx, (Nue*)e));
	}else if(IS_Exception(e)) {
		knh_throwException(ctx, (Exception*)e);
	}else if(IS_bString(e)) {
		knh_throwException(ctx, new_Exception(ctx, (String*)e));
	}else {
		DBG2_P("Cannot throw %s", CLASSN(knh_Object_cid(e)));
		knh_throwException(ctx, new_Exception__b(ctx, STEXT("INTERNAL!!")));
	}
}


/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
