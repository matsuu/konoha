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

#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif


/* ======================================================================== */
/* [method] */

KNHAPI(void) knh_putc(Ctx *ctx, OutputStream *w, int ch)
{
	KNH_ASSERT(IS_OutputStream(w));
	knh_OutputStream_putc(ctx, w, ch);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_write(Ctx *ctx, OutputStream *w, knh_bytes_t s)
{
	KNH_ASSERT(IS_OutputStream(w));
	knh_OutputStream_write(ctx, w, s);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_flush(Ctx *ctx, OutputStream *w)
{
	KNH_ASSERT(IS_OutputStream(w));
	knh_OutputStream_flush(ctx, w);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_print(Ctx *ctx, OutputStream *w, knh_bytes_t s)
{
	KNH_ASSERT(IS_OutputStream(w));
	knh_OutputStream_print_(ctx, w, s, 0);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_println(Ctx *ctx, OutputStream *w, knh_bytes_t s)
{
	KNH_ASSERT(IS_OutputStream(w));
	knh_OutputStream_print_(ctx, w, s, 1);
}

/* ======================================================================== */

KNHAPI(void) knh_write_EOL(Ctx *ctx, OutputStream *w)
{
	KNH_ASSERT(IS_OutputStream(w));
	knh_OutputStream_write(ctx, w, knh_String_tobytes(DP(w)->NEWLINE));
	if(knh_OutputStream_isAutoFlush(w)) {
		knh_OutputStream_flush(ctx, w);
	}
	knh_OutputStream_setBOL(w, 1);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_write_TAB(Ctx *ctx, OutputStream *w)
{
	KNH_ASSERT(IS_OutputStream(w));
	knh_OutputStream_write(ctx, w, knh_String_tobytes(DP(w)->TAB));
}

#define _knh_write_delim(ctx, w)    knh_write(ctx, w, STEXT(", "))
#define _knh_write_dots(ctx, w)     knh_write(ctx, w, STEXT("..."))

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_write_BOL(Ctx *ctx, OutputStream *w)
{
	knh_intptr_t i, n = DP(w)->indent;
	for(i = 0; i < n; i++) knh_write_TAB(ctx, w);
	knh_OutputStream_setBOL(w, 0);
}

/* ======================================================================== */
/* [datatype] */

void knh_write__s(Ctx *ctx, OutputStream *w, char *s)
{
	knh_write(ctx, w, B(s));
}

/* ------------------------------------------------------------------------ */

void knh_write__p(Ctx *ctx, OutputStream *w, void *ptr)
{
	char buf[KNH_INT_FMTSIZ];
	knh_snprintf(buf, sizeof(buf), "%p", ptr);
	knh_write(ctx, w, B(buf));
}

/* ------------------------------------------------------------------------ */

void knh_write__ifmt(Ctx *ctx, OutputStream *w, char *fmt, knh_intptr_t n)
{
	char buf[KNH_INT_FMTSIZ];
	knh_snprintf(buf, sizeof(buf), fmt, n);
	knh_write(ctx, w, B(buf));
}

#define _knh_write__i(ctx, w, n)   knh_write__ifmt(ctx, w, KNH_INTPTR_FMT, n)
#define _knh_write__u(ctx, w, n)   knh_write__ifmt(ctx, w, KNH_UINT_FMT, n)
#define _knh_write__x(ctx, w, n)   knh_write__ifmt(ctx, w, KNH_INTPTR_FMTX, n)

/* ------------------------------------------------------------------------ */

void knh_write__ffmt(Ctx *ctx, OutputStream *w, char *fmt, knh_float_t n)
{
	char buf[KNH_FLOAT_FMTSIZ];
	knh_snprintf(buf, sizeof(buf), fmt, n);
	knh_write(ctx, w, B(buf));
}

#define _knh_write__f(ctx, w, f)  knh_write__ffmt(ctx, w, KNH_FLOAT_FMT, f)
#define _knh_write__e(ctx, w, f)  knh_write__ffmt(ctx, w, KNH_FLOAT_FMTE, f)

/* ------------------------------------------------------------------------ */

void knh_write_integerfmt(Ctx *ctx, OutputStream *w, char *fmt, knh_int_t n)
{
	char buf[KNH_INT_FMTSIZ];
	knh_snprintf(buf, sizeof(buf), fmt, n);
	knh_write(ctx, w, B(buf));
}

/* ------------------------------------------------------------------------ */
/* [flag] */

void knh_write__flag(Ctx *ctx, OutputStream *w, knh_flag_t flag)
{
	knh_intptr_t i;
	knh_flag_t f = 1 << 15;
	for(i = 0; i < 16; i++) {
		if(i > 0 && i % 8 == 0) knh_putc(ctx, w, ' ');
		if((f & flag) == f) {
			knh_putc(ctx, w, '1');
		}else{
			knh_putc(ctx, w, '0');
		}
		f = f >> 1;
	}
}

/* ------------------------------------------------------------------------ */
/* language */
/* ------------------------------------------------------------------------ */

void knh_write_cid(Ctx *ctx, OutputStream *w, knh_class_t cid)
{
	knh_write(ctx, w, B(CTXCLASSN(cid)));
}

/* ------------------------------------------------------------------------ */

#define _knh_write_fn(ctx, w, fn)   knh_write__s(ctx, w, FIELDN(fn))

void knh_write_mn(Ctx *ctx, OutputStream *w, knh_methodn_t mn)
{
	char *name = FIELDN(METHODN_TOFIELDN(mn));
	if(METHODN_IS_MOVTEXT(mn)) {
		knh_putc(ctx, w, '%');
	}
	else if(METHODN_IS_GETTER(mn)) {
		knh_write(ctx, w, STEXT("get"));
		if(islower(name[0])) {
			knh_putc(ctx, w, toupper(name[0])); name++;
		}
	}
	else if(METHODN_IS_SETTER(mn)) {
		knh_write(ctx, w, STEXT("set"));
		if(islower(name[0])) {
			knh_putc(ctx, w, toupper(name[0])); name++;
		}
	}
	knh_write__s(ctx, w, name);
}

/* ------------------------------------------------------------------------ */

void knh_write_cidmn(Ctx *ctx, OutputStream *w, knh_class_t cid, knh_methodn_t mn)
{
	knh_write_cid(ctx, w, cid);
	knh_putc(ctx, w, '.');
	knh_write_mn(ctx, w, mn);
}

/* ------------------------------------------------------------------------ */

void knh_write_type(Ctx *ctx, OutputStream *w, knh_type_t type)
{
	if(type == TYPE_void) {
		knh_write(ctx, w, STEXT("void"));
		return;
	}

	knh_class_t cid = CLASS_type(type);
	KNH_ASSERT_cid(cid);
	char *cname = CTXCLASSN(cid);
	if(type == NNTYPE_Int || type == NNTYPE_Float || type == NNTYPE_Boolean) {
		knh_putc(ctx, w, tolower(cname[0]));
		knh_write__s(ctx, w, cname + 1);
		return;
	}
	knh_write__s(ctx, w, cname);
	if(IS_NNTYPE(type)) {
		knh_putc(ctx, w, '!');
	}
}


/* ------------------------------------------------------------------------ */

void knh_write_fline(Ctx *ctx, OutputStream *w, char *file, int line)
{
	if(line == 0) {
		knh_write(ctx, w, STEXT("(unknown:0)"));
	}
	else {
		knh_putc(ctx, w, '(');
		knh_write__s(ctx, w, file);
		knh_putc(ctx, w, ':');
		knh_write__i(ctx, w, line);
		knh_putc(ctx, w, ')');
	}
}

/* ======================================================================== */
/* [String] */

#define _knh_write__O(ctx, w, o)    knh_format(ctx, w, METHODN__k, o, KNH_NULL)

KNHAPI(void) knh_format(Ctx *ctx, OutputStream *w, knh_methodn_t mn, Object *o, Any *m)
{
	knh_sfp_t *esp = KNH_LOCAL(ctx);
	KNH_SETv(ctx, esp[1].o, o);
	esp[1].data = knh_Object_data(o);
	knh_esp1_format(ctx, mn, w, m);
}

/* ======================================================================== */
/* [printf] */

KNHAPI(void) knh_printf(Ctx *ctx, OutputStream *w, char *fmt, ...)
{
	va_list args;
	int ch; char *c = fmt;
	va_start(args , fmt);
	while((ch = *c) != '\0') {
		c++;
		switch(ch) {
		case '\\':
			ch = *c++;
			switch(ch) {
				case '\0' : return ;
				case 'n': knh_println(ctx, w, STEXT("")); break;
				case 't': knh_write_TAB(ctx, w); break;
				default:
					knh_putc(ctx, w, '\\');
					knh_putc(ctx, w, ch);
			}
			break;
		case '%':
			ch = *c++;
			switch(ch) {
				case '\0' : return ;
				case 'd':
					knh_write__i(ctx, w, (knh_intptr_t)va_arg(args, knh_intptr_t));
					break;

				case 'u':
					knh_write__u(ctx, w, (knh_uintptr_t)va_arg(args, knh_uintptr_t));
					break;

//				case 'x':
//					knh_write__x(ctx, w, (knh_uintptr_t)va_arg(args, knh_uintptr_t));
//					break;

				case 'f':
					knh_write__f(ctx, w, (knh_float_t)va_arg(args, double));
					break;

				case 'e':
					knh_write__e(ctx, w, (knh_float_t)va_arg(args, double));
					break;

				case 's':
					knh_write__s(ctx, w, (char*)va_arg(args, char*));
					break;

				case 'p':
					knh_write__p(ctx, w, (void*)va_arg(args, void*));
					break;

				case 'F':
					knh_write__flag(ctx, w, (knh_flag_t)va_arg(args, int));
					break;

				case 'N':
					knh_write__s(ctx, w, FIELDN((knh_fieldn_t)va_arg(args, int)));
					break;

				case 'M':
					knh_write_mn(ctx, w, (knh_methodn_t)va_arg(args, int));
					break;

				case 'C':
					knh_write_cid(ctx, w, (knh_class_t)va_arg(args, int));
					break;

				case 'T':
					knh_write_type(ctx, w, (knh_methodn_t)va_arg(args, int));
					break;

				case 'B':
					knh_write(ctx, w, (knh_bytes_t)va_arg(args, knh_bytes_t));
					break;

				case 'O':
					knh_write__O(ctx, w, (Object*)va_arg(args, Object*));
					break;

				default:
					knh_putc(ctx, w, '%');
					knh_putc(ctx, w, ch);
			}
			break;
		default:
			knh_putc(ctx, w, ch);
		}
	} /* while */
	va_end(args);
}

/* ======================================================================== */
/* [verbose] */

#ifdef KNH_DBGMODE
static int verbose = 1;
#else
static int verbose = 0;
#endif

/* ------------------------------------------------------------------------ */

void konoha_setverbose(int v)
{
	verbose = v;
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) konoha_says(Ctx *ctx, int type, char *fmt, ...)
{
	int ch;
	char *c = fmt;
	va_list args;
	if(type == KONOHA_NOTICE && !knh_Context_isVerbose(ctx)) {
		return;
	}
	if(ctx->err == NULL) {
		FILE *fp = stderr;
		fprintf(fp, "[KONOHA] ");
		va_start(args , fmt);
		while((ch = *c) != '\0') {
			c++;
			if(ch == '\\') {
				ch = *c++;
				switch(ch) {
				case '\0' : return ;
				case 'n': fprintf(fp, KONOHA_OS_LINEFEED); break;
				case 't': fputc('\t', fp); break;
				default:
					fputc('\\', fp);
					fputc(ch, fp);
				}
			}
			else if(ch == '%') {
				ch = *c++;
				switch(ch) {
				case '\0' : return ;
				case 'd':
					fprintf(fp, KNH_INT_FMT, (knh_int_t)va_arg(args, knh_int_t));
					break;

				case 'u':
					fprintf(fp, KNH_UINT_FMT, (knh_uint_t)va_arg(args, knh_uint_t));
					break;

				case 'f':
					fprintf(fp, "%f", (double)va_arg(args, double));
					break;

				case 's':
					fprintf(fp, "%s", (char*)va_arg(args, char*));
					break;

				case 'O':
					fprintf(fp, "OBJ(cid=%d)", (int)knh_Object_cid((Object*)va_arg(args, Object*)));
					break;

				case 'p':
					fprintf(fp, "%p", (void*)va_arg(args, void*));
						break;

				default:
					fputc('%', fp);
					fputc(ch, fp);
				}
			}
			else if(ch == 0) {
				return;
			}
			else {
				fputc(ch, fp);
			}
		} /* while */
		fprintf(fp, KONOHA_OS_LINEFEED);
	}
	else {
		OutputStream *w = KNH_STDERR;
		knh_write(ctx, w, STEXT("[konoha] "));
		va_start(args , fmt);
		while((ch = *c) != '\0') {
			c++;
			if(ch == '\\') {
				ch = *c++;
				switch(ch) {
				case '\0' : return ;
				case 'n':
					knh_write_EOL(ctx, w); break;
				case 't':
					knh_write_TAB(ctx, w); break;
				default:
					knh_putc(ctx, w, '\\');
					knh_putc(ctx, w, ch);
				}
			}
			else if(ch == '%') {
				ch = *c++;
				switch(ch) {
					case '\0' : return ;
					case 'd':
						knh_write__i(ctx, w, (knh_int_t)va_arg(args, knh_int_t));
						break;

					case 'u':
						knh_write__u(ctx, w, (knh_uint_t)va_arg(args, knh_uint_t));
						break;

					case 'f':
						knh_write__f(ctx, w, (knh_float_t)va_arg(args, double));
						break;

					case 's':
						knh_write__s(ctx, w, (char*)va_arg(args, char*));
						break;

					case 'p':
						knh_write__p(ctx, w, (void*)va_arg(args, void*));
						break;

					case 'O':
						knh_write__O(ctx, w, (Object*)va_arg(args, Object*));
						break;

					default:
						knh_putc(ctx, w, '%');
						knh_putc(ctx, w, ch);
				}
			}
			else if(ch == 0) {
				return;
			}
			else {
				knh_putc(ctx, w, ch);
			}
		} /* while */
		knh_write_EOL(ctx, w);
	}
	va_end(args);
}

/* ------------------------------------------------------------------------ */

typedef void (*f_mt)(Ctx *, Object *, OutputStream *, Any *);

/* ------------------------------------------------------------------------ */

METHOD knh_fmethod_movableText(Ctx *ctx, knh_sfp_t *sfp)
{
	f_mt f = (f_mt)DP(sfp[-1].mtd)->code;
	f(ctx, sfp[0].o, (OutputStream*)sfp[1].o, sfp[2].o);
	KNH_RETURN_void(ctx, sfp);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
