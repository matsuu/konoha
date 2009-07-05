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

/* ------------------------------------------------------------------------ */
/* [macros] */


#define _knh_Method_mn(mtd)    DP(mtd)->mn
#define _knh_Method_mf(mtd)    DP(mtd)->mf

METHOD knh_fmethod_abstract(Ctx *ctx, knh_sfp_t *sfp);

/* ======================================================================== */
/* [MethodField] */

MethodField* new_MethodField(Ctx *ctx, knh_type_t rtype, size_t psize)
{
	MethodField *mf = (knh_MethodField_t*)new_Object_init(ctx, FLAG_MethodField, CLASS_MethodField, psize);
	mf->rtype = rtype;
	return mf;
}

/* ======================================================================== */
/* [hcode] */

knh_hcode_t knh_mparam_hcode(knh_hcode_t h, knh_type_t type, knh_fieldn_t fn)
{
	h = h * (KNH_TCLASS_SIZE+1) + type;
	return h + fn;
}

/* ======================================================================== */
/* [param] */

#define _knh_MethodField_rztype(mf)   ((mf)->rtype)
#define _knh_MethodField_psize(mf)    ((mf)->psize)

#define _knh_Method_rztype(mtd)      ((DP(mtd)->mf)->rtype)
#define _knh_Method_psize(mtd)       ((DP(mtd)->mf)->psize)
#define _knh_Method_pztype(mtd,n)    knh_MethodField_pztype(DP(mtd)->mf,n)

//#define _KONOHA_LASTPARAM     256

/* ------------------------------------------------------------------------ */

void knh_MethodField_set(MethodField *o, size_t n, knh_type_t type, knh_fieldn_t fn)
{
	if(o->psize > KNH_METHODFIELD_2) {
		DBG2_ASSERT(n < o->psize);
		o->mparams[n].type = type;
		o->mparams[n].fn = fn;
	}
	else if(n == 0) {
		DBG2_ASSERT(o->psize == 1 || o->psize == 2);
		o->p0.type = type;
		o->p0.fn= fn;
	}else {
		DBG2_ASSERT(n == 1 && o->psize == 2);
		o->p1.type = type;
		o->p1.fn = fn;
	}
}

/* ------------------------------------------------------------------------ */

knh_type_t knh_MethodField_pztype(MethodField *o, size_t n)
{
	if(o->psize > KNH_METHODFIELD_2) {
		if(n < o->psize) {
			return o->mparams[n].type;
		}
		return o->mparams[o->psize - 1].type; /* last type */
	}
	else if(n == 0 || o->psize != 2) {
		return o->p0.type;  /* last type or void */
	}else {
		DBG2_ASSERT(n == 1 && o->psize == 2);
		return o->p1.type;
	}
}

/* ------------------------------------------------------------------------ */

knh_mparam_t knh_MethodField_param(MethodField *o, size_t n)
{
	if(o->psize > KNH_METHODFIELD_2) {
		if(n < o->psize) {
			return o->mparams[n];
		}
		return o->mparams[o->psize - 1]; /* last param */
	}
	else if(n == 0 || o->psize != 2) {
		return o->p0;  /* last type or void */
	}else {
		DBG2_ASSERT(n == 1 && o->psize == 2);
		return o->p1;
	}
}

/* ------------------------------------------------------------------------ */

knh_type_t knh_Method_rtype(Ctx *ctx, Method *mtd, knh_class_t cid)
{
	return knh_pmztype_totype(ctx, DP(mtd)->mf->rtype, cid);
}

/* ------------------------------------------------------------------------ */

knh_type_t knh_Method_ptype(Ctx *ctx, Method *o, knh_class_t cid, size_t n)
{
	return knh_pmztype_totype(ctx, knh_MethodField_pztype(DP(o)->mf, n), cid);
}

/* ------------------------------------------------------------------------ */

knh_mparam_t knh_Method_param(Method *o, size_t n)
{
	return knh_MethodField_param(DP(o)->mf, n);
}

