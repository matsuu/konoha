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

#ifdef KONOHA_ON_LKM
#undef KNH_USING_POSIX
#endif

#ifdef KNH_USING_WINDOWS
#include <windows.h>
#include <winsock2.h>
#endif

#ifdef KNH_USING_POSIX
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#ifdef KNH_USING_BTRON
#include <btron/bsocket.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [SOCKET] */

KNHAPI(knh_intptr_t) knh_socket_open(Ctx *ctx, char *ip_or_host, int port, int isThrowable)
{
#if defined(KNH_USING_POSIX)
#if defined(KNH_USING_WINDOWS)
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,0), &wsaData);
#endif
	struct in_addr addr = {0};
	struct hostent	*host;
	struct sockaddr_in	server = {0};
	knh_intptr_t sd = -1;

	server.sin_family = AF_INET;

	if ((addr.s_addr = inet_addr(ip_or_host)) == -1) {
		host = gethostbyname(ip_or_host);
		if (host == NULL) {
			KNH_PERRNO(ctx, NULL, "Socket!!", "gethostbyname", isThrowable);
			return -1;
		}
		memcpy(&addr, (struct in_addr *)*host->h_addr_list, sizeof(struct in_addr));
	}
	server.sin_family = AF_INET;
	server.sin_addr = addr;
	server.sin_port = htons(port);

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		KNH_PERRNO(ctx, NULL, "Socket!!", "socket", isThrowable);
		return -1;
	}
	if (connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
		KNH_PERRNO(ctx, NULL, "Socket!!", "connect", isThrowable);
		return -1;
	}
	return sd;
#elif defined(KNH_USING_BTRON)
        char tmp[HBUFLEN];
        struct hostent host;
        struct sockaddr_in server = {0};
        W err, sd;

        err = so_gethostbyname(ip_or_host, &host, tmp);
        if (err < 0) {
            KNH_PERRNO(ctx, NULL, "Socket!!", "gethostbyname", isThrowable);
            return -1;
        }

        server.sin_family = PF_INET;
        memcpy(&(server.sin_addr), host.h_addr, host.h_length);
        server.sin_port = htons(port);

        err = so_socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (err < 0) {
            KNH_PERRNO(ctx, NULL, "Socket!!", "socket", isThrowable);
            return -1;
        }
        sd = err;

        err = so_connect(sd, (struct sockaddr*)&server, sizeof(server));
        if (err < 0) {
            KNH_PERRNO(ctx, NULL, "Socket!!", "connect", isThrowable);
            so_close(sd);
            return -1;
        }
        return (knh_intptr_t)sd;
#else
	return -1;
#endif
}

/* ------------------------------------------------------------------------ */

KNHAPI(int) knh_socket_send(Ctx *ctx, knh_intptr_t sd, char *buf, size_t bufsiz, int flags)
{
	int res = -1;
#if defined(KNH_USING_WINDOWS)
	res = send((SOCKET)sd, buf, bufsiz, flags);
#elif defined(KNH_USING_POSIX)
	res = send(sd, buf, bufsiz, flags);
#elif defined(KNH_USING_BTRON)
        res = so_send(sd, buf, bufsiz, flags);
        if (res < 0) res = -1;
#endif
	if(res == -1) {
		KNH_PERRNO(ctx, NULL, "Socket!!", "send", knh_Context_isStrict(ctx));
	}
	return res;
}
/* ------------------------------------------------------------------------ */

KNHAPI(int) knh_socket_recv(Ctx *ctx, knh_intptr_t sd, char *buf, size_t bufsiz, int flags)
{
	int res = -1;
#if defined(KNH_USING_WINDOWS)
	res = recv((SOCKET)sd, buf, bufsiz, flags);
#elif defined(KNH_USING_POSIX)
	res = recv(sd, buf, bufsiz, flags);
#elif defined(KNH_USING_BTRON)
        res = so_recv(sd, buf, bufsiz, flags);
        if (res < 0) res = -1;
#endif
	if(res == -1) {
		KNH_PERRNO(ctx, NULL, "Socket!!", "recv", knh_Context_isStrict(ctx));
	}
	return res;
}

/* ------------------------------------------------------------------------ */

KNHAPI(int) knh_socket_close(Ctx *ctx, knh_intptr_t sd)
{
#if defined(KNH_USING_WINDOWS)
	return closesocket((SOCKET)sd);
#elif defined(KNH_USING_POSIX)
	return close((int)sd);
#elif defined(KNH_USING_BTRON)
        return so_close(sd);
#else
	return 0;  /* becuase, it wasn't opened. */
#endif
}

/* ------------------------------------------------------------------------ */
/* [IO DRIVER] */

/* 'ip:127.0.0.1:80' */
/* 'host:localhost:80' */
/* 'socket:localhost:80' */

