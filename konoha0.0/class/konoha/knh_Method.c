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

#define _FIELDN_NONAME    ((knh_fieldn_t)-1)
#define _FIELDN_NEWID     ((knh_fieldn_t)-2)
#define _FIELDN_return    FIELDN_
#define _METHODN_NONAME   ((knh_methodn_t)-1)
#define _METHODN_NEWID    ((knh_methodn_t)-2)

#define _KNH_FLAG_FN_SUPER   KNH_FLAG_T0
#define _KNH_FLAG_FN_U1      KNH_FLAG_T1
#define _KNH_FLAG_FN_U2      KNH_FLAG_T2
#define _FIELDN_IS_SUPER(fnq)       ((fnq & KNH_FLAG_FN_SUPER) == KNH_FLAG_FN_SUPER)
#define _FIELDN_IS_U1(fnq)          ((fnq & KNH_FLAG_FN_U1) == KNH_FLAG_FN_U1)
#define _FIELDN_IS_U2(fnq)          ((fnq & KNH_FLAG_FN_U2) == KNH_FLAG_FN_U2)
#define _FIELDN_IS_PROTECTED(fnq)   (FIELDN_IS_U1(fnq)||FIELDN_IS_U2(fnq))
#define _FIELDN_UNMASK(fnq)         (fnq & (~(KNH_FLAG_FN_SUPER|KNH_FLAG_FN_U1|KNH_FLAG_FN_U2)))

//#define _METHODN_NONAME   KONOHA_TCLASS_SIZE
//#define _METHODN_NEWID    0

// 0000 0000 0000 0000
// 0100 0000 0000 0000  
// 0010 0000 0000 0000
// 0110 0000 0000 0000

#define _KNH_FLAG_MN_SUPER        KNH_FLAG_T0
#define _KNH_FLAG_MN_GETTER       KNH_FLAG_T1
#define _KNH_FLAG_MN_SETTER       KNH_FLAG_T2
#define _KNH_FLAG_MN_MOVTEXT      (KNH_FLAG_T1|KNH_FLAG_T2)
#define _KNH_FLAG_MN_FIELDN       (~(KNH_FLAG_T0|KNH_FLAG_T1|KNH_FLAG_T2))

#define _METHODN_IS_GETTER(mn)   ((mn & KNH_FLAG_MN_MOVTEXT) == KNH_FLAG_MN_GETTER)
#define _METHODN_TO_GETTER(mn)   (mn | KNH_FLAG_MN_GETTER)
#define _METHODN_IS_SETTER(mn)   ((mn & KNH_FLAG_MN_MOVTEXT) == KNH_FLAG_MN_SETTER)
#define _METHODN_TO_SETTER(mn)   (mn | KNH_FLAG_MN_SETTER)
#define _METHODN_IS_MOVTEXT(mn)  ((mn & KNH_FLAG_MN_MOVTEXT) == KNH_FLAG_MN_MOVTEXT)
#define _METHODN_TO_MOVTEXT(mn)  (mn | KNH_FLAG_MN_MOVTEXT)

#define _METHODN_TOFIELDN(mn)     (mn & KNH_FLAG_MN_FIELDN)

#define _knh_Method_mn(mtd)    (mtd)->mn
#define _knh_Method_mf(mtd)    (mtd)->mf

/* ======================================================================== */
/* [structs] */

void knh_Method_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	Method *b =  (Method*)s1;
	b->flag   = 0;
	b->delta  = 0;
	b->cid    = CLASS_Object;
	b->mn     = METHODN_NONAME;
	KNH_INITv(b->mf, KNH_NULL);
	b->func  = knh_Method_fAbstractMethod;
	b->code  = NULL;
}

/* ------------------------------------------------------------------------ */

void knh_Method_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
	Method *b =  (Method*)s1;
	Method *b2 = (Method*)s2;
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

