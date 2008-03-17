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
/* [Bytes] */

INLINE
knh_bytes_t knh_Bytes_firstbyte(Bytes *b, size_t pos)
{
	knh_bytes_t v;
	DEBUG_ASSERT(pos <= b->size);
	v.buf = b->value + pos;
	v.len = pos;
	return v;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bytes_t knh_Bytes_lastbyte(Bytes *b, size_t pos)
{
	knh_bytes_t v;
	DEBUG_ASSERT(pos <= b->size);
	v.buf = b->value + pos;
	v.len = b->size  - pos;
	return v;
}

/* ------------------------------------------------------------------------ */

INLINE
size_t knh_Bytes_lastsize(Bytes *b, size_t pos)
{
	return b->size - pos;
}

/* ------------------------------------------------------------------------ */

INLINE
void knh_Bytes_subclear(Bytes *b, size_t pos)
{
	DEBUG_ASSERT(pos <= b->size);
	knh_bzero(b->value + pos, b->size - pos);
	b->size = pos;
}

/* ======================================================================== */
/* [String] */

String *new_String__buffer(Ctx *ctx, knh_class_t cid, knh_buffer_t cb)
{
	String *s;
	if(cid == CLASS_String) {
		if(cb.pos == cb.ba->size) {
			return knh_String_EMPTY();
		}
		s = new_String__fast(ctx, CLASS_String, knh_Bytes_lastbyte(cb.ba, cb.pos));
	}
	else {
		s = new_String__checked(ctx, cid, knh_Bytes_lastbyte(cb.ba, cb.pos));
	}
	knh_Bytes_subclear(cb.ba, cb.pos);
	return s;
}

/* ------------------------------------------------------------------------ */

String *new_String__bufferconv(Ctx *ctx, knh_class_t cid, knh_buffer_t cb, BytesConv *bconv)
{
	TODO();
	return new_String__buffer(ctx, cid, cb);
}

/* ======================================================================== */
/* [ctxbuf] */


knh_buffer_t knh_Context_buffer(Ctx* ctx)
{
	knh_buffer_t cb;
	cb.ba = ((Context*)ctx)->bufa;
	cb.w  = ((Context*)ctx)->bufw;
	cb.pos = knh_Bytes_size(((Context*)ctx)->bufa);
	return cb;
}

/* ------------------------------------------------------------------------ */

size_t knh_buffer_size(knh_buffer_t cb)
{
	return knh_Bytes_lastsize(cb.ba, cb.pos);
}

/* ------------------------------------------------------------------------ */

knh_bytes_t knh_buffer_tobytes(knh_buffer_t cb)
{
	return B2(knh_Bytes_tochar(cb.ba) + cb.pos, knh_Bytes_lastsize(cb.ba, cb.pos));
}

/* ------------------------------------------------------------------------ */

char *knh_buffer_top(knh_buffer_t cb)
{
	return knh_Bytes_tochar(cb.ba) + cb.pos;
}

/* ------------------------------------------------------------------------ */


void knh_buffer_clear(knh_buffer_t cb)
{
	knh_Bytes_subclear(cb.ba, cb.pos);
}


/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