/* ------------------------------------------------------------------------ */
/* [Type] */

int knh_MethodField_equalsType(MethodField *o, MethodField *o2)
{
	if(o->psize != o2->psize || o->rtype != o2->rtype) return 0;
	if(o->psize > KNH_METHODFIELD_2) {
		size_t i;
		for(i = 0; i < o->psize; i++) {
			if(o->mparams[i].type != o2->mparams[i].type) return 0;
		}
	}
	else {
		if(o->p0.type != o2->p0.type || o->p1.type != o2->p1.type) return 0;
	}
	return 1;
}

/* ======================================================================== */
/* [AbstractMethod] */

METHOD knh_fmethod_abstract(Ctx *ctx, knh_sfp_t *sfp)
{
	Method *mtd = sfp[-1].mtd;
	knh_cwb_t cb = new_cwb(ctx);
	knh_printf(ctx, cb.w, "AbstractMethod!!: %C.%M", knh_Object_cid(sfp[0].o), DP(mtd)->mn);
	String *s = new_String__cwb(ctx, cb);
	KNH_THROW(ctx, s);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Method.isAbstract() */

knh_bool_t knh_Method_isAbstract(Method *o)
{
	return (DP(o)->fproceed == knh_fmethod_abstract);
}

/* ------------------------------------------------------------------------ */

void knh_Method_toAbstract(Ctx *ctx, Method *o)
{
	if(knh_Method_isObjectCode(o)) {
		KNH_FINALv(ctx, DP(o)->code);
		knh_Method_setObjectCode(o, 0);
	}
	knh_Method_syncfunc(o, knh_fmethod_abstract);
	o->pc_start  = NULL;
}

/* ======================================================================== */
/* [Method] */

void knh_Method_syncfunc(Method *o, knh_fmethod f)
{
	DP(o)->fproceed = f;
	(o)->fcall_1 = f;
}

/* ------------------------------------------------------------------------ */

Method* new_Method(Ctx *ctx, knh_flag_t flag, knh_class_t cid, knh_methodn_t mn, knh_fmethod func)
{
	Method* o = (Method*)new_Object_bcid(ctx, CLASS_Method, 0);
	DP(o)->flag  = flag;
	DP(o)->cid    = cid;
	DP(o)->mn     = mn;
	if(METHODN_IS_MOVTEXT(mn)) {
		KNH_SETv(ctx, DP(o)->mf, konoha_findMethodField0(ctx, TYPE_void));
	}
	func = (func == NULL) ? knh_fmethod_abstract : func;
	knh_Method_syncfunc(o, func);
	DP(o)->code  = NULL;
	o->pc_start  = NULL;
	return o;
}

/* ======================================================================== */
/* [NoSuchMethod] */

static
METHOD knh_fmethod_NoSuchMethod(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_cwb_t cwb = new_cwb(ctx);
	knh_Bytes_write(ctx, cwb.ba, STEXT("NoSuchMethod!!: "));
	knh_write_cid(ctx, cwb.w, knh_Object_cid(sfp[0].o));
	knh_putc(ctx, cwb.w, '.');
	knh_write_mn(ctx, cwb.w, DP(sfp[-1].mtd)->mn);
	String *s = new_String__cwb(ctx, cwb);
	KNH_THROW(ctx, s);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_Method_isNoSuchMethod(Method *o)
{
	return (DP(o)->fproceed == knh_fmethod_NoSuchMethod);
}

/* ------------------------------------------------------------------------ */

Method* new_Method__NoSuchMethod(Ctx *ctx, knh_class_t cid, knh_methodn_t mn)
{
	Method *mtd = new_Method(ctx, 0, cid, mn, knh_fmethod_NoSuchMethod);
	return mtd;
}

/* ======================================================================== */
/* [method type] */

int knh_methodn_isNew(Ctx *ctx, knh_methodn_t mn)
{
	if(mn == METHODN_new) return 1;
	if(METHODN_IS_MOVTEXT(mn) || METHODN_IS_GETTER(mn) || METHODN_IS_SETTER(mn)) {
		return 0;
	}
	char *n = FIELDN(METHODN_TOFIELDN(mn));
	if(n[0] == 'n' && n[1] == 'e' && n[2] == 'w' && n[3] == ':') {
		return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

int knh_Method_isConstructor(Ctx *ctx, Method *o)
{
	knh_class_t rtype = CLASS_type(knh_Method_rztype(o));
	if(rtype != DP(o)->cid) {
		return 0;
	}
	return knh_methodn_isNew(ctx, DP(o)->mn);
}

/* ------------------------------------------------------------------------ */

int knh_methodn_isOp(Ctx *ctx, knh_methodn_t mn)
{
	if(METHODN_IS_MOVTEXT(mn) || METHODN_IS_GETTER(mn) || METHODN_IS_SETTER(mn)) {
		return 0;
	}
	char *n = FIELDN(METHODN_TOFIELDN(mn));
	if(n[0] == 'o' && n[1] == 'p' && isupper(n[2])) {
		return 1;
	}
	return 0;
}

/* ======================================================================== */
/* [methods] */

/* ------------------------------------------------------------------------ */
/* @method String! Method.getName() */


String* knh_Method_getName(Ctx *ctx, Method *o)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_format_methodn(ctx, buf, sizeof(buf), DP(o)->mn);
	return new_String(ctx, B(buf), NULL);
}

/* ======================================================================== */
/* [Weaving] */

int knh_Method_isWoven(Method *mtd)
{
	return (mtd->fcall_1 != DP(mtd)->fproceed);
}

/* ------------------------------------------------------------------------ */

int knh_Method_canWeave(Ctx *ctx, Method *mtd, Method *aspect)
{
	if(knh_Method_isGenerator(mtd) || knh_Method_isAspect(mtd)) {
		TODO();
		return 0;
	}
	if(!IS_Method(aspect)) return 1; /* remove aspect */
	if(knh_Method_isWoven(aspect)) {
		KNH_WARNING(ctx, "nested aspect is not supported");
		return 0;
	}
	if(knh_Method_isAspect(aspect)) return 1;
	if(knh_Method_isVarArgs(mtd)) {
		KNH_WARNING(ctx, "variable length method can be woven");
		return 0;
	}
	if(knh_MethodField_equalsType(DP(mtd)->mf, DP(aspect)->mf)) {
		return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

void knh_Method_weave(Ctx *ctx, Method *aspect, Method *mtd)
{
	if(IS_Method(aspect)) {
		mtd->fcall_1 = aspect->fcall_1;
		mtd->pc_start = aspect->pc_start;
	}
	else { /* remove aspect */
		mtd->fcall_1 = DP(mtd)->fproceed;
		mtd->pc_start = knh_Method_pcstartNULL(mtd);
	}
}

/* ------------------------------------------------------------------------ */

/* ======================================================================== */
/* [Method] */

void knh_Class_addMethod(Ctx *ctx, knh_class_t cid, Method *mtd)
{
	KNH_ASSERT(IS_Method(mtd));
	KNH_ASSERT(cid == DP(mtd)->cid);
	KNH_ASSERT_cid(cid);
	ClassStruct *cs = ctx->share->ClassTable[cid].cstruct;;
	size_t i;
	for(i = 0; i < knh_Array_size(cs->methods); i++) {
		Method *mtd2 = (Method*)knh_Array_n(cs->methods, i);
		if(DP(mtd2)->mn == DP(mtd)->mn) {
			char buf[CLASSNAME_BUFSIZ];
			knh_format_cmethodn(ctx, buf, sizeof(buf), cid, DP(mtd)->mn);
			KNH_WARNING(ctx, "Duplicated method: %s", buf);
			return ;
		}
	}
	if(knh_class_isSingleton(cid)) {
		DP(mtd)->flag = DP(mtd)->flag | KNH_FLAG_MF_STATIC;
	}
	knh_Array_add(ctx, cs->methods, UP(mtd));
}

/* ------------------------------------------------------------------------ */
/* [MethodField] */

void konoha_addMethodFieldTable(Ctx *ctx, MethodField *mf)
{
	knh_hcode_t h = knh_MethodField_hachCode(ctx, mf);
	HashMap *hmap = DP(ctx->sys)->MethodFieldHashMap;
	if(IS_NOTNULL(hmap)) {
		KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
		MethodField *mf2 = (MethodField*)knh_HashMap_get__hcode(ctx, hmap, h);
		if(IS_MethodField(mf2)) {
			//DBG2_P("MISS!! %lu  rtype=%s%s psize=%d", h, TYPEQN(mf2->rtype), mf2->psize);
		}
		if(mf2->psize != 0) {
			knh_HashMap_set__hcode(ctx, hmap, h, UP(mf));
			DBG2_({
				mf2 = (MethodField*)knh_HashMap_get__hcode(ctx, hmap, h);
				KNH_ASSERT(mf == mf2);
			});
		}
		KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	}
}

/* ------------------------------------------------------------------------ */

MethodField *konoha_findMethodField0(Ctx *ctx, knh_type_t rtype)
{
	HashMap *hmap = DP(ctx->sys)->MethodFieldHashMap;
	if(IS_NOTNULL(hmap)) {
		knh_hcode_t h = rtype;
		KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
		MethodField *mf = (MethodField*)knh_HashMap_get__hcode(ctx, hmap, h);
		KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
		if(IS_MethodField(mf)) {
			if(mf->rtype == rtype && mf->psize == 0) {
				return mf;
			}
		}
	}
	MethodField *mf = new_MethodField(ctx, rtype, 0);
	konoha_addMethodFieldTable(ctx, mf);
	return mf;
}

/* ------------------------------------------------------------------------ */

MethodField *konoha_findMethodField1(Ctx *ctx, knh_type_t rtype, knh_type_t p1, knh_fieldn_t fn1)
{
	HashMap *hmap = DP(ctx->sys)->MethodFieldHashMap;
	if(IS_NOTNULL(hmap)) {
		knh_hcode_t h = rtype;
		h = knh_mparam_hcode(h, p1, fn1);
		KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
		MethodField *mf = (MethodField*)knh_HashMap_get__hcode(ctx, hmap, h);
		KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
		if(IS_MethodField(mf)) {
			if(mf->rtype == rtype && mf->psize == 1 && mf->p0.type == p1 && mf->p0.fn == fn1) {
				return mf;
			}
		}
	}
	MethodField *mf = new_MethodField(ctx, rtype, 1);
	mf->p0.type = p1;
	mf->p0.fn = fn1;
	konoha_addMethodFieldTable(ctx, mf);
	return mf;
}

/* ------------------------------------------------------------------------ */
/* [field_method] */

static
METHOD knh_fmethod_getter(Ctx *ctx, knh_sfp_t *sfp)
{
	DBG2_ASSERT(IS_Method(sfp[-1].mtd));
	KNH_RETURN(ctx, sfp, KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta));
}

/* ------------------------------------------------------------------------ */

static
METHOD knh_fmethod_igetter(Ctx *ctx, knh_sfp_t *sfp)
{
	DBG2_ASSERT(IS_Method(sfp[-1].mtd));
#ifdef KNH_USING_UNBOXFIELD
	knh_int_t *data = (knh_int_t*)(&(KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta)));
	KNH_RETURN_Int(ctx, sfp, data[0]);
#else/*KNH_USING_UNBOXFIELD*/
	Int *o = (Int*)KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta);
	KNH_RETURN_Int(ctx, sfp, o->n.ivalue);
#endif/*KNH_USING_UNBOXFIELD*/
}

/* ------------------------------------------------------------------------ */

static
METHOD knh_fmethod_fgetter(Ctx *ctx, knh_sfp_t *sfp)
{
	DBG2_ASSERT(IS_Method(sfp[-1].mtd));
#ifdef KNH_USING_UNBOXFIELD
	knh_float_t *data = (knh_float_t*)(&(KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta)));
	KNH_RETURN_Float(ctx, sfp, data[0]);
#else/*KNH_USING_UNBOXFIELD*/
	Float *o = (Float*)KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta);
	KNH_RETURN_Float(ctx, sfp, o->n.fvalue);
#endif/*KNH_USING_UNBOXFIELD*/
}

