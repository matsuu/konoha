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
/* [stmt] */

knh_int_t knh_tokens_skipmeta(Token **ts, knh_int_t s, knh_int_t e)
{
	knh_int_t i;
	for(i = s; i < e; i++) {
		if(ts[i]->tt == TT_LABEL) continue;
		if(ts[i]->tt == TT_METAN) {
			if(i + 1 < e && ts[i+1]->tt == TT_PARENTHESIS) {
				i++;
			}
			continue;
		}
		return i;
	}
	return e;
}

/* ------------------------------------------------------------------------ */

Token *new_Token__metavalue(Ctx *ctx, Token *tk)
{
	TODO();
	return new_Token__RAW(ctx, KNH_FLAG_TKF_GENERATED, tk, KNH_NULL);
}

/* ======================================================================== */
/* [stmt] */

INLINE
knh_bool_t knh_Stmt_hasMeta(Stmt *b)
{
	return (IS_NOTNULL(b->meta));
}

/* ------------------------------------------------------------------------ */

void knh_Stmt_add_meta(Ctx *ctx, Stmt *b, Token **ts, knh_int_t e)
{
	knh_int_t i, labelidx = -1, s = -1;
	for(i = e - 1; i >= 0; i--) {
		if(ts[i]->tt == TT_LABEL) {
			if(labelidx != -1) {
				MC_EPRINT(ctx, ts[labelidx], MC_WARNING, "labeled twice");
			}
			s = i;
			labelidx = i;
			continue;
		}
		if(ts[i]->tt == TT_METAN) {
			s = i; 
			continue;
		}
		if(0 <= i - 1 && ts[i]->tt == TT_PARENTHESIS && ts[i-1]->tt == TT_METAN) {
			s = i - 1;
			continue;
		}
		break;
	}
	if(s == -1) return ;
	Stmt *stmt = new_Stmt(ctx, 0, STT_META);
	if(labelidx != -1) {
		knh_Stmt_terms_add(ctx, stmt, ts[labelidx]);
	}
	for(i = s; i < e; i++) {
		if(ts[i]->tt == TT_LABEL) {
			continue;
		}
		if(ts[i]->tt == TT_METAN) {
			knh_Stmt_terms_add(ctx, stmt, ts[i]);
			if(i + 1 < e && ts[i+1]->tt == TT_PARENTHESIS) {
				knh_Stmt_terms_add(ctx, stmt, new_Token__metavalue(ctx, ts[i+1]));
				i++;
			}
			else{
				knh_Stmt_terms_add(ctx, stmt, new_Token__RAW(ctx, 0, ts[i], KNH_NULL));
			}
			continue;
		}
	}
	KNH_SETv(ctx, b->meta, stmt);
}

/* ======================================================================== */
/* [label] */

Token *knh_Stmt_getLabel(Stmt *b)
{
	if(IS_NOTNULL(b->meta)) {
		DEBUG_ASSERT(b->meta->size > 0);
		Token *tk = b->meta->terms[0];
		if(IS_Token(tk) && tk->tt == TT_LABEL) {
			return tk;
		}
	}
	return KNH_NULL;
}

/* ======================================================================== */
/* [flag] */

knh_flag_t knh_Stmt_metaflag__class(Ctx *ctx, Stmt *b)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

knh_flag_t knh_Stmt_metaflag__method(Ctx *ctx, Stmt *b)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

knh_flag_t knh_Stmt_metaflag__field(Ctx *ctx, Stmt *b)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

knh_flag_t knh_Stmt_metaflag__new(Ctx *ctx, Stmt *b)
{
	return 0;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
