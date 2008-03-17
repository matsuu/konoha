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

#define _CLASS_Object         ((knh_class_t)0)
#define _CLASS_newid          ((knh_class_t)-1)
#define _CLASS_unknown        ((knh_class_t)-2)

#define _CLASS_any            CLASS_Prototype
#define _CLASS_any__          CLASS_TOPLURAL(CLASS_Prototype)
#define _CLASS_Any            CLASS_Prototype

#define _knh_Class_type(c)     (c)->type
#define _knh_Class_class(c)    TYPE_TONOTNULL((c)->type)
#define _knh_Class_bcid(c)     (c)->bcid

/* ======================================================================== */
/* [structs] */

void
knh_Class_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs) 
{
	Class *b =  (Class*)s1;
	b->bcid = CLASS_Object;
	b->type = CLASS_Object;
}

/* ------------------------------------------------------------------------ */

#define _knh_Class_struct_copy   NULL

/* ------------------------------------------------------------------------ */

knh_int_t
knh_Class_struct_compare(Ctx *ctx, Struct *s1, Struct *s2) 
{
	Class *b =  (Class*)s1;
	Class *b2 = (Class*)s2;
	return knh_type_compare(ctx, b->type, b2->type);
}

/* ------------------------------------------------------------------------ */

#define _knh_Class_struct_traverse   NULL

/* ======================================================================== */
/* [constructors] */

Class* new_Class__base(Ctx *ctx, knh_class_t bcid, knh_class_t cid)
{
	DEBUG_ASSERT(bcid <= cid);
	Class* b = (Class*)knh_Object_malloc0(ctx, KNH_FLAG_Class, CLASS_Class, sizeof(Class));
	b->bcid = bcid;
	b->type = cid;
	return b;
}

/* ------------------------------------------------------------------------ */


Class* new_Class__type(Ctx *ctx, knh_type_t type)
{
	if(TYPE_ISBASE(type)) {
		return knh_tclass_class((knh_class_t)type);
	}
	Class* b = (Class*)knh_Object_malloc0(ctx, KNH_FLAG_Class, CLASS_Class, sizeof(Class));
	if(TYPE_ISPLURAL(type)) {
		b->type = type;
		b->bcid = CLASS_Iterator;
	}else {
		b->type = type;
		b->bcid = TYPE_UNMASK(type);
	}		
	return b;
}

/* ======================================================================== */
/* [methods] */

knh_class_t knh_Class_cid(Class *b)
{
	if(TYPE_ISPLURAL(b->type)) return CLASS_Iterator;
	return TYPE_UNMASK(b->type);
}

/* ======================================================================== */
/* [mappings] */


/* ======================================================================== */
/* [iterators] */

Object* knh_Class_null_next(Ctx *ctx, Iterator *it)
{
	return KNH_NULL;
}

///* ------------------------------------------------------------------------ */
//
///* @map Class Iterator! */
//
//Object* knh_tclass_class_next(Ctx *ctx, Iterator *it);
//
///* ------------------------------------------------------------------------ */
//
//
//Object* knh_Class_Iterator(Ctx *ctx, Object *self, MapMap *map)
//{
//	knh_class_t cid = knh_Class_cid(self);
//	f_next f = knh_Class_null_next;
//	if(knh_Class_isSingleton(cid)) {
//		f = NULL;  /* knh_Object_single_next */
//	}else if(cid == CLASS_Class) {
//		f = knh_tclass_class_next;
//	}
//	return new_Iterator(ctx, cid, self, f);
//}

/* ======================================================================== */
/* [movabletext] */

/* @method void Class.%s(OutputStream w, Any m) */

void knh_Class__s(Ctx *ctx, Class *b, OutputStream *w, Any *m)
{
	knh_write__class(ctx, w, knh_Class_class(b));
}

/* ------------------------------------------------------------------------ */
/* @method void Class.%dump(OutputStream w, Any m) */

void knh_Class__dump(Ctx *ctx, Class *b, OutputStream *w, Any *m)
{
	knh_class_t cid = knh_Class_cid(b);
	knh_write__class(ctx, w, knh_Class_class(b));
	if(cid < KONOHA_TSTRUCT_SIZE && knh_tclass_bcid(cid) < KONOHA_TSTRUCT_SIZE) {
		return ;
	}
	knh_int_t i, c = 0;
	for(i = 0; i < knh_tclass_bsize(cid); i++) {
		knh_cfield_t *cf = knh_Class_fieldAt(cid, i);
		if(cf->fn == FIELDN_NONAME || KNH_FLAG_IS(cf->flag, KNH_FLAG_CFF_HIDDEN)) continue;
		if(c == 0) {
			knh_putc(ctx, w, '[');
		}
		if(c > 0) {
			knh_write_delim(ctx, w);
		}
		knh_printf(ctx, w, "%T %s", cf->type, FIELDN(cf->fn));
		Object *v = cf->value;
		if(IS_NOTNULL(v)) {
			knh_putc(ctx, w, '=');
			if(STRUCT_IS_String(v)) {
				knh_format(ctx, w, METHODN__dump, v, KNH_NULL);
			}
			else {
				knh_format(ctx, w, METHODN__s, v, KNH_NULL);
			}
		}
		c++;
	}
	if(c > 0) {
		knh_putc(ctx, w, ']');
	}
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
