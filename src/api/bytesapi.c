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

/* ======================================================================== */
/* [constructor] */

/* ------------------------------------------------------------------------ */
/* @method Bytes! Bytes.new(Int init) */

static METHOD knh__Bytes_new(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *o = (Bytes*)sfp[0].o;
	size_t init = IS_NULL(sfp[1].o) ? 0 : knh_bytes_newsize(p_size(sfp[1]));
	KNH_ASSERT(o->buf == NULL);
	if(init > 0) {
	  o->buf = (knh_uchar_t*)KNH_MALLOC(ctx, init);
		o->capacity = init;
		knh_bzero(o->buf, init);
	}
	KNH_RETURN(ctx, sfp, o);
}

/* ------------------------------------------------------------------------ */
/* @method void Bytes.putc(Int! c) */

static METHOD knh__Bytes_putc(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *o = (Bytes*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		knh_Bytes_putc(ctx, o, p_int(sfp[1]));
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void Bytes.write(Bytes! b, Int n, Int l) */

static METHOD knh__Bytes_write(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *o = (Bytes*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		knh_bytes_t t = knh_Bytes_tobytes(sfp[1].ba);
		if(IS_NOTNULL(sfp[2].o)) {
			size_t n = knh_array_index(ctx, p_int(sfp[2]), o->size);
			t = knh_bytes_last(t, n);
		}
		if(IS_NOTNULL(sfp[3].o)) {
			size_t l = p_int(sfp[3]);
			if(l < t.len) {
				t.len = l;
			}
		}
		knh_Bytes_write(ctx, o, t);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] void Bytes.opLshift(Int! v) */

static METHOD knh__Bytes_opLshift(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *o = (Bytes*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		knh_sfp_t *v = sfp + 1;
		int i, ac = knh_sfp_argc(ctx, v);
		for(i = 0; i < ac; i++) {
			knh_Bytes_putc(ctx, o, p_int(v[i]));
		}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method Int! Bytes.getSize() */

static METHOD knh__Bytes_getSize(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *o = (Bytes*)sfp[0].o;
	KNH_RETURN_Int(ctx, sfp, o->size);
}

/* ------------------------------------------------------------------------ */
/* @method Int! Bytes.get(Int! n) */

static METHOD knh__Bytes_get(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *o = (Bytes*)sfp[0].o;
	size_t n2 = knh_array_index(ctx, p_int(sfp[1]), o->size);
	KNH_RETURN_Int(ctx, sfp, o->buf[n2]);
}

/* ------------------------------------------------------------------------ */
/* @method void Bytes.set(Int! n, Int! c) */

static METHOD knh__Bytes_set(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *o = (Bytes*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		size_t n2 = knh_array_index(ctx, p_int(sfp[1]), o->size);
		o->buf[n2] = (knh_uchar_t)p_int(sfp[2]);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void Bytes.opFill(Int! c) */

static METHOD knh__Bytes_opFill(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *o = (Bytes*)sfp[0].o;
	if(!knh_Object_isImmutable(o)) {
		size_t i, n = p_int(sfp[1]);
		for(i = 0; i < o->size; i++) {
			o->buf[i] = n;
		}
	}
	KNH_RETURN(ctx, sfp, o);
}

/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */
/* @method void Bytes.%k(OutputStream w, String m) */

static
void knh_Bytes__k(Ctx *ctx, Bytes *o, OutputStream *w, String *m)
{
	knh_printf(ctx, w, "byte[%d]", (o)->size);
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

/* ======================================================================== */
/* [mapping] */

/* @map Bytes String! @Const @Final */

static
MAPPER knh_Bytes_String(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_bytes_t t = knh_Bytes_tobytes((Bytes*)sfp[0].o);
	String *s = TS_EMPTY;
	if(knh_bytes_checkENCODING(t)) {
		s = new_String(ctx, t, NULL);
	}
	KNH_MAPPED(ctx, sfp, s);
}

/* ------------------------------------------------------------------------ */
/* @map String Bytes! @Const @Final */

static
MAPPER knh_String_Bytes(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *b = new_Bytes(ctx, knh_String_strlen(sfp[0].s) + 1);
	knh_Bytes_write(ctx, b, knh_String_tobytes(sfp[0].s));
	KNH_MAPPED(ctx, sfp, b);
}

/* ------------------------------------------------------------------------ */

#endif/*KNH_CC_METHODAPI*/

#ifdef __cplusplus
}
#endif
