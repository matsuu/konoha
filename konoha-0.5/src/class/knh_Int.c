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

#define _knh_Int_value(o)      (o)->value

/* ======================================================================== */
/* [constructors] */

KNHAPI(Int*) new_Int(Ctx *ctx, knh_int_t value)
{
	knh_Int_t *b = (knh_Int_t*)new_hObject(ctx, FLAG_Int, CLASS_Int, CLASS_Int);
	b->n.ivalue = value;
	return b;
}

/* ------------------------------------------------------------------------ */

KNHAPI(Int*) new_IntX__fast(Ctx *ctx, knh_class_t cid, knh_int_t value)
{
	knh_Int_t *b = (knh_Int_t*)new_hObject(ctx, FLAG_Int, CLASS_Int, cid);
	b->n.ivalue = value;
	return b;
}

/* ------------------------------------------------------------------------ */

KNHAPI(Int*) new_IntX(Ctx *ctx, knh_class_t cid, knh_int_t value)
{
	ClassSpec *u = (ClassSpec*)ctx->share->ClassTable[cid].cspec;
	KNH_ASSERT(IS_ClassSpec(u));
	if(DP(u)->fichk(u, value)) {
		Int *n = (knh_Int_t*)new_hObject(ctx, FLAG_Int, CLASS_Int, cid);
		n->n.ivalue = value;
		return n;
	}
	else {
		return DP(u)->ivalue;
	}
}

/* ======================================================================== */

knh_int_t knh_IntNULL_toint(Int *v)
{
	if(IS_NULL(v)) {
		return 0;
	}else {
		return v->n.ivalue;
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