/* ------------------------------------------------------------------------ */

static
METHOD knh_fmethod_bgetter(Ctx *ctx, knh_sfp_t *sfp)
{
	DBG2_ASSERT(IS_Method(sfp[-1].mtd));
#ifdef KNH_USING_UNBOXFIELD
	knh_bool_t *data = (knh_bool_t*)(&(KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta)));
	KNH_RETURN_Boolean(ctx, sfp, data[0]);
#else/*KNH_USING_UNBOXFIELD*/
	Boolean *o = (Boolean*)KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta);
	KNH_RETURN_Boolean(ctx, sfp, o->n.bvalue);
#endif/*KNH_USING_UNBOXFIELD*/
}

/* ------------------------------------------------------------------------ */

static
METHOD knh_fmethod_setter(Ctx *ctx, knh_sfp_t *sfp)
{
	DBG2_ASSERT(IS_Method(sfp[-1].mtd));
	KNH_MOV(ctx, KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta), sfp[1].o);
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */

static
METHOD knh_fmethod_bsetter(Ctx *ctx, knh_sfp_t *sfp)
{
	DBG2_ASSERT(IS_Method(sfp[-1].mtd));
#ifdef KNH_USING_UNBOXFIELD
	knh_bool_t *data = (knh_bool_t*)(&(KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta)));
	data[0] = sfp[1].bvalue;
