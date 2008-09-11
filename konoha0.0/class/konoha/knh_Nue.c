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
/* [macros] */

#define _IS_NULL(o)          (((Object*)o)->h.cid == CLASS_Nue)
#define _IS_NOTNULL(o)       (((Object*)o)->h.cid != CLASS_Nue)


/* ======================================================================== */
/* [constructors] */

/* ------------------------------------------------------------------------ */

Object *new_Nue(Ctx *ctx, String *msg)
{
	KNH_ASSERT(IS_String(msg));
	knh_Nue_t *o = (knh_Nue_t*)new_PObject0(ctx, FLAG_Nue, CLASS_Nue, CLASS_Nue);
	KNH_INITv(o->orign, msg);
	o->str = (knh_uchar_t*)knh_String_tochar(msg);
	o->size = knh_String_strlen(msg);
	return (Object*)o;
}

#define _new_Nue__b(ctx, txt)   new_Nue(ctx, new_String(ctx, txt, NULL));
#define _new_Nue__s(ctx, txt)   new_Nue(ctx, new_String(ctx, B(txt), NULL));

/* ------------------------------------------------------------------------ */

Object *knh_Nue_fdefault(Ctx *ctx, knh_class_t cid)
{
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */

int knh_Nue_compareTo(Nue *o, Nue *o2)
{
	if(o2->h.cid == CLASS_Nue) {
		return 0;
	}
	else {
		return -1;
	}
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
