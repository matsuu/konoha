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

void knh_putc(Ctx *ctx, Writer *w, int ch)
{
	if(IS_Bytes(w)) {
		knh_Bytes_putc(ctx, (Bytes*)w, ch);
	}else if(IS_OutputStream(w)) {
		knh_OutputStream_putc(ctx, (OutputStream*)w, ch);
	}
}

/* ------------------------------------------------------------------------ */

void knh_write(Ctx *ctx, Writer *w, knh_bytes_t s)
{
	if(IS_Bytes(w)) {
		knh_Bytes_write(ctx, (Bytes*)w, s);
	}else if(IS_OutputStream(w)) {
		knh_OutputStream_write(ctx, (OutputStream*)w, s);
	}
}

/* ------------------------------------------------------------------------ */

void knh_flush(Ctx *ctx, Writer *w)
{
	if(IS_OutputStream(w)) {
		knh_OutputStream_flush(ctx, (OutputStream*)w);
	}
}

/* ------------------------------------------------------------------------ */

void knh_print(Ctx *ctx, Writer *w, knh_bytes_t s)
{
	if(IS_Bytes(w)) {
		knh_Bytes_write(ctx, (Bytes*)w, s);
	}else if(IS_OutputStream(w)) {
		knh_OutputStream_print_(ctx, (OutputStream*)w, s, 0);
	}
}

/* ------------------------------------------------------------------------ */

void knh_println(Ctx *ctx, Writer *w, knh_bytes_t s)
{
	if(IS_Bytes(w)) {
		knh_Bytes_write(ctx, (Bytes*)w, s);
		knh_Bytes_write(ctx, (Bytes*)w, STEXT(KONOHA_OS_LINEFEED));
	}else if(IS_OutputStream(w)) {
		knh_OutputStream_print_(ctx, (OutputStream*)w, s, 1);
	}
}

/* ======================================================================== */

void knh_write_newline(Ctx *ctx, Writer *w)
{
	if(IS_Bytes(w)) {
		knh_Bytes_write(ctx, (Bytes*)w, STEXT(KONOHA_OS_LINEFEED));
	}else if(IS_OutputStream(w)) {
		knh_OutputStream_write(ctx, (OutputStream*)w, knh_String_tobytes(((OutputStream*)w)->NEWLINE));
	}
}

/* ------------------------------------------------------------------------ */

void knh_write_tab(Ctx *ctx, Writer *w)
{
	if(IS_Bytes(w)) {
		knh_Bytes_write(ctx, (Bytes*)w, STEXT("\t"));
	}else if(IS_OutputStream(w)) {
		knh_OutputStream_write(ctx, (OutputStream*)w, knh_String_tobytes(((OutputStream*)w)->TAB));
	}
}

#define _knh_write_delim(ctx, w)    knh_write(ctx, w, STEXT(", "))
#define _knh_write_dots(ctx, w)     knh_write(ctx, w, STEXT("..."))

/* ------------------------------------------------------------------------ */

void knh_write_indent(Ctx *ctx, Writer *w)
{
	knh_int_t i, n = 0;
	if(IS_Bytes(w)) {
		n = 0;
	}else if(IS_OutputStream(w)) {
		n = ((OutputStream*)w)->indent;
	}
	for(i = 0; i < n; i++) knh_write_tab(ctx, w);
}

/* ======================================================================== */
/* [datatype] */

void knh_write__s(Ctx *ctx, Writer *w, char *s)
{
	knh_write(ctx, w, B(s));
}

/* ------------------------------------------------------------------------ */

void knh_write__p(Ctx *ctx, Writer *w, void *ptr)
{
	char buf[KNH_INT_FMTSIZ];
	knh_snprintf(buf, sizeof(buf), "%p", ptr);
	knh_write(ctx, w, B(buf));
}

/* ------------------------------------------------------------------------ */

void knh_write__ifmt(Ctx *ctx, Writer *w, char *fmt, knh_int_t n)
{
	char buf[KNH_INT_FMTSIZ];
	knh_snprintf(buf, sizeof(buf), fmt, n);
	knh_write(ctx, w, B(buf));
}

#define _knh_write__i(ctx, w, n)   knh_write__ifmt(ctx, w, KNH_INT_FMT, n)
#define _knh_write__u(ctx, w, n)   knh_write__ifmt(ctx, w, KNH_UINT_FMT, n)
#define _knh_write__x(ctx, w, n)   knh_write__ifmt(ctx, w, KNH_INT_FMTX, n)

/* ------------------------------------------------------------------------ */

