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
/* [try-catch-finally] */

Stmt *new_Stmt__catch(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
	/* TT_CATCH */;
	DEBUG_ASSERT(ts[s]->tt == TT_CATCH);
	DEBUG_ASSERT(s == *cp);
	Stmt *b = new_Stmt(ctx, 0, STT_CATCH);
	knh_Stmt_add_meta(ctx, b, ts, s);
	knh_Stmt_terms_add__fast(ctx, b, ts[*cp]);

    *cp += 1;
    /* (catch_param) */
	if(*cp += 1 < e && ts[*cp]->tt == TT_PARENTHESIS && knh_Token_tokens_size(ts[*cp]) == 2) {
		Token **tp = knh_Token_ts(ts[*cp]);
		if(knh_Token_isTYPEN(tp[0])) {
			knh_Stmt_terms_add__fast(ctx, b, tp[0]);
		}else{
			KNH_GOTO(L_ERR);
		}
		if(knh_Token_isFIELDN(tp[1])) {
			knh_Stmt_terms_add__fast(ctx, b, tp[1]);
		}else{
			KNH_GOTO(L_ERR);
		}
		*cp += 1;
		goto L_2;
	}else {
		KNH_GOTO(L_ERR);
	}
	
	L_2:; 
	if(*cp < e && ts[*cp]->tt == TT_BRACE) { /* %s */
		knh_Stmt_terms_add(ctx, b, new_Stmt__block(ctx, knh_Token_ts(ts[*cp]), 0, knh_Token_tokens_size(ts[*cp])));
		knh_Token_tokens_empty(ctx, ts[*cp]);
		*cp += 1;
		goto L_3;
	}else {
		KNH_GOTO(L_ERR);
	}
	
	L_3:; 
	if(*cp < e && ts[*cp]->tt == TT_CATCH) {
		knh_Stmt_tail_append(ctx, b, new_Stmt__catch(ctx, ts, *cp, e, cp));
	}

	return b;

	L_ERR:;
	knh_int_t ee = knh_tokens_epos(s, *cp, e);
	MC_EPRINT(ctx, ts[ee], MC_ERROR, "catch statement: %s", knh_Token_tochar(ts[ee]));
	knh_Stmt_toSyntaxError(ctx, b, ts[ee]);
	*cp = knh_tokens_nextstmt(ts, *cp, e);
	return b;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
