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

///* ======================================================================== */
///* [func] */
//
//#define _IS_Number(o)  (STRUCT_Nue <= knh_Object_topsid(o) && knh_Object_topsid(o) <= STRUCT_String)
//#define _IS_CLASS_Number(cid) (CLASS_Int <= cid && cid < CLASS_String)
//#define _CLASS_ISNUMBER(c)    (STRUCT_Int <= knh_tclass_topsid(c) && knh_tclass_topsid(c) < STRUCT_String)
//
//typedef knh_int_t   (*f_toint)(Number *v);
//typedef knh_float_t (*f_tofloat)(Number *v);
//typedef knh_int64_t  (*f_toint64)(Number *v);
//
//typedef Number* (*f_newnum__i)(Ctx *, knh_class_t, knh_int_t);
//typedef Number* (*f_newnum__f)(Ctx *, knh_class_t, knh_float_t);
//typedef Number* (*f_newnum__l)(Ctx *, knh_class_t, knh_int64_t);
//typedef Number* (*f_newnum__b)(Ctx *, knh_class_t, knh_bytes_t);
//
///* ------------------------------------------------------------------------ */
//
//Number *new_Number__RAW(Ctx *ctx, knh_class_t cid, knh_bytes_t t)
//{
//	knh_class_t bcid = knh_tclass_bcid(cid);
//	if(bcid == CLASS_Int && t.len == sizeof(knh_int_t)) {
//		return new_IntX(ctx, cid, *((knh_int_t*)t.buf));
//	}
//	if(bcid == CLASS_Float && t.len == sizeof(knh_float_t)) {
//		return new_FloatX(ctx, cid, *((knh_float_t*)t.buf));
//	}
//	if(bcid == CLASS_Int64 && t.len == sizeof(knh_int64_t)) {
//		return new_Int64X(ctx, cid, *((knh_int64_t*)t.buf));
//	}
//	if(t.len != 0) {
//		DBG2_P("cid=%s, len=%d", CLASSN(cid), (int)t.len);
//	}
//	return KNH_NULL;
//}
//
//static f_newnum__i tglobal_newnum__i[] = {
//	new_Int__i,
//	new_Int64__i,
//	new_Float__i,
//#ifdef CLASS_Decimal
//	new_Decimal__i,
//#endif
//};
//
//static f_newnum__f tglobal_newnum__f[] = {
//	new_Int__f,
//	new_Int64__f,
//	new_Float__f,
//#ifdef CLASS_Decimal
//	new_Decimal__f,
//#endif
//};
//
//static f_newnum__l tglobal_newnum__l[] = {
//	new_Int__l,
//	new_Int64__l,
//	new_Float__l,
//#ifdef CLASS_Decimal
//	new_Decimal__l,
//#endif
//};
//
//static f_newnum__b tglobal_newnum__b[] = {
//	new_Int__b,
//	new_Int64__b,
//	new_Float__b,
//#ifdef CLASS_Decimal
//	new_Decimal__b,
//#endif
//};
//
///* ------------------------------------------------------------------------ */
///* [toint] */
//
//knh_int_t knh_Nue_toint(Number *b)
//{
//	return 0;
//}
//
///* ------------------------------------------------------------------------ */
//
//knh_int_t knh_Boolean_toint(Number *b)
//{
//	return IS_TRUE(b) ? 1 : 0;
//}
//
///* ------------------------------------------------------------------------ */
//
//knh_int_t knh_String_toint(Number *b)
//{
//	return (knh_int_t)knh_bytes_toint(knh_String_tobytes(b));
//}
//
//
//static f_toint tglobal_toint[] = {
//	knh_Nue_toint,
//	knh_Boolean_toint,
//	knh_Int_toint,
//	knh_Int64_toint,
//	knh_Float_toint,
//#ifdef CLASS_Decimal
//	knh_Decimal_toint,
//#endif
//	knh_String_toint,
//};
//
///* ------------------------------------------------------------------------ */
///* [tofloat] */
//
//knh_float_t knh_Nue_tofloat(Number *b)
//{
//	return 0.0;
//}
//
///* ------------------------------------------------------------------------ */
//
//knh_float_t knh_Boolean_tofloat(Number *b)
//{
//	return IS_TRUE(b) ? 1.0 : 0.0;
//}
//
///* ------------------------------------------------------------------------ */
//
//knh_float_t knh_String_tofloat(Number *b)
//{
//	return knh_bytes_tofloat(knh_String_tobytes(b));
//}
//
//static f_tofloat tglobal_tofloat[] = {
//	knh_Nue_tofloat,
//	knh_Boolean_tofloat,
//	knh_Int_tofloat,
//	knh_Int64_tofloat,
//	knh_Float_tofloat,
//#ifdef CLASS_Decimal
//	knh_Decimal_tofloat,
//#endif
//	knh_String_tofloat,
//};
//
///* ------------------------------------------------------------------------ */
///* [toint64] */
//
//knh_int64_t knh_Nue_toint64(Number *b)
//{
//	return 0L;
//}
//
///* ------------------------------------------------------------------------ */
//
//knh_int64_t knh_Boolean_toint64(Number *b)
//{
//	return IS_TRUE(b) ? 1L : 0L;
//}
//
///* ------------------------------------------------------------------------ */
//
//knh_int64_t knh_String_toint64(Number *b)
//{
//	return knh_bytes_toint64(knh_String_tobytes(b));
//}
//
//
//static f_toint64 tglobal_toint64[] = {
//	knh_Nue_toint64,
//	knh_Boolean_toint64,
//	knh_Int_toint64,
//	knh_Int64_toint64,
//	knh_Float_toint64,
//#ifdef CLASS_Dicimal
//	knh_Decimal_toint64,
//#endif
//	knh_String_toint64,
//};
//
///* ======================================================================== */
///* [constructors] */
//
//Number *new_Number__i(Ctx *ctx, knh_class_t cid, knh_int_t n)
//{
//	knh_class_t bcid = knh_tclass_bcid(cid);
//	KNH_ASSERT(IS_CLASS_Number(bcid));
//	return tglobal_newnum__i[bcid - CLASS_Int](ctx, cid, n);
//}
//
///* ------------------------------------------------------------------------ */
//
//Number *new_Number__f(Ctx *ctx, knh_class_t cid, knh_float_t n)
//{
//	knh_class_t bcid = knh_tclass_bcid(cid);
//	KNH_ASSERT(IS_CLASS_Number(bcid));
//	return tglobal_newnum__f[bcid - CLASS_Int](ctx, cid, n);
//}
//
///* ------------------------------------------------------------------------ */
//
//Number *new_Number__l(Ctx *ctx, knh_class_t cid, knh_int64_t n)
//{
//	knh_class_t bcid = knh_tclass_bcid(cid);
//	KNH_ASSERT(IS_CLASS_Number(bcid));
//	return tglobal_newnum__l[bcid - CLASS_Int](ctx, cid, n);
//}
//
///* ------------------------------------------------------------------------ */
//
//Number *new_Number__b(Ctx *ctx, knh_class_t cid, knh_bytes_t t)
//{
//	knh_class_t bcid = knh_tclass_bcid(cid);
//	KNH_ASSERT(IS_CLASS_Number(bcid));
//	return tglobal_newnum__b[bcid - CLASS_Int](ctx, cid, t);
//}

