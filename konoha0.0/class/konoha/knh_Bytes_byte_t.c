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
#include<string.h>

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

/* ------------------------------------------------------------------------ */
/* [macros] */

#define _KNH_SIZE(v)         knh_size(v)

/* ------------------------------------------------------------------------ */
/* [lib] */

size_t knh_size(size_t s)
{
//	return s;
	if(s % sizeof(void *) == 0) return s;
	size_t ns = ((s / sizeof(void*)) + 1) * sizeof(void*);
//	DEBUG("%d => %d", s, ns);
	return ns;
}

/* ------------------------------------------------------------------------ */

INLINE
size_t knh_strlen(void *c)
{
	return strlen((char*)c);
}

/* ------------------------------------------------------------------------ */

INLINE
void knh_memcpy(void *d, void *s, size_t n)
{
	memcpy(d,s,n);
}

/* ------------------------------------------------------------------------ */

INLINE
void knh_bzero(void *s, size_t n)
{
	memset(s,0,n);
}

/* ------------------------------------------------------------------------ */

INLINE
knh_int_t knh_strcmp(char *s1, char *s2)
{
	return strcmp(s1,s2);	
}

/* ------------------------------------------------------------------------ */

INLINE
knh_int_t knh_strncmp(char *s1, char *s2, size_t n)
{
	return strncmp(s1,s2,n);	
}

/* ======================================================================== */
/* [bytes] */

INLINE
knh_bytes_t new_bytes(char *c)
{
	knh_bytes_t v;
	v.buf = (knh_uchar_t*)c;
	v.len = knh_strlen(c);
	return v;
}

#undef  _B
#define _B(c)     new_bytes(c)

/* ------------------------------------------------------------------------ */

INLINE
knh_bytes_t new_bytes__2(void *buf, size_t len)
{
	knh_bytes_t v;
	v.buf = (knh_uchar_t*)buf;
	v.len = len;
	return v;
}

#define _B2(c,n)   new_bytes__2(c,n)
#define _STEXT(c)  new_bytes__2(c,sizeof(c)-1)
#define _TEXT(c)   new_bytes__2(c,sizeof(c)-1)
#define _ISB(t,c) (t.len == (sizeof(c)-1) && knh_strncmp((char*)t.buf,c,t.len) == 0)


/* ======================================================================== */
/* [lib] */


