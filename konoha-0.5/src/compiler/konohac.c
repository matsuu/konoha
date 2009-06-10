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
/* [CLASS] */

/* ------------------------------------------------------------------------ */
/* [META] */

static
knh_flag_t knh_StmtCLASS_flag(Ctx *ctx, Stmt *o)
{
	knh_flag_t flag = 0;
	if(IS_DictMap(DP(o)->metaDictMap)) {
		Object *v = knh_DictMap_get__b(ctx, DP(o)->metaDictMap, STEXT("Final"));
		if(IS_NOTNULL(v)) {
			flag |= KNH_FLAG_CF_FINAL;
		}
		v = knh_DictMap_get__b(ctx, DP(o)->metaDictMap, STEXT("Private"));
		if(IS_NOTNULL(v)) {
			flag |= KNH_FLAG_CF_PRIVATE;
		}
		v = knh_DictMap_get__b(ctx, DP(o)->metaDictMap, STEXT("Interface"));
		if(IS_NOTNULL(v)) {
			flag |= KNH_FLAG_CF_INTERFACE;
		}
		v = knh_DictMap_get__b(ctx, DP(o)->metaDictMap, STEXT("Singleton"));
		if(IS_NOTNULL(v)) {
			flag |= KNH_FLAG_CF_SINGLETON;
		}
		v = knh_DictMap_get__b(ctx, DP(o)->metaDictMap, STEXT("Release"));
		if(IS_NOTNULL(v)) {
			flag |= KNH_FLAG_CF_RELEASE;
		}
	}
	return flag;
}

/* ------------------------------------------------------------------------ */
/* [implements] */

