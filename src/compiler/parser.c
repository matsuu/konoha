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
/* [tokens] */

#undef  KNH_LVALUE
#undef	KNH_RVALUE

static Stmt *new_StmtSTMT1(Ctx *ctx, knh_tokens_t *tc);
static Stmt *new_StmtDECL(Ctx *ctx, Token *tkT, knh_tokens_t *tc);
static Term *new_TermEXPR(Ctx *ctx, knh_tokens_t *tc, int level);
static Stmt *new_StmtMETA(Ctx *ctx,  knh_tokens_t *tc, knh_stmt_t stt);
static void knh_Stmt_addMETA(Ctx *ctx, Stmt *o, knh_tokens_t *tc);
static void knh_Stmt_add_STMT1(Ctx *ctx, Stmt *o, knh_tokens_t *tc);
static void knh_Stmt_add_SEMICOLON(Ctx *ctx, Stmt *o, knh_tokens_t *tc);
static int knh_Token_isLVALUE(Ctx *ctx, Token *tkL);
static void knh_Stmt_toLVALUE(Ctx *ctx, Stmt *stmt, int pe, char *fmt);

/* ------------------------------------------------------------------------ */

static int knh_tokens_count(knh_tokens_t *tc, knh_token_t tt)
{
	Token **ts = tc->ts;
	int i, cnt = 0;
	for(i = tc->c; i < tc->e; i++) {
		if(SP(ts[i])->tt == tt) cnt++;
	}
	return cnt;
}

/* ------------------------------------------------------------------------ */

static void knh_tokens_skipSEMICOLON(knh_tokens_t *tc)
{
	while(tc->c < tc->e) {
		if(SP(tc->ts[tc->c])->tt != TT_SEMICOLON) break;
		tc->c += 1;
	}
}

/* ------------------------------------------------------------------------ */

static void knh_tokens_nextStmt(knh_tokens_t *tc)
{
	Token **ts = tc->ts;
	int i;
	for(i = tc->c; i < tc->e; i++) {
		if(knh_Token_isBOL(ts[i])) {
			tc->c = i;
			knh_tokens_skipSEMICOLON(tc);
			return;
		}
	}
	tc->c = tc->e;
}

/* ------------------------------------------------------------------------ */

static
knh_tokens_t knh_tokens_splitSTMT(Ctx *ctx, knh_tokens_t *tc)
{
	knh_tokens_t sub = *tc;
	int i;
	for(i = tc->c + 1; i < tc->e; i++) {
		if(knh_Token_isBOL(sub.ts[i])) {
			if(SP(sub.ts[i])->tt != TT_SEMICOLON) {
				knh_Token_perror(ctx, sub.ts[i-1], KERR_INFO, "needs ;");
			}
			sub.e = i;
			tc->c = i;
			knh_tokens_skipSEMICOLON(tc);
			return sub;
		}
	}
	sub.e = tc->e;
	tc->c = tc->e;
	return sub;
}

/* ------------------------------------------------------------------------ */

static
knh_tokens_t knh_tokens_splitEXPR(Ctx *ctx, knh_tokens_t *tc, knh_token_t tt)
{
	knh_tokens_t sub = *tc;
	int i;
	for(i = tc->c; i < tc->e; i++) {
		if(SP(sub.ts[i])->tt == tt) {
			sub.e =i;
			tc->c = i + 1;
			return sub;
		}
	}
	sub.e = i;
	tc->c = tc->e;
	return sub;
}

/* ------------------------------------------------------------------------ */

static
void knh_tokens_ignore(Ctx *ctx, knh_tokens_t *tc)
{
	if(tc->c < tc->e) {
		Token *tk = tc->ts[tc->c];
		knh_Token_perror(ctx, tk, KERR_DWARN, "ignored %s ..", sToken(tk));
		tc->c = tc->e;
	}
}

/* ------------------------------------------------------------------------ */

static Token* knh_tokens_curToken(knh_tokens_t *tc)
{
	int c = tc->c;
	while(!(c < tc->e)) {
		if(c == 0) break;
		c--;
	}
	tc->c = c + 1;
	return tc->ts[c];
}

/* ------------------------------------------------------------------------ */

static
void knh_Stmt_tokens_perror(Ctx *ctx, Stmt *o, knh_tokens_t *tc, char *fmt)
{
	Token *tk = knh_tokens_curToken(tc);
	knh_Token_perror(ctx, tk, KERR_ERROR, fmt, sToken(tk));
	knh_Stmt_add(ctx, o, TM(tk));
	if(SP(tk)->tt == TT_ERR) {
		knh_tokens_nextStmt(tc);
		KNH_ASSERT(SP(o)->stt == STT_ERR);
	}
}

/* ======================================================================== */
/* [COMMON TOKENS] */

/* namespace classname konoha.Class */

static knh_bool_t knh_Token_isNSCLASSN(Ctx *ctx, Token *tk)
{
	if(SP(tk)->tt == TT_NAME) {
		size_t i, prev = 0;
		knh_bytes_t t = knh_Token_tobytes(ctx, tk);
		for(i = 0; i < t.len; i++) {
			if(isupper(t.buf[i])) {
				if(prev == '.') return 1; else return 0;
			}
			if(islower(t.buf[i]) || isdigit(t.buf[i]) || t.buf[i] == '.') {
				prev = t.buf[i];
				continue;
			}
			return 0;
		}
		return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static void knh_Stmt_add_NSCLASSN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isNSCLASSN(ctx, tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_tokens_perror(ctx, o, tc, _("syntax error: %s"));
	}
}

/* ------------------------------------------------------------------------ */

static void knh_Stmt_add_TYPEN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isTYPEN(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_tokens_perror(ctx, o, tc, _("syntax error: %s"));
	}
}

/* ------------------------------------------------------------------------ */

