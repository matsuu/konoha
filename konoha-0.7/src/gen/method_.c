/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER  
 * 
 * Copyright (c) 2005-2009, Kimio Kuramitsu <kimio at ynu.ac.jp>
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

#ifdef KNH_CC_METHODAPI

/* ======================================================================== */
/* [flag] */

static 
METHOD knh__Object_isRelease(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_isRelease((knh_Object_t*)sfp[0].o));
}

static
METHOD knh__Object_isDebug(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(knh_Object_isRelease((knh_Object_t*)sfp[0].o)));
}

static 
METHOD knh__Object_isImmutable(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_isImmutable((knh_Object_t*)sfp[0].o));
}

static 
METHOD knh__Object_isUndefined(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_isUndefined((knh_Object_t*)sfp[0].o));
}

static 
METHOD knh__Object_isModified(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_isModified((knh_Object_t*)sfp[0].o));
}

static
METHOD knh__Object_setModified(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Object_setModified((knh_Object_t*)sfp[0].o, p_bool(sfp[1]));
	KNH_RETURN_void(ctx, sfp);
}

static 
METHOD knh__Object_isShared(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_isShared((knh_Object_t*)sfp[0].o));
}

static
METHOD knh__Object_setShared(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Object_setShared((knh_Object_t*)sfp[0].o, p_bool(sfp[1]));
	KNH_RETURN_void(ctx, sfp);
}

static 
METHOD knh__DictMap_isIgnoreCase(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_DictMap_isIgnoreCase((knh_DictMap_t*)sfp[0].o));
}

static 
METHOD knh__DictSet_isIgnoreCase(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_DictSet_isIgnoreCase((knh_DictSet_t*)sfp[0].o));
}

static 
METHOD knh__Class_isRelease(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_class_isRelease(knh_Class_cid(sfp[0].c)));
}

static
METHOD knh__Class_isDebug(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(knh_class_isRelease(knh_Class_cid(sfp[0].c))));
}

static 
METHOD knh__Class_isImmutable(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_class_isImmutable(knh_Class_cid(sfp[0].c)));
}

static 
METHOD knh__Class_isMetaClass(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_class_isMetaClass(knh_Class_cid(sfp[0].c)));
}

static 
METHOD knh__Class_isPrivate(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_class_isPrivate(knh_Class_cid(sfp[0].c)));
}

static
METHOD knh__Class_isPublic(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(knh_class_isPrivate(knh_Class_cid(sfp[0].c))));
}

static 
METHOD knh__Class_isFinal(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_class_isFinal(knh_Class_cid(sfp[0].c)));
}

static 
METHOD knh__Class_isSingleton(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_class_isSingleton(knh_Class_cid(sfp[0].c)));
}

static 
METHOD knh__Class_isInterface(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_class_isInterface(knh_Class_cid(sfp[0].c)));
}

static 
METHOD knh__Method_isPrivate(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Method_isPrivate((knh_Method_t*)sfp[0].o));
}

static
METHOD knh__Method_isPublic(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(knh_Method_isPrivate((knh_Method_t*)sfp[0].o)));
}

static 
METHOD knh__Method_isVirtual(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Method_isVirtual((knh_Method_t*)sfp[0].o));
}

static
METHOD knh__Method_isFinal(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(knh_Method_isVirtual((knh_Method_t*)sfp[0].o)));
}

static 
METHOD knh__Method_isConst(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Method_isConst((knh_Method_t*)sfp[0].o));
}

static 
METHOD knh__Method_isStatic(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Method_isStatic((knh_Method_t*)sfp[0].o));
}

static 
METHOD knh__Method_isVarArgs(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Method_isVarArgs((knh_Method_t*)sfp[0].o));
}

static 
METHOD knh__Mapper_isInterface(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Mapper_isInterface((knh_Mapper_t*)sfp[0].o));
}

static 
METHOD knh__Mapper_isICast(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Mapper_isICast((knh_Mapper_t*)sfp[0].o));
}

static 
METHOD knh__Mapper_isSignificant(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Mapper_isSignificant((knh_Mapper_t*)sfp[0].o));
}

static 
METHOD knh__Mapper_isFinal(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Mapper_isFinal((knh_Mapper_t*)sfp[0].o));
}

static 
METHOD knh__Mapper_isSynonym(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Mapper_isSynonym((knh_Mapper_t*)sfp[0].o));
}

static 
METHOD knh__Mapper_isLossLess(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Mapper_isLossLess((knh_Mapper_t*)sfp[0].o));
}

