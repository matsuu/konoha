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


/* ------------------------------------------------------------------------ */
/* string_charset.c 
 * 
 * This file is used to make string functions depending on character
 * encoding. We expect the use of UTF-8 in konoha, but other encodings 
 * are not limited to it.
 * */  

/* ------------------------------------------------------------------------ */

INLINE
size_t knh_string_size(knh_bytes_t s)
{
#ifdef KONOHA_CHARSET_ENC__UTF8
	size_t i, len = 0;
	for(i = 0; i < s.len; i++) {
		if((s.buf[i] & 0xC0 != 0x80)) len++;
	}
	return len;
#endif
	return s.len;  /* KONOHA_CHARSET_ENC__ASCII*/
}

/* ------------------------------------------------------------------------ */

INLINE
size_t knh_string_index(knh_bytes_t s, size_t n)
{
#ifdef KONOHA_CHARSET_ENC__UTF8
	size_t i, len = 0;
	for(i = 0; i < s.len; i++) {
		if(len == n) return i;
		if((s.buf[i] & 0xC0 != 0x80)) len++;
	}
	return s.len;
#endif
	return knh_uint_min(s.len, n); /* KONOHA_CHARSET_ENC__ASCII */
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_string_isvalid(knh_bytes_t s)
{
	return 1;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
