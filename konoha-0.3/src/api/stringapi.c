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

#ifdef KNH_CC_METHODAPI

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! String.equals(String! s) */

static METHOD knh__String_equals(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp,
		((sfp[0].s)->size == (sfp[1].s)->size &&
		knh_bytes_strcmp(knh_String_tobytes(sfp[0].s), knh_String_tobytes(sfp[1].s))));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! String.equalsIgnoreCase(String! s) */

static METHOD knh__String_equalsIgnoreCase(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp,
		((sfp[0].s)->size == (sfp[1].s)->size &&
		knh_bytes_strcasecmp(knh_String_tobytes(sfp[0].s), knh_String_tobytes(sfp[1].s))));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! String.startsWith(String! s) */

static METHOD knh__String_startsWith(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_bytes_startsWith(knh_String_tobytes(sfp[0].s), knh_String_tobytes(sfp[1].s)));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! String.endsWith(String! s) */

static METHOD knh__String_endsWith(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_bytes_endsWith(knh_String_tobytes(sfp[0].s), knh_String_tobytes(sfp[1].s)));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Int! String.indexOf(String! s) */

static METHOD knh__String_indexOf(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t base = knh_String_tobytes(sfp[0].s);
	knh_bytes_t delim = knh_String_tobytes(sfp[1].s);
	int loc = knh_bytes_indexOf(base, delim);
	if (knh_String_isASCII(sfp[0].s) || loc == -1) {
		KNH_RETURN_Int(ctx, sfp, loc);
	} else {
		base.len = (size_t)loc;
		KNH_RETURN_Int(ctx, sfp, knh_bytes_mlen(base));
	}
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Int! String.getSize() */

static METHOD knh__String_getSize(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_NULL(sfp[0].o)) {
		KNH_RETURN_Int(ctx, sfp, 0);
	}
	else {
		String *s = (String*)sfp[0].o;
		if(knh_String_isASCII(s)) {
			KNH_RETURN_Int(ctx, sfp, knh_String_strlen(s));
		}
		else {
			KNH_RETURN_Int(ctx, sfp, knh_bytes_mlen(knh_String_tobytes(s)));
		}
	}
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] String! String.opAdd(Any v) */

static METHOD knh__String_opAdd(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_cwb_t cwb = new_cwb(ctx);
//	if(IS_bString(sfp[0].o)) {
//		knh_Bytes_write(ctx, cwb.ba, knh_String_tobytes(sfp[0].s));
//	}
//	else {
//		KNH_SETESP(ctx, sfp, 2);
//		knh_sfp_format(ctx, sfp, METHODN__s, cwb.w, KNH_NULL);
//	}
//	if(IS_bString(sfp[1].o)) {
//		knh_Bytes_write(ctx, cwb.ba, knh_String_tobytes(sfp[1].s));
//	}
//	else {
//		KNH_SETESP(ctx, sfp, 2);
//		knh_sfp_format(ctx, sfp+1, METHODN__s, cwb.w, KNH_NULL);
//	}
	knh_sfp_t *esp = KNH_LOCAL(ctx);
	KNH_SETv(ctx, esp[1].o, sfp[0].o); esp[1].data = sfp[0].data;
	knh_esp1_format(ctx, METHODN__s, cwb.w, KNH_NULL);
	KNH_ASSERT(esp == ctx->esp);
	KNH_SETv(ctx, esp[1].o, sfp[1].o); esp[1].data = sfp[1].data;
	knh_esp1_format(ctx, METHODN__s, cwb.w, KNH_NULL);
	KNH_RETURN(ctx, sfp, new_String__cwb(ctx, cwb));
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS|STATIC|NULLBASE] String! String.concat(Any v) */

