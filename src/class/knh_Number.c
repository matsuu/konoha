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
 * (1) GNU Lesser General Public License 3.0 (with KONOHA_UNDER_LGPL3)
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
/* [conv] */

/* ------------------------------------------------------------------------ */

knh_int_t knh_Number_tointeger(Any *o)
{
	Object *n = (Object*)o;
	switch(n->h.bcid) {
		case CLASS_Nue :
			return 0;
		case CLASS_Boolean :
			return (IS_TRUE(n)) ? 1 : 0;
		case CLASS_Int :
			return (knh_int_t)((Int*)n)->n.ivalue;
		case CLASS_Float :
			return (knh_int_t)((Float*)n)->n.fvalue;
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
			return (knh_float_t)((Int*)n)->n.ivalue;
		case CLASS_Float :
			return (knh_float_t)((Float*)n)->n.fvalue;
	}
	KNH_ASSERT(n->h.bcid == CLASS_Int); /* STOP */
	return (knh_float_t)0.0;
}

///* ======================================================================== */
///* [Int] */
//
//knh_int_t knh_Int_toint(Int *o)
//{
//	KNH_ASSERT(IS_bInt(o));
//	return (knh_int_t)o->value;
//}
//
///* ------------------------------------------------------------------------ */
//
//knh_float_t knh_Int_tofloat(Int *o)
//{
//	KNH_ASSERT(IS_bInt(o));
//	return (knh_float_t)(o->value);
//}

///* ======================================================================== */
///* [Float] */
//
//knh_int_t knh_Float_toint(Float *o)
//{
//	KNH_ASSERT(IS_bFloat(o));
//	return (knh_int_t)(o->value);
//}
//
///* ------------------------------------------------------------------------ */
//
//knh_float_t knh_Float_tofloat(Float *o)
//{
//	KNH_ASSERT(IS_bFloat(o));
//	return (knh_float_t)(o->value);
//}
//

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
