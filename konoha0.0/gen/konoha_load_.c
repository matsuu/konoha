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

/* ======================================================================== */
/* [prototype] */

void knh_package_konoha_ginit(Ctx *ctx);
void knh_package_naruto_ginit(Ctx *ctx);
void knh_package_konohac_ginit(Ctx *ctx);
void knh_package_math_ginit(Ctx *ctx);
void knh_driver_mysql_ginit(Ctx *ctx);
/* ======================================================================== */
/* [init] */

void konoha_load_builtins(Ctx *ctx)
{
	KNH_TFIELDN(ctx, FIELDN_this, new_String__STEXT(ctx, CLASS_String, "this"));
	KNH_TFIELDN(ctx, FIELDN_vargs, new_String__STEXT(ctx, CLASS_String, "vargs"));
	KNH_TFIELDN(ctx, FIELDN_run, new_String__STEXT(ctx, CLASS_String, "run"));
	KNH_TFIELDN(ctx, FIELDN_new, new_String__STEXT(ctx, CLASS_String, "new"));
	KNH_TFIELDN(ctx, FIELDN_init, new_String__STEXT(ctx, CLASS_String, "init"));
	KNH_TFIELDN(ctx, FIELDN_new____array, new_String__STEXT(ctx, CLASS_String, "new::array"));
	KNH_TFIELDN(ctx, FIELDN_value, new_String__STEXT(ctx, CLASS_String, "value"));
	KNH_TFIELDN(ctx, FIELDN_new____init, new_String__STEXT(ctx, CLASS_String, "new::init"));
	KNH_TFIELDN(ctx, FIELDN_____fast, new_String__STEXT(ctx, CLASS_String, "::fast"));
	KNH_TFIELDN(ctx, FIELDN_index, new_String__STEXT(ctx, CLASS_String, "index"));
	KNH_TFIELDN(ctx, FIELDN_, new_String__STEXT(ctx, CLASS_String, ""));
	KNH_TFIELDN(ctx, FIELDN_opAdd, new_String__STEXT(ctx, CLASS_String, "opAdd"));
	KNH_TFIELDN(ctx, FIELDN_v, new_String__STEXT(ctx, CLASS_String, "v"));
	KNH_TFIELDN(ctx, FIELDN_opSub, new_String__STEXT(ctx, CLASS_String, "opSub"));
	KNH_TFIELDN(ctx, FIELDN_n, new_String__STEXT(ctx, CLASS_String, "n"));
	KNH_TFIELDN(ctx, FIELDN_opMul, new_String__STEXT(ctx, CLASS_String, "opMul"));
	KNH_TFIELDN(ctx, FIELDN_opDiv, new_String__STEXT(ctx, CLASS_String, "opDiv"));
	KNH_TFIELDN(ctx, FIELDN_opMod, new_String__STEXT(ctx, CLASS_String, "opMod"));
	KNH_TFIELDN(ctx, FIELDN_opEq, new_String__STEXT(ctx, CLASS_String, "opEq"));
	KNH_TFIELDN(ctx, FIELDN_opNeq, new_String__STEXT(ctx, CLASS_String, "opNeq"));
	KNH_TFIELDN(ctx, FIELDN_opLt, new_String__STEXT(ctx, CLASS_String, "opLt"));
	KNH_TFIELDN(ctx, FIELDN_opLte, new_String__STEXT(ctx, CLASS_String, "opLte"));
	KNH_TFIELDN(ctx, FIELDN_opGt, new_String__STEXT(ctx, CLASS_String, "opGt"));
	KNH_TFIELDN(ctx, FIELDN_opGte, new_String__STEXT(ctx, CLASS_String, "opGte"));
	KNH_TFIELDN(ctx, FIELDN_opLogicalAnd, new_String__STEXT(ctx, CLASS_String, "opLogicalAnd"));
	KNH_TFIELDN(ctx, FIELDN_opLogicalOr, new_String__STEXT(ctx, CLASS_String, "opLogicalOr"));
	KNH_TFIELDN(ctx, FIELDN_opLogicalXor, new_String__STEXT(ctx, CLASS_String, "opLogicalXor"));
	KNH_TFIELDN(ctx, FIELDN_opLogicalNot, new_String__STEXT(ctx, CLASS_String, "opLogicalNot"));
	KNH_TFIELDN(ctx, FIELDN_opLShift, new_String__STEXT(ctx, CLASS_String, "opLShift"));
	KNH_TFIELDN(ctx, FIELDN_opRShift, new_String__STEXT(ctx, CLASS_String, "opRShift"));
	KNH_TFIELDN(ctx, FIELDN_s, new_String__STEXT(ctx, CLASS_String, "s"));
	KNH_TFIELDN(ctx, FIELDN_w, new_String__STEXT(ctx, CLASS_String, "w"));
	KNH_TFIELDN(ctx, FIELDN_m, new_String__STEXT(ctx, CLASS_String, "m"));
	KNH_TFIELDN(ctx, FIELDN_x, new_String__STEXT(ctx, CLASS_String, "x"));
	KNH_TFIELDN(ctx, FIELDN_bits, new_String__STEXT(ctx, CLASS_String, "bits"));
	KNH_TFIELDN(ctx, FIELDN_dump, new_String__STEXT(ctx, CLASS_String, "dump"));
	KNH_TFIELDN(ctx, FIELDN_random, new_String__STEXT(ctx, CLASS_String, "random"));
	KNH_TFIELDN(ctx, FIELDN_in, new_String__STEXT(ctx, CLASS_String, "in"));
	KNH_TFIELDN(ctx, FIELDN_input, new_String__STEXT(ctx, CLASS_String, "input"));
	KNH_TFIELDN(ctx, FIELDN_out, new_String__STEXT(ctx, CLASS_String, "out"));
	KNH_TFIELDN(ctx, FIELDN_err, new_String__STEXT(ctx, CLASS_String, "err"));
	KNH_TFIELDN(ctx, FIELDN_another, new_String__STEXT(ctx, CLASS_String, "another"));
	KNH_TFIELDN(ctx, FIELDN_urn, new_String__STEXT(ctx, CLASS_String, "urn"));
	KNH_TFIELDN(ctx, FIELDN_query, new_String__STEXT(ctx, CLASS_String, "query"));
	KNH_TFIELDN(ctx, FIELDN_count, new_String__STEXT(ctx, CLASS_String, "count"));
	KNH_TFIELDN(ctx, FIELDN_reset, new_String__STEXT(ctx, CLASS_String, "reset"));
	KNH_TFIELDN(ctx, FIELDN_size, new_String__STEXT(ctx, CLASS_String, "size"));
	KNH_TFIELDN(ctx, FIELDN_term, new_String__STEXT(ctx, CLASS_String, "term"));
	KNH_TFIELDN(ctx, FIELDN_add____fast, new_String__STEXT(ctx, CLASS_String, "add::fast"));
	KNH_TFIELDN(ctx, FIELDN_add, new_String__STEXT(ctx, CLASS_String, "add"));
	KNH_TFIELDN(ctx, FIELDN_clear, new_String__STEXT(ctx, CLASS_String, "clear"));
	KNH_TFIELDN(ctx, FIELDN_readLine, new_String__STEXT(ctx, CLASS_String, "readLine"));
	KNH_TFIELDN(ctx, FIELDN_close, new_String__STEXT(ctx, CLASS_String, "close"));
	KNH_TFIELDN(ctx, FIELDN_pop, new_String__STEXT(ctx, CLASS_String, "pop"));
	KNH_TFIELDN(ctx, FIELDN_slice, new_String__STEXT(ctx, CLASS_String, "slice"));
	KNH_TFIELDN(ctx, FIELDN_start, new_String__STEXT(ctx, CLASS_String, "start"));
	KNH_TFIELDN(ctx, FIELDN_end, new_String__STEXT(ctx, CLASS_String, "end"));
	KNH_TFIELDN(ctx, FIELDN_inputStream, new_String__STEXT(ctx, CLASS_String, "inputStream"));
	KNH_TFIELDN(ctx, FIELDN_outputStream, new_String__STEXT(ctx, CLASS_String, "outputStream"));
	KNH_TFIELDN(ctx, FIELDN_match, new_String__STEXT(ctx, CLASS_String, "match"));
	KNH_TFIELDN(ctx, FIELDN_initialCapacity, new_String__STEXT(ctx, CLASS_String, "initialCapacity"));
	KNH_TFIELDN(ctx, FIELDN_key, new_String__STEXT(ctx, CLASS_String, "key"));
	KNH_TFIELDN(ctx, FIELDN_append, new_String__STEXT(ctx, CLASS_String, "append"));
	KNH_TFIELDN(ctx, FIELDN_remove, new_String__STEXT(ctx, CLASS_String, "remove"));
	KNH_TFIELDN(ctx, FIELDN_opIn, new_String__STEXT(ctx, CLASS_String, "opIn"));
	KNH_TFIELDN(ctx, FIELDN_keys, new_String__STEXT(ctx, CLASS_String, "keys"));
	KNH_TFIELDN(ctx, FIELDN_write, new_String__STEXT(ctx, CLASS_String, "write"));
	KNH_TFIELDN(ctx, FIELDN_buf, new_String__STEXT(ctx, CLASS_String, "buf"));
	KNH_TFIELDN(ctx, FIELDN_flush, new_String__STEXT(ctx, CLASS_String, "flush"));
	KNH_TFIELDN(ctx, FIELDN_runtime, new_String__STEXT(ctx, CLASS_String, "runtime"));
	KNH_TFIELDN(ctx, FIELDN_opInstanceof, new_String__STEXT(ctx, CLASS_String, "opInstanceof"));
	KNH_TFIELDN(ctx, FIELDN_c, new_String__STEXT(ctx, CLASS_String, "c"));
	KNH_TFIELDN(ctx, FIELDN_property, new_String__STEXT(ctx, CLASS_String, "property"));
	KNH_TFIELDN(ctx, FIELDN_class, new_String__STEXT(ctx, CLASS_String, "class"));
	KNH_TFIELDN(ctx, FIELDN_name, new_String__STEXT(ctx, CLASS_String, "name"));
	KNH_TFIELDN(ctx, FIELDN_isAbstract, new_String__STEXT(ctx, CLASS_String, "isAbstract"));
	KNH_TFIELDN(ctx, FIELDN_uRN, new_String__STEXT(ctx, CLASS_String, "uRN"));
	KNH_TFIELDN(ctx, FIELDN_next, new_String__STEXT(ctx, CLASS_String, "next"));
	KNH_TFIELDN(ctx, FIELDN_e, new_String__STEXT(ctx, CLASS_String, "e"));
	KNH_TFIELDN(ctx, FIELDN_msg, new_String__STEXT(ctx, CLASS_String, "msg"));
	KNH_TFIELDN(ctx, FIELDN_bag, new_String__STEXT(ctx, CLASS_String, "bag"));
	KNH_TFIELDN(ctx, FIELDN_compare, new_String__STEXT(ctx, CLASS_String, "compare"));
	KNH_TFIELDN(ctx, FIELDN_other, new_String__STEXT(ctx, CLASS_String, "other"));
	KNH_TFIELDN(ctx, FIELDN_opNot, new_String__STEXT(ctx, CLASS_String, "opNot"));
	KNH_TFIELDN(ctx, FIELDN_opSeq, new_String__STEXT(ctx, CLASS_String, "opSeq"));
	KNH_TFIELDN(ctx, FIELDN_opIsMapTo, new_String__STEXT(ctx, CLASS_String, "opIsMapTo"));
	KNH_TFIELDN(ctx, FIELDN_empty, new_String__STEXT(ctx, CLASS_String, "empty"));
	KNH_TFIELDN(ctx, FIELDN_refc, new_String__STEXT(ctx, CLASS_String, "refc"));
	KNH_TFIELDN(ctx, FIELDN_addr, new_String__STEXT(ctx, CLASS_String, "addr"));
	KNH_TFIELDN(ctx, FIELDN_equals, new_String__STEXT(ctx, CLASS_String, "equals"));
	KNH_TFIELDN(ctx, FIELDN_startsWith, new_String__STEXT(ctx, CLASS_String, "startsWith"));
	KNH_TFIELDN(ctx, FIELDN_endsWith, new_String__STEXT(ctx, CLASS_String, "endsWith"));
	KNH_TFIELDN(ctx, FIELDN_placeOrder, new_String__STEXT(ctx, CLASS_String, "placeOrder"));
	KNH_TFIELDN(ctx, FIELDN_uname, new_String__STEXT(ctx, CLASS_String, "uname"));
	KNH_TFIELDN(ctx, FIELDN_order, new_String__STEXT(ctx, CLASS_String, "order"));
	KNH_TFIELDN(ctx, FIELDN_code, new_String__STEXT(ctx, CLASS_String, "code"));
	KNH_TFIELDN(ctx, FIELDN_sin, new_String__STEXT(ctx, CLASS_String, "sin"));
	KNH_TFIELDN(ctx, FIELDN_isRelease, new_String__STEXT(ctx, CLASS_String, "isRelease"));
	KNH_TFIELDN(ctx, FIELDN_isDebug, new_String__STEXT(ctx, CLASS_String, "isDebug"));
	KNH_TFIELDN(ctx, FIELDN_isImmutable, new_String__STEXT(ctx, CLASS_String, "isImmutable"));
	KNH_TFIELDN(ctx, FIELDN_hasMetaData, new_String__STEXT(ctx, CLASS_String, "hasMetaData"));
	KNH_TFIELDN(ctx, FIELDN_isSynchronized, new_String__STEXT(ctx, CLASS_String, "isSynchronized"));
	KNH_TFIELDN(ctx, FIELDN_isModified, new_String__STEXT(ctx, CLASS_String, "isModified"));
	KNH_TFIELDN(ctx, FIELDN_modified, new_String__STEXT(ctx, CLASS_String, "modified"));
	KNH_TFIELDN(ctx, FIELDN_b, new_String__STEXT(ctx, CLASS_String, "b"));
	KNH_TFIELDN(ctx, FIELDN_isMetaExtensible, new_String__STEXT(ctx, CLASS_String, "isMetaExtensible"));
	KNH_TFIELDN(ctx, FIELDN_isPrivate, new_String__STEXT(ctx, CLASS_String, "isPrivate"));
	KNH_TFIELDN(ctx, FIELDN_isPublic, new_String__STEXT(ctx, CLASS_String, "isPublic"));
	KNH_TFIELDN(ctx, FIELDN_isFinal, new_String__STEXT(ctx, CLASS_String, "isFinal"));
	KNH_TFIELDN(ctx, FIELDN_isSystem, new_String__STEXT(ctx, CLASS_String, "isSystem"));
	KNH_TFIELDN(ctx, FIELDN_isNA, new_String__STEXT(ctx, CLASS_String, "isNA"));
	KNH_TFIELDN(ctx, FIELDN_isVirtual, new_String__STEXT(ctx, CLASS_String, "isVirtual"));
	KNH_TFIELDN(ctx, FIELDN_isStatic, new_String__STEXT(ctx, CLASS_String, "isStatic"));
	KNH_TFIELDN(ctx, FIELDN_isClass, new_String__STEXT(ctx, CLASS_String, "isClass"));
	KNH_TFIELDN(ctx, FIELDN_isVarArgs, new_String__STEXT(ctx, CLASS_String, "isVarArgs"));
	KNH_TFIELDN(ctx, FIELDN_isAspect, new_String__STEXT(ctx, CLASS_String, "isAspect"));
	KNH_TFIELDN(ctx, FIELDN_isInterface, new_String__STEXT(ctx, CLASS_String, "isInterface"));
	KNH_TFIELDN(ctx, FIELDN_isSignificant, new_String__STEXT(ctx, CLASS_String, "isSignificant"));
	KNH_TFIELDN(ctx, FIELDN_isSynonym, new_String__STEXT(ctx, CLASS_String, "isSynonym"));
	KNH_TFIELDN(ctx, FIELDN_isLossLess, new_String__STEXT(ctx, CLASS_String, "isLossLess"));
	KNH_TFIELDN(ctx, FIELDN_isTotal, new_String__STEXT(ctx, CLASS_String, "isTotal"));
	KNH_TFIELDN(ctx, FIELDN_isPartial, new_String__STEXT(ctx, CLASS_String, "isPartial"));
	KNH_TFIELDN(ctx, FIELDN_isTemporal, new_String__STEXT(ctx, CLASS_String, "isTemporal"));
	KNH_TFIELDN(ctx, FIELDN_isLocal, new_String__STEXT(ctx, CLASS_String, "isLocal"));
	KNH_TFIELDN(ctx, FIELDN_isDerived, new_String__STEXT(ctx, CLASS_String, "isDerived"));
	KNH_TFIELDN(ctx, FIELDN_isUnsigned, new_String__STEXT(ctx, CLASS_String, "isUnsigned"));
	KNH_TFIELDN(ctx, FIELDN_isFatal, new_String__STEXT(ctx, CLASS_String, "isFatal"));
	KNH_TFIELDN(ctx, FIELDN_isLogging, new_String__STEXT(ctx, CLASS_String, "isLogging"));
	KNH_TFIELDN(ctx, FIELDN_isGenerated, new_String__STEXT(ctx, CLASS_String, "isGenerated"));
/* ------------------------------------------------------------------------ */

	knh_package_konoha_ginit(ctx);
	knh_package_naruto_ginit(ctx);
	knh_package_konohac_ginit(ctx);
#ifdef KONOHA_MONOLITHIC
	knh_package_math_ginit(ctx);
#endif
#ifdef KONOHA_MONOLITHIC
	knh_driver_mysql_ginit(ctx);
#endif
}

#ifdef __cplusplus
}
#endif
