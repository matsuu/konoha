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
knh_DictMap_struct_init(Ctx *ctx, knh_DictMap_struct *b, int init, Object *cs)
{
	b->capacity = (size_t)knh_int_max(init, KNH_DICTMAP_INITSIZE);
	b->size = 0;
	b->list = (knh_dictmape_t*)KNH_MALLOC(ctx, sizeof(knh_dictmape_t) * b->capacity);
	size_t i;
	for(i = 0; i < b->capacity; i++) {
		KNH_INITv(b->list[i].key, KNH_NULL);
		KNH_INITv(b->list[i].value, KNH_NULL);
	}
	b->sorted = 0;
}

/* ------------------------------------------------------------------------ */

void
knh_DictMap_struct_copy(Ctx *ctx, knh_DictMap_struct *b, knh_DictMap_struct *b2)
{
	size_t i;
	b2->capacity = b->capacity;
	b2->size = b->size;
	b2->sorted = b->sorted;
	b2->list = (knh_dictmape_t*)KNH_MALLOC(ctx, sizeof(knh_dictmape_t) * b2->capacity);
	for(i = 0; i < b2->capacity; i++) {
		KNH_INITv(b2->list[i].key, b->list[i].key);
		KNH_INITv(b2->list[i].value, b->list[i].value);
	}
}

/* ------------------------------------------------------------------------ */

void
knh_DictMap_struct_traverse(Ctx *ctx, knh_DictMap_struct *b, f_traverse gc)
{
	size_t i;
	for(i = 0; i < b->capacity; i++) {
		gc(ctx, UP(b->list[i].key));
		gc(ctx, UP(b->list[i].value));
	}
	if(IS_SWEEP(gc)) {
		KNH_FREE(b->list, sizeof(knh_dictmape_t) * b->capacity);
	}
}

/* ======================================================================== */
/* [constructors] */


DictMap* new_DictMap(Ctx *ctx, knh_int_t capacity)
{
	DictMap *o =
		(DictMap*)new_Object_malloc(ctx, FLAG_DictMap, CLASS_DictMap, sizeof(knh_DictMap_struct));
	knh_DictMap_struct_init(ctx, DP(o), capacity, NULL);
	return o;
}

/* ------------------------------------------------------------------------ */

/* @method DictMap! DictMap.new(Int initialCapacity) */

DictMap *knh_DictMap_new(Ctx *ctx, DictMap *o, knh_int_t initialCapacity)
{
	if(initialCapacity > DP(o)->capacity) {
		knh_DictMap_resize(ctx, o, (size_t)initialCapacity);
	}
	return o;
}

///* ------------------------------------------------------------------------ */
///* @method[VARARGS] DictMap! DictMap.new::init(Any value) */
//
//DictMap* knh_DictMap_new__init(Ctx *ctx, DictMap *o, knh_vargc_t ac, Object **a)
//{
//	knh_int_t i;
//	for(i = 0; i < ac; i += 2) {
//		if(!IS_String(a[i]) || IS_NULL(a[i+1])) break;
//		knh_DictMap_append(ctx, o, a[i], a[i+1]);
//	}
//	knh_DictMap_sort(o);
//	return o;
//}

/* ======================================================================== */
/* [utils] */

static
int knh_DictMap_util_cmp(const knh_dictmape_t *n1, const knh_dictmape_t *n2)
{
	return knh_strcmp(knh_String_tochar(n1->key), knh_String_tochar(n2->key));
}

/* ------------------------------------------------------------------------ */

void knh_DictMap_sort(DictMap *o)
{
	if(DP(o)->sorted == DP(o)->size) return;
	knh_qsort(DP(o)->list, DP(o)->size, sizeof(knh_dictmape_t),
				(int (*)(const void*, const void*))knh_DictMap_util_cmp);
	DP(o)->sorted = DP(o)->size;
}

/* ------------------------------------------------------------------------ */

#define DICTMAP_LINER_SIZE 8

