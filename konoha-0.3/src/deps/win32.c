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

#ifdef KNH_USING_WIN32

#include<time.h>
#include<windows.h>

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [dlopen] */

void *knh_dlopen(Ctx *ctx, const char* path, int mode)
{
	char buff[FILENAME_BUFSIZ];
	knh_format_ospath(NULL, buff, sizeof(buff), B((char*)path));
	void *hdr = (void*)LoadLibraryA((LPCTSTR)buff);
	fprintf(stderr, "dlopen .. '%s' hdr=%p\n", buff, hdr);
	return hdr;
}

/* ------------------------------------------------------------------------ */

void *knh_dlsym(Ctx *ctx, void* handle, const char* symbol)
{
	//char buff[FILENAME_BUFSIZ];
	//knh_snprintf(buff, sizeof(buff), "_%s@4", symbol);
	void *p = (void*)GetProcAddress((HMODULE)handle, (LPCSTR)symbol);
//	fprintf(stderr, "dlsym .. '%s', hdr=%p, *p=%p\n", buff, handle, p);
	return p;
}

/* ------------------------------------------------------------------------ */

const char *knh_dlerror(Ctx *ctx)
{
	return "DLLERROR";
}

/* ------------------------------------------------------------------------ */

int knh_dlclose(Ctx *ctx, void* handle)
{
	return (int)FreeLibrary((HMODULE)handle);
}

/* ======================================================================== */
/* [homepath] */

char *
knh_format_homepath(char *buf, size_t bufsiz)
{
	// @url(http://shinh.skr.jp/binary/b2con.html)
	char bufl[FILENAME_BUFSIZ];
	HMODULE h = LoadLibrary(NULL);
	GetModuleFileNameA(h, buf, bufsiz);
	knh_format_nzpath(bufl, sizeof(bufl), B(buf));
	//DBG2_P("nzpath='%s'", bufl);
	knh_format_parentpath(buf, bufsiz, B(bufl), 2);
	return buf;
}

/* ======================================================================== */
/* [file] */

int knh_isfile(Ctx *ctx, knh_bytes_t path)
{
	char dirname[FILENAME_BUFSIZ];
	knh_format_ospath(ctx, dirname, sizeof(dirname), path);
	DWORD attr = GetFileAttributesA(dirname);
	if(attr == -1) return 0;
	if((attr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) return 0;
	return 1;
}

/* ------------------------------------------------------------------------ */

int knh_isdir(Ctx *ctx, knh_bytes_t path)
{
	char dirname[FILENAME_BUFSIZ];
	knh_format_ospath(ctx, dirname, sizeof(dirname), path);
	DWORD attr = GetFileAttributesA(dirname);
	if(attr == -1) return 0;
	return ((attr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);
}

/* ======================================================================== */
/* [time] */

knh_uint_t knh_initseed()
{
	return time(NULL);
}
/* ------------------------------------------------------------------------ */

knh_uint64_t konoha_gettime()
{
	DWORD tickCount = GetTickCount();
	return (knh_int64_t)tickCount;
}

/* ======================================================================== */

#ifdef __cplusplus
}
#endif

#endif/* KNH_USING_WIN32 */
