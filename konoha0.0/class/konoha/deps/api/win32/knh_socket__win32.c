/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER  
 * 
 * Copyright (c) 2005-2008, Kimio Kuramitsu <kimio at ynu.ac.jp>
 *           (c) 2007       Satoshi Kobayashi <gucchi at ubicg.ynu.ac.jp>
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

#ifdef KONOHA_API__WIN32

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <winsock2.h>
#include <mswsock.h>
#include <io.h>
#include <fcntl.h>



#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */
/* complete the following functions */

knh_socket_t  knh_socket_open(Ctx *ctx, char *ip_or_host, int port);
void knh_socket_close(Ctx *ctx, knh_socket_t sd);

knh_bool_t knh_Socket_open__deps(Ctx *ctx, knh_Socket *b, char *ip_or_host, int port);
void knh_Socket_close__deps(Ctx *ctx, knh_Socket *b);
int knh_InputStream_getc__Socket(Ctx *ctx, knh_inptr_t *ptr);
size_t knh_InputStream_read__Socket(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz);
void knh_OutputStream_putc__Socket(Ctx *ctx, knh_outptr_t *ptr, int ch);
size_t knh_OutputStream_write__Socket(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz);
void knh_OutputStream_flush__Socket(Ctx *ctx, knh_outptr_t *ptr);

/* ======================================================================== */
/* [Socket] */

knh_socket_t knh_socket_open(Ctx *ctx, char *ip_or_host, int port)
{
	knh_socket_t sd = INVALID_SOCKET;
	int sockopt = SO_SYNCHRONOUS_NONALERT;
	WSADATA wsadata;
	if(WSAStartup(MAKEWORD(2,0),&wsadata) != 0){
		return INVALID_SOCKET;
	}
	setsockopt(INVALID_SOCKET, SOL_SOCKET, SO_OPENTYPE, (char *)&sockopt, sizeof(sockopt));
	if((sd = socket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET){
		return INVALID_SOCKET;
	}
	struct in_addr addr = {0};
	struct hostent	*host;
	struct sockaddr_in	server = {0};
//	
////	memset((void *)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	
	if ((addr.s_addr = inet_addr(ip_or_host)) == INADDR_NONE) {
		host = gethostbyname(ip_or_host);
		if (host == NULL) {
			//KNH_THROWf(ctx, "Socket!!: no such host %s", ip_or_host);
			return INVALID_SOCKET;
		}
		addr.s_addr=*(*(unsigned int **)host->h_addr_list);
	}
	
	server.sin_addr = addr;
	server.sin_port = htons(port);
//
//	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//		return -1;
//	}
	if (connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
		return INVALID_SOCKET;
	}
	return sd;
}

/* ------------------------------------------------------------------------ */

void knh_socket_close(Ctx *ctx, knh_socket_t sd)
{
	
	closesocket(sd);
	WSACleanup();
}

/* ------------------------------------------------------------------------ */

knh_bool_t knh_Socket_open__deps(Ctx *ctx, knh_Socket *b, char *ip_or_host, int port)
{
	knh_socket_t sd;
	if((sd = knh_socket_open(ctx, ip_or_host, port)) == INVALID_SOCKET) {
		return 0;
	}
	b->sd = sd;
//	b->fp_in = fdopen(sd, "r");
	int sd_handle = _open_osfhandle(sd, _O_RDONLY);
	b->fp_out = fdopen(sd_handle, "w");
	return 1;
}

/* ------------------------------------------------------------------------ */

void knh_Socket_close__deps(Ctx *ctx, knh_Socket *b)
{
//	fclose(b->fp_in);
	fclose(b->fp_out);
	closesocket(b->sd);
}

/* ======================================================================== */
/* [InputStream] */

int knh_InputStream_getc__Socket(Ctx *ctx, knh_inptr_t *ptr)
{
	knh_Socket *b = (knh_Socket*)ptr;
	char buf[1];
	int size = recv(b->sd, buf, 1, 0);
	if(size == 0) {
		return EOF;
	}
	return (int)buf[0];
}

/* ------------------------------------------------------------------------ */

size_t 
knh_InputStream_read__Socket(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz)
{
	knh_Socket *b = (knh_Socket*)ptr;
	return recv(b->sd, buf, bufsiz, 0);
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

#endif/*KONOHA_API__WIN32*/