knh_int_t knh_bytes_strcmp(knh_bytes_t v1, knh_bytes_t v2)
{
	size_t i, len = (v1.len < v2.len) ? v1.len : v2.len ;
	knh_int_t res;
	for(i = 0; i < len; i++) {
		res = (knh_int_t)v1.buf[i] - v2.buf[i];
		if(res != 0) return res;
	}
	return (knh_int_t)v1.len - (knh_int_t)v2.len;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bool_t knh_bytes_equals(knh_bytes_t v1, knh_bytes_t v2)
{
	return (v1.len == v2.len && knh_bytes_strcmp(v1, v2) == 0);
}

/* ------------------------------------------------------------------------ */


knh_bool_t knh_bytes_startsWith(knh_bytes_t v1, knh_bytes_t v2)
{
	size_t i; 
	if(v1.len < v2.len) return 0;	
	for(i = 0; i < v2.len; i++) {
		if(v1.buf[i] != v2.buf[i]) return 0;
	}
	return 1;
}


/* ------------------------------------------------------------------------ */


knh_bool_t knh_bytes_endsWith(knh_bytes_t v1, knh_bytes_t v2)
{
	size_t i; 
	if(v1.len < v2.len) return 0;	
	for(i = 0; i < v2.len; i++) {
		if(v1.buf[(v1.len-v2.len)+i] != v2.buf[i]) return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

knh_index_t knh_bytes_index(knh_bytes_t v, knh_int_t ch)
{
	knh_index_t i;
	for(i = 0; i < v.len; i++) {
		if(v.buf[i] == ch) return i;
#ifdef KONOHA_SECURE_CHAR
		if(v.buf[i] == '\0') return -1; 
#endif
	}
	return -1;
}

/* ------------------------------------------------------------------------ */


knh_index_t knh_bytes_rindex(knh_bytes_t v, knh_int_t ch)
{
	knh_index_t i;
	for(i = v.len - 1; i >= 0; i--) {
		if(v.buf[i] == ch) return i;
#ifdef KONOHA_SECURE_CHAR
		if(v.buf[i] == '\0') return -1; 
#endif
	}
	return -1;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bytes_t knh_bytes_first(knh_bytes_t t, knh_int_t loc)
{
	knh_bytes_t t2;
	t2.buf = t.buf;
	t2.len = loc;
	return t2;
}

/* ------------------------------------------------------------------------ */

INLINE
knh_bytes_t knh_bytes_last(knh_bytes_t t, knh_int_t loc)
{
	knh_bytes_t t2;
	t2.buf = t.buf + loc;
	t2.len = t.len - loc;
	return t2;
}

/* ------------------------------------------------------------------------ */


knh_bytes_t knh_bytes_trim(knh_bytes_t t, knh_int_t ch)
{
	while(t.buf[0] == ch) {
		t.buf++;
		t.len--;
	}
	if(t.len == 0) return t;
	while(t.buf[t.len-1] == ch) {
		t.len--;
		if(t.len == 0) return t;
	}
	return t;
}

/* ======================================================================== */
/* [decode] */

knh_int_t knh_bytes_toint(knh_bytes_t t)
{
	knh_int_t n = 0, i = 0, c, base = 10;
	if(t.len > 1) {
		if(t.buf[0] == '0') {
			if(t.buf[1] == 'x') {
				base = 16; i = 2;
			}
			else if(t.buf[1] == 'b') {
				base = 2;  i = 2;
			}
		}else if(t.buf[0] == '-') {
			base = 10; i = 1;
		}
	}
	
	for(;i < t.len; i++) {
		c = t.buf[i];
		if('0' <= c && c <= '9') {
			n = n * base + (c - '0');       
		}else if(base == 16) {
			if('A' <= c && c <= 'F') {
				n = n * 16 + (10 + c - 'A');       
			}else if('a' <= c && c <= 'f') {
				n = n * 16 + (10 + c - 'a');
			}else {
				break;
			}
		}else {
			break;
		}
	}
	if(t.buf[0] == '-') return -n;
	return n;
}

/* ------------------------------------------------------------------------ */


knh_float_t knh_bytes_tofloat(knh_bytes_t t)
{
	knh_int_t i = 0, c = 1;
	knh_float_t v = 0.0;

	if(t.buf[0] == '-') i = 1;

	for(;i < t.len; i++) {
		if('0' <= t.buf[i] && t.buf[i] <= '9') {
			v = v * 10 + (t.buf[i] - '0');
		}
		else if(t.buf[i] == '.') {
			i++;
			break;
		}
		else {
			return (t.buf[0] == '-') ? -v : v;
		}
	}

	for(; i < t.len; i++) {
		if('0' <= t.buf[i] && t.buf[i] <= '9') {
			v = v * 10 + (t.buf[i] - '0');
			c *= 10;
		}else {
			break;
		}
	}
	return (t.buf[0] == '-') ? (-v /c) : (v / c) ;
}

/* ------------------------------------------------------------------------ */

knh_int_t knh_bytes_toint64(knh_bytes_t t)
{
	knh_int64_t n = 0;
	int i = 0, c, base = 10;
	if(t.len > 1) {
		if(t.buf[0] == '0') {
			if(t.buf[1] == 'x') {
				base = 16; i = 2;
			}
			else if(t.buf[1] == 'b') {
				base = 2;  i = 2;
			}
		}else if(t.buf[0] == '-') {
			base = 10; i = 1;
		}
	}
	
	for(;i < t.len; i++) {
		c = t.buf[i];
		if('0' <= c && c <= '9') {
			n = n * base + (c - '0');       
		}else if(base == 16) {
			if('A' <= c && c <= 'F') {
				n = n * 16 + (10 + c - 'A');       
			}else if('a' <= c && c <= 'f') {
				n = n * 16 + (10 + c - 'a');
			}else {
				break;
			}
		}else {
			break;
		}
	}
	if(t.buf[0] == '-') return -n;
	return n;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
