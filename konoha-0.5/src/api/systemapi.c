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
#if !defined(KONOHA_ON_LKM) && !defined(KNH_USING_BTRON)
#include <dirent.h>
#endif

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
/* @method[STATIC] OutputStream! System.getOut() */

static METHOD knh__System_getOut(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, DP(ctx->sys)->out);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] OutputStream! System.getErr() */

static METHOD knh__System_getErr(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, DP(ctx->sys)->err);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] Boolean! System.hasLib(String! lib, String func) */

METHOD knh__System_hasLib(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
	knh_bytes_t libname = knh_String_tobytes(sfp[1].s);
	knh_cwb_write(ctx, cwb, libname);
	knh_cwb_ospath(ctx, cwb);
	void *p = knh_cwb_dlopen(ctx, cwb);
	int res = 0;
	if(p == NULL && !knh_bytes_startsWith(libname, STEXT("lib"))) {
		knh_cwb_subclear(cwb, 0);
		knh_cwb_write(ctx, cwb, STEXT("lib"));
		knh_cwb_write(ctx, cwb, libname);
		p = knh_cwb_dlopen(ctx, cwb);
	}
	if(p != NULL) {
		res = 1;
		if(IS_NOTNULL(sfp[2].o)) {
			void *f = knh_dlsym(ctx, p, p_char(sfp[2]));
			res = (f != NULL);
		}
	}
	knh_cwb_close(cwb);
	KNH_RETURN_Boolean(ctx, sfp, res);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] void System.setRandomSeed(Int seed) */

