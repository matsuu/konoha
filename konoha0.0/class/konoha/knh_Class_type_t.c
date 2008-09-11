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

/* NN = NONNULL*/

#define _KNH_FLAG_TF_NN                KNH_FLAG_T0
#define _TYPE_ISNULLABLE(t)            ((t & KNH_FLAG_TF_NN)==0)   
#define _TYPE_ISNOTNULL(t)             ((t & KNH_FLAG_TF_NN)==KNH_FLAG_TF_NN)
#define _CLASS_TONNTYPE(c)             (c|KNH_FLAG_TF_NN)
#define _TYPE_TONNTYPE(t)              (t|KNH_FLAG_TF_NN)

#define _TYPE_UNMASK(t)                (t&(~(KNH_FLAG_TF_NN|KNH_FLAG_T1)))
#define _TYPE_UNMASK_NN(t)             (t&(~KNH_FLAG_TF_NN))

#define _TYPEQN(t)                     TYPEN(t), TYPEQ(t)

#define _TYPE_void                     CLASS_TONNTYPE(CLASS_Nue)
#define _NNTYPE_void                   CLASS_TONNTYPE(CLASS_Nue)

#define _TYPE_any                      CLASS_Any
#define _NNTYPE_any                    CLASS_any

//#define _KNH_FLAG_TF_PMZ               KNH_FLAG_T1
//#define _TYPE_ISPMZ(t)                 ((t & KNH_FLAG_TF_PMZ)==KNH_FLAG_TF_PMZ)   
//#define _CLASS_PMZ(t)                  (t) /*((t | KNH_FLAG_TF_PMZ))*/
//#define _TYPE_PMZ(t)                   ((t | KNH_FLAG_TF_PMZ))   
//#define _TYPE_UNMASK_PMZ(t)            (t&(~KNH_FLAG_TF_PMZ))

/* ------------------------------------------------------------------------ */

knh_class_t
knh_pmztype_toclass(Ctx *ctx, knh_type_t t, knh_class_t this_cid)
{
	knh_class_t cid = TYPE_UNMASK_NN(t);
	DEBUG_ASSERT_cid(this_cid);
	if(cid == CLASS_This) {
		return this_cid;
	}
	else if(cid == CLASS_Any1) {
		return knh_tClass[this_cid].p1;
	}
	else if(cid == CLASS_Any2) {
		return knh_tClass[this_cid].p2;
	}
	else if(knh_tClass_isPMZ(cid)) { /* Iterator<This> */
		knh_class_t p1 = knh_pmztype_toclass(ctx, knh_tClass[cid].p1, this_cid);
		knh_class_t p2 = knh_pmztype_toclass(ctx, knh_tClass[cid].p2, this_cid);
		return knh_pmzclass(ctx, knh_tClass[cid].bcid, p1, p2);
	}
	return cid;
}

/* ------------------------------------------------------------------------ */

knh_type_t
knh_pmztype_totype(Ctx *ctx, knh_type_t t, knh_class_t this_cid)
{
	knh_class_t cid = TYPE_UNMASK_NN(t), mask = (t & KNH_FLAG_TF_NN);
	DEBUG_ASSERT_cid(this_cid);
	if(cid == CLASS_This) {
		return this_cid | mask;
	}
	else if(cid == CLASS_Any1) {
		return knh_tClass[this_cid].p1 | mask;
	}
	else if(cid == CLASS_Any2) {
		return knh_tClass[this_cid].p2 | mask;
	}
	else if(knh_tClass_isPMZ(cid)) { /* Iterator<This> */
		knh_class_t p1 = knh_pmztype_toclass(ctx, knh_tClass[cid].p1, this_cid);
		knh_class_t p2 = knh_pmztype_toclass(ctx, knh_tClass[cid].p2, this_cid);
		return knh_pmzclass(ctx, knh_tClass[cid].bcid, p1, p2) | mask;
	}
	return t;
}


/* ------------------------------------------------------------------------ */

