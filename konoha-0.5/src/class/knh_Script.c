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

/* ======================================================================== */
/* [constructors] */

Script *new_Script(Ctx *ctx, knh_bytes_t nsname)
{
	knh_class_t cid = knh_ClassTable_newId(ctx);
	knh_Script_t *o = (Script*)new_Object_init(ctx, FLAG_Script, CLASS_Script, 0);
	o->h.cid = cid;

	char buf[CLASSNAME_BUFSIZ];
	knh_ClassTable_t *TC = (knh_ClassTable_t*)(&ctx->share->ClassTable[cid]);
	knh_snprintf(buf, sizeof(buf), "%s.Script", (char*)nsname.buf);

	KNH_ASSERT(ctx->share->ClassTable[cid].class_cid == NULL);

	TC->cflag  = CFLAG_Script;
	TC->oflag  = FLAG_Script;

	TC->bcid   = CLASS_Script; /* CLASS_Object */
	TC->supcid = CLASS_Script;

	TC->offset = 0;
	TC->sid    = CLASS_Script;
	TC->bsize  = KNH_SCRIPT_FIELDSIZE;
	TC->size = TC->bsize * sizeof(knh_Object_t*);

	konoha_setClassName(ctx, cid, new_String(ctx, B(buf), NULL));
	KNH_INITv(TC->cstruct, new_ClassStruct0(ctx, KNH_SCRIPT_FIELDSIZE, KNH_SCRIPT_FIELDSIZE/2));

	KNH_ASSERT(TC->cmap == NULL);
	KNH_INITv(TC->cmap, ctx->share->ClassTable[CLASS_Script].cmap);

	KNH_ASSERT(TC->cspec == NULL);
	konoha_setClassDefaultValue(ctx, cid, UP(o), NULL);

	Method *mtd = new_Method(ctx, 0, cid, METHODN_lambda, NULL);
	KNH_SETv(ctx, DP(mtd)->mf, konoha_findMethodField0(ctx, TYPE_Any));
	knh_Class_addMethod(ctx, cid, mtd);
	return o;
}

///* ------------------------------------------------------------------------ */
//
//static
//void knh_Script_restart(Ctx *ctx, Script *o)
//{
//	knh_class_t cid = o->h.cid;
//	knh_ClassTable_t *TC = (knh_ClassTable_t*)(&ctx->share->ClassTable[cid]);
//	int i;
//	for(i = 0; i < KNH_SCRIPT_FIELDSIZE; i++) {
//		KNH_SETv(ctx, o->fields[i], KNH_NULL);
//	}
//	KNH_ASSERT(TC->lname != NULL);
//	DBG2_P("%s", knh_String_tochar(TC->lname));
//	KNH_SETv(ctx, TC->cstruct, new_ClassStruct0(ctx, TC->sid));
//	DBG2_P("refc=%d", (int)o->h.refc);
//	KNH_ASSERT(o->h.refc == 2);
//	{
//		Method *mtd = new_Method(ctx, 0, cid, METHODN_lambda, NULL);
//		KNH_SETv(ctx, DP(mtd)->mf, MF_Any);
//		knh_Class_addMethod__fast(ctx, cid, mtd);
//	}
//}


/* ======================================================================== */
/* [method] */

//
//void knh_Script_set(Ctx *ctx, Script *b, knh_index_t idx, Object *value)
//{
//	KNH_ASSERT(0 <= idx && idx < KNH_PROTOTYPE_FIELDSIZE);
//	knh_Class_fields_set_value(ctx, knh_Object_cid(b), idx, value);
//	KNH_SETv(ctx, b->fields[idx], value);
//}
//
///* ------------------------------------------------------------------------ */
//
//
//Object *knh_Script_get(Ctx *ctx, Script *b, knh_index_t idx)
//{
//	KNH_ASSERT(0 <= idx && idx < KNH_PROTOTYPE_FIELDSIZE);
//	return b->fields[idx];
//}

///* ======================================================================== */
///* [Object] */
//
//knh_bool_t knh_Class_isScript(Ctx *ctx, knh_class_t cid)
//{
//	return (cid > KONOHA_TSTRUCT_SIZE && knh_tclass_topsid(cid) == STRUCT_Script);
//}


/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */
/* @method void Script.%k(OutputStream w, String m) */

void knh_Script__k(Ctx *ctx, Script *o, OutputStream *w, String *m)
{
//	int i;
//	knh_putc(ctx, w, '{');
//	for(i = 0; i < KNH_SCRIPT_FIELDSIZE; i++) {
//		knh_cfield_t *cf = knh_Class_fieldAt(ctx, knh_Object_cid(o), i);
//		if(cf == NULL) break;
//		if(cf->fn == FIELDN_NONAME) break;
//		if(i > 0) {
//			knh_write_delim(ctx, w);
//		}
//		knh_printf(ctx, w, "%s: ", FIELDN(cf->fn));
//		knh_format(ctx, w, METHODN__k, o->fields[i], KNH_NULL);
//	}
//	knh_putc(ctx, w, '}');
	knh_write(ctx, w, STEXT("<script>"));
}

/* ------------------------------------------------------------------------ */
/* @method void Script.%dump(OutputStream w, String m) */

void knh_Script__dump(Ctx *ctx, Script *o, OutputStream *w, String *m)
{
	size_t i;
	for(i = 0; i < KNH_SCRIPT_FIELDSIZE; i++) {
		knh_cfield_t *cf = knh_Class_fieldAt(ctx, knh_Object_cid(o), i);
		if(cf == NULL) break;
		if(cf->fn == FIELDN_NONAME) break;
		{
			knh_type_t type = knh_pmztype_totype(ctx, cf->type, knh_Object_cid(o));
			knh_printf(ctx, w, "[%d] %T %s=", i, type, FIELDN(cf->fn));
			knh_format(ctx, w, METHODN__k, o->fields[i], KNH_NULL);
			knh_println(ctx, w, STEXT(""));
		}
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
