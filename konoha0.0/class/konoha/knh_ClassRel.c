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

#define START(b)   (b->capacity - b->psize)
#define SORTED_YES 0
#define SORTED_NO  1

/* ======================================================================== */
/* [structs] */

void
knh_ClassRel_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	ClassRel *b = (ClassRel*)s;
	b->capacity = knh_uint_min(4, init);
	b->size   = 0;
	b->psize  = 0;
	b->sorted = SORTED_YES;
	b->maplist   = (MapMap**)knh_malloc(ctx, b->capacity * sizeof(MapMap*));
	knh_bzero(b->maplist, b->capacity * sizeof(MapMap*));
}

/* ------------------------------------------------------------------------ */

#define _knh_ClassRel_struct_copy    NULL

/* ------------------------------------------------------------------------ */

#define _knh_ClassRel_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void
knh_ClassRel_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	ClassRel *b = (ClassRel*)s;
	knh_int_t i;
	for(i = 0; i < b->size; i++) {
		gc(ctx, b->maplist[i]);
	}
	for(i = START(b); i < b->capacity; i++) {
		gc(ctx, b->maplist[i]);
	}
	if(IS_SWEEP(gc)) {
		knh_free(b->maplist, b->capacity * sizeof(MapMap*));
	}
}

/* ======================================================================== */
/* [constructors] */

ClassRel* new_ClassRel(Ctx *ctx, knh_ushort_t capacity)
{
	ClassRel *b = (ClassRel*)knh_Object_malloc0(ctx, KNH_FLAG_ClassRel, CLASS_ClassRel, sizeof(ClassRel));
	knh_ClassRel_struct_init(ctx, (Struct*)b, capacity, NULL);
	return b;
}

/* ------------------------------------------------------------------------ */

void knh_ClassRel_resize(Ctx *ctx, ClassRel *b, size_t newsize)
{
	MapMap **newlist = (MapMap**)knh_malloc(ctx, newsize * sizeof(MapMap*));
	knh_bzero(newlist, newsize);
	knh_int_t i;
	for(i = 0; i < b->size; i++) {
		newlist[i] = b->maplist[i];
	}
	for(i = START(b); i < b->capacity; i++) {
		newlist[i + (newsize-b->capacity)] = b->maplist[i];
	}
	knh_free(b->maplist, b->capacity * sizeof(MapMap*));
	b->maplist = newlist;
	b->capacity = newsize;
}

/* ------------------------------------------------------------------------ */

int 
knh_ClassRel_util_cmp(const MapMap *m1, const MapMap *m2)
{
	int res = m1->flag - m2->flag;
	return (res == 0) ? m2->tcid - m1->tcid : res;
}

/* ------------------------------------------------------------------------ */

void knh_ClassRel_sort(Ctx *ctx, ClassRel *b)
{
	if(b->size > 1) {
		knh_qsort(b->maplist, b->size, sizeof(MapMap*), 
					(int (*)(const void*, const void*))knh_ClassRel_util_cmp);		
	}
	if(b->psize > 1) {
		knh_qsort(b->maplist + START(b), b->psize, sizeof(MapMap*), 
					(int (*)(const void*, const void*))knh_ClassRel_util_cmp);		
	}
}

/* ------------------------------------------------------------------------ */


void knh_ClassRel_add(Ctx *ctx, ClassRel *b, MapMap *map)
{
//	if(map->scpid == CLASS_Int) {
//		DEBUG("%s%s --> %s%s", TYPEN(map->scpid), TYPEQ(map->scpid), TYPEN(map->tcid), TYPEQ(map->tcid));
//	}
	if(b->size + b->psize == b->capacity) {
		knh_ClassRel_resize(ctx, b, b->capacity + 8);
	}
	knh_class_t scid = map->scid;
	if(TYPE_ISPLURAL(scid)) {
		DEBUG_ASSERT(b->maplist[START(b)-1] == NULL);
		KNH_INITv(b->maplist[START(b)-1], map);
		b->psize++;
	}else {
		DEBUG_ASSERT(b->maplist[b->size] == NULL);
		KNH_INITv(b->maplist[b->size], map);
		b->size++;
	}
	knh_ClassRel_sort(ctx, b);
}

/* ======================================================================== */
/* [find] */


