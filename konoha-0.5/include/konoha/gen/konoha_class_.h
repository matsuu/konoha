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

#ifndef KONOHA_CLASS__H
#define KONOHA_CLASS__H

#include<konoha/konoha_t.h>
#include<konoha/konoha_class.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */
#define KONOHA_BUILDID                  587

/* ======================================================================== */

/* ======================================================================== */
/* [FLAG] */

/* ------------------------------------------------------------------------ */
/* Object */
#define KNH_FLAG_OF_RELEASE             KNH_FLAG_T0

#define knh_Object_isRelease(o)  \
	(((o)->h.flag & KNH_FLAG_OF_RELEASE) == KNH_FLAG_OF_RELEASE)

#define knh_Object_isDebug(o)   \
	(((o)->h.flag & KNH_FLAG_OF_RELEASE) != KNH_FLAG_OF_RELEASE)
#define KNH_FLAG_OF_IMMUTABLE           KNH_FLAG_T1

#define knh_Object_isImmutable(o)  \
	(((o)->h.flag & KNH_FLAG_OF_IMMUTABLE) == KNH_FLAG_OF_IMMUTABLE)
#define KNH_FLAG_OF_CYCLIC              KNH_FLAG_T2

#define knh_Object_isCyclic(o)  \
	(((o)->h.flag & KNH_FLAG_OF_CYCLIC) == KNH_FLAG_OF_CYCLIC)

#define knh_Object_setCyclic(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_OF_CYCLIC; else (o)->h.flag &= ~(KNH_FLAG_OF_CYCLIC);

#define KNH_FLAG_OF_UNDEFINED           KNH_FLAG_T3

#define knh_Object_isUndefined(o)  \
	(((o)->h.flag & KNH_FLAG_OF_UNDEFINED) == KNH_FLAG_OF_UNDEFINED)
#define KNH_FLAG_OF_MODIFIED            KNH_FLAG_T4

#define knh_Object_isModified(o)  \
	(((o)->h.flag & KNH_FLAG_OF_MODIFIED) == KNH_FLAG_OF_MODIFIED)

#define knh_Object_setModified(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_OF_MODIFIED; else (o)->h.flag &= ~(KNH_FLAG_OF_MODIFIED);

#define KNH_FLAG_OF_FORMATTED           KNH_FLAG_T5

#define knh_Object_isFormatted(o)  \
	(((o)->h.flag & KNH_FLAG_OF_FORMATTED) == KNH_FLAG_OF_FORMATTED)

#define knh_Object_setFormatted(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_OF_FORMATTED; else (o)->h.flag &= ~(KNH_FLAG_OF_FORMATTED);

#define KNH_FLAG_OF_SHARED              KNH_FLAG_T6

#define knh_Object_isShared(o)  \
	(((o)->h.flag & KNH_FLAG_OF_SHARED) == KNH_FLAG_OF_SHARED)

#define knh_Object_setShared(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_OF_SHARED; else (o)->h.flag &= ~(KNH_FLAG_OF_SHARED);

#define KNH_FLAG_OF_LOCAL4              KNH_FLAG_T7

#define knh_Object_isLocal4(o)  \
	(((o)->h.flag & KNH_FLAG_OF_LOCAL4) == KNH_FLAG_OF_LOCAL4)

#define knh_Object_setLocal4(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_OF_LOCAL4; else (o)->h.flag &= ~(KNH_FLAG_OF_LOCAL4);

#define KNH_FLAG_OF_LOCAL3              KNH_FLAG_T8

#define knh_Object_isLocal3(o)  \
	(((o)->h.flag & KNH_FLAG_OF_LOCAL3) == KNH_FLAG_OF_LOCAL3)

#define knh_Object_setLocal3(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_OF_LOCAL3; else (o)->h.flag &= ~(KNH_FLAG_OF_LOCAL3);

#define KNH_FLAG_OF_LOCAL2              KNH_FLAG_T9

#define knh_Object_isLocal2(o)  \
	(((o)->h.flag & KNH_FLAG_OF_LOCAL2) == KNH_FLAG_OF_LOCAL2)

#define knh_Object_setLocal2(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_OF_LOCAL2; else (o)->h.flag &= ~(KNH_FLAG_OF_LOCAL2);

#define KNH_FLAG_OF_LOCAL1              KNH_FLAG_T10

#define knh_Object_isLocal1(o)  \
	(((o)->h.flag & KNH_FLAG_OF_LOCAL1) == KNH_FLAG_OF_LOCAL1)

#define knh_Object_setLocal1(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_OF_LOCAL1; else (o)->h.flag &= ~(KNH_FLAG_OF_LOCAL1);


/* ------------------------------------------------------------------------ */
/* Nue */
#define KNH_FLAG_NUE_GCHOOK             KNH_FLAG_OF_LOCAL1

#define knh_Nue_isGCHook(o)  \
	(((o)->h.flag & KNH_FLAG_NUE_GCHOOK) == KNH_FLAG_NUE_GCHOOK)

#define knh_Nue_setGCHook(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_NUE_GCHOOK; else (o)->h.flag &= ~(KNH_FLAG_NUE_GCHOOK);


/* ------------------------------------------------------------------------ */
/* String */
#define KNH_FLAG_STRING_TEXTSGM         KNH_FLAG_OF_LOCAL1

#define knh_String_isTextSgm(o)  \
	(((o)->h.flag & KNH_FLAG_STRING_TEXTSGM) == KNH_FLAG_STRING_TEXTSGM)

#define knh_String_setTextSgm(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_STRING_TEXTSGM; else (o)->h.flag &= ~(KNH_FLAG_STRING_TEXTSGM);

#define KNH_FLAG_STRING_ASCII           KNH_FLAG_OF_LOCAL2

#define knh_String_isASCII(o)  \
	(((o)->h.flag & KNH_FLAG_STRING_ASCII) == KNH_FLAG_STRING_ASCII)

#define knh_String_setASCII(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_STRING_ASCII; else (o)->h.flag &= ~(KNH_FLAG_STRING_ASCII);


/* ------------------------------------------------------------------------ */
/* Bytes */
#define KNH_FLAG_BYTES_STACKBUFFER      KNH_FLAG_OF_LOCAL1

#define knh_Bytes_isStackBuffer(o)  \
	(((o)->h.flag & KNH_FLAG_BYTES_STACKBUFFER) == KNH_FLAG_BYTES_STACKBUFFER)

#define knh_Bytes_setStackBuffer(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_BYTES_STACKBUFFER; else (o)->h.flag &= ~(KNH_FLAG_BYTES_STACKBUFFER);


/* ------------------------------------------------------------------------ */
/* Array */
#define KNH_FLAG_ARY_DIM                KNH_FLAG_OF_LOCAL1

#define knh_Array_isDim(o)  \
	(((o)->h.flag & KNH_FLAG_ARY_DIM) == KNH_FLAG_ARY_DIM)

#define knh_Array_setDim(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_ARY_DIM; else (o)->h.flag &= ~(KNH_FLAG_ARY_DIM);


/* ------------------------------------------------------------------------ */
/* IArray */
#define KNH_FLAG_ARY_DIM                KNH_FLAG_OF_LOCAL1

#define knh_IArray_isDim(o)  \
	(((o)->h.flag & KNH_FLAG_ARY_DIM) == KNH_FLAG_ARY_DIM)

#define knh_IArray_setDim(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_ARY_DIM; else (o)->h.flag &= ~(KNH_FLAG_ARY_DIM);


/* ------------------------------------------------------------------------ */
/* FArray */
#define KNH_FLAG_ARY_DIM                KNH_FLAG_OF_LOCAL1

#define knh_FArray_isDim(o)  \
	(((o)->h.flag & KNH_FLAG_ARY_DIM) == KNH_FLAG_ARY_DIM)

#define knh_FArray_setDim(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_ARY_DIM; else (o)->h.flag &= ~(KNH_FLAG_ARY_DIM);


/* ------------------------------------------------------------------------ */
/* DictMap */
#define KNH_FLAG_DICTM_IGNORECASE       KNH_FLAG_OF_LOCAL1

#define knh_DictMap_isIgnoreCase(o)  \
	(((o)->h.flag & KNH_FLAG_DICTM_IGNORECASE) == KNH_FLAG_DICTM_IGNORECASE)

#define knh_DictMap_setIgnoreCase(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_DICTM_IGNORECASE; else (o)->h.flag &= ~(KNH_FLAG_DICTM_IGNORECASE);


/* ------------------------------------------------------------------------ */
/* DictSet */
#define KNH_FLAG_DICTS_IGNORECASE       KNH_FLAG_OF_LOCAL1

#define knh_DictSet_isIgnoreCase(o)  \
	(((o)->h.flag & KNH_FLAG_DICTS_IGNORECASE) == KNH_FLAG_DICTS_IGNORECASE)

#define knh_DictSet_setIgnoreCase(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_DICTS_IGNORECASE; else (o)->h.flag &= ~(KNH_FLAG_DICTS_IGNORECASE);


/* ------------------------------------------------------------------------ */
/* Class */
#define KNH_FLAG_CF_RELEASE             KNH_FLAG_T0

#define knh_class_isRelease(o)  \
	((ctx->share->ClassTable[(o)].cflag & KNH_FLAG_CF_RELEASE) == KNH_FLAG_CF_RELEASE)

#define knh_class_isDebug(o)   \
	((ctx->share->ClassTable[(o)].cflag & KNH_FLAG_CF_RELEASE) != KNH_FLAG_CF_RELEASE)
#define KNH_FLAG_CF_IMMUTABLE           KNH_FLAG_T1

#define knh_class_isImmutable(o)  \
	((ctx->share->ClassTable[(o)].cflag & KNH_FLAG_CF_IMMUTABLE) == KNH_FLAG_CF_IMMUTABLE)
#define KNH_FLAG_CF_CYCLIC              KNH_FLAG_T2

#define knh_class_isCyclic(o)  \
	((ctx->share->ClassTable[(o)].cflag & KNH_FLAG_CF_CYCLIC) == KNH_FLAG_CF_CYCLIC)

#define knh_class_setCyclic(o,b)  \
	if(b) ctx->share->ClassTable[(o)].cflag |= KNH_FLAG_CF_CYCLIC; else ctx->share->ClassTable[(o)].cflag &= ~(KNH_FLAG_CF_CYCLIC);

#define KNH_FLAG_CF_METAEXTENSIBLE      KNH_FLAG_T3

#define knh_class_isMetaExtensible(o)  \
	((ctx->share->ClassTable[(o)].cflag & KNH_FLAG_CF_METAEXTENSIBLE) == KNH_FLAG_CF_METAEXTENSIBLE)
#define KNH_FLAG_CF_PRIVATE             KNH_FLAG_T4

#define knh_class_isPrivate(o)  \
	((ctx->share->ClassTable[(o)].cflag & KNH_FLAG_CF_PRIVATE) == KNH_FLAG_CF_PRIVATE)

#define knh_class_isPublic(o)   \
	((ctx->share->ClassTable[(o)].cflag & KNH_FLAG_CF_PRIVATE) != KNH_FLAG_CF_PRIVATE)
#define KNH_FLAG_CF_FINAL               KNH_FLAG_T5

#define knh_class_isFinal(o)  \
	((ctx->share->ClassTable[(o)].cflag & KNH_FLAG_CF_FINAL) == KNH_FLAG_CF_FINAL)
#define KNH_FLAG_CF_SINGLETON           KNH_FLAG_T6

#define knh_class_isSingleton(o)  \
	((ctx->share->ClassTable[(o)].cflag & KNH_FLAG_CF_SINGLETON) == KNH_FLAG_CF_SINGLETON)
#define KNH_FLAG_CF_NULLOBJECT          KNH_FLAG_T7

#define knh_class_isNullObject(o)  \
	((ctx->share->ClassTable[(o)].cflag & KNH_FLAG_CF_NULLOBJECT) == KNH_FLAG_CF_NULLOBJECT)
#define KNH_FLAG_CF_INTERFACE           KNH_FLAG_T8

#define knh_class_isInterface(o)  \
	((ctx->share->ClassTable[(o)].cflag & KNH_FLAG_CF_INTERFACE) == KNH_FLAG_CF_INTERFACE)

/* ------------------------------------------------------------------------ */
/* ClassStruct */
#define KNH_FLAG_CFF_HIDDEN             KNH_FLAG_T0

#define knh_ClassStruct_isHidden(o,n)  \
	((((ClassStruct)o)->fields[n].flag & KNH_FLAG_CFF_HIDDEN) == KNH_FLAG_CFF_HIDDEN)

#define knh_ClassStruct_setHidden(o,n,b)  \
	if(b) ((ClassStruct)o)->fields[n].flag |= KNH_FLAG_CFF_HIDDEN; else ((ClassStruct)o)->fields[n].flag &= ~(KNH_FLAG_CFF_HIDDEN);

#define KNH_FLAG_CFF_AUTONAME           KNH_FLAG_T1

#define knh_ClassStruct_isAutoName(o,n)  \
	((((ClassStruct)o)->fields[n].flag & KNH_FLAG_CFF_AUTONAME) == KNH_FLAG_CFF_AUTONAME)

#define knh_ClassStruct_setAutoName(o,n,b)  \
	if(b) ((ClassStruct)o)->fields[n].flag |= KNH_FLAG_CFF_AUTONAME; else ((ClassStruct)o)->fields[n].flag &= ~(KNH_FLAG_CFF_AUTONAME);

#define KNH_FLAG_CFF_NULLASSINGED       KNH_FLAG_T2

#define knh_ClassStruct_isNullAssinged(o,n)  \
	((((ClassStruct)o)->fields[n].flag & KNH_FLAG_CFF_NULLASSINGED) == KNH_FLAG_CFF_NULLASSINGED)

#define knh_ClassStruct_setNullAssinged(o,n,b)  \
	if(b) ((ClassStruct)o)->fields[n].flag |= KNH_FLAG_CFF_NULLASSINGED; else ((ClassStruct)o)->fields[n].flag &= ~(KNH_FLAG_CFF_NULLASSINGED);

#define KNH_FLAG_CFF_PROTECTED          KNH_FLAG_T3

#define knh_ClassStruct_isProtected(o,n)  \
	((((ClassStruct)o)->fields[n].flag & KNH_FLAG_CFF_PROTECTED) == KNH_FLAG_CFF_PROTECTED)

#define knh_ClassStruct_setProtected(o,n,b)  \
	if(b) ((ClassStruct)o)->fields[n].flag |= KNH_FLAG_CFF_PROTECTED; else ((ClassStruct)o)->fields[n].flag &= ~(KNH_FLAG_CFF_PROTECTED);

#define KNH_FLAG_CFF_GETTER             KNH_FLAG_T4

#define knh_ClassStruct_isGetter(o,n)  \
	((((ClassStruct)o)->fields[n].flag & KNH_FLAG_CFF_GETTER) == KNH_FLAG_CFF_GETTER)

#define knh_ClassStruct_setGetter(o,n,b)  \
	if(b) ((ClassStruct)o)->fields[n].flag |= KNH_FLAG_CFF_GETTER; else ((ClassStruct)o)->fields[n].flag &= ~(KNH_FLAG_CFF_GETTER);

#define KNH_FLAG_CFF_SETTER             KNH_FLAG_T5

#define knh_ClassStruct_isSetter(o,n)  \
	((((ClassStruct)o)->fields[n].flag & KNH_FLAG_CFF_SETTER) == KNH_FLAG_CFF_SETTER)

#define knh_ClassStruct_setSetter(o,n,b)  \
	if(b) ((ClassStruct)o)->fields[n].flag |= KNH_FLAG_CFF_SETTER; else ((ClassStruct)o)->fields[n].flag &= ~(KNH_FLAG_CFF_SETTER);

#define KNH_FLAG_CFF_KEY                KNH_FLAG_T6

#define knh_ClassStruct_isKey(o,n)  \
	((((ClassStruct)o)->fields[n].flag & KNH_FLAG_CFF_KEY) == KNH_FLAG_CFF_KEY)

#define knh_ClassStruct_setKey(o,n,b)  \
	if(b) ((ClassStruct)o)->fields[n].flag |= KNH_FLAG_CFF_KEY; else ((ClassStruct)o)->fields[n].flag &= ~(KNH_FLAG_CFF_KEY);


/* ------------------------------------------------------------------------ */
/* Method */
#define KNH_FLAG_MF_PRIVATE             KNH_FLAG_T0

#define knh_Method_isPrivate(o)  \
	((DP((Method*)o)->flag & KNH_FLAG_MF_PRIVATE) == KNH_FLAG_MF_PRIVATE)

#define knh_Method_isPublic(o)   \
	((DP((Method*)o)->flag & KNH_FLAG_MF_PRIVATE) != KNH_FLAG_MF_PRIVATE)

#define knh_Method_setPrivate(o,b)  \
	if(b) DP((Method*)o)->flag |= KNH_FLAG_MF_PRIVATE; else DP((Method*)o)->flag &= ~(KNH_FLAG_MF_PRIVATE);


#define knh_Method_setPublic(o,b)  \
	if(b) DP((Method*)o)->flag &= ~(KNH_FLAG_MF_PRIVATE); else DP((Method*)o)->flag |= KNH_FLAG_MF_PRIVATE;

#define KNH_FLAG_MF_VIRTUAL             KNH_FLAG_T1

#define knh_Method_isVirtual(o)  \
	((DP((Method*)o)->flag & KNH_FLAG_MF_VIRTUAL) == KNH_FLAG_MF_VIRTUAL)

#define knh_Method_isFinal(o)   \
	((DP((Method*)o)->flag & KNH_FLAG_MF_VIRTUAL) != KNH_FLAG_MF_VIRTUAL)

#define knh_Method_setVirtual(o,b)  \
	if(b) DP((Method*)o)->flag |= KNH_FLAG_MF_VIRTUAL; else DP((Method*)o)->flag &= ~(KNH_FLAG_MF_VIRTUAL);


#define knh_Method_setFinal(o,b)  \
	if(b) DP((Method*)o)->flag &= ~(KNH_FLAG_MF_VIRTUAL); else DP((Method*)o)->flag |= KNH_FLAG_MF_VIRTUAL;

#define KNH_FLAG_MF_RELEASE             KNH_FLAG_T2

#define knh_Method_isRelease(o)  \
	((DP((Method*)o)->flag & KNH_FLAG_MF_RELEASE) == KNH_FLAG_MF_RELEASE)

#define knh_Method_isDebug(o)   \
	((DP((Method*)o)->flag & KNH_FLAG_MF_RELEASE) != KNH_FLAG_MF_RELEASE)

#define knh_Method_setRelease(o,b)  \
	if(b) DP((Method*)o)->flag |= KNH_FLAG_MF_RELEASE; else DP((Method*)o)->flag &= ~(KNH_FLAG_MF_RELEASE);


#define knh_Method_setDebug(o,b)  \
	if(b) DP((Method*)o)->flag &= ~(KNH_FLAG_MF_RELEASE); else DP((Method*)o)->flag |= KNH_FLAG_MF_RELEASE;

#define KNH_FLAG_MF_CONST               KNH_FLAG_T3

#define knh_Method_isConst(o)  \
	((DP((Method*)o)->flag & KNH_FLAG_MF_CONST) == KNH_FLAG_MF_CONST)
#define KNH_FLAG_MF_STATIC              KNH_FLAG_T4

#define knh_Method_isStatic(o)  \
	((DP((Method*)o)->flag & KNH_FLAG_MF_STATIC) == KNH_FLAG_MF_STATIC)
#define KNH_FLAG_MF_NULLBASE            KNH_FLAG_T5

#define knh_Method_isNullBase(o)  \
	((DP((Method*)o)->flag & KNH_FLAG_MF_NULLBASE) == KNH_FLAG_MF_NULLBASE)
#define KNH_FLAG_MF_VARARGS             KNH_FLAG_T6

#define knh_Method_isVarArgs(o)  \
	((DP((Method*)o)->flag & KNH_FLAG_MF_VARARGS) == KNH_FLAG_MF_VARARGS)

#define knh_Method_setVarArgs(o,b)  \
	if(b) DP((Method*)o)->flag |= KNH_FLAG_MF_VARARGS; else DP((Method*)o)->flag &= ~(KNH_FLAG_MF_VARARGS);

#define KNH_FLAG_MF_GENERATOR           KNH_FLAG_T7

#define knh_Method_isGenerator(o)  \
	((DP((Method*)o)->flag & KNH_FLAG_MF_GENERATOR) == KNH_FLAG_MF_GENERATOR)

#define knh_Method_setGenerator(o,b)  \
	if(b) DP((Method*)o)->flag |= KNH_FLAG_MF_GENERATOR; else DP((Method*)o)->flag &= ~(KNH_FLAG_MF_GENERATOR);

#define KNH_FLAG_MF_ASPECT              KNH_FLAG_T8

#define knh_Method_isAspect(o)  \
	((DP((Method*)o)->flag & KNH_FLAG_MF_ASPECT) == KNH_FLAG_MF_ASPECT)

#define knh_Method_setAspect(o,b)  \
	if(b) DP((Method*)o)->flag |= KNH_FLAG_MF_ASPECT; else DP((Method*)o)->flag &= ~(KNH_FLAG_MF_ASPECT);

#define KNH_FLAG_MF_OBJECTCODE          KNH_FLAG_T9

#define knh_Method_isObjectCode(o)  \
	((DP((Method*)o)->flag & KNH_FLAG_MF_OBJECTCODE) == KNH_FLAG_MF_OBJECTCODE)

#define knh_Method_setObjectCode(o,b)  \
	if(b) DP((Method*)o)->flag |= KNH_FLAG_MF_OBJECTCODE; else DP((Method*)o)->flag &= ~(KNH_FLAG_MF_OBJECTCODE);

#define KNH_FLAG_MF_GENERATED           KNH_FLAG_T10

#define knh_Method_isGenerated(o)  \
	((DP((Method*)o)->flag & KNH_FLAG_MF_GENERATED) == KNH_FLAG_MF_GENERATED)

#define knh_Method_setGenerated(o,b)  \
	if(b) DP((Method*)o)->flag |= KNH_FLAG_MF_GENERATED; else DP((Method*)o)->flag &= ~(KNH_FLAG_MF_GENERATED);


/* ------------------------------------------------------------------------ */
/* Mapper */
#define KNH_FLAG_MMF_INTERFACE          KNH_FLAG_T0

#define knh_Mapper_isInterface(o)  \
	((DP((Mapper*)o)->flag & KNH_FLAG_MMF_INTERFACE) == KNH_FLAG_MMF_INTERFACE)

#define knh_Mapper_setInterface(o,b)  \
	if(b) DP((Mapper*)o)->flag |= KNH_FLAG_MMF_INTERFACE; else DP((Mapper*)o)->flag &= ~(KNH_FLAG_MMF_INTERFACE);

#define KNH_FLAG_MMF_ICAST              KNH_FLAG_T1

#define knh_Mapper_isICast(o)  \
	((DP((Mapper*)o)->flag & KNH_FLAG_MMF_ICAST) == KNH_FLAG_MMF_ICAST)
#define KNH_FLAG_MMF_SIGNIFICANT        KNH_FLAG_T2

#define knh_Mapper_isSignificant(o)  \
	((DP((Mapper*)o)->flag & KNH_FLAG_MMF_SIGNIFICANT) == KNH_FLAG_MMF_SIGNIFICANT)

#define knh_Mapper_setSignificant(o,b)  \
	if(b) DP((Mapper*)o)->flag |= KNH_FLAG_MMF_SIGNIFICANT; else DP((Mapper*)o)->flag &= ~(KNH_FLAG_MMF_SIGNIFICANT);

#define KNH_FLAG_MMF_FINAL              KNH_FLAG_T3

#define knh_Mapper_isFinal(o)  \
	((DP((Mapper*)o)->flag & KNH_FLAG_MMF_FINAL) == KNH_FLAG_MMF_FINAL)
#define KNH_FLAG_MMF_SYNONYM            KNH_FLAG_T4

#define knh_Mapper_isSynonym(o)  \
	((DP((Mapper*)o)->flag & KNH_FLAG_MMF_SYNONYM) == KNH_FLAG_MMF_SYNONYM)

#define knh_Mapper_setSynonym(o,b)  \
	if(b) DP((Mapper*)o)->flag |= KNH_FLAG_MMF_SYNONYM; else DP((Mapper*)o)->flag &= ~(KNH_FLAG_MMF_SYNONYM);

#define KNH_FLAG_MMF_LOSSLESS           KNH_FLAG_T5

#define knh_Mapper_isLossLess(o)  \
	((DP((Mapper*)o)->flag & KNH_FLAG_MMF_LOSSLESS) == KNH_FLAG_MMF_LOSSLESS)

#define knh_Mapper_setLossLess(o,b)  \
	if(b) DP((Mapper*)o)->flag |= KNH_FLAG_MMF_LOSSLESS; else DP((Mapper*)o)->flag &= ~(KNH_FLAG_MMF_LOSSLESS);

#define KNH_FLAG_MMF_TOTAL              KNH_FLAG_T6

#define knh_Mapper_isTotal(o)  \
	((DP((Mapper*)o)->flag & KNH_FLAG_MMF_TOTAL) == KNH_FLAG_MMF_TOTAL)

#define knh_Mapper_isPartial(o)   \
	((DP((Mapper*)o)->flag & KNH_FLAG_MMF_TOTAL) != KNH_FLAG_MMF_TOTAL)

#define knh_Mapper_setTotal(o,b)  \
	if(b) DP((Mapper*)o)->flag |= KNH_FLAG_MMF_TOTAL; else DP((Mapper*)o)->flag &= ~(KNH_FLAG_MMF_TOTAL);


#define knh_Mapper_setPartial(o,b)  \
	if(b) DP((Mapper*)o)->flag &= ~(KNH_FLAG_MMF_TOTAL); else DP((Mapper*)o)->flag |= KNH_FLAG_MMF_TOTAL;

#define KNH_FLAG_MMF_CONST              KNH_FLAG_T7

