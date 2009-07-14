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

KNHAPI(char*) knh_format_ospath(Ctx *ctx, char *buf, size_t bufsiz, knh_bytes_t path)
{
	size_t i;
	if(knh_bytes_startsWith(path, STEXT("file:"))) {
		knh_format_bytes(buf, bufsiz, knh_bytes_last(path, 5));
	}
	else {
		knh_format_bytes(buf, bufsiz, path);
	}
	for(i = 0; buf[i] != 0; i++) {
		if(buf[i] == '/' || buf[i] == '\\') {
			buf[i] = KONOHA_OS_FILE_SEPARATOR;
		}
	}
	//DBG_P("ospath='%s'", buf);
	return buf;
}

/* ------------------------------------------------------------------------ */

KNHAPI(char*) knh_format_ospath2(Ctx *ctx, char *buf, size_t bufsiz, knh_bytes_t path, char *ext)
{
	size_t i;
	if(knh_bytes_startsWith(path, STEXT("file:"))) {
		path = knh_bytes_last(path, 5);
	}
	knh_format_bytes(buf, bufsiz, path);
	if(ext != NULL) {
		size_t esize = knh_strlen(ext) + 1;
		if(path.len + esize < bufsiz) {
			knh_memcpy(buf + path.len, ext, esize);
		}
	}
	DBG2_P("'%s'", buf);
	for(i = 0; buf[i] != 0; i++) {
		if(buf[i] == '/' || buf[i] == '\\') {
			buf[i] = KONOHA_OS_FILE_SEPARATOR;
		}
	}
	return buf;
}

/* ------------------------------------------------------------------------ */

char *
knh_format_parentpath(char *buf, size_t bufsiz, knh_bytes_t path, int n)
{
	int i, c = 0;
	for(i = path.len - 1; i >= 0; i--) {
		if(path.buf[i] == '/' || path.buf[i] == '\\') {
			c++;
			if(n <= c) {
				path.len = i;
				return knh_format_bytes(buf, bufsiz, path);
			}
		}
	}
	buf[0] = 0;
	return buf;
}


/* ------------------------------------------------------------------------ */

char *
knh_format_nzpath(char *buf, size_t bufsiz, knh_bytes_t path)
{
	//size_t i, j = 0;
	int i, j = 0;
	for(i = 0; i < path.len; i++) {
		if(path.buf[i] == '/' || path.buf[i] == '\\') {
			int ch = path.buf[i];
			if(path.buf[i+1] == '.' && path.buf[i+2] == '.' && path.buf[i+3] == ch) {
				i = i + 2;
				for(; j >= 0; j--) {
					if(buf[j] == ch) {
						buf[j] = 0;
						break;
					}
					buf[j] = 0;
				}
				continue;
			}
		}
		if(j == bufsiz - 1) {
			buf[j] = 0;
			return buf;
		}
		buf[j] = (path.buf[i] == '\\') ? '/' : path.buf[i];
		j++; buf[j]= 0;
	}
	buf[j] = 0;
	return buf;
}

/* ------------------------------------------------------------------------ */

char *
knh_format_catpath(char *buf, size_t bufsiz, knh_bytes_t path, knh_bytes_t file)
{
	if(file.buf[0]=='/' || file.buf[0] == '\\' || path.buf[0] == 0) {
		return knh_format_nzpath(buf, bufsiz, file);
	}
	else {
		char buff[FILEPATH_BUFSIZ];
		knh_snprintf(buff, sizeof(buff), "%s/%s", (char*)path.buf, (char*)file.buf);
		return knh_format_nzpath(buf, bufsiz, B(buff));
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
