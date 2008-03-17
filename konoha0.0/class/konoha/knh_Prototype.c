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
knh_Prototype_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Prototype *b = (Prototype*)s;
	knh_int_t i;
	for(i = 0; i < KNH_PROTOTYPE_FIELDSIZE; i++) {
		KNH_INITv(b->value[i], KNH_NULL);
	}
	KNH_INITv(b->ns, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

#define _knh_Prototype_struct_copy   NULL

/* ------------------------------------------------------------------------ */

#define _knh_Prototype_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void knh_Prototype_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Prototype *b = (Prototype*)s;
	knh_int_t i;
	for(i = 0; i < KNH_PROTOTYPE_FIELDSIZE; i++) {
		gc(ctx, b->value[i]);
	}
	gc(ctx, b->ns);
}

/* ======================================================================== */
/* [constructors] */

Prototype *new_Prototype(Ctx *ctx, knh_nsn_t nsn)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_snprintf(buf, sizeof(buf), "%s.Prototype", NSN(nsn));

	NameSpace *runtime_ns = ((Context*)ctx)->runtime->ns;
	knh_class_t cid = knh_NameSpace_getClass(ctx, runtime_ns, B(buf));
	Prototype* b = NULL;

	if(cid != CLASS_unknown) {
		b = knh_tclass_safevalue(ctx, cid);
		DEBUG_ASSERT(knh_Object_cid(b) == cid);
		return b;
	}

	cid = knh_tclass_newId(ctx);
	b = (Prototype*)knh_Object_malloc0(ctx, KNH_FLAG_Prototype, cid, sizeof(Prototype));
	knh_Prototype_struct_init(ctx, (Struct*)b, 0, NULL);
	KNH_SETv(ctx, b->ns, new_NameSpace(ctx, runtime_ns, knh_tnsn_name(nsn)));

	String *cname = new_String__fast(ctx, CLASS_String__class, B(buf));
	KNH_TCLASS(ctx, KNH_FLAG_Prototype|KNH_FLAG_CF_PRIVATE, cname, cid, STRUCT_Prototype, CLASS_Object, b, NULL, 0);
	knh_NameSpace_setClass(ctx, runtime_ns, cname, cid);
	Method *mtd = new_Method(ctx, 0, cid, METHODN_run, NULL);
	KNH_SETv(ctx, mtd->mf, new_MethodField__PrototypeRun(ctx));
	knh_Class_addMethod__fast(ctx, cid, mtd);
	return b;
}

/* ======================================================================== */
/* [method] */

//
//void knh_Prototype_set(Ctx *ctx, Prototype *b, knh_index_t idx, Object *value)
//{
//	DEBUG_ASSERT(0 <= idx && idx < KNH_PROTOTYPE_FIELDSIZE);
//	knh_Class_fields_set_value(ctx, knh_Object_cid(b), idx, value);
//	KNH_SETv(ctx, b->value[idx], value);	
//}
//
///* ------------------------------------------------------------------------ */
//
//
//Object *knh_Prototype_get(Ctx *ctx, Prototype *b, knh_index_t idx)
//{
//	DEBUG_ASSERT(0 <= idx && idx < KNH_PROTOTYPE_FIELDSIZE);
//	return b->value[idx];
//}

/* ======================================================================== */
/* [Object] */


knh_bool_t knh_Class_isPrototype(Ctx *ctx, knh_class_t cid)
{
	return (cid > KONOHA_TSTRUCT_SIZE && knh_tclass_topsid(cid) == STRUCT_Prototype);
}

/* ======================================================================== */
/* [movabletext] */

/* @method void Prototype.%dump(OutputStream w, Any m) */

void knh_Prototype__dump(Ctx *ctx, Prototype *b, OutputStream *w, Any *m)
{
	knh_int_t i, indent = 0;
	if(indent != 0) {
		knh_putc(ctx, w, '[');
	}
	for(i = 0; i < KNH_PROTOTYPE_FIELDSIZE; i++) {
		knh_cfield_t *cf = knh_Class_fieldAt(knh_Object_cid(b), i);
		if(cf->fn == FIELDN_NONAME) break;
		if(indent == 0) {
			knh_printf(ctx, w, "[%d] %s%s %s=", i, TYPEN(cf->type), TYPEQ(cf->type), FIELDN(cf->fn));	
			knh_format(ctx, w, METHODN__dump, b->value[i], KNH_NULL);
			knh_println(ctx, w, STEXT(""));
		}else{
			if(i > 0) {
				knh_write_delim(ctx, w);
			}
			knh_printf(ctx, w, "%s=", FIELDN(cf->fn));
			knh_format(ctx, w, METHODN__dump, b->value[i], KNH_NULL);
		}
	}
	if(indent != 0) {
		knh_putc(ctx, w, ']');
	}
}

#ifdef __cplusplus
}
#endif