#define knh_Mapper_isConst(o)  \
	((DP((Mapper*)o)->flag & KNH_FLAG_MMF_CONST) == KNH_FLAG_MMF_CONST)

#define knh_Mapper_isTemporal(o)   \
	((DP((Mapper*)o)->flag & KNH_FLAG_MMF_CONST) != KNH_FLAG_MMF_CONST)

#define knh_Mapper_setConst(o,b)  \
	if(b) DP((Mapper*)o)->flag |= KNH_FLAG_MMF_CONST; else DP((Mapper*)o)->flag &= ~(KNH_FLAG_MMF_CONST);


#define knh_Mapper_setTemporal(o,b)  \
	if(b) DP((Mapper*)o)->flag &= ~(KNH_FLAG_MMF_CONST); else DP((Mapper*)o)->flag |= KNH_FLAG_MMF_CONST;

#define KNH_FLAG_MMF_LOCAL              KNH_FLAG_T8

#define knh_Mapper_isLocal(o)  \
	((DP((Mapper*)o)->flag & KNH_FLAG_MMF_LOCAL) == KNH_FLAG_MMF_LOCAL)

#define knh_Mapper_setLocal(o,b)  \
	if(b) DP((Mapper*)o)->flag |= KNH_FLAG_MMF_LOCAL; else DP((Mapper*)o)->flag &= ~(KNH_FLAG_MMF_LOCAL);

#define KNH_FLAG_MMF_DERIVED            KNH_FLAG_T9

#define knh_Mapper_isDerived(o)  \
	((DP((Mapper*)o)->flag & KNH_FLAG_MMF_DERIVED) == KNH_FLAG_MMF_DERIVED)

#define knh_Mapper_setDerived(o,b)  \
	if(b) DP((Mapper*)o)->flag |= KNH_FLAG_MMF_DERIVED; else DP((Mapper*)o)->flag &= ~(KNH_FLAG_MMF_DERIVED);

#define KNH_FLAG_MMF_MAPMAP             KNH_FLAG_OF_LOCAL1

#define knh_Mapper_isMapMap(o)  \
	(((o)->h.flag & KNH_FLAG_MMF_MAPMAP) == KNH_FLAG_MMF_MAPMAP)

#define knh_Mapper_setMapMap(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_MMF_MAPMAP; else (o)->h.flag &= ~(KNH_FLAG_MMF_MAPMAP);


/* ------------------------------------------------------------------------ */
/* ClassMap */
#define KNH_FLAG_CM_SORTED              KNH_FLAG_OF_LOCAL1

#define knh_ClassMap_isSorted(o)  \
	(((o)->h.flag & KNH_FLAG_CM_SORTED) == KNH_FLAG_CM_SORTED)

#define knh_ClassMap_setSorted(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_CM_SORTED; else (o)->h.flag &= ~(KNH_FLAG_CM_SORTED);


/* ------------------------------------------------------------------------ */
/* Closure */
#define KNH_FLAG_CCF_SHAREDSTACK        KNH_FLAG_OF_LOCAL1

#define knh_Closure_isSharedStack(o)  \
	(((o)->h.flag & KNH_FLAG_CCF_SHAREDSTACK) == KNH_FLAG_CCF_SHAREDSTACK)

#define knh_Closure_setSharedStack(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_CCF_SHAREDSTACK; else (o)->h.flag &= ~(KNH_FLAG_CCF_SHAREDSTACK);

#define KNH_FLAG_CCF_COPIEDSTACK        KNH_FLAG_OF_LOCAL2

#define knh_Closure_isCopiedStack(o)  \
	(((o)->h.flag & KNH_FLAG_CCF_COPIEDSTACK) == KNH_FLAG_CCF_COPIEDSTACK)

#define knh_Closure_setCopiedStack(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_CCF_COPIEDSTACK; else (o)->h.flag &= ~(KNH_FLAG_CCF_COPIEDSTACK);


/* ------------------------------------------------------------------------ */
/* InputStream */
#define KNH_FLAG_IN_FILE                KNH_FLAG_OF_LOCAL1

#define knh_InputStream_isFILE(o)  \
	(((o)->h.flag & KNH_FLAG_IN_FILE) == KNH_FLAG_IN_FILE)

#define knh_InputStream_setFILE(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_IN_FILE; else (o)->h.flag &= ~(KNH_FLAG_IN_FILE);


/* ------------------------------------------------------------------------ */
/* OutputStream */
#define KNH_FLAG_OUT_BOL                KNH_FLAG_OF_LOCAL1

#define knh_OutputStream_isBOL(o)  \
	(((o)->h.flag & KNH_FLAG_OUT_BOL) == KNH_FLAG_OUT_BOL)

#define knh_OutputStream_setBOL(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_OUT_BOL; else (o)->h.flag &= ~(KNH_FLAG_OUT_BOL);

#define KNH_FLAG_OUT_AUTOFLUSH          KNH_FLAG_OF_LOCAL2

#define knh_OutputStream_isAutoFlush(o)  \
	(((o)->h.flag & KNH_FLAG_OUT_AUTOFLUSH) == KNH_FLAG_OUT_AUTOFLUSH)

#define knh_OutputStream_setAutoFlush(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_OUT_AUTOFLUSH; else (o)->h.flag &= ~(KNH_FLAG_OUT_AUTOFLUSH);

#define KNH_FLAG_OUT_STORINGBUFFER      KNH_FLAG_OF_LOCAL3

#define knh_OutputStream_isStoringBuffer(o)  \
	(((o)->h.flag & KNH_FLAG_OUT_STORINGBUFFER) == KNH_FLAG_OUT_STORINGBUFFER)

#define knh_OutputStream_setStoringBuffer(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_OUT_STORINGBUFFER; else (o)->h.flag &= ~(KNH_FLAG_OUT_STORINGBUFFER);


/* ------------------------------------------------------------------------ */
/* Exception */
#define KNH_FLAG_EF_FATAL               KNH_FLAG_T0

#define knh_Exception_isFatal(o)  \
	((DP((Exception*)o)->flag & KNH_FLAG_EF_FATAL) == KNH_FLAG_EF_FATAL)
#define KNH_FLAG_EF_LOGGING             KNH_FLAG_T1

#define knh_Exception_isLogging(o)  \
	((DP((Exception*)o)->flag & KNH_FLAG_EF_LOGGING) == KNH_FLAG_EF_LOGGING)
#define KNH_FLAG_EF_GENERATED           KNH_FLAG_T2

#define knh_Exception_isGenerated(o)  \
	((DP((Exception*)o)->flag & KNH_FLAG_EF_GENERATED) == KNH_FLAG_EF_GENERATED)
#define KNH_FLAG_EF_CAUGHT              KNH_FLAG_T3

#define knh_Exception_isCaught(o)  \
	((DP((Exception*)o)->flag & KNH_FLAG_EF_CAUGHT) == KNH_FLAG_EF_CAUGHT)

#define knh_Exception_setCaught(o,b)  \
	if(b) DP((Exception*)o)->flag |= KNH_FLAG_EF_CAUGHT; else DP((Exception*)o)->flag &= ~(KNH_FLAG_EF_CAUGHT);


/* ------------------------------------------------------------------------ */
/* ExceptionHandler */
#define KNH_FLAG_EHF_JUMPABLE           KNH_FLAG_OF_LOCAL1

#define knh_ExceptionHandler_isJumpable(o)  \
	(((o)->h.flag & KNH_FLAG_EHF_JUMPABLE) == KNH_FLAG_EHF_JUMPABLE)

#define knh_ExceptionHandler_setJumpable(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_EHF_JUMPABLE; else (o)->h.flag &= ~(KNH_FLAG_EHF_JUMPABLE);

#define KNH_FLAG_EHF_CATCHING           KNH_FLAG_OF_LOCAL2

#define knh_ExceptionHandler_isCatching(o)  \
	(((o)->h.flag & KNH_FLAG_EHF_CATCHING) == KNH_FLAG_EHF_CATCHING)

#define knh_ExceptionHandler_setCatching(o,b)  \
	if(b) (o)->h.flag |= KNH_FLAG_EHF_CATCHING; else (o)->h.flag &= ~(KNH_FLAG_EHF_CATCHING);


/* ------------------------------------------------------------------------ */
/* Context */
#define KNH_FLAG_CTXF_STRICT            KNH_FLAG_T0

#define knh_Context_isStrict(o)  \
	((((Context*)o)->flag & KNH_FLAG_CTXF_STRICT) == KNH_FLAG_CTXF_STRICT)

#define knh_Context_setStrict(o,b)  \
	if(b) ((Context*)o)->flag |= KNH_FLAG_CTXF_STRICT; else ((Context*)o)->flag &= ~(KNH_FLAG_CTXF_STRICT);

#define KNH_FLAG_CTXF_DEBUG             KNH_FLAG_T1

#define knh_Context_isDebug(o)  \
	((((Context*)o)->flag & KNH_FLAG_CTXF_DEBUG) == KNH_FLAG_CTXF_DEBUG)

#define knh_Context_setDebug(o,b)  \
	if(b) ((Context*)o)->flag |= KNH_FLAG_CTXF_DEBUG; else ((Context*)o)->flag &= ~(KNH_FLAG_CTXF_DEBUG);

#define KNH_FLAG_CTXF_VERBOSE           KNH_FLAG_T2

#define knh_Context_isVerbose(o)  \
	((((Context*)o)->flag & KNH_FLAG_CTXF_VERBOSE) == KNH_FLAG_CTXF_VERBOSE)

#define knh_Context_setVerbose(o,b)  \
	if(b) ((Context*)o)->flag |= KNH_FLAG_CTXF_VERBOSE; else ((Context*)o)->flag &= ~(KNH_FLAG_CTXF_VERBOSE);

#define KNH_FLAG_CTXF_TRUSTED           KNH_FLAG_T3

#define knh_Context_isTrusted(o)  \
	((((Context*)o)->flag & KNH_FLAG_CTXF_TRUSTED) == KNH_FLAG_CTXF_TRUSTED)

#define knh_Context_setTrusted(o,b)  \
	if(b) ((Context*)o)->flag |= KNH_FLAG_CTXF_TRUSTED; else ((Context*)o)->flag &= ~(KNH_FLAG_CTXF_TRUSTED);

#define KNH_FLAG_CTXF_INTERACTIVE       KNH_FLAG_T4

#define knh_Context_isInteractive(o)  \
	((((Context*)o)->flag & KNH_FLAG_CTXF_INTERACTIVE) == KNH_FLAG_CTXF_INTERACTIVE)

#define knh_Context_setInteractive(o,b)  \
	if(b) ((Context*)o)->flag |= KNH_FLAG_CTXF_INTERACTIVE; else ((Context*)o)->flag &= ~(KNH_FLAG_CTXF_INTERACTIVE);

#define KNH_FLAG_CTXF_COMPILING         KNH_FLAG_T5

#define knh_Context_isCompiling(o)  \
	((((Context*)o)->flag & KNH_FLAG_CTXF_COMPILING) == KNH_FLAG_CTXF_COMPILING)

#define knh_Context_setCompiling(o,b)  \
	if(b) ((Context*)o)->flag |= KNH_FLAG_CTXF_COMPILING; else ((Context*)o)->flag &= ~(KNH_FLAG_CTXF_COMPILING);


/* ------------------------------------------------------------------------ */
/* Token */
#define KNH_FLAG_TKF_BOL                KNH_FLAG_T0

#define knh_Token_isBOL(o)  \
	((SP(o)->flag & KNH_FLAG_TKF_BOL) == KNH_FLAG_TKF_BOL)

#define knh_Token_setBOL(o,b)  \
	if(b) SP(o)->flag |= KNH_FLAG_TKF_BOL; else SP(o)->flag &= ~(KNH_FLAG_TKF_BOL);

#define KNH_FLAG_TKF_TAILWILDCARD       KNH_FLAG_T1

#define knh_Token_isTailWildCard(o)  \
	((SP(o)->flag & KNH_FLAG_TKF_TAILWILDCARD) == KNH_FLAG_TKF_TAILWILDCARD)

#define knh_Token_setTailWildCard(o,b)  \
	if(b) SP(o)->flag |= KNH_FLAG_TKF_TAILWILDCARD; else SP(o)->flag &= ~(KNH_FLAG_TKF_TAILWILDCARD);

#define KNH_FLAG_TKF_TOPDOT             KNH_FLAG_T2

#define knh_Token_isTopDot(o)  \
	((SP(o)->flag & KNH_FLAG_TKF_TOPDOT) == KNH_FLAG_TKF_TOPDOT)

#define knh_Token_setTopDot(o,b)  \
	if(b) SP(o)->flag |= KNH_FLAG_TKF_TOPDOT; else SP(o)->flag &= ~(KNH_FLAG_TKF_TOPDOT);

#define KNH_FLAG_TKF_GETTER             KNH_FLAG_T3

#define knh_Token_isGetter(o)  \
	((SP(o)->flag & KNH_FLAG_TKF_GETTER) == KNH_FLAG_TKF_GETTER)

#define knh_Token_setGetter(o,b)  \
	if(b) SP(o)->flag |= KNH_FLAG_TKF_GETTER; else SP(o)->flag &= ~(KNH_FLAG_TKF_GETTER);

#define KNH_FLAG_TKF_SETTER             KNH_FLAG_T4

#define knh_Token_isSetter(o)  \
	((SP(o)->flag & KNH_FLAG_TKF_SETTER) == KNH_FLAG_TKF_SETTER)

#define knh_Token_setSetter(o,b)  \
	if(b) SP(o)->flag |= KNH_FLAG_TKF_SETTER; else SP(o)->flag &= ~(KNH_FLAG_TKF_SETTER);

#define KNH_FLAG_TKF_EXCEPTIONTYPE      KNH_FLAG_T5

#define knh_Token_isExceptionType(o)  \
	((SP(o)->flag & KNH_FLAG_TKF_EXCEPTIONTYPE) == KNH_FLAG_TKF_EXCEPTIONTYPE)

#define knh_Token_setExceptionType(o,b)  \
	if(b) SP(o)->flag |= KNH_FLAG_TKF_EXCEPTIONTYPE; else SP(o)->flag &= ~(KNH_FLAG_TKF_EXCEPTIONTYPE);

#define KNH_FLAG_TKF_NOTNULLTYPE        KNH_FLAG_T6

#define knh_Token_isNotNullType(o)  \
	((SP(o)->flag & KNH_FLAG_TKF_NOTNULLTYPE) == KNH_FLAG_TKF_NOTNULLTYPE)

#define knh_Token_setNotNullType(o,b)  \
	if(b) SP(o)->flag |= KNH_FLAG_TKF_NOTNULLTYPE; else SP(o)->flag &= ~(KNH_FLAG_TKF_NOTNULLTYPE);

#define KNH_FLAG_TKF_ITERATORTYPE       KNH_FLAG_T7

#define knh_Token_isIteratorType(o)  \
	((SP(o)->flag & KNH_FLAG_TKF_ITERATORTYPE) == KNH_FLAG_TKF_ITERATORTYPE)

#define knh_Token_setIteratorType(o,b)  \
	if(b) SP(o)->flag |= KNH_FLAG_TKF_ITERATORTYPE; else SP(o)->flag &= ~(KNH_FLAG_TKF_ITERATORTYPE);

#define KNH_FLAG_TKF_ARRAYTYPE          KNH_FLAG_T8

#define knh_Token_isArrayType(o)  \
	((SP(o)->flag & KNH_FLAG_TKF_ARRAYTYPE) == KNH_FLAG_TKF_ARRAYTYPE)

#define knh_Token_setArrayType(o,b)  \
	if(b) SP(o)->flag |= KNH_FLAG_TKF_ARRAYTYPE; else SP(o)->flag &= ~(KNH_FLAG_TKF_ARRAYTYPE);

#define KNH_FLAG_TKF_NULLABLETYPE       KNH_FLAG_T9

#define knh_Token_isNullableType(o)  \
	((SP(o)->flag & KNH_FLAG_TKF_NULLABLETYPE) == KNH_FLAG_TKF_NULLABLETYPE)

#define knh_Token_setNullableType(o,b)  \
	if(b) SP(o)->flag |= KNH_FLAG_TKF_NULLABLETYPE; else SP(o)->flag &= ~(KNH_FLAG_TKF_NULLABLETYPE);


/* ------------------------------------------------------------------------ */
/* Stmt */
#define KNH_FLAG_STMTF_ADPOSITION       KNH_FLAG_T0

#define knh_Stmt_isAdposition(o)  \
	((SP(o)->flag & KNH_FLAG_STMTF_ADPOSITION) == KNH_FLAG_STMTF_ADPOSITION)

#define knh_Stmt_setAdposition(o,b)  \
	if(b) SP(o)->flag |= KNH_FLAG_STMTF_ADPOSITION; else SP(o)->flag &= ~(KNH_FLAG_STMTF_ADPOSITION);

#define KNH_FLAG_STMTF_NONNEWLINE       KNH_FLAG_T1

#define knh_Stmt_isNonNewLine(o)  \
	((SP(o)->flag & KNH_FLAG_STMTF_NONNEWLINE) == KNH_FLAG_STMTF_NONNEWLINE)

#define knh_Stmt_setNonNewLine(o,b)  \
	if(b) SP(o)->flag |= KNH_FLAG_STMTF_NONNEWLINE; else SP(o)->flag &= ~(KNH_FLAG_STMTF_NONNEWLINE);

#define KNH_FLAG_STMTF_TYPED            KNH_FLAG_T2

#define knh_Stmt_isTyped(o)  \
	((SP(o)->flag & KNH_FLAG_STMTF_TYPED) == KNH_FLAG_STMTF_TYPED)

#define knh_Stmt_setTyped(o,b)  \
	if(b) SP(o)->flag |= KNH_FLAG_STMTF_TYPED; else SP(o)->flag &= ~(KNH_FLAG_STMTF_TYPED);

#define KNH_FLAG_STMTF_MEMO1            KNH_FLAG_T3

#define knh_Stmt_isMemo1(o)  \
	((SP(o)->flag & KNH_FLAG_STMTF_MEMO1) == KNH_FLAG_STMTF_MEMO1)

#define knh_Stmt_setMemo1(o,b)  \
	if(b) SP(o)->flag |= KNH_FLAG_STMTF_MEMO1; else SP(o)->flag &= ~(KNH_FLAG_STMTF_MEMO1);


/* ------------------------------------------------------------------------ */
/* Asm */
#define KNH_FLAG_CPF_CANCELLED          KNH_FLAG_T0

#define knh_Asm_isCancelled(o)  \
	((DP(o)->flag & KNH_FLAG_CPF_CANCELLED) == KNH_FLAG_CPF_CANCELLED)

#define knh_Asm_setCancelled(o,b)  \
	if(b) DP(o)->flag |= KNH_FLAG_CPF_CANCELLED; else DP(o)->flag &= ~(KNH_FLAG_CPF_CANCELLED);

#define KNH_FLAG_CPF_PROCEED            KNH_FLAG_T1

#define knh_Asm_isPROCEED(o)  \
	((DP(o)->flag & KNH_FLAG_CPF_PROCEED) == KNH_FLAG_CPF_PROCEED)

#define knh_Asm_setPROCEED(o,b)  \
	if(b) DP(o)->flag |= KNH_FLAG_CPF_PROCEED; else DP(o)->flag &= ~(KNH_FLAG_CPF_PROCEED);

#define KNH_FLAG_CPF_YEILD              KNH_FLAG_T2

#define knh_Asm_isYEILD(o)  \
	((DP(o)->flag & KNH_FLAG_CPF_YEILD) == KNH_FLAG_CPF_YEILD)

#define knh_Asm_setYEILD(o,b)  \
	if(b) DP(o)->flag |= KNH_FLAG_CPF_YEILD; else DP(o)->flag &= ~(KNH_FLAG_CPF_YEILD);


/* ======================================================================== */
/* [CLASS] */

