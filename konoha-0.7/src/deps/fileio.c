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

#ifdef KONOHA_ON_LKM
#undef KNH_USING_POSIX
#endif

#ifdef KONOHA_ON_TB
#define KNH_USING_POSIX
#endif

#define KNH_USING_NOAPI 1

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [FILE] */

KNHAPI(FILE*) knh_fopen(Ctx *ctx, char *filename, char *mode, int isThrowable)
{
#if defined(KNH_USING_NOFILE)
	return NULL;
#elif defined(KNH_USING_STDC) || defined(KNH_USING_POSIX)
	FILE *fp = fopen(filename, mode);
	if(fp == NULL) {
		KNH_PERRNO(ctx, NULL, "IO!!", "fopen", isThrowable);
	}
	return fp;
#else
	KNH_NOAPI(ctx, NULL, isThrowable);
	return NULL;
#endif
}

/* ------------------------------------------------------------------------ */

KNHAPI(int) knh_fgetc(Ctx *ctx, FILE *fp)
{
#if defined(KNH_USING_NOFILE)
	return -1;
#elif defined(KNH_USING_STDC) || defined(KNH_USING_POSIX)
	return fgetc(fp);
#else
	return -1;
#endif
}

/* ------------------------------------------------------------------------ */

KNHAPI(size_t) knh_fread(Ctx *ctx, void *ptr, size_t size, FILE *fp)
{
#if defined(KNH_USING_NOFILE)
	return 0;
#elif defined(KNH_USING_STDC) || defined(KNH_USING_POSIX)
	return fread(ptr, 1, size, fp);
#else
	return 0;
#endif
}

/* ------------------------------------------------------------------------ */

KNHAPI(size_t) knh_fwrite(Ctx *ctx, void *ptr, size_t size, FILE *fp)
{
#if defined(KNH_USING_NOFILE)
	return 0;
#elif defined(KNH_USING_STDC) || defined(KNH_USING_POSIX)
	return fwrite(ptr, 1, size, fp);
#else
	return 0;
#endif
}

/* ------------------------------------------------------------------------ */

KNHAPI(int) knh_fflush(Ctx *ctx, FILE *fp)
{
#if defined(KNH_USING_NOFILE)
	return 0;
#elif defined(KNH_USING_STDC) || defined(KNH_USING_POSIX)
	return fflush(fp);
#else
	return 0;
#endif
}

/* ------------------------------------------------------------------------ */

KNHAPI(int) knh_fclose(Ctx *ctx, FILE *fp)
{
#if defined(KNH_USING_NOFILE)
	return 1;
#elif defined(KNH_USING_STDC) || defined(KNH_USING_POSIX)
	return fclose(fp);
#else
	return 1;
#endif
}

/* ======================================================================== */
/* [NOP] */

static
knh_io_t knh_iodrv_open__NOP(Ctx *ctx, knh_bytes_t n, char *mode, int isThrowable)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

static
void knh_iodrv_init__NOP(Ctx *ctx, Object *stream, char *mode)
{
}

/* ------------------------------------------------------------------------ */

static knh_intptr_t knh_iodrv_read__NOP(Ctx *ctx, knh_io_t fd, char *buf, size_t bufsiz)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

static knh_intptr_t knh_iodrv_write__NOP(Ctx *ctx, knh_io_t fd, char *buf, size_t bufsiz)
{
	return bufsiz;
}

/* ------------------------------------------------------------------------ */

static void knh_iodrv_close__NOP(Ctx *ctx, knh_io_t fd)
{

}

/* ======================================================================== */
/* [FILE] */

static knh_io_t knh_iodrv_open__FILE(Ctx *ctx, knh_bytes_t file, char *mode, int isThrowable)
{
	FILE *fp;
	fp = knh_fopen(ctx, (char*)file.buf, mode, isThrowable);
	if(fp == NULL) {
		return (knh_io_t)-1;
	}
	TODO();
	return (knh_io_t)fp;
}

/* ------------------------------------------------------------------------ */

