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

//KNHAPI(char*) knh_format_ospath(Ctx *ctx, char *buf, size_t bufsiz, knh_bytes_t path)
//{
//	knh_intptr_t i, hasUTF8 = 0;
//	if(knh_bytes_startsWith(path, STEXT("file:"))) {
//		knh_format_bytes(buf, bufsiz, knh_bytes_last(path, 5));
//	}
//	else {
//		knh_format_bytes(buf, bufsiz, path);
//	}
//	for(i = 0; buf[i] != 0; i++) {
//		if(buf[i] == '/' || buf[i] == '\\') {
//			buf[i] = KONOHA_OS_FILE_SEPARATOR;
//		}
//		if(buf[i] < 0) hasUTF8 = 1;
//	}
//	//DBG_P("ospath='%s'", buf);
//	if(hasUTF8) {
//		TODO();
//	}
//	return buf;
//}
//
///* ------------------------------------------------------------------------ */
//
//KNHAPI(char*) knh_format_ospath2(Ctx *ctx, char *buf, size_t bufsiz, knh_bytes_t path, char *ext)
//{
//	knh_intptr_t i, hasUTF8 = 0;
//	if(knh_bytes_startsWith(path, STEXT("file:"))) {
//		path = knh_bytes_last(path, 5);
//	}
//	if(ext == NULL) {
//		knh_format_bytes(buf, bufsiz, path);
//	}
//	else {
//		knh_format_join2(buf, bufsiz, path, B(ext));
//		DBG2_P("'%s'", buf);
//	}
//	for(i = 0; buf[i] != 0; i++) {
//		if(buf[i] == '/' || buf[i] == '\\') {
//			buf[i] = KONOHA_OS_FILE_SEPARATOR;
//		}
//		if(buf[i] < 0) hasUTF8 = 1;
//	}
//	if(hasUTF8) {
//		TODO();
//	}
//	return buf;
//}
//
///* ------------------------------------------------------------------------ */
//
//char *
//knh_format_parentpath(char *buf, size_t bufsiz, knh_bytes_t path, int n)
//{
//	int i, c = 0;
//	for(i = path.len - 1; i >= 0; i--) {
//		if(path.buf[i] == '/' || path.buf[i] == '\\') {
//			c++;
//			if(n <= c) {
//				path.len = i;
//				return knh_format_bytes(buf, bufsiz, path);
//			}
//		}
//	}
//	buf[0] = 0;
//	return buf;
//}
//
//
///* ------------------------------------------------------------------------ */
//
//char *
//knh_format_nzpath(char *buf, size_t bufsiz, knh_bytes_t path)
//{
//	//size_t i, j = 0;
//	int i, j = 0;
//	for(i = 0; i < path.len; i++) {
//		if(path.buf[i] == '/' || path.buf[i] == '\\') {
//			int ch = path.buf[i];
//			if(path.buf[i+1] == '.' && path.buf[i+2] == '.' && path.buf[i+3] == ch) {
//				i = i + 2;
//				for(; j >= 0; j--) {
//					if(buf[j] == ch) {
//						buf[j] = 0;
//						break;
//					}
//					buf[j] = 0;
//				}
//				continue;
//			}
//		}
//		if(j == bufsiz - 1) {
//			buf[j] = 0;
//			return buf;
//		}
//		buf[j] = (path.buf[i] == '\\') ? '/' : path.buf[i];
//		j++; buf[j]= 0;
//	}
//	buf[j] = 0;
//	return buf;
//}
//
///* ------------------------------------------------------------------------ */
//
//char *
//knh_format_catpath(char *buf, size_t bufsiz, knh_bytes_t path, knh_bytes_t file)
//{
//	if(file.buf[0]=='/' || file.buf[0] == '\\' || path.buf[0] == 0) {
//		return knh_format_nzpath(buf, bufsiz, file);
//	}
//	else {
//		char buff[FILEPATH_BUFSIZ];
//		knh_snprintf(buff, sizeof(buff), "%s/%s", (char*)path.buf, (char*)file.buf);
//		return knh_format_nzpath(buf, bufsiz, B(buff));
//	}
//}

