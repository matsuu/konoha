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

#ifndef KONOHA_NAME__H
#define KONOHA_NAME__H

#include<konoha/konoha_config.h>
#include<konoha/konoha_t.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

/* ======================================================================== */
/* [flag] */

/* ------------------------------------------------------------------------ */
/* Token */
#define KNH_FLAG_TKF_TAILC              KNH_FLAG0

#define knh_Token_isTailC(o)  \
	(((o)->flag & KNH_FLAG_TKF_TAILC) == KNH_FLAG_TKF_TAILC)

#define knh_Token_setTailC(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_TKF_TAILC; else (o)->flag &= ~(KNH_FLAG_TKF_TAILC);

#define KNH_FLAG_TKF_TOPDOT             KNH_FLAG1

#define knh_Token_isTopDot(o)  \
	(((o)->flag & KNH_FLAG_TKF_TOPDOT) == KNH_FLAG_TKF_TOPDOT)

#define knh_Token_setTopDot(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_TKF_TOPDOT; else (o)->flag &= ~(KNH_FLAG_TKF_TOPDOT);

#define KNH_FLAG_TKF_EXCEPTIONTYPE      KNH_FLAG2

#define knh_Token_isExceptionType(o)  \
	(((o)->flag & KNH_FLAG_TKF_EXCEPTIONTYPE) == KNH_FLAG_TKF_EXCEPTIONTYPE)

#define knh_Token_setExceptionType(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_TKF_EXCEPTIONTYPE; else (o)->flag &= ~(KNH_FLAG_TKF_EXCEPTIONTYPE);

#define KNH_FLAG_TKF_NOTNULLTYPE        KNH_FLAG3

#define knh_Token_isNotNullType(o)  \
	(((o)->flag & KNH_FLAG_TKF_NOTNULLTYPE) == KNH_FLAG_TKF_NOTNULLTYPE)

#define knh_Token_setNotNullType(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_TKF_NOTNULLTYPE; else (o)->flag &= ~(KNH_FLAG_TKF_NOTNULLTYPE);

#define KNH_FLAG_TKF_ITERATORTYPE       KNH_FLAG4

#define knh_Token_isIteratorType(o)  \
	(((o)->flag & KNH_FLAG_TKF_ITERATORTYPE) == KNH_FLAG_TKF_ITERATORTYPE)

#define knh_Token_setIteratorType(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_TKF_ITERATORTYPE; else (o)->flag &= ~(KNH_FLAG_TKF_ITERATORTYPE);

#define KNH_FLAG_TKF_ARRAYTYPE          KNH_FLAG5

#define knh_Token_isArrayType(o)  \
	(((o)->flag & KNH_FLAG_TKF_ARRAYTYPE) == KNH_FLAG_TKF_ARRAYTYPE)

#define knh_Token_setArrayType(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_TKF_ARRAYTYPE; else (o)->flag &= ~(KNH_FLAG_TKF_ARRAYTYPE);

#define KNH_FLAG_TKF_NEXTPARENTHESIS    KNH_FLAG6

#define knh_Token_isNextParenthesis(o)  \
	(((o)->flag & KNH_FLAG_TKF_NEXTPARENTHESIS) == KNH_FLAG_TKF_NEXTPARENTHESIS)

#define knh_Token_setNextParenthesis(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_TKF_NEXTPARENTHESIS; else (o)->flag &= ~(KNH_FLAG_TKF_NEXTPARENTHESIS);

#define KNH_FLAG_TKF_NEXTBRACE          KNH_FLAG7

#define knh_Token_isNextBrace(o)  \
	(((o)->flag & KNH_FLAG_TKF_NEXTBRACE) == KNH_FLAG_TKF_NEXTBRACE)

#define knh_Token_setNextBrace(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_TKF_NEXTBRACE; else (o)->flag &= ~(KNH_FLAG_TKF_NEXTBRACE);

#define KNH_FLAG_TKF_NEXTBRANCET        KNH_FLAG8

#define knh_Token_isNextBrancet(o)  \
	(((o)->flag & KNH_FLAG_TKF_NEXTBRANCET) == KNH_FLAG_TKF_NEXTBRANCET)

#define knh_Token_setNextBrancet(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_TKF_NEXTBRANCET; else (o)->flag &= ~(KNH_FLAG_TKF_NEXTBRANCET);

#define KNH_FLAG_TKF_TOGET              KNH_FLAG9

#define knh_Token_isToGet(o)  \
	(((o)->flag & KNH_FLAG_TKF_TOGET) == KNH_FLAG_TKF_TOGET)

#define knh_Token_setToGet(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_TKF_TOGET; else (o)->flag &= ~(KNH_FLAG_TKF_TOGET);

#define KNH_FLAG_TKF_TOSET              KNH_FLAG10

#define knh_Token_isToSet(o)  \
	(((o)->flag & KNH_FLAG_TKF_TOSET) == KNH_FLAG_TKF_TOSET)

#define knh_Token_setToSet(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_TKF_TOSET; else (o)->flag &= ~(KNH_FLAG_TKF_TOSET);

#define KNH_FLAG_TKF_GENERATED          KNH_FLAG11

#define knh_Token_isGenerated(o)  \
	(((o)->flag & KNH_FLAG_TKF_GENERATED) == KNH_FLAG_TKF_GENERATED)

#define knh_Token_setGenerated(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_TKF_GENERATED; else (o)->flag &= ~(KNH_FLAG_TKF_GENERATED);

#define KNH_FLAG_TKF_PERRORED           KNH_FLAG12

#define knh_Token_isPerrored(o)  \
	(((o)->flag & KNH_FLAG_TKF_PERRORED) == KNH_FLAG_TKF_PERRORED)

#define knh_Token_setPerrored(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_TKF_PERRORED; else (o)->flag &= ~(KNH_FLAG_TKF_PERRORED);


/* ------------------------------------------------------------------------ */
/* Stmt */
#define KNH_FLAG_STMTF_ADPOSITION       KNH_FLAG0

#define knh_Stmt_isAdposition(o)  \
	(((o)->flag & KNH_FLAG_STMTF_ADPOSITION) == KNH_FLAG_STMTF_ADPOSITION)

#define knh_Stmt_setAdposition(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_STMTF_ADPOSITION; else (o)->flag &= ~(KNH_FLAG_STMTF_ADPOSITION);

#define KNH_FLAG_STMTF_PRINTLINE        KNH_FLAG1

#define knh_Stmt_isPrintLine(o)  \
	(((o)->flag & KNH_FLAG_STMTF_PRINTLINE) == KNH_FLAG_STMTF_PRINTLINE)

#define knh_Stmt_setPrintLine(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_STMTF_PRINTLINE; else (o)->flag &= ~(KNH_FLAG_STMTF_PRINTLINE);

#define KNH_FLAG_STMTF_OPNEXT           KNH_FLAG2

#define knh_Stmt_isOpNext(o)  \
	(((o)->flag & KNH_FLAG_STMTF_OPNEXT) == KNH_FLAG_STMTF_OPNEXT)

#define knh_Stmt_setOpNext(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_STMTF_OPNEXT; else (o)->flag &= ~(KNH_FLAG_STMTF_OPNEXT);

#define KNH_FLAG_STMTF_OPPREV           KNH_FLAG3

#define knh_Stmt_isOpPrev(o)  \
	(((o)->flag & KNH_FLAG_STMTF_OPPREV) == KNH_FLAG_STMTF_OPPREV)

#define knh_Stmt_setOpPrev(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_STMTF_OPPREV; else (o)->flag &= ~(KNH_FLAG_STMTF_OPPREV);

#define KNH_FLAG_STMTF_VISIBLE          KNH_FLAG4

#define knh_Stmt_isVisible(o)  \
	(((o)->flag & KNH_FLAG_STMTF_VISIBLE) == KNH_FLAG_STMTF_VISIBLE)

#define knh_Stmt_setVisible(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_STMTF_VISIBLE; else (o)->flag &= ~(KNH_FLAG_STMTF_VISIBLE);


/* ------------------------------------------------------------------------ */
/* Cmpl */
#define KNH_FLAG_CPF_SYNTAXERROR        KNH_FLAG0

#define knh_Cmpl_isSyntaxError(o)  \
	(((o)->flag & KNH_FLAG_CPF_SYNTAXERROR) == KNH_FLAG_CPF_SYNTAXERROR)

#define knh_Cmpl_setSyntaxError(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_CPF_SYNTAXERROR; else (o)->flag &= ~(KNH_FLAG_CPF_SYNTAXERROR);

#define KNH_FLAG_CPF_TYPEERROR          KNH_FLAG1

#define knh_Cmpl_isTypeError(o)  \
	(((o)->flag & KNH_FLAG_CPF_TYPEERROR) == KNH_FLAG_CPF_TYPEERROR)

#define knh_Cmpl_setTypeError(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_CPF_TYPEERROR; else (o)->flag &= ~(KNH_FLAG_CPF_TYPEERROR);

#define KNH_FLAG_CPF_CANCELLED          KNH_FLAG2

#define knh_Cmpl_isCancelled(o)  \
	(((o)->flag & KNH_FLAG_CPF_CANCELLED) == KNH_FLAG_CPF_CANCELLED)

#define knh_Cmpl_setCancelled(o,b)  \
	if(b) (o)->flag |= KNH_FLAG_CPF_CANCELLED; else (o)->flag &= ~(KNH_FLAG_CPF_CANCELLED);


/* ------------------------------------------------------------------------ */
/* Nue */
#define KNH_FLAG_NUE_GCHOOK             KNH_FLAG_OF_LOCAL1

#define knh_Nue_isGCHook(o)  \
	((knh_Object_head(o)->flag & KNH_FLAG_NUE_GCHOOK) == KNH_FLAG_NUE_GCHOOK)

#define knh_Nue_setGCHook(o,b)  \
	if(b) knh_Object_head(o)->flag |= KNH_FLAG_NUE_GCHOOK; else knh_Object_head(o)->flag &= ~(KNH_FLAG_NUE_GCHOOK);

#define KNH_FLAG_NUE_OBJECTTEXT         KNH_FLAG_OF_LOCAL2

#define knh_Nue_isObjectText(o)  \
	((knh_Object_head(o)->flag & KNH_FLAG_NUE_OBJECTTEXT) == KNH_FLAG_NUE_OBJECTTEXT)

#define knh_Nue_setObjectText(o,b)  \
	if(b) knh_Object_head(o)->flag |= KNH_FLAG_NUE_OBJECTTEXT; else knh_Object_head(o)->flag &= ~(KNH_FLAG_NUE_OBJECTTEXT);


/* ------------------------------------------------------------------------ */
/* String */
#define KNH_FLAG_STRING_STEXT           KNH_FLAG_OF_LOCAL1

#define knh_String_isSTEXT(o)  \
	((knh_Object_head(o)->flag & KNH_FLAG_STRING_STEXT) == KNH_FLAG_STRING_STEXT)

#define knh_String_setSTEXT(o,b)  \
	if(b) knh_Object_head(o)->flag |= KNH_FLAG_STRING_STEXT; else knh_Object_head(o)->flag &= ~(KNH_FLAG_STRING_STEXT);


/* ------------------------------------------------------------------------ */
/* Bytes */
#define KNH_FLAG_BYTES_STACKBUFFER      KNH_FLAG_OF_LOCAL1

#define knh_Bytes_isStackBuffer(o)  \
	((knh_Object_head(o)->flag & KNH_FLAG_BYTES_STACKBUFFER) == KNH_FLAG_BYTES_STACKBUFFER)

#define knh_Bytes_setStackBuffer(o,b)  \
	if(b) knh_Object_head(o)->flag |= KNH_FLAG_BYTES_STACKBUFFER; else knh_Object_head(o)->flag &= ~(KNH_FLAG_BYTES_STACKBUFFER);


/* ------------------------------------------------------------------------ */
/* Object */
#define KNH_FLAG_OF_RELEASE             KNH_FLAG0

#define knh_Object_isRelease(o)  \
	((knh_Object_head(o)->flag & KNH_FLAG_OF_RELEASE) == KNH_FLAG_OF_RELEASE)

#define knh_Object_isDebug(o)   \
	((knh_Object_head(o)->flag & KNH_FLAG_OF_RELEASE) != KNH_FLAG_OF_RELEASE)
#define KNH_FLAG_OF_IMMUTABLE           KNH_FLAG1

#define knh_Object_isImmutable(o)  \
	((knh_Object_head(o)->flag & KNH_FLAG_OF_IMMUTABLE) == KNH_FLAG_OF_IMMUTABLE)
#define KNH_FLAG_OF_METADATA            KNH_FLAG2

#define knh_Object_hasMetaData(o)  \
	((knh_Object_head(o)->flag & KNH_FLAG_OF_METADATA) == KNH_FLAG_OF_METADATA)

#define knh_Object_setMetaData(o,b)  \
	if(b) knh_Object_head(o)->flag |= KNH_FLAG_OF_METADATA; else knh_Object_head(o)->flag &= ~(KNH_FLAG_OF_METADATA);

#define KNH_FLAG_OF_SYNCHRONIZED        KNH_FLAG3

#define knh_Object_isSynchronized(o)  \
	((knh_Object_head(o)->flag & KNH_FLAG_OF_SYNCHRONIZED) == KNH_FLAG_OF_SYNCHRONIZED)
#define KNH_FLAG_OF_MODIFIED            KNH_FLAG4

#define knh_Object_isModified(o)  \
	((knh_Object_head(o)->flag & KNH_FLAG_OF_MODIFIED) == KNH_FLAG_OF_MODIFIED)

#define knh_Object_setModified(o,b)  \
	if(b) knh_Object_head(o)->flag |= KNH_FLAG_OF_MODIFIED; else knh_Object_head(o)->flag &= ~(KNH_FLAG_OF_MODIFIED);

#define KNH_FLAG_OF_LOCAL4              KNH_FLAG5

#define knh_Object_isLocal4(o)  \
	((knh_Object_head(o)->flag & KNH_FLAG_OF_LOCAL4) == KNH_FLAG_OF_LOCAL4)

#define knh_Object_setLocal4(o,b)  \
	if(b) knh_Object_head(o)->flag |= KNH_FLAG_OF_LOCAL4; else knh_Object_head(o)->flag &= ~(KNH_FLAG_OF_LOCAL4);

#define KNH_FLAG_OF_LOCAL3              KNH_FLAG6

#define knh_Object_isLocal3(o)  \
	((knh_Object_head(o)->flag & KNH_FLAG_OF_LOCAL3) == KNH_FLAG_OF_LOCAL3)

#define knh_Object_setLocal3(o,b)  \
	if(b) knh_Object_head(o)->flag |= KNH_FLAG_OF_LOCAL3; else knh_Object_head(o)->flag &= ~(KNH_FLAG_OF_LOCAL3);

#define KNH_FLAG_OF_LOCAL2              KNH_FLAG7

#define knh_Object_isLocal2(o)  \
	((knh_Object_head(o)->flag & KNH_FLAG_OF_LOCAL2) == KNH_FLAG_OF_LOCAL2)

#define knh_Object_setLocal2(o,b)  \
	if(b) knh_Object_head(o)->flag |= KNH_FLAG_OF_LOCAL2; else knh_Object_head(o)->flag &= ~(KNH_FLAG_OF_LOCAL2);

#define KNH_FLAG_OF_LOCAL1              KNH_FLAG8

#define knh_Object_isLocal1(o)  \
	((knh_Object_head(o)->flag & KNH_FLAG_OF_LOCAL1) == KNH_FLAG_OF_LOCAL1)

#define knh_Object_setLocal1(o,b)  \
	if(b) knh_Object_head(o)->flag |= KNH_FLAG_OF_LOCAL1; else knh_Object_head(o)->flag &= ~(KNH_FLAG_OF_LOCAL1);


/* ------------------------------------------------------------------------ */
/* Class */
#define KNH_FLAG_CF_RELEASE             KNH_FLAG0

#define knh_class_isRelease(o)  \
	((knh_tclass_table(o)->cflag & KNH_FLAG_CF_RELEASE) == KNH_FLAG_CF_RELEASE)

#define knh_class_isDebug(o)   \
	((knh_tclass_table(o)->cflag & KNH_FLAG_CF_RELEASE) != KNH_FLAG_CF_RELEASE)
#define KNH_FLAG_CF_IMMUTABLE           KNH_FLAG1

#define knh_class_isImmutable(o)  \
	((knh_tclass_table(o)->cflag & KNH_FLAG_CF_IMMUTABLE) == KNH_FLAG_CF_IMMUTABLE)
#define KNH_FLAG_CF_METAEXTENSIBLE      KNH_FLAG2

#define knh_class_isMetaExtensible(o)  \
	((knh_tclass_table(o)->cflag & KNH_FLAG_CF_METAEXTENSIBLE) == KNH_FLAG_CF_METAEXTENSIBLE)
#define KNH_FLAG_CF_PRIVATE             KNH_FLAG3

#define knh_class_isPrivate(o)  \
	((knh_tclass_table(o)->cflag & KNH_FLAG_CF_PRIVATE) == KNH_FLAG_CF_PRIVATE)

#define knh_class_isPublic(o)   \
	((knh_tclass_table(o)->cflag & KNH_FLAG_CF_PRIVATE) != KNH_FLAG_CF_PRIVATE)
#define KNH_FLAG_CF_FINAL               KNH_FLAG4

#define knh_class_isFinal(o)  \
	((knh_tclass_table(o)->cflag & KNH_FLAG_CF_FINAL) == KNH_FLAG_CF_FINAL)
#define KNH_FLAG_CF_STRICT              KNH_FLAG5

#define knh_class_isStrict(o)  \
	((knh_tclass_table(o)->cflag & KNH_FLAG_CF_STRICT) == KNH_FLAG_CF_STRICT)
#define KNH_FLAG_CF_SYSTEM              KNH_FLAG6

#define knh_class_isSystem(o)  \
	((knh_tclass_table(o)->cflag & KNH_FLAG_CF_SYSTEM) == KNH_FLAG_CF_SYSTEM)
#define KNH_FLAG_CF_NULLOBJECT          KNH_FLAG7

#define knh_class_isNullObject(o)  \
	((knh_tclass_table(o)->cflag & KNH_FLAG_CF_NULLOBJECT) == KNH_FLAG_CF_NULLOBJECT)
#define KNH_FLAG_CF_NA                  KNH_FLAG8

#define knh_class_isNA(o)  \
	((knh_tclass_table(o)->cflag & KNH_FLAG_CF_NA) == KNH_FLAG_CF_NA)

/* ------------------------------------------------------------------------ */
/* ClassStruct */
#define KNH_FLAG_CFF_HIDDEN             KNH_FLAG0

#define knh_ClassStruct_isHidden(o,n)  \
	((((ClassStruct)o)->fields[n].flag & KNH_FLAG_CFF_HIDDEN) == KNH_FLAG_CFF_HIDDEN)

#define knh_ClassStruct_setHidden(o,n,b)  \
	if(b) ((ClassStruct)o)->fields[n].flag |= KNH_FLAG_CFF_HIDDEN; else ((ClassStruct)o)->fields[n].flag &= ~(KNH_FLAG_CFF_HIDDEN);

#define KNH_FLAG_CFF_AUTONAME           KNH_FLAG1

#define knh_ClassStruct_isAutoName(o,n)  \
	((((ClassStruct)o)->fields[n].flag & KNH_FLAG_CFF_AUTONAME) == KNH_FLAG_CFF_AUTONAME)

#define knh_ClassStruct_setAutoName(o,n,b)  \
	if(b) ((ClassStruct)o)->fields[n].flag |= KNH_FLAG_CFF_AUTONAME; else ((ClassStruct)o)->fields[n].flag &= ~(KNH_FLAG_CFF_AUTONAME);

#define KNH_FLAG_CFF_SAFEVALUE          KNH_FLAG2

#define knh_ClassStruct_isSafeValue(o,n)  \
	((((ClassStruct)o)->fields[n].flag & KNH_FLAG_CFF_SAFEVALUE) == KNH_FLAG_CFF_SAFEVALUE)

#define knh_ClassStruct_setSafeValue(o,n,b)  \
	if(b) ((ClassStruct)o)->fields[n].flag |= KNH_FLAG_CFF_SAFEVALUE; else ((ClassStruct)o)->fields[n].flag &= ~(KNH_FLAG_CFF_SAFEVALUE);

#define KNH_FLAG_CFF_PROTECTED          KNH_FLAG3

