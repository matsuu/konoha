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
/* [constructors] */

AffineConv *new_AffineConv(Ctx *ctx, knh_float_t fa, knh_float_t fb)
{
	knh_AffineConv_t *af = (AffineConv*)new_Object_bcid(ctx, CLASS_AffineConv, 0);
	af->scale = (knh_affinefloat_t)fa;
	af->shift = (knh_affinefloat_t)fb;
	return af;
}

/* ======================================================================== */
/* [conv] */

static
MAPPER knh_AffineConv_fmap__i2i(Ctx *ctx, knh_sfp_t *sfp)
{
	AffineConv *af = (AffineConv*)sfp[1].o;
	KNH_ASSERT(IS_AffineConv(af));
	knh_float_t y = (sfp[0].ivalue * af->scale) + af->shift;
	KNH_MAPPED_Int(ctx, sfp, (knh_int_t)y);
}

/* ------------------------------------------------------------------------ */

static
MAPPER knh_AffineConv_fmap__i2f(Ctx *ctx, knh_sfp_t *sfp)
{
	AffineConv *af = (AffineConv*)sfp[1].o;
	KNH_ASSERT(IS_AffineConv(af));
	knh_float_t y = (sfp[0].ivalue * af->scale) + af->shift;
	KNH_MAPPED_Float(ctx, sfp, y);
}

/* ------------------------------------------------------------------------ */

static
MAPPER knh_AffineConv_fmap__f2i(Ctx *ctx, knh_sfp_t *sfp)
{
	AffineConv *af = (AffineConv*)sfp[1].o;
	KNH_ASSERT(IS_AffineConv(af));
	knh_float_t y = (sfp[0].fvalue * af->scale) + af->shift;
	KNH_MAPPED_Int(ctx, sfp, (knh_int_t)y);
}

/* ------------------------------------------------------------------------ */

static
MAPPER knh_AffineConv_fmap__f2f(Ctx *ctx, knh_sfp_t *sfp)
{
	AffineConv *af = (AffineConv*)sfp[1].o;
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
	KNH_ASSERT(scid == CLASS_Float);
	{
		if(tcid == CLASS_Int) return knh_AffineConv_fmap__f2i;
		KNH_ASSERT(tcid == CLASS_Float);
		return knh_AffineConv_fmap__f2f;
	}
}

/* ------------------------------------------------------------------------ */
/* [TAFFINE] */

#define _KNH_FLAG_MMF_AFFINE (KNH_FLAG_MMF_SIGNIFICANT|KNH_FLAG_MMF_SYNONYM|KNH_FLAG_MMF_TOTAL|KNH_FLAG_MMF_CONST)

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
		if(scale != 0.0) {
			KNH_TAFFINE(ctx, tcid, scid, 1.0 / scale, -(shift/scale));
		}
	}
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
