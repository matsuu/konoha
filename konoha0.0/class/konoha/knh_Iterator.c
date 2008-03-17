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
/* [macros] */

#define _knh_Iterator_cid(it)          (((Iterator*)it)->cid)
#define _knh_Iterator_source(it)       (((Iterator*)it)->source)
#define _knh_Iterator_setsource(ctx, it, s)    KNH_SETv(ctx, (((Iterator*)it)->pos), s)
#define _knh_Iterator_pos(it)          (((Iterator*)it)->pos)
#define _knh_Iterator_setpos(it, size)  ((Iterator*)it)->pos = (size)
#define _knh_Iterator_ref(it)          (((Iterator*)it)->ref)
#define _knh_Iterator_setref(it, rr)       ((Iterator*)it)->ref = (rr)

/* ======================================================================== */
/* [structs] */

void
knh_Iterator_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	Iterator *b  = (Iterator*)s1;
	b->cid    =  0;
	b->flag   =  0;
	b->fnext  =  knh_Object_single_next;
	b->feach  =  knh_Iterator_each;
	KNH_INITv(b->source, KNH_NULL);
	b->pos    =  0;
	b->ref    =  NULL; 
	b->count = 0;
	b->start = 0;
	b->end   = (size_t)-1;
}

/* ------------------------------------------------------------------------ */

void
knh_Iterator_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
	Iterator *b  = (Iterator*)s1;
	Iterator *b2 = (Iterator*)s2;
	b2->cid      = b->cid;
	b2->flag     = b->flag;
	b2->fnext    = b->fnext;
	b2->feach    = b->feach;
	b2->pos      = b->pos;
	b2->ref      = b->ref;
	KNH_INITv(b2->source, b->source);
	b2->count = b->count;
	b2->start = b->start;
	b2->end   = b->end;
}

/* ------------------------------------------------------------------------ */

#define _knh_Iterator_struct_compare NULL

/* ------------------------------------------------------------------------ */

void
knh_Iterator_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Iterator *b = (Iterator*)s;
	gc(ctx, b->source);
}

/* ======================================================================== */
/* [constructors] */

Object *
knh_Object_single_next(Ctx *ctx, Iterator *it)
{
	if(knh_Iterator_pos(it) == 0) {
		knh_Iterator_setpos(it, 1);
		return knh_Iterator_source(it);
	}
	return KNH_NULL;		
}

/* ------------------------------------------------------------------------ */


Iterator* new_Iterator(Ctx *ctx, knh_class_t cid, Object *source, f_next f)
{
	Iterator *b = (Iterator*)knh_Object_malloc(ctx, CLASS_Iterator);
	knh_Iterator_struct_init(ctx, (Struct *)b, 0, NULL);
	b->cid    =  cid;
	b->fnext  =  f == NULL ? knh_Object_single_next : f;
	KNH_SETv(ctx, b->source, source);
	return b;
}

/* ------------------------------------------------------------------------ */

Object *knh_Iterator_fvalue(Ctx *ctx, knh_class_t cid)
{
	return new_Iterator(ctx, cid, KNH_NULL, knh_Object_single_next);
}

/* ------------------------------------------------------------------------ */

Object* knh_MapMap_fmap__Iterator(Ctx *ctx, Object *self, MapMap *map)
{
	return new_Iterator(ctx, knh_Object_cid(self), self, knh_Object_single_next);
}

/* ======================================================================== */
/* [object] */

knh_class_t knh_Object_pcid(Object *b)
{
	if(IS_Iterator(b)) {
		Iterator *it = (Iterator*)b;
		if(it->cid == CLASS_any) {
			return CLASS_Iterator;
		}
		return CLASS_TOPLURAL(it->cid);
	}
	else {
		return knh_Object_cid(b);
	}
}

/* ======================================================================== */
/* [foreach] */

INLINE
Object *knh_Iterator_foreach(Ctx *ctx, Iterator *b, knh_class_t cid)
{
	return b->feach(ctx, b, cid);
}

/* ======================================================================== */
/* [next] */

Object *knh_Iterator_each(Ctx *ctx, Iterator *b, knh_class_t cid)
{
	Object *v = b->fnext(ctx, b);
	while(IS_NOTNULL(v)) {
		if(knh_Object_opInstanceof(ctx, v, cid)) {
			return v;
		}
		v = b->fnext(ctx, b);
	}
	return v; /* KNH_NULL */
}

/* ------------------------------------------------------------------------ */

