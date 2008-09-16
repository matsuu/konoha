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
/* [konoha] */

static Stmt *konoha_parse(Ctx *ctx, char *kscript);

/* ======================================================================== */
/* [CLASS] */

KNHAPI(knh_class_t) konoha_addVirtualClass(Ctx *ctx, char *name, int method_size)
{
	NameSpace *ns = knh_Context_getNameSpace(ctx);;
	char bufc[CLASSNAME_BUFSIZ];
	knh_snprintf(bufc, sizeof(bufc), "%s.%s", knh_String_tochar(DP(ns)->nsname), name);
	DBG2_P("class='%s'", bufc);

	knh_class_t cid = knh_tClass_newId(ctx);
	KNH_TCLASS_NAME(ctx, cid, new_String(ctx, B(bufc), NULL));

	knh_tClass_t *TC = (knh_tClass_t*)&(knh_tClass[cid]);

	TC->cflag  = 0 | KNH_FLAG_CF_SINGLETON;
	TC->oflag  = KNH_FLAG_CF2OF(TC->cflag);

	TC->bcid   = CLASS_Object;
	TC->supcid = CLASS_Object;
	TC->offset = 0;
	TC->sid    = 0;
	TC->bsize = 0;
	TC->size = 0;

	KNH_ASSERT(TC->cstruct == NULL);
	KNH_INITv(TC->cstruct, new_ClassStruct0(ctx, cid, method_size));

	KNH_ASSERT(TC->cmap == NULL);
	KNH_INITv(TC->cmap, new_ClassMap0(ctx, 4));

	KNH_TCLASS_DEFAULT(ctx, cid, new_PObject__NNctx(ctx, TC->oflag, CLASS_Object, cid), NULL);
	knh_NameSpace_setLocalName(ctx, ns, cid);
	return cid;
}

///* ------------------------------------------------------------------------ */
//
//knh_class_t KNHAPI konoha_addWrapperClass(Ctx *ctx, char *name, knh_class_t supcid, int method_size)
//{
//	NameSpace *ns = knh_Context_getNameSpace(ctx);;
//	char bufc[CLASSNAME_BUFSIZ];
//	knh_snprintf(bufc, sizeof(bufc), "%s.%s", knh_String_tochar(DP(ns)->nsname), name);
//	DBG2_P("class='%s'", bufc);
//
//	knh_class_t cid = knh_tClass_newId(ctx);
//	KNH_TCLASS_NAME(ctx, cid, new_String(ctx, B(bufc), NULL));
//
//	knh_tClass_t *TC = (knh_tClass_t*)&(knh_tClass[cid]);
//
//	TC->cflag  = 0;
//	TC->oflag  = KNH_FLAG_CF2OF(TC->cflag);
//
//	TC->bcid   = CLASS_Object;
//	TC->supcid = supcid;
//	TC->offset = 0;
//	TC->sid    = 0;
//	TC->bsize = 0;
//	TC->size = 0;
//
//	KNH_ASSERT(TC->cstruct == NULL);
//	KNH_INITv(TC->cstruct, new_ClassStruct0(ctx, cid, method_size));
//
//	KNH_ASSERT(TC->cmap == NULL);
//	KNH_INITv(TC->cmap, new_ClassMap0(ctx, 4));
//
//	KNH_TCLASS_DEFAULT(ctx, cid, new_Object__RAW(ctx, TC->oflag, cid, 0), NULL);
//	return cid;
//}

/* ======================================================================== */
/* [METHOD] */
/* konoha_addMethod(ctx, "Float! Math.abs(Float! n)", f); */

#ifndef StmtMACRO
#define StmtMETHOD_method(stmt)         DP(stmt)->tokens[2]
#endif

