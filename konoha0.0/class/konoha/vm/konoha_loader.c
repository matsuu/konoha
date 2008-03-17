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

#include"commons.h"

#ifdef KONOHA_USING_DL
#include<dlfcn.h>              /* @using dl -ldl */
#endif

/* ------------------------------------------------------------------------ */

#ifdef KONOHA_OS__MACOSX
	#define KNH_LOADER_DLL_SUPPORTED       1
	#define KNH_LOADER_DLL_PREFIX          "lib"
	#define KNH_LOADER_DLL_EXT             ".dylib"
#endif

/* ------------------------------------------------------------------------ */

#ifdef KONOHA_OS__LINUX
	#define KNH_LOADER_DLL_PREFIX          "lib"
	#define KNH_LOADER_DLL_EXT             ".so"
	#define KNH_LOADER_DLL_WITH_VERSION    1
#endif

/* ------------------------------------------------------------------------ */

#ifdef KONOHA_OS__CYGWIN
	#define KNH_LOADER_DLL_PREFIX          "/usr/lib/lib"
	#define KNH_LOADER_DLL_EXT             ".dll"
	#define KNH_LOADER_DLL_WITH_VERSION    1
#endif

/* ------------------------------------------------------------------------ */

#ifdef KONOHA_OS__WIN32
//	#define KNH_LOADER_DLL_SUPPORTED       1
	#define KNH_LOADER_DLL_EXT             "dll"
#endif


/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */
/* [global] */

static DictSet *knh_FuncDictSet = NULL;
static DictSet *knh_LibDictSet = NULL;

/* ------------------------------------------------------------------------ */

void knh_loader_ginit()
{
	DEBUG_ASSERT(knh_LibDictSet == NULL);
	KNH_INITv(knh_LibDictSet, new_DictSet(NULL, 8));
	KNH_INITv(knh_FuncDictSet, new_DictSet(NULL, 16));
}

/* ------------------------------------------------------------------------ */

void knh_loader_gtraverse(Ctx *ctx, f_gc gc)
{
	if(IS_SWEEP(gc)) {
		int i;
		for(i = 0; i < knh_LibDictSet->size; i++) {
#if defined(KONOHA_USING_DL)
			void *dlhdr = (void*)knh_DictSet_value(knh_LibDictSet, i);
			dlclose(dlhdr);
#endif
		}
	}
	gc(ctx, knh_LibDictSet);
	gc(ctx, knh_FuncDictSet);
	if(IS_SWEEP(gc)) {
		knh_LibDictSet = NULL;
		knh_FuncDictSet = NULL;
	}
}

/* ======================================================================== */
/* [FuncDictSet] */

void KNH_TFUNC(Ctx *ctx, char *funcname, void *func)
{
	if(func != NULL) {
		knh_DictSet_set(ctx, knh_FuncDictSet, new_String__fast(ctx, CLASS_String, B(funcname)), (knh_uint_t)func);
	}
}

/* ------------------------------------------------------------------------ */

void *
knh_system_loadBuiltInFunc(Ctx *ctx, knh_bytes_t funcname, void *deffunc)
{
	void *func = (void*)knh_DictSet_get__b(knh_FuncDictSet, funcname);
	if(func == NULL) {
		return deffunc;
	}
	DEBUG("using built-in function: %s", funcname.buf);
	return func;
}

/* ======================================================================== */
/* [LibDictSet] */

void *
knh_system_loadFunc(Ctx *ctx, char *dirname, char *libname, char *funcname, void *deffunc)
{
#if defined(KONOHA_USING_DL)
#define IMPL_knh_loader_loaddll
	char bufn[KONOHA_FILEN_SIZE];
	knh_snprintf(bufn, sizeof(bufn), "%s%s%s", KNH_LOADER_DLL_PREFIX, libname, KNH_LOADER_DLL_EXT);

	char bufp[KONOHA_FILEN_SIZE];
	if(dirname == NULL) {
		knh_system_path(bufp, sizeof(bufp), "lib", bufn);
	}
	else {
		knh_snprintf(bufp, sizeof(bufp), "%s/%s", dirname, bufn);
	}
	
	void *dlhdr = (void*)knh_DictSet_get__b(knh_LibDictSet, B(bufn));

	if(dlhdr == NULL) {
		//DEBUG("Opening dll %s ..", bufp);
		dlhdr = dlopen(bufp, RTLD_LAZY);
		if (!dlhdr && dirname == NULL) {
			//DEBUG("Opening dll %s ..", bufn);
    		dlhdr = dlopen(bufn, RTLD_LAZY);
    	}
		if (!dlhdr) {
			KNH_NOTICE("cannot open '%s': %s", bufn, dlerror());
    		return NULL;
    	}
		knh_DictSet_set(ctx, knh_LibDictSet, new_String__fast(ctx, CLASS_String, B(bufn)), (knh_uint_t)dlhdr);
	}
	
	void *func = dlsym(dlhdr, funcname);
	if(func == NULL) {
		KNH_NOTICE("not found %s: %s", funcname, dlerror());
		return deffunc;
	}
	return func;
#endif

#if !defined(IMPL_knh_loader_loaddll)
	KNH_NOTICE("unsupported");
	return deffunc;
#endif
}

/* ------------------------------------------------------------------------ */

void *knh_system_loadPackageFunc(Ctx *ctx, knh_bytes_t pname, knh_bytes_t fname)
{
#ifdef KONOHA_MONOLITHIC
	return knh_system_loadBuiltInFunc(ctx, fname, NULL);
#else
	void *func;
	char bufp[KONOHA_FILEN_SIZE];
	knh_index_t idx;

	func = knh_system_loadBuiltInFunc(ctx, fname, NULL);
	if(func != NULL) {
		return func;
	}
	
	knh_system_path(bufp, sizeof(bufp), "package", (char*)pname.buf);
	idx = knh_bytes_rindex(pname, '.');
	if(idx != -1) {
		pname = knh_bytes_last(pname, idx + 1);
	}
	return knh_system_loadFunc(ctx, bufp, (char*)pname.buf, (char*)fname.buf, NULL);
#endif/*KONOHA_MONOLITHIC*/
}

/* ------------------------------------------------------------------------ */

void *knh_system_loadDriverFunc(Ctx *ctx, knh_bytes_t drvname, char *funcbase, void *deffunc)
{
#ifdef KONOHA_MONOLITHIC
	char buff[KONOHA_FILEN_SIZE];
	knh_snprintf(buff, sizeof(buff), "%s__%s", funcbase, (char*)drvname.buf);
	return knh_system_loadBuiltInFunc(ctx, B(buff), deffunc);
#else
	char buff[KONOHA_FILEN_SIZE];
	char bufp[KONOHA_FILEN_SIZE];
	void *func;
	knh_snprintf(buff, sizeof(buff), "%s__%s", funcbase, (char*)drvname.buf);
	func = knh_system_loadBuiltInFunc(ctx, B(buff), NULL);
	if(func != NULL) {
		return func;
	}
	knh_system_path(bufp, sizeof(bufp), "driver", (char*)drvname.buf);
	return knh_system_loadFunc(ctx, bufp, (char*)drvname.buf, buff, deffunc);
#endif/*KONOHA_MONOLITHIC*/
}

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
