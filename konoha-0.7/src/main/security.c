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

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [password] */

static int secureMode = 0;

/* ------------------------------------------------------------------------ */

void knh_setSecureMode(void)
{
	secureMode = 1;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_isTrustedPath(Ctx *ctx, knh_bytes_t path)
{
	DBG2_P("check: %s", (char*)path.buf);
	if(knh_bytes_startsWith(path, STEXT("http:"))) {
		return 0;
	}
	return (secureMode != 1);
}

/* ======================================================================== */
/* [password] */

KNHAPI(char*) knh_getPassword(Ctx *ctx, knh_bytes_t url)
{
	return "password";
}

/* ======================================================================== */
/* [Trusted] */

KNHAPI(void) knh_stack_checkSecurityManager(Ctx *ctx, knh_sfp_t *sfp)
{
	/* VERY SLOW */
	knh_sfp_t *sp = sfp - 2;
	while(ctx->stack < sp) {
		if(IS_Method(sp[0].mtd)) {
			if(!URI_ISTRUSTED(DP(sp[0].mtd)->uri)) {
				char buf[FILEPATH_BUFSIZ];
				knh_snprintf(buf, sizeof(buf), "Security!!: untrusted domain='%s'", URIDN(DP(sp[0].mtd)->uri));
				KNH_THROWs(ctx, buf);
			}
		}
		sp--;
	}
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_isTrustedHost(Ctx *ctx, knh_bytes_t host)
{
	TODO();
//	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
//	int res = knh_DictMap_index__b(DP(ctx->sys)->trustedHostDictMap, host);
//	if(res != -1) return 1;
//	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	return 0;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
