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

/* ------------------------------------------------------------------------ */
/* [macros] */


#define _knh_Method_mn(mtd)    DP(mtd)->mn
#define _knh_Method_mf(mtd)    DP(mtd)->mf

static METHOD knh_Method_fAbstractMethod(Ctx *ctx, knh_sfp_t *sfp);
void knh_KLRCode__dump_(Ctx *ctx, KLRCode* o, OutputStream *w, Any *m);


/* ======================================================================== */
/* [structs] */

void knh_Method_struct_init(Ctx *ctx, knh_Method_struct *b, int init, Object *cs)
{
	b->flag   = 0;
	b->delta  = 0;
	b->cid    = CLASS_Object;
	b->mn     = METHODN_NONAME;
	b->func  = knh_Method_fAbstractMethod;
	KNH_INITv(b->mf, MF_Any_Any_);
	b->code  = NULL;
}

/* ------------------------------------------------------------------------ */

void knh_Method_struct_copy(Ctx *ctx, knh_Method_struct *b, knh_Method_struct *b2)
{
	b2->flag  = b->flag;
	b2->delta  = b->delta;
	b2->cid    = b->cid;
	b2->mn     = b->mn;
	KNH_INITv(b2->mf, b->mf);
	b2->func   = b->func;
	if(knh_Method_isObjectCode(b)) {
		KNH_INITv(b2->code, b->code);
	}
	else {
		b2->code = b->code;
	}
}

/* ------------------------------------------------------------------------ */

void
knh_Method_struct_traverse(Ctx *ctx, knh_Method_struct *b, f_traverse gc)
{
	gc(ctx, UP(b->mf));
	if((b->flag & KNH_FLAG_MF_OBJECTCODE) == KNH_FLAG_MF_OBJECTCODE) {
		gc(ctx, (Object*)b->code);
		if(IS_SWEEP(gc)) {
			b->code = NULL;
		}
	}
}

/* ======================================================================== */
/* [AbstractMethod] */

static
METHOD knh_Method_fAbstractMethod(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_NULL(sfp[0].o)) {
		METHOD_RETURN(ctx, sfp, KNH_NULL);
	}
	{
		Method *mtd = sfp[-1].mtd;
		knh_wbuf_t cb = knh_Context_wbuf(ctx);
		knh_printf(ctx, cb.w, "AbstractMethod!!: %C.%M", knh_Object_cid(sfp[0].o), DP(mtd)->mn);
		{
			String *s = new_String__wbuf(ctx, cb);
			KNH_THROW(ctx, s);
		}
	}
}

/* ------------------------------------------------------------------------ */
/* @method Boolean Method.isAbstract() */

INLINE
knh_bool_t knh_Method_isAbstract(Method *o)
{
	return (DP(o)->func == knh_Method_fAbstractMethod);
}

/* ======================================================================== */
/* [constructors] */

Method* new_Method(Ctx *ctx, knh_flag_t flag, knh_class_t cid, knh_methodn_t mn, f_method func)
{
	Method* o =
		(Method*)new_Object_malloc(ctx, FLAG_Method, CLASS_Method, sizeof(knh_Method_struct));
	knh_Method_struct_init(ctx, DP(o), 0, NULL);
	DP(o)->flag  = flag;
	DP(o)->cid    = cid;
	DP(o)->mn     = mn;
	if(METHODN_IS_MOVTEXT(DP(o)->mn)) {
		KNH_SETv(ctx, DP(o)->mf, MF_void_OutputStream_Any);
	}
	DP(o)->func  = (func == NULL) ? knh_Method_fAbstractMethod : func;
	DP(o)->code  = NULL;
	o->fcall_1 = DP(o)->func;
	o->code_2  = NULL;
	return o;
}

/* ------------------------------------------------------------------------ */

knh_hcode_t knh_Method_hashCode(Method *o)
{
	knh_hcode_u u;
	u.value2.u1 = DP(o)->cid;
	u.value2.u1 = DP(o)->mn;
	return u.hcode;
}

/* ------------------------------------------------------------------------ */

int knh_Method_compareTo(Method *o, Method *o2)
{
	char buf[CLASSNAME_BUFSIZ], buf2[CLASSNAME_BUFSIZ];
	return knh_strcmp(
		knh_format_cmethodn(buf, sizeof(buf), DP(o)->cid, DP(o)->mn),
		knh_format_cmethodn(buf2, sizeof(buf2), DP(o)->cid, DP(o2)->mn));
}

/* ------------------------------------------------------------------------ */
/* [abstract] */

void knh_Method_toAbstract(Ctx *ctx, Method *o)
{
	if(knh_Method_isObjectCode(o)) {
		KNH_FINALv(ctx, DP(o)->code);
		knh_Method_setObjectCode(o, 0);
	}
	DP(o)->func = knh_Method_fAbstractMethod;
	o->fcall_1 = knh_Method_fAbstractMethod;
	o->code_2  = NULL;
}

/* ------------------------------------------------------------------------ */

void knh_ClassStruct_toAbstractAll(Ctx *ctx, ClassStruct *o)
{
	Array *a = DP(o)->methods;
	if(IS_bArray(a)) {
		size_t i;
		for(i = 0; i < knh_Array_size(a); i++) {
			Method *mtd = (Method*)knh_Array_n(a, i);
			knh_Method_toAbstract(ctx, mtd);
		}
	}
}

