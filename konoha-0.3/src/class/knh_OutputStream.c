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
/* [structs] */


/* ======================================================================== */
/* [methods] */

Object *knh_OutputStream_open(Ctx *ctx, OutputStream *o, String *urn, String *mode)
{
	knh_bytes_t fname = knh_String_tobytes(urn);
	knh_index_t loc = knh_bytes_index(fname, ':');

	if(loc == -1 || (loc == 1 && isalpha(fname.buf[0]))) {  /* 'C:/' */
		DP(o)->driver = *(knh_System_getIODriver(ctx, STEXT("file")));
	}
	else {
		DP(o)->driver = *(knh_System_getIODriver(ctx, knh_bytes_first(fname, loc)));
	}
	if(IS_NULL(mode)) {
		DP(o)->fd = DP(o)->driver.fopen(ctx, NULL, o, fname, "w");
	}
	else {
		DP(o)->fd = DP(o)->driver.fopen(ctx, NULL, o, fname, knh_String_tochar(mode));
	}

	if(DP(o)->fd != -1) {
		KNH_SETv(ctx, DP(o)->ba, new_Bytes(ctx, DP(o)->driver.bufsiz));
		knh_OutputStream_setBOL(o,1);
	}
	else {
		char buff[FILENAME_BUFSIZ];
		knh_snprintf(buff, sizeof(buff), "IO!!: cannot open %s", (char*)fname.buf);
		DP(o)->driver = knh_System_getDefaultIODriver();
		return (Object*)new_Nue__s(ctx, buff);
	}
	return (Object*)o;
}

/* ======================================================================== */
/* [methods] */

/* ------------------------------------------------------------------------ */

void knh_OutputStream_putc(Ctx *ctx, OutputStream *o, knh_int_t ch)
{
	Bytes *ba = DP(o)->ba;
	KNH_ASSERT(IS_Bytes(ba));
	knh_Bytes_putc(ctx, ba, ch);
	if(!knh_OutputStream_isStoringBuffer(o) && ba->size > DP(o)->driver.bufsiz) {
		DP(o)->driver.fwrite(ctx, DP(o)->fd, (char*)(ba)->buf, (ba)->size);
		knh_Bytes_clear(ba, 0);
	}
	DP(o)->size++;
}

/* ------------------------------------------------------------------------ */

void knh_OutputStream_write(Ctx *ctx, OutputStream *o, knh_bytes_t buf)
{
	Bytes *ba = DP(o)->ba;
	KNH_ASSERT(IS_Bytes(ba));
	knh_Bytes_write(ctx, ba, buf);
	if(!knh_OutputStream_isStoringBuffer(o) && ba->size > DP(o)->driver.bufsiz) {
		DP(o)->driver.fwrite(ctx, DP(o)->fd, (char*)(ba)->buf, (ba)->size);
		knh_Bytes_clear(ba, 0);
	}
	DP(o)->size += buf.len;
}

/* ------------------------------------------------------------------------ */
/* @method void OutputStream.flush() */

void knh_OutputStream_flush(Ctx *ctx, OutputStream *o)
{
	if(!knh_OutputStream_isStoringBuffer(o)) {
		Bytes *ba = DP(o)->ba;
		DP(o)->driver.fwrite(ctx, DP(o)->fd, (char*)(ba)->buf, (ba)->size);
		knh_Bytes_clear(ba, 0);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void OutputStream.clear() */

void knh_OutputStream_clear(Ctx *ctx, OutputStream *o)
{
	if(knh_OutputStream_isStoringBuffer(o)) {
		knh_Bytes_clear(DP(o)->ba, 0);
	}
}

/* ------------------------------------------------------------------------ */
/* @method void OutputStream.close() */

void knh_OutputStream_close(Ctx *ctx, OutputStream *o)
{
	knh_OutputStream_flush(ctx, o);
	f_io_close f = DP(o)->driver.fclose;
	DP(o)->driver = knh_System_getDefaultIODriver();
	f(ctx, DP(o)->fd);
	DP(o)->fd = -1;
}

/* ------------------------------------------------------------------------ */

int knh_OutputStream_isClosed(OutputStream *o)
{
	return (DP(o)->fd == -1);
}

/* ------------------------------------------------------------------------ */

void knh_OutputStream_indent_inc(Ctx *ctx, OutputStream *o)
{
	DP(o)->indent++;
}

/* ------------------------------------------------------------------------ */

void knh_OutputStream_indent_dec(Ctx *ctx, OutputStream *o)
{
	DP(o)->indent--;
}

/* ------------------------------------------------------------------------ */

void knh_OutputStream_write_indent(Ctx *ctx, OutputStream *o)
{
	int i;
	for(i = 0; i < DP(o)->indent; i++) {
		knh_OutputStream_write(ctx, o, knh_String_tobytes(DP(o)->TAB));
	}
}

/* ------------------------------------------------------------------------ */

void knh_OutputStream_print_(Ctx *ctx, OutputStream *o, knh_bytes_t str, knh_bool_t isnl)
{
	if(str.len > 0) {
		if(knh_OutputStream_isBOL(o)) {
			knh_write_BOL(ctx, o);
		}
		if(IS_NULL(DP(o)->bconv)) {
			knh_OutputStream_write(ctx, o, str);
		}
		else {
			knh_OutputStream_write__bconv(ctx, o, str);
		}
	}
	if(isnl) {
		knh_write_EOL(ctx, o);
	}
}


/* ======================================================================== */


/* ------------------------------------------------------------------------ */

KNHAPI(OutputStream*) new_FileOutputStream(Ctx *ctx, knh_bytes_t file, char *mode)
{
	OutputStream* o = (OutputStream*)new_Object_bcid(ctx, CLASS_OutputStream, 0);
	knh_OutputStream_setBOL(o, 1);

	DP(o)->driver = *(knh_System_getIODriver(ctx, STEXT("file")));
	DP(o)->fd = DP(o)->driver.fopen(ctx, NULL, o, file, mode);
	if(DP(o)->fd != -1) {
		KNH_SETv(ctx, DP(o)->ba, new_Bytes(ctx, DP(o)->driver.bufsiz));
		KNH_SETv(ctx, DP(o)->urn, new_String(ctx, file, NULL));
	}
	else {
		DP(o)->driver = knh_System_getDefaultIODriver();
	}
	return o;
}

/* ------------------------------------------------------------------------ */

KNHAPI(OutputStream*) new_BytesOutputStream(Ctx *ctx, Bytes *ba)
{
	OutputStream* o = (OutputStream*)new_Object_bcid(ctx, CLASS_OutputStream, -1);
	knh_OutputStream_setBOL(o, 1);
	KNH_ASSERT(IS_Bytes(ba));
	KNH_SETv(ctx, DP(o)->ba, ba);
	knh_OutputStream_setStoringBuffer(o, 1);
	return o;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