/* ------------------------------------------------------------------------ */
/* Object */
#define STRUCT_Object           ((knh_struct_t)0)
#define CLASS_Object            ((knh_class_t)0)
#define IS_bObject(o)           ((o)->h.bcid == CLASS_Object)
#ifndef Object
#define Object                  knh_Object_t
#endif
#define IS_Object(o)            ((o)->h.cid == CLASS_Object)
#define ASSERT_Object(o)        DEBUG_ASSERT(((o)->h.cid == CLASS_Object))
#define TYPE_Object             CLASS_Object
#define NNTYPE_Object           TYPE_TONNTYPE(CLASS_Object)
#define CFLAG_Object            ((knh_flag_t)KNH_FLAG_CF_CYCLIC)
#define FLAG_Object             KNH_FLAG_CF2OF(CFLAG_Object)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Any */
#define STRUCT_Any              ((knh_struct_t)1)
#define CLASS_Any               ((knh_class_t)1)
#define IS_bAny(o)              ((o)->h.bcid == CLASS_Any)
#ifndef Any
#define Any                     knh_Any_t
#endif
#define IS_Any(o)               ((o)->h.cid == CLASS_Any)
#define ASSERT_Any(o)           DEBUG_ASSERT(((o)->h.cid == CLASS_Any))
#define TYPE_Any                CLASS_Any
#define NNTYPE_Any              TYPE_TONNTYPE(CLASS_Any)
#define CFLAG_Any               ((knh_flag_t)KNH_FLAG_CF_CYCLIC)
#define FLAG_Any                KNH_FLAG_CF2OF(CFLAG_Any)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* This */
#define STRUCT_This             STRUCT_Any
#define CLASS_This              ((knh_class_t)KNH_TCLASS_SIZE-(0+1))
#ifndef This
#define This                    knh_This_t
#endif
#define IS_This(o)              ((o)->h.cid == CLASS_This)
#define ASSERT_This(o)          DEBUG_ASSERT(((o)->h.cid == CLASS_This))
#define TYPE_This               CLASS_This
#define NNTYPE_This             TYPE_TONNTYPE(CLASS_This)
#define CFLAG_This              ((knh_flag_t)KNH_FLAG_CF_CYCLIC|KNH_FLAG_CF_PRIVATE)
#define FLAG_This               KNH_FLAG_CF2OF(CFLAG_This)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Any0 */
#define STRUCT_Any0             STRUCT_Any
#define CLASS_Any0              ((knh_class_t)KNH_TCLASS_SIZE-(1+1))
#ifndef Any0
#define Any0                    knh_Any0_t
#endif
#define IS_Any0(o)              ((o)->h.cid == CLASS_Any0)
#define ASSERT_Any0(o)          DEBUG_ASSERT(((o)->h.cid == CLASS_Any0))
#define TYPE_Any0               CLASS_Any0
#define NNTYPE_Any0             TYPE_TONNTYPE(CLASS_Any0)
#define CFLAG_Any0              ((knh_flag_t)KNH_FLAG_CF_CYCLIC|KNH_FLAG_CF_PRIVATE)
#define FLAG_Any0               KNH_FLAG_CF2OF(CFLAG_Any0)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Any1 */
#define STRUCT_Any1             STRUCT_Any
#define CLASS_Any1              ((knh_class_t)KNH_TCLASS_SIZE-(2+1))
#ifndef Any1
#define Any1                    knh_Any1_t
#endif
#define IS_Any1(o)              ((o)->h.cid == CLASS_Any1)
#define ASSERT_Any1(o)          DEBUG_ASSERT(((o)->h.cid == CLASS_Any1))
#define TYPE_Any1               CLASS_Any1
#define NNTYPE_Any1             TYPE_TONNTYPE(CLASS_Any1)
#define CFLAG_Any1              ((knh_flag_t)KNH_FLAG_CF_CYCLIC|KNH_FLAG_CF_PRIVATE)
#define FLAG_Any1               KNH_FLAG_CF2OF(CFLAG_Any1)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Any2 */
#define STRUCT_Any2             STRUCT_Any
#define CLASS_Any2              ((knh_class_t)KNH_TCLASS_SIZE-(3+1))
#ifndef Any2
#define Any2                    knh_Any2_t
#endif
#define IS_Any2(o)              ((o)->h.cid == CLASS_Any2)
#define ASSERT_Any2(o)          DEBUG_ASSERT(((o)->h.cid == CLASS_Any2))
#define TYPE_Any2               CLASS_Any2
#define NNTYPE_Any2             TYPE_TONNTYPE(CLASS_Any2)
#define CFLAG_Any2              ((knh_flag_t)KNH_FLAG_CF_CYCLIC|KNH_FLAG_CF_PRIVATE)
#define FLAG_Any2               KNH_FLAG_CF2OF(CFLAG_Any2)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Any3 */
#define STRUCT_Any3             STRUCT_Any
#define CLASS_Any3              ((knh_class_t)KNH_TCLASS_SIZE-(4+1))
#ifndef Any3
#define Any3                    knh_Any3_t
#endif
#define IS_Any3(o)              ((o)->h.cid == CLASS_Any3)
#define ASSERT_Any3(o)          DEBUG_ASSERT(((o)->h.cid == CLASS_Any3))
#define TYPE_Any3               CLASS_Any3
#define NNTYPE_Any3             TYPE_TONNTYPE(CLASS_Any3)
#define CFLAG_Any3              ((knh_flag_t)KNH_FLAG_CF_CYCLIC|KNH_FLAG_CF_PRIVATE)
#define FLAG_Any3               KNH_FLAG_CF2OF(CFLAG_Any3)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Nue */
#define STRUCT_Nue              ((knh_struct_t)2)
#define CLASS_Nue               ((knh_class_t)2)
#define IS_bNue(o)              ((o)->h.bcid == CLASS_Nue)
#ifndef Nue
#define Nue                     knh_Nue_t
#endif
#define IS_Nue(o)               ((o)->h.cid == CLASS_Nue)
#define ASSERT_Nue(o)           DEBUG_ASSERT(((o)->h.cid == CLASS_Nue))
#define TYPE_Nue                CLASS_Nue
#define NNTYPE_Nue              TYPE_TONNTYPE(CLASS_Nue)
#define CFLAG_Nue               ((knh_flag_t)KNH_FLAG_CF_IMMUTABLE|KNH_FLAG_CF_PRIVATE)
#define FLAG_Nue                KNH_FLAG_CF2OF(CFLAG_Nue)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Boolean */
#define STRUCT_Boolean          ((knh_struct_t)3)
#define CLASS_Boolean           ((knh_class_t)3)
#define IS_bBoolean(o)          ((o)->h.bcid == CLASS_Boolean)
#ifndef Boolean
#define Boolean                 knh_Boolean_t
#endif
#define IS_Boolean(o)           ((o)->h.cid == CLASS_Boolean)
#define ASSERT_Boolean(o)       DEBUG_ASSERT(((o)->h.cid == CLASS_Boolean))
#define TYPE_Boolean            CLASS_Boolean
#define NNTYPE_Boolean          TYPE_TONNTYPE(CLASS_Boolean)
#define CFLAG_Boolean           ((knh_flag_t)KNH_FLAG_CF_IMMUTABLE)
#define FLAG_Boolean            KNH_FLAG_CF2OF(CFLAG_Boolean)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Number */
#define STRUCT_Number           ((knh_struct_t)4)
#define CLASS_Number            ((knh_class_t)4)
#define IS_bNumber(o)           ((o)->h.bcid == CLASS_Number)
#ifndef Number
#define Number                  knh_Number_t
#endif
#define IS_Number(o)            ((o)->h.cid == CLASS_Number)
#define ASSERT_Number(o)        DEBUG_ASSERT(((o)->h.cid == CLASS_Number))
#define TYPE_Number             CLASS_Number
#define NNTYPE_Number           TYPE_TONNTYPE(CLASS_Number)
#define CFLAG_Number            ((knh_flag_t)KNH_FLAG_CF_IMMUTABLE)
#define FLAG_Number             KNH_FLAG_CF2OF(CFLAG_Number)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Int */
#define STRUCT_Int              ((knh_struct_t)5)
#define CLASS_Int               ((knh_class_t)5)
#define IS_bInt(o)              ((o)->h.bcid == CLASS_Int)
#ifndef Int
#define Int                     knh_Int_t
#endif
#define IS_Int(o)               ((o)->h.cid == CLASS_Int)
#define ASSERT_Int(o)           DEBUG_ASSERT(((o)->h.cid == CLASS_Int))
#define TYPE_Int                CLASS_Int
#define NNTYPE_Int              TYPE_TONNTYPE(CLASS_Int)
#define CFLAG_Int               ((knh_flag_t)KNH_FLAG_CF_IMMUTABLE)
#define FLAG_Int                KNH_FLAG_CF2OF(CFLAG_Int)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Float */
#define STRUCT_Float            ((knh_struct_t)6)
#define CLASS_Float             ((knh_class_t)6)
#define IS_bFloat(o)            ((o)->h.bcid == CLASS_Float)
#ifndef Float
#define Float                   knh_Float_t
#endif
#define IS_Float(o)             ((o)->h.cid == CLASS_Float)
#define ASSERT_Float(o)         DEBUG_ASSERT(((o)->h.cid == CLASS_Float))
#define TYPE_Float              CLASS_Float
#define NNTYPE_Float            TYPE_TONNTYPE(CLASS_Float)
#define CFLAG_Float             ((knh_flag_t)KNH_FLAG_CF_IMMUTABLE)
#define FLAG_Float              KNH_FLAG_CF2OF(CFLAG_Float)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* String */
#define STRUCT_String           ((knh_struct_t)7)
#define CLASS_String            ((knh_class_t)7)
#define IS_bString(o)           ((o)->h.bcid == CLASS_String)
#ifndef String
#define String                  knh_String_t
#endif
#define IS_String(o)            ((o)->h.cid == CLASS_String)
#define ASSERT_String(o)        DEBUG_ASSERT(((o)->h.cid == CLASS_String))
#define TYPE_String             CLASS_String
#define NNTYPE_String           TYPE_TONNTYPE(CLASS_String)
#define CFLAG_String            ((knh_flag_t)KNH_FLAG_CF_IMMUTABLE)
#define FLAG_String             KNH_FLAG_CF2OF(CFLAG_String)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Bytes */
#define STRUCT_Bytes            ((knh_struct_t)8)
#define CLASS_Bytes             ((knh_class_t)8)
#define IS_bBytes(o)            ((o)->h.bcid == CLASS_Bytes)
#ifndef Bytes
#define Bytes                   knh_Bytes_t
#endif
#define IS_Bytes(o)             ((o)->h.cid == CLASS_Bytes)
#define ASSERT_Bytes(o)         DEBUG_ASSERT(((o)->h.cid == CLASS_Bytes))
#define TYPE_Bytes              CLASS_Bytes
#define NNTYPE_Bytes            TYPE_TONNTYPE(CLASS_Bytes)
#define CFLAG_Bytes             ((knh_flag_t)0)
#define FLAG_Bytes              KNH_FLAG_CF2OF(CFLAG_Bytes)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Tuple2 */
#define STRUCT_Tuple2           ((knh_struct_t)9)
#define CLASS_Tuple2            ((knh_class_t)9)
#define IS_bTuple2(o)           ((o)->h.bcid == CLASS_Tuple2)
#ifndef Tuple2
#define Tuple2                  knh_Tuple2_t
#endif
#define IS_Tuple2(o)            ((o)->h.cid == CLASS_Tuple2)
#define ASSERT_Tuple2(o)        DEBUG_ASSERT(((o)->h.cid == CLASS_Tuple2))
#define TYPE_Tuple2             CLASS_Tuple2
#define NNTYPE_Tuple2           TYPE_TONNTYPE(CLASS_Tuple2)
#define CFLAG_Tuple2            ((knh_flag_t)KNH_FLAG_CF_IMMUTABLE)
#define FLAG_Tuple2             KNH_FLAG_CF2OF(CFLAG_Tuple2)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Range */
#define STRUCT_Range            ((knh_struct_t)10)
#define CLASS_Range             ((knh_class_t)10)
#define IS_bRange(o)            ((o)->h.bcid == CLASS_Range)
#ifndef Range
#define Range                   knh_Range_t
#endif
#define IS_Range(o)             ((o)->h.cid == CLASS_Range)
#define ASSERT_Range(o)         DEBUG_ASSERT(((o)->h.cid == CLASS_Range))
#define TYPE_Range              CLASS_Range
#define NNTYPE_Range            TYPE_TONNTYPE(CLASS_Range)
#define CFLAG_Range             ((knh_flag_t)KNH_FLAG_CF_IMMUTABLE)
#define FLAG_Range              KNH_FLAG_CF2OF(CFLAG_Range)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Array */
#define STRUCT_Array            ((knh_struct_t)11)
#define CLASS_Array             ((knh_class_t)11)
#define IS_bArray(o)            ((o)->h.bcid == CLASS_Array)
#ifndef Array
#define Array                   knh_Array_t
#endif
#define IS_Array(o)             ((o)->h.cid == CLASS_Array)
#define ASSERT_Array(o)         DEBUG_ASSERT(((o)->h.cid == CLASS_Array))
#define TYPE_Array              CLASS_Array
#define NNTYPE_Array            TYPE_TONNTYPE(CLASS_Array)
#define CFLAG_Array             ((knh_flag_t)KNH_FLAG_CF_CYCLIC)
#define FLAG_Array              KNH_FLAG_CF2OF(CFLAG_Array)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* IArray */
#define STRUCT_IArray           ((knh_struct_t)12)
#define CLASS_IArray            ((knh_class_t)12)
#define IS_bIArray(o)           ((o)->h.bcid == CLASS_IArray)
#ifndef IArray
#define IArray                  knh_IArray_t
#endif
#define IS_IArray(o)            ((o)->h.cid == CLASS_IArray)
#define ASSERT_IArray(o)        DEBUG_ASSERT(((o)->h.cid == CLASS_IArray))
#define TYPE_IArray             CLASS_IArray
#define NNTYPE_IArray           TYPE_TONNTYPE(CLASS_IArray)
#define CFLAG_IArray            ((knh_flag_t)KNH_FLAG_CF_CYCLIC)
#define FLAG_IArray             KNH_FLAG_CF2OF(CFLAG_IArray)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* FArray */
#define STRUCT_FArray           ((knh_struct_t)13)
#define CLASS_FArray            ((knh_class_t)13)
#define IS_bFArray(o)           ((o)->h.bcid == CLASS_FArray)
#ifndef FArray
#define FArray                  knh_FArray_t
#endif
#define IS_FArray(o)            ((o)->h.cid == CLASS_FArray)
#define ASSERT_FArray(o)        DEBUG_ASSERT(((o)->h.cid == CLASS_FArray))
#define TYPE_FArray             CLASS_FArray
#define NNTYPE_FArray           TYPE_TONNTYPE(CLASS_FArray)
#define CFLAG_FArray            ((knh_flag_t)KNH_FLAG_CF_CYCLIC)
#define FLAG_FArray             KNH_FLAG_CF2OF(CFLAG_FArray)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Iterator */
#define STRUCT_Iterator         ((knh_struct_t)14)
#define CLASS_Iterator          ((knh_class_t)14)
#define IS_bIterator(o)         ((o)->h.bcid == CLASS_Iterator)
#ifndef Iterator
#define Iterator                knh_Iterator_t
#endif
#define IS_Iterator(o)          ((o)->h.cid == CLASS_Iterator)
#define ASSERT_Iterator(o)      DEBUG_ASSERT(((o)->h.cid == CLASS_Iterator))
#define TYPE_Iterator           CLASS_Iterator
#define NNTYPE_Iterator         TYPE_TONNTYPE(CLASS_Iterator)
#define CFLAG_Iterator          ((knh_flag_t)0)
#define FLAG_Iterator           KNH_FLAG_CF2OF(CFLAG_Iterator)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* DictMap */
#define STRUCT_DictMap          ((knh_struct_t)15)
#define CLASS_DictMap           ((knh_class_t)15)
#define IS_bDictMap(o)          ((o)->h.bcid == CLASS_DictMap)
#ifndef DictMap
#define DictMap                 knh_DictMap_t
#endif
#define IS_DictMap(o)           ((o)->h.cid == CLASS_DictMap)
#define ASSERT_DictMap(o)       DEBUG_ASSERT(((o)->h.cid == CLASS_DictMap))
#define TYPE_DictMap            CLASS_DictMap
#define NNTYPE_DictMap          TYPE_TONNTYPE(CLASS_DictMap)
#define CFLAG_DictMap           ((knh_flag_t)KNH_FLAG_CF_CYCLIC)
#define FLAG_DictMap            KNH_FLAG_CF2OF(CFLAG_DictMap)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* DictSet */
#define STRUCT_DictSet          ((knh_struct_t)16)
#define CLASS_DictSet           ((knh_class_t)16)
#define IS_bDictSet(o)          ((o)->h.bcid == CLASS_DictSet)
#ifndef DictSet
#define DictSet                 knh_DictSet_t
#endif
#define IS_DictSet(o)           ((o)->h.cid == CLASS_DictSet)
#define ASSERT_DictSet(o)       DEBUG_ASSERT(((o)->h.cid == CLASS_DictSet))
#define TYPE_DictSet            CLASS_DictSet
#define NNTYPE_DictSet          TYPE_TONNTYPE(CLASS_DictSet)
#define CFLAG_DictSet           ((knh_flag_t)KNH_FLAG_CF_CYCLIC)
#define FLAG_DictSet            KNH_FLAG_CF2OF(CFLAG_DictSet)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* HashMap */
#define STRUCT_HashMap          ((knh_struct_t)17)
#define CLASS_HashMap           ((knh_class_t)17)
#define IS_bHashMap(o)          ((o)->h.bcid == CLASS_HashMap)
#ifndef HashMap
#define HashMap                 knh_HashMap_t
#endif
#define IS_HashMap(o)           ((o)->h.cid == CLASS_HashMap)
#define ASSERT_HashMap(o)       DEBUG_ASSERT(((o)->h.cid == CLASS_HashMap))
#define TYPE_HashMap            CLASS_HashMap
#define NNTYPE_HashMap          TYPE_TONNTYPE(CLASS_HashMap)
#define CFLAG_HashMap           ((knh_flag_t)0)
#define FLAG_HashMap            KNH_FLAG_CF2OF(CFLAG_HashMap)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* HashSet */
#define STRUCT_HashSet          ((knh_struct_t)18)
#define CLASS_HashSet           ((knh_class_t)18)
#define IS_bHashSet(o)          ((o)->h.bcid == CLASS_HashSet)
#ifndef HashSet
#define HashSet                 knh_HashSet_t
#endif
#define IS_HashSet(o)           ((o)->h.cid == CLASS_HashSet)
#define ASSERT_HashSet(o)       DEBUG_ASSERT(((o)->h.cid == CLASS_HashSet))
#define TYPE_HashSet            CLASS_HashSet
#define NNTYPE_HashSet          TYPE_TONNTYPE(CLASS_HashSet)
#define CFLAG_HashSet           ((knh_flag_t)0)
#define FLAG_HashSet            KNH_FLAG_CF2OF(CFLAG_HashSet)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* DictIdx */
#define STRUCT_DictIdx          ((knh_struct_t)19)
#define CLASS_DictIdx           ((knh_class_t)19)
#define IS_bDictIdx(o)          ((o)->h.bcid == CLASS_DictIdx)
#ifndef DictIdx
#define DictIdx                 knh_DictIdx_t
#endif
#define IS_DictIdx(o)           ((o)->h.cid == CLASS_DictIdx)
#define ASSERT_DictIdx(o)       DEBUG_ASSERT(((o)->h.cid == CLASS_DictIdx))
#define TYPE_DictIdx            CLASS_DictIdx
#define NNTYPE_DictIdx          TYPE_TONNTYPE(CLASS_DictIdx)
#define CFLAG_DictIdx           ((knh_flag_t)KNH_FLAG_CF_PRIVATE)
#define FLAG_DictIdx            KNH_FLAG_CF2OF(CFLAG_DictIdx)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Class */
#define STRUCT_Class            ((knh_struct_t)20)
#define CLASS_Class             ((knh_class_t)20)
#define IS_bClass(o)            ((o)->h.bcid == CLASS_Class)
#ifndef Class
#define Class                   knh_Class_t
#endif
#define IS_Class(o)             ((o)->h.cid == CLASS_Class)
#define ASSERT_Class(o)         DEBUG_ASSERT(((o)->h.cid == CLASS_Class))
#define TYPE_Class              CLASS_Class
#define NNTYPE_Class            TYPE_TONNTYPE(CLASS_Class)
#define CFLAG_Class             ((knh_flag_t)0)
#define FLAG_Class              KNH_FLAG_CF2OF(CFLAG_Class)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* ClassStruct */
#define STRUCT_ClassStruct      ((knh_struct_t)21)
#define CLASS_ClassStruct       ((knh_class_t)21)
#define IS_bClassStruct(o)      ((o)->h.bcid == CLASS_ClassStruct)
#ifndef ClassStruct
#define ClassStruct             knh_ClassStruct_t
#endif
#define IS_ClassStruct(o)       ((o)->h.cid == CLASS_ClassStruct)
#define ASSERT_ClassStruct(o)   DEBUG_ASSERT(((o)->h.cid == CLASS_ClassStruct))
#define TYPE_ClassStruct        CLASS_ClassStruct
#define NNTYPE_ClassStruct      TYPE_TONNTYPE(CLASS_ClassStruct)
#define CFLAG_ClassStruct       ((knh_flag_t)KNH_FLAG_CF_PRIVATE)
#define FLAG_ClassStruct        KNH_FLAG_CF2OF(CFLAG_ClassStruct)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* MethodField */
#define STRUCT_MethodField      ((knh_struct_t)22)
#define CLASS_MethodField       ((knh_class_t)22)
#define IS_bMethodField(o)      ((o)->h.bcid == CLASS_MethodField)
#ifndef MethodField
#define MethodField             knh_MethodField_t
#endif
#define IS_MethodField(o)       ((o)->h.cid == CLASS_MethodField)
#define ASSERT_MethodField(o)   DEBUG_ASSERT(((o)->h.cid == CLASS_MethodField))
#define TYPE_MethodField        CLASS_MethodField
#define NNTYPE_MethodField      TYPE_TONNTYPE(CLASS_MethodField)
#define CFLAG_MethodField       ((knh_flag_t)KNH_FLAG_CF_PRIVATE)
#define FLAG_MethodField        KNH_FLAG_CF2OF(CFLAG_MethodField)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Method */
#define STRUCT_Method           ((knh_struct_t)23)
#define CLASS_Method            ((knh_class_t)23)
#define IS_bMethod(o)           ((o)->h.bcid == CLASS_Method)
#ifndef Method
#define Method                  knh_Method_t
#endif
#define IS_Method(o)            ((o)->h.cid == CLASS_Method)
#define ASSERT_Method(o)        DEBUG_ASSERT(((o)->h.cid == CLASS_Method))
#define TYPE_Method             CLASS_Method
#define NNTYPE_Method           TYPE_TONNTYPE(CLASS_Method)
#define CFLAG_Method            ((knh_flag_t)0)
#define FLAG_Method             KNH_FLAG_CF2OF(CFLAG_Method)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Mapper */
#define STRUCT_Mapper           ((knh_struct_t)24)
#define CLASS_Mapper            ((knh_class_t)24)
#define IS_bMapper(o)           ((o)->h.bcid == CLASS_Mapper)
#ifndef Mapper
#define Mapper                  knh_Mapper_t
#endif
#define IS_Mapper(o)            ((o)->h.cid == CLASS_Mapper)
#define ASSERT_Mapper(o)        DEBUG_ASSERT(((o)->h.cid == CLASS_Mapper))
#define TYPE_Mapper             CLASS_Mapper
#define NNTYPE_Mapper           TYPE_TONNTYPE(CLASS_Mapper)
#define CFLAG_Mapper            ((knh_flag_t)0)
#define FLAG_Mapper             KNH_FLAG_CF2OF(CFLAG_Mapper)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* ClassMap */
#define STRUCT_ClassMap         ((knh_struct_t)25)
#define CLASS_ClassMap          ((knh_class_t)25)
#define IS_bClassMap(o)         ((o)->h.bcid == CLASS_ClassMap)
#ifndef ClassMap
#define ClassMap                knh_ClassMap_t
#endif
#define IS_ClassMap(o)          ((o)->h.cid == CLASS_ClassMap)
#define ASSERT_ClassMap(o)      DEBUG_ASSERT(((o)->h.cid == CLASS_ClassMap))
#define TYPE_ClassMap           CLASS_ClassMap
#define NNTYPE_ClassMap         TYPE_TONNTYPE(CLASS_ClassMap)
#define CFLAG_ClassMap          ((knh_flag_t)KNH_FLAG_CF_PRIVATE)
#define FLAG_ClassMap           KNH_FLAG_CF2OF(CFLAG_ClassMap)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Closure */
#define STRUCT_Closure          ((knh_struct_t)26)
#define CLASS_Closure           ((knh_class_t)26)
#define IS_bClosure(o)          ((o)->h.bcid == CLASS_Closure)
#ifndef Closure
#define Closure                 knh_Closure_t
#endif
#define IS_Closure(o)           ((o)->h.cid == CLASS_Closure)
#define ASSERT_Closure(o)       DEBUG_ASSERT(((o)->h.cid == CLASS_Closure))
#define TYPE_Closure            CLASS_Closure
#define NNTYPE_Closure          TYPE_TONNTYPE(CLASS_Closure)
#define CFLAG_Closure           ((knh_flag_t)0)
#define FLAG_Closure            KNH_FLAG_CF2OF(CFLAG_Closure)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* AffineConv */
#define STRUCT_AffineConv       ((knh_struct_t)27)
#define CLASS_AffineConv        ((knh_class_t)27)
#define IS_bAffineConv(o)       ((o)->h.bcid == CLASS_AffineConv)
#ifndef AffineConv
#define AffineConv              knh_AffineConv_t
#endif
#define IS_AffineConv(o)        ((o)->h.cid == CLASS_AffineConv)
#define ASSERT_AffineConv(o)    DEBUG_ASSERT(((o)->h.cid == CLASS_AffineConv))
#define TYPE_AffineConv         CLASS_AffineConv
#define NNTYPE_AffineConv       TYPE_TONNTYPE(CLASS_AffineConv)
#define CFLAG_AffineConv        ((knh_flag_t)KNH_FLAG_CF_PRIVATE)
#define FLAG_AffineConv         KNH_FLAG_CF2OF(CFLAG_AffineConv)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Regex */
#define STRUCT_Regex            ((knh_struct_t)28)
#define CLASS_Regex             ((knh_class_t)28)
#define IS_bRegex(o)            ((o)->h.bcid == CLASS_Regex)
#ifndef Regex
#define Regex                   knh_Regex_t
#endif
#define IS_Regex(o)             ((o)->h.cid == CLASS_Regex)
#define ASSERT_Regex(o)         DEBUG_ASSERT(((o)->h.cid == CLASS_Regex))
#define TYPE_Regex              CLASS_Regex
#define NNTYPE_Regex            TYPE_TONNTYPE(CLASS_Regex)
#define CFLAG_Regex             ((knh_flag_t)KNH_FLAG_CF_IMMUTABLE)
#define FLAG_Regex              KNH_FLAG_CF2OF(CFLAG_Regex)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* BytesConv */
#define STRUCT_BytesConv        ((knh_struct_t)29)
#define CLASS_BytesConv         ((knh_class_t)29)
#define IS_bBytesConv(o)        ((o)->h.bcid == CLASS_BytesConv)
#ifndef BytesConv
#define BytesConv               knh_BytesConv_t
#endif
#define IS_BytesConv(o)         ((o)->h.cid == CLASS_BytesConv)
#define ASSERT_BytesConv(o)     DEBUG_ASSERT(((o)->h.cid == CLASS_BytesConv))
#define TYPE_BytesConv          CLASS_BytesConv
#define NNTYPE_BytesConv        TYPE_TONNTYPE(CLASS_BytesConv)
#define CFLAG_BytesConv         ((knh_flag_t)KNH_FLAG_CF_PRIVATE)
#define FLAG_BytesConv          KNH_FLAG_CF2OF(CFLAG_BytesConv)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* ClassSpec */
#define STRUCT_ClassSpec        ((knh_struct_t)30)
#define CLASS_ClassSpec         ((knh_class_t)30)
#define IS_bClassSpec(o)        ((o)->h.bcid == CLASS_ClassSpec)
#ifndef ClassSpec
#define ClassSpec               knh_ClassSpec_t
#endif
#define IS_ClassSpec(o)         ((o)->h.cid == CLASS_ClassSpec)
#define ASSERT_ClassSpec(o)     DEBUG_ASSERT(((o)->h.cid == CLASS_ClassSpec))
#define TYPE_ClassSpec          CLASS_ClassSpec
#define NNTYPE_ClassSpec        TYPE_TONNTYPE(CLASS_ClassSpec)
#define CFLAG_ClassSpec         ((knh_flag_t)KNH_FLAG_CF_PRIVATE)
#define FLAG_ClassSpec          KNH_FLAG_CF2OF(CFLAG_ClassSpec)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* InputStream */
#define STRUCT_InputStream      ((knh_struct_t)31)
#define CLASS_InputStream       ((knh_class_t)31)
#define IS_bInputStream(o)      ((o)->h.bcid == CLASS_InputStream)
#ifndef InputStream
#define InputStream             knh_InputStream_t
#endif
#define IS_InputStream(o)       ((o)->h.cid == CLASS_InputStream)
#define ASSERT_InputStream(o)   DEBUG_ASSERT(((o)->h.cid == CLASS_InputStream))
#define TYPE_InputStream        CLASS_InputStream
#define NNTYPE_InputStream      TYPE_TONNTYPE(CLASS_InputStream)
#define CFLAG_InputStream       ((knh_flag_t)0)
#define FLAG_InputStream        KNH_FLAG_CF2OF(CFLAG_InputStream)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* OutputStream */
#define STRUCT_OutputStream     ((knh_struct_t)32)
#define CLASS_OutputStream      ((knh_class_t)32)
#define IS_bOutputStream(o)     ((o)->h.bcid == CLASS_OutputStream)
#ifndef OutputStream
#define OutputStream            knh_OutputStream_t
#endif
#define IS_OutputStream(o)      ((o)->h.cid == CLASS_OutputStream)
#define ASSERT_OutputStream(o)  DEBUG_ASSERT(((o)->h.cid == CLASS_OutputStream))
#define TYPE_OutputStream       CLASS_OutputStream
#define NNTYPE_OutputStream     TYPE_TONNTYPE(CLASS_OutputStream)
#define CFLAG_OutputStream      ((knh_flag_t)0)
#define FLAG_OutputStream       KNH_FLAG_CF2OF(CFLAG_OutputStream)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Socket */
#define STRUCT_Socket           ((knh_struct_t)33)
#define CLASS_Socket            ((knh_class_t)33)
#define IS_bSocket(o)           ((o)->h.bcid == CLASS_Socket)
#ifndef Socket
#define Socket                  knh_Socket_t
#endif
#define IS_Socket(o)            ((o)->h.cid == CLASS_Socket)
#define ASSERT_Socket(o)        DEBUG_ASSERT(((o)->h.cid == CLASS_Socket))
#define TYPE_Socket             CLASS_Socket
#define NNTYPE_Socket           TYPE_TONNTYPE(CLASS_Socket)
#define CFLAG_Socket            ((knh_flag_t)0)
#define FLAG_Socket             KNH_FLAG_CF2OF(CFLAG_Socket)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Connection */
#define STRUCT_Connection       ((knh_struct_t)34)
#define CLASS_Connection        ((knh_class_t)34)
#define IS_bConnection(o)       ((o)->h.bcid == CLASS_Connection)
#ifndef Connection
#define Connection              knh_Connection_t
#endif
#define IS_Connection(o)        ((o)->h.cid == CLASS_Connection)
#define ASSERT_Connection(o)    DEBUG_ASSERT(((o)->h.cid == CLASS_Connection))
#define TYPE_Connection         CLASS_Connection
#define NNTYPE_Connection       TYPE_TONNTYPE(CLASS_Connection)
#define CFLAG_Connection        ((knh_flag_t)0)
#define FLAG_Connection         KNH_FLAG_CF2OF(CFLAG_Connection)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* ResultSet */
#define STRUCT_ResultSet        ((knh_struct_t)35)
#define CLASS_ResultSet         ((knh_class_t)35)
#define IS_bResultSet(o)        ((o)->h.bcid == CLASS_ResultSet)
#ifndef ResultSet
#define ResultSet               knh_ResultSet_t
#endif
#define IS_ResultSet(o)         ((o)->h.cid == CLASS_ResultSet)
#define ASSERT_ResultSet(o)     DEBUG_ASSERT(((o)->h.cid == CLASS_ResultSet))
#define TYPE_ResultSet          CLASS_ResultSet
#define NNTYPE_ResultSet        TYPE_TONNTYPE(CLASS_ResultSet)
#define CFLAG_ResultSet         ((knh_flag_t)0)
#define FLAG_ResultSet          KNH_FLAG_CF2OF(CFLAG_ResultSet)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Exception */
#define STRUCT_Exception        ((knh_struct_t)36)
#define CLASS_Exception         ((knh_class_t)36)
#define IS_bException(o)        ((o)->h.bcid == CLASS_Exception)
#ifndef Exception
#define Exception               knh_Exception_t
#endif
#define IS_Exception(o)         ((o)->h.cid == CLASS_Exception)
#define ASSERT_Exception(o)     DEBUG_ASSERT(((o)->h.cid == CLASS_Exception))
#define TYPE_Exception          CLASS_Exception
#define NNTYPE_Exception        TYPE_TONNTYPE(CLASS_Exception)
#define CFLAG_Exception         ((knh_flag_t)0)
#define FLAG_Exception          KNH_FLAG_CF2OF(CFLAG_Exception)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* ExceptionHandler */
#define STRUCT_ExceptionHandler ((knh_struct_t)37)
#define CLASS_ExceptionHandler  ((knh_class_t)37)
#define IS_bExceptionHandler(o) ((o)->h.bcid == CLASS_ExceptionHandler)
#ifndef ExceptionHandler
#define ExceptionHandler        knh_ExceptionHandler_t
#endif
#define IS_ExceptionHandler(o)  ((o)->h.cid == CLASS_ExceptionHandler)
#define ASSERT_ExceptionHandler(o) DEBUG_ASSERT(((o)->h.cid == CLASS_ExceptionHandler))
#define TYPE_ExceptionHandler   CLASS_ExceptionHandler
#define NNTYPE_ExceptionHandler TYPE_TONNTYPE(CLASS_ExceptionHandler)
#define CFLAG_ExceptionHandler  ((knh_flag_t)KNH_FLAG_CF_PRIVATE)
#define FLAG_ExceptionHandler   KNH_FLAG_CF2OF(CFLAG_ExceptionHandler)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Script */
#define STRUCT_Script           ((knh_struct_t)38)
#define CLASS_Script            ((knh_class_t)38)
#define IS_bScript(o)           ((o)->h.bcid == CLASS_Script)
#ifndef Script
#define Script                  knh_Script_t
#endif
#define IS_Script(o)            ((o)->h.cid == CLASS_Script)
#define ASSERT_Script(o)        DEBUG_ASSERT(((o)->h.cid == CLASS_Script))
#define TYPE_Script             CLASS_Script
#define NNTYPE_Script           TYPE_TONNTYPE(CLASS_Script)
#define CFLAG_Script            ((knh_flag_t)KNH_FLAG_CF_PRIVATE)
#define FLAG_Script             KNH_FLAG_CF2OF(CFLAG_Script)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* NameSpace */
#define STRUCT_NameSpace        ((knh_struct_t)39)
#define CLASS_NameSpace         ((knh_class_t)39)
#define IS_bNameSpace(o)        ((o)->h.bcid == CLASS_NameSpace)
#ifndef NameSpace
#define NameSpace               knh_NameSpace_t
#endif
#define IS_NameSpace(o)         ((o)->h.cid == CLASS_NameSpace)
#define ASSERT_NameSpace(o)     DEBUG_ASSERT(((o)->h.cid == CLASS_NameSpace))
#define TYPE_NameSpace          CLASS_NameSpace
#define NNTYPE_NameSpace        TYPE_TONNTYPE(CLASS_NameSpace)
#define CFLAG_NameSpace         ((knh_flag_t)KNH_FLAG_CF_PRIVATE)
#define FLAG_NameSpace          KNH_FLAG_CF2OF(CFLAG_NameSpace)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* System */
#define STRUCT_System           ((knh_struct_t)40)
#define CLASS_System            ((knh_class_t)40)
#define IS_bSystem(o)           ((o)->h.bcid == CLASS_System)
#ifndef System
#define System                  knh_System_t
#endif
#define IS_System(o)            ((o)->h.cid == CLASS_System)
#define ASSERT_System(o)        DEBUG_ASSERT(((o)->h.cid == CLASS_System))
#define TYPE_System             CLASS_System
#define NNTYPE_System           TYPE_TONNTYPE(CLASS_System)
#define CFLAG_System            ((knh_flag_t)KNH_FLAG_CF_SINGLETON)
#define FLAG_System             KNH_FLAG_CF2OF(CFLAG_System)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Context */
#define STRUCT_Context          ((knh_struct_t)41)
#define CLASS_Context           ((knh_class_t)41)
#define IS_bContext(o)          ((o)->h.bcid == CLASS_Context)
#ifndef Context
#define Context                 knh_Context_t
#endif
#define IS_Context(o)           ((o)->h.cid == CLASS_Context)
#define ASSERT_Context(o)       DEBUG_ASSERT(((o)->h.cid == CLASS_Context))
#define TYPE_Context            CLASS_Context
#define NNTYPE_Context          TYPE_TONNTYPE(CLASS_Context)
#define CFLAG_Context           ((knh_flag_t)0)
#define FLAG_Context            KNH_FLAG_CF2OF(CFLAG_Context)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Token */
#define STRUCT_Token            ((knh_struct_t)42)
#define CLASS_Token             ((knh_class_t)42)
#define IS_bToken(o)            ((o)->h.bcid == CLASS_Token)
#ifndef Token
#define Token                   knh_Token_t
#endif
#define IS_Token(o)             ((o)->h.cid == CLASS_Token)
#define ASSERT_Token(o)         DEBUG_ASSERT(((o)->h.cid == CLASS_Token))
#define TYPE_Token              CLASS_Token
#define NNTYPE_Token            TYPE_TONNTYPE(CLASS_Token)
#define CFLAG_Token             ((knh_flag_t)0)
#define FLAG_Token              KNH_FLAG_CF2OF(CFLAG_Token)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Stmt */
#define STRUCT_Stmt             ((knh_struct_t)43)
#define CLASS_Stmt              ((knh_class_t)43)
#define IS_bStmt(o)             ((o)->h.bcid == CLASS_Stmt)
#ifndef Stmt
#define Stmt                    knh_Stmt_t
#endif
#define IS_Stmt(o)              ((o)->h.cid == CLASS_Stmt)
#define ASSERT_Stmt(o)          DEBUG_ASSERT(((o)->h.cid == CLASS_Stmt))
#define TYPE_Stmt               CLASS_Stmt
#define NNTYPE_Stmt             TYPE_TONNTYPE(CLASS_Stmt)
#define CFLAG_Stmt              ((knh_flag_t)0)
#define FLAG_Stmt               KNH_FLAG_CF2OF(CFLAG_Stmt)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Asm */
#define STRUCT_Asm              ((knh_struct_t)44)
#define CLASS_Asm               ((knh_class_t)44)
#define IS_bAsm(o)              ((o)->h.bcid == CLASS_Asm)
#ifndef Asm
#define Asm                     knh_Asm_t
#endif
#define IS_Asm(o)               ((o)->h.cid == CLASS_Asm)
#define ASSERT_Asm(o)           DEBUG_ASSERT(((o)->h.cid == CLASS_Asm))
#define TYPE_Asm                CLASS_Asm
#define NNTYPE_Asm              TYPE_TONNTYPE(CLASS_Asm)
#define CFLAG_Asm               ((knh_flag_t)KNH_FLAG_CF_PRIVATE)
#define FLAG_Asm                KNH_FLAG_CF2OF(CFLAG_Asm)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* KLRCode */
#define STRUCT_KLRCode          ((knh_struct_t)45)
#define CLASS_KLRCode           ((knh_class_t)45)
#define IS_bKLRCode(o)          ((o)->h.bcid == CLASS_KLRCode)
#ifndef KLRCode
#define KLRCode                 knh_KLRCode_t
#endif
#define IS_KLRCode(o)           ((o)->h.cid == CLASS_KLRCode)
#define ASSERT_KLRCode(o)       DEBUG_ASSERT(((o)->h.cid == CLASS_KLRCode))
#define TYPE_KLRCode            CLASS_KLRCode
#define NNTYPE_KLRCode          TYPE_TONNTYPE(CLASS_KLRCode)
#define CFLAG_KLRCode           ((knh_flag_t)0)
#define FLAG_KLRCode            KNH_FLAG_CF2OF(CFLAG_KLRCode)