static int  knh_Token_isCLASSN(Ctx *ctx, Token *tk)
{
	if(SP(tk)->tt == TT_TYPEN) {
		knh_bytes_t t = knh_Token_tobytes(ctx, tk);
		if(isupper(t.buf[0])) {
			size_t i;
			for(i = 0; i < t.len; i++) {
				if(t.buf[i] == ':') return 0;
			}
		}
		return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static void knh_Stmt_add_CLASSN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isCLASSN(ctx, tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_tokens_perror(ctx, o, tc, _("syntax error: %s"));
	}
}

/* ------------------------------------------------------------------------ */

static int knh_Token_isCLASSTN(Ctx *ctx, Token *tk)
{
	if(SP(tk)->tt == TT_TYPEN) {
		knh_bytes_t t = knh_Token_tobytes(ctx, tk);
		return isupper(t.buf[0]);
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static void knh_Stmt_add_CLASSTN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isCLASSTN(ctx, tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_tokens_perror(ctx, o, tc, _("syntax error: %s"));
	}
}

/* ------------------------------------------------------------------------ */

static int knh_Token_isPATH(Ctx *ctx, Token *tk)
{
	if(SP(tk)->tt == TT_URN) return 1;
	return knh_Token_isNSCLASSN(ctx, tk);
}

/* ------------------------------------------------------------------------ */

static void knh_Stmt_add_PATH(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isPATH(ctx, tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_tokens_perror(ctx, o, tc, _("syntax error: %s"));
	}
}

/* ------------------------------------------------------------------------ */

static int knh_Token_isVARN(Token *tk)
{
	if(SP(tk)->tt == TT_NAME) {
		size_t i;
		knh_bytes_t t = knh_String_tobytes(DP(tk)->text);
		for(i = 0; i < t.len; i++) {
			if(t.buf[i] == '.' || t.buf[i] == ':') return 0;
		}
		return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static void knh_Stmt_add_VARN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isVARN(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_tokens_perror(ctx, o, tc, _("syntax error: %s"));
	}
}

/* ======================================================================== */
/* [COMMONS STMT] */

static void knh_Stmt_add_ASIS(Ctx *ctx, Stmt *o)
{
	if(SP(o)->stt == STT_ERR) return;
	knh_Stmt_add(ctx, o, TM(new_TokenASIS(ctx, FL(o))));
}

/* ------------------------------------------------------------------------ */

static
void knh_Stmt_add_S(Ctx *ctx, Stmt *o, knh_token_t tt, String *ts)
{
	if(SP(o)->stt == STT_ERR) return;
	knh_Stmt_add(ctx, o, TM(new_Token__S(ctx, FL(o), tt, ts)));
}

/* ------------------------------------------------------------------------ */

static
void knh_Stmt_add_TYPEVARN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	Token **ts = tc->ts;
	if(SP(o)->stt == STT_ERR) return;

	if(tc->c < tc->e) {
		if(knh_Token_isVARN(ts[tc->c])) {
			knh_Stmt_add(ctx, o, TM(new_TokenASIS(ctx, FL(ts[tc->c]))));
			knh_Stmt_add(ctx, o, TM(ts[tc->c]));
			tc->c += 1;
			return;
		}
		if(knh_Token_isTYPEN(tc->ts[tc->c])) {
			knh_Stmt_add(ctx, o, TM(tc->ts[tc->c]));
			tc->c += 1;
			knh_Stmt_add_VARN(ctx, o, tc);
			return;
		}
	}
	knh_Stmt_tokens_perror(ctx, o, tc, _("syntax error: %s"));
}

/* ------------------------------------------------------------------------ */

static
void knh_Stmt_add_PARAMs(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && SP(tc->ts[tc->c])->tt != TT_PARENTHESIS) {
		knh_Stmt_tokens_perror(ctx, o, tc, _("syntax error: %s"));
	}
	knh_tokens_t param_tc;
	knh_Token_tc(ctx, tc->ts[tc->c], &param_tc); tc->c += 1;
	if(param_tc.c == param_tc.e) {
		knh_Stmt_add(ctx, o, TM(new_Stmt(ctx, 0, STT_DONE)));
		return;
	}

	Stmt *stmt = NULL;
	while(param_tc.c <param_tc.e) {
		Stmt *o2 = new_Stmt(ctx, 0, STT_DECL);
		knh_tokens_t ptc = knh_tokens_splitEXPR(ctx, &param_tc, TT_COMMA);
		if(SP(ptc.ts[ptc.c])->tt == TT_METAN) {
			ptc.meta = ptc.c;
			knh_Stmt_addMETA(ctx, o2, &ptc);
		}
		knh_Stmt_add_TYPEVARN(ctx, o2, &ptc);
		if(ptc.c + 1 < ptc.e && SP(ptc.ts[ptc.c])->tt == TT_LET) {
			ptc.c += 1;
			knh_Stmt_add(ctx, o2, new_TermEXPR(ctx, &ptc, 0));
		}
		else {
			knh_tokens_ignore(ctx, &ptc);
			knh_Stmt_add_ASIS(ctx, o2);
		}
		stmt =knh_StmtNULL_tail_append(ctx, stmt, o2);
	}
	knh_Stmt_add(ctx, o, TM(stmt));
	return;
}

/* ------------------------------------------------------------------------ */

static
void knh_Stmt_add_EXPR(Ctx *ctx, Stmt *stmt, knh_tokens_t *tc, int level)
{
	knh_tokens_t expr_tc = knh_tokens_splitSTMT(ctx, tc);
	if(expr_tc.c < expr_tc.e) {
		knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, &expr_tc, level));
	}
	else {
		KNH_ASSERT(expr_tc.e > 0);
		Token *tk = tc->ts[expr_tc.e-1];
		knh_Token_perror(ctx, tk, KERR_ERROR, _("no expression"));
		SP(stmt)->stt = STT_ERR;
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_Stmt_add_EXPRs(Ctx *ctx, Stmt *stmt_b, knh_tokens_t *tc, int level)
{
	knh_tokens_t expr_tc = knh_tokens_splitSTMT(ctx, tc);
	while(expr_tc.c < expr_tc.e) {
		knh_tokens_t sub_tc = knh_tokens_splitEXPR(ctx, &expr_tc, TT_COMMA);
		if(sub_tc.c < sub_tc.e) {
			knh_Stmt_add(ctx, stmt_b, new_TermEXPR(ctx, &sub_tc, level));
		}
	}
}

/* ======================================================================== */
/* [VALUE] */

static Stmt *new_StmtERR(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *stmt = new_Stmt(ctx, 0, STT_DONE);
	knh_Stmt_toERR(ctx, stmt, TM(knh_tokens_curToken(tc)));
	knh_tokens_nextStmt(tc);
	return stmt;
}

/* ------------------------------------------------------------------------ */

static Stmt *new_StmtNullData(Ctx *ctx, Token *tk)
{
	Stmt *stmt = new_Stmt(ctx, 0, STT_CALL1);
	knh_Token_setCONST(ctx, tk, KNH_NULL);
	knh_Stmt_add(ctx, stmt, TM(tk));
	return stmt;
}

/* ======================================================================== */
/* [VALUE] */

static Stmt *new_Stmt__stmt(Ctx *ctx, Stmt *o)
{
	Stmt *stmt = new_Stmt(ctx, 0, STT_CALL);
	knh_Stmt_add(ctx, stmt, TM(o));
	return stmt;
}

/* ======================================================================== */
/* [NAME] */

static Token *new_TokenTHIS(Ctx *ctx, Token *tk)
{
	return new_TokenASIS(ctx, FL(tk));
}

/* ------------------------------------------------------------------------ */

static
Token *new_TokenFUNCNAME(Ctx *ctx, Token *tk, knh_bytes_t name, int isfunc)
{
	if(!isfunc) {
		knh_fieldn_t fn = knh_tName_get_fnq(ctx, name, FIELDN_NEWID);
		Token *tkfunc = new_TokenFN(ctx, FL(tk), fn);
		knh_Token_setGetter(tkfunc, 1);
		knh_Token_setTopDot(tkfunc, 1);
		return tkfunc;
	}
	else {
		knh_methodn_t mn = konoha_getMethodName(ctx, name, METHODN_NEWID);
		Token *tkfunc = new_TokenMN(ctx, FL(tk), mn);
		knh_Token_setTopDot(tkfunc, 1);
		return tkfunc;
	}
}

/* ------------------------------------------------------------------------ */

static
Token *new_TokenVARN(Ctx *ctx, Token *tk, knh_bytes_t name)
{
	knh_fieldn_t fn = knh_tName_get_fnq(ctx, name, FIELDN_NEWID);
	return new_TokenFN(ctx, FL(tk), fn);
}

/* ------------------------------------------------------------------------ */

static int knh_bytes_isCLASSN(knh_bytes_t t)
{
	size_t i;
	if(!isupper(t.buf[0])) return 0;
	for(i = 1; i < t.len; i++) {
		if(!isalnum(t.buf[i])) return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

static
Token *new_TokenCLASSN(Ctx *ctx, Token *tk, knh_bytes_t name)
{
	knh_NameSpace_t *ns = knh_Context_getNameSpace(ctx);
	return new_Token__S(ctx, FL(tk), TT_TYPEN, new_String__DictSet(ctx, DP(ns)->name2cidDictSet, name));
}

/* ------------------------------------------------------------------------ */

static int knh_bytes_isCONSTN(knh_bytes_t t)
{
	knh_index_t loc = knh_bytes_rindex(t, '.');
	if(loc == -1 || !knh_bytes_isCLASSN(knh_bytes_first(t, loc))) return 0;
	t = knh_bytes_last(t,loc+1);
	size_t i;
	if(!isupper(t.buf[0])) return 0;
	for(i = 1; i < t.len; i++) {
		if(!isupper(t.buf[i]) && !isdigit(t.buf[i]) && t.buf[i] != '_') return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

static Token *new_TokenCONSTN(Ctx *ctx, Token *tk, knh_bytes_t name)
{
	return new_Token__S(ctx, FL(tk), TT_CONSTN, new_String(ctx, name, NULL));
}

/* ------------------------------------------------------------------------ */

static
void knh_Stmt_add_FIRSTNAME(Ctx *ctx, Stmt *stmt, Token *tk, knh_bytes_t name)
{
	knh_index_t idx = knh_bytes_rindex(name, '.');
	knh_bool_t isfunc = (DP(tk)->tt_next == TT_PARENTHESIS) ? 1 : 0;
	KNH_ASSERT(DP(stmt)->size == 0);
	KNH_ASSERT(idx != -1);

	L_NAMEDIV:;
	{
		knh_bytes_t fname = knh_bytes_first(name, idx);
		knh_bytes_t lname = knh_bytes_last(name,  idx+1);

		knh_Stmt_add(ctx, stmt, TM(new_TokenFUNCNAME(ctx, tk, lname, isfunc)));

		//DEBUG("**1 idx=%d, len=%d", (int)idx, fn.len);
		idx = knh_bytes_rindex(fname, '.');
		if(idx == -1) {
			if(knh_bytes_isCLASSN(fname)) {
				knh_Stmt_add(ctx, stmt, TM(new_TokenCLASSN(ctx, tk, fname)));
			}
			else if(knh_bytes_isCONSTN(fname)) {
				knh_Stmt_add(ctx, stmt, TM(new_TokenCONSTN(ctx, tk, fname)));
			}
			else {
				knh_Stmt_add(ctx, stmt, TM(new_TokenVARN(ctx, tk, fname)));
			}
			return;
		}
		else {
			Stmt *stmt_in = new_Stmt(ctx, 0, STT_CALL);
			knh_Stmt_add(ctx, stmt, TM(stmt_in));
			stmt = stmt_in;
			isfunc = 0;
			name = fname;
		}
		goto L_NAMEDIV;
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_Stmt_swap01(Stmt *stmt)
{
	KNH_ASSERT(DP(stmt)->size > 1);
	Term *temp = DP(stmt)->terms[0];
	DP(stmt)->terms[0] = DP(stmt)->terms[1];
	DP(stmt)->terms[1] = temp;
}

/* ------------------------------------------------------------------------ */

static
Stmt* knh_Stmt_add_SECONDNAME(Ctx *ctx, Stmt *stmt, Token *tk)
{
	KNH_ASSERT(SP(tk)->tt == TT_NAME);
	KNH_ASSERT(DP(stmt)->size == 1);
	{
		Stmt *stmt_head = stmt;
		knh_bytes_t name = knh_Token_tobytes(ctx, tk);
		knh_index_t idx = knh_bytes_index(name, '.');
		while(idx > 0) {
			knh_Stmt_add(ctx, stmt_head, TM(new_TokenFUNCNAME(ctx, tk, knh_bytes_first(name, idx), 0)));
			knh_Stmt_swap01(stmt_head);
			stmt_head = new_Stmt__stmt(ctx, stmt_head);
			name = knh_bytes_last(name, idx+1);
			idx = knh_bytes_index(name, '.');
		}
		knh_Stmt_add(ctx, stmt_head, TM(new_TokenFUNCNAME(ctx, tk, name, DP(tk)->tt_next == TT_PARENTHESIS)));
		knh_Stmt_swap01(stmt_head);
		return stmt_head;
	}
}

/* ------------------------------------------------------------------------ */

static Term *new_TermNAME(Ctx *ctx, Token *tk)
{
	KNH_ASSERT(SP(tk)->tt == TT_NAME);
	{
		knh_bytes_t t = knh_Token_tobytes(ctx, tk);
		if(knh_bytes_rindex(t, '.') == -1) {
			return TM(tk);
		}
		else {
			Stmt* stmt = new_Stmt(ctx, 0, STT_CALL);
			knh_Stmt_add_FIRSTNAME(ctx, stmt, tk, t);
			return TM(stmt);
		}
	}
}

/* ------------------------------------------------------------------------ */

static
Stmt *new_StmtNAME1(Ctx *ctx, Token *tk)
{
	KNH_ASSERT(SP(tk)->tt == TT_NAME);
	{
		knh_bytes_t t = knh_Token_tobytes(ctx, tk);
		if(knh_bytes_rindex(t, '.') == -1) {
			Stmt *stmt = new_Stmt(ctx, 0, STT_CALL);
			knh_Stmt_add(ctx, stmt, TM(tk));
			return stmt;
		}
		else {
			Stmt* stmt = new_Stmt(ctx, 0, STT_CALL);
			knh_Stmt_add_FIRSTNAME(ctx, stmt, tk, t);
			return new_Stmt__stmt(ctx, stmt);
		}
	}
}

/* ------------------------------------------------------------------------ */

static
Stmt *new_StmtNAME2(Ctx *ctx, Token *tk)
{
	DBG2_ASSERT(SP(tk)->tt == TT_NAME || SP(tk)->tt == TT_CMETHODN);
	knh_bytes_t t = knh_Token_tobytes(ctx, tk);
	if(knh_bytes_rindex(t, '.') == -1) {
		Stmt *stmt = new_Stmt(ctx, 0, STT_CALL);
		knh_Stmt_add(ctx, stmt, TM(tk));
		knh_Stmt_add(ctx, stmt, TM(new_TokenTHIS(ctx, tk)));
		return stmt;
	}
	else {
		Stmt* stmt = new_Stmt(ctx, 0, STT_CALL);
		knh_Stmt_add_FIRSTNAME(ctx, stmt, tk, t);
		return stmt;
	}
}

/* ======================================================================== */
/* [list] */

static
Term *new_TermTUPLE(Ctx *ctx, Token *tk, int isData)
{
	knh_tokens_t tc;
	knh_Token_tc(ctx, tk, &tc);
	int c = knh_tokens_count(&tc, TT_COMMA);
	if(tc.e == 0) {
		return TM(new_TokenCONST(ctx, FL(tk), KNH_NULL));
	}
	if(c == 0) {
		return new_TermEXPR(ctx, &tc, isData);
	}
	else {
		Stmt *stmt = new_Stmt(ctx, KNH_FLAG_STMTF_LITERAL, STT_NEW);
		Token *tk_new = new_TokenMN(ctx, FL(tk), METHODN_new__init);
		knh_Stmt_add(ctx, stmt, TM(tk_new));
		knh_Stmt_add(ctx, stmt, TM(tk_new) /* DUMMY new_Token__T(ctx, tk, STEXT("Tuple"))*/);
		knh_Stmt_add_EXPRs(ctx, stmt, &tc, isData);
		c = DP(stmt)->size - 2;
		if(c == 2) {
			KNH_SETv(ctx, DP(stmt)->terms[1], new_TokenCID(ctx, FL(tk), CLASS_Tuple2));
		}
#ifdef CLASS_Triple
		else if(c == 3){
			KNH_SETv(ctx, DP(stmt)->terms[1], new_TokenCID(ctx, FL(tk), CLASS_Triple));
		}
#endif
		else {
			KNH_SETv(ctx, DP(stmt)->terms[1], new_TokenCID(ctx, FL(tk), CLASS_Array));
		}
		return TM(stmt);
	}
}

/* ------------------------------------------------------------------------ */

static Token *knh_tokens_findIDXNULL(knh_tokens_t *tc)
{
	int i;
	for(i = tc->c; i < tc->e; i++) {
		knh_token_t tt = SP(tc->ts[i])->tt;
		//KNH_ASSERT(!knh_Token_isBOL(tc->ts[i]));
		if(tt == TT_SUBSETE || tt == TT_OFFSET || tt == TT_SUBSET) {
			return tc->ts[i];
		}
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
Term *new_TermARRAY(Ctx *ctx, Token *tk, int isData)
{
	knh_tokens_t tc;
	knh_Token_tc(ctx, tk, &tc);
	Stmt *stmt = new_Stmt(ctx, KNH_FLAG_STMTF_LITERAL, STT_NEW);
	knh_Stmt_add(ctx, stmt, TM(new_TokenMN(ctx, FL(tk), METHODN_new__init)));
	knh_Stmt_add(ctx, stmt, TM(new_TokenCID(ctx, FL(tk), CLASS_Array)));
	knh_Stmt_add_EXPRs(ctx, stmt, &tc, isData);
	return TM(stmt);
}

/* ======================================================================== */

static
void knh_Stmt_add_IDX(Ctx *ctx, Stmt *stmt, Token *tkb)
{
	KNH_ASSERT(SP(tkb)->tt == TT_BRANCET);
	knh_tokens_t tc;

	Token *tkidx = NULL;
	knh_Token_tc(ctx, tkb, &tc);
	if(tc.e == 0) {
		knh_Stmt_add(ctx, stmt, TM(new_TokenMN(ctx, FL(tkb), METHODN_setAll)));
		knh_Stmt_swap01(stmt);
		return ;
	}
	if((tkidx = knh_tokens_findIDXNULL(&tc)) == NULL) {
		knh_Stmt_add(ctx, stmt, TM(new_TokenMN(ctx, FL(tkb), METHODN_get)));
		knh_Stmt_swap01(stmt);
		knh_Stmt_add_EXPRs(ctx, stmt, &tc, /*isData*/0);
#if defined(METHODN_set2D)
		if(DP(stmt)->size == 4) {
			DP(DP(stmt)->tokens[0])->mn = METHODN_get2D;
		}
		else if(DP(stmt)->size == 5){
			DP(DP(stmt)->tokens[0])->mn = METHODN_get3D;
		}
#endif
	}
	else {
		knh_tokens_t first_tc = knh_tokens_splitEXPR(ctx, &tc, SP(tkidx)->tt);
		if(SP(tkidx)->tt == TT_SUBSETE) {
			knh_Stmt_add(ctx, stmt, TM(new_TokenMN(ctx, FL(tkb), METHODN_opSubsete)));
		}
		else if(SP(tkidx)->tt == TT_OFFSET) {
			knh_Stmt_add(ctx, stmt, TM(new_TokenMN(ctx, FL(tkb), METHODN_opOffset)));
		}
		else {
			knh_Stmt_add(ctx, stmt, TM(new_TokenMN(ctx, FL(tkb), METHODN_opSubset)));
		}
		knh_Stmt_swap01(stmt);
		if(first_tc.c == first_tc.e) {
			knh_Stmt_add(ctx, stmt, TM(new_TokenCONST(ctx, FL(tkidx), KNH_NULL)));
		}
		else {
			knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, &first_tc, /*isData*/0));
		}
		if(tc.c == tc.e) {
			knh_Stmt_add(ctx, stmt, TM(new_TokenCONST(ctx, FL(tkidx), KNH_NULL)));
		}
		else {
			knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, &tc, /*isData*/0));
		}
	}
	knh_Token_tokens_empty(ctx, tkb);
}

/* ======================================================================== */
/* [DictMap] */

static
void knh_tokens_toArray(Ctx *ctx, knh_tokens_t *tc, Array *a, int ignoreCOMMA)
{
	int i;
	Token **ts = tc->ts;
	for(i = tc->c; i < tc->e; i++) {
		if(ignoreCOMMA && SP(ts[i])->tt == TT_COMMA) continue;
		if(SP(ts[i])->tt == TT_PARENTHESIS) {
			knh_tokens_t intc;
			knh_Array_add(ctx, a, UP(TS_LP));
			knh_Token_tc(ctx, ts[i], &intc);
			knh_tokens_toArray(ctx, &intc, a, 0);
			knh_Array_add(ctx, a, UP(TS_RP));
		}
		else if(SP(ts[i])->tt == TT_BRACE) {
			knh_tokens_t intc;
			knh_Array_add(ctx, a, UP(TS_LB));
			knh_Token_tc(ctx, ts[i], &intc);
			knh_tokens_toArray(ctx, &intc, a, 0);
			knh_Array_add(ctx, a, UP(TS_RB));
		}
		else if(SP(ts[i])->tt == TT_BRANCET) {
			knh_tokens_t intc;
			knh_Array_add(ctx, a, UP(TS_LS));
			knh_Token_tc(ctx, ts[i], &intc);
			knh_tokens_toArray(ctx, &intc, a, 0);
			knh_Array_add(ctx, a, UP(TS_RS));
		}
		else if(IS_bString(DP(ts[i])->data)) {
			knh_Array_add(ctx, a, DP(ts[i])->data);
		}
		else {
			knh_Array_add(ctx, a, UP(new_String(ctx, knh_Token_tobytes(ctx, ts[i]), NULL)));
		}
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_Stmt_add_PAIR(Ctx *ctx, Stmt *stmt, knh_tokens_t *tc, int isData)
{
	int s = tc->c;
	Token **ts = tc->ts;
	if(tc->c < tc->e && (SP(ts[tc->e - 1])->tt == TT_COMMA || SP(ts[tc->e - 1])->tt == TT_SEMICOLON)) {
		tc->e -= 1;
	}

	if(!(tc->c < tc->e)) {
		if(!isData) {
			knh_perror(ctx, SP(stmt)->fileid, SP(stmt)->line, KERR_DWARN, _("empty"));
		}
		return;
	}

	if(SP(ts[s])->tt == TT_LABEL) {
		knh_Stmt_add(ctx, stmt, TM(knh_Token_toCONST(ctx, ts[s])));
		s = tc->c + 1;
	}
	else if(DP(ts[s])->tt_next == TT_COLON) {
		knh_Stmt_add(ctx, stmt, TM(knh_Token_toCONST(ctx, ts[s])));
		s = tc->c + 2;
	}
	else {
		if(!isData) {
			knh_perror(ctx, SP(stmt)->fileid, SP(stmt)->line, KERR_DWARN, _("empty"));
		}
		return;
	}

	//fprintf(stderr, "VALUE s=%d, e=%d\n", s, tc->e);
	if(s == tc->e) {
		if(!isData) {
			knh_perror(ctx, SP(stmt)->fileid, SP(stmt)->line, KERR_ERRATA, _("empty: ==> null"));
		}
		knh_Stmt_add(ctx, stmt, TM(new_TokenCONST(ctx, UP(ts[s]), KNH_NULL)));
		return;
	}

	if(s + 1 == tc->e) {
		knh_token_t tt = SP(ts[s])->tt;
		if(tt == TT_NUM || tt == TT_BRACE || tt == TT_BRANCET || tt == TT_PARENTHESIS) {
			tc->c = s;
			tc->e = tc->e;
			knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, tc, isData));
			return ;
		}
		if(!IS_bString(DP(ts[s])->data)) {
			KNH_SETv(ctx, DP(ts[s])->data, new_String(ctx, knh_Token_tobytes(ctx, ts[s]), NULL));
		}
		knh_Stmt_add(ctx, stmt, TM(knh_Token_toCONST(ctx, ts[s])));
		return;
	}

	/* friend: Person {} */
	if(s + 2 == tc->e && SP(ts[s])->tt == TT_TYPEN && DP(ts[s])->tt_next == TT_BRACE) {
		tc->c = s;
		tc->e = s + 2;
		knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, tc, isData));
		return ;
	}

	int i, allnum = 1;
	for(i = s; i < tc->e; i++) {
		if(SP(ts[i])->tt == TT_COMMA) continue;
		if(SP(ts[i])->tt != TT_NUM) {
			allnum = 0;
			break;
		}
	}
	if(allnum) { /* size: 10pt 20pt */
		knh_tokens_t numtc = *tc;
		Stmt *newstmt = new_Stmt(ctx, 0, STT_NEW);
		knh_Stmt_add(ctx, newstmt, TM(new_TokenMN(ctx, FL(stmt), METHODN_new__init)));
		knh_Stmt_add(ctx, newstmt, TM(new_TokenCID(ctx, FL(stmt), CLASS_Array)));
		for(i = s; i < tc->e; i++) {
			if(SP(ts[i])->tt == TT_COMMA) continue;
			if(SP(ts[i])->tt == TT_NUM) {
				numtc.c = i; numtc.e = i + 1;
				knh_Stmt_add(ctx, newstmt, new_TermEXPR(ctx, &numtc, isData));
			}
		}
		knh_Stmt_add(ctx, stmt, TM(newstmt));
		return;
	}
	else {  /* func: int func(int n); */
		Array *a = new_Array(ctx, CLASS_String, 0);
		knh_Stmt_add(ctx, stmt, TM(new_TokenCONST(ctx, FL(stmt), UP(a))));
		tc->c = s;
		knh_tokens_toArray(ctx, tc, a, 1);
	}
}

/* ------------------------------------------------------------------------ */

static
Term *new_TermDICTMAP(Ctx *ctx, Token *ctk, Token *tk, int isData)
{
	knh_tokens_t tc;
	knh_Token_tc(ctx, tk, &tc);
	Stmt *stmt = new_Stmt(ctx, KNH_FLAG_STMTF_LITERAL, STT_NEW);
	knh_Stmt_add(ctx, stmt, TM(new_TokenMN(ctx, FL(tk), METHODN_new__init)));
	if(IS_NULL(ctk)) {
		knh_Stmt_add(ctx, stmt, TM(new_TokenCID(ctx, FL(tk), CLASS_DictMap)));
	}
	else {
		knh_Stmt_add(ctx, stmt, TM(ctk));
	}

	int i;
	knh_tokens_t pair_tc = tc;
	for(i = 1; i < tc.e; i++) {
		if(SP(tc.ts[i])->tt == TT_LABEL) {
			pair_tc.e = i;
			knh_Stmt_add_PAIR(ctx, stmt, &pair_tc, isData);
			pair_tc.c = i;
			continue;
		}
		if(DP(tc.ts[i])->tt_next == TT_COLON &&
			(SP(tc.ts[i])->tt == TT_STR || SP(tc.ts[i])->tt == TT_TSTR || SP(tc.ts[i])->tt == TT_NUM)) {
			pair_tc.e = i;
			knh_Stmt_add_PAIR(ctx, stmt, &pair_tc, isData);
			pair_tc.c = i;
		}
	}
	if(tc.c + 1 < tc.e) {
		pair_tc.e = tc.e;
		knh_Stmt_add_PAIR(ctx, stmt, &pair_tc, isData);
	}
	return TM(stmt);
}

/* ======================================================================== */
/* [PROPN] */

static
Term* new_TermPROPN(Ctx *ctx, Token *tk, int isData)
{
	if(isData) {
		knh_Token_setCONST(ctx, tk, KNH_NULL);
		return TM(tk);
	}
	else {
		Stmt *stmt = new_Stmt(ctx, 0, STT_CALL);
		KNH_ASSERT(IS_String(DP(tk)->text));
		if(knh_bytes_index(knh_String_tobytes(DP(tk)->text), '*') > 0) {
			knh_Stmt_add(ctx, stmt, TM(new_TokenMN(ctx, FL(tk), METHODN_listProperties)));
		}
		else {
			knh_Stmt_add(ctx, stmt, TM(new_TokenMN(ctx, FL(tk), METHODN_getProperty)));
		}
		knh_Stmt_add(ctx, stmt, TM(new_TokenCID(ctx, FL(tk), CLASS_Context)));
		knh_Token_toCONST(ctx, tk);
		knh_Stmt_add(ctx, stmt, TM(tk));
		return TM(stmt);
	}
}

/* ======================================================================== */
/* [VALUE] */

static
Term *new_TermVALUE(Ctx *ctx, Token *tk, int isData)
{
	switch(SP(tk)->tt) {
		case TT_NAME:
		{
			knh_bytes_t t = knh_Token_tobytes(ctx, tk);
			if(ISB(t, "null")) {
				knh_Token_setCONST(ctx, tk, KNH_NULL);
				return TM(tk);
			}
			else if(ISB(t, "true")) {
				knh_Token_setCONST(ctx, tk, KNH_TRUE);
				return TM(tk);
			}
			else if(ISB(t, "false")) {
				knh_Token_setCONST(ctx, tk, KNH_FALSE);
				return TM(tk);
			}
			if(isData) {
				knh_Token_toCONST(ctx, tk);
				return TM(tk);
			}
			else {
				return new_TermNAME(ctx, tk);
			}
		}
		case TT_PARENTHESIS:
			return new_TermTUPLE(ctx, tk, isData);
		case TT_BRANCET:
			return new_TermARRAY(ctx, tk, isData);
		case TT_BRACE:
			return new_TermDICTMAP(ctx, (Token*)KNH_NULL, tk, isData);
		case TT_PROPN:
			return new_TermPROPN(ctx, tk, isData);
		case TT_ESTR:
		case TT_STR:
		case TT_NUM:
		case TT_TSTR:
		case TT_URN:
		case TT_TYPEN:
		case TT_CONSTN:
		case TT_CMETHODN:
		case TT_ERR:
			return TM(tk);
	}
	if(!isData) {
		knh_Token_perror(ctx, tk, KERR_ERROR, _("unknown token"), sToken(tk));
	}
	return TM(tk);
}

/* ======================================================================== */
/* [STMT] */

Stmt *new_StmtINSTMT(Ctx *ctx, Token *tk)
{
	DBG2_ASSERT(SP(tk)->tt == TT_BRACE);

	knh_tokens_t tc;
	knh_Token_tc(ctx, tk, &tc);
	Stmt *first_stmt = NULL, *last_stmt = NULL;
	int prev = 0;

	while(tc.c < tc.e) {
		//DBG2_P("S c = %d, e = %d", (int)tc.c, (int)tc.e);
		if(SP(tc.ts[tc.c])->tt == TT_SEMICOLON) {
			tc.c += 1;
			continue;
		}
		prev = tc.c;
		if(first_stmt == NULL) {
			first_stmt = new_StmtSTMT1(ctx, &tc);
			last_stmt = knh_Stmt_tail(ctx, first_stmt);
		}
		else {
			KNH_SETv(ctx, DP(last_stmt)->next, new_StmtSTMT1(ctx, &tc));
			last_stmt = knh_Stmt_tail(ctx, DP(last_stmt)->next);
		}
		if(prev == tc.c) { /* infinate loop */
			DBG_P("Infinate loop? prev = %d, c = %d, e = %d", prev, tc.c, tc.e);
			KNH_ABORT();
			break;
		}
	}
	if(first_stmt == NULL) {
		first_stmt = new_Stmt(ctx, 0, STT_DONE);
	}
	return first_stmt;
}

/* ======================================================================== */
/* [EXPR] */

static
Term *new_TermPEXPR(Ctx *ctx, Token *tk, int isData)
{
	DBG2_ASSERT(SP(tk)->tt == TT_PARENTHESIS);
	{
		knh_tokens_t p_tc;
		knh_Token_tc(ctx, tk, &p_tc);
		if(p_tc.e == 0) {
			if(!isData) {
				knh_Token_perror(ctx, tk, KERR_ERRATA, _("empty: () ==> false"));
			}
			return TM(new_TokenCONST(ctx, FL(tk), KNH_FALSE));
		}
		return new_TermEXPR(ctx, &p_tc, isData);
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_Stmt_add_PEXPR(Ctx *ctx, Stmt *stmt, knh_tokens_t *tc)
{
	if(SP(stmt)->stt == STT_ERR) return;
	if(tc->c < tc->e) {
		if(SP(tc->ts[tc->c])->tt == TT_WHILE) {
			tc->c += 1;  /* @ADHOC do {} while() */
		}
	}
	if(tc->c < tc->e) {
		if(SP(tc->ts[tc->c])->tt == TT_PARENTHESIS) {
			knh_Stmt_add(ctx, stmt, new_TermPEXPR(ctx, tc->ts[tc->c], 0/*isData*/));
			tc->c += 1;
			return ;
		}
	}
	knh_Stmt_tokens_perror(ctx, stmt, tc, _("syntax error"));
}

/* ======================================================================== */
/* [OP] */

static int knh_tokens_findOPR(Ctx *ctx, knh_tokens_t *tc, int isData)
{
	int i, oppri = 98, idx = -1;
	Token **ts = tc->ts;
	for(i = tc->c; i < tc->e; i++) {
		int p = knh_token_getOpPriority(SP(ts[i])->tt);
		if(p == 0) {
			if(SP(ts[i])->tt != TT_DOTS) {
				if(!isData) {
					knh_Token_perror(ctx, ts[i], KERR_ERROR, _("unexpected token: %s"), sToken(ts[i]));
				}
				return i;
			}
			tc->e = i;
			break;
		}
		if(p <= oppri) {
			oppri = p;
			idx = i;
		}
	}
	return idx;
}

/* ------------------------------------------------------------------------ */

static
Stmt *new_StmtNEXT(Ctx *ctx, Token *op, knh_tokens_t *tc)
{
	Stmt *stmt = new_Stmt(ctx, 0, STT_CALL);
	if(SP(op)->tt == TT_NEXT) {
		knh_Stmt_add(ctx, stmt, TM(new_TokenMN(ctx, FL(op), METHODN_opNext)));
	}
	else {
		knh_Stmt_add(ctx, stmt, TM(new_TokenMN(ctx, FL(op), METHODN_opPrev)));
	}
	knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, tc, 0/*isData*/));
	return stmt;
}

/* ------------------------------------------------------------------------ */

static
Term *new_TermOPR(Ctx *ctx, knh_tokens_t *tc, Token *op)
{
	/* $expr ? $expr : $expr */
	if(SP(op)->tt == TT_QUESTION) {
		Stmt *stmt = new_Stmt(ctx, 0, STT_TRI);
		knh_tokens_t expr_tc = knh_tokens_splitEXPR(ctx, tc, SP(op)->tt);
		knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, &expr_tc, 0/*isData*/));
		expr_tc = knh_tokens_splitEXPR(ctx, tc, TT_COLON);
		if(expr_tc.c < expr_tc.e && tc->c < tc-> e) {
			knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, &expr_tc, 0/*isData*/));
			knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, tc, 0/*isData*/));
		}
		else {
			knh_Stmt_tokens_perror(ctx, stmt, &expr_tc, _("syntax error"));
		}
		return TM(stmt);
	}
	else if(SP(op)->tt == TT_NEXT || SP(op)->tt == TT_PREV) {
		if(tc->ts[tc->c] == op) {
			knh_Token_perror(ctx, op, KERR_DWARN, _("unsupported C/C++ grammer fully"), sToken(op));
			tc->c += 1;
		}
		knh_tokens_t ltc = knh_tokens_splitEXPR(ctx, tc, SP(op)->tt);
		knh_tokens_t rtc = ltc;
		{
			Term *lval = new_TermEXPR(ctx, &ltc, 0/*isData*/);
			if(IS_Token(lval)) {
				if(knh_Token_isLVALUE(ctx, (Token*)lval)) {
					Stmt *stmt = new_Stmt(ctx, 0, STT_LET);
					knh_Stmt_add(ctx, stmt, lval);
					knh_Stmt_add(ctx, stmt, TM(new_StmtNEXT(ctx, op, &rtc)));
					return TM(stmt);
				}
				else {
					knh_Token_perror(ctx, op, KERR_ERROR, _("cannot use %s for this expression"), sToken(op));
					return TM(new_StmtERR(ctx, &ltc));
				}
			}
			else {
				Stmt *stmt = (Stmt*)lval;
				KNH_ASSERT(IS_Stmt(stmt));
				knh_Stmt_toLVALUE(ctx, stmt, KERR_ERROR, _("cannot use %s for this expression"));
				if(SP(stmt)->stt != STT_ERR) {
					knh_Stmt_add(ctx, stmt, TM(new_StmtNEXT(ctx, op, &rtc)));
				}
				return TM(stmt);
			}
		}
	}
	else {
		knh_stmt_t stt = STT_OP;
		switch(SP(op)->tt) {
			case TT_AND: stt = STT_AND; break;
			case TT_OR:  stt = STT_OR; break;
			case TT_ALT: stt = STT_ALT; break;
		}
		Stmt *stmt;
		if(SP(tc->ts[tc->c])->tt == SP(op)->tt) {
			stmt = new_Stmt(ctx, KNH_FLAG_STMTF_ADPOSITION, stt);
			tc->c += 1;
		}
		else{
			stmt = new_Stmt(ctx, 0, stt);
		}

		if(stt == STT_OP) {
			knh_Stmt_add(ctx, stmt, TM(op));
		}
		while(tc->c < tc->e) {
			knh_tokens_t op_tc = knh_tokens_splitEXPR(ctx, tc, SP(op)->tt);
			knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, &op_tc, 0/*isData*/));
		}
		return TM(stmt);
	}
}

