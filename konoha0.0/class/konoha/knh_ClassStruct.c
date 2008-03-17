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

#define _knh_tstruct_isNative(sid)   (sid < KONOHA_TSTRUCT_SIZE)

/* ======================================================================== */
/* [structs] */

void
knh_ClassStruct_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	ClassStruct *b = (ClassStruct*)s;
	b->sid = 0;
	b->fsize = init;
	if(b->fsize == 0) {
		b->fields = NULL;
	}else {
		b->fields = (knh_cfield_t*)knh_malloc(ctx, b->fsize * sizeof(knh_cfield_t));
		knh_int_t i;
		for(i = 0; i < b->fsize; i++) {
			b->fields[i].flag = 0;
			b->fields[i].type = TYPE_any;
			b->fields[i].fn   = FIELDN_NONAME;
			KNH_INITv(b->fields[i].value, KNH_NULL); 
		}
	}
	KNH_INITv(b->methods, new_Array(ctx, b->fsize * 2));
}

/* ------------------------------------------------------------------------ */

#define _knh_ClassStruct_struct_copy    NULL

/* ------------------------------------------------------------------------ */

#define _knh_ClassStruct_struct_compare NULL

/* ------------------------------------------------------------------------ */

void
knh_ClassStruct_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	ClassStruct *b = (ClassStruct*)s;
	if(b->fields != NULL) {
		knh_int_t i;
		for(i = 0; i < b->fsize; i++) {
			gc(ctx, b->fields[i].value); 
		}
		if(IS_SWEEP(gc)) {
			knh_free(b->fields, b->fsize * sizeof(knh_cfield_t));
		}
	}
	gc(ctx, b->methods);
}

/* ======================================================================== */
/* [constructors] */


ClassStruct* new_ClassStruct(Ctx *ctx, knh_struct_t sid)
{
	ClassStruct* b = 
		(ClassStruct*)knh_Object_malloc0(ctx, KNH_FLAG_ClassStruct, CLASS_ClassStruct, sizeof(ClassStruct));
	knh_ClassStruct_struct_init(ctx, (Struct*)b, knh_tstruct_bsize(sid), NULL);
	b->sid = sid;
	return b;
}

/* ======================================================================== */
/* [safe] */

void knh_cfield_safetype(knh_cfield_t *cf)
{
	if(IS_NULL(cf->value) && TYPE_ISNOTNULL(cf->type)) {			
		if(knh_tclass_hasDefaultValue(TYPE_UNMASK_NULL(cf->type))) {
			cf->flag |= KNH_FLAG_CFF_SAFEVALUE;
		}
		else {
			cf->type = TYPE_UNMASK_NULL(cf->type);
		}
	}
}

/* ------------------------------------------------------------------------ */

Object *knh_cfield_safevalue(Ctx *ctx, knh_cfield_t *cf)
{
	if(KNH_FLAG_IS(cf->flag, KNH_FLAG_CFF_SAFEVALUE)) {
		return knh_tclass_safevalue(ctx, TYPE_UNMASK_NULL(cf->type));
	}
	return cf->value;
}

/* ======================================================================== */
/* [field] */

knh_index_t 
knh_Class_initField(Ctx *ctx, knh_class_t cid, knh_flag_t flag, knh_type_t type, knh_fieldn_t fn, Object *value)
{
	ClassStruct *b = knh_tclass_cstruct(cid);
	DEBUG_ASSERT(b->fields != NULL);
	knh_index_t idx = 0;
	for(idx = 0; idx < b->fsize; idx++) {
		if(b->fields[idx].fn == FIELDN_NONAME) {
			b->fields[idx].flag = flag;
			b->fields[idx].type = type;
			b->fields[idx].fn = FIELDN_UNMASK(fn);
			KNH_SETv(ctx, b->fields[idx].value, value);
			knh_cfield_safetype(&(b->fields[idx]));
			return knh_tclass_offset(cid) + idx;
		}
		if(b->fields[idx].fn == fn) {
			DEBUG("It shouldn't happen");
			return -1;
		}
	}
	return -1;
}	

/* ------------------------------------------------------------------------ */

knh_index_t knh_Class_indexOfField(knh_class_t cid, knh_fieldn_t fn)
{
	L_TAIL:;
	ClassStruct *b = knh_tclass_cstruct(cid);
	knh_index_t idx = -1;
	if(b->fields != NULL) {
		for(idx = 0; idx < b->fsize; idx++) {
			if(b->fields[idx].fn == fn) {
				return knh_tclass_offset(cid) + idx;
			}
		}
		idx = -1;
	}
	if(knh_tclass_offset(cid) == 0) return -1;
	cid = knh_tclass_supcid(cid);
	goto L_TAIL;
}	

