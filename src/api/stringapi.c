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

#ifdef KNH_CC_METHODAPI

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! String.equals(String! s) */

static METHOD knh__String_equals(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp,
		((sfp[0].s)->size == (sfp[1].s)->size &&
		knh_bytes_strcmp(knh_String_tobytes(sfp[0].s), knh_String_tobytes(sfp[1].s)) == 0));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! String.equals:IgnoreCase(String! s) */

static METHOD knh__String_equals__IgnoreCase(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp,
		((sfp[0].s)->size == (sfp[1].s)->size &&
		knh_bytes_strcasecmp(knh_String_tobytes(sfp[0].s), knh_String_tobytes(sfp[1].s))== 0));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! String.startsWith(String! s) */

static METHOD knh__String_startsWith(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_bytes_startsWith(knh_String_tobytes(sfp[0].s), knh_String_tobytes(sfp[1].s)));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! String.startsWith:IgnoreCase(String! s) */

static METHOD knh__String_startsWith__IgnoreCase(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t base = knh_String_tobytes(sfp[0].s);
	knh_bytes_t expr = knh_String_tobytes(sfp[1].s);
	int res = 0;
	if(expr.len < base.len) {
		base = knh_bytes_first(base, expr.len);
		res = (knh_bytes_strcasecmp(base, expr) == 0);
	}
	KNH_RETURN_Boolean(ctx, sfp, res);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! String.endsWith(String! s) */

static METHOD knh__String_endsWith(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_bytes_endsWith(knh_String_tobytes(sfp[0].s), knh_String_tobytes(sfp[1].s)));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! String.endsWith:IgnoreCase(String! s) */

static METHOD knh__String_endsWith__IgnoreCase(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t base = knh_String_tobytes(sfp[0].s);
	knh_bytes_t expr = knh_String_tobytes(sfp[1].s);
	int res = 0;
	if(expr.len < base.len) {
		base = knh_bytes_last(base, base.len - expr.len);
		res = (knh_bytes_strcasecmp(base, expr) == 0);
	}
	KNH_RETURN_Boolean(ctx, sfp, res);
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
/* @method[CONST] Int! String.indexOf:IgnoreCase(String! s) */

static METHOD knh__String_indexOf__IgnoreCase(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t base = knh_String_tobytes(sfp[0].s);
	knh_bytes_t delim = knh_String_tobytes(sfp[1].s);
	knh_intptr_t loc = base.len - delim.len;
	for(loc = 0; loc < base.len - delim.len; loc++) {
		if(base.buf[loc] != delim.buf[loc]) continue;
		knh_bytes_t sub = knh_bytes_offlen(base, loc, delim.len);
		if(knh_bytes_strcasecmp(sub, delim) == 0) break;
	}
	if(loc == base.len - delim.len) loc = -1;
	if (loc >= 0 && !knh_String_isASCII(sfp[0].s)) {
		base.len = (size_t)loc;
		loc = knh_bytes_mlen(base);
	}
	KNH_RETURN_Int(ctx, sfp, loc);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Int! String.lastIndexOf(String! s) */

static METHOD knh__String_lastIndexOf(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t base = knh_String_tobytes(sfp[0].s);
	knh_bytes_t delim = knh_String_tobytes(sfp[1].s);
	knh_intptr_t loc = base.len - delim.len;
	for(; loc >= 0; loc--) {
		if(base.buf[loc] != delim.buf[loc]) continue;
		knh_bytes_t sub = knh_bytes_offlen(base, loc, delim.len);
		if(knh_bytes_strcmp(sub, delim) == 0) break;
	}
	if (loc >= 0 && !knh_String_isASCII(sfp[0].s)) {
		base.len = (size_t)loc;
		loc = knh_bytes_mlen(base);
	}
	KNH_RETURN_Int(ctx, sfp, loc);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] Int! String.lastIndexOf:IgnoreCase(String! s) */

static METHOD knh__String_lastIndexOf__IgnoreCase(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t base = knh_String_tobytes(sfp[0].s);
	knh_bytes_t delim = knh_String_tobytes(sfp[1].s);
	knh_intptr_t loc = base.len - delim.len;
	for(; loc >= 0; loc--) {
		if(base.buf[loc] != delim.buf[loc]) continue;
		knh_bytes_t sub = knh_bytes_offlen(base, loc, delim.len);
		if(knh_bytes_strcasecmp(sub, delim) == 0) break;
	}
	if (loc >= 0 && !knh_String_isASCII(sfp[0].s)) {
		base.len = (size_t)loc;
		loc = knh_bytes_mlen(base);
	}
	KNH_RETURN_Int(ctx, sfp, loc);
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
	knh_sfp_t *esp = KNH_LOCAL(ctx);
	if(IS_bString(sfp[0].o)) {
		knh_Bytes_write(ctx, cwb.ba, knh_String_tobytes(sfp[0].s));
	}
	else {
		KNH_SETv(ctx, esp[1].o, sfp[0].o); esp[1].data = sfp[0].data;
		knh_esp1_format(ctx, METHODN__s, cwb.w, KNH_NULL);
	}
	if(IS_bString(sfp[1].o)) {
		knh_Bytes_write(ctx, cwb.ba, knh_String_tobytes(sfp[1].s));
	}
	else {
		KNH_ASSERT(esp == ctx->esp);
		KNH_SETv(ctx, esp[1].o, sfp[1].o); esp[1].data = sfp[1].data;
		knh_esp1_format(ctx, METHODN__s, cwb.w, KNH_NULL);
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
/* @method[VARARGS] String! String.format(Any v) */

static METHOD knh__String_format(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t fmt = knh_String_tobytes(sfp[0].s);
	knh_sfp_t *param = sfp + 1;
	int ac = knh_sfp_argc(ctx, param);
	knh_bytes_t mt, expr, next;

	if(!knh_bytes_findMT(ctx, fmt, &mt, &expr, &next)) {
		KNH_RETURN(ctx, sfp, sfp[0].s);
	}

	knh_cwb_t cwb = new_cwb(ctx);
	int count;
	for(count = 0; ; count++) {
		if(mt.buf > fmt.buf + 1) {
			fmt.len = (mt.buf - fmt.buf) - 1;
			knh_Bytes_write(ctx, cwb.ba, fmt);
		}
		int index = count;
		if(expr.len > 0) {
			knh_int_t num;
			if(knh_bytes_parseint(expr, &num)) {
				index = (int)num;
			}
		}
		if(0 <= index && index < ac) {
			knh_sfp_t *esp = KNH_LOCAL(ctx);
			mt.buf = mt.buf - 1; mt.len++;   /* 's' == > '%s' */
			KNH_SETv(ctx, esp[1].o, param[index].o); esp[1].data = param[index].data;
			Object *m = KNH_NULL;
			if(knh_bytes_isOptionalMT(mt)) m = UP(new_String(ctx, mt, NULL));
			knh_methodn_t mn = konoha_getMethodName(ctx, mt, METHODN__empty);
			knh_esp1_format(ctx, mn, cwb.w, m);
		}
		else {
			if(knh_Context_isDebug(ctx)) {
				KNH_THROW_OUTOFINDEX(ctx, index, ac);
			}
		}
		fmt.buf = next.buf; fmt.len = next.len;
		if(!knh_bytes_findMT(ctx, fmt, &mt, &expr, &next)) {
			break;
		}
	}
	if(fmt.len > 0) {
		knh_Bytes_write(ctx, cwb.ba, fmt);
	}
	KNH_RETURN(ctx, sfp, new_StringX__cwb(ctx, knh_Object_cid(sfp[0].o), cwb));
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
	int search_flag= 0, ch = target.buf[0], i;

	if (base.len == 0 || target.len == 0) KNH_RETURN(ctx, sfp, sfp[0].o);
	for(i = 0; i < base.len - target.len+1; i++) {
		if(base.buf[i] == ch && knh_bytes_equals_(base, i, target)) {
		    knh_Bytes_write(ctx, cwb.ba, alt);
			i += target.len - 1;
			search_flag = 1;
		}else {
			knh_Bytes_putc(ctx, cwb.ba, base.buf[i]);
		}
	}
	if(search_flag == 0) {
		KNH_RETURN(ctx, sfp, sfp[0].o);
	}
	else {
		knh_bytes_t leftover = {base.buf + i, base.len - i};
		knh_Bytes_write(ctx, cwb.ba, leftover);
		KNH_RETURN(ctx, sfp, new_String__cwb(ctx, cwb));
	}
}

/* ======================================================================== */

/* ------------------------------------------------------------------------ */
/* @method[CONST] Boolean! String.opHas(String! s) */

static METHOD knh__String_opHas(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_bytes_indexOf(knh_String_tobytes(sfp[0].s), knh_String_tobytes(sfp[1].s)) != -1);
}

/* ------------------------------------------------------------------------ */
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
/* @method[CONST] Int! String.getChar(Int n) */

static METHOD knh__String_getChar(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t base = knh_String_tobytes(sfp[0].s);
	knh_intptr_t index = IS_NULL(sfp[1].o) ? 0 : (knh_intptr_t)sfp[1].ivalue;
	if(knh_String_isASCII(sfp[0].s)) {
		size_t n = knh_array_index(ctx, index, knh_String_strlen(sfp[0].s));
		KNH_RETURN_Int(ctx, sfp, knh_uchar_toucs4(&base.buf[n]));
	}
	else {
		size_t off = knh_array_index(ctx, index, knh_bytes_mlen(base));
		knh_bytes_t sub = knh_bytes_mofflen(base, off, 1);
		KNH_RETURN_Int(ctx, sfp, knh_uchar_toucs4(&sub.buf[0]));
	}
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String! String.substring(Int offset, Int len) */

static METHOD knh__String_substring(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t base = knh_String_tobytes(sfp[0].s);
	knh_bytes_t sub;
	if(knh_String_isASCII(sfp[0].s)) {
		size_t offset = IS_NULL(sfp[1].o) ? 0 : knh_array_index(ctx, sfp[1].ivalue, base.len);
		sub = knh_bytes_last(base, offset);
		if(IS_NOTNULL(sfp[2].o)) {
			size_t len = (size_t)sfp[2].ivalue;
			if(len < sub.len) sub = knh_bytes_first(sub, len);
		}
	}
	else { // multibytes
		size_t mlen = knh_bytes_mlen(base);
		size_t offset = IS_NULL(sfp[1].o) ? 0 : knh_array_index(ctx, sfp[1].ivalue, mlen);
		size_t length = IS_NULL(sfp[1].o) ? (mlen - offset) : (size_t)sfp[2].ivalue;
		sub = knh_bytes_mofflen(base, offset, length);
	}

	String *s;
	if(sub.len == 0) {
		s = TS_EMPTY;
	}
	else if(sub.len == base.len) {
		s = sfp[0].s;
	}
	else {
		s = new_String(ctx, sub, sfp[0].s);
	}
	KNH_RETURN(ctx, sfp, s);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String! String.opOffset(Int offset, Int len) */

static METHOD knh__String_opOffset(Ctx *ctx, knh_sfp_t *sfp)
{
	knh__String_substring(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String! String.opSubset(Int s, Int e) */

static METHOD knh__String_opSubset(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_NOTNULL(sfp[2].o)) {
		size_t offset = IS_NULL(sfp[1].o) ? 0 : (size_t)sfp[1].ivalue;
		sfp[2].ivalue = sfp[2].ivalue - offset;
	}
	knh__String_substring(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String! String.opSubsete(Int s, Int e) */

static METHOD knh__String_opSubsete(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_NOTNULL(sfp[2].o)) {
		size_t offset = IS_NULL(sfp[1].o) ? 0 : (size_t)sfp[1].ivalue;
		sfp[2].ivalue = sfp[2].ivalue - offset + 1;
	}
	knh__String_substring(ctx, sfp);
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
	knh_bytes_t t2 = knh_bytes_trim(t);
	String *s = sfp[0].s;
	if(t.len > t2.len) {
		s = new_String(ctx, t2, s);
	}
	KNH_RETURN(ctx, sfp, s);
}

/* ------------------------------------------------------------------------ */

static Array *knh_String_toCharArray(Ctx *ctx, String *bs, int istrim)
{
	knh_bytes_t base = knh_String_tobytes(bs);
	if(knh_String_isASCII(bs)) {
		size_t i, n = base.len;
		Array *a = new_Array(ctx, CLASS_String, n);
		for(i = 0; i < n; i++) {
			if(istrim && isspace(base.buf[i])) continue;
			knh_bytes_t sub = { base.buf + i, 1};
			knh_Array_add(ctx, a, UP(new_String(ctx, sub, bs)));
		}
		return a;
	}
	else {
		size_t i, n = knh_bytes_mlen(base);
		Array *a = new_Array(ctx, CLASS_String, n);
		for(i = 0; i < n; i++) {
			if(istrim && isspace(base.buf[i])) continue;
			knh_bytes_t sub = knh_bytes_mofflen(base, n, 1);
			knh_Array_add(ctx, a, UP(new_String(ctx, sub, bs)));
		}
		return a;
	}
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String[] String.split(String delim, Int istrim) */

static METHOD knh__String_split(Ctx *ctx, knh_sfp_t *sfp)
{
	Array *a = NULL;
	int istrim = IS_NULL(sfp[2].o) ? 0 : (int)sfp[2].ivalue;
	if(IS_NULL(sfp[1].o)) {
		a = knh_String_toCharArray(ctx, sfp[0].s, istrim);
	}
	else {
		knh_bytes_t delim = knh_String_tobytes(sfp[1].s);
		if(delim.len == 0) {
			a = knh_String_toCharArray(ctx, sfp[0].s, istrim);
		}
		else {
			knh_bytes_t base = knh_String_tobytes(sfp[0].s);
			a = new_Array(ctx, CLASS_String, 8);
			while(1) {
				knh_index_t loc = knh_bytes_indexOf(base, delim);
				if(loc == -1) {
					if(istrim) base = knh_bytes_trim(base);
					knh_Array_add(ctx, a, UP(new_String(ctx, base, sfp[0].s)));
				}
				else if(loc == 0) {
					knh_Array_add(ctx, a, UP(TS_EMPTY));
				}
				else {
					knh_bytes_t t = knh_bytes_first(base, loc);
					if(istrim) t = knh_bytes_trim(t);
					knh_Array_add(ctx, a, UP(new_String(ctx, t, sfp[0].s)));
				}
				base.buf = base.buf + loc + delim.len;
				base.len = base.len - loc - delim.len;
			}
		}
	}
	KNH_ASSERT(a != NULL);
	KNH_RETURN(ctx, sfp, a);
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

/* ------------------------------------------------------------------------ */
/* [Regex] */
/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* @method[CONST] Regex Regex.new(String! pattern, String option) */

static
METHOD knh__Regex_new(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Regex_t *o = (Regex*)sfp[0].o;
	knh_bytes_t p = knh_String_tobytes(sfp[1].s);
	knh_index_t loc = knh_bytes_index(p, ':');
	KNH_SETv(ctx, o->pattern, sfp[1].s);
	if(loc == -1) {
		o->df = knh_System_getRegexDriver(ctx, STEXT("re"));
	}
	else {
		o->df = knh_System_getRegexDriver(ctx, knh_bytes_first(p, loc));
	}
	o->reg = o->df->regmalloc(ctx);
	{
		char *ptn = (char*)(knh_bytes_last(p, loc+1).buf);
		char *opt = IS_NULL(sfp[2].o) ? "" : knh_String_tochar(sfp[2].s);
		o->df->regcomp(ctx, o->reg, ptn, opt);
	}
	KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ------------------------------------------------------------------------ */

static
int knh_String_opMatch(Ctx *ctx, String *o, Regex *re)
{
	char *str = knh_String_tochar(o);
	knh_regmatch_t pmatch[KNH_REGEX_NMATCH_SIZE];
	int res = re->df->regexec(ctx, re->reg, str, KNH_REGEX_NMATCH_SIZE, pmatch, 0);
	return (res == 0);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! String.opMatch(Regex! re) */

static
METHOD knh__String_opMatch(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_String_opMatch(ctx, sfp[0].s, (Regex*)sfp[1].o));
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Regex.opMatch(String! s) */

static
METHOD knh__Regex_opMatch(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_String_opMatch(ctx, sfp[1].s, (Regex*)sfp[0].o));
}

/* ------------------------------------------------------------------------ */

Array *knh_Regex_split(Ctx *ctx, Regex *o, String *s)
{
	char *str = knh_String_tochar(s);
	knh_regmatch_t pmatch[KNH_REGEX_NMATCH_SIZE];
	int res = o->df->regexec(ctx, o->reg, str, KNH_REGEX_NMATCH_SIZE, pmatch, 0);
	if(res == 0) {
		Array *a = new_Array(ctx, CLASS_String, KNH_REGEX_NMATCH_SIZE);
		knh_bytes_t sub = knh_String_tobytes(s);
		int i;
		for(i = 1; i < KNH_REGEX_NMATCH_SIZE; i++) {
			if(pmatch[i].rm_so == -1) break;
			//DBG_P("[%d], rm_so=%d, rm_eo=%d", i, pmatch[i].rm_so, pmatch[i].rm_eo);
			sub.buf = (knh_uchar_t*)str + pmatch[i].rm_so;
			sub.len = pmatch[i].rm_eo - pmatch[i].rm_so;
			knh_Array_add(ctx, a, UP(new_String(ctx, sub, s)));
		}
		return a;
	}
	else {
		return (Array*)konoha_getClassDefaultValue(ctx, ACLASS_String);
		//return (Array*)KNH_NULL;
	}
}

/* ------------------------------------------------------------------------ */
/* @method[CONST] String[] String.match(Regex pattern) */

static METHOD knh__String_match(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, knh_Regex_split(ctx, (Regex*)sfp[1].o, sfp[0].s));
}

/* ======================================================================== */
/* [movabletext] */

/* @method void Regex.%s(OutputStream w, String m) */

void knh_Regex__s(Ctx *ctx, Regex *o, OutputStream *w, String *m)
{
	knh_putc(ctx, w, '\'');
	knh_write(ctx, w, knh_String_tobytes(o->pattern));
	knh_putc(ctx, w, '\'');
}

/* ------------------------------------------------------------------------ */

#endif/*KNH_CC_METHODAPI*/

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
