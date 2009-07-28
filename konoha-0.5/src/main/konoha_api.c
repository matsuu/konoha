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

KNHAPI(void) konoha_loadScript(konoha_t konoha, char *fpath)
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

KNHAPI(int) konoha_setMethodFunc(konoha_t konoha, char *name, knh_fmethod func)
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

void knh_add_history(char *line)
{
#if defined(KNH_USING_READLINE)
	if(line != NULL && *line) add_history(line);
#endif
}

/* ------------------------------------------------------------------------ */

int knh_ask(Ctx *ctx, char *prompt, int def)
{
	if(!knh_Context_isInteractive(ctx)) {
		return def;
	}
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
		KNH_THROWs((Ctx*)shellContext, "Interrupt!!");
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

#if defined(KNH_USING_READLINE)

volatile
static Ctx *ctxRL = NULL;

char *dupstr(char *s)
{
	 char *r = malloc(strlen(s) + 1);
	 if(r != NULL) {
		 strcpy(r, s);
		 return r;
	 }
	 return NULL;
}

static char* keywords[]= {
		"using", "import", "pragma",
		"if", "else", "switch", "case",
		"while", "do", "for", "foreach",
		"break", "continue", "throw",
		"try", "catch", "finally",
		"class", "extends", "implements",
		"function", "return", "yeild",
		"print", "assert",
		"int", "float", "boolean", "var",
		"null", "true", "false",
		NULL,
};

static
char *knh_rl_stmt(const char *text, int state)
{
	static int index, len;
	char *name;
	if(state == 0) {
		len = knh_strlen(text);
		index = 0;
	}
	while((name = keywords[index]) != NULL) {
		index++;
		if (strncmp(name, text, len) == 0) return (dupstr(name));
	}
	return NULL;
}

static
knh_bytes_t knh_bytes_token(knh_bytes_t t)
{
	int i;
	for(i = t.len - 1; i >= 0; i--) {
		if(!isalnum(t.buf[i])) {
			t.buf = t.buf + i + 1;
			t.len = t.len -(i + 1);
			break;
		}
	}
	return t;
}

static
char *knh_rl_name(const char *text, int state)
{
	static int index;
	static knh_bytes_t t = {(knh_uchar_t*)"", 0};
	Ctx *ctx = (Ctx*)ctxRL;
	if(state == 0) {
		t = knh_bytes_token(B((char*)text));
		index = 0;
	}
	if(ctx != NULL) {
		DictMap *symbolDictMap = DP(ctx->abr)->symbolDictMap;
		if(state == 0) {
			knh_DictMap_sort(symbolDictMap);
		}
		for(; index < knh_DictMap_size(symbolDictMap); ) {
			char *name = knh_String_tochar(knh_DictMap_keyAt(symbolDictMap, index));
			index++;
			if (strncmp(name, (char*)t.buf, t.len) == 0) {
				return (dupstr(name));
			}
		}
	}
	return NULL;
}

static
void knh_Context_initSymbolTable(Ctx *ctx)
{
	knh_Context_initAsm(ctx);
	DictMap *symbolDictMap = DP((ctx)->abr)->symbolDictMap;
	int i;
	for(i = 0; i < KNH_TCLASS_SIZE; i++) {
		String *sname = ClassTable(i).sname;
		if(sname != NULL) {
			knh_DictMap_set(ctx, symbolDictMap, sname, UP(sname));
		}
	}
	for(i = 0; keywords[i] != NULL; i++) {
		String *s = T(keywords[i]);
		knh_DictMap_set(ctx, symbolDictMap, s, UP(s));
	}
}

#ifdef RL_VERSION_MAJOR  /* 5, or later */
char **completion_matches(const char *, rl_compentry_func_t *);
#endif

static
char **knh_completion(const char* text, int start, int end)
{
	char **matches = NULL;
	if (end == 0) {
		matches = completion_matches(text, knh_rl_stmt);
	}
	else {
		matches = completion_matches(text, knh_rl_name);
	}
	return matches;
}
#endif/*KNH_USING_READLINE*/

/* ======================================================================== */

static
void knh_initScriptLine(Ctx *ctx)
{
	DBG2_ASSERT(ctx->lines == NULL);
	KNH_INITv(((Context*)ctx)->lines, new_Array(ctx, CLASS_String, 0));
}

/* ------------------------------------------------------------------------ */

static
void knh_Context_addScriptLine(Ctx *ctx, knh_bytes_t l)
{
	if(ctx->lines != NULL) {
		knh_Array_add(ctx, ctx->lines, UP(new_String(ctx, l, NULL)));
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_cancelScriptLine(Ctx *ctx, size_t at)
{
	if(ctx->lines != NULL) {
		DBG2_P("lines (size) %d at=%d", (int)(ctx->lines)->size, (int)at);
		if(at < (ctx->lines)->size) {
			(ctx->lines)->size = at;
		}
	}
}

/* ------------------------------------------------------------------------ */

String *knh_Context_getScriptLineNULL(Ctx *ctx, size_t at)
{
	if(ctx->lines != NULL) {
		DBG2_ASSERT(at < (ctx->lines)->size);
		return (String*)knh_Array_n(ctx->lines, at - 1);
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */
/* @method String[] Script.getLines() @Hidden */

METHOD knh__Script_getLines(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *res = (ctx->lines == NULL)
		? new_Array(ctx, CLASS_String, 0) : ctx->lines;
	KNH_RETURN(ctx, sfp, res);
}

/* ------------------------------------------------------------------------ */

int knh_getpid()
{
	return 0;
}

/* ------------------------------------------------------------------------ */

static
void knh_clearScriptLine(Ctx *ctx)
{
	if(ctx->lines != NULL) {
		char buff[FILEPATH_BUFSIZ];
		int i, pid = knh_getpid();
		//knh_snprintf(buff, sizeof(buff), "\nDo you want to save 'myscript%d.k'? [Y/n]: ", pid);
		fprintf(stdout, "\nThank you for joining 'Konoha User Experience Program'.\n");
		fprintf(stdout, "All your activity have been sent to our project server.\n");
		L_AGAIN:;
		knh_snprintf(buff, sizeof(buff), "\nDo you want to report your actions? [Y/n]: ");
		if(knh_ask(ctx, buff, 1)) {
			knh_sfp_t *lsfp = KNH_LOCAL(ctx);
			OutputStream *w;
			knh_snprintf(buff, sizeof(buff), "myscript%d.k", pid);
			w = new_FileOutputStream(ctx, B(buff), "w", 0);
			KNH_LPUSH(ctx, w);
			for(i = 0; i < knh_Array_size(ctx->lines); i++) {
				knh_bytes_t line = knh_String_tobytes((String*)knh_Array_n(ctx->lines, i));
				if(knh_bytes_startsWith(line, STEXT("man ")) || knh_bytes_startsWith(line, STEXT("dump "))) {
					knh_write(ctx, w, STEXT("// "));
				}
				knh_println(ctx, w, line);
			}
			knh_OutputStream_close(ctx, w);
			KNH_LOCALBACK(ctx, lsfp);
		}
		else {
			fprintf(stdout, "Your activity will improve Konoha project.\n");
			fprintf(stdout, "Think about it, AGAIN.\n");
			goto L_AGAIN;
		}
		fprintf(stdout, "\nOpps!! The server isn't working.\n");
		fprintf(stdout, "(Don't report the server malfunction. It's a joke.)\n");
		fprintf(stdout, "More importantly, your script was saved at '%s'\n", buff);
		fprintf(stdout, "See you.\n");
		KNH_FINALv(ctx, ((Context*)ctx)->lines);
		((Context*)ctx)->lines = NULL;
	}
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
#if defined(KNH_USING_READLINE)
	ctxRL = ctx;
	rl_attempted_completion_function = knh_completion;
	knh_Context_initSymbolTable(ctx);
	using_history();
#endif
	knh_System__dump(ctx, ctx->sys, KNH_STDOUT, (String*)KNH_NULL);
	knh_initScriptLine(ctx);
	{
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
				goto L_CLOSE;
			}
			knh_Bytes_write(ctx, cwb.ba, B(ln));
			knh_Context_addScriptLine(ctx, B(ln));
			nest = knh_bytes_checkStmtLine(knh_cwb_tobytes(cwb));
			if(nest == 0) break;
			if(nest < 0) {
				knh_cancelScriptLine(ctx, linenum);
				linecnt = linenum;
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
				goto L_CLOSE;
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

		L_CLOSE:
		if(ln != NULL) free(ln);
		knh_clearScriptLine(ctx);
		knh_cwb_clear(cwb);
		KNH_LOCALBACK(ctx, lsfp);
		knh_Context_clearstack(ctx);
		knh_Context_setInteractive(ctx, 0);
		knh_endContext(ctx);
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
