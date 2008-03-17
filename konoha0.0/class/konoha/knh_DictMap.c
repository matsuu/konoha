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

/* ======================================================================== */
/* [config] */

/* ======================================================================== */
/* [structs] */

void
knh_DictMap_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	DictMap *b =  (DictMap*)s1;
	
	b->capacity = (size_t)knh_int_max(init, KNH_DICTMAP_INITSIZE);
	b->size = 0;
	b->list = (knh_dictmape_t*)knh_malloc(ctx, sizeof(knh_dictmape_t) * b->capacity);
	size_t i;
	for(i = 0; i < b->capacity; i++) {
		KNH_INITv(b->list[i].key, KNH_NULL);
		KNH_INITv(b->list[i].value, KNH_NULL);
	}
	b->sorted = 0;
}

/* ------------------------------------------------------------------------ */

void
knh_DictMap_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
	DictMap *b =  (DictMap*)s1;
	DictMap *b2 = (DictMap*)s2;

	size_t i;
	b2->capacity = b->capacity;
	b2->size = b->size;
	b2->sorted = b->sorted;
	b2->list = (knh_dictmape_t*)knh_malloc(ctx, sizeof(knh_dictmape_t) * b2->capacity);
	for(i = 0; i < b2->capacity; i++) {
		KNH_INITv(b2->list[i].key, b->list[i].key);
		KNH_INITv(b2->list[i].value, b->list[i].value);
	}
}

/* ------------------------------------------------------------------------ */

knh_int_t
knh_DictMap_struct_compare(Ctx *ctx, Struct *s1, Struct *s2) 
{
	DictMap *b =  (DictMap*)s1;
	DictMap *b2 = (DictMap*)s2;
	TODO();	
	return b - b2;
}

/* ------------------------------------------------------------------------ */

void
knh_DictMap_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	DictMap *b= (DictMap*)s;
	size_t i;
	for(i = 0; i < b->capacity; i++) {
		gc(ctx, b->list[i].key);
		gc(ctx, b->list[i].value);
	}
	if(IS_SWEEP(gc)) {
		knh_free(b->list, sizeof(knh_dictmape_t) * b->capacity);
	}
}

/* ======================================================================== */
/* [constructors] */


DictMap* new_DictMap(Ctx *ctx0, knh_int_t capacity)
{
	DictMap *b = 
		(DictMap*)knh_Object_malloc0(ctx0, KNH_FLAG_DictMap, CLASS_DictMap, sizeof(DictMap));
	knh_DictMap_struct_init(ctx0, (Struct*)b, capacity, NULL);
	return b;
}

/* ------------------------------------------------------------------------ */

/* @method DictMap! DictMap.new(Int initialCapacity) */

DictMap *knh_DictMap_new(Ctx *ctx, DictMap *b, knh_int_t initialCapacity)
{
	if(initialCapacity > b->capacity) {
		knh_DictMap_resize(ctx, b, (size_t)initialCapacity);
	}
	return b;
}


/* ------------------------------------------------------------------------ */

/* @method[VARARGS] DictMap! DictMap.new::init(Any value) */

DictMap* knh_DictMap_new__init(Ctx *ctx, DictMap *b, knh_vargc_t ac, Object **a)
{
	knh_int_t i;
	for(i = 0; i < ac; i += 2) {
		if(!IS_String(a[i]) || IS_NULL(a[i+1])) break;
		knh_DictMap_append(ctx, b, a[i], a[i+1]);
	}
	knh_DictMap_sort(b);
	return b;
}

/* ======================================================================== */
/* [utils] */

int 
knh_DictMap_util_cmp(const knh_dictmape_t *n1, const knh_dictmape_t *n2)
{
	return knh_strcmp(knh_String_tochar(n1->key), knh_String_tochar(n2->key));
}

/* ------------------------------------------------------------------------ */

void knh_DictMap_sort(DictMap *b)
{
	if(b->sorted == b->size) return;
	knh_qsort(b->list, b->size, sizeof(knh_dictmape_t), 
				(int (*)(const void*, const void*))knh_DictMap_util_cmp);		
	b->sorted = b->size;
}

/* ------------------------------------------------------------------------ */

#define DICTMAP_LINER_SIZE 8
	
knh_int_t
knh_DictMap_findb_between(DictMap *b, knh_bytes_t kv, size_t sp, size_t ep)
{
	JUMP:;
	knh_int_t i;
	if(ep - sp < DICTMAP_LINER_SIZE) {
		for(i = sp; i < ep; i++) {
			if(knh_String_equals(b->list[i].key, kv)) return i;
		}
		return -1;
	}
	
	size_t cp = KNH_MID(sp, ep);
	i = knh_bytes_strcmp(kv, knh_String_tobytes(b->list[cp].key));

	if(i < 0) {
		ep = cp;
		goto JUMP;
	}else if(i == 0) {
		return cp;
	}
	sp = cp + 1;
	goto JUMP;
}

/* ------------------------------------------------------------------------ */

knh_index_t knh_DictMap_indexb(DictMap *b, knh_bytes_t kv)
{
	int loc;
	if(b->size == 0) return -1;
	if(b->size - b->sorted >= DICTMAP_LINER_SIZE) {
		knh_DictMap_sort(b);
		return knh_DictMap_findb_between(b, kv, 0, b->sorted);
	}
	loc = knh_DictMap_findb_between(b, kv, 0, b->sorted);
	return (loc == -1) ? knh_DictMap_findb_between(b, kv, b->sorted, b->size) : loc;
}

/* ======================================================================== */
/* [methods] */