static 
METHOD knh__Mapper_isTotal(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Mapper_isTotal((knh_Mapper_t*)sfp[0].o));
}

static
METHOD knh__Mapper_isPartial(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(knh_Mapper_isTotal((knh_Mapper_t*)sfp[0].o)));
}

static 
METHOD knh__Mapper_isConst(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Mapper_isConst((knh_Mapper_t*)sfp[0].o));
}

static
METHOD knh__Mapper_isTemporal(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(knh_Mapper_isConst((knh_Mapper_t*)sfp[0].o)));
}

static 
METHOD knh__Mapper_isLocal(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Mapper_isLocal((knh_Mapper_t*)sfp[0].o));
}

static 
METHOD knh__Mapper_isDerived(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Mapper_isDerived((knh_Mapper_t*)sfp[0].o));
}

static 
METHOD knh__OutputStream_isAutoFlush(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_OutputStream_isAutoFlush((knh_OutputStream_t*)sfp[0].o));
}

static
METHOD knh__OutputStream_setAutoFlush(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_OutputStream_setAutoFlush((knh_OutputStream_t*)sfp[0].o, p_bool(sfp[1]));
	KNH_RETURN_void(ctx, sfp);
}

static 
METHOD knh__OutputStream_isStoringBuffer(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_OutputStream_isStoringBuffer((knh_OutputStream_t*)sfp[0].o));
}

static
METHOD knh__OutputStream_setStoringBuffer(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_OutputStream_setStoringBuffer((knh_OutputStream_t*)sfp[0].o, p_bool(sfp[1]));
	KNH_RETURN_void(ctx, sfp);
}

static 
METHOD knh__Exception_isFatal(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Exception_isFatal((knh_Exception_t*)sfp[0].o));
}

static 
METHOD knh__Exception_isLogging(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Exception_isLogging((knh_Exception_t*)sfp[0].o));
}

static 
METHOD knh__Exception_isGenerated(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Exception_isGenerated((knh_Exception_t*)sfp[0].o));
}

static 
METHOD knh__Context_isStrict(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Context_isStrict((knh_Context_t*)sfp[0].o));
}

static
METHOD knh__Context_setStrict(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Context_setStrict((knh_Context_t*)sfp[0].o, p_bool(sfp[1]));
	KNH_RETURN_void(ctx, sfp);
}

static 
METHOD knh__Context_isDebug(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Context_isDebug((knh_Context_t*)sfp[0].o));
}

static
METHOD knh__Context_setDebug(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Context_setDebug((knh_Context_t*)sfp[0].o, p_bool(sfp[1]));
	KNH_RETURN_void(ctx, sfp);
}

static 
METHOD knh__Context_isVerbose(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Context_isVerbose((knh_Context_t*)sfp[0].o));
}

static
METHOD knh__Context_setVerbose(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Context_setVerbose((knh_Context_t*)sfp[0].o, p_bool(sfp[1]));
	KNH_RETURN_void(ctx, sfp);
}

static 
METHOD knh__Context_isInteractive(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Context_isInteractive((knh_Context_t*)sfp[0].o));
}

/* ======================================================================== */
/* [method] */

