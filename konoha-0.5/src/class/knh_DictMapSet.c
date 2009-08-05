/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2005-2009, Kimio Kuramitsu <kimio at ynu.ac.jp>
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
/* [hdict] */
/* @data */

typedef struct {
	size_t capacity;
	size_t sorted;
	void (*fdict_init)(Ctx *ctx, knh_dict_t *);
	void (*fdict_traverse)(Ctx *ctx, knh_dict_t *, knh_ftraverse ftr);
	int  (*fdict_compar)(const void *, const void *);
	void *dummy;
} knh_hdict_t ;

/* ------------------------------------------------------------------------ */

static
size_t knh_dict_capacity(knh_dict_t *a)
{
	if(a == NULL) {
		return 0;
	}
	else {
		knh_hdict_t *h = ((knh_hdict_t*)a);
		return h[-1].capacity;
	}
}

/* ------------------------------------------------------------------------ */

static
size_t knh_dict_sorted(knh_dict_t *a)
{
	if(a == NULL) {
		return 0;
	}
	else {
		knh_hdict_t *h = ((knh_hdict_t*)a);
		return h[-1].sorted;
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_dict_setsorted(knh_dict_t *a, size_t size)
{
	if(a != NULL) {
		knh_hdict_t *h = ((knh_hdict_t*)a);
		h[-1].sorted = size;
	}
}

/* ------------------------------------------------------------------------ */

static
knh_dict_t *knh_dict_malloc(Ctx *ctx, size_t capacity,
		void (*fdict_init)(Ctx *, knh_dict_t*), void (*fdict_traverse)(Ctx*, knh_dict_t*, knh_ftraverse),
		int (*fdict_compar)(const void*, const void*))
{
	knh_hdict_t *h;
	knh_dict_t *a;
	size_t i;
	if(!(capacity > 0)) {
		capacity = (KONOHA_SMALLPAGESIZE - sizeof(knh_hdict_t)) / sizeof(knh_dict_t);
	}

	h = (knh_hdict_t*)KNH_MALLOC(ctx, (capacity * sizeof(knh_dict_t)) + sizeof(knh_hdict_t));
	h->capacity = capacity;
	h->sorted = 0;
	h->fdict_init = fdict_init;
	h->fdict_traverse = fdict_traverse;
	h->fdict_compar = fdict_compar;
	a = (knh_dict_t*)(h+1);
	for(i = 0; i < capacity; i++) {
		fdict_init(ctx, a + i);
	}
	return a;
}

/* ------------------------------------------------------------------------ */

knh_dict_t* knh_dict_resize(Ctx *ctx, knh_dict_t *a, size_t newsize)
{
	knh_hdict_t *h = ((knh_hdict_t*)a) - 1, *newh = NULL;
	knh_dict_t *newa = NULL;
	size_t i, size = h->capacity;
	if (size < newsize) {
		newh = (knh_hdict_t*)KNH_MALLOC(ctx, (sizeof(knh_dict_t) * newsize) + sizeof(knh_hdict_t));
		newh->capacity = newsize;
		newh->fdict_init = h->fdict_init;
		newh->fdict_traverse = h->fdict_traverse;
		newh->sorted = h->sorted;
		newh->fdict_compar = h->fdict_compar;
		newa = (knh_dict_t*)(newh + 1);
		if(size > 0) {
			knh_memcpy(newa, a, (sizeof(knh_dict_t) * size));
		}
		for(i = size; i < newsize; i++) {
			newh->fdict_init(ctx, newa + i);
		}
		if(size > 0) {
			KNH_FREE(ctx, h, (sizeof(knh_dict_t) * size) + sizeof(knh_hdict_t));
		}
		return newa;
	}
	else if(newsize < size) {
		if(newsize > 0) {
			newh = (knh_hdict_t*)KNH_MALLOC(ctx, (sizeof(knh_dict_t) * newsize) + sizeof(knh_hdict_t));
			newh->capacity = newsize;
			newh->fdict_init = h->fdict_init;
			newh->fdict_traverse = h->fdict_traverse;
			newh->sorted = h->sorted;
			newh->fdict_compar = h->fdict_compar;
			newa = (knh_dict_t*)(newh + 1);
			knh_memcpy(newa, a, (sizeof(knh_dict_t) * size));
		}
		else {
			DBG2_P("resize to 0");
			newa = NULL;
		}
		for(i = newsize; i < size; i++) {
			newh->fdict_traverse(ctx, a + i, knh_Object_sweep);
		}
		KNH_FREE(ctx, h, (sizeof(knh_dict_t) * size) + sizeof(knh_hdict_t));
		return newa;
	}
	else { /* size == newssiz */
		return a;
	}
}

/* ------------------------------------------------------------------------ */

void knh_dict_traverse(Ctx *ctx, knh_dict_t *a, knh_ftraverse ftr)
{
	if(a != NULL) {
		knh_hdict_t *h = ((knh_hdict_t*)a) - 1;
		size_t i = 0;
		for(i = 0; i < h->capacity; i++) {
			h->fdict_traverse(ctx, a + i, ftr);
		}
		if(IS_SWEEP(ftr) && h->capacity > 0) {
			KNH_FREE(ctx, h, (h->capacity * sizeof(knh_dict_t)) + sizeof(knh_hdict_t));
		}
	}
}

/* ======================================================================== */
/* [sort] */

static
void knh_dict_sort(knh_dict_t *a, size_t size)
{
	if(a != NULL) {
		knh_hdict_t *h = ((knh_hdict_t*)a) - 1;
		if(h->fdict_compar != NULL) {
			knh_sort(a, size, sizeof(knh_dict_t), h->fdict_compar);
			h->sorted = size;
		}
		else {
			DBG_P("cannot sort !!");
		}
	}
}

/* ======================================================================== */
/* [dictentry] */

#define UNSORTED_MAXSIZ 8

static
knh_index_t knh_dict_findb_between(knh_dict_t *a, knh_fbytescmp fcmp, knh_bytes_t key, size_t sp, size_t ep)
{
	L_TAIL:;
	if(ep - sp < UNSORTED_MAXSIZ) {
		size_t i;
		for(i = sp; i < ep; i++) {
			if(fcmp(knh_String_tobytes(a[i].key), key) == 0) return i;
		}
		return -1;
	}
	else {
		size_t cp = KNH_MID(sp, ep);
		int i = fcmp(key, knh_String_tobytes(a[cp].key));
		if(i == 0) {
			return cp;
		}
		else if(i < 0) {
			ep = cp;
		}else {
			sp = cp + 1;
		}
		goto L_TAIL;
	}
}

/* ------------------------------------------------------------------------ */

static
knh_index_t knh_dict_index_b(knh_dict_t *a, size_t size, knh_fbytescmp fcmp, knh_bytes_t key)
{
	if(a == NULL) {
		return -1;
	}
	else {
		size_t sorted = knh_dict_sorted(a);
		if(size - sorted >= UNSORTED_MAXSIZ) {
			knh_dict_sort(a, size);
			return knh_dict_findb_between(a, fcmp, key, 0, size);
		}
		else {
			knh_index_t loc = knh_dict_findb_between(a, fcmp, key, 0, sorted);
			return (loc == -1) ? knh_dict_findb_between(a, fcmp, key, sorted, size) : loc;
		}
	}
}


/* ------------------------------------------------------------------------ */

void knh_DictMap_sort(DictMap *o)
{
	if(knh_dict_sorted(o->_list) != o->size) {
		knh_dict_sort(o->_list, o->size);
	}
}

/* ------------------------------------------------------------------------ */

void knh_DictSet_sort(DictSet *o)
{
	if(knh_dict_sorted(o->_list) != o->size) {
		knh_dict_sort(o->_list, o->size);
	}
}

/* ========================================================================= */

static
void knh_dictmap_finit(Ctx *ctx, knh_dict_t *p)
{
	knh_dictmape_t *e = (knh_dictmape_t*)p;
	KNH_INITv(e->key, KNH_NULL);
	KNH_INITv(e->value, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

static
void knh_dictmap_ftraverse(Ctx *ctx, knh_dict_t *p, knh_ftraverse ftr)
{
	knh_dictmape_t *e = (knh_dictmape_t*)p;
	ftr(ctx, UP(e->key));
	ftr(ctx, e->value);
}

/* ------------------------------------------------------------------------ */

static
void knh_dictset_finit(Ctx *ctx, knh_dict_t *p)
{
	knh_dictsete_t *e = (knh_dictsete_t*)p;
	KNH_INITv(e->key, KNH_NULL);
	e->value = 0;
}

/* ------------------------------------------------------------------------ */

static
void knh_dictset_ftraverse(Ctx *ctx, knh_dict_t *p, knh_ftraverse ftr)
{
	knh_dictsete_t *e = (knh_dictsete_t*)p;
	ftr(ctx, UP(e->key));
}

/* ------------------------------------------------------------------------ */

static
int knh_dict_fcmp(const void *p, const void *p2)
{
	knh_dict_t *e = (knh_dict_t*)p;
	knh_dict_t *e2 = (knh_dict_t*)p2;
	return knh_bytes_strcmp(knh_String_tobytes(e->key), knh_String_tobytes(e2->key));
}

/* ------------------------------------------------------------------------ */

static
int knh_dict_fcasecmp(const void *p, const void *p2)
{
	knh_dict_t *e = (knh_dict_t*)p;
	knh_dict_t *e2 = (knh_dict_t*)p2;
	return knh_bytes_strcasecmp(knh_String_tobytes(e->key), knh_String_tobytes(e2->key));
}

/* ------------------------------------------------------------------------ */

static
void knh_dict_tocase(knh_dict_t *a)
{
	if(a != NULL) {
		knh_hdict_t *h = ((knh_hdict_t*)a);
		h[-1].fdict_compar = knh_dict_fcasecmp;
	}
}

/* ------------------------------------------------------------------------ */

void knh_DictMap_toIgnoreCase(DictMap *o)
{
	knh_dict_tocase(o->_list);
	o->fcmp = knh_bytes_strcasecmp;
	knh_DictMap_setIgnoreCase(o, 1);
}

/* ------------------------------------------------------------------------ */

void knh_DictSet_toIgnoreCase(DictSet *o)
{
	knh_dict_tocase(o->_list);
	o->fcmp = knh_bytes_strcasecmp;
	knh_DictSet_setIgnoreCase(o, 1);
}

/* ======================================================================== */
/* [DictMap] */

knh_dict_t *knh_dictmap_malloc(Ctx *ctx, size_t init)
{
	return knh_dict_malloc(ctx, init, knh_dictmap_finit, knh_dictmap_ftraverse, knh_dict_fcmp);
}

/* ------------------------------------------------------------------------ */

DictMap* new_DictMap0(Ctx *ctx, knh_intptr_t capacity)
{
	knh_DictMap_t *o = (knh_DictMap_t*)new_hObject(ctx, FLAG_DictMap, CLASS_DictMap, CLASS_DictMap);
	o->_list = knh_dict_malloc(ctx, capacity, knh_dictmap_finit, knh_dictmap_ftraverse, knh_dict_fcmp);
	o->size = 0;
	o->fcmp = knh_bytes_strcmp;
	return o;
}

/* ------------------------------------------------------------------------ */

DictMap* new_DictMap(Ctx *ctx, knh_class_t p1, knh_intptr_t capacity)
{
	knh_class_t cid = knh_class_Generics(ctx, CLASS_DictMap, p1, CLASS_unknown);
	knh_DictMap_t *o = (knh_DictMap_t*)new_hObject(ctx, FLAG_DictMap, CLASS_DictMap, cid);
	o->_list = knh_dict_malloc(ctx, capacity, knh_dictmap_finit, knh_dictmap_ftraverse, knh_dict_fcmp);
	o->size = 0;
	o->fcmp = knh_bytes_strcmp;
	return o;
}

/* ======================================================================== */
/* [methods] */

size_t knh_DictMap_size(DictMap *o)
{
	return o->size;
}

/* ------------------------------------------------------------------------ */

String* knh_DictMap_keyAt(DictMap *o, size_t n)
{
	KNH_ASSERT(IS_bDictMap(o));
	KNH_ASSERT(n < o->size);
	return o->list[n].key;
}

/* ------------------------------------------------------------------------ */

Object* knh_DictMap_valueAt(DictMap *o, size_t n)
{
	KNH_ASSERT(IS_bDictMap(o));
	KNH_ASSERT(n < o->size);
	return o->list[n].value;
}

/* ------------------------------------------------------------------------ */

void knh_DictMap_removeAt(Ctx *ctx, DictMap *o, size_t n)
{
	KNH_ASSERT(IS_bDictMap(o));
	KNH_ASSERT(n < o->size);
	KNH_SETv(ctx, o->list[n].value, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

knh_index_t knh_DictMap_index(DictMap *o, knh_bytes_t key)
{
	KNH_ASSERT(IS_bDictMap(o));
	return knh_dict_index_b(o->_list, o->size, o->fcmp, key);
}

/* ------------------------------------------------------------------------ */

static
knh_index_t knh_dict_first(knh_dict_t *a, knh_fbytescmp fcmp, knh_bytes_t key, size_t sp, size_t ep)
{
	L_TAIL:;
	if(ep - sp < UNSORTED_MAXSIZ) {
		size_t i;
		for(i = sp; i < ep; i++) {
			int res = fcmp(knh_String_tobytes(a[i].key), key);
			if(res >= 0) return i;
		}
		return -1;
	}
	else {
		size_t cp = KNH_MID(sp, ep);
		int i = fcmp(key, knh_String_tobytes(a[cp].key));
		if(i == 0) {
			return cp;
		}
		else if(i < 0) {
			ep = cp;
		}else {
			sp = cp + 1;
		}
		goto L_TAIL;
	}
}

/* ------------------------------------------------------------------------ */

knh_index_t knh_DictMap_firstIndex(DictMap *o, knh_bytes_t key)
{
	KNH_ASSERT(IS_bDictMap(o));
	knh_DictMap_sort(o);
	return knh_dict_first(o->_list, o->fcmp, key, 0, o->size);
}

/* ------------------------------------------------------------------------ */

String *new_String__DictMap(Ctx *ctx, DictMap *o, knh_bytes_t key)
{
	KNH_ASSERT(IS_bDictMap(o));
	knh_index_t loc = knh_dict_index_b(o->_list, o->size, o->fcmp, key);
	if(loc == -1) {
		return new_String(ctx, key, NULL);
	}
	else {
		return o->list[loc].key;
	}
}

/* ------------------------------------------------------------------------ */

Object *knh_DictMap_get__b(Ctx *ctx, DictMap *o, knh_bytes_t key)
{
	KNH_ASSERT(IS_bDictMap(o));
	knh_intptr_t loc = knh_dict_index_b(o->_list, o->size, o->fcmp, key);
	return (loc == -1) ? KNH_NULL : o->list[loc].value;
}

/* ------------------------------------------------------------------------ */

Object *knh_DictMap_get(Ctx *ctx, DictMap *o, String *key)
{
	KNH_ASSERT(IS_bDictMap(o));
	knh_intptr_t loc = knh_dict_index_b(o->_list, o->size, o->fcmp, knh_String_tobytes(key));
	return (loc == -1) ? KNH_NULL : o->list[loc].value;
}

/* ------------------------------------------------------------------------ */

void knh_DictMap_append(Ctx *ctx, DictMap *o, String *key, Any *value)
{
	KNH_ASSERT(IS_bDictMap(o));
	if(o->_list == NULL) {
		o->_list = knh_dict_malloc(ctx, 8, knh_dictmap_finit, knh_dictmap_ftraverse, knh_dict_fcmp);
		o->size = 0;
	}
	else {
		size_t capacity = knh_dict_capacity(o->_list);
		if(o->size == capacity) {
			o->_list = knh_dict_resize(ctx, o->_list, capacity * 2);
		}
	}
	KNH_SETv(ctx, o->list[o->size].key, key);
	KNH_SETv(ctx, o->list[o->size].value, value);
	o->size++;
}

/* ------------------------------------------------------------------------ */

void knh_DictMap_set(Ctx *ctx, DictMap *o, String *key, Any *v)
{
	knh_Object_t *value = v;
	int loc = knh_dict_index_b(o->_list, o->size, o->fcmp, knh_String_tobytes(key));
	if(loc != -1) {
		KNH_SETv(ctx, o->list[loc].key, key);  /* To avoid losing key */
		KNH_SETv(ctx, o->list[loc].value, value);
	}
	else {
		knh_DictMap_append(ctx, o, key, value);
	}
}

/* ------------------------------------------------------------------------ */

void knh_DictMap_remove(Ctx *ctx, DictMap *o, String *key)
{
	int loc = knh_dict_index_b(o->_list, o->size, o->fcmp, knh_String_tobytes(key));
	if(loc != 1) {
		KNH_SETv(ctx, o->list[loc].key, key);  /* To avoid losing key */
		KNH_SETv(ctx, o->list[loc].value, KNH_NULL);
	}
}

/* ------------------------------------------------------------------------ */

void knh_DictMap_clear(Ctx *ctx, DictMap *o)
{
	size_t i, capacity = knh_dict_capacity(o->_list);
	for(i = 0; i < capacity; i++) {
		KNH_SETv(ctx, o->list[i].key, KNH_NULL);
		KNH_SETv(ctx, o->list[i].value, KNH_NULL);
	}
	o->size = 0;
	knh_dict_setsorted(o->_list, 0);
}

/* ======================================================================== */
/* [DictSet] */

knh_dict_t *knh_dictset_malloc(Ctx *ctx, size_t init)
{
	return knh_dict_malloc(ctx, init, knh_dictset_finit, knh_dictset_ftraverse, knh_dict_fcmp);
}

/* ------------------------------------------------------------------------ */

#define _new_DictSet(ctx, c)   new_DictSet0(ctx, c)

DictSet* new_DictSet0(Ctx *ctx, knh_intptr_t capacity)
{
	knh_DictSet_t *o = (knh_DictSet_t*)new_hObject(ctx, FLAG_DictSet, CLASS_DictSet, CLASS_DictSet);
	o->_list = knh_dict_malloc(ctx, capacity, knh_dictset_finit, knh_dictset_ftraverse, knh_dict_fcmp);
	o->size = 0;
	o->fcmp = knh_bytes_strcmp;
	return o;
}

/* ======================================================================== */
/* [methods] */

size_t knh_DictSet_size(DictSet *o)
{
	return o->size;
}

/* ------------------------------------------------------------------------ */

String* knh_DictSet_keyAt(DictSet *o, size_t n)
{
	KNH_ASSERT(n < o->size);
	return o->list[n].key;
}

/* ------------------------------------------------------------------------ */

knh_uintptr_t knh_DictSet_valueAt(DictSet *o, size_t n)
{
	KNH_ASSERT(n < o->size);
	return o->list[n].value;
}

/* ------------------------------------------------------------------------ */

void knh_DictSet_removeAt(Ctx *ctx, DictSet *o, size_t n)
{
	KNH_ASSERT(n < o->size);
	o->list[n].value = 0;
}

/* ------------------------------------------------------------------------ */

String *new_String__DictSet(Ctx *ctx, DictSet *o, knh_bytes_t key)
{
	knh_index_t loc = knh_dict_index_b(o->_list, o->size, o->fcmp, key);
	if(loc == -1) {
		return new_String(ctx, key, NULL);
	}
	else {
		return o->list[loc].key;
	}
}

/* ------------------------------------------------------------------------ */

knh_uintptr_t knh_DictSet_get__b(DictSet *o, knh_bytes_t key)
{
	knh_intptr_t loc = knh_dict_index_b(o->_list, o->size, o->fcmp, key);
	return (loc == -1) ? 0 : o->list[loc].value;
}

/* ------------------------------------------------------------------------ */

knh_uintptr_t knh_DictSet_get(Ctx *ctx, DictSet *o, String *key)
{
	knh_intptr_t loc = knh_dict_index_b(o->_list, o->size, o->fcmp, knh_String_tobytes(key));
	return (loc == -1) ? 0 : o->list[loc].value;
}

/* ------------------------------------------------------------------------ */

void knh_DictSet_append(Ctx *ctx, DictSet *o, String *key, knh_uintptr_t n)
{
	if(o->_list == NULL) {
		o->_list = knh_dict_malloc(ctx, 8, knh_dictmap_finit, knh_dictmap_ftraverse, knh_dict_fcmp);
		o->size = 0;
	}
	else {
		size_t capacity = knh_dict_capacity(o->_list);
		if(o->size == capacity) {
			o->_list = knh_dict_resize(ctx, o->_list, capacity * 2);
		}
	}
	KNH_SETv(ctx, o->list[o->size].key, key);
	o->list[o->size].value = n;
	o->size++;
}

/* ------------------------------------------------------------------------ */

void knh_DictSet_set(Ctx *ctx, DictSet *o, String *key, knh_uintptr_t n)
{
	int loc = knh_dict_index_b(o->_list, o->size, o->fcmp, knh_String_tobytes(key));
	if(loc != -1) {
		KNH_SETv(ctx, o->list[loc].key, key);  /* To avoid losing key */
		o->list[loc].value = n;
	}
	else {
		knh_DictSet_append(ctx, o, key, n);
	}
}

/* ------------------------------------------------------------------------ */

void knh_DictSet_add(Ctx *ctx, DictSet *o, String *key)
{
	int loc = knh_dict_index_b(o->_list, o->size, o->fcmp, knh_String_tobytes(key));
	if(loc != -1) {
		KNH_SETv(ctx, o->list[loc].key, key);  /* To avoid losing key */
		o->list[loc].value += 1;
	}
	else {
		knh_DictSet_append(ctx, o, key, 1);
	}
}

/* ------------------------------------------------------------------------ */

void knh_DictSet_remove(Ctx *ctx, DictSet *o, String *key)
{
	int loc = knh_dict_index_b(o->_list, o->size, o->fcmp, knh_String_tobytes(key));
	if(loc != 1) {
		KNH_SETv(ctx, o->list[loc].key, key);  /* To avoid losing key */
		o->list[loc].value = 0;
	}
}

/* ------------------------------------------------------------------------ */

void knh_DictSet_clear(Ctx *ctx, DictSet *o)
{
	size_t i, capacity = knh_dict_capacity(o->_list);
	for(i = 0; i < capacity; i++) {
		KNH_SETv(ctx, o->list[i].key, KNH_NULL);
		o->list[i].value = 0;
	}
	o->size = 0;
	knh_dict_setsorted(o->_list, 0);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