METHOD knh__System_setRandomSeed(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_uint_t seed = IS_NULL(sfp[1].o) ? 0 : p_uinteger(sfp[1]);
	knh_srand(seed);
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method[STATIC] void System.exit(Int status) @Tricky */

static METHOD knh__System_exit(Ctx *ctx, knh_sfp_t *sfp)
{
#ifdef KNH_USING_STDC
	int status = IS_NULL(sfp[1].o) ? 0 : p_int(sfp[1]);
	KNH_SECURE(ctx, sfp);
	KNH_NOTICE(ctx, "exiting by a user");
	exit(status);
#endif
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method String[] System.listDir(String dirname) */
METHOD knh__System_listDir(Ctx *ctx, knh_sfp_t *sfp)
{
#if defined(KONOHA_USING_POSIX)
	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf)
	Array *a = new_Array(ctx, CLASS_String, 0);
	knh_bytes_t t = (IS_NULL(sfp[1].s)) ? STEXT(".") : knh_String_tobytes(sfp[1].s);
	knh_cwb_write(ctx, cwb, t);
	knh_cwb_ospath(ctx, cwb);
	Array *a = new_Array(ctx, CLASS_String, 0);
	KNH_SETv(ctx, sfp[2].o, a);
	DIR *dirptr;
	if ((dirptr = opendir(dirname)) == NULL) {
		KNH_PERRNO(ctx, cwb, "OS!!", "opendir", knh_Context_isStrict(ctx));
	} else {
		struct dirent *direntp;
		while ((direntp = readdir(dirptr)) != NULL) {
			char *p = direntp->d_name;
			if(p[0] == '.' && (p[1] == 0 || p[1] == '.')) continue;
			knh_Array_add(ctx, a, UP(new_String(ctx, B(p), NULL)));
		}
		closedir(dirptr);
	}
	knh_cwb_close(cwb);
	KNH_RETURN(ctx, sfp, a);
#endif
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! System.hasDir(String! path) */

static METHOD knh__System_hasDir(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_cwb_t cwbbuf, *cwb = knh_cwb_openinit(ctx, &cwbbuf, knh_String_tobytes(sfp[1].s));
	knh_cwb_ospath(ctx, cwb);
	knh_bool_t res = knh_cwb_isdir(ctx, cwb);
	knh_cwb_close(cwb);
	KNH_RETURN_Boolean(ctx,sfp, res);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! System.hasFile(String! path) */

static METHOD knh__System_hasFile(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_cwb_t cwbbuf, *cwb = knh_cwb_openinit(ctx, &cwbbuf, knh_String_tobytes(sfp[1].s));
	knh_cwb_ospath(ctx, cwb);
	knh_bool_t res = knh_cwb_isfile(ctx, cwb);
	knh_cwb_close(cwb);
	KNH_RETURN_Boolean(ctx,sfp, res);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! System.mkdir(String! filename) @Tricky */

static METHOD knh__System_mkdir(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_SECURE(ctx, sfp);
	KNH_RETURN_Boolean(ctx, sfp,
		knh_mkdir(ctx, knh_String_tobytes(sfp[1].s), knh_Context_isStrict(ctx))
	);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! System.unlink(String! filename) @Tricky */

static METHOD knh__System_unlink(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_SECURE(ctx, sfp);
	KNH_RETURN_Boolean(ctx, sfp,
		knh_unlink(ctx, knh_String_tobytes(sfp[1].s), knh_Context_isStrict(ctx))
	);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! System.rename(String oldname, String newname) @Tricky */

static METHOD knh__System_rename(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_SECURE(ctx, sfp);
	KNH_RETURN_Boolean(ctx, sfp,
		knh_rename(ctx, knh_String_tobytes(sfp[1].s), knh_String_tobytes(sfp[2].s), knh_Context_isStrict(ctx))
	);
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
		KNH_SETv(ctx, ((Context*)ctx)->in, knh_getClassDefaultValue(ctx, CLASS_InputStream));
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
		KNH_SETv(ctx, ((Context*)ctx)->out, knh_getClassDefaultValue(ctx, CLASS_OutputStream));
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
		KNH_SETv(ctx, ((Context*)ctx)->err, knh_getClassDefaultValue(ctx, CLASS_OutputStream));
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

	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
	knh_write_char(ctx, cwb->w, "Exception!!");
	if(IS_NOTNULL(sfp[1].o)) {
		knh_write_char(ctx, cwb->w, ": ");
		knh_write(ctx, cwb->w, knh_String_tobytes(sfp[1].s));
	}
	KNH_SETv(ctx, DP(o)->msg, new_String__cwb(ctx, cwb));
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
	knh_write_char(ctx, w, EXPTN(DP(o)->eid));
	knh_write_char(ctx, w, "!!");
}

/* ------------------------------------------------------------------------ */
/* @method void Exception.%k(OutputStream w, String m) */

static
void knh_Exception__k(Ctx *ctx, Exception *o, OutputStream *w, String *m)
{
	KNH_ASSERT(IS_Exception(o));
	knh_putc(ctx, w, '\'');
	knh_write(ctx, w, knh_String_tobytes(DP(o)->msg));
	knh_putc(ctx, w, '\'');
}

/* ------------------------------------------------------------------------ */
/* @method void Exception.%dump(OutputStream w, String m) */

static
void knh_Exception__dump(Ctx *ctx, Exception *o, OutputStream *w, String *m)
{
	DBG2_ASSERT(IS_Exception(o));
	knh_write_EOL(ctx, w);
	if(DP(o)->line != 0) {
		knh_printf(ctx, w, "[%s:%d] ", DP(o)->file, DP(o)->line);
	}
	knh_write(ctx, w, knh_String_tobytes(DP(o)->msg));
	knh_print(ctx, w, STEXT(" Exception"));
	if(IS_bArray(DP(o)->traces)) {
		size_t i, size = knh_Array_size(DP(o)->traces), c = 0;
		knh_bytes_t prev = STEXT("?");
		for(i = 0; i < size; i++) {
			String *s = (String*)knh_Array_n(DP(o)->traces, i);
			if(knh_String_startsWith(s, prev)) {
				c++;
				continue;
			}
			if(c > 0) {
				knh_printf(ctx, w, "\n    ** called %d times recursively **", c);
				c = 0;
			}
			knh_printf(ctx, w, "\n  at %s", knh_String_tochar(s));
			prev = knh_String_tobytes(s);
			prev = knh_bytes_first(prev, knh_bytes_rindex(prev, '('));
		}
	}
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */

#else /*KNH_CC_METHODAPI*/

/* ------------------------------------------------------------------------ */
/* @method void System.%k(OutputStream w, String m) */

void knh_System__k(Ctx *ctx, System *o, OutputStream *w, String *m)
{
	knh_printf(ctx, w, "Konoha %s(%s) %s (#%d, %s %s)",
		KONOHA_VERSION, KONOHA_XCODE, KONOHA_LICENSE,
		((size_t)KONOHA_BUILDID), __DATE__, __TIME__);
}

/* ------------------------------------------------------------------------ */
/* @method void System.%dump(OutputStream w, String m) */

void knh_System__dump(Ctx *ctx, System *o, OutputStream *w, String *m)
{
	knh_System__k(ctx, o, w, m);
	knh_write_EOL(ctx, w);
	knh_printf(ctx, w, "[%s] on %s (%d, %s)\n", KONOHA_CC_VERSION, KONOHA_PLATFORM, (knh_intptr_t)(sizeof(void*) * 8), konoha_encoding());
	knh_write_char(ctx, w, "Options:");

#ifdef KNH_FASTMODE
	knh_write_char(ctx, w, " fastmode");
#endif

#ifdef KNH_USING_ICONV
	knh_write_char(ctx, w, " iconv");
#endif
#ifdef KNH_USING_INT32
	knh_write_char(ctx, w, " int32");
#endif
#ifdef KNH_USING_RCGC
	knh_write_char(ctx, w, " refc");
#endif
	knh_write_USING_SQLITE3(ctx, w);
#ifdef KNH_USING_THREAD
	knh_write_char(ctx, w, " thread");
#endif
	knh_write_USING_REGEX(ctx, w);
	knh_printf(ctx, w, " used_memory:%d kb", (knh_intptr_t)(ctx->stat->usedMemorySize / 1024));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */
/* @method void Context.setEncoding(String enc) */

void knh_Context_setEncoding(Ctx *ctx, knh_Context_t *o, String *enc)
{
	if(IS_NULL(enc)) {
		enc = KNH_ENC;
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
