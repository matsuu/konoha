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
///****************************************************************************
// * 
// * konoha Open Source License 1.0  (Based on the BSD License)
// *
// * Copyright (c) 2005-2006, Kimio Kuramitsu <kimio@ynu.ac.jp>
// *           (c) 2006-      konoha Open Source Forum 
// * All rights reserved.
// * 
// ****************************************************************************/
//
///* ************************************************************************ */
//
//#include"commons.h"
//
///* ************************************************************************ */
///* @c Token */
//
//Token *new_Token__typen(Ctx *ctx, Token *tk)
//{
//	Token* b = (Token*)knh_Object_malloc(ctx, CLASS_Token);
//	b->flag = tk->flag;
//	b->tt = tk->tt;
//	DEBUG_ASSERT(IS_String(tk->data));
//	KNH_INITv(b->data, tk->data);
//	knh_Token_FL_update(b, knh_Token_FL(tk));
//	return b;
//}
//
///* ------------------------------------------------------------------------ */
//
//PUBLIC
//void knh_Token_swap(Token *a, Token *b)
//{
//	Token temp;
//	temp = *a;
//	*a = *b;
//	*b = temp;
//}
//
///* ------------------------------------------------------------------------ */
//
//PUBLIC
//Token *knh_Token_typebase(Token *b)
//{
//	DEBUG_ASSERT(b->tt == TT_TYPEN);
//	if(IS_String(b->data)) return b;
//	DEBUG_ASSERT(IS_Array(b->data));
//	Token *tb = (Token*)knh_Array_n(b->data, 0);
//	DEBUG_ASSERT(tb->tt == TT_TYPEN);
//	DEBUG_ASSERT(IS_String(tb->data));
//	return tb;
//}
//
///* ------------------------------------------------------------------------ */
//
//PUBLIC
//size_t knh_Token_typesize(Token *b)
//{
//	DEBUG_ASSERT(b->tt == TT_TYPEN);
//	if(IS_String(b->data)) return 0;
//	DEBUG_ASSERT(IS_Array(b->data));
//	return knh_Array_size((Array*)b->data) - 1;
//}
//
///* ------------------------------------------------------------------------ */
//
//PUBLIC
//Token *knh_Token_types(Token *b, size_t n)
//{
//	DEBUG_ASSERT(IS_Array(b->data));
//	return (Token*)knh_Array_n((Array*)b->data, n+1);
//}
//
///* ------------------------------------------------------------------------ */
//
//Token *knh_Token_typelast(Token *b)
//{
//	DEBUG_ASSERT(b->tt == TT_TYPEN);
//	if(IS_String(b->data)) return b;
//	DEBUG_ASSERT(IS_Array(b->data));
//	if(knh_Array_size((Array*)b->data) == 1) return b;
//	return knh_Token_typelast((Token*)knh_Array_n((Array*)b->data, knh_Array_size((Array*)b->data) - 1));
//}
//
///* ------------------------------------------------------------------------ */
//
//knh_bool_t knh_Token_istypeopen(Token *b)
//{
//	DEBUG_ASSERT(b->tt == TT_TYPEN);
//	return ((b->flag & TKF_BLOCK) == TKF_BLOCK);
//}
//
///* ------------------------------------------------------------------------ */
//
//void knh_Token_typeopen(Token *b)
//{
//	Token *tl = knh_Token_typelast(b);
//	DEBUG_ASSERT(tl->tt == TT_TYPEN);
//	tl->flag |= TKF_BLOCK;
//}
//
///* ------------------------------------------------------------------------ */
//
//Token *knh_Token_typeopenlast(Token *b)
//{
//	DEBUG_ASSERT(knh_Token_istypeopen(b));
//	if(IS_String(b->data)) {
//		return b;
//	}
//	DEBUG_ASSERT(IS_Array(b->data));
//	if(knh_Array_size((Array*)b->data) > 0) {
//		Token *tl = (Token*)knh_Array_last(b->data);
//		if(knh_Token_istypeopen(tl)) {
//			return knh_Token_typeopenlast(tl);
//		}
//	}
//	return b;
//}
//
///* ------------------------------------------------------------------------ */
//
//void knh_Token_typeclose(Token *b)
//{
//	Token *tl = knh_Token_typeopenlast(b);
//	DEBUG_ASSERT(knh_Token_istypeopen(tl));
//	tl->flag = tl->flag & (~TKF_BLOCK);
//	DEBUG_ASSERT(!knh_Token_istypeopen(tl));
//}
//
///* ------------------------------------------------------------------------ */
//
//PUBLIC
//void knh_Token_typeadd(Ctx *ctx, Token *b, Token *tk)
//{
//	DEBUG_ASSERT(tk->tt == TT_TYPEN);
//	Token *tl = knh_Token_typeopenlast(b);
//	DEBUG_ASSERT(knh_Token_istypeopen(tl));
//
//	if(IS_String(tl->data)) {
//		Array *na = new_Array(ctx, 2);
//		knh_Array_add(ctx, na, new_Token__typen(ctx, tl));
//		KNH_SETv(ctx, tl->data, na);
//	}
//	DEBUG_ASSERT(IS_Array(tl->data));
//	knh_Array_add(ctx, tl->data, tk);
//}
//
///* ------------------------------------------------------------------------ */
//
//knh_bool_t knh_Token_isArrayPostfix(Token *tk)
//{
//	/* [] */
//	return (tk->tt == TT_BRANCET && knh_Token_tokens_size(tk) == 0) ;	
//}
//
///* ------------------------------------------------------------------------ */
//
//void knh_Token_typeToArray(Ctx *ctx, Token *b)
//{
//	DEBUG_ASSERT(b->tt == TT_TYPEN);
//	Token *tb = knh_Token_typebase(knh_Token_typelast(b));
//	DEBUG_ASSERT(IS_String(tb->data));
//	char buf[CLASSNAKNH_BUFSIZ];
//	//DEBUG("** %s", knh_Token_tochar(tb));
//	knh_snprintf(buf, sizeof(buf), "%s[]", knh_Token_tochar(tb));
//	KNH_SETv(ctx, tb->data, new_String__fast(ctx, CLASS_String, B(buf)));
//}
//
///* ------------------------------------------------------------------------ */
//
//knh_bool_t knh_Token_isclosureparams(Token *tk)
//{
//	if(tk->tt != TT_PARENTHESIS) return 0;
//	Token **ts = knh_Token_ts(tk);
//	knh_int_t i, e = knh_Token_tokens_size(tk);
//	for(i = 0; i < e; i++) {
//		if(ts[i]->tt == TT_TYPEN) continue;
//		if(ts[i]->tt == TT_COMMA) continue;
//		return 0;
//	}
//	return 1;
//}
//
///* ------------------------------------------------------------------------ */
//
//void knh_Token_typeToClosure(Ctx *ctx, Token *b, Token *tk)
//{
//	DEBUG_ASSERT(b->tt == TT_TYPEN);
//	DEBUG_ASSERT(tk->tt == TT_PARENTHESIS);
//	Token *tc = new_Token__byte(ctx, knh_Token_FL(b), 0, STEXT("Closure"));
//	knh_Token_swap(b,tc);
//	knh_Token_typeopen(b);
//	knh_Token_typeadd(ctx, b, tc);
//	Token **ts = knh_Token_ts(tk);
//	knh_int_t i, e = knh_Token_tokens_size(tk);
//	for(i = 0; i < e; i++) {
//		if(ts[i]->tt == TT_TYPEN) {
//			knh_Token_typeadd(ctx, b, ts[i]);
//		}
//	}
//	knh_Token_typeclose(b);
//}
//
///* ------------------------------------------------------------------------ */
//
//void knh_Token_typeToNormal(Ctx *ctx, Token *b)
//{
//	DEBUG_ASSERT(b->tt == TT_TYPEN);
//	knh_Token_typeclose(b);
//	Token *tb = knh_Token_typebase(b);
//	KNH_SETv(ctx, b->data, tb->data);
//}
//
///* ======================================================================== */
///* [line] */
//
//PUBLIC
//void knh_Token_parser_typeadd(Ctx *ctx, Token *b, Token *tk_prev, Token *tk)
//{
//	DEBUG_ASSERT(tk_prev->tt = TT_TYPEN);
//	LOCAL_OPEN(ctx, 0);
//	LOCAL_PUSH(ctx, tk);
//	LOCAL_CLOSE_WHEN_RETURN(ctx);	
//
//	switch(tk->tt) {
//	case TT_LT:
//		knh_Token_typeopen(tk_prev);
//		return;
//	case TT_GT:
//		if(knh_Token_istypeopen(tk_prev)) {
//			knh_Token_typeclose(tk_prev);
//			return;
//		}
//		break;
//	case TT_RSHIFT:
//		if(knh_Token_istypeopen(tk_prev)) {
//			knh_Token_typeclose(tk_prev);
//			if(knh_Token_istypeopen(tk_prev)) {
//				knh_Token_typeclose(tk_prev);
//				return;
//			}
//		}
//		break;
//	case TT_BRANCET:
//		if(knh_Token_isArrayPostfix(tk)) {
//			knh_Token_typeToArray(ctx, tk_prev);
//			return;
//		}
//		break;
//	case TT_PARENTHESIS:
//		if(knh_Token_isclosureparams(tk)) {
//			knh_Token_typeToClosure(ctx, tk_prev, tk);
//			return;
//		}
//		//tk_prev->flag |= TKF_FUNC;
//		break;
//		
//	case TT_TYPEN:
//		if(knh_Token_istypeopen(tk_prev)) {
//			knh_Token_typeadd(ctx, tk_prev, tk);
//			return;
//		}
//		break;
//	case TT_COMMA:
//		if(knh_Token_istypeopen(tk_prev)) {
//			return;
//		}
//		break;
//	}
//	if(knh_Token_istypeopen(tk_prev)) {
//		knh_Token_typeclose(tk_prev);
//		NOTE_WarningInGenerics(ctx, knh_Token_FL(tk), knh_Token_typebase(tk_prev));
//		knh_Token_typeToNormal(ctx, tk_prev);
//	}
//	knh_Tokens_add(ctx, b, tk);
//}
//
///* ======================================================================== */
///* [asm] */
//
//PUBLIC
//knh_type_t knh_Token_type(Ctx *ctx, Token *b)
//{
//	DEBUG_ASSERT(b->tt == TT_TYPEN);
//	knh_bytes_t tname = knh_Token_tobytes(b);
//	knh_int_t loc = knh_bytes_index(tname, '[');
//	if(loc > 0) {
//		tname = knh_bytes_first(tname, loc);
//	}
//	knh_type_t btype = knh_NameSpace_guess_type(ctx, Context_nspace(ctx), NULL, tname);
//	if(loc > 0) {
//		TODO();
//		return CLASS_Array;
//	}
//	return btype;
//}

#ifdef __cplusplus 
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
