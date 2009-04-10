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

#ifdef KNH_CC_METHODAPI

/* ======================================================================== */
/* [common] */

static
knh_hcode_t knh_stack_hashCode(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_class_t bcid = (sfp[0].o)->h.bcid;
	if(CLASS_Boolean <= bcid && bcid <= CLASS_Float) {
		return (knh_hcode_t)(sfp[0].i)->n.data;
	}
	return ctx->share->StructTable[bcid].fhashCode(ctx, sfp[0].o);
}

/* ------------------------------------------------------------------------ */

static
int knh_stack_equals(Ctx *ctx, knh_sfp_t *sfp, Object *o)
{
	knh_class_t bcid = (sfp[0].o)->h.bcid;
	if(CLASS_Boolean <= bcid && bcid <= CLASS_Float) {
		return ((sfp[0].i)->n.data == ((Int*)o)->n.data);
	}
	return (knh_Object_compareTo(ctx, sfp[0].o, o) == 0);
}

/* ------------------------------------------------------------------------ */
/* @method This! HashMap.new(Int init) */

static METHOD knh__HashMap_new(Ctx *ctx, knh_sfp_t *sfp)
{
	HashMap *o = (HashMap*)sfp[0].o;
	int init = IS_NULL(sfp[1].o) ? KNH_HASH_INITSIZE: p_int(sfp[1]);
	if(init > 0) {
		ctx->share->StructTable[STRUCT_HashMap].finit(ctx, sfp[0].o, init);
	}
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* @method void HashMap.get(Any1 key) */

static METHOD knh__HashMap_get(Ctx *ctx, knh_sfp_t *sfp)
{
	HashMap *o = (HashMap*)sfp[0].o;
	knh_hcode_t hcode = knh_stack_hashCode(ctx, sfp + 1);
	knh_uintptr_t h =  hcode % DP(o)->hmax;
	knh_hashentry_t *e = DP(o)->array[h];

	while(e != NULL) {
		if(e->hcode == hcode
				&& knh_Object_cid(sfp[1].o) == knh_Object_cid(e->key)
				&& knh_stack_equals(ctx, sfp + 1, e->key)) {
			KNH_RETURN(ctx, sfp, e->value);
		}
		e = e->next;
	}
	KNH_RETURN(ctx, sfp, KNH_NULL);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! HashMap.opHas(Any1 key) */

static METHOD knh__HashMap_opHas(Ctx *ctx, knh_sfp_t *sfp)
{
	HashMap *o = (HashMap*)sfp[0].o;
	knh_hcode_t hcode = knh_stack_hashCode(ctx, sfp + 1);
	knh_uintptr_t h =  hcode % DP(o)->hmax;
	knh_hashentry_t *e = DP(o)->array[h];

	while(e != NULL) {
		if(e->hcode == hcode
				&& knh_Object_cid(sfp[1].o) == knh_Object_cid(e->key)
				&& knh_stack_equals(ctx, sfp + 1, e->key)) {
			KNH_RETURN_Boolean(ctx, sfp, 1);
		}
		e = e->next;
	}
	KNH_RETURN_Boolean(ctx, sfp, 0);
}

/* ------------------------------------------------------------------------ */
/* @method void HashMap.remove(Any1 key) */

static METHOD knh__HashMap_remove(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {
		knh_Hash_t *o = (knh_Hash_t*)sfp[0].o;
		knh_hcode_t hcode = knh_stack_hashCode(ctx, sfp + 1);
		knh_uintptr_t h =  hcode % DP(o)->hmax;
		knh_hashentry_t *e = DP(o)->array[h];
		knh_hashentry_t **prev_next = &(DP(o)->array[h]);

		while(e != NULL) {
			if(e->hcode == hcode
					&& knh_Object_cid(sfp[1].o) == knh_Object_cid(e->key)
					&& knh_stack_equals(ctx, sfp + 1, e->key)) {
				prev_next[0] = e->next;
				knh_hashentry_collect(ctx, o, e);
				DP(o)->size--;
			}
			prev_next = &(e->next);
			e = e->next;
		}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void HashMap.set(Any1! key, Any2 value) */

static METHOD knh__HashMap_set(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_IMM(sfp[0].o)) {
		if(IS_NULL(sfp[2].o)) {
			knh__HashMap_remove(ctx, sfp);
			return ;
		}

		knh_Hash_t *o = (knh_Hash_t*)sfp[0].o;
		knh_hcode_t hcode = knh_stack_hashCode(ctx, sfp + 1);
		knh_uintptr_t h =  hcode % DP(o)->hmax;
		knh_hashentry_t *e = DP(o)->array[h];

		while(e != NULL) {
			if(e->hcode == hcode
					&& knh_Object_cid(sfp[1].o) == knh_Object_cid(e->key)
					&& knh_stack_equals(ctx, sfp + 1, e->key)) {
				knh_sfp_boxing(ctx, sfp+2);
				KNH_SETv(ctx, e->value, sfp[2].o);
				KNH_RETURN_void(ctx, sfp);
			}
			e = e->next;
		}

		/* add newentry */ {
			e = new_hashentry(ctx, o);
			e->hcode = hcode;
			knh_sfp_boxing(ctx, sfp+1);
			KNH_INITv(e->key, sfp[1].o);
			knh_sfp_boxing(ctx, sfp+2);
			KNH_INITv(e->value, sfp[2].o);
			e->next = DP(o)->array[h];
			DP(o)->array[h] = e;
			DP(o)->size++;
		}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ======================================================================== */
/* @method void HashMap.%k(OutputStream w, String m) */

void knh_HashMap__k(Ctx *ctx, knh_Hash_t *o, OutputStream *w, String *m)
{
	size_t pos = 0, c = 0;
	size_t max = (KNH_HASH_TABLESIZE / o->hashop->size) * DP(o)->tables_size;
	knh_putc(ctx, w, '{');
	while(pos < max) {
		knh_hashentry_t *e = knh_hashentry_at((knh_Hash_t*)o, pos);
		if(e != NULL) {
			if(c > 0) {
				knh_write_delim(ctx,w);
			}
			knh_format(ctx, w, METHODN__k, e->key, KNH_NULL);
			knh_putc(ctx, w, ':');
			knh_putc(ctx, w, ' ');
			knh_format(ctx, w, METHODN__k, e->value, KNH_NULL);
			c++;
		}
		pos++;
	}
	knh_putc(ctx, w, '}');
}

/* ------------------------------------------------------------------------ */
/* @method void HashMap.%dump(OutputStream w, String m) */

void knh_HashMap__dump(Ctx *ctx, HashMap *o, OutputStream *w, String *m)
{
	knh_HashMap__k(ctx, (knh_Hash_t*)o, w, m);
}

/* ======================================================================== */
/* [mapping] */

static
ITRNEXT knh_HashMap_var_next(Ctx *ctx, knh_sfp_t *sfp, int n)
{
	Iterator *it = sfp[0].it;
	knh_Hash_t *o = (knh_Hash_t*)DP(it)->source;
	KNH_ASSERT(IS_bHashMap(o));
	size_t pos = DP(it)->pos;
	size_t max = (KNH_HASH_TABLESIZE / o->hashop->size) * DP(o)->tables_size;
	while(pos < max) {
		knh_hashentry_t *e = knh_hashentry_at(o, pos);
		if(e != NULL) {
			DP(it)->pos = pos + 1;
			KNH_ITRNEXT(ctx, sfp, n, e->key);
		}
		pos++;
	}
	KNH_ITREND(ctx, sfp, n);
}

/* ------------------------------------------------------------------------ */
/* @map HashMap Iterator! @Final*/

MAPPER knh_HashMap_Iterator(Ctx *ctx, knh_sfp_t *sfp)
{
	HashMap *o = (HashMap*)sfp[0].o;
	KNH_MAPPED(ctx, sfp, new_Iterator(ctx, ctx->share->ClassTable[o->h.cid].p1, UP(o), knh_HashMap_var_next));
}

/* ------------------------------------------------------------------------ */
/* @method Any1.. HashMap.opItr() */

static METHOD knh__HashMap_opItr(Ctx *ctx, knh_sfp_t *sfp)
{
	HashMap *o = (HashMap*)sfp[0].o;
	KNH_RETURN(ctx, sfp, new_Iterator(ctx, ctx->share->ClassTable[o->h.cid].p1, UP(o), knh_HashMap_var_next));
}

///* ------------------------------------------------------------------------ */
//
//static
//Object* knh_HashMap_tuple2_next(Ctx *ctx, Iterator *it)
//{
//	HashMap *o = (HashMap*)DP(it)->source;
//	KNH_ASSERT(IS_bHashMap(o));
//	size_t pos = DP(it)->pos, capacity = knh_hashmapentry_capacity(ctx, o);
//	while(pos < capacity) {
//		knh_hashmapentry_t *e = knh_hashmapentry_at(o, pos);
//		if(e != NULL) {
//			DP(it)->pos = , pos+1);
//			return new_Tuple2(ctx, e->key, e->value);
//		}
//		pos++;
//	}
//	return KNH_VOID;
//}
//
///* ------------------------------------------------------------------------ */
///* @map HashMap Tuple2..! */
//
//Iterator* knh_HashMap_Tuple2__(Ctx *ctx, HashMap *o, Mapper *mpr)
//{
//	return new_Iterator(ctx, CLASS_Tuple2, o, knh_HashMap_tuple2_next);
//}
//
///* ------------------------------------------------------------------------ */

///* ======================================================================== */
///* [constructor] */
//
///* ------------------------------------------------------------------------ */
///* @method HashSet! HashSet.new(Int initialCapacity=0) */
//
//HashSet *knh_HashSet_new(Ctx *ctx, HashSet *b, size_t initialCapacity)
//{
//	if(initialCapacity > DP(b)->capacity) {
//		knh_HashSet_resize(ctx, b, (size_t)initialCapacity);
//	}
//	return b;
//}
//
///* ------------------------------------------------------------------------ */
///* ======================================================================== */
///* [method] */
//
///* ------------------------------------------------------------------------ */
///* @method Boolean HashSet.opHas(Any1 key) */
//
//
//knh_bool_t knh_HashSet_opHas(Ctx *ctx, HashSet *b, knh_hcode_t key, Object *keyobj)
//{
//	return (knh_HashSet_get(ctx, b, key, keyobj) != 0);
//}
//
///* ------------------------------------------------------------------------ */
///* ======================================================================== */
///* [mapping] */
//
///* ------------------------------------------------------------------------ */
///* @map HashSet Iterator! */
//
//Iterator* knh_HashSet_Iterator(Ctx *ctx, HashSet *o, Mapper *map)
//{
//	return new_Iterator(ctx, ctx->share->ClassTable[o->h.cid].p1, o, knh_HashMap_key_next);
//}
//
///* ======================================================================== */
///* [movabletext] */
//
///* @method void HashSet.%dump(OutputStream w, String m) */
//
//void knh_HashSet__dump(Ctx *ctx, HashSet *b, OutputStream *w, String *m)
//{
////	knh_hashsete_t *cur, *next;
////	size_t c = 0, i;
////	knh_fputc(ctx, w, '[');
////	for(i = 0; i < DP(b)->capacity; i++) {
////		cur = DP(b)->array[i];
////		while(cur != NULL) {
////			next = cur->next;
////			if(c > 0) knh_print_delim(ctx,w);
////			if(!knh_ucheck_todump(lv, c)) {
////				knh_print_dots(ctx, w);
////				break;
////			}
////			knh_Object__dump(ctx, cur->h.keyobj, w, lv+1);
////			if(cur->value != 1) knh_printf(ctx, w, "<%d>", cur->value);
////			c++;
////			cur = next;
////		}
////	}
////	knh_fputc(ctx, w, ']');
//}
//
//
///* ------------------------------------------------------------------------ */


#endif/*KNH_CC_METHODAPI*/

#ifdef __cplusplus
}
#endif
