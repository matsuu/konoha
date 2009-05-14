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
/* [cwb] */

knh_cwb_t new_cwb(Ctx* ctx)
{
	knh_cwb_t cwb;
	cwb.ba = ((Context*)ctx)->bufa;
	cwb.w  = ((Context*)ctx)->bufw;
	cwb.pos = knh_Bytes_size(((Context*)ctx)->bufa);
	return cwb;
}

/* ------------------------------------------------------------------------ */

size_t knh_cwb_size(knh_cwb_t cwb)
{
	return (cwb.ba)->size - cwb.pos;
}

/* ------------------------------------------------------------------------ */

knh_bytes_t knh_cwb_tobytes(knh_cwb_t cwb)
{
	knh_bytes_t t = {(cwb.ba)->buf + cwb.pos, (cwb.ba)->size - cwb.pos};
	return t;
}

/* ------------------------------------------------------------------------ */

char *knh_cwb_tochar(knh_cwb_t cwb)
{
	knh_bytes_t t = {(cwb.ba)->buf + cwb.pos, (cwb.ba)->size - cwb.pos};
	KNH_ASSERT(t.buf[t.len] == 0);
	return (char*)t.buf;
}

/* ------------------------------------------------------------------------ */

void knh_cwb_clear(knh_cwb_t cwb)
{
	knh_Bytes_clear(cwb.ba, cwb.pos);
}

/* ======================================================================== */
/* [String] */

String *new_String__cwb(Ctx *ctx, knh_cwb_t cwb)
{
	if(cwb.pos == (cwb.ba)->size) {
		return TS_EMPTY;
	}
	else {
		knh_bytes_t t = knh_cwb_tobytes(cwb);
		String *s = new_String(ctx, t, NULL);
		knh_cwb_clear(cwb);
		return s;
	}
}

/* ------------------------------------------------------------------------ */

String *new_StringX__cwb(Ctx *ctx, knh_class_t cid, knh_cwb_t cwb)
{
	knh_bytes_t t = knh_cwb_tobytes(cwb);
	String *s = new_StringX(ctx, cid, t, NULL);
	knh_cwb_clear(cwb);
	return s;
}

///* ------------------------------------------------------------------------ */
//
//
//size_t knh_Bytes_lastsize(Bytes *o, size_t pos)
//{
//	return o->size - pos;
//}

///* ------------------------------------------------------------------------ */
//
//char *knh_cwb_top(knh_cwb_t cb)
//{
//	return knh_Bytes_tochar(cb.ba) + cb.pos;
//}




///* ======================================================================== */
///* [Bytes] */
//
//
//knh_bytes_t knh_Bytes_firstbyte(Bytes *o, size_t pos)
//{
//	knh_bytes_t v;
//	KNH_ASSERT(pos <= o->size);
//	v.buf = o->buf + pos;
//	v.len = pos;
//	return v;
//}
//
///* ------------------------------------------------------------------------ */
//
//
//knh_bytes_t knh_Bytes_lastbyte(Bytes *o, size_t pos)
//{
//	knh_bytes_t v;
//	KNH_ASSERT(pos <= o->size);
//	v.buf = o->buf + pos;
//	v.len = o->size  - pos;
//	return v;
//}

///* ------------------------------------------------------------------------ */
//
//void knh_Bytes_subclear(Bytes *o, size_t pos)
//{
//	KNH_ASSERT(pos <= o->size);
//	knh_bzero(o->buf + pos, o->size - pos);
//	o->size = pos;
//}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
