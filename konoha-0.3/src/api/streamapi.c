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

#ifdef KNH_CC_METHODAPI

/* ------------------------------------------------------------------------ */
/* @method InputStream InputStream.new(String! urn) */

static METHOD knh__InputStream_new(Ctx *ctx, knh_sfp_t *sfp)
{
	InputStream *o = (InputStream*)sfp[0].o;
	KNH_RETURN(ctx, sfp, knh_InputStream_open(ctx, o, sfp[1].s));
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! InputStream.isClosed() */

static METHOD knh__InputStream_isClosed(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_InputStream_isClosed((InputStream*)sfp[0].o));
}


/* ======================================================================== */
/* [iterators] */

static
ITRNEXT knh_InputStream_line_next(Ctx *ctx, knh_sfp_t *sfp, int n)
{
	Iterator *it = sfp[0].it;
	InputStream *in = (InputStream*)DP(it)->source;
	int ch;
	knh_cwb_t cb = new_cwb(ctx);

	while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
		if(ch == 13) continue;
		if(ch == 10) {
			KNH_ITRNEXT(ctx, sfp, n, new_String__cwbconv(ctx, cb, DP(in)->bconv));
		}
		knh_Bytes_putc(ctx, cb.ba, ch);
	}
	if(knh_cwb_size(cb) != 0) {
		KNH_ITRNEXT(ctx, sfp, n, new_String__cwbconv(ctx, cb, DP(in)->bconv));
	}
	KNH_ITREND(ctx, sfp, n);
}

/* ------------------------------------------------------------------------ */
/* @map InputStream String.. @Final */

