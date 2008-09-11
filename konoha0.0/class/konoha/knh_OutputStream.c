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

static knh_outptr_t* knh_OutputStream_open__NOP(Ctx *ctx, knh_bytes_t n, char *mode);
static void knh_OutputStream_putc__NOP(Ctx *ctx, knh_outptr_t *ptr, int ch);
static size_t knh_OutputStream_write__NOP(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz);
static void knh_OutputStream_flush__NOP(Ctx *ctx, knh_outptr_t *ptr);
static void knh_OutputStream_close__NOP(Ctx *ctx, knh_outptr_t *ptr);

static knh_outptr_t* knh_OutputStream_open__FILE(Ctx *ctx, knh_bytes_t file, char *mode);
static void knh_OutputStream_putc__FILE(Ctx *ctx, knh_outptr_t *ptr, int ch);
static size_t knh_OutputStream_write__FILE(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz);
static void knh_OutputStream_flush__FILE(Ctx *ctx, knh_outptr_t *ptr);
static void knh_OutputStream_close__FILE(Ctx *ctx, knh_outptr_t *ptr);

static void knh_OutputStream_putc__Bytes(Ctx *ctx, knh_outptr_t *ptr, int ch);
static size_t knh_OutputStream_write__Bytes(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz);
static void knh_OutputStream_close__Bytes(Ctx *ctx, knh_outptr_t *ptr);

static knh_outptr_drvapi_t OUT__NOP = {
	KNH_DRVAPI_TYPE__OUTPUTSTREAM, "nop",
	knh_OutputStream_open__NOP,
	knh_OutputStream_putc__NOP,
	knh_OutputStream_write__NOP,
	knh_OutputStream_flush__NOP,
	knh_OutputStream_close__NOP
};

static knh_outptr_drvapi_t OUT__FILE = {
	KNH_DRVAPI_TYPE__OUTPUTSTREAM, "file",
	knh_OutputStream_open__FILE,
	knh_OutputStream_putc__FILE,
	knh_OutputStream_write__FILE,
	knh_OutputStream_flush__FILE,
	knh_OutputStream_close__FILE
};

static knh_outptr_drvapi_t OUT__stdout = {
	KNH_DRVAPI_TYPE__OUTPUTSTREAM, "stdout",
	knh_OutputStream_open__NOP,
	knh_OutputStream_putc__FILE,
	knh_OutputStream_write__FILE,
	knh_OutputStream_flush__FILE,
	knh_OutputStream_close__NOP
};

static knh_outptr_drvapi_t OUT__Bytes = {
	KNH_DRVAPI_TYPE__OUTPUTSTREAM, "Bytes",
	knh_OutputStream_open__NOP,
	knh_OutputStream_putc__Bytes,
	knh_OutputStream_write__Bytes,
	knh_OutputStream_flush__NOP,
	knh_OutputStream_close__Bytes
};

/* ------------------------------------------------------------------------ */

