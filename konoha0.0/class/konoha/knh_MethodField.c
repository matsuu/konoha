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
knh_MethodField_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	MethodField *b =  (MethodField*)s1;
	b->flag = 0;
	b->size = knh_int_min(init, 255);
	b->params = (knh_mfield_t*)knh_malloc(ctx, b->size * sizeof(knh_mfield_t));
	knh_int_t i;
	for(i = 0; i < b->size; i++) {
		b->params[i].type = TYPE_any;
		b->params[i].fn   = FIELDN_NONAME;
	}
}

/* ------------------------------------------------------------------------ */

void knh_MethodField_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
	MethodField *b =  (MethodField*)s1;
	MethodField *b2 = (MethodField*)s2;
	b2->size  =  b->size;
	b2->params = (knh_mfield_t*)knh_malloc(ctx, b2->size * sizeof(knh_mfield_t));
	knh_int_t i;
	for(i = 0; i < b2->size; i++) {
		b2->params[i].type = b->params[i].type;
		b2->params[i].fn   = b->params[i].fn;
	}
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_MethodField_struct_compare(Ctx *ctx, Struct *s1, Struct *s2)
{
	MethodField *b =  (MethodField*)s1;
	MethodField *b2 = (MethodField*)s2;
	knh_int_t res = b->size < b2->size;
	if(res != 0) return res;
	res = b->flag - b2->flag;
	if(res != 0) return res;
	knh_index_t i;
	for(i = 0; i < b->size; i++) {
		res = b->params[i].type - b2->params[i].type;
		if(res != 0) return res;
#ifdef KONOHA_METHODFIELD_RESERVED_NAME  /* @option */
		res = b->params[i].fn - b2->params[i].fn;
		if(res != 0) return res;
#endif
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

void knh_MethodField_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	MethodField *b = (MethodField*)s;
	if(IS_SWEEP(gc)) {
		knh_free(b->params, b->size * sizeof(knh_mfield_t));
	}
}

/* ======================================================================== */
/* [constructors] */


MethodField* new_MethodField(Ctx *ctx, knh_flag_t flag, size_t size)
{
	MethodField* b = 
		(MethodField*)knh_Object_malloc0(ctx, KNH_FLAG_MethodField, CLASS_MethodField, sizeof(MethodField));
	knh_MethodField_struct_init(ctx, (Struct*)b, size, NULL);
	b->flag = flag & KNH_FLAG_MF_VARARGS;
	return b;
}

/* ======================================================================== */
/* [hcode] */

INLINE
knh_hcode_t knh_methodfield_hcode(knh_type_t r, knh_type_t a0, knh_type_t a1) 
{
	return (r + a0) + (a1 << 4);
}

/* ------------------------------------------------------------------------ */

knh_hcode_t knh_MethodField_hcode(MethodField *b) 
{
	switch(b->size) {
		case 0: return knh_methodfield_hcode(0, 0, 0);
		case 1: return knh_methodfield_hcode(b->params[0].type, 0, 0);
		case 2: return knh_methodfield_hcode(b->params[0].type, b->params[1].type, 0);
	}
	return knh_methodfield_hcode(b->params[0].type, b->params[1].type, b->params[2].type);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_MethodField_equalsType(MethodField *b, MethodField *b2)
{
	if(b->size != b2->size) return 0;
	if(b->flag != b2->flag) return 0;
	knh_index_t i;
	for(i = 0; i < b->size; i++) {
		if(b->params[i].type != b2->params[i].type) return 0;
	}
	return 1;
}

/* ======================================================================== */
/* [flag] */

INLINE
void knh_MethodField_setVarArgs(MethodField *b)
{
#ifdef MF_VARARGS
	b->flag |= MF_VARARGS;
#endif
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_MethodField_isVarArgs(MethodField *b)
{
#ifdef MF_VARARGS
	return ((b->flag & MF_VARARGS) == MF_VARARGS);
#endif
	return 0;
}

/* ======================================================================== */
/* [param] */

INLINE
knh_type_t knh_MethodField_rtype(MethodField *b)
{
	return b->params[0].type;
}

#define _knh_Method_rtype(mtd)          knh_MethodField_rtype(knh_Method_mf(mtd))

/* ------------------------------------------------------------------------ */

INLINE
size_t knh_MethodField_psize(MethodField *b)
{
	return b->size - 1;
}

#define _knh_Method_psize(mtd)      knh_MethodField_psize(knh_Method_mf(mtd))

/* ------------------------------------------------------------------------ */


knh_index_t knh_MethodField_pindex(MethodField *b, knh_fieldn_t fn)
{
	knh_index_t i;
	for(i = 1; i < b->size; i++) {
		if(b->params[i].fn == fn) return i-1;
	}
	return -1;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_type_t knh_MethodField_ptype(MethodField *b, size_t n)
{
	if(n < b->size - 1) {
		return b->params[n+1].type;
	}
	return b->params[b->size-1].type;
}

#define _knh_Method_ptype(mtd,n)          knh_MethodField_ptype(knh_Method_mf(mtd),n)

/* ------------------------------------------------------------------------ */

INLINE
knh_mfield_t knh_MethodField_pfields(MethodField *b, size_t n)
{
	if(n < b->size - 1) {
		return b->params[n+1];
	}
	return b->params[n+1];
}

#define _knh_Method_pfields(mtd,n)   knh_MethodField_pfields(knh_Method_mf(mtd),n)

/* ------------------------------------------------------------------------ */

INLINE
knh_mfield_t knh_MethodField_lastfield(MethodField *b)
{
	return b->params[b->size-1];
}

#define _knh_Method_lastfield(mtd)   knh_MethodField_lastfield(knh_Method_mf(mtd))

///* ======================================================================== */
///* [movabletext] */
//
///* @method void MethodField.%dump(OutputStream w, Any m) */
//
//
//void knh_MethodField__dump(Ctx *ctx, MethodField *b, OutputStream *w, Any *m)
//{
////	knh_fputc(ctx, w, '(');
////	knh_int_t i;
////	for(i = 1; i < b->size; i++) {
////		if(i > 1) knh_print_delim(ctx, w);
////		knh_type_p__s(ctx, b->params[i].type, w);
////		knh_fputc(ctx, w, ' ');
////		knh_prints(ctx, w, FIELDN(b->params[i].fn));
////	}
////	knh_fputc(ctx, w, ')');
//}

/* ======================================================================== */
/* [global] */

static Object *tglobalMethodFieldMovableText       = NULL;
static Object *tglobalMethodFieldNoSuchMethod      = NULL;
static Object *tglobalMethodFieldPrototypeRun      = NULL;

/* ------------------------------------------------------------------------ */


MethodField* new_MethodField__mt(Ctx *ctx)
{
	if(tglobalMethodFieldMovableText == NULL) {
		MethodField *mf = new_MethodField(ctx, 0, 3);
		mf->params[0].type = TYPE_void;
		mf->params[0].fn = FIELDN_return;
		mf->params[1].type = TYPE_OutputStream;
		mf->params[1].fn = FIELDN_w;
		mf->params[2].type = TYPE_any;
		mf->params[2].fn = FIELDN_m;
		tglobalMethodFieldMovableText = mf;
		KNH_TGLOBAL(tglobalMethodFieldMovableText);
	}	
	return (MethodField*)tglobalMethodFieldMovableText;
}
 
/* ------------------------------------------------------------------------ */


MethodField* new_MethodField__NoSuchMethod(Ctx *ctx)
{
	if(tglobalMethodFieldNoSuchMethod == NULL) {
		MethodField *mf = new_MethodField(ctx, KNH_FLAG_MF_VARARGS, 2);
		mf->params[0].type = TYPE_any;
		mf->params[0].fn = FIELDN_return;
		mf->params[1].type = TYPE_any;
		mf->params[1].fn = FIELDN_w;
		tglobalMethodFieldNoSuchMethod = mf;
		KNH_TGLOBAL(tglobalMethodFieldNoSuchMethod);
	}	
	return (MethodField*)tglobalMethodFieldNoSuchMethod;
}

/* ------------------------------------------------------------------------ */

MethodField* new_MethodField__PrototypeRun(Ctx *ctx)
{
	if(tglobalMethodFieldPrototypeRun == NULL) {
		MethodField *mf = new_MethodField(ctx, 0, 1);
		mf->params[0].type = TYPE_any;
		mf->params[0].fn = FIELDN_return;
		tglobalMethodFieldPrototypeRun = mf;
		KNH_TGLOBAL(tglobalMethodFieldPrototypeRun);
	}
	return (MethodField*)tglobalMethodFieldPrototypeRun;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
