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

#define _KNH_THROW(ctx, e) \
	if(IS_NULL(e)) { \
		knh_konohavm_throwException(ctx, new_Exception__Nue(ctx, (Nue*)e)); \
	}else if(IS_Exception(e)) { \
		knh_konohavm_throwException(ctx, (Exception*)e); \
	}else if(IS_String(e)) { \
		knh_konohavm_throwException(ctx, new_Exception(ctx, (String*)e)); \
	}else { \
		DEBUG("Cannot throw %s", CLASSN(knh_Object_cid(e))); \
	} \

#define _KNH_THROWs(ctx, s) \
	knh_konohavm_throwException(ctx, new_Exception__b(ctx, B(s))); \

#define _KNH_THROWf(ctx, fmt, ...) \
	char throwbuf_[256]; \
	snprintf(throwbuf_, sizeof(throwbuf_), fmt, ## __VA_ARGS__); \
	knh_konohavm_throwException(ctx, new_Exception__b(ctx, B(throwbuf_))); \

#define DEBUG_THROWf(ctx, fmt, ...) \
	fprintf(stderr, "THROW?[%s:%d]: ", __func__, __LINE__); \
	fprintf(stderr, fmt, ## __VA_ARGS__); \
	fprintf(stderr, "\n"); \

/* ======================================================================== */
/* [throw] */


void knh_konohavm_throwException(Ctx *ctx, Exception *e)
{
	DEBUG_ASSERT(IS_Exception(e));
	if(ctx == NULL || !IS_Context(ctx)) {
		TODO();
		return ;
	}
	
	Context *b = (Context*)ctx; 
	while(b->stack <= b->ebp) {
//		fprintf(stderr, "stack[%d]\t %d:%s\n", 
//			(b->ebp - b->stack), (int)b->line[(b->ebp - b->stack)], CLASSNo(b->ebp[0]));
		if(IS_ExceptionHandler(b->ebp[0])) {
			knh_ExceptionHandler_longjmp(ctx, b->ebp[0], e);
		}
		else if(IS_Method(b->ebp[0])) {
			knh_Exception_addStackTrace(ctx, e, knh_stackf_getStackTraceMsg(ctx, b->ebp+1));
		}
		b->ebp--;
	}
#ifdef KONOHA_SAFEMODE
	fprintf(stderr, "Uncaught Exception: %s\n", knh_String_tochar(e->message));
	TODO(); //TOGCv(ctx, b->ebp[1], e); 
//	knh_print(ctx, StdErr, STEXT("Exception uncaught:"));
//	knh_Exception_dump(ctx, e, StdErr, 0);
//	knh_println(ctx, StdErr, STEXT(""));
#endif	
}

/* ------------------------------------------------------------------------ */


void knh_Exception_addStackTrace(Ctx *ctx, Exception *b, String *msg)
{
	if(IS_NOTNULL(msg)) {
		if(IS_NULL(b->traces)) {
			KNH_SETv(ctx, b->traces, new_Array(ctx, 16));
		}
		knh_Array_add(ctx, b->traces, msg);
	}
}


/* ------------------------------------------------------------------------ */
/* Catch */


String *knh_stackf_getStackTraceMsg(Ctx *ctx, Object **sf)
{
	DEBUG_ASSERT(IS_Method(sf[-1]));
//	void *pc = ((Context*)ctx)->stackop[(sf - ((Context*)ctx)->ebp)-1];
//	if(pc == NULL) {
//		return;
//	}

	char *fn = "-";
	int  loc = 0;

	Method *mtd = (Method*)sf[-1];
	char bufm[CLASSNAME_BUFSIZ];
	char bufn[CLASSNAME_BUFSIZ*2];
	knh_snprintf(bufn, sizeof(bufn), "%s.%s:(%s:%d)",
		CLASSN(knh_Object_cid(sf[0])), knh_format_methodn(bufm, sizeof(bufm), mtd->mn), fn, loc);
	return new_String__fast(ctx, CLASS_String, B(bufn));
}


#ifdef __cplusplus
}
#endif