/* ------------------------------------------------------------------------ */
#define ACLASS_Int              CLASS_IArray
#define ATYPE_Int               CLASS_IArray
#define NNATYPE_Int             NNTYPE_cid(CLASS_IArray)
#define ACLASS_Float            CLASS_FArray
#define ATYPE_Float             CLASS_FArray
#define NNATYPE_Float           NNTYPE_cid(CLASS_FArray)

/* ======================================================================== */
/* [Array<X>] */
#define ACLASS_String           ((knh_class_t)(KNH_TCLASS_SIZE-(5+1)))
#define ATYPE_String            ACLASS_String
#define NNATYPE_String          NNTYPE_cid(ACLASS_String)

/* ======================================================================== */
/* [Iterator<X>] */
#define ICLASS_String           ((knh_class_t)(KNH_TCLASS_SIZE-(6+1)))
#define ITYPE_String            NNTYPE_cid(ICLASS_String)
#define NNITYPE_String          NNTYPE_cid(ICLASS_String)
#define ICLASS_Any1             ((knh_class_t)(KNH_TCLASS_SIZE-(7+1)))
#define ITYPE_Any1              NNTYPE_cid(ICLASS_Any1)
#define NNITYPE_Any1            NNTYPE_cid(ICLASS_Any1)
#define ICLASS_Int              ((knh_class_t)(KNH_TCLASS_SIZE-(8+1)))
#define ITYPE_Int               NNTYPE_cid(ICLASS_Int)
#define NNITYPE_Int             NNTYPE_cid(ICLASS_Int)
#define ICLASS_This             ((knh_class_t)(KNH_TCLASS_SIZE-(9+1)))
#define ITYPE_This              NNTYPE_cid(ICLASS_This)
#define NNITYPE_This            NNTYPE_cid(ICLASS_This)

/* ======================================================================== */
/* [Generics] */
#define CLASS_ArrayCmp          ((knh_class_t)(KNH_TCLASS_SIZE-(10+1)))
#define TYPE_ArrayCmp           CLASS_ArrayCmp
#define NNTYPE_ArrayCmp         NNTYPE_cid(CLASS_This)

/* ======================================================================== */
/* [Object:X] */
#define CLASS_String__urn       ((knh_class_t)(KNH_TCLASS_SIZE-(11+1)))
#define TYPE_String__urn        CLASS_String__urn
#define NNTYPE_String__urn      NNTYPE_cid(CLASS_String__urn)

/* ======================================================================== */
/* [tString] */
#define TSN_EMPTY               0
#define TS_EMPTY                        ((ctx)->share->tString[TSN_EMPTY])
#define TSN_TAB                 1
#define TS_TAB                          ((ctx)->share->tString[TSN_TAB])
#define TSN_LF                  2
#define TS_LF                           ((ctx)->share->tString[TSN_LF])
#define TSN_SPC                 3
#define TS_SPC                          ((ctx)->share->tString[TSN_SPC])
#define TSN_EOL                 4
#define TS_EOL                          ((ctx)->share->tString[TSN_EOL])
#define TSN_BEGIN               5
#define TS_BEGIN                        ((ctx)->share->tString[TSN_BEGIN])
#define TSN_END                 6
#define TS_END                          ((ctx)->share->tString[TSN_END])
#define TSN_void                7
#define TS_void                         ((ctx)->share->tString[TSN_void])
#define TSN_true                8
#define TS_true                         ((ctx)->share->tString[TSN_true])
#define TSN_false               9
#define TS_false                        ((ctx)->share->tString[TSN_false])
#define TSN_null                10
#define TS_null                         ((ctx)->share->tString[TSN_null])
#define TSN_main                11
#define TS_main                         ((ctx)->share->tString[TSN_main])
#define TSN_ENCODING            12
#define TS_ENCODING                     ((ctx)->share->tString[TSN_ENCODING])
#define TSN_DEVNULL             13
#define TS_DEVNULL                      ((ctx)->share->tString[TSN_DEVNULL])
#define TSN_DEVSTDIN            14
#define TS_DEVSTDIN                     ((ctx)->share->tString[TSN_DEVSTDIN])
#define TSN_DEVSTDERR           15
#define TS_DEVSTDERR                    ((ctx)->share->tString[TSN_DEVSTDERR])
#define TSN_DEVSTDOUT           16
#define TS_DEVSTDOUT                    ((ctx)->share->tString[TSN_DEVSTDOUT])
#define TSN_ATlabel             17
#define TS_ATlabel                      ((ctx)->share->tString[TSN_ATlabel])
#define TSN_SecurityException   18
#define TS_SecurityException            ((ctx)->share->tString[TSN_SecurityException])
#define TSN_AssertionException  19
#define TS_AssertionException           ((ctx)->share->tString[TSN_AssertionException])
#define TSN_LP                  20
#define TS_LP                           ((ctx)->share->tString[TSN_LP])
#define TSN_RP                  21
#define TS_RP                           ((ctx)->share->tString[TSN_RP])
#define TSN_LB                  22
#define TS_LB                           ((ctx)->share->tString[TSN_LB])
#define TSN_RB                  23
#define TS_RB                           ((ctx)->share->tString[TSN_RB])
#define TSN_LS                  24
#define TS_LS                           ((ctx)->share->tString[TSN_LS])
#define TSN_RS                  25
#define TS_RS                           ((ctx)->share->tString[TSN_RS])
#define KNH_TSTRING_SIZE        26

