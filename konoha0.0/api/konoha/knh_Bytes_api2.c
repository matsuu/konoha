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
/* [constructor] */

/* ------------------------------------------------------------------------ */
/* @method Bytes! Bytes.new(Int init=256) */

Bytes* knh_Bytes_new(Ctx *ctx, Bytes *b, size_t init)
{
	if(init > b->capacity) {
		knh_Bytes_resize(ctx, b, (size_t)init);
	}
	return b;
}

/* ======================================================================== */
/* [method] */

/* ------------------------------------------------------------------------ */

/* ======================================================================== */
/* [mapping] */

/* @map Bytes String */

Object* knh_Bytes_String(Ctx *ctx, Object *self, MapMap *map)
{
	Bytes *b = (Bytes*)self;
	knh_bytes_t t = knh_Bytes_tobytes(b);
	if(!knh_string_isvalid(t)) return KNH_NULL;
	return new_String__fast(ctx, CLASS_String, t);
}

/* ------------------------------------------------------------------------ */
/* @map String Bytes! */

Object* knh_String_Bytes(Ctx *ctx, Object *self, MapMap *map)
{
	String *s = (String*)self;
	Bytes *b = new_Bytes(ctx, s->strlen + 1);
	knh_Bytes_write(ctx, b, knh_String_tobytes(self));
	return b;
}

/* ======================================================================== */
/* [movabletext] */

//* @method void Bytes.%dump(OutputStream w, Any m) */
//
//void knh_Bytes__dump(Ctx *ctx, Bytes *b, OutputStream *w, Any *m)
//{
//	TODO();
//}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
