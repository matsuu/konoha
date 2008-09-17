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
/* [structs] */

void
knh_MethodField_struct_init(Ctx *ctx, knh_MethodField_struct *b, int init, Object *cs)
{
	int i;
	b->flag = 0;
	b->size = knh_int_min(init, 255);
	b->params = (knh_mfield_t*)KNH_MALLOC(ctx, b->size * sizeof(knh_mfield_t));
	for(i = 0; i < b->size; i++) {
		b->params[i].type = TYPE_any;
		b->params[i].fn   = FIELDN_NONAME;
	}
}

/* ------------------------------------------------------------------------ */

void knh_MethodField_struct_copy(Ctx *ctx, knh_MethodField_struct *b, knh_MethodField_struct *b2)
{
	int i;
	b2->size  =  b->size;
	b2->params = (knh_mfield_t*)KNH_MALLOC(ctx, b2->size * sizeof(knh_mfield_t));
	for(i = 0; i < b2->size; i++) {
		b2->params[i].type = b->params[i].type;
		b2->params[i].fn   = b->params[i].fn;
	}
}

///* ------------------------------------------------------------------------ */
//
//int knh_MethodField_struct_compare(knh_MethodField_struct *b, knh_MethodField_struct *b2)
//{
//	int i, res = b->size < b2->size;
//	if(res != 0) return res;
//	res = b->flag - b2->flag;
//	if(res != 0) return res;
//	for(i = 0; i < b->size; i++) {
//		res = b->params[i].type - b2->params[i].type;
//		if(res != 0) return res;
//		res = b->params[i].fn - b2->params[i].fn;
//		if(res != 0) return res;
//	}
//	return 0;
//}

/* ------------------------------------------------------------------------ */

void knh_MethodField_struct_traverse(Ctx *ctx, knh_MethodField_struct *b, f_traverse gc)
{
	if(IS_SWEEP(gc)) {
		KNH_FREE(b->params, b->size * sizeof(knh_mfield_t));
	}
}

/* ======================================================================== */
/* [constructors] */

MethodField* new_MethodField(Ctx *ctx, knh_flag_t flag, size_t size)
{
	knh_MethodField_t* o = 
		(MethodField*)new_Object_malloc(ctx, FLAG_MethodField, CLASS_MethodField, sizeof(knh_MethodField_struct));
	knh_MethodField_struct_init(ctx, DP(o), size, NULL);
	DP(o)->flag = flag & KNH_FLAG_MF_VARARGS;
	return o;
}

/* ------------------------------------------------------------------------ */

MethodField *new_MethodField__0(Ctx *ctx, knh_flag_t flag, knh_type_t rtype)
{
	MethodField *o = new_MethodField(ctx, flag, 1);
	knh_MethodField_struct *mf = DP(o);
	mf->params[0].type = rtype;
	mf->params[0].fn = FIELDN_return;
	return o;
}

/* ------------------------------------------------------------------------ */

MethodField *new_MethodField__1(Ctx *ctx, knh_flag_t flag, knh_type_t rtype, knh_type_t t1, knh_fieldn_t fn1)
{
	MethodField *o = new_MethodField(ctx, flag, 2);
	knh_MethodField_struct *mf = DP(o);
	mf->params[0].type = rtype;
	mf->params[0].fn = FIELDN_return;
	mf->params[1].type = t1;
	mf->params[1].fn = fn1;
	return o;
}

/* ------------------------------------------------------------------------ */

MethodField *new_MethodField__2(Ctx *ctx, knh_flag_t flag, knh_type_t rtype, knh_type_t t1, knh_fieldn_t fn1, knh_type_t t2, knh_fieldn_t fn2)
{
	MethodField *o = new_MethodField(ctx, flag, 3);
	knh_MethodField_struct *mf = DP(o);
	mf->params[0].type = rtype;
	mf->params[0].fn = FIELDN_return;
	mf->params[1].type = t1;
	mf->params[1].fn = fn1;
	mf->params[2].type = t2;
	mf->params[2].fn = fn2;
	return o;
}

/* ------------------------------------------------------------------------ */