/* ======================================================================== */
/* [field] */
#define FIELDN_                         ((knh_fieldn_t)0)
#define METHODN_                        ((knh_methodn_t)0)
#define METHODN__                       ((knh_methodn_t)0|KNH_FLAG_MN_MOVTEXT)
#define METHODN_get                     ((knh_methodn_t)0|KNH_FLAG_MN_GETTER)
#define METHODN_set                     ((knh_methodn_t)0|KNH_FLAG_MN_SETTER)
#define FIELDN_2D                       ((knh_fieldn_t)1)
#define METHODN_2D                      ((knh_methodn_t)1)
#define METHODN__2D                     ((knh_methodn_t)1|KNH_FLAG_MN_MOVTEXT)
#define METHODN_get2D                   ((knh_methodn_t)1|KNH_FLAG_MN_GETTER)
#define METHODN_set2D                   ((knh_methodn_t)1|KNH_FLAG_MN_SETTER)
#define FIELDN_3D                       ((knh_fieldn_t)2)
#define METHODN_3D                      ((knh_methodn_t)2)
#define METHODN__3D                     ((knh_methodn_t)2|KNH_FLAG_MN_MOVTEXT)
#define METHODN_get3D                   ((knh_methodn_t)2|KNH_FLAG_MN_GETTER)
#define METHODN_set3D                   ((knh_methodn_t)2|KNH_FLAG_MN_SETTER)
#define FIELDN_GLOBAL                   ((knh_fieldn_t)3)
#define METHODN_GLOBAL                  ((knh_methodn_t)3)
#define METHODN__GLOBAL                 ((knh_methodn_t)3|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getGLOBAL               ((knh_methodn_t)3|KNH_FLAG_MN_GETTER)
#define METHODN_setGLOBAL               ((knh_methodn_t)3|KNH_FLAG_MN_SETTER)
#define FIELDN_a                        ((knh_fieldn_t)4)
#define METHODN_a                       ((knh_methodn_t)4)
#define METHODN__a                      ((knh_methodn_t)4|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getA                    ((knh_methodn_t)4|KNH_FLAG_MN_GETTER)
#define METHODN_setA                    ((knh_methodn_t)4|KNH_FLAG_MN_SETTER)
#define FIELDN_add                      ((knh_fieldn_t)5)
#define METHODN_add                     ((knh_methodn_t)5)
#define METHODN__add                    ((knh_methodn_t)5|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getAdd                  ((knh_methodn_t)5|KNH_FLAG_MN_GETTER)
#define METHODN_setAdd                  ((knh_methodn_t)5|KNH_FLAG_MN_SETTER)
#define FIELDN_add__fast                ((knh_fieldn_t)6)
#define METHODN_add__fast               ((knh_methodn_t)6)
#define METHODN__add__fast              ((knh_methodn_t)6|KNH_FLAG_MN_MOVTEXT)
#define FIELDN_addHistory               ((knh_fieldn_t)7)
#define METHODN_addHistory              ((knh_methodn_t)7)
#define METHODN__addHistory             ((knh_methodn_t)7|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getAddHistory           ((knh_methodn_t)7|KNH_FLAG_MN_GETTER)
#define METHODN_setAddHistory           ((knh_methodn_t)7|KNH_FLAG_MN_SETTER)
#define FIELDN_all                      ((knh_fieldn_t)8)
#define METHODN_all                     ((knh_methodn_t)8)
#define METHODN__all                    ((knh_methodn_t)8|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getAll                  ((knh_methodn_t)8|KNH_FLAG_MN_GETTER)
#define METHODN_setAll                  ((knh_methodn_t)8|KNH_FLAG_MN_SETTER)
#define FIELDN_autoFlush                ((knh_fieldn_t)9)
#define METHODN_autoFlush               ((knh_methodn_t)9)
#define METHODN__autoFlush              ((knh_methodn_t)9|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getAutoFlush            ((knh_methodn_t)9|KNH_FLAG_MN_GETTER)
#define METHODN_setAutoFlush            ((knh_methodn_t)9|KNH_FLAG_MN_SETTER)
#define FIELDN_b                        ((knh_fieldn_t)10)
#define METHODN_b                       ((knh_methodn_t)10)
#define METHODN__b                      ((knh_methodn_t)10|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getB                    ((knh_methodn_t)10|KNH_FLAG_MN_GETTER)
#define METHODN_setB                    ((knh_methodn_t)10|KNH_FLAG_MN_SETTER)
#define FIELDN_bag                      ((knh_fieldn_t)11)
#define METHODN_bag                     ((knh_methodn_t)11)
#define METHODN__bag                    ((knh_methodn_t)11|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getBag                  ((knh_methodn_t)11|KNH_FLAG_MN_GETTER)
#define METHODN_setBag                  ((knh_methodn_t)11|KNH_FLAG_MN_SETTER)
#define FIELDN_base                     ((knh_fieldn_t)12)
#define METHODN_base                    ((knh_methodn_t)12)
#define METHODN__base                   ((knh_methodn_t)12|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getBase                 ((knh_methodn_t)12|KNH_FLAG_MN_GETTER)
#define METHODN_setBase                 ((knh_methodn_t)12|KNH_FLAG_MN_SETTER)
#define FIELDN_bits                     ((knh_fieldn_t)13)
#define METHODN_bits                    ((knh_methodn_t)13)
#define METHODN__bits                   ((knh_methodn_t)13|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getBits                 ((knh_methodn_t)13|KNH_FLAG_MN_GETTER)
#define METHODN_setBits                 ((knh_methodn_t)13|KNH_FLAG_MN_SETTER)
#define FIELDN_buf                      ((knh_fieldn_t)14)
#define METHODN_buf                     ((knh_methodn_t)14)
#define METHODN__buf                    ((knh_methodn_t)14|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getBuf                  ((knh_methodn_t)14|KNH_FLAG_MN_GETTER)
#define METHODN_setBuf                  ((knh_methodn_t)14|KNH_FLAG_MN_SETTER)
#define FIELDN_byte                     ((knh_fieldn_t)15)
#define METHODN_byte                    ((knh_methodn_t)15)
#define METHODN__byte                   ((knh_methodn_t)15|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getByte                 ((knh_methodn_t)15|KNH_FLAG_MN_GETTER)
#define METHODN_setByte                 ((knh_methodn_t)15|KNH_FLAG_MN_SETTER)
#define FIELDN_bytes                    ((knh_fieldn_t)16)
#define METHODN_bytes                   ((knh_methodn_t)16)
#define METHODN__bytes                  ((knh_methodn_t)16|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getBytes                ((knh_methodn_t)16|KNH_FLAG_MN_GETTER)
#define METHODN_setBytes                ((knh_methodn_t)16|KNH_FLAG_MN_SETTER)
#define FIELDN_c                        ((knh_fieldn_t)17)
#define METHODN_c                       ((knh_methodn_t)17)
#define METHODN__c                      ((knh_methodn_t)17|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getC                    ((knh_methodn_t)17|KNH_FLAG_MN_GETTER)
#define METHODN_setC                    ((knh_methodn_t)17|KNH_FLAG_MN_SETTER)
#define FIELDN_callcc                   ((knh_fieldn_t)18)
#define METHODN_callcc                  ((knh_methodn_t)18)
#define METHODN__callcc                 ((knh_methodn_t)18|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getCallcc               ((knh_methodn_t)18|KNH_FLAG_MN_GETTER)
#define METHODN_setCallcc               ((knh_methodn_t)18|KNH_FLAG_MN_SETTER)
#define FIELDN_ch                       ((knh_fieldn_t)19)
#define METHODN_ch                      ((knh_methodn_t)19)
#define METHODN__ch                     ((knh_methodn_t)19|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getCh                   ((knh_methodn_t)19|KNH_FLAG_MN_GETTER)
#define METHODN_setCh                   ((knh_methodn_t)19|KNH_FLAG_MN_SETTER)
#define FIELDN_changeChannel            ((knh_fieldn_t)20)
#define METHODN_changeChannel           ((knh_methodn_t)20)
#define METHODN__changeChannel          ((knh_methodn_t)20|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getChangeChannel        ((knh_methodn_t)20|KNH_FLAG_MN_GETTER)
#define METHODN_setChangeChannel        ((knh_methodn_t)20|KNH_FLAG_MN_SETTER)
#define FIELDN_char                     ((knh_fieldn_t)21)
#define METHODN_char                    ((knh_methodn_t)21)
#define METHODN__char                   ((knh_methodn_t)21|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getChar                 ((knh_methodn_t)21|KNH_FLAG_MN_GETTER)
#define METHODN_setChar                 ((knh_methodn_t)21|KNH_FLAG_MN_SETTER)
#define FIELDN_class                    ((knh_fieldn_t)22)
#define METHODN_class                   ((knh_methodn_t)22)
#define METHODN__class                  ((knh_methodn_t)22|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getClass                ((knh_methodn_t)22|KNH_FLAG_MN_GETTER)
#define METHODN_setClass                ((knh_methodn_t)22|KNH_FLAG_MN_SETTER)
#define FIELDN_clear                    ((knh_fieldn_t)23)
#define METHODN_clear                   ((knh_methodn_t)23)
#define METHODN__clear                  ((knh_methodn_t)23|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getClear                ((knh_methodn_t)23|KNH_FLAG_MN_GETTER)
#define METHODN_setClear                ((knh_methodn_t)23|KNH_FLAG_MN_SETTER)
#define FIELDN_close                    ((knh_fieldn_t)24)
#define METHODN_close                   ((knh_methodn_t)24)
#define METHODN__close                  ((knh_methodn_t)24|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getClose                ((knh_methodn_t)24|KNH_FLAG_MN_GETTER)
#define METHODN_setClose                ((knh_methodn_t)24|KNH_FLAG_MN_SETTER)
#define FIELDN_concat                   ((knh_fieldn_t)25)
#define METHODN_concat                  ((knh_methodn_t)25)
#define METHODN__concat                 ((knh_methodn_t)25|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getConcat               ((knh_methodn_t)25|KNH_FLAG_MN_GETTER)
#define METHODN_setConcat               ((knh_methodn_t)25|KNH_FLAG_MN_SETTER)
#define FIELDN_const                    ((knh_fieldn_t)26)
#define METHODN_const                   ((knh_methodn_t)26)
#define METHODN__const                  ((knh_methodn_t)26|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getConst                ((knh_methodn_t)26|KNH_FLAG_MN_GETTER)
#define METHODN_setConst                ((knh_methodn_t)26|KNH_FLAG_MN_SETTER)
#define FIELDN_copy                     ((knh_fieldn_t)27)
#define METHODN_copy                    ((knh_methodn_t)27)
#define METHODN__copy                   ((knh_methodn_t)27|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getCopy                 ((knh_methodn_t)27|KNH_FLAG_MN_GETTER)
#define METHODN_setCopy                 ((knh_methodn_t)27|KNH_FLAG_MN_SETTER)
#define FIELDN_d                        ((knh_fieldn_t)28)
#define METHODN_d                       ((knh_methodn_t)28)
#define METHODN__d                      ((knh_methodn_t)28|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getD                    ((knh_methodn_t)28|KNH_FLAG_MN_GETTER)
#define METHODN_setD                    ((knh_methodn_t)28|KNH_FLAG_MN_SETTER)
#define FIELDN_debug                    ((knh_fieldn_t)29)
#define METHODN_debug                   ((knh_methodn_t)29)
#define METHODN__debug                  ((knh_methodn_t)29|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getDebug                ((knh_methodn_t)29|KNH_FLAG_MN_GETTER)
#define METHODN_setDebug                ((knh_methodn_t)29|KNH_FLAG_MN_SETTER)
#define FIELDN_default                  ((knh_fieldn_t)30)
#define METHODN_default                 ((knh_methodn_t)30)
#define METHODN__default                ((knh_methodn_t)30|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getDefault              ((knh_methodn_t)30|KNH_FLAG_MN_GETTER)
#define METHODN_setDefault              ((knh_methodn_t)30|KNH_FLAG_MN_SETTER)
#define FIELDN_defined                  ((knh_fieldn_t)31)
#define METHODN_defined                 ((knh_methodn_t)31)
#define METHODN__defined                ((knh_methodn_t)31|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getDefined              ((knh_methodn_t)31|KNH_FLAG_MN_GETTER)
#define METHODN_setDefined              ((knh_methodn_t)31|KNH_FLAG_MN_SETTER)
#define FIELDN_delegate                 ((knh_fieldn_t)32)
#define METHODN_delegate                ((knh_methodn_t)32)
#define METHODN__delegate               ((knh_methodn_t)32|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getDelegate             ((knh_methodn_t)32|KNH_FLAG_MN_GETTER)
#define METHODN_setDelegate             ((knh_methodn_t)32|KNH_FLAG_MN_SETTER)
#define FIELDN_delim                    ((knh_fieldn_t)33)
#define METHODN_delim                   ((knh_methodn_t)33)
#define METHODN__delim                  ((knh_methodn_t)33|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getDelim                ((knh_methodn_t)33|KNH_FLAG_MN_GETTER)
#define METHODN_setDelim                ((knh_methodn_t)33|KNH_FLAG_MN_SETTER)
#define FIELDN_domain                   ((knh_fieldn_t)34)
#define METHODN_domain                  ((knh_methodn_t)34)
#define METHODN__domain                 ((knh_methodn_t)34|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getDomain               ((knh_methodn_t)34|KNH_FLAG_MN_GETTER)
#define METHODN_setDomain               ((knh_methodn_t)34|KNH_FLAG_MN_SETTER)
#define FIELDN_dump                     ((knh_fieldn_t)35)
#define METHODN_dump                    ((knh_methodn_t)35)
#define METHODN__dump                   ((knh_methodn_t)35|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getDump                 ((knh_methodn_t)35|KNH_FLAG_MN_GETTER)
#define METHODN_setDump                 ((knh_methodn_t)35|KNH_FLAG_MN_SETTER)
#define FIELDN_e                        ((knh_fieldn_t)36)
#define METHODN_e                       ((knh_methodn_t)36)
#define METHODN__e                      ((knh_methodn_t)36|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getE                    ((knh_methodn_t)36|KNH_FLAG_MN_GETTER)
#define METHODN_setE                    ((knh_methodn_t)36|KNH_FLAG_MN_SETTER)
#define FIELDN_empty                    ((knh_fieldn_t)37)
#define METHODN_empty                   ((knh_methodn_t)37)
#define METHODN__empty                  ((knh_methodn_t)37|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getEmpty                ((knh_methodn_t)37|KNH_FLAG_MN_GETTER)
#define METHODN_setEmpty                ((knh_methodn_t)37|KNH_FLAG_MN_SETTER)
#define FIELDN_enc                      ((knh_fieldn_t)38)
#define METHODN_enc                     ((knh_methodn_t)38)
#define METHODN__enc                    ((knh_methodn_t)38|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getEnc                  ((knh_methodn_t)38|KNH_FLAG_MN_GETTER)
#define METHODN_setEnc                  ((knh_methodn_t)38|KNH_FLAG_MN_SETTER)
#define FIELDN_encoding                 ((knh_fieldn_t)39)
#define METHODN_encoding                ((knh_methodn_t)39)
#define METHODN__encoding               ((knh_methodn_t)39|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getEncoding             ((knh_methodn_t)39|KNH_FLAG_MN_GETTER)
#define METHODN_setEncoding             ((knh_methodn_t)39|KNH_FLAG_MN_SETTER)
#define FIELDN_endsWith                 ((knh_fieldn_t)40)
#define METHODN_endsWith                ((knh_methodn_t)40)
#define METHODN__endsWith               ((knh_methodn_t)40|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getEndsWith             ((knh_methodn_t)40|KNH_FLAG_MN_GETTER)
#define METHODN_setEndsWith             ((knh_methodn_t)40|KNH_FLAG_MN_SETTER)
#define FIELDN_endsWith__IgnoreCase     ((knh_fieldn_t)41)
#define METHODN_endsWith__IgnoreCase    ((knh_methodn_t)41)
#define METHODN__endsWith__IgnoreCase   ((knh_methodn_t)41|KNH_FLAG_MN_MOVTEXT)
#define FIELDN_equals                   ((knh_fieldn_t)42)
#define METHODN_equals                  ((knh_methodn_t)42)
#define METHODN__equals                 ((knh_methodn_t)42|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getEquals               ((knh_methodn_t)42|KNH_FLAG_MN_GETTER)
#define METHODN_setEquals               ((knh_methodn_t)42|KNH_FLAG_MN_SETTER)
#define FIELDN_equals__IgnoreCase       ((knh_fieldn_t)43)
#define METHODN_equals__IgnoreCase      ((knh_methodn_t)43)
#define METHODN__equals__IgnoreCase     ((knh_methodn_t)43|KNH_FLAG_MN_MOVTEXT)
#define FIELDN_err                      ((knh_fieldn_t)44)
#define METHODN_err                     ((knh_methodn_t)44)
#define METHODN__err                    ((knh_methodn_t)44|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getErr                  ((knh_methodn_t)44|KNH_FLAG_MN_GETTER)
#define METHODN_setErr                  ((knh_methodn_t)44|KNH_FLAG_MN_SETTER)
#define FIELDN_eval                     ((knh_fieldn_t)45)
#define METHODN_eval                    ((knh_methodn_t)45)
#define METHODN__eval                   ((knh_methodn_t)45|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getEval                 ((knh_methodn_t)45|KNH_FLAG_MN_GETTER)
#define METHODN_setEval                 ((knh_methodn_t)45|KNH_FLAG_MN_SETTER)
#define FIELDN_exec                     ((knh_fieldn_t)46)
#define METHODN_exec                    ((knh_methodn_t)46)
#define METHODN__exec                   ((knh_methodn_t)46|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getExec                 ((knh_methodn_t)46|KNH_FLAG_MN_GETTER)
#define METHODN_setExec                 ((knh_methodn_t)46|KNH_FLAG_MN_SETTER)
#define FIELDN_exit                     ((knh_fieldn_t)47)
#define METHODN_exit                    ((knh_methodn_t)47)
#define METHODN__exit                   ((knh_methodn_t)47|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getExit                 ((knh_methodn_t)47|KNH_FLAG_MN_GETTER)
#define METHODN_setExit                 ((knh_methodn_t)47|KNH_FLAG_MN_SETTER)
#define FIELDN_f                        ((knh_fieldn_t)48)
#define METHODN_f                       ((knh_methodn_t)48)
#define METHODN__f                      ((knh_methodn_t)48|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getF                    ((knh_methodn_t)48|KNH_FLAG_MN_GETTER)
#define METHODN_setF                    ((knh_methodn_t)48|KNH_FLAG_MN_SETTER)
#define FIELDN_file                     ((knh_fieldn_t)49)
#define METHODN_file                    ((knh_methodn_t)49)
#define METHODN__file                   ((knh_methodn_t)49|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getFile                 ((knh_methodn_t)49|KNH_FLAG_MN_GETTER)
#define METHODN_setFile                 ((knh_methodn_t)49|KNH_FLAG_MN_SETTER)
#define FIELDN_filename                 ((knh_fieldn_t)50)
#define METHODN_filename                ((knh_methodn_t)50)
#define METHODN__filename               ((knh_methodn_t)50|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getFilename             ((knh_methodn_t)50|KNH_FLAG_MN_GETTER)
#define METHODN_setFilename             ((knh_methodn_t)50|KNH_FLAG_MN_SETTER)
#define FIELDN_float                    ((knh_fieldn_t)51)
#define METHODN_float                   ((knh_methodn_t)51)
#define METHODN__float                  ((knh_methodn_t)51|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getFloat                ((knh_methodn_t)51|KNH_FLAG_MN_GETTER)
#define METHODN_setFloat                ((knh_methodn_t)51|KNH_FLAG_MN_SETTER)
#define FIELDN_floatToIntBits           ((knh_fieldn_t)52)
#define METHODN_floatToIntBits          ((knh_methodn_t)52)
#define METHODN__floatToIntBits         ((knh_methodn_t)52|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getFloatToIntBits       ((knh_methodn_t)52|KNH_FLAG_MN_GETTER)
#define METHODN_setFloatToIntBits       ((knh_methodn_t)52|KNH_FLAG_MN_SETTER)
#define FIELDN_flush                    ((knh_fieldn_t)53)
#define METHODN_flush                   ((knh_methodn_t)53)
#define METHODN__flush                  ((knh_methodn_t)53|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getFlush                ((knh_methodn_t)53|KNH_FLAG_MN_GETTER)
#define METHODN_setFlush                ((knh_methodn_t)53|KNH_FLAG_MN_SETTER)
#define FIELDN_format                   ((knh_fieldn_t)54)
#define METHODN_format                  ((knh_methodn_t)54)
#define METHODN__format                 ((knh_methodn_t)54|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getFormat               ((knh_methodn_t)54|KNH_FLAG_MN_GETTER)
#define METHODN_setFormat               ((knh_methodn_t)54|KNH_FLAG_MN_SETTER)
#define FIELDN_formatted                ((knh_fieldn_t)55)
#define METHODN_formatted               ((knh_methodn_t)55)
#define METHODN__formatted              ((knh_methodn_t)55|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getFormatted            ((knh_methodn_t)55|KNH_FLAG_MN_GETTER)
#define METHODN_setFormatted            ((knh_methodn_t)55|KNH_FLAG_MN_SETTER)
#define FIELDN_funcname                 ((knh_fieldn_t)56)
#define METHODN_funcname                ((knh_methodn_t)56)
#define METHODN__funcname               ((knh_methodn_t)56|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getFuncname             ((knh_methodn_t)56|KNH_FLAG_MN_GETTER)
#define METHODN_setFuncname             ((knh_methodn_t)56|KNH_FLAG_MN_SETTER)
#define FIELDN_g                        ((knh_fieldn_t)57)
#define METHODN_g                       ((knh_methodn_t)57)
#define METHODN__g                      ((knh_methodn_t)57|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getG                    ((knh_methodn_t)57|KNH_FLAG_MN_GETTER)
#define METHODN_setG                    ((knh_methodn_t)57|KNH_FLAG_MN_SETTER)
#define FIELDN_gc                       ((knh_fieldn_t)58)
#define METHODN_gc                      ((knh_methodn_t)58)
#define METHODN__gc                     ((knh_methodn_t)58|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getGc                   ((knh_methodn_t)58|KNH_FLAG_MN_GETTER)
#define METHODN_setGc                   ((knh_methodn_t)58|KNH_FLAG_MN_SETTER)
#define FIELDN_h                        ((knh_fieldn_t)59)
#define METHODN_h                       ((knh_methodn_t)59)
#define METHODN__h                      ((knh_methodn_t)59|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getH                    ((knh_methodn_t)59|KNH_FLAG_MN_GETTER)
#define METHODN_setH                    ((knh_methodn_t)59|KNH_FLAG_MN_SETTER)
#define FIELDN_hasDir                   ((knh_fieldn_t)60)
#define METHODN_hasDir                  ((knh_methodn_t)60)
#define METHODN__hasDir                 ((knh_methodn_t)60|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getHasDir               ((knh_methodn_t)60|KNH_FLAG_MN_GETTER)
#define METHODN_setHasDir               ((knh_methodn_t)60|KNH_FLAG_MN_SETTER)
#define FIELDN_hasFile                  ((knh_fieldn_t)61)
#define METHODN_hasFile                 ((knh_methodn_t)61)
#define METHODN__hasFile                ((knh_methodn_t)61|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getHasFile              ((knh_methodn_t)61|KNH_FLAG_MN_GETTER)
#define METHODN_setHasFile              ((knh_methodn_t)61|KNH_FLAG_MN_SETTER)
#define FIELDN_hook                     ((knh_fieldn_t)62)
#define METHODN_hook                    ((knh_methodn_t)62)
#define METHODN__hook                   ((knh_methodn_t)62|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getHook                 ((knh_methodn_t)62|KNH_FLAG_MN_GETTER)
#define METHODN_setHook                 ((knh_methodn_t)62|KNH_FLAG_MN_SETTER)
#define FIELDN_host                     ((knh_fieldn_t)63)
#define METHODN_host                    ((knh_methodn_t)63)
#define METHODN__host                   ((knh_methodn_t)63|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getHost                 ((knh_methodn_t)63|KNH_FLAG_MN_GETTER)
#define METHODN_setHost                 ((knh_methodn_t)63|KNH_FLAG_MN_SETTER)
#define FIELDN_i                        ((knh_fieldn_t)64)
#define METHODN_i                       ((knh_methodn_t)64)
#define METHODN__i                      ((knh_methodn_t)64|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getI                    ((knh_methodn_t)64|KNH_FLAG_MN_GETTER)
#define METHODN_setI                    ((knh_methodn_t)64|KNH_FLAG_MN_SETTER)
#define FIELDN_in                       ((knh_fieldn_t)65)
#define METHODN_in                      ((knh_methodn_t)65)
#define METHODN__in                     ((knh_methodn_t)65|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIn                   ((knh_methodn_t)65|KNH_FLAG_MN_GETTER)
#define METHODN_setIn                   ((knh_methodn_t)65|KNH_FLAG_MN_SETTER)
#define FIELDN_index                    ((knh_fieldn_t)66)
#define METHODN_index                   ((knh_methodn_t)66)
#define METHODN__index                  ((knh_methodn_t)66|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIndex                ((knh_methodn_t)66|KNH_FLAG_MN_GETTER)
#define METHODN_setIndex                ((knh_methodn_t)66|KNH_FLAG_MN_SETTER)
#define FIELDN_indexOf                  ((knh_fieldn_t)67)
#define METHODN_indexOf                 ((knh_methodn_t)67)
#define METHODN__indexOf                ((knh_methodn_t)67|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIndexOf              ((knh_methodn_t)67|KNH_FLAG_MN_GETTER)
#define METHODN_setIndexOf              ((knh_methodn_t)67|KNH_FLAG_MN_SETTER)
#define FIELDN_indexOf__IgnoreCase      ((knh_fieldn_t)68)
#define METHODN_indexOf__IgnoreCase     ((knh_methodn_t)68)
#define METHODN__indexOf__IgnoreCase    ((knh_methodn_t)68|KNH_FLAG_MN_MOVTEXT)
#define FIELDN_init                     ((knh_fieldn_t)69)
#define METHODN_init                    ((knh_methodn_t)69)
#define METHODN__init                   ((knh_methodn_t)69|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getInit                 ((knh_methodn_t)69|KNH_FLAG_MN_GETTER)
#define METHODN_setInit                 ((knh_methodn_t)69|KNH_FLAG_MN_SETTER)
#define FIELDN_inputStream              ((knh_fieldn_t)70)
#define METHODN_inputStream             ((knh_methodn_t)70)
#define METHODN__inputStream            ((knh_methodn_t)70|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getInputStream          ((knh_methodn_t)70|KNH_FLAG_MN_GETTER)
#define METHODN_setInputStream          ((knh_methodn_t)70|KNH_FLAG_MN_SETTER)
#define FIELDN_insert                   ((knh_fieldn_t)71)
#define METHODN_insert                  ((knh_methodn_t)71)
#define METHODN__insert                 ((knh_methodn_t)71|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getInsert               ((knh_methodn_t)71|KNH_FLAG_MN_GETTER)
#define METHODN_setInsert               ((knh_methodn_t)71|KNH_FLAG_MN_SETTER)
#define FIELDN_int                      ((knh_fieldn_t)72)
#define METHODN_int                     ((knh_methodn_t)72)
#define METHODN__int                    ((knh_methodn_t)72|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getInt                  ((knh_methodn_t)72|KNH_FLAG_MN_GETTER)
#define METHODN_setInt                  ((knh_methodn_t)72|KNH_FLAG_MN_SETTER)
#define FIELDN_intToFloatBits           ((knh_fieldn_t)73)
#define METHODN_intToFloatBits          ((knh_methodn_t)73)
#define METHODN__intToFloatBits         ((knh_methodn_t)73|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIntToFloatBits       ((knh_methodn_t)73|KNH_FLAG_MN_GETTER)
#define METHODN_setIntToFloatBits       ((knh_methodn_t)73|KNH_FLAG_MN_SETTER)
#define FIELDN_invoke                   ((knh_fieldn_t)74)
#define METHODN_invoke                  ((knh_methodn_t)74)
#define METHODN__invoke                 ((knh_methodn_t)74|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getInvoke               ((knh_methodn_t)74|KNH_FLAG_MN_GETTER)
#define METHODN_setInvoke               ((knh_methodn_t)74|KNH_FLAG_MN_SETTER)
#define FIELDN_isAbstract               ((knh_fieldn_t)75)
#define METHODN_isAbstract              ((knh_methodn_t)75)
#define METHODN__isAbstract             ((knh_methodn_t)75|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsAbstract           ((knh_methodn_t)75|KNH_FLAG_MN_GETTER)
#define METHODN_setIsAbstract           ((knh_methodn_t)75|KNH_FLAG_MN_SETTER)
#define FIELDN_isAspect                 ((knh_fieldn_t)76)
#define METHODN_isAspect                ((knh_methodn_t)76)
#define METHODN__isAspect               ((knh_methodn_t)76|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsAspect             ((knh_methodn_t)76|KNH_FLAG_MN_GETTER)
#define METHODN_setIsAspect             ((knh_methodn_t)76|KNH_FLAG_MN_SETTER)
#define FIELDN_isAutoFlush              ((knh_fieldn_t)77)
#define METHODN_isAutoFlush             ((knh_methodn_t)77)
#define METHODN__isAutoFlush            ((knh_methodn_t)77|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsAutoFlush          ((knh_methodn_t)77|KNH_FLAG_MN_GETTER)
#define METHODN_setIsAutoFlush          ((knh_methodn_t)77|KNH_FLAG_MN_SETTER)
#define FIELDN_isClosed                 ((knh_fieldn_t)78)
#define METHODN_isClosed                ((knh_methodn_t)78)
#define METHODN__isClosed               ((knh_methodn_t)78|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsClosed             ((knh_methodn_t)78|KNH_FLAG_MN_GETTER)
#define METHODN_setIsClosed             ((knh_methodn_t)78|KNH_FLAG_MN_SETTER)
#define FIELDN_isConst                  ((knh_fieldn_t)79)
#define METHODN_isConst                 ((knh_methodn_t)79)
#define METHODN__isConst                ((knh_methodn_t)79|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsConst              ((knh_methodn_t)79|KNH_FLAG_MN_GETTER)
#define METHODN_setIsConst              ((knh_methodn_t)79|KNH_FLAG_MN_SETTER)
#define FIELDN_isDebug                  ((knh_fieldn_t)80)
#define METHODN_isDebug                 ((knh_methodn_t)80)
#define METHODN__isDebug                ((knh_methodn_t)80|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsDebug              ((knh_methodn_t)80|KNH_FLAG_MN_GETTER)
#define METHODN_setIsDebug              ((knh_methodn_t)80|KNH_FLAG_MN_SETTER)
#define FIELDN_isDerived                ((knh_fieldn_t)81)
#define METHODN_isDerived               ((knh_methodn_t)81)
#define METHODN__isDerived              ((knh_methodn_t)81|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsDerived            ((knh_methodn_t)81|KNH_FLAG_MN_GETTER)
#define METHODN_setIsDerived            ((knh_methodn_t)81|KNH_FLAG_MN_SETTER)
#define FIELDN_isFatal                  ((knh_fieldn_t)82)
#define METHODN_isFatal                 ((knh_methodn_t)82)
#define METHODN__isFatal                ((knh_methodn_t)82|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsFatal              ((knh_methodn_t)82|KNH_FLAG_MN_GETTER)
#define METHODN_setIsFatal              ((knh_methodn_t)82|KNH_FLAG_MN_SETTER)
#define FIELDN_isFinal                  ((knh_fieldn_t)83)
#define METHODN_isFinal                 ((knh_methodn_t)83)
#define METHODN__isFinal                ((knh_methodn_t)83|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsFinal              ((knh_methodn_t)83|KNH_FLAG_MN_GETTER)
#define METHODN_setIsFinal              ((knh_methodn_t)83|KNH_FLAG_MN_SETTER)
#define FIELDN_isFormatted              ((knh_fieldn_t)84)
#define METHODN_isFormatted             ((knh_methodn_t)84)
#define METHODN__isFormatted            ((knh_methodn_t)84|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsFormatted          ((knh_methodn_t)84|KNH_FLAG_MN_GETTER)
#define METHODN_setIsFormatted          ((knh_methodn_t)84|KNH_FLAG_MN_SETTER)
#define FIELDN_isGenerated              ((knh_fieldn_t)85)
#define METHODN_isGenerated             ((knh_methodn_t)85)
#define METHODN__isGenerated            ((knh_methodn_t)85|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsGenerated          ((knh_methodn_t)85|KNH_FLAG_MN_GETTER)
#define METHODN_setIsGenerated          ((knh_methodn_t)85|KNH_FLAG_MN_SETTER)
#define FIELDN_isICast                  ((knh_fieldn_t)86)
#define METHODN_isICast                 ((knh_methodn_t)86)
#define METHODN__isICast                ((knh_methodn_t)86|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsICast              ((knh_methodn_t)86|KNH_FLAG_MN_GETTER)
#define METHODN_setIsICast              ((knh_methodn_t)86|KNH_FLAG_MN_SETTER)
#define FIELDN_isIgnoreCase             ((knh_fieldn_t)87)
#define METHODN_isIgnoreCase            ((knh_methodn_t)87)
#define METHODN__isIgnoreCase           ((knh_methodn_t)87|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsIgnoreCase         ((knh_methodn_t)87|KNH_FLAG_MN_GETTER)
#define METHODN_setIsIgnoreCase         ((knh_methodn_t)87|KNH_FLAG_MN_SETTER)
#define FIELDN_isImmutable              ((knh_fieldn_t)88)
#define METHODN_isImmutable             ((knh_methodn_t)88)
#define METHODN__isImmutable            ((knh_methodn_t)88|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsImmutable          ((knh_methodn_t)88|KNH_FLAG_MN_GETTER)
#define METHODN_setIsImmutable          ((knh_methodn_t)88|KNH_FLAG_MN_SETTER)
#define FIELDN_isInteractive            ((knh_fieldn_t)89)
#define METHODN_isInteractive           ((knh_methodn_t)89)
#define METHODN__isInteractive          ((knh_methodn_t)89|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsInteractive        ((knh_methodn_t)89|KNH_FLAG_MN_GETTER)
#define METHODN_setIsInteractive        ((knh_methodn_t)89|KNH_FLAG_MN_SETTER)
#define FIELDN_isInterface              ((knh_fieldn_t)90)
#define METHODN_isInterface             ((knh_methodn_t)90)
#define METHODN__isInterface            ((knh_methodn_t)90|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsInterface          ((knh_methodn_t)90|KNH_FLAG_MN_GETTER)
#define METHODN_setIsInterface          ((knh_methodn_t)90|KNH_FLAG_MN_SETTER)
#define FIELDN_isLocal                  ((knh_fieldn_t)91)
#define METHODN_isLocal                 ((knh_methodn_t)91)
#define METHODN__isLocal                ((knh_methodn_t)91|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsLocal              ((knh_methodn_t)91|KNH_FLAG_MN_GETTER)
#define METHODN_setIsLocal              ((knh_methodn_t)91|KNH_FLAG_MN_SETTER)
#define FIELDN_isLogging                ((knh_fieldn_t)92)
#define METHODN_isLogging               ((knh_methodn_t)92)
#define METHODN__isLogging              ((knh_methodn_t)92|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsLogging            ((knh_methodn_t)92|KNH_FLAG_MN_GETTER)
#define METHODN_setIsLogging            ((knh_methodn_t)92|KNH_FLAG_MN_SETTER)
#define FIELDN_isLossLess               ((knh_fieldn_t)93)
#define METHODN_isLossLess              ((knh_methodn_t)93)
#define METHODN__isLossLess             ((knh_methodn_t)93|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsLossLess           ((knh_methodn_t)93|KNH_FLAG_MN_GETTER)
#define METHODN_setIsLossLess           ((knh_methodn_t)93|KNH_FLAG_MN_SETTER)
#define FIELDN_isMetaExtensible         ((knh_fieldn_t)94)
#define METHODN_isMetaExtensible        ((knh_methodn_t)94)
#define METHODN__isMetaExtensible       ((knh_methodn_t)94|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsMetaExtensible     ((knh_methodn_t)94|KNH_FLAG_MN_GETTER)
#define METHODN_setIsMetaExtensible     ((knh_methodn_t)94|KNH_FLAG_MN_SETTER)
#define FIELDN_isModified               ((knh_fieldn_t)95)
#define METHODN_isModified              ((knh_methodn_t)95)
#define METHODN__isModified             ((knh_methodn_t)95|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsModified           ((knh_methodn_t)95|KNH_FLAG_MN_GETTER)
#define METHODN_setIsModified           ((knh_methodn_t)95|KNH_FLAG_MN_SETTER)
#define FIELDN_isNotNull                ((knh_fieldn_t)96)
#define METHODN_isNotNull               ((knh_methodn_t)96)
#define METHODN__isNotNull              ((knh_methodn_t)96|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsNotNull            ((knh_methodn_t)96|KNH_FLAG_MN_GETTER)
#define METHODN_setIsNotNull            ((knh_methodn_t)96|KNH_FLAG_MN_SETTER)
#define FIELDN_isNull                   ((knh_fieldn_t)97)
#define METHODN_isNull                  ((knh_methodn_t)97)
#define METHODN__isNull                 ((knh_methodn_t)97|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsNull               ((knh_methodn_t)97|KNH_FLAG_MN_GETTER)
#define METHODN_setIsNull               ((knh_methodn_t)97|KNH_FLAG_MN_SETTER)
#define FIELDN_isNullBase               ((knh_fieldn_t)98)
#define METHODN_isNullBase              ((knh_methodn_t)98)
#define METHODN__isNullBase             ((knh_methodn_t)98|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsNullBase           ((knh_methodn_t)98|KNH_FLAG_MN_GETTER)
#define METHODN_setIsNullBase           ((knh_methodn_t)98|KNH_FLAG_MN_SETTER)
#define FIELDN_isPartial                ((knh_fieldn_t)99)
#define METHODN_isPartial               ((knh_methodn_t)99)
#define METHODN__isPartial              ((knh_methodn_t)99|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsPartial            ((knh_methodn_t)99|KNH_FLAG_MN_GETTER)
#define METHODN_setIsPartial            ((knh_methodn_t)99|KNH_FLAG_MN_SETTER)
#define FIELDN_isPrivate                ((knh_fieldn_t)100)
#define METHODN_isPrivate               ((knh_methodn_t)100)
#define METHODN__isPrivate              ((knh_methodn_t)100|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsPrivate            ((knh_methodn_t)100|KNH_FLAG_MN_GETTER)
#define METHODN_setIsPrivate            ((knh_methodn_t)100|KNH_FLAG_MN_SETTER)
#define FIELDN_isPublic                 ((knh_fieldn_t)101)
#define METHODN_isPublic                ((knh_methodn_t)101)
#define METHODN__isPublic               ((knh_methodn_t)101|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsPublic             ((knh_methodn_t)101|KNH_FLAG_MN_GETTER)
#define METHODN_setIsPublic             ((knh_methodn_t)101|KNH_FLAG_MN_SETTER)
#define FIELDN_isRelease                ((knh_fieldn_t)102)
#define METHODN_isRelease               ((knh_methodn_t)102)
#define METHODN__isRelease              ((knh_methodn_t)102|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsRelease            ((knh_methodn_t)102|KNH_FLAG_MN_GETTER)
#define METHODN_setIsRelease            ((knh_methodn_t)102|KNH_FLAG_MN_SETTER)
#define FIELDN_isShared                 ((knh_fieldn_t)103)
#define METHODN_isShared                ((knh_methodn_t)103)
#define METHODN__isShared               ((knh_methodn_t)103|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsShared             ((knh_methodn_t)103|KNH_FLAG_MN_GETTER)
#define METHODN_setIsShared             ((knh_methodn_t)103|KNH_FLAG_MN_SETTER)
#define FIELDN_isSignificant            ((knh_fieldn_t)104)
#define METHODN_isSignificant           ((knh_methodn_t)104)
#define METHODN__isSignificant          ((knh_methodn_t)104|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsSignificant        ((knh_methodn_t)104|KNH_FLAG_MN_GETTER)
#define METHODN_setIsSignificant        ((knh_methodn_t)104|KNH_FLAG_MN_SETTER)
#define FIELDN_isStatement              ((knh_fieldn_t)105)
#define METHODN_isStatement             ((knh_methodn_t)105)
#define METHODN__isStatement            ((knh_methodn_t)105|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsStatement          ((knh_methodn_t)105|KNH_FLAG_MN_GETTER)
#define METHODN_setIsStatement          ((knh_methodn_t)105|KNH_FLAG_MN_SETTER)
#define FIELDN_isStatic                 ((knh_fieldn_t)106)
#define METHODN_isStatic                ((knh_methodn_t)106)
#define METHODN__isStatic               ((knh_methodn_t)106|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsStatic             ((knh_methodn_t)106|KNH_FLAG_MN_GETTER)
#define METHODN_setIsStatic             ((knh_methodn_t)106|KNH_FLAG_MN_SETTER)
#define FIELDN_isStoringBuffer          ((knh_fieldn_t)107)
#define METHODN_isStoringBuffer         ((knh_methodn_t)107)
#define METHODN__isStoringBuffer        ((knh_methodn_t)107|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsStoringBuffer      ((knh_methodn_t)107|KNH_FLAG_MN_GETTER)
#define METHODN_setIsStoringBuffer      ((knh_methodn_t)107|KNH_FLAG_MN_SETTER)
#define FIELDN_isStrict                 ((knh_fieldn_t)108)
#define METHODN_isStrict                ((knh_methodn_t)108)
#define METHODN__isStrict               ((knh_methodn_t)108|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsStrict             ((knh_methodn_t)108|KNH_FLAG_MN_GETTER)
#define METHODN_setIsStrict             ((knh_methodn_t)108|KNH_FLAG_MN_SETTER)
#define FIELDN_isSynonym                ((knh_fieldn_t)109)
#define METHODN_isSynonym               ((knh_methodn_t)109)
#define METHODN__isSynonym              ((knh_methodn_t)109|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsSynonym            ((knh_methodn_t)109|KNH_FLAG_MN_GETTER)
#define METHODN_setIsSynonym            ((knh_methodn_t)109|KNH_FLAG_MN_SETTER)
#define FIELDN_isTemporal               ((knh_fieldn_t)110)
#define METHODN_isTemporal              ((knh_methodn_t)110)
#define METHODN__isTemporal             ((knh_methodn_t)110|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsTemporal           ((knh_methodn_t)110|KNH_FLAG_MN_GETTER)
#define METHODN_setIsTemporal           ((knh_methodn_t)110|KNH_FLAG_MN_SETTER)
#define FIELDN_isTotal                  ((knh_fieldn_t)111)
#define METHODN_isTotal                 ((knh_methodn_t)111)
#define METHODN__isTotal                ((knh_methodn_t)111|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsTotal              ((knh_methodn_t)111|KNH_FLAG_MN_GETTER)
#define METHODN_setIsTotal              ((knh_methodn_t)111|KNH_FLAG_MN_SETTER)
#define FIELDN_isTrusted                ((knh_fieldn_t)112)
#define METHODN_isTrusted               ((knh_methodn_t)112)
#define METHODN__isTrusted              ((knh_methodn_t)112|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsTrusted            ((knh_methodn_t)112|KNH_FLAG_MN_GETTER)
#define METHODN_setIsTrusted            ((knh_methodn_t)112|KNH_FLAG_MN_SETTER)
#define FIELDN_isUndefined              ((knh_fieldn_t)113)
#define METHODN_isUndefined             ((knh_methodn_t)113)
#define METHODN__isUndefined            ((knh_methodn_t)113|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsUndefined          ((knh_methodn_t)113|KNH_FLAG_MN_GETTER)
#define METHODN_setIsUndefined          ((knh_methodn_t)113|KNH_FLAG_MN_SETTER)
#define FIELDN_isVarArgs                ((knh_fieldn_t)114)
#define METHODN_isVarArgs               ((knh_methodn_t)114)
#define METHODN__isVarArgs              ((knh_methodn_t)114|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsVarArgs            ((knh_methodn_t)114|KNH_FLAG_MN_GETTER)
#define METHODN_setIsVarArgs            ((knh_methodn_t)114|KNH_FLAG_MN_SETTER)
#define FIELDN_isVerbose                ((knh_fieldn_t)115)
#define METHODN_isVerbose               ((knh_methodn_t)115)
#define METHODN__isVerbose              ((knh_methodn_t)115|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsVerbose            ((knh_methodn_t)115|KNH_FLAG_MN_GETTER)
#define METHODN_setIsVerbose            ((knh_methodn_t)115|KNH_FLAG_MN_SETTER)
#define FIELDN_isVirtual                ((knh_fieldn_t)116)
#define METHODN_isVirtual               ((knh_methodn_t)116)
#define METHODN__isVirtual              ((knh_methodn_t)116|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsVirtual            ((knh_methodn_t)116|KNH_FLAG_MN_GETTER)
#define METHODN_setIsVirtual            ((knh_methodn_t)116|KNH_FLAG_MN_SETTER)
#define FIELDN_istrim                   ((knh_fieldn_t)117)
#define METHODN_istrim                  ((knh_methodn_t)117)
#define METHODN__istrim                 ((knh_methodn_t)117|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIstrim               ((knh_methodn_t)117|KNH_FLAG_MN_GETTER)
#define METHODN_setIstrim               ((knh_methodn_t)117|KNH_FLAG_MN_SETTER)
#define FIELDN_j                        ((knh_fieldn_t)118)
#define METHODN_j                       ((knh_methodn_t)118)
#define METHODN__j                      ((knh_methodn_t)118|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getJ                    ((knh_methodn_t)118|KNH_FLAG_MN_GETTER)
#define METHODN_setJ                    ((knh_methodn_t)118|KNH_FLAG_MN_SETTER)
#define FIELDN_k                        ((knh_fieldn_t)119)
#define METHODN_k                       ((knh_methodn_t)119)
#define METHODN__k                      ((knh_methodn_t)119|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getK                    ((knh_methodn_t)119|KNH_FLAG_MN_GETTER)
#define METHODN_setK                    ((knh_methodn_t)119|KNH_FLAG_MN_SETTER)
#define FIELDN_key                      ((knh_fieldn_t)120)
#define METHODN_key                     ((knh_methodn_t)120)
#define METHODN__key                    ((knh_methodn_t)120|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getKey                  ((knh_methodn_t)120|KNH_FLAG_MN_GETTER)
#define METHODN_setKey                  ((knh_methodn_t)120|KNH_FLAG_MN_SETTER)
#define FIELDN_l                        ((knh_fieldn_t)121)
#define METHODN_l                       ((knh_methodn_t)121)
#define METHODN__l                      ((knh_methodn_t)121|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getL                    ((knh_methodn_t)121|KNH_FLAG_MN_GETTER)
#define METHODN_setL                    ((knh_methodn_t)121|KNH_FLAG_MN_SETTER)
#define FIELDN_lambda                   ((knh_fieldn_t)122)
#define METHODN_lambda                  ((knh_methodn_t)122)
#define METHODN__lambda                 ((knh_methodn_t)122|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getLambda               ((knh_methodn_t)122|KNH_FLAG_MN_GETTER)
#define METHODN_setLambda               ((knh_methodn_t)122|KNH_FLAG_MN_SETTER)
#define FIELDN_lastIndexOf              ((knh_fieldn_t)123)
#define METHODN_lastIndexOf             ((knh_methodn_t)123)
#define METHODN__lastIndexOf            ((knh_methodn_t)123|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getLastIndexOf          ((knh_methodn_t)123|KNH_FLAG_MN_GETTER)
#define METHODN_setLastIndexOf          ((knh_methodn_t)123|KNH_FLAG_MN_SETTER)
#define FIELDN_lastIndexOf__IgnoreCase  ((knh_fieldn_t)124)
#define METHODN_lastIndexOf__IgnoreCase ((knh_methodn_t)124)
#define METHODN__lastIndexOf__IgnoreCase ((knh_methodn_t)124|KNH_FLAG_MN_MOVTEXT)
#define FIELDN_len                      ((knh_fieldn_t)125)
#define METHODN_len                     ((knh_methodn_t)125)
#define METHODN__len                    ((knh_methodn_t)125|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getLen                  ((knh_methodn_t)125|KNH_FLAG_MN_GETTER)
#define METHODN_setLen                  ((knh_methodn_t)125|KNH_FLAG_MN_SETTER)
#define FIELDN_likely                   ((knh_fieldn_t)126)
#define METHODN_likely                  ((knh_methodn_t)126)
#define METHODN__likely                 ((knh_methodn_t)126|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getLikely               ((knh_methodn_t)126|KNH_FLAG_MN_GETTER)
#define METHODN_setLikely               ((knh_methodn_t)126|KNH_FLAG_MN_SETTER)
#define FIELDN_linenum                  ((knh_fieldn_t)127)
#define METHODN_linenum                 ((knh_methodn_t)127)
#define METHODN__linenum                ((knh_methodn_t)127|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getLinenum              ((knh_methodn_t)127|KNH_FLAG_MN_GETTER)
#define METHODN_setLinenum              ((knh_methodn_t)127|KNH_FLAG_MN_SETTER)
#define FIELDN_listProperties           ((knh_fieldn_t)128)
#define METHODN_listProperties          ((knh_methodn_t)128)
#define METHODN__listProperties         ((knh_methodn_t)128|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getListProperties       ((knh_methodn_t)128|KNH_FLAG_MN_GETTER)
#define METHODN_setListProperties       ((knh_methodn_t)128|KNH_FLAG_MN_SETTER)
#define FIELDN_m                        ((knh_fieldn_t)129)
#define METHODN_m                       ((knh_methodn_t)129)
#define METHODN__m                      ((knh_methodn_t)129|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getM                    ((knh_methodn_t)129|KNH_FLAG_MN_GETTER)
#define METHODN_setM                    ((knh_methodn_t)129|KNH_FLAG_MN_SETTER)
#define FIELDN_main                     ((knh_fieldn_t)130)
#define METHODN_main                    ((knh_methodn_t)130)
#define METHODN__main                   ((knh_methodn_t)130|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getMain                 ((knh_methodn_t)130|KNH_FLAG_MN_GETTER)
#define METHODN_setMain                 ((knh_methodn_t)130|KNH_FLAG_MN_SETTER)
#define FIELDN_man                      ((knh_fieldn_t)131)
#define METHODN_man                     ((knh_methodn_t)131)
#define METHODN__man                    ((knh_methodn_t)131|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getMan                  ((knh_methodn_t)131|KNH_FLAG_MN_GETTER)
#define METHODN_setMan                  ((knh_methodn_t)131|KNH_FLAG_MN_SETTER)
#define FIELDN_match                    ((knh_fieldn_t)132)
#define METHODN_match                   ((knh_methodn_t)132)
#define METHODN__match                  ((knh_methodn_t)132|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getMatch                ((knh_methodn_t)132|KNH_FLAG_MN_GETTER)
#define METHODN_setMatch                ((knh_methodn_t)132|KNH_FLAG_MN_SETTER)
#define FIELDN_memcpy                   ((knh_fieldn_t)133)
#define METHODN_memcpy                  ((knh_methodn_t)133)
#define METHODN__memcpy                 ((knh_methodn_t)133|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getMemcpy               ((knh_methodn_t)133|KNH_FLAG_MN_GETTER)
#define METHODN_setMemcpy               ((knh_methodn_t)133|KNH_FLAG_MN_SETTER)
#define FIELDN_mode                     ((knh_fieldn_t)134)
#define METHODN_mode                    ((knh_methodn_t)134)
#define METHODN__mode                   ((knh_methodn_t)134|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getMode                 ((knh_methodn_t)134|KNH_FLAG_MN_GETTER)
#define METHODN_setMode                 ((knh_methodn_t)134|KNH_FLAG_MN_SETTER)
#define FIELDN_modified                 ((knh_fieldn_t)135)
#define METHODN_modified                ((knh_methodn_t)135)
#define METHODN__modified               ((knh_methodn_t)135|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getModified             ((knh_methodn_t)135|KNH_FLAG_MN_GETTER)
#define METHODN_setModified             ((knh_methodn_t)135|KNH_FLAG_MN_SETTER)
#define FIELDN_msg                      ((knh_fieldn_t)136)
#define METHODN_msg                     ((knh_methodn_t)136)
#define METHODN__msg                    ((knh_methodn_t)136|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getMsg                  ((knh_methodn_t)136|KNH_FLAG_MN_GETTER)
#define METHODN_setMsg                  ((knh_methodn_t)136|KNH_FLAG_MN_SETTER)
#define FIELDN_mtd                      ((knh_fieldn_t)137)
#define METHODN_mtd                     ((knh_methodn_t)137)
#define METHODN__mtd                    ((knh_methodn_t)137|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getMtd                  ((knh_methodn_t)137|KNH_FLAG_MN_GETTER)
#define METHODN_setMtd                  ((knh_methodn_t)137|KNH_FLAG_MN_SETTER)
#define FIELDN_n                        ((knh_fieldn_t)138)
#define METHODN_n                       ((knh_methodn_t)138)
#define METHODN__n                      ((knh_methodn_t)138|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getN                    ((knh_methodn_t)138|KNH_FLAG_MN_GETTER)
#define METHODN_setN                    ((knh_methodn_t)138|KNH_FLAG_MN_SETTER)
#define FIELDN_name                     ((knh_fieldn_t)139)
#define METHODN_name                    ((knh_methodn_t)139)
#define METHODN__name                   ((knh_methodn_t)139|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getName                 ((knh_methodn_t)139|KNH_FLAG_MN_GETTER)
#define METHODN_setName                 ((knh_methodn_t)139|KNH_FLAG_MN_SETTER)
#define FIELDN_new                      ((knh_fieldn_t)140)
#define METHODN_new                     ((knh_methodn_t)140)
#define METHODN__new                    ((knh_methodn_t)140|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getNew                  ((knh_methodn_t)140|KNH_FLAG_MN_GETTER)
#define METHODN_setNew                  ((knh_methodn_t)140|KNH_FLAG_MN_SETTER)
#define FIELDN_new__array               ((knh_fieldn_t)141)
#define METHODN_new__array              ((knh_methodn_t)141)
#define METHODN__new__array             ((knh_methodn_t)141|KNH_FLAG_MN_MOVTEXT)
#define FIELDN_new__array2D             ((knh_fieldn_t)142)
#define METHODN_new__array2D            ((knh_methodn_t)142)
#define METHODN__new__array2D           ((knh_methodn_t)142|KNH_FLAG_MN_MOVTEXT)
#define FIELDN_new__array3D             ((knh_fieldn_t)143)
#define METHODN_new__array3D            ((knh_methodn_t)143)
#define METHODN__new__array3D           ((knh_methodn_t)143|KNH_FLAG_MN_MOVTEXT)
#define FIELDN_new__init                ((knh_fieldn_t)144)
#define METHODN_new__init               ((knh_methodn_t)144)
#define METHODN__new__init              ((knh_methodn_t)144|KNH_FLAG_MN_MOVTEXT)
#define FIELDN_next                     ((knh_fieldn_t)145)
#define METHODN_next                    ((knh_methodn_t)145)
#define METHODN__next                   ((knh_methodn_t)145|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getNext                 ((knh_methodn_t)145|KNH_FLAG_MN_GETTER)
#define METHODN_setNext                 ((knh_methodn_t)145|KNH_FLAG_MN_SETTER)
#define FIELDN_o                        ((knh_fieldn_t)146)
#define METHODN_o                       ((knh_methodn_t)146)
#define METHODN__o                      ((knh_methodn_t)146|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getO                    ((knh_methodn_t)146|KNH_FLAG_MN_GETTER)
#define METHODN_setO                    ((knh_methodn_t)146|KNH_FLAG_MN_SETTER)
#define FIELDN_off                      ((knh_fieldn_t)147)
#define METHODN_off                     ((knh_methodn_t)147)
#define METHODN__off                    ((knh_methodn_t)147|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOff                  ((knh_methodn_t)147|KNH_FLAG_MN_GETTER)
#define METHODN_setOff                  ((knh_methodn_t)147|KNH_FLAG_MN_SETTER)
#define FIELDN_offset                   ((knh_fieldn_t)148)
#define METHODN_offset                  ((knh_methodn_t)148)
#define METHODN__offset                 ((knh_methodn_t)148|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOffset               ((knh_methodn_t)148|KNH_FLAG_MN_GETTER)
#define METHODN_setOffset               ((knh_methodn_t)148|KNH_FLAG_MN_SETTER)
#define FIELDN_opAdd                    ((knh_fieldn_t)149)
#define METHODN_opAdd                   ((knh_methodn_t)149)
#define METHODN__opAdd                  ((knh_methodn_t)149|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpAdd                ((knh_methodn_t)149|KNH_FLAG_MN_GETTER)
#define METHODN_setOpAdd                ((knh_methodn_t)149|KNH_FLAG_MN_SETTER)
#define FIELDN_opAddr                   ((knh_fieldn_t)150)
#define METHODN_opAddr                  ((knh_methodn_t)150)
#define METHODN__opAddr                 ((knh_methodn_t)150|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpAddr               ((knh_methodn_t)150|KNH_FLAG_MN_GETTER)
#define METHODN_setOpAddr               ((knh_methodn_t)150|KNH_FLAG_MN_SETTER)
#define FIELDN_opDiv                    ((knh_fieldn_t)151)
#define METHODN_opDiv                   ((knh_methodn_t)151)
#define METHODN__opDiv                  ((knh_methodn_t)151|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpDiv                ((knh_methodn_t)151|KNH_FLAG_MN_GETTER)
#define METHODN_setOpDiv                ((knh_methodn_t)151|KNH_FLAG_MN_SETTER)
#define FIELDN_opEq                     ((knh_fieldn_t)152)
#define METHODN_opEq                    ((knh_methodn_t)152)
#define METHODN__opEq                   ((knh_methodn_t)152|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpEq                 ((knh_methodn_t)152|KNH_FLAG_MN_GETTER)
#define METHODN_setOpEq                 ((knh_methodn_t)152|KNH_FLAG_MN_SETTER)
#define FIELDN_opFill                   ((knh_fieldn_t)153)
#define METHODN_opFill                  ((knh_methodn_t)153)
#define METHODN__opFill                 ((knh_methodn_t)153|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpFill               ((knh_methodn_t)153|KNH_FLAG_MN_GETTER)
#define METHODN_setOpFill               ((knh_methodn_t)153|KNH_FLAG_MN_SETTER)
#define FIELDN_opGt                     ((knh_fieldn_t)154)
#define METHODN_opGt                    ((knh_methodn_t)154)
#define METHODN__opGt                   ((knh_methodn_t)154|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpGt                 ((knh_methodn_t)154|KNH_FLAG_MN_GETTER)
#define METHODN_setOpGt                 ((knh_methodn_t)154|KNH_FLAG_MN_SETTER)
#define FIELDN_opGte                    ((knh_fieldn_t)155)
#define METHODN_opGte                   ((knh_methodn_t)155)
#define METHODN__opGte                  ((knh_methodn_t)155|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpGte                ((knh_methodn_t)155|KNH_FLAG_MN_GETTER)
#define METHODN_setOpGte                ((knh_methodn_t)155|KNH_FLAG_MN_SETTER)
#define FIELDN_opHas                    ((knh_fieldn_t)156)
#define METHODN_opHas                   ((knh_methodn_t)156)
#define METHODN__opHas                  ((knh_methodn_t)156|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpHas                ((knh_methodn_t)156|KNH_FLAG_MN_GETTER)
#define METHODN_setOpHas                ((knh_methodn_t)156|KNH_FLAG_MN_SETTER)
#define FIELDN_opInstanceof             ((knh_fieldn_t)157)
#define METHODN_opInstanceof            ((knh_methodn_t)157)
#define METHODN__opInstanceof           ((knh_methodn_t)157|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpInstanceof         ((knh_methodn_t)157|KNH_FLAG_MN_GETTER)
#define METHODN_setOpInstanceof         ((knh_methodn_t)157|KNH_FLAG_MN_SETTER)
#define FIELDN_opIs                     ((knh_fieldn_t)158)
#define METHODN_opIs                    ((knh_methodn_t)158)
#define METHODN__opIs                   ((knh_methodn_t)158|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpIs                 ((knh_methodn_t)158|KNH_FLAG_MN_GETTER)
#define METHODN_setOpIs                 ((knh_methodn_t)158|KNH_FLAG_MN_SETTER)
#define FIELDN_opIsa                    ((knh_fieldn_t)159)
#define METHODN_opIsa                   ((knh_methodn_t)159)
#define METHODN__opIsa                  ((knh_methodn_t)159|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpIsa                ((knh_methodn_t)159|KNH_FLAG_MN_GETTER)
#define METHODN_setOpIsa                ((knh_methodn_t)159|KNH_FLAG_MN_SETTER)
#define FIELDN_opItr                    ((knh_fieldn_t)160)
#define METHODN_opItr                   ((knh_methodn_t)160)
#define METHODN__opItr                  ((knh_methodn_t)160|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpItr                ((knh_methodn_t)160|KNH_FLAG_MN_GETTER)
#define METHODN_setOpItr                ((knh_methodn_t)160|KNH_FLAG_MN_SETTER)
#define FIELDN_opLand                   ((knh_fieldn_t)161)
#define METHODN_opLand                  ((knh_methodn_t)161)
#define METHODN__opLand                 ((knh_methodn_t)161|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpLand               ((knh_methodn_t)161|KNH_FLAG_MN_GETTER)
#define METHODN_setOpLand               ((knh_methodn_t)161|KNH_FLAG_MN_SETTER)
#define FIELDN_opLnot                   ((knh_fieldn_t)162)
#define METHODN_opLnot                  ((knh_methodn_t)162)
#define METHODN__opLnot                 ((knh_methodn_t)162|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpLnot               ((knh_methodn_t)162|KNH_FLAG_MN_GETTER)
#define METHODN_setOpLnot               ((knh_methodn_t)162|KNH_FLAG_MN_SETTER)
#define FIELDN_opLor                    ((knh_fieldn_t)163)
#define METHODN_opLor                   ((knh_methodn_t)163)
#define METHODN__opLor                  ((knh_methodn_t)163|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpLor                ((knh_methodn_t)163|KNH_FLAG_MN_GETTER)
#define METHODN_setOpLor                ((knh_methodn_t)163|KNH_FLAG_MN_SETTER)
#define FIELDN_opLshift                 ((knh_fieldn_t)164)
#define METHODN_opLshift                ((knh_methodn_t)164)
#define METHODN__opLshift               ((knh_methodn_t)164|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpLshift             ((knh_methodn_t)164|KNH_FLAG_MN_GETTER)
#define METHODN_setOpLshift             ((knh_methodn_t)164|KNH_FLAG_MN_SETTER)
#define FIELDN_opLt                     ((knh_fieldn_t)165)
#define METHODN_opLt                    ((knh_methodn_t)165)
#define METHODN__opLt                   ((knh_methodn_t)165|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpLt                 ((knh_methodn_t)165|KNH_FLAG_MN_GETTER)
#define METHODN_setOpLt                 ((knh_methodn_t)165|KNH_FLAG_MN_SETTER)
#define FIELDN_opLte                    ((knh_fieldn_t)166)
#define METHODN_opLte                   ((knh_methodn_t)166)
#define METHODN__opLte                  ((knh_methodn_t)166|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpLte                ((knh_methodn_t)166|KNH_FLAG_MN_GETTER)
#define METHODN_setOpLte                ((knh_methodn_t)166|KNH_FLAG_MN_SETTER)
#define FIELDN_opMatch                  ((knh_fieldn_t)167)
#define METHODN_opMatch                 ((knh_methodn_t)167)
#define METHODN__opMatch                ((knh_methodn_t)167|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpMatch              ((knh_methodn_t)167|KNH_FLAG_MN_GETTER)
#define METHODN_setOpMatch              ((knh_methodn_t)167|KNH_FLAG_MN_SETTER)
#define FIELDN_opMod                    ((knh_fieldn_t)168)
#define METHODN_opMod                   ((knh_methodn_t)168)
#define METHODN__opMod                  ((knh_methodn_t)168|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpMod                ((knh_methodn_t)168|KNH_FLAG_MN_GETTER)
#define METHODN_setOpMod                ((knh_methodn_t)168|KNH_FLAG_MN_SETTER)
#define FIELDN_opMul                    ((knh_fieldn_t)169)
#define METHODN_opMul                   ((knh_methodn_t)169)
#define METHODN__opMul                  ((knh_methodn_t)169|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpMul                ((knh_methodn_t)169|KNH_FLAG_MN_GETTER)
#define METHODN_setOpMul                ((knh_methodn_t)169|KNH_FLAG_MN_SETTER)
#define FIELDN_opNeg                    ((knh_fieldn_t)170)
#define METHODN_opNeg                   ((knh_methodn_t)170)
#define METHODN__opNeg                  ((knh_methodn_t)170|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpNeg                ((knh_methodn_t)170|KNH_FLAG_MN_GETTER)
#define METHODN_setOpNeg                ((knh_methodn_t)170|KNH_FLAG_MN_SETTER)
#define FIELDN_opNeq                    ((knh_fieldn_t)171)
#define METHODN_opNeq                   ((knh_methodn_t)171)
#define METHODN__opNeq                  ((knh_methodn_t)171|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpNeq                ((knh_methodn_t)171|KNH_FLAG_MN_GETTER)
#define METHODN_setOpNeq                ((knh_methodn_t)171|KNH_FLAG_MN_SETTER)
#define FIELDN_opNext                   ((knh_fieldn_t)172)
#define METHODN_opNext                  ((knh_methodn_t)172)
#define METHODN__opNext                 ((knh_methodn_t)172|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpNext               ((knh_methodn_t)172|KNH_FLAG_MN_GETTER)
#define METHODN_setOpNext               ((knh_methodn_t)172|KNH_FLAG_MN_SETTER)
#define FIELDN_opNot                    ((knh_fieldn_t)173)
#define METHODN_opNot                   ((knh_methodn_t)173)
#define METHODN__opNot                  ((knh_methodn_t)173|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpNot                ((knh_methodn_t)173|KNH_FLAG_MN_GETTER)
#define METHODN_setOpNot                ((knh_methodn_t)173|KNH_FLAG_MN_SETTER)
#define FIELDN_opOffset                 ((knh_fieldn_t)174)
#define METHODN_opOffset                ((knh_methodn_t)174)
#define METHODN__opOffset               ((knh_methodn_t)174|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpOffset             ((knh_methodn_t)174|KNH_FLAG_MN_GETTER)
#define METHODN_setOpOffset             ((knh_methodn_t)174|KNH_FLAG_MN_SETTER)
#define FIELDN_opPrev                   ((knh_fieldn_t)175)
#define METHODN_opPrev                  ((knh_methodn_t)175)
#define METHODN__opPrev                 ((knh_methodn_t)175|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpPrev               ((knh_methodn_t)175|KNH_FLAG_MN_GETTER)
#define METHODN_setOpPrev               ((knh_methodn_t)175|KNH_FLAG_MN_SETTER)
#define FIELDN_opRshift                 ((knh_fieldn_t)176)
#define METHODN_opRshift                ((knh_methodn_t)176)
#define METHODN__opRshift               ((knh_methodn_t)176|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpRshift             ((knh_methodn_t)176|KNH_FLAG_MN_GETTER)
#define METHODN_setOpRshift             ((knh_methodn_t)176|KNH_FLAG_MN_SETTER)
#define FIELDN_opSub                    ((knh_fieldn_t)177)
#define METHODN_opSub                   ((knh_methodn_t)177)
#define METHODN__opSub                  ((knh_methodn_t)177|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpSub                ((knh_methodn_t)177|KNH_FLAG_MN_GETTER)
#define METHODN_setOpSub                ((knh_methodn_t)177|KNH_FLAG_MN_SETTER)
#define FIELDN_opSubset                 ((knh_fieldn_t)178)
#define METHODN_opSubset                ((knh_methodn_t)178)
#define METHODN__opSubset               ((knh_methodn_t)178|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpSubset             ((knh_methodn_t)178|KNH_FLAG_MN_GETTER)
#define METHODN_setOpSubset             ((knh_methodn_t)178|KNH_FLAG_MN_SETTER)
#define FIELDN_opSubsete                ((knh_fieldn_t)179)
#define METHODN_opSubsete               ((knh_methodn_t)179)
#define METHODN__opSubsete              ((knh_methodn_t)179|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpSubsete            ((knh_methodn_t)179|KNH_FLAG_MN_GETTER)
#define METHODN_setOpSubsete            ((knh_methodn_t)179|KNH_FLAG_MN_SETTER)
#define FIELDN_opTo                     ((knh_fieldn_t)180)
#define METHODN_opTo                    ((knh_methodn_t)180)
#define METHODN__opTo                   ((knh_methodn_t)180|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpTo                 ((knh_methodn_t)180|KNH_FLAG_MN_GETTER)
#define METHODN_setOpTo                 ((knh_methodn_t)180|KNH_FLAG_MN_SETTER)
#define FIELDN_opXor                    ((knh_fieldn_t)181)
#define METHODN_opXor                   ((knh_methodn_t)181)
#define METHODN__opXor                  ((knh_methodn_t)181|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpXor                ((knh_methodn_t)181|KNH_FLAG_MN_GETTER)
#define METHODN_setOpXor                ((knh_methodn_t)181|KNH_FLAG_MN_SETTER)
#define FIELDN_option                   ((knh_fieldn_t)182)
#define METHODN_option                  ((knh_methodn_t)182)
#define METHODN__option                 ((knh_methodn_t)182|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOption               ((knh_methodn_t)182|KNH_FLAG_MN_GETTER)
#define METHODN_setOption               ((knh_methodn_t)182|KNH_FLAG_MN_SETTER)
#define FIELDN_out                      ((knh_fieldn_t)183)
#define METHODN_out                     ((knh_methodn_t)183)
#define METHODN__out                    ((knh_methodn_t)183|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOut                  ((knh_methodn_t)183|KNH_FLAG_MN_GETTER)
#define METHODN_setOut                  ((knh_methodn_t)183|KNH_FLAG_MN_SETTER)
#define FIELDN_outputStream             ((knh_fieldn_t)184)
#define METHODN_outputStream            ((knh_methodn_t)184)
#define METHODN__outputStream           ((knh_methodn_t)184|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOutputStream         ((knh_methodn_t)184|KNH_FLAG_MN_GETTER)
#define METHODN_setOutputStream         ((knh_methodn_t)184|KNH_FLAG_MN_SETTER)
#define FIELDN_p                        ((knh_fieldn_t)185)
#define METHODN_p                       ((knh_methodn_t)185)
#define METHODN__p                      ((knh_methodn_t)185|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getP                    ((knh_methodn_t)185|KNH_FLAG_MN_GETTER)
#define METHODN_setP                    ((knh_methodn_t)185|KNH_FLAG_MN_SETTER)
#define FIELDN_path                     ((knh_fieldn_t)186)
#define METHODN_path                    ((knh_methodn_t)186)
#define METHODN__path                   ((knh_methodn_t)186|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getPath                 ((knh_methodn_t)186|KNH_FLAG_MN_GETTER)
#define METHODN_setPath                 ((knh_methodn_t)186|KNH_FLAG_MN_SETTER)
#define FIELDN_pattern                  ((knh_fieldn_t)187)
#define METHODN_pattern                 ((knh_methodn_t)187)
#define METHODN__pattern                ((knh_methodn_t)187|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getPattern              ((knh_methodn_t)187|KNH_FLAG_MN_GETTER)
#define METHODN_setPattern              ((knh_methodn_t)187|KNH_FLAG_MN_SETTER)
#define FIELDN_pop                      ((knh_fieldn_t)188)
#define METHODN_pop                     ((knh_methodn_t)188)
#define METHODN__pop                    ((knh_methodn_t)188|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getPop                  ((knh_methodn_t)188|KNH_FLAG_MN_GETTER)
#define METHODN_setPop                  ((knh_methodn_t)188|KNH_FLAG_MN_SETTER)
#define FIELDN_port                     ((knh_fieldn_t)189)
#define METHODN_port                    ((knh_methodn_t)189)
#define METHODN__port                   ((knh_methodn_t)189|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getPort                 ((knh_methodn_t)189|KNH_FLAG_MN_GETTER)
#define METHODN_setPort                 ((knh_methodn_t)189|KNH_FLAG_MN_SETTER)
#define FIELDN_print                    ((knh_fieldn_t)190)
#define METHODN_print                   ((knh_methodn_t)190)
#define METHODN__print                  ((knh_methodn_t)190|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getPrint                ((knh_methodn_t)190|KNH_FLAG_MN_GETTER)
#define METHODN_setPrint                ((knh_methodn_t)190|KNH_FLAG_MN_SETTER)
#define FIELDN_println                  ((knh_fieldn_t)191)
#define METHODN_println                 ((knh_methodn_t)191)
#define METHODN__println                ((knh_methodn_t)191|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getPrintln              ((knh_methodn_t)191|KNH_FLAG_MN_GETTER)
#define METHODN_setPrintln              ((knh_methodn_t)191|KNH_FLAG_MN_SETTER)
#define FIELDN_proceed                  ((knh_fieldn_t)192)
#define METHODN_proceed                 ((knh_methodn_t)192)
#define METHODN__proceed                ((knh_methodn_t)192|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getProceed              ((knh_methodn_t)192|KNH_FLAG_MN_GETTER)
#define METHODN_setProceed              ((knh_methodn_t)192|KNH_FLAG_MN_SETTER)
#define FIELDN_prompt                   ((knh_fieldn_t)193)
#define METHODN_prompt                  ((knh_methodn_t)193)
#define METHODN__prompt                 ((knh_methodn_t)193|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getPrompt               ((knh_methodn_t)193|KNH_FLAG_MN_GETTER)
#define METHODN_setPrompt               ((knh_methodn_t)193|KNH_FLAG_MN_SETTER)
#define FIELDN_property                 ((knh_fieldn_t)194)
#define METHODN_property                ((knh_methodn_t)194)
#define METHODN__property               ((knh_methodn_t)194|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getProperty             ((knh_methodn_t)194|KNH_FLAG_MN_GETTER)
#define METHODN_setProperty             ((knh_methodn_t)194|KNH_FLAG_MN_SETTER)
#define FIELDN_putChar                  ((knh_fieldn_t)195)
#define METHODN_putChar                 ((knh_methodn_t)195)
#define METHODN__putChar                ((knh_methodn_t)195|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getPutChar              ((knh_methodn_t)195|KNH_FLAG_MN_GETTER)
#define METHODN_setPutChar              ((knh_methodn_t)195|KNH_FLAG_MN_SETTER)
#define FIELDN_putc                     ((knh_fieldn_t)196)
#define METHODN_putc                    ((knh_methodn_t)196)
#define METHODN__putc                   ((knh_methodn_t)196|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getPutc                 ((knh_methodn_t)196|KNH_FLAG_MN_GETTER)
#define METHODN_setPutc                 ((knh_methodn_t)196|KNH_FLAG_MN_SETTER)
#define FIELDN_q                        ((knh_fieldn_t)197)
#define METHODN_q                       ((knh_methodn_t)197)
#define METHODN__q                      ((knh_methodn_t)197|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getQ                    ((knh_methodn_t)197|KNH_FLAG_MN_GETTER)
#define METHODN_setQ                    ((knh_methodn_t)197|KNH_FLAG_MN_SETTER)
#define FIELDN_query                    ((knh_fieldn_t)198)
#define METHODN_query                   ((knh_methodn_t)198)
#define METHODN__query                  ((knh_methodn_t)198|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getQuery                ((knh_methodn_t)198|KNH_FLAG_MN_GETTER)
#define METHODN_setQuery                ((knh_methodn_t)198|KNH_FLAG_MN_SETTER)
#define FIELDN_r                        ((knh_fieldn_t)199)
#define METHODN_r                       ((knh_methodn_t)199)
#define METHODN__r                      ((knh_methodn_t)199|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getR                    ((knh_methodn_t)199|KNH_FLAG_MN_GETTER)
#define METHODN_setR                    ((knh_methodn_t)199|KNH_FLAG_MN_SETTER)
#define FIELDN_random                   ((knh_fieldn_t)200)
#define METHODN_random                  ((knh_methodn_t)200)
#define METHODN__random                 ((knh_methodn_t)200|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getRandom               ((knh_methodn_t)200|KNH_FLAG_MN_GETTER)
#define METHODN_setRandom               ((knh_methodn_t)200|KNH_FLAG_MN_SETTER)
#define FIELDN_randomSeed               ((knh_fieldn_t)201)
#define METHODN_randomSeed              ((knh_methodn_t)201)
#define METHODN__randomSeed             ((knh_methodn_t)201|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getRandomSeed           ((knh_methodn_t)201|KNH_FLAG_MN_GETTER)
#define METHODN_setRandomSeed           ((knh_methodn_t)201|KNH_FLAG_MN_SETTER)
#define FIELDN_re                       ((knh_fieldn_t)202)
#define METHODN_re                      ((knh_methodn_t)202)
#define METHODN__re                     ((knh_methodn_t)202|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getRe                   ((knh_methodn_t)202|KNH_FLAG_MN_GETTER)
#define METHODN_setRe                   ((knh_methodn_t)202|KNH_FLAG_MN_SETTER)
#define FIELDN_read                     ((knh_fieldn_t)203)
#define METHODN_read                    ((knh_methodn_t)203)
#define METHODN__read                   ((knh_methodn_t)203|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getRead                 ((knh_methodn_t)203|KNH_FLAG_MN_GETTER)
#define METHODN_setRead                 ((knh_methodn_t)203|KNH_FLAG_MN_SETTER)
#define FIELDN_readLine                 ((knh_fieldn_t)204)
#define METHODN_readLine                ((knh_methodn_t)204)
#define METHODN__readLine               ((knh_methodn_t)204|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getReadLine             ((knh_methodn_t)204|KNH_FLAG_MN_GETTER)
#define METHODN_setReadLine             ((knh_methodn_t)204|KNH_FLAG_MN_SETTER)
#define FIELDN_register                 ((knh_fieldn_t)205)
#define METHODN_register                ((knh_methodn_t)205)
#define METHODN__register               ((knh_methodn_t)205|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getRegister             ((knh_methodn_t)205|KNH_FLAG_MN_GETTER)
#define METHODN_setRegister             ((knh_methodn_t)205|KNH_FLAG_MN_SETTER)
#define FIELDN_remove                   ((knh_fieldn_t)206)
#define METHODN_remove                  ((knh_methodn_t)206)
#define METHODN__remove                 ((knh_methodn_t)206|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getRemove               ((knh_methodn_t)206|KNH_FLAG_MN_GETTER)
#define METHODN_setRemove               ((knh_methodn_t)206|KNH_FLAG_MN_SETTER)
#define FIELDN_replace                  ((knh_fieldn_t)207)
#define METHODN_replace                 ((knh_methodn_t)207)
#define METHODN__replace                ((knh_methodn_t)207|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getReplace              ((knh_methodn_t)207|KNH_FLAG_MN_GETTER)
#define METHODN_setReplace              ((knh_methodn_t)207|KNH_FLAG_MN_SETTER)
#define FIELDN_reverse                  ((knh_fieldn_t)208)
#define METHODN_reverse                 ((knh_methodn_t)208)
#define METHODN__reverse                ((knh_methodn_t)208|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getReverse              ((knh_methodn_t)208|KNH_FLAG_MN_GETTER)
#define METHODN_setReverse              ((knh_methodn_t)208|KNH_FLAG_MN_SETTER)
#define FIELDN_s                        ((knh_fieldn_t)209)
#define METHODN_s                       ((knh_methodn_t)209)
#define METHODN__s                      ((knh_methodn_t)209|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getS                    ((knh_methodn_t)209|KNH_FLAG_MN_GETTER)
#define METHODN_setS                    ((knh_methodn_t)209|KNH_FLAG_MN_SETTER)
#define FIELDN_script                   ((knh_fieldn_t)210)
#define METHODN_script                  ((knh_methodn_t)210)
#define METHODN__script                 ((knh_methodn_t)210|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getScript               ((knh_methodn_t)210|KNH_FLAG_MN_GETTER)
#define METHODN_setScript               ((knh_methodn_t)210|KNH_FLAG_MN_SETTER)
#define FIELDN_seed                     ((knh_fieldn_t)211)
#define METHODN_seed                    ((knh_methodn_t)211)
#define METHODN__seed                   ((knh_methodn_t)211|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getSeed                 ((knh_methodn_t)211|KNH_FLAG_MN_GETTER)
#define METHODN_setSeed                 ((knh_methodn_t)211|KNH_FLAG_MN_SETTER)
#define FIELDN_shared                   ((knh_fieldn_t)212)
#define METHODN_shared                  ((knh_methodn_t)212)
#define METHODN__shared                 ((knh_methodn_t)212|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getShared               ((knh_methodn_t)212|KNH_FLAG_MN_GETTER)
#define METHODN_setShared               ((knh_methodn_t)212|KNH_FLAG_MN_SETTER)
#define FIELDN_shuffle                  ((knh_fieldn_t)213)
#define METHODN_shuffle                 ((knh_methodn_t)213)
#define METHODN__shuffle                ((knh_methodn_t)213|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getShuffle              ((knh_methodn_t)213|KNH_FLAG_MN_GETTER)
#define METHODN_setShuffle              ((knh_methodn_t)213|KNH_FLAG_MN_SETTER)
#define FIELDN_size                     ((knh_fieldn_t)214)
#define METHODN_size                    ((knh_methodn_t)214)
#define METHODN__size                   ((knh_methodn_t)214|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getSize                 ((knh_methodn_t)214|KNH_FLAG_MN_GETTER)
#define METHODN_setSize                 ((knh_methodn_t)214|KNH_FLAG_MN_SETTER)
#define FIELDN_sort                     ((knh_fieldn_t)215)
#define METHODN_sort                    ((knh_methodn_t)215)
#define METHODN__sort                   ((knh_methodn_t)215|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getSort                 ((knh_methodn_t)215|KNH_FLAG_MN_GETTER)
#define METHODN_setSort                 ((knh_methodn_t)215|KNH_FLAG_MN_SETTER)
#define FIELDN_split                    ((knh_fieldn_t)216)
#define METHODN_split                   ((knh_methodn_t)216)
#define METHODN__split                  ((knh_methodn_t)216|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getSplit                ((knh_methodn_t)216|KNH_FLAG_MN_GETTER)
#define METHODN_setSplit                ((knh_methodn_t)216|KNH_FLAG_MN_SETTER)
#define FIELDN_stackdump                ((knh_fieldn_t)217)
#define METHODN_stackdump               ((knh_methodn_t)217)
#define METHODN__stackdump              ((knh_methodn_t)217|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getStackdump            ((knh_methodn_t)217|KNH_FLAG_MN_GETTER)
#define METHODN_setStackdump            ((knh_methodn_t)217|KNH_FLAG_MN_SETTER)
#define FIELDN_startsWith               ((knh_fieldn_t)218)
#define METHODN_startsWith              ((knh_methodn_t)218)
#define METHODN__startsWith             ((knh_methodn_t)218|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getStartsWith           ((knh_methodn_t)218|KNH_FLAG_MN_GETTER)
#define METHODN_setStartsWith           ((knh_methodn_t)218|KNH_FLAG_MN_SETTER)
#define FIELDN_startsWith__IgnoreCase   ((knh_fieldn_t)219)
#define METHODN_startsWith__IgnoreCase  ((knh_methodn_t)219)
#define METHODN__startsWith__IgnoreCase ((knh_methodn_t)219|KNH_FLAG_MN_MOVTEXT)
#define FIELDN_status                   ((knh_fieldn_t)220)
#define METHODN_status                  ((knh_methodn_t)220)
#define METHODN__status                 ((knh_methodn_t)220|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getStatus               ((knh_methodn_t)220|KNH_FLAG_MN_GETTER)
#define METHODN_setStatus               ((knh_methodn_t)220|KNH_FLAG_MN_SETTER)
#define FIELDN_stdErr                   ((knh_fieldn_t)221)
#define METHODN_stdErr                  ((knh_methodn_t)221)
#define METHODN__stdErr                 ((knh_methodn_t)221|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getStdErr               ((knh_methodn_t)221|KNH_FLAG_MN_GETTER)
#define METHODN_setStdErr               ((knh_methodn_t)221|KNH_FLAG_MN_SETTER)
#define FIELDN_storingBuffer            ((knh_fieldn_t)222)
#define METHODN_storingBuffer           ((knh_methodn_t)222)
#define METHODN__storingBuffer          ((knh_methodn_t)222|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getStoringBuffer        ((knh_methodn_t)222|KNH_FLAG_MN_GETTER)
#define METHODN_setStoringBuffer        ((knh_methodn_t)222|KNH_FLAG_MN_SETTER)
#define FIELDN_strict                   ((knh_fieldn_t)223)
#define METHODN_strict                  ((knh_methodn_t)223)
#define METHODN__strict                 ((knh_methodn_t)223|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getStrict               ((knh_methodn_t)223|KNH_FLAG_MN_GETTER)
#define METHODN_setStrict               ((knh_methodn_t)223|KNH_FLAG_MN_SETTER)
#define FIELDN_string                   ((knh_fieldn_t)224)
#define METHODN_string                  ((knh_methodn_t)224)
#define METHODN__string                 ((knh_methodn_t)224|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getString               ((knh_methodn_t)224|KNH_FLAG_MN_GETTER)
#define METHODN_setString               ((knh_methodn_t)224|KNH_FLAG_MN_SETTER)
#define FIELDN_substring                ((knh_fieldn_t)225)
#define METHODN_substring               ((knh_methodn_t)225)
#define METHODN__substring              ((knh_methodn_t)225|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getSubstring            ((knh_methodn_t)225|KNH_FLAG_MN_GETTER)
#define METHODN_setSubstring            ((knh_methodn_t)225|KNH_FLAG_MN_SETTER)
#define FIELDN_super                    ((knh_fieldn_t)226)
#define METHODN_super                   ((knh_methodn_t)226)
#define METHODN__super                  ((knh_methodn_t)226|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getSuper                ((knh_methodn_t)226|KNH_FLAG_MN_GETTER)
#define METHODN_setSuper                ((knh_methodn_t)226|KNH_FLAG_MN_SETTER)
#define FIELDN_swap                     ((knh_fieldn_t)227)
#define METHODN_swap                    ((knh_methodn_t)227)
#define METHODN__swap                   ((knh_methodn_t)227|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getSwap                 ((knh_methodn_t)227|KNH_FLAG_MN_GETTER)
#define METHODN_setSwap                 ((knh_methodn_t)227|KNH_FLAG_MN_SETTER)
#define FIELDN_t                        ((knh_fieldn_t)228)
#define METHODN_t                       ((knh_methodn_t)228)
#define METHODN__t                      ((knh_methodn_t)228|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getT                    ((knh_methodn_t)228|KNH_FLAG_MN_GETTER)
#define METHODN_setT                    ((knh_methodn_t)228|KNH_FLAG_MN_SETTER)
#define FIELDN_term                     ((knh_fieldn_t)229)
#define METHODN_term                    ((knh_methodn_t)229)
#define METHODN__term                   ((knh_methodn_t)229|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getTerm                 ((knh_methodn_t)229|KNH_FLAG_MN_GETTER)
#define METHODN_setTerm                 ((knh_methodn_t)229|KNH_FLAG_MN_SETTER)
#define FIELDN_this                     ((knh_fieldn_t)230)
#define METHODN_this                    ((knh_methodn_t)230)
#define METHODN__this                   ((knh_methodn_t)230|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getThis                 ((knh_methodn_t)230|KNH_FLAG_MN_GETTER)
#define METHODN_setThis                 ((knh_methodn_t)230|KNH_FLAG_MN_SETTER)
#define FIELDN_toLower                  ((knh_fieldn_t)231)
#define METHODN_toLower                 ((knh_methodn_t)231)
#define METHODN__toLower                ((knh_methodn_t)231|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getToLower              ((knh_methodn_t)231|KNH_FLAG_MN_GETTER)
#define METHODN_setToLower              ((knh_methodn_t)231|KNH_FLAG_MN_SETTER)
#define FIELDN_toUpper                  ((knh_fieldn_t)232)
#define METHODN_toUpper                 ((knh_methodn_t)232)
#define METHODN__toUpper                ((knh_methodn_t)232|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getToUpper              ((knh_methodn_t)232|KNH_FLAG_MN_GETTER)
#define METHODN_setToUpper              ((knh_methodn_t)232|KNH_FLAG_MN_SETTER)
#define FIELDN_trim                     ((knh_fieldn_t)233)
#define METHODN_trim                    ((knh_methodn_t)233)
#define METHODN__trim                   ((knh_methodn_t)233|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getTrim                 ((knh_methodn_t)233|KNH_FLAG_MN_GETTER)
#define METHODN_setTrim                 ((knh_methodn_t)233|KNH_FLAG_MN_SETTER)
#define FIELDN_typeof                   ((knh_fieldn_t)234)
#define METHODN_typeof                  ((knh_methodn_t)234)
#define METHODN__typeof                 ((knh_methodn_t)234|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getTypeof               ((knh_methodn_t)234|KNH_FLAG_MN_GETTER)
#define METHODN_setTypeof               ((knh_methodn_t)234|KNH_FLAG_MN_SETTER)
#define FIELDN_u                        ((knh_fieldn_t)235)
#define METHODN_u                       ((knh_methodn_t)235)
#define METHODN__u                      ((knh_methodn_t)235|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getU                    ((knh_methodn_t)235|KNH_FLAG_MN_GETTER)
#define METHODN_setU                    ((knh_methodn_t)235|KNH_FLAG_MN_SETTER)
#define FIELDN_unlikely                 ((knh_fieldn_t)236)
#define METHODN_unlikely                ((knh_methodn_t)236)
#define METHODN__unlikely               ((knh_methodn_t)236|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getUnlikely             ((knh_methodn_t)236|KNH_FLAG_MN_GETTER)
#define METHODN_setUnlikely             ((knh_methodn_t)236|KNH_FLAG_MN_SETTER)
#define FIELDN_unlink                   ((knh_fieldn_t)237)
#define METHODN_unlink                  ((knh_methodn_t)237)
#define METHODN__unlink                 ((knh_methodn_t)237|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getUnlink               ((knh_methodn_t)237|KNH_FLAG_MN_GETTER)
#define METHODN_setUnlink               ((knh_methodn_t)237|KNH_FLAG_MN_SETTER)
#define FIELDN_urn                      ((knh_fieldn_t)238)
#define METHODN_urn                     ((knh_methodn_t)238)
#define METHODN__urn                    ((knh_methodn_t)238|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getUrn                  ((knh_methodn_t)238|KNH_FLAG_MN_GETTER)
#define METHODN_setUrn                  ((knh_methodn_t)238|KNH_FLAG_MN_SETTER)
#define FIELDN_v                        ((knh_fieldn_t)239)
#define METHODN_v                       ((knh_methodn_t)239)
#define METHODN__v                      ((knh_methodn_t)239|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getV                    ((knh_methodn_t)239|KNH_FLAG_MN_GETTER)
#define METHODN_setV                    ((knh_methodn_t)239|KNH_FLAG_MN_SETTER)
#define FIELDN_value                    ((knh_fieldn_t)240)
#define METHODN_value                   ((knh_methodn_t)240)
#define METHODN__value                  ((knh_methodn_t)240|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getValue                ((knh_methodn_t)240|KNH_FLAG_MN_GETTER)
#define METHODN_setValue                ((knh_methodn_t)240|KNH_FLAG_MN_SETTER)
#define FIELDN_vargs                    ((knh_fieldn_t)241)
#define METHODN_vargs                   ((knh_methodn_t)241)
#define METHODN__vargs                  ((knh_methodn_t)241|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getVargs                ((knh_methodn_t)241|KNH_FLAG_MN_GETTER)
#define METHODN_setVargs                ((knh_methodn_t)241|KNH_FLAG_MN_SETTER)
#define FIELDN_verbose                  ((knh_fieldn_t)242)
#define METHODN_verbose                 ((knh_methodn_t)242)
#define METHODN__verbose                ((knh_methodn_t)242|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getVerbose              ((knh_methodn_t)242|KNH_FLAG_MN_GETTER)
#define METHODN_setVerbose              ((knh_methodn_t)242|KNH_FLAG_MN_SETTER)
#define FIELDN_w                        ((knh_fieldn_t)243)
#define METHODN_w                       ((knh_methodn_t)243)
#define METHODN__w                      ((knh_methodn_t)243|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getW                    ((knh_methodn_t)243|KNH_FLAG_MN_GETTER)
#define METHODN_setW                    ((knh_methodn_t)243|KNH_FLAG_MN_SETTER)
#define FIELDN_write                    ((knh_fieldn_t)244)
#define METHODN_write                   ((knh_methodn_t)244)
#define METHODN__write                  ((knh_methodn_t)244|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getWrite                ((knh_methodn_t)244|KNH_FLAG_MN_GETTER)
#define METHODN_setWrite                ((knh_methodn_t)244|KNH_FLAG_MN_SETTER)
#define FIELDN_x                        ((knh_fieldn_t)245)
#define METHODN_x                       ((knh_methodn_t)245)
#define METHODN__x                      ((knh_methodn_t)245|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getX                    ((knh_methodn_t)245|KNH_FLAG_MN_GETTER)
#define METHODN_setX                    ((knh_methodn_t)245|KNH_FLAG_MN_SETTER)
#define FIELDN_y                        ((knh_fieldn_t)246)
#define METHODN_y                       ((knh_methodn_t)246)
#define METHODN__y                      ((knh_methodn_t)246|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getY                    ((knh_methodn_t)246|KNH_FLAG_MN_GETTER)
#define METHODN_setY                    ((knh_methodn_t)246|KNH_FLAG_MN_SETTER)
#define FIELDN_z                        ((knh_fieldn_t)247)
#define METHODN_z                       ((knh_methodn_t)247)
#define METHODN__z                      ((knh_methodn_t)247|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getZ                    ((knh_methodn_t)247|KNH_FLAG_MN_GETTER)
#define METHODN_setZ                    ((knh_methodn_t)247|KNH_FLAG_MN_SETTER)
#define KNH_TFIELDN_SIZE                496

