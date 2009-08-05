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
/* [main] */

static
int knh_NameSpace_compile(Ctx *ctx, NameSpace *ns, Stmt *stmt, int isEval);

/* ------------------------------------------------------------------------ */
/* [import script] */

static
knh_bool_t knh_bytes_isSystemScript(knh_bytes_t path)
{
	size_t i;
	for(i = 0; i < path.len; i++) {
		int ch = path.buf[i];
		if(ch == '/' || ch == '\\' || ch == '.') return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

static
void knh_NameSpace_loaded(Ctx *ctx, NameSpace *ns, knh_uri_t uri)
{
	KNH_ASSERT(IS_NameSpace(ns));
	String *s = knh_getResourceName(ctx, uri);
	knh_uintptr_t trust = KNH_PATH_UNTRUSTED;
	if(URI_ISTRUSTED(uri)) {
		trust = KNH_PATH_TRUSTED;
	}
	if(IS_NULL(DP(ns)->pathTrustDictSet)) {
		KNH_SETv(ctx, DP(ns)->pathTrustDictSet, new_DictSet0(ctx, 4));
	}
	knh_DictSet_set(ctx, DP(ns)->pathTrustDictSet, s, trust);
}

/* ------------------------------------------------------------------------ */

static
int knh_NameSpace_isLoaded(Ctx *ctx, NameSpace *ns, knh_uri_t uri)
{
	if(IS_NOTNULL(DP(ns)->pathTrustDictSet)) {
		String *s = knh_getResourceName(ctx, uri);
		knh_uintptr_t n = knh_DictSet_get__b(DP(ns)->pathTrustDictSet, knh_String_tobytes(s));
		return (n != 0);
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

InputStream* new_ScriptInputStream(Ctx *ctx, knh_bytes_t path, knh_cwb_t *cwb, NameSpace *ns, int isThrowable)
{
	knh_uri_t uri = 0;
	knh_iodrv_t *drv = NULL;
	knh_cwb_t cwbbuf;
	if(cwb == NULL) {
		cwb = knh_cwb_openinit(ctx, &cwbbuf, path);
	}
	if(knh_bytes_startsWith(path, STEXT("http://"))) {
		drv = knh_getIODriver(ctx, STEXT("http"));
	}
	else {
		drv = knh_getIODriver(ctx, STEXT("file"));
		knh_cwb_ospath(ctx, cwb);
		if(!knh_cwb_isfile(ctx, cwb) && knh_bytes_isSystemScript(path)) {
			String *spath = (String*)knh_Context_getProperty(ctx, (Context*)ctx, STEXT("konoha.script.path"));
			if(IS_bString(spath)) {
				knh_cwb_subclear(cwb, 0);
				knh_cwb_write(ctx, cwb, knh_String_tobytes(spath));
				knh_cwb_putc(ctx, cwb, '/');
				knh_cwb_write(ctx, cwb, path);
				knh_cwb_ospath(ctx, cwb);
				if(knh_cwb_isfile(ctx, cwb)) {
					uri = knh_cwb_getResourceId(ctx, cwb);
					DBG2_ASSERT(uri != 0);
					uri = URI_TRUSTED(uri);
				}
			}
			spath = (String*)knh_Context_getProperty(ctx, (Context*)ctx, STEXT("user.script.path"));
			if(IS_bString(spath) && uri == 0) {
				knh_cwb_subclear(cwb, 0);
				knh_cwb_write(ctx, cwb, knh_String_tobytes(spath));
				knh_cwb_putc(ctx, cwb, '/');
				knh_cwb_write(ctx, cwb, path);
				knh_cwb_ospath(ctx, cwb);
				if(knh_cwb_isfile(ctx, cwb)) {
					uri = knh_cwb_getResourceId(ctx, cwb);
					DBG2_ASSERT(uri != 0);
					uri = URI_TRUSTED(uri);
				}
			}
			if(uri == 0) {
				knh_cwb_subclear(cwb, 0);
				knh_cwb_write(ctx, cwb, path);
			}
		}
	}
	if(uri == 0) {
		uri = knh_cwb_getResourceId(ctx, cwb);
	}
	if(knh_NameSpace_isLoaded(ctx, ns, uri)) {
		KNH_WARNING(ctx, "Already imported: %s", (char*)path.buf);
		if(!knh_ask(ctx, "Do you want to reload it [y/N] ?", 0)) {
			return (InputStream*)KNH_DEF(ctx, CLASS_InputStream);
		}
	}
	{
		String *spath = knh_getResourceName(ctx, uri);
		path = knh_String_tobytes(spath);
		KNH_NOTICE(ctx, "importing script: %s", path.buf);
		knh_io_t fd = drv->fopen(ctx, path, "r", isThrowable);
		InputStream *in = new_InputStream__io(ctx, spath, fd, drv);
		if(!knh_InputStream_isClosed(ctx, in)) {
			DP(in)->uri = uri;
			if(!knh_bytes_startsWith(path, STEXT("http://"))) {
				knh_InputStream_setEncoding(ctx, in, KNH_ENC);
			}
		}
		return in;
	}
}

/* ------------------------------------------------------------------------ */

Stmt *knh_InputStream_parseStmt(Ctx *ctx, InputStream *in, int isData)
{
	Token *tk = new_Token(ctx, 0, DP(in)->uri, 0, knh_char_totoken('{'));
	KNH_LPUSH(ctx, tk);
	KNH_LPUSH(ctx, in);
	knh_Token_parse(ctx, tk, in);
	//DBG2_DUMP(ctx, tk, KNH_NULL, "tokens");
	return new_StmtINSTMT(ctx, tk, isData);
}

/* ------------------------------------------------------------------------ */

static
void knh_Asm_openDynamicLinkLibrary(Ctx *ctx, Asm *abr, knh_uri_t uri)
{
	knh_bytes_t path = knh_String_tobytes(knh_getResourceName(ctx, uri));
	if(path.buf[0] != '(' && !knh_bytes_startsWith(path, STEXT("http://"))) {  // check "(eval)", "(shell)", or o
		knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
		knh_index_t idx = knh_bytes_rindex(path, '.');
		if(idx > 0) path = knh_bytes_first(path, idx);
		knh_cwb_write(ctx, cwb, path);
		knh_cwb_putc(ctx, cwb, '_');
		knh_cwb_write(ctx, cwb, STEXT(KONOHA_PLATFORM));
		knh_cwb_ospath(ctx, cwb);
		DP(abr)->dlhdr =knh_cwb_dlopen(ctx, cwb);
		if(DP(abr)->dlhdr != NULL) {
			KNH_NOTICE(ctx, "opened dynamic library: %s", knh_cwb_tochar(ctx, cwb));
		}
		else {
			if(knh_cwb_isfile(ctx, cwb)) {
				KNH_WARNING(ctx, "cannot open dynamic library: %s", knh_cwb_tochar(ctx, cwb));
			}
		}
		knh_cwb_close(cwb);
	}
	else {
		DP(abr)->dlhdr = NULL;
	}
}

/* ------------------------------------------------------------------------ */

int knh_NameSpace_load(Ctx *ctx, NameSpace *ns, InputStream *in, int isEval, int isThrowable)
{
	int res = 0;
	knh_sfp_t *lsfp = KNH_LOCAL(ctx);
	knh_uri_t uri = DP(in)->uri;
	KNH_LPUSH(ctx, in);
	KNH_ASSERT(!knh_InputStream_isClosed(ctx, in));
	KNH_LPUSH(ctx, new_ExceptionHandler(ctx));
	KNH_TRY(ctx, L_CATCH, lsfp, 1);
	knh_Context_initAsm(ctx);   // initialization
	{
		Stmt *stmt = knh_InputStream_parseStmt(ctx, in, 0/*isData*/);
		KNH_LPUSH(ctx, stmt);
		if(URI_UNMASK(uri) != 0) {
			DBG_DUMP(ctx, stmt, KNH_NULL, "stmt");
		}
		if(isEval) {
			knh_Asm_openDynamicLinkLibrary(ctx, ctx->abr, uri);
		}
		res = knh_NameSpace_compile(ctx, ns, stmt, isEval);
		if(URI_UNMASK(uri) != 0) {
			knh_NameSpace_loaded(ctx, ns, uri);
		}
	}
	KNH_LOCALBACK(ctx, lsfp);
	return res;

	/* catch */
	L_CATCH:;
	if(isThrowable) {
		KNH_THROW_AGAIN(ctx, lsfp, 1);
	}
	else {
		KNH_PRINT_STACKTRACE(ctx, lsfp, 1);
	}
	return 0;
}

/* ======================================================================== */
/* [namespace/package] */

static
char *knh_cwb_packageScript(Ctx *ctx, knh_cwb_t *cwb, knh_bytes_t rootdir, knh_bytes_t package)
{
	knh_cwb_subclear(cwb, 0);
	knh_cwb_write(ctx, cwb, rootdir);
	knh_cwb_putc(ctx, cwb, '/');
	knh_cwb_write(ctx, cwb, package);
	knh_cwb_putc(ctx, cwb, '/');
	knh_index_t loc = knh_bytes_index(package, '.');
	if(loc != -1) {
		package = knh_bytes_first(package, loc);
	}
	knh_cwb_write(ctx, cwb, package);
	knh_cwb_write(ctx, cwb, STEXT(".k"));
	knh_cwb_ospath(ctx, cwb);
	if(knh_cwb_isfile(ctx, cwb)) {
		return knh_cwb_tochar(ctx, cwb);
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
char *knh_lookupPackageScript(Ctx *ctx, knh_cwb_t *cwb, knh_bytes_t pkgname)
{
	String *spath;
	char *path = knh_getenv("KONOHA_PACKAGE");
	if(path != NULL) {
		path = knh_cwb_packageScript(ctx, cwb, B(path), pkgname);
		if(path != NULL) return path;
	}
	spath = (String*)knh_Context_getProperty(ctx, (Context*)ctx, STEXT("konoha.package.path"));
	if(IS_bString(spath)) {
		path = knh_cwb_packageScript(ctx, cwb, knh_String_tobytes(spath), pkgname);
		if(path != NULL) return path;
	}
	spath = (String*)knh_Context_getProperty(ctx, (Context*)ctx, STEXT("user.package.path"));
	if(IS_bString(spath)){
		path = knh_cwb_packageScript(ctx, cwb, knh_String_tobytes(spath), pkgname);
		if(path != NULL) return path;
	}
	if(knh_hasScriptFunc(ctx, "getKonohaPackage")) {
		TODO();
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
NameSpace *knh_NameSpace_newPackageNULL(Ctx *ctx, knh_bytes_t pkgname)
{
	knh_uri_t uri = knh_getResourceId(ctx, pkgname);
	String *nsname = knh_getResourceName(ctx, uri);
	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
	char *fpath = knh_lookupPackageScript(ctx, cwb, knh_String_tobytes(nsname));
	NameSpace *ns = NULL;
	if(fpath != NULL) {
		pkgname = knh_String_tobytes(nsname);
		KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
		ns = (NameSpace*)knh_DictMap_get__b(ctx,  DP(ctx->sys)->NameSpaceTableDictMap, pkgname);
		if(IS_NULL(ns)) {
			ns = new_NameSpace(ctx, nsname);
			knh_DictMap_set(ctx, DP(ctx->sys)->NameSpaceTableDictMap, nsname, UP(ns));
			KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
			knh_sfp_t *lsfp = KNH_LOCAL(ctx);
			NameSpace *curns = knh_switchCurrentNameSpace(ctx, ns);
			InputStream *in = new_ScriptInputStream(ctx, knh_cwb_tobytes(cwb), cwb, ctx->share->mainns, 0);
			KNH_LPUSH(ctx, in);
			if(!knh_InputStream_isClosed(ctx, in)) {
				knh_NameSpace_load(ctx, ns, in, 1/*isEval*/,0/*isThrowable*/);
			}
			else {
				KNH_WARNING(ctx, "package script does not exist");
				ns = NULL;
			}
			knh_switchCurrentNameSpace(ctx, curns);
			KNH_LOCALBACK(ctx, lsfp);
		}
		else {
			KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
		}
	}
	knh_cwb_close(cwb);
	return ns;
}

///* ------------------------------------------------------------------------ */
//
//Object *konohac_data(Ctx *ctx, InputStream *in, knh_class_t reqc)
//{
//	knh_sfp_t *lsfp = KNH_LOCAL(ctx);
//	KNH_LPUSH(ctx, in);
//	KNH_LPUSH(ctx, new_ExceptionHandler(ctx));
//	KNH_TRY(ctx, L_CATCH, lsfp, 1);
//	{
//		Stmt *stmt = knh_InputStream_parseStmt(ctx, in, 1/*isData*/);
//		KNH_LPUSH(ctx, stmt);
//		return knh_Stmt_toData(ctx, stmt, reqc);
//	}
//	/* catch */
//	L_CATCH:;
//	KNH_LOCALBACK(ctx, lsfp);
//	//KNH_PRINT_STACKTRACE(ctx, lsfp, 1);
//	return KNH_NULL;
//}

/* ======================================================================== */
/* [CLASS] */

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
			knh_ClassMap_add(ctx, ClassTable(cid).cmap, new_Mapper__interface(ctx, cid, icid));
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
		KNH_ASSERT(ClassTable(cid).class_cid == NULL);
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

	knh_ClassTable_t *TC = (knh_ClassTable_t*)&(ClassTable(cid));
	TC->cflag  = knh_StmtCLASS_flag(ctx, stmt);
	TC->oflag  = KNH_FLAG_CF2OF(TC->cflag);
	if(SP(StmtCLASS_instmt(stmt))->stt == STT_DONE) {
		TC->bcid   = CLASS_Any;    /* Glue */
	}
	else {
		TC->bcid   = CLASS_Object;
	}
	TC->supcid = supcid;
	TC->offset = 0; /* will be extended in CLASS_typing */
	KNH_ASSERT(TC->class_cid == NULL);
	knh_setClassName(ctx, cid, new_String(ctx, B(bufn), NULL));
	KNH_INITv(TC->cstruct, new_ClassStruct0(ctx, 0, 8));
	KNH_INITv(TC->cmap, ctx->share->ClassTable[CLASS_Any].cmap);
	knh_setClassDefaultValue(ctx, cid, KNH_NULL, NULL);
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
				knh_Token_perror(ctx, tk, KERR_EWARN, _("cannot implements %C: this class is not @Interface"), icid);
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

static
int knh_StmtIMPORT_decl(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	int res = 1;
	knh_bytes_t path = knh_String_tobytes(DP(StmtIMPORT_file(stmt))->text);
	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
	if(path.buf[0] != '/' && path.buf[0] != '\\' && !knh_bytes_startsWith(path, STEXT("http://"))) {
		knh_cwb_write(ctx, cwb, knh_String_tobytes(knh_getResourceName(ctx, SP(stmt)->uri)));
		knh_cwb_parentpath(ctx, cwb, NULL);
		knh_cwb_putc(ctx, cwb, '/');
	}
	knh_cwb_write(ctx, cwb, path);
	{
		knh_sfp_t *lsfp = KNH_LOCAL(ctx);
		InputStream *in = new_ScriptInputStream(ctx, path, cwb, ctx->share->mainns, 0);
		KNH_LPUSH(ctx, in);
		if(!knh_InputStream_isClosed(ctx, in)) {
			res = knh_NameSpace_load(ctx, ctx->share->mainns, in, 1/*isEval*/,0/*isThrowable*/);
		}
		else {
			res = 0;
		}
		KNH_LOCALBACK(ctx, lsfp);
	}
	knh_cwb_close(cwb);
	return res;
}

/* ------------------------------------------------------------------------ */

static
int knh_StmtUIMPORT_decl(Ctx *ctx, Stmt *stmt, Asm *abr, NameSpace *ns)
{
	Token *tk = DP(stmt)->tokens[0];
	knh_bytes_t name = knh_Token_tobytes(ctx, tk);
	knh_index_t loc = knh_bytes_rindex(name, '.');
	if(loc != -1 && isupper(name.buf[loc+1])) { /* using math.Math */
		if(knh_NameSpace_newPackageNULL(ctx, knh_bytes_first(name, loc))) {
			knh_class_t newcid = knh_getcid(ctx, name);
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
		if(knh_NameSpace_newPackageNULL(ctx, name)) {
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
	knh_format_classurn(ctx, bufcu, sizeof(bufcu), bcid, knh_getURNAlias(ctx, knh_Token_tobytes(ctx, tkurn)));

	knh_class_t cid = knh_findcid(ctx, B(bufcu));
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
		knh_methodn_t mn = knh_getmn(ctx, knh_bytes_last(name, loc+1), METHODN_NONAME);
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
			Array *a = (ClassTable(cid).cstruct)->methods;
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
	Script *scr = knh_getCurrentScript(ctx);
	Method *mtd = knh_Class_getMethod(ctx, knh_Object_cid(scr), METHODN_lambda);
	knh_sfp_t *lsfp = KNH_LOCAL(ctx);

	int isExpr = knh_stmt_isExpr(SP(stmt)->stt);

	knh_methodn_t mt = METHODN__k;
	if(SP(stmt)->stt == STT_MT) {
		Token *tk0 = DP(stmt)->tokens[0];
		knh_methodn_t mn = knh_getmn(ctx, knh_Token_tobytes(ctx, tk0), METHODN_NEWID);
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

static
int knh_NameSpace_compile(Ctx *ctx, NameSpace *ns, Stmt *stmt, int isEval)
{
	Asm *abr = knh_Context_getAsm(ctx);
	knh_sfp_t *lsfp = KNH_LOCAL(ctx);
	KNH_LPUSH(ctx, stmt);

	Stmt *cur = stmt;
	DP(abr)->uri = SP(stmt)->uri;
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

/* ------------------------------------------------------------------------ */

Object *knh_Stmt_toData(Ctx *ctx, Stmt *stmt, knh_class_t reqc)
{
//	Asm *abr = knh_Context_getAsm(ctx);
//	DP(abr)->level = 0;
//	NameSpace *ns = ctx->ns;
//	if(IS_Stmt(stmt)) {
//		KNH_ASM_SETLINE(ctx, abr, SP(stmt)->line);
//		if(knh_stmt_isExpr(SP(stmt)->stt)) {
//			Token *tk = knh_StmtEXPR_typing(ctx, stmt, abr, ns, reqc);
//			if(tk == NULL || IS_Stmt(tk)) return KNH_NULL;
//		}
//		else {
//			knh_Stmt_done(ctx, stmt);
//		}
//	}
	TODO();
	return KNH_NULL;
}



/* ------------------------------------------------------------------------ */
/* [Extension] */

static
Array* knh_DictMap_makeArray(Ctx *ctx, DictMap *o, knh_bytes_t key)
{

	knh_index_t idx = knh_DictMap_firstIndex(o, key);
	if(idx != -1) {
		Array *a = new_Array0(ctx, 0);
		int i;
		for(i = idx; i < knh_DictMap_size(o); i++) {
			String *k = knh_DictMap_keyAt(o, i);
			Object *v = knh_DictMap_valueAt(o, i);
			if(knh_String_startsWith(k, key) && IS_NOTNULL(v)) {
				knh_Array_add(ctx, a, UP(k));
				knh_Array_add(ctx, a, v);
			}
		}
		return a;
	}
	return (Array*)KNH_NULL;
}

/* ------------------------------------------------------------------------ */

static
void knh_invokeMethodListener(Ctx *ctx, DictMap *meta, Method *mtd, knh_bytes_t key1, knh_bytes_t key2)
{
	Closure *cc;
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	{
		DictMap *dm = DP(ctx->sys)->listenerDictMap;
		cc = (Closure*)knh_DictMap_get__b(ctx, dm, key1);
	}
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	if(IS_NOTNULL(cc)) {
		knh_sfp_t *lsfp = KNH_LOCAL(ctx);
		if(IS_NOTNULL(meta)) {
			KNH_SETv(ctx, lsfp[2].o, meta);   /* cc(DictMap, Method) */
			KNH_SETv(ctx, lsfp[3].o, mtd);
			knh_Closure_invokesfp(ctx, cc, lsfp, /*argc*/2);
		}
		else {
			DictMap *dmeta = (DictMap*)KNH_DEF(ctx, CLASS_DictMap);
			KNH_SETv(ctx, lsfp[2].o, dmeta);
			KNH_SETv(ctx, lsfp[3].o, mtd);
			knh_Closure_invokesfp(ctx, cc, lsfp, /*argc*/2);
			knh_DictMap_clear(ctx, dmeta);
		}
	}
	if(IS_NOTNULL(meta)) {
		int i;
		Array *a;
		knh_sfp_t *lsfp = KNH_LOCAL(ctx);
		KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
		{
			DictMap *dm = DP(ctx->sys)->listenerDictMap;
			a = knh_DictMap_makeArray(ctx, dm, key2);
		}
		KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
		if(IS_NULL(a)) return;

		KNH_LPUSH(ctx, a); // TO AVOID GC;
		for(i = 0; i < knh_Array_size(a); i+=2) {
			String *key = (String*)knh_Array_n(a, i);
			knh_bytes_t anno = knh_bytes_rmod(knh_String_tobytes(key), '@');
			if(IS_NOTNULL(knh_DictMap_get__b(ctx, meta, anno))) {
				cc = (Closure*)knh_Array_n(a, i+1);
				KNH_SETv(ctx, lsfp[3].o, meta);   /* cc(DictMap, Method) */
				KNH_SETv(ctx, lsfp[4].o, mtd);
				knh_Closure_invokesfp(ctx, cc, lsfp+1, /*argc*/2);
			}
		}
		KNH_LOCALBACK(ctx, lsfp);
	}
}

/* ------------------------------------------------------------------------ */

void knh_invokeMethodTypingListener(Ctx *ctx, DictMap *meta, Method *mtd)
{
	knh_invokeMethodListener(ctx, meta, mtd, STEXT("MethodT"), STEXT("MethodT@"));
}

/* ------------------------------------------------------------------------ */

void knh_invokeMethodCompilationListener(Ctx *ctx, DictMap *meta, Method *mtd)
{
	knh_invokeMethodListener(ctx, meta, mtd, STEXT("MethodC"), STEXT("MethodC@"));
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
