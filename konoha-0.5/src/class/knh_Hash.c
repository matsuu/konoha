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

/* ------------------------------------------------------------------------ */

knh_hashentry_t *new_hashentry(Ctx *ctx, knh_Hash_t *o)
{
	knh_Hash_struct *b = DP(o);
	if(b->unused_first != NULL) {
		knh_hashentry_t *e = b->unused_first;
		b->unused_first = e->next;
		return e;
	}
	if(b->tables_size > 0 && b->tables_size == b->tables_capacity) {
		size_t newsize = b->tables_capacity * 2;
		if(newsize < KNH_FASTMALLOC_SIZE / sizeof(char*)) {
			newsize = KNH_FASTMALLOC_SIZE / sizeof(char*);
		}else if(newsize < KONOHA_SMALLPAGESIZE / sizeof(char*)) {
			newsize = KONOHA_SMALLPAGESIZE / sizeof(char*);
		}

		char **newtables = (char**)KNH_MALLOC(ctx, sizeof(char*) * newsize);
		knh_memcpy(newtables, b->tables, b->tables_size * sizeof(char*));
		char **oldtables = b->tables;
		b->tables = newtables;
		b->tables_capacity = newsize;
		if(b->tables_size > 1) {
			KNH_FREE(ctx, oldtables, sizeof(char*) * b->tables_size);
		}
	}

	char *newtable = (char*)KNH_MALLOC(ctx, KNH_HASH_TABLESIZE);
	knh_bzero(newtable, KNH_HASH_TABLESIZE);
	size_t i, esize = o->hashop->size, tsize = KNH_HASH_TABLESIZE / esize;
	for(i = 0; i < tsize; i++) {
		knh_hashentry_t *e = KNH_HASHENTRY(newtable, esize, i);
		e->next = (i == tsize - 1) ? NULL : KNH_HASHENTRY(newtable, esize, i + 1);
	}
	if(b->tables_size == 0) {
		b->tables_first = newtable;
		b->tables = &b->tables_first;
		b->tables_capacity = 1;
		b->tables_size = 1;
	}
	else {
		b->tables[b->tables_size] = newtable;
		b->tables_size += 1;
	}
	{
		knh_hashentry_t *e = (knh_hashentry_t*)newtable;
		b->unused_first = e->next;
		return e;
	}
}

/* ------------------------------------------------------------------------ */

void knh_hashentry_collect(Ctx *ctx, knh_Hash_t *o, knh_hashentry_t *e)
{
	o->hashop->ftraverse(ctx, e, knh_Object_sweep);
	e->key = NULL;
	e->hcode = 0;
	e->next = DP(o)->unused_first;
	DP(o)->unused_first = e;
}

/* ------------------------------------------------------------------------ */

knh_hashentry_t *knh_hashentry_at(knh_Hash_t *o, size_t n)
{
	size_t esize = o->hashop->size;
	size_t tsize = KNH_HASH_TABLESIZE / esize;
	size_t i = n / tsize, j = n % tsize;
	if(j < DP(o)->tables_size) {
		knh_hashentry_t *e = KNH_HASHENTRY(DP(o)->tables[j], esize, i);
		if(e->key != NULL) return e;
	}
	return NULL;
}

/* ======================================================================== */
/* [constructors] */

HashMap* new_HashMap(Ctx *ctx, char *name, size_t capacity)
{
	if(capacity == 0) capacity = KNH_HASH_INITSIZE;
	HashMap* o = (HashMap*)new_Object_bcid(ctx, CLASS_HashMap, capacity);
	if(name != NULL) {
		DP(o)->DBG_name = name;
	}
	return o;
}

/* ======================================================================== */
/* [methods] */

