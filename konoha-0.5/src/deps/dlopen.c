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

#ifdef KNH_USING_POSIX
#include<unistd.h>
#include<dlfcn.h>
#endif

#ifdef KNH_USING_WINDOWS
#include<windows.h>
#endif

#ifdef KNH_USING_BTRON
#include<btron/file.h>
#include<btron/dynload.h>
#include<tstring.h>
#endif


/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [dlopen] */

void *knh_dlopen(Ctx *ctx, knh_bytes_t libname)
{
#if defined(KNH_USING_WINDOWS)
	char buff[FILEPATH_BUFSIZ];
	if(knh_bytes_endsWith(libname, STEXT(KONOHA_OS_DLLEXT))) {
		knh_format_ospath(ctx, buff, sizeof(buff), libname);
	}
	else {
		knh_format_ospath2(ctx, buff, sizeof(buff), libname, KONOHA_OS_DLLEXT);
	}
	DBG_P("knh_dlopen .. '%s'\n", buff);
	return (void*)LoadLibraryA((LPCTSTR)buff);
#elif defined(KNH_USING_POSIX)
	char buff[FILEPATH_BUFSIZ];
	if(knh_bytes_endsWith(libname, STEXT(KONOHA_OS_DLLEXT))) {
		knh_format_ospath(ctx, buff, sizeof(buff), libname);
	}
	else {
		knh_format_ospath2(ctx, buff, sizeof(buff), libname, KONOHA_OS_DLLEXT);
	}
	DBG_P("knh_dlopen .. '%s'\n", buff);
	return dlopen(buff, RTLD_LAZY);
#elif defined(KNH_USING_BTRON)
        char buff[FILEPATH_BUFSIZ];
        TC buff_tc[FILEPATH_BUFSIZ];
        LINK lnk;
        W err;
	if(knh_bytes_endsWith(libname, STEXT(KONOHA_OS_DLLEXT))) {
		knh_format_ospath(ctx, buff, sizeof(buff), libname);
	}
	else {
		knh_format_ospath2(ctx, buff, sizeof(buff), libname, KONOHA_OS_DLLEXT);
	}
	DBG_P("knh_dlopen .. '%s'\n", buff);
        eucstotcs(buff_tc, buff);
        err = b_get_lnk(buff_tc, &lnk, F_NORM);
        if (err < 0) {
            return NULL;
        }
        err = b_dlopen(&lnk, DL_LAZY);
        if (err <= 0) {
            return NULL;
        }
        // Be careful that BTRON dlopen handles are of type W, not void*!
        return (void*)err;
#else
	return NULL;
#endif
}

/* ------------------------------------------------------------------------ */

void *knh_dlsym(Ctx *ctx, void* hdr, const char* symbol)
{
#if defined(KNH_USING_WINDOWS)
    return GetProcAddress((HMODULE)hdr, (LPCSTR)symbol);
#elif defined(KNH_USING_POSIX)
    return dlsym(hdr, symbol);
#elif defined(KNH_USING_BTRON)
    UW val = NULL;
    W err = b_dlsym((W)hdr, symbol, &val);
    if (err < 0) {
        return NULL;
    }
    return val;
#else
    return NULL;
#endif
}

/* ------------------------------------------------------------------------ */

const char *knh_dlerror(Ctx *ctx)
{
#if defined(KNH_USING_WINDOWS)
    return "TODO: dlerror()";
#elif defined(KNH_USING_POSIX)
    return dlerror();
#else
    return "Unsupported dlopen APIs";
#endif
}

/* ------------------------------------------------------------------------ */

int knh_dlclose(Ctx *ctx, void* hdr)
{
#if defined(KNH_USING_WINDOWS)
    return (int)FreeLibrary((HMODULE)hdr);
#elif defined(KNH_USING_POSIX)
    return dlclose(hdr);
#elif defined(KNH_USING_BTRON)
    return b_dlclose((W)hdr);
#else
    return 0;
#endif
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