INLINE 
String* knh_DictMaps_key(DictMap *b, size_t n)
{
	return b->list[n].key;
}

/* ------------------------------------------------------------------------ */

INLINE 
Any* knh_DictMaps_value(DictMap *b, size_t n)
{
	return b->list[n].value;
}


/* ------------------------------------------------------------------------ */


INLINE
Any *knh_DictMap_getb(Ctx *ctx, DictMap *b, knh_bytes_t key)
{
	knh_int_t loc = knh_DictMap_indexb(b, key);
	return (loc == -1) ? KNH_NULL : b->list[loc].value;
}


/* ------------------------------------------------------------------------ */

/* @method Any DictMap.get(String! key) */

INLINE
Any *knh_DictMap_get(Ctx *ctx, DictMap *b, String *key)
{
	knh_int_t loc = knh_DictMap_indexb(b, knh_String_tobytes(key));
	return (loc == -1) ? KNH_NULL : b->list[loc].value;
}

/* ------------------------------------------------------------------------ */

void
knh_DictMap_resize(Ctx *ctx, DictMap *b, size_t newsize)
{
	knh_dictmape_t *newlist = (knh_dictmape_t *)knh_malloc(ctx, newsize * sizeof(knh_dictmape_t));
	size_t i;
	if(newsize < b->capacity) {
		knh_memcpy(&newlist[0], &b->list[0], (sizeof(knh_dictmape_t) * newsize));
		for(i = newsize; i < b->capacity; i++) {
			KNH_FINALv(ctx, b->list[i].key);
			KNH_FINALv(ctx, b->list[i].value);
		}
	}else {
		knh_memcpy(&newlist[0], &b->list[0], (sizeof(knh_dictmape_t) * b->capacity));
		for(i = b->capacity; i < newsize; i++) {
			KNH_INITv(newlist[i].key, KNH_NULL);
			KNH_INITv(newlist[i].value, KNH_NULL);
		}
	}
	knh_free(b->list, sizeof(knh_dictmape_t) * b->capacity);
	b->list = newlist;
	b->capacity = newsize;
}


/* ------------------------------------------------------------------------ */

/* @method void DictMap.append(String! key, Any! value) */

void knh_DictMap_append(Ctx *ctx, DictMap *b, String *key, Any *value)
{
   if(b->size >= b->capacity) {
      knh_DictMap_resize(ctx, b, b->capacity * 2);
   }
   KNH_SETv(ctx, b->list[b->size].key, key);
   KNH_SETv(ctx, b->list[b->size].value, value);
   b->size++;
}

/* ------------------------------------------------------------------------ */

/* @method void DictMap.set(String! key, Any value) */

#define _knh_DictMap_put(ctx,b,k,v) knh_DictMap_set(ctx,b,k,v)


void knh_DictMap_set(Ctx *ctx, DictMap *b, String *key, Any *value)
{
	int loc = knh_DictMap_indexb(b, knh_String_tobytes(key));
	if(loc != -1) {
		KNH_SETv(ctx, b->list[loc].key, key);  /* To avoid losing key */
		if(IS_NULL(value) && IS_NOTNULL(b->list[loc].value)) {
			b->size--;
		}else if(IS_NOTNULL(value) && IS_NULL(b->list[loc].value)) {
			b->size++;
		}
		KNH_SETv(ctx, b->list[loc].value, value);
		return ;
	}
	knh_DictMap_append(ctx, b, key, value);
}

/* ------------------------------------------------------------------------ */
/* @method void DictMap.remove(String! key) */

#define _knh_DictMap_put(ctx,b,k,v) knh_DictMap_set(ctx,b,k,v)


void knh_DictMap_remove(Ctx *ctx, DictMap *b, String *key)
{
	knh_DictMap_set(ctx, b, key, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

/* @method void DictMap.clear() */


void knh_DictMap_clear(Ctx *ctx, DictMap *b) 
{
	size_t i;
	for(i = 0; i < b->capacity; i++) {
		KNH_SETv(ctx, b->list[i].key, KNH_NULL);
		KNH_SETv(ctx, b->list[i].value, KNH_NULL);
	}
	b->size = 0;
	b->sorted = 0;
}

/* ======================================================================== */
/* [mappings] */

/* ======================================================================== */
/* [iterators] */

Object *knh_DictMap_key_next(Ctx *ctx, Iterator *it)
{
	DictMap *b = (DictMap*)knh_Iterator_source(it);
	size_t pos;  
	for(pos = knh_Iterator_pos(it); pos < b->size; pos++) {
		if(IS_NOTNULL(b->list[pos].value)) {
			knh_Iterator_setpos(it,pos+1);
			return b->list[pos].key;
		}
	}
	knh_Iterator_setpos(it,pos);
	return KNH_NULL;
}


/* ------------------------------------------------------------------------ */

/* @map DictMap Iterator! */
/* @map DictMap String.. */

Any* knh_DictMap_Iterator(Ctx *ctx, Object *self, MapMap *map)
{
	knh_DictMap_sort(self);
	return new_Iterator(ctx, CLASS_String, self, knh_DictMap_key_next);	
}

#define _knh_DictMap_String__   knh_DictMap_Iterator


/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */

/* @method void DictMap.%dump(OutputStream w, Any m) */

void knh_DictMap__dump(Ctx *ctx, DictMap *b, OutputStream *w, Any *m)
{
	knh_DictMap_sort(b);
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
		knh_format(ctx, w, METHODN__dump, b->list[c].value, KNH_NULL);
	}
	knh_putc(ctx, w, '}');
}

#ifdef __cplusplus
}
#endif