/* ======================================================================== */
/* [MFN] */
#define MFN_nThis_Int           0
#define MF_nThis_Int                    knh_tMethodField(ctx, MFN_nThis_Int)
#define MFN_nThis_nInt          1
#define MF_nThis_nInt                   knh_tMethodField(ctx, MFN_nThis_nInt)
#define MFN_nThis_Any1_         2
#define MF_nThis_Any1_                  knh_tMethodField(ctx, MFN_nThis_Any1_)
#define MFN_nThis_nInt_         3
#define MF_nThis_nInt_                  knh_tMethodField(ctx, MFN_nThis_nInt_)
#define MFN_nThis_nFloat_       4
#define MF_nThis_nFloat_                knh_tMethodField(ctx, MFN_nThis_nFloat_)
#define MFN_void_nAny1          5
#define MF_void_nAny1                   knh_tMethodField(ctx, MFN_void_nAny1)
#define MFN_void_nAny1_         6
#define MF_void_nAny1_                  knh_tMethodField(ctx, MFN_void_nAny1_)
#define MFN_void_nInt           7
#define MF_void_nInt                    knh_tMethodField(ctx, MFN_void_nInt)
#define MFN_void_nInt_          8
#define MF_void_nInt_                   knh_tMethodField(ctx, MFN_void_nInt_)
#define MFN_void_nFloat         9
#define MF_void_nFloat                  knh_tMethodField(ctx, MFN_void_nFloat)
#define MFN_void_nFloat_        10
#define MF_void_nFloat_                 knh_tMethodField(ctx, MFN_void_nFloat_)
#define MFN_nInt                11
#define MF_nInt                         knh_tMethodField(ctx, MFN_nInt)
#define MFN_nAny1_nInt          12
#define MF_nAny1_nInt                   knh_tMethodField(ctx, MFN_nAny1_nInt)
#define MFN_nInt_nInt           13
#define MF_nInt_nInt                    knh_tMethodField(ctx, MFN_nInt_nInt)
#define MFN_nFloat_nInt         14
#define MF_nFloat_nInt                  knh_tMethodField(ctx, MFN_nFloat_nInt)
#define MFN_void_nInt_nAny1     15
#define MF_void_nInt_nAny1              knh_tMethodField(ctx, MFN_void_nInt_nAny1)
#define MFN_void_nInt_nInt      16
#define MF_void_nInt_nInt               knh_tMethodField(ctx, MFN_void_nInt_nInt)
#define MFN_void_nInt_nFloat    17
#define MF_void_nInt_nFloat             knh_tMethodField(ctx, MFN_void_nInt_nFloat)
#define MFN_void_Any1           18
#define MF_void_Any1                    knh_tMethodField(ctx, MFN_void_Any1)
#define MFN_nThis_Int_Int       19
#define MF_nThis_Int_Int                knh_tMethodField(ctx, MFN_nThis_Int_Int)
#define MFN_void_nInt_Any1      20
#define MF_void_nInt_Any1               knh_tMethodField(ctx, MFN_void_nInt_Any1)
#define MFN_Any1                21
#define MF_Any1                         knh_tMethodField(ctx, MFN_Any1)
#define MFN_void                22
#define MF_void                         knh_tMethodField(ctx, MFN_void)
#define MFN_nInt_Any1           23
#define MF_nInt_Any1                    knh_tMethodField(ctx, MFN_nInt_Any1)
#define MFN_nBoolean_Any1       24
#define MF_nBoolean_Any1                knh_tMethodField(ctx, MFN_nBoolean_Any1)
#define MFN_void_ArrayCmp       25
#define MF_void_ArrayCmp                knh_tMethodField(ctx, MFN_void_ArrayCmp)
#define MFN_void_OutputStream_Any 26
#define MF_void_OutputStream_Any        knh_tMethodField(ctx, MFN_void_OutputStream_Any)
#define MFN_iAny1               27
#define MF_iAny1                        knh_tMethodField(ctx, MFN_iAny1)
#define MFN_iInt                28
#define MF_iInt                         knh_tMethodField(ctx, MFN_iInt)
#define MFN_nThis_nInt_nInt     29
#define MF_nThis_nInt_nInt              knh_tMethodField(ctx, MFN_nThis_nInt_nInt)
#define MFN_nThis_nInt_nInt_nInt 30
#define MF_nThis_nInt_nInt_nInt         knh_tMethodField(ctx, MFN_nThis_nInt_nInt_nInt)
#define MFN_Any1_nInt_nInt      31
#define MF_Any1_nInt_nInt               knh_tMethodField(ctx, MFN_Any1_nInt_nInt)
#define MFN_Any1_nInt_nInt_nInt 32
#define MF_Any1_nInt_nInt_nInt          knh_tMethodField(ctx, MFN_Any1_nInt_nInt_nInt)
#define MFN_void_nInt_nInt_Any1 33
#define MF_void_nInt_nInt_Any1          knh_tMethodField(ctx, MFN_void_nInt_nInt_Any1)
#define MFN_void_nInt_nInt_nInt_Any1 34
#define MF_void_nInt_nInt_nInt_Any1     knh_tMethodField(ctx, MFN_void_nInt_nInt_nInt_Any1)
#define MFN_nInt_nInt_nInt      35
#define MF_nInt_nInt_nInt               knh_tMethodField(ctx, MFN_nInt_nInt_nInt)
#define MFN_nInt_nInt_nInt_nInt 36
#define MF_nInt_nInt_nInt_nInt          knh_tMethodField(ctx, MFN_nInt_nInt_nInt_nInt)
#define MFN_void_nInt_nInt_nInt 37
#define MF_void_nInt_nInt_nInt          knh_tMethodField(ctx, MFN_void_nInt_nInt_nInt)
#define MFN_void_nInt_nInt_nInt_nInt 38
#define MF_void_nInt_nInt_nInt_nInt     knh_tMethodField(ctx, MFN_void_nInt_nInt_nInt_nInt)
#define MFN_nFloat_nInt_nInt    39
#define MF_nFloat_nInt_nInt             knh_tMethodField(ctx, MFN_nFloat_nInt_nInt)
#define MFN_nFloat_nInt_nInt_nInt 40
#define MF_nFloat_nInt_nInt_nInt        knh_tMethodField(ctx, MFN_nFloat_nInt_nInt_nInt)
#define MFN_void_nInt_nInt_nFloat 41
#define MF_void_nInt_nInt_nFloat        knh_tMethodField(ctx, MFN_void_nInt_nInt_nFloat)
#define MFN_void_nInt_nInt_nInt_nFloat 42
#define MF_void_nInt_nInt_nInt_nFloat   knh_tMethodField(ctx, MFN_void_nInt_nInt_nInt_nFloat)
#define MFN_nBytes_Int          43
#define MF_nBytes_Int                   knh_tMethodField(ctx, MFN_nBytes_Int)
#define MFN_void_nBytes_Int_Int 44
#define MF_void_nBytes_Int_Int          knh_tMethodField(ctx, MFN_void_nBytes_Int_Int)
#define MFN_void_Int_nBytes_Int_Int 45
#define MF_void_Int_nBytes_Int_Int      knh_tMethodField(ctx, MFN_void_Int_nBytes_Int_Int)
#define MFN_nConnection_nString 46
#define MF_nConnection_nString          knh_tMethodField(ctx, MFN_nConnection_nString)
#define MFN_nResultSet_nString  47
#define MF_nResultSet_nString           knh_tMethodField(ctx, MFN_nResultSet_nString)
#define MFN_void_nString        48
#define MF_void_nString                 knh_tMethodField(ctx, MFN_void_nString)
#define MFN_nInt_nAny           49
#define MF_nInt_nAny                    knh_tMethodField(ctx, MFN_nInt_nAny)
#define MFN_nString_nInt        50
#define MF_nString_nInt                 knh_tMethodField(ctx, MFN_nString_nInt)
#define MFN_Int_nAny            51
#define MF_Int_nAny                     knh_tMethodField(ctx, MFN_Int_nAny)
#define MFN_Float_nAny          52
#define MF_Float_nAny                   knh_tMethodField(ctx, MFN_Float_nAny)
#define MFN_String_nAny         53
#define MF_String_nAny                  knh_tMethodField(ctx, MFN_String_nAny)
#define MFN_Any_nAny            54
#define MF_Any_nAny                     knh_tMethodField(ctx, MFN_Any_nAny)
#define MFN_Any1_nString        55
#define MF_Any1_nString                 knh_tMethodField(ctx, MFN_Any1_nString)
#define MFN_nBoolean_nString    56
#define MF_nBoolean_nString             knh_tMethodField(ctx, MFN_nBoolean_nString)
#define MFN_void_nString_Any1   57
#define MF_void_nString_Any1            knh_tMethodField(ctx, MFN_void_nString_Any1)
#define MFN_void_Any_           58
#define MF_void_Any_                    knh_tMethodField(ctx, MFN_void_Any_)
#define MFN_iString             59
#define MF_iString                      knh_tMethodField(ctx, MFN_iString)
#define MFN_nInt_nString        60
#define MF_nInt_nString                 knh_tMethodField(ctx, MFN_nInt_nString)
#define MFN_void_nString_nInt   61
#define MF_void_nString_nInt            knh_tMethodField(ctx, MFN_void_nString_nInt)
#define MFN_void_String_        62
#define MF_void_String_                 knh_tMethodField(ctx, MFN_void_String_)
#define MFN_Any2_Any1           63
#define MF_Any2_Any1                    knh_tMethodField(ctx, MFN_Any2_Any1)
#define MFN_void_nAny1_Any2     64
#define MF_void_nAny1_Any2              knh_tMethodField(ctx, MFN_void_nAny1_Any2)
#define MFN_nBoolean            65
#define MF_nBoolean                     knh_tMethodField(ctx, MFN_nBoolean)
#define MFN_nBoolean_nInt       66
#define MF_nBoolean_nInt                knh_tMethodField(ctx, MFN_nBoolean_nInt)
#define MFN_nInt_nInt_          67
#define MF_nInt_nInt_                   knh_tMethodField(ctx, MFN_nInt_nInt_)
#define MFN_nInt_Int            68
#define MF_nInt_Int                     knh_tMethodField(ctx, MFN_nInt_Int)
#define MFN_nFloat_nFloat       69
#define MF_nFloat_nFloat                knh_tMethodField(ctx, MFN_nFloat_nFloat)
#define MFN_nFloat              70
#define MF_nFloat                       knh_tMethodField(ctx, MFN_nFloat)
#define MFN_nBoolean_Float      71
#define MF_nBoolean_Float               knh_tMethodField(ctx, MFN_nBoolean_Float)
#define MFN_nBoolean_nFloat     72
#define MF_nBoolean_nFloat              knh_tMethodField(ctx, MFN_nBoolean_nFloat)
#define MFN_nInt_nFloat         73
#define MF_nInt_nFloat                  knh_tMethodField(ctx, MFN_nInt_nFloat)
#define MFN_nThis_Any_          74
#define MF_nThis_Any_                   knh_tMethodField(ctx, MFN_nThis_Any_)
#define MFN_nBoolean_Any        75
#define MF_nBoolean_Any                 knh_tMethodField(ctx, MFN_nBoolean_Any)
#define MFN_nBoolean_nClass     76
#define MF_nBoolean_nClass              knh_tMethodField(ctx, MFN_nBoolean_nClass)
#define MFN_nClass              77
#define MF_nClass                       knh_tMethodField(ctx, MFN_nClass)
#define MFN_iThis               78
#define MF_iThis                        knh_tMethodField(ctx, MFN_iThis)
#define MFN_nArray              79
#define MF_nArray                       knh_tMethodField(ctx, MFN_nArray)
#define MFN_InputStream_nString_String 80
#define MF_InputStream_nString_String   knh_tMethodField(ctx, MFN_InputStream_nString_String)
#define MFN_nInt_nBytes_Int_Int 81
#define MF_nInt_nBytes_Int_Int          knh_tMethodField(ctx, MFN_nInt_nBytes_Int_Int)
#define MFN_nString             82
#define MF_nString                      knh_tMethodField(ctx, MFN_nString)
#define MFN_OutputStream_nString_String 83
#define MF_OutputStream_nString_String  knh_tMethodField(ctx, MFN_OutputStream_nString_String)
#define MFN_void_Any            84
#define MF_void_Any                     knh_tMethodField(ctx, MFN_void_Any)
#define MFN_nSocket_nString_nInt 85
#define MF_nSocket_nString_nInt         knh_tMethodField(ctx, MFN_nSocket_nString_nInt)
#define MFN_nInputStream        86
#define MF_nInputStream                 knh_tMethodField(ctx, MFN_nInputStream)
#define MFN_nOutputStream       87
#define MF_nOutputStream                knh_tMethodField(ctx, MFN_nOutputStream)
#define MFN_void_String         88
#define MF_void_String                  knh_tMethodField(ctx, MFN_void_String)
#define MFN_nString_nBytes_String 89
#define MF_nString_nBytes_String        knh_tMethodField(ctx, MFN_nString_nBytes_String)
#define MFN_nBytes_String       90
#define MF_nBytes_String                knh_tMethodField(ctx, MFN_nBytes_String)
#define MFN_nString_Any         91
#define MF_nString_Any                  knh_tMethodField(ctx, MFN_nString_Any)
#define MFN_nString_nString     92
#define MF_nString_nString              knh_tMethodField(ctx, MFN_nString_nString)
#define MFN_nString_Any_        93
#define MF_nString_Any_                 knh_tMethodField(ctx, MFN_nString_Any_)
#define MFN_nString_String      94
#define MF_nString_String               knh_tMethodField(ctx, MFN_nString_String)
#define MFN_nString_nString_nString 95
#define MF_nString_nString_nString      knh_tMethodField(ctx, MFN_nString_nString_nString)
#define MFN_nString_Int_Int     96
#define MF_nString_Int_Int              knh_tMethodField(ctx, MFN_nString_Int_Int)
#define MFN_aString_String_Int  97
#define MF_aString_String_Int           knh_tMethodField(ctx, MFN_aString_String_Int)
#define MFN_Regex_nString_String 98
#define MF_Regex_nString_String         knh_tMethodField(ctx, MFN_Regex_nString_String)
#define MFN_nBoolean_nRegex     99
#define MF_nBoolean_nRegex              knh_tMethodField(ctx, MFN_nBoolean_nRegex)
#define MFN_aString_Regex       100
#define MF_aString_Regex                knh_tMethodField(ctx, MFN_aString_Regex)
#define MFN_void_InputStream    101
#define MF_void_InputStream             knh_tMethodField(ctx, MFN_void_InputStream)
#define MFN_void_OutputStream   102
#define MF_void_OutputStream            knh_tMethodField(ctx, MFN_void_OutputStream)
#define MFN_void_Int            103
#define MF_void_Int                     knh_tMethodField(ctx, MFN_void_Int)
#define MFN_Any_nString         104
#define MF_Any_nString                  knh_tMethodField(ctx, MFN_Any_nString)
#define MFN_void_nString_Any    105
#define MF_void_nString_Any             knh_tMethodField(ctx, MFN_void_nString_Any)
#define MFN_naString_String     106
#define MF_naString_String              knh_tMethodField(ctx, MFN_naString_String)
#define MFN_nException_String_Any 107
#define MF_nException_String_Any        knh_tMethodField(ctx, MFN_nException_String_Any)
#define MFN_nThis_nAny_nMethod  108
#define MF_nThis_nAny_nMethod           knh_tMethodField(ctx, MFN_nThis_nAny_nMethod)
#define MFN_Any0_Any1_Any2_Any3 109
#define MF_Any0_Any1_Any2_Any3          knh_tMethodField(ctx, MFN_Any0_Any1_Any2_Any3)
#define MFN_nException_String_String_Object 110
#define MF_nException_String_String_Object knh_tMethodField(ctx, MFN_nException_String_String_Object)
#define MFN_String              111
#define MF_String                       knh_tMethodField(ctx, MFN_String)
#define MFN_nThis               112
#define MF_nThis                        knh_tMethodField(ctx, MFN_nThis)
#define MFN_void_String_String_Int 113
#define MF_void_String_String_Int       knh_tMethodField(ctx, MFN_void_String_String_Int)
#define MFN_String_String       114
#define MF_String_String                knh_tMethodField(ctx, MFN_String_String)
#define MFN_Boolean_nClass      115
#define MF_Boolean_nClass               knh_tMethodField(ctx, MFN_Boolean_nClass)
#define MFN_void_Boolean        116
#define MF_void_Boolean                 knh_tMethodField(ctx, MFN_void_Boolean)
#define KNH_TMETHODFIELD_SIZE   117
#define EXPT_Exception          1
#define EXPT_Fatal              2
#define EXPT_OutOfMemory        3
#define EXPT_Security           4
#define EXPT_Null               5
#define EXPT_OutOfIndex         6
#define EXPT_IO                 7
#define EXPT_Script             8
#define EXPT_Syntax             9
#define EXPT_Type               10

