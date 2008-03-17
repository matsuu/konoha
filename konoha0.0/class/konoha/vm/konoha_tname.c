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

#define KNH_FIELDN_MAXSIZ   64
#define KNH_METHODN_MAXSIZ  64

#define _NSN_main           0
#define _FILEN_unknown      0

/* ======================================================================== */
/* [global] */

static DictIdx *tnsnDictIdx         = NULL;
static DictIdx *tfilenDictIdx       = NULL;
static DictIdx *tfieldnDictIdx      = NULL;

/* ------------------------------------------------------------------------ */

void knh_tname_ginit()
{
	DEBUG_ASSERT(tfieldnDictIdx == NULL);
	KNH_INITv(tfieldnDictIdx, new_DictIdx(NULL, KONOHA_TFIELDN_SIZE * 2, 0));
	KNH_INITv(tnsnDictIdx, new_DictIdx(NULL, 8, 0));
	knh_tnsn_forname(NULL, STEXT("main"));
	DEBUG_ASSERT(knh_tnsn_forname(NULL, STEXT("main")) == NSN_main);
	KNH_INITv(tfilenDictIdx, new_DictIdx(NULL, 32, 0));
	knh_tfilen_forname(NULL, STEXT("(unknown)"));
	DEBUG_ASSERT(knh_tfilen_forname(NULL, STEXT("(unknown)")) == FILEN_unknown);
}

/* ------------------------------------------------------------------------ */

void knh_tname_gtraverse(Ctx *ctx, f_gc gc)
{
	gc(ctx, tfieldnDictIdx);
	gc(ctx, tnsnDictIdx);
	gc(ctx, tfilenDictIdx);
	if(IS_SWEEP(gc)) {
		tfieldnDictIdx = NULL;
		tnsnDictIdx    = NULL;
		tfilenDictIdx    = NULL;
	}
}

/* ======================================================================== */
/* [tfieldn, tmethodn] */

char *
knh_format_nzname(char *buf, size_t bufsiz, knh_bytes_t t)
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

