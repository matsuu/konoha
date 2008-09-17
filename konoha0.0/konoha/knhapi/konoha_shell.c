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

#ifdef KNH_USING_READLINE
	#include<readline/readline.h>  /* @using readline -lreadline */
	#include<readline/history.h>
#endif

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [readline] */

static
char *knh_readline(char *prompt)
{
	char *ln = NULL;
#if defined(KNH_USING_READLINE)
//	if(konoha_using_readline()) {
//		char *ln = lib_readline(prompt);
//		if(ln != NULL && *ln) lib_add_history(ln);
//		return ln;
//	}
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
		if(isascii(ch)) {
			if(isprint(ch)) {
				bufl[pos] = ch;
			}
			//DEBUG("get ch=%d %c", ch, ch);
		}
		else{
			bufl[pos] = ch;
		}
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


/* ======================================================================== */
/* [shell] */

#ifndef KONOHA_SERIAL_NUMBER
#define KONOHA_SERIAL_NUMBER 0
#endif

static
void konoha_show_version(Ctx *ctx, OutputStream *w)
{
#ifdef KONOHA_UNDER_GPL2
	knh_printf(ctx, w, "Konoha %s-GPL2 (#%d, %s, %s)\n", KONOHA_VERSION, KONOHA_SERIAL_NUMBER, __DATE__, __TIME__);
#else
	knh_printf(ctx, w, "Konoha %s (#%d, %s, %s)\n" TERM_INIT, KONOHA_VERSION, KONOHA_SERIAL_NUMBER, __DATE__, __TIME__);
#endif
	knh_printf(ctx, w, "[%s] on %s (%d, %s)\n", KONOHA_CC_VERSION, KONOHA_OS, sizeof(void*) * 8, konoha_encoding());
}

/* ------------------------------------------------------------------------ */

static
int konoha_shell_checkline(knh_bytes_t line)
{
	char *ln = (char*)line.buf;
	size_t len = line.len;
	knh_int_t i = 0, ch, quote = 0, nest =0;
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

KNHAPI(void) konoha_shell(Ctx *ctx)
{
	if(ctx == NULL) {
		KNH_SAYS("Context is not initialized");
		return;
	}

	konoha_show_version(ctx, KNH_STDOUT);
	{
		int linenum, linecnt = 0;
		knh_wbuf_t cb = knh_Context_wbuf(ctx);
		char *ln = NULL;
		KNH_LOPEN(ctx, 1);

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
				KNH_LCLOSE(ctx);
				knh_Context_clearstack(ctx);
				return;
			}
			knh_Bytes_write(ctx, cb.ba, B(ln));
			nest = konoha_shell_checkline(knh_wbuf_tobytes(cb));
			if(nest == 0) break;
			if(nest < 0) {
				knh_println(ctx, KNH_STDOUT, STEXT("(Canceled)"));
				knh_Bytes_subclear(cb.ba, cb.pos);
				goto START_LINE;
			}else {
				knh_Bytes_putc(ctx, cb.ba, '\n');
				if(ln != NULL) free(ln);
				ln = knh_readline("... ");
				linecnt++;
			}
		}
		if(cb.pos < knh_Bytes_size(cb.ba)) {
			knh_bytes_t t = knh_wbuf_tobytes(cb);
			if(ISB(t, "exit") || ISB(t, "quit") || ISB(t, "bye")) {
				if(ln != NULL) free(ln);
				knh_Bytes_subclear(cb.ba, cb.pos);
				KNH_LCLOSE(ctx);
				knh_Context_clearstack(ctx);
				return;
			}
			knh_Bytes_putc(ctx, cb.ba, ';');
			knh_Bytes_putc(ctx, cb.ba, '\n');
			{
				InputStream *in = new_InputStream__Bytes(ctx, cb.ba, cb.pos, knh_Bytes_size(cb.ba));
				KNH_LSETv(ctx, 0, in);
				DP(in)->fileid = knh_tName_getFileId(ctx, STEXT("(shell)"));
				DP(in)->line = linenum;
				knh_InputStream_setEncoding(ctx, in, knh_systemEncoding);
				knh_konohac_eval(ctx, TS_main, in);
				knh_Bytes_subclear(cb.ba, cb.pos);
			}
		}
		goto START_LINE;
	}

}

/* ======================================================================== */
/* @method void Script.eval(String script, String file, Int linenum) @ClassFunc */

METHOD knh__Script_eval(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_NOTNULL(sfp[1].s)) {
		KNH_LOPEN(ctx, 0);
		knh_wbuf_t wbuf = knh_Context_wbuf(ctx);
		knh_Bytes_write(ctx, wbuf.ba, knh_String_tobytes(sfp[1].s));
		knh_Bytes_putc(ctx, wbuf.ba, ';');
		knh_Bytes_putc(ctx, wbuf.ba, '\n');
		InputStream *in = new_InputStream__Bytes(ctx, wbuf.ba, wbuf.pos, knh_Bytes_size(wbuf.ba));
		KNH_LPUSH(ctx, in);
		if(IS_NULL(sfp[2].o)) {
			DP(in)->fileid = knh_tName_getFileId(ctx, STEXT("(eval)"));
		}
		else {
			DP(in)->fileid = knh_tName_getFileId(ctx, knh_String_tobytes(sfp[2].s));
		}
		if(IS_NULL(sfp[3].o)) {
			DP(in)->line = 0;
		}
		else {
			DP(in)->fileid = (sfp[3].i)->value;
		}
		knh_konohac_eval(ctx, TS_main, in);
		knh_Bytes_subclear(wbuf.ba, wbuf.pos);
		KNH_LCLOSE(ctx);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Script.isStatement(String! script) @ClassFunc */

METHOD knh__Script_isStatement(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(konoha_shell_checkline(knh_String_tobytes(sfp[1].s))));
}

/* ------------------------------------------------------------------------ */
/* @method String Script.readline(String prompt) @ClassFunc */

METHOD knh__Script_readline(Ctx *ctx, knh_sfp_t *sfp)
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
/* @method void Script.addHistory(String! s) @ClassFunc */

METHOD knh__Script_addHistory(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_add_history(knh_String_tochar(sfp[1].s));
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