static
Mapper* new_Mapper__interface(Ctx *ctx, knh_class_t scid, knh_class_t tcid)
{
	return new_Mapper(ctx, KNH_FLAG_MMF_INTERFACE, scid, tcid, knh_Mapper_fasis, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

static
void knh_class_addInterface(Ctx *ctx, knh_class_t cid, knh_class_t icid)
{
	KNH_ASSERT(!knh_class_isInterface(icid));
	if(knh_class_instanceof(ctx, cid, icid)) {
		return ;
	}
	else {
		knh_class_t isupcid = icid;
		int allchecked = 1;
		while(isupcid != CLASS_Object) {
			ClassStruct *cs = ctx->share->ClassTable[isupcid].cstruct;
			size_t i;
			for(i = 0; i < knh_Array_size(cs->methods); i++) {
				Method *imtd = (Method*)knh_Array_n(cs->methods, i);
				if(knh_Method_isPrivate(imtd)) {
					continue;
				}
				else {
					Method *mtd = knh_Class_getMethod(ctx, cid, DP(imtd)->mn);
					if(IS_NOTNULL(mtd)) {
						if(!knh_MethodField_equalsType(DP(mtd)->mf, DP(imtd)->mf)) {
							char bufcm[CLASSNAME_BUFSIZ];
							knh_format_cmethodn(ctx, bufcm, sizeof(bufcm), DP(imtd)->cid, DP(imtd)->mn);
							DBG2_P("mismatch!! %s", bufcm);
							allchecked = 0;
						}
					}
				}
			}
			isupcid = ctx->share->ClassTable[isupcid].supcid;
		}
		if(allchecked) {
			isupcid = icid;
			while(isupcid != CLASS_Object) {
				ClassStruct *cs = ctx->share->ClassTable[isupcid].cstruct;
				size_t i;
				for(i = 0; i < knh_Array_size(cs->methods); i++) {
					Method *imtd = (Method*)knh_Array_n(cs->methods, i);
					if(knh_Method_isPrivate(imtd)) {
						continue;
					}
					else {
						Method *mtd = knh_Class_getMethod(ctx, cid, DP(imtd)->mn);
						if(IS_NULL(mtd)) {
							mtd = new_Method(ctx, 0, cid, DP(imtd)->mn, NULL);
							KNH_SETv(ctx, DP(mtd)->mf, DP(imtd)->mf);
							KNH_ASSERT(IS_NOTNULL(DP(mtd)->mf));
							knh_Class_addMethod(ctx, cid, mtd);
						}
					}
				}
				isupcid = ctx->share->ClassTable[isupcid].supcid;
			}
			DBG2_P("add interface %s to %s", CLASSN(icid), CLASSN(cid));
			knh_ClassMap_add(ctx, ctx->share->ClassTable[cid].cmap, new_Mapper__interface(ctx, cid, icid));
		}
	}
}

/* ------------------------------------------------------------------------ */

static
int knh_StmtCLASS_decl(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	char bufn[CLASSNAME_BUFSIZ];
	knh_snprintf(bufn, sizeof(bufn), "%s.%s", knh_String_tochar(DP(ns)->nsname), sToken(StmtCLASS_class(stmt)));

	knh_class_t cid  = knh_NameSpace_getcid(ctx, ns, B(bufn));
	if(cid == CLASS_unknown) {
		cid = knh_ClassTable_newId(ctx);
		KNH_ASSERT(ctx->share->ClassTable[cid].class_cid == NULL);
	}
	else {
		knh_Asm_perror(ctx, abr, KERR_ERROR, _("cannot redefine %C"), cid);
		knh_Stmt_done(ctx, stmt);
		return 0;
	}

	knh_class_t supcid = CLASS_Object;
	if(SP(StmtCLASS_superclass(stmt))->tt != TT_ASIS) {
		supcid = knh_NameSpace_getcid(ctx, ns, knh_Token_tobytes(ctx, StmtCLASS_superclass(stmt)));
		if(supcid == CLASS_unknown) {
			supcid = CLASS_Object;
			knh_Asm_perror(ctx, abr, KERR_ERRATA, _("unknown class: %s ==> %C"), sToken(StmtCLASS_superclass(stmt)), supcid);
		}
		else if(knh_class_isFinal(supcid)) {
			knh_Asm_perror(ctx, abr, KERR_ERROR, _("cannot extends %C: this class is final"), supcid);
			knh_Stmt_done(ctx, stmt);
			return 0;
		}
	}

	DP(StmtCLASS_class(stmt))->cid = cid;

	knh_ClassTable_t *TC = (knh_ClassTable_t*)&(ctx->share->ClassTable[cid]);
	TC->cflag  = knh_StmtCLASS_flag(ctx, stmt);
	TC->oflag  = KNH_FLAG_CF2OF(TC->cflag);
	if(SP(StmtCLASS_instmt(stmt))->stt == STT_DONE) {
		TC->bcid   = CLASS_Any;
	}
	else {
		TC->bcid   = CLASS_Object;
	}
	TC->supcid = supcid;
	if(supcid == CLASS_Object) {
		TC->offset = 0;
	}else {
		TC->offset = ctx->share->ClassTable[supcid].bsize;
	}
	KNH_ASSERT(TC->class_cid == NULL);
	konoha_setClassName(ctx, cid, new_String(ctx, B(bufn), NULL));
	KNH_INITv(TC->cstruct, new_ClassStruct0(ctx, 0, 8));
	KNH_INITv(TC->cmap, ctx->share->ClassTable[CLASS_Any].cmap);
	konoha_setClassDefaultValue(ctx, cid, KNH_NULL, NULL);
	knh_NameSpace_setLocalName(ctx, ns, cid);

	if(SP(StmtCLASS_interface(stmt))->stt != STT_DONE) {
		Stmt *istmt = StmtCLASS_interface(stmt);
		int i, n = DP(istmt)->size;
		for(i = 0; i < n; i++) {
			Token *tk = DP(stmt)->tokens[i];
			knh_class_t icid = knh_NameSpace_getcid(ctx, ns, knh_Token_tobytes(ctx, tk));
			if(icid == CLASS_unknown) {
				knh_Token_perror(ctx, tk, KERR_EWARN, _("unknown class: %s"), sToken(tk));
				continue;
			}
			if(!knh_class_isInterface(icid)) {
				knh_Token_perror(ctx, tk, KERR_EWARN, _("cannot implements %C: this class is not @Interfac"), icid);
				continue;
			}
			knh_class_addInterface(ctx, cid, icid);
		}
	}
	if(SP(StmtCLASS_instmt(stmt))->stt == STT_DONE) {
		knh_Stmt_done(ctx, stmt);
	}
	KNH_NOTICE(ctx, "added new class: %s", CLASSN(cid));
	return 1;
}

/* ------------------------------------------------------------------------ */
/* [declc] */

static
char *knh_lookup_includeScript(Ctx *ctx, knh_bytes_t path, char *buf, size_t bufsiz)
{
	knh_index_t loc = knh_bytes_rindex(path, '/');
	if(loc == -1) loc = knh_bytes_rindex(path, '\\');
	char *filename = (char*)path.buf + loc + 1;

#ifdef KNH_PREFIX
	knh_snprintf(buf, bufsiz, "%s/lib/konoha/include/%s", KNH_PREFIX, filename);
#else
	knh_snprintf(buf, bufsiz, "%s/include/%s", knh_String_tochar(DP(ctx->sys)->homeDir), filename);
#endif
	if(knh_isfile(ctx, B(buf))) return buf;
	char *p = knh_getenv("HOME");
	if(p != NULL) {
		knh_snprintf(buf, bufsiz, "%s/.konoha/include/%s", p, filename);
		if(knh_isfile(ctx, B(buf))) return buf;
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
int knh_StmtIMPORT_decl(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	String *fname = (String*)DP(StmtIMPORT_file(stmt))->data;
	char bufp[FILENAME_BUFSIZ], buff[FILENAME_BUFSIZ];

	String *cfname = konoha_getFileName(ctx, SP(stmt)->fileid);
	KNH_ASSERT(IS_String(fname));
	if(knh_String_endsWith(cfname, STEXT(".k"))) {
		knh_format_parentpath(bufp, sizeof(bufp), knh_String_tobytes(cfname), 1);
	}
	else {
		bufp[0]=0;
	}
	knh_format_catpath(buff, sizeof(buff), B(bufp), knh_String_tobytes(fname));
	if(!knh_isfile(ctx, B(buff))) {
		knh_lookup_includeScript(ctx, knh_String_tobytes(fname), buff, sizeof(buff));
	}
	KNH_NOTICE(ctx, "including script: %s", buff);
	knh_NameSpace_loadScript(ctx, ns, B(buff), 1 /* isEval */);
	return 1;
}

/* ------------------------------------------------------------------------ */

static
int knh_StmtUIMPORT_decl(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	Token *tk = DP(stmt)->tokens[0];
	knh_bytes_t name = knh_Token_tobytes(ctx, tk);
	knh_index_t loc = knh_bytes_rindex(name, '.');
	if(loc != -1) { /* using math.Math */
		if(knh_System_loadPackage(ctx, knh_bytes_first(name, loc))) {
			knh_class_t newcid = konoha_getcid(ctx, name);
			if(newcid == CLASS_unknown) {
				knh_Token_perror(ctx, tk, KERR_ERROR, _("unknown class: %s"), sToken(tk));
				return 0;
			}
			knh_class_t oldcid = knh_NameSpace_getcid(ctx, ns, knh_bytes_last(name, loc+1));
			if(oldcid != CLASS_unknown && newcid != oldcid) {
				KNH_WARNING(ctx, _("ovrriding.. %s => %s"), CLASSN(oldcid), CLASSN(newcid));
			}
			knh_NameSpace_setLocalName(ctx, ns, newcid);
			return 1;
		}
	}else {
		if(knh_System_loadPackage(ctx, name)) {
			if(knh_Token_isTailWildCard(tk)) {
				knh_NameSpace_importClass(ctx, ns, name);
			}
			return 1;
		}
	}
	knh_Token_perror(ctx, tk, KERR_ERROR, _("package not found: %s"), sToken(tk));
	return 0;
}

/* ------------------------------------------------------------------------ */

static
int knh_StmtUALIAS_decl(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	DBG2_DUMP(ctx, stmt, KNH_NULL, "decl");
	TODO();
	return 1;
}

/* ------------------------------------------------------------------------ */

static
char *knh_format_classurn(Ctx *ctx, char *buf, size_t bufsiz, knh_class_t bcid, knh_bytes_t urn)
{
	knh_snprintf(buf, bufsiz, KNH_CLASSSPEC_FMT, CLASSN(bcid), urn.buf);
	return buf;
}

/* ------------------------------------------------------------------------ */

static
void knh_NameSpace_setTagName(Ctx *ctx, NameSpace *o, String *name, knh_class_t cid)
{
	KNH_ASSERT(IS_NameSpace(o));
	KNH_ASSERT_cid(cid);
	knh_DictSet_set(ctx, DP(o)->name2cidDictSet, name, (knh_uintptr_t)(cid+1));
//	knh_bytes_t n = knh_String_tobytes(name);
//	knh_index_t loc = knh_bytes_index(n, ':');
//	if(loc != -1) {
//		n = knh_bytes_last(n, loc+1);
//		if(isupper(n.buf[0])) {
//			knh_DictSet_set(ctx, DP(o)->name2cidDictSet, new_String(ctx, n, name), (knh_uintptr_t)(cid+1));
//		}
//	}
}

/* ------------------------------------------------------------------------ */

static
int knh_StmtXCLASS_decl(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, knh_class_t bcid)
{
	Token *tkclassn = DP(stmt)->tokens[0];
	Token *tkurn = DP(stmt)->tokens[1];

	char bufcu[CLASSNAME_BUFSIZ];
	knh_format_classurn(ctx, bufcu, sizeof(bufcu), bcid, konoha_getURNAlias(ctx, knh_Token_tobytes(ctx, tkurn)));

	knh_class_t cid = konoha_findcid(ctx, B(bufcu));
	if(cid == bcid || cid == CLASS_unknown) {
		knh_Token_perror(ctx, tkurn, KERR_EWARN, _("resource not found: %s"), sToken(tkurn));
		cid = bcid;
	}

	knh_class_t oldcid = knh_NameSpace_getcid(ctx, ns, knh_Token_tobytes(ctx, tkclassn));
	if(oldcid != CLASS_unknown && cid != oldcid) {
		KNH_WARNING(ctx, _("overriding %s"), knh_Token_tobytes(ctx, tkclassn));
	}

	KNH_ASSERT(IS_String(DP(tkclassn)->data));
	knh_NameSpace_setTagName(ctx, ns, DP(tkclassn)->text, cid);
	return 1;
}

/* ------------------------------------------------------------------------ */

static
int knh_StmtUVOCAB_decl(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	return knh_StmtXCLASS_decl(ctx, stmt, abr, ns, CLASS_String);
}

/* ------------------------------------------------------------------------ */

static
int knh_StmtUENUM_decl(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	return knh_StmtXCLASS_decl(ctx, stmt, abr, ns, CLASS_Int);
}

/* ------------------------------------------------------------------------ */

static
int knh_StmtUUNIT_decl(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	return knh_StmtXCLASS_decl(ctx, stmt, abr, ns, CLASS_Float);
}

/* ------------------------------------------------------------------------ */

static
int knh_StmtUFUNC_decl(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	Token *tk = DP(stmt)->tokens[0];
	knh_bytes_t name = knh_Token_tobytes(ctx, tk);
	if(SP(tk)->tt == TT_CMETHODN) {
		knh_index_t loc = knh_bytes_rindex(name, '.');
		knh_class_t cid = knh_NameSpace_getcid(ctx, ns, knh_bytes_first(name, loc));
		if(cid == CLASS_unknown) {
			knh_Token_perror(ctx, tk, KERR_ERROR, _("unknown class: %s"), sToken(tk));
			return 0;
		}
		knh_methodn_t mn = konoha_getMethodName(ctx, knh_bytes_last(name, loc+1), METHODN_NONAME);
		if(mn == METHODN_NONAME) {
			knh_Token_perror(ctx, tk, KERR_ERROR, _("unknown method: %C.%s"), cid, sToken(tk));
			return 0;
		}
		knh_NameSpace_setFuncClass(ctx, ns, mn, cid);
	}
	else {
		knh_class_t cid = knh_NameSpace_getcid(ctx, ns, name);
		if(cid == CLASS_unknown) {
			knh_Token_perror(ctx, tk, KERR_ERROR, _("unknown class: %s"), sToken(tk));
			return 0;
		}
		else {
			KNH_ASSERT_cid(cid);
			Array *a = (ctx->share->ClassTable[cid].cstruct)->methods;
			size_t i;
			for(i = 0; i < knh_Array_size(a); i++) {
				Method *mtd = (Method*)knh_Array_n(a, i);
				KNH_ASSERT(IS_Method(mtd));
				if(!knh_Method_isStatic(mtd)) continue;
				knh_NameSpace_setFuncClass(ctx, ns, DP(mtd)->mn, cid);
				if(knh_Context_isVerbose(ctx)) {
					KNH_NOTICE(ctx, _("using %C.%M"), cid, DP(mtd)->mn);
				}
			}
		}
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

static
int knh_StmtUMAPMAP_decl(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	DBG2_DUMP(ctx, stmt, KNH_NULL, "decl");
	TODO();
	return 1;
}

/* ------------------------------------------------------------------------ */

static
int knh_Stmt_eval(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns, int isEval)
{
	Script *scr = knh_Asm_getScript(ctx, abr);
	Method *mtd = knh_Class_getMethod(ctx, knh_Object_cid(scr), METHODN_lambda);
	knh_sfp_t *lsfp = KNH_LOCAL(ctx);

	int isExpr = knh_stmt_isExpr(SP(stmt)->stt);

	knh_methodn_t mt = METHODN__k;
	if(SP(stmt)->stt == STT_MT) {
		Token *tk0 = DP(stmt)->tokens[0];
		knh_methodn_t mn = konoha_getMethodName(ctx, knh_Token_tobytes(ctx, tk0), METHODN_NEWID);
		char *name = FIELDN(METHODN_TOFIELDN(mn));
		if(name[1] != 0) mt = METHODN__s;
	}

	if(isExpr) {
		if(SP(stmt)->stt == STT_CALL1) {
			Token *tk0 = DP(stmt)->tokens[0];
			if(SP(tk0)->tt == TT_STR) {
				if(isEval) {
					knh_write(ctx, KNH_STDOUT, knh_String_tobytes(DP(tk0)->text));
					knh_write_EOL(ctx, KNH_STDOUT);
				}
				return 1;
			}
			if(SP(tk0)->tt == TT_ESTR) {
				mt = METHODN__s;
			}
			SP(stmt)->stt = STT_RETURN;
		}
		else if(SP(stmt)->stt == STT_LET) {
			isExpr = 0;
		}
		else {
			Stmt *newstmt = new_Stmt(ctx, 0, STT_RETURN);
			knh_Stmt_add(ctx, newstmt, UP(stmt));
			stmt = newstmt;
			KNH_LPUSH(ctx, stmt);
		}
	}

	KNH_ASM_METHOD(ctx, abr, mtd, NULL, stmt, 0 /* isIteration */);
	if(knh_Method_isAbstract(mtd) || SP(stmt)->stt == STT_ERR) {
		KNH_LOCALBACK(ctx, lsfp);
		return 0;
	}

	int isVOID = knh_Stmt_isVOID(stmt);
	if(isEval) {
		ExceptionHandler *hdr = new_ExceptionHandler(ctx);
		KNH_MOV(ctx, lsfp[0].o, hdr);
		KNH_TRY(ctx, L_CATCH, lsfp, 0);
		{
			KNH_MOV(ctx, lsfp[1].o, DP(mtd)->code); // TO AVOID RCGC
			KNH_MOV(ctx, lsfp[3].o, scr);
			KNH_SCALL(ctx, lsfp, 2, mtd, 0/*args*/);
			if(isExpr && !isVOID) {
				//DBG2_P("returning %s %lld", CLASSNo(lsfp[2].o), lsfp[2].ivalue);
				((Context*)ctx)->esp = lsfp+1;
				knh_esp1_format(ctx, mt, KNH_STDOUT, KNH_NULL);
				knh_write_EOL(ctx, KNH_STDOUT);
			}
		}
		KNH_LOCALBACK(ctx, lsfp);
		return 1;

		/* catch */
		L_CATCH:;
		KNH_PRINT_STACKTRACE(ctx, lsfp, 0);
	}
	KNH_LOCALBACK(ctx, lsfp);
	return 1;
}

/* ------------------------------------------------------------------------ */

int knh_Stmt_compile(Ctx *ctx, Stmt *stmt, String *nsname, int isEval)
{
	Asm *abr = knh_Context_getAsm(ctx);
	NameSpace *ns = knh_Context_setNameSpace(ctx, nsname);
	knh_sfp_t *lsfp = KNH_LOCAL(ctx);
	KNH_LPUSH(ctx, stmt);

	Stmt *cur = stmt;
	DP(abr)->fileid = SP(stmt)->fileid;
	while(IS_Stmt(cur)) {
		knh_stmt_t stt = SP(cur)->stt;
		DP(abr)->line = SP(cur)->line;
		DP(abr)->level = 0;
		int res = 1;
		switch(stt) {
		case STT_CLASS:
			res = knh_StmtCLASS_decl(ctx, cur, abr, ns);
			break;
		case STT_IMPORT:
			res = knh_StmtIMPORT_decl(ctx, cur, abr, ns);
			knh_Stmt_done(ctx, cur);
			break;
		case STT_UIMPORT:
			res = knh_StmtUIMPORT_decl(ctx, cur, abr, ns);
			knh_Stmt_done(ctx, cur);
			break;
		case STT_UALIAS:
			res = knh_StmtUALIAS_decl(ctx, cur, abr, ns);
			knh_Stmt_done(ctx, cur);
			break;
		case STT_UVOCAB:
			res = knh_StmtUVOCAB_decl(ctx, cur, abr, ns);
			knh_Stmt_done(ctx, cur);
			break;
		case STT_UENUM:
			res = knh_StmtUENUM_decl(ctx, cur, abr, ns);
			knh_Stmt_done(ctx, cur);
			break;
		case STT_UUNIT:
			res = knh_StmtUUNIT_decl(ctx, cur, abr, ns);
			knh_Stmt_done(ctx, cur);
			break;
		case STT_UFUNC:
			res = knh_StmtUFUNC_decl(ctx, cur, abr, ns);
			knh_Stmt_done(ctx, cur);
			break;
		case STT_UMAPMAP:
			res = knh_StmtUMAPMAP_decl(ctx, cur, abr, ns);
			knh_Stmt_done(ctx, cur);
			break;
		}
		if(res == 0) {
			goto L_FAILED;
		}
		cur = DP(cur)->next;
	}

	cur = stmt;
	while(IS_Stmt(cur)) {
		knh_stmt_t stt = SP(cur)->stt;
		DP(abr)->line = SP(cur)->line;
		DP(abr)->level = 0;
		Term *tm = TM(cur);
		switch(stt) {
		case STT_CLASS:
			tm = knh_StmtCLASS_typing(ctx, cur, abr, ns);
			break;
		case STT_METHOD:
			tm = knh_StmtMETHOD_typing(ctx, cur, abr, ns);
			break;
//		case STT_FORMAT:
//			tm = knh_StmtFORMAT_typing(ctx, cur, abr, ns);
//			break;
		case STT_DECL: {
			knh_Asm_initThisScript(ctx, abr);
			tm = knh_StmtDECL_typing(ctx, cur, abr, ns);
			break;
			}
		case STT_LET: {
			knh_Asm_initThisScript(ctx, abr);
			tm = knh_StmtLET_typing(ctx, cur, abr, ns, TYPE_void);
			break;
			}
		}
		if(tm == NULL) {
			knh_Stmt_done(ctx, stmt);
			goto L_FAILED;
		}
		cur = DP(cur)->next;
	}

	if(DP(abr)->dlhdr != NULL) {
		DBG2_P("init function");
		knh_finit finit = (knh_finit)knh_dlsym(ctx, DP(abr)->dlhdr, "init");
		if(finit != NULL) {
			finit(ctx);
		}
		DP(abr)->dlhdr = NULL;
	}

	cur = stmt;
	while(IS_Stmt(cur)) {
		knh_stmt_t stt = SP(cur)->stt;
		KNH_ASM_SETLINE(ctx, abr, SP(cur)->line);
		DP(abr)->level = 0;
		switch(stt) {
		case STT_CLASS:
			knh_StmtCLASS_asm(ctx, cur, abr); break;
		case STT_METHOD:
			knh_StmtMETHOD_asm(ctx, cur, abr); break;
		case STT_FORMAT:
			knh_StmtFORMAT_asm(ctx, cur, abr); break;
		case STT_DONE:
			break;
		default:
			if(!knh_Stmt_eval(ctx, cur, abr, ns, isEval)) {
				goto L_FAILED;
			}
		}
		knh_Stmt_done(ctx, cur);
		cur = DP(cur)->next;
	}

	KNH_LOCALBACK(ctx, lsfp);
	return 1;

	L_FAILED:;
	KNH_LOCALBACK(ctx, lsfp);
	return 0;
}

/* ======================================================================== */
/* [main] */

static
Stmt *knh_InputStream_parseStmt(Ctx *ctx, InputStream *in)
{
	Token *tk = new_Token(ctx, 0, DP(in)->fileid, 0, knh_char_totoken('{'));
	KNH_LPUSH(ctx, tk);
	KNH_LPUSH(ctx, in);
	knh_Token_parse(ctx, tk, in);
	DBG2_DUMP(ctx, tk, KNH_NULL, "tokens");
	Stmt *stmt = new_StmtINSTMT(ctx, tk); // new_Stmt(ctx, 0, STT_DONE)(ctx);
	return stmt;
}

/* ------------------------------------------------------------------------ */

Stmt *knh_bytes_parseStmt(Ctx *ctx, knh_bytes_t kscript, int fileid, int line)
{
	knh_cwb_t cwb = new_cwb(ctx);
	knh_Bytes_write(ctx, cwb.ba, kscript);
	knh_Bytes_putc(ctx, cwb.ba, ';');
	InputStream *in = new_BytesInputStream(ctx, cwb.ba, cwb.pos, knh_Bytes_size(cwb.ba));
	DP(in)->fileid = (knh_fileid_t)fileid;
	DP(in)->line = line;
	Stmt *stmt = knh_InputStream_parseStmt(ctx, in);
	knh_cwb_clear(cwb);
	return stmt;
}

/* ------------------------------------------------------------------------ */

void konohac_eval(Ctx *ctx, String *nsname, InputStream *in)
{
	knh_sfp_t *lsfp = KNH_LOCAL(ctx);
	KNH_LPUSH(ctx, new_ExceptionHandler(ctx));
	KNH_TRY(ctx, L_CATCH, lsfp, 0);
	{
		Stmt *stmt = knh_InputStream_parseStmt(ctx, in);
		KNH_LPUSH(ctx, stmt);
		DBG_DUMP(ctx, stmt, KNH_NULL, "stmt");
		knh_Stmt_compile(ctx, stmt, nsname, !knh_Context_isCompiling(ctx) /* isrun 1 */);
	}
	KNH_LOCALBACK(ctx, lsfp);
	return;

	/* catch */
	L_CATCH:;
	KNH_PRINT_STACKTRACE(ctx, lsfp, 0);
	return;
}

/* ------------------------------------------------------------------------ */

void knh_Asm_openlib(Ctx *ctx, Asm *abr, knh_bytes_t fpath)
{
	knh_cwb_t cwb = new_cwb(ctx);
	knh_index_t idx = knh_bytes_rindex(fpath, '.');
	if(idx > 0) fpath = knh_bytes_first(fpath, idx);
	knh_Bytes_write(ctx, cwb.ba, fpath);
	knh_Bytes_putc(ctx, cwb.ba, '_');
	knh_Bytes_write(ctx, cwb.ba, STEXT(KONOHA_PLATFORM));
	knh_Bytes_write(ctx, cwb.ba, STEXT(KONOHA_OS_DLLEXT));
	knh_Bytes_putc(ctx, cwb.ba, 0);

	if(DP(abr)->dlhdr != NULL) {
		DP(abr)->dlhdr = NULL;
	}

	knh_bytes_t f = knh_cwb_tobytes(cwb);
	DP(abr)->dlhdr =knh_dlopen(ctx, (char*)f.buf, KNH_RTLD_LAZY);
	if(DP(abr)->dlhdr != NULL) {
		KNH_NOTICE(ctx, "opened dynamic library: %s", f.buf);
	}
	else {
		if(knh_isfile(ctx, f)) {
			KNH_WARNING(ctx, "cannot open dynamic library: %s", f.buf);
		}
	}
	knh_cwb_clear(cwb);
}

/* ======================================================================== */
/* [loaded] */

static
void knh_NameSpace_loaded(Ctx *ctx, NameSpace *o, knh_fileid_t fileid)
{
	KNH_ASSERT(IS_NameSpace(o));
	if(IS_NULL(DP(o)->lconstDictMap)) {
		KNH_SETv(ctx, DP(o)->lconstDictMap, new_DictMap0(ctx, 16));
	}
	char buf[40];
	knh_snprintf(buf, sizeof(buf), "_LOADED_%d", (int)fileid);
	knh_DictMap_set(ctx, DP(o)->lconstDictMap, new_String(ctx, B(buf), NULL), UP(konoha_getFileName(ctx, fileid)));
}

/* ------------------------------------------------------------------------ */

static
int knh_NameSpace_isLoaded(Ctx *ctx, NameSpace *o, knh_fileid_t fileid)
{
	if(IS_NOTNULL(DP(o)->lconstDictMap)) {
		char buf[40];
		knh_snprintf(buf, sizeof(buf), "_LOADED_%d", (int)fileid);
		return (knh_DictMap_index__b(DP(o)->lconstDictMap, B(buf)) != -1);
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

int knh_NameSpace_loadScript(Ctx *ctx, NameSpace *ns, knh_bytes_t fpath, int isEval)
{
	knh_fileid_t fileid = konoha_getFileId(ctx, fpath);
	if(knh_NameSpace_isLoaded(ctx, ns, fileid)) {
		DBG2_P("Already imported: %s", fpath.buf);
		return 1;
	}
	knh_NameSpace_loaded(ctx, ns, fileid);
	knh_sfp_t *lsfp = KNH_LOCAL(ctx);
	InputStream *in = new_FileInputStream(ctx, fpath);
	KNH_LPUSH(ctx, in);
	DP(in)->fileid = fileid;
	knh_InputStream_setEncoding(ctx, in, knh_systemEncoding);
	Stmt *stmt = knh_InputStream_parseStmt(ctx, in);
	KNH_LPUSH(ctx, stmt);
	if(isEval) {
		knh_Asm_openlib(ctx, knh_Context_getAsm(ctx), fpath);
	}
	knh_Stmt_compile(ctx, stmt, DP(ns)->nsname, isEval);
	KNH_LOCALBACK(ctx, lsfp);
	return 1;
}

/* ------------------------------------------------------------------------ */

void konoha_compile(Ctx *ctx, String *nsname, knh_bytes_t fpath)
{
	knh_sfp_t *lsfp = KNH_LOCAL(ctx);
	KNH_LPUSH(ctx, new_ExceptionHandler(ctx));
	KNH_TRY(ctx, L_CATCH, lsfp, 0);
	{
		NameSpace *ns = knh_Context_setNameSpace(ctx, nsname);
		knh_NameSpace_loadScript(ctx, ns, fpath, 0);
	}
	KNH_LOCALBACK(ctx, lsfp);
	return;

	/* catch */
	L_CATCH:;
	KNH_PRINT_STACKTRACE(ctx, lsfp, 0);
	return;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
