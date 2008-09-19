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

#define _knh_Iterator_cid(it)           DP(it)->cid
#define _knh_Iterator_source(it)        DP(it)->source
#define _knh_Iterator_pos(it)           DP(it)->pos
#define _knh_Iterator_setpos(it, p)     DP(it)->pos = p
#define _knh_Iterator_ref(it)           DP(it)->ref

/* ------------------------------------------------------------------------ */
/* [private] */

static Object *knh_Object_single_next(Ctx *ctx, Iterator *it);

/* ======================================================================== */
/* [structs] */

void
knh_Iterator_struct_init(Ctx *ctx, knh_Iterator_struct *b, int init, Object *cs)
{
	b->fnext  =  knh_Object_single_next;
	KNH_INITv(b->source, KNH_VOID);
	b->pos    =  0;
	b->ref    =  NULL; 
	b->count = 0;
	b->start = 0;
	b->end   = (size_t)-1;
}

/* ------------------------------------------------------------------------ */

void
knh_Iterator_struct_copy(Ctx *ctx, knh_Iterator_struct *b, knh_Iterator_struct *b2)
{
	b2->fnext    = b->fnext;
	b2->pos      = b->pos;
	b2->ref      = b->ref;
	KNH_INITv(b2->source, b->source);
	b2->count = b->count;
	b2->start = b->start;
	b2->end   = b->end;
}

/* ------------------------------------------------------------------------ */

void
knh_Iterator_struct_traverse(Ctx *ctx, knh_Iterator_struct *b, f_traverse gc)
{
	gc(ctx, b->source);
}

/* ======================================================================== */
/* [constructors] */

static
Object *knh_Object_single_next(Ctx *ctx, Iterator *it)
{
	if(knh_Iterator_pos(it) == 0) {
		knh_Iterator_setpos(it, 1);
		return knh_Iterator_source(it);
	}
	return KNH_VOID;		
}

/* ------------------------------------------------------------------------ */

Iterator* new_Iterator(Ctx *ctx, knh_class_t p1, Any *source, f_next fnext)
{
	knh_class_t cid = knh_class_Iterator(ctx, p1);
	Iterator *o = (Iterator*)new_ObjectX_malloc(ctx, FLAG_Iterator, CLASS_Iterator, cid, sizeof(knh_Iterator_struct));
	knh_Iterator_struct_init(ctx, DP(o), 0, NULL);
	if(fnext != NULL) {
		DP(o)->fnext = fnext;
	}
	KNH_SETv(ctx, DP(o)->source, source);
	o->fnext_1 = DP(o)->fnext;
	return o;
}

/* ======================================================================== */
/* [slice] */

Object *knh_Iterator_slice(Ctx *ctx, Iterator *o)
{
	Object *v = o->fnext_1(ctx, o);
	size_t s = DP(o)->start;
	size_t c = DP(o)->count;
	size_t e = DP(o)->end;
	while(IS_NOTNULL(v)) {
		if(c > e) {
			return KNH_NULL;
		}
		c++;
		if(c < s) {
			continue;
		}
		break;
	}
	DP(o)->count = c;
	return v;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