#define knh_ClassStruct_isProtected(o,n)  \
	((((ClassStruct)o)->fields[n].flag & KNH_FLAG_CFF_PROTECTED) == KNH_FLAG_CFF_PROTECTED)

#define knh_ClassStruct_setProtected(o,n,b)  \
	if(b) ((ClassStruct)o)->fields[n].flag |= KNH_FLAG_CFF_PROTECTED; else ((ClassStruct)o)->fields[n].flag &= ~(KNH_FLAG_CFF_PROTECTED);

#define KNH_FLAG_CFF_GETTER             KNH_FLAG4

#define knh_ClassStruct_isGetter(o,n)  \
	((((ClassStruct)o)->fields[n].flag & KNH_FLAG_CFF_GETTER) == KNH_FLAG_CFF_GETTER)

#define knh_ClassStruct_setGetter(o,n,b)  \
	if(b) ((ClassStruct)o)->fields[n].flag |= KNH_FLAG_CFF_GETTER; else ((ClassStruct)o)->fields[n].flag &= ~(KNH_FLAG_CFF_GETTER);

#define KNH_FLAG_CFF_SETTER             KNH_FLAG5

#define knh_ClassStruct_isSetter(o,n)  \
	((((ClassStruct)o)->fields[n].flag & KNH_FLAG_CFF_SETTER) == KNH_FLAG_CFF_SETTER)

#define knh_ClassStruct_setSetter(o,n,b)  \
	if(b) ((ClassStruct)o)->fields[n].flag |= KNH_FLAG_CFF_SETTER; else ((ClassStruct)o)->fields[n].flag &= ~(KNH_FLAG_CFF_SETTER);

#define KNH_FLAG_CFF_KEY                KNH_FLAG6

#define knh_ClassStruct_isKey(o,n)  \
	((((ClassStruct)o)->fields[n].flag & KNH_FLAG_CFF_KEY) == KNH_FLAG_CFF_KEY)

#define knh_ClassStruct_setKey(o,n,b)  \
	if(b) ((ClassStruct)o)->fields[n].flag |= KNH_FLAG_CFF_KEY; else ((ClassStruct)o)->fields[n].flag &= ~(KNH_FLAG_CFF_KEY);


/* ------------------------------------------------------------------------ */
/* Method */
#define KNH_FLAG_MF_PUBLIC              KNH_FLAG0

#define knh_Method_isPublic(o)  \
	((((Method*)o)->flag & KNH_FLAG_MF_PUBLIC) == KNH_FLAG_MF_PUBLIC)

#define knh_Method_isPrivate(o)   \
	((((Method*)o)->flag & KNH_FLAG_MF_PUBLIC) != KNH_FLAG_MF_PUBLIC)

#define knh_Method_setPublic(o,b)  \
	if(b) ((Method*)o)->flag |= KNH_FLAG_MF_PUBLIC; else ((Method*)o)->flag &= ~(KNH_FLAG_MF_PUBLIC);


#define knh_Method_setPrivate(o,b)  \
	if(b) ((Method*)o)->flag &= ~(KNH_FLAG_MF_PUBLIC); else ((Method*)o)->flag |= KNH_FLAG_MF_PUBLIC;

#define KNH_FLAG_MF_VIRTUAL             KNH_FLAG1

#define knh_Method_isVirtual(o)  \
	((((Method*)o)->flag & KNH_FLAG_MF_VIRTUAL) == KNH_FLAG_MF_VIRTUAL)

#define knh_Method_isFinal(o)   \
	((((Method*)o)->flag & KNH_FLAG_MF_VIRTUAL) != KNH_FLAG_MF_VIRTUAL)

#define knh_Method_setVirtual(o,b)  \
	if(b) ((Method*)o)->flag |= KNH_FLAG_MF_VIRTUAL; else ((Method*)o)->flag &= ~(KNH_FLAG_MF_VIRTUAL);


#define knh_Method_setFinal(o,b)  \
	if(b) ((Method*)o)->flag &= ~(KNH_FLAG_MF_VIRTUAL); else ((Method*)o)->flag |= KNH_FLAG_MF_VIRTUAL;

#define KNH_FLAG_MF_STATIC              KNH_FLAG2

#define knh_Method_isStatic(o)  \
	((((Method*)o)->flag & KNH_FLAG_MF_STATIC) == KNH_FLAG_MF_STATIC)
#define KNH_FLAG_MF_CLASS               KNH_FLAG3

#define knh_Method_isClass(o)  \
	((((Method*)o)->flag & KNH_FLAG_MF_CLASS) == KNH_FLAG_MF_CLASS)
#define KNH_FLAG_MF_VARARGS             KNH_FLAG4

#define knh_Method_isVarArgs(o)  \
	((((Method*)o)->mf->flag & KNH_FLAG_MF_VARARGS) == KNH_FLAG_MF_VARARGS)

#define knh_Method_setVarArgs(o,b)  \
	if(b) ((Method*)o)->mf->flag |= KNH_FLAG_MF_VARARGS; else ((Method*)o)->mf->flag &= ~(KNH_FLAG_MF_VARARGS);

#define KNH_FLAG_MF_ASPECT              KNH_FLAG5

#define knh_Method_isAspect(o)  \
	((((Method*)o)->mf->flag & KNH_FLAG_MF_ASPECT) == KNH_FLAG_MF_ASPECT)

#define knh_Method_setAspect(o,b)  \
	if(b) ((Method*)o)->mf->flag |= KNH_FLAG_MF_ASPECT; else ((Method*)o)->mf->flag &= ~(KNH_FLAG_MF_ASPECT);

#define KNH_FLAG_MF_OBJECTCODE          KNH_FLAG6

#define knh_Method_isObjectCode(o)  \
	((((Method*)o)->flag & KNH_FLAG_MF_OBJECTCODE) == KNH_FLAG_MF_OBJECTCODE)

#define knh_Method_setObjectCode(o,b)  \
	if(b) ((Method*)o)->flag |= KNH_FLAG_MF_OBJECTCODE; else ((Method*)o)->flag &= ~(KNH_FLAG_MF_OBJECTCODE);

#define KNH_FLAG_MF_GENERATED           KNH_FLAG7

#define knh_Method_isGenerated(o)  \
	((((Method*)o)->mf->flag & KNH_FLAG_MF_GENERATED) == KNH_FLAG_MF_GENERATED)

#define knh_Method_setGenerated(o,b)  \
	if(b) ((Method*)o)->mf->flag |= KNH_FLAG_MF_GENERATED; else ((Method*)o)->mf->flag &= ~(KNH_FLAG_MF_GENERATED);


/* ------------------------------------------------------------------------ */
/* MapMap */
#define KNH_FLAG_MMF_INTERFACE          KNH_FLAG0

#define knh_MapMap_isInterface(o)  \
	((((MapMap*)o)->flag & KNH_FLAG_MMF_INTERFACE) == KNH_FLAG_MMF_INTERFACE)

#define knh_MapMap_setInterface(o,b)  \
	if(b) ((MapMap*)o)->flag |= KNH_FLAG_MMF_INTERFACE; else ((MapMap*)o)->flag &= ~(KNH_FLAG_MMF_INTERFACE);

#define KNH_FLAG_MMF_VERYSIGNIFICANT    KNH_FLAG1
#define KNH_FLAG_MMF_SIGNIFICANT        KNH_FLAG2

#define knh_MapMap_isSignificant(o)  \
	((((MapMap*)o)->flag & KNH_FLAG_MMF_SIGNIFICANT) == KNH_FLAG_MMF_SIGNIFICANT)

#define knh_MapMap_setSignificant(o,b)  \
	if(b) ((MapMap*)o)->flag |= KNH_FLAG_MMF_SIGNIFICANT; else ((MapMap*)o)->flag &= ~(KNH_FLAG_MMF_SIGNIFICANT);

#define KNH_FLAG_MMF_SYNONYM            KNH_FLAG3

#define knh_MapMap_isSynonym(o)  \
	((((MapMap*)o)->flag & KNH_FLAG_MMF_SYNONYM) == KNH_FLAG_MMF_SYNONYM)

#define knh_MapMap_setSynonym(o,b)  \
	if(b) ((MapMap*)o)->flag |= KNH_FLAG_MMF_SYNONYM; else ((MapMap*)o)->flag &= ~(KNH_FLAG_MMF_SYNONYM);

#define KNH_FLAG_MMF_LOSSLESS           KNH_FLAG4

#define knh_MapMap_isLossLess(o)  \
	((((MapMap*)o)->flag & KNH_FLAG_MMF_LOSSLESS) == KNH_FLAG_MMF_LOSSLESS)

#define knh_MapMap_setLossLess(o,b)  \
	if(b) ((MapMap*)o)->flag |= KNH_FLAG_MMF_LOSSLESS; else ((MapMap*)o)->flag &= ~(KNH_FLAG_MMF_LOSSLESS);

#define KNH_FLAG_MMF_TOTAL              KNH_FLAG5

#define knh_MapMap_isTotal(o)  \
	((((MapMap*)o)->flag & KNH_FLAG_MMF_TOTAL) == KNH_FLAG_MMF_TOTAL)

#define knh_MapMap_isPartial(o)   \
	((((MapMap*)o)->flag & KNH_FLAG_MMF_TOTAL) != KNH_FLAG_MMF_TOTAL)

#define knh_MapMap_setTotal(o,b)  \
	if(b) ((MapMap*)o)->flag |= KNH_FLAG_MMF_TOTAL; else ((MapMap*)o)->flag &= ~(KNH_FLAG_MMF_TOTAL);


#define knh_MapMap_setPartial(o,b)  \
	if(b) ((MapMap*)o)->flag &= ~(KNH_FLAG_MMF_TOTAL); else ((MapMap*)o)->flag |= KNH_FLAG_MMF_TOTAL;

#define KNH_FLAG_MMF_STATIC             KNH_FLAG6

#define knh_MapMap_isStatic(o)  \
	((((MapMap*)o)->flag & KNH_FLAG_MMF_STATIC) == KNH_FLAG_MMF_STATIC)

#define knh_MapMap_isTemporal(o)   \
	((((MapMap*)o)->flag & KNH_FLAG_MMF_STATIC) != KNH_FLAG_MMF_STATIC)

#define knh_MapMap_setStatic(o,b)  \
	if(b) ((MapMap*)o)->flag |= KNH_FLAG_MMF_STATIC; else ((MapMap*)o)->flag &= ~(KNH_FLAG_MMF_STATIC);


#define knh_MapMap_setTemporal(o,b)  \
	if(b) ((MapMap*)o)->flag &= ~(KNH_FLAG_MMF_STATIC); else ((MapMap*)o)->flag |= KNH_FLAG_MMF_STATIC;

#define KNH_FLAG_MMF_LOCAL              KNH_FLAG7

#define knh_MapMap_isLocal(o)  \
	((((MapMap*)o)->flag & KNH_FLAG_MMF_LOCAL) == KNH_FLAG_MMF_LOCAL)

#define knh_MapMap_setLocal(o,b)  \
	if(b) ((MapMap*)o)->flag |= KNH_FLAG_MMF_LOCAL; else ((MapMap*)o)->flag &= ~(KNH_FLAG_MMF_LOCAL);

#define KNH_FLAG_MMF_DERIVED            KNH_FLAG8

#define knh_MapMap_isDerived(o)  \
	((((MapMap*)o)->flag & KNH_FLAG_MMF_DERIVED) == KNH_FLAG_MMF_DERIVED)

#define knh_MapMap_setDerived(o,b)  \
	if(b) ((MapMap*)o)->flag |= KNH_FLAG_MMF_DERIVED; else ((MapMap*)o)->flag &= ~(KNH_FLAG_MMF_DERIVED);


/* ------------------------------------------------------------------------ */
/* Exception */
#define KNH_FLAG_EF_FATAL               KNH_FLAG0

#define knh_Exception_isFatal(o)  \
	((((Exception*)o)->flag & KNH_FLAG_EF_FATAL) == KNH_FLAG_EF_FATAL)
#define KNH_FLAG_EF_LOGGING             KNH_FLAG1

#define knh_Exception_isLogging(o)  \
	((((Exception*)o)->flag & KNH_FLAG_EF_LOGGING) == KNH_FLAG_EF_LOGGING)
#define KNH_FLAG_EF_GENERATED           KNH_FLAG2

#define knh_Exception_isGenerated(o)  \
	((((Exception*)o)->flag & KNH_FLAG_EF_GENERATED) == KNH_FLAG_EF_GENERATED)
#define KNH_FLAG_EF_CAUGHT              KNH_FLAG3

#define knh_Exception_isCaught(o)  \
	((((Exception*)o)->flag & KNH_FLAG_EF_CAUGHT) == KNH_FLAG_EF_CAUGHT)

#define knh_Exception_setCaught(o,b)  \
	if(b) ((Exception*)o)->flag |= KNH_FLAG_EF_CAUGHT; else ((Exception*)o)->flag &= ~(KNH_FLAG_EF_CAUGHT);


/* ------------------------------------------------------------------------ */
/* ExceptionHandler */
#define KNH_FLAG_EHF_CATCHING           KNH_FLAG_OF_LOCAL1

#define knh_ExceptionHandler_isCatching(o)  \
	((knh_Object_head(o)->flag & KNH_FLAG_EHF_CATCHING) == KNH_FLAG_EHF_CATCHING)

#define knh_ExceptionHandler_setCatching(o,b)  \
	if(b) knh_Object_head(o)->flag |= KNH_FLAG_EHF_CATCHING; else knh_Object_head(o)->flag &= ~(KNH_FLAG_EHF_CATCHING);


/* ------------------------------------------------------------------------ */
/* IntUnit */
#define KNH_FLAG_UF_UNSIGNED            KNH_FLAG0

#define knh_IntUnit_isUnsigned(o)  \
	((((IntUnit*)o)->spec.flag & KNH_FLAG_UF_UNSIGNED) == KNH_FLAG_UF_UNSIGNED)

/* ======================================================================== */
/* [class] */

/* ------------------------------------------------------------------------ */
/* konoha */

