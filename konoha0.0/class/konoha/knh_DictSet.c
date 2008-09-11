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

#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

/** We share these functions with DictMap */

void knh_DictMap_sort(DictMap *b);
knh_index_t knh_DictMap_index__b(DictMap *b, knh_bytes_t kv);

/* ======================================================================== */
/* [config] */

/* ======================================================================== */
/* [structs] */

void
knh_DictSet_struct_init(Ctx *ctx, knh_DictSet_struct *b, int init, Object *cs)
{
	b->capacity = (size_t)knh_int_max(init, KNH_DICTMAP_INITSIZE);
	b->size = 0;
	b->list = (knh_dictsete_t*)KNH_MALLOC(ctx, sizeof(knh_dictsete_t) * b->capacity);
	//DBG2_P("list=%p, capacity=%d, size=%d", b->list, b->capacity, sizeof(knh_dictsete_t) * b->capacity);
	{
		size_t i;
		for(i = 0; i < b->capacity; i++) {
			KNH_INITv(b->list[i].key, KNH_NULL);
			b->list[i].value = 0;
		}
	}
	b->sorted = 0;
}

/* ------------------------------------------------------------------------ */

void
knh_DictSet_struct_copy(Ctx *ctx, knh_DictSet_struct *b, knh_DictSet_struct *b2)
{
	size_t i;
	b2->capacity = b->capacity;
	b2->size = b->size;
	b2->sorted = b->sorted;
	b2->list = (knh_dictsete_t*)KNH_MALLOC(ctx, sizeof(knh_dictsete_t) * b2->capacity);
	for(i = 0; i < b2->capacity; i++) {
		KNH_INITv(b2->list[i].key, b->list[i].key);
		b2->list[i].value = b->list[i].value;
	}
}

/* ------------------------------------------------------------------------ */

void
knh_DictSet_struct_traverse(Ctx *ctx, knh_DictSet_struct *b, f_traverse gc)
{
	size_t i;
	for(i = 0; i < b->capacity; i++) {
		gc(ctx, UP(b->list[i].key));
	}
	if(IS_SWEEP(gc)) {
		KNH_FREE(b->list, sizeof(knh_dictsete_t) * b->capacity);
	}
}
	
/* ======================================================================== */
/* [constructors] */


DictSet *new_DictSet(Ctx *ctx, knh_int_t capacity)
{
	DictSet *o = 
		(DictSet*)new_Object_malloc(ctx, FLAG_DictSet, CLASS_DictSet, sizeof(knh_DictSet_struct));
	knh_DictSet_struct_init(ctx, DP(o), capacity, NULL);
	return o;
}

/* ------------------------------------------------------------------------ */

/* @method DictSet! DictSet.new(Int initialCapacity=0) */

INLINE
DictSet* knh_DictSet_new(Ctx *ctx, DictSet *b, knh_int_t initialCapacity)
{
	if(initialCapacity > DP(b)->capacity) {
		knh_DictSet_resize(ctx, b, (size_t)initialCapacity);
	}
	return b;
}

/* ======================================================================== */
/* [wrapper] */

INLINE
void knh_DictSet_sort(DictSet *b)
{
	knh_DictMap_sort((DictMap*)b);
}

/* ------------------------------------------------------------------------ */

INLINE
knh_index_t knh_DictSet_index__b(DictSet *b, knh_bytes_t kv)
{
	return knh_DictMap_index__b((DictMap*)b, kv);
}

/* ======================================================================== */
/* [methods] */

INLINE 
String* knh_DictSet_key(DictSet *b, size_t n)
{
	KNH_ASSERT(n < DP(b)->size);
	return DP(b)->list[n].key;
}

/* ------------------------------------------------------------------------ */

INLINE 
knh_uint_t knh_DictSet_value(DictSet *b, size_t n)
{
	KNH_ASSERT(n < DP(b)->size);
	return DP(b)->list[n].value;
}

/* ------------------------------------------------------------------------ */

String *new_String__DictSet(Ctx *ctx, DictSet *o, knh_bytes_t key)
{
	knh_int_t loc = knh_DictSet_index__b(o, key);
	if(loc == -1) {
		return new_String(ctx, key, NULL);
	}
	else {
		return DP(o)->list[loc].key;
	}
}

/* ------------------------------------------------------------------------ */

INLINE
knh_uint_t knh_DictSet_get__b(DictSet *b, knh_bytes_t kv)
{
	knh_int_t loc = knh_DictSet_index__b(b, kv);
	return (loc == -1) ? 0 : DP(b)->list[loc].value;
}

