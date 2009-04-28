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

#ifdef KNH_CC_METHODAPI

/* ======================================================================== */
/* [method] */

/* ------------------------------------------------------------------------ */
/* @method[STATIC] InputStream! System.getIn() */

static METHOD knh__System_getIn(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, DP(ctx->sys)->in);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] void System.setIn(InputStream in) */

static METHOD knh__System_setIn(Ctx *ctx, knh_sfp_t *sfp)
{
	if(knh_Context_isAdmin(ctx)) {
		if(IS_NULL(sfp[1].o)) {
			KNH_SETv(ctx, DP(ctx->sys)->in, konoha_getClassDefaultValue(ctx, CLASS_InputStream));
		}
		else {
			KNH_SETv(ctx, DP(ctx->sys)->in, sfp[1].o);
		}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] OutputStream! System.getOut() */

static METHOD knh__System_getOut(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, DP(ctx->sys)->out);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] void System.setOut(OutputStream out) */

static METHOD knh__System_setOut(Ctx *ctx, knh_sfp_t *sfp)
{
	if(knh_Context_isAdmin(ctx)) {
		if(IS_NULL(sfp[1].o)) {
			KNH_SETv(ctx, DP(ctx->sys)->out, konoha_getClassDefaultValue(ctx, CLASS_OutputStream));
		}
		else {
			KNH_SETv(ctx, DP(ctx->sys)->out, sfp[1].o);
		}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] OutputStream! System.getErr() */

static METHOD knh__System_getErr(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, DP(ctx->sys)->err);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] void System.setStdErr(OutputStream out) */

