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
/* [prototype] */

int knhdemo_init(Ctx *ctx);
int knhmath_init(Ctx *ctx);
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
	KNH_RETURN_Boolean(ctx, sfp, !(knh_Object_isDebug((knh_Object_t*)sfp[0].o)));
}

static 
METHOD knh__Object_isImmutable(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_isImmutable((knh_Object_t*)sfp[0].o));
}

static 
METHOD knh__Object_hasMetaData(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_hasMetaData((knh_Object_t*)sfp[0].o));
}

static 
METHOD knh__Object_isSynchronized(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_isSynchronized((knh_Object_t*)sfp[0].o));
}

static 
METHOD knh__Object_isModified(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_isModified((knh_Object_t*)sfp[0].o));
}

static
METHOD knh__Object_setModified(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Object_setModified((knh_Object_t*)sfp[0].o, IS_TRUE(sfp[1].o));
	KNH_RETURN_void(ctx, sfp);
}

static 
METHOD knh__Object_isGCMarked(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_isGCMarked((knh_Object_t*)sfp[0].o));
}

static
METHOD knh__Object_setGCMarked(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Object_setGCMarked((knh_Object_t*)sfp[0].o, IS_TRUE(sfp[1].o));
	KNH_RETURN_void(ctx, sfp);
}

static 
METHOD knh__Object_isFormatted(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Object_isFormatted((knh_Object_t*)sfp[0].o));
}

static
METHOD knh__Object_setFormatted(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Object_setFormatted((knh_Object_t*)sfp[0].o, IS_TRUE(sfp[1].o));
	KNH_RETURN_void(ctx, sfp);
}

static 
METHOD knh__Class_isRelease(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_class_isRelease(knh_Class_cid(sfp[0].c)));
}

static
METHOD knh__Class_isDebug(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(knh_class_isDebug(knh_Class_cid(sfp[0].c))));
}

static 
METHOD knh__Class_isImmutable(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_class_isImmutable(knh_Class_cid(sfp[0].c)));
}

static 
METHOD knh__Class_isMetaExtensible(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_class_isMetaExtensible(knh_Class_cid(sfp[0].c)));
}

static 
METHOD knh__Class_isPrivate(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_class_isPrivate(knh_Class_cid(sfp[0].c)));
}

static
METHOD knh__Class_isPublic(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(knh_class_isPublic(knh_Class_cid(sfp[0].c))));
}

static 
METHOD knh__Class_isFinal(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_class_isFinal(knh_Class_cid(sfp[0].c)));
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
	KNH_RETURN_Boolean(ctx, sfp, !(knh_Method_isPublic((knh_Method_t*)sfp[0].o)));
}

static 
METHOD knh__Method_isVirtual(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Method_isVirtual((knh_Method_t*)sfp[0].o));
}

static
METHOD knh__Method_isFinal(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(knh_Method_isFinal((knh_Method_t*)sfp[0].o)));
}

static 
METHOD knh__Method_isStatic(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Method_isStatic((knh_Method_t*)sfp[0].o));
}

static 
METHOD knh__Method_isClassFunc(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Method_isClassFunc((knh_Method_t*)sfp[0].o));
}

static 
METHOD knh__Method_isNullBase(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Method_isNullBase((knh_Method_t*)sfp[0].o));
}

static 
METHOD knh__Method_isVarArgs(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Method_isVarArgs((knh_Method_t*)sfp[0].o));
}

static 
METHOD knh__Method_isAspect(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Method_isAspect((knh_Method_t*)sfp[0].o));
}

static 
METHOD knh__Mapper_isInterface(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Mapper_isInterface((knh_Mapper_t*)sfp[0].o));
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
	KNH_RETURN_Boolean(ctx, sfp, !(knh_Mapper_isPartial((knh_Mapper_t*)sfp[0].o)));
}

static 
METHOD knh__Mapper_isStatic(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Mapper_isStatic((knh_Mapper_t*)sfp[0].o));
}

static
METHOD knh__Mapper_isTemporal(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(knh_Mapper_isTemporal((knh_Mapper_t*)sfp[0].o)));
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
METHOD knh__IntUnit_isUnsigned(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_IntUnit_isUnsigned((knh_IntUnit_t*)sfp[0].o));
}

static 
METHOD knh__OutputStream_isAutoFlush(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_OutputStream_isAutoFlush((knh_OutputStream_t*)sfp[0].o));
}

static
METHOD knh__OutputStream_setAutoFlush(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_OutputStream_setAutoFlush((knh_OutputStream_t*)sfp[0].o, IS_TRUE(sfp[1].o));
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
METHOD knh__Context_isRelease(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Context_isRelease((knh_Context_t*)sfp[0].o));
}

static
METHOD knh__Context_isDebug(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, !(knh_Context_isDebug((knh_Context_t*)sfp[0].o)));
}

static
METHOD knh__Context_setRelease(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Context_setRelease((knh_Context_t*)sfp[0].o, IS_TRUE(sfp[1].o));
	KNH_RETURN_void(ctx, sfp);
}

static
METHOD knh__Context_setDebug(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Context_setDebug((knh_Context_t*)sfp[0].o, IS_TRUE(sfp[1].o));
	KNH_RETURN_void(ctx, sfp);
}

static 
METHOD knh__Context_isCompiling(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Context_isCompiling((knh_Context_t*)sfp[0].o));
}

static
METHOD knh__Context_setCompiling(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Context_setCompiling((knh_Context_t*)sfp[0].o, IS_TRUE(sfp[1].o));
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
	knh_Context_setVerbose((knh_Context_t*)sfp[0].o, IS_TRUE(sfp[1].o));
	KNH_RETURN_void(ctx, sfp);
}

static 
METHOD knh__Context_isVerbose2(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_Context_isVerbose2((knh_Context_t*)sfp[0].o));
}

static
METHOD knh__Context_setVerbose2(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Context_setVerbose2((knh_Context_t*)sfp[0].o, IS_TRUE(sfp[1].o));
	KNH_RETURN_void(ctx, sfp);
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
	KNH_RETURN(ctx, sfp, KNH_VOID);
}

