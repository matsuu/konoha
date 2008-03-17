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

#ifdef KONOHA_OS__TK

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */
/* [name] */

char *
knh_file_ospath(Ctx *ctx, knh_bytes_t path, char *buf, size_t bufsiz)
{
	size_t i;
	if(knh_bytes_startsWith(path, STEXT("file:"))) {
		knh_snprintf(buf, bufsiz, "%s", (char*)(&path.buf[5]));
	}
	else {
		knh_snprintf(buf, bufsiz, "%s", (char*)path.buf);
	}
	for(i = 0; buf[i] != 0; i++) {
		if(buf[i] == '\\') buf[i] = '/';
	}
	return buf;
}

/* ------------------------------------------------------------------------ */

char *
knh_file_knhpath(Ctx *ctx, knh_bytes_t path, char *buf, size_t bufsiz)
{
	size_t i;
	if(knh_bytes_startsWith(path, STEXT("file:"))) {
		knh_snprintf(buf, bufsiz, "%s", (char*)path.buf);
	}
	else {
		knh_snprintf(buf, bufsiz, "file:%s", (char*)path.buf);
	}
	for(i = 0; buf[i] != 0; i++) {
		if(buf[i] == '\\') buf[i] = '/';
	}
	return buf;
}

/* ======================================================================== */
/* [setting] */

char *knh_file_getInstalledHomePath(char *buf, size_t bufsiz)
{
	
	/** HERE **/

#ifdef KONOHA_HOME
	return KONOHA_HOME;
#endif
	return "/usr/konoha";
}

/* ======================================================================== */
/* [file] */

#ifdef __cplusplus
}
#endif

#endif/*KONOHA_OS__TK*/
