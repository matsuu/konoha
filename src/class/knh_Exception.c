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
#include<linux/errno.h>
static int errno;
#else

#ifdef KNH_USING_POSIX
#include<errno.h>
#else
static int errno;
#endif
#endif

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [macros] */

#define _EXPT_unknown  ((knh_expt_t)-1)
#define _EXPT_newid    ((knh_expt_t)0)

#ifndef EXPT_Exception
#define EXPT_Exception 1
#endif

/* ======================================================================== */
/* [ExptTable] */

static
knh_expt_t knh_ExptTable_newId(Ctx *ctx)
{
	knh_class_t newid;
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	if(!(ctx->share->ExptTableSize < KNH_TEXPT_SIZE)) {
		KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
		KNH_EXIT("Enlarge KNH_TEXPT_SIZE %d", KNH_TEXPT_SIZE);
		return 0;
	}
	newid = ctx->share->ExptTableSize;
	ctx->share->ExptTableSize += 1;
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	return newid + 1;
}

#define _KNH_ASSERT_eid(eid)    KNH_ASSERT(eid < ctx->share->ExptTableSize + 1)

/* ------------------------------------------------------------------------ */

static
int knh_ExptTable_isa(Ctx *ctx, knh_expt_t eid, knh_expt_t parent)
{
	KNH_ASSERT_eid(eid);
	KNH_ASSERT(parent < ctx->share->ExptTableSize);
	if(eid == parent || parent == 1) return 1;
	if(eid == 1) return 0;
	while((eid = ctx->share->ExptTable[eid-1].parent) != 1) {
		if(eid == parent) return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

#define _EXPTN(eid)   knh_String_tochar(knh_ExptTable_name(ctx, eid))

String *knh_ExptTable_name(Ctx *ctx, knh_expt_t eid)
{
	KNH_ASSERT_eid(eid);
	return ctx->share->ExptTable[eid-1].name;
}

/* ------------------------------------------------------------------------ */
/* [forname] */

static
knh_expt_t knh_texpt_forname(Ctx *ctx, knh_bytes_t msg, knh_expt_t def)
{
	knh_intptr_t loc = knh_bytes_index(msg, '!');
	if(loc != -1) {
		if(msg.buf[loc+1] != '!') {
			return EXPT_Exception;
		}
		msg = knh_bytes_first(msg, loc);
	}

	if(msg.len == 0) return EXPT_Exception; /* '!!' */

	knh_expt_t eid = (knh_expt_t)knh_DictSet_get__b(DP(ctx->sys)->ExptNameDictSet, msg);
	if(eid != 0) return eid;
	if(def == EXPT_newid) {
		return konoha_addException(ctx, KNH_FLAG_EF_GENERATED, EXPT_newid, new_String(ctx, msg, NULL), NULL);
	}
	return def;
}

/* ------------------------------------------------------------------------ */
/* [TABLE] */

knh_expt_t
konoha_addException(Ctx *ctx, knh_flag_t flag, knh_class_t eid, String *name, char *pname)
{
	if(eid == EXPT_newid) {
		eid = knh_ExptTable_newId(ctx);
	}else {
		ctx->share->ExptTableSize += 1;
		KNH_ASSERT(eid == ctx->share->ExptTableSize);
	}

	KNH_ASSERT_eid(eid);

	knh_expt_t parent = EXPT_Exception;
	if(pname != NULL) {
		parent = knh_texpt_forname(ctx, B(pname), parent);
		if(parent == EXPT_Exception) {
			DBG2_P("NoSuchException!!: %s", pname);
		}
	}

	KNH_ASSERT(ctx->share->ExptTable[eid-1].name == NULL);
	ctx->share->ExptTable[eid-1].flag = flag;
	ctx->share->ExptTable[eid-1].parent = parent;
	KNH_INITv(ctx->share->ExptTable[eid-1].name, name);
	knh_DictSet_set(ctx, DP(ctx->sys)->ExptNameDictSet, name, eid);
	//DBG2_P("Generating new Exception eid=%d name='%s'", eid, knh_String_tochar(((Context*)ctx)->ExptTable[eid].name));
	return eid;
}

/* ======================================================================== */
/* [Exception.new] */

/* @method Exception! Exception.new:init(String e, String msg, Object bag) */
// new Exception("Security!!", "hogehoge");
// new Exception("Security!!: hogehoge", null);

Exception* knh_Exception_new__init(Ctx *ctx, Exception *o, String *e, String *msg, Object *bag)
{
	knh_expt_t eid = EXPT_Exception;
	if(IS_NOTNULL(e)) {
		KNH_RCSETv(ctx, DP(o)->bag, e);
		eid = knh_texpt_forname(ctx, knh_String_tobytes(e), EXPT_newid /*EXPT_unknown*/);
	}
	if(eid == EXPT_unknown) {
		KNH_WARNING(ctx, "unknown exception: %s", knh_String_tochar(e));
		DP(o)->eid = EXPT_Exception;
	}
	else {
		DP(o)->eid = eid;
	}
	KNH_ASSERT_eid(eid);
	DP(o)->flag = ctx->share->ExptTable[DP(o)->eid].flag;
	{
		if(IS_NOTNULL(msg)) {
			KNH_RCSETv(ctx, DP(o)->bag, msg);
			knh_cwb_t cwb = new_cwb(ctx);
			knh_write_char(ctx, cwb.w, EXPTN(DP(o)->eid));
			knh_write_char(ctx, cwb.w, "!!: ");
			knh_write(ctx, cwb.w, knh_String_tobytes(msg));
			KNH_SETv(ctx, DP(o)->message, new_String__cwb(ctx, cwb));
		}
		else {
			int loc = knh_bytes_indexOf(knh_String_tobytes(e), STEXT("!!:"));
			if(loc > 0 && eid != EXPT_unknown) {
				KNH_SETv(ctx, DP(o)->message, e);
				return o;
			}
			knh_cwb_t cwb = new_cwb(ctx);
			knh_write_char(ctx, cwb.w, EXPTN(DP(o)->eid));
			knh_write_char(ctx, cwb.w, "!!");
			if(loc > 0) {
				knh_write_char(ctx, cwb.w, ": ");
				knh_write(ctx, cwb.w, knh_bytes_last(knh_String_tobytes(e), loc+3));
			}
			KNH_SETv(ctx, DP(o)->message, new_String__cwb(ctx, cwb));
		}
	}
	KNH_SETv(ctx, DP(o)->bag, bag);
	return o;
}

/* ------------------------------------------------------------------------ */

int knh_Exception_isa(Ctx *ctx, Exception *o, String *msg)
{
	knh_expt_t eid = knh_texpt_forname(ctx, knh_String_tobytes(msg), EXPT_unknown);
	int res = 0;
	DBG2_P("%s(%d) isa? %s(%d)", knh_String_tochar(DP(o)->message), DP(o)->eid, knh_String_tochar(msg), eid);
	if(eid == EXPT_unknown) res = 0;
	res = knh_ExptTable_isa(ctx, DP(o)->eid, eid);
	DBG2_P("res=%d", res);
	return res;
}

/* ------------------------------------------------------------------------ */

KNHAPI(Exception*) new_Exception(Ctx *ctx, String *msg)
{
	knh_Exception_t* o = (knh_Exception_t*)new_Object_bcid(ctx, CLASS_Exception, 0);
	knh_Exception_new__init(ctx, o, msg, (String*)KNH_NULL, (Object*)KNH_NULL);
	return o;
}

/* ------------------------------------------------------------------------ */

KNHAPI(Exception*) new_Exception__b(Ctx *ctx, knh_bytes_t msg)
{
	knh_Exception_t* o = (knh_Exception_t*)new_Object_bcid(ctx, CLASS_Exception, 0);
	knh_Exception_new__init(ctx, o, new_String(ctx, msg, NULL), (String*)KNH_NULL, (Object*)KNH_NULL);
	return o;
}

#define _new_Exception__s(ctx, s)     new_Exception__b(ctx, B(s))

/* ------------------------------------------------------------------------ */

Exception* new_NullException (Ctx *ctx, Object *o)
{
	return new_Exception__b(ctx, STEXT("Null!!"));
}

/* ------------------------------------------------------------------------ */

#define _KNH_PERRNO(ctx, emsg, func, isThrowable) { \
		knh_perrno(ctx, emsg, func, __FILE__, __LINE__, isThrowable); \
	}\

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_perrno(Ctx *ctx, char *emsg, char *func, char *file, int line, int isThrowable)
{
	if(emsg == NULL) emsg = "Exception!!";
	if(errno == 13) {
		emsg = "Security!!";
	}
#ifdef _MSC_VER
	char emsg2[256];
	strerror_s(emsg2, sizeof(emsg2), errno);
#else
	char *emsg2 = strerror(errno);
#endif
	if(isThrowable) {
		char buf[256];
		knh_snprintf(buf, sizeof(buf), "%s: func=%s, errno=%d: %s", emsg, func, errno, emsg2);
		knh_throwException(ctx, new_Exception__b(ctx, B(buf)), KNH_SAFEFILE(file), line);
	}
	else {
		KNH_NOTICE(ctx, "%s() says errno=%d: %s", func, errno, emsg2);
	}
}

/* ------------------------------------------------------------------------ */

#define _KNH_NOAPI(ctx, isThrowable) { \
		knh_throw_Unsupported(ctx, __FUNCTION__, __FILE__, __LINE__, isThrowable); \
	}\

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_throw_Unsupported(Ctx *ctx,const char *func, char *file, int line, int isThrowable)
{
	if(isThrowable) {
		char buf[256];
		knh_snprintf(buf, sizeof(buf), "Unsupported!!: func=%s", func);
		knh_throwException(ctx, new_Exception__b(ctx, B(buf)), KNH_SAFEFILE(file), line);
	}
	else {
		KNH_NOTICE(ctx, "unsupported: %s", func);
	}
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_throw_OutOfIndex(Ctx *ctx, knh_int_t n, size_t max, char *file, int line)
{
	char buf[80];
	knh_snprintf(buf, sizeof(buf), "OutOfIndex!!: %d <%d", (int)n, (int)max);
	knh_throwException(ctx, new_Exception__b(ctx, B(buf)), KNH_SAFEFILE(file), line);
}

#define _KNH_THROW_OUTOFINDEX(ctx, n, max) { \
		knh_throw_OutOfIndex(ctx, n, max, __FILE__, __LINE__); \
	}\

/* ======================================================================== */
/* [ExceptionHandler] */

ExceptionHandler* new_ExceptionHandler(Ctx *ctx)
{
	return (ExceptionHandler*)new_Object_bcid(ctx, CLASS_ExceptionHandler, 0);
}

/* ------------------------------------------------------------------------ */

void knh_ExceptionHandler_longjmp(Ctx *ctx, ExceptionHandler *o, Exception *e)
{
	KNH_ASSERT(IS_Exception(e));
	KNH_SETv(ctx, DP(o)->caught, e);
	longjmp(DP(o)->jmpbuf, DP(e)->eid);
}

/* ------------------------------------------------------------------------ */

Exception* knh_ExceptionHandler_getCaughtException(ExceptionHandler *o)
{
	KNH_ASSERT(IS_Exception(DP(o)->caught));
	return DP(o)->caught;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
