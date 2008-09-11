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
#define _knh_LRUMap                      knh_HashMap_struct

#define _new_LRUMap(ctx,n)               new_HashMap(ctx,n)
#define _knh_LRUMap_get(ctx,b,kh,ko)     knh_HashMap_get(ctx,b,kh,ko)
#define _knh_LRUMap_set(ctx,b,kh,ko,v)   knh_HashMap_set(ctx,b,kh,ko,v)

	
#ifndef OLDHASH

/* ======================================================================== */
/* [structs] */

void
knh_HashMap_struct_init(Ctx *ctx, knh_HashMap_struct *b, int init, Object *cs)
{
	b->DBG_name = "HashMap";
	if(init > 0) {
		int i;
		b->table_size = init * 3 / 4 + 10;	
		b->table = (knh_hashmapentry_t*)KNH_MALLOC(ctx, sizeof(knh_hashmapentry_t) * b->table_size);
		b->ex_tables = NULL;
		b->ex_size = 0;
		b->ex_capacity = 0;
		for(i = 0; i < b->table_size; i++) {
			b->table[i].hcode = 0;
			b->table[i].key = NULL;
			b->table[i].value = NULL;
			b->table[i].next = (i == b->table_size - 1) ? NULL : &(b->table[i+1]);
		}
		b->unused = &(b->table[0]);
	
		b->capacity = init;
		b->array = (knh_hashmapentry_t**)KNH_MALLOC(ctx, sizeof(knh_hashmapentry_t*) * init);
		knh_bzero(b->array, sizeof(knh_hashmapentry_t*) * init);
	}
	else {
		b->table_size = 0;	
		b->table = NULL;
		b->ex_tables = NULL;
		b->ex_size = 0;
		b->ex_capacity = 0;
		b->unused = NULL;
	
		b->capacity = 0;
		b->array = NULL;
	}
	b->fcompareTo = knh_Object_compareTo;
}

/* ------------------------------------------------------------------------ */

knh_hashmapentry_t *new_hashmapentry(Ctx *ctx, HashMap *o)
{
	knh_hashmapentry_t *e = DP(o)->unused;
	if(e != NULL) {
		DP(o)->unused = e->next;
		return e;
	}
	else if(DP(o)->table_size == 0) {
		knh_HashMap_struct_init(ctx, DP(o), KNH_HASHMAP_INITSIZE, NULL);
		e = DP(o)->unused;
		DP(o)->unused = e->next;
		return e;
	}
	else {
		knh_HashMap_struct *b = DP(o);
		knh_hashmapentry_t *newtable = (knh_hashmapentry_t*)KNH_MALLOC(ctx, sizeof(knh_hashmapentry_t) * b->table_size);
		int i;
		for(i = 0; i < b->table_size; i++) {
			newtable[i].hcode = 0;
			newtable[i].key = NULL;
			newtable[i].value = NULL;
			newtable[i].next = (i == b->table_size - 1) ? NULL : &(newtable[i+1]);
		}
		e = &(newtable[0]);
		b->unused = &(newtable[1]);
		
		if(b->ex_size  == b->ex_capacity) {
			if(b->ex_capacity == 0) {
				b->ex_capacity = 8;
				b->ex_tables = (knh_hashmapentry_t**)KNH_MALLOC(ctx, sizeof(knh_hashmapentry_t*) * b->ex_capacity);
			}
			else {
				b->ex_capacity *= 2;
				knh_hashmapentry_t **newtbll = (knh_hashmapentry_t**)KNH_MALLOC(ctx, sizeof(knh_hashmapentry_t*) * b->ex_capacity);
				knh_memcpy(newtbll, b->ex_tables, sizeof(knh_hashmapentry_t*) * b->ex_size);
				KNH_FREE(b->ex_tables, sizeof(knh_hashmapentry_t*) * b->ex_size);
				b->ex_tables = newtbll;
			}
		}
		b->ex_tables[b->ex_size] = newtable;
		b->ex_size++;
		
		if(b->ex_size * (b->table_size+1) > b->capacity) {
			size_t nc = b->capacity * 2 + 1;
			knh_hashmapentry_t **newarray = (knh_hashmapentry_t**)KNH_MALLOC(ctx, sizeof(knh_hashmapentry_t*) * nc);
			knh_bzero(newarray, sizeof(knh_hashmapentry_t*) * nc);
			
			int i, j;
			knh_hashmapentry_t *t = b->table;
			for(i = 0; i < b->table_size; i++) {
				knh_uint_t h = t[i].hcode % nc;
				t[i].next = newarray[h];
				newarray[h] = &(t[i]);
			}
			for(j = 0; j < b->ex_size - 1; j++) {
				t = b->ex_tables[j];
				for(i = 0; i < b->table_size; i++) {
					knh_uint_t h = t[i].hcode % nc;
					t[i].next = newarray[h];
					newarray[h] = &(t[i]);
				}
			}
			KNH_FREE(b->array, sizeof(knh_hashmapentry_t*) * b->capacity);
			b->array = newarray;
			b->capacity = nc;
		}
		return e;
	}
}

