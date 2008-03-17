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

#include<stdarg.h>

/* ======================================================================== */
/* [macros] */

#define _Tuple                   Tuple1 
#define _TupleNULL               Tuple1NULL
#define _IS_STRUCT_Tuple(ctx,o)        (knh_Object_topsid(ctx,o) < STRUCT_Prototype)
#define _IS_Tuple(o)             (knh_Object_cid(o) < CLASS_Prototype)
#define _ISA_Tuple(ctx,o)        (knh_Object_cid(o) < CLASS_Prototype)
#define _DEBUG_Tuple             DEBUG_Tuple1

/* ======================================================================== */
/* [structs] */

void
knh_Tuple0_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
}

/* ------------------------------------------------------------------------ */

void
knh_Tuple0_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
}

/* ------------------------------------------------------------------------ */

knh_int_t
knh_Tuple0_struct_compare(Ctx *ctx, Struct *s1, Struct *s2) 
{
	return s1 - s2;
}

/* ------------------------------------------------------------------------ */

void
knh_Tuple0_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
}

/* ======================================================================== */
/* [field] */

void
knh__Tuple_get_field(Ctx *ctx, Object **sf)
{
	Tuple1 *t = (Tuple1*)knh_stackf_structDelta(ctx, sf);
	KNH_SETr(ctx, sf, t->v[0]);
}

/* ------------------------------------------------------------------------ */

void
knh__Tuple_set_field(Ctx *ctx, Object **sf)
{
	Tuple1 *t = (Tuple1*)knh_stackf_structDelta(ctx, sf);
	KNH_SETv(ctx, t->v[0], sf[1]);
	KNH_SETr_void(ctx, sf);
}

/* ======================================================================== */
/* [constructors] */

/* @method[VARARGS] Tuple! Tuple.new(Any value) */

Tuple* knh_Tuple_new(Ctx *ctx, Tuple *b, knh_vargc_t ac, Any **value)
{
	DEBUG_ASSERT(knh_Object_cid(b) == ac);
	knh_int_t i;
	for(i = 0; i < ac; i++) {
		KNH_INITv(b->v[i], value[i+1]);
	}
	return b;
}

/* ------------------------------------------------------------------------ */

//#define _knh_Tuple2_new(ctx,o1,o2) new_Tuple(ctx,o1,o2,NULL)
//
//Tuple* new_Tuple(Ctx *ctx, ...)
//{
//	va_list args; knh_class_t cid = 0;
//	Object *t[CLASS_Prototype]; 
//	va_start(args , ctx);
//	while((t[cid] = va_arg(args, Object*)) != NULL) {
//		cid++;
//		if(cid == CLASS_Prototype - 1) break;  /* for safety */
//	}
//	va_end(args);
//	
//	if(cid == 0) return KNH_NULL;
//	int i;
//	Tuple *b = (Tuple*)knh_Object_malloc(ctx, cid);
//	for(i = 0; i < cid; i++) {
//		KNH_INITv(b[i], t[i]);
//	}
//	return (Object*)b;
//}


/* ======================================================================== */
/* [methods] */

/* @method Int! Tuple.getSize() */

#define _knh_Tuple_size(b)  knh_Tuple_getSize(b)

INLINE
size_t knh_Tuple_getSize(Tuple *b)
{
	DEBUG_ASSERT(knh_Object_cid(b) < CLASS_Prototype);
	return (knh_Object_cid(b));
}

/* ------------------------------------------------------------------------ */

/* @method Any Tuple.get::fast(Int! index) */


Object *knh_Tuple_get__fast(Tuple *b, knh_int_t index)
{
	return KNH_FIELDn(b, index);
}

/* ------------------------------------------------------------------------ */

/* @method Any Tuple.get(Int! index) */


Object *knh_Tuple_get(Tuple *b, knh_int_t index)
{
	return KNH_FIELDn(b, knh_array_index(index, knh_Tuple_size(b)));
}

/* ======================================================================== */
/* [mappings] */

/* ------------------------------------------------------------------------ */

/* @map Array Tuple! */


Object* knh_Array_Tuple(Ctx *ctx, Object *self, MapMap *map)
{
	Array *b = (Array*)self;
	knh_class_t cid = knh_int_min(knh_Array_size(b), CLASS_Prototype - 1);
	if(cid == 0) return KNH_NULL;
	Tuple *t = (Tuple*)knh_Object_malloc(ctx, cid);
	size_t i;
	for(i = 0; i < cid; i++) {
		KNH_INITv(t->v[i], knh_Array_n(b,i));
	}
	return t;
}

/* ======================================================================== */
/* [iterators] */

Object*
knh_Tuple_next(Ctx *ctx, Iterator *it)
{
	Tuple *b = (Tuple*)knh_Iterator_source(it);
	size_t pos ;
	for(pos = knh_Iterator_pos(it); pos < knh_Tuple_size(b); pos++) {
		if(IS_NOTNULL(KNH_FIELDn(b, pos))) {
			knh_Iterator_setpos(it,pos+1);
			return KNH_FIELDn(b, pos);
		}
	}		
	knh_Iterator_setpos(it,pos+1);
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

/* @Map Tuple Iterator! */


Object* knh_Tuple_Iterator(Ctx *ctx, Object *self, MapMap *map)
{
	return new_Iterator(ctx, CLASS_Any, self, knh_Tuple_next);	
}

/* ======================================================================== */
/* [movabletext] */


/* @method void Tuple.%dump(OutputStream w, Any m) */


void knh_Tuple__dump(Ctx *ctx, Tuple *b, OutputStream *w, Any *m)
{
//	knh_fputc(ctx, w, '(');
//	size_t c;
//	for(c = 0; c < knh_Tuple_size(b); c++) {
//		if(c > 0) {
//			knh_print_delim(ctx, w);
//		}
//		knh_Object__dump(ctx, KNH_FIELDn(b, c), w, lv+1);
//		c++;
//	}
//	knh_fputc(ctx, w, ')');
}




#ifdef __cplusplus
}
#endif