knh_int_t
knh_Method_struct_compare(Ctx *ctx, Struct *s1, Struct *s2) 
{
	Method *b =  (Method*)s1;
	Method *b2 = (Method*)s2;
	knh_int_t res = knh_strcmp(METHODN(b->mn), METHODN(b2->mn));
	if(res == 0) {
		return knh_type_compare(ctx, b->cid, b2->cid);
	}
	return res;
}

/* ------------------------------------------------------------------------ */

void 
knh_Method_code_traverse(Ctx *ctx, Method *b, f_gc gc)
{
	if(knh_Method_isObjectCode(b)) {
		gc(ctx, (Object*)b->code);	
		if(IS_SWEEP(gc)) {
			b->code = NULL;
		}
	}
}

/* ------------------------------------------------------------------------ */

void 
knh_Method_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Method *b = (Method*)s;
	gc(ctx, b->mf);
	knh_Method_code_traverse(ctx, b, gc);
}

/* ======================================================================== */
/* [constructors] */


Method* new_Method(Ctx *ctx, knh_flag_t flag, knh_class_t cid, knh_methodn_t mn, f_method func)
{
	Method* b = 
		(Method*)knh_Object_malloc0(ctx, KNH_FLAG_Method, CLASS_Method, sizeof(Method));
	knh_Method_struct_init(ctx, (Struct*)b, 0, NULL);
	b->flag  = flag;
	b->cid    = cid;
	b->mn     = mn;
	if(METHODN_IS_MOVTEXT(b->mn)) {
		KNH_SETv(ctx, b->mf, new_MethodField__mt(ctx));
	}
	b->func  = (func == NULL) ? knh_Method_fAbstractMethod : func;
	b->code  = NULL;
	return b;
}

/* ======================================================================== */
/* [AbstractMethod] */

void knh_Method_fAbstractMethod(Ctx *ctx, Object **sf)
{
	if(IS_NULL(sf[0])) {
		KNH_SETr(ctx, sf, KNH_NULL);
		return;
	}
	KNH_THROWf(ctx, "AbstractMethod!!: %s.%s", 
		CLASSN(knh_Object_cid(sf[0])), METHODN(((Method*)sf[-1])->mn));
}

/* ------------------------------------------------------------------------ */
/* @method Bool Method.isAbstract() */

INLINE
knh_bool_t knh_Method_isAbstract(Method *b)
{
	return (b->func == knh_Method_fAbstractMethod);
}

/* ------------------------------------------------------------------------ */

void knh_Method_toAbstract(Ctx *ctx, Method *b)
{
	if(knh_Method_isObjectCode(b)) {
		KNH_FINALv(ctx, b->code);
		knh_Method_setObjectCode(b, 0);
	}
	b->func = knh_Method_fAbstractMethod;
}

/* ------------------------------------------------------------------------ */
/* [abstract] */

void knh_ClassStruct_toAbstractAll(Ctx *ctx, ClassStruct *b) 
{
	DEBUG_ASSERT(IS_Array(b->methods));
	knh_int_t i;
	for(i = 0; i < knh_Array_size(b->methods); i++) {
		Method *mtd = knh_Array_n(b->methods, i);
		knh_Method_toAbstract(ctx, mtd);
	}
}

/* ======================================================================== */
/* [NoSuchMethod] */

