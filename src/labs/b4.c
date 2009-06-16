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


/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */

//static Object *fiboMethod = NULL;
//
///* ------------------------------------------------------------------------ */
///* @method Int! Script.initfibo() */
//
//METHOD knh__Script_initfibo(Ctx *ctx, knh_sfp_t *sfp)
//{
//	fiboMethod = (Object*)knh_Class_getMethod(ctx, CLASS_Script, METHODN_fibo);
//	KNH_ASSERT(IS_Method(fiboMethod));
//}
//
//
///* ------------------------------------------------------------------------ */
///* @method Int! Script.fibo(Int! n) */
//
//METHOD knh__Script_fibo(Ctx *ctx, knh_sfp_t *sfp)
//{
//	JIT_SETESP(ctx, 2);
//	JIT_iLTn(ctx, 2, 1, 3);
//	JIT_bJIFF(ctx, NPC, L_JUMP, 2);
//	JIT_RETo(ctx, -1, ctx->share->tInt[1  - KNH_TINT_MIN]);
//	L_JUMP:;
//	JIT_iSUBn(ctx, 5, 1, 1);
//	JIT_FCALL(ctx, 3, 3, 0, fiboMethod);
//	JIT_iSUBn(ctx, 6, 1, 2);
//	JIT_FCALL(ctx, 4, 3, 0, fiboMethod);
//	JIT_iADD(ctx, -1, 3, 4);
//	JIT_RET(ctx);
//}

/* ------------------------------------------------------------------------ */
/* @method void Script.changeChannel(Int! ch) */

METHOD knh__Script_changeChannel(Ctx *ctx, knh_sfp_t *sfp)
{
	fprintf(stdout, "switching channel to %d..\n", (int)sfp[1].ivalue);
	konoha_throwSecurityException();
}

/* ------------------------------------------------------------------------ */
/* @method void Script.hook(String! funcname) */

METHOD knh__Script_hook(Ctx *ctx, knh_sfp_t *sfp)
{
	char *funcname = knh_String_tochar(sfp[1].s);
	fprintf(stdout, "hooking security point at %s\n", funcname);
}

/* ------------------------------------------------------------------------ */
/* [pacage test] */

/* @data */

static char* MyRoom[] = {
	"cold", "confortable", "hot", NULL
//	"寒い", "ビミョー", "暑い", NULL
};

/* ------------------------------------------------------------------------ */

static
MAPPER knh_fmapper_myroom(Ctx *ctx, knh_sfp_t *sfp)
{
	ClassSpec *u = (ClassSpec*)DP(sfp[1].mpr)->mapdata;
	DBG2_P("t = %fC", sfp[0].fvalue);
	int n = 1;
	if(sfp[0].fvalue <= 12.0) n = 0;
	if(sfp[0].fvalue >= 25.0) n = 2;
	Array *a = (DP(u)->vocabDictIdx)->terms;
	Object *s = knh_Array_n(a, n);
	KNH_MAPPED(ctx, sfp, s);
}