/* ------------------------------------------------------------------------ */

knh_index_t knh_Class_queryField(knh_class_t cid, knh_fieldn_t fnq)
{
	knh_fieldn_t fn = FIELDN_UNMASK(fnq);
	L_TAIL:;
	ClassStruct *b = knh_tclass_cstruct(cid);
	if(FIELDN_IS_SUPER(fnq)) {
		goto L_SUPER;
	}
	knh_index_t idx = -1;
	if(b->fields != NULL) {
		for(idx = 0; idx < b->fsize; idx++) {
			if(b->fields[idx].fn == fn) {
				if(KNH_FLAG_IS(b->fields[idx].flag, KNH_FLAG_CFF_PROTECTED)) {
					if(!FIELDN_IS_PROTECTED(fnq)) {
						return -1;
					}
				}
				return knh_tclass_offset(cid) + idx;
			}
		}
		idx = -1;
	}
	L_SUPER:;
	if(knh_tclass_offset(cid) == 0) return -1;
	cid = knh_tclass_supcid(cid);
	goto L_TAIL;
}	

/* ------------------------------------------------------------------------ */

knh_cfield_t *knh_Class_fieldAt(knh_class_t cid, size_t n)
{
	DEBUG_ASSERT(0 <= n && n < knh_tclass_size(cid));
	L_TAIL:;
	ClassStruct *b = knh_tclass_cstruct(cid);
	size_t offset = knh_tclass_offset(cid);
	if(offset <= n) {
		if(b->fields == NULL) {
			return NULL;
		}
		else {
			return &(b->fields[n - offset]);
		}
	}
	cid = knh_tclass_supcid(cid);
	goto L_TAIL;
}

/* ------------------------------------------------------------------------ */

Object *knh_ClassStruct_safevalue(Ctx *ctx, ClassStruct *b, size_t n)
{
	return knh_cfield_safevalue(ctx, &(b->fields[n]));
}

/* ======================================================================== */
/* [Method] */

/* ------------------------------------------------------------------------ */

void knh_Class_addMethod__fast(Ctx *ctx, knh_class_t cid, Method *method) 
{
	KNH_ASSERT(cid == method->cid);
	DEBUG_ASSERT(IS_Method(method));
	ClassStruct *b = knh_tclass_cstruct(cid);	
	knh_int_t i;
	for(i = 0; i < knh_Array_size(b->methods); i++) {
		Method *mtd = knh_Array_n(b->methods, i);
		if(mtd->mn == method->mn) {
			DEBUG("Duplicated method: %s.%s", CLASSN(cid), METHODN(method->mn)); 
			knh_Array_setn(ctx, b->methods, i, method);
			return ;
		}
	}
	knh_Array_append(ctx, b->methods, method);
}

/* ------------------------------------------------------------------------ */

void knh_Class_addMethod(Ctx *ctx, knh_class_t cid, Method *method) 
{
	KNH_ASSERT(cid == method->cid);
	DEBUG_ASSERT(IS_Method(method));
	ClassStruct *b = knh_tclass_cstruct(cid);	
	knh_int_t i;
	for(i = 0; i < knh_Array_size(b->methods); i++) {
		Method *mtd = knh_Array_n(b->methods, i);
		if(mtd->mn == method->mn) {
			DEBUG("Duplicated method: %s.%s", CLASSN(cid), METHODN(method->mn)); 
			knh_Array_setn(ctx, b->methods, i, method);
			return ;
		}
	}
	knh_Array_append(ctx, b->methods, method);
}

/* ------------------------------------------------------------------------ */

