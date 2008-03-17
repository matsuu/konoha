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

#ifndef KONOHAC_T_H_
#define KONOHAC_T_H_

#include<konoha/konoha_t.h>

#include"konoha.h"

/* ************************************************************************ */

#ifdef __cplusplus 
extern "C" {
#endif

#define KNH_STT_LVALUE  0
#define KNH_STT_RVALUE  1

/* ------------------------------------------------------------------------ */

typedef knh_ushort_t   knh_token_t;
typedef knh_ushort_t   knh_stmt_t;

/* ------------------------------------------------------------------------ */

#define MC_FATAL     0
#define MC_LANG      1
#define MC_ERROR     2
#define MC_TYPE      3
#define MC_WARNING   4
#define MC_IGNORED   5
#define MC_ERRATA    6
#define MC_NOTICE    7
#define MC_INFO      8

#define MC_EPRINT(ctx, tk, lv, fmt, ...) { \
		DEBUG("<ERR=%d>", lv); \
		OutputStream *w_ = konohac_perror(ctx, tk, lv); \
		knh_printf(ctx, w_, fmt, ##__VA_ARGS__); \
		knh_println(ctx, w_, STEXT("")); \
		knh_flush(ctx, w_); \
	} \

#define MC_EPRINT2(ctx, tk, lv, fmt, ...) \
	if(!knh_Token_isPerrored(tk)) { \
		DEBUG(fmt, ##__VA_ARGS__); \
		konohac_perror(ctx, tk, lv); \
		konohac_eprintf(ctx, tk, lv, fmt, ##__VA_ARGS__); \
		knh_Token_setPerrored(tk, 1); \
	} else { \
		DEBUG(fmt, ##__VA_ARGS__); \
	} \

/* ------------------------------------------------------------------------ */

#define KNH_GOTO(L) \
	DEBUG("goto .."); \
	goto L; \

/* ------------------------------------------------------------------------ */
/* @class Token Object knh_Token */
/* @flag Token.TailC TKF (%s)->flag 'is:set:*:*' */
/* @flag Token.TopDot TKF (%s)->flag 'is:set:*:*' */
/* @flag Token.ExceptionType TKF (%s)->flag 'is:set:*:*' */
/* @flag Token.NotNullType TKF (%s)->flag 'is:set:*:*' */
/* @flag Token.IteratorType TKF (%s)->flag 'is:set:*:*' */
/* @flag Token.ArrayType TKF (%s)->flag 'is:set:*:*' */
/* @flag Token.NextParenthesis TKF (%s)->flag 'is:set:*:*' */
/* @flag Token.NextBrace TKF (%s)->flag 'is:set:*:*' */
/* @flag Token.NextBrancet TKF (%s)->flag 'is:set:*:*' */
/* @flag Token.ToGet TKF (%s)->flag 'is:set:*:*' */
/* @flag Token.ToSet TKF (%s)->flag 'is:set:*:*' */
/* @flag Token.Generated TKF (%s)->flag 'is:set:*:*' */
/* @flag Token.Perrored TKF (%s)->flag 'is:set:*:*' */

typedef struct knh_Token {
	knh_token_t tt;
	knh_flag_t flag;
	knh_filen_t filen;
	knh_line_t line;
	Object* data;
} knh_Token;


/* ------------------------------------------------------------------------ */
/* @class Stmt Object knh_Stmt */
/* @flag Stmt.Adposition STMTF (%s)->flag 'is:set:*:*' */
/* @flag Stmt.PrintLine STMTF (%s)->flag 'is:set:*:*' */
/* @flag Stmt.OpNext STMTF (%s)->flag 'is:set:*:*' */
/* @flag Stmt.OpPrev STMTF (%s)->flag 'is:set:*:*' */
/* @flag Stmt.Visible STMTF (%s)->flag 'is:set:*:*' */

/* ------------------------------------------------------------------------ */

#define Term         Object
#define IS_Term(o)   (IS_Token(o)||IS_Stmt(o))

typedef struct knh_Stmt {
	knh_flag_t flag;
	knh_stmt_t stt;
	knh_ushort_t size;
	knh_ushort_t capacity;
	Term** terms;
	struct knh_Stmt* meta;
	struct knh_Stmt* next;
} knh_Stmt;

struct knh_Stmt;
typedef void    (*f_stmtvisit)(Ctx*, struct knh_Stmt*, Object*, int, int);
//typedef void    (*f_termvisit)(Ctx*, Term *, Object*, int, int);

/* ------------------------------------------------------------------------ */
/* @class Cmpl Object knh_Cmpl */
/* @flag Cmpl.SyntaxError CPF (%s)->flag 'is:set:*:*' */
/* @flag Cmpl.TypeError CPF (%s)->flag 'is:set:*:*' */
/* @flag Cmpl.Cancelled CPF (%s)->flag 'is:set:*:*' */

typedef struct knh_Cmpl {
	knh_flag_t flag;
	knh_nsn_t nsn;
	knh_Prototype* nsproto;
	knh_filen_t filen;
	knh_class_t this_cid;
	knh_Method* method;
	knh_ushort_t vars_size;
	knh_ushort_t vars_offset;
	knh_cfield_t* vars;
	int nastep;
	int llstep;
	knh_Bytes* elf;
	knh_Bytes* dwarf;
	int line;
	knh_DictIdx* labelIdDictIdx;
	knh_DictSet* labelAddrDictSet;
	knh_Array* lstacks;
} knh_Cmpl;

/* ------------------------------------------------------------------------ */
/* @class VirtualMachineCode Object knh_VirtualMachineCode */

typedef struct {
	knh_ushort_t offset;
	knh_ushort_t line;
} knh_dwarf_t;

typedef struct knh_VirtualMachineCode {
	knh_vmc_t* code;
	size_t size;
	knh_filen_t filen;
	knh_nsn_t nsn;
	knh_dwarf_t* dwarf;
	size_t dsize;
} knh_VirtualMachineCode;


/* ------------------------------------------------------------------------ */

#define KNH_ASMV_ONSTACK 0
#define KNH_ASMV_EBP  0
#define KNH_ASMV_SFP  1
#define KNH_ASMV_OFP  2
#define KNH_ASMV_OBJ  3
#define KNH_ASMV_OIDX 4
#define KNH_ASMV_ERR  5

typedef struct {
	knh_uchar_t  potype;
	knh_uchar_t  index;
	knh_type_t   type; 
	Object     *value;
} knh_asmv_t;


/* ************************************************************************ */

#ifdef __cplusplus 
}
#endif

#include"../gen/konohac_.h"

#endif /*KONOHAC_T_H_*/
