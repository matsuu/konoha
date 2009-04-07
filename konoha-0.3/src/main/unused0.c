///****************************************************************************
// * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
// *
// * Copyright (c) 2005-2008, Kimio Kuramitsu <kimio at ynu.ac.jp>
// *           (c) 2008-      Konoha Software Foundation
// * All rights reserved.
// *
// * You may choose one of the following two licenses when you use konoha.
// * See www.konohaware.org/license.html for further information.
// *
// * (1) GNU General Public License 2.0      (with    KONOHA_UNDER_GPL2)
// * (2) Konoha Software Foundation License 1.0
// *
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
// * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// *
// ****************************************************************************/
//
///* ************************************************************************ */
//
//#include"commons.h"
//
///* ************************************************************************ */
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
///* ======================================================================== */
///* [konoha] */
//
//KNHAPI(knh_class_t) konoha_addClass(Ctx *ctx, knh_flag_t flag, char *name, int method_size)
//{
//	NameSpace *ns = knh_Context_getNameSpace(ctx);;
//	char bufc[CLASSNAME_BUFSIZ];
//	knh_snprintf(bufc, sizeof(bufc), "%s.%s", knh_String_tochar(DP(ns)->nsname), name);
//	KNH_NOTICE(ctx, "adding a native class: %s", bufc);
//
//	knh_class_t cid = knh_ClassTable_newId(ctx);
//	konoha_seClassTableName(ctx, cid, new_String(ctx, B(bufc), NULL));
//
//	knh_ClassTable_t *TC = (knh_ClassTable_t*)&(ctx->share->ClassTable[cid]);
//
//	TC->cflag  = flag;
//	TC->oflag  = KNH_FLAG_CF2OF(TC->cflag);
//
//	TC->bcid   = CLASS_Any;
//	TC->supcid = CLASS_Object;
//	TC->offset = 0;
//	TC->sid    = 0;
//	TC->bsize = 0;
//	TC->size = 0;
//
//	KNH_ASSERT(TC->cstruct == NULL);
//	KNH_INITv(TC->cstruct, new_ClassStruct0(ctx, cid, method_size));
//
//	KNH_ASSERT(TC->cmap == NULL);
//	KNH_INITv(TC->cmap, ctx->share->ClassTable[CLASS_Any].cmap); /* Default*/
//
//	konoha_seClassTableDefaultValue(ctx, cid, new_Object_init(ctx, TC->oflag, cid, 0), NULL);
//	knh_NameSpace_setLocalName(ctx, ns, cid);
//	return cid;
//}
//
///* ------------------------------------------------------------------------ */
//
//KNHAPI(knh_class_t) konoha_addVirtualClass(Ctx *ctx, char *name, int method_size)
//{
//	return konoha_addClass(ctx, KNH_FLAG_CF_SINGLETON, name, method_size);
//}
//
///* ------------------------------------------------------------------------ */
//
//KNHAPI(knh_class_t) konoha_addNaitiveClass(Ctx *ctx, char *name, int method_size)
//{
//	return konoha_addClass(ctx, 0, name, method_size);
//}
//
///* ------------------------------------------------------------------------ */
//
//KNHAPI(void) konoha_addDefaultObject(Ctx *ctx, Object *o)
//{
//	knh_class_t cid = knh_Object_cid(o);
//	KNH_NOTICE(ctx, "set a new default value: %o", o);
//	konoha_seClassTableDefaultValue(ctx, cid, o, NULL);
//}
//
/////* ======================================================================== */
/////* [METHOD] */
/////* konoha_addMethod(ctx, "Float! Math.abs(Float! n)", f); */
////
////#ifndef StmtMACRO
////#define StmtMETHOD_method(stmt)         DP(stmt)->tokens[2]
////#endif
////
////KNHAPI(void) konoha_addMethod(Ctx *ctx, char *kscript, knh_fmethod f)
////{
////	NameSpace *ns = knh_Context_getNameSpace(ctx);;
////	knh_sfp_t *lsfp = KNH_LOCAL(ctx);
////	Stmt *stmt = knh_bytes_parseStmt(ctx, kscript);
////	KNH_LPUSH(ctx, stmt);
////	if(SP(stmt)->stt == STT_METHOD) {
////		knh_StmtMETHOD_typing(ctx, stmt, knh_Context_getAsm(ctx), ns);
////		Method *mtd = (Method*)DP(StmtMETHOD_method(stmt))->data;
////		if(IS_Method(mtd)) {
////			if(!knh_Method_isAbstract(mtd)) {
////				char bufcm[CLASSNAME_BUFSIZ];
////				knh_format_cmethodn(ctx, bufcm, sizeof(bufcm), DP(mtd)->cid, DP(mtd)->mn);
////				KNH_NOTICE(ctx, "PACKAGE[%s]: rewriting method: %s", knh_String_tochar(DP(ns)->nsname), bufcm);
////				knh_Method_toAbstract(ctx, mtd);
////			}
////			knh_Method_syncfunc(mtd, f);
////		}
////		else {
////			goto L_ERROR;
////		}
////	}
////	else {
////		goto L_ERROR;
////	}
////	KNH_LOCALBACK(ctx, lsfp);
////	return;
////
////	L_ERROR:;
////	KNH_WARNING(ctx, "PACKAGE[%s]: cannot add method: %s", knh_String_tochar(DP(ns)->nsname), kscript);
////	KNH_LOCALBACK(ctx, lsfp);
////}
//
///* ------------------------------------------------------------------------ */
//
//KNHAPI(void) konoha_addFormatter(Ctx *ctx, char *cname, char *fmt, void *f)
//{
//	TODO();
//}
//
/////* ======================================================================== */
/////* [MAPPER] */
/////* konoha_addMapper(ctx, "", f); */
////
////void KNHAPI konoha_addMethod(Ctx *ctx, char *kscript, knh_fmethod f)
////{
////
////}
//
///* ======================================================================== */
///* [CONST] */
///* konoha_addConst(ctx, "Math.PI", 3.14159) */
//
//KNHAPI(void) konoha_addConst(Ctx *ctx, char *name, Object *o)
//{
//	NameSpace *ns = knh_Context_getNameSpace(ctx);;
//	knh_bytes_t t = B(name);
//	int loc;
//	if((loc = knh_bytes_index(t, '.')) == -1) {
//		if(knh_bytes_index(t, '_') == -1) {
//			knh_NameSpace_addConst(ctx, ns, new_String__T(ctx, name), o);
//		}
//		else {
//			if(knh_tConst_addGlobalConst(ctx, new_String__T(ctx, name), o) == 0) {
//				goto L_ERROR;;
//			}
//		}
//	}
//	else {
//		knh_class_t cid = knh_NameSpace_geClassTable(ctx, ns, knh_bytes_first(t, loc));
//		if(knh_tConst_addClassConst(ctx, cid, knh_bytes_last(t, loc+1), o) == 0) {
//			goto L_ERROR;
//		}
//	}
//	return;
//
//	L_ERROR:;
//	KNH_WARNING(ctx, "PACKAGE[%s]: cannot add const: %s", knh_String_tochar(DP(ns)->nsname), name);
//}
//
///* ------------------------------------------------------------------------ */
//
//KNHAPI(void) konoha_addIntConst(Ctx *ctx, char *name, knh_int_t value)
//{
//	konoha_addConst(ctx, name, (Object*)new_Int(ctx, (knh_int_t)value));
//}
//
///* ------------------------------------------------------------------------ */
//
//KNHAPI(void) konoha_addIntegerConst(Ctx *ctx, char *name, knh_int_t value)
//{
//	konoha_addConst(ctx, name, (Object*)new_Int(ctx, value));
//}
//
///* ------------------------------------------------------------------------ */
//
//KNHAPI(void) konoha_addFloatConst(Ctx *ctx, char *name, knh_float_t value)
//{
//	konoha_addConst(ctx, name, (Object*)new_Float(ctx, value));
//}
//
///* ------------------------------------------------------------------------ */
//
//KNHAPI(void) konoha_addStringConst(Ctx *ctx, char *name, char *text)
//{
//	konoha_addConst(ctx, name, (Object*)new_String__T(ctx, text));
//}
//
///* ======================================================================== */
///* [DRIVER] */
//
///* konoha_addDriver(ctx, "mysql", KNH_DRVAPI_TYPE__DB, &DBDRV) */
//
//KNHAPI(void) konoha_addDriver(Ctx *ctx, char *name, int type, void *drv)
//{
//	TODO();
//}
//
//
///* ------------------------------------------------------------------------ */
//
//#ifdef __cplusplus
//}
//#endif