/* ======================================================================== */
/* [CAST] */

static Token *knh_Token_findCASTNULL(Ctx *ctx, Token *tk, Token *ntk, int isData)
{
	if(SP(tk)->tt == TT_PARENTHESIS && !knh_Token_isTopDot(ntk)) {
		knh_tokens_t tc;
		knh_Token_tc(ctx, tk, &tc);
		if(tc.e == 0) return NULL;
		if((tc.e > 2 && (tc.ts[1])->tt != TT_WITH)  || tc.e == 2) {
			if(!isData) {
				knh_Token_perror(ctx, tc.ts[1], KERR_ERROR, _("syntax error"));
			}
			SP(tk)->tt = TT_ERR;
			return NULL;
		}
		if(SP(tc.ts[0])->tt == TT_MUL) {
			SP(tc.ts[0])->tt = TT_CID;
			DP(tc.ts[0])->cid = CLASS_Any;
			return tk; //tc.ts[0];
		}
		if(knh_Token_isTYPEN(tc.ts[0])) {
			return tk; //tc.ts[0];
		}
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
Term *new_TermCAST(Ctx *ctx, Token *tk, knh_tokens_t *tc, int isData)
{
	Stmt *stmt = new_Stmt(ctx, 0, STT_MAPCAST);
	KNH_ASSERT(SP(tk)->tt == TT_PARENTHESIS);
	knh_tokens_t ctc;
	knh_Token_tc(ctx, tk, &ctc);
	knh_Stmt_add(ctx, stmt, TM(ctc.ts[0]));
	knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, tc, isData));
	if(ctc.e > 2) {
		KNH_ASSERT((ctc.ts[1])->tt == TT_WITH);
		ctc.c = 2;
		knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, &ctc, isData));
	}
	return TM(stmt);
}

