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
/* [Number] */

/* ------------------------------------------------------------------------ */

knh_int_t knh_Number_tointeger(Any *o)
{
	Object *n = (Object*)o;
	switch(n->h.bcid) {
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
		case CLASS_Boolean :
#ifndef KNH_USING_NOFLOAT
			return (IS_TRUE(n)) ? 1 : 0;
#else
			return (IS_TRUE(n)) ? 1.0 : 0.0;
#endif
		case CLASS_Int :
			return (knh_float_t)((Int*)n)->n.ivalue;
		case CLASS_Float :
			return (knh_float_t)((Float*)n)->n.fvalue;
	}
	KNH_ASSERT(n->h.bcid == CLASS_Int); /* STOP */
#ifndef KNH_USING_NOFLOAT
	return (IS_TRUE(n)) ? 1 : 0;
#else
	return (IS_TRUE(n)) ? 1.0 : 0.0;
#endif
}

/* ======================================================================== */
/* [Int] */

KNHAPI(Int*) new_Int(Ctx *ctx, knh_int_t value)
{
	knh_Int_t *b = (knh_Int_t*)new_hObject(ctx, FLAG_Int, CLASS_Int, CLASS_Int);
	b->n.ivalue = value;
	return b;
}

/* ------------------------------------------------------------------------ */

KNHAPI(Int*) new_IntX__fast(Ctx *ctx, knh_class_t cid, knh_int_t value)
{
	knh_Int_t *b = (knh_Int_t*)new_hObject(ctx, FLAG_Int, CLASS_Int, cid);
	b->n.ivalue = value;
	return b;
}

/* ------------------------------------------------------------------------ */

KNHAPI(Int*) new_IntX(Ctx *ctx, knh_class_t cid, knh_int_t value)
{
	ClassSpec *u = konoha_getClassSpec(ctx, cid);
	if(DP(u)->fichk(u, value)) {
		Int *n = (knh_Int_t*)new_hObject(ctx, FLAG_Int, CLASS_Int, cid);
		n->n.ivalue = value;
		return n;
	}
	else {
		if(DP(u)->imin >= 0) {
			KNH_WARNING(ctx, _("out of range: %u of %s"), value, CLASSN(cid));
		}
		else {
			KNH_WARNING(ctx, _("out of range: %d of %s"), value, CLASSN(cid));
		}
		return DP(u)->ivalue;
	}
}

/* ======================================================================== */
/* [Float] */

KNHAPI(Float*) new_Float(Ctx *ctx, knh_float_t value)
{
	Float *b = (Float*)new_hObject(ctx, FLAG_Float, CLASS_Float, CLASS_Float);
	b->n.fvalue = value;
	return b;
}

/* ------------------------------------------------------------------------ */

KNHAPI(Float*) new_FloatX__fast(Ctx *ctx, knh_class_t cid, knh_float_t value)
{
	Float *b = (Float*)new_hObject(ctx, FLAG_Float, CLASS_Float, cid);
	b->n.fvalue = value;
	return b;
}

/* ------------------------------------------------------------------------ */

KNHAPI(Float*) new_FloatX(Ctx *ctx, knh_class_t cid, knh_float_t value)
{
	KNH_ASSERT_cid(cid);
	ClassSpec *u = konoha_getClassSpec(ctx, cid);
	if(DP(u)->ffchk(u, value)) {
		Float *f = (Float*)new_hObject(ctx, FLAG_Float, CLASS_Float, cid);
		f->n.fvalue = value;
		return f;
	}
	else {
		KNH_WARNING(ctx, _("out of range: %f of %s"), value, CLASSN(cid));
		return DP(u)->fvalue;
	}
}

/* ======================================================================== */
/* [Affine] */

static
AffineConv *new_AffineConv(Ctx *ctx, knh_float_t fa, knh_float_t fb)
{
	knh_AffineConv_t *af = (AffineConv*)new_Object_bcid(ctx, CLASS_AffineConv, 0);
	af->scale = (knh_affinefloat_t)fa;
	af->shift = (knh_affinefloat_t)fb;
	return af;
}

/* ------------------------------------------------------------------------ */
/* [mapper] */

