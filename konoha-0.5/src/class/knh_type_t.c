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

/* ======================================================================== */
/* [macros] */

/* ------------------------------------------------------------------------ */

knh_class_t knh_pmztype_toclass(Ctx *ctx, knh_type_t t, knh_class_t this_cid)
{
	knh_class_t cid = CLASS_type(t);
	KNH_ASSERT_cid(cid);
	KNH_ASSERT_cid(this_cid);
	if(cid == CLASS_This) {
		return this_cid;
	}
	if(cid == CLASS_Any1) {
		return ctx->share->ClassTable[this_cid].p1;
	}
	if(cid == CLASS_Any2) {
		return ctx->share->ClassTable[this_cid].p2;
	}
	if(ClassTable(cid).bcid == CLASS_Closure) {
		knh_type_t r0 = ClassTable(cid).r0;
		knh_type_t p1 = ClassTable(cid).p1;
		knh_type_t p2 = ClassTable(cid).p2;
		knh_type_t p3 = ClassTable(cid).p3;
		knh_type_t rr0 = knh_pmztype_totype(ctx, r0, this_cid);
		knh_type_t pp1 = knh_pmztype_totype(ctx, p1, this_cid);
		knh_type_t pp2 = knh_pmztype_totype(ctx, p2, this_cid);
		knh_type_t pp3 = knh_pmztype_totype(ctx, p3, this_cid);
		if(r0 != rr0 || p1 != pp1 || p2 != pp2 || p3 != pp3) {
			return knh_class_Closure(ctx, rr0, pp1, pp2, pp3);
		}
		return cid;
	}
	if(knh_Class_isGenerics(cid)) { /* Iterator<This> */
		knh_class_t p1 = ClassTable(cid).p1;
		knh_class_t p2 = ClassTable(cid).p2;
		knh_class_t pp1 = knh_pmztype_toclass(ctx, p1, this_cid);
		knh_class_t pp2 = knh_pmztype_toclass(ctx, p2, this_cid);
		if(p1 != pp1 || p2 != pp2) {
			return knh_class_Generics(ctx, ClassTable(cid).bcid, pp1, pp2);
		}
		return cid;
	}
	return cid;
}

/* ------------------------------------------------------------------------ */

knh_type_t knh_pmztype_totype(Ctx *ctx, knh_type_t t, knh_class_t this_cid)
{
	knh_class_t cid = CLASS_type(t), mask = (t & KNH_FLAG_TF_NA);
	KNH_ASSERT_cid(cid);
	KNH_ASSERT_cid(this_cid);
	if(cid == CLASS_This) {
		return this_cid | mask;
	}
	if(cid == CLASS_Any1) {
		return ctx->share->ClassTable[this_cid].p1 | mask;
	}
	if(cid == CLASS_Any2) {
		return ctx->share->ClassTable[this_cid].p2 | mask;
	}
	if(ClassTable(cid).bcid == CLASS_Closure) {
		knh_type_t r0 = ClassTable(cid).r0;
		knh_type_t p1 = ClassTable(cid).p1;
		knh_type_t p2 = ClassTable(cid).p2;
		knh_type_t p3 = ClassTable(cid).p3;
		knh_type_t rr0 = knh_pmztype_totype(ctx, r0, this_cid);
		knh_type_t pp1 = knh_pmztype_totype(ctx, p1, this_cid);
		knh_type_t pp2 = knh_pmztype_totype(ctx, p2, this_cid);
		knh_type_t pp3 = knh_pmztype_totype(ctx, p3, this_cid);
		if(r0 != rr0 || p1 != pp1 || p2 != pp2 || p3 != pp3) {
			return knh_class_Closure(ctx, rr0, pp1, pp2, pp3) | mask;
		}
		return cid | mask;
	}
	if(knh_Class_isGenerics(cid)) { /* Iterator<This> */
		knh_class_t p1 = ClassTable(cid).p1;
		knh_class_t p2 = ClassTable(cid).p2;
		knh_class_t pp1 = knh_pmztype_toclass(ctx, p1, this_cid);
		if(p2 != CLASS_unknown) {
			knh_class_t pp2 = knh_pmztype_toclass(ctx, p2, this_cid);
			if(p1 != pp1 || p2 != pp2) {
				return knh_class_Generics(ctx, ClassTable(cid).bcid, pp1, pp2) | mask;
			}
		}else {
			if(p1 != pp1) {
				return knh_class_Generics(ctx, ClassTable(cid).bcid, pp1, CLASS_unknown) | mask;
			}
		}
		return cid | mask;
	}
	return t;
}