/* ------------------------------------------------------------------------ */
/* @method Int! DictSet.get(String! key) */

INLINE
knh_int_t knh_DictSet_get(DictSet *b, String *key)
{
	knh_int_t loc = knh_DictSet_index__b(b, knh_String_tobytes(key));
	return (loc == -1) ? 0 : DP(b)->list[loc].value;
}

/* ------------------------------------------------------------------------ */
/* @method Boolean DictSet.opIn(Any value) */

INLINE
knh_bool_t knh_DictSet_opIn(Ctx *ctx, DictSet *b, Any *value)
{
	String *s = (String*)value;
	return (IS_bString(s) && knh_DictSet_index__b(b, knh_String_tobytes(s)) != -1);
}

/* ------------------------------------------------------------------------ */

void
knh_DictSet_resize(Ctx *ctx, DictSet *b, size_t newsize)
{
	DBG2_RESIZE(b, DP(b)->list, DP(b)->capacity, newsize);

	knh_dictsete_t *newlist = (knh_dictsete_t*)KNH_MALLOC(ctx, newsize * sizeof(knh_dictsete_t));
	size_t i;
	if(newsize < DP(b)->capacity) {
		knh_memcpy(&newlist[0], &DP(b)->list[0], (sizeof(knh_dictsete_t) * newsize));
		for(i = newsize; i < DP(b)->capacity; i++) {
			KNH_FINALv(ctx, DP(b)->list[i].key);
			DP(b)->list[i].value = 0;
		}
	}else {
		knh_memcpy(&newlist[0], &DP(b)->list[0], (sizeof(knh_dictsete_t) * DP(b)->capacity));
		for(i = DP(b)->capacity; i < newsize; i++) {
			KNH_INITv(newlist[i].key, KNH_NULL);
			newlist[i].value = 0;
		}
	}
	KNH_FREE(DP(b)->list, sizeof(knh_dictsete_t) * DP(b)->capacity);
	DP(b)->list = newlist;
	DP(b)->capacity = newsize;
}

/* ------------------------------------------------------------------------ */

void knh_DictSet_append(Ctx *ctx, DictSet *b, String *key, knh_uint_t value)
{
   if(DP(b)->size == DP(b)->capacity) {
      knh_DictSet_resize(ctx, b, DP(b)->capacity * 2);
   }
   KNH_SETv(ctx, DP(b)->list[DP(b)->size].key, key);
   DP(b)->list[DP(b)->size].value = value;
   DP(b)->size++;
}

/* ------------------------------------------------------------------------ */
/* @method void DictSet.set(String! key, Int! value) */

#define _knh_DictSet_put(ctx,b,k,v) knh_DictSet_set(ctx,b,k,v)


void knh_DictSet_set(Ctx *ctx, DictSet *b, String *key, knh_uint_t value)
{
	knh_int_t loc = knh_DictSet_index__b(b, knh_String_tobytes(key));
	if(loc != -1) {
		KNH_SETv(ctx, DP(b)->list[loc].key, key);  /* To avoid losing key */
		if(value == 0 && DP(b)->list[loc].value > 0) {
			DP(b)->size--;
		}else if(value > 0 && DP(b)->list[loc].value == 0) {
			DP(b)->size++;
		}
		DP(b)->list[loc].value = value;
		return ;
	}
	knh_DictSet_append(ctx, b, key, value);
}

/* ------------------------------------------------------------------------ */
/* @method void DictSet.add(String! key) */

void knh_DictSet_add(Ctx *ctx, DictSet *b, String *key)
{
	knh_int_t loc = knh_DictSet_index__b(b, knh_String_tobytes(key));
	if(loc != -1) {
		KNH_SETv(ctx, DP(b)->list[loc].key, key);  /* To avoid losing key */
		DP(b)->list[loc].value++;
		return ;
	}
	knh_DictSet_append(ctx, b, key, 1);
}

/* ------------------------------------------------------------------------ */
/* @method void DictSet.clear() */

void knh_DictSet_clear(Ctx *ctx, DictSet *b) 
{
	size_t i;
	for(i = 0; i < DP(b)->capacity; i++) {
		KNH_SETv(ctx, DP(b)->list[i].key, KNH_NULL);
		DP(b)->list[i].value = 0;
	}
	DP(b)->size = 0;
	DP(b)->sorted = 0;
}


/* ======================================================================== */
/* [mappings] */

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
