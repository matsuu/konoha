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
/* [visit_declc] */

void knh_stmtvisit_declc(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
    switch(stmt->stt) {
        case STT_DONE: break;
        case STT_NAMESPACE:
            knh_stmtvisit_declc__namespace(ctx, stmt, v, level, step);
            break;
        case STT_INCLUDE:
            knh_stmtvisit_declc__include(ctx, stmt, v, level, step);
            break;
        case STT_UIMPORT:
            knh_stmtvisit_declc__uimport(ctx, stmt, v, level, step);
            break;
        case STT_UVOCAB:
            knh_stmtvisit_declc__uvocab(ctx, stmt, v, level, step);
            break;
        case STT_UINT:
            knh_stmtvisit_declc__uint(ctx, stmt, v, level, step);
            break;
        case STT_UINT64:
            knh_stmtvisit_declc__uint64(ctx, stmt, v, level, step);
            break;
        case STT_UFLOAT:
            knh_stmtvisit_declc__ufloat(ctx, stmt, v, level, step);
            break;
        case STT_UTABLE:
            knh_stmtvisit_declc__utable(ctx, stmt, v, level, step);
            break;
        case STT_UFUNC:
            knh_stmtvisit_declc__ufunc(ctx, stmt, v, level, step);
            break;
        case STT_WEAVE:
            knh_stmtvisit_declc__weave(ctx, stmt, v, level, step);
            break;
        case STT_CLASS:
            knh_stmtvisit_declc__class(ctx, stmt, v, level, step);
            break;
        case STT_HELP:
            knh_stmtvisit_declc__help(ctx, stmt, v, level, step);
            break;
    }
}

/* ======================================================================== */
/* [visit_declm] */

void knh_stmtvisit_declm(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
    switch(stmt->stt) {
        case STT_DONE: break;
        case STT_NAMESPACE:
            knh_stmtvisit_declm__namespace(ctx, stmt, v, level, step);
            break;
        case STT_CLASS:
            knh_stmtvisit_declm__class(ctx, stmt, v, level, step);
            break;
        case STT_METHOD:
            knh_stmtvisit_declm__method(ctx, stmt, v, level, step);
            break;
    }
}

/* ======================================================================== */
/* [visit_declv] */

