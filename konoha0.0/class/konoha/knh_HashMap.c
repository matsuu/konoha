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

/* ------------------------------------------------------------------------ */

#define _LRUMap                          HashMap
#define _knh_LRUMap                      knh_HashMap

#define _new_LRUMap(ctx,n)               new_HashMap(ctx,n)
#define _knh_LRUMap_get(ctx,b,kh,ko)     knh_HashMap_get(ctx,b,kh,ko)
#define _knh_LRUMap_set(ctx,b,kh,ko,v)   knh_HashMap_set(ctx,b,kh,ko,v)

/* ======================================================================== */
/* [hashmape] */

INLINE
knh_hashmape_t *knh_HashMape_new(Ctx *ctx, knh_hcode_t key, Object *kobj, Object *value) 
{
	knh_hashmape_t *cur = (knh_hashmape_t*)knh_malloc(ctx, sizeof(knh_hashmape_t));
	cur->h.key = key;
	if(kobj == NULL) kobj = KNH_NULL;
	KNH_INITv(cur->h.keyobj, kobj);
	KNH_INITv(cur->value, value);
	cur->next = NULL;
	return cur;
}

/* ------------------------------------------------------------------------ */

INLINE
void knh_HashMape_traverse(Ctx *ctx, knh_hashmape_t *cur, f_gc gc)
{
	gc(ctx, cur->h.keyobj);
	gc(ctx, cur->value);
	if(IS_SWEEP(gc)) {
		knh_free(cur, sizeof(knh_hashmape_t));
	}
}

/* ======================================================================== */
/* [structs] */

void
knh_HashMap_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	HashMap *b =  (HashMap*)s1;
	if(init == 0) init = KNH_HASHMAP_INITSIZE; 
	b->capacity = KNH_MAX(13, init);
	b->factor   = KNH_HASHMAP_INITFACTOR;
	b->size = 0;
	b->array = (knh_hashmape_t**)knh_malloc(ctx, sizeof(knh_hashmape_t*) * b->capacity);
	knh_bzero(b->array, sizeof(knh_hashmape_t*) * b->capacity);
}

/* ------------------------------------------------------------------------ */

void
knh_HashMap_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
	//HashMap *b =  (HashMap*)s1;
	//HashMap *b2 = (HashMap*)s2;
	TODO();
	//b2->flag  =     b->flag;
	//KNH_INITv(b2->name, b->name);
}

/* ------------------------------------------------------------------------ */

#define _knh_HashMap_struct_compare NULL

/* ------------------------------------------------------------------------ */

void
knh_HashMap_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	HashMap *b = (HashMap*)s;

	knh_hashmape_t *cur, *next;
	size_t i;
	for(i = 0; i < b->capacity; i++) {
		cur = b->array[i];
		while(cur != NULL) {
			next = cur->next;
			knh_HashMape_traverse(ctx, cur, gc);
			cur = next;
		}
	}
	if(IS_SWEEP(gc)) {
		knh_free(b->array, sizeof(knh_hashmape_t*) * b->capacity);
	}
}

/* ======================================================================== */
/* [constructors] */

HashMap* new_HashMap(Ctx *ctx, size_t capacity)
{
	HashMap* b = 
		(HashMap*)knh_Object_malloc0(ctx, KNH_FLAG_HashMap, CLASS_HashMap, sizeof(HashMap));
	knh_HashMap_struct_init(ctx, (Struct*)b, capacity, NULL);
	return b;
}

/* ------------------------------------------------------------------------ */

/* @method HashMap! HashMap.new(Int initialCapacity=0) */

INLINE
HashMap *knh_HashMap_new(Ctx *ctx, HashMap *b, size_t initialCapacity)
{
	if(initialCapacity > b->capacity) {
		knh_HashMap_resize(ctx, b, (size_t)initialCapacity);
	}
	return b;
}

/* ------------------------------------------------------------------------ */

/* @method[VARARGS] HashMap! HashMap.new::init(Any value) */