/* ------------------------------------------------------------------------ */

size_t knh_hashmapentry_capacity(Ctx *ctx, HashMap *o)
{
	return DP(o)->table_size * (DP(o)->ex_size + 1);
}

/* ------------------------------------------------------------------------ */

knh_hashmapentry_t *knh_hashmapentry_at(HashMap *o, size_t n)
{
	KNH_ASSERT(DP(o)->table_size > 0);
	if(n < DP(o)->table_size) {
		if(DP(o)->table[n].key == NULL) {
			return NULL;
		}
		else {
			return &(DP(o)->table[n]);
		}
	}
	else {
		KNH_ASSERT(DP(o)->ex_tables != NULL);
		int i = (n % DP(o)->table_size);
		int j = (n / DP(o)->table_size) - 1;
//		DBG2_P("table_size=%d, j=%d, i=%d", DP(o)->table_size, j, i);
		knh_hashmapentry_t *e = DP(o)->ex_tables[j] + i;
		if(e->key == NULL) return NULL;
		return e;
	}
}

/* ------------------------------------------------------------------------ */

#define _knh_HashMap_struct_copy NULL

/* ------------------------------------------------------------------------ */

#define _knh_HashMap_struct_compare NULL

/* ------------------------------------------------------------------------ */

void
knh_HashMap_struct_traverse(Ctx *ctx, knh_HashMap_struct *b, f_traverse ftr)
{
	size_t i;
	for(i = 0; i < b->table_size; i++) {
		if(b->table[i].key != NULL) {
			ftr(ctx, b->table[i].key);
			ftr(ctx, b->table[i].value);
		}
	}
	if(b->ex_size > 0) {
		int j;
		for(j = 0; j < b->ex_size; j++) {
			knh_hashmapentry_t *t = b->ex_tables[j];
			for(i = 0; i < b->table_size; i++) {
				if(t[i].key != NULL) {
					ftr(ctx, t[i].key);
					ftr(ctx, t[i].value);
				}
			}
		}
	}
	if(IS_SWEEP(ftr)) {
		if(b->table != NULL) {
			KNH_FREE(b->table, sizeof(knh_hashmapentry_t) * b->table_size);
			b->table = NULL;
		}
		if(b->array != NULL) {
			KNH_FREE(b->array, sizeof(knh_hashmapentry_t*) * b->capacity);
			b->array = NULL;
		}
		if(b->ex_tables != NULL) {
			for(i = 0; i < b->ex_size; i++) {
				KNH_FREE(b->ex_tables[i], sizeof(knh_hashmapentry_t) * b->table_size);
			}
			KNH_FREE(b->ex_tables, sizeof(knh_hashmapentry_t*) * b->ex_capacity);
			b->ex_tables = NULL;
		}
	}
}

/* ======================================================================== */
/* [constructors] */

HashMap* new_HashMap(Ctx *ctx, char *name, size_t capacity)
{
	HashMap* o = 
		(HashMap*)new_Object_malloc(ctx, FLAG_HashMap, CLASS_HashMap, sizeof(knh_HashMap_struct));
	if(capacity == 0) capacity = KNH_HASHMAP_INITSIZE;
	knh_HashMap_struct_init(ctx, DP(o), capacity, NULL);
	if(name != NULL) {
		DP(o)->DBG_name = name;
	}
	return o;
}

/* ======================================================================== */
/* [methods] */