/* ------------------------------------------------------------------------ */
/* Tuple */
#define STRUCT_Tuple            ((knh_struct_t)0)
#define CLASS_Tuple             ((knh_class_t)KONOHA_TSTRUCT_SIZE+0)
#define TYPE_Tuple              CLASS_TONULLABLE(CLASS_Tuple)
#define TYPE_Tuple__            CLASS_TOPLURAL(CLASS_Tuple)
#define CLASS_Tuple__           CLASS_TOPLURAL(CLASS_Tuple)
#define KNH_CFLAG_Tuple         ((knh_flag_t)0)
#define KNH_FLAG_Tuple          KNH_FLAG_CF2OF(KNH_CFLAG_Tuple)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Tuple1 */
#define STRUCT_Tuple1           ((knh_struct_t)1)
#define CLASS_Tuple1            ((knh_class_t)1)
#define STRUCT_IS_Tuple1(o)     (knh_Object_topsid(o) == STRUCT_Tuple1)
#ifndef Tuple1
#define Tuple1                  knh_Tuple1
#endif
#define IS_Tuple1(o)            (knh_Object_cid(o) == CLASS_Tuple1)
#define TYPE_Tuple1             CLASS_TONULLABLE(CLASS_Tuple1)
#define TYPE_Tuple1__           CLASS_TOPLURAL(CLASS_Tuple1)
#define CLASS_Tuple1__          CLASS_TOPLURAL(CLASS_Tuple1)
#define KNH_CFLAG_Tuple1        ((knh_flag_t)0)
#define KNH_FLAG_Tuple1         KNH_FLAG_CF2OF(KNH_CFLAG_Tuple1)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Tuple2 */
#define STRUCT_Tuple2           ((knh_struct_t)2)
#define CLASS_Tuple2            ((knh_class_t)2)
#define STRUCT_IS_Tuple2(o)     (knh_Object_topsid(o) == STRUCT_Tuple2)
#ifndef Tuple2
#define Tuple2                  knh_Tuple2
#endif
#define IS_Tuple2(o)            (knh_Object_cid(o) == CLASS_Tuple2)
#define TYPE_Tuple2             CLASS_TONULLABLE(CLASS_Tuple2)
#define TYPE_Tuple2__           CLASS_TOPLURAL(CLASS_Tuple2)
#define CLASS_Tuple2__          CLASS_TOPLURAL(CLASS_Tuple2)
#define KNH_CFLAG_Tuple2        ((knh_flag_t)0)
#define KNH_FLAG_Tuple2         KNH_FLAG_CF2OF(KNH_CFLAG_Tuple2)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Tuple3 */
#define STRUCT_Tuple3           ((knh_struct_t)3)
#define CLASS_Tuple3            ((knh_class_t)3)
#define STRUCT_IS_Tuple3(o)     (knh_Object_topsid(o) == STRUCT_Tuple3)
#ifndef Tuple3
#define Tuple3                  knh_Tuple3
#endif
#define IS_Tuple3(o)            (knh_Object_cid(o) == CLASS_Tuple3)
#define TYPE_Tuple3             CLASS_TONULLABLE(CLASS_Tuple3)
#define TYPE_Tuple3__           CLASS_TOPLURAL(CLASS_Tuple3)
#define CLASS_Tuple3__          CLASS_TOPLURAL(CLASS_Tuple3)
#define KNH_CFLAG_Tuple3        ((knh_flag_t)0)
#define KNH_FLAG_Tuple3         KNH_FLAG_CF2OF(KNH_CFLAG_Tuple3)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Tuple4 */
#define STRUCT_Tuple4           ((knh_struct_t)4)
#define CLASS_Tuple4            ((knh_class_t)4)
#define STRUCT_IS_Tuple4(o)     (knh_Object_topsid(o) == STRUCT_Tuple4)
#ifndef Tuple4
#define Tuple4                  knh_Tuple4
#endif
#define IS_Tuple4(o)            (knh_Object_cid(o) == CLASS_Tuple4)
#define TYPE_Tuple4             CLASS_TONULLABLE(CLASS_Tuple4)
#define TYPE_Tuple4__           CLASS_TOPLURAL(CLASS_Tuple4)
#define CLASS_Tuple4__          CLASS_TOPLURAL(CLASS_Tuple4)
#define KNH_CFLAG_Tuple4        ((knh_flag_t)0)
#define KNH_FLAG_Tuple4         KNH_FLAG_CF2OF(KNH_CFLAG_Tuple4)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Tuple5 */
#define STRUCT_Tuple5           ((knh_struct_t)5)
#define CLASS_Tuple5            ((knh_class_t)5)
#define STRUCT_IS_Tuple5(o)     (knh_Object_topsid(o) == STRUCT_Tuple5)
#ifndef Tuple5
#define Tuple5                  knh_Tuple5
#endif
#define IS_Tuple5(o)            (knh_Object_cid(o) == CLASS_Tuple5)
#define TYPE_Tuple5             CLASS_TONULLABLE(CLASS_Tuple5)
#define TYPE_Tuple5__           CLASS_TOPLURAL(CLASS_Tuple5)
#define CLASS_Tuple5__          CLASS_TOPLURAL(CLASS_Tuple5)
#define KNH_CFLAG_Tuple5        ((knh_flag_t)0)
#define KNH_FLAG_Tuple5         KNH_FLAG_CF2OF(KNH_CFLAG_Tuple5)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Tuple6 */
#define STRUCT_Tuple6           ((knh_struct_t)6)
#define CLASS_Tuple6            ((knh_class_t)6)
#define STRUCT_IS_Tuple6(o)     (knh_Object_topsid(o) == STRUCT_Tuple6)
#ifndef Tuple6
#define Tuple6                  knh_Tuple6
#endif
#define IS_Tuple6(o)            (knh_Object_cid(o) == CLASS_Tuple6)
#define TYPE_Tuple6             CLASS_TONULLABLE(CLASS_Tuple6)
#define TYPE_Tuple6__           CLASS_TOPLURAL(CLASS_Tuple6)
#define CLASS_Tuple6__          CLASS_TOPLURAL(CLASS_Tuple6)
#define KNH_CFLAG_Tuple6        ((knh_flag_t)0)
#define KNH_FLAG_Tuple6         KNH_FLAG_CF2OF(KNH_CFLAG_Tuple6)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Tuple7 */
#define STRUCT_Tuple7           ((knh_struct_t)7)
#define CLASS_Tuple7            ((knh_class_t)7)
#define STRUCT_IS_Tuple7(o)     (knh_Object_topsid(o) == STRUCT_Tuple7)
#ifndef Tuple7
#define Tuple7                  knh_Tuple7
#endif
#define IS_Tuple7(o)            (knh_Object_cid(o) == CLASS_Tuple7)
#define TYPE_Tuple7             CLASS_TONULLABLE(CLASS_Tuple7)
#define TYPE_Tuple7__           CLASS_TOPLURAL(CLASS_Tuple7)
#define CLASS_Tuple7__          CLASS_TOPLURAL(CLASS_Tuple7)
#define KNH_CFLAG_Tuple7        ((knh_flag_t)0)
#define KNH_FLAG_Tuple7         KNH_FLAG_CF2OF(KNH_CFLAG_Tuple7)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Tuple8 */
#define STRUCT_Tuple8           ((knh_struct_t)8)
#define CLASS_Tuple8            ((knh_class_t)8)
#define STRUCT_IS_Tuple8(o)     (knh_Object_topsid(o) == STRUCT_Tuple8)
#ifndef Tuple8
#define Tuple8                  knh_Tuple8
#endif
#define IS_Tuple8(o)            (knh_Object_cid(o) == CLASS_Tuple8)
#define TYPE_Tuple8             CLASS_TONULLABLE(CLASS_Tuple8)
#define TYPE_Tuple8__           CLASS_TOPLURAL(CLASS_Tuple8)
#define CLASS_Tuple8__          CLASS_TOPLURAL(CLASS_Tuple8)
#define KNH_CFLAG_Tuple8        ((knh_flag_t)0)
#define KNH_FLAG_Tuple8         KNH_FLAG_CF2OF(KNH_CFLAG_Tuple8)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Tuple9 */
#define STRUCT_Tuple9           ((knh_struct_t)9)
#define CLASS_Tuple9            ((knh_class_t)9)
#define STRUCT_IS_Tuple9(o)     (knh_Object_topsid(o) == STRUCT_Tuple9)
#ifndef Tuple9
#define Tuple9                  knh_Tuple9
#endif
#define IS_Tuple9(o)            (knh_Object_cid(o) == CLASS_Tuple9)
#define TYPE_Tuple9             CLASS_TONULLABLE(CLASS_Tuple9)
#define TYPE_Tuple9__           CLASS_TOPLURAL(CLASS_Tuple9)
#define CLASS_Tuple9__          CLASS_TOPLURAL(CLASS_Tuple9)
#define KNH_CFLAG_Tuple9        ((knh_flag_t)0)
#define KNH_FLAG_Tuple9         KNH_FLAG_CF2OF(KNH_CFLAG_Tuple9)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Tuple10 */
#define STRUCT_Tuple10          ((knh_struct_t)10)
#define CLASS_Tuple10           ((knh_class_t)10)
#define STRUCT_IS_Tuple10(o)    (knh_Object_topsid(o) == STRUCT_Tuple10)
#ifndef Tuple10
#define Tuple10                 knh_Tuple10
#endif
#define IS_Tuple10(o)           (knh_Object_cid(o) == CLASS_Tuple10)
#define TYPE_Tuple10            CLASS_TONULLABLE(CLASS_Tuple10)
#define TYPE_Tuple10__          CLASS_TOPLURAL(CLASS_Tuple10)
#define CLASS_Tuple10__         CLASS_TOPLURAL(CLASS_Tuple10)
#define KNH_CFLAG_Tuple10       ((knh_flag_t)0)
#define KNH_FLAG_Tuple10        KNH_FLAG_CF2OF(KNH_CFLAG_Tuple10)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Tuple11 */
#define STRUCT_Tuple11          ((knh_struct_t)11)
#define CLASS_Tuple11           ((knh_class_t)11)
#define STRUCT_IS_Tuple11(o)    (knh_Object_topsid(o) == STRUCT_Tuple11)
#ifndef Tuple11
#define Tuple11                 knh_Tuple11
#endif
#define IS_Tuple11(o)           (knh_Object_cid(o) == CLASS_Tuple11)
#define TYPE_Tuple11            CLASS_TONULLABLE(CLASS_Tuple11)
#define TYPE_Tuple11__          CLASS_TOPLURAL(CLASS_Tuple11)
#define CLASS_Tuple11__         CLASS_TOPLURAL(CLASS_Tuple11)
#define KNH_CFLAG_Tuple11       ((knh_flag_t)0)
#define KNH_FLAG_Tuple11        KNH_FLAG_CF2OF(KNH_CFLAG_Tuple11)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Tuple12 */
#define STRUCT_Tuple12          ((knh_struct_t)12)
#define CLASS_Tuple12           ((knh_class_t)12)
#define STRUCT_IS_Tuple12(o)    (knh_Object_topsid(o) == STRUCT_Tuple12)
#ifndef Tuple12
#define Tuple12                 knh_Tuple12
#endif
#define IS_Tuple12(o)           (knh_Object_cid(o) == CLASS_Tuple12)
#define TYPE_Tuple12            CLASS_TONULLABLE(CLASS_Tuple12)
#define TYPE_Tuple12__          CLASS_TOPLURAL(CLASS_Tuple12)
#define CLASS_Tuple12__         CLASS_TOPLURAL(CLASS_Tuple12)
#define KNH_CFLAG_Tuple12       ((knh_flag_t)0)
#define KNH_FLAG_Tuple12        KNH_FLAG_CF2OF(KNH_CFLAG_Tuple12)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Tuple13 */
#define STRUCT_Tuple13          ((knh_struct_t)13)
#define CLASS_Tuple13           ((knh_class_t)13)
#define STRUCT_IS_Tuple13(o)    (knh_Object_topsid(o) == STRUCT_Tuple13)
#ifndef Tuple13
#define Tuple13                 knh_Tuple13
#endif
#define IS_Tuple13(o)           (knh_Object_cid(o) == CLASS_Tuple13)
#define TYPE_Tuple13            CLASS_TONULLABLE(CLASS_Tuple13)
#define TYPE_Tuple13__          CLASS_TOPLURAL(CLASS_Tuple13)
#define CLASS_Tuple13__         CLASS_TOPLURAL(CLASS_Tuple13)
#define KNH_CFLAG_Tuple13       ((knh_flag_t)0)
#define KNH_FLAG_Tuple13        KNH_FLAG_CF2OF(KNH_CFLAG_Tuple13)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Tuple14 */
#define STRUCT_Tuple14          ((knh_struct_t)14)
#define CLASS_Tuple14           ((knh_class_t)14)
#define STRUCT_IS_Tuple14(o)    (knh_Object_topsid(o) == STRUCT_Tuple14)
#ifndef Tuple14
#define Tuple14                 knh_Tuple14
#endif
#define IS_Tuple14(o)           (knh_Object_cid(o) == CLASS_Tuple14)
#define TYPE_Tuple14            CLASS_TONULLABLE(CLASS_Tuple14)
#define TYPE_Tuple14__          CLASS_TOPLURAL(CLASS_Tuple14)
#define CLASS_Tuple14__         CLASS_TOPLURAL(CLASS_Tuple14)
#define KNH_CFLAG_Tuple14       ((knh_flag_t)0)
#define KNH_FLAG_Tuple14        KNH_FLAG_CF2OF(KNH_CFLAG_Tuple14)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Tuple15 */
#define STRUCT_Tuple15          ((knh_struct_t)15)
#define CLASS_Tuple15           ((knh_class_t)15)
#define STRUCT_IS_Tuple15(o)    (knh_Object_topsid(o) == STRUCT_Tuple15)
#ifndef Tuple15
#define Tuple15                 knh_Tuple15
#endif
#define IS_Tuple15(o)           (knh_Object_cid(o) == CLASS_Tuple15)
#define TYPE_Tuple15            CLASS_TONULLABLE(CLASS_Tuple15)
#define TYPE_Tuple15__          CLASS_TOPLURAL(CLASS_Tuple15)
#define CLASS_Tuple15__         CLASS_TOPLURAL(CLASS_Tuple15)
#define KNH_CFLAG_Tuple15       ((knh_flag_t)0)
#define KNH_FLAG_Tuple15        KNH_FLAG_CF2OF(KNH_CFLAG_Tuple15)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Prototype */
#define STRUCT_Prototype        ((knh_struct_t)16)
#define CLASS_Prototype         ((knh_class_t)16)
#define STRUCT_IS_Prototype(o)  (knh_Object_topsid(o) == STRUCT_Prototype)
#ifndef Prototype
#define Prototype               knh_Prototype
#endif
#define IS_Prototype(o)         (knh_Object_cid(o) == CLASS_Prototype)
#define TYPE_Prototype          CLASS_TONULLABLE(CLASS_Prototype)
#define TYPE_Prototype__        CLASS_TOPLURAL(CLASS_Prototype)
#define CLASS_Prototype__       CLASS_TOPLURAL(CLASS_Prototype)
#define KNH_CFLAG_Prototype     ((knh_flag_t)0)
#define KNH_FLAG_Prototype      KNH_FLAG_CF2OF(KNH_CFLAG_Prototype)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Nue */
#define STRUCT_Nue              ((knh_struct_t)17)
#define CLASS_Nue               ((knh_class_t)17)
#define STRUCT_IS_Nue(o)        (knh_Object_topsid(o) == STRUCT_Nue)
#ifndef Nue
#define Nue                     knh_Nue
#endif
#define IS_Nue(o)               (knh_Object_cid(o) == CLASS_Nue)
#define TYPE_Nue                CLASS_TONULLABLE(CLASS_Nue)
#define TYPE_Nue__              CLASS_TOPLURAL(CLASS_Nue)
#define CLASS_Nue__             CLASS_TOPLURAL(CLASS_Nue)
#define KNH_CFLAG_Nue           ((knh_flag_t)0)
#define KNH_FLAG_Nue            KNH_FLAG_CF2OF(KNH_CFLAG_Nue)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Bool */
#define STRUCT_Bool             ((knh_struct_t)18)
#define CLASS_Bool              ((knh_class_t)18)
#define STRUCT_IS_Bool(o)       (knh_Object_topsid(o) == STRUCT_Bool)
#ifndef Bool
#define Bool                    knh_Bool
#endif
#define IS_Bool(o)              (knh_Object_cid(o) == CLASS_Bool)
#define TYPE_Bool               CLASS_TONULLABLE(CLASS_Bool)
#define TYPE_Bool__             CLASS_TOPLURAL(CLASS_Bool)
#define CLASS_Bool__            CLASS_TOPLURAL(CLASS_Bool)
#define KNH_CFLAG_Bool          ((knh_flag_t)0)
#define KNH_FLAG_Bool           KNH_FLAG_CF2OF(KNH_CFLAG_Bool)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Int */
#define STRUCT_Int              ((knh_struct_t)19)
#define CLASS_Int               ((knh_class_t)19)
#define STRUCT_IS_Int(o)        (knh_Object_topsid(o) == STRUCT_Int)
#ifndef Int
#define Int                     knh_Int
#endif
#define IS_Int(o)               (knh_Object_cid(o) == CLASS_Int)
#define TYPE_Int                CLASS_TONULLABLE(CLASS_Int)
#define TYPE_Int__              CLASS_TOPLURAL(CLASS_Int)
#define CLASS_Int__             CLASS_TOPLURAL(CLASS_Int)
#define KNH_CFLAG_Int           ((knh_flag_t)0)
#define KNH_FLAG_Int            KNH_FLAG_CF2OF(KNH_CFLAG_Int)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Int64 */
#define STRUCT_Int64            ((knh_struct_t)20)
#define CLASS_Int64             ((knh_class_t)20)
#define STRUCT_IS_Int64(o)      (knh_Object_topsid(o) == STRUCT_Int64)
#ifndef Int64
#define Int64                   knh_Int64
#endif
#define IS_Int64(o)             (knh_Object_cid(o) == CLASS_Int64)
#define TYPE_Int64              CLASS_TONULLABLE(CLASS_Int64)
#define TYPE_Int64__            CLASS_TOPLURAL(CLASS_Int64)
#define CLASS_Int64__           CLASS_TOPLURAL(CLASS_Int64)
#define KNH_CFLAG_Int64         ((knh_flag_t)0)
#define KNH_FLAG_Int64          KNH_FLAG_CF2OF(KNH_CFLAG_Int64)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Float */
#define STRUCT_Float            ((knh_struct_t)21)
#define CLASS_Float             ((knh_class_t)21)
#define STRUCT_IS_Float(o)      (knh_Object_topsid(o) == STRUCT_Float)
#ifndef Float
#define Float                   knh_Float
#endif
#define IS_Float(o)             (knh_Object_cid(o) == CLASS_Float)
#define TYPE_Float              CLASS_TONULLABLE(CLASS_Float)
#define TYPE_Float__            CLASS_TOPLURAL(CLASS_Float)
#define CLASS_Float__           CLASS_TOPLURAL(CLASS_Float)
#define KNH_CFLAG_Float         ((knh_flag_t)0)
#define KNH_FLAG_Float          KNH_FLAG_CF2OF(KNH_CFLAG_Float)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* String */
#define STRUCT_String           ((knh_struct_t)22)
#define CLASS_String            ((knh_class_t)22)
#define STRUCT_IS_String(o)     (knh_Object_topsid(o) == STRUCT_String)
#ifndef String
#define String                  knh_String
#endif
#define IS_String(o)            (knh_Object_cid(o) == CLASS_String)
#define TYPE_String             CLASS_TONULLABLE(CLASS_String)
#define TYPE_String__           CLASS_TOPLURAL(CLASS_String)
#define CLASS_String__          CLASS_TOPLURAL(CLASS_String)
#define KNH_CFLAG_String        ((knh_flag_t)0)
#define KNH_FLAG_String         KNH_FLAG_CF2OF(KNH_CFLAG_String)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Regex */
#define STRUCT_Regex            ((knh_struct_t)23)
#define CLASS_Regex             ((knh_class_t)23)
#define STRUCT_IS_Regex(o)      (knh_Object_topsid(o) == STRUCT_Regex)
#ifndef Regex
#define Regex                   knh_Regex
#endif
#define IS_Regex(o)             (knh_Object_cid(o) == CLASS_Regex)
#define TYPE_Regex              CLASS_TONULLABLE(CLASS_Regex)
#define TYPE_Regex__            CLASS_TOPLURAL(CLASS_Regex)
#define CLASS_Regex__           CLASS_TOPLURAL(CLASS_Regex)
#define KNH_CFLAG_Regex         ((knh_flag_t)0)
#define KNH_FLAG_Regex          KNH_FLAG_CF2OF(KNH_CFLAG_Regex)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Bytes */
#define STRUCT_Bytes            ((knh_struct_t)24)
#define CLASS_Bytes             ((knh_class_t)24)
#define STRUCT_IS_Bytes(o)      (knh_Object_topsid(o) == STRUCT_Bytes)
#ifndef Bytes
#define Bytes                   knh_Bytes
#endif
#define IS_Bytes(o)             (knh_Object_cid(o) == CLASS_Bytes)
#define TYPE_Bytes              CLASS_TONULLABLE(CLASS_Bytes)
#define TYPE_Bytes__            CLASS_TOPLURAL(CLASS_Bytes)
#define CLASS_Bytes__           CLASS_TOPLURAL(CLASS_Bytes)
#define KNH_CFLAG_Bytes         ((knh_flag_t)0)
#define KNH_FLAG_Bytes          KNH_FLAG_CF2OF(KNH_CFLAG_Bytes)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* BytesConv */
#define STRUCT_BytesConv        ((knh_struct_t)25)
#define CLASS_BytesConv         ((knh_class_t)25)
#define STRUCT_IS_BytesConv(o)  (knh_Object_topsid(o) == STRUCT_BytesConv)
#ifndef BytesConv
#define BytesConv               knh_BytesConv
#endif
#define IS_BytesConv(o)         (knh_Object_cid(o) == CLASS_BytesConv)
#define TYPE_BytesConv          CLASS_TONULLABLE(CLASS_BytesConv)
#define TYPE_BytesConv__        CLASS_TOPLURAL(CLASS_BytesConv)
#define CLASS_BytesConv__       CLASS_TOPLURAL(CLASS_BytesConv)
#define KNH_CFLAG_BytesConv     ((knh_flag_t)0)
#define KNH_FLAG_BytesConv      KNH_FLAG_CF2OF(KNH_CFLAG_BytesConv)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Array */
#define STRUCT_Array            ((knh_struct_t)26)
#define CLASS_Array             ((knh_class_t)26)
#define STRUCT_IS_Array(o)      (knh_Object_topsid(o) == STRUCT_Array)
#ifndef Array
#define Array                   knh_Array
#endif
#define IS_Array(o)             (knh_Object_cid(o) == CLASS_Array)
#define TYPE_Array              CLASS_TONULLABLE(CLASS_Array)
#define TYPE_Array__            CLASS_TOPLURAL(CLASS_Array)
#define CLASS_Array__           CLASS_TOPLURAL(CLASS_Array)
#define KNH_CFLAG_Array         ((knh_flag_t)0)
#define KNH_FLAG_Array          KNH_FLAG_CF2OF(KNH_CFLAG_Array)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* HashMap */
#define STRUCT_HashMap          ((knh_struct_t)27)
#define CLASS_HashMap           ((knh_class_t)27)
#define STRUCT_IS_HashMap(o)    (knh_Object_topsid(o) == STRUCT_HashMap)
#ifndef HashMap
#define HashMap                 knh_HashMap
#endif
#define IS_HashMap(o)           (knh_Object_cid(o) == CLASS_HashMap)
#define TYPE_HashMap            CLASS_TONULLABLE(CLASS_HashMap)
#define TYPE_HashMap__          CLASS_TOPLURAL(CLASS_HashMap)
#define CLASS_HashMap__         CLASS_TOPLURAL(CLASS_HashMap)
#define KNH_CFLAG_HashMap       ((knh_flag_t)0)
#define KNH_FLAG_HashMap        KNH_FLAG_CF2OF(KNH_CFLAG_HashMap)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* HashSet */
#define STRUCT_HashSet          ((knh_struct_t)28)
#define CLASS_HashSet           ((knh_class_t)28)
#define STRUCT_IS_HashSet(o)    (knh_Object_topsid(o) == STRUCT_HashSet)
#ifndef HashSet
#define HashSet                 knh_HashSet
#endif
#define IS_HashSet(o)           (knh_Object_cid(o) == CLASS_HashSet)
#define TYPE_HashSet            CLASS_TONULLABLE(CLASS_HashSet)
#define TYPE_HashSet__          CLASS_TOPLURAL(CLASS_HashSet)
#define CLASS_HashSet__         CLASS_TOPLURAL(CLASS_HashSet)
#define KNH_CFLAG_HashSet       ((knh_flag_t)0)
#define KNH_FLAG_HashSet        KNH_FLAG_CF2OF(KNH_CFLAG_HashSet)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* DictMap */
#define STRUCT_DictMap          ((knh_struct_t)29)
#define CLASS_DictMap           ((knh_class_t)29)
#define STRUCT_IS_DictMap(o)    (knh_Object_topsid(o) == STRUCT_DictMap)
#ifndef DictMap
#define DictMap                 knh_DictMap
#endif
#define IS_DictMap(o)           (knh_Object_cid(o) == CLASS_DictMap)
#define TYPE_DictMap            CLASS_TONULLABLE(CLASS_DictMap)
#define TYPE_DictMap__          CLASS_TOPLURAL(CLASS_DictMap)
#define CLASS_DictMap__         CLASS_TOPLURAL(CLASS_DictMap)
#define KNH_CFLAG_DictMap       ((knh_flag_t)0)
#define KNH_FLAG_DictMap        KNH_FLAG_CF2OF(KNH_CFLAG_DictMap)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* DictSet */
#define STRUCT_DictSet          ((knh_struct_t)30)
#define CLASS_DictSet           ((knh_class_t)30)
#define STRUCT_IS_DictSet(o)    (knh_Object_topsid(o) == STRUCT_DictSet)
#ifndef DictSet
#define DictSet                 knh_DictSet
#endif
#define IS_DictSet(o)           (knh_Object_cid(o) == CLASS_DictSet)
#define TYPE_DictSet            CLASS_TONULLABLE(CLASS_DictSet)
#define TYPE_DictSet__          CLASS_TOPLURAL(CLASS_DictSet)
#define CLASS_DictSet__         CLASS_TOPLURAL(CLASS_DictSet)
#define KNH_CFLAG_DictSet       ((knh_flag_t)0)
#define KNH_FLAG_DictSet        KNH_FLAG_CF2OF(KNH_CFLAG_DictSet)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Iterator */
#define STRUCT_Iterator         ((knh_struct_t)31)
#define CLASS_Iterator          ((knh_class_t)31)
#define STRUCT_IS_Iterator(o)   (knh_Object_topsid(o) == STRUCT_Iterator)
#ifndef Iterator
#define Iterator                knh_Iterator
#endif
#define IS_Iterator(o)          (knh_Object_cid(o) == CLASS_Iterator)
#define TYPE_Iterator           CLASS_TONULLABLE(CLASS_Iterator)
#define TYPE_Iterator__         CLASS_TOPLURAL(CLASS_Iterator)
#define CLASS_Iterator__        CLASS_TOPLURAL(CLASS_Iterator)
#define KNH_CFLAG_Iterator      ((knh_flag_t)0)
#define KNH_FLAG_Iterator       KNH_FLAG_CF2OF(KNH_CFLAG_Iterator)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* DictIdx */
#define STRUCT_DictIdx          ((knh_struct_t)32)
#define CLASS_DictIdx           ((knh_class_t)32)
#define STRUCT_IS_DictIdx(o)    (knh_Object_topsid(o) == STRUCT_DictIdx)
#ifndef DictIdx
#define DictIdx                 knh_DictIdx
#endif
#define IS_DictIdx(o)           (knh_Object_cid(o) == CLASS_DictIdx)
#define TYPE_DictIdx            CLASS_TONULLABLE(CLASS_DictIdx)
#define TYPE_DictIdx__          CLASS_TOPLURAL(CLASS_DictIdx)
#define CLASS_DictIdx__         CLASS_TOPLURAL(CLASS_DictIdx)
#define KNH_CFLAG_DictIdx       ((knh_flag_t)0)
#define KNH_FLAG_DictIdx        KNH_FLAG_CF2OF(KNH_CFLAG_DictIdx)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Class */
#define STRUCT_Class            ((knh_struct_t)33)
#define CLASS_Class             ((knh_class_t)33)
#define STRUCT_IS_Class(o)      (knh_Object_topsid(o) == STRUCT_Class)
#ifndef Class
#define Class                   knh_Class
#endif
#define IS_Class(o)             (knh_Object_cid(o) == CLASS_Class)
#define TYPE_Class              CLASS_TONULLABLE(CLASS_Class)
#define TYPE_Class__            CLASS_TOPLURAL(CLASS_Class)
#define CLASS_Class__           CLASS_TOPLURAL(CLASS_Class)
#define KNH_CFLAG_Class         ((knh_flag_t)0)
#define KNH_FLAG_Class          KNH_FLAG_CF2OF(KNH_CFLAG_Class)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* ClassStruct */
#define STRUCT_ClassStruct      ((knh_struct_t)34)
#define CLASS_ClassStruct       ((knh_class_t)34)
#define STRUCT_IS_ClassStruct(o) (knh_Object_topsid(o) == STRUCT_ClassStruct)
#ifndef ClassStruct
#define ClassStruct             knh_ClassStruct
#endif
#define IS_ClassStruct(o)       (knh_Object_cid(o) == CLASS_ClassStruct)
#define TYPE_ClassStruct        CLASS_TONULLABLE(CLASS_ClassStruct)
#define TYPE_ClassStruct__      CLASS_TOPLURAL(CLASS_ClassStruct)
#define CLASS_ClassStruct__     CLASS_TOPLURAL(CLASS_ClassStruct)
#define KNH_CFLAG_ClassStruct   ((knh_flag_t)0)
#define KNH_FLAG_ClassStruct    KNH_FLAG_CF2OF(KNH_CFLAG_ClassStruct)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* MethodField */
#define STRUCT_MethodField      ((knh_struct_t)35)
#define CLASS_MethodField       ((knh_class_t)35)
#define STRUCT_IS_MethodField(o) (knh_Object_topsid(o) == STRUCT_MethodField)
#ifndef MethodField
#define MethodField             knh_MethodField
#endif
#define IS_MethodField(o)       (knh_Object_cid(o) == CLASS_MethodField)
#define TYPE_MethodField        CLASS_TONULLABLE(CLASS_MethodField)
#define TYPE_MethodField__      CLASS_TOPLURAL(CLASS_MethodField)
#define CLASS_MethodField__     CLASS_TOPLURAL(CLASS_MethodField)
#define KNH_CFLAG_MethodField   ((knh_flag_t)0)
#define KNH_FLAG_MethodField    KNH_FLAG_CF2OF(KNH_CFLAG_MethodField)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Method */
#define STRUCT_Method           ((knh_struct_t)36)
#define CLASS_Method            ((knh_class_t)36)
#define STRUCT_IS_Method(o)     (knh_Object_topsid(o) == STRUCT_Method)
#ifndef Method
#define Method                  knh_Method
#endif
#define IS_Method(o)            (knh_Object_cid(o) == CLASS_Method)
#define TYPE_Method             CLASS_TONULLABLE(CLASS_Method)
#define TYPE_Method__           CLASS_TOPLURAL(CLASS_Method)
#define CLASS_Method__          CLASS_TOPLURAL(CLASS_Method)
#define KNH_CFLAG_Method        ((knh_flag_t)0)
#define KNH_FLAG_Method         KNH_FLAG_CF2OF(KNH_CFLAG_Method)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* MapMap */
#define STRUCT_MapMap           ((knh_struct_t)37)
#define CLASS_MapMap            ((knh_class_t)37)
#define STRUCT_IS_MapMap(o)     (knh_Object_topsid(o) == STRUCT_MapMap)
#ifndef MapMap
#define MapMap                  knh_MapMap
#endif
#define IS_MapMap(o)            (knh_Object_cid(o) == CLASS_MapMap)
#define TYPE_MapMap             CLASS_TONULLABLE(CLASS_MapMap)
#define TYPE_MapMap__           CLASS_TOPLURAL(CLASS_MapMap)
#define CLASS_MapMap__          CLASS_TOPLURAL(CLASS_MapMap)
#define KNH_CFLAG_MapMap        ((knh_flag_t)0)
#define KNH_FLAG_MapMap         KNH_FLAG_CF2OF(KNH_CFLAG_MapMap)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* ClassRel */
#define STRUCT_ClassRel         ((knh_struct_t)38)
#define CLASS_ClassRel          ((knh_class_t)38)
#define STRUCT_IS_ClassRel(o)   (knh_Object_topsid(o) == STRUCT_ClassRel)
#ifndef ClassRel
#define ClassRel                knh_ClassRel
#endif
#define IS_ClassRel(o)          (knh_Object_cid(o) == CLASS_ClassRel)
#define TYPE_ClassRel           CLASS_TONULLABLE(CLASS_ClassRel)
#define TYPE_ClassRel__         CLASS_TOPLURAL(CLASS_ClassRel)
#define CLASS_ClassRel__        CLASS_TOPLURAL(CLASS_ClassRel)
#define KNH_CFLAG_ClassRel      ((knh_flag_t)0)
#define KNH_FLAG_ClassRel       KNH_FLAG_CF2OF(KNH_CFLAG_ClassRel)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* AffineConv */
#define STRUCT_AffineConv       ((knh_struct_t)39)
#define CLASS_AffineConv        ((knh_class_t)39)
#define STRUCT_IS_AffineConv(o) (knh_Object_topsid(o) == STRUCT_AffineConv)
#ifndef AffineConv
#define AffineConv              knh_AffineConv
#endif
#define IS_AffineConv(o)        (knh_Object_cid(o) == CLASS_AffineConv)
#define TYPE_AffineConv         CLASS_TONULLABLE(CLASS_AffineConv)
#define TYPE_AffineConv__       CLASS_TOPLURAL(CLASS_AffineConv)
#define CLASS_AffineConv__      CLASS_TOPLURAL(CLASS_AffineConv)
#define KNH_CFLAG_AffineConv    ((knh_flag_t)0)
#define KNH_FLAG_AffineConv     KNH_FLAG_CF2OF(KNH_CFLAG_AffineConv)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* IntUnit */
#define STRUCT_IntUnit          ((knh_struct_t)40)
#define CLASS_IntUnit           ((knh_class_t)40)
#define STRUCT_IS_IntUnit(o)    (knh_Object_topsid(o) == STRUCT_IntUnit)
#ifndef IntUnit
#define IntUnit                 knh_IntUnit
#endif
#define IS_IntUnit(o)           (knh_Object_cid(o) == CLASS_IntUnit)
#define TYPE_IntUnit            CLASS_TONULLABLE(CLASS_IntUnit)
#define TYPE_IntUnit__          CLASS_TOPLURAL(CLASS_IntUnit)
#define CLASS_IntUnit__         CLASS_TOPLURAL(CLASS_IntUnit)
#define KNH_CFLAG_IntUnit       ((knh_flag_t)0)
#define KNH_FLAG_IntUnit        KNH_FLAG_CF2OF(KNH_CFLAG_IntUnit)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* FloatUnit */
#define STRUCT_FloatUnit        ((knh_struct_t)41)
#define CLASS_FloatUnit         ((knh_class_t)41)
#define STRUCT_IS_FloatUnit(o)  (knh_Object_topsid(o) == STRUCT_FloatUnit)
#ifndef FloatUnit
#define FloatUnit               knh_FloatUnit
#endif
#define IS_FloatUnit(o)         (knh_Object_cid(o) == CLASS_FloatUnit)
#define TYPE_FloatUnit          CLASS_TONULLABLE(CLASS_FloatUnit)
#define TYPE_FloatUnit__        CLASS_TOPLURAL(CLASS_FloatUnit)
#define CLASS_FloatUnit__       CLASS_TOPLURAL(CLASS_FloatUnit)
#define KNH_CFLAG_FloatUnit     ((knh_flag_t)0)
#define KNH_FLAG_FloatUnit      KNH_FLAG_CF2OF(KNH_CFLAG_FloatUnit)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Vocabulary */
#define STRUCT_Vocabulary       ((knh_struct_t)42)
#define CLASS_Vocabulary        ((knh_class_t)42)
#define STRUCT_IS_Vocabulary(o) (knh_Object_topsid(o) == STRUCT_Vocabulary)
#ifndef Vocabulary
#define Vocabulary              knh_Vocabulary
#endif
#define IS_Vocabulary(o)        (knh_Object_cid(o) == CLASS_Vocabulary)
#define TYPE_Vocabulary         CLASS_TONULLABLE(CLASS_Vocabulary)
#define TYPE_Vocabulary__       CLASS_TOPLURAL(CLASS_Vocabulary)
#define CLASS_Vocabulary__      CLASS_TOPLURAL(CLASS_Vocabulary)
#define KNH_CFLAG_Vocabulary    ((knh_flag_t)0)
#define KNH_FLAG_Vocabulary     KNH_FLAG_CF2OF(KNH_CFLAG_Vocabulary)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* InputStream */
#define STRUCT_InputStream      ((knh_struct_t)43)
#define CLASS_InputStream       ((knh_class_t)43)
#define STRUCT_IS_InputStream(o) (knh_Object_topsid(o) == STRUCT_InputStream)
#ifndef InputStream
#define InputStream             knh_InputStream
#endif
#define IS_InputStream(o)       (knh_Object_cid(o) == CLASS_InputStream)
#define TYPE_InputStream        CLASS_TONULLABLE(CLASS_InputStream)
#define TYPE_InputStream__      CLASS_TOPLURAL(CLASS_InputStream)
#define CLASS_InputStream__     CLASS_TOPLURAL(CLASS_InputStream)
#define KNH_CFLAG_InputStream   ((knh_flag_t)0)
#define KNH_FLAG_InputStream    KNH_FLAG_CF2OF(KNH_CFLAG_InputStream)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* OutputStream */
#define STRUCT_OutputStream     ((knh_struct_t)44)
#define CLASS_OutputStream      ((knh_class_t)44)
#define STRUCT_IS_OutputStream(o) (knh_Object_topsid(o) == STRUCT_OutputStream)
#ifndef OutputStream
#define OutputStream            knh_OutputStream
#endif
#define IS_OutputStream(o)      (knh_Object_cid(o) == CLASS_OutputStream)
#define TYPE_OutputStream       CLASS_TONULLABLE(CLASS_OutputStream)
#define TYPE_OutputStream__     CLASS_TOPLURAL(CLASS_OutputStream)
#define CLASS_OutputStream__    CLASS_TOPLURAL(CLASS_OutputStream)
#define KNH_CFLAG_OutputStream  ((knh_flag_t)0)
#define KNH_FLAG_OutputStream   KNH_FLAG_CF2OF(KNH_CFLAG_OutputStream)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Socket */
#define STRUCT_Socket           ((knh_struct_t)45)
#define CLASS_Socket            ((knh_class_t)45)
#define STRUCT_IS_Socket(o)     (knh_Object_topsid(o) == STRUCT_Socket)
#ifndef Socket
#define Socket                  knh_Socket
#endif
#define IS_Socket(o)            (knh_Object_cid(o) == CLASS_Socket)
#define TYPE_Socket             CLASS_TONULLABLE(CLASS_Socket)
#define TYPE_Socket__           CLASS_TOPLURAL(CLASS_Socket)
#define CLASS_Socket__          CLASS_TOPLURAL(CLASS_Socket)
#define KNH_CFLAG_Socket        ((knh_flag_t)0)
#define KNH_FLAG_Socket         KNH_FLAG_CF2OF(KNH_CFLAG_Socket)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* ResultSet */
#define STRUCT_ResultSet        ((knh_struct_t)46)
#define CLASS_ResultSet         ((knh_class_t)46)
#define STRUCT_IS_ResultSet(o)  (knh_Object_topsid(o) == STRUCT_ResultSet)
#ifndef ResultSet
#define ResultSet               knh_ResultSet
#endif
#define IS_ResultSet(o)         (knh_Object_cid(o) == CLASS_ResultSet)
#define TYPE_ResultSet          CLASS_TONULLABLE(CLASS_ResultSet)
#define TYPE_ResultSet__        CLASS_TOPLURAL(CLASS_ResultSet)
#define CLASS_ResultSet__       CLASS_TOPLURAL(CLASS_ResultSet)
#define KNH_CFLAG_ResultSet     ((knh_flag_t)0)
#define KNH_FLAG_ResultSet      KNH_FLAG_CF2OF(KNH_CFLAG_ResultSet)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Connection */
#define STRUCT_Connection       ((knh_struct_t)47)
#define CLASS_Connection        ((knh_class_t)47)
#define STRUCT_IS_Connection(o) (knh_Object_topsid(o) == STRUCT_Connection)
#ifndef Connection
#define Connection              knh_Connection
#endif
#define IS_Connection(o)        (knh_Object_cid(o) == CLASS_Connection)
#define TYPE_Connection         CLASS_TONULLABLE(CLASS_Connection)
#define TYPE_Connection__       CLASS_TOPLURAL(CLASS_Connection)
#define CLASS_Connection__      CLASS_TOPLURAL(CLASS_Connection)
#define KNH_CFLAG_Connection    ((knh_flag_t)0)
#define KNH_FLAG_Connection     KNH_FLAG_CF2OF(KNH_CFLAG_Connection)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Exception */
#define STRUCT_Exception        ((knh_struct_t)48)
#define CLASS_Exception         ((knh_class_t)48)
#define STRUCT_IS_Exception(o)  (knh_Object_topsid(o) == STRUCT_Exception)
#ifndef Exception
#define Exception               knh_Exception
#endif
#define IS_Exception(o)         (knh_Object_cid(o) == CLASS_Exception)
#define TYPE_Exception          CLASS_TONULLABLE(CLASS_Exception)
#define TYPE_Exception__        CLASS_TOPLURAL(CLASS_Exception)
#define CLASS_Exception__       CLASS_TOPLURAL(CLASS_Exception)
#define KNH_CFLAG_Exception     ((knh_flag_t)0)
#define KNH_FLAG_Exception      KNH_FLAG_CF2OF(KNH_CFLAG_Exception)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* ExceptionHandler */
#define STRUCT_ExceptionHandler ((knh_struct_t)49)
#define CLASS_ExceptionHandler  ((knh_class_t)49)
#define STRUCT_IS_ExceptionHandler(o) (knh_Object_topsid(o) == STRUCT_ExceptionHandler)
#ifndef ExceptionHandler
#define ExceptionHandler        knh_ExceptionHandler
#endif
#define IS_ExceptionHandler(o)  (knh_Object_cid(o) == CLASS_ExceptionHandler)
#define TYPE_ExceptionHandler   CLASS_TONULLABLE(CLASS_ExceptionHandler)
#define TYPE_ExceptionHandler__ CLASS_TOPLURAL(CLASS_ExceptionHandler)
#define CLASS_ExceptionHandler__ CLASS_TOPLURAL(CLASS_ExceptionHandler)
#define KNH_CFLAG_ExceptionHandler ((knh_flag_t)0)
#define KNH_FLAG_ExceptionHandler KNH_FLAG_CF2OF(KNH_CFLAG_ExceptionHandler)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* System */
#define STRUCT_System           (knh_struct_t)(sizeof(knh_System)/sizeof(Object*))
#define CLASS_System            ((knh_class_t)KONOHA_TSTRUCT_SIZE+1)
#ifndef System
#define System                  knh_System
#endif
#define IS_System(o)            (knh_Object_cid(o) == CLASS_System)
#define TYPE_System             CLASS_TONULLABLE(CLASS_System)
#define TYPE_System__           CLASS_TOPLURAL(CLASS_System)
#define CLASS_System__          CLASS_TOPLURAL(CLASS_System)
#define KNH_CFLAG_System        ((knh_flag_t)0)
#define KNH_FLAG_System         KNH_FLAG_CF2OF(KNH_CFLAG_System)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* NameSpace */
#define STRUCT_NameSpace        (knh_struct_t)(sizeof(knh_NameSpace)/sizeof(Object*))
#define CLASS_NameSpace         ((knh_class_t)KONOHA_TSTRUCT_SIZE+2)
#ifndef NameSpace
#define NameSpace               knh_NameSpace
#endif
#define IS_NameSpace(o)         (knh_Object_cid(o) == CLASS_NameSpace)
#define TYPE_NameSpace          CLASS_TONULLABLE(CLASS_NameSpace)
#define TYPE_NameSpace__        CLASS_TOPLURAL(CLASS_NameSpace)
#define CLASS_NameSpace__       CLASS_TOPLURAL(CLASS_NameSpace)
#define KNH_CFLAG_NameSpace     ((knh_flag_t)0)
#define KNH_FLAG_NameSpace      KNH_FLAG_CF2OF(KNH_CFLAG_NameSpace)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Runtime */
#define STRUCT_Runtime          ((knh_struct_t)50)
#define CLASS_Runtime           ((knh_class_t)50)
#define STRUCT_IS_Runtime(o)    (knh_Object_topsid(o) == STRUCT_Runtime)
#ifndef Runtime
#define Runtime                 knh_Runtime
#endif
#define IS_Runtime(o)           (knh_Object_cid(o) == CLASS_Runtime)
#define TYPE_Runtime            CLASS_TONULLABLE(CLASS_Runtime)
#define TYPE_Runtime__          CLASS_TOPLURAL(CLASS_Runtime)
#define CLASS_Runtime__         CLASS_TOPLURAL(CLASS_Runtime)
#define KNH_CFLAG_Runtime       ((knh_flag_t)0)
#define KNH_FLAG_Runtime        KNH_FLAG_CF2OF(KNH_CFLAG_Runtime)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Context */
#define STRUCT_Context          ((knh_struct_t)51)
#define CLASS_Context           ((knh_class_t)51)
#define STRUCT_IS_Context(o)    (knh_Object_topsid(o) == STRUCT_Context)
#ifndef Context
#define Context                 knh_Context
#endif
#define IS_Context(o)           (knh_Object_cid(o) == CLASS_Context)
#define TYPE_Context            CLASS_TONULLABLE(CLASS_Context)
#define TYPE_Context__          CLASS_TOPLURAL(CLASS_Context)
#define CLASS_Context__         CLASS_TOPLURAL(CLASS_Context)
#define KNH_CFLAG_Context       ((knh_flag_t)0)
#define KNH_FLAG_Context        KNH_FLAG_CF2OF(KNH_CFLAG_Context)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Mutex */
#define STRUCT_Mutex            ((knh_struct_t)52)
#define CLASS_Mutex             ((knh_class_t)52)
#define STRUCT_IS_Mutex(o)      (knh_Object_topsid(o) == STRUCT_Mutex)
#ifndef Mutex
#define Mutex                   knh_Mutex
#endif
#define IS_Mutex(o)             (knh_Object_cid(o) == CLASS_Mutex)
#define TYPE_Mutex              CLASS_TONULLABLE(CLASS_Mutex)
#define TYPE_Mutex__            CLASS_TOPLURAL(CLASS_Mutex)
#define CLASS_Mutex__           CLASS_TOPLURAL(CLASS_Mutex)
#define KNH_CFLAG_Mutex         ((knh_flag_t)0)
#define KNH_FLAG_Mutex          KNH_FLAG_CF2OF(KNH_CFLAG_Mutex)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* naruto */