/* ======================================================================== */
/* [conv] */

knh_int_t knh_Number_toint(Any *o)
{
	Object *n = (Object*)o;
	switch(n->h.bcid) {
		case CLASS_Nue :
			return 0;
		case CLASS_Boolean :
			return (IS_TRUE(n)) ? 1 : 0;
		case CLASS_Int :
			return ((Int*)n)->value;
		case CLASS_Int64 :
			return (knh_int_t)((Int64*)n)->value;
		case CLASS_Float :
			return (knh_int_t)((Float*)n)->value;
	}
	KNH_ASSERT(n->h.bcid == CLASS_Int); /* STOP */
	return 0;
}

/* ------------------------------------------------------------------------ */

knh_int64_t knh_Number_toint64(Any *o)
{
	Object *n = (Object*)o;
	switch(n->h.bcid) {
		case CLASS_Nue :
			return 0;
		case CLASS_Boolean :
			return (IS_TRUE(n)) ? 1 : 0;
		case CLASS_Int :
			return (knh_int64_t)((Int*)n)->value;
		case CLASS_Int64 :
			return (knh_int64_t)((Int64*)n)->value;
		case CLASS_Float :
			return (knh_int64_t)((Float*)n)->value;
	}
	KNH_ASSERT(n->h.bcid == CLASS_Int); /* STOP */
	return 0;
}

/* ------------------------------------------------------------------------ */

knh_float_t knh_Number_tofloat(Any *o)
{
	Object *n = (Object*)o;
	switch(n->h.bcid) {
		case CLASS_Nue :
			return 0.0;
		case CLASS_Boolean :
			return (IS_TRUE(n)) ? 1.0 : 0.0;
		case CLASS_Int :
			return (knh_float_t)((Int*)n)->value;
		case CLASS_Int64 :
			return (knh_float_t)((Int64*)n)->value;
		case CLASS_Float :
			return (knh_float_t)((Float*)n)->value;
	}
	KNH_ASSERT(n->h.bcid == CLASS_Int); /* STOP */
	return (knh_float_t)0.0;
}

/* ======================================================================== */
/* [Int] */

knh_int_t knh_Int_toint(Int *o)
{
	KNH_ASSERT(IS_bInt(o));
	return (knh_int_t)o->value;
}

/* ------------------------------------------------------------------------ */

knh_float_t knh_Int_tofloat(Int *o)
{
	KNH_ASSERT(IS_bInt(o));
	return (knh_float_t)(o->value);
}

/* ------------------------------------------------------------------------ */

knh_int64_t knh_Int_toint64(Int *o)
{
	KNH_ASSERT(IS_bInt(o));
	return (knh_int64_t)(o->value);
}

/* ======================================================================== */
/* [Float] */

knh_int_t knh_Float_toint(Float *o)
{
	KNH_ASSERT(IS_bFloat(o));
	return (knh_int_t)(o->value);
}

/* ------------------------------------------------------------------------ */

knh_float_t knh_Float_tofloat(Float *o)
{
	KNH_ASSERT(IS_bFloat(o));
	return (knh_float_t)(o->value);
}

/* ------------------------------------------------------------------------ */

knh_int64_t knh_Float_toint64(Float *o)
{
	KNH_ASSERT(IS_bFloat(o));
	return (knh_int64_t)(o->value);
}

/* ======================================================================== */
/* [Int64] */

knh_int_t knh_Int64_toint(Int64 *o)
{
	KNH_ASSERT(IS_bInt64(o));
	return (knh_int_t)(o->value);
}

/* ------------------------------------------------------------------------ */

knh_float_t knh_Int64_tofloat(Int64 *o)
{
	KNH_ASSERT(IS_bInt64(o));
	return (knh_float_t)(o->value);
}

/* ------------------------------------------------------------------------ */

knh_int64_t knh_Int64_toint64(Int64 *o)
{
	KNH_ASSERT(IS_bInt64(o));
	return (knh_int64_t)(o->value);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