/* ======================================================================== */
/* [file] */

char* knh_cwb_ospath(Ctx *ctx, knh_cwb_t* cwb)
{
	knh_bytes_t path = knh_cwb_tobytes(cwb);
	int hasUTF8 = 0;
	if(knh_bytes_startsWith(path, STEXT("file:"))) {
		knh_Bytes_remove(ctx, cwb->ba, cwb->pos, 5);
	}
	{
		size_t i;
		for(i = 0; i < path.len; i++) {
			int ch = path.buf[i];
			if(ch == '/' || ch == '\\') {
				path.buf[i] = KONOHA_OS_FILE_SEPARATOR;
			}
			if(ch > 127) hasUTF8 = 1;
		}
	}
	if(hasUTF8) {
		TODO();
	}
	return knh_cwb_tochar(ctx, cwb);
}

/* ------------------------------------------------------------------------ */

char* knh_cwb_realpath(Ctx *ctx, knh_cwb_t *cwb)
{
	char *p = knh_cwb_tochar(ctx, cwb);
#if defined(KNH_USING_POSIX)
	p = realpath(p, NULL);
	if(p != NULL) {
		knh_cwb_subclear(cwb, 0);
		knh_Bytes_write(ctx, cwb->ba, B(p));
		free(p);
		p = knh_cwb_tochar(ctx, cwb);
	}
#else
	TODO();
#endif
	return p;
}

/* ------------------------------------------------------------------------ */