/* ------------------------------------------------------------------------ */
/* Counter */
#define STRUCT_Counter          ((knh_struct_t)53)
#define CLASS_Counter           ((knh_class_t)53)
#define STRUCT_IS_Counter(o)    (knh_Object_topsid(o) == STRUCT_Counter)
#ifndef Counter
#define Counter                 knh_Counter
#endif
#define IS_Counter(o)           (knh_Object_cid(o) == CLASS_Counter)
#define TYPE_Counter            CLASS_TONULLABLE(CLASS_Counter)
#define TYPE_Counter__          CLASS_TOPLURAL(CLASS_Counter)
#define CLASS_Counter__         CLASS_TOPLURAL(CLASS_Counter)
#define KNH_CFLAG_Counter       ((knh_flag_t)0)
#define KNH_FLAG_Counter        KNH_FLAG_CF2OF(KNH_CFLAG_Counter)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Amazon */
#define STRUCT_Amazon           ((knh_struct_t)54)
#define CLASS_Amazon            ((knh_class_t)54)
#define STRUCT_IS_Amazon(o)     (knh_Object_topsid(o) == STRUCT_Amazon)
#ifndef Amazon
#define Amazon                  knh_Amazon
#endif
#define IS_Amazon(o)            (knh_Object_cid(o) == CLASS_Amazon)
#define TYPE_Amazon             CLASS_TONULLABLE(CLASS_Amazon)
#define TYPE_Amazon__           CLASS_TOPLURAL(CLASS_Amazon)
#define CLASS_Amazon__          CLASS_TOPLURAL(CLASS_Amazon)
#define KNH_CFLAG_Amazon        ((knh_flag_t)0)
#define KNH_FLAG_Amazon         KNH_FLAG_CF2OF(KNH_CFLAG_Amazon)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* konohac */