static
knh_int_t knh_DictMap_findb_between(DictMap *o, knh_bytes_t kv, size_t sp, size_t ep)
{
	JUMP:;
	knh_int_t i;
	if(ep - sp < DICTMAP_LINER_SIZE) {
		for(i = sp; i < ep; i++) {
			if(knh_String_equals(DP(o)->list[i].key, kv)) return i;
		}
		return -1;
	}

	size_t cp = KNH_MID(sp, ep);
	i = knh_bytes_strcmp(kv, knh_String_tobytes(DP(o)->list[cp].key));

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

knh_index_t knh_DictMap_index__b(DictMap *o, knh_bytes_t kv)
{
	int loc;
	if(DP(o)->size == 0) return -1;
	if(DP(o)->size - DP(o)->sorted >= DICTMAP_LINER_SIZE) {
		knh_DictMap_sort(o);
		return knh_DictMap_findb_between(o, kv, 0, DP(o)->sorted);
	}
	loc = knh_DictMap_findb_between(o, kv, 0, DP(o)->sorted);
	return (loc == -1) ? knh_DictMap_findb_between(o, kv, DP(o)->sorted, DP(o)->size) : loc;
}

/* ======================================================================== */
/* [methods] */

String* knh_DictMap_keyAt(DictMap *o, size_t n)
{
	KNH_ASSERT(n < DP(o)->size);
	return DP(o)->list[n].key;
}

/* ------------------------------------------------------------------------ */

Object* knh_DictMap_valueAt(DictMap *o, size_t n)
{
	KNH_ASSERT(n < DP(o)->size);
	return DP(o)->list[n].value;
}

/* ------------------------------------------------------------------------ */

String *new_String__DictMap(Ctx *ctx, DictMap *o, knh_bytes_t key)
{
	knh_int_t loc = knh_DictMap_index__b(o, key);
	if(loc == -1) {
		return new_String(ctx, key, NULL);
	}
	else {
		return DP(o)->list[loc].key;
	}
}

/* ------------------------------------------------------------------------ */

Object *knh_DictMap_get__b(Ctx *ctx, DictMap *o, knh_bytes_t key)
{
	knh_int_t loc = knh_DictMap_index__b(o, key);
	return (loc == -1) ? KNH_NULL : DP(o)->list[loc].value;
}


/* ------------------------------------------------------------------------ */
/* @method Any DictMap.get(String! key) */

Object *knh_DictMap_get(Ctx *ctx, DictMap *o, String *key)
{
	knh_int_t loc = knh_DictMap_index__b(o, knh_String_tobytes(key));
	return (loc == -1) ? KNH_NULL : DP(o)->list[loc].value;
}

/* ------------------------------------------------------------------------ */

void knh_DictMap_resize(Ctx *ctx, DictMap *o, size_t newsize)
{
	knh_dictmape_t *newlist = (knh_dictmape_t *)KNH_MALLOC(ctx, newsize * sizeof(knh_dictmape_t));
	size_t i;
	if(newsize < DP(o)->capacity) {
		knh_memcpy(&newlist[0], &DP(o)->list[0], (sizeof(knh_dictmape_t) * newsize));
		for(i = newsize; i < DP(o)->capacity; i++) {
			KNH_FINALv(ctx, DP(o)->list[i].key);
			KNH_FINALv(ctx, DP(o)->list[i].value);
		}
	}else {
		knh_memcpy(&newlist[0], &DP(o)->list[0], (sizeof(knh_dictmape_t) * DP(o)->capacity));
		for(i = DP(o)->capacity; i < newsize; i++) {
			KNH_INITv(newlist[i].key, KNH_NULL);
			KNH_INITv(newlist[i].value, KNH_NULL);
		}
	}
	KNH_FREE(DP(o)->list, sizeof(knh_dictmape_t) * DP(o)->capacity);
	DP(o)->list = newlist;
	DP(o)->capacity = newsize;
}


/* ------------------------------------------------------------------------ */
/* @method void DictMap.append(String! key, Any! value) */

void knh_DictMap_append(Ctx *ctx, DictMap *o, String *key, Any *value)
{
   if(DP(o)->size >= DP(o)->capacity) {
      knh_DictMap_resize(ctx, o, DP(o)->capacity * 2);
   }
   KNH_SETv(ctx, DP(o)->list[DP(o)->size].key, key);
   KNH_SETv(ctx, DP(o)->list[DP(o)->size].value, value);
   DP(o)->size++;
}

/* ------------------------------------------------------------------------ */
/* @method void DictMap.set(String! key, Any value) */

#define _knh_DictMap_put(ctx,b,k,v) knh_DictMap_set(ctx,b,k,v)

void knh_DictMap_set(Ctx *ctx, DictMap *o, String *key, Any *v)
{
	knh_Object_t *value = v;
	int loc = knh_DictMap_index__b(o, knh_String_tobytes(key));
	if(loc != -1) {
		KNH_SETv(ctx, DP(o)->list[loc].key, key);  /* To avoid losing key */
		if(IS_NULL(value) && IS_NOTNULL(DP(o)->list[loc].value)) {
			DP(o)->size--;
		}else if(IS_NOTNULL(value) && IS_NULL(DP(o)->list[loc].value)) {
			DP(o)->size++;
		}
		KNH_SETv(ctx, DP(o)->list[loc].value, value);
		return ;
	}
	knh_DictMap_append(ctx, o, key, value);
}

/* ------------------------------------------------------------------------ */
/* @method void DictMap.remove(String! key) */

#define _knh_DictMap_put(ctx,b,k,v) knh_DictMap_set(ctx,b,k,v)

void knh_DictMap_remove(Ctx *ctx, DictMap *o, String *key)
{
	knh_DictMap_set(ctx, o, key, KNH_NULL);
}

/* ------------------------------------------------------------------------ */
/* @method void DictMap.clear() */

void knh_DictMap_clear(Ctx *ctx, DictMap *o)
{
	size_t i;
	for(i = 0; i < DP(o)->capacity; i++) {
		KNH_SETv(ctx, DP(o)->list[i].key, KNH_NULL);
		KNH_SETv(ctx, DP(o)->list[i].value, KNH_NULL);
	}
	DP(o)->size = 0;
	DP(o)->sorted = 0;
}

/* ======================================================================== */
/* [mappings] */

/* ======================================================================== */
/* [iterators] */

Object *knh_DictMap_key_next(Ctx *ctx, Iterator *it)
{
	DictMap *o = (DictMap*)knh_Iterator_source(it);
	size_t pos;
	for(pos = knh_Iterator_pos(it); pos < DP(o)->size; pos++) {
		if(IS_NOTNULL(DP(o)->list[pos].value)) {
			knh_Iterator_setpos(it,pos+1);
			return (Object*)DP(o)->list[pos].key;
		}
	}
	knh_Iterator_setpos(it,pos);
	return (Object*)KNH_NULL;
}

/* ------------------------------------------------------------------------ */
/* @map DictMap Iterator! */
/* @map DictMap String.. */

Iterator* knh_DictMap_Iterator(Ctx *ctx, DictMap *o, Mapper *map)
{
	knh_DictMap_sort(o);
	return new_Iterator(ctx, CLASS_String, UP(o), knh_DictMap_key_next);
}

#define _knh_DictMap_String__   knh_DictMap_Iterator


/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */
/* @method void DictMap.%dump(OutputStream w, Any m) */

void knh_DictMap__dump(Ctx *ctx, DictMap *o, OutputStream *w, Any *m)
{
	knh_DictMap_sort(o);
	knh_putc(ctx, w, '{');
	size_t c;
	for(c = 0; c < DP(o)->size; c++) {
		if(c > 0) {
			knh_write_delim(ctx,w);
		}
		if(!knh_array_isdump(c)) {
			knh_write_dots(ctx, w);
			break;
		}
		knh_format(ctx, w, METHODN__s, (Object*)DP(o)->list[c].key, KNH_NULL);
		knh_putc(ctx, w, ':');	knh_putc(ctx, w, ' ');
		knh_format(ctx, w, METHODN__dump, DP(o)->list[c].value, KNH_NULL);
	}
	knh_putc(ctx, w, '}');
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