/* ======================================================================== */
/* [NoSuchMethod] */

METHOD knh_Method_fNoSuchMethod(Ctx *ctx, knh_sfp_t *sfp)
{
	Method *mtd = sfp[-1].mtd;
	char bufcm[CLASSNAME_BUFSIZ];
	knh_format_cmethodn(bufcm, sizeof(bufcm), knh_Object_cid(sfp[0].o), DP(mtd)->mn);
	String *s = new_String(ctx, B(bufcm), NULL);
	KNH_THROW(ctx, s);
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_Method_isNoSuchMethod(Method *o)
{
	return (DP(o)->func == knh_Method_fNoSuchMethod);
}

/* ------------------------------------------------------------------------ */

Method* new_Method__NoSuchMethod(Ctx *ctx, knh_class_t cid, knh_methodn_t mn)
{
	Method *mtd = new_Method(ctx, 0, cid, mn, knh_Method_fNoSuchMethod);
	return mtd;
}

/* ======================================================================== */
/* [name] */

knh_bool_t knh_methodn_isNew(knh_methodn_t mn)
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

knh_bool_t knh_Method_isNew(Method *o)
{
	knh_class_t rtype = TYPE_UNMASK_NN(knh_Method_rtype(o));
	if(rtype != DP(o)->cid) {
		return 0;
	}
	return knh_methodn_isNew(DP(o)->mn);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_methodn_isOp(knh_methodn_t mn)
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

/* @method String! Method.getName() */

INLINE
String* knh_Method_getName(Ctx *ctx, Method *o)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_format_methodn(buf, sizeof(buf), DP(o)->mn);
	return new_String(ctx, B(buf), NULL);
}

/* ------------------------------------------------------------------------ */

/* @method String! Method.getURN() */

String* knh_Method_getURN(Ctx *ctx, Method *o)
{
	char buf[CLASSNAME_BUFSIZ];
	char buf2[CLASSNAME_BUFSIZ];
	knh_format_methodn(buf2, sizeof(buf2), DP(o)->mn);
	knh_snprintf(buf, sizeof(buf), "%s.%s", CLASSN(DP(o)->cid), buf2);
	return new_String(ctx, B(buf), NULL);
}

///* ------------------------------------------------------------------------ */
//
//knh_bool_t knh_Method_update_flag(Ctx *ctx, Method *o, knh_flag_t flag)
//{
//	return (DP(o)->flag == flag);
//}
//
///* ------------------------------------------------------------------------ */
//
//knh_bool_t knh_Method_update_func(Ctx *ctx, Method *o, f_method func)
//{
//	if(func == NULL) {
//		func = knh_Method_fAbstractMethod;
//	}
//	DP(o)->func   = func;
//	DP(o)->delta  = 0;
//	knh_Method_code_traverse(ctx, b, knh_sweep);
//	return 1;
//}

/* ======================================================================== */
/* [movabletext] */

/* @method void Method.%s(OutputStream w, Any m) */

void knh_Method__s(Ctx *ctx, Method *o, OutputStream *w, Any *m)
{
	knh_write__s(ctx, w, CTXCLASSN(DP(o)->cid));
	knh_putc(ctx, w, '.');
	knh_write__mn(ctx, w, DP(o)->mn);
}

/* ------------------------------------------------------------------------ */
/* @method void Method.%k(OutputStream w, Any m) */

void knh_Method__k(Ctx *ctx, Method *o, OutputStream *w, Any *m)
{
	if(knh_Method_isAbstract(o)) {
		knh_write(ctx, w, STEXT("@abstract"));
		knh_putc(ctx, w, ' ');
	}

	if(knh_Method_rtype(o) == TYPE_void) {
		knh_write(ctx, w, knh_String_tobytes(TS_void));
	}else{
//		knh_write__type(ctx, w, knh_pmztype_totype(ctx, knh_Method_rtype(o), DP(o)->cid));
		knh_write__type(ctx, w, knh_Method_rtype(o));
	}
	knh_putc(ctx, w, ' ');
	knh_Method__s(ctx, o, w, KNH_NULL);
	knh_putc(ctx, w, '(');
	knh_int_t i;
	for(i = 0; i < knh_Method_psize(o); i++) {
		if(i > 0) {
			knh_write_delim(ctx, w);
		}
		knh_mfield_t mf = knh_Method_pfields(o, i);
		//knh_write__type(ctx, w, knh_pmztype_totype(ctx, mf.type, DP(o)->cid));
		knh_write__type(ctx, w, mf.type);
		knh_putc(ctx, w, ' ');
		knh_write(ctx, w, B(FIELDN(mf.fn)));
	}
	if(knh_Method_isVarArgs(o)) {
		knh_write_delim(ctx, w);
		knh_write_dots(ctx, w);
	}
	knh_putc(ctx, w, ')');
}

/* ------------------------------------------------------------------------ */
/* @method void Method.%dump(OutputStream w, Any m) */

void knh_Method__dump(Ctx *ctx, Method *o, OutputStream *w, Any *m)
{
	knh_Method__k(ctx, o, w, m);
	knh_println(ctx, w, STEXT(""));
	if(knh_Method_isObjectCode(o)) {
		if(IS_KLRCode((Object*)DP(o)->code)) {
			knh_KLRCode__dump_(ctx, (KLRCode*)DP(o)->code, w, UP(o));
		}
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
