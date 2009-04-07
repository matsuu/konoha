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
/* [methods] */

//static
//void knh_InputStream_setbuf(Ctx *ctx, InputStream *in)
//{
//	KNH_ASSERT(!IS_Bytes(DP(in)->ba));
//	if(DP(o)->fd != -1) {
//		DP(o)->bufsiz = DP(o)->driver.bufsiz;
//		if(DP(o)->bufsiz > 0) {
//			KNH_SETv(ctx, DP(o)->ba, new_Bytes(ctx, DP(o)->bufsiz));
//			DP(o)->buf = (char*)(DP(o)->ba)->buf;
//		}
//		DP(o)->bufpos = 0;
//		DP(o)->bufend = 0;  /* empty */
//		KNH_SETv(ctx, DP(o)->urn, new_String(ctx, fname, NULL));
//	}
//	else {
//		DP(o)->driver = knh_System_getDefaultIODriver();
//		char buff[FILENAME_BUFSIZ];
//		knh_snprintf(buff, sizeof(buff), "IO!!: '%s'", (char*)fname.buf);
//		return (Object*)new_Nue__s(ctx, buff);
//	}
//}

/* ------------------------------------------------------------------------ */


Object *knh_InputStream_open(Ctx *ctx, InputStream *o, String *urn)
{
	knh_bytes_t fname = knh_String_tobytes(urn);
	knh_index_t loc = knh_bytes_index(fname, ':');
	if(loc == -1 || (loc == 1 && isalpha(fname.buf[0]))) {  /* 'C:/' */
		DP(o)->driver = *(knh_System_getIODriver(ctx, STEXT("file")));
	}
	else {
		DP(o)->driver = *(knh_System_getIODriver(ctx, knh_bytes_first(fname, loc)));
	}
	DP(o)->fd = DP(o)->driver.fopen(ctx, o, NULL, fname, "r");
	if(DP(o)->fd != -1) {
		DP(o)->bufsiz = DP(o)->driver.bufsiz;
		if(DP(o)->bufsiz > 0) {
			KNH_SETv(ctx, DP(o)->ba, new_Bytes(ctx, DP(o)->bufsiz));
			DP(o)->buf = (char*)(DP(o)->ba)->buf;
		}
		DP(o)->bufpos = 0;
		DP(o)->bufend = 0;  /* empty */
		KNH_SETv(ctx, DP(o)->urn, new_String(ctx, fname, NULL));
	}
	else {
		DP(o)->driver = knh_System_getDefaultIODriver();
		char buff[FILENAME_BUFSIZ];
		knh_snprintf(buff, sizeof(buff), "IO!!: '%s'", (char*)fname.buf);
		return (Object*)new_Nue__s(ctx, buff);
	}
	return (Object*)o;
}

/* ------------------------------------------------------------------------ */

int knh_InputStream_getc(Ctx *ctx, InputStream *o)
{
	int ch;
	if(knh_InputStream_isSTDIN(o)) {
		ch = fgetc(DP(o)->fp);
	}
	else {
		while(1) {
			if(DP(o)->bufpos < DP(o)->bufend) {
				ch = (knh_uchar_t)DP(o)->buf[DP(o)->bufpos];
				DP(o)->bufpos++;
				break;
			}
			DP(o)->bufpos = 0;
			DP(o)->bufend = DP(o)->driver.fread(ctx, DP(o)->fd, DP(o)->buf, DP(o)->bufsiz);
			//DBG2_P("* bufpos=%d, bufend=%d, bufsiz=%d", DP(o)->bufpos, DP(o)->bufend, DP(o)->bufsiz)
			if(DP(o)->bufend == 0) return EOF;
		}
	}
	{ /* statstics */
		DP(o)->size++;
		if(ch == '\n') {
			if(DP(o)->prev != '\r') {
				DP(o)->line++;
			}
		}else if(ch == '\r') {
			DP(o)->line++;
		}
		DP(o)->prev = ch;
	}
	return ch;
}

/* ------------------------------------------------------------------------ */

size_t
knh_InputStream_read(Ctx *ctx, InputStream *o, char *buf, size_t bufsiz)
{
	if(knh_InputStream_isSTDIN(o)) {
		return fread(buf, 1, bufsiz, DP(o)->fp);
	}
	else {
		size_t inbufsiz = (DP(o)->bufend - DP(o)->bufpos);
		if(bufsiz <= inbufsiz) {
			knh_memcpy(buf, DP(o)->buf, bufsiz);
			DP(o)->bufpos += bufsiz;
			{
				DP(o)->size += bufsiz;
			}
			return bufsiz;
		}
		knh_memcpy(buf, DP(o)->buf, inbufsiz);
		DP(o)->bufpos += inbufsiz;
		DP(o)->size += bufsiz;
		buf += inbufsiz;
		size_t s = DP(o)->driver.fread(ctx, DP(o)->fd, buf+inbufsiz, bufsiz-inbufsiz);
		DP(o)->size += s;
		return s + inbufsiz;
	}
}

