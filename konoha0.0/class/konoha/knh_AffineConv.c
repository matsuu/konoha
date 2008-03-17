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

void knh_AffineConv_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	AffineConv *b = (AffineConv*)s;
	b->scale = 1.0;
	b->shift = 0.0;
	b->iscale = 1;
	b->ishift = 0;
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
	AffineConv *b = knh_Object_malloc(ctx, CLASS_AffineConv);
	b->scale = fa;
	b->shift = fb;
	b->iscale = (knh_int_t)fa;
	b->ishift = (knh_int_t)fb;
	return b;
}

/* ======================================================================== */
/* [conv] */

Object *knh_AffineConv_fmap__ftof(Ctx *ctx, Object *self, MapMap *map)
{
	AffineConv *b = (AffineConv*)map->config;
	knh_float_t y = knh_Number_tofloat((Number*)self) * b->scale + b->shift;
	return new_Number__f(ctx, map->tcid, y);
}

/* ------------------------------------------------------------------------ */

Object *knh_AffineConv_fmap__itof(Ctx *ctx, Object *self, MapMap *map)
{
	AffineConv *b = (AffineConv*)map->config;
	knh_float_t y = knh_Number_tofloat((Number*)self) * b->scale + b->shift;
	return new_Number__f(ctx, map->tcid, y);
}

/* ------------------------------------------------------------------------ */

Object *knh_AffineConv_fmap__ftoi(Ctx *ctx, Object *self, MapMap *map)
{
	AffineConv *b = (AffineConv*)map->config;
	knh_int_t y = knh_Number_toint((Number*)self) * b->iscale + b->ishift;
	return new_Number__i(ctx, map->tcid, y);
}

/* ------------------------------------------------------------------------ */

Object *knh_AffineConv_fmap__itoi(Ctx *ctx, Object *self, MapMap *map)
{
	AffineConv *b = (AffineConv*)map->config;
	knh_int_t y = knh_Number_toint((Number*)self) * b->iscale + b->ishift;
	return new_Number__i(ctx, map->tcid, y);
}

/* ------------------------------------------------------------------------ */

/* @dispatch knh_Object_fmap AffineConv */

f_mapmap knh_AffineConv_fmap(Ctx *ctx, AffineConv *b, knh_class_t scpid, knh_class_t tpcid)
{
	DEBUG_ASSERT(IS_AffineConv(b));
	knh_class_t scid = knh_tclass_bcid(scpid);
	knh_class_t tcid = knh_tclass_bcid(tpcid);

	DEBUG_ASSERT(IS_CLASS_Number(scid));
	DEBUG_ASSERT(IS_CLASS_Number(tcid));
	
	switch(scid) {
		case CLASS_Int:
			if(tcid == CLASS_Int) {
				return knh_AffineConv_fmap__itoi;
			}
			else if(tcid == CLASS_Float) {
				return knh_AffineConv_fmap__itof;
			}
		case CLASS_Float:
			if(tcid == CLASS_Int) {
				return knh_AffineConv_fmap__ftoi;
			}
			else if(tcid == CLASS_Float) {
				return knh_AffineConv_fmap__ftof;
			}
	}
	DEBUG("unknown fconv %s => %s", CLASSN(scid), CLASSN(tcid));
	return NULL;
}

/* ------------------------------------------------------------------------ */

/* @dispatch new_MapMap_inv AffineConv */

MapMap *new_MapMap_inv__AffineConv(Ctx *ctx, MapMap *map)
{
	DEBUG_ASSERT(IS_AffineConv(map->config));
	AffineConv *b = (AffineConv*)map->config;
	AffineConv *fconv = new_AffineConv(ctx, 1.0 / b->scale, - (b->shift / b->scale));
	f_mapmap fmap = knh_AffineConv_fmap(ctx, fconv, map->tcid, map->scid);
	return new_MapMap(ctx, map->flag, map->tcid, map->scid, fmap, fconv);
}

/* ------------------------------------------------------------------------ */
/* [TAFFINE] */

#define _KNH_FLAG_MMF_AFFINE (KNH_FLAG_MMF_SIGNIFICANT|KNH_FLAG_MMF_SYNONYM|KNH_FLAG_MMF_TOTAL|KNH_FLAG_MMF_STATIC)

void
KNH_TAFFINE(Ctx *ctx, knh_class_t scid, knh_class_t tcid, knh_float_t scale, knh_float_t shift)
{
	ClassRel *crel = knh_tclass_crel(scid);
	MapMap *map = new_MapMap(ctx, KNH_FLAG_MMF_AFFINE, scid, tcid, knh_AffineConv_fmap__ftof, new_AffineConv(ctx, scale, shift));
	knh_ClassRel_add(ctx, crel, map);

	crel = knh_tclass_crel(tcid);
	knh_float_t iscale = 1.0 / scale;
	knh_float_t ishift = -(shift / scale);
	map = new_MapMap(ctx, KNH_FLAG_MMF_AFFINE, tcid, scid, knh_AffineConv_fmap__ftof, new_AffineConv(ctx, iscale, ishift));
	knh_ClassRel_add(ctx, crel, map);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
