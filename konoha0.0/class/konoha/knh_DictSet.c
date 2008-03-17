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
knh_index_t knh_DictMap_indexb(DictMap *b, knh_bytes_t kv);

/* ======================================================================== */
/* [config] */

/* ======================================================================== */
/* [structs] */

void
knh_DictSet_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	DictSet *b =  (DictSet*)s1;
	b->capacity = (size_t)knh_int_max(init, KNH_DICTMAP_INITSIZE);
	b->size = 0;
	b->list = (knh_dictsete_t*)knh_malloc(ctx, sizeof(knh_dictsete_t) * b->capacity);
	size_t i;
	for(i = 0; i < b->capacity; i++) {
		KNH_INITv(b->list[i].key, KNH_NULL);
		b->list[i].value = 0;
	}
	b->sorted = 0;
}

/* ------------------------------------------------------------------------ */

void
knh_DictSet_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
	DictSet *b =  (DictSet*)s1;
	DictSet *b2 = (DictSet*)s2;
	
	size_t i;
	b2->capacity = b->capacity;
	b2->size = b->size;
	b2->sorted = b->sorted;
	b2->list = (knh_dictsete_t*)knh_malloc(ctx, sizeof(knh_dictsete_t) * b2->capacity);
	for(i = 0; i < b2->capacity; i++) {
		KNH_INITv(b2->list[i].key, b->list[i].key);
		b2->list[i].value = b->list[i].value;
	}
}

/* ------------------------------------------------------------------------ */

knh_int_t
knh_DictSet_struct_compare(Ctx *ctx, Struct *s1, Struct *s2) 
{
	DictSet *b =  (DictSet*)s1;
	DictSet *b2 = (DictSet*)s2;
	return b - b2;
}

/* ------------------------------------------------------------------------ */

void
knh_DictSet_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	DictSet *b = (DictSet*)s;
	size_t i;
	for(i = 0; i < b->capacity; i++) {
		gc(ctx, b->list[i].key);
	}
	if(IS_SWEEP(gc)) {
		knh_free(b->list, sizeof(knh_dictsete_t) * b->capacity);
	}
}
	
/* ======================================================================== */
/* [constructors] */


DictSet *new_DictSet(Ctx *ctx, knh_int_t capacity)
{
	DictSet *b = 
		(DictSet*)knh_Object_malloc0(ctx, KNH_FLAG_DictSet, CLASS_DictSet, sizeof(DictSet));
	knh_DictSet_struct_init(ctx, (Struct*)b, capacity, NULL);
	return b;
}

/* ------------------------------------------------------------------------ */

/* @method DictSet! DictSet.new(Int initialCapacity=0) */

