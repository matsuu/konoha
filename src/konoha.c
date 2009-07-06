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

#include<konoha.h>

#ifdef KNH_USING_BTRON
#include <basic.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

int
#ifdef KNH_USING_BTRON
main_unix(int argc, char **argv)
#else
main(int argc, char **argv)
#endif
{
	konoha_t konoha = konoha_open(4096);
	int n = konoha_parseopt(konoha, argc, argv);
	if(argc - n == 0) {
		//package_init(konoha.ctx);
		konoha_shell(konoha);
	}
	else {
		konoha_read(konoha, argv[n]);
		konoha_main(konoha, argc - n, argv + n);
	}
	konoha_close(konoha);
	return 0;
}

#ifdef KNH_USING_BTRON
int main(int argc, TC** argv)
{
    char buf[4096];
    char* argv_euc[256];
    int i, pos, len;

    pos = 0;
    for (i = 0; i < argc; i++) {
        argv_euc[i] = buf + pos;
        len = tcstoeucs(argv_euc[i], argv[i]);
        if (len >= 0) {
            pos += (len + 1);
        }
        else {
            buf[pos] = '\0';
            pos++;
        }
    }
    argv_euc[argc] = NULL;

    return main_unix(argc, argv_euc);
}
#endif

#ifdef __cplusplus
}
#endif