/* ------------------------------------------------------------------------ */

static int knh_Token_isNEW(Ctx *ctx, Token *tk)
{
	if(SP(tk)->tt == TT_NAME) {
		char *p = sToken(tk);
		return (p[0]=='n' && p[1] == 'e' && p[2] == 'w' && (p[3]==0 || p[3]==':'));
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static Term *new_TermEXPR(Ctx *ctx, knh_tokens_t *tc, int isData)
{
	Token **ts = tc->ts;
	int oc = tc->c, e = tc->e;
	int fc = 0, pc = 0;
	Stmt *stmt = NULL;
//	DBG2_P("tt='%s'[%d] .. tt='%s'[%d]",
//			knh_token_tochar(ts[oc]->tt), oc, knh_token_tochar(ts[e-1]->tt), e-1);
	if(!(oc < e)) {
		DBG2_P("tc->c=%d, tc->e=%d", (int)oc, (int)e);
		DBG2_ASSERT(oc < e);
		Token *tke = new_Token(ctx, 0, SP(tc->ts[e-1])->fileid, SP(tc->ts[e-1])->line, TT_ERR);
		if(!isData) {
			knh_perror(ctx, SP(tc->ts[e-1])->fileid, SP(tc->ts[e-1])->line, KERR_ERROR, _("syntax error"));
		}
		return TM(tke);
	}

	if (oc + 1 == e) {
		return new_TermVALUE(ctx, ts[oc], isData);
	}

	if(SP(ts[oc])->tt == TT_SUB) {
		SP(ts[oc])->tt = TT_NEG;
	}

	for(pc = oc; pc < e; pc++) {
		if(SP(ts[pc])->tt == TT_ERR) {
			knh_tokens_ignore(ctx, tc);
			tc->c = tc->e;
			return TM(ts[pc]);
		}
	}

	pc = 0;
	{
		knh_token_t tt0 = SP(ts[oc])->tt, tt1 = DP(ts[oc])->tt_next;
		/* @TEST a.f "text" + 1 */
		if(tt0 == TT_NAME || tt0 == TT_CMETHODN || tt0 == TT_CONSTN || tt0 == TT_TYPEN) {
			if(tt1 == TT_STR || tt1 == TT_TSTR || tt1 == TT_ESTR) {
				DP(ts[oc])->tt_next = TT_PARENTHESIS; // needed
				if(tt0 == TT_CONSTN || tt0 == TT_TYPEN) SP(ts[oc])->tt = TT_NAME;
				stmt = new_StmtNAME2(ctx, ts[oc]);
				tc->c = oc + 1;
				knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, tc, isData));
				return TM(stmt);
			}
		}
		/* @TEXT (a).f "text" + 1 */
		if(tt0 == TT_PARENTHESIS
				&& (tt1 == TT_NAME || tt1 == TT_CONSTN || tt1 == TT_TYPEN)
				&& knh_Token_isTopDot(ts[oc+1])) {
			knh_token_t tt2 = DP(ts[oc+1])->tt_next;
			if(tt2 == TT_STR || tt2 == TT_TSTR || tt2 == TT_TSTR) {
				DP(ts[oc])->tt_next = TT_PARENTHESIS;
				stmt = new_Stmt(ctx, 0, STT_CALL);
				if(tt1 == TT_CONSTN || tt1 == TT_TYPEN) SP(ts[oc+1])->tt = TT_NAME;
				knh_Stmt_add(ctx, stmt, new_TermVALUE(ctx, ts[oc], isData));
				stmt = knh_Stmt_add_SECONDNAME(ctx, stmt, ts[oc+1]);
				tc->c = oc + 2;
				knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, tc, isData));
				return TM(stmt);
			}
		}
	}

	/* OPERATOR */ {
		int idx = knh_tokens_findOPR(ctx, tc, isData);
		if(idx != -1) {
			if(SP(ts[idx])->tt == TT_ERR) return TM(ts[idx]);
			return new_TermOPR(ctx, tc, ts[idx]);
		}
	}

	/* cast operator (C)a */ {
		Token *cast_op = knh_Token_findCASTNULL(ctx, ts[oc], ts[oc+1], isData);
		if(cast_op != NULL) {
			tc->c += 1;
			return TM(new_TermCAST(ctx, cast_op, tc, isData));
		}
	}

	if(knh_Token_isNEW(ctx, ts[oc])) {  /* @TEST new:gc Person("naruto") */
		if(DP(ts[oc])->tt_next == TT_TYPEN) {
			if(DP(ts[oc+1])->tt_next == TT_PARENTHESIS) {
				stmt = new_Stmt(ctx, 0, STT_NEW);
				knh_Stmt_add(ctx, stmt, TM(ts[oc]));
				knh_Stmt_add(ctx, stmt, TM(ts[oc+1]));
				pc = oc + 2;
				goto L_PARAM;
			}
			else if(DP(ts[oc+1])->tt_next == TT_BRANCET) {   /* @TEST new Int[10] */
				stmt = new_Stmt(ctx, 0, STT_NEW);
				knh_tokens_t cma_tc;
				knh_Token_tc(ctx, ts[oc+2], &cma_tc);
				if(knh_tokens_count(&cma_tc, TT_COMMA) == 1) {
					knh_Stmt_add(ctx, stmt, TM(new_TokenMN(ctx, FL(ts[oc]), METHODN_new__array2D)));
				}
				else if(knh_tokens_count(&cma_tc, TT_COMMA) == 2) {
					knh_Stmt_add(ctx, stmt, TM(new_TokenMN(ctx, FL(ts[oc]), METHODN_new__array3D)));
				}
				else {
					knh_Stmt_add(ctx, stmt, TM(new_TokenMN(ctx, FL(ts[oc]), METHODN_new__array)));
				}
				knh_Stmt_add(ctx, stmt, TM(ts[oc+1]));
				knh_Token_setArrayType(ts[oc+1], 1);
				pc = oc + 2;
				KNH_ASSERT(SP(ts[pc])->tt == TT_BRANCET);
				SP(ts[pc])->tt = TT_PARENTHESIS;
				goto L_PARAM;
			}
			else {
				Token *tke = ts[oc];
				knh_Token_perror(ctx, tke, KERR_ERROR, _("syntax error"));
				SP(tke)->tt = TT_ERR;
				tc->c = oc + 2; knh_tokens_nextStmt(tc);
				return TM(tke);
			}
		}
		else if(DP(ts[oc])->tt_next == TT_NAME && ISB(knh_Token_tobytes(ctx, ts[oc+1]), "byte") && DP(ts[oc+1])->tt_next == TT_BRANCET) {
			stmt = new_Stmt(ctx, 0, STT_NEW);
			knh_Stmt_add(ctx, stmt, TM(new_TokenMN(ctx, FL(ts[oc]), METHODN_new)));
			knh_Stmt_add(ctx, stmt, TM(new_Token__S(ctx, FL(ts[oc]), TT_TYPEN, ctx->share->ClassTable[CLASS_Bytes].sname)));
			pc = oc + 2;
			KNH_ASSERT(SP(ts[pc])->tt == TT_BRANCET);
			SP(ts[pc])->tt = TT_PARENTHESIS;
			goto L_PARAM;
		}
		else {
			knh_Token_perror(ctx, ts[oc+1], KERR_ERROR, _("syntax error"));
			return TM(new_StmtERR(ctx, tc));
		}
	}

	/* Closure Class (a, b) { ... } */
	if(knh_Token_isTYPEN(ts[oc])) {
		if(DP(ts[oc])->tt_next == TT_PARENTHESIS) {
			if(DP(ts[fc])->tt_next == TT_BRACE) {  /* @TEST Class (a,b) { ... } */
				tc->c = oc;
				stmt = new_Stmt(ctx, 0, STT_FUNCTION);
				knh_Stmt_add_TYPEN(ctx, stmt, tc);
				knh_Stmt_add_PARAMs(ctx, stmt, tc);
				knh_Stmt_add_STMT1(ctx, stmt, tc);
				fc = tc->c;
				goto L_NEXTFUNC;
			}
		}
	}

	/** first **/
	KNH_ASSERT(fc < e);
	{
		knh_token_t tt0 = SP(ts[oc])->tt, tt1 = DP(ts[oc])->tt_next;
		if((tt0 == TT_CONSTN || tt0 == TT_TYPEN) && tt1 == TT_PARENTHESIS) {
			SP(ts[oc])->tt = TT_NAME;
			tt0 = TT_NAME;
		}
		/* NAME */
		if(tt0 == TT_NAME) {
			if(tt1 == TT_PARENTHESIS) {   /* @TEST func(a) */
				stmt = new_StmtNAME2(ctx, ts[oc]);
				pc = oc + 1;
				goto L_PARAM;
			}
			else if(tt1 == TT_BRANCET) {    /* @TEST d[a] */
				stmt = new_StmtNAME1(ctx, ts[oc]);
				fc = oc + 1;
				goto L_FUNC;
			}
			else {
				tc->c = oc + 1;
				knh_tokens_ignore(ctx, tc);
				return new_TermVALUE(ctx, ts[oc], isData);
			}
		}
		else if(tt0 == TT_CMETHODN) {
			if(tt1 == TT_PARENTHESIS) {   /* @TEST func(a) */
				stmt = new_StmtNAME2(ctx, ts[oc]);
				pc = oc + 1;
				goto L_PARAM;
			}
			else {
				tc->c = oc + 1;
				knh_tokens_ignore(ctx, tc);
				return new_TermVALUE(ctx, ts[oc], isData);
			}
		}/* TT_NAME */
		else if(tt0 == TT_MT) {  /* @TEST %s(a) */
			if(tt1 != TT_PARENTHESIS) {
				tc->c = oc + 1;
				knh_Token_perror(ctx, ts[oc], KERR_ERROR, _("syntax error"));
				return TM(new_StmtERR(ctx, tc));
			}
			stmt = new_Stmt(ctx, 0, STT_MT);
			knh_Stmt_add(ctx, stmt, TM(ts[oc]));
			pc = oc + 1;
			goto L_PARAM;
		} /* DP(ts[oc])->TT == TT_MT */
		else if(knh_Token_isTYPEN(ts[oc])) {
			if(DP(ts[oc])->tt_next == TT_BRACE) {  /* @TEST Class {..} */
				Term *tm = new_TermDICTMAP(ctx, ts[oc], ts[oc+1], isData);
				tc->c = oc + 2;
				knh_tokens_ignore(ctx, tc);
				return tm;
			}
			tc->c = oc + 1;
			knh_tokens_ignore(ctx, tc);
			return TM(ts[oc]);
		}
		else {
			KNH_ASSERT(stmt == NULL);
			DBG2_P("**** FIRST TOKEN=%s", knh_token_tochar(tt0));
			Term *tm = new_TermVALUE(ctx, ts[oc], isData);
			if(SP((Token*)tm)->tt == TT_ERR) {
				return tm;
			}
			stmt = new_Stmt(ctx, 0, STT_CALL);
			knh_Stmt_add(ctx, stmt, tm);
			fc = oc + 1;
		}
	}

	L_FUNC:; /* function name */
	KNH_ASSERT(stmt != NULL);
	KNH_ASSERT(DP(stmt)->size == 1);
	KNH_ASSERT(fc > 0);

	if(SP(ts[fc])->tt == TT_NAME && knh_Token_isTopDot(ts[fc])) {
		stmt = knh_Stmt_add_SECONDNAME(ctx, stmt, ts[fc]);
		if(DP(ts[fc])->tt_next == TT_PARENTHESIS) {  /* @TEST (a).f(a) */
			pc = fc + 1;
			goto L_PARAM;
		}
		else if(DP(ts[fc])->tt_next == TT_BRANCET) { /* @TEST (a).f[a] */
			KNH_ASSERT(DP(stmt)->size == 2);
			stmt = new_Stmt__stmt(ctx, stmt);
			fc = fc + 1;
			goto L_FUNC;
		}
		/* (a).f */
		return TM(stmt);
	}
	else if(SP(ts[fc])->tt == TT_BRANCET) {
		knh_Stmt_add_IDX(ctx, stmt, ts[fc]);
		fc = fc + 1;
		goto L_NEXTFUNC;
	}
	else {
		DBG2_P("** Unexpected funcname %s **", knh_token_tochar(SP(ts[fc])->tt));
		knh_Token_perror(ctx, ts[fc], KERR_ERROR, _("syntax error"));
		knh_Stmt_add(ctx, stmt, TM(ts[fc]));
		tc->c = tc->e;
	}
	return TM(stmt);

	/** third *************************************************************/

	L_PARAM:;
	KNH_ASSERT(stmt != NULL);
	KNH_ASSERT(pc > 0);
	//DBG2_P("oc=%d, fc=%d, pc=%d %s", oc, fc, pc, knh_token_tochar(SP(ts[pc])->tt));
	KNH_ASSERT(SP(ts[pc])->tt == TT_PARENTHESIS);
	{
		knh_tokens_t ptc;
		knh_Token_tc(ctx, ts[pc], &ptc);
		knh_Stmt_add_EXPRs(ctx, stmt, &ptc, isData);
	}
	if(DP(stmt)->size == 1) {
		knh_perror(ctx, SP(ts[pc])->fileid, SP(ts[pc])->line, KERR_ERRATA, _("empty: () == > (null)"));
		knh_Stmt_add(ctx, stmt, TM(new_TokenCONST(ctx, FL(ts[oc]), KNH_NULL)));
	}
	fc = pc + 1; pc = 0;

	L_NEXTFUNC:;
	if(fc < e) {
		stmt = new_Stmt__stmt(ctx, stmt);
		goto L_FUNC;
	}
	return TM(stmt);
}