static METHOD knh__System_setErr(Ctx *ctx, knh_sfp_t *sfp)
{
	if(knh_Context_isAdmin(ctx)) {
		if(IS_NULL(sfp[1].o)) {
			KNH_SETv(ctx, DP(ctx->sys)->err, konoha_getClassDefaultValue(ctx, CLASS_OutputStream));
		}
		else {
			KNH_SETv(ctx, DP(ctx->sys)->err, sfp[1].o);
		}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] void System.exit(Int status) */

static METHOD knh__System_exit(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_intptr_t status = IS_NULL(sfp[1].o) ? 0 : p_int(sfp[1]);
	KNH_SECURE(ctx);
	KNH_NOTICE(ctx, "exiting by a user");
	exit((int)status);
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! System.hasDir(String! path) */

static METHOD knh__System_hasDir(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx,sfp, knh_isdir(ctx, knh_String_tobytes(sfp[1].s)));
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! System.hasFile(String! path) */

static METHOD knh__System_hasFile(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx,sfp, knh_isfile(ctx, knh_String_tobytes(sfp[1].s)));
}


/* ======================================================================== */
/* [Context] */

/* ------------------------------------------------------------------------ */
/* @method Any Context.getProperty(String! key) */

Object* knh_Context_getProperty(Ctx *ctx, Context *b, knh_bytes_t key)
{
	Object *v = knh_DictMap_get__b(ctx,  b->props, key);
	if(IS_NULL(v)) {
		return knh_System_getProperty(ctx, ctx->sys, key);
	}
	return v;
}

/* ------------------------------------------------------------------------ */
/* @method void Context.setProperty(String! key, Any value) */

void knh_Context_setProperty(Ctx *ctx, Context *b, String *key, Any *value)
{
	knh_DictMap_set(ctx, b->props, key, value);
}

/* ------------------------------------------------------------------------ */
/* @method String[]! Context.listProperties(String key) */

static METHOD knh__Context_listProperties(Ctx *ctx, knh_sfp_t *sfp)
{
	DictSet *ds = new_DictSet(ctx, 64);
	KNH_MOV(ctx, sfp[0].o, ds); // TO RCGC
	if(IS_NULL(sfp[1].s)) {
		KNH_MOV(ctx, sfp[1].o, TS_EMPTY);
	}
	DictMap *map = DP(ctx->sys)->props;
	size_t i;
	for(i = 0; i < map->size; i++) {
		if(IS_NOTNULL(knh_DictMap_valueAt(map, i))) {
			String *key = knh_DictMap_keyAt(map, i);
			if(knh_String_startsWith(key, knh_String_tobytes(sfp[1].s))) {
				knh_DictSet_add(ctx, ds, key);
			}
		}
	}
	map = ctx->props;
	for(i = 0; i < map->size; i++) {
		if(IS_NOTNULL(knh_DictMap_valueAt(map, i))) {
			String *key = knh_DictMap_keyAt(map, i);
			if(knh_String_startsWith(key, knh_String_tobytes(sfp[1].s))) {
				knh_DictSet_add(ctx, ds, key);
			}
		}
	}
	Array *a = new_Array(ctx, CLASS_String, ds->size);
	for(i = 0; i < ds->size; i++) {
		knh_Array_add(ctx, a, UP(knh_DictSet_keyAt(ds, i)));
	}
	KNH_RETURN(ctx, sfp, a);
}


/* ------------------------------------------------------------------------ */
/* @method void Context.setIn(InputStream in) */

static METHOD knh__Context_setIn(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_ASSERT(ctx == (Ctx*)sfp[0].o);
	if(IS_NULL(sfp[1].o)) {
		KNH_SETv(ctx, ((Context*)ctx)->in, konoha_getClassDefaultValue(ctx, CLASS_InputStream));
	}
	else {
		KNH_SETv(ctx, ((Context*)ctx)->in, sfp[1].o);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void Context.setOut(OutputStream in) */

static METHOD knh__Context_setOut(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_ASSERT(ctx == (Ctx*)sfp[0].o);
	if(IS_NULL(sfp[1].o)) {
		KNH_SETv(ctx, ((Context*)ctx)->out, konoha_getClassDefaultValue(ctx, CLASS_OutputStream));
	}
	else {
		KNH_SETv(ctx, ((Context*)ctx)->out, sfp[1].o);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void Context.setErr(OutputStream out) */

static METHOD knh__Context_setErr(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_ASSERT(ctx == (Ctx*)sfp[0].o);
	if(IS_NULL(sfp[1].o)) {
		KNH_SETv(ctx, ((Context*)ctx)->err, konoha_getClassDefaultValue(ctx, CLASS_OutputStream));
	}
	else {
		KNH_SETv(ctx, ((Context*)ctx)->err, sfp[1].o);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ======================================================================== */
/* [movabletext] */

/* @method void Context.%dump(OutputStream w, String m) */

static
void knh_Context__dump(Ctx *ctx, Context *b, OutputStream *w, String *m)
{
//	knh_int_t i = 0;
//	for(i = b->esp - b->stack; i >= 0; i--) {
//		knh_printf(ctx, w, "[%d]\t%o\n", i, b->stack[i]);
//	}
}

/* ------------------------------------------------------------------------ */
/* @method Exception! Exception.new(String msg, Any bag) */

static METHOD knh__Exception_new(Ctx *ctx, knh_sfp_t *sfp)
{
	Exception *o = sfp[0].e;
	DP(o)->eid  = EXPT_Exception;
	DP(o)->flag = ctx->share->ExptTable[EXPT_Exception].flag;

	knh_cwb_t cwb = new_cwb(ctx);
	knh_write__s(ctx, cwb.w, "Exception!!");
	if(IS_NOTNULL(sfp[1].o)) {
		knh_write__s(ctx, cwb.w, ": ");
		knh_write(ctx, cwb.w, knh_String_tobytes(sfp[1].s));
	}
	KNH_SETv(ctx, DP(o)->message, new_String__cwb(ctx, cwb));
	KNH_SETv(ctx, DP(o)->bag, sfp[2].o);
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Exception.opIsa(String! m) */

static METHOD knh__Exception_opIsa(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Exception_isa(ctx, sfp[0].e, sfp[1].s));
}


/* ------------------------------------------------------------------------ */
/* @method void Exception.%s(OutputStream w, String m) */

static
void knh_Exception__s(Ctx *ctx, Exception *o, OutputStream *w, String *m)
{
	KNH_ASSERT(IS_Exception(o));
	knh_write__s(ctx, w, EXPTN(DP(o)->eid));
	knh_write__s(ctx, w, "!!");
}

/* ------------------------------------------------------------------------ */
/* @method void Exception.%k(OutputStream w, String m) */

static
void knh_Exception__k(Ctx *ctx, Exception *o, OutputStream *w, String *m)
{
	KNH_ASSERT(IS_Exception(o));
	knh_putc(ctx, w, '\'');
	knh_write(ctx, w, knh_String_tobytes(DP(o)->message));
	knh_putc(ctx, w, '\'');
}

/* ------------------------------------------------------------------------ */
/* @method void Exception.%dump(OutputStream w, String m) */

static
void knh_Exception__dump(Ctx *ctx, Exception *o, OutputStream *w, String *m)
{
	KNH_ASSERT(IS_Exception(o));
	knh_write__s(ctx, w, "---- ---- 8< 8< ---- ---- >8 >8 ---- ----");
	knh_println(ctx, w, STEXT(""));
	if(DP(o)->line != 0) {
		knh_printf(ctx, w, "[%s:%d] ", DP(o)->file, DP(o)->line);
	}
	knh_write(ctx, w, knh_String_tobytes(DP(o)->message));
	knh_println(ctx, w, STEXT(""));
	if(IS_Array(DP(o)->traces)) {
		size_t i;
		for(i = 0; i < knh_Array_size(DP(o)->traces); i++) {
			knh_write(ctx, w, STEXT("  at "));
			knh_format(ctx, w, METHODN__s, knh_Array_n(DP(o)->traces, i), KNH_NULL);
			knh_println(ctx, w, STEXT(""));
		}
	}
	knh_write__s(ctx, w, "---- ---- 8< 8< ---- ---- >8 >8 ---- ----");
	knh_println(ctx, w, STEXT(""));
}

/* ------------------------------------------------------------------------ */

#else /*KNH_CC_METHODAPI*/

/* ------------------------------------------------------------------------ */
/* @method void System.%k(OutputStream w, String m) */

void knh_System__k(Ctx *ctx, System *o, OutputStream *w, String *m)
{
	char *_PREVIEW_ = (KONOHA_BUILDID % 2 == 1) ? " _PREVIEW_" : "";
#ifdef KONOHA_UNDER_GPL2
	knh_printf(ctx, w, "Konoha %s%s GPL2 (#%d, %s, %s)", KONOHA_VERSION, _PREVIEW_, KONOHA_BUILDID, __DATE__, __TIME__);
#else
	knh_printf(ctx, w, "Konoha %s%s (#%d, %s, %s)" TERM_INIT, KONOHA_VERSION, _PREVIEW_, KONOHA_BUILDID, __DATE__, __TIME__);
#endif
}


/* ------------------------------------------------------------------------ */
/* @method void System.%dump(OutputStream w, String m) */

void knh_System__dump(Ctx *ctx, System *o, OutputStream *w, String *m)
{
	knh_System__k(ctx, o, w, m);
	knh_write_EOL(ctx, w);
	knh_printf(ctx, w, "[%s] on %s (%d, %s, %s)\n", KONOHA_CC_VERSION, KONOHA_PLATFORM,
			sizeof(void*) * 8, konoha_encoding(), knh_message_text(KMSG_LANG));
	knh_write__s(ctx, w, "Options:");

#ifdef KNH_FASTMODE
	knh_write__s(ctx, w, " fastmode");
#endif

#ifdef KNH_USING_ICONV
	knh_write__s(ctx, w, " iconv");
#endif
#ifdef KNH_USING_INT32
	knh_write__s(ctx, w, " int32");
#endif
#ifdef KNH_USING_MATH
	knh_write__s(ctx, w, " math");
#endif
	knh_write_USING_SQLITE3(ctx, w);
#ifdef KNH_USING_THREAD
	knh_write__s(ctx, w, " thread");
#endif
	knh_write_USING_REGEX(ctx, w);
	knh_printf(ctx, w, " used_memory:%d kb", (int)ctx->stat->usedMemorySize / 1024);
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */
/* @method void Context.setEncoding(String enc) */

void knh_Context_setEncoding(Ctx *ctx, knh_Context_t *o, String *enc)
{
	if(IS_NULL(enc)) {
		enc = knh_systemEncoding;
	}
	KNH_SETv(ctx, o->enc, enc);
	if(knh_bytes_strcasecmp(knh_String_tobytes(enc), STEXT(KONOHA_ENCODING))==0) {
		KNH_SETv(ctx, DP(o->in)->bconv, KNH_NULL);
		KNH_SETv(ctx, DP(o->out)->bconv, KNH_NULL);
		KNH_SETv(ctx, DP(o->err)->bconv, KNH_NULL);
	}
	else {
		BytesConv *bin = new_BytesConv__in(ctx, knh_String_tochar(enc));
		BytesConv *bout = new_BytesConv__out(ctx, knh_String_tochar(enc));
		if(IS_NULL(bin) || IS_NULL(bout)) {
			KNH_WARNING(ctx, "unsupported character encoding: %s", knh_String_tochar(enc));
		}
		KNH_SETv(ctx, DP(o->in)->bconv, bin);
		KNH_SETv(ctx, DP(o->out)->bconv, bout);
		KNH_SETv(ctx, DP(o->err)->bconv, bout);
	}
}

/* ------------------------------------------------------------------------ */

#endif/*KNH_CC_METHODAPI*/

#ifdef __cplusplus
}
#endif
