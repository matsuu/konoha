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

#define _INT_BUFSIZ 32
#define _knh_Int_value(b)      (b)->value

/* ======================================================================== */
/* [structs] */

void
knh_Int_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	Int *b =  (Int*)s1;
	b->value = 0;
}

/* ------------------------------------------------------------------------ */

void
knh_Int_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
	Int *b =  (Int*)s1;
	Int *b2 = (Int*)s2;
	b2->value = b->value;
}

/* ------------------------------------------------------------------------ */

knh_int_t
knh_Int_struct_compare(Ctx *ctx, Struct *s1, Struct *s2) 
{
	Int *b =  (Int*)s1;
	Int *b2 = (Int*)s2;
	knh_class_t cid = knh_struct_cid(s1);
	return knh_IntUnit_compare(knh_tclass_getIntUnit(ctx, cid), b->value, b2->value);
}

/* ------------------------------------------------------------------------ */

#define _knh_Int_struct_traverse NULL

/* ======================================================================== */
/* [constructors] */

Int* new_Int__fast(Ctx *ctx, knh_class_t cid, knh_int_t value)
{
	Int *b = (Int*)knh_Object_malloc0(ctx, KNH_FLAG_Int, cid, sizeof(Int));
	b->value = value;
	return b;
}

#define _new_Int(ctx, value) new_Int__checked(ctx, CLASS_Int, value)

/* ======================================================================== */
/* [utils] */

INLINE
knh_int_t knh_int_max(knh_int_t a, knh_int_t b)
{
	return (a > b) ? a : b;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_int_t knh_int_min(knh_int_t a, knh_int_t b)
{
	return (a < b) ? a : b;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_uint_t knh_uint_max(knh_uint_t a, knh_uint_t b)
{
	return (a > b) ? a : b;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_uint_t knh_uint_min(knh_uint_t a, knh_uint_t b)
{
	return (a < b) ? a : b;
}

/* ======================================================================== */

knh_int_t knh_IntNULL_toint(Int *v)
{
	if(IS_NULL(v)) {
		return 0;
	}else {
		return v->value;
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