/* ======================================================================== */
/* [LET] */

static int knh_Token_isLCONSTN(Ctx *ctx, Token *tk)
{
	knh_bytes_t t = knh_Token_tobytes(ctx, tk);
	size_t i;
	for(i = 0; i < t.len; i++) {
		if(islower(t.buf[i])) return 0;
	}
	return 1;
}

/* ------------------------------------------------------------------------ */

static int knh_Token_isLVALUE(Ctx *ctx, Token *tkL)
{
	if(SP(tkL)->tt == TT_TYPEN && knh_Token_isLCONSTN(ctx, tkL)) {
		SP(tkL)->tt = TT_CONSTN;
	}
	return knh_Token_isVARN(tkL) || SP(tkL)->tt == TT_CONSTN;
}

/* ------------------------------------------------------------------------ */

static
void knh_Stmt_toLVALUE(Ctx *ctx, Stmt *stmt, int pe, char *fmt)
{
	if(SP(stmt)->stt == STT_CALL) {
		Token *tk = (Token*)DP(stmt)->tokens[0];
		DBG2_ASSERT(IS_Token(tk));
		if(knh_Token_isGetter(tk)) {
			knh_Token_setGetter(tk, 0);
			knh_Token_setSetter(tk, 1);
			return ;
		}
		else if(SP(tk)->tt == TT_MN) {
			knh_methodn_t mn = DP(tk)->mn;
			if(METHODN_IS_SETTER(mn)) {
				return ;
			}
			else if(METHODN_IS_GETTER(mn)) {
				mn = METHODN_TOFIELDN(mn);
				DP(tk)->mn = METHODN_TO_SETTER(mn);
				TODO();
				return ;
			}
		}
		else if(SP(tk)->tt == TT_FN) {
			TODO();
		}
		else {
			TODO();
		}
	}
	SP(stmt)->stt = STT_ERR;
	knh_perror(ctx, SP(stmt)->fileid, SP(stmt)->line, pe, fmt);
	DBG2_P("stt=%s", knh_stmt_tochar(SP(stmt)->stt));
}

/* ------------------------------------------------------------------------ */

static
Stmt *new_StmtLET(Ctx *ctx, knh_tokens_t *lvalue_tc, knh_tokens_t *rvalue_tc)
{
	Term *lval = new_TermEXPR(ctx, lvalue_tc, 0/*isData*/);
	if(IS_Token(lval)) {
		if(knh_Token_isLVALUE(ctx, (Token*)lval)) {
			Stmt *stmt = new_Stmt(ctx, 0, STT_LET);
			knh_Stmt_add(ctx, stmt, lval);
			knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, rvalue_tc, 0/*isData*/));
			return stmt;
		}
		else {
			knh_Token_perror(ctx, (Token*)lval, KERR_ERROR, _("unavailable l-value"));
			return new_StmtERR(ctx, lvalue_tc);
		}
	}
	else {
		Stmt *stmt = (Stmt*)lval;
		KNH_ASSERT(IS_Stmt(stmt));
		knh_Stmt_toLVALUE(ctx, stmt, KERR_ERROR, _("unavailable l-value"));
		if(SP(stmt)->stt != STT_ERR) {
			knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, rvalue_tc, 0/*isData*/));
		}
		return stmt;
	}
}

/* ------------------------------------------------------------------------ */

static
Stmt *new_StmtLETOP(Ctx *ctx, knh_tokens_t *lvalue_tc, Token *tkl, knh_tokens_t *rvalue_tc)
{
	SP(tkl)->tt = SP(tkl)->tt - (TT_ADDE - TT_ADD);
	rvalue_tc->c = lvalue_tc->c;
	return new_StmtLET(ctx, lvalue_tc, rvalue_tc);
}

/* ------------------------------------------------------------------------ */

static
Stmt *new_StmtLETMULTI(Ctx *ctx, knh_tokens_t *lvalue_tc, knh_tokens_t *rvalue_tc)
{
	knh_tokens_t cma_tc = knh_tokens_splitEXPR(ctx, lvalue_tc, TT_COMMA);
	Stmt *stmt_head = new_StmtLET(ctx, &cma_tc, rvalue_tc);
	Stmt *stmt = new_Stmt(ctx, 0, STT_LETMULTI);
	while(cma_tc.c < cma_tc.e) {
		knh_Stmt_add_VARN(ctx, stmt, &cma_tc);
		cma_tc = knh_tokens_splitEXPR(ctx, lvalue_tc, TT_COMMA);
	}
	knh_StmtNULL_tail_append(ctx, stmt_head, stmt);
	return stmt_head;
}

/* ------------------------------------------------------------------------ */

static
Stmt *new_StmtLETMULTI2(Ctx *ctx, knh_tokens_t *lvalue_tc, knh_tokens_t *rvalue_tc)
{
	Stmt *stmt_head = NULL;
	knh_tokens_t ltc = knh_tokens_splitEXPR(ctx, lvalue_tc, TT_COMMA);
	knh_tokens_t rtc = knh_tokens_splitEXPR(ctx, rvalue_tc, TT_COMMA);
	while(ltc.c < ltc.e && rtc.c < rtc.e) {
		Stmt *stmt = new_StmtLET(ctx, &ltc, &rtc);
		stmt_head = knh_StmtNULL_tail_append(ctx, stmt_head, stmt);
		ltc = knh_tokens_splitEXPR(ctx, lvalue_tc, TT_COMMA);
		rtc = knh_tokens_splitEXPR(ctx, rvalue_tc, TT_COMMA);
	}
	KNH_ASSERT(stmt_head != NULL);
	return stmt_head;
}

/* ------------------------------------------------------------------------ */

static Token *knh_tokens_findLETNULL(knh_tokens_t *tc)
{
	Token **ts = tc->ts;
	int i;
	for(i = tc->c; i < tc->e; i++) {
		if(TT_LET <= SP(ts[i])->tt && SP(ts[i])->tt <= TT_ALTLET) return ts[i];
	}
	return NULL;
}

/* ------------------------------------------------------------------------ */

static
void knh_tokens_divideLET(knh_tokens_t *tc, knh_tokens_t *ltc, knh_tokens_t *rtc)
{
	Token **ts = tc->ts;
	int i;
	for(i = tc->c; i < tc->e; i++) {
		if(TT_LET <= SP(ts[i])->tt && SP(ts[i])->tt <= TT_ALTLET) {
			break;
		}
	}
	ltc->ts = tc->ts;
	ltc->c = tc->c;
	ltc->e = i;
	rtc->ts = tc->ts;
	rtc->c = rtc->c = i + 1;
	rtc->e = tc->e;
}

/* ------------------------------------------------------------------------ */

static
Stmt* new_StmtLETEXPR(Ctx *ctx, knh_tokens_t *tc, int isData)
{
	knh_tokens_t expr_tc = knh_tokens_splitSTMT(ctx, tc);
	Token *tkl = knh_tokens_findLETNULL(&expr_tc);
	if(tkl != NULL) {
		if(isData) {
			Stmt *stmt = new_Stmt(ctx, 0, STT_CALL1);
			knh_Token_setCONST(ctx, tkl, KNH_NULL);
			knh_Stmt_add(ctx, stmt, TM(tkl));
			return stmt;
		}
		else {
			knh_tokens_t lvalue_tc, rvalue_tc;
			knh_tokens_divideLET(&expr_tc, &lvalue_tc, &rvalue_tc);
			if(SP(tkl)->tt != TT_LET) {
				return new_StmtLETOP(ctx, &lvalue_tc, tkl, &rvalue_tc);
			}
			else{
				int lc = knh_tokens_count(&lvalue_tc, TT_COMMA);
				int rc = knh_tokens_count(&rvalue_tc, TT_COMMA);
				if(lc == 0) {
					return new_StmtLET(ctx, &lvalue_tc, &rvalue_tc);
				}
				else if(rc == 0) {
					return new_StmtLETMULTI(ctx, &lvalue_tc, &rvalue_tc);
				}
				else {
					return new_StmtLETMULTI2(ctx, &lvalue_tc, &rvalue_tc);
				}
			}
		}
	}
	else if(!(expr_tc.c < expr_tc.e)) {
		return new_Stmt(ctx, 0, STT_DONE);
	}
	else {
		Term *term = new_TermEXPR(ctx, &expr_tc, isData);
		if(IS_Token(term)) {
			Stmt *stmt = new_Stmt(ctx, 0, STT_CALL1);
			knh_Stmt_add(ctx, stmt, term);
			return stmt;
		}
		DBG2_ASSERT(IS_Stmt(term));
		return (Stmt*)term;
	}
}

/* ======================================================================== */
/* [new_Stmt] */

