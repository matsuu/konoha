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
knh_ClassStruct_struct_init(Ctx *ctx, knh_ClassStruct_struct *b, int init, Object *cs)
{
	b->sid = 0;
	b->fsize = init;
	if(b->fsize == 0) {
		b->fields = NULL;
	}else {
		b->fields = (knh_cfield_t*)KNH_MALLOC(ctx, b->fsize * sizeof(knh_cfield_t));
		knh_int_t i;
		for(i = 0; i < b->fsize; i++) {
			b->fields[i].flag = 0;
			b->fields[i].type = TYPE_any;
			b->fields[i].fn   = FIELDN_NONAME;
			KNH_INITv(b->fields[i].value, KNH_NULL);
		}
	}
	b->methods = NULL;
}

/* ------------------------------------------------------------------------ */

#define _knh_ClassStruct_struct_copy    NULL

/* ------------------------------------------------------------------------ */

void
knh_ClassStruct_struct_traverse(Ctx *ctx, knh_ClassStruct_struct *b, f_traverse gc)
{
	if(b->fields != NULL) {
		knh_int_t i;
		for(i = 0; i < b->fsize; i++) {
			gc(ctx, b->fields[i].value);
		}
		if(IS_SWEEP(gc)) {
			KNH_FREE(b->fields, b->fsize * sizeof(knh_cfield_t));
		}
	}
	gc(ctx, UP(b->methods));
}

/* ======================================================================== */
/* [constructors] */

ClassStruct* new_ClassStruct0(Ctx *ctx, knh_struct_t sid, int method_size)
{
	knh_ClassStruct_t* o =
		(knh_ClassStruct_t*)new_Object_malloc(ctx, FLAG_ClassStruct, CLASS_ClassStruct, sizeof(knh_ClassStruct_struct));
	if(STRUCT_ISFIELD(sid)) {
		knh_ClassStruct_struct_init(ctx, DP(o), STRUCT_FIELDSIZE(sid), NULL);
	}
	else {
		knh_ClassStruct_struct_init(ctx, DP(o), 0 /* (knh_tStruct[sid].size / sizeof(Object*)) */, NULL);
	}
	KNH_INITv(DP(o)->methods, new_Array0(ctx, method_size));
	DP(o)->sid = sid;
	return o;
}

/* ======================================================================== */
/* [finit] */

void knh_ClassStruct_finit(Ctx *ctx, ClassStruct *o, knh_class_t self_cid, Object **v)
{
	size_t i;
	knh_cfield_t *cf = DP(o)->fields;
	for(i = 0; i < DP(o)->fsize; i++) {
		if(IS_NULL(cf[i].value) && TYPE_ISNOTNULL(cf[i].type)) {
			knh_class_t cid = knh_pmztype_toclass(ctx, cf[i].type, self_cid);
			KNH_INITv(v[i], new_Object__init(ctx, 0, cid));
		}
		else {
			KNH_INITv(v[i], cf[i].value);
		}
	}
}

/* ======================================================================== */
/* [field] */

knh_index_t knh_Class_indexOfField(knh_class_t cid, knh_fieldn_t fn)
{
	L_TAIL:;
	DEBUG_ASSERT_cid(cid);
	{
		knh_index_t idx = -1;
		ClassStruct *o = knh_tClass[cid].cstruct;

		if(DP(o)->fields != NULL) {
			for(idx = 0; idx < DP(o)->fsize; idx++) {
				if(DP(o)->fields[idx].fn == fn) {
					return knh_tClass[cid].offset + idx;
				}
			}
			idx = -1;
		}
		if(knh_tClass[cid].offset == 0) return -1;
		cid = knh_tClass[cid].supcid;
	}
	goto L_TAIL;
}

/* ------------------------------------------------------------------------ */

knh_index_t knh_Class_queryField(knh_class_t cid, knh_fieldn_t fnq)
{
	knh_fieldn_t fn = FIELDN_UNMASK(fnq);
	L_TAIL:;
	DEBUG_ASSERT_cid(cid);
	{
		ClassStruct *o = knh_tClass[cid].cstruct;
		knh_index_t idx = -1;
		if(FIELDN_IS_SUPER(fnq)) {
			TODO(); /* UNSET fnq */
			goto L_SUPER;
		}
		if(DP(o)->fields != NULL) {
			for(idx = 0; idx < DP(o)->fsize; idx++) {
				if(DP(o)->fields[idx].fn == fn) {
					if(KNH_FLAG_IS(DP(o)->fields[idx].flag, KNH_FLAG_CFF_PROTECTED)) {
						if(!FIELDN_IS_PROTECTED(fnq)) {
							return -1;
						}
					}
					return knh_tClass[cid].offset + idx;
				}
			}
			idx = -1;
		}
		L_SUPER:;
		if(knh_tClass[cid].offset == 0) return -1;
		cid = knh_tClass[cid].supcid;
		goto L_TAIL;
	}
}

