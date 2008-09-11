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

#define _EXPT_newid            ((knh_expt_t)0)
#define _EXPT_Exception        ((knh_expt_t)1)
#define _EXPT_NoSuchException  ((knh_expt_t)2)

#define _knh_Exception_eid(o)   (o)->eid

/* ======================================================================== */
/* [structs] */

void
knh_Exception_struct_init(Ctx *ctx, knh_Exception_struct *b, int init, Object *cs)
{
	b->eid  = 1;
	b->flag = 0;
	KNH_INITv(b->message, TS_EMPTY);
	KNH_INITv(b->bag, KNH_NULL);
	KNH_INITv(b->traces, KNH_NULL);
	b->file = "";
	b->line = 0;
}

/* ------------------------------------------------------------------------ */

#define _knh_Exception_struct_copy   NULL

/* ------------------------------------------------------------------------ */

#define _knh_Exception_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void
knh_Exception_struct_traverse(Ctx *ctx, knh_Exception_struct *b, f_traverse gc)
{
	gc(ctx, UP(b->message));
	gc(ctx, b->bag);
	gc(ctx, UP(b->traces));
	//if(isSWEEP(gc)) KNH_FREE(something);
}

/* ======================================================================== */
/* [constructors] */

/* @method Exception! Exception.new(String! e, String msg, Object bag) */

static
Exception* knh_Exception_new(Ctx *ctx, Exception *o, String *e, String *msg, Object *bag)
{
	DP(o)->eid  = EXPT_Exception; //knh_texpt_forname(ctx, knh_String_tobytes(e), EXPT_Exception);
	//DEBUG("eid=%d", DP(o)->eid);
	DP(o)->flag = 0; // knh_texpt_flag(DP(o)->eid);
	if(IS_NULL(msg)) {
		KNH_SETv(ctx, DP(o)->message, e);
	}
	else {
		knh_wbuf_t cb = knh_Context_wbuf(ctx);
		knh_write(ctx, cb.w, knh_String_tobytes(e));
		knh_putc(ctx, cb.w, ':');
		knh_putc(ctx, cb.w, ' ');
		knh_write(ctx, cb.w, knh_String_tobytes(msg));
		KNH_SETv(ctx, DP(o)->message, new_String__wbuf(ctx, cb));
	}
	KNH_SETv(ctx, DP(o)->bag, bag);
	return o;
}

/* ------------------------------------------------------------------------ */

Exception* new_Exception(Ctx *ctx, String *msg)
{
	knh_Exception_t* o =
		(knh_Exception_t*)new_Object_malloc(ctx, FLAG_Exception, CLASS_Exception, sizeof(knh_Exception_struct));
	knh_Exception_struct_init(ctx, DP(o), 0, NULL);
	knh_Exception_new(ctx, o, msg, (String*)KNH_NULL, (Object*)KNH_NULL);
	return o;
}

/* ------------------------------------------------------------------------ */

Exception* new_Exception__b(Ctx *ctx, knh_bytes_t msg)
{
	knh_Exception_t* o =
		(knh_Exception_t*)new_Object_malloc(ctx, FLAG_Exception, CLASS_Exception, sizeof(knh_Exception_struct));
	knh_Exception_struct_init(ctx, DP(o), 0, NULL);
	knh_Exception_new(ctx, o, new_String(ctx, msg, NULL), (String*)KNH_NULL, (Object*)KNH_NULL);
	return o;
}

#define _new_Exception__s(ctx, s)     new_Exception__b(ctx, B(s))

/* ------------------------------------------------------------------------ */

Exception* new_Exception__Nue(Ctx *ctx, knh_Nue_t *nue)
{
	knh_Exception_t* o =
		(knh_Exception_t*)new_Object_malloc(ctx, FLAG_Exception, CLASS_Exception, sizeof(knh_Exception_struct));
	knh_Exception_struct_init(ctx, DP(o), 0, NULL);
	if(nue->orign == NULL) {
		knh_Exception_new(ctx, o, new_String(ctx, B((char*)nue->str), NULL), (String*)KNH_NULL, (Object*)KNH_NULL);
	}
	else {
		knh_Exception_new(ctx, o, (String*)nue->orign, (String*)KNH_NULL, (Object*)KNH_NULL);
	}
	return o;
}

/* ======================================================================== */
/* [file,line] */


#ifdef __cplusplus
}
#endif
