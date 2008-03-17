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
/* [using] */


Stmt *new_Stmt__using(Ctx *ctx, Token **ts, knh_int_t s, knh_int_t e, knh_int_t *cp)
{
	DEBUG_ASSERT(ts[s]->tt == TT_USING);
	DEBUG_ASSERT(s == *cp);
	
	Stmt *stmt = NULL;
	int c = *cp + 1;
	
	if(!(c < e)) {
		MC_EPRINT(ctx, ts[s], MC_ERROR, "using statement: no entry");
		*cp = c;
		return new_Stmt__SyntaxError(ctx, ts, s, e, cp);
	}

	/* first */
	knh_bytes_t op = knh_Token_tobytes(ts[c]);
	
	if(ISB(op, "import")) {
		c += 1;
		goto L_UIMPORT;
	}

	if(ISB(op, "unit")) {
		stmt= new_Stmt(ctx, 0, STT_UFLOAT);
		c += 1;
		goto L_CLASSTN;
	}

	if(knh_bytes_startsWith(op, STEXT("vacab"))) {
		stmt = new_Stmt(ctx, 0, STT_UVOCAB);
		c += 1;
		goto L_CLASSTN;
	}

	if(ISB(op, "enum")) {
		stmt= new_Stmt(ctx, 0, STT_UINT);
		c += 1;
		goto L_CLASSTN;
	}

	if(ISB(op, "table")) {
		stmt = new_Stmt(ctx, 0, STT_UTABLE);
		c += 1;
		goto L_CLASSTN;
	}
	
	/* shorthand */
	if(knh_Token_isNSCLASSN(ts[c])) {
		goto L_UIMPORT;
	}

	if(knh_Token_isCLASSTN(ts[c])) {
		if(knh_bytes_startsWith(op, STEXT("Int::"))) {
			stmt= new_Stmt(ctx, 0, STT_UINT);
			goto L_CLASSTN;
		}
		if(knh_bytes_startsWith(op, STEXT("Float::"))) {
			stmt= new_Stmt(ctx, 0, STT_UFLOAT);
			goto L_CLASSTN;
	   }
	   if(knh_bytes_startsWith(op, STEXT("String::"))) {
		   stmt= new_Stmt(ctx, 0, STT_UVOCAB);
			goto L_CLASSTN;
	   }
	   if(knh_bytes_startsWith(op, STEXT("Int64::"))) {
		   stmt= new_Stmt(ctx, 0, STT_UINT64);
			goto L_CLASSTN;
	   }
	   if(c + 1 < e && knh_Token_isNSCLASSN(ts[c+1])) {
			stmt = new_Stmt(ctx, 0, STT_UIMPORT);
			goto L_CLASSTN;
	   }
	   KNH_GOTO(L_ERR);
	}

	KNH_GOTO(L_ERR);
	
	/* second */
	
	L_UIMPORT:
	if(knh_Token_isNSCLASSN(ts[c])) {
		stmt = new_Stmt(ctx, 0, STT_UIMPORT);
		knh_Stmt_add_meta(ctx, stmt, ts, s);
		knh_Stmt_terms_add(ctx, stmt, new_Token__ASIS(ctx, ts[c]));
		knh_Stmt_terms_add(ctx, stmt, ts[c]);
		c += 1;
		goto L_END;
	}
	else {
	   KNH_GOTO(L_ERR);
	}
	
	L_CLASSTN:;
	DEBUG_ASSERT(stmt!= NULL);
	knh_Stmt_add_meta(ctx, stmt, ts, s);

	if(c < e && knh_Token_isCLASSTN(ts[c])) {
		knh_Stmt_terms_add(ctx, stmt, ts[c]);
		c += 1;
		goto L_CURN;
	}
	else {
		KNH_GOTO(L_ERR);
	}

	L_CURN:;
	if(c < e && (knh_Token_isURN(ts[c]) || knh_Token_isNSCLASSN(ts[c]))) {
		knh_Stmt_terms_add(ctx, stmt, ts[c]);
		c += 1;
		goto L_END;
	}
	else {
		KNH_GOTO(L_ERR);
	}

	L_END:;
	/* ; */
	if(c < e && ts[c]->tt == TT_SEMICOLON) {
		c += 1;
	}
	else {
		//MC_EPRINT(ctx, ts[c-1], MC_NOTICE, "; required");
	}
	*cp = c;	
	return stmt;
	
	L_ERR:;
	knh_int_t ee = knh_tokens_epos(s, c, e);
	MC_EPRINT(ctx, ts[ee], MC_ERROR, "using statement: %s", knh_Token_tochar(ts[ee]));
	if(stmt == NULL) {
		return new_Stmt__SyntaxError(ctx, ts, c, e, cp);
	}
	knh_Stmt_toSyntaxError(ctx, stmt, ts[ee]);
	*cp = knh_tokens_nextstmt(ts, c, e);
	return stmt; 
}

/* ------------------------------------------------------------------------ */


#ifdef __cplusplus
}
#endif