static
void knh_StmtMETA_addLabel(Ctx *ctx, Stmt *o, Token *tkL)
{
	if(IS_NULL(DP(o)->metaDictMap)) {
		KNH_SETv(ctx, DP(o)->metaDictMap, new_DictMap0(ctx, 2));
	}
	DBG2_P("label: %s", sToken(tkL))
	if(IS_DictMap(DP(o)->metaDictMap)) {
		knh_DictMap_set(ctx, DP(o)->metaDictMap, TS_ATlabel, UP(tkL));
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtMETA_addMeta(Ctx *ctx, Stmt *o, String *p)
{
	if(IS_NULL(DP(o)->metaDictMap)) {
		KNH_SETv(ctx, DP(o)->metaDictMap, new_DictMap0(ctx, 2));
	}
	if(IS_DictMap(DP(o)->metaDictMap)) {
		KNH_ASSERT(IS_String(p));
		knh_DictMap_set(ctx, DP(o)->metaDictMap, p, UP(p));
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_StmtMETA_addMeta2(Ctx *ctx, Stmt *o, String *k, Token *p)
{
	if(IS_NULL(DP(o)->metaDictMap)) {
		KNH_SETv(ctx, DP(o)->metaDictMap, new_DictMap0(ctx, 2));
	}
	if(IS_DictMap(DP(o)->metaDictMap)) {
		knh_tokens_t tc;
		knh_Token_tc(ctx, p, &tc);
		if(tc.e == 0) {
			knh_DictMap_set(ctx, DP(o)->metaDictMap, k, UP(k));
		}
		else if(tc.e == 1) {
			if(IS_String(DP(tc.ts[0])->data)) {
				knh_DictMap_set(ctx, DP(o)->metaDictMap, k, DP(tc.ts[0])->data);
			}
			else {
				knh_DictMap_set(ctx, DP(o)->metaDictMap, k, UP(new_String(ctx, knh_Token_tobytes(ctx, tc.ts[0]), NULL)));
			}
		}
		else {
			TODO();
		}
	}
}

/* ------------------------------------------------------------------------ */

static
void knh_Stmt_addMETA(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	DBG2_P("stt=%s, meta=%d", knh_stmt_tochar(o->stt), tc->meta);
	if(tc->meta == -1 || SP(o)->stt == STT_DONE || SP(o)->stt == STT_ERR) {
		return ;
	}
	Token **ts = tc->ts;
	int i;
	if(tc->meta < tc->c) {
		for(i = tc->meta; i < tc->c; i++) {
			if(SP(ts[i])->tt == TT_LABEL) {
				knh_StmtMETA_addLabel(ctx, o, ts[i]);
			}
			else if(SP(ts[i])->tt == TT_METAN) {
				if(DP(ts[i])->tt_next == TT_PARENTHESIS) {
					knh_StmtMETA_addMeta2(ctx, o, (String*)DP(ts[i-1])->data, ts[i]);
					i++;
				}
				else {
					DBG2_P("META!! %s", sToken(ts[i]));
					knh_StmtMETA_addMeta(ctx, o, (String*)DP(ts[i])->data);
				}
			}
		}
		tc->meta = -1;
	}
	else {
		for(i = tc->meta; i < tc->e; i++) {
			if(SP(ts[i])->tt == TT_LABEL) {
				knh_StmtMETA_addLabel(ctx, o, ts[i]);
			}
			else if(SP(ts[i])->tt == TT_METAN) {
				if(DP(ts[i])->tt_next == TT_PARENTHESIS) {
					knh_StmtMETA_addMeta2(ctx, o, (String*)DP(ts[i-1])->data, ts[i]);
					i++;
				}
				else {
					knh_StmtMETA_addMeta(ctx, o, (String*)DP(ts[i])->data);
				}
			}
			else {
				break;
			}
		}
		tc->meta = -1;
		tc->c = i;
	}
}

/* ------------------------------------------------------------------------ */

static
Stmt *new_StmtMETA(Ctx *ctx,  knh_tokens_t *tc, knh_stmt_t stt)
{
	Stmt *o = new_Stmt(ctx, 0, stt);
	knh_Stmt_addMETA(ctx, o, tc);
	int c = tc->c - 1;
	if(c < 0) c = 0;
	SP(o)->line = SP(tc->ts[c])->line;
	SP(o)->fileid = SP(tc->ts[c])->fileid;
	return o;
}


/* ======================================================================== */
/* [COMMONS] */

static void knh_Stmt_add_STMT1(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && SP(tc->ts[tc->c])->tt == TT_BRACE) {
		knh_Stmt_add(ctx, o, TM(new_StmtINSTMT(ctx, tc->ts[tc->c])));
		tc->c += 1;
	}
	else {
		knh_Stmt_add(ctx, o, TM(new_StmtSTMT1(ctx, tc)));
	}
}

/* ------------------------------------------------------------------------ */

static void knh_Stmt_add_SEMICOLON(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && SP(tc->ts[tc->c])->tt == TT_SEMICOLON) {
		tc->c += 1;
	}
	else {
		knh_perror(ctx, SP(o)->fileid, SP(o)->line, KERR_INFO, _("needs ;"));
	}
}

/* ======================================================================== */
/* [new_Stmt] */

static int knh_Token_isNSNAME(Token *tk)
{
	if(SP(tk)->tt == TT_NAME) {
		size_t i;
		knh_bytes_t t = knh_String_tobytes(DP(tk)->text);
		for(i = 0; i < t.len; i++) {
			if(islower(t.buf[i]) || isdigit(t.buf[i]) || t.buf[i] == '.') {
				continue;
			}
			return 0;
		}
		return 1;
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static void knh_Stmt_add_NSNAME(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isNSNAME(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_tokens_perror(ctx, o, tc, _("namespace name is needed"));
	}
}

/* ------------------------------------------------------------------------ */

static Stmt *new_StmtNAMESPACE(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_NAMESPACE);
	knh_Stmt_add_NSNAME(ctx, o, tc); /* NSNAME */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [import] */

static int knh_Token_isFURN(Token *tk)
{
	switch(SP(tk)->tt) {
		case TT_STR:
		case TT_TSTR:
		case TT_URN:
		{
			String *s = (String*)DP(tk)->data;
			if(knh_String_endsWith(s, STEXT(".k"))) {
				return 1;
			}
			return 0;
		}
	}
	return 0;
}

/* ------------------------------------------------------------------------ */

static void knh_Stmt_add_FURN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isFURN(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_tokens_perror(ctx, o, tc, _("file or URN is needed"));
	}
}

/* ------------------------------------------------------------------------ */

static Stmt *new_StmtIMPORT(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_IMPORT);
	knh_Stmt_add_FURN(ctx, o, tc); /* FURN */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [USING] */
/* ------------------------------------------------------------------------ */
/* [using import] */

static
Stmt *new_StmtUIMPORT(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_UIMPORT);
	knh_Stmt_add_NSCLASSN(ctx, o, tc); /* NSCLASSN */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [using alias] */

//static
//Stmt *new_StmtUALIAS(Ctx *ctx, knh_tokens_t *tc)
//{
//	Stmt *o = new_StmtMETA(ctx, tc, STT_UALIAS);
//	knh_Stmt_add_CLASSN(ctx, o, tc); /* CLASSN */
//	knh_Stmt_add_PATH(ctx, o, tc); /* PATH */
//	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
//	return o;
//}

/* ------------------------------------------------------------------------ */
/* [using unit] */

static
Stmt *new_StmtUUNIT(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_UUNIT);
	knh_Stmt_add_CLASSTN(ctx, o, tc); /* CLASSTN */
	knh_Stmt_add_PATH(ctx, o, tc); /* PATH */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [using enum] */

static
Stmt *new_StmtUENUM(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_UENUM);
	knh_Stmt_add_CLASSTN(ctx, o, tc); /* CLASSTN */
	knh_Stmt_add_PATH(ctx, o, tc); /* PATH */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [using vocab] */

static
Stmt *new_StmtUVOCAB(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_UVOCAB);
	knh_Stmt_add_CLASSTN(ctx, o, tc); /* CLASSTN */
	knh_Stmt_add_PATH(ctx, o, tc); /* PATH */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [CMETHODN] */

#define knh_Token_isCFUNCN(tk)   (knh_Token_isCMETHODN(tk) || (knh_Token_isTYPEN(tk) && knh_Token_isTailWildCard(tk)))

static
void knh_Stmt_add_CFUNCN(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && knh_Token_isCFUNCN(tc->ts[tc->c])) {
		knh_Stmt_add(ctx, o, UP(tc->ts[tc->c]));
		tc->c += 1;
	}
	else {
		knh_Stmt_tokens_perror(ctx, o, tc, _("class function name is needed"));
	}
}

/* ------------------------------------------------------------------------ */
/* [using func] */

static
Stmt *new_StmtUFUNC(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_UFUNC);
	knh_Stmt_add_CFUNCN(ctx, o, tc); /* CMETHODN */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [using mapmap] */

//static
//Stmt *new_StmtUMAPMAP(Ctx *ctx, knh_tokens_t *tc)
//{
//	Stmt *o = new_StmtMETA(ctx, tc, STT_UMAPMAP);
//	knh_Stmt_add_CLASSTN(ctx, o, tc); /* CLASSTN */
//	knh_Stmt_add_CLASSTN(ctx, o, tc); /* CLASSTN */
//	knh_Stmt_add_PATH(ctx, o, tc); /* PATH */
//	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
//	return o;
//}

/* ------------------------------------------------------------------------ */

static
Stmt *new_StmtUSING(Ctx *ctx, knh_tokens_t *tc)
{
	if(tc->c < tc->e) {
		Token *tk = tc->ts[tc->c];
		knh_bytes_t op = knh_Token_tobytes(ctx, tk);

		if(ISB(op, "import")) {
			tc->c += 1;
			return new_StmtUIMPORT(ctx, tc);
		}

		if(ISB(op, "unit")) {
			tc->c += 1;
			return new_StmtUUNIT(ctx, tc);
		}

		if(knh_bytes_startsWith(op, STEXT("vacab"))) {
			tc->c += 1;
			return new_StmtUVOCAB(ctx, tc);
		}

		if(ISB(op, "enum")) {
			tc->c += 1;
			return new_StmtUENUM(ctx, tc);
		}

		/* using naruto.* */
		if(knh_Token_isNSCLASSN(ctx, tk)) {
			return new_StmtUIMPORT(ctx, tc);
		}

		/* using Math.* */
		if(knh_Token_isCFUNCN(tk)) {
			return new_StmtUFUNC(ctx, tc);
		}

		/* using Int:ns */
		if(knh_Token_isCLASSTN(ctx, tk)) {
			if(knh_bytes_startsWith(op, STEXT("Int:"))||knh_bytes_startsWith(op, STEXT("int:"))) {
				return new_StmtUENUM(ctx, tc);
			}
			if(knh_bytes_startsWith(op, STEXT("Float:"))||knh_bytes_startsWith(op, STEXT("float:"))) {
				return new_StmtUUNIT(ctx, tc);
			}
			if(knh_bytes_startsWith(op, STEXT("String:"))) {
				return new_StmtUVOCAB(ctx, tc);
			}
		}
		knh_Token_perror(ctx, tc->ts[tc->c-1], KERR_EWARN, _("unknown using options: %s"), sToken(tk));
	}
	knh_tokens_nextStmt(tc);
	return new_Stmt(ctx, 0, STT_DONE);
}

/* ------------------------------------------------------------------------ */
/* [class] */
/* ------------------------------------------------------------------------ */

static Stmt *new_StmtIMPLEMENTS(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_Stmt(ctx, 0, STT_IMPLEMENTS);
	if(tc->c < tc->e) {
		while(tc->c < tc->e) {
			knh_Stmt_add_CLASSN(ctx, o, tc);
			if(tc->c < tc->e && SP(tc->ts[tc->c])->tt != TT_COMMA) {
				break;
			}
			tc->c += 1;
		}
	}
	return o;
}

/* ------------------------------------------------------------------------ */

static void knh_Stmt_add_EXTENDS(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && SP(tc->ts[tc->c])->tt == TT_EXTENDS) {
		tc->c += 1;
		knh_Stmt_add_CLASSN(ctx, o, tc);
	}
	else {
		knh_Stmt_add_S(ctx, o, TT_TYPEN, ctx->share->ClassTable[CLASS_Object].sname);
	}
	if(tc->c < tc->e && SP(tc->ts[tc->c])->tt == TT_IMPLEMENTS) {
		tc->c += 1;
		knh_Stmt_add(ctx, o, TM(new_StmtIMPLEMENTS(ctx, tc)));
	}
	else {
		knh_Stmt_add(ctx, o, TM(new_Stmt(ctx, 0, STT_DONE)));
	}
	knh_Stmt_add_STMT1(ctx, o, tc);
}

/* ------------------------------------------------------------------------ */

static Stmt *new_StmtCLASS(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_CLASS);
	knh_Stmt_add_CLASSN(ctx, o, tc); /* CLASSN */
	knh_Stmt_add_EXTENDS(ctx, o, tc); /* extends */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [format] */

static Stmt *new_StmtFORMAT(Ctx *ctx, knh_tokens_t *tc)
{
	Token **ts = tc->ts;
	if(tc->c < tc->e && SP(ts[tc->c])->tt == TT_PARENTHESIS) {
		/* format("%s", a) */
		tc->c =-1;
		return new_StmtLETEXPR(ctx, tc, 0/*isData*/);
	}
	else {
		knh_Token_perror(ctx, tc->ts[tc->c-1], KERR_EWARN, _("format will be supported soon or later"));
		knh_tokens_nextStmt(tc);
		return new_Stmt(ctx, 0, STT_DONE);
	}
//	Stmt *o = new_StmtMETA(ctx, tc, STT_FORMAT);
//	knh_Stmt_add_MT(ctx, o, tc); /* MT */
//	knh_Stmt_add_PARAMs(ctx, o, tc); /* PARAM* */
//	knh_Stmt_add_STR(ctx, o, tc); /* STR */
//	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
//	return o;
}

/* ------------------------------------------------------------------------ */
/* [return] */

static Stmt *new_StmtRETURN(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_RETURN);
	knh_Stmt_add_EXPRs(ctx, o, tc, 0/*isData*/); /* EXPR* */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [mapmap] */
/* ------------------------------------------------------------------------ */

static
void knh_Stmt_add_CLASSTNs(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	knh_tokens_t stmt_tc = knh_tokens_splitSTMT(ctx, tc);
	while(stmt_tc.c < stmt_tc.e) {
		knh_tokens_t comma_tc = knh_tokens_splitEXPR(ctx, &stmt_tc, TT_COMMA);
		if(comma_tc.c < comma_tc.e) {
			knh_Stmt_add_CLASSTN(ctx, o, &comma_tc);
			knh_tokens_ignore(ctx, &comma_tc);
		}
	}
}

/* ------------------------------------------------------------------------ */

static Stmt *new_StmtMAPMAP(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_MAPMAP);
	knh_Stmt_add_CLASSTNs(ctx, o, tc); /* CLASSTN* */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [weave] */

static Stmt *new_StmtWEAVE(Ctx *ctx, knh_tokens_t *tc)
{
	knh_Token_perror(ctx, tc->ts[tc->c-1], KERR_EWARN, _("weave will be supported soon or later"));
	knh_tokens_nextStmt(tc);
	return new_Stmt(ctx, 0, STT_DONE);
//	Stmt *o = new_StmtMETA(ctx, tc, STT_WEAVE);
//	knh_Stmt_add_ANY(ctx, o, tc); /* ANY */
//	knh_Stmt_add_CMETHODN(ctx, o, tc); /* CMETHODN */
//	return o;
}

/* ------------------------------------------------------------------------ */
/* [aspect] */

static Stmt *new_StmtASPECT(Ctx *ctx, knh_tokens_t *tc)
{
	knh_Token_perror(ctx, tc->ts[tc->c-1], KERR_EWARN, _("aspect will be supported soon or later"));
	knh_tokens_nextStmt(tc);
	return new_Stmt(ctx, 0, STT_DONE);
//	Stmt *o = new_StmtMETA(ctx, tc, STT_ASPECT);
//	knh_Stmt_add_TYPEN(ctx, o, tc); /* TYPEN */
//	knh_Stmt_add_CMETHOD(ctx, o, tc); /* cmethod */
//	return o;
}

/* ------------------------------------------------------------------------ */
/* [block] */

static Stmt *new_StmtBLOCK(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_BLOCK);
	knh_Stmt_add_STMT1(ctx, o, tc); /* { */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [if] */
/* ------------------------------------------------------------------------ */

static void knh_Stmt_add_ELSE(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && SP(tc->ts[tc->c])->tt == TT_ELSE) {
		tc->c += 1;
		knh_Stmt_add_STMT1(ctx, o, tc);
	}
	else {
		knh_Stmt_add(ctx, o, TM(new_Stmt(ctx, 0, STT_DONE)));
	}
}

