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

#ifdef KONOHA_ON_LKM
#undef KNH_USING_POSIX
#endif

#ifdef KNH_USING_POSIX
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#include<dlfcn.h>
#include<time.h>
#include<sys/time.h>

#ifdef KONOHA_ON_MACOSX
#include <mach-o/dyld.h>
#endif

#endif/*KNH_USING_POSIX*/

#ifdef KNH_USING_WINDOWS
#include<windows.h>
#endif


/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [fileutils] */

KNHAPI(char*) knh_format_ospath(Ctx *ctx, char *buf, size_t bufsiz, knh_bytes_t path)
{
	knh_intptr_t i, hasUTF8 = 0;
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
		if(buf[i] < 0) hasUTF8 = 1;
	}
	//DBG_P("ospath='%s'", buf);
	if(hasUTF8) {
		TODO();
	}
	return buf;
}

/* ------------------------------------------------------------------------ */

KNHAPI(char*) knh_format_ospath2(Ctx *ctx, char *buf, size_t bufsiz, knh_bytes_t path, char *ext)
{
	knh_intptr_t i, hasUTF8 = 0;
	if(knh_bytes_startsWith(path, STEXT("file:"))) {
		path = knh_bytes_last(path, 5);
	}
	if(ext == NULL) {
		knh_format_bytes(buf, bufsiz, path);
	}
	else {
		knh_format_join2(buf, bufsiz, path, B(ext));
		DBG2_P("'%s'", buf);
	}
	for(i = 0; buf[i] != 0; i++) {
		if(buf[i] == '/' || buf[i] == '\\') {
			buf[i] = KONOHA_OS_FILE_SEPARATOR;
		}
		if(buf[i] < 0) hasUTF8 = 1;
	}
	if(hasUTF8) {
		TODO();
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

/* ======================================================================== */
/* [file] */

knh_boolean_t knh_isfile(Ctx *ctx, knh_bytes_t path)
{
#if defined(KNH_USING_WINDOWS)
	char dirname[FILEPATH_BUFSIZ];
	knh_format_ospath(ctx, dirname, sizeof(dirname), path);
	DWORD attr = GetFileAttributesA(dirname);
	if(attr == -1) return 0;
	if((attr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) return 0;
	return 1;
#elif defined(KNH_USING_POSIX)
	char dirname[FILEPATH_BUFSIZ];
	knh_format_ospath(ctx, dirname, sizeof(dirname), path);
    struct stat buf;
	if(stat(dirname, &buf) == -1) return 0;
	return S_ISREG(buf.st_mode);
#elif defined(KNH_USING_BTRON)
	char dirname[FILEPATH_BUFSIZ];
	knh_format_ospath(ctx, dirname, sizeof(dirname), path);
	FILE* fp = fopen(dirname,"r");
	if(fp == NULL){
            return 0;
	}
	fclose(fp);
	return 1;
#else
	return 0;
#endif
}

/* ------------------------------------------------------------------------ */

knh_boolean_t knh_isdir(Ctx *ctx, knh_bytes_t path)
{
#if defined(KNH_USING_WINDOWS)
	char dirname[FILEPATH_BUFSIZ];
	knh_format_ospath(ctx, dirname, sizeof(dirname), path);
	DWORD attr = GetFileAttributesA(dirname);
	if(attr == -1) return 0;
	return ((attr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);
#elif defined(KNH_USING_POSIX)
	char dirname[FILEPATH_BUFSIZ];
	knh_format_ospath(ctx, dirname, sizeof(dirname), path);
    struct stat buf;
	if(stat(dirname, &buf) == -1) return 0;
	return S_ISDIR(buf.st_mode);
#else
	return 0;
#endif
}

/* ------------------------------------------------------------------------ */

static
knh_bytes_t knh_bytes_parentpath(knh_bytes_t path)
{
	knh_intptr_t i;
	for(i = path.len - 1; i > 0; i--) {
		if(path.buf[i] == '/' || path.buf[i] == '\\') {
			path.len = i;
			return path;
		}
	}
	path.len = 0;
	return path;
}

/* ------------------------------------------------------------------------ */

static
knh_boolean_t knh_mkdir0(Ctx *ctx, knh_bytes_t path, int isThrowable)
{
#if defined(KNH_USING_WINDOWS)
	char dirname[FILEPATH_BUFSIZ];
	knh_format_ospath(ctx, dirname, sizeof(dirname), path);
	if(!CreateDirectoryA(dirname, NULL)) {
		KNH_PERRNO(ctx, "OS!!", "CreateDirectory", isThrowable);
		return 0;
	}
	return 1;
#elif defined(KNH_USING_POSIX)
	char dirname[FILEPATH_BUFSIZ];
	knh_format_ospath(ctx, dirname, sizeof(dirname), path);
	if(mkdir(dirname, 0777) == -1) {
		KNH_PERRNO(ctx, "OS!!", "mkdir", isThrowable);
		return 0;
	}
	return 1;
#else
	KNH_NOAPI(ctx, isThrowable);
	return 0;
#endif
}
/* ------------------------------------------------------------------------ */

knh_boolean_t knh_mkdir(Ctx *ctx, knh_bytes_t path, int isThrowable)
{
	if(!knh_isdir(ctx, path)) {
		knh_bytes_t ppath = knh_bytes_parentpath(path);
		if(ppath.len == 0 || knh_isdir(ctx, ppath) ) {
			return knh_mkdir0(ctx, path, isThrowable);
		}
		else if(knh_mkdir(ctx, ppath, isThrowable)) {
			return knh_mkdir0(ctx, path, isThrowable);
		}
		return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

knh_boolean_t knh_unlink(Ctx *ctx, knh_bytes_t f, int isThrowable)
{
#if defined(KNH_USING_POSIX)
	char fbuf[FILEPATH_BUFSIZ];
	knh_format_ospath(ctx, fbuf, sizeof(fbuf), f);
	if(unlink(fbuf) == -1) {
		KNH_PERRNO(ctx, "OS!!", "unlink", isThrowable);
		return 0;
	}
	return 1;
#elif defined(KNH_USING_WINDOWS)
	char fbuf[FILEPATH_BUFSIZ];
	knh_format_ospath(ctx, fbuf, sizeof(fbuf), f);
	if(DeleteFileA(fbuf) == 0) {
		KNH_PERRNO(ctx, "OS!!", "DeleteFile", isThrowable);
		return 0;
	}
	return 1;
#else
	KNH_NOAPI(ctx, isThrowable);
	return 0;
#endif/*KNH_USING_WINDOWS*/
}

/* ------------------------------------------------------------------------ */

knh_boolean_t knh_rename(Ctx *ctx, knh_bytes_t on, knh_bytes_t nn, int isThrowable)
{
#if defined(KNH_USING_POSIX)
	char oldbuf[FILEPATH_BUFSIZ], newbuf[FILEPATH_BUFSIZ];
	knh_format_ospath(ctx, oldbuf, sizeof(oldbuf), on);
	knh_format_ospath(ctx, newbuf, sizeof(newbuf), nn);
	if(rename(oldbuf, newbuf) == -1) {
		KNH_PERRNO(ctx, "OS!!", "rename", isThrowable);
		return 0;
	}
	return 1;
#elif defined(KNH_USING_WINDOWS)
	char oldbuf[FILEPATH_BUFSIZ], newbuf[FILEPATH_BUFSIZ];
	knh_format_ospath(ctx, oldbuf, sizeof(oldbuf), on);
	knh_format_ospath(ctx, newbuf, sizeof(newbuf), nn);
	if(MoveFileA(oldbuf, newbuf) == 0) {
		KNH_PERRNO(ctx, "OS!!", "MoveFile", isThrowable);
		return 0;
	}
	return 1;
#else
	KNH_NOAPI(ctx, isThrowable);
	return 0;
#endif/*KNH_USING_WINDOWS*/
}

/* ======================================================================== */
/* [homepath] */

#undef HOMEPATH

char *knh_format_homepath(char *buf, size_t bufsiz)
{
#if defined(KONOHA_HOMEPATH)
	knh_snprintf(buf, bufsiz, KONOHA_HOMEPATH);
	return buf;
#elif defined(KNH_USING_WINDOWS)
	char bufl[FILEPATH_BUFSIZ];
	HMODULE h = LoadLibrary(NULL);
	GetModuleFileNameA(h, buf, bufsiz);
	knh_format_nzpath(bufl, sizeof(bufl), B(buf));
	//DBG2_P("nzpath='%s'", bufl);
	knh_format_parentpath(buf, bufsiz, B(bufl), 2);
	return buf;
#elif defined(KONOHA_ON_LINUX)
	// @url(http://shinh.skr.jp/binary/b2con.html)
	// http://doc.trolltech.com/3.3/qapplication.html#applicationDirPath
	char bufl[FILEPATH_BUFSIZ];
	readlink("/proc/self/exe", buf, bufsiz);
	knh_format_nzpath(bufl, sizeof(bufl), B(buf));
	knh_format_parentpath(buf, bufsiz, B(bufl), 2);
	return buf;
#elif defined(KONOHA_ON_MACOSX)
	char bufl[FILEPATH_BUFSIZ];
	const char *s = _dyld_get_image_name(0);
	s = realpath(s, bufl);
	knh_format_parentpath(buf, bufsiz, B((char*)s), 2);
	return buf;
#else
	#ifndef KNH_PREFIX
	#define KNH_PREFIX "/konoha"
	#endif
	knh_snprintf(buf, bufsiz, KNH_PREFIX);
	return buf;
#endif
}

/* ======================================================================== */

#ifdef __cplusplus
}
#endif

