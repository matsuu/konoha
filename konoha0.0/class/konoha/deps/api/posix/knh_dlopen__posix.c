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

//#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */
/* [dylib] */

//void *
//knh_dlopen(const char *path)
//{
//#if defined(KONOHA_USING_LIBDL)
//#define IMPL_knh_loader_loaddll
//	char buf[256];
//	if(dirname == NULL) {
//		knh_snprintf(buf, sizeof(buf), "%s%s%s", KNH_LOADER_DLL_PREFIX, libname, KNH_LOADER_DLL_EXT);
//	}
//	else {
//		knh_snprintf(buf, sizeof(buf), "%s/%s%s%s", dirname, KNH_LOADER_DLL_PREFIX, libname, KNH_LOADER_DLL_EXT);
//	}
//	void *dlhdr = (void*)knh_DictSet_get__b(tglobalLibDictSet, B(buf));
//	if(dlhdr == NULL) {
//		//DEBUG("Opening dll %s ..", buf);
//		dlhdr = dlopen(buf, RTLD_LAZY);
//    	if (!dlhdr) {
//    		KNH_NOTICE("cannot open '%s': %s", buf, dlerror());
//    		return NULL;
//    	}
//		knh_DictSet_set(ctx, tglobalLibDictSet, new_String__fast(ctx, CLASS_String, B(buf)), (knh_uint_t)dlhdr);
//	}
//	
//	void *func = dlsym(dlhdr, funcname);
//	if(func == NULL) {
//		KNH_NOTICE("not found %s: %s", funcname, dlerror());
//		return NULL;
//	}
//	return func;
//#endif
//#if !defined(IMPL_knh_loader_loaddll)
//	KNH_NOTICE("unsupported");
//	return NULL;
//#endif
//}
//
///* ------------------------------------------------------------------------ */
//
//void knh_tlib_test(Ctx *ctx)
//{
//	double (*f_cos)(double) = knh_loader_loaddll(ctx, NULL, "m", "cos");
//	printf ("%f\n", (*f_cos)(2.0));
//}
//
///* ======================================================================== */
///* [class] */
//
//void knh_loader_load_package(Ctx *ctx, char *pkgname)
//{
//	TODO();
//}
//
///* ------------------------------------------------------------------------ */
//
//IntUnit *knh_loader_loadIntUnit(Ctx *ctx, char *urn)
//{
//	TODO();
//	return KNH_NULL;
//}
//
///* ------------------------------------------------------------------------ */
//
//FloatUnit *knh_loader_loadFloatUnit(Ctx *ctx, char *urn)
//{
//	TODO();
//	return KNH_NULL;
//}
//
///* ------------------------------------------------------------------------ */
//
//Vocabulary *knh_loader_loadVocabulary(Ctx *ctx, char *urn)
//{
//	TODO();
//	return KNH_NULL;
//}
//
///* ------------------------------------------------------------------------ */
//
//Object *knh_loader_load_spec(Ctx *ctx, knh_class_t bcid, char *urn)
//{
//	switch(bcid) {
//	case CLASS_Int: 
//		return knh_loader_loadIntUnit(ctx, urn);
//	case CLASS_Float:
//		return knh_loader_loadFloatUnit(ctx, urn);
//	case CLASS_String:
//		return knh_loader_loadVocabulary(ctx, urn);
//	}
//	DEBUG("unsupported bcid = %s", CLASSN(bcid));
//	return KNH_NULL;
//}
//
///* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