/* ======================================================================== */
/* [KNH_CLASS_T] */

typedef struct knh_Iterator_t {
	knh_hObject_t h;
	knh_Iterator_struct *b;
	knh_fitrnext fnext_1;
} knh_Iterator_t; 

typedef struct knh_HashMap_t {
	knh_hObject_t h;
	knh_HashMap_struct *b;
} knh_HashMap_t; 

typedef struct knh_HashSet_t {
	knh_hObject_t h;
	knh_HashSet_struct *b;
} knh_HashSet_t; 

typedef struct knh_Method_t {
	knh_hObject_t h;
	knh_Method_struct *b;
	knh_fmethod fcall_1;
	knh_code_t *pc_start;
} knh_Method_t; 

typedef struct knh_Mapper_t {
	knh_hObject_t h;
	knh_Mapper_struct *b;
	knh_fmapper fmap_1;
} knh_Mapper_t; 

typedef struct knh_ClassMap_t {
	knh_hObject_t h;
	knh_ClassMap_struct *b;
} knh_ClassMap_t; 

typedef struct knh_Closure_t {
	knh_hObject_t h;
	knh_Closure_struct *b;
	knh_fmethod finvoke_1;
	knh_fmethod fcallcc_2;
} knh_Closure_t; 

typedef struct knh_ClassSpec_t {
	knh_hObject_t h;
	knh_ClassSpec_struct *b;
} knh_ClassSpec_t; 

