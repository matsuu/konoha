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

#include<konoha/konoha_dev.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

/* ======================================================================== */
/* [flag] */

METHOD knh__Object_isRelease(Ctx *ctx, Object **sfp)
{
	if(knh_Object_isRelease(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Object_isDebug(Ctx *ctx, Object **sfp)
{
	if(knh_Object_isDebug(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}
}

METHOD knh__Object_isImmutable(Ctx *ctx, Object **sfp)
{
	if(knh_Object_isImmutable(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Object_hasMetaData(Ctx *ctx, Object **sfp)
{
	if(knh_Object_hasMetaData(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Object_isSynchronized(Ctx *ctx, Object **sfp)
{
	if(knh_Object_isSynchronized(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Object_isModified(Ctx *ctx, Object **sfp)
{
	if(knh_Object_isModified(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Object_setModified(Ctx *ctx, Object **sfp)
{
	knh_Object_setModified(sfp[0], IS_TRUE(sfp[1]));
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__Class_isRelease(Ctx *ctx, Object **sfp)
{
	if(knh_class_isRelease(knh_Class_cid(sfp[0]))) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Class_isDebug(Ctx *ctx, Object **sfp)
{
	if(knh_class_isDebug(knh_Class_cid(sfp[0]))) {
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}
}

METHOD knh__Class_isImmutable(Ctx *ctx, Object **sfp)
{
	if(knh_class_isImmutable(knh_Class_cid(sfp[0]))) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Class_isMetaExtensible(Ctx *ctx, Object **sfp)
{
	if(knh_class_isMetaExtensible(knh_Class_cid(sfp[0]))) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Class_isPrivate(Ctx *ctx, Object **sfp)
{
	if(knh_class_isPrivate(knh_Class_cid(sfp[0]))) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Class_isPublic(Ctx *ctx, Object **sfp)
{
	if(knh_class_isPublic(knh_Class_cid(sfp[0]))) {
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}
}

METHOD knh__Class_isFinal(Ctx *ctx, Object **sfp)
{
	if(knh_class_isFinal(knh_Class_cid(sfp[0]))) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Class_isSystem(Ctx *ctx, Object **sfp)
{
	if(knh_class_isSystem(knh_Class_cid(sfp[0]))) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Class_isNA(Ctx *ctx, Object **sfp)
{
	if(knh_class_isNA(knh_Class_cid(sfp[0]))) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Method_isPublic(Ctx *ctx, Object **sfp)
{
	if(knh_Method_isPublic(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Method_isPrivate(Ctx *ctx, Object **sfp)
{
	if(knh_Method_isPrivate(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}
}

METHOD knh__Method_isVirtual(Ctx *ctx, Object **sfp)
{
	if(knh_Method_isVirtual(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Method_isFinal(Ctx *ctx, Object **sfp)
{
	if(knh_Method_isFinal(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}
}

METHOD knh__Method_isStatic(Ctx *ctx, Object **sfp)
{
	if(knh_Method_isStatic(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Method_isClass(Ctx *ctx, Object **sfp)
{
	if(knh_Method_isClass(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Method_isVarArgs(Ctx *ctx, Object **sfp)
{
	if(knh_Method_isVarArgs(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Method_isAspect(Ctx *ctx, Object **sfp)
{
	if(knh_Method_isAspect(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__MapMap_isInterface(Ctx *ctx, Object **sfp)
{
	if(knh_MapMap_isInterface(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__MapMap_isSignificant(Ctx *ctx, Object **sfp)
{
	if(knh_MapMap_isSignificant(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__MapMap_isSynonym(Ctx *ctx, Object **sfp)
{
	if(knh_MapMap_isSynonym(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__MapMap_isLossLess(Ctx *ctx, Object **sfp)
{
	if(knh_MapMap_isLossLess(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__MapMap_isTotal(Ctx *ctx, Object **sfp)
{
	if(knh_MapMap_isTotal(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__MapMap_isPartial(Ctx *ctx, Object **sfp)
{
	if(knh_MapMap_isPartial(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}
}

METHOD knh__MapMap_isStatic(Ctx *ctx, Object **sfp)
{
	if(knh_MapMap_isStatic(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__MapMap_isTemporal(Ctx *ctx, Object **sfp)
{
	if(knh_MapMap_isTemporal(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}
}

METHOD knh__MapMap_isLocal(Ctx *ctx, Object **sfp)
{
	if(knh_MapMap_isLocal(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__MapMap_isDerived(Ctx *ctx, Object **sfp)
{
	if(knh_MapMap_isDerived(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__IntUnit_isUnsigned(Ctx *ctx, Object **sfp)
{
	if(knh_IntUnit_isUnsigned(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Exception_isFatal(Ctx *ctx, Object **sfp)
{
	if(knh_Exception_isFatal(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Exception_isLogging(Ctx *ctx, Object **sfp)
{
	if(knh_Exception_isLogging(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

METHOD knh__Exception_isGenerated(Ctx *ctx, Object **sfp)
{
	if(knh_Exception_isGenerated(sfp[0])) {
		METHOD_RETURN(ctx, sfp, KNH_TRUE);
	}else{
		METHOD_RETURN(ctx, sfp, KNH_FALSE);
	}
}

/* ======================================================================== */
/* [method] */

METHOD knh__Array_new(Ctx *ctx, Object **sfp)
{
	/* method Array! Array.new(Int init)  */
	Object *rv = knh_Array_new(
		ctx,
		(knh_Array*)sfp[0],
		knh_IntNULL_toint(sfp[1]) /* Int sfp[1] => knh_int_t init */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Array_new__array(Ctx *ctx, Object **sfp)
{
	/* method Array! Array.new::array(Int init, Any value)  */
	Object *rv = knh_Array_new__array(
		ctx,
		(knh_Array*)sfp[0],
		knh_IntNULL_toint(sfp[1]) /* Int sfp[1] => knh_int_t init */,
		(Any*)sfp[2] /* Any sfp[2] => Any* value */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Array_new__init(Ctx *ctx, Object **sfp)
{
	/* method[VARARGS] Array! Array.new::init(Any value)  */
	Object *rv = knh_Array_new__init(
		ctx,
		(knh_Array*)sfp[0],
		knh_stackf_argc(ctx, &(sfp[1])),
		&(sfp[1])
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Array_get__fast(Ctx *ctx, Object **sfp)
{
	/* method Any Array.get::fast(Int! index)  */
	Object *rv = knh_Array_get__fast(
		(knh_Array*)sfp[0],
		(size_t)knh_Int_toint(sfp[1]) /* Int! sfp[1] => size_t index */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Array_set__fast(Ctx *ctx, Object **sfp)
{
	/* method void Array.set::fast(Int! index, Any value)  */
	knh_Array_set__fast(
		ctx,
		(knh_Array*)sfp[0],
		(size_t)knh_Int_toint(sfp[1]) /* Int! sfp[1] => size_t index */,
		(Object*)sfp[2] /* Any sfp[2] => Object* value */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__Array_get(Ctx *ctx, Object **sfp)
{
	/* method Any Array.get(Int! index)  */
	Object *rv = knh_Array_get(
		(knh_Array*)sfp[0],
		knh_Int_toint(sfp[1]) /* Int! sfp[1] => knh_int_t index */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Array_set(Ctx *ctx, Object **sfp)
{
	/* method void Array.set(Int! index, Any value)  */
	knh_Array_set(
		ctx,
		(knh_Array*)sfp[0],
		knh_Int_toint(sfp[1]) /* Int! sfp[1] => knh_int_t index */,
		(Any*)sfp[2] /* Any sfp[2] => Any* value */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__Bytes_new(Ctx *ctx, Object **sfp)
{
	/* method Bytes! Bytes.new(Int init=256)  */
	Object *rv = knh_Bytes_new(
		ctx,
		(knh_Bytes*)sfp[0],
		(size_t)knh_IntNULL_toint(sfp[1]) /* Int sfp[1] => size_t init */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Tuple_new(Ctx *ctx, Object **sfp)
{
	/* method[VARARGS] Tuple! Tuple.new(Any value)  */
	Object *rv = knh_Tuple_new(
		ctx,
		(Tuple*)sfp[0],
		knh_stackf_argc(ctx, &(sfp[1])),
		&(sfp[1])
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Tuple_getSize(Ctx *ctx, Object **sfp)
{
	/* method Int! Tuple.getSize()  */
	size_t v = knh_Tuple_getSize(
		(Tuple*)sfp[0]
	);
	Object* rv = new_Int(ctx, (knh_int_t)v) /* size_t v => Int rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Tuple_get__fast(Ctx *ctx, Object **sfp)
{
	/* method Any Tuple.get::fast(Int! index)  */
	Object *rv = knh_Tuple_get__fast(
		(Tuple*)sfp[0],
		knh_Int_toint(sfp[1]) /* Int! sfp[1] => knh_int_t index */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Tuple_get(Ctx *ctx, Object **sfp)
{
	/* method Any Tuple.get(Int! index)  */
	Object *rv = knh_Tuple_get(
		(Tuple*)sfp[0],
		knh_Int_toint(sfp[1]) /* Int! sfp[1] => knh_int_t index */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__DictIdx_index(Ctx *ctx, Object **sfp)
{
	/* method Int! DictIdx.index(String! term)  */
	knh_index_t v = knh_DictIdx_index(
		ctx,
		(knh_DictIdx*)sfp[0],
		knh_String_tobytes(sfp[1]) /* String! sfp[1] => knh_bytes_t v */
	);
	Object* rv = new_Int(ctx, v) /* knh_index_t v => Int rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__DictIdx_add__fast(Ctx *ctx, Object **sfp)
{
	/* method Int! DictIdx.add::fast(String! term)  */
	knh_index_t v = knh_DictIdx_add__fast(
		ctx,
		(knh_DictIdx*)sfp[0],
		(String*)sfp[1] /* String! sfp[1] => String* term */
	);
	Object* rv = new_Int(ctx, v) /* knh_index_t v => Int rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__DictIdx_add(Ctx *ctx, Object **sfp)
{
	/* method Int! DictIdx.add(String! term)  */
	knh_index_t v = knh_DictIdx_add(
		ctx,
		(knh_DictIdx*)sfp[0],
		(String*)sfp[1] /* String! sfp[1] => String* term */
	);
	Object* rv = new_Int(ctx, v) /* knh_index_t v => Int rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__DictIdx_get__fast(Ctx *ctx, Object **sfp)
{
	/* method String DictIdx.get::fast(Int! index)  */
	Object *rv = knh_DictIdx_get__fast(
		(knh_DictIdx*)sfp[0],
		knh_Int_toint(sfp[1]) /* Int! sfp[1] => knh_int_t termid */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__DictIdx_get(Ctx *ctx, Object **sfp)
{
	/* method String DictIdx.get(Int! index)  */
	Object *rv = knh_DictIdx_get(
		(knh_DictIdx*)sfp[0],
		knh_Int_toint(sfp[1]) /* Int! sfp[1] => knh_int_t termid */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__DictIdx_clear(Ctx *ctx, Object **sfp)
{
	/* method void DictIdx.clear()  */
	knh_DictIdx_clear(
		ctx,
		(knh_DictIdx*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__InputStream_readLine(Ctx *ctx, Object **sfp)
{
	/* method String InputStream.readLine()  */
	Object *rv = knh_InputStream_readLine(
		ctx,
		(knh_InputStream*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__InputStream_close(Ctx *ctx, Object **sfp)
{
	/* method void InputStream.close()  */
	knh_InputStream_close(
		ctx,
		(knh_InputStream*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__Array_add__fast(Ctx *ctx, Object **sfp)
{
	/* method void Array.add::fast(Any value)  */
	knh_Array_add__fast(
		ctx,
		(knh_Array*)sfp[0],
		(Any*)sfp[1] /* Any sfp[1] => Any* value */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__Array_add(Ctx *ctx, Object **sfp)
{
	/* method void Array.add(Any value)  */
	knh_Array_add(
		ctx,
		(knh_Array*)sfp[0],
		(Any*)sfp[1] /* Any sfp[1] => Any* value */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__Array_pop(Ctx *ctx, Object **sfp)
{
	/* method Any Array.pop()  */
	Object *rv = knh_Array_pop(
		ctx,
		(knh_Array*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Array_slice(Ctx *ctx, Object **sfp)
{
	/* method Array! Array.slice(Int start, Int end)  */
	Object *rv = knh_Array_slice(
		ctx,
		(knh_Array*)sfp[0],
		knh_IntNULL_toint(sfp[1]) /* Int sfp[1] => knh_int_t start */,
		knh_IntNULL_toint(sfp[2]) /* Int sfp[2] => knh_int_t end */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Array_clear(Ctx *ctx, Object **sfp)
{
	/* method void Array.clear()  */
	knh_Array_clear(
		ctx,
		(knh_Array*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__Socket_getInputStream(Ctx *ctx, Object **sfp)
{
	/* method InputStream! Socket.getInputStream()  */
	Object *rv = knh_Socket_getInputStream(
		ctx,
		(knh_Socket*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Socket_getOutputStream(Ctx *ctx, Object **sfp)
{
	/* method OutputStream! Socket.getOutputStream()  */
	Object *rv = knh_Socket_getOutputStream(
		ctx,
		(knh_Socket*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Socket_close(Ctx *ctx, Object **sfp)
{
	/* method void Socket.close()  */
	knh_Socket_close(
		ctx,
		(knh_Socket*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__Regex_match(Ctx *ctx, Object **sfp)
{
	/* method Bool Regex.match(String s)  */
	knh_bool_t v = knh_Regex_match(
		ctx,
		(knh_Regex*)sfp[0],
		(String*)sfp[1] /* String sfp[1] => String* s */
	);
	Object* rv = new_Bool(ctx, v) /* knh_bool_t v => Bool rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__DictMap_new(Ctx *ctx, Object **sfp)
{
	/* method DictMap! DictMap.new(Int initialCapacity)  */
	Object *rv = knh_DictMap_new(
		ctx,
		(knh_DictMap*)sfp[0],
		knh_IntNULL_toint(sfp[1]) /* Int sfp[1] => knh_int_t initialCapacity */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__DictMap_new__init(Ctx *ctx, Object **sfp)
{
	/* method[VARARGS] DictMap! DictMap.new::init(Any value)  */
	Object *rv = knh_DictMap_new__init(
		ctx,
		(knh_DictMap*)sfp[0],
		knh_stackf_argc(ctx, &(sfp[1])),
		&(sfp[1])
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__DictMap_get(Ctx *ctx, Object **sfp)
{
	/* method Any DictMap.get(String! key)  */
	Object *rv = knh_DictMap_get(
		ctx,
		(knh_DictMap*)sfp[0],
		(String*)sfp[1] /* String! sfp[1] => String* key */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__DictMap_append(Ctx *ctx, Object **sfp)
{
	/* method void DictMap.append(String! key, Any! value)  */
	knh_DictMap_append(
		ctx,
		(knh_DictMap*)sfp[0],
		(String*)sfp[1] /* String! sfp[1] => String* key */,
		(Any*)sfp[2] /* Any! sfp[2] => Any* value */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__DictMap_set(Ctx *ctx, Object **sfp)
{
	/* method void DictMap.set(String! key, Any value)  */
	knh_DictMap_set(
		ctx,
		(knh_DictMap*)sfp[0],
		(String*)sfp[1] /* String! sfp[1] => String* key */,
		(Any*)sfp[2] /* Any sfp[2] => Any* value */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__DictMap_remove(Ctx *ctx, Object **sfp)
{
	/* method void DictMap.remove(String! key)  */
	knh_DictMap_remove(
		ctx,
		(knh_DictMap*)sfp[0],
		(String*)sfp[1] /* String! sfp[1] => String* key */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__DictMap_clear(Ctx *ctx, Object **sfp)
{
	/* method void DictMap.clear()  */
	knh_DictMap_clear(
		ctx,
		(knh_DictMap*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__HashMap_new(Ctx *ctx, Object **sfp)
{
	/* method HashMap! HashMap.new(Int initialCapacity=0)  */
	Object *rv = knh_HashMap_new(
		ctx,
		(knh_HashMap*)sfp[0],
		(size_t)knh_IntNULL_toint(sfp[1]) /* Int sfp[1] => size_t initialCapacity */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__HashMap_new__init(Ctx *ctx, Object **sfp)
{
	/* method[VARARGS] HashMap! HashMap.new::init(Any value)  */
	Object *rv = knh_HashMap_new__init(
		ctx,
		(knh_HashMap*)sfp[0],
		knh_stackf_argc(ctx, &(sfp[1])),
		&(sfp[1])
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__HashMap_get(Ctx *ctx, Object **sfp)
{
	/* method Any HashMap.get(Any key)  */
	Object *rv = knh_HashMap_get(
		ctx,
		(knh_HashMap*)sfp[0],
		knh_Object_hcode(ctx, sfp[1]),
		(Any*)sfp[1] /* Any sfp[1] => Any* kobj */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__HashMap_set(Ctx *ctx, Object **sfp)
{
	/* method void HashMap.set(Any! key, Any value)  */
	knh_HashMap_set(
		ctx,
		(knh_HashMap*)sfp[0],
		knh_Object_hcode(ctx, sfp[1]),
		(Any*)sfp[1] /* Any! sfp[1] => Any* kobj */,
		(Any*)sfp[2] /* Any sfp[2] => Any* value */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__HashMap_remove(Ctx *ctx, Object **sfp)
{
	/* method void HashMap.remove(Any key)  */
	knh_HashMap_remove(
		ctx,
		(knh_HashMap*)sfp[0],
		knh_Object_hcode(ctx, sfp[1]),
		(Any*)sfp[1] /* Any sfp[1] => Any* kobj */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__HashMap_opIn(Ctx *ctx, Object **sfp)
{
	/* method Bool HashMap.opIn(Any key)  */
	knh_bool_t v = knh_HashMap_opIn(
		ctx,
		(knh_HashMap*)sfp[0],
		knh_Object_hcode(ctx, sfp[1]),
		(Any*)sfp[1] /* Any sfp[1] => Any* keyobj */
	);
	Object* rv = new_Bool(ctx, v) /* knh_bool_t v => Bool rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__HashMap_keys(Ctx *ctx, Object **sfp)
{
	/* method Iterator! HashMap.keys()  */
	Object *rv = knh_HashMap_keys(
		ctx,
		(knh_HashMap*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__HashSet_new(Ctx *ctx, Object **sfp)
{
	/* method HashSet! HashSet.new(Int initialCapacity=0)  */
	Object *rv = knh_HashSet_new(
		ctx,
		(knh_HashSet*)sfp[0],
		(size_t)knh_IntNULL_toint(sfp[1]) /* Int sfp[1] => size_t initialCapacity */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__HashSet_get(Ctx *ctx, Object **sfp)
{
	/* method Int! HashSet.get(Any key);  */
	knh_uint_t v = knh_HashSet_get(
		ctx,
		(knh_HashSet*)sfp[0],
		knh_Object_hcode(ctx, sfp[1]),
		(Object*)sfp[1] /* Any sfp[1] => Object* keyobj */
	);
	Object* rv = new_Int(ctx, v) /* knh_uint_t v => Int rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__HashSet_opIn(Ctx *ctx, Object **sfp)
{
	/* method Bool HashSet.opIn(Any key)  */
	knh_bool_t v = knh_HashSet_opIn(
		ctx,
		(knh_HashSet*)sfp[0],
		knh_Object_hcode(ctx, sfp[1]),
		(Object*)sfp[1] /* Any sfp[1] => Object* keyobj */
	);
	Object* rv = new_Bool(ctx, v) /* knh_bool_t v => Bool rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__HashSet_set(Ctx *ctx, Object **sfp)
{
	/* method void HashSet.set(Any key, Int! value);  */
	knh_HashSet_set(
		ctx,
		(knh_HashSet*)sfp[0],
		knh_Object_hcode(ctx, sfp[1]),
		(Any*)sfp[1] /* Any sfp[1] => Any* keyobj */,
		(knh_uint_t)knh_Int_toint(sfp[2]) /* Int! sfp[2] => knh_uint_t value */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__HashSet_add(Ctx *ctx, Object **sfp)
{
	/* method void HashSet.add(Any key)  */
	knh_HashSet_add(
		ctx,
		(knh_HashSet*)sfp[0],
		knh_Object_hcode(ctx, sfp[1]),
		(Any*)sfp[1] /* Any sfp[1] => Any* keyobj */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__HashSet_remove(Ctx *ctx, Object **sfp)
{
	/* method void HashSet.remove(Any key)  */
	knh_HashSet_remove(
		ctx,
		(knh_HashSet*)sfp[0],
		knh_Object_hcode(ctx, sfp[1]),
		(Any*)sfp[1] /* Any sfp[1] => Any* keyobj */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__OutputStream_write(Ctx *ctx, Object **sfp)
{
	/* method void OutputStream.write(Bytes buf)  */
	knh_OutputStream_write(
		ctx,
		(knh_OutputStream*)sfp[0],
		knh_BytesNULL_tobytes(sfp[1]) /* Bytes sfp[1] => knh_bytes_t buf */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__OutputStream_flush(Ctx *ctx, Object **sfp)
{
	/* method void OutputStream.flush()  */
	knh_OutputStream_flush(
		ctx,
		(knh_OutputStream*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__OutputStream_close(Ctx *ctx, Object **sfp)
{
	/* method void OutputStream.close()  */
	knh_OutputStream_close(
		ctx,
		(knh_OutputStream*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__Context_getRuntime(Ctx *ctx, Object **sfp)
{
	/* method Runtime! Context.getRuntime()  */
	Object *rv = knh_Context_getRuntime(
		ctx,
		(knh_Context*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Object_opInstanceof(Ctx *ctx, Object **sfp)
{
	/* method Bool Object.opInstanceof(Class c)  */
	knh_bool_t v = knh_Object_opInstanceof(
		ctx,
		(Object*)sfp[0],
		knh_Class_type((Class*)sfp[1]) /* Class sfp[1] => knh_type_t c */
	);
	Object* rv = new_Bool(ctx, v) /* knh_bool_t v => Bool rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Context_getProperty(Ctx *ctx, Object **sfp)
{
	/* method Any Context.getProperty(String! key)  */
	Object *rv = knh_Context_getProperty(
		ctx,
		(knh_Context*)sfp[0],
		knh_String_tobytes(sfp[1]) /* String! sfp[1] => knh_bytes_t key */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Context_setProperty(Ctx *ctx, Object **sfp)
{
	/* method void Context.setProperty(String! key, Any value)  */
	knh_Context_setProperty(
		ctx,
		(knh_Context*)sfp[0],
		(String*)sfp[1] /* String! sfp[1] => String* key */,
		(Any*)sfp[2] /* Any sfp[2] => Any* value */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__NameSpace_setClass(Ctx *ctx, Object **sfp)
{
	/* method void NameSpace.setClass(String name, Class c)  */
	knh_NameSpace_setClass(
		ctx,
		(knh_NameSpace*)sfp[0],
		(String*)sfp[1] /* String sfp[1] => String* name */,
		knh_Class_class((Class*)sfp[2]) /* Class sfp[2] => knh_class_t c */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__NameSpace_getClass(Ctx *ctx, Object **sfp)
{
	/* method Class NameSpace.getClass(String name)  */
	knh_class_t v = knh_NameSpace_getClass(
		ctx,
		(knh_NameSpace*)sfp[0],
		knh_StringNULL_tobytes(sfp[1]) /* String sfp[1] => knh_bytes_t name */
	);
	Object* rv = new_Class__type(ctx, v) /* knh_class_t v => Class rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Method_isAbstract(Ctx *ctx, Object **sfp)
{
	/* method Bool Method.isAbstract()  */
	knh_bool_t v = knh_Method_isAbstract(
		(knh_Method*)sfp[0]
	);
	Object* rv = new_Bool(ctx, v) /* knh_bool_t v => Bool rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Method_getName(Ctx *ctx, Object **sfp)
{
	/* method String! Method.getName()  */
	Object *rv = knh_Method_getName(
		ctx,
		(knh_Method*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Method_getURN(Ctx *ctx, Object **sfp)
{
	/* method String! Method.getURN()  */
	Object *rv = knh_Method_getURN(
		ctx,
		(knh_Method*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__ResultSet_next(Ctx *ctx, Object **sfp)
{
	/* method ResultSet ResultSet.next()  */
	Object *rv = knh_ResultSet_next(
		ctx,
		(knh_ResultSet*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__ResultSet_get(Ctx *ctx, Object **sfp)
{
	/* method Any ResultSet.get(Int! n)  */
	Object *rv = knh_ResultSet_get(
		ctx,
		(knh_ResultSet*)sfp[0],
		(size_t)knh_Int_toint(sfp[1]) /* Int! sfp[1] => size_t n */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Exception_new(Ctx *ctx, Object **sfp)
{
	/* method Exception! Exception.new(String! e, String msg, Object bag)  */
	Object *rv = knh_Exception_new(
		ctx,
		(knh_Exception*)sfp[0],
		(String*)sfp[1] /* String! sfp[1] => String* e */,
		(String*)sfp[2] /* String sfp[2] => String* msg */,
		(Object*)sfp[3] /* Object sfp[3] => Object* bag */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__System_getProperty(Ctx *ctx, Object **sfp)
{
	/* method Any System.getProperty(String! key)  */
	Object *rv = knh_System_getProperty(
		ctx,
		(knh_System*)sfp[0],
		knh_String_tobytes(sfp[1]) /* String! sfp[1] => knh_bytes_t key */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__System_setProperty(Ctx *ctx, Object **sfp)
{
	/* method void System.setProperty(String! key, Any value)  */
	knh_System_setProperty(
		ctx,
		(knh_System*)sfp[0],
		(String*)sfp[1] /* String! sfp[1] => String* key */,
		(Any*)sfp[2] /* Any sfp[2] => Any* value */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__Object_getClass(Ctx *ctx, Object **sfp)
{
	/* method Class! Object.getClass()  */
	knh_class_t v = knh_Object_getClass(
		(Object*)sfp[0]
	);
	Object* rv = new_Class__type(ctx, v) /* knh_class_t v => Class rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Object_compare(Ctx *ctx, Object **sfp)
{
	/* method Int! Object.compare(Any other)  */
	knh_int_t v = knh_Object_compare(
		ctx,
		(Object*)sfp[0],
		(Object*)sfp[1] /* Any sfp[1] => Object* o2 */
	);
	Object* rv = new_Int(ctx, v) /* knh_int_t v => Int rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__Connection_close(Ctx *ctx, Object **sfp)
{
	/* method void Connection.close()  */
	knh_Connection_close(
		ctx,
		(knh_Connection*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__DictSet_new(Ctx *ctx, Object **sfp)
{
	/* method DictSet! DictSet.new(Int initialCapacity=0)  */
	Object *rv = knh_DictSet_new(
		ctx,
		(knh_DictSet*)sfp[0],
		knh_IntNULL_toint(sfp[1]) /* Int sfp[1] => knh_int_t initialCapacity */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__DictSet_get(Ctx *ctx, Object **sfp)
{
	/* method Int! DictSet.get(String! key)  */
	knh_int_t v = knh_DictSet_get(
		(knh_DictSet*)sfp[0],
		(String*)sfp[1] /* String! sfp[1] => String* key */
	);
	Object* rv = new_Int(ctx, v) /* knh_int_t v => Int rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__DictSet_opIn(Ctx *ctx, Object **sfp)
{
	/* method Bool DictSet.opIn(Any value)  */
	knh_bool_t v = knh_DictSet_opIn(
		ctx,
		(knh_DictSet*)sfp[0],
		(Any*)sfp[1] /* Any sfp[1] => Any* value */
	);
	Object* rv = new_Bool(ctx, v) /* knh_bool_t v => Bool rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__DictSet_set(Ctx *ctx, Object **sfp)
{
	/* method void DictSet.set(String! key, Int! value)  */
	knh_DictSet_set(
		ctx,
		(knh_DictSet*)sfp[0],
		(String*)sfp[1] /* String! sfp[1] => String* key */,
		(knh_uint_t)knh_Int_toint(sfp[2]) /* Int! sfp[2] => knh_uint_t value */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__DictSet_add(Ctx *ctx, Object **sfp)
{
	/* method void DictSet.add(String! key)  */
	knh_DictSet_add(
		ctx,
		(knh_DictSet*)sfp[0],
		(String*)sfp[1] /* String! sfp[1] => String* key */
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__DictSet_clear(Ctx *ctx, Object **sfp)
{
	/* method void DictSet.clear()  */
	knh_DictSet_clear(
		ctx,
		(knh_DictSet*)sfp[0]
	);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

METHOD knh__String_equals(Ctx *ctx, Object **sfp)
{
	/* method Bool! String.equals(String! s)  */
	knh_bool_t v = knh_String_equals(
		(knh_String*)sfp[0],
		knh_String_tobytes(sfp[1]) /* String! sfp[1] => knh_bytes_t s */
	);
	Object* rv = new_Bool(ctx, v) /* knh_bool_t v => Bool rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__String_startsWith(Ctx *ctx, Object **sfp)
{
	/* method Bool! String.startsWith(String! s)  */
	knh_bool_t v = knh_String_startsWith(
		(knh_String*)sfp[0],
		knh_String_tobytes(sfp[1]) /* String! sfp[1] => knh_bytes_t s */
	);
	Object* rv = new_Bool(ctx, v) /* knh_bool_t v => Bool rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__String_endsWith(Ctx *ctx, Object **sfp)
{
	/* method Bool! String.endsWith(String! s)  */
	knh_bool_t v = knh_String_endsWith(
		(knh_String*)sfp[0],
		knh_String_tobytes(sfp[1]) /* String! sfp[1] => knh_bytes_t s */
	);
	Object* rv = new_Bool(ctx, v) /* knh_bool_t v => Bool rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__String_getSize(Ctx *ctx, Object **sfp)
{
	/* method Int! String.getSize()  */
	size_t v = knh_String_getSize(
		(knh_String*)sfp[0]
	);
	Object* rv = new_Int(ctx, (knh_int_t)v) /* size_t v => Int rv */;
	METHOD_RETURN(ctx, sfp, rv);
}

METHOD knh__String_opMul(Ctx *ctx, Object **sfp)
{
	/* method[STATIC] String! String.opMul(Int! n)  */
	Object *rv = knh_String_opMul(
		ctx,
		(knh_String*)sfp[0],
		knh_Int_toint(sfp[1]) /* Int! sfp[1] => knh_int_t n */
	);
	METHOD_RETURN(ctx, sfp, rv);
}

/* ======================================================================== */
/* [package] */

void knh_package_konoha_ginit(Ctx *ctx)
{

	KNH_TSTRUCT(ctx, 0, 0, "Tuple0", NULL, NULL, NULL, NULL); 
	KNH_TSTRUCT(ctx, STRUCT_Tuple1, sizeof(knh_Tuple1),
		"Tuple1",
		knh_Tuple1_struct_init,
		knh_Tuple1_struct_copy, 
		knh_Tuple1_struct_compare, 
		knh_Tuple1_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Tuple2, sizeof(knh_Tuple2),
		"Tuple2",
		knh_Tuple2_struct_init,
		knh_Tuple2_struct_copy, 
		knh_Tuple2_struct_compare, 
		knh_Tuple2_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Tuple3, sizeof(knh_Tuple3),
		"Tuple3",
		knh_Tuple3_struct_init,
		knh_Tuple3_struct_copy, 
		knh_Tuple3_struct_compare, 
		knh_Tuple3_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Tuple4, sizeof(knh_Tuple4),
		"Tuple4",
		knh_Tuple4_struct_init,
		knh_Tuple4_struct_copy, 
		knh_Tuple4_struct_compare, 
		knh_Tuple4_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Tuple5, sizeof(knh_Tuple5),
		"Tuple5",
		knh_Tuple5_struct_init,
		knh_Tuple5_struct_copy, 
		knh_Tuple5_struct_compare, 
		knh_Tuple5_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Tuple6, sizeof(knh_Tuple6),
		"Tuple6",
		knh_Tuple6_struct_init,
		knh_Tuple6_struct_copy, 
		knh_Tuple6_struct_compare, 
		knh_Tuple6_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Tuple7, sizeof(knh_Tuple7),
		"Tuple7",
		knh_Tuple7_struct_init,
		knh_Tuple7_struct_copy, 
		knh_Tuple7_struct_compare, 
		knh_Tuple7_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Tuple8, sizeof(knh_Tuple8),
		"Tuple8",
		knh_Tuple8_struct_init,
		knh_Tuple8_struct_copy, 
		knh_Tuple8_struct_compare, 
		knh_Tuple8_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Tuple9, sizeof(knh_Tuple9),
		"Tuple9",
		knh_Tuple9_struct_init,
		knh_Tuple9_struct_copy, 
		knh_Tuple9_struct_compare, 
		knh_Tuple9_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Tuple10, sizeof(knh_Tuple10),
		"Tuple10",
		knh_Tuple10_struct_init,
		knh_Tuple10_struct_copy, 
		knh_Tuple10_struct_compare, 
		knh_Tuple10_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Tuple11, sizeof(knh_Tuple11),
		"Tuple11",
		knh_Tuple11_struct_init,
		knh_Tuple11_struct_copy, 
		knh_Tuple11_struct_compare, 
		knh_Tuple11_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Tuple12, sizeof(knh_Tuple12),
		"Tuple12",
		knh_Tuple12_struct_init,
		knh_Tuple12_struct_copy, 
		knh_Tuple12_struct_compare, 
		knh_Tuple12_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Tuple13, sizeof(knh_Tuple13),
		"Tuple13",
		knh_Tuple13_struct_init,
		knh_Tuple13_struct_copy, 
		knh_Tuple13_struct_compare, 
		knh_Tuple13_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Tuple14, sizeof(knh_Tuple14),
		"Tuple14",
		knh_Tuple14_struct_init,
		knh_Tuple14_struct_copy, 
		knh_Tuple14_struct_compare, 
		knh_Tuple14_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Tuple15, sizeof(knh_Tuple15),
		"Tuple15",
		knh_Tuple15_struct_init,
		knh_Tuple15_struct_copy, 
		knh_Tuple15_struct_compare, 
		knh_Tuple15_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Prototype, sizeof(knh_Prototype),
		"Prototype",
		knh_Prototype_struct_init,
		knh_Prototype_struct_copy, 
		knh_Prototype_struct_compare, 
		knh_Prototype_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Nue, sizeof(knh_Nue),
		"Nue",
		knh_Nue_struct_init,
		knh_Nue_struct_copy, 
		knh_Nue_struct_compare, 
		knh_Nue_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Bool, sizeof(knh_Bool),
		"Bool",
		knh_Bool_struct_init,
		knh_Bool_struct_copy, 
		knh_Bool_struct_compare, 
		knh_Bool_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Int, sizeof(knh_Int),
		"Int",
		knh_Int_struct_init,
		knh_Int_struct_copy, 
		knh_Int_struct_compare, 
		knh_Int_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Int64, sizeof(knh_Int64),
		"Int64",
		knh_Int64_struct_init,
		knh_Int64_struct_copy, 
		knh_Int64_struct_compare, 
		knh_Int64_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Float, sizeof(knh_Float),
		"Float",
		knh_Float_struct_init,
		knh_Float_struct_copy, 
		knh_Float_struct_compare, 
		knh_Float_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_String, sizeof(knh_String),
		"String",
		knh_String_struct_init,
		knh_String_struct_copy, 
		knh_String_struct_compare, 
		knh_String_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Regex, sizeof(knh_Regex),
		"Regex",
		knh_Regex_struct_init,
		knh_Regex_struct_copy, 
		knh_Regex_struct_compare, 
		knh_Regex_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Bytes, sizeof(knh_Bytes),
		"Bytes",
		knh_Bytes_struct_init,
		knh_Bytes_struct_copy, 
		knh_Bytes_struct_compare, 
		knh_Bytes_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_BytesConv, sizeof(knh_BytesConv),
		"BytesConv",
		knh_BytesConv_struct_init,
		knh_BytesConv_struct_copy, 
		knh_BytesConv_struct_compare, 
		knh_BytesConv_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Array, sizeof(knh_Array),
		"Array",
		knh_Array_struct_init,
		knh_Array_struct_copy, 
		knh_Array_struct_compare, 
		knh_Array_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_HashMap, sizeof(knh_HashMap),
		"HashMap",
		knh_HashMap_struct_init,
		knh_HashMap_struct_copy, 
		knh_HashMap_struct_compare, 
		knh_HashMap_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_HashSet, sizeof(knh_HashSet),
		"HashSet",
		knh_HashSet_struct_init,
		knh_HashSet_struct_copy, 
		knh_HashSet_struct_compare, 
		knh_HashSet_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_DictMap, sizeof(knh_DictMap),
		"DictMap",
		knh_DictMap_struct_init,
		knh_DictMap_struct_copy, 
		knh_DictMap_struct_compare, 
		knh_DictMap_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_DictSet, sizeof(knh_DictSet),
		"DictSet",
		knh_DictSet_struct_init,
		knh_DictSet_struct_copy, 
		knh_DictSet_struct_compare, 
		knh_DictSet_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Iterator, sizeof(knh_Iterator),
		"Iterator",
		knh_Iterator_struct_init,
		knh_Iterator_struct_copy, 
		knh_Iterator_struct_compare, 
		knh_Iterator_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_DictIdx, sizeof(knh_DictIdx),
		"DictIdx",
		knh_DictIdx_struct_init,
		knh_DictIdx_struct_copy, 
		knh_DictIdx_struct_compare, 
		knh_DictIdx_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Class, sizeof(knh_Class),
		"Class",
		knh_Class_struct_init,
		knh_Class_struct_copy, 
		knh_Class_struct_compare, 
		knh_Class_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_ClassStruct, sizeof(knh_ClassStruct),
		"ClassStruct",
		knh_ClassStruct_struct_init,
		knh_ClassStruct_struct_copy, 
		knh_ClassStruct_struct_compare, 
		knh_ClassStruct_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_MethodField, sizeof(knh_MethodField),
		"MethodField",
		knh_MethodField_struct_init,
		knh_MethodField_struct_copy, 
		knh_MethodField_struct_compare, 
		knh_MethodField_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Method, sizeof(knh_Method),
		"Method",
		knh_Method_struct_init,
		knh_Method_struct_copy, 
		knh_Method_struct_compare, 
		knh_Method_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_MapMap, sizeof(knh_MapMap),
		"MapMap",
		knh_MapMap_struct_init,
		knh_MapMap_struct_copy, 
		knh_MapMap_struct_compare, 
		knh_MapMap_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_ClassRel, sizeof(knh_ClassRel),
		"ClassRel",
		knh_ClassRel_struct_init,
		knh_ClassRel_struct_copy, 
		knh_ClassRel_struct_compare, 
		knh_ClassRel_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_AffineConv, sizeof(knh_AffineConv),
		"AffineConv",
		knh_AffineConv_struct_init,
		knh_AffineConv_struct_copy, 
		knh_AffineConv_struct_compare, 
		knh_AffineConv_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_IntUnit, sizeof(knh_IntUnit),
		"IntUnit",
		knh_IntUnit_struct_init,
		knh_IntUnit_struct_copy, 
		knh_IntUnit_struct_compare, 
		knh_IntUnit_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_FloatUnit, sizeof(knh_FloatUnit),
		"FloatUnit",
		knh_FloatUnit_struct_init,
		knh_FloatUnit_struct_copy, 
		knh_FloatUnit_struct_compare, 
		knh_FloatUnit_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Vocabulary, sizeof(knh_Vocabulary),
		"Vocabulary",
		knh_Vocabulary_struct_init,
		knh_Vocabulary_struct_copy, 
		knh_Vocabulary_struct_compare, 
		knh_Vocabulary_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_InputStream, sizeof(knh_InputStream),
		"InputStream",
		knh_InputStream_struct_init,
		knh_InputStream_struct_copy, 
		knh_InputStream_struct_compare, 
		knh_InputStream_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_OutputStream, sizeof(knh_OutputStream),
		"OutputStream",
		knh_OutputStream_struct_init,
		knh_OutputStream_struct_copy, 
		knh_OutputStream_struct_compare, 
		knh_OutputStream_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Socket, sizeof(knh_Socket),
		"Socket",
		knh_Socket_struct_init,
		knh_Socket_struct_copy, 
		knh_Socket_struct_compare, 
		knh_Socket_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_ResultSet, sizeof(knh_ResultSet),
		"ResultSet",
		knh_ResultSet_struct_init,
		knh_ResultSet_struct_copy, 
		knh_ResultSet_struct_compare, 
		knh_ResultSet_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Connection, sizeof(knh_Connection),
		"Connection",
		knh_Connection_struct_init,
		knh_Connection_struct_copy, 
		knh_Connection_struct_compare, 
		knh_Connection_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Exception, sizeof(knh_Exception),
		"Exception",
		knh_Exception_struct_init,
		knh_Exception_struct_copy, 
		knh_Exception_struct_compare, 
		knh_Exception_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_ExceptionHandler, sizeof(knh_ExceptionHandler),
		"ExceptionHandler",
		knh_ExceptionHandler_struct_init,
		knh_ExceptionHandler_struct_copy, 
		knh_ExceptionHandler_struct_compare, 
		knh_ExceptionHandler_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Runtime, sizeof(knh_Runtime),
		"Runtime",
		knh_Runtime_struct_init,
		knh_Runtime_struct_copy, 
		knh_Runtime_struct_compare, 
		knh_Runtime_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Context, sizeof(knh_Context),
		"Context",
		knh_Context_struct_init,
		knh_Context_struct_copy, 
		knh_Context_struct_compare, 
		knh_Context_struct_traverse);
	KNH_TSTRUCT(ctx, STRUCT_Mutex, sizeof(knh_Mutex),
		"Mutex",
		knh_Mutex_struct_init,
		knh_Mutex_struct_copy, 
		knh_Mutex_struct_compare, 
		knh_Mutex_struct_traverse);
	KNH_TCLASS(ctx, KNH_CFLAG_Object,
		new_String__STEXT(ctx, CLASS_String, "konoha.Object"),
		CLASS_Object, STRUCT_Object, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Tuple,
		new_String__STEXT(ctx, CLASS_String, "konoha.Tuple"),
		CLASS_Tuple, STRUCT_Tuple, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Tuple1,
		new_String__STEXT(ctx, CLASS_String, "konoha.Tuple1"),
		CLASS_Tuple1, STRUCT_Tuple1, CLASS_Tuple,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Tuple2,
		new_String__STEXT(ctx, CLASS_String, "konoha.Tuple2"),
		CLASS_Tuple2, STRUCT_Tuple2, CLASS_Tuple,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Tuple3,
		new_String__STEXT(ctx, CLASS_String, "konoha.Tuple3"),
		CLASS_Tuple3, STRUCT_Tuple3, CLASS_Tuple,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Tuple4,
		new_String__STEXT(ctx, CLASS_String, "konoha.Tuple4"),
		CLASS_Tuple4, STRUCT_Tuple4, CLASS_Tuple,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Tuple5,
		new_String__STEXT(ctx, CLASS_String, "konoha.Tuple5"),
		CLASS_Tuple5, STRUCT_Tuple5, CLASS_Tuple,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Tuple6,
		new_String__STEXT(ctx, CLASS_String, "konoha.Tuple6"),
		CLASS_Tuple6, STRUCT_Tuple6, CLASS_Tuple,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Tuple7,
		new_String__STEXT(ctx, CLASS_String, "konoha.Tuple7"),
		CLASS_Tuple7, STRUCT_Tuple7, CLASS_Tuple,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Tuple8,
		new_String__STEXT(ctx, CLASS_String, "konoha.Tuple8"),
		CLASS_Tuple8, STRUCT_Tuple8, CLASS_Tuple,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Tuple9,
		new_String__STEXT(ctx, CLASS_String, "konoha.Tuple9"),
		CLASS_Tuple9, STRUCT_Tuple9, CLASS_Tuple,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Tuple10,
		new_String__STEXT(ctx, CLASS_String, "konoha.Tuple10"),
		CLASS_Tuple10, STRUCT_Tuple10, CLASS_Tuple,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Tuple11,
		new_String__STEXT(ctx, CLASS_String, "konoha.Tuple11"),
		CLASS_Tuple11, STRUCT_Tuple11, CLASS_Tuple,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Tuple12,
		new_String__STEXT(ctx, CLASS_String, "konoha.Tuple12"),
		CLASS_Tuple12, STRUCT_Tuple12, CLASS_Tuple,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Tuple13,
		new_String__STEXT(ctx, CLASS_String, "konoha.Tuple13"),
		CLASS_Tuple13, STRUCT_Tuple13, CLASS_Tuple,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Tuple14,
		new_String__STEXT(ctx, CLASS_String, "konoha.Tuple14"),
		CLASS_Tuple14, STRUCT_Tuple14, CLASS_Tuple,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Tuple15,
		new_String__STEXT(ctx, CLASS_String, "konoha.Tuple15"),
		CLASS_Tuple15, STRUCT_Tuple15, CLASS_Tuple,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Prototype,
		new_String__STEXT(ctx, CLASS_String, "konoha.Prototype"),
		CLASS_Prototype, STRUCT_Prototype, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Nue,
		new_String__STEXT(ctx, CLASS_String, "konoha.Nue"),
		CLASS_Nue, STRUCT_Nue, CLASS_Object,
		KNH_NULL, knh_Nue_fvalue, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Bool,
		new_String__STEXT(ctx, CLASS_String, "konoha.Bool"),
		CLASS_Bool, STRUCT_Bool, CLASS_Object,
		KNH_NULL, knh_Bool_fvalue, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Int,
		new_String__STEXT(ctx, CLASS_String, "konoha.Int"),
		CLASS_Int, STRUCT_Int, CLASS_Object,
		knh_Int_spec(ctx), NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Int64,
		new_String__STEXT(ctx, CLASS_String, "konoha.Int64"),
		CLASS_Int64, STRUCT_Int64, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Float,
		new_String__STEXT(ctx, CLASS_String, "konoha.Float"),
		CLASS_Float, STRUCT_Float, CLASS_Object,
		knh_Float_spec(ctx), NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_String,
		new_String__STEXT(ctx, CLASS_String, "konoha.String"),
		CLASS_String, STRUCT_String, CLASS_Object,
		knh_String_spec(ctx), NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Regex,
		new_String__STEXT(ctx, CLASS_String, "konoha.Regex"),
		CLASS_Regex, STRUCT_Regex, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Bytes,
		new_String__STEXT(ctx, CLASS_String, "konoha.Bytes"),
		CLASS_Bytes, STRUCT_Bytes, CLASS_Object,
		KNH_NULL, knh_Bytes_fvalue, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_BytesConv,
		new_String__STEXT(ctx, CLASS_String, "konoha.BytesConv"),
		CLASS_BytesConv, STRUCT_BytesConv, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Array,
		new_String__STEXT(ctx, CLASS_String, "konoha.Array"),
		CLASS_Array, STRUCT_Array, CLASS_Object,
		KNH_NULL, knh_Array_fvalue, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_HashMap,
		new_String__STEXT(ctx, CLASS_String, "konoha.HashMap"),
		CLASS_HashMap, STRUCT_HashMap, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_HashSet,
		new_String__STEXT(ctx, CLASS_String, "konoha.HashSet"),
		CLASS_HashSet, STRUCT_HashSet, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_DictMap,
		new_String__STEXT(ctx, CLASS_String, "konoha.DictMap"),
		CLASS_DictMap, STRUCT_DictMap, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_DictSet,
		new_String__STEXT(ctx, CLASS_String, "konoha.DictSet"),
		CLASS_DictSet, STRUCT_DictSet, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Iterator,
		new_String__STEXT(ctx, CLASS_String, "konoha.Iterator"),
		CLASS_Iterator, STRUCT_Iterator, CLASS_Object,
		KNH_NULL, knh_Iterator_fvalue, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_DictIdx,
		new_String__STEXT(ctx, CLASS_String, "konoha.DictIdx"),
		CLASS_DictIdx, STRUCT_DictIdx, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Class,
		new_String__STEXT(ctx, CLASS_String, "konoha.Class"),
		CLASS_Class, STRUCT_Class, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_ClassStruct,
		new_String__STEXT(ctx, CLASS_String, "konoha.ClassStruct"),
		CLASS_ClassStruct, STRUCT_ClassStruct, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_MethodField,
		new_String__STEXT(ctx, CLASS_String, "konoha.MethodField"),
		CLASS_MethodField, STRUCT_MethodField, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Method,
		new_String__STEXT(ctx, CLASS_String, "konoha.Method"),
		CLASS_Method, STRUCT_Method, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_MapMap,
		new_String__STEXT(ctx, CLASS_String, "konoha.MapMap"),
		CLASS_MapMap, STRUCT_MapMap, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_ClassRel,
		new_String__STEXT(ctx, CLASS_String, "konoha.ClassRel"),
		CLASS_ClassRel, STRUCT_ClassRel, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_AffineConv,
		new_String__STEXT(ctx, CLASS_String, "konoha.AffineConv"),
		CLASS_AffineConv, STRUCT_AffineConv, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_IntUnit,
		new_String__STEXT(ctx, CLASS_String, "konoha.IntUnit"),
		CLASS_IntUnit, STRUCT_IntUnit, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_FloatUnit,
		new_String__STEXT(ctx, CLASS_String, "konoha.FloatUnit"),
		CLASS_FloatUnit, STRUCT_FloatUnit, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Vocabulary,
		new_String__STEXT(ctx, CLASS_String, "konoha.Vocabulary"),
		CLASS_Vocabulary, STRUCT_Vocabulary, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_InputStream,
		new_String__STEXT(ctx, CLASS_String, "konoha.InputStream"),
		CLASS_InputStream, STRUCT_InputStream, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_OutputStream,
		new_String__STEXT(ctx, CLASS_String, "konoha.OutputStream"),
		CLASS_OutputStream, STRUCT_OutputStream, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Socket,
		new_String__STEXT(ctx, CLASS_String, "konoha.Socket"),
		CLASS_Socket, STRUCT_Socket, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_ResultSet,
		new_String__STEXT(ctx, CLASS_String, "konoha.ResultSet"),
		CLASS_ResultSet, STRUCT_ResultSet, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Connection,
		new_String__STEXT(ctx, CLASS_String, "konoha.Connection"),
		CLASS_Connection, STRUCT_Connection, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Exception,
		new_String__STEXT(ctx, CLASS_String, "konoha.Exception"),
		CLASS_Exception, STRUCT_Exception, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_ExceptionHandler,
		new_String__STEXT(ctx, CLASS_String, "konoha.ExceptionHandler"),
		CLASS_ExceptionHandler, STRUCT_ExceptionHandler, CLASS_Object,
		KNH_NULL, knh_ExceptionHandler_fvalue, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_System,
		new_String__STEXT(ctx, CLASS_String, "konoha.System"),
		CLASS_System, STRUCT_System, CLASS_Object,
		KNH_NULL, knh_System_fvalue, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_NameSpace,
		new_String__STEXT(ctx, CLASS_String, "konoha.NameSpace"),
		CLASS_NameSpace, STRUCT_NameSpace, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Runtime,
		new_String__STEXT(ctx, CLASS_String, "konoha.Runtime"),
		CLASS_Runtime, STRUCT_Runtime, CLASS_Object,
		KNH_NULL, knh_Runtime_fvalue, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Context,
		new_String__STEXT(ctx, CLASS_String, "konoha.Context"),
		CLASS_Context, STRUCT_Context, CLASS_Object,
		KNH_NULL, knh_Context_fvalue, 0); 
	KNH_TCLASS(ctx, KNH_CFLAG_Mutex,
		new_String__STEXT(ctx, CLASS_String, "konoha.Mutex"),
		CLASS_Mutex, STRUCT_Mutex, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_new, NULL, /*delta*/0, 
		CLASS_Array, CLASS_Array, METHODN_new, 1,
		TYPE_Int, FIELDN_init
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_new__array, NULL, /*delta*/0, 
		CLASS_Array, CLASS_Array, METHODN_new__array, 2,
		TYPE_Int, FIELDN_init,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_new__init, NULL, /*delta*/0, 
		CLASS_Array, CLASS_Array, METHODN_new__init, 1,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_get__fast, NULL, /*delta*/0, 
		TYPE_Any, CLASS_Array, METHODN_get__fast, 1,
		CLASS_Int, FIELDN_index
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_set__fast, NULL, /*delta*/0, 
		TYPE_void, CLASS_Array, METHODN_set__fast, 2,
		CLASS_Int, FIELDN_index,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_get, NULL, /*delta*/0, 
		TYPE_Any, CLASS_Array, METHODN_get, 1,
		CLASS_Int, FIELDN_index
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_set, NULL, /*delta*/0, 
		TYPE_void, CLASS_Array, METHODN_set, 2,
		CLASS_Int, FIELDN_index,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Bytes_new, NULL, /*delta*/0, 
		CLASS_Bytes, CLASS_Bytes, METHODN_new, 1,
		TYPE_Int, FIELDN_init
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opAdd, NULL, /*delta*/0, 
		CLASS_Int, CLASS_Int, METHODN_opAdd, 1,
		CLASS_Int, FIELDN_v
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opSub, NULL, /*delta*/0, 
		CLASS_Int, CLASS_Int, METHODN_opSub, 1,
		CLASS_Int, FIELDN_n
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opMul, NULL, /*delta*/0, 
		CLASS_Int, CLASS_Int, METHODN_opMul, 1,
		CLASS_Int, FIELDN_n
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opDiv, NULL, /*delta*/0, 
		CLASS_Int, CLASS_Int, METHODN_opDiv, 1,
		CLASS_Int, FIELDN_n
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opMod, NULL, /*delta*/0, 
		CLASS_Int, CLASS_Int, METHODN_opMod, 1,
		CLASS_Int, FIELDN_n
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opEq, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_Int, METHODN_opEq, 1,
		CLASS_Int, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opNeq, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_Int, METHODN_opNeq, 1,
		CLASS_Int, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opLt, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Int, METHODN_opLt, 1,
		CLASS_Int, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opLte, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Int, METHODN_opLte, 1,
		CLASS_Int, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opGt, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Int, METHODN_opGt, 1,
		CLASS_Int, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opGte, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Int, METHODN_opGte, 1,
		CLASS_Int, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opLogicalAnd, NULL, /*delta*/0, 
		CLASS_Int, CLASS_Int, METHODN_opLogicalAnd, 1,
		CLASS_Int, FIELDN_v
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opLogicalOr, NULL, /*delta*/0, 
		CLASS_Int, CLASS_Int, METHODN_opLogicalOr, 1,
		CLASS_Int, FIELDN_v
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opLogicalXor, NULL, /*delta*/0, 
		CLASS_Int, CLASS_Int, METHODN_opLogicalXor, 1,
		CLASS_Int, FIELDN_n
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opLogicalNot, NULL, /*delta*/0, 
		CLASS_Int, CLASS_Int, METHODN_opLogicalNot, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opLShift, NULL, /*delta*/0, 
		CLASS_Int, CLASS_Int, METHODN_opLShift, 1,
		CLASS_Int, FIELDN_n
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Int_opRShift, NULL, /*delta*/0, 
		CLASS_Int, CLASS_Int, METHODN_opRShift, 1,
		CLASS_Int, FIELDN_n
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Int__s, /*delta*/0, 
		TYPE_void, CLASS_Int, METHODN__s, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Int__x, /*delta*/0, 
		TYPE_void, CLASS_Int, METHODN__x, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Int__bits, /*delta*/0, 
		TYPE_void, CLASS_Int, METHODN__bits, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Int__dump, /*delta*/0, 
		TYPE_void, CLASS_Int, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Float_random, NULL, /*delta*/0, 
		TYPE_Float, CLASS_Float, METHODN_random, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__System_getIn, NULL, /*delta*/0, 
		CLASS_InputStream, CLASS_System, METHODN_getIn, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__System_setIn, NULL, /*delta*/0, 
		TYPE_void, CLASS_System, METHODN_setIn, 1,
		TYPE_InputStream, FIELDN_input
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__System_getOut, NULL, /*delta*/0, 
		CLASS_OutputStream, CLASS_System, METHODN_getOut, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__System_setOut, NULL, /*delta*/0, 
		TYPE_void, CLASS_System, METHODN_setOut, 1,
		TYPE_OutputStream, FIELDN_out
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__System_getErr, NULL, /*delta*/0, 
		CLASS_OutputStream, CLASS_System, METHODN_getErr, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__System_setErr, NULL, /*delta*/0, 
		TYPE_void, CLASS_System, METHODN_setErr, 1,
		TYPE_OutputStream, FIELDN_out
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__String_opAdd, NULL, /*delta*/0, 
		CLASS_String, CLASS_String, METHODN_opAdd, 1,
		TYPE_Any, FIELDN_v
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Bool_opEq, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Bool, METHODN_opEq, 1,
		TYPE_Any, FIELDN_another
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Bool_opNeq, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Bool, METHODN_opNeq, 1,
		TYPE_Any, FIELDN_another
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Bool__s, /*delta*/0, 
		TYPE_void, CLASS_Bool, METHODN__s, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Float_opAdd, NULL, /*delta*/0, 
		CLASS_Float, CLASS_Float, METHODN_opAdd, 1,
		CLASS_Float, FIELDN_v
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Float_opSub, NULL, /*delta*/0, 
		CLASS_Float, CLASS_Float, METHODN_opSub, 1,
		CLASS_Float, FIELDN_v
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Float_opMul, NULL, /*delta*/0, 
		CLASS_Float, CLASS_Float, METHODN_opMul, 1,
		CLASS_Float, FIELDN_v
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Float_opDiv, NULL, /*delta*/0, 
		CLASS_Float, CLASS_Float, METHODN_opDiv, 1,
		CLASS_Float, FIELDN_v
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Float_opEq, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Float, METHODN_opEq, 1,
		TYPE_Float, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Float_opNeq, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Float, METHODN_opNeq, 1,
		TYPE_Float, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Float_opLt, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Float, METHODN_opLt, 1,
		TYPE_Float, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Float_opLte, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Float, METHODN_opLte, 1,
		TYPE_Float, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Float_opGt, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Float, METHODN_opGt, 1,
		TYPE_Float, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Float_opGte, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Float, METHODN_opGte, 1,
		TYPE_Float, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Float__s, /*delta*/0, 
		TYPE_void, CLASS_Float, METHODN__s, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Float__dump, /*delta*/0, 
		TYPE_void, CLASS_Float, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Connection_new, NULL, /*delta*/0, 
		CLASS_Connection, CLASS_Connection, METHODN_new, 1,
		CLASS_String, FIELDN_urn
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Connection_query, NULL, /*delta*/0, 
		TYPE_ResultSet, CLASS_Connection, METHODN_query, 1,
		CLASS_String, FIELDN_query
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Tuple_new, NULL, /*delta*/0, 
		CLASS_Tuple, CLASS_Tuple, METHODN_new, 1,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Tuple_getSize, NULL, /*delta*/0, 
		CLASS_Int, CLASS_Tuple, METHODN_getSize, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Tuple_get__fast, NULL, /*delta*/0, 
		TYPE_Any, CLASS_Tuple, METHODN_get__fast, 1,
		CLASS_Int, FIELDN_index
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Tuple_get, NULL, /*delta*/0, 
		TYPE_Any, CLASS_Tuple, METHODN_get, 1,
		CLASS_Int, FIELDN_index
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Tuple__dump, /*delta*/0, 
		TYPE_void, CLASS_Tuple, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictIdx_index, NULL, /*delta*/0, 
		CLASS_Int, CLASS_DictIdx, METHODN_index, 1,
		CLASS_String, FIELDN_term
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictIdx_add__fast, NULL, /*delta*/0, 
		CLASS_Int, CLASS_DictIdx, METHODN_add__fast, 1,
		CLASS_String, FIELDN_term
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictIdx_add, NULL, /*delta*/0, 
		CLASS_Int, CLASS_DictIdx, METHODN_add, 1,
		CLASS_String, FIELDN_term
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictIdx_get__fast, NULL, /*delta*/0, 
		TYPE_String, CLASS_DictIdx, METHODN_get__fast, 1,
		CLASS_Int, FIELDN_index
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictIdx_get, NULL, /*delta*/0, 
		TYPE_String, CLASS_DictIdx, METHODN_get, 1,
		CLASS_Int, FIELDN_index
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictIdx_clear, NULL, /*delta*/0, 
		TYPE_void, CLASS_DictIdx, METHODN_clear, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_DictIdx__dump, /*delta*/0, 
		TYPE_void, CLASS_DictIdx, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__InputStream_readLine, NULL, /*delta*/0, 
		TYPE_String, CLASS_InputStream, METHODN_readLine, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__InputStream_close, NULL, /*delta*/0, 
		TYPE_void, CLASS_InputStream, METHODN_close, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_InputStream__dump, /*delta*/0, 
		TYPE_void, CLASS_InputStream, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_add__fast, NULL, /*delta*/0, 
		TYPE_void, CLASS_Array, METHODN_add__fast, 1,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_add, NULL, /*delta*/0, 
		TYPE_void, CLASS_Array, METHODN_add, 1,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_pop, NULL, /*delta*/0, 
		TYPE_Any, CLASS_Array, METHODN_pop, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_slice, NULL, /*delta*/0, 
		CLASS_Array, CLASS_Array, METHODN_slice, 2,
		TYPE_Int, FIELDN_start,
		TYPE_Int, FIELDN_end
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_clear, NULL, /*delta*/0, 
		TYPE_void, CLASS_Array, METHODN_clear, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Array__dump, /*delta*/0, 
		TYPE_void, CLASS_Array, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Socket_getInputStream, NULL, /*delta*/0, 
		CLASS_InputStream, CLASS_Socket, METHODN_getInputStream, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Socket_getOutputStream, NULL, /*delta*/0, 
		CLASS_OutputStream, CLASS_Socket, METHODN_getOutputStream, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Socket_close, NULL, /*delta*/0, 
		TYPE_void, CLASS_Socket, METHODN_close, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Regex_match, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_Regex, METHODN_match, 1,
		TYPE_String, FIELDN_s
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Regex__s, /*delta*/0, 
		TYPE_void, CLASS_Regex, METHODN__s, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Regex__dump, /*delta*/0, 
		TYPE_void, CLASS_Regex, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictMap_new, NULL, /*delta*/0, 
		CLASS_DictMap, CLASS_DictMap, METHODN_new, 1,
		TYPE_Int, FIELDN_initialCapacity
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictMap_new__init, NULL, /*delta*/0, 
		CLASS_DictMap, CLASS_DictMap, METHODN_new__init, 1,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictMap_get, NULL, /*delta*/0, 
		TYPE_Any, CLASS_DictMap, METHODN_get, 1,
		CLASS_String, FIELDN_key
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictMap_append, NULL, /*delta*/0, 
		TYPE_void, CLASS_DictMap, METHODN_append, 2,
		CLASS_String, FIELDN_key,
		CLASS_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictMap_set, NULL, /*delta*/0, 
		TYPE_void, CLASS_DictMap, METHODN_set, 2,
		CLASS_String, FIELDN_key,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictMap_remove, NULL, /*delta*/0, 
		TYPE_void, CLASS_DictMap, METHODN_remove, 1,
		CLASS_String, FIELDN_key
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictMap_clear, NULL, /*delta*/0, 
		TYPE_void, CLASS_DictMap, METHODN_clear, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_DictMap__dump, /*delta*/0, 
		TYPE_void, CLASS_DictMap, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashMap_new, NULL, /*delta*/0, 
		CLASS_HashMap, CLASS_HashMap, METHODN_new, 1,
		TYPE_Int, FIELDN_initialCapacity
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashMap_new__init, NULL, /*delta*/0, 
		CLASS_HashMap, CLASS_HashMap, METHODN_new__init, 1,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashMap_get, NULL, /*delta*/0, 
		TYPE_Any, CLASS_HashMap, METHODN_get, 1,
		TYPE_Any, FIELDN_key
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashMap_set, NULL, /*delta*/0, 
		TYPE_void, CLASS_HashMap, METHODN_set, 2,
		CLASS_Any, FIELDN_key,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashMap_remove, NULL, /*delta*/0, 
		TYPE_void, CLASS_HashMap, METHODN_remove, 1,
		TYPE_Any, FIELDN_key
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashMap_opIn, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_HashMap, METHODN_opIn, 1,
		TYPE_Any, FIELDN_key
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashMap_keys, NULL, /*delta*/0, 
		CLASS_Iterator, CLASS_HashMap, METHODN_keys, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_HashMap__dump, /*delta*/0, 
		TYPE_void, CLASS_HashMap, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_MapMap__dump, /*delta*/0, 
		TYPE_void, CLASS_MapMap, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Prototype__dump, /*delta*/0, 
		TYPE_void, CLASS_Prototype, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Nue__s, /*delta*/0, 
		TYPE_void, CLASS_Nue, METHODN__s, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Iterator__dump, /*delta*/0, 
		TYPE_void, CLASS_Iterator, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashSet_new, NULL, /*delta*/0, 
		CLASS_HashSet, CLASS_HashSet, METHODN_new, 1,
		TYPE_Int, FIELDN_initialCapacity
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashSet_get, NULL, /*delta*/0, 
		CLASS_Int, CLASS_HashSet, METHODN_get, 1,
		TYPE_Any, FIELDN_key
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashSet_opIn, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_HashSet, METHODN_opIn, 1,
		TYPE_Any, FIELDN_key
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashSet_set, NULL, /*delta*/0, 
		TYPE_void, CLASS_HashSet, METHODN_set, 2,
		TYPE_Any, FIELDN_key,
		CLASS_Int, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashSet_add, NULL, /*delta*/0, 
		TYPE_void, CLASS_HashSet, METHODN_add, 1,
		TYPE_Any, FIELDN_key
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashSet_remove, NULL, /*delta*/0, 
		TYPE_void, CLASS_HashSet, METHODN_remove, 1,
		TYPE_Any, FIELDN_key
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_HashSet__dump, /*delta*/0, 
		TYPE_void, CLASS_HashSet, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__OutputStream_write, NULL, /*delta*/0, 
		TYPE_void, CLASS_OutputStream, METHODN_write, 1,
		TYPE_Bytes, FIELDN_buf
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__OutputStream_flush, NULL, /*delta*/0, 
		TYPE_void, CLASS_OutputStream, METHODN_flush, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__OutputStream_close, NULL, /*delta*/0, 
		TYPE_void, CLASS_OutputStream, METHODN_close, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Context_getRuntime, NULL, /*delta*/0, 
		CLASS_Runtime, CLASS_Context, METHODN_getRuntime, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_opInstanceof, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_Object, METHODN_opInstanceof, 1,
		TYPE_Class, FIELDN_c
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Context_getProperty, NULL, /*delta*/0, 
		TYPE_Any, CLASS_Context, METHODN_getProperty, 1,
		CLASS_String, FIELDN_key
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Context_setProperty, NULL, /*delta*/0, 
		TYPE_void, CLASS_Context, METHODN_setProperty, 2,
		CLASS_String, FIELDN_key,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Context__dump, /*delta*/0, 
		TYPE_void, CLASS_Context, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__NameSpace_setClass, NULL, /*delta*/0, 
		TYPE_void, CLASS_NameSpace, METHODN_setClass, 2,
		TYPE_String, FIELDN_name,
		TYPE_Class, FIELDN_c
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__NameSpace_getClass, NULL, /*delta*/0, 
		TYPE_Class, CLASS_NameSpace, METHODN_getClass, 1,
		TYPE_String, FIELDN_name
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isAbstract, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_Method, METHODN_isAbstract, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_getName, NULL, /*delta*/0, 
		CLASS_String, CLASS_Method, METHODN_getName, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_getURN, NULL, /*delta*/0, 
		CLASS_String, CLASS_Method, METHODN_getURN, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Method__s, /*delta*/0, 
		TYPE_void, CLASS_Method, METHODN__s, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Method__dump, /*delta*/0, 
		TYPE_void, CLASS_Method, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__ResultSet_next, NULL, /*delta*/0, 
		TYPE_ResultSet, CLASS_ResultSet, METHODN_next, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__ResultSet_get, NULL, /*delta*/0, 
		TYPE_Any, CLASS_ResultSet, METHODN_get, 1,
		CLASS_Int, FIELDN_n
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_ResultSet__dump, /*delta*/0, 
		TYPE_void, CLASS_ResultSet, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Exception_new, NULL, /*delta*/0, 
		CLASS_Exception, CLASS_Exception, METHODN_new, 3,
		CLASS_String, FIELDN_e,
		TYPE_String, FIELDN_msg,
		TYPE_Object, FIELDN_bag
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Exception__s, /*delta*/0, 
		TYPE_void, CLASS_Exception, METHODN__s, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Exception__dump, /*delta*/0, 
		TYPE_void, CLASS_Exception, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__System_getProperty, NULL, /*delta*/0, 
		TYPE_Any, CLASS_System, METHODN_getProperty, 1,
		CLASS_String, FIELDN_key
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__System_setProperty, NULL, /*delta*/0, 
		TYPE_void, CLASS_System, METHODN_setProperty, 2,
		CLASS_String, FIELDN_key,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_System__dump, /*delta*/0, 
		TYPE_void, CLASS_System, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_getClass, NULL, /*delta*/0, 
		CLASS_Class, CLASS_Object, METHODN_getClass, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_compare, NULL, /*delta*/0, 
		CLASS_Int, CLASS_Object, METHODN_compare, 1,
		TYPE_Any, FIELDN_other
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_opEq, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_Object, METHODN_opEq, 1,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_opNeq, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_Object, METHODN_opNeq, 1,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_opLt, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_Object, METHODN_opLt, 1,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_opLte, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_Object, METHODN_opLte, 1,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_opGt, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_Object, METHODN_opGt, 1,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_opGte, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_Object, METHODN_opGte, 1,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_opNot, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_Object, METHODN_opNot, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_opSeq, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_Object, METHODN_opSeq, 1,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_opIsMapTo, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_Object, METHODN_opIsMapTo, 1,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Object__s, /*delta*/0, 
		TYPE_void, CLASS_Object, METHODN__s, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Object__dump, /*delta*/0, 
		TYPE_void, CLASS_Object, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Object__empty, /*delta*/0, 
		TYPE_void, CLASS_Object, METHODN__empty, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Object__refc, /*delta*/0, 
		TYPE_void, CLASS_Object, METHODN__refc, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Object__addr, /*delta*/0, 
		TYPE_void, CLASS_Object, METHODN__addr, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Connection_close, NULL, /*delta*/0, 
		TYPE_void, CLASS_Connection, METHODN_close, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Mutex__dump, /*delta*/0, 
		TYPE_void, CLASS_Mutex, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictSet_new, NULL, /*delta*/0, 
		CLASS_DictSet, CLASS_DictSet, METHODN_new, 1,
		TYPE_Int, FIELDN_initialCapacity
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictSet_get, NULL, /*delta*/0, 
		CLASS_Int, CLASS_DictSet, METHODN_get, 1,
		CLASS_String, FIELDN_key
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictSet_opIn, NULL, /*delta*/0, 
		TYPE_Bool, CLASS_DictSet, METHODN_opIn, 1,
		TYPE_Any, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictSet_set, NULL, /*delta*/0, 
		TYPE_void, CLASS_DictSet, METHODN_set, 2,
		CLASS_String, FIELDN_key,
		CLASS_Int, FIELDN_value
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictSet_add, NULL, /*delta*/0, 
		TYPE_void, CLASS_DictSet, METHODN_add, 1,
		CLASS_String, FIELDN_key
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictSet_clear, NULL, /*delta*/0, 
		TYPE_void, CLASS_DictSet, METHODN_clear, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_DictSet__dump, /*delta*/0, 
		TYPE_void, CLASS_DictSet, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Class__s, /*delta*/0, 
		TYPE_void, CLASS_Class, METHODN__s, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Class__dump, /*delta*/0, 
		TYPE_void, CLASS_Class, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_Int64__dump, /*delta*/0, 
		TYPE_void, CLASS_Int64, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__String_equals, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_String, METHODN_equals, 1,
		CLASS_String, FIELDN_s
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__String_startsWith, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_String, METHODN_startsWith, 1,
		CLASS_String, FIELDN_s
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__String_endsWith, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_String, METHODN_endsWith, 1,
		CLASS_String, FIELDN_s
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__String_getSize, NULL, /*delta*/0, 
		CLASS_Int, CLASS_String, METHODN_getSize, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__String_opMul, NULL, /*delta*/0, 
		CLASS_String, CLASS_String, METHODN_opMul, 1,
		CLASS_Int, FIELDN_n
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_String__s, /*delta*/0, 
		TYPE_void, CLASS_String, METHODN__s, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_String__dump, /*delta*/0, 
		TYPE_void, CLASS_String, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, knh_ClassRel__dump, /*delta*/0, 
		TYPE_void, CLASS_ClassRel, METHODN__dump, 2,
		TYPE_OutputStream, FIELDN_w,
		TYPE_Any, FIELDN_m
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_isRelease, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Object, METHODN_isRelease, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_isDebug, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Object, METHODN_isDebug, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_isImmutable, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Object, METHODN_isImmutable, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_hasMetaData, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Object, METHODN_hasMetaData, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_isSynchronized, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Object, METHODN_isSynchronized, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_isModified, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Object, METHODN_isModified, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_setModified, NULL, /*delta*/0, 
		TYPE_void, CLASS_Object, METHODN_setModified, 1,
		TYPE_Bool, FIELDN_b
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isRelease, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Class, METHODN_isRelease, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isDebug, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Class, METHODN_isDebug, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isImmutable, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Class, METHODN_isImmutable, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isMetaExtensible, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Class, METHODN_isMetaExtensible, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isPrivate, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Class, METHODN_isPrivate, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isPublic, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Class, METHODN_isPublic, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isFinal, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Class, METHODN_isFinal, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isSystem, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Class, METHODN_isSystem, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isNA, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Class, METHODN_isNA, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isPublic, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Method, METHODN_isPublic, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isPrivate, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Method, METHODN_isPrivate, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isVirtual, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Method, METHODN_isVirtual, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isFinal, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Method, METHODN_isFinal, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isStatic, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Method, METHODN_isStatic, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isClass, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Method, METHODN_isClass, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isVarArgs, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Method, METHODN_isVarArgs, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isAspect, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Method, METHODN_isAspect, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__MapMap_isInterface, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_MapMap, METHODN_isInterface, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__MapMap_isSignificant, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_MapMap, METHODN_isSignificant, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__MapMap_isSynonym, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_MapMap, METHODN_isSynonym, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__MapMap_isLossLess, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_MapMap, METHODN_isLossLess, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__MapMap_isTotal, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_MapMap, METHODN_isTotal, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__MapMap_isPartial, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_MapMap, METHODN_isPartial, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__MapMap_isStatic, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_MapMap, METHODN_isStatic, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__MapMap_isTemporal, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_MapMap, METHODN_isTemporal, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__MapMap_isLocal, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_MapMap, METHODN_isLocal, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__MapMap_isDerived, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_MapMap, METHODN_isDerived, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__IntUnit_isUnsigned, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_IntUnit, METHODN_isUnsigned, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Exception_isFatal, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Exception, METHODN_isFatal, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Exception_isLogging, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Exception, METHODN_isLogging, 0
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Exception_isGenerated, NULL, /*delta*/0, 
		CLASS_Bool, CLASS_Exception, METHODN_isGenerated, 0
	);

	KNH_TMAPMAP(ctx, 
		0, 
		CLASS_Bytes, CLASS_String,  
		knh_Bytes_String, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_String, CLASS_Bytes,  
		knh_String_Bytes, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		0, 
		CLASS_String, CLASS_Int,  
		knh_String_Int, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_Int, CLASS_String,  
		knh_Int_String, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_Bool, CLASS_String,  
		knh_Bool_String, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		0, 
		CLASS_String, CLASS_Float,  
		knh_String_Float, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		0, 
		CLASS_Float, CLASS_String,  
		knh_Float_String, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		0, 
		CLASS_Int, CLASS_Float,  
		knh_Int_Float, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		0, 
		CLASS_Float, CLASS_Int,  
		knh_Float_Int, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_Array, CLASS_Tuple,  
		knh_Array_Tuple, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_InputStream, CLASS_String__,  
		knh_InputStream_String__, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_Array, CLASS_Iterator,  
		knh_Array_Iterator, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_DictMap, CLASS_Iterator,  
		knh_DictMap_Iterator, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_HashMap, CLASS_Iterator,  
		knh_HashMap_Iterator, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_Nue, CLASS_String,  
		knh_Nue_String, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_Iterator, CLASS_Array,  
		knh_Iterator_Array, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_HashSet, CLASS_Iterator,  
		knh_HashSet_Iterator, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		0, 
		CLASS_ResultSet, CLASS_Iterator,  
		knh_ResultSet_Iterator, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_Object, CLASS_Iterator,  
		knh_Object_Iterator, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_Object, CLASS_String,  
		knh_Object_String, KNH_NULL
	);

	KNH_TMAPMAP(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_DictSet, CLASS_Iterator,  
		knh_DictSet_Iterator, KNH_NULL
	);

}

#ifdef __cplusplus
}
#endif