/* ------------------------------------------------------------------------ */
/* Token */
#define STRUCT_Token            ((knh_struct_t)55)
#define CLASS_Token             ((knh_class_t)55)
#define STRUCT_IS_Token(o)      (knh_Object_topsid(o) == STRUCT_Token)
#ifndef Token
#define Token                   knh_Token
#endif
#define IS_Token(o)             (knh_Object_cid(o) == CLASS_Token)
#define TYPE_Token              CLASS_TONULLABLE(CLASS_Token)
#define TYPE_Token__            CLASS_TOPLURAL(CLASS_Token)
#define CLASS_Token__           CLASS_TOPLURAL(CLASS_Token)
#define KNH_CFLAG_Token         ((knh_flag_t)0)
#define KNH_FLAG_Token          KNH_FLAG_CF2OF(KNH_CFLAG_Token)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Stmt */
#define STRUCT_Stmt             ((knh_struct_t)56)
#define CLASS_Stmt              ((knh_class_t)56)
#define STRUCT_IS_Stmt(o)       (knh_Object_topsid(o) == STRUCT_Stmt)
#ifndef Stmt
#define Stmt                    knh_Stmt
#endif
#define IS_Stmt(o)              (knh_Object_cid(o) == CLASS_Stmt)
#define TYPE_Stmt               CLASS_TONULLABLE(CLASS_Stmt)
#define TYPE_Stmt__             CLASS_TOPLURAL(CLASS_Stmt)
#define CLASS_Stmt__            CLASS_TOPLURAL(CLASS_Stmt)
#define KNH_CFLAG_Stmt          ((knh_flag_t)0)
#define KNH_FLAG_Stmt           KNH_FLAG_CF2OF(KNH_CFLAG_Stmt)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Cmpl */
#define STRUCT_Cmpl             ((knh_struct_t)57)
#define CLASS_Cmpl              ((knh_class_t)57)
#define STRUCT_IS_Cmpl(o)       (knh_Object_topsid(o) == STRUCT_Cmpl)
#ifndef Cmpl
#define Cmpl                    knh_Cmpl
#endif
#define IS_Cmpl(o)              (knh_Object_cid(o) == CLASS_Cmpl)
#define TYPE_Cmpl               CLASS_TONULLABLE(CLASS_Cmpl)
#define TYPE_Cmpl__             CLASS_TOPLURAL(CLASS_Cmpl)
#define CLASS_Cmpl__            CLASS_TOPLURAL(CLASS_Cmpl)
#define KNH_CFLAG_Cmpl          ((knh_flag_t)0)
#define KNH_FLAG_Cmpl           KNH_FLAG_CF2OF(KNH_CFLAG_Cmpl)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* VirtualMachineCode */
#define STRUCT_VirtualMachineCode ((knh_struct_t)58)
#define CLASS_VirtualMachineCode ((knh_class_t)58)
#define STRUCT_IS_VirtualMachineCode(o) (knh_Object_topsid(o) == STRUCT_VirtualMachineCode)
#ifndef VirtualMachineCode
#define VirtualMachineCode      knh_VirtualMachineCode
#endif
#define IS_VirtualMachineCode(o) (knh_Object_cid(o) == CLASS_VirtualMachineCode)
#define TYPE_VirtualMachineCode CLASS_TONULLABLE(CLASS_VirtualMachineCode)
#define TYPE_VirtualMachineCode__ CLASS_TOPLURAL(CLASS_VirtualMachineCode)
#define CLASS_VirtualMachineCode__ CLASS_TOPLURAL(CLASS_VirtualMachineCode)
#define KNH_CFLAG_VirtualMachineCode ((knh_flag_t)0)
#define KNH_FLAG_VirtualMachineCode KNH_FLAG_CF2OF(KNH_CFLAG_VirtualMachineCode)

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* +math */

/* ------------------------------------------------------------------------ */
/* #mysql */