MethodField *new_MethodField__3(Ctx *ctx, knh_flag_t flag, knh_type_t rtype, 
		knh_type_t t1, knh_fieldn_t fn1, knh_type_t t2, knh_fieldn_t fn2, knh_type_t t3, knh_fieldn_t fn3)
{
	MethodField *o = new_MethodField(ctx, flag, 4);
	knh_MethodField_struct *mf = DP(o);
	mf->params[0].type = rtype;
	mf->params[0].fn = FIELDN_return;
	mf->params[1].type = t1;
	mf->params[1].fn = fn1;
	mf->params[2].type = t2;
	mf->params[2].fn = fn2;
	mf->params[3].type = t3;
	mf->params[3].fn = fn3;
	return o;
}

/* ------------------------------------------------------------------------ */

MethodField *new_MethodField__4(Ctx *ctx, knh_flag_t flag, knh_type_t rtype, 
		knh_type_t t1, knh_fieldn_t fn1, knh_type_t t2, knh_fieldn_t fn2, 
		knh_type_t t3, knh_fieldn_t fn3, knh_type_t t4, knh_fieldn_t fn4)
{
	MethodField *o = new_MethodField(ctx, flag, 5);
	knh_MethodField_struct *mf = DP(o);
	mf->params[0].type = rtype;
	mf->params[0].fn = FIELDN_return;
	mf->params[1].type = t1;
	mf->params[1].fn = fn1;
	mf->params[2].type = t2;
	mf->params[2].fn = fn2;
	mf->params[3].type = t3;
	mf->params[3].fn = fn3;
	mf->params[4].type = t4;
	mf->params[4].fn = fn4;	
	return o;
}

/* ======================================================================== */
/* [hcode] */

INLINE
knh_hcode_t knh_methodfield_hcode(knh_type_t r, knh_type_t a0, knh_type_t a1) 
{
	return (r + a0) + (a1 << 4);
}

/* ------------------------------------------------------------------------ */

knh_hcode_t knh_MethodField_hcode(MethodField *o) 
{
	switch(DP(o)->size) {
		case 0: return knh_methodfield_hcode(0, 0, 0);
		case 1: return knh_methodfield_hcode(DP(o)->params[0].type, 0, 0);
		case 2: return knh_methodfield_hcode(DP(o)->params[0].type, DP(o)->params[1].type, 0);
	}
	return knh_methodfield_hcode(DP(o)->params[0].type, DP(o)->params[1].type, DP(o)->params[2].type);
}


/* ======================================================================== */
/* [flag] */