Object *
knh_Method_returnValue(Ctx *ctx, Method *b)
{
	knh_type_t rtype = TYPE_TONOTNULL(knh_Method_rtype(b));
	if(knh_tclass_hasDefaultValue(rtype)) {
		return knh_tclass_safevalue(ctx, rtype);
	}
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

void
knh_Method_fNoSuchMethod(Ctx *ctx, Object **sf)
{
	Method *mtd = (Method*)sf[-1];
	if(IS_NULL(sf[0])) {
		KNH_SETr(ctx, sf, knh_Method_returnValue(ctx, mtd));
	}
	else {
		knh_buffer_t cb = knh_Context_buffer(ctx);
		knh_printf(ctx, cb.w, "NoSuchMethod!!: %C.%M", knh_Object_cid(sf[0]), (mtd)->mn);
		String *s = new_String__buffer(ctx, CLASS_String, cb);
		KNH_THROW(ctx, s);
	}
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_Method_isNoSuchMethod(Method *b)
{
	return (b->func == knh_Method_fNoSuchMethod);
}

/* ------------------------------------------------------------------------ */

Method* new_Method__NoSuchMethod(Ctx *ctx, knh_class_t cid, knh_methodn_t mn) 
{
	Method *mtd = new_Method(ctx, 0, cid, mn, knh_Method_fNoSuchMethod);
	KNH_SETv(ctx, mtd->mf, new_MethodField__NoSuchMethod(ctx));
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

knh_bool_t knh_Method_isNew(Method *b)
{
	knh_class_t rtype = TYPE_TONOTNULL(knh_Method_rtype(b));
	if(rtype != b->cid) {
		return 0;
	}
	return knh_methodn_isNew(b->mn);
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
String* knh_Method_getName(Ctx *ctx, Method *b)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_format_methodn(buf, sizeof(buf), b->mn);
	return new_String__fast(ctx, CLASS_String, B(buf));
}

/* ------------------------------------------------------------------------ */

/* @method String! Method.getURN() */

String* knh_Method_getURN(Ctx *ctx, Method *b)
{
	char buf[CLASSNAME_BUFSIZ];
	char buf2[CLASSNAME_BUFSIZ];
	knh_format_methodn(buf2, sizeof(buf2), b->mn);
	knh_snprintf(buf, sizeof(buf), "%s.%s", CLASSN(b->cid), buf2);
	return new_String__fast(ctx, CLASS_String__urn, B(buf));
}

///* ------------------------------------------------------------------------ */
//
//knh_bool_t knh_Method_update_flag(Ctx *ctx, Method *b, knh_flag_t flag)
//{
//	return (b->flag == flag);
//}
//
///* ------------------------------------------------------------------------ */
//
//
//knh_bool_t knh_Method_update_func(Ctx *ctx, Method *b, f_method func)
//{
//	if(func == NULL) {
//		func = knh_Method_fAbstractMethod;
//	}
//	b->func   = func;
//	b->delta  = 0;
//	knh_Method_code_traverse(ctx, b, knh_sweep);
//	return 1;
//}

/* ======================================================================== */
/* [movabletext] */

/* @method void Method.%s(OutputStream w, Any m) */

void knh_Method__s(Ctx *ctx, Method *b, OutputStream *w, Any *m)
{
	knh_write__s(ctx, w, CLASSN(b->cid));
	knh_putc(ctx, w, '.');
	knh_write__mn(ctx, w, b->mn);
}

/* ------------------------------------------------------------------------ */
/* @method void Method.%dump(OutputStream w, Any m) */

void knh_Method__dump(Ctx *ctx, Method *b, OutputStream *w, Any *m)
{
	if(knh_Method_isAbstract(b)) {
		knh_write(ctx, w, STEXT("@abstract"));
		knh_putc(ctx, w, ' ');
	}

	if(knh_Method_rtype(b) == TYPE_void) {
		knh_write(ctx, w, STEXT("void"));
	}else{
		knh_write__type(ctx, w, knh_Method_rtype(b));
	}
	knh_putc(ctx, w, ' ');
	knh_Method__s(ctx, b, w, KNH_NULL);
	knh_putc(ctx, w, '(');
	knh_int_t i;
	for(i = 0; i < knh_Method_psize(b); i++) {
		if(i > 0) {
			knh_write_delim(ctx, w);
		}
		knh_mfield_t mf = knh_Method_pfields(b, i);
		knh_write__type(ctx, w, mf.type);
		knh_putc(ctx, w, ' ');
		knh_write(ctx, w, B(FIELDN(mf.fn)));
	}
	if(knh_Method_isVarArgs(b)) {
		knh_write_delim(ctx, w);
		knh_write_dots(ctx, w);
	}
	knh_putc(ctx, w, ')');
}


/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
