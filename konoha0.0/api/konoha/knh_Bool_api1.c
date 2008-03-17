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
/* @method Bool! Bool.opEq(Any another) */

METHOD knh__Bool_opEq(Ctx *ctx, Object **sfp)
{
	if(IS_TRUE(sfp[0])) {
		if(IS_TRUE(sfp[1])) {
			METHOD_RETURN(ctx, sfp, KNH_TRUE);
		}
		else {
			METHOD_RETURN(ctx, sfp, KNH_FALSE);
		}
	}
	else {
		if(IS_TRUE(sfp[1])) {
			METHOD_RETURN(ctx, sfp, KNH_FALSE);
		}
		else {
			METHOD_RETURN(ctx, sfp, KNH_TRUE);
		}
	}
}

/* ------------------------------------------------------------------------ */
/* @method Bool! Bool.opNeq(Any another) */

METHOD knh__Bool_opNeq(Ctx *ctx, Object **sfp)
{
	if(IS_TRUE(sfp[0])) {
		if(IS_TRUE(sfp[1])) {
			METHOD_RETURN(ctx, sfp, KNH_FALSE);
		}
		else {
			METHOD_RETURN(ctx, sfp, KNH_TRUE);
		}
	}
	else {
		if(IS_TRUE(sfp[1])) {
			METHOD_RETURN(ctx, sfp, KNH_TRUE);
		}
		else {
			METHOD_RETURN(ctx, sfp, KNH_FALSE);
		}
	}
}

/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [mapping] */

/* ------------------------------------------------------------------------ */
/* @map[STATIC] Bool String! */

Object* knh_Bool_String(Ctx *ctx, Object *self, MapMap *map)
{
	if(IS_TRUE(self)) {
		return knh_String_cTRUE();
	}
	return knh_String_cFALSE();
}

/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */
/* @method void Bool.%s(OutputStream w, Any m) */

void knh_Bool__s(Ctx *ctx, Bool *b, OutputStream *w, Any *m)
{
	if(IS_TRUE(b)) knh_write(ctx, w, STEXT("true"));
	else knh_write(ctx, w, STEXT("false")); 
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
