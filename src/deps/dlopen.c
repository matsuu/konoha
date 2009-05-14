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
#include<dlfcn.h>

#include<time.h>
#include<sys/time.h>
#endif

#ifdef KNH_USING_WINDOWS
#undef KNH_USING_NOAPI
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
	char buff[FILENAME_BUFSIZ];
	knh_format_ospath(ctx, buff, sizeof(buff), B((char*)path));
	DBG_P("dlopen .. '%s'\n", buff);
#ifdef KNH_USING_WINDOWS
	return (void*)LoadLibraryA((LPCTSTR)buff);
#endif
#ifdef KNH_USING_POSIX
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

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
