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

#define _knh_Float_value(o)    (o)->value

/* ======================================================================== */
/* [structs] */

void
knh_Float_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	Float *b =  (Float*)s1;
	b->value = 0.0;
}

/* ------------------------------------------------------------------------ */

void
knh_Float_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
	Float *b =  (Float*)s1;
	Float *b2 = (Float*)s2;
	b2->value = b->value;
}

/* ------------------------------------------------------------------------ */

knh_int_t
knh_Float_struct_compare(Ctx *ctx, Struct *s1, Struct *s2) 
{
	Float *b =  (Float*)s1;
	Float *b2 = (Float*)s2;
	return b->value - b2->value;
}

/* ------------------------------------------------------------------------ */

#define _knh_Float_struct_traverse NULL

/* ======================================================================== */
/* [constructors] */

Float* new_Float__fast(Ctx *ctx, knh_class_t cid, knh_float_t value)
{
	Float *b = (Float*)knh_Object_malloc0(ctx, KNH_FLAG_Float, cid, sizeof(Float));
	b->value = value;
	return b;
}

#define _new_Float(ctx, value) new_Float__fast(ctx, CLASS_Float, value)

/* ------------------------------------------------------------------------ */

INLINE
Float* new_Float__checked(Ctx *ctx, knh_class_t cid, knh_float_t value)
{
	return knh_FloatUnit_value(ctx, knh_tclass_getFloatUnit(ctx, cid), value);
}

/* ======================================================================== */
/* [utils] */

INLINE
knh_float_t knh_float_max(knh_float_t a, knh_float_t b)
{
	return (a > b) ? a : b;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_float_t knh_float_min(knh_float_t a, knh_float_t b)
{
	return (a < b) ? a : b;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
