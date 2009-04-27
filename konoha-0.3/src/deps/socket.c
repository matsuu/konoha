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

#ifdef KNH_USING_POSIX
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#define KNH_USING_NOAPI 1

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [SOCKET] */

KNHAPI(knh_intptr_t) knh_socket_open(Ctx *ctx, char *ip_or_host, int port)
{
#ifdef KNH_USING_POSIX
#undef KNH_USING_NOAPI
	struct in_addr addr = {0};
	struct hostent	*host;
	struct sockaddr_in	server = {0};
	knh_intptr_t sd = -1;

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
	return sd;
#endif
#ifdef KNH_USING_NOAPI
	return -1;
#endif

}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_socket_close(Ctx *ctx, knh_intptr_t sd)
{
#ifdef KNH_USING_POSIX
	close((int)sd);
#endif
#ifdef KNH_USING_NOAPI
	return -1;
#endif
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
