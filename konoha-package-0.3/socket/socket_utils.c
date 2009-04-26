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

#include<konoha.h>

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [URL] */

//char *
//knh_bytes_urlencode(knh_bytes_t s, char *buf, size_t bufsiz)
//{
//	/* @author <sourceforge account> */
//	TODO();
//	knh_snprintf(buf, bufsiz, "%s", (char*)s.buf);
//	return buf;
//}
//
///* ------------------------------------------------------------------------ */
//
//char *
//knh_bytes_urldecode(knh_bytes_t s, char *buf, size_t bufsiz)
//{
//	/* @author <sourceforge account> */
//	knh_snprintf(buf, bufsiz, "%s", (char*)s.buf);
//	return buf;
//}
//
///* ------------------------------------------------------------------------ */
//
//char *
//knh_bytes_urlhost(knh_bytes_t url, char *buf, size_t bufsiz)
//{
//	knh_index_t idx = knh_bytes_index(url, ':');
//	int i = 0;
//	if(idx == -1 || url.buf[idx+1] != '/' || url.buf[idx+2] != '/') {
//		buf[0] = 0;
//		return buf;
//	}
//	idx += 3;
//	for(; idx < url.len; idx++) {
//		if(url.buf[idx] == '/' || url.buf[idx] == ':') break;
//		buf[i] = url.buf[idx]; i++;
//		if(i + 1 == bufsiz) { /* check overflow */
//			break;
//		}
//	}
//	buf[i] = 0;
//	return buf;
//}
//
///* ------------------------------------------------------------------------ */
//
//int
//knh_bytes_urlport(knh_bytes_t url, int defport)
//{
//	knh_index_t idx = knh_bytes_index(url, ':');
//	knh_bytes_t t;
//	if(idx == -1 || url.buf[idx+1] != '/' || url.buf[idx+2] != '/') {
//		return defport;
//	}
//	t = knh_bytes_last(url, idx+3);
//	idx = knh_bytes_index(url, ':');
//	if(idx == -1 || !isdigit(t.buf[idx+1])) {
//		return defport;
//	}
//	return (int)knh_bytes_toint(knh_bytes_last(t, idx));
//}
//
///* ------------------------------------------------------------------------ */
//
//char *
//knh_bytes_urlpath(knh_bytes_t url, char *buf, size_t bufsiz)
//{
//	knh_index_t idx = knh_bytes_index(url, ':');
//	knh_bytes_t t;
//	if(idx == -1 || url.buf[idx+1] != '/' || url.buf[idx+2] != '/') {
//		if(buf == NULL) return "/";
//		buf[0] = '/';
//		buf[1] = 0;
//	}
//	t = knh_bytes_last(url, idx+3);
//	idx = knh_bytes_index(t, '/');
//	if(idx == -1) {
//		if(buf == NULL) return "/";
//		buf[0] = '/';
//		buf[1] = 0;
//	}
//	if(buf == NULL) return (char*)t.buf + idx;
//	knh_snprintf(buf, bufsiz, "%s", (char*)(t.buf + idx));
//	return buf;
//}

/* ======================================================================== */
/* [other] */

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