static
knh_outptr_drvapi_t *knh_System_getOutputStreamDriver(Ctx *ctx, knh_bytes_t name)
{
	knh_outptr_drvapi_t *p = (knh_outptr_drvapi_t *)knh_System_getDRVAPI(ctx, KNH_DRVAPI_TYPE__OUTPUTSTREAM, name);
	if(p == NULL) {
		KNH_WARNING(ctx, "OutputStream: unsupported scheme '%s'", name);
		p = &OUT__NOP;
	}
	return p;
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_addOutputStreamDriver(Ctx *ctx, char *alias, knh_outptr_drvapi_t *d)
{
	KNH_TDRVAPI(ctx, alias, (knh_drvapi_t*)d);
}

/* ------------------------------------------------------------------------ */

void KNHINIT init_OutputStream(Ctx *ctx)
{
	konoha_addOutputStreamDriver(ctx, NULL, &OUT__NOP);
	konoha_addOutputStreamDriver(ctx, NULL, &OUT__FILE);
	konoha_addOutputStreamDriver(ctx, NULL, &OUT__stdout);
	konoha_addOutputStreamDriver(ctx, NULL, &OUT__Bytes);
}

/* ======================================================================== */
/* [structs] */

void
knh_OutputStream_struct_init(Ctx *ctx, knh_OutputStream_struct *b, int init, Object *cs)
{
	b->outptr = NULL;
	KNH_INITv(b->ba, KNH_NULL);
	b->apis = OUT__NOP;
	KNH_INITv(b->bconv, KNH_NULL);
	KNH_INITv(b->enc, TS_ENCODING);
	KNH_INITv(b->urn, TS_DEVNULL);
	b->size = 0;
	b->line = 0;
	KNH_INITv(b->NEWLINE, TS_LF);
	KNH_INITv(b->TAB, TS_TAB);
	b->indent = 0;
}

/* ------------------------------------------------------------------------ */

#define _knh_OutputStream_struct_copy      NULL

/* ------------------------------------------------------------------------ */

#define _knh_OutputStream_struct_compare   NULL

/* ------------------------------------------------------------------------ */

void
knh_OutputStream_struct_traverse(Ctx *ctx, knh_OutputStream_struct *b, f_traverse gc)
{
	if(IS_SWEEP(gc) && b->outptr != NULL) {
		b->apis.fclose(ctx, b->outptr);
		b->outptr = NULL;
	}
	gc(ctx, UP(b->ba));
	gc(ctx, UP(b->enc));
	gc(ctx, UP(b->bconv));
	gc(ctx, UP(b->urn));
	gc(ctx, UP(b->NEWLINE));
	gc(ctx, UP(b->TAB));
}

/* ======================================================================== */
/* [methods] */

Object *knh_OutputStream_open(Ctx *ctx, OutputStream *o, String *urn, String *mode)
{
	knh_bytes_t fname = knh_String_tobytes(urn);
	knh_index_t loc = knh_bytes_index(fname, ':');
	if(loc == -1 || (loc == 1 && isalpha(fname.buf[0]))) {  /* 'C:/' */
		DP(o)->apis = *(knh_System_getOutputStreamDriver(ctx, STEXT("file")));
	}
	else {
		DP(o)->apis = *(knh_System_getOutputStreamDriver(ctx, knh_bytes_first(fname, loc)));
	}
	if(IS_NULL(mode)) {
		DP(o)->outptr = DP(o)->apis.fopen(ctx, fname, "w");
	}
	else {
		DP(o)->outptr = DP(o)->apis.fopen(ctx, fname, knh_String_tochar(mode));
	}
	if(DP(o)->outptr == NULL) {
		char buff[FILENAME_BUFSIZ];
		knh_snprintf(buff, sizeof(buff), "IO!!: cannot open %s", (char*)fname.buf);
		DP(o)->apis = OUT__NOP;
		return (Object*)new_Nue__s(ctx, buff);
	}
	knh_OutputStream_setBOL(o,1);
	knh_OutputStream_setAutoFlush(o,1);
	return (Object*)o;
}

/* ======================================================================== */
/* [methods] */

void knh_OutputStream_putc(Ctx *ctx, OutputStream *o, int ch)
{
	DP(o)->apis.fputc(ctx, DP(o)->outptr, ch);
	DP(o)->size++;
}

/* ------------------------------------------------------------------------ */

void knh_OutputStream_write(Ctx *ctx, OutputStream *o, knh_bytes_t buf)
{
	DP(o)->apis.fwrite(ctx, DP(o)->outptr, (char*)buf.buf, buf.len);
	DP(o)->size += buf.len;
}

/* ------------------------------------------------------------------------ */
/* @method void OutputStream.flush() */

void knh_OutputStream_flush(Ctx *ctx, OutputStream *o)
{
	DP(o)->apis.fflush(ctx, DP(o)->outptr);
}

/* ------------------------------------------------------------------------ */
/* @method void OutputStream.close() */

void knh_OutputStream_close(Ctx *ctx, OutputStream *o)
{
	DP(o)->apis.fclose(ctx, DP(o)->outptr);
	DP(o)->outptr = NULL;
	DP(o)->apis = OUT__NOP;
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
			DP(o)->apis.fwrite(ctx, DP(o)->outptr, (char*)str.buf, str.len);
			DP(o)->size += str.len;
		}
		else {
			Bytes *ba = knh_Context_openBConvBuf(ctx);
			DP(o)->size += knh_BytesConv_conv(ctx, DP(o)->bconv, str, ba);
			//DBG2_(DP(o)->apis.fwrite(ctx, DP(o)->outptr, (char*)str.buf, str.len);)
			DP(o)->apis.fwrite(ctx, DP(o)->outptr, knh_Bytes_tochar(ba), ba->size);
			knh_Context_closeBConvBuf(ctx, ba);
		}
	}
	if(isnl) {
		knh_write_EOL(ctx, o);
	}
}


/* ======================================================================== */
/* ======================================================================== */
/* [nop] */

