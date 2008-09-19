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
#include<time.h>

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
#define _KNH_FLAG_PF_NOCOMMA     KNH_FLAG_T5
#define _KNH_FLAG_PF_EMPTY       KNH_FLAG_T6
#define _KNH_FLAG_PF_BOL         KNH_FLAG_T7

/* ------------------------------------------------------------------------ */

void knh_sfp_print(Ctx *ctx, knh_sfp_t *sfp, knh_flag_t flag, Object *s, knh_methodn_t mn, Object *o)
{
	OutputStream *w = KNH_STDOUT;
	if(KNH_FLAG_IS(flag, KNH_FLAG_PF_BOL)) {
		if(KNH_FLAG_IS(flag, KNH_FLAG_PF_TIME)) {
//			char buf[80];
//			time_t timer;
//			struct tm now_buf, *now;
//			time(&timer);
//			now = localtime_r(&timer, &now_buf);
//			knh_snprintf(buf, sizeof(buf), "[%d/%d/%d %d/%d/%d] ", now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
//			knh_write__s(ctx, w, buf);
		}
	}
	else {
		if(!KNH_FLAG_IS(flag, KNH_FLAG_PF_NOCOMMA)) {
			knh_putc(ctx, w, ',');
			knh_putc(ctx, w, ' ');
		}
	}
	if(IS_bString(s)) {
		knh_print(ctx, w, knh_String_tobytes((String*)s));
		if(KNH_FLAG_IS(flag, KNH_FLAG_PF_NAME)) {
			knh_putc(ctx, w, '=');
		}
		if(!KNH_FLAG_IS(flag, KNH_FLAG_PF_EMPTY)) {
			knh_format(ctx, w, mn, o, KNH_NULL);
		}
	}
	else {
		if(!KNH_FLAG_IS(flag, KNH_FLAG_PF_EMPTY)) {
			knh_format(ctx, w, mn, o, KNH_NULL);
		}
	}
	if(KNH_FLAG_IS(flag, KNH_FLAG_PF_EOL)) {
		knh_println(ctx, w, STEXT(""));
		knh_flush(ctx, w);
	}
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
	char *f = file;
	L_TAIL:;
	if(f[0] == '.' && f[1] == '.' && f[2] == '/') {
		f = f + 3;
		goto L_TAIL;
	}
	return f;
}


/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