#else/*KNH_USING_UNBOXFIELD*/
	KNH_MOV(ctx, KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta), new_Boolean(ctx, sfp[1].bvalue));
#endif/*KNH_USING_UNBOXFIELD*/
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */

static
METHOD knh_fmethod_isetter(Ctx *ctx, knh_sfp_t *sfp)
{
	DBG2_ASSERT(IS_Method(sfp[-1].mtd));
#ifdef KNH_USING_UNBOXFIELD
	knh_int_t *data = (knh_int_t*)(&(KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta)));
	data[0] = sfp[1].ivalue;
#else/*KNH_USING_UNBOXFIELD*/
	Int *n = new_Int(ctx, sfp[1].ivalue);
	KNH_MOV(ctx, KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta), n);
#endif/*KNH_USING_UNBOXFIELD*/
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */

static
METHOD knh_fmethod_insetter(Ctx *ctx, knh_sfp_t *sfp)
{
	DBG2_ASSERT(IS_Method(sfp[-1].mtd));
	Int *n = IS_NULL(sfp[1].o) ? sfp[1].i : new_Int(ctx, sfp[1].ivalue);
	KNH_MOV(ctx, KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta), n);
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */

static
METHOD knh_fmethod_fsetter(Ctx *ctx, knh_sfp_t *sfp)
{
	DBG2_ASSERT(IS_Method(sfp[-1].mtd));
#ifdef KNH_USING_UNBOXFIELD
	knh_float_t *data = (knh_float_t*)(&(KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta)));
	data[0] = sfp[1].fvalue;
