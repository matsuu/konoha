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
/* [constructors] */

Regex *new_Regex(Ctx *ctx, String *pattern)
{
	knh_Regex_t *o = (knh_Regex_t*)new_hObject(ctx, FLAG_Regex, CLASS_Regex, CLASS_Regex);
	knh_bytes_t p = knh_String_tobytes(pattern);
	knh_index_t loc = knh_bytes_index(p, ':');

	KNH_INITv(o->pattern, pattern);
	if(loc == -1) {
		o->df = knh_System_getRegexDriver(ctx, STEXT("re"));
		o->reg = o->df->regmalloc(ctx);
	}
	else {
		o->df = knh_System_getRegexDriver(ctx, knh_bytes_first(p, loc));
		o->reg = o->df->regmalloc(ctx);
		o->df->regcomp(ctx, o->reg, (char*)(knh_bytes_last(p, loc+1).buf), 0);
	}
	return o;
}

/* ------------------------------------------------------------------------ */

int knh_String_opMatch(Ctx *ctx, String *o, Regex *re)
{
	char *str = knh_String_tochar(o);
	knh_regmatch_t pmatch[KNH_REGEX_NMATCH_SIZE];
	int res = re->df->regexec(ctx, re->reg, str, KNH_REGEX_NMATCH_SIZE, pmatch, 0);
	//DBG_P("res=%d", res);
//	if(res == 0) {
//		int i;
//		for(i = 0; i < KNH_REGEX_NMATCH_SIZE; i++) {
//			if(pmatch[i].rm_so == -1) break;
//			//DBG_P("[%d], rm_so=%d, rm_eo=%d", i, pmatch[i].rm_so, pmatch[i].rm_eo);
//		}
//	}
	return (res == 0);
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! String.opMatch(Regex! re) */

METHOD knh__String_opMatch(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_String_opMatch(ctx, sfp[0].s, (Regex*)sfp[1].o));
}

/* ------------------------------------------------------------------------ */
/* @method Boolean! Regex.opMatch(String! s) */

METHOD knh__Regex_opMatch(Ctx *ctx, knh_sfp_t *sfp)
{
	KNH_RETURN_Boolean(ctx, sfp, knh_String_opMatch(ctx, sfp[1].s, (Regex*)sfp[0].o));
}

/* ------------------------------------------------------------------------ */

Array *knh_Regex_split(Ctx *ctx, Regex *o, String *s)
{
	char *str = knh_String_tochar(s);
	knh_regmatch_t pmatch[KNH_REGEX_NMATCH_SIZE];
	int res = o->df->regexec(ctx, o->reg, str, KNH_REGEX_NMATCH_SIZE, pmatch, 0);
	if(res == 0) {
		Array *a = new_Array(ctx, CLASS_String, KNH_REGEX_NMATCH_SIZE);
		knh_bytes_t sub = knh_String_tobytes(s);
		int i;
		for(i = 1; i < KNH_REGEX_NMATCH_SIZE; i++) {
			if(pmatch[i].rm_so == -1) break;
			//DBG_P("[%d], rm_so=%d, rm_eo=%d", i, pmatch[i].rm_so, pmatch[i].rm_eo);
			sub.buf = (knh_uchar_t*)str + pmatch[i].rm_so;
			sub.len = pmatch[i].rm_eo - pmatch[i].rm_so;
			knh_Array_add(ctx, a, UP(new_String(ctx, sub, s)));
		}
		return a;
	}
	else {
		return (Array*)konoha_getClassDefaultValue(ctx, ACLASS_String);
		//return (Array*)KNH_NULL;
	}
}

///* ------------------------------------------------------------------------ */
///* @MAPMAP String DictMap */
//
//Object *knh_Regex_mapmap(Ctx *ctx, Regex *o, Object *source, knh_class_t tcid)
//{
//
//}

/* ======================================================================== */
/* [movabletext] */

/* @method void Regex.%s(OutputStream w, String m) */


void knh_Regex__s(Ctx *ctx, Regex *o, OutputStream *w, String *m)
{
	knh_putc(ctx, w, '\'');
	knh_write(ctx, w, knh_String_tobytes(o->pattern));
	knh_putc(ctx, w, '\'');
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
