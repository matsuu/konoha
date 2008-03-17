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

#define THIS(b)  DEBUG_THIS(b, STRUCT_HashSet)

/* ======================================================================== */
/* [hashsete] */

INLINE
knh_hashsete_t *knh_HashSete_new(Ctx *ctx, knh_hcode_t key, Object *keyobj, knh_uint_t value) 
{
	knh_hashsete_t *cur = (knh_hashsete_t*)knh_malloc(ctx, sizeof(knh_hashsete_t));
	cur->h.key = key;
	if(keyobj == NULL) keyobj = KNH_NULL;
	KNH_INITv(cur->h.keyobj, keyobj);
	cur->value = value;
	cur->next = NULL;
	return cur;
}

/* ------------------------------------------------------------------------ */

INLINE
void knh_HashSete_traverse(Ctx *ctx, knh_hashsete_t *cur, f_gc gc)
{
	gc(ctx, cur->h.keyobj);
	if(IS_SWEEP(gc)) {
		knh_free(cur, sizeof(knh_hashsete_t));
	}
}

/* ======================================================================== */
/* [structs] */

void
knh_HashSet_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	HashSet *b =  (HashSet*)s1;
	if(init == 0) init = KNH_HASHMAP_INITSIZE; 
	b->capacity = KNH_MAX(13, init);
	b->factor   = KNH_HASHMAP_INITFACTOR;
	b->size = 0;
	b->array = (knh_hashsete_t**)knh_malloc(ctx, sizeof(knh_hashsete_t*) * b->capacity);
	knh_bzero(b->array, sizeof(knh_hashsete_t*) * b->capacity);
}

/* ------------------------------------------------------------------------ */

void
knh_HashSet_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
	//HashSet *b =  (HashSet*)s1;
	//HashSet *b2 = (HashSet*)s2;
	TODO();	
	//b2->flag  =     b->flag;
	//KNH_INITv(b2->name, b->name);
}

/* ------------------------------------------------------------------------ */

#define _knh_HashSet_struct_compare NULL

/* ------------------------------------------------------------------------ */

void
knh_HashSet_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	HashSet *b = (HashSet*)s;

	knh_hashsete_t *cur, *next;
	size_t i;
	for(i = 0; i < b->capacity; i++) {
		cur = b->array[i];
		while(cur != NULL) {
			next = cur->next;
			knh_HashSete_traverse(ctx, cur, gc);
			cur = next;
		}
	}
	if(IS_SWEEP(gc)) {
		knh_free(b->array, sizeof(knh_hashsete_t*) * b->capacity);
	}
}

/* ======================================================================== */
/* [constructors] */

HashSet* new_HashSet(Ctx *ctx, size_t capacity)
{
	HashSet* b = 
		(HashSet*)knh_Object_malloc0(ctx, KNH_FLAG_HashSet, CLASS_HashSet, sizeof(HashSet));
	knh_HashSet_struct_init(ctx, (Struct*)b, capacity, NULL);
	return b;
}

/* ------------------------------------------------------------------------ */

/* @method HashSet! HashSet.new(Int initialCapacity=0) */

HashSet *knh_HashSet_new(Ctx *ctx, HashSet *b, size_t initialCapacity)
{
	if(initialCapacity > b->capacity) {
		knh_HashSet_resize(ctx, b, (size_t)initialCapacity);
	}
	return b;
}

/* ======================================================================== */
/* [wrappers] */

void knh_HashSet_rehash(Ctx *ctx, HashSet *b)
{
	knh_HashMap_rehash(ctx, (HashMap*)b);
}

/* ------------------------------------------------------------------------ */

void knh_HashSet_resize(Ctx *ctx, HashSet *b, size_t nc)
{
	knh_HashMap_resize(ctx, (HashMap*)b, nc);
}

/* ======================================================================== */
/* [methods] */

/* @method Int! HashSet.get(Any key); */

