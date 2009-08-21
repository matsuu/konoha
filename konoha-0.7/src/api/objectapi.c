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

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef KNH_CC_METHODAPI

/* ======================================================================== */
/* [Object] */

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Class! Object.getClass() */

static METHOD knh__Object_getClass(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN(ctx, sfp, new_Class(ctx, (sfp[0].o)->h.cid));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.isNull() */

static METHOD knh__Object_isNull(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, IS_NULL(sfp[0].o));
}

/* ------------------------------------------------------------------------ */
/* @method[CONST|NULLBASE] Boolean! Object.isNotNull() */

static METHOD knh__Object_isNotNull(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, IS_NOTNULL(sfp[0].o));
}




/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [method] */

/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [mapping] */


#endif/* KNH_CC_METHODAPI*/

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