/* ------------------------------------------------------------------------ */
/* @method String InputStream.readLine() */

String* knh_InputStream_readLine(Ctx *ctx, InputStream *o)
{
	int ch;
	knh_cwb_t cwb = new_cwb(ctx);
	while((ch = knh_InputStream_getc(ctx, o)) != EOF) {
		if(ch == '\r') {
			return new_String__cwbconv(ctx, cwb, DP(o)->bconv);
		}
		if(ch == '\n') {
			if(DP(o)->prev == '\r') continue;
			return new_String__cwbconv(ctx, cwb, DP(o)->bconv);
		}
		knh_Bytes_putc(ctx, cwb.ba, ch);
	}
	if(knh_cwb_size(cwb) != 0) {
		return new_String__cwbconv(ctx, cwb, DP(o)->bconv);
	}
	return (String*)KNH_NULL;
}

/* ------------------------------------------------------------------------ */
/* @method void InputStream.close() */

void knh_InputStream_close(Ctx *ctx, InputStream *o)
{
	if(knh_InputStream_isSTDIN(o)) {
		KNH_ASSERT(DP(o)->fp == stdin);
		knh_InputStream_setSTDIN(o, 0);
	}
	else {
		f_io_close f = DP(o)->driver.fclose;
		DP(o)->driver = knh_System_getDefaultIODriver();
		f(ctx, DP(o)->fd);
	}
	DP(o)->fd = -1;
}

/* ------------------------------------------------------------------------ */

int knh_InputStream_isClosed(InputStream *o)
{
	return (DP(o)->fd == -1);
}

/* ======================================================================== */
/* [File] */

KNHAPI(InputStream*) new_FileInputStream(Ctx *ctx, knh_bytes_t file)
{
	InputStream* o = (InputStream*)new_Object_bcid(ctx, CLASS_InputStream, 0);
	DP(o)->driver = *(knh_System_getIODriver(ctx, STEXT("file")));
	DP(o)->fd = DP(o)->driver.fopen(ctx, o, NULL, file, "r");
	if(DP(o)->fd != -1) {
		DP(o)->bufsiz = DP(o)->driver.bufsiz;
		if(DP(o)->bufsiz > 0) {
			KNH_SETv(ctx, DP(o)->ba, new_Bytes(ctx, DP(o)->bufsiz));
			DP(o)->buf = (char*)(DP(o)->ba)->buf;
		}
		DP(o)->bufpos = 0;
		DP(o)->bufend = 0;  /* empty */
		KNH_SETv(ctx, DP(o)->urn, new_String(ctx, file, NULL));
	}
	else {
		DP(o)->driver = knh_System_getDefaultIODriver();
	}
	return o;
}

/* ======================================================================== */
/* [Bytes] */

KNHAPI(InputStream*) new_BytesInputStream(Ctx *ctx, Bytes *ba, size_t s, size_t e)
{
	InputStream* o = (InputStream*)new_Object_bcid(ctx, CLASS_InputStream, 0);
	DP(o)->fd = -1;
	KNH_ASSERT(IS_Bytes(ba));
	KNH_SETv(ctx, DP(o)->ba, ba);
	DP(o)->buf = (char*)(ba)->buf;
	DP(o)->bufsiz = (ba)->size;
	KNH_ASSERT(e <= knh_Bytes_size(ba));
	KNH_ASSERT(s <= e);
	DP(o)->bufpos   = s;
	DP(o)->bufend   = e;
	return o;
}

/* ------------------------------------------------------------------------ */
/* @map Bytes InputStream! */

MAPPER knh_Bytes_InputStream(Ctx *ctx, knh_sfp_t *sfp)
{
	Bytes *ba = (Bytes*)sfp[0].o;
	KNH_MAPPED(ctx, sfp, new_BytesInputStream(ctx, ba, 0, knh_Bytes_size(ba)));
}

/* ======================================================================== */
/* [Bytes] */

KNHAPI(InputStream*) new_StringInputStream(Ctx *ctx, String *str, size_t s, size_t e)
{
	InputStream* o = (InputStream*)new_Object_bcid(ctx, CLASS_InputStream, 0);
	DP(o)->fd = -1;
	KNH_ASSERT(IS_Bytes(str));
	KNH_SETv(ctx, DP(o)->str, str);
	DP(o)->buf = (char*)(str)->str;
	DP(o)->bufsiz = (str)->size;
	KNH_ASSERT(e <= (str)->size);
	KNH_ASSERT(s <= e);
	DP(o)->bufpos   = s;
	DP(o)->bufend   = e;
	return o;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