INLINE
Object *knh_Iterator_each__slice(Ctx *ctx, Iterator *b, knh_class_t cid)
{
	Object *v = b->fnext(ctx, b);
	while(IS_NOTNULL(v)) {
		if(knh_Object_opInstanceof(ctx, v, cid)) {
			if(b->count > b->end) {
				return KNH_NULL;
			}
			b->count++;
			if(b->count < b->start) {
				continue;
			}
			return v;
		}
		v = b->fnext(ctx,b);
	}
	return v; /* KNH_NULL */
}

/* ------------------------------------------------------------------------ */


Object *knh_Iterator_each__map(Ctx *ctx, Iterator *b, knh_class_t tcid)
{
//	TODO();
//	Object *v, *v2;
//	while((v = b->fnext(ctx, b)) != KNH_NULL) {
//		v2 = knh_Object_mapto(ctx, v, tcid);
//		if(v != v2) knh_Object_safefree(ctx, v);
//		if(v2 != KNH_NULL) return v2;
//		knh_Object_safefree(ctx, v2);
//	}
	return KNH_NULL;
}

/* ======================================================================== */
/* [slice] */

//
//void knh_Iterator_setslice(Iterator *b, size_t start, size_t end)
//{
//	b->flag = IF_SLICE | b->flag;
//	b->count = 0;
//	b->start = start;
//	b->end   = end;
//	b->feach = knh_Iterator_each__slice;
//}

/* ======================================================================== */
/* [mappings] */

/* @map Iterator Array! */

Object* knh_Iterator_Array(Ctx *ctx, Object *self, MapMap *map)
{
	Iterator *b = (Iterator*)self;
	Array *a = new_Array(ctx, 0);
	if(b->cid == CLASS_any) {
		Object *v = b->fnext(ctx, b);
		while(IS_NOTNULL(v)) {
			knh_Array_append(ctx, a, v);
			v = b->fnext(ctx, b);
		}
	}else {
		Object *v = knh_Iterator_foreach(ctx, b, b->cid);
		while(IS_NOTNULL(v)) {
			knh_Array_append(ctx, a, v);
			v = knh_Iterator_foreach(ctx, b, b->cid);
		}
	}
	return a;
}

/* ======================================================================== */
/* [movabletext] */

///* @method void Iterator.%s(OutputStream w, Any m) */
//
//void knh_Iterator__s(Ctx *ctx, Iterator *b, OutputStream *w, Any *m)
//{
//	knh_methodn_t mn = METHODN__s;
//	Any *m2 = m;
//	if(IS_NOTNULL(m)) {
//		knh_bytes_t n = knh_String_tobytes(m);
//		if(n.buf[0] == '%') {
//			knh_index_t loc = knh_bytes_index(n, '.');
//			if(loc > 0) {
//				mn = knh_tmethodn_forname(ctx, knh_bytes_first(n, loc), METHODN__empty);
//				m2 = new_String__fast(ctx, CLASS_String, knh_bytes_last(n, loc+1));
//			}
//			else {
//				mn = knh_tmethodn_forname(ctx, n, METHODN__empty);
//			}
//		}
//	}
//	KNH_LOPEN(ctx, 0);
//	KNH_LPUSH(ctx, m2);
//	knh_putc(ctx, w, '[');
//	size_t c = 0;
//	Object *v = knh_Iterator_foreach(ctx, b, b->cid);
//	while(IS_NOTNULL(v)) {
//		if(c > 0) {
//			knh_write_delim(ctx,w);
//		}
//		knh_format(ctx, w, mn, v, m2);
//		v = knh_Iterator_foreach(ctx, b, b->cid);
//		c++;
//	}
//	knh_putc(ctx, w, ']');
//	KNH_LCLOSE(ctx);
//}

/* ------------------------------------------------------------------------ */

/* @method void Iterator.%dump(OutputStream w, Any m) */

void knh_Iterator__dump(Ctx *ctx, Iterator *b, OutputStream *w, Any *m)
{
	knh_putc(ctx, w, '[');
	size_t c = 0;
	Object *v = b->fnext(ctx, b);
	while(IS_NOTNULL(v)) {
		if(c > 0) {
			knh_write_delim(ctx,w);
		}
		//knh_printf(ctx, w, "(#%d)", c);
		knh_format(ctx, w, METHODN__dump, v, KNH_NULL);
		if(!knh_array_isdump(c)) {
			break;
		}
		v = b->fnext(ctx, b);
		c++;
	}
	knh_write_dots(ctx, w);
	knh_putc(ctx, w, ']');
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