#else/*KNH_USING_UNBOXFIELD*/
	Float *n = new_Float(ctx, sfp[1].fvalue);
	KNH_MOV(ctx, KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta), n);
#endif/*KNH_USING_UNBOXFIELD*/
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */

static
METHOD knh_fmethod_fnsetter(Ctx *ctx, knh_sfp_t *sfp)
{
	DBG2_ASSERT(IS_Method(sfp[-1].mtd));
	Float *n = IS_NULL(sfp[1].o) ? sfp[1].f : new_Float(ctx, sfp[1].fvalue);
	KNH_MOV(ctx, KNH_FIELDn(sfp[0].o, DP(sfp[-1].mtd)->delta), n);
	KNH_RETURN_void(ctx, sfp);
}


/* ------------------------------------------------------------------------ */

static
Method *new_Method_getter(Ctx *ctx, knh_class_t cid, knh_methodn_t mn, knh_type_t type, int idx)
{
	knh_fmethod f = knh_fmethod_getter;
	if(IS_ubxint(type)) {
		f = knh_fmethod_igetter;
	}
	else if(IS_ubxfloat(type)) {
		f = knh_fmethod_fgetter;
	}
	else if(IS_ubxboolean(type)) {
		f = knh_fmethod_bgetter;
	}
	Method *mtd = new_Method(ctx, KNH_FLAG_MF_GENERATED, cid, mn, f);
	DP(mtd)->delta = idx;
	KNH_SETv(ctx, DP(mtd)->mf, konoha_findMethodField0(ctx, type));
	return mtd;
}