INLINE
void knh_MethodField_setVarArgs(MethodField *o)
{
#ifdef MF_VARARGS
	DP(o)->flag |= MF_VARARGS;
#endif
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_MethodField_isVarArgs(MethodField *o)
{
#ifdef MF_VARARGS
	return ((DP(o)->flag & MF_VARARGS) == MF_VARARGS);
#endif
	return 0;
}

/* ======================================================================== */
/* [param] */

INLINE
knh_type_t knh_MethodField_rtype(MethodField *o)
{
	return DP(o)->params[0].type;
}

#define _knh_Method_rtype(mtd)          knh_MethodField_rtype(knh_Method_mf(mtd))

/* ------------------------------------------------------------------------ */

INLINE
size_t knh_MethodField_psize(MethodField *o)
{
	return DP(o)->size - 1;
}

#define _knh_Method_psize(mtd)      knh_MethodField_psize(knh_Method_mf(mtd))

/* ------------------------------------------------------------------------ */

//knh_index_t knh_MethodField_pindex(MethodField *o, knh_fieldn_t fn)
//{
//	knh_index_t i;
//	for(i = 1; i < DP(o)->size; i++) {
//		if(DP(o)->params[i].fn == fn) return i-1;
//	}
//	return -1;
//}

/* ------------------------------------------------------------------------ */

INLINE
knh_type_t knh_MethodField_ptype(MethodField *o, size_t n)
{
	if(n < DP(o)->size - 1) {
		return DP(o)->params[n+1].type;
	}
	return DP(o)->params[DP(o)->size-1].type;
}

#define _knh_Method_ptype(mtd,n)          knh_MethodField_ptype(knh_Method_mf(mtd),n)

/* ------------------------------------------------------------------------ */

INLINE
knh_mfield_t knh_MethodField_pfields(MethodField *o, size_t n)
{
	if(n < DP(o)->size - 1) {
		return DP(o)->params[n+1];
	}
	return DP(o)->params[n+1];
}

#define _knh_Method_pfields(mtd,n)   knh_MethodField_pfields(knh_Method_mf(mtd),n)

/* ------------------------------------------------------------------------ */

INLINE
knh_mfield_t knh_MethodField_lastfield(MethodField *o)
{
	return DP(o)->params[DP(o)->size-1];
}

#define _knh_Method_lastfield(mtd)   knh_MethodField_lastfield(knh_Method_mf(mtd))

///* ======================================================================== */
///* [movabletext] */
//
///* @method void MethodField.%dump(OutputStream w, Any m) */
//
//
//void knh_MethodField__dump(Ctx *ctx, MethodField *o, OutputStream *w, Any *m)
//{
////	knh_fputc(ctx, w, '(');
////	knh_int_t i;
////	for(i = 1; i < DP(o)->size; i++) {
////		if(i > 1) knh_print_delim(ctx, w);
////		knh_type_p__s(ctx, DP(o)->params[i].type, w);
////		knh_fputc(ctx, w, ' ');
////		knh_prints(ctx, w, FIELDN(DP(o)->params[i].fn));
////	}
////	knh_fputc(ctx, w, ')');
//}

///* ======================================================================== */
///* [global] */
//
//static Object *knh_constMFMovableText       = NULL;
//static Object *knh_constMFNoSuchMethod      = NULL;
//static Object *knh_constMFPrototypeRun      = NULL;
//
///* ------------------------------------------------------------------------ */
//
//MethodField* new_MethodField__mt(Ctx *ctx)
//{
//	if(knh_constMFMovableText == NULL) {
//		MethodField *o = new_MethodField(ctx, 0, 3);
//		knh_Method_struct *mf = DP(o);
//		mf->params[0].type = TYPE_void;
//		mf->params[0].fn = FIELDN_return;
//		mf->params[1].type = TYPE_OutputStream;
//		mf->params[1].fn = FIELDN_w;
//		mf->params[2].type = TYPE_any;
//		mf->params[2].fn = FIELDN_m;
//		knh_constMFMovableText = o;
//		KNH_TSTATICOBJ(knh_constMFMovableText);
//	}	
//	return (MethodField*)knh_constMFMovableText;
//}
// 
///* ------------------------------------------------------------------------ */
//
//MethodField* new_MethodField__NoSuchMethod(Ctx *ctx)
//{
//	if(knh_constMFNoSuchMethod == NULL) {
//		MethodField *o = new_MethodField(ctx, KNH_FLAG_MF_VARARGS, 2);
//		knh_Method_struct *mf = DP(o);
//		mf->params[0].type = TYPE_any;
//		mf->params[0].fn = FIELDN_return;
//		mf->params[1].type = TYPE_any;
//		mf->params[1].fn = FIELDN_w;
//		knh_constMFNoSuchMethod = o;
//		KNH_TSTATICOBJ(knh_constMFNoSuchMethod);
//	}
//	return (MethodField*)knh_constMFNoSuchMethod;
//}
//
///* ------------------------------------------------------------------------ */
//
//MethodField* new_MethodField__PrototypeRun(Ctx *ctx)
//{
//	if(knh_constMFPrototypeRun == NULL) {
//		MethodField *o = new_MethodField(ctx, 0, 1);
//		knh_Method_struct *mf = DP(o);
//		mf->params[0].type = TYPE_any;
//		mf->params[0].fn = FIELDN_return;
//		knh_constMFPrototypeRun = o;
//		KNH_TSTATICOBJ(knh_constMFPrototypeRun);
//	}
//	return (MethodField*)knh_constMFPrototypeRun;
//}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
