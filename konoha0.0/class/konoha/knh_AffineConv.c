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

void knh_AffineConv_struct_init(Ctx *ctx, knh_AffineConv_struct *b, int init, Object *cs)
{
	b->scale = 1.0;
	b->shift = 0.0;
}

/* ------------------------------------------------------------------------ */

#define _knh_AffineConv_struct_copy      NULL

/* ------------------------------------------------------------------------ */

#define _knh_AffineConv_struct_compare   NULL

/* ------------------------------------------------------------------------ */

#define _knh_AffineConv_struct_traverse  NULL

/* ======================================================================== */
/* [constructors] */

AffineConv *new_AffineConv(Ctx *ctx, knh_float_t fa, knh_float_t fb)
{
	knh_AffineConv_t *o = 
		(AffineConv*)new_Object_malloc(ctx, FLAG_AffineConv, CLASS_AffineConv, sizeof(knh_AffineConv_struct));
	//knh_AffineConv_struct_init(ctx, DP(o), 0, NULL);
	DP(o)->scale = fa;
	DP(o)->shift = fb;
	return o;
}

/* ======================================================================== */
/* [conv] */

static
Int *knh_AffineConv_fmap__i2i(Ctx *ctx, Int *o, Mapper *mpr)
{
	AffineConv *u = (AffineConv*)DP(mpr)->mapdata;
	knh_float_t y = (o->value * DP(u)->scale) + DP(u)->shift;
	return new_IntX(ctx, DP(mpr)->tcid, (knh_int_t)y);
}

/* ------------------------------------------------------------------------ */

static
Int64 *knh_AffineConv_fmap__i2l(Ctx *ctx, Int *o, Mapper *mpr)
{
	AffineConv *u = (AffineConv*)DP(mpr)->mapdata;
	knh_float_t y = (o->value * DP(u)->scale) + DP(u)->shift;
	return new_Int64X(ctx, DP(mpr)->tcid, (knh_int64_t)y);
}

/* ------------------------------------------------------------------------ */

static
Float *knh_AffineConv_fmap__i2f(Ctx *ctx, Int *o, Mapper *mpr)
{
	AffineConv *u = (AffineConv*)DP(mpr)->mapdata;
	knh_float_t y = (o->value * DP(u)->scale) + DP(u)->shift;
	return new_FloatX(ctx, DP(mpr)->tcid, (knh_float_t)y);
}

/* ------------------------------------------------------------------------ */

static
Int *knh_AffineConv_fmap__l2i(Ctx *ctx, Int64 *o, Mapper *mpr)
{
	AffineConv *u = (AffineConv*)DP(mpr)->mapdata;
	knh_float_t y = (o->value * DP(u)->scale) + DP(u)->shift;
	return new_IntX(ctx, DP(mpr)->tcid, (knh_int_t)y);
}

/* ------------------------------------------------------------------------ */

static
Int64 *knh_AffineConv_fmap__l2l(Ctx *ctx, Int64 *o, Mapper *mpr)
{
	AffineConv *u = (AffineConv*)DP(mpr)->mapdata;
	knh_float_t y = (o->value * DP(u)->scale) + DP(u)->shift;
	return new_Int64X(ctx, DP(mpr)->tcid, (knh_int64_t)y);
}

/* ------------------------------------------------------------------------ */

static
Float *knh_AffineConv_fmap__l2f(Ctx *ctx, Int64 *o, Mapper *mpr)
{
	AffineConv *u = (AffineConv*)DP(mpr)->mapdata;
	knh_float_t y = (o->value * DP(u)->scale) + DP(u)->shift;
	return new_FloatX(ctx, DP(mpr)->tcid, (knh_float_t)y);
}

/* ------------------------------------------------------------------------ */

