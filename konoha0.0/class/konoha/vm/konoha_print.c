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

/* ======================================================================== */
/* [verbose] */


#define _KNH_FLAG_PF_LINEFEED   KNH_FLAG_T0

/* ------------------------------------------------------------------------ */

static int tglobalVerbose = 5;

/* ------------------------------------------------------------------------ */

int knh_verbose(void) 
{
	return tglobalVerbose;
}

/* ======================================================================== */
/* [file] */

char *KNH_SAFEFILE(char *file)
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

void
knh_vmprint(Ctx *ctx, Object **sfp, /* knh_dwarf_t dwf,*/ knh_flag_t flag, knh_methodn_t mn, Object *o)
{
	knh_format(ctx, KNH_STDOUT, mn, o, KNH_NULL);
	knh_putc(ctx, KNH_STDOUT, ' ');
	if(KNH_FLAG_IS(flag, KNH_FLAG_PF_LINEFEED)) {
		knh_println(ctx, KNH_STDOUT, STEXT(""));
		knh_flush(ctx, KNH_STDOUT);
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
