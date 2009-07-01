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

#ifdef KONOHA_ON_LKM
#undef KNH_USING_POSIX
#endif

#ifdef KNH_USING_POSIX
#include <unistd.h>
#include<dlfcn.h>

#include<time.h>
#include<sys/time.h>
#endif

#ifdef KNH_USING_WINDOWS
#include<windows.h>
#endif


/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [dlopen] */

void *knh_dlopen(Ctx *ctx, const char* path, int mode)
{
#if defined(KNH_USING_WINDOWS)
	char buff[FILEPATH_BUFSIZ];
	knh_format_ospath(ctx, buff, sizeof(buff), B((char*)path));
	DBG_P("knh_dlopen .. '%s'\n", buff);
	return (void*)LoadLibraryA((LPCTSTR)buff);
#elif defined(KNH_USING_POSIX)
	char buff[FILEPATH_BUFSIZ];
	knh_format_ospath(ctx, buff, sizeof(buff), B((char*)path));
	DBG_P("knh_dlopen .. '%s'\n", buff);
	return dlopen(buff, mode);
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
#else
	return 0;
#endif
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