HashMap* knh_HashMap_new__init(Ctx *ctx, HashMap *b, knh_vargc_t ac, Object **a)
{
	knh_int_t i;
	for(i = 0; i < ac; i += 2) {
		if(IS_NULL(a[i]) || IS_NULL(a[i+1])) break;
		knh_HashMap_set(ctx, b, knh_Object_hcode(ctx,a[i]), a[i], a[i+1]);
	}
	return b;
}

/* ======================================================================== */
/* [methods] */

/* @method Any HashMap.get(Any key) */

Any *knh_HashMap_get(Ctx *ctx, HashMap *b, knh_hcode_t key, Any *kobj)
{
	knh_uint_t h = key % b->capacity;
	knh_hashmape_t *cur = b->array[h];
	while(cur != NULL) {
		if(cur->h.key == key) {
			if(kobj == NULL) {
				return cur->value;
			}
			if(knh_Object_equals(ctx, kobj, cur->h.keyobj)) {
				return cur->value;
			}
		}
		cur = cur->next;
	}
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

Object *knh_HashMap_get__b(HashMap *b, knh_bytes_t kv)  
{
	knh_hcode_t key = knh_bytes_hcode(kv);
	knh_uint_t h =  key % b->capacity;
	knh_hashmape_t *cur = b->array[h];
	
	while(cur != NULL) {
		if(cur->h.key == key) {
			if(STRUCT_IS_String(cur->h.keyobj) && knh_String_equals(cur->h.keyobj, kv)) {
				return cur->value;
			}
		}
		cur = cur->next;
	}
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

void knh_HashMap_rehash(Ctx *ctx, HashMap *b)
{
	if(((float)b->size / b->capacity) < b->factor) {
		return ;
	}
	knh_HashMap_resize(ctx, b, b->capacity * 2 + 1);
}

/* ------------------------------------------------------------------------ */

void knh_HashMap_resize(Ctx *ctx, HashMap *b, size_t nc)
{
	size_t i, nh;
	DEBUG_RESIZE(b, b->array, b->capacity, nc);
	knh_hashmape_t **na = (knh_hashmape_t**)knh_malloc(ctx, sizeof(knh_hashmape_t*) * nc);	
	for(i = 0; i < nc; i++) na[i] = NULL;

	knh_hashmape_t *cur, *next;
	for(i = 0; i < b->capacity; i++) {
		cur = b->array[i];
		while(cur != NULL) {
			next = cur->next; 
			nh = cur->h.key % nc;
			cur->next = na[nh];
			na[nh] = cur;  /* push top */
			cur = next;
		}	
	}
	knh_free(b->array, sizeof(knh_hashmape_t*) * b->capacity);
	b->array = na;
	b->capacity = nc;
}

/* ------------------------------------------------------------------------ */

/* @method void HashMap.set(Any! key, Any value) */

void knh_HashMap_set(Ctx *ctx, HashMap *b, knh_hcode_t key, Any *kobj, Any *value)
{
	DEBUG_ASSERT(IS_HashMap(b));
	if(((float)b->size / b->capacity) > b->factor) {
		knh_HashMap_rehash(ctx, b);
	}

	knh_uint_t h = key % b->capacity;
	knh_hashmape_t *cur = b->array[h];

	while(cur != NULL) {
		if(cur->h.key == key) {
			if(kobj == NULL) {
				KNH_ASSERT(cur->h.keyobj == NULL);
				KNH_SETv(ctx, cur->value, value);
				return;
			}
			if(knh_Object_equals(ctx, kobj, cur->h.keyobj)) {
				KNH_SETv(ctx, cur->h.keyobj, kobj);
				KNH_SETv(ctx, cur->value, value);
				return;
			}
		}
		cur = cur->next;
	}
	cur = knh_HashMape_new(ctx, key, kobj, value);
	cur->next = b->array[h];
	b->array[h] = cur;
	b->size++;
}

#define _knh_HashMap_put(ctx,b,h,k,v) knh_HashMap_set(ctx,b,h,k,v)

/* ------------------------------------------------------------------------ */

/* @method void HashMap.remove(Any key) */

void knh_HashMap_remove(Ctx *ctx, HashMap *b, knh_hcode_t key, Any *kobj)
{
	knh_uint_t h = key % b->capacity;
	knh_hashmape_t **prev, *cur;
	
	prev = &b->array[h];
	cur = *prev;
	while(cur != NULL) {
		if(cur->h.key == key) {
			if(kobj == NULL || knh_Object_equals(ctx, kobj, cur->h.keyobj)) {
				*prev = cur->next;
				knh_HashMape_traverse(ctx, cur, knh_sweep);
				b->size--;
				return ;
			}
		}
		prev = &cur->next;
		cur = *prev;
	}
}

/* ------------------------------------------------------------------------ */
/* @method Bool HashMap.opIn(Any key) */

INLINE
knh_bool_t knh_HashMap_opIn(Ctx *ctx, HashMap *b, knh_hcode_t key, Any *keyobj)
{
	if(keyobj != NULL && IS_NULL(keyobj)) return 0;
	return IS_NOTNULL(knh_HashMap_get(ctx, b, key, keyobj));
}

/* ======================================================================== */
/* [mappings] */

/* ======================================================================== */
/* [iterators] */

knh_hashmape_t *
knh_HashMape_next(Ctx *ctx, Iterator *it)
{
	HashMap *b = (HashMap *)knh_Iterator_source(it);
	knh_hashmape_t *cur = (knh_hashmape_t*)knh_Iterator_ref(it);
	if(cur != NULL) {
		knh_Iterator_setref(it, cur->next);
		return cur;
	}
	size_t pos = knh_Iterator_pos(it); 
	for(; pos < b->capacity; pos++) {
		cur = b->array[pos];
		if(cur != NULL) {
			knh_Iterator_setpos(it, pos+1);
			knh_Iterator_setref(it, cur->next);
			return cur;
		}
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

Object* knh_HashMap_key_next(Ctx *ctx, Iterator *it)
{
	knh_hashmape_t *cur = knh_HashMape_next(ctx, it);
	if(cur == NULL) return KNH_NULL;
	return cur->h.keyobj;
}

#define _knh_HashSet_key_next knh_HashMap_key_next

/* ------------------------------------------------------------------------ */

/* @method Iterator! HashMap.keys() */

Iterator *knh_HashMap_keys(Ctx *ctx, HashMap *b)
{
	return new_Iterator(ctx, CLASS_Any, b, knh_HashMap_key_next);
}

/* ------------------------------------------------------------------------ */

/* @map HashMap Iterator! */

Object* knh_HashMap_Iterator(Ctx *ctx, Object *self, MapMap *map)
{
	return new_Iterator(ctx, CLASS_Any, self, knh_HashMap_key_next);
}

///* ------------------------------------------------------------------------ */
//
//Object *knh_HashMap_tuple2_next(Ctx *ctx, Iterator *it) 
//{
//	knh_hashmape_t *cur = knh_HashMape_next(ctx, it);
//	if(cur == NULL) return KNH_NULL;
//	return knh_Tuple2_new(ctx, cur->h.keyobj, cur->value);
//}
//
///* ------------------------------------------------------------------------ */
//
///* @map HashMap Tuple2..! */
//
//
//Object* knh_HashMap_Tuple2__(Ctx *ctx, Object *self, MapMap *map)
//{
//	return new_Iterator(ctx, CLASS_Tuple2, self, knh_HashMap_tuple2_next);	
//}

/* ======================================================================== */
/* [movabletext] */

/* @method void HashMap.%dump(OutputStream w, Any m) */

void knh_HashMap__dump(Ctx *ctx, HashMap *b, OutputStream *w, Any *m)
{
//	knh_hashmape_t *cur, *next;
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
//			knh_Tuple2__dump(ctx, cur->h.keyobj, cur->value, w, lv+1);
//			c++;
//			cur = next;
//		}
//	}
//	knh_fputc(ctx, w, ']');
}


#ifdef __cplusplus
}
#endif
