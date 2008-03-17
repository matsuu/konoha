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


/* ======================================================================== */
/* [structs] */

void
knh_BytesConv_struct_init(Ctx *ctx, Struct *s1, int init, Object *cs)
{
	BytesConv *b =  (BytesConv*)s1;
	KNH_INITv(b->name, knh_String_EMPTY());
	b->fbconv = knh_BytesConv_fbconv__nop;
#ifdef KONOHA_USING_ICONV
	b->iconv_d = ((iconv_t)-1);
#endif
}

/* ------------------------------------------------------------------------ */

#define _knh_BytesConv_struct_copy NULL

/* ------------------------------------------------------------------------ */

#define _knh_BytesConv_struct_compare NULL

/* ------------------------------------------------------------------------ */

void
knh_BytesConv_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	BytesConv *b = (BytesConv*)s;
#ifdef KONOHA_USING_ICONV
   if(IS_SWEEP(gc) && b->iconv_d != ((iconv_t)-1)) {
		iconv_close(b->iconv_d);		
   }
#endif
	gc(ctx, b->name);	
}

/* ======================================================================== */
/* [constructors] */

BytesConv* new_BytesConv(Ctx *ctx, knh_bytes_t name, f_bconv fbconv)
{
	BytesConv* b = (BytesConv*)knh_Object_malloc(ctx, CLASS_BytesConv);
	knh_BytesConv_struct_init(ctx, (Struct*)b, 0, NULL);
	KNH_SETv(ctx, b->name, new_String__fast(ctx, CLASS_String, name));
	b->fbconv = fbconv;
	return b;
}

/* ------------------------------------------------------------------------ */

BytesConv* new_BytesConv__iconv(Ctx *ctx, knh_bytes_t from, knh_bytes_t to)
{
	BytesConv* b = (BytesConv*)knh_Object_malloc(ctx, CLASS_BytesConv);
	knh_BytesConv_struct_init(ctx, (Struct*)b, 0, NULL);

	char buf[KONOHA_FILEN_SIZE];
	knh_snprintf(buf, sizeof(buf), "%s=>%s", (char*)from.buf, (char*)to.buf);	
	KNH_SETv(ctx, b->name, new_String__fast(ctx, CLASS_String, B(buf)));
	b->fbconv = knh_BytesConv_fbconv__iconv;

	return b;
}

/* ======================================================================== */
/* [fbconv] */

size_t 
knh_BytesConv_fbconv__nop(Ctx *ctx, BytesConv *b, char *buf, size_t bufsiz, knh_Bytes *ba)
{
	knh_Bytes_write(ctx, ba, B2(buf, bufsiz));
	return bufsiz;
}

/* ------------------------------------------------------------------------ */

size_t 
knh_BytesConv_fbconv__iconv(Ctx *ctx, BytesConv *b, char *buf, size_t bufsiz, knh_Bytes *ba)
{
#if defined(KONOHA_USING_ICONV)
	char buffer[256], *ibuf = buf;
	size_t ilen = bufsiz;

	if(b->iconv_d == (iconv_t)-1) {
		return ilen;
	}

	while(ilen > 0) {
		char *obuf = buffer;
		size_t olen = sizeof(buffer);
		size_t rc = iconv(b->iconv_d, &ibuf, &ilen, &obuf, &olen);
 		if(rc == (size_t)-1) {
 			return bufsiz - ibuf;
 		}
 		knh_Bytes_write(ctx, ba, B(buffer, sizeof(buffer) - olen));
	}
	return bufsiz;
#else
	return 0;
#endif
}

/* ======================================================================== */
/* [movabletext] */

///* @method void BytesConv.%dump(OutputStream w, Any m) */
//
//void knh_BytesConv__dump(Ctx *ctx, BytesConv *b, OutputStream *w, Any *m)
//{
//	TODO();
//}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
