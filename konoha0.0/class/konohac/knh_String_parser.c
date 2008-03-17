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
/* [macro] */

#define _SPF_BACKQUOTED  KNH_FLAG07

/* ======================================================================== */
/* [knh_bytes_t] */

INLINE 
knh_bool_t knh_byte_isBackQuoted(knh_bytes_t t) 
{
	return (knh_bytes_index(t, '\\') >= 0);
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_write__BackQuoted(Ctx *ctx, OutputStream *w, knh_uchar_t *p)
{
	DEBUG_ASSERT(p[0] == '\\');
	switch(p[1]) {
		case '\r': knh_putc(ctx, w, '\r'); break;
		case '\t': knh_putc(ctx, w, '\t'); break;
		case '\n': knh_putc(ctx, w, '\n'); break;
		case '\v': knh_putc(ctx, w, '\v'); break;
		default: knh_putc(ctx, w, p[1]); break;
	}
	return 2; 
}

/* ======================================================================== */
/* [String] */

String *new_String__parser(Ctx *ctx, knh_class_t cid, knh_flag_t pf, knh_bytes_t t)
{
	knh_buffer_t cb = knh_Context_buffer(ctx);
	knh_int_t i = 0;
	for(i = 0; i < t.len; i++) {
		if(t.buf[i] == '\\' && (pf & SPF_BACKQUOTED) == SPF_BACKQUOTED) {
			i += knh_write__BackQuoted(ctx, cb.w, t.buf+i);
			continue;
		}
		if(t.buf[i] == '\0') {
			DEBUG("We met an unexpected '\\0'  at %d < %d", (int)i, (int)t.len);
			break;
		}
		i++;
	}
	return new_String__buffer(ctx, cid, cb);
}


/* ------------------------------------------------------------------------ */

String *new_String__UPROPN(Ctx *ctx, knh_bytes_t urn)
{
	knh_bytes_t fu = urn, lu = {(knh_uchar_t*)"", 0};

	LOOP:;
	String *base = (String*)knh_Context_getProperty(ctx, (Context*)ctx, fu);
	if(STRUCT_IS_String(base)) {
		if(lu.len == 0) {
			return base;
		}
		char *fmt = "%s/%s";
		fu = knh_String_tobytes(base);
		if(fu.buf[fu.len-1] == '/') {
			fmt = "%s%s";
		}
		char buf[KONOHA_URN_SIZE];
		snprintf(buf, sizeof(buf), fmt, fu.buf, lu.buf);
		return new_String__fast(ctx, CLASS_String__urn, B(buf));
	}
	knh_index_t idx = knh_bytes_rindex(fu, '/');
	if(idx != -1 && fu.buf[idx-1] != '/') {
		fu = knh_bytes_first(urn, idx);
		lu = knh_bytes_last(urn, idx+1);
		goto LOOP;
	}
	return new_String__fast(ctx, CLASS_String__urn, urn);
}


#ifdef __cplusplus
}
#endif
