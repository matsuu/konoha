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

#define KONOHA_ENCODING__UTF8

/* ------------------------------------------------------------------------ */
static
knh_bool_t knh_bytes_checkUTF8_isLead(knh_uchar_t c)
{
	if ((c & 0xC0) != 0x80) return 1;
	return 0;
}

static
knh_ushort_t knh_bytes_checkUTF8_getBytes(knh_uchar_t c)
{
	KNH_ASSERT(knh_bytes_checkUTF8_isLead(c));
	if ((c & 0xF0) == 0xE0) {
		return 3;
	} else {
		switch(c & 0xF0){
		case 0xC0:
			return 2;
		case 0xF0:
			return 4;
		default:
			switch (c & 0x0F) {
			case 0x8:
				return 5;
			case 0xC:
				return 6;
			default:
				return -1;
			}

		}
	}
}
/* ------------------------------------------------------------------------ */
static
knh_bool_t knh_bytes_checkUTF8_isTrail(knh_uchar_t c)
{
	if ((0x80 <= c) && (c <= 0xBF)) return 1;
	return 0;
}

/* ------------------------------------------------------------------------ */
static
knh_bool_t knh_bytes_checkUTF8_isSingleton(knh_uchar_t c)
{
	if (c <= 0x7f) return 1;
	// if ((c & 0x80) == 0) return 1;	// which is faster??
	return 0;
}

/* ------------------------------------------------------------------------ */
knh_bool_t knh_bytes_checkENCODING(knh_bytes_t s) {
#ifdef KONOHA_ENCODING__UTF8
	size_t i, j;
	knh_uchar_t ch;
	size_t bytes = 0;
	for (i=0; i < s.len; i++) {
		ch = s.buf[i];
		/* UTF8 must be in
		 * single: 0x00 - 0x7f
		 * lead: 0xC0 - 0xFD (actually, 0xC2-0xF4)
		 * trail: 0x80 - 0xBF
		 * consequently, invalid utf8 is ranged
		 * 0xC0 - 0xC1, 0xF5 - 0xFF
		 *  */
		if (knh_bytes_checkUTF8_isSingleton(ch)) {
		} else if (knh_bytes_checkUTF8_isLead(ch)) {
			bytes = knh_bytes_checkUTF8_getBytes(ch);
			for (j=1;j<bytes;j++)
			{
				ch = s.buf[i+j];
				if (!knh_bytes_checkUTF8_isTrail(ch)) {
					DBG2_P("invalid UTF!");
					return 0;
				}
			}
			i += bytes;
		}
	}
	return 1;
#endif
	return 1; /* if KONOHA_ENCODING is not set */
}

/* ------------------------------------------------------------------------ */

size_t knh_bytes_mlen(knh_bytes_t s) {
#ifdef KONOHA_ENCODING__UTF8
	size_t i, len = 0, ulen = 0;

	for (i = 0; i < s.len; i++) {
		if (knh_bytes_checkUTF8_isLead(s.buf[i]))
			ulen++;
		else if (knh_bytes_checkUTF8_isSingleton(s.buf[i]))
			len++;
	}
	return ulen + len;
#endif
	return s.len; /* if KONOHA_ENCODING is not set */
}

/* ======================================================================== */

knh_bytes_t knh_bytes_mofflen(knh_bytes_t m, size_t moff, size_t mlen)
{
#ifdef KONOHA_ENCODING__UTF8
	size_t i, s = m.len, len = 0, ulen = 0;
	size_t bytes = 0;
	for (i = 0; i < m.len; i++) {
		if (knh_bytes_checkUTF8_isLead(m.buf[i])) ulen++;
		else if (knh_bytes_checkUTF8_isSingleton(m.buf[i])) len++;
		if (ulen + len == moff+1) {
			s = i;
			break;
		}
	}
	if (!(s < m.len)) {
		m.buf = (knh_uchar_t*)"";
		m.len = 0;
		return m;
	}
	knh_uchar_t ch = m.buf[s];
	if (knh_bytes_checkUTF8_isSingleton(ch)) {
		bytes = 1;
	} else {
		bytes = knh_bytes_checkUTF8_getBytes(ch);
	}
	m.buf = m.buf + s;
	m.len = bytes;
	return m;
#endif
	return knh_bytes_offlen(m, moff, mlen); /* if KONOHA_ENCODING is not set */
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
