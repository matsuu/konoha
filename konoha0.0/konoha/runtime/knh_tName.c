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
/* [macro] */

//#define KNH_FIELDN_MAXSIZ   64
//#define KNH_METHODN_MAXSIZ  64

#define _FIELDN_NONAME    ((knh_fieldn_t)-1)
#define _FIELDN_NEWID     ((knh_fieldn_t)-2)
#define _FIELDN_return    FIELDN_
#define _METHODN_NONAME   ((knh_methodn_t)-1)
#define _METHODN_NEWID    ((knh_methodn_t)-2)

#define _KNH_FLAG_FN_SUPER   KNH_FLAG_T0
#define _KNH_FLAG_FN_U1      KNH_FLAG_T1
#define _KNH_FLAG_FN_U2      KNH_FLAG_T2
#define _FIELDN_IS_SUPER(fnq)       ((fnq & KNH_FLAG_FN_SUPER) == KNH_FLAG_FN_SUPER)
#define _FIELDN_IS_U1(fnq)          ((fnq & KNH_FLAG_FN_U1) == KNH_FLAG_FN_U1)
#define _FIELDN_IS_U2(fnq)          ((fnq & KNH_FLAG_FN_U2) == KNH_FLAG_FN_U2)
#define _FIELDN_IS_PROTECTED(fnq)   (FIELDN_IS_U1(fnq)||FIELDN_IS_U2(fnq))
#define _FIELDN_UNMASK(fnq)         (fnq & (~(KNH_FLAG_FN_SUPER|KNH_FLAG_FN_U1|KNH_FLAG_FN_U2)))

//#define _METHODN_NONAME   KONOHA_TCLASS_SIZE
//#define _METHODN_NEWID    0

// 0000 0000 0000 0000
// 0100 0000 0000 0000
// 0010 0000 0000 0000
// 0110 0000 0000 0000

#define _KNH_FLAG_MN_SUPER        KNH_FLAG_T0
#define _KNH_FLAG_MN_GETTER       KNH_FLAG_T1
#define _KNH_FLAG_MN_SETTER       KNH_FLAG_T2
#define _KNH_FLAG_MN_MOVTEXT      (KNH_FLAG_T1|KNH_FLAG_T2)
#define _KNH_FLAG_MN_FIELDN       (~(KNH_FLAG_T0|KNH_FLAG_T1|KNH_FLAG_T2))

#define _METHODN_IS_GETTER(mn)   ((mn & KNH_FLAG_MN_MOVTEXT) == KNH_FLAG_MN_GETTER)
#define _METHODN_TO_GETTER(mn)   (mn | KNH_FLAG_MN_GETTER)
#define _METHODN_IS_SETTER(mn)   ((mn & KNH_FLAG_MN_MOVTEXT) == KNH_FLAG_MN_SETTER)
#define _METHODN_TO_SETTER(mn)   (mn | KNH_FLAG_MN_SETTER)
#define _METHODN_IS_MOVTEXT(mn)  ((mn & KNH_FLAG_MN_MOVTEXT) == KNH_FLAG_MN_MOVTEXT)
#define _METHODN_TO_MOVTEXT(mn)  (mn | KNH_FLAG_MN_MOVTEXT)

#define _METHODN_TOFIELDN(mn)     (mn & KNH_FLAG_MN_FIELDN)

/* ======================================================================== */
/* [tfieldn, tmethodn] */