/* ======================================================================== */
/* [field] */
#define FIELDN_this                     ((knh_fieldn_t)0)
#define METHODN_this                    ((knh_methodn_t)0)
#define METHODN__this                   ((knh_methodn_t)0|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getThis                 ((knh_methodn_t)0|KNH_FLAG_MN_GETTER)
#define METHODN_setThis                 ((knh_methodn_t)0|KNH_FLAG_MN_SETTER)
#define FIELDN_vargs                    ((knh_fieldn_t)1)
#define METHODN_vargs                   ((knh_methodn_t)1)
#define METHODN__vargs                  ((knh_methodn_t)1|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getVargs                ((knh_methodn_t)1|KNH_FLAG_MN_GETTER)
#define METHODN_setVargs                ((knh_methodn_t)1|KNH_FLAG_MN_SETTER)
#define FIELDN_run                      ((knh_fieldn_t)2)
#define METHODN_run                     ((knh_methodn_t)2)
#define METHODN__run                    ((knh_methodn_t)2|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getRun                  ((knh_methodn_t)2|KNH_FLAG_MN_GETTER)
#define METHODN_setRun                  ((knh_methodn_t)2|KNH_FLAG_MN_SETTER)
#define FIELDN_new                      ((knh_fieldn_t)3)
#define METHODN_new                     ((knh_methodn_t)3)
#define METHODN__new                    ((knh_methodn_t)3|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getNew                  ((knh_methodn_t)3|KNH_FLAG_MN_GETTER)
#define METHODN_setNew                  ((knh_methodn_t)3|KNH_FLAG_MN_SETTER)
#define FIELDN_init                     ((knh_fieldn_t)4)
#define METHODN_init                    ((knh_methodn_t)4)
#define METHODN__init                   ((knh_methodn_t)4|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getInit                 ((knh_methodn_t)4|KNH_FLAG_MN_GETTER)
#define METHODN_setInit                 ((knh_methodn_t)4|KNH_FLAG_MN_SETTER)
#define FIELDN_new____array             ((knh_fieldn_t)5)
#define METHODN_new__array              ((knh_methodn_t)5)
#define METHODN__new__array             ((knh_methodn_t)5|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getNew__array           ((knh_methodn_t)5|KNH_FLAG_MN_GETTER)
#define METHODN_setNew__array           ((knh_methodn_t)5|KNH_FLAG_MN_SETTER)
#define FIELDN_value                    ((knh_fieldn_t)6)
#define METHODN_value                   ((knh_methodn_t)6)
#define METHODN__value                  ((knh_methodn_t)6|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getValue                ((knh_methodn_t)6|KNH_FLAG_MN_GETTER)
#define METHODN_setValue                ((knh_methodn_t)6|KNH_FLAG_MN_SETTER)
#define FIELDN_new____init              ((knh_fieldn_t)7)
#define METHODN_new__init               ((knh_methodn_t)7)
#define METHODN__new__init              ((knh_methodn_t)7|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getNew__init            ((knh_methodn_t)7|KNH_FLAG_MN_GETTER)
#define METHODN_setNew__init            ((knh_methodn_t)7|KNH_FLAG_MN_SETTER)
#define FIELDN_____fast                 ((knh_fieldn_t)8)
#define METHODN___fast                  ((knh_methodn_t)8)
#define METHODN____fast                 ((knh_methodn_t)8|KNH_FLAG_MN_MOVTEXT)
#define METHODN_get__fast               ((knh_methodn_t)8|KNH_FLAG_MN_GETTER)
#define METHODN_set__fast               ((knh_methodn_t)8|KNH_FLAG_MN_SETTER)
#define FIELDN_index                    ((knh_fieldn_t)9)
#define METHODN_index                   ((knh_methodn_t)9)
#define METHODN__index                  ((knh_methodn_t)9|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIndex                ((knh_methodn_t)9|KNH_FLAG_MN_GETTER)
#define METHODN_setIndex                ((knh_methodn_t)9|KNH_FLAG_MN_SETTER)
#define FIELDN_                         ((knh_fieldn_t)10)
#define METHODN_                        ((knh_methodn_t)10)
#define METHODN__                       ((knh_methodn_t)10|KNH_FLAG_MN_MOVTEXT)
#define METHODN_get                     ((knh_methodn_t)10|KNH_FLAG_MN_GETTER)
#define METHODN_set                     ((knh_methodn_t)10|KNH_FLAG_MN_SETTER)
#define FIELDN_opAdd                    ((knh_fieldn_t)11)
#define METHODN_opAdd                   ((knh_methodn_t)11)
#define METHODN__opAdd                  ((knh_methodn_t)11|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpAdd                ((knh_methodn_t)11|KNH_FLAG_MN_GETTER)
#define METHODN_setOpAdd                ((knh_methodn_t)11|KNH_FLAG_MN_SETTER)
#define FIELDN_v                        ((knh_fieldn_t)12)
#define METHODN_v                       ((knh_methodn_t)12)
#define METHODN__v                      ((knh_methodn_t)12|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getV                    ((knh_methodn_t)12|KNH_FLAG_MN_GETTER)
#define METHODN_setV                    ((knh_methodn_t)12|KNH_FLAG_MN_SETTER)
#define FIELDN_opSub                    ((knh_fieldn_t)13)
#define METHODN_opSub                   ((knh_methodn_t)13)
#define METHODN__opSub                  ((knh_methodn_t)13|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpSub                ((knh_methodn_t)13|KNH_FLAG_MN_GETTER)
#define METHODN_setOpSub                ((knh_methodn_t)13|KNH_FLAG_MN_SETTER)
#define FIELDN_n                        ((knh_fieldn_t)14)
#define METHODN_n                       ((knh_methodn_t)14)
#define METHODN__n                      ((knh_methodn_t)14|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getN                    ((knh_methodn_t)14|KNH_FLAG_MN_GETTER)
#define METHODN_setN                    ((knh_methodn_t)14|KNH_FLAG_MN_SETTER)
#define FIELDN_opMul                    ((knh_fieldn_t)15)
#define METHODN_opMul                   ((knh_methodn_t)15)
#define METHODN__opMul                  ((knh_methodn_t)15|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpMul                ((knh_methodn_t)15|KNH_FLAG_MN_GETTER)
#define METHODN_setOpMul                ((knh_methodn_t)15|KNH_FLAG_MN_SETTER)
#define FIELDN_opDiv                    ((knh_fieldn_t)16)
#define METHODN_opDiv                   ((knh_methodn_t)16)
#define METHODN__opDiv                  ((knh_methodn_t)16|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpDiv                ((knh_methodn_t)16|KNH_FLAG_MN_GETTER)
#define METHODN_setOpDiv                ((knh_methodn_t)16|KNH_FLAG_MN_SETTER)
#define FIELDN_opMod                    ((knh_fieldn_t)17)
#define METHODN_opMod                   ((knh_methodn_t)17)
#define METHODN__opMod                  ((knh_methodn_t)17|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpMod                ((knh_methodn_t)17|KNH_FLAG_MN_GETTER)
#define METHODN_setOpMod                ((knh_methodn_t)17|KNH_FLAG_MN_SETTER)
#define FIELDN_opEq                     ((knh_fieldn_t)18)
#define METHODN_opEq                    ((knh_methodn_t)18)
#define METHODN__opEq                   ((knh_methodn_t)18|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpEq                 ((knh_methodn_t)18|KNH_FLAG_MN_GETTER)
#define METHODN_setOpEq                 ((knh_methodn_t)18|KNH_FLAG_MN_SETTER)
#define FIELDN_opNeq                    ((knh_fieldn_t)19)
#define METHODN_opNeq                   ((knh_methodn_t)19)
#define METHODN__opNeq                  ((knh_methodn_t)19|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpNeq                ((knh_methodn_t)19|KNH_FLAG_MN_GETTER)
#define METHODN_setOpNeq                ((knh_methodn_t)19|KNH_FLAG_MN_SETTER)
#define FIELDN_opLt                     ((knh_fieldn_t)20)
#define METHODN_opLt                    ((knh_methodn_t)20)
#define METHODN__opLt                   ((knh_methodn_t)20|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpLt                 ((knh_methodn_t)20|KNH_FLAG_MN_GETTER)
#define METHODN_setOpLt                 ((knh_methodn_t)20|KNH_FLAG_MN_SETTER)
#define FIELDN_opLte                    ((knh_fieldn_t)21)
#define METHODN_opLte                   ((knh_methodn_t)21)
#define METHODN__opLte                  ((knh_methodn_t)21|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpLte                ((knh_methodn_t)21|KNH_FLAG_MN_GETTER)
#define METHODN_setOpLte                ((knh_methodn_t)21|KNH_FLAG_MN_SETTER)
#define FIELDN_opGt                     ((knh_fieldn_t)22)
#define METHODN_opGt                    ((knh_methodn_t)22)
#define METHODN__opGt                   ((knh_methodn_t)22|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpGt                 ((knh_methodn_t)22|KNH_FLAG_MN_GETTER)
#define METHODN_setOpGt                 ((knh_methodn_t)22|KNH_FLAG_MN_SETTER)
#define FIELDN_opGte                    ((knh_fieldn_t)23)
#define METHODN_opGte                   ((knh_methodn_t)23)
#define METHODN__opGte                  ((knh_methodn_t)23|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpGte                ((knh_methodn_t)23|KNH_FLAG_MN_GETTER)
#define METHODN_setOpGte                ((knh_methodn_t)23|KNH_FLAG_MN_SETTER)
#define FIELDN_opLogicalAnd             ((knh_fieldn_t)24)
#define METHODN_opLogicalAnd            ((knh_methodn_t)24)
#define METHODN__opLogicalAnd           ((knh_methodn_t)24|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpLogicalAnd         ((knh_methodn_t)24|KNH_FLAG_MN_GETTER)
#define METHODN_setOpLogicalAnd         ((knh_methodn_t)24|KNH_FLAG_MN_SETTER)
#define FIELDN_opLogicalOr              ((knh_fieldn_t)25)
#define METHODN_opLogicalOr             ((knh_methodn_t)25)
#define METHODN__opLogicalOr            ((knh_methodn_t)25|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpLogicalOr          ((knh_methodn_t)25|KNH_FLAG_MN_GETTER)
#define METHODN_setOpLogicalOr          ((knh_methodn_t)25|KNH_FLAG_MN_SETTER)
#define FIELDN_opLogicalXor             ((knh_fieldn_t)26)
#define METHODN_opLogicalXor            ((knh_methodn_t)26)
#define METHODN__opLogicalXor           ((knh_methodn_t)26|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpLogicalXor         ((knh_methodn_t)26|KNH_FLAG_MN_GETTER)
#define METHODN_setOpLogicalXor         ((knh_methodn_t)26|KNH_FLAG_MN_SETTER)
#define FIELDN_opLogicalNot             ((knh_fieldn_t)27)
#define METHODN_opLogicalNot            ((knh_methodn_t)27)
#define METHODN__opLogicalNot           ((knh_methodn_t)27|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpLogicalNot         ((knh_methodn_t)27|KNH_FLAG_MN_GETTER)
#define METHODN_setOpLogicalNot         ((knh_methodn_t)27|KNH_FLAG_MN_SETTER)
#define FIELDN_opLShift                 ((knh_fieldn_t)28)
#define METHODN_opLShift                ((knh_methodn_t)28)
#define METHODN__opLShift               ((knh_methodn_t)28|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpLShift             ((knh_methodn_t)28|KNH_FLAG_MN_GETTER)
#define METHODN_setOpLShift             ((knh_methodn_t)28|KNH_FLAG_MN_SETTER)
#define FIELDN_opRShift                 ((knh_fieldn_t)29)
#define METHODN_opRShift                ((knh_methodn_t)29)
#define METHODN__opRShift               ((knh_methodn_t)29|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpRShift             ((knh_methodn_t)29|KNH_FLAG_MN_GETTER)
#define METHODN_setOpRShift             ((knh_methodn_t)29|KNH_FLAG_MN_SETTER)
#define FIELDN_s                        ((knh_fieldn_t)30)
#define METHODN_s                       ((knh_methodn_t)30)
#define METHODN__s                      ((knh_methodn_t)30|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getS                    ((knh_methodn_t)30|KNH_FLAG_MN_GETTER)
#define METHODN_setS                    ((knh_methodn_t)30|KNH_FLAG_MN_SETTER)
#define FIELDN_w                        ((knh_fieldn_t)31)
#define METHODN_w                       ((knh_methodn_t)31)
#define METHODN__w                      ((knh_methodn_t)31|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getW                    ((knh_methodn_t)31|KNH_FLAG_MN_GETTER)
#define METHODN_setW                    ((knh_methodn_t)31|KNH_FLAG_MN_SETTER)
#define FIELDN_m                        ((knh_fieldn_t)32)
#define METHODN_m                       ((knh_methodn_t)32)
#define METHODN__m                      ((knh_methodn_t)32|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getM                    ((knh_methodn_t)32|KNH_FLAG_MN_GETTER)
#define METHODN_setM                    ((knh_methodn_t)32|KNH_FLAG_MN_SETTER)
#define FIELDN_x                        ((knh_fieldn_t)33)
#define METHODN_x                       ((knh_methodn_t)33)
#define METHODN__x                      ((knh_methodn_t)33|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getX                    ((knh_methodn_t)33|KNH_FLAG_MN_GETTER)
#define METHODN_setX                    ((knh_methodn_t)33|KNH_FLAG_MN_SETTER)
#define FIELDN_bits                     ((knh_fieldn_t)34)
#define METHODN_bits                    ((knh_methodn_t)34)
#define METHODN__bits                   ((knh_methodn_t)34|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getBits                 ((knh_methodn_t)34|KNH_FLAG_MN_GETTER)
#define METHODN_setBits                 ((knh_methodn_t)34|KNH_FLAG_MN_SETTER)
#define FIELDN_dump                     ((knh_fieldn_t)35)
#define METHODN_dump                    ((knh_methodn_t)35)
#define METHODN__dump                   ((knh_methodn_t)35|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getDump                 ((knh_methodn_t)35|KNH_FLAG_MN_GETTER)
#define METHODN_setDump                 ((knh_methodn_t)35|KNH_FLAG_MN_SETTER)
#define FIELDN_random                   ((knh_fieldn_t)36)
#define METHODN_random                  ((knh_methodn_t)36)
#define METHODN__random                 ((knh_methodn_t)36|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getRandom               ((knh_methodn_t)36|KNH_FLAG_MN_GETTER)
#define METHODN_setRandom               ((knh_methodn_t)36|KNH_FLAG_MN_SETTER)
#define FIELDN_in                       ((knh_fieldn_t)37)
#define METHODN_in                      ((knh_methodn_t)37)
#define METHODN__in                     ((knh_methodn_t)37|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIn                   ((knh_methodn_t)37|KNH_FLAG_MN_GETTER)
#define METHODN_setIn                   ((knh_methodn_t)37|KNH_FLAG_MN_SETTER)
#define FIELDN_input                    ((knh_fieldn_t)38)
#define METHODN_input                   ((knh_methodn_t)38)
#define METHODN__input                  ((knh_methodn_t)38|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getInput                ((knh_methodn_t)38|KNH_FLAG_MN_GETTER)
#define METHODN_setInput                ((knh_methodn_t)38|KNH_FLAG_MN_SETTER)
#define FIELDN_out                      ((knh_fieldn_t)39)
#define METHODN_out                     ((knh_methodn_t)39)
#define METHODN__out                    ((knh_methodn_t)39|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOut                  ((knh_methodn_t)39|KNH_FLAG_MN_GETTER)
#define METHODN_setOut                  ((knh_methodn_t)39|KNH_FLAG_MN_SETTER)
#define FIELDN_err                      ((knh_fieldn_t)40)
#define METHODN_err                     ((knh_methodn_t)40)
#define METHODN__err                    ((knh_methodn_t)40|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getErr                  ((knh_methodn_t)40|KNH_FLAG_MN_GETTER)
#define METHODN_setErr                  ((knh_methodn_t)40|KNH_FLAG_MN_SETTER)
#define FIELDN_another                  ((knh_fieldn_t)41)
#define METHODN_another                 ((knh_methodn_t)41)
#define METHODN__another                ((knh_methodn_t)41|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getAnother              ((knh_methodn_t)41|KNH_FLAG_MN_GETTER)
#define METHODN_setAnother              ((knh_methodn_t)41|KNH_FLAG_MN_SETTER)
#define FIELDN_urn                      ((knh_fieldn_t)42)
#define METHODN_urn                     ((knh_methodn_t)42)
#define METHODN__urn                    ((knh_methodn_t)42|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getUrn                  ((knh_methodn_t)42|KNH_FLAG_MN_GETTER)
#define METHODN_setUrn                  ((knh_methodn_t)42|KNH_FLAG_MN_SETTER)
#define FIELDN_query                    ((knh_fieldn_t)43)
#define METHODN_query                   ((knh_methodn_t)43)
#define METHODN__query                  ((knh_methodn_t)43|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getQuery                ((knh_methodn_t)43|KNH_FLAG_MN_GETTER)
#define METHODN_setQuery                ((knh_methodn_t)43|KNH_FLAG_MN_SETTER)
#define FIELDN_count                    ((knh_fieldn_t)44)
#define METHODN_count                   ((knh_methodn_t)44)
#define METHODN__count                  ((knh_methodn_t)44|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getCount                ((knh_methodn_t)44|KNH_FLAG_MN_GETTER)
#define METHODN_setCount                ((knh_methodn_t)44|KNH_FLAG_MN_SETTER)
#define FIELDN_reset                    ((knh_fieldn_t)45)
#define METHODN_reset                   ((knh_methodn_t)45)
#define METHODN__reset                  ((knh_methodn_t)45|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getReset                ((knh_methodn_t)45|KNH_FLAG_MN_GETTER)
#define METHODN_setReset                ((knh_methodn_t)45|KNH_FLAG_MN_SETTER)
#define FIELDN_size                     ((knh_fieldn_t)46)
#define METHODN_size                    ((knh_methodn_t)46)
#define METHODN__size                   ((knh_methodn_t)46|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getSize                 ((knh_methodn_t)46|KNH_FLAG_MN_GETTER)
#define METHODN_setSize                 ((knh_methodn_t)46|KNH_FLAG_MN_SETTER)
#define FIELDN_term                     ((knh_fieldn_t)47)
#define METHODN_term                    ((knh_methodn_t)47)
#define METHODN__term                   ((knh_methodn_t)47|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getTerm                 ((knh_methodn_t)47|KNH_FLAG_MN_GETTER)
#define METHODN_setTerm                 ((knh_methodn_t)47|KNH_FLAG_MN_SETTER)
#define FIELDN_add____fast              ((knh_fieldn_t)48)
#define METHODN_add__fast               ((knh_methodn_t)48)
#define METHODN__add__fast              ((knh_methodn_t)48|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getAdd__fast            ((knh_methodn_t)48|KNH_FLAG_MN_GETTER)
#define METHODN_setAdd__fast            ((knh_methodn_t)48|KNH_FLAG_MN_SETTER)
#define FIELDN_add                      ((knh_fieldn_t)49)
#define METHODN_add                     ((knh_methodn_t)49)
#define METHODN__add                    ((knh_methodn_t)49|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getAdd                  ((knh_methodn_t)49|KNH_FLAG_MN_GETTER)
#define METHODN_setAdd                  ((knh_methodn_t)49|KNH_FLAG_MN_SETTER)
#define FIELDN_clear                    ((knh_fieldn_t)50)
#define METHODN_clear                   ((knh_methodn_t)50)
#define METHODN__clear                  ((knh_methodn_t)50|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getClear                ((knh_methodn_t)50|KNH_FLAG_MN_GETTER)
#define METHODN_setClear                ((knh_methodn_t)50|KNH_FLAG_MN_SETTER)
#define FIELDN_readLine                 ((knh_fieldn_t)51)
#define METHODN_readLine                ((knh_methodn_t)51)
#define METHODN__readLine               ((knh_methodn_t)51|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getReadLine             ((knh_methodn_t)51|KNH_FLAG_MN_GETTER)
#define METHODN_setReadLine             ((knh_methodn_t)51|KNH_FLAG_MN_SETTER)
#define FIELDN_close                    ((knh_fieldn_t)52)
#define METHODN_close                   ((knh_methodn_t)52)
#define METHODN__close                  ((knh_methodn_t)52|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getClose                ((knh_methodn_t)52|KNH_FLAG_MN_GETTER)
#define METHODN_setClose                ((knh_methodn_t)52|KNH_FLAG_MN_SETTER)
#define FIELDN_pop                      ((knh_fieldn_t)53)
#define METHODN_pop                     ((knh_methodn_t)53)
#define METHODN__pop                    ((knh_methodn_t)53|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getPop                  ((knh_methodn_t)53|KNH_FLAG_MN_GETTER)
#define METHODN_setPop                  ((knh_methodn_t)53|KNH_FLAG_MN_SETTER)
#define FIELDN_slice                    ((knh_fieldn_t)54)
#define METHODN_slice                   ((knh_methodn_t)54)
#define METHODN__slice                  ((knh_methodn_t)54|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getSlice                ((knh_methodn_t)54|KNH_FLAG_MN_GETTER)
#define METHODN_setSlice                ((knh_methodn_t)54|KNH_FLAG_MN_SETTER)
#define FIELDN_start                    ((knh_fieldn_t)55)
#define METHODN_start                   ((knh_methodn_t)55)
#define METHODN__start                  ((knh_methodn_t)55|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getStart                ((knh_methodn_t)55|KNH_FLAG_MN_GETTER)
#define METHODN_setStart                ((knh_methodn_t)55|KNH_FLAG_MN_SETTER)
#define FIELDN_end                      ((knh_fieldn_t)56)
#define METHODN_end                     ((knh_methodn_t)56)
#define METHODN__end                    ((knh_methodn_t)56|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getEnd                  ((knh_methodn_t)56|KNH_FLAG_MN_GETTER)
#define METHODN_setEnd                  ((knh_methodn_t)56|KNH_FLAG_MN_SETTER)
#define FIELDN_inputStream              ((knh_fieldn_t)57)
#define METHODN_inputStream             ((knh_methodn_t)57)
#define METHODN__inputStream            ((knh_methodn_t)57|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getInputStream          ((knh_methodn_t)57|KNH_FLAG_MN_GETTER)
#define METHODN_setInputStream          ((knh_methodn_t)57|KNH_FLAG_MN_SETTER)
#define FIELDN_outputStream             ((knh_fieldn_t)58)
#define METHODN_outputStream            ((knh_methodn_t)58)
#define METHODN__outputStream           ((knh_methodn_t)58|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOutputStream         ((knh_methodn_t)58|KNH_FLAG_MN_GETTER)
#define METHODN_setOutputStream         ((knh_methodn_t)58|KNH_FLAG_MN_SETTER)
#define FIELDN_match                    ((knh_fieldn_t)59)
#define METHODN_match                   ((knh_methodn_t)59)
#define METHODN__match                  ((knh_methodn_t)59|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getMatch                ((knh_methodn_t)59|KNH_FLAG_MN_GETTER)
#define METHODN_setMatch                ((knh_methodn_t)59|KNH_FLAG_MN_SETTER)
#define FIELDN_initialCapacity          ((knh_fieldn_t)60)
#define METHODN_initialCapacity         ((knh_methodn_t)60)
#define METHODN__initialCapacity        ((knh_methodn_t)60|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getInitialCapacity      ((knh_methodn_t)60|KNH_FLAG_MN_GETTER)
#define METHODN_setInitialCapacity      ((knh_methodn_t)60|KNH_FLAG_MN_SETTER)
#define FIELDN_key                      ((knh_fieldn_t)61)
#define METHODN_key                     ((knh_methodn_t)61)
#define METHODN__key                    ((knh_methodn_t)61|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getKey                  ((knh_methodn_t)61|KNH_FLAG_MN_GETTER)
#define METHODN_setKey                  ((knh_methodn_t)61|KNH_FLAG_MN_SETTER)
#define FIELDN_append                   ((knh_fieldn_t)62)
#define METHODN_append                  ((knh_methodn_t)62)
#define METHODN__append                 ((knh_methodn_t)62|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getAppend               ((knh_methodn_t)62|KNH_FLAG_MN_GETTER)
#define METHODN_setAppend               ((knh_methodn_t)62|KNH_FLAG_MN_SETTER)
#define FIELDN_remove                   ((knh_fieldn_t)63)
#define METHODN_remove                  ((knh_methodn_t)63)
#define METHODN__remove                 ((knh_methodn_t)63|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getRemove               ((knh_methodn_t)63|KNH_FLAG_MN_GETTER)
#define METHODN_setRemove               ((knh_methodn_t)63|KNH_FLAG_MN_SETTER)
#define FIELDN_opIn                     ((knh_fieldn_t)64)
#define METHODN_opIn                    ((knh_methodn_t)64)
#define METHODN__opIn                   ((knh_methodn_t)64|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpIn                 ((knh_methodn_t)64|KNH_FLAG_MN_GETTER)
#define METHODN_setOpIn                 ((knh_methodn_t)64|KNH_FLAG_MN_SETTER)
#define FIELDN_keys                     ((knh_fieldn_t)65)
#define METHODN_keys                    ((knh_methodn_t)65)
#define METHODN__keys                   ((knh_methodn_t)65|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getKeys                 ((knh_methodn_t)65|KNH_FLAG_MN_GETTER)
#define METHODN_setKeys                 ((knh_methodn_t)65|KNH_FLAG_MN_SETTER)
#define FIELDN_write                    ((knh_fieldn_t)66)
#define METHODN_write                   ((knh_methodn_t)66)
#define METHODN__write                  ((knh_methodn_t)66|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getWrite                ((knh_methodn_t)66|KNH_FLAG_MN_GETTER)
#define METHODN_setWrite                ((knh_methodn_t)66|KNH_FLAG_MN_SETTER)
#define FIELDN_buf                      ((knh_fieldn_t)67)
#define METHODN_buf                     ((knh_methodn_t)67)
#define METHODN__buf                    ((knh_methodn_t)67|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getBuf                  ((knh_methodn_t)67|KNH_FLAG_MN_GETTER)
#define METHODN_setBuf                  ((knh_methodn_t)67|KNH_FLAG_MN_SETTER)
#define FIELDN_flush                    ((knh_fieldn_t)68)
#define METHODN_flush                   ((knh_methodn_t)68)
#define METHODN__flush                  ((knh_methodn_t)68|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getFlush                ((knh_methodn_t)68|KNH_FLAG_MN_GETTER)
#define METHODN_setFlush                ((knh_methodn_t)68|KNH_FLAG_MN_SETTER)
#define FIELDN_runtime                  ((knh_fieldn_t)69)
#define METHODN_runtime                 ((knh_methodn_t)69)
#define METHODN__runtime                ((knh_methodn_t)69|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getRuntime              ((knh_methodn_t)69|KNH_FLAG_MN_GETTER)
#define METHODN_setRuntime              ((knh_methodn_t)69|KNH_FLAG_MN_SETTER)
#define FIELDN_opInstanceof             ((knh_fieldn_t)70)
#define METHODN_opInstanceof            ((knh_methodn_t)70)
#define METHODN__opInstanceof           ((knh_methodn_t)70|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpInstanceof         ((knh_methodn_t)70|KNH_FLAG_MN_GETTER)
#define METHODN_setOpInstanceof         ((knh_methodn_t)70|KNH_FLAG_MN_SETTER)
#define FIELDN_c                        ((knh_fieldn_t)71)
#define METHODN_c                       ((knh_methodn_t)71)
#define METHODN__c                      ((knh_methodn_t)71|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getC                    ((knh_methodn_t)71|KNH_FLAG_MN_GETTER)
#define METHODN_setC                    ((knh_methodn_t)71|KNH_FLAG_MN_SETTER)
#define FIELDN_property                 ((knh_fieldn_t)72)
#define METHODN_property                ((knh_methodn_t)72)
#define METHODN__property               ((knh_methodn_t)72|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getProperty             ((knh_methodn_t)72|KNH_FLAG_MN_GETTER)
#define METHODN_setProperty             ((knh_methodn_t)72|KNH_FLAG_MN_SETTER)
#define FIELDN_class                    ((knh_fieldn_t)73)
#define METHODN_class                   ((knh_methodn_t)73)
#define METHODN__class                  ((knh_methodn_t)73|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getClass                ((knh_methodn_t)73|KNH_FLAG_MN_GETTER)
#define METHODN_setClass                ((knh_methodn_t)73|KNH_FLAG_MN_SETTER)
#define FIELDN_name                     ((knh_fieldn_t)74)
#define METHODN_name                    ((knh_methodn_t)74)
#define METHODN__name                   ((knh_methodn_t)74|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getName                 ((knh_methodn_t)74|KNH_FLAG_MN_GETTER)
#define METHODN_setName                 ((knh_methodn_t)74|KNH_FLAG_MN_SETTER)
#define FIELDN_isAbstract               ((knh_fieldn_t)75)
#define METHODN_isAbstract              ((knh_methodn_t)75)
#define METHODN__isAbstract             ((knh_methodn_t)75|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsAbstract           ((knh_methodn_t)75|KNH_FLAG_MN_GETTER)
#define METHODN_setIsAbstract           ((knh_methodn_t)75|KNH_FLAG_MN_SETTER)
#define FIELDN_uRN                      ((knh_fieldn_t)76)
#define METHODN_uRN                     ((knh_methodn_t)76)
#define METHODN__uRN                    ((knh_methodn_t)76|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getURN                  ((knh_methodn_t)76|KNH_FLAG_MN_GETTER)
#define METHODN_setURN                  ((knh_methodn_t)76|KNH_FLAG_MN_SETTER)
#define FIELDN_next                     ((knh_fieldn_t)77)
#define METHODN_next                    ((knh_methodn_t)77)
#define METHODN__next                   ((knh_methodn_t)77|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getNext                 ((knh_methodn_t)77|KNH_FLAG_MN_GETTER)
#define METHODN_setNext                 ((knh_methodn_t)77|KNH_FLAG_MN_SETTER)
#define FIELDN_e                        ((knh_fieldn_t)78)
#define METHODN_e                       ((knh_methodn_t)78)
#define METHODN__e                      ((knh_methodn_t)78|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getE                    ((knh_methodn_t)78|KNH_FLAG_MN_GETTER)
#define METHODN_setE                    ((knh_methodn_t)78|KNH_FLAG_MN_SETTER)
#define FIELDN_msg                      ((knh_fieldn_t)79)
#define METHODN_msg                     ((knh_methodn_t)79)
#define METHODN__msg                    ((knh_methodn_t)79|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getMsg                  ((knh_methodn_t)79|KNH_FLAG_MN_GETTER)
#define METHODN_setMsg                  ((knh_methodn_t)79|KNH_FLAG_MN_SETTER)
#define FIELDN_bag                      ((knh_fieldn_t)80)
#define METHODN_bag                     ((knh_methodn_t)80)
#define METHODN__bag                    ((knh_methodn_t)80|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getBag                  ((knh_methodn_t)80|KNH_FLAG_MN_GETTER)
#define METHODN_setBag                  ((knh_methodn_t)80|KNH_FLAG_MN_SETTER)
#define FIELDN_compare                  ((knh_fieldn_t)81)
#define METHODN_compare                 ((knh_methodn_t)81)
#define METHODN__compare                ((knh_methodn_t)81|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getCompare              ((knh_methodn_t)81|KNH_FLAG_MN_GETTER)
#define METHODN_setCompare              ((knh_methodn_t)81|KNH_FLAG_MN_SETTER)
#define FIELDN_other                    ((knh_fieldn_t)82)
#define METHODN_other                   ((knh_methodn_t)82)
#define METHODN__other                  ((knh_methodn_t)82|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOther                ((knh_methodn_t)82|KNH_FLAG_MN_GETTER)
#define METHODN_setOther                ((knh_methodn_t)82|KNH_FLAG_MN_SETTER)
#define FIELDN_opNot                    ((knh_fieldn_t)83)
#define METHODN_opNot                   ((knh_methodn_t)83)
#define METHODN__opNot                  ((knh_methodn_t)83|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpNot                ((knh_methodn_t)83|KNH_FLAG_MN_GETTER)
#define METHODN_setOpNot                ((knh_methodn_t)83|KNH_FLAG_MN_SETTER)
#define FIELDN_opSeq                    ((knh_fieldn_t)84)
#define METHODN_opSeq                   ((knh_methodn_t)84)
#define METHODN__opSeq                  ((knh_methodn_t)84|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpSeq                ((knh_methodn_t)84|KNH_FLAG_MN_GETTER)
#define METHODN_setOpSeq                ((knh_methodn_t)84|KNH_FLAG_MN_SETTER)
#define FIELDN_opIsMapTo                ((knh_fieldn_t)85)
#define METHODN_opIsMapTo               ((knh_methodn_t)85)
#define METHODN__opIsMapTo              ((knh_methodn_t)85|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOpIsMapTo            ((knh_methodn_t)85|KNH_FLAG_MN_GETTER)
#define METHODN_setOpIsMapTo            ((knh_methodn_t)85|KNH_FLAG_MN_SETTER)
#define FIELDN_empty                    ((knh_fieldn_t)86)
#define METHODN_empty                   ((knh_methodn_t)86)
#define METHODN__empty                  ((knh_methodn_t)86|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getEmpty                ((knh_methodn_t)86|KNH_FLAG_MN_GETTER)
#define METHODN_setEmpty                ((knh_methodn_t)86|KNH_FLAG_MN_SETTER)
#define FIELDN_refc                     ((knh_fieldn_t)87)
#define METHODN_refc                    ((knh_methodn_t)87)
#define METHODN__refc                   ((knh_methodn_t)87|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getRefc                 ((knh_methodn_t)87|KNH_FLAG_MN_GETTER)
#define METHODN_setRefc                 ((knh_methodn_t)87|KNH_FLAG_MN_SETTER)
#define FIELDN_addr                     ((knh_fieldn_t)88)
#define METHODN_addr                    ((knh_methodn_t)88)
#define METHODN__addr                   ((knh_methodn_t)88|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getAddr                 ((knh_methodn_t)88|KNH_FLAG_MN_GETTER)
#define METHODN_setAddr                 ((knh_methodn_t)88|KNH_FLAG_MN_SETTER)
#define FIELDN_equals                   ((knh_fieldn_t)89)
#define METHODN_equals                  ((knh_methodn_t)89)
#define METHODN__equals                 ((knh_methodn_t)89|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getEquals               ((knh_methodn_t)89|KNH_FLAG_MN_GETTER)
#define METHODN_setEquals               ((knh_methodn_t)89|KNH_FLAG_MN_SETTER)
#define FIELDN_startsWith               ((knh_fieldn_t)90)
#define METHODN_startsWith              ((knh_methodn_t)90)
#define METHODN__startsWith             ((knh_methodn_t)90|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getStartsWith           ((knh_methodn_t)90|KNH_FLAG_MN_GETTER)
#define METHODN_setStartsWith           ((knh_methodn_t)90|KNH_FLAG_MN_SETTER)
#define FIELDN_endsWith                 ((knh_fieldn_t)91)
#define METHODN_endsWith                ((knh_methodn_t)91)
#define METHODN__endsWith               ((knh_methodn_t)91|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getEndsWith             ((knh_methodn_t)91|KNH_FLAG_MN_GETTER)
#define METHODN_setEndsWith             ((knh_methodn_t)91|KNH_FLAG_MN_SETTER)
#define FIELDN_placeOrder               ((knh_fieldn_t)92)
#define METHODN_placeOrder              ((knh_methodn_t)92)
#define METHODN__placeOrder             ((knh_methodn_t)92|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getPlaceOrder           ((knh_methodn_t)92|KNH_FLAG_MN_GETTER)
#define METHODN_setPlaceOrder           ((knh_methodn_t)92|KNH_FLAG_MN_SETTER)
#define FIELDN_uname                    ((knh_fieldn_t)93)
#define METHODN_uname                   ((knh_methodn_t)93)
#define METHODN__uname                  ((knh_methodn_t)93|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getUname                ((knh_methodn_t)93|KNH_FLAG_MN_GETTER)
#define METHODN_setUname                ((knh_methodn_t)93|KNH_FLAG_MN_SETTER)
#define FIELDN_order                    ((knh_fieldn_t)94)
#define METHODN_order                   ((knh_methodn_t)94)
#define METHODN__order                  ((knh_methodn_t)94|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getOrder                ((knh_methodn_t)94|KNH_FLAG_MN_GETTER)
#define METHODN_setOrder                ((knh_methodn_t)94|KNH_FLAG_MN_SETTER)
#define FIELDN_code                     ((knh_fieldn_t)95)
#define METHODN_code                    ((knh_methodn_t)95)
#define METHODN__code                   ((knh_methodn_t)95|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getCode                 ((knh_methodn_t)95|KNH_FLAG_MN_GETTER)
#define METHODN_setCode                 ((knh_methodn_t)95|KNH_FLAG_MN_SETTER)
#define FIELDN_sin                      ((knh_fieldn_t)96)
#define METHODN_sin                     ((knh_methodn_t)96)
#define METHODN__sin                    ((knh_methodn_t)96|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getSin                  ((knh_methodn_t)96|KNH_FLAG_MN_GETTER)
#define METHODN_setSin                  ((knh_methodn_t)96|KNH_FLAG_MN_SETTER)
#define FIELDN_isRelease                ((knh_fieldn_t)97)
#define METHODN_isRelease               ((knh_methodn_t)97)
#define METHODN__isRelease              ((knh_methodn_t)97|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsRelease            ((knh_methodn_t)97|KNH_FLAG_MN_GETTER)
#define METHODN_setIsRelease            ((knh_methodn_t)97|KNH_FLAG_MN_SETTER)
#define FIELDN_isDebug                  ((knh_fieldn_t)98)
#define METHODN_isDebug                 ((knh_methodn_t)98)
#define METHODN__isDebug                ((knh_methodn_t)98|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsDebug              ((knh_methodn_t)98|KNH_FLAG_MN_GETTER)
#define METHODN_setIsDebug              ((knh_methodn_t)98|KNH_FLAG_MN_SETTER)
#define FIELDN_isImmutable              ((knh_fieldn_t)99)
#define METHODN_isImmutable             ((knh_methodn_t)99)
#define METHODN__isImmutable            ((knh_methodn_t)99|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsImmutable          ((knh_methodn_t)99|KNH_FLAG_MN_GETTER)
#define METHODN_setIsImmutable          ((knh_methodn_t)99|KNH_FLAG_MN_SETTER)
#define FIELDN_hasMetaData              ((knh_fieldn_t)100)
#define METHODN_hasMetaData             ((knh_methodn_t)100)
#define METHODN__hasMetaData            ((knh_methodn_t)100|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getHasMetaData          ((knh_methodn_t)100|KNH_FLAG_MN_GETTER)
#define METHODN_setHasMetaData          ((knh_methodn_t)100|KNH_FLAG_MN_SETTER)
#define FIELDN_isSynchronized           ((knh_fieldn_t)101)
#define METHODN_isSynchronized          ((knh_methodn_t)101)
#define METHODN__isSynchronized         ((knh_methodn_t)101|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsSynchronized       ((knh_methodn_t)101|KNH_FLAG_MN_GETTER)
#define METHODN_setIsSynchronized       ((knh_methodn_t)101|KNH_FLAG_MN_SETTER)
#define FIELDN_isModified               ((knh_fieldn_t)102)
#define METHODN_isModified              ((knh_methodn_t)102)
#define METHODN__isModified             ((knh_methodn_t)102|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsModified           ((knh_methodn_t)102|KNH_FLAG_MN_GETTER)
#define METHODN_setIsModified           ((knh_methodn_t)102|KNH_FLAG_MN_SETTER)
#define FIELDN_modified                 ((knh_fieldn_t)103)
#define METHODN_modified                ((knh_methodn_t)103)
#define METHODN__modified               ((knh_methodn_t)103|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getModified             ((knh_methodn_t)103|KNH_FLAG_MN_GETTER)
#define METHODN_setModified             ((knh_methodn_t)103|KNH_FLAG_MN_SETTER)
#define FIELDN_b                        ((knh_fieldn_t)104)
#define METHODN_b                       ((knh_methodn_t)104)
#define METHODN__b                      ((knh_methodn_t)104|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getB                    ((knh_methodn_t)104|KNH_FLAG_MN_GETTER)
#define METHODN_setB                    ((knh_methodn_t)104|KNH_FLAG_MN_SETTER)
#define FIELDN_isMetaExtensible         ((knh_fieldn_t)105)
#define METHODN_isMetaExtensible        ((knh_methodn_t)105)
#define METHODN__isMetaExtensible       ((knh_methodn_t)105|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsMetaExtensible     ((knh_methodn_t)105|KNH_FLAG_MN_GETTER)
#define METHODN_setIsMetaExtensible     ((knh_methodn_t)105|KNH_FLAG_MN_SETTER)
#define FIELDN_isPrivate                ((knh_fieldn_t)106)
#define METHODN_isPrivate               ((knh_methodn_t)106)
#define METHODN__isPrivate              ((knh_methodn_t)106|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsPrivate            ((knh_methodn_t)106|KNH_FLAG_MN_GETTER)
#define METHODN_setIsPrivate            ((knh_methodn_t)106|KNH_FLAG_MN_SETTER)
#define FIELDN_isPublic                 ((knh_fieldn_t)107)
#define METHODN_isPublic                ((knh_methodn_t)107)
#define METHODN__isPublic               ((knh_methodn_t)107|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsPublic             ((knh_methodn_t)107|KNH_FLAG_MN_GETTER)
#define METHODN_setIsPublic             ((knh_methodn_t)107|KNH_FLAG_MN_SETTER)
#define FIELDN_isFinal                  ((knh_fieldn_t)108)
#define METHODN_isFinal                 ((knh_methodn_t)108)
#define METHODN__isFinal                ((knh_methodn_t)108|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsFinal              ((knh_methodn_t)108|KNH_FLAG_MN_GETTER)
#define METHODN_setIsFinal              ((knh_methodn_t)108|KNH_FLAG_MN_SETTER)
#define FIELDN_isSystem                 ((knh_fieldn_t)109)
#define METHODN_isSystem                ((knh_methodn_t)109)
#define METHODN__isSystem               ((knh_methodn_t)109|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsSystem             ((knh_methodn_t)109|KNH_FLAG_MN_GETTER)
#define METHODN_setIsSystem             ((knh_methodn_t)109|KNH_FLAG_MN_SETTER)
#define FIELDN_isNA                     ((knh_fieldn_t)110)
#define METHODN_isNA                    ((knh_methodn_t)110)
#define METHODN__isNA                   ((knh_methodn_t)110|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsNA                 ((knh_methodn_t)110|KNH_FLAG_MN_GETTER)
#define METHODN_setIsNA                 ((knh_methodn_t)110|KNH_FLAG_MN_SETTER)
#define FIELDN_isVirtual                ((knh_fieldn_t)111)
#define METHODN_isVirtual               ((knh_methodn_t)111)
#define METHODN__isVirtual              ((knh_methodn_t)111|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsVirtual            ((knh_methodn_t)111|KNH_FLAG_MN_GETTER)
#define METHODN_setIsVirtual            ((knh_methodn_t)111|KNH_FLAG_MN_SETTER)
#define FIELDN_isStatic                 ((knh_fieldn_t)112)
#define METHODN_isStatic                ((knh_methodn_t)112)
#define METHODN__isStatic               ((knh_methodn_t)112|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsStatic             ((knh_methodn_t)112|KNH_FLAG_MN_GETTER)
#define METHODN_setIsStatic             ((knh_methodn_t)112|KNH_FLAG_MN_SETTER)
#define FIELDN_isClass                  ((knh_fieldn_t)113)
#define METHODN_isClass                 ((knh_methodn_t)113)
#define METHODN__isClass                ((knh_methodn_t)113|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsClass              ((knh_methodn_t)113|KNH_FLAG_MN_GETTER)
#define METHODN_setIsClass              ((knh_methodn_t)113|KNH_FLAG_MN_SETTER)
#define FIELDN_isVarArgs                ((knh_fieldn_t)114)
#define METHODN_isVarArgs               ((knh_methodn_t)114)
#define METHODN__isVarArgs              ((knh_methodn_t)114|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsVarArgs            ((knh_methodn_t)114|KNH_FLAG_MN_GETTER)
#define METHODN_setIsVarArgs            ((knh_methodn_t)114|KNH_FLAG_MN_SETTER)
#define FIELDN_isAspect                 ((knh_fieldn_t)115)
#define METHODN_isAspect                ((knh_methodn_t)115)
#define METHODN__isAspect               ((knh_methodn_t)115|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsAspect             ((knh_methodn_t)115|KNH_FLAG_MN_GETTER)
#define METHODN_setIsAspect             ((knh_methodn_t)115|KNH_FLAG_MN_SETTER)
#define FIELDN_isInterface              ((knh_fieldn_t)116)
#define METHODN_isInterface             ((knh_methodn_t)116)
#define METHODN__isInterface            ((knh_methodn_t)116|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsInterface          ((knh_methodn_t)116|KNH_FLAG_MN_GETTER)
#define METHODN_setIsInterface          ((knh_methodn_t)116|KNH_FLAG_MN_SETTER)
#define FIELDN_isSignificant            ((knh_fieldn_t)117)
#define METHODN_isSignificant           ((knh_methodn_t)117)
#define METHODN__isSignificant          ((knh_methodn_t)117|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsSignificant        ((knh_methodn_t)117|KNH_FLAG_MN_GETTER)
#define METHODN_setIsSignificant        ((knh_methodn_t)117|KNH_FLAG_MN_SETTER)
#define FIELDN_isSynonym                ((knh_fieldn_t)118)
#define METHODN_isSynonym               ((knh_methodn_t)118)
#define METHODN__isSynonym              ((knh_methodn_t)118|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsSynonym            ((knh_methodn_t)118|KNH_FLAG_MN_GETTER)
#define METHODN_setIsSynonym            ((knh_methodn_t)118|KNH_FLAG_MN_SETTER)
#define FIELDN_isLossLess               ((knh_fieldn_t)119)
#define METHODN_isLossLess              ((knh_methodn_t)119)
#define METHODN__isLossLess             ((knh_methodn_t)119|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsLossLess           ((knh_methodn_t)119|KNH_FLAG_MN_GETTER)
#define METHODN_setIsLossLess           ((knh_methodn_t)119|KNH_FLAG_MN_SETTER)
#define FIELDN_isTotal                  ((knh_fieldn_t)120)
#define METHODN_isTotal                 ((knh_methodn_t)120)
#define METHODN__isTotal                ((knh_methodn_t)120|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsTotal              ((knh_methodn_t)120|KNH_FLAG_MN_GETTER)
#define METHODN_setIsTotal              ((knh_methodn_t)120|KNH_FLAG_MN_SETTER)
#define FIELDN_isPartial                ((knh_fieldn_t)121)
#define METHODN_isPartial               ((knh_methodn_t)121)
#define METHODN__isPartial              ((knh_methodn_t)121|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsPartial            ((knh_methodn_t)121|KNH_FLAG_MN_GETTER)
#define METHODN_setIsPartial            ((knh_methodn_t)121|KNH_FLAG_MN_SETTER)
#define FIELDN_isTemporal               ((knh_fieldn_t)122)
#define METHODN_isTemporal              ((knh_methodn_t)122)
#define METHODN__isTemporal             ((knh_methodn_t)122|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsTemporal           ((knh_methodn_t)122|KNH_FLAG_MN_GETTER)
#define METHODN_setIsTemporal           ((knh_methodn_t)122|KNH_FLAG_MN_SETTER)
#define FIELDN_isLocal                  ((knh_fieldn_t)123)
#define METHODN_isLocal                 ((knh_methodn_t)123)
#define METHODN__isLocal                ((knh_methodn_t)123|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsLocal              ((knh_methodn_t)123|KNH_FLAG_MN_GETTER)
#define METHODN_setIsLocal              ((knh_methodn_t)123|KNH_FLAG_MN_SETTER)
#define FIELDN_isDerived                ((knh_fieldn_t)124)
#define METHODN_isDerived               ((knh_methodn_t)124)
#define METHODN__isDerived              ((knh_methodn_t)124|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsDerived            ((knh_methodn_t)124|KNH_FLAG_MN_GETTER)
#define METHODN_setIsDerived            ((knh_methodn_t)124|KNH_FLAG_MN_SETTER)
#define FIELDN_isUnsigned               ((knh_fieldn_t)125)
#define METHODN_isUnsigned              ((knh_methodn_t)125)
#define METHODN__isUnsigned             ((knh_methodn_t)125|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsUnsigned           ((knh_methodn_t)125|KNH_FLAG_MN_GETTER)
#define METHODN_setIsUnsigned           ((knh_methodn_t)125|KNH_FLAG_MN_SETTER)
#define FIELDN_isFatal                  ((knh_fieldn_t)126)
#define METHODN_isFatal                 ((knh_methodn_t)126)
#define METHODN__isFatal                ((knh_methodn_t)126|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsFatal              ((knh_methodn_t)126|KNH_FLAG_MN_GETTER)
#define METHODN_setIsFatal              ((knh_methodn_t)126|KNH_FLAG_MN_SETTER)
#define FIELDN_isLogging                ((knh_fieldn_t)127)
#define METHODN_isLogging               ((knh_methodn_t)127)
#define METHODN__isLogging              ((knh_methodn_t)127|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsLogging            ((knh_methodn_t)127|KNH_FLAG_MN_GETTER)
#define METHODN_setIsLogging            ((knh_methodn_t)127|KNH_FLAG_MN_SETTER)
#define FIELDN_isGenerated              ((knh_fieldn_t)128)
#define METHODN_isGenerated             ((knh_methodn_t)128)
#define METHODN__isGenerated            ((knh_methodn_t)128|KNH_FLAG_MN_MOVTEXT)
#define METHODN_getIsGenerated          ((knh_methodn_t)128|KNH_FLAG_MN_GETTER)
#define METHODN_setIsGenerated          ((knh_methodn_t)128|KNH_FLAG_MN_SETTER)

