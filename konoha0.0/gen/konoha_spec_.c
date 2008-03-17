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

#include<konoha/konoha_dev.h>


#ifdef __cplusplus 
extern "C" {
#endif

/* ======================================================================== */

knh_class_t knh_system_loadEnum(Ctx *ctx, knh_bytes_t urn)
{
	knh_index_t idx = knh_bytes_rindex(urn, '/');
	DEBUG_ASSERT(idx != -1);
	int ch = urn.buf[idx+1];
	knh_class_t cid/*, tcid*/;

	switch(ch) {
	case 'A':
		if(ISB(urn, "http://enum/Age")) {
			cid = KNH_TENUM(ctx, "http://enum/Age", "", 0, 200, 0, 0, 120);
			return cid;
		}
		break;

	case 'M':
		if(ISB(urn, "http://enum/Month")) {
			cid = KNH_TENUM(ctx, "http://enum/Month", "", 1, 12, 1, 1, 12);
			return cid;
		}
		break;

	}

	return CLASS_Int;
}

/* ------------------------------------------------------------------------ */

knh_class_t knh_system_loadUnit(Ctx *ctx, knh_bytes_t urn)
{
	knh_index_t idx = knh_bytes_rindex(urn, '/');
	DEBUG_ASSERT(idx != -1);
	int ch = urn.buf[idx+1];
	knh_class_t cid, tcid;

	switch(ch) {
	case 'C':
		if(ISB(urn, "http://unit/Celsius")) {
			cid = KNH_TUNIT(ctx, "http://unit/Celsius", "C", -273.15, KNH_FLOAT_MAX, 0.0, 0.01);
			return cid;
		}
		break;

	case 'F':
		if(ISB(urn, "http://unit/Fahrenheit")) {
			cid = KNH_TUNIT(ctx, "http://unit/Fahrenheit", "F", -459.67, KNH_FLOAT_MAX, 32.0, 0.01);
			tcid = knh_tclass_classURN(ctx, CLASS_Float, B("http://unit/Celsius"));
			KNH_TAFFINE(ctx, cid, tcid, 5.0/9.0, -32.0*5.0/9.0);
			return cid;
		}
		break;
	}

	return CLASS_Float;
}

/* ------------------------------------------------------------------------ */

knh_class_t knh_system_loadVocabulary(Ctx *ctx, knh_bytes_t urn)
{
//	knh_index_t idx = knh_bytes_rindex(urn, '/');
//	DEBUG_ASSERT(idx != -1);
//	int ch = urn.buf[idx+1];
//	knh_class_t cid, tcid;
//
//	switch(ch) {
//	case 'S':
//		if(ISB(urn, "http://konoha/EnglishSeason")) {
//			cid = KNH_TVOCAB(ctx, "http://konoha/EnglishSeason", "", "spring", "summer", "fall", "winter");
// 			cid = KNH_TUNIT(ctx, "http://unit/Fahrenheit", "F", -459.67, KNH_FLOAT_MAX, 32.0, 0.01);
//			tcid = knh_tclass_classURN(ctx, CLASS_Float, B("http://unit/Celsius"));
//			KNH_TAFFINE(ctx, cid, tcid, 5.0/9.0, -32.0*5.0/9.0);
//			return cid;
//		}
//		break;
//		
//	}
//
//
	return CLASS_String;
}




/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
