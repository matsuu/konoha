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
knh_DictIdx_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	DictIdx *b = (DictIdx*)s;
	if(init == 0) init = KNH_DICTMAP_INITSIZE;
	b->offset = 0;
	KNH_INITv(b->terms, new_Array(ctx, init));
	KNH_INITv(b->termsDictSet, new_DictSet(ctx, init));
}

/* ------------------------------------------------------------------------ */

#define _knh_DictIdx_struct_copy   NULL
#define _knh_DictIdx_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void
knh_DictIdx_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	DictIdx *b = (DictIdx*)s;
	gc(ctx, b->terms);
	gc(ctx, b->termsDictSet);
}

/* ======================================================================== */
/* [constructors] */


DictIdx* new_DictIdx(Ctx *ctx, size_t initialCapacity, knh_int_t offset)
{
	DictIdx* b = (DictIdx*)knh_Object_malloc0(ctx, KNH_FLAG_DictIdx, CLASS_DictIdx, sizeof(DictIdx));
	knh_DictIdx_struct_init(ctx, (Struct *)b, initialCapacity, NULL);
	b->offset = offset;
	return b;
}

///* ------------------------------------------------------------------------ */
//
///* @method DictIdx! DictIdx.new(Int initialCapacity=0, Int offset=0) */
//
//DictIdx* knh_DictIdx_new(Ctx *ctx, DictIdx *b, size_t initialCapacity, knh_uint_t offset)
//{
//	knh_DictIdx_struct_init(ctx, (Struct *)b, initialCapacity, NULL);
//	b->offset = offset;
//	return b;
//}


/* ======================================================================== */
/* [methods] */

//  Array             DictSet       termid
//  terms[0], "a"     "a" : idx=1   (idx-1)+offset
//  terms[1], "b"     "b" : idx=2   (idx-1)+offset

#define termid_toarrayn(termid)      (termid - b->offset)
#define termid_todictid(termid)      (termid - b->offset + 1)
#define dictid_toarrayn(dictid)      (dictid - 1)
#define dictid_totermid(dictid)      (dictid - 1 + b->offset)
#define arrayn_todictid(arrayn)      (arrayn + 1)
#define arrayn_totermid(arrayn)      (arrayn + b->offset)

/* ------------------------------------------------------------------------ */


/* @method Int! DictIdx.index(String! term) */

INLINE
knh_index_t knh_DictIdx_index(Ctx *ctx, DictIdx *b, knh_bytes_t v)
{
	knh_index_t dictid = (knh_index_t)knh_DictSet_get__b(b->termsDictSet, v);
	if(dictid == 0) return -1;
	return dictid_totermid(dictid);
}

/* ------------------------------------------------------------------------ */

/* @method Int! DictIdx.add::fast(String! term) */

INLINE
knh_index_t knh_DictIdx_add__fast(Ctx *ctx, DictIdx *b, String *term)
{
	knh_index_t dictid = (knh_index_t)knh_Array_size(b->terms) + 1;
	knh_Array_add(ctx, b->terms, term);
	knh_DictSet_put(ctx, b->termsDictSet, term, dictid);
	return dictid_totermid(dictid);
}

/* ------------------------------------------------------------------------ */

/* @method Int! DictIdx.add(String! term) */


knh_index_t knh_DictIdx_add(Ctx *ctx, DictIdx *b, String *term)
{
	knh_index_t dictid = 
		(knh_index_t)knh_DictSet_get__b(b->termsDictSet, knh_String_tobytes(term));
	if(dictid != 0) {
		knh_DictSet_put(ctx, b->termsDictSet, term, dictid); /* TO AVOID GC HERE */
		return dictid_totermid(dictid);
	}
	return knh_DictIdx_add__fast(ctx, b, term);
}

/* ------------------------------------------------------------------------ */


knh_index_t knh_DictIdx_add__b(Ctx *ctx, DictIdx *b, knh_bytes_t term)
{
	knh_index_t dictid = (knh_index_t)knh_DictSet_get__b(b->termsDictSet, term);
	if(dictid != 0) return dictid_totermid(dictid);
	return knh_DictIdx_add__fast(ctx, b, new_String__fast(ctx, CLASS_String, term));
}

/* ------------------------------------------------------------------------ */

/* @method String DictIdx.get::fast(Int! index) */

INLINE
String* knh_DictIdx_get__fast(DictIdx *b, knh_int_t termid)
{
	size_t n = termid_toarrayn(termid);
	KNH_FAST_ASSERT(0 <= n && n < knh_Array_size(b->terms));
	return knh_Array_n(b->terms, n);
}

/* ------------------------------------------------------------------------ */

/* @method String DictIdx.get(Int! index) */

INLINE
String* knh_DictIdx_get(DictIdx *b, knh_int_t termid)
{
	size_t n = termid_toarrayn(termid);
	if(0 <= n && n < knh_Array_size(b->terms)) {
		return knh_Array_n(b->terms, n);
	}
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

/* @method void DictIdx.clear() */


void knh_DictIdx_clear(Ctx *ctx, DictIdx *b)
{
	knh_Array_clear(ctx, b->terms);
	knh_DictSet_clear(ctx, b->termsDictSet);
}

/* ======================================================================== */
/* [mappings] */

/* @Map DictIdx Iterator! */


Object* knh_DictIdx_Iterator(Ctx *ctx, Object *self, MapMap *map)
{
	return knh_Array_Iterator(ctx, ((DictIdx*)self)->terms, KNH_NULL);
}

/* ======================================================================== */
/* [movabletext] */

/* @method void DictIdx.%dump(OutputStream w, Any m) */


void knh_DictIdx__dump(Ctx *ctx, DictIdx *b, OutputStream *w, Any *m)
{
	knh_Array__dump(ctx, b->terms, w, m);
}


#ifdef __cplusplus
}
#endif