static
char *knh_format_nzname(char *buf, size_t bufsiz, knh_bytes_t t)
{
	size_t i, u =  0, c = 0;
	for(i = 0; i < t.len; i++) {
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
knh_fieldn_t knh_tfieldn_common(Ctx *ctx, knh_bytes_t n, knh_fieldn_t def)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_format_nzname(buf, sizeof(buf), n);
	knh_bytes_t tname = B(buf);

	knh_index_t idx = knh_DictIdx_index(ctx, DP(knh_rootSystem)->tfieldnDictIdx, tname);
	if(idx == -1) {
		if(def == FIELDN_NEWID) {
			String *s = new_String(ctx, tname, NULL);
			knh_fieldn_t fn =
				(knh_fieldn_t)knh_DictIdx_add__fast(ctx, DP(knh_rootSystem)->tfieldnDictIdx, s);
			if(fn == (knh_fieldn_t)-1) {  /* Integer overflowed */
				KNH_THROWs(ctx, "OutOfMemory!!: Too many field names");
			}
			return fn;
		}
		return def;
	}
	return (knh_fieldn_t)idx;
}



/* ======================================================================== */
/* [tfieldn] */

void KNH_TFIELDN__T(Ctx *ctx, knh_fieldn_t fn, char *text)
{
	String *name = new_String__T(ctx, text);
#if defined(KNH_DBGMODE2)
	knh_fieldn_t fn2 = (knh_fieldn_t)knh_DictIdx_add__fast(ctx, DP(knh_rootSystem)->tfieldnDictIdx, name);
	//DEBUG("'%s' %d %d", knh_String_tochar(name), fn, fn2);
	KNH_ASSERT(fn == fn2);
#else
	knh_DictIdx_add__fast(ctx, DP(knh_rootSystem)->tfieldnDictIdx, name);
#endif
}

/* ------------------------------------------------------------------------ */

String *knh_tfieldn_name(knh_fieldn_t fn)
{
	String *s = (String*)knh_DictIdx_get__fast(DP(knh_rootSystem)->tfieldnDictIdx, FIELDN_UNMASK(fn));
	DBG_(
	if(IS_NULL(s)) {
		DBG2_P("unknown fn=%d", (int)FIELDN_UNMASK(fn));
		return TS_EMPTY;
	})
	return s;
}

#define _FIELDN(fn) knh_String_tochar(knh_tfieldn_name(fn))

/* ------------------------------------------------------------------------ */

knh_fieldn_t knh_tName_get_fnq(Ctx *ctx, knh_bytes_t tname, knh_fieldn_t def)
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
		if(!knh_bytes_endsWith(tname, STEXT("__"))) {
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
		idx = knh_DictIdx_index(ctx, DP(knh_rootSystem)->tfieldnDictIdx, tname);
		if(idx == -1) {
			if(def == FIELDN_NEWID) {
				String *s = new_String(ctx, tname, NULL);
				knh_fieldn_t fn = (knh_fieldn_t)knh_DictIdx_add__fast(ctx, DP(knh_rootSystem)->tfieldnDictIdx, s);
				if(!(fn < KNH_FLAG_FN_U2)) {
					KNH_THROWs(ctx, "OutOfMemory!!: Too many field names");
				}
				return fn | mask;
			}
			return def;
		}
		return ((knh_fieldn_t)idx | mask);
	}
}

/* ======================================================================== */
/* [methodn] */

//#define _METHODN(mn)  FIELDN(METHODN_TOFIELDN(mn))


String *new_String__mn(Ctx *ctx, knh_methodn_t mn)
{
	if(METHODN_IS_MOVTEXT(mn)) {
		char buf[CLASSNAME_BUFSIZ];
		knh_snprintf(buf, sizeof(buf), "%%%s", FIELDN(METHODN_TOFIELDN(mn)));
		return new_String(ctx, B(buf), NULL);
	}
	if(METHODN_IS_GETTER(mn)) {
		char buf[CLASSNAME_BUFSIZ];
		knh_snprintf(buf, sizeof(buf), "get%s", FIELDN(METHODN_TOFIELDN(mn)));
		if(islower(buf[3])) buf[3] = toupper(buf[3]);
		return new_String(ctx, B(buf), NULL);
	}
	if(METHODN_IS_SETTER(mn)) {
		char buf[CLASSNAME_BUFSIZ];
		knh_snprintf(buf, sizeof(buf), "set%s", FIELDN(METHODN_TOFIELDN(mn)));
		if(islower(buf[3])) buf[3] = toupper(buf[3]);
		return new_String(ctx, B(buf), NULL);
	}
	String *s = (String*)knh_DictIdx_get__fast(DP(knh_rootSystem)->tfieldnDictIdx, FIELDN_UNMASK(mn));
	if(IS_NULL(s)) {
		return TS_EMPTY;
	}
	return s;
}