static MAPPER knh_InputStream_String__(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_MAPPED(ctx, sfp, new_Iterator(ctx, CLASS_String, sfp[0].o, knh_InputStream_line_next));
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

/* ======================================================================== */
/* [OutputStream] */

/* @method OutputStream OutputStream.new(String! urn, String mode) */

static METHOD knh__OutputStream_new(Ctx *ctx, knh_sfp_t *sfp)
{
	OutputStream *o = (OutputStream*)sfp[0].o;
	KNH_RETURN(ctx, sfp, knh_OutputStream_open(ctx, o, sfp[1].s, sfp[2].s));
}

/* ------------------------------------------------------------------------ */
/* @method void OutputStream.putc(Int! ch) */

static METHOD knh__OutputStream_putc(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *ba = DP(sfp[0].w)->ba;
	KNH_ASSERT(IS_Bytes(ba));
	knh_Bytes_putc(ctx, ba, sfp[1].ivalue);
	if(!knh_OutputStream_isStoringBuffer(sfp[0].w) && ba->size > DP(sfp[0].w)->driver->bufsiz) {
		DP(sfp[0].w)->driver->fwrite(ctx, DP(sfp[0].w)->fd, (char*)(ba)->buf, (ba)->size);
		knh_Bytes_clear(ba, 0);
	}
	DP(sfp[0].w)->size++;
}

/* ------------------------------------------------------------------------ */
/* @method void OutputStream.write(Bytes! buf, Int offset, Int len) */

static METHOD knh__OutputStream_write(Ctx *ctx, knh_sfp_t *sfp)
{
	OutputStream *o = (OutputStream*)sfp[0].o;
	knh_bytes_t buf = knh_Bytes_tobytes((Bytes*)sfp[1].o);
	size_t offset = IS_NULL(sfp[2].o) ? 0 : knh_array_index(ctx, p_int(sfp[2]), buf.len);
	size_t len = IS_NULL(sfp[3].o) ? (buf.len - offset) : p_int(sfp[3]);
	if(offset + len > buf.len) len = buf.len - offset;
	buf.buf = &(buf.buf[offset]);
	buf.len = len;
	knh_OutputStream_write(ctx, o, buf);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! OutputStream.isClosed() */

static METHOD knh__OutputStream_isClosed(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_OutputStream_isClosed((OutputStream*)sfp[0].o));
}

/* ------------------------------------------------------------------------ */
/* @method void OutputStream.print(Any v) */

static METHOD knh__OutputStream_print(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_bString(sfp[1].o)) {
		knh_OutputStream_print_(ctx, sfp[0].w, knh_String_tobytes(sfp[1].s), 0);
	}
	else {
		KNH_SHIFTESP(ctx, sfp);
		knh_esp1_format(ctx, METHODN__s, sfp[0].w, KNH_NULL);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void OutputStream.println(Any v) */

static METHOD knh__OutputStream_println(Ctx *ctx, knh_sfp_t *sfp)
{
	if(IS_bString(sfp[1].o)) {
		knh_OutputStream_print_(ctx, sfp[0].w, knh_String_tobytes(sfp[1].s), 1);
	}
	else {
		KNH_SHIFTESP(ctx, sfp);
		knh_esp1_format(ctx, METHODN__s, sfp[0].w, KNH_NULL);
		KNH_ASSERT(IS_OutputStream(sfp[2].o)); // Tricky ..
		knh_write_EOL(ctx, sfp[2].w);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method[VARARGS] void OutputStream.opLshift(Any v) */

static METHOD knh__OutputStream_opLshift(Ctx *ctx, knh_sfp_t *sfp)
{
	OutputStream *out = (OutputStream*)sfp[0].o;
	knh_sfp_t *v = sfp + 1, *esp1 = ctx->esp + 1;
	int ac = knh_sfp_argc(ctx, v);
	size_t i;
	for(i = 0; i < ac; i++) {
		if(IS_bString(v[i].o)) {
			if(v[i].s == TS_EOL) {
				knh_write_EOL(ctx, out);
			}
			else if(v[i].s == TS_BEGIN) {
				DP(out)->indent++;
			}
			else if(v[i].s == TS_END) {
				DP(out)->indent--;
			}
			else {
				knh_OutputStream_print_(ctx, out, knh_String_tobytes(v[i].s), 0);
			}
		}
		else {
			KNH_SETv(ctx, esp1[0].o, v[i].o);
			esp1[0].data = v[i].data;
			KNH_ASSERT(ctx->esp + 1 == esp1);
			knh_esp1_format(ctx, METHODN__s, out, KNH_NULL);
		}
	}
	if(knh_OutputStream_isAutoFlush(out)) {
		knh_OutputStream_flush(ctx, out);
	}
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method void OutputStream.%k(OutputStream w, String m) */

void knh_OutputStream__k(Ctx *ctx, OutputStream *o, OutputStream *w, String *m)
{
	knh_putc(ctx, w, '\'');
	knh_print(ctx, w, knh_String_tobytes(DP(o)->urn));
	knh_putc(ctx, w, '\'');
}

/* ======================================================================== */
/* [Socket] */

/* ------------------------------------------------------------------------ */
/* @method Socket! Socket.new(String! host, Int! port); */

METHOD knh__Socket_new(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Socket_t *so = (knh_Socket_t*)sfp[0].o;
	knh_bytes_t urn = knh_String_tobytes(sfp[1].s);
	char *ip_or_host = NULL;
	if(knh_bytes_startsWith(urn, STEXT("socket:"))) {
		ip_or_host = (char*)(knh_bytes_last(urn, 7)).buf;
	}
	else if(knh_bytes_startsWith(urn, STEXT("ip:"))) {
		ip_or_host = (char*)(knh_bytes_last(urn, 3)).buf;
	}
	else {
		ip_or_host = (char*)urn.buf;
	}
	KNH_SETv(ctx, DP(so)->urn, sfp[1].o);
	DP(so)->port = (int)sfp[2].ivalue;
	DP(so)->sd = knh_socket_open(ctx, ip_or_host, DP(so)->port);
	if(DP(so)->sd != -1) {
		KNH_SETv(ctx, DP(so)->in,  new_InputStream__io(ctx, DP(so)->urn, (knh_io_t)DP(so)->sd, konoha_getSocketDriver()));
		KNH_SETv(ctx, DP(so)->out, new_OutputStream__io(ctx, DP(so)->urn, (knh_io_t)DP(so)->sd, konoha_getSocketDriver()));
	}
	KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ------------------------------------------------------------------------ */
/* @method InputStream! Socket.getInputStream() */

METHOD knh__Socket_getInputStream(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Socket_t *so = (knh_Socket_t*)sfp[0].o;
	KNH_RETURN(ctx, sfp, DP(so)->in);
}

/* ------------------------------------------------------------------------ */
/* @method OutputStream! Socket.getOutputStream() */

METHOD knh__Socket_getOutputStream(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Socket_t *so = (knh_Socket_t*)sfp[0].o;
	KNH_RETURN(ctx, sfp, DP(so)->out);
}

/* ------------------------------------------------------------------------ */
/* @method void Socket.close() */

METHOD knh__Socket_close(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Socket_t *so = (knh_Socket_t*)sfp[0].o;
	if(DP(so)->sd != -1) {
		knh_InputStream_close(ctx, DP(so)->in);
		knh_OutputStream_close(ctx, DP(so)->out);
		knh_socket_close(ctx, DP(so)->sd);
		DP(so)->sd = -1;
	}
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Socket.isClosed() */

METHOD knh__Socket_isClosed(Ctx *ctx, knh_sfp_t *sfp)
{
	knh_Socket_t *so = (knh_Socket_t*)sfp[0].o;
	KNH_RETURN_Boolean(ctx, sfp, (DP(so)->sd == -1));
}

/* ------------------------------------------------------------------------ */


#else /*KNH_CC_METHODAPI*/

/* ------------------------------------------------------------------------ */
/* @method void InputStream.setEncoding(String enc) */

void knh_InputStream_setEncoding(Ctx *ctx, InputStream *o, String *enc)
{
	if(IS_NULL(enc)) {
		KNH_SETv(ctx, DP(o)->enc, TS_ENCODING);
		KNH_SETv(ctx, DP(o)->bconv, KNH_NULL);
	}
	else if(knh_bytes_strcasecmp(knh_String_tobytes(enc), STEXT(KONOHA_ENCODING)) == 0) {
		KNH_SETv(ctx, DP(o)->enc, TS_ENCODING);
		KNH_SETv(ctx, DP(o)->bconv, KNH_NULL);
	}
	else {
		BytesConv *bin = new_BytesConv__in(ctx, knh_String_tochar(enc));
		if(IS_NULL(bin)) {
			KNH_SETv(ctx, DP(o)->enc, TS_ENCODING);
			KNH_WARNING(ctx, "unsupported character encoding: %s", knh_String_tochar(enc));
		}
		else {
			KNH_SETv(ctx, DP(o)->enc, enc);
		}
		KNH_SETv(ctx, DP(o)->bconv, bin);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void OutputStream.setEncoding(String enc) */

void knh_OutputStream_setEncoding(Ctx *ctx, OutputStream *o, String *enc)
{
	if(IS_NULL(enc)) {
		KNH_SETv(ctx, DP(o)->enc, TS_ENCODING);
		KNH_SETv(ctx, DP(o)->bconv, KNH_NULL);
	}
	else if(knh_bytes_strcasecmp(knh_String_tobytes(enc), STEXT(KONOHA_ENCODING)) == 0) {
		KNH_SETv(ctx, DP(o)->enc, TS_ENCODING);
		KNH_SETv(ctx, DP(o)->bconv, KNH_NULL);
	}
	else {
		BytesConv *bout = new_BytesConv__out(ctx, knh_String_tochar(enc));
		if(IS_NULL(bout)) {
			KNH_SETv(ctx, DP(o)->enc, TS_ENCODING);
			KNH_WARNING(ctx, "unsupported character encoding: %s", knh_String_tochar(enc));
		}
		else {
			KNH_SETv(ctx, DP(o)->enc, enc);
		}
		KNH_SETv(ctx, DP(o)->bconv, bout);
	}
}

/* ------------------------------------------------------------------------ */

#endif /*KNH_CC_METHODAPI*/


#ifdef __cplusplus
}
#endif