/* ------------------------------------------------------------------------ */

static Stmt *new_StmtIF(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_IF);
	knh_Stmt_add_PEXPR(ctx, o, tc); /* pexpr */
	knh_Stmt_add_STMT1(ctx, o, tc); /* { */
	knh_Stmt_add_ELSE(ctx, o, tc); /* else */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [switch] */

static Stmt *new_StmtSWITCH(Ctx *ctx, knh_tokens_t *tc)
{
	knh_Token_perror(ctx, tc->ts[tc->c-1], KERR_EWARN, _("switch will be supported soon or later"));
	knh_tokens_nextStmt(tc);
	return new_Stmt(ctx, 0, STT_DONE);
//	Stmt *o = new_StmtMETA(ctx, tc, STT_SWITCH);
//	knh_Stmt_add_PEXPR(ctx, o, tc); /* pexpr */
//	knh_Stmt_add_STMT1(ctx, o, tc); /* { */
//	return o;
}

/* ------------------------------------------------------------------------ */
/* [while] */

static Stmt *new_StmtWHILE(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_WHILE);
	knh_Stmt_add_PEXPR(ctx, o, tc); /* pexpr */
	knh_Stmt_add_STMT1(ctx, o, tc); /* { */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [do] */

static Stmt *new_StmtDO(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_DO);
	knh_Stmt_add_STMT1(ctx, o, tc); /* { */
	knh_Stmt_add_PEXPR(ctx, o, tc); /* pexpr */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [foreach] */
/* ------------------------------------------------------------------------ */

static
void knh_Stmt_add_FROM(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	knh_Stmt_add(ctx, o, new_TermEXPR(ctx, tc, 0/*isData*/));
}

/* ------------------------------------------------------------------------ */

static
void knh_Stmt_add_WHERE(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e) {
		knh_Stmt_add(ctx, o, new_TermEXPR(ctx, tc, 0/*isData*/));
	}
	else {
		knh_Stmt_add(ctx, o, TM(new_TokenCONST(ctx, FL(o), KNH_TRUE)));
	}
}

/* ------------------------------------------------------------------------ */
// foreach(String n from source[] where p) {} */
// foreach(select name, age from (HashMap).opItr2()[] where p) {} */
// foreach(n from a [] where p) {}
// foreach(n from

void
knh_Stmt_add_PEACH(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	Token *tk = tc->ts[tc->c];
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && SP(tk)->tt != TT_PARENTHESIS) {
		knh_Stmt_tokens_perror(ctx, o, tc, _("syntax error: needs ()"));
		return;
	}

	knh_tokens_t ptc;
	knh_tokens_t val_tc, from_tc, where_tc;
	int i;
	knh_Token_tc(ctx, tc->ts[tc->c], &ptc);
	for(i = 1; i < ptc.e; i++) {
		if(SP(ptc.ts[i])->tt == TT_FROM || SP(ptc.ts[i])->tt == TT_COLON
			|| (i > 0 && SP(ptc.ts[i])->tt == TT_NAME && ISB(knh_Token_tobytes(ctx, ptc.ts[i]), "in"))) {
			val_tc.c = 0;
			val_tc.e = i;
			val_tc.ts = ptc.ts;
			if(SP(ptc.ts[i])->tt == TT_FROM) {
				knh_Stmt_setMAPNEXT(o, 1);
			}
			i++;
			goto L_FROM;
		}
	}
	knh_Stmt_tokens_perror(ctx, o, tc, _("syntax error: needs from"));
	return;

	L_FROM:;
	from_tc.c = i;
	from_tc.e = ptc.e;
	from_tc.ts = ptc.ts;
	where_tc.c = ptc.e;
	where_tc.e = ptc.e;
	where_tc.ts = ptc.ts;
	for(i = 0; i < ptc.e; i++) {
		if(SP(ptc.ts[i])->tt == TT_WHERE || SP(ptc.ts[i])->tt == TT_SEMICOLON) {
			from_tc.e = i;
			where_tc.c = i + 1;
			break;
		}
	}

	if(!(from_tc.c < from_tc.e)) {
		DBG2_P("NO FROM!! c=%d, e=%d", from_tc.c, from_tc.e);
		knh_Stmt_tokens_perror(ctx, o, tc, _("syntax error: needs from"));
		return;
	}

	knh_Stmt_add_TYPEVARN(ctx, o, &val_tc);
	knh_tokens_ignore(ctx, &val_tc);
	knh_Stmt_add_FROM(ctx, o, &from_tc);
	knh_Stmt_add_WHERE(ctx, o, &where_tc);
	tc->c += 1;
	knh_Stmt_add_STMT1(ctx, o, tc);
}

/* ------------------------------------------------------------------------ */

static Stmt *new_StmtFOREACH(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_FOREACH);
	knh_Stmt_add_PEACH(ctx, o, tc); /* peach */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [for] */

static
void knh_Stmt_add_PSTMT3(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	Token *tk = tc->ts[tc->c];
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e && SP(tk)->tt != TT_PARENTHESIS) {
		knh_Stmt_tokens_perror(ctx, o, tc, _("syntax error: needs ()"));
	}

	knh_tokens_t ptc;
	knh_Token_tc(ctx, tc->ts[tc->c], &ptc);

	if(knh_tokens_count(&ptc, TT_COLON) > 0) {
		/* java-style for(n : a) */
		SP(o)->stt = STT_FOREACH;
		knh_Stmt_add_PEACH(ctx, o, tc);
		return;
	}

	int c = knh_tokens_count(&ptc, TT_SEMICOLON);
	if(c != 2) {
		knh_Stmt_tokens_perror(ctx, o, tc, _("syntax error: needs ;"));
		return ;
	}

	/* for(FIRST;second;third) */
	knh_tokens_t stmt_tc = knh_tokens_splitEXPR(ctx, &ptc, TT_SEMICOLON);
	if(stmt_tc.c < stmt_tc.e) {
		Token *tkT = stmt_tc.ts[stmt_tc.c];
		if(SP(tkT)->tt == TT_TYPEN && DP(tkT)->tt_next == TT_NAME) {
			stmt_tc.c  += 1;
			stmt_tc.meta = -1;
			knh_Stmt_add(ctx, o, TM(new_StmtDECL(ctx, tkT, &stmt_tc)));
		}
		else {
			knh_Stmt_add(ctx, o, TM(new_StmtLETEXPR(ctx, &stmt_tc, 0/*isData*/)));
		}
	}
	else {
		knh_Stmt_add(ctx, o, TM(new_Stmt(ctx, 0, STT_DONE)));
	}

	stmt_tc = knh_tokens_splitEXPR(ctx, &ptc, TT_SEMICOLON);
	/* for(first;SECODN;third) */
	if(stmt_tc.c < stmt_tc.e) {
		knh_Stmt_add(ctx, o, new_TermEXPR(ctx, &stmt_tc, 0/*isData*/));
	}
	else {
		knh_Stmt_add(ctx, o, TM(new_TokenCONST(ctx, FL(tc->ts[tc->c]), KNH_TRUE)));
	}

	/* for(first;second;THIRD) */
	if(ptc.c < ptc.e) {
		knh_Stmt_add(ctx, o, TM(new_StmtLETEXPR(ctx, &ptc, 0/*isData*/)));
	}
	else {
		knh_Stmt_add(ctx, o, TM(new_Stmt(ctx, 0, STT_DONE)));
	}
	tc->c += 1;
	knh_Stmt_add_STMT1(ctx, o, tc);
}

/* ------------------------------------------------------------------------ */

static Stmt *new_StmtFOR(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_FOR);
	knh_Stmt_add_PSTMT3(ctx, o, tc); /* pstmt3 */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [break] */

static
void knh_Stmt_add_LABEL_(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e) {
		Token *tk = tc->ts[tc->c];
		if(SP(tk)->tt == TT_LABEL || SP(tk)->tt == TT_CONSTN ||
				SP(tk)->tt == TT_NAME || SP(tk)->tt == TT_TYPEN) {
			knh_Stmt_add(ctx, o, TM(tk));
			tc->c += 1;
		}
		else {
			knh_Stmt_add_ASIS(ctx, o);
		}
	}
	else {
		knh_Stmt_add_ASIS(ctx, o);
	}
}

/* ------------------------------------------------------------------------ */

static Stmt *new_StmtBREAK(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_BREAK);
	knh_Stmt_add_LABEL_(ctx, o, tc); /* any_ */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [continue] */

static Stmt *new_StmtCONTINUE(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_CONTINUE);
	knh_Stmt_add_LABEL_(ctx, o, tc); /* any_ */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [try] */
/* ------------------------------------------------------------------------ */

static Stmt *new_StmtCATCH(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *stmt = NULL;
	if(tc->c < tc->e && SP(tc->ts[tc->c])->tt == TT_PARENTHESIS) {
		knh_tokens_t tcP;  /* (tcP)*/
		knh_Token_tc(ctx, tc->ts[tc->c], &tcP);
		if(tcP.e < 1) {
			knh_Token_perror(ctx, tc->ts[tc->c], KERR_DWARN, _("nothing to catch"));
			return new_Stmt(ctx, 0, STT_DONE);
		}
		else {
			stmt = new_Stmt(ctx, 0, STT_CATCH);
			knh_Stmt_add_TYPEN(ctx, stmt, &tcP);
			knh_Stmt_add_VARN(ctx, stmt, &tcP);
			knh_tokens_ignore(ctx, &tcP);
			tc->c += 1;
		}
		knh_Stmt_add_STMT1(ctx, stmt, tc);
	}
	else {
		knh_Stmt_tokens_perror(ctx, stmt, tc, _("syntax error: needs ()"));
		return new_Stmt(ctx, 0, STT_DONE);
	}

	if(tc->c < tc->e && SP(tc->ts[tc->c])->tt == TT_CATCH) {
		tc->c += 1;
		knh_StmtNULL_tail_append(ctx, stmt, new_StmtCATCH(ctx, tc));
	}
	return stmt;
}

/* ------------------------------------------------------------------------ */

static void knh_Stmt_add_CATCH(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;

	if(tc->c < tc->e && SP(tc->ts[tc->c])->tt == TT_CATCH) {
		tc->c += 1;
		knh_Stmt_add(ctx, o, TM(new_StmtCATCH(ctx, tc)));
	}
	else {
		knh_Stmt_add(ctx, o, TM(new_Stmt(ctx, 0, STT_DONE)));
	}

	if(tc->c < tc->e && SP(tc->ts[tc->c])->tt == TT_FINALLY) {
		tc->c += 1;
		knh_Stmt_add_STMT1(ctx, o, tc);
	}
	else {
		knh_Stmt_add(ctx, o, TM(new_Stmt(ctx, 0, STT_DONE)));
	}
}

/* ------------------------------------------------------------------------ */

static Stmt *new_StmtTRY(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_TRY);
	knh_Stmt_add_STMT1(ctx, o, tc); /* { */
	knh_Stmt_add_CATCH(ctx, o, tc); /* catch */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [throw] */

static Stmt *new_StmtTHROW(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_THROW);
	knh_Stmt_add_EXPR(ctx, o, tc, 0/*isData*/); /* expr */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [local] */

static Stmt *new_StmtREGISTER(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_REGISTER);
	knh_Stmt_add_EXPRs(ctx, o, tc, 0/*isData*/); /* expr* */
	//knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [print] */

static
void knh_Stmt_add_PRINTEXPRs(Ctx *ctx, Stmt *stmt, knh_tokens_t *tc)
{
	knh_tokens_t expr_tc = knh_tokens_splitSTMT(ctx, tc);
	while(expr_tc.c < expr_tc.e) {
		knh_tokens_t sub_tc = knh_tokens_splitEXPR(ctx, &expr_tc, TT_COMMA);
		if(sub_tc.c < sub_tc.e) {
			if(sub_tc.c + 1 == sub_tc.e) {
				Token *tkn = sub_tc.ts[sub_tc.c];
				if(SP(tkn)->tt == TT_NAME || SP(tkn)->tt == TT_CONSTN) {
					tkn = new_TokenCONST(ctx, FL(tkn), DP(tkn)->data);
					knh_Token_setPNAME(tkn, 1);
					knh_Stmt_add(ctx, stmt, TM(tkn));
				}
			}
			knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, &sub_tc, 0/*isData*/));
		}
	}
}

/* ------------------------------------------------------------------------ */

static Stmt *new_StmtPRINT(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_PRINT);
	knh_Stmt_add_PRINTEXPRs(ctx, o, tc); /* expr* */
	knh_Stmt_add_SEMICOLON(ctx, o, tc); /* ; */
	return o;
}

/* ------------------------------------------------------------------------ */
/* [assert] */

static Stmt *new_StmtASSERT(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_ASSERT);
	knh_Stmt_add_PEXPR(ctx, o, tc); /* pexpr */
	knh_Stmt_add_STMT1(ctx, o, tc); /* { */
	return o;
}


/* ======================================================================== */
/* [FUNCEXPR] */