void knh_write__ffmt(Ctx *ctx, Writer *w, char *fmt, knh_float_t n)
{
	char buf[KNH_FLOAT_FMTSIZ];
	knh_snprintf(buf, sizeof(buf), fmt, n);
	knh_write(ctx, w, B(buf));
}

#define _knh_write__f(ctx, w, f)  knh_write__ffmt(ctx, w, KNH_FLOAT_FMT, f)
#define _knh_write__e(ctx, w, f)  knh_write__ffmt(ctx, w, KNH_FLOAT_FMTE, f)

/* ------------------------------------------------------------------------ */
/* [flag] */

void knh_write__flag(Ctx *ctx, Writer *w, knh_flag_t flag)
{
	knh_int_t i;
	knh_flag_t f = KNH_FLAG15;
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

void knh_write__type(Ctx *ctx, Writer *w, knh_type_t type)
{
	knh_write(ctx, w, B(TYPEN(type)));
	knh_write(ctx, w, B(TYPEQ(type)));	
}

/* ------------------------------------------------------------------------ */

void knh_write__class(Ctx *ctx, Writer *w, knh_class_t cid)
{
	knh_write(ctx, w, B(TYPEN(cid)));
	if(TYPE_ISPLURAL(cid)) {
		knh_write(ctx, w, STEXT(".."));	
	}
}

#define _knh_write__expt(ctx, w, eid)    knh_write__s(ctx, w, EXPTN(eid))

/* ------------------------------------------------------------------------ */

void knh_write__mn(Ctx *ctx, Writer *w, knh_methodn_t mn)
{
	char buf[CLASSNAME_BUFSIZ];
	knh_format_methodn(buf, sizeof(buf), mn);
	knh_write__s(ctx, w, buf);
}

#define _knh_write__fn(ctx, w, fn)   knh_write__s(ctx, w, FIELDN(fn))

/* ======================================================================== */
/* [String] */

INLINE
void knh_format(Ctx *ctx, OutputStream *b, knh_methodn_t mn, Object *o, Any *m)
{
	Method *mtd = knh_Method_ufind(ctx, knh_Object_cid(o), mn);
	if(IS_NULL(mtd)) return ;
	/* ebp[-4] */
	KNH_PUSHv(ctx, mtd);    /* ebp[-3] */
	KNH_PUSHv(ctx, o);      /* ebp[-2] */
	KNH_PUSHv(ctx, b);      /* ebp[-1] */
	KNH_PUSHv(ctx, m);      /* ebp[0]  */
	KNH_SCALL(ctx, 3);
	VM_SHIFT(ctx, -1);
}

#define _knh_write__O(ctx, w, o)    knh_format(ctx, w, METHODN__s, o, KNH_NULL)

/* ------------------------------------------------------------------------ */

String* 
knh_Object_movableText(Ctx *ctx, Object *b, knh_methodn_t mn, Any *m)
{
        knh_buffer_t cb = knh_Context_buffer(ctx);
        knh_format(ctx, cb.w, mn, b, m);
        return new_String__buffer(ctx, CLASS_String, cb);
}

#define _knh_Object_toString(ctx, b)   knh_Object_movableText(ctx, b, METHODN__s, KNH_NULL)

/* ======================================================================== */
/* [option] */


/* ======================================================================== */
/* [printf] */

void knh_printf(Ctx *ctx, Writer *w, char *fmt, ...) 
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
				case 't': knh_write_tab(ctx, w); break;
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
					knh_write__i(ctx, w, (knh_int_t)va_arg(args, knh_int_t)); 
					break;
					
				case 'u': 
					knh_write__u(ctx, w, (knh_uint_t)va_arg(args, knh_uint_t)); 
					break;

				case 'x':
					knh_write__x(ctx, w, (knh_uint_t)va_arg(args, knh_uint_t)); 
					break;

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
					knh_write__mn(ctx, w, (knh_methodn_t)va_arg(args, int)); 
					break;

				case 'C': 
					knh_write__class(ctx, w, (knh_class_t)va_arg(args, int)); 
					break;

				case 'T': 
					knh_write__type(ctx, w, (knh_methodn_t)va_arg(args, int)); 
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

/* ------------------------------------------------------------------------ */

typedef void (*f_mt)(Ctx *, Object *, OutputStream *, Any *);

/* ------------------------------------------------------------------------ */

METHOD knh_fmethod_movableText(Ctx *ctx, Object **sfp)
{
	f_mt f = (f_mt)((Method*)sfp[-1])->code;
	if(IS_NULL(sfp[1])) {
		f(ctx, sfp[0], new_OutputStream__NULL(ctx), sfp[2]);
	}
	else{
		f(ctx, sfp[0], sfp[1], sfp[2]);
	}
	METHOD_RETURN(ctx, sfp, KNH_VOID);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