/* ------------------------------------------------------------------------ */

knh_methodn_t knh_tName_getMethodn(Ctx *ctx, knh_bytes_t tname, knh_methodn_t def)
{
	if(tname.len == 0 || tname.len > 64) {
		DBG2_P("invalid method name '%s'", tname.buf);
		return METHODN_NONAME;
	}
	if(tname.buf[0] == '%') {
		knh_fieldn_t fn = knh_tfieldn_common(ctx, knh_bytes_last(tname, 1), def);
		if(fn == FIELDN_NONAME) {
			return METHODN_NONAME;
		}
		return KNH_FLAG_MN_MOVTEXT | fn;
	}
	else if(tname.buf[0] == 'g' && tname.buf[1] == 'e' && tname.buf[2] == 't') {
		knh_fieldn_t fn = knh_tfieldn_common(ctx, knh_bytes_last(tname, 3), def);
		if(fn == FIELDN_NONAME) {
			return METHODN_NONAME;
		}
		return KNH_FLAG_MN_GETTER | fn;
	}
	else if(tname.buf[0] == 's' && tname.buf[1] == 'e' && tname.buf[2] == 't') {
		knh_fieldn_t fn = knh_tfieldn_common(ctx, knh_bytes_last(tname, 3), def);
		if(fn == FIELDN_NONAME) {
			return METHODN_NONAME;
		}
		return KNH_FLAG_MN_SETTER | fn;
	}
	else {
		knh_fieldn_t fn = knh_tfieldn_common(ctx, tname, def);
		return fn;
	}
}

/* ------------------------------------------------------------------------ */

char *
knh_format_methodn(char *buf, size_t bufsiz, knh_methodn_t mn)
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
knh_format_methodparam(char *buf, size_t bufsiz, knh_methodn_t mn, int n)
{
	if(METHODN_IS_MOVTEXT(mn)) {
		knh_snprintf(buf, bufsiz, "%%%s(#%d)", FIELDN(METHODN_TOFIELDN(mn)), n);
		return buf;
	}
	if(METHODN_IS_GETTER(mn)) {
		knh_snprintf(buf, bufsiz, "get%s(#%d)", FIELDN(METHODN_TOFIELDN(mn)), n);
		if(islower(buf[3])) buf[3] = toupper(buf[3]);
		return buf;
	}
	if(METHODN_IS_SETTER(mn)) {
		knh_snprintf(buf, bufsiz, "set%s(#%d)", FIELDN(METHODN_TOFIELDN(mn)), n);
		if(islower(buf[3])) buf[3] = toupper(buf[3]);
		return buf;
	}
	knh_snprintf(buf, bufsiz, "%s(#%d)", FIELDN(mn), n);
	return buf;
}

/* ------------------------------------------------------------------------ */

char *
knh_format_cmethodn(char *buf, size_t bufsiz, knh_class_t cid, knh_methodn_t mn)
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
/* [fileid] */

knh_fileid_t knh_tName_getFileId(Ctx *ctx, knh_bytes_t t)
{
	knh_index_t idx = knh_DictIdx_index(ctx, DP(knh_rootSystem)->tfileidDictIdx, t);
	if(idx == -1) {
		String *s = new_String(ctx, t, NULL);
		knh_fileid_t filen = (knh_fileid_t)knh_DictIdx_add__fast(ctx, DP(knh_rootSystem)->tfileidDictIdx, s);
		return filen;
	}
	return (knh_fileid_t)idx;
}

/* ------------------------------------------------------------------------ */

String *knh_tfileid_name(knh_fileid_t fileid)
{
	String *s = (String*)knh_DictIdx_get__fast(DP(knh_rootSystem)->tfileidDictIdx, fileid);
	DBG_(
		if(IS_NULL(s)) {
			DBG_P("unknown fileid=%d", (int)fileid);
			return TS_EMPTY;
		}
	)
	return s;
}

#define _FILEIDN(fileid) knh_String_tochar(knh_tfileid_name(fileid))

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