static
MAPPER knh_AffineConv_fmap__i2i(Ctx *ctx, knh_sfp_t *sfp)
{
	AffineConv *af = (AffineConv*)DP(sfp[1].mpr)->mapdata;
	KNH_ASSERT(IS_AffineConv(af));
	knh_float_t y = (sfp[0].ivalue * af->scale) + af->shift;
	KNH_MAPPED_Int(ctx, sfp, (knh_int_t)y);
}

/* ------------------------------------------------------------------------ */

static
MAPPER knh_AffineConv_fmap__i2f(Ctx *ctx, knh_sfp_t *sfp)
{
	AffineConv *af = (AffineConv*)DP(sfp[1].mpr)->mapdata;
	KNH_ASSERT(IS_AffineConv(af));
	knh_float_t y = (sfp[0].ivalue * af->scale) + af->shift;
	KNH_MAPPED_Float(ctx, sfp, y);
}

/* ------------------------------------------------------------------------ */

static
MAPPER knh_AffineConv_fmap__f2i(Ctx *ctx, knh_sfp_t *sfp)
{
	AffineConv *af = (AffineConv*)DP(sfp[1].mpr)->mapdata;
	KNH_ASSERT(IS_AffineConv(af));
	knh_float_t y = (sfp[0].fvalue * af->scale) + af->shift;
	KNH_MAPPED_Int(ctx, sfp, (knh_int_t)y);
}

/* ------------------------------------------------------------------------ */

static
MAPPER knh_AffineConv_fmap__f2f(Ctx *ctx, knh_sfp_t *sfp)
{
	AffineConv *af = (AffineConv*)DP(sfp[1].mpr)->mapdata;
	KNH_ASSERT(IS_AffineConv(af));
	knh_float_t y = (sfp[0].fvalue * af->scale) + af->shift;
	KNH_MAPPED_Float(ctx, sfp, y);
}

/* ------------------------------------------------------------------------ */

static
knh_fmapper knh_fmapper_affine(knh_class_t scid, knh_class_t tcid)
{
	if(scid == CLASS_Int) {
		if(tcid == CLASS_Int) return knh_AffineConv_fmap__i2i;
		KNH_ASSERT(tcid == CLASS_Float);
		return knh_AffineConv_fmap__i2f;
	}
	//KNH_ASSERT(scid == CLASS_Float);
	{
		if(tcid == CLASS_Int) return knh_AffineConv_fmap__f2i;
		//KNH_ASSERT(tcid == CLASS_Float);
		return knh_AffineConv_fmap__f2f;
	}
}

/* ------------------------------------------------------------------------ */
/* [TAFFINE] */

#define _KNH_FLAG_MMF_AFFINE (KNH_FLAG_MMF_ICAST|KNH_FLAG_MMF_SYNONYM|KNH_FLAG_MMF_TOTAL|KNH_FLAG_MMF_CONST)

static
void KNH_TAFFINE(Ctx *ctx, knh_class_t scid, knh_class_t tcid, knh_float_t scale, knh_float_t shift)
{
	Mapper *mpr = new_Mapper(ctx, KNH_FLAG_MMF_AFFINE, scid, tcid,
			knh_fmapper_affine(ctx->share->ClassTable[scid].bcid, ctx->share->ClassTable[tcid].bcid),
			(Object*)new_AffineConv(ctx, scale, shift));
	knh_ClassMap_add(ctx, ctx->share->ClassTable[scid].cmap, mpr);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_addAffineMapper(Ctx *ctx, knh_class_t scid, char *text, knh_float_t scale, knh_float_t shift)
{
	//KNH_ASSERT_cid(scid);
	knh_class_t tcid = konoha_findcid(ctx, B(text));
	if(tcid != CLASS_unknown && ctx->share->ClassTable[tcid].bcid != tcid) {
		KNH_TAFFINE(ctx, scid, tcid, scale, shift);
#ifndef KONOHA_ON_LKM
		if(scale != 0.0) {
			KNH_TAFFINE(ctx, tcid, scid, 1.0 / scale, -(shift/scale));
		}
#else
		if(scale != 0) {
			KNH_TAFFINE(ctx, tcid, scid, 1 / scale, -(shift/scale));
		}
#endif


	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
