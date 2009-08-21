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

#include"commons.h"

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif


/* ======================================================================== */
/* [method] */

KNHAPI(void) knh_putc(Ctx *ctx, OutputStream *w, int ch)
{
	DBG2_ASSERT(IS_OutputStream(w));
	knh_OutputStream_putc(ctx, w, ch);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_write(Ctx *ctx, OutputStream *w, knh_bytes_t s)
{
	DBG2_ASSERT(IS_OutputStream(w));
	knh_OutputStream_write(ctx, w, s);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_flush(Ctx *ctx, OutputStream *w)
{
	DBG2_ASSERT(IS_OutputStream(w));
	knh_OutputStream_flush(ctx, w);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_print(Ctx *ctx, OutputStream *w, knh_bytes_t s)
{
	DBG2_ASSERT(IS_OutputStream(w));
	knh_OutputStream_print_(ctx, w, s, 0);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_println(Ctx *ctx, OutputStream *w, knh_bytes_t s)
{
	DBG2_ASSERT(IS_OutputStream(w));
	knh_OutputStream_print_(ctx, w, s, 1);
}

/* ======================================================================== */

KNHAPI(void) knh_write_EOL(Ctx *ctx, OutputStream *w)
{
	DBG2_ASSERT(IS_OutputStream(w));
	knh_OutputStream_write(ctx, w, knh_String_tobytes(DP(w)->NEWLINE));
	if(knh_OutputStream_isAutoFlush(w)) {
		knh_OutputStream_flush(ctx, w);
	}
	knh_OutputStream_setBOL(w, 1);
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_write_TAB(Ctx *ctx, OutputStream *w)
{
	DBG2_ASSERT(IS_OutputStream(w));
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

void knh_write_char(Ctx *ctx, OutputStream *w, char *s)
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

void knh_write_dfmt(Ctx *ctx, OutputStream *w, char *fmt, knh_intptr_t n)
{
	char buf[KNH_INT_FMTSIZ];
	knh_snprintf(buf, sizeof(buf), fmt, n);
	knh_write(ctx, w, B(buf));
}

/* ------------------------------------------------------------------------ */

void knh_write_ifmt(Ctx *ctx, OutputStream *w, char *fmt, knh_int_t n)
{
	char buf[KNH_INT_FMTSIZ];
	knh_snprintf(buf, sizeof(buf), fmt, n);
	knh_write(ctx, w, B(buf));
}

//#define _knh_write__i(ctx, w, n)   knh_write_dfmt(ctx, w, KNH_INTPTR_FMT, n)
//#define _knh_write__u(ctx, w, n)   knh_write_dfmt(ctx, w, KNH_UINT_FMT, n)
//#define _knh_write__x(ctx, w, n)   knh_write_dfmt(ctx, w, KNH_INTPTR_FMTX, n)

/* ------------------------------------------------------------------------ */

void knh_write_ffmt(Ctx *ctx, OutputStream *w, char *fmt, knh_float_t n)
{
	char buf[KNH_FLOAT_FMTSIZ];
	knh_snprintf(buf, sizeof(buf), fmt, n);
	knh_write(ctx, w, B(buf));
}

//#define _knh_write__f(ctx, w, f)  knh_write_ffmt(ctx, w, KNH_FLOAT_FMT, f)
//#define _knh_write__e(ctx, w, f)  knh_write_ffmt(ctx, w, KNH_FLOAT_FMTE, f)

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

#define _knh_write_fn(ctx, w, fn)   knh_write(ctx, w, B(FIELDN(fn)))

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
	knh_write_char(ctx, w, name);
}

/* ------------------------------------------------------------------------ */

#define _knh_write_type(ctx, w, type)   knh_write_type_(ctx, w, type, 0)
#define _knh_write_ltype(ctx, w, type)  knh_write_type_(ctx, w, type, 1)

void knh_write_type_(Ctx *ctx, OutputStream *w, knh_type_t type, int isLongName)
{
	knh_class_t cid = CLASS_type(type);
	KNH_ASSERT_cid(cid);
	if(type == TYPE_void) {
		knh_write(ctx, w, STEXT("void"));
	}
	else if(type == TYPE_var) {
		knh_write(ctx, w, STEXT("var"));
	}
	else {
		char *cname = (isLongName) ? knh_ClassTable_CLASSN(ctx, cid) : CTXCLASSN(cid);
		if(IS_ubxtype(type)) {
			knh_putc(ctx, w, tolower(cname[0]));
			knh_write_char(ctx, w, cname + 1);
			return;
		}
		knh_write_char(ctx, w, cname);
		if(IS_NATYPE(type)) {
			knh_putc(ctx, w, '?');
		}
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
		knh_write_char(ctx, w, file);
		knh_putc(ctx, w, ':');
		knh_write_dfmt(ctx, w, KNH_INTPTR_FMT, line);
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

static char* knh_vprintf_parseindex(char *p, int *index)
{
    char *ptr = p+1;
	if(ptr[0] == '{' && isdigit(ptr[1]) && ptr[2] == '}') {
		*index = ptr[1] - '0';
		ptr += 3;
		return ptr;
	}
	return p;
}

/* ------------------------------------------------------------------------ */
/* @data */

#define VA_NOP                0
#define VA_DIGIT              1 /* intptr_t */
#define VA_LONG               2 /* knh_int_t */
#define VA_FLOAT              3
#define VA_CHAR               4
#define VA_POINTER            5
#define VA_OBJECT             6
#define VA_FIELDN             7
#define VA_CLASS              8
#define VA_TYPE               9
#define VA_METHODN            10
#define VA_BYTES              11

typedef struct {
	int atype;
	union {
		knh_intptr_t  dvalue;
		knh_uintptr_t uvalue;
		knh_int_t     ivalue;
		knh_float_t   fvalue;
		knh_float_t   evalue;
		void         *pvalue;
		char         *svalue;
		Object       *ovalue;
		knh_bytes_t   bvalue;
		knh_class_t     cid;
		knh_type_t      type;
		knh_fieldn_t    fn;
		knh_methodn_t   mn;
	};
} knh_valist_t;

/* ------------------------------------------------------------------------ */

void knh_vprintf(Ctx *ctx, OutputStream *w, char *fmt, va_list ap)
{
	knh_valist_t args[10];
	char *c = fmt;
	int i, ch, bindex = 0, bindex_max = 10;
	for(i = 0; i < bindex_max; i++) args[i].atype = 0;

	while((ch = *c) != '\0') {
		c++;
		if(ch == '%') {
			ch = *c;
			int index = bindex++;
			c = knh_vprintf_parseindex(c++, &index);
			//DBG2_P("bindex=%d, index=%d", bindex, index);
			switch(ch) {
				case 'd': case 'u':
					args[index].atype = VA_DIGIT;
					break;
				case 'l': case 'i':
					args[index].atype = VA_LONG;
					break;
				case 'f': case 'e':
					args[index].atype = VA_FLOAT;
					break;
				case 's':
					args[index].atype = VA_CHAR;
					break;
				case 'p':
					args[index].atype = VA_POINTER;
					break;
				case 'K': case 'k':
				case 'O': case 'o':
					args[index].atype = VA_OBJECT;
					break;
				case 'N': case 'F':
					args[index].atype = VA_FIELDN;
					break;
				case 'M':
					args[index].atype = VA_METHODN;
					break;
				case 'C':
					args[index].atype = VA_CLASS;
					break;
				case 'T':
					args[index].atype = VA_TYPE;
					break;
				case 'B':
					args[index].atype = VA_BYTES;
					break;
				default:
					bindex--;
			}
			if(bindex == 10) {
				DBG2_ASSERT(bindex < 10);
				break;
			}
		}
	}

	for(i = 0; i < 10; i++) {
		switch(args[i].atype) {
		case VA_DIGIT:
			args[i].dvalue = (knh_intptr_t)va_arg(ap, knh_intptr_t);
			break;
		case VA_LONG:
			args[i].ivalue = (knh_int_t)va_arg(ap, knh_int_t);
			break;
#if defined(KNH_USING_NOFLOAT)
		case VA_FLOAT:
			args[i].fvalue = (knh_float_t)va_arg(ap, knh_float_t);
			break;
#else
		case VA_FLOAT:
			args[i].fvalue = (knh_float_t)va_arg(ap, double);
			break;
#endif
		case VA_CHAR:
			args[i].svalue = (char*)va_arg(ap, char*);
			break;
		case VA_POINTER:
			args[i].pvalue = (void*)va_arg(ap, void*);
			break;
		case VA_OBJECT:
			args[i].ovalue = (Object*)va_arg(ap, Object*);
			break;
		case VA_FIELDN:
			args[i].fn = (knh_fieldn_t)va_arg(ap, int/*knh_fieldn_t*/);
			break;
		case VA_METHODN:
			args[i].mn = (knh_methodn_t)va_arg(ap, int/*knh_methodn_t*/);
			break;
		case VA_CLASS:
			args[i].cid = (knh_class_t)va_arg(ap, int/*knh_class_t*/);
			break;
		case VA_TYPE:
			args[i].type = (knh_type_t)va_arg(ap, int/*knh_type_t*/);
			break;
		case VA_BYTES:
			args[i].bvalue = (knh_bytes_t)va_arg(ap, knh_bytes_t);
			break;
		default:
			bindex_max = i;
			goto L_FORMAT;
		}
	}

	L_FORMAT: {
		knh_bytes_t b;
		c = fmt;
		bindex = 0;
		b.buf = (knh_uchar_t*)c;
		b.len = 0;
		while((ch = *c) != '\0') {
			c++;
			if(ch == '\\') {
				if(b.len > 0) {
					knh_print(ctx, w, b);
				}
				ch = *c;
				switch(ch) {
					case '\0' : return ;
					case 'n': knh_println(ctx, w, STEXT("")); break;
					case 't': knh_write_TAB(ctx, w); break;
					default:
						knh_putc(ctx, w, '\\');
						knh_putc(ctx, w, ch);
				}
				b.buf = (knh_uchar_t*)c;
				b.len = 0;
			}
			else if(ch == '%') {
				if(b.len > 0) {
				  knh_print(ctx, w, b);
				}
				ch = *c;
				int index = bindex++;
				c = knh_vprintf_parseindex(++c, &index);

				switch(ch) {
					case '\0' : return ;
					case 'd':
						KNH_ASSERT(args[index].atype == VA_DIGIT);
						knh_write_dfmt(ctx, w, KNH_INTPTR_FMT, args[index].dvalue);
						break;
					case 'u':
						KNH_ASSERT(args[index].atype == VA_DIGIT);
						knh_write_dfmt(ctx, w, KNH_INTPTR_UFMT, args[index].uvalue);
						break;
					case 'l': case 'i' :
						KNH_ASSERT(args[index].atype == VA_LONG);
						knh_write_ifmt(ctx, w, KNH_INT_FMT, args[index].ivalue);
						break;
					case 'f':
						KNH_ASSERT(args[index].atype == VA_FLOAT);
						knh_write_ffmt(ctx, w, KNH_FLOAT_FMT, args[index].fvalue);
						break;
					case 'e':
						KNH_ASSERT(args[index].atype == VA_FLOAT);
						knh_write_ffmt(ctx, w, KNH_FLOAT_FMTE, args[index].fvalue);
						break;
					case 's':
						KNH_ASSERT(args[index].atype == VA_CHAR);
						knh_write(ctx, w, B(args[index].svalue));
						break;
					case 'p':
						KNH_ASSERT(args[index].atype == VA_POINTER);
						knh_write__p(ctx, w, args[index].pvalue);
						break;
					case 'O': case 'o':
						KNH_ASSERT(args[index].atype == VA_OBJECT);
						knh_write__O(ctx, w, args[index].ovalue);
						break;
					case 'K': case 'k':
						KNH_ASSERT(args[index].atype == VA_OBJECT);
						knh_write__O(ctx, w, args[index].ovalue);
						break;
					case 'N': case 'F':
						KNH_ASSERT(args[index].atype == VA_FIELDN);
						knh_write_char(ctx, w, FIELDN(args[index].fn));
						break;
					case 'M':
						KNH_ASSERT(args[index].atype == VA_METHODN);
						knh_write_mn(ctx, w, args[index].mn);
						break;
					case 'C':
						KNH_ASSERT(args[index].atype == VA_CLASS);
						knh_write_cid(ctx, w, args[index].cid);
						break;
					case 'T':
						KNH_ASSERT(args[index].atype == VA_TYPE);
						knh_write_type(ctx, w, args[index].type);
						break;
					case 'B':
						KNH_ASSERT(args[index].atype == VA_BYTES);
						knh_write(ctx,w, args[index].bvalue);
						break;
					default:
						//knh_putc(ctx, w, '%');
						knh_putc(ctx, w, ch);
				}
				b.buf = (knh_uchar_t*)c;
				b.len = 0;
				if(!(bindex <= bindex_max)) {
					DBG2_ASSERT(bindex <= bindex_max);
					break;
				}
			}
			else {
				b.len = b.len+1;
			}
		}
		if(b.len > 0) {
		  knh_print(ctx, w, b);
		}
	}
}

/* ------------------------------------------------------------------------ */


KNHAPI(void) knh_printf(Ctx *ctx, OutputStream *w, char *fmt, ...)
{
	va_list ap;
	va_start(ap , fmt);
	knh_vprintf(ctx, w, fmt, ap);
	va_end(ap);
}

/* ======================================================================== */
/* [verbose] */

#ifdef KNH_DBGMODE
static int verbose = 1;
#else
static int verbose = 0;
#endif

/* ------------------------------------------------------------------------ */

void knh_setverbose(int v)
{
	verbose = v;
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_says(Ctx *ctx, int type, char *fmt, ...)
{
#ifndef KONOHA_ON_LKM
// TODO_LKM
// how to print this.
// printk? or something...

	if(type == KONOHA_NOTICE && (!knh_Context_isVerbose(ctx) || !knh_Context_isInteractive(ctx))) {
		return;
	}
	if(ctx->err == NULL) {
		int ch;
		char *c = fmt;
		FILE *fp = stderr;
		fprintf(fp, "[KONOHA] ");
		va_list args;
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
		va_end(args);
	}
	else {
		va_list args;
		OutputStream *w = KNH_STDERR;
		knh_write(ctx, w, STEXT("[konoha] "));
		va_start(args, fmt);
		knh_vprintf(ctx, w, fmt, args);
		va_end(args);
		knh_write_EOL(ctx, w);
	}
#endif
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

knh_bool_t knh_stack_isRecuriveFormatting(Ctx *ctx, knh_sfp_t *sfp, Object *o, OutputStream *w, void *mtdcode)
{
	knh_sfp_t *sp = sfp - 1;
	while(ctx->stack < sp) {
		if(sp[0].o == o && sp[1].w == w && IS_Method(sp[-1].mtd)) {
			if(DP(sp[-1].mtd)->code == mtdcode) return 1;
		}
		sp--;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
