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

#ifdef KNH_CC_METHODAPI

/* ======================================================================== */
/* [DictMap] */

/* ------------------------------------------------------------------------ */
/* @method This! DictMap.new(Int n) */

static METHOD knh__DictMap_new(Ctx *ctx, knh_sfp_t *sfp)
{
	DictMap *o = (DictMap*)sfp[0].o;
	size_t init = IS_NULL(sfp[1].o) ? KNH_DICT_INITSIZE: p_int(sfp[1]);
	if(init > 0) {
		o->_list = knh_dictmap_malloc(ctx, init);
		o->size = 0;
	}
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] This! DictMap.new:init(T1 value) @VARARGS */

static METHOD knh__DictMap_new__init(Ctx *ctx, knh_sfp_t *sfp)
{
	DictMap *o = (DictMap*)sfp[0].o;
	knh_sfp_t *v = sfp + 1;
	int ac = knh_stack_argc(ctx, v);
	size_t i;
	for(i = 0; i < ac; i+=2) {
		if(IS_bString(v[i].s)) {
			knh_sfp_boxing(ctx, v + i + 1);
			knh_DictMap_append(ctx, o, v[i].s, v[i+1].o);
		}
	}
	knh_DictMap_sort(o);
	KNH_RETURN(ctx, sfp, o);
}

/* ======================================================================== */
/* [method] */

/* ------------------------------------------------------------------------ */
/* @method T1 DictMap.get(String! key) */

static METHOD knh__DictMap_get(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, knh_DictMap_get(ctx, (DictMap*)sfp[0].o, sfp[1].s));
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! DictMap.opHas(String! key) */

static METHOD knh__DictMap_opHas(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_DictMap_index((DictMap*)sfp[0].o, knh_String_tobytes(sfp[1].s)) != -1);
}

/* ------------------------------------------------------------------------ */
/* @method void DictMap.set(String! key, T1 value) */

