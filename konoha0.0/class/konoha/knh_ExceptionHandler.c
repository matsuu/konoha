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

#define _KNH_SETJUMP(hdlr)   setjmp(((ExceptionHandler*)hdlr)->jmpbuf)

/* ======================================================================== */
/* [structs] */

/* ------------------------------------------------------------------------ */

void
knh_ExceptionHandler_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	ExceptionHandler *b = (ExceptionHandler*)s;
	KNH_INITv(b->caught, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

#define _knh_ExceptionHandler_struct_copy   NULL

/* ------------------------------------------------------------------------ */

#define _knh_ExceptionHandler_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void
knh_ExceptionHandler_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	ExceptionHandler *b = (ExceptionHandler*)s;
	gc(ctx, b->caught);
}

/* ======================================================================== */
/* [constructors] */


ExceptionHandler* new_ExceptionHandler(Ctx *ctx)
{
	ExceptionHandler* b = 
		(ExceptionHandler*)knh_Object_malloc0(ctx, KNH_FLAG_ExceptionHandler, CLASS_ExceptionHandler, sizeof(ExceptionHandler));
	knh_ExceptionHandler_struct_init(ctx, (Struct *)b, 0, NULL);
	return b;
}

/* ------------------------------------------------------------------------ */

Object *knh_ExceptionHandler_fvalue(Ctx *ctx, knh_class_t cid)
{
	return new_ExceptionHandler(ctx);
}

/* ======================================================================== */
/* [methods] */

void knh_ExceptionHandler_longjmp(Ctx *ctx, ExceptionHandler *b, Exception *e)
{
	DEBUG_ASSERT(IS_Exception(e));
	if(!knh_ExceptionHandler_isCatching(b)) {
		return ;
	}
	KNH_SETv(ctx, b->caught, e); // setCaughtException(ctx, b, e)
	longjmp(b->jmpbuf, e->eid);
}

/* ------------------------------------------------------------------------ */

Exception* knh_ExceptionHandler_getCaughtException(ExceptionHandler *b)
{
	KNH_ASSERT(IS_Exception(b->caught));
	return b->caught;
}

/* ======================================================================== */
/* [movabletext] */


#ifdef __cplusplus
}
#endif
