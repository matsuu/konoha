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

#define SELF STRUCT_InputStream


/* ======================================================================== */
/* [drivers] */

static knh_inptr_drivers_t DRIVERS__nop = {
	knh_InputStream_open__nop,
	knh_InputStream_getc__nop,
	knh_InputStream_read__nop,
	knh_InputStream_close__nop
};

static knh_inptr_drivers_t DRIVERS__FILE = {
	knh_InputStream_open__FILE,
	knh_InputStream_getc__FILE,
	knh_InputStream_read__FILE,
	knh_InputStream_close__FILE
};

static knh_inptr_drivers_t DRIVERS__stdin = {
	knh_InputStream_open__nop,
	knh_InputStream_getc__FILE,
	knh_InputStream_read__FILE,
	knh_InputStream_close__nop
};

static knh_inptr_drivers_t DRIVERS__Bytes = {
	knh_InputStream_open__nop,
	knh_InputStream_getc__Bytes,
	knh_InputStream_read__Bytes,
	knh_InputStream_close__Bytes
};

#if defined(KONOHA_USING_INPUTSTREAM_HTTP)
static knh_inptr_drivers_t DRIVERS__http = {
	knh_InputStream_open__http,
	knh_InputStream_getc__http,
	knh_InputStream_read__http,
	knh_InputStream_close__http
};
#endif

/* ======================================================================== */
/* [structs] */

void
knh_InputStream_struct_init(Ctx *ctx, Struct *s, int init, Object *cs)
{
	InputStream *b = (InputStream*)s;
	b->inptr = NULL;
	KNH_INITv(b->ba, KNH_NULL);
	b->bapos = 0;
	b->baend = 0;
	b->drv = DRIVERS__nop;
	KNH_INITv(b->bconv, KNH_NULL);
	KNH_INITv(b->urn, knh_String_EMPTY());	
	b->size    = 0;
	b->line    = 1;
	b->prev    = '\n';
	b->filen   = 0;
}

/* ------------------------------------------------------------------------ */

#define _knh_InputStream_struct_copy   NULL

/* ------------------------------------------------------------------------ */

#define _knh_InputStream_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void
knh_InputStream_struct_traverse(Ctx *ctx, Struct *s, f_gc gc)
{
	InputStream *b = (InputStream*)s;
	if(IS_SWEEP(gc) && b->inptr != NULL) {
		b->drv.fclose(ctx, b->inptr);
		b->inptr = NULL;
	}
	gc(ctx, b->ba);
	gc(ctx, b->bconv);
	gc(ctx, b->urn);
}

/* ======================================================================== */
/* [constructors] */