/* ------------------------------------------------------------------------ */

static
Method *new_Method_setter(Ctx *ctx, knh_class_t cid, knh_methodn_t mn, knh_type_t type, int idx)
{
	knh_fmethod f = knh_fmethod_setter;
	if(IS_ubxint(type)) {
		f = knh_fmethod_isetter;
	}
	else if(IS_bxint(type)) {
		f = knh_fmethod_insetter;
	}
	else if(IS_ubxfloat(type)) {
		f = knh_fmethod_fsetter;
	}
	else if(IS_bxfloat(type)) {
		f = knh_fmethod_fnsetter;
	}
	else if(IS_ubxboolean(type)) {
		f = knh_fmethod_bsetter;
	}
	Method *mtd = new_Method(ctx, KNH_FLAG_MF_GENERATED, cid, mn, f);
	DP(mtd)->delta = idx;
	KNH_SETv(ctx, DP(mtd)->mf, konoha_findMethodField1(ctx, TYPE_void, type, FIELDN_v));
	return mtd;
}

/* ------------------------------------------------------------------------ */

Method*
knh_Class_getMethod__(Ctx *ctx, knh_class_t this_cid, knh_methodn_t mn, knh_bool_t gen)
{
	knh_class_t cid = this_cid;
	TAIL_RECURSION:;
	KNH_ASSERT_cid(cid);
	{
		ClassStruct *cs = ctx->share->ClassTable[cid].cstruct;;
		size_t i;
		for(i = 0; i < knh_Array_size(cs->methods); i++) {
			Method *mtd = (Method*)knh_Array_n(cs->methods, i);
			if(DP(mtd)->mn == mn) return mtd;
		}
		if(cid == CLASS_Object) {
			cid = this_cid;
			goto L_GenerateField;
		}
		cid = ctx->share->ClassTable[cid].supcid;
	}
	goto TAIL_RECURSION;

	L_GenerateField:;
	if(METHODN_IS_GETTER(mn)) {
		knh_index_t idx = knh_Class_indexOfField(ctx, this_cid, METHODN_TOFIELDN(mn));
		if(idx == -1) {
			goto L_NoSuchMethod;
		}
		else {
			knh_cfield_t *cf = knh_Class_fieldAt(ctx, this_cid, idx);
			if(!KNH_FLAG_IS(cf->flag, KNH_FLAG_CFF_GETTER)) {
				goto L_NoSuchMethod;
			}
			else {
				Method *mtd = new_Method_getter(ctx, this_cid, mn, cf->type, idx);
				ClassStruct *cs = ctx->share->ClassTable[this_cid].cstruct;;
				knh_Array_add(ctx, cs->methods, UP(mtd));
				return mtd;
			}
		}
	}

	if(METHODN_IS_SETTER(mn)) {
		knh_index_t idx = knh_Class_indexOfField(ctx, this_cid, METHODN_TOFIELDN(mn));
		if(idx == -1) {
			goto L_NoSuchMethod;
		}
		else {
			knh_cfield_t *cf = knh_Class_fieldAt(ctx, this_cid, idx);
			if(!KNH_FLAG_IS(cf->flag, KNH_FLAG_CFF_SETTER)) {
				goto L_NoSuchMethod;
			}
			else {
				Method *mtd = new_Method_setter(ctx, this_cid, mn, cf->type, idx);
				ClassStruct *cs = ctx->share->ClassTable[this_cid].cstruct;;
				knh_Array_add(ctx, cs->methods, UP(mtd));
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
			ClassStruct *cs = ctx->share->ClassTable[this_cid].cstruct;;
			DBG2_({
				char bufcm[CLASSNAME_BUFSIZ];
				knh_format_cmethodn(ctx, bufcm, sizeof(bufcm), cid, mn);
				DBG2_P("GENERATE NoSuchMethod: %s", bufcm);
			})
			knh_Array_add(ctx, cs->methods, UP(mtd));
			return mtd;
		}
	}
	else {
		return (Method*)KNH_NULL;
	}
}

#define _knh_Class_getMethod(ctx, c, mn)    knh_Class_getMethod__(ctx, c, mn, 0)
#define _knh_Class_findMethod(ctx, c, mn)   knh_Class_getMethod__(ctx, c, mn, 1)

/* ======================================================================== */
/* [utils] */

Method *konoha_lookupMethod(Ctx *ctx, knh_class_t cid, knh_methodn_t mn)
{
	KNH_ASSERT(!METHODN_IS_MOVTEXT(mn));
	knh_hcode_t h = ((((knh_hcode_t)cid) << (sizeof(knh_class_t) * 8)) + mn) % ctx->cachesize;
	Method *mtd = ctx->mtdCache[h];
	if(mtd != NULL) {
		if(DP(mtd)->mn == mn) {
			if(DP(mtd)->cid == cid || knh_class_instanceof(ctx, cid, DP(mtd)->cid)) {
				knh_stat_mtdCacheHit(ctx);
				return mtd;
			}
		}
		knh_stat_mtdCacheMiss(ctx);
		DBG2_({
			char bufcm[CLASSNAME_BUFSIZ];
			knh_format_cmethodn(ctx, bufcm, sizeof(bufcm), cid, mn);
			DBG2_P("Cache missed. looking up %s", bufcm);
		})
	}
	mtd = knh_Class_findMethod(ctx, cid, mn);
	ctx->mtdCache[h] = mtd;
	return mtd;
}

/* ------------------------------------------------------------------------ */

Method *konoha_lookupFormatter(Ctx *ctx, knh_class_t cid, knh_methodn_t mn)
{
	DBG2_ASSERT(METHODN_IS_MOVTEXT(mn));
	knh_hcode_t h = ((((knh_hcode_t)cid) << (sizeof(knh_class_t) * 8)) + mn) % ctx->cachesize;
	Method *mtd = ctx->fmtCache[h];
	if(mtd != NULL) {
		if(DP(mtd)->mn == mn) {
			if(DP(mtd)->cid == cid || knh_class_instanceof(ctx, cid, DP(mtd)->cid)) {
				knh_stat_fmtCacheHit(ctx);
				return mtd;
			}
		}
		knh_stat_fmtCacheMiss(ctx);
		DBG2_({
			char bufcm[CLASSNAME_BUFSIZ];
			knh_format_cmethodn(ctx, bufcm, sizeof(bufcm), cid, mn);
			DBG2_P("Cache missed. looking up %s <%s>", bufcm, CLASSN(DP(mtd)->cid));
		})
	}
	mtd = knh_Class_findMethod(ctx, cid, mn);
	ctx->fmtCache[h] = mtd;
	return mtd;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
