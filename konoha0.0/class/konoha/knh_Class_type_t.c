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

/* ************************************************************************ */

#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */
/* [macros] */

#define _KNH_FLAG_TF_NULLABLE        KNH_FLAG_T0
#define _KNH_FLAG_TF_PLURAL          KNH_FLAG_T1

#define _CLASS_TONULLABLE(c)        (c|KNH_FLAG_TF_NULLABLE)
#define _CLASS_TOPLURAL(c)          (c|KNH_FLAG_TF_PLURAL)

#define _TYPE_ISBASE(t)             (t < KONOHA_TCLASS_SIZE)    /* new_Class_type.c */
#define _TYPE_ISNULLABLE(t)         ((t & KNH_FLAG_TF_NULLABLE)==KNH_FLAG_TF_NULLABLE)
#define _TYPE_ISNOTNULL(t)          ((t & KNH_FLAG_TF_NULLABLE)==0)
#define _TYPE_ISPLURAL(t)           ((t & KNH_FLAG_TF_PLURAL)==KNH_FLAG_TF_PLURAL)

#define _KNH_TYPE_MASK               (KNH_FLAG_TF_NULLABLE|KNH_FLAG_TF_PLURAL)
#define _KNH_CLASS_MASK              (~(KNH_TYPE_MASK))

#define _TYPE_UNMASK(t)              (t & KNH_CLASS_MASK)
#define _TYPE_UNMASK_NULL(t)         (t&(~KNH_FLAG_TF_NULLABLE))
#define _TYPE_TONOTNULL(t)           (t&(~KNH_FLAG_TF_NULLABLE))
#define _TYPE_COPY(t,t2)             ((t & KNH_TYPE_MASK) | t2) 

/* ------------------------------------------------------------------------ */

#define _TYPEQN(t)                TYPEN(t), TYPEQ(t)
#define _CLASSQN(t)               CLASSN(TYPE_UNMASK(t)), knh_CLASSQ(t)

/* ------------------------------------------------------------------------ */

#define _TYPE_Any                 CLASS_TONULLABLE(CLASS_any)
#define _TYPE_any                 CLASS_TONULLABLE(CLASS_any)
#define _TYPE_any__               CLASS_Iterator
#define _TYPE_any__               CLASS_Iterator

#define _TYPE_void                CLASS_TONULLABLE(CLASS_Object)
#define _TYPE_Object              CLASS_TONULLABLE(CLASS_Object)
#define _TYPE_Object__            CLASS_Iterator

#define _TYPE_Tuple               CLASS_TONULLABLE(CLASS_Tuple)
#define _TYPE_Tuple__             CLASS_TOPLURAL(CLASS_Tuple)


/* ------------------------------------------------------------------------ */

knh_class_t knh_type_toclass(knh_type_t t)
{
	if(TYPE_ISPLURAL(t)) {
		return CLASS_Iterator;
	}
	return TYPE_UNMASK(t);
}

/* ------------------------------------------------------------------------ */
/* [byte] */

INLINE
knh_bool_t knh_bytes_isPluralType(knh_bytes_t t)
{
	if(t.len > 2 && t.buf[t.len-1] == '.' && t.buf[t.len-2] == '.') {
		return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_bytes_isNotNullType(knh_bytes_t t)
{
	if(t.len > 2 && t.buf[t.len-1] == '!' && t.buf[t.len-2] != '!') {
		return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_type_compare(Ctx *ctx, knh_type_t t1, knh_type_t t2)
{
//	knh_class_t cid = knh_type_tocid(t1), cid2 = knh_type_tocid(t2);
//	knh_int_t res = knh_strcmp(CLASSN(cid), CLASSN(cid2));
//	if(res != 0) return res;
	return (knh_int_t)t1 - (knh_int_t)t2;
}

/* ======================================================================== */
/* [movabletext] */

char *TYPEQ(knh_type_t type)
{
	if(TYPE_ISPLURAL(type)) {
		return "..";
	}else if(TYPE_ISNOTNULL(type)) {
		return "!";
	}
	return "";
}

/* ------------------------------------------------------------------------ */

#define _TYPEN(type)  knh_TYPEN(ctx,type)

char *knh_TYPEN(Ctx *ctx, knh_type_t type)
{
	if(type == TYPE_void) return "void";	
	knh_class_t cid = TYPE_UNMASK(type);
	if(cid == CLASS_any) return "any";
	return CLASSN(cid);
}

/* ------------------------------------------------------------------------ */

char *knh_CLASSQ(knh_type_t type)
{
	if(TYPE_ISPLURAL(type)) {
		return "..";
	}
	return "";
}

#ifdef __cplusplus
}
#endif