InputStream *
new_InputStream(Ctx *ctx, String *urn, knh_inptr_t *inptr, knh_inptr_drivers_t drv)
{
	InputStream* b = (InputStream*)knh_Object_malloc(ctx, CLASS_InputStream);
	knh_InputStream_struct_init(ctx, (Struct*)b, 0, NULL);
	b->inptr = inptr;
	if(b->inptr == NULL) {
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

///* ------------------------------------------------------------------------ */
///* @method InputStream! InputStream.new(String! urn) */
//
//InputStream *knh_InputStream_new(Ctx *ctx, InputStream *b, knh_bytes_t urn)
//{
//	return b;
//}

/* ======================================================================== */
/* [methods] */

void knh_InputStream_open(Ctx *ctx, InputStream *b, String *urn)
{
	KNH_SETv(ctx, b->urn, urn);
	if(knh_String_startsWith(urn, STEXT("file:"))) {
		b->drv = DRIVERS__FILE;
	}
#if defined(KONOHA_USING_INPUTSTREAM__http)
	else if(knh_String_startsWith(urn, STEXT("http:"))) {
		b->drv = DRIVERS__http;
	}
#endif
	else if(knh_bytes_index(knh_String_tobytes(urn), ':') != -1) {
		b->drv = DRIVERS__FILE;
	}
	b->inptr = b->drv.fopen(ctx, knh_String_tobytes(urn));
	if(b->inptr == NULL) {
		b->drv = DRIVERS__nop;
	}
}

/* ------------------------------------------------------------------------ */

int knh_InputStream_getc(Ctx *ctx, InputStream *b)
{
	int ch = b->drv.fgetc(ctx, b->inptr);
	if(ch != EOF) {
		b->size++;
		if(ch == '\n') {
			if(b->prev != '\r') {
				b->line++;
			}
		}else if(ch == '\r') {
			b->line++;
		}
		b->prev = ch;
	}
	return ch;
}

/* ------------------------------------------------------------------------ */

size_t 
knh_InputStream_read(Ctx *ctx, InputStream *b, char *buf, size_t bufsiz)
{
	size_t size = b->drv.fread(ctx, b->inptr, buf, bufsiz);
	b->size += size;
	return size;
}

/* ------------------------------------------------------------------------ */
/* @method String InputStream.readLine() */

String* knh_InputStream_readLine(Ctx *ctx, InputStream *b)
{
	int ch;	
	knh_buffer_t cb = knh_Context_buffer(ctx);
	while((ch = knh_InputStream_getc(ctx, b)) != EOF) {
		if(ch == '\r') {
			return new_String__buffer(ctx, CLASS_String, cb);
		}
		if(ch == '\n') {
			if(b->prev == '\r') continue;
		}
		knh_Bytes_putc(ctx, cb.ba, ch);
	}
	if(knh_buffer_size(cb) != 0) {
		return new_String__buffer(ctx, CLASS_String, cb);
	}
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */
/* @method void InputStream.close() */

INLINE
void knh_InputStream_close(Ctx *ctx, InputStream *b)
{
	b->drv.fclose(ctx, b->inptr);
	b->inptr = NULL;
	b->drv = DRIVERS__nop;
}

/* ======================================================================== */
/* [nop] */

knh_inptr_t* knh_InputStream_open__nop(Ctx *ctx, knh_bytes_t n)
{
	return NULL;
}

/* ------------------------------------------------------------------------ */

int knh_InputStream_getc__nop(Ctx *ctx, knh_inptr_t *ptr)
{
	return EOF;
}

/* ------------------------------------------------------------------------ */

size_t 
knh_InputStream_read__nop(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

void 
knh_InputStream_close__nop(Ctx *ctx, knh_inptr_t *ptr)
{
	
}

/* ------------------------------------------------------------------------ */

InputStream *new_InputStream__NULL(Ctx *ctx)
{
	InputStream* b = (InputStream*)knh_Object_malloc(ctx, CLASS_InputStream);
	knh_InputStream_struct_init(ctx, (Struct*)b, 0, NULL);
	b->inptr = (knh_inptr_t*)NULL;
	KNH_SETv(ctx, b->urn, new_String__fast(ctx, CLASS_String, STEXT("/dev/null")));
	return b;
}

/* ======================================================================== */
/* [FILE] */

knh_inptr_t* knh_InputStream_open__FILE(Ctx *ctx, knh_bytes_t file)
{
	char buf[KONOHA_FILEN_SIZE];
	knh_file_ospath(ctx, file, buf, sizeof(buf));
	
	FILE *fp = fopen(buf, "r");
	if(fp == NULL) {
		KNH_THROWf(ctx, "IO!!: cannot open: %s¥n", buf);
		return NULL;
	}
	return (knh_inptr_t*)fp;
}

/* ------------------------------------------------------------------------ */

int knh_InputStream_getc__FILE(Ctx *ctx, knh_inptr_t *ptr)
{
	FILE *fp = (FILE*)ptr;
	return fgetc(fp);
}

/* ------------------------------------------------------------------------ */

size_t 
knh_InputStream_read__FILE(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz)
{
	FILE *fp = (FILE*)ptr;
	return fread(buf, bufsiz, 1, fp);
}

/* ------------------------------------------------------------------------ */

void 
knh_InputStream_close__FILE(Ctx *ctx, knh_inptr_t *ptr)
{
	FILE *fp = (FILE*)ptr;
	fclose(fp);
}

/* ------------------------------------------------------------------------ */

InputStream *new_InputStream__FILE(Ctx *ctx, FILE *fp)
{
	InputStream* b = (InputStream*)knh_Object_malloc(ctx, CLASS_InputStream);
	knh_InputStream_struct_init(ctx, (Struct*)b, 0, NULL);
	b->inptr = (knh_inptr_t*)fp;
	if(fp == stdin) {
		b->drv = DRIVERS__stdin;
		KNH_SETv(ctx, b->urn, new_String__fast(ctx, CLASS_String, STEXT("/dev/stdin")));
	}
	else {
		b->drv = DRIVERS__FILE;
		KNH_SETv(ctx, b->urn, new_String__fast(ctx, CLASS_String, STEXT("/dev/unknown")));
	}
	return b;
}

/* ======================================================================== */
/* [Bytes] */

int knh_InputStream_getc__Bytes(Ctx *ctx, knh_inptr_t *ptr)
{
	InputStream *b = (InputStream*)ptr;
	if(IS_NULL(b->ba) || !(b->bapos < b->baend)) return EOF;
	knh_uchar_t *p = (knh_uchar_t*)knh_Bytes_tochar(b->ba);
	int ch = p[b->bapos]; 
	b->bapos++;
	return ch;
}

/* ------------------------------------------------------------------------ */

size_t 
knh_InputStream_read__Bytes(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz)
{
	InputStream *b = (InputStream*)ptr;
	if(IS_NULL(b->ba) || !(b->bapos < b->baend)) return 0;
	char *p = knh_Bytes_tochar(b->ba);
	size_t psize = b->baend - b->bapos;
	if (bufsiz < psize) psize = bufsiz;
	knh_memcpy(buf, p, psize);
	b->bapos += psize;
	return psize;
}

/* ------------------------------------------------------------------------ */

void 
knh_InputStream_close__Bytes(Ctx *ctx, knh_inptr_t *ptr)
{
	InputStream *b = (InputStream*)ptr;
	KNH_SETv(ctx, b->ba, KNH_NULL);
	b->bapos = 0;
	b->baend = 0;
}

/* ------------------------------------------------------------------------ */

InputStream *new_InputStream__Bytes(Ctx *ctx, Bytes *ba, size_t s, size_t e)
{
	InputStream* b = (InputStream*)knh_Object_malloc(ctx, CLASS_InputStream);
	knh_InputStream_struct_init(ctx, (Struct*)b, 0, NULL);
	b->inptr = (knh_inptr_t*)b;
	KNH_SETv(ctx, b->ba, ba);
	DEBUG_ASSERT(e <= knh_Bytes_size(ba));
	DEBUG_ASSERT(s <= e);
	b->bapos   = s;
	b->baend   = e;
	b->drv = DRIVERS__Bytes;
	return b;
}

/* ======================================================================== */
/* [mappings] */

/* ======================================================================== */
/* [iterators] */

Object* knh_InputStream_line_next(Ctx *ctx, Iterator *it)
{
	InputStream *b = (InputStream*)knh_Iterator_source(it);
	int ch;	
	knh_buffer_t cb = knh_Context_buffer(ctx);
	
	while((ch = knh_InputStream_getc(ctx, b)) != EOF) {
		if(ch == 13) continue;
		if(ch == 10) {
			return new_String__buffer(ctx, CLASS_String, cb);
		}
		knh_Bytes_putc(ctx, cb.ba, ch);
	}
	if(knh_buffer_size(cb) != 0) {
		return new_String__buffer(ctx, CLASS_String, cb);
	}
	return KNH_NULL;
}

/* ------------------------------------------------------------------------ */
/* @map InputStream String.. */

Object* knh_InputStream_String__(Ctx *ctx, Object *self, MapMap *map)
{
	return new_Iterator(ctx, CLASS_String, self, knh_InputStream_line_next);
}

/* ======================================================================== */
/* [movabletext] */

/* @method void InputStream.%dump(OutputStream w, Any m) */

void knh_InputStream__dump(Ctx *ctx, InputStream *b, OutputStream *w, Any *m)
{
	
}

/* ======================================================================== */
/* [TFUNC] */

void
KNH_TFUNC_INPUTSTREAM_OPEN(Ctx *ctx, char *n, f_inptr_open f)
{
	if(f == NULL) f = knh_InputStream_open__nop;
	KNH_TFUNC(ctx, n, (void*)f);
}

/* ------------------------------------------------------------------------ */

void
KNH_TFUNC_INPUTSTREAM_GETC(Ctx *ctx, char *n, f_inptr_getc f)
{
	if(f == NULL) f = knh_InputStream_getc__nop;
	KNH_TFUNC(ctx, n, (void*)f);
}

/* ------------------------------------------------------------------------ */

void
KNH_TFUNC_INPUTSTREAM_READ(Ctx *ctx, char *n, f_inptr_read f)
{
	if(f == NULL) f = knh_InputStream_read__nop;
	KNH_TFUNC(ctx, n, (void*)f);
}

/* ------------------------------------------------------------------------ */

void
KNH_TFUNC_INPUTSTREAM_CLOSE(Ctx *ctx, char *n, f_inptr_close f)
{
	if(f == NULL) f = knh_InputStream_close__nop;
	KNH_TFUNC(ctx, n, (void*)f);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
