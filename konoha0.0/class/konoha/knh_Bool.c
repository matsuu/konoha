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

#define _IS_TRUE(o)          (o != KNH_FALSE && IS_NOTNULL(o))
#define _IS_FALSE(o)         (o == KNH_FALSE || IS_NULL(o))
#define _new_Bool(ctx,b)     ((b == 0) ? KNH_FALSE : KNH_TRUE)

/* ======================================================================== */
/* [structs] */

void
knh_Bool_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Bool *b = (Bool*)s;
	b->value = 0;
}

/* ------------------------------------------------------------------------ */

void
knh_Bool_struct_copy(Ctx *ctx, Struct *s, Struct *s2)
{
	Bool *b = (Bool*)s;
	Bool *b2 = (Bool*)s2;
	b2->value = b->value;
}

/* ------------------------------------------------------------------------ */

knh_int_t 
knh_Bool_struct_compare(Ctx *ctx, Struct *s, Struct *s2) 
{
	Bool *b = (Bool*)s;
	Bool *b2 = (Bool*)s2;
	return b->value - b2->value;
}

/* ------------------------------------------------------------------------ */

#define _knh_Bool_struct_traverse NULL

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