MapMapNULL *knh_ClassRel_find__first(ClassRel *b, knh_class_t tcid)
{
	int i;	
	for(i = b->size - 1; i >= 0; i--) {
		if(b->maplist[i]->flag == KNH_FLAG_MMF_INTERFACE) return NULL;
		if(b->maplist[i]->tcid == tcid) return b->maplist[i];
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */


MapMapNULL *knh_ClassRel_findp__first(ClassRel *b, knh_class_t tcid)
{
	int i;	
	for(i = b->capacity - 1; i >= b->capacity - b->size; i--) {
		if(b->maplist[i]->flag == KNH_FLAG_MMF_INTERFACE) return NULL;
		if(b->maplist[i]->tcid == tcid) return b->maplist[i];
	}
	return NULL;
}

///* ------------------------------------------------------------------------ */
//
//
//MappingNULL *knh_ClassRel_find__second(Ctx *ctx, ClassRel *b, classp_t tcid)
//{
//	int i;	
//	for(i = b->size - 1; i >= 0; i--) {
//		if(knh_Classp_interfaceof(ctx, b->maplist[i]->tcid, tcid)) return b->maplist[i];
//	}
//	return NULL;
//}
//
///* ------------------------------------------------------------------------ */
//
//
//MappingNULL *knh_ClassRel_findp__second(Ctx *ctx, ClassRel *b, classp_t tcid)
//{
//	int i;	
//	for(i = b->capacity - 1; i >= b->capacity - b->size; i--) {
//		if(knh_Classp_interfaceof(ctx, b->maplist[i]->tcid, tcid)) return b->maplist[i];
//	}
//	return NULL;
//}


/* ======================================================================== */
/* [mappings] */

/* ======================================================================== */
/* [iterators] */

//Object* knh_ClassRel_class_next(Ctx *ctx, Iterator *it)
//{
//	ClassRel *b = (ClassRel*)knh_Iterator_source(it);
//	size_t pos = knh_Iterator_pos(it);
//	if(pos < b->size) {
//		int i;	
//		for(i = pos; i < b->size; i++) {
//#ifdef MAPF_INTERFACE
//			if(b->maplist[i].flag != MAPF_INTERFACE) continue;
//#endif
//			knh_Iterator_setpos(it, i+1);
//			return knh_tclass_class(ctx, b->maplist[i].tcid);
//		}
//		knh_Iterator_setpos(it, b->size+1);
//	}
//	return KNH_NULL;
//}
//
///* ------------------------------------------------------------------------ */
//
///* @Map ClassRel Iterator */
//
//
//Object* knh_ClassRel_interfaces(Ctx *ctx, Object *self, Mapping *map)
//{
//	return new_Iterator(ctx, CLASS_Class, self, knh_ClassRel_class_next);
//}
//

/* ======================================================================== */
/* [movabletext] */

/* @method void ClassRel.%dump(OutputStream w, Any m) */

void knh_ClassRel__dump(Ctx *ctx, ClassRel *b, OutputStream *w, Any *m)
{
	knh_int_t i;
	for(i = 0; i < b->size; i++) {
		knh_printf(ctx, w, "[%d]\t", i);
		knh_MapMap__dump(ctx, b->maplist[i], w, knh_String_EMPTY());
		knh_println(ctx, w, STEXT(""));
	}
	for(i = START(b); i < b->capacity; i++) {
		knh_printf(ctx, w, "[%d]\t", i);
		knh_MapMap__dump(ctx, b->maplist[i], w, knh_String_EMPTY());
		knh_println(ctx, w, STEXT(""));
	}
}

///* ------------------------------------------------------------------------ */
//
//
//Object *knh_type_cast(Ctx *ctx, knh_type_t t, Object *b)
//{
//	DEBUG("%s%s --> %s%s", TYPEN(knh_Object_cid(b)), TYPEQ(knh_Object_cid(b)), TYPEN(t), TYPEQ(t));
//	if(TYPE_ISNULLABLE(t)) {
//		VM_PUSH(ctx, b);
//		VM_PUSH_MAP(ctx, t);
//		VM_MAP(ctx);
//		return VM_EBP(ctx, 0);
//	}else {
//		VM_PUSH(ctx, b);
//		VM_PUSH_MAP(ctx, TYPE_TONULLABLE(t));
//		VM_MAPE(ctx);
//		return VM_EBP(ctx, 0);
//	}
//}

///* ------------------------------------------------------------------------ */
//
///* @method Any Object.opMap(Class c, Object! serv) */
//
//
//Any *knh_Object_opMap(Ctx *ctx, Object *b, knh_class_t tcid, Object* serv)
//{
//	TODO();
//	return b;
//}

/* ------------------------------------------------------------------------ */

//
//Method *knh_Class_find_itfmethod(Ctx *ctx, knh_class_t cid, knh_methodn_t mn)
//{
//	if(knh_tmethodn_isnew(ctx, mn)) return KNH_NULL;
//	Method *mtd = knh_Class_getMethod(ctx, cid, mn);	
//	if(IS_NOTNULL(mtd) && !knh_Method_isPrivate(mtd)) return mtd;
//#ifdef MAPF_INTERFACE
//	knh_int_t i;	
//	ClassRel *b = knh_tclass_cmap(ctx, cid);
//	for(i = 0; i < b->size; i++) {
//		if(b->maplist[i].flag == MAPF_INTERFACE) {
//			mtd = knh_Class_getMethod(ctx, b->maplist[i].tcid, mn);
//			if(IS_NOTNULL(mtd) && !knh_Method_isPrivate(mtd)) return mtd;
//		} 
//	}
//#endif
//	return KNH_NULL;	
//}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
