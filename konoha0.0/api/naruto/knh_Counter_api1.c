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
/* @method Counter! Counter.new() */

METHOD knh__Counter_new(Ctx *ctx, Object **sfp)
{
	((knh_Counter*)sfp[0])->count = 0;
	METHOD_RETURN(ctx, sfp, sfp[0]);
}

/* ======================================================================== */
/* [method] */

/* ------------------------------------------------------------------------ */
/* @method void Counter.count() */

METHOD knh__Counter_count(Ctx *ctx, Object **sfp)
{
	((knh_Counter*)sfp[0])->count++;
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

/* ------------------------------------------------------------------------ */
/* @method Int! Counter.getCount() */

METHOD knh__Counter_getCount(Ctx *ctx, Object **sfp)
{
	Int *c = new_Int(ctx, ((knh_Counter*)sfp[0])->count);
	METHOD_RETURN(ctx, sfp, c);
}

/* ------------------------------------------------------------------------ */
/* @method void Counter.reset() */

METHOD knh__Counter_reset(Ctx *ctx, Object **sfp)
{
	((knh_Counter*)sfp[0])->count++;
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [mapping] */

/* ------------------------------------------------------------------------ */
/* @map Counter Int! */

Object* knh_Counter_Int(Ctx *ctx, Object *self, MapMap *map)
{
	return new_Int(ctx, ((Counter*)self)->count);
}

/* ------------------------------------------------------------------------ */
/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */
/* @method void Counter.%s(OutputStream w, Any m) */

void knh_Counter__s(Ctx *ctx, Counter *b, OutputStream *w, Any *m)
{
	knh_write__i(ctx, w, b->count);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
