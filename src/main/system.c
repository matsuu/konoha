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
/* [Constant Value] */

int knh_addClassConst(Ctx *ctx, knh_class_t cid, String* name, Object *value)
{
	KNH_ASSERT_cid(cid);
	if(ClassTable(cid).constPool == NULL) {
		knh_ClassTable_t *t = pClassTable(cid);
		KNH_INITv(t->constPool, new_DictMap0(ctx, 0));
	}
	DictMap *cmap = ClassTable(cid).constPool;
	KNH_ASSERT(IS_DictMap(cmap));
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	int res = knh_DictMap_index(cmap, knh_String_tobytes(name));
	if(res != -1) return 0;
	knh_DictMap_append(ctx, cmap, name, value);
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	return 1;
}

/* ------------------------------------------------------------------------ */

Object *knh_getClassConstNULL(Ctx *ctx, knh_class_t cid, knh_bytes_t name)
{
	KNH_ASSERT_cid(cid);
	if(ClassTable(cid).constPool == NULL) return NULL;
	DictMap *cmap = ClassTable(cid).constPool;
	Object *value = NULL;
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	int res = knh_DictMap_index(cmap, name);
	if(res != -1) {
		value = knh_DictMap_valueAt(cmap, res);
	}
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	return value;
}

/* ------------------------------------------------------------------------ */

