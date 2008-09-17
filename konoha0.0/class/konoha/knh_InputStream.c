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

static knh_inptr_t* knh_InputStream_open__NOP(Ctx *ctx, knh_bytes_t n);
static int knh_InputStream_getc__NOP(Ctx *ctx, knh_inptr_t *ptr);
static size_t knh_InputStream_read__NOP(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz);
static void knh_InputStream_close__NOP(Ctx *ctx, knh_inptr_t *ptr);

static knh_inptr_t* knh_InputStream_open__FILE(Ctx *ctx, knh_bytes_t file);
static int knh_InputStream_getc__FILE(Ctx *ctx, knh_inptr_t *ptr);
static size_t knh_InputStream_read__FILE(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz);
static void knh_InputStream_close__FILE(Ctx *ctx, knh_inptr_t *ptr);

static int knh_InputStream_getc__Bytes(Ctx *ctx, knh_inptr_t *ptr);
static size_t knh_InputStream_read__Bytes(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz);
static void knh_InputStream_close__Bytes(Ctx *ctx, knh_inptr_t *ptr);

/* ======================================================================== */

static knh_inptr_drvapi_t IN__NOP = {
	KNH_DRVAPI_TYPE__INPUTSTREAM, "NOP",
	knh_InputStream_open__NOP,
	knh_InputStream_getc__NOP,
	knh_InputStream_read__NOP,
	knh_InputStream_close__NOP
};

static knh_inptr_drvapi_t IN__FILE = {
	KNH_DRVAPI_TYPE__INPUTSTREAM, "file",
	knh_InputStream_open__FILE,
	knh_InputStream_getc__FILE,
	knh_InputStream_read__FILE,
	knh_InputStream_close__FILE
};

static knh_inptr_drvapi_t IN__stdin = {
	KNH_DRVAPI_TYPE__INPUTSTREAM, "stdin",
	knh_InputStream_open__NOP,
	knh_InputStream_getc__FILE,
	knh_InputStream_read__FILE,
	knh_InputStream_close__NOP
};

static knh_inptr_drvapi_t IN__Bytes = {
	KNH_DRVAPI_TYPE__INPUTSTREAM, "Bytes",
	knh_InputStream_open__NOP,
	knh_InputStream_getc__Bytes,
	knh_InputStream_read__Bytes,
	knh_InputStream_close__Bytes
};

/* ------------------------------------------------------------------------ */

