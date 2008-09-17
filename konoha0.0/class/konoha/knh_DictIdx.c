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
/* [structs] */

void
knh_DictIdx_struct_init(Ctx *ctx, knh_DictIdx_struct *b, int init, Object *cs)
{
	if(init == 0) init = KNH_DICTMAP_INITSIZE;
	b->offset = 0;
	if(ctx == NULL) {
		KNH_INITv(b->terms, new_Array0(ctx, init));
	}
	else {
		KNH_INITv(b->terms, new_Array(ctx, CLASS_String, init));
	}
	KNH_INITv(b->termsDictSet, new_DictSet(ctx, init));
}

/* ------------------------------------------------------------------------ */

#define _knh_DictIdx_struct_copy   NULL

/* ------------------------------------------------------------------------ */

void
knh_DictIdx_struct_traverse(Ctx *ctx, knh_DictIdx_struct *b, f_traverse gc)
{
	gc(ctx, UP(b->terms));
	gc(ctx, UP(b->termsDictSet));
}

/* ======================================================================== */
/* [constructors] */

DictIdx* new_DictIdx(Ctx *ctx, size_t initialCapacity, knh_int_t offset)
{
	knh_DictIdx_t* o = (DictIdx*)new_Object_malloc(ctx, FLAG_DictIdx, CLASS_DictIdx, sizeof(knh_DictIdx_struct));
	knh_DictIdx_struct_init(ctx, DP(o), initialCapacity, NULL);
	DP(o)->offset = offset;
	return o;
}

///* ------------------------------------------------------------------------ */
//
///* @method DictIdx! DictIdx.new(Int initialCapacity=0, Int offset=0) */
//
//DictIdx* knh_DictIdx_new(Ctx *ctx, DictIdx *b, size_t initialCapacity, knh_uint_t offset)
//{
//	knh_DictIdx_struct_init(ctx, (Struct *)b, initialCapacity, NULL);
//	DP(o)->offset = offset;
//	return b;
//}


/* ======================================================================== */
/* [methods] */

//  Array             DictSet       termid
//  terms[0], "a"     "a" : idx=1   (idx-1)+offset
//  terms[1], "b"     "b" : idx=2   (idx-1)+offset

#define termid_toarrayn(termid)      (termid - DP(o)->offset)
#define termid_todictid(termid)      (termid - DP(o)->offset + 1)
#define dictid_toarrayn(dictid)      (dictid - 1)
#define dictid_totermid(dictid)      (dictid - 1 + DP(o)->offset)
#define arrayn_todictid(arrayn)      (arrayn + 1)
#define arrayn_totermid(arrayn)      (arrayn + DP(o)->offset)

/* ------------------------------------------------------------------------ */


/* @method Int! DictIdx.index(String! term) */

INLINE
knh_index_t knh_DictIdx_index(Ctx *ctx, DictIdx *o, knh_bytes_t v)
{
	knh_index_t dictid = (knh_index_t)knh_DictSet_get__b(DP(o)->termsDictSet, v);
	if(dictid == 0) return -1;
	return dictid_totermid(dictid);
}

/* ------------------------------------------------------------------------ */

/* @method Int! DictIdx.add::fast(String! term) */

INLINE
knh_index_t knh_DictIdx_add__fast(Ctx *ctx, DictIdx *o, String *term)
{
	knh_index_t dictid = (knh_index_t)knh_Array_size(DP(o)->terms) + 1;
	knh_Array_add(ctx, DP(o)->terms, UP(term));
	knh_DictSet_put(ctx, DP(o)->termsDictSet, term, dictid);
	return dictid_totermid(dictid);
}

/* ------------------------------------------------------------------------ */
/* @method Int! DictIdx.add(String! term) */

knh_index_t knh_DictIdx_add(Ctx *ctx, DictIdx *o, String *term)
{
	knh_index_t dictid =
		(knh_index_t)knh_DictSet_get__b(DP(o)->termsDictSet, knh_String_tobytes(term));
	if(dictid != 0) {
		knh_DictSet_put(ctx, DP(o)->termsDictSet, term, dictid); /* TO AVOID GC HERE */
		return dictid_totermid(dictid);
	}
	return knh_DictIdx_add__fast(ctx, o, term);
}

/* ------------------------------------------------------------------------ */

knh_index_t knh_DictIdx_add__b(Ctx *ctx, DictIdx *o, knh_bytes_t term)
{
	knh_index_t dictid = (knh_index_t)knh_DictSet_get__b(DP(o)->termsDictSet, term);
	if(dictid != 0) return dictid_totermid(dictid);
	return knh_DictIdx_add__fast(ctx, o, new_String(ctx, term, NULL));
}

/* ------------------------------------------------------------------------ */

/* @method String DictIdx.get::fast(Int! index) */

INLINE
String* knh_DictIdx_get__fast(DictIdx *o, knh_int_t termid)
{
	size_t n = termid_toarrayn(termid);
	KNH_ASSERT(0 <= n && n < knh_Array_size(DP(o)->terms));
	return (String*)knh_Array_n(DP(o)->terms, n);
}

/* ------------------------------------------------------------------------ */

/* @method String DictIdx.get(Int! index) */

INLINE
String* knh_DictIdx_get(DictIdx *o, knh_int_t termid)
{
	size_t n = termid_toarrayn(termid);
	if(0 <= n && n < knh_Array_size(DP(o)->terms)) {
		return (String*)knh_Array_n(DP(o)->terms, n);
	}
	return (String*)KNH_NULL;
}

/* ------------------------------------------------------------------------ */

/* @method void DictIdx.clear() */


void knh_DictIdx_clear(Ctx *ctx, DictIdx *o)
{
	knh_Array_clear(ctx, DP(o)->terms);
	knh_DictSet_clear(ctx, DP(o)->termsDictSet);
}

///* ======================================================================== */
///* [mappings] */
//
///* @Map DictIdx Iterator! */
//
//Object* knh_DictIdx_Iterator(Ctx *ctx, Object *self, Mapper *map)
//{
//	return knh_Array_Iterator(ctx, ((DictIdx*)self)->terms, KNH_NULL);
//}

/* ======================================================================== */
/* [movabletext] */

/* @method void DictIdx.%k(OutputStream w, Any m) */

void knh_DictIdx__k(Ctx *ctx, DictIdx *o, OutputStream *w, Any *m)
{
	knh_Array__k(ctx, DP(o)->terms, w, m);
}

/* ======================================================================== */
/* [movabletext] */

#ifdef __cplusplus
}
#endif
