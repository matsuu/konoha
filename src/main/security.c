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
#ifndef KONOHA_ON_LKM
#include<time.h>
#endif

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [verbose] */
/* ------------------------------------------------------------------------ */

KNHAPI(char*) konoha_getPassword(Ctx *ctx, knh_bytes_t url)
{
	knh_index_t loc = knh_bytes_index(url, '?');
	if(loc > 0) url = knh_bytes_first(url, loc);
	loc = knh_bytes_index(url, ':');
	if(loc > 0 && url.buf[loc+1] == '/' && url.buf[loc+2] == '/') {
		knh_bytes_t scheme = knh_bytes_first(url, loc + 3);
		knh_bytes_t t = knh_bytes_last(url, loc+3);
		loc = knh_bytes_index(t, '@');
		if(loc > 0) {
			knh_bytes_t t = knh_bytes_last(t, loc+1);
		}
		knh_format_join2(buf, bufsiz, scheme, t);
		return 1;
	}
	return "UseAnother";
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