static
void knh_addConstData(Ctx *ctx, char *dname, Object *value)
{
	knh_bytes_t n = B(dname);
	knh_index_t loc = knh_bytes_rindex(n, '.');
	String *name = T__(dname + (loc+1));
	knh_class_t cid = CLASS_Any;
	if(loc != -1) {
		if(ctx->abr != NULL && IS_Asm(ctx->abr)) {
			DBG2_P("nsname=%s", knh_String_tochar(DP(DP(ctx->abr)->ns)->nsname));
			cid = knh_NameSpace_getcid(ctx, DP(ctx->abr)->ns, knh_bytes_first(n, loc));
		}
		else {
			cid = knh_getcid(ctx, knh_bytes_first(n, loc));
		}
		if(cid == CLASS_unknown) {
			DBG2_P("unknown class const: %s", dname);
			cid = CLASS_Any;
		}
	}
	knh_addClassConst(ctx, cid, name, value);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_loadIntConstData(Ctx *ctx, knh_IntConstData_t *data)
{
	while(data->name != NULL) {
		Object *value = UP(new_Int(ctx, data->ivalue));
		knh_addConstData(ctx, data->name, value);
		data++;
	}
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_loadFloatConstData(Ctx *ctx, knh_FloatConstData_t *data)
{
	while(data->name != NULL) {
		Object *value = UP(new_Float(ctx, data->fvalue));
		knh_addConstData(ctx, data->name, value);
		data++;
	}
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_loadStringConstData(Ctx *ctx, knh_StringConstData_t *data)
{
	while(data->name != NULL) {
		Object *value = UP(T__(data->value));
		knh_addConstData(ctx, data->name, value);
		data++;
	}
}

/* ------------------------------------------------------------------------ */

void knh_Const__man(Ctx *ctx, knh_class_t cid, OutputStream *w)
{
	KNH_ASSERT_cid(cid);
	if(ClassTable(cid).constPool == NULL) return ;
	DictMap *tcmap = ClassTable(cid).constPool;
	size_t i, size = knh_DictMap_size(tcmap);
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	int hasCaption = 0;
	for(i = 0; i < size; i++) {
		if(!hasCaption) {
			knh_write_char(ctx, w, _("Const"));
			knh_write_EOL(ctx, w);
			hasCaption = 1;
		}
		knh_printf(ctx, w, "\t%s.%s: %O\n", CLASSN(cid),
				knh_String_tochar(knh_DictMap_keyAt(tcmap, i)),
				knh_DictMap_valueAt(tcmap, i));
	}
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
}

/* ======================================================================== */
/* [SystemConst] */

#define _KNH_SYS(ctx, n)    knh_getSystemConst(ctx, n)
#define _KNH_SYS_CTX    0
#define _KNH_SYS_STDIN  1
#define _KNH_SYS_STDOUT 2
#define _KNH_SYS_STDERR 3
#define _KNH_SYS_OS     4
#define _KNH_SYS_SCRIPT 5

Object *knh_getSystemConst(Ctx *ctx, int n)
{
	switch(n) {
		case _KNH_SYS_CTX:     return (Object*)ctx;
		case _KNH_SYS_STDIN:   return (Object*)((ctx)->in);
		case _KNH_SYS_STDOUT:  return (Object*)((ctx)->out);
		case _KNH_SYS_STDERR:  return (Object*)((ctx)->err);
		case _KNH_SYS_OS:      return (Object*)knh_getClassDefaultValue(ctx, CLASS_System);
		case _KNH_SYS_SCRIPT:  return (Object*)knh_NameSpace_getScript(ctx, (ctx->share)->mainns);
	}
	DBG_P("unknown system const n=%d", n);
	return KNH_NULL;
}

/* ======================================================================== */
/* [tfieldn, tmethodn] */

static
char *knh_format_nzname(char *buf, size_t bufsiz, knh_bytes_t t)
{
	size_t i = 0, u =  0, c = 0;
	if(isdigit(t.buf[i])) {
		/* %4.2f*/
		while(isdigit(t.buf[i]) || t.buf[i] == '.') i++;
	}
	for(; i < t.len; i++) {
		if(t.buf[i] == '.')  break ;  /* %itr.%itr */
		if(t.buf[i] == '_') {
			u = 1; continue;
		}
		if(u == 1) {
			buf[c] = toupper(t.buf[i]);
			u = 0;
		}
		else {
			buf[c] = t.buf[i];
		}
		c++;
		if(!(c + 1 < bufsiz)) {
			break;
		}
	}
	buf[c] = 0;
	if(isupper(buf[0])) buf[0] = tolower(buf[0]);
//	DEBUG("'%s'", buf);
	return buf;
}

/* ------------------------------------------------------------------------ */

static
knh_fieldn_t knh_System_getfn(Ctx *ctx, knh_bytes_t n, knh_fieldn_t def)
{
	char buf[CLASSNAME_BUFSIZ];
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	knh_index_t idx = knh_DictIdx_index(ctx, DP(ctx->sys)->FieldNameDictIdx, n);
	if(idx == -1) {
		knh_format_nzname(buf, sizeof(buf), n);
		n = B(buf);
		idx = knh_DictIdx_index(ctx, DP(ctx->sys)->FieldNameDictIdx, n);
	}
	if(idx == -1) {
		if(def == FIELDN_NEWID) {
			String *s = new_String(ctx, n, NULL);
			idx = knh_DictIdx_add__fast(ctx, DP(ctx->sys)->FieldNameDictIdx, s);
			if(!(idx < KNH_FLAG_MN_SETTER)) {  /* Integer overflowed */
				DBG_P("idx=%d < %d", (int)idx, (int)KNH_FLAG_MN_SETTER);
				DBG2_ABORT();
				KNH_THROWs(ctx, "OutOfMemory!!: Too many field names");
			}
		}
		else {
			idx = def;
		}
	}
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	return (knh_fieldn_t)idx;
}

/* ------------------------------------------------------------------------ */

int knh_bytes_isOptionalMT(knh_bytes_t t)
{
	DBG2_ASSERT(t.buf[0] != '%');
	return (isdigit(t.buf[0]) || knh_bytes_index(t, '%') > 0);
}

/* ------------------------------------------------------------------------ */

knh_bytes_t knh_bytes_mtoption(knh_bytes_t t)
{
	size_t i = 0;
	while(isdigit(t.buf[i]) || t.buf[i] == '.') i++;
	t.len = i;
	return t;
}

/* ------------------------------------------------------------------------ */

char *knh_format_newFMT(char *buf, size_t bufsiz, knh_bytes_t t, int dot, char *fmt)
{
	size_t i = 0, j = 1;
	buf[0] = '%';
	for(j = 1; j < bufsiz; j++) {
		if(t.buf[i] == '.') {
			i++;
			if(dot == 1) {
				buf[j] = '.';
				dot = 0;
			}
			else {
				dot = -1;
			}
			continue;
		}
		if(!isdigit(t.buf[i])) {
			i = (fmt[0] == '%') ? 1 : 0;
			for(;fmt[i] != 0; i++) {
				buf[j] = fmt[i]; j++;
			}
			buf[j] = 0;
			DBG_P("FMT='%s'", buf);
			return buf;
		}
		if(dot >= 0) {
			buf[j] = t.buf[i];
		}
		i++;
	}
	buf[0] = 0;
	return buf;
}

/* ======================================================================== */
/* [tfieldn] */

String *knh_getFieldName(Ctx *ctx, knh_fieldn_t fn)
{
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	String *s = (String*)knh_DictIdx_get__fast(DP(ctx->sys)->FieldNameDictIdx, FIELDN_UNMASK(fn));
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	DBG_(
	if(IS_NULL(s)) {
		DBG_P("unknown fn=%d", (int)FIELDN_UNMASK(fn));
		return TS_EMPTY;
	})
	return s;
}

#define _FIELDN(fn) knh_String_tochar(knh_getFieldName(ctx, fn))

/* ------------------------------------------------------------------------ */

knh_fieldn_t knh_getfnq(Ctx *ctx, knh_bytes_t tname, knh_fieldn_t def)
{
	knh_index_t idx = knh_bytes_index(tname, ':');
	if(idx > 0) {
		tname = knh_bytes_first(tname, idx);
	}
	if(tname.len == 0 || tname.len > 80) {
		DBG2_P("invalid field name '%s'", tname.buf);
		return FIELDN_NONAME;
	}
	else {
		knh_fieldn_t mask = 0;
		if(knh_bytes_startsWith(tname, STEXT("super."))) {
			mask = KNH_FLAG_FN_SUPER;
			tname = knh_bytes_last(tname, 6);
		}
		else if(!knh_bytes_endsWith(tname, STEXT("__"))) {
			if(tname.buf[0] == '_') {
				mask = KNH_FLAG_FN_U1;
				tname = knh_bytes_last(tname, 1);
			}
			if(tname.buf[0] == '_') {
				mask = KNH_FLAG_FN_U2;
				tname = knh_bytes_last(tname, 1);
			}
			while(tname.buf[0] == '_') {
				tname = knh_bytes_last(tname, 1);
			}
		}

		KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
		idx = knh_DictIdx_index(ctx, DP(ctx->sys)->FieldNameDictIdx, tname);
		if(idx == -1) {
			if(def == FIELDN_NEWID) {
				String *s = new_String(ctx, tname, NULL);
				idx = knh_DictIdx_add__fast(ctx, DP(ctx->sys)->FieldNameDictIdx, s);
				if(!(idx < KNH_FLAG_FN_U2)) {
					DBG_P("idx=%d < %d", (int)idx, (int)KNH_FLAG_FN_U2);
					DBG2_ABORT();
					KNH_THROWs(ctx, "OutOfMemory!!: Too many field names");
				}
			}
			else {
				idx = def;
			}
		}
		KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
		return ((knh_fieldn_t)idx | mask);
	}
}

/* ======================================================================== */
/* [methodn] */

//String *new_String__mn(Ctx *ctx, knh_methodn_t mn)
//{
//	if(METHODN_IS_MOVTEXT(mn)) {
//		char buf[CLASSNAME_BUFSIZ];
//		knh_snprintf(buf, sizeof(buf), "%%%s", FIELDN(METHODN_TOFIELDN(mn)));
//		return new_String(ctx, B(buf), NULL);
//	}
//	if(METHODN_IS_GETTER(mn)) {
//		char buf[CLASSNAME_BUFSIZ];
//		knh_snprintf(buf, sizeof(buf), "get%s", FIELDN(METHODN_TOFIELDN(mn)));
//		if(islower(buf[3])) buf[3] = toupper(buf[3]);
//		return new_String(ctx, B(buf), NULL);
//	}
//	if(METHODN_IS_SETTER(mn)) {
//		char buf[CLASSNAME_BUFSIZ];
//		knh_snprintf(buf, sizeof(buf), "set%s", FIELDN(METHODN_TOFIELDN(mn)));
//		if(islower(buf[3])) buf[3] = toupper(buf[3]);
//		return new_String(ctx, B(buf), NULL);
//	}
//
//	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
//	String *s = (String*)knh_DictIdx_get__fast(DP(ctx->sys)->FieldNameDictIdx, FIELDN_UNMASK(mn));
//	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
//	if(IS_NULL(s)) {
//		return TS_EMPTY;
//	}
//	return s;
//}

/* ------------------------------------------------------------------------ */

knh_methodn_t knh_getmn(Ctx *ctx, knh_bytes_t tname, knh_methodn_t def)
{
	if(tname.len == 0 || tname.len > 64) {
		DBG2_P("invalid method name '%s'", tname.buf);
		return METHODN_NONAME;
	}
	if(tname.buf[0] == '%') {
		knh_fieldn_t fn = knh_System_getfn(ctx, knh_bytes_last(tname, 1), def);
		if(fn == FIELDN_NONAME) {
			return METHODN_NONAME;
		}
		return KNH_FLAG_MN_MOVTEXT | fn;
	}
	else if(tname.buf[0] == 'g' && tname.buf[1] == 'e' && tname.buf[2] == 't') {
		knh_fieldn_t fn = knh_System_getfn(ctx, knh_bytes_last(tname, 3), def);
		if(fn == FIELDN_NONAME) {
			return METHODN_NONAME;
		}
		return KNH_FLAG_MN_GETTER | fn;
	}
	else if(tname.buf[0] == 's' && tname.buf[1] == 'e' && tname.buf[2] == 't') {
		knh_fieldn_t fn = knh_System_getfn(ctx, knh_bytes_last(tname, 3), def);
		if(fn == FIELDN_NONAME) {
			return METHODN_NONAME;
		}
		return KNH_FLAG_MN_SETTER | fn;
	}
	else {
		knh_fieldn_t fn = knh_System_getfn(ctx, tname, def);
		return fn;
	}
}

/* ------------------------------------------------------------------------ */

char *knh_format_methodn(Ctx *ctx, char *buf, size_t bufsiz, knh_methodn_t mn)
{
	if(METHODN_IS_MOVTEXT(mn)) {
		knh_snprintf(buf, bufsiz, "%%%s", FIELDN(METHODN_TOFIELDN(mn)));
		return buf;
	}
	if(METHODN_IS_GETTER(mn)) {
		knh_snprintf(buf, bufsiz, "get%s", FIELDN(METHODN_TOFIELDN(mn)));
		if(islower(buf[3])) buf[3] = toupper(buf[3]);
		return buf;
	}
	if(METHODN_IS_SETTER(mn)) {
		knh_snprintf(buf, bufsiz, "set%s", FIELDN(METHODN_TOFIELDN(mn)));
		if(islower(buf[3])) buf[3] = toupper(buf[3]);
		return buf;
	}
	knh_snprintf(buf, bufsiz, "%s", FIELDN(mn));
	return buf;
}

/* ------------------------------------------------------------------------ */

char *
knh_format_cmethodn(Ctx *ctx, char *buf, size_t bufsiz, knh_class_t cid, knh_methodn_t mn)
{
	if(METHODN_IS_MOVTEXT(mn)) {
		knh_snprintf(buf, bufsiz, "%s.%%%s", CLASSN(cid), FIELDN(METHODN_TOFIELDN(mn)));
		return buf;
	}
	if(METHODN_IS_GETTER(mn)) {
		int off = knh_strlen(CLASSN(cid))+4;
		knh_snprintf(buf, bufsiz, "%s.get%s", CLASSN(cid), FIELDN(METHODN_TOFIELDN(mn)));
		if(islower(buf[off])) buf[off] = toupper(buf[off]);
		return buf;
	}
	if(METHODN_IS_SETTER(mn)) {
		int off = knh_strlen(CLASSN(cid))+4;
		knh_snprintf(buf, bufsiz, "%s.set%s", CLASSN(cid), FIELDN(METHODN_TOFIELDN(mn)));
		if(islower(buf[off])) buf[off] = toupper(buf[off]);
		return buf;
	}
	knh_snprintf(buf, bufsiz, "%s.%s", CLASSN(cid), FIELDN(mn));
	return buf;
}

/* ======================================================================== */
/* [uri] */

knh_uri_t knh_getResourceId(Ctx *ctx, knh_bytes_t t)
{
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	knh_index_t idx = knh_DictIdx_index(ctx, DP(ctx->sys)->ResourceDictIdx, t);
	if(idx == -1) {
		String *s = new_String(ctx, t, NULL);
		idx = knh_DictIdx_add__fast(ctx, DP(ctx->sys)->ResourceDictIdx, s);
	}
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	return (knh_uri_t)idx;
}

/* ------------------------------------------------------------------------ */

knh_uri_t knh_cwb_getResourceId(Ctx *ctx, knh_cwb_t *cwb)
{
	knh_bytes_t t = knh_cwb_tobytes(cwb);
	knh_uri_t uri = 0;
	if(!knh_bytes_startsWith(t, STEXT("http://"))) {
		knh_cwb_realpath(ctx, cwb);
		t = knh_cwb_tobytes(cwb);
	}
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	{
		knh_index_t idx = knh_DictIdx_index(ctx, DP(ctx->sys)->ResourceDictIdx, t);
		if(idx == -1) {
			String *s = knh_cwb_newString(ctx, cwb);
			idx = knh_DictIdx_add__fast(ctx, DP(ctx->sys)->ResourceDictIdx, s);
			t = knh_String_tobytes(s);
			knh_cwb_write(ctx, cwb, t);
		}
		uri = (knh_uri_t)idx;
	}
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	if(!knh_isTrustedPath(ctx, t)) {
		uri = URI_UNTRUSTED(uri);
	}
	return uri;
}

/* ------------------------------------------------------------------------ */

String *knh_getResourceName(Ctx *ctx, knh_uri_t uri)
{
	String *s;
	uri = URI_UNMASK(uri);
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	s = (String*)knh_DictIdx_get__fast(DP(ctx->sys)->ResourceDictIdx, uri);
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	DBG_(
		if(IS_NULL(s)) {
			DBG_P("unknown uri=%d", (int)uri);
			return TS_EMPTY;
		}
	)
	return s;
}

#define _URIDN(uri) knh_String_tochar(knh_getResourceName(ctx, uri))
#define _FILEN(uri) knh_safefile(URIDN(uri))

/* ======================================================================== */
/* [tPackage] */

#define knh_homeDir                DP(ctx->sys)->homeDir
#define knh_sysnsDictMap           DP(ctx->sys)->sysnsDictMap
#define knh_funcDictSet            DP(ctx->sys)->funcDictSet
#define knh_drvapiDictSet          DP(ctx->sys)->drvapiDictSet
#define knh_makespecDictSet        DP(ctx->sys)->makespecDictSet

/* ======================================================================== */
/* [DRVAPI] */

void knh_addDriverAPI(Ctx *ctx, char *alias, knh_drvapi_t* p)
{
	char bufn[CLASSNAME_BUFSIZ];
	KNH_ASSERT(IS_DRVAPI(p->type));
	if(alias == NULL) {
		knh_snprintf(bufn, sizeof(bufn), "%s:%02d", p->name, p->type);
	}
	else {
		knh_snprintf(bufn, sizeof(bufn), "%s:%02d", alias, p->type);
	}
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	knh_DictSet_set(ctx, DP(ctx->sys)->DriversTableDictSet, new_String(ctx, B(bufn), NULL), (knh_uintptr_t)p);
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
}

/* ------------------------------------------------------------------------ */

knh_drvapi_t *knh_getDriverAPI(Ctx *ctx, int type, knh_bytes_t name)
{
	char bufn[CLASSNAME_BUFSIZ], bufn2[CLASSNAME_BUFSIZ];
	knh_format_bytes(bufn2, sizeof(bufn2), name);
	knh_snprintf(bufn, sizeof(bufn), "%s:%02d", bufn2, type);
	KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
	knh_drvapi_t *p = (knh_drvapi_t*)knh_DictSet_get__b(DP(ctx->sys)->DriversTableDictSet, B(bufn));
	KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	return p;
}

/* ------------------------------------------------------------------------ */
/* [NameSpace] */

NameSpace *knh_getNameSpace(Ctx *ctx, knh_bytes_t name)
{
	if(knh_bytes_equals(name, STEXT("main"))) {
		KNH_ASSERT(IS_NameSpace(ctx->share->mainns));
		return ctx->share->mainns;
	}
	else {
		NameSpace *ns;
		KNH_LOCK(ctx, LOCK_SYSTBL, NULL);
		ns = (NameSpace*)knh_DictMap_get__b(ctx,  DP(ctx->sys)->NameSpaceTableDictMap, name);
		KNH_UNLOCK(ctx, LOCK_SYSTBL, NULL);
		return ns;
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