KNHAPI(void) konoha_addMethod(Ctx *ctx, char *kscript, f_method f)
{
	NameSpace *ns = knh_Context_getNameSpace(ctx);;
	KNH_LOPEN(ctx, 0);
	Stmt *stmt = konoha_parse(ctx, kscript);
	KNH_LPUSH(ctx, stmt);
	if(SP(stmt)->stt == STT_METHOD) {
		knh_StmtMETHOD_name(ctx, stmt, knh_Context_getCompiler(ctx), ns, -1);
		Method *mtd = (Method*)DP(StmtMETHOD_method(stmt))->data;
		if(IS_Method(mtd)) {
			if(!knh_Method_isAbstract(mtd)) {
				char bufcm[CLASSNAME_BUFSIZ];
				knh_format_cmethodn(bufcm, sizeof(bufcm), DP(mtd)->cid, DP(mtd)->mn);
				KNH_NOTICE(ctx, "PACKAGE[%s]: rewriting method: %s", knh_String_tochar(DP(ns)->nsname), bufcm);
				knh_Method_toAbstract(ctx, mtd);
			}
			DP(mtd)->func = f;
			(mtd)->fcall_1 = f;
		}
		else {
			goto L_ERROR;
		}
	}
	else {
		goto L_ERROR;
	}
	KNH_LCLOSE(ctx);
	return;

	L_ERROR:;
	KNH_WARNING(ctx, "PACKAGE[%s]: cannot add method: %s", knh_String_tochar(DP(ns)->nsname), kscript);
	KNH_LCLOSE(ctx);
}

///* ======================================================================== */
///* [MAPPER] */
///* konoha_addMapper(ctx, "", f); */
//
//void KNHAPI konoha_addMethod(Ctx *ctx, char *kscript, f_method f)
//{
//
//}

/* ======================================================================== */
/* [CONST] */
/* konoha_addConst(ctx, "Math.PI", 3.14159) */

KNHAPI(void) konoha_addConst(Ctx *ctx, char *name, Object *o)
{
	NameSpace *ns = knh_Context_getNameSpace(ctx);;
	knh_bytes_t t = B(name);
	int loc;
	if((loc = knh_bytes_index(t, '.')) == -1) {
		knh_NameSpace_addLocalConst(ctx, ns, new_String__T(ctx, name), o);
	}
	else {
		knh_class_t cid = knh_NameSpace_getClass(ctx, ns, knh_bytes_first(t, loc));
		if(knh_tClass_addClassConst(ctx, cid, knh_bytes_last(t, loc+1), o) == 0) {
			goto L_ERROR;
		}
	}
	return;

	L_ERROR:;
	KNH_WARNING(ctx, "PACKAGE[%s]: cannot add const: %s", knh_String_tochar(DP(ns)->nsname), name);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_addIntConst(Ctx *ctx, char *name, knh_int_t value)
{
	konoha_addConst(ctx, name, (Object*)new_Int(ctx, value));
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_addInt64Const(Ctx *ctx, char *name, knh_int64_t value)
{
	konoha_addConst(ctx, name, (Object*)new_Int64(ctx, value));
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_addFloatConst(Ctx *ctx, char *name, knh_float_t value)
{
	konoha_addConst(ctx, name, (Object*)new_Float(ctx, value));
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_addStringConst(Ctx *ctx, char *name, char *text)
{
	konoha_addConst(ctx, name, (Object*)new_String__T(ctx, text));
}

/* ======================================================================== */
/* [DRIVER] */

/* konoha_addDriver(ctx, "mysql", KNH_DRVAPI_TYPE__DB, &DBDRV) */

KNHAPI(void) konoha_addDriver(Ctx *ctx, char *name, int type, void *drv)
{
	TODO();
}

/* ======================================================================== */
/* [UTILS] */

/* ------------------------------------------------------------------------ */

static
Stmt *konoha_parse(Ctx *ctx, char *kscript)
{
	knh_wbuf_t cwb = knh_Context_wbuf(ctx);
	knh_Bytes_write(ctx, cwb.ba, B(kscript));
	knh_Bytes_putc(ctx, cwb.ba, ';');
	InputStream *in = new_InputStream__Bytes(ctx, cwb.ba, cwb.pos, knh_Bytes_size(cwb.ba));
	DP(in)->fileid = 0;
	DP(in)->line = 0;
	Stmt *stmt = knh_konohac_parse(ctx, in);
	knh_Bytes_subclear(cwb.ba, cwb.pos);
	return stmt;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