knh_hashentry_t *knh_Hash_get__hcode(Ctx *ctx, knh_Hash_t *o, knh_hcode_t hcode)
{
	knh_uintptr_t h = hcode % DP(o)->hmax;
	knh_hashentry_t *e = DP(o)->array[h];
	while(e != NULL) {
		if(e->hcode == hcode) return e;
		e = e->next;
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

Object *knh_HashMap_get__hcode(Ctx *ctx, HashMap *o, knh_hcode_t hcode)
{
	knh_uintptr_t h = hcode % DP((knh_Hash_t*)o)->hmax;
	knh_hashentry_t *e = DP((knh_Hash_t*)o)->array[h];
	while(e != NULL) {
		if(e->hcode == hcode) return e->value;
		e = e->next;
	}
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

knh_uintptr_t knh_HashSet_get__hcode(Ctx *ctx, HashSet *o, knh_hcode_t hcode)
{
	knh_uintptr_t h = hcode % DP((knh_Hash_t*)o)->hmax;
	knh_hashentry_t *e = DP((knh_Hash_t*)o)->array[h];
	while(e != NULL) {
		if(e->hcode == hcode) return e->uvalue;
		e = e->next;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

void knh_Hash_remove__hcode(Ctx *ctx, knh_Hash_t *o, knh_hcode_t hcode)
{
	knh_uintptr_t h = hcode % DP(o)->hmax;
	knh_hashentry_t *e = DP(o)->array[h];
	knh_hashentry_t **prev_next = &(DP(o)->array[h]);
	while(e != NULL) {
		if(e->hcode == hcode) {
			prev_next[0] = e->next;
			knh_hashentry_collect(ctx, o, e);
			DP(o)->size--;
			return ;
		}
		prev_next = &(e->next);
		e = e->next;
	}
}

/* ------------------------------------------------------------------------ */

void knh_Hash_rehash(Ctx *ctx, knh_Hash_t *o)
{
	knh_Hash_struct *b = DP(o);
	if(b->size * 4 < b->hmax * 3) return ;
	size_t newhmax = b->hmax * 2 + 1;
	if(newhmax < KNH_HASH_INITSIZE) newhmax = KNH_HASH_INITSIZE;
	if(b->capacity < newhmax) {
		if(b->capacity != 0) {
			KNH_FREE(ctx, b->array, DP(o)->capacity * sizeof(knh_hashentry_t*));
		}
		size_t newsize = knh_bytes_newsize(newhmax * sizeof(knh_hashentry_t*));
		b->array = (knh_hashentry_t**)KNH_MALLOC(ctx, newsize);
		b->capacity = newsize / sizeof(knh_hashentry_t*);
	}
	knh_bzero(b->array, newhmax * sizeof(knh_hashentry_t*));
	b->hmax = newhmax;
	size_t i, j, esize = o->hashop->size;
	size_t tsize = KNH_HASH_TABLESIZE / esize;
	for(i = 0; i < b->tables_size; i++) {
		for(j = 0; j < tsize; j++) {
			knh_hashentry_t *e = KNH_HASHENTRY(b->tables[i], esize, j);
			if(e->key == NULL) continue;
			e->next = NULL;
			knh_uintptr_t h = e->hcode % newhmax;
			knh_hashentry_t **p = &(b->array[h]);
			while(p[0] != NULL) p = &(p[0]->next);
			p[0] = e;
		}
	}
}

/* ------------------------------------------------------------------------ */

void knh_HashMap_set__hcode(Ctx *ctx, HashMap *o, knh_hcode_t hcode, Any *value)
{
	knh_Hash_t *hash = (knh_Hash_t*)o;
	knh_hashentry_t *e = knh_Hash_get__hcode(ctx, hash, hcode);
	if(e != NULL) {
		KNH_SETv(ctx, e->value, value);
		return;
	}
	knh_Hash_rehash(ctx, hash);
	e = new_hashentry(ctx, hash);
	e->hcode = hcode;
	KNH_INITv(e->key, KNH_NULL);
	KNH_INITv(e->value, value);
	knh_uintptr_t h = hcode % DP(o)->hmax;
	e->next = DP(o)->array[h];
	DP(o)->array[h] = e;
	DP(o)->size++;
}

/* ------------------------------------------------------------------------ */

void knh_HashSet_set__hcode(Ctx *ctx, HashSet *o, knh_hcode_t hcode, knh_uintptr_t uvalue)
{
	knh_Hash_t *hash = (knh_Hash_t*)o;
	knh_hashentry_t *e = knh_Hash_get__hcode(ctx, hash, hcode);
	if(e != NULL) {
		e->uvalue = uvalue;
		return;
	}
	knh_Hash_rehash(ctx, hash);
	e = new_hashentry(ctx, hash);
	e->hcode = hcode;
	KNH_INITv(e->key, KNH_NULL);
	e->uvalue = uvalue;
	knh_uintptr_t h = hcode % DP(o)->hmax;
	e->next = DP(o)->array[h];
	DP(o)->array[h] = e;
	DP(o)->size++;
}

///* ------------------------------------------------------------------------ */
///* @method void HashMap.clear() */
//
//void knh_HashMap_clear(Ctx *ctx, HashMap *o)
//{
//	int init = DP(o)->capacity;
//	knh_HashMap_traverse(ctx, DP(o), knh_Object_sweep);
//	knh_HashMap_init(ctx, DP(o), init, NULL);
//}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