static
knh_io_t knh_iodrv_open__SOCKET(Ctx *ctx, knh_bytes_t file, char *mode, int isThrowable)
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
	DBG_P("opening socket host='%s', port=%d", host_or_ip, port);
	return (knh_io_t)knh_socket_open(ctx, host_or_ip, port, isThrowable);
}

/* ------------------------------------------------------------------------ */

static
void knh_iodrv_init__SOCKET(Ctx *ctx, Object *stream, char *mode)
{
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
	4096,
	knh_iodrv_open__SOCKET,
	knh_iodrv_init__SOCKET,
	knh_iodrv_read__SOCKET,
	knh_iodrv_write__SOCKET,
	knh_iodrv_close__SOCKET
};

/* ------------------------------------------------------------------------ */

knh_iodrv_t *knh_getSocketDriver(void)
{
	return &IO__SOCKET;
}

/* ------------------------------------------------------------------------ */
/* [HTTP DRIVER] */
/* 'ip:127.0.0.1:80' */
/* 'host:localhost:80' */
/* 'socket:localhost:80' */

static
knh_io_t knh_iodrv_open__HTTP(Ctx *ctx, knh_bytes_t url, char *mode, int isThrowable)
{
	char bfscheme[20], bfhost[80];
	char bfuname[20];
	int port = 80;
	knh_bytes_t path;
	knh_bytes_parseURLscheme(url, bfscheme, sizeof(bfscheme));
	knh_bytes_parseURLhost(url, bfhost, sizeof(bfhost));
	knh_bytes_parseURLuname(url, bfuname, sizeof(bfuname));
	knh_bytes_parseURLport(url, &port);
	path = knh_bytes_substringURLpath(url);
	DBG2_P("socket host='%s', port=%d, path='%s'", bfhost, port, path.buf);
	knh_intptr_t sd = knh_socket_open(ctx, bfhost, port, isThrowable);
	if(sd != -1) {
		knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
		knh_bytes_t msg;
		knh_cwb_write(ctx, cwb, STEXT("GET "));
		knh_cwb_write(ctx, cwb, path);
		knh_cwb_write(ctx, cwb, STEXT(" HTTP/1.1\r\n"));
		knh_cwb_write(ctx, cwb, STEXT("Host: "));
		knh_cwb_write(ctx, cwb, B(bfhost));
		knh_cwb_write(ctx, cwb, STEXT("\r\n"));
		knh_cwb_write(ctx, cwb, STEXT("\r\n"));
		msg = knh_cwb_tobytes(cwb);
		knh_socket_send(ctx, sd, (char*)msg.buf, msg.len, 0);
		knh_cwb_subclear(cwb, 0);
	}
	return sd;
}

/* ------------------------------------------------------------------------ */

static
void knh_iodrv_init__HTTP(Ctx *ctx, Object *stream, char *mode)
{
	if(IS_InputStream(stream) && mode[0] != 'h') {
		InputStream *in = (InputStream*)stream;
		knh_sfp_t *esp = ctx->esp + 1;
		do {
			String *s = knh_InputStream_readLine(ctx, in);
			KNH_SETv(ctx, esp[0].o, s);
			DBG2_P("line='%s'", knh_String_tochar(s));
		}while((esp[0].s)->size > 0);
	}
}

/* ------------------------------------------------------------------------ */

static
knh_intptr_t knh_iodrv_read__HTTP(Ctx *ctx, knh_io_t sd, char *buf, size_t bufsiz)
{
	return knh_socket_recv(ctx, (knh_intptr_t)sd, buf, bufsiz, 0);
}

/* ------------------------------------------------------------------------ */

static
knh_intptr_t knh_iodrv_write__HTTP(Ctx *ctx, knh_io_t sd, char *buf, size_t bufsiz)
{
	return 0; //knh_socket_send(ctx, (knh_intptr_t)sd, buf, bufsiz, 0);
}

/* ------------------------------------------------------------------------ */

static
void knh_iodrv_close__HTTP(Ctx *ctx, knh_io_t sd)
{
	knh_socket_close(ctx, (knh_intptr_t)sd);
}

/* ------------------------------------------------------------------------ */
/* @data */

static knh_iodrv_t IO__HTTP = {
	KNH_DRVAPI_TYPE__IO, "http",
	4096,
	knh_iodrv_open__HTTP,
	knh_iodrv_init__HTTP,
	knh_iodrv_read__HTTP,
	knh_iodrv_write__HTTP,
	knh_iodrv_close__HTTP
};

/* ======================================================================== */
/* [KNHAPI] */

void KNHINIT init_SocketDriver(Ctx *ctx)
{
	knh_addIODriver(ctx, NULL, &IO__SOCKET);
	knh_addIODriver(ctx, "ip", &IO__SOCKET);
	knh_addIODriver(ctx, "host", &IO__SOCKET);
	knh_addIODriver(ctx, "http", &IO__HTTP);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
