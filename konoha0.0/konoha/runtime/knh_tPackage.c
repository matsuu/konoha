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

#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [global] */

#define knh_homeDir                DP(knh_rootSystem)->homeDir
#define knh_sysnsDictMap           DP(knh_rootSystem)->sysnsDictMap
#define knh_funcDictSet            DP(knh_rootSystem)->funcDictSet
#define knh_drvapiDictSet          DP(knh_rootSystem)->drvapiDictSet
#define knh_makespecDictSet        DP(knh_rootSystem)->makespecDictSet

/* ======================================================================== */
/* [SLOCK] */

#define KNH_SLOCK(lock)
#define KNH_SUNLOCK(lock)
#define LOCK_FUNC                   1
#define LOCK_PKGMGR                 1

/* ======================================================================== */
/* [DRVAPI] */

void KNH_TDRVAPI(Ctx *ctx, char *alias, knh_drvapi_t* p)
{
	char bufn[CLASSNAME_BUFSIZ];
	KNH_ASSERT(IS_DRVAPI(p->type));
	if(alias == NULL) {
		knh_snprintf(bufn, sizeof(bufn), "%s:%02d", p->name, p->type);
	}
	else {
		knh_snprintf(bufn, sizeof(bufn), "%s:%02d", alias, p->type);
	}
	KNH_SLOCK(LOCK_FUNC);
	knh_DictSet_set(ctx, DP(knh_rootSystem)->drvapiDictSet, new_String0(ctx, B(bufn), NULL), (knh_uint_t)p);
	KNH_SUNLOCK(LOCK_FUNC);
}

/* ------------------------------------------------------------------------ */

