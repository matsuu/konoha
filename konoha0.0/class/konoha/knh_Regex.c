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

#ifdef  KONOHA_LIBPCRE
	#include<pcre.h>
#endif/*KONOHA_LIBPCRE*/

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */
/* [prec] */



/* ======================================================================== */
/* [structs] */

void
knh_Regex_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	Regex *b = (Regex*)s;
	KNH_INITv(b->pstr, KNH_NULL);
	b->re = NULL;
}

/* ------------------------------------------------------------------------ */

#define _knh_Regex_struct_copy  NULL
#define _knh_Regex_struct_compare NULL

/* ------------------------------------------------------------------------ */

void
knh_Regex_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	Regex *b = (Regex*)s;
	gc(ctx, b->pstr);
	if(IS_SWEEP(gc)) {
		
	}
}

/* ======================================================================== */
/* [constructors] */

Regex *new_Regex(Ctx *ctx, String *pstr)
{
	Regex *b = (Regex*)knh_Object_malloc0(ctx, KNH_FLAG_Regex, CLASS_Regex, sizeof(Regex));
	knh_Regex_struct_init(ctx, (Struct*)b, 0, NULL);
	KNH_SETv(ctx, b->pstr, pstr);
	return b;
}

/* ======================================================================== */
/* [match] */


INLINE
knh_bool_t knh_Regex_match__b(Ctx *ctx, Regex *b, knh_bytes_t s)
{
	if(b->re == NULL) {
		TODO(); //KNH_UNSUPPORTEDs(ctx, b, "match");
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

/* @method Bool Regex.match(String s) */

INLINE
knh_bool_t knh_Regex_match(Ctx *ctx, Regex *b, String *s)
{
	if(IS_NULL(s)) return 0;
	return knh_Regex_match__b(ctx, b, knh_String_tobytes(s));
}

/* ======================================================================== */
/* [transform] */
/* Tuple t = Tuple(hogehoge, 're:(**):(**):(**)') */

Object *knh_Regex_transform(Ctx *ctx, Regex *b, knh_class_t tcid, String *s)
{
	if(IS_NULL(s)) return KNH_NULL;
	TODO();
	return KNH_NULL;
}

/* ======================================================================== */
/* [mapmap] */

Object *knh_mapserv__Regex(Ctx *ctx, Object *mapserv, Object *s, knh_class_t tcid)
{
	TODO();
	return KNH_NULL;
}


/* ======================================================================== */
/* [movabletext] */

/* @method void Regex.%s(OutputStream w, Any m) */

INLINE
void knh_Regex__s(Ctx *ctx, Regex *b, OutputStream *w, Any *m)
{
	knh_write__s(ctx, w, "'re:");
	knh_write(ctx, w, knh_String_tobytes(b->pstr));
	knh_putc(ctx, w, '\'');
}

/* ------------------------------------------------------------------------ */

/* @method void Regex.%dump(OutputStream w, Any m) */

void knh_Regex__dump(Ctx *ctx, Regex *b, OutputStream *w, Any *m)
{
//	int_byte_t quote = '\'';
//	if(knh_Object_cid(b) == CLASS_Regex) quote = '"';
//	knh_putc(ctx, w, quote);
//	char *p = knh_Regex_tochar(b);
//	knh_int_t i;
//	for(i = 0; i < b->strlen; i++) {
//		switch(p[i]) {
//			case '\t' :
//				knh_putc(ctx, w, '\\'); knh_putc(ctx, w, 't'); break ;
//			case '\n' :
//				knh_putc(ctx, w, '\\'); knh_putc(ctx, w, 'n'); break ;
//			case '\r' :
//				knh_putc(ctx, w, '\\'); knh_putc(ctx, w, 'r'); break ;
//			case '\\' : case '\"' : case '\'' :
//				knh_putc(ctx, w, '\\'); knh_putc(ctx, w, p[i]); break ;
//			default :
//				knh_putc(ctx, w, p[i]);
//		}
//	}
//	knh_putc(ctx, w, quote);
}

/* ------------------------------------------------------------------------ */
