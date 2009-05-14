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

#define KNH_USING_NOAPI 1

#ifdef KNH_USING_POSIX
#undef KNH_USING_NOAPI
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

#endif/*KNH_USING_POSIX*/

#ifdef KNH_USING_WINDOWS
#undef KNH_USING_NOAPI
#include<windows.h>
#endif


/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [file] */

int knh_isfile(Ctx *ctx, knh_bytes_t path)
{
	char dirname[FILENAME_BUFSIZ];
	knh_format_ospath(ctx, dirname, sizeof(dirname), path);
#ifdef KNH_USING_WINDOWS
	DWORD attr = GetFileAttributesA(dirname);
	if(attr == -1) return 0;
	if((attr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) return 0;
	return 1;
#endif/*KNH_USING_WINDOWS*/
#ifdef KNH_USING_POSIX
    struct stat buf;
	if(stat(dirname, &buf) == -1) return 0;
	return S_ISREG(buf.st_mode);
#endif/*KNH_USING_POSIX*/
#ifdef KNH_USING_NOAPI
	return 0;
#endif
}

/* ------------------------------------------------------------------------ */

int knh_isdir(Ctx *ctx, knh_bytes_t path)
{
	char dirname[FILENAME_BUFSIZ];
	knh_format_ospath(ctx, dirname, sizeof(dirname), path);
#ifdef KNH_USING_WINDOWS
	DWORD attr = GetFileAttributesA(dirname);
	if(attr == -1) return 0;
	return ((attr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);
#endif
#ifdef KNH_USING_NOAPI
	return 0;
#endif/*KNH_USING_WINDOWS*/
#ifdef KNH_USING_POSIX
    struct stat buf;
	if(stat(dirname, &buf) == -1) return 0;
	return S_ISDIR(buf.st_mode);
#endif/*KNH_USING_POSIX*/
#ifdef KNH_USING_NOAPI
	return 0;
#endif
}

/* ======================================================================== */
/* [homepath] */

char *
knh_format_homepath(char *buf, size_t bufsiz)
{
	// @url(http://shinh.skr.jp/binary/b2con.html)
	char bufl[FILENAME_BUFSIZ];
#ifdef KNH_USING_WINDOWS
#define HOMEPATH
	HMODULE h = LoadLibrary(NULL);
	GetModuleFileNameA(h, buf, bufsiz);
	knh_format_nzpath(bufl, sizeof(bufl), B(buf));
	//DBG2_P("nzpath='%s'", bufl);
	knh_format_parentpath(buf, bufsiz, B(bufl), 2);
#endif/*KNH_USING_WINDOWS*/
#ifdef KNH_USING_POSIX
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
#ifndef HOMEPATH
	knh_snprintf(bufl, sizeof(bufl), "/usr/konoha");
#endif
#endif/*KNH_USING_POSIX*/
#ifdef KNH_USING_NOAPI
	knh_snprintf(bufl, sizeof(bufl), "/Konoha");
#endif
	return buf;
}

/* ======================================================================== */

#ifdef __cplusplus
}
#endif

