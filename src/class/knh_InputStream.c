/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2005-2009, Kimio Kuramitsu <kimio at ynu.ac.jp>
 *           (c) 2008-      Konoha Software Foundation
 * All rights reserved.
 *
 * You may choose one of the following two licenses when you use konoha.
 * See www.konohaware.org/license.html for further information.
 *
 * (1) GNU Lesser General Public License 3.0 (with KONOHA_UNDER_LGPL3)
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

KNHAPI(InputStream*) new_InputStream__io(Ctx *ctx, String *urn, knh_io_t fd, knh_iodrv_t *drv)
{
	InputStream* o = (InputStream*)new_Object_bcid(ctx, CLASS_InputStream, 0);
	KNH_SETv(ctx, DP(o)->urn, urn);
	DP(o)->fd = fd;
	if(fd != -1) {
		DP(o)->driver = drv;
		DP(o)->bufsiz = drv->bufsiz;
		if(DP(o)->bufsiz > 0) {
			KNH_SETv(ctx, DP(o)->ba, new_Bytes(ctx, DP(o)->bufsiz));
			DP(o)->buf = (char*)(DP(o)->ba)->buf;
		}
		else {
			knh_InputStream_setFILE(o, 1);
		}
		DP(o)->bufpos = 0;
		DP(o)->bufend = 0;  /* empty */
	}
	return o;
}

/* ------------------------------------------------------------------------ */

KNHAPI(InputStream*) new_InputStream__FILE(Ctx *ctx, String *urn, FILE *fp, knh_iodrv_t *drv)
{
	InputStream* o = (InputStream*)new_Object_bcid(ctx, CLASS_InputStream, 0);
	KNH_SETv(ctx, DP(o)->urn, urn);
	if(fp != NULL) {
		DP(o)->fp = fp;
		DP(o)->driver = drv;
		knh_InputStream_setFILE(o, 1);
	}
	return o;
}

/* ======================================================================== */
/* [methods] */

Object *knh_InputStream_open(Ctx *ctx, InputStream *o, String *urn, String *m)
{
	knh_bytes_t fname = knh_String_tobytes(urn);
	knh_index_t loc = knh_bytes_index(fname, ':');
	if(loc == -1 || (loc == 1 && isalpha(fname.buf[0]))) {  /* 'C:/' */
		DP(o)->driver = knh_getIODriver(ctx, STEXT("file"));
	}
	else {
		DP(o)->driver = knh_getIODriver(ctx, knh_bytes_first(fname, loc));
	}
	KNH_SETv(ctx, DP(o)->urn, new_String(ctx, fname, NULL));
	char *mode = "r";
	if(IS_NOTNULL(m)) mode = knh_String_tochar(m);
	DP(o)->fd = DP(o)->driver->fopen(ctx, fname, mode, knh_Context_isStrict(ctx));
	if(DP(o)->fd != -1) {
		KNH_SETv(ctx, DP(o)->urn, urn);
		DP(o)->bufsiz = DP(o)->driver->bufsiz;
		if(DP(o)->bufsiz > 0) {
			KNH_SETv(ctx, DP(o)->ba, new_Bytes(ctx, DP(o)->bufsiz));
			DP(o)->buf = (char*)(DP(o)->ba)->buf;
		}
		else {
			knh_InputStream_setFILE(o, 1);
		}
		DP(o)->bufpos = 0;
		DP(o)->bufend = 0;  /* empty */
		DP(o)->driver->finit(ctx, (Object*)o, mode);
	}
	else {
		DP(o)->driver = knh_getDefaultIODriver();
	}
	return (Object*)o;
}

/* ------------------------------------------------------------------------ */

