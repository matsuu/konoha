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

/* ======================================================================== */
/* [macro] */

#define _NSN_main           0
#define _FILEN_unknown      0

/* ======================================================================== */
/* [constructors] */


/* ======================================================================== */
/* [properties] */

char *
knh_bytes_nzenvkey(knh_bytes_t t, char *buf, size_t bufsiz)
{
	size_t i;
	for(i = 0; i < t.len; i++) {
		if(i < bufsiz) {
			buf[i] = toupper(t.buf[i]);
		}
		else {
			buf[bufsiz-1] = 0;
			return buf;
		}
	}
	buf[i] = 0;
	return buf;
}

/* ------------------------------------------------------------------------ */
/* @method Any System.getProperty(String! key) */

Any* knh_System_getProperty(Ctx *ctx, System *o, knh_bytes_t key)
{
	if(knh_bytes_startsWith(key, STEXT("env."))) {
		char envkey[256];
		knh_bytes_nzenvkey(knh_bytes_last(key, 4), envkey, sizeof(envkey));
		char *v = knh_getenv(envkey);
		if(v == NULL) {
			return KNH_NULL;
		}
		return UP(new_String(ctx, B(v), NULL));
	}
	return knh_DictMap_get__b(ctx,  DP(o)->props, key);
}

/* ------------------------------------------------------------------------ */
/* @method void System.setProperty(String! key, Any value) */

void knh_System_setProperty(Ctx *ctx, System *o, String *key, Any *value)
{
	knh_DictMap_set(ctx, DP(o)->props, key, value);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_setSystemPropertyText(Ctx *ctx, char *key, char *value)
{
	String *k = new_String__T(ctx, key);
	String *v = new_String__T(ctx, value);
	knh_DictMap_set(ctx, DP(ctx->sys)->props, k, UP(v));
}

/* ------------------------------------------------------------------------ */

knh_bool_t konoha_initcheck(void)
{
#ifdef KONOHA_SAFEMODE
	fprintf(stderr, "\taddress sizeof(void*) = %d bytes\n", (int)sizeof(void *));
	fprintf(stderr, "\tint sizeof(knh_int_t) = %d bytes\n", (int)sizeof(knh_intptr_t));
	fprintf(stderr, "\tfloat sizeof(knh_float_t) = %d bytes\n", (int)sizeof(knh_float_t));
	fprintf(stderr, "\tlong sizeof(knh_long_t) = %d bytes\n", (int)sizeof(knh_int64_t));
	fprintf(stderr, "\tshort sizeof(knh_short_t) = %d bytes\n", (int)sizeof(knh_short_t));
	fprintf(stderr, "\tObject(header) sizeof(hObject) = %d bytes\n", (int)sizeof(knh_hObject_t));
#endif
	KNH_ASSERT(sizeof(knh_intptr_t) == sizeof(void *));
 	KNH_ASSERT(sizeof(knh_short_t) * 2 == sizeof(knh_intptr_t));
 	return 1;
 }

/* ======================================================================== */
/* [urnalias] */

knh_bytes_t knh_Runtime_aliasURN(Ctx *ctx, knh_bytes_t aurn)
{
	String *s = (String*)knh_DictMap_get__b(ctx,  DP(ctx->sys)->URNAliasDictMap, aurn);
	if(IS_NOTNULL(s)) {
		return knh_String_tobytes(s);
	}
	return aurn;
}

/* ------------------------------------------------------------------------ */

void knh_Runtime_setAliasURN(Ctx *ctx, String *alias, String *urn)
{
	if(knh_Context_isVerbose(ctx)) {
		String *s =(String*)knh_DictMap_get__b(ctx,  DP(ctx->sys)->URNAliasDictMap, knh_String_tobytes(urn));
		if(IS_NOTNULL(s)) {
			KNH_WARNING(ctx, "Overriding %s %s", knh_String_tochar(alias), knh_String_tochar(s));
		}
	}
	knh_DictMap_set(ctx, DP(ctx->sys)->URNAliasDictMap, alias, UP(urn));
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_addAliasURN(Ctx *ctx, char *alias, char *urn)
{
	knh_Runtime_setAliasURN(ctx, new_String__T(ctx, alias), new_String__T(ctx, urn));
}



#ifdef __cplusplus
}
#endif