static
void knh_Stmt_add_CMETHOD(Ctx *ctx, Stmt *o, knh_tokens_t *tc)
{
	if(SP(o)->stt == STT_ERR) return;
	if(tc->c < tc->e) {
		Token *tkc = tc->ts[tc->c];
		if(SP(tkc)->tt == TT_CMETHODN) {
			knh_Stmt_add(ctx, o, TM(tkc));
			knh_Stmt_add(ctx, o, TM(tkc));
			tc->c += 1;
			goto L_PARAMS;
		}
		else if(SP(tkc)->tt == TT_NAME /* && knh_Token_isMETHODN(tkc) */) {
			knh_Stmt_add_ASIS(ctx, o);
			knh_Stmt_add(ctx, o, TM(tkc));
			tc->c += 1;
			goto L_PARAMS;
		}
		else if(SP(tkc)->tt == TT_PARENTHESIS) {
			knh_Stmt_add_ASIS(ctx, o);
			knh_Stmt_add(ctx, o, TM(new_TokenMN(ctx, FL(tkc), METHODN_new)));
			//tc->c += 1;
			goto L_PARAMS;
		}
	}
	knh_Stmt_tokens_perror(ctx, o, tc, _("method/function name is needed"));
	return;

	L_PARAMS:;
	knh_Stmt_add_PARAMs(ctx, o, tc);
	if(tc->c < tc->e && SP(tc->ts[tc->c])->tt == TT_BRACE) {
		knh_Stmt_add_STMT1(ctx, o, tc);
	}
	else {
		knh_Stmt_add_SEMICOLON(ctx, o, tc);
	}
}

/* ------------------------------------------------------------------------ */
/* [method] */

static
Stmt *new_StmtMETHOD(Ctx *ctx, knh_tokens_t *tc)
{
	Stmt *o = new_StmtMETA(ctx, tc, STT_METHOD);
	knh_Stmt_add_TYPEN(ctx, o, tc); /* TYPEN */
	knh_Stmt_add_CMETHOD(ctx, o, tc); /* cmethod */
	return o;
}

/* ======================================================================== */
/* [DECL] */

static
Stmt *new_StmtDECL(Ctx *ctx, Token *tkT, knh_tokens_t *tc)
{
	Stmt *stmt = new_StmtMETA(ctx, tc, STT_DECL);

	knh_tokens_t expr_tc = knh_tokens_splitEXPR(ctx, tc, TT_COMMA);
	knh_Stmt_add(ctx, stmt, TM(tkT));
	knh_Stmt_add_VARN(ctx, stmt, &expr_tc);

	if(expr_tc.c == expr_tc.e) {   /* Type name; */
		knh_Stmt_add_ASIS(ctx, stmt);
		goto L_NEXT;
	}

	if(SP(expr_tc.ts[expr_tc.c])->tt == TT_LET) {  /* Type name = (expr) */
		expr_tc.c += 1;
		knh_Stmt_add(ctx, stmt, new_TermEXPR(ctx, &expr_tc, 0/*isData*/));
	}
	else { /* Syntax Error */
		knh_perror(ctx, SP(stmt)->fileid, SP(stmt)->line, KERR_ERROR, _("initialization needs ="));
		SP(stmt)->stt = STT_ERR;
		return stmt;
	}

	L_NEXT:;
	if(tc->c < tc->e) {
		Stmt *newstmt = new_StmtDECL(ctx, tkT, tc);
		KNH_SETv(ctx, DP(newstmt)->metaDictMap, DP(stmt)->metaDictMap);
		KNH_SETv(ctx, DP(stmt)->next, newstmt);
	}
	return stmt;
}

/* ------------------------------------------------------------------------ */

static
Stmt* new_StmtFUNCEXPR(Ctx *ctx, knh_tokens_t *tc)
{
	tc->c -= 1;  /* rollback @see(new_StmtSTMT1) */
	Token** ts = tc->ts;
	int c = tc->c;
	KNH_ASSERT(c < tc->e);

	if(SP(ts[c])->tt == TT_TYPEN) {  /* @TEST int func(n) { ... } */
		if(DP(ts[c])->tt_next == TT_NAME && DP(ts[c+1])->tt_next == TT_PARENTHESIS) {
			return new_StmtMETHOD(ctx, tc);
		}
		if(DP(ts[c])->tt_next == TT_CMETHODN && DP(ts[c+1])->tt_next == TT_PARENTHESIS) { /* @TEST float Math.abs() */
			return new_StmtMETHOD(ctx, tc);
		}
		if(DP(ts[c])->tt_next == TT_NAME && knh_Token_isVARN(ts[c+1])) {  /* @TEST int name; */
			Token *tk_TYPEN = ts[c]; tc->c += 1;
			knh_tokens_t expr_tc = knh_tokens_splitSTMT(ctx, tc);
			return new_StmtDECL(ctx, tk_TYPEN, &expr_tc);
		}
		if(DP(ts[c])->tt_next == TT_PARENTHESIS && DP(ts[c+1])->tt_next== TT_BRACE) { /* @TEST int (n) {...} */
			return new_StmtMETHOD(ctx, tc);
		}
	}
	/* @TEST f(n) { ... } */
	if(SP(ts[c])->tt == TT_NAME) {
		if(DP(ts[c])->tt_next == TT_PARENTHESIS && DP(ts[c+1])->tt_next== TT_BRACE) {
			return new_StmtMETHOD(ctx, tc);
		}
	}
	return new_StmtLETEXPR(ctx, tc, 0/*isData*/);
}

/* ------------------------------------------------------------------------ */
/* [pragma] */

static void konohac_pragma(Ctx *ctx, knh_tokens_t *tc)
{
	KNH_FUTURE("pargma");
	knh_tokens_nextStmt(tc);
}

/* ------------------------------------------------------------------------ */
/* [SPECIAL] */

static int knh_Token_isDEBUG(Token *tk)
{
	if(DP(tk)->tt_next == TT_BRACE) {
		String *s = DP(tk)->text;
		if(IS_String(s)) {
			return (knh_bytes_strcasecmp(knh_String_tobytes(s), STEXT("DEBUG")) == 0);
		}
	}
	return 0;
}

/* ------------------------------------------------------------------------ */
/* [STMT1] */

static Stmt *new_StmtSTMT1(Ctx *ctx, knh_tokens_t *tc)
{
	Token *tkc = NULL;
	tc->meta = -1;

	L_TAIL:;
	if(!(tc->c < tc->e)) {
		DBG2_P("c = %d, e = %d", tc->c, tc->e);
		return new_Stmt(ctx, 0, STT_DONE);
	}

	tkc = tc->ts[tc->c];
	tc->c += 1;
	if(knh_Token_isDEBUG(tkc)) {
		Stmt *stmt = new_StmtBLOCK(ctx, tc);
		knh_Stmt_setDEBUG(stmt, 1);
		return stmt;
	}

	switch(SP(tkc)->tt) {

	case TT_LABEL:
	{
		if(tc->meta == -1) tc->meta = tc->c - 1;
		goto L_TAIL;
	}
	case TT_METAN:
	{
		if(tc->meta == -1) tc->meta = tc->c - 1;
		//DBG2_P("Found METAN '@%s', tc->meta=%d", sToken(tkc), tc->meta);
		if(DP(tkc)->tt_next == TT_PARENTHESIS) {
			tc->c += 1;
		}
		if(DP(tkc)->tt_next == TT_BRACE) {
			//DBG2_P("Found DATA '@%s', tc->meta=%d", sToken(tkc), tc->meta);
			tc->c += 1;
		}
		if(DP(tkc)->tt_next == TT_TYPEN) {
			DBG2_ASSERT(IS_String(DP(tc->ts[tc->c])->text));
			if(knh_String_equals(DP(tc->ts[tc->c])->text, STEXT("Unsafe"))) {
				knh_Token_setUnsafeType(tc->ts[tc->c], 1);
			}
		}
		goto L_TAIL;
	}

	case TT_NAMESPACE:
		return new_StmtNAMESPACE(ctx, tc);
	case TT_IMPORT:
		return new_StmtIMPORT(ctx, tc);
	case TT_PRAGMA:
		konohac_pragma(ctx, tc);
		return new_Stmt(ctx, 0, STT_DONE);
	case TT_USING:
		return new_StmtUSING(ctx, tc);
	case TT_WITH:
		break;  /* NOTHERE */
	case TT_CLASS:
		return new_StmtCLASS(ctx, tc);
	case TT_EXTENDS:
		break;  /* NOTHERE */
	case TT_IMPLEMENTS:
		break;  /* NOTHERE */
	case TT_METHOD:
		return new_StmtMETHOD(ctx, tc);
	case TT_FORMAT:
		return new_StmtFORMAT(ctx, tc);
	case TT_RETURN:
		return new_StmtRETURN(ctx, tc);
	case TT_MAPMAP:
		return new_StmtMAPMAP(ctx, tc);
	case TT_WEAVE:
		return new_StmtWEAVE(ctx, tc);
	case TT_ASPECT:
		return new_StmtASPECT(ctx, tc);
	case TT_IF:
		return new_StmtIF(ctx, tc);
	case TT_ELSE:
		break;  /* NOTHERE */
	case TT_SWITCH:
		return new_StmtSWITCH(ctx, tc);
	case TT_CASE:
		break;   /* NOTHERE */
	case TT_WHILE:
		return new_StmtWHILE(ctx, tc);
	case TT_DO:
		return new_StmtDO(ctx, tc);
	case TT_FOR:
		return new_StmtFOR(ctx, tc);
	case TT_FOREACH:
		return new_StmtFOREACH(ctx, tc);
	case TT_FROM:
		break;  /* NOTHERE */
	case TT_WHERE:
		break;  /* NOTHERE */
	case TT_BREAK:
		return new_StmtBREAK(ctx, tc);
	case TT_CONTINUE:
		return new_StmtCONTINUE(ctx, tc);
	case TT_TRY:
		return new_StmtTRY(ctx, tc);
	case TT_CATCH:
		break;  /* NOTHERE */
	case TT_FINALLY:
		break;  /* NOTHERE */
	case TT_THROW:
		return new_StmtTHROW(ctx, tc);
	case TT_REGISTER:
		return new_StmtREGISTER(ctx, tc);
	case TT_PRINT:
		return new_StmtPRINT(ctx, tc);
	case TT_ASSERT:
		return new_StmtASSERT(ctx, tc);
	case TT_SEMICOLON:
		knh_tokens_nextStmt(tc);
		DBG2_P("EMPTY STATEMENT tc->c=%d, tc->e=%d", tc->c, tc->e);
		return new_Stmt(ctx, 0, STT_DONE);

	case TT_BRACE:  /* BRACE */
	{
		DBG2_P("**** Block? ******");
		tc->c -= 1;
		return new_StmtBLOCK(ctx, tc);
	}
	case TT_PARENTHESIS:  /* PARENTHESIS */
	case TT_BRANCET:  /* BRANCET */
	case TT_DOTS:  /* DOTS */
	case TT_NOT:  /* Not */
	case TT_LOR:  /* Lor */
	case TT_ADD:  /* Add */
	case TT_SUB:  /* Sub */
	case TT_LAND:  /* Land */
	case TT_LNOT:  /* Lnot */
	case TT_XOR:  /* Xor */
	case TT_NEXT:  /* Next */
	case TT_PREV:  /* Prev */
	case TT_NEG:  /* Neg */
	case TT_NUM:  /* NUM */
	case TT_STR:  /* STR */
	case TT_TSTR:  /* TSTR */
	case TT_ESTR:  /* EVAL */
	case TT_PROPN:  /* PROPN */
	case TT_URN:  /* URN */
	case TT_MT:  /* MT */
	case TT_CONSTN:  /* CONSTN */
	case TT_TYPEN:  /* TYPEN */
	case TT_CMETHODN:  /* CMETHODN */
	case TT_NAME:  /* NAME */
	case TT_MN:  /* MN */
	case TT_FN:  /* FN */
	case TT_CID:  /* CID */
	case TT_MPR:  /* MPR */
		return new_StmtFUNCEXPR(ctx, tc);

	case TT_COMMA:
	case TT_LET:
	case TT_LSHIFTE:
	case TT_RSHIFTE:
	case TT_ADDE:
	case TT_SUBE:
	case TT_MULE:
	case TT_DIVE:
	case TT_MODE:
	case TT_BITORE:
	case TT_BITANDE:
	case TT_ALTLET:
	case TT_QUESTION:
	case TT_ITR:
	case TT_SUBSET:
	case TT_OFFSET:
	case TT_COLON:
	case TT_ALT:
	case TT_OR:
	case TT_AND:
	case TT_INSTANCEOF:
	case TT_ISA:
	case TT_AS:
	case TT_HAS:
	case TT_IS:
	case TT_TO:
	case TT_EQ:
	case TT_NEQ:
	case TT_LT:
	case TT_LTE:
	case TT_GT:
	case TT_GTE:
	case TT_MATCH:
	case TT_LSHIFT:
	case TT_RSHIFT:
	case TT_DIV:  /* Div */
	case TT_MOD:  /* Mod */
	case TT_MUL:  /* Mul */
		break; /* NOTHERE */

	case TT_ERR:
		tc->c -= 1;
		return new_StmtERR(ctx, tc);

	case TT_EOT:  /* EOT */
	case TT_CONST:  /* CONST */
	case TT_DEFVAL:  /* DEFVAL */
	case TT_SYSVAL:  /* SYSVAL */
	case TT_STACK:  /* STACK */
	case TT_FIELD:  /* FIELD */
	case TT_GLOBAL:  /* GLOBAL */
	case TT_MEMBER:  /* MEMBER */
	case TT_CLASSID:  /* CLASSID */
	case TT_ASIS:  /* ASIS */
	case TT_NOP:  /* NOP */
		break;
	}

	tc->c -= 1;
	Token *tk = tc->ts[tc->c];
	knh_Token_perror(ctx, tk, KERR_ERROR, "syntax error: don't use '%s' HERE", sToken(tk));
	return new_StmtERR(ctx, tc);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
