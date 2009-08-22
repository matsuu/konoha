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

#ifdef KNH_CC_METHODAPI

void knh_KLRCode__dumpmtd(Ctx *ctx, KLRCode* o, OutputStream *w, Method *mtd);

/* ======================================================================== */
/* [%empty] */

/* ------------------------------------------------------------------------ */
/* @method void Object.%empty(OutputStream w, String m) */

static
void knh_Object__empty(Ctx *ctx, Object *o, OutputStream *w, String *m)
{
	DBG_P("%%empty(%s)", CLASSNo(o));
}

/* ======================================================================== */
/* [%s] */

/* ------------------------------------------------------------------------ */
/* @method void Object.%s(OutputStream w, String m) */

static
void knh_Object__s(Ctx *ctx, Object *b, OutputStream *w, String *m)
{
	if(IS_NULL(b)) {
		knh_write(ctx, w, STEXT("null"));
	}
	else {
		knh_write_char(ctx,w, CLASSN(knh_Object_cid(b)));
		knh_write(ctx,w, STEXT(":"));
		knh_write__p(ctx,w, (void*)b);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Boolean.%s(OutputStream w, String m) */

static METHOD knh__Boolean__s(Ctx *ctx, knh_sfp_t *sfp)
{
	if(p_bool(sfp[0])) {
		knh_write(ctx, sfp[1].w, knh_String_tobytes(TS_true));
	}
	else {
		knh_write(ctx, sfp[1].w, knh_String_tobytes(TS_false));
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%s(OutputStream w, String m) */

static METHOD knh__Int__s(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_write_ifmt(ctx, sfp[1].w, KNH_INT_FMT, sfp[0].ivalue);
}

/* ------------------------------------------------------------------------ */
/* @method void String.%s(OutputStream w, String m) */

static
void knh_String__s(Ctx *ctx, String *b, OutputStream *w, String *m)
{
	knh_print(ctx, w, knh_String_tobytes(b));
}

/* ------------------------------------------------------------------------ */
/* @method void Regex.%s(OutputStream w, String m) */

void knh_Regex__s(Ctx *ctx, Regex *o, OutputStream *w, String *m)
{
	knh_putc(ctx, w, '\'');
	knh_write(ctx, w, knh_String_tobytes(o->pattern));
	knh_putc(ctx, w, '\'');
}

/* ------------------------------------------------------------------------ */
/* @method void Class.%s(OutputStream w, String m) */

static
void knh_Class__s(Ctx *ctx, Class *o, OutputStream *w, String *m)
{
	knh_write_ltype(ctx, w, o->cid);
}

/* ------------------------------------------------------------------------ */
/* @method void Method.%s(OutputStream w, String m) */

static
void knh_Method__s(Ctx *ctx, Method *o, OutputStream *w, String *m)
{
	knh_write_char(ctx, w, CTXCLASSN(DP(o)->cid));
	knh_putc(ctx, w, '.');
	knh_write_mn(ctx, w, DP(o)->mn);
}

/* ------------------------------------------------------------------------ */
/* @method void Exception.%s(OutputStream w, String m) */

static
void knh_Exception__s(Ctx *ctx, Exception *o, OutputStream *w, String *m)
{
	KNH_ASSERT(IS_Exception(o));
	knh_write_char(ctx, w, EXPTN(DP(o)->eid));
	knh_write_char(ctx, w, "!!");
}

/* ======================================================================== */
/* [%k] */

/* ------------------------------------------------------------------------ */
/* @method void Object.%k(OutputStream w, String m) */

static
void knh_Object__k(Ctx *ctx, Object *o, OutputStream *w, String *m)
{
	if(knh_Object_isUndefined(o)) {
		knh_write(ctx, w, STEXT("undefined"));
	}
	else if(IS_NULL(o)) {
		DBG2_ABORT();
		knh_write(ctx, w, STEXT("null"));
	}
	else if(o->h.cid == CLASS_Object || o->h.bcid != CLASS_Object) {
		knh_format(ctx, w, METHODN__s, o, KNH_NULL);
	}
	else if(knh_stack_isRecuriveFormatting(ctx, ctx->esp - 3, UP(o), w, knh_Object__k)) {
		knh_write_dots(ctx, w);
	}
	else {
		size_t bsize = ctx->share->ClassTable[o->h.cid].bsize;
		knh_write_cid(ctx, w, o->h.cid);
		if(bsize > 0) {
			size_t i;
			Object **v = (Object**)o->ref;
			knh_putc(ctx, w, '{');
			for(i = 0; i < bsize; i++) {
				knh_cfield_t *cf = knh_Class_fieldAt(ctx, knh_Object_cid(o), i);
				if(cf->fn == FIELDN_NONAME) break;
				if(cf->fn == FIELDN_register) continue;
				if(i > 0) {
					knh_write_delim(ctx, w);
				}
				knh_write_fn(ctx, w, cf->fn);
				knh_write(ctx, w, STEXT(": "));
#ifdef KNH_USING_UNBOXFIELD
				if(IS_ubxint(cf->type)) {
					knh_int_t *data = (knh_int_t*)(v + i);
					knh_write_ifmt(ctx, w, KNH_INT_FMT, data[0]);
					continue;
				}
				else if(IS_ubxfloat(cf->type)) {
					knh_float_t *data = (knh_float_t*)(v + i);
					knh_write_ffmt(ctx, w, KNH_FLOAT_FMT, data[0]);
					continue;
				}
				else if(IS_ubxboolean(cf->type)) {
					knh_bool_t *data = (knh_bool_t*)(v + i);
					if(data[0]) knh_write(ctx, w, STEXT("true"));
					else knh_write(ctx, w, STEXT("false"));
					continue;
				}
#endif
				knh_format(ctx, w, METHODN__k, v[i], KNH_NULL);
			}
			knh_putc(ctx, w, '}');
		}
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Boolean.%k(OutputStream w, String m) */

static METHOD knh__Boolean__k(Ctx *ctx, knh_sfp_t *sfp)
{
	if(p_bool(sfp[0])) {
		knh_write(ctx, sfp[1].w, knh_String_tobytes(TS_true));
	}
	else {
		knh_write(ctx, sfp[1].w, knh_String_tobytes(TS_false));
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%k(OutputStream w, String m) */

static METHOD knh__Int__k(Ctx *ctx, knh_sfp_t *sfp)
{
	ClassSpec *u = knh_getClassSpec(ctx, knh_Object_cid(sfp[0].o));
	knh_write_intx(ctx, sfp[1].w, u, sfp[0].ivalue);
}

/* ------------------------------------------------------------------------ */
/* @method void Float.%k(OutputStream w, String m) */

static METHOD knh__Float__k(Ctx *ctx, knh_sfp_t *sfp)
{
	ClassSpec *u = knh_getClassSpec(ctx, knh_Object_cid(sfp[0].o));
	knh_write_floatx(ctx, sfp[1].w, u, p_float(sfp[0]));
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
/* @method void Bytes.%k(OutputStream w, String m) */

static
void knh_Bytes__k(Ctx *ctx, Bytes *o, OutputStream *w, String *m)
{
	knh_printf(ctx, w, "byte[%d]", (o)->size);
}

/* ------------------------------------------------------------------------ */
/* @method void Iterator.%k(OutputStream w, String m) */

static
void knh_Iterator__k(Ctx *ctx, Iterator *it, OutputStream *w, String *m)
{
	size_t c = 0;
	knh_sfp_t *lsfp = KNH_LOCAL(ctx);
	KNH_MOV(ctx, lsfp[0].o, it);
	KNH_SHIFTESP(ctx, lsfp+3);
	while(it->fnext_1(ctx, lsfp, 2)) {
		if(c > 0) {
			knh_write_EOL(ctx,w);
		}
		KNH_SHIFTESP(ctx, lsfp+1);
		knh_esp1_format(ctx, METHODN__k, w, KNH_NULL);
		c++;
		KNH_SHIFTESP(ctx, lsfp+3);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Pair.%k(OutputStream w, String m) */

static
void knh_Pair__k(Ctx *ctx, knh_Pair_t *o, OutputStream *w, String *m)
{
	knh_putc(ctx, w, '(');
	if(knh_stack_isRecuriveFormatting(ctx, ctx->esp - 3, UP(o), w, knh_Pair__k)) {
		knh_write_dots(ctx,w);
	}
	else {
		knh_format(ctx, w, METHODN__k, o->first, KNH_NULL);
		knh_write_delim(ctx,w);
		knh_format(ctx, w, METHODN__k, o->second, KNH_NULL);
	}
	knh_putc(ctx, w, ')');
}

/* ------------------------------------------------------------------------ */
/* @method void Tuple.%k(OutputStream w, String m) */

static
void knh_Tuple__k(Ctx *ctx, knh_Tuple_t *o, OutputStream *w, String *m)
{
	knh_putc(ctx, w, '(');
	if(knh_stack_isRecuriveFormatting(ctx, ctx->esp - 3, UP(o), w, knh_Tuple__k)) {
		knh_write_dots(ctx,w);
	}
	else if(knh_Tuple_isTriple(o)) {
		knh_format(ctx, w, METHODN__k, o->first, KNH_NULL);
		knh_write_delim(ctx,w);
		knh_format(ctx, w, METHODN__k, o->second, KNH_NULL);
		knh_write_delim(ctx,w);
		knh_format(ctx, w, METHODN__k, o->third, KNH_NULL);
	}
	else {
		size_t i, c = 0;
		for(i = 0; o->size; i++) {
			if(c > 0) {
				knh_write_delim(ctx,w);
			}
			knh_format(ctx, w, METHODN__k, o->list[c], KNH_NULL);
			c++;
		}
	}
	knh_putc(ctx, w, ')');
}

/* ------------------------------------------------------------------------ */
/* @method void Range.%k(OutputStream w, String m) */

static
void knh_Range__k(Ctx *ctx, knh_Range_t *o, OutputStream *w, String *m)
{
	knh_putc(ctx, w, '(');
	knh_format(ctx, w, METHODN__k, o->start, KNH_NULL);
	if(knh_Range_isInclusive(o)) {
		knh_write(ctx, w, STEXT(" to "));
	}
	else {
		knh_write(ctx, w, STEXT(" until "));
	}
	knh_format(ctx, w, METHODN__k, o->end, KNH_NULL);
	knh_putc(ctx, w, ')');
}

/* ------------------------------------------------------------------------ */
/* @method void Array.%k(OutputStream w, String m) */

static
void knh_Array__k(Ctx *ctx, Array *o, OutputStream *w, String *m)
{
	knh_putc(ctx, w, '[');
	if(knh_stack_isRecuriveFormatting(ctx, ctx->esp - 3, UP(o), w, knh_Array__k)) {
		knh_write_dots(ctx,w);
	}
	else {
		size_t c;
		for(c = 0; c < o->size; c++) {
			if(c > 0) {
				knh_write_delim(ctx,w);
			}
			knh_format(ctx, w, METHODN__k, o->list[c], KNH_NULL);
		}
	}
	knh_putc(ctx, w, ']');
}

/* ------------------------------------------------------------------------ */
/* @method void IArray.%k(OutputStream w, String m) */

static
void knh_IArray__k(Ctx *ctx, IArray *o, OutputStream *w, String *m)
{
	size_t c;
	knh_putc(ctx, w, '[');
	for(c = 0; c < o->size; c++) {
		if(c > 0) {
			knh_write_delim(ctx,w);
		}
		knh_write_ifmt(ctx, w, KNH_INT_FMT, o->ilist[c]);
	}
	knh_putc(ctx, w, ']');
}

/* ------------------------------------------------------------------------ */
/* @method void FArray.%k(OutputStream w, String m) */

static
void knh_FArray__k(Ctx *ctx, FArray *o, OutputStream *w, String *m)
{
	knh_putc(ctx, w, '[');
	size_t c;
	for(c = 0; c < o->size; c++) {
		if(c > 0) {
			knh_write_delim(ctx,w);
		}
		knh_write_ffmt(ctx, w, KNH_FLOAT_FMT, o->flist[c]);
	}
	knh_putc(ctx, w, ']');
}

/* ------------------------------------------------------------------------ */
/* @method void DictMap.%k(OutputStream w, String m) */

static
void knh_DictMap__k(Ctx *ctx, DictMap *o, OutputStream *w, String *m)
{
	knh_DictMap_sort(o);
	knh_putc(ctx, w, '{');
	size_t c;
	for(c = 0; c < o->size; c++) {
		if(c > 0) {
			knh_write_delim(ctx, w);
		}
		knh_write(ctx, w, knh_String_tobytes(o->list[c].key));
		knh_putc(ctx, w, ':');	knh_putc(ctx, w, ' ');
		knh_format(ctx, w, METHODN__k, o->list[c].value, KNH_NULL);
	}
	knh_putc(ctx, w, '}');
}

/* ------------------------------------------------------------------------ */
/* @method void DictSet.%k(OutputStream w, String m) */

static
void knh_DictSet__k(Ctx *ctx, DictSet *o, OutputStream *w, String *m)
{
	knh_DictSet_sort(o);
	knh_putc(ctx, w, '{');
	size_t c;
	for(c = 0; c < o->size; c++) {
		if(c > 0) {
			knh_write_delim(ctx, w);
		}
		knh_write(ctx, w, knh_String_tobytes(o->list[c].key));
//		knh_putc(ctx, w, ':');	knh_putc(ctx, w, ' ');
//		knh_format(ctx, w, static METHODN__k, o->list[c].value, KNH_NULL);
	}
	knh_putc(ctx, w, '}');
}

/* ------------------------------------------------------------------------ */
/* @method void DictIdx.%k(OutputStream w, String m) */

void knh_DictIdx__k(Ctx *ctx, DictIdx *o, OutputStream *w, String *m)
{
	knh_Array__k(ctx, o->terms, w, m);
}

/* ------------------------------------------------------------------------ */
/* @method void HashMap.%k(OutputStream w, String m) */

void knh_HashMap__k(Ctx *ctx, knh_Hash_t *o, OutputStream *w, String *m)
{
	size_t pos = 0, c = 0;
	size_t max = (KNH_HASH_TABLESIZE / o->hashop->size) * DP(o)->tables_size;
	knh_putc(ctx, w, '{');
	while(pos < max) {
		knh_hashentry_t *e = knh_hashentry_at((knh_Hash_t*)o, pos);
		if(e != NULL) {
			if(c > 0) {
				knh_write_delim(ctx,w);
			}
			knh_format(ctx, w, METHODN__k, e->key, KNH_NULL);
			knh_putc(ctx, w, ':');
			knh_putc(ctx, w, ' ');
			knh_format(ctx, w, METHODN__k, e->value, KNH_NULL);
			c++;
		}
		pos++;
	}
	knh_putc(ctx, w, '}');
}

/* ------------------------------------------------------------------------ */
/* @method void Class.%k(OutputStream w, String m) */

static
void knh_Class__k(Ctx *ctx, Class *o, OutputStream *w, String *m)
{
	knh_write_cid(ctx, w, o->cid);
}

/* ------------------------------------------------------------------------ */
/* @method void Method.%k(OutputStream w, String m) */

static
void knh_Method__k(Ctx *ctx, Method *o, OutputStream *w, String *m)
{
	if(knh_Method_isAbstract(o)) {
		knh_write(ctx, w, STEXT("@abstract"));
		knh_putc(ctx, w, ' ');
	}
	if(knh_Method_rztype(o) == TYPE_void) {
		knh_write(ctx, w, knh_String_tobytes(TS_void));
	}else{
		knh_write_type(ctx, w, knh_Method_rztype(o));
	}
	knh_putc(ctx, w, ' ');
	knh_Method__s(ctx, o, w, (String*)KNH_NULL);
	knh_putc(ctx, w, '(');
	size_t i;
	for(i = 0; i < knh_Method_psize(o); i++) {
		if(i > 0) {
			knh_write_delim(ctx, w);
		}
		knh_mparam_t mf = knh_Method_param(o, i);
		knh_write_type(ctx, w, mf.type);
		knh_putc(ctx, w, ' ');
		knh_write(ctx, w, B(FIELDN(mf.fn)));
	}
	if(knh_Method_isVarArgs(o)) {
		knh_write_delim(ctx, w);
		knh_write_dots(ctx, w);
	}
	knh_putc(ctx, w, ')');
}

/* ------------------------------------------------------------------------ */
/* @method void Mapper.%k(OutputStream w, String m) */

static
void knh_Mapper__k(Ctx *ctx, Mapper *o, OutputStream *w, String *m)
{
	knh_write_cid(ctx, w, DP(o)->scid);
	if(knh_Mapper_isTotal(o)) {
		knh_write(ctx, w, STEXT("==>"));
	}else{
		knh_write(ctx, w, STEXT("-->"));
	}
	knh_write_cid(ctx, w, DP(o)->tcid);
}

/* ------------------------------------------------------------------------ */
/* @method void ClassMap.%dump(OutputStream w, String m) */

static
void knh_ClassMap__dump(Ctx *ctx, ClassMap *o, OutputStream *w, String *m)
{
	size_t i;
	for(i = 0; i < DP(o)->size; i++) {
		knh_printf(ctx, w, "[%d]\t", i);
		knh_Mapper__k(ctx, DP(o)->maplist[i], w, m);
		knh_write_EOL(ctx, w);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Exception.%k(OutputStream w, String m) */

static
void knh_Exception__k(Ctx *ctx, Exception *o, OutputStream *w, String *m)
{
	KNH_ASSERT(IS_Exception(o));
	knh_putc(ctx, w, '\'');
	knh_write(ctx, w, knh_String_tobytes(DP(o)->msg));
	knh_putc(ctx, w, '\'');
}

/* ------------------------------------------------------------------------ */
/* @method void InputStream.%k(OutputStream w, String m) */

static
void knh_InputStream__k(Ctx *ctx, InputStream *o, OutputStream *w, String *m)
{
	knh_putc(ctx, w, '\'');
	knh_print(ctx, w, knh_String_tobytes(DP(o)->urn));
	knh_putc(ctx, w, '\'');
}

/* ------------------------------------------------------------------------ */
/* @method void OutputStream.%k(OutputStream w, String m) */

static
void knh_OutputStream__k(Ctx *ctx, OutputStream *o, OutputStream *w, String *m)
{
	knh_putc(ctx, w, '\'');
	knh_print(ctx, w, knh_String_tobytes(DP(o)->urn));
	knh_putc(ctx, w, '\'');
}

/* ------------------------------------------------------------------------ */
/* @method void System.%k(OutputStream w, String m) */

void knh_System__k(Ctx *ctx, System *o, OutputStream *w, String *m)
{
	knh_printf(ctx, w, "Konoha %s(%s) %s (#%d, %s %s)",
		KONOHA_VERSION, KONOHA_XCODE, KONOHA_LICENSE,
		((size_t)KONOHA_BUILDID), __DATE__, __TIME__);
}

/* ------------------------------------------------------------------------ */
/* @method void Script.%k(OutputStream w, String m) */

void knh_Script__k(Ctx *ctx, Script *o, OutputStream *w, String *m)
{
	knh_write(ctx, w, STEXT("<script>"));
}

/* ------------------------------------------------------------------------ */
/* @method void Any.%k(OutputStream w, String m) */

static
void knh_Any__k(Ctx *ctx, knh_Any_t *o, OutputStream *w, String *m)
{
	knh_write(ctx, w, knh_String_tobytes(TS_null));
}

/* ======================================================================== */
/* [dump] */

/* ------------------------------------------------------------------------ */
/* @method void Object.%dump(OutputStream w, String m) */

static
void knh_Object__dump(Ctx *ctx, Object *b, OutputStream *w, String *m)
{
	TODO();
//	knh_class_t cid = knh_Object_cid(b);
//	if(cid < KONOHA_TSTRUCT_SIZE) {
//		knh_format(ctx, w, METHODN__s, b, KNH_NULL);
//		return ;
//	}
//	knh_intptr_t i, c = 0;
//	knh_putc(ctx, w, '[');
//	for(i = 0; i < ClassTable(cid).bsize; i++) {
//		knh_cfield_t *cf = knh_Class_fieldAt(ctx, cid, i);
//		if(cf->fn == FIELDN_NONAME || KNH_FLAG_IS(cf->flag, KNH_FLAG_CFF_HIDDEN)) continue;
//		if(c > 0) {
//			knh_write_delim(ctx, w);
//		}
//		knh_printf(ctx, w, "%s=", /* cf->type, */ FIELDN(cf->fn));
//		Object *v = KNH_FIELDn(b, i);
//		if(IS_bString(v)) {
//			knh_format(ctx, w, METHODN__dump, v, KNH_NULL);
//		}
//		else {
//			knh_format(ctx, w, METHODN__s, v, KNH_NULL);
//		}
//		c++;
//	}
//	knh_putc(ctx, w, ']');
}

/* ------------------------------------------------------------------------ */
/* @method void Bytes.%dump(OutputStream w, String m) */

static
void knh_Bytes__dump(Ctx *ctx, Bytes *o, OutputStream *w, String *m)
{
	size_t i, j, n;
	char buf[40];
	for(j = 0; j * 16 < o->size; j++) {
		knh_snprintf(buf, sizeof(buf), "%08x", (int)(j*16));
		knh_write(ctx, w, B(buf));
		for(i = 0; i < 16; i++) {
			n = j * 16 + i;
			if(n < o->size) {
				knh_snprintf(buf, sizeof(buf), " %2x", (int)o->buf[n]);
				knh_write(ctx, w, B(buf));
			}
			else {
				knh_write(ctx, w, STEXT("   "));
			}
		}
		knh_write(ctx, w, STEXT("    "));
		for(i = 0; i < 16; i++) {
			n = j * 16 + i;
			if(n < o->size && isprint(o->buf[n])) {
				knh_snprintf(buf, sizeof(buf), "%c", (int)o->buf[n]);
				knh_write(ctx, w, B(buf));
			}
			else {
				knh_write(ctx, w, STEXT(" "));
			}
		}
		knh_write_EOL(ctx, w);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void DictSet.%dump(OutputStream w, String m) */

static
void knh_DictSet__dump(Ctx *ctx, DictSet *o, OutputStream *w, String *m)
{
	knh_DictSet_sort(o);
	knh_putc(ctx, w, '{');
	size_t c;
	for(c = 0; c < o->size; c++) {
		if(c > 0) {
			knh_write_delim(ctx, w);
		}
		knh_write(ctx, w, knh_String_tobytes(o->list[c].key));
		knh_putc(ctx, w, ':');	knh_putc(ctx, w, ' ');
		knh_write_dfmt(ctx, w, KNH_INTPTR_FMT, o->list[c].value);
	}
	knh_putc(ctx, w, '}');
}

/* ------------------------------------------------------------------------ */
/* @method void Class.%dump(OutputStream w, String m) */

static
void knh_Class__dump(Ctx *ctx, Class *o, OutputStream *w, String *m)
{
	TODO_THROW(ctx);
}

/* ------------------------------------------------------------------------ */
/* @method void Method.%dump(OutputStream w, String m) */

static
void knh_Method__dump(Ctx *ctx, Method *o, OutputStream *w, String *m)
{
	knh_Method__k(ctx, o, w, m);
	knh_println(ctx, w, STEXT(""));
	if(knh_Method_isObjectCode(o)) {
		if(IS_KLRCode((Object*)DP(o)->code)) {
			knh_KLRCode__dumpmtd(ctx, (KLRCode*)DP(o)->code, w, o);
		}
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Exception.%dump(OutputStream w, String m) */

static
void knh_Exception__dump(Ctx *ctx, Exception *o, OutputStream *w, String *m)
{
	DBG2_ASSERT(IS_Exception(o));
	knh_write_EOL(ctx, w);
	if(DP(o)->line != 0) {
		knh_printf(ctx, w, "[%s:%d] ", DP(o)->file, DP(o)->line);
	}
	knh_write(ctx, w, knh_String_tobytes(DP(o)->msg));
	knh_print(ctx, w, STEXT(" Exception"));
	if(IS_bArray(DP(o)->traces)) {
		size_t i, size = knh_Array_size(DP(o)->traces), c = 0;
		knh_bytes_t prev = STEXT("?");
		for(i = 0; i < size; i++) {
			String *s = (String*)knh_Array_n(DP(o)->traces, i);
			if(knh_String_startsWith(s, prev)) {
				c++;
				continue;
			}
			if(c > 0) {
				knh_printf(ctx, w, "\n    ** called %d times recursively **", c);
				c = 0;
			}
			knh_printf(ctx, w, "\n  at %s", knh_String_tochar(s));
			prev = knh_String_tobytes(s);
			prev = knh_bytes_first(prev, knh_bytes_rindex(prev, '('));
		}
	}
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */
/* @method void System.%dump(OutputStream w, String m) */

void knh_System__dump(Ctx *ctx, System *o, OutputStream *w, String *m)
{
	knh_System__k(ctx, o, w, m);
	knh_write_EOL(ctx, w);
	knh_printf(ctx, w, "[%s] on %s (%d, %s)\n", KONOHA_CC_VERSION, KONOHA_PLATFORM, (knh_intptr_t)(sizeof(void*) * 8), konoha_encoding());
	knh_write_char(ctx, w, "Options:");

#ifdef KNH_FASTMODE
	knh_write_char(ctx, w, " fastmode");
#endif

#ifdef KNH_USING_ICONV
	knh_write_char(ctx, w, " iconv");
#endif
#ifdef KNH_USING_INT32
	knh_write_char(ctx, w, " int32");
#endif
#ifdef KNH_USING_RCGC
	knh_write_char(ctx, w, " refc");
#endif
	knh_write_USING_SQLITE3(ctx, w);
#ifdef KNH_USING_THREAD
	knh_write_char(ctx, w, " thread");
#endif
	knh_write_USING_REGEX(ctx, w);
	knh_printf(ctx, w, " used_memory:%d kb", (knh_intptr_t)(ctx->stat->usedMemorySize / 1024));
	knh_write_EOL(ctx, w);
}

/* ------------------------------------------------------------------------ */
/* @method void Script.%dump(OutputStream w, String m) */

static
void knh_Script__dump(Ctx *ctx, Script *o, OutputStream *w, String *m)
{
	size_t i;
	for(i = 0; i < KNH_SCRIPT_FIELDSIZE; i++) {
		knh_cfield_t *cf = knh_Class_fieldAt(ctx, knh_Object_cid(o), i);
		if(cf == NULL) break;
		if(cf->fn == FIELDN_NONAME) break;
		{
			knh_type_t type = knh_pmztype_totype(ctx, cf->type, knh_Object_cid(o));
			knh_printf(ctx, w, "[%d] %T %s=", i, type, FIELDN(cf->fn));
			knh_format(ctx, w, METHODN__k, o->fields[i], KNH_NULL);
			knh_println(ctx, w, STEXT(""));
		}
	}
}

/* ======================================================================== */
/* [man] */

/* ------------------------------------------------------------------------ */

static
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

/* ------------------------------------------------------------------------ */

static
void knh_ClassMap__man(Ctx *ctx, ClassMap *o, OutputStream *w, knh_class_t cid)
{
	int i;
	int hasCaption = 0, from = 0;
	L_TAIL:;
	knh_ClassMap_sort(ctx, o);
	for(i = 0; i < DP(o)->size; i++) {
		if(hasCaption == 0) {
			knh_write_char(ctx, w, _("Mapper"));
			knh_write_EOL(ctx, w);
			hasCaption = 1;
		}
		if(from == 0) {
			knh_write_TAB(ctx, w);
			knh_write_cid(ctx, w, cid);
			knh_write_EOL(ctx, w);
			from = 1;
		}
		Mapper *mpr = DP(o)->maplist[i];
		knh_write_TAB(ctx, w); knh_write_TAB(ctx, w);
		if(knh_Mapper_isSynonym(mpr)) {
			knh_write_char(ctx, w, "=== ");
		}
		else if(knh_Mapper_isTotal(mpr)) {
			knh_write_char(ctx, w, "==> ");
		}
		else {
			knh_write_char(ctx, w, "--> ");
		}
		knh_write_cid(ctx, w, DP(mpr)->tcid);
		knh_write_EOL(ctx, w);
	}
	if(ClassTable(cid).supcid != CLASS_Object) {
		cid = ClassTable(cid).supcid;
		o = ClassTable(cid).cmap;
		from = 0;
		goto L_TAIL;
	}
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */

static
char *knh_methodop_tochar(knh_methodn_t mn)
{
	switch(mn) {
	case METHODN_opNot: return "!x";
	case METHODN_opInstanceof: return "x instanceof T";

	case METHODN_opHas:  return "y in x";
	case METHODN_opIs:  return "x is y";
	case METHODN_opAs:  return "x as y";

	case METHODN_opEq:  return "x == y";
	case METHODN_opNeq:  return "x != x";
	case METHODN_opLt:  return "x < y";
	case METHODN_opLte:  return "x <= y";
	case METHODN_opGt:  return "x > y";
	case METHODN_opGte:  return "x >= y";

	case METHODN_opLshift:  return "x << y";
	case METHODN_opRshift:  return "x >> y";

	case METHODN_opMod:  return "x mod y";

#ifdef METHODN_opAdd__2
	case METHODN_opAdd__2 :
#endif
	case METHODN_opAdd:  return "x + y";

#ifdef METHODN_opSub__2
	case METHODN_opSub__2 :
#endif
	case METHODN_opNeg: return "-x";

	case METHODN_opSub:  return "x - y";

#ifdef METHODN_opDiv__2
	case METHODN_opDiv__2 :
#endif
	case METHODN_opDiv:  return "x / y";

#ifdef METHODN_opMul__2
	case METHODN_opMul__2 :
#endif
	case METHODN_opMul:  return "x * y";

	case METHODN_opLor:  return "x & y";
	case METHODN_opLand:  return "x | y";
	case METHODN_opLnot:  return "~x";
	case METHODN_opXor:  return "x ^ y";
	case METHODN_opNext:  return "x++";
	case METHODN_opPrev:  return "x--";
	case METHODN_opItr:   return "x..";
	case METHODN_getSize: return "|x|";
	case METHODN_get: return "x[n]";
	case METHODN_set: return "x[n]=y";
	case METHODN_setAll: return "x[]=y";
	case METHODN_opRangeTo: return "x[m to n]";
	case METHODN_opRangeUntil: return "x[m until n]";
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
void knh_Class_NAME__man(Ctx *ctx, knh_class_t cid, OutputStream *w)
{
	knh_write_char(ctx, w, _("Class"));
	knh_write_EOL(ctx, w);

	knh_write_TAB(ctx, w);
	knh_write(ctx, w, knh_String_tobytes(ClassTable(cid).lname));
	knh_write_EOL(ctx, w);

	while(ClassTable(cid).supcid != CLASS_Object) {
		cid = ClassTable(cid).supcid;
		knh_write_TAB(ctx, w);
		knh_write(ctx, w, STEXT("extends "));
		knh_write(ctx, w, knh_String_tobytes(ClassTable(cid).lname));
		knh_write_EOL(ctx, w);
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_Method__man(Ctx *ctx, Method *o, OutputStream *w, knh_class_t cid)
{
	if(!knh_Context_isVerbose(ctx)) {
		if(knh_Method_isPrivate(o)) return;
	}

	if(knh_Method_isAbstract(o)) {
		knh_write(ctx, w, STEXT("@Abstract"));
		knh_putc(ctx, w, ' ');
	}
//	if(knh_Method_rztype(o) == TYPE_void) {
//		knh_write(ctx, w, knh_String_tobytes(TS_void));
//	}else{
		knh_write_type(ctx, w, knh_pmztype_totype(ctx, knh_Method_rztype(o), cid));
//	}
	knh_putc(ctx, w, ' ');

	if(knh_Method_isStatic(o)) {
		knh_write_char(ctx, w, CTXCLASSN(cid));
		knh_putc(ctx, w, '.');
	}
	knh_write_mn(ctx, w, DP(o)->mn);

	knh_putc(ctx, w, '(');
	size_t i;
	for(i = 0; i < knh_Method_psize(o); i++) {
		if(i > 0) {
			knh_write_delim(ctx, w);
		}
		knh_mparam_t mf = knh_Method_param(o, i);
		knh_write_type(ctx, w, knh_pmztype_totype(ctx, mf.type, cid));
		knh_putc(ctx, w, ' ');
		knh_write(ctx, w, B(FIELDN(mf.fn)));
	}
	if(knh_Method_isVarArgs(o)) {
		knh_write_delim(ctx, w);
		knh_write_dots(ctx, w);
	}
	knh_putc(ctx, w, ')');
}

/* ------------------------------------------------------------------------ */
/* @method void Class.%man(OutputStream w, String m) */

static
void knh_Class__man(Ctx *ctx, Class *o, OutputStream *w, String *m)
{
	knh_class_t cid = (o)->cid;
	knh_Class_NAME__man(ctx, cid, w);
	knh_Const__man(ctx, cid, w);

	char bufmn[CLASSNAME_BUFSIZ];
	KNH_ASSERT_cid(cid);
	knh_sfp_t *lsfp = KNH_LOCAL(ctx);
	DictMap *dm = new_DictMap0(ctx, 128);
	KNH_LPUSH(ctx, dm);
	size_t i = 0;
	while(1) {
		Array *a = ClassTable(cid).cstruct->methods;
		for(i = 0; i < knh_Array_size(a); i++) {
			Method *mtd = (Method*)knh_Array_n(a, i);
			char *op = knh_methodop_tochar(DP(mtd)->mn);
			if(op == NULL) {
				knh_format_methodn(ctx, bufmn, sizeof(bufmn), DP(mtd)->mn);
				//DBG2_P("mn='%s'", bufmn);
				knh_bytes_t name = B(bufmn);
				if(IS_NULL(knh_DictMap_get__b(ctx,  dm, name))) {
					knh_DictMap_set(ctx, dm, new_String(ctx, name, NULL), UP(mtd));
				}
			}
			else {
				knh_bytes_t name = B(op);
				if(IS_NULL(knh_DictMap_get__b(ctx,  dm, name))) {
					knh_DictMap_set(ctx, dm, T__(op), UP(mtd));
				}
			}
		}
		if(cid == CLASS_Object) break;
		cid = ClassTable(cid).supcid;
	}

	int cnt = 0;
	cid = (o)->cid;

	int hasCaption = 0;
	int isBOL = 1;
	for(i = 0; i < knh_DictMap_size(dm); i++) {
		Method *mtd = (Method*)knh_DictMap_valueAt(dm, i);
		if(IS_Method(mtd)) {
			char *op = knh_methodop_tochar(DP(mtd)->mn);
			if(op == NULL) continue;
			knh_DictMap_removeAt(ctx, dm, i);
			if(DP(mtd)->cid == CLASS_Object && cid != CLASS_Object) continue;
			if(hasCaption == 0) {
				knh_write_char(ctx, w, _("Operator"));
				knh_write_EOL(ctx, w);
				hasCaption = 1;
			}
			if(isBOL == 1) {
				knh_write_TAB(ctx, w);
				isBOL = 0;
			}
			knh_snprintf(bufmn, sizeof(bufmn), "%10s  ", op);
			knh_write_char(ctx, w, bufmn);
			if(cnt % 5 == 4) {
				knh_write_EOL(ctx, w);
				isBOL = 1;
			}
			cnt++;
		}
	}
	if(isBOL != 1) {
		knh_write_EOL(ctx, w);
	}

	hasCaption = 0;
	isBOL = 1;
	knh_DictMap_sort(dm);

	for(i = 0; i < knh_DictMap_size(dm); i++) {
		Method *mtd = (Method*)knh_DictMap_valueAt(dm, i);
		if(IS_Method(mtd)) {
			if(METHODN_IS_MOVTEXT(DP(mtd)->mn)) continue;
			if(DP(mtd)->cid == CLASS_Object && cid != CLASS_Object) continue;
//			if(DP(mtd)->cid != ClassTable(cid).bcid) continue;
			if(hasCaption == 0) {
				knh_write_char(ctx, w, _("Method"));
				knh_write_EOL(ctx, w);
				hasCaption = 1;
			}
			knh_write_TAB(ctx, w);
			knh_Method__man(ctx, mtd, w, cid);
			knh_write_EOL(ctx, w);
			knh_DictMap_removeAt(ctx, dm, i);
		}
	}

	hasCaption = 0;
	cnt = 8;
	for(i = 0; i < knh_DictMap_size(dm); i++) {
		Method *mtd = (Method*)knh_DictMap_valueAt(dm, i);
		if(IS_Method(mtd)) {
			if(!METHODN_IS_MOVTEXT(DP(mtd)->mn)) continue;
			if(DP(mtd)->cid == CLASS_Object && cid != CLASS_Object) continue;
			if(hasCaption == 0) {
				knh_write_char(ctx, w, _("Formatter"));
				knh_write_EOL(ctx, w);
				knh_write_TAB(ctx, w);
				hasCaption = 1;
			}
			knh_bytes_t k = knh_String_tobytes(knh_DictMap_keyAt(dm, i));
			if(cnt + k.len > 72) {
				knh_write_EOL(ctx, w);
				knh_write_TAB(ctx, w);
				cnt = 8;
			}
			knh_write(ctx, w, k); knh_putc(ctx, w, ' ');
			cnt += (k.len + 1);
		}
	}
	knh_write_EOL(ctx, w);

	knh_ClassMap__man(ctx, ClassTable(cid).cmap, w, cid);
	KNH_LOCALBACK(ctx, lsfp);
}


/* ======================================================================== */
/* [C Compatible] */

/* ------------------------------------------------------------------------ */
/* @method void Object.%p(OutputStream w, String m) */

static METHOD knh__Object__p(Ctx *ctx, knh_sfp_t *sfp)
{
	void *p = NULL;
	if(IS_bInt(sfp[0].o) || IS_bFloat(sfp[0].o)) {
		p = (void*)(&sfp[0] + sizeof(void*));
	}
	else if(IS_Boolean(sfp[0].o)) {
		p = (sfp[0].bvalue) ? (void*)(KNH_TRUE) : (void*)(KNH_FALSE);
	}
	else if(IS_NOTNULL(sfp[0].o)) {
		p = (void*)sfp[0].o;
	}
	knh_write__p(ctx, sfp[1].w, p);
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%c(OutputStream w, String m) */

static METHOD knh__Int__c(Ctx *ctx, knh_sfp_t *sfp)
{
	char buf[16];
	knh_format_utf8(buf, sizeof(buf), sfp[0].ivalue);
	knh_write(ctx, sfp[1].w, B(buf));
}

/* ======================================================================== */
/* [number] */

/* ------------------------------------------------------------------------ */
/* @method void Int.%d(OutputStream w, String m) */

static METHOD knh__Int__d(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_String(sfp[2].s)) {
		char fmt[40];
		knh_format_newFMT(fmt, sizeof(fmt), knh_String_tobytes(sfp[2].s), 0, KNH_INT_FMT);
		knh_write_ifmt(ctx, sfp[1].w, fmt, sfp[0].ivalue);
	}
	else {
		knh_write_ifmt(ctx, sfp[1].w, KNH_INT_FMT, sfp[0].ivalue);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%u(OutputStream w, String m) */

static METHOD knh__Int__u(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_String(sfp[2].s)) {
		char fmt[40];
		knh_format_newFMT(fmt, sizeof(fmt), knh_String_tobytes(sfp[2].s), 0, KNH_UINT_FMT);
		knh_write_ifmt(ctx, sfp[1].w, fmt, sfp[0].ivalue);
	}
	else {
		knh_write_ifmt(ctx, sfp[1].w, KNH_UINT_FMT, sfp[0].ivalue);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%f(OutputStream w, String m) */

static METHOD knh__Int__f(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_String(sfp[2].s)) {
		char fmt[40];
		knh_format_newFMT(fmt, sizeof(fmt), knh_String_tobytes(sfp[2].s), 1, KNH_FLOAT_FMT);
		knh_write_ffmt(ctx, sfp[1].w, fmt, (knh_float_t)sfp[0].ivalue);
	}
	else {
		knh_write_ffmt(ctx, sfp[1].w, KNH_FLOAT_FMT, (knh_float_t)sfp[0].ivalue);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%x(OutputStream w, String m) */

static METHOD knh__Int__x(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_write_ifmt(ctx, sfp[1].w, KNH_INT_XFMT, sfp[0].ivalue);
}

/* ------------------------------------------------------------------------ */

static
void knh_write_bits(Ctx *ctx, OutputStream *w, knh_uint64_t n, size_t bits)
{
	size_t i;
	knh_uint64_t flag = 1ULL << (bits - 1);
	for(i = 0; i < bits; i++) {
		if(i > 0 && i % 8 == 0) {
			knh_putc(ctx, w, ' ');
		}
		if((flag & n) == flag) {
			knh_putc(ctx, w, '1');
		}else{
			knh_putc(ctx, w, '0');
		}
		flag = flag >> 1;
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Int.%bits(OutputStream w, String m) */

static METHOD knh__Int__bits(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_write_bits(ctx, sfp[1].w, sfp[0].ivalue, sizeof(knh_int_t) * 8);
}

/* ------------------------------------------------------------------------ */
/* @method void Float.%s(OutputStream w, String m) */

static METHOD knh__Float__s(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_write_ffmt(ctx, sfp[1].w, KNH_FLOAT_FMT, p_float(sfp[0]));
}

/* ------------------------------------------------------------------------ */
/* @method void Float.%d(OutputStream w, String m) */

static METHOD knh__Float__d(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_String(sfp[2].s)) {
		char fmt[40];
		knh_format_newFMT(fmt, sizeof(fmt), knh_String_tobytes(sfp[2].s), 0, KNH_INT_FMT);
		//DBG_P("fmt='%s'", fmt);
		knh_write_ifmt(ctx, sfp[1].w, fmt, (knh_int_t)p_float(sfp[0]));
	}
	else {
		knh_write_ifmt(ctx, sfp[1].w, KNH_INT_FMT, (knh_int_t)p_float(sfp[0]));
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Float.%f(OutputStream w, String m) */

static METHOD knh__Float__f(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_String(sfp[2].s)) {
		char fmt[40];
		knh_format_newFMT(fmt, sizeof(fmt), knh_String_tobytes(sfp[2].s), 1, KNH_FLOAT_FMT);
		//DBG_P("fmt='%s'", fmt);
		knh_write_ffmt(ctx, sfp[1].w, fmt, p_float(sfp[0]));
	}
	else {
		knh_write_ffmt(ctx, sfp[1].w, KNH_FLOAT_FMT, p_float(sfp[0]));
	}
}

/* ------------------------------------------------------------------------ */
/* @method void Float.%bits(OutputStream w, String m) */

static METHOD knh__Float__bits(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_write_bits(ctx, sfp[1].w, sfp[0].data, sizeof(knh_float_t) * 8);
}



#endif/* KNH_CC_METHODAPI*/

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