static
knh_intptr_t knh_iodrv_read__FILE(Ctx *ctx, knh_io_t fd, char *buf, size_t bufsiz)
{
	return knh_fread(ctx, buf, bufsiz, (FILE*)fd);
}

/* ------------------------------------------------------------------------ */

static
knh_intptr_t knh_iodrv_write__FILE(Ctx *ctx, knh_io_t fd, char *buf, size_t bufsiz)
{
	size_t ssize = knh_fwrite(ctx, buf, bufsiz, (FILE*)fd);
	knh_fflush(ctx, (FILE*)fd);
	return ssize;
}

/* ------------------------------------------------------------------------ */

static
void knh_iodrv_close__FILE(Ctx *ctx, knh_io_t fd)
{
	knh_fclose(ctx, (FILE*)fd);
}

/* ======================================================================== */
/* @data */

static knh_iodrv_t IO__NOP = {
	KNH_DRVAPI_TYPE__IO, "NOP",
	0,
	knh_iodrv_open__NOP,
	knh_iodrv_init__NOP,
	knh_iodrv_read__NOP,
	knh_iodrv_write__NOP,
	knh_iodrv_close__NOP
};

static knh_iodrv_t IO__FILE = {
	KNH_DRVAPI_TYPE__IO, "file",
	0,
	knh_iodrv_open__FILE,
	knh_iodrv_init__NOP,
	knh_iodrv_read__FILE,
	knh_iodrv_write__FILE,
	knh_iodrv_close__FILE
};

/* ======================================================================== */
/* [drivers] */

knh_iodrv_t *knh_getIODriver(Ctx *ctx, knh_bytes_t name)
{
	knh_iodrv_t *p = (knh_iodrv_t*)knh_getDriverAPI(ctx, KNH_DRVAPI_TYPE__IO, name);
	if(p == NULL) {
		KNH_WARNING(ctx, "IO!!: unsupported scheme '%s'", name);
		p = &IO__NOP;
	}
	return p;
}

/* ------------------------------------------------------------------------ */

knh_iodrv_t *knh_getDefaultIODriver(void)
{
	return &IO__NOP;
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_addIODriver(Ctx *ctx, char *alias, knh_iodrv_t *d)
{
	knh_addDriverAPI(ctx, alias, (knh_drvapi_t*)d);
}

/* ======================================================================== */
/* [init] */

void KNHINIT init_IO(Ctx *ctx)
{
	knh_addIODriver(ctx, NULL, &IO__NOP);
	knh_addIODriver(ctx, NULL, &IO__FILE);
}

/* ======================================================================== */
/* [init] */
/* @data */

static knh_iodrv_t IO__stdio = {
	KNH_DRVAPI_TYPE__IO, "stdio",
	0,
	knh_iodrv_open__NOP,
	knh_iodrv_init__NOP,
	knh_iodrv_read__FILE,
	knh_iodrv_write__FILE,
	knh_iodrv_close__NOP
};

/* ------------------------------------------------------------------------ */

InputStream *new_InputStream__stdio(Ctx *ctx, FILE *fp, String *enc)
{
	InputStream* o = new_InputStream__FILE(ctx, TS_DEVSTDIN, stdin, &IO__stdio);
	knh_InputStream_setEncoding(ctx, o, enc);
	return o;
}

/* ------------------------------------------------------------------------ */

OutputStream *new_OutputStream__stdio(Ctx *ctx, FILE *fp, String *enc)
{
#ifdef KNH_USING_NOFILE
	OutputStream* o = new_OutputStream__FILE(ctx, TS_DEVSTDOUT, NULL, &IO__stdio);
#else
	OutputStream* o = NULL;
	KNH_ASSERT(fp == stdout || fp == stderr);
	if(fp == stdout) {
		o = new_OutputStream__FILE(ctx, TS_DEVSTDOUT, stdout, &IO__stdio);
	}
	else {
		o = new_OutputStream__FILE(ctx, TS_DEVSTDERR, stderr, &IO__stdio);
	}
#endif
	knh_OutputStream_setAutoFlush(o, 1);
	knh_OutputStream_setEncoding(ctx, o, enc);
	return o;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
