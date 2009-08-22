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

/* ======================================================================== */
/* [Glue] */

static
void knh_fgfree__default(Ctx *ctx, knh_Glue_t *g)
{
	g->ptr = NULL;
	g->gfree = knh_fgfree__default;
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_Glue_init(Ctx *ctx, knh_Glue_t *g, void *ptr, knh_fgfree gfree)
{
	KNH_ASSERT(IS_bAny(g));
	g->ptr = ptr;
	if(gfree == NULL) gfree = knh_fgfree__default;
	g->gfree = gfree;
}

/* ------------------------------------------------------------------------ */

KNHAPI(Object*) new_Glue(Ctx *ctx, char *lname, void *ptr, knh_fgfree gfree)
{
	knh_class_t cid = knh_getcid(ctx, B(lname));
	if(cid == CLASS_unknown) {
		KNH_THROWf(ctx, "Unknown!!: %s", lname);
	}
	knh_Glue_t *g = (knh_Glue_t*)new_Object_bcid(ctx, CLASS_Any, 0);
	g->h.cid = cid;
	knh_Glue_init(ctx, g, ptr, gfree);
	return (Object*)g;
}

/* ======================================================================== */
/* [new] */
/* @method[VIRTUAL] This! Object.new() */

METHOD knh__Object_new(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ======================================================================== */
/* [getkey] */

String *knh_Object_getkey(Ctx *ctx, Object *o)
{
	knh_sfp_t lsfp;
	lsfp.o = o;
	lsfp.data = ((Int*)o)->n.data;
	return ctx->share->StructTable[knh_Object_bcid(o)].fgetkey(ctx, &lsfp);
}

/* ------------------------------------------------------------------------ */
/* @method String! Object.getKey() */

METHOD knh__Object_getKey(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, ctx->share->StructTable[knh_Object_bcid(sfp[0].o)].fgetkey(ctx, sfp));
}

/* ======================================================================== */
/* [copy] */

Object *knh_Object_copy(Ctx *ctx, Object *b)
{
	if(knh_Object_isImmutable(b)) {
		return b;
	}
	DBG2_P("!IMMUTABLE %s", CLASSN(knh_Object_cid(b)));
	return b;
}

/* ======================================================================== */
/* [commons] */

knh_hcode_t knh_Object_hashCode(Ctx *ctx, Object *o)
{
	return ctx->share->StructTable[o->h.bcid].fhashCode(ctx, o);
}

/* ------------------------------------------------------------------------ */


int knh_Object_compareTo(Ctx *ctx, Object *o1, Object *o2)
{
	knh_class_t bcid = o1->h.bcid;
	knh_class_t bcid2 = o2->h.bcid;
	int res;
	if(bcid == bcid2) {
		res = ctx->share->StructTable[bcid].fcompareTo(o1, o2);
	}
	else {
		if((o1->h.cid == CLASS_Int || o1->h.cid == CLASS_Float)
		&& (o2->h.cid == CLASS_Int || o2->h.cid == CLASS_Float)) {
			res = (int)knh_Number_tofloat(o1) - (int)knh_Number_tofloat(o2);
		}
		else {
			res = (int)(o1 - o2);
		}
	}
	DBG2_P("compared %s %s res=%d", CLASSNo(o1), CLASSNo(o2), res);
	return res;
}

/* ------------------------------------------------------------------------ */

int knh_Object_cmp(Object *o1, Object *o2)
{
	/* this funtion is prepared for the compatibility with qsort. */
	return knh_Object_compareTo(knh_getCurrentContext(), o1, o2);
}

/* ------------------------------------------------------------------------ */


knh_bool_t knh_Object_equals(Ctx *ctx, Object *o1, Object *o2)
{
	return (knh_Object_compareTo(ctx, o1, o2) == 0);
}


/* ------------------------------------------------------------------------ */

knh_bytes_t knh_Object_tobytes(Ctx *ctx, Object *o)
{
	switch(o->h.bcid) {
		case STRUCT_String : return knh_String_tobytes((String*)o);
		case STRUCT_Bytes : return knh_Bytes_tobytes((Bytes*)o);
	}
	return STEXT("");
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