/* ------------------------------------------------------------------------ */

knh_cfield_t *knh_Class_fieldAt(knh_class_t cid, size_t n)
{
	DEBUG_ASSERT_cid(cid);
	KNH_ASSERT(0 <= n && n < knh_tClass[cid].size);
	L_TAIL:;
	{
		ClassStruct *o = knh_tClass[cid].cstruct;;
		size_t offset = knh_tClass[cid].offset;
		if(offset <= n) {
			if(DP(o)->fields == NULL) {
				return NULL;
			}
			else {
				return &(DP(o)->fields[n - offset]);
			}
		}
		DEBUG_ASSERT_cid(cid);
		cid = knh_tClass[cid].supcid;
	}
	goto L_TAIL;
}

/* ======================================================================== */
/* [Method] */

/* ------------------------------------------------------------------------ */

void knh_Class_addMethod__fast(Ctx *ctx, knh_class_t cid, Method *mtd)
{
	KNH_ASSERT(IS_Method(mtd));
	KNH_ASSERT(cid == DP(mtd)->cid);
	{
		ClassStruct *o = knh_tClass[cid].cstruct;
		if(knh_class_isSingleton(cid)) {
			DP(mtd)->flag = DP(mtd)->flag | KNH_FLAG_MF_CLASSFUNC;
		}
		knh_Array_add(ctx, DP(o)->methods, UP(mtd));
	}
}
/* ------------------------------------------------------------------------ */

void knh_Class_addMethod(Ctx *ctx, knh_class_t cid, Method *mtd)
{
	KNH_ASSERT(IS_Method(mtd));
	KNH_ASSERT(cid == DP(mtd)->cid);
	{
		ClassStruct *o = knh_tClass[cid].cstruct;;
		knh_int_t i;
		for(i = 0; i < knh_Array_size(DP(o)->methods); i++) {
			Method *mtd2 = (Method*)knh_Array_n(DP(o)->methods, i);
			if(DP(mtd2)->mn == DP(mtd)->mn) {
				char buf[CLASSNAME_BUFSIZ];
				knh_format_cmethodn(buf, sizeof(buf), cid, DP(mtd)->mn);
				DBG2_P("Duplicated method: %s", buf);
//				knh_Array_setn(ctx, DP(o)->methods, i, mtd);
				return ;
			}
		}
		if(knh_class_isSingleton(cid)) {
			DP(mtd)->flag = DP(mtd)->flag | KNH_FLAG_MF_CLASSFUNC;
		}
		knh_Array_add(ctx, DP(o)->methods, UP(mtd));
	}
}

/* ------------------------------------------------------------------------ */
/* [field_method] */

static
METHOD knh__ClassStruct_fmethodGetter(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_ASSERT(IS_Method(sfp[-1].mtd));
//	int delta = DP(sfp[-1].mtd)->delta;
//	DBG2_P("%s.get[%d]", CLASSNo((sfp[0].o)), delta);
//	DBG2_P("sfp[-1]: %s", CLASSNo((sfp[-1].o)));
//	DBG2_P("sfp[0]: %s", CLASSNo((sfp[0].o)));
//	DBG2_P("sfp[1]: %s", CLASSNo((sfp[1].o)));
	METHOD_RETURN(ctx, sfp, KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta));
}

/* ------------------------------------------------------------------------ */

static
METHOD knh__ClassStruct_fmethodSetter(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_ASSERT(IS_Method(sfp[-1].mtd));
	//DBG2_P("%s.get[%d]", CLASSNo((sfp[0].o)), DP(sfp[-1].mtd)->delta);
	VM_MOV(ctx, KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta), sfp[1].o);
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

/* ------------------------------------------------------------------------ */

static
MethodField* new_MethodField__getter(Ctx *ctx, knh_type_t type)
{
	MethodField *mf = new_MethodField(ctx, 0, 1);
	DP(mf)->params[0].type = type;
	DP(mf)->params[0].fn = FIELDN_return;
	return mf;
}

/* ------------------------------------------------------------------------ */

