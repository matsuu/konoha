/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2005-2009, Kimio Kuramitsu <kimio at ynu.ac.jp>
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
#ifndef KONOHA_ON_LKM
#include<time.h>
#endif

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [verbose] */

#define _KNH_FLAG_PF_STDERR      KNH_FLAG_T0
#define _KNH_FLAG_PF_EOL         KNH_FLAG_T1
#define _KNH_FLAG_PF_TIME        KNH_FLAG_T2
#define _KNH_FLAG_PF_FUNC        KNH_FLAG_T3
#define _KNH_FLAG_PF_NAME        KNH_FLAG_T4
#define _KNH_FLAG_PF_BOL         KNH_FLAG_T7

/* ------------------------------------------------------------------------ */

static
OutputStream *knh_stack_pstream(Ctx *ctx, knh_flag_t flag)
{
	return KNH_STDOUT;
}

/* ------------------------------------------------------------------------ */

static
void knh_stack_beginPRINT(Ctx *ctx, knh_sfp_t *sfp, knh_flag_t flag, OutputStream *w)
{
	if(KNH_FLAG_IS(flag, KNH_FLAG_PF_BOL)) {
		if(KNH_FLAG_IS(flag, KNH_FLAG_PF_TIME)) {
	//		char buf[80];
	//		time_t timer;
	//		struct tm now_buf, *now;
	//		time(&timer);
	//		now = localtime_r(&timer, &now_buf);
	//		knh_snprintf(buf, sizeof(buf), "[%d/%d/%d %d/%d/%d] ", now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
	//		knh_write__s(ctx, w, buf);
		}
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_stack_endPRINT(Ctx *ctx, knh_sfp_t *sfp, knh_flag_t flag, OutputStream *w)
{
	if(KNH_FLAG_IS(flag, KNH_FLAG_PF_BOL)) {
		knh_putc(ctx, w, ' ');
	}
	else if(KNH_FLAG_IS(flag, KNH_FLAG_PF_EOL)) {
		knh_write_EOL(ctx, w);
		knh_flush(ctx, w);
	}
	else if(KNH_FLAG_IS(flag, KNH_FLAG_PF_NAME)) {
		knh_putc(ctx, w, '=');
	}
	else {
		knh_putc(ctx, w, ',');
		knh_putc(ctx, w, ' ');
	}
}

/* ------------------------------------------------------------------------ */

void knh_stack_pmsg(Ctx *ctx, knh_sfp_t *sfp, knh_flag_t flag, String *s)
{
	OutputStream *w = knh_stack_pstream(ctx, flag);
	knh_stack_beginPRINT(ctx, sfp, flag, w);
	KNH_ASSERT(IS_bString(s));
	if((s)->size > 0) {  /* remove TS_EMPTY */
		knh_print(ctx, w, knh_String_tobytes(s));
	}
	else {
		flag = (flag & ~(KNH_FLAG_PF_BOL));
	}
	knh_stack_endPRINT(ctx, sfp, flag, w);
}

/* ------------------------------------------------------------------------ */

void knh_stack_p(Ctx *ctx, knh_sfp_t *sfp, knh_flag_t flag, knh_methodn_t mn, int sfpidx)
{
	OutputStream *w = knh_stack_pstream(ctx, flag);
	knh_stack_beginPRINT(ctx, sfp, flag, w);
	knh_sfp_t *esp = ctx->esp;
	KNH_SETv(ctx, esp[1].o, sfp[sfpidx].o);
	esp[1].data = sfp[sfpidx].data;
	knh_esp1_format(ctx, mn, w, KNH_NULL);
	knh_stack_endPRINT(ctx, sfp, flag, w);
}

/* ------------------------------------------------------------------------ */

static int tglobalVerbose = 5;

/* ------------------------------------------------------------------------ */

int knh_verbose(void)
{
	return tglobalVerbose;
}

/* ======================================================================== */
/* [file] */

KNHAPI(char*) KNH_SAFEFILE(char *file)
{
	if(file == NULL) return "(unknown)";
	knh_bytes_t t = B(file);
	int loc = knh_bytes_rindex(t, '/');
	if(loc == -1) {
		return file;
	}
	return (char*)t.buf + loc + 1;
}


/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
