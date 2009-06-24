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

static
void konoha_setCurrenContext(Ctx *ctx)
{
#ifdef KNH_USING_NOTHREAD
	curctx = ctx;
#else
	if(ctx == NULL) {
		knh_thread_setspecific(ctxkey, NULL);
	}
	else {
		knh_thread_setspecific(ctxkey, ctx);
	}
#endif
}

/* ------------------------------------------------------------------------ */

KNHAPI(Ctx*) konoha_getCurrentContext(void)
{
	Ctx *ctx;
#ifdef KNH_USING_NOTHREAD
	ctx = curctx;
#else
	ctx = (Ctx*)knh_thread_getspecific(ctxkey);
	KNH_ASSERT(ctx != NULL);
#endif
	KNH_ASSERT(ctx->threadid == knh_thread_self());
	return ctx;
}

/* ------------------------------------------------------------------------ */

KNHAPI(Ctx*) konoha_getThreadContext(Ctx *ctx)
{
#ifdef KNH_USING_NOTHREAD
	curctx = ctx;
	return ctx;
#else
	knh_thread_t thread = knh_thread_self();
	if(ctx->threadid != thread) {
		ctx = (Ctx*)knh_thread_getspecific(ctxkey);
		if(ctx != NULL && ctx->threadid == thread) {
			return ctx;
		}
	}
	DBG_P("thread inconsitency.. creating new context..");
	Ctx *newctx = new_Context(ctx);
	knh_thread_setspecific(ctxkey, newctx);
	return newctx;
#endif
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

KNHAPI(char*) konoha_eval(konoha_t konoha, char *script)
{
	KONOHA_CHECK(konoha, NULL);
	Ctx *ctx = konoha.ctx;
	Bytes *ba = NULL;
	konoha_setCurrenContext(ctx);
	{
		knh_sfp_t *lsfp = KNH_LOCAL(ctx);
		knh_cwb_t cwb = new_cwb(ctx);
		knh_Bytes_write(ctx, cwb.ba, B(script));
		knh_Bytes_putc(ctx, cwb.ba, ';');
		knh_Bytes_putc(ctx, cwb.ba, '\n');
		InputStream *in = new_BytesInputStream(ctx, cwb.ba, cwb.pos, knh_Bytes_size(cwb.ba));
		KNH_LPUSH(ctx, in);
		DP(in)->fileid = konoha_getFileId(ctx, STEXT("(eval)"));
		DP(in)->line = 0;
		ba = new_Bytes(ctx, 1024);
		OutputStream *out = new_BytesOutputStream(ctx, ba);
		KNH_LPUSH(ctx, out);
		//		printk("ctx : %p %p\n", (Context*)ctx->out, out);
		KNH_SETv(ctx, ((Context*)ctx)->out, out);
		//		printk("2\n");
		KNH_SETv(ctx, ((Context*)ctx)->err, out);

		konohac_eval(ctx, TS_main, in);

		knh_cwb_clear(cwb);
		knh_OutputStream_flush(ctx, out);
		KNH_LOCALBACK(ctx, lsfp);
	}
	konoha_setCurrenContext(NULL);
	return (char*)ba->buf;
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_readFile(Ctx *ctx, char *fpath)
{
	if(!knh_isfile(ctx, B(fpath))) {
		KNH_WARNING(ctx, "No such file: %s\n", fpath);
		return ;
	}
	InputStream *in = new_FileInputStream(ctx, B(fpath));
	if(knh_InputStream_isClosed(in)) {
		KNH_WARNING(ctx, "No such script file: %s\n", fpath);
	}
	DP(in)->fileid = konoha_getFileId(ctx, B(fpath));
	knh_InputStream_setEncoding(ctx, in, knh_systemEncoding);
	konohac_eval(ctx, (String*)KNH_NULL, in);
	knh_Context_clearstack(ctx);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_read(konoha_t konoha, char *fpath)
{
	KONOHA_CHECK_(konoha);
	konoha_setCurrenContext(konoha.ctx);
	{
		konoha_readFile(konoha.ctx, fpath);
	}
	konoha_setCurrenContext(NULL);
}

/* ------------------------------------------------------------------------ */

KNHAPI(int) konoha_main(konoha_t konoha, int argc, char **argv)
{
	KONOHA_CHECK(konoha, 0);
	Ctx *ctx = konoha.ctx;
	konoha_setCurrenContext(ctx);
	knh_sfp_t *lsfp = KNH_LOCAL(ctx);
	KNH_MOV(ctx, lsfp[0].o, new_ExceptionHandler(ctx));
	KNH_TRY(ctx, L_CATCH, lsfp, 0);
	{
		NameSpace *ns = knh_System_getNameSpace(ctx, STEXT("main"));
		Script *scr = knh_NameSpace_getScript(ctx, ns);
		Method *mtd = knh_Class_getMethod(ctx, knh_Object_cid(scr), METHODN_main);

		if(IS_NULL(mtd)) {
			goto L_END_TRY;
		}
		if(knh_Method_psize(mtd) == 1) {
			knh_type_t ptype = knh_Method_pztype(mtd, 0);
			if(ptype != ATYPE_String && ptype != NNATYPE_String) {
				KNH_WARNING(ctx, "Type!!: cannot invoke main()");
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
			KNH_WARNING(ctx, "Type!!: cannot invoke main()");
			goto L_END_TRY;
		}
	}
	L_END_TRY:
	knh_Context_clearstack(ctx);
	konoha_setCurrenContext(NULL);
	return 0;

	/* catch */
	L_CATCH:;
	KNH_PRINT_STACKTRACE(ctx, lsfp, 0);
	konoha_setCurrenContext(NULL);
	return 0;
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

/* ------------------------------------------------------------------------ */

int knh_readline_askYesNo(char *prompt, int def)
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
/* [shell] */

static
int konoha_shell_checkline(knh_bytes_t line)
{
	char *ln = (char*)line.buf;
	size_t i = 0, len = line.len;
	int ch, quote = 0, nest =0;
	L_NORMAL:
	for(; i < len; i++) {
		ch = ln[i];
		if(ch == '{' || ch == '[' || ch == '(') nest++;
		if(ch == '}' || ch == ']' || ch == ')') nest--;
		if(ch == '\'' || ch == '"') {
			quote = ch; i++;
			goto L_QUOTE;
		}
	}
	return nest;

	L_QUOTE:
	KNH_ASSERT(i > 0);
	for(; i < len; i++) {
		ch = ln[i];
		if(ln[i-1] != '\\' && ch == quote) {
			i++;
			goto L_NORMAL;
		}
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_shell(konoha_t konoha)
{
	KONOHA_CHECK_(konoha);
	Ctx *ctx = konoha.ctx;
	konoha_setCurrenContext(ctx);
	knh_Context_setInteractive(ctx, 1);
	knh_Context_setDebug(ctx, 1);
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
			nest = konoha_shell_checkline(knh_cwb_tobytes(cwb));
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
				konoha_setCurrenContext(NULL);
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
				DP(in)->fileid = konoha_getFileId(ctx, STEXT("(shell)"));
				DP(in)->line = linenum;
				knh_InputStream_setEncoding(ctx, in, knh_systemEncoding);
				konohac_eval(ctx, TS_main, in);
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
			DP(in)->fileid = konoha_getFileId(ctx, STEXT("(eval)"));
		}
		else {
			DP(in)->fileid = konoha_getFileId(ctx, knh_String_tobytes(sfp[2].s));
		}
		if(IS_NULL(sfp[3].o)) {
			DP(in)->line = 0;
		}
		else {
			DP(in)->fileid = (knh_fileid_t)p_int(sfp[3]);
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
	KNH_RETURN_Boolean(ctx, sfp, !(konoha_shell_checkline(knh_String_tobytes(sfp[1].s))));
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
