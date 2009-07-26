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

/* ************************************************************************ */

#include"commons.h"


/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */

/* ------------------------------------------------------------------------ */
/* @method void Script.changeChannel(Int! ch) */

METHOD knh__Script_changeChannel(Ctx *ctx, knh_sfp_t *sfp)
{
	fprintf(stdout, "switching channel to %d..\n", (int)sfp[1].ivalue);
	konoha_throwSecurityException();
}

/* ------------------------------------------------------------------------ */
/* @method void Script.hook(String! funcname) */

METHOD knh__Script_hook(Ctx *ctx, knh_sfp_t *sfp)
{
	char *funcname = knh_String_tochar(sfp[1].s);
	fprintf(stdout, "hooking security point at %s\n", funcname);
}

/* ------------------------------------------------------------------------ */

#if defined(KNHX_API)
/**
  regist C function to Method.
  @param method  method name,types... like this -> "void System.echo(String str)"
  @param func    function pointer.  that func must have normal library API
                 METHOD funcname (Ctx *ctx, knh_sfp_t* ){}
  @return true/false
 */
//KNHAPI(int) knh_registLocalFunction(konoha_t konoha, char* method, knh_fmethod func)
//{
//    Ctx *ctx = konoha.ctx;
//    konoha_setCurrentContext(ctx);
//    knh_sfp_t *lsfp = KNH_LOCAL(ctx);
//
//    knh_cwb_t cwb = new_cwb(ctx);
//    knh_Bytes_write(ctx, cwb.ba, B(method));
//    InputStream *in = new_BytesInputStream(ctx, cwb.ba, cwb.pos, knh_Bytes_size(cwb.ba));
//
//    KNH_LPUSH(ctx, in);
//    knh_InputStream_setEncoding(ctx, in, KNH_ENC);
//
//    Stmt *stmt = knh_InputStream_parseStmt(ctx, in, 0/*isData*/);
//    KNH_LPUSH(ctx, stmt);
//
//    NameSpace *ns = knh_getCurrentNameSpace(ctx);
//    knh_Stmt_compile(ctx, stmt, DP(ns)->nsname, 1);
//
//    knh_methodn_t mn = knh_Method_fromName(ctx, method);
//    knh_Method_syncfunc(mtd, func);
//    KNH_LOCALBACK(ctx, lsfp);
//    return;
//}

#endif

/* ------------------------------------------------------------------------ */
/* [pacage test] */

/* ------------------------------------------------------------------------ */

int package_init(Ctx *ctx)
{
    return 1;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
