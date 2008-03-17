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

//#define _Null                knh_Nue_NULL()
#define _IS_NULL(o)          (knh_Object_cid(o) == CLASS_Nue)
#define _IS_NOTNULL(o)       (knh_Object_cid(o) != CLASS_Nue)

//#define _KNH_DONE_IFNULL(w)         if(IS_NULL(w)) return ;
//#define _KNH_RETURN_IFNULL(w,v)     if(IS_NULL(w)) return v;
//#define _KNH_THROW_IFNULL(ctx,w)    if(IS_NULL(w)) knh_konohavm_throwException(ctx, new_Exception__Nue(ctx, w));

/* ======================================================================== */
/* [structs] */

void
knh_Nue_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	Nue *b =  (Nue*)s1;
	b->msg = "Null!!";
}

/* ------------------------------------------------------------------------ */

void
knh_Nue_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
	Nue *b =  (Nue*)s1;
	Nue *b2 = (Nue*)s2;
	if(knh_Nue_isObjectText(b)) {
		KNH_INITv(b2->msg, b->msg);
	}
	else{
		b2->msg = b->msg;
	}
}

/* ------------------------------------------------------------------------ */

knh_int_t 
knh_Nue_struct_compare(Ctx *ctx, Struct *s, Struct *s2) 
{
	return 0;
}

/* ------------------------------------------------------------------------ */

void
knh_Nue_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Nue *b = (Nue*)s;
	if(IS_SWEEP(gc)) {
		if(knh_Nue_isGCHook(b)) {
			knh_Object_refc_inc(b);
			knh_konohavm_throwException(ctx, new_Exception__Nue(ctx, b));
		}
	}
	if(knh_Nue_isObjectText(b)) {
		gc(ctx, b->msg);
	}
}

/* ======================================================================== */
/* [constructors] */

Nue *
new_Nue__STEXT(Ctx *ctx, char *msg)
{
	Nue *b = (Nue*)knh_Object_malloc0(ctx, KNH_FLAG_Nue, CLASS_Nue, sizeof(Nue));
	b->msg = msg;
	return b;
}

/* ------------------------------------------------------------------------ */


Nue *
new_Nue(Ctx *ctx, String *msg)
{
	DEBUG_ASSERT(IS_String(msg));
	Nue *b = (Nue*)knh_Object_malloc0(ctx, KNH_FLAG_Nue, CLASS_Nue, sizeof(Nue));
	knh_Nue_setObjectText(b, 1);
	KNH_INITv(b->msg, msg);
	return b;
}

/* ------------------------------------------------------------------------ */

ObjectNULL *knh_Nue_fvalue(Ctx *ctx, knh_class_t cid)
{
	return KNH_NULL;
}

/* ======================================================================== */
/* [mappings] */

/* @map[STATIC] Nue String! */

Object* knh_Nue_String(Ctx *ctx, Object *self, MapMap *map)
{
	return knh_String_NULL();
}

/* ======================================================================== */
/* [movabletext] */

/* @method void Nue.%s(OutputStream w, Any m) */


void knh_Nue__s(Ctx *ctx, Nue *b, OutputStream *w, Any *m)
{
	knh_write(ctx, w, knh_String_tobytes(knh_String_NULL()));
}


#ifdef __cplusplus
}
#endif
