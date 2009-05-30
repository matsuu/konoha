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

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef KONOHAC_ERROR_BUFSIZ
#define KONOHAC_ERROR_BUFSIZ 512
#endif

/* ======================================================================== */
/* [perrata] */

void knh_vperror(Ctx *ctx, knh_fileid_t file, int line, int level, const char *fmt, va_list *ap)
{
	knh_sfp_t list[16] = {};

}

/* ======================================================================== */
/* [perrata] */

void knh_perrata(Ctx *ctx, knh_fileid_t fileid, int line, char *oldt, char *newt)
{
	if(knh_Context_isCompiling(ctx)) {
		OutputStream *w = KNH_STDERR;
		knh_write__s(ctx, w, "\t (ERRATA): ");
		knh_write__s(ctx, w, oldt);
		knh_write__s(ctx, w, " ==> ");
		knh_write__s(ctx, w, newt);
		knh_write_EOL(ctx, w);
	}
}

#define _KNH_PERRATA_(ctx, f, l, msgo, msgn)    knh_perrata(ctx, f, l, msgo, msgn)
#define _KNH_PERRATA(ctx, tk, msg)  knh_perrata(ctx, (tk)->fileid, (tk)->line, sToken(tk), msg)

/* ------------------------------------------------------------------------ */

void
knh_Token_perrata(Ctx *ctx, Token *o, char *newtoken)
{
	knh_perrata(ctx, SP(o)->fileid, SP(o)->line, sToken(o), newtoken);
}

/* ======================================================================== */
/* [perror] */

void
knh_perror(Ctx *ctx, knh_fileid_t fileid, int line, int pe, char *msg)
{
	KNH_ASSERT(pe != KMSG_EABORT);
	char buf[512];
	OutputStream *w = KNH_STDERR;
#ifdef KNH_DBGMODE
	knh_snprintf(buf, sizeof(buf), " - [%s:%d]:%s(%d) ", FILEIDN(fileid), line, knh_message_tochar(pe), knh_message_type(pe));
#else
	switch(knh_message_type(pe)) {
	case 1:
		knh_snprintf(buf, sizeof(buf), " - [%s:%d]:(error) ", FILEIDN(fileid), line);
		break;
	case 3:
		if(!knh_Context_isCompiling(ctx)) return;
		knh_snprintf(buf, sizeof(buf), " - [%s:%d]:(info) ", FILEIDN(fileid), line);
		break;
	default:
		if(!knh_Context_isCompiling(ctx)) return;
		knh_snprintf(buf, sizeof(buf), " - [%s:%d]:(warning) ", FILEIDN(fileid), line);
		break;
	}
#endif
	knh_write__s(ctx, w, buf);
	if(msg == NULL || msg[0] == 0) {
		knh_println(ctx, w, B(knh_message_text(pe)));
	}
	else {
		knh_print(ctx, w, B(knh_message_text(pe)));
		knh_write__s(ctx, w, ": ");
		knh_println(ctx, w, B(msg));
	}
}

/* ------------------------------------------------------------------------ */

void knh_perror__s(Ctx *ctx, knh_fileid_t fileid, int line, int pe, char *msg)
{
	char buf[512];
	OutputStream *w = KNH_STDERR;
#ifdef KNH_DBGMODE
	knh_snprintf(buf, sizeof(buf), " - [%s:%d]:%s(%d) ", FILEIDN(fileid), line, knh_message_tochar(pe), knh_message_type(pe));
#else
	switch(knh_message_type(pe)) {
	case 1:
		knh_snprintf(buf, sizeof(buf), " - [%s:%d]:(error) ", FILEIDN(fileid), line);
		break;
	case 3:
		if(!knh_Context_isCompiling(ctx)) return;
		knh_snprintf(buf, sizeof(buf), " - [%s:%d]:(info) ", FILEIDN(fileid), line);
		break;
	default:
		if(!knh_Context_isCompiling(ctx)) return;
		knh_snprintf(buf, sizeof(buf), " - [%s:%d]:(warning) ", FILEIDN(fileid), line);
		break;
	}
#endif
	knh_write__s(ctx, w, buf);
	if(msg == NULL) msg = "NULL";
	knh_snprintf(buf, sizeof(buf), knh_message_text(pe), msg);
	knh_println(ctx, w, B(buf));
}

/* ------------------------------------------------------------------------ */

void knh_Token_perror(Ctx *ctx, Token *o, int pe)
{
	if(SP(o)->tt == TT_ERR) return;
	knh_perror(ctx, SP(o)->fileid, (int)SP(o)->line, pe, sToken(o));
	if(knh_message_type(pe) == 1) {
		SP(o)->tt = TT_ERR;
	}
}


/* ------------------------------------------------------------------------ */

void knh_Stmt_perror(Ctx *ctx, Stmt *o, int pe, Token *tk)
{
	if(tk == NULL || !IS_Token(tk)) {
		knh_perror(ctx, SP(o)->fileid, (int)SP(o)->line, pe, NULL);
		if(knh_message_type(pe) == 1) {
			SP(o)->stt = STT_ERR;
		}
	}
	else {
		knh_Token_perror(ctx, tk, pe);
		SP(tk)->tt = TT_ERR;
		knh_Stmt_add(ctx, o, TM(tk));
	}
}

/* ======================================================================== */
/* [Asm] */

void
knh_Asm_perror(Ctx *ctx, Asm *abr, int pe, char *msg)
{
	knh_perror(ctx, DP(abr)->fileid, (int)DP(abr)->line, pe, msg);
}

/* ------------------------------------------------------------------------ */

void
knh_Asm_assert(Ctx *ctx, Asm *abr, int c)
{
	knh_perror(ctx, DP(abr)->fileid, (int)DP(abr)->line, KMSG_EABORT, NULL);
	knh_Asm_setCancelled(abr, 1);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
