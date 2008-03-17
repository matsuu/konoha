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
/* [structs] */

void
knh_Int64_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	Int64 *b =  (Int64*)s1;
	b->value = 0;
}

/* ------------------------------------------------------------------------ */

void
knh_Int64_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
	Int64 *b =  (Int64*)s1;
	Int64 *b2 = (Int64*)s2;
	b2->value = b->value;
}

/* ------------------------------------------------------------------------ */

knh_int_t
knh_Int64_struct_compare(Ctx *ctx, Struct *s1, Struct *s2) 
{
	Int64 *b =  (Int64*)s1;
	Int64 *b2 = (Int64*)s2;
	//knh_class_t cid = knh_struct_cid(s1);
	TODO();
	return b->value - b2->value;
	//return knh_IntSpec_compare(knh_tclass_getIntUnit(ctx, cid), b->value, b2->value);
}

/* ------------------------------------------------------------------------ */

#define _knh_Int64_struct_traverse NULL


/* ======================================================================== */
/* [constructors] */

Int64* new_Int64__fast(Ctx *ctx, knh_class_t cid, knh_int64_t value)
{
	Int64 *b = (Int64*)knh_Object_malloc0(ctx, KNH_FLAG_Int64, cid, sizeof(Int64));
	b->value = value;
	return b;
}

#define _new_Int64(ctx, value) new_Int64__fast(ctx, CLASS_Int64, value)

/* ------------------------------------------------------------------------ */

Int64* new_Int64__checked(Ctx *ctx, knh_class_t cid, knh_int64_t value)
{
	TODO();
	return new_Int64__fast(ctx, cid, value);
}

/* ======================================================================== */
/* [utils] */

INLINE
knh_int64_t knh_int64_max(knh_int64_t a, knh_int64_t b)
{
	return (a > b) ? a : b;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_int64_t knh_int64_min(knh_int64_t a, knh_int64_t b)
{
	return (a < b) ? a : b;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_uint64_t knh_uint64_max(knh_uint64_t a, knh_uint64_t b)
{
	return (a > b) ? a : b;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_uint64_t knh_uint64_min(knh_uint64_t a, knh_uint64_t b)
{
	return (a < b) ? a : b;
}

///* ======================================================================== */
///* [mappings] */
//
///* @map String Int64 */
//
//Object* 
//knh_String_Int64(Ctx *ctx, Object *self, Mapping *map)
//{
//	knh_bytes_t t = knh_String_tobytes(self);
//	if(!knh_byte_isnum(t)) {
//		return_Null(ctx, "NumberFormat!!: %s", t.buf);
//	}
//	return new_Int64(ctx, knh_bytes_toint(t));
//}
//
///* ------------------------------------------------------------------------ */
//
///* ------------------------------------------------------------------------ */
///* Int64 original */
//
///* @method[VARARGS] Int64! Int64.opAdd(Int64! v) */
//
//INLINE
//knh_int64_t knh_Int64_opAdd(Int64 *b, knh_vargc_t ac, Int64 **v)
//{
//	knh_int64_t i, n = knh_Int64_value(b);
//	for(i = 0; i < ac; i++) {
//		n += knh_Int64_value(v[i]);
//	}
//	return n;
//}
//
///* ------------------------------------------------------------------------ */
//
///* @method[VARAR] Int64! Int64.opSub(Int64! n) */
//
//INLINE
//knh_int64_t knh_Int64_opSub(Int64 *b, knh_vargc_t ac, Int64 **v)
//{
//	knh_int64_t i, n = knh_Int64_value(b);
//	for(i = 0; i < ac; i++) {
//		n -= knh_Int64_value(v[i]);
//	}
//	return n;
//}
//
///* ------------------------------------------------------------------------ */
//
///* @method[VARARGS] Int64! Int64.opMul(Int64! n) */
//
//INLINE
//knh_int64_t knh_Int64_opMul(Int64 *b, knh_vargc_t ac, Int64 **v)
//{
//	knh_int64_t i, n = knh_Int64_value(b);
//	for(i = 0; i < ac; i++) {
//		n *= knh_Int64_value(v[i]);
//	}
//	return n;
//}
//
///* ------------------------------------------------------------------------ */
//
///* @method[VARARGS] Int64! Int64.opDiv(Int64! n) */
//
//INLINE
//knh_int64_t knh_Int64_opDiv(Int64 *b, knh_vargc_t ac, Int64 **v)
//{
//	knh_int64_t i, n = knh_Int64_value(b);
//	for(i = 0; i < ac; i++) {
//		n /= knh_Int64_value(v[i]);
//	}
//	return n;
//}
//
///* ------------------------------------------------------------------------ */
//
///* @method Int64! Int64.opMod(Int64! n) */
//
//INLINE
//knh_int64_t knh_Int64_opMod(Int64 *b, knh_int64_t n)
//{
//	return knh_Int64_value(b) % n;
//}

/* ======================================================================== */
/* [movabletext] */

/* @method void Int64.%dump(OutputStream w=new, Any m) */


void knh_Int64__dump(Ctx *ctx, Int64 *b, OutputStream *w, Any *m)
{
//	char buf[FMT_NSPEC_BUFSIZE];
//	IntSpec *spec = knh_tclass_getIntUnit(ctx, knh_Object_cid(b));
//	knh_IntSpec_format(spec, buf, knh_Int64_value(b)); 
//	knh_prints(ctx, w, buf);
}

#ifdef __cplusplus
}
#endif
