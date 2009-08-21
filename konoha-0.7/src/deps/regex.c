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

#if defined(KNH_USING_ONIGURUMA)
#define KNH_USING_REGEX
	#ifdef KONOHA_ON_WINDOWS
	#include "onigposix.h"  // this path was written by nakata. why?
	#else
	#include<onigposix.h>
	#endif
#elif defined(KNH_USING_REGEX)
#include<regex.h>
#endif

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* [NOP] */

static
knh_regex_t* knh_regex_malloc__NOP(Ctx *ctx)
{
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
int knh_regex_regcomp__NOP(Ctx *ctx, knh_regex_t *reg, char *pattern, char *option)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

static
int knh_regex_regexec__NOP(Ctx *ctx, knh_regex_t *reg, char *str, size_t nmatch, knh_regmatch_t p[], int flags)
{
	size_t i;
	for(i = 0; i < KNH_REGEX_NMATCH_SIZE; i++) {
		p[i].rm_so = -1;
		p[i].rm_eo = -1;
		p[i].rm_name.buf = NULL;
		p[i].rm_name.len = 0;
	}
	return 1 /* mismatched */;
}

/* ------------------------------------------------------------------------ */

static
void knh_regex_regfree__NOP(Ctx *ctx, knh_regex_t *reg)
{
	KNH_ASSERT(reg == NULL);
}

/* ======================================================================== */

void knh_write_USING_REGEX(Ctx *ctx, OutputStream *w)
{
#ifdef KNH_USING_REGEX
	knh_write_char(ctx, w, " regex");
#endif
}

/* ------------------------------------------------------------------------ */

#ifdef KNH_USING_REGEX

static
knh_regex_t* knh_regex_malloc(Ctx *ctx)
{
	return (regex_t*)KNH_MALLOC(ctx, sizeof(regex_t));
}

/* ------------------------------------------------------------------------ */

static
int knh_regex_regcomp(Ctx *ctx, knh_regex_t *reg, char *pattern, char *option)
{
	int flag = REG_EXTENDED;
	if(knh_bytes_index(B(option), 'i') >= 0) {
		flag |= REG_ICASE;
	}
	int res = regcomp((regex_t*)reg, pattern, flag);
	if(res != 0) {
		char buf[FILEPATH_BUFSIZ * 4];
		regerror(res, (regex_t*)reg, buf, sizeof(buf));
		KNH_WARNING(ctx, "regex(error): %s", buf);
	}
	return res;
}

/* ------------------------------------------------------------------------ */

static
int knh_regex_regexec(Ctx *ctx, knh_regex_t *reg, char *str, size_t nmatch, knh_regmatch_t p[], int flags)
{
	regmatch_t pmatch[KNH_REGEX_NMATCH_SIZE];
	int res = regexec((regex_t*)reg, str, KNH_REGEX_NMATCH_SIZE, pmatch, 0);
	if(res == 0) {
		size_t i;
		for(i = 0; i < KNH_REGEX_NMATCH_SIZE; i++) {
			p[i].rm_so = pmatch[i].rm_so;
			p[i].rm_eo = pmatch[i].rm_eo;
			p[i].rm_name.buf = NULL;
			p[i].rm_name.len = 0;
		}
	}
	return res;
}

/* ------------------------------------------------------------------------ */

static
void knh_regex_regfree(Ctx *ctx, knh_regex_t *reg)
{
	regfree((regex_t*)reg);
	KNH_FREE(ctx, reg, sizeof(regex_t));
}

/* ------------------------------------------------------------------------ */

#endif

/* ======================================================================== */
/* @data */

static knh_regex_drvapi_t RE__NOP = {
	KNH_DRVAPI_TYPE__REGEX,
	"NOP",
	knh_regex_malloc__NOP,
	knh_regex_regcomp__NOP,
	knh_regex_regexec__NOP,
	knh_regex_regfree__NOP
};

#ifdef KNH_USING_REGEX

static knh_regex_drvapi_t RE__regex = {
	KNH_DRVAPI_TYPE__REGEX,
	"regex",
	knh_regex_malloc,
	knh_regex_regcomp,
	knh_regex_regexec,
	knh_regex_regfree
};

#endif

/* ======================================================================== */
/* [string parser] */

static
Regex *new_Regex(Ctx *ctx, String *pattern, String *option)
{
	knh_Regex_t *o = (knh_Regex_t*)new_hObject(ctx, FLAG_Regex, CLASS_Regex, CLASS_Regex);
	knh_bytes_t p = knh_String_tobytes(pattern);
	knh_index_t loc = knh_bytes_index(p, ':');
	KNH_INITv(o->pattern, pattern);
	if(loc == -1) {
		o->df = knh_System_getRegexDriver(ctx, STEXT("re"));
	}
	else {
		o->df = knh_System_getRegexDriver(ctx, knh_bytes_first(p, loc));
	}
	o->reg = o->df->regmalloc(ctx);
	{
		char *ptn = (char*)(knh_bytes_last(p, loc+1).buf);
		char *opt = IS_NULL(option) ? "" : knh_String_tochar(option);
		o->df->regcomp(ctx, o->reg, ptn, opt);
	}
	return o;
}

/* ------------------------------------------------------------------------ */

static
Object* new_Regex_parseOf(Ctx *ctx, String *pattern)
{
	return (Object*)new_Regex(ctx, pattern, (String*)KNH_NULL);
}

static knh_parser_drvapi_t PARSER__Regex = {
	KNH_DRVAPI_TYPE__PARSER,
	"regex", NNTYPE_Regex, new_Regex_parseOf
};

/* ======================================================================== */
/* [drivers] */

knh_regex_drvapi_t *knh_System_getRegexDriver(Ctx *ctx, knh_bytes_t name)
{
	knh_regex_drvapi_t *p = (knh_regex_drvapi_t *)knh_getDriverAPI(ctx, KNH_DRVAPI_TYPE__REGEX, name);
	if(p == NULL) {
		KNH_WARNING(ctx, "Regex: unsupported scheme '%s'", name);
		p = &RE__NOP;
	}
	return p;
}

/* ------------------------------------------------------------------------ */

KNHAPI(void) knh_addRegexDriver(Ctx *ctx, char *alias, knh_regex_drvapi_t *d)
{
	if(alias != NULL) {
		knh_addParserDriver(ctx, alias, &PARSER__Regex);
	}
	else {
		knh_addParserDriver(ctx, d->name, &PARSER__Regex);
	}
	knh_addDriverAPI(ctx, alias, (knh_drvapi_t*)d);
}

/* ======================================================================== */
/* [init] */

void KNHINIT init_Regex(Ctx *ctx)
{
	knh_addRegexDriver(ctx, NULL, &RE__NOP);
#ifdef KNH_USING_REGEX
	knh_addRegexDriver(ctx, NULL, &RE__regex);
	knh_addRegexDriver(ctx, "re", &RE__regex);
#if defined(KNH_USING_ONIGURUMA)
	knh_setSystemPropertyText(ctx, "konoha.regex", "oniguruma");
#else
	knh_setSystemPropertyText(ctx, "konoha.regex", "POSIX.2");
#endif
#endif
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