knh_class_t knh_class_Array(Ctx *ctx, knh_class_t p1)
{
	char buf[CLASSNAME_BUFSIZ];
	if(p1 == CLASS_Any) return CLASS_Array;
	knh_snprintf(buf, sizeof(buf), "%s[]", CLASSN(p1));
	knh_class_t cid = knh_NameSpace_getClass(ctx, knh_rootNameSpace, B(buf));
	if(cid == CLASS_unknown) {
		DBG2_P("Generating %s", buf);
		return KNH_TPMZCLASS(ctx, CLASS_newid, new_String0(ctx, B(buf), NULL), CLASS_Array, p1, CLASS_Nue);
	}
	return cid;
}

/* ------------------------------------------------------------------------ */

knh_class_t knh_class_Iterator(Ctx *ctx, knh_class_t p1)
{
	char buf[CLASSNAME_BUFSIZ];
	if(p1 == CLASS_Any) return CLASS_Iterator;
	knh_snprintf(buf, sizeof(buf), "%s..", CLASSN(p1));
	knh_class_t cid = knh_NameSpace_getClass(ctx, knh_rootNameSpace, B(buf));
	if(cid == CLASS_unknown) {
		DBG2_P("*** Generating %s ***", buf);
		return KNH_TPMZCLASS(ctx, CLASS_newid, new_String0(ctx, B(buf), NULL), CLASS_Iterator, p1, CLASS_Nue);
	}
	return cid;
}

/* ------------------------------------------------------------------------ */

knh_class_t knh_pmzclass(Ctx *ctx, knh_class_t bcid, knh_class_t p1, knh_class_t p2)
{
	char buf[CLASSNAME_BUFSIZ];
	if(bcid == CLASS_Iterator) {
		return knh_class_Iterator(ctx, p1);
	}
	else if(bcid == CLASS_Array){
		return knh_class_Array(ctx, p1);
	}
	else {
		knh_snprintf(buf, sizeof(buf), "%s<%s,%s>", CLASSN(bcid), CLASSN(p1), CLASSN(p2));
	}
	{
		knh_class_t cid = knh_NameSpace_getClass(ctx, knh_rootNameSpace, B(buf));
		if(cid == CLASS_unknown) {
			//DBG2_P("Generating %s", buf);
			return KNH_TPMZCLASS(ctx, CLASS_newid, new_String0(ctx, B(buf), NULL), bcid, p1, p2);
		}
		return cid;
	}
}


///* ------------------------------------------------------------------------ */
///* [byte] */
//
//knh_bool_t knh_bytes_isPluralType(knh_bytes_t t)
//{
//	if(t.len > 2 && t.buf[t.len-1] == '.' && t.buf[t.len-2] == '.') {
//		return 1;
//	}
//	return 0;
//}
//
/* ------------------------------------------------------------------------ */

knh_bool_t knh_bytes_isNotNullType(knh_bytes_t t)
{
	if(t.len > 2 && t.buf[t.len-1] == '!' && t.buf[t.len-2] != '!') {
		return 1;
	}
	return 0;
}
//
///* ------------------------------------------------------------------------ */
//
//knh_int_t knh_type_compare(Ctx *ctx, knh_type_t t1, knh_type_t t2)
//{
////	knh_class_t cid = knh_type_tocid(t1), cid2 = knh_type_tocid(t2);
////	knh_int_t res = knh_strcmp(CLASSN(cid), CLASSN(cid2));
////	if(res != 0) return res;
//	return (knh_int_t)t1 - (knh_int_t)t2;
//}

/* ======================================================================== */
/* [movabletext] */

char *TYPEQ(knh_type_t type)
{
	if(TYPE_ISNOTNULL(type)) {
		return "!";
	}
	return "";
}

/* ------------------------------------------------------------------------ */

#define _TYPEN(type)  knh_TYPEN(ctx,type)

char *knh_TYPEN(Ctx *ctx, knh_type_t type)
{
	if(type == TYPE_void) return "void";
	knh_class_t cid = TYPE_UNMASK_NN(type);
	return CLASSN(cid);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