static
ClassSpec *unit_Temperature(Ctx *ctx, knh_bytes_t urn)
{
	knh_bytes_t t = knh_bytes_rmod(urn, '/');
	if(ISB(t, "Celsius")) {
		return new_Unit(ctx, "C", urn, -273.15, KNH_FLOAT_MAX, 0.01);
	}
	else if(ISB(t, "Fahrenheit")) {
		ClassSpec *u = new_Unit(ctx, "F", urn, -459.67, KNH_FLOAT_MAX, 0.01);
		konoha_addAffineMapper(ctx, DP(u)->ucid, "Float{http://konoha/Temperature/Celsius}", 5.0/9.0, -32.0*5.0/9.0);
		return u;
	}
	else if(ISB(t, "Kelvin")) {
		ClassSpec *u = new_Unit(ctx, "K", urn, 0.0, KNH_FLOAT_MAX, 0.001);
		konoha_addAffineMapper(ctx, DP(u)->ucid, "Float{http://konoha/Temperature/Celsius}", 1.0, -273.15);
		return u;
	}
	else if(ISB(t, "MyRoom")) {
		ClassSpec *u = new_Vocab(ctx, "", urn, 0, MyRoom);
		knh_class_t scid = konoha_findcid(ctx, STEXT("Float{http://konoha/Temperature/Celsius}"));
		Mapper *mpr = new_Mapper(ctx,
				KNH_FLAG_MMF_TOTAL|KNH_FLAG_MMF_CONST|KNH_FLAG_MMF_FINAL, scid, DP(u)->ucid,
				knh_fmapper_myroom, (Object*)u);
		konoha_addMapper(ctx, mpr);
		return u;
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */
/* @data */

static char* MonthData[] = {
	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December",
	NULL
};

static char* WeekData[] = {
	"Monday", "Tuesday", "Wednesday", "Tursday", "Friday", "Saturday", "Sunday",
	NULL
};

static
ClassSpec *unit_Date(Ctx *ctx, knh_bytes_t urn)
{
	knh_bytes_t t = knh_bytes_rmod(urn, '/');
	if(ISB(t, "Month")) {
		return new_Vocab(ctx, "", urn, 1, MonthData);
	}
	else if(ISB(t, "Week")) {
		return new_Vocab(ctx, "", urn, 1, WeekData);
	}
	return NULL;
}

///* ------------------------------------------------------------------------ */
//
//static
//ClassSpec *makespec_ItalianCity__en(Ctx *ctx, knh_class_t bcid, char *extra)
//{
//	if(bcid == CLASS_String) {
//		return new_Vocabulary(ctx, "en", "Rome", "Milan", "Rome", NULL);
//	}
//	return (ClassSpec*)KNH_NULL;
//}
//
///* ------------------------------------------------------------------------ */
//
//static
//ClassSpec *makespec_ItalianCity__ja(Ctx *ctx, knh_class_t bcid, char *extra)
//{
//	if(bcid == CLASS_String) {
//		ClassSpec *cs = new_Vocabulary(ctx, "ja", "ローマ", "ミラノ", "ローマ", NULL);
//		konoha_addVocabularyMapper(ctx, DP(cs)->cid, "konoha.String{http://konoha/ItalianCity.en}");
//		return cs;
//	}
//	return (ClassSpec*)KNH_NULL;
//}
//
///* ------------------------------------------------------------------------ */
//
//static
//ClassSpec *makespec_ItalianCity__it(Ctx *ctx, knh_class_t bcid, char *extra)
//{
//	if(bcid == CLASS_String) {
//		ClassSpec *cs = new_Vocabulary(ctx, "it", "Roma", "Milano", "Roma", NULL);
//		konoha_addVocabularyMapper(ctx, DP(cs)->cid, "konoha.String{http://konoha/ItalianCity.en}");
//		return cs;
//	}
//	return (ClassSpec*)KNH_NULL;
//}

/* ======================================================================== */
/* @data */

static
knh_StringConstData_t URNAliasData[] = {
//	{":摂氏", "http://konoha/Temperature/Celsius"},
//	{":華氏", "http://konoha/Temperature/Fahrenheit"},
	{":C", "http://konoha/Temperature/Celsius"},
	{":F", "http://konoha/Temperature/Fahrenheit"},
	{":K", "http://konoha/Temperature/Kelvin"},
	{":Celsius", "http://konoha/Temperature/Celsius"},
	{":Fahrenheit", "http://konoha/Temperature/Fahrenheit"},
	{":Kelvin", "http://konoha/Temperature/Kelvin"},
	{":MyRoom", "http://konoha/Temperature/MyRoom"},
	{":M", "http://konoha/English/Date/Month"},
	{":W", "http://konoha/English/Date/Week"},
	{NULL}
};

static
knh_NamedPointerData_t ClassSpecFuncData[] = {
	{"http://konoha/Temperature", unit_Temperature},
	{"http://konoha/English/Date", unit_Date},
	{NULL}
};

/* ------------------------------------------------------------------------ */

int package_init(Ctx *ctx)
{
//	KNH_NOTICE(ctx, "loading SCOPE2009..");
//	konoha_loadURNAliasData(ctx, URNAliasData);
//	konoha_loadClassSpecFuncData(ctx, ClassSpecFuncData);
	return 1;
}

/* ------------------------------------------------------------------------ */



#ifdef __cplusplus
}
#endif
