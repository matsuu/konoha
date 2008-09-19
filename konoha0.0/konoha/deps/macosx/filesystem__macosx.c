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

#ifdef KONOHA_OS__MACOSX

#include <mach-o/dyld.h>

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [ospath] */

char *
knh_format_ospath(char *buf, size_t bufsiz, knh_bytes_t path)
{
	if(knh_bytes_startsWith(path, STEXT("file:"))) {
		knh_format_bytes(buf, bufsiz, knh_bytes_last(path, 5));
	}
	else {
		knh_format_bytes(buf, bufsiz, path);
	}
	return buf;
}

/* ------------------------------------------------------------------------ */

char *
knh_format_homepath(char *buf, size_t bufsiz)
{
	char bufl[FILENAME_BUFSIZ];
	const char *s = _dyld_get_image_name(0);
	s = realpath(s, bufl);
	knh_format_parentpath(buf, bufsiz, B((char*)s), 2);
	//DBG_P("'%s', homepath='%s'", s, buf);
	return buf;
}

/* ======================================================================== */
/* [file] */

#ifdef __cplusplus
}
#endif

#endif/*KONOHA_OS__TK*/
