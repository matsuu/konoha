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

#ifdef KNH_USING_READLINE
	#include<readline/readline.h>  /* @using readline -lreadline */
	#include<readline/history.h>
#endif

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [ctxkey] */

static int isInit = 0;

#ifdef KNH_USING_NOTHREAD
static Ctx *curctx = NULL;
#else
static knh_thread_key_t ctxkey;
#endif

/* ------------------------------------------------------------------------ */

void konoha_init(void)
{
#ifndef KNH_USING_NOTHREAD
	if(isInit == 0) {
		isInit = 1;
		knh_thread_key_create(&ctxkey);
	}
#endif
	knh_srand(0);
	isInit = 1;
}

/* ------------------------------------------------------------------------ */
/* [Context] */

KNHAPI(void) knh_beginContext(Ctx *ctx)
{
#ifdef KNH_USING_NOTHREAD
	curctx = ctx;
#else
	knh_mutex_lock(ctx->ctxlock);
	knh_thread_setspecific(ctxkey, ctx);
#endif
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_endContext(Ctx *ctx)
{
#ifdef KNH_USING_NOTHREAD
	curctx = NULL;
#else
	knh_thread_setspecific(ctxkey, NULL);
	knh_mutex_unlock(ctx->ctxlock);
#endif
}

/* ------------------------------------------------------------------------ */

KNHAPI(Ctx*) knh_getCurrentContext(void)
{
	Ctx *ctx;
#ifdef KNH_USING_NOTHREAD
	ctx = curctx;
#else
	ctx = (Ctx*)knh_thread_getspecific(ctxkey);
#endif
	if(ctx == NULL) {
		fprintf(stderr, "NOT IN THE CONTEXT OF KONOHA\n");
		exit(1);
	}
	return ctx;
}

///* ------------------------------------------------------------------------ */
//
//KNHAPI(Ctx*) knh_getThreadContext(Ctx *ctx)
//{
//#ifdef KNH_USING_NOTHREAD
//	curctx = ctx;
//	return ctx;
//#else
//	knh_thread_t thread = knh_thread_self();
//	if(ctx->threadid != thread) {
//		ctx = (Ctx*)knh_thread_getspecific(ctxkey);
//		if(ctx != NULL && ctx->threadid == thread) {
//			return ctx;
//		}
//	}
//	DBG_P("thread inconsitency.. creating new context..");
//	Ctx *newctx = new_Context(ctx);
//	knh_thread_setspecific(ctxkey, newctx);
//	return newctx;
//#endif
//}

/* ======================================================================== */
/* [option] */

static int dumpLevel2 = 0;    // this is -d2 debug mode for konoha itself
static int debugLevel = 0;

/* ----------------------------------------------------------------------- */

KNHAPI(int) konoha_debugLevel(void)
{
	return debugLevel;
}

/* ----------------------------------------------------------------------- */

KNHAPI(int) konoha_isSystemDump2(void)
{
	return (dumpLevel2 == 2);
}

/* ----------------------------------------------------------------------- */

static void konoha_dumpInit(void)
{
	fprintf(stderr, "sizeof(knh_intptr_t)=%d, sizeof(void*)=%d\n", (int)sizeof(knh_intptr_t), (int)sizeof(void*));
	KNH_ASSERT(sizeof(knh_intptr_t) == sizeof(void*));
	fprintf(stderr, "sizeof(knh_int_t)=%d, sizeof(knh_float_t)=%d\n", (int)sizeof(knh_int_t), (int)sizeof(knh_float_t));
	KNH_ASSERT(sizeof(knh_int_t) <= sizeof(knh_float_t));
	fprintf(stderr, "sizeof(knh_sfp_t)=%d, sizeof(Ctx)=%d\n", (int)sizeof(knh_sfp_t), (int)sizeof(knh_Context_t));
	fprintf(stderr, "sizeof(Object)=%d FASTMALLOC=%d\n", (int)sizeof(knh_Object_t), (int)KNH_FASTMALLOC_SIZE);
	fprintf(stderr, "sizeof(Int)=%d, sizeof(Method)=%d\n", (int)sizeof(knh_Int_t), (int)sizeof(knh_Method_struct));
	fprintf(stderr, "sizeof(knh_thread_t)=%d, sizeof(knh_mutex_t)=%d\n", (int)sizeof(knh_thread_t), (int)sizeof(knh_mutex_t));
}

/* ----------------------------------------------------------------------- */

KNHAPI(int) konoha_parseopt(konoha_t konoha, int argc, char **argv)
{
	KONOHA_CHECK(konoha, 1);
	int n;
	for(n = 1; n < argc; n++) {
		char *t = argv[n];
		if(t[0] != '-') return n;
		if(t[1] == 's' && t[2] == 0) {
			knh_Context_setTrusted(konoha.ctx, 1);
		}
		else if(t[1] == 'c' && t[2] == 0) {
			knh_Context_setCompiling(konoha.ctx, 1);
		}
		else if(t[1] == 'v') {
			knh_Context_setVerbose(konoha.ctx, 1);
		}
		else if(t[1] == 'g' && t[2] == 0) {
			debugLevel = 1;
			knh_Context_setDebug(konoha.ctx, 1);
		}
		else if(t[1] == 'g' && t[2] == '2' && t[3] == 0) {
			debugLevel = 2;
			knh_Context_setDebug(konoha.ctx, 1);
		}
		else if(t[1] == 'd' && t[2] == '2' && t[3] == 0) {
			dumpLevel2 = 2;
			konoha_dumpInit();
		}
	}
	return n;
}

/* ======================================================================== */
/* [konoha] */

KNHAPI(int) konoha_hasRuntimeError(konoha_t konoha)
{
	KONOHA_CHECK(konoha, 1);
	Ctx *ctx = konoha.ctx;
	return (ctx->hasError);
}

/* ------------------------------------------------------------------------ */

void knh_setRuntimeError(Ctx *ctx, String *msg)
{
	KNH_SETv(ctx, ((Context*)ctx)->msgError, msg);
	((Context*)ctx)->hasError = 1;
}

/* ------------------------------------------------------------------------ */

KNHAPI(char*) knh_getRuntimeError(konoha_t konoha)
{
	KONOHA_CHECK(konoha, "This isn't an konoha instance");
	Ctx *ctx = konoha.ctx;
	if(ctx->hasError && IS_bString(ctx->msgError)) {
		return knh_String_text(ctx, ctx->msgError);
	}
	return "";
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_setOutputStreamBuffer(konoha_t konoha, size_t osize, size_t esize)
{
	KONOHA_CHECK_(konoha);
	Ctx *ctx = konoha.ctx;
	if(osize > 0) {
		KNH_SETv(ctx, ((Context*)ctx)->out, new_BytesOutputStream(ctx, new_Bytes(ctx, osize)));
	}
	else {
		KNH_SETv(ctx, ((Context*)ctx)->out, KNH_DEF(ctx, CLASS_OutputStream));
	}
	if(esize > 0) {
		KNH_SETv(ctx, ((Context*)ctx)->err, new_BytesOutputStream(ctx, new_Bytes(ctx, esize)));
	}
	else {
		KNH_SETv(ctx, ((Context*)ctx)->err, KNH_DEF(ctx, CLASS_OutputStream));
	}
}

/* ------------------------------------------------------------------------ */

KNHAPI(char*) knh_getSTDOUTBuffer(konoha_t konoha)
{
	KONOHA_CHECK(konoha, "");
	Ctx *ctx = konoha.ctx;
	OutputStream *out = ((Context*)ctx)->out;
	knh_OutputStream_flush(ctx, out);
	if(IS_Bytes(DP(out)->ba)) {
		Bytes *ba = DP(out)->ba;
		DBG_P("malloc(%ld)", ba->size + 1);
		char *p = (char*)malloc(ba->size + 1);
		if(p != NULL) {
			knh_memcpy(p, ba->buf, ba->size);
			p[ba->size] = 0;
			return p;
		}
	}
	return "";
}

/* ------------------------------------------------------------------------ */

KNHAPI(char*) knh_getSTDERRBuffer(konoha_t konoha)
{
	KONOHA_CHECK(konoha, "");
	Ctx *ctx = konoha.ctx;
	OutputStream *out = ((Context*)ctx)->err;
	knh_OutputStream_flush(ctx, out);
	if(IS_Bytes(DP(out)->ba)) {
		Bytes *ba = DP(out)->ba;
		DBG_P("malloc(%ld)", ba->size + 1);
		char *p = (char*)malloc(ba->size + 1);
		if(p != NULL) {
			knh_memcpy(p, ba->buf, ba->size);
			p[ba->size] = 0;
			return p;
		}
	}
	return "";
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_evalScript(konoha_t konoha, char *script)
{
	KONOHA_CHECK_(konoha);
	Ctx *ctx = konoha.ctx;
	knh_beginContext(ctx);
	{
		knh_sfp_t *lsfp = KNH_LOCAL(ctx);
		knh_cwb_t cwb = new_cwb(ctx);
		knh_Bytes_write(ctx, cwb.ba, B(script));
		knh_Bytes_putc(ctx, cwb.ba, ';');
		knh_Bytes_putc(ctx, cwb.ba, '\n');
		{
			InputStream *in = new_BytesInputStream(ctx, cwb.ba, cwb.pos, knh_Bytes_size(cwb.ba));
			KNH_LPUSH(ctx, in);
			DP(in)->resid = knh_getResourceId(ctx, STEXT("(eval)"));
			DP(in)->line = 0;
			konohac_eval(ctx, TS_main, in);
		}
		knh_cwb_clear(cwb);
		KNH_LOCALBACK(ctx, lsfp);
	}
	knh_endContext(ctx);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_readFile(Ctx *ctx, char *fpath)
{
	if(!knh_isfile(ctx, B(fpath))) {
		KNH_WARNING(ctx, "No such file: %s\n", fpath);

		return ;
	}
	InputStream *in = new_FileInputStream(ctx, B(fpath), 1);
	if(knh_InputStream_isClosed(in)) {
		KNH_WARNING(ctx, "No such script file: %s\n", fpath);
	}
	DP(in)->resid = knh_getResourceId(ctx, B(fpath));
	knh_InputStream_setEncoding(ctx, in, KNH_ENC);
	konohac_eval(ctx, (String*)KNH_NULL, in);
	knh_Context_clearstack(ctx);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_loadScript(konoha_t konoha, char *fpath)
{
	KONOHA_CHECK_(konoha);
	knh_beginContext(konoha.ctx);
	{
		konoha_readFile(konoha.ctx, fpath);
	}
	knh_endContext(konoha.ctx);
}

/* ------------------------------------------------------------------------ */

KNHAPI(int) konoha_runMain(konoha_t konoha, int argc, char **argv)
{
	KONOHA_CHECK(konoha, -1);
	Ctx *ctx = konoha.ctx;
	knh_beginContext(ctx);
	knh_sfp_t *lsfp = KNH_LOCAL(ctx);
	KNH_MOV(ctx, lsfp[0].o, new_ExceptionHandler(ctx));
	KNH_TRY(ctx, L_CATCH, lsfp, 0);
	{
		NameSpace *ns = ctx->share->mainns;
		Script *scr = knh_NameSpace_getScript(ctx, ns);
		Method *mtd = knh_Class_getMethod(ctx, knh_Object_cid(scr), METHODN_main);

		if(IS_NULL(mtd)) {
			goto L_END_TRY;
		}
		if(knh_Method_psize(mtd) == 1) {
			knh_type_t ptype = knh_Method_pztype(mtd, 0);
			if(ptype != ATYPE_String && ptype != NNATYPE_String) {
				knh_setRuntimeError(ctx, T("Type!!: main()"));
				goto L_END_TRY;
			}
			else {
				Array *a = new_Array(ctx, CLASS_String, argc);
				int i;
				for(i = 0; i < argc; i++) {
					knh_Array_add(ctx, a, UP(new_String__T(ctx, argv[i])));
				}
				//KNH_MOV(ctx, lsfp[1].o, mtd);
				KNH_MOV(ctx, lsfp[2].o, scr);
				KNH_MOV(ctx, lsfp[3].o, a);
				KNH_SCALL(ctx, lsfp, 1, mtd, /* args*/ 1);
			}
		}
		else {
			knh_setRuntimeError(ctx, T("Type!!: main()"));
			goto L_END_TRY;
		}
	}
	L_END_TRY:
	knh_Context_clearstack(ctx);
	knh_endContext(ctx);
	return (ctx->hasError == 0 ? -1 : 0);

	/* catch */
	L_CATCH:;
	KNH_PRINT_STACKTRACE(ctx, lsfp, 0);
	knh_endContext(ctx);
	return (ctx->hasError == 0 ? -1 : 0);
}

/* ------------------------------------------------------------------------ */

static
knh_sfp_t *konoha_vinvokeScriptFunc(konoha_t konoha, char *fmt, va_list args)
{
	KONOHA_CHECK(konoha, 0);
	Ctx *ctx = konoha.ctx;
	knh_bytes_t fname = B(fmt);
	knh_index_t loc = knh_bytes_index(fname, '(');
	if(loc > 0) {
		fname = knh_bytes_first(fname, loc);
		fmt = fmt + loc + 1;
	}
	knh_beginContext(ctx);
	{
		knh_sfp_t *lsfp = KNH_LOCAL(ctx);
		KNH_MOV(ctx, lsfp[0].o, new_ExceptionHandler(ctx));
		KNH_TRY(ctx, L_CATCH, lsfp, 0);
		{
			knh_methodn_t mn = knh_getmn(ctx, fname, METHODN_NONAME);
			NameSpace *ns = ctx->share->mainns;
			Script *scr = knh_NameSpace_getScript(ctx, ns);
			Method *mtd = konoha_lookupMethod(ctx, knh_Object_cid(scr), mn);
			int n = knh_stack_vpush(ctx, lsfp + 1, fmt, args);
			KNH_MOV(ctx, lsfp[2].o, scr);
			KNH_SCALL(ctx, lsfp, 1, mtd, /* args*/ n);
		}
		knh_Context_clearstack(ctx);
		((Context*)ctx)->hasError = 0;
		knh_endContext(ctx);
		return lsfp + 1;

		/* catch */
		L_CATCH:;
		KNH_PRINT_STACKTRACE(ctx, lsfp, 0);
		knh_endContext(ctx);
		return lsfp + 1;
	}
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_invokeScriptFunc(konoha_t konoha, char *fmt, ...)
{
	va_list args;
	va_start(args , fmt);
	konoha_vinvokeScriptFunc(konoha, fmt, args);
	va_end(args);
}

/* ------------------------------------------------------------------------ */

KNHAPI(knh_int_t) konoha_invokeIntFunc(konoha_t konoha, char *fmt, ...)
{
	knh_sfp_t *lsfp;
	va_list args;
	va_start(args , fmt);
	lsfp = konoha_vinvokeScriptFunc(konoha, fmt, args);
	va_end(args);
	return lsfp[0].ivalue;
}

/* ------------------------------------------------------------------------ */

KNHAPI(knh_float_t) konoha_invokeFloatFunc(konoha_t konoha, char *fmt, ...)
{
	knh_sfp_t *lsfp;
	va_list args;
	va_start(args , fmt);
	lsfp = konoha_vinvokeScriptFunc(konoha, fmt, args);
	va_end(args);
	return lsfp[0].fvalue;
}

/* ------------------------------------------------------------------------ */

KNHAPI(int) konoha_invokeBooleanFunc(konoha_t konoha, char *fmt, ...)
{
	knh_sfp_t *lsfp;
	va_list args;
	va_start(args , fmt);
	lsfp = konoha_vinvokeScriptFunc(konoha, fmt, args);
	va_end(args);
	return lsfp[0].bvalue;
}

/* ------------------------------------------------------------------------ */

KNHAPI(char*) konoha_invokeStringFunc(konoha_t konoha, char *fmt, ...)
{
	knh_sfp_t *lsfp;
	va_list args;
	va_start(args , fmt);
	lsfp = konoha_vinvokeScriptFunc(konoha, fmt, args);
	va_end(args);
	{
		Ctx *ctx = konoha.ctx;
		if(ctx->hasError == 0 && IS_String(lsfp[0].o)) {
			String *s = lsfp[0].s;
			char *p = (char*)malloc(s->size+1);
			if(p == NULL) {
				knh_setRuntimeError(ctx, T("out of memory"));
			}
			else {
				knh_memcpy(p, s->str, s->size);
				p[s->size] = 0;
			}
			return p;
		}
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

KNHAPI(int) konoha_addMethodFunc(konoha_t konoha, char *name, knh_fmethod func)
{
	KONOHA_CHECK(konoha, -1);
	Ctx *ctx = konoha.ctx;
	NameSpace *ns = ctx->share->mainns;
	knh_class_t cid; knh_methodn_t mn;
	knh_bytes_t n = B(name);
	knh_index_t loc = knh_bytes_rindex(n, '.');
	if(loc == -1) {
		cid = knh_Object_cid(knh_NameSpace_getScript(ctx, ns));
	}
	else {
		cid = knh_NameSpace_getcid(ctx, ns, knh_bytes_first(n, loc));
		if(cid == CLASS_unknown) {
			cid = knh_getcid(ctx, knh_bytes_first(n, loc));
			if(cid == CLASS_unknown) {
				goto L_ERROR;
			}
		}
		n = knh_bytes_last(n, loc+1);
	}
	mn = knh_getmn(ctx, n, METHODN_NONAME);
	{
		Method *mtd = knh_Class_getMethod(ctx, cid, mn);
		if(IS_NULL(mtd)) {
			goto L_ERROR;
		}
		knh_Method_syncFunc(mtd, func);
	}
	return 0;

	L_ERROR:
	knh_setRuntimeError(ctx, T("method not found"));
	return -1;
}

/* ======================================================================== */
/* [readline] */

static
char *knh_readline(char *prompt)
{
	char *ln = NULL;
#if defined(KNH_USING_READLINE)
	ln = readline(prompt);
	if(ln != NULL && *ln) add_history(ln);
	return ln;
#else
	char bufl[1024];
	int pos = 0, ch;
	fputs(prompt, stdout);
	while((ch = fgetc(stdin)) != EOF) {
		if(ch == '\r') continue;
		if(ch == '\n') break;
		bufl[pos] = ch;
		pos++;
		if(pos < sizeof(bufl)) {
			continue;
		}
		else {
			bufl[pos-1] = 0;
		}
	}
	KNH_ASSERT(pos < sizeof(bufl));
	bufl[pos] = 0;
	ln = (char*)malloc(KNH_SIZE(pos+1));
	knh_memcpy(ln, bufl, pos);
	ln[pos] = 0;
	return ln;
#endif
}

/* ------------------------------------------------------------------------ */

static
void knh_add_history(char *line)
{
#if defined(KNH_USING_READLINE)
	if(line != NULL && *line) add_history(line);
#endif
}

///* ------------------------------------------------------------------------ */
//
int knh_ask(char *prompt, int def)
{
	L_TAIL:;
	char *line = knh_readline(prompt);  /* "Please enter [Y/n] : " */
	if(line == NULL) return def;
	int res;
	if (line[0] == 'y' || line[0] == 'Y') {
		res = 1;
	}
	else if (line[0] == 'n' || line[0] == 'N') {
		res = 0;
	}
	else if (line[0] == '\0') {
		res = def;
	}
	else {
		fprintf(stdout, "Again. "); fflush(stdout);
		goto L_TAIL;
	}
	free(line);
	return res;
}

/* ======================================================================== */
/* @data */

static volatile Ctx* shellContext = NULL;

#if defined(KNH_USING_POSIX)
#include <signal.h>

static void knh_initSIGINT(void);

static
void sigint_action(int signum, siginfo_t *info, void *ctx)
{
	DBG2_P("sigint_handler(%d):  signo(%d) code(0x%x)\n", signum, info->si_signo, info->si_code);
	if(shellContext == NULL) {
//		if(knh_ask("\nAre you sure ?[Y/n]", 1)) {
			exit(0);
//		}
	}
	else {
		//knh_initSIGINT();
		KNH_THROWs(shellContext, "Interrupted!!");
	}
}
#endif

/* ------------------------------------------------------------------------ */

static void knh_initSIGINT(void)
{
#if defined(KNH_USING_POSIX)
	struct sigaction sa_sigint;
	knh_bzero(&sa_sigint, sizeof(sa_sigint));
	sa_sigint.sa_sigaction = sigint_action;
	sa_sigint.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGINT, &sa_sigint, NULL) < 0) {
		perror("sigaction");
	}
#endif
}

/* ======================================================================== */
/* [shell] */

KNHAPI(void) konoha_shell(konoha_t konoha)
{
	KONOHA_CHECK_(konoha);
	Ctx *ctx = konoha.ctx;
	knh_beginContext(ctx);
	knh_Context_setInteractive(ctx, 1);
	knh_Context_setDebug(ctx, 1);
	knh_initSIGINT();
	{
		knh_System__dump(ctx, ctx->sys, KNH_STDOUT, (String*)KNH_NULL);
		int linenum, linecnt = 0;
		knh_cwb_t cwb = new_cwb(ctx);
		char *ln = NULL;
		knh_sfp_t *lsfp = KNH_LOCAL(ctx);
		KNH_LPUSH(ctx, KNH_NULL);  // step esp++;

		START_LINE:;
		if(ln != NULL) free(ln);
#ifdef KNH_DBGMODE
		ln = knh_readline("\n>>> ");
#else
		ln = knh_readline(">>> ");
#endif
		linecnt++;
		linenum = linecnt;

		while(1) {
			int nest = 0;
			if(ln == NULL) {
				KNH_LOCALBACK(ctx, lsfp);
				knh_Context_clearstack(ctx);
				return;
			}
			knh_Bytes_write(ctx, cwb.ba, B(ln));
			nest = knh_bytes_checkStmtLine(knh_cwb_tobytes(cwb));
			if(nest == 0) break;
			if(nest < 0) {
				knh_println(ctx, KNH_STDOUT, STEXT("(Canceled)"));
				knh_cwb_clear(cwb);
				goto START_LINE;
			}else {
				knh_Bytes_putc(ctx, cwb.ba, '\n');
				if(ln != NULL) free(ln);
				ln = knh_readline("... ");
				linecnt++;
			}
		}
		if(cwb.pos < knh_Bytes_size(cwb.ba)) {
			knh_bytes_t t = knh_cwb_tobytes(cwb);
			if(ISB(t, "exit") || ISB(t, "quit") || ISB(t, "bye")) {
				if(ln != NULL) free(ln);
				knh_cwb_clear(cwb);
				KNH_LOCALBACK(ctx, lsfp);
				knh_Context_clearstack(ctx);
				knh_Context_setInteractive(ctx, 0);
				knh_endContext(ctx);
				return;
			}
			if(knh_bytes_startsWith(t, STEXT("man "))) {
				char bufc[CLASSNAME_BUFSIZ], *p = bufc;
				knh_snprintf(bufc, sizeof(bufc), "%%man(%s)", (char*)knh_bytes_last(t, 4).buf);
				while(*p != 0) {
					if(*p == ';') *p = ' ';
					p++;
				}
				knh_cwb_clear(cwb);
				knh_Bytes_write(ctx, cwb.ba, B(bufc));
			}
			else if(knh_bytes_startsWith(t, STEXT("dump "))) {
				char bufc[CLASSNAME_BUFSIZ], *p = bufc;
				knh_snprintf(bufc, sizeof(bufc), "%%dump(%s)", (char*)knh_bytes_last(t, 5).buf);
				while(*p != 0) {
					if(*p == ';') *p = ' ';
					p++;
				}
				knh_cwb_clear(cwb);
				knh_Bytes_write(ctx, cwb.ba, B(bufc));
			}
			//knh_Bytes_putc(ctx, cwb.ba, ';');
			knh_Bytes_putc(ctx, cwb.ba, '\n');
			{
				InputStream *in = new_BytesInputStream(ctx, cwb.ba, cwb.pos, knh_Bytes_size(cwb.ba));
				KNH_MOV(ctx, lsfp[0].o, in);
				DP(in)->resid = knh_getResourceId(ctx, STEXT("(shell)"));
				DP(in)->line = linenum;
				knh_InputStream_setEncoding(ctx, in, KNH_ENC);
				shellContext = ctx;
				konohac_eval(ctx, TS_main, in);
				shellContext = NULL;
				knh_cwb_clear(cwb);
			}
		}
		goto START_LINE;
	}
}

/* ======================================================================== */
/* @method void Script.eval(String script, String file, Int linenum) @Static */

METHOD knh__Script_eval(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_NOTNULL(sfp[1].s)) {
		knh_sfp_t *lsfp = KNH_LOCAL(ctx);
		knh_cwb_t cwb = new_cwb(ctx);
		knh_Bytes_write(ctx, cwb.ba, knh_String_tobytes(sfp[1].s));
		knh_Bytes_putc(ctx, cwb.ba, ';');
		knh_Bytes_putc(ctx, cwb.ba, '\n');
		InputStream *in = new_BytesInputStream(ctx, cwb.ba, cwb.pos, knh_Bytes_size(cwb.ba));
		KNH_LPUSH(ctx, in);
		if(IS_NULL(sfp[2].o)) {
			DP(in)->resid = knh_getResourceId(ctx, STEXT("(eval)"));
		}
		else {
			DP(in)->resid = knh_getResourceId(ctx, knh_String_tobytes(sfp[2].s));
		}
		if(IS_NULL(sfp[3].o)) {
			DP(in)->line = 0;
		}
		else {
			DP(in)->resid = (knh_resid_t)p_int(sfp[3]);
		}
		konohac_eval(ctx, TS_main, in);
		knh_cwb_clear(cwb);
		KNH_LOCALBACK(ctx, lsfp);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Script.isStatement(String! script) @Static */

METHOD knh__Script_isStatement(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(knh_bytes_checkStmtLine(knh_String_tobytes(sfp[1].s))));
}

/* ------------------------------------------------------------------------ */
/* @method String Script.readLine(String prompt) @Static */

METHOD knh__Script_readLine(Ctx *ctx, knh_sfp_t *sfp)
{
	char *line;
	if(IS_NULL(sfp[1].o)) {
		line = knh_readline("");
	}
	else {
		line = knh_readline(knh_String_tochar(sfp[1].s));
	}
	if(line == NULL) {
		KNH_RETURN(ctx, sfp, KNH_NULL);
	}
	else {
		KNH_RETURN(ctx, sfp, new_String(ctx, B(line), NULL));
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Script.addHistory(String! s) @Static */

METHOD knh__Script_addHistory(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_add_history(knh_String_tochar(sfp[1].s));
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
