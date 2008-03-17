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
/* [structs] */

void knh_Counter_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	knh_Counter *b =  (knh_Counter*)s1;
	b->count = 0;
}

/* ------------------------------------------------------------------------ */

void knh_Counter_struct_copy(Ctx *ctx, Struct *s1, Struct *s2)
{
	knh_Counter *b =  (knh_Counter*)s1;
	knh_Counter *b2 = (knh_Counter*)s2;
	b2->count = b->count;
}

/* ------------------------------------------------------------------------ */

#define _knh_Counter_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void knh_Counter_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	knh_Counter *b = (knh_Counter*)s;
	b->count = 0;
}

/* ======================================================================== */
/* [constructors] */

Object *knh_Counter_fvalue(Ctx *ctx, knh_class_t cid)
{
	knh_Counter *b = (knh_Counter*)knh_Object_malloc(ctx, cid);
	knh_Counter_struct_init(ctx, (Struct*)b, 0, NULL);
	return b;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