static
MethodField* new_MethodField__setter(Ctx *ctx, knh_type_t type, knh_fieldn_t fn)
{
	MethodField *mf = new_MethodField(ctx, 0, 2);
	DP(mf)->params[0].type = TYPE_void;
	DP(mf)->params[0].fn = FIELDN_return;
	DP(mf)->params[1].type = type;
	DP(mf)->params[1].fn = fn;
	return mf;
}

/* ------------------------------------------------------------------------ */

Method*
knh_Class_getMethod__(Ctx *ctx, knh_class_t this_cid, knh_methodn_t mn, knh_bool_t gen)
{
	knh_class_t cid = this_cid;
	TAIL_RECURSION:;
	DEBUG_ASSERT_cid(cid);
	{
		ClassStruct *o = knh_tClass[cid].cstruct;;
		knh_int_t i;
		for(i = 0; i < knh_Array_size(DP(o)->methods); i++) {
			Method *mtd = (Method*)knh_Array_n(DP(o)->methods, i);
			if(DP(mtd)->mn == mn) return mtd;
		}
		if(cid == CLASS_Object) {
			cid = this_cid;
			goto L_GenerateField;
		}
		cid = knh_tClass[cid].supcid;
	}
	goto TAIL_RECURSION;

	L_GenerateField:;
	if(METHODN_IS_GETTER(mn)) {
		knh_index_t idx = knh_Class_indexOfField(this_cid, METHODN_TOFIELDN(mn));
		if(idx == -1) {
			goto L_NoSuchMethod;
		}
		else {
			knh_cfield_t *cf = knh_Class_fieldAt(this_cid, idx);
			if(!KNH_FLAG_IS(cf->flag, KNH_FLAG_CFF_GETTER)) {
				goto L_NoSuchMethod;
			}
			else {
				Method *mtd = new_Method(ctx, KNH_FLAG_MF_GENERATED, this_cid, mn, knh__ClassStruct_fmethodGetter);
				ClassStruct *o = knh_tClass[this_cid].cstruct;;
				DP(mtd)->delta = idx;
				KNH_SETv(ctx, DP(mtd)->mf, new_MethodField__getter(ctx, cf->type));
				knh_Array_add(ctx, DP(o)->methods, UP(mtd));
				return mtd;
			}
		}
	}

	if(METHODN_IS_SETTER(mn)) {
		knh_index_t idx = knh_Class_indexOfField(this_cid, METHODN_TOFIELDN(mn));
		if(idx == -1) {
			goto L_NoSuchMethod;
		}
		else {
			knh_cfield_t *cf = knh_Class_fieldAt(this_cid, idx);
			if(!KNH_FLAG_IS(cf->flag, KNH_FLAG_CFF_SETTER)) {
				goto L_NoSuchMethod;
			}
			else {
				Method *mtd = new_Method(ctx, KNH_FLAG_MF_GENERATED, this_cid, mn, knh__ClassStruct_fmethodSetter);
				ClassStruct *o = knh_tClass[this_cid].cstruct;;
				DP(mtd)->delta = idx;
				KNH_SETv(ctx, DP(mtd)->mf, new_MethodField__setter(ctx, cf->type, cf->fn));
				knh_Array_add(ctx, DP(o)->methods, UP(mtd));
				return mtd;
			}
		}
	}

	L_NoSuchMethod:;
	//DEBUG("Not Found: cid=%s, mn=%d,%s", CLASSN(this_cid), mn, METHODN(mn));
	if(gen) {
		if(METHODN_IS_MOVTEXT(mn)) {
			return knh_Class_getMethod(ctx, cid, METHODN__empty);
		}
		else {
			Method *mtd = new_Method__NoSuchMethod(ctx, cid, mn);
			ClassStruct *o = knh_tClass[this_cid].cstruct;;
			DBG2_({
				char bufcm[CLASSNAME_BUFSIZ];
				knh_format_cmethodn(bufcm, sizeof(bufcm), cid, mn);
				DBG2_P("GENERATE NoSuchMethod: %s", bufcm);
			})
			knh_Array_add(ctx, DP(o)->methods, UP(mtd));
			return mtd;
		}
	}
	else {
		return (Method*)KNH_NULL;
	}
}

#define _knh_Class_getMethod(ctx, c, mn)    knh_Class_getMethod__(ctx, c, mn, 0)
#define _knh_Class_findMethod(ctx, c, mn)   knh_Class_getMethod__(ctx, c, mn, 1)

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