static
METHOD knh__Array_clear(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void Array.clear()  */
	knh_Array_clear(
		ctx,
		(knh_Array_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

static
METHOD knh__InputStream_setEncoding(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void InputStream.setEncoding(String enc)  */
	knh_InputStream_setEncoding(
		ctx,
		(knh_InputStream_t*)sfp[0].o,
		(String*)sfp[1].o /* String sfp[1].o => String* enc */
	);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

static
METHOD knh__OutputStream_setEncoding(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void OutputStream.setEncoding(String enc)  */
	knh_OutputStream_setEncoding(
		ctx,
		(knh_OutputStream_t*)sfp[0].o,
		(String*)sfp[1].o /* String sfp[1].o => String* enc */
	);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

static
METHOD knh__Context_getProperty(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Any Context.getProperty(String! key)  */
	Object *rv = (Object*)knh_Context_getProperty(
		ctx,
		(knh_Context_t*)sfp[0].o,
		knh_String_tobytes((String*)sfp[1].o) /* String! sfp[1].o => knh_bytes_t key */
	);
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__Context_setProperty(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void Context.setProperty(String! key, Any value)  */
	knh_Context_setProperty(
		ctx,
		(knh_Context_t*)sfp[0].o,
		(String*)sfp[1].o /* String! sfp[1].o => String* key */,
		(Any*)sfp[2].o /* Any sfp[2].o => Any* value */
	);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

static
METHOD knh__Context_setEncoding(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void Context.setEncoding(String enc)  */
	knh_Context_setEncoding(
		ctx,
		(knh_Context_t*)sfp[0].o,
		(String*)sfp[1].o /* String sfp[1].o => String* enc */
	);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

static
METHOD knh__Connection_close(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void Connection.close()  */
	knh_Connection_close(
		ctx,
		(knh_Connection_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

static
METHOD knh__DictIdx_size(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Int! DictIdx.size()  */
	size_t v = knh_DictIdx_size(
		(knh_DictIdx_t*)sfp[0].o
	);
	Object* rv = (Object*)new_Int(ctx, (knh_int_t)v) /* size_t v => Int rv */;
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__DictIdx_index(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Int! DictIdx.index(String! term)  */
	knh_index_t v = knh_DictIdx_index(
		ctx,
		(knh_DictIdx_t*)sfp[0].o,
		knh_String_tobytes((String*)sfp[1].o) /* String! sfp[1].o => knh_bytes_t v */
	);
	Object* rv = (Object*)new_Int(ctx, v) /* knh_index_t v => Int rv */;
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__DictIdx_add__fast(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Int! DictIdx.add::fast(String! term)  */
	knh_index_t v = knh_DictIdx_add__fast(
		ctx,
		(knh_DictIdx_t*)sfp[0].o,
		(String*)sfp[1].o /* String! sfp[1].o => String* term */
	);
	Object* rv = (Object*)new_Int(ctx, v) /* knh_index_t v => Int rv */;
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__DictIdx_add(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Int! DictIdx.add(String! term)  */
	knh_index_t v = knh_DictIdx_add(
		ctx,
		(knh_DictIdx_t*)sfp[0].o,
		(String*)sfp[1].o /* String! sfp[1].o => String* term */
	);
	Object* rv = (Object*)new_Int(ctx, v) /* knh_index_t v => Int rv */;
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__DictIdx_clear(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void DictIdx.clear()  */
	knh_DictIdx_clear(
		ctx,
		(knh_DictIdx_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

static
METHOD knh__Exception_new__init(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Exception! Exception.new:init(String e, String msg, Object bag)  */
	Object *rv = (Object*)knh_Exception_new__init(
		ctx,
		(knh_Exception_t*)sfp[0].o,
		(String*)sfp[1].o /* String sfp[1].o => String* e */,
		(String*)sfp[2].o /* String sfp[2].o => String* msg */,
		(Object*)sfp[3].o /* Object sfp[3].o => Object* bag */
	);
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__InputStream_readLine(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method String InputStream.readLine()  */
	Object *rv = (Object*)knh_InputStream_readLine(
		ctx,
		(knh_InputStream_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__InputStream_close(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void InputStream.close()  */
	knh_InputStream_close(
		ctx,
		(knh_InputStream_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

static
METHOD knh__Method_isAbstract(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Boolean! Method.isAbstract()  */
	knh_bool_t v = knh_Method_isAbstract(
		(knh_Method_t*)sfp[0].o
	);
	Object* rv = (Object*)new_Boolean(ctx, v) /* knh_bool_t v => Boolean rv */;
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__Method_getName(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method String! Method.getName()  */
	Object *rv = (Object*)knh_Method_getName(
		ctx,
		(knh_Method_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__OutputStream_flush(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void OutputStream.flush()  */
	knh_OutputStream_flush(
		ctx,
		(knh_OutputStream_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

static
METHOD knh__OutputStream_clear(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void OutputStream.clear()  */
	knh_OutputStream_clear(
		ctx,
		(knh_OutputStream_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

static
METHOD knh__OutputStream_close(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void OutputStream.close()  */
	knh_OutputStream_close(
		ctx,
		(knh_OutputStream_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

static
METHOD knh__ResultSet_close(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void ResultSet.close()  */
	knh_ResultSet_close(
		ctx,
		(knh_ResultSet_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

static
METHOD knh__System_getProperty(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Any System.getProperty(String! key)  */
	Object *rv = (Object*)knh_System_getProperty(
		ctx,
		(knh_System_t*)sfp[0].o,
		knh_String_tobytes((String*)sfp[1].o) /* String! sfp[1].o => knh_bytes_t key */
	);
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__System_setProperty(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void System.setProperty(String! key, Any value)  */
	knh_System_setProperty(
		ctx,
		(knh_System_t*)sfp[0].o,
		(String*)sfp[1].o /* String! sfp[1].o => String* key */,
		(Any*)sfp[2].o /* Any sfp[2].o => Any* value */
	);
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

#endif/*KNH_CC_METHODAPI*/

#ifdef __cplusplus
}
#endif
