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

#include<konoha.h>

#ifdef KNH_USING_SOCKET
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

#ifdef KNH_USING_SOCKET

static
knh_io_t knh_socket_open(Ctx *ctx, char *ip_or_host, int port)
{
	struct in_addr addr = {0};
	struct hostent	*host;
	struct sockaddr_in	server = {0};
	int sd = -1;

	server.sin_family = AF_INET;

	if ((addr.s_addr = inet_addr(ip_or_host)) == -1) {
		host = gethostbyname(ip_or_host);
		if (host == NULL) {
			KNH_PERRNO(ctx, "Socket!!", "gethostbyname");
			//KNH_THROWf(ctx, "Socket!!: no such host %s", ip_or_host);
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
	return (knh_io_t)sd;
}

/* ------------------------------------------------------------------------ */
/* 'ip:127.0.0.1:80' */
/* 'host:localhost:80' */
/* 'socket:localhost:80' */

static
knh_io_t knh_iodrv_open__SOCKET(Ctx *ctx, InputStream *in, OutputStream *out, knh_bytes_t file, char *mode)
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

	knh_io_t sd = knh_socket_open(ctx, host_or_ip, port);
	if(sd != -1) {

	}
	return sd;
}

/* ------------------------------------------------------------------------ */

static
knh_int_t knh_iodrv_read__SOCKET(Ctx *ctx, knh_io_t sd, char *buf, size_t bufsiz)
{
	ssize_t ssize = recv((int)sd, buf, bufsiz, 0);
	return ssize;
}

/* ------------------------------------------------------------------------ */

static
knh_int_t knh_iodrv_write__SOCKET(Ctx *ctx, knh_io_t sd, char *buf, size_t bufsiz)
{
	ssize_t ssize = send((int)sd, buf, bufsiz, 0);
	return ssize;
}

/* ------------------------------------------------------------------------ */

static
void knh_iodrv_close__SOCKET(Ctx *ctx, knh_io_t sd)
{
	close((int)sd);
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

#endif/*KNH_USING_SOCKET*/

/* ======================================================================== */
/* [Socket] */

typedef struct {
	knh_socket_t sd;
	int port;
	struct knh_InputStream_t  *in;
	struct knh_OutputStream_t *out;
} knh_SocketGlue_t;

static
void knh_SocketGlue_free(Ctx *ctx, Glue *glue)
{

}

/* ------------------------------------------------------------------------ */
/* @method Socket Socket.new(String host, int port); */

METHOD Socket_new(Ctx *ctx, knh_sfp_t *sfp)
{
  knh_SocketGlue_t *g = KNH_MALLOC(ctx, sizeof(knh_SocketGlue_t));
  knh_Glue_init(ctx, sfp[0].glue, g, knh_SocketGlue_free);
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
  KNH_INITv(g->urn, sfp[1].o);
  g->port = (int)sfp[2].ivalue;
  g->sd = knh_socket_open(ctx, ip_or_host, port);
  if(sd != -1) {
    KNH_INITv(g->in, new_InputStream(ctx, g->urn, g->sd, DRIVERS__sockin));
    KNH_INITv(g->out, new_OutputStream(ctx, g->urn, g->sd, DRIVERS__sockout));
  }
  else {
    KNH_INITv(g->in, konoha_getDefaultValue(ctx, CLASS_InputStream));
    KNH_INITv(g->out, konoha_getDefaultValue(ctx, CLASS_OutputStream));
  }
  KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ------------------------------------------------------------------------ */
/* @method InputStream Socket.getInputStream() */

METHOD Socket_getInputStream(Ctx *ctx, knh_sfp_t *sfp)
{
  knh_SocketGlue_t *g = (knh_SocketGlue_t)sfp[0].glue;
  if(g != NULL) {
    KNH_RETURN(ctx, sfp, g->in);
  }
  else {
    KNH_RETURN(ctx, sfp, konoha_getDefaultValue(ctx, CLASS_InputStream));
  }
}

/* ------------------------------------------------------------------------ */
/* @method OutputStream Socket.getOutputStream() */

METHOD Socket_getOutputStream(Ctx *ctx, knh_sfp_t *sfp)
{
  knh_SocketGlue_t *g = (knh_SocketGlue_t)sfp[0].glue;
  if(g != NULL) {
    KNH_RETURN(ctx, sfp, g->out);
  }
  else {
    KNH_RETURN(ctx, sfp, konoha_getDefaultValue(ctx, CLASS_OutputStream));
  }
}

/* ------------------------------------------------------------------------ */
/* @method void Socket.close() */

METHOD Socket_close(Ctx *ctx, knh_sfp_t *sfp)
{
  knh_SocketGlue_t *g = (knh_SocketGlue_t)sfp[0].glue;
  if(g != NULL && g->sd != -1) {
    knh_InputStream_close(ctx, g->in);
    knh_OutputStream_close(ctx, g->out);
    knh_socket_close(ctx, g->sd);
    g->sd = -1;
  }
  KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Socket.isClose() */

METHOD Socket_isClose(Ctx *ctx, knh_sfp_t *sfp)
{
  knh_SocketGlue_t *g = (knh_SocketGlue_t)sfp[0].glue;
  KNH_RETURN_Boolean(!(g != NULL && g->sd != -1));
}

/* ======================================================================== */
/* [KNHAPI] */

int init(Ctx *ctx)
{
  KNH_NOTICE(ctx, "loading socket..");
#ifdef KNH_USING_SOCKET
  konoha_addIODriver(ctx, NULL, &IO__SOCKET);
  konoha_addIODriver(ctx, "ip", &IO__SOCKET);
  konoha_addIODriver(ctx, "host", &IO__SOCKET);
#endif
  return 1;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
