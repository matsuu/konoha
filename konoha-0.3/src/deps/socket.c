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
#define KNH_USING_NOAPI 1

#ifdef KNH_USING_POSIX
#undef KNH_USING_NOPAI
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [SOCKET] */

KNHAPI(knh_intptr_t) knh_socket_open(Ctx *ctx, char *ip_or_host, int port)
{
#ifdef KNH_USING_POSIX
	struct in_addr addr = {0};
	struct hostent	*host;
	struct sockaddr_in	server = {0};
	knh_intptr_t sd = -1;

	server.sin_family = AF_INET;

	if ((addr.s_addr = inet_addr(ip_or_host)) == -1) {
		host = gethostbyname(ip_or_host);
		if (host == NULL) {
			KNH_PERRNO(ctx, "Socket!!", "gethostbyname");
			return -1;
		}
		memcpy(&addr, (struct in_addr *)*host->h_addr_list, sizeof(struct in_addr));
	}
	server.sin_family = AF_INET;
	server.sin_addr = addr;
	server.sin_port = htons(port);

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		KNH_PERRNO(ctx, "Socket!!", "socket");
		return -1;
	}
	if (connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
		KNH_PERRNO(ctx, "Socket!!", "connect");
		return -1;
	}
	return sd;
#endif/*KNH_USING_POSIX*/
#ifdef KNH_USING_WINDOWS
	return -1;
#endif
#ifdef KNH_USING_NOAPI
	return -1;
#endif
}

/* ------------------------------------------------------------------------ */

KNHAPI(int) knh_socket_send(Ctx *ctx, knh_intptr_t sd, char *buf, size_t bufsiz, int flags)
{
	int res = -1;
#ifdef KNH_USING_POSIX
	res = send(sd, buf, bufsiz, flags);
#endif/*KNH_USING_POSIX*/
#ifdef KNH_USING_WINDOWS
	res = send((SOCKET)sd, buf, bufsiz, flags);
#endif
	if(res == -1) {
		KNH_PERRNO(ctx, "Socket!!", "send");
	}
	return res;
}
/* ------------------------------------------------------------------------ */

KNHAPI(int) knh_socket_recv(Ctx *ctx, knh_intptr_t sd, char *buf, size_t bufsiz, int flags)
{
	int res = -1;
#ifdef KNH_USING_POSIX
	res = recv(sd, buf, bufsiz, flags);
#endif/*KNH_USING_POSIX*/
#ifdef KNH_USING_WINDOWS
	res = recv((SOCKET)sd, buf, bufsiz, flags);
#endif
	if(res == -1) {
		KNH_PERRNO(ctx, "Socket!!", "recv");
	}
	return res;
}

/* ------------------------------------------------------------------------ */

KNHAPI(int) knh_socket_close(Ctx *ctx, knh_intptr_t sd)
{
#ifdef KNH_USING_POSIX
	return close((int)sd);
#endif/*KNH_USING_POSIX*/
#ifdef KNH_USING_WINDOWS
	return closesocket((SOCKET)sd);
#endif
#ifdef KNH_USING_NOAPI
	return -1;
#endif
}


/* ------------------------------------------------------------------------ */
/* [IO DRIVER] */

/* 'ip:127.0.0.1:80' */
/* 'host:localhost:80' */
/* 'socket:localhost:80' */

static
knh_io_t knh_iodrv_open__SOCKET(Ctx *ctx, knh_bytes_t file, char *mode)
{
	knh_bytes_t urn = knh_bytes_skipscheme(file);
	knh_index_t loc = knh_bytes_rindex(urn, ':');
	int port = 80; /* default */
	if(loc != -1) {
		port = (int)knh_bytes_toint(knh_bytes_last(urn, loc+1));
		urn = knh_bytes_first(urn, loc);
	}
	char host_or_ip[128];
	knh_format_bytes(host_or_ip, sizeof(host_or_ip), urn);

	KNH_WARNING(ctx, "opening socket host='%s', port=%d", host_or_ip, port);
	KNH_SECURE(ctx);
	return (knh_io_t)knh_socket_open(ctx, host_or_ip, port);
}

/* ------------------------------------------------------------------------ */

static
knh_intptr_t knh_iodrv_read__SOCKET(Ctx *ctx, knh_io_t sd, char *buf, size_t bufsiz)
{
	return knh_socket_recv(ctx, (knh_intptr_t)sd, buf, bufsiz, 0);
}

/* ------------------------------------------------------------------------ */

static
knh_intptr_t knh_iodrv_write__SOCKET(Ctx *ctx, knh_io_t sd, char *buf, size_t bufsiz)
{
	return knh_socket_send(ctx, (knh_intptr_t)sd, buf, bufsiz, 0);
}

/* ------------------------------------------------------------------------ */

static
void knh_iodrv_close__SOCKET(Ctx *ctx, knh_io_t sd)
{
	knh_socket_close(ctx, (knh_intptr_t)sd);
}

/* ------------------------------------------------------------------------ */
/* @data */

static knh_iodrv_t IO__SOCKET = {
	KNH_DRVAPI_TYPE__IO, "socket",
	1024,
	knh_iodrv_open__SOCKET,
	knh_iodrv_read__SOCKET,
	knh_iodrv_write__SOCKET,
	knh_iodrv_close__SOCKET
};

/* ------------------------------------------------------------------------ */

knh_iodrv_t *konoha_getSocketDriver()
{
	return &IO__SOCKET;
}


/* ======================================================================== */
/* [KNHAPI] */

void KNHINIT init_SocketDriver(Ctx *ctx)
{
	konoha_addIODriver(ctx, NULL, &IO__SOCKET);
	konoha_addIODriver(ctx, "ip", &IO__SOCKET);
	konoha_addIODriver(ctx, "host", &IO__SOCKET);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
