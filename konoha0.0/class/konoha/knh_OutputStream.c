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
/* [drivers] */

static knh_outptr_drivers_t DRIVERS__nop = {
	knh_OutputStream_open__nop,
	knh_OutputStream_putc__nop,
	knh_OutputStream_write__nop,
	knh_OutputStream_flush__nop,
	knh_OutputStream_close__nop
};

static knh_outptr_drivers_t DRIVERS__FILE = {
	knh_OutputStream_open__FILE,
	knh_OutputStream_putc__FILE,
	knh_OutputStream_write__FILE,
	knh_OutputStream_flush__FILE,
	knh_OutputStream_close__FILE
};

static knh_outptr_drivers_t DRIVERS__stdout = {
	knh_OutputStream_open__nop,
	knh_OutputStream_putc__FILE,
	knh_OutputStream_write__FILE,
	knh_OutputStream_flush__FILE,
	knh_OutputStream_close__nop
};

static knh_outptr_drivers_t DRIVERS__Bytes = {
	knh_OutputStream_open__nop,
	knh_OutputStream_putc__Bytes,
	knh_OutputStream_write__Bytes,
	knh_OutputStream_flush__nop,
	knh_OutputStream_close__nop
};

/* ======================================================================== */
/* [structs] */

void
knh_OutputStream_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	OutputStream *b = (OutputStream*)s;
	b->outptr = NULL;
	KNH_INITv(b->ba, KNH_NULL);
	b->drv = DRIVERS__nop;
	KNH_INITv(b->bconv, KNH_NULL);
	KNH_INITv(b->urn, knh_String_EMPTY());
	b->size = 0;
	b->line = 0;
	KNH_INITv(b->NEWLINE, knh_String_NL());
	KNH_INITv(b->TAB, knh_String_TAB());
	b->indent = 0;
}

/* ------------------------------------------------------------------------ */

#define _knh_OutputStream_struct_copy      NULL

/* ------------------------------------------------------------------------ */

#define _knh_OutputStream_struct_compare   NULL

/* ------------------------------------------------------------------------ */

void
knh_OutputStream_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	OutputStream *b = (OutputStream*)s;

	if(IS_SWEEP(gc) && b->outptr != NULL) {
		b->drv.fclose(ctx, b->outptr);
		b->outptr = NULL;
	}
	gc(ctx, b->ba);
	gc(ctx, b->bconv);
	gc(ctx, b->urn);
	gc(ctx, b->NEWLINE);
	gc(ctx, b->TAB);
}

/* ======================================================================== */
/* [methods] */

OutputStream *
new_OutputStream(Ctx *ctx, String *urn, knh_outptr_t *outptr, knh_outptr_drivers_t drv)
{
	OutputStream* b = (OutputStream*)knh_Object_malloc(ctx, CLASS_OutputStream);
	knh_OutputStream_struct_init(ctx, (Struct*)b, 0, NULL);
	b->outptr = outptr;
	if(b->outptr == NULL) {
		b->drv = DRIVERS__nop;	
	}
	else {
		b->drv = drv;
	}
	if(urn == NULL || IS_NULL(urn)) {
		KNH_SETv(ctx, b->urn, knh_String_EMPTY());
	}
	else {
		KNH_SETv(ctx, b->urn, urn);
	}		
	return b;
}

/* ======================================================================== */
/* [methods] */

void knh_OutputStream_putc(Ctx *ctx, OutputStream *b, int ch)
{
	b->drv.fputc(ctx, b->outptr, ch);
	b->size++;
}

/* ------------------------------------------------------------------------ */
/* @method void OutputStream.write(Bytes buf) */

void knh_OutputStream_write(Ctx *ctx, OutputStream *b, knh_bytes_t buf)
{
	b->drv.fwrite(ctx, b->outptr, (char*)buf.buf, buf.len);
	b->size += buf.len;
}

/* ------------------------------------------------------------------------ */
/* @method void OutputStream.flush() */

INLINE
void knh_OutputStream_flush(Ctx *ctx, OutputStream *b)
{
	b->drv.fflush(ctx, b->outptr);
}

