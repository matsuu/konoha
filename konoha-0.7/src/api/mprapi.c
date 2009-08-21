/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2005-2009, Kimio Kuramitsu <kimio at ynu.ac.jp>
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

#ifdef KNH_CC_METHODAPI

/* ======================================================================== */
/* [toBoolean] */

/* ------------------------------------------------------------------------ */
/* @map[CONST] String Boolean! @Const @Final */

static MAPPER knh_String_Boolean(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t t = knh_String_tobytes(sfp[0].s);
	int b = (knh_bytes_equalsIgnoreCase(t, STEXT("true")) ||
				knh_bytes_equalsIgnoreCase(t, STEXT("yes")));
	KNH_MAPPED_Boolean(ctx, sfp, b);
}

/* ======================================================================== */
/* [toInt] */

/* ------------------------------------------------------------------------ */
/* @map Float Int! @Const @Final */

static MAPPER knh_Float_Int(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_int_t v = (knh_int_t)sfp[0].fvalue;
	KNH_MAPPED_Int(ctx, sfp, v);
}

/* ------------------------------------------------------------------------ */
/* @map String Int @Const @Final */

static MAPPER knh_String_Int(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_int_t v = 0;
	if(knh_bytes_parseint(knh_String_tobytes(sfp[0].s), &v)) {
		KNH_MAPPED_Int(ctx, sfp, v);
	}
	KNH_MAPPED(ctx, sfp, KNH_NULL);
}


/* ======================================================================== */
/* [toFloat] */

/* ------------------------------------------------------------------------ */
/* @map Int Float! @Const @Final */

static MAPPER knh_Int_Float(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_float_t v = (knh_float_t)sfp[0].ivalue;
	KNH_MAPPED_Float(ctx, sfp, v);
}

/* ------------------------------------------------------------------------ */
/* @map String Float @Final @Const */

static MAPPER knh_String_Float(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_float_t f = 0.0;
	if(knh_bytes_parsefloat(knh_String_tobytes(sfp[0].s), &f)) {
		KNH_MAPPED_Float(ctx, sfp, f);
	}
	else {
		KNH_MAPPED(ctx, sfp, KNH_NULL);
	}
}

/* ======================================================================== */
/* [String] */

/* ------------------------------------------------------------------------ */
/* @map Object String! */

static
MAPPER knh_Object_String(Ctx *ctx, knh_sfp_t *sfp)
{
	Object *o = sfp[0].o;
	Method *mtd = knh_lookupFormatter(ctx, knh_Object_cid(o), METHODN__s);
	if(IS_NULL(mtd)) {
		KNH_MAPPED(ctx, sfp, TS_EMPTY);
	}
	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
	KNH_MOV(ctx, sfp[2].o, o);
	KNH_MOV(ctx, sfp[3].o, cwb->w);
	KNH_MOV(ctx, sfp[4].o, KNH_NULL);
	KNH_SCALL(ctx, sfp, 1, mtd, 2);
	KNH_MAPPED(ctx, sfp, knh_cwb_newString(ctx, cwb));
}

/* ------------------------------------------------------------------------ */
/* @map[CONST] Boolean String! @Const @Final @LossLess */

static MAPPER knh_Boolean_String(Ctx *ctx, knh_sfp_t *sfp)
{
	String *s = (p_bool(sfp[0])) ? TS_true : TS_false;
	KNH_MAPPED(ctx, sfp, s);
}

/* ------------------------------------------------------------------------ */
/* @map Int String! @Const @Final @LossLess */

static MAPPER knh_Int_String(Ctx *ctx, knh_sfp_t *sfp)
{
	char buf[256];
	knh_snprintf(buf, sizeof(buf), KNH_INT_FMT, sfp[0].ivalue);
	KNH_MAPPED(ctx, sfp, new_String(ctx, B(buf), NULL));
}

/* ------------------------------------------------------------------------ */
/* @map Float String! @Const @Final @LossLess */

static MAPPER knh_Float_String(Ctx *ctx, knh_sfp_t *sfp)
{
	char buf[256];
	knh_snprintf(buf, sizeof(buf), KNH_FLOAT_FMT, sfp[0].fvalue);
	KNH_MAPPED(ctx, sfp, new_String(ctx, B(buf), NULL));
}

/* ------------------------------------------------------------------------ */
/* @map Bytes String! @Const @Final */

static
MAPPER knh_Bytes_String(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t t = knh_Bytes_tobytes((Bytes*)sfp[0].o);
	String *s = TS_EMPTY;
	if(knh_bytes_checkENCODING(t)) {
		s = new_String(ctx, t, NULL);
	}
	KNH_MAPPED(ctx, sfp, s);
}

/* ======================================================================== */
/* [Bytes] */

/* ------------------------------------------------------------------------ */
/* @map String Bytes! @Const @Final */

