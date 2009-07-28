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

#ifdef KNH_CC_METHODAPI

/* ======================================================================== */
/* [konoha.script] */

/* ------------------------------------------------------------------------ */
/* @method Boolean! Script.isStmt(String! script) @Static */

METHOD knh__Script_isStmt(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(knh_bytes_checkStmtLine(knh_String_tobytes(sfp[1].s))));
}

/* ------------------------------------------------------------------------ */
/* @method void Script.eval(String! script, String file, Int line) @Static */

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



#endif/* KNH_CC_METHODAPI*/

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