Object *knh_HashMap_get__hcode(Ctx *ctx, HashMap *o, knh_hcode_t hcode)
{
	knh_uint_t h = hcode % DP(o)->capacity;
	knh_hashmapentry_t *cur = DP(o)->array[h];
	while(cur != NULL) {
		if(cur->hcode == hcode) {
			return cur->value;
		}
		cur = cur->next;
	}
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

void knh_HashMap_set__hcode(Ctx *ctx, HashMap *o, knh_hcode_t hcode, Any *value)
{
	knh_uint_t h = hcode % DP(o)->capacity;
	knh_hashmapentry_t *cur = DP(o)->array[h];
	while(cur != NULL) {
		if(cur->hcode == hcode) {
			KNH_SETv(ctx, cur->value, value);
			return;
		}
		cur = cur->next;
	}
	cur = new_hashmapentry(ctx, o);
	cur->hcode = hcode;
	KNH_INITv(cur->key, KNH_NULL);
	KNH_INITv(cur->value, value);
	cur->next = DP(o)->array[h];
	DP(o)->array[h] = cur;
	DP(o)->size++;
}

/* ------------------------------------------------------------------------ */

void knh_HashMap_remove__hcode(Ctx *ctx, HashMap *o, knh_hcode_t hcode)
{
	knh_uint_t h = hcode % DP(o)->capacity;
	knh_hashmapentry_t *cur = DP(o)->array[h];
	knh_hashmapentry_t **prev_next = &(DP(o)->array[h]);
	while(cur != NULL) {
		if(cur->hcode == hcode) {
			prev_next[0] = cur->next;
			cur->next = DP(o)->unused;
			DP(o)->unused = cur;
			cur->hcode = 0;
			cur->key = NULL;
			cur->value = NULL;
			DP(o)->size--;
			return ;
		}
		prev_next = &(cur->next);
		cur = cur->next;
	}
}

/* ------------------------------------------------------------------------ */
/* @method void HashMap.clear() */

void knh_HashMap_clear(Ctx *ctx, HashMap *o)
{
	int init = DP(o)->capacity;
	knh_HashMap_struct_traverse(ctx, DP(o), knh_Object_RCsweep);
	knh_HashMap_struct_init(ctx, DP(o), init, NULL);
}

#else

///* ======================================================================== */
///* [hashmape] */
//
//INLINE
//knh_hashmape_t *knh_HashMape_new(Ctx *ctx, knh_hcode_t key, Object *kobj, Object *value) 
//{
//	knh_hashmape_t *cur = (knh_hashmape_t*)KNH_MALLOC(ctx, sizeof(knh_hashmape_t));
//	cur->h.key = key;
//	if(kobj == NULL) kobj = KNH_NULL;
//	KNH_INITv(cur->h.keyobj, kobj);
//	KNH_INITv(cur->value, value);
//	cur->next = NULL;
//	return cur;
//}
//
///* ------------------------------------------------------------------------ */
//
//INLINE
//void knh_HashMape_traverse(Ctx *ctx, knh_hashmape_t *cur, f_traverse gc)
//{
//	gc(ctx, cur->h.keyobj);
//	gc(ctx, cur->value);
//	if(IS_SWEEP(gc)) {
//		KNH_FREE(cur, sizeof(knh_hashmape_t));
//	}
//}
//
///* ======================================================================== */
///* [structs] */
//
//void
//knh_HashMap_struct_init(Ctx *ctx, knh_HashMap_struct *b, int init, Object *cs)
//{
//	if(init == 0) init = KNH_HASHMAP_INITSIZE; 
//	b->capacity = KNH_MAX(13, init);
//	b->factor   = KNH_HASHMAP_INITFACTOR;
//	b->size = 0;
//	b->array = (knh_hashmape_t**)KNH_MALLOC(ctx, sizeof(knh_hashmape_t*) * b->capacity);
//	knh_bzero(b->array, sizeof(knh_hashmape_t*) * b->capacity);
//}
//
///* ------------------------------------------------------------------------ */
//
//void
//knh_HashMap_struct_copy(Ctx *ctx, knh_HashMap_struct *b1, knh_HashMap_struct *b2)
//{
//	TODO();
//}
//
///* ------------------------------------------------------------------------ */
//
//#define _knh_HashMap_struct_compare NULL
//
///* ------------------------------------------------------------------------ */
//
//void
//knh_HashMap_struct_traverse(Ctx *ctx, knh_HashMap_struct *b, f_traverse gc)
//{
//	knh_hashmape_t *cur, *next;
//	size_t i;
//	for(i = 0; i < b->capacity; i++) {
//		cur = b->array[i];
//		while(cur != NULL) {
//			next = cur->next;
//			knh_HashMape_traverse(ctx, cur, gc);
//			cur = next;
//		}
//	}
//	if(IS_SWEEP(gc)) {
//		KNH_FREE(b->array, sizeof(knh_hashmape_t*) * b->capacity);
//	}
//}
//
///* ======================================================================== */
///* [constructors] */
//
//HashMap* new_HashMap(Ctx *ctx, size_t capacity)
//{
//	HashMap* o = 
//		(HashMap*)new_Object__RAW(ctx, FLAG_HashMap, CLASS_HashMap, sizeof(knh_HashMap_struct));
//	knh_HashMap_struct_init(ctx, DP(o), capacity, NULL);
//	return o;
//}
//
//
///* ======================================================================== */
///* [methods] */
//
///* @method Any2 HashMap.get(Any1 key) */
//
//Object *knh_HashMap_get(Ctx *ctx, HashMap *b, knh_hcode_t key, Any *kobj)
//{
//	knh_uint_t h = key % DP(b)->capacity;
//	knh_hashmape_t *cur = DP(b)->array[h];
//	while(cur != NULL) {
//		if(cur->h.key == key) {
//			if(kobj == NULL) {
//				return cur->value;
//			}
//			if(knh_Object_equals(kobj, cur->h.keyobj)) {
//				return cur->value;
//			}
//		}
//		cur = cur->next;
//	}
//	return KNH_NULL;
//}
//
///* ------------------------------------------------------------------------ */
//
//Object *knh_HashMap_get__b(HashMap *b, knh_bytes_t kv)  
//{
//	knh_hcode_t key = knh_bytes_hcode(kv);
//	knh_uint_t h =  key % DP(b)->capacity;
//	knh_hashmape_t *cur = DP(b)->array[h];
//	
//	while(cur != NULL) {
//		if(cur->h.key == key) {
//			if(IS_bString(cur->h.keyobj) && knh_String_equals((String*)cur->h.keyobj, kv)) {
//				return cur->value;
//			}
//		}
//		cur = cur->next;
//	}
//	return KNH_NULL;
//}
//
///* ------------------------------------------------------------------------ */
//
//void knh_HashMap_rehash(Ctx *ctx, HashMap *b)
//{
//	if(((float)DP(b)->size / DP(b)->capacity) < DP(b)->factor) {
//		return ;
//	}
//	knh_HashMap_resize(ctx, b, DP(b)->capacity * 2 + 1);
//}
//
///* ------------------------------------------------------------------------ */
//
//void knh_HashMap_resize(Ctx *ctx, HashMap *b, size_t nc)
//{
//	size_t i, nh;
//	//DEBUG_RESIZE(b, DP(b)->array, DP(b)->capacity, nc);
//	knh_hashmape_t **na = (knh_hashmape_t**)KNH_MALLOC(ctx, sizeof(knh_hashmape_t*) * nc);	
//	for(i = 0; i < nc; i++) na[i] = NULL;
//
//	knh_hashmape_t *cur, *next;
//	for(i = 0; i < DP(b)->capacity; i++) {
//		cur = DP(b)->array[i];
//		while(cur != NULL) {
//			next = cur->next; 
//			nh = cur->h.key % nc;
//			cur->next = na[nh];
//			na[nh] = cur;  /* push top */
//			cur = next;
//		}	
//	}
//	KNH_FREE(DP(b)->array, sizeof(knh_hashmape_t*) * DP(b)->capacity);
//	DP(b)->array = na;
//	DP(b)->capacity = nc;
//}
//
///* ------------------------------------------------------------------------ */
///* @method void HashMap.set(Any1 key, Any2 value) */
//
//void knh_HashMap_set(Ctx *ctx, HashMap *b, knh_hcode_t key, Any *kobj, Any *value)
//{
//	KNH_ASSERT(IS_HashMap(b));
//	if(((float)DP(b)->size / DP(b)->capacity) > DP(b)->factor) {
//		knh_HashMap_rehash(ctx, b);
//	}
//
//	knh_uint_t h = key % DP(b)->capacity;
//	knh_hashmape_t *cur = DP(b)->array[h];
//
//	while(cur != NULL) {
//		if(cur->h.key == key) {
//			if(kobj == NULL) {
//				KNH_ASSERT(IS_NULL(cur->h.keyobj));
//				KNH_SETv(ctx, cur->value, value);
//				return;
//			}
//			if(knh_Object_equals(kobj, cur->h.keyobj)) {
//				KNH_SETv(ctx, cur->h.keyobj, kobj);
//				KNH_SETv(ctx, cur->value, value);
//				return;
//			}
//		}
//		cur = cur->next;
//	}
//	cur = knh_HashMape_new(ctx, key, kobj, value);
//	cur->next = DP(b)->array[h];
//	DP(b)->array[h] = cur;
//	DP(b)->size++;
//}
//
//#define _knh_HashMap_put(ctx,b,h,k,v) knh_HashMap_set(ctx,b,h,k,v)
//
///* ------------------------------------------------------------------------ */
///* @method void HashMap.remove(Any1 key) */
//
//void knh_HashMap_remove(Ctx *ctx, HashMap *b, knh_hcode_t key, Any *kobj)
//{
//	knh_uint_t h = key % DP(b)->capacity;
//	knh_hashmape_t **prev, *cur;
//	
//	prev = &DP(b)->array[h];
//	cur = *prev;
//	while(cur != NULL) {
//		if(cur->h.key == key) {
//			if(kobj == NULL || knh_Object_equals(kobj, cur->h.keyobj)) {
//				*prev = cur->next;
//				knh_HashMape_traverse(ctx, cur, knh_Object_RCsweep);
//				DP(b)->size--;
//				return ;
//			}
//		}
//		prev = &cur->next;
//		cur = *prev;
//	}
//}

#endif

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