static
knh_inptr_drvapi_t *knh_System_getInputStreamDriver(Ctx *ctx, knh_bytes_t name)
{
	knh_inptr_drvapi_t *p = (knh_inptr_drvapi_t *)knh_System_getDRVAPI(ctx, KNH_DRVAPI_TYPE__INPUTSTREAM, name);
	if(p == NULL) {
		KNH_WARNING(ctx, "InputStream: unsupported scheme '%s'", name);
		p = &IN__NOP;
	}
	return p;
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_addInputStreamDriver(Ctx *ctx, char *alias, knh_inptr_drvapi_t *d)
{
	KNH_TDRVAPI(ctx, alias, (knh_drvapi_t*)d);
}

/* ------------------------------------------------------------------------ */

void KNHINIT init_InputStream(Ctx *ctx)
{
	konoha_addInputStreamDriver(ctx, NULL, &IN__NOP);
	konoha_addInputStreamDriver(ctx, NULL, &IN__FILE);
	konoha_addInputStreamDriver(ctx, NULL, &IN__stdin);
	konoha_addInputStreamDriver(ctx, NULL, &IN__Bytes);
}

/* ======================================================================== */
/* [structs] */

void
knh_InputStream_struct_init(Ctx *ctx, knh_InputStream_struct *b, int init, Object *cs)
{
	b->inptr = NULL;
	KNH_INITv(b->ba, KNH_NULL);
	b->bapos = 0;
	b->baend = 0;
	b->apis = IN__NOP;
	KNH_INITv(b->bconv, KNH_NULL);
	KNH_INITv(b->enc, TS_ENCODING);
	KNH_INITv(b->urn, TS_DEVNULL);
	b->size    = 0;
	b->line    = 1;
	b->prev    = '\n';
	b->fileid   = 0;
}

/* ------------------------------------------------------------------------ */

#define _knh_InputStream_struct_copy   NULL

/* ------------------------------------------------------------------------ */

#define _knh_InputStream_struct_compare  NULL

/* ------------------------------------------------------------------------ */

void
knh_InputStream_struct_traverse(Ctx *ctx, knh_InputStream_struct *b, f_traverse gc)
{
	if(IS_SWEEP(gc) && b->inptr != NULL) {
		b->apis.fclose(ctx, b->inptr);
		b->inptr = NULL;
	}
	gc(ctx, UP(b->ba));
	gc(ctx, UP(b->enc));
	gc(ctx, UP(b->bconv));
	gc(ctx, UP(b->urn));
}

/* ======================================================================== */
/* [methods] */

Object *knh_InputStream_open(Ctx *ctx, InputStream *o, String *urn)
{
	knh_bytes_t fname = knh_String_tobytes(urn);
	knh_index_t loc = knh_bytes_index(fname, ':');
	if(loc == -1 || (loc == 1 && isalpha(fname.buf[0]))) {  /* 'C:/' */
		DP(o)->apis = *(knh_System_getInputStreamDriver(ctx, STEXT("file")));
	}
	else {
		DP(o)->apis = *(knh_System_getInputStreamDriver(ctx, knh_bytes_first(fname, loc)));
	}
	DP(o)->inptr = DP(o)->apis.fopen(ctx, fname);
	if(DP(o)->inptr == NULL) {
		char buff[FILENAME_BUFSIZ];
		knh_snprintf(buff, sizeof(buff), "IO!!: %s", (char*)fname.buf);
		DP(o)->apis = IN__NOP;
		return (Object*)new_Nue__s(ctx, buff);
	}
	return (Object*)o;
}

/* ------------------------------------------------------------------------ */

int knh_InputStream_getc(Ctx *ctx, InputStream *b)
{
	int ch = DP(b)->apis.fgetc(ctx, DP(b)->inptr);
	if(ch != EOF) {
		DP(b)->size++;
		if(ch == '\n') {
			if(DP(b)->prev != '\r') {
				DP(b)->line++;
			}
		}else if(ch == '\r') {
			DP(b)->line++;
		}
		DP(b)->prev = ch;
	}
	return ch;
}

/* ------------------------------------------------------------------------ */

size_t
knh_InputStream_read(Ctx *ctx, InputStream *b, char *buf, size_t bufsiz)
{
	size_t size = DP(b)->apis.fread(ctx, DP(b)->inptr, buf, bufsiz);
	DP(b)->size += size;
	return size;
}
/* ------------------------------------------------------------------------ */
/* @method String InputStream.readLine() */

String* knh_InputStream_readLine(Ctx *ctx, InputStream *b)
{
	int ch;
	knh_wbuf_t cb = knh_Context_wbuf(ctx);
	while((ch = knh_InputStream_getc(ctx, b)) != EOF) {
		if(ch == '\r') {
			return new_String__wbufconv(ctx, cb, DP(b)->bconv);
		}
		if(ch == '\n') {
			if(DP(b)->prev == '\r') continue;
			return new_String__wbufconv(ctx, cb, DP(b)->bconv);
		}
		knh_Bytes_putc(ctx, cb.ba, ch);
	}
	if(knh_wbuf_size(cb) != 0) {
		return new_String__wbufconv(ctx, cb, DP(b)->bconv);
	}
	return (String*)KNH_NULL;
}

/* ------------------------------------------------------------------------ */
/* @method void InputStream.close() */

INLINE
void knh_InputStream_close(Ctx *ctx, InputStream *b)
{
	DP(b)->apis.fclose(ctx, DP(b)->inptr);
	DP(b)->inptr = NULL;
	DP(b)->apis = IN__NOP;
}

/* ======================================================================== */
/* [NOP] */

static
knh_inptr_t* knh_InputStream_open__NOP(Ctx *ctx, knh_bytes_t n)
{
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
int knh_InputStream_getc__NOP(Ctx *ctx, knh_inptr_t *ptr)
{
	return EOF;
}

/* ------------------------------------------------------------------------ */

static size_t knh_InputStream_read__NOP(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

static void knh_InputStream_close__NOP(Ctx *ctx, knh_inptr_t *ptr)
{

}

/* ======================================================================== */
/* [FILE] */

static knh_inptr_t* knh_InputStream_open__FILE(Ctx *ctx, knh_bytes_t file)
{
	char buf[FILENAME_BUFSIZ];
	knh_format_ospath(buf, sizeof(buf), file);
	DBG2_P("opening '%s'", buf);
	{
		FILE *fp = knh_fopen(buf, "r");
		if(fp == NULL) {
			KNH_THROWf(ctx, "IO!!: cannot open: %s\n", (char*)file.buf);
			return NULL;
		}
		return (knh_inptr_t*)fp;
	}
}

/* ------------------------------------------------------------------------ */

static int knh_InputStream_getc__FILE(Ctx *ctx, knh_inptr_t *ptr)
{
	FILE *fp = (FILE*)ptr;
	return fgetc(fp);
}

/* ------------------------------------------------------------------------ */

static
size_t knh_InputStream_read__FILE(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz)
{
	FILE *fp = (FILE*)ptr;
	return fread(buf, bufsiz, 1, fp);
}

/* ------------------------------------------------------------------------ */

static
void knh_InputStream_close__FILE(Ctx *ctx, knh_inptr_t *ptr)
{
	FILE *fp = (FILE*)ptr;
	knh_fclose(fp);
}

/* ------------------------------------------------------------------------ */

InputStream *new_InputStream__FILE(Ctx *ctx, FILE *fp)
{
	InputStream* o =
		(InputStream*)new_Object_malloc(ctx, FLAG_InputStream, CLASS_InputStream, sizeof(knh_InputStream_struct));
	knh_InputStream_struct_init(ctx, DP(o), 0, NULL);

	DP(o)->inptr = (knh_inptr_t*)fp;
	if(fp == stdin) {
		DP(o)->apis = IN__stdin;
		KNH_SETv(ctx, DP(o)->urn, TS_DEVSTDIN);
	}
	else {
		DP(o)->apis = IN__FILE;
	}
	return o;
}

/* ======================================================================== */
/* [Bytes] */

static
int knh_InputStream_getc__Bytes(Ctx *ctx, knh_inptr_t *ptr)
{
	InputStream *b = (InputStream*)ptr;
	if(IS_NULL(DP(b)->ba) || !(DP(b)->bapos < DP(b)->baend)) return EOF;
	knh_uchar_t *p = (knh_uchar_t*)knh_Bytes_tochar(DP(b)->ba);
	int ch = p[DP(b)->bapos];
	DP(b)->bapos++;
	return ch;
}

/* ------------------------------------------------------------------------ */

static
size_t knh_InputStream_read__Bytes(Ctx *ctx, knh_inptr_t *ptr, char *buf, size_t bufsiz)
{
	InputStream *b = (InputStream*)ptr;
	if(IS_NULL(DP(b)->ba) || !(DP(b)->bapos < DP(b)->baend)) return 0;
	char *p = knh_Bytes_tochar(DP(b)->ba);
	size_t psize = DP(b)->baend - DP(b)->bapos;
	if (bufsiz < psize) psize = bufsiz;
	knh_memcpy(buf, p, psize);
	DP(b)->bapos += psize;
	return psize;
}

/* ------------------------------------------------------------------------ */

static
void knh_InputStream_close__Bytes(Ctx *ctx, knh_inptr_t *ptr)
{
	InputStream *b = (InputStream*)ptr;
	KNH_SETv(ctx, DP(b)->ba, KNH_NULL);
	DP(b)->bapos = 0;
	DP(b)->baend = 0;
}

/* ------------------------------------------------------------------------ */

InputStream *new_InputStream__Bytes(Ctx *ctx, Bytes *ba, size_t s, size_t e)
{
	InputStream* o =
		(InputStream*)new_Object_malloc(ctx, FLAG_InputStream, CLASS_InputStream, sizeof(knh_InputStream_struct));
	knh_InputStream_struct_init(ctx, DP(o), 0, NULL);
	DP(o)->inptr = (knh_inptr_t*)o;
	KNH_SETv(ctx, DP(o)->ba, ba);
	KNH_ASSERT(e <= knh_Bytes_size(ba));
	KNH_ASSERT(s <= e);
	DP(o)->bapos   = s;
	DP(o)->baend   = e;
	DP(o)->apis = IN__Bytes;
	return o;
}

/* ======================================================================== */
/* [mappings] */


/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