/* ======================================================================== */
/* [macros] */
#define knh_Array_setn(ctx,b,n,v) knh_Array_set__fast(ctx,b,n,v)
#define knh_Method_rtype(mtd)          knh_MethodField_rtype(knh_Method_mf(mtd))
#define knh_Method_psize(mtd)      knh_MethodField_psize(knh_Method_mf(mtd))
#define knh_Method_ptype(mtd,n)          knh_MethodField_ptype(knh_Method_mf(mtd),n)
#define knh_Method_pfields(mtd,n)   knh_MethodField_pfields(knh_Method_mf(mtd),n)
#define knh_Method_lastfield(mtd)   knh_MethodField_lastfield(knh_Method_mf(mtd))
#define Tuple                   Tuple1 
#define TupleNULL               Tuple1NULL
#define IS_STRUCT_Tuple(ctx,o)        (knh_Object_topsid(ctx,o) < STRUCT_Prototype)
#define IS_Tuple(o)             (knh_Object_cid(o) < CLASS_Prototype)
#define ISA_Tuple(ctx,o)        (knh_Object_cid(o) < CLASS_Prototype)
#define DEBUG_Tuple             DEBUG_Tuple1
#define knh_Tuple_size(b)  knh_Tuple_getSize(b)
#define knh_DictIdx_struct_copy   NULL
#define knh_DictIdx_struct_compare  NULL
#define knh_InputStream_struct_copy   NULL
#define knh_InputStream_struct_compare  NULL
#define knh_Array_size(a)     (a)->size
#define knh_Array_n(a,n)      (a)->list[(n)]
#define KNH_ARRAY_RESIZE(ctx, TYPE, array, oldsize, newsize) \
	if(newsize != 0 && newsize != oldsize) { \
		TYPE *newarray = (TYPE *)knh_malloc(ctx, KNH_SIZE(sizeof(TYPE) * newsize)); \
		if(newsize < oldsize) { \
			knh_memcpy(newarray, array, (sizeof(TYPE) * newsize)); \
		}else { \
			knh_memcpy(newarray, array, (sizeof(TYPE) * oldsize)); \
		} \
		knh_free(array, KNH_SIZE(sizeof(TYPE) * oldsize)); \
		array = newarray; \
		oldsize = newsize; \
	} \


#define knh_Array_append(ctx,b,n) knh_Array_add__fast(ctx,b,n)
#define knh_Socket_struct_copy   NULL
#define knh_Socket_struct_compare  NULL
#define INT_BUFSIZ 32
#define knh_Int_value(b)      (b)->value
#define knh_Int_struct_traverse NULL
#define new_Int(ctx, value) new_Int__checked(ctx, CLASS_Int, value)
#define knh_Regex_struct_copy  NULL
#define knh_Regex_struct_compare NULL
#define knh_tstruct_isNative(sid)   (sid < KONOHA_TSTRUCT_SIZE)
#define knh_ClassStruct_struct_copy    NULL
#define knh_ClassStruct_struct_compare NULL
#define knh_Class_getMethod(ctx, c, mn)    knh_Class_getMethod__(ctx, c, mn, 0)
#define knh_Class_findMethod(ctx, c, mn)   knh_Class_getMethod__(ctx, c, mn, 1)
#define knh_Float_value(o)    (o)->value
#define knh_Float_struct_traverse NULL
#define new_Float(ctx, value) new_Float__fast(ctx, CLASS_Float, value)
#define IS_TRUE(o)          (o != KNH_FALSE && IS_NOTNULL(o))
#define IS_FALSE(o)         (o == KNH_FALSE || IS_NULL(o))
#define new_Bool(ctx,b)     ((b == 0) ? KNH_FALSE : KNH_TRUE)
#define knh_Bool_struct_traverse NULL
#define knh_DictMap_put(ctx,b,k,v) knh_DictMap_set(ctx,b,k,v)
#define knh_DictMap_put(ctx,b,k,v) knh_DictMap_set(ctx,b,k,v)
#define knh_DictMap_String__   knh_DictMap_Iterator
#define LRUMap                          HashMap
#define knh_LRUMap                      knh_HashMap
#define new_LRUMap(ctx,n)               new_HashMap(ctx,n)
#define knh_LRUMap_get(ctx,b,kh,ko)     knh_HashMap_get(ctx,b,kh,ko)
#define knh_LRUMap_set(ctx,b,kh,ko,v)   knh_HashMap_set(ctx,b,kh,ko,v)
#define knh_HashMap_struct_compare NULL
#define knh_HashMap_put(ctx,b,h,k,v) knh_HashMap_set(ctx,b,h,k,v)
#define knh_HashSet_key_next knh_HashMap_key_next
#define knh_AffineConv_struct_copy      NULL
#define knh_AffineConv_struct_compare   NULL
#define knh_AffineConv_struct_traverse  NULL
#define KNH_FLAG_MMF_AFFINE (KNH_FLAG_MMF_SIGNIFICANT|KNH_FLAG_MMF_SYNONYM|KNH_FLAG_MMF_TOTAL|KNH_FLAG_MMF_STATIC)
#define knh_MapMap_struct_compare  NULL
#define knh_Prototype_struct_copy   NULL
#define knh_Prototype_struct_compare  NULL
#define IS_NULL(o)          (knh_Object_cid(o) == CLASS_Nue)
#define IS_NOTNULL(o)       (knh_Object_cid(o) != CLASS_Nue)
#define knh_Iterator_cid(it)          (((Iterator*)it)->cid)
#define knh_Iterator_source(it)       (((Iterator*)it)->source)
#define knh_Iterator_setsource(ctx, it, s)    KNH_SETv(ctx, (((Iterator*)it)->pos), s)
#define knh_Iterator_pos(it)          (((Iterator*)it)->pos)
#define knh_Iterator_setpos(it, size)  ((Iterator*)it)->pos = (size)
#define knh_Iterator_ref(it)          (((Iterator*)it)->ref)
#define knh_Iterator_setref(it, rr)       ((Iterator*)it)->ref = (rr)
#define knh_Iterator_struct_compare NULL
#define knh_HashSet_struct_compare NULL
#define knh_HashSet_put(ctx,b,h,k,v) knh_HashSet_set(ctx,b,h,k,v)
#define knh_OutputStream_struct_copy      NULL
#define knh_OutputStream_struct_compare   NULL
#define KNH_FLAG_PF_LINEFEED   KNH_FLAG_T0
#define NSN_main           0
#define FILEN_unknown      0
#define FIELDN(fn) knh_String_tochar(knh_tfieldn_name(fn))
#define METHODN(mn)  FIELDN(METHODN_TOFIELDN(mn))
#define NSN(nsn) knh_String_tochar(knh_tnsn_name(nsn))
#define FILEN(filen) knh_String_tochar(knh_tfilen_name(filen))
#define KNH_THROW(ctx, e) \
	if(IS_NULL(e)) { \
		knh_konohavm_throwException(ctx, new_Exception__Nue(ctx, (Nue*)e)); \
	}else if(IS_Exception(e)) { \
		knh_konohavm_throwException(ctx, (Exception*)e); \
	}else if(IS_String(e)) { \
		knh_konohavm_throwException(ctx, new_Exception(ctx, (String*)e)); \
	}else { \
		DEBUG("Cannot throw %s", CLASSN(knh_Object_cid(e))); \
	} \


