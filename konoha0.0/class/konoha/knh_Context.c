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

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

#ifndef KONOHA_CONTEXT_BUFSIZ
#define KONOHA_CONTEXT_BUFSIZ  4096
#endif

/* ======================================================================== */
/* [macros] */

#define _KNH_STDIN          (((Context*)ctx)->in)
#define _KNH_STDOUT         (((Context*)ctx)->out)
#define _KNH_STDERR         (((Context*)ctx)->err)

/* ------------------------------------------------------------------------ */

Object *knh_Context_fdefault(Ctx *ctx, knh_class_t cid)
{
	return (Object*)ctx;
}

/* ------------------------------------------------------------------------ */

void knh_Context_clearstack(Ctx *ctx)
{
	int i;
	for(i = ctx->ebp - ctx->stack + 1; i < ctx->stacksize - 1; i++) {
		KNH_SETv(ctx, ctx->stack[i].o, KNH_NULL);
	}
}

/* ======================================================================== */
/* [properties] */


#ifdef __cplusplus
}
#endif