void knh_stmtvisit_declv(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
    switch(stmt->stt) {
        case STT_DONE: break;
        case STT_NAMESPACE: 
            knh_Cmpl_before_declv(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_declv__namespace(ctx, stmt, v, level, step); 
            knh_Cmpl_after_declv(ctx, (Cmpl*)v, stmt, level);
            break;
        case STT_CLASS: 
            knh_Cmpl_before_declv(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_declv__class(ctx, stmt, v, level, step); 
            knh_Cmpl_after_declv(ctx, (Cmpl*)v, stmt, level);
            break;
        case STT_METHOD: 
            knh_Cmpl_before_declv(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_declv__method(ctx, stmt, v, level, step); 
            knh_Cmpl_after_declv(ctx, (Cmpl*)v, stmt, level);
            break;
        case STT_DECL: 
            knh_Cmpl_before_declv(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_declv__decl(ctx, stmt, v, level, step); 
            knh_Cmpl_after_declv(ctx, (Cmpl*)v, stmt, level);
            break;
        case STT_IF: 
            knh_Cmpl_before_declv(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_declv__if(ctx, stmt, v, level, step); 
            knh_Cmpl_after_declv(ctx, (Cmpl*)v, stmt, level);
            break;
        case STT_TRY: 
            knh_Cmpl_before_declv(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_declv__try(ctx, stmt, v, level, step); 
            knh_Cmpl_after_declv(ctx, (Cmpl*)v, stmt, level);
            break;
        case STT_DO: 
            knh_Cmpl_before_declv(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_declv__do(ctx, stmt, v, level, step); 
            knh_Cmpl_after_declv(ctx, (Cmpl*)v, stmt, level);
            break;
        case STT_WHILE: 
            knh_Cmpl_before_declv(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_declv__while(ctx, stmt, v, level, step); 
            knh_Cmpl_after_declv(ctx, (Cmpl*)v, stmt, level);
            break;
        case STT_FOR: 
            knh_Cmpl_before_declv(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_declv__for(ctx, stmt, v, level, step); 
            knh_Cmpl_after_declv(ctx, (Cmpl*)v, stmt, level);
            break;
        case STT_FOREACH: 
            knh_Cmpl_before_declv(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_declv__foreach(ctx, stmt, v, level, step); 
            knh_Cmpl_after_declv(ctx, (Cmpl*)v, stmt, level);
            break;
        case STT_LET: 
            knh_Cmpl_before_declv(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_declv__let(ctx, stmt, v, level, step); 
            knh_Cmpl_after_declv(ctx, (Cmpl*)v, stmt, level);
            break;
    }
}

/* ======================================================================== */
/* [visit_asm] */

void knh_stmtvisit_asm(Ctx *ctx, Stmt *stmt, Object *v, int level, int step)
{
    switch(stmt->stt) {
        case STT_DONE: break;
        case STT_NAMESPACE:
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__namespace(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            break;
        case STT_CLASS:
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__class(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            break;
        case STT_METHOD:
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__method(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            break;
        case STT_IF:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__if(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_TRY:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__try(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_DO:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__do(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_WHILE:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__while(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_FOR:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__for(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_FOREACH:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__foreach(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_CONTINUE:
            if(level == 0) {
                    return;
            }
            knh_stmtvisit_asm__continue(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            break;
        case STT_BREAK:
            if(level == 0) {
                    return;
            }
            knh_stmtvisit_asm__break(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            break;
        case STT_GOTO:
            if(level == 0) {
                    return;
            }
            knh_stmtvisit_asm__goto(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            break;
        case STT_THROW:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__throw(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_RETURN:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__return(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_EVAL:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__eval(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_PRINT:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__print(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_ASSERT:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__assert(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_NEW:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__new(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_MAP:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__map(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_LET:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__let(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_CALL:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__call(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_MOVTEXT:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__movtext(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_TRINARY:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__trinary(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_OP:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__op(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_ALT:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__alt(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_AND:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__and(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_OR:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__or(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_NEXT:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__next(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
        case STT_ERR:
            if(level == 0) {
                    knh_Cmpl_prepareRun(ctx, (Cmpl*)v, stmt);
            }
            knh_Cmpl_before_asm(ctx, (Cmpl*)v, stmt, level);
            knh_stmtvisit_asm__err(ctx, stmt, v, level, step);
            knh_Cmpl_after_asm(ctx, (Cmpl*)v, stmt, level);
            if(level == 0) {
                knh_Cmpl_commitRun(ctx, (Cmpl*)v, knh_Stmt_isVisible(stmt));
            }
            break;
    }
}

/* ======================================================================== */
/* [seval] */

Term* knh_Term_seval(Ctx *ctx, Term *b, knh_class_t req, NameSpace *ns)
{
    if(IS_Token(b)) {
        return knh_Token_seval(ctx, (Token*)b, req, ns);
    }
    Stmt *stmt = (Stmt*)b;
    DEBUG_ASSERT(IS_Stmt(stmt));
    Term *v;
    knh_int_t i, isall = 1;
    switch(stmt->stt) {
    case STT_DONE: 
        return b; 
    case STT_NAMESPACE: /* ['namespace', 'NAME'] */
        return b;
    case STT_INCLUDE: /* ['include', 'ANY'] */
        return b;
    case STT_UIMPORT: /* ['NSCLASSN'] */
        return b;
    case STT_UVOCAB: /* ['CLASSTN', 'CURN'] */
        return b;
    case STT_UINT: /* ['CLASSTN', 'CURN'] */
        return b;
    case STT_UINT64: /* ['CLASSTN', 'CURN'] */
        return b;
    case STT_UFLOAT: /* ['CLASSTN', 'CURN'] */
        return b;
    case STT_UTABLE: /* ['CLASSTN', 'CURN'] */
        return b;
    case STT_UFUNC: /* ['CMETHODN', 'NAME'] */
        return b;
    case STT_WEAVE: /* ['ANY', 'ANY'] */
        return b;
    case STT_CLASS: /* ['class', 'CLASSN', 'CLASSN', 'implements', '{'] */
        return b;
    case STT_IMPLEMENTS: /* ['implements', '+CLASSN'] */
        return b;
    case STT_METHOD: /* ['TYPEN', 'METHODFN', 'decl', '?{'] */
        return b;
    case STT_DECL: /* ['TYPEN', 'FIELDN', 'expr'] */
        v = knh_Term_seval(ctx, stmt->terms[2], knh_Stmt_reqtype(stmt, req, 2), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[2] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[2], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
    break;
    case STT_IF: /* ['if', 'expr', '{', '{'] */
        v = knh_Term_seval(ctx, stmt->terms[1], knh_Stmt_reqtype(stmt, req, 1), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[1] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[1], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
    break;
    case STT_TRY: /* ['try', '{', '__catch', '{'] */
        return b;
    case STT_CATCH: /* ['catch', 'EXPTN', 'FIELDN', '{'] */
        return b;
    case STT_DO: /* ['do', '{', 'while', 'expr'] */
        v = knh_Term_seval(ctx, stmt->terms[3], knh_Stmt_reqtype(stmt, req, 3), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[3] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[3], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
    break;
    case STT_WHILE: /* ['while', 'expr', '{'] */
        v = knh_Term_seval(ctx, stmt->terms[1], knh_Stmt_reqtype(stmt, req, 1), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[1] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[1], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
    break;
    case STT_FOR: /* ['for', 'expr', 'expr', 'expr', '{'] */
        v = knh_Term_seval(ctx, stmt->terms[1], knh_Stmt_reqtype(stmt, req, 1), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[1] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[1], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
        v = knh_Term_seval(ctx, stmt->terms[2], knh_Stmt_reqtype(stmt, req, 2), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[2] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[2], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
        v = knh_Term_seval(ctx, stmt->terms[3], knh_Stmt_reqtype(stmt, req, 3), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[3] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[3], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
    break;
    case STT_FOREACH: /* ['foreach', 'decl', 'FIELDN', 'expr', 'expr', '{'] */
        v = knh_Term_seval(ctx, stmt->terms[3], knh_Stmt_reqtype(stmt, req, 3), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[3] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[3], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
        v = knh_Term_seval(ctx, stmt->terms[4], knh_Stmt_reqtype(stmt, req, 4), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[4] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[4], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
    break;
    case STT_CONTINUE: /* ['continue', '?ANY'] */
        return b;
    case STT_BREAK: /* ['break', '?ANY'] */
        return b;
    case STT_GOTO: /* ['goto', 'ANY'] */
        return b;
    case STT_THROW: /* ['throw', 'expr'] */
        v = knh_Term_seval(ctx, stmt->terms[1], knh_Stmt_reqtype(stmt, req, 1), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[1] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[1], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
    break;
    case STT_RETURN: /* ['return', '?expr'] */
    if(2 == stmt->size) {
            v = knh_Term_seval(ctx, stmt->terms[1], knh_Stmt_reqtype(stmt, req, 1), ns);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(stmt->terms[1] != v) {
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[1], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
            }
            if(!knh_Term_isStaticValue(v)) {
                isall = 0;
            }
        }
    break;
    case STT_EVAL: /* ['eval', 'expr'] */
        v = knh_Term_seval(ctx, stmt->terms[1], knh_Stmt_reqtype(stmt, req, 1), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[1] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[1], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
    break;
    case STT_PRINT: /* ['print', '+expr'] */
        for(i = 1; i < stmt->size; i++) {
            v = knh_Term_seval(ctx, stmt->terms[i], knh_Stmt_reqtype(stmt, req, i), ns);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(stmt->terms[i] != v) {
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[i], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
            }
            if(!knh_Term_isStaticValue(v)) {
                isall = 0;
            }
        }
    break;
    case STT_ASSERT: /* ['assert', 'expr'] */
        v = knh_Term_seval(ctx, stmt->terms[1], knh_Stmt_reqtype(stmt, req, 1), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[1] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[1], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
    break;
    case STT_HELP: /* ['help', '?ANY'] */
        return b;
    case STT_NEW: /* ['NEW', 'CLASSN', '+expr'] */
        for(i = 2; i < stmt->size; i++) {
            v = knh_Term_seval(ctx, stmt->terms[i], knh_Stmt_reqtype(stmt, req, i), ns);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(stmt->terms[i] != v) {
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[i], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
            }
            if(!knh_Term_isStaticValue(v)) {
                isall = 0;
            }
        }
        if(isall) {
            v = knh_Stmt_seval__new(ctx, stmt, req);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(knh_Term_isStaticValue(v)) {
                DEBUG("switch CALL1..");
                stmt->stt = STT_CALL;
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[0], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
                stmt->size = 1;
            }
        }
    break;
    case STT_MAP: /* ['CLASSN', 'expr', '?expr'] */
        v = knh_Term_seval(ctx, stmt->terms[1], knh_Stmt_reqtype(stmt, req, 1), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[1] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[1], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
    if(3 == stmt->size) {
            v = knh_Term_seval(ctx, stmt->terms[2], knh_Stmt_reqtype(stmt, req, 2), ns);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(stmt->terms[2] != v) {
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[2], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
            }
            if(!knh_Term_isStaticValue(v)) {
                isall = 0;
            }
        }
        if(isall) {
            v = knh_Stmt_seval__map(ctx, stmt, req);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(knh_Term_isStaticValue(v)) {
                DEBUG("switch CALL1..");
                stmt->stt = STT_CALL;
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[0], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
                stmt->size = 1;
            }
        }
    break;
    case STT_LET: /* ['FIELDN', 'expr'] */
        v = knh_Term_seval(ctx, stmt->terms[1], knh_Stmt_reqtype(stmt, req, 1), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[1] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[1], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
    break;
    case STT_CALL: /* ['METHODN', '+expr'] */
        for(i = 1; i < stmt->size; i++) {
            v = knh_Term_seval(ctx, stmt->terms[i], knh_Stmt_reqtype(stmt, req, i), ns);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(stmt->terms[i] != v) {
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[i], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
            }
            if(!knh_Term_isStaticValue(v)) {
                isall = 0;
            }
        }
        if(isall) {
            v = knh_Stmt_seval__call(ctx, stmt, req);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(knh_Term_isStaticValue(v)) {
                DEBUG("switch CALL1..");
                stmt->stt = STT_CALL;
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[0], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
                stmt->size = 1;
            }
        }
    break;
    case STT_MOVTEXT: /* ['MOVTEXT', 'expr'] */
        v = knh_Term_seval(ctx, stmt->terms[1], knh_Stmt_reqtype(stmt, req, 1), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[1] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[1], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
        if(isall) {
            v = knh_Stmt_seval__movtext(ctx, stmt, req);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(knh_Term_isStaticValue(v)) {
                DEBUG("switch CALL1..");
                stmt->stt = STT_CALL;
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[0], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
                stmt->size = 1;
            }
        }
    break;
    case STT_TRINARY: /* ['expr', 'expr', 'expr'] */
        v = knh_Term_seval(ctx, stmt->terms[0], knh_Stmt_reqtype(stmt, req, 0), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[0] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[0], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
        v = knh_Term_seval(ctx, stmt->terms[1], knh_Stmt_reqtype(stmt, req, 1), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[1] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[1], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
        v = knh_Term_seval(ctx, stmt->terms[2], knh_Stmt_reqtype(stmt, req, 2), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[2] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[2], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
    break;
    case STT_OP: /* ['OP', 'expr', '+expr'] */
        v = knh_Term_seval(ctx, stmt->terms[1], knh_Stmt_reqtype(stmt, req, 1), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[1] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[1], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
        for(i = 2; i < stmt->size; i++) {
            v = knh_Term_seval(ctx, stmt->terms[i], knh_Stmt_reqtype(stmt, req, i), ns);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(stmt->terms[i] != v) {
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[i], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
            }
            if(!knh_Term_isStaticValue(v)) {
                isall = 0;
            }
        }
        if(isall) {
            v = knh_Stmt_seval__op(ctx, stmt, req);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(knh_Term_isStaticValue(v)) {
                DEBUG("switch CALL1..");
                stmt->stt = STT_CALL;
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[0], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
                stmt->size = 1;
            }
        }
    break;
    case STT_ALT: /* ['expr', '+expr'] */
        v = knh_Term_seval(ctx, stmt->terms[0], knh_Stmt_reqtype(stmt, req, 0), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[0] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[0], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
        for(i = 1; i < stmt->size; i++) {
            v = knh_Term_seval(ctx, stmt->terms[i], knh_Stmt_reqtype(stmt, req, i), ns);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(stmt->terms[i] != v) {
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[i], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
            }
            if(!knh_Term_isStaticValue(v)) {
                isall = 0;
            }
        }
        if(isall) {
            v = knh_Stmt_seval__alt(ctx, stmt, req);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(knh_Term_isStaticValue(v)) {
                DEBUG("switch CALL1..");
                stmt->stt = STT_CALL;
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[0], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
                stmt->size = 1;
            }
        }
    break;
    case STT_AND: /* ['expr', '+expr'] */
        v = knh_Term_seval(ctx, stmt->terms[0], knh_Stmt_reqtype(stmt, req, 0), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[0] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[0], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
        for(i = 1; i < stmt->size; i++) {
            v = knh_Term_seval(ctx, stmt->terms[i], knh_Stmt_reqtype(stmt, req, i), ns);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(stmt->terms[i] != v) {
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[i], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
            }
            if(!knh_Term_isStaticValue(v)) {
                isall = 0;
            }
        }
        if(isall) {
            v = knh_Stmt_seval__and(ctx, stmt, req);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(knh_Term_isStaticValue(v)) {
                DEBUG("switch CALL1..");
                stmt->stt = STT_CALL;
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[0], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
                stmt->size = 1;
            }
        }
    break;
    case STT_OR: /* ['expr', '+expr'] */
        v = knh_Term_seval(ctx, stmt->terms[0], knh_Stmt_reqtype(stmt, req, 0), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[0] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[0], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
        for(i = 1; i < stmt->size; i++) {
            v = knh_Term_seval(ctx, stmt->terms[i], knh_Stmt_reqtype(stmt, req, i), ns);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(stmt->terms[i] != v) {
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[i], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
            }
            if(!knh_Term_isStaticValue(v)) {
                isall = 0;
            }
        }
        if(isall) {
            v = knh_Stmt_seval__or(ctx, stmt, req);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(knh_Term_isStaticValue(v)) {
                DEBUG("switch CALL1..");
                stmt->stt = STT_CALL;
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[0], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
                stmt->size = 1;
            }
        }
    break;
    case STT_NEXT: /* ['expr', 'ANY'] */
        v = knh_Term_seval(ctx, stmt->terms[0], knh_Stmt_reqtype(stmt, req, 0), ns);
        DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
        if(stmt->terms[0] != v) {
            Object *avoid_gc = NULL;
            KNH_INITv(avoid_gc, v);
            KNH_SETv(ctx, stmt->terms[0], avoid_gc);
            KNH_FINALv(ctx, avoid_gc);
        }
        if(!knh_Term_isStaticValue(v)) {
            isall = 0;
        }
        
        if(isall) {
            v = knh_Stmt_seval__next(ctx, stmt, req);
            DEBUG_ASSERT(v != NULL && IS_NOTNULL(v));
            if(knh_Term_isStaticValue(v)) {
                DEBUG("switch CALL1..");
                stmt->stt = STT_CALL;
                Object *avoid_gc = NULL;
                KNH_INITv(avoid_gc, v);
                KNH_SETv(ctx, stmt->terms[0], avoid_gc);
                KNH_FINALv(ctx, avoid_gc);
                stmt->size = 1;
            }
        }
    break;
    case STT_META: /* ['+META'] */
        return b;
    case STT_ERR: /* ['ERR'] */
        return b;
    }
    return b;
}

/* ======================================================================== */
/* [cmpl_asm] */

knh_asmv_t
knh_Cmpl_asmv(Ctx *ctx, Cmpl *b, Term *tm, knh_type_t req, int sp)
{
	if(IS_Token(tm)) {
		if(knh_Term_isStaticValue(tm)) {
			return new_asmv__StaticValue(ctx, (Token*)tm, req);
		}
		Token *tk = (Token*)tm;
		if(knh_Token_isFIELDN(tk)) {
			return new_asmv__name(ctx, b, tk, req, sp);
		}
		DEBUG("unknown token %s", knh_Token_tochar(tk));
		return new_asmv__noname(ctx, tk, req);
	}
	DEBUG_ASSERT(IS_Stmt(tm));
	Stmt *stmt = (Stmt*)tm;
	switch(stmt->stt) {
	case STT_METHOD:
		return knh_Cmpl_asmv__method(ctx, b, tm, req, sp);
	case STT_NEW:
		return knh_Cmpl_asmv__new(ctx, b, tm, req, sp);
	case STT_MAP:
		return knh_Cmpl_asmv__map(ctx, b, tm, req, sp);
	case STT_CALL:
		return knh_Cmpl_asmv__call(ctx, b, tm, req, sp);
	case STT_MOVTEXT:
		return knh_Cmpl_asmv__movtext(ctx, b, tm, req, sp);
	case STT_TRINARY:
		return knh_Cmpl_asmv__trinary(ctx, b, tm, req, sp);
	case STT_OP:
		return knh_Cmpl_asmv__op(ctx, b, tm, req, sp);
	case STT_ALT:
		return knh_Cmpl_asmv__alt(ctx, b, tm, req, sp);
	case STT_AND:
		return knh_Cmpl_asmv__and(ctx, b, tm, req, sp);
	case STT_OR:
		return knh_Cmpl_asmv__or(ctx, b, tm, req, sp);
	case STT_NEXT:
		return knh_Cmpl_asmv__next(ctx, b, tm, req, sp);
	}
	DEBUG("unknown expr %s", knh_stmt_tochar(stmt->stt));
	return new_asmv__OBJ(KNH_NULL);
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
