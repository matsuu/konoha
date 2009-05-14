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
/* [macros] */

//#define _knh_Iterator_cid(it)           DP(it)->cid
//#define _DP(it)->source        DP(it)->source
//#define _DP(it)->pos           DP(it)->pos
//#define _DP(it)->pos = , p)     DP(it)->pos = p
//#define _knh_Iterator_ref(it)           DP(it)->ref

/* ------------------------------------------------------------------------ */
/* [private] */

static
ITRNEXT knh_fitrnext_end(Ctx *ctx, knh_sfp_t *sfp, int n)
{
	KNH_ITREND(ctx, sfp, n);
}

/* ------------------------------------------------------------------------ */

void knh_Iterator_close(Ctx *ctx, Iterator *it)
{
	KNH_ASSERT(IS_bIterator(it));
	DP(it)->fnext = knh_fitrnext_end;
	it->fnext_1   = knh_fitrnext_end;
}

/* ======================================================================== */
/* [constructors] */

Iterator* new_Iterator(Ctx *ctx, knh_class_t p1, Any *source, knh_fitrnext fnext)
{
	knh_class_t cid = knh_class_Iterator(ctx, p1);
	Iterator *o = (Iterator*)new_Object_init(ctx, FLAG_Iterator, cid, 0);
	if(IS_NULL(source)) fnext = knh_fitrnext_end;
	if(fnext != NULL) DP(o)->fnext = fnext;
	KNH_SETv(ctx, DP(o)->source, source);
	o->fnext_1 = DP(o)->fnext;
	return o;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
