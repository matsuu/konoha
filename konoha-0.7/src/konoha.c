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

#include<konoha.h>

#ifdef __cplusplus
extern "C" {
#endif

int
main(int argc, char **argv)
{
#if defined(KNH_USING_BTRON)
    char buf[4096];
    char* args[256];
    int i, pos = 0, len;

    for (i = 0; i < argc; i++) {
        args[i] = buf + pos;
        len = tcstoeucs(args[i], (TC*)argv[i]);
        if (len >= 0) {
            pos += (len + 1);
        }
        else {
            buf[pos] = '\0';
            pos++;
        }
    }
    args[argc] = NULL;

#else
    char** args = (char**) argv;
#endif
    konoha_t konoha = konoha_open(4096);
    int n = konoha_parseopt(konoha, argc, args);
    if(argc - n == 0) {
        //package_init(konoha.ctx);
        konoha_shell(konoha);
    }
    else {
        if(konoha_loadScript(konoha, args[n]) != -1) {
            konoha_runMain(konoha, argc - n, args + n);
        }
        else {
            fprintf(stderr, "[konoha] cannot open: %s\n", args[n]);
        }
    }
    konoha_close(konoha);
    return 0;
}


#ifdef __cplusplus
}
#endif