/* ------------------------------------------------------------------------ */

knh_class_t knh_class_Array(Ctx *ctx, knh_class_t p1)
{
	char buf[CLASSNAME_BUFSIZ];
	if(p1 == CLASS_Any) return CLASS_Array;
	knh_snprintf(buf, sizeof(buf), "%s[]", CLASSN(p1));
	knh_class_t cid = knh_getcid(ctx, B(buf));
	if(cid == CLASS_unknown) {
		DBG_P("Generating %s", buf);
		return knh_addGenericsClass(ctx, CLASS_newid, new_String(ctx, B(buf), NULL), CLASS_Array, p1, CLASS_unknown);
	}
	//DBG2_P("cid=%d, %s", cid, buf);
	return cid;
}

/* ------------------------------------------------------------------------ */

knh_class_t knh_class_Iterator(Ctx *ctx, knh_class_t p1)
{
	char buf[CLASSNAME_BUFSIZ];
	if(p1 == CLASS_Any) return CLASS_Iterator;
	knh_snprintf(buf, sizeof(buf), "%s..", CLASSN(p1));
	knh_class_t cid = knh_getcid(ctx, B(buf));
	if(cid == CLASS_unknown) {
		DBG_P("Generating %s", buf);
		return knh_addGenericsClass(ctx, CLASS_newid, new_String(ctx, B(buf), NULL), CLASS_Iterator, p1, CLASS_unknown);
	}
	return cid;
}

/* ------------------------------------------------------------------------ */

knh_class_t knh_class_Generics(Ctx *ctx, knh_class_t bcid, knh_class_t p1, knh_class_t p2)
{
	DBG2_ASSERT(bcid != CLASS_Closure);
	if(bcid == CLASS_Iterator) {
		return knh_class_Iterator(ctx, p1);
	}
	else if(bcid == CLASS_Array){
		return knh_class_Array(ctx, p1);
	}
	if(p1 == CLASS_Any && (p2 == CLASS_Any || p2 == CLASS_unknown)) {
		return bcid;
	}
	else {
		char buf[CLASSNAME_BUFSIZ];
		if(p2 == CLASS_unknown) {
			knh_snprintf(buf, sizeof(buf), "%s<%s>", CLASSN(bcid), CLASSN(p1));
		}
		else {
			knh_snprintf(buf, sizeof(buf), "%s<%s,%s>", CLASSN(bcid), CLASSN(p1), CLASSN(p2));
		}
		knh_class_t cid = knh_getcid(ctx, B(buf));
		if(cid == CLASS_unknown) {
			DBG_P("Generating %s", buf);
			return knh_addGenericsClass(ctx, CLASS_newid, new_String(ctx, B(buf), NULL), bcid, p1, p2);
		}
		return cid;
	}
}

/* ------------------------------------------------------------------------ */

char* knh_format_type(Ctx *ctx, char *buf, size_t bufsiz, knh_type_t type)
{
	if(type == TYPE_void) {
		knh_snprintf(buf, bufsiz, "void");
		return buf;
	}
	if(type == TYPE_void) {
		knh_snprintf(buf, bufsiz, "var");
		return buf;
	}
	knh_class_t cid = CLASS_type(type);
	if(!(cid < ctx->share->ClassTableSize)) {
		cid = CLASS_Any;
		type = cid;
	}
	KNH_ASSERT_cid(cid);
	char *cname = knh_ClassTable_CLASSN(ctx, cid);
	if(IS_ubxtype(type)) {
		knh_snprintf(buf, bufsiz, "%s", cname);
		buf[0] = tolower(buf[0]);
		return buf;
	}
	if(IS_NNTYPE(type)) {
		knh_snprintf(buf, bufsiz, "%s", cname);
	}
	else {
		knh_snprintf(buf, bufsiz, "%s?", cname);
	}
	return buf;
}

/* ======================================================================== */
/* [movabletext] */

char *TYPEQ(knh_type_t type)
{
	if(IS_NNTYPE(type)) {
		return "";
	}
	return "?";
}

/* ------------------------------------------------------------------------ */

#define _TYPEN(type)  knh_TYPEN(ctx,type)

char *knh_TYPEN(Ctx *ctx, knh_type_t type)
{
	if(type == TYPE_void) return "void";
	if(type == TYPE_var)  return "var";
	knh_class_t cid = CLASS_type(type);
	return CLASSN(cid);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
