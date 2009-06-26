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
/* [macros] */


///* ------------------------------------------------------------------------ */
//
//knh_Object_t *new_Boolean(Ctx *ctx, int c)
//{
//	return (c) ? KNH_TRUE : KNH_FALSE;
//}

/* ======================================================================== */
/* [Null] */

///* ------------------------------------------------------------------------ */
//
//Object *new_Nue(Ctx *ctx, String *msg)
//{
//	KNH_ASSERT(IS_String(msg));
//	knh_Nue_t *o = (knh_Nue_t*)new_hObject(ctx, FLAG_Nue, CLASS_Nue, CLASS_Nue);
//	KNH_INITv(o->orign, msg);
//	o->str = (knh_uchar_t*)knh_String_tochar(msg);
//	o->size = knh_String_strlen(msg);
//	return (Object*)o;
//}
//
//#define _new_Nue__b(ctx, txt)   new_Nue(ctx, new_String(ctx, txt, NULL));
//#define _new_Nue__s(ctx, txt)   new_Nue(ctx, new_String(ctx, B(txt), NULL));

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
	DBG_P("bcid=%s, cid=%s", CLASSN(g->h.bcid), CLASSN(g->h.cid));
	KNH_ASSERT(IS_bAny(g));
	g->ptr = ptr;
	if(gfree == NULL) gfree = knh_fgfree__default;
	g->gfree = gfree;
}

/* ------------------------------------------------------------------------ */

KNHAPI(Object*) new_Glue(Ctx *ctx, char *lname, void *ptr, knh_fgfree gfree)
{
	knh_class_t cid = konoha_getcid(ctx, B(lname));
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
	if(bcid == bcid2) {
		return ctx->share->StructTable[bcid].fcompareTo(o1, o2);
	}
	else {
		if((o1->h.cid == CLASS_Int || o1->h.cid == CLASS_Float)
		&& (o2->h.cid == CLASS_Int || o2->h.cid == CLASS_Float)) {
			return (int)(knh_Number_tofloat(o1) - knh_Number_tofloat(o2));
		}
		DBG2_P("Compared Incompatible Type %s - %s", CLASSN(o1->h.cid), CLASSN(o2->h.cid));
		return (int)(o1 - o2);
	}
}

/* ------------------------------------------------------------------------ */

int knh_Object_cmp(Object *o1, Object *o2)
{
	/* this funtion is prepared for the compatibility with qsort. */
	return knh_Object_compareTo(konoha_getCurrentContext(), o1, o2);
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
	TODO();
	return STEXT("");
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