/* ------------------------------------------------------------------------ */
/* @method void OutputStream.close() */

void knh_OutputStream_close(Ctx *ctx, OutputStream *b)
{
	b->drv.fclose(ctx, b->outptr);
	b->outptr = NULL;
	b->drv = DRIVERS__nop;
}

/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */

void knh_OutputStream_print_(Ctx *ctx, OutputStream *b, knh_bytes_t str, knh_bool_t isnl)
{
	if(str.len > 0) {
		if(IS_NULL(b->bconv)) {
			b->drv.fwrite(ctx, b->outptr, (char*)str.buf, str.len);
			b->size += str.len;
		}
		else {
			TODO();
		}
	}
	if(isnl) {
		knh_bytes_t buf = knh_String_tobytes(b->NEWLINE);
		b->drv.fwrite(ctx, b->outptr, (char*)buf.buf, buf.len);
		b->size += buf.len;
		b->drv.fflush(ctx, b->outptr);
	}
}

/* ------------------------------------------------------------------------ */

void knh_OutputStream_indent_inc(Ctx *ctx, OutputStream *b)
{
	b->indent++;
}

/* ------------------------------------------------------------------------ */

void knh_OutputStream_indent_dec(Ctx *ctx, OutputStream *b)
{
	b->indent--;
}

/* ------------------------------------------------------------------------ */

void knh_OutputStream_write_indent(Ctx *ctx, OutputStream *b)
{
	int i;
	for(i = 0; i < b->indent; i++) {
		knh_OutputStream_write(ctx, b, knh_String_tobytes(b->TAB));
	}
}

/* ======================================================================== */
/* [nop] */

knh_outptr_t* knh_OutputStream_open__nop(Ctx *ctx, knh_bytes_t n)
{
	return NULL;
}

/* ------------------------------------------------------------------------ */

void knh_OutputStream_putc__nop(Ctx *ctx, knh_outptr_t *ptr, int ch)
{

}

/* ------------------------------------------------------------------------ */

size_t 
knh_OutputStream_write__nop(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz)
{
	return bufsiz;
}

/* ------------------------------------------------------------------------ */

void 
knh_OutputStream_flush__nop(Ctx *ctx, knh_outptr_t *ptr)
{
	
}

/* ------------------------------------------------------------------------ */

void 
knh_OutputStream_close__nop(Ctx *ctx, knh_outptr_t *ptr)
{
	
}

/* ------------------------------------------------------------------------ */

OutputStream *new_OutputStream__NULL(Ctx *ctx)
{
	OutputStream* b = (OutputStream*)knh_Object_malloc(ctx, CLASS_OutputStream);
	knh_OutputStream_struct_init(ctx, (Struct*)b, 0, NULL);
	b->outptr = (knh_outptr_t*)NULL;
	KNH_SETv(ctx, b->urn, new_String__fast(ctx, CLASS_String, STEXT("/dev/null")));
	return b;
}

/* ======================================================================== */
/* [FILE] */

knh_outptr_t* knh_OutputStream_open__FILE(Ctx *ctx, knh_bytes_t file)
{
	char buf[KONOHA_FILEN_SIZE];
	knh_file_ospath(ctx, file, buf, sizeof(buf));
	
	FILE *fp = fopen(buf, "w");
	if(fp == NULL) {
		KNH_THROWf(ctx, "IO!!: cannot open: %s¥n", buf);
		fprintf(stderr, "konoha: Cannot open: %s\n", buf);
		return NULL;
	}
	return (knh_outptr_t*)fp;
}

/* ------------------------------------------------------------------------ */

void knh_OutputStream_putc__FILE(Ctx *ctx, knh_outptr_t *ptr, int ch)
{
	fputc(ch, (FILE*)ptr);
}

/* ------------------------------------------------------------------------ */

size_t 
knh_OutputStream_write__FILE(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz)
{
	return fwrite(buf, 1, bufsiz, (FILE*)ptr);
}

/* ------------------------------------------------------------------------ */

void 
knh_OutputStream_flush__FILE(Ctx *ctx, knh_outptr_t *ptr)
{
	fflush((FILE*)ptr);
}

/* ------------------------------------------------------------------------ */

