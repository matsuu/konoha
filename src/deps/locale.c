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
#define KONOHA_WITH_LOCALE 1

#include"commons.h"

#ifdef HAVE_LOCALE_H
#include<locale.h>
#endif

#ifdef HAVE_LOCALCHARSET_H
#include<localcharset.h>
#endif

#ifdef HAVE_LANGINFO_H
#include<langinfo.h>
#endif

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [charset] */

#ifdef KONOHA_ON_WINDOWS

#define HAVE_LOCALCHARSET_H 1

static char *locale_charset(void)
{
	static char codepage[64];
	knh_snprintf(codepage, sizeof(codepage), "CP%d", (int)GetACP());
	return codepage;
}

#endif

/* ------------------------------------------------------------------------ */

char *konoha_encoding()
{
#if defined(KONOHA_OS_ENCODING)
	return KONOHA_OS_ENCODING;
#elif defined(KNH_USING_ICONV) && defined(HAVE_LOCALCHARSET_H)
	return (char*)locale_charset();
#else
//	char *enc = knh_getenv("LC_CTYPE");
//	if(enc != NULL) {
//		return (char*)enc;
//	}
	return KONOHA_ENCODING;
#endif
}

/* ------------------------------------------------------------------------ */

char *knh_format_lang(char *buf, size_t bufsiz)
{
#ifdef KONOHA_OS_LANG
	knh_snprintf(buf, bufsiz, "%s", KONOHA_OS_LANG);
#else
	char *enc = knh_getenv("LANG");
	if(enc == NULL || (enc[0] == 'C' && enc[1] == 0)) {
		knh_snprintf(buf, bufsiz, "en");
	}
	else {
		int i = 0;
		while(enc[i] != 0) {
			if(enc[i] == '.' || i + 1 == bufsiz ) {
				break;
			}
			buf[i] = enc[i]; i++;
		}
		buf[i] = 0;
	}
#endif
	return buf;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