knh_drvapi_t *knh_System_getDRVAPI(Ctx *ctx, int type, knh_bytes_t name)
{
	char bufn[CLASSNAME_BUFSIZ], bufn2[CLASSNAME_BUFSIZ];
	knh_format_bytes(bufn2, sizeof(bufn2), name);
	knh_snprintf(bufn, sizeof(bufn), "%s:%02d", bufn2, type);
	KNH_SLOCK(LOCK_FUNC);
	knh_drvapi_t *p = (knh_drvapi_t*)knh_DictSet_get__b(DP(knh_rootSystem)->drvapiDictSet, B(bufn));
	KNH_SUNLOCK(LOCK_FUNC);
	return p;
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_addParserDriver(Ctx *ctx, char *alias, knh_parser_drvapi_t *d)
{
	if(alias != NULL) {
		KNH_TDRVAPI(ctx, alias, (knh_drvapi_t*)d);
	}
	else {
		KNH_TDRVAPI(ctx, d->name, (knh_drvapi_t*)d);
	}
}

/* ======================================================================== */
/* [func] */

void KNH_TSTATICLIB__T(Ctx *ctx, char *text, void *func)
{
	if(func != NULL) {
		KNH_SLOCK(LOCK_FUNC);
		knh_DictSet_set(ctx, knh_funcDictSet, new_String__T(ctx, text), (knh_uint_t)func);
		KNH_SUNLOCK(LOCK_FUNC);
	}
}

/* ======================================================================== */
/* [namespace] */

static
NameSpace *knh_System_getNameSpace(Ctx *ctx, knh_bytes_t pkgname, int isnew)
{
	NameSpace *ns = (NameSpace*)knh_DictMap_get__b(ctx, knh_sysnsDictMap, pkgname);
	if(IS_NULL(ns) && isnew) {
		KNH_SLOCK(LOCK_PKGMGR);
		String *nsname = new_String(ctx, pkgname, NULL);
		ns = new_NameSpace(ctx, knh_rootNameSpace, nsname);
		knh_DictMap_set(ctx, knh_sysnsDictMap, nsname, UP(ns));
		KNH_SLOCK(LOCK_PKGMGR);
	}
	return ns;
}

/* ======================================================================== */
/* [package] */

char *knh_format_packagedir(char *buf, size_t bufsiz, char *homedir)
{
	char *p = knh_getenv("KONOHA_PACKAGE");
	if(p != NULL) {
		knh_snprintf(buf, bufsiz, "%s", p);
		return buf;
	}
#ifdef KNH_PREFIX
	knh_snprintf(buf, bufsiz, "%s/lib/konoha", KNH_PREFIX);
	return buf;
#else
	knh_snprintf(buf, bufsiz, "%s/package", homedir);
	return buf;
#endif
}

/* ------------------------------------------------------------------------ */

static
char *knh_format_packagepath(char *buf, size_t bufsiz, char *pre, char *name, char *ext)
{
	char *p = knh_getenv("KONOHA_PACKAGE");
	if(p != NULL) {
		knh_snprintf(buf, bufsiz, "%s/%s/%sknh%s%s", p, name, pre, name, ext);
		return buf;
	}
#ifdef KNH_PREFIX
	knh_snprintf(buf, bufsiz, "%s/lib/konoha/%s/%sknh%s%s", KNH_PREFIX, name, pre, name, ext);
	return buf;
#else
	knh_snprintf(buf, bufsiz, "%s/package/%s/%sknh%s%s", knh_String_tochar(knh_homeDir), name, pre, name, ext);
	return buf;
#endif
}

/* ------------------------------------------------------------------------ */

static
int knh_System_loadPackage(Ctx *ctx, knh_bytes_t pkgname)
{
	int res = 0;
	char bufp[CLASSNAME_BUFSIZ], buff[FILENAME_BUFSIZ];
	knh_format_bytes(bufp, sizeof(bufp), pkgname);
#ifdef KONOHA_MONOLITHIC
	knh_snprintf(buff, sizeof(buff), "knh%s_init", bufp);
	f_libknh_init finit = (f_libknh_init)knh_DictSet_get__b(knh_funcDictSet, B(buff));
	if(finit != NULL) {
		NameSpace *pkgns = knh_System_getNameSpace(ctx, pkgname, 1);
		DP(pkgns)->dlhdr = NULL;
		NameSpace *curns = knh_Context_switchNameSpace(ctx, pkgns);
		finit(ctx);
		knh_Context_switchNameSpace(ctx, curns);
		knh_snprintf(buff, sizeof(buff), "knh%s_traverse", bufp);
		DP(pkgns)->ftraverse = (f_libknh_traverse)knh_DictSet_get__b(knh_funcDictSet, B(buff));
		res = 1;
	}
	else {
		DBG_P("function not found '%s'", buff);
	}
#else/*KONOHA_MONOLITHIC*/
	void *dlhdr = NULL;
	knh_format_packagepath(buff, sizeof(buff), "lib", bufp, KONOHA_OS_DLLEXT);
	DBG2_P("loading package .. '%s'", buff);
	dlhdr =knh_dlopen(buff, KNH_RTLD_LAZY);
	if (dlhdr != NULL) {
		NameSpace *pkgns = knh_System_getNameSpace(ctx, pkgname, 1);
		DP(pkgns)->dlhdr = dlhdr;
		knh_snprintf(buff, sizeof(buff), "knh%s_init", bufp);
		f_libknh_init finit = (f_libknh_init)knh_dlsym(dlhdr, buff);
		if(finit != NULL) {
			NameSpace *curns = knh_Context_switchNameSpace(ctx, pkgns);
			finit(ctx);
			knh_Context_switchNameSpace(ctx, curns);
			knh_snprintf(buff, sizeof(buff), "knh%s_traverse", bufp);
			DP(pkgns)->ftraverse = (f_libknh_traverse)knh_dlsym(dlhdr, buff);
			res = 1;
		}
		else {
			DBG_P("function not found '%s'", buff);
		}
	}
	else {
		DBG_P("cannot open '%s'", buff);
	}
#endif/*KONOHA_MONOLITHIC*/
	knh_format_packagepath(buff, sizeof(buff), "", bufp, ".k");
	DBG2_P("opening.. '%s'", buff);
	FILE *fp = knh_fopen(buff, "r");
	if(fp != NULL) {
		InputStream *in = new_InputStream__FILE(ctx, fp);
		DP(in)->fileid = knh_tName_getFileId(ctx, B(buff));
		knh_InputStream_setEncoding(ctx, in, knh_systemEncoding);
		NameSpace *pkgns = knh_System_getNameSpace(ctx, pkgname, 1);
		NameSpace *curns = knh_Context_switchNameSpace(ctx, pkgns);
		knh_konohac_eval(ctx, (String*)KNH_NULL, in);
		knh_Context_switchNameSpace(ctx, curns);
		res = 1;
		knh_fclose(fp);
	}
	else {

	}
	return res;
}

/* ------------------------------------------------------------------------ */
/* [NameSpace] */

int knh_System_using(Ctx *ctx, knh_bytes_t name)
{
	NameSpace *ns = (NameSpace*)knh_DictMap_get__b(ctx, knh_sysnsDictMap, name);
	if(IS_NULL(ns)) {
		return knh_System_loadPackage(ctx, name);
	}
	return 1;
}

/* ------------------------------------------------------------------------ */
/* [NameSpace] */

NameSpace *knh_Runtime_getNameSpace(Ctx *ctx, knh_bytes_t name)
{
	if(knh_bytes_equals(name, STEXT("main"))) {
		if(IS_NULL(ctx->ns)) {
			KNH_SETv(ctx, ((Context*)ctx)->ns, new_NameSpace(ctx, knh_rootNameSpace, TS_main));
		}
		return ctx->ns;
	}
	else {
		NameSpace *ns = (NameSpace*)knh_DictMap_get__b(ctx, DP(ctx->runtime)->tnameSpaceDictMap, name);
		if(IS_NULL(ns)) {
			String *nsname = NULL;
			if(knh_System_loadPackage(ctx, name)) {
				ns = knh_System_getNameSpace(ctx, name, 0);
				KNH_ASSERT(IS_NameSpace(ns));
				nsname = DP(ns)->nsname;
			}
			else {
				nsname = new_String(ctx, name, NULL);
				ns = new_NameSpace(ctx, knh_rootNameSpace, nsname);
			}
			knh_DictMap_set(ctx, DP(ctx->runtime)->tnameSpaceDictMap, nsname, UP(ns));
		}
		return ns;
	}
}

///* ------------------------------------------------------------------------ */
//
//void *knh_System_getFunc(Ctx *ctx, knh_bytes_t funcname, void *deffunc)
//{
//	void *func;
//	KNH_SLOCK(LOCK_FUNC);
//	func = (void*)knh_DictSet_get__b(knh_funcDictSet, funcname);
//	KNH_SUNLOCK(LOCK_FUNC);
//	if(func == NULL) {
//		return deffunc;
//	}
//	DBG2_P("using built-in function: %s", funcname.buf);
//	return func;
//}

/* ======================================================================== */
/* [makesepc] */

KNHAPI(void) konoha_addClassSpecFunc(Ctx *ctx, char *urn, f_makespec func)
{
	if(func != (f_makespec)NULL) {
		KNH_SLOCK(LOCK_FUNC);
		DBG2_P("adding.. '%s'", urn);
		knh_DictSet_set(ctx, knh_makespecDictSet, new_String__T(ctx, urn), (knh_uint_t)func);
		KNH_SUNLOCK(LOCK_FUNC);
	}
}
/* ------------------------------------------------------------------------ */

ClassSpec *knh_System_loadClassSpec(Ctx *ctx, knh_class_t bcid, knh_bytes_t urn)
{
	DBG2_P("S urn='%s'", urn.buf);
	urn = knh_Runtime_aliasURN(ctx, urn);
	DBG2_P("E urn='%s'", urn.buf);
	KNH_SLOCK(LOCK_FUNC);
	DBG2_P("finding.. '%s'", urn.buf);
	f_makespec func = (void*)knh_DictSet_get__b(knh_makespecDictSet, urn);
	KNH_SUNLOCK(LOCK_FUNC);
	if(func != NULL) {
		return func(ctx, bcid, NULL);
	}
	return (ClassSpec*)(KNH_NULL);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