static
MAPPER knh_String_Bytes(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *b = new_Bytes(ctx, knh_String_strlen(sfp[0].s) + 1);
	knh_Bytes_write(ctx, b, knh_String_tobytes(sfp[0].s));
	KNH_MAPPED(ctx, sfp, b);
}

/* ======================================================================== */
/* [Iterator] */

/* ------------------------------------------------------------------------ */
/* @map Object Iterator! @Const */

static MAPPER knh_Object_Iterator(Ctx *ctx, knh_sfp_t *sfp)
{
	Object *o = sfp[0].o;
	KNH_MAPPED(ctx, sfp, new_Iterator(ctx, o->h.cid, o, NULL));
}

/* ------------------------------------------------------------------------ */
/* @method This.. Object.opItr() */

static METHOD knh__Object_opItr(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, new_Iterator(ctx, knh_Object_cid(sfp[0].o), sfp[0].o, NULL));
}

/* ------------------------------------------------------------------------ */
/* [Array] */

/* @map Array Iterator! */

MAPPER knh_Array_Iterator(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_MAPPED(ctx, sfp,
		new_ArrayIterator(ctx, ctx->share->ClassTable[(sfp[0].o)->h.cid].p1, (Array*)sfp[0].o));
}

/* ------------------------------------------------------------------------ */
/* @method T1.. Array.opItr() */

static METHOD knh__Array_opItr(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp,
		new_ArrayIterator(ctx, ctx->share->ClassTable[(sfp[0].o)->h.cid].p1, (Array*)sfp[0].o));
}

/* ------------------------------------------------------------------------ */
/* [IArray] */

static
ITRNEXT knh_IArray_var_next(Ctx *ctx, knh_sfp_t *sfp, int n)
{
	IArray *o = (IArray*)DP(sfp[0].it)->source;
	KNH_ASSERT(IS_bIArray(o));
	size_t pos = DP(sfp[0].it)->pos;
	while(pos < o->size) {
		DP(sfp[0].it)->pos = pos+1;
		KNH_ITRNEXT_Int(ctx, sfp, n, o->ilist[pos]);
		pos++;
	}
	KNH_ITREND(ctx, sfp, n);
}

/* ------------------------------------------------------------------------ */
/* @map IArray Iterator! */

MAPPER knh_IArray_Iterator(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_MAPPED(ctx, sfp,
		new_Iterator(ctx, ctx->share->ClassTable[(sfp[0].o)->h.cid].p1, sfp[0].o, knh_IArray_var_next));
}

/* ------------------------------------------------------------------------ */
/* @method Int.. IArray.opItr() */

static METHOD knh__IArray_opItr(Ctx *ctx, knh_sfp_t *sfp)
{
	IArray *o = (IArray*)sfp[0].o;
	KNH_RETURN(ctx, sfp, new_Iterator(ctx, ctx->share->ClassTable[o->h.cid].p1, UP(o), knh_IArray_var_next));
}

/* ------------------------------------------------------------------------ */
/* [FArray] */

static
ITRNEXT knh_FArray_var_next(Ctx *ctx, knh_sfp_t *sfp, int n)
{
	FArray *o = (FArray*)DP(sfp[0].it)->source;
	KNH_ASSERT(IS_bFArray(o));
	size_t pos = DP(sfp[0].it)->pos;
	while(pos < o->size) {
		DP(sfp[0].it)->pos = pos+1;
		KNH_ITRNEXT_Float(ctx, sfp, n, o->flist[pos]);
		pos++;
	}
	KNH_ITREND(ctx, sfp, n);
}

/* ------------------------------------------------------------------------ */
/* @map FArray Iterator! */

MAPPER knh_FArray_Iterator(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_MAPPED(ctx, sfp,
		new_Iterator(ctx, ctx->share->ClassTable[(sfp[0].o)->h.cid].p1, sfp[0].o, knh_FArray_var_next));
}

/* ------------------------------------------------------------------------ */
/* @method T1.. FArray.opItr() */

static METHOD knh__FArray_opItr(Ctx *ctx, knh_sfp_t *sfp)
{
	FArray *o = (FArray*)sfp[0].o;
	KNH_RETURN(ctx, sfp, new_Iterator(ctx, ctx->share->ClassTable[o->h.cid].p1, UP(o), knh_FArray_var_next));
}


/* ======================================================================== */
/* [Iterator] */

/* ------------------------------------------------------------------------ */
/* @map Iterator Array! */

MAPPER knh_Iterator_Array(Ctx *ctx, knh_sfp_t *sfp)
{
	Iterator *it = sfp[0].it;
	Array *a = new_Array(ctx, ctx->share->ClassTable[it->h.cid].p1, 0);
	while(it->fnext_1(ctx, sfp, 1)) {
		knh_sfp_boxing(ctx, sfp + 1);
		knh_Array_add(ctx, a, sfp[1].o);
	}
	KNH_MAPPED(ctx, sfp, a);
}

/* ------------------------------------------------------------------------ */

#endif/* KNH_CC_METHODAPI*/

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