knh_boolean_t knh_cwb_isfile(Ctx *ctx, knh_cwb_t *cwb)
{
	char *pathname = knh_cwb_tochar(ctx, cwb);
#if defined(KNH_USING_WINDOWS)
	DWORD attr = GetFileAttributesA(pathname);
	if(attr == -1) return 0;
	if((attr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) return 0;
	return 1;
#elif defined(KNH_USING_POSIX)
    struct stat buf;
	if(stat(pathname, &buf) == -1) return 0;
	return S_ISREG(buf.st_mode);
#elif defined(KNH_USING_BTRON)
	FILE* fp = fopen(pathname,"r");
	if(fp == NULL) {
		return 0;
	}
	fclose(fp);
	return 1;
#else
	TODO();
	return 0;
#endif
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_cwb_isdir(Ctx *ctx, knh_cwb_t *cwb)
{
	char *pathname = knh_cwb_tochar(ctx, cwb);
#if defined(KNH_USING_WINDOWS)
	DWORD attr = GetFileAttributesA(pathname);
	if(attr == -1) return 0;
	return ((attr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);
#elif defined(KNH_USING_POSIX)
    struct stat buf;
	if(stat(pathname, &buf) == -1) return 0;
	return S_ISDIR(buf.st_mode);
#else
	return 0;
#endif
}

///* ------------------------------------------------------------------------ */
//
//knh_boolean_t knh_isdir(Ctx *ctx, knh_bytes_t path)
//{
//#if defined(KNH_USING_WINDOWS)
//	char pathname[FILEPATH_BUFSIZ];
//	knh_format_ospath(ctx, pathname, sizeof(pathname), path);
//	DWORD attr = GetFileAttributesA(pathname);
//	if(attr == -1) return 0;
//	return ((attr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);
//#elif defined(KNH_USING_POSIX)
//	char pathname[FILEPATH_BUFSIZ];
//	knh_format_ospath(ctx, pathname, sizeof(pathname), path);
//    struct stat buf;
//	if(stat(pathname, &buf) == -1) return 0;
//	return S_ISDIR(buf.st_mode);
//#else
//	return 0;
//#endif
//}

///* ------------------------------------------------------------------------ */
//
//knh_boolean_t knh_isfile(Ctx *ctx, knh_bytes_t path)
//{
//#if defined(KNH_USING_WINDOWS)
//	char pathname[FILEPATH_BUFSIZ];
//	knh_format_ospath(ctx, pathname, sizeof(pathname), path);
//	DWORD attr = GetFileAttributesA(pathname);
//	if(attr == -1) return 0;
//	if((attr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) return 0;
//	return 1;
//#elif defined(KNH_USING_POSIX)
//	char pathname[FILEPATH_BUFSIZ];
//	knh_format_ospath(ctx, pathname, sizeof(pathname), path);
//    struct stat buf;
//	if(stat(pathname, &buf) == -1) return 0;
//	return S_ISREG(buf.st_mode);
//#elif defined(KNH_USING_BTRON)
//	char pathname[FILEPATH_BUFSIZ];
//	knh_format_ospath(ctx, pathname, sizeof(pathname), path);
//	FILE* fp = fopen(pathname,"r");
//	if(fp == NULL){
//            return 0;
//	}
//	fclose(fp);
//	return 1;
//#else
//	return 0;
//#endif
//}

/* ------------------------------------------------------------------------ */

#define SUBPATH_BUFSIZ 40

knh_bool_t knh_cwb_parentpath(Ctx *ctx, knh_cwb_t *cwb, char *subbuf)
{
	knh_bytes_t path = knh_cwb_tobytes(cwb);
	knh_intptr_t i;
	for(i = path.len - 1; i > 0; i--) {
		if(path.buf[i] == '/' || path.buf[i] == '\\') {
			if(subbuf != NULL) {
				knh_snprintf(subbuf, SUBPATH_BUFSIZ, "%s", (char*)path.buf + i);
			}
			knh_cwb_subclear(cwb, i);
			return 1;
		}
	}
	knh_cwb_subclear(cwb, 0);
	return 0;
}

/* ------------------------------------------------------------------------ */

static
knh_bool_t knh_cwb_mkdir(Ctx *ctx, knh_cwb_t *cwb, char *subpath, int isThrowable)
{
	char *pathname;
	if(!knh_cwb_isdir(ctx, cwb)) {
		char subbuf[SUBPATH_BUFSIZ];
		if(knh_cwb_parentpath(ctx, cwb, subbuf)) {
			if(knh_cwb_mkdir(ctx, cwb, subpath, isThrowable)) {
				knh_cwb_write(ctx, cwb, B(subbuf));
			}
			else {
				return 0;
			}
		}
	}
	pathname = knh_cwb_tochar(ctx, cwb);
#if defined(KNH_USING_WINDOWS)
	if(!CreateDirectoryA(pathname, NULL)) {
		KNH_PERRNO(ctx, cwb, "OS!!", "CreateDirectory", isThrowable);
		return 0;
	}
	return 1;
#elif defined(KNH_USING_POSIX)
	if(mkdir(pathname, 0777) == -1) {
		KNH_PERRNO(ctx, cwb, "OS!!", "mkdir", isThrowable);
		return 0;
	}
	return 1;
#else
	KNH_NOAPI(ctx, cwb, isThrowable);
	return 0;
#endif
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_mkdir(Ctx *ctx, knh_bytes_t path, int isThrowable)
{
	knh_cwb_t cwbbuf, *cwb = knh_cwb_openinit(ctx, &cwbbuf, path);
	knh_bool_t res = 1;
	knh_cwb_ospath(ctx, cwb);
	if(!knh_cwb_isdir(ctx, cwb)) {
		knh_cwb_realpath(ctx, cwb);
		res = knh_cwb_mkdir(ctx, cwb, NULL, isThrowable);
	}
	knh_cwb_close(cwb);
	return res;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_unlink(Ctx *ctx, knh_bytes_t path, int isThrowable)
{
	knh_cwb_t cwbbuf, *cwb = knh_cwb_openinit(ctx, &cwbbuf, path);
	char *pathname = knh_cwb_ospath(ctx, cwb);
	int res = 1;
#if defined(KNH_USING_POSIX)
	if(unlink(pathname) == -1) {
		KNH_PERRNO(ctx, cwb, "OS!!", "unlink", isThrowable);
		res = 0;
	}
#elif defined(KNH_USING_WINDOWS)
	if(DeleteFileA(pathname) == 0) {
		KNH_PERRNO(ctx, cwb, "OS!!", "DeleteFile", isThrowable);
		res = 0;
	}
#else
	KNH_NOAPI(ctx, cwb, isThrowable);
#endif
	knh_cwb_close(cwb);
	return res;
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_rename(Ctx *ctx, knh_bytes_t on, knh_bytes_t nn, int isThrowable)
{
	knh_cwb_t cwbbuf, *cwb = knh_cwb_openinit(ctx, &cwbbuf, on);
	char *pathname = knh_cwb_ospath(ctx, cwb);
	knh_cwb_t cwbbuf2, *cwb2 = knh_cwb_openinit(ctx, &cwbbuf2, nn);
	char *pathname2 = knh_cwb_ospath(ctx, cwb2);
	int res = 1;
#if defined(KNH_USING_POSIX)
	if(rename(pathname, pathname2) == -1) {
		KNH_PERRNO(ctx, cwb, "OS!!", "rename", isThrowable);
		res = 0;
	}
#elif defined(KNH_USING_WINDOWS)
	if(MoveFileA(pathname, pathname2) == 0) {
		KNH_PERRNO(ctx, cwb, "OS!!", "MoveFile", isThrowable);
		res = 0;
	}
#else
	KNH_NOAPI(ctx, isThrowable);
#endif
	knh_cwb_close(cwb);
	return res;
}

/* ======================================================================== */
/* [homepath] */

// $konoha.path /usr/local/konoha
// $konoha.bin.path  /usr/local/bin/konoha
// $konoha.package.path {$konoha.path}/package
// $konoha.script.path  {$konoha.path}/script

void knh_System_initPath(Ctx *ctx, System *o)
{
	knh_System_struct *sys = DP(o);
	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
	char *homepath = knh_getenv("KONOHA_HOME");
	knh_bytes_t home;
#if defined(KNH_PREFIX)
	if(homepath != NULL) {
		homepath = KNH_PREFIX "/kohoha";
	}
#endif
	if(homepath != NULL) {
		knh_DictMap_set(ctx, sys->props, T("konoha.path"), UP(T(homepath)));
	}
#if defined(KNH_USING_WINDOWS)
	{
		char bufl[FILEPATH_BUFSIZ];
		HMODULE h = LoadLibrary(NULL);
		GetModuleFileNameA(h, buf, bufsiz);
		knh_cwb_write(ctx, cwb, B(bufl));
		knh_DictMap_set(ctx, sys->props,
			T("konoha.bin.path"), UP(new_String__cwb(ctx, cwb)));
		if(homepath == NULL) {
			GetModuleFileNameA(h, buf, bufsiz);
			knh_cwb_write(ctx, cwb, B(bufl));
			knh_cwb_parentpath(ctx, cwb, NULL);
			knh_cwb_parentpath(ctx, cwb, NULL);
			homepath = knh_cwb_tochar(ctx, cwb);
			knh_DictMap_set(ctx, sys->props,
				T("konoha.path"), UP(new_String__cwb(ctx, cwb)));
		}
	}
#elif defined(KONOHA_ON_LINUX)
	// @url(http://shinh.skr.jp/binary/b2con.html)
	// http://doc.trolltech.com/3.3/qapplication.html#applicationDirPath
	{
		char bufl[FILEPATH_BUFSIZ];
		readlink("/proc/self/exe", buf, bufsiz);
		knh_cwb_write(ctx, cwb, B(bufl));
		knh_DictMap_set(ctx, sys->props,
			T("konoha.bin.path"), UP(new_String__cwb(ctx, cwb)));
		if(homepath == NULL) {
			readlink("/proc/self/exe", buf, bufsiz);
			knh_cwb_write(ctx, cwb, B(bufl));
			knh_cwb_parentpath(ctx, cwb, NULL);
			knh_cwb_parentpath(ctx, cwb, NULL);
			homepath = knh_cwb_tochar(ctx, cwb);
			knh_DictMap_set(ctx, sys->props,
				T("konoha.path"), UP(new_String__cwb(ctx, cwb)));
		}
	}
#elif defined(KONOHA_ON_MACOSX)
	{
		char *s = (char*)_dyld_get_image_name(0);
		s = realpath(s, NULL);
		knh_cwb_write(ctx, cwb, B(s));
		knh_DictMap_set(ctx, sys->props,
			T("konoha.bin.path"), UP(new_String__cwb(ctx, cwb)));
		if(homepath == NULL) {
			knh_cwb_write(ctx, cwb, B(s));
			knh_cwb_parentpath(ctx, cwb, NULL);
			knh_cwb_parentpath(ctx, cwb, NULL);
			homepath = knh_cwb_tochar(ctx, cwb);
			knh_DictMap_set(ctx, sys->props,
				T("konoha.path"), UP(new_String__cwb(ctx, cwb)));
		}
		free(s);
	}
#else
	homepath = "/konoha"
	knh_DictMap_set(ctx, sys->props,
		T("konoha.path"), UP(T(homepath)));
#endif
	KNH_ASSERT(homepath != NULL);
	home = B(homepath);
	/* $konoha.package.path {$konoha.path}/package */
	knh_cwb_subclear(cwb, 0);
	knh_cwb_write(ctx, cwb, home);
	knh_cwb_write(ctx, cwb, STEXT("/package"));
	knh_DictMap_set(ctx, sys->props,
		T("konoha.package.path"), UP(new_String__cwb(ctx, cwb)));

	/* $konoha.script.path {$konoha.path}/script */
	knh_cwb_write(ctx, cwb, home);
	knh_cwb_write(ctx, cwb, STEXT("/script"));
	knh_DictMap_set(ctx, sys->props, T("konoha.script.path"), UP(new_String__cwb(ctx, cwb)));

	homepath = knh_getenv("HOME");
	if(homepath != NULL) {
		/* $user.path */
		knh_cwb_write(ctx, cwb, home);
		knh_cwb_putc(ctx, cwb, '/');
		knh_cwb_write(ctx, cwb, STEXT(KONOHA_FOLDER));
		homepath = knh_cwb_tochar(ctx, cwb); home = B(homepath);
		knh_DictMap_set(ctx, sys->props, T("user.path"), UP(new_String__cwb(ctx, cwb)));
		/* $konoha.temp.path ${user.path}/temp */
		knh_cwb_write(ctx, cwb, home);
		knh_cwb_write(ctx, cwb, STEXT("/temp"));
		knh_DictMap_set(ctx, sys->props, T("konoha.temp.path"), UP(new_String__cwb(ctx, cwb)));

		/* $user.package.path ${user.path}/package */
		knh_cwb_write(ctx, cwb, home);
		knh_cwb_write(ctx, cwb, STEXT("/package"));
		knh_DictMap_set(ctx, sys->props, T("user.package.path"), UP(new_String__cwb(ctx, cwb)));

		/* $user.script.path ${user.path}/script */
		knh_cwb_write(ctx, cwb, home);
		knh_cwb_write(ctx, cwb, STEXT("/script"));
		knh_DictMap_set(ctx, sys->props, T("user.script.path"), UP(new_String__cwb(ctx, cwb)));
	}
	else {
#if defined(KONOHA_ON_WINDOWS)
		knh_cwb_write(ctx, cwb, STEXT("\\Temp"));
#else
		knh_cwb_write(ctx, cwb, STEXT("/tmp"));
#endif
		knh_DictMap_set(ctx, sys->props, T("konoha.temp.path"), UP(new_String__cwb(ctx, cwb)));
	}
}

/* ======================================================================== */

#ifdef __cplusplus
}
#endif