Method* 
knh_Class_getMethod__(Ctx *ctx, knh_class_t this_cid, knh_methodn_t mn, knh_bool_t gen)
{
	knh_class_t cid = this_cid;
	TAIL_RECURSION:;
	ClassStruct *b = knh_tclass_cstruct(cid);
	knh_int_t i;
	for(i = 0; i < knh_Array_size(b->methods); i++) {
		Method *mtd = knh_Array_n(b->methods, i);
		if(mtd->mn == mn) return mtd;
	}
	if(cid == CLASS_Object) {
		goto L_GenerateField;
	}
	cid = knh_tclass_supcid(cid);
	goto TAIL_RECURSION;

	L_GenerateField:;
	if(METHODN_IS_GETTER(mn)) {
		knh_index_t idx = knh_Class_indexOfField(this_cid, METHODN_TOFIELDN(mn));
		if(idx == -1) {
			goto L_NoSuchMethod;
		}
		knh_cfield_t *cf = knh_Class_fieldAt(this_cid, idx);
		if(!KNH_FLAG_IS(cf->flag, KNH_FLAG_CFF_GETTER)) {
			goto L_NoSuchMethod;
		}
		Method *mtd = new_Method(ctx, KNH_FLAG_MF_GENERATED, this_cid, mn, knh__ClassStruct_fmethodGetter);
		mtd->delta = idx;
		KNH_SETv(ctx, mtd->mf, new_MethodField__getter(ctx, cf->type));
		knh_Array_append(ctx, b->methods, mtd);
		return mtd;
	}

	if(METHODN_IS_SETTER(mn)) {
		knh_index_t idx = knh_Class_indexOfField(this_cid, METHODN_TOFIELDN(mn));
		if(idx == -1) {
			goto L_NoSuchMethod;
		}
		knh_cfield_t *cf = knh_Class_fieldAt(this_cid, idx);
		if(!KNH_FLAG_IS(cf->flag, KNH_FLAG_CFF_SETTER)) {
			goto L_NoSuchMethod;
		}
		Method *mtd = new_Method(ctx, KNH_FLAG_MF_GENERATED, this_cid, mn, knh__ClassStruct_fmethodSetter);
		mtd->delta = idx;
		KNH_SETv(ctx, mtd->mf, new_MethodField__setter(ctx, cf->type, cf->fn));
		knh_Array_append(ctx, b->methods, mtd);
		return mtd;
	}

	L_NoSuchMethod:;
	//DEBUG("Not Found: cid=%s, mn=%d,%s", CLASSN(this_cid), mn, METHODN(mn));
	if(gen) {
		Method *mtd = new_Method__NoSuchMethod(ctx, cid, mn);
		knh_Array_add(ctx, b->methods, mtd);
		return mtd;
	}
	else {
		return KNH_NULL;
	}
}

#define _knh_Class_getMethod(ctx, c, mn)    knh_Class_getMethod__(ctx, c, mn, 0)
#define _knh_Class_findMethod(ctx, c, mn)   knh_Class_getMethod__(ctx, c, mn, 1)

/* ------------------------------------------------------------------------ */
/* [field_method] */

void knh__ClassStruct_fmethodGetter(Ctx *ctx, Object **sfp)
{
	DEBUG_ASSERT(IS_Method(sfp[-1]));
	DEBUG("%s.get[%d]", CLASSNo(sfp[0]), ((Method*)sfp[-1])->delta);
	VM_RET(ctx, KNH_FIELDn(sfp[0], ((Method*)sfp[-1])->delta));
}	

/* ------------------------------------------------------------------------ */

void knh__ClassStruct_fmethodSetter(Ctx *ctx, Object **sfp)
{
	DEBUG_ASSERT(IS_Method(sfp[-1]));
	DEBUG("%s.get[%d]", CLASSNo(sfp[0]), ((Method*)sfp[-1])->delta);
	VM_MOV(ctx, KNH_FIELDn(sfp[0], ((Method*)sfp[-1])->delta), sfp[1]);
	VM_RET_VOID(ctx);
}

/* ------------------------------------------------------------------------ */

MethodField* new_MethodField__getter(Ctx *ctx, knh_type_t type)
{
	MethodField *mf = new_MethodField(ctx, 0, 1);
	mf->params[0].type = type;
	mf->params[0].fn = FIELDN_return;
	return mf;
}

/* ------------------------------------------------------------------------ */

MethodField* new_MethodField__setter(Ctx *ctx, knh_type_t type, knh_fieldn_t fn)
{
	MethodField *mf = new_MethodField(ctx, 0, 2);
	mf->params[0].type = TYPE_void;
	mf->params[0].fn = FIELDN_return;
	mf->params[1].type = type;
	mf->params[1].fn = fn;
	return mf;
}

/* ------------------------------------------------------------------------ */
/* [movabletext] */

void knh_cfield_dump(Ctx *ctx, knh_cfield_t *f, size_t offset, size_t fsize, OutputStream *w)
{
	size_t idx = 0;
	for(idx = 0; idx < fsize; idx++) {
		if(f[idx].fn == FIELDN_NONAME) {
			knh_printf(ctx, w, "[%d] -\n", (offset+idx));
			continue;
		}
		knh_printf(ctx, w, "[%d] %F %T %N = %O\n", (offset+idx), f[idx].flag, f[idx].type, f[idx].fn, f[idx].value);
	}
}	

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
