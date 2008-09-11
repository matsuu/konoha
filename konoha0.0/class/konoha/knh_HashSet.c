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

#ifndef OLDHASH


/* ======================================================================== */
/* [structs] */

void
knh_HashSet_struct_init(Ctx *ctx, knh_HashSet_struct *b, int init, Object *cs)
{
	b->DBG_name = "HashSet";
	if(init > 0) {
		int i;
		b->table_size = init * 3 / 4 + 10;	
		b->table = (knh_hashsetentry_t*)KNH_MALLOC(ctx, sizeof(knh_hashsetentry_t) * b->table_size);
		b->ex_tables = NULL;
		b->ex_size = 0;
		b->ex_capacity = 0;
		for(i = 0; i < b->table_size; i++) {
			b->table[i].hcode = 0;
			b->table[i].key = NULL;
			b->table[i].value = 0;
			b->table[i].next = (i == b->table_size - 1) ? NULL : &(b->table[i+1]);
		}
		b->unused = &(b->table[0]);
	
		b->capacity = init;
		b->array = (knh_hashsetentry_t**)KNH_MALLOC(ctx, sizeof(knh_hashsetentry_t*) * init);
		knh_bzero(b->array, sizeof(knh_hashsetentry_t*) * init);
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

static
knh_hashsetentry_t *new_hashsetentry(Ctx *ctx, HashSet *o)
{
	knh_hashsetentry_t *e = DP(o)->unused;
	if(e != NULL) {
		DP(o)->unused = e->next;
		return e;
	}
	else if(DP(o)->table_size == 0) {
		knh_HashSet_struct_init(ctx, DP(o), KNH_HASHMAP_INITSIZE, NULL);
		e = DP(o)->unused;
		DP(o)->unused = e->next;
		return e;
	}
	else {
		knh_HashSet_struct *b = DP(o);
		knh_hashsetentry_t *newtable = (knh_hashsetentry_t*)KNH_MALLOC(ctx, sizeof(knh_hashsetentry_t) * b->table_size);
		int i;
		for(i = 0; i < b->table_size; i++) {
			newtable[i].hcode = 0;
			newtable[i].key = NULL;
			newtable[i].value = 0;
			newtable[i].next = (i == b->table_size - 1) ? NULL : &(newtable[i+1]);
		}
		e = &(newtable[0]);
		b->unused = &(newtable[1]);
		
		if(b->ex_size  == b->ex_capacity) {
			if(b->ex_capacity == 0) {
				b->ex_capacity = 8;
				b->ex_tables = (knh_hashsetentry_t**)KNH_MALLOC(ctx, sizeof(knh_hashsetentry_t*) * b->ex_capacity);
			}
			else {
				b->ex_capacity *= 2;
				knh_hashsetentry_t **newtbll = (knh_hashsetentry_t**)KNH_MALLOC(ctx, sizeof(knh_hashsetentry_t*) * b->ex_capacity);
				knh_memcpy(newtbll, b->ex_tables, sizeof(knh_hashsetentry_t*) * b->ex_size);
				KNH_FREE(b->ex_tables, sizeof(knh_hashsetentry_t*) * b->ex_size);
				b->ex_tables = newtbll;
			}
		}
		b->ex_tables[b->ex_size] = newtable;
		b->ex_size++;
		
		if(b->ex_size * (b->table_size+1) > b->capacity) {
			size_t nc = b->capacity * 2 + 1;
			knh_hashsetentry_t **newarray = (knh_hashsetentry_t**)KNH_MALLOC(ctx, sizeof(knh_hashsetentry_t*) * nc);
			knh_bzero(newarray, sizeof(knh_hashsetentry_t*) * nc);
			
			int i, j;
			knh_hashsetentry_t *t = b->table;
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
			KNH_FREE(b->array, sizeof(knh_hashsetentry_t*) * b->capacity);
			b->array = newarray;
			b->capacity = nc;
		}
		return e;
	}
}

/* ------------------------------------------------------------------------ */

#define _knh_HashSet_struct_copy NULL

/* ------------------------------------------------------------------------ */

#define _knh_HashSet_struct_compare NULL

/* ------------------------------------------------------------------------ */

void
knh_HashSet_struct_traverse(Ctx *ctx, knh_HashSet_struct *b, f_traverse ftr)
{
	size_t i;
	for(i = 0; i < b->table_size; i++) {
		if(b->table[i].key != NULL) {
			ftr(ctx, b->table[i].key);
		}
	}
	if(b->ex_size > 0) {
		int j;
		for(j = 0; j < b->ex_size; j++) {
			knh_hashsetentry_t *t = b->ex_tables[j];
			for(i = 0; i < b->table_size; i++) {
				if(t[i].key != NULL) {
					ftr(ctx, t[i].key);
				}
			}
		}
	}
	if(IS_SWEEP(ftr)) {
		if(b->table != NULL) {
			KNH_FREE(b->table, sizeof(knh_hashsetentry_t) * b->table_size);
			b->table = NULL;
		}
		if(b->array != NULL) {
			KNH_FREE(b->array, sizeof(knh_hashsetentry_t*) * b->capacity);
			b->array = NULL;
		}
		if(b->ex_tables != NULL) {
			for(i = 0; i < b->ex_size; i++) {
				KNH_FREE(b->ex_tables[i], sizeof(knh_hashsetentry_t) * b->table_size);
			}
			KNH_FREE(b->ex_tables, sizeof(knh_hashmapentry_t*) * b->ex_capacity);
			b->ex_tables = NULL;
		}
	}
}

/* ======================================================================== */
/* [constructors] */

HashSet* new_HashSet(Ctx *ctx, char *name, size_t capacity)
{
	HashSet* o = 
		(HashSet*)new_Object_malloc(ctx, FLAG_HashSet, CLASS_HashSet, sizeof(knh_HashSet_struct));
	if(capacity == 0) capacity = KNH_HASHMAP_INITSIZE;
	knh_HashSet_struct_init(ctx, DP(o), capacity, NULL);
	if(name != NULL) {
		DP(o)->DBG_name = name;
	}
	return o;
}

/* ======================================================================== */
/* [methods] */

knh_uint_t knh_HashSet_get__hcode(Ctx *ctx, HashSet *o, knh_hcode_t hcode)
{
	knh_uint_t h = hcode % DP(o)->capacity;
	knh_hashsetentry_t *cur = DP(o)->array[h];
	while(cur != NULL) {
		if(cur->hcode == hcode) {
			return cur->value;
		}
		cur = cur->next;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

void knh_HashSet_set__hcode(Ctx *ctx, HashSet *o, knh_hcode_t hcode, knh_uint_t value)
{
	knh_uint_t h = hcode % DP(o)->capacity;
	knh_hashsetentry_t *cur = DP(o)->array[h];
	while(cur != NULL) {
		if(cur->hcode == hcode) {
			cur->value = value;
			return ;
		}
		cur = cur->next;
	}
	cur = new_hashsetentry(ctx, o);
	cur->hcode = hcode;
	KNH_INITv(cur->key, KNH_NULL);
	cur->value = value;
	cur->next = DP(o)->array[h];
	DP(o)->array[h] = cur;
	DP(o)->size++;
}

/* ------------------------------------------------------------------------ */

void knh_HashSet_add__hcode(Ctx *ctx, HashSet *o, knh_hcode_t hcode)
{
	knh_uint_t h = hcode % DP(o)->capacity;
	knh_hashsetentry_t *cur = DP(o)->array[h];
	while(cur != NULL) {
		if(cur->hcode == hcode) {
			cur->value++;
			return ;
		}
		cur = cur->next;
	}
	cur = new_hashsetentry(ctx, o);
	cur->hcode = hcode;
	KNH_INITv(cur->key, KNH_NULL);
	cur->value = 1;
	cur->next = DP(o)->array[h];
	DP(o)->array[h] = cur;
	DP(o)->size++;
}

/* ------------------------------------------------------------------------ */

void knh_HashSet_remove__hcode(Ctx *ctx, HashSet *o, knh_hcode_t hcode)
{
	knh_uint_t h = hcode % DP(o)->capacity;
	knh_hashsetentry_t *cur = DP(o)->array[h];
	knh_hashsetentry_t **prev_next = &(DP(o)->array[h]);
	while(cur != NULL) {
		if(cur->hcode == hcode) {
			prev_next[0] = cur->next;
			cur->next = DP(o)->unused;
			DP(o)->unused = cur;
			cur->hcode = 0;
			cur->key = NULL;
			cur->value = 0;
			DP(o)->size--;
			return ;
		}
		prev_next = &(cur->next);
		cur = cur->next;
	}
}

/* ------------------------------------------------------------------------ */

void knh_HashSet_clear(Ctx *ctx, HashSet *o)
{
	int init = DP(o)->capacity;
	knh_HashSet_struct_traverse(ctx, DP(o), knh_Object_RCsweep);
	knh_HashSet_struct_init(ctx, DP(o), init, NULL);
}

#else

///* ======================================================================== */
///* [hashsete] */
//
//INLINE
//knh_hashsete_t *knh_HashSete_new(Ctx *ctx, knh_hcode_t key, Object *keyobj, knh_uint_t value) 
//{
//	knh_hashsete_t *cur = (knh_hashsete_t*)KNH_MALLOC(ctx, sizeof(knh_hashsete_t));
//	cur->h.key = key;
//	if(keyobj == NULL) keyobj = KNH_NULL;
//	KNH_INITv(cur->h.keyobj, keyobj);
//	cur->value = value;
//	cur->next = NULL;
//	return cur;
//}
//
///* ------------------------------------------------------------------------ */
//
//INLINE
//void knh_HashSete_traverse(Ctx *ctx, knh_hashsete_t *cur, f_traverse gc)
//{
//	gc(ctx, cur->h.keyobj);
//	if(IS_SWEEP(gc)) {
//		KNH_FREE(cur, sizeof(knh_hashsete_t));
//	}
//}
//
///* ======================================================================== */
///* [structs] */
//
//void
//knh_HashSet_struct_init(Ctx *ctx, knh_HashSet_struct *b, int init, Object *cs)
//{
//	if(init == 0) init = KNH_HASHMAP_INITSIZE; 
//	b->capacity = KNH_MAX(13, init);
//	b->factor   = KNH_HASHMAP_INITFACTOR;
//	b->size = 0;
//	b->array = (knh_hashsete_t**)KNH_MALLOC(ctx, sizeof(knh_hashsete_t*) * b->capacity);
//	knh_bzero(b->array, sizeof(knh_hashsete_t*) * b->capacity);
//}
//
///* ------------------------------------------------------------------------ */
//
//void
//knh_HashSet_struct_copy(Ctx *ctx, knh_HashSet_struct *b, knh_HashSet_struct *b2)
//{
//	TODO();	
//}
//
///* ------------------------------------------------------------------------ */
//
//#define _knh_HashSet_struct_compare NULL
//
///* ------------------------------------------------------------------------ */
//
//void
//knh_HashSet_struct_traverse(Ctx *ctx, knh_HashSet_struct *b, f_traverse gc)
//{
//	knh_hashsete_t *cur, *next;
//	size_t i;
//	for(i = 0; i < b->capacity; i++) {
//		cur = b->array[i];
//		while(cur != NULL) {
//			next = cur->next;
//			knh_HashSete_traverse(ctx, cur, gc);
//			cur = next;
//		}
//	}
//	if(IS_SWEEP(gc)) {
//		KNH_FREE(b->array, sizeof(knh_hashsete_t*) * b->capacity);
//	}
//}
//
///* ======================================================================== */
///* [wrappers] */
//
//HashSet* new_HashSet(Ctx *ctx, size_t capacity)
//{
//	HashSet* o = 
//		(HashSet*)new_Object__RAW(ctx, FLAG_HashSet, CLASS_HashSet, sizeof(knh_HashSet_struct));
//	knh_HashSet_struct_init(ctx, DP(o), capacity, NULL);
//	return o;
//}
//
///* ------------------------------------------------------------------------ */
//
//
//
///* ======================================================================== */
///* [wrappers] */
//
//void knh_HashSet_rehash(Ctx *ctx, HashSet *b)
//{
//	knh_HashMap_rehash(ctx, (HashMap*)b);
//}
//
///* ------------------------------------------------------------------------ */
//
//void knh_HashSet_resize(Ctx *ctx, HashSet *b, size_t nc)
//{
//	knh_HashMap_resize(ctx, (HashMap*)b, nc);
//}
//
///* ======================================================================== */
///* [methods] */
//
///* @method Int! HashSet.get(Any1 key); */
//
//knh_uint_t knh_HashSet_get(Ctx *ctx, HashSet *b, knh_hcode_t key, Object *keyobj)
//{
//	knh_uint_t h = key % DP(b)->capacity;
//	knh_hashsete_t *cur = DP(b)->array[h];
//	
//	while(cur != NULL) {
//		if(cur->h.key == key) {
//			if(keyobj == NULL || knh_Object_equals(keyobj, cur->h.keyobj)) {
//				return cur->value;
//			}
//		}
//		cur = cur->next;
//	}
//	return 0;
//}
//
//
///* ------------------------------------------------------------------------ */
//
//knh_uint_t knh_HashSet_get__b(Ctx *ctx, HashSet *b, knh_bytes_t kv)
//{
//
//	knh_hcode_t key = knh_bytes_hcode(kv);
//	knh_uint_t h =  key % DP(b)->capacity;
//	knh_hashsete_t *cur = DP(b)->array[h];
//
//	while(cur != NULL) {
//		if(cur->h.key == key && cur->h.keyobj != NULL) {
//			if(IS_bString(cur->h.keyobj) && knh_String_equals((String*)cur->h.keyobj, kv)) {
//				return cur->value;
//			}
//		}
//		cur = cur->next;
//	}
//	return 0;
//}
//
///* ------------------------------------------------------------------------ */
///* @method void HashSet.set(Any1 key, Int! value); */
//
//#define _knh_HashSet_put(ctx,b,h,k,v) knh_HashSet_set(ctx,b,h,k,v)
//
//void knh_HashSet_set(Ctx *ctx, HashSet *b, knh_hcode_t key, Any *keyobj, knh_uint_t value)
//{
//	if(((float)DP(b)->size / DP(b)->capacity) > DP(b)->factor) {
//		knh_HashSet_rehash(ctx, b);
//	}
//
//	knh_uint_t h = key % DP(b)->capacity;
//	knh_hashsete_t *cur = DP(b)->array[h];
//
//	while(cur != NULL) {
//		if(cur->h.key == key) {
//			if(keyobj == NULL) {
//				KNH_ASSERT(IS_NULL(cur->h.keyobj));
//				cur->value = value;
//				return;
//			}else if(knh_Object_equals(keyobj, cur->h.keyobj)) {
//				KNH_SETv(ctx, cur->h.keyobj, keyobj);
//				cur->value = value;
//				return;
//			}
//		}
//		cur = cur->next;
//	}
//	cur = knh_HashSete_new(ctx, key, keyobj, value);
//	cur->next = DP(b)->array[h];
//	DP(b)->array[h] = cur;
//	DP(b)->size++;
//}
//
///* ------------------------------------------------------------------------ */
///* @method void HashSet.add(Any1 key) */
//
//void knh_HashSet_add(Ctx *ctx, HashSet *b, knh_hcode_t key, Any *keyobj)
//{
//	if(((float)DP(b)->size / DP(b)->capacity) > DP(b)->factor) {
//		knh_HashSet_rehash(ctx, b);
//	}
//
//	knh_uint_t h = key % DP(b)->capacity;
//	knh_hashsete_t *cur = DP(b)->array[h];
//
//	while(cur != NULL) {
//		if(cur->h.key == key) {
//			if(keyobj == NULL) {
//				KNH_ASSERT(cur->h.keyobj == NULL);
//			}else if(knh_Object_equals(keyobj, cur->h.keyobj)) {
//				KNH_SETv(ctx, cur->h.keyobj, keyobj);
//			}
//			cur->value++;
//			return;
//		}
//		cur = cur->next;
//	}
//	cur = knh_HashSete_new(ctx, key, keyobj, 1);
//	cur->next = DP(b)->array[h];
//	DP(b)->array[h] = cur;
//	DP(b)->size++;
//}
//
///* ------------------------------------------------------------------------ */
///* @method void HashSet.remove(Any1 key) */
//
//void knh_HashSet_remove(Ctx *ctx, HashSet *b, knh_hcode_t key, Any *keyobj)
//{
//	knh_uint_t h = key % DP(b)->capacity;
//	knh_hashsete_t **prev, *cur;
//	
//	prev = &DP(b)->array[h];
//	cur = *prev;
//	while(cur != NULL) {
//		if(cur->h.key == key) {
//			if(keyobj == NULL || knh_Object_equals(keyobj, cur->h.keyobj)) {
//				*prev = cur->next;
//				knh_HashSete_traverse(ctx, cur, knh_Object_RCsweep);
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
