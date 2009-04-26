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

#ifdef KNH_USING_POSIX

#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#include<dlfcn.h>

#include<time.h>
#include<sys/time.h>

#ifdef KONOHA_OS__MACOSX
#include <mach-o/dyld.h>
#endif

#ifdef KNH_USING_WINDOWS
#include<windows.h>
#endif

#define KNH_USING_NOAPI 1

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [dlopen] */

void *knh_dlopen(Ctx *ctx, const char* path, int mode)
{
	char buff[FILENAME_BUFSIZ];
	knh_format_ospath(ctx, buff, sizeof(buff), B((char*)path));
	DBG_P("dlopen .. '%s'\n", buff);
#ifdef KNH_USING_WINDOWS
#undef KNH_USING_NOAPI
	return (void*)LoadLibraryA((LPCTSTR)buff);
#endif
#ifdef KNH_USING_POSIX
#undef KNH_USING_NOAPI
	return dlopen(buff, mode);
#endif
#ifdef KNH_USING_NOAPI
	return NULL;
#endif
}

/* ------------------------------------------------------------------------ */

void *knh_dlsym(Ctx *ctx, void* hdr, const char* symbol)
{
#ifdef KNH_USING_WINDOWS
	return GetProcAddress((HMODULE)handle, (LPCSTR)symbol);
#endif
#ifdef KNH_USING_POSIX
	return dlsym(hdr, symbol);
#endif
#ifdef KNH_USING_NOAPI
	return NULL;
#endif
}

/* ------------------------------------------------------------------------ */

const char *knh_dlerror(Ctx *ctx)
{
#ifdef KNH_USING_WINDOWS
	return "TODO: dlerror()";
#endif
#ifdef KNH_USING_POSIX
	return dlerror();
#endif
#ifdef KNH_USING_NOAPI
	return "Unsupported dlopen APIs";
#endif
}

/* ------------------------------------------------------------------------ */

int knh_dlclose(Ctx *ctx, void* hdr)
{
#ifdef KNH_USING_WINDOWS
	return (int)FreeLibrary((HMODULE)handle);
#endif
#ifdef KNH_USING_POSIX
	return dlclose(hdr);
#endif
#ifdef KNH_USING_NOAPI
	return 1;
#endif
}

/* ======================================================================== */
/* [homepath] */

char *
knh_format_homepath(char *buf, size_t bufsiz)
{
	char bufl[FILENAME_BUFSIZ];
#ifdef KONOHA_OS__LINUX
#define HOMEPATH
	// @url(http://shinh.skr.jp/binary/b2con.html)
	// http://doc.trolltech.com/3.3/qapplication.html#applicationDirPath
	readlink("/proc/self/exe", buf, bufsiz);
	knh_format_nzpath(bufl, sizeof(bufl), B(buf));
	knh_format_parentpath(buf, bufsiz, B(bufl), 2);
#endif/*KONOHA_OS__LINUX*/
#ifdef KONOHA_OS__MACOSX
#define HOMEPATH
	const char *s = _dyld_get_image_name(0);
	s = realpath(s, bufl);
	knh_format_parentpath(buf, bufsiz, B((char*)s), 2);
	//DBG_P("'%s', homepath='%s'", s, buf);
#endif
#ifdef KONOHA_OS__CYGWIN
#define HOMEPATH
	// @url(http://shinh.skr.jp/binary/b2con.html)
	HMODULE h = LoadLibrary(NULL);
	GetModuleFileNameA(h, buf, bufsiz);
	knh_format_nzpath(bufl, sizeof(bufl), B(buf));
	//DBG2_P("nzpath='%s'", bufl);
	knh_format_parentpath(buf, bufsiz, B(bufl), 2);
#endif
#ifndef HOMEPATH
	knh_snprintf(bufl, sizeof(bufl), "/usr/konoha");
#endif
	return buf;
}

/* ======================================================================== */
/* [file] */

int knh_isfile(Ctx *ctx, knh_bytes_t path)
{
	struct stat buf;
	char dirname[FILENAME_BUFSIZ];
	knh_format_ospath(ctx, dirname, sizeof(dirname), path);
	if(stat(dirname, &buf) == -1) return 0;
	return S_ISREG(buf.st_mode);
}

/* ------------------------------------------------------------------------ */

int knh_isdir(Ctx *ctx, knh_bytes_t path)
{
	struct stat buf;
	char dirname[FILENAME_BUFSIZ];
	knh_format_ospath(ctx, dirname, sizeof(dirname), path);
	if(stat(dirname, &buf) == -1) return 0;
	return S_ISDIR(buf.st_mode);
}

/* ------------------------------------------------------------------------ */

int knh_isnewerfile(Ctx *ctx, char *path, char *path2)
{
	char f1[FILENAME_BUFSIZ];
	char f2[FILENAME_BUFSIZ];
	struct stat s1, s2;
	knh_format_ospath(ctx, f1, sizeof(f1), B(path));
	knh_format_ospath(ctx, f2, sizeof(f2), B(path2));
	if(stat(f1, &s1) == -1 || stat(f2, &s2) == -1) return 0;
	return s1.st_mtime > s2.st_mtime;
}

/* ======================================================================== */
/* [time] */

knh_uint_t knh_initseed()
{
	return time(NULL) + getpid();
}

/* ------------------------------------------------------------------------ */

knh_uint64_t konoha_gettime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif

#endif/* KNH_USING_POSIX */