int knh_InputStream_getc(Ctx *ctx, InputStream *o)
{
	int ch;
	if(knh_InputStream_isFILE(o)) {
		ch = knh_fgetc(ctx, DP(o)->fp);
	}
	else {
		while(1) {
			if(DP(o)->bufpos < DP(o)->bufend) {
				ch = (knh_uchar_t)DP(o)->buf[DP(o)->bufpos];
				DP(o)->bufpos++;
				break;
			}
			DP(o)->bufpos = 0;
			DP(o)->bufend = DP(o)->driver->fread(ctx, DP(o)->fd, DP(o)->buf, DP(o)->bufsiz);
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
	if(knh_InputStream_isFILE(o)) {
		return knh_fread(ctx, buf, bufsiz, DP(o)->fp);
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
		size_t s = DP(o)->driver->fread(ctx, DP(o)->fd, buf+inbufsiz, bufsiz-inbufsiz);
		DP(o)->size += s;
		return s + inbufsiz;
	}
}

/* ------------------------------------------------------------------------ */
/* @method String InputStream.readLine() */

String* knh_InputStream_readLine(Ctx *ctx, InputStream *in)
{
	int ch;
	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
	while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
		if(ch == '\r') {
			return new_String__cwbconv(ctx, cwb, DP(in)->bconv);
		}
		if(ch == '\n') {
			if(DP(in)->prev == '\r') continue;
			return new_String__cwbconv(ctx, cwb, DP(in)->bconv);
		}
		knh_Bytes_putc(ctx, cwb->ba, ch);
	}
	if(knh_cwb_size(cwb) != 0) {
		return new_String__cwbconv(ctx, cwb, DP(in)->bconv);
	}
	return (String*)KNH_NULL;
}

/* ------------------------------------------------------------------------ */
/* @method void InputStream.close() */

void knh_InputStream_close(Ctx *ctx, InputStream *o)
{
	f_io_close f = DP(o)->driver->fclose;
	DP(o)->driver = knh_getDefaultIODriver();
	f(ctx, DP(o)->fd);
	DP(o)->fd = -1;
	KNH_SETv(ctx, DP(o)->ba, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

int knh_InputStream_isClosed(Ctx *ctx, InputStream *o)
{
	return (DP(o)->fd == -1 && IS_NULL(DP(o)->ba));
}

/* ======================================================================== */
/* [File] */

KNHAPI(InputStream*) new_FileInputStream(Ctx *ctx, knh_bytes_t file, int isThrowable)
{
	knh_iodrv_t *drv = knh_getIODriver(ctx, STEXT("file"));
	knh_io_t fd = drv->fopen(ctx, file, "r", isThrowable);
	return new_InputStream__io(ctx, new_String(ctx, file, NULL), fd, drv);
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
/* [String] */

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

/* ======================================================================== */
/* [Data] */

int knh_bytes_checkStmtLine(knh_bytes_t line)
{
	char *ln = (char*)line.buf;
	size_t i = 0, len = line.len;
	int ch, quote = 0, nest =0;
	L_NORMAL:
	for(; i < len; i++) {
		ch = ln[i];
		if(ch == '{' || ch == '[' || ch == '(') nest++;
		if(ch == '}' || ch == ']' || ch == ')') nest--;
		if(ch == '\'' || ch == '"' || ch == '`') {
			quote = ch; i++;
			goto L_QUOTE;
		}
	}
	return nest;

	L_QUOTE:
	KNH_ASSERT(i > 0);
	for(; i < len; i++) {
		ch = ln[i];
		if(ln[i-1] != '\\' && ch == quote) {
			i++;
			goto L_NORMAL;
		}
	}
	return 1;
}

///* ------------------------------------------------------------------------ */
//
//KNHAPI(Object*) knh_InputStream_readData(Ctx *ctx, InputStream *in, knh_class_t reqc)
//{
//	int ch, linenum = DP(in)->line;
//	knh_cwb_t cwbbuf, *cwb = knh_cwb_open(ctx, &cwbbuf);
//	L_AGAIN:;
//	while((ch = knh_InputStream_getc(ctx, in)) != EOF) {
//		if(ch == '\r' || ch == '`') {
//			int prev = DP(in)->prev;
//			if(prev == '\r' || prev == '\n') continue;
//			if(prev == ']' || prev == '}' || knh_bytes_checkStmtLine(knh_cwb_tobytes(cwb)) == 0) {
//				break;
//			}
//		}
//		knh_Bytes_putc(ctx, cwb->ba, ch);
//	}
//	if(knh_cwb_size(cwb) == 0) {
//		if(ch == EOF) return KNH_NULL;
//		goto L_AGAIN;
//	}
//
//	{
//		InputStream *bin = new_BytesInputStream(ctx, cwb->ba, cwb->pos, knh_Bytes_size(cwb->ba));
//		Object *value = NULL;
//		DP(bin)->uri = URI_EVAL;
//		DP(bin)->line = linenum;
//		knh_InputStream_setEncoding(ctx, bin, DP(in)->enc);
//		value = konohac_data(ctx, bin, reqc);
//		knh_cwb_close(cwb);
//		if(IS_NULL(value)) goto L_AGAIN;
//		return value;
//	}
//}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