static
METHOD knh__Connection_close(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void Connection.close()  */
	knh_Connection_close(
		ctx,
		(knh_Connection_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, KNH_VOID);
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
	KNH_RETURN(ctx, sfp, KNH_VOID);
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
	KNH_RETURN(ctx, sfp, KNH_VOID);
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
METHOD knh__DictIdx_get__fast(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method String DictIdx.get::fast(Int! index)  */
	Object *rv = (Object*)knh_DictIdx_get__fast(
		(knh_DictIdx_t*)sfp[0].o,
		knh_Int_toint((Int*)sfp[1].o) /* Int! sfp[1].o => knh_int_t termid */
	);
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__DictIdx_get(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method String DictIdx.get(Int! index)  */
	Object *rv = (Object*)knh_DictIdx_get(
		(knh_DictIdx_t*)sfp[0].o,
		knh_Int_toint((Int*)sfp[1].o) /* Int! sfp[1].o => knh_int_t termid */
	);
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
	KNH_RETURN(ctx, sfp, KNH_VOID);
}

static
METHOD knh__DictMap_new(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method DictMap! DictMap.new(Int initialCapacity)  */
	Object *rv = (Object*)knh_DictMap_new(
		ctx,
		(knh_DictMap_t*)sfp[0].o,
		knh_IntNULL_toint((Int*)sfp[1].o) /* Int sfp[1].o => knh_int_t initialCapacity */
	);
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__DictMap_get(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Any DictMap.get(String! key)  */
	Object *rv = (Object*)knh_DictMap_get(
		ctx,
		(knh_DictMap_t*)sfp[0].o,
		(String*)sfp[1].o /* String! sfp[1].o => String* key */
	);
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__DictMap_append(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void DictMap.append(String! key, Any! value)  */
	knh_DictMap_append(
		ctx,
		(knh_DictMap_t*)sfp[0].o,
		(String*)sfp[1].o /* String! sfp[1].o => String* key */,
		(Any*)sfp[2].o /* Any! sfp[2].o => Any* value */
	);
	KNH_RETURN(ctx, sfp, KNH_VOID);
}

static
METHOD knh__DictMap_set(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void DictMap.set(String! key, Any value)  */
	knh_DictMap_set(
		ctx,
		(knh_DictMap_t*)sfp[0].o,
		(String*)sfp[1].o /* String! sfp[1].o => String* key */,
		(Any*)sfp[2].o /* Any sfp[2].o => Any* v */
	);
	KNH_RETURN(ctx, sfp, KNH_VOID);
}

static
METHOD knh__DictMap_remove(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void DictMap.remove(String! key)  */
	knh_DictMap_remove(
		ctx,
		(knh_DictMap_t*)sfp[0].o,
		(String*)sfp[1].o /* String! sfp[1].o => String* key */
	);
	KNH_RETURN(ctx, sfp, KNH_VOID);
}

static
METHOD knh__DictMap_clear(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void DictMap.clear()  */
	knh_DictMap_clear(
		ctx,
		(knh_DictMap_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, KNH_VOID);
}

static
METHOD knh__DictSet_new(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method DictSet! DictSet.new(Int initialCapacity=0)  */
	Object *rv = (Object*)knh_DictSet_new(
		ctx,
		(knh_DictSet_t*)sfp[0].o,
		knh_IntNULL_toint((Int*)sfp[1].o) /* Int sfp[1].o => knh_int_t initialCapacity */
	);
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__DictSet_get(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Int! DictSet.get(String! key)  */
	knh_int_t v = knh_DictSet_get(
		(knh_DictSet_t*)sfp[0].o,
		(String*)sfp[1].o /* String! sfp[1].o => String* key */
	);
	Object* rv = (Object*)new_Int(ctx, v) /* knh_int_t v => Int rv */;
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__DictSet_opIn(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Boolean DictSet.opIn(Any value)  */
	knh_bool_t v = knh_DictSet_opIn(
		ctx,
		(knh_DictSet_t*)sfp[0].o,
		(Any*)sfp[1].o /* Any sfp[1].o => Any* value */
	);
	Object* rv = (Object*)new_Boolean(ctx, v) /* knh_bool_t v => Boolean rv */;
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__DictSet_set(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void DictSet.set(String! key, Int! value)  */
	knh_DictSet_set(
		ctx,
		(knh_DictSet_t*)sfp[0].o,
		(String*)sfp[1].o /* String! sfp[1].o => String* key */,
		(knh_uint_t)knh_Int_toint((Int*)sfp[2].o) /* Int! sfp[2].o => knh_uint_t value */
	);
	KNH_RETURN(ctx, sfp, KNH_VOID);
}

static
METHOD knh__DictSet_add(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void DictSet.add(String! key)  */
	knh_DictSet_add(
		ctx,
		(knh_DictSet_t*)sfp[0].o,
		(String*)sfp[1].o /* String! sfp[1].o => String* key */
	);
	KNH_RETURN(ctx, sfp, KNH_VOID);
}

static
METHOD knh__DictSet_clear(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void DictSet.clear()  */
	knh_DictSet_clear(
		ctx,
		(knh_DictSet_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, KNH_VOID);
}

static
METHOD knh__HashMap_clear(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void HashMap.clear()  */
	knh_HashMap_clear(
		ctx,
		(knh_HashMap_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, KNH_VOID);
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
	KNH_RETURN(ctx, sfp, KNH_VOID);
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
	KNH_RETURN(ctx, sfp, KNH_VOID);
}

static
METHOD knh__Method_isAbstract(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Boolean Method.isAbstract()  */
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
METHOD knh__Method_getURN(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method String! Method.getURN()  */
	Object *rv = (Object*)knh_Method_getURN(
		ctx,
		(knh_Method_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__Object_compareTo(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Int! Object.compareTo(Any o)  */
	int v = knh_Object_compareTo(
		(knh_Object_t*)sfp[0].o,
		(Object*)sfp[1].o /* Any sfp[1].o => Object* o2 */
	);
	Object* rv = (Object*)new_Int(ctx, (knh_int_t)v) /* int v => Int rv */;
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
	KNH_RETURN(ctx, sfp, KNH_VOID);
}

static
METHOD knh__OutputStream_close(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method void OutputStream.close()  */
	knh_OutputStream_close(
		ctx,
		(knh_OutputStream_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, KNH_VOID);
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
	KNH_RETURN(ctx, sfp, KNH_VOID);
}

static
METHOD knh__ResultSet_next(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method ResultSet ResultSet.next()  */
	Object *rv = (Object*)knh_ResultSet_next(
		ctx,
		(knh_ResultSet_t*)sfp[0].o
	);
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__String_equals(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Boolean! String.equals(String! s)  */
	knh_bool_t v = knh_String_equals(
		(knh_String_t*)sfp[0].o,
		knh_String_tobytes((String*)sfp[1].o) /* String! sfp[1].o => knh_bytes_t s */
	);
	Object* rv = (Object*)new_Boolean(ctx, v) /* knh_bool_t v => Boolean rv */;
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__String_startsWith(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Boolean! String.startsWith(String! s)  */
	knh_bool_t v = knh_String_startsWith(
		(knh_String_t*)sfp[0].o,
		knh_String_tobytes((String*)sfp[1].o) /* String! sfp[1].o => knh_bytes_t s */
	);
	Object* rv = (Object*)new_Boolean(ctx, v) /* knh_bool_t v => Boolean rv */;
	KNH_RETURN(ctx, sfp, rv);
}

static
METHOD knh__String_endsWith(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Boolean! String.endsWith(String! s)  */
	knh_bool_t v = knh_String_endsWith(
		(knh_String_t*)sfp[0].o,
		knh_String_tobytes((String*)sfp[1].o) /* String! sfp[1].o => knh_bytes_t s */
	);
	Object* rv = (Object*)new_Boolean(ctx, v) /* knh_bool_t v => Boolean rv */;
	KNH_RETURN(ctx, sfp, rv);
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
	KNH_RETURN(ctx, sfp, KNH_VOID);
}

static
METHOD knh__Tuple2_get__fast(Ctx *ctx, knh_sfp_t *sfp)
{
	/* method Any Tuple2.get:fast(Int! index)  */
	Object *rv = (Object*)knh_Tuple2_get__fast(
		(knh_Tuple2_t*)sfp[0].o,
		knh_Int_toint((Int*)sfp[1].o) /* Int! sfp[1].o => knh_int_t index */
	);
	KNH_RETURN(ctx, sfp, rv);
}

/* ======================================================================== */
/* [tmapper] */

INLINE static
void KNH_TMAPPER_Array_Iterator(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_Iterator_t* (*fmapfunc)(Ctx *, knh_Array_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

INLINE static
void KNH_TMAPPER_Iterator_Array(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_Array_t* (*fmapfunc)(Ctx *, knh_Iterator_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

INLINE static
void KNH_TMAPPER_Boolean_String(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_String_t* (*fmapfunc)(Ctx *, knh_Boolean_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

INLINE static
void KNH_TMAPPER_Bytes_String(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_String_t* (*fmapfunc)(Ctx *, knh_Bytes_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

INLINE static
void KNH_TMAPPER_String_Bytes(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_Bytes_t* (*fmapfunc)(Ctx *, knh_String_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

INLINE static
void KNH_TMAPPER_DictMap_Iterator(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_Iterator_t* (*fmapfunc)(Ctx *, knh_DictMap_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

INLINE static
void KNH_TMAPPER_DictSet_Iterator(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_Iterator_t* (*fmapfunc)(Ctx *, knh_DictSet_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

INLINE static
void KNH_TMAPPER_String_Float(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_Float_t* (*fmapfunc)(Ctx *, knh_String_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

INLINE static
void KNH_TMAPPER_Float_String(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_String_t* (*fmapfunc)(Ctx *, knh_Float_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

INLINE static
void KNH_TMAPPER_Int_Float(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_Float_t* (*fmapfunc)(Ctx *, knh_Int_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

INLINE static
void KNH_TMAPPER_Float_Int(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_Int_t* (*fmapfunc)(Ctx *, knh_Float_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

INLINE static
void KNH_TMAPPER_HashMap_Iterator(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_Iterator_t* (*fmapfunc)(Ctx *, knh_HashMap_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

INLINE static
void KNH_TMAPPER_InputStream_String(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_Iterator_t* (*fmapfunc)(Ctx *, knh_InputStream_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

INLINE static
void KNH_TMAPPER_String_Int(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_Int_t* (*fmapfunc)(Ctx *, knh_String_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

INLINE static
void KNH_TMAPPER_Int_String(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_String_t* (*fmapfunc)(Ctx *, knh_Int_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

INLINE static
void KNH_TMAPPER_Object_String(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_String_t* (*fmapfunc)(Ctx *, knh_Object_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

INLINE static
void KNH_TMAPPER_Object_Iterator(
	Ctx *ctx,
	knh_flag_t flag,
	knh_class_t scid,
	knh_class_t tcid,
	knh_Iterator_t* (*fmapfunc)(Ctx *, knh_Object_t*, knh_Mapper_t *),
	Object *mapopt) {
	KNH_TMAPPER(ctx, flag, scid, tcid, (f_mapper)fmapfunc, mapopt);
}

/* ======================================================================== */
/* [INIT] */

void knh_tString_init0(void)
{
	DEBUG_ASSERT(knh_tString != NULL);

	KNH_INITv(knh_tString[TSN_EMPTY], new_String__T(NULL, ""));
	KNH_INITv(knh_tString[TSN_TAB], new_String__T(NULL, "\t"));
	KNH_INITv(knh_tString[TSN_LF], new_String__T(NULL, "\n"));
	KNH_INITv(knh_tString[TSN_SPC], new_String__T(NULL, " "));
	KNH_INITv(knh_tString[TSN_EOL], new_String__T(NULL, "EOL"));
	KNH_INITv(knh_tString[TSN_BEGIN], new_String__T(NULL, "BEGIN"));
	KNH_INITv(knh_tString[TSN_END], new_String__T(NULL, "END"));
	KNH_INITv(knh_tString[TSN_void], new_String__T(NULL, "void"));
	KNH_INITv(knh_tString[TSN_true], new_String__T(NULL, "true"));
	KNH_INITv(knh_tString[TSN_false], new_String__T(NULL, "false"));
	KNH_INITv(knh_tString[TSN_null], new_String__T(NULL, "null"));
	KNH_INITv(knh_tString[TSN_main], new_String__T(NULL, "main"));
	KNH_INITv(knh_tString[TSN_ENCODING], new_String__T(NULL, ""KONOHA_ENCODING""));
	KNH_INITv(knh_tString[TSN_DEVNULL], new_String__T(NULL, "/dev/null"));
	KNH_INITv(knh_tString[TSN_DEVSTDIN], new_String__T(NULL, "/dev/stdin"));
	KNH_INITv(knh_tString[TSN_DEVSTDERR], new_String__T(NULL, "/dev/stderr"));
	KNH_INITv(knh_tString[TSN_DEVSTDOUT], new_String__T(NULL, "/dev/stdout"));
	KNH_INITv(knh_tString[TSN_ATlabel], new_String__T(NULL, "@label"));
	KNH_INITv(knh_tString[TSN_TYPEERR], new_String__T(NULL, "Type!!"));
	KNH_INITv(knh_tString[TSN_NULLERR], new_String__T(NULL, "Null!!"));
	KNH_INITv(knh_tString[TSN_SYNTAXERR], new_String__T(NULL, "Syntax!!"));
}
static INLINE knh_struct_t KNH_TSTRUCT_Iterator(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_Iterator_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_Iterator_struct*, knh_Iterator_struct*),
	void (*fgc)(Ctx*, knh_Iterator_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(Iterator*),
	int (*fcompareTo)(Iterator*, Iterator*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_DictMap(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_DictMap_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_DictMap_struct*, knh_DictMap_struct*),
	void (*fgc)(Ctx*, knh_DictMap_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(DictMap*),
	int (*fcompareTo)(DictMap*, DictMap*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_DictSet(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_DictSet_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_DictSet_struct*, knh_DictSet_struct*),
	void (*fgc)(Ctx*, knh_DictSet_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(DictSet*),
	int (*fcompareTo)(DictSet*, DictSet*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_HashMap(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_HashMap_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_HashMap_struct*, knh_HashMap_struct*),
	void (*fgc)(Ctx*, knh_HashMap_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(HashMap*),
	int (*fcompareTo)(HashMap*, HashMap*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_HashSet(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_HashSet_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_HashSet_struct*, knh_HashSet_struct*),
	void (*fgc)(Ctx*, knh_HashSet_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(HashSet*),
	int (*fcompareTo)(HashSet*, HashSet*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_LRUHashMap(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_LRUHashMap_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_LRUHashMap_struct*, knh_LRUHashMap_struct*),
	void (*fgc)(Ctx*, knh_LRUHashMap_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(LRUHashMap*),
	int (*fcompareTo)(LRUHashMap*, LRUHashMap*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_DictIdx(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_DictIdx_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_DictIdx_struct*, knh_DictIdx_struct*),
	void (*fgc)(Ctx*, knh_DictIdx_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(DictIdx*),
	int (*fcompareTo)(DictIdx*, DictIdx*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_ClassStruct(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_ClassStruct_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_ClassStruct_struct*, knh_ClassStruct_struct*),
	void (*fgc)(Ctx*, knh_ClassStruct_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(ClassStruct*),
	int (*fcompareTo)(ClassStruct*, ClassStruct*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_MethodField(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_MethodField_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_MethodField_struct*, knh_MethodField_struct*),
	void (*fgc)(Ctx*, knh_MethodField_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(MethodField*),
	int (*fcompareTo)(MethodField*, MethodField*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_Method(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_Method_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_Method_struct*, knh_Method_struct*),
	void (*fgc)(Ctx*, knh_Method_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(Method*),
	int (*fcompareTo)(Method*, Method*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_Mapper(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_Mapper_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_Mapper_struct*, knh_Mapper_struct*),
	void (*fgc)(Ctx*, knh_Mapper_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(Mapper*),
	int (*fcompareTo)(Mapper*, Mapper*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_ClassMap(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_ClassMap_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_ClassMap_struct*, knh_ClassMap_struct*),
	void (*fgc)(Ctx*, knh_ClassMap_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(ClassMap*),
	int (*fcompareTo)(ClassMap*, ClassMap*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_AffineConv(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_AffineConv_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_AffineConv_struct*, knh_AffineConv_struct*),
	void (*fgc)(Ctx*, knh_AffineConv_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(AffineConv*),
	int (*fcompareTo)(AffineConv*, AffineConv*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_IntUnit(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_IntUnit_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_IntUnit_struct*, knh_IntUnit_struct*),
	void (*fgc)(Ctx*, knh_IntUnit_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(IntUnit*),
	int (*fcompareTo)(IntUnit*, IntUnit*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_FloatUnit(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_FloatUnit_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_FloatUnit_struct*, knh_FloatUnit_struct*),
	void (*fgc)(Ctx*, knh_FloatUnit_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(FloatUnit*),
	int (*fcompareTo)(FloatUnit*, FloatUnit*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_BytesConv(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_BytesConv_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_BytesConv_struct*, knh_BytesConv_struct*),
	void (*fgc)(Ctx*, knh_BytesConv_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(BytesConv*),
	int (*fcompareTo)(BytesConv*, BytesConv*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_StringUnit(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_StringUnit_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_StringUnit_struct*, knh_StringUnit_struct*),
	void (*fgc)(Ctx*, knh_StringUnit_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(StringUnit*),
	int (*fcompareTo)(StringUnit*, StringUnit*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_InputStream(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_InputStream_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_InputStream_struct*, knh_InputStream_struct*),
	void (*fgc)(Ctx*, knh_InputStream_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(InputStream*),
	int (*fcompareTo)(InputStream*, InputStream*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_OutputStream(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_OutputStream_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_OutputStream_struct*, knh_OutputStream_struct*),
	void (*fgc)(Ctx*, knh_OutputStream_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(OutputStream*),
	int (*fcompareTo)(OutputStream*, OutputStream*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_Connection(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_Connection_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_Connection_struct*, knh_Connection_struct*),
	void (*fgc)(Ctx*, knh_Connection_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(Connection*),
	int (*fcompareTo)(Connection*, Connection*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_ResultSet(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_ResultSet_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_ResultSet_struct*, knh_ResultSet_struct*),
	void (*fgc)(Ctx*, knh_ResultSet_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(ResultSet*),
	int (*fcompareTo)(ResultSet*, ResultSet*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_Exception(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_Exception_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_Exception_struct*, knh_Exception_struct*),
	void (*fgc)(Ctx*, knh_Exception_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(Exception*),
	int (*fcompareTo)(Exception*, Exception*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_ExceptionHandler(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_ExceptionHandler_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_ExceptionHandler_struct*, knh_ExceptionHandler_struct*),
	void (*fgc)(Ctx*, knh_ExceptionHandler_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(ExceptionHandler*),
	int (*fcompareTo)(ExceptionHandler*, ExceptionHandler*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_NameSpace(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_NameSpace_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_NameSpace_struct*, knh_NameSpace_struct*),
	void (*fgc)(Ctx*, knh_NameSpace_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(NameSpace*),
	int (*fcompareTo)(NameSpace*, NameSpace*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_Runtime(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_Runtime_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_Runtime_struct*, knh_Runtime_struct*),
	void (*fgc)(Ctx*, knh_Runtime_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(Runtime*),
	int (*fcompareTo)(Runtime*, Runtime*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_Token(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_Token_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_Token_struct*, knh_Token_struct*),
	void (*fgc)(Ctx*, knh_Token_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(Token*),
	int (*fcompareTo)(Token*, Token*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_Stmt(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_Stmt_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_Stmt_struct*, knh_Stmt_struct*),
	void (*fgc)(Ctx*, knh_Stmt_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(Stmt*),
	int (*fcompareTo)(Stmt*, Stmt*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_Compiler(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_Compiler_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_Compiler_struct*, knh_Compiler_struct*),
	void (*fgc)(Ctx*, knh_Compiler_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(Compiler*),
	int (*fcompareTo)(Compiler*, Compiler*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

static INLINE knh_struct_t KNH_TSTRUCT_KLRCode(Ctx *ctx,
	knh_struct_t sid,
	size_t size,
	char *name,
	void (*finit)(Ctx*, knh_KLRCode_struct*, int, Object*),
	void (*fcopy)(Ctx*, knh_KLRCode_struct*, knh_KLRCode_struct*),
	void (*fgc)(Ctx*, knh_KLRCode_struct*, f_traverse),
	knh_hcode_t (*fhashCode)(KLRCode*),
	int (*fcompareTo)(KLRCode*, KLRCode*)) {
	return KNH_TSTRUCT(ctx, sid, size, name, 
		(f_tStruct_init)finit, (f_tStruct_copy)fcopy, (f_tStruct_traverse)fgc,
		(f_hashCode)fhashCode, (f_compareTo)fcompareTo);
}

void konoha_class_init0(Ctx *ctx)
{
	KNH_TSTRUCT(ctx, STRUCT_Object, 0, "Object", NULL, NULL, NULL, (f_hashCode)knh_Object_hashCode, (f_compareTo)knh_Object_compareTo); 
	KNH_TSTRUCT(ctx, STRUCT_Any, 0, "Any", NULL, NULL, NULL, (f_hashCode)NULL, (f_compareTo)NULL); 
	KNH_TSTRUCT(ctx, STRUCT_Nue, 0, "Nue", NULL, NULL, NULL, (f_hashCode)NULL, (f_compareTo)knh_Nue_compareTo); 
	KNH_TSTRUCT(ctx, STRUCT_Boolean, 0, "Boolean", NULL, NULL, NULL, (f_hashCode)NULL, (f_compareTo)NULL); 
	KNH_TSTRUCT(ctx, STRUCT_Number, 0, "Number", NULL, NULL, NULL, (f_hashCode)NULL, (f_compareTo)NULL); 
	KNH_TSTRUCT(ctx, STRUCT_Int, 0, "Int", NULL, NULL, NULL, (f_hashCode)knh_Int_hashCode, (f_compareTo)knh_Int_compareTo); 
	KNH_TSTRUCT(ctx, STRUCT_Int64, 0, "Int64", NULL, NULL, NULL, (f_hashCode)NULL, (f_compareTo)NULL); 
	KNH_TSTRUCT(ctx, STRUCT_Float, 0, "Float", NULL, NULL, NULL, (f_hashCode)NULL, (f_compareTo)knh_Float_compareTo); 
	KNH_TSTRUCT(ctx, STRUCT_String, 0, "String", NULL, NULL, NULL, (f_hashCode)knh_String_hashCode, (f_compareTo)knh_String_compareTo); 
	KNH_TSTRUCT(ctx, STRUCT_Bytes, 0, "Bytes", NULL, NULL, NULL, (f_hashCode)NULL, (f_compareTo)NULL); 
	KNH_TSTRUCT(ctx, STRUCT_Tuple2, 0, "Tuple2", NULL, NULL, NULL, (f_hashCode)NULL, (f_compareTo)NULL); 
	KNH_TSTRUCT(ctx, STRUCT_Range, 0, "Range", NULL, NULL, NULL, (f_hashCode)NULL, (f_compareTo)NULL); 
	KNH_TSTRUCT(ctx, STRUCT_Array, 0, "Array", NULL, NULL, NULL, (f_hashCode)NULL, (f_compareTo)NULL); 
	KNH_TSTRUCT_Iterator(ctx, STRUCT_Iterator, sizeof(knh_Iterator_struct),
		"Iterator",
		knh_Iterator_struct_init,
		knh_Iterator_struct_copy, 
//		knh_Iterator_struct_compare, 
		knh_Iterator_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT(ctx, STRUCT_DictMap2, 0, "DictMap2", NULL, NULL, NULL, (f_hashCode)NULL, (f_compareTo)NULL); 
	KNH_TSTRUCT(ctx, STRUCT_DictSet2, 0, "DictSet2", NULL, NULL, NULL, (f_hashCode)NULL, (f_compareTo)NULL); 
	KNH_TSTRUCT_DictMap(ctx, STRUCT_DictMap, sizeof(knh_DictMap_struct),
		"DictMap",
		knh_DictMap_struct_init,
		knh_DictMap_struct_copy, 
//		knh_DictMap_struct_compare, 
		knh_DictMap_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_DictSet(ctx, STRUCT_DictSet, sizeof(knh_DictSet_struct),
		"DictSet",
		knh_DictSet_struct_init,
		knh_DictSet_struct_copy, 
//		knh_DictSet_struct_compare, 
		knh_DictSet_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_HashMap(ctx, STRUCT_HashMap, sizeof(knh_HashMap_struct),
		"HashMap",
		knh_HashMap_struct_init,
		knh_HashMap_struct_copy, 
//		knh_HashMap_struct_compare, 
		knh_HashMap_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_HashSet(ctx, STRUCT_HashSet, sizeof(knh_HashSet_struct),
		"HashSet",
		knh_HashSet_struct_init,
		knh_HashSet_struct_copy, 
//		knh_HashSet_struct_compare, 
		knh_HashSet_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_LRUHashMap(ctx, STRUCT_LRUHashMap, sizeof(knh_LRUHashMap_struct),
		"LRUHashMap",
		knh_LRUHashMap_struct_init,
		knh_LRUHashMap_struct_copy, 
//		knh_LRUHashMap_struct_compare, 
		knh_LRUHashMap_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_DictIdx(ctx, STRUCT_DictIdx, sizeof(knh_DictIdx_struct),
		"DictIdx",
		knh_DictIdx_struct_init,
		knh_DictIdx_struct_copy, 
//		knh_DictIdx_struct_compare, 
		knh_DictIdx_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT(ctx, STRUCT_Class, 0, "Class", NULL, NULL, NULL, (f_hashCode)knh_Class_hashCode, (f_compareTo)knh_Class_compareTo); 
	KNH_TSTRUCT_ClassStruct(ctx, STRUCT_ClassStruct, sizeof(knh_ClassStruct_struct),
		"ClassStruct",
		knh_ClassStruct_struct_init,
		knh_ClassStruct_struct_copy, 
//		knh_ClassStruct_struct_compare, 
		knh_ClassStruct_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_MethodField(ctx, STRUCT_MethodField, sizeof(knh_MethodField_struct),
		"MethodField",
		knh_MethodField_struct_init,
		knh_MethodField_struct_copy, 
//		knh_MethodField_struct_compare, 
		knh_MethodField_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_Method(ctx, STRUCT_Method, sizeof(knh_Method_struct),
		"Method",
		knh_Method_struct_init,
		knh_Method_struct_copy, 
//		knh_Method_struct_compare, 
		knh_Method_struct_traverse,
		knh_Method_hashCode,
		knh_Method_compareTo);
	KNH_TSTRUCT_Mapper(ctx, STRUCT_Mapper, sizeof(knh_Mapper_struct),
		"Mapper",
		knh_Mapper_struct_init,
		knh_Mapper_struct_copy, 
//		knh_Mapper_struct_compare, 
		knh_Mapper_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_ClassMap(ctx, STRUCT_ClassMap, sizeof(knh_ClassMap_struct),
		"ClassMap",
		knh_ClassMap_struct_init,
		knh_ClassMap_struct_copy, 
//		knh_ClassMap_struct_compare, 
		knh_ClassMap_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_AffineConv(ctx, STRUCT_AffineConv, sizeof(knh_AffineConv_struct),
		"AffineConv",
		knh_AffineConv_struct_init,
		knh_AffineConv_struct_copy, 
//		knh_AffineConv_struct_compare, 
		knh_AffineConv_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_IntUnit(ctx, STRUCT_IntUnit, sizeof(knh_IntUnit_struct),
		"IntUnit",
		knh_IntUnit_struct_init,
		knh_IntUnit_struct_copy, 
//		knh_IntUnit_struct_compare, 
		knh_IntUnit_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_FloatUnit(ctx, STRUCT_FloatUnit, sizeof(knh_FloatUnit_struct),
		"FloatUnit",
		knh_FloatUnit_struct_init,
		knh_FloatUnit_struct_copy, 
//		knh_FloatUnit_struct_compare, 
		knh_FloatUnit_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT(ctx, STRUCT_Regex, 0, "Regex", NULL, NULL, NULL, (f_hashCode)NULL, (f_compareTo)NULL); 
	KNH_TSTRUCT_BytesConv(ctx, STRUCT_BytesConv, sizeof(knh_BytesConv_struct),
		"BytesConv",
		knh_BytesConv_struct_init,
		knh_BytesConv_struct_copy, 
//		knh_BytesConv_struct_compare, 
		knh_BytesConv_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_StringUnit(ctx, STRUCT_StringUnit, sizeof(knh_StringUnit_struct),
		"StringUnit",
		knh_StringUnit_struct_init,
		knh_StringUnit_struct_copy, 
//		knh_StringUnit_struct_compare, 
		knh_StringUnit_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_InputStream(ctx, STRUCT_InputStream, sizeof(knh_InputStream_struct),
		"InputStream",
		knh_InputStream_struct_init,
		knh_InputStream_struct_copy, 
//		knh_InputStream_struct_compare, 
		knh_InputStream_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_OutputStream(ctx, STRUCT_OutputStream, sizeof(knh_OutputStream_struct),
		"OutputStream",
		knh_OutputStream_struct_init,
		knh_OutputStream_struct_copy, 
//		knh_OutputStream_struct_compare, 
		knh_OutputStream_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_Connection(ctx, STRUCT_Connection, sizeof(knh_Connection_struct),
		"Connection",
		knh_Connection_struct_init,
		knh_Connection_struct_copy, 
//		knh_Connection_struct_compare, 
		knh_Connection_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_ResultSet(ctx, STRUCT_ResultSet, sizeof(knh_ResultSet_struct),
		"ResultSet",
		knh_ResultSet_struct_init,
		knh_ResultSet_struct_copy, 
//		knh_ResultSet_struct_compare, 
		knh_ResultSet_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_Exception(ctx, STRUCT_Exception, sizeof(knh_Exception_struct),
		"Exception",
		knh_Exception_struct_init,
		knh_Exception_struct_copy, 
//		knh_Exception_struct_compare, 
		knh_Exception_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_ExceptionHandler(ctx, STRUCT_ExceptionHandler, sizeof(knh_ExceptionHandler_struct),
		"ExceptionHandler",
		knh_ExceptionHandler_struct_init,
		knh_ExceptionHandler_struct_copy, 
//		knh_ExceptionHandler_struct_compare, 
		knh_ExceptionHandler_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT(ctx, STRUCT_Script, 0, "Script", NULL, NULL, NULL, (f_hashCode)NULL, (f_compareTo)NULL); 
	KNH_TSTRUCT_NameSpace(ctx, STRUCT_NameSpace, sizeof(knh_NameSpace_struct),
		"NameSpace",
		knh_NameSpace_struct_init,
		knh_NameSpace_struct_copy, 
//		knh_NameSpace_struct_compare, 
		knh_NameSpace_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_Runtime(ctx, STRUCT_Runtime, sizeof(knh_Runtime_struct),
		"Runtime",
		knh_Runtime_struct_init,
		knh_Runtime_struct_copy, 
//		knh_Runtime_struct_compare, 
		knh_Runtime_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT(ctx, STRUCT_Context, 0, "Context", NULL, NULL, NULL, (f_hashCode)NULL, (f_compareTo)NULL); 
	KNH_TSTRUCT_Token(ctx, STRUCT_Token, sizeof(knh_Token_struct),
		"Token",
		knh_Token_struct_init,
		knh_Token_struct_copy, 
//		knh_Token_struct_compare, 
		knh_Token_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_Stmt(ctx, STRUCT_Stmt, sizeof(knh_Stmt_struct),
		"Stmt",
		knh_Stmt_struct_init,
		knh_Stmt_struct_copy, 
//		knh_Stmt_struct_compare, 
		knh_Stmt_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_Compiler(ctx, STRUCT_Compiler, sizeof(knh_Compiler_struct),
		"Compiler",
		knh_Compiler_struct_init,
		knh_Compiler_struct_copy, 
//		knh_Compiler_struct_compare, 
		knh_Compiler_struct_traverse,
		NULL,
		NULL);
	KNH_TSTRUCT_KLRCode(ctx, STRUCT_KLRCode, sizeof(knh_KLRCode_struct),
		"KLRCode",
		knh_KLRCode_struct_init,
		knh_KLRCode_struct_copy, 
//		knh_KLRCode_struct_compare, 
		knh_KLRCode_struct_traverse,
		NULL,
		NULL);
	KNH_TCLASS__T(ctx, CFLAG_Object, "konoha.Object",
		CLASS_Object, STRUCT_Object, CLASS_Object,
		KNH_NULL, NULL, 32); 
	KNH_TCLASS__T(ctx, CFLAG_Any, "konoha.Any",
		CLASS_Any, STRUCT_Any, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_This, "konoha.This",
		CLASS_This, STRUCT_This, CLASS_Any,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_Any1, "konoha.Any1",
		CLASS_Any1, STRUCT_Any1, CLASS_Any,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_Any2, "konoha.Any2",
		CLASS_Any2, STRUCT_Any2, CLASS_Any,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_Nue, "konoha.Nue",
		CLASS_Nue, STRUCT_Nue, CLASS_Object,
		KNH_NULL, knh_Nue_fdefault, 2); 
	KNH_TCLASS__T(ctx, CFLAG_Boolean, "konoha.Boolean",
		CLASS_Boolean, STRUCT_Boolean, CLASS_Object,
		KNH_NULL, NULL, 1); 
	KNH_TCLASS__T(ctx, CFLAG_Number, "konoha.Number",
		CLASS_Number, STRUCT_Number, CLASS_Object,
		KNH_NULL, NULL, 14); 
	KNH_TCLASS__T(ctx, CFLAG_Int, "konoha.Int",
		CLASS_Int, STRUCT_Int, CLASS_Number,
		knh_Int_cspec(ctx), knh_Int_fdefault, 29); 
	KNH_TCLASS__T(ctx, CFLAG_IntX, "konoha.IntX",
		CLASS_IntX, STRUCT_IntX, CLASS_Number,
		KNH_NULL, knh_IntX_fdefault, 0); 
	KNH_TCLASS__T(ctx, CFLAG_Int64, "konoha.Int64",
		CLASS_Int64, STRUCT_Int64, CLASS_Number,
		KNH_NULL, NULL, 1); 
	KNH_TCLASS__T(ctx, CFLAG_Int64X, "konoha.Int64X",
		CLASS_Int64X, STRUCT_Int64X, CLASS_Number,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_Float, "konoha.Float",
		CLASS_Float, STRUCT_Float, CLASS_Number,
		knh_Float_cspec(ctx), knh_Float_fdefault, 23); 
	KNH_TCLASS__T(ctx, CFLAG_FloatX, "konoha.FloatX",
		CLASS_FloatX, STRUCT_FloatX, CLASS_Number,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_String, "konoha.String",
		CLASS_String, STRUCT_String, CLASS_Object,
		knh_String_cspec(ctx), knh_String_fdefault, 24); 
	KNH_TCLASS__T(ctx, CFLAG_StringX, "konoha.StringX",
		CLASS_StringX, STRUCT_StringX, CLASS_String,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_Bytes, "konoha.Bytes",
		CLASS_Bytes, STRUCT_Bytes, CLASS_Object,
		KNH_NULL, NULL, 7); 
	KNH_TCLASS__T(ctx, CFLAG_Tuple2, "konoha.Tuple2",
		CLASS_Tuple2, STRUCT_Tuple2, CLASS_Object,
		KNH_NULL, NULL, 4); 
	KNH_TCLASS_PARAM(ctx, CLASS_Tuple2, CLASS_Any, CLASS_Any);
	KNH_TCLASS__T(ctx, CFLAG_Range, "konoha.Range",
		CLASS_Range, STRUCT_Range, CLASS_Object,
		KNH_NULL, NULL, 3); 
	KNH_TCLASS__T(ctx, CFLAG_Array, "konoha.Array",
		CLASS_Array, STRUCT_Array, CLASS_Object,
		KNH_NULL, NULL, 17); 
	KNH_TCLASS_PARAM(ctx, CLASS_Array, CLASS_Any, CLASS_Nue);
	KNH_TCLASS__T(ctx, CFLAG_Iterator, "konoha.Iterator",
		CLASS_Iterator, STRUCT_Iterator, CLASS_Object,
		KNH_NULL, NULL, 1); 
	KNH_TCLASS_PARAM(ctx, CLASS_Iterator, CLASS_Any, CLASS_Nue);
	KNH_TCLASS__T(ctx, CFLAG_DictMap2, "konoha.DictMap2",
		CLASS_DictMap2, STRUCT_DictMap2, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_DictSet2, "konoha.DictSet2",
		CLASS_DictSet2, STRUCT_DictSet2, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_DictMap, "konoha.DictMap",
		CLASS_DictMap, STRUCT_DictMap, CLASS_Object,
		KNH_NULL, NULL, 7); 
	KNH_TCLASS__T(ctx, CFLAG_DictSet, "konoha.DictSet",
		CLASS_DictSet, STRUCT_DictSet, CLASS_Object,
		KNH_NULL, NULL, 7); 
	KNH_TCLASS__T(ctx, CFLAG_HashMap, "konoha.HashMap",
		CLASS_HashMap, STRUCT_HashMap, CLASS_Object,
		KNH_NULL, NULL, 9); 
	KNH_TCLASS_PARAM(ctx, CLASS_HashMap, CLASS_Any, CLASS_Any);
	KNH_TCLASS__T(ctx, CFLAG_HashSet, "konoha.HashSet",
		CLASS_HashSet, STRUCT_HashSet, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS_PARAM(ctx, CLASS_HashSet, CLASS_Any, CLASS_Nue);
	KNH_TCLASS__T(ctx, CFLAG_LRUHashMap, "konoha.LRUHashMap",
		CLASS_LRUHashMap, STRUCT_LRUHashMap, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_DictIdx, "konoha.DictIdx",
		CLASS_DictIdx, STRUCT_DictIdx, CLASS_Object,
		KNH_NULL, NULL, 8); 
	KNH_TCLASS__T(ctx, CFLAG_Class, "konoha.Class",
		CLASS_Class, STRUCT_Class, CLASS_Object,
		KNH_NULL, knh_Class_fdefault, 12); 
	KNH_TCLASS__T(ctx, CFLAG_ClassStruct, "konoha.ClassStruct",
		CLASS_ClassStruct, STRUCT_ClassStruct, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_MethodField, "konoha.MethodField",
		CLASS_MethodField, STRUCT_MethodField, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_Method, "konoha.Method",
		CLASS_Method, STRUCT_Method, CLASS_Object,
		KNH_NULL, NULL, 15); 
	KNH_TCLASS__T(ctx, CFLAG_Mapper, "konoha.Mapper",
		CLASS_Mapper, STRUCT_Mapper, CLASS_Object,
		KNH_NULL, NULL, 12); 
	KNH_TCLASS__T(ctx, CFLAG_ClassMap, "konoha.ClassMap",
		CLASS_ClassMap, STRUCT_ClassMap, CLASS_Object,
		KNH_NULL, NULL, 1); 
	KNH_TCLASS__T(ctx, CFLAG_AffineConv, "konoha.AffineConv",
		CLASS_AffineConv, STRUCT_AffineConv, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_IntUnit, "konoha.IntUnit",
		CLASS_IntUnit, STRUCT_IntUnit, CLASS_Object,
		KNH_NULL, NULL, 1); 
	KNH_TCLASS__T(ctx, CFLAG_FloatUnit, "konoha.FloatUnit",
		CLASS_FloatUnit, STRUCT_FloatUnit, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_Regex, "konoha.Regex",
		CLASS_Regex, STRUCT_Regex, CLASS_Object,
		KNH_NULL, NULL, 1); 
	KNH_TCLASS__T(ctx, CFLAG_BytesConv, "konoha.BytesConv",
		CLASS_BytesConv, STRUCT_BytesConv, CLASS_Object,
		KNH_NULL, NULL, 1); 
	KNH_TCLASS__T(ctx, CFLAG_StringUnit, "konoha.StringUnit",
		CLASS_StringUnit, STRUCT_StringUnit, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_InputStream, "konoha.InputStream",
		CLASS_InputStream, STRUCT_InputStream, CLASS_Object,
		KNH_NULL, NULL, 6); 
	KNH_TCLASS__T(ctx, CFLAG_OutputStream, "konoha.OutputStream",
		CLASS_OutputStream, STRUCT_OutputStream, CLASS_Object,
		KNH_NULL, NULL, 11); 
	KNH_TCLASS__T(ctx, CFLAG_Connection, "konoha.Connection",
		CLASS_Connection, STRUCT_Connection, CLASS_Object,
		KNH_NULL, NULL, 3); 
	KNH_TCLASS__T(ctx, CFLAG_ResultSet, "konoha.ResultSet",
		CLASS_ResultSet, STRUCT_ResultSet, CLASS_Object,
		KNH_NULL, NULL, 2); 
	KNH_TCLASS__T(ctx, CFLAG_Exception, "konoha.Exception",
		CLASS_Exception, STRUCT_Exception, CLASS_Object,
		KNH_NULL, NULL, 5); 
	KNH_TCLASS__T(ctx, CFLAG_ExceptionHandler, "konoha.ExceptionHandler",
		CLASS_ExceptionHandler, STRUCT_ExceptionHandler, CLASS_Object,
		KNH_NULL, knh_ExceptionHandler_fdefault, 0); 
	KNH_TCLASS__T(ctx, CFLAG_Script, "konoha.Script",
		CLASS_Script, STRUCT_Script, CLASS_Object,
		KNH_NULL, NULL, 6); 
	KNH_TCLASS__T(ctx, CFLAG_NameSpace, "konoha.NameSpace",
		CLASS_NameSpace, STRUCT_NameSpace, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_System, "konoha.System",
		CLASS_System, STRUCT_System, CLASS_Object,
		KNH_NULL, knh_System_fdefault, 9); 
	KNH_TCLASS__T(ctx, CFLAG_Runtime, "konoha.Runtime",
		CLASS_Runtime, STRUCT_Runtime, CLASS_Object,
		KNH_NULL, knh_Runtime_fdefault, 0); 
	KNH_TCLASS__T(ctx, CFLAG_Context, "konoha.Context",
		CLASS_Context, STRUCT_Context, CLASS_Object,
		KNH_NULL, knh_Context_fdefault, 14); 
	KNH_TCLASS__T(ctx, CFLAG_Token, "konoha.Token",
		CLASS_Token, STRUCT_Token, CLASS_Object,
		KNH_NULL, NULL, 2); 
	KNH_TCLASS__T(ctx, CFLAG_Stmt, "konoha.Stmt",
		CLASS_Stmt, STRUCT_Stmt, CLASS_Object,
		KNH_NULL, NULL, 2); 
	KNH_TCLASS__T(ctx, CFLAG_Compiler, "konoha.Compiler",
		CLASS_Compiler, STRUCT_Compiler, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_TCLASS__T(ctx, CFLAG_KLRCode, "konoha.KLRCode",
		CLASS_KLRCode, STRUCT_KLRCode, CLASS_Object,
		KNH_NULL, NULL, 0); 
	KNH_ACLASS(ctx, ACLASS_String, CLASS_String);
	KNH_ICLASS(ctx, ICLASS_String, CLASS_String);
	KNH_ICLASS(ctx, ICLASS_Any1, CLASS_Any1);
	KNH_ICLASS(ctx, ICLASS_This, CLASS_This);
#ifdef KONOHA_MONOLITHIC

	KNH_TSTATICLIB__T(ctx, "knhdemo_init", (void*)knhdemo_init);
	KNH_TSTATICLIB__T(ctx, "knhmath_init", (void*)knhmath_init);
#endif/*KONOHA_MONOLITHIC*/

	KNH_TFIELDN__T(ctx, FIELDN_, "");
	KNH_TFIELDN__T(ctx, FIELDN___fast, ":fast");
	KNH_TFIELDN__T(ctx, FIELDN_a, "a");
	KNH_TFIELDN__T(ctx, FIELDN_add, "add");
	KNH_TFIELDN__T(ctx, FIELDN_add__fast, "add:fast");
	KNH_TFIELDN__T(ctx, FIELDN_addHistory, "addHistory");
	KNH_TFIELDN__T(ctx, FIELDN_addr, "addr");
	KNH_TFIELDN__T(ctx, FIELDN_append, "append");
	KNH_TFIELDN__T(ctx, FIELDN_autoFlush, "autoFlush");
	KNH_TFIELDN__T(ctx, FIELDN_b, "b");
	KNH_TFIELDN__T(ctx, FIELDN_bits, "bits");
	KNH_TFIELDN__T(ctx, FIELDN_buf, "buf");
	KNH_TFIELDN__T(ctx, FIELDN_c, "c");
	KNH_TFIELDN__T(ctx, FIELDN_class, "class");
	KNH_TFIELDN__T(ctx, FIELDN_clear, "clear");
	KNH_TFIELDN__T(ctx, FIELDN_close, "close");
	KNH_TFIELDN__T(ctx, FIELDN_compareTo, "compareTo");
	KNH_TFIELDN__T(ctx, FIELDN_compiling, "compiling");
	KNH_TFIELDN__T(ctx, FIELDN_copy, "copy");
	KNH_TFIELDN__T(ctx, FIELDN_d, "d");
	KNH_TFIELDN__T(ctx, FIELDN_debug, "debug");
	KNH_TFIELDN__T(ctx, FIELDN_default, "default");
	KNH_TFIELDN__T(ctx, FIELDN_defined, "defined");
	KNH_TFIELDN__T(ctx, FIELDN_delim, "delim");
	KNH_TFIELDN__T(ctx, FIELDN_dump, "dump");
	KNH_TFIELDN__T(ctx, FIELDN_e, "e");
	KNH_TFIELDN__T(ctx, FIELDN_empty, "empty");
	KNH_TFIELDN__T(ctx, FIELDN_enc, "enc");
	KNH_TFIELDN__T(ctx, FIELDN_encoding, "encoding");
	KNH_TFIELDN__T(ctx, FIELDN_endsWith, "endsWith");
	KNH_TFIELDN__T(ctx, FIELDN_equals, "equals");
	KNH_TFIELDN__T(ctx, FIELDN_err, "err");
	KNH_TFIELDN__T(ctx, FIELDN_eval, "eval");
	KNH_TFIELDN__T(ctx, FIELDN_f, "f");
	KNH_TFIELDN__T(ctx, FIELDN_file, "file");
	KNH_TFIELDN__T(ctx, FIELDN_first, "first");
	KNH_TFIELDN__T(ctx, FIELDN_flush, "flush");
	KNH_TFIELDN__T(ctx, FIELDN_format, "format");
	KNH_TFIELDN__T(ctx, FIELDN_formatted, "formatted");
	KNH_TFIELDN__T(ctx, FIELDN_g, "g");
	KNH_TFIELDN__T(ctx, FIELDN_gCMarked, "gCMarked");
	KNH_TFIELDN__T(ctx, FIELDN_h, "h");
	KNH_TFIELDN__T(ctx, FIELDN_hasMetaData, "hasMetaData");
	KNH_TFIELDN__T(ctx, FIELDN_i, "i");
	KNH_TFIELDN__T(ctx, FIELDN_in, "in");
	KNH_TFIELDN__T(ctx, FIELDN_index, "index");
	KNH_TFIELDN__T(ctx, FIELDN_indexOf, "indexOf");
	KNH_TFIELDN__T(ctx, FIELDN_init, "init");
	KNH_TFIELDN__T(ctx, FIELDN_initialCapacity, "initialCapacity");
	KNH_TFIELDN__T(ctx, FIELDN_insert, "insert");
	KNH_TFIELDN__T(ctx, FIELDN_isAbstract, "isAbstract");
	KNH_TFIELDN__T(ctx, FIELDN_isAspect, "isAspect");
	KNH_TFIELDN__T(ctx, FIELDN_isAutoFlush, "isAutoFlush");
	KNH_TFIELDN__T(ctx, FIELDN_isClassFunc, "isClassFunc");
	KNH_TFIELDN__T(ctx, FIELDN_isCompiling, "isCompiling");
	KNH_TFIELDN__T(ctx, FIELDN_isDebug, "isDebug");
	KNH_TFIELDN__T(ctx, FIELDN_isDerived, "isDerived");
	KNH_TFIELDN__T(ctx, FIELDN_isFatal, "isFatal");
	KNH_TFIELDN__T(ctx, FIELDN_isFinal, "isFinal");
	KNH_TFIELDN__T(ctx, FIELDN_isFormatted, "isFormatted");
	KNH_TFIELDN__T(ctx, FIELDN_isGCMarked, "isGCMarked");
	KNH_TFIELDN__T(ctx, FIELDN_isGenerated, "isGenerated");
	KNH_TFIELDN__T(ctx, FIELDN_isImmutable, "isImmutable");
	KNH_TFIELDN__T(ctx, FIELDN_isInterface, "isInterface");
	KNH_TFIELDN__T(ctx, FIELDN_isLocal, "isLocal");
	KNH_TFIELDN__T(ctx, FIELDN_isLogging, "isLogging");
	KNH_TFIELDN__T(ctx, FIELDN_isLossLess, "isLossLess");
	KNH_TFIELDN__T(ctx, FIELDN_isMetaExtensible, "isMetaExtensible");
	KNH_TFIELDN__T(ctx, FIELDN_isModified, "isModified");
	KNH_TFIELDN__T(ctx, FIELDN_isNullBase, "isNullBase");
	KNH_TFIELDN__T(ctx, FIELDN_isPartial, "isPartial");
	KNH_TFIELDN__T(ctx, FIELDN_isPrivate, "isPrivate");
	KNH_TFIELDN__T(ctx, FIELDN_isPublic, "isPublic");
	KNH_TFIELDN__T(ctx, FIELDN_isRelease, "isRelease");
	KNH_TFIELDN__T(ctx, FIELDN_isSignificant, "isSignificant");
	KNH_TFIELDN__T(ctx, FIELDN_isStatement, "isStatement");
	KNH_TFIELDN__T(ctx, FIELDN_isStatic, "isStatic");
	KNH_TFIELDN__T(ctx, FIELDN_isSynchronized, "isSynchronized");
	KNH_TFIELDN__T(ctx, FIELDN_isSynonym, "isSynonym");
	KNH_TFIELDN__T(ctx, FIELDN_isTemporal, "isTemporal");
	KNH_TFIELDN__T(ctx, FIELDN_isTotal, "isTotal");
	KNH_TFIELDN__T(ctx, FIELDN_isUnsigned, "isUnsigned");
	KNH_TFIELDN__T(ctx, FIELDN_isVarArgs, "isVarArgs");
	KNH_TFIELDN__T(ctx, FIELDN_isVerbose, "isVerbose");
	KNH_TFIELDN__T(ctx, FIELDN_isVerbose2, "isVerbose2");
	KNH_TFIELDN__T(ctx, FIELDN_isVirtual, "isVirtual");
	KNH_TFIELDN__T(ctx, FIELDN_j, "j");
	KNH_TFIELDN__T(ctx, FIELDN_k, "k");
	KNH_TFIELDN__T(ctx, FIELDN_key, "key");
	KNH_TFIELDN__T(ctx, FIELDN_l, "l");
	KNH_TFIELDN__T(ctx, FIELDN_lambda, "lambda");
	KNH_TFIELDN__T(ctx, FIELDN_len, "len");
	KNH_TFIELDN__T(ctx, FIELDN_linenum, "linenum");
	KNH_TFIELDN__T(ctx, FIELDN_m, "m");
	KNH_TFIELDN__T(ctx, FIELDN_main, "main");
	KNH_TFIELDN__T(ctx, FIELDN_man, "man");
	KNH_TFIELDN__T(ctx, FIELDN_mode, "mode");
	KNH_TFIELDN__T(ctx, FIELDN_modified, "modified");
	KNH_TFIELDN__T(ctx, FIELDN_n, "n");
	KNH_TFIELDN__T(ctx, FIELDN_name, "name");
	KNH_TFIELDN__T(ctx, FIELDN_new, "new");
	KNH_TFIELDN__T(ctx, FIELDN_new__array, "new:array");
	KNH_TFIELDN__T(ctx, FIELDN_new__init, "new:init");
	KNH_TFIELDN__T(ctx, FIELDN_new__offset, "new:offset");
	KNH_TFIELDN__T(ctx, FIELDN_new__slice, "new:slice");
	KNH_TFIELDN__T(ctx, FIELDN_next, "next");
	KNH_TFIELDN__T(ctx, FIELDN_o, "o");
	KNH_TFIELDN__T(ctx, FIELDN_offset, "offset");
	KNH_TFIELDN__T(ctx, FIELDN_opAdd, "opAdd");
	KNH_TFIELDN__T(ctx, FIELDN_opAdd__2, "opAdd:2");
	KNH_TFIELDN__T(ctx, FIELDN_opDiv, "opDiv");
	KNH_TFIELDN__T(ctx, FIELDN_opDiv__2, "opDiv:2");
	KNH_TFIELDN__T(ctx, FIELDN_opEq, "opEq");
	KNH_TFIELDN__T(ctx, FIELDN_opGt, "opGt");
	KNH_TFIELDN__T(ctx, FIELDN_opGte, "opGte");
	KNH_TFIELDN__T(ctx, FIELDN_opIn, "opIn");
	KNH_TFIELDN__T(ctx, FIELDN_opInstanceof, "opInstanceof");
	KNH_TFIELDN__T(ctx, FIELDN_opIs, "opIs");
	KNH_TFIELDN__T(ctx, FIELDN_opIsa, "opIsa");
	KNH_TFIELDN__T(ctx, FIELDN_opItr, "opItr");
	KNH_TFIELDN__T(ctx, FIELDN_opLShift, "opLShift");
	KNH_TFIELDN__T(ctx, FIELDN_opLogicalAnd, "opLogicalAnd");
	KNH_TFIELDN__T(ctx, FIELDN_opLogicalNot, "opLogicalNot");
	KNH_TFIELDN__T(ctx, FIELDN_opLogicalOr, "opLogicalOr");
	KNH_TFIELDN__T(ctx, FIELDN_opLogicalXor, "opLogicalXor");
	KNH_TFIELDN__T(ctx, FIELDN_opLt, "opLt");
	KNH_TFIELDN__T(ctx, FIELDN_opLte, "opLte");
	KNH_TFIELDN__T(ctx, FIELDN_opMod, "opMod");
	KNH_TFIELDN__T(ctx, FIELDN_opMul, "opMul");
	KNH_TFIELDN__T(ctx, FIELDN_opMul__2, "opMul:2");
	KNH_TFIELDN__T(ctx, FIELDN_opNeg, "opNeg");
	KNH_TFIELDN__T(ctx, FIELDN_opNeq, "opNeq");
	KNH_TFIELDN__T(ctx, FIELDN_opNext, "opNext");
	KNH_TFIELDN__T(ctx, FIELDN_opNot, "opNot");
	KNH_TFIELDN__T(ctx, FIELDN_opOffset, "opOffset");
	KNH_TFIELDN__T(ctx, FIELDN_opPrev, "opPrev");
	KNH_TFIELDN__T(ctx, FIELDN_opRShift, "opRShift");
	KNH_TFIELDN__T(ctx, FIELDN_opSlice, "opSlice");
	KNH_TFIELDN__T(ctx, FIELDN_opSub, "opSub");
	KNH_TFIELDN__T(ctx, FIELDN_opSub__2, "opSub:2");
	KNH_TFIELDN__T(ctx, FIELDN_opSubset, "opSubset");
	KNH_TFIELDN__T(ctx, FIELDN_opTo, "opTo");
	KNH_TFIELDN__T(ctx, FIELDN_out, "out");
	KNH_TFIELDN__T(ctx, FIELDN_p, "p");
	KNH_TFIELDN__T(ctx, FIELDN_pop, "pop");
	KNH_TFIELDN__T(ctx, FIELDN_print, "print");
	KNH_TFIELDN__T(ctx, FIELDN_println, "println");
	KNH_TFIELDN__T(ctx, FIELDN_prompt, "prompt");
	KNH_TFIELDN__T(ctx, FIELDN_property, "property");
	KNH_TFIELDN__T(ctx, FIELDN_q, "q");
	KNH_TFIELDN__T(ctx, FIELDN_query, "query");
	KNH_TFIELDN__T(ctx, FIELDN_r, "r");
	KNH_TFIELDN__T(ctx, FIELDN_random, "random");
	KNH_TFIELDN__T(ctx, FIELDN_readLine, "readLine");
	KNH_TFIELDN__T(ctx, FIELDN_readline, "readline");
	KNH_TFIELDN__T(ctx, FIELDN_refc, "refc");
	KNH_TFIELDN__T(ctx, FIELDN_release, "release");
	KNH_TFIELDN__T(ctx, FIELDN_remove, "remove");
	KNH_TFIELDN__T(ctx, FIELDN_replace, "replace");
	KNH_TFIELDN__T(ctx, FIELDN_s, "s");
	KNH_TFIELDN__T(ctx, FIELDN_script, "script");
	KNH_TFIELDN__T(ctx, FIELDN_second, "second");
	KNH_TFIELDN__T(ctx, FIELDN_size, "size");
	KNH_TFIELDN__T(ctx, FIELDN_split, "split");
	KNH_TFIELDN__T(ctx, FIELDN_startsWith, "startsWith");
	KNH_TFIELDN__T(ctx, FIELDN_t, "t");
	KNH_TFIELDN__T(ctx, FIELDN_term, "term");
	KNH_TFIELDN__T(ctx, FIELDN_this, "this");
	KNH_TFIELDN__T(ctx, FIELDN_times, "times");
	KNH_TFIELDN__T(ctx, FIELDN_toLower, "toLower");
	KNH_TFIELDN__T(ctx, FIELDN_toUpper, "toUpper");
	KNH_TFIELDN__T(ctx, FIELDN_trim, "trim");
	KNH_TFIELDN__T(ctx, FIELDN_typeof, "typeof");
	KNH_TFIELDN__T(ctx, FIELDN_u, "u");
	KNH_TFIELDN__T(ctx, FIELDN_uRN, "uRN");
	KNH_TFIELDN__T(ctx, FIELDN_urn, "urn");
	KNH_TFIELDN__T(ctx, FIELDN_v, "v");
	KNH_TFIELDN__T(ctx, FIELDN_value, "value");
	KNH_TFIELDN__T(ctx, FIELDN_vargs, "vargs");
	KNH_TFIELDN__T(ctx, FIELDN_verbose, "verbose");
	KNH_TFIELDN__T(ctx, FIELDN_verbose2, "verbose2");
	KNH_TFIELDN__T(ctx, FIELDN_w, "w");
	KNH_TFIELDN__T(ctx, FIELDN_write, "write");
	KNH_TFIELDN__T(ctx, FIELDN_x, "x");
	KNH_TFIELDN__T(ctx, FIELDN_y, "y");
	KNH_TFIELDN__T(ctx, FIELDN_z, "z");
/* ------------------------------------------------------------------------ */

	knh_tMethodField_add(ctx, new_MethodField__1(ctx, KNH_FLAG_MF_VARARGS, TYPE_Any, TYPE_Any, FIELDN_o)); //MFN_Any_Any_
	knh_tMethodField_add(ctx, new_MethodField__2(ctx, 0, TYPE_void, TYPE_OutputStream, FIELDN_w, TYPE_Any, FIELDN_o)); //MFN_void_OutputStream_Any
	knh_tMethodField_add(ctx, new_MethodField__0(ctx, 0, TYPE_Any)); //MFN_Any
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_This, TYPE_Int, FIELDN_i)); //MFN_nThis_Int
	knh_tMethodField_add(ctx, new_MethodField__2(NULL, 0, NNTYPE_This, TYPE_Int, FIELDN_i, TYPE_Any1, FIELDN_v)); //MFN_nThis_Int_Any1
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, KNH_FLAG_MF_VARARGS, NNTYPE_This, TYPE_Any1, FIELDN_v)); //MFN_nThis_Any1_
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_void, TYPE_Any1, FIELDN_v)); //MFN_void_Any1
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, KNH_FLAG_MF_VARARGS, TYPE_void, TYPE_Any1, FIELDN_v)); //MFN_void_Any1_
	knh_tMethodField_add(ctx, new_MethodField__0(NULL, 0, NNTYPE_Int)); //MFN_nInt
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_Any1, NNTYPE_Int, FIELDN_i)); //MFN_Any1_nInt
	knh_tMethodField_add(ctx, new_MethodField__2(NULL, 0, TYPE_void, NNTYPE_Int, FIELDN_i, TYPE_Any1, FIELDN_v)); //MFN_void_nInt_Any1
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_void, NNTYPE_Int, FIELDN_n)); //MFN_void_nInt
	knh_tMethodField_add(ctx, new_MethodField__0(NULL, 0, TYPE_Any1)); //MFN_Any1
	knh_tMethodField_add(ctx, new_MethodField__0(NULL, 0, TYPE_void)); //MFN_void
	knh_tMethodField_add(ctx, new_MethodField__2(NULL, 0, NNTYPE_This, TYPE_Int, FIELDN_s, TYPE_Int, FIELDN_e)); //MFN_nThis_Int_Int
	knh_tMethodField_add(ctx, new_MethodField__0(NULL, 0, ITYPE_Any1)); //MFN_iAny1
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_Bytes, TYPE_Int, FIELDN_i)); //MFN_nBytes_Int
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, KNH_FLAG_MF_VARARGS, TYPE_void, NNTYPE_Int, FIELDN_v)); //MFN_void_nInt_
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_Int, NNTYPE_Int, FIELDN_i)); //MFN_nInt_nInt
	knh_tMethodField_add(ctx, new_MethodField__2(NULL, 0, TYPE_void, NNTYPE_Int, FIELDN_i, NNTYPE_Int, FIELDN_v)); //MFN_void_nInt_nInt
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_Connection, NNTYPE_String, FIELDN_u)); //MFN_nConnection_nString
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_ResultSet, NNTYPE_String, FIELDN_q)); //MFN_ResultSet_nString
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_Any, NNTYPE_String, FIELDN_k)); //MFN_Any_nString
	knh_tMethodField_add(ctx, new_MethodField__2(NULL, 0, TYPE_void, NNTYPE_String, FIELDN_k, TYPE_Any, FIELDN_v)); //MFN_void_nString_Any
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_void, TYPE_String, FIELDN_e)); //MFN_void_String
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_Int, NNTYPE_String, FIELDN_t)); //MFN_nInt_nString
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_String, NNTYPE_Int, FIELDN_i)); //MFN_String_nInt
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_DictMap, TYPE_Int, FIELDN_i)); //MFN_nDictMap_Int
	knh_tMethodField_add(ctx, new_MethodField__2(NULL, 0, TYPE_void, NNTYPE_String, FIELDN_k, NNTYPE_Any, FIELDN_v)); //MFN_void_nString_nAny
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_void, NNTYPE_String, FIELDN_k)); //MFN_void_nString
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_DictSet, TYPE_Int, FIELDN_i)); //MFN_nDictSet_Int
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_Boolean, TYPE_Any, FIELDN_v)); //MFN_Boolean_Any
	knh_tMethodField_add(ctx, new_MethodField__2(NULL, 0, TYPE_void, NNTYPE_String, FIELDN_k, NNTYPE_Int, FIELDN_v)); //MFN_void_nString_nInt
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_Float, NNTYPE_Float, FIELDN_v)); //MFN_nFloat_nFloat
	knh_tMethodField_add(ctx, new_MethodField__0(NULL, 0, NNTYPE_Float)); //MFN_nFloat
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, KNH_FLAG_MF_VARARGS, NNTYPE_Float, NNTYPE_Float, FIELDN_v)); //MFN_nFloat_nFloat_
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_Boolean, NNTYPE_Float, FIELDN_v)); //MFN_nBoolean_nFloat
	knh_tMethodField_add(ctx, new_MethodField__0(NULL, 0, TYPE_Float)); //MFN_Float
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_void, NNTYPE_Any1, FIELDN_k)); //MFN_void_nAny1
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_Boolean, NNTYPE_Any1, FIELDN_k)); //MFN_nBoolean_nAny1
	knh_tMethodField_add(ctx, new_MethodField__2(NULL, 0, TYPE_void, NNTYPE_Any1, FIELDN_k, TYPE_Any2, FIELDN_v)); //MFN_void_nAny1_Any2
	knh_tMethodField_add(ctx, new_MethodField__0(NULL, 0, TYPE_String)); //MFN_String
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_InputStream, NNTYPE_String, FIELDN_u)); //MFN_InputStream_nString
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, KNH_FLAG_MF_VARARGS, NNTYPE_Int, NNTYPE_Int, FIELDN_v)); //MFN_nInt_nInt_
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_Boolean, NNTYPE_Int, FIELDN_v)); //MFN_nBoolean_nInt
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_Int, TYPE_Int, FIELDN_n)); //MFN_nInt_Int
	knh_tMethodField_add(ctx, new_MethodField__0(NULL, 0, TYPE_Boolean)); //MFN_Boolean
	knh_tMethodField_add(ctx, new_MethodField__0(NULL, 0, NNTYPE_String)); //MFN_nString
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_Float, NNTYPE_Number, FIELDN_v)); //MFN_nFloat_nNumber
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, KNH_FLAG_MF_VARARGS, NNTYPE_Float, NNTYPE_Number, FIELDN_v)); //MFN_nFloat_nNumber_
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_Boolean, NNTYPE_Number, FIELDN_v)); //MFN_nBoolean_nNumber
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, KNH_FLAG_MF_VARARGS, NNTYPE_This, TYPE_Any, FIELDN_v)); //MFN_nThis_Any_
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_Int, TYPE_Any, FIELDN_o)); //MFN_nInt_Any
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_Boolean, TYPE_Any, FIELDN_v)); //MFN_nBoolean_Any
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_Boolean, NNTYPE_Class, FIELDN_c)); //MFN_nBoolean_nClass
	knh_tMethodField_add(ctx, new_MethodField__0(NULL, 0, TYPE_Class)); //MFN_Class
	knh_tMethodField_add(ctx, new_MethodField__0(NULL, 0, ITYPE_This)); //MFN_iThis
	knh_tMethodField_add(ctx, new_MethodField__2(NULL, 0, TYPE_OutputStream, NNTYPE_String, FIELDN_u, TYPE_String, FIELDN_m)); //MFN_OutputStream_nString_String
	knh_tMethodField_add(ctx, new_MethodField__3(NULL, 0, TYPE_void, NNTYPE_Bytes, FIELDN_b, TYPE_Int, FIELDN_o, TYPE_Int, FIELDN_l)); //MFN_void_nBytes_Int_Int
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_void, TYPE_Any, FIELDN_v)); //MFN_void_Any
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, KNH_FLAG_MF_VARARGS, TYPE_void, TYPE_Any, FIELDN_v)); //MFN_void_Any_
	knh_tMethodField_add(ctx, new_MethodField__2(NULL, 0, NNTYPE_Range, TYPE_Any1, FIELDN_s, TYPE_Any1, FIELDN_e)); //MFN_nRange_Any1_Any1
	knh_tMethodField_add(ctx, new_MethodField__2(NULL, 0, NNTYPE_Range, TYPE_Any1, FIELDN_s, TYPE_Int, FIELDN_o)); //MFN_nRange_Any1_Int
	knh_tMethodField_add(ctx, new_MethodField__0(NULL, 0, TYPE_ResultSet)); //MFN_ResultSet
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_Boolean, NNTYPE_String, FIELDN_s)); //MFN_nBoolean_nString
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_String, TYPE_Any, FIELDN_v)); //MFN_nString_Any
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, KNH_FLAG_MF_VARARGS, NNTYPE_String, TYPE_Any, FIELDN_v)); //MFN_nString_Any_
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_String, NNTYPE_String, FIELDN_t)); //MFN_nString_nString
	knh_tMethodField_add(ctx, new_MethodField__2(NULL, 0, NNTYPE_String, NNTYPE_String, FIELDN_o, NNTYPE_String, FIELDN_n)); //MFN_nString_nString_nString
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_String, NNTYPE_Int, FIELDN_n)); //MFN_nString_nInt
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, NNTYPE_String, TYPE_String, FIELDN_v)); //MFN_nString_String
	knh_tMethodField_add(ctx, new_MethodField__2(NULL, 0, NNTYPE_String, TYPE_Int, FIELDN_o, TYPE_Int, FIELDN_l)); //MFN_nString_Int_Int
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, ATYPE_String, TYPE_String, FIELDN_d)); //MFN_aString_String
	knh_tMethodField_add(ctx, new_MethodField__0(NULL, 0, NNTYPE_InputStream)); //MFN_nInputStream
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_void, TYPE_InputStream, FIELDN_i)); //MFN_void_InputStream
	knh_tMethodField_add(ctx, new_MethodField__0(NULL, 0, NNTYPE_OutputStream)); //MFN_nOutputStream
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_void, TYPE_OutputStream, FIELDN_o)); //MFN_void_OutputStream
	knh_tMethodField_add(ctx, new_MethodField__2(NULL, 0, NNTYPE_Tuple2, TYPE_Any1, FIELDN_f, TYPE_Any2, FIELDN_s)); //MFN_nTuple2_Any1_Any2
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_Any, NNTYPE_Int, FIELDN_i)); //MFN_Any_nInt
	knh_tMethodField_add(ctx, new_MethodField__3(NULL, 0, TYPE_void, TYPE_String, FIELDN_s, TYPE_String, FIELDN_f, TYPE_Int, FIELDN_l)); //MFN_void_String_String_Int
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_String, TYPE_String, FIELDN_p)); //MFN_String_String
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_Boolean, NNTYPE_Class, FIELDN_c)); //MFN_Boolean_nClass
	knh_tMethodField_add(ctx, new_MethodField__0(NULL, 0, NNTYPE_Boolean)); //MFN_nBoolean
	knh_tMethodField_add(ctx, new_MethodField__1(NULL, 0, TYPE_void, TYPE_Boolean, FIELDN_b)); //MFN_void_Boolean
	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_new, (void*)NULL, /*delta*/0, 
		CLASS_Array, METHODN_new,
		MF_nThis_Int
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_new__array, (void*)NULL, /*delta*/0, 
		CLASS_Array, METHODN_new__array,
		MF_nThis_Int_Any1
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS, 
		knh__Array_new__init, (void*)NULL, /*delta*/0, 
		CLASS_Array, METHODN_new__init,
		MF_nThis_Any1_
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_add, (void*)NULL, /*delta*/0, 
		CLASS_Array, METHODN_add,
		MF_void_Any1
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS, 
		knh__Array_opLShift, (void*)NULL, /*delta*/0, 
		CLASS_Array, METHODN_opLShift,
		MF_void_Any1_
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_getSize, (void*)NULL, /*delta*/0, 
		CLASS_Array, METHODN_getSize,
		MF_nInt
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_get, (void*)NULL, /*delta*/0, 
		CLASS_Array, METHODN_get,
		MF_Any1_nInt
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_set, (void*)NULL, /*delta*/0, 
		CLASS_Array, METHODN_set,
		MF_void_nInt_Any1
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_remove, (void*)NULL, /*delta*/0, 
		CLASS_Array, METHODN_remove,
		MF_void_nInt
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_pop, (void*)NULL, /*delta*/0, 
		CLASS_Array, METHODN_pop,
		MF_Any1
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_insert, (void*)NULL, /*delta*/0, 
		CLASS_Array, METHODN_insert,
		MF_void_nInt_Any1
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_clear, (void*)NULL, /*delta*/0, 
		CLASS_Array, METHODN_clear,
		MF_void
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_set__opSubset, (void*)NULL, /*delta*/0, 
		CLASS_Array, METHODN_opSubset,
		MF_nThis_Int_Int
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_set__opSlice, (void*)NULL, /*delta*/0, 
		CLASS_Array, METHODN_opSlice,
		MF_nThis_Int_Int
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_set__opOffset, (void*)NULL, /*delta*/0, 
		CLASS_Array, METHODN_opOffset,
		MF_nThis_Int_Int
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Array__k, /*delta*/0, 
		CLASS_Array, METHODN__k,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Array_opItr, (void*)NULL, /*delta*/0, 
		CLASS_Array, METHODN_opItr,
		MF_iAny1
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Boolean__s, /*delta*/0, 
		CLASS_Boolean, METHODN__s,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Bytes_new, (void*)NULL, /*delta*/0, 
		CLASS_Bytes, METHODN_new,
		MF_nBytes_Int
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Bytes_add, (void*)NULL, /*delta*/0, 
		CLASS_Bytes, METHODN_add,
		MF_void_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS, 
		knh__Bytes_opLShift, (void*)NULL, /*delta*/0, 
		CLASS_Bytes, METHODN_opLShift,
		MF_void_nInt_
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Bytes_getSize, (void*)NULL, /*delta*/0, 
		CLASS_Bytes, METHODN_getSize,
		MF_nInt
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Bytes_get, (void*)NULL, /*delta*/0, 
		CLASS_Bytes, METHODN_get,
		MF_nInt_nInt
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Bytes_set, (void*)NULL, /*delta*/0, 
		CLASS_Bytes, METHODN_set,
		MF_void_nInt_nInt
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Bytes__dump, /*delta*/0, 
		CLASS_Bytes, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_BytesConv__k, /*delta*/0, 
		CLASS_BytesConv, METHODN__k,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Class__s, /*delta*/0, 
		CLASS_Class, METHODN__s,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Class__k, /*delta*/0, 
		CLASS_Class, METHODN__k,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Class__dump, /*delta*/0, 
		CLASS_Class, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Class__man, /*delta*/0, 
		CLASS_Class, METHODN__man,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_ClassMap__dump, /*delta*/0, 
		CLASS_ClassMap, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Connection_close, (void*)NULL, /*delta*/0, 
		CLASS_Connection, METHODN_close,
		MF_void
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Connection_new, (void*)NULL, /*delta*/0, 
		CLASS_Connection, METHODN_new,
		MF_nConnection_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Connection_query, (void*)NULL, /*delta*/0, 
		CLASS_Connection, METHODN_query,
		MF_ResultSet_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Context_getProperty, (void*)NULL, /*delta*/0, 
		CLASS_Context, METHODN_getProperty,
		MF_Any_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Context_setProperty, (void*)NULL, /*delta*/0, 
		CLASS_Context, METHODN_setProperty,
		MF_void_nString_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Context_setEncoding, (void*)NULL, /*delta*/0, 
		CLASS_Context, METHODN_setEncoding,
		MF_void_String
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Context__dump, /*delta*/0, 
		CLASS_Context, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictIdx_size, (void*)NULL, /*delta*/0, 
		CLASS_DictIdx, METHODN_size,
		MF_nInt
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictIdx_index, (void*)NULL, /*delta*/0, 
		CLASS_DictIdx, METHODN_index,
		MF_nInt_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictIdx_add__fast, (void*)NULL, /*delta*/0, 
		CLASS_DictIdx, METHODN_add__fast,
		MF_nInt_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictIdx_add, (void*)NULL, /*delta*/0, 
		CLASS_DictIdx, METHODN_add,
		MF_nInt_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictIdx_get__fast, (void*)NULL, /*delta*/0, 
		CLASS_DictIdx, METHODN_get__fast,
		MF_String_nInt
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictIdx_get, (void*)NULL, /*delta*/0, 
		CLASS_DictIdx, METHODN_get,
		MF_String_nInt
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictIdx_clear, (void*)NULL, /*delta*/0, 
		CLASS_DictIdx, METHODN_clear,
		MF_void
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_DictIdx__k, /*delta*/0, 
		CLASS_DictIdx, METHODN__k,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictMap_new, (void*)NULL, /*delta*/0, 
		CLASS_DictMap, METHODN_new,
		MF_nDictMap_Int
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictMap_get, (void*)NULL, /*delta*/0, 
		CLASS_DictMap, METHODN_get,
		MF_Any_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictMap_append, (void*)NULL, /*delta*/0, 
		CLASS_DictMap, METHODN_append,
		MF_void_nString_nAny
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictMap_set, (void*)NULL, /*delta*/0, 
		CLASS_DictMap, METHODN_set,
		MF_void_nString_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictMap_remove, (void*)NULL, /*delta*/0, 
		CLASS_DictMap, METHODN_remove,
		MF_void_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictMap_clear, (void*)NULL, /*delta*/0, 
		CLASS_DictMap, METHODN_clear,
		MF_void
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_DictMap__dump, /*delta*/0, 
		CLASS_DictMap, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictSet_new, (void*)NULL, /*delta*/0, 
		CLASS_DictSet, METHODN_new,
		MF_nDictSet_Int
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictSet_get, (void*)NULL, /*delta*/0, 
		CLASS_DictSet, METHODN_get,
		MF_nInt_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictSet_opIn, (void*)NULL, /*delta*/0, 
		CLASS_DictSet, METHODN_opIn,
		MF_Boolean_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictSet_set, (void*)NULL, /*delta*/0, 
		CLASS_DictSet, METHODN_set,
		MF_void_nString_nInt
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictSet_add, (void*)NULL, /*delta*/0, 
		CLASS_DictSet, METHODN_add,
		MF_void_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__DictSet_clear, (void*)NULL, /*delta*/0, 
		CLASS_DictSet, METHODN_clear,
		MF_void
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_DictSet__dump, /*delta*/0, 
		CLASS_DictSet, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Exception__s, /*delta*/0, 
		CLASS_Exception, METHODN__s,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Exception__dump, /*delta*/0, 
		CLASS_Exception, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Float_opAdd__2, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opAdd__2,
		MF_nFloat_nFloat
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Float_opNg, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opNeg,
		MF_nFloat
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Float_opSub__2, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opSub__2,
		MF_nFloat_nFloat
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Float_opMul__2, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opMul__2,
		MF_nFloat_nFloat
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Float_opDiv__2, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opDiv__2,
		MF_nFloat_nFloat
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS|KNH_FLAG_MF_STATIC, 
		knh__Float_opAdd, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opAdd,
		MF_nFloat_nFloat_
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS|KNH_FLAG_MF_STATIC, 
		knh__Float_opSub, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opSub,
		MF_nFloat_nFloat_
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS|KNH_FLAG_MF_STATIC, 
		knh__Float_opMul, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opMul,
		MF_nFloat_nFloat_
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS|KNH_FLAG_MF_STATIC, 
		knh__Float_opDiv, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opDiv,
		MF_nFloat_nFloat_
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Float_opMod, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opMod,
		MF_nFloat_nFloat
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Float_opEq, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opEq,
		MF_nBoolean_nFloat
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Float_opNeq, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opNeq,
		MF_nBoolean_nFloat
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Float_opLt, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opLt,
		MF_nBoolean_nFloat
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Float_opLte, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opLte,
		MF_nBoolean_nFloat
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Float_opGt, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opGt,
		MF_nBoolean_nFloat
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Float_opGte, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opGte,
		MF_nBoolean_nFloat
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Float_opNext, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opNext,
		MF_nFloat
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Float_opPrev, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_opPrev,
		MF_nFloat
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Float_random, (void*)NULL, /*delta*/0, 
		CLASS_Float, METHODN_random,
		MF_Float
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Float__s, /*delta*/0, 
		CLASS_Float, METHODN__s,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Float__k, /*delta*/0, 
		CLASS_Float, METHODN__k,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Float__bits, /*delta*/0, 
		CLASS_Float, METHODN__bits,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Float__dump, /*delta*/0, 
		CLASS_Float, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashMap_clear, (void*)NULL, /*delta*/0, 
		CLASS_HashMap, METHODN_clear,
		MF_void
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashMap_new, (void*)NULL, /*delta*/0, 
		CLASS_HashMap, METHODN_new,
		MF_nThis_Int
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashMap_get, (void*)NULL, /*delta*/0, 
		CLASS_HashMap, METHODN_get,
		MF_void_nAny1
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashMap_opIn, (void*)NULL, /*delta*/0, 
		CLASS_HashMap, METHODN_opIn,
		MF_nBoolean_nAny1
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashMap_remove, (void*)NULL, /*delta*/0, 
		CLASS_HashMap, METHODN_remove,
		MF_void_nAny1
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashMap_set, (void*)NULL, /*delta*/0, 
		CLASS_HashMap, METHODN_set,
		MF_void_nAny1_Any2
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_HashMap__k, /*delta*/0, 
		CLASS_HashMap, METHODN__k,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_HashMap__dump, /*delta*/0, 
		CLASS_HashMap, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__HashMap_opItr, (void*)NULL, /*delta*/0, 
		CLASS_HashMap, METHODN_opItr,
		MF_iAny1
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__InputStream_readLine, (void*)NULL, /*delta*/0, 
		CLASS_InputStream, METHODN_readLine,
		MF_String
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__InputStream_close, (void*)NULL, /*delta*/0, 
		CLASS_InputStream, METHODN_close,
		MF_void
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__InputStream_new, (void*)NULL, /*delta*/0, 
		CLASS_InputStream, METHODN_new,
		MF_InputStream_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__InputStream_setEncoding, (void*)NULL, /*delta*/0, 
		CLASS_InputStream, METHODN_setEncoding,
		MF_void_String
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_InputStream__dump, /*delta*/0, 
		CLASS_InputStream, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_InputStream__k, /*delta*/0, 
		CLASS_InputStream, METHODN__k,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Int64__dump, /*delta*/0, 
		CLASS_Int64, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opAdd__2, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opAdd__2,
		MF_nInt_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opNg, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opNeg,
		MF_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opSub__2, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opSub__2,
		MF_nInt_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opMul__2, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opMul__2,
		MF_nInt_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opDiv__2, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opDiv__2,
		MF_nInt_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS|KNH_FLAG_MF_STATIC, 
		knh__Int_opAdd, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opAdd,
		MF_nInt_nInt_
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS|KNH_FLAG_MF_STATIC, 
		knh__Int_opSub, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opSub,
		MF_nInt_nInt_
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS|KNH_FLAG_MF_STATIC, 
		knh__Int_opMul, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opMul,
		MF_nInt_nInt_
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS|KNH_FLAG_MF_STATIC, 
		knh__Int_opDiv, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opDiv,
		MF_nInt_nInt_
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opMod, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opMod,
		MF_nInt_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opEq, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opEq,
		MF_nBoolean_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opNeq, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opNeq,
		MF_nBoolean_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opLt, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opLt,
		MF_nBoolean_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opLte, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opLte,
		MF_nBoolean_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opGt, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opGt,
		MF_nBoolean_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opGte, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opGte,
		MF_nBoolean_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opLogicalAnd, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opLogicalAnd,
		MF_nInt_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opLogicalOr, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opLogicalOr,
		MF_nInt_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opLogicalXor, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opLogicalXor,
		MF_nInt_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opLogicalNot, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opLogicalNot,
		MF_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opLShift, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opLShift,
		MF_nInt_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opRShift, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opRShift,
		MF_nInt_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opNext, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opNext,
		MF_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Int_opPrev, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_opPrev,
		MF_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_NULLBASE|KNH_FLAG_MF_STATIC, 
		knh__Int_getSize, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_getSize,
		MF_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_CLASSFUNC, 
		knh__Int_random, (void*)NULL, /*delta*/0, 
		CLASS_Int, METHODN_random,
		MF_nInt_Int
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Int__s, /*delta*/0, 
		CLASS_Int, METHODN__s,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Int__x, /*delta*/0, 
		CLASS_Int, METHODN__x,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Int__bits, /*delta*/0, 
		CLASS_Int, METHODN__bits,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Iterator__dump, /*delta*/0, 
		CLASS_Iterator, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Mapper__k, /*delta*/0, 
		CLASS_Mapper, METHODN__k,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isAbstract, (void*)NULL, /*delta*/0, 
		CLASS_Method, METHODN_isAbstract,
		MF_Boolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_getName, (void*)NULL, /*delta*/0, 
		CLASS_Method, METHODN_getName,
		MF_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_getURN, (void*)NULL, /*delta*/0, 
		CLASS_Method, METHODN_getURN,
		MF_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Method__s, /*delta*/0, 
		CLASS_Method, METHODN__s,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Method__k, /*delta*/0, 
		CLASS_Method, METHODN__k,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Method__dump, /*delta*/0, 
		CLASS_Method, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Nue__s, /*delta*/0, 
		CLASS_Nue, METHODN__s,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Nue__k, /*delta*/0, 
		CLASS_Nue, METHODN__k,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Number_opAdd__2, (void*)NULL, /*delta*/0, 
		CLASS_Number, METHODN_opAdd__2,
		MF_nFloat_nNumber
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Number_opSub__2, (void*)NULL, /*delta*/0, 
		CLASS_Number, METHODN_opSub__2,
		MF_nFloat_nNumber
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Number_opMul__2, (void*)NULL, /*delta*/0, 
		CLASS_Number, METHODN_opMul__2,
		MF_nFloat_nNumber
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Number_opDiv__2, (void*)NULL, /*delta*/0, 
		CLASS_Number, METHODN_opDiv__2,
		MF_nFloat_nNumber
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS|KNH_FLAG_MF_STATIC, 
		knh__Number_opAdd, (void*)NULL, /*delta*/0, 
		CLASS_Number, METHODN_opAdd,
		MF_nFloat_nNumber_
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS|KNH_FLAG_MF_STATIC, 
		knh__Number_opSub, (void*)NULL, /*delta*/0, 
		CLASS_Number, METHODN_opSub,
		MF_nFloat_nNumber_
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS|KNH_FLAG_MF_STATIC, 
		knh__Number_opMul, (void*)NULL, /*delta*/0, 
		CLASS_Number, METHODN_opMul,
		MF_nFloat_nNumber_
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS|KNH_FLAG_MF_STATIC, 
		knh__Number_opDiv, (void*)NULL, /*delta*/0, 
		CLASS_Number, METHODN_opDiv,
		MF_nFloat_nNumber_
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Number_opEq, (void*)NULL, /*delta*/0, 
		CLASS_Number, METHODN_opEq,
		MF_nBoolean_nNumber
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Number_opNeq, (void*)NULL, /*delta*/0, 
		CLASS_Number, METHODN_opNeq,
		MF_nBoolean_nNumber
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Number_opLt, (void*)NULL, /*delta*/0, 
		CLASS_Number, METHODN_opLt,
		MF_nBoolean_nNumber
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Number_opLte, (void*)NULL, /*delta*/0, 
		CLASS_Number, METHODN_opLte,
		MF_nBoolean_nNumber
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Number_opGt, (void*)NULL, /*delta*/0, 
		CLASS_Number, METHODN_opGt,
		MF_nBoolean_nNumber
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Number_opGte, (void*)NULL, /*delta*/0, 
		CLASS_Number, METHODN_opGte,
		MF_nBoolean_nNumber
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS, 
		knh__Object_new__init, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_new__init,
		MF_nThis_Any_
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_compareTo, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_compareTo,
		MF_nInt_Any
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Object_opEq, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_opEq,
		MF_Boolean_Any
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Object_opNeq, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_opNeq,
		MF_Boolean_Any
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Object_opLt, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_opLt,
		MF_Boolean_Any
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Object_opLte, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_opLte,
		MF_Boolean_Any
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Object_opGt, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_opGt,
		MF_Boolean_Any
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Object_opGte, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_opGte,
		MF_Boolean_Any
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Object_opNot, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_opNot,
		MF_Boolean
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Object_opIs, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_opIs,
		MF_nBoolean_Any
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Object_opIsa, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_opIsa,
		MF_nBoolean_nClass
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Object_opTo, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_opTo,
		MF_nBoolean_nClass
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Object_getClass, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_getClass,
		MF_Class
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_opItr, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_opItr,
		MF_iThis
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Object__s, /*delta*/0, 
		CLASS_Object, METHODN__s,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Object__k, /*delta*/0, 
		CLASS_Object, METHODN__k,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Object__dump, /*delta*/0, 
		CLASS_Object, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Object__empty, /*delta*/0, 
		CLASS_Object, METHODN__empty,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Object__refc, /*delta*/0, 
		CLASS_Object, METHODN__refc,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Object__addr, /*delta*/0, 
		CLASS_Object, METHODN__addr,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__OutputStream_flush, (void*)NULL, /*delta*/0, 
		CLASS_OutputStream, METHODN_flush,
		MF_void
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__OutputStream_close, (void*)NULL, /*delta*/0, 
		CLASS_OutputStream, METHODN_close,
		MF_void
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__OutputStream_new, (void*)NULL, /*delta*/0, 
		CLASS_OutputStream, METHODN_new,
		MF_OutputStream_nString_String
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__OutputStream_write, (void*)NULL, /*delta*/0, 
		CLASS_OutputStream, METHODN_write,
		MF_void_nBytes_Int_Int
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__OutputStream_setEncoding, (void*)NULL, /*delta*/0, 
		CLASS_OutputStream, METHODN_setEncoding,
		MF_void_String
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__OutputStream_print, (void*)NULL, /*delta*/0, 
		CLASS_OutputStream, METHODN_print,
		MF_void_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__OutputStream_println, (void*)NULL, /*delta*/0, 
		CLASS_OutputStream, METHODN_println,
		MF_void_Any
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS, 
		knh__OutputStream_opLShift, (void*)NULL, /*delta*/0, 
		CLASS_OutputStream, METHODN_opLShift,
		MF_void_Any_
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_OutputStream__k, /*delta*/0, 
		CLASS_OutputStream, METHODN__k,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Range_new, (void*)NULL, /*delta*/0, 
		CLASS_Range, METHODN_new,
		MF_nRange_Any1_Any1
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Range_new__slice, (void*)NULL, /*delta*/0, 
		CLASS_Range, METHODN_new__slice,
		MF_nRange_Any1_Any1
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Range_new__offset, (void*)NULL, /*delta*/0, 
		CLASS_Range, METHODN_new__offset,
		MF_nRange_Any1_Int
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Regex__s, /*delta*/0, 
		CLASS_Regex, METHODN__s,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__ResultSet_next, (void*)NULL, /*delta*/0, 
		CLASS_ResultSet, METHODN_next,
		MF_ResultSet
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_ResultSet__dump, /*delta*/0, 
		CLASS_ResultSet, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Script__k, /*delta*/0, 
		CLASS_Script, METHODN__k,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Script__dump, /*delta*/0, 
		CLASS_Script, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__String_equals, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_equals,
		MF_nBoolean_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__String_startsWith, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_startsWith,
		MF_nBoolean_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__String_endsWith, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_endsWith,
		MF_nBoolean_nString
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__String_indexOf, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_indexOf,
		MF_nInt_nString
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC|KNH_FLAG_MF_NULLBASE, 
		knh__String_getSize, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_getSize,
		MF_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC|KNH_FLAG_MF_NULLBASE, 
		knh__String_opAdd__2, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_opAdd__2,
		MF_nString_Any
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS|KNH_FLAG_MF_STATIC|KNH_FLAG_MF_NULLBASE, 
		knh__String_opAdd, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_opAdd,
		MF_nString_Any_
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__String_opSub__2, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_opSub__2,
		MF_nString_nString
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__String_replace, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_replace,
		MF_nString_nString_nString
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__String_times, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_times,
		MF_nString_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_VARARGS|KNH_FLAG_MF_STATIC, 
		knh__String_opMul, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_opMul,
		MF_nString_Any_
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__String_opMul__2, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_opMul__2,
		MF_nString_Any
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC|KNH_FLAG_MF_NULLBASE, 
		knh__String_opDiv__2, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_opDiv__2,
		MF_nString_String
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC|KNH_FLAG_MF_NULLBASE, 
		knh__String_opDiv, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_opDiv,
		MF_nString_String
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC|KNH_FLAG_MF_NULLBASE, 
		knh__String_opMod, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_opMod,
		MF_nString_String
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__String_opIn, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_opIn,
		MF_nBoolean_nString
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__String_get, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_get,
		MF_nString_nInt
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__String_opOffset, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_opOffset,
		MF_nString_Int_Int
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__String_toLower, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_toLower,
		MF_nString
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__String_toUpper, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_toUpper,
		MF_nString
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__String_trim, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_trim,
		MF_nString
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__String_split, (void*)NULL, /*delta*/0, 
		CLASS_String, METHODN_split,
		MF_aString_String
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_String__s, /*delta*/0, 
		CLASS_String, METHODN__s,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_String__k, /*delta*/0, 
		CLASS_String, METHODN__k,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__System_getProperty, (void*)NULL, /*delta*/0, 
		CLASS_System, METHODN_getProperty,
		MF_Any_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__System_setProperty, (void*)NULL, /*delta*/0, 
		CLASS_System, METHODN_setProperty,
		MF_void_nString_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__System_getIn, (void*)NULL, /*delta*/0, 
		CLASS_System, METHODN_getIn,
		MF_nInputStream
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__System_setIn, (void*)NULL, /*delta*/0, 
		CLASS_System, METHODN_setIn,
		MF_void_InputStream
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__System_getOut, (void*)NULL, /*delta*/0, 
		CLASS_System, METHODN_getOut,
		MF_nOutputStream
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__System_setOut, (void*)NULL, /*delta*/0, 
		CLASS_System, METHODN_setOut,
		MF_void_OutputStream
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__System_getErr, (void*)NULL, /*delta*/0, 
		CLASS_System, METHODN_getErr,
		MF_nOutputStream
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__System_setErr, (void*)NULL, /*delta*/0, 
		CLASS_System, METHODN_setErr,
		MF_void_OutputStream
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_System__k, /*delta*/0, 
		CLASS_System, METHODN__k,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		KNH_FLAG_MF_STATIC, 
		knh__Tuple_new, (void*)NULL, /*delta*/0, 
		CLASS_Tuple2, METHODN_new,
		MF_nTuple2_Any1_Any2
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Tuple2_getSize, (void*)NULL, /*delta*/0, 
		CLASS_Tuple2, METHODN_getSize,
		MF_nInt
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Tuple2_get__fast, (void*)NULL, /*delta*/0, 
		CLASS_Tuple2, METHODN_get__fast,
		MF_Any_nInt
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Tuple2__dump, /*delta*/0, 
		CLASS_Tuple2, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Stmt__s, /*delta*/0, 
		CLASS_Stmt, METHODN__s,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Stmt__dump, /*delta*/0, 
		CLASS_Stmt, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Token__s, /*delta*/0, 
		CLASS_Token, METHODN__s,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh_fmethod_movableText, (void*)knh_Token__dump, /*delta*/0, 
		CLASS_Token, METHODN__dump,
		MF_void_OutputStream_Any
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Script_eval, (void*)NULL, /*delta*/0, 
		CLASS_Script, METHODN_eval,
		MF_void_String_String_Int
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Script_isStatement, (void*)NULL, /*delta*/0, 
		CLASS_Script, METHODN_isStatement,
		MF_nBoolean_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Script_readline, (void*)NULL, /*delta*/0, 
		CLASS_Script, METHODN_readline,
		MF_String_String
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Script_addHistory, (void*)NULL, /*delta*/0, 
		CLASS_Script, METHODN_addHistory,
		MF_void_nString
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_opInstanceof, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_opInstanceof,
		MF_Boolean_nClass
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_isRelease, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_isRelease,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_isDebug, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_isDebug,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_isImmutable, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_isImmutable,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_hasMetaData, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_hasMetaData,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_isSynchronized, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_isSynchronized,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_isModified, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_isModified,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_setModified, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_setModified,
		MF_void_Boolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_isGCMarked, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_isGCMarked,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_setGCMarked, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_setGCMarked,
		MF_void_Boolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_isFormatted, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_isFormatted,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Object_setFormatted, (void*)NULL, /*delta*/0, 
		CLASS_Object, METHODN_setFormatted,
		MF_void_Boolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isRelease, (void*)NULL, /*delta*/0, 
		CLASS_Class, METHODN_isRelease,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isDebug, (void*)NULL, /*delta*/0, 
		CLASS_Class, METHODN_isDebug,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isImmutable, (void*)NULL, /*delta*/0, 
		CLASS_Class, METHODN_isImmutable,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isMetaExtensible, (void*)NULL, /*delta*/0, 
		CLASS_Class, METHODN_isMetaExtensible,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isPrivate, (void*)NULL, /*delta*/0, 
		CLASS_Class, METHODN_isPrivate,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isPublic, (void*)NULL, /*delta*/0, 
		CLASS_Class, METHODN_isPublic,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isFinal, (void*)NULL, /*delta*/0, 
		CLASS_Class, METHODN_isFinal,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Class_isInterface, (void*)NULL, /*delta*/0, 
		CLASS_Class, METHODN_isInterface,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isPrivate, (void*)NULL, /*delta*/0, 
		CLASS_Method, METHODN_isPrivate,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isPublic, (void*)NULL, /*delta*/0, 
		CLASS_Method, METHODN_isPublic,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isVirtual, (void*)NULL, /*delta*/0, 
		CLASS_Method, METHODN_isVirtual,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isFinal, (void*)NULL, /*delta*/0, 
		CLASS_Method, METHODN_isFinal,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isStatic, (void*)NULL, /*delta*/0, 
		CLASS_Method, METHODN_isStatic,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isClassFunc, (void*)NULL, /*delta*/0, 
		CLASS_Method, METHODN_isClassFunc,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isNullBase, (void*)NULL, /*delta*/0, 
		CLASS_Method, METHODN_isNullBase,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isVarArgs, (void*)NULL, /*delta*/0, 
		CLASS_Method, METHODN_isVarArgs,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Method_isAspect, (void*)NULL, /*delta*/0, 
		CLASS_Method, METHODN_isAspect,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Mapper_isInterface, (void*)NULL, /*delta*/0, 
		CLASS_Mapper, METHODN_isInterface,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Mapper_isSignificant, (void*)NULL, /*delta*/0, 
		CLASS_Mapper, METHODN_isSignificant,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Mapper_isFinal, (void*)NULL, /*delta*/0, 
		CLASS_Mapper, METHODN_isFinal,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Mapper_isSynonym, (void*)NULL, /*delta*/0, 
		CLASS_Mapper, METHODN_isSynonym,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Mapper_isLossLess, (void*)NULL, /*delta*/0, 
		CLASS_Mapper, METHODN_isLossLess,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Mapper_isTotal, (void*)NULL, /*delta*/0, 
		CLASS_Mapper, METHODN_isTotal,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Mapper_isPartial, (void*)NULL, /*delta*/0, 
		CLASS_Mapper, METHODN_isPartial,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Mapper_isStatic, (void*)NULL, /*delta*/0, 
		CLASS_Mapper, METHODN_isStatic,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Mapper_isTemporal, (void*)NULL, /*delta*/0, 
		CLASS_Mapper, METHODN_isTemporal,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Mapper_isLocal, (void*)NULL, /*delta*/0, 
		CLASS_Mapper, METHODN_isLocal,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Mapper_isDerived, (void*)NULL, /*delta*/0, 
		CLASS_Mapper, METHODN_isDerived,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__IntUnit_isUnsigned, (void*)NULL, /*delta*/0, 
		CLASS_IntUnit, METHODN_isUnsigned,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__OutputStream_isAutoFlush, (void*)NULL, /*delta*/0, 
		CLASS_OutputStream, METHODN_isAutoFlush,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__OutputStream_setAutoFlush, (void*)NULL, /*delta*/0, 
		CLASS_OutputStream, METHODN_setAutoFlush,
		MF_void_Boolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Exception_isFatal, (void*)NULL, /*delta*/0, 
		CLASS_Exception, METHODN_isFatal,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Exception_isLogging, (void*)NULL, /*delta*/0, 
		CLASS_Exception, METHODN_isLogging,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Exception_isGenerated, (void*)NULL, /*delta*/0, 
		CLASS_Exception, METHODN_isGenerated,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Context_isRelease, (void*)NULL, /*delta*/0, 
		CLASS_Context, METHODN_isRelease,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Context_isDebug, (void*)NULL, /*delta*/0, 
		CLASS_Context, METHODN_isDebug,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Context_setRelease, (void*)NULL, /*delta*/0, 
		CLASS_Context, METHODN_setRelease,
		MF_void_Boolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Context_setDebug, (void*)NULL, /*delta*/0, 
		CLASS_Context, METHODN_setDebug,
		MF_void_Boolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Context_isCompiling, (void*)NULL, /*delta*/0, 
		CLASS_Context, METHODN_isCompiling,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Context_setCompiling, (void*)NULL, /*delta*/0, 
		CLASS_Context, METHODN_setCompiling,
		MF_void_Boolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Context_isVerbose, (void*)NULL, /*delta*/0, 
		CLASS_Context, METHODN_isVerbose,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Context_setVerbose, (void*)NULL, /*delta*/0, 
		CLASS_Context, METHODN_setVerbose,
		MF_void_Boolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Context_isVerbose2, (void*)NULL, /*delta*/0, 
		CLASS_Context, METHODN_isVerbose2,
		MF_nBoolean
	);

	KNH_TMETHOD(ctx, 
		0, 
		knh__Context_setVerbose2, (void*)NULL, /*delta*/0, 
		CLASS_Context, METHODN_setVerbose2,
		MF_void_Boolean
	);

	KNH_TMAPPER_Array_Iterator(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_Array, CLASS_Iterator,  
		knh_Array_Iterator, KNH_NULL
	);

	KNH_TMAPPER_Iterator_Array(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_Iterator, CLASS_Array,  
		knh_Iterator_Array, KNH_NULL
	);

	KNH_TMAPPER_Boolean_String(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_Boolean, CLASS_String,  
		knh_Boolean_String, KNH_NULL
	);

	KNH_TMAPPER_Bytes_String(ctx, 
		0, 
		CLASS_Bytes, CLASS_String,  
		knh_Bytes_String, KNH_NULL
	);

	KNH_TMAPPER_String_Bytes(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_String, CLASS_Bytes,  
		knh_String_Bytes, KNH_NULL
	);

	KNH_TMAPPER_DictMap_Iterator(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_DictMap, CLASS_Iterator,  
		knh_DictMap_Iterator, KNH_NULL
	);

	KNH_TMAPPER_DictSet_Iterator(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_DictSet, CLASS_Iterator,  
		knh_DictSet_Iterator, KNH_NULL
	);

	KNH_TMAPPER_String_Float(ctx, 
		0, 
		CLASS_String, CLASS_Float,  
		knh_String_Float, KNH_NULL
	);

	KNH_TMAPPER_Float_String(ctx, 
		KNH_FLAG_MMF_STATIC|KNH_FLAG_MMF_FINAL|KNH_FLAG_MMF_TOTAL, 
		CLASS_Float, CLASS_String,  
		knh_Float_String, KNH_NULL
	);

	KNH_TMAPPER_Int_Float(ctx, 
		KNH_FLAG_MMF_STATIC|KNH_FLAG_MMF_FINAL|KNH_FLAG_MMF_TOTAL, 
		CLASS_Int, CLASS_Float,  
		knh_Int_Float, KNH_NULL
	);

	KNH_TMAPPER_Float_Int(ctx, 
		KNH_FLAG_MMF_STATIC|KNH_FLAG_MMF_FINAL|KNH_FLAG_MMF_TOTAL, 
		CLASS_Float, CLASS_Int,  
		knh_Float_Int, KNH_NULL
	);

	KNH_TMAPPER_HashMap_Iterator(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_HashMap, CLASS_Iterator,  
		knh_HashMap_Iterator, KNH_NULL
	);

	KNH_TMAPPER_InputStream_String(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_InputStream, ICLASS_String,  
		knh_InputStream_String__, KNH_NULL
	);

	KNH_TMAPPER_String_Int(ctx, 
		KNH_FLAG_MMF_STATIC|KNH_FLAG_MMF_FINAL, 
		CLASS_String, CLASS_Int,  
		knh_String_Int, KNH_NULL
	);

	KNH_TMAPPER_Int_String(ctx, 
		KNH_FLAG_MMF_STATIC|KNH_FLAG_MMF_FINAL|KNH_FLAG_MMF_TOTAL, 
		CLASS_Int, CLASS_String,  
		knh_Int_String, KNH_NULL
	);

	KNH_TMAPPER_Object_String(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_Object, CLASS_String,  
		knh_Object_String, KNH_NULL
	);

	KNH_TMAPPER_Object_Iterator(ctx, 
		KNH_FLAG_MMF_TOTAL, 
		CLASS_Object, CLASS_Iterator,  
		knh_Object_Iterator, KNH_NULL
	);

	init_InputStream(ctx);
	init_OutputStream(ctx);
	init_Regex(ctx);
}

#ifdef __cplusplus
}
#endif
