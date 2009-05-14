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

//static Object *fiboMethod = NULL;
//
///* ------------------------------------------------------------------------ */
///* @method Int! Script.initfibo() */
//
//METHOD knh__Script_initfibo(Ctx *ctx, knh_sfp_t *sfp)
//{
//	fiboMethod = (Object*)knh_Class_getMethod(ctx, CLASS_Script, METHODN_fibo);
//	KNH_ASSERT(IS_Method(fiboMethod));
//}
//
//
///* ------------------------------------------------------------------------ */
///* @method Int! Script.fibo(Int! n) */
//
//METHOD knh__Script_fibo(Ctx *ctx, knh_sfp_t *sfp)
//{
//	JIT_SETESP(ctx, 2);
//	JIT_iLTn(ctx, 2, 1, 3);
//	JIT_bJIFF(ctx, NPC, L_JUMP, 2);
//	JIT_RETo(ctx, -1, ctx->share->tInt[1  - KNH_TINT_MIN]);
//	L_JUMP:;
//	JIT_iSUBn(ctx, 5, 1, 1);
//	JIT_FCALL(ctx, 3, 3, 0, fiboMethod);
//	JIT_iSUBn(ctx, 6, 1, 2);
//	JIT_FCALL(ctx, 4, 3, 0, fiboMethod);
//	JIT_iADD(ctx, -1, 3, 4);
//	JIT_RET(ctx);
//}

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

#ifdef __cplusplus
}
#endif
