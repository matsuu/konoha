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
/* [constructors] */

DictIdx* new_DictIdx0(Ctx *ctx, size_t init, knh_intptr_t offset)
{
	knh_DictIdx_t *o = (knh_DictIdx_t*)new_hObject(ctx, FLAG_DictIdx, CLASS_DictIdx, CLASS_DictIdx);
	KNH_INITv(o->terms, new_Array0(ctx, init));
	KNH_INITv(o->termsDictSet, new_DictSet(ctx, init));
	o->offset = offset;
	return o;
}

/* ------------------------------------------------------------------------ */

DictIdx* new_DictIdx0__ignoreCase(Ctx *ctx, size_t init, knh_intptr_t offset)
{
	DictIdx *o = new_DictIdx0(ctx, init, offset);
	knh_DictSet_toIgnoreCase(o->termsDictSet);
	return o;
}

/* ======================================================================== */
/* [methods] */

//  Array             DictSet       termid
//  terms[0], "a"     "a" : idx=1   (idx-1)+offset
//  terms[1], "b"     "b" : idx=2   (idx-1)+offset

#define termid_toarrayn(termid)      (termid - o->offset)
#define termid_todictid(termid)      (termid - o->offset + 1)
#define dictid_toarrayn(dictid)      (dictid - 1)
#define dictid_totermid(dictid)      (dictid - 1 + o->offset)
#define arrayn_todictid(arrayn)      (arrayn + 1)
#define arrayn_totermid(arrayn)      (arrayn + o->offset)

/* ------------------------------------------------------------------------ */
/* @method Int! DictIdx.size() */

size_t knh_DictIdx_size(DictIdx *o)
{
	return knh_Array_size(o->terms);
}

/* ------------------------------------------------------------------------ */
/* @method Int! DictIdx.index(String! term) */

knh_index_t knh_DictIdx_index(Ctx *ctx, DictIdx *o, knh_bytes_t v)
{
	knh_index_t dictid = (knh_index_t)knh_DictSet_get__b(o->termsDictSet, v);
	if(dictid == 0) return -1;
	return dictid_totermid(dictid);
}

/* ------------------------------------------------------------------------ */
/* @method Int! DictIdx.add::fast(String! term) */

knh_index_t knh_DictIdx_add__fast(Ctx *ctx, DictIdx *o, String *term)
{
	knh_index_t dictid = (knh_index_t)knh_Array_size(o->terms) + 1;
	knh_Array_add(ctx, o->terms, UP(term));
	knh_DictSet_set(ctx, o->termsDictSet, term, dictid);
	return dictid_totermid(dictid);
}

/* ------------------------------------------------------------------------ */
/* @method Int! DictIdx.add(String! term) */

knh_index_t knh_DictIdx_add(Ctx *ctx, DictIdx *o, String *term)
{
	knh_index_t dictid =
		(knh_index_t)knh_DictSet_get__b(o->termsDictSet, knh_String_tobytes(term));
	if(dictid != 0) {
		knh_DictSet_set(ctx, o->termsDictSet, term, dictid); /* TO AVOID GC HERE */
		return dictid_totermid(dictid);
	}
	return knh_DictIdx_add__fast(ctx, o, term);
}

/* ------------------------------------------------------------------------ */

knh_index_t knh_DictIdx_add__b(Ctx *ctx, DictIdx *o, knh_bytes_t term)
{
	knh_index_t dictid = (knh_index_t)knh_DictSet_get__b(o->termsDictSet, term);
	if(dictid != 0) return dictid_totermid(dictid);
	return knh_DictIdx_add__fast(ctx, o, new_String(ctx, term, NULL));
}

/* ------------------------------------------------------------------------ */
/* @  method String DictIdx.get::fast(Int! index) */

String* knh_DictIdx_get__fast(DictIdx *o, knh_intptr_t termid)
{
	size_t n = termid_toarrayn(termid);
	KNH_ASSERT(/*0 <= n &&*/ n < knh_Array_size(o->terms));
	return (String*)knh_Array_n(o->terms, n);
}

/* ------------------------------------------------------------------------ */
/* @  method String DictIdx.get(Int! index) */

String* knh_DictIdx_get(Ctx *ctx, DictIdx *o, knh_intptr_t termid)
{
	size_t n = termid_toarrayn(termid);
	if(/*0 <= n &&*/ n < knh_Array_size(o->terms)) {
		return (String*)knh_Array_n(o->terms, n);
	}
	return (String*)KNH_NULL;
}

/* ------------------------------------------------------------------------ */

/* @method void DictIdx.clear() */


void knh_DictIdx_clear(Ctx *ctx, DictIdx *o)
{
	knh_Array_clear(ctx, o->terms);
	knh_DictSet_clear(ctx, o->termsDictSet);
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


/* ======================================================================== */
/* [movabletext] */

#ifdef __cplusplus
}
#endif
