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

/* ======================================================================== */
/* [constructor] */

/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [method] */

/* ------------------------------------------------------------------------ */
/* @method InputStream! System.getIn() */

METHOD knh__System_getIn(Ctx *ctx, Object **sfp)
{
	VM_RET(ctx, ((Context*)ctx)->in);	
}

/* ------------------------------------------------------------------------ */
/* @method void System.setIn(InputStream input) */

METHOD knh__System_setIn(Ctx *ctx, Object **sfp)
{
	if(IS_NULL(sfp[1])) {
		KNH_SETv(ctx, ((Context*)ctx)->in, new_InputStream__NULL(ctx));
	}
	else {
		KNH_SETv(ctx, ((Context*)ctx)->in, sfp[1]);
	}		
	VM_RET_VOID(ctx);
}

/* ------------------------------------------------------------------------ */
/* @method OutputStream! System.getOut() */

METHOD knh__System_getOut(Ctx *ctx, Object **sfp)
{
	VM_RET(ctx, ((Context*)ctx)->out);	
}

/* ------------------------------------------------------------------------ */
/* @method void System.setOut(OutputStream out) */

METHOD knh__System_setOut(Ctx *ctx, Object **sfp)
{
	if(IS_NULL(sfp[1])) {
		KNH_SETv(ctx, ((Context*)ctx)->out, new_OutputStream__NULL(ctx));
	}
	else {
		KNH_SETv(ctx, ((Context*)ctx)->out, sfp[1]);
	}		
	VM_RET_VOID(ctx);
}

/* ------------------------------------------------------------------------ */
/* @method OutputStream! System.getErr() */

METHOD knh__System_getErr(Ctx *ctx, Object **sfp)
{
	VM_RET(ctx, ((Context*)ctx)->err);	
}

/* ------------------------------------------------------------------------ */
/* @method void System.setErr(OutputStream out) */

METHOD knh__System_setErr(Ctx *ctx, Object **sfp)
{
	if(IS_NULL(sfp[1])) {
		KNH_SETv(ctx, ((Context*)ctx)->err, new_OutputStream__NULL(ctx));
	}
	else {
		KNH_SETv(ctx, ((Context*)ctx)->err, sfp[1]);
	}		
	VM_RET_VOID(ctx);
}

/* ======================================================================== */
/* [mapping] */

/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