void 
knh_OutputStream_close__FILE(Ctx *ctx, knh_outptr_t *ptr)
{
	fclose((FILE*)ptr);
}

/* ------------------------------------------------------------------------ */

OutputStream *new_OutputStream__FILE(Ctx *ctx, FILE *fp)
{
	OutputStream* b = (OutputStream*)knh_Object_malloc(ctx, CLASS_OutputStream);
	knh_OutputStream_struct_init(ctx, (Struct*)b, 0, NULL);
	b->outptr = (knh_outptr_t*)fp;
	if(fp == stdout) {
		KNH_SETv(ctx, b->urn, new_String__fast(ctx, CLASS_String, STEXT("/dev/stdout")));
		b->drv = DRIVERS__stdout;
	}
	else if(fp == stderr) {
		KNH_SETv(ctx, b->urn, new_String__fast(ctx, CLASS_String, STEXT("/dev/stderr")));
		b->drv = DRIVERS__stdout;
	}
	else {
		KNH_SETv(ctx, b->urn, new_String__fast(ctx, CLASS_String, STEXT("/dev/unknown")));
		b->drv = DRIVERS__FILE;
	}
	return b;
}

/* ======================================================================== */
/* [Bytes] */

void knh_OutputStream_putc__Bytes(Ctx *ctx, knh_outptr_t *ptr, int ch)
{
	OutputStream *b = (OutputStream*)ptr;
	knh_Bytes_putc(ctx, b->ba, ch);
}

/* ------------------------------------------------------------------------ */

size_t 
knh_OutputStream_write__Bytes(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz)
{
	OutputStream *b = (OutputStream*)ptr;
	knh_Bytes_write(ctx, b->ba, B2(buf, bufsiz));
	return bufsiz;
}

/* ------------------------------------------------------------------------ */

void 
knh_OutputStream_close__Bytes(Ctx *ctx, knh_outptr_t *ptr)
{
	OutputStream *b = (OutputStream*)ptr;
	KNH_SETv(ctx, b->ba, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

OutputStream *new_OutputStream__Bytes(Ctx *ctx, Bytes *ba)
{
	OutputStream* b = (OutputStream*)knh_Object_malloc(ctx, CLASS_OutputStream);
	knh_OutputStream_struct_init(ctx, (Struct*)b, 0, NULL);
	b->outptr = (knh_outptr_t*)b;
	if(!IS_NULL(ba)) {
		KNH_SETv(ctx, b->ba, ba);
		b->drv = DRIVERS__Bytes;
	}
	return b;
}


/* ======================================================================== */
/* [TFUNC] */

void
KNH_TFUNC_OUTPUTSTREAM_OPEN(Ctx *ctx, char *n, f_outptr_open f)
{
	if(f == NULL) f = knh_OutputStream_open__nop;
	KNH_TFUNC(ctx, n, (void*)f);
}

/* ------------------------------------------------------------------------ */

void
KNH_TFUNC_OUTPUTSTREAM_PUTC(Ctx *ctx, char *n, f_outptr_putc f)
{
	if(f == NULL) f = knh_OutputStream_putc__nop;
	KNH_TFUNC(ctx, n, (void*)f);
}

/* ------------------------------------------------------------------------ */

void
KNH_TFUNC_OUTPUTSTREAM_WRITE(Ctx *ctx, char *n, f_outptr_write f)
{
	if(f == NULL) f = knh_OutputStream_write__nop;
	KNH_TFUNC(ctx, n, (void*)f);
}

/* ------------------------------------------------------------------------ */

void
KNH_TFUNC_OUTPUTSTREAM_FLUSH(Ctx *ctx, char *n, f_outptr_flush f)
{
	if(f == NULL) f = knh_OutputStream_flush__nop;
	KNH_TFUNC(ctx, n, (void*)f);
}

/* ------------------------------------------------------------------------ */

void
KNH_TFUNC_OUTPUTSTREAM_CLOSE(Ctx *ctx, char *n, f_outptr_close f)
{
	if(f == NULL) f = knh_OutputStream_close__nop;
	KNH_TFUNC(ctx, n, (void*)f);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
