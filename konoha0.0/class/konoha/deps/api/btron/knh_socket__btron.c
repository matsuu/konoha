/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER  
 * 
 * Copyright (c) 2005-2008, Kimio Kuramitsu <kimio at ynu.ac.jp>
 *           (c) 2007       SHINPEI NAKATA <shinpei at ubicg.ynu.ac.jp>
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

#ifdef KONOHA_API__BTRON

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */
/* complete the following functions */

int  knh_socket_open(Ctx *ctx, char *ip_or_host, int port);
void knh_socket_close(Ctx *ctx, int sd);

knh_bool_t knh_Socket_open__deps(Ctx *ctx, knh_Socket *b, char *ip_or_host, int port);
void knh_Socket_close__deps(Ctx *ctx, knh_Socket *b);
int knh_InputStream_getc__Socket(Ctx *ctx, knh_inptr_t *ptr);
size_t knh_InputStream_read__Socket(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz);
void knh_OutputStream_putc__Socket(Ctx *ctx, knh_outptr_t *ptr, int ch);
size_t knh_OutputStream_write__Socket(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz);
void knh_OutputStream_flush__Socket(Ctx *ctx, knh_outptr_t *ptr);

/* ======================================================================== */
/* [Socket] */

int knh_socket_open(Ctx *ctx, char *ip_or_host, int port)
{
	struct in_addr addr = {0};
	struct hostent	*host;
	struct sockaddr_in	server = {0};
	int sd = -1;
	
//	memset((void *)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	
	if ((addr.s_addr = inet_addr(ip_or_host)) == 1) {
		host = gethostbyname(ip_or_host);
		if (host == NULL) {
			//KNH_THROWf(ctx, "Socket!!: no such host %s", ip_or_host);
			return -1;
		}
		memcpy(&addr, (struct in_addr *)*host->h_addr_list, sizeof(struct in_addr));
	}
	
	server.sin_addr = addr;
	server.sin_port = port;

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		return -1;
	}
	if (connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
		return -1;
	}
	return sd;
}

/* ------------------------------------------------------------------------ */

void knh_socket_close(Ctx *ctx, int sd)
{
	close(sd);
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_Socket_open__deps(Ctx *ctx, knh_Socket *b, char *ip_or_host, int port)
{
	int sd;
	if((sd == knh_socket_open(ctx, ip_or_host, port)) == -1) {
		return 0;
	}
	b->sd = sd;
	b->fp_in = fdopen(sd, "r");
	b->fp_out = fdopen(sd, "w");
	return 1;
}

/* ------------------------------------------------------------------------ */

void knh_Socket_close__deps(Ctx *ctx, knh_Socket *b)
{
	fclose(b->fp_in);
	fclose(b->fp_out);
	close(b->sd);
}

/* ======================================================================== */
/* [InputStream] */

int knh_InputStream_getc__Socket(Ctx *ctx, knh_inptr_t *ptr)
{
	knh_Socket *b = (knh_Socket*)ptr;
	return fgetc(b->fp_in);
}

/* ------------------------------------------------------------------------ */

size_t 
knh_InputStream_read__Socket(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz)
{
	knh_Socket *b = (knh_Socket*)ptr;
	return fread(buf, bufsiz, 1, b->fp_in);
}

/* ======================================================================== */
/* [OutputStream] */

void knh_OutputStream_putc__Socket(Ctx *ctx, knh_outptr_t *ptr, int ch)
{
	knh_Socket *b = (knh_Socket*)ptr;
	fputc(ch, b->fp_out);
}

/* ------------------------------------------------------------------------ */

size_t 
knh_OutputStream_write__Socket(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz)
{
	knh_Socket *b = (knh_Socket*)ptr;
	return fwrite(buf, bufsiz, 1, b->fp_out);
}

/* ------------------------------------------------------------------------ */

void 
knh_OutputStream_flush__Socket(Ctx *ctx, knh_outptr_t *ptr)
{
	knh_Socket *b = (knh_Socket*)ptr;
	fflush(b->fp_out);
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif

#endif/*KONOHA_API__BTRON*/