knh_uint_t knh_HashSet_get(Ctx *ctx, HashSet *b, knh_hcode_t key, Object *keyobj)
{
	knh_uint_t h = key % b->capacity;
	knh_hashsete_t *cur = b->array[h];
	
	while(cur != NULL) {
		if(cur->h.key == key) {
			if(keyobj == NULL || knh_Object_equals(ctx, keyobj, cur->h.keyobj)) {
				return cur->value;
			}
		}
		cur = cur->next;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

/* @method Bool HashSet.opIn(Any key) */

INLINE
knh_bool_t knh_HashSet_opIn(Ctx *ctx, HashSet *b, knh_hcode_t key, Object *keyobj)
{
	return (knh_HashSet_get(ctx, b, key, keyobj) != 0);
}

/* ------------------------------------------------------------------------ */

knh_uint_t knh_HashSet_get__b(Ctx *ctx, HashSet *b, knh_bytes_t kv)
{

	knh_hcode_t key = knh_bytes_hcode(kv);
	knh_uint_t h =  key % b->capacity;
	knh_hashsete_t *cur = b->array[h];

	while(cur != NULL) {
		if(cur->h.key == key && cur->h.keyobj != NULL) {
			if(STRUCT_IS_String(cur->h.keyobj) && knh_String_equals(cur->h.keyobj, kv)) {
				return cur->value;
			}
		}
		cur = cur->next;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

/* @method void HashSet.set(Any key, Int! value); */

#define _knh_HashSet_put(ctx,b,h,k,v) knh_HashSet_set(ctx,b,h,k,v)


void knh_HashSet_set(Ctx *ctx, HashSet *b, knh_hcode_t key, Any *keyobj, knh_uint_t value)
{
	if(((float)b->size / b->capacity) > b->factor) {
		knh_HashSet_rehash(ctx, b);
	}

	knh_uint_t h = key % b->capacity;
	knh_hashsete_t *cur = b->array[h];

	while(cur != NULL) {
		if(cur->h.key == key) {
			if(keyobj == NULL) {
				KNH_ASSERT(IS_NULL(cur->h.keyobj));
				cur->value = value;
				return;
			}else if(knh_Object_equals(ctx, keyobj, cur->h.keyobj)) {
				KNH_SETv(ctx, cur->h.keyobj, keyobj);
				cur->value = value;
				return;
			}
		}
		cur = cur->next;
	}
	cur = knh_HashSete_new(ctx, key, keyobj, value);
	cur->next = b->array[h];
	b->array[h] = cur;
	b->size++;
}

/* ------------------------------------------------------------------------ */

/* @method void HashSet.add(Any key) */

void knh_HashSet_add(Ctx *ctx, HashSet *b, knh_hcode_t key, Any *keyobj)
{
	if(((float)b->size / b->capacity) > b->factor) {
		knh_HashSet_rehash(ctx, b);
	}

	knh_uint_t h = key % b->capacity;
	knh_hashsete_t *cur = b->array[h];

	while(cur != NULL) {
		if(cur->h.key == key) {
			if(keyobj == NULL) {
				KNH_ASSERT(cur->h.keyobj == NULL);
			}else if(knh_Object_equals(ctx, keyobj, cur->h.keyobj)) {
				KNH_SETv(ctx, cur->h.keyobj, keyobj);
			}
			cur->value++;
			return;
		}
		cur = cur->next;
	}
	cur = knh_HashSete_new(ctx, key, keyobj, 1);
	cur->next = b->array[h];
	b->array[h] = cur;
	b->size++;
}

/* ------------------------------------------------------------------------ */

/* @method void HashSet.remove(Any key) */

void knh_HashSet_remove(Ctx *ctx, HashSet *b, knh_hcode_t key, Any *keyobj)
{
	knh_uint_t h = key % b->capacity;
	knh_hashsete_t **prev, *cur;
	
	prev = &b->array[h];
	cur = *prev;
	while(cur != NULL) {
		if(cur->h.key == key) {
			if(keyobj == NULL || knh_Object_equals(ctx, keyobj, cur->h.keyobj)) {
				*prev = cur->next;
				knh_HashSete_traverse(ctx, cur, knh_sweep);
				b->size--;
				return ;
			}
		}
		prev = &cur->next;
		cur = *prev;
	}
}

/* ======================================================================== */
/* [mappings] */

/* @map HashSet Iterator! */


Object* knh_HashSet_Iterator(Ctx *ctx, Object *self, MapMap *map)
{
	return new_Iterator(ctx, CLASS_Any, self, knh_HashSet_key_next);
}

/* ======================================================================== */
/* [movabletext] */

/* @method void HashSet.%dump(OutputStream w, Any m) */

void knh_HashSet__dump(Ctx *ctx, HashSet *b, OutputStream *w, Any *m)
{
//	knh_hashsete_t *cur, *next;
//	size_t c = 0, i;
//	knh_fputc(ctx, w, '[');
//	for(i = 0; i < b->capacity; i++) {
//		cur = b->array[i];
//		while(cur != NULL) {
//			next = cur->next;
//			if(c > 0) knh_print_delim(ctx,w);
//			if(!knh_ucheck_todump(lv, c)) {
//				knh_print_dots(ctx, w);
//				break;
//			}
//			knh_Object__dump(ctx, cur->h.keyobj, w, lv+1);
//			if(cur->value != 1) knh_printf(ctx, w, "<%d>", cur->value);
//			c++;
//			cur = next;
//		}
//	}
//	knh_fputc(ctx, w, ']');
}


#ifdef __cplusplus
}
#endif