knh_fieldn_t knh_tfieldn_common(Ctx *ctx, knh_bytes_t n, knh_fieldn_t def)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_format_nzname(buf, sizeof(buf), n);
	knh_bytes_t tname = B(buf);
	
	knh_index_t idx = knh_DictIdx_index(ctx, tfieldnDictIdx, tname);
	if(idx == -1) {
		if(def == FIELDN_NEWID) {
			String *s = new_String__fast(ctx, CLASS_String__field, tname);
			knh_fieldn_t fn = 
				(knh_fieldn_t)knh_DictIdx_add__fast(ctx, tfieldnDictIdx, s);
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

INLINE
String *knh_tfieldn_name(knh_fieldn_t fn)
{
	return knh_DictIdx_get__fast(tfieldnDictIdx, fn);
}

#define _FIELDN(fn) knh_String_tochar(knh_tfieldn_name(fn))

/* ------------------------------------------------------------------------ */

knh_fieldn_t knh_tfieldn_forname(Ctx *ctx, knh_bytes_t tname, knh_fieldn_t def)
{
	if(tname.len == 0 || tname.len > KNH_FIELDN_MAXSIZ || knh_bytes_index(tname, ':') > 0) {
		return FIELDN_NONAME;
	}
	knh_index_t idx = knh_DictIdx_index(ctx, tfieldnDictIdx, tname);
	if(idx == -1) {
		return knh_tfieldn_common(ctx, tname, def);
	}
	return (knh_fieldn_t)idx;
}

/* ------------------------------------------------------------------------ */

void KNH_TFIELDN(Ctx *ctx, knh_fieldn_t fn, String *name)
{
#if defined(KONOHA_DEBUGMODE)
	knh_fieldn_t fn2 = (knh_fieldn_t)knh_DictIdx_add__fast(ctx, tfieldnDictIdx, name);
	//DEBUG("'%s' %d %d", knh_String_tochar(name), fn, fn2);
	DEBUG_ASSERT(fn == fn2);
#else
	knh_DictIdx_add__fast(ctx, tfieldnDictIdx, name);
#endif
}

/* ------------------------------------------------------------------------ */

knh_fieldn_t knh_tfieldn_level(Ctx *ctx, int level)
{
	char bufn[40];
	knh_snprintf(bufn, sizeof(bufn), "%dv", level);
	knh_bytes_t tname = B(bufn);
	
	knh_index_t idx = knh_DictIdx_index(ctx, tfieldnDictIdx, tname);
	if(idx == -1) {
		return knh_tfieldn_common(ctx, tname, FIELDN_NEWID);
	}
	return (knh_fieldn_t)idx;
}




/* ======================================================================== */
/* [methodn] */

#define _METHODN(mn)  FIELDN(METHODN_TOFIELDN(mn))

/* ------------------------------------------------------------------------ */

knh_methodn_t knh_tmethodn_forname(Ctx *ctx, knh_bytes_t tname, knh_methodn_t def)
{
	knh_methodn_t mn_mask = 0;
	if(tname.len == 0 || tname.len > KNH_METHODN_MAXSIZ) {
		return METHODN_NONAME;
	}
	if(tname.buf[0] == '%') {
		mn_mask |= KNH_FLAG_MN_MOVTEXT;
		knh_fieldn_t fn = knh_tfieldn_common(ctx, knh_bytes_last(tname, 1), def);
		if(fn == FIELDN_NONAME) {
			return METHODN_NONAME;
		}
		return mn_mask | fn;
	}
	if(tname.buf[0] == 'g' && tname.buf[1] == 'e' && tname.buf[2] == 't') {
		mn_mask |= KNH_FLAG_MN_GETTER;
		knh_fieldn_t fn = knh_tfieldn_common(ctx, knh_bytes_last(tname, 3), def);
		if(fn == FIELDN_NONAME) {
			return METHODN_NONAME;
		}
		return mn_mask | fn;		
	}
	if(tname.buf[0] == 's' && tname.buf[1] == 'e' && tname.buf[2] == 't') {
		mn_mask |= KNH_FLAG_MN_SETTER;
		knh_fieldn_t fn = knh_tfieldn_common(ctx, knh_bytes_last(tname, 3), def);
		if(fn == FIELDN_NONAME) {
			return METHODN_NONAME;
		}
		return mn_mask | fn;		
	}
	knh_fieldn_t fn = knh_tfieldn_common(ctx, tname, def);
	return mn_mask | fn;
}

/* ------------------------------------------------------------------------ */

char *
knh_format_methodn(char *buf, size_t bufsiz, knh_methodn_t mn)
{
	if(METHODN_IS_MOVTEXT(mn)) {
		snprintf(buf, bufsiz, "%%%s", FIELDN(METHODN_TOFIELDN(mn)));
		return buf;
	}
	if(METHODN_IS_GETTER(mn)) {
		snprintf(buf, bufsiz, "get%s", FIELDN(METHODN_TOFIELDN(mn)));
		if(islower(buf[3])) buf[3] = toupper(buf[3]);
		return buf;
	}
	if(METHODN_IS_SETTER(mn)) {
		snprintf(buf, bufsiz, "set%s", FIELDN(METHODN_TOFIELDN(mn)));
		if(islower(buf[3])) buf[3] = toupper(buf[3]);
		return buf;
	}
	snprintf(buf, bufsiz, "%s", FIELDN(mn));
	return buf;
}

/* ======================================================================== */
/* [nsn] */

char *
knh_bytes_nznsn(knh_bytes_t t, char *buf, size_t bufsiz)
{
	size_t i;
	for(i = 0; i < t.len; i++) {
		if(i < bufsiz) {
			buf[i] = tolower(t.buf[i]);
		}
		else {
			buf[bufsiz-1] = 0;
			return buf;
		}
	}
	buf[i] = 0;
	return buf;
}

/* ------------------------------------------------------------------------ */

knh_nsn_t knh_tnsn_forname(Ctx *ctx, knh_bytes_t t)
{
	char buf[KONOHA_NAME_SIZE];
	knh_bytes_nznsn(t, buf, sizeof(buf));
	knh_bytes_t ns = B(buf);
	
	knh_index_t idx = knh_DictIdx_index(ctx, tnsnDictIdx, ns);
	if(idx == -1) {
		String *s = new_String__fast(ctx, CLASS_String, ns);
		knh_nsn_t nsn = (knh_nsn_t)knh_DictIdx_add__fast(ctx, tnsnDictIdx, s);
		return nsn;
	}
	return (knh_nsn_t)idx;
}

/* ------------------------------------------------------------------------ */

INLINE
String *knh_tnsn_name(knh_nsn_t nsn)
{
	return knh_DictIdx_get__fast(tnsnDictIdx, nsn);
}

#define _NSN(nsn) knh_String_tochar(knh_tnsn_name(nsn))

/* ======================================================================== */
/* [filen] */

knh_filen_t knh_tfilen_forname(Ctx *ctx, knh_bytes_t t)
{
	knh_index_t idx = knh_DictIdx_index(ctx, tfilenDictIdx, t);
	if(idx == -1) {
		String *s = new_String__fast(ctx, CLASS_String, t);
		knh_filen_t filen = (knh_filen_t)knh_DictIdx_add__fast(ctx, tfilenDictIdx, s);
		return filen;
	}
	return (knh_filen_t)idx;
}

/* ------------------------------------------------------------------------ */

INLINE
String *knh_tfilen_name(knh_filen_t filen)
{
	return knh_DictIdx_get__fast(tfilenDictIdx, filen);
}

#define _FILEN(filen) knh_String_tochar(knh_tfilen_name(filen))

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