static METHOD knh__DictMap_set(Ctx *ctx, knh_sfp_t *sfp)
{
	DictMap *o = (DictMap*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		knh_sfp_boxing(ctx, sfp + 2);
		knh_DictMap_set(ctx, o, sfp[1].s, sfp[2].o);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void DictMap.remove(String! key) */

static METHOD knh__DictMap_remove(Ctx *ctx, knh_sfp_t *sfp)
{
	DictMap *o = (DictMap*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		knh_DictMap_remove(ctx, o, sfp[1].s);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void DictMap.clear() */

static METHOD knh__DictMap_clear(Ctx *ctx, knh_sfp_t *sfp)
{
	DictMap *o = (DictMap*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		knh_DictMap_clear(ctx, o);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ======================================================================== */
/* @method Int! DictMap.getSize() */

static METHOD knh__DictMap_getSize(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Int(ctx, sfp, knh_DictMap_size((DictMap*)sfp[0].o));
}

/* ------------------------------------------------------------------------ */
//
//#define OPSUBSET   0
//#define OPSUBSETE  1
//#define OPOFFSET   2
//
//static METHOD knh__DictMap_subset(Ctx *ctx, knh_sfp_t *sfp, int mode)
//{
//	DictMap *o = (DictMap*)sfp[0].o;
//	size_t i, s = 0, e = o->size;
//	if(IS_NOTNULL(sfp[1].o)) {
//		knh_bytes_t cs = knh_String_tobytes(sfp[1].s);
//		for(i = 0; i < o->size; i++) {
//			knh_bytes_t ks = knh_String_tobytes(knh_DictMap_keyAt(o, i));
//			if(knh_bytes_strcmp(cs, ks) <= 0) {
//				s = i;
//			}
//			else {
//				break;
//			}
//		}
//	}
//	if(IS_NOTNULL(sfp[2].o)) {
//		if(mode == OPSUBSETE) {
//			knh_bytes_t cs = knh_String_tobytes(sfp[2].s);
//			for(i = s; i < o->size; i++) {
//				knh_bytes_t ks = knh_String_tobytes(knh_DictMap_keyAt(o, i));
//				if(knh_bytes_strcmp(ks, cs) <= 0) {
//					continue;
//				}
//				else {
//					e = i;
//					break;
//				}
//			}
//		}
//		else if(mode == OPSUBSET) {
//			knh_bytes_t cs = knh_String_tobytes(sfp[2].s);
//			for(i = s; i < o->size; i++) {
//				knh_bytes_t ks = knh_String_tobytes(knh_DictMap_keyAt(o, i));
//				if(knh_bytes_strcmp(ks, cs) < 0) {
//					continue;
//				}
//				else {
//					e = i;
//					break;
//				}
//			}
//		}
//		else {
//			e = s + p_int(sfp[2]);
//			if(!(e < o->size)) {
//				e = o->size;
//			}
//			else if(e < s) {
//				e = s;
//			}
//		}
//	}
//	{
//		DictMap *d = new_DictMap(ctx, ctx->share->ClassTable[knh_Object_cid(o)].p1, e - s);
//		for(i = s; i < e; i++) {
//			knh_DictMap_append(ctx, d, knh_DictMap_keyAt(o, i), knh_DictMap_valueAt(o, i));
//		}
//		KNH_RETURN(ctx, sfp, d);
//	}
//}
//
///* ------------------------------------------------------------------------ */
///* @method This! DictMap.opSubsete(String s, String e) */
//
//static METHOD knh__DictMap_opSubsete(Ctx *ctx, knh_sfp_t *sfp)
//{
//	knh__DictMap_subset(ctx, sfp, OPSUBSETE);
//}
//
///* ------------------------------------------------------------------------ */
///* @method This! DictMap.opSubset(String s, String e) */
//
//static METHOD knh__DictMap_opSubset(Ctx *ctx, knh_sfp_t *sfp)
//{
//	knh__DictMap_subset(ctx, sfp, OPSUBSET);
//}
//
///* ------------------------------------------------------------------------ */
///* @method This! DictMap.opOffset(String s, Int! n) */
//
//static METHOD knh__DictMap_opOffset(Ctx *ctx, knh_sfp_t *sfp)
//{
//	knh__DictMap_subset(ctx, sfp, OPOFFSET);
//}

/* ------------------------------------------------------------------------ */

static String* knh_Object_key(Ctx *ctx, Object *o)
{
	switch(o->h.bcid) {
	case CLASS_String:
		return (String*)o;
	}
	{
		char buf[80];
		knh_snprintf(buf, sizeof(buf), "&%p", o);
		return new_String(ctx, B(buf), NULL);
	}
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] void DictMap.opLshift(Any v) @VARARGS */

static METHOD knh__DictMap_opLshift(Ctx *ctx, knh_sfp_t *sfp)
{
	DictMap *o = (DictMap*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		knh_sfp_t *v = sfp + 1;
		int ac = knh_stack_argc(ctx, v);
		size_t i;
		for(i = 0; i < ac; i++) {
			if(IS_NULL(v[1].o)) continue;
			String *key = knh_Object_key(ctx, v[i].o);
			knh_sfp_boxing(ctx, v + i);
			knh_DictMap_append(ctx, o, key, v[i].o);
		}
		knh_DictMap_sort(o);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [mapping] */

/* ======================================================================== */
/* [iterators] */

static ITRNEXT knh_DictMap_key_next(Ctx *ctx, knh_sfp_t *sfp, int n)
{
	Iterator *it = sfp[0].it;
	DictMap *o = (DictMap*)DP(it)->source;
	size_t pos;
	for(pos = DP(it)->pos; pos < o->size; pos++) {
		if(IS_NOTNULL(o->list[pos].value)) {
			DP(it)->pos = pos+1;
			KNH_ITRNEXT(ctx, sfp, n, (Object*)o->list[pos].key);
		}
	}
	DP(it)->pos = pos;
	KNH_ITREND(ctx, sfp, n);
}

/* ------------------------------------------------------------------------ */
/* @map DictMap Iterator! */

static MAPPER knh_DictMap_Iterator(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_DictMap_sort((DictMap*)sfp[0].o);
	KNH_MAPPED(ctx, sfp, new_Iterator(ctx, CLASS_String, sfp[0].o, knh_DictMap_key_next));
}

/* ------------------------------------------------------------------------ */
/* @map DictMap String..! */

static MAPPER knh_DictMap_Iterator__(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_DictMap_sort((DictMap*)sfp[0].o);
	KNH_MAPPED(ctx, sfp, new_Iterator(ctx, CLASS_String, sfp[0].o, knh_DictMap_key_next));
}

/* ------------------------------------------------------------------------ */
/* @method String.. DictMap.opItr() */

static METHOD knh__DictMap_opItr(Ctx *ctx, knh_sfp_t *sfp)
{
	DictMap *o = (DictMap*)sfp[0].o;
	knh_DictMap_sort(o);
	KNH_RETURN(ctx, sfp, new_Iterator(ctx, CLASS_String, UP(o), knh_DictMap_key_next));
}

/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */
/* @method void DictMap.%k(OutputStream w, String m) */

static void knh_DictMap__k(Ctx *ctx, DictMap *o, OutputStream *w, String *m)
{
	knh_DictMap_sort(o);
	knh_putc(ctx, w, '{');
	size_t c;
	for(c = 0; c < o->size; c++) {
		if(c > 0) {
			knh_write_delim(ctx, w);
		}
		knh_write(ctx, w, knh_String_tobytes(o->list[c].key));
		knh_putc(ctx, w, ':');	knh_putc(ctx, w, ' ');
		knh_format(ctx, w, METHODN__k, o->list[c].value, KNH_NULL);
	}
	knh_putc(ctx, w, '}');
}


/* ======================================================================== */
/* [DictSet] */

/* ------------------------------------------------------------------------ */
/* @method This! DictSet.new(Int n) */

static METHOD knh__DictSet_new(Ctx *ctx, knh_sfp_t *sfp)
{
	DictSet *o = (DictSet*)sfp[0].o;
	size_t init = IS_NULL(sfp[1].o) ? KNH_DICT_INITSIZE: p_int(sfp[1]);
	if(init > 0) {
		o->_list = knh_dictset_malloc(ctx, init);
		o->size = 0;
	}
	KNH_RETURN(ctx, sfp, o);
}

/* ======================================================================== */
/* [method] */

/* ------------------------------------------------------------------------ */
/* @method void DictSet.add(String! key) */

static METHOD knh__DictSet_add(Ctx *ctx, knh_sfp_t *sfp)
{
	DictSet *o = (DictSet*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		knh_DictSet_add(ctx, o, sfp[1].s);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method Int! DictSet.get(String! key) */

static METHOD knh__DictSet_get(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Int(ctx, sfp, knh_DictSet_get(ctx, (DictSet*)sfp[0].o, sfp[1].s));
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! DictSet.opHas(String! key) */

static METHOD knh__DictSet_opHas(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_DictSet_get__b((DictSet*)sfp[0].o, knh_String_tobytes(sfp[1].s)) != 0);
}

/* ------------------------------------------------------------------------ */
/* @method void DictSet.set(String! key, Int! value) */

static METHOD knh__DictSet_set(Ctx *ctx, knh_sfp_t *sfp)
{
	DictSet *o = (DictSet*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		knh_DictSet_set(ctx, o, sfp[1].s, p_int(sfp[2]));
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void DictSet.remove(String! key) */

static METHOD knh__DictSet_remove(Ctx *ctx, knh_sfp_t *sfp)
{
	DictSet *o = (DictSet*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		knh_DictSet_remove(ctx, o, sfp[1].s);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void DictSet.clear() */

static METHOD knh__DictSet_clear(Ctx *ctx, knh_sfp_t *sfp)
{
	DictSet *o = (DictSet*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		knh_DictSet_clear(ctx, o);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ======================================================================== */
/* @method Int! DictSet.getSize() */

static METHOD knh__DictSet_getSize(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Int(ctx, sfp, knh_DictSet_size((DictSet*)sfp[0].o));
}

///* ------------------------------------------------------------------------ */
//
//#define OPSUBSET   0
//#define OPSUBSETE  1
//#define OPOFFSET   2
//
//static METHOD knh__DictSet_subset(Ctx *ctx, knh_sfp_t *sfp, int mode)
//{
//	DictSet *o = (DictSet*)sfp[0].o;
//	size_t i, s = 0, e = o->size;
//	if(IS_NOTNULL(sfp[1].o)) {
//		knh_bytes_t cs = knh_String_tobytes(sfp[1].s);
//		for(i = 0; i < o->size; i++) {
//			knh_bytes_t ks = knh_String_tobytes(knh_DictSet_keyAt(o, i));
//			if(knh_bytes_strcmp(cs, ks) <= 0) {
//				s = i;
//			}
//			else {
//				break;
//			}
//		}
//	}
//	if(IS_NOTNULL(sfp[2].o)) {
//		if(mode == OPSUBSETE) {
//			knh_bytes_t cs = knh_String_tobytes(sfp[2].s);
//			for(i = s; i < o->size; i++) {
//				knh_bytes_t ks = knh_String_tobytes(knh_DictSet_keyAt(o, i));
//				if(knh_bytes_strcmp(ks, cs) <= 0) {
//					continue;
//				}
//				else {
//					e = i;
//					break;
//				}
//			}
//		}
//		else if(mode == OPSUBSET) {
//			knh_bytes_t cs = knh_String_tobytes(sfp[2].s);
//			for(i = s; i < o->size; i++) {
//				knh_bytes_t ks = knh_String_tobytes(knh_DictSet_keyAt(o, i));
//				if(knh_bytes_strcmp(ks, cs) < 0) {
//					continue;
//				}
//				else {
//					e = i;
//					break;
//				}
//			}
//		}
//		else {
//			e = s + p_int(sfp[2]);
//			if(!(e < o->size)) {
//				e = o->size;
//			}
//			else if(e < s) {
//				e = s;
//			}
//		}
//	}
//	{
//		DictSet *d = new_DictSet(ctx, e - s);
//		for(i = s; i < e; i++) {
//			knh_DictSet_append(ctx, d, knh_DictSet_keyAt(o, i), knh_DictSet_valueAt(o, i));
//		}
//		KNH_RETURN(ctx, sfp, d);
//	}
//}
//
///* ------------------------------------------------------------------------ */
///* @method This! DictSet.opSubsete(String s, String e) */
//
//static METHOD knh__DictSet_opSubsete(Ctx *ctx, knh_sfp_t *sfp)
//{
//	knh__DictSet_subset(ctx, sfp, OPSUBSETE);
//}
//
///* ------------------------------------------------------------------------ */
///* @method This! DictSet.opSubset(String s, String e) */
//
//static METHOD knh__DictSet_opSubset(Ctx *ctx, knh_sfp_t *sfp)
//{
//	knh__DictSet_subset(ctx, sfp, OPSUBSET);
//}
//
///* ------------------------------------------------------------------------ */
///* @method This! DictSet.opOffset(String s, Int! n) */
//
//static METHOD knh__DictSet_opOffset(Ctx *ctx, knh_sfp_t *sfp)
//{
//	knh__DictSet_subset(ctx, sfp, OPOFFSET);
//}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] void DictSet.opLshift(String v) @VARARGS */

static METHOD knh__DictSet_opLshift(Ctx *ctx, knh_sfp_t *sfp)
{
	DictSet *o = (DictSet*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		knh_sfp_t *v = sfp + 1;
		int ac = knh_stack_argc(ctx, v);
		size_t i;
		for(i = 0; i < ac; i++) {
			if(IS_NULL(v[1].o)) continue;
			knh_DictSet_append(ctx, o, v[i].s, 1);
		}
		knh_DictSet_sort(o);
	}
	KNH_RETURN_void(ctx, sfp);
}


/* ------------------------------------------------------------------------ */
/* @map DictSet Iterator! @Const @Final */

static MAPPER knh_DictSet_Iterator(Ctx *ctx, knh_sfp_t *sfp)
{
	DictSet *o = (DictSet*)sfp[0].o;
	knh_DictSet_sort(o);
	KNH_MAPPED(ctx, sfp, new_Iterator(ctx, CLASS_String, UP(o), knh_DictMap_key_next));
}

/* ------------------------------------------------------------------------ */
/* @map DictSet String..! @Const @Final */

static MAPPER knh_DictSet_String__(Ctx *ctx, knh_sfp_t *sfp)
{
	DictSet *o = (DictSet*)sfp[0].o;
	knh_DictSet_sort(o);
	KNH_MAPPED(ctx, sfp, new_Iterator(ctx, CLASS_String, UP(o), knh_DictMap_key_next));
}

/* ------------------------------------------------------------------------ */
/* @method String.. DictSet.opItr() */

static METHOD knh__DictSet_opItr(Ctx *ctx, knh_sfp_t *sfp)
{
	DictSet *o = (DictSet*)sfp[0].o;
	knh_DictSet_sort(o);
	KNH_RETURN(ctx, sfp, new_Iterator(ctx, CLASS_String, UP(o), knh_DictMap_key_next));
}

/* ------------------------------------------------------------------------ */
/* @map String.. DictSet! @Final */

static MAPPER knh_String___DictSet(Ctx *ctx, knh_sfp_t *sfp)
{
	Iterator *it = sfp[0].it;
	DictSet *d = new_DictSet(ctx, 8);
	while(it->fnext_1(ctx, sfp, 1)) {
		knh_DictSet_add(ctx, d, sfp[1].s);
	}
	KNH_MAPPED(ctx, sfp, d);
}

/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */
/* @method void DictSet.%k(OutputStream w, String m) */

static void knh_DictSet__k(Ctx *ctx, DictSet *o, OutputStream *w, String *m)
{
	knh_DictSet_sort(o);
	knh_putc(ctx, w, '{');
	size_t c;
	for(c = 0; c < o->size; c++) {
		if(c > 0) {
			knh_write_delim(ctx, w);
		}
		knh_write(ctx, w, knh_String_tobytes(o->list[c].key));
//		knh_putc(ctx, w, ':');	knh_putc(ctx, w, ' ');
//		knh_format(ctx, w, static METHODN__k, o->list[c].value, KNH_NULL);
	}
	knh_putc(ctx, w, '}');
}

/* ------------------------------------------------------------------------ */
/* @method void DictSet.%dump(OutputStream w, String m) */

static void knh_DictSet__dump(Ctx *ctx, DictSet *o, OutputStream *w, String *m)
{
	knh_DictSet_sort(o);
	knh_putc(ctx, w, '{');
	size_t c;
	for(c = 0; c < o->size; c++) {
		if(c > 0) {
			knh_write_delim(ctx, w);
		}
		knh_write(ctx, w, knh_String_tobytes(o->list[c].key));
		knh_putc(ctx, w, ':');	knh_putc(ctx, w, ' ');
		knh_write_dfmt(ctx, w, KNH_INTPTR_FMT, o->list[c].value);
	}
	knh_putc(ctx, w, '}');
}

/* ------------------------------------------------------------------------ */

#endif/*KNH_CC_METHODAPI*/

#ifdef __cplusplus
}
#endif