static METHOD knh__String_concat(Ctx *ctx, knh_sfp_t *sfp)
{
	int i, ac = knh_sfp_argc(ctx, sfp);
	knh_cwb_t cwb = new_cwb(ctx);
	knh_sfp_t *esp = KNH_LOCAL(ctx);
	for(i = 0; i < ac; i++) {
		if(IS_bString(sfp[i].o)) {
			knh_Bytes_write(ctx, cwb.ba, knh_String_tobytes(sfp[i].s));
		}
		else {
			KNH_ASSERT(esp == ctx->esp);
			KNH_SETv(ctx, esp[1].o, sfp[i].o); esp[1].data = sfp[i].data;
			knh_esp1_format(ctx, METHODN__s, cwb.w, KNH_NULL);
		}
	}
	KNH_RETURN(ctx, sfp, new_String__cwb(ctx, cwb));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String! String.opSub(String! t) */

static METHOD knh__String_opSub(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t base = knh_String_tobytes(sfp[0].s);
	knh_bytes_t t = knh_String_tobytes(sfp[1].s);
	knh_uchar_t c = t.buf[0];
	knh_cwb_t cwb = new_cwb(ctx);
	size_t i;
	for(i = 0; i < base.len; i++) {
		if(base.buf[i] == c) {
			size_t j;
			for(j = 1; j < t.len; j++) {
				if(base.buf[i+j] != t.buf[j]) break;
			}
			if(j == t.len) {
				i += t.len - 1;
				continue;
			}
		}
		knh_Bytes_putc(ctx, cwb.ba, base.buf[i]);
	}
	if(base.len == knh_cwb_size(cwb)) {
		knh_cwb_clear(cwb);
		KNH_RETURN(ctx, sfp, sfp[0].o);
	}
	else {
		KNH_RETURN(ctx, sfp, new_String__cwb(ctx, cwb));
	}
}

/* ------------------------------------------------------------------------ */

 static
int knh_bytes_equals_(knh_bytes_t base, size_t s, knh_bytes_t target)
{
	size_t i;
	for(i = 1; i < target.len; i++) {
		if(base.buf[s+i] != target.buf[i]) return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String! String.replace(String! o, String! n)      .....  */
/* @author nakata */

static METHOD knh__String_replace(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t base = knh_String_tobytes(sfp[0].s);
	knh_bytes_t target = knh_String_tobytes(sfp[1].s);
	knh_bytes_t alt = knh_String_tobytes(sfp[2].s);

	knh_cwb_t cwb = new_cwb(ctx);

	size_t i;
	int s = 0, ch = target.buf[0];
	for(i = 0; i < base.len - target.len+1; i++) {
		if(base.buf[i] == ch && knh_bytes_equals_(base, i, target)) {
			knh_Bytes_write(ctx, cwb.ba, alt);
			i += target.len - 1;
			s = i;
		}else {
			knh_Bytes_putc(ctx, cwb.ba, base.buf[i]);
		}
	}
	if(s == 0) {
		KNH_RETURN(ctx, sfp, sfp[0].o);
	}
	else {
		knh_bytes_t hs = {base.buf + i, base.len - i};
		knh_Bytes_write(ctx, cwb.ba, hs);
		KNH_RETURN(ctx, sfp, new_String__cwb(ctx, cwb));
	}
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String! String.opMul(Int! n) */

static METHOD knh__String_opMul(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_intptr_t n = p_int(sfp[1]);
	if(n <= 0) {
		KNH_RETURN(ctx, sfp, TS_EMPTY);
	}else if(n == 1) {
		KNH_RETURN(ctx, sfp, sfp[0].o);
	}
	else {
		knh_bytes_t base = knh_String_tobytes(sfp[0].s);
		knh_cwb_t cwb = new_cwb(ctx);
		knh_intptr_t i;
		for(i = 0; i < n; i++) {
			knh_Bytes_write(ctx, cwb.ba, base);
		}
		KNH_RETURN(ctx, sfp, new_String__cwb(ctx, cwb));
	}
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] String! String.opFmt(Any v) */

static METHOD knh__String_opFmt(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_cwb_t cwb = new_cwb(ctx);
	knh_sfp_t *v = sfp + 1;
	int ac = knh_sfp_argc(ctx, v);
	knh_bytes_t fmt = knh_String_tobytes(sfp[0].s);

	while(1) {
		knh_index_t loc = knh_bytes_index(fmt, '%');
		if(loc == -1) break;
		if(loc > 0) {
			knh_Bytes_write(ctx, cwb.ba, knh_bytes_first(fmt, loc));
		}
		if(fmt.buf[loc+1]=='%') {
			knh_Bytes_putc(ctx, cwb.ba, '%');
			fmt = knh_bytes_last(fmt, loc+2);
			continue;
		}
		fmt = knh_bytes_last(fmt, loc); /* a%s.. ==> s.. */
		loc = knh_bytes_index(fmt, '{');
		if(loc == -1) {
			KNH_WARNING(ctx, "formatting: there is no {} for %%%s", (char*)fmt.buf);
			goto L_ERROR;
		}
		knh_bytes_t mtn = knh_bytes_first(fmt, loc);
		knh_methodn_t mt =
			(mtn.len > 1) ? knh_tName_getMethodn(ctx, mtn, METHODN__empty) : METHODN__empty;
		int idx = -1;
		if(fmt.buf[loc+2] == '}') { /* %s{1} */
			idx = fmt.buf[loc+1] - '0';
			if(idx < 0 || idx > 9) {
				idx = -1;
			}
			fmt = knh_bytes_last(fmt, loc+3);
		}
		else if(fmt.buf[loc+3] == '}') { /* %s{11} */
			idx = (fmt.buf[loc+1] - '0') * 10 + (fmt.buf[loc+2] - '0');
			if(idx < 0 || idx > 99) {
				idx = -1;
			}
			fmt = knh_bytes_last(fmt, loc+3);
		}
		//DBG2_P("idx=%d", idx);
		if(idx == -1) {
			int quote = knh_Object_cid(sfp[0].o) == CLASS_String ? '"' : '\'';
			knh_bytes_t fmt = knh_String_tobytes(sfp[0].s);
			KNH_WARNING(ctx, "formatting: illegal string format: %c%s%c", quote, (char*)fmt.buf, quote);
			goto L_ERROR;
		}
		if(0 <= idx && (size_t) idx < ac) {
			knh_sfp_t *esp = KNH_LOCAL(ctx);
			KNH_SETv(ctx, esp[1].o, v[idx].o); esp[1].data = v[idx].data;
			mtn = knh_bytes_last(mtn, 1);
			Object *m = (mtn.len > 0 && knh_bytes_isOptionalMT(mtn)) ?
					UP(new_String(ctx, mtn, NULL)) : KNH_NULL;
			knh_esp1_format(ctx, mt, cwb.w, m);
		}
		else {
			KNH_WARNING(ctx, "formatting: out of index %d < %d", (int)idx, (int)ac);
			knh_write(ctx, cwb.w, STEXT("(null)"));
		}
	}
	if(fmt.len > 0) {
		knh_Bytes_write(ctx, cwb.ba, fmt);
	}
	L_ERROR:;
	KNH_RETURN(ctx, sfp, new_StringX__cwb(ctx, knh_Object_cid(sfp[0].o), cwb));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] String! String.opDiv(String v) */

static METHOD knh__String_opDiv(Ctx *ctx, knh_sfp_t *sfp)
{
	if(!IS_bString(sfp[0].o)) {
		KNH_RETURN(ctx, sfp, TS_EMPTY);
	}
	else {
		knh_bytes_t base = knh_String_tobytes(sfp[0].s);
		knh_index_t index = knh_bytes_indexOf(base, knh_String_tobytes(sfp[1].s));
		if(index == -1) {
			KNH_RETURN(ctx, sfp, sfp[0].o);
		}
		else {
			if(index == 0) {
				KNH_RETURN(ctx, sfp, TS_EMPTY);
			}
			else {
				base.len = index;
				KNH_RETURN(ctx, sfp, new_String(ctx, base, sfp[0].s));
			}
		}
	}
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] String! String.opMod(String v) */

static METHOD knh__String_opMod(Ctx *ctx, knh_sfp_t *sfp)
{
	if(!IS_bString(sfp[0].o)) {
		KNH_RETURN(ctx, sfp, TS_EMPTY);
	}
	else {
		knh_bytes_t base = knh_String_tobytes(sfp[0].s);
		knh_bytes_t delim = knh_String_tobytes(sfp[1].s);
		knh_index_t index = knh_bytes_indexOf(base, delim);
		if(index == -1) {
			KNH_RETURN(ctx, sfp, TS_EMPTY);
		}
		else {
			base = knh_bytes_last(base, index + delim.len);
			KNH_RETURN(ctx, sfp, new_String(ctx, base, sfp[0].s));
		}
	}
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! String.opHas(String! s) */

static METHOD knh__String_opHas(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_bytes_indexOf(knh_String_tobytes(sfp[0].s), knh_String_tobytes(sfp[1].s)) != -1);
}

/* ======================================================================== */
/* @method[CONST] String! String.get(Int! n) */

static METHOD knh__String_get(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t base = knh_String_tobytes(sfp[0].s);
	if(knh_String_isASCII(sfp[0].s)) {
		size_t n = knh_array_index(ctx, p_int(sfp[1]), knh_String_strlen(sfp[0].s));
		base.buf = base.buf + n;
		base.len = 1;
		KNH_RETURN(ctx, sfp, new_String(ctx, base, sfp[0].s));
	}
	else {
		size_t off = knh_array_index(ctx, p_int(sfp[1]), knh_bytes_mlen(base));
		knh_bytes_t sub = knh_bytes_mofflen(base, off, 1);
		KNH_RETURN(ctx, sfp, new_String(ctx, sub, sfp[0].s));
	}
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String! String.opOffset(Int offset, Int len) */

static METHOD knh__String_opOffset(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t base = knh_String_tobytes(sfp[0].s);
	if(knh_String_isASCII(sfp[0].s)) {
		size_t offset = IS_NULL(sfp[1].o) ? 0 : knh_array_index(ctx, p_int(sfp[1]), base.len);
		if(IS_NULL(sfp[2].o)) {
			KNH_RETURN(ctx, sfp, new_String(ctx, knh_bytes_last(base, offset), sfp[0].s));
		}
		else {
			knh_bytes_t sub = knh_bytes_offlen(base, offset, knh_array_index(ctx, p_int(sfp[2]), base.len - offset + 1 ));
			KNH_RETURN(ctx, sfp, new_String(ctx, sub, sfp[0].s));
		}
	}
	else {
		// multibytes
		size_t mlen = knh_bytes_mlen(base);
		size_t offset = IS_NULL(sfp[1].o) ? 0 : knh_array_index(ctx, p_int(sfp[1]), mlen);
		if(IS_NULL(sfp[2].o)) {
			KNH_RETURN(ctx, sfp, new_String(ctx, knh_bytes_last(base, offset), sfp[0].s));
		}
		else {
			knh_bytes_t sub = knh_bytes_mofflen(base, offset, p_int(sfp[2]));
			KNH_RETURN(ctx, sfp, new_String(ctx, sub, sfp[0].s));
		}
	}
}

/* ======================================================================== */

/* ------------------------------------------------------------------------ */
/* @func String:+ */

size_t bconv__toLower(Ctx *ctx, BytesConv *o, knh_bytes_t t, knh_Bytes_t *ba)
{
	size_t i;
	for(i = 0; i < t.len; i++) {
		if(isupper(t.buf[i])) {
			knh_Bytes_putc(ctx, ba, tolower(t.buf[i]));
		}
		else {
			knh_Bytes_putc(ctx, ba, t.buf[i]);
		}
	}
	return t.len;
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String! String.toLower() */

static METHOD knh__String_toLower(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, new_String__fbcnv(ctx, sfp[0].s, bconv__toLower, (BytesConv*)KNH_NULL));
}

/* ------------------------------------------------------------------------ */
/* @func String:+ */

size_t bconv__toUpper(Ctx *ctx, BytesConv *o, knh_bytes_t t, knh_Bytes_t *ba)
{
	size_t i;
	for(i = 0; i < t.len; i++) {
		if(islower(t.buf[i])) {
			knh_Bytes_putc(ctx, ba, toupper(t.buf[i]));
		}
		else {
			knh_Bytes_putc(ctx, ba, t.buf[i]);
		}
	}
	return t.len;
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String! String.toUpper() */

static METHOD knh__String_toUpper(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, new_String__fbcnv(ctx, sfp[0].s, bconv__toUpper, (BytesConv*)KNH_NULL));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String! String.trim() */

static METHOD knh__String_trim(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t t = knh_String_tobytes(sfp[0].s);
	size_t i, s = 0;
	for(i = 0; i < t.len; i++) {
		if(!isspace(t.buf[i])) break;
	}
	s = i;
	for(i = t.len - 1; s < i; i--) {
		if(!isspace(t.buf[i])) break;
	}
	if(i - s + 1 == t.len) {
		KNH_RETURN(ctx, sfp, sfp[0].o)
	}
	t.buf = t.buf + s;
	t.len = i - s + 1;
	KNH_RETURN(ctx, sfp, new_String(ctx, t, NULL));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String[] String.split(Any delim) */

static METHOD knh__String_split(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_Regex(sfp[1].o)) {
		KNH_RETURN(ctx, sfp, knh_Regex_split(ctx, (Regex*)sfp[1].o, sfp[0].s));
	}
	else if(IS_String(sfp[1].o)) {
		int trim = 0;
		knh_bytes_t base = knh_String_tobytes(sfp[0].s);
		knh_bytes_t delim = knh_String_tobytes(sfp[1].s);
		if(delim.len > 1 && delim.buf[delim.len-1] == ' ') {
			trim = 1;
			delim.len -=1;
		}
		if(delim.len == 0) {
			if(knh_String_isASCII(sfp[0].s)) {
				size_t i, n = base.len;
				Array *a = new_Array(ctx, CLASS_String, n);
				knh_bytes_t sub = knh_String_tobytes(sfp[0].s);
				for(i = 0; i < n; i++) {
					sub.buf = base.buf + i;
					sub.len = 1;
					knh_Array_add(ctx, a, UP(new_String(ctx, sub, sfp[0].s)));
				}
				KNH_RETURN(ctx, sfp, a);
			}
			else {
				size_t i, n = knh_bytes_mlen(base);
				Array *a = new_Array(ctx, CLASS_String, n);
				for(i = 0; i < n; i++) {
					knh_bytes_t sub = knh_bytes_mofflen(base, n, 1);
					knh_Array_add(ctx, a, UP(new_String(ctx, sub, sfp[0].s)));
				}
				KNH_RETURN(ctx, sfp, a);
			}
		}else {
			Array *a = new_Array(ctx, CLASS_String, 8);
			while(1) {
				knh_index_t loc = knh_bytes_indexOf(base, delim);
				if(loc == -1) {
					if(knh_bytes_equals(base, knh_String_tobytes(sfp[0].s))) {
						knh_Array_add(ctx, a, UP(sfp[0].s));
					}
					else {
						knh_Array_add(ctx, a, UP(new_String(ctx, base, sfp[0].s)));
					}
					break;
				}
				if(loc == 0) {
					knh_Array_add(ctx, a, UP(TS_EMPTY));
				}
				else {
					knh_Array_add(ctx, a, UP(new_String(ctx, knh_bytes_first(base, loc), sfp[0].s)));
				}
				base.buf = base.buf + loc + delim.len;
				base.len = base.len - loc - delim.len;
				if(trim) {
					while(isspace(base.buf[0])) {
						base.buf = base.buf + 1;
						base.len = base.len - 1;
					}
				}
			}
			KNH_RETURN(ctx, sfp, a);
		}
	}
	else {  /* sfp[1].o == null */
		knh_bytes_t base = knh_String_tobytes(sfp[0].s);
		Array *a = new_Array(ctx, CLASS_String, 8);
		size_t loc;
		while(1) {
			while(isspace(base.buf[0])) {
				base.buf = base.buf + 1;
				base.len = base.len - 1;
			}
			if(base.buf[0] == 0) break;
			for(loc = 0; loc < base.len; loc++) {
				int ch = base.buf[loc];
				if(isspace(ch)) break;
			}
			if(loc == base.len) {
				if(knh_bytes_equals(base, knh_String_tobytes(sfp[0].s))) {
					knh_Array_add(ctx, a, UP(sfp[0].s));
				}
				else {
					knh_Array_add(ctx, a, UP(new_String(ctx, base, sfp[0].s)));
				}
				break;
			} else {
				knh_Array_add(ctx, a, UP(new_String(ctx, knh_bytes_first(base, loc), NULL /*sfp[0].s*/)));
			}
			base.buf = base.buf + loc;
			base.len = base.len - loc;
		}

		KNH_RETURN(ctx, sfp, a);
	}
}

/* ======================================================================== */
/* [movabletext] */

/* @method void String.%s(OutputStream w, String m) */

static
void knh_String__s(Ctx *ctx, String *b, OutputStream *w, String *m)
{
	knh_print(ctx, w, knh_String_tobytes(b));
}

/* ------------------------------------------------------------------------ */
/* @method void String.%k(OutputStream w, String m) */

static
void knh_String__k(Ctx *ctx, String *o, OutputStream *w, String *m)
{
	int quote = '\'';
	if(knh_Object_cid(o) == CLASS_String) quote = '"';
	knh_putc(ctx, w, quote);
	knh_bytes_t t = knh_String_tobytes(o);
	knh_bytes_t sub = t;
	size_t i, s = 0;
	for(i = 0; i < o->size; i++) {
		switch(t.buf[i]) {
			case '\t' :
				sub.buf = t.buf + s;
				sub.len = i - s;
				knh_print(ctx, w, sub); s = i + 1;
				knh_putc(ctx, w, '\\'); knh_putc(ctx, w, 't'); break ;
			case '\n' :
				sub.buf = t.buf + s;
				sub.len = i - s;
				knh_print(ctx, w, sub); s = i + 1;
				knh_putc(ctx, w, '\\'); knh_putc(ctx, w, 'n'); break ;
			case '\r' :
				sub.buf = t.buf + s;
				sub.len = i - s;
				knh_print(ctx, w, sub); s = i + 1;
				knh_putc(ctx, w, '\\'); knh_putc(ctx, w, 'r'); break ;
			case '\\' :
				sub.buf = t.buf + s;
				sub.len = i - s;
				knh_print(ctx, w, sub); s = i + 1;
				knh_putc(ctx, w, '\\'); knh_putc(ctx, w, '\\'); break ;
			default:
				if(t.buf[i] == quote) {
					sub.buf = t.buf + s;
					sub.len = i - s;
					knh_print(ctx, w, sub); s = i + 1;
					knh_putc(ctx, w, '\\'); knh_putc(ctx, w, quote);
				}
		}
	}
	if (s < t.len) {
		sub.buf = t.buf + s;
		sub.len = t.len - s;
		knh_print(ctx, w, sub);
	}
	knh_putc(ctx, w, quote);
}

#endif/*KNH_CC_METHODAPI*/

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
