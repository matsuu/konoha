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
/* deps/api/knh_socket__{posix|win32|btron}.c */

int  knh_socket_open(Ctx *ctx, char *ip_or_host, int port);
void knh_socket_close(Ctx *ctx, int sd);

knh_bool_t knh_Socket_open__deps(Ctx *ctx, knh_Socket *b, char *ip_or_host, int port);
void knh_Socket_close__deps(Ctx *ctx, knh_Socket *b);
int knh_InputStream_getc__Socket(Ctx *ctx, knh_inptr_t *ptr);
size_t knh_InputStream_read__Socket(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz);
void knh_OutputStream_putc__Socket(Ctx *ctx, knh_outptr_t *ptr, int ch);
size_t knh_OutputStream_write__Socket(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz);
void knh_OutputStream_flush__Socket(Ctx *ctx, knh_outptr_t *ptr);

static knh_inptr_drivers_t DRIVERS__sockin = {
	knh_InputStream_open__nop,
	knh_InputStream_getc__Socket,
	knh_InputStream_read__Socket,
	knh_InputStream_close__nop
};

static knh_outptr_drivers_t DRIVERS__sockout = {
	knh_OutputStream_open__nop,
	knh_OutputStream_putc__Socket,
	knh_OutputStream_write__Socket,
	knh_OutputStream_flush__Socket,
	knh_OutputStream_close__nop
};

/* ======================================================================== */
/* [structs] */

void knh_Socket_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Socket* b = (Socket*)s;
	KNH_INITv(b->urn, knh_String_EMPTY());
	b->sd = -1;
	b->port = 0;
	b->fp_in = NULL;
	b->fp_out = NULL;
	KNH_INITv(b->in, KNH_NULL);
	KNH_INITv(b->out, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

#define _knh_Socket_struct_copy   NULL

/* ------------------------------------------------------------------------ */

#define _knh_Socket_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void
knh_Socket_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Socket *b = (Socket*)s;
	gc(ctx, b->urn);
	if(IS_SWEEP(gc)) {
		if(b->sd != -1) {
			knh_Socket_close(ctx, b);
		}
	}
	gc(ctx, b->in);
	gc(ctx, b->out);
}

/* ======================================================================== */
/* [constructors] */

Socket* new_Socket(Ctx *ctx, knh_bytes_t urn, int port)
{
	char *ip_or_host = NULL;
	Socket* b = (Socket*)knh_Object_malloc(ctx, CLASS_Socket);
	knh_Socket_struct_init(ctx, (Struct*)b, 0, NULL);
	KNH_SETv(ctx, b->urn, new_String__fast(ctx, CLASS_String, urn));
	b->port = port;
	
	if(knh_bytes_startsWith(urn, STEXT("socket:"))) {
		ip_or_host = (char*)(knh_bytes_last(urn, 7)).buf;
	}
	else if(knh_bytes_startsWith(urn, STEXT("ip:"))) {
		ip_or_host = (char*)(knh_bytes_last(urn, 3)).buf;
	}
	else {
		ip_or_host = (char*)urn.buf;
	}
	if(knh_Socket_open__deps(ctx, b, ip_or_host, port)) {
		KNH_SETv(ctx, b->in, new_InputStream(ctx, b->urn, (knh_inptr_t*)b, DRIVERS__sockin));
		KNH_SETv(ctx, b->out, new_OutputStream(ctx, b->urn, (knh_outptr_t*)b, DRIVERS__sockout));
	}
	else {
		KNH_SETv(ctx, b->in, new_InputStream__NULL(ctx));
		KNH_SETv(ctx, b->out, new_OutputStream__NULL(ctx));
	}
	return b;
}

/* ======================================================================== */
/* [method] */

/* ------------------------------------------------------------------------ */
/* @method InputStream! Socket.getInputStream() */

InputStream *knh_Socket_getInputStream(Ctx *ctx, Socket *b)
{
	return b->in;
}

/* ------------------------------------------------------------------------ */
/* @method OutputStream! Socket.getOutputStream() */

OutputStream *knh_Socket_getOutputStream(Ctx *ctx, Socket *b)
{
	return b->out;
}

/* ------------------------------------------------------------------------ */
/* @method void Socket.close() */

void knh_Socket_close(Ctx *ctx, Socket *b)
{
	knh_InputStream_close(ctx, b->in);
	knh_OutputStream_close(ctx, b->out);
	if(b->sd != -1) {
		knh_Socket_close__deps(ctx, b);
		b->sd = -1;
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
