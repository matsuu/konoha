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
knh_Exception_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Exception *b = (Exception*)s;
	b->eid  = 1;
	b->flag = 0;
	KNH_INITv(b->message, knh_String_EMPTY());
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
knh_Exception_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Exception *b = (Exception*)s;
	gc(ctx, b->message);
	gc(ctx, b->bag);
	gc(ctx, b->traces);
	//if(isSWEEP(gc)) knh_free(something);
}

/* ======================================================================== */
/* [constructors] */

/* @method Exception! Exception.new(String! e, String msg, Object bag) */

Exception* knh_Exception_new(Ctx *ctx, Exception *b, String *e, String *msg, Object *bag)
{
	b->eid  = knh_texpt_forname(ctx, knh_String_tobytes(e), EXPT_Exception);
	//DEBUG("eid=%d", b->eid);
	b->flag = knh_texpt_flag(b->eid);
	if(IS_NULL(msg)) {
		KNH_SETv(ctx, b->message, e);
	}
	else {
		knh_buffer_t cb = knh_Context_buffer(ctx);
		knh_write(ctx, cb.w, knh_String_tobytes(e));
		knh_putc(ctx, cb.w, ':');
		knh_putc(ctx, cb.w, ' ');
		knh_write(ctx, cb.w, knh_String_tobytes(msg));
		KNH_SETv(ctx, b->message, new_String__buffer(ctx, CLASS_String, cb));
	}
	KNH_SETv(ctx, b->bag, bag);
	return b;
}

/* ------------------------------------------------------------------------ */

INLINE
Exception* new_Exception(Ctx *ctx, String *msg)
{
	Exception* b = (Exception*)knh_Object_malloc(ctx, CLASS_Exception);
	knh_Exception_struct_init(ctx, (Struct*)b, 0, NULL);
	knh_Exception_new(ctx, b, msg, KNH_NULL, KNH_NULL);
	return b;
}

/* ------------------------------------------------------------------------ */

INLINE
Exception* new_Exception__b(Ctx *ctx, knh_bytes_t msg)
{
	Exception* b = (Exception*)knh_Object_malloc(ctx, CLASS_Exception);
	knh_Exception_struct_init(ctx, (Struct*)b, 0, NULL);
	knh_Exception_new(ctx, b, new_String__fast(ctx, CLASS_String, msg), KNH_NULL, KNH_NULL);
	return b;
}

/* ------------------------------------------------------------------------ */

INLINE
Exception* new_Exception__Nue(Ctx *ctx, Nue *nue)
{
	Exception* b = (Exception*)knh_Object_malloc(ctx, CLASS_Exception);
	knh_Exception_struct_init(ctx, (Struct*)b, 0, NULL);
	if(knh_Nue_isObjectText(nue)) {
		knh_Exception_new(ctx, b, (String*)nue->msg, KNH_NULL, nue);
	}
	else{
		knh_Exception_new(ctx, b, new_String__fast(ctx, CLASS_String, B(nue->msg)), KNH_NULL, nue);
	}
	return b;
}

/* ======================================================================== */
/* [file,line] */


/* ======================================================================== */
/* [movabletext] */

/* ------------------------------------------------------------------------ */
/* @method void Exception.%s(OutputStream w, Any m) */

void knh_Exception__s(Ctx *ctx, Exception *b, OutputStream *w, Any *m)
{
	DEBUG_ASSERT(IS_Exception(b));
	knh_write(ctx, w, knh_String_tobytes(knh_texpt_name(b->eid)));
}

/* ------------------------------------------------------------------------ */
/* @method void Exception.%dump(OutputStream w, Any m) */

void knh_Exception__dump(Ctx *ctx, Exception *b, OutputStream *w, Any *m)
{
	knh_write__s(ctx, w, "---- ---- 8< 8< ---- ---- >8 >8 ---- ----");
	knh_println(ctx, w, STEXT(""));
	if(b->line == 0) {
		knh_printf(ctx, w, "(%s:%d) ", b->file, b->line);
	}
	knh_write(ctx, w, knh_String_tobytes(b->message));
	knh_println(ctx, w, STEXT(""));
	if(IS_Array(b->traces)) {
		knh_int_t i;
		for(i = 0; i < knh_Array_size(b->traces); i++) {
			knh_write(ctx, w, STEXT("  at "));
			knh_format(ctx, w, METHODN__s, knh_Array_n(b->traces, i), KNH_NULL);
			knh_println(ctx, w, STEXT(""));
		}
	}		
	knh_write__s(ctx, w, "---- ---- 8< 8< ---- ---- >8 >8 ---- ----");
	knh_println(ctx, w, STEXT(""));	
}	

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
