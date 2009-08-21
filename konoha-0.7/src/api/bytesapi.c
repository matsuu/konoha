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

/* ======================================================================== */
/* [constructor] */

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
/* @method void Bytes.write(Bytes! buffer, Int offset, Int length) */

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
		int i, ac = knh_stack_argc(ctx, v);
		for(i = 0; i < ac; i++) {
			knh_Bytes_putc(ctx, o, p_int(v[i]));
		}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void Bytes.memcpy(Int offset, Bytes! buffer, Int offset, Int length)  */

static METHOD knh__Bytes_memcpy(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *d = (Bytes*)sfp[0].o;
	if(!knh_Object_isImmutable(d)) {
		size_t doff = IS_NULL(sfp[1].o) ? 0 : p_int(sfp[1]);
		Bytes *s = (Bytes*)sfp[2].o;
		size_t soff = IS_NULL(sfp[3].o) ? 0 : p_int(sfp[3]);
		size_t slen = IS_NULL(sfp[4].o) ? 0 : ((s)->size - soff);
		if(doff + slen < (d)->size) {
			knh_memcpy(d->buf + doff, s->buf + soff, slen);
		}
		else {
			KNH_THROW_OUTOFINDEX(ctx, doff + slen, (d)->size);
		}
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */

#endif/*KNH_CC_METHODAPI*/

#ifdef __cplusplus
}
#endif
