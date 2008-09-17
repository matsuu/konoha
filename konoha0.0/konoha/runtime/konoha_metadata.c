///****************************************************************************
// * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER  
// * 
// * Copyright (c) 2005-2008, Kimio Kuramitsu <kimio at ynu.ac.jp>
// *           (c) 2008-      Konoha Software Foundation  
// * All rights reserved.
// * 
// * You may choose one of the following two licenses when you use konoha. 
// * See www.konohaware.org/license.html for further information.
// * 
// * (1) GNU General Public License 2.0      (with    KONOHA_UNDER_GPL2)
// * (2) Konoha Software Foundation License 1.0
// * 
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER 
// * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// *  
// ****************************************************************************/
//
///* ************************************************************************ */
//
//#include"commons.h"
//
///* ************************************************************************ */
//
//#ifdef __cplusplus 
//extern "C" {
//#endif
//
///* ======================================================================== */
///* [global] */
//
//#define tmeta(ctx) ((Context*)ctx)->runtime->tmetaHashMap
//
///* ======================================================================== */
///* [methods] */
//
//void knh_metadata_set(Ctx *ctx, Object *b, String *key, Any *value)
//{
//	DictMap *dm = (DictMap*)knh_HashMap_get(ctx, tmeta(ctx), (knh_uint_t)b, NULL);
//	if(IS_NOTNULL(value)) {
//		if(IS_NULL(dm)) {
//			dm = new_DictMap(ctx, 2);
//			knh_HashMap_put(ctx, tmeta(ctx), (knh_uint_t)b, NULL, dm);
//			knh_Object_setMetaData(b, 1);
//		}
//		knh_DictMap_put(ctx, dm, key, value);
//	}
//	else{
//		if(IS_NOTNULL(dm)) {
//			knh_DictMap_remove(ctx, dm, key);
//		}
//	}
//}
//
///* ------------------------------------------------------------------------ */
//
//Any *knh_metadata_get(Ctx *ctx, Object *b, knh_bytes_t key)
//{
//	if(knh_Object_hasMetaData(b)) {
//		DictMap *dm = (DictMap*)knh_HashMap_get(ctx, tmeta(ctx), (knh_uint_t)b, NULL);
//		if(IS_NOTNULL(dm)) {
//			return knh_DictMap_get__b(ctx, dm, key);
//		}
//	}
//	return KNH_NULL;
//}
//
///* ------------------------------------------------------------------------ */
//
//void knh_metadata_clear(Ctx *ctx, Object *b)
//{
//	DBG2_P("Removing metadata %p ..\n", b);
//	knh_Object_setMetaData(b, 0);
//	knh_HashMap_remove(ctx, tmeta(ctx), (knh_uint_t)b, NULL);
//}
//
///* ------------------------------------------------------------------------ */
//
////
////void knh_Object_setmeta(Ctx *ctx, Object *b, DictMap *dm)
////{
////	CHECK_knh_Object_setmeta;
////#ifdef OF_METADATA
////	KNH_ASSERT(!knh_Object_hasMetaData(b));
////	knh_HashMap_put(ctx, tmeta(ctx), (knh_uint_t)b, NULL, dm);
////	knh_Object_setflag(b, OF_METADATA);
////#endif
////}
////
/////* ------------------------------------------------------------------------ */
////
/////* @method[PRIVATE] DictMap Object.meta() */
////
////
////DictMap *knh_Object_meta(Ctx *ctx, Object *b)
////{
////#ifdef OF_METADATA
////	if(knh_Object_isflag(b, OF_METADATA)) {
////		return knh_HashMap_get(ctx, tmeta(ctx), (knh_uint_t)b, NULL);
////	}
////#endif
////	return KNH_NULL;
////}
//
//
//
//#ifdef __cplusplus
//}
//#endif