INLINE
DictSet* knh_DictSet_new(Ctx *ctx, DictSet *b, knh_int_t initialCapacity)
{
	if(initialCapacity > b->capacity) {
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
	return knh_DictMap_indexb((DictMap*)b, kv);
}

/* ======================================================================== */
/* [methods] */

INLINE 
String* knh_DictSet_key(DictSet *b, size_t n)
{
	DEBUG_ASSERT(n < b->size);
	return b->list[n].key;
}

/* ------------------------------------------------------------------------ */

INLINE 
knh_uint_t knh_DictSet_value(DictSet *b, size_t n)
{
	DEBUG_ASSERT(n < b->size);
	return b->list[n].value;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_uint_t knh_DictSet_get__b(DictSet *b, knh_bytes_t kv)
{
	knh_int_t loc = knh_DictSet_index__b(b, kv);
	return (loc == -1) ? 0 : b->list[loc].value;
}

/* ------------------------------------------------------------------------ */

/* @method Int! DictSet.get(String! key) */

INLINE
knh_int_t knh_DictSet_get(DictSet *b, String *key)
{
	knh_int_t loc = knh_DictSet_index__b(b, knh_String_tobytes(key));
	return (loc == -1) ? 0 : b->list[loc].value;
}

/* ------------------------------------------------------------------------ */

/* @method Bool DictSet.opIn(Any value) */

INLINE
knh_bool_t knh_DictSet_opIn(Ctx *ctx, DictSet *b, Any *value)
{
	return (STRUCT_IS_String(value) && knh_DictSet_index__b(b, knh_String_tobytes(value)) != -1);
}

/* ------------------------------------------------------------------------ */

void
knh_DictSet_resize(Ctx *ctx, DictSet *b, size_t newsize)
{
	DEBUG_RESIZE(b, b->list, b->capacity, newsize);
	
	knh_dictsete_t *newlist = (knh_dictsete_t*)knh_malloc(ctx, newsize * sizeof(knh_dictsete_t));
	size_t i;
	if(newsize < b->capacity) {
		knh_memcpy(&newlist[0], &b->list[0], (sizeof(knh_dictsete_t) * newsize));
		for(i = newsize; i < b->capacity; i++) {
			KNH_FINALv(ctx, b->list[i].key);
			b->list[i].value = 0;
		}
	}else {
		knh_memcpy(&newlist[0], &b->list[0], (sizeof(knh_dictsete_t) * b->capacity));
		for(i = b->capacity; i < newsize; i++) {
			KNH_INITv(newlist[i].key, KNH_NULL);
			newlist[i].value = 0;
		}
	}
	knh_free(b->list, sizeof(knh_dictsete_t) * b->capacity);
	b->list = newlist;
	b->capacity = newsize;
}

/* ------------------------------------------------------------------------ */


void knh_DictSet_append(Ctx *ctx, DictSet *b, String *key, knh_uint_t value)
{
   if(b->size == b->capacity) {
      knh_DictSet_resize(ctx, b, b->capacity * 2);
   }
   KNH_SETv(ctx, b->list[b->size].key, key);
   b->list[b->size].value = value;
   b->size++;
}

/* ------------------------------------------------------------------------ */

/* @method void DictSet.set(String! key, Int! value) */

#define _knh_DictSet_put(ctx,b,k,v) knh_DictSet_set(ctx,b,k,v)


void knh_DictSet_set(Ctx *ctx, DictSet *b, String *key, knh_uint_t value)
{
	knh_int_t loc = knh_DictSet_index__b(b, knh_String_tobytes(key));
	if(loc != -1) {
		KNH_SETv(ctx, b->list[loc].key, key);  /* To avoid losing key */
		if(value == 0 && b->list[loc].value > 0) {
			b->size--;
		}else if(value > 0 && b->list[loc].value == 0) {
			b->size++;
		}
		b->list[loc].value = value;
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
		KNH_SETv(ctx, b->list[loc].key, key);  /* To avoid losing key */
		b->list[loc].value++;
		return ;
	}
	knh_DictSet_append(ctx, b, key, 1);
}

/* ------------------------------------------------------------------------ */

/* @method void DictSet.clear() */


void knh_DictSet_clear(Ctx *ctx, DictSet *b) 
{
	size_t i;
	for(i = 0; i < b->capacity; i++) {
		KNH_SETv(ctx, b->list[i].key, KNH_NULL);
		b->list[i].value = 0;
	}
	b->size = 0;
	b->sorted = 0;
}


/* ======================================================================== */
/* [mappings] */


/* ======================================================================== */
/* [iterators] */

Object*
knh_DictSet_key_next(Ctx *ctx, Iterator *it)
{
	DictSet *b = (DictSet*)knh_Iterator_source(it);
	size_t pos;  
	for(pos = knh_Iterator_pos(it); pos < b->size; pos++) {
		if(b->list[pos].value != 0) {
			knh_Iterator_setpos(it,pos+1);
			return b->list[pos].key;
		}
	}
	knh_Iterator_setpos(it,pos);
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

/* @map DictSet Iterator! */


Object* knh_DictSet_Iterator(Ctx *ctx, Object *self, MapMap *map)
{
	return new_Iterator(ctx, CLASS_String, self, knh_DictSet_key_next);	
}

/* ======================================================================== */
/* [movabletext] */

/* @method void DictSet.%dump(OutputStream w, Any m) */

void knh_DictSet__dump(Ctx *ctx, DictSet *b, OutputStream *w, Any *m)
{
	knh_DictSet_sort(b);
	knh_putc(ctx, w, '{');
	size_t c;
	for(c = 0; c < b->size; c++) {
		if(c > 0) {
			knh_write_delim(ctx,w);
		}
		if(!knh_array_isdump(c)) {
			knh_write_dots(ctx, w);
			break;
		}
		knh_format(ctx, w, METHODN__s, b->list[c].key, KNH_NULL);
		knh_putc(ctx, w, ':');	knh_putc(ctx, w, ' ');
		knh_write__i(ctx, w, b->list[c].value);
	}
	knh_putc(ctx, w, '}');
}


#ifdef __cplusplus
}
#endif