static
knh_outptr_t* knh_OutputStream_open__NOP(Ctx *ctx, knh_bytes_t n, char *mode)
{
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
void knh_OutputStream_putc__NOP(Ctx *ctx, knh_outptr_t *ptr, int ch)
{

}

/* ------------------------------------------------------------------------ */

static
size_t knh_OutputStream_write__NOP(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz)
{
	return bufsiz;
}

/* ------------------------------------------------------------------------ */

static
void knh_OutputStream_flush__NOP(Ctx *ctx, knh_outptr_t *ptr)
{

}

/* ------------------------------------------------------------------------ */

static
void knh_OutputStream_close__NOP(Ctx *ctx, knh_outptr_t *ptr)
{

}

/* ======================================================================== */
/* [FILE] */

static
knh_outptr_t* knh_OutputStream_open__FILE(Ctx *ctx, knh_bytes_t file, char *mode)
{
	char buf[FILENAME_BUFSIZ];
	knh_format_ospath(buf, sizeof(buf), file);
	{
		FILE *fp = knh_fopen(buf, mode);
		if(fp == NULL) {
			KNH_THROWf(ctx, "IO!!: cannot open: %s, mode='%s'\n", (char*)file.buf, mode);
			return NULL;
		}
		return (knh_outptr_t*)fp;
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_OutputStream_putc__FILE(Ctx *ctx, knh_outptr_t *ptr, int ch)
{
	fputc(ch, (FILE*)ptr);
}

/* ------------------------------------------------------------------------ */

static
size_t knh_OutputStream_write__FILE(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz)
{
	return fwrite(buf, 1, bufsiz, (FILE*)ptr);
}

/* ------------------------------------------------------------------------ */

static
void knh_OutputStream_flush__FILE(Ctx *ctx, knh_outptr_t *ptr)
{
	fflush((FILE*)ptr);
}

/* ------------------------------------------------------------------------ */

static
void knh_OutputStream_close__FILE(Ctx *ctx, knh_outptr_t *ptr)
{
	knh_fclose((FILE*)ptr);
}

/* ------------------------------------------------------------------------ */

OutputStream *new_OutputStream__FILE(Ctx *ctx, FILE *fp)
{
	OutputStream* o = (OutputStream*)new_Object_malloc(ctx, FLAG_OutputStream, CLASS_OutputStream, sizeof(knh_OutputStream_struct));
	knh_OutputStream_struct_init(ctx, DP(o), 0, NULL);
	knh_OutputStream_setBOL(o, 1);
	knh_OutputStream_setAutoFlush(o, 1);
	DP(o)->outptr = (knh_outptr_t*)fp;
	if(fp == stdout) {
		KNH_SETv(ctx, DP(o)->urn, TS_DEVSTDOUT);
		DP(o)->apis = OUT__stdout;
	}
	else if(fp == stderr) {
		KNH_SETv(ctx, DP(o)->urn, TS_DEVSTDERR);
		DP(o)->apis = OUT__stdout;
	}
	else {
		DP(o)->apis = OUT__FILE;
	}
	return o;
}

/* ======================================================================== */
/* [Bytes] */

static
void knh_OutputStream_putc__Bytes(Ctx *ctx, knh_outptr_t *ptr, int ch)
{
	OutputStream *o = (OutputStream*)ptr;
	knh_Bytes_putc(ctx, DP(o)->ba, ch);
}

/* ------------------------------------------------------------------------ */

static
size_t knh_OutputStream_write__Bytes(Ctx *ctx, knh_outptr_t *ptr, char *buf, size_t bufsiz)
{
	OutputStream *o = (OutputStream*)ptr;
	knh_Bytes_write(ctx, DP(o)->ba, B2(buf, bufsiz));
	return bufsiz;
}

/* ------------------------------------------------------------------------ */

static
void knh_OutputStream_close__Bytes(Ctx *ctx, knh_outptr_t *ptr)
{
	OutputStream *o = (OutputStream*)ptr;
	KNH_SETv(ctx, DP(o)->ba, KNH_NULL);
}

/* ------------------------------------------------------------------------ */

OutputStream *new_OutputStream__Bytes(Ctx *ctx, Bytes *ba)
{
	OutputStream* o = (OutputStream*)new_Object_malloc(ctx, FLAG_OutputStream, CLASS_OutputStream, sizeof(knh_OutputStream_struct));
	knh_OutputStream_struct_init(ctx, DP(o), 0, NULL);
	knh_OutputStream_setBOL(o, 1);
	//knh_OutputStream_setAutoFlush(o, 1);
	if(!IS_NULL(ba)) {
		KNH_SETv(ctx, DP(o)->ba, ba);
		DP(o)->apis = OUT__Bytes;
	}
	DP(o)->outptr = (knh_outptr_t*)o;
	return o;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