typedef struct knh_InputStream_t {
	knh_hObject_t h;
	knh_InputStream_struct *b;
} knh_InputStream_t; 

typedef struct knh_OutputStream_t {
	knh_hObject_t h;
	knh_OutputStream_struct *b;
} knh_OutputStream_t; 

typedef struct knh_Socket_t {
	knh_hObject_t h;
	knh_Socket_struct *b;
} knh_Socket_t; 

typedef struct knh_Connection_t {
	knh_hObject_t h;
	knh_Connection_struct *b;
} knh_Connection_t; 

typedef struct knh_ResultSet_t {
	knh_hObject_t h;
	knh_ResultSet_struct *b;
} knh_ResultSet_t; 

typedef struct knh_Exception_t {
	knh_hObject_t h;
	knh_Exception_struct *b;
} knh_Exception_t; 

typedef struct knh_ExceptionHandler_t {
	knh_hObject_t h;
	knh_ExceptionHandler_struct *b;
} knh_ExceptionHandler_t; 

typedef struct knh_NameSpace_t {
	knh_hObject_t h;
	knh_NameSpace_struct *b;
} knh_NameSpace_t; 

typedef struct knh_System_t {
	knh_hObject_t h;
	knh_System_struct *b;
} knh_System_t; 

typedef struct knh_Token_t {
	knh_hObject_t h;
	knh_Token_struct *b;
	knh_fileid_t fileid;
	knh_ushort_t line;
	knh_flag_t flag;
	knh_token_t  tt;
} knh_Token_t; 

typedef struct knh_Stmt_t {
	knh_hObject_t h;
	knh_Stmt_struct *b;
	knh_fileid_t fileid;
	knh_ushort_t line;
	knh_flag_t flag;
	knh_stmt_t  stt;
} knh_Stmt_t; 

typedef struct knh_Asm_t {
	knh_hObject_t h;
	knh_Asm_struct *b;
	knh_fileid_t fileid;
	knh_ushort_t line;
} knh_Asm_t; 

typedef struct knh_KLRCode_t {
	knh_hObject_t h;
	knh_KLRCode_struct *b;
	knh_fileid_t fileid;
	knh_ushort_t line;
} knh_KLRCode_t; 

/* ======================================================================== */

#ifdef __cplusplus
}
#endif

/* ======================================================================== */

#endif/*KONOHA_CLASS__H*/
