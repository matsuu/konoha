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

#ifdef KONOHA_USING_READLINE
	#include<readline/readline.h>  /* @using readline -lreadline */
	#include<readline/history.h>
#endif

//#include<konoha/lib/readline.h>

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */
/* [readline] */

char *knh_readline(char *prompt)
{
	char *ln = NULL;
#if defined(KONOHA_USING_READLINE)
//	if(konoha_using_readline()) {
//		char *ln = lib_readline(prompt);
//		if(ln != NULL && *ln) lib_add_history(ln);
//		return ln;
//	}
	ln = readline(prompt);
	if(ln != NULL && *ln) add_history(ln);
	return ln;
#endif
	
	char bufl[256];
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
	DEBUG_ASSERT(pos < sizeof(bufl));
	bufl[pos] = 0;
	ln = malloc(KNH_SIZE(pos+1));
	knh_memcpy(ln, bufl, pos);
	ln[pos] = 0;
	return ln;
}

/* ======================================================================== */
/* [shell] */

#ifndef KONOHA_SERIAL_NUMBER
#define KONOHA_SERIAL_NUMBER 0
#endif

void konoha_show_version(Ctx *ctx)
{
#ifdef KONOHA_UNDER_GPL2
	knh_printf(ctx, KNH_STDOUT, "Konoha %s-GPL2 (#%d, %s, %s)\n", KONOHA_VERSION, KONOHA_SERIAL_NUMBER, __DATE__, __TIME__);
#else
	knh_printf(ctx, KNH_STDOUT, "Konoha %s (#%d, %s, %s)\n" TERM_INIT, KONOHA_VERSION, KONOHA_SERIAL_NUMBER, __DATE__, __TIME__);
#endif
	knh_printf(ctx, KNH_STDOUT, "[%s] on %s\n", KONOHA_CC_VERSION, knh_tconst_uname());
}

/* ------------------------------------------------------------------------ */

knh_int_t 
konoha_shell_checkline(knh_bytes_t line)
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
	DEBUG_ASSERT(i > 0);
	for(; i < len; i++) {
		ch = ln[i];
		if(ln[i-1] != '\\' && ch == quote) {
			i++;
			goto L_NORMAL;
		}
	}
	return -1; /* cancelled */
}

/* ------------------------------------------------------------------------ */


void konoha_shell(konoha_t konoha)
{
	Ctx *ctx = konoha_ctx(konoha);
	knh_nsn_t nsn = NSN_main;	

	if(ctx == NULL) {
		KNH_NOTICE(ctx, "not initialized");
		return;
	}

	//konoha_using_readline();
	konoha_show_version(ctx);
	
	knh_buffer_t cb = knh_Context_buffer(ctx);
	char *ln = NULL;
	KNH_LOPEN(ctx, 0);
	
	START_LINE:;
	if(ln != NULL) free(ln);
#ifdef KONOHA_DEBUGMODE
	ln = knh_readline("\n>>> ");
#else
	ln = knh_readline(">>> ");
#endif
	
	while(1) {
		if(ln == NULL) {
			KNH_LCLOSE(ctx);
			return;
		}
		knh_Bytes_write(ctx, cb.ba, B(ln));
		knh_int_t nest = konoha_shell_checkline(knh_buffer_tobytes(cb));
		if(nest == 0) break;
		if(nest < 0) {
			fprintf(stdout, "(Canceled)\n");
			knh_Bytes_subclear(cb.ba, cb.pos);
			goto START_LINE;
		}else {
			knh_Bytes_putc(ctx, cb.ba, '\n');
			if(ln != NULL) free(ln);
			ln = knh_readline("... ");
		}
	}
	if(cb.pos < knh_Bytes_size(cb.ba)) {
		knh_bytes_t t = knh_buffer_tobytes(cb);
		if(ISB(t, "exit") || ISB(t, "quit") || ISB(t, "bye")) {
			if(ln != NULL) free(ln);
			knh_Bytes_subclear(cb.ba, cb.pos);
			KNH_LCLOSE(ctx);
			return;
		}
		knh_Bytes_putc(ctx, cb.ba, ';');
		knh_Bytes_putc(ctx, cb.ba, '\n');
		{
			InputStream *in = new_InputStream__Bytes(ctx, cb.ba, cb.pos, knh_Bytes_size(cb.ba));
			in->filen = knh_tfilen_forname(ctx, STEXT("(shell)"));
			nsn = knh_konohac_eval(ctx, nsn, in);
			knh_Bytes_subclear(cb.ba, cb.pos);
		}
	}
	goto START_LINE;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