static
Int *knh_AffineConv_fmap__f2i(Ctx *ctx, Float *o, Mapper *mpr)
{
	AffineConv *u = (AffineConv*)DP(mpr)->mapdata;
	knh_float_t y = (o->value * DP(u)->scale) + DP(u)->shift;
	return new_IntX(ctx, DP(mpr)->tcid, (knh_int_t)y);
}

/* ------------------------------------------------------------------------ */

static
Int64 *knh_AffineConv_fmap__f2l(Ctx *ctx, Float *o, Mapper *mpr)
{
	AffineConv *u = (AffineConv*)DP(mpr)->mapdata;
	knh_float_t y = (o->value * DP(u)->scale) + DP(u)->shift;
	return new_Int64X(ctx, DP(mpr)->tcid, (knh_int64_t)y);
}

/* ------------------------------------------------------------------------ */

static
Float *knh_AffineConv_fmap__f2f(Ctx *ctx, Float *o, Mapper *mpr)
{
	AffineConv *u = (AffineConv*)DP(mpr)->mapdata;
	knh_float_t y = (o->value * DP(u)->scale) + DP(u)->shift;
	return new_FloatX(ctx, DP(mpr)->tcid, (knh_float_t)y);
}

/* ------------------------------------------------------------------------ */

f_mapper knh_tmapper_faffine(knh_class_t scid, knh_class_t tcid)
{
	if(scid == CLASS_Int) {
		if(tcid == CLASS_Int)    return (f_mapper)knh_AffineConv_fmap__i2i;
		if(tcid == CLASS_Int64)  return (f_mapper)knh_AffineConv_fmap__i2l;
		KNH_ASSERT(tcid == CLASS_Float);
		return (f_mapper)knh_AffineConv_fmap__i2f;
	}
	if(scid == CLASS_Int64) {
		if(tcid == CLASS_Int)    return (f_mapper)knh_AffineConv_fmap__l2i;
		if(tcid == CLASS_Int64)  return (f_mapper)knh_AffineConv_fmap__l2l;
		KNH_ASSERT(tcid == CLASS_Float);
		return (f_mapper)knh_AffineConv_fmap__l2f;
	}
	KNH_ASSERT(scid == CLASS_Float);
	{
		if(tcid == CLASS_Int)    return (f_mapper)knh_AffineConv_fmap__f2i;
		if(tcid == CLASS_Int64)  return (f_mapper)knh_AffineConv_fmap__f2l;
		KNH_ASSERT(tcid == CLASS_Float);
		return (f_mapper)knh_AffineConv_fmap__f2f;
	}
}

/* ------------------------------------------------------------------------ */
/* [TAFFINE] */

#define _KNH_FLAG_MMF_AFFINE (KNH_FLAG_MMF_SIGNIFICANT|KNH_FLAG_MMF_SYNONYM|KNH_FLAG_MMF_TOTAL|KNH_FLAG_MMF_STATIC)

static void
KNH_TAFFINE_(Ctx *ctx, knh_class_t scid, knh_class_t tcid, knh_float_t scale, knh_float_t shift)
{
	Mapper *mpr = new_Mapper(ctx, KNH_FLAG_MMF_AFFINE, scid, tcid, 
			knh_tmapper_faffine(knh_tClass[scid].bcid, knh_tClass[tcid].bcid), 
			(Object*)new_AffineConv(ctx, scale, shift));
	knh_ClassMap_add(ctx, knh_tClass[scid].cmap, mpr);
}

/* ------------------------------------------------------------------------ */

void
KNH_TAFFINE(Ctx *ctx, knh_class_t scid, knh_class_t tcid, knh_float_t scale, knh_float_t shift)
{
	DEBUG_ASSERT_cid(scid);
	DEBUG_ASSERT_cid(tcid);
	{
		KNH_TAFFINE_(ctx, scid, tcid, scale, shift);
		if(scale != 0.0) {
			KNH_TAFFINE_(ctx, tcid, scid, 1.0 / scale, -(shift/scale));
		}
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