#define KNH_THROWs(ctx, s) \
	knh_konohavm_throwException(ctx, new_Exception__b(ctx, B(s))); \


#define KNH_THROWf(ctx, fmt, ...) \
	char throwbuf_[256]; \
	snprintf(throwbuf_, sizeof(throwbuf_), fmt, ## __VA_ARGS__); \
	knh_konohavm_throwException(ctx, new_Exception__b(ctx, B(throwbuf_))); \


#define KNH_SETr(ctx,sf,v)          KNH_SETv(ctx,sf[-1],v)
#define KNH_SETr_void(ctx,sf)       KNH_SETv(ctx,sf[-1],KNH_NULL)
#define KNH_SAFE_SETr(ctx, sf, v)   KNH_SETv(ctx, sf[-1], v)
#define KNH_LOPEN(ctx, n) \
	Object **local_ = ((Context*)ctx)->ebp; \
	knh_stackf_locals(ctx, n) \


#define KNH_LOCALv(n)                 local_[n+1]
#define KNH_LVALUE(n)                 local_[n+1]
#define KNH_LSETv(ctx, n, v)          KNH_SETv(ctx, local_[n+1], v) 
#define KNH_LCLOSE(ctx)              ((Context*)ctx)->ebp = local_
#define KNH_LPUSH(ctx,v) \
	((Context*)ctx)->ebp++; \
	KNH_SETv(ctx, ((Context*)ctx)->ebp[0], v); \


#define KNH_PUSHv(ctx,v) \
	((Context*)ctx)->ebp++; \
	KNH_SETv(ctx, ((Context*)ctx)->ebp[0], v); \


#define KNH_STACKOP(p)        ((Context*)ctx)->stackop[(p)-((Context*)ctx)->stack]
#define STRUCT_newid         0
#define STRUCT_TUPLE(s)      (knh_struct_t)(sizeof(s)/sizeof(Object*))
#define STRUCTN(sid)   knh_tstruct_name(sid)
#define knh_sweep      knh_Object_refc_dec
#define IS_SWEEP(gc)   (gc == knh_sweep)
#define KNH_SAFEFREE(ctx,o)  knh_Object_safefree(ctx,o)
#define KNH_INITv(v, o) {\
		v = o; \
		DEBUG_ASSERT(v != NULL); \
		knh_Object_head(v)->refc++; \
	}\


#define KNH_INITn(a,n,v)          knh_INITn((a),(n),(v))
#define KNH_SETv_(ctx,a,v)         knh_SETv(ctx,&(a),(v))
#define KNH_SETv(ctx,v,o) {\
		Object *o_tmp = (Object *)o; \
		DEBUG_ASSERT(o_tmp != NULL); \
		knh_Object_head(o_tmp)->refc++; \
		knh_Object_refc_dec(ctx, v); \
		v = o_tmp; \
	}\


#define KNH_SETt(ctx,T,v,o) {\
		T *o_tmp = (T *)o; \
		DEBUG_ASSERT(o_tmp != NULL); \
		knh_Object_head(o_tmp)->refc++; \
		knh_Object_refc_dec(ctx, v); \
		v = (T *)o_tmp; \
	}\


#define KNH_SETv__ngc_(ctx,a,v)    knh_SETv__ngc(ctx,&((Object*)a),(v))
#define KNH_SETv__ngc(ctx,v,o) {\
		Object *o_tmp = (Object*)o; \
		knh_Object_head(o_tmp)->refc++; \
		knh_Object_head(v)->refc--; \
		v = o_tmp; \
	} \


#define KNH_SETt__ngc(ctx, T, v,o) {\
		T *o_tmp = (T *)o; \
		knh_Object_head(o_tmp)->refc++; \
		knh_Object_head(v)->refc--; \
		v = (T *)o_tmp; \
	} \


#define KNH_SETn_(ctx,a,n,v)       knh_SETn(ctx,a,(n),(v))
#define KNH_FINALv_(ctx,a) knh_FINALv(ctx,(Object**)&(a))
#define KNH_FINALv(ctx, v) {\
		knh_Object_refc_dec(ctx, v); \
		v = NULL; \
	}\


#define KNH_FINALn(ctx,a,n)       knh_FINALn(ctx,(a),(n))
#define EXPTN(eid)   knh_String_tochar(knh_texpt_name(eid))
#define KNH_TGLOBAL(v)   knh_tglobal_insert(&(v))
#define KNH_FLAG_CF2OF(f)        (f)
#define CLASSN(cid)   knh_String_tochar(knh_tclass_name(cid))
#define CLASSNo(o)    CLASSN(knh_Object_cid(o))
#define knh_Vocabulary_struct_copy   NULL
#define knh_Vocabulary_struct_compare  NULL
#define knh_Vocabulary_fval__default knh_Vocabulary_newString
#define KNH_STDIN          (((Context*)ctx)->in)
#define KNH_STDOUT         (((Context*)ctx)->out)
#define KNH_STDERR         (((Context*)ctx)->err)
#define IntCache(ctx)      ((Context*)ctx)->cacheIntLRUMap
#define FloatCache(ctx)    ((Context*)ctx)->cacheFloatLRUMap
#define StringCache(ctx)   ((Context*)ctx)->cacheStringLRUMap
#define knh_Context_struct_copy   NULL
#define knh_Context_struct_compare  NULL
#define FIELDN_NONAME    ((knh_fieldn_t)-1)
#define FIELDN_NEWID     ((knh_fieldn_t)-2)
#define FIELDN_return    FIELDN_
#define METHODN_NONAME   ((knh_methodn_t)-1)
#define METHODN_NEWID    ((knh_methodn_t)-2)
#define KNH_FLAG_FN_SUPER   KNH_FLAG_T0
#define KNH_FLAG_FN_U1      KNH_FLAG_T1
#define KNH_FLAG_FN_U2      KNH_FLAG_T2
#define FIELDN_IS_SUPER(fnq)       ((fnq & KNH_FLAG_FN_SUPER) == KNH_FLAG_FN_SUPER)
#define FIELDN_IS_U1(fnq)          ((fnq & KNH_FLAG_FN_U1) == KNH_FLAG_FN_U1)
#define FIELDN_IS_U2(fnq)          ((fnq & KNH_FLAG_FN_U2) == KNH_FLAG_FN_U2)
#define FIELDN_IS_PROTECTED(fnq)   (FIELDN_IS_U1(fnq)||FIELDN_IS_U2(fnq))
#define FIELDN_UNMASK(fnq)         (fnq & (~(KNH_FLAG_FN_SUPER|KNH_FLAG_FN_U1|KNH_FLAG_FN_U2)))
#define KNH_FLAG_MN_SUPER        KNH_FLAG_T0
#define KNH_FLAG_MN_GETTER       KNH_FLAG_T1
#define KNH_FLAG_MN_SETTER       KNH_FLAG_T2
#define KNH_FLAG_MN_MOVTEXT      (KNH_FLAG_T1|KNH_FLAG_T2)
#define KNH_FLAG_MN_FIELDN       (~(KNH_FLAG_T0|KNH_FLAG_T1|KNH_FLAG_T2))
#define METHODN_IS_GETTER(mn)   ((mn & KNH_FLAG_MN_MOVTEXT) == KNH_FLAG_MN_GETTER)
#define METHODN_TO_GETTER(mn)   (mn | KNH_FLAG_MN_GETTER)
#define METHODN_IS_SETTER(mn)   ((mn & KNH_FLAG_MN_MOVTEXT) == KNH_FLAG_MN_SETTER)
#define METHODN_TO_SETTER(mn)   (mn | KNH_FLAG_MN_SETTER)
#define METHODN_IS_MOVTEXT(mn)  ((mn & KNH_FLAG_MN_MOVTEXT) == KNH_FLAG_MN_MOVTEXT)
#define METHODN_TO_MOVTEXT(mn)  (mn | KNH_FLAG_MN_MOVTEXT)
#define METHODN_TOFIELDN(mn)     (mn & KNH_FLAG_MN_FIELDN)
#define knh_Method_mn(mtd)    (mtd)->mn
#define knh_Method_mf(mtd)    (mtd)->mf
#define KNH_FLAG_TF_NULLABLE        KNH_FLAG_T0
#define KNH_FLAG_TF_PLURAL          KNH_FLAG_T1
#define CLASS_TONULLABLE(c)        (c|KNH_FLAG_TF_NULLABLE)
#define CLASS_TOPLURAL(c)          (c|KNH_FLAG_TF_PLURAL)
#define TYPE_ISBASE(t)             (t < KONOHA_TCLASS_SIZE)    /* new_Class_type.c */
#define TYPE_ISNULLABLE(t)         ((t & KNH_FLAG_TF_NULLABLE)==KNH_FLAG_TF_NULLABLE)
#define TYPE_ISNOTNULL(t)          ((t & KNH_FLAG_TF_NULLABLE)==0)
#define TYPE_ISPLURAL(t)           ((t & KNH_FLAG_TF_PLURAL)==KNH_FLAG_TF_PLURAL)
#define KNH_TYPE_MASK               (KNH_FLAG_TF_NULLABLE|KNH_FLAG_TF_PLURAL)
#define KNH_CLASS_MASK              (~(KNH_TYPE_MASK))
#define TYPE_UNMASK(t)              (t & KNH_CLASS_MASK)
#define TYPE_UNMASK_NULL(t)         (t&(~KNH_FLAG_TF_NULLABLE))
#define TYPE_TONOTNULL(t)           (t&(~KNH_FLAG_TF_NULLABLE))
#define TYPE_COPY(t,t2)             ((t & KNH_TYPE_MASK) | t2) 
#define TYPEQN(t)                TYPEN(t), TYPEQ(t)
#define CLASSQN(t)               CLASSN(TYPE_UNMASK(t)), knh_CLASSQ(t)
#define TYPE_Any                 CLASS_TONULLABLE(CLASS_any)
#define TYPE_any                 CLASS_TONULLABLE(CLASS_any)
#define TYPE_any__               CLASS_Iterator
#define TYPE_any__               CLASS_Iterator
#define TYPE_void                CLASS_TONULLABLE(CLASS_Object)
#define TYPE_Object              CLASS_TONULLABLE(CLASS_Object)
#define TYPE_Object__            CLASS_Iterator
#define TYPE_Tuple               CLASS_TONULLABLE(CLASS_Tuple)
#define TYPE_Tuple__             CLASS_TOPLURAL(CLASS_Tuple)
#define TYPEN(type)  knh_TYPEN(ctx,type)
#define knh_IntUnit_struct_copy    NULL
#define knh_IntUnit_struct_compare NULL
#define knh_ResultSet_struct_copy NULL
#define knh_ResultSet_struct_compare NULL
#define knh_Bytes_size(o)      (o)->size
#define knh_Bytes_value(o)     (o)->value
#define knh_Bytes_tochar(b)  (char*)knh_Bytes_value(b)
#define knh_BytesConv_struct_copy NULL
#define knh_BytesConv_struct_compare NULL
#define knh_write_delim(ctx, w)    knh_write(ctx, w, STEXT(", "))
#define knh_write_dots(ctx, w)     knh_write(ctx, w, STEXT("..."))
#define knh_write__i(ctx, w, n)   knh_write__ifmt(ctx, w, KNH_INT_FMT, n)
#define knh_write__u(ctx, w, n)   knh_write__ifmt(ctx, w, KNH_UINT_FMT, n)
#define knh_write__x(ctx, w, n)   knh_write__ifmt(ctx, w, KNH_INT_FMTX, n)
#define knh_write__f(ctx, w, f)  knh_write__ffmt(ctx, w, KNH_FLOAT_FMT, f)
#define knh_write__e(ctx, w, f)  knh_write__ffmt(ctx, w, KNH_FLOAT_FMTE, f)
#define knh_write__expt(ctx, w, eid)    knh_write__s(ctx, w, EXPTN(eid))
#define knh_write__fn(ctx, w, fn)   knh_write__s(ctx, w, FIELDN(fn))
#define knh_write__O(ctx, w, o)    knh_format(ctx, w, METHODN__s, o, KNH_NULL)
#define knh_Object_toString(ctx, b)   knh_Object_movableText(ctx, b, METHODN__s, KNH_NULL)
#define EXPT_newid            ((knh_expt_t)0)
#define EXPT_Exception        ((knh_expt_t)1)
#define EXPT_NoSuchException  ((knh_expt_t)2)
#define knh_Exception_eid(o)   (o)->eid
#define knh_Exception_struct_copy   NULL
#define knh_Exception_struct_compare  NULL
#define IS_Number(o)  (STRUCT_Nue <= knh_Object_topsid(o) && knh_Object_topsid(o) <= STRUCT_String)
#define IS_CLASS_Number(cid) (CLASS_Int <= cid && cid < CLASS_String)
#define CLASS_ISNUMBER(c)    (STRUCT_Int <= knh_tclass_topsid(c) && knh_tclass_topsid(c) < STRUCT_String)
#define knh_Object_cid(o)           (knh_class_t)(knh_Object_head(o)->cid)
#define knh_Object_topsid(o)        knh_tclass_topsid(knh_Object_cid(o))
#define knh_Object_offset(o)        knh_tclass_offset(knh_Object_cid(o))
#define knh_Connection_struct_copy    NULL
#define knh_Connection_struct_compare  NULL
#define KNH_MUTEX_RECURSIVE    0
#define KNH_MUTEX_FAST         1
#define knh_Mutex_struct_copy  NULL
#define knh_Mutex_struct_compare   NULL
#define knh_FloatUnit_struct_copy    NULL
#define knh_FloatUnit_struct_compare NULL
#define knh_DictSet_put(ctx,b,k,v) knh_DictSet_set(ctx,b,k,v)
#define knh_Runtime_struct_copy  NULL
#define knh_Runtime_struct_compare NULL
#define CLASS_Object         ((knh_class_t)0)
#define CLASS_newid          ((knh_class_t)-1)
#define CLASS_unknown        ((knh_class_t)-2)
#define CLASS_any            CLASS_Prototype
#define CLASS_any__          CLASS_TOPLURAL(CLASS_Prototype)
#define CLASS_Any            CLASS_Prototype
#define knh_Class_type(c)     (c)->type
#define knh_Class_class(c)    TYPE_TONOTNULL((c)->type)
#define knh_Class_bcid(c)     (c)->bcid
#define knh_Class_struct_copy   NULL
#define knh_Class_struct_traverse   NULL
#define IS_SPEC(o)                (CLASS_IntUnit <= knh_Object_cid(o)  && knh_Object_cid(o) <= CLASS_Vocabulary)
#define KNH_SIZE(v)         knh_size(v)
#define B(c)     new_bytes(c)
#define B2(c,n)   new_bytes__2(c,n)
#define STEXT(c)  new_bytes__2(c,sizeof(c)-1)
#define TEXT(c)   new_bytes__2(c,sizeof(c)-1)
#define ISB(t,c) (t.len == (sizeof(c)-1) && knh_strncmp((char*)t.buf,c,t.len) == 0)
#define knh_Int64_struct_traverse NULL
#define new_Int64(ctx, value) new_Int64__fast(ctx, CLASS_Int64, value)
#define new_String(ctx,t)              new_String__fast(ctx,CLASS_String,B(t))
#define new_String__STEXT(ctx,cid,s)   new_String__fast(ctx, cid, STEXT(s))
#define knh_String_value(o)   (o)->value
#define knh_String_struct_copy  NULL
#define knh_bytes_hcode(t)     knh_string_hash((t).buf, (t).len)
#define knh_ClassRel_struct_copy    NULL
#define knh_ClassRel_struct_compare  NULL
#define KNH_SETJUMP(hdlr)   setjmp(((ExceptionHandler*)hdlr)->jmpbuf)
#define knh_ExceptionHandler_struct_copy   NULL
#define knh_ExceptionHandler_struct_compare  NULL
#define knh_Amazon_struct_copy      NULL
#define knh_Amazon_struct_compare   NULL
#define knh_Amazon_struct_traverse  NULL
#define knh_Counter_struct_compare  NULL
#define knh_Stmt_struct_copy  NULL
#define knh_Stmt_struct_compare  NULL
#define knh_Token_isFirstExpr(tk)    (knh_token_isInExpr(tk->tt) && !knh_token_isNotFirst(tk->tt))
#define knh_VirtualMachineCode_struct_compare  NULL
#define SPF_BACKQUOTED  KNH_FLAG07
#define knh_Cmpl_struct_copy   NULL
#define knh_Cmpl_struct_compare  NULL
#define knh_stmtvisit_asm__op           knh_stmtvisit_asm__call
#define knh_stmtvisit_asm__new          knh_stmtvisit_asm__call
#define knh_stmtvisit_asm__map          knh_stmtvisit_asm__call
#define knh_stmtvisit_asm__movtext      knh_stmtvisit_asm__call
#define knh_stmtvisit_asm__alt          knh_stmtvisit_asm__call
#define knh_stmtvisit_asm__and          knh_stmtvisit_asm__call
#define knh_stmtvisit_asm__or           knh_stmtvisit_asm__call
#define knh_stmtvisit_asm__trinary      knh_stmtvisit_asm__call
#define knh_stmtvisit_asm__next         knh_stmtvisit_asm__call
#define knh_Cmpl_indexOfGlobalVariable(mc, fnq)       knh_Class_queryField(knh_Object_cid(mc->nsproto), fnq)
#define knh_Cmpl_indexOfFieldVariable(mc, fnq)        knh_Class_queryField(mc->this_cid, fnq)
#define knh_stmtvisit_declm__namespace  knh_stmtvisit_declc__namespace
#define knh_stmtvisit_declv__namespace  knh_stmtvisit_declc__namespace
#define knh_stmtvisit_asm__namespace    knh_stmtvisit_declc__namespace
#define knh_Token_struct_copy  NULL
#define knh_Token_struct_compare  NULL
#define new_asmv__EBP(n,type)     new_asmv(KNH_ASMV_EBP, n, type, NULL)
#define new_asmv__SFP(n,type)     new_asmv(KNH_ASMV_SFP, n, type, NULL)
#define new_asmv__OFP(n,type)     new_asmv(KNH_ASMV_OFP, n, type, NULL)
#define new_asmv__OIDX(o,n,type)  new_asmv(KNH_ASMV_OIDX, n, type, o)
#define new_asmv__ONSTACK(type)   new_asmv(KNH_ASMV_ONSTACK, 0, type, NULL)

#ifdef __cplusplus
}
#endif

/* ======================================================================== */

#endif/*KONOHA_NAME__H*/
